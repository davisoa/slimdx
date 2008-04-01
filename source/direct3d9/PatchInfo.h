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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		/// <summary>Describes a triangular high-order patch.</summary>
		/// <unmanaged>D3DTRIPATCH_INFO</unmanaged>
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class TrianglePatchInfo : System::IEquatable<TrianglePatchInfo>
		{
		public:
			property int StartVertexOffset;
			property int VertexCount;
			property Basis Basis;
			property Degree Degree;

			static bool operator == ( TrianglePatchInfo left, TrianglePatchInfo right );
			static bool operator != ( TrianglePatchInfo left, TrianglePatchInfo right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( TrianglePatchInfo other );
			static bool Equals( TrianglePatchInfo% value1, TrianglePatchInfo% value2 );
		};

		/// <summary>Describes a rectangular high-order patch.</summary>
		/// <unmanaged>D3DRECTPATCH_INFO</unmanaged>
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class RectanglePatchInfo : System::IEquatable<RectanglePatchInfo>
		{
		public:
			property int StartVertexOffsetWidth;
			property int StartVertexOffsetHeight;
			property int Width;
			property int Height;
			property int Stride;
			property Basis Basis;
			property Degree Degree;

			static bool operator == ( RectanglePatchInfo left, RectanglePatchInfo right );
			static bool operator != ( RectanglePatchInfo left, RectanglePatchInfo right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( RectanglePatchInfo other );
			static bool Equals( RectanglePatchInfo% value1, RectanglePatchInfo% value2 );
		};

		//TODO: This is D3DX, and really needs to move alongside PatchMesh.
		/// <summary>Structure that contains the attributes of a patch mesh.</summary>
		/// <unmanaged>D3DXPATCHINFO</unmanaged>
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
	}
}