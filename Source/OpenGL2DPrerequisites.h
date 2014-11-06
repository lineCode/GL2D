#ifndef ___OGL2D_OPENGL_2D_PREREQUISITES_H___
#define ___OGL2D_OPENGL_2D_PREREQUISITES_H___

#include "GL2D.h"

namespace GL2D
{
	template< typename Object, typename Interface >
	class CUnknown;
	template< typename Object, typename Interface >
	class CResource;
	template< typename Object, typename Interface >
	class CImage;
	template< typename Object, typename Interface >
	class CRenderTargetBase;

	class CComBitmap;
	class CComStrokeStyle;
	class CComBrush;
	class CComSolidColorBrush;
	class CComFactory;
	class CComBitmapBrush;
	class CComLinearGradientBrush;
	class CComRadialGradientBrush;
	class CComLayer;
	class CComMesh;
	class CComGeometry;
	class CComDrawingStateBlock;
	class CComRenderTarget;
	class CComHwndRenderTarget;
	class CComBitmapRenderTarget;
	class CComGradientStopCollection;

	typedef CImage< CComBitmap, IGL2DBitmap > CBitmap;
	typedef CResource< CComStrokeStyle, IGL2DStrokeStyle > CStrokeStyle;
	typedef CResource< CComBrush, IGL2DBrush > CBrush;
	typedef CResource< CComSolidColorBrush, IGL2DSolidColorBrush > CSolidColorBrush;
	typedef CResource< CComFactory, IGL2DFactory > CFactory;
	typedef CResource< CComBitmapBrush, IGL2DBitmapBrush > CBitmapBrush;
	typedef CResource< CComLinearGradientBrush, IGL2DLinearGradientBrush > CLinearGradientBrush;
	typedef CResource< CComRadialGradientBrush, IGL2DRadialGradientBrush > CRadialGradientBrush;
	typedef CResource< CComLayer, IGL2DLayer > CLayer;
	typedef CResource< CComMesh, IGL2DMesh > CMesh;
	typedef CResource< CComGeometry, IGL2DGeometry > CGeometry;
	typedef CResource< CComDrawingStateBlock, IGL2DDrawingStateBlock > CDrawingStateBlock;
	typedef CRenderTargetBase< CResource< CComRenderTarget, IGL2DRenderTarget >, IGL2DRenderTarget > CRenderTarget;
	typedef CRenderTargetBase< CResource< CComHwndRenderTarget, IGL2DHwndRenderTarget >, IGL2DRenderTarget > CHwndRenderTarget;
	typedef CRenderTargetBase< CResource< CComBitmapRenderTarget, IGL2DBitmapRenderTarget >, IGL2DRenderTarget > CBitmapRenderTarget;
	typedef CResource< CComGradientStopCollection, IGL2DGradientStopCollection > CGradientStopCollection;

}

#endif
