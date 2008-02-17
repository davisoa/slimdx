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
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "../ComObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Adapter;
		
		/// <remarks>
		/// Provides access to connected adapters and window associations. A Factory
		/// is also required to create most DXGI objects.
		/// </remarks>
		public ref class Factory : public ComObject
		{
			COMOBJECT(IDXGIFactory);
			
		public:
			/// <summary>
			/// Constructs a new Factory.
			/// </summary>
			Factory();
			
			/// <summary>
			/// Constructs a Factory from an unmanaged pointer.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIFactory pointer.</param>
			Factory( IntPtr pointer );
			
			/// <summary>
			/// Gets the number of available adapters.
			/// </summary>
			/// <returns>The number of available adapters.</returns>
			int GetAdapterCount();
			
			/// <summary>
			/// Gets the specified adapter.
			/// </summary>
			/// <param name="index">The index of the desired adapter.</param>
			/// <returns>The specified adapter, or null on failure.</returns>
			Adapter^ GetAdapter( int index );
		
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="module">The unmanaged HMODULE for the software adapter DLL.</param>
			/// <returns>The specified adapter, or null on failure.</returns>
			Adapter^ CreateSoftwareAdapter( IntPtr module );
			
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="module">The module for the software adapter DLL.</param>
			/// <returns>The specified adapter, or null on failure.</returns>
			Adapter^ CreateSoftwareAdapter( System::Reflection::Module^ module );
			
			/// <summary>
			/// Gets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <returns>The window handle.</returns>
			IntPtr GetWindowAssociation();
			
			/// <summary>
			/// Sets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <param name="handle">The window handle.</param>
			/// <param name="flags">Flags controlling window association behavior.</param>
			/// <returns>A Result code.</returns>
			Result SetWindowAssociation( IntPtr handle, WindowAssociationFlags flags );
		};
	}
};