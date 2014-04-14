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
		ERROR_DIRECTORY_LISTING = 0,
		EXCEPTION_CONNECTION_TOO_MANY = 1,
		EXCEPTION_CONNECTION_BAD_HOSTNAME = 2,
		EXCEPTION_CONNECTION_CONNECT_FAILED = 3,
		EXCEPTION_CONNECTION_NO_RESPONSE = 4,
		EXCEPTION_CONNECTION_INVALID_RESPONSE = 5,
		EXCEPTION_CONNECTION_USER_NA = 6,
		EXCEPTION_CONNECTION_PASS_NA = 7,
		EXCEPTION_CONNECTION_ACCOUNT_NA = 8,
		EXCEPTION_CONNECTION_CONNECT_FAILED_UNKNOWN = 9,
		ERROR_CONNECTION_UNKNOWN_ID = 10,
		EXCEPTION_CONNECTION_PORT_INVALID = 11,
		ERROR_CONNECTION_PORT_NA = 12,
		ERROR_CONNECTION_LIST_NA = 13,
		EXCEPTION_CONNECTION_LIST_ABORTED = 14,
		ERROR_CONNECTION_UNKNOWN_ERROR = 15
	};
}


class FtpClient::ContainerException{

public:
	ExceptionLevel level;
	ExceptionCode code;

	ContainerException(ExceptionLevel level, ExceptionCode code) {
		this->level = level;
		this->code = code;
	};
	virtual ~ContainerException(void){};
};





