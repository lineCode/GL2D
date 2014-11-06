#include "GLBitmapRenderTarget.h"
#include "GLBitmap.h"

namespace GL2D
{
	CRenderTargetBase::CRenderTargetBase( const GL2D_SIZE_F & size )
		: CObject( &glGenFramebuffers, &glDeleteFramebuffers )
	{
	}

	CRenderTargetBase::~CRenderTargetBase()
	{
	}
	
	STDMETHODIMP CRenderTargetBase::CreateBitmap( GL2D_SIZE_U size, const void *srcData, uint32_t pitch, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			CBitmap * bmp = CBitmap::CreateInstance();
			bmp->Initialise( size, srcData, pitch, *bitmapProperties );
			*bitmap = bmp;
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateBitmapFromWicBitmap( IWICBitmapSource *wicBitmapSource, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateSharedBitmap( REFIID riid, void *data, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateBitmapBrush( IGL2DBitmap *bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DBitmapBrush **bitmapBrush )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapBrush )
		{
		}

		return hr;
	}
	
	STDMETHODIMP CRenderTargetBase::CreateSolidColorBrush( const GL2D_COLOR_F *color, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DSolidColorBrush **solidColorBrush )
	{
		HRESULT hr = E_POINTER;

		if ( solidColorBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateGradientStopCollection( const GL2D_GRADIENT_STOP *gradientStops, uint32_t gradientStopsCount, GL2D_GAMMA colorInterpolationGamma, GL2D_EXTEND_MODE extendMode, IGL2DGradientStopCollection **gradientStopCollection )
	{
		HRESULT hr = E_POINTER;

		if ( gradientStopCollection )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateLinearGradientBrush( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DLinearGradientBrush **linearGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( linearGradientBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateRadialGradientBrush( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DRadialGradientBrush **radialGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( radialGradientBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateCompatibleRenderTarget( const GL2D_SIZE_F *desiredSize, const GL2D_SIZE_U *desiredPixelSize, const GL2D_PIXEL_FORMAT *desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options, IGL2DBitmapRenderTarget **bitmapRenderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapRenderTarget )
		{
			*bitmapRenderTarget = CBitmapRenderTarget::CreateInstance();
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateLayer( const GL2D_SIZE_F *size, IGL2DLayer **layer )
	{
		HRESULT hr = E_POINTER;

		if ( layer )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP CRenderTargetBase::CreateMesh( IGL2DMesh **mesh )
	{
		HRESULT hr = E_POINTER;

		if ( mesh )
		{
			hr = S_OK;
		}

		return hr;
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawLine( GL2D_POINT_2F point0, GL2D_POINT_2F point1, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawRectangle( const GL2D_RECT_F *rect, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillRectangle( const GL2D_RECT_F *rect, IGL2DBrush *brush )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawRoundedRectangle( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush,float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillRoundedRectangle( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawEllipse( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush,float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillEllipse( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawGeometry( IGL2DGeometry *geometry, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillGeometry( IGL2DGeometry *geometry, IGL2DBrush *brush, IGL2DBrush *opacityBrush )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillMesh( IGL2DMesh *mesh, IGL2DBrush *brush )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::FillOpacityMask( IGL2DBitmap *opacityMask, IGL2DBrush *brush,GL2D_OPACITY_MASK_CONTENT content, const GL2D_RECT_F *destinationRectangle, const GL2D_RECT_F *sourceRectangle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawBitmap( IGL2DBitmap *bitmap, const GL2D_RECT_F *destinationRectangle, float opacity, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F *sourceRectangle )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawText( const WCHAR *string, uint32_t stringLength, IDWriteTextFormat *textFormat, const GL2D_RECT_F *layoutRect, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawTextLayout( GL2D_POINT_2F origin, IDWriteTextLayout *textLayout, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::DrawGlyphRun( GL2D_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN *glyphRun, IGL2DBrush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetTransform( const GL2D_MATRIX_3X2_F *transform )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::GetTransform( GL2D_MATRIX_3X2_F *transform ) const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetAntialiasMode( GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	STDMETHODIMP_( GL2D_ANTIALIAS_MODE ) CRenderTargetBase::GetAntialiasMode() const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetTextAntialiasMode( GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode  )
	{
	}

	STDMETHODIMP_( GL2D_TEXT_ANTIALIAS_MODE ) CRenderTargetBase::GetTextAntialiasMode( ) const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetTextRenderingParams( IDWriteRenderingParams *textRenderingParams )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::GetTextRenderingParams( IDWriteRenderingParams **textRenderingParams ) const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetTags( Tag tag1, Tag tag2 )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::GetTags( Tag *tag1, Tag *tag2 ) const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::PushLayer( const GL2D_LAYER_PARAMETERS *layerParameters, IGL2DLayer *layer )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::PopLayer()
	{
	}

	STDMETHODIMP CRenderTargetBase::Flush( Tag *tag1, Tag *tag2 )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SaveDrawingState( IGL2DDrawingStateBlock *drawingStateBlock ) const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::RestoreDrawingState( IGL2DDrawingStateBlock *drawingStateBlock )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::PushAxisAlignedClip( const GL2D_RECT_F *clipRect, GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::PopAxisAlignedClip()
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::Clear( const GL2D_COLOR_F * colour )
	{
		glClearColor( colour->r, colour->g, colour->b, colour->a );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	STDMETHODIMP_( void ) CRenderTargetBase::BeginDraw()
	{
		glBindFramebuffer( m_name, GL2D_GL_FRAMEBUFFER_MODE_DRAW );
		glDisable( GL_DEPTH_TEST );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity ();
		glOrtho( 0, m_size.cx, m_size.cy, 0, 0, 1 );
		glMatrixMode( GL_MODELVIEW );
	}
	
	STDMETHODIMP CRenderTargetBase::EndDraw( Tag *tag1, Tag *tag2 )
	{
		glBindFramebuffer( 0, GL2D_GL_FRAMEBUFFER_MODE_DRAW );
		return glGetLastError( "glBindFramebuffer" );
	}

	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CRenderTargetBase::GetPixelFormat() const
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::SetDpi( float dpiX, float dpiY )
	{
	}

	STDMETHODIMP_( void ) CRenderTargetBase::GetDpi( float *dpiX, float *dpiY ) const
	{
	}

	STDMETHODIMP_( GL2D_SIZE_F ) CRenderTargetBase::GetSize() const
	{
	}

	STDMETHODIMP_( GL2D_SIZE_U ) CRenderTargetBase::GetPixelSize() const
	{
	}

	STDMETHODIMP_( uint32_t ) CRenderTargetBase::GetMaximumBitmapSize() const
	{
	}

	STDMETHODIMP_( bool ) CRenderTargetBase::IsSupported( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties ) const
	{
	}
}