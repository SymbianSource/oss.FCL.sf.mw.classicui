/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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

// AknDialog.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include <AknDialog.h>
#include <eikmenub.h>
#include <eikenv.h>
#include <aknappui.h>
#include "aknenv.h"
#include <eikcapc.h>
#include <eikdialogext.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <aknsoundsystem.h>
#include "aknitemactionmenuregister.h"

#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include "AknUtils.h"

#include <skinlayout.cdl.h>
using namespace SkinLayout;



class CAknDialogAttributes: public CBase
	{
public:
	~CAknDialogAttributes()
		{
		delete iBgContext;
		delete iBrushAndPenContext;
		}
public: // data
	TInt iAknDialogFlags;
	CAknsFrameBackgroundControlContext* iBgContext;	
    CCoeBrushAndPenContext* iBrushAndPenContext;
	TRect iOuterRect;
	TRect iInnerRect;
	TBool iNeedsUpdate;
	};

/**
 * Constructor 
 */
EXPORT_C CAknDialog::CAknDialog() 
	{
	}


/**
 * Creates a menu using a menu resource.
 * A menu resource MUST be specified - this function will Panic otherwise.  If a menu is not required use CEikDialog!
 */
EXPORT_C void CAknDialog::ConstructL(TInt aMenuTitleResourceId)
	{
    if ( !iAttributes ) 
        {
		AttributesL();        
		}
	
	CreateMenuBarL(aMenuTitleResourceId);
	
	iAttributes->iAknDialogFlags &= ~EAknDialogFlagNotConstructed;
	}

/**
 *
 */
EXPORT_C CAknDialog::~CAknDialog() 
	{
    AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( NULL );

    if ( iCoeEnv->AppUi() && iAttributes )
		if (iAttributes->iAknDialogFlags&EAknDialogFlagDefaultSounds) // return original sound stack
			{
			iAvkonAppUiBase->KeySounds()->PopContext();
			}

	if (iMenuBar) 
		{
		if ( iAttributes )
			{
			iAttributes->iAknDialogFlags |= EAknDialogFlagDialogDeleted;
			}
		HideMenu();
		iEikonEnv->EikAppUi()->RemoveFromStack(iMenuBar);
		delete iMenuBar;
		}
	delete iAttributes;
	}

EXPORT_C void CAknDialog::PrepareLC(TInt aResourceId)
	{ 
	if (!iMenuBar)
		{
		// PrepareLC has to keep ownership of "this".
		CleanupStack::PushL(this);	
		CreateMenuBarL(R_AVKON_DIALOG_EMPTY_MENUBAR); // empty menu bar
		CleanupStack::Pop(this);
		}
	CEikDialog::PrepareLC(aResourceId);
	}

EXPORT_C TInt CAknDialog::RunLD()
	{
	return CEikDialog::RunLD();
	}

/**
 * Swap the Application menu with the Form's menu before displaying
 *
 */
EXPORT_C TInt CAknDialog::ExecuteLD(TInt aResourceId) 
	{
    if ( iCoeEnv->AppUi() ) // Enable default tones while dialog / form is on screen
        {
        CleanupStack::PushL(this);
		if (!iAttributes)
			{
			AttributesL();
			iAttributes->iAknDialogFlags |= EAknDialogFlagNotConstructed; // Way to indicate to SetEmphasis that other members are  not accessible
			}

        iAvkonAppUiBase->KeySounds()->PushContextL(R_AVKON_DEFAULT_SKEY_LIST);
        iAttributes->iAknDialogFlags |= EAknDialogFlagDefaultSounds;
        CleanupStack::Pop();
        }

	return ( CEikDialog::ExecuteLD(aResourceId) );	
    }

/**
 *From MEikMenuObserver
 * (called when menu is cancelled)
 * Called also from destructor ( EAknDialogFlagDialogDeleted is set)
 */
EXPORT_C void CAknDialog::SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)
	{
	if (!iAttributes 
		|| iAttributes->iAknDialogFlags & EAknDialogFlagNotConstructed
		|| iAttributes->iAknDialogFlags & EAknDialogFlagDialogDeleted)
		return;

	CEikAppUi* appUi = iEikonEnv->EikAppUi();
	appUi->RemoveFromStack(aMenuControl);
    // Remove focus from aMenuControl because AppUi's RemoveFromStack won't do
    // that.
    aMenuControl->SetFocus( EFalse );
	TRAP_IGNORE(appUi->AddToStackL(aMenuControl, aEmphasis ? ECoeStackPriorityDialog : ECoeStackPriorityMenu));
	appUi->UpdateStackedControlFlags(this, aEmphasis ? ECoeStackFlagRefusesFocus : 0, ECoeStackFlagRefusesFocus);
	appUi->UpdateStackedControlFlags(aMenuControl, aEmphasis ? 0 : ECoeStackFlagRefusesFocus, ECoeStackFlagRefusesFocus);
	appUi->HandleStackChanged();
	}

/**
 * This function intialiases the items on the menu.  It's used to disable and enable menu items and may be
 * over ridden to add new ones.
 * NOTE that it might be called with the 'wrong' ResourceId so it must do a check and not assume.
 *
 */
EXPORT_C void CAknDialog::DynInitMenuPaneL(TInt /*aResourceId*/, CEikMenuPane* /*aMenuPane*/) 
	{
	}

/**
 *From MEikCommandObserver
 */
EXPORT_C void CAknDialog::ProcessCommandL(TInt /* aCommandId */)
	{
	HideMenu();
	}


/**
 * From CCoeControl
 *
 * If MMC is supported always process user input (MMC PIN requester does not seem
 * to have focus when it pops up)
 */
EXPORT_C TKeyResponse CAknDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) 
	{
	if (IsFocused() ||
		(aType == EEventKey && aKeyEvent.iCode == EKeyEscape)
		)
		return (CEikDialog::OfferKeyEventL(aKeyEvent, aType));
	else
		return EKeyWasNotConsumed;
	}



/**
 *
 * From CEikDialog - If there is an Options key then pops up menu, otherwise exits.  Override this if necessary.
 */
EXPORT_C TBool CAknDialog::OkToExitL(TInt aButtonId) 
	{
	TBool retVal;

	if (iMenuBar)
		HideMenu();
	
	if (aButtonId == EAknSoftkeyOptions)
		{
		DisplayMenuL();
		retVal = EFalse;
		}
	else 
		{
		retVal = ETrue;
		}

	if (aButtonId == EAknSoftkeyMark || aButtonId == EAknSoftkeyUnmark)
		{
		retVal = EFalse;
		}

	return retVal;
	}


/**
 * 
 */
EXPORT_C void CAknDialog::DisplayMenuL() 
	{
	iMenuBar->TryDisplayMenuBarL();
	}

/**
 * 
 */
EXPORT_C void CAknDialog::HideMenu() 
	{
	iMenuBar->StopDisplayingMenuBar();
	}

EXPORT_C void CAknDialog::FocusChanged(TDrawNow aDrawNow)
	{
	if (!iAttributes || iAttributes->iAknDialogFlags & EAknDialogFlagDialogDeleted)
		return;
	TInt controlID = IdOfFocusControl();
	if (controlID)
		Line(controlID)->SetFocus(IsFocused(), aDrawNow);			
	}

/**
 * 
 */
EXPORT_C TBool CAknDialog::MenuShowing() const
	{
	return iMenuBar->IsDisplayed();
	}


EXPORT_C void CAknDialog::Reserved_MtsmPosition()
	{
	}

EXPORT_C void CAknDialog::Reserved_MtsmObject()
	{
	}

EXPORT_C void CAknDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CEikDialog::HandlePointerEventL(aPointerEvent);
    }   

EXPORT_C void* CAknDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

void CAknDialog::CreateMenuBarL(TInt aMenuTitleResourceId)
	{
	if (iMenuBar)
		{
		// just replace the content if it doesn't already exist
		iMenuBar->TitleArray()->ResetAndDestroy();
		iMenuBar->SetMenuTitleResourceId(aMenuTitleResourceId);
		}
	else
		{
		CEikMenuBar* newMenuBar = new (ELeave) CEikMenuBar();
		CleanupStack::PushL(newMenuBar);
		newMenuBar->ConstructL(this, NULL, aMenuTitleResourceId);
		iEikonEnv->EikAppUi()->AddToStackL(newMenuBar,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus);
		iMenuBar=newMenuBar;
		CleanupStack::Pop(); // now owned by this Dialog.
		}

    AknItemActionMenuRegister::SetConstructingMenuBarOwnerL( this );
	}

//
// UpdateBgContext is done here because we dont want to create huge icons 
// always when dialog is launched. The icon is anyway used only when
// queries are used, so deferring its creation to MopSupplyObject;
// this saves considerable amount of time and memory for non-popup
// dialogs. SetFrameRects renders the qsn_fr_popup, so deferring that call.
//
static void UpdateBgContext(CAknDialogAttributes &aAttrs)
	{
	if (aAttrs.iNeedsUpdate)
		{
		TRect outerRect = aAttrs.iOuterRect;
		TRect innerRect = aAttrs.iInnerRect;
		aAttrs.iBgContext->SetFrameRects( outerRect, innerRect );
		aAttrs.iNeedsUpdate = EFalse;
		}
	}

EXPORT_C TTypeUid::Ptr CAknDialog::MopSupplyObject(TTypeUid aId)
	{	
	// Must test on the type of dialog before supplying an object
	if ( Extension() ) { 
	    if ( aId.iUid == MAknsControlContext::ETypeId && 
		    Extension()->LayoutCategory() == CEikDialogExtension::EPopupLayout )
			    {
		    if (!iAttributes)
			    {
			    TRAPD( err, AttributesL() );
			    if ( err )
				    {
				    delete iAttributes;
				    iAttributes = 0;
				    return CEikDialog::MopSupplyObject(aId);
				    }
			    else
				    {
				    iAttributes->iAknDialogFlags |= EAknDialogFlagNotConstructed; // Way to indicate to SetEmphasis that other members are  not accessible
				    }
			    }
			UpdateBgContext(*iAttributes);
		    return MAknsControlContext::SupplyMopObject(aId, iAttributes->iBgContext );
		    }
        }
	if (aId.iUid == CEikMenuBar::ETypeId)
		return aId.MakePtr(iMenuBar);
	else
		return CEikDialog::MopSupplyObject(aId);
	}

EXPORT_C void CAknDialog::Draw(const TRect& aRect) const
	{

		CEikDialog::Draw(aRect); // Frame drawing done in eikdialog
	}
	
EXPORT_C void CAknDialog::SizeChanged()
	{
	if (iAttributes)
		{
		TRect windowRect = Rect();
	
		TAknLayoutRect topLeft;
        topLeft.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_2());

		TAknLayoutRect bottomRight;
        bottomRight.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_5());

		TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
		TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

		iAttributes->iOuterRect = outerRect;
		iAttributes->iInnerRect = innerRect;
		iAttributes->iNeedsUpdate = ETrue;
		iAttributes->iBgContext->SetParentPos( PositionRelativeToScreen() );
		}
	CEikDialog::SizeChanged();
	}

EXPORT_C void CAknDialog::CEikDialog_Reserved_1()
	{
	}
	
EXPORT_C void CAknDialog::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknDialog::CAknDialog_Reserved()
	{
	}

CAknDialogAttributes* CAknDialog::AttributesL()
	{
	if ( !iAttributes )
		{
		iAttributes = new (ELeave) CAknDialogAttributes();
        
		TRect windowRect = Rect();
	
		TAknLayoutRect topLeft;
        topLeft.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_2());

		TAknLayoutRect bottomRight;
		bottomRight.LayoutRect(windowRect, ELayoutEmpty, 169, ELayoutEmpty, ELayoutEmpty, 2, 7,7);
        bottomRight.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
		TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

		iAttributes->iBgContext = CAknsFrameBackgroundControlContext::NewL(
				KAknsIIDQsnFrPopup, outerRect, innerRect, ETrue );


		if ( &Window() )
			iAttributes->iBgContext->SetParentPos( PositionRelativeToScreen() );
		}
	
	return iAttributes; 
	}

// end of CAknDialog
