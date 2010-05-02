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

#include "../stack_array.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace D3DCompiler
	{
		public value class ShaderMacro : System::IEquatable<ShaderMacro>
		{
		internal:
			static stack_array<D3D10_SHADER_MACRO> Marshal( array<ShaderMacro>^ macros, [Out] array<System::Runtime::InteropServices::GCHandle>^% handles );
			static void Unmarshal( array<System::Runtime::InteropServices::GCHandle>^ handles );
			
		public:
			property System::String^ Name;
			property System::String^ Value;

			static bool operator == ( ShaderMacro left, ShaderMacro right );
			static bool operator != ( ShaderMacro left, ShaderMacro right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ShaderMacro other );
			static bool Equals( ShaderMacro% value1, ShaderMacro% value2 );
		};
	}
};