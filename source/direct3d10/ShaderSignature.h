/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "../ComObject.h"

#include "Enums.h"
#include "Resource10.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		public ref class ShaderSignature : System::IDisposable
		{
		private:
			const void* m_Buffer;
			int m_Length;
			ID3D10Blob *blob;
		
		internal:
			property const void* Buffer
			{
				const void* get();
			}
			
			property int Length
			{
				int get();
			}

			ShaderSignature( ID3D10Blob *blob );
			ShaderSignature( const void* buffer, int length );

			void Destruct();

		public:
			~ShaderSignature();
			!ShaderSignature();

			static ShaderSignature^ GetInputSignature( System::String^ shaderSource );
			static ShaderSignature^ GetInputSignature( array<System::Byte>^ shaderSource );

			static ShaderSignature^ GetOutputSignature( System::String^ shaderSource );
			static ShaderSignature^ GetOutputSignature( array<System::Byte>^ shaderSource );

			static ShaderSignature^ GetInputOutputSignature( System::String^ shaderSource );
			static ShaderSignature^ GetInputOutputSignature( array<System::Byte>^ shaderSource );

			/// <summary>
			/// Returns the hash code for this instance.
			/// </summary>
			/// <returns>A 32-bit signed integer hash code.</returns>
			virtual int GetHashCode() override;
		};
	}
};