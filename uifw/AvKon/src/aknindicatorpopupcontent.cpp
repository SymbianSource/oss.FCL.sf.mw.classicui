/*
* Copyright (c) 2007,2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content that is shown inside a universal status
*                indicator popup.
*
*/


// SYSTEM INCLUDE FILES

#include <AknsDrawUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsConstants.h>
#include <AknUtils.h>
#include "akndigitalclock.h"
#include <avkon.mbg>
#include <gulicon.h>
#include <barsread.h>
#include <AknIndicator.h>
#include <AknIndicatorPlugin.h>
#include <AknIndicatorPluginImplUIDs.hrh>
#include <AknIndicatorContainer.h>
#include <apgcli.h>
#include <aknconsts.h>
#include <aknglobalpopupprioritycontroller.h>
#include <AknTasHook.h> // for testability hooks
#include <touchfeedback.h>


// USER INCLUDE FILES
#include "aknindicatorpopupcontent.h"
#include "aknindicatorpopup.h"
#include "AknBatteryIcon.h"
#include "AknSignalIcon.h"


// CONSTANTS

/** Granularity of the indicator item array. */
const TInt KItemArrayGranularity = 8;

/** Path to the clock application, launched directly from the popup. */
_LIT( KClockApplication, "\\sys\\bin\\clock.exe" );

/** Internal state flags. */
enum TIndicatorPopupContentFlags
    {
    /** Pointer down event has happened inside this control. */
    EAknIndicatorPopupContentButton1Down        = 0x00000001,
    /** Clock application is being launched. */
    EAknIndicatorPopupContentClockBeingLaunched = 0x00000002
    };

const TInt KBatteryAreaIndex = 0;
const TInt KSignalAreaIndex  = 1;


// =============================================================================
// CAknIndicatorPopupItem
// Item class declaration & definition.
// =============================================================================
//
NONSHARABLE_CLASS( CAknIndicatorPopupItem ) : public CBase
    {
public:

    /**
    * Default constructor.
    *
    * @param  aUid       UID of the indicator.
    * @param  aPlugin    Pointer to the indicator's ECOM plugin,
    *                    can be NULL.
    * @param  aPriority  Display priority of the indicator.
    * @param  aTextType  Type of the item text.
    */
    CAknIndicatorPopupItem( TInt aUid,
                            CAknIndicatorPlugin* aPlugin,
                            TInt aPriority,
                            TInt aTextType );

    /**
    * Destructor.
    */
    ~CAknIndicatorPopupItem();

    /**
    * Second-phase constructor to be used with custom icon.
    *
    * @param  aText  Item text.
    * @param  aIcon  Indicator icon.
    */
    void ConstructL( const TDesC& aText,
                     const CGulIcon* aIcon );

    /**
    * Second-phase constructor to be used with the default
    * indicator icon.
    *
    * @param  aText    Item text.
    * @param  aIconID  Index of the indicator icon.
    * @param  aIconID  Index of the indicator icon mask.
    */
    void ConstructL( const TDesC& aText,
                     TInt aIconID,
                     TInt aIconMaskID );

    /**
    * Sets the area of this item in the popup.
    *
    * @param  aRect  Rectangle of this item, relative
    *                to the popup.
    */
    void SetRect( const TRect& aRect );

    /**
    * Changes the indicator icon of the item or updates
    * the color when skin changes.
    *
    * @param  aIcon  Pointer to the new icon if the icon
    *                is to be changed.
    */
    void UpdateIndicatorIconL( const CGulIcon* aIcon = NULL );

    /**
    * Updates the item text.
    *
    * @param  aText  Item text.
    */
    void UpdateTextL( const TDesC& aText, TInt aTextType );

    /**
    * Draws the item.
    *
    * @param  aGc  Reference to the window graphics context.
    */
    void DrawItem( CWindowGc& aGc );

public: // Member data

    /** UID of the indicator. */
    TInt                  iUid;

    /** Indicator priority. */
    TInt                  iPriority;

    /** Item text, owned. */
    HBufC*                iText;

    /** Type of the text. */
    TInt                  iTextType;

    /** Item area. */
    TRect                 iRect;

    /** Indicator icon area. */
    TRect                 iIconRect;

    /** Default indicator icon, owned. */
    CGulIcon*             iIcon;

    /** Custom indicator icon, not owned. */
    const CGulIcon*       iCustomIcon;

    /** Index of the default indicator icon. */
    TInt                  iIconID;

    /** Index of the default indicator icon mask. */
    TInt                  iIconMaskID;

    /** Pointer to the indicator plugin, not owned. */
    CAknIndicatorPlugin*  iPlugin;
    };


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::CAknIndicatorPopupItem
// Default constructor
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupItem::CAknIndicatorPopupItem( TInt aUid,
                                                CAknIndicatorPlugin* aPlugin,
                                                TInt aPriority,
                                                TInt aTextType )
    : iUid( aUid ),
      iPriority( aPriority ),
      iTextType( aTextType ),
      iPlugin( aPlugin )
    {
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::CAknIndicatorPopupItem
// Destructor
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupItem::~CAknIndicatorPopupItem()
    {
    delete iText;
    delete iIcon;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::ConstructL
// Second-phase constructor
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::ConstructL( const TDesC& aText,
                                         const CGulIcon* aIcon )
    {
    delete iText;
    iText = NULL;
    iText = aText.AllocL();

    iCustomIcon = aIcon;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::ConstructL
// Second-phase constructor
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::ConstructL( const TDesC& aText,
                                         TInt aIconID,
                                         TInt aIconMaskID )
    {
    delete iText;
    iText = NULL;
    iText = aText.AllocL();

    iIconID     = aIconID;
    iIconMaskID = aIconMaskID;

    UpdateIndicatorIconL();
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::SetRect
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::SetRect( const TRect& aRect )
    {
    iRect = aRect;

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        iRect,
        AknLayoutScalable_Avkon::list_single_uniindi_pane_g1() );
    iIconRect = layoutRect.Rect();

    CFbsBitmap* bitmap = NULL;

    if ( iCustomIcon )
        {
        bitmap = iCustomIcon->Bitmap();
        }
    else if ( iIcon )
        {
        bitmap = iIcon->Bitmap();
        }

    if ( bitmap )
        {
        AknIconUtils::SetSize( bitmap,
                               iIconRect.Size(),
                               EAspectRatioPreserved );
        }
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::UpdateIndicatorIconL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::UpdateIndicatorIconL( const CGulIcon* aIcon )
    {
    if ( iCustomIcon &&
         !aIcon )
        {
        // Custom icon in use
        if ( iPlugin )
            {
            iCustomIcon = NULL;
            TRAPD( err, iCustomIcon = iPlugin->IconL( iUid ) );

            if ( !err && iCustomIcon )
                {
                // Icon update succeeded.
                AknIconUtils::SetSize( iCustomIcon->Bitmap(),
                                       iIconRect.Size(),
                                       EAspectRatioPreserved );
                return;
                }

            // Else use the default icon.
            }
        }

    delete iIcon;
    iIcon = NULL;

    if ( aIcon )
        {
        iCustomIcon = aIcon;

        AknIconUtils::SetSize( iCustomIcon->Bitmap(),
                               iIconRect.Size(),
                               EAspectRatioPreserved );
        }
    else
        {
        CFbsBitmap* bitmap;
        CFbsBitmap* mask;

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        AknsUtils::CreateColorIconLC(
            skin,
            KAknsIIDDefault,
            KAknsIIDQsnIconColors,
            EAknsCIQsnIconColorsCG20,
            bitmap,
            mask,
            KAvkonBitmapFile,
            iIconID,
            iIconMaskID,
            KRgbGray );

        AknIconUtils::SetSize( bitmap,
                               iIconRect.Size(),
                               EAspectRatioPreserved );

        iIcon = CGulIcon::NewL( bitmap, mask );

        CleanupStack::Pop( 2, bitmap );
        }
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::UpdateTextL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::UpdateTextL( const TDesC& aText, TInt aTextType )
    {
    delete iText;
    iText = NULL;
    iText = aText.AllocL();
    iTextType = aTextType;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupItem::DrawItem
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupItem::DrawItem( CWindowGc& aGc )
    {
    // Use custom icon if it exists.
    const CGulIcon* icon = iCustomIcon;
    if ( !icon )
        {
        icon = iIcon;
        }

    if ( icon && icon->Bitmap() && icon->Mask() )
        {
        aGc.BitBltMasked( iIconRect.iTl,
                          icon->Bitmap(),
                          iIconRect.Size(),
                          icon->Mask(),
                          ETrue );
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TAknTextLineLayout textLayout(
        AknLayoutScalable_Avkon::list_single_uniindi_pane_t1().LayoutLine() );

    TRgb textColor;

    if ( iTextType == CAknIndicatorPlugin::EAknIndicatorPluginLinkText )
        {
        aGc.SetUnderlineStyle( EUnderlineOn );
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnHighlightColors,
                                   EAknsCIQsnHighlightColorsCG3 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG55 );
        }

    TAknLayoutText layoutText;
    layoutText.LayoutText( iRect, textLayout );
    layoutText.DrawText( aGc, *iText, ETrue, textColor );

    aGc.SetUnderlineStyle( EUnderlineOff );
    }


// =============================================================================
// CAknIndicatorPopupContent
// =============================================================================
//

// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::NewL
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupContent* CAknIndicatorPopupContent::NewL()
    {
    CAknIndicatorPopupContent* self = CAknIndicatorPopupContent::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::NewLC
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupContent* CAknIndicatorPopupContent::NewLC()
    {
    CAknIndicatorPopupContent* self = new (ELeave) CAknIndicatorPopupContent;
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknIndicatorPopupContent" );
    return self;
    }


// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupContent::~CAknIndicatorPopupContent()
    {
    AKNTASHOOK_REMOVE();
    // Ensure here that this popup is removed from the global
    // popup priority stack.
    AknGlobalPopupPriorityController::RemovePopupPriority( *this );

    iItems.ResetAndDestroy();
    iItems.Close();

    delete iClock;
    delete iBattery;
    delete iSignal;

    if ( iBatteryPlugin || iSignalPlugin )
        {
        delete iBatteryPlugin;
        delete iSignalPlugin;
        REComSession::FinalClose();
        }

    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl( this );
        }

    delete iSeparatorIcon;
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::MinimumSize
// -----------------------------------------------------------------------------
//
TSize CAknIndicatorPopupContent::MinimumSize()
    {
    TInt items( iItems.Count() );

    // Get the maximum number of indicator items from layout data.
    TAknLayoutScalableParameterLimits limits(
        AknLayoutScalable_Avkon::list_single_uniindi_pane_ParamLimits() );
    TInt variety( limits.LastRow() + 1 ); // Last variety for no indicator items

    if ( items > 0 )
        {
        if ( items <= variety )
            {
            variety -= items;
            }
        else
            {
            variety = 0; // Maximum number of items.
            }
        }

    TRect applicationWindow;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       applicationWindow );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        applicationWindow,
        AknLayoutScalable_Avkon::popup_uni_indicator_window( variety ) );

    return TSize( layoutRect.Rect().Size() );
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    TInt  itemCount( iItems.Count() );

    switch ( aType )
        {
        case KAknsMessageSkinChange:
            {
            // Update clock text color.
            TRgb textColor;

            MAknsSkinInstance* skin = AknsUtils::SkinInstance();

            AknsUtils::GetCachedColor( skin,
                                       textColor,
                                       KAknsIIDQsnTextColors,
                                       EAknsCIQsnTextColorsCG55 );

            iClock->SetColor( textColor );

            // Update signal icon.
            iSignal->SetColorIndex( 0 ); // reset skin color
            TRAP_IGNORE( SetSignalStateL( iSignalState ) );
            // Color of the battery indicator is changed by it's container.
            iBattery->HandleResourceChange( aType );
            // Update the signal icon and separator line color.
            TRAP_IGNORE( LoadIconsL() );

            // Update the color of the indicator icons.
            for ( TInt i = 0; i < itemCount; i++ )
                {
                TRAP_IGNORE( iItems[i]->UpdateIndicatorIconL() );
                }
            break;
            }

        case KEikMessageFadeAllWindows:
            {
            if ( !Window().IsFaded() )
                {
                Window().SetFaded( ETrue,
                                   RWindowTreeNode::EFadeIncludeChildren );
                }
            break;
            }

        case KEikMessageUnfadeWindows:
            {
            if ( Window().IsFaded() )
                {
                Window().SetFaded( EFalse,
                                   RWindowTreeNode::EFadeIncludeChildren );
                }
            break;
            }

        default:
            break;
        }
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( Rect().Contains( aPointerEvent.iPosition ) )
        {
        CBase* currentFocusedItem = NULL;
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                // Set flag that down was inside the popup.
                iFlags |= EAknIndicatorPopupContentButton1Down;
                iPreviousPressedDownItem = NULL;
                
                if ( iClock->Rect().Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iClock;
                    iPressedDownRect = iClockPressedDownArea;
                    }
                else if ( iSignalArea.Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iSignal;
                    iPressedDownRect = iSignalPressedDownArea;
                    }
                else if ( iBatteryArea.Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iBattery;
                    iPressedDownRect = iBatteryArea;
                    }
                else
                    {
                    CAknIndicatorPopupItem* item = TappedItem( aPointerEvent.iPosition );
                    if ( item )
                        {
                        currentFocusedItem = item;
                        iPressedDownRect = item->iRect;
                        }
                    else
                    // No item get tapped
                        {                        
                        return;
                        }                   
                    }
                iEnablePressedDownState = ETrue;
                Window().Invalidate( iPressedDownRect );                
                iPreviousPressedDownItem = currentFocusedItem;
                break;    

            case TPointerEvent::EDrag:
                if ( iClock->Rect().Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iClock;
                    }
                else if ( iSignalArea.Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iSignal;
                    }
                else if ( iBatteryArea.Contains( aPointerEvent.iPosition ))
                    {
                    currentFocusedItem = iBattery;
                    }
                else
                    {
                    currentFocusedItem = TappedItem( aPointerEvent.iPosition );
                    }
  
                if( currentFocusedItem != iPreviousPressedDownItem )
                    {
                    iFlags &= ~EAknIndicatorPopupContentButton1Down;
                    iEnablePressedDownState = EFalse;
                    Window().Invalidate( iPressedDownRect );                    
                    }
                break;

            case TPointerEvent::EButton1Up:
                if ( iFlags & EAknIndicatorPopupContentButton1Down )
                    {
                    // Up happened, reset button down flag.
                    iFlags &= ( ~EAknIndicatorPopupContentButton1Down );
                    iEnablePressedDownState = EFalse;

                    if ( iBatteryPlugin &&
                         iBatteryArea.Contains( aPointerEvent.iPosition ) )
                        {
                        ReportEventL(
                            static_cast<MCoeControlObserver::TCoeEvent>(
                                EAknIndicatorPopupTapEvent ) );
                            
                        // Dummy value used as indicator UID parameter,
                        // as it's not used by the battery indicator plugin.
                        iBatteryPlugin->HandleIndicatorTapL( 0 );
                        break;
                        }
                    else if ( iSignalPlugin &&
                         iSignalArea.Contains( aPointerEvent.iPosition ) )
                        {
                        ReportEventL(
                            static_cast<MCoeControlObserver::TCoeEvent>(
                                EAknIndicatorPopupTapEvent ) );

                        // Dummy value used as indicator UID parameter,
                        // as it's not used by the signal indicator plugin.
                        iSignalPlugin->HandleIndicatorTapL( 0 );
                        break;
                        }
                    else if ( iClock &&
                              iClock->Rect().Contains( aPointerEvent.iPosition ) )
                        {
                        ReportEventL(
                            static_cast<MCoeControlObserver::TCoeEvent>(
                                EAknIndicatorPopupTapEvent ) );

                        if ( !( iFlags & EAknIndicatorPopupContentClockBeingLaunched ) )
                            {
                            // Start clock application directly when down event
                            // happens in clock, this functionality was previously
                            // in the CAknDigitalClock.
                            RApaLsSession apa;
                            User::LeaveIfError( apa.Connect() );
                            CleanupClosePushL( apa );
                            CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
                            cmdLine->SetExecutableNameL( KClockApplication );
                            cmdLine->SetCommandL( EApaCommandRun );
                            User::LeaveIfError( apa.StartApp( *cmdLine ) );
                            CleanupStack::PopAndDestroy( 2, &apa ); // cmdLine and apa

                            // Set the flag indicating that clock is being launched.
                            iFlags |= EAknIndicatorPopupContentClockBeingLaunched;
                            }
                        }

                    CAknIndicatorPopupItem* item = TappedItem( aPointerEvent.iPosition );
                    if ( item )
                        {
                        ReportEventL(
                            static_cast<MCoeControlObserver::TCoeEvent>(
                                EAknIndicatorPopupTapEvent ) );
                        
                        item->iPlugin->HandleIndicatorTapL( item->iUid );
                        break;
                        }
                    }
                break;

            default:
                break;
            }
        }
    else if ( iFlags & EAknIndicatorPopupContentButton1Down )// Drag to outside
        {
        iFlags &= ~EAknIndicatorPopupContentButton1Down;
        iEnablePressedDownState = EFalse;
        Window().Invalidate( iPressedDownRect );
        }
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CAknIndicatorPopupContent::CountComponentControls() const
    {
    TInt count = 0;

    if ( iClock )
        {
        count++;
        }

    if ( iBattery )
        {
        count++;
        }

    if ( iSignal )
        {
        count++;
        }

    return count;
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CAknIndicatorPopupContent::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* componentControl = NULL;

    switch ( aIndex )
        {
        case 0:
            componentControl = iClock;
            break;
        case 1:
            componentControl = iBattery;
            break;
        case 2:
            componentControl = iSignal;
            break;
        default:
            break;
        }

    return componentControl;
    }


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknIndicatorPopupContent::SetContainerWindowL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::SetContainerWindowL(
    const CCoeControl& aContainer )
    {
    CCoeControl::SetContainerWindowL( aContainer );

    if( iClock )
        {
        iClock->SetContainerWindowL( aContainer );
        }
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopupContent::AddItemL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::AddItemL( TInt aIndicatorUid,
                                          const TDesC& aText,
                                          TInt aTextType,
                                          const CGulIcon* aIcon,
                                          CAknIndicatorPlugin* aPlugin,
                                          TInt aPriority )
    {
    TInt  itemCount( iItems.Count() );
    for ( TInt i = 0; i < itemCount; i++ )
        {
        if ( iItems[i]->iUid == aIndicatorUid )
            {
            // Indicator item exists already.
            return;
            }
        }

    CAknIndicatorPopupItem* newItem =
        new (ELeave) CAknIndicatorPopupItem( aIndicatorUid,
                                             aPlugin,
                                             aPriority,
                                             aTextType );

    if ( aIcon )
        {
        // If the plugin provides an icon, use it.
        newItem->ConstructL( aText, aIcon );
        }
    else
        {
        // Otherwise use the same icon as in the indicator pane.
        TInt bitmapID;
        TInt maskID;

        CAknIndicator::GetBitmapIndexL(
            CAknIndicatorContainer::EUniversalIndicators,
            aIndicatorUid,
            bitmapID,
            maskID );

        newItem->ConstructL( aText, bitmapID, maskID );
        }

    if ( aPlugin )
        {
        aPlugin->SetPluginObserver( this );
        }

    iItems.AppendL( newItem );

    // Discard possible pressed down highlight when the popup size changes,
    // as the position of the highlighted item may change.
    iEnablePressedDownState = EFalse;
    
    SizeChanged();
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopupContent::RemoveItem
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::RemoveItem( TInt aIndicatorUid )
    {
    TInt itemCount( iItems.Count() );
    for ( TInt i = 0; i < itemCount; i++ )
        {
        if ( iItems[i]->iUid == aIndicatorUid )
            {
            delete iItems[i];
            iItems[i] = NULL;
            iItems.Remove( i );
            break;
            }
        }

    // Discard possible pressed down highlight when the popup size changes,
    // as the position of the highlighted item may change.
    iEnablePressedDownState = EFalse;
    
    SizeChanged();
    }


// ---------------------------------------------------------------------------
// CAknIndicatorPopupContent::SetContentVisible
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::SetContentVisible( TBool aVisible )
    {
    if ( aVisible )
        {
        SizeChanged(); // also includes UpdateFeedbackAreas()
        }
    if ( iClock )
        {
        // The clock timer needs to be running only when the
        // popup is visible.
        if ( aVisible )
            {
            // Error ignored, if this leaves then the clock
            // is not updated if time changes while popup is visible.
            iClock->StartTimer();
            }
        else
            {
            iClock->StopTimer();
            }
        }


    if ( !aVisible )
        {
        // Remove this popup from the global popup priority stack.
        AknGlobalPopupPriorityController::RemovePopupPriority( *this );

        // Clear the state flags.
        iFlags &= ( ~EAknIndicatorPopupContentButton1Down );
        iFlags &= ( ~EAknIndicatorPopupContentClockBeingLaunched );
        }
    else
        {
        // Add this popup from the global popup priority stack so
        // that it can receive key events.
        // Note that the popup priority is not set, so it has
        // priority the default priority, which is 0.
        AknGlobalPopupPriorityController::ShowPopup( *this, ETrue );
        }
    }

// ---------------------------------------------------------------------------
// CAknIndicatorPopupContent::SetBatteryStateL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::SetBatteryStateL( TInt aState )
    {
    if ( iBattery )
        {
        iBattery->SetBatteryIconL( aState );
        }
    }
// ---------------------------------------------------------------------------
// CAknIndicatorPopupContent::SetSignalStateL
// ---------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::SetSignalStateL( TInt aState )
    {
    TInt newState( aState );
    
    if ( iSignal )
        {
        if ( newState == KAknSignalOffLineMode )
            {
            // Set offline state icon to the signal area. 
            iSignal->SetOffLine( ETrue );
            }
        else if ( newState == KAknSignalOffLineMode - 1 )
            {
            // This aState parameter is used to inform about connection
            // state change from offline mode. Signal icon is set not
            // to be in offline state and the correct signal state is
            // used from iSignalState.
            iSignal->SetOffLine( EFalse );
            newState = iSignalState;
            }
        iSignal->LoadIconL( newState, EAknsCIQsnIconColorsCG5 );
        }

    // Ensure that the new value is valid, offline mode state is
    // not stored as a signal state.
    if ( newState >= 0 &&
         newState <= EAknSignalHsdpaIndicatorMultipdp ) // last signal state
        {
        iSignalState = newState;
        }
    }
// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::HandlePluginUpdateL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::HandlePluginUpdateL( TInt aUid )
    {
    TInt  itemCount( iItems.Count() );
    for ( TInt i = 0; i < itemCount; i++ )
        {
        if ( iItems[i]->iUid == aUid &&
             iItems[i]->iPlugin ) // Can update only if we have a
            {                     // pointer to the plugin.
            // Update text
            TInt textType;
            HBufC* text = iItems[i]->iPlugin->TextL( aUid, textType );
            if ( text )
                {
                CleanupStack::PushL( text );
                iItems[i]->UpdateTextL( *text, textType );
                CleanupStack::PopAndDestroy( text );
                }

            // Update icon
            const CGulIcon* icon = NULL;
            TRAPD( err, icon = iItems[i]->iPlugin->IconL( aUid ) );
            if ( !err && icon )
                {
                iItems[i]->UpdateIndicatorIconL( icon );
                }

            break;
            }
        }

    DrawDeferred();
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::UpdateAllIndicatorsL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::UpdateAllIndicatorsL()
    {
    CAknIndicatorPlugin* plugin = NULL;
    TInt  itemCount( iItems.Count() );

    for ( TInt i = 0; i < itemCount; i++ )
        {
        plugin = iItems[i]->iPlugin;

        if ( plugin ) // Can update only if we have a
            {         // pointer to the plugin.
            TInt uid( iItems[i]->iUid );

            // Update text
            TInt textType;
            HBufC* text = plugin->TextL( uid, textType );
            if ( text )
                {
                CleanupStack::PushL( text );
                iItems[i]->UpdateTextL( *text, textType );
                CleanupStack::PopAndDestroy( text );
                }

            // Update icon
            const CGulIcon* icon = NULL;
            TRAPD( err, icon = plugin->IconL( uid ) );
            if ( !err && icon )
                {
                iItems[i]->UpdateIndicatorIconL( icon );
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// Default constructor.
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupContent::CAknIndicatorPopupContent()
    : iItems( KItemArrayGranularity )
    {
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::ConstructL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::ConstructL()
    {
    iClock = CAknDigitalClock::NewL( this );
    TAknTextLineLayout clockLayout(
        AknLayoutScalable_Avkon::uniindi_top_pane_t1( 1 ).LayoutLine() );

    // Ensure that the left and right values of the clock text layout
    // are zero, currently the whole top area is set as the parent
    // for this layout, so it's narrowed by reducting the
    // signal pane area.
    clockLayout.il = 0;
    clockLayout.ir = 0;
    iClock->SetTimeLayout( clockLayout );
    TRgb textColor;

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    AknsUtils::GetCachedColor( skin,
                               textColor,
                               KAknsIIDQsnTextColors,
                               EAknsCIQsnTextColorsCG55 );
    iClock->SetColor( textColor );

    iBattery = CAknBatteryIcon::NewL();
    iBattery->SetContainerWindowL( *this );
    iSignal = CAknSignalIcon::NewL();
    iSignal->SetContainerWindowL( *this );

    // Create default signal icon.
    iSignal->LoadIconL( 0, EAknsCIQsnIconColorsCG5 );

    // Set this to draw the icon also in offline mode.
    iSignal->SetOffLineIconDraw( ETrue );
    TRAPD( err, iBatteryPlugin = CAknIndicatorPlugin::NewL(
        TUid::Uid( KImplUIDBatteryIndicatorPlugin ) ) );
    if ( err == KErrNone )
        {
        iBatteryPlugin->SetPluginObserver( this );
        }
    TRAPD( err1, iSignalPlugin  = CAknIndicatorPlugin::NewL(
        TUid::Uid( KImplUIDSignalIndicatorPlugin ) ) );
    if ( err1 == KErrNone )
        {
        iSignalPlugin->SetPluginObserver( this );
        }

    iFeedback = MTouchFeedback::Instance();

    // Load the separator line and signal icon graphics.
    LoadIconsL();
    
    iEnablePressedDownState = EFalse;
    iPreviousPressedDownItem = NULL;
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::PrioritizeIndicatorsL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::PrioritizeIndicatorsL()
    {
    TInt count = iItems.Count();
    if ( count < 2 )
        {
        return;
        }

    CAknIndicatorPopupItem* temp;
    for ( TInt ii = 1; ii < count; ii++ )
        {
        temp = iItems[ii];
        TInt tempPriority = temp->iPriority;

        if ( tempPriority >= 0 )
            {
            for ( TInt jj = 0; jj <= ii; jj++ )
                {
                TInt indicatorPriority = iItems[jj]->iPriority;

                if ( tempPriority < indicatorPriority )
                    {
                    iItems.Remove( ii );
                    iItems.InsertL( temp, jj );
                    break;
                    }
                else if ( jj == ( ii - 1 ) )
                    {
                    break;
                    }
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::UpdateFeedbackAreas
//
// Digital clock takes care of its own feedback, but we have to either
// enable or block feedback for signal indicator, according to
// wheather it has associated plug-in or not (if it has plug-in, then
// something happens when it is tapped and feedback should be produced).
//
// In addition we have to set feedback to every item, which acts as a link.
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::UpdateFeedbackAreas()
    {
    if ( iFeedback )
        {
        // First remove all old feedback areas
        iFeedback->RemoveFeedbackForControl( this );
        if ( iBatteryPlugin )
            {
            // Set battery indicator's feedback area    
            CFeedbackSpec* fbSpec = CFeedbackSpec::New();
            if ( fbSpec )
                {
                fbSpec->AddFeedback( ETouchEventStylusDown,
                                     ETouchFeedbackSensitiveButton );
                fbSpec->AddFeedback( ETouchEventStylusUp,
                                     ETouchFeedbackSensitiveButton,
                                     ETouchFeedbackVibra );

                iFeedback->SetFeedbackArea( this, 
                                            KBatteryAreaIndex, 
                                            iBatteryArea, 
                                            fbSpec );
                delete fbSpec;                                
                }
            }
            
        if ( iSignalPlugin )
            {
            // Set signal indicator's feedback area
            CFeedbackSpec* fbSpec = CFeedbackSpec::New();
            if ( fbSpec )
                {
                fbSpec->AddFeedback( ETouchEventStylusDown,
                                     ETouchFeedbackSensitiveButton );
                fbSpec->AddFeedback( ETouchEventStylusUp,
                                     ETouchFeedbackSensitiveButton,
                                     ETouchFeedbackVibra );

                iFeedback->SetFeedbackArea( this, 
                                            KSignalAreaIndex, 
                                            iSignalArea, 
                                            fbSpec );
                delete fbSpec;                                
                }
            }

        // Go through the items, and set feedback areas for those which act
        // as link (i.e. have associated plugin)
        TInt itemCount( iItems.Count() );

        for ( TInt i = 0; i < itemCount; i++ )
            {
            if ( iItems[i]->iPlugin &&
                 iItems[i]->iTextType ==
                     CAknIndicatorPlugin::EAknIndicatorPluginLinkText &&
                 iItems[i]->iRect != TRect( 0, 0, 0, 0 ) )
                {
                CFeedbackSpec* fbSpec = CFeedbackSpec::New();
                if ( fbSpec )
                    {
                    fbSpec->AddFeedback( ETouchEventStylusDown,
                                         ETouchFeedbackSensitiveButton );

                    iFeedback->SetFeedbackArea( this,
                                                KSignalAreaIndex + i + 1,
                                                iItems[i]->iRect,
                                                fbSpec );
                    delete fbSpec;                                
                    }
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::LoadIconsL
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::LoadIconsL()
    {
    TRect rect( Rect() );

    delete iSeparatorIcon;
    iSeparatorIcon = NULL;

    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask   = NULL;

    AknsUtils::CreateColorIconL( AknsUtils::SkinInstance(),
                                 KAknsIIDQgnGrafLineVerticalFade,
                                 KAknsIIDQsnLineColors,
                                 EAknsCIQsnLineColorsCG3,
                                 bitmap,
                                 mask,
                                 KNullDesC,
                                 KErrNotFound,
                                 KErrNotFound,
                                 KRgbGray );

    iSeparatorIcon = CGulIcon::NewL( bitmap, mask );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        rect,
        AknLayoutScalable_Avkon::uniindi_top_pane() );

    layoutRect.LayoutRect(
        layoutRect.Rect(),
        AknLayoutScalable_Avkon::uniindi_top_pane_g3( 1 ) );

    AknIconUtils::SetSize( iSeparatorIcon->Bitmap(),
                           layoutRect.Rect().Size(),
                           EAspectRatioNotPreserved );

    //
    // Create a custom signal icon for connectivity manager link.
    //

    CFbsBitmap* signalBitmap = NULL;
    CFbsBitmap* signalMask   = NULL;

    AknsUtils::CreateColorIconL( AknsUtils::SkinInstance(),
                                 KAknsIIDQgnPropLinkConnectionManager,
                                 KAknsIIDQsnIconColors,
                                 EAknsCIQsnIconColorsCG5,
                                 signalBitmap,
                                 signalMask,
                                 AknIconUtils::AvkonIconFileName(),
                                 EMbmAvkonQgn_prop_link_connection_manager,
                                 EMbmAvkonQgn_prop_link_connection_manager_mask,
                                 KRgbGray );

    // Ownership is transferred.
    iSignal->SetSignalIcon( signalBitmap );
    iSignal->SetSignalIconMask( signalMask );
    }

// -----------------------------------------------------------------------------
// CAknIndicatorPopupContent::TappedItem
// -----------------------------------------------------------------------------
//
CAknIndicatorPopupItem* 
CAknIndicatorPopupContent::TappedItem(const TPoint& aPoint) const
    {    
    for ( TInt ii = 0; ii < iItems.Count(); ii++ )
        {
        CAknIndicatorPopupItem* item = iItems[ii];                    
        if ( item->iRect.Contains( aPoint ) && item->iPlugin
             && item->iTextType ==
             CAknIndicatorPlugin::EAknIndicatorPluginLinkText )
            {
            return item;
            }                        
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::SizeChanged
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::SizeChanged()
    {
    TRect rect( Rect() );

    // Popup window top area
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( rect,
                           AknLayoutScalable_Avkon::uniindi_top_pane() );
    TRect topRect( layoutRect.Rect() );

    // Signal pane area
    layoutRect.LayoutRect( topRect,
                           AknLayoutScalable_Avkon::uniindi_top_pane_g1() );
    TRect signalRect( layoutRect.Rect() );

    // Battery pane area
    layoutRect.LayoutRect( topRect,
                           AknLayoutScalable_Avkon::uniindi_top_pane_g2() );
    TRect batteryRect( layoutRect.Rect() );
    
    // Clock pane area
    layoutRect.LayoutRect( topRect,
                           AknLayoutScalable_Avkon::aid_area_touch_clock() );
    TRect clockRect( layoutRect.Rect() );

    // Separator line size
    layoutRect.LayoutRect(
        topRect,
        AknLayoutScalable_Avkon::uniindi_top_pane_g3() );
    TRect separatorRect = layoutRect.Rect();
    TSize separatorSize( layoutRect.Rect().Size() );

    TBool layoutMirrored( AknLayoutUtils::LayoutMirrored() );

    iClock->SetRect( clockRect );
    iBattery->SetRect( batteryRect );
    iSignal->SetRect( signalRect );

    // Make the touch responsive areas of signal pane
    // slightly larger by not taking into account the margins from
    // top and sides.
    iBatteryArea = batteryRect;
    iSignalArea  = signalRect;

    if ( layoutMirrored )
        {
        iBatteryArea.iTl    = topRect.iTl;
        iBatteryArea.iBr.iY = topRect.iBr.iY;
        iSignalArea.iBr     = topRect.iBr;
        iSignalArea.iTl.iY  = topRect.iTl.iY;
        }
    else
        {
        iBatteryArea.iBr    = topRect.iBr;
        iBatteryArea.iTl.iY = topRect.iTl.iY;
        iBatteryArea.iTl.iX = clockRect.iBr.iX;
        iSignalArea.iTl     = topRect.iTl;
        iSignalArea.iBr.iY  = topRect.iBr.iY;
        }

    // Calculate permanent component press down effect rect
    iSignalPressedDownArea = iSignalArea;
    iClockPressedDownArea = clockRect;
        
    // Indicator area
    layoutRect.LayoutRect( rect,
                           AknLayoutScalable_Avkon::list_uniindi_pane() );
    TRect listRect( layoutRect.Rect() );

    TRAP_IGNORE( PrioritizeIndicatorsL() );

    TAknLayoutScalableParameterLimits limits(
        AknLayoutScalable_Avkon::list_single_uniindi_pane_ParamLimits() );
    TInt maxNumberOfIndicatorsShown = limits.LastRow();

    TInt itemCount( iItems.Count() );

    for ( TInt i = 0; i < itemCount; i++ )
        {
        if ( i <= maxNumberOfIndicatorsShown )
            {
            layoutRect.LayoutRect(
                listRect,
                AknLayoutScalable_Avkon::list_single_uniindi_pane( 0, 0, i ) );
            iItems[i]->SetRect( layoutRect.Rect() );
            }
        else
            {
            iItems[i]->SetRect( TRect( 0, 0, 0, 0 ) );
            }
        }

    UpdateFeedbackAreas();

    AknIconUtils::SetSize( iSeparatorIcon->Bitmap(),
                           separatorSize,
                           EAspectRatioNotPreserved );

    DrawDeferred();
    }


// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknIndicatorPopupContent::Draw
// -----------------------------------------------------------------------------
//
void CAknIndicatorPopupContent::Draw( const TRect& aRect ) const
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CWindowGc& gc = SystemGc();

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TRect rect( Rect() );

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::uniindi_top_pane() );
        TRect topRect( layoutRect.Rect() );

        layoutRect.LayoutRect(
            topRect,
            AknLayoutScalable_Avkon::bg_uniindi_top_pane( 1 ) );
        TRect topCenterRect( layoutRect.Rect() );
        layoutRect.LayoutRect(
            topRect,
            AknLayoutScalable_Avkon::uniindi_top_pane_g3() );
        TRect leftSeparatorRect( layoutRect.Rect() );
        
        layoutRect.LayoutRect(
            topRect,
            AknLayoutScalable_Avkon::uniindi_top_pane_g3( 1 ) );
        TRect separatorRect( layoutRect.Rect() );
       
        layoutRect.LayoutRect(
            topRect,
            AknLayoutScalable_Avkon::uniindi_top_pane_g4() );
        TRect rightSeparatorRect( layoutRect.Rect() );

        // Draw the button frame to the permanent items area.
        AknsDrawUtils::DrawFrame( skin,
                                  gc,
                                  topRect,
                                  topCenterRect,
                                  KAknsIIDQsnFrPopupHeading,
                                  KAknsIIDQsnFrPopupHeadingCenter );
        if ( iEnablePressedDownState )
            {  
            AknsDrawUtils::DrawFrame( skin,
                                      gc,
                                      iPressedDownRect,
                                      iPressedDownRect,
                                      KAknsIIDQsnFrListPressed,
                                      KAknsIIDQsnFrListCenterPressed);
            }
        CFbsBitmap* bitmap = iSeparatorIcon->Bitmap();
        CFbsBitmap* mask   = iSeparatorIcon->Mask();

        // Draw the separator line on the top pane.
        gc.BitBltMasked( leftSeparatorRect.iTl,
                         bitmap,
                         leftSeparatorRect.Size(),
                         mask,
                         ETrue );
                          
        gc.BitBltMasked( rightSeparatorRect.iTl,
                         bitmap,
                         rightSeparatorRect.Size(),
                         mask,
                         ETrue );

        // Draw the indicator items.
        for ( TInt i = 0; i < iItems.Count(); i++ )
            {
            if ( aRect.Intersects( iItems[i]->iRect ) )
                {
                iItems[i]->DrawItem( gc );
                }
            }
        }
    }
