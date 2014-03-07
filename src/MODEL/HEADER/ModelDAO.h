#pragma once
#include "ModelDAOInterface.h"
#include "../../InnerConfig.h"

namespace FtpClient {
    class ModelDAO;
}
class FtpClient::ModelDAO :
	public FtpClient::ModelDAOInterface
{
public:
	ModelDAO(InnerConfig* innerConfigObject);
	virtual ~ModelDAO(void);
private:
	InnerConfig* innerConfigObject;
};

