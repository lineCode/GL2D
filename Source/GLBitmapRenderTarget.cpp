#include "stdafx.h"

#include "GLBitmapRenderTarget.h"

namespace GL2D
{
	CComBitmapRenderTarget::CComBitmapRenderTarget()
	{
	}

	CComBitmapRenderTarget::~CComBitmapRenderTarget()
	{
	}

	STDMETHODIMP CComBitmapRenderTarget::GetBitmap( IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			*bitmap = NULL;
			hr = E_NOTIMPL;
		}

		return hr;
	}
}
