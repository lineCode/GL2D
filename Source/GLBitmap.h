#ifndef ___OGL2D_BITMAP_H___
#define ___OGL2D_BITMAP_H___

#include "GLImage.h"
#include "GLObject.h"

namespace GL2D
{
	class CComBitmap
		: public CObject
	{
	public:
		CComBitmap();
		virtual ~CComBitmap();

		void Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props );
		void Draw( const GL2D_RECT_F & rcDst, GL2D_GL_TEXTURE_FILTER mode, const GL2D_RECT_F & rcSrc );
		
		STDMETHOD_( GL2D_SIZE_F, GetSize )()const;
		STDMETHOD_( GL2D_SIZE_U, GetPixelSize )()const;
		STDMETHOD_( GL2D_PIXEL_FORMAT, GetPixelFormat )()const;
		STDMETHOD_( void, GetDpi )( float * dpiX, float * dpiY  )const;
		STDMETHOD( CopyFromBitmap )( const GL2D_POINT_2U * destPoint, IGL2DBitmap * bitmap, const GL2D_RECT_U * srcRect );
		STDMETHOD( CopyFromRenderTarget )( const GL2D_POINT_2U * destPoint, IGL2DRenderTarget * renderTarget, const GL2D_RECT_U * srcRect );
		STDMETHOD( CopyFromMemory )( const GL2D_RECT_U * dstRect, const void * srcData, uint32_t pitch );
	};
}

#endif // ___OGL2D_BITMAP_H___
