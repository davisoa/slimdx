/*
* Copyright (c) 2007-2010 SlimDX Group
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
#pragma once

#include "EnumsDC.h"

namespace SlimDX
{
	namespace D3DCompiler
	{	
		public value class ShaderParameterDescription : System::IEquatable<ShaderParameterDescription>
		{
		private:
			System::String^ m_SemanticName;
			System::UInt32 m_SemanticIndex;
			System::UInt32 m_Register;
			SystemValueType m_SystemValueType;
			RegisterComponentType m_ComponentType;
			RegisterComponentMaskFlags m_Mask;
			RegisterComponentMaskFlags m_ReadWriteMask;
			int m_Stream;
		
		internal:
			ShaderParameterDescription( const D3D11_SIGNATURE_PARAMETER_DESC& native );
		
		public:
			property System::String^ SemanticName
			{
				System::String^ get();
			}
			
			property System::UInt32 SemanticIndex
			{
				System::UInt32 get();
			}
			
			property System::UInt32 Register
			{
				System::UInt32 get();
			}
			
			property SystemValueType SystemType
			{
				SystemValueType get();
			}
			
			property RegisterComponentType ComponentType
			{
				RegisterComponentType get();
			}
			
			property RegisterComponentMaskFlags UsageMask
			{
				RegisterComponentMaskFlags get();
			}
			
			property RegisterComponentMaskFlags ReadWriteMask
			{
				RegisterComponentMaskFlags get();
			}

			property int Stream
			{
				int get();
			}

			static bool operator == ( ShaderParameterDescription left, ShaderParameterDescription right );
			static bool operator != ( ShaderParameterDescription left, ShaderParameterDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ShaderParameterDescription other );
			static bool Equals( ShaderParameterDescription% value1, ShaderParameterDescription% value2 );
		};
	}
};