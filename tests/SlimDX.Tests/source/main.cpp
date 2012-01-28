#include "stdafx.h"
/*
* Copyright (c) 2007-2012 SlimDX Group
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

int main(array<System::String ^> ^args)
{
	//TODO: Instead of sending empty values, we should
	//      turn the managed args array into the appropriate
	//      native data to send to Google Mock.
	int argc = 0;
	char** argv = 0;
	testing::InitGoogleMock( &argc, argv );

	//TODO: We set verbosity to "error" so that we don't see the warnings
	//      generated by 'unexpected' calls to QueryInterface, AddRef, and
	//      Release on our mocks. Should probably handle that more gracefully.
	testing::FLAGS_gmock_verbose = "error";
    return RUN_ALL_TESTS();
}
