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

namespace SlimDX2.DXGI
{
    public partial class Factory1
    {
        /// <summary>
        ///   Default Constructor for Factory1.
        /// </summary>
        public Factory1() : base(IntPtr.Zero)
        {
            IntPtr factoryPtr;
            DXGI.CreateDXGIFactory1(GetType().GUID, out factoryPtr);
            NativePointer = factoryPtr;
        }

        /// <summary>
        ///   Return the number of available adapters from this factory.
        /// </summary>
        /// <returns>The number of adapters</returns>
        public int GetAdapterCount1()
        {
            int nbAdapters = 0;
            Adapter1 adapter;
            do
            {
                try
                {
                    EnumAdapters1(nbAdapters, out adapter);
                }
                catch (SlimDX2Exception exception)
                {
                    if (exception.ResultCode.Code == (int) DXGIError.NotFound)
                        break;
                    throw;
                }
                nbAdapters++;
            } while (true);
            return nbAdapters;
        }
    }
}