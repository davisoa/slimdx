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

#include "../SlimDXException.h"

#define RECORD_DXGI(x) Result::Record<DXGIException^>( (x) )

namespace SlimDX
{
	namespace DXGI
	{
		/// <summary>
		/// Represents errors that occur in the DXGI subsystem.
		/// </summary>
		[System::Serializable]
		public ref class DXGIException : public SlimDXException
		{
		protected:
			DXGIException( System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context );
			
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX.DXGIException"/> class.
			/// </summary>
			DXGIException();
			
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX.DXGIException"/> class.
			/// </summary>
			/// <param name="message">The message describing the exception.</param>
			DXGIException( System::String^ message );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX.DXGIException"/> class.
			/// </summary>
			/// <param name="message">The message describing the exception.</param>
			/// <param name="innerException">The exception that caused this exception.</param>
			DXGIException( System::String^ message, System::Exception^ innerException );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX.DXGIException"/> class.
			/// </summary>
			/// <param name="result">The result code that caused this exception.</param>
			DXGIException( Result result );
		};
	}
}
