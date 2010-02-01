/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the decorator class for navigation
*                pane controls.
*
*/


// SYSTEM INCLUDE FILES
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <touchfeedback.h>

#include <AknTasHook.h>
// USER INCLUDE FILES
#include "aknappui.h"
#include "aknconsts.h"
#include "aknnavilabel.h"
#include "aknnavide.h"
#include "AknNaviObserver.h"
#include "AknUtils.h"
#include "AknStatuspaneUtils.h"
#include "AknNaviDecoratorObserver.h"
#include "akntabgrp.h"
#include "akntitle.h"
#include "AknTitlePaneLabel.h"


const TInt KEikNavidePointerRepeatInterval = 500000;  // in micro seconds


// ============================= LOCAL FUNCTIONS ===============================

NONSHARABLE_CLASS( CAknNavigationDecoratorExtension ) : public CBase
    {
public:
    enum
        {
        ENaviDecoratorNoSide = 0,
        ENaviDecoratorLeftSide,
        ENaviDecoratorRightSide
        };
    
public:
    static CAknNavigationDecoratorExtension* NewL();
    ~CAknNavigationDecoratorExtension();
    
private:
    CAknNavigationDecoratorExtension();
    CAknNavigationDecoratorExtension( const CAknNavigationDecoratorExtension* aExtension );
    
public:
    CPeriodic* iTimer;
    TInt iEffectTimerCount;
    TInt iOutermostRepeats;
    TInt iBlinkingSide;
    };

CAknNavigationDecoratorExtension* CAknNavigationDecoratorExtension::NewL()
    {
    CAknNavigationDecoratorExtension* naviExtension = 
        new (ELeave) CAknNavigationDecoratorExtension();
    return naviExtension;
    }

CAknNavigationDecoratorExtension::CAknNavigationDecoratorExtension() : 
    iTimer(NULL), iEffectTimerCount(0), iOutermostRepeats(0), iBlinkingSide(0)
    {
    }

CAknNavigationDecoratorExtension::~CAknNavigationDecoratorExtension()
    {
    }
    
// -----------------------------------------------------------------------------
// IsMaskAllBlack
//
// Checks whether the given bitmap is all black (first row ignored).
// The width of the bitmap is assumed to be 8 or less (sufficient for arrows).
//
// Returns: Boolean value.
// -----------------------------------------------------------------------------
//
static TBool IsMaskAllBlack( CFbsBitmap* bitmap )
    {
    if ( !bitmap )
        {
        return EFalse;
        }

    TSize size( bitmap->SizeInPixels() );

    if ( size.iWidth > 8 )
        {
        return EFalse;
        }
        
    TBuf8<8> scanLineBuf;

    for ( TInt y = 1; y < size.iHeight; y++ )
        {
        bitmap->GetScanLine( scanLineBuf,
                             TPoint( 0, y ),
                             size.iWidth,
                             EGray256 );
        for ( TInt x = 0; x < size.iWidth; x++ )
            {
            if ( scanLineBuf[x] != 0 )
                {
                return EFalse;
                }
            }
        }

    return ETrue;
    }

// ============================ MEMBER FUNCTIONS ===============================

EXPORT_C CAknNavigationDecorator* CAknNavigationDecorator::NewL(
    CAknNavigationControlContainer* /*aNavigationControlContainer*/,
    CCoeControl* aDecoratedControl,
    TControlType aType )
    {
    CleanupStack::PushL( aDecoratedControl );
    CAknNavigationDecorator* self = new (ELeave) CAknNavigationDecorator;

    self->iDecoratedControl = aDecoratedControl;

    CleanupStack::Pop( aDecoratedControl );
    
    // Control type must be set before calling constructor.
    self->iControlType = aType;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self ); // self
    AKNTASHOOK_ADDL( self, "CAknNavigationDecorator" );
    return self;
    }

EXPORT_C CAknNavigationDecorator::~CAknNavigationDecorator()
    {
    AKNTASHOOK_REMOVE();
    if ( iContainer )
        {
        iContainer->Pop( this );
        }

    if ( iLayoutStyleTimer )
        {
        iLayoutStyleTimer->Cancel();
        delete iLayoutStyleTimer;
        }
        
    if( iExtension && iExtension->iTimer )
        {
        if ( iExtension->iTimer->IsActive() )
            {
            CancelTimer();
            }

        delete iExtension->iTimer;
        }
    
    delete iExtension;    
    delete iDecoratedControl;
    }


EXPORT_C void CAknNavigationDecorator::ConstructL()
    {
    iDecoratedControl->SetObserver( this );

    iNaviArrowsVisible    = EFalse;
    iNaviArrowLeftDimmed  = ETrue;
    iNaviArrowRightDimmed = ETrue;
    
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    
    iLayoutStyleTimer = CPeriodic::NewL( CActive::EPriorityIdle );
    if ( AknStatuspaneUtils::FlatLayoutActive() &&
         !isLandscape )
        {
        iLayoutFlags |= ENaviControlLayoutNarrow;
        iLayoutFlags |= ENaviControlLayoutModeForced;
        }

    // Wide layout is used in usual portrait mode,
    // except for tabs in non-touch layouts.
    else if ( AknStatuspaneUtils::UsualLayoutActive() &&
              !isLandscape &&
              ( iControlType != ETabGroup ||
                AknLayoutUtils::PenEnabled() ) )
        {
        iLayoutFlags |= ENaviControlLayoutWide;
        iLayoutFlags |= ENaviControlLayoutModeForced;
        }
    else
        {        
        iLayoutFlags |= ENaviControlLayoutNormal;
        iLayoutFlags |= ENaviControlLayoutModeAutomatic;
        }
    
    iExtension = CAknNavigationDecoratorExtension::NewL();
    
    ActivateL();
    }

EXPORT_C CCoeControl* CAknNavigationDecorator::DecoratedControl()
    {
    // In case the decorated control is of the ENaviVolume type, this
    // function returns the CAknVolumeControl object which is a component
    // control of the volume popup, instead of the volume popup control itself.
    // This is in order to maintain BC.
    if ( iControlType == ENaviVolume )
        {
        CCoeControl* volumeControl = iDecoratedControl->ComponentControl( 5 );
        
        if ( volumeControl )
            {
            return volumeControl;
            }
        }

    return iDecoratedControl;
    }

EXPORT_C void CAknNavigationDecorator::MakeScrollButtonVisible( TBool aVisible )
    {
    TBool differ = ( iNaviArrowsVisible != aVisible );
    
    iNaviArrowsVisible = aVisible;
    
    if ( iControlType == ENaviLabel )
        {
        if ( iNaviArrowsVisible )
            {
            STATIC_CAST( CAknNaviLabel*, iDecoratedControl )->
                SetNaviLabelType( CAknNaviLabel::ENavigationLabel );
            }
        else
            {
            STATIC_CAST( CAknNaviLabel*, iDecoratedControl )->
                SetNaviLabelType( CAknNaviLabel::EAdditionalInfoLabel );
            }
        }
    else if ( iControlType == ETabGroup )
        {
        static_cast<CAknTabGroup*>(
            iDecoratedControl )->SetNaviArrowsVisible( aVisible );
        }

    if ( differ )
        {
        SizeChanged();
        }
    }

EXPORT_C TBool CAknNavigationDecorator::ScrollButtonVisible() const
    {
    return iNaviArrowsVisible;
    }

EXPORT_C void CAknNavigationDecorator::SetScrollButtonDimmed(
    TScrollButton aButton,
    TBool aDimmed )
    {
    if ( aButton == ELeftButton )
        {
        iNaviArrowLeftDimmed = aDimmed;

        if ( aDimmed )
            {
            iExtension->iBlinkingSide = 
                CAknNavigationDecoratorExtension::ENaviDecoratorRightSide;
            }
        }
    if ( aButton == ERightButton )
        {
        iNaviArrowRightDimmed = aDimmed;

        if ( aDimmed )
            {
            iExtension->iBlinkingSide = 
                CAknNavigationDecoratorExtension::ENaviDecoratorLeftSide;
            }
        }
    }

EXPORT_C TBool CAknNavigationDecorator::IsScrollButtonDimmed(
    TScrollButton aButton ) const
    {
    if ( aButton == ELeftButton )
        {
        return iNaviArrowLeftDimmed;
        }
    if ( aButton == ERightButton )
        {
        return iNaviArrowRightDimmed;
        }
    return ETrue;
    }

EXPORT_C void CAknNavigationDecorator::SetControlType( TControlType aType )
    {
    iControlType = aType;
    }

EXPORT_C CAknNavigationDecorator::TControlType CAknNavigationDecorator::ControlType() const
    {
    return iControlType;
    }

EXPORT_C void CAknNavigationDecorator::SizeChanged()
    {
    if ( iControlType == ENaviVolume )
        {
        // The control for ENaviVolume type does not reside in the navi pane
        // anymore, so the control size doesn't need to be adjusted if navi pane
        // size changes.
        return;
        }
    
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool flatLayout( AknStatuspaneUtils::FlatLayoutActive() );
    
    if ( isLandscape &&
         flatLayout &&
         !AknLayoutUtils::PenEnabled() &&
         NaviControlLayoutMode() == ENaviControlLayoutModeAutomatic &&
         NaviControlLayoutStyle() == ENaviControlLayoutNormal )
        {
        if ( iLayoutStyleTimer && !iLayoutStyleTimer->IsActive() )
            {
            InitLayoutStyleTimer();
            }            
        }
    else
        {
        CancelLayoutStyleTimer();
        }    
    
    TBool wideInUseInLsc( EFalse );
    
    if ( NaviControlLayoutStyle() != ENaviControlLayoutNarrow &&
         flatLayout &&
         !isLandscape )
        {
        iLayoutFlags &= ~ENaviControlLayoutNormal;
        iLayoutFlags &= ~ENaviControlLayoutWide;
        iLayoutFlags |= ENaviControlLayoutNarrow;
        }

    // Only flat layout supports narrow mode for now.
    if ( NaviControlLayoutStyle() == ENaviControlLayoutNarrow )
        {
        if ( !flatLayout ||
             ( isLandscape && AknLayoutUtils::PenEnabled() ) )
            {
            iLayoutFlags &= ~ENaviControlLayoutNarrow;           
            iLayoutFlags |= ENaviControlLayoutNormal; 
            }
        }
    // Wide layout is supported only in portrait mode.
    else if ( NaviControlLayoutStyle() == ENaviControlLayoutWide )
        {
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            wideInUseInLsc = ETrue;
            }
        }
    
    if ( NaviControlLayoutStyle() == ENaviControlLayoutNarrow &&
         NaviControlLayoutStyleSupported( ENaviControlLayoutNarrow ) )
        {
        SizeChangedInNarrowLayout();
        }
    else if ( NaviControlLayoutStyle() == ENaviControlLayoutWide &&
              !wideInUseInLsc )
        {
        SizeChangedInWideLayout();
        }
    else // Normal layout
        {
        SizeChangedInNormalLayout();
        }

    // Finally call the navi arrow bitmap getter, as it will
    // resize the navi arrows to correct size.
    if ( iContainer )
        {
        iContainer->NaviArrowBitmap( 0 );
        iContainer->NaviArrowBitmap( 1 );
        }
    }

void CAknNavigationDecorator::SizeChangedInNormalLayout()
    {
    TRect rect;
    TRect leftArrowRect;
    TRect rightArrowRect;
    
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane && 
         statusPane->CurrentLayoutResId() == R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT &&
         iControlType == ETabGroup )
        {
        // At the moment this special handling is required for tab group
        // in portrait mode, because tabs don't support wide navi pane layout yet.
        TAknLayoutRect layoutRect;
            
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
        
        TBool isHDLayoutActive( AknStatuspaneUtils::HDLayoutActive() );
                    
        TAknWindowComponentLayout topArea( 
            AknLayoutScalable_Avkon::area_top_pane( isHDLayoutActive ? 8 : 0 ) );
        TAknWindowComponentLayout spLayout(
            AknLayoutScalable_Avkon::status_pane( isHDLayoutActive ? 1 : 0 ) );
            
        TAknWindowComponentLayout layout(
                TAknWindowComponentLayout::Compose( topArea, spLayout ) );
                
        layoutRect.LayoutRect( screenRect, layout );
        TRect spRect( layoutRect.Rect() );
                
        layoutRect.LayoutRect(
            spRect,
            AknLayoutScalable_Avkon::navi_pane( isHDLayoutActive ? 8 : 5 ) );
        rect = layoutRect.Rect();
        rect.Move( -rect.iTl.iX, -rect.iTl.iY );
        leftArrowRect  = NaviArrowRect( ELeftButton,  EFalse, rect );
        rightArrowRect = NaviArrowRect( ERightButton, EFalse, rect );
        }
    else
        {
        rect = ParentRect();
        
        if ( iControlType == ENaviVolume &&
             !Layout_Meta_Data::IsLandscapeOrientation() &&
             AknStatuspaneUtils::SmallLayoutActive() )
            {
            // Small status pane volume control has it's own positions for
            // navi arrows, but in landscape the data doesn't exist
            // so normal navi arrow positions are used.
            
            // These layout data items aren't mirrored.
            TBool layoutMirrored( AknLayoutUtils::LayoutMirrored() );
            
            TRect naviPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::ENaviPane,
                                               naviPaneRect );
                                               
            naviPaneRect.Move( -naviPaneRect.iTl.iX,
                               -naviPaneRect.iTl.iY );
            
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(
                naviPaneRect,
                layoutMirrored ?
                    AknLayoutScalable_Avkon::status_small_pane_g6( 0 ) :
                    AknLayoutScalable_Avkon::status_small_pane_g5( 0 ) );
            leftArrowRect = layoutRect.Rect();

            layoutRect.LayoutRect(
                naviPaneRect,
                layoutMirrored ?
                    AknLayoutScalable_Avkon::status_small_pane_g5( 0 ) :
                    AknLayoutScalable_Avkon::status_small_pane_g6( 0 ) );
            rightArrowRect = layoutRect.Rect();   
            }
        else
            {
            leftArrowRect = NaviArrowRect( ELeftButton );
            rightArrowRect = NaviArrowRect( ERightButton );
            }
        }

    if ( iControlType == ETabGroup )
        {
        rect = DecoratedTabControlRect( AknLayoutUtils::PenEnabled(),
                                        ETrue );
        }

    iArrowRightSize = rightArrowRect.Size();
    iArrowLeftSize  = leftArrowRect.Size();
    
    iArrowRightPos = TPoint( rightArrowRect.iTl.iX, rect.iTl.iY );
    iArrowLeftPos  = TPoint( leftArrowRect.iTl.iX, rect.iTl.iY );
    
    TSize rectSize( rect.Size() );
    
    // In case the decorated control is tab group, the tab layout mode
    // must be set before it's size is set.
    if ( iControlType == ETabGroup )
        {
        CAknTabGroup* tabGroup = static_cast <CAknTabGroup*> (iDecoratedControl);
        TRAP_IGNORE( tabGroup->SetNarrowTabLayoutL( EFalse ) );
        }
    
    if ( ScrollButtonVisible() )
        {
        iDecoratedControl->SetRect( rect );
        }
    else
        {
        iDecoratedControl->SetRect( Rect() );
        }
    }


void CAknNavigationDecorator::SizeChangedInNarrowLayout()
    {
    TRect rect( DecoratedControlNarrowRect( this->ControlType() ) );
    
    TRect leftArrowRect( NaviArrowRect( ELeftButton, ETrue ) );
    TRect rightArrowRect( NaviArrowRect( ERightButton, ETrue ) );

    iArrowRightSize = rightArrowRect.Size();
    iArrowRightPos  = rightArrowRect.iTl;
    
    iArrowLeftSize  = leftArrowRect.Size();
    iArrowLeftPos   = leftArrowRect.iTl;

    // Tab group is handled specificly... 
    if ( iControlType == ETabGroup )
        {
        // Note. Size is set bigger than normally. 
        // Tabs take this into account in layout calculations (akntabgrp.cpp).
        iDecoratedControl->SetRect( Rect() ); 
        CAknTabGroup* tabGroup = static_cast <CAknTabGroup*> (iDecoratedControl);
        // This sets tab size using animation.
        TBool useAnimation( Layout_Meta_Data::IsLandscapeOrientation() );
        TRAP_IGNORE( tabGroup->SetNarrowTabLayoutL( ETrue, useAnimation ) );
        }
    else
        {
        if ( ScrollButtonVisible() )
            {
            iDecoratedControl->SetRect( TRect( iArrowLeftPos.iX + iArrowLeftSize.iWidth,
                                               rect.iTl.iY,
                                               iArrowRightPos.iX,
                                               rect.iBr.iY ) );
            }
        else
            {
            iDecoratedControl->SetRect( rect );
            }
        }                 
    }


void CAknNavigationDecorator::SizeChangedInWideLayout()
    {
    TRect rect( Rect() );
    TRect parentRect;

    if ( iControlType == ETabGroup &&
         !AknLayoutUtils::PenEnabled() )
        {
        parentRect = DecoratedTabControlRect( EFalse, ETrue );
        }
    else
        {
        parentRect = ParentRect();
        }

    if ( rect.Width()  < parentRect.Width() ||
         rect.Height() < parentRect.Height() )
        {
        rect = parentRect;
        }

    TRect leftArrowRect( NaviArrowRect( ELeftButton ) );
    TRect rightArrowRect( NaviArrowRect( ERightButton ) );

    iArrowRightSize = rightArrowRect.Size();
    iArrowLeftSize  = leftArrowRect.Size();

    if ( ScrollButtonVisible() )
        {
        rect.iTl.iX += iArrowRightSize.iWidth;
        rect.iBr.iX -= iArrowLeftSize.iWidth;
        }
    
    if ( parentRect.Height() < rect.Height() )
        {
        iArrowRightPos = TPoint( rect.iBr.iX, parentRect.iTl.iY );
        iArrowLeftPos = TPoint( rect.iTl.iX - iArrowLeftSize.iWidth, parentRect.iTl.iY );
        }
    else
        {
        iArrowRightPos = TPoint( rect.iBr.iX, rightArrowRect.iTl.iY );
        iArrowLeftPos = TPoint( rect.iTl.iX - iArrowLeftSize.iWidth, iArrowRightPos.iY );
        }

    // In case the decorated control is tab group, the tab layout mode
    // must be set before it's size is set.
    if ( iControlType == ETabGroup )
        {
        CAknTabGroup* tabGroup = static_cast <CAknTabGroup*> ( iDecoratedControl );
        TRAP_IGNORE( tabGroup->SetNarrowTabLayoutL( EFalse) );
        }

    iDecoratedControl->SetRect( rect );
    }

EXPORT_C TInt CAknNavigationDecorator::CountComponentControls() const
    {
    if ( iContainer && iDecoratedControl )
        {
        return 1;
        }

    return 0;
    }


EXPORT_C CCoeControl* CAknNavigationDecorator::ComponentControl(TInt /*aIndex*/) const
    {
    // DecoratedControl() isn't declared as const but doesn't actually
    // change anything.
    return ( const_cast<CAknNavigationDecorator*>(this)->DecoratedControl() );
    }


EXPORT_C void* CAknNavigationDecorator::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

   
// ---------------------------------------------------------------------------
// CAknNavigationDecorator::HandlePointerEventL
// Handles pointer events by checking first if the pointer event was
// in the arrow areas and sending the arrow event to observer,
// and if not sending the pointer event to all child components.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationDecorator::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        TRect naviPaneRect( ParentRect() );
        TRect parentRect = naviPaneRect;
        
        TRect statusPaneRect;
        AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EStatusPane, statusPaneRect );
        
        // In certain status pane layouts the navi pane has extended
        // touch responsive area in the layout data which is larger
        // than the actual decorator size.
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        if ( statusPane )
            {
            TInt currentLayoutResId( statusPane->CurrentLayoutResId() );
            
            if ( currentLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ||
                 currentLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE )
                {
                TAknLayoutRect layoutRect;
                layoutRect.LayoutRect(
                    statusPaneRect,
                    AknLayoutScalable_Avkon::aid_touch_navi_pane() );
                parentRect = layoutRect.Rect();
                
                // Make the parent rect navi pane relative and move it so
                // that the bottom sides of the real navi pane area and the
                // touch pane responsive area are aligned. This means
                // that the iTl.iY will become negative, which is required
                // for pointer events in which the down event happens
                // inside the decorator rect, but the up event in the
                // extended area above the decorator rect.
                parentRect.Move( -parentRect.iTl.iX,
                                 -( parentRect.iTl.iY +
                                    ( parentRect.Height() -
                                      naviPaneRect.Height() ) ) );
                }
            }

        TRect rightArrowTabRect( iArrowRightPos, iArrowRightSize );
        TRect leftArrowTabRect( iArrowLeftPos, iArrowLeftSize );
        
        // Get tab arrow touch aid rects from layout data, they extend the
        // arrow areas bit to the decorated control's area to make the arrows
        // more "finger usable".
        TAknLayoutRect arrowAidLayout;
        arrowAidLayout.LayoutRect(
            statusPaneRect,
            AknLayoutScalable_Avkon::aid_touch_tab_arrow_left(
                Layout_Meta_Data::IsLandscapeOrientation() ? 2 : 0 ) );
        
        // The arrows are the same size so use only the other's width.
        TInt aidWidth( arrowAidLayout.Rect().Width() );
        
        rightArrowTabRect.iTl.iX -= aidWidth;
        leftArrowTabRect.iBr.iX  += aidWidth;
                
        TBool rightArrowTapped(
            iNaviArrowsVisible &&
            !iNaviArrowRightDimmed &&
            rightArrowTabRect.Contains( aPointerEvent.iPosition ) );
            
        TBool leftArrowTapped(
            iNaviArrowsVisible &&
            !iNaviArrowLeftDimmed &&
            leftArrowTabRect.Contains( aPointerEvent.iPosition ) );
        
        // Inform controls if tapped to arrows.
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down ||
             aPointerEvent.iType == TPointerEvent::EButtonRepeat )
            {
            // Detects whether tap hits left arrow.
            if ( leftArrowTapped && iNaviDecoratorObserver )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback &&
                     ( iDecoratedControl && !iDecoratedControl->IsDimmed() ) )
                    {
                    TTouchLogicalFeedback feedbackType =
                        ( aPointerEvent.iType == TPointerEvent::EButtonRepeat ?
                              ETouchFeedbackSensitiveButton :
                              ETouchFeedbackBasicButton );
                    feedback->InstantFeedback( this, feedbackType, aPointerEvent );
                    }

                iNaviDecoratorObserver->HandleNaviDecoratorEventL(
                    MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow );

                // Request pointer repeat to implement longtapping
                Window().RequestPointerRepeatEvent(
                    KEikNavidePointerRepeatInterval, leftArrowTabRect );

                // Don't pass the event to children as the tap point
                // may be in the decorated control's area and it's
                // already handled here.
                }
            // Detects whether tap hits right arrow.
            else if ( rightArrowTapped && iNaviDecoratorObserver )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback &&
                     ( iDecoratedControl && !iDecoratedControl->IsDimmed() ) )
                    {
                    TTouchLogicalFeedback feedbackType =
                        ( aPointerEvent.iType == TPointerEvent::EButtonRepeat ?
                              ETouchFeedbackSensitiveButton :
                              ETouchFeedbackBasicButton );
                    feedback->InstantFeedback( this, feedbackType, aPointerEvent );
                    }

                iNaviDecoratorObserver->HandleNaviDecoratorEventL(
                    MAknNaviDecoratorObserver::EAknNaviDecoratorEventRightTabArrow );

                // Request pointer repeat to implement longtapping
                Window().RequestPointerRepeatEvent(
                    KEikNavidePointerRepeatInterval, rightArrowTabRect );

                // Don't pass the event to children as the tap point
                // may be in the decorated control's area and it's
                // already handled here.
                }
            else
                {
                // Pass the pointer events to children.
                CCoeControl::HandlePointerEventL( aPointerEvent );
                }

            // check if navi label was hit
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            if ( iControlType == ENaviLabel )
                {
                if ( parentRect.Contains( aPointerEvent.iPosition ) &&
                     iNaviDecoratorObserver )
                    {
                    iNaviDecoratorObserver->HandleNaviDecoratorEventL(
                        MAknNaviDecoratorObserver::EAknNaviDecoratorEventNaviLabel );
                    }
                }
            else if( !rightArrowTapped && !leftArrowTapped )
                {
                CCoeControl::HandlePointerEventL( aPointerEvent );
                }
            
            // feedback is also given on up event from arrows
            if ( rightArrowTapped || leftArrowTapped )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback &&
                     ( iDecoratedControl && !iDecoratedControl->IsDimmed() ) )
                    {
                    feedback->InstantFeedback( this, 
                                               ETouchFeedbackBasicButton,
                                               ETouchFeedbackVibra,
                                               aPointerEvent );
                    }
                }
            }
        else
            {
            if ( !rightArrowTapped && !leftArrowTapped )
                {
                // Pass other pointer events to children if it
                // happened outside the arrow areas.
                CCoeControl::HandlePointerEventL( aPointerEvent );
                }
            }
        }
    }


EXPORT_C void CAknNavigationDecorator::HandleControlEventL(
    CCoeControl* /*aControl*/, TCoeEvent aEventType )
    {
    TInt event = aEventType;
    switch ( event )
        {
        case MAknNavigationObserver::ENaviEventHandleNavigation:
            {
            iNaviArrowRightDimmed = EFalse;
            iNaviArrowLeftDimmed  = EFalse;
            break;
            }
        case MAknNavigationObserver::ENaviEventRightMostItemReached:
            {
            iNaviArrowRightDimmed = ETrue;
            iNaviArrowLeftDimmed  = EFalse;
            break;
            }
        case MAknNavigationObserver::ENaviEventLeftMostItemReached:
            {
            iNaviArrowRightDimmed = EFalse;
            iNaviArrowLeftDimmed  = ETrue;
            break;
            }
        case MAknNavigationObserver::ENaviEventOneItemExists:
            {
            iNaviArrowRightDimmed = ETrue;
            iNaviArrowLeftDimmed  = ETrue;
            break;
            }
        case MAknNavigationObserver::ENaviEventAlreadyLeftmostItem:
            {
#ifdef RD_ANIMATION_EFFECTS 
            iExtension->iBlinkingSide = 
                    CAknNavigationDecoratorExtension::ENaviDecoratorRightSide;           
            StartTimerL();
            return;
#else
            break;
#endif // RD_ANIMATION_EFFECTS
            }
        case MAknNavigationObserver::ENaviEventAlreadyRightmostItem:
            {
#ifdef RD_ANIMATION_EFFECTS
            iExtension->iBlinkingSide = 
                    CAknNavigationDecoratorExtension::ENaviDecoratorLeftSide;
            StartTimerL();
            return;
#else // RD_ANIMATION_EFFECTS
            break;
#endif
            }
        case MAknNavigationObserver::ENaviEventRedrawNeeded:
            break;
        default:
            break;
        }
    
    ReportEventL( MCoeControlObserver::EEventStateChanged );
    
    MCoeControlObserver* observer = Observer();
    // If event was not sent yet to the navigation control container, send it now
    if ( iContainer && observer != iContainer )
        {
        SetObserver( iContainer );
        ReportEventL( MCoeControlObserver::EEventStateChanged );
        SetObserver( observer );
        }
    }


EXPORT_C void CAknNavigationDecorator::Draw( const TRect& /*aRect*/ ) const
    {
    // Draw navigation pane scroll indicator arrows if visible
    if ( iNaviArrowsVisible && iContainer )
        {
        CWindowGc& gc = SystemGc();
        
        CFbsBitmap* colorbmp = iContainer->NaviColorBitmap();

        if ( !iNaviArrowLeftDimmed )
            {
            CFbsBitmap* arrowBmp = &( iContainer->NaviArrowBitmap( 0 ) );
            CFbsBitmap* arrowMask = &( iContainer->NaviArrowBitmap( 1 ) );
            
            TPoint arrowPos( iArrowLeftPos );
            
            if ( arrowBmp )
                {
                TInt arrowHeight( arrowBmp->SizeInPixels().iHeight );
                if ( arrowHeight < Size().iHeight )
                    {
                    arrowPos.iY = ( Size().iHeight - arrowHeight ) / 2;
                    }
                }
                    
            if( colorbmp && !IsMaskAllBlack( arrowMask ) )
                {
                gc.BitBltMasked(
                    arrowPos,
                    colorbmp, 
                    TRect( iArrowLeftSize ),
                    arrowMask,
                    ETrue );
                }
            else
                {
                gc.BitBltMasked(
                    arrowPos,
                    arrowBmp, 
                    TRect( iArrowLeftSize ),
                    arrowMask,
                    ETrue );
                }
            }
        
        if ( !iNaviArrowRightDimmed )
            {
            CFbsBitmap* arrowBmp = &( iContainer->NaviArrowBitmap( 2 ) );
            CFbsBitmap* arrowMask = &( iContainer->NaviArrowBitmap( 3 ) );
            
            TPoint arrowPos( iArrowRightPos );
            
            if ( arrowBmp )
                {
                TInt arrowHeight( arrowBmp->SizeInPixels().iHeight );
                if ( arrowHeight < Size().iHeight )
                    {
                    arrowPos.iY = ( Size().iHeight - arrowHeight ) / 2;
                    }
                }
            
            if( colorbmp && !IsMaskAllBlack( arrowMask ) )
                {
                gc.BitBltMasked(
                    arrowPos,
                    colorbmp, 
                    TRect( iArrowRightSize ),
                    arrowMask,
                    ETrue );
                }
            else
                {
                gc.BitBltMasked(
                    arrowPos,
                    arrowBmp,
                    TRect( iArrowRightSize ),
                    arrowMask,
                    ETrue );
                }
            }
        }
    }

void CAknNavigationDecorator::SetNaviStack(
    CAknNavigationControlContainer* aContainer )
    {
    iContainer = aContainer;

    if ( iContainer &&
         iControlType == ETabGroup )
        {
        CAknTabGroup* tabGroup =
            static_cast <CAknTabGroup*> ( iDecoratedControl );
        tabGroup->SetDecoratorLayout( iLayoutFlags & ENaviControlLayoutNarrow );
        }
    }

// ---------------------------------------------------------------------------
// CAknNavigationDecorator::SetNaviDecoratorObserver
// Sets observer for navidecorator.
// ---------------------------------------------------------------------------
//  
EXPORT_C void CAknNavigationDecorator::SetNaviDecoratorObserver(
    MAknNaviDecoratorObserver* aObserver )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        iNaviDecoratorObserver = aObserver;
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationDecorator::ParentRect
// Returns the navigation decorator rectangle.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationDecorator::ParentRect()
    {
    return DecoratedControlRect( iControlType, iNaviArrowsVisible );
    }


// ---------------------------------------------------------------------------
// CAknNavigationDecorator::DecoratedControlNarrowRect
// Returns the navigation decorator rectangle used in the narrow layout.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationDecorator::DecoratedControlNarrowRect(
    TInt /*aControlType*/ )
    {
    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );

    // Status pane area
    TRect statusPaneRect;
    AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EStatusPane, statusPaneRect );
        
    // Navi pane area
    TRect naviPaneRect;
    AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::ENaviPane, naviPaneRect );

    // Short navi pane
    TAknLayoutRect naviSrtRect;        
    naviSrtRect.LayoutRect(
        statusPaneRect,
        AknLayoutScalable_Avkon::navi_pane_srt( 0 ) );        

    TRect rect( naviSrtRect.Rect() );
        
    // Set relative to navipane coordinates
    rect.Move( -naviPaneRect.iTl.iX, 0 );
    rect.iTl.iY = 0;
    rect.SetHeight( naviSrtRect.Rect().Height() );

    return rect;
    }


// ---------------------------------------------------------------------------
// CAknNavigationDecorator::DecoratedControlRect
// Returns the rectangle of the navigation decorator in relation to the
// navi pane.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationDecorator::DecoratedControlRect( TInt aControlType,
                                                     TBool aArrowsUsed )
    {
    TRect rect;

    switch ( aControlType )
        {
        case ETabGroup:
            {
            rect = DecoratedTabControlRect( ETrue, aArrowsUsed );
            break;
            }
        case ENaviVolume:
            {
            rect = DecoratedVolumeControlRect();
            break;
            }
        default:
            {
            rect = DecoratedDefaultControlRect();
            break;
            }
        }

    return rect;
    }


// ---------------------------------------------------------------------------
// CAknNavigationDecorator::DecoratedControlRect
// Returns the default rectangle of the navigation decorator.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationDecorator::DecoratedDefaultControlRect()
    {
    TRect rect;
    
    TRect naviPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::ENaviPane, naviPaneRect );

    if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        // screen
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    
        // top area
        TAknLayoutRect topAreaLayoutRect;        
        topAreaLayoutRect.LayoutRect(
            screenRect,
            AknLayoutScalable_Avkon::area_top_pane( 1 ) );
        
        // small statuspane      
        TAknLayoutRect statusPaneLayoutRect;
        statusPaneLayoutRect.LayoutRect(
            topAreaLayoutRect.Rect(),
            AknLayoutScalable_Avkon::status_small_pane() );
        TRect statusPaneRect( statusPaneLayoutRect.Rect() );
        
        TAknWindowComponentLayout signalPaneLayout(
            AknLayoutScalable_Avkon::status_small_pane_g2( 0 ) );
        TAknLayoutRect signalPaneLayoutRect;
        signalPaneLayoutRect.LayoutRect( statusPaneRect, signalPaneLayout );

        rect = statusPaneRect; 

        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        if ( statusPane &&
             statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidSignal)).IsInCurrentLayout() )
            {
            TSize size( rect.Size() );
            size.iWidth -= signalPaneLayoutRect.Rect().Width();            
            rect.SetSize( size );
            }
        
        // Adjust the size for the navi pane content so that there's space for
        // the possible navi arrows.
        TInt arrowWidth = NaviArrowRect( ELeftButton ).Width();
        rect.iTl.iX += arrowWidth;
        rect.iBr.iX -= arrowWidth;
        }
    else if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        // navi navi pane
        TAknLayoutRect naviNaviLayoutRect;        
        naviNaviLayoutRect.LayoutRect(
            naviPaneRect,
            AknLayoutScalable_Avkon::navi_navi_pane() );        
        
        // pane for text and graphics
        TAknLayoutRect naviControlLayoutRect;        
        naviControlLayoutRect.LayoutRect(
            naviNaviLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane() );
        
        rect = naviControlLayoutRect.Rect();
        
        // Set relative to stacon navipane coordinates
        rect.Move( -naviPaneRect.iTl.iX,
                   -naviControlLayoutRect.Rect().iTl.iY ); 
        }       
    else
        {
        // navi navi pane
        TAknLayoutRect naviNaviLayoutRect;        
        naviNaviLayoutRect.LayoutRect(
            naviPaneRect,
            AknLayoutScalable_Avkon::navi_navi_pane() );        
        
        // pane for text and graphics
        TAknLayoutRect naviControlLayoutRect;        
        naviControlLayoutRect.LayoutRect(
            naviNaviLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane() );         
        TRect naviControlRect( naviControlLayoutRect.Rect() );
        
        rect = naviControlRect;
        rect.Move( -naviNaviLayoutRect.Rect().iTl.iX,
                   -naviControlRect.iTl.iY );
        }

    return rect;
    }


// ---------------------------------------------------------------------------
// CAknNavigationDecorator::DecoratedTabControlRect
// Returns the tab group rectangle in relation to the navi pane.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationDecorator::DecoratedTabControlRect( TBool aTopAdjacent,
                                                        TBool aArrowsUsed )
    {
    TRect rect;

    // "Stacon" statuspane
    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        TRect naviPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::ENaviPane,
                                           naviPaneRect );

        TInt variety = AknStatuspaneUtils::ExtendedStaconPaneActive() ? 1 : 0;

        TAknLayoutRect staconNaviTabRect;
        staconNaviTabRect.LayoutRect(
            naviPaneRect,
            AknLayoutScalable_Avkon::navi_navi_pane_stacon( variety ) );

        // tab pane
        TAknLayoutRect tabsPaneLayoutRect;
        tabsPaneLayoutRect.LayoutRect(
            staconNaviTabRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_tabs_pane() );
        TRect tabsRect( tabsPaneLayoutRect.Rect() );

        rect = tabsRect;

        // Set relative to stacon navipane coordinates
        rect.Move( -staconNaviTabRect.Rect().iTl.iX, -tabsRect.iTl.iY );
        }
    else
        {
        TBool penEnabled( AknLayoutUtils::PenEnabled() );
        TRect naviPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::ENaviPane,
                                           naviPaneRect );

        if ( !penEnabled )
            {
            // Tab pane is the only control which doesn't use the wide navi pane
            // layout in non-touch portrait mode, so we can't get the navi
            // pane rect directly from AknLayoutUtils.
            TRect statusPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane,
                                               statusPaneRect );

            TAknLayoutRect naviPaneLayoutRect;
            naviPaneLayoutRect.LayoutRect(
                statusPaneRect,
                AknLayoutScalable_Avkon::navi_pane( 5 ) );
            naviPaneRect = naviPaneLayoutRect.Rect();
            }
        
        if ( aArrowsUsed )
            {
            // navi navi pane
            TAknLayoutRect naviNaviPaneLayoutRect;
            naviNaviPaneLayoutRect.LayoutRect(
                naviPaneRect,
                AknLayoutScalable_Avkon::navi_navi_pane() );
    
            // tab pane
            TAknLayoutRect tabsPaneLayoutRect;
            tabsPaneLayoutRect.LayoutRect(
                naviNaviPaneLayoutRect.Rect(),
                AknLayoutScalable_Avkon::navi_navi_tabs_pane() );
            TRect tabsRect( tabsPaneLayoutRect.Rect() );
            
            rect = tabsRect;
            
            if ( aTopAdjacent )
                {
                rect.Move( -naviNaviPaneLayoutRect.Rect().iTl.iX,
                           -tabsRect.iTl.iY );
                }
            else
                {
                rect.Move( -naviNaviPaneLayoutRect.Rect().iTl.iX,
                           -( tabsRect.iTl.iY - ( naviPaneRect.Height() -
                                                  tabsRect.Height() ) ) );
                }
            }
        else
            {
            rect = naviPaneRect;
            rect.Move( -naviPaneRect.iTl.iX,
                       -naviPaneRect.iTl.iY );
            }
        }

    return rect;
    }


TRect CAknNavigationDecorator::DecoratedVolumeControlRect()
    {
    TRect rect;
    
    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    
    if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        // top area
        TAknLayoutRect topAreaLayoutRect;        
        topAreaLayoutRect.LayoutRect(
            screenRect,
            AknLayoutScalable_Avkon::area_top_pane( 1 ) );
        
        // small statuspane      
        TAknLayoutRect statusPaneLayoutRect;
        statusPaneLayoutRect.LayoutRect(
            topAreaLayoutRect.Rect(),
            AknLayoutScalable_Avkon::status_small_pane() );
        TRect statusPaneRect( statusPaneLayoutRect.Rect() );
        
        rect = statusPaneRect; 
        
        statusPaneLayoutRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::status_small_volume_pane() );
        rect = statusPaneLayoutRect.Rect();
        }
        
    else if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        // bottom area
        TAknLayoutRect bottomAreaLayoutRect;        
        bottomAreaLayoutRect.LayoutRect(
            screenRect,
            AknLayoutScalable_Avkon::area_bottom_pane( 2 ) );        
            
        // stacon bottom
        TAknLayoutRect staconBottomLayoutRect;
        staconBottomLayoutRect.LayoutRect(
            bottomAreaLayoutRect.Rect(),
            AknLayoutScalable_Avkon::stacon_bottom_pane() );
            
        TInt naviPaneVariety = AknStatuspaneUtils::StaconSoftKeysRight() ? 2 : 3;
        TAknLayoutRect staconNaviRect;        
        staconNaviRect.LayoutRect(
            staconBottomLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_pane_stacon( naviPaneVariety ) );        

        TAknLayoutRect staconNaviControlRect;        
        staconNaviControlRect.LayoutRect(
            staconNaviRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_pane() );
        
        TAknLayoutRect volumeControlRect;
        volumeControlRect.LayoutRect(
            staconNaviControlRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_volume_pane() );

        rect = volumeControlRect.Rect();
        
        // Set relative to stacon navipane coordinates
        rect.Move( -staconNaviRect.Rect().iTl.iX, 0 ); 
        rect.iTl.iY = 0;
        rect.SetHeight( volumeControlRect.Rect().Height() );
        }
        
    // "Flat" statuspane
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        TAknLayoutRect naviRect;        
        naviRect.LayoutRect(
            screenRect,
            AknLayoutScalable_Avkon::navi_pane( 2 ) );
        
        TAknLayoutRect naviNaviLayoutRect;        
        naviNaviLayoutRect.LayoutRect(
            naviRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_pane() );
        
        TAknLayoutRect volumeControlRect;
        volumeControlRect.LayoutRect(
            naviNaviLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_volume_pane() );
            
        rect = volumeControlRect.Rect();
        
        rect.Move( -naviNaviLayoutRect.Rect().iTl.iX, 0 ); 
        rect.iTl.iY = 0;
        rect.SetHeight( volumeControlRect.Rect().Height() );
        }
        
    else
        {        
        // Is battery pane visible in current layout
        TInt battery = AknStatuspaneUtils::ExtendedLayoutActive() ? 5 : 0; // classic or extended
        
        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            battery = AknStatuspaneUtils::ExtendedLayoutActive() ? 6 : 1; // classic or extended
            }
        else if ( AknStatuspaneUtils::UsualLayoutActive() &&
                  !Layout_Meta_Data::IsLandscapeOrientation() )
            {
            battery = 7;
            }

        if ( AknStatuspaneUtils::HDLayoutActive() && battery == 5 )
            {
            battery = 8;
            }

        // app window
        TAknLayoutRect applicationWindowLayoutRect;
        applicationWindowLayoutRect.LayoutRect(
            screenRect,
            AknLayoutScalable_Avkon::application_window( 0 ) );
        
        // statuspane
        TAknLayoutRect statusPaneLayoutRect;
        statusPaneLayoutRect.LayoutRect(
            applicationWindowLayoutRect.Rect(),
            AknLayoutScalable_Avkon::status_pane( 0 ) );
        
        // navi pane
        TAknLayoutRect naviPaneLayoutRect;
        naviPaneLayoutRect.LayoutRect(
            statusPaneLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_pane( battery ) );
        
        TAknLayoutRect naviNaviLayoutRect;        
        naviNaviLayoutRect.LayoutRect(
            naviPaneLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_pane() );
        
        TAknLayoutRect volumeControlRect;
        volumeControlRect.LayoutRect(
            naviNaviLayoutRect.Rect(),
            AknLayoutScalable_Avkon::navi_navi_volume_pane() );
        TRect volumeRect( volumeControlRect.Rect() );
        
        rect = volumeRect;
        
        rect.Move( -naviNaviLayoutRect.Rect().iTl.iX, -volumeRect.iTl.iY );
        }

    return rect;
    }

EXPORT_C void CAknNavigationDecorator::SetNaviControlLayoutStyle(
    TAknNaviControlLayoutStyle aStyle )
    {
    if ( AknStatuspaneUtils::FlatLayoutActive() &&
         !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // In portrait flat sp mode only narrow mode is allowed.
        iLayoutFlags &= ~ENaviControlLayoutNarrow;
        iLayoutFlags &= ~ENaviControlLayoutNormal;
        iLayoutFlags |= ENaviControlLayoutNarrow;
        }
    else if ( NaviControlLayoutStyleSupported( aStyle ) )
        {
        iLayoutFlags &= ~ENaviControlLayoutNarrow;
        iLayoutFlags &= ~ENaviControlLayoutNormal;
        iLayoutFlags &= ~ENaviControlLayoutWide;
        iLayoutFlags |= aStyle;        
        }
        
    if ( NaviControlLayoutMode() == ENaviControlLayoutModeAutomatic &&
         NaviControlLayoutStyle() == ENaviControlLayoutNormal )
        {
        InitLayoutStyleTimer();
        }
    else
        {
        CancelLayoutStyleTimer();
        }

    if ( iContainer )
        {
        iContainer->SetSize( iContainer->Size() );
        }
    else
        {
        SizeChanged();
        }
    }


EXPORT_C CAknNavigationDecorator::TAknNaviControlLayoutStyle CAknNavigationDecorator::NaviControlLayoutStyle()
    {
    if ( iLayoutFlags & ENaviControlLayoutNarrow )
        {
        return ENaviControlLayoutNarrow;
        }
    else if ( iLayoutFlags & ENaviControlLayoutWide )
        {
        return ENaviControlLayoutWide;
        }
    else
        {
        return ENaviControlLayoutNormal;
        }
    }


EXPORT_C void CAknNavigationDecorator::SetNaviControlLayoutMode(
    TAknNaviControlLayoutMode aMode )
    {
    iLayoutFlags &= ~ENaviControlLayoutModeAutomatic;                
    iLayoutFlags &= ~ENaviControlLayoutModeForced;                
    iLayoutFlags |= aMode;

    if ( NaviControlLayoutMode() == ENaviControlLayoutModeForced )
        {
        CancelLayoutStyleTimer();
        }
    else 
        {
        if ( NaviControlLayoutMode()  == ENaviControlLayoutModeAutomatic &&
             NaviControlLayoutStyle() == ENaviControlLayoutNormal )
            {
            InitLayoutStyleTimer();
            }        
        }          
    }


EXPORT_C CAknNavigationDecorator::TAknNaviControlLayoutMode CAknNavigationDecorator::NaviControlLayoutMode()
    {
    if ( iLayoutFlags & ENaviControlLayoutModeForced )
        {
        return ENaviControlLayoutModeForced;
        }
    else
        {
        return ENaviControlLayoutModeAutomatic;
        }
    }


EXPORT_C TBool CAknNavigationDecorator::NaviControlLayoutStyleSupported(
    TAknNaviControlLayoutStyle aStyle )
    {
    TBool retVal( EFalse );
    TBool penEnabled( AknLayoutUtils::PenEnabled() );

    if ( aStyle == ENaviControlLayoutNormal )
        {
        retVal = ETrue;
        }
    else if ( aStyle == ENaviControlLayoutNarrow )
        {
        if ( ( iControlType == ETabGroup && !penEnabled ) ||
             iControlType == ENaviLabel ||
             iControlType == ENaviImage ||
             iControlType == EHintText ||
             iControlType == EEditorIndicator )
            {
            retVal = ETrue;
            }
        }
    else if ( aStyle == ENaviControlLayoutWide )
        {
        // Wide layout is not currently supported for tabs in non-touch
        // layouts.
        if ( iControlType == ETabGroup && !penEnabled )
            {
            retVal = EFalse;
            }
        else
            {
            retVal = ETrue;
            }
        }

    return retVal;
    }


void CAknNavigationDecorator::InitLayoutStyleTimer()
    {
    if ( IsVisible() )
        {
        const TInt KIdleDelay = 5000000; // 5 s
        iLayoutStyleTimer->Cancel();    
        iLayoutStyleTimer->Start(TTimeIntervalMicroSeconds32(KIdleDelay),
            TTimeIntervalMicroSeconds32(KIdleDelay), 
            TCallBack(CAknNavigationDecorator::LayoutStyleEvent, this));
        }
    }

void CAknNavigationDecorator::CancelLayoutStyleTimer()
    {
    if (iLayoutStyleTimer && iLayoutStyleTimer->IsActive())
        {
        iLayoutStyleTimer->Cancel();
        }    
    }

TInt CAknNavigationDecorator::LayoutStyleEvent( TAny* aPtr )
    {
    ( ( CAknNavigationDecorator*) aPtr )->DoLayoutStyleEvent();
    return ETrue;
    }

void CAknNavigationDecorator::DoLayoutStyleEvent()
    {
    // First check that status pane layout or layout mode
    // has not been changed during timeout time.
    if ( !iContainer ||
         ( iContainer && iContainer->Top() != this ) ||
         !AknStatuspaneUtils::FlatLayoutActive() ||
         NaviControlLayoutMode() != ENaviControlLayoutModeAutomatic ||
         !IsVisible() )
        {
        CancelLayoutStyleTimer();
        return; 
        }
    
    // Only if automatic mode is active and control supports narrow layout style 
    // and titlepane text does not fit completely in normal mode
    // we change the layout style...
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    CCoeControl* navipanecontrol = NULL;
    CCoeControl* titlepaneControl = NULL;
    TBool textDoesFitVisibleTitlePaneArea = EFalse;
    
    if ( statusPane )
        {
        TRAP_IGNORE( navipanecontrol =
            statusPane->ControlL(TUid::Uid( EEikStatusPaneUidNavi ) ) );
        CAknTitlePane* titlePane =
            dynamic_cast <CAknTitlePane*> ( titlepaneControl );
            
        TRAP_IGNORE( titlepaneControl =
            statusPane->ControlL(TUid::Uid( EEikStatusPaneUidTitle ) ) );
    
        if ( navipanecontrol && titlePane )
            {        
            CAknTitlePaneLabel* titleLabel =
                static_cast <CAknTitlePaneLabel*> ( titlePane->TextLabel() );
                
            if ( titleLabel )
                {
                // check it text fits, add some safety margin (15%)
                TInt textlength = titleLabel->TextLength();
                TInt visibleAreaForText =
                    titlepaneControl->Size().iWidth - navipanecontrol->Size().iWidth;
                if ( textlength < ( visibleAreaForText * 85 / 100) )
                    {
                    textDoesFitVisibleTitlePaneArea = ETrue;
                    }
                }            
            }
        }
    
    if ( NaviControlLayoutMode() == ENaviControlLayoutModeAutomatic &&
         NaviControlLayoutStyleSupported( ENaviControlLayoutNarrow ) &&
         !textDoesFitVisibleTitlePaneArea )
        {
        SetNaviControlLayoutStyle( ENaviControlLayoutNarrow );         
        SizeChanged();
        DrawDeferred();
        }    
    
    CancelLayoutStyleTimer();
    }

TInt CAknNavigationDecorator::IndicationDrawCallbackL( TAny* aThis )
    {
    CAknNavigationDecorator* decorator = 
        static_cast<CAknNavigationDecorator*>(aThis);
    
    decorator->SmallDirectionIndicationL();
    
    return KErrNone;
    }

void CAknNavigationDecorator::SmallDirectionIndicationL()
    {
    TRect rect;
    
    // Cancel blinking if moved from the min or max position,
    // unless the area is blank. Then redraw and cancel after redraw
    if ( !iNaviArrowLeftDimmed &&
         !iNaviArrowRightDimmed && 
         ( iExtension->iEffectTimerCount % 2 == 0 ) )
        {
        CancelTimer();
        return;
        }
    
    // Stop timer if done normal-inverted-normal-inverted-normal sequence
    // or the user has changed the value from the min or max
    if ( iExtension->iEffectTimerCount >= 3 || 
         ( !iNaviArrowLeftDimmed &&
           !iNaviArrowRightDimmed ) )
        {
        CancelTimer();
        }
    
    Window().Invalidate( rect );
    ActivateGc();
            
    rect = TRect( iArrowLeftSize );
    
    // Draw navigation pane scroll indicator arrows if visible
    if ( iNaviArrowsVisible && iContainer )
        {
        CWindowGc& gc = SystemGc();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
        
        CFbsBitmap* colorbmp = iContainer->NaviColorBitmap();

        if ( iExtension->iBlinkingSide == 
             CAknNavigationDecoratorExtension::ENaviDecoratorLeftSide ) 
            {
            if( iExtension->iEffectTimerCount % 2 == 1 &&
                !iNaviArrowLeftDimmed )
                {
                CFbsBitmap* arrowBmp = &(iContainer->NaviArrowBitmap(0));
                CFbsBitmap* arrowMask = &(iContainer->NaviArrowBitmap(1));
                if( colorbmp && !IsMaskAllBlack( arrowMask ) )
                    {
                    gc.BitBltMasked( iArrowLeftPos,
                                     colorbmp,
                                     rect, 
                                     arrowMask,
                                     ETrue );
                    }
                else
                    {
                    gc.BitBltMasked( iArrowLeftPos,
                                     arrowBmp,
                                     rect,
                                     arrowMask,
                                     ETrue );
                    }
                }
            else
                {
                // draw empty
                AknsDrawUtils::Background(
                    skin,
                    cc,
                    this,
                    gc, 
                    TRect( iArrowLeftPos, rect.Size() ),
                    KAknsDrawParamDefault );
                }
            }
        rect = TRect( iArrowRightSize );
        
        if ( iExtension->iBlinkingSide == 
             CAknNavigationDecoratorExtension::ENaviDecoratorRightSide ) 
            {
            if ( iExtension->iEffectTimerCount % 2 == 1 &&
                 !iNaviArrowRightDimmed )
                {
                CFbsBitmap* arrowBmp = &(iContainer->NaviArrowBitmap(2));
                CFbsBitmap* arrowMask = &(iContainer->NaviArrowBitmap(3));
                if( colorbmp && !IsMaskAllBlack( arrowMask ) )
                    {
                    gc.BitBltMasked( iArrowRightPos,
                                     colorbmp,
                                     rect,
                                     arrowMask,
                                     ETrue );
                    }
                else
                    {
                    gc.BitBltMasked( iArrowRightPos,
                                     arrowBmp,
                                     rect,
                                     arrowMask,
                                     ETrue );
                    }
                }
            else
                {
                // draw empty
                AknsDrawUtils::Background(
                    skin,
                    cc,
                    this,
                    gc, 
                    TRect( iArrowRightPos, rect.Size() ),
                    KAknsDrawParamDefault );
                }
            }
        }

    DeactivateGc();
    
    iExtension->iEffectTimerCount++;
    }


void CAknNavigationDecorator::StartTimerL()
    {
    if ( !iExtension->iTimer )
        {
        iExtension->iTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    else if ( iExtension->iTimer->IsActive() )
        {
        return; // do not re-start as we have the feedback ongoing
        }
    
    iExtension->iEffectTimerCount = 0;

    const TTimeIntervalMicroSeconds32 KArrowFeedbackActionTime = 160 * 1000;
    
    TCallBack callback( IndicationDrawCallbackL, this );
    iExtension->iTimer->Start( KArrowFeedbackActionTime,
                               KArrowFeedbackActionTime,
                               callback );
    }
    
void CAknNavigationDecorator::CancelTimer()
    {
    if ( iExtension && iExtension->iTimer )
        {
        if ( iExtension->iTimer->IsActive() )
            {
            iExtension->iTimer->Cancel();
            }
        }
    }

EXPORT_C void CAknNavigationDecorator::HandleResourceChange( TInt aType )
    {
    if ( iControlType == ENaviVolume )
        {
        // We must forward the event to the volume popup instead
        // of the old style volume control.
        iDecoratedControl->HandleResourceChange( aType );
        }
    else
        {
        CCoeControl::HandleResourceChange( aType );
        }

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TAknNaviControlLayoutStyle layoutStyle = NaviControlLayoutStyle();
        TAknNaviControlLayoutMode  layoutMode  = NaviControlLayoutMode();
        TBool sizeChangedCalled( EFalse );
        
        if ( layoutMode  == ENaviControlLayoutModeAutomatic &&
             layoutStyle == ENaviControlLayoutNarrow )
            {
            SetNaviControlLayoutStyle( ENaviControlLayoutNormal );
            sizeChangedCalled = ETrue;
            }
        else if ( iControlType == ETabGroup &&
                  AknStatuspaneUtils::UsualLayoutActive() &&
                  !Layout_Meta_Data::IsLandscapeOrientation() )
            {
            // Need special handling for tab group in portrait mode usual
            // layout if switching from touch layout to a non-touch layout
            // or vice versa since the wide layout is not supported in
            // non-touch layout but is always used for tab groups in
            // portrait touch layouts.
            if ( AknLayoutUtils::PenEnabled() )
                {
                if ( layoutStyle != ENaviControlLayoutWide )
                    {
                    SetNaviControlLayoutMode( ENaviControlLayoutModeForced );
                    SetNaviControlLayoutStyle( ENaviControlLayoutWide );
                    sizeChangedCalled = ETrue;
                    }
                }
            else
                {
                if ( layoutStyle == ENaviControlLayoutWide )
                    {
                    SetNaviControlLayoutMode( ENaviControlLayoutModeAutomatic );
                    SetNaviControlLayoutStyle( ENaviControlLayoutNormal );
                    sizeChangedCalled = ETrue;
                    }
                }
            }

        if ( !sizeChangedCalled )
            {
            SizeChanged();
            }
        }
    }


TRect CAknNavigationDecorator::NaviArrowRect( TScrollButton aScrollButton,
                                              TBool aNarrowLayout,
                                              TRect aNaviRect )
    {
    TAknLayoutRect layoutRect;
    TRect arrowRect;

    TAknWindowComponentLayout arrowLayout;
    if ( aNarrowLayout )
        {
        arrowLayout = aScrollButton == ELeftButton ?
            AknLayoutScalable_Avkon::navi_navi_pane_srt_g1( 0 ) :
            AknLayoutScalable_Avkon::navi_navi_pane_srt_g2( 0 );
        }
    else
        {
        arrowLayout = aScrollButton == ELeftButton ?
            AknLayoutScalable_Avkon::navi_navi_pane_g1( 0 ) :
            AknLayoutScalable_Avkon::navi_navi_pane_g2( 0 );
        }

    // aNaviRect is empty by default
    if ( !aNaviRect.IsEmpty() )
        {
        layoutRect.LayoutRect( aNaviRect, arrowLayout );
        arrowRect = layoutRect.Rect();
        }
    else
        {
        if ( aNarrowLayout )
            {
            TRect naviPaneRect( DecoratedControlNarrowRect( 0 ) ); // parameter not used
            layoutRect.LayoutRect( naviPaneRect, arrowLayout );
            arrowRect = layoutRect.Rect();
            }
        else
            {
            TRect naviPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::ENaviPane,
                                               naviPaneRect );

            naviPaneRect.Move( -naviPaneRect.iTl.iX,
                               -naviPaneRect.iTl.iY );

            layoutRect.LayoutRect(
                naviPaneRect,
                AknLayoutScalable_Avkon::navi_navi_pane() );
            TRect naviNaviRect( layoutRect.Rect() );

            layoutRect.LayoutRect( naviNaviRect, arrowLayout );
            arrowRect = layoutRect.Rect();
            }
        }

    return arrowRect;
    }

//  End of File  
