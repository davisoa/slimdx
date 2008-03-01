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

#include "DeviceConstants.h"
#include "Enums.h"

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Describes the state of a mouse device.
		/// </summary>
		public ref class MouseState
		{
		internal:
			array<bool>^ buttons;

		public:
			MouseState()
			{
				buttons = gcnew array<bool>( 8 );
			}

			MouseState( int x, int y, int z )
			{
				X = x;
				Y = y;
				Z = z;
				buttons = gcnew array<bool>( 8 );
			}

			/// <summary>
			/// Gets the X axis of the mouse.
			/// </summary>
			property int X;

			/// <summary>
			/// Gets the Y axis of the mouse.
			/// </summary>
			property int Y;

			/// <summary>
			/// Gets the Z axis of the mouse.
			/// </summary>
			property int Z;

			/// <summary>
			/// Gets the state of the mouse buttons.
			/// </summary>
			array<bool>^ GetButtons()
			{
				return buttons;
			}

			bool IsPressed(int button) { return buttons[button]; }

			bool IsReleased(int button) { return !buttons[button]; }
		};
	}
}