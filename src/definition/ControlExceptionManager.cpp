#include "../header/ControlExceptionManager.h"
#include "../header/ViewGuiBuilderInterface.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"
#include "../header/ControlMainEventsInterface.h"

using namespace FtpClient;

ControlExceptionManager::ControlExceptionManager(ViewGuiBuilderInterface* viewGuiBuilderObject, InnerConfig* cfg, ControlMainEventsInterface* ctrl){
	this->mainControlObject = ctrl;
	this->viewGuiBuilderObject = viewGuiBuilderObject;
	this->innerConfigObject = cfg;
}

void ControlExceptionManager::manageException(ContainerException &e) {
	switch(e.code) {
		case ExceptionCode::ERROR_DIRECTORY_LISTING :
			this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_directoryListing_inaccessible, e.level);
			break;
		case ExceptionCode::ERROR_CONNECTION_UNKNOWN_FTP_LIST_FORMAT:
			this->viewGuiBuilderObject->spawnExceptionWindow("Unknown files list format from server", e.level);
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_FAILED_TO_CONNECT:
			this->viewGuiBuilderObject->spawnExceptionWindow("Connection failed. Check connection parameters.", e.level);
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_TIMEOUT:
			this->viewGuiBuilderObject->spawnExceptionWindow("Operation timeout. Please reconnect.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_TYPE:
			this->viewGuiBuilderObject->spawnExceptionWindow("Transfer problem. Please reconnect and try once again.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_SIZE_NOT_MATCH:
			this->viewGuiBuilderObject->spawnExceptionWindow("Transfer problem. Please reconnect and try once again.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_TRANSFER_ERROR:
			this->viewGuiBuilderObject->spawnExceptionWindow("Transfer problem. Please reconnect and try once again.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_QUOTE_ERROR:
			this->viewGuiBuilderObject->spawnExceptionWindow("FTP error. Working with this server problably won't be possible.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_UPLOAD_ERROR:
			this->viewGuiBuilderObject->spawnExceptionWindow("Transfer problem. Please reconnect and try once again.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_INVALID_PORT:
			this->viewGuiBuilderObject->spawnExceptionWindow("Invalid port", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_CONNECTION_LIBCURL_UNKNOWN_ERROR:
			this->viewGuiBuilderObject->spawnExceptionWindow("Cannot connect! Unknown error.", e.level);
			this->viewGuiBuilderObject->showListInServerTree(NULL);
			this->viewGuiBuilderObject->activateConnectButton();
			this->viewGuiBuilderObject->deactivateDisconnectButton();
			break;
		case ExceptionCode::ERROR_THREAD_CANNOT_KILL:
			this->viewGuiBuilderObject->spawnExceptionWindow("Fatal error! Cannot end transfer thread!", e.level);
			break;
		case ExceptionCode::ERROR_FILE_IO:
			this->viewGuiBuilderObject->spawnExceptionWindow("File write error!", e.level);
			break;
		case ExceptionCode::EXCEPTION_INVALID_PARAMS:
			this->viewGuiBuilderObject->spawnExceptionWindow("Parameters cannot be empty.", e.level);
			break;
	}
}


ControlExceptionManager::~ControlExceptionManager(void)
{
}
