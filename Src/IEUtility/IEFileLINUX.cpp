// LINUX Kernel API Implementation of IE File Class
// API Required Portions of the code is here
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include "IEFile.h"

#define COPY_BUFFER_SIZE 8 * 1024

static IEFileErrorType LinuxErrorToIE(int r)
{
	switch(r)
	{
		case ENOENT:
			return IEFileErrorType::FILE_NOT_EXISTS;
			break;

		case EEXIST:
			return IEFileErrorType::FILE_EXISTS;
			break;

		case EACCES:
		case EAGAIN:
		case EROFS:
			return IEFileErrorType::PERMISSION_ERROR;
			break;

		// File Path Syntax Errors (You provide unrecognized charater etc..)
		case ENAMETOOLONG:
			return IEFileErrorType::PATH_SYNTAX_ERROR;
			break;

		default:
			IE_ERROR("Platform Linux Error Code For Fatal Error : %d", r);
			DEBUG("Error String %s \n", strerror(r));
			return IEFileErrorType::FATAL_ERROR;
			break;
	}

}

static int IEActionTypeToLinux(IEFileActionType type)
{
	static int values[] = 
	{
		O_CREAT | O_EXCL,
		O_TRUNC,
		O_CREAT,
		0,
		O_CREAT
	};
	return values[static_cast<int>(type)];
}

static int IEAccessTypeToLinux(IEFileAccessType type)
{
	static int values[] = 
	{
		O_RDONLY,
		O_WRONLY,
		O_RDWR
	};
	return values[static_cast<int>(type)];
}

static int IEHintTypeToLinux(IEFileAccessHintType type)
{

	static int values[] = 
	{
		POSIX_FADV_NORMAL, 
		POSIX_FADV_SEQUENTIAL
	};
	return values[static_cast<int>(type)];
}

static int IEShareTypeToLinux(IEFileShareType type)
{
	static int values[] =
	{
		LOCK_EX,	// Exclusive Lock
		LOCK_SH,	// Shared Lock ()
		LOCK_SH,	// Shared Lock (Linux Does not have shared write only access)
		0,			// No Lock
	};
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

	// OPEN The FILE!
	handle = open(path,
	              IEAccessTypeToLinux(access) | 
	              IEActionTypeToLinux(action),
	              S_IRWXU);

	if(handle < 0)
	{
		return LinuxErrorToIE(errno);
	}

	// POSIX Sequential Stuff
	if(int error = posix_fadvise(handle, 0, 0, IEHintTypeToLinux(hint)))
	{
		close(handle);	// Dont Check This Error, we're fucked already
		return LinuxErrorToIE(error);
	}

	// Lock the File
	int shareType = IEShareTypeToLinux(share);

	if(shareType != 0 &&
	   flock(handle, shareType | LOCK_NB) < 0)
	{
 		close(handle);
 		return LinuxErrorToIE(errno);
 	}

 	// Get File Size
 	struct stat fileStats;
 	if(fstat(handle, &fileStats) < 0)
 	{
 		return LinuxErrorToIE(errno);
 	}

 	// Populate Properties of the Class
 	fileOpened = true;
	fileSize = static_cast<IEUInt64>(fileStats.st_size);
	eofReached = false;
	relativePtrLocation = 0;

 	// All Cool
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Close()
{
	if(fileOpened &&
	   close(handle) < 0)
	{
		return LinuxErrorToIE(errno);
	}
	fileOpened = false;
	eofReached = true;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Read(IEByte buffer[], IEUInt32& actualAmount, IEUInt32 requestedAmount)
{
	int readAmount = read(handle, buffer, requestedAmount);
	if(readAmount < 0)
	{
		return LinuxErrorToIE(errno);
	}
	if(readAmount == 0)
	{
		eofReached = true;
	}
	actualAmount = readAmount;
	relativePtrLocation += actualAmount;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::ReadRest(IEByte buffer[], IESize bufferSize)
{

	ssize_t actualWritten = 0;
	IEByte* bufferSegment = buffer;
	IESize remainingFile = fileSize - relativePtrLocation;

	if(remainingFile > bufferSize)
	{
		return IEFileErrorType::READ_BUFFER_TOO_SMALL;
	}

	size_t readAmount;
	do
	{
		if(remainingFile > SSIZE_MAX)
			readAmount = SSIZE_MAX;
		else
			readAmount = static_cast<IEUInt32>(remainingFile);

		// Do Read
		actualWritten = read(handle, 
		                     bufferSegment,
		                     readAmount);
		if(actualWritten < 0)
		{
			return LinuxErrorToIE(errno);
		}
		remainingFile -= actualWritten;
		bufferSegment += actualWritten;
	}
	while(remainingFile != 0);

	eofReached = true;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Write(IEUInt32& actualAmount, const IEByte buffer[], IEUInt32 requestedAmount)
{
	int readAmount = write(handle, buffer, requestedAmount);
	if(readAmount < 0)
	{
		return LinuxErrorToIE(errno);
	}
	actualAmount = readAmount;
	relativePtrLocation += actualAmount;
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Delete(const char* path)
{
	if(remove(path) < 0)
	{
		return LinuxErrorToIE(errno);
	}
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::Copy(const char* newFile, const char* existingFile)
{
	IEFile f1, f2;

	// Use IEFile Here Linux one is kinda long
	IEFileErrorType err;

	err = f1.Open(newFile,
	              IEFileActionType::CREATE,
	              IEFileAccessType::WRITE,
	              IEFileShareType::CONSERVATIVE);
	if(err != IEFileErrorType::OK)
	{
		return err;
	}

	err = f2.Open(existingFile,
	              IEFileActionType::ACCESS,
	              IEFileAccessType::READ,
	              IEFileShareType::CONSERVATIVE);	
	if(err != IEFileErrorType::OK)
	{
		f1.Close();
		IEFile::Delete(newFile);
		return err;
	}

	// Pre allocate
	if(int errorNo = posix_fallocate(f1.handle, 0, f2.fileSize))
	{
		f1.Close();
		IEFile::Delete(newFile);
		return LinuxErrorToIE(errorNo);
	}

	// Read to buffer write to buffer
	IEByte* buffer[COPY_BUFFER_SIZE];
	ssize_t actualWritten = 0;
	size_t readAmount;
	IESize remainingFile = f2.fileSize;

	do
	{
		if(remainingFile > COPY_BUFFER_SIZE)
			readAmount = COPY_BUFFER_SIZE;
		else
			readAmount = static_cast<IEUInt32>(remainingFile);

		// Do Read
		actualWritten = read(f2.handle, 
		                     buffer, 
		                     readAmount);
		if(actualWritten < 0)
		{
			f1.Close();
			IEFile::Delete(newFile);
			return LinuxErrorToIE(errno);
		}
		remainingFile -= actualWritten;

		// Now Write
		if(write(f1.handle, buffer, actualWritten) < 0)
		{
			f1.Close();
			IEFile::Delete(newFile);
			return LinuxErrorToIE(errno);
		}
	}
	while(remainingFile != 0);
	return IEFileErrorType::OK;
}

IEFileErrorType	IEFile::Move(const char* newFile, const char* existingFile)
{
	// We Need to check existence of the newFile since linux rename overwrites
	struct stat buffer;
	if(stat(newFile, &buffer) == 0)
	{
		return IEFileErrorType::FILE_EXISTS;
	}

	// Continue
	if(rename(existingFile, newFile) < 0)
	{
		return LinuxErrorToIE(errno);
	}
	return IEFileErrorType::OK;
}

IEFileErrorType IEFile::FileExists(const char* path)
{
	struct stat buffer;
	if(stat(path, &buffer) < 0)
	{
		return LinuxErrorToIE(errno);
	}
	return IEFileErrorType::FILE_EXISTS;
}