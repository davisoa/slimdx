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
	namespace Direct3D9
	{
		ref class AdapterInformation;

		/// <summary>Implements a read-only collection of <see cref="AdapterInformation"/> instances.</summary>
		public ref class AdapterCollection : public System::Collections::Generic::ICollection<AdapterInformation^>
		{
		private:
			System::Collections::Generic::List<AdapterInformation^>^ list;

		internal:
			AdapterCollection( unsigned int adapterCount );

			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}

		public:
			/// <summary>
			/// Adds an item to the collection.
			/// </summary>
			/// <param name="item">The item to add to the collection.</param>
			/// <exception cref="System.NotSupportedException">Always thrown, since the collection is read-only.</exception>
			virtual void Add( AdapterInformation^ item ) { SLIMDX_UNREFERENCED_PARAMETER(item); throw gcnew System::NotSupportedException(); }
			
			/// <summary>
			/// Removes all items from the collection.
			/// </summary>
			/// <exception cref="System.NotSupportedException">Always thrown, since the collection is read-only.</exception>
			virtual void Clear() { throw gcnew System::NotSupportedException(); }
			
			/// <summary>
			/// Determines whether the collection contains the specified item.
			/// </summary>
			/// <param name="item">The item for which to search.</param>
			/// <returns><c>true</c> if the collection contains the item; otherwise, <c>false</c>.</returns>
			virtual bool Contains( AdapterInformation^ item ) { return list->Contains( item ); }
			
			/// <summary>
			/// Copies the elements of the collection to an array, starting at a particular array index.
			/// </summary>
			/// <param name="array">The destination array.</param>
			/// <param name="arrayIndex">The index at which to start copying items.</param>
			virtual void CopyTo( array<AdapterInformation^>^ array, int arrayIndex ) { list->CopyTo( array, arrayIndex ); }
			
			/// <summary>
			/// Removes an item from the collection.
			/// </summary>
			/// <param name="item">The item to remove.</param>
			/// <returns><c>true</c> if the item was removed from the collection; otherwise, <c>false</c>.</returns>
			/// <exception cref="System.NotSupportedException">Always thrown, since the collection is read-only.</exception>
			virtual bool Remove( AdapterInformation^ item ) { SLIMDX_UNREFERENCED_PARAMETER(item); throw gcnew System::NotSupportedException(); }

			/// <summary>
			/// Returns an enumerator that iterates through the collection.
			/// </summary>
			/// <returns>An enumerator that can be used to iterate through the collection.</returns>
			virtual System::Collections::Generic::IEnumerator<AdapterInformation^>^ GetEnumerator() { return list->GetEnumerator(); }

			/// <summary>
			/// Gets the number of items contained in the collection.
			/// </summary>
			virtual property int Count
			{
				int get() { return list->Count; }
			}

			/// <summary>
			/// Gets the <see cref="AdapterInformation"/> item at the specified index.
			/// </summary>
			/// <param name="index">The index of the item to retrieve.</param>
			property AdapterInformation^ default[int]
			{
				AdapterInformation^ get( int index )
				{
					return list[index];
				}
			}

			/// <summary>
			/// Gets a value indicating whether the collection is read-only.
			/// </summary>
			/// <value>This property is always <c>true</c>.</value>
			virtual property bool IsReadOnly
			{
				bool get() { return true; }
			}

			/// <summary>
			/// Gets the default <see cref="AdapterInformation"/> item.
			/// </summary>
			property AdapterInformation^ DefaultAdapter
			{
				AdapterInformation^ get() { return list[0]; }
			}
		};
	}
}