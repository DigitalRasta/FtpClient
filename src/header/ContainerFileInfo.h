#pragma once
#include <string>
#include <stdint.h>


namespace FtpClient {
    class ContainerFileInfo;
}
/*
*<summary>Information storage for files</summary>
*/
class FtpClient::ContainerFileInfo{
public:
	std::string fileName;	     // file or directory name 
	std::string filePath;		 // path to file
	uint64_t fileSize;			 // size of file
	int  day;                    // the day digit of the file date 
	int  month;                  // the month digit of the file date 
	int  year;                   // the year digit of the file date 
	int  hour;                   // the hour digit of the file date 
	int  minute;                 // the minute digit of the file date 
	bool  isDir;                 // flag if the entry is directory or a file
	int ID;
	int attributes;				 // file attributes

	ContainerFileInfo(void) {};

	//Constructor for drive letters
	ContainerFileInfo(std::string filePath, std::string fileName, int ID) {
		this->fileName = fileName;
		this->filePath = filePath;
		this->isDir = true;

		this->fileSize = 0;
		this->day = -1;
		this->month = -1;
		this->year = -1;
		this->hour = -1;
		this->minute = -1;

		this->attributes = -1;
		this->ID = ID;
	}

	//Standard constructor
	ContainerFileInfo(std::string dirPath, std::string name, uint64_t fileSize, bool isDir, int day,
		int month, int year, int hour, int minute, int ID, int attr = -1) {
		this->fileName = name;
		this->filePath = dirPath;
		this->isDir = isDir;
		this->ID = ID;

		if(isDir) {
			this->fileSize = 0;
		} else {
			this->fileSize = fileSize;
		}
		this->day = day;
		this->month = month;
		this->year = year;
		this->hour = hour;
		this->minute = minute;

		this->attributes = attr;

	}
	virtual ~ContainerFileInfo(void){};
};
