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
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"

#include "EffectCompiler.h"

namespace SlimDX
{
namespace Direct3D9
{
	EffectCompiler::EffectCompiler( ID3DXEffectCompiler* compiler ) : BaseEffect( compiler )
	{
		if( compiler == NULL )
			throw gcnew ArgumentNullException( "compiler" );

		m_Pointer = compiler;
	}

	EffectCompiler::EffectCompiler( IntPtr compiler )
	{
		if( compiler == IntPtr::Zero )
			throw gcnew ArgumentNullException( "compiler" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( compiler.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXEffectCompiler, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXEffectCompiler*>( pointer );
	}

	EffectCompiler::EffectCompiler( String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		InitThis( System::Text::ASCIIEncoding::ASCII->GetBytes( data ), defines, includeFile, flags, errors );
	}

	EffectCompiler::EffectCompiler( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		InitThis( data, defines, includeFile, flags, errors );
	}

	void EffectCompiler::InitThis( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;
		pin_ptr<Byte> pinnedData = &data[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCreateEffectCompiler( (LPCSTR) pinnedData, data->Length, macros, includePtr,
			(DWORD) flags, &compiler, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", errors );
		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = compiler;
	}

	EffectCompiler^ EffectCompiler::FromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCreateEffectCompilerFromFile( (LPCTSTR) pinnedFile, macros, includePtr,
			(DWORD) flags, &compiler, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", errors );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew EffectCompiler( compiler );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
		[Out] String^% compilationErrors, [Out] ConstantTable^% constantTable )
	{
		D3DXHANDLE handle = functionHandle != nullptr ? functionHandle->InternalHandle : NULL;
		array<Byte>^ targetBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( target );
		pin_ptr<unsigned char> pinnedTarget = &targetBytes[0];

		ID3DXBuffer* errorBuffer;
		ID3DXBuffer* shader;
		ID3DXConstantTable* table;

		HRESULT hr = CompilerPointer->CompileShader( handle, (LPCSTR) pinnedTarget, (DWORD) flags, &shader, &errorBuffer, &table );

		//marshal errors if necessary
		compilationErrors = BufferWrapper::ConvertToString( errorBuffer );
			
		// CheckHResult() is not used because we need to include the compiler errors.
		if( DirectXException::EnableExceptions && FAILED(hr) )
		{
			GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		constantTable = gcnew ConstantTable( table );
		return gcnew ShaderBytecode( shader );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
		[Out] String^% compilationErrors )
	{
		D3DXHANDLE handle = functionHandle != nullptr ? functionHandle->InternalHandle : NULL;
		array<Byte>^ targetBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( target );
		pin_ptr<unsigned char> pinnedTarget = &targetBytes[0];

		ID3DXBuffer* errorBuffer;
		ID3DXBuffer* shader;

		HRESULT hr = CompilerPointer->CompileShader( handle, (LPCSTR) pinnedTarget, (DWORD) flags, &shader, &errorBuffer, NULL );

		//marshal errors if necessary
		if( errorBuffer != NULL )
		{
			compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
		}
		else
		{
			compilationErrors = String::Empty;
		}
			
		// CheckHResult() is not used because we need to include the compiler errors.
		if( DirectXException::EnableExceptions && FAILED(hr) )
		{
			GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderBytecode( shader );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags )
	{
		String^ errors;
		return CompileShader( functionHandle, target, flags, errors );
	}

	EffectBytecode^ EffectCompiler::CompileEffect( ShaderFlags flags, [Out] String^% compilationErrors )
	{
		ID3DXBuffer* effect;
		ID3DXBuffer* errorBuffer;

		HRESULT hr = CompilerPointer->CompileEffect( (DWORD) flags, &effect, &errorBuffer );

		//marshal errors if necessary
		if( errorBuffer != NULL )
		{
			compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		// CheckHResult() is not used because we need to include the compiler errors.
		if( DirectXException::EnableExceptions && FAILED(hr) )
		{
			GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		return gcnew EffectBytecode( effect );
	}

	EffectBytecode^ EffectCompiler::CompileEffect( ShaderFlags flags )
	{
		String^ errors;
		return CompileEffect( flags, errors );
	}

	void EffectCompiler::SetLiteral( EffectHandle^ handle, bool literal )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		HRESULT hr = CompilerPointer->SetLiteral( nativeHandle, literal );
		GraphicsException::CheckHResult( hr );
	}

	bool EffectCompiler::GetLiteral( EffectHandle^ handle )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		BOOL literal = false;
		HRESULT hr = CompilerPointer->GetLiteral( nativeHandle, &literal );
		GraphicsException::CheckHResult( hr );
		
		return literal > 0;
	}
}
}