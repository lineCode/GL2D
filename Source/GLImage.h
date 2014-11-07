#ifndef ___OGL2D_IMAGE_H___
#define ___OGL2D_IMAGE_H___

#include "OpenGL2DPrerequisites.h"
#include "GLResource.h"

namespace GL2D
{
	template< typename Object, class Interface >
	class CImage
		: public CResource< Object, Interface >
	{
	public:
		GL2D_API CImage()
		{
		}

		GL2D_API virtual ~CImage()
		{
		}
	};
}

#endif // ___OGL2D_BITMAP_H___
