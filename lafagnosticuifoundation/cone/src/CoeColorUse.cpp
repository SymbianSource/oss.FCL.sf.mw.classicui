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

#include <coecoloruse.h>

//
// class TCoeColorUse
//

/** Constructor. */
EXPORT_C TCoeColorUse::TCoeColorUse()
	: iLogicalColor(0), iUse(0) 
	{
	}

/** Sets the use of the logical colour.

@param aUse The use of the logical colour. A valid value describing a colour 
use consists of choices of one value from each of the enums TGround, TAreas, 
TFocus, TState and TTones ORed together. */
EXPORT_C void TCoeColorUse::SetUse(TInt aUse)
	{
	iUse=aUse;
	}

/** Sets the logical colour which has its use described by this object. 

@param aLogicalColor The logical colour. */
EXPORT_C void TCoeColorUse::SetLogicalColor(TInt aLogicalColor)
	{
	iLogicalColor=aLogicalColor;
	}

EXPORT_C TInt TCoeColorUse::LogicalColor() const
/** Gets the logical colour which has its use described by this TCoeColourUse.

@return The logical colour. */
	{
	return iLogicalColor;
	}

EXPORT_C TInt TCoeColorUse::Use() const
/** Gets the value describing the use of the logical colour. 

@return The use of the logical colour. This is the logical OR of one value 
from each of the enums TGround, TAreas, TFocus, TState and TTones. */
	{
	return iUse;
	}

EXPORT_C TBool TCoeColorUse::IsForeground() const
/** Tests whether the logical colour is used as a foreground colour. 

@return ETrue if the logical colour is used as a foreground colour, otherwise 
EFalse. */
	{
	return iUse&EFore;
	}

EXPORT_C TBool TCoeColorUse::IsBackground() const
/** Tests whether the logical colour is used as a background colour. 

@return ETrue if the logical colour is used as a background colour, otherwise 
EFalse. */
	{
	return iUse&EBack;
	}

EXPORT_C TBool TCoeColorUse::IsContents() const
/** Tests whether the logical colour is used to draw a control's contents. 

The contents are the parts of the control that the user interacts with, e.g. 
an editor field, the contents of a list box, the page of a web browser. This 
is opposed to the fascia (or 'surrounds') which are the parts of controls 
which make up the illusion that the contents are set into some sort of solid 
frontage.

@return ETrue if the logical colour is used to draw a control's contents, 
otherwise EFalse. */
	{
	return iUse&EContents;
	}

EXPORT_C TBool TCoeColorUse::IsHighlights() const
/** Tests whether the logical colour is used to draw a control's highlighted contents. 

@return ETrue if the logical colour is used to draw a control's highlighted 
contents, otherwise EFalse. */
	{
	return iUse&EHighlights;
	}

EXPORT_C TBool TCoeColorUse::IsSurrounds() const
/** Tests whether the logical colour is used to draw a control's surrounds. 

@return ETrue if the logical colour is used to draw a control's surrounds, 
otherwise EFalse. */
	{
	return iUse&ESurrounds;
	}

EXPORT_C TBool TCoeColorUse::IsBorders() const
/** Tests whether the logical colour is used to draw a control's borders.

@return ETrue if the logical colour is used to draw a control's borders, otherwise 
EFalse. */
	{
	return iUse&EBorders;
	}

EXPORT_C TBool TCoeColorUse::IsActive() const
/** Tests whether the logical colour is active. i.e. whether or not it is used 
to draw the control when active and either focused or unfocused.

@return ETrue if the logical colour is active, otherwise EFalse. */
	{
	return iUse&EActive;
	}

EXPORT_C TBool TCoeColorUse::IsDimmed() const
/** Tests whether the logical colour is used to draw the control when dimmed and 
either focused or unfocused. 

@return ETrue if the logical colour is used to draw the control when dimmed 
and either focused or unfocused, otherwise EFalse. */
	{
	return iUse&EDimmed;
	}

EXPORT_C TBool TCoeColorUse::IsPressed() const
/** Tests whether the logical colour is used to draw the control when focused and 
pressed. 

@return ETrue if the logical colour is used to draw the control when focused 
and pressed, otherwise EFalse. */
	{
	return iUse&EPressed;
	}

EXPORT_C TBool TCoeColorUse::IsNormal() const
/** Tests whether the logical colour is used to draw the control in a normal state.

@return ETrue if the logical colour is used to draw the control in a normal 
state, otherwise EFalse. */
	{
	return iUse&ENormal;
	}

EXPORT_C TBool TCoeColorUse::IsSet() const
/** Tests whether the logical colour is used to draw the control in a set state. 

@return ETrue if the logical colour is used to draw the control in a set state, 
otherwise EFalse. */
	{
	return iUse&ESet;
	}
