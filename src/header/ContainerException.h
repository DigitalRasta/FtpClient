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
		ERROR_CONNECTION_UNKNOWN_FTP_LIST_FORMAT = 16,
		ERROR_CONNECTION_LIBCURL_FAILED_TO_CONNECT = 17,
		ERROR_CONNECTION_LIBCURL_TIMEOUT = 18,
		ERROR_CONNECTION_LIBCURL_TRANSFER_TYPE = 19,
		ERROR_CONNECTION_LIBCURL_TRANSFER_SIZE_NOT_MATCH = 20,
		ERROR_CONNECTION_LIBCURL_TRANSFER_ERROR = 21,
		ERROR_CONNECTION_LIBCURL_QUOTE_ERROR = 22,
		ERROR_CONNECTION_LIBCURL_UPLOAD_ERROR = 23,
		ERROR_CONNECTION_LIBCURL_INVALID_PORT = 24,
		ERROR_CONNECTION_LIBCURL_UNKNOWN_ERROR = 25,
		ERROR_THREAD_CANNOT_KILL = 26,
		ERROR_FILE_IO = 27,
		EXCEPTION_INVALID_PARAMS = 28
	};
}

/*
*<summary>Wrapper for exceptions</summary>
*/
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





