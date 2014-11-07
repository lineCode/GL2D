#ifndef ___OGL2D_BITMAP_RENDER_TARGET_H___
#define ___OGL2D_BITMAP_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"

namespace GL2D
{
	class CComBitmapRenderTarget
		: public IGL2DBitmapRenderTarget
	{
	public:
		GL2D_API CComBitmapRenderTarget();
		GL2D_API virtual ~CComBitmapRenderTarget();

		GL2D_API STDMETHOD( GetBitmap )( IGL2DBitmap **bitmap );
	};
}

#endif // ___OGL2D_RENDER_TARGET_H___
