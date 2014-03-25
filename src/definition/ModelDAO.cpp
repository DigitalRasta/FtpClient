#include "../header/ModelDAO.h"
#include "../header/InnerConfig.h"
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace FtpClient;
using namespace std;
ModelDAO::ModelDAO(InnerConfig* innerConfigObject):innerConfigObject(innerConfigObject){
}


ModelDAO::~ModelDAO(void){
}

vector<string> ModelDAO::getLogicalDrives(void) {
	DWORD volumesList = ::GetLogicalDrives(); //Return 32 bits, if first bit = 1 it means A aviable, second = 1 means B etc.
	return this->convertLogicalDrives(volumesList);
}

vector<string> ModelDAO::convertLogicalDrives(DWORD volumesList) {
	vector<string> returnVector = vector<string>();
	for(int i = 0; i < 32; i++) {
		char letter = 'A'+i;
		unsigned int bits = 1;
		bits = bits << i;
		if((bits & volumesList) == bits) {
			stringstream strStr;
			string strToVector;
			strStr << letter;
			strStr >> strToVector;
			returnVector.push_back(strToVector);
		}
	}
	return returnVector;
}
