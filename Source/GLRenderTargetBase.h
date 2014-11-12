#ifndef ___OGL2D_RENDER_TARGET_BASE_H___
#define ___OGL2D_RENDER_TARGET_BASE_H___

#include "OpenGL2DPrerequisites.h"
#include "GLBaseTypes.h"
#include "GLObject.h"

#if defined( DrawText )
#	undef DrawText
#endif

namespace GL2D
{
	template< typename Object, typename Interface >
	class CRenderTargetBase
		: public CResource< Object, Interface >
		, public CObject
	{
	public:
		CRenderTargetBase();
		virtual ~CRenderTargetBase();

		static Interface * CreateInstance()
		{
			return new CRenderTargetBase< Object, Interface >();
		}

		STDMETHOD( CreateBitmap )( GL2D_SIZE_U size, const void *srcData, uint32_t pitch, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap );
		STDMETHOD( CreateBitmapFromWicBitmap )( IWICBitmapSource *wicBitmapSource, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap );
		STDMETHOD( CreateSharedBitmap )( REFIID riid, void *data, const GL2D_BITMAP_PROPERTIES *bitmapProperties, IGL2DBitmap **bitmap );
		STDMETHOD( CreateBitmapBrush )( IGL2DBitmap *bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DBitmapBrush **bitmapBrush );
		STDMETHOD( CreateSolidColorBrush )( const GL2D_COLOR_F *color, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DSolidColorBrush **solidColorBrush );
		STDMETHOD( CreateGradientStopCollection )( const GL2D_GRADIENT_STOP *gradientStops, uint32_t gradientStopsCount, GL2D_GAMMA colorInterpolationGamma, GL2D_EXTEND_MODE extendMode, IGL2DGradientStopCollection **gradientStopCollection );
		STDMETHOD( CreateLinearGradientBrush )( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DLinearGradientBrush **linearGradientBrush );
		STDMETHOD( CreateRadialGradientBrush )( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties, const GL2D_BRUSH_PROPERTIES *brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DRadialGradientBrush **radialGradientBrush );
		STDMETHOD( CreateCompatibleRenderTarget )( const GL2D_SIZE_F *desiredSize, const GL2D_SIZE_U *desiredPixelSize, const GL2D_PIXEL_FORMAT *desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options, IGL2DBitmapRenderTarget **bitmapRenderTarget );
		STDMETHOD( CreateLayer )( const GL2D_SIZE_F *size, IGL2DLayer **layer );
		STDMETHOD( CreateMesh )( IGL2DMesh **mesh );
		STDMETHOD_( void, DrawLine )( GL2D_POINT_2F point0, GL2D_POINT_2F point1, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL );
		STDMETHOD_( void, DrawRectangle )( const GL2D_RECT_F *rect, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL );
		STDMETHOD_( void, FillRectangle )( const GL2D_RECT_F *rect, IGL2DBrush *brush );
		STDMETHOD_( void, DrawRoundedRectangle )( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush,float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL );
		STDMETHOD_( void, FillRoundedRectangle )( const GL2D_ROUNDED_RECT *roundedRect, IGL2DBrush *brush );
		STDMETHOD_( void, DrawEllipse )( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush,float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL );
		STDMETHOD_( void, FillEllipse )( const GL2D_ELLIPSE *ellipse, IGL2DBrush *brush );
		STDMETHOD_( void, DrawGeometry )( IGL2DGeometry *geometry, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL );
		STDMETHOD_( void, FillGeometry )( IGL2DGeometry *geometry, IGL2DBrush *brush, IGL2DBrush *opacityBrush = NULL );
		STDMETHOD_( void, FillMesh )( IGL2DMesh *mesh, IGL2DBrush *brush );
		STDMETHOD_( void, FillOpacityMask )( IGL2DBitmap *opacityMask, IGL2DBrush *brush,GL2D_OPACITY_MASK_CONTENT content, const GL2D_RECT_F *destinationRectangle = NULL, const GL2D_RECT_F *sourceRectangle = NULL );
		STDMETHOD_( void, DrawBitmap )( IGL2DBitmap *bitmap, const GL2D_RECT_F *destinationRectangle = NULL, float opacity = 1.0f, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode = GL2D_BITMAP_INTERPOLATION_MODE_LINEAR, const GL2D_RECT_F *sourceRectangle = NULL );
		STDMETHOD_( void, DrawText )( const WCHAR *string, uint32_t stringLength, IDWriteTextFormat *textFormat, const GL2D_RECT_F *layoutRect, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL );
		STDMETHOD_( void, DrawTextLayout )( GL2D_POINT_2F origin, IDWriteTextLayout *textLayout, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE );
		STDMETHOD_( void, DrawGlyphRun )( GL2D_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN *glyphRun, IGL2DBrush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL );
		STDMETHOD_( void, SetTransform )( const GL2D_MATRIX_3X2_F *transform );
		STDMETHOD_( void, GetTransform )( GL2D_MATRIX_3X2_F *transform ) const;
		STDMETHOD_( void, SetAntialiasMode )( GL2D_ANTIALIAS_MODE antialiasMode );
		STDMETHOD_( GL2D_ANTIALIAS_MODE, GetAntialiasMode )() const;
		STDMETHOD_( void, SetTextAntialiasMode )( GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode  );
		STDMETHOD_( GL2D_TEXT_ANTIALIAS_MODE, GetTextAntialiasMode )( ) const;
		STDMETHOD_( void, SetTextRenderingParams )( IDWriteRenderingParams *textRenderingParams = NULL );
		STDMETHOD_( void, GetTextRenderingParams )( IDWriteRenderingParams **textRenderingParams ) const;
		STDMETHOD_( void, SetTags )( GL2D_TAG tag1, GL2D_TAG tag2 );
		STDMETHOD_( void, GetTags )( GL2D_TAG *tag1 = NULL, GL2D_TAG *tag2 = NULL ) const;
		STDMETHOD_( void, PushLayer )( const GL2D_LAYER_PARAMETERS *layerParameters, IGL2DLayer *layer );
		STDMETHOD_( void, PopLayer )();
		STDMETHOD( Flush )( GL2D_TAG *tag1 = NULL, GL2D_TAG *tag2 = NULL );
		STDMETHOD_( void, SaveDrawingState )( IGL2DDrawingStateBlock *drawingStateBlock ) const;
		STDMETHOD_( void, RestoreDrawingState )( IGL2DDrawingStateBlock *drawingStateBlock );
		STDMETHOD_( void, PushAxisAlignedClip )( const GL2D_RECT_F *clipRect, GL2D_ANTIALIAS_MODE antialiasMode );
		STDMETHOD_( void, PopAxisAlignedClip )();
		STDMETHOD_( void, Clear )( const GL2D_COLOR_F *clearColor = NULL );
		STDMETHOD_( void, BeginDraw )();
		STDMETHOD( EndDraw )( GL2D_TAG *tag1 = NULL, GL2D_TAG *tag2 = NULL );
		STDMETHOD_( GL2D_PIXEL_FORMAT, GetPixelFormat )() const;
		STDMETHOD_( void, SetDpi )( float dpiX, float dpiY );
		STDMETHOD_( void, GetDpi )( float *dpiX, float *dpiY ) const;
		STDMETHOD_( GL2D_SIZE_F, GetSize )() const;
		STDMETHOD_( GL2D_SIZE_U, GetPixelSize )() const;
		STDMETHOD_( uint32_t, GetMaximumBitmapSize )() const;
		STDMETHOD_( bool, IsSupported )( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties ) const;

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmap( GL2D_SIZE_U size, const void *srcData, uint32_t pitch, const GL2D_BITMAP_PROPERTIES &bitmapProperties, IGL2DBitmap **bitmap )
		{
			return CreateBitmap(size, srcData, pitch, &bitmapProperties, bitmap);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmap( GL2D_SIZE_U size, const GL2D_BITMAP_PROPERTIES &bitmapProperties, IGL2DBitmap **bitmap )
		{
			return CreateBitmap(size, NULL, 0, &bitmapProperties, bitmap);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmapFromWicBitmap( IWICBitmapSource *wicBitmapSource, const GL2D_BITMAP_PROPERTIES &bitmapProperties, IGL2DBitmap **bitmap )
		{
			return CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmapFromWicBitmap( IWICBitmapSource *wicBitmapSource, IGL2DBitmap **bitmap )
		{
			return CreateBitmapFromWicBitmap(wicBitmapSource, NULL, bitmap);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmapBrush( IGL2DBitmap *bitmap, IGL2DBitmapBrush **bitmapBrush )
		{
			return CreateBitmapBrush(bitmap, NULL, NULL, bitmapBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmapBrush( IGL2DBitmap *bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties, IGL2DBitmapBrush **bitmapBrush )
		{
			return CreateBitmapBrush(bitmap, &bitmapBrushProperties, NULL, bitmapBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateBitmapBrush( IGL2DBitmap *bitmap, const GL2D_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties, const GL2D_BRUSH_PROPERTIES &brushProperties, IGL2DBitmapBrush **bitmapBrush )
		{
			return CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateSolidColorBrush( const GL2D_COLOR_F &color, IGL2DSolidColorBrush **solidColorBrush )
		{
			return CreateSolidColorBrush(&color, NULL, solidColorBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateSolidColorBrush( const GL2D_COLOR_F &color, const GL2D_BRUSH_PROPERTIES &brushProperties, IGL2DSolidColorBrush **solidColorBrush )
		{
			return CreateSolidColorBrush(&color, &brushProperties, solidColorBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateGradientStopCollection( const GL2D_GRADIENT_STOP *gradientStops, uint32_t gradientStopsCount, IGL2DGradientStopCollection **gradientStopCollection )
		{
			return CreateGradientStopCollection(gradientStops, gradientStopsCount, GL2D_GAMMA_2_2, GL2D_EXTEND_MODE_CLAMP, gradientStopCollection);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateLinearGradientBrush( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DLinearGradientBrush **linearGradientBrush )
		{
			return CreateLinearGradientBrush(&linearGradientBrushProperties, NULL, gradientStopCollection, linearGradientBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateLinearGradientBrush( const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties, const GL2D_BRUSH_PROPERTIES &brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DLinearGradientBrush **linearGradientBrush )
		{
			return CreateLinearGradientBrush(&linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateRadialGradientBrush( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DRadialGradientBrush **radialGradientBrush )
		{
			return CreateRadialGradientBrush(&radialGradientBrushProperties, NULL, gradientStopCollection, radialGradientBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateRadialGradientBrush( const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties, const GL2D_BRUSH_PROPERTIES &brushProperties, IGL2DGradientStopCollection *gradientStopCollection, IGL2DRadialGradientBrush **radialGradientBrush )
		{
			return CreateRadialGradientBrush(&radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateCompatibleRenderTarget( IGL2DBitmapRenderTarget **bitmapRenderTarget )
		{
			return CreateCompatibleRenderTarget(NULL, NULL, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateCompatibleRenderTarget( GL2D_SIZE_F desiredSize, IGL2DBitmapRenderTarget **bitmapRenderTarget )
		{
			return CreateCompatibleRenderTarget(&desiredSize, NULL, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateCompatibleRenderTarget( GL2D_SIZE_F desiredSize, GL2D_SIZE_U desiredPixelSize, IGL2DBitmapRenderTarget **bitmapRenderTarget )
		{
			return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateCompatibleRenderTarget( GL2D_SIZE_F desiredSize, GL2D_SIZE_U desiredPixelSize, GL2D_PIXEL_FORMAT desiredFormat, IGL2DBitmapRenderTarget **bitmapRenderTarget )
		{
			return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateCompatibleRenderTarget( GL2D_SIZE_F desiredSize, GL2D_SIZE_U desiredPixelSize, GL2D_PIXEL_FORMAT desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options, IGL2DBitmapRenderTarget **bitmapRenderTarget )
		{
			return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, options, bitmapRenderTarget);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateLayer( GL2D_SIZE_F size, IGL2DLayer **layer )
		{
			return CreateLayer(&size, layer);
		}

		COM_DECLSPEC_NOTHROW
		HRESULT CreateLayer( IGL2DLayer **layer )
		{
			return CreateLayer(NULL, layer);
		}

		COM_DECLSPEC_NOTHROW
		void DrawRectangle( const GL2D_RECT_F &rect, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL )
		{
			DrawRectangle(&rect, brush, strokeWidth, strokeStyle);
		}

		COM_DECLSPEC_NOTHROW
		void FillRectangle( const GL2D_RECT_F &rect, IGL2DBrush *brush )
		{
			FillRectangle(&rect, brush);
		}

		COM_DECLSPEC_NOTHROW
		void DrawRoundedRectangle( const GL2D_ROUNDED_RECT &roundedRect, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL )
		{
			DrawRoundedRectangle(&roundedRect, brush, strokeWidth, strokeStyle);
		}

		COM_DECLSPEC_NOTHROW
		void FillRoundedRectangle( const GL2D_ROUNDED_RECT &roundedRect, IGL2DBrush *brush )
		{
			FillRoundedRectangle(&roundedRect, brush);
		}

		COM_DECLSPEC_NOTHROW
		void DrawEllipse( const GL2D_ELLIPSE &ellipse, IGL2DBrush *brush, float strokeWidth = 1.0f, IGL2DStrokeStyle *strokeStyle = NULL  )
		{
			DrawEllipse(&ellipse, brush, strokeWidth, strokeStyle);
		}

		COM_DECLSPEC_NOTHROW
		void FillEllipse( const GL2D_ELLIPSE &ellipse, IGL2DBrush *brush )
		{
			FillEllipse(&ellipse, brush);
		}

		COM_DECLSPEC_NOTHROW
		void FillOpacityMask( IGL2DBitmap *opacityMask, IGL2DBrush *brush, GL2D_OPACITY_MASK_CONTENT content, const GL2D_RECT_F &destinationRectangle, const GL2D_RECT_F &sourceRectangle )
		{
			FillOpacityMask(opacityMask, brush, content, &destinationRectangle, &sourceRectangle);
		}

		COM_DECLSPEC_NOTHROW
		void DrawBitmap( IGL2DBitmap *bitmap, const GL2D_RECT_F &destinationRectangle, float opacity = 1.0f, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode = GL2D_BITMAP_INTERPOLATION_MODE_LINEAR, const GL2D_RECT_F *sourceRectangle = NULL )
		{
			DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle);
		}

		COM_DECLSPEC_NOTHROW
		void DrawBitmap( IGL2DBitmap *bitmap, const GL2D_RECT_F &destinationRectangle, float opacity, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F &sourceRectangle )
		{
			DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle);
		}

		COM_DECLSPEC_NOTHROW
		void SetTransform( const GL2D_MATRIX_3X2_F &transform )
		{
			SetTransform(&transform);
		}

		COM_DECLSPEC_NOTHROW
		void PushLayer( const GL2D_LAYER_PARAMETERS &layerParameters, IGL2DLayer *layer )
		{
			PushLayer(&layerParameters, layer);
		}

		COM_DECLSPEC_NOTHROW
		void PushAxisAlignedClip( const GL2D_RECT_F &clipRect, GL2D_ANTIALIAS_MODE antialiasMode )
		{
			return PushAxisAlignedClip(&clipRect, antialiasMode);
		}

		COM_DECLSPEC_NOTHROW
		void Clear( const GL2D_COLOR_F &clearColor )
		{
			return Clear(&clearColor);
		}

		COM_DECLSPEC_NOTHROW
		void DrawText( const WCHAR *string, uint32_t stringLength, IDWriteTextFormat *textFormat, const GL2D_RECT_F &layoutRect, IGL2DBrush *defaultForegroundBrush, GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL )
		{
			return DrawText(string, stringLength, textFormat, &layoutRect, defaultForegroundBrush, options, measuringMode);
		}

		COM_DECLSPEC_NOTHROW
		bool IsSupported( const GL2D_RENDER_TARGET_PROPERTIES &renderTargetProperties ) const
		{
			return IsSupported(&renderTargetProperties);
		}

	protected:
		GL2D_SIZE_U m_size;
	};
}

#include "GLRenderTargetBase.inl"

#endif // ___OGL2D_RENDER_TARGET_H___
