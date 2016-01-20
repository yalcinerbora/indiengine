#include "IEFile.h"
#include <cassert>

IEFile::IEFile() : relativePtrLocation(0),
					fileOpened(false),
					fileSize(0),
					eofReached(true)
{}

IEFile::IEFile(IEFile&& mv)
	: handle(mv.handle)
	, relativePtrLocation(mv.relativePtrLocation)
	, fileOpened(mv.fileOpened)
	, fileSize(mv.fileSize)
	, eofReached(mv.eofReached)
{
	mv.fileOpened = false;
}

IEFile::~IEFile()
{
	Close();
}

IEFile& IEFile::operator=(IEFile&& mv)
{
	assert(&mv != this);
	
	handle = mv.handle;
	relativePtrLocation = mv.relativePtrLocation;
	fileOpened = mv.fileOpened;
	fileSize = mv.fileSize;
	eofReached = mv.eofReached;
	
	mv.fileOpened = false;
	return *this;
}

bool IEFile::hasFileOpened() const
{
	return fileOpened;
}

uint64_t IEFile::getFileSize() const
{
	return fileSize;
}

bool IEFile::isEOFReached() const
{
	return eofReached;
}

uint64_t IEFile::getRelativePtrLocation() const
{
	return relativePtrLocation;
}

IEFileErrorType IEFile::ReadAll(uint8_t data[], size_t arrayLength,
								   const char* path,
								   IEFileShareType share)
{
	// Open file but all the data to byte
	IEFile f;
	f.Open(path, IEFileActionType::ACCESS, IEFileAccessType::READ, share);

	if(arrayLength < f.getFileSize())
	{
		return IEFileErrorType::READ_BUFFER_TOO_SMALL;
	}
	return f.ReadRest(data, arrayLength);
}