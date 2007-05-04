#pragma once

using namespace System;
using namespace System::Drawing;

namespace SlimDX
{
	namespace Direct3D
	{
		//relevant enums
		public enum class FontWeight : Int32
		{
			DoNotCare = FW_DONTCARE,
			Thin = FW_THIN,
			ExtraLight = FW_EXTRALIGHT,
			UltraLight = FW_ULTRALIGHT,
			Light = FW_LIGHT,
			Normal = FW_NORMAL,
			Regular = FW_REGULAR,
			Medium = FW_MEDIUM,
			SemiBold = FW_SEMIBOLD,
			DemiBold = FW_DEMIBOLD,
			Bold = FW_BOLD,
			ExtraBold = FW_EXTRABOLD,
			UltraBold = FW_ULTRABOLD,
			Heavy = FW_HEAVY,
			Black = FW_BLACK,
		};

		public enum class CharacterSet : Int32
		{
			Ansi = ANSI_CHARSET,
			Default = DEFAULT_CHARSET,
			Symbol = SYMBOL_CHARSET,
			ShiftJIS = SHIFTJIS_CHARSET,
			Hangul = HANGUL_CHARSET,
			GB2312 = GB2312_CHARSET,
			ChineseBig5 = CHINESEBIG5_CHARSET,
			Oem = OEM_CHARSET,

			Johab = JOHAB_CHARSET,
			Hebrew = HEBREW_CHARSET,
			Arabic = ARABIC_CHARSET,
			Greek = GREEK_CHARSET,
			Turkish = TURKISH_CHARSET,
			Vietnamese = VIETNAMESE_CHARSET,
			Thai = THAI_CHARSET,
			EastEurope = EASTEUROPE_CHARSET,
			Russian = RUSSIAN_CHARSET,

			Baltic = BALTIC_CHARSET,
			Mac = MAC_CHARSET,
		};

		public enum class Precision : Int32
		{
			Default = OUT_DEFAULT_PRECIS,
			String = OUT_STRING_PRECIS,
			Character = OUT_CHARACTER_PRECIS,
			Stroke = OUT_STROKE_PRECIS,
			Tt = OUT_TT_PRECIS,
			Device = OUT_DEVICE_PRECIS,
			Raster = OUT_RASTER_PRECIS,
			TtOnly = OUT_TT_ONLY_PRECIS,
			Outline = OUT_OUTLINE_PRECIS,
			ScreenOutline = OUT_SCREEN_OUTLINE_PRECIS,
			PsOnly = OUT_PS_ONLY_PRECIS,
		};

		public enum class FontQuality : Int32
		{
			Default = DEFAULT_QUALITY,
			Draft = DRAFT_QUALITY,
			Proof = PROOF_QUALITY,
			NonAntiAliased = NONANTIALIASED_QUALITY,
			AntiAliased = ANTIALIASED_QUALITY,
			ClearType = CLEARTYPE_QUALITY,
			ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY,
		};

		[Flags]
		public enum class PitchAndFamily : Int32
		{
			Default = DEFAULT_PITCH,
			Fixed = FIXED_PITCH,
			Variable = VARIABLE_PITCH,
			Mono = MONO_FONT,

			DontCare = FF_DONTCARE,
			Roman = FF_ROMAN,
			Swiss = FF_SWISS,
			Modern = FF_MODERN,
			Script = FF_SCRIPT,
			Decorative = FF_DECORATIVE,
		};

		public enum class DrawTextFormat : Int32
		{
			Top = DT_TOP,
			Left = DT_LEFT,
			Center = DT_CENTER,
			Right = DT_RIGHT,
			VCenter = DT_VCENTER,
			Bottom = DT_BOTTOM,
			WordBreak = DT_WORDBREAK,
			SingleLine = DT_SINGLELINE,
			ExpandTabs = DT_EXPANDTABS,
			NoClip = DT_NOCLIP,
			CalcRect = DT_CALCRECT,
			RtlReading = DT_RTLREADING,
		};

		public ref class Font
		{
		private:
			ID3DXFont* m_Font;
			bool m_Disposed;

		internal:
			property ID3DXFont* InternalPointer
			{
				ID3DXFont* get() { return m_Font; }
			}

		public:
			Font( ID3DXFont* font );
			Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic,
				CharacterSet charSet, Precision outputPrecision, FontQuality quality,
				PitchAndFamily pitchAndFamily, String^ faceName );
			~Font();
			!Font();

			int DrawText( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, int color );
			int DrawText( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, Color color );
			int DrawText( Sprite^ sprite, String^ text, int x, int y, int color );
			int DrawText( Sprite^ sprite, String^ text, int x, int y, Color color );
		};
	}
}
