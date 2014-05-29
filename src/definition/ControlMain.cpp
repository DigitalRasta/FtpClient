#include "../header/ControlMain.h"
#include "../header/ModelDAOInterface.h"
#include "../header/ViewGuiBuilderInterface.h"
#include "../header/ContainerException.h"
#include "../header/ContainerFileInfo.h"
#include "../header/InnerConfig.h"


#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <future>
using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject), exceptionManagerObject(viewGuiBuilderObject, innerConfigObject){
	this->localFilesList = NULL;
	this->transferEnd = false;
	this->programEnd = false;
}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
	this->viewGuiBuilderObject->bindMainWindowEvents(this);
	this->initLocalBrowser("F:/test");
	try {
		this->modelDAOObject->createNewConnection("ftp-bujnyj.ogicom.pl", "21", "ftpclienttest.bujnyj", "Test1234");
	} catch (ContainerException &e) {
		this->viewGuiBuilderObject->spawnExceptionWindow("Error", e.level);
	}
	try {
		std::list<ContainerFileInfo>* filesList = this->modelDAOObject->serverGetDirectoryContent("/");
		this->serverFilesList = filesList;
		this->viewGuiBuilderObject->showListInServerTree(filesList);
		//this->viewGuiBuilderObject->showListInLocalTree();
	} catch (ContainerException &e) {
		this->viewGuiBuilderObject->spawnExceptionWindow("Error2", e.level);
	}
	//this->viewGuiBuilderObject->spawnExceptionWindow("ERROR!", ExceptionLevel::EXCEPTIONLEVEL_CRITICAL);
	//this->viewGuiBuilderObject->spawnConnectWindow();

}


void ControlMain::initLocalBrowser(std::string startPath) {
	if(startPath.compare("/") == 0 || startPath.compare("\\") == 0 || startPath.compare(" ") == 0 ) {
		this->localFilesList = this->modelDAOObject->getLogicalDrives();
	} else {
		this->localFilesList = this->modelDAOObject->getDirectoryContent(startPath);
	}
	this->viewGuiBuilderObject->showListInLocalTree(this->localFilesList);
}



void ControlMain::connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) {

}

void ControlMain::localTreeCellDoubleClick(std::string name) {
	if(name.compare("..") == 0) {
		ContainerFileInfo fileObject = (*this->localFilesList).front();
		if(this->modelDAOObject->isPathLogicalPartition(fileObject.filePath)) {
			this->localFilesList = this->modelDAOObject->getLogicalDrives();
		} else {

			try {
				this->localFilesList = this->modelDAOObject->getDirectoryContent(this->modelDAOObject->goUpInDirPath(fileObject.filePath));
			} catch (ContainerException &e) {
				this->exceptionManagerObject.manageException(e);
			}
		}
	} else {
		ContainerFileInfo fileObject = (*this->localFilesList).front();
		for (std::list<ContainerFileInfo>::iterator it=(*this->localFilesList).begin(); it != (*this->localFilesList).end(); ++it){
			if(it->fileName.compare(name) == 0) {
				fileObject = *it;
				break;
			}
		}
		if(fileObject.isDir) {
			if(fileObject.filePath.size() == 2) {
				try {
					this->localFilesList = this->modelDAOObject->getDirectoryContent(fileObject.filePath);
				} catch (ContainerException &e) {
					this->exceptionManagerObject.manageException(e);
				}
			} else {
				try {
					this->localFilesList = this->modelDAOObject->getDirectoryContent((fileObject.filePath + fileObject.fileName));
				} catch (ContainerException &e) {
					this->exceptionManagerObject.manageException(e);
				}
			}
		} else {
			//TODO
		}

	}
	this->localFilesList = this->modelDAOObject->orderFilesListDirecrotiesFiles(this->localFilesList);
	this->viewGuiBuilderObject->showListInLocalTree(this->localFilesList);
}


void ControlMain::serverTreeCellDoubleClick(std::string name) {
	if(name.compare("..") == 0) {
		ContainerFileInfo fileObject = (*this->serverFilesList).front();
		try {
			this->serverFilesList = this->modelDAOObject->serverGetDirectoryContent(this->modelDAOObject->goUpInDirPath(fileObject.filePath));
		} catch (ContainerException &e) {
			this->exceptionManagerObject.manageException(e);
		}
	} else {
		ContainerFileInfo fileObject = (*this->serverFilesList).front();
		for (std::list<ContainerFileInfo>::iterator it=(*this->serverFilesList).begin(); it != (*this->serverFilesList).end(); ++it){
			if(it->fileName.compare(name) == 0) {
				fileObject = *it;
				break;
			}
		}
		if(fileObject.isDir) {
			try {
				this->serverFilesList = this->modelDAOObject->serverGetDirectoryContent((fileObject.filePath + fileObject.fileName + "/"));
			} catch (ContainerException &e) {
				this->exceptionManagerObject.manageException(e);
			}
		} else {
			//TODO
		}

	}
	this->viewGuiBuilderObject->showListInServerTree(this->serverFilesList);
}


void ControlMain::serverDeleteButton(ContainerFileInfo* file) {
	if(this->viewGuiBuilderObject->spawnAreYouSureWindow()) {
		if(this->modelDAOObject->deleteServerFile(file)) {
			this->refreshServerTree(file->filePath);
			this->viewGuiBuilderObject->deactivateDownloadButton();
		} else {
			if(file->isDir) {
				this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotDeleteDirectory, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			} else {
				this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotDeleteFile, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			}
		}
	}
}

void ControlMain::localDeleteButton(ContainerFileInfo* file) {
	if(this->viewGuiBuilderObject->spawnAreYouSureWindow()) {
		if(this->modelDAOObject->deleteLocalFile(file)) {
			this->refreshLocalTree(file->filePath);
		} else {
			if(file->isDir) {
				this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotDeleteDirectory, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			} else {
				this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotDeleteFile, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			}
		}
	}
}

void ControlMain::localNewFolderButton() {
	std::string name = this->viewGuiBuilderObject->spawnInsertNameWindow();
	for(int i = 0; i < name.size(); i++) {
		if(name[i] < 0) {
			this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_specialCharsNotSupported, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			return;
		}
	}
	bool flag = this->modelDAOObject->newFolderLocal(this->localFilesList->front().filePath+name);
	if(flag) {
		this->refreshLocalTree(this->localFilesList->front().filePath);
	} else {
		this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotCreateDirectory, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
	}
}

void ControlMain::serverNewFolderButton() {
	std::string name = this->viewGuiBuilderObject->spawnInsertNameWindow();
	for(int i = 0; i < name.size(); i++) {
		if(name[i] < 0) {
			this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_specialCharsNotSupported, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
			return;
		}
	}
	bool flag = this->modelDAOObject->newFolderServer(this->serverFilesList->front().filePath+name);
	if(flag) {
		this->refreshServerTree(this->serverFilesList->front().filePath);
	} else {
		this->viewGuiBuilderObject->spawnExceptionWindow(this->innerConfigObject->exception_cannotCreateDirectory, ExceptionLevel::EXCEPTIONLEVEL_STANDARD);
	}
}

void ControlMain::refreshLocalTree(std::string path) {
	try {
		this->localFilesList = this->modelDAOObject->getDirectoryContent(path);
	} catch (ContainerException &e) {
		this->exceptionManagerObject.manageException(e);
	}
	this->localFilesList = this->modelDAOObject->orderFilesListDirecrotiesFiles(this->localFilesList);
	this->viewGuiBuilderObject->showListInLocalTree(this->localFilesList);
}

void ControlMain::refreshServerTree(std::string path) {
	try {
		this->serverFilesList = this->modelDAOObject->serverGetDirectoryContent(path);
		
	} catch (ContainerException &e) {
		this->exceptionManagerObject.manageException(e);
	}
	this->serverFilesList = this->modelDAOObject->orderFilesListDirecrotiesFiles(this->serverFilesList);
	this->viewGuiBuilderObject->showListInServerTree(this->serverFilesList);
}

void ControlMain::downloadButton(ContainerFileInfo* fileServer) {
	this->downloadOrUpload = true;
	this->viewGuiBuilderObject->spawnProgressBar(true);
	this->lastFileTransfer = fileServer;
	std::function<void(double)> progressCallback = this->viewGuiBuilderObject->getProgressBarCallback();
	try {
		this->modelDAOObject->downloadFile(fileServer->filePath, this->localFilesList->front().filePath, fileServer->fileName, fileServer->fileSize, progressCallback, std::bind(&ControlMain::endTransferCallback, this, std::placeholders::_1));
	} catch (ContainerException &e) {
		this->viewGuiBuilderObject->endTransfer();
		this->exceptionManagerObject.manageException(e);
	}
}

void ControlMain::endTransferCallback(int param) {
	this->lastTransferCode = param;
	this->transferEnd = true;
}

void ControlMain::checkTransferEnd() {
	this->viewGuiBuilderObject->refreshProgressBar();
	if(this->transferEnd == true) {
		if(this->lastTransferCode != 0) {
			this->modelDAOObject->deleteLocalFile(&ContainerFileInfo(this->localFilesList->front().filePath, this->lastFileTransfer->fileName, 0));
			this->exceptionManagerObject.manageException(ContainerException(ExceptionLevel::EXCEPTIONLEVEL_HIGH, (ExceptionCode)this->lastTransferCode));
		}
		this->refreshLocalTree(this->localFilesList->front().filePath);
		this->transferEnd = false;
		this->viewGuiBuilderObject->endTransfer();
	}
}

bool ControlMain::checkProgramEnd() {
	return this->programEnd;
}

void ControlMain::cancelDownload() {
	try {
		this->modelDAOObject->killTransferThread();
	} catch (ContainerException &e) {
		this->exceptionManagerObject.manageException(e);
	}
	ContainerFileInfo fileToDelete = ContainerFileInfo(this->localFilesList->front().filePath, this->lastFileTransfer->fileName, 0, false, -1, -1, -1, -1, -1, 0);
	this->modelDAOObject->deleteLocalFile(&fileToDelete);
	this->viewGuiBuilderObject->endTransfer();
}

void ControlMain::cancelUpload() {
	try {
		this->modelDAOObject->killTransferThread();
	} catch (ContainerException &e) {
		this->exceptionManagerObject.manageException(e);
	}
	//ContainerFileInfo fileToDelete = ContainerFileInfo(this->localFilesList->front().filePath, this->lastFileTransfer->fileName, 0, false, -1, -1, -1, -1, -1, 0);
	//this->modelDAOObject->deleteLocalFile(&fileToDelete);
	this->viewGuiBuilderObject->endTransfer();
}

void ControlMain::uploadButton(ContainerFileInfo* fileLocal) {
	this->downloadOrUpload = false;
	this->viewGuiBuilderObject->spawnProgressBar(false);
	this->lastFileTransfer = fileLocal;
	std::function<void(double)> progressCallback = this->viewGuiBuilderObject->getProgressBarCallback();
	try {
		this->modelDAOObject->uploadFile(this->serverFilesList->front().filePath, fileLocal->filePath, fileLocal->fileName, fileLocal->fileSize, progressCallback, std::bind(&ControlMain::endTransferCallback, this, std::placeholders::_1));
	} catch (ContainerException &e) {
		this->viewGuiBuilderObject->endTransfer();
		this->exceptionManagerObject.manageException(e);
	}
}

void ControlMain::endProgram() {
	this->programEnd = true;
}

ControlMain::~ControlMain(void){
}
