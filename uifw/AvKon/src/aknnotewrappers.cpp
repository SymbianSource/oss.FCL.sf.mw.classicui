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
*       Implementation of wrappers for standard note types
*
*/


#include <barsread.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include "aknnotewrappers.h"
#include <StringLoader.h>
#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#endif

void TAknNoteResData::ReadFromResource(TResourceReader& aResReader)
	{
    iResId = aResReader.ReadInt32();
    iTimeout = STATIC_CAST(CAknNoteDialog::TTimeout, aResReader.ReadInt32());
    iTone = STATIC_CAST(CAknNoteDialog::TTone, aResReader.ReadInt16());
    iText = aResReader.ReadTPtrC();
	}

EXPORT_C CAknNoteWrapper::CAknNoteWrapper()
    {
	iTimeoutInMicroseconds = -1;
	iTone = STATIC_CAST(TTone,-1);
	AKNTASHOOK_ADD( this, "CAknNoteWrapper" );
    }

EXPORT_C CAknNoteWrapper::CAknNoteWrapper(CAknNoteWrapper** aSelfPtr)
    : CAknNoteDialog(REINTERPRET_CAST(CEikDialog**,aSelfPtr))
    {
	iTimeoutInMicroseconds = -1;
	iTone = STATIC_CAST(TTone,-1);
	AKNTASHOOK_ADD( this, "CAknNoteWrapper" );
    }

EXPORT_C TInt CAknNoteWrapper::ExecuteLD(TInt aResId)
    {
	TAknNoteResData resData = ReadResDataAndPrepareL(aResId);
    if (resData.iText.Length() > 0)
        {
        SetTextL(resData.iText);
        }

	if (iTimeoutInMicroseconds == -1)
		{
		SetTimeout(resData.iTimeout);
		}

	if (iTone == STATIC_CAST(TTone,-1))
		{
		SetTone(resData.iTone);
		}
	return RunLD();
    }

EXPORT_C TInt CAknNoteWrapper::ExecuteLD(TInt aResId, const TDesC& aPrompt)
    {
    TAknNoteResData resData = ReadResDataAndPrepareL(aResId);
    SetTextL(aPrompt);

	if (iTimeoutInMicroseconds == -1)
		{
		SetTimeout(resData.iTimeout);
		}

	if (iTone == STATIC_CAST(TTone,-1))
		{
		SetTone(resData.iTone);
		}
	return RunLD();
    }

TAknNoteResData CAknNoteWrapper::ReadResDataAndPrepareL(TInt aResId)
	{
	TResourceReader resReader;
    CleanupStack::PushL( this );
    iCoeEnv->CreateResourceReaderLC(resReader, aResId);
    TAknNoteResData resData;
    resData.ReadFromResource(resReader);
    CleanupStack::PopAndDestroy(); // Resource reader
    CleanupStack::Pop(); // this
    PrepareLC(resData.iResId);
	return resData;
	}


EXPORT_C void CAknNoteWrapper::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknNoteWrapper::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknNoteWrapper::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void* CAknNoteWrapper::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

//-------------------------------------------------------------------------------------
// CAknNoteWrapper::HandlePointerEventL()
// Due to the functionality of dialogs inherited from this father class it
// isn't necessary to check is the pointer down anywhere. Any tap, anywhere
// will close the dialog. If the up pointerevent is directed inside the area
// the HandleDialogPageEventL( EDialogPageTapped ) is called.
//-------------------------------------------------------------------------------------
//

EXPORT_C void CAknNoteWrapper::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if (aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }
            StaticDeleteL(this);     
            }
        }
    }

//-------------------------------------------------------------------------------------
// CAknNoteWrapper::HandleDialogPageEventL()
// This method is called when the CEikDialogPage, which has an observer handle
// to this class, is tapped. (it is called only on PointerUp event.)
//-------------------------------------------------------------------------------------
//
EXPORT_C void CAknNoteWrapper::HandleDialogPageEventL( TInt aEventID)
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( aEventID == MEikDialogPageObserver::EDialogPageTapped )
            {        
            StaticDeleteL(this);
            }   
        }
    }


EXPORT_C CAknConfirmationNote::CAknConfirmationNote()
    : CAknResourceNoteDialog(R_AKN_CONFIRMATION_NOTE)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxConfirmationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknConfirmationNote" );
    }

//-------------------------------------------------------------------------------------
// CAknNoteWrapper::Reserved1
//-------------------------------------------------------------------------------------
//    
EXPORT_C void CAknNoteWrapper::Reserved1()
    {
    }

EXPORT_C CAknConfirmationNote::CAknConfirmationNote( TBool aWaitingDialog )
    : CAknResourceNoteDialog( ( aWaitingDialog ? R_AKN_CONFIRMATION_NOTE_WAIT :
                                                 R_AKN_CONFIRMATION_NOTE) )
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxConfirmationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknConfirmationNote" );
    }

EXPORT_C CAknConfirmationNote::CAknConfirmationNote(CAknConfirmationNote** aSelfPtr)
    : CAknResourceNoteDialog(
        R_AKN_CONFIRMATION_NOTE, 
        REINTERPRET_CAST(CAknNoteWrapper**, aSelfPtr))
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxConfirmationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknConfirmationNote" );
    }
    
EXPORT_C void CAknConfirmationNote::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknResourceNoteDialog::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CAknConfirmationNote::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknConfirmationNote::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknConfirmationNote::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknConfirmationNote::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknConfirmationNote::CAknResourceNoteDialog_Reserved()
	{
	}

EXPORT_C CAknInformationNote::CAknInformationNote()
    : CAknResourceNoteDialog(R_AKN_INFORMATION_NOTE)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxInformationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknInformationNote" );
    }

EXPORT_C CAknInformationNote::CAknInformationNote( TBool aWaitingDialog )
    : CAknResourceNoteDialog( ( aWaitingDialog ? R_AKN_INFORMATION_NOTE_WAIT :
                                                 R_AKN_INFORMATION_NOTE) )
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxInformationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknInformationNote" );
    }

EXPORT_C CAknInformationNote::CAknInformationNote(CAknInformationNote** aSelfPtr)
    : CAknResourceNoteDialog(
        R_AKN_INFORMATION_NOTE, 
        REINTERPRET_CAST(CAknNoteWrapper**, aSelfPtr))
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxInformationNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknInformationNote" );
    }

EXPORT_C void CAknInformationNote::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknResourceNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknInformationNote::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknInformationNote::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknInformationNote::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknInformationNote::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknInformationNote::CAknResourceNoteDialog_Reserved()
	{
	}

EXPORT_C CAknErrorNote::CAknErrorNote()
    : CAknResourceNoteDialog(R_AKN_ERROR_NOTE)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxErrorNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknErrorNote" );
    }

EXPORT_C CAknErrorNote::CAknErrorNote( TBool aWaitingDialog )
: CAknResourceNoteDialog(( aWaitingDialog ? R_AKN_ERROR_NOTE_WAIT :
                                            R_AKN_ERROR_NOTE ) )
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxErrorNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknErrorNote" );
    }

EXPORT_C CAknErrorNote::CAknErrorNote(CAknErrorNote** aSelfPtr)
    : CAknResourceNoteDialog(
        R_AKN_ERROR_NOTE, 
        REINTERPRET_CAST(CAknNoteWrapper**, aSelfPtr))
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxErrorNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknErrorNote" );
    }

EXPORT_C void CAknErrorNote::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknResourceNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknErrorNote::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknErrorNote::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknErrorNote::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknErrorNote::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknErrorNote::CAknResourceNoteDialog_Reserved()
	{
	}

EXPORT_C CAknWarningNote::CAknWarningNote()
    : CAknResourceNoteDialog(R_AKN_WARNING_NOTE)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxWarningNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknWarningNote" );
    }

EXPORT_C CAknWarningNote::CAknWarningNote( TBool aWaitingDialog )
    : CAknResourceNoteDialog(( aWaitingDialog ? R_AKN_WARNING_NOTE_WAIT :
                                                R_AKN_WARNING_NOTE ) )
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxWarningNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknWarningNote" );
    }

EXPORT_C CAknWarningNote::CAknWarningNote(CAknWarningNote** aSelfPtr)
    : CAknResourceNoteDialog(
        R_AKN_WARNING_NOTE, 
        REINTERPRET_CAST(CAknNoteWrapper**, aSelfPtr))
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxWarningNoteControlUid );
#endif
    AKNTASHOOK_ADD( this, "CAknWarningNote" );
    }

EXPORT_C void CAknWarningNote::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknResourceNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknWarningNote::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknWarningNote::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknWarningNote::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknWarningNote::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknWarningNote::CAknResourceNoteDialog_Reserved()
	{
	}
	
EXPORT_C TInt CAknResourceNoteDialog::ExecuteLD()
	{	
	return CAknNoteWrapper::ExecuteLD(iResId);
	}

EXPORT_C TInt CAknResourceNoteDialog::ExecuteLD(const TDesC& aPrompt)
	{	
	return CAknNoteWrapper::ExecuteLD(iResId, aPrompt);
	}

EXPORT_C void CAknResourceNoteDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNoteWrapper::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknResourceNoteDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknResourceNoteDialog::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknResourceNoteDialog::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknResourceNoteDialog::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknResourceNoteDialog::CAknResourceNoteDialog_Reserved()
	{
	}

// End of File
