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
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "../SlimDXObject.h"
#include "Enums.h"

namespace SlimDX
{
	ref class DataStream;

	namespace DirectSound
	{
		ref class DirectSound;
		ref class WaveFormatExtended;

		public value class BufferDescription
		{
		internal:
			void Marshal( DSBUFFERDESC& desc );

		public:
			property int SizeInBytes;
			property BufferFlags Flags;
			property WaveFormatExtended^ Format;
			property Guid AlgorithmFor3D;
		};

		[StructLayout( LayoutKind::Sequential, Pack = 4 )]
		public value class BufferCaps
		{
			int Size;
			BufferFlags Flags;
			int SizeBytes;
			int UnlockTransferRate;
			int PlayCpuOverhead;
		};

		public ref class SoundBuffer : SlimDXObject
		{
			DXOBJECT(IDirectSoundBuffer);

		private:
			//While I believe the IDirectSoundBuffer can be safely cast to one of these, it's not
			//guaranteed to be safe to do so, so we'll just do the Right Thing (tm) and use QueryInterface
			//to get it and store it separately.
			IDirectSoundBuffer8* m_DS8Pointer;

			void SetDS8Pointer();

		internal:
			SoundBuffer( IDirectSoundBuffer* buffer );

		public:
			SoundBuffer( DirectSound^ dsound, BufferDescription desc );
			~SoundBuffer();

			void Initialize( DirectSound^ dsound, BufferDescription desc );
			//void AcquireResources( 
			void Restore();

			void Play( int priority, PlayFlags flags );
			void Stop();

			DataStream^ Lock( int offset, int sizeBytes, LockFlags flags, [Out] DataStream^% secondPart );
			void Unlock( DataStream^ firstPart, DataStream^ secondPart );

			void SetFormat( WaveFormatExtended^ format );
			WaveFormatExtended^ GetFormat();

			property int CurrentWritePosition
			{
				int get();
			}

			property int CurrentPlayPosition
			{
				int get();
				void set( int value );
			}

			property int Frequency
			{
				int get();
				void set( int value );
			}

			property int Volume
			{
				int get();
				void set( int value );
			}

			property int Pan
			{
				int get();
				void set( int value );
			}

			property BufferStatus Status
			{
				BufferStatus get();
			}
		};
	}
}