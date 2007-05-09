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
//#define 
#include <windows.h>
#include <dinput.h>

#include "DirectInput.h"
#include "Device.h"

namespace SlimDX
{
namespace DirectInput
{
	Guid FromGUID( const GUID& guid )
	{
		Guid result( guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], 
			guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );
		return result;
	}

	Guid SystemGuid::Keyboard::get()
	{
		return FromGUID( GUID_SysKeyboard );
	}

	Guid SystemGuid::Mouse::get()
	{
		return FromGUID( GUID_SysMouse );
	}

	Guid SystemGuid::Joystick::get()
	{
		return FromGUID( GUID_Joystick );
	}

	/*Guid SystemGuid::MouseEm::get()
	{
		return FromGUID( GUID_SysMouseEm );
	}

	Guid SystemGuid::MouseEm2::get()
	{
		return FromGUID( GUID_SysMouseEm2 );
	}

	Guid SystemGuid::KeyboardEm::get()
	{
		return FromGUID( GUID_SysKeyboardEm );
	}

	Guid SystemGuid::KeyboardEm2::get()
	{
		return FromGUID( GUID_SysKeyboardEm2 );
	}*/

	Device^ DirectInput::CreateDevice( Guid subsystem )
	{
		return gcnew Device( subsystem );
	}
}
}