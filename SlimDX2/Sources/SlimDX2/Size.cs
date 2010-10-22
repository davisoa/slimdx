﻿// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Globalization;
using System.Runtime.InteropServices;

namespace SlimDX2
{
    /// <summary>
    ///   The maximum number of bytes to which a pointer can point. Use for a count that must span the full range of a pointer.
    ///   Equivalent to Windows type SIZE_T.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Size
    {
        private IntPtr _size;

        /// <summary>
        ///   Default constructor.
        /// </summary>
        /// <param name = "size">value to set</param>
        private unsafe Size(void* size)
        {
            _size = new IntPtr(size);
        }

        /// <summary>
        ///   Default constructor.
        /// </summary>
        /// <param name = "size">value to set</param>
        public Size(int size)
        {
            _size = new IntPtr(size);
        }

        /// <summary>
        ///   Default constructor.
        /// </summary>
        /// <param name = "size">value to set</param>
        public Size(long size)
        {
            _size = new IntPtr(size);
        }

        /// <summary>
        ///   Returns a <see cref = "System.String" /> that represents this instance.
        /// </summary>
        /// <returns>
        ///   A <see cref = "System.String" /> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format(CultureInfo.CurrentCulture, "{0}", _size);
        }

        /// <summary>
        ///   Returns a <see cref = "System.String" /> that represents this instance.
        /// </summary>
        /// <param name = "format">The format.</param>
        /// <returns>
        ///   A <see cref = "System.String" /> that represents this instance.
        /// </returns>
        public string ToString(string format)
        {
            if (format == null)
                return ToString();

            return string.Format(CultureInfo.CurrentCulture, "{0}", _size.ToString(format));
        }

        /// <summary>
        ///   Returns a hash code for this instance.
        /// </summary>
        /// <returns>
        ///   A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
        /// </returns>
        public override int GetHashCode()
        {
            return _size.ToInt32();
        }

        /// <summary>
        ///   Determines whether the specified <see cref = "Size" /> is equal to this instance.
        /// </summary>
        /// <param name = "other">The <see cref = "Size" /> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref = "Size" /> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(Size other)
        {
            return _size == other._size;
        }

        /// <summary>
        ///   Determines whether the specified <see cref = "System.Object" /> is equal to this instance.
        /// </summary>
        /// <param name = "value">The <see cref = "System.Object" /> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref = "System.Object" /> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public override bool Equals(object value)
        {
            if (value == null)
                return false;

            if (value.GetType() != GetType())
                return false;

            return Equals((Size) value);
        }

        /// <summary>
        ///   Adds two sizes.
        /// </summary>
        /// <param name = "left">The first size to add.</param>
        /// <param name = "right">The second size to add.</param>
        /// <returns>The sum of the two sizes.</returns>
        public static Size operator +(Size left, Size right)
        {
            return new Size(left._size.ToInt64() + right._size.ToInt64());
        }

        /// <summary>
        ///   Assert a size (return it unchanged).
        /// </summary>
        /// <param name = "value">The size to assert (unchange).</param>
        /// <returns>The asserted (unchanged) size.</returns>
        public static Size operator +(Size value)
        {
            return value;
        }

        /// <summary>
        ///   Subtracts two sizes.
        /// </summary>
        /// <param name = "left">The first size to subtract.</param>
        /// <param name = "right">The second size to subtract.</param>
        /// <returns>The difference of the two sizes.</returns>
        public static Size operator -(Size left, Size right)
        {
            return new Size(left._size.ToInt64() - right._size.ToInt64());
        }

        /// <summary>
        ///   Reverses the direction of a given size.
        /// </summary>
        /// <param name = "value">The size to negate.</param>
        /// <returns>A size facing in the opposite direction.</returns>
        public static Size operator -(Size value)
        {
            return new Size(-value._size.ToInt64());
        }

        /// <summary>
        ///   Scales a size by the given value.
        /// </summary>
        /// <param name = "value">The size to scale.</param>
        /// <param name = "scale">The amount by which to scale the size.</param>
        /// <returns>The scaled size.</returns>
        public static Size operator *(int scale, Size value)
        {
            return new Size(scale*value._size.ToInt64());
        }

        /// <summary>
        ///   Scales a size by the given value.
        /// </summary>
        /// <param name = "value">The size to scale.</param>
        /// <param name = "scale">The amount by which to scale the size.</param>
        /// <returns>The scaled size.</returns>
        public static Size operator *(Size value, int scale)
        {
            return new Size(scale*value._size.ToInt64());
        }

        /// <summary>
        ///   Scales a size by the given value.
        /// </summary>
        /// <param name = "value">The size to scale.</param>
        /// <param name = "scale">The amount by which to scale the size.</param>
        /// <returns>The scaled size.</returns>
        public static Size operator /(Size value, int scale)
        {
            return new Size(value._size.ToInt64()/scale);
        }

        /// <summary>
        ///   Tests for equality between two objects.
        /// </summary>
        /// <param name = "left">The first value to compare.</param>
        /// <param name = "right">The second value to compare.</param>
        /// <returns><c>true</c> if <paramref name = "left" /> has the same value as <paramref name = "right" />; otherwise, <c>false</c>.</returns>
        public static bool operator ==(Size left, Size right)
        {
            return left.Equals(right);
        }

        /// <summary>
        ///   Tests for inequality between two objects.
        /// </summary>
        /// <param name = "left">The first value to compare.</param>
        /// <param name = "right">The second value to compare.</param>
        /// <returns><c>true</c> if <paramref name = "left" /> has a different value than <paramref name = "right" />; otherwise, <c>false</c>.</returns>
        public static bool operator !=(Size left, Size right)
        {
            return !left.Equals(right);
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "int" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static implicit operator int(Size value)
        {
            return value._size.ToInt32();
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "long" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static implicit operator long(Size value)
        {
            return value._size.ToInt64();
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "int" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static implicit operator Size(int value)
        {
            return new Size(value);
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "long" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static implicit operator Size(long value)
        {
            return new Size(value);
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "IntPtr" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static explicit operator IntPtr(Size value)
        {
            return value._size;
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "void*" /> to <see cref = "Size" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static unsafe explicit operator Size(void* value)
        {
            return new Size(value);
        }

        /// <summary>
        ///   Performs an implicit conversion from <see cref = "Size" /> to <see cref = "void*" />.
        /// </summary>
        /// <param name = "value">The value.</param>
        /// <returns>The result of the conversion.</returns>
        public static unsafe explicit operator void*(Size value)
        {
            return (void*) value._size;
        }
    }
}