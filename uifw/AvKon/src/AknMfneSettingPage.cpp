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
*     This set of classes implememts setting pages for time, date, and duration
*       and IP address
*
*
*/


#include "aknmfnesettingpage.h"

#include <aknlayoutscalable_avkon.cdl.h>
#include <avkon.mbg>
#include <aknconsts.h>

#include <AknTasHook.h>
#if defined( RD_SCALABLE_UI_V2)
#include "aknbutton.h"
// For MAknMfneCommandObserver
#include <aknmfnecommandobserver.h>
#endif //if defined( RD_SCALABLE_UI_V2)


//////////////////////////////////////////////////////////////////////
//
//  MFNE SETTING PAGE - virtual class
//
//////////////////////////////////////////////////////////////////////



// -----------------------------------------------------------------------------
// CAknMfneSettingPage::~CAknMfneSettingPage
// -----------------------------------------------------------------------------
//
EXPORT_C CAknMfneSettingPage::~CAknMfneSettingPage()
    {
    AKNTASHOOK_REMOVE();
    }


/**
 * Simple pass-through constructor for this interim class
 *
 */
EXPORT_C CAknMfneSettingPage::CAknMfneSettingPage( TInt aResourceId ) : CAknSettingPage( aResourceId )
    {
    AKNTASHOOK_ADD( this, "CAknMfneSettingPage" );
    }

/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CAknMfneSettingPage::CAknMfneSettingPage(  
                                const TDesC* aSettingText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId )
                                :   CAknSettingPage( 
                                    aSettingText, 
                                    aSettingNumber, 
                                    aControlType, 
                                    aEditorResourceId, 
                                    aSettingPageResourceId) 
    {
    AKNTASHOOK_ADD( this, "CAknMfneSettingPage" );
    }

EXPORT_C void CAknMfneSettingPage::SizeChanged()
    {
    StandardSettingPageLayout();  // Must be part of any re-implementation

    TRect rect( SettingItemContentRect( EFalse ) );
        
    iMfneLayoutRect.LayoutRect(
        rect,
        AknLayoutScalable_Avkon::setting_code_pane_copy1() );
    TRect editorRect( iMfneLayoutRect.Rect() );
    
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        editorRect,
        AknLayoutScalable_Avkon::indicator_popup_pane_cp6() );
    TRect indicatorRect( layoutRect.Rect() );
    
    layoutRect.LayoutRect(
        editorRect,
        AknLayoutScalable_Avkon::input_focus_pane_cp2_copy1() );
    TRect editorFrameRect( layoutRect.Rect() );

    AknLayoutUtils::LayoutMfne(
        Mfne(),
        editorRect,
        AknLayoutScalable_Avkon::setting_code_pane_t1_copy1() );

    layoutRect.LayoutRect(
        editorFrameRect,
        AknLayoutScalable_Avkon::set_opt_bg_pane_g1_copy1() );
    SetEditedItemFrameRects( editorFrameRect, layoutRect.Rect() );
    
    SetEditorIndicatorRect( indicatorRect );
    }

EXPORT_C void CAknMfneSettingPage::Draw(const TRect& aRect) const
    {
    BaseDraw( aRect );

    if ( !IsSkinsHandlingEditorFrameDrawing() )
        {
        // Legacy frame drawing
        CWindowGc& gc=SystemGc(); 
        iMfneLayoutRect.DrawRect( gc );
        iHorizontalShadow.DrawRect( gc );
        iVerticalShadow.DrawRect( gc );
        iOutlineFrame.DrawOutLineRect( gc );
        }
    }

/** 
 *
 * Type-specific access to the MFNE
 *
 */
EXPORT_C CEikMfne* CAknMfneSettingPage::Mfne() const
    {
    return STATIC_CAST( CEikMfne*, EditorControl());
    }

EXPORT_C void CAknMfneSettingPage::HandleControlEventL(CCoeControl* /*aControl*/,
                 MCoeControlObserver::TCoeEvent aEventType)
    {
    // Ordering is important here.  Need first to do the check on validity because
    // UpdateSettingL may leave if the data is invalid !
    if ( aEventType == EEventStateChanged )
        {
        // This updates the CBA depending on validity of data as reported by mfne
        CheckAndSetDataValidity();
        UpdateCbaL();

		if ( iUpdateMode == EUpdateWhenChanged )
			UpdateSettingL();
		
		}
	}
	
EXPORT_C void CAknMfneSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    if(!AknLayoutUtils::PenEnabled())
        {
        CAknSettingPage::HandlePointerEventL(aPointerEvent); 
        }
    else
        {
        CEikMfne* pMfne = Mfne();
        if ( pMfne && iMfneLayoutRect.Rect().Contains( aPointerEvent.iPosition ) )
            {
            pMfne->HandlePointerEventL(aPointerEvent);
            }
        else
            {
            CAknSettingPage::HandlePointerEventL(aPointerEvent);
            }
        }
    }	

EXPORT_C void* CAknMfneSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknMfneSettingPage::CheckAndSetDataValidity()
	{
	SetDataValidity( Mfne()->Field(Mfne()->CurrentField())->IsValid() );
	}

// -----------------------------------------------------------------------------
// CAknMfneSettingPage::ConstructL
// This second phase constructor should be called by the derived classes
// to create touch enabled edit buttons in touch enabled devices
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMfneSettingPage::ConstructL()
	{
    BaseConstructL();
#if defined( RD_SCALABLE_UI_V2)
    if ( AknLayoutUtils::PenEnabled() )
        {
        Mfne()->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
        }
    SizeChanged();
#endif //if defined( RD_SCALABLE_UI_V2)
	}

// -----------------------------------------------------------------------------
// CAknMfneSettingPage::ComponentControl
// Calls parent class' implementation and then checks if touch buttons are
// available to be accessed
// -----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknMfneSettingPage::ComponentControl(TInt aIndex) const
	{	    
    return CAknSettingPage::ComponentControl(aIndex);
    }
        

// -----------------------------------------------------------------------------
// CAknMfneSettingPage::CountComponentControls
// Calls parent class' implementation and then adds touch buttons to the count
// if they have been initialzed
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknMfneSettingPage::CountComponentControls() const
	{
	return CAknSettingPage::CountComponentControls();
	}

//////////////////////////////////////////////////////////////////////
//
//  DATE SETTING PAGE
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Destructor
 *
 */
EXPORT_C CAknDateSettingPage::~CAknDateSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}



/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDateValue		Reference to a Time value set to the initial date
 */
EXPORT_C CAknDateSettingPage::CAknDateSettingPage( TInt aResourceId, TTime& aDateValue ):
	 CAknMfneSettingPage(aResourceId),iDateValue(aDateValue)
	{
	iBackupDateValue = iDateValue;
	AKNTASHOOK_ADD( this, "CAknDateSettingPage" );
	}

/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CAknDateSettingPage::CAknDateSettingPage(	
                                const TDesC* aSettingText, 
                                TInt aSettingNumber, 
                                TInt aControlType,
                                TInt aEditorResourceId, 
                                TInt aSettingPageResourceId, 
                                TTime& aDateValue )
                                :   CAknMfneSettingPage( 
                                    aSettingText, 
                                    aSettingNumber, 
                                    aControlType, 
                                    aEditorResourceId, 
                                    aSettingPageResourceId), 
                                    iDateValue(aDateValue)
	{
	iBackupDateValue = iDateValue;
	AKNTASHOOK_ADD( this, "CAknDateSettingPage" );
	}

/**
 *
 * 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
 * required aggregate objects, and then set the Date value. 
 *
 */
EXPORT_C void CAknDateSettingPage::ConstructL()
	{
    CAknMfneSettingPage::ConstructL();

    DateEditor()->SetUpAndDownKeysConsumed(ETrue);
	DateEditor()->SetDate( iDateValue );

	DateEditor()->SetSkinTextColorL(EAknsCIQsnTextColorsCG26);

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage.
	SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}
/**
 * This framework method is called when the editor changes its value and the mode of 
 * execution of the setting page is a continuous update mode.
 *
 */
EXPORT_C void CAknDateSettingPage::UpdateSettingL()
	{
	// The following actually leaves if a field is empty or is out of range: 
	iDateValue = DateEditor()->Date();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}
/**
 * We reload the value once again, in case we were not in
 * continuous update mode. A special event is generated for the observer to say that the
 * value is accepted.
 *
 */
EXPORT_C void CAknDateSettingPage::AcceptSettingL()
	{
	DateEditor()->PrepareForFocusLossL();
	iDateValue = DateEditor()->Date();
	}
/**
 * The backup value, stored at construction time, is re-loaded into the referenced Date.
 * An event is sent to the observer saying that the event was dismissed.
 */
EXPORT_C void CAknDateSettingPage::RestoreOriginalSettingL()
	{
	iDateValue = iBackupDateValue;
	}

/**
 *
 * Type-specific access to the editor 
 *
 */
EXPORT_C CEikDateEditor* CAknDateSettingPage::DateEditor()
	{
	return STATIC_CAST( CEikDateEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknDateSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknDateSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknDateSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknMfneSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknDateSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknDateSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknDateSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknDateSettingPage::CAknSettingPage_Reserved_2()
	{
	}
//////////////////////////////////////////////////////////////////////
//
//  TIME SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Destructor
 *
 */
EXPORT_C CAknTimeSettingPage::~CAknTimeSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aTimeValue		Reference to a Time value set to the initial date
 */
EXPORT_C CAknTimeSettingPage::CAknTimeSettingPage( TInt aResourceId, TTime& aTimeValue ):
	 CAknMfneSettingPage(aResourceId),iTimeValue(aTimeValue)
	{
	iBackupTimeValue = iTimeValue;
	AKNTASHOOK_ADD( this, "CAknTimeSettingPage" );
	}
/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CAknTimeSettingPage::CAknTimeSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTime& aTimeValue )
								:	CAknMfneSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId), 
									iTimeValue(aTimeValue)
	{
	iBackupTimeValue = iTimeValue;
	AKNTASHOOK_ADD( this, "CAknTimeSettingPage" );
	}
/**
 *
 * 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
 * required aggregate objects, and then set the Time value. 
 *
 */
EXPORT_C void CAknTimeSettingPage::ConstructL()
	{
    CAknMfneSettingPage::ConstructL();

    TimeEditor()->SetUpAndDownKeysConsumed(ETrue);
	TimeEditor()->SetTime( iTimeValue );

	TimeEditor()->SetSkinTextColorL(EAknsCIQsnTextColorsCG26);

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}
/**
 * This framework method is called when the editor changes its value and the mode of 
 * execution of the setting page is a continuous update mode.
 *
 */
EXPORT_C void CAknTimeSettingPage::UpdateSettingL()
	{
	iTimeValue = TimeEditor()->Time();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}
/**
 * We reload the event once again, in case we were not in
 * continuous update mode. A special event is generated for the observer to say that the
 * value is accepted.
 *
 */
EXPORT_C void CAknTimeSettingPage::AcceptSettingL()
	{
	iTimeValue = TimeEditor()->Time();
	}
/**
 * The backup value, stored at construction time, is re-loaded into the referenced Time.
 * An event is sent to the observer saying that the event was dismissed.
 */
EXPORT_C void CAknTimeSettingPage::RestoreOriginalSettingL()
	{
	iTimeValue = iBackupTimeValue;
	}

/**
 *
 * Type-specific access to the editor 
 *
 */
EXPORT_C CEikTimeEditor* CAknTimeSettingPage::TimeEditor()
	{
	return STATIC_CAST( CEikTimeEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknTimeSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknTimeSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknTimeSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknMfneSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknTimeSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknTimeSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknTimeSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknTimeSettingPage::CAknSettingPage_Reserved_2()
	{
	}
//////////////////////////////////////////////////////////////////////
//
//  DURATION SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Destructor
 *
 */
EXPORT_C CAknDurationSettingPage::~CAknDurationSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDurationValue		Reference to a Time value set to the initial date
 */
EXPORT_C CAknDurationSettingPage::CAknDurationSettingPage( TInt aResourceId, TTimeIntervalSeconds& aDurationValue ):
	 CAknMfneSettingPage(aResourceId),iDurationValue(aDurationValue)
	{
	iBackupDurationValue = iDurationValue;
	AKNTASHOOK_ADD( this, "CAknDurationSettingPage" );
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText		Text at top of setting pane
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId		Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aDurationValue				reference to a duration
	 */

EXPORT_C CAknDurationSettingPage::CAknDurationSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTimeIntervalSeconds& aDurationValue )
								:	CAknMfneSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId), 
									iDurationValue(aDurationValue)
	{
	iBackupDurationValue = iDurationValue;
	AKNTASHOOK_ADD( this, "CAknDurationSettingPage" );
	}
/**
 *
 * 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
 * required aggregate objects, and then set the Duration value. 
 *
 */
EXPORT_C void CAknDurationSettingPage::ConstructL()
	{
	CAknMfneSettingPage::ConstructL();
	
    DurationEditor()->SetUpAndDownKeysConsumed(ETrue);
	DurationEditor()->SetDuration( iDurationValue );
	
	DurationEditor()->SetSkinTextColorL(EAknsCIQsnTextColorsCG26);

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}
/**
 * This framework method is called when the editor changes its value and the mode of 
 * execution of the setting page is a continuous update mode.
 *
 */
EXPORT_C void CAknDurationSettingPage::UpdateSettingL()
	{
	iDurationValue = DurationEditor()->Duration();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}
/**
 * We reload the event once again, in case we were not in
 * continuous update mode. A special event is generated for the observer to say that the
 * value is accepted.
 *
 */
EXPORT_C void CAknDurationSettingPage::AcceptSettingL()
	{
	DurationEditor()->PrepareForFocusLossL();
	iDurationValue = DurationEditor()->Duration();
	}
/**
 * The backup value, stored at construction time, is re-loaded into the referenced Duration.
 * An event is sent to the observer saying that the event was dismissed.
 */
EXPORT_C void CAknDurationSettingPage::RestoreOriginalSettingL()
	{
	iDurationValue = iBackupDurationValue;
	}

/**
 *
 * Type-specific access to the editor 
 *
 */
EXPORT_C CEikDurationEditor* CAknDurationSettingPage::DurationEditor()
	{
	return STATIC_CAST( CEikDurationEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknDurationSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknDurationSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknDurationSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknMfneSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknDurationSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknDurationSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknDurationSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknDurationSettingPage::CAknSettingPage_Reserved_2()
	{
	}
//////////////////////////////////////////////////////////////////////
//
//  TIME OFFSET SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Destructor
 *
 */
EXPORT_C CAknTimeOffsetSettingPage::~CAknTimeOffsetSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aDurationValue		Reference to a Time value set to the initial date
 */
EXPORT_C CAknTimeOffsetSettingPage::CAknTimeOffsetSettingPage( TInt aResourceId, TTimeIntervalSeconds& aTimeOffsetValue ):
	 CAknMfneSettingPage(aResourceId),iTimeOffsetValue(aTimeOffsetValue)
	{
	iBackupTimeOffsetValue = iTimeOffsetValue;
	AKNTASHOOK_ADD( this, "CAknTimeOffsetSettingPage" );
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText		Text at top of setting pane
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId		Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aDurationValue				reference to a duration
	 */

EXPORT_C CAknTimeOffsetSettingPage::CAknTimeOffsetSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TTimeIntervalSeconds& aTimeOffsetValue )
								:	CAknMfneSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId), 
									iTimeOffsetValue(aTimeOffsetValue)
	{
	iBackupTimeOffsetValue = iTimeOffsetValue;
	AKNTASHOOK_ADD( this, "CAknTimeOffsetSettingPage" );
	}
/**
 *
 * 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
 * required aggregate objects, and then set the TimeOffset value. 
 *
 */
EXPORT_C void CAknTimeOffsetSettingPage::ConstructL()
	{
    CAknMfneSettingPage::ConstructL();

    TimeOffsetEditor()->SetUpAndDownKeysConsumed(ETrue);
	TimeOffsetEditor()->SetTimeOffset( iTimeOffsetValue );
	
	TimeOffsetEditor()->SetSkinTextColorL(EAknsCIQsnTextColorsCG26);
	
	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}
/**
 * This framework method is called when the editor changes its value and the mode of 
 * execution of the setting page is a continuous update mode.
 *
 */
EXPORT_C void CAknTimeOffsetSettingPage::UpdateSettingL()
	{
	iTimeOffsetValue = TimeOffsetEditor()->TimeOffset();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}
/**
 * We reload the event once again, in case we were not in
 * continuous update mode. A special event is generated for the observer to say that the
 * value is accepted.
 *
 */
EXPORT_C void CAknTimeOffsetSettingPage::AcceptSettingL()
	{
	TimeOffsetEditor()->PrepareForFocusLossL();
	iTimeOffsetValue = TimeOffsetEditor()->TimeOffset();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingOked);	
	}
/**
 * The backup value, stored at construction time, is re-loaded into the referenced TimeOffset.
 * An event is sent to the observer saying that the event was dismissed.
 */
EXPORT_C void CAknTimeOffsetSettingPage::RestoreOriginalSettingL()
	{
	iTimeOffsetValue = iBackupTimeOffsetValue;
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingCancelled);	
	}

/**
 *
 * Type-specific access to the editor 
 *
 */
EXPORT_C CEikTimeOffsetEditor* CAknTimeOffsetSettingPage::TimeOffsetEditor()
	{
	return STATIC_CAST( CEikTimeOffsetEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknTimeOffsetSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknTimeOffsetSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknTimeOffsetSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknMfneSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknTimeOffsetSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknTimeOffsetSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknTimeOffsetSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknTimeOffsetSettingPage::CAknSettingPage_Reserved_2()
	{
	}
//////////////////////////////////////////////////////////////////////
//
//  IP ADDRESS FIELD SETTING PAGE
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Destructor
 *
 */
EXPORT_C CAknIpFieldSettingPage::~CAknIpFieldSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

/**
 * Constructor using Setting page resource
 *
 *
 * @param	aResourceId		Setting page resource Id
 * @param	aIpFieldValue		Reference to a Time value set to the initial date
 */
EXPORT_C CAknIpFieldSettingPage::CAknIpFieldSettingPage( TInt aResourceId, TInetAddr& aIpAddress ):
	 CAknMfneSettingPage(aResourceId),iIpAddress(aIpAddress)
	{
	iBackupIpAddress = iIpAddress;
	AKNTASHOOK_ADD( this, "CAknIpFieldSettingPage" );
	}
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				 = 0				Default Avkon SP resource if used + this editor resource
	 *			 = 0				 = 0				uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, IpField )
	 *
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText	Text at top of setting pane
	 *	@param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aIpAddress				reference to a IP address
	 */

EXPORT_C CAknIpFieldSettingPage::CAknIpFieldSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TInetAddr& aIpAddress )
								:	CAknMfneSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId), 
									iIpAddress(aIpAddress)
	{
	iBackupIpAddress = iIpAddress;
	AKNTASHOOK_ADD( this, "CAknIpFieldSettingPage" );
	}
/**
 *
 * 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
 * required aggregate objects, and then set the IpField value. 
 *
 */
EXPORT_C void CAknIpFieldSettingPage::ConstructL()
	{
    CAknMfneSettingPage::ConstructL();
    IpFieldEditor()->SetUpAndDownKeysConsumed(ETrue);
	IpFieldEditor()->SetAddress( iIpAddress );
	
	IpFieldEditor()->SetSkinTextColorL(EAknsCIQsnTextColorsCG26);

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrInput, KAknsIIDQsnFrInputCenter );
	}
/**
 * This framework method is called when the editor changes its value and the mode of 
 * execution of the setting page is a continuous update mode.
 *
 */
EXPORT_C void CAknIpFieldSettingPage::UpdateSettingL()
	{
	iIpAddress = IpFieldEditor()->Address();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}
/**
 * We reload the event once again, in case we were not in
 * continuous update mode. A special event is generated for the observer to say that the
 * value is accepted.
 *
 */
EXPORT_C void CAknIpFieldSettingPage::AcceptSettingL()
	{
	IpFieldEditor()->PrepareForFocusLossL();
	iIpAddress = IpFieldEditor()->Address();
	}
/**
 * The backup value, stored at construction time, is re-loaded into the referenced IpField.
 * An event is sent to the observer saying that the event was dismissed.
 */
EXPORT_C void CAknIpFieldSettingPage::RestoreOriginalSettingL()
	{
	iIpAddress = iBackupIpAddress;
	}

/**
 *
 * Type-specific access to the editor 
 *
 */
EXPORT_C CAknIpFieldEditor* CAknIpFieldSettingPage::IpFieldEditor()
	{
	return STATIC_CAST( CAknIpFieldEditor*, EditorControl());
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknIpFieldSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknIpFieldSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknIpFieldSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknMfneSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknIpFieldSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknIpFieldSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknIpFieldSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknIpFieldSettingPage::CAknSettingPage_Reserved_2()
	{
	}
// End of File
