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

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Contains parameters for noise supression in a capture buffer.
		/// </summary>		
		public value class NoiseSuppressParameters
		{
		internal:
			NoiseSuppressParameters( const DSCFXNoiseSuppress& value );
			DSCFXNoiseSuppress Marshal();

		public:
			/// <summary>
			/// Boolean value that specifies whether the effect is enabled.
			/// </summary>
			property bool Enable;
		};


		/// <summary>
		/// The CaptureEffectNoiseSuppress object is used to set and retrieve parameters on a capture buffer that supports noise suppression. This object requires Microsoft Windows XP or later.
		/// </summary>
		public ref class CaptureEffectNoiseSuppress : public ComObject
		{
			COMOBJECT(IDirectSoundCaptureFXNoiseSuppress, CaptureEffectNoiseSuppress);

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::CaptureEffectNoiseSuppress"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundCaptureFXNoiseSuppress pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static CaptureEffectNoiseSuppress^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::CaptureEffectNoiseSuppress"/> class.
			/// </summary>
			~CaptureEffectNoiseSuppress();

			/// <summary>
			/// Sets the enumerator to its initial position, which is before the first element in the collection.
			/// </summary>
			void Reset();

			/// <summary>
			/// Gets or sets he noise suppression parameters of a buffer.
			/// </summary>
			property NoiseSuppressParameters AllParameters
			{
				NoiseSuppressParameters get();
				void set( NoiseSuppressParameters value );
			}
		};
	}
}