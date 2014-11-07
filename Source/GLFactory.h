#ifndef ___OGL2D_FACTORY_H___
#define ___OGL2D_FACTORY_H___

#include "GLUnknown.h"

namespace GL2D
{
	class CComFactory
		: public IGL2DFactory
	{
	public:
		GL2D_API CComFactory();
		GL2D_API virtual ~CComFactory();

		GL2D_API STDMETHOD( ReloadSystemMetrics )();
		GL2D_API STDMETHOD_( void, GetDesktopDpi )( float *dpiX, float *dpiY );
		GL2D_API STDMETHOD( CreateRectangleGeometry )( const GL2D_RECT_F *rectangle, IGL2DRectangleGeometry **rectangleGeometry );
		GL2D_API STDMETHOD( CreateRoundedRectangleGeometry )( const GL2D_ROUNDED_RECT *roundedRectangle, IGL2DRoundedRectangleGeometry **roundedRectangleGeometry );
		GL2D_API STDMETHOD( CreateEllipseGeometry )( const GL2D_ELLIPSE *ellipse, IGL2DEllipseGeometry **ellipseGeometry );
		GL2D_API STDMETHOD( CreateGeometryGroup )( GL2D_FILL_MODE fillMode, IGL2DGeometry **geometries, uint32_t geometriesCount, IGL2DGeometryGroup **geometryGroup );
		GL2D_API STDMETHOD( CreateTransformedGeometry )( IGL2DGeometry *sourceGeometry, const GL2D_MATRIX_3X2_F *transform, IGL2DTransformedGeometry **transformedGeometry );
		GL2D_API STDMETHOD( CreatePathGeometry )( IGL2DPathGeometry **pathGeometry );
		GL2D_API STDMETHOD( CreateStrokeStyle )( const GL2D_STROKE_STYLE_PROPERTIES *strokeStyleProperties, const float *dashes, uint32_t dashesCount, IGL2DStrokeStyle **strokeStyle );
		GL2D_API STDMETHOD( CreateDrawingStateBlock )( const GL2D_DRAWING_STATE_DESCRIPTION *drawingStateDescription, IDWriteRenderingParams *textRenderingParams, IGL2DDrawingStateBlock **drawingStateBlock );
		GL2D_API STDMETHOD( CreateWicBitmapRenderTarget )( IWICBitmap *target, const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DRenderTarget **renderTarget );
		GL2D_API STDMETHOD( CreateHwndRenderTarget )( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, const GL2D_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties, IGL2DHwndRenderTarget **hwndRenderTarget );
		GL2D_API STDMETHOD( CreateDxgiSurfaceRenderTarget )( IDXGISurface *dxgiSurface, const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DRenderTarget **renderTarget );
		GL2D_API STDMETHOD( CreateDCRenderTarget )( const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties, IGL2DDCRenderTarget **dcRenderTarget );
	};
}

#endif //___OPENGL2D_FACTORY_H___