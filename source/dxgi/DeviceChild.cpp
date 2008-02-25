/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include <dxgi.h>

#include "DXGIException.h"

#include "Device.h"
#include "DeviceChild.h"

using namespace System;

namespace SlimDX
{
namespace DXGI
{ 
	DeviceChild::DeviceChild()
	{
	}
	
	DeviceChild::DeviceChild( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Device^ DeviceChild::GetDevice()
	{
		IDXGIDevice* device = 0;
		RECORD_DXGI( InternalPointer->GetDevice( __uuidof( device ), reinterpret_cast<void**>( &device ) ) );
		if( Result::Last.IsFailure )
			return nullptr;
		return gcnew Device( device );
	}
}
}
