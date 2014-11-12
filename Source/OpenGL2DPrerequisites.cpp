#include "stdafx.h"

#include "OpenGL2DPrerequisites.h"

namespace GL2D
{
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
