#pragma once

namespace FtpClient {
    class ExceptionContainer;
}
class FtpClient::ExceptionContainer
{
public:
	ExceptionContainer(void);
	virtual ~ExceptionContainer(void);
};





namespace FtpClient {
	enum ExceptionLevel {
		STANDARD = 0,
		HIGH = 1,
		CRITICAL = 2
	};

	enum ExceptionCode {

	};
}

