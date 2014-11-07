#ifndef ___OGL2D_RENDER_TARGET_H___
#define ___OGL2D_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"

namespace GL2D
{
	class CComRenderTarget
        : public IGL2DRenderTarget
	{
	public:
		GL2D_API CComRenderTarget();
		GL2D_API virtual ~CComRenderTarget();
	};
}

#include "GLRenderTargetBase.h"

#endif // ___OGL2D_RENDER_TARGET_H___
