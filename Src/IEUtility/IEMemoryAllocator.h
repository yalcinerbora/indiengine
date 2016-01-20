/**

*/

#ifndef __IE_MEMORYALLOCATOR_H__
#define __IE_MEMORYALLOCATOR_H__

#include <cstdint>

struct Mem
{
	size_t		size;
	uint8_t*	memory;
};

class IEMemoryAllocatorBasicI
{
	public:
	virtual Mem		Allocate(size_t size) = 0;
	virtual void	Reallocate(Mem&, size_t size) = 0;
	virtual void	Deallocate(Mem) = 0;					
};

class IEMemoryAllocatorI : public IEMemoryAllocatorBasicI
{
	public:
	virtual Mem		AllocateAll() = 0;
	virtual Mem		AllocateAligned(size_t size, uint32_t alignment) = 0;
	virtual Mem		ReallocateAligned(Mem&, size_t size, uint32_t alignment) = 0;
	virtual void	DeallocateAll() = 0;

	virtual bool	Owns(Mem) = 0;
};
#endif //__IE_BITMANIPULATION_H__