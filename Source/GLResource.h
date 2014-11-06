#ifndef ___OGL2D_RESOURCE_H___
#define ___OGL2D_RESOURCE_H___

#include "GLUnknown.h"

namespace GL2D
{
	template< typename Object, typename Interface >
	class CResource
		: public CUnknown< Object, Interface >
	{
	public:
		CResource()
		{
		}

		virtual ~CResource()
		{
		}
		
		STDMETHOD_( void, GetFactory )( IGL2DFactory ** pFactory ) const
		{
		}

		static CResource< Object, Interface > * CreateInstance()
		{
			return new CResource< Object, Interface >;
		}
	};
}

#endif
