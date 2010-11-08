// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//------------------------------------------------------------------------------
// <auto-generated>
//     Functions for SlimDX2.DXGI namespace.
//     This code was generated by a tool.
//     Date : 11/08/2010 15:18:19
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace SlimDX2.DXGI {


	/// <summary>
    /// DXGI Functions.
    /// </summary>
    static partial class DXGI {   
        
        /// <summary>	
        /// Creates a DXGI 1.0 factory that generates objects used to enumerate and specify video graphics settings.	
        /// </summary>	
        /// <remarks>	
        /// Use a DXGI factory to generate objects that {{enumerate adapters}}, {{create swap chains}}, and {{associate a window}} with the alt+enter key sequence for toggling to and from the fullscreen display mode.Note Do not mix the use of DXGI 1.0 (<see cref="SlimDX2.DXGI.Factory"/>) and DXGI 1.1 (<see cref="SlimDX2.DXGI.Factory1"/>) in an application. Use IDXGIFactory or IDXGIFactory1, but not both in an application.	
        /// </remarks>	
        /// <param name="riid">The globally unique identifier (GUID) of the <see cref="SlimDX2.DXGI.Factory"/> object referenced by the ppFactory parameter.</param>
        /// <param name="factoryRef">Address of a pointer to an <see cref="SlimDX2.DXGI.Factory"/> object.</param>
        /// <returns>Returns S_OK if successful; otherwise, returns one of the following <see cref="SlimDX2.DXGI.DXGIError"/>.</returns>
        /// <unmanaged>HRESULT CreateDXGIFactory([None] REFIID riid,[Out] void** ppFactory)</unmanaged>
		public static SlimDX2.Result CreateDXGIFactory(Guid riid, out IntPtr factoryRef) {
            unsafe {
                SlimDX2.Result __result__;
                __result__= (SlimDX2.Result)CreateDXGIFactory_(ref  riid, out factoryRef);
                __result__.CheckError();
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>HRESULT CreateDXGIFactory([None] REFIID riid,[Out] void** ppFactory)</unmanaged>
		[DllImport("dxgi.dll", EntryPoint = "CreateDXGIFactory", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static SlimDX2.Result CreateDXGIFactory_(ref Guid riid, out IntPtr factoryRef);		
        
        /// <summary>	
        /// Creates a DXGI 1.1 factory that generates objects used to enumerate and specify video graphics settings.	
        /// </summary>	
        /// <remarks>	
        /// Use a DXGI 1.1 factory to generate objects that {{enumerate adapters}},  {{create swap chains}}, and {{associate a window}} with  the alt+enter key sequence for toggling to and from the full-screen display mode.  This entry point is not supported by DXGI 1.0 shipped in Windows Vista and Windows Server 2008. DXGI 1.1 support is required which is available on  Windows 7, Windows Server 2008 R2, and as an update to Windows Vista (KB971644).Note Do not mix the use of DXGI 1.0 (<see cref="SlimDX2.DXGI.Factory"/>) and DXGI 1.1 (<see cref="SlimDX2.DXGI.Factory1"/>) in an application. Use IDXGIFactory or IDXGIFactory1, but not both in an application.	
        /// </remarks>	
        /// <param name="riid">The globally unique identifier (GUID) of the <see cref="SlimDX2.DXGI.Factory1"/> object referenced by  the ppFactory parameter.</param>
        /// <param name="factoryRef">Address of a pointer to an <see cref="SlimDX2.DXGI.Factory1"/> object.</param>
        /// <returns>Returns S_OK if successful; an error code otherwise. For a list of error codes, see <see cref="SlimDX2.DXGI.DXGIError"/>.</returns>
        /// <unmanaged>HRESULT CreateDXGIFactory1([None] REFIID riid,[Out] void** ppFactory)</unmanaged>
		public static SlimDX2.Result CreateDXGIFactory1(Guid riid, out IntPtr factoryRef) {
            unsafe {
                SlimDX2.Result __result__;
                __result__= (SlimDX2.Result)CreateDXGIFactory1_(ref  riid, out factoryRef);
                __result__.CheckError();
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>HRESULT CreateDXGIFactory1([None] REFIID riid,[Out] void** ppFactory)</unmanaged>
		[DllImport("dxgi.dll", EntryPoint = "CreateDXGIFactory1", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static SlimDX2.Result CreateDXGIFactory1_(ref Guid riid, out IntPtr factoryRef);		
    }
}