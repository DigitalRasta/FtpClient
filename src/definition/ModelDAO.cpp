#include "../header/ModelDAO.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../header/ContainerException.h"
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <list>
#include <stdint.h>


using namespace FtpClient;
ModelDAO::ModelDAO(InnerConfig* innerConfigObject):innerConfigObject(innerConfigObject){
}


ModelDAO::~ModelDAO(void){
}

std::list<ContainerFileInfo> ModelDAO::getLogicalDrives(void) {
	DWORD volumesList = ::GetLogicalDrives(); //Return 32 bits, if first bit = 1 it means A aviable, second = 1 means B etc.
	std::vector<std::string> drivesList =  this->convertLogicalDrives(volumesList);
	std::list<ContainerFileInfo> listToReturn;
	for(unsigned int i = 0; i < drivesList.size(); i++) {
		listToReturn.push_back(ContainerFileInfo(drivesList[i]+":", drivesList[i]));
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


std::list<ContainerFileInfo> ModelDAO::getDirectoryContent(std::string path) {
	WIN32_FIND_DATAA result;
	HANDLE searchHandle;
	std::list<ContainerFileInfo> listToReturn = std::list<ContainerFileInfo>();
	path += "*"; //add for all files listing
	searchHandle = FindFirstFileA(path.c_str(), &result);
	if(searchHandle == INVALID_HANDLE_VALUE) {
		throw ContainerException(this->innerConfigObject->error_directoryListing, FtpClient::EXCEPTIONLEVEL_STANDARD, FtpClient::ERROR_DIRECTORY_LISTING);
	}
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
			fileToPush = ContainerFileInfo(path, std::string(result.cFileName), fileSize, dir, timeConversion.wDay, timeConversion.wMonth, timeConversion.wYear, timeConversion.wHour, timeConversion.wMinute);
		} else {
			fileToPush = ContainerFileInfo(path, std::string(result.cFileName), fileSize, dir, -1, -1, -1, -1, -1);
		}
		listToReturn.push_back(fileToPush);
	}while(FindNextFileA(searchHandle, &result) != 0); //search whole dir
	return listToReturn;
}