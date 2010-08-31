/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Base class for Setting Item Editing
*
*/


#include "aknsettingpage.h"

#include <akninputblock.h>
//For TResourceReader
#include <barsread.h>

//For the CEikLabels
#include <eiklabel.h>

// For the hint text support in the navi pane
#include <aknnavide.h>
#include <aknappui.h>

#include <eikmop.h>

// Skins support
#include <aknconsts.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>

#include <AknTasHook.h>
// Skin layout macros
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
//For MCoeCaptionRetrieverForFep
#include <fepbase.h>
#include <AknPopupFader.h>
#include "aknitemactionmenuregister.h"
#include "aknqueryeditorindicator.h"

// This determines the maximum number of digits in the optional number displayed on the
// top left of the setting page
const TInt KAknSettingPageMaxOrdinalDigits = 3;

// For formatting numbers; maximum is taken care of by an assert in the source
_LIT( KAknSettingPageNumberFormat, "%d" );

/**
 * Local Panic Function and Panic Codes 
 */

enum TAknSettingPagePanicCodes
	{
	EAknPanicSettingPageGeneralPanic,
	EAknPanicSettingPageNoMenuBar,
	EAknPanicSettingPageNoMenuBarResource,
	EAknPanicSettingPageDeprecated,
	EAknPanicSettingPageIllegalSettingNumber, 
	EAknPanicSettingPageIllegalLayout
	};

GLDEF_C void Panic(TAknSettingPagePanicCodes aPanic)
	{
	_LIT(KPanicCat,"AknSettingPage");
	User::Panic(KPanicCat, aPanic);
	}

// ---------------------------------------------------------------------------
// Calculates and returns control rectangle i.e. whole popup rect common to 
// all setting pages.
// ---------------------------------------------------------------------------
//
static TRect ControlRect( TBool aEmbeddedSoftkeys )
    {
    TRect container;
    
    if ( aEmbeddedSoftkeys )
        {
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                container );
        
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( container, 
                AknLayoutScalable_Avkon::popup_settings_window( 0 ) );
        
        TRect finalRect( AknPopupUtils::Position( layoutRect.Rect().Size(), 
                ETrue ), layoutRect.Rect().Size() );
        
        return finalRect;
        }

    AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, container);

    return container;
    }


// ---------------------------------------------------------------------------
// Calculates and returns container rectangle common to all setting pages.
// This container holds all setting view items excluding caption and softkeys.
// ---------------------------------------------------------------------------
//
static TRect ContainerRect( TBool aEmbeddedSoftkeys )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( TRect( ControlRect( aEmbeddedSoftkeys ) ).Size(), 
            AknLayoutScalable_Avkon::settings_container_pane( 0 ) );
    
    return layoutRect.Rect();
    }


NONSHARABLE_CLASS(CAknSettingPageExtension): public CBase, public MCoeCaptionRetrieverForFep
    , public MCoeControlBackground, public MAknFadedComponent
    {
    public:
        static CAknSettingPageExtension* NewL( CAknSettingPage* parent );
	    ~CAknSettingPageExtension();

	    /**
	     * Sets the skin item ID for the frame graphics that is drawn
	     * around the setting item.
	     *
	     * @param  aFrameIID        Skin item ID of the frame graphics.
	     * @param  aFrameCenterIID  Skin item ID of the center piece of the frame
	     *                          graphics.
	     */
	    void SetEditedItemFrameIID( const TAknsItemID& aFrameIID,
	                                const TAknsItemID& aFrameCenterIID );

	    /**
	     * Sets the outer and inner rectangle for the frame graphics that is drawn
	     * around the setting item.
	     *
	     * @param  aOuterRect  Frame outer rectangle.
	     * @param  aInnerRect  Frame inner rectangle.
	     */
	    void SetEditedItemFrameRects( const TRect& aOuterRect,
	                                  const TRect& aInnerRect );
	    
	    /**
	     * Creates if necessary and returns the editor indicator
	     * container control.
	     * 
	     * @return Editor indicator container control.
	     */
	    CAknQueryEditIndicator* EditorIndicatorContainer();

        /**
         * Creates background skin context.
         */
        void CreateBackgroundContextL();

    public: // From base class MCoeControlBackground

	    /**
	     * Draws the background for the setting page and
		 * the editor control (aControl).
	     *
	     * @param  aGc       Graphics context used for drawing.
	     * @param  aControl  The control being drawn.
	     * @param  aRect     The area to be redrawn.
	     */
	    void Draw( CWindowGc& aGc,
	               const CCoeControl& aControl,
	               const TRect& aRect ) const;

    public: // From base class MAknFadedComponent
        
        /**
         * Returns the number of faded components.
         * 
         * @return Number of faded components.
         */
        TInt CountFadedComponents();
        
        /**
         * Returns faded component.
         * 
         * @param   aIndex Component index.
         * @return  Faded component.
         */
        CCoeControl* FadedComponent( TInt aIndex );
	    
    private:
        CAknSettingPageExtension();
	    void ConstructL( CAknSettingPage* aParent );
       /**
       * from MCoeCaptionRetrieverForFep
       * fill aCaption with the target control's caption 
       */
  	   IMPORT_C virtual void GetCaptionForFep(TDes& aCaption) const;

    public: // data
        TBool iDrawBackground;   // Determines if background should be drawn (transparency)
        TBool iIsStopActiveSchedulerCalled; // Determins if the CAknSettingPage::StopActiveScheduler function called 
        CEikScrollBarFrame* iSBFrame;

        /**
         * Control context for the setting page background graphics.
         * Not own.
         */
        CAknsBasicBackgroundControlContext* iSettingPageBgContext;
        
        /**
         * Control context for the setting page bitmap background graphics.
         * Own.
         */
        CAknsBasicBackgroundControlContext* iBasicBgContext;

        /**
         * Control context for the setting page frame background graphics.
         * Own.
         */
        CAknsFrameBackgroundControlContext* iFrameBgContext;

        CEikLabel* iShadowText;
        CFbsBitmap* iLockIcon;
        CFbsBitmap* iLockIconMask;
        TRect iLockIconRect;
        CAknSettingPage* iParent;

        /**
	     * Control context for providing the skinning for the hosted editor
	     * and it's surrounding area.
	     * Own.
	     */
	    CAknsFrameBackgroundControlContext* iEditedItemControlContext;

	    /**
	     * Popup fader.
	     */
        TAknPopupFader iFader;
        
        /**
         * Editing state indicator container for the editor setting pages.
         * Own.
         */
        CAknQueryEditIndicator* iEditIndicator;
        
        /**
         * Whether softkeys are embedded or not.
         */
        TBool iEmbeddedSoftkeys;
    };


void CAknSettingPage::GetCaptionForFep(TDes& aCaption) const
    {
    if (iSettingText==NULL)
        {
        aCaption=KNullDesC;
        }
    else
        {
        const TInt maximumLength=aCaption.MaxLength();
        if (iSettingText->Length()>maximumLength)
            {
            aCaption=iSettingText->Left(maximumLength);
            }
        else
            {
            aCaption=*iSettingText;
            }
        }    
    }


CAknSettingPageExtension* CAknSettingPageExtension::NewL(CAknSettingPage* aParent )
    {
    CAknSettingPageExtension* self = new (ELeave) CAknSettingPageExtension;
    CleanupStack::PushL(self);
    self->ConstructL( aParent );
	CleanupStack::Pop(self);
	return self;
    }

CAknSettingPageExtension::~CAknSettingPageExtension()
    {
    delete iSBFrame;
    delete iSettingPageBgContext;
    delete iShadowText;
    delete iLockIcon;
    delete iLockIconMask;
    delete iEditedItemControlContext;
    delete iEditIndicator;
    }


// ----------------------------------------------------------------------------
// Sets the skin item IDs for the frame graphics drawn around the setting item.
// ----------------------------------------------------------------------------
//
void CAknSettingPageExtension::SetEditedItemFrameIID(
        const TAknsItemID& aFrameIID,
        const TAknsItemID& aFrameCenterIID )
    {
    iEditedItemControlContext->SetFrame( aFrameIID );
    iEditedItemControlContext->SetCenter( aFrameCenterIID );
    }


// ----------------------------------------------------------------------------
// Sets the frame rectangles of the setting item frame.
// ----------------------------------------------------------------------------
//
void CAknSettingPageExtension::SetEditedItemFrameRects(
        const TRect& aOuterRect,
        const TRect& aInnerRect )
    {
    iEditedItemControlContext->SetFrameRects( aOuterRect, aInnerRect );
    }


// ----------------------------------------------------------------------------
// Creates if necessary and returns the editor indicator container control.
// ----------------------------------------------------------------------------
//
CAknQueryEditIndicator* CAknSettingPageExtension::EditorIndicatorContainer()
    {
    if ( !iEditIndicator )
        {
        TRAPD( err, iEditIndicator = CAknQueryEditIndicator::NewL( iParent ) );
        if ( !err )
            {
            iEditIndicator->SetBackground( this );
            }
        }
    
    return iEditIndicator;
    }


// ----------------------------------------------------------------------------
// Creates background skin context.
// ----------------------------------------------------------------------------
//
void CAknSettingPageExtension::CreateBackgroundContextL()
    {
    TRect nullRect( 0, 0, 0, 0 );

    if ( iEmbeddedSoftkeys )
        {
        iFrameBgContext =
        CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopup,
                                                  nullRect,
                                                  nullRect,
                                                  EFalse );
        iSettingPageBgContext = iFrameBgContext;
        }
    else
        {
        iBasicBgContext = 
        CAknsBasicBackgroundControlContext::NewL( 
                KAknsIIDQsnBgAreaMainListSet, 
                nullRect,
                EFalse );
        iSettingPageBgContext = iBasicBgContext;
        }
    }


// ----------------------------------------------------------------------------
// Draws the background for the setting page and the setting page item.
// ----------------------------------------------------------------------------
//
void CAknSettingPageExtension::Draw( CWindowGc& aGc,
                                     const CCoeControl& aControl,
                                     const TRect& aRect ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    if ( !iParent->IsBackgroundDrawingEnabled() )
        {
        return;
        }
    
    if ( &aControl == iParent )
        {
        AknsDrawUtils::Background( skin,
                                   iSettingPageBgContext,
                                   aGc,
                                   aRect );

        AknsDrawUtils::Background( skin,
                                   iEditedItemControlContext,
                                   aGc,
                                   aRect );
        }
    else if ( &aControl == iSBFrame->VerticalScrollBar() )
        {
        AknsDrawUtils::Background( skin,
                                   iSettingPageBgContext,
                                   aGc,
                                   aRect );
        }
    else if ( &aControl == iParent->EditorControl() )
        {
        aGc.SetBrushColor( TRgb( ~0 ) );
        
        AknsDrawUtils::Background( skin,
                                   iSettingPageBgContext,
                                   aGc,
                                   aRect );

        AknsDrawUtils::Background( skin,
                                   iEditedItemControlContext,
                                   aGc,
                                   aRect );
        }
    else if ( &aControl == iEditIndicator )
        {
        AknsDrawUtils::Background( skin,
                                   iSettingPageBgContext,
                                   aGc,
                                   aRect );
        }
    }


// ----------------------------------------------------------------------------
// Counts faded components.
// ----------------------------------------------------------------------------
//
TInt CAknSettingPageExtension::CountFadedComponents()
    {
    TInt count = 1; // this
    
    CCoeControl* buttonGroupControl = NULL;
    
    if ( iParent->Cba() )
        {
        MEikButtonGroup* buttonGroup = iParent->Cba()->ButtonGroup();
        
        if ( buttonGroup )
            {
            buttonGroupControl = buttonGroup->AsControl();
            
            if ( buttonGroupControl )
                {
                ++count;
                }
            }
        }
    
    return count;
    }


// ----------------------------------------------------------------------------
// Returns faded components.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknSettingPageExtension::FadedComponent( TInt aIndex )
    {
    switch ( aIndex )
        {
        case 0:
            return iParent;
            
        case 1:
            {
            CCoeControl* cba = NULL;
            
            if ( iParent->Cba() )
                {
                MEikButtonGroup* buttonGroup = iParent->Cba()->ButtonGroup();
                
                if ( buttonGroup )
                    {
                    cba = buttonGroup->AsControl();
                    }
                }

            return cba;
            }
            
        default:
            return NULL;
        }
    }


CAknSettingPageExtension::CAknSettingPageExtension()
    {
    iEmbeddedSoftkeys = ETrue;
    }

void CAknSettingPageExtension::ConstructL( CAknSettingPage* aParent )
    {
    iParent = aParent;
    iDrawBackground = ETrue;
    iIsStopActiveSchedulerCalled = EFalse;

    TRect nullRect( 0, 0, 0, 0 );

    iEditedItemControlContext =
        CAknsFrameBackgroundControlContext::NewL( KAknsIIDDefault,
                                                  nullRect,
                                                  nullRect,
                                                  EFalse );
    }

/**
* GetCaptionForFep.  Overrides MCoeCaptionRetrieverForFep::GetCaptionForFep
*
*/
EXPORT_C void CAknSettingPageExtension::GetCaptionForFep(TDes& aCaption) const
    {
    iParent->GetCaptionForFep(aCaption);
    }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * Constructor
 *
 * @param	aResourceId Setting Page resource ID
 */
EXPORT_C CAknSettingPage::CAknSettingPage( TInt aResourceId )
								:	iResourceId( aResourceId ), iIsProtected(0)
	{
	ResetFlags();
	iSettingNumber = EAknSettingPageNoOrdinalDisplayed;
	AKNTASHOOK_ADD( this, "CAknSettingPage" );
	}


EXPORT_C CAknSettingPage::CAknSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId )
								:	iSettingTextFromConstructor ( aSettingText ),
									iResourceId( aSettingPageResourceId ),
									iSettingNumber (aSettingNumber),
									iControlType (aControlType),
									iEditorResourceId (aEditorResourceId)
	{
	ResetFlags();
	AKNTASHOOK_ADD( this, "CAknSettingPage" );
	}

EXPORT_C void CAknSettingPage::ResetFlags()
	{
	iUpdateMode = EUpdateWhenAccepted;
	iSettingId = KAknSettingPageNoIdSet;
	SetDataValidity( ETrue );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknSettingPage::~CAknSettingPage()
	{
	AKNTASHOOK_REMOVE();
	iEikonEnv->EikAppUi()->RemoveFromStack(this);

    AknItemActionMenuRegister::SetOverridingMenuBarOwnerL( NULL );
    
	if (iMenuBar)
		{
		iEikonEnv->EikAppUi()->RemoveFromStack(iMenuBar);
		delete iMenuBar;
		}

	delete iNumberLabel;
	delete iTextLabel;
	delete iEditorControl;
	delete iSettingText;
	delete iHintText;
	delete iCba;
	delete iExtension;

    // If navi pane context is not poped out yet, pop it now.
	PopNaviDecoratorIfRequired();
	delete iNaviDecorator;

	StopActiveScheduler();
	}

void CAknSettingPage::StopActiveScheduler()
	{
    SetStopActiveSchedulerFlag( ETrue );
	CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
	}

void CAknSettingPage::StartActiveScheduler()
	{
	if (!iWait.IsStarted())
		{
		iWait.Start();
		}
	}
/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/ ) const
	{}
#else
EXPORT_C void CAknSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CCoeControl::WriteInternalStateL(aWriteStream);
	}
#endif

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknSettingPage::Reserved_2()
	{
	}

/**
* New reserved methods 
*/ 
EXPORT_C void CAknSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknSettingPage::CAknSettingPage_Reserved_2()
	{
	}

/**
 * public method for construction.	Only thing required to do in this class is to call the 
 * BaseConstructL(). Derived classes may be required to do more
 *
 */
EXPORT_C void  CAknSettingPage::ConstructL()
	{
	BaseConstructL();
	}

/**
 * Protected non-virtual base method for construction.	Only thing required to do in this class is 
 * call the ConstructFromResourceL routine and set the flag that says construction has occured
 *
 */
EXPORT_C void  CAknSettingPage::BaseConstructL()
	{
    if( iFlags.IsSet( EIsBaseConstructedIndex ) )
        {
        return;
        }

    if ( !iExtension )
        {
        iExtension = CAknSettingPageExtension::NewL( this );
        }

	// Setting pages have a default object provider parent set in the eikappui.
    SetMopParent(iEikonEnv->EikAppUi());
	ConstructFromResourceL( SettingPageResourceId() );
	iFlags.Set( EIsBaseConstructedIndex );
	}

/** 
*
* This routes the keys to the editor. 
* However, if the menu is showing, then events have to be forwarded manually to it. 
*
*/
EXPORT_C TKeyResponse CAknSettingPage::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType) 
	{
    if( IsStopActiveSchudlerCalled() )
        {
        switch( aKeyEvent.iCode )
            {
        case EKeyOK:
        case EKeyEnter:
        case EKeyEscape:
             return EKeyWasConsumed;
        default:
            break;
            }
        return EKeyWasNotConsumed;
        }

	// Always react to Escape key by cancelling the setting page
	if ( aType == EEventKey && aKeyEvent.iCode == EKeyEscape)
		{
		ProcessCommandL( EAknSoftkeyCancel );
        //Remove self from stack to make CAknShutter continue shutdown.
        iEikonEnv->EikAppUi()->RemoveFromStack(this);
		return EKeyWasConsumed;
		}
		
	if(!IsEditable())
	    {
	    return EKeyWasConsumed;
	    }

	// Only handle other key events if we're focused

	if (IsFocused())
		{
		if (iEditorControl)
			{
			// Abstraction of key events: Escape is handled like Cancel 
			// OK is handled like select.
			if ( aType == EEventKey )
				{

				switch ( aKeyEvent.iCode )
					{	

					// OK key is handled like the Select softkey by default
					// Note that in listbox editor types the OK key must be sent to the listbox
					// so that may have to be synthesized 
                    case EKeyEnter:
					case EKeyOK :
					    if (aKeyEvent.iRepeats != 0) return EKeyWasConsumed;
						if ( DataValidity() )
							ProcessCommandL( EAknSoftkeySelect );
						return EKeyWasConsumed;


					default :
						break ;
					}
				}	
		
			iEditorControl->OfferKeyEventL( aKeyEvent, aType );
			}

        return (aKeyEvent.iScanCode == EStdKeyYes ? EKeyWasNotConsumed : EKeyWasConsumed);
		}

	return EKeyWasNotConsumed;	// Keys can fall through to menus

	}

/** 
* This constructs the control based upon the id passed
*
*/
EXPORT_C void CAknSettingPage::ConstructFromResourceL( TInt aResourceId )
	{
	if (!aResourceId )
		aResourceId = R_AVKON_DEFAULT_SETTING_PAGE;
	TResourceReader reader;
	iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
	ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy(); //reader 
	}

/** 
* Used by ConstructFromResource()
* This routine does all the work. 
*
*/
EXPORT_C void CAknSettingPage::ConstructFromResourceL(TResourceReader &aRes)
	{
	CreateWindowL();

	SetGloballyCapturing( ETrue );
    SetPointerCapture(ETrue);

    if( NULL == iExtension )
        {
        iExtension = CAknSettingPageExtension::NewL( this );
        }

	// Ensure that any value set from constructors turns on the numbering
	if (iSettingNumber != EAknSettingPageNoOrdinalDisplayed )
		{
		SetNumbered( ETrue );
		}

// Read in the number from resource
	TInt number = aRes.ReadInt16();

	if ( number != EAknSettingPageNoOrdinalDisplayed )
		{
		iSettingNumber = number;
		SetNumbered( ETrue );	
		}

//
// Handle the setting text ( i.e. the title at the top of the setting page )
//
	TPtrC settingText = aRes.ReadTPtrC();

//
// Resource text overrides text set via constructor. However, if the text was 
// set via the method SetSettingTextL then we use text given by that API
// 
//
	if ( settingText.Length() > 0  && ( !iSettingText ) )
		{
		SetSettingTextL( settingText );
		}

// if there is no iSettingText by this point, use the value given at construction:
	if (!iSettingText )
// But the value passed at constuction is a pointer and must be tested too:
		if ( iSettingTextFromConstructor )
			SetSettingTextL( *iSettingTextFromConstructor );
		else
			SetSettingTextL( KNullDesC ); // empty (zero-length) descriptor.

	TPtrC hintText = aRes.ReadTPtrC();
	if ( hintText.Length() > 0 )
		{
		delete iHintText;
		iHintText = 0;
		iHintText = hintText.AllocL();
		}

// Both CBa and Menu have defaults set here, not in .rh file for dependcy reasons
	iCbaResourceId = aRes.ReadInt32();
	if ( !iCbaResourceId )
		iCbaResourceId = R_AVKON_SOFTKEYS_OK_CANCEL__OK;

	iMenuBarId = aRes.ReadInt32();
	if ( !iMenuBarId )
		iMenuBarId = R_AVKON_MENUPANE_EMPTY;

	// The following are put in temporary variables because pre-existing EditorResourceId will over-ride
	// that in the resource link
	TInt controlType = aRes.ReadInt16();
	TInt editorResourceId = aRes.ReadInt32();

	// Use the resource if it is not the case that both are present from construction
	if (!( iEditorResourceId && iControlType ) )
		{
		iEditorResourceId = editorResourceId;
		iControlType = controlType;
		}

	// Possible user-defined softkey bindings for invalid data
	iInvalidDataCbaResourceId = aRes.ReadInt32();
	// If it is not defined by the user (.rh default is 0), then 
	// it is set the specified default value if the valid cba resource is also 
	// the default.  Otherwise, it is set to be equal to the valid cba resource
	if ( !iInvalidDataCbaResourceId )
		if ( iCbaResourceId == R_AVKON_SOFTKEYS_OK_CANCEL__SELECT ||
            iCbaResourceId == R_AVKON_SOFTKEYS_OK_CANCEL ||
            iCbaResourceId == R_AVKON_SOFTKEYS_OK_CANCEL__OK)
			iInvalidDataCbaResourceId = R_AVKON_SOFTKEYS_CANCEL;
		else
			iInvalidDataCbaResourceId = iCbaResourceId;

	iExtensionId = aRes.ReadInt32();

	// Resource all read now

	// Construct menubar and cba before constructed-from resource objects might need them

	// Create a CBA for use with the setting page
	const TSize screenSize=TSize(AKN_LAYOUT_WINDOW_screen.iW, AKN_LAYOUT_WINDOW_screen.iH);
	
	TInt resourceId = 0;
	if(IsEditable())
	    resourceId = iCbaResourceId;
	else
	    resourceId = iInvalidDataCbaResourceId;
    
	if ( iExtensionId )
	    {
	    TResourceReader reader;
	    iCoeEnv->CreateResourceReaderLC( reader, iExtensionId );	    
	    TInt flags = reader.ReadInt32();
	    CleanupStack::PopAndDestroy(); // reader

	    if ( flags & KAknSettingPageNoEmbeddedSoftKeys )
	        {
	        iExtension->iEmbeddedSoftkeys = EFalse;
	        }
	    }
	
    AknItemActionMenuRegister::SetOverridingMenuBarOwnerL( this );

	if ( !iExtension->iEmbeddedSoftkeys )
	    {
	    iCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba,
	        CEikButtonGroupContainer::EHorizontal, this, resourceId, *this);
	    iCba->SetBoundingRect(TRect(screenSize));
	    }
	else
	    {
        iCba = CEikButtonGroupContainer::NewL( CEikButtonGroupContainer::ECba,
            CEikButtonGroupContainer::EHorizontal, 
            this, resourceId, *this, CEikButtonGroupContainer::EIsEmbedded | 
            CEikButtonGroupContainer::EAddToStack );
	    }
	
	iExtension->CreateBackgroundContextL();

    if ( iExtension->iEmbeddedSoftkeys && 
            CAknEnv::Static()->TransparencyEnabled() )
        {
        EnableWindowTransparency();
        }

	// Make the menu bar
	iMenuBar = new (ELeave) CEikMenuBar() ;
	iMenuBar->ConstructL( this, NULL, iMenuBarId ) ;
	iEikonEnv->EikAppUi()->AddToStackL(iMenuBar,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus);
	

	iTextLabel = new(ELeave) CEikLabel( );
    iTextLabel->UseLogicalToVisualConversion(ETrue);
	iTextLabel->SetContainerWindowL(*this);
    
    iExtension->iShadowText = new(ELeave) CEikLabel( );
    iExtension->iShadowText->UseLogicalToVisualConversion(ETrue);
	iExtension->iShadowText->SetContainerWindowL(*this);
        
	// IsNumbered() should give the current answer now whether to have a number of not
	if ( IsNumbered() && ( iSettingNumber != EAknSettingPageNoOrdinalDisplayed ) )		
		{
		iNumberLabel = new(ELeave) CEikLabel( );
		TBuf<KAknSettingPageMaxOrdinalDigits> text;
		__ASSERT_DEBUG( (iSettingNumber < 1000), Panic(EAknPanicSettingPageIllegalSettingNumber ) );
		__ASSERT_DEBUG( (iSettingNumber > -100), Panic(EAknPanicSettingPageIllegalSettingNumber ) );
		text.Format( KAknSettingPageNumberFormat,iSettingNumber );
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion(text);
		iNumberLabel->SetTextL( text );
		iNumberLabel->SetContainerWindowL(*this);
		}
	
	// Create scrollbar here before making sizechanged
	delete iExtension->iSBFrame;
    iExtension->iSBFrame=NULL;
    iExtension->iSBFrame=new(ELeave) CEikScrollBarFrame(this, NULL, ETrue);        
	
    iExtension->iSBFrame->CreateDoubleSpanScrollBarsL(EFalse, EFalse, ETrue, EFalse); // non-window owning scrollbar (1st param)
    iExtension->iSBFrame->SetTypeOfVScrollBar(CEikScrollBarFrame::EDoubleSpan);
    iExtension->iSBFrame->DrawBackground( EFalse, EFalse );
    iExtension->iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff,
                                                   CEikScrollBarFrame::EOff );
    
    iExtension->iSBFrame->VerticalScrollBar()->SetContainerWindowL(*this);
    iExtension->iSBFrame->VerticalScrollBar()->SetMopParent(this);
    iExtension->iSBFrame->VerticalScrollBar()->CopyControlContextFrom(this);//iSkinsInfo->BackgroundAndFrameControl()
    iExtension->iSBFrame->VerticalScrollBar()->SetBackground( iExtension );

	SEikControlInfo controlInfo=EikControlFactory::CreateByTypeL(iControlType);

	iEditorControl=controlInfo.iControl;
	iEditorControl->SetContainerWindowL(*this);
	iEditorControl->SetBackground( iExtension );
	SetBackground( iExtension );
		
// Construct contained control from given resource Id 

		{
		TResourceReader editorReader;
		iCoeEnv->CreateResourceReaderLC(editorReader,iEditorResourceId);
		iEditorControl->ConstructFromResourceL( editorReader );
		CleanupStack::PopAndDestroy(); //editorReader	
		} // editorReader out of scope

	// Position of the entire setting page - the mainpane
	TRect containerRect( ControlRect( iExtension->iEmbeddedSoftkeys ) );
		
	// Create lock icon
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	
	AknsUtils::CreateColorIconL(skin, KAknsIIDQgnIndiSettProtectedAdd, 
        KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG16, iExtension->iLockIcon, 
        iExtension->iLockIconMask, KAvkonBitmapFile, EMbmAvkonQgn_indi_sett_protected_add, 
        EMbmAvkonQgn_indi_sett_protected_add_mask, KRgbBlack);
    
	
	// Root the layout chain of calls: This will cause SizeChanged to be called
	// SizeChanged in turn will layout skin information as well as contained controls
	SetRect(containerRect);

	if ( iSettingText )
		{        
		iTextLabel->SetTextL(*iSettingText);
		iTextLabel->CropText();
		if(iExtension->iShadowText)
		    {
		    iExtension->iShadowText->SetTextL(*iSettingText);
		    iExtension->iShadowText->CropText();
		    }
		}
	}

/**
*
* Method to get the editor resource via the setting page resource. Done as a static 
* method in this class.
*
*/
EXPORT_C void CAknSettingPage::GetEditorResourceInfoL( 
		TInt aSettingPageResourceId, 
		TInt& aControlType, 
		TInt& aEditorResourceId )
	{

	aEditorResourceId = 0;
	aControlType = -1;	

	TResourceReader reader;
	// Static method; cannot use iCoeEnv:
	CEikonEnv::Static()->CreateResourceReaderLC(reader,aSettingPageResourceId);  // reader on C-stack

// Only the editor resource items (type nad resource link) are needed; others are discarded
	reader.ReadInt16(); // number
	reader.ReadTPtrC(); // setting text
	reader.ReadTPtrC(); // hint text
	reader.ReadInt32(); // CBA resource id
	reader.ReadInt32(); // Menubar

	aControlType = reader.ReadInt16();
	aEditorResourceId = reader.ReadInt32();
	
	CleanupStack::PopAndDestroy(); //reader 
	}
/**
* This routine is called as part of the set-up of the control.	It is the place to put
* layout code. 
*
*/
EXPORT_C void CAknSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation
    AknLayoutUtils::LayoutControl(
        iEditorControl,
        SettingItemContentRect( ETrue ),
        AknLayoutScalable_Avkon::setting_text_pane_copy1( 0 ) );
	}

/**
* This routine is the base layout for CAknSettingPage. It lays out the labels and configures
* the drawing in general
*
*/
EXPORT_C void CAknSettingPage::StandardSettingPageLayout()
	{
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color, 
		KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG10 );
    
	TRect rect = Rect();
	
    if ( iCba && iExtension->iEmbeddedSoftkeys )
        {
        CEikCba* cba = static_cast<CEikCba*>( iCba->ButtonGroup() );
        
        if ( cba )
            {
            TAknLayoutRect cbaLayout;
            cbaLayout.LayoutRect( rect, 
                    AknLayoutScalable_Avkon::popup_sk_window( 0 ) );
            
            // CBA's layout data contains also distance from left and right
            // borders so we can take only its height - otherwise
            // horizontal position would be wrong in landscape.
            TRect cbaRect(  cbaLayout.Rect().Size() );
            cbaRect.Move( 0, iSize.iHeight - cbaRect.Height() );
            
            cba->SetRect( cbaRect );
            }
        }

	TRect highlightRect( SettingItemContentRect( ETrue ) );
    
    // transparent setting page
	if(!IsBackgroundDrawingEnabled())
	    {
	    color = AKN_LAF_COLOR_STATIC(0);
	    AknLayoutUtils::LayoutLabel(
	        iTextLabel,
	        rect,
	        AknLayoutScalable_Avkon::main_pane_set_t1_copy1( 3 ) );
	    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iTextLabel, EColorLabelText, color ) );
        
        if(iExtension->iShadowText)
            {            
            highlightRect.Move(1,1);
    	    color = AKN_LAF_COLOR_STATIC(215);
    	    AknLayoutUtils::LayoutLabel(
    	        iExtension->iShadowText,
    	        rect,
    	        AknLayoutScalable_Avkon::main_pane_set_t1_copy1( 3 ) );
    	    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *(iExtension->iShadowText), EColorLabelText, color ) );        
            }
	    }
	else // normal setting page
	    {
	    // no ordinal
	    if ( !iNumberLabel )
    	    {
    	    AknLayoutUtils::LayoutLabel(
    	        iTextLabel,
    	        rect,
    	        AknLayoutScalable_Avkon::main_pane_set_t1_copy1( iIsProtected ? 3 : 2 ) );
    	    }
    	else
    		{
            TAknTextLineLayout textLabelLayout(
    	        AknLayoutScalable_Avkon::main_pane_set_t1_copy1( 4 ).LayoutLine() );

            if ( !iIsProtected ) // is there lock icon
                {
                // There's isn't a variety for this case, so we do some
                // composing.
                TAknTextLineLayout longTextLabelLayout(
                    AknLayoutScalable_Avkon::main_pane_set_t1_copy1( 2 ) );
                textLabelLayout.ir = longTextLabelLayout.ir;
                }
    	
    		AknLayoutUtils::LayoutLabel(
    		    iTextLabel,
    		    rect,
    		    textLabelLayout );
    		AknLayoutUtils::LayoutLabel(
    		    iNumberLabel,
    		    rect,
                AknLayoutScalable_Avkon::main_pane_set_t2_copy1( 1 ) );
    		
    		if (!error)
    	        {
    	        // set the ordinal color
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iNumberLabel, 
	                EColorLabelText, color ) );
    	        }
    		}
    		
        if (!error)
            {
            // set the text color, same for all so set in general place
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iTextLabel, 
	            EColorLabelText, color ) );
            }
        }		 

	if(!IsBackgroundDrawingEnabled() && iExtension->iSBFrame)
		{
		TRAP_IGNORE( iExtension->iSBFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EOff) );                 
		}

	if ( iExtension->iEmbeddedSoftkeys )
	    {
        TAknLayoutRect innerRect;
        innerRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::bg_popup_window_pane_g1( 0 ) );
        iExtension->iFrameBgContext->SetFrameRects( rect, innerRect.Rect() );
	    }
	else
	    {
	    iExtension->iBasicBgContext->SetRect( rect );
	    }
	
	TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;
    
    vSbarModel.iScrollSpan= 0;
    vSbarModel.iThumbSpan = 0;
    
    // Layout scrollbar
    
    if ( iExtension->iSBFrame )
        {
        vSbarModel.iThumbPosition = 0;
        TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
        TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );
        
        iExtension->iSBFrame->Tile( &vDsSbarModel );
        AknLayoutUtils::LayoutVerticalScrollBar( iExtension->iSBFrame, 
            ContainerRect( iExtension->iEmbeddedSoftkeys ),
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::listscroll_set_pane_copy1( 0 ),
                AknLayoutScalable_Avkon::scroll_pane_cp121_copy1( 0 ) ) );       
        iExtension->iSBFrame->SetVFocusPosToThumbPos( vDsSbarModel.FocusPosition() );
        }
    
    if(iExtension->iLockIcon)
        {
        TAknLayoutRect layRect;
        layRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::set_content_pane_g1_copy1( 0 ) );
        iExtension->iLockIconRect = layRect.Rect();
        AknIconUtils::SetSize(iExtension->iLockIcon, iExtension->iLockIconRect.Size(), 
            EAspectRatioPreservedAndUnusedSpaceRemoved );
        }
    }
		
/**
 *From MEikMenuObserver ( this one has to be implemented as is pure virtual )
 * (called when menu is cancelled)
 */
EXPORT_C void CAknSettingPage::SetEmphasis(CCoeControl* aMenuControl, TBool aEmphasis)
	{
	CEikAppUi* appUi = iEikonEnv->EikAppUi();
	appUi->UpdateStackedControlFlags(this, aEmphasis ? ECoeStackFlagRefusesFocus : 0, ECoeStackFlagRefusesFocus);
	appUi->RemoveFromStack(aMenuControl);
	TRAP_IGNORE(appUi->AddToStackL(aMenuControl, aEmphasis ? ECoeStackPriorityDialog : ECoeStackPriorityMenu));	// should not leave since just removed.
	appUi->UpdateStackedControlFlags(aMenuControl, aEmphasis ? 0 : ECoeStackFlagRefusesFocus, ECoeStackFlagRefusesFocus);
	appUi->HandleStackChanged();
	}

/**
 * This function intialiases the items on the menu.  It's used to disable and enable menu items and may be
 * over ridden to add new ones.
 * In addition it adds menu items which have been provided in the ConstructL in the form of a Menu Bar resource.
 * Instead of using the Menu Bar directly it extracts the menu panes and adds them to it's own menu pane.
 * It must be called in the DynInitMenuPaneL() function of any derived class before anything else!!
 *
 */
EXPORT_C void CAknSettingPage::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ) 
	{
	if ( aResourceId == R_AVKON_FORM_MENUPANE )
		{
		if ( iMenuBarId )
			{
			TResourceReader reader ;
			iCoeEnv->CreateResourceReaderLC( reader, iMenuBarId ) ;

			TInt count = reader.ReadInt16() ;  // Number of menu panes
			while (count--)
				{
				TInt menuPaneResourceId = reader.ReadInt32() ;
				reader.ReadTPtrC() ; // read and ignore the rest...
				reader.ReadInt32() ;
				reader.ReadTPtrC() ;
				reader.ReadInt16() ;
				reader.ReadInt16() ;
				reader.ReadInt32() ; 
				aMenuPane->AddMenuItemsL( menuPaneResourceId, 0, ETrue ) ; // at the top, with a separator
				}
			CleanupStack::PopAndDestroy() ; // Resource Reader
			}
		}
	}
/**
* This implementation concerns itself only with the layout switch. Otherwise, the base 
* class is called.
*/
EXPORT_C void CAknSettingPage::HandleResourceChange(TInt aType)
	{
    if(aType==KEikDynamicLayoutVariantSwitch)
		{
		SetRect( ControlRect( iExtension->iEmbeddedSoftkeys ) );
        }
	else if( aType == KAknsMessageSkinChange )
	    {
	    // Create lock icon
	    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	    
	    delete iExtension->iLockIcon;
	    delete iExtension->iLockIconMask;
	    iExtension->iLockIcon = NULL;
	    iExtension->iLockIconMask = NULL;
	    TRAP_IGNORE(AknsUtils::CreateColorIconL(skin, KAknsIIDQgnIndiSettProtectedAdd, 
        KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG16, iExtension->iLockIcon, 
        iExtension->iLockIconMask, KAvkonBitmapFile, EMbmAvkonQgn_indi_sett_protected_add, 
        EMbmAvkonQgn_indi_sett_protected_add_mask, KRgbBlack));
        
		StandardSettingPageLayout();
	    }
	
	CCoeControl::HandleResourceChange(aType);
	}

/**
 * Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyBack
 * to accept or cancel the pop-up.
 *
 * @param	aCommandId	Event Id from the soft-key
 */
EXPORT_C void CAknSettingPage::ProcessCommandL(TInt aCommandId)
	{
	if(!IsEditable() && !(aCommandId == EAknSoftkeyBack || aCommandId == EAknSoftkeyCancel))
	    {
	    return;
	    }
	
	HideMenu();

	// Respond to softkey events
	switch (aCommandId)
		{
		case EAknSoftkeyOk:
		case EAknSoftkeySelect:  
		case EAknSoftkeyDone:
			SelectCurrentItemL(); // has non-trivial implemenations in listbox type 
										// controls to put the selection on the current item
			AttemptExitL(ETrue);
			break;
		case EAknSoftkeyBack:
		case EAknSoftkeyCancel:
			AttemptExitL(EFalse);
			break;
		case EAknSoftkeyOptions:
			DisplayMenuL();
			break;
		default:
			break;
		}
	}

/**
 * Acts upon changes in the hosted control's state. 
 * This class's implementation is trivial and should be able to be
 * safely re-implemented in client-derived classes.
 *
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
EXPORT_C void CAknSettingPage::HandleControlEventL(CCoeControl* /*aControl*/,
				 MCoeControlObserver::TCoeEvent aEventType)
	{
	// This implementation is good for most controls so it is provided 
	// here in the base class
	if ( aEventType == EEventStateChanged && iUpdateMode == EUpdateWhenChanged )
		{
		UpdateSettingL();
		}
	}

/**
 * Called when the user accepts or cancels the setting. Default implementation
 * sets the return value and exists.  
 *
 * @param	aAccept ETrue if the user accepted. EFalse if the user cancelled.
 */
EXPORT_C void CAknSettingPage::AttemptExitL(TBool aAccept)
	{
	if ( OkToExitL( aAccept ) )
		{
		DismissL( aAccept );
		if(iReturn)
			{
		    *iReturn = aAccept;
			}
		StopActiveScheduler();
		}
	else 
	    {
	    DrawDeferred();
	    }
	}

/**
 * Checks if it OK to exit. Derived classes may check for valid data before allowing the dialog to 
 * leave, possibly putting up notes.
 *
 * Returns ETrue if the dialog is ready to exit. Returns ETrue by default.
 */
EXPORT_C TBool CAknSettingPage::OkToExitL(TBool /*aAccept*/ )
	{
	return(ETrue);
	}


/**
 * Called to remove the setting page 
 *
 * @param	aAccept ETrue to accept the current value; EFalse otherwise
 */
EXPORT_C void CAknSettingPage::DismissL(TBool aAccept)
	{
    AknItemActionMenuRegister::SetOverridingMenuBarOwnerL( NULL );
    MakeVisible( EFalse );

	if ( aAccept )
		{
		AcceptSettingL();
		if ( iSettingPageObserver )
			iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingOked);
		}
	else
		{
		RestoreOriginalSettingL();
		if ( iSettingPageObserver )
			iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingCancelled);
		}

	iEikonEnv->RemoveFromStack(iCba);
	delete iCba;
	iCba = 0;

	PopNaviDecoratorIfRequired();
	}

/**
 * Substitutes the new setting number.	If not yet constructed, just record the new value.
 * If already constructed, we have to reformat the label.  
 * 
 * The label reformatting code needs to be soaked up in another routine for ROM saving and 
 * double maintenance
 *
 * @param	aSettingNumber	The new setting number to display
 */
EXPORT_C void CAknSettingPage::SetSettingNumberL( TInt aSettingNumber )
	{
	iSettingNumber = aSettingNumber;
	SetNumbered( ETrue);

	// Update the number label if present
	if ( iNumberLabel )
		{
		TBuf<KAknSettingPageMaxOrdinalDigits> text; 
		text.Format(_L("%d"),iSettingNumber); // Subject to layout changes
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion(text);
		iNumberLabel->SetTextL( text );
		}
	}

/**
 * Sets the observer for the setting.
 *
 * @param	aObserver	The observer for changes to the setting
 */
EXPORT_C void CAknSettingPage::SetSettingPageObserver( MAknSettingPageObserver* aObserver)
	{
	iSettingPageObserver = aObserver;
	}

/**
 * Sets the setting Id.  The Id may be used to unabiguously number a setting in some context
 * It would be useful to call SettingId() on aSettingPageControl in handling an observer
 * callback
 *
 * @param	aSettingId		An id to provide to the observer in the callback 
 */
EXPORT_C void CAknSettingPage::SetSettingId( TInt aSettingId )
	{
	iSettingId = aSettingId;
	}

/**
 * returns the setting Id.
 *
 */
EXPORT_C TInt CAknSettingPage::SettingId( void ) const
	{
	return iSettingId;
	}


/**
 * Substitutes the new setting text.  Allocate memory for it.
 * If already constructed, we have to reformat the label.  
 * 
 * Note that calling this will over-ride text in Setting Page resource
 * 
 * @param	aSettingText	The new setting text to display
 */
EXPORT_C void CAknSettingPage::SetSettingTextL( const TDesC& aText )
	{
    HBufC* newBuffer = 
        HBufC::NewL(aText.Length());
	
    delete iSettingText;
    iSettingText = newBuffer;

    *iSettingText = aText;
    
	if (iTextLabel && iSettingText)
		{
		iTextLabel->SetTextL(*iSettingText);
		iTextLabel->CropText();
		if(iExtension->iShadowText)
		    {		    
    		iExtension->iShadowText->SetTextL(*iSettingText);
    		iExtension->iShadowText->CropText();
		    }
		}
	}


/**
 * Standard CCoeControl routine to return the control at a given index
 *
 * @param	aIndex	index at which to return control
 */
EXPORT_C CCoeControl* CAknSettingPage::ComponentControl(TInt aIndex) const
	{
	CCoeControl* buttonGroupControl = NULL;
	
	if ( iCba && iExtension->iEmbeddedSoftkeys )
	    {
	    MEikButtonGroup* buttonGroup = iCba->ButtonGroup();
	    
	    if ( buttonGroup )
	        {
	        buttonGroupControl = buttonGroup->AsControl();
	        }
	    }
	CCoeControl* controls[] = { 
	        iEditorControl, 
	        iExtension->iShadowText, 
	        iTextLabel, 
	        iNumberLabel,
	        buttonGroupControl,
	        iExtension->iSBFrame ? 
	            iExtension->iSBFrame->VerticalScrollBar() : NULL,
	        iExtension->iEditIndicator };

	for (TUint ii=0;ii<sizeof(controls)/sizeof(CCoeControl*);ii++)
	  if (controls[ii] && aIndex-- == 0)
	  {
		return controls[ii];
	  }
	return NULL;
	}
	
EXPORT_C void CAknSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {   
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

/**
* Get InputCapabilities.  Overrides CoeControl::InputCapabilities
*
*/
EXPORT_C TCoeInputCapabilities CAknSettingPage::InputCapabilities() const
	{
	return TCoeInputCapabilities(TCoeInputCapabilities::EAllText, NULL, iExtension);	
	}

EXPORT_C void* CAknSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 * Standard CCoeControl routine to return the number of component controls
 *
 * @return	number of component controls
 */
EXPORT_C TInt CAknSettingPage::CountComponentControls() const
	{
	TInt count = 0;
    CCoeControl* buttonGroupControl = NULL;
    
    if ( iCba && iExtension->iEmbeddedSoftkeys )
        {
        MEikButtonGroup* buttonGroup = iCba->ButtonGroup();
        
        if ( buttonGroup )
            {
            buttonGroupControl = buttonGroup->AsControl();
            }
        }
	CCoeControl* controls[] = { 
	        iEditorControl, 
	        iExtension->iShadowText, 
	        iTextLabel, 
	        iNumberLabel, 
	        buttonGroupControl,
	        iExtension->iSBFrame ? 
	            iExtension->iSBFrame->VerticalScrollBar() : NULL,
	        iExtension->iEditIndicator };
	for (TUint ii=0;ii<sizeof(controls)/sizeof(CCoeControl*);ii++)
		if (controls[ii])
			count++;
	return count;

	}

/**
 * Returns reference to the hosted "editor" control as a CCoeControl.
 * This routine is used in derived classes, which then case to the specific run-time type
 * 
 */
EXPORT_C CCoeControl* CAknSettingPage::EditorControl() const
	{
	return iEditorControl;
	}

/**
* Access routine for private state data
*/
EXPORT_C TBool CAknSettingPage::Waiting()
	{
	return iWait.IsStarted();
	}

/**
 * Internal routine to restore a saved "original" value 
 *
 */
EXPORT_C void CAknSettingPage::RestoreOriginalSettingL()
	{
	}

/**
 * 
 * Executes a waiting dialog-like setting page
 * 
 * The passed mode determines if the editor's value is updated continuously, or just
 * when it is accepted.
 * 
 * @param	aMode		The update mode of the class
 */
EXPORT_C TBool CAknSettingPage::ExecuteLD( TAknSettingPageUpdateMode aMode )
	{

	// This is a copy of the return value on the stack
    TBool returnValue = EFalse;
	// Set a pointer to this return value so that it can be modified in other
	// methods while the setting page is running.
	// This relationship must be set up before any user-re-implementable methods
	// so that they have a value return value. 
	iReturn = &returnValue;

	CleanupStack::PushL( this ); // Matching Pop is in AttemptExitL
	CAknInputBlock* inputBlock = CAknInputBlock::NewLC( );
	if ( !IsBaseConstructed() )
		ConstructL();
	iUpdateMode = aMode;

// Ensure we have a menu bar by this point
	__ASSERT_DEBUG( iMenuBar, Panic( EAknPanicSettingPageNoMenuBar ) ) ;

	DynamicInitL();
	ActivateL();

	if ( iExtension->iEmbeddedSoftkeys )
	    {
	    iExtension->iFader.FadeBehindPopup( iExtension, this, ETrue );
	    }
	
	// Catch up with editor's brute draw (in editor setting page)
	DrawNow();   //  EECO-7QYCR4 and TSAA-7Q3D2J is conflict , so make an extra draw operation here
    DrawDeferred();

	iEditorControl->SetObserver( this );
	iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog);

    if( !iExtension->iEmbeddedSoftkeys )
        {
        if (!iNaviPane)
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            if(sp)
                iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
            }

        // It would be nice if iNaviDecorator is always going to point to uniquely identifiable
        // Pop-able item - but this is not the case. 
        // The default navipane Wipe is represented by a NULL in the stack, so that 
        // is not much good for recording if the leaving methods were successful or not - 
        // That is, you cannot distinguish between failed creation/Pushing, or the result of a 
        // PushDefaultL().
        // The solution is to use iNaviPane as a record as to whether we need to pop or not, 
        // hence it needs to be zeroed if the Push fails
        if ( iHintText && iNaviPane )
            {
            TRAPD( err, iNaviDecorator = iNaviPane->CreateNavigationLabelL( iHintText->Des() ) );
            if ( err != KErrNone )
                {
                iNaviPane = 0; //  This will suppress the Pop
                User::Leave( err );
                }
            else
                {
                // OK if this leaves.  iNaviDecorator will not be found when you pop
                iNaviPane->PushL(*iNaviDecorator); 
                }
            }
        else if(iNaviPane)
            {
            TRAPD( err, iNaviPane->PushDefaultL( ETrue ) ); // We will have to suppress Pop if this fails
            if ( err != KErrNone )
                {
                iNaviPane = 0; //  This will suppress the Pop
                User::Leave( err );
                }
            else
                {
                // Actually, this returns a NULL but still do it for in case the wipe becomes
                // represented by a concrete object in future.
                iNaviDecorator = iNaviPane->Top(); 
                }
            }
        }

    CleanupStack::PopAndDestroy( inputBlock );   

	if ( PostDisplayCheckL() )
		{
		StartActiveScheduler();
		}
	else
		AttemptExitL(EFalse);
	
	iEikonEnv->EikAppUi()->RemoveFromStack(this);
	CleanupStack::Pop(); // this

	if ( iExtension->iEmbeddedSoftkeys )
	    {
	    iExtension->iFader.FadeBehindPopup( iExtension, this, EFalse );
	    }
	
	delete (this);
	return returnValue;
	}

/**
 * Puts up a constructed dialog. Part of the non-waiting API calls.    
 * Activity to perform as soon as the setting page is displayed
 * 
 */
EXPORT_C TBool CAknSettingPage::PostDisplayCheckL()
	{
	return ETrue;
	}

/**
* Called immediately prior to activation of the dialog.  Framework routine for derived
* classes.
*
*/
EXPORT_C void CAknSettingPage::DynamicInitL()
	{
	}

/**
* Called when something has changed. Use to update the object referenced by 
* the client code. 
*
*/
EXPORT_C void CAknSettingPage::UpdateSettingL()
	{
	}

/**
* Called when the setting page has been dismissed and the user is accepting the value.
* Derived classes need to implement.
*/
EXPORT_C void CAknSettingPage::AcceptSettingL()
	{
	}
/**
* Draw routine.  Overrides CoeControl::Draw
*
*/

EXPORT_C void CAknSettingPage::Draw(const TRect& aRect) const
	{ 
	BaseDraw( aRect );
	}


EXPORT_C void CAknSettingPage::BaseDraw( const TRect& /*aRect*/ ) const
	{
	CWindowGc& gc = SystemGc();

	if ( iIsProtected && iExtension->iLockIcon )
        {
        TRect lockRect( TPoint( 0, 0 ), iExtension->iLockIconRect.Size() );

        gc.BitBltMasked( iExtension->iLockIconRect.iTl,
                         iExtension->iLockIcon,
                         lockRect,
                         iExtension->iLockIconMask,
                         ETrue );
        }
	}

/**
 * Return the CBA reference; Must be called after full construction, or null reference will 
 * be returned.
 *
 */
EXPORT_C CEikButtonGroupContainer* CAknSettingPage::Cba() const
	{	
	return (iCba);
	}

/**
 * 
 */
EXPORT_C void CAknSettingPage::DisplayMenuL() 
	{
	iMenuBar->TryDisplayMenuBarL() ;
	}

/**
 * 
 */
EXPORT_C void CAknSettingPage::HideMenu() 
	{
    if( iMenuBar ) 
        {
        iMenuBar->StopDisplayingMenuBar();
        }
    }

/**
 *	This is used as a protected access function for the state of the menu bar
 *	
 */
EXPORT_C TBool CAknSettingPage::MenuShowing() const
	{
        if(iMenuBar)
            {
	    return iMenuBar->IsDisplayed();
            }

        return EFalse;  
        }
/**
 *	This is used to access the default resource id for the cba
 */
EXPORT_C TInt CAknSettingPage::DefaultCbaResourceId() const
	{
	return ( iCbaResourceId ) ;
	}

EXPORT_C void CAknSettingPage::Reserved_MtsmPosition()
	{
	}

EXPORT_C void CAknSettingPage::Reserved_MtsmObject()
	{
	}

/**
 * Access method for the number of the setting page
 *
 */
EXPORT_C TInt CAknSettingPage::SettingNumber() const
	{
	return iSettingNumber;
	}

/**
 * Access method for whether the setting page is numbered or not
 *
 */
EXPORT_C TBool CAknSettingPage::IsNumbered() const
	{
	return ( iFlags.IsSet( ENumberedStyleIndex ) );
	}

/**
 * Set method for whether the setting page is numbered or not
 *
 */
EXPORT_C void CAknSettingPage::SetNumbered( TBool aNumbered )
	{
	iFlags.Assign( ENumberedStyleIndex, aNumbered );
	}
/**
 * Access method for the internally held resource Id
 *
 */
EXPORT_C TInt CAknSettingPage::SettingPageResourceId()
	{
	return iResourceId;
	}

/**
 * This method can be used to test if BaseConstructL() has been called yet
 * successfully
 *
 */
EXPORT_C TBool CAknSettingPage::IsBaseConstructed()
	{
	return ( iFlags.IsSet( EIsBaseConstructedIndex ) );
	}

/** 
 * Puts the focus back on the editor. For complicated setting pages that have focus removed from them
 * at some point, then a re-implementation may have to do some work here.
 *
 */
EXPORT_C void CAknSettingPage::SetFocusToEditor()
	{
	__ASSERT_DEBUG(EFalse, Panic(EAknPanicSettingPageDeprecated) ) ;
	}

/** 
 * This framework method is used to update the contents of the CBA in a custom way.
 * Some setting page classes implement a degree of validation and will implement this.
 * Derived classes should ensure that this and CheckAndSetDataValidity() are called frequently enough for their
 * purposes.
 *
 */
EXPORT_C void CAknSettingPage::UpdateCbaL()
	{
	if ( IsStopActiveSchudlerCalled() )
	    {
	    CAknEnv::StopSchedulerWaitWithBusyMessage(iWait);
	    return;
	    }

	if(!IsEditable())
	    {
	    Cba()->SetCommandSetL( InvalidDataCbaResourceId() );
	    return;
	    }
	
	if ( InvalidDataCbaResourceId() != DefaultCbaResourceId() )
		{
		TBool validLabels = ETrue;
		if ( !DataValidity() )
			{
			TInt leftId;
			leftId	= (Cba()->ButtonGroup()->CommandId(0)); 
			if ( (leftId == EAknSoftkeyOk ) 
				|| (leftId == EEikBidBlank) 
				|| (leftId == EAknSoftkeyEmpty)
				|| (leftId == 0 ) ) // Despite the resources, only switch if the left is OK or blank
				validLabels = EFalse;
			}

		if ( validLabels )
			Cba()->SetCommandSetL( DefaultCbaResourceId() );
		else
			Cba()->SetCommandSetL( InvalidDataCbaResourceId() ); 

		Cba()->DrawDeferred();
		}
	}

/**
 * This method is re-implemented in listbox editor setting pages to move
 * the selection to the current highlighted item
 *
 */
EXPORT_C void CAknSettingPage::SelectCurrentItemL()
	{
	// No action by default
	}

EXPORT_C void CAknSettingPage::FocusChanged(TDrawNow aDrawNow)
	{
	CCoeControl* ctrl = EditorControl();
	if (ctrl)
		ctrl->SetFocus(IsFocused(), aDrawNow);			
	}

EXPORT_C TInt CAknSettingPage::InvalidDataCbaResourceId() const
	{
	return iInvalidDataCbaResourceId;
	}

EXPORT_C void CAknSettingPage::SetDataValidity( TBool aValid )
	{
	iFlags.Assign( EHasValidDataIndex, aValid );
	}

EXPORT_C TBool CAknSettingPage::DataValidity( ) const
	{
	return (iFlags.IsSet( EHasValidDataIndex ));
	}

EXPORT_C void CAknSettingPage::CheckAndSetDataValidity()
	{
	// Default implementation in the base class
	SetDataValidity( ETrue );
	}


// ----------------------------------------------------------------------------
// Sets the outer and inner rectangle for the frame graphics that is drawn
// around the setting item.
// ----------------------------------------------------------------------------
//
void CAknSettingPage::SetEditedItemFrameRects( const TRect& aOuterRect,
                                               const TRect& aInnerRect )
    {
    iExtension->SetEditedItemFrameRects( aOuterRect, aInnerRect );
    }


// ----------------------------------------------------------------------------
// Sets the skin item ID for the frame graphics that is drawn around the
// setting item.
// ----------------------------------------------------------------------------
//
void CAknSettingPage::SetEditedItemFrameIID(
        const TAknsItemID& aFrameIID,
        const TAknsItemID& aFrameCenterIID )
	{
	iExtension->SetEditedItemFrameIID( aFrameIID, aFrameCenterIID );
	}


// ----------------------------------------------------------------------------
// Sets the rectangle for the editing state indicators.
// ----------------------------------------------------------------------------
//
void CAknSettingPage::SetEditorIndicatorRect( const TRect& aRect )
    {
    CAknQueryEditIndicator* editIndicator =
        iExtension->EditorIndicatorContainer();

    if ( editIndicator )
        {
        editIndicator->SetRect( aRect );
        }
    }


TBool CAknSettingPage::IsSkinsHandlingEditorFrameDrawing() const
	{
	return ETrue;
	}

CAknsFrameBackgroundControlContext* CAknSettingPage::EditedItemControlContext() const
	{
	return NULL;
	}


// ---------------------------------------------------------------------------
// CAknSettingPage::BaseConstructL
// ---------------------------------------------------------------------------
//
void CAknSettingPage::BaseConstructL( TUint aFlags )
    {
    if ( aFlags & KAknSettingPageNoEmbeddedSoftKeys )
        {
        if ( !iExtension )
            {
            iExtension = CAknSettingPageExtension::NewL( this );
            }

        iExtension->iEmbeddedSoftkeys = EFalse;
        }
    
    BaseConstructL();
    }


EXPORT_C TTypeUid::Ptr CAknSettingPage::MopSupplyObject(TTypeUid aId)
	{
    if ( aId.iUid == CEikScrollBarFrame::ETypeId && iExtension->iSBFrame )
        {
        return aId.MakePtr( iExtension->iSBFrame );
        }
    else if ( aId.iUid == MAknEditingStateIndicator::ETypeId &&
              iExtension->iEditIndicator )
        {
        return SupplyMopObject( aId, iExtension->iEditIndicator );
        }

    return SupplyMopObject( aId, iCba, iMenuBar );
	}

EXPORT_C void CAknSettingPage::SetEditState(const TBool aEditable)
    {
    if(aEditable)
        iIsProtected = 0;
    else
        iIsProtected = 1;
    
    if(Cba()) 
    	{
    	TRAP_IGNORE( UpdateCbaL() );    	
    	}
    }
    
EXPORT_C TBool CAknSettingPage::IsEditable() const
    {
    TBool editable = ETrue;
    
    if(iIsProtected != 0)
        editable = EFalse;
    
    return editable;
    }


// ---------------------------------------------------------------------------
// Calculates and returns setting item content rect.
// ---------------------------------------------------------------------------
//
TRect CAknSettingPage::SettingItemContentRect( TBool aScrollBarUsed )
    {
    TRect containerRect( ContainerRect( iExtension->iEmbeddedSoftkeys ) );
    TRect contentRect;

    TAknLayoutRect listScrollSetPane;
    listScrollSetPane.LayoutRect(
            containerRect,
            AknLayoutScalable_Avkon::listscroll_set_pane_copy1() );
    
    if ( aScrollBarUsed )
        {
        TAknLayoutRect setContentPane;
        setContentPane.LayoutRect(
            listScrollSetPane.Rect(),
            AknLayoutScalable_Avkon::set_content_pane_copy1() );
        contentRect = setContentPane.Rect();
        }
    else
        {
        // Take the space reserved for scrollbar into use for the content
        // if the scrollbar is not shown.
        contentRect = listScrollSetPane.Rect();
        }
    
    return contentRect;
    }


void CAknSettingPage::PopNaviDecoratorIfRequired()
    {
    if ( iNaviPane && !iExtension->iEmbeddedSoftkeys )
        {
        iNaviPane->Pop( iNaviDecorator ); // iNaviDecorator is not to be detroyed yet

        // This is only a reference. Set to zero only to ensure invariant that we have 
        // poped out iNaviPane context already.
        iNaviPane=0; 
        }
    }

/**
* Enables / disables transparency effect, ie. does the setting page draw it's own background or not.
* @param aDrawBackground  EFalse enables transparency
*/ 
void CAknSettingPage::SetDrawBackground(const TBool aDrawBackground)
    {
    iExtension->iDrawBackground = aDrawBackground;
    }

/**
* Is the setting page drawing the background itself or not (= "transparency")
*/ 
TBool CAknSettingPage::IsBackgroundDrawingEnabled() const
    {
    return iExtension->iDrawBackground;
    }

/**
* Set the flag to indicate that if the function CAknSettingPage::StopActiveScheduler called or not
* @param aStopCalled ETrue means the StopActiveScheduler have been called
*/ 
void CAknSettingPage::SetStopActiveSchedulerFlag(const TBool aStopCalled )
    {
    if( iExtension )
        {
        iExtension->iIsStopActiveSchedulerCalled = aStopCalled;
        }
    }

/**
* Is the setting page's function StopActiveSchudler called or not
*/ 
TBool CAknSettingPage::IsStopActiveSchudlerCalled()const
    {
    if( iExtension )
        {
        return iExtension->iIsStopActiveSchedulerCalled;
        }

     return ETrue;
    }

/**
* Returns pointer to text label
*/   
EXPORT_C CEikLabel* CAknSettingPage::TextLabel() const
    {
    return iTextLabel;
    }   

/**
* Returns pointer to shadow text
*/ 
EXPORT_C CEikLabel* CAknSettingPage::ShadowText() const
    {
    return iExtension->iShadowText;
    }

// End of File
