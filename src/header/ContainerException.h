#pragma once
#include <string>

namespace FtpClient {
    class ContainerException;
}
namespace FtpClient {
	enum ExceptionLevel {
		EXCEPTIONLEVEL_STANDARD = 0,
		EXCEPTIONLEVEL_HIGH = 1,
		EXCEPTIONLEVEL_CRITICAL = 2
	};

	enum ExceptionCode {
		ERROR_DIRECTORY_LISTING = 000000
	};
}


class FtpClient::ContainerException{
private:
	std::string message;
	ExceptionLevel level;
	ExceptionCode code;
public:
	ContainerException(std::string message, ExceptionLevel level, ExceptionCode code) {
		this->message = message;
		this->level = level;
		this->code = code;
	};
	virtual ~ContainerException(void){};
};





