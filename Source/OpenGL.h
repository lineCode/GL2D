#ifndef ___OGL2D_OPENGL_H___
#define ___OGL2D_OPENGL_H___

#include <Windows.h>
#include <gl/GL.h>
#include <functional>
#include <cstdint>

#if _MSC_VER > 1700
#	define DEF_HAS_VARIADIC_TEMPLATES	1
#else
#	define DEF_HAS_VARIADIC_TEMPLATES	0
#endif

static const GLuint GL_INVALID_INDEX = 0xFFFFFFFF;

typedef enum GL2D_GL_FRAMEBUFFER_STATUS : unsigned int
{	GL2D_GL_FRAMEBUFFER_COMPLETE						= 0x8CD5
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT			= 0x8CD6
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	= 0x8CD7
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER			= 0x8CDB
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER			= 0x8CDC
,	GL2D_GL_FRAMEBUFFER_UNSUPPORTED						= 0x8CDD
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE			= 0x8D56
,	GL2D_GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS		= 0x8DA8
}	GL2D_GL_FRAMEBUFFER_STATUS;

typedef enum GL2D_GL_TEXTURE_ATTACHMENT : unsigned int
{	GL2D_GL_TEXTURE_ATTACHMENT_NONE		= 0
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR0	= 0x8CE0
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR1	= 0x8CE1
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR2	= 0x8CE2
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR3	= 0x8CE3
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR4	= 0x8CE4
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR5	= 0x8CE5
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR6	= 0x8CE6
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR7	= 0x8CE7
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR8	= 0x8CE8
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR9	= 0x8CE9
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR10	= 0x8CEA
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR11	= 0x8CEB
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR12	= 0x8CEC
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR13	= 0x8CED
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR14	= 0x8CEE
,	GL2D_GL_TEXTURE_ATTACHMENT_COLOR15	= 0x8CEF
,	GL2D_GL_TEXTURE_ATTACHMENT_DEPTH	= 0x8D00
,	GL2D_GL_TEXTURE_ATTACHMENT_STENCIL	= 0x8D20
}	GL2D_GL_TEXTURE_ATTACHMENT;

typedef enum GL2D_GL_FRAMEBUFFER_MODE : unsigned int
{	GL2D_GL_FRAMEBUFFER_MODE_READ		= 0x8CA8
,	GL2D_GL_FRAMEBUFFER_MODE_DRAW		= 0x8CA9
,	GL2D_GL_FRAMEBUFFER_MODE_DEFAULT	= 0x8D40
}	GL2D_GL_FRAMEBUFFER_MODE;

typedef enum GL2D_GL_RENDERBUFFER_MODE : unsigned int
{	GL2D_GL_RENDERBUFFER_MODE_DEFAULT	= 0x8D41
}	GL2D_GL_RENDERBUFFER_MODE;

typedef enum GL2D_GL_RENDERBUFFER_ATTACHMENT : unsigned int
{	GL2D_GL_RENDERBUFFER_ATTACHMENT_NONE	= 0
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR0	= 0x8CE0
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR1	= 0x8CE1
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR2	= 0x8CE2
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR3	= 0x8CE3
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR4	= 0x8CE4
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR5	= 0x8CE5
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR6	= 0x8CE6
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR7	= 0x8CE7
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR8	= 0x8CE8
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR9	= 0x8CE9
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR10	= 0x8CEA
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR11	= 0x8CEB
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR12	= 0x8CEC
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR13	= 0x8CED
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR14	= 0x8CEE
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_COLOR15	= 0x8CEF
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_DEPTH	= 0x8D00
,	GL2D_GL_RENDERBUFFER_ATTACHMENT_STENCIL	= 0x8D20
}	GL2D_GL_RENDERBUFFER_ATTACHMENT;

typedef enum GL2D_GL_RENDERBUFFER_PARAMETER : unsigned int
{	GL2D_GL_RENDERBUFFER_PARAMETER_WIDTH			= 0x8D42
,	GL2D_GL_RENDERBUFFER_PARAMETER_HEIGHT			= 0x8D43
,	GL2D_GL_RENDERBUFFER_PARAMETER_INTERNAL_FORMAT	= 0x8D44
,	GL2D_GL_RENDERBUFFER_PARAMETER_RED_SIZE			= 0x8D50
,	GL2D_GL_RENDERBUFFER_PARAMETER_GREEN_SIZE		= 0x8D51
,	GL2D_GL_RENDERBUFFER_PARAMETER_BLUE_SIZE		= 0x8D52
,	GL2D_GL_RENDERBUFFER_PARAMETER_ALPHA_SIZE		= 0x8D53
,	GL2D_GL_RENDERBUFFER_PARAMETER_DEPTH_SIZE		= 0x8D54
,	GL2D_GL_RENDERBUFFER_PARAMETER_STENCIL_SIZE		= 0x8D55
}	GL2D_GL_RENDERBUFFER_PARAMETER;

typedef enum GL2D_GL_RENDERBUFFER_STORAGE : unsigned int
{	GL2D_GL_RENDERBUFFER_STORAGE_L8			= 0x8229
,	GL2D_GL_RENDERBUFFER_STORAGE_L16F		= 0x822D
,	GL2D_GL_RENDERBUFFER_STORAGE_L32F		= 0x822E
,	GL2D_GL_RENDERBUFFER_STORAGE_A8L8		= 0x822C
,	GL2D_GL_RENDERBUFFER_STORAGE_AL16F		= 0x822F
,	GL2D_GL_RENDERBUFFER_STORAGE_AL32F		= 0x8230
,	GL2D_GL_RENDERBUFFER_STORAGE_RGB5_A1	= 0x8057
,	GL2D_GL_RENDERBUFFER_STORAGE_RGBA4		= 0x8056
,	GL2D_GL_RENDERBUFFER_STORAGE_RGB565		= 0x8D62
,	GL2D_GL_RENDERBUFFER_STORAGE_RGB8		= 0x8051
,	GL2D_GL_RENDERBUFFER_STORAGE_RGBA8		= 0x8058
,	GL2D_GL_RENDERBUFFER_STORAGE_RGB16F		= 0x881B
,	GL2D_GL_RENDERBUFFER_STORAGE_RGBA16F	= 0x881A
,	GL2D_GL_RENDERBUFFER_STORAGE_RGB32F		= 0x8815
,	GL2D_GL_RENDERBUFFER_STORAGE_RGBA32F	= 0x8814
,	GL2D_GL_RENDERBUFFER_STORAGE_DXTC1		= 0x83F1
,	GL2D_GL_RENDERBUFFER_STORAGE_DXTC3		= 0x83F2
,	GL2D_GL_RENDERBUFFER_STORAGE_DXTC5		= 0x83F3
,	GL2D_GL_RENDERBUFFER_STORAGE_DEPTH16	= 0x81A5
,	GL2D_GL_RENDERBUFFER_STORAGE_DEPTH24	= 0x81A6
,	GL2D_GL_RENDERBUFFER_STORAGE_DEPTH32	= 0x81A7
,	GL2D_GL_RENDERBUFFER_STORAGE_STENCIL1	= 0x8D46
,	GL2D_GL_RENDERBUFFER_STORAGE_STENCIL4	= 0x8D47
,	GL2D_GL_RENDERBUFFER_STORAGE_STENCIL8	= 0x8D48
,	GL2D_GL_RENDERBUFFER_STORAGE_STENCIL16	= 0x8D49
}	GL2D_GL_RENDERBUFFER_STORAGE;

typedef enum GL2D_GL_FORMAT : unsigned int
{	GL2D_GL_FORMAT_STENCIL			= 0x1901
,	GL2D_GL_FORMAT_DEPTH			= 0x1902
,	GL2D_GL_FORMAT_RED				= 0x1903
,	GL2D_GL_FORMAT_GREEN			= 0x1904
,	GL2D_GL_FORMAT_BLUE				= 0x1905
,	GL2D_GL_FORMAT_ALPHA			= 0x1906
,	GL2D_GL_FORMAT_RGB				= 0x1907
,	GL2D_GL_FORMAT_RGBA				= 0x1908
,	GL2D_GL_FORMAT_LUMINANCE		= 0x1909
,	GL2D_GL_FORMAT_LUMINANCE_ALPHA	= 0x190A
,	GL2D_GL_FORMAT_BGR				= 0x80E0
,	GL2D_GL_FORMAT_BGRA				= 0x80E1
,	GL2D_GL_FORMAT_RG				= 0x8227
,	GL2D_GL_FORMAT_DEPTH_STENCIL	= 0x84F9
}	GL2D_GL_FORMAT;

typedef enum GL2D_GL_INTERNAL : unsigned int
{	GL2D_GL_INTERNAL_1							= 1
,	GL2D_GL_INTERNAL_2							= 2
,	GL2D_GL_INTERNAL_3							= 3
,	GL2D_GL_INTERNAL_4							= 4
,	GL2D_GL_INTERNAL_LUMINANCE					= 0x1909
,	GL2D_GL_INTERNAL_R3_G3_B2					= 0x2A10
,	GL2D_GL_INTERNAL_ALPHA4						= 0x803B
,	GL2D_GL_INTERNAL_ALPHA8						= 0x803C
,	GL2D_GL_INTERNAL_ALPHA12					= 0x803D
,	GL2D_GL_INTERNAL_ALPHA16					= 0x803E
,	GL2D_GL_INTERNAL_COMPRESSED_ALPHA			= 0x84E9
,	GL2D_GL_INTERNAL_COMPRESSED_LUMINANCE		= 0x84EA
,	GL2D_GL_INTERNAL_COMPRESSED_LUMINANCE_ALPHA	= 0x84EB
,	GL2D_GL_INTERNAL_COMPRESSED_INTENSITY		= 0x84EC
,	GL2D_GL_INTERNAL_COMPRESSED_RGB				= 0x84ED
,	GL2D_GL_INTERNAL_COMPRESSED_RGBA			= 0x84EE
,	GL2D_GL_INTERNAL_LUMINANCE4					= 0x803F
,	GL2D_GL_INTERNAL_LUMINANCE8					= 0x8040
,	GL2D_GL_INTERNAL_LUMINANCE12				= 0x8041
,	GL2D_GL_INTERNAL_LUMINANCE16				= 0x8042
,	GL2D_GL_INTERNAL_LUMINANCE4_ALPHA4			= 0x8043
,	GL2D_GL_INTERNAL_LUMINANCE6_ALPHA2			= 0x8044
,	GL2D_GL_INTERNAL_LUMINANCE8_ALPHA8			= 0x8045
,	GL2D_GL_INTERNAL_LUMINANCE12_ALPHA4			= 0x8046
,	GL2D_GL_INTERNAL_LUMINANCE12_ALPHA12		= 0x8047
,	GL2D_GL_INTERNAL_LUMINANCE16_ALPHA16		= 0x8048
,	GL2D_GL_INTERNAL_INTENSITY					= 0x8049
,	GL2D_GL_INTERNAL_INTENSITY4					= 0x804A
,	GL2D_GL_INTERNAL_INTENSITY8					= 0x804B
,	GL2D_GL_INTERNAL_INTENSITY12				= 0x804C
,	GL2D_GL_INTERNAL_INTENSITY16				= 0x804D
,	GL2D_GL_INTERNAL_RGB4						= 0x804F
,	GL2D_GL_INTERNAL_RGB5						= 0x8050
,	GL2D_GL_INTERNAL_RGB8						= 0x8051
,	GL2D_GL_INTERNAL_RGB10						= 0x8052
,	GL2D_GL_INTERNAL_RGB12						= 0x8053
,	GL2D_GL_INTERNAL_RGB16						= 0x8054
,	GL2D_GL_INTERNAL_RGBA2						= 0x8055
,	GL2D_GL_INTERNAL_RGBA4						= 0x8056
,	GL2D_GL_INTERNAL_RGB5_A1					= 0x8057
,	GL2D_GL_INTERNAL_RGBA8						= 0x8058
,	GL2D_GL_INTERNAL_RGB10_A2					= 0x8059
,	GL2D_GL_INTERNAL_RGBA12						= 0x805A
,	GL2D_GL_INTERNAL_RGBA16						= 0x805B
,	GL2D_GL_INTERNAL_DEPTH_COMPONENT16			= 0x81A5
,	GL2D_GL_INTERNAL_DEPTH_COMPONENT24			= 0x81A6
,	GL2D_GL_INTERNAL_DEPTH_COMPONENT32			= 0x81A7
,	GL2D_GL_INTERNAL_R8							= 0x8229
,	GL2D_GL_INTERNAL_RG8						= 0x822B
,	GL2D_GL_INTERNAL_RG16						= 0x822C
,	GL2D_GL_INTERNAL_R16F						= 0x822D
,	GL2D_GL_INTERNAL_R32F						= 0x822E
,	GL2D_GL_INTERNAL_RG16F						= 0x822F
,	GL2D_GL_INTERNAL_RG32F						= 0x8230
,	GL2D_GL_INTERNAL_COMPRESSED_RGBA_S3TC_DXT1	= 0x83F1
,	GL2D_GL_INTERNAL_COMPRESSED_RGBA_S3TC_DXT3	= 0x83F2
,	GL2D_GL_INTERNAL_COMPRESSED_RGBA_S3TC_DXT5	= 0x83F3
,	GL2D_GL_INTERNAL_RGBA32F					= 0x8814
,	GL2D_GL_INTERNAL_RGB32F						= 0x8815
,	GL2D_GL_INTERNAL_RGBA16F					= 0x881A
,	GL2D_GL_INTERNAL_RGB16F						= 0x881B
,	GL2D_GL_INTERNAL_DEPTH24_STENCIL8			= 0x88F0
,	GL2D_GL_INTERNAL_SRGB						= 0x8C40
,	GL2D_GL_INTERNAL_SRGB8						= 0x8C41
,	GL2D_GL_INTERNAL_SRGB_ALPHA					= 0x8C42
,	GL2D_GL_INTERNAL_SRGB8_ALPHA8				= 0x8C43
,	GL2D_GL_INTERNAL_SLUMINANCE_ALPHA			= 0x8C44
,	GL2D_GL_INTERNAL_SLUMINANCE8_ALPHA8			= 0x8C45
,	GL2D_GL_INTERNAL_SLUMINANCE					= 0x8C46
,	GL2D_GL_INTERNAL_SLUMINANCE8				= 0x8C47
,	GL2D_GL_INTERNAL_DEPTH_COMPONENT32F			= 0x8CAC
,	GL2D_GL_INTERNAL_STENCIL_INDEX1				= 0x8D46
,	GL2D_GL_INTERNAL_STENCIL_INDEX4				= 0x8D47
,	GL2D_GL_INTERNAL_STENCIL_INDEX8				= 0x8D48
,	GL2D_GL_INTERNAL_STENCIL_INDEX16			= 0x8D49
}	GL2D_GL_INTERNAL;

typedef enum GL2D_GL_TYPE : unsigned int
{	GL2D_GL_TYPE_DEFAULT						= 0
,	GL2D_GL_TYPE_BYTE							= 0x1400
,	GL2D_GL_TYPE_UNSIGNED_BYTE					= 0x1401
,	GL2D_GL_TYPE_SHORT							= 0x1402
,	GL2D_GL_TYPE_UNSIGNED_SHORT					= 0x1403
,	GL2D_GL_TYPE_INT							= 0x1404
,	GL2D_GL_TYPE_UNSIGNED_INT					= 0x1405
,	GL2D_GL_TYPE_FLOAT							= 0x1406
,	GL2D_GL_TYPE_DOUBLE							= 0x140A
,	GL2D_GL_TYPE_BITMAP							= 0X1A00
,	GL2D_GL_TYPE_UNSIGNED_BYTE_3_3_2			= 0x8032
,	GL2D_GL_TYPE_UNSIGNED_SHORT_4_4_4_4			= 0x8033
,	GL2D_GL_TYPE_UNSIGNED_SHORT_5_5_5_1			= 0x8034
,	GL2D_GL_TYPE_UNSIGNED_INT_8_8_8_8			= 0x8035
,	GL2D_GL_TYPE_UNSIGNED_INT_10_10_10_2		= 0x8036
,	GL2D_GL_TYPE_UNSIGNED_BYTE_2_3_3_REV		= 0x8362
,	GL2D_GL_TYPE_UNSIGNED_SHORT_5_6_5			= 0x8363
,	GL2D_GL_TYPE_UNSIGNED_SHORT_5_6_5_REV		= 0x8364
,	GL2D_GL_TYPE_UNSIGNED_SHORT_4_4_4_4_REV		= 0x8365
,	GL2D_GL_TYPE_UNSIGNED_SHORT_1_5_5_5_REV		= 0x8366
,	GL2D_GL_TYPE_UNSIGNED_INT_8_8_8_8_REV		= 0x8367
,	GL2D_GL_TYPE_UNSIGNED_INT_2_10_10_10_REV	= 0x8368
,	GL2D_GL_TYPE_UNSIGNED_INT_24_8				= 0x84FA
#if CASTOR_USE_DOUBLE
,	GL2D_GL_TYPE_REAL							= GL2D_GL_TYPE_DOUBLE
#else
,	GL2D_GL_TYPE_REAL							= GL2D_GL_TYPE_FLOAT
#endif
}	GL2D_GL_TYPE;

typedef enum GL2D_GL_TEXTURE_INDEX : unsigned int
{	GL2D_GL_TEXTURE_INDEX_0		= 0x84C0
,	GL2D_GL_TEXTURE_INDEX_1		= 0x84C1
,	GL2D_GL_TEXTURE_INDEX_2		= 0x84C2
,	GL2D_GL_TEXTURE_INDEX_3		= 0x84C3
,	GL2D_GL_TEXTURE_INDEX_4		= 0x84C4
,	GL2D_GL_TEXTURE_INDEX_5		= 0x84C5
,	GL2D_GL_TEXTURE_INDEX_6		= 0x84C6
,	GL2D_GL_TEXTURE_INDEX_7		= 0x84C7
,	GL2D_GL_TEXTURE_INDEX_8		= 0x84C8
,	GL2D_GL_TEXTURE_INDEX_9		= 0x84C9
,	GL2D_GL_TEXTURE_INDEX_10	= 0x84CA
,	GL2D_GL_TEXTURE_INDEX_11	= 0x84CB
,	GL2D_GL_TEXTURE_INDEX_12	= 0x84CC
,	GL2D_GL_TEXTURE_INDEX_13	= 0x84CD
,	GL2D_GL_TEXTURE_INDEX_14	= 0x84CE
,	GL2D_GL_TEXTURE_INDEX_15	= 0x84CF
,	GL2D_GL_TEXTURE_INDEX_16	= 0x84D0
,	GL2D_GL_TEXTURE_INDEX_17	= 0x84D1
,	GL2D_GL_TEXTURE_INDEX_18	= 0x84D2
,	GL2D_GL_TEXTURE_INDEX_19	= 0x84D3
,	GL2D_GL_TEXTURE_INDEX_20	= 0x84D4
,	GL2D_GL_TEXTURE_INDEX_21	= 0x84D5
,	GL2D_GL_TEXTURE_INDEX_22	= 0x84D6
,	GL2D_GL_TEXTURE_INDEX_23	= 0x84D7
,	GL2D_GL_TEXTURE_INDEX_24	= 0x84D8
,	GL2D_GL_TEXTURE_INDEX_25	= 0x84D9
,	GL2D_GL_TEXTURE_INDEX_26	= 0x84DA
,	GL2D_GL_TEXTURE_INDEX_27	= 0x84DB
,	GL2D_GL_TEXTURE_INDEX_28	= 0x84DC
,	GL2D_GL_TEXTURE_INDEX_29	= 0x84DD
,	GL2D_GL_TEXTURE_INDEX_30	= 0x84DE
,	GL2D_GL_TEXTURE_INDEX_31	= 0x84DF
}	GL2D_GL_TEXTURE_INDEX;
	
typedef enum GL2D_GL_TEXTURE_MAG_FILTER : unsigned int
{	GL2D_GL_TEXTURE_MAG_FILTER_NEAREST	= 0x2600
,	GL2D_GL_TEXTURE_MAG_FILTER_LINEAR	= 0x2601
};
	
typedef enum GL2D_GL_TEXTURE_MIN_FILTER : unsigned int
{	GL2D_GL_TEXTURE_MIN_FILTER_NEAREST					= 0x2600
,	GL2D_GL_TEXTURE_MIN_FILTER_LINEAR					= 0x2601
,	GL2D_GL_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_NEAREST	= 0x2700
,	GL2D_GL_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_NEAREST	= 0x2701
,	GL2D_GL_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_LINEAR	= 0x2702
,	GL2D_GL_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_LINEAR		= 0x2703
}	GL2D_GL_TEXTURE_MIN_FILTER;
	
typedef enum GL2D_GL_TEXTURE_FILTER : unsigned int
{	GL2D_GL_TEXTURE_FILTER_NEAREST	= 0x2600
,	GL2D_GL_TEXTURE_FILTER_LINEAR	= 0x2601
}	GL2D_GL_TEXTURE_FILTER;

/**@name FBO */
//@{

static std::function< void ( int n, uint32_t* framebuffers  ) > glGenFramebuffers;
static std::function< void ( int n, uint32_t const * framebuffers  ) > glDeleteFramebuffers;
static std::function< void ( uint32_t target, GL2D_GL_FRAMEBUFFER_MODE framebuffer  ) > glBindFramebuffer;
static std::function< uint32_t ( uint32_t target  ) > glCheckFramebufferStatus;
static std::function< void ( uint32_t target, uint32_t attachment, uint32_t texture, int level  ) > glFramebufferTexture;
static std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level  ) > glFramebufferTexture1D;
static std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level  ) > glFramebufferTexture2D;
static std::function< void ( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer  ) > glFramebufferTextureLayer;
#if DEF_HAS_VARIADIC_TEMPLATES
static std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer ) > glFramebufferTexture3D;
static std::function< void ( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter ) > glBlitFramebuffer;
#else
static void (CALLBACK * glFramebufferTexture3D)( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
static void (CALLBACK * glBlitFramebuffer)( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
#endif
static std::function< void			( int n, uint32_t const * bufs ) > glDrawBuffers;

//@}
/**@name Texture */
//@{

static std::function < void ( uint32_t texture ) > glActiveTexture;

//@}
/**@name RBO */
//@{

static std::function< void ( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId ) > glFramebufferRenderbuffer;
static std::function< void ( int n, uint32_t * ids ) > glGenRenderbuffers;
static std::function< void ( int n, uint32_t const * ids ) > glDeleteRenderbuffers;
static std::function< void ( uint32_t target, uint32_t id ) > glBindRenderbuffer;
static std::function< void ( uint32_t target, uint32_t internalFormat, int width, int height ) > glRenderbufferStorage;
static std::function< void ( uint32_t target, int isamples, uint32_t internalFormat, int width, int height ) > glRenderbufferStorageMultisample;
#if DEF_HAS_VARIADIC_TEMPLATES
static std::function< void ( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations ) > glTexImage2DMultisample;
#else
static void (CALLBACK * glTexImage2DMultisample)( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
#endif
static std::function< void ( uint32_t target, uint32_t param, int* value ) > glGetRenderbufferParameteriv;

static void InitialiseOpenGL();

HRESULT glGetLastError( char const * const name );

#endif
