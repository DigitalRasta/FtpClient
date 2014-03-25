#pragma once
#include "ModelConnectionInterface.h"

namespace FtpClient {
    class ModelConnection;
}
class FtpClient::ModelConnection :
	public FtpClient::ModelConnectionInterface
{
public:
	ModelConnection(void);
	virtual ~ModelConnection(void);
};

