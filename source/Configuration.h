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
#include "Result.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	/// <summary>
	/// Used to control global options that affect all of SlimDX.
	/// </summary>
	public ref class Configuration sealed
	{
	private:
		static System::Collections::Generic::Dictionary<Result,ResultWatchFlags>^ m_Watches;
	
		static Configuration();
		
		Configuration();
	
		[System::Diagnostics::Conditional( "DEBUG" )]
		static void SetDebugValues();

	internal:
		static bool TryGetResultWatch( Result result, [Out] ResultWatchFlags% flags );

	public:
		/// <summary>
		/// Gets or sets whether SlimDX is currently tracking call stacks from object creation. If set to false,
		/// objects will not carry a call stack from when they were created. The default value is false.
		/// </summary>
		/// <remarks>Object tracking is a useful debugging facility, but may have a significant negative
		/// impact on performance. It will default to enabled when the DEBUG symbol is defined.</remarks>
		static property bool EnableObjectTracking;

		/// <summary>
		/// Gets or sets whether SlimDX defaults to throwing exceptions on <see cref="Result">result codes</see>
		/// that indicate errors. The default value is true.
		/// </summary>
		static property bool ThrowOnError;

		/// <summary>
		/// Gets or sets whether SlimDX detects double disposal of objects. If set to true, SlimDX will throw
		/// an ObjectDisposedException when an already disposed object is disposed. If set to false, double
		/// disposals will be silently ignored. The default value is false.
		/// </summary>
		static property bool DetectDoubleDispose;

		/// <summary>
		/// Add a watch indicating the action to be taken when a method returns the
		/// specified <see cref="Result">result code</see> is returned.
		/// </summary>
		/// <param name="result">The result code to watch for.</param>
		/// <param name="flags">The action to take when the specified result code occurs.</param>
		static void AddResultWatch( Result result, ResultWatchFlags flags );

		/// <summary>
		/// Remove a watch on the specified <see cref="Result">result code</see>.
		/// If no watch was set, this call is ignored.
		/// </summary>
		/// <param>The result code to stop watching.</param>
		static void RemoveResultWatch( Result result );

		/// <summary>
		/// Clear out all watches on all <see cref="Result">result codes</see>.
		/// </summary>
		static void ClearResultWatches();
	};
}