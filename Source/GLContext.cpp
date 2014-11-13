#include "stdafx.h"

#include "GLContext.h"

#define BUFFER_OFFSET( x ) ( ( const GLvoid * )( x ) )

namespace GL2D
{
	namespace gl_api
	{
		template< typename Func >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, Func & p_func )
		{
			p_func = reinterpret_cast< Func >( wglGetProcAddress( p_strName.c_str() ) );

			if ( !p_func && !p_strExt.empty() )
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

	std::recursive_mutex CContext::m_mutex;
	std::map< std::thread::id, CContext * > CContext::m_activeContexts;

	CContext::CContext( HWND window )
		: m_window( window )
		, m_previous( NULL )
	{
		m_dc = ::GetDC( m_window );
		m_context = DoCreateContext();
		
		MakeCurrent();
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
		gl_api::GetFunction( "glGenBuffers", "ARB", m_pfnGenBuffers );
		gl_api::GetFunction( "glDeleteBuffers", "ARB", m_pfnDeleteBuffers );
		gl_api::GetFunction( "glBindBuffer", "ARB", m_pfnBindBuffer );
		gl_api::GetFunction( "glBufferData", "ARB", m_pfnBufferData );
		gl_api::GetFunction( "glCreateShader", "ARB", m_pfnCreateShader );
		gl_api::GetFunction( "glDeleteShader", "ARB", m_pfnDeleteShader );
		gl_api::GetFunction( "glShaderSource", "ARB", m_pfnShaderSource );
		gl_api::GetFunction( "glCompileShader", "ARB", m_pfnCompileShader );
		gl_api::GetFunction( "glGetShaderiv", "ARB", m_pfnGetShaderiv );
		gl_api::GetFunction( "glGetShaderInfoLog", "ARB", m_pfnGetShaderInfoLog );
		gl_api::GetFunction( "glAttachShader", "ARB", m_pfnAttachShader );
		gl_api::GetFunction( "glCreateProgram", "ARB", m_pfnCreateProgram );
		gl_api::GetFunction( "glDeleteProgram", "ARB", m_pfnDeleteProgram );
		gl_api::GetFunction( "glAttachShader", "ARB", m_pfnAttachShader );
		gl_api::GetFunction( "glLinkProgram", "ARB", m_pfnLinkProgram );
		gl_api::GetFunction( "glGetProgramiv", "ARB", m_pfnGetProgramiv );
		gl_api::GetFunction( "glGetProgramInfoLog", "ARB", m_pfnGetProgramInfoLog );
		gl_api::GetFunction( "glGetUniformLocation", "ARB", m_pfnGetUniformLocation );
		gl_api::GetFunction( "glUniform1i", "ARB", m_pfnUniform1i );
		gl_api::GetFunction( "glGetAttribLocation", "ARB", m_pfnGetAttribLocation );
		gl_api::GetFunction( "glUseProgram", "ARB", m_pfnUseProgram );
		gl_api::GetFunction( "glVertexAttribPointer", "ARB", m_pfnVertexAttribPointer );
		
		std::string vssrc;
		vssrc += "#version 130\n";
		vssrc += "\n";
		vssrc += "in vec4 vertex;\n";
		vssrc += "in vec2 texture;\n";
		vssrc += "out vec2 vtx_texture;\n";
		vssrc += "\n";
		vssrc += "void main()\n";
		vssrc += "{\n";
		vssrc += "    gl_Position = vertex;\n";
		vssrc += "    vtx_texture = texture;\n";
		vssrc += "}\n";
		GLuint vs = DoCreateShader( vssrc, GL2D_GL_SHADER_TYPE_VERTEX );
		
		std::string fssrc;
		fssrc += "#version 130\n";
		fssrc += "\n";
		fssrc += "uniform sampler2D diffuse;\n";
		fssrc += "in vec2 vtx_texture;\n";
		fssrc += "out vec4 pxl_fragColor;\n";
		fssrc += "\n";
		fssrc += "void main()\n";
		fssrc += "{\n";
		fssrc += "    pxl_fragColor = texture( diffuse, vtx_texture );\n";
		fssrc += "}\n";
		GLuint fs = DoCreateShader( fssrc, GL2D_GL_SHADER_TYPE_FRAGMENT );
		
		HRESULT hr = ( fs != GL_INVALID_INDEX && vs != GL_INVALID_INDEX ) ? S_OK : E_FAIL;

		if ( hr == S_OK )
		{
			m_program = m_pfnCreateProgram();
			hr = glGetLastError( "CreateProgram" );
		}

		if ( hr == S_OK )
		{
			m_pfnAttachShader( m_program, vs );
			hr = glGetLastError( "AttachShader" );
		}

		if ( hr == S_OK )
		{
			m_pfnAttachShader( m_program, fs );
			hr = glGetLastError( "AttachShader" );
		}

		if ( hr == S_OK )
		{
			m_pfnLinkProgram( m_program );
			hr = glGetLastError( "LinkProgram" );
		}

		if ( hr == S_OK )
		{
			int linked = 0;
			m_pfnGetProgramiv( m_program, GL2D_GL_PROGRAM_QUERY_LINK_STATUS, &linked );
			hr = glGetLastError( "GetProgramiv" );
			int infologLength = 0;
			int charsWritten  = 0;
			m_pfnGetProgramiv( m_program, GL2D_GL_PROGRAM_QUERY_INFO_LOG_LENGTH, &infologLength );

			if ( infologLength > 0 )
			{
				char * infoLog = new char[infologLength];
				m_pfnGetProgramInfoLog( m_program, infologLength, &charsWritten, infoLog );
				hr = glGetLastError( "GetProgramInfoLog" );
				std::cout << infoLog << std::endl;
				delete [] infoLog;
			}
		}

		if ( hr == S_OK )
		{
			m_sampler = m_pfnGetUniformLocation( m_program, "diffuse" );
		}

		if ( hr == S_OK )
		{
			m_vertex = m_pfnGetAttribLocation( m_program, "texture" );
		}

		if ( hr == S_OK )
		{
			m_texture = m_pfnGetAttribLocation( m_program, "vertex" );
		}

		if ( vs != GL_INVALID_INDEX )
		{
			m_pfnDeleteShader( vs );
		}

		if ( fs != GL_INVALID_INDEX )
		{
			m_pfnDeleteShader( fs );
		}

		hr = GenBuffers( 1, &m_buffer );

		if ( hr == S_OK )
		{
			hr = BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, m_buffer );
		}

		if ( hr == S_OK )
		{
			float quad[16] =
			{
				0, 0, 0, 0,
				1, 0, 1, 0,
				1, 1, 1, 1,
				0, 1, 0, 1
			};

			hr = BufferData( GL2D_GL_BUFFER_TARGET_ARRAY, sizeof( quad ), quad, GL2D_GL_BUFFER_USAGE_STATIC_DRAW );
		}

		if ( hr == S_OK )
		{
			hr = BindBuffer( GL2D_GL_BUFFER_TARGET_ARRAY, 0 );
		}

		EndCurrent();

		if ( hr != S_OK )
		{
			throw std::exception( "Can't create context shader program" );
		}
	}

	CContext::~CContext()
	{
		DoCleanup();
	}

	HRESULT CContext::MakeCurrent()
	{
		wglMakeCurrent( m_dc, m_context );

		m_mutex.lock();
		std::map< std::thread::id, CContext * >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it != m_activeContexts.end() )
		{
			m_previous = it->second;
		}

		m_activeContexts[std::this_thread::get_id()] = this;
		m_mutex.unlock();
		return glGetLastError( "MakeCurrent" );
	}

	HRESULT CContext::EndCurrent()
	{
		m_mutex.lock();
		m_activeContexts[std::this_thread::get_id()] = m_previous;

		if ( m_previous )
		{
			wglMakeCurrent( m_dc, m_previous->m_context );
			m_previous = NULL;
		}
		else
		{
			wglMakeCurrent( m_dc, NULL );
		}
		
		m_mutex.unlock();
		return S_OK;
	}

	HWND CContext::GetWindow()const
	{
		return m_window;
	}

	int CContext::GetInt( GLenum param )
	{
		m_mutex.lock();
		std::map< std::thread::id, CContext * >::iterator it = m_activeContexts.find( std::this_thread::get_id() );

		if ( it == m_activeContexts.end() )
		{
			MakeCurrent();
		}

		GLint value = 0;
		glGetIntegerv( param, &value );

		if ( it == m_activeContexts.end() )
		{
			EndCurrent();
		}
		
		m_mutex.unlock();
		return value;
	}

	HRESULT CContext::GenFramebuffers( GLsizei n, GLuint* framebuffers )
	{
		m_pfnGenFramebuffers( n, framebuffers );
		return glGetLastError( "GenFramebuffers" );
	}

	HRESULT CContext::DeleteFramebuffers( GLsizei n, GLuint const * framebuffers )
	{
		m_pfnDeleteFramebuffers( n, framebuffers );
		return glGetLastError( "DeleteFramebuffers" );
	}

	HRESULT CContext::BindFramebuffer( GL2D_GL_FRAMEBUFFER_MODE target, uint32_t framebuffer )
	{
		m_pfnBindFramebuffer( target, framebuffer );
		return glGetLastError( "BindFramebuffer" );
	}

	uint32_t CContext::CheckFramebufferStatus( uint32_t target )
	{
		return m_pfnCheckFramebufferStatus( target );
	}

	HRESULT CContext::FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture( target, attachment, texture, level );
		return glGetLastError( "FramebufferTexture" );
	}

	HRESULT CContext::FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture1D( target, attachment, textarget, texture, level );
		return glGetLastError( "FramebufferTexture1D" );
	}

	HRESULT CContext::FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level )
	{
		m_pfnFramebufferTexture2D( target, attachment, textarget, texture, level );
		return glGetLastError( "FramebufferTexture2D" );
	}

	HRESULT CContext::FramebufferTextureLayer( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer )
	{
		m_pfnFramebufferTextureLayer( target, attachment, texture, level, layer );
		return glGetLastError( "FramebufferTextureLayer" );
	}

	HRESULT CContext::FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer )
	{
		m_pfnFramebufferTexture3D( target, attachment, textarget, texture, level, layer );
		return glGetLastError( "FramebufferTexture3D" );
	}

	HRESULT CContext::BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter )
	{
		m_pfnBlitFramebuffer( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
		return glGetLastError( "BlitFramebuffer" );
	}

	HRESULT CContext::DrawBuffers( int n, uint32_t const * bufs )
	{
		m_pfnDrawBuffers( n, bufs );
		return glGetLastError( "DrawBuffers" );
	}

	HRESULT CContext::GenTextures( GLsizei n, GLuint* textures  )
	{
		m_pfnGenTextures( n, textures );
		return glGetLastError( "GenTextures" );
	}

	HRESULT CContext::DeleteTextures( GLsizei n, GLuint const * textures  )
	{
		m_pfnDeleteTextures( n, textures );
		return glGetLastError( "DeleteTextures" );
	}

	HRESULT CContext::ActiveTexture( uint32_t texture )
	{
		m_pfnActiveTexture( texture );
		return glGetLastError( "ActiveTexture" );
	}

	HRESULT CContext::FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId )
	{
		m_pfnFramebufferRenderbuffer( target, attachmentPoint, renderbufferTarget, renderbufferId );
		return glGetLastError( "FramebufferRenderbuffer" );
	}

	HRESULT CContext::GenRenderbuffers( GLsizei n, GLuint * ids )
	{
		m_pfnGenRenderbuffers( n, ids );
		return glGetLastError( "GenRenderbuffers" );
	}

	HRESULT CContext::DeleteRenderbuffers( GLsizei n, GLuint const * ids )
	{
		m_pfnDeleteRenderbuffers( n, ids );
		return glGetLastError( "DeleteRenderbuffers" );
	}

	HRESULT CContext::BindRenderbuffer( uint32_t target, uint32_t id )
	{
		m_pfnBindRenderbuffer( target, id );
		return glGetLastError( "BindRenderbuffer" );
	}

	HRESULT CContext::RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height )
	{
		m_pfnRenderbufferStorage( target, internalFormat, width, height );
		return glGetLastError( "RenderbufferStorage" );
	}

	HRESULT CContext::RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height )
	{
		m_pfnRenderbufferStorageMultisample( target, isamples, internalFormat, width, height );
		return glGetLastError( "RenderbufferStorageMultisample" );
	}

	HRESULT CContext::TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations )
	{
		m_pfnTexImage2DMultisample( target, samples, internalformat, width, height, fixedsamplelocations );
		return glGetLastError( "TexImage2DMultisample" );
	}

	HRESULT CContext::GetRenderbufferParameteriv( uint32_t target, uint32_t param, int* value )
	{
		m_pfnGetRenderbufferParameteriv( target, param, value );
		return glGetLastError( "GetRenderbufferParameteriv" );
	}

	HRESULT CContext::GenBuffers( GLsizei n, GLuint* buffers )
	{
		m_pfnGenBuffers( n, buffers );
		return glGetLastError( "GenBuffers" );
	}

	HRESULT CContext::DeleteBuffers( GLsizei n, GLuint const * buffers )
	{
		m_pfnDeleteBuffers( n, buffers );
		return glGetLastError( "DeleteBuffers" );
	}

	HRESULT CContext::BindBuffer( GL2D_GL_BUFFER_TARGET target, GLuint buffer )
	{
		m_pfnBindBuffer( target, buffer );
		return glGetLastError( "BindBuffer" );
	}

	HRESULT CContext::BufferData( GL2D_GL_BUFFER_TARGET target, ptrdiff_t size, const GLvoid * data, GL2D_GL_BUFFER_USAGE usage )
	{
		m_pfnBufferData( target, size, data, usage );
		return glGetLastError( "BufferData" );
	}

	HRESULT CContext::DrawTexture( GLuint name, const GL2D_RECT_F & destinationRectangle, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F & sourceRectangle )
	{
		GL2D_GL_TEXTURE_FILTER filter = GL2D_GL_TEXTURE_FILTER_NEAREST;

		if ( interpolationMode == GL2D_BITMAP_INTERPOLATION_MODE_LINEAR )
		{
			filter = GL2D_GL_TEXTURE_FILTER_LINEAR;
		}

		m_pfnUseProgram( m_program );
		HRESULT hr = glGetLastError( "UseProgram" );
		
		if ( hr == S_OK )
		{
			hr = ActiveTexture( GL_TEXTURE0 );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, name );
			hr = glGetLastError( "BindTexture" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
			hr = glGetLastError( "TexParameteri" );
		}

		if ( hr == S_OK )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
			hr = glGetLastError( "TexParameteri" );
		}

		if ( hr == S_OK )
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
			hr = glGetLastError( "BindTexture" );
		}

		if ( hr == S_OK )
		{
			m_pfnVertexAttribPointer( m_vertex, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), BUFFER_OFFSET( 0 ) );
			hr = glGetLastError( "VertexAttribPointer" );
		}

		if ( hr == S_OK )
		{
			m_pfnVertexAttribPointer( m_texture, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), BUFFER_OFFSET( 2 * sizeof( float ) ) );
			hr = glGetLastError( "VertexAttribPointer" );
		}

		if ( hr == S_OK )
		{
			glDrawArrays( GL_QUADS, 0, 4 );
			hr = glGetLastError( "DrawArrays" );
		}

		if ( hr == S_OK )
		{
			m_pfnUseProgram( 0 );
			hr = glGetLastError( "UseProgram" );
		}

		return hr;
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

	void CContext::DoCleanup()
	{
		if ( m_program != GL_INVALID_INDEX )
		{
			m_pfnDeleteProgram( m_program );
		}
		if ( m_buffer != GL_INVALID_INDEX )
		{
			m_pfnDeleteBuffers( 1, &m_buffer );
		}

		::ReleaseDC( m_window, m_dc );
		wglDeleteContext( m_context );
	}

	GLuint CContext::DoCreateShader( const std::string & source, GL2D_GL_SHADER_TYPE type )
	{
		GLuint shader = m_pfnCreateShader( type );
		HRESULT hr = glGetLastError( "CreateShader" );
		
		if ( hr == S_OK )
		{
			int l_iLength = int( source.size() );
			char * l_pszTmp = new char[source.size() + 1];
			strncpy_s( l_pszTmp, source.size() + 1, source.c_str(), source.size() );
			m_pfnShaderSource( shader, 1, const_cast< const char ** >( &l_pszTmp ), &l_iLength );
			hr = glGetLastError( "ShaderSource" );

			if ( hr == S_OK )
			{
				m_pfnCompileShader( shader );
				hr = glGetLastError( "CompileShader" );
			}

			if ( hr == S_OK )
			{
				int compiled = 0;
				m_pfnGetShaderiv( shader, GL2D_GL_SHADER_QUERY_COMPILE_STATUS, &compiled );
				hr = glGetLastError( "GetShaderiv" );
				int infologLength = 0;
				int charsWritten  = 0;
				m_pfnGetShaderiv( shader, GL2D_GL_SHADER_QUERY_INFO_LOG_LENGTH, &infologLength );

				if ( infologLength > 0 )
				{
					char * infoLog = new char[infologLength];
					m_pfnGetShaderInfoLog( shader, infologLength, &charsWritten, infoLog );
					hr = glGetLastError( "GetShaderInfoLog" );
					std::cout << infoLog << std::endl;
					delete [] infoLog;
				}
			}

			if ( hr != S_OK )
			{
				m_pfnDeleteShader( shader );
				shader = GL_INVALID_INDEX;
			}
		}

		return shader;
	}
}
