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
#include <vcclr.h>
#include <memory>

#include "../ComObject.h"
#include "../DataStream.h"
#include "../Utilities.h"

#include "Device.h"
#include "Mesh.h"
#include "MeshData.h"
#include "ProgressiveMesh.h"
#include "PatchMesh.h"
#include "MeshContainer.h"
#include "SkinInfo.h"
#include "IAllocateHierarchy.h"
#include "AnimationFrame.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	IAllocateHierarchyShim::IAllocateHierarchyShim( IAllocateHierarchy^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	HRESULT IAllocateHierarchyShim::CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame )
	{
		Frame^ frame;
		*ppNewFrame = NULL;

		try
		{
			frame = m_WrappedInterface->CreateFrame( gcnew String(Name) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
		 
		// return the unmanaged shim
		*ppNewFrame = frame->Pointer;

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData,
		const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer )
	{
		MeshContainer^ meshContainer;
		*ppNewMeshContainer = NULL;

		MeshData^ meshData;
		int count = 0;

		if( pMeshData->Type == D3DXMESHTYPE_MESH )
		{
			meshData = gcnew MeshData( Mesh::FromPointer( pMeshData->pMesh ) );
			meshData->Mesh->InternalPointer->AddRef();
			count = meshData->Mesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PMESH )
		{
			meshData = gcnew MeshData( ProgressiveMesh::FromPointer( pMeshData->pPMesh ) );
			meshData->ProgressiveMesh->InternalPointer->AddRef();
			count = meshData->ProgressiveMesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PATCHMESH )
		{
			meshData = gcnew MeshData( PatchMesh::FromPointer( pMeshData->pPatchMesh ) );
			meshData->PatchMesh->InternalPointer->AddRef();
			count = meshData->PatchMesh->PatchCount;
		}

		count *= 3;

		array<ExtendedMaterial>^ materials = gcnew array<ExtendedMaterial>( NumMaterials );
		array<EffectInstance>^ effects = gcnew array<EffectInstance>( NumMaterials );
		array<int>^ adjacency = gcnew array<int>( count );

		for( unsigned int i = 0; i < NumMaterials; i++ )
		{
			materials[i] = ExtendedMaterial::FromUnmanaged( pMaterials[i] );
			effects[i] = EffectInstance::FromUnmanaged( pEffectInstances[i] );
		}

		for( int i = 0; i < count; i++ )
			adjacency[i] = pAdjacency[i];

		SkinInfo^ skinInfo = nullptr;
		if(pSkinInfo != NULL)
		{
			skinInfo = SkinInfo::FromPointer( pSkinInfo );
			pSkinInfo->AddRef();
		}

		try
		{
			meshContainer = m_WrappedInterface->CreateMeshContainer( gcnew String(Name), meshData, materials, 
				effects, adjacency, skinInfo );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		// return the unmanaged shim
		*ppNewMeshContainer = meshContainer->Pointer; 

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::DestroyFrame( LPD3DXFRAME pFrameToFree )
	{
		try
		{
			m_WrappedInterface->DestroyFrame( ((FrameShim*)pFrameToFree)->GetFrame() );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree )
	{
		try
		{			
			m_WrappedInterface->DestroyMeshContainer( ((MeshContainerShim*)pMeshContainerToFree)->GetMeshContainer() );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}
}
}
