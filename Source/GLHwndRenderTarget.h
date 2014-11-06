#ifndef ___OGL2D_HWND_RENDER_TARGET_H___
#define ___OGL2D_HWND_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"

namespace GL2D
{
	class CComHwndRenderTarget
	{
	public:
		CComHwndRenderTarget();
		virtual ~CComHwndRenderTarget();

		STDMETHOD_( HWND, GetHwnd )()const;

	private:
		HWND m_hWnd;
	};
}

#endif // ___OGL2D_RENDER_TARGET_H___
