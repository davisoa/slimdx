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
#include <vcclr.h>

#include "../math/Math.h"
#include "../DataStream.h"
#include "Device.h"
#include "Texture.h"
#include "BaseEffect.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		BaseEffect::BaseEffect( IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, int index )
		{
			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = InternalPointer->GetAnnotation( parentHandle, index );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = InternalPointer->GetAnnotationByName( parentHandle, reinterpret_cast<LPCSTR>( pinnedName ) );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = InternalPointer->GetParameter( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = InternalPointer->GetParameterByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterBySemantic( EffectHandle^ parameter, String^ semantic )
		{
			array<Byte>^ semanticBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( semantic );
			pin_ptr<unsigned char> pinnedSemantic = &semanticBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = InternalPointer->GetParameterBySemantic( parentHandle, reinterpret_cast<const char*>( pinnedSemantic ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterElement( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = InternalPointer->GetParameterElement( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		ParameterDescription BaseEffect::GetParameterDescription( EffectHandle^ parameter )
		{
			D3DXPARAMETER_DESC description;

			HRESULT hr = InternalPointer->GetParameterDesc( parameter->InternalHandle, &description );
			Direct3D9ErrorHandler::TestForFailure( hr );

			ParameterDescription outDesc;
			outDesc.Name = gcnew String( description.Name );
			outDesc.Semantic = gcnew String( description.Semantic );
			outDesc.Class = static_cast<ParameterClass>( description.Class );
			outDesc.Type = static_cast<ParameterType>( description.Type );
			outDesc.Rows = description.Rows;
			outDesc.Columns = description.Columns;
			outDesc.Elements = description.Elements;
			outDesc.Annotations = description.Annotations;
			outDesc.StructMembers = description.StructMembers;
			outDesc.Flags = static_cast<ParameterFlags>( description.Flags );
			outDesc.Bytes = description.Bytes;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetFunction( int index )
		{
			D3DXHANDLE handle = InternalPointer->GetFunction( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetFunction( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE handle = InternalPointer->GetFunctionByName( reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		FunctionDescription BaseEffect::GetFunctionDescription( EffectHandle^ handle )
		{
			D3DXFUNCTION_DESC description;

			HRESULT hr = InternalPointer->GetFunctionDesc( handle->InternalHandle, &description );
			Direct3D9ErrorHandler::TestForFailure( hr );

			FunctionDescription outDesc;
			outDesc.Name = gcnew String( description.Name );
			outDesc.Annotations = description.Annotations;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetTechnique( int index )
		{
			D3DXHANDLE handle = InternalPointer->GetTechnique( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetTechnique( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE handle = InternalPointer->GetTechniqueByName( reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		TechniqueDescription BaseEffect::GetTechniqueDescription( EffectHandle^ handle )
		{
			D3DXTECHNIQUE_DESC description;

			HRESULT hr = InternalPointer->GetTechniqueDesc( handle->InternalHandle, &description );
			Direct3D9ErrorHandler::TestForFailure( hr );

			TechniqueDescription outDesc;
			outDesc.Name = gcnew String( description.Name );
			outDesc.Annotations = description.Annotations;
			outDesc.Passes = description.Passes;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, int index )
		{
			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE pass = InternalPointer->GetPass( nativeHandle, index );

			if( pass == NULL )
				return nullptr;
			return gcnew EffectHandle( pass );
		}

		EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE pass = InternalPointer->GetPassByName( nativeHandle, reinterpret_cast<const char*>( pinnedName ) );

			if( pass == NULL )
				return nullptr;
			return gcnew EffectHandle( pass );
		}

		PassDescription BaseEffect::GetPassDescription( EffectHandle^ handle )
		{
			D3DXPASS_DESC description;
			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;

			HRESULT hr = InternalPointer->GetPassDesc( nativeHandle, &description );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return PassDescription();

			PassDescription passDesc;
			passDesc.Name = gcnew String( description.Name );
			passDesc.Annotations = description.Annotations;
			passDesc.VertexShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( description.pVertexShaderFunction ) ) );
			passDesc.PixelShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( description.pPixelShaderFunction ) ) );

			return passDesc;
		}

		EffectDescription BaseEffect::Description::get()
		{
			D3DXEFFECT_DESC description;

			HRESULT hr = InternalPointer->GetDesc( &description );
			Direct3D9ErrorHandler::TestForFailure( hr );

			EffectDescription outDesc;
			outDesc.Creator = gcnew String( description.Creator );
			outDesc.Parameters = description.Parameters;
			outDesc.Techniques = description.Techniques;
			outDesc.Functions = description.Functions;

			return outDesc;
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, bool value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetBool( handle, value );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<bool>^ values )
		{
			//implementing set for bool array is REALLY ANNOYING.
			//Win32 uses BOOL, which is an int
			array<BOOL>^ expandedArray = gcnew array<BOOL>( values->Length );
			Array::Copy( values, expandedArray, values->Length );

			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<BOOL> pinnedValue = &expandedArray[0];
			HRESULT hr = InternalPointer->SetBoolArray( handle, pinnedValue, values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, int value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetInt( handle, value );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<int>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<int> pinnedValue = &values[0];
			HRESULT hr = InternalPointer->SetIntArray( handle, pinnedValue, values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, float value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetFloat( handle, value );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<float>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<float> pinnedValues = &values[0];
			HRESULT hr = InternalPointer->SetFloatArray( handle, pinnedValues, values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, Vector4 value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<Vector4>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<Vector4> pinnedValue = &values[0];
			HRESULT hr = InternalPointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinnedValue ), values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, ColorValue value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<ColorValue>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<ColorValue> pinnedValue = &values[0];
			HRESULT hr = InternalPointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinnedValue ), values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, Matrix value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetMatrix( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, array<Matrix>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<Matrix> pinnedValue = &values[0];
			HRESULT hr = InternalPointer->SetMatrixArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinnedValue ), values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, BaseTexture^ value )
		{
			IDirect3DBaseTexture9* texture = NULL;
			if( value != nullptr )
				texture = value->BaseTexturePointer;

			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetTexture( handle, texture );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ parameter, String^ value )
		{
			array<unsigned char>^ valueBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( value );
			pin_ptr<unsigned char> pinnedValue = &valueBytes[0];

			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetString( handle, reinterpret_cast<LPCSTR>( pinnedValue ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ parameter, Matrix value )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->SetMatrixTranspose( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ parameter, array<Matrix>^ values )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			pin_ptr<Matrix> pinnedValue = &values[0];
			HRESULT hr = InternalPointer->SetMatrixTransposeArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinnedValue ), values->Length );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		bool BaseEffect::GetBool( EffectHandle^ parameter )
		{
			BOOL value = FALSE;
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetBool( handle, &value );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value < 0;
		}

		array<bool>^ BaseEffect::GetBoolArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<BOOL>^ data = gcnew array<BOOL>( count );
			pin_ptr<BOOL> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetBoolArray( handle, pinnedData, count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

            //now we go from BOOL to bool
            array<bool>^ boolData = gcnew array<bool>( count );
            Array::Copy( data, boolData, count );
            return boolData;
		}

		int BaseEffect::GetInt( EffectHandle^ parameter )
		{
			int value = 0;
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetInt( handle, &value );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<int>^ BaseEffect::GetIntArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<int>^ data = gcnew array<int>( count );
			pin_ptr<int> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetIntArray( handle, pinnedData, count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		float BaseEffect::GetFloat( EffectHandle^ parameter )
		{
			float value = 0.0f;
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetFloat( handle, &value );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<float>^ BaseEffect::GetFloatArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<float>^ data = gcnew array<float>( count );
			pin_ptr<float> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetFloatArray( handle, pinnedData, count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		Vector4 BaseEffect::GetVector( EffectHandle^ parameter )
		{
			Vector4 value = Vector4();
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetVector( handle, reinterpret_cast<D3DXVECTOR4*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<Vector4>^ BaseEffect::GetVectorArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<Vector4>^ data = gcnew array<Vector4>( count );
			pin_ptr<Vector4> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetVectorArray( handle, reinterpret_cast<D3DXVECTOR4*>( pinnedData ), count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		ColorValue BaseEffect::GetColor( EffectHandle^ parameter )
		{
			ColorValue value = ColorValue();
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetVector( handle, reinterpret_cast<D3DXVECTOR4*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<ColorValue>^ BaseEffect::GetColorArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<ColorValue>^ data = gcnew array<ColorValue>( count );
			pin_ptr<ColorValue> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetVectorArray( handle, reinterpret_cast<D3DXVECTOR4*>( pinnedData ), count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		Matrix BaseEffect::GetMatrix( EffectHandle^ parameter )
		{
			Matrix value = Matrix();
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetMatrix( handle, reinterpret_cast<D3DXMATRIX*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<Matrix>^ BaseEffect::GetMatrixArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<Matrix>^ data = gcnew array<Matrix>( count );
			pin_ptr<Matrix> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetMatrixArray( handle, reinterpret_cast<D3DXMATRIX*>( pinnedData ), count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		BaseTexture^ BaseEffect::GetTexture( EffectHandle^ parameter )
		{
			IDirect3DBaseTexture9* texture = NULL;
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetTexture( handle, &texture );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			switch( texture->GetType() )
			{
			case D3DRTYPE_TEXTURE:
				return gcnew Texture( static_cast<IDirect3DTexture9*>( texture ) );
			case D3DRTYPE_VOLUMETEXTURE:
				return gcnew VolumeTexture( static_cast<IDirect3DVolumeTexture9*>( texture ) );
			case D3DRTYPE_CUBETEXTURE:
				return gcnew CubeTexture( static_cast<IDirect3DCubeTexture9*>( texture ) );

			default:
				return nullptr;
			}
		}

		Matrix BaseEffect::GetMatrixTranspose( EffectHandle^ parameter )
		{
			Matrix value = Matrix();
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			HRESULT hr = InternalPointer->GetMatrixTranspose( handle, reinterpret_cast<D3DXMATRIX*>( &value ) );
			Direct3D9ErrorHandler::TestForFailure( hr );

			return value;
		}

		array<Matrix>^ BaseEffect::GetMatrixTransposeArray( EffectHandle^ parameter, int count )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			array<Matrix>^ data = gcnew array<Matrix>( count );
			pin_ptr<Matrix> pinnedData = &data[0];

			HRESULT hr = InternalPointer->GetMatrixTransposeArray( handle, reinterpret_cast<D3DXMATRIX*>( pinnedData ), count );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		String^ BaseEffect::GetString( EffectHandle^ parameter )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			LPCSTR data = 0;

			HRESULT hr = InternalPointer->GetString(handle,&data);
			Direct3D9ErrorHandler::TestForFailure( hr );

			return gcnew String(data);
		}

		DataStream^ BaseEffect::GetValue( EffectHandle^ parameter, int bytes )
		{
			D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
			void* data = new char[bytes];

			HRESULT hr = InternalPointer->GetValue( handle, data, bytes );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				return nullptr;

			DataStream^ ds = gcnew DataStream( data, bytes, true, true, false );
			ds->TakeOwnership();
			return ds;
		}
	}
}