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
//     Functions for SlimDX2.Direct3D namespace.
//     This code was generated by a tool.
//     Date : 10/25/2010 14:26:43
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace SlimDX2.Direct3D {


	/// <summary>
    /// D3DCommon Functions.
    /// </summary>
    static partial class D3DCommon {   
        
        /// <summary>	
        /// Creates a buffer.	
        /// </summary>	
        /// <remarks>	
        /// The latest D3dcompiler_nn.dll contains the D3DCreateBlob compiler function. Therefore, you are no longer required to create and use an arbitrary length data buffer by using the  {{D3D10CreateBlob}} function that is contained in D3d10.dll.	
        /// </remarks>	
        /// <param name="size">Number of bytes in the blob.</param>
        /// <param name="blobRef">The address of a pointer to the <see cref="SlimDX2.Direct3D.Blob"/> interface that is used to retrieve the buffer.</param>
        /// <returns>Returns one of the following {{Direct3D 10 Return Codes}}.</returns>
        /// <unmanaged>HRESULT D3DCreateBlob([In] SIZE_T Size,[Out] ID3DBlob** ppBlob)</unmanaged>
		public static SlimDX2.Result CreateBlob(SlimDX2.Size size, out SlimDX2.Direct3D.Blob blobRef) {
            unsafe {
                IntPtr blobRef_ = IntPtr.Zero;
                SlimDX2.Result __result__;
                __result__= (SlimDX2.Result)D3DCreateBlob_( size, out blobRef_);
                blobRef = (blobRef_ == IntPtr.Zero)?null:new SlimDX2.Direct3D.Blob(blobRef_);
                __result__.CheckError();
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>HRESULT D3DCreateBlob([In] SIZE_T Size,[Out] ID3DBlob** ppBlob)</unmanaged>
		[DllImport("d3dcompiler_43.dll", EntryPoint = "D3DCreateBlob", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static SlimDX2.Result D3DCreateBlob_(SlimDX2.Size size, out IntPtr blobRef);		
    }
}