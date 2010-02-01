// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __COECOLORUSE_H__
#define __COECOLORUSE_H__

#include <e32std.h>

/** Logical colour used when drawing in controls.

This class pairs a logical colour value with an explanation of how it is used 
when drawing a control. The explanation is in terms of categories of use, e.g. 
in the TGround category, the colour can used for either the foreground or 
background. 

@publishedAll 
@released */
class TCoeColorUse
    {
public:
	/** Foreground and background category flags */
	enum TGround
		{
		/** The logical colour is used to draw the control when it is in the foreground. */
		EFore=0x01,
		/** The logical colour is used to draw the control when it is in the background. */
		EBack=0x02
		};

	/** Flags that control the area in which colour is used. */
	enum TAreas
		{
		/** The logical colour is used to draw a control's contents. */
		EContents=0x10,
		/** The logical colour is used to draw a control's highlighted contents. */
		EHighlights=0x20,
		/** The logical colour is used to draw a control's surrounds. */
		ESurrounds=0x40,
		/** The logical colour is used to draw a control's borders. */
		EBorders=0x80
		};

	/** Focus category flags */
	enum TFocus
		{
		/** The logical colour is used to draw the control when active and either focused 
		or unfocused. */
		EActive=0x100,
		/** The logical colour is used to draw the control when dimmed and either focused 
		or unfocused. */
		EDimmed=0x200,
		/** The logical colour is used to draw the control when it is shadowed. */
		EShadowed=0x400,	
		/** The logical colour is used to draw the control when focused and pressed. */
		EPressed=0x800
		};

	/** State category flags */
	enum TState
		{
		/** The logical colour is used to draw the control in the normal state. */
		ENormal=0x1000,
		/** The logical colour is used to draw the control in the set state. */
		ESet=0x2000,
		/** The logical colour is used to draw the control in the checked state. */
		EChecked=0x4000
		};

	/** Tone flags */
	enum TTones
		{
		/** The logical colour is used to draw the control in neutral tones. */
		ENeutral=0x10000,
		/** The logical colour is used to draw the control in light tones. */
		ELight=0x20000,
		/** The logical colour is used to draw the control in midlight tones. */
		EMidLight=0x40000,
		/** The logical colour is used to draw the control in mid tones. */
		EMid=0x80000,
		/** The logical colour is used to draw the control in dark tones. */
		EDark=0x100000
		};
public:
	IMPORT_C TCoeColorUse();
	//
	IMPORT_C void SetUse(TInt aUse);
	IMPORT_C void SetLogicalColor(TInt aLogicalColor);
	IMPORT_C TInt LogicalColor() const;
	IMPORT_C TInt Use() const;
	//
	IMPORT_C TBool IsForeground() const;
	IMPORT_C TBool IsBackground() const;
	//
	IMPORT_C TBool IsContents() const;
	IMPORT_C TBool IsHighlights() const;
	IMPORT_C TBool IsSurrounds() const;
	IMPORT_C TBool IsBorders() const;
	IMPORT_C TBool IsActive() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C TBool IsPressed() const;
	IMPORT_C TBool IsNormal() const;
	IMPORT_C TBool IsSet() const;
private:
    TInt iLogicalColor;
	TInt iUse;
	TInt iTCoeColorUse_Reserved1;
    };


#endif // __COECOLORUSE_H__

