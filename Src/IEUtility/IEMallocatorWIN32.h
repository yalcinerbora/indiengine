
/**

*/

#ifndef __IE_MALLOCATORWIN32_H__
#define __IE_MALLOCATORWIN32_H__

#include "IEMemoryAllocator.h"
#include "IESystemDefinitions.h"
#include <windows.h>

class IEMallocatorWIN32 : public IEMemoryAllocatorBasicI
{
	public:
	Mem		Allocate(size_t size) override;
	void	Reallocate(Mem&, size_t size) override;
	void	Deallocate(Mem) override;
};

Mem IEMallocatorWIN32::Allocate(size_t size)
{
	VirtualAlloc();
	return;
}

void IEMallocatorWIN32::Reallocate(Mem& m, size_t size)
{
	VirtualAlloc();
	
}

void IEMallocatorWIN32::Deallocate(Mem m)
{
	VirtualAlloc();
}
#endif //__IE_MALLOCATORWIN32_H__
