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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class XFileSaveObject;
		ref class XFile;
		ref class XFileEnumerationObject;
		ref class XFileData;

		public ref class XFileSaveData : public ComObject
		{
			COMOBJECT(ID3DXFileSaveData, XFileSaveData);

		public:
			static XFileSaveData^ FromPointer( System::IntPtr pointer );

			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, array<System::Byte>^ data );
			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, System::IO::Stream^ data );

			Result AddDataReference( System::String^ name, System::Guid id );

			property System::Guid Id { System::Guid get(); }
			property System::String^ Name { System::String^ get(); }
			property XFileSaveObject^ SaveObject { XFileSaveObject^ get(); }
			property System::Guid Type { System::Guid get(); }
		};

		public ref class XFileSaveObject : public ComObject
		{
			COMOBJECT(ID3DXFileSaveObject, XFileSaveObject);

		public:
			static XFileSaveObject^ FromPointer( System::IntPtr pointer );

			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, array<System::Byte>^ data );
			XFileSaveData^ AddDataObject( System::Guid dataTemplate, System::String^ name, System::Guid id, System::IO::Stream^ data );
			XFile^ GetFile();
			Result Save();
		};

		public ref class XFile : public ComObject
		{
			COMOBJECT(ID3DXFile, XFile);

		public:
			XFile();
			static XFile^ FromPointer( System::IntPtr pointer );

			XFileEnumerationObject^ CreateEnumerationObject( System::String^ fileName, System::Runtime::InteropServices::CharSet charSet );
			XFileEnumerationObject^ CreateEnumerationObject( array<System::Byte>^ memory );
			XFileEnumerationObject^ CreateEnumerationObject( System::IO::Stream^ stream );
			XFileSaveObject^ CreateSaveObject( System::String^ fileName, System::Runtime::InteropServices::CharSet charSet, XFileFormat format );

			Result RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject );
			Result RegisterTemplates( array<System::Byte>^ memory );
			Result RegisterTemplates( System::IO::Stream^ memory );
			Result RegisterTemplates( System::String^ name );
		};

		public ref class XFileEnumerationObject : public ComObject
		{
			COMOBJECT(ID3DXFileEnumObject, XFileEnumerationObject);

		public:
			static XFileEnumerationObject^ FromPointer( System::IntPtr pointer );

			XFileData^ GetChild( int id );
			XFileData^ GetDataObject( System::Guid id );
			XFileData^ GetDataObject( System::String^ name );
			XFile^ GetFile();

			property int ChildCount { int get(); }
		};

		public ref class XFileData : public ComObject
		{
			COMOBJECT(ID3DXFileData, XFileData);

		public:
			static XFileData^ FromPointer( System::IntPtr pointer );

			XFileData^ GetChild( int id );
			XFileEnumerationObject^ GetEnumerationObject();

			DataStream^ Lock();
			Result Unlock();

			property int ChildCount { int get(); }
			property System::Guid Id { System::Guid get(); }
			property System::Guid Type { System::Guid get(); }
			property System::String^ Name { System::String^ get(); }
			property bool IsReference { bool get(); }
		};
	}
}