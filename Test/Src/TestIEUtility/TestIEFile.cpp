#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEFile.h"
#include "IEUtility/IEStackString.h"

TEST(IEFile, FileOpening)
{
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	static constexpr char* noFilePath = "./TestIEFile Files/textSimpleWrong.txt";
	static constexpr char* syntaxWrongPath = "./TestIEFile Files/text<~~SimpleWrong.txt";
	static constexpr char* openFilePath = "./TestIEFile Files/openFile.txt";
	IEFile f;

	// Open File
	// Access Tag
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(correctPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	EXPECT_EQ(IEFileErrorType::ALREADY_OPENED_A_FILE,
			  f.Open(correctPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Check Some Errors
	// Wrong Path Syntax or something related to path
	// Linux Filesystem is flexible (no way to define wrong syntax)
	if(IE_CURRENT_PLATFORM == IEPlatformType::WINDOWS)
	{
		EXPECT_EQ(IEFileErrorType::PATH_SYNTAX_ERROR,
				  f.Open(syntaxWrongPath,
				  IEFileActionType::ACCESS,
				  IEFileAccessType::READ,
				  IEFileShareType::CONSERVATIVE));
	}

	// You are trying to open not existing file
	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS,
			  f.Open(noFilePath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	// You are creating a file while there is a file exists at that path
	EXPECT_EQ(IEFileErrorType::FILE_EXISTS,
			  f.Open(correctPath,
			  IEFileActionType::CREATE,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));

	// You are overwritng a file while there is not a file exists at that path
	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS,
			  f.Open(noFilePath,
			  IEFileActionType::OVERWRITE,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));

	// Always create the file even if there is a file
	// This should return ok unless there is not any syntax errors or permission errors
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(noFilePath,
			  IEFileActionType::CREATE_FORCE,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Always open the file even if there is no file at that path
	// In this case create a file
	// This should return ok unless there is not any syntax errors or permission errors
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(openFilePath,
			  IEFileActionType::ACCESS_CREATE,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Also We will test delete to make sure are created files does not
	// iterfere with the re-run of this test case
	// More Extensive Test will be done on later cases
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Delete(noFilePath));
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Delete(openFilePath));
}

TEST(IEFile, FileOpeningReadWrite)
{
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	static constexpr char* noFilePath = "./TestIEFile Files/asdsadadasd.txt";
	IEFile f;

	EXPECT_EQ(IEFileErrorType::CANT_READ_NEW_FILE,
			  f.Open(noFilePath,
			  IEFileActionType::CREATE,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	// You are overwritng a file while there is not a file exists at that path
	EXPECT_EQ(IEFileErrorType::CANT_READ_NEW_FILE,
			  f.Open(correctPath,
			  IEFileActionType::OVERWRITE,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	// Always create the file even if there is a file
	// This should return ok unless there is not any syntax errors or permission errors
	EXPECT_EQ(IEFileErrorType::CANT_READ_NEW_FILE,
			  f.Open(correctPath,
			  IEFileActionType::CREATE_FORCE,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));
}

TEST(IEFile, Delete)
{
	static constexpr char* noFilePath = "./TestIEFile Files/asdsadadasd.txt";
	static constexpr char* correctPath = "./TestIEFile Files/deleteFile.txt";
	static constexpr char* syntaxPath = "./TestIEFile Files/<<deleteFile.txt";

	// Create the correctPath (so that it becomes correct path)
	IEFile f;
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(correctPath,
			  IEFileActionType::CREATE_FORCE,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS,
			  IEFile::Delete(noFilePath));

	// Linux Filesystem is flexible (no way to define wrong syntax)
	if(IE_CURRENT_PLATFORM == IEPlatformType::WINDOWS)
	{
		EXPECT_EQ(IEFileErrorType::PATH_SYNTAX_ERROR,
				  IEFile::Delete(syntaxPath));
	}

	EXPECT_EQ(IEFileErrorType::OK,
			  IEFile::Delete(correctPath));
}

TEST(IEFile, Move)
{
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	static constexpr char* correctPath2 = "./TestIEFile Files/textSimple2.txt";
	static constexpr char* newPath = "./TestIEFile Files/textSimple0000.txt";
	static constexpr char* newPath2 = "./TestIEFile Files/textSimple000111.txt";

	//**************************************************************//
	// gtest does not like this on its EXPECT_EQ Macro so its seperate
	//**************************************************************//

	// Move Normal
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Move(newPath, correctPath));
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Move(correctPath, newPath));

	// Error Check
	// Move Not Avail File
	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS, IEFile::Move(newPath, newPath2));

	// Move Avail File to an existing location
	EXPECT_EQ(IEFileErrorType::FILE_EXISTS, IEFile::Move(correctPath, correctPath2));
}

TEST(IEFile, Copy)
{
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	static constexpr char* correctPath2 = "./TestIEFile Files/textSimple2.txt";
	static constexpr char* newPath = "./TestIEFile Files/textSimple0000.txt";
	static constexpr char* newPath2 = "./TestIEFile Files/textSimple000111.txt";
	static constexpr char* newPath3 = "./TestIEFile Files/textSimple0001112.txt";

	//**************************************************************//
	// gtest does not like this on its EXPECT_EQ Macro so its seperate
	//**************************************************************//

	// Copy Normal
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Copy(newPath3, correctPath));

	// Error Check
	// Copy Not Avail File
	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS, IEFile::Copy(newPath, newPath2));

	// Copy Avail File to an existing location
	EXPECT_EQ(IEFileErrorType::FILE_EXISTS, IEFile::Copy(correctPath, correctPath2));

	// Clean up
	EXPECT_EQ(IEFileErrorType::OK,
			  IEFile::Delete(newPath3));
}

TEST(IEFile, ReadRest)
{
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	IEFile f;

	// Read Rest Test
	// Open File
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(correctPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	// Equavilent to ReadAll
	IEStackString<256> string;
	EXPECT_EQ(IEFileErrorType::OK,
			  f.ReadRest(reinterpret_cast<uint8_t*>(string.Edit()), string.MaxLength()));
	string.LengthAfterEdit(static_cast<int>(f.getFileSize()));
	string.LineEndingAfterEdit();

	EXPECT_STREQ("this is a simple text with no line endings", string.Data());
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Read Some then Read Rest
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(correctPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	IEStackString<64> stringShort;
	uint32_t amount;

	// Read First 5 Chars
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Read(reinterpret_cast<uint8_t*>(stringShort.Edit()), amount, 5));
	EXPECT_EQ(5, amount);
	stringShort.LengthAfterEdit(static_cast<int>(amount));
	stringShort.LineEndingAfterEdit();

	// Now Read Rest
	EXPECT_EQ(IEFileErrorType::OK,
			  f.ReadRest(reinterpret_cast<uint8_t*>(string.Edit()), string.MaxLength()));
	string.LengthAfterEdit(static_cast<int>(f.getFileSize() - amount));
	string.LineEndingAfterEdit();
	
	EXPECT_STREQ("is a simple text with no line endings", string.Data());
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Consume Test
	EXPECT_EQ(IEFileErrorType::OK,
			  IEFile::ReadAll(reinterpret_cast<uint8_t*>(string.Edit()), string.MaxLength(),
			  correctPath, IEFileShareType::CONSERVATIVE));
	string.LengthAfterEdit(static_cast<int>(f.getFileSize()));
	string.LineEndingAfterEdit();
	EXPECT_STREQ("this is a simple text with no line endings", string.Data());
}

TEST(IEFile, Read)
{
	// Path and File
	static constexpr char* correctPath = "./TestIEFile Files/textSimple.txt";
	IEFile f;

	// Read All Test
	// Open File
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(correctPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	uint8_t string[256];
	uint32_t bytesRead;
	uint32_t totalRead = 0;

	// Read One by One
	while(!f.isEOFReached())
	{
		EXPECT_EQ(IEFileErrorType::OK, f.Read(string + totalRead, bytesRead, 1));
		totalRead += bytesRead;
	}
	string[totalRead] = '\0';
	EXPECT_STREQ("this is a simple text with no line endings",
				 reinterpret_cast<char*>(string));
	EXPECT_EQ(IEFileErrorType::OK, f.Close());
	// All Done!
}

TEST(IEFile, Write)
{
	static const char testString[] = "Writing this text to file no line endings";
	static constexpr char* path = "./TestIEFile Files/writeFile.txt";
	IEFile f;

	// Open a file for writing
	// Read All Test
	// Open File
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(path,
			  IEFileActionType::CREATE,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));


	// Write the string byte by byte
	uint32_t actualamount;
	for(int i = 0; testString[i] != '\0'; i++)
	{
		EXPECT_EQ(IEFileErrorType::OK,
				  f.Write(actualamount, reinterpret_cast<const uint8_t*>(testString + i), 1));
	}
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Read the file back
	char buffer[256] = {};
	EXPECT_EQ(IEFileErrorType::OK,
			  IEFile::ReadAll(reinterpret_cast<uint8_t*>(buffer), 256,
			  path, IEFileShareType::CONSERVATIVE));

	// Compare
	EXPECT_STREQ(testString, buffer);
	EXPECT_EQ(IEFileErrorType::OK, IEFile::Delete(path));
}

TEST(IEFile, PermissionErrorCheck)
{
	static constexpr char* path = "./TestIEFile Files/textSimple.txt";
	static constexpr char* readOnlyPath = "./TestIEFile Files/readOnlyFile.txt";
	IEFile f, f2, f3;

	// Open the file with only share read mode
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(path,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::SHARED_READ));	// Ppl can read along with me

	// Open file with shared read mode again check if its ok
	EXPECT_EQ(IEFileErrorType::OK,
			  f2.Open(path,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::SHARED_READ));	// second handle doing its work

	EXPECT_EQ(IEFileErrorType::PERMISSION_ERROR,
			  f3.Open(path,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));	// third handle try to hold all permissions
	// which fails
	// Close the files
	EXPECT_EQ(IEFileErrorType::OK, f.Close());
	EXPECT_EQ(IEFileErrorType::OK, f2.Close());

	// Try to write read only file
	EXPECT_EQ(IEFileErrorType::PERMISSION_ERROR,
			  f.Open(readOnlyPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::WRITE,
			  IEFileShareType::CONSERVATIVE));
}

TEST(IEFile, FileSizeExistance)
{
	uint32_t textSimpleSize = 42; // byte
	static constexpr char* existsPath = "./TestIEFile Files/textSimple.txt";
	static constexpr char* notExistPath = "./TestIEFile Files/nonExistFile.txt";
	IEFile f;

	// File Size Check
	EXPECT_EQ(IEFileErrorType::OK,
			  f.Open(existsPath,
			  IEFileActionType::ACCESS,
			  IEFileAccessType::READ,
			  IEFileShareType::CONSERVATIVE));

	EXPECT_EQ(textSimpleSize, f.getFileSize());
	EXPECT_EQ(IEFileErrorType::OK, f.Close());

	// Existance Function Check
	EXPECT_EQ(IEFileErrorType::FILE_EXISTS, IEFile::FileExists(existsPath));
	EXPECT_EQ(IEFileErrorType::FILE_NOT_EXISTS, IEFile::FileExists(notExistPath));
}