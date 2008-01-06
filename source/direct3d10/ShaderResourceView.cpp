/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <d3d10.h>
#include <d3dx10.h>

#include "GraphicsException.h"

#include "ShaderResourceView.h"
#include "Device.h"
#include "Resource.h"
#include "Texture1D.h"
#include "Texture2D.h"
#include "Texture3D.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	ShaderResourceView::ShaderResourceView( ID3D10ShaderResourceView* view ) : ResourceView( view )
	{
	}

	ShaderResourceView::ShaderResourceView( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10ShaderResourceView, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3D10ShaderResourceView*>( result );
	}
	
	ShaderResourceView::ShaderResourceView( Device^ device, Texture1D^ resource )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( resource == nullptr )
			throw gcnew ArgumentNullException( "resource" );
		
		D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
		ZeroMemory( &viewDesc, sizeof( viewDesc ) );
		viewDesc.Format = static_cast<DXGI_FORMAT>( resource->Format );
	    Format = resource->Format;
		viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE1D;
		Dimension = ResourceViewDimension::Texture1D;
		viewDesc.Texture2D.MipLevels = resource->MipLevels;
		
		ID3D10ShaderResourceView *view;
		HRESULT hr = device->DevicePointer->CreateShaderResourceView( resource->InternalPointer, &viewDesc, &view );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = view;
	}

	ShaderResourceView::ShaderResourceView( Device^ device, Texture2D^ resource )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( resource == nullptr )
			throw gcnew ArgumentNullException( "resource" );
		
		D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
		ZeroMemory( &viewDesc, sizeof( viewDesc ) );
		viewDesc.Format = static_cast<DXGI_FORMAT>( resource->Format );
	    Format = resource->Format;
		viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		Dimension = ResourceViewDimension::Texture2D;
		viewDesc.Texture2D.MipLevels = resource->MipLevels;
		
		ID3D10ShaderResourceView *view;
		HRESULT hr = device->DevicePointer->CreateShaderResourceView( resource->InternalPointer, &viewDesc, &view );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = view;
	}

	ShaderResourceView::ShaderResourceView( Device^ device, Texture3D^ resource )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( resource == nullptr )
			throw gcnew ArgumentNullException( "resource" );
		
		D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
		ZeroMemory( &viewDesc, sizeof( viewDesc ) );
		viewDesc.Format = static_cast<DXGI_FORMAT>( resource->Format );
	    Format = resource->Format;
		viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE3D;
		Dimension = ResourceViewDimension::Texture3D;
		viewDesc.Texture3D.MipLevels = resource->MipLevels;
		
		ID3D10ShaderResourceView *view;
		HRESULT hr = device->DevicePointer->CreateShaderResourceView( resource->InternalPointer, &viewDesc, &view );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = view;
	}
}
}
