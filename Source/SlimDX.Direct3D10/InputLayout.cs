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
using SlimDX.D3DCompiler;

namespace SlimDX.Direct3D10
{
    public partial class InputLayout
    {
        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D10.InputLayout" /> object to describe the
        ///   input-buffer data for the input-assembler stage.
        /// </summary>
        /// <unmanaged>ID3D10Device::CreateInputLayout</unmanaged>
        /// <param name = "device">The device used to create the layout.</param>
        /// <param name = "elements">An array of input elements describing the layout of the input data.</param>
        /// <param name = "shaderBytecode">The compiled shader used to validate the input elements.</param>
        public InputLayout(Device device, ShaderBytecode shaderBytecode, InputElement[] elements)
            : base(IntPtr.Zero)
        {
            InputLayout layout;
            device.CreateInputLayout(elements, elements.Length, shaderBytecode.GetBufferPointer(),
                                     shaderBytecode.GetBufferSize(), out layout);
            NativePointer = layout.NativePointer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D10.InputLayout" /> object to describe the
        ///   input-buffer data for the input-assembler stage.
        /// </summary>
        /// <unmanaged>ID3D10Device::CreateInputLayout</unmanaged>
        /// <param name = "device">The device used to create the layout.</param>
        /// <param name = "elements">An array of input elements describing the layout of the input data.</param>
        /// <param name = "shaderSignature">The shader signature used to validate the input elements.</param>
        public InputLayout(Device device, ShaderSignature shaderSignature, InputElement[] elements)
            : base(IntPtr.Zero)
        {
            InputLayout layout;
            device.CreateInputLayout(elements, elements.Length, shaderSignature.GetBufferPointer(),
                                     shaderSignature.GetBufferSize(), out layout);
            NativePointer = layout.NativePointer;
        }
    }
}