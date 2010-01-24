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

#include "../dxgi/Enums.h"

#include "Enums11.h"

namespace SlimDX
{
	namespace Direct3D11
	{	
		public value class DepthStencilViewDescription : System::IEquatable<DepthStencilViewDescription>
		{				
		internal:
			DepthStencilViewDescription( const D3D11_DEPTH_STENCIL_VIEW_DESC& native );
			
			D3D11_DEPTH_STENCIL_VIEW_DESC CreateNativeVersion();
		
		public:
			property DXGI::Format Format;
			property DepthStencilViewDimension Dimension;
			property DepthStencilViewFlags Flags;
			property int MipSlice;
			property int FirstArraySlice;
			property int ArraySize;

			static bool operator == ( DepthStencilViewDescription left, DepthStencilViewDescription right );
			static bool operator != ( DepthStencilViewDescription left, DepthStencilViewDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( DepthStencilViewDescription other );
			static bool Equals( DepthStencilViewDescription% value1, DepthStencilViewDescription% value2 );
		};
	}
};