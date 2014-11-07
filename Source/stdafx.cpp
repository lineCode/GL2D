#include "stdafx.h"

#include "OpenGL.h"

namespace GL2D
{
	namespace gl_api
	{
		template< typename Func >
		bool GetFunction( std::string const & p_strName, std::string const & p_strExt, Func & p_func )
		{
#if defined( _WIN32 )
			p_func = reinterpret_cast< Func >( wglGetProcAddress( p_strName.c_str() ) );
#else
			p_func = reinterpret_cast< Func >( glXGetProcAddressARB( ( GLubyte const * )p_strName.c_str() ) );
#endif
			if ( p_func && !p_strExt.empty() )
			{
#if defined( _WIN32 )
				p_func = reinterpret_cast< Func >( wglGetProcAddress( ( p_strName + p_strExt ).c_str() ) );
#else
				p_func = reinterpret_cast< Func >( glXGetProcAddressARB( ( GLubyte const * )( p_strName + p_strExt ).c_str() ) );
#endif
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

	void InitialiseOpenGL()
	{
		gl_api::GetFunction( "glActiveTexture", "", glActiveTexture );
		gl_api::GetFunction( "glDrawBuffers", "ARB", glDrawBuffers );
		gl_api::GetFunction( "glBlitFramebuffer", "ARB", glBlitFramebuffer );
		gl_api::GetFunction( "glGenRenderbuffers", "ARB", glGenRenderbuffers );
		gl_api::GetFunction( "glDeleteRenderbuffers", "ARB", glDeleteRenderbuffers );
		gl_api::GetFunction( "glBindRenderbuffer", "ARB", glBindRenderbuffer );
		gl_api::GetFunction( "glRenderbufferStorage", "ARB", glRenderbufferStorage );
		gl_api::GetFunction( "glRenderbufferStorageMultisample", "ARB", glRenderbufferStorageMultisample );
		gl_api::GetFunction( "glGetRenderbufferParameteriv", "ARB", glGetRenderbufferParameteriv );
		gl_api::GetFunction( "glFramebufferRenderbuffer", "ARB", glFramebufferRenderbuffer );
		gl_api::GetFunction( "glGenFramebuffers", "ARB", glGenFramebuffers );
		gl_api::GetFunction( "glDeleteFramebuffers", "ARB", glDeleteFramebuffers );
		gl_api::GetFunction( "glBindFramebuffer", "ARB", glBindFramebuffer );
		gl_api::GetFunction( "glFramebufferTexture", "ARB", glFramebufferTexture );
		gl_api::GetFunction( "glFramebufferTexture1D", "ARB", glFramebufferTexture1D );
		gl_api::GetFunction( "glFramebufferTexture2D", "ARB", glFramebufferTexture2D );
		gl_api::GetFunction( "glFramebufferTexture3D", "ARB", glFramebufferTexture3D );
		gl_api::GetFunction( "glFramebufferTextureLayer", "ARB", glFramebufferTextureLayer );
		gl_api::GetFunction( "glCheckFramebufferStatus", "ARB", glCheckFramebufferStatus );
	}

	HRESULT glGetLastError( char const * const name )
	{
		GLenum err = glGetError();

		if ( err )
		{
			std::cout << name << " failed" << std::endl;
		}

		return err ? E_FAIL : S_OK;
	}
}