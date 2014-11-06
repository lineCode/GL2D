#include "stdafx.h"

#include "GL2D.h"
#include "GLResource.h"
#include "GLFactory.h"

HRESULT WINAPI GL2DCreateFactory( GL2D_FACTORY_TYPE factoryType, REFIID riid, const GL2D_FACTORY_OPTIONS *pFactoryOptions, void **ppIFactory )
{
	HRESULT hr = E_POINTER;

	if ( ppIFactory )
	{
		*ppIFactory = GL2D::CFactory::CreateInstance();
	}

	return hr;
}

void WINAPI GL2DMakeRotateMatrix( float angle, GL2D_POINT_2F center, GL2D_MATRIX_3X2_F *matrix )
{
}

void WINAPI GL2DMakeSkewMatrix( float angleX, float angleY, GL2D_POINT_2F center, GL2D_MATRIX_3X2_F *matrix )
{
}

bool WINAPI GL2DIsMatrixInvertible( const GL2D_MATRIX_3X2_F *matrix )
{
	return false;
}

bool WINAPI GL2DInvertMatrix( _Inout_ GL2D_MATRIX_3X2_F *matrix )
{
	return false;
}
