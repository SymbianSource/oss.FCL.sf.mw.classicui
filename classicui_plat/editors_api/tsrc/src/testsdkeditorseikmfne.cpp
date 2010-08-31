/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test EIKMFNE.h
*
*/


#include "testsdkeditorseikmfne.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::FocusChanged
// -----------------------------------------------------------------------------
void CTestSDKEditorsEIKMFNE::FocusChanged( TDrawNow aDrawNow )
    {
    CEikMfne::FocusChanged( aDrawNow );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEIKMFNE::WriteInternalStateL( RWriteStream& aWriteStream ) const
    {
    CEikMfne::WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::HandleInteraction
// -----------------------------------------------------------------------------
void CTestSDKEditorsEIKMFNE::HandleInteraction( TBool aHandleDeHighlight, 
                                                TInt aNewCurrentField, 
                                                TInt aOldWidthInPixelsOfOldCurrentField,
                                                CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, 
                                                TBool& aDataAltered, 
                                                TBool& aError )
    {
    CEikMfne::HandleInteraction( aHandleDeHighlight, 
                                 aNewCurrentField, 
                                 aOldWidthInPixelsOfOldCurrentField, 
                                 aOldHighlightTypeOfOldCurrentField, 
                                 aDataAltered, 
                                 aError );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::FieldIsAboutToBeDeHighlighted
// -----------------------------------------------------------------------------
void CTestSDKEditorsEIKMFNE::FieldIsAboutToBeDeHighlighted( CEikMfneField* aField, 
                                                            TBool& aDrawAllFields )
    {
    CEikMfne::FieldIsAboutToBeDeHighlighted( aField, aDrawAllFields );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::MfneSize
// -----------------------------------------------------------------------------
TSize CTestSDKEditorsEIKMFNE::MfneSize() const
    {
    return CEikMfne::MfneSize();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::MfneSize
// -----------------------------------------------------------------------------
TSize CTestSDKEditorsEIKMFNE::MfneSize(TBool aShrinkToMinimumSize)
    {
    return CEikMfne::MfneSize( aShrinkToMinimumSize );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEIKMFNE::MfneSize
// -----------------------------------------------------------------------------
void CTestSDKEditorsEIKMFNE::SizeChanged()
    {
    CEikMfne::SizeChanged();
    }
