#ifndef ___OGL2D_HELPER_H___
#define ___OGL2D_HELPER_H___

#ifndef ___OGL2D_GL2D_H___
#include "GL2D.h"
#endif // #ifndef ___OGL2D_GL2D_H___

namespace GL2D
{
	//
	// Forward declared IdentityMatrix function to allow matrix class to use
	// these constructors.
	// 
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_MATRIX_3X2_F
	IdentityMatrix();

	//
	// The default trait type for objects in D2D is float.
	//
	template< typename Type >
	struct TypeTraits
	{
		typedef GL2D_POINT_2F Point;
		typedef GL2D_SIZE_F   Size;
		typedef GL2D_RECT_F   Rect;
	};

	template<>
	struct TypeTraits< uint32_t >
	{
		typedef GL2D_POINT_2U Point;
		typedef GL2D_SIZE_U   Size;
		typedef GL2D_RECT_U   Rect;
	};

	static
	COM_DECLSPEC_NOTHROW
	inline
	float FloatMax()
	{
#ifdef FLT_MAX
			return FLT_MAX;
#else
			return 3.402823466e+38F;
#endif
	}

	//
	// Construction helpers
	//
	template< typename Type >
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	typename TypeTraits< Type >::Point
	Point2(
		Type x,
		Type y
		)
	{
		typename TypeTraits< Type >::Point point = { x, y };

		return point;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_POINT_2F
	Point2F(
		float x = 0.f,
		float y = 0.f
		)
	{
		return Point2< float >(x, y);
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_POINT_2U
	Point2U(
		uint32_t x = 0,
		uint32_t y = 0
		)
	{
		return Point2< uint32_t >(x, y);
	}

	template< typename Type >
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	typename TypeTraits< Type >::Size
	Size(
		Type width,
		Type height
		)
	{
		typename TypeTraits< Type >::Size size = { width, height };

		return size;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_SIZE_F
	SizeF(
		float width = 0.f,
		float height = 0.f
		)
	{
		return Size< float >(width, height);
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_SIZE_U
	SizeU(
		uint32_t width = 0,
		uint32_t height = 0
		)
	{
		return Size< uint32_t >(width, height);
	}

	template< typename Type >
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	typename TypeTraits< Type >::Rect
	Rect(
		Type left,
		Type top,
		Type right,
		Type bottom
		)
	{
		typename TypeTraits< Type >::Rect rect = { left, top, right, bottom };

		return rect;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_RECT_F
	RectF(
		float left = 0.f,
		float top = 0.f,
		float right = 0.f,
		float bottom = 0.f
		)
	{
		return Rect< float >(left, top, right, bottom);
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_RECT_U
	RectU(
		uint32_t left = 0,
		uint32_t top = 0,
		uint32_t right = 0,
		uint32_t bottom = 0
		)
	{
		return Rect< uint32_t >(left, top, right, bottom);
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_RECT_F
	InfiniteRect()
	{
		GL2D_RECT_F rect = { -FloatMax(), -FloatMax(), FloatMax(),  FloatMax() };

		return rect;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_ARC_SEGMENT
	ArcSegment(
		const GL2D_POINT_2F &point,
		const GL2D_SIZE_F &size,
		float rotationAngle,
		GL2D_SWEEP_DIRECTION sweepDirection,
		GL2D_ARC_SIZE arcSize
		)
	{
		GL2D_ARC_SEGMENT arcSegment = { point, size, rotationAngle, sweepDirection, arcSize };

		return arcSegment;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_BEZIER_SEGMENT
	BezierSegment(
		const GL2D_POINT_2F &point1,
		const GL2D_POINT_2F &point2,
		const GL2D_POINT_2F &point3
		)
	{
		GL2D_BEZIER_SEGMENT bezierSegment = { point1, point2, point3 };

		return bezierSegment;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_ELLIPSE
	Ellipse(
		const GL2D_POINT_2F &center,
		float radiusX,
		float radiusY
		)
	{
		GL2D_ELLIPSE ellipse;

		ellipse.point = center;
		ellipse.radiusX = radiusX;
		ellipse.radiusY = radiusY;

		return ellipse;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_ROUNDED_RECT
	RoundedRect(
		const GL2D_RECT_F &rect,
		float radiusX,
		float radiusY
		)
	{
		GL2D_ROUNDED_RECT roundedRect;

		roundedRect.rect = rect;
		roundedRect.radiusX = radiusX;
		roundedRect.radiusY = radiusY;

		return roundedRect;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_BRUSH_PROPERTIES
	BrushProperties(
		float opacity = 1.0,
		const GL2D_MATRIX_3X2_F &transform = GL2D::IdentityMatrix()
		)
	{
		GL2D_BRUSH_PROPERTIES brushProperties;

		brushProperties.opacity = opacity;
		brushProperties.transform = transform;

		return brushProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_GRADIENT_STOP
	GradientStop(
		float position,
		const GL2D_COLOR_F &color
		)
	{
		GL2D_GRADIENT_STOP gradientStop = { position, color };

		return gradientStop;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_QUADRATIC_BEZIER_SEGMENT
	QuadraticBezierSegment(
		const GL2D_POINT_2F &point1,
		const GL2D_POINT_2F &point2
		)
	{
		GL2D_QUADRATIC_BEZIER_SEGMENT quadraticBezier = { point1, point2 };

		return quadraticBezier;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_STROKE_STYLE_PROPERTIES
	StrokeStyleProperties(
		GL2D_CAP_STYLE startCap = GL2D_CAP_STYLE_FLAT,
		GL2D_CAP_STYLE endCap = GL2D_CAP_STYLE_FLAT,
		GL2D_CAP_STYLE dashCap = GL2D_CAP_STYLE_FLAT,
		GL2D_LINE_JOIN lineJoin = GL2D_LINE_JOIN_MITER,
		float miterLimit = 10.0f,
		GL2D_DASH_STYLE dashStyle = GL2D_DASH_STYLE_SOLID,
		float dashOffset = 0.0f
		)
	{
		GL2D_STROKE_STYLE_PROPERTIES strokeStyleProperties;

		strokeStyleProperties.startCap = startCap;
		strokeStyleProperties.endCap = endCap;
		strokeStyleProperties.dashCap = dashCap;
		strokeStyleProperties.lineJoin = lineJoin;
		strokeStyleProperties.miterLimit = miterLimit;
		strokeStyleProperties.dashStyle = dashStyle;
		strokeStyleProperties.dashOffset = dashOffset;

		return strokeStyleProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_BITMAP_BRUSH_PROPERTIES
	BitmapBrushProperties(
		GL2D_EXTEND_MODE extendModeX = GL2D_EXTEND_MODE_CLAMP,
		GL2D_EXTEND_MODE extendModeY = GL2D_EXTEND_MODE_CLAMP,
		GL2D_BITMAP_INTERPOLATION_MODE interpolationMode = GL2D_BITMAP_INTERPOLATION_MODE_LINEAR
		)
	{
		GL2D_BITMAP_BRUSH_PROPERTIES bitmapBrushProperties;

		bitmapBrushProperties.extendModeX = extendModeX;
		bitmapBrushProperties.extendModeY = extendModeY;
		bitmapBrushProperties.interpolationMode = interpolationMode;

		return bitmapBrushProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES
	LinearGradientBrushProperties(
		const GL2D_POINT_2F &startPoint,
		const GL2D_POINT_2F &endPoint
		)
	{
		GL2D_LINEAR_GRADIENT_BRUSH_PROPERTIES linearGradientBrushProperties;

		linearGradientBrushProperties.startPoint = startPoint;
		linearGradientBrushProperties.endPoint = endPoint;

		return linearGradientBrushProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES
	RadialGradientBrushProperties(
		const GL2D_POINT_2F &center,
		const GL2D_POINT_2F &gradientOriginOffset,
		float radiusX,
		float radiusY
		)
	{
		GL2D_RADIAL_GRADIENT_BRUSH_PROPERTIES radialGradientBrushProperties;

		radialGradientBrushProperties.center = center;
		radialGradientBrushProperties.gradientOriginOffset = gradientOriginOffset;
		radialGradientBrushProperties.radiusX = radiusX;
		radialGradientBrushProperties.radiusY = radiusY;

		return radialGradientBrushProperties;
	}

	//
	// PixelFormat
	// 
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_PIXEL_FORMAT
	PixelFormat(
		GL2D_GL_FORMAT format = GL2D_GL_FORMAT_RGBA,
		GL2D_GL_INTERNAL internal = GL2D_GL_INTERNAL_RGBA8,
		GL2D_GL_TYPE type = GL2D_GL_TYPE_BYTE
		)
	{
		GL2D_PIXEL_FORMAT pixelFormat;

		pixelFormat.format = format;
		pixelFormat.internal = internal;
		pixelFormat.type = type;

		return pixelFormat;
	}

	//
	// Bitmaps
	// 
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_BITMAP_PROPERTIES
	BitmapProperties(
		const GL2D_PIXEL_FORMAT &pixelFormat = GL2D::PixelFormat(),
		float dpiX = 96.0f,
		float dpiY = 96.0f
		)
	{
		GL2D_BITMAP_PROPERTIES bitmapProperties;

		bitmapProperties.pixelFormat = pixelFormat;
		bitmapProperties.dpiX = dpiX;
		bitmapProperties.dpiY = dpiY;

		return bitmapProperties;
	}

	//
	// Render Targets
	// 
	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_RENDER_TARGET_PROPERTIES
	RenderTargetProperties(
		GL2D_RENDER_TARGET_TYPE type =  GL2D_RENDER_TARGET_TYPE_DEFAULT,
		const GL2D_PIXEL_FORMAT &pixelFormat = GL2D::PixelFormat(),
		float dpiX = 0.0,
		float dpiY = 0.0,
		GL2D_RENDER_TARGET_USAGE usage = GL2D_RENDER_TARGET_USAGE_NONE,
		GL2D_FEATURE_LEVEL  minLevel = GL2D_FEATURE_LEVEL_DEFAULT
		)
	{
		GL2D_RENDER_TARGET_PROPERTIES renderTargetProperties;

		renderTargetProperties.type = type;
		renderTargetProperties.pixelFormat = pixelFormat;
		renderTargetProperties.dpiX = dpiX;
		renderTargetProperties.dpiY = dpiY;
		renderTargetProperties.usage = usage;
		renderTargetProperties.minLevel = minLevel;

		return renderTargetProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_HWND_RENDER_TARGET_PROPERTIES
	HwndRenderTargetProperties(
		HWND hwnd,
		GL2D_SIZE_U pixelSize = GL2D::Size( static_cast< uint32_t >( 0 ), static_cast< uint32_t >( 0 ) ),
		GL2D_PRESENT_OPTIONS presentOptions = GL2D_PRESENT_OPTIONS_NONE
		)
	{
		GL2D_HWND_RENDER_TARGET_PROPERTIES hwndRenderTargetProperties;

		hwndRenderTargetProperties.hwnd = hwnd;
		hwndRenderTargetProperties.pixelSize = pixelSize;
		hwndRenderTargetProperties.presentOptions = presentOptions;

		return hwndRenderTargetProperties;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_LAYER_PARAMETERS
	LayerParameters(
		const GL2D_RECT_F &contentBounds = GL2D::InfiniteRect(),
		IGL2DGeometry *geometricMask = NULL,
		GL2D_ANTIALIAS_MODE maskAntialiasMode = GL2D_ANTIALIAS_MODE_PER_PRIMITIVE,
		GL2D_MATRIX_3X2_F maskTransform = GL2D::IdentityMatrix(),
		float opacity = 1.0,
		IGL2DBrush *opacityBrush = NULL,
		GL2D_LAYER_OPTIONS layerOptions = GL2D_LAYER_OPTIONS_NONE
		)
	{
		GL2D_LAYER_PARAMETERS layerParameters = { 0 };

		layerParameters.contentBounds = contentBounds;
		layerParameters.geometricMask = geometricMask;
		layerParameters.maskAntialiasMode = maskAntialiasMode;
		layerParameters.maskTransform = maskTransform;
		layerParameters.opacity = opacity;
		layerParameters.opacityBrush = opacityBrush;
		layerParameters.layerOptions = layerOptions;

		return layerParameters;
	}

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_DRAWING_STATE_DESCRIPTION
	DrawingStateDescription(
		GL2D_ANTIALIAS_MODE antialiasMode = GL2D_ANTIALIAS_MODE_PER_PRIMITIVE,
		GL2D_TEXT_ANTIALIAS_MODE textAntialiasMode = GL2D_TEXT_ANTIALIAS_MODE_DEFAULT,
		GL2D_TAG tag1 = 0,
		GL2D_TAG tag2 = 0,
		const GL2D_MATRIX_3X2_F &transform = GL2D::IdentityMatrix()
		)
	{
		GL2D_DRAWING_STATE_DESCRIPTION drawingStateDescription;

		drawingStateDescription.antialiasMode = antialiasMode;
		drawingStateDescription.textAntialiasMode = textAntialiasMode;
		drawingStateDescription.tag1 = tag1;
		drawingStateDescription.tag2 = tag2;
		drawingStateDescription.transform = transform;

		return drawingStateDescription;
	}

	//
	// Colors, this enum defines a set of predefined colors.
	//
	class ColorF : public GL2D_COLOR_F
	{
	public:

		enum Enum
		{
			AliceBlue = 0xF0F8FF,
			AntiqueWhite = 0xFAEBD7,
			Aqua = 0x00FFFF,
			Aquamarine = 0x7FFFD4,
			Azure = 0xF0FFFF,
			Beige = 0xF5F5DC,
			Bisque = 0xFFE4C4,
			Black = 0x000000,
			BlanchedAlmond = 0xFFEBCD,
			Blue = 0x0000FF,
			BlueViolet = 0x8A2BE2,
			Brown = 0xA52A2A,
			BurlyWood = 0xDEB887,
			CadetBlue = 0x5F9EA0,
			Chartreuse = 0x7FFF00,
			Chocolate = 0xD2691E,
			Coral = 0xFF7F50,
			CornflowerBlue = 0x6495ED,
			Cornsilk = 0xFFF8DC,
			Crimson = 0xDC143C,
			Cyan = 0x00FFFF,
			DarkBlue = 0x00008B,
			DarkCyan = 0x008B8B,
			DarkGoldenrod = 0xB8860B,
			DarkGray = 0xA9A9A9,
			DarkGreen = 0x006400,
			DarkKhaki = 0xBDB76B,
			DarkMagenta = 0x8B008B,
			DarkOliveGreen = 0x556B2F,
			DarkOrange = 0xFF8C00,
			DarkOrchid = 0x9932CC,
			DarkRed = 0x8B0000,
			DarkSalmon = 0xE9967A,
			DarkSeaGreen = 0x8FBC8F,
			DarkSlateBlue = 0x483D8B,
			DarkSlateGray = 0x2F4F4F,
			DarkTurquoise = 0x00CED1,
			DarkViolet = 0x9400D3,
			DeepPink = 0xFF1493,
			DeepSkyBlue = 0x00BFFF,
			DimGray = 0x696969,
			DodgerBlue = 0x1E90FF,
			Firebrick = 0xB22222,
			FloralWhite = 0xFFFAF0,
			ForestGreen = 0x228B22,
			Fuchsia = 0xFF00FF,
			Gainsboro = 0xDCDCDC,
			GhostWhite = 0xF8F8FF,
			Gold = 0xFFD700,
			Goldenrod = 0xDAA520,
			Gray = 0x808080,
			Green = 0x008000,
			GreenYellow = 0xADFF2F,
			Honeydew = 0xF0FFF0,
			HotPink = 0xFF69B4,
			IndianRed = 0xCD5C5C,
			Indigo = 0x4B0082,
			Ivory = 0xFFFFF0,
			Khaki = 0xF0E68C,
			Lavender = 0xE6E6FA,
			LavenderBlush = 0xFFF0F5,
			LawnGreen = 0x7CFC00,
			LemonChiffon = 0xFFFACD,
			LightBlue = 0xADD8E6,
			LightCoral = 0xF08080,
			LightCyan = 0xE0FFFF,
			LightGoldenrodYellow = 0xFAFAD2,
			LightGreen = 0x90EE90,
			LightGray = 0xD3D3D3,
			LightPink = 0xFFB6C1,
			LightSalmon = 0xFFA07A,
			LightSeaGreen = 0x20B2AA,
			LightSkyBlue = 0x87CEFA,
			LightSlateGray = 0x778899,
			LightSteelBlue = 0xB0C4DE,
			LightYellow = 0xFFFFE0,
			Lime = 0x00FF00,
			LimeGreen = 0x32CD32,
			Linen = 0xFAF0E6,
			Magenta = 0xFF00FF,
			Maroon = 0x800000,
			MediumAquamarine = 0x66CDAA,
			MediumBlue = 0x0000CD,
			MediumOrchid = 0xBA55D3,
			MediumPurple = 0x9370DB,
			MediumSeaGreen = 0x3CB371,
			MediumSlateBlue = 0x7B68EE,
			MediumSpringGreen = 0x00FA9A,
			MediumTurquoise = 0x48D1CC,
			MediumVioletRed = 0xC71585,
			MidnightBlue = 0x191970,
			MintCream = 0xF5FFFA,
			MistyRose = 0xFFE4E1,
			Moccasin = 0xFFE4B5,
			NavajoWhite = 0xFFDEAD,
			Navy = 0x000080,
			OldLace = 0xFDF5E6,
			Olive = 0x808000,
			OliveDrab = 0x6B8E23,
			Orange = 0xFFA500,
			OrangeRed = 0xFF4500,
			Orchid = 0xDA70D6,
			PaleGoldenrod = 0xEEE8AA,
			PaleGreen = 0x98FB98,
			PaleTurquoise = 0xAFEEEE,
			PaleVioletRed = 0xDB7093,
			PapayaWhip = 0xFFEFD5,
			PeachPuff = 0xFFDAB9,
			Peru = 0xCD853F,
			Pink = 0xFFC0CB,
			Plum = 0xDDA0DD,
			PowderBlue = 0xB0E0E6,
			Purple = 0x800080,
			Red = 0xFF0000,
			RosyBrown = 0xBC8F8F,
			RoyalBlue = 0x4169E1,
			SaddleBrown = 0x8B4513,
			Salmon = 0xFA8072,
			SandyBrown = 0xF4A460,
			SeaGreen = 0x2E8B57,
			SeaShell = 0xFFF5EE,
			Sienna = 0xA0522D,
			Silver = 0xC0C0C0,
			SkyBlue = 0x87CEEB,
			SlateBlue = 0x6A5ACD,
			SlateGray = 0x708090,
			Snow = 0xFFFAFA,
			SpringGreen = 0x00FF7F,
			SteelBlue = 0x4682B4,
			Tan = 0xD2B48C,
			Teal = 0x008080,
			Thistle = 0xD8BFD8,
			Tomato = 0xFF6347,
			Turquoise = 0x40E0D0,
			Violet = 0xEE82EE,
			Wheat = 0xF5DEB3,
			White = 0xFFFFFF,
			WhiteSmoke = 0xF5F5F5,
			Yellow = 0xFFFF00,
			YellowGreen = 0x9ACD32,
		};

		//
		// Construct a color, note that the alpha value from the "rgb" component
		// is never used.
		// 
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		ColorF(
			uint32_t rgb,
			float a = 1.0
			)
		{
			Init(rgb, a);
		}

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		ColorF(
			Enum knownColor,
			float a = 1.0
			)
		{
			Init(knownColor, a);
		}

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		ColorF(
			float r,
			float g,
			float b,
			float a = 1.0
			)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

	private:

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		void
		Init(
			uint32_t rgb,
			float a
			)
		{
			this->r = static_cast<float>((rgb & sc_redMask) >> sc_redShift) / 255.f;
			this->g = static_cast<float>((rgb & sc_greenMask) >> sc_greenShift) / 255.f;
			this->b = static_cast<float>((rgb & sc_blueMask) >> sc_blueShift) / 255.f;
			this->a = a;
		}

		static const uint32_t sc_redShift   = 16;
		static const uint32_t sc_greenShift = 8;
		static const uint32_t sc_blueShift  = 0;

		static const uint32_t sc_redMask = 0xff << sc_redShift;
		static const uint32_t sc_greenMask = 0xff << sc_greenShift;
		static const uint32_t sc_blueMask = 0xff << sc_blueShift;
	};

	class Matrix3x2F : public GL2D_MATRIX_3X2_F
	{
	public:

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F(
			float _11,
			float _12,
			float _21,
			float _22,
			float _31,
			float _32
			)
		{
			this->_11 = _11;
			this->_12 = _12;
			this->_21 = _21;
			this->_22 = _22;
			this->_31 = _31;
			this->_32 = _32;
		}

		//
		// Creates an identity matrix
		// 
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F(
			)
		{
		}

		//
		// Named quasi-constructors
		//
		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Identity()
		{
			Matrix3x2F identity;

			identity._11 = 1.f;
			identity._12 = 0.f;
			identity._21 = 0.f;
			identity._22 = 1.f;
			identity._31 = 0.f;
			identity._32 = 0.f;

			return identity;
		}

		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Translation(
			GL2D_SIZE_F size
			)
		{
			Matrix3x2F translation;

			translation._11 = 1.0; translation._12 = 0.0;
			translation._21 = 0.0; translation._22 = 1.0;
			translation._31 = size.width; translation._32 = size.height;

			return translation;
		}

		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Translation(
			float x,
			float y
			)
		{
			return Translation(SizeF(x, y));
		}


		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Scale(
			GL2D_SIZE_F size,
			GL2D_POINT_2F center = GL2D::Point2F()
			)
		{
			Matrix3x2F scale;

			scale._11 = size.width; scale._12 = 0.0;
			scale._21 = 0.0; scale._22 = size.height;
			scale._31 = center.x - size.width * center.x;
			scale._32 = center.y - size.height * center.y;

			return scale;
		}

		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Scale(
			float x,
			float y,
			GL2D_POINT_2F center = GL2D::Point2F()
			)
		{
			return Scale(SizeF(x, y), center);
		}

		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Rotation(
			float angle,
			GL2D_POINT_2F center = GL2D::Point2F()
			)
		{
			Matrix3x2F rotation;

			GL2DMakeRotateMatrix(angle, center, &rotation);

			return rotation;
		}

		static
		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		Skew(
			float angleX,
			float angleY,
			GL2D_POINT_2F center = GL2D::Point2F()
			)
		{
			Matrix3x2F skew;

			GL2DMakeSkewMatrix(angleX, angleY, center, &skew);

			return skew;
		}

		//
		// Functions for convertion from the base GL2D_MATRIX_3X2_F to this type
		// without making a copy
		//
		static
		COM_DECLSPEC_NOTHROW
		inline
		const Matrix3x2F*
		ReinterpretBaseType(const GL2D_MATRIX_3X2_F *pMatrix)
		{
			return static_cast<const Matrix3x2F *>(pMatrix);
		}

		static
		COM_DECLSPEC_NOTHROW
		inline
		Matrix3x2F*
		ReinterpretBaseType(GL2D_MATRIX_3X2_F *pMatrix)
		{
			return static_cast<Matrix3x2F *>(pMatrix);
		}

		COM_DECLSPEC_NOTHROW
		inline
		float
		Determinant() const
		{
			return (_11 * _22) - (_12 * _21);
		}

		COM_DECLSPEC_NOTHROW
		inline
		bool
		IsInvertible() const
		{
			return !!GL2DIsMatrixInvertible(this);
		}

		COM_DECLSPEC_NOTHROW
		inline
		bool
		Invert()
		{
			return !!GL2DInvertMatrix(this);
		}

		COM_DECLSPEC_NOTHROW
		inline
		bool
		IsIdentity() const
		{
			return     _11 == 1.f && _12 == 0.f
					&& _21 == 0.f && _22 == 1.f
					&& _31 == 0.f && _32 == 0.f;
		}

		COM_DECLSPEC_NOTHROW
		inline
		void SetProduct(
			const Matrix3x2F &a,
			const Matrix3x2F &b
			)
		{
			_11 = a._11 * b._11 + a._12 * b._21;
			_12 = a._11 * b._12 + a._12 * b._22;
			_21 = a._21 * b._11 + a._22 * b._21;
			_22 = a._21 * b._12 + a._22 * b._22;
			_31 = a._31 * b._11 + a._32 * b._21 + b._31;
			_32 = a._31 * b._12 + a._32 * b._22 + b._32;
		}

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		Matrix3x2F
		operator*(
			const Matrix3x2F &matrix
			) const
		{
			Matrix3x2F result;

			result.SetProduct(*this, matrix);

			return result;
		}

		COM_DECLSPEC_NOTHROW
		GL2DFORCEINLINE
		GL2D_POINT_2F
		TransformPoint(
			GL2D_POINT_2F point
			) const
		{
			GL2D_POINT_2F result =
			{
				point.x * _11 + point.y * _21 + _31,
				point.x * _12 + point.y * _22 + _32
			};

			return result;
		}
	};

	COM_DECLSPEC_NOTHROW
	GL2DFORCEINLINE
	GL2D_POINT_2F
	operator*(
		const GL2D_POINT_2F &point,
		const GL2D_MATRIX_3X2_F &matrix
		)
	{
		return Matrix3x2F::ReinterpretBaseType(&matrix)->TransformPoint(point);
	}

	COM_DECLSPEC_NOTHROW
	GL2D_MATRIX_3X2_F
	IdentityMatrix()
	{
		return Matrix3x2F::Identity();
	}

} // namespace GL2D

COM_DECLSPEC_NOTHROW
GL2DFORCEINLINE
GL2D_MATRIX_3X2_F
operator*(
	const GL2D_MATRIX_3X2_F &matrix1,
	const GL2D_MATRIX_3X2_F &matrix2
	)
{
	return
		(*GL2D::Matrix3x2F::ReinterpretBaseType(&matrix1)) *
		(*GL2D::Matrix3x2F::ReinterpretBaseType(&matrix2));
}

COM_DECLSPEC_NOTHROW
inline
bool
operator==(const GL2D_SIZE_U &size1, const GL2D_SIZE_U &size2)
{
	return (size1.width == size2.width) && (size1.height == size2.height);
}

COM_DECLSPEC_NOTHROW
inline
bool
operator==(const GL2D_RECT_U &rect1, const GL2D_RECT_U &rect2)
{
	return (rect1.left  == rect2.left)  && (rect1.top     == rect2.top) &&
			(rect1.right == rect2.right) && (rect1.bottom  == rect2.bottom);
}

#endif // #ifndef _GL2D_HELPER_H_