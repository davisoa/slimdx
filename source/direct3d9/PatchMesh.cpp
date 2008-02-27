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
#include <d3d9.h>
#include <d3dx9.h>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "PatchMesh.h"

#include "Direct3D9Exception.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	bool PatchInfo::operator == ( PatchInfo left, PatchInfo right )
	{
		return PatchInfo::Equals( left, right );
	}

	bool PatchInfo::operator != ( PatchInfo left, PatchInfo right )
	{
		return !PatchInfo::Equals( left, right );
	}

	int PatchInfo::GetHashCode()
	{
		return PatchType.GetHashCode() + Degree.GetHashCode() + Basis.GetHashCode();
	}

	bool PatchInfo::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<PatchInfo>( value ) );
	}

	bool PatchInfo::Equals( PatchInfo value )
	{
		return ( PatchType == value.PatchType && Degree == value.Degree && Basis == value.Basis );
	}

	bool PatchInfo::Equals( PatchInfo% value1, PatchInfo% value2 )
	{
		return ( value1.PatchType == value2.PatchType && value1.Degree == value2.Degree && value1.Basis == value2.Basis );
	}

	bool DisplacementParameters::operator == ( DisplacementParameters left, DisplacementParameters right )
	{
		return DisplacementParameters::Equals( left, right );
	}

	bool DisplacementParameters::operator != ( DisplacementParameters left, DisplacementParameters right )
	{
		return !DisplacementParameters::Equals( left, right );
	}

	int DisplacementParameters::GetHashCode()
	{
		return Texture->GetHashCode() + MinFilter.GetHashCode() + MagFilter.GetHashCode()
			 + MipFilter.GetHashCode() + Wrap.GetHashCode() + LevelOfDetailBias.GetHashCode();
	}

	bool DisplacementParameters::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<DisplacementParameters>( value ) );
	}

	bool DisplacementParameters::Equals( DisplacementParameters value )
	{
		return ( Texture == value.Texture && MinFilter == value.MinFilter && MagFilter == value.MagFilter
			 && MipFilter == value.MipFilter && Wrap == value.Wrap && LevelOfDetailBias == value.LevelOfDetailBias );
	}

	bool DisplacementParameters::Equals( DisplacementParameters% value1, DisplacementParameters% value2 )
	{
		return ( value1.Texture == value2.Texture && value1.MinFilter == value2.MinFilter && value1.MagFilter == value2.MagFilter
			 && value1.MipFilter == value2.MipFilter && value1.Wrap == value2.Wrap && value1.LevelOfDetailBias == value2.LevelOfDetailBias );
	}

	PatchMesh::PatchMesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	PatchMesh::PatchMesh( Device^ device, PatchInfo info, int patchCount, int vertexCount, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPatchMesh *result;
		pin_ptr<VertexElement> pinnedElements = &vertexDeclaration[0];

		HRESULT hr = D3DXCreatePatchMesh( reinterpret_cast<D3DXPATCHINFO*>( &info ), patchCount, vertexCount, 0, 
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ), device->InternalPointer, &result );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(result);
	}

	PatchMesh::PatchMesh( Mesh^ mesh )
	{
		ID3DXPatchMesh *result;

		HRESULT hr = D3DXCreateNPatchMesh( mesh->MeshPointer, &result );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(result);
	}

	PatchMesh^ PatchMesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXPatchMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadPatchMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&materialBuffer, &instanceBuffer, &materialCount, &mesh );

		if( RECORD_D3D9( hr ).IsFailure )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew PatchMesh( mesh );
	}

	PatchMesh^ PatchMesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXPatchMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadPatchMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&materialBuffer, NULL, &materialCount, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			materials = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew PatchMesh( mesh );
	}

	PatchMesh^ PatchMesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags )
	{
		ID3DXPatchMesh* mesh;

		HRESULT hr = D3DXLoadPatchMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), 
			device->InternalPointer, NULL, NULL, NULL, &mesh );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew PatchMesh( mesh );
	}

	PatchMesh^ PatchMesh::Clone( MeshFlags flags, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPatchMesh *result;
		pin_ptr<VertexElement> pinnedElements = &vertexDeclaration[0];

		HRESULT hr = InternalPointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ), &result );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew PatchMesh( result );
	}

	Result PatchMesh::GenerateAdjacency( float tolerance )
	{
		HRESULT hr = InternalPointer->GenerateAdjacency( tolerance );
		return RECORD_D3D9( hr );
	}

	array<VertexElement>^ PatchMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];

		HRESULT hr = InternalPointer->GetDeclaration( elementBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		// Apparently the returned decl does not include an End element. This is bizarre and confusing,
		// not to mention completely unexpected. We patch it up here.
		int count = D3DXGetDeclLength( elementBuffer ) + 1;
		array<VertexElement>^ elements = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		memcpy( pinnedElements, elementBuffer, count * sizeof(D3DVERTEXELEMENT9) );
		elements[count - 1] = VertexElement::VertexDeclarationEnd;

		return elements;
	}

	Device^ PatchMesh::GetDevice()
	{
		IDirect3DDevice9* device;

		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew Device( device );
	}

	IndexBuffer^ PatchMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;

		HRESULT hr = InternalPointer->GetIndexBuffer( &ib );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew IndexBuffer( ib );
	}

	VertexBuffer^ PatchMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;

		HRESULT hr = InternalPointer->GetVertexBuffer( &vb );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew VertexBuffer( vb );
	}

	PatchInfo PatchMesh::GetPatchInfo()
	{
		PatchInfo result;

		HRESULT hr = InternalPointer->GetPatchInfo( reinterpret_cast<D3DXPATCHINFO*>( &result ) );
		RECORD_D3D9( hr );

		return result;
	}

	Result PatchMesh::Optimize()
	{
		HRESULT hr = InternalPointer->Optimize( 0 );
		return RECORD_D3D9( hr );
	}

	DisplacementParameters PatchMesh::GetDisplacementParameters()
	{
		DisplacementParameters result;
		IDirect3DBaseTexture9 *texture;
		D3DTEXTUREFILTERTYPE minFilter;
		D3DTEXTUREFILTERTYPE magFilter;
		D3DTEXTUREFILTERTYPE mipFilter;
		D3DTEXTUREADDRESS wrap;
		DWORD lodBias;

		HRESULT hr = InternalPointer->GetDisplaceParam( &texture, &minFilter, &magFilter, &mipFilter, &wrap, &lodBias );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return result;

		result.Texture = gcnew Texture( reinterpret_cast<IDirect3DTexture9*>( texture ) );
		result.MinFilter = static_cast<TextureFilter>( minFilter );
		result.MagFilter = static_cast<TextureFilter>( magFilter );
		result.MipFilter = static_cast<TextureFilter>( mipFilter );
		result.Wrap = static_cast<TextureAddress>( wrap );
		result.LevelOfDetailBias = lodBias;

		return result;
	}

	Result PatchMesh::SetDisplacementParameters( DisplacementParameters parameters )
	{
		HRESULT hr = InternalPointer->SetDisplaceParam( reinterpret_cast<IDirect3DTexture9*>( parameters.Texture->InternalPointer ), 
			static_cast<D3DTEXTUREFILTERTYPE>( parameters.MinFilter ), static_cast<D3DTEXTUREFILTERTYPE>( parameters.MagFilter ),
			static_cast<D3DTEXTUREFILTERTYPE>( parameters.MipFilter ), static_cast<D3DTEXTUREADDRESS>( parameters.Wrap ), parameters.LevelOfDetailBias );
		return RECORD_D3D9( hr );
	}

	DataStream^ PatchMesh::LockAttributeBuffer( LockFlags flags )
	{
		DWORD *data;
		int faceCount = InternalPointer->GetNumPatches();
		
		HRESULT hr = InternalPointer->LockAttributeBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, faceCount * sizeof( DWORD ), true, !readOnly, false );
	}

	Result PatchMesh::UnlockAttributeBuffer()
	{
		HRESULT hr = InternalPointer->UnlockAttributeBuffer();
		return RECORD_D3D9( hr );
	}

	DataStream^ PatchMesh::LockIndexBuffer( LockFlags flags )
	{
		void *data;
		IDirect3DIndexBuffer9 *indexBuffer;
		
		HRESULT hr = InternalPointer->GetIndexBuffer( &indexBuffer );
		RECORD_D3D9( hr );
		D3DINDEXBUFFER_DESC description;
		hr = indexBuffer->GetDesc( &description );
		RECORD_D3D9( hr );
		indexBuffer->Release();
		
		hr = InternalPointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, description.Size, true, !readOnly, false );
	}

	Result PatchMesh::UnlockIndexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockIndexBuffer();
		return RECORD_D3D9( hr );
	}

	DataStream^ PatchMesh::LockVertexBuffer( LockFlags flags )
	{
		void *data;
		IDirect3DVertexBuffer9* vertexBuffer;

		HRESULT hr = InternalPointer->GetVertexBuffer( &vertexBuffer );
		RECORD_D3D9( hr );
		D3DVERTEXBUFFER_DESC description;
		hr = vertexBuffer->GetDesc( &description );
		RECORD_D3D9( hr );
		vertexBuffer->Release();
		
		hr = InternalPointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, description.Size, true, !readOnly, false );
	}

	Result PatchMesh::UnlockVertexBuffer()
	{
		HRESULT hr = InternalPointer->UnlockVertexBuffer();
		return RECORD_D3D9( hr );
	}

	Result PatchMesh::GetTessellationSize( float tessellationLevel, bool adaptive, [Out] int% triangleCount, [Out] int% vertexCount )
	{
		pin_ptr<int> pinnedTriCount = &triangleCount;
		pin_ptr<int> pinnedVertexCount = &vertexCount;

		HRESULT hr = InternalPointer->GetTessSize( tessellationLevel, adaptive, reinterpret_cast<DWORD*>( pinnedTriCount ), 
			reinterpret_cast<DWORD*>( pinnedVertexCount ) );
		return RECORD_D3D9( hr );
	}

	Result PatchMesh::Tessellate( float tessellationLevel, Mesh^ mesh )
	{
		HRESULT hr = InternalPointer->Tessellate( tessellationLevel, reinterpret_cast<ID3DXMesh*>( mesh->InternalPointer ) );
		return RECORD_D3D9( hr );
	}

	Result PatchMesh::Tessellate( Vector4 translation, int minimumLevel, int maximumLevel, Mesh^ mesh )
	{
		HRESULT hr = InternalPointer->TessellateAdaptive( reinterpret_cast<D3DXVECTOR4*>( &translation ), maximumLevel, minimumLevel, 
			reinterpret_cast<ID3DXMesh*>( mesh->InternalPointer ) );
		return RECORD_D3D9( hr );
	}

	int PatchMesh::ControlVerticesPerPatch::get()
	{
		return InternalPointer->GetControlVerticesPerPatch();
	}

	int PatchMesh::PatchCount::get()
	{
		return InternalPointer->GetNumPatches();
	}

	int PatchMesh::VertexCount::get()
	{
		return InternalPointer->GetNumVertices();
	}

	PatchMeshType PatchMesh::Type::get()
	{
		return static_cast<PatchMeshType>( InternalPointer->GetOptions() );
	}
}
}