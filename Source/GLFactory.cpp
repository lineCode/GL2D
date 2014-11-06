#include "stdafx.h"

#include "GLFactory.h"
#include "GLResource.h"
#include "GLRenderTarget.h"

namespace GL2D
{
	CComFactory::CComFactory()
	{
	}

	CComFactory::~CComFactory()
	{
	}

	STDMETHODIMP CComFactory::ReloadSystemMetrics()
	{
		HRESULT hr = E_POINTER;



		return hr;
	}

	void CComFactory::GetDesktopDpi( float *dpiX, float *dpiY )
	{
		HDC screen = GetDC( 0 );

		if ( dpiX && dpiY )
		{
			*dpiX = float( GetDeviceCaps( screen, LOGPIXELSX ) );
			*dpiY = float( GetDeviceCaps( screen, LOGPIXELSY ) );
		}
	}

	STDMETHODIMP CComFactory::CreateRectangleGeometry( const GL2D_RECT_F *rectangle, IGL2DRectangleGeometry **rectangleGeometry )
	{
		HRESULT hr = E_POINTER;

		if ( rectangleGeometry )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateRoundedRectangleGeometry( const GL2D_ROUNDED_RECT *roundedRectangle, IGL2DRoundedRectangleGeometry **roundedRectangleGeometry )
	{
		HRESULT hr = E_POINTER;

		if ( roundedRectangleGeometry )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateEllipseGeometry( const GL2D_ELLIPSE *ellipse, IGL2DEllipseGeometry **ellipseGeometry )
	{
		HRESULT hr = E_POINTER;

		if ( ellipseGeometry )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateGeometryGroup( GL2D_FILL_MODE fillMode, IGL2DGeometry **geometries, uint32_t geometriesCount, IGL2DGeometryGroup **geometryGroup )
	{
		HRESULT hr = E_POINTER;

		if ( geometryGroup )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateTransformedGeometry( IGL2DGeometry *sourceGeometry, const GL2D_MATRIX_3X2_F *transform, IGL2DTransformedGeometry **transformedGeometry )
	{
		HRESULT hr = E_POINTER;

		if ( transformedGeometry )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreatePathGeometry( IGL2DPathGeometry **pathGeometry )
	{
		HRESULT hr = E_POINTER;

		if ( pathGeometry )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateStrokeStyle( const GL2D_STROKE_STYLE_PROPERTIES *strokeStyleProperties, const float *dashes, uint32_t dashesCount, IGL2DStrokeStyle **strokeStyle )
	{
		HRESULT hr = E_POINTER;

		if ( strokeStyle )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateDrawingStateBlock( const GL2D_DRAWING_STATE_DESCRIPTION *drawingStateDescription, IDWriteRenderingParams *textRenderingParams, IGL2DDrawingStateBlock **drawingStateBlock )
	{
		HRESULT hr = E_POINTER;

		if ( drawingStateBlock )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateWicBitmapRenderTarget( IWICBitmap *target, const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DRenderTarget **renderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( renderTarget )
		{
			CRenderTarget::CreateInstance();
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateHwndRenderTarget( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, const GL2D_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties, IGL2DHwndRenderTarget **hwndRenderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( hwndRenderTarget )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateDxgiSurfaceRenderTarget( IDXGISurface *dxgiSurface, const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DRenderTarget **renderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( renderTarget )
		{
		}

		return hr;
	}

	STDMETHODIMP CComFactory::CreateDCRenderTarget( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DDCRenderTarget **dcRenderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( dcRenderTarget )
		{
		}

		return hr;
	}
}
