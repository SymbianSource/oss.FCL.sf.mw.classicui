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
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include "eikccpu.h"
#include <eikedwin.h>
#include <eikbtgpc.h>
#include <aknenv.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikappui.h>
#include <eikdialg.h>
const TInt KLeftSoftkeyIndex = 0;
const TInt KRightSoftkeyIndex = 2;
const TInt KNullCommandId = -1;

// declare the function IsCbaEmbeddedInDialog
TBool IsCbaEmbeddedInDialog( const TInt& aFlags );

/**
* Internal extension class for CAknCcpuSupport.
*
* @since 9.2
*
* @internal
*/
NONSHARABLE_CLASS( CAknCcpuSupportExtension ) : public CBase
    {
public: // Construction and destruction

    CAknCcpuSupportExtension();
    ~CAknCcpuSupportExtension();

public: // Data
    TBool iIsCbaEmded;
    // Owned
    CEikButtonGroupContainer* iCba;
    // not owned
    CEikButtonGroupContainer* iDialogCba;
    };

CAknCcpuSupportExtension::CAknCcpuSupportExtension()
    {
    }

CAknCcpuSupportExtension::~CAknCcpuSupportExtension()
    {
    delete iCba;
    }

//
// CAknCcpuSupport
//

enum TAknCcpuSupportFlags
	{
	EFocused
	};

EXPORT_C CAknCcpuSupport::CAknCcpuSupport( MEikCcpuEditor* aEditor )
: iEditor( aEditor )
	{
	}

EXPORT_C CAknCcpuSupport::~CAknCcpuSupport()
	{
	if ( iMenu )
	    {
		iMenu->RemoveEditMenuObserver(this);
	    }
	TRAP_IGNORE( DeleteCBAL() );
	iEikonEnv->EikAppUi()->RemoveFromStack( this );
	delete iExtention;
	}

EXPORT_C void CAknCcpuSupport::ConstructL()
	{
    iExtention = new ( ELeave ) CAknCcpuSupportExtension;
	iEikonEnv->EikAppUi()->AddToStackL( this, ECoeStackPriorityFep-1, ECoeStackFlagRefusesFocus );
	HandleFocusChangeL();
	}

EXPORT_C void CAknCcpuSupport::HandleSelectionChangeL()
	{
	if ( iExtention->iCba )
	    {
		UpdateCBALabelsL();
	    }
	}

EXPORT_C void CAknCcpuSupport::HandleFocusChangeL()
	{
	TBool focused = iEditor->CcpuIsFocused();
	if ( COMPARE_BOOLS( focused, iFlags[EFocused] ) )
	    {
		return;
	    }

	iFlags.Assign( EFocused, focused );

	if ( focused )
		{
		MopGetObject( iMenu );
		if ( iMenu )
		    {
			iMenu->SetEditMenuObserver( this );
		    }
		}
	else
		{
		if ( iMenu )
			{
			iMenu->RemoveEditMenuObserver( this );
			iMenu = NULL;
			}
		}

	if ( iExtention->iCba && !focused )
		{
		// something has caused loss of focus while shift is pressed - drop everything.
		DeleteCBAL();
		}
	}

EXPORT_C TKeyResponse CAknCcpuSupport::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
	{
	if ( !iFlags[EFocused] )
	    {
		return EKeyWasNotConsumed;
	    }

	if ( aKeyEvent.iCode == EKeyF21 )		// FEP generates F21 on long shift press
		{
		if ( aType == EEventKey )
			{		
			DeleteCBAL();
			CEikAppUi* eikAppUi = (CEikAppUi *)CCoeEnv::Static()->AppUi();
			if( eikAppUi && eikAppUi->IsDisplayingDialog() && eikAppUi->TopFocusedControl() )
				{
				CEikDialog* dlg = eikAppUi->TopFocusedControl()->MopGetObject( dlg );
				if ( dlg && IsCbaEmbeddedInDialog( dlg->DialogFlags() ) )
					{
					CEikButtonGroupContainer* currentCba = dlg->MopGetObject( currentCba );
					
					if ( currentCba )
						{
						CEikCba* dlgcba = static_cast<CEikCba*>( currentCba->ButtonGroup() );
						TUint flags( 0 ); 
						flags |= CEikButtonGroupContainer::EIsEmbedded | CEikButtonGroupContainer::EAddToStack;
                        iExtention->iCba = CEikButtonGroupContainer::NewL( 
                                CEikButtonGroupContainer::ECba, 
                                CEikButtonGroupContainer::EHorizontal, 
								this, R_AVKON_SOFTKEYS_EMPTY, flags );
						
						CEikCba* cba = static_cast<CEikCba*>(
                                iExtention->iCba->ButtonGroup() );					   
						
                        if( !iExtention->iIsCbaEmded )
							{
							currentCba->AddCommandToStackL( KLeftSoftkeyIndex, -1, KNullDesC, NULL, NULL );
							currentCba->AddCommandToStackL( KRightSoftkeyIndex, -1, KNullDesC, NULL, NULL );
							currentCba->ActivateL();
							currentCba->DrawNow();
                            iExtention->iDialogCba = currentCba;
                            iExtention->iIsCbaEmded = ETrue;
							}
					
						cba->SetButtonGroupFlags( ~( EEikCbaFlagTransparent | EEikCbaFlagOutlineFont ) );
						TRect dlgRect(dlg->Rect());
						TRect cbaRect(currentCba->Rect());
                        iExtention->iCba->SetRect( currentCba->Rect());
                        iExtention->iCba->SetPosition(
                            TPoint( dlg->DrawableWindow()->Position().iX, 
                                    dlg->DrawableWindow()->Position().iY + dlgRect.Height() - cbaRect.Height() ) );
                        iExtention->iCba->SetBoundingRect( dlg->Rect() );
						
						}				
					}	
				}
			if( !iExtention->iCba )//if iCba was not create in the above branch but was deleted by DeleteCBA
				{
			    iExtention->iCba = CEikButtonGroupContainer::NewL( 
			            CEikButtonGroupContainer::ECba,
			            CEikButtonGroupContainer::EHorizontal,
			            this, R_AVKON_SOFTKEYS_EMPTY );
			    iExtention->iCba->SetBoundingRect( iEikonEnv->EikAppUi()->ApplicationRect() );
				}
			UpdateCBALabelsL();
			}
		return EKeyWasConsumed;
		}  
    else if ( aType == EEventKey &&
              aKeyEvent.iCode == EKeyF18 &&
              ( aKeyEvent.iModifiers & EModifierCtrl ) )			
        {
        // FEP requests Ccpu actions with CTRL + F18         
        // Requested action is encoded in iScanCode.
        ProcessCommandL( aKeyEvent.iScanCode );
       	return EKeyWasConsumed;
        }					
	else if ( ( aKeyEvent.iScanCode == EStdKeyLeftShift || 
	            aKeyEvent.iScanCode == EStdKeyRightShift ) && 
	            aType == EEventKeyUp )
		{
		DeleteCBAL();
		}
	
	return EKeyWasNotConsumed;
	}

EXPORT_C void CAknCcpuSupport::DynInitMenuPaneL( TInt aResourceId,CEikMenuPane* aMenuPane )
	{
	if ( aResourceId == R_AVKON_EDIT_MODE_MENU || 
		aResourceId == R_AVKON_EDIT_TEXT_MENU )
		{
		aMenuPane->SetItemDimmed( EEikCmdEditCut,!iEditor->CcpuCanCut() );
		aMenuPane->SetItemDimmed( EEikCmdEditCopy,!iEditor->CcpuCanCopy() );
		aMenuPane->SetItemDimmed( EEikCmdEditPaste,!iEditor->CcpuCanPaste() );
		}
	}

EXPORT_C void CAknCcpuSupport::ProcessCommandL( TInt aCommandId )
	{
	switch ( aCommandId )
		{
		case EEikCmdEditCut:
			iEditor->CcpuCutL();
			break;
		case EEikCmdEditCopy:
			iEditor->CcpuCopyL();
			break;
		case EEikCmdEditPaste:
			iEditor->CcpuPasteL();
			break;
		case EEikCmdEditUndo:
			iEditor->CcpuUndoL();
			break;
		default:
			break;
		}
	}

void CAknCcpuSupport::UpdateCBALabelsL()
	{
	TBool change = EFalse;

	if ( iEditor->CcpuCanCopy() )
	    {
		change = UpdateCBALabelL( KLeftSoftkeyIndex, EEikCmdEditCopy, R_TEXT_SOFTKEY_COPY ) || change;
	    }
	else
	    {
		change = UpdateCBALabelL( KLeftSoftkeyIndex, KNullCommandId, R_TEXT_SOFTKEY_EMPTY ) || change;
	    }

	if ( iEditor->CcpuCanPaste() )
	    {
		change = UpdateCBALabelL( KRightSoftkeyIndex, EEikCmdEditPaste, R_TEXT_SOFTKEY_PASTE ) || change;
	    }
	else
	    {
		change = UpdateCBALabelL( KRightSoftkeyIndex, KNullCommandId, R_TEXT_SOFTKEY_EMPTY ) || change;
	    }

	if ( change )
		{
        iExtention->iCba->DrawNow();
		}
	}

TBool CAknCcpuSupport::UpdateCBALabelL( TInt aPosition, TInt aCommandId, TInt aTextResId )
	{
	if ( iExtention->iCba->ButtonGroup()->CommandId(aPosition) != aCommandId )
		{
		HBufC* buf = iEikonEnv->AllocReadResourceLC( aTextResId );
		iExtention->iCba->SetCommandL( aPosition, aCommandId, *buf );
		CleanupStack::PopAndDestroy( buf );
		return ETrue;
		}
	return EFalse;
	}

void CAknCcpuSupport::SetEmphasis( CCoeControl* /*aMenuControl*/, TBool /*aEmphasis*/ )
	{
	}

EXPORT_C void CAknCcpuSupport::HandlePointerEventL( const TPointerEvent& aPointerEvent ) 
    { 
    CAknControl::HandlePointerEventL( aPointerEvent ); 
    }

EXPORT_C void* CAknCcpuSupport::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }
void CAknCcpuSupport::DeleteCBAL()
	{
	if ( iExtention->iCba )
		{
	    delete iExtention->iCba;
	    iExtention->iCba = NULL;
		}
	if ( iExtention->iIsCbaEmded )
		{
		CEikAppUi* eikAppUi = (CEikAppUi *)CCoeEnv::Static()->AppUi();
        if( eikAppUi && eikAppUi->IsDisplayingDialog() && eikAppUi->TopFocusedControl() )
            {
            CEikDialog* dlg = eikAppUi->TopFocusedControl()->MopGetObject( dlg );
            if ( dlg )
                {
                CEikButtonGroupContainer* currentCba = dlg->MopGetObject( currentCba );
                CEikCba* dlgcba = static_cast<CEikCba*>(
                    currentCba->ButtonGroup() );
                if ( currentCba && iExtention->iDialogCba == currentCba )
                    {
                    currentCba->RemoveCommandFromStack( KLeftSoftkeyIndex, -1 );
                    currentCba->RemoveCommandFromStack( KRightSoftkeyIndex, -1 );
                    currentCba->DrawNow();
                    currentCba->ActivateL();
                    iExtention->iDialogCba = NULL;
                    iExtention->iIsCbaEmded = EFalse;
                    }
                }
            }
		}
	}

/**
 * To detect if CBA is embedded in the diaplog.
 * @param aFlags it should be CEikDialog::DialogFlags()
 * @return if an CBA is embedded in the dialog return ETrue 
 *         else return EFalse
 */
TBool IsCbaEmbeddedInDialog( const TInt& aFlags )
    {
    return !( aFlags & EEikDialogFlagFillAppClientRect ) &&
        !( aFlags & EEikDialogFlagFillScreen ) &&
        !( aFlags & EEikDialogFlagVirtualInput ) &&
        !( aFlags & EEikDialogFlagNoEmbeddedSoftkeys );
    }


