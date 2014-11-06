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

	STDMETHODIMP_( HWND ) CComHwndRenderTarget::GetHwnd()const
	{
		return m_hWnd;
	}
}
