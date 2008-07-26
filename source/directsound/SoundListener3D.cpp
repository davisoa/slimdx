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

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>
#include <d3dx9.h>

#include "../DataStream.h"
#include "../ComObject.h"
#include "../math/Vector3.h"

#include "Enums.h"
#include "ResultCode.h"
#include "DirectSound.h"
#include "DirectSoundException.h"

#include "SoundBuffer.h"
#include "SecondarySoundBuffer.h"
#include "SoundListener3D.h"
#include "Listener3DSettings.h"
#include "Listener3DOrientation.h"

namespace SlimDX
{
	namespace DirectSound
	{
		SoundListener3D::SoundListener3D( System::IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		SoundListener3D::SoundListener3D( IDirectSound3DListener *listener )
		{
			if( listener == NULL )
				throw gcnew System::ArgumentNullException( "listener" );

			IDirectSound3DListener8* dsListener;
			HRESULT hr = listener->QueryInterface( IID_IDirectSound3DListener8, reinterpret_cast<void**>( &dsListener ) );	
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			Construct(dsListener);
		}

		SoundListener3D::SoundListener3D( SoundBuffer^ soundBuffer )
		{
			IDirectSound3DListener8* listener;
			HRESULT hr = soundBuffer->InternalPointer->QueryInterface( IID_IDirectSound3DListener8, reinterpret_cast<void**>( &listener ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );
			
			Construct(listener);
		}

		SoundListener3D::SoundListener3D( SecondarySoundBuffer^ secondaryBuffer )
		{
			IDirectSound3DListener8* listener;
			HRESULT hr = secondaryBuffer->DS8Pointer->QueryInterface( IID_IDirectSound3DListener8, reinterpret_cast<void**>( &listener ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );
			
			Construct(listener);
		}

		SoundListener3D^ SoundListener3D::FromPointer( IDirectSound3DListener* pointer )
		{
			SoundListener3D^ tableEntry = safe_cast<SoundListener3D^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew SoundListener3D( pointer );
		}

		SoundListener3D^ SoundListener3D::FromPointer( System::IntPtr pointer )
		{
			SoundListener3D^ tableEntry = safe_cast<SoundListener3D^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew SoundListener3D( pointer );
		}

		SoundListener3D::~SoundListener3D()
		{
			Destruct();
		}

		void SoundListener3D::CommitDeferredSettings()
		{
			HRESULT hr = InternalPointer->CommitDeferredSettings();
			RECORD_DSOUND( hr );
		}

		Listener3DSettings SoundListener3D::AllParameters::get()
		{
			DS3DLISTENER result;
			result.dwSize = sizeof( DS3DLISTENER );
			HRESULT hr = InternalPointer->GetAllParameters( &result );
			RECORD_DSOUND( hr );

			return Listener3DSettings( result );
		}

		void SoundListener3D::AllParameters::set( Listener3DSettings value )
		{
			DS3DLISTENER result = value.ToUnmanaged();
			HRESULT hr = InternalPointer->SetAllParameters( &result, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		float SoundListener3D::DistanceFactor::get()
		{
			float distance = 0.0f;
			HRESULT hr = InternalPointer->GetDistanceFactor( &distance );
			RECORD_DSOUND( hr );

			return distance;
		}

		void SoundListener3D::DistanceFactor::set( float value )
		{
			HRESULT hr = InternalPointer->SetDistanceFactor( value, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		float SoundListener3D::DopplerFactor::get()
		{
			float doppler = 0.0f;
			HRESULT hr = InternalPointer->GetDopplerFactor( &doppler );
			RECORD_DSOUND( hr );

			return doppler;
		}

		void SoundListener3D::DopplerFactor::set( float value )
		{
			HRESULT hr = InternalPointer->SetDopplerFactor( value, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		float SoundListener3D::RolloffFactor::get()
		{
			float rolloff = 0.0f;
			HRESULT hr = InternalPointer->GetRolloffFactor( &rolloff );
			RECORD_DSOUND( hr );

			return rolloff;
		}

		void SoundListener3D::RolloffFactor::set( float value )
		{
			HRESULT hr = InternalPointer->SetRolloffFactor( value, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		Listener3DOrientation SoundListener3D::Orientation::get()
		{
			D3DVECTOR front = D3DVECTOR();
			D3DVECTOR top = D3DVECTOR();
			HRESULT hr = InternalPointer->GetOrientation( &front, &top );
			RECORD_DSOUND( hr );

			return Listener3DOrientation( front, top );
		}

		void SoundListener3D::Orientation::set( Listener3DOrientation value )
		{
			HRESULT hr = InternalPointer->SetOrientation( value.Front.X, value.Front.Y, value.Front.Z,
														  value.Top.X, value.Top.Y, value.Top.Z,
														  Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		Vector3 SoundListener3D::Position::get()
		{
			D3DVECTOR position = D3DVECTOR();
			HRESULT hr = InternalPointer->GetPosition( &position );
			RECORD_DSOUND( hr );

			return Vector3( position.x, position.y, position.z );
		}

		void SoundListener3D::Position::set( Vector3 value )
		{
			HRESULT hr = InternalPointer->SetPosition( value.X, value.Y, value.Z, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}

		Vector3 SoundListener3D::Velocity::get()
		{
			D3DVECTOR velocity = D3DVECTOR();
			HRESULT hr = InternalPointer->GetVelocity( &velocity );
			RECORD_DSOUND( hr );

			return Vector3( velocity.x, velocity.y, velocity.z );
		}

		void SoundListener3D::Velocity::set( Vector3 value )
		{
			HRESULT hr = InternalPointer->SetVelocity( value.X, value.Y, value.Z, Deferred ?  DS3D_DEFERRED : DS3D_IMMEDIATE );
			RECORD_DSOUND( hr );
		}
	}
}