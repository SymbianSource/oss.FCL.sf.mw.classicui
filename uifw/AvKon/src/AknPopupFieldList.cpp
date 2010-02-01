/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/

// AknPopupFieldList.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include <coemain.h>
#include <avkon.hrh>
#include <avkon.rsg>

#include "AknPopupFieldList.h"
#include "AknDesCArrayDecorator.h"
#include "AknQueryValue.h"

#include "AknPanic.h"
#include <eikmop.h>

// -------------------------------
// AknPopupFieldList
// -------------------------------

/**
 * No longer implemented, do not use
 */
EXPORT_C CAknPopupFieldList* CAknPopupFieldList::NewL(CEikListBox* /*aListBox*/, TInt /*aCbaResource*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	return 0;
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::SetQueryValue(MAknQueryValue* /*aValue*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::SetDecorator(TAknDesCArrayDecorator* /*aDecorator*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::ProcessCommandL(TInt /*aCommandId*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent /*aEventType*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}


/**
 * No longer implemented, do not use
 */
EXPORT_C CAknPopupFieldList::CAknPopupFieldList()
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C CAknPopupFieldList::~CAknPopupFieldList()
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::ConstructL(CEikListBox* /*aListBox*/, TInt /*aCbaResource*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}


/**
 * No longer implemented, do not use
 */
EXPORT_C void CAknPopupFieldList::AttemptExitL(TBool /*aAccept*/)
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	}

/** 
 * No longer implemented, do not use
 */
EXPORT_C CEikListBox* CAknPopupFieldList::ListBox() const
	{
	Panic(EAknPanicPopupFieldListNotImplemented);
	return 0;
	}



// debug only invariant function
EXPORT_C void CAknPopupFieldList::__DbgTestInvariant() const          
	{    
	}

EXPORT_C TTypeUid::Ptr CAknPopupFieldList::MopSupplyObject(TTypeUid aId)
	{
	return SupplyMopObject(aId, iPopoutCba);
	}
	
EXPORT_C void CAknPopupFieldList::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikBorderedControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknPopupFieldList::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

// End of File
