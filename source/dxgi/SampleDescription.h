/*
* Copyright (c) 2007-2010 SlimDX Group
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

namespace SlimDX
{
	namespace DXGI
	{	
		/// <summary>
		/// Describes multisample parameters.
		/// </summary>
		/// <unmanaged>DXGI_SAMPLE_DESC</unmanaged>
		public value class SampleDescription : System::IEquatable<SampleDescription>
		{
			int m_Count;
			int m_Quality;
		
		internal:
			SampleDescription( const DXGI_SAMPLE_DESC& native );
			
			DXGI_SAMPLE_DESC CreateNativeVersion();
			
		public:
			/// <summary>
			/// Gets or sets the number of samples per pixel.
			/// </summary>
			property int Count
			{
				int get();
				void set( int value );
			}
			
			/// <summary>
			/// Gets or sets the sample quality.
			/// </summary>
			property int Quality
			{
				int get();
				void set( int value );
			}
			
			/// <summary>
			/// Initializes a new instance of the <see cref="SampleDescription"/> structure.
			/// </summary>
			/// <param name="count">The sample count.</param>
			/// <param name="quality">The sample quality.</param>
			SampleDescription( int count, int quality );
			
			/// <summary>
			/// Converts the value of the object to its equivalent string representation.
			/// </summary>
			/// <returns>The string representation of the value of this instance.</returns>
			virtual System::String^ ToString() override;
			
			static bool operator == ( SampleDescription left, SampleDescription right );
			static bool operator != ( SampleDescription left, SampleDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( SampleDescription other );
			static bool Equals( SampleDescription% value1, SampleDescription% value2 );
		};
	}
};