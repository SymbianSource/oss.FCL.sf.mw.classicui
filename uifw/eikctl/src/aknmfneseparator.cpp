/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <eikenv.h>

#include "aknmfneseparator.h"


_LIT( KSafeNullDesC, "" );


CAknMfneSeparator::CAknMfneSeparator() : iVisible( ETrue )
    {
    }

CAknMfneSeparator::~CAknMfneSeparator()
    {
    delete iText;
    }

CAknMfneSeparator* CAknMfneSeparator::NewL(const TDesC& aText)
    {
    CAknMfneSeparator* self = new(ELeave) CAknMfneSeparator();
    CleanupStack::PushL(self);
    self->SetTextL(aText);
    CleanupStack::Pop(self);
    return self;
    }

void CAknMfneSeparator::SetTextL(const TDesC& aText)
    {
    delete iText;
    iText = NULL;
    iText = HBufC::NewL(aText.Length());
    *iText = aText;
    }

TInt CAknMfneSeparator::MaximumWidthInPixels(
    const CFont& aFont,
    TBool /*aShrinkToMinimumSize*/)
    {
    return aFont.TextWidthInPixels(*iText);
    }

TCoeInputCapabilities CAknMfneSeparator::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::ENone);
    }

const TDesC& CAknMfneSeparator::Text() const
    {
    if ( iVisible )
        {
        return *iText;
        }
    else
        {
        return KSafeNullDesC();
        }
    }

void CAknMfneSeparator::MakeVisible( TBool aVisible )
    {
    iVisible = aVisible;
    }
