#include "stdafx.h"

#include "GLBitmap.h"
#include "GLHelper.h"

namespace GL2D
{
	CComBitmap::CComBitmap()
		: CObject( &glGenTextures, &glDeleteTextures )
	{
	}

	CComBitmap::~CComBitmap()
	{
	}
	
	void CComBitmap::Initialise( const GL2D_SIZE_U & size, const void * data, uint32_t pitch, const GL2D_BITMAP_PROPERTIES & props )
	{
		m_format = props.pixelFormat;
		m_size = size;
		glBindTexture( GL_TEXTURE_2D, m_name );
		glTexImage2D( GL_TEXTURE_2D, 0, m_format.internal, size.width, size.height, 0, m_format.format, m_format.type, data );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
	
	void CComBitmap::Draw( const GL2D_RECT_F & rcDst, GL2D_GL_TEXTURE_FILTER mode, const GL2D_RECT_F & rcSrc )
	{
		glBindTexture( GL_TEXTURE_2D, m_name );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	STDMETHODIMP_( GL2D_SIZE_F ) CComBitmap::GetSize()const
	{
		float x, y;
		GetDpi( &x, &y );
        return SizeF( m_size.width / x, m_size.height / y );
	}

	STDMETHODIMP_( GL2D_SIZE_U ) CComBitmap::GetPixelSize()const
	{
		return m_size;
	}

	STDMETHODIMP_( GL2D_PIXEL_FORMAT ) CComBitmap::GetPixelFormat()const
	{
		return m_format;
	}

	STDMETHODIMP_( void ) CComBitmap::GetDpi( float * dpiX, float * dpiY  )const
	{
		if ( dpiX && dpiY )
		{
			*dpiX = 96.0f;
			*dpiY = 96.0f;
		}
	}

	STDMETHODIMP CComBitmap::CopyFromBitmap( const GL2D_POINT_2U * destPoint, IGL2DBitmap * bitmap, const GL2D_RECT_U * srcRect )
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP CComBitmap::CopyFromRenderTarget( const GL2D_POINT_2U * destPoint, IGL2DRenderTarget * renderTarget, const GL2D_RECT_U * srcRect )
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP CComBitmap::CopyFromMemory( const GL2D_RECT_U * dstRect, const void * srcData, uint32_t pitch )
	{
		glBindTexture( GL_TEXTURE_2D, m_name );
        glTexSubImage2D( GL_TEXTURE_2D, 0, dstRect->left, dstRect->top, dstRect->right - dstRect->left, dstRect->bottom - dstRect->top, m_format.format, m_format.type, srcData );
		glBindTexture( GL_TEXTURE_2D, 0 );
		return E_NOTIMPL;
	}
}