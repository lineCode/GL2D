#ifndef ___OGL2D_DISPATCH_H___
#define ___OGL2D_DISPATCH_H___

#include "OpenGL2DPrerequisites.h"

namespace GL2D
{
	template< typename Object, const GUID * Clsid >
	class CUnknown
        : public Object
	{
	public:
		GL2D_API CUnknown()
			: m_llRefCount( 0 )
		{
			AddRef();
		}

		GL2D_API virtual ~CUnknown()
		{
		}

		GL2D_API virtual HRESULT STDMETHODCALLTYPE QueryInterface( const IID & riid, void ** ppv )
		{
			HRESULT hr = E_POINTER;

			if ( ppv )
			{
				if ( ( riid == IID_IUnknown ) || ( riid == *Clsid ) )
				{
					*ppv = this;
					AddRef(); 
					hr = S_OK;
				}
				else
				{
					hr = E_NOINTERFACE;
					*ppv = NULL; 
				}
			}

			return hr;
		}

		GL2D_API virtual ULONG STDMETHODCALLTYPE AddRef( void )
		{
			m_llRefCount++;
			return m_llRefCount;
		}

		GL2D_API virtual ULONG STDMETHODCALLTYPE Release( void )
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