#ifndef ___GL2D_CONTEXT_H___
#define ___GL2D_CONTEXT_H___

#include "OpenGL2DPrerequisites.h"

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
		
		void MakeCurrent();
		void EndCurrent();
		HWND GetWindow()const;

		void GenFramebuffers( GLsizei n, GLuint* framebuffers );
		void DeleteFramebuffers( GLsizei n, GLuint const * framebuffers );
		void BindFramebuffer( uint32_t target, GL2D_GL_FRAMEBUFFER_MODE framebuffer );
		uint32_t CheckFramebufferStatus( uint32_t target );
		void FramebufferTexture( uint32_t target, uint32_t attachment, uint32_t texture, int level );
		void FramebufferTexture1D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		void FramebufferTexture2D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level );
		void FramebufferTextureLayer( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer );
		void FramebufferTexture3D( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		void BlitFramebuffer( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
		void DrawBuffers( int n, uint32_t const * bufs );
		void GenTextures( GLsizei n, GLuint* textures  );
		void DeleteTextures( GLsizei n, GLuint const * textures  );
		void ActiveTexture( uint32_t texture );
		void FramebufferRenderbuffer( uint32_t target, uint32_t attachmentPoint, uint32_t renderbufferTarget, uint32_t renderbufferId );
		void GenRenderbuffers( GLsizei n, GLuint * ids );
		void DeleteRenderbuffers( GLsizei n, GLuint const * ids );
		void BindRenderbuffer( uint32_t target, uint32_t id );
		void RenderbufferStorage( uint32_t target, uint32_t internalFormat, int width, int height );
		void RenderbufferStorageMultisample( uint32_t target, int isamples, uint32_t internalFormat, int width, int height );
		void TexImage2DMultisample( uint32_t target, int samples, int internalformat, int width, int height, uint8_t fixedsamplelocations );
		void GetRenderbufferParameteriv( uint32_t target, uint32_t param, int* value );

	private:
		HGLRC DoCreateContext();
		bool DoSelectPixelFormat();

		HWND m_window;
		HDC m_dc;
		HGLRC m_context;
		/**@name FBO */
		//@{

		std::function< void ( GLsizei n, GLuint* framebuffers ) > m_pfnGenFramebuffers;
		std::function< void ( GLsizei n, GLuint const * framebuffers ) > m_pfnDeleteFramebuffers;
		std::function< void ( uint32_t target, GL2D_GL_FRAMEBUFFER_MODE framebuffer  ) > m_pfnBindFramebuffer;
		std::function< uint32_t ( uint32_t target ) > m_pfnCheckFramebufferStatus;
		std::function< void ( uint32_t target, uint32_t attachment, uint32_t texture, int level ) > m_pfnFramebufferTexture;
		std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level ) > m_pfnFramebufferTexture1D;
		std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level ) > m_pfnFramebufferTexture2D;
		std::function< void ( uint32_t target,uint32_t attachment, uint32_t texture,int level,int layer ) > m_pfnFramebufferTextureLayer;
#if DEF_HAS_VARIADIC_TEMPLATES
		std::function< void ( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer ) > m_pfnFramebufferTexture3D;
		std::function< void ( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter ) > m_pfnBlitFramebuffer;
#else
		void ( CALLBACK * m_pfnFramebufferTexture3D )( uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t texture, int level, int layer );
		void ( CALLBACK * m_pfnBlitFramebuffer )( int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, uint32_t mask, uint32_t filter );
#endif
		std::function< void ( int n, uint32_t const * bufs ) > m_pfnDrawBuffers;

		//@}
		/**@name FBO */
		//@{
		std::function< void ( GLsizei n, GLuint* textures  ) > m_pfnGenTextures;
		std::function< void ( GLsizei n, GLuint const * textures  ) > m_pfnDeleteTextures;

		//@}
		/**@name Texture */
		//@{

		std::function< void ( uint32_t texture ) > m_pfnActiveTexture;

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
	};
}

#endif
