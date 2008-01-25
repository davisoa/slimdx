/*
* Copyright (c) 2007 SlimDX Group
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

#include <dxgi.h>

#include "ModeDescription.h"

namespace SlimDX
{
namespace DXGI
{ 	
	ModeDescription::ModeDescription( int width, int height, Rational refreshRate, DXGI::Format format )
	: m_Width( width ), m_Height( height ), m_RefreshRate( refreshRate ), m_Format( format ),
		m_ScanlineOrdering( DisplayModeScanlineOrdering::Unspecified ), m_Scaling( DisplayModeScaling::Unspecified )
	{
	}
	
	DXGI_MODE_DESC ModeDescription::CreateNativeVersion()
	{
		DXGI_MODE_DESC native;
		native.Width = m_Width;
		native.Height = m_Height;
		native.RefreshRate.Numerator = m_RefreshRate.Numerator;
		native.RefreshRate.Denominator = m_RefreshRate.Denominator;
		native.Format = static_cast<DXGI_FORMAT>( m_Format );
		native.ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>( m_ScanlineOrdering );
		native.Scaling = static_cast<DXGI_MODE_SCALING>( m_Scaling );
		
		return native;
	}
	
	ModeDescription::ModeDescription( const DXGI_MODE_DESC& native )
	{
		m_Width = native.Width;
		m_Height = native.Height;
		m_RefreshRate.Numerator = native.RefreshRate.Numerator;
		m_RefreshRate.Denominator = native.RefreshRate.Denominator;
		m_Format = static_cast<DXGI::Format>( native.Format );
		m_ScanlineOrdering = static_cast<DisplayModeScanlineOrdering>( native.ScanlineOrdering );
		m_Scaling = static_cast<DisplayModeScaling>( native.Scaling );
	}

	int ModeDescription::Width::get()
	{
		return m_Width;
	}

	void ModeDescription::Width::set( int value )
	{
		m_Width = value;
	}

	int ModeDescription::Height::get()
	{
		return m_Height;
	}
	
	void ModeDescription::Height::set( int value )
	{
		m_Height = value;
	}
	
	Rational ModeDescription::RefreshRate::get()
	{
		return m_RefreshRate;
	}
	
	void ModeDescription::RefreshRate::set( Rational value )
	{
		m_RefreshRate = value;
	}
	
	DXGI::Format ModeDescription::Format::get()
	{
		return m_Format;
	}
	
	void ModeDescription::Format::set( DXGI::Format value )
	{
		m_Format = value;
	}
	
	DisplayModeScanlineOrdering ModeDescription::ScanlineOrdering::get()
	{
		return m_ScanlineOrdering;
	}
	
	void ModeDescription::ScanlineOrdering::set( DisplayModeScanlineOrdering value )
	{
		m_ScanlineOrdering = value;
	}
	
	DisplayModeScaling ModeDescription::Scaling::get()
	{
		return m_Scaling;
	}
	
	void ModeDescription::Scaling::set( DisplayModeScaling value )
	{
		m_Scaling = value;
	}
}
}
