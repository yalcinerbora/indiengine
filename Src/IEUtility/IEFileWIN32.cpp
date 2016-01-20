// WIN32 API Implementation of IE File Class
// API Required Portions of the code is here
#include "IEFile.h"
#include "IEMacros.h"
#include "IEMath.h"
#include <windows.h>
#include <limits>

static IEFileErrorType Win32ErrorToIE(DWORD r)
{
	switch(r)
	{
		case ERROR_FILE_NOT_FOUND:
			return IEFileErrorType::FILE_NOT_EXISTS;
			break;

		case ERROR_ALREADY_EXISTS:
		case ERROR_FILE_EXISTS:
			return IEFileErrorType::FILE_EXISTS;
			break;

		case ERROR_SHARING_VIOLATION:
		case ERROR_LOCK_VIOLATION:
		case ERROR_ACCESS_DENIED:
		case ERROR_FILE_READ_ONLY:
			return IEFileErrorType::PERMISSION_ERROR;
			break;

			// File Path Syntax Errors (You provide unrecognized charater etc..)
		case ERROR_PATH_NOT_FOUND:
		case ERROR_INVALID_NAME:
		case ERROR_META_EXPANSION_TOO_LONG:
			return IEFileErrorType::PATH_SYNTAX_ERROR;
			break;

		default:
			IE_ERROR("Platform Windows Error Code For Fatal Error : %d", r);
			return IEFileErrorType::FATAL_ERROR;
			break;
	}

}

static DWORD IEActionTypeToWin32(IEFileActionType type)
{
	static DWORD values[] = {CREATE_NEW, TRUNCATE_EXISTING, CREATE_ALWAYS,
		OPEN_EXISTING, OPEN_ALWAYS};
	return values[static_cast<int>(type)];
}

static DWORD IEAccessTypeToWin32(IEFileAccessType type)
{
	static DWORD values[] = {GENERIC_READ, GENERIC_WRITE,
		GENERIC_READ | GENERIC_WRITE};
	return values[static_cast<int>(type)];
}

static DWORD IEHintTypeToWin32(IEFileAccessHintType type)
{
	static DWORD values[] = {FILE_FLAG_SEQUENTIAL_SCAN, FILE_FLAG_RANDOM_ACCESS};
	return values[static_cast<int>(type)];
}

static DWORD IEShareTypeToWin32(IEFileShareType type)
{
	static DWORD values[] = {0, FILE_SHARE_READ, FILE_SHARE_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE};
	return values[static_cast<int>(type)];
}

// Platform Specific
// File Access
IEFileErrorType IEFile::Open(const char* path,
							 IEFileActionType action,
							 IEFileAccessType access,
							 IEFileShareType share,
							 IEFileAccessHintType hint)
{
	if(fileOpened)
		return IEFileErrorType::ALREADY_OPENED_A_FILE;

	// Logical Errors That can be related
	if(access == IEFileAccessType::READ &&
	   (action == IEFileActionType::OVERWRITE ||
	   action == IEFileActionType::CREATE_FORCE ||
	   action == IEFileActionType::CREATE))
	{
		return IEFileErrorType::CANT_READ_NEW_FILE;
	}

	handle = CreateFile(path,
						IEAccessTypeToWin32(access),
						IEShareTypeToWin32(share),
						0,
						IEActionTypeToWin32(action),
						IEHintTypeToWin32(hint),
						0);

	// Check Handle
	if(handle == INVALID_HANDLE_VALUE)
	{
		return Win32ErrorToIE(GetLastError());
	}

	// All Good Continue
	// Get File Info for file size
	FILE_STANDARD_INFO fileInfo;
	if(!GetFileInformationByHandleEx(handle, FileStandardInfo, &fileInfo, sizeof(fileInfo)))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}

	// Populate Properties of the Class
	fileOpened = true;
	fileSize = fileInfo.EndOfFile.QuadPart;
	relativePtrLocation = 0;
	if(fileSize != 0) eofReached = false;

	// Cool We opened the file! (with proper error representation)
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Close()
{
	if(fileOpened)
	{
		if(!CloseHandle(handle))
		{
			// Error found interperet the error
			return Win32ErrorToIE(GetLastError());
		}
		fileOpened = false;
		eofReached = true;
	}
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Read(uint8_t buffer[], uint32_t& actualAmount, uint32_t requestedAmount)
{
	if(!ReadFile(handle, buffer,
		requestedAmount,
		reinterpret_cast<LPDWORD>(&actualAmount),
		nullptr))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}
	if(actualAmount == 0)
	{
		eofReached = true;
	}
	relativePtrLocation += actualAmount;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::ReadRest(uint8_t buffer[], size_t bufferSize)
{
	// Load it with 2^32 chunks (4GB Chunks)
	// for 64 bit support (win32 api read at most 32bit chunks)
	DWORD actualWritten = 0;
	uint8_t* bufferSegment = buffer;
	size_t remainingFile = fileSize - relativePtrLocation;

	if(bufferSize < remainingFile)
	{
		return IEFileErrorType::READ_BUFFER_TOO_SMALL;
	}

	uint32_t readAmount;
	do
	{
		readAmount = static_cast<uint32_t>(IEMath::Min<size_t>(remainingFile, std::numeric_limits<uint32_t>::max()));

		// Do Read
		if(!ReadFile(handle, bufferSegment,
			readAmount, &actualWritten, nullptr))
		{
			// Error found interperet the error
			return Win32ErrorToIE(GetLastError());
		}
		remainingFile -= actualWritten;
		bufferSegment += actualWritten;
	}
	while(remainingFile != 0);

	eofReached = true;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Write(uint32_t& actualAmount, const uint8_t buffer[], uint32_t requestedAmount)
{
	if(!WriteFile(handle, buffer, requestedAmount, reinterpret_cast<LPDWORD>(&actualAmount), nullptr))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}
	relativePtrLocation += actualAmount;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Delete(const char* path)
{
	if(!DeleteFile(path))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Copy(const char* newFile, const char* existingFile)
{
	if(!CopyFile(existingFile, newFile, true))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}
	return IEFileErrorType::OK;
}

IEFileErrorType	IEFile::Move(const char* newFile, const char* existingFile)
{
	if(!MoveFileEx(existingFile, newFile,
		MOVEFILE_WRITE_THROUGH))
	{
		// Error found interperet the error
		return Win32ErrorToIE(GetLastError());
	}
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::FileExists(const char* path)
{
	if(GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES)
	{
		return Win32ErrorToIE(GetLastError());
	}
	return IEFileErrorType::FILE_EXISTS;
}

