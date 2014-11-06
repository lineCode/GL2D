#include "stdafx.h"

#include "OpenGL.h"

namespace GL2D
{
	namespace gl_api
	{
		template< typename Func >
		bool GetFunction( std::string const & p_strName, Func & p_func )
		{
#if defined( _WIN32 )
			p_func = reinterpret_cast< Func >( wglGetProcAddress( p_strName.c_str() ) );
#else
			p_func = reinterpret_cast< Func >( glXGetProcAddress( (GLubyte const *)p_strName.c_str() );
#endif
			return p_func != NULL;
		}
#if DEF_HAS_VARIADIC_TEMPLATES
		template< typename Ret, typename ... Arguments >
		bool GetFunction( std::string const & p_strName, std::function< Ret( Arguments... ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( Arguments... );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#else
		template< typename Ret >
		bool GetFunction( std::string const & p_strName, std::function< Ret() > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)();
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5, T6 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5, T6 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5, T6, T7 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5, T6, T7 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5, T6, T7, T8 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5, T6, T7, T8, T9 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}

		template< typename Ret, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		bool GetFunction( std::string const & p_strName, std::function< Ret( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 ) > & p_func )
		{
			typedef Ret(CALLBACK * PFNType)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 );
			PFNType l_pfnResult = NULL;

			if( GetFunction( p_strName, l_pfnResult ) )
			{
				p_func = l_pfnResult;
			}

			return l_pfnResult != NULL;
		}
#endif
	}

	void InitialiseOpenGL()
	{
#define GL_GET_FUNC( func, ext )\
		if( !gl_api::GetFunction( std::string( "gl" ) + #func, gl##func ) )\
		{\
			if( !gl_api::GetFunction( std::string( "gl" ) + std::string( #func ) + std::string( #ext ), gl##func ) )\
			{\
				std::cerr << "Unable to retrieve function gl" << #func << std::endl;\
			}\
		}

		GL_GET_FUNC( ActiveTexture,							);

		GL_GET_FUNC( DrawBuffers,						ARB	);
		GL_GET_FUNC( BlitFramebuffer,					ARB	);
		GL_GET_FUNC( GenRenderbuffers,					ARB	);
		GL_GET_FUNC( DeleteRenderbuffers,				ARB	);
		GL_GET_FUNC( BindRenderbuffer,					ARB	);
		GL_GET_FUNC( RenderbufferStorage,				ARB	);
		GL_GET_FUNC( RenderbufferStorageMultisample,	ARB	);
		GL_GET_FUNC( GetRenderbufferParameteriv,		ARB	);
		GL_GET_FUNC( FramebufferRenderbuffer,			ARB	);
		GL_GET_FUNC( GenFramebuffers,					ARB	);
		GL_GET_FUNC( DeleteFramebuffers,				ARB	);
		GL_GET_FUNC( BindFramebuffer,					ARB	);
		GL_GET_FUNC( FramebufferTexture,				ARB	);
		GL_GET_FUNC( FramebufferTexture1D,				ARB	);
		GL_GET_FUNC( FramebufferTexture2D,				ARB	);
		GL_GET_FUNC( FramebufferTexture3D,				ARB	);
		GL_GET_FUNC( FramebufferTextureLayer,			ARB	);
		GL_GET_FUNC( CheckFramebufferStatus,			ARB	);

#undef GL_GET_FUNC
	}
}