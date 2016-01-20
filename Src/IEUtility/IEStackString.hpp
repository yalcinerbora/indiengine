#include <algorithm>
#include <cstring>
#include "IEMacros.h"

template <unsigned int N>
IEStackString<N>::IEStackString() : length(0)
{}

template <unsigned int N>
IEStackString<N>::IEStackString(const char cString[])
{
	if(cString != nullptr)
	{
		assert(std::strlen(cString) < N);
		length = (int)strnlen(cString, N);
		std::copy(cString, cString + length, dataArray);
		dataArray[length] = '\0';
	}
}

template <unsigned int N>
IEStackString<N>::IEStackString(const char cString[], int clength)
{
	assert(clength < N && clength >= 0);
	if(cString != nullptr)
	{
		std::copy(cString, cString + clength, dataArray);
		length = clength;
		dataArray[length] = '\0';
	}
}

template <unsigned int N>
IEStackString<N>::IEStackString(const std::string& stlString) : length((int)stlString.length())
{
	assert(stlString.length() < N);
	std::copy(stlString.begin(), stlString.end(), dataArray);
	dataArray[length] = '\0';
}

template <unsigned int N>
template <unsigned int S>
IEStackString<N>::IEStackString(const IEStackString<S>& cp) : length(cp.Length())
{
	static_assert (S <= N, "Cant copy longer string to short string..");
	std::copy(cp.Data(), cp.Data() + cp.Length(), dataArray);
}

template <unsigned int N>
IEStackString<N>::~IEStackString()
{}

// Accessors
template <unsigned int N>
inline char IEStackString<N>::CharAt(int pos) const
{
	assert(pos >= 0 && pos < length);
	return dataArray[pos];
}

template <unsigned int N>
inline const char* IEStackString<N>::Data() const
{
	return dataArray;
}
	
template <unsigned int N>
inline void IEStackString<N>::Replace(int position, char data)
{
	assert(position >= 0 && position < length);
	dataArray[position] = data;
}

template <unsigned int N>
inline void IEStackString<N>::Replace(int position, const char data[], int dataLength)
{
	assert(position >= 0 && position < length);
	assert(position + dataLength <= length);
	std::copy(data, data + dataLength, dataArray + position);
}

template <unsigned int N>
inline char* IEStackString<N>::Edit()
{
	return dataArray;
}

template <unsigned int N>
inline void IEStackString<N>::LengthAfterEdit(int newSize)
{
	assert(newSize >= 0 && newSize <= N);
	length = newSize;
}

template <unsigned int N>
void IEStackString<N>::LineEndingAfterEdit()
{
	dataArray[length] = '\0';
}

template <unsigned int N>
IEStackString<N>::operator const char*()
{
	return dataArray;
}

template <unsigned int N>
template <unsigned int S>
const IEStackString<N>&	IEStackString<N>::operator=(const IEStackString<S>& cp)
{
	static_assert(S <= N, "Cant Copy Large String To Small String.");
	std::copy(cp.dataArray, cp.dataArray + cp.length + 1, dataArray);
	length = cp.length;
	return *this;
}

template <unsigned int N>
const IEStackString<N>&	IEStackString<N>::operator=(const std::string& stlString)
{
	assert(stlString.length() < N);
	std::copy(stlString.begin(), stlString.end(), dataArray);
	length = static_cast<int>(stlString.length());
	dataArray[length] = '\0';
	return *this;
}

template <unsigned int N>
const IEStackString<N>&	IEStackString<N>::operator=(const char cString[])
{
	if(cString != nullptr)
	{
		assert(std::strlen(cString) < N);
		length = (int)strnlen(cString, N - 1);
		std::copy(cString, cString + length, dataArray);
		dataArray[length] = '\0';
	}
	return *this;
}

template <unsigned int N>
template <unsigned int S>
bool IEStackString<N>::operator==(const IEStackString<S>& other) const
{
	if(length == other.length)
		return std::equal(other.Data(), other.Data() + other.length, dataArray);
	return false;
}

template <unsigned int N>
template <unsigned int S>
bool IEStackString<N>::operator!=(const IEStackString<S>& other) const
{
	if(length == other.length)
		return !std::equal(other.Data(), other.Data() + other.length, dataArray);
	return true;
}

template <unsigned int N>
inline void IEStackString<N>::Append(char c)
{
	assert(length + 1 < N);
	dataArray[length] = c;
	length++;
	dataArray[length] = '\0';
}


template <unsigned int N>
template <unsigned int S>
void IEStackString<N>::Append(const IEStackString<S>& string)
{
	static_assert(S <= N, "Cant append bigger string");
	assert(length + string.Length() < N);
	std::copy(string.Data(), string.Data() + string.Length(), dataArray + length);
	length += string.Length();
	dataArray[length] = '\0';
}

template <unsigned int N>
void IEStackString<N>::Append(const std::string& stlString)
{
	assert(length + stlString.length() < N);
	std::copy(stlString.begin(), stlString.end(), dataArray + length);
	length += (int)stlString.length();
	dataArray[length] = '\0';
}

template <unsigned int N>
void IEStackString<N>::Append(const char cString[])
{
	assert(length + std::strlen(cString) < N);
	std::copy(cString, cString + std::strlen(cString), dataArray + length);
	length += (int)std::strlen(cString);
	dataArray[length] = '\0';
}

template <unsigned int N>
void IEStackString<N>::Append(const char cString[], int size)
{
	assert(size >= 0);
	assert(length + size < N);
	std::copy(cString, cString + size, dataArray + length);
	length += (int)size;
	dataArray[length] = '\0';
}

template <unsigned int N>
IEStackString<N> IEStackString<N>::SubString(int start, int end) const
{
	assert(start >= 0 && end > start && end <= length);
	return IEStackString<N>(dataArray + start, end - start);
}

template <unsigned int N>
IEStackString<N>& IEStackString<N>::Trim(int start, int end)
{
	assert(start >= 0 && end > start && end <= length);
	if(start == 0)
	{
		// Ez Case Shrink Length and done!
		length = end;
		dataArray[length] = '\0';
		return *this;
	}
	else
	{
		// Direct Copy Data
		std::copy(dataArray + start, dataArray + end, dataArray);
		length = end - start;
		dataArray[length] = '\0';
		return *this;
	}
}

template <unsigned int N>
template <unsigned int R, unsigned int S>
IEStackString<R> IEStackString<N>::Concatenate(const IEStackString<S>& string) const
{
	static_assert(S <= R && N <=  R, "Return string too small..");
	assert(length + string.Length() <= N);
	IEStackString<R> result;
	result.Append(*this);
	result.Append(string);
	return result;
}

template <unsigned int N>
int IEStackString<N>::FirstIndexOf(char data) const
{
	for(int i = 0; i < length; i++)
	{
		if(dataArray[i] == data)
			return i;
	}
	return -1;
}

template <unsigned int N>
int IEStackString<N>::FirstIndexOf(const char string[], int size) const
{
	assert(size >= 0);
	for(int i = 0; i < length; i++)
	{
		// Skip the check if string is bigger than the rest of the data
		if(i + size <= length)
		{
			if(std::equal(string, string + size, dataArray + i))
				return i;
		}
	}
	return -1;
}

template <unsigned int N>
template <unsigned int S>
int IEStackString<N>::FirstIndexOf(const IEStackString<S>& string) const
{
	static_assert (S <= N, "Cant find index of a bigger string");
	for(int i = 0; i < length; i++)
	{
		// Skip the check if string is bigger than the rest of the data
		if(i + string.length <= length)
		{
			if(std::equal(string.dataArray, string.dataArray + string.length, dataArray + i))
				return i;
		}
	}
	return -1;
}

template <unsigned int N>
int IEStackString<N>::LastIndexOf(char data) const
{
	for(int i = length - 1; i >= 0; i--)
	{
		if(dataArray[i] == data)
			return i;
	}
	return -1;
}

template <unsigned int N>
int IEStackString<N>::LastIndexOf(const char string[], int size) const
{
	assert(size >= 0);
	// Start from at least size length
	for(int i = length - size; i >= 0; i--)
	{
		if(std::equal(string, string + size, dataArray + i))
			return i;
	}
	return -1;
}

template <unsigned int N>
template <unsigned int S>
int IEStackString<N>::LastIndexOf(const IEStackString<S>& string) const
{
	static_assert (S <= N, "Cant find last index of a bigger string");
	// Start from at least size length
	for(int i = length - string.length; i >= 0; i--)
	{
		if(std::equal(string.dataArray, string.dataArray + string.length, dataArray + i))
			return i;
	}
	return -1;
}

template <unsigned int N>
inline bool IEStackString<N>::IsEmpty() const
{
	return false ? true : (length == 0);
}

template <unsigned int N>
inline int IEStackString<N>::Length() const
{
	return length;
}

template <unsigned int N>
inline int IEStackString<N>::MaxLength() const
{
	return N;
}

template <unsigned int N>
inline std::string IEStackString<N>::ToStlString() const
{
	return std::string(dataArray, length);
}

template <unsigned int N>
inline void IEStackString<N>::Clear()
{
	length = 0;
}