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


#include "aknquerydata.h"

/**
 * Used to encapsulate the rules of how long the string is 
 * NB for a stringlength to be valid it must be <= Maxlength of descriptor.
 */
EXPORT_C TInt GetMaxTextLength(const CAknQueryControl* aControl, const TDes& aDataText,TInt aApiValue) 
	{
    // Case 1:  If we have an aApiValue and it is valid, use this.
    if (aApiValue>0 && aApiValue<= aDataText.MaxLength()) 
        return aApiValue;
    // Case  2:  If we have a value set from resource and it is valid, use this.
    if (
        aControl && // there is a control
        aControl->GetTextEntryLength()!=0 && // a value has been set for this control
        aControl->GetTextEntryLength()<=aDataText.MaxLength() //the value set is valid
        )
        return aControl->GetTextEntryLength();
    return aDataText.MaxLength();
    }

// End of File
