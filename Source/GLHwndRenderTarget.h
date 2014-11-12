#ifndef ___OGL2D_HWND_RENDER_TARGET_H___
#define ___OGL2D_HWND_RENDER_TARGET_H___

#include "GLRenderTargetBase.h"
#include "GLContext.h"

#include <memory>

namespace GL2D
{
	class CComHwndRenderTarget
		: public IGL2DHwndRenderTarget
	{
	public:
		GL2D_API CComHwndRenderTarget();
		GL2D_API virtual ~CComHwndRenderTarget();

		STDMETHOD( Create )( const GL2D_RENDER_TARGET_PROPERTIES & renderTargetProperties, const GL2D_HWND_RENDER_TARGET_PROPERTIES & hwndRenderTargetProperties );
		STDMETHOD_( void, Destroy )();
		
		GL2D_API STDMETHOD_( GL2D_WINDOW_STATE, CheckWindowState )();
		GL2D_API STDMETHOD( Resize )( const GL2D_SIZE_U *pixelSize );
		GL2D_API STDMETHOD_( HWND, GetHwnd )()const;

	private:
		std::unique_ptr< CContext > m_context;
	};
}

#endif // ___OGL2D_RENDER_TARGET_H___
