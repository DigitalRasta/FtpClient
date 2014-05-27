#include "../header/ModelConnection.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../lib/ftpparse.h"
#include <curl\curl.h>
#include <time.h>
#include <sstream>
#include <list>
#include <stdint.h>
#include <Windows.h>
#include <functional>

using namespace FtpClient;

ModelConnection::ModelConnection(std::string host, std::string port, std::string login, std::string password, InnerConfig* configObject){
	this->loginPass = login + ":" + password;
	this->hostURL = "ftp://"+host+":"+port;
	this->filesList = NULL;
}


size_t ModelConnection::GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object){
	char* responseResult = (char*)ptr;
	ModelConnection * connection = (ModelConnection*) object;
	std::string line;
	bool backDotsFound = false;
	int id = 0;
	for(int i = 0; i < nmemb; i++) {
		if(responseResult[i] == '\n') {
			connection->parseLineAndAddToList(line, id);
			id++;
			if(connection->filesList->size() > 0 && connection->filesList->back().fileName.compare("..") == 0) {
				backDotsFound = true;
			}
			line.erase();
			continue;
		}
		line.push_back(responseResult[i]);
	}
	if(!backDotsFound && connection->currentPath.compare("/") != 0) {
		connection->filesList->push_front(ContainerFileInfo(connection->currentPath, std::string(".."), -1, true, -1, -1, -1, -1, -1, -1));
	}
    return nmemb;
}

std::list<ContainerFileInfo>* ModelConnection::getDirectoryContent(std::string path) {
	this->currentPath = path;
	this->clearListAndInit();
	this->libFtpObject = curl_easy_init();
	curl_easy_setopt(this->libFtpObject, CURLOPT_URL, (this->hostURL+path).c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_USERPWD, this->loginPass.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEFUNCTION, &GetFilesList_response);
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEDATA, this); //send >this< object to static method
	int result = curl_easy_perform(this->libFtpObject);
	if(result != 0) {
		throw ContainerException(ExceptionLevel::EXCEPTIONLEVEL_HIGH, this->translateCurlErrorCode(result));
	}
	curl_easy_cleanup(this->libFtpObject);
	return this->filesList;
}

void ModelConnection::clearListAndInit() {
	if(this->filesList != NULL) {
		delete this->filesList;
	}
	this->filesList = new std::list<ContainerFileInfo>();
}

void ModelConnection::parseLineAndAddToList(std::string line, int id) {
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
	if(parseContainer.name[1] == '.' && this->currentPath.compare("/") == 0) {
		return;
	}
	
	tm* timeContainer = localtime(&parseContainer.mtime);
	
	if(parseContainer.flagtrycwd == 1) {
		this->filesList->push_back(ContainerFileInfo(this->currentPath, std::string(parseContainer.name), -1, true, timeContainer->tm_mday, timeContainer->tm_mon+1, timeContainer->tm_year+1900, timeContainer->tm_hour, timeContainer->tm_min, id));
	} else {
		this->filesList->push_back(ContainerFileInfo(this->currentPath, std::string(parseContainer.name), parseContainer.size, false, timeContainer->tm_mday, timeContainer->tm_mon+1, timeContainer->tm_year+1900, timeContainer->tm_hour, timeContainer->tm_min, id));
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

void ModelConnection::setFilesList(std::list<ContainerFileInfo>* list) {
	this->filesList = list;
}

bool ModelConnection::deleteFile(ContainerFileInfo* file) {
	std::string path = this->currentPath;
	std::string command;
	this->libFtpObject = curl_easy_init();
	curl_slist commandsList;
	commandsList.next = NULL;
	curl_easy_setopt(this->libFtpObject, CURLOPT_URL, (this->hostURL+path).c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_USERPWD, this->loginPass.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_FTP_RESPONSE_TIMEOUT, 10);
	if(file->isDir) {
		command = "RMD " + file->filePath + file->fileName;
		commandsList.data =  const_cast<char*>(command.c_str());
	} else {	
		command = "DELE " + file->filePath + file->fileName;
		commandsList.data =  const_cast<char*>(command.c_str());
	}	
	curl_easy_setopt(this->libFtpObject, CURLOPT_QUOTE, &commandsList);
	int result = curl_easy_perform(this->libFtpObject);
	curl_easy_cleanup(this->libFtpObject);
	if(result == 0) {
		 return true;
	} 
	return false;
}

bool ModelConnection::newFolder(std::string pathWithName) {
	std::string command = "MKD " + pathWithName;
	this->libFtpObject = curl_easy_init();
	curl_easy_setopt(this->libFtpObject, CURLOPT_URL, (this->hostURL+this->currentPath).c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_USERPWD, this->loginPass.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_FTP_RESPONSE_TIMEOUT, 10);
	curl_slist commandsList;
	commandsList.next = NULL;
	commandsList.data = const_cast<char*>(command.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_QUOTE, &commandsList);
	int result = curl_easy_perform(this->libFtpObject);
	curl_easy_cleanup(this->libFtpObject);
	if(result == 0) {
		 return true;
	} 
	return false;
}

size_t ModelConnection::downloadFileWriteFunction(void *buffer, size_t size, size_t nmemb, void *stream){
	struct FtpFile* out = (struct FtpFile*)stream;
	if(!out->stream) {
		return -1;
	}
	uint64_t result = fwrite(buffer, size, nmemb, out->stream);
	out->progress += result;
	double precent = ((double)out->progress) / ((double)out->size);
	out->progressBarCallback(precent);
	return result;
}

bool ModelConnection::downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback) {
	this->endDownloadCallback = endDownloadCallback;
	this->downloadFileHandler.stream = fopen((localPath+name).c_str(), "wb");
	this->mainThread = GetCurrentThread();
	if(this->downloadFileHandler.stream) {
		fclose(this->downloadFileHandler.stream);
	} else {
		return false;
	}
	this->downloadFileHandler.stream =  fopen((localPath+name).c_str(), "ab");
	this->downloadFileHandler.size = size;
	this->downloadFileHandler.progress = 0;
	this->downloadFileHandler.progressBarCallback = progressBarCallback;
	this->libFtpObject = curl_easy_init();
	curl_easy_setopt(this->libFtpObject, CURLOPT_URL, (this->hostURL+serverPath+name).c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_USERPWD, this->loginPass.c_str());
	curl_easy_setopt(this->libFtpObject, CURLOPT_FTP_RESPONSE_TIMEOUT, 10);
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEFUNCTION, this->downloadFileWriteFunction);
	curl_easy_setopt(this->libFtpObject, CURLOPT_WRITEDATA, &this->downloadFileHandler);
	this->downloadThread = CreateThread(NULL, 0, startDownload, (void*) this, 0, NULL);
	this->downloadObserverThread = CreateThread(NULL, 0, checkDownloadRunning, (void*) this, 0, NULL);
	return true;
}

DWORD WINAPI ModelConnection::startDownload(void* Param) {
	ModelConnection* This = (ModelConnection*)Param;
	int check = curl_easy_perform(This->libFtpObject);
	fclose(This->downloadFileHandler.stream);
	if(check == 0) {
		This->downloadCode = 0;
	} else {
		This->downloadCode = This->translateCurlErrorCode(check);
	}
	return 0;
}

DWORD WINAPI ModelConnection::checkDownloadRunning(void* Param) {
	ModelConnection* This = (ModelConnection*)Param;
	while(true) {
		int threadResult = WaitForSingleObject(This->downloadThread, 20);
		if(threadResult == WAIT_TIMEOUT) {
			Sleep(100);
		} else {
			if(threadResult == WAIT_OBJECT_0) {
				This->endDownloadCallback(This->downloadCode);
				break;
			} else {
				This->endDownloadCallback(-1);
				break;
			}
		}
	}
	return 0;
}



ModelConnection::~ModelConnection(void)
{
}
