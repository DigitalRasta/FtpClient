#include <header\InnerConfig.h>
#include <header\ModelDAO.h>
#include <definition\ModelDAO.cpp>
#include <vector>
#include <string>
#include "CppUnitTest.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace FtpClient;
using namespace std;
namespace UnitTest
{
	TEST_CLASS(TestModelDAO) {
		private:
		public:
			static InnerConfig* cfgObject;
			TEST_METHOD(logicalDrivesConvert) {
				InnerConfig* cfgObject = new InnerConfig();
				ModelDAO* modelObject = new ModelDAO(cfgObject);
				vector<string> result = modelObject->convertLogicalDrives(12);
				Assert::AreEqual(string("C"), result[0],  false);
				Assert::AreEqual(string("D"), result[1],  false);
				result = modelObject->convertLogicalDrives(0);
				Assert::IsTrue(result.empty());
				result = modelObject->convertLogicalDrives(-1);
				Assert::IsTrue(result.size() == 32);
			};
	};
}
