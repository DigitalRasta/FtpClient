#include "../header/ControlExceptionManager.h"
#include "../header/ViewGuiBuilderInterface.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"

using namespace FtpClient;

ControlExceptionManager::ControlExceptionManager(ViewGuiBuilderInterface* viewGuiBuilderObject, InnerConfig* cfg){
	this->viewGuiBuilderObject = viewGuiBuilderObject;
	this->innerConfigObject = cfg;
}

void ControlExceptionManager::manageException(ContainerException &e) {
	switch(e.level) {
	case ExceptionLevel::EXCEPTIONLEVEL_STANDARD :
		switch(e.code) {
		case ExceptionCode::ERROR_DIRECTORY_LISTING :
			this->viewGuiBuilderObject->spawnExceptionWindow(e.message + "\n" + this->innerConfigObject->exception_directoryListing_inaccessible, e.level);
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_CONNECT_FAILED :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_ACCOUNT_NA :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_BAD_HOSTNAME :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_CONNECT_FAILED_UNKNOWN :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_INVALID_RESPONSE :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_NO_RESPONSE :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_PASS_NA :
			//TODO
			break;
		case ExceptionCode::EXCEPTION_CONNECTION_USER_NA :
			//TODO
			break;
		}
	break;
	case ExceptionLevel::EXCEPTIONLEVEL_HIGH :
		switch(e.code) {
		case ExceptionCode::EXCEPTION_CONNECTION_TOO_MANY :
			//TODO
			break;
		}
	break;
	case ExceptionLevel::EXCEPTIONLEVEL_CRITICAL :

	break;

	}
}


ControlExceptionManager::~ControlExceptionManager(void)
{
}
