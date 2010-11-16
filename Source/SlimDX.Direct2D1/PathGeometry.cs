﻿// Copyright (c) 2007-2010 SlimDX Group
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
using System;

namespace SlimDX.Direct2D1
{
    public partial class PathGeometry
    {
        /// <summary>	
        /// Creates an empty <see cref="SlimDX.Direct2D1.PathGeometry"/>.	
        /// </summary>	
        /// <param name="factory">an instance of <see cref = "SlimDX.Direct2D1.Factory" /></param>
        public PathGeometry(Factory factory)
            : base(IntPtr.Zero)
        {
            PathGeometry temp;
            factory.CreatePathGeometry(out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>	
        /// Copies the contents of the path geometry to the specified <see cref="SlimDX.Direct2D1.GeometrySink"/>.	
        /// </summary>	
        /// <param name="geometrySink">The sink to which the path geometry's contents are copied. Modifying this sink does not change the contents of this path geometry.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Stream([In] ID2D1GeometrySink* geometrySink)</unmanaged>
        public SlimDX.Result Stream(GeometrySink geometrySink)
        {
            GeometrySinkCallback _callback = null;
            IntPtr ptr;
            if (geometrySink is ComObject)
                ptr = (geometrySink as ComObject).NativePointer;
            else
            {
                _callback = new GeometrySinkCallback(geometrySink);
                ptr = _callback.NativePointer;
            }
            return this.Stream_(ptr);
        }

        /// <summary>	
        /// Retrieves the geometry sink that is used to populate the path geometry with figures and segments. 	
        /// </summary>	
        /// <remarks>	
        /// Because path geometries are immutable and can only be populated once, it is an error to call Open on a path geometry more than once.Note that the fill mode defaults to <see cref="SlimDX.Direct2D1.FillMode.Alternate"/>. To set the fill mode, call {{SetFillMode}} before the first call to {{BeginFigure}}. Failure to do so will put the geometry sink in an error state. 	
        /// </remarks>	
        /// <returns>the geometry sink that is used to populate the path geometry with figures and segments.</returns>
        /// <unmanaged>HRESULT Open([Out] ID2D1GeometrySink** geometrySink)</unmanaged>
        public GeometrySink Open()
        {
            GeometrySink sink;
            this.Open(out sink);
            return sink;
        }
    }
}
