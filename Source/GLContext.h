#ifndef ___GL2D_CONTEXT_H___
#define ___GL2D_CONTEXT_H___

#include "OpenGL2DPrerequisites.h"

#include <map>
#include <thread>
#include <mutex>

namespace GL2D
{
	/*!
	\author 	Sylvain DOREMUS
	\brief		Gère un contexte OpenGL
	*/
	class CContext
	{
	public:
		/** Constructeur
		@param window
			L'identifcateur de la fenêtre, peut être nul, à ce moment le contexte est initiélisé avec la fenêtre du bureau
		*/
		CContext( HWND window = NULL );

		/** Destructeur
		*/
		~CContext();
		
		HRESULT MakeCurrent();
		HRESULT EndCurrent();
		HWND GetWindow()const;

		int GetInt( GLenum param );

		HRESULT GenFramebuffers( GLsizei n, GLuint* framebuffers );
		HRESULT DeleteFramebuffers( GLsizei n, GLuint const * framebuffers );
		HRESULT BindFramebuffer( GL2D_GL_FRAMEBUFFER_MODE target, uint32_t framebuffer );
		uint32_t CheckFramebufferStatus( uint32_t target );
		HRESULT FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level );
		HRESULT FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		HRESULT FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		HRESULT FramebufferTextureLayer( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer );
		HRESULT FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		HRESULT BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
		HRESULT DrawBuffers( int n, uint32_t const * bufs );
		HRESULT GenTextures( GLsizei n, GLuint* textures  );
		HRESULT DeleteTextures( GLsizei n, GLuint const * textures  );
		HRESULT ActiveTexture( uint32_t texture );
		HRESULT FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId );
		HRESULT GenRenderbuffers( GLsizei n, GLuint * ids );
		HRESULT DeleteRenderbuffers( GLsizei n, GLuint const * ids );
		HRESULT BindRenderbuffer( uint32_t target, uint32_t id );
		HRESULT RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height );
		HRESULT RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height );
		HRESULT TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
		HRESULT GetRenderbufferParameteriv( uint32_t target, uint32_t param, int* value );
		HRESULT GenBuffers( GLsizei n, GLuint* buffers );
		HRESULT DeleteBuffers( GLsizei n, GLuint const * buffers );
		HRESULT BindBuffer( GL2D_GL_BUFFER_TARGET target, uint32_t buffer );
		HRESULT BufferData( GL2D_GL_BUFFER_TARGET target, ptrdiff_t size, const GLvoid * data, GL2D_GL_BUFFER_USAGE usage );
		
		HRESULT DrawTexture( GLuint name, const GL2D_RECT_F & destinationRectangle, GL2D_BITMAP_INTERPOLATION_MODE interpolationMode, const GL2D_RECT_F & sourceRectangle );

	private:
		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef char GLchar;

		HWND m_window;
		HDC m_dc;
		HGLRC m_context;
		CContext * m_previous;
		GLuint m_buffer;
		GLuint m_program;
		GLuint m_sampler;
		GLuint m_vertex;
		GLuint m_texture;

		static std::recursive_mutex m_mutex;
		static std::map< std::thread::id, CContext * > m_activeContexts;

		/**@name FBO */
		//@{

		std::function< void ( GLsizei n, GLuint* framebuffers ) > m_pfnGenFramebuffers;
		std::function< void ( GLsizei n, GLuint const * framebuffers ) > m_pfnDeleteFramebuffers;
		std::function< void ( GLenum target, GLuint framebuffer ) > m_pfnBindFramebuffer;
		std::function< uint32_t ( GLenum target ) > m_pfnCheckFramebufferStatus;
		std::function< void ( GLenum target, uint32_t attachment, uint32_t texture, int level ) > m_pfnFramebufferTexture;
		std::function< void ( GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level ) > m_pfnFramebufferTexture1D;
		std::function< void ( GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level ) > m_pfnFramebufferTexture2D;
		std::function< void ( GLenum target,uint32_t attachment, uint32_t texture,int level,int layer ) > m_pfnFramebufferTextureLayer;
#if DEF_HAS_VARIADIC_TEMPLATES
		std::function< void ( GLenum target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer ) > m_pfnFramebufferTexture3D;
		std::function< void ( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter ) > m_pfnBlitFramebuffer;
#else
		void ( CALLBACK * m_pfnFramebufferTexture3D )( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		void ( CALLBACK * m_pfnBlitFramebuffer )( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
#endif
		std::function< void ( int n, GLenum const * bufs ) > m_pfnDrawBuffers;

		//@}
		/**@name Textures */
		//@{

		std::function< void ( GLsizei n, GLuint* textures  ) > m_pfnGenTextures;
		std::function< void ( GLsizei n, GLuint const * textures  ) > m_pfnDeleteTextures;
		std::function< void ( GLenum texture ) > m_pfnActiveTexture;

		//@}
		/**@name RBO */
		//@{

		std::function< void ( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId ) > m_pfnFramebufferRenderbuffer;
		std::function< void ( GLsizei n, GLuint * ids ) > m_pfnGenRenderbuffers;
		std::function< void ( GLsizei n, GLuint const * ids ) > m_pfnDeleteRenderbuffers;
		std::function< void ( uint32_t target, uint32_t id ) > m_pfnBindRenderbuffer;
		std::function< void ( uint32_t target, uint32_t internalFormat, int width, int height ) > m_pfnRenderbufferStorage;
		std::function< void ( uint32_t target, int isamples, uint32_t internalFormat, int width, int height ) > m_pfnRenderbufferStorageMultisample;
#if DEF_HAS_VARIADIC_TEMPLATES
		std::function< void ( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations ) > m_pfnTexImage2DMultisample;
#else
		void ( CALLBACK * m_pfnTexImage2DMultisample )( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
#endif
		std::function< void ( uint32_t target, uint32_t param, int* value ) > m_pfnGetRenderbufferParameteriv;

		//@}
		/**@name VBO */
		//@{

		std::function< void ( GLsizei n, GLuint * buffers ) > m_pfnGenBuffers;
		std::function< void ( GLsizei n, GLuint const * buffers ) > m_pfnDeleteBuffers;
		std::function< void ( GLenum target, GLuint buffer  ) > m_pfnBindBuffer;
		std::function< void ( GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage ) > m_pfnBufferData;
		std::function< void ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer ) > m_pfnVertexAttribPointer;
		
		//@}
		/**@name Shader */
		//@{
		
		std::function< GLuint ( GLenum type ) > m_pfnCreateShader;
		std::function< void ( GLuint name ) > m_pfnDeleteShader;
		std::function< void ( GLuint shader, GLsizei count, const GLchar ** string, const GLint * length ) > m_pfnShaderSource;
		std::function< void ( GLuint shader ) > m_pfnCompileShader;
		std::function< void ( GLuint shader, GLenum pname, GLint * params ) > m_pfnGetShaderiv;
		std::function< void ( GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog ) > m_pfnGetShaderInfoLog;
		std::function< GLuint () > m_pfnCreateProgram;
		std::function< void ( GLuint name ) > m_pfnDeleteProgram;
		std::function< void ( GLuint program, GLuint shader) > m_pfnAttachShader;
		std::function< void ( GLuint program ) > m_pfnLinkProgram;
		std::function< void ( GLuint program, GLenum pname, GLint * params ) > m_pfnGetProgramiv;
		std::function< void ( GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog ) > m_pfnGetProgramInfoLog;
		std::function< GLint ( GLuint program, const GLchar * name ) > m_pfnGetUniformLocation;
		std::function< void ( GLint location, GLint v0 ) > m_pfnUniform1i;
		std::function< GLint ( GLuint program, const GLchar * name ) > m_pfnGetAttribLocation;
		std::function< GLint ( GLuint program ) > m_pfnUseProgram;

		//@}
		
		HGLRC DoCreateContext();
		bool DoSelectPixelFormat();
		void DoCleanup();
		GLuint DoCreateShader( const std::string & source, GL2D_GL_SHADER_TYPE type );
	};
}

#endif
