/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         For bctestform application
*
*/










// INCLUDE FILES
#include <aknutils.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <aknform.h>
#include <eikseced.h>
#include <eikedwin.h>
#include <bctestform.rsg>
#include "BCTestForm.hrh"
#include "BCTestFormView.h"
#include "BCTestFormContainer.h"


// CONSTANTS
const TInt KBCTestFormCountComponent = 1;
const TInt KBCTestFormMessageBufLength = 256;

// MACROS
#define BCTestForm_BACKGROUND_COLOR AKN_LAF_COLOR( 219 )

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestFormContainer::CBCTestFormContainer( CBCTestFormView* )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestFormContainer::CBCTestFormContainer( CBCTestFormView* aView )
    :   iView( aView ),
	iLabel( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::ConstructL( const TRect& )
// Symbian 2nd phase constructor can leave.
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::ConstructL( const TRect& aRect )
    {
    CRepository* repository = NULL;
    TRAPD(ret, repository = CRepository::NewL(KCRUidAknFep));
    if (ret == KErrNone)
        {
        ret = repository->Set( KAknFepPredTxtFlag, 0 );
        }
    delete repository;

    CreateWindowL();

    CreateLabelL();


    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestFormContainer::~CBCTestFormContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFormContainer::~CBCTestFormContainer()
    {
    delete iLabel;
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::SetTextToLabelL( TInt )
//
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::SetTextToLabelL( TInt aResourceId )
    {
    TBuf<KBCTestFormMessageBufLength> messageString( NULL );
    iCoeEnv->ReadResourceL( messageString, aResourceId );
    iLabel->SetTextL( messageString );
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::DisplayFormL( TInt )
//
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::DisplayFormL( TInt aResourceId )
    {
    CAknForm* form = new( ELeave ) CAknForm;
    CleanupStack::PushL( form );
    form->ConstructL();
    CleanupStack::Pop();

    if ( aResourceId == R_BCTESTFORM_DOUBLE_LINE_FORM)
		{
		form->PrepareLC( aResourceId );
		TBuf<KBCTestFormMessageBufLength> edwinString( NULL );
		iCoeEnv->ReadResourceL( edwinString, R_BCTESTFORM_TEXT_EDWIN_TEXT );
		CEikEdwin* myEdwin =
		    STATIC_CAST(CEikEdwin*,
				form->ControlOrNull(EBCTestFormDlgCtrlIdEdwin01)) ;
		if ( myEdwin )
		    {
		    myEdwin->SetTextL(&edwinString);
		    }
		TBuf<KBCTestFormMessageBufLength> secretString( NULL );
		iCoeEnv->ReadResourceL( secretString, R_BCTESTFORM_TEXT_SECRET_TEXT );
		CEikSecretEditor* secEd =
		    STATIC_CAST(CEikSecretEditor*,
				form->ControlOrNull(EBCTestFormDlgCtrlIdSecret01));
		if ( secEd )
		    {
		    secEd->SetText(secretString);
		    }
		form->RunLD();
		}
    else if ( aResourceId == R_BCTESTFORM_DOUBLE_AND_SINGLE_LINE_FORM)
		{
		form->PrepareLC( aResourceId );
		TBuf<KBCTestFormMessageBufLength> edwinString( NULL );
		iCoeEnv->ReadResourceL( edwinString, R_BCTESTFORM_TEXT_EDWIN_TEXT );
		CEikEdwin* myEdwin =
		    STATIC_CAST(CEikEdwin*,
				form->ControlOrNull(EBCTestFormDlgCtrlIdEdwin01)) ;
		if ( myEdwin )
		    {
		    myEdwin->SetTextL(&edwinString);
		    }
		myEdwin = STATIC_CAST(CEikEdwin*,
				      form->ControlOrNull(EBCTestFormDlgCtrlIdEdwin11)) ;
		if ( myEdwin )
		    {
		    myEdwin->SetTextL(&edwinString);
		    }
		form->RunLD();
		}
    else
		{
		form->ExecuteLD( aResourceId );
		}
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::CreateLabelL()
// Creates label object.
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::CreateLabelL()
    {
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetAlignment( EHCenterVCenter );
	    iLabel->SetFont( iEikonEnv->TitleFont() );

        }
    SetTextToLabelL( R_BCTESTFORM_TEXT_LABEL_TITLE );
    }

// ----------------------------------------------------------------------------
// TKeyResponse CBCTestFormContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CBCTestFormContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }
    switch ( aKeyEvent.iCode )
        {
        case EKeySpace:
	case EKeyOK:
            iView->DisplayNextOutlineL();
            DrawNow();
            break;
        default:
            return EKeyWasNotConsumed;
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::SizeChanged()
// Called by framework when the view size is changed
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::SizeChanged()
    {
    iLabel->SetRect( Rect() );
    }

// ----------------------------------------------------------------------------
// TInt CBCTestFormContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CBCTestFormContainer::CountComponentControls() const
    {
    // returns nbr of controls inside this container
    return KBCTestFormCountComponent;
    }

// ----------------------------------------------------------------------------
// CCoeControl* CBCTestFormContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CBCTestFormContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex ) // Component is...
        {
        case EBCTestFormComponentLabel: // Label object.
            return iLabel;
        default: // Exception : returns NULL value.
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( BCTestForm_BACKGROUND_COLOR );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ----------------------------------------------------------------------------
// void CBCTestFormContainer::HandleResourceChange(TInt)
// Makes dynamic resolution change smoother
// ----------------------------------------------------------------------------
//
void CBCTestFormContainer::HandleResourceChange(TInt aType)
    {
    if (aType == KEikDynamicLayoutVariantSwitch)
        {
        }
    CCoeControl::HandleResourceChange( aType );
    }

// End of File
