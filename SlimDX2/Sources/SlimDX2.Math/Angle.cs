﻿/*
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
using System;
using System.Globalization;


namespace SlimDX2.Math
{
    /// <summary>
    /// Represents a unit independant angle using a single-precision floating-point
    /// internal representation.
    /// </summary>
    [Serializable]
    public struct AngleSingle : IComparable, IComparable<AngleSingle>, IEquatable<AngleSingle>, IFormattable
    {
        /// <summary>
        /// A value that specifies the size of a single degree.
        /// </summary>
        public const float Degree = 0.002777777777777778f;

        /// <summary>
        /// A value that specifies the size of a single minute.
        /// </summary>
        public const float Minute = 0.000046296296296296f;

        /// <summary>
        /// A value that specifies the size of a single second.
        /// </summary>
        public const float Second = 0.000000771604938272f;

        /// <summary>
        /// A value that specifies the size of a single radian.
        /// </summary>
        public const float Radian = 0.159154943091895336f;

        /// <summary>
        /// A value that specifies the size of a single milliradian.
        /// </summary>
        public const float Milliradian = 0.0001591549431f;

        /// <summary>
        /// A value that specifies the size of a single gradian.
        /// </summary>
        public const float Gradian = 0.0025f;

        /// <summary>
        /// The internal representation of the angle.
        /// </summary>
        float radians;

        /// <summary>
        /// Initializes a new instance of the SlimMath.AngleSingle structure with the
        /// given unit dependant angle and unit type.
        /// </summary>
        /// <param name="angle">A unit dependant measure of the angle.</param>
        /// <param name="type">The type of unit the angle argument is.</param>
        public AngleSingle(float angle, AngleType type)
        {
            switch (type)
            {
                case AngleType.Revolution:
                    radians = Utilities.RevolutionsToRadians(angle);
                    break;

                case AngleType.Degree:
                    radians = Utilities.DegreesToRadians(angle);
                    break;

                case AngleType.Radian:
                    radians = angle;
                    break;

                case AngleType.Gradian:
                    radians = Utilities.GradiansToRadians(angle);
                    break;

                default:
                    radians = 0.0f;
                    break;
            }
        }

        /// <summary>
        /// Initializes a new instance of the SlimMath.AngleSingle structure using the
        /// arc length formula (θ = s/r).
        /// </summary>
        /// <param name="arcLength">The measure of the arc.</param>
        /// <param name="radius">The radius of the circle.</param>
        public AngleSingle(float arcLength, float radius)
        {
            radians = arcLength / radius;
        }

        /// <summary>
        /// Wraps this SlimMath.AngleSingle to be in the range [π, -π].
        /// </summary>
        public void Wrap()
        {
            float newangle = (float)System.Math.IEEERemainder(radians, MathExtended.TwoPi);

            if (newangle <= -MathExtended.Pi)
                newangle += MathExtended.TwoPi;
            else if (newangle > MathExtended.Pi)
                newangle -= MathExtended.TwoPi;

            radians = newangle;
        }

        /// <summary>
        /// Wraps this SlimMath.AngleSingle to be in the range [0, 2π).
        /// </summary>
        public void WrapPositive()
        {
            float newangle = radians % MathExtended.TwoPi;

            if (newangle < 0.0)
                newangle += MathExtended.TwoPi;

            radians = newangle;
        }

        /// <summary>
        /// Gets or sets the total number of revolutions this SlimMath.AngleSingle represents.
        /// </summary>
        public float Revolutions
        {
            get { return Utilities.RadiansToRevolutions(radians); }
            set { radians = Utilities.RevolutionsToRadians(value); }
        }

        /// <summary>
        /// Gets or sets the total number of degrees this SlimMath.AngleSingle represents.
        /// </summary>
        public float Degrees
        {
            get { return Utilities.RadiansToDegrees(radians); }
            set { radians = Utilities.DegreesToRadians(value); }
        }

        /// <summary>
        /// Gets or sets the minutes component of the degrees this SlimMath.AngleSingle represents.
        /// When setting the minutes, if the value is in the range (-60, 60) the whole degrees are
        /// not changed; otherwise, the whole degrees may be changed. Fractional values may set
        /// the seconds component.
        /// </summary>
        public float Minutes
        {
            get
            {
                float degrees = Utilities.RadiansToDegrees(radians);

                if (degrees < 0)
                {
                    float degreesfloor = (float)System.Math.Ceiling(degrees);
                    return (degrees - degreesfloor) * 60.0f;
                }
                else
                {
                    float degreesfloor = (float)System.Math.Floor(degrees);
                    return (degrees - degreesfloor) * 60.0f;
                }
            }
            set
            {
                float degrees = Utilities.RadiansToDegrees(radians);
                float degreesfloor = (float)System.Math.Floor(degrees);

                degreesfloor += value / 60.0f;
                radians = Utilities.DegreesToRadians(degreesfloor);
            }
        }

        /// <summary>
        /// Gets or sets the seconds of the degrees this SlimMath.AngleSingle represents.
        /// When setting te seconds, if the value is in the range (-60, 60) the whole minutes
        /// or whole degrees are not changed; otherwise, the whole minutes or whole degrees
        /// may be changed.
        /// </summary>
        public float Seconds
        {
            get
            {
                float degrees = Utilities.RadiansToDegrees(radians);

                if (degrees < 0)
                {
                    float degreesfloor = (float)System.Math.Ceiling(degrees);

                    float minutes = (degrees - degreesfloor) * 60.0f;
                    float minutesfloor = (float)System.Math.Ceiling(minutes);

                    return (minutes - minutesfloor) * 60.0f;
                }
                else
                {
                    float degreesfloor = (float)System.Math.Floor(degrees);

                    float minutes = (degrees - degreesfloor) * 60.0f;
                    float minutesfloor = (float)System.Math.Floor(minutes);

                    return (minutes - minutesfloor) * 60.0f;
                }
            }
            set
            {
                float degrees = Utilities.RadiansToDegrees(radians);
                float degreesfloor = (float)System.Math.Floor(degrees);

                float minutes = (degrees - degreesfloor) * 60.0f;
                float minutesfloor = (float)System.Math.Floor(minutes);

                minutesfloor += value / 60.0f;
                degreesfloor += minutesfloor / 60.0f;
                radians = Utilities.DegreesToRadians(degreesfloor);
            }
        }
        
        /// <summary>
        /// Gets or sets the total number of radians this SlimMath.AngleSingle represents.
        /// </summary>
        public float Radians
        {
            get { return radians; }
            set { radians = value; }
        }

        /// <summary>
        /// Gets or sets the total number of milliradians this SlimMath.AngleSingle represents.
        /// One milliradian is equal to 1/(2000π).
        /// </summary>
        public float Milliradians
        {
            get { return radians / (Milliradian * MathExtended.TwoPi); }
            set { radians = value * (Milliradian * MathExtended.TwoPi); }
        }

        /// <summary>
        /// Gets or sets the total number of gradians this SlimMath.AngleSingle represents.
        /// </summary>
        public float Gradians
        {
            get { return Utilities.RadiansToGradians(radians); }
            set { radians = Utilities.RadiansToGradians(value); }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is a right angle (i.e. 90° or π/2).
        /// </summary>
        public bool IsRight
        {
            get { return radians == MathExtended.PiOverTwo; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is a straight angle (i.e. 180° or π).
        /// </summary>
        public bool IsStraight
        {
            get { return radians == MathExtended.Pi; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is a full rotation angle (i.e. 360° or 2π).
        /// </summary>
        public bool IsFullRotation
        {
            get { return radians == MathExtended.TwoPi; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is an oblique angle (i.e. is not 90° or a multiple of 90°).
        /// </summary>
        public bool IsOblique
        {
            get { return WrapPositive(this).radians != MathExtended.PiOverTwo; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is an acute angle (i.e. less than 90° but greater than 0°).
        /// </summary>
        public bool IsAcute
        {
            get { return radians > 0.0 && radians < MathExtended.PiOverTwo; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is an obtuse angle (i.e. greater than 90° but less than 180°).
        /// </summary>
        public bool IsObtuse
        {
            get { return radians > MathExtended.PiOverTwo && radians < MathExtended.Pi; }
        }

        /// <summary>
        /// Gets a System.Boolean that determines whether this SlimMath.Angle
        /// is a reflex angle (i.e. greater than 180° but less than 360°).
        /// </summary>
        public bool IsReflex
        {
            get { return radians > MathExtended.Pi && radians < MathExtended.TwoPi; }
        }

        /// <summary>
        /// Gets a SlimMath.AngleSingle instance that complements this angle (i.e. the two angles add to 90°).
        /// </summary>
        public AngleSingle Complement
        {
            get { return new AngleSingle(MathExtended.PiOverTwo - radians, AngleType.Radian); }
        }

        /// <summary>
        /// Gets a SlimMath.AngleSingle instance that supplements this angle (i.e. the two angles add to 180°).
        /// </summary>
        public AngleSingle Supplement
        {
            get { return new AngleSingle(MathExtended.Pi - radians, AngleType.Radian); }
        }

        /// <summary>
        /// Wraps the SlimMath.AngleSingle given in the value argument to be in the range [π, -π].
        /// </summary>
        /// <param name="value">A SlimMath.AngleSingle to wrap.</param>
        /// <returns>The SlimMath.AngleSingle that is wrapped.</returns>
        public static AngleSingle Wrap(AngleSingle value)
        {
            value.Wrap();
            return value;
        }

        /// <summary>
        /// Wraps the SlimMath.AngleSingle given in the value argument to be in the range [0, 2π).
        /// </summary>
        /// <param name="value">A SlimMath.AngleSingle to wrap.</param>
        /// <returns>The SlimMath.AngleSingle that is wrapped.</returns>
        public static AngleSingle WrapPositive(AngleSingle value)
        {
            value.WrapPositive();
            return value;
        }

        /// <summary>
        /// Compares two SlimMath.AngleSingle instances and returns the smaller angle.
        /// </summary>
        /// <param name="left">The first SlimMath.AngleSingle instance to compare.</param>
        /// <param name="right">The second SlimMath.AngleSingle instance to compare.</param>
        /// <returns>The smaller of the two given SlimMath.AngleSingle instances.</returns>
        public static AngleSingle Min(AngleSingle left, AngleSingle right)
        {
            if (left.radians < right.radians)
                return left;

            return right;
        }

        /// <summary>
        /// Compares two SlimMath.AngleSingle instances and returns the greater angle.
        /// </summary>
        /// <param name="left">The first SlimMath.AngleSingle instance to compare.</param>
        /// <param name="right">The second SlimMath.AngleSingle instance to compare.</param>
        /// <returns>The greater of the two given SlimMath.AngleSingle instances.</returns>
        public static AngleSingle Max(AngleSingle left, AngleSingle right)
        {
            if (left.radians > right.radians)
                return left;

            return right;
        }

        /// <summary>
        /// Adds two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to add.</param>
        /// <param name="right">The second object to add.</param>
        /// <returns>The value of the two objects added together.</returns>
        public static AngleSingle Add(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians + right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Subtracts two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to subtract.</param>
        /// <param name="right">The second object to subtract.</param>
        /// <returns>The value of the two objects subtracted.</returns>
        public static AngleSingle Subtract(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians - right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Multiplies two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to multiply.</param>
        /// <param name="right">The second object to multiply.</param>
        /// <returns>The value of the two objects multiplied together.</returns>
        public static AngleSingle Multiply(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians * right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Divides two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The numerator object.</param>
        /// <param name="right">The denominator object.</param>
        /// <returns>The value of the two objects divided.</returns>
        public static AngleSingle Divide(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians / right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Gets a new SlimMath.AngleSingle instance that represents the zero angle (i.e. 0°).
        /// </summary>
        public static AngleSingle ZeroAngle
        {
            get { return new AngleSingle(0.0f, AngleType.Radian); }
        }

        /// <summary>
        /// Gets a new SlimMath.AngleSingle instance that represents the right angle (i.e. 90° or π/2).
        /// </summary>
        public static AngleSingle RightAngle
        {
            get { return new AngleSingle(MathExtended.PiOverTwo, AngleType.Radian); }
        }

        /// <summary>
        /// Gets a new SlimMath.AngleSingle instance that represents the straight angle (i.e. 180° or π).
        /// </summary>
        public static AngleSingle StraightAngle
        {
            get { return new AngleSingle(MathExtended.Pi, AngleType.Radian); }
        }

        /// <summary>
        /// Gets a new SlimMath.AngleSingle instance that represents the full rotation angle (i.e. 360° or 2π).
        /// </summary>
        public static AngleSingle FullRotationAngle
        {
            get { return new AngleSingle(MathExtended.TwoPi, AngleType.Radian); }
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether the values of two SlimMath.Angle
        /// objects are equal.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if the left and right parameters have the same value; otherwise, false.</returns>
        public static bool operator ==(AngleSingle left, AngleSingle right)
        {
            return left.radians == right.radians;
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether the values of two SlimMath.Angle
        /// objects are not equal.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if the left and right parameters do not have the same value; otherwise, false.</returns>
        public static bool operator !=(AngleSingle left, AngleSingle right)
        {
            return left.radians != right.radians;
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether a SlimMath.Angle
        /// object is less than another SlimMath.AngleSingle object.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if left is less than right; otherwise, false.</returns>
        public static bool operator <(AngleSingle left, AngleSingle right)
        {
            return left.radians < right.radians;
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether a SlimMath.Angle
        /// object is greater than another SlimMath.AngleSingle object.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if left is greater than right; otherwise, false.</returns>
        public static bool operator >(AngleSingle left, AngleSingle right)
        {
            return left.radians > right.radians;
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether a SlimMath.Angle
        /// object is less than or equal to another SlimMath.AngleSingle object.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if left is less than or equal to right; otherwise, false.</returns>
        public static bool operator <=(AngleSingle left, AngleSingle right)
        {
            return left.radians <= right.radians;
        }

        /// <summary>
        /// Returns a System.Boolean that indicates whether a SlimMath.Angle
        /// object is greater than or equal to another SlimMath.AngleSingle object.
        /// </summary>
        /// <param name="left">The first object to compare.</param>
        /// <param name="right">The second object to compare.</param>
        /// <returns>True if left is greater than or equal to right; otherwise, false.</returns>
        public static bool operator >=(AngleSingle left, AngleSingle right)
        {
            return left.radians >= right.radians;
        }

        /// <summary>
        /// Returns the value of the SlimMath.AngleSingle operand. (The sign of
        /// the operand is unchanged.)
        /// </summary>
        /// <param name="value">A SlimMath.AngleSingle object.</param>
        /// <returns>The value of the value parameter.</returns>
        public static AngleSingle operator +(AngleSingle value)
        {
            return value;
        }

        /// <summary>
        /// Returns the the negated value of the SlimMath.AngleSingle operand.
        /// </summary>
        /// <param name="value">A SlimMath.AngleSingle object.</param>
        /// <returns>The negated value of the value parameter.</returns>
        public static AngleSingle operator -(AngleSingle value)
        {
            return new AngleSingle(-value.radians, AngleType.Radian);
        }

        /// <summary>
        /// Adds two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to add.</param>
        /// <param name="right">The second object to add.</param>
        /// <returns>The value of the two objects added together.</returns>
        public static AngleSingle operator +(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians + right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Subtracts two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to subtract</param>
        /// <param name="right">The second object to subtract.</param>
        /// <returns>The value of the two objects subtracted.</returns>
        public static AngleSingle operator -(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians - right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Multiplies two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The first object to multiply.</param>
        /// <param name="right">The second object to multiply.</param>
        /// <returns>The value of the two objects multiplied together.</returns>
        public static AngleSingle operator *(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians * right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Divides two SlimMath.AngleSingle objects and returns the result.
        /// </summary>
        /// <param name="left">The numerator object.</param>
        /// <param name="right">The denominator object.</param>
        /// <returns>The value of the two objects divided.</returns>
        public static AngleSingle operator /(AngleSingle left, AngleSingle right)
        {
            return new AngleSingle(left.radians / right.radians, AngleType.Radian);
        }

        /// <summary>
        /// Compares this instance to a specified object and returns an integer that
        /// indicates whether the value of this instance is less than, equal to, or greater
        /// than the value of the specified object.
        /// </summary>
        /// <param name="other">The object to compare.</param>
        /// <returns>
        /// A signed integer that indicates the relationship of the current instance
        /// to the obj parameter. If the value is less than zero, the current instance
        /// is less than the other. If the value is zero, the current instance is equal
        /// to the other. If the value is greater than zero, the current instance is
        /// greater than the other.
        /// </returns>
        public int CompareTo(object other)
        {
            if (other == null)
                return 1;

            if (!(other is AngleSingle))
                throw new ArgumentException("Argument must be of type Angle.", "other");

            float radians = ((AngleSingle)other).radians;

            if (this.radians > radians)
                return 1;

            if (this.radians < radians)
                return -1;

            return 0;
        }

        /// <summary>
        /// Compares this instance to a second SlimMath.AngleSingle and returns
        /// an integer that indicates whether the value of this instance is less than,
        /// equal to, or greater than the value of the specified object.
        /// </summary>
        /// <param name="other">The object to compare.</param>
        /// <returns>
        /// A signed integer that indicates the relationship of the current instance
        /// to the obj parameter. If the value is less than zero, the current instance
        /// is less than the other. If the value is zero, the current instance is equal
        /// to the other. If the value is greater than zero, the current instance is
        /// greater than the other.
        /// </returns>
        public int CompareTo(AngleSingle other)
        {
            if (this.radians > other.radians)
                return 1;

            if (this.radians < other.radians)
                return -1;

            return 0;
        }

        /// <summary>
        /// Returns a value that indicates whether the current instance and a specified
        /// SlimMath.AngleSingle object have the same value.
        /// </summary>
        /// <param name="other">The object to compare.</param>
        /// <returns>
        /// Returns true if this SlimMath.AngleSingle object and another have the same value;
        /// otherwise, false.
        /// </returns>
        public bool Equals(AngleSingle other)
        {
            return this == other;
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format(CultureInfo.CurrentCulture, Utilities.RadiansToDegrees(radians).ToString("0.##°"));
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(string format)
        {
            if (format == null)
                return ToString();

            return string.Format(CultureInfo.CurrentCulture, "{0}°", Utilities.RadiansToDegrees(radians).ToString(format, CultureInfo.CurrentCulture));
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="formatProvider">The format provider.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(IFormatProvider formatProvider)
        {
            return string.Format(formatProvider, Utilities.RadiansToDegrees(radians).ToString("0.##°"));
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <param name="formatProvider">The format provider.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(string format, IFormatProvider formatProvider)
        {
            if (format == null)
                return ToString(formatProvider);

            return string.Format(formatProvider, "{0}°", Utilities.RadiansToDegrees(radians).ToString(format, CultureInfo.CurrentCulture));
        }

        /// <summary>
        /// Returns a hash code for this SlimMath.AngleSingle instance.
        /// </summary>
        /// <returns>A 32-bit signed integer hash code.</returns>
        public override int GetHashCode()
        {
            return (int)(BitConverter.DoubleToInt64Bits(radians) % int.MaxValue);
        }

        /// <summary>
        /// Returns a value that indicates whether the current instance and a specified
        /// object have the same value.
        /// </summary>
        /// <param name="obj">The object to compare.</param>
        /// <returns>
        /// Returns true if the obj parameter is a SlimMath.AngleSingle object or a type
        /// capable of implicit conversion to a SlimMath.AngleSingle value, and
        /// its value is equal to the value of the current SlimMath.Angle
        /// object; otherwise, false.
        /// </returns>
        public override bool Equals(object obj)
        {
            return (obj is AngleSingle) && (this == (AngleSingle)obj);
        }
    }
}
