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
#if !BOOST_PP_IS_ITERATING
#ifndef SLIMDX_DXGI_RESOURCE_
#define SLIMDX_DXGI_RESOURCE_

#include "../ComObject.h"

#include "DeviceChildDxgi.h"
#include "Enums.h"

#define BOOST_PP_FILENAME_1 "ResourceDxgi.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"

namespace SlimDX
{
	namespace DXGI
	{
		SDX_COM_SUBCLASS(Resource,DeviceChild)
		{
			COMOBJECT_INTERFACE(IDXGIResource, Resource);

		public:
			/// <summary>
			/// Gets or sets the eviction priority for the resource.
			/// </summary>
			property ResourcePriority EvictionPriority
			{
				SDX_METHOD(ResourcePriority get());
				SDX_METHOD(void set( ResourcePriority value ));
			}
			
			/// <summary>
			/// Gets the resource usage.
			/// </summary>
			property DXGI::Usage Usage
			{
				SDX_METHOD(DXGI::Usage get());
			}
		};
	}
};

#include "../InterfaceEnd.h"
#endif