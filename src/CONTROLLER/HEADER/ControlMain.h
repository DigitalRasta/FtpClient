#pragma once
#include "ControlMainEventsInterface.h"
#include "../../MODEL/HEADER/ModelDAOInterface.h"
#include "../../VIEW/HEADER/ViewGuiBuilderInterface.h"
#include "../../InnerConfig.h"

namespace FtpClient {
    class ControlMain;
}
class FtpClient::ControlMain :
	public FtpClient::ControlMainEventsInterface
{
public:
	ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject);

	void startFtpClient(void);

	/*
	*Interface
	*/
	virtual void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password);

	virtual ~ControlMain(void);
private:
	ViewGuiBuilderInterface* viewGuiBuilderObject;
	ModelDAOInterface* modelDAOObject;
	InnerConfig* innerConfigObject;
};

