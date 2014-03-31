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
				Assert::AreEqual(21, element.hour);
				Assert::AreEqual(55, element.minute);
				Assert::AreEqual(0, element.fileSizeLow);
				Assert::AreEqual(true, element.isDir);
				element = testList.front(); testList.pop_front();
				Assert::AreEqual(string("fileTest.txt"), element.fileName);
				Assert::AreEqual(24, element.fileSizeLow);
				Assert::AreEqual(false, element.isDir);
				element = testList.front(); testList.pop_front();
				Assert::AreEqual(string("fileTest2.txt"), element.fileName);
				Assert::AreEqual(1516, element.fileSizeLow);
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
	};
}


InnerConfig* UnitTest::TestModelDAO::cfgObject = new InnerConfig();
ModelDAO*    UnitTest::TestModelDAO::modelObject = new ModelDAO(UnitTest::TestModelDAO::cfgObject);