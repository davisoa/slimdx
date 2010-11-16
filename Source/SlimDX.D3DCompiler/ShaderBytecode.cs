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
using System.IO;
using System.Text;
using SlimDX.Direct3D;

namespace SlimDX.D3DCompiler
{
    /// <summary>
    ///   Represents the compiled bytecode of a shader or effect.
    /// </summary>
    /// <unmanaged>Blob</unmanaged>
    public class ShaderBytecode : Blob
    {
        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.D3DCompiler.ShaderBytecode" /> class.
        /// </summary>
        /// <param name = "data">A <see cref = "T:SlimDX.DataStream" /> containing the compiled bytecode.</param>
        public ShaderBytecode(DataStream data) : base(IntPtr.Zero)
        {
            CreateFromPointer(data.DataPointer, (int) data.Length);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.D3DCompiler.ShaderBytecode" /> class.
        /// </summary>
        /// <param name = "data">A <see cref = "T:System.IO.Stream" /> containing the compiled bytecode.</param>
        public ShaderBytecode(Stream data)
            : base(IntPtr.Zero)
        {
            int size = (int) (data.Length - data.Position);

            byte[] localBuffer = new byte[size];
            data.Read(localBuffer, 0, size);
            CreateFromBuffer(localBuffer);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.D3DCompiler.ShaderBytecode" /> class.
        /// </summary>
        /// <param name = "data">A <see cref = "T:System.IO.Stream" /> containing the compiled bytecode.</param>
        public ShaderBytecode(byte[] buffer)
            : base(IntPtr.Zero)
        {
            CreateFromBuffer(buffer);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.D3DCompiler.ShaderBytecode" /> class.
        /// </summary>
        /// <param name = "buffer">a pointer to a compiler bytecode</param>
        /// <param name = "sizeInBytes">size of the bytecode</param>
        public ShaderBytecode(IntPtr buffer, int sizeInBytes)
            : base(IntPtr.Zero)
        {
            CreateFromPointer(buffer, sizeInBytes);
        }

        private void CreateFromBuffer(byte[] buffer)
        {
            unsafe
            {
                fixed (void* pBuffer = &buffer[0])
                    CreateFromPointer((IntPtr) pBuffer, buffer.Length);
            }
        }

        private void CreateFromPointer(IntPtr buffer, int sizeInBytes)
        {
            Blob blob;
            D3DCommon.CreateBlob(sizeInBytes, out blob);
            NativePointer = blob.NativePointer;

            Utilities.CopyMemory(blob.GetBufferPointer(), buffer, sizeInBytes);
        }

        protected internal ShaderBytecode(Blob blob)
            : base(IntPtr.Zero)
        {
            NativePointer = blob.NativePointer;
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags)
        {
            string compilationErrors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), null, profile, shaderFlags, effectFlags, null, null,
                           out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags)
        {
            string compilationErrors = null;
            return Compile(shaderSource, null, profile, shaderFlags, effectFlags, null, null, out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags)
        {
            string compilationErrors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), entryPoint, profile, shaderFlags, effectFlags, null,
                           null, out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags)
        {
            string compilationErrors = null;
            return Compile(shaderSource, entryPoint, profile, shaderFlags, effectFlags, null, null,
                           out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags, ShaderMacro[] defines, Include include)
        {
            string compilationErrors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), null, profile, shaderFlags, effectFlags, defines,
                           include, out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags, ShaderMacro[] defines, Include include)
        {
            string compilationErrors = null;
            return Compile(shaderSource, null, profile, shaderFlags, effectFlags, defines, include,
                           out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags, ShaderMacro[] defines, Include include,
                                             out string compilationErrors)
        {
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), null, profile, shaderFlags, effectFlags, defines,
                           include, out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string profile, ShaderFlags shaderFlags,
                                             EffectFlags effectFlags, ShaderMacro[] defines, Include include,
                                             out string compilationErrors)
        {
            return Compile(shaderSource, null, profile, shaderFlags, effectFlags, defines, include,
                           out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags, ShaderMacro[] defines,
                                             Include include)
        {
            string compilationErrors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), entryPoint, profile, shaderFlags, effectFlags, defines,
                           include, out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags, ShaderMacro[] defines,
                                             Include include)
        {
            string compilationErrors = null;
            return Compile(shaderSource, entryPoint, profile, shaderFlags, effectFlags, defines, include,
                           out compilationErrors);
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(byte[] shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags, ShaderMacro[] defines,
                                             Include include, out string compilationErrors)
        {
            unsafe
            {
                ShaderBytecode bytecode;

                Blob blobForCode = null;
                Blob blobForErrors = null;
                compilationErrors = null;

                try
                {
                    IncludeCallback includeCallback = null;
                    if (include != null)
                        includeCallback = new IncludeCallback(include);
                    IntPtr includeCallbackPtr = includeCallback == null ? IntPtr.Zero : includeCallback.NativePointer;


                    fixed (void* pData = &shaderSource[0])
                        D3D.Compile((IntPtr)pData, shaderSource.Length, "", PrepareMacros(defines), includeCallbackPtr, entryPoint,
                                    profile, shaderFlags,
                                    effectFlags, out blobForCode, out blobForErrors);
                }
                catch (SlimDXException ex)
                {
                    if (blobForErrors != null)
                    {
                        compilationErrors = Utilities.BlobToString(blobForErrors);
                    }
                    ex.Data.Add("CompilationErrors", compilationErrors);
                    throw ex;
                }
                bytecode = new ShaderBytecode(blobForCode);

                return bytecode;
            }
        }

        /// <summary>
        ///   Compiles the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode Compile(string shaderSource, string entryPoint, string profile,
                                             ShaderFlags shaderFlags, EffectFlags effectFlags, ShaderMacro[] defines,
                                             Include include, out string compilationErrors)
        {
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Compile(Encoding.ASCII.GetBytes(shaderSource), entryPoint, profile, shaderFlags, effectFlags, defines,
                           include, out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string profile, ShaderFlags shaderFlags,
                                                     EffectFlags effectFlags)
        {
            string compilationErrors = null;
            return CompileFromFile(fileName, null, profile, shaderFlags, effectFlags, null, null, out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string entryPoint, string profile,
                                                     ShaderFlags shaderFlags, EffectFlags effectFlags)
        {
            string compilationErrors = null;
            return CompileFromFile(fileName, entryPoint, profile, shaderFlags, effectFlags, null, null,
                                   out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string profile, ShaderFlags shaderFlags,
                                                     EffectFlags effectFlags, ShaderMacro[] defines, Include include)
        {
            string compilationErrors = null;
            return CompileFromFile(fileName, null, profile, shaderFlags, effectFlags, defines, include,
                                   out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string profile, ShaderFlags shaderFlags,
                                                     EffectFlags effectFlags, ShaderMacro[] defines, Include include,
                                                     out string compilationErrors)
        {
            return CompileFromFile(fileName, null, profile, shaderFlags, effectFlags, defines, include,
                                   out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string entryPoint, string profile,
                                                     ShaderFlags shaderFlags, EffectFlags effectFlags,
                                                     ShaderMacro[] defines, Include include)
        {
            string compilationErrors = null;
            return CompileFromFile(fileName, entryPoint, profile, shaderFlags, effectFlags, defines, include,
                                   out compilationErrors);
        }

        /// <summary>
        ///   Compiles a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "entryPoint">The name of the shader entry-point function, or <c>null</c> for an effect file.</param>
        /// <param name = "profile">The shader target or set of shader features to compile against.</param>
        /// <param name = "shaderFlags">Shader compilation options.</param>
        /// <param name = "effectFlags">Effect compilation options.</param>
        /// <param name = "defines">A set of macros to define during compilation.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if compilation succeeded.</param>
        /// <returns>The compiled shader bytecode, or <c>null</c> if the method fails.</returns>
        public static ShaderBytecode CompileFromFile(string fileName, string entryPoint, string profile,
                                                     ShaderFlags shaderFlags, EffectFlags effectFlags,
                                                     ShaderMacro[] defines, Include include,
                                                     out string compilationErrors)
        {
            if (fileName == null)
            {
                throw new ArgumentNullException("fileName");
            }
            if (profile == null)
            {
                throw new ArgumentNullException("profile");
            }
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Could not open the shader or effect file.", fileName);
            }
            return Compile(File.ReadAllText(fileName), entryPoint, profile, shaderFlags, effectFlags,
                           PrepareMacros(defines), include, out compilationErrors);
        }

        /// <summary>
        ///   Disassembles compiled HLSL code back into textual source.
        /// </summary>
        /// <returns>The textual source of the shader or effect.</returns>
        public string Disassemble()
        {
            return this.Disassemble(DisassemblyFlags.None, null);
        }

        /// <summary>
        ///   Disassembles compiled HLSL code back into textual source.
        /// </summary>
        /// <param name = "flags">Flags affecting the output of the disassembly.</param>
        /// <returns>The textual source of the shader or effect.</returns>
        public string Disassemble(DisassemblyFlags flags)
        {
            return this.Disassemble(flags, null);
        }

        /// <summary>
        ///   Disassembles compiled HLSL code back into textual source.
        /// </summary>
        /// <param name = "flags">Flags affecting the output of the disassembly.</param>
        /// <param name = "comments">Commenting information to embed in the disassembly.</param>
        /// <returns>The textual source of the shader or effect.</returns>
        public string Disassemble(DisassemblyFlags flags, string comments)
        {
            Blob output;
            D3D.Disassemble(GetBufferPointer(), GetBufferSize(), flags, comments, out output);
            return Utilities.BlobToString(output);
        }

        public static ShaderBytecode FromPointer(IntPtr pointer)
        {
            // TODO: check that pointer is a blob?
            return new ShaderBytecode(new Blob(pointer));
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to preprocess.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(string shaderSource)
        {
            string errors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Preprocess(Encoding.ASCII.GetBytes(shaderSource), null, null, out errors);
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to preprocess.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(byte[] shaderSource)
        {
            string errors = null;
            return Preprocess(shaderSource, null, null, out errors);
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to preprocess.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(string shaderSource, ShaderMacro[] defines, Include include)
        {
            string errors = null;
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Preprocess(Encoding.ASCII.GetBytes(shaderSource), defines, include, out errors);
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to preprocess.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(byte[] shaderSource, ShaderMacro[] defines, Include include)
        {
            string errors = null;
            return Preprocess(shaderSource, defines, include, out errors);
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">An array of bytes containing the raw source of the shader or effect to preprocess.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if preprocessing succeeded.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(byte[] shaderSource, ShaderMacro[] defines, Include include,
                                        out string compilationErrors)
        {
            unsafe
            {
                Blob blobForText = null;
                Blob blobForErrors = null;
                compilationErrors = null;

                try
                {
                    IncludeCallback includeCallback = null;
                    if (include != null)
                        includeCallback = new IncludeCallback(include);
                    IntPtr includeCallbackPtr = includeCallback == null ? IntPtr.Zero : includeCallback.NativePointer;

                    fixed (void* pData = &shaderSource[0])
                        D3D.Preprocess((IntPtr)pData, shaderSource.Length, "", PrepareMacros(defines), includeCallbackPtr,
                                       out blobForText, out blobForErrors);
                }
                catch (SlimDXException ex)
                {
                    if (blobForErrors != null)
                    {
                        compilationErrors = Utilities.BlobToString(blobForErrors);
                    }
                    ex.Data.Add("CompilationErrors", compilationErrors);
                }
                return Utilities.BlobToString(blobForText);
            }
        }

        /// <summary>
        ///   Preprocesses the provided shader or effect source.
        /// </summary>
        /// <param name = "shaderSource">A string containing the source of the shader or effect to preprocess.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if preprocessing succeeded.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string Preprocess(string shaderSource, ShaderMacro[] defines, Include include,
                                        out string compilationErrors)
        {
            if (string.IsNullOrEmpty(shaderSource))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Preprocess(Encoding.ASCII.GetBytes(shaderSource), defines, include, out compilationErrors);
        }

        /// <summary>
        ///   Preprocesses a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string PreprocessFromFile(string fileName)
        {
            string errors = null;
            if (fileName == null)
            {
                throw new ArgumentNullException("fileName");
            }
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Could not open the shader or effect file.", fileName);
            }
            string str = File.ReadAllText(fileName);
            if (string.IsNullOrEmpty(str))
            {
                throw new ArgumentNullException("shaderSource");
            }
            return Preprocess(Encoding.ASCII.GetBytes(str), null, null, out errors);
        }

        /// <summary>
        ///   Preprocesses a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string PreprocessFromFile(string fileName, ShaderMacro[] defines, Include include)
        {
            string errors = null;
            return PreprocessFromFile(fileName, defines, include, out errors);
        }

        /// <summary>
        ///   Preprocesses a shader or effect from a file on disk.
        /// </summary>
        /// <param name = "fileName">The name of the source file to compile.</param>
        /// <param name = "defines">A set of macros to define during preprocessing.</param>
        /// <param name = "include">An interface for handling include files.</param>
        /// <param name = "compilationErrors">When the method completes, contains a string of compilation errors, or an empty string if preprocessing succeeded.</param>
        /// <returns>The preprocessed shader source.</returns>
        public static string PreprocessFromFile(string fileName, ShaderMacro[] defines, Include include,
                                                out string compilationErrors)
        {
            if (fileName == null)
            {
                throw new ArgumentNullException("fileName");
            }
            if (!File.Exists(fileName))
            {
                throw new FileNotFoundException("Could not open the shader or effect file.", fileName);
            }
            return Preprocess(File.ReadAllText(fileName), defines, include, out compilationErrors);
        }

        /// <summary>
        ///   Strips extraneous information from a compiled shader or effect.
        /// </summary>
        /// <param name = "flags">Options specifying what to remove from the shader.</param>
        /// <returns>A string containing any errors that may have occurred.</returns>
        public string Strip(StripFlags flags)
        {
            try
            {
                Blob blob;
                D3D.StripShader(GetBufferPointer(), GetBufferSize(), flags, out blob);
                return Utilities.BlobToString(blob);
            }
            catch (SlimDXException ex)
            {
                return null;
            }
        }

        /// <summary>
        ///   Gets the raw data of the compiled bytecode.
        /// </summary>
        public DataStream Data
        {
            get { return new DataStream(this); }
        }

        /// <summary>
        ///   Read a compiled shader bytecode from a Stream and return a ShaderBytecode
        /// </summary>
        /// <param name = "stream"></param>
        /// <returns></returns>
        public static ShaderBytecode FromStream(Stream stream)
        {
            return new ShaderBytecode(stream);
        }

        /// <summary>
        ///   Read a compiled shader bytecode from a Stream and return a ShaderBytecode
        /// </summary>
        /// <param name = "fileName"></param>
        /// <returns></returns>
        public static ShaderBytecode FromFile(string fileName)
        {
            return new ShaderBytecode(File.ReadAllBytes(fileName));
        }

        internal static ShaderMacro[] PrepareMacros(ShaderMacro[] macros)
        {
            if (macros == null)
                return null;

            if (macros.Length == 0)
                return null;

            if (macros[macros.Length - 1].Name == null && macros[macros.Length - 1].Definition == null)
                return macros;

            var macroArray = new ShaderMacro[macros.Length + 1];

            Array.Copy(macros, macroArray, macros.Length);

            macroArray[macros.Length] = new ShaderMacro(null, null);
            return macroArray;
        }
    }
}