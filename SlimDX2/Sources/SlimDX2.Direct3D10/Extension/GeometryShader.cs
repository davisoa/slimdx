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
using SlimDX2.D3DCompiler;

namespace SlimDX2.Direct3D10
{
    public partial class GeometryShader
    {
        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.Direct3D10.GeometryShader" /> class.
        /// </summary>
        /// <param name = "device">The device used to create the shader.</param>
        /// <param name = "shaderBytecode">The compiled shader bytecode.</param>
        public GeometryShader(Device device, ShaderBytecode shaderBytecode)
            : base(IntPtr.Zero)
        {
            GeometryShader temp;
            device.CreateGeometryShader(shaderBytecode.GetBufferPointer(),
                                        shaderBytecode.GetBufferSize(), out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX2.Direct3D10.GeometryShader" /> class.
        /// </summary>
        /// <param name = "device">The device used to create the shader.</param>
        /// <param name = "shaderBytecode">The compiled shader bytecode.</param>
        /// <param name = "elements">An array of <see cref = "T:SlimDX2.Direct3D10.StreamOutputElement" /> instances describing the layout of the output buffers.</param>
        /// <param name = "outputStreamStride">The size, in bytes, of each element in the array pointed to by pSODeclaration. This parameter is only used when the output slot is 0 for all entries in pSODeclaration.</param>
        public GeometryShader(Device device, ShaderBytecode shaderBytecode, StreamOutputElement[] elements, int outputStreamStride)
            : base(IntPtr.Zero)
        {
            GeometryShader temp;
            device.CreateGeometryShaderWithStreamOutput(shaderBytecode.GetBufferPointer(),
                                                        shaderBytecode.GetBufferSize(), elements, elements.Length, outputStreamStride, out temp);
            NativePointer = temp.NativePointer;
        }
    }
}