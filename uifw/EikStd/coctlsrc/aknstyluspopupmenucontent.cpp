/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content that is shown inside a stylus popup menu.
*
*/


#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsEffectAnim.h>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknBidiTextUtils.h>
#include <AknUtils.h>
#include <AknsConstants.h>
#include <eikapp.h>
#include <aknappui.h>
#include <AknDef.h>
#include <touchfeedback.h>

#include "aknstyluspopupmenuphysicshandler.h"
#include "aknstyluspopupmenucontent.h"

const TInt KItemArrayGranularity = 4;

// Item shown or dimmed
const TInt KShown = 0; 
const TInt KHidden = 1; 

const TInt KNoItemSelected = -1; 


// =============================================================================
// Item class declaration & definition
// =============================================================================
//
NONSHARABLE_CLASS( CAknStylusPopUpMenuItem ) : public CBase
    {
    public:
        CAknStylusPopUpMenuItem( TInt aCommandId );
        ~CAknStylusPopUpMenuItem();
        void ConstructL(const TDesC& aText); 
    public: //Data
        TInt iCommandId; 
        TInt iVisibility;
        HBufC* iText;
        TRect iRect;   
    }; 

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuItem::CAknStylusPopUpMenuItem
// Default constructor
// -----------------------------------------------------------------------------
//
CAknStylusPopUpMenuItem::CAknStylusPopUpMenuItem( TInt aCommandId): 
    iCommandId( aCommandId ), iVisibility( KShown )
    {
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuItem::CAknStylusPopUpMenuItem
// Destructor
// -----------------------------------------------------------------------------
//
CAknStylusPopUpMenuItem::~CAknStylusPopUpMenuItem()
    {
    delete iText; 
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuItem::CAknStylusPopUpMenuItem
// Default constructor
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuItem::ConstructL(const TDesC& aText)
    {
    delete iText;
    iText = NULL; 
    iText = aText.AllocL(); 
    }



// =============================================================================
// Extension class declaration & definition
// =============================================================================
/*
 * Extension contains menu highlight animation functionality. 
 * The CAknStylusPopUpMenuContent class contains a pointer to 
 * this structure. 
 */

NONSHARABLE_CLASS( CAknStylusPopUpMenuExtension ):
    public CActive,
    public MAknsEffectAnimObserver
    {
public:
    enum TFlag
        {
        /**
        * If set, animation creation is attempted. If not set, animation will
        * never be created.
        */
        EFlagUseAnimation = 0
        };

    CAknStylusPopUpMenuExtension();
    ~CAknStylusPopUpMenuExtension();

    void ConstructL( CAknStylusPopUpMenuContent* aControl );
    TInt CreateAnimation();
    void HandleLayoutSwitch();
    void ChangeHighlightBackground();
    void MenuClosed();

public: // Implementation of MAknsEffectAnimObserver
    void AnimFrameReady( TInt aError, TInt );

protected: // CActive overloads
    void DoCancel();
    void RunL();

private: // New internal methods
    void NoAnimIfError( TInt aError );
    void UseNoAnimation();
    void Play();
    TBool DrawHighlightBackground( CFbsBitGc& aGc );
    void PostDeleteAnimation();
    void CreateAnimationL( const TSize& aHighlightSize );
    void DoResizeL( const TSize& aHighlightSize, TBool aAboutToStart );

public: // Data
    CAknsEffectAnim* iAnimation;
    /**
    * Stored flags are explained in enumeration TFlags.
    */
    TBitFlags32 iAnimFlags; 
    TBool iObserverInformed; 
    TBool iInformObserver; 
private: //Data    
    CAknStylusPopUpMenuContent* iControl;
    };

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::CAknStylusPopUpMenuExtension
// High CActive priority is well argumented because running the active object
// will result in animation deletion -> results in freeing resources.
// -----------------------------------------------------------------------------
//
CAknStylusPopUpMenuExtension::CAknStylusPopUpMenuExtension() :
    CActive( EPriorityHigh ),
    iAnimFlags ( 0 )
    {
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::~CAknStylusPopUpMenuExtension
// Destructor for extension class
// -----------------------------------------------------------------------------
//
CAknStylusPopUpMenuExtension::~CAknStylusPopUpMenuExtension()
    {
    Cancel(); // Cancel possibly pending request
    delete iAnimation;
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::ConstructL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::ConstructL( CAknStylusPopUpMenuContent* aControl )
    {
    ASSERT( aControl );
    iControl = aControl;
    iAnimFlags.Set( EFlagUseAnimation ); // Animations are created by default
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::CreateAnimation
// -----------------------------------------------------------------------------
//
TInt CAknStylusPopUpMenuExtension::CreateAnimation()
    {
    if( !iAnimation && iAnimFlags.IsSet( EFlagUseAnimation ) )
        {
        TRAPD( err, CreateAnimationL( iControl->HighlightRect().Size() ) );
        if( KErrNone != err )
            {
            // Animation has not been drawn -> no need for repaint
            UseNoAnimation();
            return err; 
            }
        }
    return KErrNone; 
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::NoAnimIfError
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::NoAnimIfError( TInt aError )
    {
    if( KErrNone != aError )
        {
        UseNoAnimation();
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::UseNoAnimation
// Falls back to normal highlight rendering.
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::UseNoAnimation()
    {
    delete iAnimation;
    iAnimation = NULL;

    // Do not attempt to create animations in the future
    iAnimFlags.Clear( EFlagUseAnimation );
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::HandleLayoutSwitch
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::HandleLayoutSwitch()
    {
    if( iAnimation ) // Animation exists -> try to resize
        {
        // Resize animation
        TBool aboutToStart = ETrue;
        if( iAnimation->State() == EAknsAnimStateStopped )
            {
            aboutToStart = EFalse;
            }

        TRAPD( err, DoResizeL( iControl->HighlightRect().Size(), aboutToStart ) );
        NoAnimIfError( err );
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::ChangeHighlightBackground
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::ChangeHighlightBackground()
    {
    // Every time the current menu item is changed we need to change the
    // animation input layer (animated element is the highlight background that
    // can differ between highlight positions).
    if( iAnimation )
        {
        if( iAnimation->State() == EAknsAnimStateStopped  )
            {
            // Input layers don't exist when stopped or finished. We need to
            // resize to create the input layers and to update the output
            // layer.
            TRAPD( err, DoResizeL( iAnimation->Size(), EFalse ) );
            NoAnimIfError( err );
            }
        else // Either paused, running or finished
            {
            // Update the highlight background
            if( iAnimation->InputRgbGc() )
                {
                DrawHighlightBackground( *iAnimation->InputRgbGc() );
                }

            // We need to update the output frame (otherwise the highlight
            // would be drawn with the old output before the next new animation
            // frame).
            NoAnimIfError( iAnimation->UpdateOutput() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::MenuClosed
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::MenuClosed()
    {
    delete iAnimation;
    iAnimation = NULL;

    iAnimFlags.Set( EFlagUseAnimation );

    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::AnimFrameReady
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::AnimFrameReady( TInt aError, TInt )
    {
    if( KErrNone != aError )
        {
        // Animation has failed to run -> schedule the animation for
        // deletion to fall back to normal rendering.
        PostDeleteAnimation();
        }
    else if( iControl ) // Frame ok
        {
        if ( iControl->IsVisible() )
            {
            iControl->RepaintHighlight();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::DoCancel
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::DoCancel()
    {
    // Required method, but not needed
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::RunL
// Postponed animation deletion is done here
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::RunL()
    {
    UseNoAnimation();
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::Play
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::Play()
    {
    if( !iAnimation )
        {
        return;
        }

    // No need to start running/finished animation
    if( EAknsAnimStateRunning == iAnimation->State() ||
        EAknsAnimStateFinished == iAnimation->State() )
        {
        return;
        }
    if( EAknsAnimStatePaused == iAnimation->State() )
        {
        NoAnimIfError( iAnimation->Continue() );
        }
    else if( EAknsAnimStateStopped == iAnimation->State() )
        {
        if( iAnimation->NeedsInputLayer() )
            {
            TRAPD( err, DoResizeL( iAnimation->Size(), ETrue ) );
            NoAnimIfError( err );

            if( KErrNone != err )
                return;
            }

        NoAnimIfError( iAnimation->Start() );
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::DrawHighlightBackground
// Draws skinned highlight background to the provided graphics context.
// -----------------------------------------------------------------------------
//
TBool CAknStylusPopUpMenuExtension::DrawHighlightBackground( CFbsBitGc& aGc )
    {
    // Draw the background under the current highlight. This simplified
    // drawing, we only grab a piece from the menu background bitmap.
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( iControl );

    return AknsDrawUtils::DrawBackground( skin, cc, iControl, aGc, TPoint(0,0),
                                          iControl->HighlightRect(),
                                          KAknsDrawParamRGBOnly );
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::PostDeleteAnimation
// Schedules the animation for deletion by activating the extension itself.
// Deletion is postponed because in many error/failure occasions the caller has
// been animation and direct deletion is possibly not safe (because function
// stack would return through the deleted object).
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::PostDeleteAnimation()
    {
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::CreateAnimationL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::CreateAnimationL( const TSize& aHighlightSize )
    {
    delete iAnimation;
    iAnimation = NULL;

    iAnimation = CAknsEffectAnim::NewL( this );

    if( !iAnimation->ConstructFromSkinL( KAknsIIDQsnAnimList ) ) 
        {
        // Animation for the ID was not found from the skin
        User::Leave( KErrNotFound );
        }

    DoResizeL( aHighlightSize, ETrue );

    Play();
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuExtension::DoResizeL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuExtension::DoResizeL(
    const TSize& aHighlightSize, TBool aAboutToStart )
    {
    iAnimation->BeginConfigInputLayersL( aHighlightSize, aAboutToStart );

    if( iAnimation->InputRgbGc() )
        {
        DrawHighlightBackground( *iAnimation->InputRgbGc() );
        }

    iAnimation->EndConfigInputLayersL();
    }



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuContent::CAknStylusPopUpMenuContent( CAknStylusPopUpMenu& aPopUpMenu ) : 
    iItems( KItemArrayGranularity ), 
    iCurrentItem( KNoItemSelected ),
    iFirstItem ( 0 ),
    iPopUpMenu( aPopUpMenu ),
    iPhysicsHandler( 0 )
    {
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::ConstructL
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::ConstructL()
    {
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknStylusPopUpMenuExtension;
        iExtension->ConstructL( this );
        }
        
   if ( !iPhysicsHandler )
        {
        iPhysicsHandler = CAknStylusPopUpMenuPhysicsHandler::NewL( this );
        }     
        
    ControlEnv()->AddForegroundObserverL( *this );
    MakeVisible( EFalse );
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::NewL
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuContent* CAknStylusPopUpMenuContent::NewL( CAknStylusPopUpMenu& aPopUpMenu )
    {
    CAknStylusPopUpMenuContent* self = CAknStylusPopUpMenuContent::NewLC( aPopUpMenu );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::NewLC
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuContent* CAknStylusPopUpMenuContent::NewLC( CAknStylusPopUpMenu& aPopUpMenu )
    {
    CAknStylusPopUpMenuContent* self = new ( ELeave ) CAknStylusPopUpMenuContent( aPopUpMenu );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknStylusPopUpMenuContent::~CAknStylusPopUpMenuContent()
    {
    delete iPhysicsHandler;
    
    iItems.ResetAndDestroy();
    CCoeEnv::Static()->RemoveForegroundObserver( *this );
    delete iExtension; 
    if ( iSBFrame )
        {
        delete iSBFrame;    
        }
    }


// ---------------------------------------------------------------------------
// Adds a new menu item to the array of items.
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::AddMenuItemL( const TDesC& aItem, 
    const TInt aCommandId )
    {
    __ASSERT_DEBUG( !IsVisible(), User::Invariant() ); 

    CAknStylusPopUpMenuItem* item = new (ELeave) CAknStylusPopUpMenuItem( 
        aCommandId );
    CleanupStack::PushL( item ); 
    item->ConstructL( aItem );  
    iItems.AppendL( item );
    CleanupStack::Pop( item ); 

    }

// ---------------------------------------------------------------------------
// Removes the menu item based on the given command id and frees the 
// memory occupied by it.
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::RemoveMenuItem( const TInt aCommandId )
    {
    __ASSERT_DEBUG( !IsVisible(), User::Invariant() ); 
    TBool changed = EFalse;
    for ( TInt itemIndex = iItems.Count() - 1; itemIndex >= 0; itemIndex-- )
        {
        if ( iItems[itemIndex]->iCommandId == aCommandId )
            {
            delete iItems[itemIndex];
            iItems.Remove( itemIndex );
            if ( iFirstItem > itemIndex && iFirstItem > 0 )
                {
                iFirstItem--;
                }
            changed = ETrue;
            }
        }
    if ( changed )
        {
        SizeChanged();
        }
    }

// ---------------------------------------------------------------------------
// Hides / unhides the menu item based on the given command id 
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::SetItemDimmed( const TInt aCommandId, const TBool aDimmed )
    {
    __ASSERT_DEBUG( !IsVisible(), User::Invariant() ); 
    
    TInt itemIndex( 0 );
    TBool sizeChanged( EFalse );
    TInt newVisibility( KShown );
    
    if ( aDimmed )
        {
        newVisibility = KHidden;
        }
    
    // Set new visibility to item if it has changed
    for ( itemIndex = 0; itemIndex < iItems.Count(); itemIndex++ )
        {
        if ( iItems[itemIndex]->iCommandId == aCommandId )
            {
            if ( iItems[itemIndex]->iVisibility != newVisibility )
                {
                iItems[itemIndex]->iVisibility = newVisibility;
                sizeChanged = ETrue;
                }
            break; 
            }
        }

    // Update first item and popup size if necessary
    if ( sizeChanged )
        {
        if ( iFirstItem >= itemIndex && iFirstItem > 0 )
            {
            for ( TInt i = 0; i < iItems.Count(); i++ )
                {
                if ( iItems[i]->iVisibility == KShown )
                    {
                    iFirstItem = i;
                    break;
                    }
                }
            }
        SizeChanged();
        }
    }

// ---------------------------------------------------------------------------
// Returns the command id of the specified menu item.
// ---------------------------------------------------------------------------
//
TInt CAknStylusPopUpMenuContent::CurrentCommandId() const
    {
    if ( iCurrentItem >= 0 && iCurrentItem < iItems.Count() )
        {
        return iItems[iCurrentItem]->iCommandId; 
        }
    return KErrNotFound; 
    }
        

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::RepaintHighlight
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::RepaintHighlight() const
    {
    ActivateGc();
    CWindowGc& gc = SystemGc();
    Window().Invalidate( HighlightRect() ); 
    Window().BeginRedraw( HighlightRect() ); 
    DrawItem( gc, iCurrentItem, EDrawHighlight );
    Window().EndRedraw(); 
    DeactivateGc();
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::HighlightRect
// -----------------------------------------------------------------------------
//
TRect CAknStylusPopUpMenuContent::HighlightRect() const
    {
    if ( iCurrentItem >= 0 && iCurrentItem < iItems.Count() )
        {
        return iItems[iCurrentItem]->iRect; 
        }
    return TRect(); 
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::Clear
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::Clear()
    {
    iItems.ResetAndDestroy();
    iCurrentItem = KNoItemSelected;
    iFirstItem = 0;
    iPhysicsHandler->Reset();
    }


// ---------------------------------------------------------------------------
// From class CCoeControl
// Calculates the total size needed to display the items.
// ---------------------------------------------------------------------------
//
TSize CAknStylusPopUpMenuContent::MinimumSize()
    {
    TInt textWidth = 0; // Text width 
    TInt height = 0; // height of all menu items combined.
    TInt width = 0; // Width of menu
    TInt visibleItems = 0; // Number of visible items
    
    // Find the widest visible item and count visible items
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->iVisibility == KShown )
            {
            visibleItems++;
            textWidth = AknLayoutUtils::FontFromId( AknLayoutScalable_Avkon::
            list_single_popup_submenu_pane_t1( 0 ).LayoutLine().FontId() )->TextWidthInPixels( *( iItems[i]->iText ) );
            width = Max( width, textWidth );
            }
        }
        
    if ( visibleItems == 0 )
        {
        return TSize( 0, 0 );
        }
            
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                       mainPaneRect );
    TAknWindowLineLayout listLayout = 
       AknLayoutScalable_Avkon::list_single_touch_menu_pane(0).LayoutLine();
 
    TAknTextLineLayout textLayout = 
       AknLayoutScalable_Avkon::list_single_touch_menu_pane_t1().LayoutLine();

    TAknWindowLineLayout unit = 
       AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine();
    
    TInt singleItemHeight = listLayout.iH; 
    height = singleItemHeight * visibleItems;
    
    if ( height > mainPaneRect.Height() )
        {
        TInt fitsToMenu = mainPaneRect.Height() / singleItemHeight;
        height = fitsToMenu * singleItemHeight;
        TAknWindowLineLayout scrollBar = 
            AknLayoutScalable_Avkon::scroll_pane( 0 );
        width += scrollBar.iW;
        }

    width += textLayout.ir + textLayout.il;

    if ( width > ( mainPaneRect.Width() - unit.iW ) )
        {
        width = mainPaneRect.Width() - ( unit.iW );
        }

    return TSize( width, height );
    }

// ---------------------------------------------------------------------------
// From class CCoeControl
// CAknStylusPopUpMenuContent::HandleResourceChange
// ---------------------------------------------------------------------------
//    
void CAknStylusPopUpMenuContent::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    
    if ( aType == KAknsMessageSkinChange )
        {
        // Implementation when graphics are ready.
        }
    else if ( aType == KEikDynamicLayoutVariantSwitch )
        {

        // Background under highlight may have changed -> we need to update
        // highlight background to animation
        if ( iExtension )
            {
            iExtension->HandleLayoutSwitch();
            }
            
        iPopUpMenu.UpdatePosition();
        }
    else if ( aType == KEikMessageFadeAllWindows ) 
        {
        if ( Observer() ) 
            {
            // this will close the stylus popup menu
            TRAP_IGNORE( Observer()->HandleControlEventL( this,
                MCoeControlObserver::EEventRequestExit ) );
            }    
        }    
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::HandlePointerEventL( 
        const TPointerEvent& aPointerEvent )
    {
    CAknControl::HandlePointerEventL( aPointerEvent );
    CCoeControl* grabber = GrabbingComponent();    
    if( grabber )
        {
        return;
        }
    iPhysicsHandler->HandlePointerEventL( aPointerEvent );
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::MakeVisible
// -----------------------------------------------------------------------------
//    
void CAknStylusPopUpMenuContent::MakeVisible( TBool aVisible ) 
    {
    //Start highlight animation
    CAknControl::MakeVisible( aVisible);     

    if ( aVisible )
        {
        iCurrentItem = KNoItemSelected; 
        if ( iExtension )
            {
            iExtension->iInformObserver = ETrue; 
            iExtension->iObserverInformed = EFalse; 
            }
        // Fix for TSW Error EAJA-73MHSP
        ClaimPointerGrab( ETrue );
        UpdateScrollBar();
        
        // clear pressed down highlight from scrollbar
        if ( iSBFrame )
            {
            CAknDoubleSpanScrollBar* scrollbar = 
                static_cast<CAknDoubleSpanScrollBar*>( 
                        iSBFrame->VerticalScrollBar() );
                
            if ( scrollbar )
                {
                scrollbar->ResetPressedDownHighlight();
                }
            }
        }
    else
        {
        if ( iExtension && iExtension->iInformObserver && !iExtension->iObserverInformed )
            {
            iExtension->iInformObserver = EFalse; 
            TRAP_IGNORE(Observer()->HandleControlEventL( this,
                MCoeControlObserver::EEventRequestCancel )); 
            }
        if ( iSBFrame )
            {
            delete iSBFrame;
            iSBFrame = NULL;
            }
        if( iExtension )
            {
            iExtension->MenuClosed();    
            }
        }
    }
    
// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::CountComponentControls
// -----------------------------------------------------------------------------
//    
TInt CAknStylusPopUpMenuContent::CountComponentControls() const
    {
    if ( iSBFrame )
        {
        return 1;
        }
    return 0;
    }
    
// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::ComponentControl
// -----------------------------------------------------------------------------
//    
CCoeControl* CAknStylusPopUpMenuContent::ComponentControl( TInt aIndex ) const
    {
    return iSBFrame->ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::MoveHighlightTo
// Moves the menu pane highlight to the new selected menu item aNewSelectedItem.
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::MoveHighlightTo(TInt aNewSelectedItem)
    {
    TInt previous = KNoItemSelected; 
    if ( iCurrentItem == aNewSelectedItem )
        {
        return; 
        }
    else
        {
        previous = iCurrentItem; 
        iCurrentItem = aNewSelectedItem; 
        }

    ActivateGc(); 
    CWindowGc& gc =  SystemGc();
    if ( previous >= 0 && previous < iItems.Count() )
        {
        Window().Invalidate( iItems[previous]->iRect ); 
        Window().BeginRedraw( iItems[previous]->iRect ); 
        // Remove highlight from previously highlighted item
        DrawItem( gc, previous, ERemoveHighlight ); 
        Window().EndRedraw(); 
        }
    
    if( iExtension )
        {
        iExtension->ChangeHighlightBackground();
        }
    Window().Invalidate( HighlightRect() ); 
    Window().BeginRedraw( HighlightRect() );     
    DrawItem( gc, iCurrentItem, EDrawHighlight ); 
    Window().EndRedraw(); 
    DeactivateGc(); 
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::DrawItem
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::DrawItem(
    CWindowGc& aGc,TInt aItem,THighlightType aHighlight) const
    {
    TRect rect( iItems[aItem]->iRect );
    
    // Use offset to move items smoothly.
    // If physics not in use, offset is always 0.
    rect.Move( TPoint( 0, -Offset() ) ); 

    if ( aHighlight == EDrawHighlight )
        {
        TBool drawOk = EFalse; 
        if( iExtension->iAnimation ) // Draw animated highlight
            {
            drawOk = iExtension->iAnimation->Render( aGc, rect );
            }
        if ( !drawOk )
            {
            // Animated highlight was not available, use normal skinned
            // rendering.
            TAknLayoutRect listRect; 
            TAknLayoutRect innerRect;

            listRect.LayoutRect( rect, 
                AknLayoutScalable_Avkon::list_highlight_pane_cp1().LayoutLine() );
            innerRect.LayoutRect( listRect.Rect(),
                AknLayoutScalable_Avkon::list_highlight_pane_g1_cp1().LayoutLine() );
            
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            aGc.SetBrushStyle( CGraphicsContext::ESolidBrush ); 
            // if we have transparent highlight, draw also background under highlight
            if ( Background() )
                {
                Background()->Draw( aGc, *this, rect );
                }
            
            drawOk = AknsDrawUtils::DrawFrame( skin, aGc, rect, innerRect.Rect(), 
                KAknsIIDQsnFrList, KAknsIIDDefault );

            //Both highlight animation and frame drawing failed. 
            if ( !drawOk )
                {
                listRect.DrawRect( aGc ); 
                innerRect.DrawRect( aGc ); 
                }
            }
        }

    if ( aHighlight == ERemoveHighlight && Background() )
        {
        Background()->Draw( aGc, *this, rect );
        }

    TAknLayoutText layoutText; 
    layoutText.LayoutText( rect, 
        AknLayoutScalable_Avkon::list_single_touch_menu_pane_t1().LayoutLine()); 

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TRgb textColor(layoutText.Color()); 
    AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG20 );

    layoutText.DrawText( aGc, *(iItems[aItem]->iText), ETrue, textColor ); 
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::StartAnimation
// -----------------------------------------------------------------------------
//
TInt CAknStylusPopUpMenuContent::StartAnimation()
    {
    if( iExtension )
        {
        // Creates animation only if it does not exist
        return iExtension->CreateAnimation();
        }
    return KErrNotSupported; 
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::UpdateScrollBar
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::UpdateScrollBar()
    {
    if ( !iSBFrame )
        {
        return;
        }
            
    TAknWindowLineLayout listLayout = 
    AknLayoutScalable_Avkon::list_single_touch_menu_pane(0).LayoutLine();

    TInt singleItemHeight = listLayout.iH; 
    TRect listRect = Rect(); 
    
    TInt fitsToMenu = listRect.Height() / singleItemHeight;
    TInt visibleItems = 0;
    TInt thumbPos = 0;
    
    // Count visible items
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->iVisibility == KShown )
            {
            visibleItems++;
            }
        if ( i == iFirstItem )
                {
                thumbPos = visibleItems-1;
                }
        }

    if ( fitsToMenu == 0 || visibleItems == 0 )
        {
        return;
        }
        
    if ( visibleItems > fitsToMenu )
        {
        TRAP_IGNORE( iSBFrame->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EOn ) );
        }
    else
        {
        TRAP_IGNORE( iSBFrame->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EOff ) );
        return;
        }
        
    TAknDoubleSpanScrollBarModel vsbarModel;
    TAknDoubleSpanScrollBarModel hsbarModel;
    
    if ( iSBFrame->VScrollBarVisibility() != CEikScrollBarFrame::EOff )
        {
        vsbarModel.iThumbPosition = thumbPos * singleItemHeight + Offset();
        vsbarModel.iScrollSpan = visibleItems * singleItemHeight;
        vsbarModel.iThumbSpan = fitsToMenu * singleItemHeight;
            
        TEikScrollBarFrameLayout layout;
        layout.iTilingMode=TEikScrollBarFrameLayout::EInclusiveRectConstant;
        layout.SetClientMargin(0);
        layout.SetInclusiveMargin(0);
        
        TBool changed ( EFalse );
        TRect clientRect( listRect );
        TRect inclusiveRect( listRect );
        TRAP_IGNORE ( changed = iSBFrame->TileL( &hsbarModel, 
                                                 &vsbarModel,
                                                 clientRect, 
                                                 inclusiveRect, 
                                                 layout ) );
        if ( changed )
            {
            iSBFrame->DrawScrollBarsDeferred();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::CalculateShownItems
// -----------------------------------------------------------------------------
//   
TInt CAknStylusPopUpMenuContent::CalculateShownItems(  TScrollType aScroll )
    {
    TInt visibleItems ( 0 );
    TInt shownItems ( 0 );
    TInt firstItem ( KNoItemSelected );
    TInt lastItem ( 0 );
    TRect listRect = Rect();

    //
    // Empty listRect causes infinite loop in this
    // function. (while ( lastItem == 0 || visibleItems < shownItems ))
    //
    // listRect can be empty if the popup menu is created
    // from resource and RemoveMenuItem is called before
    // making the popup menu visible.
    //
    TAknWindowLineLayout listLayout = 
    AknLayoutScalable_Avkon::list_single_touch_menu_pane(0).LayoutLine();

    TInt singleItemHeight = listLayout.iH; 
    TInt fitsToMenu = listRect.Height() / singleItemHeight;

    if ( iItems.Count() == 0 || listRect.IsEmpty() || fitsToMenu <= 0 )
        {
        return KNoItemSelected;
        }
   
    // Count visible items and calculate first and last shown item
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->iVisibility == KShown )
            {
            if ( firstItem == KNoItemSelected )
                {
                firstItem = i;
                }
            visibleItems++;
            if ( i >= iFirstItem )
                {
                shownItems++;
                if ( shownItems == fitsToMenu )
                    {
                    lastItem = i;
                    }
                }
            }
        }

    if ( visibleItems == 0 )
        {
        return KNoItemSelected;
        }
    
    // Scrolling fixes to iFirstItem
    if ( aScroll == EScrollUp && 
         iItems[iFirstItem]->iVisibility == KHidden )
        {
        while ( iItems[iFirstItem]->iVisibility == KHidden && 
                iFirstItem > 0 )
            {
            iFirstItem--;
            }
        }

    if ( aScroll == EScrollDown && 
         iItems[iFirstItem]->iVisibility == KHidden )
        {
        while ( iItems[iFirstItem]->iVisibility == KHidden &&
                iFirstItem < iItems.Count() - 1 )
            {
            iFirstItem++;
            }
        }
        
    // Is scroll bar needed
    if ( visibleItems > fitsToMenu )
        {
        if ( !iSBFrame )
            {
            TRAPD( err, iSBFrame =  new ( ELeave ) CEikScrollBarFrame( 
                    this, this, EFalse, ETrue ) );

            if ( !err )
                {
                TRAPD( err, iSBFrame->CreateDoubleSpanScrollBarsL( 
                    EFalse, EFalse, ETrue, EFalse ) );

                if ( !err )
                    {
                    iSBFrame->DrawBackground( EFalse, EFalse );
                    if ( AknLayoutUtils::LayoutMirrored() )
        	            {
                        listRect.iTl.iX += AknLayoutScalable_Avkon::scroll_pane().LayoutLine().iW;
        	            }
                    else
        	            {
                        listRect.iBr.iX -= AknLayoutScalable_Avkon::scroll_pane().LayoutLine().iW;
                        }
                    }
                }
            }

        }
    
    // Adjust first and last item 
    if ( iFirstItem < firstItem )
        {
        iFirstItem = firstItem;
        }
    
    if ( lastItem == 0 && ( visibleItems == 1 || fitsToMenu == 1 ) )
        {
        iFirstItem = firstItem;
        lastItem = iFirstItem;
        }
    else
        {
        while ( lastItem == 0 || visibleItems < shownItems )
            {
            if ( iFirstItem > 0 )
                {
                iFirstItem--;    
                }
            shownItems = 0;
            // Count new last item
            for ( TInt i = iFirstItem; i < iItems.Count(); i++ )
                {
                if ( iItems[i]->iVisibility == KShown )
                    {
                    shownItems++;
                    if ( shownItems <= fitsToMenu  )
                        {
                        lastItem = i;
                        }
                    }
                }
            }
        }

    // add one item because to take partial items into account
    ++lastItem;
    
    // Position items starting from the topmost item
    for ( TInt i = 0; i < iItems.Count(); i ++ )
        {
        TRect itemRect;
        if ( iItems[i]->iVisibility == KShown 
             && ( i >= iFirstItem && i <= lastItem ) )
            {
            itemRect.SetRect ( listRect.iTl, 
                               TSize( listRect.Width(), 
                               singleItemHeight ) );
            listRect.iTl.iY += singleItemHeight;
            }
         else
            {
            itemRect.SetRect( TPoint( 0,0 ), TPoint( 0,0 ) );
            }
        iItems[i]->iRect = itemRect;
        }

    return lastItem;    
    }

// ---------------------------------------------------------------------------
// From class CCoeControl
// CAknStylusPopUpMenuContent::SizeChanged
// ---------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::SizeChanged()
    {
    TAknWindowLineLayout listLayout = 
        AknLayoutScalable_Avkon::list_single_touch_menu_pane(0).LayoutLine();

    iPhysicsHandler->SetItemHeight( listLayout.iH );
    iPhysicsHandler->SetWorldHeight( WorldHeight() );
    iPhysicsHandler->SetViewRect( Rect() );

    TRAP_IGNORE( InitPhysicsL() );
        
    if ( CalculateShownItems( ENoScroll ) != KNoItemSelected )
        {
        UpdateScrollBar();
        DrawNow();
        }
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::Draw
// Draw a control called by window server.
// -----------------------------------------------------------------------------
//    
void CAknStylusPopUpMenuContent::Draw( const TRect& /*aRect*/ ) const
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CWindowGc& gc = SystemGc();

        for ( TInt i=iFirstItem; i < iItems.Count(); i++ )
            {
            if ( iItems[i]->iVisibility != KHidden )
                {
                DrawItem( gc, i, ( i == iCurrentItem ) ? EDrawHighlight : 
                    ENoHighlight );
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::ListRectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknStylusPopUpMenuContent::ListRectFromLayout( const TRect& aParent,
        const TAknWindowLineLayout& aLineLayout ) const
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aLineLayout );

    TAknWindowLineLayout listLayout =             
        AknLayoutScalable_Avkon::list_touch_menu_pane().LayoutLine();

    TAknLayoutRect listRect; 
    listRect.LayoutRect( layoutRect.Rect(), listLayout ); 

    return listRect.Rect();
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknStylusPopUpMenuContent::RectFromLayout( const TRect& aParent,
        const TAknWindowLineLayout& aLineLayout ) const
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aLineLayout );
    return layoutRect.Rect();
    }

// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::HandleScrollEventL
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::HandleScrollEventL(
        CEikScrollBar* aScrollBar,
        TEikScrollEvent /*aEventType*/ )
    {
    iPhysicsHandler->HandleScrollEvent( aScrollBar->ThumbPosition() );
    }
    
// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::HandleGainingForeground
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::HandleGainingForeground()
    {
    
    }
    
// -----------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::HandleLosingForeground
// -----------------------------------------------------------------------------
//
void CAknStylusPopUpMenuContent::HandleLosingForeground()
    {
    if ( Observer() )
        {
        // this will close the stylus popup menu
        TRAP_IGNORE( Observer()->HandleControlEventL( this,
            MCoeControlObserver::EEventRequestExit ) );
        }
    }


// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CAknStylusPopUpMenuContent::InitPhysicsL()
    {
    if ( iPhysicsHandler )
        {
        iPhysicsHandler->InitPhysicsL();
        }
    }
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::Offset
// ---------------------------------------------------------------------------
//     
TInt CAknStylusPopUpMenuContent::Offset() const
    {
    return iPhysicsHandler->Offset();
    }
    
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::WorldHeight
// ---------------------------------------------------------------------------
//    
TInt CAknStylusPopUpMenuContent::WorldHeight() const
    {
    TInt visibleItems = 0;
    
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->iVisibility == KShown )
            {
            visibleItems++;
            }
        }
    if ( visibleItems == 0 )
        {
        return 0;
        }
            
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                       mainPaneRect );
    TAknWindowLineLayout listLayout = 
       AknLayoutScalable_Avkon::list_single_touch_menu_pane(0).LayoutLine();
 
    TAknTextLineLayout textLayout = 
       AknLayoutScalable_Avkon::list_single_touch_menu_pane_t1().LayoutLine();

    TAknWindowLineLayout unit = 
       AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine();
    
    TInt singleItemHeight = listLayout.iH; 
    TInt height = singleItemHeight * visibleItems;
    return height;
    }
    
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::UpdateView
// ---------------------------------------------------------------------------
//     
void CAknStylusPopUpMenuContent::UpdateView( TInt aTopItem )
    {        
    TInt visibleItems = 0;
    
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->iVisibility == KShown )
            {
            if ( visibleItems == aTopItem )
                {
                iFirstItem = i;
                break;
                }
            visibleItems ++;
            }
        }
    SizeChanged();    
    }
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::ContainingItem
// ---------------------------------------------------------------------------
//   
TInt CAknStylusPopUpMenuContent::ContainingItem( const TPoint& aPosition )
    { 
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        CAknStylusPopUpMenuItem* item = iItems[i];
        if ( item->iRect.Contains( aPosition ) && item->iVisibility != KHidden )
            {
            return i;
            }
        }
    return KNoItemSelected;    
    }
    

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::SetHighlight
// ---------------------------------------------------------------------------
//   
void CAknStylusPopUpMenuContent::SetHighlight( TInt aItem )
    {
    iCurrentItem = aItem;
    DrawDeferred();
    }
    
// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::CurrentItem
// ---------------------------------------------------------------------------
//   
TInt CAknStylusPopUpMenuContent::CurrentItem() const
    {
    return iCurrentItem;
    }

// ---------------------------------------------------------------------------
// CAknStylusPopUpMenuContent::SelectItem
// ---------------------------------------------------------------------------
//     
void CAknStylusPopUpMenuContent::SelectItem( TInt aItem )
    {
    iCurrentItem = aItem;
    if ( Observer() )
        {
        if ( iExtension )
            {
            iExtension->iInformObserver = EFalse; 
            iExtension->iObserverInformed = ETrue; 
            }
        TRAP_IGNORE(Observer()->HandleControlEventL( this,
            MCoeControlObserver::EEventStateChanged ));
        }
    }
    
