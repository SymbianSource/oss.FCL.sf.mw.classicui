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
*   This class handles setting_text_pane and setting_code_pane (the latter in 
*	the case of integers.  There is a common base class to soak up some common 
*	textual functionality.
*
*
*/


#include "akntextsettingpage.h"
#include "aknsettingpage.h"

#include "akntextcontrol.h"
#include <AknsDrawUtils.h>

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknsControlContext.h>
#include <AknsFrameBackgroundControlContext.h>
#include <eikedwob.h>

#include <AknTasHook.h>

class CAknTextSettingPageExtension : public CBase
								   , public MEikEdwinObserver
    {
public:
    static CAknTextSettingPageExtension* NewL(CAknTextSettingPage* aExtensionOwner )
        {
        CAknTextSettingPageExtension* extension = new (ELeave) CAknTextSettingPageExtension( aExtensionOwner );
        CleanupStack::PushL(extension);
        extension->ConstructL();
        CleanupStack::Pop(extension);
        return extension;
        }
        
    ~CAknTextSettingPageExtension()
        {
        iExtensionOwner = 0;
        }
        
    TInt PreviousCba()
        {
        return iPreviousCba;
        };
    void SetPreviousCba(TInt aCbaId)
        {
        iPreviousCba = aCbaId;
        }
	TBool PopupState()
	 	{
		return iPopupState;
		}

	virtual void HandleEdwinEventL( CEikEdwin* /*aEdwin*/, TEdwinEvent aEventType )
		{
		if( iExtensionOwner && MEikEdwinObserver::EEventChinesePopupClose == aEventType )
			{
			iPopupState = EFalse;
			iExtensionOwner->ProcessPopupStateChangesL();
			}
	     else if(iExtensionOwner && MEikEdwinObserver::EEventChinesePopupOpen == aEventType)
	     	{
	     	iPopupState = ETrue;
	     	}			
		}
    
private:
    void ConstructL()
        {
        }
        
    CAknTextSettingPageExtension(CAknTextSettingPage*  aExtensionOwner )
        : iPreviousCba( 0 ), iExtensionOwner( aExtensionOwner )
        , iPopupState( EFalse )
        {
        }
        
private:
    TInt iPreviousCba;
    CAknTextSettingPage* iExtensionOwner;
    TBool iPopupState;  // when open the popup set popup state flag  to 1
    };

/**
 * Exported in case others want to derive from this class
 *
 */
EXPORT_C CAknEdwinSettingPage::CAknEdwinSettingPage( TInt aResourceId ) 
	: CAknSettingPage(aResourceId)
	{
	AKNTASHOOK_ADD( this, "CAknEdwinSettingPage" );
	}


EXPORT_C CAknEdwinSettingPage::CAknEdwinSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId ) 
								:	CAknSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId )
	{
	AKNTASHOOK_ADD( this, "CAknEdwinSettingPage" );
	}

/**
 * All setting pages containing edwins will have the same draw code
 *
 */
EXPORT_C void CAknEdwinSettingPage::Draw(const TRect& aRect) const
	{
	BaseDraw( aRect );
	}

/** 
 *
 * Type-specific access to the text editor control
 *
 */
EXPORT_C CEikEdwin* CAknEdwinSettingPage::TextControl()
	{
	return STATIC_CAST( CEikEdwin*, EditorControl());
	}
	
EXPORT_C void CAknEdwinSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSettingPage::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CAknEdwinSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
* CAknEdwinSettingPage reserved methods
*/
EXPORT_C void CAknEdwinSettingPage::CAknEdwinSettingPage_Reserved_1()
	{
	}



///////////////////////////////////////////////////////////////////////
//
// CAknTextSettingPage
//
///////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced text + flags
 *
 */
EXPORT_C CAknTextSettingPage::CAknTextSettingPage( TInt aResourceId, TDes& aText, TInt aFlags ):
	 CAknEdwinSettingPage(aResourceId),iText(aText), iTextSettingPageFlags( aFlags )
	{
	AKNTASHOOK_ADD( this, "CAknTextSettingPage" );
	}

EXPORT_C CAknTextSettingPage::CAknTextSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TDes& aText, 
								TInt aTextSettingPageFlags)
								:	CAknEdwinSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId ), 
									iText( aText ),  
									iTextSettingPageFlags( aTextSettingPageFlags )
	{
	AKNTASHOOK_ADD( this, "CAknTextSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknTextSettingPage::~CAknTextSettingPage()
	{
	if( TextControl( ) )
		{	
	    TextControl( )->RemoveEdwinObserver( iExtension );
		}
	AKNTASHOOK_REMOVE();
	delete iBackupText;
	
    delete iExtension;
	}


/** 
 *
 * The 2nd stage construction. Stored internal resource is used to perform the
 * construction.
 *
 */
EXPORT_C void CAknTextSettingPage::ConstructL()
	{
	BaseConstructL();
	iBackupText = iText.AllocL();
	CEikEdwin* editor = TextControl();

	// Inhibit predictive text entry unless allowed by API
	if ( !(iTextSettingPageFlags & EPredictiveTextEntryPermitted) )
		editor->SetAknEditorFlags( EAknEditorFlagNoT9 | editor->AknEdwinFlags() );
	
	if(!IsEditable())
	    {
	    editor->SetReadOnly(ETrue);
	    editor->SetAknEditorFlags( CEikEdwin::EDisplayOnly | editor->AknEdwinFlags() );
	    }

	// Determine the maximum size of the text.

	// First get the maximum extent that may have been set by resource
	TInt maxLen = editor->MaxLength();
	
	// Get maximum length from the iText
	TInt desMaxLen = iText.MaxLength();

	// Use the minimum value of the two
	if ( maxLen == 0 ) // Not set in resource
		{
		editor->SetMaxLength( desMaxLen );
		}
	else
		{
		editor->SetMaxLength( Min( maxLen, desMaxLen ) );
		}

	// Note that this will set the text to be the length in the passed descriptor, despite the maxlength 
	// set above; subsequent editing will ensure that the editor can only decrease in size.
	editor->SetTextL( &iText );
	
	iExtension = CAknTextSettingPageExtension::NewL(this);

	editor->AddEdwinObserverL( iExtension );
	// Initialize the validity and CBAs
	CheckAndSetDataValidity();
	UpdateCbaL();

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	TextControl()->ScrollBarFrame()->VerticalScrollBar()->SetMopParent(this);
	}

/**
 * Acts upon changes in the hosted control's state. 
 *
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
EXPORT_C void CAknTextSettingPage::HandleControlEventL(CCoeControl* /*aControl*/,
				 MCoeControlObserver::TCoeEvent aEventType)
	{
	// This event is used as it is called at least every time an edit is made to 
	// the edwin.
	if ( aEventType == EEventStateChanged )
		{
		if ( iUpdateMode == EUpdateWhenChanged)
			UpdateSettingL();

		// This updates the CBA depending on text length
		CheckAndSetDataValidity();
		UpdateCbaL();
		}
	}

/**
 *
 * This routine is called before the editor when the editor is first displayed.  This routine
 * puts in altered softkey bindings if there is zero-length text.
 *
 */
EXPORT_C void CAknTextSettingPage::DynamicInitL()
	{
	UpdateCbaL();
	}
/**
 *
 * This routine is called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CAknTextSettingPage::UpdateSettingL()
	{
	UpdateTextL();

	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	
	}
/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CAknTextSettingPage::UpdateTextL()
	{
	CEikEdwin* edwin = TextControl();
	edwin->CheckValidityOfChars(0, edwin->TextLength());

	HBufC* heapText = edwin->GetTextInHBufL();
	// GetTextInHBufL returns a null pointer if the text length is zero!
	if ( heapText )
		{
		iText.Copy(heapText->Left( iText.MaxLength() ) );
		delete heapText;
		}
	else
		{
		iText.SetLength( 0 );
		}
	}
/**
 *
 * The value is copied out and the call back called if there is an observer
 *
 */
EXPORT_C void CAknTextSettingPage::AcceptSettingL()
	{
	UpdateTextL();
	}

/** 
 * 
 * If the setting page is cancelled, this is called to restore the backed up copy of the 
 * input text
 *
 */
EXPORT_C void CAknTextSettingPage::RestoreOriginalSettingL()
	{
	iText.Copy( *iBackupText );
	}

void CAknTextSettingPage::ProcessPopupStateChangesL()
	{
	UpdateCbaL();
	}
EXPORT_C void CAknTextSettingPage::UpdateCbaL()
	{
	if ( IsStopActiveSchudlerCalled() )
	    {
	    CAknSettingPage::UpdateCbaL();
	    return;
	    }

	// Modify the CBA labels if the text goes to zero length or becomes non-zero
    TInt cbaId = 0;    
	if ( !DataValidity() || !IsEditable() )
	    {
	    cbaId = InvalidDataCbaResourceId();	    
	    }		
	else
	    {
	    cbaId = DefaultCbaResourceId(); 
	    }
    if( (iExtension->PreviousCba() != cbaId) && ( !iExtension->PopupState() ) )
	    {
	    Cba()->SetCommandSetL( cbaId );
	    Cba()->DrawDeferred();
	    iExtension->SetPreviousCba( cbaId );
	    }	
	}

EXPORT_C void CAknTextSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation
	
	TAknLayoutRect layoutRect;
	
	layoutRect.LayoutRect(
	    SettingItemContentRect( ETrue ),
        AknLayoutScalable_Avkon::setting_text_pane_copy1( 0 ) );
	TRect parentRect( layoutRect.Rect() );
	
	layoutRect.LayoutRect(
	   parentRect,
	   AknLayoutScalable_Avkon::input_focus_pane_cp1_copy1() );
	TRect edwinFrameRect( layoutRect.Rect() );

	layoutRect.LayoutRect(
	    parentRect,
	    AknLayoutScalable_Avkon::indicator_popup_pane_cp5() );
	TRect indicatorRect( layoutRect.Rect() );
	    
	iEdwinLayoutRect.LayoutRect(
	    parentRect,
	    AknLayoutScalable_Avkon::list_set_text_pane_copy1( 0 ) );
	TRect edwinRect( iEdwinLayoutRect.Rect() );

    TAknLayoutScalableParameterLimits textLimits(
        AknLayoutScalable_Avkon::set_text_pane_t1_copy1_ParamLimits() );
	
    TAknTextComponentLayout layout;
    RArray<TAknTextComponentLayout> array;
    
    for ( TInt i = textLimits.FirstRow(); i <= textLimits.LastRow(); ++i )
        {
        array.Append(
            AknLayoutScalable_Avkon::set_text_pane_t1_copy1( 0, 0, i ) );
        }
    
    AknLayoutUtils::LayoutEdwin( TextControl(),
                                 edwinRect,
                                 layout.Multiline( array ),
                                 EAknsCIQsnTextColorsCG26 );
            
    array.Close();

    layoutRect.LayoutRect(
        edwinFrameRect,
        AknLayoutScalable_Avkon::set_opt_bg_pane_g1_copy1() );
    SetEditedItemFrameRects( edwinFrameRect, layoutRect.Rect() );
    
    SetEditorIndicatorRect( indicatorRect );

    if ( !TextControl()->ScrollBarFrame() )
        {
        TRAP_IGNORE(
            {
            TextControl()->CreateScrollBarFrameL();
            TextControl()->ScrollBarFrame()->SetScrollBarVisibilityL( 
                CEikScrollBarFrame::EOff,CEikScrollBarFrame::EOn );
            });
        }
    
    if ( TextControl()->ScrollBarFrame() )
        {
        layoutRect.LayoutRect(
            Rect(), 
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::settings_container_pane( 0 ),
                AknLayoutScalable_Avkon::listscroll_set_pane_copy1( 0 ) ) );
        
        AknLayoutUtils::LayoutVerticalScrollBar(
            TextControl()->ScrollBarFrame(), 
            layoutRect.Rect(),
            AknLayoutScalable_Avkon::scroll_pane_cp121_copy1( 0 ) );       
        }
	}

/**
* Validity is alway ETrue unless the flag asking for some non-whitespace data is set.
* If set, and if there is an edwin, then check to see that there is a valid character 
* somewhere in the text
*/
EXPORT_C void CAknTextSettingPage::CheckAndSetDataValidity()
	{
    TBool validity(ETrue);
	
	if ( ! (iTextSettingPageFlags & EZeroLengthAllowed ) )
		{
		CEikEdwin* edwin =  TextControl();
		if ( edwin )
			{
			// Use access to Text() to get at text without allocating anything
			TPtrC text = edwin->Text()->Read(0);
			
            // we shold not have only spaces in the text    
			validity &= AknTextUtils::IsEmptyText( text );
			
			_LIT( KEnterSymbol, "\x21b2\x2029" );
			if ( text.Compare( KEnterSymbol ) == 0 )
			    {
			    validity = EFalse;
			    }
			
			// check that enter char does not come here
			TInt flags = edwin->UserFlags();
			TInt flags2 = edwin->AknEdwinFlags();
			
			
			// check that all chars are valid
			for(TInt n=0;validity && n<text.Length();n++)
			    {
			    TChar ch = text[n];
			    //validity &= ch.IsAlpha();
			    }
			}
		else
			{
			validity = EFalse;			
			}
		}
	SetDataValidity( validity );
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknTextSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknTextSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknTextSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknEdwinSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknTextSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }


/** 
*
* This routes the keys to the editor. 
* However, if the menu is showing, then events have to be forwarded manually to it. 
*
*/
EXPORT_C TKeyResponse CAknTextSettingPage::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType) 
	{
    if( IsStopActiveSchudlerCalled() )
        {
        return EKeyWasConsumed;
        }
	if ( aType == EEventKey )
	    {
	    if( aKeyEvent.iCode == EKeyEnter )
	        {
	        CEikEdwin* ed = STATIC_CAST( CEikEdwin*, EditorControl());
	        return ed->OfferKeyEventL(aKeyEvent, aType);
	        }
	    }
    return CAknSettingPage::OfferKeyEventL(aKeyEvent, aType);
	}

/**
* Framework method to determine if it OK to exit the setting page.
* Derived classes may check for valid data before allowing the dismissal of the 
* setting page.
*/
EXPORT_C TBool CAknTextSettingPage::OkToExitL(TBool aAccept)
    {
	// FEP may reject input causing editing be cancelled
	// user in between keypress and editing cancellation may press Ok
		
	// here we will force fep either to commit or to cancel by changing focus
    CEikEdwin* ed = STATIC_CAST( CEikEdwin*, EditorControl());
    TInt cursorPos = ed->CursorPos();
    
    CCoeEnv *coeEnv = CCoeEnv::Static();
    CCoeFep* fep = coeEnv->Fep();
    if(fep)
        fep->HandleChangeInFocus(); // will also commit changes in fep
    
    ed->SetFocus(ETrue); // return focus and selection
    ed->ClearSelectionL();
    ed->SetCursorPosL(cursorPos, EFalse);
	
	if(aAccept)
	    return(DataValidity());
	else
	    return ETrue;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknTextSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknTextSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknTextSettingPage::CAknSettingPage_Reserved_2()
	{
	}

/**
* CAknEdwinSettingPage reserved methods
*/
EXPORT_C void CAknTextSettingPage::CAknEdwinSettingPage_Reserved_1()
	{
	}

/////////////////////////////////////////////////////////////////////////
//
// Integer Edwin
//
/////////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced text + flags
 *
 */
EXPORT_C CAknIntegerSettingPage::CAknIntegerSettingPage( TInt aResourceId, TInt& aValue, TInt aFlags ):
	 CAknEdwinSettingPage(aResourceId),iValue(aValue), iIntegerSettingPageFlags( aFlags )
	{
	AKNTASHOOK_ADD( this, "CAknIntegerSettingPage" );
	}

EXPORT_C CAknIntegerSettingPage::CAknIntegerSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TInt& aValue, 
								TInt aIntegerSettingPageFlags)
								:	CAknEdwinSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId ), 
									iValue( aValue ),  iIntegerSettingPageFlags( aIntegerSettingPageFlags )
	{
	AKNTASHOOK_ADD( this, "CAknIntegerSettingPage" );
	}



/** 
 *
 * The 2nd stage construction. Stored internal resource is used to perform the
 * construction.
 *
 */
EXPORT_C void CAknIntegerSettingPage::ConstructL()
	{
	BaseConstructL();
	iBackupValue = iValue;

	CEikEdwin* editor = TextControl();

	// Editor Flags are over-ridden
	editor->RemoveFlagFromUserFlags( CEikEdwin::ENoAutoSelection );

	if ( iIntegerSettingPageFlags & ENoInitialSelection  ) 
		{
		editor->AddFlagToUserFlags( CEikEdwin::ENoAutoSelection );
		editor->AddFlagToUserFlags( CEikEdwin::EJustAutoCurEnd );
		}
	if ( iIntegerSettingPageFlags & EPutCursorAtBeginning )
		{
		editor->RemoveFlagFromUserFlags( CEikEdwin::EJustAutoCurEnd );
		}
	
	IntegerEditorControl()->SetValueL( iValue );
	
	if(!IsEditable())
	    IntegerEditorControl()->SetReadOnly(ETrue);

	CheckAndSetDataValidity();
	UpdateCbaL();

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}

/**
 * Acts upon changes in the hosted control's state. 
 *
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
EXPORT_C void CAknIntegerSettingPage::HandleControlEventL(CCoeControl* /*aControl*/,
				 MCoeControlObserver::TCoeEvent aEventType)
	{
	// This event is used as it is called at least every time an edit is made to 
	// the edwin.
	if ( aEventType == EEventStateChanged )
		{
		if ( iUpdateMode == EUpdateWhenChanged)
			UpdateSettingL();

		// This updates the CBA depending on text length
		CheckAndSetDataValidity();
		UpdateCbaL();
		}
	}

/**
 *
 * This routine is called before the editor when the editor is first displayed.  This routine
 * puts in altered softkey bindings if there is zero-length text.
 *
 */
EXPORT_C void CAknIntegerSettingPage::DynamicInitL()
	{
	UpdateCbaL();
	}
/**
 *
 * This routine may be called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CAknIntegerSettingPage::UpdateSettingL()
	{
//  Status currently thrown away to prevent warning
	IntegerEditorControl()->GetTextAsInteger( iValue );

	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}



/** 
 * 
 * If the setting page is cancelled, this is called to restore the backed up copy of the 
 * input text
 *
 */
EXPORT_C void CAknIntegerSettingPage::RestoreOriginalSettingL()
	{
	iValue = iBackupValue;
	}

/** 
 *
 * Type-specific access to the text editor control
 *
 */
EXPORT_C CAknIntegerEdwin* CAknIntegerSettingPage::IntegerEditorControl()
	{
	return STATIC_CAST( CAknIntegerEdwin*, EditorControl());
	}

EXPORT_C void CAknIntegerSettingPage::UpdateCbaL()
	{
	CAknSettingPage::UpdateCbaL();

	}

EXPORT_C void CAknIntegerSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation
	
    TRect rect( SettingItemContentRect( EFalse ) );
    
    iEdwinLayoutRect.LayoutRect(
        rect,
        AknLayoutScalable_Avkon::setting_code_pane_copy1() );
    TRect edwinRect( iEdwinLayoutRect.Rect() );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        edwinRect,
        AknLayoutScalable_Avkon::input_focus_pane_cp2_copy1() );
    TRect edwinFrameRect( layoutRect.Rect() );

    layoutRect.LayoutRect(
        edwinRect,
        AknLayoutScalable_Avkon::indicator_popup_pane_cp6() );
    TRect indicatorRect( layoutRect.Rect() );
    
    AknLayoutUtils::LayoutEdwin(
            IntegerEditorControl(),
            edwinRect, 
            AknLayoutScalable_Avkon::setting_code_pane_t1_copy1().LayoutLine(),
            EAknsCIQsnTextColorsCG26,
            0,
            ETrue );

    layoutRect.LayoutRect( edwinFrameRect,
                           AknLayoutScalable_Avkon::set_opt_bg_pane_g1() );
    SetEditedItemFrameRects( edwinFrameRect, layoutRect.Rect() );
    
    SetEditorIndicatorRect( indicatorRect );
	}


EXPORT_C void CAknIntegerSettingPage::CheckAndSetDataValidity()
	{
	TInt anInt;
	CAknIntegerEdwin::TValidationStatus intStatus = IntegerEditorControl()->GetTextAsInteger( anInt );
	SetDataValidity( intStatus == CAknIntegerEdwin::EValueValid );

	// Check other flags if not valid
	if ( !DataValidity() )
		{
		if ( iIntegerSettingPageFlags & EEmptyValueAllowed )
			SetDataValidity( (intStatus == CAknIntegerEdwin::EEmpty) );
		}
	// check next flag if data still not valid
	if ( !DataValidity() )
		{
		if ( iIntegerSettingPageFlags & EInvalidValueAllowed )
			SetDataValidity ( ETrue );
		}

	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknIntegerSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknIntegerSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknIntegerSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknEdwinSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknIntegerSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknIntegerSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknIntegerSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknIntegerSettingPage::CAknSettingPage_Reserved_2()
	{
	}
/**
* CAknEdwinSettingPage reserved methods
*/
EXPORT_C void CAknIntegerSettingPage::CAknEdwinSettingPage_Reserved_1()
	{
	}

// End of File
