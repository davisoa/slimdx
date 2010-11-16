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

namespace SlimDX.Direct3D11
{
    public partial class Texture3D
    {
        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Texture3D" /> class.
        /// </summary>
        /// <param name = "device">The device with which to associate the texture.</param>
        /// <param name = "description">The description of the texture.</param>
        public Texture3D(Device device, Texture3DDescription description)
            : base(IntPtr.Zero)
        {
            Texture3D temp;
            device.CreateTexture3D(ref description, null, out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Texture3D" /> class.
        /// </summary>
        /// <param name = "device">The device with which to associate the texture.</param>
        /// <param name = "description">The description of the texture.</param>
        /// <param name = "data">The initial texture data.</param>
        public Texture3D(Device device, Texture3DDescription description, DataBox data)
            : this(device, description, new[] {data})
        {
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Texture3D" /> class.
        /// </summary>
        /// <param name = "device">The device with which to associate the texture.</param>
        /// <param name = "description">The description of the texture.</param>
        /// <param name = "data">An array of initial texture data for each subresource.</param>
        public Texture3D(Device device, Texture3DDescription description, DataBox[] data) : base(IntPtr.Zero)
        {
            Texture3D temp;

            SubResourceData[] subResourceDatas = null;

            if (data != null)
            {
                subResourceDatas = new SubResourceData[data.Length];
                for (int i = 0; i < subResourceDatas.Length; i++)
                {
                    subResourceDatas[i].DataPointer = data[i].Data.DataPointer;
                    subResourceDatas[i].Pitch = data[i].RowPitch;
                    subResourceDatas[i].SlicePitch = data[i].SlicePitch;
                }
            }

            device.CreateTexture3D(ref description, subResourceDatas, out temp);
            NativePointer = temp.NativePointer;
        }
    }
}