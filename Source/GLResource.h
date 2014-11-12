#ifndef ___OGL2D_RESOURCE_H___
#define ___OGL2D_RESOURCE_H___

#include "GLUnknown.h"

namespace GL2D
{
	template< typename Object, class Interface >
	class CResource
		: public CUnknown< Object, &__uuidof( Interface ) >
	{
	public:
		GL2D_API CResource()
		{
		}

		GL2D_API virtual ~CResource()
		{
		}
		
		GL2D_API STDMETHOD_( void, GetFactory )( IGL2DFactory ** pFactory ) const
		{
		}

		static Interface * CreateInstance()
		{
			return new CResource< Object, Interface >();
		}
	};
}

#endif
