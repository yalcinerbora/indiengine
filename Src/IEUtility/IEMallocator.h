/**

*/

#ifndef __IE_MALLOCATOR_H__
#define __IE_MALLOCATOR_H__

#include <cstdlib>
#include <type_traits>
#include "IEMemoryAllocator.h"
#include "IESystemDefinitions.h"

class IEMallocator : public IEMemoryAllocatorBasicI
{
	public:
	Mem		Allocate(size_t size) override;
	void	Reallocate(Mem&, size_t size) override;
	void	Deallocate(Mem) override;
};

Mem IEMallocator::Allocate(size_t size)
{
	return{size, static_cast<uint8_t*>(std::malloc(size))};
}

void IEMallocator::Reallocate(Mem& m, size_t size)
{
	std::realloc(m.memory, size);
}

void IEMallocator::Deallocate(Mem m)
{
	std::free(m.memory);
}
#endif //__IE_MALLOCATOR_H__
