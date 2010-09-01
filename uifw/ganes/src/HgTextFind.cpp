/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "HgTextFind.h"
#include <ganes/HgScroller.h>
#include "HgConstants.h"

// -----------------------------------------------------------------------------
// CHgTextFind::NewL()
// -----------------------------------------------------------------------------
//
CHgTextFind* CHgTextFind::NewL(CHgScroller& aScroller)
    {
    CHgTextFind* self = new (ELeave) CHgTextFind( aScroller );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CHgTextFind::~CHgTextFind()
// -----------------------------------------------------------------------------
//
CHgTextFind::~CHgTextFind()
    {
    delete iState;
    iBuf.Close();
    iSearchDesc.Close();
    delete iTimer;
    }

// -----------------------------------------------------------------------------
// CHgTextFind::CHgTextFind()
// -----------------------------------------------------------------------------
//
CHgTextFind::CHgTextFind( CHgScroller& aScroller ) 
    : iScroller( aScroller)
    {
            
    }

// -----------------------------------------------------------------------------
// CHgTextFind::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::ConstructL()
    {
    iState = new (ELeave) CAknEdwinState();
    iState->SetObjectProvider(&iScroller);
    iState->SetDefaultCase( EAknEditorUpperCase );
    iState->SetFlags(
            EAknEditorFlagFixedCase |
            EAknEditorFlagNoT9 |
            EAknEditorFlagNoEditIndicators |
            EAknEditorFlagNoLRNavigation |
            EAknEditorFlagSupressShiftMenu
            );
    
    iBuf.CreateL( KMaxPopupTextLength );
    iSearchDesc.CreateL( KMaxSearchLenght );
    iTimer = CPeriodic::New( CActive::EPriorityLow );
    }

// -----------------------------------------------------------------------------
// CHgTextFind::StartFepInlineEditL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::StartFepInlineEditL( const TDesC& aInitialInlineText, 
        TInt /*aPositionOfInsertionPointInInlineText*/, 
        TBool /*aCursorVisibility*/, const MFormCustomDraw* /*aCustomDraw*/,
        MFepInlineTextFormatRetriever& /*aInlineTextFormatRetriever*/, 
        MFepPointerEventHandlerDuringInlineEdit& /*aPointerEventHandlerDuringInlineEdit*/ )
    {
    iTimer->Cancel();
    if( iBuf.Length() + aInitialInlineText.Length() < iBuf.MaxLength() )
        iBuf.Append(aInitialInlineText);
    iScroller.DrawNow();
    }

// -----------------------------------------------------------------------------
// CHgTextFind::UpdateFepInlineTextL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::UpdateFepInlineTextL( const TDesC& aNewInlineText, 
        TInt /*aPositionOfInsertionPointInInlineText*/ )
    {
    iTimer->Cancel();
    if( iBuf.Length() + aNewInlineText.Length() < iBuf.MaxLength() )
        {
        if(iBuf.Length())
            {
            if( aNewInlineText.Length() )
                {
                iBuf.Replace(iBuf.Length()-1, aNewInlineText.Length(), aNewInlineText);
                iScroller.DrawNow();
                }
            else
                {
                iBuf.Delete(iBuf.Length()-1, 1);
                }
            }
        else
            {
            iBuf.Append(aNewInlineText);
            iScroller.DrawNow();
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgTextFind::SetInlineEditingCursorVisibilityL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::SetInlineEditingCursorVisibilityL( TBool /*aCursorVisibility*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgTextFind::CancelFepInlineEdit()
// -----------------------------------------------------------------------------
//
void CHgTextFind::CancelFepInlineEdit()
    {
    }

// -----------------------------------------------------------------------------
// CHgTextFind::DocumentLengthForFep()
// -----------------------------------------------------------------------------
//
TInt CHgTextFind::DocumentLengthForFep() const
    {
    return iBuf.Length();
    }

// -----------------------------------------------------------------------------
// CHgTextFind::DocumentMaximumLengthForFep()
// -----------------------------------------------------------------------------
//
TInt CHgTextFind::DocumentMaximumLengthForFep() const
    {
    return iBuf.MaxLength();
    }

// -----------------------------------------------------------------------------
// CHgTextFind::SetCursorSelectionForFepL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::SetCursorSelectionForFepL( const TCursorSelection& /*aCursorSelection*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgTextFind::GetCursorSelectionForFep()
// -----------------------------------------------------------------------------
//
void CHgTextFind::GetCursorSelectionForFep( TCursorSelection& /*aCursorSelection*/ ) const
    {
    
    }

// -----------------------------------------------------------------------------
// CHgTextFind::GetEditorContentForFep()
// -----------------------------------------------------------------------------
//
void CHgTextFind::GetEditorContentForFep( TDes& /*aEditorContent*/,
        TInt /*aDocumentPosition*/, TInt /*aLengthToRetrieve*/ ) const
    {
    
    }
    
// -----------------------------------------------------------------------------
// CHgTextFind::GetFormatForFep()
// -----------------------------------------------------------------------------
//
void CHgTextFind::GetFormatForFep( TCharFormat& /*aFormat*/, TInt /*aDocumentPosition*/ ) const
    {
    
    }

// -----------------------------------------------------------------------------
// CHgTextFind::GetScreenCoordinatesForFepL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::GetScreenCoordinatesForFepL( TPoint& /*aLeftSideOfBaseLine*/,
        TInt& /*aHeight*/, TInt& /*aAscent*/, TInt /*aDocumentPosition*/ ) const
    {
    
    }

// -----------------------------------------------------------------------------
// CHgTextFind::Extension1()
// -----------------------------------------------------------------------------
//
MCoeFepAwareTextEditor_Extension1* CHgTextFind::Extension1(TBool& aSetToTrue)
    {
    aSetToTrue = ETrue;
    return this;
    }

// -----------------------------------------------------------------------------
// CHgTextFind::SetStateTransferingOwnershipL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::SetStateTransferingOwnershipL( CState* /*aState*/, TUid /*aTypeSafetyUid*/ )
// this function must only transfer ownership after it has successfully done everything that can leave
    {
    
    }
// -----------------------------------------------------------------------------
// CHgTextFind::State()
// -----------------------------------------------------------------------------
//
MCoeFepAwareTextEditor_Extension1::CState* CHgTextFind::State( TUid /*aTypeSafetyUid */ )
    {
    return iState;
    }


// -----------------------------------------------------------------------------
// CHgTextFind::DoCommitFepInlineEditL()
// -----------------------------------------------------------------------------
//
void CHgTextFind::DoCommitFepInlineEditL()
    {
    iSearchDesc.Copy(iBuf);
    iSearchDesc.UpperCase();
    iScroller.HightlightItem(iSearchDesc);
    iTimer->Cancel();
    iTimer->Start(KSearchEndTimeOut, KSearchEndTimeOut,
            TCallBack(CHgTextFind::SearchTimerCallback, this));
    }

// -----------------------------------------------------------------------------
// CHgTextFind::SearchTimerCallback()
// -----------------------------------------------------------------------------
//
TInt CHgTextFind::SearchTimerCallback( TAny* aSelf )
    {
    CHgTextFind* self = (CHgTextFind*)aSelf;
    self->ClearSearchDesc();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CHgTextFind::ClearSearchDesc()
// -----------------------------------------------------------------------------
//
void CHgTextFind::ClearSearchDesc()
    {
    iBuf.Zero();
    iTimer->Cancel();
    iScroller.DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CHgTextFind::Text()
// -----------------------------------------------------------------------------
//
const TDesC& CHgTextFind::Text()
    {
    return iBuf;
    }


