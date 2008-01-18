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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../BaseObject.h"
#include "../Utilities.h"

#include "Device.h"
#include "VertexShader.h"
#include "ConstantTable.h"

namespace SlimDX
{
namespace Direct3D9
{
	VertexShader::VertexShader( IDirect3DVertexShader9* vertexShader )
	{
		if( vertexShader == NULL )
			throw gcnew ArgumentNullException( "vertexShader" );

		Construct(vertexShader);

		m_ConstantTable = nullptr;
	}

	VertexShader::VertexShader( IntPtr vertexShader )
	{
		Construct( vertexShader, NativeInterface );
	}

	VertexShader::VertexShader( IDirect3DVertexShader9* vertexShader, ID3DXConstantTable* constantTable )
	{
		if( vertexShader == NULL )
			throw gcnew ArgumentNullException( "vertexShader" );
		if( constantTable == NULL )
			throw gcnew ArgumentNullException( "constantTable" );

		Construct(vertexShader);

		IDirect3DDevice9* device;
		HRESULT hr = vertexShader->GetDevice(&device);
		GraphicsException::CheckHResult( hr );
		
		m_ConstantTable = gcnew ConstantTable( device, constantTable );
		device->Release();
	}

	VertexShader^ VertexShader::FromString( Device^ device, String^ sourceCode, String^ entryPoint, String^ profile, ShaderFlags flags, [Out] String^ %compilationErrors )
	{
		array<unsigned char>^ rawCode = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceCode );
		pin_ptr<unsigned char> pinnedCode = &rawCode[0];
		array<Byte>^ rawFunction = System::Text::ASCIIEncoding::ASCII->GetBytes( entryPoint );
		pin_ptr<unsigned char> pinnedFunction = &rawFunction[0];
		array<Byte>^ rawProfile = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &rawProfile[0];
		
		ID3DXBuffer *shaderBuffer;
		ID3DXBuffer *errorBuffer;
		ID3DXConstantTable* constantTable;
		
		HRESULT hr = D3DXCompileShader( reinterpret_cast<const char*>( pinnedCode ), rawCode->Length, NULL, NULL,
			reinterpret_cast<const char*>( pinnedFunction ), reinterpret_cast<const char*>( pinnedProfile ),
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, &constantTable );
		
		if( errorBuffer != NULL )
		{
			compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBuffer->GetBufferPointer() ) );
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		// CheckHResult() is not used because we need to include the compiler errors.
		if( Configuration::EnableExceptions && FAILED(hr) )
		{
			GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );
		
		IDirect3DVertexShader9 *vertexShader;
		device->InternalPointer->CreateVertexShader( reinterpret_cast<const DWORD*>( shaderBuffer->GetBufferPointer() ), &vertexShader );
		if( vertexShader == NULL)
			return nullptr;
		return gcnew VertexShader( vertexShader, constantTable );
	}

	void VertexShader::RetrieveConstantTable()
	{
		if( m_ConstantTable != nullptr )
			return;

		//Retrieve the binary data
		UINT size;
		HRESULT hr = InternalPointer->GetFunction( NULL, &size );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return;

		std::auto_ptr<char> data( new char[size] );
		hr = InternalPointer->GetFunction( data.get(), &size );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return;

		//Ask D3DX to give us the actual table
		ID3DXConstantTable* constantTable;
		hr = D3DXGetShaderConstantTable( reinterpret_cast<const DWORD*>( data.get() ), &constantTable );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return;

		m_ConstantTable = gcnew ConstantTable( constantTable );
	}
}
}