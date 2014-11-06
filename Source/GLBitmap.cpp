#include "stdafx.h"

#include "GLBitmap.h"

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
		glBindTexture( GL_TEXTURE_2D, m_name );
		glTexImage2D( GL_TEXTURE_2D, 0, props.pixelFormat.internal, size.width, size.height, 0, props.pixelFormat.format, props.pixelFormat.type, data );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
	
	void CComBitmap::Draw( const GL2D_RECT_F & rcDst, GL2D_GL_TEXTURE_FILTER mode, const GL2D_RECT_F & rcSrc )
	{
		glBindTexture( GL_TEXTURE_2D, m_name );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
}