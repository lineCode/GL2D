#ifndef ___OGL2D_BASE_TYPES_H___
#define ___OGL2D_BASE_TYPES_H___

#include <cstdint>
#include <dwrite.h>

template< typename T >
struct GL2D_SIZE
{
	T width;
	T height;
};

typedef GL2D_SIZE< uint32_t > GL2D_SIZE_U;
typedef GL2D_SIZE< int32_t > GL2D_SIZE_I;
typedef GL2D_SIZE< float > GL2D_SIZE_F;
	
template< typename T >
struct GL2D_POINT2
{
	T x;
	T y;
};

typedef GL2D_POINT2< uint32_t > GL2D_POINT_2U;
typedef GL2D_POINT2< int32_t > GL2D_POINT_2I;
typedef GL2D_POINT2< float > GL2D_POINT_2F;
	
template< typename T >
struct GL2D_RECT
{
	T left;
	T top;
	T right;
	T bottom;
};

typedef GL2D_RECT< uint32_t > GL2D_RECT_U;
typedef GL2D_RECT< int32_t > GL2D_RECT_I;
typedef GL2D_RECT< float > GL2D_RECT_F;

template< typename T >
struct GL2D_COLOR
{
	T r;
	T g;
	T b;
	T a;
};

typedef GL2D_COLOR< uint32_t > GL2D_COLOR_U;
typedef GL2D_COLOR< int32_t > GL2D_COLOR_I;
typedef GL2D_COLOR< float > GL2D_COLOR_F;
	
template< typename T >
struct GL2D_MATRIX_3X2
{
	union
	{
		struct 
		{
			T _11, _12;
			T _21, _22;
			T _31, _32;
		};

		T m[3][2];
	};
};

typedef GL2D_MATRIX_3X2< uint32_t > GL2D_MATRIX_3X2_U;
typedef GL2D_MATRIX_3X2< int32_t > GL2D_MATRIX_3X2_I;
typedef GL2D_MATRIX_3X2< float > GL2D_MATRIX_3X2_F;
	
template< typename T >
struct GL2D_MATRIX_4X3
{
	union
	{
		struct 
		{
			T _11, _12, _13;
			T _21, _22, _23;
			T _31, _32, _33;
			T _41, _42, _43;
		};

		T m[4][3];
	};
};

typedef GL2D_MATRIX_4X3< uint32_t > GL2D_MATRIX_4x3_U;
typedef GL2D_MATRIX_4X3< int32_t > GL2D_MATRIX_4x3_I;
typedef GL2D_MATRIX_4X3< float > GL2D_MATRIX_4x3_F;
	
template< typename T >
struct GL2D_MATRIX_4X4
{
	union
	{
		struct 
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
		};

		T m[4][4];
	};
};
	
template< typename T >
struct GL2D_MATRIX_5X4
{
	union
	{
		struct 
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
			T _51, _52, _53, _54;
		};

		T m[5][4];
	};
};

typedef uint64_t GL2D_TAG;

#endif // ___OGL2D_BASE_TYPES_H___
