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

#include "ObjectTable.h"
#include "InternalHelpers.h"
#include "ComObject.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;

namespace SlimDX
{
	static ObjectTable::ObjectTable()
	{
		m_Table = gcnew System::Collections::Generic::Dictionary<IntPtr, ObjectInfo>();

		AppDomain::CurrentDomain->DomainUnload += gcnew System::EventHandler( OnExit );
		AppDomain::CurrentDomain->ProcessExit += gcnew System::EventHandler( OnExit );
	}

	ObjectTable::ObjectTable()
	{
	}

	void ObjectTable::OnExit( Object^ sender, EventArgs^ e )
	{
		SLIMDX_UNREFERENCED_PARAMETER(sender);
		SLIMDX_UNREFERENCED_PARAMETER(e);

		String^ leakString = ReportLeaks();
		Debug::Write( leakString );
	}

	ComObject^ ObjectTable::Find( IntPtr nativeObject )
	{
		if( nativeObject == IntPtr::Zero )
			throw gcnew ArgumentNullException( "nativeObject" );

		if( m_Table->ContainsKey( nativeObject ) )
		{
			return m_Table[nativeObject].Handle;
		}

		return nullptr;
	}

	void ObjectTable::Add( ComObject^ obj )
	{
		ObjectInfo info;
		info.Handle = obj;
		info.IsDefaultPool = false;

		if( Configuration::EnableObjectTracking )
			info.Source = gcnew StackTrace( 2, true );

		m_Table->Add( obj->ComPointer, info );
	}

	void ObjectTable::Remove( ComObject^ obj )
	{
		m_Table->Remove( obj->ComPointer );
	}

	void ObjectTable::FlagAsDefaultPool( ComObject^ object )
	{
		m_Table[object->ComPointer].IsDefaultPool = true;
	}

	String^ ObjectTable::ReportLeaks()
	{
		String^ output = "";

		for each( KeyValuePair<IntPtr, ObjectInfo> pair in m_Table )
		{
			if( pair.Value.Source == nullptr )
				continue;

			output += String::Format( CultureInfo::InvariantCulture, "Object of type {0} was not disposed. Stack trace of object creation:\n", pair.Value.Handle->GetType() );
			for each( StackFrame^ frame in pair.Value.Source->GetFrames() )
			{
				if( frame->GetFileLineNumber() == 0 )
				{
					// Compiler autogenerated functions and the like can cause stack frames with no info;
					// that's the only time the line number is 0 and since it's not a useful frame to see,
					// we'll skip it
					continue;
				}

				output += String::Format( CultureInfo::InvariantCulture, "\t{0}({1},{2}): {3}\n",
					frame->GetFileName(),
					frame->GetFileLineNumber(),
					frame->GetFileColumnNumber(),
					frame->GetMethod() );
			}
		}

		output += String::Format( CultureInfo::InvariantCulture, "Total of {0} objects still alive.\n", m_Table->Count );
		return output;
	}

	Dictionary<IntPtr, ObjectInfo>::ValueCollection^ ObjectTable::Objects::get()
	{
		return m_Table->Values;
	}
}