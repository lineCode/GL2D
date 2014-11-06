#ifndef ___OGL2D_DISPATCH_H___
#define ___OGL2D_DISPATCH_H___

#include "OpenGL2DPrerequisites.h"

namespace GL2D
{
	template< typename Object, typename Interface >
	class CUnknown
		: public Interface
		, public Object
	{
	public:
		CUnknown()
			: m_llRefCount( 0 )
		{
			AddRef();
		}

		virtual ~CUnknown()
		{
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInterface( const IID & riid, void ** ppv )
		{
			if ( ( riid == IID_IUnknown ) || ( riid == __uuidof( Interface ) ) )
			{
				*ppv = this; 
			}
			else
			{
				*ppv = NULL; 
				return E_NOINTERFACE; 
			}

			AddRef(); 
			return S_OK;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef( void )
		{
			m_llRefCount++;
			return m_llRefCount;
		}

		virtual ULONG STDMETHODCALLTYPE Release( void )
		{
			m_llRefCount--;

			if ( !m_llRefCount )
			{
				delete this;
			}

			return m_llRefCount;
		}

	private:
		ULONG m_llRefCount;
	};
}

#endif