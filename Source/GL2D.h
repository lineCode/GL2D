#ifndef ___OGL2D_GL2D_H___
#define ___OGL2D_GL2D_H___

#include <dxgiformat.h>
#include <combaseapi.h>
#include <Wincodec.h>

#include "OpenGL.h"
#include "GLBaseTypes.h"

#undef DrawText

#define GL2D_INVALID_TAG ULONGLONG_MAX
#define GL2D_DEFAULT_FLATTENING_TOLERANCE 0.25f

#ifndef GL_DECLARE_INTERFACE
#	define GL_DECLARE_INTERFACE( x ) DECLSPEC_UUID( x ) DECLSPEC_NOVTABLE
#endif

#ifdef __cplusplus

// Define operator overloads to enable bit operations on enum values that are 
// used to define flags. Use DEFINE_ENUM_FLAG_OPERATORS(YOUR_TYPE) to enable these 
// operators on YOUR_TYPE.

// Moved here from winnt.h

// Templates are defined here in order to avoid a dependency on C++ <type_traits> header file,
// or on compiler-specific contructs.
extern "C++"
{
	template< size_t S >
	struct GL2D_ENUM_FLAG_INTEGER_FOR_SIZE;

	template<>
	struct GL2D_ENUM_FLAG_INTEGER_FOR_SIZE< 1>
	{
		typedef int8_t type;
	};

	template<>
	struct GL2D_ENUM_FLAG_INTEGER_FOR_SIZE< 2 >
	{
		typedef int16_t type;
	};

	template<>
	struct GL2D_ENUM_FLAG_INTEGER_FOR_SIZE< 4 >
	{
		typedef int32_t type;
	};

	template<>
	struct GL2D_ENUM_FLAG_INTEGER_FOR_SIZE< 8 >
	{
		typedef int64_t type;
	};

	// used as an approximation of std::underlying_type<T>
	template< class T >
	struct GL2D_ENUM_FLAG_SIZED_INTEGER
	{
		typedef typename GL2D_ENUM_FLAG_INTEGER_FOR_SIZE< sizeof( T ) >::type type;
	};
}

#	define IMPL_ENUM_FLAG_OPERATORS( ENUMTYPE ) \
	extern "C++" \
	{ \
		inline ENUMTYPE operator | ( ENUMTYPE a, ENUMTYPE b ) { return ENUMTYPE( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)a) | ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
		inline ENUMTYPE &operator |= ( ENUMTYPE &a, ENUMTYPE b ) { return (ENUMTYPE &)( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type &)a) |= ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
		inline ENUMTYPE operator & ( ENUMTYPE a, ENUMTYPE b ) { return ENUMTYPE( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)a) & ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
		inline ENUMTYPE &operator &= ( ENUMTYPE &a, ENUMTYPE b ) { return (ENUMTYPE &)( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type &)a) &= ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
		inline ENUMTYPE operator ~ ( ENUMTYPE a ) { return ENUMTYPE( ~((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)a) ); } \
		inline ENUMTYPE operator ^ ( ENUMTYPE a, ENUMTYPE b ) { return ENUMTYPE( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)a) ^ ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
		inline ENUMTYPE &operator ^= ( ENUMTYPE &a, ENUMTYPE b ) { return (ENUMTYPE &)( ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type &)a) ^= ((GL2D_ENUM_FLAG_SIZED_INTEGER< ENUMTYPE >::type)b) ); } \
	}
#else
#	define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) // NOP, C allows these operators.
#endif

	/** The measuring method used for text layout.
	*/
	typedef enum GL2D_MEASURING_MODE
	{	GL2D_MEASURING_MODE_NATURAL		//!< Text is measured using glyph ideal metrics whose values are independent to the current display resolution.
	,	GL2D_MEASURING_MODE_GDI_CLASSIC	//!< Text is measured using glyph display compatible metrics whose values tuned for the current display resolution.
	,	GL2D_MEASURING_MODE_GDI_NATURAL	//!< Text is measured using the same glyph display metrics as text measured by GDI using a font created with CLEARTYPE_NATURAL_QUALITY.
	}	GL2D_MEASURING_MODE;

	/** Qualifies how alpha is to be treated in a bitmap or render target containing alpha.
	*/
	typedef enum GL2D_ALPHA_MODE : uint32_t
	{	GL2D_ALPHA_MODE_UNKNOWN = 0			//!< Alpha mode should be determined implicitly. Some target surfaces do not supply or imply this information in which case alpha must be specified.
	,	GL2D_ALPHA_MODE_PREMULTIPLIED = 1	//!< Treat the alpha as premultipled.
	,	GL2D_ALPHA_MODE_STRAIGHT = 2		//!< Opacity is in the 'A' component only.
	,	GL2D_ALPHA_MODE_IGNORE = 3			//!< Ignore any alpha channel information.
	}	GL2D_ALPHA_MODE;

	/** Defines interpolation modes supported by GL2D APIs and built-in effects
	*/
	typedef enum GL2D_INTERPOLATION_MODE_DEFINITION
	{	GL2D_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR
	,	GL2D_INTERPOLATION_MODE_DEFINITION_LINEAR
	,	GL2D_INTERPOLATION_MODE_DEFINITION_CUBIC
	,	GL2D_INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR
	,	GL2D_INTERPOLATION_MODE_DEFINITION_ANISOTROPIC
	,	GL2D_INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC
	,	GL2D_INTERPOLATION_MODE_DEFINITION_FANT
	,	GL2D_INTERPOLATION_MODE_DEFINITION_MIPMAP_LINEAR
	}	GL2D_INTERPOLATION_MODE_DEFINITION;

	/** This determines what gamma is used for interpolation/blending.
	*/
	typedef enum GL2D_GAMMA : uint32_t
	{	GL2D_GAMMA_2_2 = 0	//!< Colors are manipulated in 2.2 gamma color space.
	,	GL2D_GAMMA_1_0 = 1	//!< Colors are manipulated in 1.0 gamma color space.
	}	GL2D_GAMMA;


	/** Specifies the contents of an opacity mask.
	*/
	typedef enum GL2D_OPACITY_MASK_CONTENT : uint32_t
	{	GL2D_OPACITY_MASK_CONTENT_GRAPHICS = 0				//!< The mask contains geometries or bitmaps.
	,	GL2D_OPACITY_MASK_CONTENT_TEXT_NATURAL = 1			//!< The mask contains text rendered using one of the natural text modes.
	,	GL2D_OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2	//!< The mask contains text rendered using one of the GDI compatible text modes.
	}	GL2D_OPACITY_MASK_CONTENT;

	/** Describes how to sample from a source outside its base tile.
	*/
	typedef enum GL2D_EXTEND_MODE : uint32_t
	{	GL2D_EXTEND_MODE_CLAMP = 0	//!< Extend the edges of the source out by clamping sample points outside the source to the edges.
	,	GL2D_EXTEND_MODE_WRAP = 1	//!< The base tile is drawn untransformed and the remainder are filled by repeating the base tile.
	,	GL2D_EXTEND_MODE_MIRROR = 2	//!< The same as wrap, but alternate tiles are flipped  The base tile is drawn untransformed.
	}	GL2D_EXTEND_MODE;

	/** Enum which describes the manner in which we render edges of non-text primitives.
	*/
	typedef enum GL2D_ANTIALIAS_MODE : uint32_t
	{	GL2D_ANTIALIAS_MODE_PER_PRIMITIVE = 0	//!< The edges of each primitive are antialiased sequentially.
	,	GL2D_ANTIALIAS_MODE_ALIASED = 1			//!< Each pixel is rendered if its pixel center is contained by the geometry.
	}	GL2D_ANTIALIAS_MODE;

	/**
	*/
	typedef enum GL2D_TEXT_ANTIALIAS_MODE : uint32_t
	{	GL2D_TEXT_ANTIALIAS_MODE_DEFAULT = 0	//!< Render text using the current system setting.
	,	GL2D_TEXT_ANTIALIAS_MODE_CLEARTYPE = 1	//!< Render text using ClearType.
	,	GL2D_TEXT_ANTIALIAS_MODE_GRAYSCALE = 2	//!< Render text using gray-scale.
	,	GL2D_TEXT_ANTIALIAS_MODE_ALIASED = 3	//!< Render text aliased.
	}	GL2D_TEXT_ANTIALIAS_MODE;

	/**
	*/
	typedef enum GL2D_BITMAP_INTERPOLATION_MODE : uint32_t
	{	GL2D_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = GL2D_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR	//!< Nearest Neighbor filtering. Also known as nearest pixel or nearest point sampling.
	,	GL2D_BITMAP_INTERPOLATION_MODE_LINEAR = GL2D_INTERPOLATION_MODE_DEFINITION_LINEAR						//!< Linear filtering.
	}	GL2D_BITMAP_INTERPOLATION_MODE;

	/** Modifications made to the draw text call that influence how the text is rendered.
	*/
	typedef enum GL2D_DRAW_TEXT_OPTIONS : uint32_t
	{	GL2D_DRAW_TEXT_OPTIONS_NONE = 0x00000000
	,	GL2D_DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001				//!< Do not snap the baseline of the text vertically.
	,	GL2D_DRAW_TEXT_OPTIONS_CLIP = 0x00000002				//!< Clip the text to the content bounds.
	,	GL2D_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT = 0x00000004	//!< Render color versions of glyphs if defined by the font.
	}	GL2D_DRAW_TEXT_OPTIONS;

	/** Differentiates which of the two possible arcs could match the given arc parameters.
	*/
	typedef enum GL2D_ARC_SIZE : uint32_t
	{	GL2D_ARC_SIZE_SMALL = 0
	,	GL2D_ARC_SIZE_LARGE = 1
	}	GL2D_ARC_SIZE;

	/** Enum which describes the drawing of the ends of a line.
	*/
	typedef enum GL2D_CAP_STYLE : uint32_t
	{	GL2D_CAP_STYLE_FLAT = 0		//!< Flat line cap.
	,	GL2D_CAP_STYLE_SQUARE = 1	//!< Square line cap.
	,	GL2D_CAP_STYLE_ROUND = 2	//!< Round line cap.
	,	GL2D_CAP_STYLE_TRIANGLE = 3	//!< Triangle line cap.
	}	GL2D_CAP_STYLE;

	/**
	*/
	typedef enum GL2D_DASH_STYLE : uint32_t
	{	GL2D_DASH_STYLE_SOLID = 0
	,	GL2D_DASH_STYLE_DASH = 1
	,	GL2D_DASH_STYLE_DOT = 2
	,	GL2D_DASH_STYLE_DASH_DOT = 3
	,	GL2D_DASH_STYLE_DASH_DOT_DOT = 4
	,	GL2D_DASH_STYLE_CUSTOM = 5
	}	GL2D_DASH_STYLE;

	/** Enum which describes the drawing of the corners on the line.
	*/
	typedef enum GL2D_LINE_JOIN : uint32_t
	{	GL2D_LINE_JOIN_MITER = 0			//!< Miter join.
	,	GL2D_LINE_JOIN_BEVEL = 1			//!< Bevel join.
	,	GL2D_LINE_JOIN_ROUND = 2			//!< Round join.
	,	GL2D_LINE_JOIN_MITER_OR_BEVEL = 3	//!< Miter/Bevel join.
	}	GL2D_LINE_JOIN;

	/** This enumeration describes the type of combine operation to be performed.
	*/
	typedef enum GL2D_COMBINE_MODE : uint32_t
	{	GL2D_COMBINE_MODE_UNION = 0		//!< Produce a geometry representing the set of points contained in either the first or the second geometry.
	,	GL2D_COMBINE_MODE_INTERSECT = 1	//!< Produce a geometry representing the set of points common to the first and the second geometries.
	,	GL2D_COMBINE_MODE_XOR = 2		//!< Produce a geometry representing the set of points contained in the first geometry or the second geometry, but not both.
	,	GL2D_COMBINE_MODE_EXCLUDE = 3	//!< Produce a geometry representing the set of points contained in the first geometry but not the second geometry.
	}	GL2D_COMBINE_MODE;
	
	/**
	*/
	typedef enum GL2D_GEOMETRY_RELATION : uint32_t
	{	GL2D_GEOMETRY_RELATION_UNKNOWN = 0		//!< The relation between the geometries couldn't be determined. This value is never returned by any D2D method.
	,	GL2D_GEOMETRY_RELATION_DISJOINT = 1		//!< The two geometries do not intersect at all.
	,	GL2D_GEOMETRY_RELATION_IS_CONTAINED = 2	//!< The passed in geometry is entirely contained by the object.
	,	GL2D_GEOMETRY_RELATION_CONTAINS = 3		//!< The object entirely contains the passed in geometry.
	,	GL2D_GEOMETRY_RELATION_OVERLAP = 4		//!< The two geometries overlap but neither completely contains the other.
	}	GL2D_GEOMETRY_RELATION;

	/** Specifies how simple the output of a simplified geometry sink should be.
	*/
	typedef enum GL2D_GEOMETRY_SIMPLIFICATION_OPTION : uint32_t
	{	GL2D_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES = 0
	,	GL2D_GEOMETRY_SIMPLIFICATION_OPTION_LINES = 1
	}	GL2D_GEOMETRY_SIMPLIFICATION_OPTION;
	
	/**
	*/
	typedef enum GL2D_FIGURE_BEGIN : uint32_t
	{	GL2D_FIGURE_BEGIN_FILLED = 0
	,	GL2D_FIGURE_BEGIN_HOLLOW = 1
	}	GL2D_FIGURE_BEGIN;


	/** Indicates whether the figure is open or closed on its end point.
	*/
	typedef enum GL2D_FIGURE_END : uint32_t
	{	GL2D_FIGURE_END_OPEN = 0
	,	GL2D_FIGURE_END_CLOSED = 1
	}	GL2D_FIGURE_END;
	
	/**
	*/
	typedef enum GL2D_WINDOW_STATE : uint32_t
	{	GL2D_WINDOW_STATE_NONE      = 0x0000000
	,	GL2D_WINDOW_STATE_OCCLUDED  = 0x0000001
	}	GL2D_WINDOW_STATE;
	
	/**
	*/
	typedef enum GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS : uint32_t
	{	GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE = 0x00000000
	,	GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE = 0x00000001	//!< The compatible render target will allow a call to GetDC on the GL2DGdiInteropRenderTarget interface. This can be specified even if the parent render target is not GDI compatible.
	}	GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS;

	/** Indicates whether the given segment should be stroked, or, if the join between this segment and the previous one should be smooth.
	*/
	typedef enum GL2D_PATH_SEGMENT : uint32_t
	{	GL2D_PATH_SEGMENT_NONE = 0x00000000
	,	GL2D_PATH_SEGMENT_FORCE_UNSTROKED = 0x00000001
	,	GL2D_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN = 0x00000002
	}	GL2D_PATH_SEGMENT;

	/**
	*/
	typedef enum GL2D_SWEEP_DIRECTION
	{	GL2D_SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0
	,	GL2D_SWEEP_DIRECTION_CLOCKWISE = 1
	}	GL2D_SWEEP_DIRECTION;

	/**
	*/
	typedef enum GL2D_FILL_MODE
	{	GL2D_FILL_MODE_ALTERNATE = 0
	,	GL2D_FILL_MODE_WINDING = 1
	}	GL2D_FILL_MODE;

	/** Specified options that can be applied when a layer resource is applied to create a layer.
	*/
	typedef enum GL2D_LAYER_OPTIONS : uint32_t
	{	GL2D_LAYER_OPTIONS_NONE = 0x00000000
	,	GL2D_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 0x00000001
	}	GL2D_LAYER_OPTIONS;

	/**
	*/
	typedef enum GL2D_RENDER_TARGET_TYPE : uint32_t
	{	GL2D_RENDER_TARGET_TYPE_DEFAULT = 0		//!< D2D is free to choose the render target type for the caller.
	,	GL2D_RENDER_TARGET_TYPE_SOFTWARE = 1	//!< The render target will render using the CPU.
	,	GL2D_RENDER_TARGET_TYPE_HARDWARE = 2	//!< The render target will render using the GPU.
	}	GL2D_RENDER_TARGET_TYPE;
	
	/**
	*/
	typedef enum GL2D_FEATURE_LEVEL : uint32_t
	{	GL2D_FEATURE_LEVEL_DEFAULT = 0	//!< The caller does not require a particular underlying D3D device level.
	,	GL2D_FEATURE_LEVEL_GL2 = 1		//!< The D3D device level is OpenGl2.x compatible.
	,	GL2D_FEATURE_LEVEL_GL3 = 2		//!< The D3D device level is OpenGl3.x compatible.
	,	GL2D_FEATURE_LEVEL_GL4 = 3		//!< The D3D device level is OpenGl4.x compatible.
	}	GL2D_FEATURE_LEVEL;
	
	/**
	*/
	typedef enum GL2D_RENDER_TARGET_USAGE : uint32_t
	{	GL2D_RENDER_TARGET_USAGE_NONE = 0x00000000
	,	GL2D_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING = 0x00000001	//!< Rendering will occur locally, if a terminal-services session is established, the bitmap updates will be sent to the terminal services client.
	,	GL2D_RENDER_TARGET_USAGE_GDI_COMPATIBLE = 0x00000002		//!< The render target will allow a call to GetDC on the IGL2DGdiInteropRenderTarget interface. Rendering will also occur locally.
	}	GL2D_RENDER_TARGET_USAGE;

	/** Describes how present should behave.
	*/
	typedef enum GL2D_PRESENT_OPTIONS : uint32_t
	{	GL2D_PRESENT_OPTIONS_NONE = 0x00000000
	,	GL2D_PRESENT_OPTIONS_RETAIN_CONTENTS = 0x00000001	//!< Keep the target contents intact through present.
	,	GL2D_PRESENT_OPTIONS_IMMEDIATELY = 0x00000002		//!< Do not wait for display refresh to commit changes to display.
	}	GL2D_PRESENT_OPTIONS;

	/**
	*/
	typedef enum GL2D_DC_INITIALIZE_MODE : uint32_t
	{	GL2D_DC_INITIALIZE_MODE_COPY = 0	//!< The contents of the D2D render target will be copied to the DC.
	,	GL2D_DC_INITIALIZE_MODE_CLEAR = 1	//!< The contents of the DC will be cleared.
	}	GL2D_DC_INITIALIZE_MODE;


	/** Indicates the debug level to be output by the debug layer.
	*/
	typedef enum GL2D_DEBUG_LEVEL
	{	GL2D_DEBUG_LEVEL_NONE = 0
	,	GL2D_DEBUG_LEVEL_ERROR = 1
	,	GL2D_DEBUG_LEVEL_WARNING = 2
	,	GL2D_DEBUG_LEVEL_INFORMATION = 3
	}	GL2D_DEBUG_LEVEL;

	/** Specifies the threading model of the created factory and all of its derived resources.
	*/
	typedef enum GL2D_FACTORY_TYPE
	{	GL2D_FACTORY_TYPE_SINGLE_THREADED = 0	//!< The resulting factory and derived resources may only be invoked serially. Reference counts on resources are interlocked, however, resource and render target state is not protected from multi-threaded access.
	,	GL2D_FACTORY_TYPE_MULTI_THREADED = 1	//!< The resulting factory may be invoked from multiple threads. Returned resources use interlocked reference counting and their state is protected.
	}	GL2D_FACTORY_TYPE;

	IMPL_ENUM_FLAG_OPERATORS( GL2D_LAYER_OPTIONS );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_PATH_SEGMENT );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_DRAW_TEXT_OPTIONS );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_WINDOW_STATE );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_RENDER_TARGET_USAGE );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_PRESENT_OPTIONS );
	IMPL_ENUM_FLAG_OPERATORS( GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS );
	
	interface IGL2DFactory;
	interface IGL2DResource;
	interface IGL2DImage;
	interface IGL2DBitmap;
	interface IGL2DGradientStopCollection;
	interface IGL2DBrush;
	interface IGL2DBitmapBrush;
	interface IGL2DSolidColorBrush;
	interface IGL2DLinearGradientBrush;
	interface IGL2DRadialGradientBrush;
	interface IGL2DStrokeStyle;
	interface IGL2DGeometry;
	interface IGL2DRectangleGeometry;
	interface IGL2DRoundedRectangleGeometry;
	interface IGL2DEllipseGeometry;
	interface IGL2DGeometryGroup;
	interface IGL2DTransformedGeometry;
	interface IGL2DSimplifiedGeometrySink;
	interface IGL2DTessellationSink;
	interface IGL2DGeometrySink;
	interface IGL2DPathGeometry;
	interface IGL2DMesh;
	interface IGL2DLayer;
	interface IGL2DDrawingStateBlock;
	interface IGL2DRenderTarget;
	interface IGL2DBitmapRenderTarget;
	interface IGL2DHwndRenderTarget;
	interface IGL2DGdiInteropRenderTarget;
	interface IGL2DDCRenderTarget;
	interface IGL2DFactory;

	/**
	*/
	typedef struct GL2D_PIXEL_FORMAT
	{
		GL2D_GL_FORMAT		format;
		GL2D_GL_INTERNAL	internal;
		GL2D_GL_TYPE		type;
	} GL2D_PIXEL_FORMAT;
	
	/**
	*/
	typedef struct GL2D_BITMAP_PROPERTIES
	{
		GL2D_PIXEL_FORMAT pixelFormat;
		float dpiX;
		float dpiY;
	} GL2D_BITMAP_PROPERTIES;
	
	/**
	*/
	typedef struct GL2D_GRADIENT_STOP
	{
		float position;
		GL2D_COLOR_F color;
	} GL2D_GRADIENT_STOP;
	
	/**
	*/
	typedef struct GL2D_BRUSH_PROPERTIES
	{
		float opacity;
		GL2D_MATRIX_3X2_F transform;
	} GL2D_BRUSH_PROPERTIES;

	/**
	*/
	typedef struct GL2D_BITMAP_BRUSH_PROPERTIES
	{
		GL2D_EXTEND_MODE extendModeX;
		GL2D_EXTEND_MODE extendModeY;
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode;
	} GL2D_BITMAP_BRUSH_PROPERTIES;
	
	/**
	*/
	typedef struct GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES
	{
		GL2D_POINT_2F startPoint;
		GL2D_POINT_2F endPoint;
	} GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES;
	
	/**
	*/
	typedef struct GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES
	{
		GL2D_POINT_2F center;
		GL2D_POINT_2F gradientOriginOffset;
		float radiusX;
		float radiusY;
	} GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES;

	/** Describes a cubic bezier in a path.
	*/
	typedef struct GL2D_BEZIER_SEGMENT
	{
		GL2D_POINT_2F point1;
		GL2D_POINT_2F point2;
		GL2D_POINT_2F point3;
	} GL2D_BEZIER_SEGMENT;

	/** Describes a triangle.
	*/
	typedef struct GL2D_TRIANGLE
	{
		GL2D_POINT_2F point1;
		GL2D_POINT_2F point2;
		GL2D_POINT_2F point3;
	} GL2D_TRIANGLE;

	/** Describes an arc that is defined as part of a path.
	*/
	typedef struct GL2D_ARC_SEGMENT
	{
		GL2D_POINT_2F point;
		GL2D_SIZE_F size;
		float rotationAngle;
		GL2D_SWEEP_DIRECTION sweepDirection;
		GL2D_ARC_SIZE arcSize;
	} GL2D_ARC_SEGMENT;

	/**
	*/
	typedef struct GL2D_QUADRATIC_BEZIER_SEGMENT
	{
		GL2D_POINT_2F point1;
		GL2D_POINT_2F point2;
	} GL2D_QUADRATIC_BEZIER_SEGMENT;
	
	/**
	*/
	typedef struct GL2D_ELLIPSE
	{
		GL2D_POINT_2F point;
		float radiusX;
		float radiusY;
	} GL2D_ELLIPSE;
	
	/**
	*/
	typedef struct GL2D_ROUNDED_RECT
	{
		GL2D_RECT_F rect;
		float radiusX;
		float radiusY;
	} GL2D_ROUNDED_RECT;

	/** Properties, aside from the width, that allow geometric penning to be specified.
	*/
	typedef struct GL2D_STROKE_STYLE_PROPERTIES
	{
		GL2D_CAP_STYLE startCap;
		GL2D_CAP_STYLE endCap;
		GL2D_CAP_STYLE dashCap;
		GL2D_LINE_JOIN lineJoin;
		float miterLimit;
		GL2D_DASH_STYLE dashStyle;
		float dashOffset;
	} GL2D_STROKE_STYLE_PROPERTIES;

	/**
	*/
	typedef struct GL2D_LAYER_PARAMETERS
	{
		//! The rectangular clip that will be applied to the layer. The clip is affected by the world transform. Content outside of the content bounds will not render.
		GL2D_RECT_F contentBounds;
		//! A general mask that can be optionally applied to the content. Content not inside the fill of the mask will not be rendered.
		IGL2DGeometry * geometricMask;
		//! Specifies whether the mask should be aliased or antialiased.
		GL2D_ANTIALIAS_MODE maskAntialiasMode;
		//! An additional transform that may be applied to the mask in addition to the current world transform.
		GL2D_MATRIX_3X2_F maskTransform;
		//! The opacity with which all of the content in the layer will be blended back to the target when the layer is popped.
		float opacity;
		//! An additional brush that can be applied to the layer. Only the opacity channel is sampled from this brush and multiplied both with the layer content and the over-all layer opacity.
		IGL2DBrush * opacityBrush;
		//! Specifies if ClearType will be rendered into the layer.
		GL2D_LAYER_OPTIONS layerOptions;
	} GL2D_LAYER_PARAMETERS;

	/**
	*/
	typedef struct GL2D_RENDER_TARGET_PROPERTIES
	{
		GL2D_RENDER_TARGET_TYPE type;
		GL2D_PIXEL_FORMAT pixelFormat;
		float dpiX;
		float dpiY;
		GL2D_RENDER_TARGET_USAGE usage;
		GL2D_FEATURE_LEVEL minLevel;
	} GL2D_RENDER_TARGET_PROPERTIES;
	
	/**
	*/
	typedef struct GL2D_HWND_RENDER_TARGET_PROPERTIES
	{
		HWND hwnd;
		GL2D_SIZE_U pixelSize;
		GL2D_PRESENT_OPTIONS presentOptions;
	} GL2D_HWND_RENDER_TARGET_PROPERTIES;

	/** Allows the drawing state to be atomically created. This also specifies the
		drawing state that is saved into an IDrawingStateBlock object.
	*/
	typedef struct GL2D_DRAWING_STATE_DESCRIPTION
	{
		GL2D_ANTIALIAS_MODE antialiasMode;
		GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode;
		GL2D_TAG tag1;
		GL2D_TAG tag2;
		GL2D_MATRIX_3X2_F transform;
	} GL2D_DRAWING_STATE_DESCRIPTION;

	/** Allows additional parameters for factory creation.
	*/
	typedef struct GL2D_FACTORY_OPTIONS
	{
		GL2D_DEBUG_LEVEL debugLevel;	//!< Requests a certain level of debugging information from the debug layer. This parameter is ignored if the debug layer DLL is not present.
	} GL2D_FACTORY_OPTIONS;

/** The root interface for all resources in D2D.
*/
interface GL_DECLARE_INTERFACE("2cd90691-12e2-11dc-9fed-001143a055f9") IGL2DResource  : public IUnknown
{
	//
	// Retrieve the factory associated with this resource.
	//
	STDMETHOD_(void, GetFactory)(
		_Outptr_ IGL2DFactory **factory 
		) const PURE;
}; // interface IGL2DResource


//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DImage
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("65019f75-8da2-497c-b32c-dfa34e48ede6") IGL2DImage  : public IGL2DResource
{
}; // interface IGL2DImage


//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DBitmap
//
//  Synopsis:
//      Root bitmap resource, linearly scaled on a draw call.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("a2296057-ea42-4099-983b-539fb6505426") IGL2DBitmap  : public IGL2DImage
{
    
    
	//
	// Returns the size of the bitmap in resolution independent units.
	//
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		) const PURE;
    
    
	//
	// Returns the size of the bitmap in resolution dependent units, (pixels).
	//
	STDMETHOD_(GL2D_SIZE_U, GetPixelSize)(
		) const PURE;
    
    
	//
	// Retrieve the format of the bitmap.
	//
	STDMETHOD_(GL2D_PIXEL_FORMAT, GetPixelFormat)(
		) const PURE;
    
    
	//
	// Return the DPI of the bitmap.
	//
	STDMETHOD_(void, GetDpi)(
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) const PURE;
    
	STDMETHOD(CopyFromBitmap)(
		_In_opt_ const GL2D_POINT_2U *destPoint,
		_In_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_RECT_U *srcRect 
		) PURE;
    
	STDMETHOD(CopyFromRenderTarget)(
		_In_opt_ const GL2D_POINT_2U *destPoint,
		_In_ IGL2DRenderTarget *renderTarget,
		_In_opt_ const GL2D_RECT_U *srcRect 
		) PURE;
    
	STDMETHOD(CopyFromMemory)(
		_In_opt_ const GL2D_RECT_U *dstRect,
		_In_ const void *srcData,
		uint32_t pitch 
		) PURE;
}; // interface IGL2DBitmap



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DGradientStopCollection
//
//  Synopsis:
//      Represents an collection of gradient stops that can then be the source resource
//      for either a linear or radial gradient brush.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a7-12e2-11dc-9fed-001143a055f9") IGL2DGradientStopCollection  : public IGL2DResource
{
    
    
	//
	// Returns the number of stops in the gradient.
	//
	STDMETHOD_(uint32_t, GetGradientStopCount)(
		) const PURE;
    
    
	//
	// Copies the gradient stops from the collection into the caller's interface.  The
	// returned colors have straight alpha.
	//
	STDMETHOD_(void, GetGradientStops)(
		_Out_writes_to_(gradientStopsCount, _Inexpressible_("Retrieved through GetGradientStopCount()") ) GL2D_GRADIENT_STOP *gradientStops,
		uint32_t gradientStopsCount 
		) const PURE;
    
    
	//
	// Returns whether the interpolation occurs with 1.0 or 2.2 gamma.
	//
	STDMETHOD_(GL2D_GAMMA, GetColorInterpolationGamma)(
		) const PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendMode)(
		) const PURE;
}; // interface IGL2DGradientStopCollection



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DBrush
//
//  Synopsis:
//      The root brush interface. All brushes can be used to fill or pen a geometry.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a8-12e2-11dc-9fed-001143a055f9") IGL2DBrush  : public IGL2DResource
{
    
    
	//
	// Sets the opacity for when the brush is drawn over the entire fill of the brush.
	//
	STDMETHOD_(void, SetOpacity)(
		float opacity 
		) PURE;
    
    
	//
	// Sets the transform that applies to everything drawn by the brush.
	//
	STDMETHOD_(void, SetTransform)(
		_In_ const GL2D_MATRIX_3X2_F *transform 
		) PURE;
    
	STDMETHOD_(float, GetOpacity)(
		) const PURE;
    
	STDMETHOD_(void, GetTransform)(
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) const PURE;
    
	COM_DECLSPEC_NOTHROW
	void
	SetTransform(
		const GL2D_MATRIX_3X2_F &transform 
		)  
	{
		SetTransform(&transform);
	}
}; // interface IGL2DBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DBitmapBrush
//
//  Synopsis:
//      A bitmap brush allows a bitmap to be used to fill a geometry.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906aa-12e2-11dc-9fed-001143a055f9") IGL2DBitmapBrush  : public IGL2DBrush
{
    
    
	//
	// Sets how the bitmap is to be treated outside of its natural extent on the X
	// axis.
	//
	STDMETHOD_(void, SetExtendModeX)(
		GL2D_EXTEND_MODE extendModeX 
		) PURE;
    
    
	//
	// Sets how the bitmap is to be treated outside of its natural extent on the X
	// axis.
	//
	STDMETHOD_(void, SetExtendModeY)(
		GL2D_EXTEND_MODE extendModeY 
		) PURE;
    
    
	//
	// Sets the interpolation mode used when this brush is used.
	//
	STDMETHOD_(void, SetInterpolationMode)(
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode 
		) PURE;
    
    
	//
	// Sets the bitmap associated as the source of this brush.
	//
	STDMETHOD_(void, SetBitmap)(
		_In_opt_ IGL2DBitmap *bitmap 
		) PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendModeX)(
		) const PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendModeY)(
		) const PURE;
    
	STDMETHOD_(GL2D_BITMAP_INTERPOLATION_MODE, GetInterpolationMode)(
		) const PURE;
    
	STDMETHOD_(void, GetBitmap)(
		_Outptr_ IGL2DBitmap **bitmap 
		) const PURE;
}; // interface IGL2DBitmapBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DSolidColorBrush
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a9-12e2-11dc-9fed-001143a055f9") IGL2DSolidColorBrush  : public IGL2DBrush
{
    
	STDMETHOD_(void, SetColor)(
		_In_ const GL2D_COLOR_F *color 
		) PURE;
    
	STDMETHOD_(GL2D_COLOR_F, GetColor)(
		) const PURE;
    
	COM_DECLSPEC_NOTHROW
	void
	SetColor(
		const GL2D_COLOR_F &color 
		)  
	{
		SetColor(&color);
	}
}; // interface IGL2DSolidColorBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DLinearGradientBrush
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906ab-12e2-11dc-9fed-001143a055f9") IGL2DLinearGradientBrush  : public IGL2DBrush
{
    
	STDMETHOD_(void, SetStartPoint)(
		GL2D_POINT_2F startPoint 
		) PURE;
    
    
	//
	// Sets the end point of the gradient in local coordinate space. This is not
	// influenced by the geometry being filled.
	//
	STDMETHOD_(void, SetEndPoint)(
		GL2D_POINT_2F endPoint 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetStartPoint)(
		) const PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetEndPoint)(
		) const PURE;
    
	STDMETHOD_(void, GetGradientStopCollection)(
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) const PURE;
}; // interface IGL2DLinearGradientBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DRadialGradientBrush
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906ac-12e2-11dc-9fed-001143a055f9") IGL2DRadialGradientBrush  : public IGL2DBrush
{
    
    
	//
	// Sets the center of the radial gradient. This will be in local coordinates and
	// will not depend on the geometry being filled.
	//
	STDMETHOD_(void, SetCenter)(
		GL2D_POINT_2F center 
		) PURE;
    
    
	//
	// Sets offset of the origin relative to the radial gradient center.
	//
	STDMETHOD_(void, SetGradientOriginOffset)(
		GL2D_POINT_2F gradientOriginOffset 
		) PURE;
    
	STDMETHOD_(void, SetRadiusX)(
		float radiusX 
		) PURE;
    
	STDMETHOD_(void, SetRadiusY)(
		float radiusY 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetCenter)(
		) const PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetGradientOriginOffset)(
		) const PURE;
    
	STDMETHOD_(float, GetRadiusX)(
		) const PURE;
    
	STDMETHOD_(float, GetRadiusY)(
		) const PURE;
    
	STDMETHOD_(void, GetGradientStopCollection)(
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) const PURE;
}; // interface IGL2DRadialGradientBrush



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DStrokeStyle
//
//  Synopsis:
//      Resource interface that holds pen style properties.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd9069d-12e2-11dc-9fed-001143a055f9") IGL2DStrokeStyle  : public IGL2DResource
{
    
	STDMETHOD_(GL2D_CAP_STYLE, GetStartCap)(
		) const PURE;
    
	STDMETHOD_(GL2D_CAP_STYLE, GetEndCap)(
		) const PURE;
    
	STDMETHOD_(GL2D_CAP_STYLE, GetDashCap)(
		) const PURE;
    
	STDMETHOD_(float, GetMiterLimit)(
		) const PURE;
    
	STDMETHOD_(GL2D_LINE_JOIN, GetLineJoin)(
		) const PURE;
    
	STDMETHOD_(float, GetDashOffset)(
		) const PURE;
    
	STDMETHOD_(GL2D_DASH_STYLE, GetDashStyle)(
		) const PURE;
    
	STDMETHOD_(uint32_t, GetDashesCount)(
		) const PURE;
    
    
	//
	// Returns the dashes from the object into a user allocated array. The user must
	// call GetDashesCount to retrieve the required size.
	//
	STDMETHOD_(void, GetDashes)(
		_Out_writes_(dashesCount) float *dashes,
		uint32_t dashesCount 
		) const PURE;
}; // interface IGL2DStrokeStyle



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a1-12e2-11dc-9fed-001143a055f9") IGL2DGeometry  : public IGL2DResource
{
    
    
	//
	// Retrieve the bounds of the geometry, with an optional applied transform.
	//
	STDMETHOD(GetBounds)(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ GL2D_RECT_F *bounds 
		) const PURE;
    
    
	//
	// Get the bounds of the corresponding geometry after it has been widened or have
	// an optional pen style applied.
	//
	STDMETHOD(GetWidenedBounds)(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ GL2D_RECT_F *bounds 
		) const PURE;
    
    
	//
	// Checks to see whether the corresponding penned and widened geometry contains the
	// given point.
	//
	STDMETHOD(StrokeContainsPoint)(
		GL2D_POINT_2F point,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) const PURE;
    
    
	//
	// Test whether the given fill of this geometry would contain this point.
	//
	STDMETHOD(FillContainsPoint)(
		GL2D_POINT_2F point,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) const PURE;
    
    
	//
	// Compare how one geometry intersects or contains another geometry.
	//
	STDMETHOD(CompareWithGeometry)(
		_In_ IGL2DGeometry *inputGeometry,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		float flatteningTolerance,
		_Out_ GL2D_GEOMETRY_RELATION *relation 
		) const PURE;
    
    
	//
	// Converts a geometry to a simplified geometry that has arcs and quadratic beziers
	// removed.
	//
	STDMETHOD(Simplify)(
		GL2D_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const PURE;
    
    
	//
	// Tessellates a geometry into triangles.
	//
	STDMETHOD(Tessellate)(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DTessellationSink *tessellationSink 
		) const PURE;
    
    
	//
	// Performs a combine operation between the two geometries to produce a resulting
	// geometry.
	//
	STDMETHOD(CombineWithGeometry)(
		_In_ IGL2DGeometry *inputGeometry,
		GL2D_COMBINE_MODE combineMode,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const PURE;
    
    
	//
	// Computes the outline of the geometry. The result is written back into a
	// simplified geometry sink.
	//
	STDMETHOD(Outline)(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const PURE;
    
    
	//
	// Computes the area of the geometry.
	//
	STDMETHOD(ComputeArea)(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ float *area 
		) const PURE;
    
    
	//
	// Computes the length of the geometry.
	//
	STDMETHOD(ComputeLength)(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ float *length 
		) const PURE;
    
    
	//
	// Computes the point and tangent a given distance along the path.
	//
	STDMETHOD(ComputePointAtLength)(
		float length,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_opt_ GL2D_POINT_2F *point,
		_Out_opt_ GL2D_POINT_2F *unitTangentVector 
		) const PURE;
    
    
	//
	// Get the geometry and widen it as well as apply an optional pen style.
	//
	STDMETHOD(Widen)(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const PURE;
    
    
	//
	// Retrieve the bounds of the geometry, with an optional applied transform.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	GetBounds(
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ GL2D_RECT_F *bounds 
		) const  
	{
		return GetBounds(&worldTransform, bounds);
	}
    
    
	//
	// Get the bounds of the corresponding geometry after it has been widened or have
	// an optional pen style applied.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	GetWidenedBounds(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_ GL2D_RECT_F *bounds 
		) const  
	{
		return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, bounds);
	}
    
    
	//
	// Get the bounds of the corresponding geometry after it has been widened or have
	// an optional pen style applied.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	GetWidenedBounds(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ GL2D_RECT_F *bounds 
		) const  
	{
		return GetWidenedBounds(strokeWidth, strokeStyle, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, bounds);
	}
    
    
	//
	// Get the bounds of the corresponding geometry after it has been widened or have
	// an optional pen style applied.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	GetWidenedBounds(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ GL2D_RECT_F *bounds 
		) const  
	{
		return GetWidenedBounds(strokeWidth, strokeStyle, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, bounds);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	StrokeContainsPoint(
		GL2D_POINT_2F point,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) const  
	{
		return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, contains);
	}
    
    
	//
	// Checks to see whether the corresponding penned and widened geometry contains the
	// given point.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	StrokeContainsPoint(
		GL2D_POINT_2F point,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ bool *contains 
		) const  
	{
		return StrokeContainsPoint(point, strokeWidth, strokeStyle, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, contains);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	StrokeContainsPoint(
		GL2D_POINT_2F point,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ bool *contains 
		) const  
	{
		return StrokeContainsPoint(point, strokeWidth, strokeStyle, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, contains);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	FillContainsPoint(
		GL2D_POINT_2F point,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) const  
	{
		return FillContainsPoint(point, &worldTransform, flatteningTolerance, contains);
	}
    
    
	//
	// Test whether the given fill of this geometry would contain this point.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	FillContainsPoint(
		GL2D_POINT_2F point,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ bool *contains 
		) const  
	{
		return FillContainsPoint(point, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, contains);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	FillContainsPoint(
		GL2D_POINT_2F point,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ bool *contains 
		) const  
	{
		return FillContainsPoint(point, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, contains);
	}
    
    
	//
	// Compare how one geometry intersects or contains another geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CompareWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		const GL2D_MATRIX_3X2_F &inputGeometryTransform,
		float flatteningTolerance,
		_Out_ GL2D_GEOMETRY_RELATION *relation 
		) const  
	{
		return CompareWithGeometry(inputGeometry, &inputGeometryTransform, flatteningTolerance, relation);
	}
    
    
	//
	// Compare how one geometry intersects or contains another geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CompareWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		_Out_ GL2D_GEOMETRY_RELATION *relation 
		) const  
	{
		return CompareWithGeometry(inputGeometry, inputGeometryTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, relation);
	}
    
    
	//
	// Compare how one geometry intersects or contains another geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CompareWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		const GL2D_MATRIX_3X2_F &inputGeometryTransform,
		_Out_ GL2D_GEOMETRY_RELATION *relation 
		) const  
	{
		return CompareWithGeometry(inputGeometry, &inputGeometryTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, relation);
	}
    
    
	//
	// Converts a geometry to a simplified geometry that has arcs and quadratic beziers
	// removed.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Simplify(
		GL2D_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Simplify(simplificationOption, &worldTransform, flatteningTolerance, geometrySink);
	}
    
    
	//
	// Converts a geometry to a simplified geometry that has arcs and quadratic beziers
	// removed.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Simplify(
		GL2D_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Simplify(simplificationOption, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Converts a geometry to a simplified geometry that has arcs and quadratic beziers
	// removed.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Simplify(
		GL2D_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Simplify(simplificationOption, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Tessellates a geometry into triangles.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Tessellate(
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_In_ IGL2DTessellationSink *tessellationSink 
		) const  
	{
		return Tessellate(&worldTransform, flatteningTolerance, tessellationSink);
	}
    
    
	//
	// Tessellates a geometry into triangles.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Tessellate(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_In_ IGL2DTessellationSink *tessellationSink 
		) const  
	{
		return Tessellate(worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, tessellationSink);
	}
    
    
	//
	// Tessellates a geometry into triangles.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Tessellate(
		const GL2D_MATRIX_3X2_F &worldTransform,
		_In_ IGL2DTessellationSink *tessellationSink 
		) const  
	{
		return Tessellate(&worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, tessellationSink);
	}
    
    
	//
	// Performs a combine operation between the two geometries to produce a resulting
	// geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CombineWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		GL2D_COMBINE_MODE combineMode,
		const GL2D_MATRIX_3X2_F &inputGeometryTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, flatteningTolerance, geometrySink);
	}
    
    
	//
	// Performs a combine operation between the two geometries to produce a resulting
	// geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CombineWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		GL2D_COMBINE_MODE combineMode,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return CombineWithGeometry(inputGeometry, combineMode, inputGeometryTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Performs a combine operation between the two geometries to produce a resulting
	// geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CombineWithGeometry(
		_In_ IGL2DGeometry *inputGeometry,
		GL2D_COMBINE_MODE combineMode,
		const GL2D_MATRIX_3X2_F &inputGeometryTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return CombineWithGeometry(inputGeometry, combineMode, &inputGeometryTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Computes the outline of the geometry. The result is written back into a
	// simplified geometry sink.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Outline(
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Outline(&worldTransform, flatteningTolerance, geometrySink);
	}
    
    
	//
	// Computes the outline of the geometry. The result is written back into a
	// simplified geometry sink.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Outline(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Outline(worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Computes the outline of the geometry. The result is written back into a
	// simplified geometry sink.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Outline(
		const GL2D_MATRIX_3X2_F &worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Outline(&worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Computes the area of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeArea(
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_ float *area 
		) const  
	{
		return ComputeArea(&worldTransform, flatteningTolerance, area);
	}
    
    
	//
	// Computes the area of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeArea(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ float *area 
		) const  
	{
		return ComputeArea(worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, area);
	}
    
    
	//
	// Computes the area of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeArea(
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ float *area 
		) const  
	{
		return ComputeArea(&worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, area);
	}
    
    
	//
	// Computes the length of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeLength(
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_ float *length 
		) const  
	{
		return ComputeLength(&worldTransform, flatteningTolerance, length);
	}
    
    
	//
	// Computes the length of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeLength(
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ float *length 
		) const  
	{
		return ComputeLength(worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, length);
	}
    
    
	//
	// Computes the length of the geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputeLength(
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_ float *length 
		) const  
	{
		return ComputeLength(&worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, length);
	}
    
    
	//
	// Computes the point and tangent a given distance along the path.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputePointAtLength(
		float length,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_Out_opt_ GL2D_POINT_2F *point,
		_Out_opt_ GL2D_POINT_2F *unitTangentVector 
		) const  
	{
		return ComputePointAtLength(length, &worldTransform, flatteningTolerance, point, unitTangentVector);
	}
    
    
	//
	// Computes the point and tangent a given distance along the path.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputePointAtLength(
		float length,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_opt_ GL2D_POINT_2F *point,
		_Out_opt_ GL2D_POINT_2F *unitTangentVector 
		) const  
	{
		return ComputePointAtLength(length, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector);
	}
    
    
	//
	// Computes the point and tangent a given distance along the path.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	ComputePointAtLength(
		float length,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_Out_opt_ GL2D_POINT_2F *point,
		_Out_opt_ GL2D_POINT_2F *unitTangentVector 
		) const  
	{
		return ComputePointAtLength(length, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector);
	}
    
    
	//
	// Get the geometry and widen it as well as apply an optional pen style.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Widen(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Widen(strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, geometrySink);
	}
    
    
	//
	// Get the geometry and widen it as well as apply an optional pen style.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Widen(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Widen(strokeWidth, strokeStyle, worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
    
    
	//
	// Get the geometry and widen it as well as apply an optional pen style.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	Widen(
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		const GL2D_MATRIX_3X2_F &worldTransform,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) const  
	{
		return Widen(strokeWidth, strokeStyle, &worldTransform, GL2D_DEFAULT_FLATTENING_TOLERANCE, geometrySink);
	}
}; // interface IGL2DGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DRectangleGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a2-12e2-11dc-9fed-001143a055f9") IGL2DRectangleGeometry  : public IGL2DGeometry
{
    
	STDMETHOD_(void, GetRect)(
		_Out_ GL2D_RECT_F *rect 
		) const PURE;
}; // interface IGL2DRectangleGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DRoundedRectangleGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a3-12e2-11dc-9fed-001143a055f9") IGL2DRoundedRectangleGeometry  : public IGL2DGeometry
{
    
	STDMETHOD_(void, GetRoundedRect)(
		_Out_ GL2D_ROUNDED_RECT *roundedRect 
		) const PURE;
}; // interface IGL2DRoundedRectangleGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DEllipseGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a4-12e2-11dc-9fed-001143a055f9") IGL2DEllipseGeometry  : public IGL2DGeometry
{
    
	STDMETHOD_(void, GetEllipse)(
		_Out_ GL2D_ELLIPSE *ellipse 
		) const PURE;
}; // interface IGL2DEllipseGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DGeometryGroup
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a6-12e2-11dc-9fed-001143a055f9") IGL2DGeometryGroup  : public IGL2DGeometry
{
    
	STDMETHOD_(GL2D_FILL_MODE, GetFillMode)(
		) const PURE;
    
	STDMETHOD_(uint32_t, GetSourceGeometryCount)(
		) const PURE;
    
	STDMETHOD_(void, GetSourceGeometries)(
		_Out_writes_(geometriesCount) IGL2DGeometry **geometries,
		uint32_t geometriesCount 
		) const PURE;
}; // interface IGL2DGeometryGroup



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DTransformedGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906bb-12e2-11dc-9fed-001143a055f9") IGL2DTransformedGeometry  : public IGL2DGeometry
{
    
	STDMETHOD_(void, GetSourceGeometry)(
		_Outptr_ IGL2DGeometry **sourceGeometry 
		) const PURE;
    
	STDMETHOD_(void, GetTransform)(
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) const PURE;
}; // interface IGL2DTransformedGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DSimplifiedGeometrySink
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd9069e-12e2-11dc-9fed-001143a055f9") IGL2DSimplifiedGeometrySink  : public IUnknown
{
    
	STDMETHOD_(void, SetFillMode)(
		GL2D_FILL_MODE fillMode 
		) PURE;
    
	STDMETHOD_(void, SetSegmentFlags)(
		GL2D_PATH_SEGMENT vertexFlags 
		) PURE;
    
	STDMETHOD_(void, BeginFigure)(
		GL2D_POINT_2F startPoint,
		GL2D_FIGURE_BEGIN figureBegin 
		) PURE;
    
	STDMETHOD_(void, AddLines)(
		_In_reads_(pointsCount) const GL2D_POINT_2F *points,
		uint32_t pointsCount 
		) PURE;
    
	STDMETHOD_(void, AddBeziers)(
		_In_reads_(beziersCount) const GL2D_BEZIER_SEGMENT *beziers,
		uint32_t beziersCount 
		) PURE;
    
	STDMETHOD_(void, EndFigure)(
		GL2D_FIGURE_END figureEnd 
		) PURE;
    
	STDMETHOD(Close)(
		) PURE;
}; // interface IGL2DSimplifiedGeometrySink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DGeometrySink
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd9069f-12e2-11dc-9fed-001143a055f9") IGL2DGeometrySink  : public IGL2DSimplifiedGeometrySink
{
    
	STDMETHOD_(void, AddLine)(
		GL2D_POINT_2F point 
		) PURE;
    
	STDMETHOD_(void, AddBezier)(
		_In_ const GL2D_BEZIER_SEGMENT *bezier 
		) PURE;
    
	STDMETHOD_(void, AddQuadraticBezier)(
		_In_ const GL2D_QUADRATIC_BEZIER_SEGMENT *bezier 
		) PURE;
    
	STDMETHOD_(void, AddQuadraticBeziers)(
		_In_reads_(beziersCount) const GL2D_QUADRATIC_BEZIER_SEGMENT *beziers,
		uint32_t beziersCount 
		) PURE;
    
	STDMETHOD_(void, AddArc)(
		_In_ const GL2D_ARC_SEGMENT *arc 
		) PURE;
    
	COM_DECLSPEC_NOTHROW
	void
	AddBezier(
		const GL2D_BEZIER_SEGMENT &bezier 
		)  
	{
		AddBezier(&bezier);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	AddQuadraticBezier(
		const GL2D_QUADRATIC_BEZIER_SEGMENT &bezier 
		)  
	{
		AddQuadraticBezier(&bezier);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	AddArc(
		const GL2D_ARC_SEGMENT &arc 
		)  
	{
		AddArc(&arc);
	}
}; // interface IGL2DGeometrySink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DTessellationSink
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906c1-12e2-11dc-9fed-001143a055f9") IGL2DTessellationSink  : public IUnknown
{
    
	STDMETHOD_(void, AddTriangles)(
		_In_reads_(trianglesCount) const GL2D_TRIANGLE *triangles,
		uint32_t trianglesCount 
		) PURE;
    
	STDMETHOD(Close)(
		) PURE;
}; // interface IGL2DTessellationSink



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DPathGeometry
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906a5-12e2-11dc-9fed-001143a055f9") IGL2DPathGeometry  : public IGL2DGeometry
{
    
    
	//
	// Opens a geometry sink that will be used to create this path geometry.
	//
	STDMETHOD(Open)(
		_Outptr_ IGL2DGeometrySink **geometrySink 
		) PURE;
    
    
	//
	// Retrieve the contents of this geometry. The caller passes an implementation of a
	// IGL2DGeometrySink interface to receive the data.
	//
	STDMETHOD(Stream)(
		_In_ IGL2DGeometrySink *geometrySink 
		) const PURE;
    
	STDMETHOD(GetSegmentCount)(
		_Out_ uint32_t *count 
		) const PURE;
    
	STDMETHOD(GetFigureCount)(
		_Out_ uint32_t *count 
		) const PURE;
}; // interface IGL2DPathGeometry



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DMesh
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd906c2-12e2-11dc-9fed-001143a055f9") IGL2DMesh  : public IGL2DResource
{
    
    
	//
	// Opens the mesh for population.
	//
	STDMETHOD(Open)(
		_Outptr_ IGL2DTessellationSink **tessellationSink 
		) PURE;
}; // interface IGL2DMesh



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DLayer
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd9069b-12e2-11dc-9fed-001143a055f9") IGL2DLayer  : public IGL2DResource
{
    
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		) const PURE;
}; // interface IGL2DLayer



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DDrawingStateBlock
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("28506e39-ebf6-46a1-bb47-fd85565ab957") IGL2DDrawingStateBlock  : public IGL2DResource
{
    
    
	//
	// Retrieves the state currently contained within this state block resource.
	//
	STDMETHOD_(void, GetDescription)(
		_Out_ GL2D_DRAWING_STATE_DESCRIPTION *stateDescription 
		) const PURE;
    
    
	//
	// Sets the state description of this state block resource.
	//
	STDMETHOD_(void, SetDescription)(
		_In_ const GL2D_DRAWING_STATE_DESCRIPTION *stateDescription 
		) PURE;
    
    
	//
	// Sets the text rendering parameters of this state block resource.
	//
	STDMETHOD_(void, SetTextRenderingParams)(
		_In_opt_ IDWriteRenderingParams *textRenderingParams = NULL 
		) PURE;
    
    
	//
	// Retrieves the text rendering parameters contained within this state block
	// resource. If a NULL text rendering parameter was specified, NULL will be
	// returned.
	//
	STDMETHOD_(void, GetTextRenderingParams)(
		_Outptr_result_maybenull_ IDWriteRenderingParams **textRenderingParams 
		) const PURE;
    
	COM_DECLSPEC_NOTHROW
	void
	SetDescription(
		const GL2D_DRAWING_STATE_DESCRIPTION &stateDescription 
		)  
	{
		SetDescription(&stateDescription);
	}
}; // interface IGL2DDrawingStateBlock



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DRenderTarget
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd90694-12e2-11dc-9fed-001143a055f9") IGL2DRenderTarget  : public IGL2DResource
{
    
    
	//
	// Create a D2D bitmap by copying from memory, or create uninitialized.
	//
	STDMETHOD(CreateBitmap)(
		GL2D_SIZE_U size,
		_In_opt_ const void *srcData,
		uint32_t pitch,
		_In_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
    
	//
	// Create a D2D bitmap by copying a WIC bitmap.
	//
	STDMETHOD(CreateBitmapFromWicBitmap)(
		_In_ IWICBitmapSource *wicBitmapSource,
		_In_opt_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
    
	//
	// Create a D2D bitmap by sharing bits from another resource. The bitmap must be
	// compatible with the render target for the call to succeed.
	// For example, an IWICBitmap can be shared with a software target, or a DXGI
	// surface can be shared with a DXGI render target.
	//
	STDMETHOD(CreateSharedBitmap)(
		_In_ REFIID riid,
		_Inout_ void *data,
		_In_opt_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
    
	//
	// Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
	// or pen a geometry.
	//
	STDMETHOD(CreateBitmapBrush)(
		_In_opt_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_Outptr_ IGL2DBitmapBrush **bitmapBrush 
		) PURE;
    
	STDMETHOD(CreateSolidColorBrush)(
		_In_ const GL2D_COLOR_F *color,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_Outptr_ IGL2DSolidColorBrush **solidColorBrush 
		) PURE;
    
    
	//
	// A gradient stop collection represents a set of stops in an ideal unit length.
	// This is the source resource for a linear gradient and radial gradient brush.
	//
	STDMETHOD(CreateGradientStopCollection)(
		_In_reads_(gradientStopsCount) const GL2D_GRADIENT_STOP *gradientStops,
		_In_range_(>=,1) uint32_t gradientStopsCount,
        
		//
		// Specifies which space the color interpolation occurs in.
		//
		GL2D_GAMMA colorInterpolationGamma,
        
		//
		// Specifies how the gradient will be extended outside of the unit length.
		//
		GL2D_EXTEND_MODE extendMode,
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) PURE;
    
	STDMETHOD(CreateLinearGradientBrush)(
		_In_ const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DLinearGradientBrush **linearGradientBrush 
		) PURE;
    
	STDMETHOD(CreateRadialGradientBrush)(
		_In_ const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DRadialGradientBrush **radialGradientBrush 
		) PURE;
    
    
	//
	// Creates a bitmap render target whose bitmap can be used as a source for
	// rendering in the API.
	//
	STDMETHOD(CreateCompatibleRenderTarget)(
        
		//
		// The requested size of the target in DIPs. If the pixel size is not specified,
		// the DPI is inherited from the parent target. However, the render target will
		// never contain a fractional number of pixels.
		//
		_In_opt_ const GL2D_SIZE_F *desiredSize,
        
		//
		// The requested size of the render target in pixels. If the DIP size is also
		// specified, the DPI is calculated from these two values. If the desired size is
		// not specified, the DPI is inherited from the parent render target. If neither
		// value is specified, the compatible render target will be the same size and have
		// the same DPI as the parent target.
		//
		_In_opt_ const GL2D_SIZE_U *desiredPixelSize,
        
		//
		// The desired pixel format. The format must be compatible with the parent render
		// target type. If the format is not specified, it will be inherited from the
		// parent render target.
		//
		_In_opt_ const GL2D_PIXEL_FORMAT *desiredFormat,
        
		//
		// Allows the caller to retrieve a GDI compatible render target.
		//
		GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        
		//
		// The returned bitmap render target.
		//
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		) PURE;
    
    
	//
	// Creates a layer resource that can be used on any target and which will resize
	// under the covers if necessary.
	//
	STDMETHOD(CreateLayer)(
        
		//
		// The resolution independent minimum size hint for the layer resource. Specify
		// this to prevent unwanted reallocation of the layer backing store. The size is in
		// DIPs, but, it is unaffected by the current world transform. If the size is
		// unspecified, the returned resource is a placeholder and the backing store will
		// be allocated to be the minimum size that can hold the content when the layer is
		// pushed.
		//
		_In_opt_ const GL2D_SIZE_F *size,
		_Outptr_ IGL2DLayer **layer 
		) PURE;
    
    
	//
	// Create a D2D mesh.
	//
	STDMETHOD(CreateMesh)(
		_Outptr_ IGL2DMesh **mesh 
		) PURE;
    
	STDMETHOD_(void, DrawLine)(
		GL2D_POINT_2F point0,
		GL2D_POINT_2F point1,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		) PURE;
    
	STDMETHOD_(void, DrawRectangle)(
		_In_ const GL2D_RECT_F *rect,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		) PURE;
    
	STDMETHOD_(void, FillRectangle)(
		_In_ const GL2D_RECT_F *rect,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawRoundedRectangle)(
		_In_ const GL2D_ROUNDED_RECT *roundedRect,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		) PURE;
    
	STDMETHOD_(void, FillRoundedRectangle)(
		_In_ const GL2D_ROUNDED_RECT *roundedRect,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawEllipse)(
		_In_ const GL2D_ELLIPSE *ellipse,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		) PURE;
    
	STDMETHOD_(void, FillEllipse)(
		_In_ const GL2D_ELLIPSE *ellipse,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawGeometry)(
		_In_ IGL2DGeometry *geometry,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		) PURE;
    
	STDMETHOD_(void, FillGeometry)(
		_In_ IGL2DGeometry *geometry,
		_In_ IGL2DBrush *brush,
        
		//
		// An optionally specified opacity brush. Only the alpha channel of the
		// corresponding brush will be sampled and will be applied to the entire fill of
		// the geometry. If this brush is specified, the fill brush must be a bitmap brush
		// with an extend mode of GL2D_EXTEND_MODE_CLAMP.
		//
		_In_opt_ IGL2DBrush *opacityBrush = NULL 
		) PURE;
    
    
	//
	// Fill a mesh. Since meshes can only render aliased content, the render target
	// antialiasing mode must be set to aliased.
	//
	STDMETHOD_(void, FillMesh)(
		_In_ IGL2DMesh *mesh,
		_In_ IGL2DBrush *brush 
		) PURE;
    
    
	//
	// Fill using the alpha channel of the supplied opacity mask bitmap. The brush
	// opacity will be modulated by the mask. The render target antialiasing mode must
	// be set to aliased.
	//
	STDMETHOD_(void, FillOpacityMask)(
		_In_ IGL2DBitmap *opacityMask,
		_In_ IGL2DBrush *brush,
		GL2D_OPACITY_MASK_CONTENT content,
		_In_opt_ const GL2D_RECT_F *destinationRectangle = NULL,
		_In_opt_ const GL2D_RECT_F *sourceRectangle = NULL 
		) PURE;
    
	STDMETHOD_(void, DrawBitmap)(
		_In_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_RECT_F *destinationRectangle = NULL,
		float opacity = 1.0f,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode = GL2D_BITMAP_INTERPOLATION_MODE_LINEAR,
		_In_opt_ const GL2D_RECT_F *sourceRectangle = NULL 
		) PURE;
    
    
	//
	// Draws the text within the given layout rectangle and by default also snaps and
	// clips it to the content bounds.
	//
	STDMETHOD_(void, DrawText)(
		_In_reads_(stringLength) const WCHAR *string,
		uint32_t stringLength,
		_In_ IDWriteTextFormat *textFormat,
		_In_ const GL2D_RECT_F *layoutRect,
		_In_ IGL2DBrush *defaultForegroundBrush,
		GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE,
		DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
		) PURE;
    
    
	//
	// Draw a snapped text layout object. Since the layout is not subsequently changed,
	// this can be more efficient than DrawText when drawing the same layout
	// repeatedly.
	//
	STDMETHOD_(void, DrawTextLayout)(
		GL2D_POINT_2F origin,
		_In_ IDWriteTextLayout *textLayout,
		_In_ IGL2DBrush *defaultForegroundBrush,
        
		//
		// The specified text options. NOTE: By default the text is clipped to the layout
		// bounds. This is derived from the origin and the layout bounds of the
		// corresponding IDWriteTextLayout object.
		//
		GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE 
		) PURE;
    
	STDMETHOD_(void, DrawGlyphRun)(
		GL2D_POINT_2F baselineOrigin,
		_In_ const DWRITE_GLYPH_RUN *glyphRun,
		_In_ IGL2DBrush *foregroundBrush,
		DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
		) PURE;
    
	STDMETHOD_(void, SetTransform)(
		_In_ const GL2D_MATRIX_3X2_F *transform 
		) PURE;
    
	STDMETHOD_(void, GetTransform)(
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) const PURE;
    
	STDMETHOD_(void, SetAntialiasMode)(
		GL2D_ANTIALIAS_MODE antialiasMode 
		) PURE;
    
	STDMETHOD_(GL2D_ANTIALIAS_MODE, GetAntialiasMode)(
		) const PURE;
    
	STDMETHOD_(void, SetTextAntialiasMode)(
		GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode 
		) PURE;
    
	STDMETHOD_(GL2D_TEXT_ANTIALIAS_MODE, GetTextAntialiasMode)(
		) const PURE;
    
	STDMETHOD_(void, SetTextRenderingParams)(
		_In_opt_ IDWriteRenderingParams *textRenderingParams = NULL 
		) PURE;
    
    
	//
	// Retrieve the text render parameters. NOTE: If NULL is specified to
	// SetTextRenderingParameters, NULL will be returned.
	//
	STDMETHOD_(void, GetTextRenderingParams)(
		_Outptr_result_maybenull_ IDWriteRenderingParams **textRenderingParams 
		) const PURE;
    
    
	//
	// Set a tag to correspond to the succeeding primitives. If an error occurs
	// rendering a primitive, the tags can be returned from the Flush or EndDraw call.
	//
	STDMETHOD_(void, SetTags)(
		GL2D_TAG tag1,
		GL2D_TAG tag2 
		) PURE;
    
    
	//
	// Retrieves the currently set tags. This does not retrieve the tags corresponding
	// to any primitive that is in error.
	//
	STDMETHOD_(void, GetTags)(
		_Out_opt_ GL2D_TAG *tag1 = NULL,
		_Out_opt_ GL2D_TAG *tag2 = NULL 
		) const PURE;
    
    
	//
	// Start a layer of drawing calls. The way in which the layer must be resolved is
	// specified first as well as the logical resource that stores the layer
	// parameters. The supplied layer resource might grow if the specified content
	// cannot fit inside it. The layer will grow monotonically on each axis.  If a NULL
	// IGL2DLayer is provided, then a layer resource will be allocated automatically.
	//
	STDMETHOD_(void, PushLayer)(
		_In_ const GL2D_LAYER_PARAMETERS *layerParameters,
		_In_opt_ IGL2DLayer *layer 
		) PURE;
    
    
	//
	// Ends a layer that was defined with particular layer resources.
	//
	STDMETHOD_(void, PopLayer)(
		) PURE;
    
	STDMETHOD(Flush)(
		_Out_opt_ GL2D_TAG *tag1 = NULL,
		_Out_opt_ GL2D_TAG *tag2 = NULL 
		) PURE;
    
    
	//
	// Gets the current drawing state and saves it into the supplied
	// IDrawingStatckBlock.
	//
	STDMETHOD_(void, SaveDrawingState)(
		_Inout_ IGL2DDrawingStateBlock *drawingStateBlock 
		) const PURE;
    
    
	//
	// Copies the state stored in the block interface.
	//
	STDMETHOD_(void, RestoreDrawingState)(
		_In_ IGL2DDrawingStateBlock *drawingStateBlock 
		) PURE;
    
    
	//
	// Pushes a clip. The clip can be antialiased. The clip must be axis aligned. If
	// the current world transform is not axis preserving, then the bounding box of the
	// transformed clip rect will be used. The clip will remain in effect until a
	// PopAxisAligned clip call is made.
	//
	STDMETHOD_(void, PushAxisAlignedClip)(
		_In_ const GL2D_RECT_F *clipRect,
		GL2D_ANTIALIAS_MODE antialiasMode 
		) PURE;
    
	STDMETHOD_(void, PopAxisAlignedClip)(
		) PURE;
    
	STDMETHOD_(void, Clear)(
		_In_opt_ const GL2D_COLOR_F *clearColor = NULL 
		) PURE;
    
    
	//
	// Start drawing on this render target. Draw calls can only be issued between a
	// BeginDraw and EndDraw call.
	//
	STDMETHOD_(void, BeginDraw)(
		) PURE;
    
    
	//
	// Ends drawing on the render target, error results can be retrieved at this time,
	// or when calling flush.
	//
	STDMETHOD(EndDraw)(
		_Out_opt_ GL2D_TAG *tag1 = NULL,
		_Out_opt_ GL2D_TAG *tag2 = NULL 
		) PURE;
    
	STDMETHOD_(GL2D_PIXEL_FORMAT, GetPixelFormat)(
		) const PURE;
    
    
	//
	// Sets the DPI on the render target. This results in the render target being
	// interpreted to a different scale. Neither DPI can be negative. If zero is
	// specified for both, the system DPI is chosen. If one is zero and the other
	// unspecified, the DPI is not changed.
	//
	STDMETHOD_(void, SetDpi)(
		float dpiX,
		float dpiY 
		) PURE;
    
    
	//
	// Return the current DPI from the target.
	//
	STDMETHOD_(void, GetDpi)(
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) const PURE;
    
    
	//
	// Returns the size of the render target in DIPs.
	//
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		) const PURE;
    
    
	//
	// Returns the size of the render target in pixels.
	//
	STDMETHOD_(GL2D_SIZE_U, GetPixelSize)(
		) const PURE;
    
    
	//
	// Returns the maximum bitmap and render target size that is guaranteed to be
	// supported by the render target.
	//
	STDMETHOD_(uint32_t, GetMaximumBitmapSize)(
		) const PURE;
    
    
	//
	// Returns true if the given properties are supported by this render target. The
	// DPI is ignored. NOTE: If the render target type is software, then neither
	// GL2D_FEATURE_LEVEL_9 nor GL2D_FEATURE_LEVEL_10 will be considered to be
	// supported.
	//
	STDMETHOD_(bool, IsSupported)(
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties 
		) const PURE;
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmap(
		GL2D_SIZE_U size,
		_In_opt_ const void *srcData,
		uint32_t pitch,
		const GL2D_BITMAP_PROPERTIES &bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		)  
	{
		return CreateBitmap(size, srcData, pitch, &bitmapProperties, bitmap);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmap(
		GL2D_SIZE_U size,
		const GL2D_BITMAP_PROPERTIES &bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		)  
	{
		return CreateBitmap(size, NULL, 0, &bitmapProperties, bitmap);
	}
    
    
	//
	// Create a D2D bitmap by copying a WIC bitmap.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmapFromWicBitmap(
		_In_ IWICBitmapSource *wicBitmapSource,
		const GL2D_BITMAP_PROPERTIES &bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		)  
	{
		return CreateBitmapFromWicBitmap(wicBitmapSource, &bitmapProperties, bitmap);
	}
    
    
	//
	// Create a D2D bitmap by copying a WIC bitmap.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmapFromWicBitmap(
		_In_ IWICBitmapSource *wicBitmapSource,
		_Outptr_ IGL2DBitmap **bitmap 
		)  
	{
		return CreateBitmapFromWicBitmap(wicBitmapSource, NULL, bitmap);
	}
    
    
	//
	// Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
	// or pen a geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmapBrush(
		_In_opt_ IGL2DBitmap *bitmap,
		_Outptr_ IGL2DBitmapBrush **bitmapBrush 
		)  
	{
		return CreateBitmapBrush(bitmap, NULL, NULL, bitmapBrush);
	}
    
    
	//
	// Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
	// or pen a geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmapBrush(
		_In_opt_ IGL2DBitmap *bitmap,
		const GL2D_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
		_Outptr_ IGL2DBitmapBrush **bitmapBrush 
		)  
	{
		return CreateBitmapBrush(bitmap, &bitmapBrushProperties, NULL, bitmapBrush);
	}
    
    
	//
	// Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
	// or pen a geometry.
	//
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateBitmapBrush(
		_In_opt_ IGL2DBitmap *bitmap,
		const GL2D_BITMAP_BRUSH_PROPERTIES &bitmapBrushProperties,
		const GL2D_BRUSH_PROPERTIES &brushProperties,
		_Outptr_ IGL2DBitmapBrush **bitmapBrush 
		)  
	{
		return CreateBitmapBrush(bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateSolidColorBrush(
		const GL2D_COLOR_F &color,
		_Outptr_ IGL2DSolidColorBrush **solidColorBrush 
		)  
	{
		return CreateSolidColorBrush(&color, NULL, solidColorBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateSolidColorBrush(
		const GL2D_COLOR_F &color,
		const GL2D_BRUSH_PROPERTIES &brushProperties,
		_Outptr_ IGL2DSolidColorBrush **solidColorBrush 
		)  
	{
		return CreateSolidColorBrush(&color, &brushProperties, solidColorBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateGradientStopCollection(
		_In_reads_(gradientStopsCount) const GL2D_GRADIENT_STOP *gradientStops,
		uint32_t gradientStopsCount,
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		)  
	{
		return CreateGradientStopCollection(gradientStops, gradientStopsCount, GL2D_GAMMA_2_2, GL2D_EXTEND_MODE_CLAMP, gradientStopCollection);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateLinearGradientBrush(
		const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DLinearGradientBrush **linearGradientBrush 
		)  
	{
		return CreateLinearGradientBrush(&linearGradientBrushProperties, NULL, gradientStopCollection, linearGradientBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateLinearGradientBrush(
		const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES &linearGradientBrushProperties,
		const GL2D_BRUSH_PROPERTIES &brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DLinearGradientBrush **linearGradientBrush 
		)  
	{
		return CreateLinearGradientBrush(&linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateRadialGradientBrush(
		const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DRadialGradientBrush **radialGradientBrush 
		)  
	{
		return CreateRadialGradientBrush(&radialGradientBrushProperties, NULL, gradientStopCollection, radialGradientBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateRadialGradientBrush(
		const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES &radialGradientBrushProperties,
		const GL2D_BRUSH_PROPERTIES &brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DRadialGradientBrush **radialGradientBrush 
		)  
	{
		return CreateRadialGradientBrush(&radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateCompatibleRenderTarget(
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		)  
	{
		return CreateCompatibleRenderTarget(NULL, NULL, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateCompatibleRenderTarget(
		GL2D_SIZE_F desiredSize,
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		)  
	{
		return CreateCompatibleRenderTarget(&desiredSize, NULL, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateCompatibleRenderTarget(
		GL2D_SIZE_F desiredSize,
		GL2D_SIZE_U desiredPixelSize,
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		)  
	{
		return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, NULL, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateCompatibleRenderTarget(
		GL2D_SIZE_F desiredSize,
		GL2D_SIZE_U desiredPixelSize,
		GL2D_PIXEL_FORMAT desiredFormat,
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		)  
	{
		return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, bitmapRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateCompatibleRenderTarget(
		GL2D_SIZE_F desiredSize,
		GL2D_SIZE_U desiredPixelSize,
		GL2D_PIXEL_FORMAT desiredFormat,
		GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options,
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		)  
	{
		return CreateCompatibleRenderTarget(&desiredSize, &desiredPixelSize, &desiredFormat, options, bitmapRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateLayer(
		GL2D_SIZE_F size,
		_Outptr_ IGL2DLayer **layer 
		)  
	{
		return CreateLayer(&size, layer);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateLayer(
		_Outptr_ IGL2DLayer **layer 
		)  
	{
		return CreateLayer(NULL, layer);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	DrawRectangle(
		const GL2D_RECT_F &rect,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		)  
	{
		DrawRectangle(&rect, brush, strokeWidth, strokeStyle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	FillRectangle(
		const GL2D_RECT_F &rect,
		_In_ IGL2DBrush *brush 
		)  
	{
		FillRectangle(&rect, brush);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	DrawRoundedRectangle(
		const GL2D_ROUNDED_RECT &roundedRect,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		)  
	{
		DrawRoundedRectangle(&roundedRect, brush, strokeWidth, strokeStyle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	FillRoundedRectangle(
		const GL2D_ROUNDED_RECT &roundedRect,
		_In_ IGL2DBrush *brush 
		)  
	{
		FillRoundedRectangle(&roundedRect, brush);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	DrawEllipse(
		const GL2D_ELLIPSE &ellipse,
		_In_ IGL2DBrush *brush,
		float strokeWidth = 1.0f,
		_In_opt_ IGL2DStrokeStyle *strokeStyle = NULL 
		)  
	{
		DrawEllipse(&ellipse, brush, strokeWidth, strokeStyle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	FillEllipse(
		const GL2D_ELLIPSE &ellipse,
		_In_ IGL2DBrush *brush 
		)  
	{
		FillEllipse(&ellipse, brush);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	FillOpacityMask(
		_In_ IGL2DBitmap *opacityMask,
		_In_ IGL2DBrush *brush,
		GL2D_OPACITY_MASK_CONTENT content,
		const GL2D_RECT_F &destinationRectangle,
		const GL2D_RECT_F &sourceRectangle 
		)  
	{
		FillOpacityMask(opacityMask, brush, content, &destinationRectangle, &sourceRectangle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	DrawBitmap(
		_In_ IGL2DBitmap *bitmap,
		const GL2D_RECT_F &destinationRectangle,
		float opacity = 1.0f,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode = GL2D_BITMAP_INTERPOLATION_MODE_LINEAR,
		_In_opt_ const GL2D_RECT_F *sourceRectangle = NULL 
		)  
	{
		DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	DrawBitmap(
		_In_ IGL2DBitmap *bitmap,
		const GL2D_RECT_F &destinationRectangle,
		float opacity,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode,
		const GL2D_RECT_F &sourceRectangle 
		)  
	{
		DrawBitmap(bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	SetTransform(
		const GL2D_MATRIX_3X2_F &transform 
		)  
	{
		SetTransform(&transform);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	PushLayer(
		const GL2D_LAYER_PARAMETERS &layerParameters,
		_In_opt_ IGL2DLayer *layer 
		)  
	{
		PushLayer(&layerParameters, layer);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	PushAxisAlignedClip(
		const GL2D_RECT_F &clipRect,
		GL2D_ANTIALIAS_MODE antialiasMode 
		)  
	{
		return PushAxisAlignedClip(&clipRect, antialiasMode);
	}
    
	COM_DECLSPEC_NOTHROW
	void
	Clear(
		const GL2D_COLOR_F &clearColor 
		)  
	{
		return Clear(&clearColor);
	}
    
    
	//
	// Draws the text within the given layout rectangle and by default also snaps and
	// clips it.
	//
	COM_DECLSPEC_NOTHROW
	void
	DrawText(
		_In_reads_(stringLength) const WCHAR *string,
		uint32_t stringLength,
		_In_ IDWriteTextFormat *textFormat,
		const GL2D_RECT_F &layoutRect,
		_In_ IGL2DBrush *defaultForegroundBrush,
		GL2D_DRAW_TEXT_OPTIONS options = GL2D_DRAW_TEXT_OPTIONS_NONE,
		DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL 
		)  
	{
		return DrawText(string, stringLength, textFormat, &layoutRect, defaultForegroundBrush, options, measuringMode);
	}
    
	COM_DECLSPEC_NOTHROW
	bool
	IsSupported(
		const GL2D_RENDER_TARGET_PROPERTIES &renderTargetProperties 
		) const  
	{
		return IsSupported(&renderTargetProperties);
	}
}; // interface IGL2DRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DBitmapRenderTarget
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd90695-12e2-11dc-9fed-001143a055f9") IGL2DBitmapRenderTarget  : public IGL2DRenderTarget
{
    
	STDMETHOD(GetBitmap)(
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
}; // interface IGL2DBitmapRenderTarget


//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DHwndRenderTarget
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("2cd90698-12e2-11dc-9fed-001143a055f9") IGL2DHwndRenderTarget  : public IGL2DRenderTarget
{
    
	STDMETHOD_(GL2D_WINDOW_STATE, CheckWindowState)(
		) PURE;
    
    
	//
	// Resize the buffer underlying the render target. This operation might fail if
	// there is insufficient video memory or system memory, or if the render target is
	// resized beyond the maximum bitmap size. If the method fails, the render target
	// will be placed in a zombie state and D2DERR_RECREATE_TARGET will be returned
	// from it when EndDraw is called. In addition an appropriate failure result will
	// be returned from Resize.
	//
	STDMETHOD(Resize)(
		_In_ const GL2D_SIZE_U *pixelSize 
		) PURE;
    
	STDMETHOD_(HWND, GetHwnd)(
		) const PURE;
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	Resize(
		const GL2D_SIZE_U &pixelSize 
		)  
	{
		return Resize(&pixelSize);
	}
}; // interface IGL2DHwndRenderTarget

//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DGdiInteropRenderTarget
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("e0db51c3-6f77-4bae-b3d5-e47509b35838") IGL2DGdiInteropRenderTarget  : public IUnknown
{
    
	STDMETHOD(GetDC)(
		GL2D_DC_INITIALIZE_MODE mode,
		_Out_ HDC *hdc 
		) PURE;
    
	STDMETHOD(ReleaseDC)(
		_In_opt_ const RECT *update 
		) PURE;
}; // interface IGL2DGdiInteropRenderTarget

//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DDCRenderTarget
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("1c51bc64-de61-46fd-9899-63a5d8f03950") IGL2DDCRenderTarget  : public IGL2DRenderTarget
{
    
	STDMETHOD(BindDC)(
		_In_ const HDC hDC,
		_In_ const RECT *pSubRect 
		) PURE;
}; // interface IGL2DDCRenderTarget



//+-----------------------------------------------------------------------------
//
//  Interface:
//      IGL2DFactory
//
//  Synopsis:
//      The root factory interface for all of D2D's objects.
//
//------------------------------------------------------------------------------
interface GL_DECLARE_INTERFACE("06152247-6f50-465a-9245-118bfd3b6007") IGL2DFactory  : public IUnknown
{
    
    
	//
	// Cause the factory to refresh any system metrics that it might have been snapped
	// on factory creation.
	//
	STDMETHOD(ReloadSystemMetrics)(
		) PURE;
    
    
	//
	// Retrieves the current desktop DPI. To refresh this, call ReloadSystemMetrics.
	//
	STDMETHOD_(void, GetDesktopDpi)(
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) PURE;
    
	STDMETHOD(CreateRectangleGeometry)(
		_In_ const GL2D_RECT_F *rectangle,
		_Outptr_ IGL2DRectangleGeometry **rectangleGeometry 
		) PURE;
    
	STDMETHOD(CreateRoundedRectangleGeometry)(
		_In_ const GL2D_ROUNDED_RECT *roundedRectangle,
		_Outptr_ IGL2DRoundedRectangleGeometry **roundedRectangleGeometry 
		) PURE;
    
	STDMETHOD(CreateEllipseGeometry)(
		_In_ const GL2D_ELLIPSE *ellipse,
		_Outptr_ IGL2DEllipseGeometry **ellipseGeometry 
		) PURE;
    
    
	//
	// Create a geometry which holds other geometries.
	//
	STDMETHOD(CreateGeometryGroup)(
		GL2D_FILL_MODE fillMode,
		_In_reads_(geometriesCount) IGL2DGeometry **geometries,
		uint32_t geometriesCount,
		_Outptr_ IGL2DGeometryGroup **geometryGroup 
		) PURE;
    
	STDMETHOD(CreateTransformedGeometry)(
		_In_ IGL2DGeometry *sourceGeometry,
		_In_ const GL2D_MATRIX_3X2_F *transform,
		_Outptr_ IGL2DTransformedGeometry **transformedGeometry 
		) PURE;
    
    
	//
	// Returns an initially empty path geometry interface. A geometry sink is created
	// off the interface to populate it.
	//
	STDMETHOD(CreatePathGeometry)(
		_Outptr_ IGL2DPathGeometry **pathGeometry 
		) PURE;
    
    
	//
	// Allows a non-default stroke style to be specified for a given geometry at draw
	// time.
	//
	STDMETHOD(CreateStrokeStyle)(
		_In_ const GL2D_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
		_In_reads_opt_(dashesCount) const float *dashes,
		uint32_t dashesCount,
		_Outptr_ IGL2DStrokeStyle **strokeStyle 
		) PURE;
    
    
	//
	// Creates a new drawing state block, this can be used in subsequent
	// SaveDrawingState and RestoreDrawingState operations on the render target.
	//
	STDMETHOD(CreateDrawingStateBlock)(
		_In_opt_ const GL2D_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
		_In_opt_ IDWriteRenderingParams *textRenderingParams,
		_Outptr_ IGL2DDrawingStateBlock **drawingStateBlock 
		) PURE;
    
    
	//
	// Creates a render target which is a source of bitmaps.
	//
	STDMETHOD(CreateWicBitmapRenderTarget)(
		_In_ IWICBitmap *target,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		) PURE;
    
    
	//
	// Creates a render target that appears on the display.
	//
	STDMETHOD(CreateHwndRenderTarget)(
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_In_ const GL2D_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties,
		_Outptr_ IGL2DHwndRenderTarget **hwndRenderTarget 
		) PURE;
    
    
	//
	// Creates a render target that draws to a DXGI Surface. The device that owns the
	// surface is used for rendering.
	//
	STDMETHOD(CreateDxgiSurfaceRenderTarget)(
		_In_ IDXGISurface *dxgiSurface,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		) PURE;
    
    
	//
	// Creates a render target that draws to a GDI device context.
	//
	STDMETHOD(CreateDCRenderTarget)(
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DDCRenderTarget **dcRenderTarget 
		) PURE;
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateRectangleGeometry(
		const GL2D_RECT_F &rectangle,
		_Outptr_ IGL2DRectangleGeometry **rectangleGeometry 
		)  
	{
		return CreateRectangleGeometry(&rectangle, rectangleGeometry);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateRoundedRectangleGeometry(
		const GL2D_ROUNDED_RECT &roundedRectangle,
		_Outptr_ IGL2DRoundedRectangleGeometry **roundedRectangleGeometry 
		)  
	{
		return CreateRoundedRectangleGeometry(&roundedRectangle, roundedRectangleGeometry);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateEllipseGeometry(
		const GL2D_ELLIPSE &ellipse,
		_Outptr_ IGL2DEllipseGeometry **ellipseGeometry 
		)  
	{
		return CreateEllipseGeometry(&ellipse, ellipseGeometry);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateTransformedGeometry(
		_In_ IGL2DGeometry *sourceGeometry,
		const GL2D_MATRIX_3X2_F &transform,
		_Outptr_ IGL2DTransformedGeometry **transformedGeometry 
		)  
	{
		return CreateTransformedGeometry(sourceGeometry, &transform, transformedGeometry);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateStrokeStyle(
		const GL2D_STROKE_STYLE_PROPERTIES &strokeStyleProperties,
		_In_reads_opt_(dashesCount) const float *dashes,
		uint32_t dashesCount,
		_Outptr_ IGL2DStrokeStyle **strokeStyle 
		)  
	{
		return CreateStrokeStyle(&strokeStyleProperties, dashes, dashesCount, strokeStyle);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateDrawingStateBlock(
		const GL2D_DRAWING_STATE_DESCRIPTION &drawingStateDescription,
		_Outptr_ IGL2DDrawingStateBlock **drawingStateBlock 
		)  
	{
		return CreateDrawingStateBlock(&drawingStateDescription, NULL, drawingStateBlock);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateDrawingStateBlock(
		_Outptr_ IGL2DDrawingStateBlock **drawingStateBlock 
		)  
	{
		return CreateDrawingStateBlock(NULL, NULL, drawingStateBlock);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateWicBitmapRenderTarget(
		_In_ IWICBitmap *target,
		const GL2D_RENDER_TARGET_PROPERTIES &renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		)  
	{
		return CreateWicBitmapRenderTarget(target, &renderTargetProperties, renderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateHwndRenderTarget(
		const GL2D_RENDER_TARGET_PROPERTIES &renderTargetProperties,
		const GL2D_HWND_RENDER_TARGET_PROPERTIES &hwndRenderTargetProperties,
		_Outptr_ IGL2DHwndRenderTarget **hwndRenderTarget 
		)  
	{
		return CreateHwndRenderTarget(&renderTargetProperties, &hwndRenderTargetProperties, hwndRenderTarget);
	}
    
	COM_DECLSPEC_NOTHROW
	HRESULT
	CreateDxgiSurfaceRenderTarget(
		_In_ IDXGISurface *dxgiSurface,
		const GL2D_RENDER_TARGET_PROPERTIES &renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		)  
	{
		return CreateDxgiSurfaceRenderTarget(dxgiSurface, &renderTargetProperties, renderTarget);
	}
}; // interface IGL2DFactory

EXTERN_C const IID IID_IGL2DResource;
EXTERN_C const IID IID_IGL2DImage;
EXTERN_C const IID IID_IGL2DBitmap;
EXTERN_C const IID IID_IGL2DGradientStopCollection;
EXTERN_C const IID IID_IGL2DBrush;
EXTERN_C const IID IID_IGL2DBitmapBrush;
EXTERN_C const IID IID_IGL2DSolidColorBrush;
EXTERN_C const IID IID_IGL2DLinearGradientBrush;
EXTERN_C const IID IID_IGL2DRadialGradientBrush;
EXTERN_C const IID IID_IGL2DStrokeStyle;
EXTERN_C const IID IID_IGL2DGeometry;
EXTERN_C const IID IID_IGL2DRectangleGeometry;
EXTERN_C const IID IID_IGL2DRoundedRectangleGeometry;
EXTERN_C const IID IID_IGL2DEllipseGeometry;
EXTERN_C const IID IID_IGL2DGeometryGroup;
EXTERN_C const IID IID_IGL2DTransformedGeometry;
EXTERN_C const IID IID_IGL2DSimplifiedGeometrySink;
EXTERN_C const IID IID_IGL2DGeometrySink;
EXTERN_C const IID IID_IGL2DTessellationSink;
EXTERN_C const IID IID_IGL2DPathGeometry;
EXTERN_C const IID IID_IGL2DMesh;
EXTERN_C const IID IID_IGL2DLayer;
EXTERN_C const IID IID_IGL2DDrawingStateBlock;
EXTERN_C const IID IID_IGL2DRenderTarget;
EXTERN_C const IID IID_IGL2DBitmapRenderTarget;
EXTERN_C const IID IID_IGL2DHwndRenderTarget;
EXTERN_C const IID IID_IGL2DDCRenderTarget;
EXTERN_C const IID IID_IGL2DFactory;
EXTERN_C const IID IID_IGL2DGdiInteropRenderTarget;

#ifdef GL2D_USE_C_DEFINITIONS

typedef interface IGL2DResource IGL2DResource;

typedef struct IGL2DResourceVtbl
{
    
	IUnknownVtbl Base;
    
    
	STDMETHOD_(void, GetFactory)(
		IGL2DResource *This,
		_Outptr_ IGL2DFactory **factory 
		) PURE;
} IGL2DResourceVtbl;

interface IGL2DResource
{
	const struct IGL2DResourceVtbl *lpVtbl;
};


#define IGL2DResource_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DResource_AddRef(This) \
	((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define IGL2DResource_Release(This) \
	((This)->lpVtbl->Base.Release((IUnknown *)This))

#define IGL2DResource_GetFactory(This, factory) \
	((This)->lpVtbl->GetFactory(This, factory))

typedef interface IGL2DImage IGL2DImage;

typedef struct IGL2DImageVtbl
{
    
	IGL2DResourceVtbl Base;
    
} IGL2DImageVtbl;

interface IGL2DImage
{
	const struct IGL2DImageVtbl *lpVtbl;
};


#define IGL2DImage_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DImage_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DImage_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DImage_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

typedef interface IGL2DBitmap IGL2DBitmap;

typedef struct IGL2DBitmapVtbl
{
    
	IGL2DImageVtbl Base;
    
    
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		IGL2DBitmap *This 
		) PURE;
    
	STDMETHOD_(GL2D_SIZE_U, GetPixelSize)(
		IGL2DBitmap *This 
		) PURE;
    
	STDMETHOD_(GL2D_PIXEL_FORMAT, GetPixelFormat)(
		IGL2DBitmap *This 
		) PURE;
    
	STDMETHOD_(void, GetDpi)(
		IGL2DBitmap *This,
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) PURE;
    
	STDMETHOD(CopyFromBitmap)(
		IGL2DBitmap *This,
		_In_opt_ const GL2D_POINT_2U *destPoint,
		_In_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_RECT_U *srcRect 
		) PURE;
    
	STDMETHOD(CopyFromRenderTarget)(
		IGL2DBitmap *This,
		_In_opt_ const GL2D_POINT_2U *destPoint,
		_In_ IGL2DRenderTarget *renderTarget,
		_In_opt_ const GL2D_RECT_U *srcRect 
		) PURE;
    
	STDMETHOD(CopyFromMemory)(
		IGL2DBitmap *This,
		_In_opt_ const GL2D_RECT_U *dstRect,
		_In_ const void *srcData,
		uint32_t pitch 
		) PURE;
} IGL2DBitmapVtbl;

interface IGL2DBitmap
{
	const struct IGL2DBitmapVtbl *lpVtbl;
};


#define IGL2DBitmap_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DBitmap_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DBitmap_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DBitmap_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DBitmap_GetSize(This) \
	((This)->lpVtbl->GetSize(This))

#define IGL2DBitmap_GetPixelSize(This) \
	((This)->lpVtbl->GetPixelSize(This))

#define IGL2DBitmap_GetPixelFormat(This) \
	((This)->lpVtbl->GetPixelFormat(This))

#define IGL2DBitmap_GetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->GetDpi(This, dpiX, dpiY))

#define IGL2DBitmap_CopyFromBitmap(This, destPoint, bitmap, srcRect) \
	((This)->lpVtbl->CopyFromBitmap(This, destPoint, bitmap, srcRect))

#define IGL2DBitmap_CopyFromRenderTarget(This, destPoint, renderTarget, srcRect) \
	((This)->lpVtbl->CopyFromRenderTarget(This, destPoint, renderTarget, srcRect))

#define IGL2DBitmap_CopyFromMemory(This, dstRect, srcData, pitch) \
	((This)->lpVtbl->CopyFromMemory(This, dstRect, srcData, pitch))

typedef interface IGL2DGradientStopCollection IGL2DGradientStopCollection;

typedef struct IGL2DGradientStopCollectionVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD_(uint32_t, GetGradientStopCount)(
		IGL2DGradientStopCollection *This 
		) PURE;
    
	STDMETHOD_(void, GetGradientStops)(
		IGL2DGradientStopCollection *This,
		_Out_writes_to_(gradientStopsCount, _Inexpressible_("Retrieved through GetGradientStopCount()") ) GL2D_GRADIENT_STOP *gradientStops,
		uint32_t gradientStopsCount 
		) PURE;
    
	STDMETHOD_(GL2D_GAMMA, GetColorInterpolationGamma)(
		IGL2DGradientStopCollection *This 
		) PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendMode)(
		IGL2DGradientStopCollection *This 
		) PURE;
} IGL2DGradientStopCollectionVtbl;

interface IGL2DGradientStopCollection
{
	const struct IGL2DGradientStopCollectionVtbl *lpVtbl;
};


#define IGL2DGradientStopCollection_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DGradientStopCollection_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DGradientStopCollection_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DGradientStopCollection_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DGradientStopCollection_GetGradientStopCount(This) \
	((This)->lpVtbl->GetGradientStopCount(This))

#define IGL2DGradientStopCollection_GetGradientStops(This, gradientStops, gradientStopsCount) \
	((This)->lpVtbl->GetGradientStops(This, gradientStops, gradientStopsCount))

#define IGL2DGradientStopCollection_GetColorInterpolationGamma(This) \
	((This)->lpVtbl->GetColorInterpolationGamma(This))

#define IGL2DGradientStopCollection_GetExtendMode(This) \
	((This)->lpVtbl->GetExtendMode(This))

typedef interface IGL2DBrush IGL2DBrush;

typedef struct IGL2DBrushVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD_(void, SetOpacity)(
		IGL2DBrush *This,
		float opacity 
		) PURE;
    
	STDMETHOD_(void, SetTransform)(
		IGL2DBrush *This,
		_In_ const GL2D_MATRIX_3X2_F *transform 
		) PURE;
    
	STDMETHOD_(float, GetOpacity)(
		IGL2DBrush *This 
		) PURE;
    
	STDMETHOD_(void, GetTransform)(
		IGL2DBrush *This,
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) PURE;
} IGL2DBrushVtbl;

interface IGL2DBrush
{
	const struct IGL2DBrushVtbl *lpVtbl;
};


#define IGL2DBrush_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DBrush_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DBrush_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DBrush_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DBrush_SetOpacity(This, opacity) \
	((This)->lpVtbl->SetOpacity(This, opacity))

#define IGL2DBrush_SetTransform(This, transform) \
	((This)->lpVtbl->SetTransform(This, transform))

#define IGL2DBrush_GetOpacity(This) \
	((This)->lpVtbl->GetOpacity(This))

#define IGL2DBrush_GetTransform(This, transform) \
	((This)->lpVtbl->GetTransform(This, transform))

typedef interface IGL2DBitmapBrush IGL2DBitmapBrush;

typedef struct IGL2DBitmapBrushVtbl
{
    
	IGL2DBrushVtbl Base;
    
    
	STDMETHOD_(void, SetExtendModeX)(
		IGL2DBitmapBrush *This,
		GL2D_EXTEND_MODE extendModeX 
		) PURE;
    
	STDMETHOD_(void, SetExtendModeY)(
		IGL2DBitmapBrush *This,
		GL2D_EXTEND_MODE extendModeY 
		) PURE;
    
	STDMETHOD_(void, SetInterpolationMode)(
		IGL2DBitmapBrush *This,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode 
		) PURE;
    
	STDMETHOD_(void, SetBitmap)(
		IGL2DBitmapBrush *This,
		_In_opt_ IGL2DBitmap *bitmap 
		) PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendModeX)(
		IGL2DBitmapBrush *This 
		) PURE;
    
	STDMETHOD_(GL2D_EXTEND_MODE, GetExtendModeY)(
		IGL2DBitmapBrush *This 
		) PURE;
    
	STDMETHOD_(GL2D_BITMAP_INTERPOLATION_MODE, GetInterpolationMode)(
		IGL2DBitmapBrush *This 
		) PURE;
    
	STDMETHOD_(void, GetBitmap)(
		IGL2DBitmapBrush *This,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
} IGL2DBitmapBrushVtbl;

interface IGL2DBitmapBrush
{
	const struct IGL2DBitmapBrushVtbl *lpVtbl;
};


#define IGL2DBitmapBrush_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DBitmapBrush_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DBitmapBrush_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DBitmapBrush_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DBitmapBrush_SetOpacity(This, opacity) \
	((This)->lpVtbl->Base.SetOpacity((IGL2DBrush *)This, opacity))

#define IGL2DBitmapBrush_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DBrush *)This, transform))

#define IGL2DBitmapBrush_GetOpacity(This) \
	((This)->lpVtbl->Base.GetOpacity((IGL2DBrush *)This))

#define IGL2DBitmapBrush_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DBrush *)This, transform))

#define IGL2DBitmapBrush_SetExtendModeX(This, extendModeX) \
	((This)->lpVtbl->SetExtendModeX(This, extendModeX))

#define IGL2DBitmapBrush_SetExtendModeY(This, extendModeY) \
	((This)->lpVtbl->SetExtendModeY(This, extendModeY))

#define IGL2DBitmapBrush_SetInterpolationMode(This, interpolationMode) \
	((This)->lpVtbl->SetInterpolationMode(This, interpolationMode))

#define IGL2DBitmapBrush_SetBitmap(This, bitmap) \
	((This)->lpVtbl->SetBitmap(This, bitmap))

#define IGL2DBitmapBrush_GetExtendModeX(This) \
	((This)->lpVtbl->GetExtendModeX(This))

#define IGL2DBitmapBrush_GetExtendModeY(This) \
	((This)->lpVtbl->GetExtendModeY(This))

#define IGL2DBitmapBrush_GetInterpolationMode(This) \
	((This)->lpVtbl->GetInterpolationMode(This))

#define IGL2DBitmapBrush_GetBitmap(This, bitmap) \
	((This)->lpVtbl->GetBitmap(This, bitmap))

typedef interface IGL2DSolidColorBrush IGL2DSolidColorBrush;

typedef struct IGL2DSolidColorBrushVtbl
{
    
	IGL2DBrushVtbl Base;
    
    
	STDMETHOD_(void, SetColor)(
		IGL2DSolidColorBrush *This,
		_In_ const GL2D_COLOR_F *color 
		) PURE;
    
	STDMETHOD_(GL2D_COLOR_F, GetColor)(
		IGL2DSolidColorBrush *This 
		) PURE;
} IGL2DSolidColorBrushVtbl;

interface IGL2DSolidColorBrush
{
	const struct IGL2DSolidColorBrushVtbl *lpVtbl;
};


#define IGL2DSolidColorBrush_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DSolidColorBrush_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DSolidColorBrush_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DSolidColorBrush_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DSolidColorBrush_SetOpacity(This, opacity) \
	((This)->lpVtbl->Base.SetOpacity((IGL2DBrush *)This, opacity))

#define IGL2DSolidColorBrush_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DBrush *)This, transform))

#define IGL2DSolidColorBrush_GetOpacity(This) \
	((This)->lpVtbl->Base.GetOpacity((IGL2DBrush *)This))

#define IGL2DSolidColorBrush_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DBrush *)This, transform))

#define IGL2DSolidColorBrush_SetColor(This, color) \
	((This)->lpVtbl->SetColor(This, color))

#define IGL2DSolidColorBrush_GetColor(This) \
	((This)->lpVtbl->GetColor(This))

typedef interface IGL2DLinearGradientBrush IGL2DLinearGradientBrush;

typedef struct IGL2DLinearGradientBrushVtbl
{
    
	IGL2DBrushVtbl Base;
    
    
	STDMETHOD_(void, SetStartPoint)(
		IGL2DLinearGradientBrush *This,
		GL2D_POINT_2F startPoint 
		) PURE;
    
	STDMETHOD_(void, SetEndPoint)(
		IGL2DLinearGradientBrush *This,
		GL2D_POINT_2F endPoint 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetStartPoint)(
		IGL2DLinearGradientBrush *This 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetEndPoint)(
		IGL2DLinearGradientBrush *This 
		) PURE;
    
	STDMETHOD_(void, GetGradientStopCollection)(
		IGL2DLinearGradientBrush *This,
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) PURE;
} IGL2DLinearGradientBrushVtbl;

interface IGL2DLinearGradientBrush
{
	const struct IGL2DLinearGradientBrushVtbl *lpVtbl;
};


#define IGL2DLinearGradientBrush_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DLinearGradientBrush_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DLinearGradientBrush_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DLinearGradientBrush_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DLinearGradientBrush_SetOpacity(This, opacity) \
	((This)->lpVtbl->Base.SetOpacity((IGL2DBrush *)This, opacity))

#define IGL2DLinearGradientBrush_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DBrush *)This, transform))

#define IGL2DLinearGradientBrush_GetOpacity(This) \
	((This)->lpVtbl->Base.GetOpacity((IGL2DBrush *)This))

#define IGL2DLinearGradientBrush_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DBrush *)This, transform))

#define IGL2DLinearGradientBrush_SetStartPoint(This, startPoint) \
	((This)->lpVtbl->SetStartPoint(This, startPoint))

#define IGL2DLinearGradientBrush_SetEndPoint(This, endPoint) \
	((This)->lpVtbl->SetEndPoint(This, endPoint))

#define IGL2DLinearGradientBrush_GetStartPoint(This) \
	((This)->lpVtbl->GetStartPoint(This))

#define IGL2DLinearGradientBrush_GetEndPoint(This) \
	((This)->lpVtbl->GetEndPoint(This))

#define IGL2DLinearGradientBrush_GetGradientStopCollection(This, gradientStopCollection) \
	((This)->lpVtbl->GetGradientStopCollection(This, gradientStopCollection))

typedef interface IGL2DRadialGradientBrush IGL2DRadialGradientBrush;

typedef struct IGL2DRadialGradientBrushVtbl
{
    
	IGL2DBrushVtbl Base;
    
    
	STDMETHOD_(void, SetCenter)(
		IGL2DRadialGradientBrush *This,
		GL2D_POINT_2F center 
		) PURE;
    
	STDMETHOD_(void, SetGradientOriginOffset)(
		IGL2DRadialGradientBrush *This,
		GL2D_POINT_2F gradientOriginOffset 
		) PURE;
    
	STDMETHOD_(void, SetRadiusX)(
		IGL2DRadialGradientBrush *This,
		float radiusX 
		) PURE;
    
	STDMETHOD_(void, SetRadiusY)(
		IGL2DRadialGradientBrush *This,
		float radiusY 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetCenter)(
		IGL2DRadialGradientBrush *This 
		) PURE;
    
	STDMETHOD_(GL2D_POINT_2F, GetGradientOriginOffset)(
		IGL2DRadialGradientBrush *This 
		) PURE;
    
	STDMETHOD_(float, GetRadiusX)(
		IGL2DRadialGradientBrush *This 
		) PURE;
    
	STDMETHOD_(float, GetRadiusY)(
		IGL2DRadialGradientBrush *This 
		) PURE;
    
	STDMETHOD_(void, GetGradientStopCollection)(
		IGL2DRadialGradientBrush *This,
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) PURE;
} IGL2DRadialGradientBrushVtbl;

interface IGL2DRadialGradientBrush
{
	const struct IGL2DRadialGradientBrushVtbl *lpVtbl;
};


#define IGL2DRadialGradientBrush_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DRadialGradientBrush_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DRadialGradientBrush_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DRadialGradientBrush_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DRadialGradientBrush_SetOpacity(This, opacity) \
	((This)->lpVtbl->Base.SetOpacity((IGL2DBrush *)This, opacity))

#define IGL2DRadialGradientBrush_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DBrush *)This, transform))

#define IGL2DRadialGradientBrush_GetOpacity(This) \
	((This)->lpVtbl->Base.GetOpacity((IGL2DBrush *)This))

#define IGL2DRadialGradientBrush_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DBrush *)This, transform))

#define IGL2DRadialGradientBrush_SetCenter(This, center) \
	((This)->lpVtbl->SetCenter(This, center))

#define IGL2DRadialGradientBrush_SetGradientOriginOffset(This, gradientOriginOffset) \
	((This)->lpVtbl->SetGradientOriginOffset(This, gradientOriginOffset))

#define IGL2DRadialGradientBrush_SetRadiusX(This, radiusX) \
	((This)->lpVtbl->SetRadiusX(This, radiusX))

#define IGL2DRadialGradientBrush_SetRadiusY(This, radiusY) \
	((This)->lpVtbl->SetRadiusY(This, radiusY))

#define IGL2DRadialGradientBrush_GetCenter(This) \
	((This)->lpVtbl->GetCenter(This))

#define IGL2DRadialGradientBrush_GetGradientOriginOffset(This) \
	((This)->lpVtbl->GetGradientOriginOffset(This))

#define IGL2DRadialGradientBrush_GetRadiusX(This) \
	((This)->lpVtbl->GetRadiusX(This))

#define IGL2DRadialGradientBrush_GetRadiusY(This) \
	((This)->lpVtbl->GetRadiusY(This))

#define IGL2DRadialGradientBrush_GetGradientStopCollection(This, gradientStopCollection) \
	((This)->lpVtbl->GetGradientStopCollection(This, gradientStopCollection))

typedef interface IGL2DStrokeStyle IGL2DStrokeStyle;

typedef struct IGL2DStrokeStyleVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD_(GL2D_CAP_STYLE, GetStartCap)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(GL2D_CAP_STYLE, GetEndCap)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(GL2D_CAP_STYLE, GetDashCap)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(float, GetMiterLimit)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(GL2D_LINE_JOIN, GetLineJoin)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(float, GetDashOffset)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(GL2D_DASH_STYLE, GetDashStyle)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(uint32_t, GetDashesCount)(
		IGL2DStrokeStyle *This 
		) PURE;
    
	STDMETHOD_(void, GetDashes)(
		IGL2DStrokeStyle *This,
		_Out_writes_(dashesCount) float *dashes,
		uint32_t dashesCount 
		) PURE;
} IGL2DStrokeStyleVtbl;

interface IGL2DStrokeStyle
{
	const struct IGL2DStrokeStyleVtbl *lpVtbl;
};


#define IGL2DStrokeStyle_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DStrokeStyle_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DStrokeStyle_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DStrokeStyle_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DStrokeStyle_GetStartCap(This) \
	((This)->lpVtbl->GetStartCap(This))

#define IGL2DStrokeStyle_GetEndCap(This) \
	((This)->lpVtbl->GetEndCap(This))

#define IGL2DStrokeStyle_GetDashCap(This) \
	((This)->lpVtbl->GetDashCap(This))

#define IGL2DStrokeStyle_GetMiterLimit(This) \
	((This)->lpVtbl->GetMiterLimit(This))

#define IGL2DStrokeStyle_GetLineJoin(This) \
	((This)->lpVtbl->GetLineJoin(This))

#define IGL2DStrokeStyle_GetDashOffset(This) \
	((This)->lpVtbl->GetDashOffset(This))

#define IGL2DStrokeStyle_GetDashStyle(This) \
	((This)->lpVtbl->GetDashStyle(This))

#define IGL2DStrokeStyle_GetDashesCount(This) \
	((This)->lpVtbl->GetDashesCount(This))

#define IGL2DStrokeStyle_GetDashes(This, dashes, dashesCount) \
	((This)->lpVtbl->GetDashes(This, dashes, dashesCount))

typedef interface IGL2DGeometry IGL2DGeometry;

typedef struct IGL2DGeometryVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD(GetBounds)(
		IGL2DGeometry *This,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		_Out_ GL2D_RECT_F *bounds 
		) PURE;
    
	STDMETHOD(GetWidenedBounds)(
		IGL2DGeometry *This,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ GL2D_RECT_F *bounds 
		) PURE;
    
	STDMETHOD(StrokeContainsPoint)(
		IGL2DGeometry *This,
		GL2D_POINT_2F point,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) PURE;
    
	STDMETHOD(FillContainsPoint)(
		IGL2DGeometry *This,
		GL2D_POINT_2F point,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ bool *contains 
		) PURE;
    
	STDMETHOD(CompareWithGeometry)(
		IGL2DGeometry *This,
		_In_ IGL2DGeometry *inputGeometry,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		float flatteningTolerance,
		_Out_ GL2D_GEOMETRY_RELATION *relation 
		) PURE;
    
	STDMETHOD(Simplify)(
		IGL2DGeometry *This,
		GL2D_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) PURE;
    
	STDMETHOD(Tessellate)(
		IGL2DGeometry *This,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DTessellationSink *tessellationSink 
		) PURE;
    
	STDMETHOD(CombineWithGeometry)(
		IGL2DGeometry *This,
		_In_ IGL2DGeometry *inputGeometry,
		GL2D_COMBINE_MODE combineMode,
		_In_opt_ const GL2D_MATRIX_3X2_F *inputGeometryTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) PURE;
    
	STDMETHOD(Outline)(
		IGL2DGeometry *This,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) PURE;
    
	STDMETHOD(ComputeArea)(
		IGL2DGeometry *This,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ float *area 
		) PURE;
    
	STDMETHOD(ComputeLength)(
		IGL2DGeometry *This,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_ float *length 
		) PURE;
    
	STDMETHOD(ComputePointAtLength)(
		IGL2DGeometry *This,
		float length,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_Out_opt_ GL2D_POINT_2F *point,
		_Out_opt_ GL2D_POINT_2F *unitTangentVector 
		) PURE;
    
	STDMETHOD(Widen)(
		IGL2DGeometry *This,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle,
		_In_opt_ const GL2D_MATRIX_3X2_F *worldTransform,
		float flatteningTolerance,
		_In_ IGL2DSimplifiedGeometrySink *geometrySink 
		) PURE;
} IGL2DGeometryVtbl;

interface IGL2DGeometry
{
	const struct IGL2DGeometryVtbl *lpVtbl;
};


#define IGL2DGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->GetBounds(This, worldTransform, bounds))

#define IGL2DGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Tessellate(This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Outline(This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->ComputeArea(This, worldTransform, flatteningTolerance, area))

#define IGL2DGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->ComputeLength(This, worldTransform, flatteningTolerance, length))

#define IGL2DGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

typedef interface IGL2DRectangleGeometry IGL2DRectangleGeometry;

typedef struct IGL2DRectangleGeometryVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD_(void, GetRect)(
		IGL2DRectangleGeometry *This,
		_Out_ GL2D_RECT_F *rect 
		) PURE;
} IGL2DRectangleGeometryVtbl;

interface IGL2DRectangleGeometry
{
	const struct IGL2DRectangleGeometryVtbl *lpVtbl;
};


#define IGL2DRectangleGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DRectangleGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DRectangleGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DRectangleGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DRectangleGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DRectangleGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DRectangleGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DRectangleGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DRectangleGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DRectangleGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRectangleGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DRectangleGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DRectangleGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRectangleGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DRectangleGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DRectangleGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DRectangleGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRectangleGeometry_GetRect(This, rect) \
	((This)->lpVtbl->GetRect(This, rect))

typedef interface IGL2DRoundedRectangleGeometry IGL2DRoundedRectangleGeometry;

typedef struct IGL2DRoundedRectangleGeometryVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD_(void, GetRoundedRect)(
		IGL2DRoundedRectangleGeometry *This,
		_Out_ GL2D_ROUNDED_RECT *roundedRect 
		) PURE;
} IGL2DRoundedRectangleGeometryVtbl;

interface IGL2DRoundedRectangleGeometry
{
	const struct IGL2DRoundedRectangleGeometryVtbl *lpVtbl;
};


#define IGL2DRoundedRectangleGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DRoundedRectangleGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DRoundedRectangleGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DRoundedRectangleGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DRoundedRectangleGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DRoundedRectangleGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DRoundedRectangleGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DRoundedRectangleGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DRoundedRectangleGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DRoundedRectangleGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRoundedRectangleGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DRoundedRectangleGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DRoundedRectangleGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRoundedRectangleGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DRoundedRectangleGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DRoundedRectangleGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DRoundedRectangleGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DRoundedRectangleGeometry_GetRoundedRect(This, roundedRect) \
	((This)->lpVtbl->GetRoundedRect(This, roundedRect))

typedef interface IGL2DEllipseGeometry IGL2DEllipseGeometry;

typedef struct IGL2DEllipseGeometryVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD_(void, GetEllipse)(
		IGL2DEllipseGeometry *This,
		_Out_ GL2D_ELLIPSE *ellipse 
		) PURE;
} IGL2DEllipseGeometryVtbl;

interface IGL2DEllipseGeometry
{
	const struct IGL2DEllipseGeometryVtbl *lpVtbl;
};


#define IGL2DEllipseGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DEllipseGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DEllipseGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DEllipseGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DEllipseGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DEllipseGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DEllipseGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DEllipseGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DEllipseGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DEllipseGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DEllipseGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DEllipseGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DEllipseGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DEllipseGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DEllipseGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DEllipseGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DEllipseGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DEllipseGeometry_GetEllipse(This, ellipse) \
	((This)->lpVtbl->GetEllipse(This, ellipse))

typedef interface IGL2DGeometryGroup IGL2DGeometryGroup;

typedef struct IGL2DGeometryGroupVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD_(GL2D_FILL_MODE, GetFillMode)(
		IGL2DGeometryGroup *This 
		) PURE;
    
	STDMETHOD_(uint32_t, GetSourceGeometryCount)(
		IGL2DGeometryGroup *This 
		) PURE;
    
	STDMETHOD_(void, GetSourceGeometries)(
		IGL2DGeometryGroup *This,
		_Out_writes_(geometriesCount) IGL2DGeometry **geometries,
		uint32_t geometriesCount 
		) PURE;
} IGL2DGeometryGroupVtbl;

interface IGL2DGeometryGroup
{
	const struct IGL2DGeometryGroupVtbl *lpVtbl;
};


#define IGL2DGeometryGroup_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DGeometryGroup_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DGeometryGroup_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DGeometryGroup_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DGeometryGroup_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DGeometryGroup_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DGeometryGroup_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DGeometryGroup_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DGeometryGroup_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DGeometryGroup_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometryGroup_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DGeometryGroup_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometryGroup_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometryGroup_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DGeometryGroup_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DGeometryGroup_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DGeometryGroup_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DGeometryGroup_GetFillMode(This) \
	((This)->lpVtbl->GetFillMode(This))

#define IGL2DGeometryGroup_GetSourceGeometryCount(This) \
	((This)->lpVtbl->GetSourceGeometryCount(This))

#define IGL2DGeometryGroup_GetSourceGeometries(This, geometries, geometriesCount) \
	((This)->lpVtbl->GetSourceGeometries(This, geometries, geometriesCount))

typedef interface IGL2DTransformedGeometry IGL2DTransformedGeometry;

typedef struct IGL2DTransformedGeometryVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD_(void, GetSourceGeometry)(
		IGL2DTransformedGeometry *This,
		_Outptr_ IGL2DGeometry **sourceGeometry 
		) PURE;
    
	STDMETHOD_(void, GetTransform)(
		IGL2DTransformedGeometry *This,
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) PURE;
} IGL2DTransformedGeometryVtbl;

interface IGL2DTransformedGeometry
{
	const struct IGL2DTransformedGeometryVtbl *lpVtbl;
};


#define IGL2DTransformedGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DTransformedGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DTransformedGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DTransformedGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DTransformedGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DTransformedGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DTransformedGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DTransformedGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DTransformedGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DTransformedGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DTransformedGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DTransformedGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DTransformedGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DTransformedGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DTransformedGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DTransformedGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DTransformedGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DTransformedGeometry_GetSourceGeometry(This, sourceGeometry) \
	((This)->lpVtbl->GetSourceGeometry(This, sourceGeometry))

#define IGL2DTransformedGeometry_GetTransform(This, transform) \
	((This)->lpVtbl->GetTransform(This, transform))

typedef interface IGL2DSimplifiedGeometrySink IGL2DSimplifiedGeometrySink;

typedef struct IGL2DSimplifiedGeometrySinkVtbl
{
    
	IUnknownVtbl Base;
    
    
	STDMETHOD_(void, SetFillMode)(
		IGL2DSimplifiedGeometrySink *This,
		GL2D_FILL_MODE fillMode 
		) PURE;
    
	STDMETHOD_(void, SetSegmentFlags)(
		IGL2DSimplifiedGeometrySink *This,
		GL2D_PATH_SEGMENT vertexFlags 
		) PURE;
    
	STDMETHOD_(void, BeginFigure)(
		IGL2DSimplifiedGeometrySink *This,
		GL2D_POINT_2F startPoint,
		GL2D_FIGURE_BEGIN figureBegin 
		) PURE;
    
	STDMETHOD_(void, AddLines)(
		IGL2DSimplifiedGeometrySink *This,
		_In_reads_(pointsCount) const GL2D_POINT_2F *points,
		uint32_t pointsCount 
		) PURE;
    
	STDMETHOD_(void, AddBeziers)(
		IGL2DSimplifiedGeometrySink *This,
		_In_reads_(beziersCount) const GL2D_BEZIER_SEGMENT *beziers,
		uint32_t beziersCount 
		) PURE;
    
	STDMETHOD_(void, EndFigure)(
		IGL2DSimplifiedGeometrySink *This,
		GL2D_FIGURE_END figureEnd 
		) PURE;
    
	STDMETHOD(Close)(
		IGL2DSimplifiedGeometrySink *This 
		) PURE;
} IGL2DSimplifiedGeometrySinkVtbl;

interface IGL2DSimplifiedGeometrySink
{
	const struct IGL2DSimplifiedGeometrySinkVtbl *lpVtbl;
};


#define IGL2DSimplifiedGeometrySink_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DSimplifiedGeometrySink_AddRef(This) \
	((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define IGL2DSimplifiedGeometrySink_Release(This) \
	((This)->lpVtbl->Base.Release((IUnknown *)This))

#define IGL2DSimplifiedGeometrySink_SetFillMode(This, fillMode) \
	((This)->lpVtbl->SetFillMode(This, fillMode))

#define IGL2DSimplifiedGeometrySink_SetSegmentFlags(This, vertexFlags) \
	((This)->lpVtbl->SetSegmentFlags(This, vertexFlags))

#define IGL2DSimplifiedGeometrySink_BeginFigure(This, startPoint, figureBegin) \
	((This)->lpVtbl->BeginFigure(This, startPoint, figureBegin))

#define IGL2DSimplifiedGeometrySink_AddLines(This, points, pointsCount) \
	((This)->lpVtbl->AddLines(This, points, pointsCount))

#define IGL2DSimplifiedGeometrySink_AddBeziers(This, beziers, beziersCount) \
	((This)->lpVtbl->AddBeziers(This, beziers, beziersCount))

#define IGL2DSimplifiedGeometrySink_EndFigure(This, figureEnd) \
	((This)->lpVtbl->EndFigure(This, figureEnd))

#define IGL2DSimplifiedGeometrySink_Close(This) \
	((This)->lpVtbl->Close(This))

typedef interface IGL2DGeometrySink IGL2DGeometrySink;

typedef struct IGL2DGeometrySinkVtbl
{
    
	IGL2DSimplifiedGeometrySinkVtbl Base;
    
    
	STDMETHOD_(void, AddLine)(
		IGL2DGeometrySink *This,
		GL2D_POINT_2F point 
		) PURE;
    
	STDMETHOD_(void, AddBezier)(
		IGL2DGeometrySink *This,
		_In_ const GL2D_BEZIER_SEGMENT *bezier 
		) PURE;
    
	STDMETHOD_(void, AddQuadraticBezier)(
		IGL2DGeometrySink *This,
		_In_ const GL2D_QUADRATIC_BEZIER_SEGMENT *bezier 
		) PURE;
    
	STDMETHOD_(void, AddQuadraticBeziers)(
		IGL2DGeometrySink *This,
		_In_reads_(beziersCount) const GL2D_QUADRATIC_BEZIER_SEGMENT *beziers,
		uint32_t beziersCount 
		) PURE;
    
	STDMETHOD_(void, AddArc)(
		IGL2DGeometrySink *This,
		_In_ const GL2D_ARC_SEGMENT *arc 
		) PURE;
} IGL2DGeometrySinkVtbl;

interface IGL2DGeometrySink
{
	const struct IGL2DGeometrySinkVtbl *lpVtbl;
};


#define IGL2DGeometrySink_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DGeometrySink_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DGeometrySink_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DGeometrySink_SetFillMode(This, fillMode) \
	((This)->lpVtbl->Base.SetFillMode((IGL2DSimplifiedGeometrySink *)This, fillMode))

#define IGL2DGeometrySink_SetSegmentFlags(This, vertexFlags) \
	((This)->lpVtbl->Base.SetSegmentFlags((IGL2DSimplifiedGeometrySink *)This, vertexFlags))

#define IGL2DGeometrySink_BeginFigure(This, startPoint, figureBegin) \
	((This)->lpVtbl->Base.BeginFigure((IGL2DSimplifiedGeometrySink *)This, startPoint, figureBegin))

#define IGL2DGeometrySink_AddLines(This, points, pointsCount) \
	((This)->lpVtbl->Base.AddLines((IGL2DSimplifiedGeometrySink *)This, points, pointsCount))

#define IGL2DGeometrySink_AddBeziers(This, beziers, beziersCount) \
	((This)->lpVtbl->Base.AddBeziers((IGL2DSimplifiedGeometrySink *)This, beziers, beziersCount))

#define IGL2DGeometrySink_EndFigure(This, figureEnd) \
	((This)->lpVtbl->Base.EndFigure((IGL2DSimplifiedGeometrySink *)This, figureEnd))

#define IGL2DGeometrySink_Close(This) \
	((This)->lpVtbl->Base.Close((IGL2DSimplifiedGeometrySink *)This))

#define IGL2DGeometrySink_AddLine(This, point) \
	((This)->lpVtbl->AddLine(This, point))

#define IGL2DGeometrySink_AddBezier(This, bezier) \
	((This)->lpVtbl->AddBezier(This, bezier))

#define IGL2DGeometrySink_AddQuadraticBezier(This, bezier) \
	((This)->lpVtbl->AddQuadraticBezier(This, bezier))

#define IGL2DGeometrySink_AddQuadraticBeziers(This, beziers, beziersCount) \
	((This)->lpVtbl->AddQuadraticBeziers(This, beziers, beziersCount))

#define IGL2DGeometrySink_AddArc(This, arc) \
	((This)->lpVtbl->AddArc(This, arc))

typedef interface IGL2DTessellationSink IGL2DTessellationSink;

typedef struct IGL2DTessellationSinkVtbl
{
    
	IUnknownVtbl Base;
    
    
	STDMETHOD_(void, AddTriangles)(
		IGL2DTessellationSink *This,
		_In_reads_(trianglesCount) const GL2D_TRIANGLE *triangles,
		uint32_t trianglesCount 
		) PURE;
    
	STDMETHOD(Close)(
		IGL2DTessellationSink *This 
		) PURE;
} IGL2DTessellationSinkVtbl;

interface IGL2DTessellationSink
{
	const struct IGL2DTessellationSinkVtbl *lpVtbl;
};


#define IGL2DTessellationSink_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DTessellationSink_AddRef(This) \
	((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define IGL2DTessellationSink_Release(This) \
	((This)->lpVtbl->Base.Release((IUnknown *)This))

#define IGL2DTessellationSink_AddTriangles(This, triangles, trianglesCount) \
	((This)->lpVtbl->AddTriangles(This, triangles, trianglesCount))

#define IGL2DTessellationSink_Close(This) \
	((This)->lpVtbl->Close(This))

typedef interface IGL2DPathGeometry IGL2DPathGeometry;

typedef struct IGL2DPathGeometryVtbl
{
    
	IGL2DGeometryVtbl Base;
    
    
	STDMETHOD(Open)(
		IGL2DPathGeometry *This,
		_Outptr_ IGL2DGeometrySink **geometrySink 
		) PURE;
    
	STDMETHOD(Stream)(
		IGL2DPathGeometry *This,
		_In_ IGL2DGeometrySink *geometrySink 
		) PURE;
    
	STDMETHOD(GetSegmentCount)(
		IGL2DPathGeometry *This,
		_Out_ uint32_t *count 
		) PURE;
    
	STDMETHOD(GetFigureCount)(
		IGL2DPathGeometry *This,
		_Out_ uint32_t *count 
		) PURE;
} IGL2DPathGeometryVtbl;

interface IGL2DPathGeometry
{
	const struct IGL2DPathGeometryVtbl *lpVtbl;
};


#define IGL2DPathGeometry_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DPathGeometry_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DPathGeometry_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DPathGeometry_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DPathGeometry_GetBounds(This, worldTransform, bounds) \
	((This)->lpVtbl->Base.GetBounds((IGL2DGeometry *)This, worldTransform, bounds))

#define IGL2DPathGeometry_GetWidenedBounds(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds) \
	((This)->lpVtbl->Base.GetWidenedBounds((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds))

#define IGL2DPathGeometry_StrokeContainsPoint(This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.StrokeContainsPoint((IGL2DGeometry *)This, point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains))

#define IGL2DPathGeometry_FillContainsPoint(This, point, worldTransform, flatteningTolerance, contains) \
	((This)->lpVtbl->Base.FillContainsPoint((IGL2DGeometry *)This, point, worldTransform, flatteningTolerance, contains))

#define IGL2DPathGeometry_CompareWithGeometry(This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation) \
	((This)->lpVtbl->Base.CompareWithGeometry((IGL2DGeometry *)This, inputGeometry, inputGeometryTransform, flatteningTolerance, relation))

#define IGL2DPathGeometry_Simplify(This, simplificationOption, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Simplify((IGL2DGeometry *)This, simplificationOption, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DPathGeometry_Tessellate(This, worldTransform, flatteningTolerance, tessellationSink) \
	((This)->lpVtbl->Base.Tessellate((IGL2DGeometry *)This, worldTransform, flatteningTolerance, tessellationSink))

#define IGL2DPathGeometry_CombineWithGeometry(This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.CombineWithGeometry((IGL2DGeometry *)This, inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink))

#define IGL2DPathGeometry_Outline(This, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Outline((IGL2DGeometry *)This, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DPathGeometry_ComputeArea(This, worldTransform, flatteningTolerance, area) \
	((This)->lpVtbl->Base.ComputeArea((IGL2DGeometry *)This, worldTransform, flatteningTolerance, area))

#define IGL2DPathGeometry_ComputeLength(This, worldTransform, flatteningTolerance, length) \
	((This)->lpVtbl->Base.ComputeLength((IGL2DGeometry *)This, worldTransform, flatteningTolerance, length))

#define IGL2DPathGeometry_ComputePointAtLength(This, length, worldTransform, flatteningTolerance, point, unitTangentVector) \
	((This)->lpVtbl->Base.ComputePointAtLength((IGL2DGeometry *)This, length, worldTransform, flatteningTolerance, point, unitTangentVector))

#define IGL2DPathGeometry_Widen(This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink) \
	((This)->lpVtbl->Base.Widen((IGL2DGeometry *)This, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink))

#define IGL2DPathGeometry_Open(This, geometrySink) \
	((This)->lpVtbl->Open(This, geometrySink))

#define IGL2DPathGeometry_Stream(This, geometrySink) \
	((This)->lpVtbl->Stream(This, geometrySink))

#define IGL2DPathGeometry_GetSegmentCount(This, count) \
	((This)->lpVtbl->GetSegmentCount(This, count))

#define IGL2DPathGeometry_GetFigureCount(This, count) \
	((This)->lpVtbl->GetFigureCount(This, count))

typedef interface IGL2DMesh IGL2DMesh;

typedef struct IGL2DMeshVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD(Open)(
		IGL2DMesh *This,
		_Outptr_ IGL2DTessellationSink **tessellationSink 
		) PURE;
} IGL2DMeshVtbl;

interface IGL2DMesh
{
	const struct IGL2DMeshVtbl *lpVtbl;
};


#define IGL2DMesh_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DMesh_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DMesh_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DMesh_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DMesh_Open(This, tessellationSink) \
	((This)->lpVtbl->Open(This, tessellationSink))

typedef interface IGL2DLayer IGL2DLayer;

typedef struct IGL2DLayerVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		IGL2DLayer *This 
		) PURE;
} IGL2DLayerVtbl;

interface IGL2DLayer
{
	const struct IGL2DLayerVtbl *lpVtbl;
};


#define IGL2DLayer_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DLayer_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DLayer_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DLayer_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DLayer_GetSize(This) \
	((This)->lpVtbl->GetSize(This))

typedef interface IGL2DDrawingStateBlock IGL2DDrawingStateBlock;

typedef struct IGL2DDrawingStateBlockVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD_(void, GetDescription)(
		IGL2DDrawingStateBlock *This,
		_Out_ GL2D_DRAWING_STATE_DESCRIPTION *stateDescription 
		) PURE;
    
	STDMETHOD_(void, SetDescription)(
		IGL2DDrawingStateBlock *This,
		_In_ const GL2D_DRAWING_STATE_DESCRIPTION *stateDescription 
		) PURE;
    
	STDMETHOD_(void, SetTextRenderingParams)(
		IGL2DDrawingStateBlock *This,
		_In_opt_ IDWriteRenderingParams *textRenderingParams 
		) PURE;
    
	STDMETHOD_(void, GetTextRenderingParams)(
		IGL2DDrawingStateBlock *This,
		_Outptr_result_maybenull_ IDWriteRenderingParams **textRenderingParams 
		) PURE;
} IGL2DDrawingStateBlockVtbl;

interface IGL2DDrawingStateBlock
{
	const struct IGL2DDrawingStateBlockVtbl *lpVtbl;
};


#define IGL2DDrawingStateBlock_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DDrawingStateBlock_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DDrawingStateBlock_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DDrawingStateBlock_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DDrawingStateBlock_GetDescription(This, stateDescription) \
	((This)->lpVtbl->GetDescription(This, stateDescription))

#define IGL2DDrawingStateBlock_SetDescription(This, stateDescription) \
	((This)->lpVtbl->SetDescription(This, stateDescription))

#define IGL2DDrawingStateBlock_SetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->SetTextRenderingParams(This, textRenderingParams))

#define IGL2DDrawingStateBlock_GetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->GetTextRenderingParams(This, textRenderingParams))

typedef interface IGL2DRenderTarget IGL2DRenderTarget;

typedef struct IGL2DRenderTargetVtbl
{
    
	IGL2DResourceVtbl Base;
    
    
	STDMETHOD(CreateBitmap)(
		IGL2DRenderTarget *This,
		GL2D_SIZE_U size,
		_In_opt_ const void *srcData,
		uint32_t pitch,
		_In_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
	STDMETHOD(CreateBitmapFromWicBitmap)(
		IGL2DRenderTarget *This,
		_In_ IWICBitmapSource *wicBitmapSource,
		_In_opt_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
	STDMETHOD(CreateSharedBitmap)(
		IGL2DRenderTarget *This,
		_In_ REFIID riid,
		_Inout_ void *data,
		_In_opt_ const GL2D_BITMAP_PROPERTIES *bitmapProperties,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
    
	STDMETHOD(CreateBitmapBrush)(
		IGL2DRenderTarget *This,
		_In_opt_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_BITMAP_BRUSH_PROPERTIES *bitmapBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_Outptr_ IGL2DBitmapBrush **bitmapBrush 
		) PURE;
    
	STDMETHOD(CreateSolidColorBrush)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_COLOR_F *color,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_Outptr_ IGL2DSolidColorBrush **solidColorBrush 
		) PURE;
    
	STDMETHOD(CreateGradientStopCollection)(
		IGL2DRenderTarget *This,
		_In_reads_(gradientStopsCount) const GL2D_GRADIENT_STOP *gradientStops,
		_In_range_(>=,1) uint32_t gradientStopsCount,
		GL2D_GAMMA colorInterpolationGamma,
		GL2D_EXTEND_MODE extendMode,
		_Outptr_ IGL2DGradientStopCollection **gradientStopCollection 
		) PURE;
    
	STDMETHOD(CreateLinearGradientBrush)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES *linearGradientBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DLinearGradientBrush **linearGradientBrush 
		) PURE;
    
	STDMETHOD(CreateRadialGradientBrush)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES *radialGradientBrushProperties,
		_In_opt_ const GL2D_BRUSH_PROPERTIES *brushProperties,
		_In_ IGL2DGradientStopCollection *gradientStopCollection,
		_Outptr_ IGL2DRadialGradientBrush **radialGradientBrush 
		) PURE;
    
	STDMETHOD(CreateCompatibleRenderTarget)(
		IGL2DRenderTarget *This,
		_In_opt_ const GL2D_SIZE_F *desiredSize,
		_In_opt_ const GL2D_SIZE_U *desiredPixelSize,
		_In_opt_ const GL2D_PIXEL_FORMAT *desiredFormat,
		GL2D_COMPATIBLE_RENDER_TARGET_OPTIONS options,
		_Outptr_ IGL2DBitmapRenderTarget **bitmapRenderTarget 
		) PURE;
    
	STDMETHOD(CreateLayer)(
		IGL2DRenderTarget *This,
		_In_opt_ const GL2D_SIZE_F *size,
		_Outptr_ IGL2DLayer **layer 
		) PURE;
    
	STDMETHOD(CreateMesh)(
		IGL2DRenderTarget *This,
		_Outptr_ IGL2DMesh **mesh 
		) PURE;
    
	STDMETHOD_(void, DrawLine)(
		IGL2DRenderTarget *This,
		GL2D_POINT_2F point0,
		GL2D_POINT_2F point1,
		_In_ IGL2DBrush *brush,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle 
		) PURE;
    
	STDMETHOD_(void, DrawRectangle)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_RECT_F *rect,
		_In_ IGL2DBrush *brush,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle 
		) PURE;
    
	STDMETHOD_(void, FillRectangle)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_RECT_F *rect,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawRoundedRectangle)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_ROUNDED_RECT *roundedRect,
		_In_ IGL2DBrush *brush,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle 
		) PURE;
    
	STDMETHOD_(void, FillRoundedRectangle)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_ROUNDED_RECT *roundedRect,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawEllipse)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_ELLIPSE *ellipse,
		_In_ IGL2DBrush *brush,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle 
		) PURE;
    
	STDMETHOD_(void, FillEllipse)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_ELLIPSE *ellipse,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, DrawGeometry)(
		IGL2DRenderTarget *This,
		_In_ IGL2DGeometry *geometry,
		_In_ IGL2DBrush *brush,
		float strokeWidth,
		_In_opt_ IGL2DStrokeStyle *strokeStyle 
		) PURE;
    
	STDMETHOD_(void, FillGeometry)(
		IGL2DRenderTarget *This,
		_In_ IGL2DGeometry *geometry,
		_In_ IGL2DBrush *brush,
		_In_opt_ IGL2DBrush *opacityBrush 
		) PURE;
    
	STDMETHOD_(void, FillMesh)(
		IGL2DRenderTarget *This,
		_In_ IGL2DMesh *mesh,
		_In_ IGL2DBrush *brush 
		) PURE;
    
	STDMETHOD_(void, FillOpacityMask)(
		IGL2DRenderTarget *This,
		_In_ IGL2DBitmap *opacityMask,
		_In_ IGL2DBrush *brush,
		GL2D_OPACITY_MASK_CONTENT content,
		_In_opt_ const GL2D_RECT_F *destinationRectangle,
		_In_opt_ const GL2D_RECT_F *sourceRectangle 
		) PURE;
    
	STDMETHOD_(void, DrawBitmap)(
		IGL2DRenderTarget *This,
		_In_ IGL2DBitmap *bitmap,
		_In_opt_ const GL2D_RECT_F *destinationRectangle,
		float opacity,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode,
		_In_opt_ const GL2D_RECT_F *sourceRectangle 
		) PURE;
    
	STDMETHOD_(void, DrawText)(
		IGL2DRenderTarget *This,
		_In_reads_(stringLength) const WCHAR *string,
		uint32_t stringLength,
		_In_ IDWriteTextFormat *textFormat,
		_In_ const GL2D_RECT_F *layoutRect,
		_In_ IGL2DBrush *defaultForegroundBrush,
		GL2D_DRAW_TEXT_OPTIONS options,
		DWRITE_MEASURING_MODE measuringMode 
		) PURE;
    
	STDMETHOD_(void, DrawTextLayout)(
		IGL2DRenderTarget *This,
		GL2D_POINT_2F origin,
		_In_ IDWriteTextLayout *textLayout,
		_In_ IGL2DBrush *defaultForegroundBrush,
		GL2D_DRAW_TEXT_OPTIONS options 
		) PURE;
    
	STDMETHOD_(void, DrawGlyphRun)(
		IGL2DRenderTarget *This,
		GL2D_POINT_2F baselineOrigin,
		_In_ const DWRITE_GLYPH_RUN *glyphRun,
		_In_ IGL2DBrush *foregroundBrush,
		DWRITE_MEASURING_MODE measuringMode 
		) PURE;
    
	STDMETHOD_(void, SetTransform)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_MATRIX_3X2_F *transform 
		) PURE;
    
	STDMETHOD_(void, GetTransform)(
		IGL2DRenderTarget *This,
		_Out_ GL2D_MATRIX_3X2_F *transform 
		) PURE;
    
	STDMETHOD_(void, SetAntialiasMode)(
		IGL2DRenderTarget *This,
		GL2D_ANTIALIAS_MODE antialiasMode 
		) PURE;
    
	STDMETHOD_(GL2D_ANTIALIAS_MODE, GetAntialiasMode)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(void, SetTextAntialiasMode)(
		IGL2DRenderTarget *This,
		GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode 
		) PURE;
    
	STDMETHOD_(GL2D_TEXT_ANTIALIAS_MODE, GetTextAntialiasMode)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(void, SetTextRenderingParams)(
		IGL2DRenderTarget *This,
		_In_opt_ IDWriteRenderingParams *textRenderingParams 
		) PURE;
    
	STDMETHOD_(void, GetTextRenderingParams)(
		IGL2DRenderTarget *This,
		_Outptr_result_maybenull_ IDWriteRenderingParams **textRenderingParams 
		) PURE;
    
	STDMETHOD_(void, SetTags)(
		IGL2DRenderTarget *This,
		GL2D_TAG tag1,
		GL2D_TAG tag2 
		) PURE;
    
	STDMETHOD_(void, GetTags)(
		IGL2DRenderTarget *This,
		_Out_opt_ GL2D_TAG *tag1,
		_Out_opt_ GL2D_TAG *tag2 
		) PURE;
    
	STDMETHOD_(void, PushLayer)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_LAYER_PARAMETERS *layerParameters,
		_In_opt_ IGL2DLayer *layer 
		) PURE;
    
	STDMETHOD_(void, PopLayer)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD(Flush)(
		IGL2DRenderTarget *This,
		_Out_opt_ GL2D_TAG *tag1,
		_Out_opt_ GL2D_TAG *tag2 
		) PURE;
    
	STDMETHOD_(void, SaveDrawingState)(
		IGL2DRenderTarget *This,
		_Inout_ IGL2DDrawingStateBlock *drawingStateBlock 
		) PURE;
    
	STDMETHOD_(void, RestoreDrawingState)(
		IGL2DRenderTarget *This,
		_In_ IGL2DDrawingStateBlock *drawingStateBlock 
		) PURE;
    
	STDMETHOD_(void, PushAxisAlignedClip)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_RECT_F *clipRect,
		GL2D_ANTIALIAS_MODE antialiasMode 
		) PURE;
    
	STDMETHOD_(void, PopAxisAlignedClip)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(void, Clear)(
		IGL2DRenderTarget *This,
		_In_opt_ const GL2D_COLOR_F *clearColor 
		) PURE;
    
	STDMETHOD_(void, BeginDraw)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD(EndDraw)(
		IGL2DRenderTarget *This,
		_Out_opt_ GL2D_TAG *tag1,
		_Out_opt_ GL2D_TAG *tag2 
		) PURE;
    
	STDMETHOD_(GL2D_PIXEL_FORMAT, GetPixelFormat)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(void, SetDpi)(
		IGL2DRenderTarget *This,
		float dpiX,
		float dpiY 
		) PURE;
    
	STDMETHOD_(void, GetDpi)(
		IGL2DRenderTarget *This,
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) PURE;
    
	STDMETHOD_(GL2D_SIZE_F, GetSize)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(GL2D_SIZE_U, GetPixelSize)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(uint32_t, GetMaximumBitmapSize)(
		IGL2DRenderTarget *This 
		) PURE;
    
	STDMETHOD_(bool, IsSupported)(
		IGL2DRenderTarget *This,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties 
		) PURE;
} IGL2DRenderTargetVtbl;

interface IGL2DRenderTarget
{
	const struct IGL2DRenderTargetVtbl *lpVtbl;
};

#define IGL2DRenderTarget_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DRenderTarget_AddRef(This) \
	((This)->lpVtbl->Base.Base.AddRef((IUnknown *)This))

#define IGL2DRenderTarget_Release(This) \
	((This)->lpVtbl->Base.Base.Release((IUnknown *)This))

#define IGL2DRenderTarget_GetFactory(This, factory) \
	((This)->lpVtbl->Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
	((This)->lpVtbl->CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap))

#define IGL2DRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
	((This)->lpVtbl->CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap))

#define IGL2DRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
	((This)->lpVtbl->CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap))

#define IGL2DRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
	((This)->lpVtbl->CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define IGL2DRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
	((This)->lpVtbl->CreateSolidColorBrush(This, color, brushProperties, solidColorBrush))

#define IGL2DRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
	((This)->lpVtbl->CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define IGL2DRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
	((This)->lpVtbl->CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define IGL2DRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
	((This)->lpVtbl->CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define IGL2DRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
	((This)->lpVtbl->CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define IGL2DRenderTarget_CreateLayer(This, size, layer) \
	((This)->lpVtbl->CreateLayer(This, size, layer))

#define IGL2DRenderTarget_CreateMesh(This, mesh) \
	((This)->lpVtbl->CreateMesh(This, mesh))

#define IGL2DRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle))

#define IGL2DRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->DrawRectangle(This, rect, brush, strokeWidth, strokeStyle))

#define IGL2DRenderTarget_FillRectangle(This, rect, brush) \
	((This)->lpVtbl->FillRectangle(This, rect, brush))

#define IGL2DRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle))

#define IGL2DRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
	((This)->lpVtbl->FillRoundedRectangle(This, roundedRect, brush))

#define IGL2DRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle))

#define IGL2DRenderTarget_FillEllipse(This, ellipse, brush) \
	((This)->lpVtbl->FillEllipse(This, ellipse, brush))

#define IGL2DRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle))

#define IGL2DRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
	((This)->lpVtbl->FillGeometry(This, geometry, brush, opacityBrush))

#define IGL2DRenderTarget_FillMesh(This, mesh, brush) \
	((This)->lpVtbl->FillMesh(This, mesh, brush))

#define IGL2DRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
	((This)->lpVtbl->FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define IGL2DRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
	((This)->lpVtbl->DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define IGL2DRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
	((This)->lpVtbl->DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define IGL2DRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
	((This)->lpVtbl->DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options))

#define IGL2DRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
	((This)->lpVtbl->DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define IGL2DRenderTarget_SetTransform(This, transform) \
	((This)->lpVtbl->SetTransform(This, transform))

#define IGL2DRenderTarget_GetTransform(This, transform) \
	((This)->lpVtbl->GetTransform(This, transform))

#define IGL2DRenderTarget_SetAntialiasMode(This, antialiasMode) \
	((This)->lpVtbl->SetAntialiasMode(This, antialiasMode))

#define IGL2DRenderTarget_GetAntialiasMode(This) \
	((This)->lpVtbl->GetAntialiasMode(This))

#define IGL2DRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
	((This)->lpVtbl->SetTextAntialiasMode(This, textAntialiasMode))

#define IGL2DRenderTarget_GetTextAntialiasMode(This) \
	((This)->lpVtbl->GetTextAntialiasMode(This))

#define IGL2DRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->SetTextRenderingParams(This, textRenderingParams))

#define IGL2DRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->GetTextRenderingParams(This, textRenderingParams))

#define IGL2DRenderTarget_SetTags(This, tag1, tag2) \
	((This)->lpVtbl->SetTags(This, tag1, tag2))

#define IGL2DRenderTarget_GetTags(This, tag1, tag2) \
	((This)->lpVtbl->GetTags(This, tag1, tag2))

#define IGL2DRenderTarget_PushLayer(This, layerParameters, layer) \
	((This)->lpVtbl->PushLayer(This, layerParameters, layer))

#define IGL2DRenderTarget_PopLayer(This) \
	((This)->lpVtbl->PopLayer(This))

#define IGL2DRenderTarget_Flush(This, tag1, tag2) \
	((This)->lpVtbl->Flush(This, tag1, tag2))

#define IGL2DRenderTarget_SaveDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->SaveDrawingState(This, drawingStateBlock))

#define IGL2DRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->RestoreDrawingState(This, drawingStateBlock))

#define IGL2DRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
	((This)->lpVtbl->PushAxisAlignedClip(This, clipRect, antialiasMode))

#define IGL2DRenderTarget_PopAxisAlignedClip(This) \
	((This)->lpVtbl->PopAxisAlignedClip(This))

#define IGL2DRenderTarget_Clear(This, clearColor) \
	((This)->lpVtbl->Clear(This, clearColor))

#define IGL2DRenderTarget_BeginDraw(This) \
	((This)->lpVtbl->BeginDraw(This))

#define IGL2DRenderTarget_EndDraw(This, tag1, tag2) \
	((This)->lpVtbl->EndDraw(This, tag1, tag2))

#define IGL2DRenderTarget_GetPixelFormat(This) \
	((This)->lpVtbl->GetPixelFormat(This))

#define IGL2DRenderTarget_SetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->SetDpi(This, dpiX, dpiY))

#define IGL2DRenderTarget_GetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->GetDpi(This, dpiX, dpiY))

#define IGL2DRenderTarget_GetSize(This) \
	((This)->lpVtbl->GetSize(This))

#define IGL2DRenderTarget_GetPixelSize(This) \
	((This)->lpVtbl->GetPixelSize(This))

#define IGL2DRenderTarget_GetMaximumBitmapSize(This) \
	((This)->lpVtbl->GetMaximumBitmapSize(This))

#define IGL2DRenderTarget_IsSupported(This, renderTargetProperties) \
	((This)->lpVtbl->IsSupported(This, renderTargetProperties))

typedef interface IGL2DBitmapRenderTarget IGL2DBitmapRenderTarget;

typedef struct IGL2DBitmapRenderTargetVtbl
{
    
	IGL2DRenderTargetVtbl Base;
    
    
	STDMETHOD(GetBitmap)(
		IGL2DBitmapRenderTarget *This,
		_Outptr_ IGL2DBitmap **bitmap 
		) PURE;
} IGL2DBitmapRenderTargetVtbl;

interface IGL2DBitmapRenderTarget
{
	const struct IGL2DBitmapRenderTargetVtbl *lpVtbl;
};


#define IGL2DBitmapRenderTarget_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DBitmapRenderTarget_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DBitmapRenderTarget_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DBitmapRenderTarget_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DBitmapRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmap((IGL2DRenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define IGL2DBitmapRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((IGL2DRenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define IGL2DBitmapRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateSharedBitmap((IGL2DRenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define IGL2DBitmapRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
	((This)->lpVtbl->Base.CreateBitmapBrush((IGL2DRenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define IGL2DBitmapRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
	((This)->lpVtbl->Base.CreateSolidColorBrush((IGL2DRenderTarget *)This, color, brushProperties, solidColorBrush))

#define IGL2DBitmapRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
	((This)->lpVtbl->Base.CreateGradientStopCollection((IGL2DRenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define IGL2DBitmapRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
	((This)->lpVtbl->Base.CreateLinearGradientBrush((IGL2DRenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define IGL2DBitmapRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
	((This)->lpVtbl->Base.CreateRadialGradientBrush((IGL2DRenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define IGL2DBitmapRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
	((This)->lpVtbl->Base.CreateCompatibleRenderTarget((IGL2DRenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define IGL2DBitmapRenderTarget_CreateLayer(This, size, layer) \
	((This)->lpVtbl->Base.CreateLayer((IGL2DRenderTarget *)This, size, layer))

#define IGL2DBitmapRenderTarget_CreateMesh(This, mesh) \
	((This)->lpVtbl->Base.CreateMesh((IGL2DRenderTarget *)This, mesh))

#define IGL2DBitmapRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawLine((IGL2DRenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define IGL2DBitmapRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRectangle((IGL2DRenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define IGL2DBitmapRenderTarget_FillRectangle(This, rect, brush) \
	((This)->lpVtbl->Base.FillRectangle((IGL2DRenderTarget *)This, rect, brush))

#define IGL2DBitmapRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define IGL2DBitmapRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
	((This)->lpVtbl->Base.FillRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush))

#define IGL2DBitmapRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawEllipse((IGL2DRenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define IGL2DBitmapRenderTarget_FillEllipse(This, ellipse, brush) \
	((This)->lpVtbl->Base.FillEllipse((IGL2DRenderTarget *)This, ellipse, brush))

#define IGL2DBitmapRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawGeometry((IGL2DRenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define IGL2DBitmapRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
	((This)->lpVtbl->Base.FillGeometry((IGL2DRenderTarget *)This, geometry, brush, opacityBrush))

#define IGL2DBitmapRenderTarget_FillMesh(This, mesh, brush) \
	((This)->lpVtbl->Base.FillMesh((IGL2DRenderTarget *)This, mesh, brush))

#define IGL2DBitmapRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
	((This)->lpVtbl->Base.FillOpacityMask((IGL2DRenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define IGL2DBitmapRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
	((This)->lpVtbl->Base.DrawBitmap((IGL2DRenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define IGL2DBitmapRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
	((This)->lpVtbl->Base.DrawText((IGL2DRenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define IGL2DBitmapRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
	((This)->lpVtbl->Base.DrawTextLayout((IGL2DRenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define IGL2DBitmapRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
	((This)->lpVtbl->Base.DrawGlyphRun((IGL2DRenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define IGL2DBitmapRenderTarget_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DBitmapRenderTarget_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DBitmapRenderTarget_SetAntialiasMode(This, antialiasMode) \
	((This)->lpVtbl->Base.SetAntialiasMode((IGL2DRenderTarget *)This, antialiasMode))

#define IGL2DBitmapRenderTarget_GetAntialiasMode(This) \
	((This)->lpVtbl->Base.GetAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
	((This)->lpVtbl->Base.SetTextAntialiasMode((IGL2DRenderTarget *)This, textAntialiasMode))

#define IGL2DBitmapRenderTarget_GetTextAntialiasMode(This) \
	((This)->lpVtbl->Base.GetTextAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.SetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DBitmapRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.GetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DBitmapRenderTarget_SetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.SetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DBitmapRenderTarget_GetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.GetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DBitmapRenderTarget_PushLayer(This, layerParameters, layer) \
	((This)->lpVtbl->Base.PushLayer((IGL2DRenderTarget *)This, layerParameters, layer))

#define IGL2DBitmapRenderTarget_PopLayer(This) \
	((This)->lpVtbl->Base.PopLayer((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_Flush(This, tag1, tag2) \
	((This)->lpVtbl->Base.Flush((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DBitmapRenderTarget_SaveDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.SaveDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DBitmapRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.RestoreDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DBitmapRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
	((This)->lpVtbl->Base.PushAxisAlignedClip((IGL2DRenderTarget *)This, clipRect, antialiasMode))

#define IGL2DBitmapRenderTarget_PopAxisAlignedClip(This) \
	((This)->lpVtbl->Base.PopAxisAlignedClip((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_Clear(This, clearColor) \
	((This)->lpVtbl->Base.Clear((IGL2DRenderTarget *)This, clearColor))

#define IGL2DBitmapRenderTarget_BeginDraw(This) \
	((This)->lpVtbl->Base.BeginDraw((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_EndDraw(This, tag1, tag2) \
	((This)->lpVtbl->Base.EndDraw((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DBitmapRenderTarget_GetPixelFormat(This) \
	((This)->lpVtbl->Base.GetPixelFormat((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_SetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.SetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DBitmapRenderTarget_GetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.GetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DBitmapRenderTarget_GetSize(This) \
	((This)->lpVtbl->Base.GetSize((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_GetPixelSize(This) \
	((This)->lpVtbl->Base.GetPixelSize((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_GetMaximumBitmapSize(This) \
	((This)->lpVtbl->Base.GetMaximumBitmapSize((IGL2DRenderTarget *)This))

#define IGL2DBitmapRenderTarget_IsSupported(This, renderTargetProperties) \
	((This)->lpVtbl->Base.IsSupported((IGL2DRenderTarget *)This, renderTargetProperties))

#define IGL2DBitmapRenderTarget_GetBitmap(This, bitmap) \
	((This)->lpVtbl->GetBitmap(This, bitmap))

typedef interface IGL2DHwndRenderTarget IGL2DHwndRenderTarget;

typedef struct IGL2DHwndRenderTargetVtbl
{
    
	IGL2DRenderTargetVtbl Base;
    
    
	STDMETHOD_(GL2D_WINDOW_STATE, CheckWindowState)(
		IGL2DHwndRenderTarget *This 
		) PURE;
    
	STDMETHOD(Resize)(
		IGL2DHwndRenderTarget *This,
		_In_ const GL2D_SIZE_U *pixelSize 
		) PURE;
    
	STDMETHOD_(HWND, GetHwnd)(
		IGL2DHwndRenderTarget *This 
		) PURE;
} IGL2DHwndRenderTargetVtbl;

interface IGL2DHwndRenderTarget
{
	const struct IGL2DHwndRenderTargetVtbl *lpVtbl;
};


#define IGL2DHwndRenderTarget_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DHwndRenderTarget_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DHwndRenderTarget_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DHwndRenderTarget_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DHwndRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmap((IGL2DRenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define IGL2DHwndRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((IGL2DRenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define IGL2DHwndRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateSharedBitmap((IGL2DRenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define IGL2DHwndRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
	((This)->lpVtbl->Base.CreateBitmapBrush((IGL2DRenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define IGL2DHwndRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
	((This)->lpVtbl->Base.CreateSolidColorBrush((IGL2DRenderTarget *)This, color, brushProperties, solidColorBrush))

#define IGL2DHwndRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
	((This)->lpVtbl->Base.CreateGradientStopCollection((IGL2DRenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define IGL2DHwndRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
	((This)->lpVtbl->Base.CreateLinearGradientBrush((IGL2DRenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define IGL2DHwndRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
	((This)->lpVtbl->Base.CreateRadialGradientBrush((IGL2DRenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define IGL2DHwndRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
	((This)->lpVtbl->Base.CreateCompatibleRenderTarget((IGL2DRenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define IGL2DHwndRenderTarget_CreateLayer(This, size, layer) \
	((This)->lpVtbl->Base.CreateLayer((IGL2DRenderTarget *)This, size, layer))

#define IGL2DHwndRenderTarget_CreateMesh(This, mesh) \
	((This)->lpVtbl->Base.CreateMesh((IGL2DRenderTarget *)This, mesh))

#define IGL2DHwndRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawLine((IGL2DRenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define IGL2DHwndRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRectangle((IGL2DRenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define IGL2DHwndRenderTarget_FillRectangle(This, rect, brush) \
	((This)->lpVtbl->Base.FillRectangle((IGL2DRenderTarget *)This, rect, brush))

#define IGL2DHwndRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define IGL2DHwndRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
	((This)->lpVtbl->Base.FillRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush))

#define IGL2DHwndRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawEllipse((IGL2DRenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define IGL2DHwndRenderTarget_FillEllipse(This, ellipse, brush) \
	((This)->lpVtbl->Base.FillEllipse((IGL2DRenderTarget *)This, ellipse, brush))

#define IGL2DHwndRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawGeometry((IGL2DRenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define IGL2DHwndRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
	((This)->lpVtbl->Base.FillGeometry((IGL2DRenderTarget *)This, geometry, brush, opacityBrush))

#define IGL2DHwndRenderTarget_FillMesh(This, mesh, brush) \
	((This)->lpVtbl->Base.FillMesh((IGL2DRenderTarget *)This, mesh, brush))

#define IGL2DHwndRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
	((This)->lpVtbl->Base.FillOpacityMask((IGL2DRenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define IGL2DHwndRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
	((This)->lpVtbl->Base.DrawBitmap((IGL2DRenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define IGL2DHwndRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
	((This)->lpVtbl->Base.DrawText((IGL2DRenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define IGL2DHwndRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
	((This)->lpVtbl->Base.DrawTextLayout((IGL2DRenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define IGL2DHwndRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
	((This)->lpVtbl->Base.DrawGlyphRun((IGL2DRenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define IGL2DHwndRenderTarget_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DHwndRenderTarget_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DHwndRenderTarget_SetAntialiasMode(This, antialiasMode) \
	((This)->lpVtbl->Base.SetAntialiasMode((IGL2DRenderTarget *)This, antialiasMode))

#define IGL2DHwndRenderTarget_GetAntialiasMode(This) \
	((This)->lpVtbl->Base.GetAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
	((This)->lpVtbl->Base.SetTextAntialiasMode((IGL2DRenderTarget *)This, textAntialiasMode))

#define IGL2DHwndRenderTarget_GetTextAntialiasMode(This) \
	((This)->lpVtbl->Base.GetTextAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.SetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DHwndRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.GetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DHwndRenderTarget_SetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.SetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DHwndRenderTarget_GetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.GetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DHwndRenderTarget_PushLayer(This, layerParameters, layer) \
	((This)->lpVtbl->Base.PushLayer((IGL2DRenderTarget *)This, layerParameters, layer))

#define IGL2DHwndRenderTarget_PopLayer(This) \
	((This)->lpVtbl->Base.PopLayer((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_Flush(This, tag1, tag2) \
	((This)->lpVtbl->Base.Flush((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DHwndRenderTarget_SaveDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.SaveDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DHwndRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.RestoreDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DHwndRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
	((This)->lpVtbl->Base.PushAxisAlignedClip((IGL2DRenderTarget *)This, clipRect, antialiasMode))

#define IGL2DHwndRenderTarget_PopAxisAlignedClip(This) \
	((This)->lpVtbl->Base.PopAxisAlignedClip((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_Clear(This, clearColor) \
	((This)->lpVtbl->Base.Clear((IGL2DRenderTarget *)This, clearColor))

#define IGL2DHwndRenderTarget_BeginDraw(This) \
	((This)->lpVtbl->Base.BeginDraw((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_EndDraw(This, tag1, tag2) \
	((This)->lpVtbl->Base.EndDraw((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DHwndRenderTarget_GetPixelFormat(This) \
	((This)->lpVtbl->Base.GetPixelFormat((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_SetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.SetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DHwndRenderTarget_GetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.GetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DHwndRenderTarget_GetSize(This) \
	((This)->lpVtbl->Base.GetSize((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_GetPixelSize(This) \
	((This)->lpVtbl->Base.GetPixelSize((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_GetMaximumBitmapSize(This) \
	((This)->lpVtbl->Base.GetMaximumBitmapSize((IGL2DRenderTarget *)This))

#define IGL2DHwndRenderTarget_IsSupported(This, renderTargetProperties) \
	((This)->lpVtbl->Base.IsSupported((IGL2DRenderTarget *)This, renderTargetProperties))

#define IGL2DHwndRenderTarget_CheckWindowState(This) \
	((This)->lpVtbl->CheckWindowState(This))

#define IGL2DHwndRenderTarget_Resize(This, pixelSize) \
	((This)->lpVtbl->Resize(This, pixelSize))

#define IGL2DHwndRenderTarget_GetHwnd(This) \
	((This)->lpVtbl->GetHwnd(This))

typedef interface IGL2DGdiInteropRenderTarget IGL2DGdiInteropRenderTarget;

typedef struct IGL2DGdiInteropRenderTargetVtbl
{
    
	IUnknownVtbl Base;
    
    
	STDMETHOD(GetDC)(
		IGL2DGdiInteropRenderTarget *This,
		GL2D_DC_INITIALIZE_MODE mode,
		_Out_ HDC *hdc 
		) PURE;
    
	STDMETHOD(ReleaseDC)(
		IGL2DGdiInteropRenderTarget *This,
		_In_opt_ const RECT *update 
		) PURE;
} IGL2DGdiInteropRenderTargetVtbl;

interface IGL2DGdiInteropRenderTarget
{
	const struct IGL2DGdiInteropRenderTargetVtbl *lpVtbl;
};


#define IGL2DGdiInteropRenderTarget_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DGdiInteropRenderTarget_AddRef(This) \
	((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define IGL2DGdiInteropRenderTarget_Release(This) \
	((This)->lpVtbl->Base.Release((IUnknown *)This))

#define IGL2DGdiInteropRenderTarget_GetDC(This, mode, hdc) \
	((This)->lpVtbl->GetDC(This, mode, hdc))

#define IGL2DGdiInteropRenderTarget_ReleaseDC(This, update) \
	((This)->lpVtbl->ReleaseDC(This, update))

typedef interface IGL2DDCRenderTarget IGL2DDCRenderTarget;

typedef struct IGL2DDCRenderTargetVtbl
{
    
	IGL2DRenderTargetVtbl Base;
    
    
	STDMETHOD(BindDC)(
		IGL2DDCRenderTarget *This,
		_In_ const HDC hDC,
		_In_ const RECT *pSubRect 
		) PURE;
} IGL2DDCRenderTargetVtbl;

interface IGL2DDCRenderTarget
{
	const struct IGL2DDCRenderTargetVtbl *lpVtbl;
};


#define IGL2DDCRenderTarget_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.Base.Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DDCRenderTarget_AddRef(This) \
	((This)->lpVtbl->Base.Base.Base.AddRef((IUnknown *)This))

#define IGL2DDCRenderTarget_Release(This) \
	((This)->lpVtbl->Base.Base.Base.Release((IUnknown *)This))

#define IGL2DDCRenderTarget_GetFactory(This, factory) \
	((This)->lpVtbl->Base.Base.GetFactory((IGL2DResource *)This, factory))

#define IGL2DDCRenderTarget_CreateBitmap(This, size, srcData, pitch, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmap((IGL2DRenderTarget *)This, size, srcData, pitch, bitmapProperties, bitmap))

#define IGL2DDCRenderTarget_CreateBitmapFromWicBitmap(This, wicBitmapSource, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateBitmapFromWicBitmap((IGL2DRenderTarget *)This, wicBitmapSource, bitmapProperties, bitmap))

#define IGL2DDCRenderTarget_CreateSharedBitmap(This, riid, data, bitmapProperties, bitmap) \
	((This)->lpVtbl->Base.CreateSharedBitmap((IGL2DRenderTarget *)This, riid, data, bitmapProperties, bitmap))

#define IGL2DDCRenderTarget_CreateBitmapBrush(This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush) \
	((This)->lpVtbl->Base.CreateBitmapBrush((IGL2DRenderTarget *)This, bitmap, bitmapBrushProperties, brushProperties, bitmapBrush))

#define IGL2DDCRenderTarget_CreateSolidColorBrush(This, color, brushProperties, solidColorBrush) \
	((This)->lpVtbl->Base.CreateSolidColorBrush((IGL2DRenderTarget *)This, color, brushProperties, solidColorBrush))

#define IGL2DDCRenderTarget_CreateGradientStopCollection(This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection) \
	((This)->lpVtbl->Base.CreateGradientStopCollection((IGL2DRenderTarget *)This, gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection))

#define IGL2DDCRenderTarget_CreateLinearGradientBrush(This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush) \
	((This)->lpVtbl->Base.CreateLinearGradientBrush((IGL2DRenderTarget *)This, linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush))

#define IGL2DDCRenderTarget_CreateRadialGradientBrush(This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush) \
	((This)->lpVtbl->Base.CreateRadialGradientBrush((IGL2DRenderTarget *)This, radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush))

#define IGL2DDCRenderTarget_CreateCompatibleRenderTarget(This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget) \
	((This)->lpVtbl->Base.CreateCompatibleRenderTarget((IGL2DRenderTarget *)This, desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget))

#define IGL2DDCRenderTarget_CreateLayer(This, size, layer) \
	((This)->lpVtbl->Base.CreateLayer((IGL2DRenderTarget *)This, size, layer))

#define IGL2DDCRenderTarget_CreateMesh(This, mesh) \
	((This)->lpVtbl->Base.CreateMesh((IGL2DRenderTarget *)This, mesh))

#define IGL2DDCRenderTarget_DrawLine(This, point0, point1, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawLine((IGL2DRenderTarget *)This, point0, point1, brush, strokeWidth, strokeStyle))

#define IGL2DDCRenderTarget_DrawRectangle(This, rect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRectangle((IGL2DRenderTarget *)This, rect, brush, strokeWidth, strokeStyle))

#define IGL2DDCRenderTarget_FillRectangle(This, rect, brush) \
	((This)->lpVtbl->Base.FillRectangle((IGL2DRenderTarget *)This, rect, brush))

#define IGL2DDCRenderTarget_DrawRoundedRectangle(This, roundedRect, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush, strokeWidth, strokeStyle))

#define IGL2DDCRenderTarget_FillRoundedRectangle(This, roundedRect, brush) \
	((This)->lpVtbl->Base.FillRoundedRectangle((IGL2DRenderTarget *)This, roundedRect, brush))

#define IGL2DDCRenderTarget_DrawEllipse(This, ellipse, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawEllipse((IGL2DRenderTarget *)This, ellipse, brush, strokeWidth, strokeStyle))

#define IGL2DDCRenderTarget_FillEllipse(This, ellipse, brush) \
	((This)->lpVtbl->Base.FillEllipse((IGL2DRenderTarget *)This, ellipse, brush))

#define IGL2DDCRenderTarget_DrawGeometry(This, geometry, brush, strokeWidth, strokeStyle) \
	((This)->lpVtbl->Base.DrawGeometry((IGL2DRenderTarget *)This, geometry, brush, strokeWidth, strokeStyle))

#define IGL2DDCRenderTarget_FillGeometry(This, geometry, brush, opacityBrush) \
	((This)->lpVtbl->Base.FillGeometry((IGL2DRenderTarget *)This, geometry, brush, opacityBrush))

#define IGL2DDCRenderTarget_FillMesh(This, mesh, brush) \
	((This)->lpVtbl->Base.FillMesh((IGL2DRenderTarget *)This, mesh, brush))

#define IGL2DDCRenderTarget_FillOpacityMask(This, opacityMask, brush, content, destinationRectangle, sourceRectangle) \
	((This)->lpVtbl->Base.FillOpacityMask((IGL2DRenderTarget *)This, opacityMask, brush, content, destinationRectangle, sourceRectangle))

#define IGL2DDCRenderTarget_DrawBitmap(This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle) \
	((This)->lpVtbl->Base.DrawBitmap((IGL2DRenderTarget *)This, bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle))

#define IGL2DDCRenderTarget_DrawText(This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode) \
	((This)->lpVtbl->Base.DrawText((IGL2DRenderTarget *)This, string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode))

#define IGL2DDCRenderTarget_DrawTextLayout(This, origin, textLayout, defaultForegroundBrush, options) \
	((This)->lpVtbl->Base.DrawTextLayout((IGL2DRenderTarget *)This, origin, textLayout, defaultForegroundBrush, options))

#define IGL2DDCRenderTarget_DrawGlyphRun(This, baselineOrigin, glyphRun, foregroundBrush, measuringMode) \
	((This)->lpVtbl->Base.DrawGlyphRun((IGL2DRenderTarget *)This, baselineOrigin, glyphRun, foregroundBrush, measuringMode))

#define IGL2DDCRenderTarget_SetTransform(This, transform) \
	((This)->lpVtbl->Base.SetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DDCRenderTarget_GetTransform(This, transform) \
	((This)->lpVtbl->Base.GetTransform((IGL2DRenderTarget *)This, transform))

#define IGL2DDCRenderTarget_SetAntialiasMode(This, antialiasMode) \
	((This)->lpVtbl->Base.SetAntialiasMode((IGL2DRenderTarget *)This, antialiasMode))

#define IGL2DDCRenderTarget_GetAntialiasMode(This) \
	((This)->lpVtbl->Base.GetAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_SetTextAntialiasMode(This, textAntialiasMode) \
	((This)->lpVtbl->Base.SetTextAntialiasMode((IGL2DRenderTarget *)This, textAntialiasMode))

#define IGL2DDCRenderTarget_GetTextAntialiasMode(This) \
	((This)->lpVtbl->Base.GetTextAntialiasMode((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_SetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.SetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DDCRenderTarget_GetTextRenderingParams(This, textRenderingParams) \
	((This)->lpVtbl->Base.GetTextRenderingParams((IGL2DRenderTarget *)This, textRenderingParams))

#define IGL2DDCRenderTarget_SetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.SetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DDCRenderTarget_GetTags(This, tag1, tag2) \
	((This)->lpVtbl->Base.GetTags((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DDCRenderTarget_PushLayer(This, layerParameters, layer) \
	((This)->lpVtbl->Base.PushLayer((IGL2DRenderTarget *)This, layerParameters, layer))

#define IGL2DDCRenderTarget_PopLayer(This) \
	((This)->lpVtbl->Base.PopLayer((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_Flush(This, tag1, tag2) \
	((This)->lpVtbl->Base.Flush((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DDCRenderTarget_SaveDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.SaveDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DDCRenderTarget_RestoreDrawingState(This, drawingStateBlock) \
	((This)->lpVtbl->Base.RestoreDrawingState((IGL2DRenderTarget *)This, drawingStateBlock))

#define IGL2DDCRenderTarget_PushAxisAlignedClip(This, clipRect, antialiasMode) \
	((This)->lpVtbl->Base.PushAxisAlignedClip((IGL2DRenderTarget *)This, clipRect, antialiasMode))

#define IGL2DDCRenderTarget_PopAxisAlignedClip(This) \
	((This)->lpVtbl->Base.PopAxisAlignedClip((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_Clear(This, clearColor) \
	((This)->lpVtbl->Base.Clear((IGL2DRenderTarget *)This, clearColor))

#define IGL2DDCRenderTarget_BeginDraw(This) \
	((This)->lpVtbl->Base.BeginDraw((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_EndDraw(This, tag1, tag2) \
	((This)->lpVtbl->Base.EndDraw((IGL2DRenderTarget *)This, tag1, tag2))

#define IGL2DDCRenderTarget_GetPixelFormat(This) \
	((This)->lpVtbl->Base.GetPixelFormat((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_SetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.SetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DDCRenderTarget_GetDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->Base.GetDpi((IGL2DRenderTarget *)This, dpiX, dpiY))

#define IGL2DDCRenderTarget_GetSize(This) \
	((This)->lpVtbl->Base.GetSize((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_GetPixelSize(This) \
	((This)->lpVtbl->Base.GetPixelSize((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_GetMaximumBitmapSize(This) \
	((This)->lpVtbl->Base.GetMaximumBitmapSize((IGL2DRenderTarget *)This))

#define IGL2DDCRenderTarget_IsSupported(This, renderTargetProperties) \
	((This)->lpVtbl->Base.IsSupported((IGL2DRenderTarget *)This, renderTargetProperties))

#define IGL2DDCRenderTarget_BindDC(This, hDC, pSubRect) \
	((This)->lpVtbl->BindDC(This, hDC, pSubRect))

typedef interface IGL2DFactory IGL2DFactory;

typedef struct IGL2DFactoryVtbl
{
    
	IUnknownVtbl Base;
    
    
	STDMETHOD(ReloadSystemMetrics)(
		IGL2DFactory *This 
		) PURE;
    
	STDMETHOD_(void, GetDesktopDpi)(
		IGL2DFactory *This,
		_Out_ float *dpiX,
		_Out_ float *dpiY 
		) PURE;
    
	STDMETHOD(CreateRectangleGeometry)(
		IGL2DFactory *This,
		_In_ const GL2D_RECT_F *rectangle,
		_Outptr_ IGL2DRectangleGeometry **rectangleGeometry 
		) PURE;
    
	STDMETHOD(CreateRoundedRectangleGeometry)(
		IGL2DFactory *This,
		_In_ const GL2D_ROUNDED_RECT *roundedRectangle,
		_Outptr_ IGL2DRoundedRectangleGeometry **roundedRectangleGeometry 
		) PURE;
    
	STDMETHOD(CreateEllipseGeometry)(
		IGL2DFactory *This,
		_In_ const GL2D_ELLIPSE *ellipse,
		_Outptr_ IGL2DEllipseGeometry **ellipseGeometry 
		) PURE;
    
	STDMETHOD(CreateGeometryGroup)(
		IGL2DFactory *This,
		GL2D_FILL_MODE fillMode,
		_In_reads_(geometriesCount) IGL2DGeometry **geometries,
		uint32_t geometriesCount,
		_Outptr_ IGL2DGeometryGroup **geometryGroup 
		) PURE;
    
	STDMETHOD(CreateTransformedGeometry)(
		IGL2DFactory *This,
		_In_ IGL2DGeometry *sourceGeometry,
		_In_ const GL2D_MATRIX_3X2_F *transform,
		_Outptr_ IGL2DTransformedGeometry **transformedGeometry 
		) PURE;
    
	STDMETHOD(CreatePathGeometry)(
		IGL2DFactory *This,
		_Outptr_ IGL2DPathGeometry **pathGeometry 
		) PURE;
    
	STDMETHOD(CreateStrokeStyle)(
		IGL2DFactory *This,
		_In_ const GL2D_STROKE_STYLE_PROPERTIES *strokeStyleProperties,
		_In_reads_opt_(dashesCount) const float *dashes,
		uint32_t dashesCount,
		_Outptr_ IGL2DStrokeStyle **strokeStyle 
		) PURE;
    
	STDMETHOD(CreateDrawingStateBlock)(
		IGL2DFactory *This,
		_In_opt_ const GL2D_DRAWING_STATE_DESCRIPTION *drawingStateDescription,
		_In_opt_ IDWriteRenderingParams *textRenderingParams,
		_Outptr_ IGL2DDrawingStateBlock **drawingStateBlock 
		) PURE;
    
	STDMETHOD(CreateWicBitmapRenderTarget)(
		IGL2DFactory *This,
		_In_ IWICBitmap *target,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		) PURE;
    
	STDMETHOD(CreateHwndRenderTarget)(
		IGL2DFactory *This,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_In_ const GL2D_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties,
		_Outptr_ IGL2DHwndRenderTarget **hwndRenderTarget 
		) PURE;
    
	STDMETHOD(CreateDxgiSurfaceRenderTarget)(
		IGL2DFactory *This,
		_In_ IDXGISurface *dxgiSurface,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DRenderTarget **renderTarget 
		) PURE;
    
	STDMETHOD(CreateDCRenderTarget)(
		IGL2DFactory *This,
		_In_ const GL2D_RENDER_TARGET_PROPERTIES *renderTargetProperties,
		_Outptr_ IGL2DDCRenderTarget **dcRenderTarget 
		) PURE;
} IGL2DFactoryVtbl;

interface IGL2DFactory
{
	const struct IGL2DFactoryVtbl *lpVtbl;
};


#define IGL2DFactory_QueryInterface(This, riid, ppv) \
	((This)->lpVtbl->Base.QueryInterface((IUnknown *)This, riid, ppv))

#define IGL2DFactory_AddRef(This) \
	((This)->lpVtbl->Base.AddRef((IUnknown *)This))

#define IGL2DFactory_Release(This) \
	((This)->lpVtbl->Base.Release((IUnknown *)This))

#define IGL2DFactory_ReloadSystemMetrics(This) \
	((This)->lpVtbl->ReloadSystemMetrics(This))

#define IGL2DFactory_GetDesktopDpi(This, dpiX, dpiY) \
	((This)->lpVtbl->GetDesktopDpi(This, dpiX, dpiY))

#define IGL2DFactory_CreateRectangleGeometry(This, rectangle, rectangleGeometry) \
	((This)->lpVtbl->CreateRectangleGeometry(This, rectangle, rectangleGeometry))

#define IGL2DFactory_CreateRoundedRectangleGeometry(This, roundedRectangle, roundedRectangleGeometry) \
	((This)->lpVtbl->CreateRoundedRectangleGeometry(This, roundedRectangle, roundedRectangleGeometry))

#define IGL2DFactory_CreateEllipseGeometry(This, ellipse, ellipseGeometry) \
	((This)->lpVtbl->CreateEllipseGeometry(This, ellipse, ellipseGeometry))

#define IGL2DFactory_CreateGeometryGroup(This, fillMode, geometries, geometriesCount, geometryGroup) \
	((This)->lpVtbl->CreateGeometryGroup(This, fillMode, geometries, geometriesCount, geometryGroup))

#define IGL2DFactory_CreateTransformedGeometry(This, sourceGeometry, transform, transformedGeometry) \
	((This)->lpVtbl->CreateTransformedGeometry(This, sourceGeometry, transform, transformedGeometry))

#define IGL2DFactory_CreatePathGeometry(This, pathGeometry) \
	((This)->lpVtbl->CreatePathGeometry(This, pathGeometry))

#define IGL2DFactory_CreateStrokeStyle(This, strokeStyleProperties, dashes, dashesCount, strokeStyle) \
	((This)->lpVtbl->CreateStrokeStyle(This, strokeStyleProperties, dashes, dashesCount, strokeStyle))

#define IGL2DFactory_CreateDrawingStateBlock(This, drawingStateDescription, textRenderingParams, drawingStateBlock) \
	((This)->lpVtbl->CreateDrawingStateBlock(This, drawingStateDescription, textRenderingParams, drawingStateBlock))

#define IGL2DFactory_CreateWicBitmapRenderTarget(This, target, renderTargetProperties, renderTarget) \
	((This)->lpVtbl->CreateWicBitmapRenderTarget(This, target, renderTargetProperties, renderTarget))

#define IGL2DFactory_CreateHwndRenderTarget(This, renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget) \
	((This)->lpVtbl->CreateHwndRenderTarget(This, renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget))

#define IGL2DFactory_CreateDxgiSurfaceRenderTarget(This, dxgiSurface, renderTargetProperties, renderTarget) \
	((This)->lpVtbl->CreateDxgiSurfaceRenderTarget(This, dxgiSurface, renderTargetProperties, renderTarget))

#define IGL2DFactory_CreateDCRenderTarget(This, renderTargetProperties, dcRenderTarget) \
	((This)->lpVtbl->CreateDCRenderTarget(This, renderTargetProperties, dcRenderTarget))

#endif

#ifdef __cplusplus
extern "C"
{
#endif

	//
	// This export cannot be in a namespace because compiler name mangling isn't consistent
	// also, this must be 'C' callable.
	//
	HRESULT WINAPI
	GL2DCreateFactory(
		_In_ GL2D_FACTORY_TYPE factoryType,
		_In_ REFIID riid,
		_In_opt_ const GL2D_FACTORY_OPTIONS *pFactoryOptions,
		_Out_ void **ppIFactory
		);


	void WINAPI
	GL2DMakeRotateMatrix(
		_In_ float angle,
		_In_ GL2D_POINT_2F center,
		_Out_ GL2D_MATRIX_3X2_F *matrix
		);

	void WINAPI
	GL2DMakeSkewMatrix(
		_In_ float angleX,
		_In_ float angleY,
		_In_ GL2D_POINT_2F center,
		_Out_ GL2D_MATRIX_3X2_F *matrix
		);

	bool WINAPI
	GL2DIsMatrixInvertible(
		_In_ const GL2D_MATRIX_3X2_F *matrix
		);

	bool WINAPI
	GL2DInvertMatrix(
		_Inout_ GL2D_MATRIX_3X2_F *matrix
		);

#ifdef __cplusplus
}
#endif

#ifndef GL2DFORCEINLINE
#	define GL2DFORCEINLINE FORCEINLINE
#endif // #ifndef GL2DFORCEINLINE

//#include <GL2DHelper.h>

#ifndef GL2D_USE_C_DEFINITIONS

COM_DECLSPEC_NOTHROW
inline
HRESULT
GL2DCreateFactory(
	_In_ GL2D_FACTORY_TYPE factoryType,
	_In_ REFIID riid,
	_Out_ void **factory
	)
{
	return
		GL2DCreateFactory(
			factoryType,
			riid,
			NULL,
			factory);
}


template<class Factory>
COM_DECLSPEC_NOTHROW
HRESULT
GL2DCreateFactory(
	_In_ GL2D_FACTORY_TYPE factoryType,
	_Out_ Factory **factory
	)
{
	return
		GL2DCreateFactory(
			factoryType,
			__uuidof(Factory),
			reinterpret_cast<void **>(factory));
}

template<class Factory>
COM_DECLSPEC_NOTHROW
HRESULT
GL2DCreateFactory(
	_In_ GL2D_FACTORY_TYPE factoryType,
	_In_ const GL2D_FACTORY_OPTIONS &factoryOptions,
	_Out_ Factory **ppFactory
	)
{
	return
		GL2DCreateFactory(
			factoryType,
			__uuidof(Factory),
			&factoryOptions,
			reinterpret_cast<void **>(ppFactory));
}

#endif

#endif
