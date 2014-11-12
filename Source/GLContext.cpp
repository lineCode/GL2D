#include "stdafx.h"

#include "GLContext.h"

namespace GL2D
{
	namespace gl_api
	{
		template< typename Func >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, Func & p_func )
		{
			p_func = reinterpret_cast< Func >( wglGetProcAddress( p_strName.c_str() ) );

			if ( p_func && !p_strExt.empty() )
			{
				p_func = reinterpret_cast< Func >( wglGetProcAddress( ( p_strName + p_strExt ).c_str() ) );
			}

			return p_func != NULL;
		}

#if DEF_HAS_VARIADIC_TEMPLATES
		template< typename Ret, typename ... Arguments >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( Arguments... ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( Arguments... );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#else
		template< typename Ret >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret() > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )();
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8, T9 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 ) > & p_func )
		{
			typedef Ret( CALLBACK * PFNType )( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 );
			PFNType l_pfnResult = NULL;

			if ( GetFunction( p_strName, p_strExt, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#endif
	}

	CContext::CContext( HWND window )
		: m_window( window )
	{
		m_dc = ::GetDC( m_window );
		m_context = DoCreateContext();
		
		m_pfnGenTextures = ::glGenTextures;
		m_pfnDeleteTextures = ::glDeleteTextures;

		gl_api::GetFunction( "glActiveTexture", "", m_pfnActiveTexture );
		gl_api::GetFunction( "glDrawBuffers", "ARB", m_pfnDrawBuffers );
		gl_api::GetFunction( "glBlitFramebuffer", "ARB", m_pfnBlitFramebuffer );
		gl_api::GetFunction( "glGenRenderbuffers", "ARB", m_pfnGenRenderbuffers );
		gl_api::GetFunction( "glDeleteRenderbuffers", "ARB", m_pfnDeleteRenderbuffers );
		gl_api::GetFunction( "glBindRenderbuffer", "ARB", m_pfnBindRenderbuffer );
		gl_api::GetFunction( "glRenderbufferStorage", "ARB", m_pfnRenderbufferStorage );
		gl_api::GetFunction( "glRenderbufferStorageMultisample", "ARB", m_pfnRenderbufferStorageMultisample );
		gl_api::GetFunction( "glGetRenderbufferParameteriv", "ARB", m_pfnGetRenderbufferParameteriv );
		gl_api::GetFunction( "glFramebufferRenderbuffer", "ARB", m_pfnFramebufferRenderbuffer );
		gl_api::GetFunction( "glGenFramebuffers", "ARB", m_pfnGenFramebuffers );
		gl_api::GetFunction( "glDeleteFramebuffers", "ARB", m_pfnDeleteFramebuffers );
		gl_api::GetFunction( "glBindFramebuffer", "ARB", m_pfnBindFramebuffer );
		gl_api::GetFunction( "glFramebufferTexture", "ARB", m_pfnFramebufferTexture );
		gl_api::GetFunction( "glFramebufferTexture1D", "ARB", m_pfnFramebufferTexture1D );
		gl_api::GetFunction( "glFramebufferTexture2D", "ARB", m_pfnFramebufferTexture2D );
		gl_api::GetFunction( "glFramebufferTexture3D", "ARB", m_pfnFramebufferTexture3D );
		gl_api::GetFunction( "glFramebufferTextureLayer", "ARB", m_pfnFramebufferTextureLayer );
		gl_api::GetFunction( "glCheckFramebufferStatus", "ARB", m_pfnCheckFramebufferStatus );
	}

	CContext::~CContext()
	{
		::ReleaseDC( m_window, m_dc );
		wglDeleteContext( m_context );
	}

	void CContext::MakeCurrent()
	{
		wglMakeCurrent( m_dc, m_context );
	}

	void CContext::EndCurrent()
	{
		wglMakeCurrent( m_dc, 0 );
	}

	HWND CContext::GetWindow()const
	{
		return m_window;
	}

	void CContext::GenFramebuffers( GLsizei n, GLuint* framebuffers )
	{
		m_pfnGenFramebuffers( n, framebuffers );
	}

	void CContext::DeleteFramebuffers( GLsizei n, GLuint const * framebuffers )
	{
		m_pfnDeleteFramebuffers( n, framebuffers );
	}

	void CContext::BindFramebuffer( uint32_t target, GL2D_GL_FRAMEBUFFER_MODE framebuffer )
	{
		m_pfnBindFramebuffer( target, framebuffer );
	}

	uint32_t CContext::CheckFramebufferStatus( uint32_t target )
	{
		return m_pfnCheckFramebufferStatus( target );
	}

	void CContext::FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture( target, attachment, texture, level );
	}

	void CContext::FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture1D( target, attachment, textarget, texture, level );
	}

	void CContext::FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture2D( target, attachment, textarget, texture, level );
	}

	void CContext::FramebufferTextureLayer( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer )
	{
		m_pfnFramebufferTextureLayer( target, attachment, texture, level, layer );
	}

	void CContext::FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer )
	{
		m_pfnFramebufferTexture3D( target, attachment, textarget, texture, level, layer );
	}

	void CContext::BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter )
	{
		m_pfnBlitFramebuffer( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
	}

	void CContext::DrawBuffers( int n, uint32_t const * bufs )
	{
		m_pfnDrawBuffers( n, bufs );
	}

	void CContext::GenTextures( GLsizei n, GLuint* textures  )
	{
		m_pfnGenTextures( n, textures );
	}

	void CContext::DeleteTextures( GLsizei n, GLuint const * textures  )
	{
		m_pfnDeleteTextures( n, textures );
	}

	void CContext::ActiveTexture( uint32_t texture )
	{
		m_pfnActiveTexture( texture );
	}

	void CContext::FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId )
	{
		m_pfnFramebufferRenderbuffer( target, attachmentPoint, renderbufferTarget, renderbufferId );
	}

	void CContext::GenRenderbuffers( GLsizei n, GLuint * ids )
	{
		m_pfnGenRenderbuffers( n, ids );
	}

	void CContext::DeleteRenderbuffers( GLsizei n, GLuint const * ids )
	{
		m_pfnDeleteRenderbuffers( n, ids );
	}

	void CContext::BindRenderbuffer( uint32_t target, uint32_t id )
	{
		m_pfnBindRenderbuffer( target, id );
	}

	void CContext::RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height )
	{
		m_pfnRenderbufferStorage( target, internalFormat, width, height );
	}

	void CContext::RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height )
	{
		m_pfnRenderbufferStorageMultisample( target, isamples, internalFormat, width, height );
	}

	void CContext::TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations )
	{
		m_pfnTexImage2DMultisample( target, samples, internalformat, width, height, fixedsamplelocations );
	}

	void CContext::GetRenderbufferParameteriv( uint32_t target, uint32_t param, int* value )
	{
		m_pfnGetRenderbufferParameteriv( target, param, value );
	}

	HGLRC CContext::DoCreateContext()
	{
		HGLRC l_hReturn = NULL;

		if ( DoSelectPixelFormat() )
		{
			l_hReturn = wglCreateContext( m_dc );
		}

		return l_hReturn;
	}

	bool CContext::DoSelectPixelFormat()
	{
		bool result = false;
		PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int pixelFormats = ::ChoosePixelFormat( m_dc, &pfd );

		if ( pixelFormats )
		{
			result = ::SetPixelFormat( m_dc, pixelFormats, &pfd ) != FALSE;
		}
		else
		{
			std::cout << "SetPixelFormat failed : " << std::endl;
		}

		return result;
	}
}
