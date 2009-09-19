#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <d3d11.h>
#include <d3dx11.h>

#include "DeviceContext11.h"
#include "UnorderedAccessView11.h"

#include "Scan.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	Scan::Scan( DeviceContext^ deviceContext, int maxElementScanSize, int maxScanCount )
	{
		if (deviceContext == nullptr)
			throw gcnew System::ArgumentNullException( "deviceContext" );

		ID3DX11Scan* nativeScan;
		D3DX11CreateScan( deviceContext->InternalPointer, maxElementScanSize, maxScanCount, &nativeScan );

		Construct( nativeScan );
	}

	void Scan::Direction::set( ScanDirection value )
	{
		InternalPointer->SetScanDirection( static_cast<D3DX11_SCAN_DIRECTION>( value ) );
	}

	void Scan::PerformScan( ScanDataType elementType, ScanOpCode operation, int numberOfElements, UnorderedAccessView^ src, UnorderedAccessView^ dest )
	{
		ID3D11UnorderedAccessView* nativeSrc = src == nullptr ? NULL : src->InternalPointer;
		ID3D11UnorderedAccessView* nativeDest = dest == nullptr ? NULL : dest->InternalPointer;

		InternalPointer->Scan( static_cast<D3DX11_SCAN_DATA_TYPE>( elementType ), static_cast<D3DX11_SCAN_OPCODE>( operation ), numberOfElements, nativeSrc, nativeDest );
	}

	void Scan::PerformMultiscan( ScanDataType elementType, ScanOpCode operation, int numberOfElements, int scanPitchInElements, int scanCount, UnorderedAccessView^ src, UnorderedAccessView^ dest )
	{
		ID3D11UnorderedAccessView* nativeSrc = src == nullptr ? NULL : src->InternalPointer;
		ID3D11UnorderedAccessView* nativeDest = dest == nullptr ? NULL : dest->InternalPointer;

		InternalPointer->Multiscan( static_cast<D3DX11_SCAN_DATA_TYPE>( elementType ), static_cast<D3DX11_SCAN_OPCODE>( operation ), numberOfElements, scanPitchInElements, scanCount, nativeSrc, nativeDest );
	}
}
}
