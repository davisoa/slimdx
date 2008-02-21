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

//using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	value class Vector2;
	value class Vector3;
	value class Vector4;
	value class Matrix;
	value class Plane;
	value class Quaternion;
	value class Rational;
	value class Ray;
	value class BoundingBox;
	value class BoundingSphere;
	value class BoundingFrustum;
	value class Color4;
	value class Color3;
	value class Float16;
}

#include "Color3.h"
#include "Color4.h"
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Rational.h"
#include "Ray.h"
#include "BoundingVolumes.h"
#include "Float16.h"
