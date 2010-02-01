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

#ifndef EIKDEFCONST_H
#define EIKDEFCONST_H

#include <e32std.h>

/** Defines the border style for an editable control.

@publishedPartner
@released
*/
#define KEikEditableControlBorder TGulBorder::EShallowSunken

/** Name of the default bitmap store.

@publishedPartner
@released
*/
_LIT(KEikDefaultAppBitmapStore,"*");

/** Uid of the KEikMessageColorSchemeChange message.

@publishedPartner
@released
*/
const TInt KUidValueEikColorSchemeChangeEvent	=0x10006956;

/**
@publishedPartner 
@released
*/
const TInt KEikDefaultCursorWidth=2;

/**
@publishedPartner 
@released
*/
const TInt KTimeBetweenClicks=1000000;	 // in Microseconds	

/**
@publishedPartner 
@released
*/		 
const TInt KDoubleClickDistance=10;

/**
@publishedPartner 
@released
*/	
const TInt KKeyboardRepeatRate=50000;

/**
@publishedPartner 
@released
*/	
const TInt KKeyboardRepeatInitialDelay=800000;

/** Resource id of the query dialog.
@publishedPartner
@released
*/
const TInt KEikResIdQueryDialog	=0;

/** Resource id of the info dialog.
@publishedPartner
@released
*/
const TInt KEikResIdInfoDialog	=1;

/**
@publishedPartner 
@released
*/	
const TInt KEikErrorResolverMaxTextLength = 256;

#endif	// EIKDEFCONST_H
