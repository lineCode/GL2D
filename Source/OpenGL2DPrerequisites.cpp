#include "stdafx.h"

#include "OpenGL2DPrerequisites.h"

namespace GL2D
{
	HRESULT glGetLastError( char const * const name )
	{
		GLenum err = glGetError();

		if ( err )
		{
			err -= GL_INVALID_ENUM;
			static std::string errors[] =
			{
				"INVALID_ENUM",
				"INVALID_VALUE",
				"INVALID_OPERATIONE",
				"STACK_OVERFLOW",
				"STACK_UNDERFLOW",
				"OUT_OF_MEMORY",
				"INVALID_FRAMEBUFFER_OPERATION",
				"CONTEXT_LOST",
			};

			std::cout << name << " failed (" << errors[err] << ")" << std::endl;
		}

		return err ? E_FAIL : S_OK;
	}
}
