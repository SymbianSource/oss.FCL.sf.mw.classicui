/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of EIKON Menu Pane class (options menu).
*
*/

// INCLUDE FILES

#include <eikmenup.h>
#include <eikmenub.h>
#include <eikmobs.h>
#include <eikon.hrh>
#include <eikpanic.h>
#include <coemain.h>
#include <basched.h>
#include <barsread.h>
#include <eikhkeyt.h>
#include <eikbutb.h>
#include <eikenv.h>
#include <eikcoctl.rsg>
#include <gulcolor.h>
#include <gulutil.h>
#include <eikappui.h>
#include <eiksbfrm.h>
#include <eikscrlb.h>
#include <gulicon.h>
#include <aknborders.h>     // AKNLAF
#include <aknenv.h>
#include <AknUtils.h>
#include <aknpopuplayout.h>
#include <bidi.h>  // Bidirectional support
#include <bidivisual.h>
#include <aknconsts.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknBidiTextUtils.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknLayoutFont.h>

#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <aknappui.h>

#include <layoutmetadata.cdl.h>
#include <AknStatuspaneUtils.h>
#include <aknCharMap.h>
#include <gfxtranseffect/gfxtranseffect.h> //For transition effects
#include <akntranseffect.h> //For transition effects
#include <akntransitionutils.h> // SetAllParents method
#include <featmgr.h>
#include <avkondomainpskeys.h>
#include <e32property.h>

#include <touchfeedback.h>
#include <AknTasHook.h>
#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include <AknPriv.hrh>
#include "aknitemactionmenudata.h"
#include "akntrace.h"

// CONSTANTS
const TInt KItemGranularity = 4;
const TInt KAlternativeSubmenuWidths = 5; // five alternative widths for submenus depending on max text width
const TInt KNoSelectedRadioButtonItem = -1;

// Delay before opening sub menu when dragging, 0.3s
const TInt KCascadeMenuOpenDelay = 300000;

class CRedirectionListener;

// -----------------------------------------------------------------------------
// TaskSwapCallBack
// -----------------------------------------------------------------------------
//
TInt TaskSwapCallBack( TAny* )
    {
    CEikonEnv::Static()->DisplayTaskList();
    return EFalse;
    }

// =============================================================================
// Extension class declaration & definition
// =============================================================================
/*
 * CEikMenuPaneExtension
 *
 * Structure containing extra local private data members.
 * Created to preserve BC.  The CEikMenuPane class contains a pointer to this structure
 * CEikmenuPane is responsible for data members of this class.
 *
 * Extension now contains menu/submenu highlight animation functionality.
 */
NONSHARABLE_CLASS( CEikMenuPaneExtension ):
    public CBase,
    public MCoeControlObserver,
    public MAknPhysicsObserver    
    {
public:
    CEikMenuPaneExtension();
    ~CEikMenuPaneExtension();

    void ConstructL( CEikMenuPane* aControl );
    void MenuClosed();

    void ConstructMenuSctRowL( TDes& aSpecialChars, TInt aResourceId );
    void ConstructMenuSctRowFromDialogL( TDes& aSpecialChars, TInt aResourceId );
    
    void StartCascadeMenuTimerL();
    void StopCascadeMenuTimer();
    static TInt CascadeMenuTimerCallBack( TAny* aThis );
    TBool IsCascadeMenuTimerActive();
    
    void StartHighlightTimerL();
    void ResetPressedHighlight();
    static TInt HighlightTimerCallBack( TAny* aThis );
    TBool HighlightTimerActive() const;
    
    void ChangePosition( TPointerEvent& aPointerEvent );
    void CalculateParentEvent( const TPointerEvent& aPointerEvent, 
                               TPointerEvent& aParentEvent );
    void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public:
    void ImmediateFeedback( TTouchLogicalFeedback aType,
                            TTouchFeedbackType aFbType );
    
public:
    void StartCascadeMenuAppearTransition();

    /**
     * Prepares cascade menu for item specific commands.
     */
    void PrepareCascadeForItemCommands();

    /**
     * Returns ETrue if this menu pane belongs to a CS menu.
     * 
     * @return ETrue if this menu pane belongs to a CS menu.
     */
    TBool ContextSensitiveMenu() const;

    /**
     * Returns ETrue if item is item specific command and the command is not
     * dimmed.
     * 
     * @param aItem Menu pane item.
     * @return ETrue if item is item specific command.
     */
    static TBool ItemSpecificCommand( CEikMenuPaneItem& aItem );

    /**
     * Enables or disables highlight
     * 
     * @param aEnabled ETrue to enable highlight, EFalse to disable.
     * @param aPointerEnabled ETrue if highlight was enabled due
     * to a pointer event.
     */
    void EnableHighlight( TBool aEnabled, TBool aPointerEnabled = EFalse );

    /**
     * Is highlight enabled
     * 
     * @return ETrue if highlight is enabled
     */
    TBool HighlightEnabled();

    /**
     * Sets the default highlight to options menu
     * 
     */    
    void SetDefaultHighlight();
    
public: // Data
    CFbsBitmap* iCascadeBitmap;
    CFbsBitmap* iCascadeBitmapMask;
    CAknsFrameBackgroundControlContext* iBgContext;
    TInt        iSubMenuWidthIndex;       // index for submenu layout which depends on the text length
    CFbsBitmap* iCheckMarkBitmap;         // bitmap to be drawn if the item has check box set on
    CFbsBitmap* iCheckMarkBitmapMask;     // mask for the above bitmap
    CFbsBitmap* iRadioButtonBitmap;       // bitmap to be drawn if the item has radio button set on
    CFbsBitmap* iRadioButtonBitmapMask;   // mask for the above bitmap
    TBool       iHasRadioGroup;           // is ETrue if submenu contains radio button group.
    TInt        iSelectedRadioButtonItem; // index of the radio button item which is currently selected (one must be selected)
    CEikMenuPane* iControl;
    CAknCharMap* iSct;      // Menu SCT row, created only when needed.
    TBool iSctHighlighted;  // No "normal" menu item can be highlighted if ETrue

    // Pen event related flag indicating whether the (sub)menu pane has
    // already consumed EButton1Down or not. If false,
    // EButton1Up will do nothing.
    TBool iItemsReadyForPenSelection;
    TBool iSpecialCharPointed;
    // transition demarcation rectangle for cascaded submenu
    // needs to be mutable since we need to get information from Draw methods
    // (that are declared const)
    mutable TRect iCascadeDRect;
    TBool iShowCascadeTransition;
    // For later deletion of cascade menu, this allows the transition system
    // to correctly handle the aborted transitions
    CEikMenuPane* iCascadeMenuObject;
    TBool iDraggedOutside;    
    TPointerEvent iLastPointerEvent;
    TInt iItemsThatFitInView;
    TRect iScrollBarRect;
    TRect iSctRect;
    CIdle* iTaskSwapIdle;
    CRedirectionListener* iRedirectionListener;
    RWindow* iMenuPaneWindow; // Not own, used by SCT
    TBool iLaunchCascadeMenu; 
    TBool isUpdateScrollDirectly;
    TBool iPressedDown;      // ETrue if pointer is down, otherwise.

    CEikCba* iCba; // Embedded cba
    TRect iMenuPaneRect; // Menu area of options menu
    TBool iDownOnMenuArea; // Down event received inside menu area
    TBool iDownOnCbaArea; // Down event received inside embedded CBA area
    
    /**
     * Menu pane extension flags definition.
     */
    enum TCEikMenuPaneExtensionFlags
        {
        ESingleClickEnabled,
        EHideItemSpecificCommands,
        EContextSensitive,
        ESkipScrollbarUpdate,
        EHighlightEnabled
        };

    /**
     * Menu pane extension flags.
     */
    TBitFlags iFlags;
    
    /**
     * Cached rectangle occupied by menu items (excluding scrollbar's area).
     */
    TRect iItemAreaRect;
    
    /**
     * Cached rectangle occupied by menu items and scrollbar.
     */
    TRect iMenuAreaRect;
    
    /**
     * Index of the item were highlight was previously drawn to.
     * Can be KErrNotFound.
     */
    TInt iHighlightedItem;
    
    /**
     * Scrollbar's desired visibility. This is calculated in conjunction with
     * menu pane's size and used later on when calculating scrollbar's layout.
     */
    CEikScrollBarFrame::TScrollBarVisibility iScrollbarVisibility;

private: // Data
    CPeriodic* iTimer; // timer to launch submenu, own
    CPeriodic* iHighlightTimer; // Timer to adjust pressed down highlight
    TInt iVerticalOffset; // Panning offset

public: // MAknPhysicsObserver
    virtual void ViewPositionChanged( const TPoint& aNewPosition,
                                      TBool aDrawNow = ETrue,
                                      TUint aFlags = 0 );
    virtual void PhysicEmulationEnded();    
    virtual TPoint ViewPosition() const;
    
public:    
    void InitPhysicsL();
    void DoOffset( TInt aOffset );
    void RestoreOffset( TInt aKeyCode );
    void SetOffset( TInt aOffset );
    inline TInt Offset() const { return iVerticalOffset; };
    
    CAknPhysics *iPhysics; 
    TPoint iViewPosition; // Current view position
 
    TInt iListTopIndex;
    TInt iListBottomIndex;
    
    TInt iViewHeight;
    TBool iFlickActive;
    TBool iPanningActive;
    TBool iKeyEventActive;
    
    // For dragging
    TPoint iStartPoint;
    TTime iStartTime;
    TPoint iPrevPoint;
    
    // For highlight
    TInt iButtonDownItem; // Item on which down event came
    TInt iNextHighlightItem; // Item waiting for highlight timer
    // When doing a full redraw drawitem should not
    // draw the background because draw has already
    // drawn it.
    TBool iFullRedraw;
    MTouchFeedback* iFeedback;
    // The top item index is stored to this member and used for controlling
    // tactile feedback when panning/flicking (feedback is only given when
    // new item comes into view, i.e. when the top item index changes)
    TInt iLastFeedbackTopItemIndex;
    };

//
// CEikMenuPane::CMenuScroller
//

class CEikMenuPane::CMenuScroller : public CBase, public MEikScrollBarObserver
    {
private:    
    friend class CEikMenuPaneExtension;
public:
    static CMenuScroller* NewL( CEikMenuPane& aMenu );
    ~CMenuScroller();

    inline TInt TopItemIndex() const;
    inline void SetTopItemIndex( TInt aIndex );
    inline CIdle* Idle() const;
public: // from MEikScrollBarObserver
    void HandleScrollEventL( CEikScrollBar* aScrollBar, TEikScrollEvent aEventType );
private:
    CMenuScroller( CEikMenuPane& aMenu );
    void ConstructL();
private:
    CEikMenuPane& iMenuPane;
    TInt iTopItemIndex;
    CIdle* iIdle;
    };

// -----------------------------------------------------------------------------
// CEikMenuPane::CMenuScroller::NewL
// -----------------------------------------------------------------------------
//
CEikMenuPane::CMenuScroller* CEikMenuPane::CMenuScroller::NewL( CEikMenuPane& aMenuPane )
    { // static
    CMenuScroller* self = new(ELeave)CMenuScroller( aMenuPane );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CMenuScroller::~CMenuScroller
// -----------------------------------------------------------------------------
//
CEikMenuPane::CMenuScroller::~CMenuScroller()
    {
    delete iIdle;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CMenuScroller::CMenuScroller
// -----------------------------------------------------------------------------
//
CEikMenuPane::CMenuScroller::CMenuScroller( CEikMenuPane& aMenuPane )
    : iMenuPane( aMenuPane ), iTopItemIndex( 0 )
    {}

// -----------------------------------------------------------------------------
// CEikMenuPane::CMenuScroller::ConstructL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CMenuScroller::ConstructL()
    {
    iIdle = CIdle::NewL( CActive::EPriorityIdle );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CMenuScroller::HandleScrollEventL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CMenuScroller::HandleScrollEventL( CEikScrollBar* aScrollBar,
                                                     TEikScrollEvent aEventType )
    {
    iMenuPane.HandleScrollEventL( aScrollBar, aEventType );
    }

inline TInt CEikMenuPane::CMenuScroller::TopItemIndex() const
    { return iTopItemIndex; }

inline void CEikMenuPane::CMenuScroller::SetTopItemIndex(TInt aIndex)
    { 
    iTopItemIndex=aIndex;
    }

inline CIdle* CEikMenuPane::CMenuScroller::Idle() const
    { return iIdle; }


void CEikMenuPaneExtension::InitPhysicsL()
    {
    _AKNTRACE_FUNC_ENTER;
           
    iVerticalOffset = 0;
    iListTopIndex = 0;
    iLastFeedbackTopItemIndex = 0;
    iPressedDown = EFalse;
    iFlickActive = EFalse;

    TRect rect( iMenuPaneRect );
    
    TInt itemHeight = iControl->iItemHeight;
    TInt itemsInRect = rect.Height() / itemHeight;
    TInt totalItemHeight = iControl->TotalItemHeight();

    iViewHeight = itemsInRect * itemHeight;
    
    TSize totalSize( rect.Width(), totalItemHeight );
    TSize viewSize( rect.Width(), iViewHeight );
    
    // Using main menu width also for submenu(s), this
    // enables consistent scroll physics between main
    // menu and submenus 
    if ( iControl->iOwner )
        {       
        CEikMenuPane* menu = iControl->iOwner;
            
        // Go through sub menu hierarchy. There might be
        // multiple submenus, although default case is 
        // only one submenu.
        while ( menu->iOwner )
            {
            CEikMenuPane* prevMenu( menu );
            menu = menu->iOwner;

            // This prevents infinite loop if iOwner is equal to menu.
            if ( menu == prevMenu )
                {
                break;
                }
            }
                            
        totalSize = TSize( menu->Rect().Width(), totalItemHeight );
        viewSize = TSize( menu->Rect().Width(), iViewHeight );      
        }
    
    iPhysics->InitPhysicsL( totalSize, viewSize, EFalse );
                                                            
    iViewPosition = TPoint( rect.Width() / 2, iListTopIndex + iViewHeight / 2 );
    _AKNTRACE( "totalSize(%d, %d)", totalSize.iWidth, totalSize.iHeight );
    _AKNTRACE( "viewSize(%d, %d)", viewSize.iWidth, viewSize.iHeight );
    _AKNTRACE( "iViewPosition(%d, %d)", iViewPosition.iX, iViewPosition.iY );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Physics emulation has moved the view.
// ---------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ViewPositionChanged( const TPoint& aNewPosition,
                                                 TBool aDrawNow,
                                                 TUint /*aFlags*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    TInt delta = iViewPosition.iY - aNewPosition.iY;

    if ( !iControl->iItemArray || delta == 0 )
        {
        return;
        }

    iListTopIndex = aNewPosition.iY - iViewHeight / 2;  
    iListBottomIndex = aNewPosition.iY + iViewHeight - iViewHeight / 2;
    
    DoOffset( delta );

    iViewPosition = aNewPosition; 
    _AKNTRACE( "iListTopIndex = %d",  iListTopIndex );
    _AKNTRACE( "iListBottomIndex = %d",  iListBottomIndex );
    _AKNTRACE( "delta = %d",  delta );
    _AKNTRACE( "iViewPosition(%d,%d)",  iViewPosition.iX, iViewPosition.iY );
    
    if ( aDrawNow )
        {
        if ( iFlags.IsClear( ESkipScrollbarUpdate ) )
            {
            TRAP_IGNORE( iControl->DoUpdateScrollBarL() );
            }

        // Redraw only item area if scrollbar is invisible, otherwise include 
        // also scrollbar's area in order to avoid drawdeferred.
        TRect drawRect( iItemAreaRect );
        
        if ( iScrollbarVisibility == CEikScrollBarFrame::EOn )
            {
            drawRect = iMenuAreaRect;
            }

        iControl->DrawNow( drawRect );
        }
    _AKNTRACE_FUNC_EXIT;
    }


void CEikMenuPaneExtension::DoOffset( TInt aOffset )
    {                                      
    _AKNTRACE_FUNC_ENTER;
    TInt itemsInRect = iControl->NumberOfItemsThatFitInView();
    TInt bottomListPosition = 0;
    
    if(iControl->iItemArray->Count() > itemsInRect)
        {
        bottomListPosition = (iControl->iItemArray->Count() - itemsInRect) * iControl->iItemHeight;
        }
    
    TInt itemIndex = iListTopIndex;
    
    if ( iListTopIndex <= 0 )
        {
        itemIndex = 0;                                
        } 
        
    else if ( iListTopIndex >= bottomListPosition )
        {
        itemIndex = bottomListPosition; 
        }           
    
    // Calculate new top item index                                                
    TInt newTopItemIndex = itemIndex / iControl->iItemHeight;
     
    // Calculate panning offset
    SetOffset( newTopItemIndex * iControl->iItemHeight - iListTopIndex );
     
    _AKNTRACE( " iVerticalOffset = %d",  iVerticalOffset );
    if ( newTopItemIndex >= 0 && newTopItemIndex < iControl->iItemArray->Count() )
        {
        _AKNTRACE( "%s", "iControl->iScroller->SetTopItemIndex(newTopItemIndex);" );
        iControl->iScroller->SetTopItemIndex(newTopItemIndex);
        }
    // calculate new top item index and offset
    TInt menuTopItemIndex = iListTopIndex/iControl->iItemHeight;
    
    TInt listBottomLimit = iControl->iItemArray->Count()* iControl->iItemHeight;
    
    if ( menuTopItemIndex > iControl->iItemArray->Count() )
    	{
    	menuTopItemIndex = iControl->iItemArray->Count() - 1;
    	}
    
    if ( menuTopItemIndex != iLastFeedbackTopItemIndex )
        {   
        iLastFeedbackTopItemIndex = menuTopItemIndex;
        // If the top list item index has changed, that means that there's
        // a new list item in view and thus feedback needs to be given
        // in case there's flicking or panning ongoing and not doing
        // bounce action
        if ( iFlickActive || iPanningActive )
            {
            if ( ( aOffset>0 && iListTopIndex <= listBottomLimit && iListTopIndex >= -iViewHeight ) ||
            	  ( aOffset<0 && iListBottomIndex >= 0 && iListBottomIndex <= listBottomLimit+iViewHeight ) ) 
            	{
            	if ( iPhysics )
                    {
                    TTouchFeedbackType feedbackType = ETouchFeedbackVibra;
                    switch( iPhysics->OngoingPhysicsAction() )
                        {
                        case CAknPhysics::EAknPhysicsActionDragging:
                            {
                            feedbackType = static_cast<TTouchFeedbackType> ( ETouchFeedbackVibra | ETouchFeedbackAudio );
                            }
                        case CAknPhysics::EAknPhysicsActionFlicking:
                        case CAknPhysics::EAknPhysicsActionBouncing:
                            {
                            ImmediateFeedback( ETouchFeedbackSensitiveList,
                                               feedbackType );
                            break;
                            }
                        default:
                            break;
                        }
                    }
            	}
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CEikMenuPaneExtension::RestoreOffset( TInt aKeyCode )
    {    
    if ( aKeyCode == 0 )
        {
        return;
        }
    _AKNTRACE_FUNC_ENTER;    
    TPoint oldViewPos = iViewPosition;
    
    TInt itemsInRect = iControl->NumberOfItemsThatFitInView();
    TInt topItem = iControl->iScroller->TopItemIndex();
    TInt bottomItem = topItem + itemsInRect;
    TInt highLightItem = iControl->iSelectedItem;    
           
    // There is partially visible items in menu. Offset is restored here if highlight 
    // is moved to partially visible item by using hw keys (up/down)     
    if ( ( highLightItem == topItem + 1 || highLightItem == topItem ) 
        && aKeyCode == EKeyUpArrow )
        {   
        iViewPosition.iY += iVerticalOffset;
        }
    //ENothingSelected is for sct row.
    else if ( ( highLightItem == bottomItem - 1 
                || highLightItem == bottomItem
                || highLightItem == CEikMenuPane::ENothingSelected                
              ) && aKeyCode == EKeyDownArrow )
        {
        iViewPosition.iY += iControl->iItemHeight + iVerticalOffset;
        }        
    // Submenu can be opened with left or right key depending on layout 
    // or with selection keys   
    else if ( ( !AknLayoutUtils::LayoutMirrored() && aKeyCode == EKeyRightArrow ) ||
              ( AknLayoutUtils::LayoutMirrored() && aKeyCode == EKeyLeftArrow ) ||
                aKeyCode == EKeyEnter || aKeyCode == EKeyOK || aKeyCode == EAknSoftkeyOk ||
                aKeyCode == EAknSoftkeySelect || aKeyCode == EAknSoftkeyOk )
        {
        if ( highLightItem != CEikMenuPane::ENothingSelected )
            {
            const CEikMenuPaneItem* item = (*iControl->iItemArray)[highLightItem];
            // Check if item has submenu                
            if ( item->iData.iCascadeId )
                {
                // Submenu is going to be opened from partial item, we need
                // to bring it fully visible
                if ( highLightItem == topItem )
                    {   
                    iViewPosition.iY += iVerticalOffset;
                    }
                else if ( highLightItem == bottomItem )
                    {
                    iViewPosition.iY += iControl->iItemHeight + iVerticalOffset;
                    }             
                }             
            }     
        }

    // Avoid redraw if position not changed
    if ( oldViewPos != iViewPosition )
        {
        // Report view position change to scroll physics
        // when sub menu is opened with hw keys.                                            
        _AKNTRACE( "[%s]", " ViewPositionChanged( iViewPosition )" );
        ViewPositionChanged( iViewPosition );
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CEikMenuPaneExtension::SetOffset( TInt aOffset )
    {   
    iVerticalOffset = aOffset;
    _AKNTRACE( "iVerticalOffset = %d", iVerticalOffset );
    }


void CEikMenuPaneExtension::PhysicEmulationEnded()
    {
    _AKNTRACE_FUNC_ENTER;    
    iFlickActive = EFalse; 
    _AKNTRACE_FUNC_EXIT;
    }    
    
TPoint CEikMenuPaneExtension::ViewPosition() const
    {
    _AKNTRACE( "iViewPosition(%d,%d)",  iViewPosition.iX, iViewPosition.iY );
    return iViewPosition;
    }    
//
// =============================================================================
// Helper class that monitor redirection changes declaration & definition
// =============================================================================
/*
 * CRedirectionListener
 *
 * Delays opening of submenus during appear transitions
 */
NONSHARABLE_CLASS( CRedirectionListener ) : public CBase,
                                            public MAknTransitionUtilsObserver
    {
public:
    CRedirectionListener( CEikMenuPaneExtension& aOwner );
    ~CRedirectionListener();

    void AppearTransitionStarting();
    void Closing();
    void LaunchCascadeMenu();
private:
    TInt AknTransitionCallback( TInt aEvent, TInt aState,
                                const TDesC8* /*aParams*/ );
private: // Data
    TBool iObserving;
    TBool iTransitionUpcoming;
    TBool iAppearTransitionRunning;
    TBool iLaunchWhenUnredirected;
    CEikMenuPaneExtension& iOwner;
    };

// -----------------------------------------------------------------------------
// CRedirectionListener::CRedirectionListener
// -----------------------------------------------------------------------------
//
CRedirectionListener::CRedirectionListener( CEikMenuPaneExtension& aOwner ) :
    iOwner( aOwner )
    {
    }

// -----------------------------------------------------------------------------
// CRedirectionListener::~CRedirectionListener
// -----------------------------------------------------------------------------
//
CRedirectionListener::~CRedirectionListener()
    {
    Closing();
    }

// -----------------------------------------------------------------------------
// CRedirectionListener::AppearTransitionStarting
// -----------------------------------------------------------------------------
//
void CRedirectionListener::AppearTransitionStarting()
    {
    TInt err = KErrNone;
    iAppearTransitionRunning = EFalse;
    if ( !iObserving )
        {
        err = CAknTransitionUtils::AddObserver( this,
                            CAknTransitionUtils::EEventWsBufferRedirection );
        }
    // Only set this value if observing
    if ( err == KErrNone )
        {
        iObserving = ETrue;
        iTransitionUpcoming = ETrue;
        }
    }

// -----------------------------------------------------------------------------
// CRedirectionListener::Closing
// -----------------------------------------------------------------------------
//
void CRedirectionListener::Closing()
    {
    if ( iObserving )
        {
        CAknTransitionUtils::RemoveObserver( this,
                            CAknTransitionUtils::EEventWsBufferRedirection );
        iObserving = EFalse;
        }
    iTransitionUpcoming = EFalse;
    iLaunchWhenUnredirected = EFalse;
    }

// -----------------------------------------------------------------------------
// CRedirectionListener::LaunchCascadeMenuL
// -----------------------------------------------------------------------------
//
void CRedirectionListener::LaunchCascadeMenu()
    {
    if ( iTransitionUpcoming && iObserving )
        {
        // Get current redirection status
        TInt redirected;
        TInt err = RProperty::Get( KPSUidAvkonDomain,
                                   KAknTfxServerRedirectionStatus,
                        redirected );
        
        if ( err == KErrNone && redirected )
            {
            // Transition has started
            iAppearTransitionRunning = ETrue;
            }
        }
    
    if ( iAppearTransitionRunning )
        {
        // Lauch submenu when unredireted if currently in transition
        iLaunchWhenUnredirected = ETrue;
        }
    else
        {
        // Launch submenu imediately if not currently in transition
        iOwner.StartCascadeMenuAppearTransition();
        iLaunchWhenUnredirected = EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CRedirectionListener::AknTransitionCallback
// -----------------------------------------------------------------------------
//
TInt CRedirectionListener::AknTransitionCallback( TInt aEvent, TInt aState,
                            const TDesC8* /*aParams*/ )
    {
    if ( aEvent == CAknTransitionUtils::EEventWsBufferRedirection )
        {
        if ( aState)
            {
            // Redirected (transition started)
            // Don't display submenu until unredirected
            iAppearTransitionRunning = iTransitionUpcoming;
            }
        else
            {
            // Unredirected (transition finished)
            iAppearTransitionRunning = EFalse;
            if ( iLaunchWhenUnredirected )
                {
                // Launch submenu waiting to be opened
                iOwner.StartCascadeMenuAppearTransition();
                iLaunchWhenUnredirected = EFalse;
                }
            }
        iTransitionUpcoming = EFalse;
        }
    return 0;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::StartCascadeMenuAppearTransition
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::StartCascadeMenuAppearTransition()
    {
    CEikMenuPane* cascadeMenuPane = iControl->iCascadeMenuPane;
    if ( cascadeMenuPane )
        {
        cascadeMenuPane->SetParent( iControl );
        GfxTransEffect::Begin( cascadeMenuPane, KGfxControlAppearAction );
        cascadeMenuPane->StartDisplayingMenuPane( iControl->iHotKeyTable,
                                                  iControl->Position(),
                                                  NULL,
                                                  0,
                                                  EPopupTargetBottomLeft );

        GfxTransEffect::SetDemarcation( cascadeMenuPane, iCascadeDRect );
        GfxTransEffect::End( cascadeMenuPane );

        // Transfer focus to cascade menu (highlight animations adapt to focus
        // change)
        cascadeMenuPane->SetFocus( ETrue, EDrawNow );
        iControl->SetFocus( EFalse, EDrawNow );
        }
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::CEikMenuPaneExtension
// High CActive priority is well argumented because running the active object
// will result in animation deletion -> results in freeing resources.
// -----------------------------------------------------------------------------
//
CEikMenuPaneExtension::CEikMenuPaneExtension() :
    // Initialise data members to zero
    iCascadeBitmap( NULL ),
    iCascadeBitmapMask( NULL ),
    iBgContext( NULL ),
    iSubMenuWidthIndex( 1 ),
    iCheckMarkBitmap( NULL ),
    iCheckMarkBitmapMask( NULL ),
    iRadioButtonBitmap( NULL ),
    iRadioButtonBitmapMask( NULL ),
    iHasRadioGroup( EFalse ),
    iSelectedRadioButtonItem( KNoSelectedRadioButtonItem ),
    iControl( NULL ),
    iSct( NULL ),
    iSctHighlighted( EFalse ),
    iSpecialCharPointed( EFalse )
    ,iVerticalOffset( 0 )
    ,iPhysics( NULL )
    ,iListTopIndex( 0 )
    ,iViewHeight( 0 )
    ,iFlickActive( EFalse )
    ,iPanningActive( EFalse )
    ,iFeedback( MTouchFeedback::Instance() )
    ,iLastFeedbackTopItemIndex( 0 )
    {
    iItemsReadyForPenSelection = !AknLayoutUtils::PenEnabled();
    iNextHighlightItem = KErrNotFound;
    iHighlightedItem = KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::~CEikMenuPaneExtension
// Destructor for extension class
// -----------------------------------------------------------------------------
//
CEikMenuPaneExtension::~CEikMenuPaneExtension()
    {
    _AKNTRACE_FUNC_ENTER;

    delete iCascadeBitmap;
    iCascadeBitmap = NULL;

    delete iCascadeBitmapMask;
    iCascadeBitmapMask = NULL;

    delete iBgContext;
    iBgContext = NULL;

    delete iCheckMarkBitmap;
    iCheckMarkBitmap = NULL;

    delete iCheckMarkBitmapMask;
    iCheckMarkBitmapMask = NULL;

    delete iRadioButtonBitmap;
    iRadioButtonBitmap = NULL;

    delete iRadioButtonBitmapMask;
    iRadioButtonBitmapMask = NULL;

    iControl = NULL;

    delete iSct;
    iSct = NULL;

    delete iCascadeMenuObject;
    iCascadeMenuObject = NULL;

    delete iTimer;
    iTimer = NULL;
    
    delete iHighlightTimer;
    iHighlightTimer = NULL;

    if ( iTaskSwapIdle )
        {
        if ( iTaskSwapIdle->IsActive() )
            {
            iTaskSwapIdle->Cancel();
            TaskSwapCallBack( NULL );
            }
        delete iTaskSwapIdle;
        }

    delete iRedirectionListener;
    delete iPhysics;
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ConstructL
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ConstructL( CEikMenuPane* aControl )
    {
    ASSERT( aControl );
    iControl = aControl;
    iDraggedOutside = EFalse;
    iLaunchCascadeMenu = EFalse;
    iButtonDownItem = KErrNotFound;
    iTaskSwapIdle = CIdle::NewL( CActive::EPriorityHigh );
    if ( aControl->iOwner == NULL && GfxTransEffect::IsRegistered( aControl ) )
        {
        // Delays submenu opening during appear transitions
        iRedirectionListener = new ( ELeave ) CRedirectionListener( *this );
        }
    if ( static_cast<CAknAppUi*>(
            iControl->ControlEnv()->AppUi() )->IsSingleClickCompatible() )
        {
        iFlags.Set( ESingleClickEnabled );
        }

    if ( !iPhysics )
        {
        iPhysics = CAknPhysics::NewL( *this, iControl );
        }
    
    iBgContext = CAknsFrameBackgroundControlContext::NewL(
        KAknsIIDQsnFrPopup, TRect( 0, 0, 1, 1 ), TRect( 0, 0, 1, 1 ), EFalse );
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::StartCascadeMenuTimerL
// Starts the timer for the sub menu launch. Timer is constructed when used for
// the first time
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::StartCascadeMenuTimerL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iTimer )
        {
        iTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    else if ( iTimer->IsActive() )
        {
        iTimer->Cancel();
        }
    iTimer->Start( KCascadeMenuOpenDelay,
                   KCascadeMenuOpenDelay,
                   TCallBack ( CascadeMenuTimerCallBack, this ) );
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::StopCascadeMenuTimer
// Stops the timer for the sub menu launch
// -----------------------------------------------------------------------------
//    
void CEikMenuPaneExtension::StopCascadeMenuTimer()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iTimer && iTimer->IsActive() )
        {
        iTimer->Cancel();
        }
    iLaunchCascadeMenu = EFalse;
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::CascadeMenuTimerCallBack
// Callback function of the timer for the sub menu launch
// -----------------------------------------------------------------------------
//    
TInt CEikMenuPaneExtension::CascadeMenuTimerCallBack( TAny* aThis )
    {
    _AKNTRACE_FUNC_ENTER;
    CEikMenuPaneExtension* self = 
        reinterpret_cast <CEikMenuPaneExtension*> ( aThis );
    self->iLaunchCascadeMenu = ETrue;
    _AKNTRACE_FUNC_EXIT;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::IsCascadeMenuTimerActive
// Returns ETrue if timer is active 
// -----------------------------------------------------------------------------
//    
TBool CEikMenuPaneExtension::IsCascadeMenuTimerActive()
    {
    if ( !iTimer )
        {
        return EFalse;
        }
    return iTimer->IsActive();
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::StartHighlightTimerL
// Starts the timer for the pressed down highlight activation.
// Timer is constructed when used for the first time
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::StartHighlightTimerL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iHighlightTimer )
        {
        iHighlightTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        if ( !iHighlightTimer )
            {
            return;
            }
        }
    else if ( iHighlightTimer->IsActive() )
        {
        iHighlightTimer->Cancel();
        }
        
    TInt timeout ( 0 );
    if ( iPhysics )
        {
        timeout = iPhysics->HighlightTimeout() * 1000;
        }
    iPressedDown = EFalse;        
    iHighlightTimer->Start( timeout,timeout, 
                   TCallBack ( HighlightTimerCallBack, this ) );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CEikMenuPaneExtension::ResetPressedHighlight
// Stops the timer for the pressed down highlight activation and resets the
// pressed highlight
// ---------------------------------------------------------------------------
//    
void CEikMenuPaneExtension::ResetPressedHighlight()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( HighlightTimerActive() )
        {
        iHighlightTimer->Cancel();
        }

    // if status changed repaint needed    
    if ( iPressedDown )
        {
        iPressedDown = EFalse;
        iControl->RepaintHighlight();    
        }
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::HighlightTimerCallBack
// Callback function of the timer for pressed down highlight
// -----------------------------------------------------------------------------
//    
TInt CEikMenuPaneExtension::HighlightTimerCallBack( TAny* aThis )
    {
    _AKNTRACE_FUNC_ENTER;
    CEikMenuPaneExtension* self = 
        reinterpret_cast <CEikMenuPaneExtension*> ( aThis );
    self->iPressedDown = ETrue;
    if ( self->iControl->SelectedItem() == self->iNextHighlightItem )
        {
        self->iControl->RepaintHighlight();
        }
    else
        {
        if ( self->iNextHighlightItem != KErrNotFound )
            {
            self->iControl->MoveHighlightTo( self->iNextHighlightItem );
            }
        }
    self->iNextHighlightItem = KErrNotFound;
    if ( self->HighlightTimerActive() )
        {
        self->iHighlightTimer->Cancel();
        }
    _AKNTRACE_FUNC_EXIT;
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// Checks if the highlight timer is running.
// ---------------------------------------------------------------------------
//
TBool CEikMenuPaneExtension::HighlightTimerActive() const
    {
    return ( iHighlightTimer && iHighlightTimer->IsActive() );
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ChangePosition
// Position of aPointerEvent should be modified when point in beside scrollbar.
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ChangePosition( TPointerEvent& aPointerEvent )    
    {
    if ( !iControl->iSBFrame )
        {
        return;
        }
    
    TRect scrollBarRect( iControl->iSBFrame->VerticalScrollBar()->Rect() );
    TPoint scrollerTl( scrollBarRect.iTl ); 
    TPoint scrollerBr( scrollBarRect.iBr );
    TRect gapRect;           
    // For layout that left to right
    if ( !AknLayoutUtils::LayoutMirrored() )
        {
        TPoint rectTl( scrollerBr.iX, iControl->Rect().iTl.iY );
        gapRect.SetRect( rectTl, iControl->Rect().iBr );
        }
    // For layout that right to left
    else
        {
        TPoint rectBr( scrollerTl.iX, iControl->Rect().iBr.iY );
        gapRect.SetRect( iControl->Rect().iTl, rectBr );         
        } 
       
    if ( gapRect.Contains( aPointerEvent.iPosition ) )
        {
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            aPointerEvent.iPosition.iX = scrollerBr.iX - 1;
            }
        else
            {
            aPointerEvent.iPosition.iX = scrollerTl.iX;
            }        
        //Modify y coordinate of point in top left/right corner of options menu
        if ( aPointerEvent.iPosition.iY < scrollerTl.iY )
            {
            aPointerEvent.iPosition.iY = scrollerTl.iY;
            }            
        //Modify y coordinate of point in bottom left/right corner of options menu
        if ( aPointerEvent.iPosition.iY > scrollerBr.iY )
            {
            aPointerEvent.iPosition.iY = scrollerBr.iY - 1;
            }
        }       
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::CalculateParentEvent
// Calculate parent event for sub menu.
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::CalculateParentEvent( const TPointerEvent& aPointerEvent, 
                           TPointerEvent& aParentEvent )
    {
    aParentEvent.iModifiers = aPointerEvent.iModifiers;
    TPoint subPos = iControl->Position();
    TPoint ownerPos = iControl->iOwner->Position();
    aParentEvent.iPosition.SetXY (
        aPointerEvent.iPosition.iX + subPos.iX - ownerPos.iX,
        aPointerEvent.iPosition.iY + subPos.iY - ownerPos.iY);
    aParentEvent.iType = aPointerEvent.iType;    
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::MenuClosed
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::MenuClosed()
    {
    _AKNTRACE_FUNC_ENTER;
    delete iSct;
    iSct = NULL;
    iSctHighlighted = EFalse;

    if ( iCba )
        {
        iCba = NULL;
        }
    
    if ( iRedirectionListener )
        {
        iRedirectionListener->Closing();
        }
		
    iFlags.Clear( EHideItemSpecificCommands );
    iFlags.Clear( EContextSensitive );
    iFlags.Clear( EHighlightEnabled );
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ConstructMenuSctRowL
// Creates a special characters row to be used in edit menu.
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ConstructMenuSctRowL( TDes& aSpecialChars, TInt aResourceId )
    {
    _AKNTRACE_FUNC_ENTER;
    TBool renew = EFalse;
    if (iSct)
        {
        delete iSct;
        iSct = NULL;
        renew = ETrue;
        }
    iSct = new(ELeave) CAknCharMap();
    iSct->ConstructMenuSctRowL(aResourceId);
    iSct->SetBuffer( aSpecialChars );
    if ( renew && iMenuPaneWindow && iControl )
        {
        iSct->SetContainerWindowL( *iControl );
        iSct->SetGloballyCapturing( ETrue );
        iSct->SetPointerCapture( ETrue );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ConstructMenuSctRowFromDialogL
// Creates a special characters row to be used in edit menu.
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ConstructMenuSctRowFromDialogL( TDes& aSpecialChars, TInt aResourceId )
    {
    TBool renew = EFalse;
    if (iSct)
        {
        delete iSct;
        iSct = NULL;
        renew = ETrue;
        }
    iSct = new(ELeave) CAknCharMap();
    iSct->ConstructMenuSctRowFromDialogL(aResourceId);
    iSct->SetBuffer( aSpecialChars );
    if ( renew && iMenuPaneWindow && iControl)
        {
        iSct->SetContainerWindowL( *iControl );
        iSct->SetGloballyCapturing( ETrue );
        iSct->SetPointerCapture( ETrue );
        }
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::HandleControlEventL
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent aEventType)
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aEventType == EEventStateChanged )
        {
        // Something has been selected from CharMap
        iSpecialCharPointed = ETrue;
        }
    _AKNTRACE( "aEventType = %d", aEventType );
    _AKNTRACE_FUNC_EXIT;
    }

    
// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ImmediateFeedback
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::ImmediateFeedback(
    TTouchLogicalFeedback aType,
    TTouchFeedbackType aFbType  = TTouchFeedbackType( ETouchFeedbackAudio |
                                                      ETouchFeedbackVibra ))
    {   
    if ( iFeedback )
        {
        iFeedback->InstantFeedback( iControl, aType, aFbType, TPointerEvent() );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::PrepareCascadeForItemCommands
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::PrepareCascadeForItemCommands()
    {
    if ( iFlags.IsSet( ESingleClickEnabled )
            && iControl->iOwner
            && iControl->iOwner->iExtension )
        {
        const TBitFlags& ownerFlags( iControl->iOwner->iExtension->iFlags );
        if ( ownerFlags.IsSet( EContextSensitive ) )
            {
            iFlags.Set( EContextSensitive );
            }
        else if ( ownerFlags.IsSet( EHideItemSpecificCommands ) )
            {
            iControl->SetItemCommandsDimmed();
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ContextSensitiveMenu
// -----------------------------------------------------------------------------
//
TBool CEikMenuPaneExtension::ContextSensitiveMenu() const
    {
    TBool isContextSensitive( EFalse );
    if ( !iControl->iOwner )
        {
        CEikMenuBar* menuBar = static_cast<CEikMenuBar*>( iControl->Parent() );
        if ( menuBar && menuBar->GetMenuType() == CEikMenuBar::EMenuContext )
            {
            isContextSensitive = ETrue;
            }
        }
    return isContextSensitive;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::ItemSpecificCommand
// -----------------------------------------------------------------------------
//
TBool CEikMenuPaneExtension::ItemSpecificCommand( CEikMenuPaneItem& aItem )
    {
    TBool itemSpecific( EFalse );
    if ( ( aItem.iData.iFlags & EEikMenuItemSpecific
            || aItem.iData.iFlags & EEikMenuItemSpecificListQuery )
            && !( aItem.iData.iFlags & EEikMenuItemDimmed ) )
        {
        itemSpecific = ETrue;
        }
    return itemSpecific;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::EnableHighlight
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::EnableHighlight(
        TBool aEnabled, TBool aPointerEnabled )
    {
    TBool wasEnabled( iFlags.IsSet( EHighlightEnabled ) );
    if ( aEnabled )
        {
        iFlags.Set( EHighlightEnabled );
        }
    else 
        {
        iFlags.Clear( EHighlightEnabled );
        }
    if ( !aPointerEnabled
            && iCba
            && ( ( wasEnabled && !aEnabled ) || ( !wasEnabled && aEnabled ) ) )
        {
        iCba->MakeCommandVisible( EAknSoftkeySelect, aEnabled );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::HighlightEnabled
// -----------------------------------------------------------------------------
//
TBool  CEikMenuPaneExtension::HighlightEnabled()
    {
    return iFlags.IsSet( EHighlightEnabled );
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneExtension::SetDefaultHighlight
// -----------------------------------------------------------------------------
//
void CEikMenuPaneExtension::SetDefaultHighlight()
    {
    TInt item( CEikMenuPane::ENothingSelected );
    if ( iSct )
        {
        iSctHighlighted = ETrue;
        }
    else
        {
        item = iControl->iScroller->TopItemIndex();
        // Partial item
        if ( Offset() != 0 )
            {
            item++;
            }
        // Task swapper
        TInt taskSwapper;
        if ( iControl->MenuItemExists( EAknCmdTaskSwapper, taskSwapper ) )
            {
            if ( item == taskSwapper )
                {
                item++;
                }
            }
        }
    iControl->SetSelectedItem( item );
    EnableHighlight( ETrue );
    if ( iControl->IsVisible() )
        {
        iControl->RepaintHighlight();
        }
    }


// =============================================================================
// Implementation of CEikMenuPane
// =============================================================================

//
// CItemArray
//

// -----------------------------------------------------------------------------
// CEikMenuPane::CItemArray::~CItemArray
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPane::CItemArray::~CItemArray()
    {
    ResetAndDestroy();
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CItemArray::CItemArray
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPane::CItemArray::CItemArray()
    : CArrayPtrFlat<CEikMenuPaneItem>( KItemGranularity )
    {
    __DECLARE_NAME(_S( "CEikMenuPane::CItemArray") );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CItemArray::AddItemL
// Adds the menu pane item aMenuItem to the end of the array owned by the menu pane
// and transfers ownership.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::CItemArray::AddItemL( CEikMenuPaneItem* aMenuItem )
    {
    CleanupStack::PushL( aMenuItem );
    AppendL( aMenuItem );
    CleanupStack::Pop();
    }

//
// CExtendedItemData
//

CExtendedItemData::~CExtendedItemData()
    {
    delete iIcon;
    delete iScaleableText;
    }


//
// CEikMenuPaneItem
//

// -----------------------------------------------------------------------------
// CEikMenuPaneItem::CEikMenuPaneItem
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPaneItem::CEikMenuPaneItem()
    {
    CreateExtendedDataBlock();
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneItem::~CEikMenuPaneItem
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPaneItem::~CEikMenuPaneItem()
    {
    delete iExtendedData;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneItem::SetIcon
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::SetIcon( CGulIcon* aIcon )
    {
    if ( iExtendedData )
        {
        if( iExtendedData->iIcon )
            {
            delete iExtendedData->iIcon;
            }

        iExtendedData->iIcon = aIcon;
        }
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneItem::DrawItemIcon
// Draws the icon for the item to the graphics context aGc, in the rectangle aRect allocating a square area with
// sides of size of aBitmapSpaceRequired to contain the icon. Draws the icon in a dimmed style if aDimmed is
// ETrue.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::DrawItemIcon( CWindowGc& aGc,
                                              TRect aRect,
                                              TBool /*aDimmed*/,
                                              TInt /*aBitmapSpaceRequired*/ ) const
    {
    _AKNTRACE_FUNC_ENTER;
    if (iExtendedData && iExtendedData->iIcon)
        {
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        TRect rect( aRect );
        AknIconUtils::SetSize(iExtendedData->iIcon->Bitmap(), rect.Size());

        TInt rectWidth = rect.Width();
        TInt rectHeight = rect.Height();
        TInt iconWidth = iExtendedData->iIcon->Bitmap()->SizeInPixels().iWidth;
        TInt iconHeight = iExtendedData->iIcon->Bitmap()->SizeInPixels().iHeight;

        // If aspect ratio of the image and rect do not match the image
        // is centered.
        if ( rectWidth > iconWidth )
            {
            rect.iTl.iX += TInt( ( rectWidth - iconWidth ) / 2 );
            }
        if ( rectHeight > iconHeight )
            {
            rect.iTl.iY += TInt( ( rectHeight - iconHeight ) / 2 );
            }
        _AKNTRACE( "rectWidth = %d",  rectWidth );
        _AKNTRACE( "rectHeight = %d",  rectHeight );
        _AKNTRACE( "iconWidth = %d",  iconWidth );
        _AKNTRACE( "iconHeight = %d",  iconHeight );
        _AKNTRACE( "rect.iTl.iX = %d",  rect.iTl.iX );
        _AKNTRACE( "rect.iTl.iY = %d",  rect.iTl.iY );

        aGc.BitBltMasked( rect.iTl, iExtendedData->iIcon->Bitmap(),
                          TRect(0, 0, rect.Width(), rect.Height()),
                          iExtendedData->iIcon->Mask(), ETrue);
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPaneItem::CreateIconL
// Constructs a new icon for the item, taking ownership of the picture bitmap
// aBitmap and the mask bitmap aMask unless bitmaps have been set to be owned externally.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::CreateIconL( CFbsBitmap* aBitmap, CFbsBitmap* aMask )
    {
    if ( iExtendedData )
        {
        if( iExtendedData->iIcon )
            {
            delete iExtendedData->iIcon;
            }

        iExtendedData->iIcon = CGulIcon::NewL( aBitmap, aMask );
        }
    }

/**
 *
 */
// -----------------------------------------------------------------------------
// CEikMenuPaneItem::IconBitmap
// Returns a pointer to the picture bitmap of the item icon.
// Does not normally imply transfer of ownership.
// -----------------------------------------------------------------------------
//
EXPORT_C CFbsBitmap* CEikMenuPaneItem::IconBitmap() const
    {
    if ( iExtendedData )
        {
        return iExtendedData->iIcon ? iExtendedData->iIcon->Bitmap() : NULL;
        }

    return NULL;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::IconMask
// Returns a pointer to the mask bitmap of the item icon.
// Does not normally imply transfer of ownership.
// -----------------------------------------------------------------------------
//
EXPORT_C CFbsBitmap* CEikMenuPaneItem::IconMask() const
    {
    if ( iExtendedData )
        {
        return iExtendedData->iIcon ? iExtendedData->iIcon->Mask() : NULL;
        }

    return NULL;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::SetBitmapsOwnedExternally
// Sets the item icon to be owned externally if aOwnedExternally is ETrue.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::SetBitmapsOwnedExternally( TBool aOwnedExternally )
    {
    if ( iExtendedData )
        {
        if( iExtendedData->iIcon )
            {
            iExtendedData->iIcon->SetBitmapsOwnedExternally( aOwnedExternally );
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::SetIconBitmapL
// Sets the picture bitmap for the title icon to aBitmap.
// Transfers ownership unless the bitmaps are owned externally.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::SetIconBitmapL( CFbsBitmap* aBitmap )
    {
    if ( iExtendedData )
        {
        if( !iExtendedData->iIcon )
            {
            iExtendedData->iIcon = CGulIcon::NewL();
            }

        iExtendedData->iIcon->SetBitmap( aBitmap );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::SetIconMaskL
// Sets the mask bitmap for the title icon to aMask.
// Transfers ownership unless the bitmaps are owned externally.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::SetIconMaskL( CFbsBitmap* aMask )
    {
    if ( iExtendedData )
        {
        if( !iExtendedData->iIcon )
            {
            iExtendedData->iIcon = CGulIcon::NewL();
            }

        iExtendedData->iIcon->SetMask( aMask );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::ScaleableText
// Returns scaleable text. If there isn't scaleable text available
// then this method returns iData.iText.
// -----------------------------------------------------------------------------
//
EXPORT_C TPtrC CEikMenuPaneItem::ScaleableText() const
    {
    if ( ( iExtendedData ) && ( iExtendedData->iScaleableText ) )
        {
        return iExtendedData->iScaleableText->Des();
        }

    return iData.iText;
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::SetScaleableTextL
// Sets scaleable text. iData.iText is set to first text version.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPaneItem::SetScaleableTextL( const TDesC& aText )
    {
    if ( iExtendedData )
        {
        if ( iExtendedData->iScaleableText )
            {
            delete iExtendedData->iScaleableText;
            iExtendedData->iScaleableText = NULL;
            }

        iData.iText = GetNominalText( aText );

        if ( IsScaleableText( aText ) )
            {
            iExtendedData->iScaleableText = HBufC::NewL( aText.Length() );
            iExtendedData->iScaleableText->Des().Copy( aText );
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPaneItem::GetNominalText
// -----------------------------------------------------------------------------
//
TPtrC CEikMenuPaneItem::GetNominalText( const TDesC& aText )
    {
    TInt limit = aText.Length();
    TInt border = aText.Locate( TChar( KScaleableTextSeparator ) );
    if ( border != KErrNotFound )
        {
        limit = border;
        }

    limit = ( limit > CEikMenuPaneItem::SData::ENominalTextLength ? CEikMenuPaneItem::SData::ENominalTextLength : limit );

    return aText.Left( limit);
    }



//
// class CEikMenuPane
//

// -----------------------------------------------------------------------------
// CEikMenuPane::~CEikMenuPane
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPane::~CEikMenuPane()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    CloseCascadeMenu();
    if ( !ItemArrayOwnedExternally() )
        {
        delete iItemArray;
        iItemArray  = NULL;
        }
    else
        {
        ResetItemArray();
        }

    if ( iLaunchingButton )
        {
        TPointerEvent event;
        event.iType = TPointerEvent::EButton1Up;
        event.iModifiers = 0;
        event.iPosition = iLaunchingButton->Position();
        TRAP_IGNORE( iLaunchingButton->HandlePointerEventL( event ) );
        iLaunchingButton = NULL; // not owned
        }

    delete iScroller;
    iScroller = NULL;

    delete iSBFrame;
    iSBFrame = NULL;

    iMenuObserver = NULL; // not owned

    iEditMenuObserver = NULL; // not owned

    iOwner = NULL; // not owned

    delete iExtension;
    iExtension = NULL;
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CEikMenuPane
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPane::CEikMenuPane( MEikMenuObserver* aMenuObserver )
    : iMenuObserver( aMenuObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    __ASSERT_DEBUG( iMenuObserver,Panic( EEikPanicNullPointer ) );
    __DECLARE_NAME(_S("CEikMenuPane"));
    iBorder = TGulBorder( AknBorderId::EAknBorderMenuSubmenuPopup ); // AKNLAF
    iAllowPointerUpEvents = EFalse;
    iNumberOfDragEvents = 0;
    MakeVisible( EFalse );
    AKNTASHOOK_ADD( this, "CEikMenuPane" );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructL
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::ConstructL( CEikMenuPane* aOwner, MEikMenuObserver* aEditMenuObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    iOwner = aOwner;
    iEditMenuObserver = aEditMenuObserver;

    CheckCreateScrollerL();
    CheckCreateExtensionL();

    CreateWindowL( iCoeEnv->RootWin() );
    EnableWindowTransparency();
    SetAllowStrayPointers();
    EnableDragEvents();

    iItemHeight = CalculateItemHeight();

    if ( iExtension->iSct )
        {
        RWindow* window = (RWindow*)this->DrawableWindow();
        iExtension->iMenuPaneWindow = window;
        iExtension->iSct->SetContainerWindowL( *this );

        // This is effectively the same as CCoeControl::EnableDragEvents()
        // which is protected.
        window->PointerFilter( EPointerFilterDrag, 0 );
        iExtension->iSct->SetGloballyCapturing( ETrue );
        iExtension->iSct->SetPointerCapture( ETrue );
        iExtension->iSct->SetObserver(iExtension);
        }

    if ( iOwner ) // submenu
        {
        SetPointerCapture( ETrue );
        }

    LoadCascadeBitmapL();
    LoadCheckMarkBitmapL();
    LoadRadioButtonBitmapL();

    // Window may not be created if OOM earlier during construction
    RWindow* window = &Window();
    if( window == NULL )
        User::Leave( KErrNoMemory );
            
    Window().SetOrdinalPosition( 0 );
    Window().SetPointerGrab( ETrue );
    SetGloballyCapturing( ETrue );

    iExtension->iPhysics->UpdateViewWindowControl(); 
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructFromResourceL
// Constructs the menu pane using the resource reader aReader, filling the menu item array with the
// list of menu items provided by the resource file.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::ConstructFromResourceL( TResourceReader& aReader )
    {
    if ( iItemArray && !ItemArrayOwnedExternally() )
        {
        delete iItemArray;
        iItemArray = NULL;
        }
    CreateItemArrayL();

    iItemHeight = CalculateItemHeight();

    CheckCreateScrollerL();
    CheckCreateExtensionL();

    const TInt count=aReader.ReadInt16();
    for ( TInt ii=0; ii<count; ++ii )
        {
        CEikMenuPaneItem* item = new(ELeave) CEikMenuPaneItem();
        CleanupStack::PushL( item );
        item->iData.iCommandId = aReader.ReadInt32();
        item->iData.iCascadeId = aReader.ReadInt32();
        item->iData.iFlags = aReader.ReadInt32();
        TPtrC txtptr = aReader.ReadTPtrC();
        item->SetScaleableTextL( txtptr );
        TPtrC extratxtptr = aReader.ReadTPtrC();
        item->iData.iExtraText = extratxtptr;
        CreateIconFromResourceL( aReader, *item );
        CleanupStack::Pop(); // pop first, since additem pushes again
        iItemArray->AddItemL( item );
        aReader.ReadInt32(); // extension link

        if ( item->iData.iFlags&( EEikMenuItemRadioStart|EEikMenuItemRadioMiddle|EEikMenuItemRadioEnd ) )
            {
            iExtension->iHasRadioGroup = ETrue;
            if ( item->iData.iFlags&EEikMenuItemSymbolOn )
                {
                iExtension->iSelectedRadioButtonItem = ii;
                }
            }
        }

    aReader.ReadInt32(); // extension link
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::AddMenuItemsL
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::AddMenuItemsL( TInt aResourceId, TInt aPreviousId, TBool /*aAddSeperator*/ )
    {
    if ( !iItemArray )
        {
        CreateItemArrayL();
        }
    
    // Read from resource and add items after the item with 'aPreviousId'
    TResourceReader reader;
    iEikonEnv->CreateResourceReaderLC( reader, aResourceId );

    TInt position = iItemArray->Count();
    if ( aPreviousId )
        {
        ItemAndPos( aPreviousId, position );
        position++;
        }

    // 'Active Applications' menu item is forced to be first
    // item in the options menu.
    if (aResourceId == R_AVKON_MENUPANE_TASK_SWAPPER)
        {
        position = 0;
        }

    const TInt count = reader.ReadInt16();
    for (TInt ii = 0; ii < count; ++ii)
        {
        CEikMenuPaneItem* item = new(ELeave) CEikMenuPaneItem();
        CleanupStack::PushL( item );
        item->iData.iCommandId = reader.ReadInt32();
        item->iData.iCascadeId = reader.ReadInt32();
        item->iData.iFlags = reader.ReadInt32();
        TPtrC txtptr = reader.ReadTPtrC();
        item->SetScaleableTextL( txtptr );
        TPtrC extratxtptr = reader.ReadTPtrC();
        item->iData.iExtraText = extratxtptr;
        CreateIconFromResourceL( reader, *item );
        iItemArray->InsertL( position++, item );
        reader.ReadInt32(); // extension link
        CleanupStack::Pop();

        if ( item->iData.iFlags&(EEikMenuItemRadioStart|EEikMenuItemRadioMiddle|EEikMenuItemRadioEnd) )
            {
            iExtension->iHasRadioGroup = ETrue;
            if ( item->iData.iFlags&EEikMenuItemSymbolOn )
                {
                iExtension->iSelectedRadioButtonItem = ii; // so if there are several on, we have only the last of them to be activated
                }
            }
        }
    CleanupStack::PopAndDestroy();// reader
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::FilterDimmedItems
// -----------------------------------------------------------------------------
//
void CEikMenuPane::FilterDimmedItems()
    {
    TInt pos = iItemArray->Count() - 1;
    while ( pos >= 0 )
        {
        CEikMenuPaneItem* item = (*iItemArray)[pos];
        if ( item->iData.iFlags&EEikMenuItemDimmed )
            {
            DeleteMenuItem( item->iData.iCommandId );
            }
        pos--;
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetScrollBarOnLeft
// Sets the scroll bar to occupy the left side of the menu pane if aOnLeft is ETrue
//
// @since ER5U
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetScrollBarOnLeft(TBool aOnLeft)
    {
    if ( aOnLeft )
        {
        iFlags |= EEikMenuItemScrollBarLeft;
        }
    else
        {
        iFlags &= (~EEikMenuItemScrollBarLeft);
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetArrowHeadScrollBar
// Sets the menu pane to use an arrow head scroll bar if aArrowHead is ETrue.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetArrowHeadScrollBar( TBool /*aArrowHead*/ )
    {
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ResetItemArray
// Resets the menu's array of items and destroys its elements.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
void CEikMenuPane::ResetItemArray()
    {
    if ( !iItemArray )
        {
        return;
        }
    iItemArray->ResetAndDestroy();
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CreateItemArrayL
// Creates a new item array to be owned by the menu pane.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CreateItemArrayL()
    {
    iItemArray = new(ELeave) CItemArray;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CreateIconFromResourceL
// Creates an icon for the menu item aItem using the resource reader aReader.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CreateIconFromResourceL( TResourceReader& aReader, CEikMenuPaneItem& aItem ) const
    {
    TPtrC bitmapFile = aReader.ReadTPtrC();
    TInt bitmapId = aReader.ReadInt16();
    TInt bitmapMaskId = aReader.ReadInt16();
    if ( bitmapId != -1 )
        {
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* bitmapMask = NULL;

        if ( bitmapId == EMbmAvkonQgn_indi_app_open_add )
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            AknsUtils::CreateIconLC(skin,
            KAknsIIDQgnIndiAppOpen,
            bitmap, bitmapMask,
                bitmapFile,
                bitmapId, bitmapMaskId);
            }
        else
            {
            AknIconUtils::CreateIconLC(bitmap, bitmapMask,
                bitmapFile,
                bitmapId, bitmapMaskId);
            }

        aItem.CreateIconL(bitmap, bitmapMask);
        CleanupStack::Pop(2); // bitmap, bitmapMask.
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::Reset
// Destroys the menu pane's item array and scroll bar frame.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::Reset()
    {
    delete iItemArray;
    iItemArray = NULL;
    delete iSBFrame;
    iSBFrame = NULL;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CloseCascadeMenu
// Closes and destroys any current cascade menu and takes focus back.
// Does nothing if no cascade menu exists.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::CloseCascadeMenu()
    {
    CloseCascadeMenu( EFalse );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::TryLaunchCascadeMenuL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::TryLaunchCascadeMenuL(const CEikMenuPaneItem& aItem)
    {
    _AKNTRACE_FUNC_ENTER;
    iExtension->iShowCascadeTransition = EFalse;
    iExtension->iButtonDownItem = KErrNotFound;
    if ( aItem.iData.iFlags&EEikMenuItemDimmed )
        {
        iMenuObserver->HandleAttemptDimmedSelectionL( aItem.iData.iCommandId );
        return;
        }
    LaunchCascadeMenuL( aItem.iData.iCascadeId );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::LaunchCascadeMenuL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::LaunchCascadeMenuL( TInt aCascadeMenuId )
    {
    _AKNTRACE_FUNC_ENTER;
#ifdef THIS_IS_CORRECT_CODE_BUT_DISABLED_BECAUSE_OF_TEST_APPS
    // Series 60 does not have cascade options menus from another cascade menus..
    if ( iOwner ) return;
#endif // THIS_IS_CORRECT_CODE_BUT_DISABLED_BECAUSE_OF_TEST_APPS

    TInt err( KErrNone );
    TRAP( err, iCascadeMenuPane = new(ELeave) CEikMenuPane( iMenuObserver ));
    iCascadeMenuPane->SetMopParent( this );
    iCascadeMenuPane->SetObserver( Observer() );
    
    // delete object here so that new cascade menu pane does not get the same
    // address -> messes up transition registration..
    if( iExtension->iCascadeMenuObject )
        {
        GfxTransEffect::Deregister( iExtension->iCascadeMenuObject );
        }
              
    delete iExtension->iCascadeMenuObject;
    iExtension->iCascadeMenuObject = NULL;
    
    User::LeaveIfError( err );
    
    // register cascade options menu
    GfxTransEffect::Register( iCascadeMenuPane, KGfxOptionsMenuCascadeControlUid, EFalse );
    TRAP( err, DoLaunchCascadeMenuL( aCascadeMenuId ) );
    if ( err )
        {
        CloseCascadeMenu();
        User::Leave( err );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::DoLaunchCascadeMenuL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::DoLaunchCascadeMenuL( TInt aCascadeMenuId )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iItemArray || iItemArray->Count() == 0 )
        {
        return;
        }
    iCascadeMenuPane->ConstructL( this, iEditMenuObserver );
    iCascadeMenuPane->SetSelectedItem( 0 );

    // Stop menu pane physics when launching cascade menu 
    iExtension->iPhysics->StopPhysics();
    iExtension->iPhysics->ResetFriction();

    iMenuObserver->RestoreMenuL(iCascadeMenuPane,aCascadeMenuId,MEikMenuObserver::EMenuPane);
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    if (fepMenuObserver)
        {
        fepMenuObserver->DynInitMenuPaneL( aCascadeMenuId, iCascadeMenuPane );
        }
    if (iEditMenuObserver)
        {
        iEditMenuObserver->DynInitMenuPaneL( aCascadeMenuId, iCascadeMenuPane );
        }

    iCascadeMenuPane->iExtension->PrepareCascadeForItemCommands();
    iCascadeMenuPane->iExtension->EnableHighlight( EFalse );
    iCascadeMenuPane->FilterDimmedItems();

    // cascade menu launch animation
    if ( iExtension->iRedirectionListener )
        {
        iExtension->iRedirectionListener->LaunchCascadeMenu();
        }
    else
        {
        iExtension->StartCascadeMenuAppearTransition();
        }

    TTouchLogicalFeedback fbLogicalType = ETouchFeedbackPopUp;
    if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
        {
        fbLogicalType = ETouchFeedbackSubMenuOpened;
        }
    iExtension->ImmediateFeedback( fbLogicalType,
                                       ETouchFeedbackVibra );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CalculateSizeAndPosition
// Calculates and returns the menu pane's size.
// Also sets the rectangle of the menu pane.
// -----------------------------------------------------------------------------
//
TRect CEikMenuPane::CalculateSizeAndPosition()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect retVal;

    TInt numItemsInPane = 0;
    if ( iItemArray )
        {// Min size is for 1 item even if menu is empty
        numItemsInPane = iItemArray->Count();
        }

    if ( iExtension->iSct )
        {
        numItemsInPane++;
        }

    TInt maxItemsInView = NumberOfItemsThatFitInView();

    if (iExtension && iExtension->iSct)
        {
        maxItemsInView++;
        }

    numItemsInPane = Min( Max( 1, numItemsInPane ), maxItemsInView);

    TRect windowRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, windowRect );

    retVal = CalculateSizeAndPositionScalable( windowRect, numItemsInPane );
    _AKNTRACE_FUNC_EXIT;
    return retVal;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::StartDisplayingMenuPane
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::StartDisplayingMenuPane( const CEikHotKeyTable* /*aHotKeyTable*/,
                                                     const TPoint& /*aTargetPos*/,
                                                     const CEikMenuPaneTitle* /*aMenuPaneTitle*/,
                                                     TInt /*aMinTitleWidth*/,
                                                     TPopupTargetPosType /*aTargetType*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iExtension->iRedirectionListener )
        {
        iExtension->iRedirectionListener->AppearTransitionStarting();
        }

    CreateScrollBarFrame();

    iExtension->iPressedDown = EFalse;
    iExtension->SetOffset( 0 );

    const TSize screenSize( iEikonEnv->EikAppUi()->ApplicationRect().Size() );

    CEikCba *cba = 0;
    MopGetObject(cba);
    if ( cba )
        {
        cba->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlPopup );
        }

    iScroller->SetTopItemIndex(0); // to avoid broken values of topitemindex
    
    // set highlight visible if menu was opened via HW keys
    if ( iCoeEnv->LastEvent().Type() == EEventKey
            && iCoeEnv->LastEvent().Key()
            && iCoeEnv->LastEvent().Key()->iCode == EKeyCBA1 )
        {        
        SetDefaultHighlight();
        }    

    SetRect( CalculateSizeAndPosition() );

    // We need to set the background context when calling create for the
    // first time. Otherwise iExtension->iBgContext would have tiny
    // rectangles and grabbing the highlight background would produce
    // white.
    UpdateBackgroundContext( Rect() );

    // Initialize physics engine
    TRAP_IGNORE ( iExtension->InitPhysicsL() );
        
    MakeVisible(ETrue);
    SetFocus(ETrue);
    Window().SetPointerGrab( ETrue );    

    if ( iExtension->iSct )
        {
        iExtension->iSctHighlighted = ETrue;
        iSelectedItem = ENothingSelected;
        // If SCT row existing, set the default focus on SCT row not the top
        }

    if (iSelectedItem != ENothingSelected)
        {
        ScrollToMakeItemVisible(iSelectedItem);
        }
    PrepareHighlightFrame();
    SetCascadedIconSize();
        TRAP_IGNORE( ActivateL());
    if (iMenuPaneTitle)
        {
        CONST_CAST(CEikMenuPaneTitle*,iMenuPaneTitle)->MakeVisible(ETrue);
        TRAP_IGNORE( CONST_CAST(CEikMenuPaneTitle*,iMenuPaneTitle)->ActivateL());
        iMenuPaneTitle->DrawNow();
        }

    TRAP_IGNORE( DoUpdateScrollBarL() );

    // No highlight - hide softkey
    if ( iExtension && iExtension->iCba )
        {
        iExtension->iCba->MakeCommandVisible( EAknSoftkeySelect,
                iExtension->iFlags.IsSet(
                        CEikMenuPaneExtension::EHighlightEnabled ) );
        }

    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::UpdateBackgroundContext
// -----------------------------------------------------------------------------
//
void CEikMenuPane::UpdateBackgroundContext( const TRect& aWindowRect )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknLayoutRect topLeft;
    TAknLayoutRect bottomRight;
    TAknsItemID frameIID;
    TAknsItemID frameCenterIID;
    
    if( iOwner ) //for sub menu
        {
        topLeft.LayoutRect( aWindowRect, SkinLayout::Submenu_skin_placing_Line_2() );
        bottomRight.LayoutRect( aWindowRect, SkinLayout::Submenu_skin_placing_Line_5() );
        frameIID = KAknsIIDQsnFrPopupSub;
        frameCenterIID = KAknsIIDQsnFrPopupCenterSubmenu;
        }
    else
        {
        topLeft.LayoutRect( aWindowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2() );
        bottomRight.LayoutRect( aWindowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5() );
        frameIID = KAknsIIDQsnFrPopup;
        frameCenterIID = KAknsIIDQsnFrPopupCenterMenu;
        }

    TRect outerRect( topLeft.Rect().iTl, bottomRight.Rect().iBr );
    TRect innerRect( topLeft.Rect().iBr, bottomRight.Rect().iTl );

    if( iExtension )
        {
        iExtension->iBgContext->SetFrame( frameIID );
        iExtension->iBgContext->SetCenter( frameCenterIID );
        iExtension->iBgContext->SetFrameRects( outerRect, innerRect );
        }
    _AKNTRACE( " outerRect.iTl.iX = %d",   outerRect.iTl.iX );
    _AKNTRACE( " outerRect.iTl.iY = %d",   outerRect.iTl.iY );
    _AKNTRACE( " outerRect.iBr.iX = %d",   outerRect.iBr.iX );
    _AKNTRACE( " outerRect.iBr.iY = %d",   outerRect.iBr.iY );
    
    _AKNTRACE( " innerRect.iTl.iX = %d",   innerRect.iTl.iX );
    _AKNTRACE( " innerRect.iTl.iY = %d",   innerRect.iTl.iY );
    _AKNTRACE( " innerRect.iBr.iX = %d",   innerRect.iBr.iX );
    _AKNTRACE( " innerRect.iBr.iY = %d",   innerRect.iBr.iY );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::RepaintHighlight
// -----------------------------------------------------------------------------
//
void CEikMenuPane::RepaintHighlight() const
    {
    if ( !iExtension->iSctHighlighted )
        {
        DrawItem( SelectedItem(), EDrawHighlight );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::MoveHighlightTo
// Moves the menu pane highlight to the new selected menu item aNewSelectedItem.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::MoveHighlightTo(TInt aNewSelectedItem)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aNewSelectedItem =  %d", aNewSelectedItem );
    _AKNTRACE( "iSelectedItem =  %d", iSelectedItem );
    if ( aNewSelectedItem == iSelectedItem )
        {
        return;
        }
    
    iExtension->StopCascadeMenuTimer();
    TInt previousTopItem = iScroller->TopItemIndex();
    TInt previousSelectedItem = iSelectedItem;
    _AKNTRACE( "previousTopItem =  %d", previousTopItem );
    _AKNTRACE( "previousSelectedItem =  %d", previousSelectedItem );

    SetSelectedItem( aNewSelectedItem );

    if ( aNewSelectedItem >= 0 )
        {
        ScrollToMakeItemVisible( aNewSelectedItem );
        }
    else
        {
        ScrollToMakeItemVisible( 0 );
        }

    ActivateGc();
    CWindowGc& gc =  SystemGc();
    PrepareGcForDrawingItems( gc );
    
    TInt topItem = iScroller->TopItemIndex();
    TInt bottomItem = topItem + NumberOfItemsThatFitInView();
    if( bottomItem > NumberOfItemsInPane() )
        {
        bottomItem = NumberOfItemsInPane();
        }
    _AKNTRACE( "topItem =  %d", topItem );
    _AKNTRACE( "bottomItem =  %d", bottomItem );
    // When the SCT row will be highlight, remove highlight from
    // bottom's and top's item.
    if (iExtension->iSctHighlighted)
        {
        DrawItem( gc, topItem, ERemoveHighlight );
        DrawItem( gc, (bottomItem-1), ERemoveHighlight );
        }

    PrepareHighlightFrame();

    if ( previousTopItem == topItem  && aNewSelectedItem >= 0 )
        {
        // then only previuosly and currently selected items should be redrawn
        if ( iExtension->iHighlightedItem != KErrNotFound )
            {
            DrawItem( gc, previousSelectedItem, ERemoveHighlight );
            }

        if ( !iExtension->iSctHighlighted )
            {
            DrawItem( gc, aNewSelectedItem, EDrawHighlight );
            }
        }

    DeactivateGc();
    
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::PrepareGcForDrawingItems
// -----------------------------------------------------------------------------
//
void CEikMenuPane::PrepareGcForDrawingItems(CGraphicsContext& aGc) const
    {
    // BIDI
    /*
     * get the fonts from the LAF!
     * Do we need to get them here? - nope - moved to DrawItem()
     */    
    aGc.SetPenColor( iEikonEnv->ControlColor( EColorMenuPaneText, *this) );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor( iEikonEnv->ControlColor( EColorMenuPaneBackground,*this ) );
    }


// ---------------------------------------------------------------------------
// CEikMenuPane::DrawItem
// ---------------------------------------------------------------------------
//
void CEikMenuPane::DrawItem( TInt aItem, THighlightType aHighlight ) const
    {
    ActivateGc();
    CWindowGc& gc = SystemGc();
    PrepareGcForDrawingItems( gc );
    DrawItem( gc, aItem, aHighlight );
    DeactivateGc();
    }


// ---------------------------------------------------------------------------
// CEikMenuPane::DrawItem
// ---------------------------------------------------------------------------
//
void CEikMenuPane::DrawItem(CWindowGc& aGc,TInt aItem,THighlightType aHighlight) const
// BIDI - no hotkey text.  No pre-adornments
    {
    if ( !iItemArray || iItemArray->Count() == 0 || aItem == ENothingSelected )
        {
        return;
        }

    TInt numItemsInArray = iItemArray->Count();
    
    __ASSERT_DEBUG( aItem < numItemsInArray, Panic( EEikPanicNoSuchMenuItem ) );
    
    if ( aItem >= numItemsInArray )
        {
        return;
        }
    
    CEikMenuPaneItem* item = (*iItemArray)[aItem];
    // Max visible number of items in menu / submenu
    TInt maxNumberOfItems = NumberOfItemsThatFitInView();
    
    TInt topIndex = iScroller->TopItemIndex();
    // true if a cascade symbol must be drawn (main menu only)
    TBool cascade = ( item->iData.iCascadeId != 0 );

    // Specifies whether the text should be moved to give some space for icon.
    TBool hasIcon = MenuHasIcon();
    
    if ( iExtension->iSct )
        {
        ++maxNumberOfItems;
        ++numItemsInArray;
        }

    // number of items in the whole menu
    TInt numItems = Min( Max( 1, numItemsInArray ), maxNumberOfItems );
    TInt index =  aItem - topIndex;

    if ( iExtension->iSct )
        {
        // Sct row exists -> the rest of the menu items are pushed down
        // in visual representation.
        ++index;
        }
    TInt itemLeftInBottom = maxNumberOfItems -(numItemsInArray - topIndex);
    if ( (itemLeftInBottom > 0) && (topIndex > 0) ) 
        {
        index += itemLeftInBottom;
        }

    TBool drawSeparator = !( ( index + topIndex ) == numItemsInArray - 1 );
    TBool drawPartialItem = EFalse;
    
    if ( index == maxNumberOfItems )
        {
        // We have partial items to draw because of panning so there
        // is one more item to draw than normally.
        drawPartialItem = ETrue;
        
        // There is no layout data for the extra item, so we used the one
        // above it. 
        --index;
        }

    // If in Menu Sct, skip the first row of the recent used characters
    if ( index < 0 || index >= maxNumberOfItems || (iExtension->iSct && index==0))
        {
        return;  // only interested in drawing visible items
        }

    TAknTextLineLayout menuTextLayout;
    TAknLayoutRect singleMenuPaneRect;

    if ( !iOwner ) // main menu
        {
        singleMenuPaneRect.LayoutRect( iExtension->iItemAreaRect,
            AknLayoutScalable_Avkon::list_single_pane_cp2( index ).LayoutLine() );
        menuTextLayout = 
            AknLayoutScalable_Avkon::list_single_pane_t1_cp2( cascade ? 1 : 0 ).LayoutLine();
        }
    else // submenu
        {
        singleMenuPaneRect.LayoutRect( iExtension->iItemAreaRect,
            AknLayoutScalable_Avkon::list_single_popup_submenu_pane( index ).LayoutLine() );
        
        if ( hasIcon )
            {
            menuTextLayout = 
                TAknTextLineLayout( 
                AknLayoutScalable_Avkon::list_single_popup_submenu_pane_t1( 1 ).LayoutLine() );
            }
        else
            {
            menuTextLayout = 
                TAknTextLineLayout( 
                AknLayoutScalable_Avkon::list_single_popup_submenu_pane_t1( 0 ).LayoutLine() );
            }
        }

    TRect itemRect( singleMenuPaneRect.Rect() );
     
    // Move the rect with our panning offset.
    itemRect.iTl.iY += iExtension->Offset();
    itemRect.iBr.iY += iExtension->Offset();
    if( drawPartialItem )
        {        
        // For the extra item, also move it one full item height
        itemRect.iTl.iY += iItemHeight;
        itemRect.iBr.iY += iItemHeight;
        }
    
    TBool drawingInitiated = ETrue;

    RWindow& window = Window();
    
   if ( &window && window.GetDrawRect() == TRect::EUninitialized )
        {
        drawingInitiated = EFalse;
        }

    if ( !drawingInitiated && !iExtension->iFullRedraw )
        {
        TRect drawRect( itemRect ); 
        drawRect.Intersection( iExtension->iItemAreaRect );
        window.Invalidate( drawRect );
        window.BeginRedraw( drawRect );
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = NULL;
    if( iExtension )
        {
        cc = iExtension->iBgContext;
        }
    TBool background( ETrue );

    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor( singleMenuPaneRect.Color() );

    // there can be partial items, so clip drawing on menu pane's item area
    aGc.SetClippingRect( iExtension->iItemAreaRect );

    if (!iExtension->iFullRedraw)
        {
        background = AknsDrawUtils::Background(
            skin, cc, this, aGc, itemRect,
            KAknsDrawParamNoClearUnderImage );
        }

    if ( !background )
        {
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetPenStyle( CGraphicsContext::ENullPen );
        aGc.SetPenColor( singleMenuPaneRect.Color() );
        aGc.SetBrushColor( singleMenuPaneRect.Color() );         
        aGc.DrawRect( itemRect );
        }

    if ( !iExtension->HighlightEnabled() )
        {
        aHighlight = ENoHighlight;
        }
    
    switch ( aHighlight )
        {
        case EDrawHighlight :
            {
            if ( !iExtension->iSctHighlighted )
                {
                iExtension->iHighlightedItem = aItem;

                // Because of transparency, background must be drawn here as well
                // (as frame may be see-through)
                aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                aGc.SetBrushColor( singleMenuPaneRect.Color() );

                AknsDrawUtils::Background(
                    skin, cc, this, aGc, itemRect,
                    KAknsDrawParamNoClearUnderImage );

                TAknLayoutRect highlightTopLeft;
                TAknLayoutRect highlightBottomRight;

                highlightTopLeft.LayoutRect(itemRect,
                    SkinLayout::List_highlight_skin_placing__popup_windows__Line_2() );
                highlightBottomRight.LayoutRect(itemRect,
                    SkinLayout::List_highlight_skin_placing__popup_windows__Line_5() );
                TRect outerRect( highlightTopLeft.Rect().iTl, highlightBottomRight.Rect().iBr );
                TRect innerRect( highlightTopLeft.Rect().iBr, highlightBottomRight.Rect().iTl );

                TBool drawOk = AknsDrawUtils::DrawFrame( skin,
                        aGc, 
                        outerRect, 
                        innerRect, 
                        KAknsIIDQsnFrList, 
                        KAknsIIDDefault );

                // skinned highlight drawing has failed
                if ( !drawOk )
                    {
                    TAknLayoutRect shadowRect;
                    TAknLayoutRect highlightRect;
                    shadowRect.LayoutRect( itemRect,
                        AKN_LAYOUT_WINDOW_Highlight_graphics__various__Line_1( itemRect ) );
                    highlightRect.LayoutRect( itemRect,
                        AKN_LAYOUT_WINDOW_Highlight_graphics__various__Line_2( itemRect ) );
                    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                    shadowRect.DrawRect( aGc );
                    highlightRect.DrawRect( aGc );
                    }
                }
            break;
            }
        case ERemoveHighlight:
        case ENoHighlight:
            if ( iExtension->iHighlightedItem == aItem )
                {
                iExtension->iHighlightedItem = KErrNotFound;
                }
        default:
            break;
        }

    // Cascade
    if ( cascade )
        {
        TAknWindowLineLayout elementCascade( AknLayoutScalable_Avkon::list_single_pane_cp2_g3().LayoutLine());
        TAknLayoutRect cascadeRect;
        cascadeRect.LayoutRect( itemRect, elementCascade );
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        CAknsMaskedBitmapItemData* itemData = static_cast<CAknsMaskedBitmapItemData*>(
            skin->GetCachedItemData( KAknsIIDQgnIndiSubmenu, EAknsITMaskedBitmap ) );
        if( itemData )
            {
            aGc.BitBltMasked( cascadeRect.Rect().iTl, itemData->Bitmap(),
                cascadeRect.Rect().Size(), itemData->Mask(), ETrue );
            }
        else
            {
            aGc.BitBltMasked( cascadeRect.Rect().iTl, iExtension->iCascadeBitmap,
                cascadeRect.Rect().Size(), iExtension->iCascadeBitmapMask, ETrue );
            }
        }
    else
        {
        TAknLayoutRect activeApplicationsIconRect;
        activeApplicationsIconRect.LayoutRect( itemRect,
            AknLayoutScalable_Avkon::list_single_pane_g1_cp2(0).LayoutLine() );
        item->DrawItemIcon( aGc, activeApplicationsIconRect.Rect(), EFalse, 0);
        }

    if ( hasIcon )
        {
        TAknLayoutRect iconLayoutRect;
        iconLayoutRect.LayoutRect( itemRect,
            AknLayoutScalable_Avkon::list_single_popup_submenu_pane_g1().LayoutLine() );

        TRect iconRect = iconLayoutRect.Rect();

        // radio button group
        if ( iExtension->iHasRadioGroup )
            {
            if( IsItemMemberOfRadioButtonGroup(aItem) )
                {
                if ( iExtension->iSelectedRadioButtonItem == KNoSelectedRadioButtonItem &&
                    item->iData.iFlags&EEikMenuItemRadioStart )
                    {
                    // just to be sure that some radio button is set on
                    iExtension->iSelectedRadioButtonItem = aItem;
                    }

                if ( aItem == iExtension->iSelectedRadioButtonItem )
                    {
                    // draw radio button
                    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
                    CAknsMaskedBitmapItemData* itemData = static_cast<CAknsMaskedBitmapItemData*>(
                        skin->GetCachedItemData( KAknsIIDQgnIndiRadiobuttOn, EAknsITMaskedBitmap ) );
                    CFbsBitmap* radioButtonBmp = iExtension->iRadioButtonBitmap;
                    CFbsBitmap* radioButtonMask = iExtension->iRadioButtonBitmapMask;
                    if( itemData )
                        {
                        radioButtonBmp = itemData->Bitmap();
                        radioButtonMask = itemData->Mask();
                        }
                    if( radioButtonBmp && radioButtonMask )
                        {
                        AknIconUtils::SetSize( radioButtonBmp,  iconRect.Size() );
                        aGc.BitBltMasked( iconRect.iTl, radioButtonBmp,
                            iconRect.Size(), radioButtonMask, ETrue );
                        }
                    }
                }
            }
        else if ( item->iData.iFlags&EEikMenuItemSymbolOn )
            // draw check mark
            {
            aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
            CAknsMaskedBitmapItemData* itemData = static_cast<CAknsMaskedBitmapItemData*>(
                skin->GetCachedItemData( KAknsIIDQgnIndiMarkedAdd, EAknsITMaskedBitmap ) );
            CFbsBitmap* checkMarkBmp = iExtension->iCheckMarkBitmap;
            CFbsBitmap* checkMarkMask = iExtension->iCheckMarkBitmapMask;
            if( itemData )
                {
                checkMarkBmp = itemData->Bitmap();
                checkMarkMask = itemData->Mask();
                }
            if( checkMarkBmp && checkMarkMask )
                {
                AknIconUtils::SetSize( checkMarkBmp,  iconRect.Size() );
                aGc.BitBltMasked( iconRect.iTl, checkMarkBmp,
                    iconRect.Size(), checkMarkMask, ETrue );
                }
            }
        }

    // Text
    TAknLayoutText textRect;
    textRect.LayoutText( itemRect, menuTextLayout );
    TRgb textColor = textRect.Color();

    if ( aHighlight == EDrawHighlight ) // highlighted text
        {
        AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG10 );
        }
    else if ( !iOwner ) // menu
        {
        AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );
        }
    else // submenu
        {
        AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG20 );
        }

    //when OOM, the background is White, if the font's color is white, hardcode it to black
    if( !background && aHighlight != EDrawHighlight )
        {
        const TInt KRate = 95;    // 95% similar rate
        const TInt KFullColor = 255;
        TInt redcolor = textColor.Red();
        TInt bluecolor = textColor.Blue();
        TInt greencolor = textColor.Green();
        // test if the color is too similar to white color
        if ( redcolor > KFullColor * KRate / 100 || 
             bluecolor > KFullColor * KRate / 100 || 
             greencolor > KFullColor * KRate / 100 )
            {
            textColor = KRgbBlack;
            }
       }
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    aGc.SetPenColor( textColor );

    const CFont* font = textRect.Font();

    //TBuf<CEikMenuPaneItem::SData::ENominalTextLength + KAknBidiExtraSpacePerLine> visualText; // buffer for visually ordered text
    TBuf<255 + KAknBidiExtraSpacePerLine> visualText; // buffer for visually ordered text

    TInt clipWidth = textRect.TextRect().Width();

    AknBidiTextUtils::ConvertToVisualAndClip(
        item->ScaleableText(),
        visualText,
        *font,
        clipWidth,
        clipWidth );

    textRect.DrawText( aGc, visualText, EFalse, textColor );
    
    // calculate demarcation rectangle for cascaded menu item
    if (iCascadeMenuPane)
        {
        TPoint position( PositionRelativeToScreen() );
        TRect cascRect( textRect.TextRect() );
        cascRect.Move( position );
        iExtension->iCascadeDRect.SetRect( cascRect.iTl, cascRect.iBr );        
        }

    TAknLayoutRect highlightRect;
    highlightRect.LayoutRect( itemRect,
        AKN_LAYOUT_WINDOW_Highlight_graphics__various__Line_2( itemRect ) );

    // store the calculated y-position to the menu item,
    // so that it can be used in HandlePointerEventL()
    item->iPos = highlightRect.Rect().iTl.iY;
    
    // don't draw separator line for the last item
    if ( drawSeparator )
        {
        AknListUtils::DrawSeparator( aGc, itemRect, textColor, skin );
        }
    
    if ( !drawingInitiated && !iExtension->iFullRedraw )
        {
        Window().EndRedraw();
        }

    aGc.CancelClippingRect();
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::Draw
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::Draw( const TRect& aRect ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = NULL;

    if( iExtension )
        {
        cc = iExtension->iBgContext;
        }

    CWindowGc& gc = SystemGc();
    PrepareGcForDrawingItems( gc );

    TInt count=0;

    if( iItemArray )
        {
        count=iItemArray->Count();
        }

    // Give the topmost menu item's rect to SCT if needed.
    if ( iExtension->iSct )
        {
        iExtension->iSct->SetMenuSctRect( ItemRect( 0 ) );

        TRegionFix<4> region;
        region.AddRect( aRect );
        region.SubRect( iExtension->iSct->Rect() );
        gc.SetClippingRegion( region );
        }
        
    // The added flag removes the white bg for transparency
    TBool frameDrawn = AknsDrawUtils::Background( 
        skin, cc, this, gc, aRect, KAknsDrawParamNoClearUnderImage );        

    if ( aRect.Intersects( iExtension->iItemAreaRect ) )
        {
        iExtension->iFullRedraw = ETrue;   
    
        for ( TInt ii=0;ii<count;++ii )
            {
            if(!iExtension->iSctHighlighted && ii == iSelectedItem  )
                DrawItem( gc, ii, EDrawHighlight);
            else
                DrawItem( gc, ii, ENoHighlight);
            }    
      
        iExtension->iFullRedraw = EFalse;   
        }

    if ( iExtension->iSct )
        {
        gc.CancelClippingRegion();
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ReportSelectionMadeL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::ReportSelectionMadeL( TBool aAbortTransition )
    {
    _AKNTRACE_FUNC_ENTER;
    if( aAbortTransition )
        {
        GfxTransEffect::Abort();
        }
    if ( !iItemArray || iItemArray->Count() == 0 )
        {
        return;
        }

    if ( iCascadeMenuPane )
        {
        SetFocus( EFalse, EDrawNow );
        iCascadeMenuPane->SetFocus( ETrue, EDrawNow );
        return;
        }

    // means the cascade created on the down event is getting the up event
    if ( iSelectedItem == ENothingSelected && !iExtension->iSctHighlighted)
        {
        return;
        }

    CEikMenuPaneItem* item = NULL;

    // the sct highlight does not have index so do not try to get item with the index
    if(iSelectedItem != ENothingSelected)
        item = (*iItemArray)[iSelectedItem];

    if ( item && item->iData.iFlags&EEikMenuItemDimmed )
        {
        iMenuObserver->HandleAttemptDimmedSelectionL( item->iData.iCommandId );
        }
    else
        {
        TInt commandId = 0;
        if ( iExtension->iSctHighlighted )
            {
            commandId = EAknCmdEditMenuSctSelected;
            }
        else if (item && !item->iData.iCascadeId)
            {
            commandId = item->iData.iCommandId;
            }

        if ( commandId == EAknCmdTaskSwapper )
            {
            if ( !iExtension->iTaskSwapIdle->IsActive() )
                {
                iExtension->iTaskSwapIdle->Start( TCallBack( TaskSwapCallBack ) );
                }
            }

        if ( !commandId ) return; // Nothing to process

        if ( iEditMenuObserver )
            iEditMenuObserver->ProcessCommandL( commandId );

        // have to save pointer now because in case if we are in a submenu
        // 'this' might be destroyed by calling iMenuObserver->ProcessCommandL(
        // commandId ), so need to avoid crash
        CEikMenuPane* menu = iOwner ? iOwner : this;
        MCoeControlObserver* observer = menu->Observer();

        if ( commandId != EAknCmdTaskSwapper )
            {
            _AKNTRACE( "commandId = %d",  commandId );
            iMenuObserver->ProcessCommandL( commandId ); 
            }
        else
            {
            ReportCanceled();
            return;
            }

        // very important for the context sensitive menu because it will
        // be closed only after this call.
        if ( this && observer )
            {
            observer->HandleControlEventL( menu,
                MCoeControlObserver::EEventRequestExit );
            }

        MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
        if ( fepMenuObserver )
            {
            fepMenuObserver->ProcessCommandL( commandId );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::FocusChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::FocusChanged( TDrawNow aDrawNow )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aDrawNow =  %d", aDrawNow );

    if ( !iItemArray || iItemArray->Count() == 0 )
        {
        return;
        }
    
    if ( aDrawNow && iExtension->HighlightEnabled() )
        {
        // if focused or if current item is a cascade draw highlight (only draw if item is selected)
        if ( iSelectedItem != ENothingSelected )
            {
            const CEikMenuPaneItem* item = (*iItemArray)[iSelectedItem];
            THighlightType highlight = ERemoveHighlight;

            if ( !iExtension->iSctHighlighted && 
                 ( item->iData.iCascadeId || IsFocused() ) )
                {
                PrepareHighlightFrame();
                highlight = EDrawHighlight;
                }

            DrawItem( iSelectedItem, highlight);
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::IsHotKeyL
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::IsHotKeyL( const TInt modifiers, const TInt code )
    {
    if ( iHotKeyTable )
        {
        const TInt command = iHotKeyTable->CommandIdFromHotKey( code,modifiers );
        if ( command )
            {
            if ( iMenuObserver->CheckHotKeyNotDimmedL( command) )
                {
                // have to save pointer now because in case if we are in a submenu
                // 'this' might be destroyed by calling iMenuObserver->ProcessCommandL(
                // commandId ), so need to avoid crash
                CEikMenuPane* menu = iOwner ? iOwner : this;
                MCoeControlObserver* observer = menu->Observer();

                iMenuObserver->ProcessCommandL( command );

                // very important for the context sensitive menu because it will
                // be closed only after this call.
                if ( this && observer )
                    {
                    observer->HandleControlEventL( menu,
                        MCoeControlObserver::EEventRequestExit );
                    }
                }
            else
                {
                iMenuObserver->HandleAttemptDimmedSelectionL( command );
                }
            return ETrue;
            }
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::OfferKeyEventL
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CEikMenuPane::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    { // if were on the control stack then consume all keys
    return OfferKeyEventL( aKeyEvent, aType, ETrue );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::OfferKeyEventL
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CEikMenuPane::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType, TBool aConsumeAllKeys )
    { 
    _AKNTRACE_FUNC_ENTER;
    // Key event handling for scroll physics   
    // Don't react to shift keys
    if ( aKeyEvent.iScanCode == EStdKeyLeftShift ||
         aKeyEvent.iScanCode == EStdKeyRightShift )
        {
        if ( aConsumeAllKeys )
            {
            _AKNTRACE( "[%s]", "OfferKeyEventL return 1" );
            _AKNTRACE_FUNC_EXIT; 
            return EKeyWasConsumed;
            }
        else
            {
            _AKNTRACE( "[%s]", "OfferKeyEventL return 2" );
            _AKNTRACE_FUNC_EXIT;
            return EKeyWasNotConsumed;
            }
        }
    // Disable key events when panning
    if ( iExtension->iPanningActive || 
         iExtension->iPhysics->OngoingPhysicsAction() 
         == CAknPhysics::EAknPhysicsActionBouncing )
        { 
        _AKNTRACE( "[%s]", "OfferKeyEventL return 3" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;         
        }
    if ( iExtension->iFlickActive )
        { 
        // Stop physics engine when key down event occurs.     
        iExtension->iPhysics->StopPhysics();
        iExtension->iPhysics->ResetFriction();
        iExtension->iFlickActive = EFalse;
        iExtension->iKeyEventActive = ETrue;
        _AKNTRACE( "[%s]", "OfferKeyEventL return 4" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;                  
        }
    else if ( iExtension->iKeyEventActive && aType != EEventKeyDown )
        {
        // Consume following events until next key down.
        _AKNTRACE( "[%s]", "OfferKeyEventL return 5" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }
    else
        {
        // Next key down after stopping flick, it is ok to continue.
        iExtension->iKeyEventActive = EFalse;
        }
        
    // Restore possible panning offset
    if (iExtension->Offset() != 0 )
        {
        iExtension->RestoreOffset( aKeyEvent.iCode );
        }       
          
    CheckCreateScrollerL();
    const TInt modifiers = ( aKeyEvent.iModifiers )&( EModifierCtrl|EModifierShift|EModifierPureKeycode );
    const TInt code = aKeyEvent.iCode;
    TKeyResponse keyResponse = EKeyWasNotConsumed;
    if ( iCascadeMenuPane )
        {
        keyResponse = iCascadeMenuPane->OfferKeyEventL( aKeyEvent, aType, EFalse );
        if ( keyResponse == EKeyWasNotConsumed &&
            ( code==EKeyEscape || (!AknLayoutUtils::LayoutMirrored() && code==EKeyLeftArrow) || ( AknLayoutUtils::LayoutMirrored() && code==EKeyRightArrow) ) )
            {
            // show transition only when "canceling" the cascade menu
            // choosing an item from cascade does not execute effect
            iExtension->iShowCascadeTransition = ETrue;
            CloseCascadeMenu();
            //Fixed for TSW errors DLAN-7SFH86.
            IgnoreEventsUntilNextPointerUp();            
            keyResponse = EKeyWasConsumed;
            }
        _AKNTRACE( "[%s]", "OfferKeyEventL return 6" );
        _AKNTRACE_FUNC_EXIT;
        return keyResponse;
        }

    // with single click first key event enables highlight
    if ( !iExtension->HighlightEnabled() )
        {
        if ( code == EKeyUpArrow || code == EKeyDownArrow ||
             code == EKeyEnter || code == EKeyOK )
            {
            iExtension->SetDefaultHighlight();
            return EKeyWasConsumed;
            }
        }    

    // if popup menu displaying, needs to check for hotkeys itself.
    if ( IsHotKeyL( modifiers, code ) )
        return EKeyWasConsumed;
    TInt count = 0;
    if( iItemArray )
        count = iItemArray->Count();
    if ( count == 0 )
        {
        _AKNTRACE( "[%s]", "OfferKeyEventL return 8" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasNotConsumed;
        }
    const TInt max = count-1;
    TInt newHighlight = iSelectedItem;
    TBool loopScrolling = ETrue;
    TInt itemAfterLastItem = loopScrolling ? 0 : max;
    TInt itemAfterFirstItem = loopScrolling ? max : 0;

    // Scroll highlighted item so that it becomes visible,
    // if it is not visible before (scrolling with scroll bar
    // can cause highlighted item to go out of screen)
    TInt topItem = iScroller->TopItemIndex();
    TInt bottomItem = topItem + NumberOfItemsThatFitInView();
          
    if ( iExtension->Offset() < 0 ) 
        {
        // Extra bottom item when panning
        bottomItem++;
        }
    
    if( bottomItem > NumberOfItemsInPane() )
        {
        bottomItem = NumberOfItemsInPane();
        }
    _AKNTRACE( "topItem = %d,bottomItem = %d", topItem,bottomItem );

    if ( aType != EEventKeyDown && iSelectedItem != ENothingSelected &&
        !(iExtension->iSctHighlighted && topItem == 0) &&
        (iSelectedItem < topItem || iSelectedItem > bottomItem - 1) )
        {
        _AKNTRACE( "[%s]", "ScrollToMakeItemVisible(iSelectedItem);" );
        ScrollToMakeItemVisible(iSelectedItem);

        ActivateGc();
        CWindowGc& gc = SystemGc();
        PrepareGcForDrawingItems( gc );

        // draw all items that are needed.
        for( TInt i = 0; i < count; i++ )
            {
            if( i == iSelectedItem && !iExtension->iSctHighlighted)
                {
                DrawItem( gc, i, EDrawHighlight );
                }
            else
                {
                DrawItem( gc, i, ERemoveHighlight );
                }
            }

        DeactivateGc();
        _AKNTRACE( "[%s]", "OfferKeyEventL return 9" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }

    if ( iSelectedItem != ENothingSelected || iExtension->iSctHighlighted )
        {
        switch ( code )
            {
            case EKeySpace:
            	_AKNTRACE( "[%s]", "OfferKeyEventL(EKeySpace)" );
                iEikonEnv->InfoMsg( R_EIK_TBUF_PRESS_SPACE_MENP );
                _AKNTRACE( "[%s]", "OfferKeyEventL return 10" );
                _AKNTRACE_FUNC_EXIT;
                return EKeyWasConsumed;
// AKNLAF start
// loop scrolling always used in options menus
            case EKeyDownArrow:
            	_AKNTRACE( "[%s]", "OfferKeyEventL(EKeyDownArrow)" );
                if ( iExtension->iSctHighlighted && iExtension->iSct )
                    {
                    iExtension->iSctHighlighted = EFalse;
                    MoveHighlightTo( ++newHighlight );
                    iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                    }
                else
                    {
                    if ( iSelectedItem == max  && iExtension->iSct)
                        {
                        // If SCT exists, it gets the highlight
                        // if moving from the bottom item
                        iExtension->iSctHighlighted = ETrue;
                        MoveHighlightTo( ENothingSelected );
                        iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                        }
                    else
                        {
                        MoveHighlightTo( ++newHighlight>max? itemAfterLastItem: newHighlight );
                        }
                    }
                keyResponse = EKeyWasConsumed;
                break;
            case EKeyUpArrow:
            	_AKNTRACE( "[%s]", "OfferKeyEventL(EKeyUpArrow)" );
                if ( iExtension->iSct &&
                    iSelectedItem == 0 && !iExtension->iSctHighlighted )
                    {
                    iExtension->iSctHighlighted = ETrue;
                    MoveHighlightTo( ENothingSelected );
                    iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                    }
                else if ( iExtension->iSctHighlighted && iExtension->iSct )
                    {
                    iExtension->iSctHighlighted = EFalse;
                    MoveHighlightTo( itemAfterFirstItem );
                    iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                    }
                else
                    {
                    MoveHighlightTo( --newHighlight<0?
                                itemAfterFirstItem: newHighlight );
                    }
                keyResponse = EKeyWasConsumed;
                break;
// AKNLAF end
            case EKeyRightArrow :
            case EKeyLeftArrow :
                {
                _AKNTRACE( "[%s]", "OfferKeyEventL(EKeyRightArrow or EKeyLeftArrow)" );
                if( count == 0 ) // Implies empty or undefined item array
                    {
                    if ( aConsumeAllKeys )
                        return EKeyWasConsumed;
                    return EKeyWasNotConsumed;
                    }
                if ( iExtension->iSctHighlighted && iExtension->iSct )
                    {
                    return iExtension->iSct->OfferKeyEventL( aKeyEvent, aType );
                    }
                const CEikMenuPaneItem* item = (*iItemArray)[iSelectedItem];

                if ( item->iData.iCascadeId && iExtension->HighlightEnabled() )
                    {
                    if ( ( !AknLayoutUtils::LayoutMirrored() && code == EKeyRightArrow ) ||
                        ( AknLayoutUtils::LayoutMirrored() && code == EKeyLeftArrow ) )
                        {
                        TryLaunchCascadeMenuL( *item );

                        if ( iCascadeMenuPane )
                            {
                            iCascadeMenuPane->iExtension->SetDefaultHighlight();
                            }

                        keyResponse = EKeyWasConsumed;
                        break;
                        } // else fall through
                    } // else fall through
                }
            case EKeyHome:
            case EKeyEnd:
                {
                _AKNTRACE( "[%s]", "OfferKeyEventL(EKeyHome or EKeyEnd)" );
                // only popup menu panes should consume these keys. ???
                if ( aConsumeAllKeys )
                        return EKeyWasConsumed;
                return EKeyWasNotConsumed;
                }
            case EKeyEnter:
            case EKeyOK:
            case EAknSoftkeySelect:
            case EAknSoftkeyOk:

                {
                _AKNTRACE( "[%s]", "OfferKeyEventL(EKeyEnter,EKeyOK,EAknSoftkeySelect,EAknSoftkeyOk)" );
                if ( iExtension->iSctHighlighted && iExtension->iSct )
                    {
                    keyResponse = iExtension->iSct->OfferKeyEventL( aKeyEvent, aType );
                    if ( keyResponse == EKeyWasConsumed )
                        {
                        ReportSelectionMadeL();
                        break;
                        }
                    }
                if ( modifiers&( EModifierShift|EModifierCtrl|EModifierFunc ) )
                    return EKeyWasConsumed;
                if ( aKeyEvent.iRepeats )
                    return EKeyWasConsumed;
                if ( count == 0 ) // Do the same as modifiers (implies empty or undefined item array)
                    return EKeyWasConsumed;
                CEikMenuPaneItem* item = (*iItemArray)[iSelectedItem];
                if ( item->iData.iCascadeId )
                    {
                    TryLaunchCascadeMenuL( *item );
                    if ( iCascadeMenuPane )
                        {
                        iCascadeMenuPane->iExtension->SetDefaultHighlight();
                        }
                    }
                else
                    ReportSelectionMadeL();
                return EKeyWasConsumed;
                }
            case '4':// These are for menu sct.
            case '5':
            case '6':
                {
                _AKNTRACE( "[%s]", "OfferKeyEventL('4','5','6')" );
                if ( iExtension->iSctHighlighted && iExtension->iSct )
                    {
                    return iExtension->iSct->OfferKeyEventL( aKeyEvent, aType );
                    }
                else
                    {
                    return EKeyWasNotConsumed;
                    }
                }

            default:
                break;
            }
        }

    switch ( code )
        {
        case EKeyMenu:
        	_AKNTRACE( "[%s]", "OfferKeyEventL(EKeyMenu)" );
            iMenuObserver->HandleSideBarMenuL( 0, TPoint( 0, 0 ), modifiers, iHotKeyTable );
            return EKeyWasConsumed;
        case EKeyEscape:
        	_AKNTRACE( "[%s]", "OfferKeyEventL(EKeyEscape)" );
            if ( iOwner )
                return EKeyWasNotConsumed; // owner will destroy the cascade
            ReportCanceled();
            return EKeyWasConsumed;
        default:
            break;
            }

    if ( MoveToItemL( code, modifiers) )
    	{
        _AKNTRACE( "[%s]", "OfferKeyEventL return 11" );
    	 _AKNTRACE_FUNC_EXIT; 
    	 return EKeyWasConsumed;  // must return here because in the case of a cascade it will have been deleted by now.
    	}

    if ( aConsumeAllKeys )
    	{
    	_AKNTRACE( "[%s]", "OfferKeyEventL return 12" );
    	 _AKNTRACE_FUNC_EXIT; 
        return EKeyWasConsumed;
    	}

    else
    	{
    	_AKNTRACE( "[%s]", "OfferKeyEventL return 13" );
    	 _AKNTRACE_FUNC_EXIT; 
        return keyResponse;
    	}
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::NavigateToNextItem
// New for AVKON
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::NavigateToNextItem()
    {
    if ( iCascadeMenuPane )
        iCascadeMenuPane->NavigateToNextItem();
    else
        {
        const TInt max = NumberOfItemsInPane() - 1;
        TInt newHighlight = SelectedItem();
        MoveHighlightTo( ( ++newHighlight > max ) ? 0 : newHighlight);
        }
    }


// ---------------------------------------------------------------------------
// Activates the currently highlighted item.
// ---------------------------------------------------------------------------
//
void CEikMenuPane::ActivateCurrentItemL()
    {
    if ( !iExtension->HighlightEnabled() )
        {
        iExtension->SetDefaultHighlight();
        return;
        }
    _AKNTRACE_FUNC_ENTER;

    if ( iExtension->iPanningActive || 
           iExtension->iPhysics->OngoingPhysicsAction() 
               == CAknPhysics::EAknPhysicsActionBouncing )
        {
        // Don't allow the item activation in kinetic scrolling enabled
        // menus if menu is being dragged or bounce effect is in action.
        // In this case the event is discarded.
        _AKNTRACE( "[%s]" "ActivateCurrentItemL return 1" );
        _AKNTRACE_FUNC_EXIT;
        return;
        }
        
    TInt count( NumberOfItemsInPane() );
        
    // Scroll highlighted item so that it becomes visible
    // if it is not visible before (scrolling with scroll bar
    // can cause highlighted item to go out of screen).
    TInt topItem( iScroller->TopItemIndex() );
    TInt bottomItem( topItem + NumberOfItemsThatFitInView() );
    if ( bottomItem > count )
        {
        bottomItem = count;
        }

    if ( iExtension->Offset() < 0 &&
         ( iSelectedItem == topItem || iSelectedItem == bottomItem ) )
        {
        // Restoring offset with "simulated" ok key event.         
        iExtension->RestoreOffset( EKeyOK ); 
        }    
    else if ( iSelectedItem < topItem ||
              iSelectedItem > bottomItem - 1 )
        {
        if ( count > iSelectedItem )
            {
            if ( iExtension->iSctHighlighted && iExtension->iSct )
                {
                TKeyEvent key;
                key.iCode = EKeyOK;
                key.iModifiers = 0;

                TKeyResponse keyResponse( EKeyWasNotConsumed );
                TEventCode type( EEventNull );
                keyResponse = iExtension->iSct->OfferKeyEventL( key,
                                                                type );
                if ( keyResponse == EKeyWasConsumed )
                    {
                    ReportSelectionMadeL();
                    }
                _AKNTRACE( "[%s]" "ActivateCurrentItemL return 2" );
                _AKNTRACE_FUNC_EXIT;
                return;
                }
            }

        iExtension->isUpdateScrollDirectly = ETrue;
        ScrollToMakeItemVisible( iSelectedItem );
        iExtension->isUpdateScrollDirectly = EFalse;

        ActivateGc();
        CWindowGc& gc = SystemGc();
        PrepareGcForDrawingItems( gc );

        // Draw all items that are needed.
        for ( TInt i = 0; i < count; i++ )
            {
            if ( i == iSelectedItem && !iExtension->iSctHighlighted )
                {
                DrawItem( gc, i, EDrawHighlight );
                }
            else
                {
                DrawItem( gc, i, ERemoveHighlight );
                }
            }

        DeactivateGc();
        _AKNTRACE( "[%s]" "ActivateCurrentItemL return 3" );
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if ( iCascadeMenuPane )
        {
        iCascadeMenuPane->ActivateCurrentItemL();
        }
    else
        {
        if ( count > iSelectedItem )
            {
            if ( iExtension->iSctHighlighted && iExtension->iSct )
                {
                TKeyEvent key;
                key.iCode = EKeyOK;
                key.iModifiers = 0;

                TKeyResponse keyResponse( EKeyWasNotConsumed );
                TEventCode type( EEventNull );
                keyResponse = iExtension->iSct->OfferKeyEventL(
                                                key, type );
                if ( keyResponse == EKeyWasConsumed )
                    {
                    ReportSelectionMadeL();
                    }
                }
            else
                {
                CEikMenuPaneItem* item = (*iItemArray)[iSelectedItem];
                if ( item->iData.iCascadeId )
                    {
                    TryLaunchCascadeMenuL(*item);
                    }
                else
                    {
                    ReportSelectionMadeL();
                    }
                }
            }
        }
    _AKNTRACE( "[%s]" "ActivateCurrentItemL return 4" );
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CancelActiveMenuPane
// New for AVKON
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::CancelActiveMenuPane()
    {
    // If it is possible to close a cascade, return ETrue
    if ( iCascadeMenuPane )
        {
        iCascadeMenuPane->CancelActiveMenuPane();
        CloseCascadeMenu( ETrue );
        return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::MoveToItemL
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::MoveToItemL(TInt /*aCode*/, TInt /*aMods*/)
    {
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ReportCanceled
// -----------------------------------------------------------------------------
//
void CEikMenuPane::ReportCanceled()
    {

    // let menubar handle the cancel case so transition can be shown
    // use "fake" pointer event
    CEikMenuBar* menubar = static_cast<CEikMenuBar*>( Parent() );
    if( menubar->MenuPane() == this )
        {
        TPointerEvent ptrEvent;
        ptrEvent.iType = TPointerEvent::EButton1Up;
        menubar->HandlePointerEventL( ptrEvent );
        }
    else
        {
        MCoeControlObserver* observer = iOwner ? iOwner->Observer() : Observer();
        if ( observer )
            {
            // context sensitive menu
            TRAP_IGNORE( observer->HandleControlEventL( iOwner ? iOwner : this,
                MCoeControlObserver::EEventRequestCancel ) );
            }
        else  
            {
            // application menu
            TRAP_IGNORE( iMenuObserver->ProcessCommandL( EEikCmdCanceled ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ExtensionInterface
// -----------------------------------------------------------------------------
//
EXPORT_C void* CEikMenuPane::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

// ----------------------------------------------------------------------------
// CEikMenuPane::HandlePointerEventL
//
// Handles pointer events.
// ----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( iOwner && !IsVisible() )
        {
        _AKNTRACE( "[%s]", "HandlePointerEventL return 1" );
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    TBool noSelection = EFalse;
 
    // get pointer grabber1
    CCoeControl* grabberBefore = GrabbingComponent();
    
    TPointerEvent pointerEvent = aPointerEvent; 
    iExtension->ChangePosition( pointerEvent );
    iExtension->iLastPointerEvent = pointerEvent;
    
    // Send pointerevent to childs - not to scroll bar if a sub menu is open
    TRect sbRect;
    if ( iSBFrame->VerticalScrollBar() &&
         iSBFrame->VScrollBarVisibility() == CEikScrollBarFrame::EOn )
        {
        sbRect = iSBFrame->VerticalScrollBar()->Rect();
        }
    if ( ! ( iCascadeMenuPane && sbRect.Contains( 
              pointerEvent.iPosition ) ) )
        {
        _AKNTRACE( "[%s]", "CAknControl::HandlePointerEventL( pointerEvent );" );
        CAknControl::HandlePointerEventL( pointerEvent );        
        }    
    else
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                {
                iExtension->ImmediateFeedback( ETouchFeedbackSubMenuClosed );
                }
            else
                {
                iExtension->ImmediateFeedback( ETouchFeedbackPopUp );
                }
            iExtension->iShowCascadeTransition = ETrue;
            CloseCascadeMenu();  
            // Submenu of submenu was closed
            if ( iCascadeMenuPane  )
                {
                iCascadeMenuPane->iExtension->EnableHighlight( EFalse );
                iCascadeMenuPane->RepaintHighlight();
                iExtension->iDownOnMenuArea = EFalse;
                }
            else
                {
                iExtension->EnableHighlight( EFalse );
                RepaintHighlight();            
                }
            IgnoreEventsUntilNextPointerUp();
            _AKNTRACE( "[%s]", "HandlePointerEventL return 2" );
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        }

    // get pointer grabber
    CCoeControl* grabberAfter = GrabbingComponent();

    // if grabberBefore or grabberAfter, then some child is handling pointerevent.
    if ( (grabberBefore || grabberAfter ) 
         && ( !iExtension->iSct || iExtension->iScrollBarRect.Contains( pointerEvent.iPosition ) ) )
        {
        _AKNTRACE( "[%s]", "HandlePointerEventL return 3" );
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    // Forward pointer events to embedded CBA if sub menu open
    if ( iExtension->iCba && iCascadeMenuPane )
        {
        TBool sendToCBA = EFalse;
        // if embedded CBA is grabbing the pointer we send the events to it
        if( iExtension->iDownOnCbaArea )
            {
            if( aPointerEvent.iType == TPointerEvent::EButton1Up )
                {
                iExtension->iDownOnCbaArea = EFalse;
                }
            sendToCBA = ETrue;
            }            
        else 
            {
            TPoint pos ( 
                aPointerEvent.iPosition + PositionRelativeToScreen() );
            TRect cbaRect ( iExtension->iCba->PositionRelativeToScreen(), 
                            iExtension->iCba->Size() );
            if ( cbaRect.Contains( pos ) && 
                 aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                sendToCBA = ETrue;
                iExtension->iDownOnCbaArea = ETrue;
                }
            }
        iCascadeMenuPane->iExtension->iDownOnCbaArea 
            = iExtension->iDownOnCbaArea;
        
        if ( sendToCBA )
            {
            // scale the pointer event coordinates relative to CBA
            TPointerEvent event = aPointerEvent;
            TPoint position( aPointerEvent.iPosition + 
                    PositionRelativeToScreen() );
            event.iPosition = (position - 
                    iExtension->iCba->PositionRelativeToScreen());
            // send the event to CBA
            iExtension->iCba->HandlePointerEventL(event);          
            _AKNTRACE( "[%s]", "HandlePointerEventL return 4" );
            _AKNTRACE_FUNC_EXIT;
            return;            
            }
        }
    // Submenu of a submenu to forward events to cba
    else if ( iCascadeMenuPane )
        {
        iCascadeMenuPane->iExtension->iDownOnCbaArea 
            = iExtension->iDownOnCbaArea;
        }
    
    // In sub menu and pointer down has come to cba area
    if ( iOwner && iOwner->iExtension->iDownOnCbaArea )
        {
        TPointerEvent parentEvent;
        iExtension->CalculateParentEvent(aPointerEvent, parentEvent);                                        
        _AKNTRACE( "[%s]", "HandlePointerEventL return 5" );
        _AKNTRACE_FUNC_EXIT;
        return iOwner->HandlePointerEventL( parentEvent );
        }

    // Rect whic contains only area of menu items.
    const TRect innerRect = iBorder.InnerRect( Rect() );
    TRect menuSctRect;
    // Get the option item's rect in Menu SCT
    if ( iExtension->iSct )
        {
        menuSctRect = iExtension->iItemAreaRect;
        }
    TRect cascadeMenuRect(0,0,0,0);

    // Y coordinate for pointer event
    const TInt yPos = aPointerEvent.iPosition.iY;


    // Get top and botton item indexes.
    TInt topItem = iScroller->TopItemIndex();
    TInt bottomItem = topItem + NumberOfItemsThatFitInView();
  
    if( iExtension->Offset() < 0 )
        {
        // Panning has happened so we have one extra item.
        ++bottomItem;    
        }

    if( bottomItem > NumberOfItemsInPane() )
        {
        bottomItem = NumberOfItemsInPane();
        }


    // if submenu, then move it's rect coordinates to relative to parent.
    if ( iCascadeMenuPane  )
        {
        TPoint subPos = iCascadeMenuPane->Position();
        cascadeMenuRect = TRect(subPos-Position(), iCascadeMenuPane->Size());
        }

    // Pointerevent in case we need to pass event from submenu to parent
    TPointerEvent parentEvent;   

    // Stop timers if dragged outside
    if ( iExtension && iExtension->iDraggedOutside )
        {
        iExtension->StopCascadeMenuTimer();
        iExtension->ResetPressedHighlight();
        }

    switch (aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Up:
            {
            _AKNTRACE( "[%s]", "TPointerEvent::EButton1Up" );
            if ( !innerRect.Contains( aPointerEvent.iPosition ) ) 
                {
                TBool highlightWasEnabled = iExtension->HighlightEnabled();
                // remove highlight in case highlight is outside of menu pane 
                iExtension->EnableHighlight( EFalse );
                if ( iOwner )
                    {
                    RepaintHighlight();
                    }
                   else if ( highlightWasEnabled && !iCascadeMenuPane )
                    {
                    DrawItem( SelectedItem(), ENoHighlight );
                    }
                } 
            if ( iOwner && 
                 !innerRect.Contains( aPointerEvent.iPosition ) && 
                 !iExtension->iDownOnMenuArea )
                {
                iExtension->CalculateParentEvent( aPointerEvent, parentEvent);
                _AKNTRACE( "[%s]", "HandlePointerEventL return 6" );
                _AKNTRACE_FUNC_EXIT;
                return iOwner->HandlePointerEventL( parentEvent );
                }
            iExtension->iDownOnMenuArea = EFalse;

            iExtension->iPanningActive = EFalse;
            if ( !(iExtension->iSct &&  iExtension->iSct->Rect().Contains( iExtension->iStartPoint ) ) )
                {
                TPoint drag = iExtension->iStartPoint - aPointerEvent.iPosition;
                if ( iExtension->iPhysics->StartPhysics( 
                    drag, iExtension->iStartTime ) )
                    {
                    iExtension->iFlickActive = ETrue;
                    iExtension->ResetPressedHighlight();
                    }
                }
            if ( iExtension->HighlightTimerActive() &&
                 !iExtension->iPressedDown )
                {
                // Complete the timer here if it's still running
                // when up event is received.
                iExtension->ResetPressedHighlight();
                CEikMenuPaneExtension::HighlightTimerCallBack( iExtension );
                }
                      
            // in submenu and pointer lifted outside of x -limits : handle in parent
            if ( iOwner && iOwner->IsFocused() && (aPointerEvent.iPosition.iX < innerRect.iTl.iX  ||
                    aPointerEvent.iPosition.iX > innerRect.iBr.iX ))
                {
                iExtension->CalculateParentEvent( aPointerEvent, parentEvent);
                _AKNTRACE( "[%s]", "HandlePointerEventL return 7" );
                _AKNTRACE_FUNC_EXIT;
                return iOwner->HandlePointerEventL( parentEvent );
                }

            // if button up inside menu and over selected item, then do selection.
            if (Extension()->iItemsReadyForPenSelection &&
                innerRect.Contains( aPointerEvent.iPosition ) )
                {
                
                if(iExtension->iSct && iExtension->iSct->Rect().Contains(aPointerEvent.iPosition) && iExtension->iSpecialCharPointed)
                    {
                    TKeyEvent key;
                    key.iCode=EKeyOK;
                    key.iModifiers=0;
                    iExtension->iSct->OfferKeyEventL(key, EEventKey);
                    iExtension->iSpecialCharPointed = EFalse;
                    Extension()->iItemsReadyForPenSelection = EFalse;
                    ReportSelectionMadeL();
                    _AKNTRACE( "[%s]", "HandlePointerEventL return 8" );
                    _AKNTRACE_FUNC_EXIT;
                    return;
                    }
                else if(iSelectedItem != ENothingSelected ) // beware out of indexing
                    {
                    if ( iItemArray->Count() == 0 )
                        {
                        _AKNTRACE( "[%s]", "HandlePointerEventL return 9" );
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                        
                    TInt threshold = 0;
                    threshold = iExtension->iPhysics->DragThreshold();
                                          
                    CEikMenuPaneItem* item = (*iItemArray)[iSelectedItem];
                    if((yPos < item->iPos + iItemHeight + threshold ) &&
                     ( yPos > item->iPos - threshold ) )
                        {
                        // if new item has submenu, show it                                         
                        if ( item->iData.iCascadeId 
                            && iSelectedItem == iExtension->iButtonDownItem )    
                            {                              
                            // close previous submenu if open
                            if ( iCascadeMenuPane )
                                {
                                CloseCascadeMenu();
                                }                           
                            iExtension->StopCascadeMenuTimer();
                                                       
                            iExtension->ResetPressedHighlight();
                            
                            // Up happened on partial item, it must be moved to be
                            // fully visible before opening (possible) cascade menu.
                            if( iSelectedItem == topItem ||
                                iSelectedItem == bottomItem - 1)
                                {
                                // Restoring physics offset with "simulated" ok key event                      
                                iExtension->RestoreOffset( EKeyOK );
                                }                                 
                            MoveHighlightTo(iSelectedItem);
                         
                            TryLaunchCascadeMenuL( *item );
                            }
                        else if ( iExtension->iButtonDownItem == iSelectedItem )
                            {
                            iExtension->ImmediateFeedback( ETouchFeedbackList,
                                                           ETouchFeedbackVibra );
                            if( !IsCascadeMenuPane() )
                                {
                                // EFalse = don't stop transition if opening the cascade menu 
                                // just report selection
                                if ( ( !iExtension->iSct || ( iExtension->iSct && menuSctRect.Contains( aPointerEvent.iPosition ) ) )
                                    && !iCascadeMenuPane && iExtension->iPressedDown )
                                    {
                                    Extension()->iItemsReadyForPenSelection = EFalse;
                                    iExtension->ResetPressedHighlight();
                                    ReportSelectionMadeL( EFalse );
                                    _AKNTRACE( "[%s]", "HandlePointerEventL return 10" );
                                    _AKNTRACE_FUNC_EXIT;
                                    return;
                                    }                            
                                }
                            else
                                {
                                if ( !iExtension->iSct || ( iExtension->iSct && menuSctRect.Contains(aPointerEvent.iPosition) ) 
                                     && iExtension->iPressedDown )
                                    {
                                    Extension()->iItemsReadyForPenSelection = EFalse;
                                    iExtension->ResetPressedHighlight();
                                    ReportSelectionMadeL();
                                    _AKNTRACE( "[%s]", "HandlePointerEventL return 11" );
                                    _AKNTRACE_FUNC_EXIT;
                                    return;
                                    }
                                }
                            }
                        }
                    }
                }
                                           
            iExtension->ResetPressedHighlight();
            iExtension->iButtonDownItem = KErrNotFound;
            if ( iExtension->iNextHighlightItem != KErrNotFound )
                {
                MoveHighlightTo( iExtension->iNextHighlightItem );
                iExtension->iNextHighlightItem = KErrNotFound;
                }  
            }
            break;
        case TPointerEvent::EButton1Down:
            {
            _AKNTRACE( "[%s]", "TPointerEvent::EButton1Down" );
            iExtension->iNextHighlightItem = KErrNotFound;

            // Start drag
            if( innerRect.Contains( aPointerEvent.iPosition ) )
                {
                if ( iExtension->iFlickActive )
                    {
                    noSelection = ETrue;
					//when touch down during the flicking, play a basic list feedback
                    iExtension->ImmediateFeedback( ETouchFeedbackList );
                    }
                // stop physics for drag
                iExtension->iPhysics->StopPhysics();
                iExtension->iPhysics->ResetFriction();
                
                iExtension->iStartPoint = aPointerEvent.iPosition;
                iExtension->iPrevPoint = iExtension->iStartPoint;
                iExtension->iStartTime.HomeTime();          
                }                                             
      
            if ( !noSelection ) 
                {
                Extension()->iItemsReadyForPenSelection = ETrue;
                }
            if ( innerRect.Contains( aPointerEvent.iPosition ) )
                {
                iExtension->iDownOnMenuArea = ETrue;
                if ( !noSelection ) 
                    {
                    iExtension->EnableHighlight( ETrue, ETrue );
                    }
                if ( iCascadeMenuPane )
                    {
                    // if submenu, and clicked outside of it
                    if ( !cascadeMenuRect.Contains( aPointerEvent.iPosition ) )
                        {
                        if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                            {
                            iExtension->ImmediateFeedback( ETouchFeedbackSubMenuClosed );
                            }
                        else
                            {
                            iExtension->ImmediateFeedback( ETouchFeedbackPopUp );
                            }
                        //Just close sub menu
                        iExtension->iShowCascadeTransition = ETrue;
                        CloseCascadeMenu();
                        // Submenu of submenu was closed
                        if ( iCascadeMenuPane  )
                            {
                            iCascadeMenuPane->iExtension->EnableHighlight( EFalse );
                            iCascadeMenuPane->RepaintHighlight();
                            iExtension->iDownOnMenuArea = EFalse;
                            }
                        else
                            {
                            iExtension->EnableHighlight( EFalse );
                            RepaintHighlight();            
                            }
                        IgnoreEventsUntilNextPointerUp();                                                                  
                        break;
                        }
                    }
                else
                    {
                    // menu sct
                    if(iExtension->iSct&& !iExtension->iSctHighlighted && iExtension->iSct->Rect().Contains(aPointerEvent.iPosition))
                        {
                        iExtension->iSctHighlighted = ETrue;
                        iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                        MoveHighlightTo( ENothingSelected ); // from other highlight to sct
                        }
                    // Act in the rect of option items
                    else if (!iExtension->iSct || (iExtension->iSct && menuSctRect.Contains(aPointerEvent.iPosition)))
                        {
                        // Scroll only through visible items
                        for ( TInt ii = topItem; ii < bottomItem; ++ii )
                            {     
                            CEikMenuPaneItem* item = (*iItemArray)[ii];

                            // if this item is clicked
                            if ((yPos < item->iPos + iItemHeight) &&
                                (yPos > item->iPos))
                                {
                                if(iExtension->iSctHighlighted && iExtension->iSct && menuSctRect.Contains(aPointerEvent.iPosition))
                                    {
                                    // from sct to normal menu item
                                    iExtension->iSctHighlighted = EFalse;
                                    iExtension->iSct->HighlightSctRow( iExtension->iSctHighlighted );
                                    }

                                iExtension->iPressedDown = ETrue;

                                // Start timer for pressed highlight
                                if ( !noSelection )
                                    {
                                    iExtension->ImmediateFeedback( ETouchFeedbackList );
                                    iExtension->StartHighlightTimerL();
                                    }
                                iExtension->iNextHighlightItem = ii;
                                iExtension->iButtonDownItem = ii;
                                
                                // down even on already highlighted item => list feedback
                                if ( iExtension->iButtonDownItem == iSelectedItem )
                                    {
                                    iExtension->ImmediateFeedback( ETouchFeedbackList );
                                    }
                                if ( noSelection )
                                    {
                                    iExtension->iButtonDownItem = KErrNotFound;
                                    }

                                // if new item has submenu, show it
                                if ( item->iData.iCascadeId )
                                    {
                                    if ( !iExtension->IsCascadeMenuTimerActive() )
                                        {
                                        iExtension->StartCascadeMenuTimerL();
                                        }   
                                    }
                                // item found, then break looping
                                break;
                                }
                            }
                        }
                    }
                }
            else
                {
                // Clicked out side submenu, parent handles this
                if ( iOwner )
                    {
                    iExtension->CalculateParentEvent(aPointerEvent, parentEvent);                                        
                    _AKNTRACE( "[%s]", "HandlePointerEventL return 12" );
                    _AKNTRACE_FUNC_EXIT;
                    return iOwner->HandlePointerEventL( parentEvent );
                    }
                else
                    {
                    // For finger usability, extend to the right.
                    TRect innerToRightRect;
                    if ( AknLayoutUtils::LayoutMirrored() )
                        {
                        innerToRightRect = TRect( Rect().iTl, innerRect.iBr );
                        }
                    else
                        {
                        innerToRightRect = TRect( innerRect.iTl, Rect().iBr );
                        }
                    // Keep opened
                    if ( innerToRightRect.Contains( aPointerEvent.iPosition ) ) 
                        {
                        break;
                        }

                    // clicked outside, then close menu case by case
                    if ( iCascadeMenuPane )
                        {
                        if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                            {
                            iExtension->ImmediateFeedback( ETouchFeedbackSubMenuClosed );
                            }
                        else
                            {
                            iExtension->ImmediateFeedback( ETouchFeedbackPopUp );
                            }
                        iExtension->iShowCascadeTransition = ETrue;
                        CloseCascadeMenu(); //Just close sub menu.
                        // Submenu of submenu was closed
                        if ( iCascadeMenuPane  )
                            {
                            iCascadeMenuPane->iExtension->EnableHighlight( EFalse );
                            iCascadeMenuPane->RepaintHighlight();
                            }
                        else
                            {
                            iExtension->EnableHighlight( EFalse );
                            RepaintHighlight();                        
                            }
                        IgnoreEventsUntilNextPointerUp();
                        }
                    else
                        {
                        _AKNTRACE( "[%s]", "HandlePointerEventL return 12.5" );
                        _AKNTRACE_FUNC_EXIT;                   
                        return;
                        }
                    }
                }

            }
            break;

        case TPointerEvent::EButtonRepeat:
        case TPointerEvent::EDrag:
            {                    
            _AKNTRACE( "[%s]", "TPointerEvent::EDrag" );
            // In submenu and drag outside and down didn't come to menu
            if ( iOwner && 
                 !iExtension->iDownOnMenuArea && 
                 !innerRect.Contains( aPointerEvent.iPosition ) )
                {
                iExtension->CalculateParentEvent( aPointerEvent, parentEvent);
                _AKNTRACE( "[%s]", "HandlePointerEventL return 13" );
                _AKNTRACE_FUNC_EXIT;
                return iOwner->HandlePointerEventL( parentEvent );
                }

            if ( ( iExtension->iSct )
            		&& ( iExtension->iSct->Rect().Contains( iExtension->iStartPoint ) ) )
            	{
            	break;
            	}
            
            TPoint drag = iExtension->iStartPoint - 
                aPointerEvent.iPosition;
            TInt threshold = drag.iY;      
            if( Abs( threshold ) > iExtension->iPhysics->DragThreshold() 
                && iExtension->iDownOnMenuArea )
                {
                iExtension->iButtonDownItem = KErrNotFound;
                iExtension->ResetPressedHighlight();
                iExtension->iNextHighlightItem = KErrNotFound;
                iExtension->iPanningActive = ETrue;
                iExtension->EnableHighlight( EFalse );
                }    
                         
            if ( iExtension->iPanningActive )
                {
                TPoint delta( 
                    0, iExtension->iPrevPoint.iY - aPointerEvent.iPosition.iY );
                iExtension->iPhysics->RegisterPanningPosition( delta );
                } 
            iExtension->iPrevPoint = aPointerEvent.iPosition;                                                     

            // in submenu and pointer dragged outside of x -limits : handle in parent
            if ( iOwner && ((aPointerEvent.iPosition.iX < innerRect.iTl.iX ) ||
                   ( aPointerEvent.iPosition.iX > innerRect.iBr.iX )))
                {
                iExtension->CalculateParentEvent(aPointerEvent, parentEvent);     
                iExtension->iButtonDownItem = KErrNotFound;
                iExtension->ResetPressedHighlight();
                }
       
            // act in Menu Sct or Option Menu repectively
            if (( iExtension->iSct && menuSctRect.Contains(aPointerEvent.iPosition)) ||
                ( !iExtension->iSct && innerRect.Contains(aPointerEvent.iPosition)) &&
                iExtension->iDownOnMenuArea ) 
               {
                iExtension->iDraggedOutside = EFalse;
                // Scroll only through visible items
                for ( TInt ii = topItem; ii < bottomItem; ++ii )
                    {
                    CEikMenuPaneItem* item = (*iItemArray)[ii];

                    // if item is searched item.
                    if ( (yPos < item->iPos + iItemHeight) && (yPos
                            > item->iPos) )
                        {
                        if ( iCascadeMenuPane )
                            {
                            // if submenu open and touched item is not the one which opened submenu, then close submenu
                            if ( (ii != iSelectedItem)
                                    && !cascadeMenuRect.Contains(
                                            aPointerEvent.iPosition ) )
                                {
                                if ( CAknTransitionUtils::TransitionsEnabled(
                                        AknTransEffect::EComponentTransitionsOff ) )
                                    {
                                    iExtension->ImmediateFeedback(
                                            ETouchFeedbackSubMenuClosed );
                                    }
                                else
                                    {
                                    iExtension->ImmediateFeedback(
                                            ETouchFeedbackPopUp );
                                    }
                                iExtension->iShowCascadeTransition = ETrue;
                                CloseCascadeMenu();
                                }
                            }
                        else
                            {
                            TInt oldSelected = iSelectedItem;
                            // update highlight to new item
                            if ( oldSelected != ii )
                                {
                                iExtension->iPressedDown = EFalse;
                                }
                            TRect screenRect( TPoint( KMinTInt, KMinTInt ),
                                    TPoint( KMaxTInt, KMaxTInt ) );
                            TRect repeatRect( screenRect.iTl.iX, item->iPos,
                                    screenRect.iBr.iX, item->iPos
                                            + iItemHeight );
                            }
                        // item found, break                      
                        break;
                        }
                    }

                }
            }
            break;

        default:
            break;
        }
    _AKNTRACE( "[%s]", "HandlePointerEventL return 16" );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::InputCapabilities
// Returns the input capabilites of the menu pane which accepts all text.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
EXPORT_C TCoeInputCapabilities CEikMenuPane::InputCapabilities() const
    {
    return TCoeInputCapabilities( TCoeInputCapabilities::EAllText ); // Max length parameter removed for release15
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::AddMenuItemL
// Adds a new menu item to the menu pane by creating a new menu item, setting its data to aMenuItem
// and appending it to the pane's menu item array. Updates the menu's scroll bar to take acount of the
// new item.
// SData is a structure so all fields in it should be set to avoid any unexpected behaviour.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::AddMenuItemL( const CEikMenuPaneItem::SData& aMenuItem )
// For use by Menu extensions
    {
    if ( !iItemArray )
        CreateItemArrayL();
    CEikMenuPaneItem* item = new(ELeave) CEikMenuPaneItem();
    item->iData = aMenuItem;
    iItemArray->AddItemL( item );
    UpdateScrollBar();
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::AddMenuItemL
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, TInt aPreviousId)
    {
    if ( !iItemArray )
        CreateItemArrayL();
    CEikMenuPaneItem* item = new(ELeave) CEikMenuPaneItem();
    item->iData=aMenuItem;
    TInt position = 0;
    ItemAndPos( aPreviousId, position );
    iItemArray->InsertL( position + 1, item);
    UpdateScrollBar();
    }



// -----------------------------------------------------------------------------
// CEikMenuPane::DeleteMenuItem
// Deletes the menu item identified by aCommandId from the pane's item array.
//  Updates the menu's scroll bar to take acount of the change.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::DeleteMenuItem( TInt aCommandId )
    {
    TInt count=0;
    if( iItemArray )
        count=iItemArray->Count();
    for ( TInt ii = 0; ii < count; ++ii )
        {
        CEikMenuPaneItem* item=(*iItemArray)[ii];
        if ( item->iData.iCommandId == aCommandId )
            {
            iItemArray->Delete( ii );
            delete item;
            UpdateScrollBar();
            return;
            }
        }
    Panic( EEikPanicNoSuchMenuItem );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::DeleteBetweenMenuItems
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::DeleteBetweenMenuItems( TInt aStartIndex, TInt aEndIndex )
    {
    __ASSERT_DEBUG( aStartIndex <= aEndIndex, Panic( EEikPanicNoSuchMenuItem ) );
    TInt items(0);
    if( iItemArray )
        items=iItemArray->Count();
    if ( aEndIndex >= items )
        Panic( EEikPanicNoSuchMenuItem );

    TInt count = aEndIndex - aStartIndex + 1;
    for ( TInt ii = 0; ii < count; ii++ )
        {
        CEikMenuPaneItem* item = (*iItemArray)[aStartIndex];
        iItemArray->Delete( aStartIndex );
        delete item;
        }
    UpdateScrollBar();
    }



// -----------------------------------------------------------------------------
// CEikMenuPane::ItemData
// Returns a reference to the data in the menu item identified by aCommandId.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPaneItem::SData& CEikMenuPane::ItemData( TInt aCommandId )
    {
    TInt pos;
    CEikMenuPaneItem* item=ItemAndPos( aCommandId, pos );
    return item->iData;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ItemAndPos
// Returns a pointer to the menu item identified by aCommandId and gets the position of the item in aPos.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPaneItem* CEikMenuPane::ItemAndPos( TInt aCommandId, TInt& aPos )
    {
    TInt count(0);
    if( iItemArray )
        count = iItemArray->Count();
    aPos = 0;
    CEikMenuPaneItem* item;
    FOREVER
        {
        if ( aPos == count )
            Panic( EEikPanicNoSuchMenuItem );
        item = (*iItemArray)[aPos];
        if ( item->iData.iCommandId == aCommandId )
            break;
        ++aPos;
        }
    return item;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemTextL
// Sets the text of the menu item identified by aCommandId by reading it from the resource with id aRid.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemTextL(TInt aCommandId,TInt aRid)
    {
    TBuf<80> tmp;
    iCoeEnv->ReadResource( tmp, aRid );
    SetItemTextL( aCommandId, tmp);
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemTextL
// Sets the text of the menu item identified by aCommandId to the descriptor aDes.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemTextL( TInt aCommandId, const TDesC& aDes )
    {
    TInt pos;
    CEikMenuPaneItem* newItem=ItemAndPos( aCommandId, pos );
    newItem->iData.iText.Copy( aDes );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemDimmed
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemDimmed( TInt aCommandId, TBool aDimmed )
    {
    CEikMenuPaneItem::SData& itemData = ItemData(aCommandId);
    if ( aDimmed )
        itemData.iFlags |= EEikMenuItemDimmed;
    else
        itemData.iFlags &= ( ~EEikMenuItemDimmed );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemButtonState
// Sets the item to be indicated or not. It should be used to change the state of radio
// buttons or check box items.
// It has real effect only starting from v3.0.
// @param aButtonState should be EEikMenuItemSymbolOn or EEikMenuItemSymbolIndeterminate
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemButtonState( TInt aCommandId,TInt aButtonState )
{
    TInt pos(0);
    CEikMenuPaneItem* item = ItemAndPos( aCommandId, pos );

    if ( IsItemMemberOfRadioButtonGroup( pos ) )
        {
        if( aButtonState&EEikMenuItemSymbolOn )
            {
            iExtension->iSelectedRadioButtonItem = pos;
            }
        else if( iExtension->iSelectedRadioButtonItem == pos )
            {
            iExtension->iSelectedRadioButtonItem = KNoSelectedRadioButtonItem;
            }
        }

    item->iData.iFlags&=( ~(EEikMenuItemSymbolOn|EEikMenuItemSymbolIndeterminate) ); // clears the flags
    if ( aButtonState&EEikMenuItemSymbolOn )
        {
        item->iData.iFlags |= EEikMenuItemSymbolOn;
        }
    else if ( aButtonState&EEikMenuItemSymbolIndeterminate )
        {
        item->iData.iFlags |= EEikMenuItemSymbolIndeterminate;
        }
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetSelectedItem
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetSelectedItem( TInt aSelectedItem )
    {
    iSelectedItem = (aSelectedItem >= NumberOfItemsInPane() ) ? 0 : aSelectedItem;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SelectedItem
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CEikMenuPane::SelectedItem() const
    {
    return iSelectedItem;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemArray
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemArray( CItemArray* aItemArray )
    {
    if ( !ItemArrayOwnedExternally() )
        delete iItemArray;
    iItemArray = aItemArray;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemArrayOwnedExternally
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemArrayOwnedExternally( TBool aOwnedExternally )
    {
    iArrayOwnedExternally=aOwnedExternally;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetLaunchingButton
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetLaunchingButton( CEikButtonBase* aButton )
    {
    iLaunchingButton = aButton;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::NumberOfItemsInPane
// Returns the number of menu items.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CEikMenuPane::NumberOfItemsInPane() const
    {
    return( iItemArray ? iItemArray->Count() : 0);
    }

// -----------------------------------------------------------------------------
//  CEikMenuPane::Close
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::Close()
    {
    if( iExtension )
        {
        iExtension->iPressedDown = EFalse;
        iExtension->ResetPressedHighlight();
        }
            
    if ( OwnsWindow() )
        CloseWindow();

    if( iExtension )
        iExtension->MenuClosed();
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::Reserved_1
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::Reserved_1()
    {}

// -----------------------------------------------------------------------------
// CEikMenuPane::Reserved_2
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::Reserved_2()
    {}


//----------------------------------------------------------------------------
// CEikMenuPane::HandleScrollEventL()
//
// Handles scroll events by calculating new top and botton item indexes
// and then drawing all items that fit to screen
//----------------------------------------------------------------------------
//
void CEikMenuPane::HandleScrollEventL( CEikScrollBar* aScrollBar, TEikScrollEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;

    _AKNTRACE( "[%s]", "Stop physics engine");
    iExtension->iPhysics->StopPhysics();
    iExtension->iPhysics->ResetFriction();

    // flag for do we need to update or even calculate scrolling
    TBool update = ETrue;

    // if submenu is opened, close it because scrolling in submenu is not possible.
    // and in this case it also means tapping outside of submenu.
    if (iCascadeMenuPane)
        {
        _AKNTRACE( "[%s]", "CloseCascadeMenu");
        CloseCascadeMenu();
        update = EFalse;
        }

    // how many items fit to view
    const TInt itemsThatFitToView = NumberOfItemsThatFitInView();

    // How many items there are in this menu.
    TInt countOfItems = 0;
    if( iItemArray )
        {
        countOfItems = iItemArray->Count();
        }

    // if scrolling is impossible because (there is not enough items to be scrolled)
    if ( countOfItems < itemsThatFitToView )
        {
        update = EFalse;
        }

    // Get top and botton item indexes.
    TInt topItem = iScroller->TopItemIndex();
    TInt bottomItem = topItem + itemsThatFitToView;
    _AKNTRACE( "topItem = %d", topItem);
    _AKNTRACE( "bottomItem = %d", bottomItem);

    if( bottomItem > NumberOfItemsInPane() )
        {
        bottomItem = NumberOfItemsInPane();
        }

    // Items that becomes topmost and downmost items
    TInt newTopItem = 0;

    // if update is not wanted, do nothing.
    if ( update )
        {
        switch (aEventType)
            {
            case EEikScrollUp:
                {
                _AKNTRACE( "[%s]", "EEikScrollUp");
                _AKNTRACE( "topItem = %d", topItem);
                // if topItem is not upmost
                if ( topItem > 0)
                    {
                    // move menu to one step up.
                    newTopItem = topItem - 1;
                    }
                else
                    {
                    newTopItem = countOfItems - itemsThatFitToView;
                    }
                _AKNTRACE( "newTopItem = %d", newTopItem);
                }
                break;

            case EEikScrollDown:
                {
                _AKNTRACE( "[%s]", "EEikScrollDown");
                _AKNTRACE( "bottomItem = %d", bottomItem);
                // if last item is not visible
                if ( bottomItem < countOfItems)
                    {
                    // move menu to show one step down.
                    newTopItem = topItem + 1;
                    }
                else
                    {
                    newTopItem = 0;
                    }
                _AKNTRACE( "newTopItem = %d", newTopItem);
                }
                break;

            case EEikScrollPageUp:
                {
                _AKNTRACE( "[%s]", "EEikScrollPageUp");
                _AKNTRACE( "topItem = %d", topItem);
                // if topItem is not upmost
                if ( topItem > 0)
                    {
                    // move menu to show one site up or then upmost.
                    newTopItem = (topItem > itemsThatFitToView) ? (topItem - itemsThatFitToView) : 0;
                    }
                else
                    {
                    update = EFalse;
                    }
                _AKNTRACE( "newTopItem = %d", newTopItem);
                _AKNTRACE( "update = %d", update);
                }
                break;

            case EEikScrollPageDown:
                {
                _AKNTRACE( "[%s]", "EEikScrollPageDown");
                _AKNTRACE( "bottomItem = %d", bottomItem);
                update = ETrue;
                _AKNTRACE( "update = %d", update);
                }
                break;

            case EEikScrollThumbDragVert:
                {
                _AKNTRACE( "[%s]", "EEikScrollThumbDragVert");
                // new thumb position
                TInt thumb = aScrollBar->ThumbPosition();
                _AKNTRACE( "thumb = %d", thumb);
                update = ETrue;
                _AKNTRACE( "update = %d", update);
                }
                break;

            default:
                update = EFalse;
                break;
            }

        // if topItem changed, then draw menu again.
        if ( newTopItem != topItem || update )
            {
            iExtension->iListTopIndex = aScrollBar->ThumbPosition();
            TPoint newPosition( iExtension->iViewPosition.iX,
                    iExtension->iListTopIndex + iExtension->iViewHeight / 2 );
            
            iExtension->iFlags.Set( CEikMenuPaneExtension::ESkipScrollbarUpdate );
            iExtension->ViewPositionChanged( newPosition );
            iExtension->iFlags.Clear( CEikMenuPaneExtension::ESkipScrollbarUpdate );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CreateScrollBarFrame
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CreateScrollBarFrame()
    {
    if (!CheckCreateScroller())
        return;
    TRAPD( err,( iSBFrame = new(ELeave) CEikScrollBarFrame( this, iScroller, ETrue, ETrue ) ) );
    if ( !err )
        {
        CEikScrollBarFrame::TScrollBarVisibility visibility = CEikScrollBarFrame::EOn;

        if ( iItemArray->Count() <= NumberOfItemsThatFitInView() )
            {
            // all items fit, no need to show the scrollbar
            visibility = CEikScrollBarFrame::EOff;
            }

        TRAP_IGNORE( iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, visibility ) );
        TRAP_IGNORE( iSBFrame->CreateDoubleSpanScrollBarsL( EFalse, EFalse, ETrue, EFalse ) );
        iSBFrame->DrawBackground( EFalse, EFalse );
        UpdateScrollBar();
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::UpdateScrollBar
// -----------------------------------------------------------------------------
//
void CEikMenuPane::UpdateScrollBar()
    {
    if ( !CheckCreateScroller() || !IsVisible() )
        return;
    CIdle* idle = iScroller->Idle();
    if ( idle && !idle->IsActive() )
        idle->Start( TCallBack( CEikMenuPane::UpdateScrollBarCallBackL, this ) );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::UpdateScrollBarCallBackL
// -----------------------------------------------------------------------------
//
TInt CEikMenuPane::UpdateScrollBarCallBackL( TAny* aObj )
    { // static
    REINTERPRET_CAST(CEikMenuPane*,aObj)->DoUpdateScrollBarL();
    return 0;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::DoUpdateScrollBarL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::DoUpdateScrollBarL()
    {
    if (!iSBFrame)
        return;
    _AKNTRACE_FUNC_ENTER;
    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;

    TRect clientRect( iExtension->iMenuPaneRect.Size() );

    // Panning uses pixel resolution scrollbar
    vSbarModel.iThumbPosition = iExtension->iListTopIndex;      
    vSbarModel.iScrollSpan = TotalItemHeight();
    vSbarModel.iThumbSpan = iExtension->iViewHeight;

    // Double span scroll bar uses different model, just convert to it here.
    TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
    TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );

    TRect scrollBarInclusiveRect( clientRect );
    TRect scrollBarClientRect( scrollBarInclusiveRect );

    TEikScrollBarFrameLayout layout;
    layout.SetClientMargin( 0 );
    layout.SetInclusiveMargin( 0 );
    layout.iTilingMode = TEikScrollBarFrameLayout::EClientRectConstant;

    CEikScrollBarFrame::TScrollBarVisibility visibility = 
            iSBFrame->ScrollBarVisibility( CEikScrollBar::EVertical );
    
    // scrollbar is shown only if needed
    if ( iExtension->iScrollbarVisibility == CEikScrollBarFrame::EOn 
            && visibility == CEikScrollBarFrame::EOff )
        {
        iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, 
                CEikScrollBarFrame::EOn );
        iExtension->iScrollBarRect = iSBFrame->VerticalScrollBar()->Rect();
        }
    else if ( iExtension->iScrollbarVisibility == CEikScrollBarFrame::EOff 
            && visibility == CEikScrollBarFrame::EOn )
        {
        iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, 
                CEikScrollBarFrame::EOff );
        iExtension->iScrollBarRect = TRect::EUninitialized;
        }
    
    TAknLayoutRect scrollLayoutRect;
    scrollLayoutRect.LayoutRect( clientRect, 
            AknLayoutScalable_Avkon::listscroll_popup_sub_pane().LayoutLine() );
    scrollBarInclusiveRect = scrollLayoutRect.Rect();
    scrollBarClientRect = scrollBarInclusiveRect;

    AknLayoutUtils::LayoutVerticalScrollBar( iSBFrame, scrollBarClientRect,
      AknLayoutScalable_Avkon::scroll_pane_cp4().LayoutLine());

    iSBFrame->TileL( &hDsSbarModel, &vDsSbarModel, scrollBarClientRect, scrollBarInclusiveRect, layout );
    iSBFrame->SetVFocusPosToThumbPos( vDsSbarModel.FocusPosition() );
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::UpdateScrollBarThumbs
// -----------------------------------------------------------------------------
//
void CEikMenuPane::UpdateScrollBarThumbs()
    {
    if ( iSBFrame )
        {
        iSBFrame->SetVFocusPosToThumbPos( iExtension->iListTopIndex );             
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ScrollToMakeItemVisible
// -----------------------------------------------------------------------------
//
void CEikMenuPane::ScrollToMakeItemVisible(TInt aItemIndex)
    {
    _AKNTRACE_FUNC_ENTER;
    if( !iItemArray || iItemArray->Count() == 0 )
        return;
    if ( !CheckCreateScroller() )
        return;

    if(iExtension->iSctHighlighted && aItemIndex == ENothingSelected)
        aItemIndex = 0;
    else if(aItemIndex == ENothingSelected)
        return;

    TInt maxItems = NumberOfItemsThatFitInView();
    
    if ( iExtension->Offset() < 0 )
        {
        maxItems++;
        }
    //
    // S60 menus are fixed size pitch and known size so scrolling can be based on index
    //
    TInt amountToScroll = 0;
    if ( aItemIndex < iScroller->TopItemIndex() )
        { // +ve scroll
        amountToScroll = iItemHeight * ( iScroller->TopItemIndex() - aItemIndex );
        }
    else if ( aItemIndex >= ( iScroller->TopItemIndex() + maxItems ) )
        {
        amountToScroll = iItemHeight * (  ( iScroller->TopItemIndex() +
            maxItems ) - aItemIndex - 1 );
        }
    if ( amountToScroll )
        {
        _AKNTRACE( "amountToScroll =  %d", amountToScroll );
        Scroll(amountToScroll);
        
        if ( !iExtension->isUpdateScrollDirectly )
            {
            UpdateScrollBar();
            }
        else
            {
            DoUpdateScrollBarL();
            }        
        }
    _AKNTRACE_FUNC_EXIT;
    return;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::Scroll
// -----------------------------------------------------------------------------
//
void CEikMenuPane::Scroll( TInt aAmount )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !CheckCreateScroller() )
        return;
    TInt count=0;
    if( iItemArray )
        count = iItemArray->Count();

    // convert aAmount to a multiple of iItemHeight.
    TInt integer = aAmount / iItemHeight;
    TReal real = TReal( TReal( aAmount ) / TReal( iItemHeight ) );
    if ( real > TReal( integer ) ) // make more positive
        aAmount = ( integer + 1 ) * iItemHeight;
    if ( real < TReal( integer ) ) // make more negative
        aAmount = ( integer - 1 ) * iItemHeight;

    // convert amount back into indices for S60
    TInt newTop = iScroller->TopItemIndex() - ( aAmount / iItemHeight );  // don't think there should be a divide by 0 here.
    newTop = Max( 0, newTop );
    newTop = Min( newTop, count - NumberOfItemsThatFitInView() );
    iScroller->SetTopItemIndex( newTop );
    _AKNTRACE( "newTop =  %d", newTop );
 
    iExtension->iListTopIndex = iScroller->TopItemIndex() * iItemHeight;
    TPoint newPosition( iExtension->iViewPosition );
    newPosition.iY = iExtension->iListTopIndex + iExtension->iViewHeight / 2;  

    iExtension->SetOffset( 0 );
    iExtension->ViewPositionChanged( newPosition );
    
    _AKNTRACE( "iExtension->iListTopIndex =  %d", iExtension->iListTopIndex );
    _AKNTRACE( "iExtension->iViewPosition.iY =  %d", iExtension->iViewPosition.iY );
    _AKNTRACE( "[%s]", "iExtension->SetOffset( 0 )" );

    _AKNTRACE_FUNC_EXIT;
    return;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ViewRect
// -----------------------------------------------------------------------------
//
TRect CEikMenuPane::ViewRect() const
    {
    return Rect();
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::NumberOfItemsThatFitInView
// -----------------------------------------------------------------------------
//
TInt CEikMenuPane::NumberOfItemsThatFitInView() const
    {
    TInt subst = 0;
    if ( iExtension->iSct )
        {
        subst = 1;
        }

    iExtension->iItemsThatFitInView = iOwner ? AknLayoutScalable_Avkon::
        list_single_popup_submenu_pane_ParamLimits().LastRow() + 1 :
        AknLayoutScalable_Avkon::
        list_single_pane_cp2_ParamLimits().LastRow() + 1 - subst;
        if ( Layout_Meta_Data::IsLandscapeOrientation() 
             && iExtension->iItemsThatFitInView == 6 )
            {
            iExtension->iItemsThatFitInView --;
            }
        
    return iExtension->iItemsThatFitInView;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::TotalItemHeight
// -----------------------------------------------------------------------------
//
TInt CEikMenuPane::TotalItemHeight() const
    {
    TInt height(0);
    TInt count(0);
    if( iItemArray )
        count = iItemArray->Count();
    for (TInt ii = 0; ii < count; ++ii )
        {
        height += iItemHeight;
        }

    if ( iExtension->iSct )
        {
        height += iItemHeight;
        }
    return height;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CheckCreateScroller
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::CheckCreateScroller()
    {
    TInt err = KErrNone;
    if ( !iScroller )
        {
        TRAP( err,( iScroller = CMenuScroller::NewL( *this ) ) );
        }
    return err == KErrNone;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CheckCreateScrollerL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CheckCreateScrollerL()
    {
    if ( !iScroller )
        iScroller = CMenuScroller::NewL( *this );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ItemArrayOwnedExternally
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::ItemArrayOwnedExternally() const
    {
    return iArrayOwnedExternally;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::GetColorUseListL
// Gets the list of logical colors employed in the drawing of the control,
// paired with an explanation of how they are used. Appends the list into aColorUseList.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::GetColorUseListL( CArrayFix<TCoeColorUse>& aColorUseList ) const
    {
    CEikBorderedControl::GetColorUseListL( aColorUseList );

    TInt commonAttributes = TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
    TCoeColorUse colorUse;

    colorUse.SetLogicalColor( EColorMenuPaneText );
    colorUse.SetUse( TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::ESurrounds|commonAttributes );
    aColorUseList.AppendL( colorUse );

    colorUse.SetLogicalColor( EColorMenuPaneBackground );
    colorUse.SetUse( TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::ESurrounds|commonAttributes);
    aColorUseList.AppendL( colorUse );

    colorUse.SetLogicalColor( EColorMenuPaneTextHighlight );
    colorUse.SetUse( TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::EHighlights|commonAttributes );
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor( EColorMenuPaneHighlight );
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|TCoeColorUse::EHighlights|commonAttributes );
    aColorUseList.AppendL( colorUse );

    colorUse.SetLogicalColor( EColorMenuPaneDimmedTextHighlight );
    colorUse.SetUse( TCoeColorUse::EBack|TCoeColorUse::EDimmed|TCoeColorUse::EHighlights|commonAttributes );
    aColorUseList.AppendL( colorUse );

    colorUse.SetLogicalColor( EColorMenuPaneDimmedHighlight );
    colorUse.SetUse( TCoeColorUse::EFore|TCoeColorUse::EDimmed|TCoeColorUse::EHighlights|commonAttributes );
    aColorUseList.AppendL( colorUse );

    colorUse.SetLogicalColor( EColorMenuPaneDimmedText );
    colorUse.SetUse( TCoeColorUse::EBack|TCoeColorUse::EDimmed|TCoeColorUse::ESurrounds|commonAttributes);
    aColorUseList.AppendL( colorUse );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::HandleResourceChange
// Handles a change to the control's resources of type aType
// which are shared across the environment, e.g. colors or fonts.
//
// @since ER5U
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::HandleResourceChange( TInt aType )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aType= %d",  aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        if ( IsActivated() )
            {
            TInt maxItems = NumberOfItemsThatFitInView();
            TInt topIndex = iScroller->TopItemIndex();            
            TInt count = iItemArray->Count();
            if ( count <= maxItems )
                {
                iScroller->SetTopItemIndex( 0 );
                topIndex = iScroller->TopItemIndex();
                }
            //In portrait mode.   
            if ( !Layout_Meta_Data::IsLandscapeOrientation() ) 
                {
                if( ( count > maxItems ) && ( count - topIndex < maxItems ) )
                    {
                    TInt maxItemGaps = maxItems - (count - topIndex);                
                    iScroller->SetTopItemIndex( topIndex - maxItemGaps );
                    topIndex = iScroller->TopItemIndex();
                    }                 
                }
            TInt index = iSelectedItem - topIndex;
            if ( index >= maxItems )
                {
                topIndex = topIndex + (index + 1 - maxItems);
                iScroller->SetTopItemIndex( topIndex );              
                }
            
            TRect rect( CalculateSizeAndPosition() );
            SetExtent( rect.iTl, rect.Size() );

            //Initialize physics engine
            if ( iExtension->iPhysics )
                {
                TRAP_IGNORE ( iExtension->InitPhysicsL() );
                iExtension->iListTopIndex = iScroller->TopItemIndex() * iItemHeight;
                iExtension->iViewPosition.iY = 
                            iExtension->iListTopIndex + iExtension->iViewHeight / 2;  
                }             
         
            TRAP_IGNORE( DoUpdateScrollBarL() );

            UpdateBackgroundContext( Rect() );
            PrepareHighlightFrame();
            SetCascadedIconSize();
            DrawDeferred();
            if ( iCascadeMenuPane )
                {
                iCascadeMenuPane->HandleResourceChange( aType );
                } 
            
            }                                           
        }
    else if( aType == KEikMessageUnfadeWindows 
             || aType == KEikMessageWindowsFadeChange 
             || aType == KEikMessageFadeAllWindows )
        {
        //Fix for ELYG-7DR5UF
        if ( IsActivated() )
            {
            CEikScrollBar *verScrollBar = iSBFrame->VerticalScrollBar();
            if ( verScrollBar != NULL 
                && iSBFrame->VScrollBarVisibility() == CEikScrollBarFrame::EOn )
                {
                //iLastPointerEvent:Menu pane save the last pointer event in this
                // variable every time in HandlePointerEvent().
                if ( verScrollBar->Rect().Contains( iExtension->iLastPointerEvent.iPosition ) &&
                    ( iExtension->iLastPointerEvent.iType == TPointerEvent::EButton1Down
                    || iExtension->iLastPointerEvent.iType == TPointerEvent::EDrag ) )
                    {
                    TPointerEvent pointerEvent = iExtension->iLastPointerEvent;                    
                    pointerEvent.iType = TPointerEvent::EButton1Up;
                    // Sending a up event to scroll bar for dehighlighting 
                    // the scroll bar.
                    verScrollBar->HandlePointerEventL(pointerEvent);   
                    iSBFrame->DrawScrollBarsDeferred();
                    ClaimPointerGrab( EFalse );
                    }
                }
            // Fixed for TSW error ELLI-7UG89S
            if ( iExtension && iExtension->iPressedDown )
                {                                
                iExtension->iPressedDown = EFalse;
                DrawNow();
                }
            if ( iCascadeMenuPane )
                {
                iCascadeMenuPane->HandleResourceChange( aType );
                }
            }
        }
    else if ( aType == KAknMessageFocusLost )
        {
        if ( iCascadeMenuPane )
            {
            iCascadeMenuPane->HandleResourceChange( aType );
            }
        else if ( iExtension && iExtension->HighlightEnabled() )
            {
            iExtension->EnableHighlight( EFalse, EFalse );
            DrawItem( iSelectedItem, ENoHighlight );
            }
        }
    else
        {        
        CCoeControl::HandleResourceChange( aType );
        if ( aType == KAknsMessageSkinChange )
            {
            // fixed for TSW error ECGO-7NZCPR.
            SetCascadedIconSize();
            DrawDeferred();
            }
        }

    // Note: Animation is skin dependent, but it exists only when the menu is
    // displayed (additionally, inactive menupane simply won't receive skin
    // change event).
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::InsertMenuItemL
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::InsertMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, TInt aPosition)
    {
    if ( !iItemArray )
        CreateItemArrayL();
    CEikMenuPaneItem* item = new(ELeave) CEikMenuPaneItem();
    item->iData = aMenuItem;
    iItemArray->InsertL( aPosition, item );
    UpdateScrollBar();
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::MenuItemExists
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CEikMenuPane::MenuItemExists( TInt aCommandId, TInt& aPosition )
    {
    TInt count(0);
    if( iItemArray )
        count = iItemArray->Count();
    aPosition = 0;
    CEikMenuPaneItem* item;
    FOREVER
        {
        if ( aPosition == count )
            return EFalse;
        item  =(*iItemArray)[aPosition];
        if ( item->iData.iCommandId == aCommandId )
            break;
        ++aPosition;
        }
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::IsCascadeMenuPane
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CEikMenuPane::IsCascadeMenuPane() const
    {
    return iOwner != NULL;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::CascadeMenuPane
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPane* CEikMenuPane::CascadeMenuPane()
    {
    return iCascadeMenuPane;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ItemDataByIndexL
// Gets a reference to the data in the specified menu item.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikMenuPaneItem::SData& CEikMenuPane::ItemDataByIndexL(TInt aItemIndex)
    {
    __ASSERT_ALWAYS( iItemArray, Panic( EEikPanicInvalidIndex ) );
    if ( aItemIndex < 0 || aItemIndex >= iItemArray->Count() )
        {
        User::Leave( KErrArgument );
        }

    CEikMenuPaneItem* item = (*iItemArray)[aItemIndex];
    return item->iData;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::LoadCascadeBitmapL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::LoadCascadeBitmapL()
    {
    if ( iExtension )
        {
        if ( iExtension->iCascadeBitmap )
            {
            delete iExtension->iCascadeBitmap;
            iExtension->iCascadeBitmap = NULL;
            }
        if ( iExtension->iCascadeBitmapMask )
            {
            delete iExtension->iCascadeBitmapMask;
            iExtension->iCascadeBitmapMask = NULL;
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        AknsUtils::CreateIconL( skin, KAknsIIDQgnIndiSubmenu, iExtension->iCascadeBitmap,
            iExtension->iCascadeBitmapMask, KAvkonBitmapFile,
            EMbmAvkonQgn_indi_submenu, EMbmAvkonQgn_indi_submenu_mask );

        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::LoadCheckMarkBitmapL
// Creates the bitmap and the mask for check mark icon
// -----------------------------------------------------------------------------
//
void CEikMenuPane::LoadCheckMarkBitmapL()
    {
    if ( iExtension )
        {
        if ( iExtension->iCheckMarkBitmap )
            {
            delete iExtension->iCheckMarkBitmap;
            iExtension->iCheckMarkBitmap = NULL;
            }
        if ( iExtension->iCheckMarkBitmapMask )
            {
            delete iExtension->iCheckMarkBitmapMask;
            iExtension->iCheckMarkBitmapMask = NULL;
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        AknsUtils::CreateIconL( skin, KAknsIIDQgnPropSubMarked, iExtension->iCheckMarkBitmap,
            iExtension->iCheckMarkBitmapMask, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_sub_marked, EMbmAvkonQgn_prop_sub_marked_mask );

        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::MenuHasCheckBoxOn
// @return ETrue if at least one of the items has a check box to be on
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::MenuHasCheckBoxOn() const
    {
    for (TInt i = 0; i < iItemArray->Count(); i++)
        {
        CEikMenuPaneItem* item=(*iItemArray)[i];
        if ( item->iData.iFlags&EEikMenuItemCheckBox && item->iData.iFlags&EEikMenuItemSymbolOn )
            return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::LoadRadioButtonBitmapL
// Loads the bitmap and the mask for radio button icon
// -----------------------------------------------------------------------------
//
void CEikMenuPane::LoadRadioButtonBitmapL()
    {
    if ( iExtension )
        {
        if ( iExtension->iRadioButtonBitmap )
            {
            delete iExtension->iRadioButtonBitmap;
            iExtension->iRadioButtonBitmap = NULL;
            }
    if ( iExtension->iRadioButtonBitmapMask )
        {
        delete iExtension->iRadioButtonBitmapMask;
        iExtension->iRadioButtonBitmapMask = NULL;
        }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        AknsUtils::CreateIconL( skin, KAknsIIDQgnPropSubCurrent, iExtension->iRadioButtonBitmap,
            iExtension->iRadioButtonBitmapMask, KAvkonBitmapFile,
            EMbmAvkonQgn_prop_sub_current, EMbmAvkonQgn_prop_sub_current_mask );

        }
}


// -----------------------------------------------------------------------------
// CEikMenuPane::IsItemMemberOfRadioButtonGroup
// @return ETrue if the item in submenu is the member of the radio button group
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::IsItemMemberOfRadioButtonGroup(TInt aItem) const
    {
    if ( !( Extension()->iHasRadioGroup ) )
        {
        return EFalse;
        }

    if (aItem < 0 || aItem >= iItemArray->Count())
        {
        return EFalse;
        }

    CEikMenuPaneItem* item = (*iItemArray)[aItem];

    if ( item->iData.iFlags&( EEikMenuItemRadioStart|EEikMenuItemRadioMiddle|EEikMenuItemRadioEnd ) )
        {
        return ETrue;
        }

    for ( TInt i = aItem; i >= 0; i-- )
        {
        // try to find the beginning of radio button group, otherwise this item is before radio button group
        CEikMenuPaneItem* previuosItem = (*iItemArray)[i];
        if (previuosItem->iData.iFlags&EEikMenuItemRadioStart)
            {
            return ETrue;
            }
        }
    return EFalse;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::MenuHasIcon
// @return ETrue if at least one of the menu items has some icon to be drawn before the text.
// It is needed for DrawItem() function to move the text of all items right or left depending on the layout.
// If the menu doesn't contain any icons then text is positioned as in normal situation.
// -----------------------------------------------------------------------------
//
TBool CEikMenuPane::MenuHasIcon() const
    {
    TBool retValue = EFalse;
    // only submenus might contain radio button or check box
    if ( iOwner && iExtension )
        {
        retValue = ( (iExtension->iHasRadioGroup) || MenuHasCheckBoxOn() );
        }
    return retValue;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CalculateSizeAndPositionScalable
// Calculate size and position of a menu if scalable layouts are available.
// Also sets the rectangular for the menu pane
// -----------------------------------------------------------------------------
//
TRect CEikMenuPane::CalculateSizeAndPositionScalable( const TRect& aWindowRect, TInt aNumItemsInPane )
    {
    __ASSERT_ALWAYS( iExtension, Panic( EEikPanicNullPointer ) );
    _AKNTRACE_FUNC_ENTER;
    TRect retVal;

    // it can be only in submenu in case when scalable layout is available
    TBool hasIcon = MenuHasIcon();

    // scrollbar is shown only if needed
    if ( iItemArray->Count() > NumberOfItemsThatFitInView() )
        {
        iExtension->iScrollbarVisibility = CEikScrollBarFrame::EOn;
        }
    else
        {
        iExtension->iScrollbarVisibility = CEikScrollBarFrame::EOff;
        }
    
    TRect parentMenuRect;
    AknLayoutUtils::TAknCbaLocation cbaPosition = AknLayoutUtils::CbaLocation();    
                
    if ( !iOwner )
        {
        _AKNTRACE( "[%s]", "the laylout of mainmenu" );
        TAknLayoutRect parentMenuLayoutRect;     // popup_menu_window

        // This is a parent menu pane

        // Number of items and cba position tells the right layout for menu pane.
        // Constants (33, 20, 7) and calculations are based on to the variants of the layout data.
        switch ( cbaPosition )
            {
            case AknLayoutUtils::EAknCbaLocationLeft:
                {
                _AKNTRACE( "[%s]", "AknLayoutUtils::EAknCbaLocationLeft" );
                switch ( aNumItemsInPane )
                    {
                    case 7:
                    case 8:
                        {
                        parentMenuLayoutRect.LayoutRect( aWindowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(37 + aNumItemsInPane).LayoutLine());
    
                        break;                  
                        }
                    default:
                        parentMenuLayoutRect.LayoutRect( aWindowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(33 - aNumItemsInPane).LayoutLine());
                        break;
                    }
                break;                
                }
            case AknLayoutUtils::EAknCbaLocationRight:
                {
                _AKNTRACE( "[%s]", "AknLayoutUtils::EAknCbaLocationRight" );
                TRect windowRect;
                AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, windowRect );
                
                switch ( aNumItemsInPane )
                    {
                    case 7:
                    case 8:
                        {
                        parentMenuLayoutRect.LayoutRect( windowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(35 + aNumItemsInPane).LayoutLine());      
                        break;                  
                        }
                    default:
                        parentMenuLayoutRect.LayoutRect( windowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(20 - aNumItemsInPane).LayoutLine());
                        break;
                    }
                break;
                }
            case AknLayoutUtils::EAknCbaLocationBottom:
                {
                _AKNTRACE( "[%s]", "AknLayoutUtils::EAknCbaLocationBottom" );
                switch ( aNumItemsInPane )
                    {
                    case 7:
                    case 8:
                        {
                        parentMenuLayoutRect.LayoutRect( aWindowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(33 + aNumItemsInPane).LayoutLine());
                        break;                  
                        }
                    default:
                        parentMenuLayoutRect.LayoutRect( aWindowRect,
                            AknLayoutScalable_Avkon::popup_menu_window(7 + aNumItemsInPane).LayoutLine());
                        break;
                    }
                break;
                }
            default:
                break;
            }
        parentMenuRect = parentMenuLayoutRect.Rect();
        }
    else
        {
        _AKNTRACE( "[%s]", "the layout of submenu" );
        // submenu
        parentMenuRect = TRect( iOwner->Position(), iOwner->Size() );
        }

    _AKNTRACE( "parentMenuRect.iTl.iX = %d", parentMenuRect.iTl.iX );
    _AKNTRACE( "parentMenuRect.iTl.iY = %d", parentMenuRect.iTl.iY );
    _AKNTRACE( "parentMenuRect.Width() = %d", parentMenuRect.Width() );
    _AKNTRACE( "parentMenuRect.Height( = %d", parentMenuRect.Height() );

    if ( !iOwner ) // main menu
        {
        // Embedded cba
        TRect screen;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
        
        TAknLayoutRect cbaRect;
        cbaRect.LayoutRect( screen, 
            AknLayoutScalable_Avkon::popup_sk_window( 0  ).LayoutLine() );

        // Add space for embedded cba
        TRect menuRect ( parentMenuRect );
        parentMenuRect.iBr.iY += ( cbaRect.Rect().Height() );

        // CEikMenuPane rect contains empty space. We want the popup content
        // to be in correct place - so we calculate correct position for
        // background and move control rect to match new background top left
        // position.
        TPoint backgroundRectPos( 
            AknPopupUtils::Position( parentMenuRect.Size(), ETrue ) );
        
        retVal = parentMenuRect;
        retVal.Move( backgroundRectPos - parentMenuRect.iTl );
        
        // Set embedded cba rect
        if ( iExtension->iCba )
            {
            // There is hidden extra touch space for scroll bar in landscape
            TInt xOffset = parentMenuRect.iTl.iX - parentMenuRect.iTl.iX ; 
            iExtension->iCba->SetRect( TRect( 
                xOffset,
                menuRect.Height(),
                parentMenuRect.Width() + xOffset,
                menuRect.Height() + cbaRect.Rect().Height() ) );
            }

        iExtension->iMenuPaneRect = TRect( retVal.iTl, 
                                           TSize ( menuRect.Size() ) );

        TInt variety = 4;
        
        // reserve area for scrollbar only if it's shown
        if ( iExtension->iScrollbarVisibility == CEikScrollBarFrame::EOn )
            {
            variety = 0;
            }

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( TRect( iExtension->iMenuPaneRect.Size() ), 
                AknLayoutScalable_Avkon::listscroll_popup_sub_pane( 0 ) );
        
        iExtension->iMenuAreaRect = layoutRect.Rect();
        
        layoutRect.LayoutRect( iExtension->iMenuAreaRect,
                AknLayoutScalable_Avkon::list_menu_pane( variety ) );

        iExtension->iItemAreaRect = layoutRect.Rect();
        
        _AKNTRACE( "[%s]", "the layout of main menu return" );
        _AKNTRACE_FUNC_EXIT;                               
        return retVal;
        }

    // This is a cascaded sub menu
    // Get a rectangle for the Parent Menu (iOwner)
    TInt parentCount = iOwner->iItemArray->Count(); // There must be at least one parent item for a submenu to have popped up.

    iExtension->iSubMenuWidthIndex = KAlternativeSubmenuWidths - 1;

    TAknLayoutRect parentListScrollLayoutRect;     // listscroll_menu_pane

    TAknTextLineLayout subMenuText;                // layout for the text when item is not indicated
    TAknTextLineLayout subMenuIconText;            // layout for the text when item is indicated

    TAknWindowLineLayout parentListScrollPaneLayout( 
        AknLayoutScalable_Avkon::listscroll_menu_pane(0).LayoutLine() );
    parentListScrollLayoutRect.LayoutRect( parentMenuRect, parentListScrollPaneLayout );    
    subMenuText = AknLayoutScalable_Avkon::list_single_popup_submenu_pane_t1(0).LayoutLine();
    subMenuIconText = AknLayoutScalable_Avkon::list_single_popup_submenu_pane_t1(1).LayoutLine();

    // Choose correct submenu width
    // Find the narrowest layout that will accommodate the text
    // Need the font.
    const CFont* font = AknLayoutUtils::FontFromId( subMenuIconText.FontId() );
    // find the longest piece of text
    TInt textWidth = 0;
    TInt maxTextWidth = 0;
    TInt ii = 0;
    
    TInt count = (NULL != iItemArray) ? iItemArray->Count() : 0;

    for (ii = 0; ii < count; ++ii)
        {
        CEikMenuPaneItem* item = (*iItemArray)[ii];
        textWidth = font->TextWidthInPixels( item->iData.iText );
        maxTextWidth = Max( maxTextWidth, textWidth );
        }

    // find the suitable item width, so that the text would be visible
    TInt submenuVariety = 1;
    
    if ( iExtension->iScrollbarVisibility == CEikScrollBarFrame::EOn )
        {
        submenuVariety = 0;
        }

    for ( ii = 6; ii < KAlternativeSubmenuWidths + 6; ++ii )
        {
        TAknWindowLineLayout submenuLayout( AknLayoutScalable_Avkon::popup_submenu_window( ii ).LayoutLine() );
        TAknLayoutRect submenuRect;
        submenuRect.LayoutRect( parentListScrollLayoutRect.Rect(), submenuLayout );

        TAknWindowLineLayout listScrollPaneLayout( AknLayoutScalable_Avkon::listscroll_popup_sub_pane().LayoutLine() );
        TAknLayoutRect listScrollPaneRect;
        listScrollPaneRect.LayoutRect( submenuRect.Rect(), listScrollPaneLayout );

        TAknWindowLineLayout listSubmenuPaneLayout( AknLayoutScalable_Avkon::list_submenu_pane( submenuVariety ).LayoutLine() );
        TAknLayoutRect listSubmenuPaneRect;
        listSubmenuPaneRect.LayoutRect( listScrollPaneRect.Rect(), listSubmenuPaneLayout );

        TAknLayoutText textIconLayout;
        textIconLayout.LayoutText( listSubmenuPaneRect.Rect(), subMenuIconText);

        TAknLayoutText textLayout;
        textLayout.LayoutText( listSubmenuPaneRect.Rect(), subMenuText);

        TInt width = textLayout.TextRect().Width();
        TInt maxWidth( maxTextWidth );

        if ( hasIcon )
            {
            // this is needed to calculate right index, because they are for the case when there is no indication
            TInt difference = textIconLayout.TextRect().iTl.iX - textLayout.TextRect().iTl.iX;
            maxWidth = maxTextWidth + difference;
            width = textIconLayout.TextRect().Width();
            }

        if ( width >= maxWidth)
            {
            iExtension->iSubMenuWidthIndex = ii - 6; // finally we found one
            break;
            }
        }

    // Position of submenu depends upon parent size and position of selected item. Position is 1 at bottom up to six at top
    TInt parentPos = iOwner->iScroller->TopItemIndex() - iOwner->SelectedItem() +
        Min( parentCount, iOwner->NumberOfItemsThatFitInView() );

    TRect parentSelectedItemRect( iOwner->HighlightRect() );
    parentSelectedItemRect.Move( iOwner->Position() );

    TAknLayoutRect submenuWindowRect;
    // To prevent a panic in layout code, count has to be at least 1 even if
    // submenu is empty. Otherwise the index is out of bounds.
    if ( count == 0 )
        {
        count++;
        }
    TInt maxItems = NumberOfItemsThatFitInView();
    submenuWindowRect.LayoutRect( parentMenuRect,
        AknLayoutScalable_Avkon::popup_submenu_window( Min( count, maxItems ) - 1 ).LayoutLine() );
    // if submenu is higher than main menu, we should not allow it to cover softkeys in landscape
    // the same should be done if position of the menu was set from outside.
    if ( ( Layout_Meta_Data::IsLandscapeOrientation()
        && cbaPosition != AknLayoutUtils::EAknCbaLocationBottom &&
        ( submenuWindowRect.Rect().Height() > parentMenuRect.Height() ) ) )
        {
        // submenu should stay inside main menu by width,
        TRect bufRect( aWindowRect );
        bufRect.iTl.iX = parentMenuRect.iTl.iX;
        bufRect.iBr.iX = parentMenuRect.iBr.iX;
        submenuWindowRect.LayoutRect( bufRect,
            AknLayoutScalable_Avkon::popup_submenu_window( Min( count, maxItems ) - 1 ).LayoutLine() );
        }

    TAknLayoutRect widthSubmenuRect;
    widthSubmenuRect.LayoutRect( parentMenuRect,
        AknLayoutScalable_Avkon::popup_submenu_window( iExtension->iSubMenuWidthIndex + 6 ).LayoutLine() );

    TAknWindowLineLayout listScrollPaneLayout( AknLayoutScalable_Avkon::listscroll_popup_sub_pane().LayoutLine() );
    TAknLayoutRect listScrollPaneRect;
    listScrollPaneRect.LayoutRect( submenuWindowRect.Rect(), listScrollPaneLayout );

    enum { EFloating, EBottom } subMenuPos;

    if ( ( Layout_Meta_Data::IsLandscapeOrientation()
        && cbaPosition != AknLayoutUtils::EAknCbaLocationBottom ) )
        {
        if ( ( parentSelectedItemRect.iTl.iY + submenuWindowRect.Rect().Height() ) >
                aWindowRect.iBr.iY )
            {
            subMenuPos = EBottom;
            }
        else
            {
            subMenuPos = EFloating;
            }
        }
    else
        {
        if ( iOwner->iExtension->Offset() < 0 &&
            ((parentPos == 1 && count == 1) || 
            (parentPos == 2 && count <= 2) ||
            (parentPos == 3 && count <= 3) ||
            (parentPos == 4 && count <= 4) ||
            (parentPos == 5 && count <= 5)  )  )
            {
            // The menu has partial items because of panning and that has an effect on submenu positioning.
            subMenuPos = EFloating;
            }
        else if (parentPos == 1 ||
                 (parentPos ==2 && count >= 2) ||
                 (parentPos == 3 && count >= 4) ||
                 (parentPos == 4 && count >= 5) ||
                 (parentPos == 5 && count >= 6) )
            {
            subMenuPos = EBottom;
            }
        else
            {
            subMenuPos = EFloating;
            }
        }

    if ( subMenuPos == EBottom )
        {
        TInt widthOffset = widthSubmenuRect.Rect().Width() - submenuWindowRect.Rect().Width();
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            retVal = TRect( TPoint( submenuWindowRect.Rect().iTl.iX - widthOffset, submenuWindowRect.Rect().iTl.iY ),
                TSize( submenuWindowRect.Rect().Width() + widthOffset, submenuWindowRect.Rect().Height() ) );
            }
        else
            {
            retVal = TRect( submenuWindowRect.Rect().iTl,
                TSize( submenuWindowRect.Rect().Width() + widthOffset, submenuWindowRect.Rect().Height() ) );
            }
        }
    else  // floating
        {
        TInt yPos = parentSelectedItemRect.iTl.iY -
            ( listScrollPaneRect.Rect().iTl.iY - submenuWindowRect.Rect().iTl.iY );

        // When a submenu is floating, make sure that the possible panning offset of the
        // parent menu is taken into account.
        yPos += iOwner->iExtension->Offset();
        TInt widthOffset = widthSubmenuRect.Rect().Width() - submenuWindowRect.Rect().Width();
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            retVal = TRect( TPoint( submenuWindowRect.Rect().iTl.iX - widthOffset, yPos ),
                TSize( submenuWindowRect.Rect().Width() + widthOffset, submenuWindowRect.Rect().Height() ) );
            }
        else
            {
            retVal = TRect( TPoint( submenuWindowRect.Rect().iTl.iX, yPos ),
                TSize( submenuWindowRect.Rect().Width() + widthOffset, submenuWindowRect.Rect().Height() ) );
            }
        }

    // move submenu if it overlaps with embedded cba
    if ( iOwner && iOwner->iExtension->iCba )
        {
        if ( retVal.iBr.iY > iOwner->iExtension->iMenuPaneRect.iBr.iY )
            {
            TInt offset = retVal.iBr.iY - 
                iOwner->iExtension->iMenuPaneRect.iBr.iY;
            retVal.Move( 0, -offset );
            }
        }
    
    if ( retVal.iTl.iY < 0 )
        {
        retVal.Move( 0, -retVal.iTl.iY );
        }

    iExtension->iMenuPaneRect = retVal;

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( TRect( iExtension->iMenuPaneRect.Size() ), 
            AknLayoutScalable_Avkon::listscroll_popup_sub_pane( 0 ) );
    
    iExtension->iMenuAreaRect = layoutRect.Rect();
    
    layoutRect.LayoutRect( iExtension->iMenuAreaRect,
            AknLayoutScalable_Avkon::list_submenu_pane( submenuVariety ) );

    iExtension->iItemAreaRect = layoutRect.Rect();
    
    _AKNTRACE( "[%s]", "the layout of sub menu return" );
    _AKNTRACE_FUNC_EXIT;  
    return retVal;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::HighlightRect
// -----------------------------------------------------------------------------
//
TRect CEikMenuPane::HighlightRect() const
    {
    TInt index = iSelectedItem - iScroller->TopItemIndex();

    // If menu is closed and the selected item index is outside the visible
    // item range this method is called with new iSelectedItem and old
    // TopItemIndex. Which results in negative index. This "fix" prevents from
    // crashing the menu.
    if( index < 0 )
        index = 0;

    // When physics is enabled highlight can be moved to partially visible
    // item which is at the bottom of menu. This causes layout panic and to 
    // avoid that we reduce index by one.
    if ( index == NumberOfItemsThatFitInView() )
        {
        index--;
        }
   
    return ItemRect( index );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::PrepareHighlightFrame
// helps to avoid flickering on drawing
// -----------------------------------------------------------------------------
//
void CEikMenuPane::PrepareHighlightFrame() const
    {
    TRect highlightRect( HighlightRect() );
    TAknLayoutRect highlightTopLeft;
    TAknLayoutRect highlightBottomRight;
    highlightTopLeft.LayoutRect( highlightRect,
        SkinLayout::List_highlight_skin_placing__popup_windows__Line_2() );
    highlightBottomRight.LayoutRect( highlightRect,
        SkinLayout::List_highlight_skin_placing__popup_windows__Line_5() );
    TRect outerRect = TRect( highlightTopLeft.Rect().iTl, highlightBottomRight.Rect().iBr );
    TRect innerRect = TRect( highlightTopLeft.Rect().iBr, highlightBottomRight.Rect().iTl );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    AknsDrawUtils::PrepareFrame( skin, outerRect, innerRect,
                                 KAknsIIDQsnFrList, KAknsIIDDefault );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::SetCascadedIconSize
// Calls SetSize for cascaded icon. Doing this in construction phase makes
// Draw() method faster.
// -----------------------------------------------------------------------------
//
void CEikMenuPane::SetCascadedIconSize() const
    {
    TAknWindowLineLayout elementCascade( AknLayoutScalable_Avkon::list_single_pane_cp2_g3().LayoutLine());
    TAknLayoutRect cascadeRect;
    cascadeRect.LayoutRect( HighlightRect(), elementCascade );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    CAknsMaskedBitmapItemData* itemData = static_cast<CAknsMaskedBitmapItemData*>(
        skin->GetCachedItemData( KAknsIIDQgnIndiSubmenu, EAknsITMaskedBitmap ) );

    if( itemData )
        {
        AknIconUtils::SetSize( itemData->Bitmap(),  cascadeRect.Rect().Size() );
        }
    else
        {
        if (iExtension->iCascadeBitmap)
            {
            AknIconUtils::SetSize( iExtension->iCascadeBitmap,  cascadeRect.Rect().Size() );
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::EnableMarqueeL
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::EnableMarqueeL( const TBool /*aEnable*/ )
    {
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::MopSupplyObject
// -----------------------------------------------------------------------------
//
EXPORT_C TTypeUid::Ptr CEikMenuPane::MopSupplyObject( TTypeUid aId )
    {
    if( aId.iUid == MAknsControlContext::ETypeId && iExtension && iExtension->iBgContext )
        {
        // Supply background skin context for scroll bars.
        return MAknsControlContext::SupplyMopObject( aId, iExtension->iBgContext);
        }

    return CCoeControl::MopSupplyObject( aId );
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CountComponentControls
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CEikMenuPane::CountComponentControls() const
    {
    TInt count = 0;
    if ( iSBFrame && iSBFrame->VerticalScrollBar() )
        {
        count = 1;
        }
    if ( iExtension->iSct )
        {
        count++;
        }

    if ( iExtension->iCba )        
        {
        count++;
        }

    return count;
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ComponentControl
// -----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CEikMenuPane::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex)
        {
        case 0:
            {
            if ( iSBFrame && iSBFrame->VerticalScrollBar() )
                {
                return iSBFrame->VerticalScrollBar();
                }
            }
        case 1:
            {
            if ( iExtension->iSct )
                {
                return iExtension->iSct;
                }
            else if ( iExtension->iCba )
                {
                return iExtension->iCba;
                }
            }
        case 2:
            {
            if ( iExtension->iCba )
                {
                return iExtension->iCba;
                }
            }
        default:
            {
            return NULL;
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::Extension
// Asserts that extension object has been created.
// -----------------------------------------------------------------------------
//
CEikMenuPaneExtension* CEikMenuPane::Extension() const
    {
    __ASSERT_ALWAYS( iExtension, Panic( EEikPanicNullPointer ) );
    return iExtension;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CheckCreateExtensionL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CheckCreateExtensionL()
    {
    if ( !iExtension )
        {
        iExtension = new (ELeave) CEikMenuPaneExtension;
        iExtension->ConstructL( this );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ItemRect
// -----------------------------------------------------------------------------
//
TRect CEikMenuPane::ItemRect( TInt aItemIndex ) const
    {
    // this method is valid for the main menu only
    TInt lastRow = AknLayoutScalable_Avkon::list_single_pane_cp2_ParamLimits().LastRow();
    aItemIndex = Min( aItemIndex, lastRow );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( iExtension->iItemAreaRect,
            AknLayoutScalable_Avkon::list_single_pane_cp2( aItemIndex ) );
            
    return layoutRect.Rect();
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CalculateItemHeight
// -----------------------------------------------------------------------------
//
TInt CEikMenuPane::CalculateItemHeight() const
    {
    TAknWindowLineLayout menuLineLayout;

    if ( iOwner ) // submenu
        {
        menuLineLayout = 
            AknLayoutScalable_Avkon::list_single_popup_submenu_pane( 0 ).LayoutLine();
        }
    else
        {
        menuLineLayout = 
            AknLayoutScalable_Avkon::list_single_pane_cp2( 0 ).LayoutLine();
        }

    TAknLayoutRect menuLayoutRect;
    menuLayoutRect.LayoutRect( Rect(), menuLineLayout );
    
    return menuLayoutRect.Rect().Height();
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructMenuSctRowL
// Creates an sct row for editing menu.
// @param aSpecialChars Buffer that holds selected characters
// @since 3.1
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::ConstructMenuSctRowL( TDes& aSpecialChars )
    {
    CheckCreateScrollerL();
    CheckCreateExtensionL();

    TInt resourceId = R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS;
    if (FeatureManager::FeatureSupported(KFeatureIdChinese))
        {
        resourceId = R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE;
        }
    iExtension->ConstructMenuSctRowL( aSpecialChars, resourceId );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructMenuSctRowL
// Creates an sct row for editing menu.
// @param aSpecialChars Buffer that holds selected characters
// @since 3.1
// -----------------------------------------------------------------------------
//

EXPORT_C void CEikMenuPane::ConstructMenuSctRowL( TDes& aSpecialChars, TInt aResourceId )
    {
    CheckCreateScrollerL();
    CheckCreateExtensionL();
    iExtension->ConstructMenuSctRowL( aSpecialChars, aResourceId );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructMenuSctRowFromDialogL
// Creates an sct row for editing menu.
// @param aSpecialChars Buffer that holds selected characters
// @since 3.1
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::ConstructMenuSctRowFromDialogL( TDes& aSpecialChars, TInt aResourceId )
    {
    CheckCreateScrollerL();
    CheckCreateExtensionL();
    iExtension->ConstructMenuSctRowFromDialogL( aSpecialChars, aResourceId );
    }

// -----------------------------------------------------------------------------
// CEikMenuPane::ConstructMenuSctRowFromDialogL
// Creates an sct row for editing menu.
// @param aSpecialChars Buffer that holds selected characters
// @since 3.1
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::ConstructMenuSctRowFromDialogL( TInt aCharCase, TDes& aSpecialChars, TInt aResourceId )
    {
    ConstructMenuSctRowFromDialogL( aSpecialChars, aResourceId);
    iExtension->iSct->SetCharacterCaseL(aCharCase);
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemSpecific
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMenuPane::SetItemSpecific(
        TInt aCommandId, TBool aItemSpecific )
    {
    if ( !iExtension )
        {
        TRAPD( err, CheckCreateExtensionL() );
        if ( err )
            {
            return;
            }
        }
    
    if ( iExtension->iFlags.IsSet(
            CEikMenuPaneExtension::ESingleClickEnabled ) )
        {
        CEikMenuPaneItem::SData& itemData = ItemData( aCommandId );
        if ( aItemSpecific )
            {
            // item specific command cannot be item action command
            itemData.iFlags &= ( ~EEikMenuItemAction );
            itemData.iFlags |= EEikMenuItemSpecific;
            }
        else
            {
            // clear both item specific flags
            itemData.iFlags &= ( ~EEikMenuItemSpecific );
            itemData.iFlags &= ( ~EEikMenuItemSpecificListQuery );
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::MenuItemCommandId
// Returns the command id of the specified menu item.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CEikMenuPane::MenuItemCommandId( const TInt aIndex ) const
    {
    if ( !iItemArray || aIndex >= iItemArray->Count() || aIndex < 0 )
        {
        Panic( EEikPanicInvalidIndex );
        }
    CEikMenuPaneItem* item = (*iItemArray)[aIndex];
    if ( !item )
        {
        Panic( EEikPanicNullPointer );
        }
    return item->iData.iCommandId;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetEmbeddedCba
// -----------------------------------------------------------------------------
//
void CEikMenuPane::SetEmbeddedCba( CEikCba* aCba )
    {
    if ( iExtension )
        {
        iExtension->iCba = aCba;
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::CloseCascadeMenu
// -----------------------------------------------------------------------------
//
void CEikMenuPane::CloseCascadeMenu( TBool aMainMenuClosing )
    {
    if ( iCascadeMenuPane == NULL )
        {
        return;
        }
    if( iCascadeMenuPane->iCascadeMenuPane)
        {
        return iCascadeMenuPane->CloseCascadeMenu();    
        }

    // This CloseCascadeMenu method is called from CEikMenuPane destructor.
    // CEikMenuPane may be destroyed in AppUi's destructor.
    // Thus, skin instance may not be valid any more when this function is called
    // and all drawing should be avoided in such situation.
    TBool okToDraw = EFalse;

    //iExtension->StartCascadeMenuDisappearTransition();
    if ( iCascadeMenuPane->IsVisible() )
        {
        okToDraw = AknsUtils::SkinInstance() != NULL;
        // Stop ongoing comp. transitions, this is mostly for fast clicking
        // cases to make sure that no "scrap" is left behind.
        GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );

        // cascade menu "cancel" animation. This does not apply
        // when something is chosen from the menu
        if ( iExtension->iShowCascadeTransition && okToDraw )
            {
            iCascadeMenuPane->SetParent( this );
    
            GfxTransEffect::Begin( iCascadeMenuPane, KGfxControlDisappearAction );
            GfxTransEffect::SetDemarcation( iCascadeMenuPane, iExtension->iCascadeDRect );
            iCascadeMenuPane->MakeVisible( EFalse );
            GfxTransEffect::End( iCascadeMenuPane );
            }
        }

        // deregister right away since cascade menu is deleted
    GfxTransEffect::Deregister( iCascadeMenuPane );
    iExtension->iShowCascadeTransition = EFalse;

    //For transitions, keep the cascade menu object alive a little
    // longer so that the transition system does not ever refer to
    // deleted object
    iExtension->iCascadeMenuObject = iCascadeMenuPane;

    
    iCascadeMenuPane->MakeVisible( EFalse );
    iCascadeMenuPane = NULL;

    if ( !aMainMenuClosing )
        {
        // Submenu is closed.Parent menu pane will grab window.
        // ClaimPointerGrab invokes pointer up event.
        ClaimPointerGrab(ETrue); 
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::NewItemCommandMenuL
// -----------------------------------------------------------------------------
//
CEikMenuPane* CEikMenuPane::NewItemCommandMenuL( MEikMenuObserver* aObserver )
    {
    CEikMenuPane* menuPane = new ( ELeave ) CEikMenuPane( aObserver );
    CleanupStack::PushL( menuPane );
    menuPane->iExtension = new ( ELeave ) CEikMenuPaneExtension();
    menuPane->iExtension->iFlags.Set(
            CEikMenuPaneExtension::ESingleClickEnabled );
    menuPane->CreateItemArrayL();
    CleanupStack::Pop( menuPane );
    return menuPane;
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetItemCommandsDimmed
// -----------------------------------------------------------------------------
//
void CEikMenuPane::SetItemCommandsDimmed()
    {
    if ( iExtension && iExtension->iFlags.IsSet(
            CEikMenuPaneExtension::ESingleClickEnabled ) )
        {
        iExtension->iFlags.Set(
                CEikMenuPaneExtension::EHideItemSpecificCommands );
        for ( TInt i = 0; i < iItemArray->Count(); ++i )
            {
            CEikMenuPaneItem* item = iItemArray->At( i );
            if ( item->iData.iFlags & EEikMenuItemAction
                    || item->iData.iFlags & EEikMenuItemSpecific
                    || item->iData.iFlags & EEikMenuItemSpecificListQuery )
                {
                item->iData.iFlags |= EEikMenuItemDimmed;
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::AddMenuItemsToItemActionMenuL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::AddMenuItemsToItemActionMenuL(
        CAknItemActionMenuData& aMenuData )
    {
    TInt menuItemCount( iItemArray->Count() );
    for ( TInt i = 0; i < menuItemCount; ++i )
        {
        CEikMenuPaneItem* item = iItemArray->At( i );
        // Add menu item if menu item is not dimmed and
        // 1) menu item belongs to cascade menu
        // 2) menu item is item specific command
        // 3) menu item is item specific list query
        if ( CEikMenuPaneExtension::ItemSpecificCommand( *item ) )
            {
            // If menu item is not list query and it has cascade menu
            // add cascade menu items to menu data directly
            if ( !( item->iData.iFlags & EEikMenuItemSpecificListQuery )
                    && item->iData.iCascadeId )
                {
                AddCascadeMenuItemsToActionMenuL(
                        item->iData.iCascadeId, EFalse, aMenuData );
                }
            // If menu item is list query or it does not have cascade menu
            else
                {
                aMenuData.AddMenuItemToDataArrayL(
                        item->iData.iCommandId,
                        item->iData.iCascadeId,
                        item->iData.iText );
                }
            }
        // If item is not item specific, add its item specific cascade menu
        // items if the item itself isn't dimmed.
        else if ( item->iData.iCascadeId && 
                !( item->iData.iFlags & EEikMenuItemDimmed ) )
            {
            AddCascadeMenuItemsToActionMenuL(
                    item->iData.iCascadeId, ETrue, aMenuData );
            }
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::AddCascadeMenuItemsToActionMenuL
// -----------------------------------------------------------------------------
//
void CEikMenuPane::AddCascadeMenuItemsToActionMenuL(
        TInt aCascadeId,
        TBool aItemSpecific,
        CAknItemActionMenuData& aMenuData )
    {
    if ( aCascadeId && iCoeEnv->IsResourceAvailableL( aCascadeId ) )
        {
        CEikMenuPane* cascadeMenu =
            CEikMenuPane::NewItemCommandMenuL( iMenuObserver );
        CleanupStack::PushL( cascadeMenu );
        cascadeMenu->AddMenuItemsL( aCascadeId, 0 );
        iMenuObserver->DynInitMenuPaneL( aCascadeId, cascadeMenu );

        TInt menuItemCount( cascadeMenu->iItemArray->Count() );
        for ( TInt i = 0; i < menuItemCount; ++i )
            {
            CEikMenuPaneItem* item = cascadeMenu->iItemArray->At( i );
            if ( ( aItemSpecific
                    && CEikMenuPaneExtension::ItemSpecificCommand( *item ) )
                || ( !aItemSpecific
                        && !( item->iData.iFlags & EEikMenuItemDimmed ) ) )
                {
                aMenuData.AddMenuItemToDataArrayL(
                        item->iData.iCommandId,
                        item->iData.iCascadeId,
                        item->iData.iText );
                }
            }
        CleanupStack::PopAndDestroy( cascadeMenu );
        }
    }


// -----------------------------------------------------------------------------
// CEikMenuPane::SetDefaultHighlight
// -----------------------------------------------------------------------------
//
void CEikMenuPane::SetDefaultHighlight()
    {
    if ( iExtension )
        {
        iExtension->SetDefaultHighlight();
        }
    }

// end of file

