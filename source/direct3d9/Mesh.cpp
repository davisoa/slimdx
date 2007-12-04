/*
* Copyright (c) 2007 SlimDX Group
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
#include <vcclr.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "../DataStream.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "SkinInfo.h"

namespace SlimDX
{
namespace Direct3D9
{
	//Utility function to convert from D3D color to SlimDX color. Can't put it in ColorValue because
	//that thing is shared between D3D 9 and D3D 10.
	ColorValue ConvertColor( const D3DCOLORVALUE& color )
	{
		ColorValue cv;
		cv.Red = color.r;
		cv.Green = color.g;
		cv.Blue = color.b;
		cv.Alpha = color.a;

		return cv;
	}

	D3DCOLORVALUE ConvertColor( ColorValue color )
	{
		D3DCOLORVALUE cv;
		cv.r = color.Red;
		cv.g = color.Green;
		cv.b = color.Blue;
		cv.a = color.Alpha;

		return cv;
	}

	D3DXMATERIAL ExtendedMaterial::ToUnmanaged( ExtendedMaterial material )
	{
		D3DXMATERIAL result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( material.TextureFilename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		result.pTextureFilename = reinterpret_cast<LPSTR>( pinnedName );
		result.MatD3D.Ambient = ConvertColor( material.MaterialD3D.Ambient );
		result.MatD3D.Diffuse = ConvertColor( material.MaterialD3D.Diffuse );
		result.MatD3D.Specular = ConvertColor( material.MaterialD3D.Specular );
		result.MatD3D.Emissive = ConvertColor( material.MaterialD3D.Emissive );
		result.MatD3D.Power = material.MaterialD3D.Power;

		return result;
	}

	ExtendedMaterial ExtendedMaterial::FromUnmanaged( const D3DXMATERIAL &material )
	{
		ExtendedMaterial result;
		result.MaterialD3D.Diffuse = ConvertColor( material.MatD3D.Diffuse );
		result.MaterialD3D.Ambient = ConvertColor( material.MatD3D.Ambient );
		result.MaterialD3D.Specular = ConvertColor( material.MatD3D.Specular );
		result.MaterialD3D.Emissive = ConvertColor( material.MatD3D.Emissive );
		result.MaterialD3D.Power = material.MatD3D.Power;
		result.TextureFilename = gcnew String( material.pTextureFilename );

		return result;
	}

	array<ExtendedMaterial>^ ExtendedMaterial::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXMATERIAL* source  = reinterpret_cast<const D3DXMATERIAL*>( buffer->GetBufferPointer() );

		array<ExtendedMaterial>^ dest = gcnew array<ExtendedMaterial>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			Material m;
			m.Diffuse = ConvertColor( source[i].MatD3D.Diffuse );
			m.Ambient = ConvertColor( source[i].MatD3D.Ambient );
			m.Specular = ConvertColor( source[i].MatD3D.Specular );
			m.Emissive = ConvertColor( source[i].MatD3D.Emissive );
			m.Power = source[i].MatD3D.Power;
			dest[i].MaterialD3D = m;
			dest[i].TextureFilename = gcnew String( source[i].pTextureFilename );
		}

		return dest;
	}

	EffectInstance EffectInstance::FromUnmanaged( const D3DXEFFECTINSTANCE &effect )
	{
		EffectInstance result;

		result.EffectFilename = gcnew String( effect.pEffectFilename );
		result.Defaults = gcnew array<EffectDefault>( effect.NumDefaults );

		for( unsigned int i = 0; i < effect.NumDefaults; i++ )
		{
			result.Defaults[i].ParameterName = gcnew String( effect.pDefaults[i].pParamName );
			result.Defaults[i].Type = static_cast<EffectDefaultType>( effect.pDefaults[i].Type );
			result.Defaults[i].Value = gcnew DataStream( effect.pDefaults[i].pValue, effect.pDefaults[i].NumBytes, true, false, true );
		}

		return result;
	}

	D3DXEFFECTINSTANCE EffectInstance::ToUnmanaged( EffectInstance effect )
	{
		D3DXEFFECTINSTANCE result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.EffectFilename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		int count = effect.Defaults->Length;

		result.pEffectFilename = reinterpret_cast<LPSTR>( pinnedName );
		result.pDefaults = new D3DXEFFECTDEFAULT[count];

		for( int i = 0; i < effect.Defaults->Length; i++ )
		{
			array<unsigned char>^ nameBytes2 = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.Defaults[i].ParameterName );
			pin_ptr<unsigned char> pinnedName2 = &nameBytes2[0];

			result.pDefaults[i].pParamName = reinterpret_cast<LPSTR>( pinnedName2 );
			result.pDefaults[i].Type = static_cast<D3DXEFFECTDEFAULTTYPE>( effect.Defaults[i].Type );
			result.pDefaults[i].NumBytes = static_cast<DWORD>( effect.Defaults[i].Value->Length );
			result.pDefaults[i].pValue = effect.Defaults[i].Value->RawPointer;
		}

		return result;
	}

	array<EffectInstance>^ EffectInstance::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXEFFECTINSTANCE* source  = reinterpret_cast<const D3DXEFFECTINSTANCE*>( buffer->GetBufferPointer() );

		array<EffectInstance>^ dest = gcnew array<EffectInstance>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			dest[i].EffectFilename = gcnew String( source[i].pEffectFilename );
			dest[i].Defaults = gcnew array<EffectDefault>( source[i].NumDefaults );
			for( unsigned int x = 0; x < source[i].NumDefaults; ++x )
			{
				dest[i].Defaults[x].ParameterName = gcnew String( source[i].pDefaults[x].pParamName );
				dest[i].Defaults[x].Type = static_cast<EffectDefaultType>( source[i].pDefaults[x].Type );
				dest[i].Defaults[x].Value = gcnew DataStream( source[i].pDefaults[x].pValue, source[i].pDefaults[x].NumBytes, true, false, true );
			}
		}

		return dest;
	}

	BaseMesh::BaseMesh( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXBaseMesh, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXBaseMesh*>( result );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &elements[0];

		HRESULT hr = m_Pointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = m_Pointer->CloneMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( fvf ), 
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	void BaseMesh::DrawSubset( int subset )
	{
		HRESULT hr = m_Pointer->DrawSubset( subset );
		GraphicsException::CheckHResult( hr );
	}

	Device^ BaseMesh::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	IndexBuffer^ BaseMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;
		HRESULT hr = m_Pointer->GetIndexBuffer( &ib );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew IndexBuffer( ib );
	}

	VertexBuffer^ BaseMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = m_Pointer->GetVertexBuffer( &vb );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexBuffer( vb );
	}

	array<VertexElement>^ BaseMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];
		HRESULT hr = m_Pointer->GetDeclaration( elementBuffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
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

	array<AttributeRange>^ BaseMesh::GetAttributeTable()
	{
		DWORD count = 0;
		HRESULT hr = m_Pointer->GetAttributeTable( NULL, &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) || count == 0 )
			return nullptr;

		array<AttributeRange>^ attribTable = gcnew array<AttributeRange>( count );
		pin_ptr<AttributeRange> pinnedTable = &attribTable[0];
		hr = m_Pointer->GetAttributeTable( reinterpret_cast<D3DXATTRIBUTERANGE*>( pinnedTable ), &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return attribTable;
	}

	DataStream^ BaseMesh::LockIndexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = 6 * FaceCount;
		if( (CreationOptions & MeshFlags::Use32Bit) == MeshFlags::Use32Bit )
			size *= 2;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockIndexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockIndexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ BaseMesh::LockVertexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = BytesPerVertex * VertexCount;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockVertexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockVertexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	array<int>^ BaseMesh::GenerateAdjacency( float epsilon )
	{
		// allocate the array to write the adjacency into
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = m_Pointer->GenerateAdjacency( epsilon, reinterpret_cast<DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	array<int>^ BaseMesh::ConvertAdjacencyToPointReps( array<int>^ adjacency )
	{
		array<int>^ points = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = m_Pointer->ConvertAdjacencyToPointReps( reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedPoints ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return points;
	}

	array<int>^ BaseMesh::ConvertPointRepsToAdjacency( array<int>^ points )
	{
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = m_Pointer->ConvertPointRepsToAdjacency( reinterpret_cast<const DWORD*>( pinnedPoints ),
			reinterpret_cast<DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	void BaseMesh::UpdateSemantics( array<VertexElement>^ elements )
	{
		pin_ptr<VertexElement> pinnedElements = &elements[0];

		HRESULT hr = m_Pointer->UpdateSemantics( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ) );
		GraphicsException::CheckHResult( hr );
	}

	IndexBuffer^ BaseMesh::ConvertSubsetToSingleStrip( int attributeId, MeshFlags options, [Out] int% indexCount )
	{
		IDirect3DIndexBuffer9 *result;
		DWORD count;

		HRESULT hr = D3DXConvertMeshSubsetToSingleStrip( m_Pointer, attributeId, static_cast<DWORD>( options ),
			&result, &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			indexCount = 0;
			return nullptr;
		}

		indexCount = count;
		return gcnew IndexBuffer( result );
	}

	IndexBuffer^ BaseMesh::ConvertSubsetToStrips( int attributeId, MeshFlags options, [Out] int% indexCount,
		[Out] array<int>^% stripLengths )
	{
		IDirect3DIndexBuffer9 *result;
		ID3DXBuffer *buffer;
		DWORD numIndices;
		DWORD numStrips;

		HRESULT hr = D3DXConvertMeshSubsetToStrips( m_Pointer, attributeId, static_cast<DWORD>( options ),
			&result, &numIndices, &buffer, &numStrips );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			indexCount = 0;
			stripLengths = nullptr;
			return nullptr;
		}

		indexCount = numIndices;
		stripLengths = ( gcnew DataStream( buffer ) )->ReadRange<int>( numStrips );
		return gcnew IndexBuffer( result );
	}

	bool BaseMesh::Intersects( Ray ray, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits )
	{
		ID3DXBuffer *allHits;
		BOOL result;
		FLOAT dist;
		DWORD count;
		DWORD face;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, &face, NULL, NULL, &dist, &allHits, &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			hits = nullptr;
			faceIndex = 0;
			distance = 0;
			return false;
		}

		faceIndex = face;
		distance = dist;

		hits = ( gcnew DataStream( allHits ) )->ReadRange<IntersectInformation>( count );

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::Intersects( Ray ray, [Out] float% distance )
	{
		BOOL result;
		FLOAT dist;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, &dist, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			distance = 0;
			return false;
		}

		distance = dist;
		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::Intersects( Ray ray )
	{
		BOOL result;

		HRESULT hr = D3DXIntersect( InternalPointer, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, NULL, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return false;

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId, [Out] float% distance, [Out] int% faceIndex, [Out] array<IntersectInformation>^% hits )
	{
		ID3DXBuffer *allHits;
		BOOL result;
		FLOAT dist;
		DWORD count;
		DWORD face;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, &face, NULL, NULL, &dist, &allHits, &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			hits = nullptr;
			faceIndex = 0;
			distance = 0;
			return false;
		}

		faceIndex = face;
		distance = dist;
		hits = ( gcnew DataStream( allHits ) )->ReadRange<IntersectInformation>( count );

		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId, [Out] float% distance )
	{
		BOOL result;
		FLOAT dist;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, &dist, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			distance = 0;
			return false;
		}

		distance = dist;
		if( result )
			return true;
		else
			return false;
	}

	bool BaseMesh::IntersectsSubset( Ray ray, int attributeId )
	{
		BOOL result;

		HRESULT hr = D3DXIntersectSubset( InternalPointer, attributeId, reinterpret_cast<const D3DXVECTOR3*>( &ray.Position ),
			reinterpret_cast<const D3DXVECTOR3*>( &ray.Direction ), &result, NULL, NULL, NULL, NULL, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return false;

		if( result )
			return true;
		else
			return false;
	}

	int BaseMesh::FaceCount::get()
	{
		return m_Pointer->GetNumFaces();
	}

	int BaseMesh::VertexCount::get()
	{
		return m_Pointer->GetNumVertices();
	}

	SlimDX::Direct3D9::VertexFormat BaseMesh::VertexFormat::get()
	{
		return static_cast<SlimDX::Direct3D9::VertexFormat>( m_Pointer->GetFVF() );
	}

	int BaseMesh::BytesPerVertex::get()
	{
		return m_Pointer->GetNumBytesPerVertex();
	}

	MeshFlags BaseMesh::CreationOptions::get()
	{
		return static_cast<MeshFlags>( m_Pointer->GetOptions() );
	}

	Mesh::Mesh( ID3DXMesh* mesh ) : BaseMesh( mesh )
	{
	}

	Mesh::Mesh( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXMesh, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXMesh*>( result );
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, array<VertexElement>^ vertexDecl )
	{
		ID3DXMesh* mesh;
		pin_ptr<VertexElement> pinnedDecl = &vertexDecl[0];

		HRESULT hr = D3DXCreateMesh( numFaces, numVertices, static_cast<DWORD>( options ),
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = mesh;
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = D3DXCreateMeshFVF( numFaces, numVertices, static_cast<DWORD>( options ), 
			static_cast<DWORD>( fvf ), device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = mesh;
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<int>^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		// figure out how many effect instances there are, and get them out of the buffer
		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ),
			device->InternalPointer, NULL, &materialBuffer, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ),
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<int>^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, adjacency, materials, effectInstances );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, materials, effectInstances );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, materials );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<int>^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromXW( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			materials = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshFromXW( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( flags ), 
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<int>^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			materials = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags )
	{
		ID3DXMesh* mesh;

		HRESULT hr = D3DXLoadMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), 
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<int>^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances, [Out] SkinInfo^% skinInfo )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &skin, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			skinInfo = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adjacencyBuffer ) )->ReadRange<int>( mesh->GetNumFaces() * 3 );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		skinInfo = gcnew SkinInfo( skin );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances, [Out] SkinInfo^% skinInfo )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &skin, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			skinInfo = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		skinInfo = gcnew SkinInfo( skin );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials, [Out] SkinInfo^% skinInfo )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		
		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, NULL, &materialCount, &skin, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			materials = nullptr;
			skinInfo = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		skinInfo = gcnew SkinInfo( skin );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromXFile( Device^ device, XFileData^ xfile, MeshFlags flags, [Out] SkinInfo^% skinInfo )
	{
		ID3DXMesh* mesh;
		ID3DXSkinInfo* skin;

		HRESULT hr = D3DXLoadSkinMeshFromXof( xfile->InternalPointer, static_cast<DWORD>( flags ), 
			device->InternalPointer, NULL, NULL, NULL, NULL, &skin, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			skinInfo = nullptr;
			return nullptr;
		}

		skinInfo = gcnew SkinInfo( skin );

		return gcnew Mesh( mesh );
	}

	void Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( MeshPointer, static_cast<DWORD>( options ) );
		GraphicsException::CheckHResult( hr );
	}

	Mesh^ Mesh::CreateBox( Device^ device, float width, float height, float depth, [Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateBox( device->InternalPointer, width, height, depth, &result, &adj );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateBox( Device^ device, float width, float height, float depth )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCreateBox( device->InternalPointer, width, height, depth, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateCylinder( Device^ device, float radius1, float radius2, float length, int slices, 
		int stacks, [Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateCylinder( device->InternalPointer, radius1, radius2, length, slices, stacks, &result, &adj );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateCylinder( Device^ device, float radius1, float radius2, float length, int slices, int stacks )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCreateCylinder( device->InternalPointer, radius1, radius2, length, slices, stacks, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateSphere( Device^ device, float radius, int slices, int stacks, [Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateSphere( device->InternalPointer, radius, slices, stacks, &result, &adj );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateSphere( Device^ device, float radius, int slices, int stacks )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCreateSphere( device->InternalPointer, radius, slices, stacks, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateTeapot( Device^ device, [Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTeapot( device->InternalPointer, &result, &adj );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateTeapot( Device^ device )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCreateTeapot( device->InternalPointer, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateTorus( Device^ device, float innerRadius, float outerRadius, int sides, 
		int rings, [Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		HRESULT hr = D3DXCreateTorus( device->InternalPointer, innerRadius, outerRadius, sides, rings, &result, &adj );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateTorus( Device^ device, float innerRadius, float outerRadius, int sides, int rings )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCreateTorus( device->InternalPointer, innerRadius, outerRadius, sides, rings, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion,
		[Out] array<int>^% adjacency, [Out] array<GlyphMetricsFloat>^% glyphMetrics )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );
		pin_ptr<GlyphMetricsFloat> pinnedMetrics = &glyphMetrics[0];

		HDC hdc = CreateCompatibleDC( NULL );
		HFONT newFont;
		HFONT oldFont;
		if( hdc == NULL )
			throw gcnew OutOfMemoryException();

		newFont = static_cast<HFONT>( font->ToHfont().ToPointer() );
		oldFont = static_cast<HFONT>( SelectObject( hdc, newFont ) );		

		HRESULT hr = D3DXCreateText( device->InternalPointer, hdc, reinterpret_cast<LPCWSTR>( pinnedText ),
			deviation, extrusion, &result, &adj, reinterpret_cast<LPGLYPHMETRICSFLOAT>( pinnedMetrics ) );
		GraphicsException::CheckHResult( hr );

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			glyphMetrics = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion,
		[Out] array<int>^% adjacency )
	{
		ID3DXMesh *result;
		ID3DXBuffer *adj;

		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );

		HDC hdc = CreateCompatibleDC( NULL );
		HFONT newFont;
		HFONT oldFont;
		if( hdc == NULL )
			throw gcnew OutOfMemoryException();

		newFont = static_cast<HFONT>( font->ToHfont().ToPointer() );
		oldFont = static_cast<HFONT>( SelectObject( hdc, newFont ) );		

		HRESULT hr = D3DXCreateText( device->InternalPointer, hdc, reinterpret_cast<LPCWSTR>( pinnedText ),
			deviation, extrusion, &result, &adj, NULL );
		GraphicsException::CheckHResult( hr );

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			return nullptr;
		}

		adjacency = ( gcnew DataStream( adj ) )->ReadRange<int>( result->GetNumFaces() * 3 );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::CreateText( Device^ device, Font^ font, String^ text, float deviation, float extrusion )
	{
		ID3DXMesh *result;

		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );

		HDC hdc = CreateCompatibleDC( NULL );
		HFONT newFont;
		HFONT oldFont;
		if( hdc == NULL )
			throw gcnew OutOfMemoryException();

		newFont = static_cast<HFONT>( font->ToHfont().ToPointer() );
		oldFont = static_cast<HFONT>( SelectObject( hdc, newFont ) );		

		HRESULT hr = D3DXCreateText( device->InternalPointer, hdc, reinterpret_cast<LPCWSTR>( pinnedText ),
			deviation, extrusion, &result, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		SelectObject( hdc, oldFont );
		DeleteObject( newFont );
		DeleteDC( hdc );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	DataStream^ Mesh::LockAttributeBuffer( LockFlags flags )
	{
		DWORD *data;
		int faceCount = MeshPointer->GetNumFaces();
		
		HRESULT hr = MeshPointer->LockAttributeBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, faceCount * sizeof( DWORD ), true, !readOnly, false );
	}

	void Mesh::UnlockAttributeBuffer()
	{
		HRESULT hr = MeshPointer->UnlockAttributeBuffer();
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::SetAttributeTable( array<AttributeRange>^ table )
	{
		pin_ptr<AttributeRange> pinnedTable = &table[0];

		HRESULT hr = MeshPointer->SetAttributeTable( reinterpret_cast<const D3DXATTRIBUTERANGE*>( pinnedTable ), table->Length );
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut,
		[Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ),
			reinterpret_cast<DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			faceRemap = nullptr;
			vertexRemap = nullptr;
		}
		else
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% faceRemap, 
		[Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), NULL,
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
		}
		else
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ),
			reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			adjacencyOut = nullptr;
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, IntPtr adjacencyIn )
	{
		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), NULL, NULL, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut,
		[Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			faceRemap = nullptr;
			vertexRemap = nullptr;
		}
		else
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% faceRemap, 
		[Out] array<int>^% vertexRemap )
	{
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), NULL,
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
		}
		else
			vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( VertexCount );
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			adjacencyOut = nullptr;
	}

	void Mesh::OptimizeInPlace( MeshOptimizeFlags flags, array<int>^ adjacencyIn )
	{
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->OptimizeInplace( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), NULL, NULL, NULL );
		GraphicsException::CheckHResult( hr );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut,
		[Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ),
			reinterpret_cast<DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% faceRemap, 
		[Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), NULL,
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		ID3DXMesh *result;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ),
			reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			return nullptr;
		}

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, IntPtr adjacencyIn )
	{
		ID3DXMesh *result;

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), NULL, NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut,
		[Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% faceRemap, 
		[Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), NULL,
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			faceRemap = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		ID3DXMesh *result;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			return nullptr;
		}

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Optimize( MeshOptimizeFlags flags, array<int>^ adjacencyIn )
	{
		ID3DXMesh *result;
		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), NULL, NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] String^% errorsAndWarnings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *errors;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), &result,
			reinterpret_cast<DWORD*>( pinnedAdjOut ), &errors );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			errorsAndWarnings = nullptr;
			return nullptr;
		}

		errorsAndWarnings = Utils::BufferToString( errors );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, array<int>^ adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), &result,
			reinterpret_cast<DWORD*>( pinnedAdjOut ), NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			return nullptr;
		}

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, array<int>^ adjacencyIn )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( pinnedAdjIn ), &result, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut, [Out] String^% errorsAndWarnings )
	{
		ID3DXMesh *result;
		ID3DXBuffer *errors;

		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), &result,
			reinterpret_cast<DWORD*>( pinnedAdjOut ), &errors );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			errorsAndWarnings = nullptr;
			return nullptr;
		}

		errorsAndWarnings = Utils::BufferToString( errors );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, IntPtr adjacencyIn, [Out] array<int>^% adjacencyOut )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), &result,
			reinterpret_cast<DWORD*>( pinnedAdjOut ), NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			adjacencyOut = nullptr;
			return nullptr;
		}

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Clean( CleanType type, IntPtr adjacencyIn )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXCleanMesh( static_cast<D3DXCLEANTYPE>( type ), MeshPointer, 
			reinterpret_cast<const DWORD*>( adjacencyIn.ToPointer() ), &result, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	void Mesh::ComputeNormals( array<int>^ adjacency )
	{
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXComputeNormals( MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::ComputeNormals()
	{
		HRESULT hr = D3DXComputeNormals( MeshPointer, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap, array<int>^ adjacency )
	{
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXComputeTangent( MeshPointer, textureStage, tangentIndex, binormalIndex, wrap,
			reinterpret_cast<const DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );
	}

	void Mesh::ComputeTangent( int textureStage, int tangentIndex, int binormalIndex, bool wrap )
	{
		HRESULT hr = D3DXComputeTangent( MeshPointer, textureStage, tangentIndex, binormalIndex, wrap, NULL );
		GraphicsException::CheckHResult( hr );
	}

	Mesh^ Mesh::ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
		int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
		int normalOutIndex, TangentOptions options, array<int>^ adjacency, float partialEdgeThreshold,
		float singularPointThreshold, float normalEdgeThreshold, [Out] array<int>^% vertexMapping )
	{
		ID3DXMesh *result;
		ID3DXBuffer *vertex;

		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXComputeTangentFrameEx( MeshPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), reinterpret_cast<const DWORD*>( pinnedAdj ),
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, &vertex );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			vertexMapping = nullptr;
			return nullptr;
		}

		vertexMapping = ( gcnew DataStream( vertex ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ Mesh::ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
		int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
		int normalOutIndex, TangentOptions options, array<int>^ adjacency, float partialEdgeThreshold,
		float singularPointThreshold, float normalEdgeThreshold )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXComputeTangentFrameEx( MeshPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), reinterpret_cast<const DWORD*>( pinnedAdj ),
			partialEdgeThreshold, singularPointThreshold, normalEdgeThreshold, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::ComputeTangentFrame( int textureInSemantic, int textureInIndex, int partialOutSemanticU, 
		int partialOutIndexU, int partialOutSemanticV, int partialOutIndexV, int normalOutSemantic,
		int normalOutIndex, TangentOptions options, float partialEdgeThreshold, float singularPointThreshold, 
		float normalEdgeThreshold )
	{
		ID3DXMesh *result;

		HRESULT hr = D3DXComputeTangentFrameEx( MeshPointer, textureInSemantic, textureInIndex,
			partialOutSemanticU, partialOutIndexU, partialOutSemanticV, partialOutIndexV, normalOutSemantic,
			normalOutIndex, static_cast<DWORD>( options ), NULL, partialEdgeThreshold, singularPointThreshold, 
			normalEdgeThreshold, &result, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		D3DVERTEXELEMENT9 *decl = NULL;
		ID3DXMesh **input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;
		pin_ptr<VertexElement> pinnedDecl = nullptr;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		if( geometryTransforms != nullptr )
		{
			pinnedGeo = &geometryTransforms[0];
			geoXForms = reinterpret_cast<D3DXMATRIX*>( pinnedGeo );
		}

		if( textureTransforms != nullptr )
		{
			pinnedTexture = &textureTransforms[0];
			textureXForms = reinterpret_cast<D3DXMATRIX*>( pinnedTexture );
		}

		if( vertexDeclaration != nullptr )
		{
			pinnedDecl = &vertexDeclaration[0];
			decl = reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl );
		}

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, decl, device->InternalPointer, &result );
		GraphicsException::CheckHResult( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options, array<Matrix>^ geometryTransforms,
		array<Matrix>^ textureTransforms )
	{
		ID3DXMesh *result;
		D3DXMATRIX *geoXForms = NULL;
		D3DXMATRIX *textureXForms = NULL;
		ID3DXMesh **input;

		pin_ptr<Matrix> pinnedGeo = nullptr;
		pin_ptr<Matrix> pinnedTexture = nullptr;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		if( geometryTransforms != nullptr )
		{
			pinnedGeo = &geometryTransforms[0];
			geoXForms = reinterpret_cast<D3DXMATRIX*>( pinnedGeo );
		}

		if( textureTransforms != nullptr )
		{
			pinnedTexture = &textureTransforms[0];
			textureXForms = reinterpret_cast<D3DXMATRIX*>( pinnedTexture );
		}

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), geoXForms,
			textureXForms, NULL, device->InternalPointer, &result );
		GraphicsException::CheckHResult( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Concatenate( Device^ device, array<Mesh^>^ meshes, MeshFlags options )
	{
		ID3DXMesh *result;
		ID3DXMesh **input;

		input = new ID3DXMesh*[meshes->Length];
		for( int i = 0; i < meshes->Length; i++ )
			input[i] = meshes[i]->MeshPointer;

		HRESULT hr = D3DXConcatenateMeshes( input, meshes->Length, static_cast<DWORD>( options ), NULL,
			NULL, NULL, device->InternalPointer, &result );
		GraphicsException::CheckHResult( hr );

		delete[] input;

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	void Mesh::Save( String^ fileName, array<int>^ adjacency, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects, XFileFormat format, CharSet charSet )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<int> pinnedAdjacency = &adjacency[0];

		D3DXMATERIAL *nativeMaterials = new D3DXMATERIAL[materials->Length];
		for( int i = 0; i < materials->Length; i++ )
			nativeMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );

		D3DXEFFECTINSTANCE *nativeEffects = new D3DXEFFECTINSTANCE[effects->Length];
		for( int i = 0; i < effects->Length; i++ )
			nativeEffects[i] = EffectInstance::ToUnmanaged( effects[i] );

		DWORD f = static_cast<DWORD>( format );
		if( charSet == CharSet::Unicode )
			f |= D3DXF_FILESAVE_TOWFILE;
		else
			f |= D3DXF_FILESAVE_TOFILE;

		HRESULT hr = D3DXSaveMeshToX( reinterpret_cast<LPCWSTR>( pinnedName ), MeshPointer, 
			reinterpret_cast<const DWORD*>( pinnedAdjacency ), nativeMaterials, nativeEffects, materials->Length, f );
		GraphicsException::CheckHResult( hr );

		delete[] nativeMaterials;
		delete[] nativeEffects;
	}

	void Mesh::Save( String^ fileName, array<int>^ adjacency, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects, XFileFormat format )
	{
		Save( fileName, adjacency, materials, effects, format, CharSet::Auto );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights,
		array<float>^ vertexWeights, int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<float> pinnedVW = &vertexWeights[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), reinterpret_cast<const FLOAT*>( pinnedVW ),
			minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights,
		int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ Mesh::Simplify( Mesh^ mesh, array<int>^ adjacency, int minimumValue, MeshSimplification options )
	{
		ID3DXMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXSimplifyMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}
}
}