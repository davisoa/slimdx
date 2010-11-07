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
//     Functions for SlimDX2.Direct2D1 namespace.
//     This code was generated by a tool.
//     Date : 11/07/2010 19:39:58
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace SlimDX2.Direct2D1 {


	/// <summary>
    /// D2D1 Functions.
    /// </summary>
    static partial class D2D1 {   
        
        /// <summary>	
        /// Creates a factory object  that can be used to create Direct2D resources.	
        /// </summary>	
        /// <remarks>	
        /// The <see cref="SlimDX2.Direct2D1.Factory"/> interface provides the starting point for  Direct2D. In general, objects created from a single instance of a factory object can be used with other resources created from that instance, but not with resources created by other factory instances.   	
        /// </remarks>	
        /// <param name="factoryType">The threading model of the factory and the resources it creates.</param>
        /// <param name="riid">A reference to the IID of <see cref="SlimDX2.Direct2D1.Factory"/> that is obtained by using __uuidof(ID2D1Factory).</param>
        /// <param name="factoryOptionsRef">The level of detail provided to the debugging layer.</param>
        /// <param name="iFactoryRef">When this method returns, contains the address to a pointer to the new factory.</param>
        /// <returns>If the function succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT D2D1CreateFactory([In] D2D1_FACTORY_TYPE factoryType,[In] REFIID riid,[In, Optional] const D2D1_FACTORY_OPTIONS* pFactoryOptions,[Out] void** ppIFactory)</unmanaged>
		public static SlimDX2.Result CreateFactory(SlimDX2.Direct2D1.FactoryType factoryType, Guid riid, SlimDX2.Direct2D1.FactoryOptions? factoryOptionsRef, out IntPtr iFactoryRef) {
            unsafe {
							
                SlimDX2.Direct2D1.FactoryOptions factoryOptionsRef_ = new SlimDX2.Direct2D1.FactoryOptions();
                if (factoryOptionsRef.HasValue)
                    factoryOptionsRef_ = factoryOptionsRef.Value;								
                SlimDX2.Result __result__;
                __result__= (SlimDX2.Result)D2D1CreateFactory_( factoryType, ref  riid, (factoryOptionsRef.HasValue)?new IntPtr(&factoryOptionsRef_):IntPtr.Zero, out iFactoryRef);
                __result__.CheckError();
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>HRESULT D2D1CreateFactory([In] D2D1_FACTORY_TYPE factoryType,[In] REFIID riid,[In, Optional] const D2D1_FACTORY_OPTIONS* pFactoryOptions,[Out] void** ppIFactory)</unmanaged>
		[DllImport("d2d1.dll", EntryPoint = "D2D1CreateFactory", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static SlimDX2.Result D2D1CreateFactory_(SlimDX2.Direct2D1.FactoryType factoryType, ref Guid riid, IntPtr factoryOptionsRef, out IntPtr iFactoryRef);		
        
        /// <summary>	
        /// Creates a rotation transformation that rotates by the specified angle about the specified point.	
        /// </summary>	
        /// <remarks>	
        /// Rotation occurs in the plane of the 2-D surface.	
        /// </remarks>	
        /// <param name="angle">The clockwise rotation angle, in degrees. </param>
        /// <param name="center">The point about which to rotate.</param>
        /// <param name="matrix">When this method returns, contains the new rotation transformation. You must allocate storage for this parameter.  </param>
        /// <unmanaged>void D2D1MakeRotateMatrix([In] FLOAT angle,[In] D2D1_POINT_2F center,[Out] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		public static void MakeRotateMatrix(float angle, System.Drawing.PointF center, out SlimDX2.Direct2D1.Matrix3x2 matrix) {
            unsafe {
                D2D1MakeRotateMatrix_( angle,  center, out matrix);
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>void D2D1MakeRotateMatrix([In] FLOAT angle,[In] D2D1_POINT_2F center,[Out] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		[DllImport("d2d1.dll", EntryPoint = "D2D1MakeRotateMatrix", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static void D2D1MakeRotateMatrix_(float angle, System.Drawing.PointF center, out SlimDX2.Direct2D1.Matrix3x2 matrix);		
        
        /// <summary>	
        /// Creates a skew transformation that has the specified x-axis angle, y-axis angle, and center point. 	
        /// </summary>	
        /// <param name="angleX">The x-axis skew angle, which is measured in degrees counterclockwise from the y-axis.</param>
        /// <param name="angleY">The y-axis skew angle, which is measured in degrees counterclockwise from the x-axis.</param>
        /// <param name="center">The center point of the skew operation.</param>
        /// <param name="matrix">When this method returns, contains the rotation transformation. You must allocate storate for this parameter.</param>
        /// <unmanaged>void D2D1MakeSkewMatrix([In] FLOAT angleX,[In] FLOAT angleY,[In] D2D1_POINT_2F center,[Out] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		public static void MakeSkewMatrix(float angleX, float angleY, System.Drawing.PointF center, out SlimDX2.Direct2D1.Matrix3x2 matrix) {
            unsafe {
                D2D1MakeSkewMatrix_( angleX,  angleY,  center, out matrix);
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>void D2D1MakeSkewMatrix([In] FLOAT angleX,[In] FLOAT angleY,[In] D2D1_POINT_2F center,[Out] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		[DllImport("d2d1.dll", EntryPoint = "D2D1MakeSkewMatrix", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static void D2D1MakeSkewMatrix_(float angleX, float angleY, System.Drawing.PointF center, out SlimDX2.Direct2D1.Matrix3x2 matrix);		
        
        /// <summary>	
        /// Indicates whether the specified matrix is invertible.	
        /// </summary>	
        /// <param name="matrix">The matrix to test.</param>
        /// <returns>BOOLtrue if the matrix was inverted; otherwise, false.</returns>
        /// <unmanaged>BOOL D2D1IsMatrixInvertible([In] const D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		public static bool IsMatrixInvertible(ref SlimDX2.Direct2D1.Matrix3x2 matrix) {
            unsafe {
                bool __result__;
                __result__= (bool)D2D1IsMatrixInvertible_(ref  matrix);
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>BOOL D2D1IsMatrixInvertible([In] const D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		[DllImport("d2d1.dll", EntryPoint = "D2D1IsMatrixInvertible", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static bool D2D1IsMatrixInvertible_(ref SlimDX2.Direct2D1.Matrix3x2 matrix);		
        
        /// <summary>	
        /// Attempts to invert the specified matrix.	
        /// </summary>	
        /// <param name="matrix">The matrix to invert.</param>
        /// <returns>BOOLtrue if the matrix was inverted; otherwise, false.</returns>
        /// <unmanaged>BOOL D2D1InvertMatrix([InOut] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		public static bool InvertMatrix(ref SlimDX2.Direct2D1.Matrix3x2 matrix) {
            unsafe {
                bool __result__;
                __result__= (bool)D2D1InvertMatrix_(ref  matrix);
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>BOOL D2D1InvertMatrix([InOut] D2D1_MATRIX_3X2_F* matrix)</unmanaged>
		[DllImport("d2d1.dll", EntryPoint = "D2D1InvertMatrix", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static bool D2D1InvertMatrix_(ref SlimDX2.Direct2D1.Matrix3x2 matrix);		
    }
}