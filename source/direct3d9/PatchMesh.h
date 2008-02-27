/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class BaseMesh;
		ref class Mesh;
		ref class VertexBuffer;
		ref class IndexBuffer;

		public enum class PatchMeshType : System::Int32
		{
			Rectangle = D3DXPATCHMESH_RECT,
			Triangle = D3DXPATCHMESH_TRI,
			NPatch = D3DXPATCHMESH_NPATCH
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		public value class PatchInfo : System::IEquatable<PatchInfo>
		{
		public:
			property PatchMeshType PatchType;
			property Degree Degree;
			property Basis Basis;

			static bool operator == ( PatchInfo left, PatchInfo right );
			static bool operator != ( PatchInfo left, PatchInfo right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( PatchInfo other );
			static bool Equals( PatchInfo% value1, PatchInfo% value2 );
		};

		public value class DisplacementParameters : System::IEquatable<DisplacementParameters>
		{
		public:
			property Texture^ Texture;
			property TextureFilter MinFilter;
			property TextureFilter MagFilter;
			property TextureFilter MipFilter;
			property TextureAddress Wrap;
			property int LevelOfDetailBias;

			static bool operator == ( DisplacementParameters left, DisplacementParameters right );
			static bool operator != ( DisplacementParameters left, DisplacementParameters right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( DisplacementParameters other );
			static bool Equals( DisplacementParameters% value1, DisplacementParameters% value2 );
		};

		public ref class PatchMesh : ComObject
		{
			COMOBJECT(ID3DXPatchMesh, PatchMesh);

		public:
			PatchMesh( Device^ device, PatchInfo info, int patchCount, int vertexCount, array<VertexElement>^ vertexDeclaration );
			PatchMesh( Mesh^ mesh );
			static PatchMesh^ FromPointer( System::IntPtr pointer );

			static PatchMesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances );
			static PatchMesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials );
			static PatchMesh^ FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags );

			PatchMesh^ Clone( MeshFlags flags, array<VertexElement>^ vertexDeclaration );
			Result GenerateAdjacency( float tolerance );

			array<VertexElement>^ GetDeclaration();
			Device^ GetDevice();
			IndexBuffer^ GetIndexBuffer();
			VertexBuffer^ GetVertexBuffer();
			PatchInfo GetPatchInfo();
			Result Optimize();

			DisplacementParameters GetDisplacementParameters();
			Result SetDisplacementParameters( DisplacementParameters parameters );

			DataStream^ LockAttributeBuffer( LockFlags flags );
			Result UnlockAttributeBuffer();

			DataStream^ LockIndexBuffer( LockFlags flags );
			Result UnlockIndexBuffer();

			DataStream^ LockVertexBuffer( LockFlags flags );
			Result UnlockVertexBuffer();

			Result GetTessellationSize( float tessellationLevel, bool adaptive, [Out] int% triangleCount, [Out] int% vertexCount );
			Result Tessellate( float tessellationLevel, Mesh^ mesh );
			Result Tessellate( Vector4 translation, int minimumLevel, int maximumLevel, Mesh^ mesh );

			property int ControlVerticesPerPatch { int get(); }
			property int PatchCount { int get(); }
			property int VertexCount { int get(); }
			property PatchMeshType Type { PatchMeshType get(); }
		};
	}
}