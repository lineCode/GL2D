#ifndef ___OGL2D_OBJECT_H___
#define ___OGL2D_OBJECT_H___

#include "OpenGL2DPrerequisites.h"
#include <cassert>
#include <functional>

namespace GL2D
{
	typedef std::function< void __stdcall ( GLsizei, GLuint * ) > Ctor;
	typedef std::function< void __stdcall ( GLsizei, const GLuint * ) > Dtor;

	class CObject
	{
	public:
		CObject( Ctor const & ctor, Dtor const & dtor )
			: m_name( GL_INVALID_INDEX )
			, m_ctor( ctor )
			, m_dtor( dtor )
		{
			m_ctor( 1, &m_name );
			assert( m_name != GL_INVALID_INDEX );
		}

		virtual ~CObject()
		{
			m_dtor( 1, &m_name );
		}

		inline GLuint GetName()
		{
			return m_name;
		}

	private:
		Ctor m_ctor;
		Dtor m_dtor;

	protected:
		GLuint m_name;
	};
}

#endif
