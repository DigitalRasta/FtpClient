#include "../header/ModelDAO.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../header/ContainerException.h"
#include "../header/ModelConnection.h"
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <list>
#include <stdint.h>
#include <algorithm>


using namespace FtpClient;
ModelDAO::ModelDAO(InnerConfig* innerConfigObject):innerConfigObject(innerConfigObject){
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	this->connectionObject = NULL;
}


ModelDAO::~ModelDAO(void){
	delete(this->connectionObject);
}

std::list<ContainerFileInfo>* ModelDAO::getLogicalDrives(void) {
	DWORD volumesList = ::GetLogicalDrives(); //Return 32 bits, if first bit = 1 it means A aviable, second = 1 means B etc.
	std::vector<std::string> drivesList =  this->convertLogicalDrives(volumesList);
	std::list<ContainerFileInfo>* listToReturn = new std::list<ContainerFileInfo>;
	for(unsigned int i = 0; i < drivesList.size(); i++) {
		(*listToReturn).push_back(ContainerFileInfo(drivesList[i]+":", drivesList[i], i));
	}
	return listToReturn;
}

std::vector<std::string> ModelDAO::convertLogicalDrives(DWORD volumesList) {
	std::vector<std::string> returnVector = std::vector<std::string>();
	for(int i = 0; i < 32; i++) {
		char letter = 'A'+i;
		unsigned int bits = 1;
		bits = bits << i;
		if((bits & volumesList) == bits) {
			std::stringstream strStr;
			std::string strToVector;
			strStr << letter;
			strStr >> strToVector;
			returnVector.push_back(strToVector);
		}
	}
	return returnVector;
}


std::list<ContainerFileInfo>* ModelDAO::getDirectoryContent(std::string pathOrg) {
	WIN32_FIND_DATAA result;
	HANDLE searchHandle;
	std::list<ContainerFileInfo>* listToReturn = new std::list<ContainerFileInfo>();
	if(pathOrg.back() != '/') {
		pathOrg += "/";
	}
	std::string path = pathOrg + "*"; //add for all files listing
	searchHandle = FindFirstFileA(path.c_str(), &result);
	if(searchHandle == INVALID_HANDLE_VALUE) { //cannot read directory content
		throw ContainerException(FtpClient::EXCEPTIONLEVEL_STANDARD, FtpClient::ERROR_DIRECTORY_LISTING);
	}
	int id = 0;
	do {
		ContainerFileInfo fileToPush;
		//0x2 means hidden file
		if((result.dwFileAttributes & 0x2) == 0x2 || std::string(result.cFileName).compare(".") == 0) {
			continue;
		}
		//0x10 means directory
		bool dir = false;
		if((result.dwFileAttributes & 0x10) == 0x10) {
			dir = true;
		}
		uint64_t fileSize = (result.nFileSizeHigh * (MAXDWORD+1)) + result.nFileSizeLow;
		FILETIME timeConversionUTC;
		SYSTEMTIME timeConversion;
		int timeConversionSuccessUTC = FileTimeToLocalFileTime(&result.ftCreationTime, &timeConversionUTC); //Conversion from UTC time to local PC time
		int timeConversionSuccess = FileTimeToSystemTime(&timeConversionUTC, &timeConversion);
		if(timeConversionSuccess && timeConversionSuccessUTC) {
			fileToPush = ContainerFileInfo(pathOrg, std::string(result.cFileName), fileSize, dir, timeConversion.wDay, timeConversion.wMonth, timeConversion.wYear, timeConversion.wHour, timeConversion.wMinute, id);
		} else {
			fileToPush = ContainerFileInfo(pathOrg, std::string(result.cFileName), fileSize, dir, -1, -1, -1, -1, -1, id);
		}
		(*listToReturn).push_back(fileToPush);
		id++;
	}while(FindNextFileA(searchHandle, &result) != 0); //search whole dir
	if(((*listToReturn).front()).fileName.compare("..") !=0) {
		(*listToReturn).push_front(ContainerFileInfo(pathOrg, "..", -1, true, -1, -1, -1, -1, -1, -1));
	}
	FindClose(searchHandle);
	return this->orderFilesListDirecrotiesFiles(listToReturn);
}

std::list<ContainerFileInfo>* ModelDAO::orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder) {
	std::list<ContainerFileInfo>* directories = new std::list<ContainerFileInfo>(*listToOrder);
	std::list<ContainerFileInfo>* files = new std::list<ContainerFileInfo>(*listToOrder);
	auto compDirs = [](ContainerFileInfo val) -> bool {return val.isDir == false;};
	auto compFiles = [](ContainerFileInfo val) -> bool {return val.isDir == true;};
	(*directories).remove_if(compDirs);
	(*files).remove_if(compFiles);
	(*directories).splice((*directories).end(), (*files));
	delete files;
	*listToOrder = std::list<ContainerFileInfo>(*directories);
	delete directories;
	return listToOrder;
}

bool ModelDAO::isPathLogicalPartition(std::string path) {
	int occurences = std::count(path.begin(), path.end(), '/');
	if(occurences > 1) { //path longer
		return false;
	} else { //path is like "F:/"
		return true;
	}
}

std::string ModelDAO::goUpInDirPath(std::string path) {
	std::string cutPath = path;
	if(path[path.size()-1] == '/') {
		cutPath.resize(cutPath.size()-1); //cut last '/'
	}
	int cutPosition = cutPath.rfind('/');
	cutPath.resize(cutPosition+1);
	return cutPath;
}


void ModelDAO::createNewConnection(std::string host, std::string port, std::string login, std::string password) {
	if(this->connectionObject != NULL) {
		delete this->connectionObject;
	}
	if(host.empty() || port.empty() || login.empty() || password.empty()) {
		throw ContainerException(ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_INVALID_PARAMS);
	}
	this->connectionObject = new ModelConnection(host, port, login, password, this->innerConfigObject);
}

std::list<ContainerFileInfo>* ModelDAO::serverGetDirectoryContent(std::string path) {
	try {
		std::list<ContainerFileInfo>* filesList = this->connectionObject->getDirectoryContent(path);
		filesList = this->orderFilesListDirecrotiesFiles(filesList);
		this->connectionObject->setFilesList(filesList);
		return filesList;
	} catch (ContainerException &e) {
		throw;
	}
}

bool ModelDAO::isPathServerRoot(std::string path) {
	if(path.compare("/") == 0) {
		return true;
	} else {
		return false;
	}
}

bool ModelDAO::deleteLocalFile(ContainerFileInfo *file) {
	std::string path = file->filePath + file->fileName;
	if(file->isDir) {
		return RemoveDirectoryA(path.c_str());
	} else {
		return DeleteFileA(path.c_str());
	}
}

bool ModelDAO::deleteServerFile(ContainerFileInfo *file) {
	return this->connectionObject->deleteFile(file);
}

bool ModelDAO::newFolderLocal(std::string pathWithName) {
	if(pathWithName[2] != '/') {
		return false;
	}
	return CreateDirectoryA(pathWithName.c_str(), NULL);
}

bool ModelDAO::newFolderServer(std::string pathWithName) {
	return this->connectionObject->newFolder(pathWithName);
}

void ModelDAO::downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback) {
	this->connectionObject->downloadFile(serverPath, localPath, name, size, progressBarCallback, endDownloadCallback);
}

void ModelDAO::uploadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endUploadCallback) {
	this->connectionObject->uploadFile(serverPath, localPath, name, size, progressBarCallback, endUploadCallback);
}

void ModelDAO::killTransferThread() {
	fclose(this->connectionObject->transferFileHandler.stream);
	bool flag = TerminateThread(this->connectionObject->transferThread, 1);
	if(!flag) {
		throw ContainerException(ExceptionLevel::EXCEPTIONLEVEL_HIGH, ExceptionCode::ERROR_THREAD_CANNOT_KILL);
	}
}