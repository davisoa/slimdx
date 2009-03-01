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

#include "Utils.h"
#include "ObjectTracker.h"

namespace SlimDX
{
	//This provides a common base for all the DirectXObject template types, and allows
	//them to access a single set of config settings.
	public ref class DirectXBase abstract
	{
	  static DirectXBase()
		{
#ifdef _DEBUG
			EnableObjectTracking = true;
#else
			EnableObjectTracking = false;
#endif
		}
		
	protected:
		DirectXBase() { }

	public:
		static property bool EnableObjectTracking;
	};

	template<typename T>
	public ref class DirectXObject abstract : public DirectXBase
	{
	protected:
		DirectXObject()
		{
			if( EnableObjectTracking )
				ObjectTracker::Add( this );
		}

		DirectXObject( T* pointer ) : m_Pointer( pointer )
		{
			if( EnableObjectTracking )
				ObjectTracker::Add( this );
		}

		T* m_Pointer;

		void Destruct()
		{
			if( m_Pointer != NULL )
			    m_Pointer->Release();
			m_Pointer = NULL;

			if( EnableObjectTracking )
				ObjectTracker::Remove( this );
		}

	internal:
		property T* InternalPointer
		{
			T* get() { return m_Pointer; }
		}

	public:
		virtual ~DirectXObject() { };

		property bool Disposed { virtual bool get() abstract; }
		property IntPtr ComPointer { virtual IntPtr get() abstract; }
		virtual void DisposeHandler( Object^ sender, EventArgs^ e ) abstract;
	};
}

#define DXOBJECT_FUNCTIONS \
	property bool Disposed { virtual bool get() override { return m_Pointer == NULL; } } \
	property IntPtr ComPointer { virtual IntPtr get() override{ return IntPtr( m_Pointer ); } } \
	virtual void DisposeHandler( Object^ sender, EventArgs^ e ) override { delete this; }