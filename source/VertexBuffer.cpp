#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
#include "VertexBuffer.h"
#include "Utils.h"

namespace SlimDX
{
namespace Direct3D
{
	VertexBuffer::VertexBuffer( IDirect3DVertexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		m_Buffer = buffer;
		m_Disposed = false;
	}

	VertexBuffer::VertexBuffer( Device^ device, int sizeBytes, Usage usage, VertexFormats format, Pool pool )
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = device->InternalPointer->CreateVertexBuffer( sizeBytes, (DWORD) usage, 
			(DWORD) format, (D3DPOOL) pool, &vb, NULL );
		FAILED_THROW( hr );
		
		m_Buffer = vb;
		m_Disposed = false;
	}

	VertexBuffer::~VertexBuffer()
	{
		Utils::MarkDisposed( m_Disposed, this );
		GC::SuppressFinalize( this );

		m_Buffer->Release();
		m_Buffer = NULL;
	}

	VertexBuffer::!VertexBuffer()
	{
		Utils::ReportNotDisposed( this );
	}

	generic<typename T>
	GraphicsStream<T>^ VertexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = m_Buffer->Lock( offset, size, &lockedPtr, (DWORD) flags );
		FAILED_THROW( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream<T>^ stream = gcnew GraphicsStream<T>( lockedPtr, true, !readOnly );
		return stream;
	}

	void VertexBuffer::Unlock()
	{
		m_Buffer->Unlock();
	}
}
}
