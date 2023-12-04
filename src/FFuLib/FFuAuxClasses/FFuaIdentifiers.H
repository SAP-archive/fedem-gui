// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_IDENTIFIERS_H
#define FFUA_IDENTIFIERS_H

/*!
  Ensure that these variables never have the same name as other
  Qt definitions (in qkeycode.h), even for those who are variables
  in qkeycode.h (accel modifiers).
*/

class FFuaKeyCode
{
public:
static const unsigned int ShiftAccel;// accelerator modifiers
static const unsigned int CtrlAccel;
static const unsigned int AltAccel;
static const unsigned int AsciiAccel;


static const int Escape;// misc keys
static const int Tab		;
static const int Backtab		;
static const int Backspace		;
static const int Return		;
static const int Enter		;
static const int Insert		;
static const int Delete		;
static const int Pause		;
static const int Print		;
static const int SysReq		;

static const int Home		;// cursor movement
static const int End		;
static const int Left		;
static const int Up		;
static const int Right		;
static const int Down		;
static const int Prior		;
static const int PageUp		;
static const int Next		;
static const int PageDown		;

static const int Shift		;// modifiers
static const int Control		;
static const int Meta		;
static const int Alt		;
static const int CapsLock		;	
static const int NumLock		;	
static const int ScrollLock		;// see translateKeyEvent()

static const int F1		;	// function keys
static const int F2		;	
static const int F3		;	
static const int F4		;	
static const int F5		;	
static const int F6		;	
static const int F7		;	
static const int F8		;	
static const int F9		;	
static const int F10		;	
static const int F11		;	
static const int F12		;	
static const int F13		;	
static const int F14		;	
static const int F15		;	
static const int F16		;	
static const int F17		;	
static const int F18		;	
static const int F19		;	
static const int F20		;	
static const int F21		;	
static const int F22		;	
static const int F23		;	
static const int F24		;	
static const int F25		;// F25 .. F35 only on X11
static const int F26		;	
static const int F27		;	
static const int F28		;	
static const int F29		;
static const int F30		;
static const int F31		;
static const int F32		;
static const int F33		;
static const int F34		;
static const int F35		;

static const int Super_L 		;// extra keys
static const int Super_R 		;
static const int Menu 		;


static const int Space		;// 7 bit printable ASCII
static const int Exclam		;
static const int QuoteDbl		;
static const int NumberSign		;
static const int Dollar		;
static const int Percent		;
static const int Ampersand		;
static const int Apostrophe		;
static const int ParenLeft		;
static const int ParenRight		;
static const int Asterisk		;
static const int Plus		;
static const int Comma		;
static const int Minus		;
static const int Period		;
static const int Slash		;
static const int key_0		;
static const int key_1		;
static const int key_2		;
static const int key_3		;
static const int key_4		;
static const int key_5		;
static const int key_6		;
static const int key_7		;
static const int key_8		;
static const int key_9		;
static const int Colon		;
static const int Semicolon		;
static const int Less		;
static const int Equal		;
static const int Greater		;
static const int Question		;
static const int At		;
static const int A		;
static const int B		;
static const int C		;
static const int D		;
static const int E		;
static const int F		;
static const int G		;
static const int H		;
static const int I		;
static const int J		;
static const int K		;
static const int L		;
static const int M		;
static const int N		;
static const int O		;
static const int P		;
static const int Q		;
static const int R		;
static const int S		;
static const int T		;
static const int U		;
static const int V		;
static const int W		;
static const int X		;
static const int Y		;
static const int Z		;
static const int BracketLeft		;
static const int Backslash		;
static const int BracketRight		;
static const int AsciiCircum		;
static const int Underscore		;
static const int QuoteLeft		;
static const int BraceLeft		;
static const int Bar		;
static const int BraceRight		;
static const int AsciiTilde		;
		
// Latin 1 codes adapted from X: keysymdef.h,v 1.21 94/08/28 16:17:06
		
static const int nobreakspace		;
static const int exclamdown		;
static const int cent		;
static const int sterling		;
static const int currency		;
static const int yen		;
static const int brokenbar		;
static const int section		;
static const int diaeresis		;
static const int copyright		;
static const int ordfeminine		;
static const int guillemotleft		;/* left angle quotation mark */
static const int notsign		;
static const int hyphen		;
static const int registered		;
static const int macron		;
static const int degree		;
static const int plusminus		;
static const int twosuperior		;
static const int threesuperior		;
static const int acute		;
static const int mu		;
static const int paragraph		;
static const int periodcentered		;
static const int cedilla		;
static const int onesuperior		;
static const int masculine		;
static const int guillemotright		;	/* right angle quotation mark */
static const int onequarter		;
static const int onehalf		;
static const int threequarters		;
static const int questiondown		;
static const int Agrave		;
static const int Aacute		;
static const int Acircumflex		;
static const int Atilde		;
static const int Adiaeresis		;
static const int Aring		;
static const int AE		;
static const int Ccedilla		;
static const int Egrave		;
static const int Eacute		;
static const int Ecircumflex		;
static const int Ediaeresis		;
static const int Igrave		;
static const int Iacute		;
static const int Icircumflex		;
static const int Idiaeresis		;
static const int ETH		;
static const int Ntilde		;
static const int Ograve		;
static const int Oacute		;
static const int Ocircumflex		;
static const int Otilde		;
static const int Odiaeresis		;
static const int multiply		;
static const int Ooblique		;
static const int Ugrave		;
static const int Uacute		;
static const int Ucircumflex		;
static const int Udiaeresis		;
static const int Yacute		;
static const int THORN		;
static const int ssharp		;
static const int agrave		;
static const int aacute		;
static const int acircumflex		;
static const int atilde		;
static const int adiaeresis		;
static const int aring		;
static const int ae		;
static const int ccedilla		;
static const int egrave		;
static const int eacute		;
static const int ecircumflex       	;
static const int ediaeresis		;
static const int igrave		;
static const int iacute		;
static const int icircumflex       	;
static const int idiaeresis		;
static const int eth		;
static const int ntilde		;
static const int ograve		;
static const int oacute		;
static const int ocircumflex       	;
static const int otilde		;
static const int odiaeresis		;
static const int division		;
static const int oslash		;
static const int ugrave		;
static const int uacute		;
static const int ucircumflex       	;
static const int udiaeresis		;
static const int yacute		;
static const int thorn		;
static const int ydiaeresis		;

static const int unknown		;
};

class FFuaOrientation
{
public:
static const int Horizontal;
static const int Vertical;
};

class FFuaTextAlignment
{
public:
  // Horizontal flags
  static const int AlignAuto;
  static const int AlignLeft;
  static const int AlignRight;
  static const int AlignHCenter;
  static const int AlignJustify;

  // Vertical flags
  static const int AlignTop;
  static const int AlignBottom;
  static const int AlignVCenter;

  // 2D flag
  static const int AlignCenter;

  // Masks
  static const int AlignHorizontal_Mask;
  static const int AlignVertical_Mask;
};

#endif
