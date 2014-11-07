#ifndef ___OGL2D_HWND_RENDER_TARGET_H___
#define ___OGL2D_HWND_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"

namespace GL2D
{
	class CComHwndRenderTarget
		: public IGL2DHwndRenderTarget
	{
	public:
		GL2D_API CComHwndRenderTarget();
		GL2D_API virtual ~CComHwndRenderTarget();

		GL2D_API STDMETHOD_( HWND, GetHwnd )()const;

	private:
		HWND m_hWnd;
	};
}

#endif // ___OGL2D_RENDER_TARGET_H___
