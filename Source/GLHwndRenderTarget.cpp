#include "stdafx.h"

#include "GLHwndRenderTarget.h"

namespace GL2D
{
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
