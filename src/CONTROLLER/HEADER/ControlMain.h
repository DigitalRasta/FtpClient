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

	virtual ~ControlMain(void);
private:
	ViewGuiBuilderInterface* viewGuiBuilderObject;
	ModelDAOInterface* modelDAOObject;
	InnerConfig* innerConfigObject;
};

