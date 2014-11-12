#include "stdafx.h"

#include "GLHwndRenderTarget.h"

namespace GL2D
{
	uint32_t GetBytesPerPixel( GL2D_PIXEL_FORMAT format )
	{
		switch ( format.internal )
		{
		case GL2D_GL_INTERNAL_LUMINANCE:
			return 1;
		case GL2D_GL_INTERNAL_ALPHA8:
			return 1;
		case GL2D_GL_INTERNAL_ALPHA16:
			return 2;
		case GL2D_GL_INTERNAL_LUMINANCE8:
			return 1;
		case GL2D_GL_INTERNAL_LUMINANCE16:
			return 2;
		case GL2D_GL_INTERNAL_LUMINANCE8_ALPHA8:
			return 2;
		case GL2D_GL_INTERNAL_LUMINANCE16_ALPHA16:
			return 4;
		case GL2D_GL_INTERNAL_INTENSITY8:
			return 1;
		case GL2D_GL_INTERNAL_INTENSITY16:
			return 2;
		case GL2D_GL_INTERNAL_RGB8:
			return 3;
		case GL2D_GL_INTERNAL_RGB16:
			return 6;
		case GL2D_GL_INTERNAL_RGBA8:
			return 4;
		case GL2D_GL_INTERNAL_RGBA16:
			return 8;
		case GL2D_GL_INTERNAL_DEPTH_COMPONENT16:
			return 2;
		case GL2D_GL_INTERNAL_DEPTH_COMPONENT24:
			return 3;
		case GL2D_GL_INTERNAL_DEPTH_COMPONENT32:
			return 4;
		case GL2D_GL_INTERNAL_R8:
			return 1;
		case GL2D_GL_INTERNAL_RG8:
			return 2;
		case GL2D_GL_INTERNAL_RG16:
			return 4;
		case GL2D_GL_INTERNAL_R32F:
			return 4;
		case GL2D_GL_INTERNAL_RG32F:
			return 8;
		case GL2D_GL_INTERNAL_RGBA32F:
			return 16;
		case GL2D_GL_INTERNAL_RGB32F:
			return 12;
		case GL2D_GL_INTERNAL_DEPTH24_STENCIL8:
			return 4;
		case GL2D_GL_INTERNAL_DEPTH_COMPONENT32F:
			return 4;
		case GL2D_GL_INTERNAL_STENCIL_INDEX1:
			return 1;
		case GL2D_GL_INTERNAL_STENCIL_INDEX4:
			return 1;
		case GL2D_GL_INTERNAL_STENCIL_INDEX8:
			return 1;
		case GL2D_GL_INTERNAL_STENCIL_INDEX16:
			return 2;
		}

		return 0;
	}

	CComHwndRenderTarget::CComHwndRenderTarget()
	{
	}

	CComHwndRenderTarget::~CComHwndRenderTarget()
	{
	}

	STDMETHODIMP CComHwndRenderTarget::Create( const GL2D_RENDER_TARGET_PROPERTIES & renderTargetProperties, const GL2D_HWND_RENDER_TARGET_PROPERTIES & hwndRenderTargetProperties )
	{
		HRESULT hr = E_FAIL;
		try
		{
			m_context = std::make_unique< CContext >( hwndRenderTargetProperties.hwnd );
			hr = S_OK;
		}
		catch( ... )
		{
		}

		return hr;
	}

	STDMETHODIMP_( void ) CComHwndRenderTarget::Destroy()
	{
		m_context.reset();
	}

	STDMETHODIMP_( GL2D_WINDOW_STATE ) CComHwndRenderTarget::CheckWindowState()
	{
		return GL2D_WINDOW_STATE_NONE;
	}

	STDMETHODIMP CComHwndRenderTarget::Resize( const GL2D_SIZE_U * pixelSize )
	{
		HRESULT hr = E_POINTER;

		if ( pixelSize )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP_( HWND ) CComHwndRenderTarget::GetHwnd()const
	{
		return m_context->GetWindow();
	}
}
