#include "../header/ModelConnection.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../lib/ftpparse.h"
#include <curl\curl.h>
#include <time.h>
#include <sstream>
#include <list>

using namespace FtpClient;

ModelConnection::ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject){
	this->libFtpObject = curl_easy_init();
	this->ID = connectionId;
	this->loginPass = login + ":" + password;
	this->hostURL = "ftp://"+host+"/";
	this->filesList = NULL;
}

int ModelConnection::getId(void) {
	return this->ID;
}

size_t ModelConnection::GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object){
	char* responseResult = (char*)ptr;
	ModelConnection * connection = (ModelConnection*) object;
	connection->clearListAndInit();
	std::string line;
	bool backDotsFound = false;
	for(int i = 0; i < nmemb; i++) {
		if(responseResult[i] == '\n') {
			connection->parseLineAndAddToList(line);
			if(connection->filesList->size() > 0 && connection->filesList->back().fileName.compare("..") == 0) {
				backDotsFound = true;
			}
			line.erase();
			continue;
		}
		line.push_back(responseResult[i]);
	}
	if(!backDotsFound) {
		connection->filesList->push_front(ContainerFileInfo(connection->currentPath, std::string(".."), -1, true, -1, -1, -1, -1, -1, -1));
	}
    return nmemb;
}

std::list<ContainerFileInfo>* ModelConnection::getDirectoryContent(std::string path) {
	this->currentPath = path;
	curl_easy_setopt(this->libFtpObject, CURLOPT_URL, (this->hostURL+path).c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_USERPWD, this->loginPass.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEFUNCTION, &GetFilesList_response);
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEDATA, this); //send >this< object to static method
	int result = curl_easy_perform(this->libFtpObject);
	if(result != 0) {
		throw ContainerException(ExceptionLevel::EXCEPTIONLEVEL_HIGH, this->translateCurlErrorCode(result));
	}
	return this->filesList;
}

void ModelConnection::clearListAndInit() {
	if(this->filesList != NULL) {
		delete this->filesList;
	}
	this->filesList = new std::list<ContainerFileInfo>();
}

void ModelConnection::parseLineAndAddToList(std::string line) {
	if(line[line.length()-1] == '\r') {
		line.resize(line.length()-1);
	}
	struct ftpParseSpace::ftpparse parseContainer;
	int result = ftpParseSpace::ftpparse(&parseContainer, const_cast<char*>(line.c_str()), (int)line.length());
	if(result == 0) {
		throw ContainerException(ExceptionLevel::EXCEPTIONLEVEL_CRITICAL, ExceptionCode::ERROR_CONNECTION_UNKNOWN_FTP_LIST_FORMAT);
	}
	if(parseContainer.name[0] == '.') {
		return;
	}
	
	tm* timeContainer = localtime(&parseContainer.mtime);
	
	if(parseContainer.flagtrycwd == 1) {
		this->filesList->push_back(ContainerFileInfo(this->currentPath, std::string(parseContainer.name), -1, true, timeContainer->tm_mday, timeContainer->tm_mon+1, timeContainer->tm_year+1900, timeContainer->tm_hour, timeContainer->tm_min));
	} else {
		this->filesList->push_back(ContainerFileInfo(this->currentPath, std::string(parseContainer.name), parseContainer.size, false, timeContainer->tm_mday, timeContainer->tm_mon+1, timeContainer->tm_year+1900, timeContainer->tm_hour, timeContainer->tm_min));
	}
}


ExceptionCode ModelConnection::translateCurlErrorCode(int code) {
	switch(code) {
	case CURLE_FAILED_INIT: 
	case CURLE_COULDNT_CONNECT:
	case CURLE_FTP_WEIRD_PASS_REPLY:
	case CURLE_FTP_WEIRD_PASV_REPLY:
	case CURLE_FTP_WEIRD_227_FORMAT:
	case CURLE_FTP_CANT_GET_HOST:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_FAILED_TO_CONNECT;
	case CURLE_OPERATION_TIMEDOUT:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_TIMEOUT;
	case CURLE_FTP_COULDNT_SET_TYPE:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_TYPE;
	case CURLE_PARTIAL_FILE:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_SIZE_NOT_MATCH;
	case CURLE_WRITE_ERROR:
	case CURLE_FTP_COULDNT_RETR_FILE:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_ERROR;
	case CURLE_QUOTE_ERROR:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_QUOTE_ERROR;
	case CURLE_UPLOAD_FAILED:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_UPLOAD_ERROR;
	case CURLE_FTP_PORT_FAILED:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_INVALID_PORT;
	default:
		return ExceptionCode::ERROR_CONNECTION_LIBCURL_UNKNOWN_ERROR;
	}
}

ModelConnection::~ModelConnection(void)
{
}
