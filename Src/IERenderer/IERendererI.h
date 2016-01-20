/**

Main Rendering Interface of the DLL

Multithreaded all of its interface is 
fire and forget style (in order to make it multi threaded)

Has interfaces to read directly from files, or from arrays
every dynamic memory once its

*/

#ifndef __IE_RENDERERI_H__
#define __IE_RENDERERI_H__

#include <cstdint>

// ObjectAlias will alias series of object

// Object Interface
// Object is pool of DrawPoints that modeled as same object (basically this means nothing)
// Object has an AABB (modelSpace),
// Multiple LOD (for each DrawPoint)
// Objects can be marked as static, dynamic
class IEObjectI;

// Objects have at leas one draw call (it can be zero but then you might as well remove the object from GPU)
// Draw call holds transform(transforms) of that particular draw call (and Draw Points implicitly)
class DrawCallI;

// Material Interface
// Holds the shader and texture, uniform information of a certain
// Material.
class IEMaterialI;

// Draw Point Interface
// DrawPoints are the series of triangles that will be renederd with a material
// You can only render Draw Points
class IEDrawPointI;

typedef uint64_t TransformId;

class IERendererI
{
	public:


		// Memory Module
		void LoadGFG();


};

#endif // __IE_RENDERERI_H__