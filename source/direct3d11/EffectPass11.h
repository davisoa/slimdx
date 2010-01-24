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

#include "../Result.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class DeviceContext;
		ref class EffectVariable;
		value class EffectPassDescription;
		value class EffectPassShaderDescription;
		
		public ref class EffectPass
		{
		private:
			ID3DX11EffectPass* m_Pointer;

		internal:
			EffectPass( ID3DX11EffectPass* pointer );
			
		public:
			property EffectPassDescription Description
			{
				EffectPassDescription get();
			}
			
			property bool IsValid
			{
				bool get();
			}
			
			property EffectPassShaderDescription GeometryShaderDescription
			{
				EffectPassShaderDescription get();
			}
			
			property EffectPassShaderDescription VertexShaderDescription
			{
				EffectPassShaderDescription get();
			}
			property EffectPassShaderDescription PixelShaderDescription
			{
				EffectPassShaderDescription get();
			}
			
			EffectPass( System::IntPtr pointer );
			
			EffectVariable^ GetAnnotationByIndex( int index );
			EffectVariable^ GetAnnotationByName( System::String^ name );
			
			Result Apply( DeviceContext^ context );
		};
	}
};
