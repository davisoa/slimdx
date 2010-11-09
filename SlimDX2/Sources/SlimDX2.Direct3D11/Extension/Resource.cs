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
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using SlimDX2.Direct3D;
using SlimDX2.DXGI;

namespace SlimDX2.Direct3D11
{
    public partial class Resource
    {
        /// <summary>
        ///   Gets a swap chain back buffer.
        /// </summary>
        /// <typeparam name = "T">The type of the buffer.</typeparam>
        /// <param name = "swapChain">The swap chain to get the buffer from.</param>
        /// <param name = "index">The index of the desired buffer.</param>
        /// <returns>The buffer interface, or <c>null</c> on failure.</returns>
        public static T FromSwapChain<T>(SwapChain swapChain, int index) where T : Resource
        {
            IntPtr resourcePtr;
            swapChain.GetBuffer(0, typeof (T).GUID, out resourcePtr);
            return (T) Activator.CreateInstance(typeof (T), resourcePtr);
        }

        /// <summary>
        ///   Loads a texture from an image file.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "fileName">Path to the file on disk.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromFile<T>(Device device, string fileName) where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            Resource temp;
            int resultOut = 0;
            D3DX11.CreateTextureFromFile(device, fileName, null, IntPtr.Zero, out temp, ref resultOut);
            return temp == null ? null : (T) Activator.CreateInstance(typeof (T), temp.NativePointer);
        }

        /// <summary>
        ///   Loads a texture from an image file.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "fileName">Path to the file on disk.</param>
        /// <param name = "loadInfo">Specifies information used to load the texture.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromFile<T>(Device device, string fileName, ImageLoadInformation loadInfo) where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            Resource temp;
            int resultOut = 0;
            D3DX11.CreateTextureFromFile(device, fileName, loadInfo, IntPtr.Zero, out temp, ref resultOut);
            return temp == null ? null : (T) Activator.CreateInstance(typeof (T), temp.NativePointer);
        }

        /// <summary>
        ///   Loads a texture from an image in memory.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "memory">Array of memory containing the image data to load.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromMemory<T>(Device device, byte[] memory) where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            unsafe
            {
                Debug.Assert(memory != null);
                Debug.Assert(memory.Length > 0);
                Resource temp;
                int resultOut = 0;
                fixed (void* pBuffer = &memory[0])
                    D3DX11.CreateTextureFromMemory(device, (IntPtr) pBuffer, memory.Length, null, IntPtr.Zero,
                                                   out temp, ref resultOut);
                return temp == null ? null : (T) Activator.CreateInstance(typeof (T), temp.NativePointer);
            }
        }

        /// <summary>
        ///   Loads a texture from an image in memory.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "memory">Array of memory containing the image data to load.</param>
        /// <param name = "loadInfo">Specifies information used to load the texture.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromMemory<T>(Device device, byte[] memory, ImageLoadInformation loadInfo) where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            unsafe
            {
                Debug.Assert(memory != null);
                Debug.Assert(memory.Length > 0);
                Resource temp;
                int resultOut = 0;
                fixed (void* pBuffer = &memory[0])
                    D3DX11.CreateTextureFromMemory(device, (IntPtr) pBuffer, memory.Length, loadInfo, IntPtr.Zero,
                                                   out temp, ref resultOut);
                return temp == null ? null : (T) Activator.CreateInstance(typeof (T), temp.NativePointer);
            }
        }

        /// <summary>
        ///   Loads a texture from a stream of data.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "stream">A stream containing the image data to load.</param>
        /// <param name = "sizeInBytes">Size of the image to load.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromStream<T>(Device device, Stream stream, int sizeInBytes) where T : Resource
        {
            byte[] buffer = Utilities.ReadStream(stream, ref sizeInBytes);
            return FromMemory<T>(device, buffer);
        }

        /// <summary>
        ///   Loads a texture from a stream of data.
        /// </summary>
        /// <param name = "device">The device used to load the texture.</param>
        /// <param name = "stream">A stream containing the image data to load.</param>
        /// <param name = "sizeInBytes">Size of the image to load.</param>
        /// <param name = "loadInfo">Specifies information used to load the texture.</param>
        /// <returns>The loaded texture object.</returns>
        public static T FromStream<T>(Device device, Stream stream, int sizeInBytes, ImageLoadInformation loadInfo)
            where T : Resource
        {
            byte[] buffer = Utilities.ReadStream(stream, ref sizeInBytes);
            return FromMemory<T>(device, buffer, loadInfo);
        }

        /// <summary>
        ///   Saves a texture to file.
        /// </summary>
        /// <param name = "context">The device used to save the texture.</param>
        /// <param name = "texture">The texture to save.</param>
        /// <param name = "format">The format the texture will be saved as.</param>
        /// <param name = "fileName">Name of the destination output file where the texture will be saved.</param>
        /// <returns>A <see cref = "T:SlimDX2.Result" /> object describing the result of the operation.</returns>
        public static Result ToFile<T>(DeviceContext context, T texture, ImageFileFormat format, string fileName)
            where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            return D3DX11.SaveTextureToFile(context, texture, format, fileName);
        }

        /// <summary>
        ///   Saves a texture to a stream.
        /// </summary>
        /// <param name = "context">The device used to save the texture.</param>
        /// <param name = "texture">The texture to save.</param>
        /// <param name = "format">The format the texture will be saved as.</param>
        /// <param name = "stream">Destination memory stream where the image will be saved.</param>
        /// <returns>A <see cref = "T:SlimDX2.Result" /> object describing the result of the operation.</returns>
        public static Result ToStream<T>(DeviceContext context, T texture, ImageFileFormat format, Stream stream)
            where T : Resource
        {
            Debug.Assert(typeof (T) == typeof (Texture1D) || typeof (T) == typeof (Texture2D) ||
                         typeof (T) == typeof (Texture3D));

            Blob blob;
            Result result = D3DX11.SaveTextureToMemory(context, texture, format, out blob, 0);

            IntPtr bufferPtr = blob.BufferPointer;
            int blobSize = blob.BufferSize;

            // Write byte-by-byte to avoid allocating a managed byte[] that will wastefully persist.
            for (int byteIndex = 0; byteIndex < blobSize; ++byteIndex)
                stream.WriteByte(Marshal.ReadByte(bufferPtr, byteIndex));

            blob.Release();

            return result;
        }
    }
}