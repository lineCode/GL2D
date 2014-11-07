#include "GLBitmapRenderTarget.h"
#include "GLBitmap.h"
#include "GLHelper.h"

namespace GL2D
{
	template< typename Object, typename Interface >
	CRenderTargetBase< Object, Interface >::CRenderTargetBase()
		: CResource< Object, Interface >()
		, CObject( glGenFramebuffers, glDeleteFramebuffers )
	{
	}

	template< typename Object, typename Interface >
	CRenderTargetBase< Object, Interface >::~CRenderTargetBase()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateBitmap( GL2D_SIZE_U size, const void *srcData, uint32_t pitch, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
			CBitmap * bmp = reinterpret_cast< CBitmap * >( CBitmap::CreateInstance() );
			bmp->Initialise( size, srcData, pitch, *bitmapProperties );
			*bitmap = bmp;
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateBitmapFromWicBitmap( IWICBitmapSource *wicBitmapSource, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateSharedBitmap( REFIID riid, void *data, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap )
	{
		HRESULT hr = E_POINTER;

		if ( bitmap )
		{
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateBitmapBrush( IGL2DBitmap *bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DBitmapBrush **bitmapBrush )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapBrush )
		{
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateSolidColorBrush( const GL2D_COLOR_F *color, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DSolidColorBrush **solidColorBrush )
	{
		HRESULT hr = E_POINTER;

		if ( solidColorBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateGradientStopCollection( const GL2D_GRADIENT_STOP *gradientStops, uint32_t gradientStopsCount, GL2D_GAMMA colorInterpolationGamma, GL2D_EXTEND_MODE extendMode, IGL2DGradientStopCollection **gradientStopCollection )
	{
		HRESULT hr = E_POINTER;

		if ( gradientStopCollection )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateLinearGradientBrush( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DLinearGradientBrush **linearGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( linearGradientBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateRadialGradientBrush( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DRadialGradientBrush **radialGradientBrush )
	{
		HRESULT hr = E_POINTER;

		if ( radialGradientBrush )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateCompatibleRenderTarget( const GL2D_SIZE_F *desiredSize, const GL2D_SIZE_U *desiredPixelSize, const GL2D_PIXEL_FORMAT *desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options, IGL2DBitmapRenderTarget **bitmapRenderTarget )
	{
		HRESULT hr = E_POINTER;

		if ( bitmapRenderTarget )
		{
			*bitmapRenderTarget = CBitmapRenderTarget::CreateInstance();
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateLayer( const GL2D_SIZE_F *size, IGL2DLayer **layer )
	{
		HRESULT hr = E_POINTER;

		if ( layer )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::CreateMesh( IGL2DMesh **mesh )
	{
		HRESULT hr = E_POINTER;

		if ( mesh )
		{
			hr = S_OK;
		}

		return hr;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawLine( GL2D_POINT_2F point0, GL2D_POINT_2F point1, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawRectangle( const GL2D_RECT_F *rect, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillRectangle( const GL2D_RECT_F *rect, IGL2DBrush *brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawRoundedRectangle( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush,float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillRoundedRectangle( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawEllipse( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush,float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillEllipse( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawGeometry( IGL2DGeometry *geometry, IGL2DBrush *brush, float strokeWidth, IGL2DStrokeStyle *strokeStyle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillGeometry( IGL2DGeometry *geometry, IGL2DBrush *brush, IGL2DBrush *opacityBrush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillMesh( IGL2DMesh *mesh, IGL2DBrush *brush )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::FillOpacityMask( IGL2DBitmap *opacityMask, IGL2DBrush *brush,GL2D_OPACITY_MASK_CONTENT content, const GL2D_RECT_F *destinationRectangle, const GL2D_RECT_F *sourceRectangle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawBitmap( IGL2DBitmap *bitmap, const GL2D_RECT_F *destinationRectangle, float opacity, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F *sourceRectangle )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawText( const WCHAR *string, uint32_t stringLength, IDWriteTextFormat *textFormat, const GL2D_RECT_F *layoutRect, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawTextLayout( GL2D_POINT_2F origin, IDWriteTextLayout *textLayout, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::DrawGlyphRun( GL2D_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN *glyphRun, IGL2DBrush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetTransform( const GL2D_MATRIX_3X2_F *transform )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::GetTransform( GL2D_MATRIX_3X2_F *transform ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetAntialiasMode( GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_ANTIALIAS_MODE ) CRenderTargetBase< Object, Interface >::GetAntialiasMode() const
	{
		return GL2D_ANTIALIAS_MODE_ALIASED;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetTextAntialiasMode( GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode  )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_TEXT_ANTIALIAS_MODE ) CRenderTargetBase< Object, Interface >::GetTextAntialiasMode( ) const
	{
		return GL2D_TEXT_ANTIALIAS_MODE_ALIASED;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetTextRenderingParams( IDWriteRenderingParams *textRenderingParams )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::GetTextRenderingParams( IDWriteRenderingParams **textRenderingParams ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetTags( GL2D_TAG tag1, GL2D_TAG tag2 )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::GetTags( GL2D_TAG *tag1, GL2D_TAG *tag2 ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::PushLayer( const GL2D_LAYER_PARAMETERS *layerParameters, IGL2DLayer *layer )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::PopLayer()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::Flush( GL2D_TAG *tag1, GL2D_TAG *tag2 )
	{
		return E_NOTIMPL;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SaveDrawingState( IGL2DDrawingStateBlock *drawingStateBlock ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::RestoreDrawingState( IGL2DDrawingStateBlock *drawingStateBlock )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::PushAxisAlignedClip( const GL2D_RECT_F *clipRect, GL2D_ANTIALIAS_MODE antialiasMode )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::PopAxisAlignedClip()
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::Clear( const GL2D_COLOR_F * colour )
	{
		glClearColor( colour->r, colour->g, colour->b, colour->a );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::BeginDraw()
	{
		glBindFramebuffer( m_name, GL2D_GL_FRAMEBUFFER_MODE_DRAW );
		glDisable( GL_DEPTH_TEST );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity ();
		glOrtho( 0, m_size.width, m_size.height, 0, 0, 1 );
		glMatrixMode( GL_MODELVIEW );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP CRenderTargetBase< Object, Interface >::EndDraw( GL2D_TAG *tag1, GL2D_TAG *tag2 )
	{
		glBindFramebuffer( 0, GL2D_GL_FRAMEBUFFER_MODE_DRAW );
		return glGetLastError( "glBindFramebuffer" );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CRenderTargetBase< Object, Interface >::GetPixelFormat() const
	{
		return GL2D_PIXEL_FORMAT();
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::SetDpi( float dpiX, float dpiY )
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( void ) CRenderTargetBase< Object, Interface >::GetDpi( float *dpiX, float *dpiY ) const
	{
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_SIZE_F ) CRenderTargetBase< Object, Interface >::GetSize() const
	{
		float x, y;
		GetDpi( &x, &y );
		return SizeF( m_size.width / x, m_size.height / y );
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( GL2D_SIZE_U ) CRenderTargetBase< Object, Interface >::GetPixelSize() const
	{
		return m_size;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( uint32_t ) CRenderTargetBase< Object, Interface >::GetMaximumBitmapSize() const
	{
		return 4096 * 4096;
	}

	template< typename Object, typename Interface >
	STDMETHODIMP_( bool ) CRenderTargetBase< Object, Interface >::IsSupported( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties ) const
	{
		return false;
	}
}