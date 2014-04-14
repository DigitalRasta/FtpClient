#include <header\InnerConfig.h>
#include <header\ModelDAO.h>
#include <header\ContainerFileInfo.h>
#include <header\ContainerException.h>
#include <definition\ModelDAO.cpp>
#include <vector>
#include <string>
#include "CppUnitTest.h"
#include <iostream>
#include <list>
#include <stdint.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace FtpClient;
using namespace std;
namespace UnitTest
{
	TEST_CLASS(TestModelDAO) {
		private:
		public:
			static InnerConfig* cfgObject;
			static ModelDAO* modelObject;

			TEST_METHOD(logicalDrivesConvert) {
				vector<string> result = modelObject->convertLogicalDrives(12);
				Assert::AreEqual(string("C"), result[0],  false);
				Assert::AreEqual(string("D"), result[1],  false);
				result = modelObject->convertLogicalDrives(0);
				Assert::IsTrue(result.empty());
				result = modelObject->convertLogicalDrives(-1);
				Assert::AreEqual(32, (int)result.size());
			};

			TEST_METHOD(getDirContentNormalWork) {
				list<ContainerFileInfo> testList = modelObject->getDirectoryContent("F:/projekty/CPP/FtpClient/UnitTest/TestDir/getDirContent/");
				ContainerFileInfo element = testList.front(); testList.pop_front();
				Assert::AreEqual(string(".."), element.fileName);
				Assert::AreEqual(true, element.isDir);
				element = testList.front(); testList.pop_front();
				Assert::AreEqual(string("dirTest"), element.fileName);
				Assert::AreEqual(26, element.day);
				Assert::AreEqual(3, element.month);
				Assert::AreEqual(2014, element.year);
				Assert::AreEqual(22, element.hour);
				Assert::AreEqual(55, element.minute);
				Assert::AreEqual((uint64_t)0, element.fileSize);
				Assert::AreEqual(true, element.isDir);
				element = testList.front(); testList.pop_front();
				Assert::AreEqual(string("fileTest.txt"), element.fileName);
				Assert::AreEqual((uint64_t)24, element.fileSize);
				Assert::AreEqual(false, element.isDir);
				element = testList.front(); testList.pop_front();
				Assert::AreEqual(string("fileTest2.txt"), element.fileName);
				Assert::AreEqual((uint64_t)1516, element.fileSize);
				Assert::AreEqual(false, element.isDir);
				Assert::IsTrue(testList.empty());
			}

			TEST_METHOD(getDirContentWrongPath) {
				bool exceptionThrowed = false;
				try{
					modelObject->getDirectoryContent("somethingreallystupid.ccsd");
				} catch(ContainerException) {
					exceptionThrowed = true;
				}
				Assert::IsTrue(exceptionThrowed);
			}

			TEST_METHOD(checkIfIsPathLogicalPartition) {
				Assert::IsFalse(modelObject->isPathLogicalPartition("F:/nooot/"));
				Assert::IsTrue(modelObject->isPathLogicalPartition("F:/"));
			}

			TEST_METHOD(goUpInDir) {
				std::string path1 = "F:/dir1/dir2/";
				Assert::AreEqual(string("F:/dir1/"), this->modelObject->goUpInDirPath(path1));
				std::string path2 = "F:/dir1/dir2";
				Assert::AreEqual(string("F:/dir1/"), this->modelObject->goUpInDirPath(path1));
			}
	};
}


InnerConfig* UnitTest::TestModelDAO::cfgObject = new InnerConfig();
ModelDAO*    UnitTest::TestModelDAO::modelObject = new ModelDAO(UnitTest::TestModelDAO::cfgObject);