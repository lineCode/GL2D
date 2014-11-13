#ifndef ___OGL2D_BITMAP_H___
#define ___OGL2D_BITMAP_H___

#include "GLImage.h"
#include "GLObject.h"

namespace GL2D
{
	class CComBitmap
		: public IGL2DBitmap
		, public CObject
	{
	public:
		GL2D_API CComBitmap();
		GL2D_API virtual ~CComBitmap();

		GL2D_API void Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props );
		GL2D_API void Draw( const GL2D_RECT_F & rcDst, GL2D_BITMAP_INTERPOLATION_MODE mode, const GL2D_RECT_F & rcSrc );
		
		GL2D_API STDMETHOD_( GL2D_SIZE_F, GetSize )()const;
		GL2D_API STDMETHOD_( GL2D_SIZE_U, GetPixelSize )()const;
		GL2D_API STDMETHOD_( GL2D_PIXEL_FORMAT, GetPixelFormat )()const;
		GL2D_API STDMETHOD_( void, GetDpi )( float * dpiX, float * dpiY  )const;
		GL2D_API STDMETHOD( CopyFromBitmap )( const GL2D_POINT_2U * destPoint, IGL2DBitmap * bitmap, const GL2D_RECT_U * srcRect );
		GL2D_API STDMETHOD( CopyFromRenderTarget )( const GL2D_POINT_2U * destPoint, IGL2DRenderTarget * renderTarget, const GL2D_RECT_U * srcRect );
		GL2D_API STDMETHOD( CopyFromMemory )( const GL2D_RECT_U * dstRect, const void * srcData, uint32_t pitch );

	private:
		GL2D_SIZE_U m_size;
		GL2D_PIXEL_FORMAT m_format;
	};
}

#endif // ___OGL2D_BITMAP_H___
