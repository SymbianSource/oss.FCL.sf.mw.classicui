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


// INCLUDE FILES
#include <ganes/HgScroller.h>

#include <aknphysics.h>

#include <ganes/HgScrollBufferObserverIface.h>
#include <ganes/HgSelectionObserverIface.h>
#include <ganes/HgMarkingObserverIface.h>
#include <ganes/HgItem.h>
#include "HgScrollbar.h"
#include "HgScrollBufferManager.h"
#include "HgConstants.h"
#include "HgPopupDrawer.h"
#include "HgMarquee.h"
#include "HgDrawUtils.h"
#include "HgIndicatorManager.h"
#include "HgTextFind.h"
#include "HgKeyUtils.h"

#include <ganes.mbg>

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <touchfeedback.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <aknitemactionmenu.h>
#include <aknappui.h>

#include <featdiscovery.h>

const TInt KIntensity = 100; // 100%

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHgScroller::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgScroller::ConstructL (const TRect& aRect, RWsSession* aSession )
    {
    // Create a window for this application view
    CreateWindowL ( );
    EnableDragEvents();
    ClaimPointerGrab();

    iUpperCaseTitle.CreateL( KMaxSearchLenght );
    iPopupText1.CreateL( KMaxPopupTextLength );
    iPopupText2.CreateL( KMaxPopupTextLength );
    
    iScrollbar = CHgScrollbar::NewL(*this);
    iPopupDrawer = new (ELeave) THgPopupDrawer();
    iPhysics = CAknPhysics::NewL(*this, this);

    TCallBack callback(CHgScroller::MarqueeCallback, this);
    iDrawUtils = CHgDrawUtils::NewL( callback );
    
    iIndicatorManager = CHgIndicatorManager::NewL();

    /*
    // Enable key search only in non-touch or hybrid (touch + qwerty) devices
    if( !AknLayoutUtils::PenEnabled() ||
        CFeatureDiscovery::IsFeatureSupportedL(TUid::Uid(KFeatureIdQwertyInput)) )
        {
        iTextFind = CHgTextFind::NewL( *this );
        iKeyUtils = CHgKeyUtils::NewL(*this);
        }
    */
    
    // Init Stuff
    if( aSession )
        {
        InitScreenL( aRect, *aSession );
        }
    else
        {
        InitScreenL( aRect );
        }
    
    iHighlightTimer = CPeriodic::NewL( CActive::EPriorityStandard );    
    iKeyScrollingTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    
    CAknAppUi* appUi = static_cast<CAknAppUi*>(iEikonEnv->AppUi());
    if( appUi && appUi->IsSingleClickCompatible() )
        {
        iDetector = CAknLongTapDetector::NewL(this);
        iActionMenu = CAknItemActionMenu::RegisterCollectionL( *this );
        }

    iDrawUtils->EnableMarquee(HasHighlight());
    
    InitItemsL();

    iCoeEnv->AddForegroundObserverL( *this );    
    }

// -----------------------------------------------------------------------------
// CHgScroller::InputCapabilities()
// -----------------------------------------------------------------------------
//
TCoeInputCapabilities CHgScroller::InputCapabilities() const
    {
    TCoeInputCapabilities cap( TCoeInputCapabilities::ENone );

    if(iTextFind)
        {
        MCoeFepAwareTextEditor* editor = NULL;
        
        if( iSelectionMode == ENoSelection 
                && iFlags & EHgScrollerSearchWithQWERTY )
            editor = iTextFind;
    
        cap = TCoeInputCapabilities( TCoeInputCapabilities::EAllText, 
                editor, 
                NULL );
        
        cap.SetObjectProvider( const_cast<CHgScroller*>(this) );
        }
    
    return cap;
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitScreenL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::InitScreenL( const TRect& /*aRect*/, RWsSession& /*aSession*/ )
    {
    // DSA not supported anymore.
    User::Leave( KErrNotSupported );
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitScreenL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::InitScreenL( const TRect& aRect )
    {
    // Set the windows size
    SetRect ( aRect );
    }

// -----------------------------------------------------------------------------
// CHgScroller::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::RefreshScreen( TInt aIndex )
    {
    if( IsDisplayed( aIndex ) )
        DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CHgScroller::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgScroller::FirstIndexOnScreen()
    {
    return CurrentIndex();
    }

// -----------------------------------------------------------------------------
// CHgScroller::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgScroller::ItemsOnScreen()
    {
    return iItemsOnScreen;
    }

// -----------------------------------------------------------------------------
// CHgScroller::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgScroller::SelectedIndex()
    {
    return iSelectedIndex;
    }

// -----------------------------------------------------------------------------
// CHgScroller::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetSelectedIndex( TInt aIndex )
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        if( !IsDisplayed( aIndex ) )
            {
            iSelectedIndex = iItems.Count() - 1;
            FitSelectionToView();
            }
        
        iSelectedIndex = aIndex;
        // Move view position so that it is fully visible.
        FitSelectionToView();
        SelectionChanged();
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::Mark()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::Mark( TInt aIndex )
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        if( !(iItems[aIndex]->Flags() & CHgItem::EHgItemFlagMarked) )
            {
            iItems[aIndex]->SetFlags( CHgItem::EHgItemFlagMarked );
            if( iMarkingObserver )
                {
                TRAP_IGNORE( iMarkingObserver->HandleMarkingL( aIndex, ETrue ) );
                }            
            }
        }    
    }

// -----------------------------------------------------------------------------
// CHgScroller::UnMark()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::UnMark( TInt aIndex )
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        if( iItems[aIndex]->Flags() & CHgItem::EHgItemFlagMarked )
            {
            iItems[aIndex]->ClearFlags( CHgItem::EHgItemFlagMarked );
            if( iMarkingObserver )
                {
                TRAP_IGNORE( iMarkingObserver->HandleMarkingL( aIndex, EFalse ) );
                }            
            }
        }    
    }

// -----------------------------------------------------------------------------
// CHgScroller::MarkAll()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::MarkAll()
    {
    for(TInt i = 0; i < iItems.Count(); ++i)
        {
        iItems[i]->SetFlags( CHgItem::EHgItemFlagMarked );
        }
    
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CHgScroller::UnMarkAll()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::UnMarkAll()
    {
    for(TInt i = 0; i < iItems.Count(); ++i)
        {
        iItems[i]->ClearFlags(CHgItem::EHgItemFlagMarked);
        }
    
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CHgScroller::GetMarkedItemsL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::GetMarkedItemsL( RArray<TInt>& aIndexes )
    {
    for(TInt i = 0; i < iItems.Count(); ++i)
        {
        if(iItems[i]->Flags() & CHgItem::EHgItemFlagMarked )
            {
            aIndexes.AppendL( i );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::EnableScrollBufferL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::EnableScrollBufferL( 
        MHgScrollBufferObserver& aObserver, 
        TInt aBufferSize,
        TInt aBufferTreshold  )
    {
    delete iManager; iManager = NULL;
    
    iManager = CHgScrollBufferManager::NewL(
            aObserver, 
            aBufferSize, 
            aBufferTreshold, 
            CurrentIndex(), 
            iItemCount);
    
    iManager->SetBufferOwner( *this );
    }

// -----------------------------------------------------------------------------
// CHgScroller::EnableNaviStripL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetScrollBarTypeL( THgScrollBarType aType )
    {
    iScrollBarType = aType;
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetSelectionObserver()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetSelectionObserver( MHgSelectionObserver& aObserver )
    {
    iSelectionObserver = &aObserver;
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetMarkingObserver()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetMarkingObserver( MHgMarkingObserver& aObserver )
    {
    iMarkingObserver = &aObserver;
    }

// -----------------------------------------------------------------------------
// CHgScroller::CHgScroller()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgScroller::CHgScroller( 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon )
 :  iDefaultIcon( aDefaultIcon ),
    iItemCount(aItemCount), 
    iCurrentRow(-1),
    iSelectedIndex(KErrNotFound),
    iScrollBarType( EHgScrollerScrollBar ),
    iFirstTime(ETrue)
    {
    // No implementation required
    }
        
// -----------------------------------------------------------------------------
// CHgScroller::~CHgScroller()
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgScroller::~CHgScroller ( )
    {
    iCoeEnv->RemoveForegroundObserver( *this );
    ReleasePopupFont();

    iItems.ResetAndDestroy();

    delete iManager;
    delete iPhysics;
    delete iScrollbar;
    delete iEmptyText;    
    delete iDefaultIcon;
    delete iPopupDrawer;
    delete iDrawUtils;
    delete iHighlightTimer;
    delete iIndicatorManager;
    delete iKeyUtils;
	delete iTextFind;
	delete iKeyScrollingTimer;
	delete iDetector;
	
	if(iActionMenu)
	    iActionMenu->RemoveCollection(*this);
    
    iUpperCaseTitle.Close();
    iPopupText1.Close();
    iPopupText2.Close();
    
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitPhysicsL()
// -----------------------------------------------------------------------------
//
void CHgScroller::InitPhysicsL()
    {
    // For to be able to pan on a empty area. 
    // The world is set to be at least the size of the view.
    TSize worldSize = TotalSize();
    
    if( !iLandscapeScrolling && (worldSize.iHeight < iHeight) )
        worldSize.iHeight = iHeight;
    
    if( iLandscapeScrolling && (worldSize.iWidth < iWidth) )
        worldSize.iWidth = iWidth;

    iPhysics->InitPhysicsL( worldSize, 
            TSize(iWidth, iHeight), 
            iLandscapeScrolling);
    }

// -----------------------------------------------------------------------------
// CHgGrid::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CHgScroller::Draw ( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    
    // Flush screen buffer
    InitDrawBuffer();

    DoDraw( aRect );

    if( iScrollbar && iItemCount )
        {
        iScrollbar->Draw( gc );
        }
    
    if( iPopupDrawer )
        {
        if(iPopupText2.Length() > 0)
            {
            iPopupDrawer->Draw( gc, 
                    iPopupText1,
                    iPopupText2
                    );
            }
        else if( iPopupText1.Length( ) > 0 )
            {
            if( iScrollBarType == EHgScrollerLetterStrip
                    || iScrollBarType == EHgScrollerLetterStripLite )
                {
                iPopupDrawer->DrawNaviChar( gc, iPopupText1 );
                }
            else
                {
                iPopupDrawer->Draw( gc, iPopupText1 );
                }
            }
        else if( iTextFind && iTextFind->Text().Length() > 0 )
            {
            iPopupDrawer->Draw( gc, iTextFind->Text() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitDrawBuffer()
// -----------------------------------------------------------------------------
//
void CHgScroller::InitDrawBuffer() const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::DrawBackground( skin, cc, this, SystemGc(),
            TPoint(0,0), Rect(), KAknsDrawParamDefault );
    }

// -----------------------------------------------------------------------------
// CHgScroller::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHgScroller::SizeChanged ( )
    {
    iWidth = Rect().Width();
    iHeight = Rect().Height();

    HandleItemCountChanged();
    
    if( iPopupDrawer )
        {
        ReleasePopupFont();

        TFontSpec fontSpecTitle = AknLayoutUtils::FontFromId(EAknLogicalFontPrimaryFont)->FontSpecInTwips();
        fontSpecTitle.iHeight = KFocusTextFontSize; // set height
        iCoeEnv->ScreenDevice()->GetNearestFontInTwips(iPopupFont, fontSpecTitle);
    
        iPopupDrawer->Init( Rect(), iPopupFont );
        }
    
    if(iFirstTime)
        {
        iViewPosition = TPoint(iWidth/2, iHeight/2);
        iFirstTime = EFalse;
        }
    
    HandleViewPositionChanged();
    
    TRAP_IGNORE( InitGraphicsL(); )
    DrawDeferred ( );
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleItemCountChaged()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleItemCountChanged()
    {
    HandleSizeChanged();

    if( iSelectedIndex >= iItemCount )
        {
        iSelectedIndex = iItemCount - 1;
        SelectionChanged();
        }

    TRAP_IGNORE ( 
            InitScrollbarL();
            InitPhysicsL();
                )
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitScrollbarL()
// -----------------------------------------------------------------------------
//
void CHgScroller::InitScrollbarL()
    {
    if( iScrollbar )
        {
        TBool prevStatic = iScrollbar->IsStatic();
        iScrollbar->InitScrollBarL( Rect(), 
                                    TotalSize(), 
                                    TSize(iWidth, iHeight), 
                                    iLandscapeScrolling); 

        iScrollbar->SetViewPosition( iViewPosition - TPoint(iWidth/2, iHeight/2));
        
        if(prevStatic != iScrollbar->IsStatic())
            HandleScrollbarVisibilityChange( !iScrollbar->IsStatic() );
        }
    }
// -----------------------------------------------------------------------------
// CHgScroller::HandlePointerEventL()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandlePointerEventL( const TPointerEvent& aEvent )
    {
    if( !HandleScrollbarEventL( aEvent ) && iItemCount )
        {
        iShowHighlight = EFalse;
        
        // Start drag
        if( aEvent.iType == TPointerEvent::EButton1Down )
            {
            iPointerDown = ETrue;
            HandleDownEventL( aEvent );

            if( iDetector 
                    && iSelectedIndex != KErrNotFound 
                    && !HasHighlight() 
                    && iActionMenu->InitMenuL() )
                iDetector->PointerEventL( aEvent );
            }
        // Drag
        else if( aEvent.iType == TPointerEvent::EDrag && iPointerDown )
            {
            HandleDragEventL( aEvent );
            
            if( iPanning && iDetector && !HasHighlight()  )
                iDetector->CancelAnimationL();
            }
        // End drag
        else if( aEvent.iType == TPointerEvent::EButton1Up && iPointerDown )
            {
            if( iDetector && !HasHighlight() )
                iDetector->PointerEventL( aEvent );
            
            HandleUpEventL( aEvent );
            iPointerDown = EFalse;
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleScrollbarEventL()
// -----------------------------------------------------------------------------
//
TBool CHgScroller::HandleScrollbarEventL( const TPointerEvent& aEvent )
    {
    TBool sbHandles = EFalse;
    if( iScrollbar )
        {
        sbHandles = iScrollbar->HandlePointerEventL( aEvent );
        if ( sbHandles && !iScrollbar->IsStatic() )
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            // Start drag
            if( aEvent.iType == TPointerEvent::EButton1Down )
                {
                if ( feedback )
                    {
                    feedback->InstantFeedback( this, ETouchFeedbackSlider, aEvent );
                    }
                }
            // Drag
            else if( aEvent.iType == TPointerEvent::EDrag 
                    && iScrollbar->IsDragging() )
                {
                // Smooth continuous tactile feedback is produced
                // during thumb dragging. The tactile feedback API 
                // filters out possible re-startings of the effect.
                if ( feedback )
                    {
                    TTimeIntervalMicroSeconds32 timeout( 300000 );
                    feedback->StartFeedback( this, 
                                             ETouchContinuousSlider, 
                                             &aEvent, 
                                             KIntensity, // intensity 50%
                                             timeout );
                    }
                }
            // End drag
            else if( aEvent.iType == TPointerEvent::EButton1Up )
                {
                // Stop the continuous tactile feedback that may be playing
                // at the time due to possible previous thumb dragging.
                if ( feedback )
                    {
                    feedback->StopFeedback( this );
                    TTouchFeedbackType type = ETouchFeedbackVibra;
                    feedback->InstantFeedback( this, ETouchFeedbackSlider, type, aEvent );
                    }
                iPopupText1.Zero();
                iPopupText2.Zero();
                DrawDeferred();
                }
            }
        }
    return sbHandles;
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleDownEventL()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleDownEventL( const TPointerEvent& aEvent )
    {
    if( !HasHighlight() 
            && (iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking) )
        {
        iPanning = ETrue;
        if(iDetector)
            iDetector->CancelAnimationL();
        }
    else
        {
        iPanning = EFalse;
        }

    iPhysics->StopPhysics();
    iPhysics->ResetFriction();

    iStart = aEvent.iPosition;
    iPrev = iStart;
    iStartTime.HomeTime();

    if(iLandscapeScrolling)
        iViewPosition.iY = iHeight / 2;
    else
        iViewPosition.iX = iWidth / 2;
    
    iFocusedIndex = KErrNotFound;
    iSelectionToFocusedItem = EFalse;
    iDrawUtils->EnableMarquee(HasHighlight());
    if(HasHighlight())
        {
        LaunchHighlightTimer();
        }
    else if( !iPanning )
        {
        SetHighlightL();
        }
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback && iSelectedIndex != KErrNotFound )
        {
        feedback->InstantFeedback( this, ETouchFeedbackList, aEvent );
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleDragEventL()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleDragEventL( const TPointerEvent& aEvent )
    {
    if(!iPanning)
        {
        TInt delta = 0;
        if(iLandscapeScrolling)
            {
            delta = iPrev.iX - aEvent.iPosition.iX;
            }
        else
            {
            delta = iPrev.iY - aEvent.iPosition.iY;
            }
        
        delta = delta < 0 ? -delta : delta;
        iPanning = delta >= iPhysics->DragThreshold();
        }

    if(iPanning)
        {
        TPoint delta = iPrev - aEvent.iPosition;
        if(iLandscapeScrolling && AknLayoutUtils::LayoutMirrored())
            delta = -delta;
        iPhysics->RegisterPanningPosition( delta );
        iPrev = aEvent.iPosition;
        iHighlightTimer->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleUpEventL()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleUpEventL( const TPointerEvent& aEvent )
    {
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    TTouchFeedbackType type = ETouchFeedbackVibra;
    if( iPanning )
        {
        // enable physics
        TPoint drag = iStart - aEvent.iPosition;
        if(iLandscapeScrolling && AknLayoutUtils::LayoutMirrored())
            drag = -drag;
        iPhysics->StartPhysics(drag, iStartTime);
        if ( feedback && iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking )
            {
            feedback->InstantFeedback( this, ETouchFeedbackFlick, type, aEvent );
            }
        }
    else
        {
        HandleSelectionL();
        if ( feedback && iSelectedIndex != KErrNotFound )
            {
            feedback->InstantFeedback( this, ETouchFeedbackList, type, aEvent );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleSelectionL()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleSelectionL()
    {
    TInt index = GetSelected(iStart);
    if(index != KErrNotFound)
        {
        if( iFocusedIndex == KErrNotFound )
            {
            // Highlight timer hasn't triggered so lets set the highlight.
            // this is not usually the case since interval is 50ms but just to be sure.
            SetHighlightL();
            }
        
        // selection needs to be valid.
        if( iSelectedIndex >= 0 && iSelectedIndex < iItems.Count() )
            {
            if( iFlags & EHgScrollerSelectionMode || iSelectionMode != ENoSelection ) 
                // Marking mode or shift key pressed ( or hash )
                {
                if( iItems[iSelectedIndex]->Flags() & CHgItem::EHgItemFlagMarked )
                    {
                    UnMark( iSelectedIndex );
                    }
                else
                    {
                    Mark( iSelectedIndex );                    
                    }
                DrawDeferred();
                }
            else // Selection
                {
                if( iSelectionToFocusedItem || !HasHighlight() )
                    {
                    if(iSelectionObserver)
                        iSelectionObserver->HandleOpenL(iSelectedIndex);
                    }
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::OfferKeyEventL()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgScroller::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if( iKeyUtils 
            && !(iFlags & EHgScrollerKeyMarkingDisabled)
            && iKeyUtils->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
        return EKeyWasConsumed;
    
    switch( aType )
        {
        case EEventKeyDown:
            KeyEventDown();
            break;
        case EEventKey:    
            return HandleKeyEvent( aKeyEvent );
        case EEventKeyUp:
            KeyEventUp();
        default:
            break;
        }
    
    // Let CCoeControl handle other cases.
    return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CHgScroller::KeyEventDown()
// -----------------------------------------------------------------------------
//
void CHgScroller::KeyEventDown()
    {
    iKeyRepeats = 0;
    iKeyScrollingState = ENoKeyScrolling;
    
    iPointerDown = EFalse;
    iPanning = EFalse;
    }

// -----------------------------------------------------------------------------
// CHgScroller::KeyEventUp()
// -----------------------------------------------------------------------------
//
void CHgScroller::KeyEventUp()
    {
    if( iKeyScrollingState != ENoKeyScrolling )
        {
        // Key has been released so stop the key scrolling.
        StopKeyScrolling();
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetItem(CHgItem* aItem, TInt aIndex)
    {
    if( aItem && aIndex >= 0 && aIndex < iItems.Count() )
        {
        delete iItems[aIndex];
        iItems[aIndex] = aItem;
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::AddItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::AddItem(CHgItem* aItem)
    {
    if( aItem )
        {
        iItems.Append(aItem);
        iItemCount++;
        HandleItemCountChanged();
        if( iManager )
            {
            iManager->ItemCountChanged( iItemCount-1, EFalse, iItemCount );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::InsertItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::InsertItem(CHgItem* aItem, TInt aIndex)
    {
    if( aItem && aIndex >= 0 )
        {
        if(aIndex < iItems.Count())
            {
            iItems.Insert(aItem, aIndex);
            }
        else
            {
            iItems.Append(aItem);
            }
        iItemCount++;
        HandleItemCountChanged();
        
        if( iManager )
            {
            iManager->ItemCountChanged( aIndex, EFalse, iItemCount );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::RemoveItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::RemoveItem(TInt aIndex)
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        delete iItems[aIndex]; iItems[aIndex] = NULL;
        iItems.Remove(aIndex);
        iItemCount--;
        HandleItemCountChanged();
        
        if( iManager )
            {
            iManager->ItemCountChanged( aIndex, ETrue, iItemCount );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::ResizeL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::ResizeL( TInt aItemCount )
    {
    // Add More
    if( iItems.Count() < aItemCount )
        {
        while( iItems.Count() < aItemCount )
            {
            iItems.AppendL( CHgItem::NewL() );
            }
        }
    // remove from the end
    else if( iItems.Count() > aItemCount )
        {
        while( iItems.Count() > aItemCount )
            {
            delete iItems[iItems.Count() - 1];
            iItems.Remove( iItems.Count() - 1 );
            }
        }
    else
        {
        return; // no change needed
        }

    iItemCount = aItemCount;

    if( iManager )
        {
        iManager->ResetBuffer( iSelectedIndex, iItemCount );
        }

    HandleItemCountChanged();
    }

// -----------------------------------------------------------------------------
// CHgScroller::ItemL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgItem& CHgScroller::ItemL(TInt aIndex)
    {
    if( aIndex < 0 || aIndex >= iItems.Count() )
        {
        User::Leave( KErrArgument );
        }

    return *iItems[aIndex];
    }

// -----------------------------------------------------------------------------
// CHgScroller::ViewPositionChanged()
// -----------------------------------------------------------------------------
//
void CHgScroller::ViewPositionChanged( const TPoint& aNewPosition,
                                        TBool aDrawNow,
                                        TUint /*aFlags*/ )
    {
    iViewPosition = aNewPosition;
    HandleViewPositionChanged();
    if( aDrawNow )
        DrawNow();
    }

// -----------------------------------------------------------------------------
// CHgScroller::ScrollBarPositionChanged()
// -----------------------------------------------------------------------------
//
void CHgScroller::ScrollBarPositionChanged( const TPoint& aNewPosition )
    {
    iViewPosition = aNewPosition;
    iPhysics->StopPhysics();
    
    if( iScrollBarType == EHgScrollerTimeStrip )
        {
        // Show first item's time.
        TInt selectedItem = CurrentIndex();
        if( selectedItem >= 0 && selectedItem < iItems.Count() )
            {
            TRAP_IGNORE(
                    iItems[selectedItem]->Time().FormatL( iPopupText1, KGanesMonthString );
                    iItems[selectedItem]->Time().FormatL( iPopupText2, KGanesYearString );
                )
            // To display month and year correctly in arabic.
            AknTextUtils::LanguageSpecificNumberConversion( iPopupText1 );
            AknTextUtils::LanguageSpecificNumberConversion( iPopupText2 );
            }
        }
    else if( iScrollBarType == EHgScrollerLetterStrip
            || iScrollBarType == EHgScrollerLetterStripLite )
        {
        TInt selectedItem = CurrentIndex();
        if( selectedItem >= 0 && selectedItem < iItems.Count() )
            {
            if(iItems[selectedItem]->Title().Length())
                {
                iPopupText1.Zero();
                iPopupText1.Append( iItems[selectedItem]->Title()[0] );
                iPopupText1.UpperCase();
                }
            }
        }
    HandleViewPositionChanged( EFalse );
    DrawNow();
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleNaviStripChar()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleNaviStripChar( const TChar& /*aChar*/ )
    {
    // Feature not used anymore
    }

// -----------------------------------------------------------------------------
// CHgScroller::PhysicEmulationEnded()
// -----------------------------------------------------------------------------
//
void CHgScroller::PhysicEmulationEnded()
    {
    // Nothing to do.
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleViewPositionChanged()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleViewPositionChanged(TBool aUpdateScrollbar)
    {
    TInt newRow = iLandscapeScrolling ?
        (iViewPosition.iX-(iWidth/2))/((iRowHeight)):
        (iViewPosition.iY-(iHeight/2))/(iRowHeight);
    
    if(iScrollbar && aUpdateScrollbar)
        iScrollbar->SetViewPosition( iViewPosition - TPoint(iWidth/2, iHeight/2));

    if(newRow != iCurrentRow)
        {
        iCurrentRow = newRow;
        
        TBool needsFeedback = 
                ( iCurrentRow >= 0 && iCurrentRow <= iItems.Count() )
                || ( iItems.Count() - iCurrentRow > ItemsOnScreen() );
        
        TInt action = iPhysics->OngoingPhysicsAction();
        if( action !=  CAknPhysics::EAknPhysicsActionNone && needsFeedback )
            {
            TTouchFeedbackType type( ETouchFeedbackVibra );
            if ( CAknPhysics::EAknPhysicsActionDragging == action )
                {
                type = TTouchFeedbackType(ETouchFeedbackVibra | ETouchFeedbackAudio);
                }

            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if(feedback)
                feedback->InstantFeedback( this, ETouchFeedbackSensitiveList,
                                            type,
                                            TPointerEvent() );
            }

        if(iManager)
            {
            iManager->SetPosition( CurrentIndex() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleViewPositionChanged()
// -----------------------------------------------------------------------------
//
TPoint CHgScroller::ViewPosition() const
    {
    return iViewPosition;
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleKeyEvent()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgScroller::HandleKeyEvent(const TKeyEvent& aKeyEvent)
    {
    iKeyRepeats++;
    TInt prevSelected = iSelectedIndex;

    TKeyScrollingState possibleKeyScrollingState = ENoKeyScrolling;
    
    switch( aKeyEvent.iCode )
        {
        case EKeyUpArrow:
            if( !iLandscapeScrolling )
                possibleKeyScrollingState = EKeyScrollingUp;
            break;
        case EKeyDownArrow:
            if( !iLandscapeScrolling )
                possibleKeyScrollingState = EKeyScrollingDown;
            break;
        case EKeyLeftArrow:
            if( iLandscapeScrolling )
                possibleKeyScrollingState = EKeyScrollingLeft;
            break;
        case EKeyRightArrow:
            if( iLandscapeScrolling )
                possibleKeyScrollingState = EKeyScrollingRight;
            break;
        case EKeyEnter:
        case EKeyOK:
            {
            if( iSelectedIndex != KErrNotFound && HasHighlight() )
                {
                if( iSelectionObserver )
                    TRAP_IGNORE( iSelectionObserver->HandleOpenL( iSelectedIndex ); )
                iShowHighlight = EFalse;
                iDrawUtils->EnableMarquee(HasHighlight());
                return EKeyWasConsumed;
                }
            else if( iItemCount )
                {
                iSelectedIndex = iCurrentRow;
                if( iSelectionObserver )
                    TRAP_IGNORE( iSelectionObserver->HandleSelectL( iSelectedIndex ); )
                FitSelectionToView();
                iShowHighlight = ETrue;
                iDrawUtils->EnableMarquee(HasHighlight());
                DrawDeferred();
                return EKeyWasConsumed;
                }
            return EKeyWasNotConsumed;
            }
        default:
            break;
        }

    if( possibleKeyScrollingState != ENoKeyScrolling 
        && iKeyRepeats > KPhysLaunchKeyCount
        && iSelectionMode == ENoSelection )
        {
        if( !iKeyScrollingTimer->IsActive() )
            {
            iKeyScrollingState = possibleKeyScrollingState;
            iKeyScrollingTimer->Start(
                    TTimeIntervalMicroSeconds32( 0 ),
                    TTimeIntervalMicroSeconds32( KKeyScrollingUpdateInterval ), 
                    TCallBack( KeyScrollingTimerCallback, this ) );
            }
        }

    if( !HasHighlight() )
        {
        // DoHandleKeyEvent will move focus at the first index on screen.  
        iSelectedIndex = KErrNotFound;
        }
    
    if( DoHandleKeyEvent(aKeyEvent) )
        {
        iShowHighlight = ETrue;
        iDrawUtils->EnableMarquee(HasHighlight());
        if( iSelectedIndex != prevSelected && iSelectionObserver )
            {
            iDrawUtils->ResetMarquee();
            TRAP_IGNORE( iSelectionObserver->HandleSelectL(iSelectedIndex); )
            }
        return EKeyWasConsumed;
        }
    else
        {
        iKeyRepeats--;
        return EKeyWasNotConsumed;
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::Release()
// -----------------------------------------------------------------------------
//
void CHgScroller::Release(TInt aReleaseStart, TInt aReleaseEnd)
    {
    for(; aReleaseStart <= aReleaseEnd; ++aReleaseStart)
        {
        if( aReleaseStart >= 0 && aReleaseStart < iItems.Count())
            {
            iItems[aReleaseStart]->SetIcon(NULL, iItems[aReleaseStart]->Flags());
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::Reset()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::Reset()
    {
    if(iItemCount)
        {
        iItems.ResetAndDestroy();
        iItemCount = 0;
        iSelectedIndex = -1;
        
        if( iManager )
            {
            iManager->ResetBuffer( iSelectedIndex, iItemCount );
            }
    
        HandleItemCountChanged();
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetFlags()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetFlags(TInt aFlags)
    {
    iFlags |= aFlags;
    }

// -----------------------------------------------------------------------------
// CHgScroller::ClearFlags()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::ClearFlags(TInt aFlags)
    {
    iFlags &= ~aFlags;    
    }

// -----------------------------------------------------------------------------
// CHgScroller::Flags()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgScroller::Flags()
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetEmptyTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetEmptyTextL( const TDesC& aEmptyText )
    {
    delete iEmptyText;
    iEmptyText = 0;
    iEmptyText = aEmptyText.AllocL();
    }

// -----------------------------------------------------------------------------
// CHgScroller::ItemCount()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgScroller::ItemCount() const
    {
    return iItems.Count();
    }

// -----------------------------------------------------------------------------
// CHgScroller::HightlightItem()
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CHgScroller::HightlightItem( const TDesC& aHighlightText )
    {
    TInt searchStartIndex = aHighlightText.Length() == 1 ||
        iSelectedIndex == KErrNotFound ? iSelectedIndex + 1 : iSelectedIndex;
    
    // From selected to end
    for(TInt i = searchStartIndex; i < iItems.Count(); ++i)
        {
        if(iItems[i]->Title().Length() > 0 )
            {
            iUpperCaseTitle.Copy( iItems[i]->Title().Left( aHighlightText.Length() ) );
            iUpperCaseTitle.UpperCase();
            TInt result = iUpperCaseTitle.CompareC( aHighlightText );

            if(result == 0)
                {
                iSelectedIndex = i;
                FitSelectionToView();
                DrawDeferred();
                return ETrue;
                }
            }
        }

    // From beginning to selected - 1
    for(TInt i = 0; i < iSelectedIndex; ++i)
        {
        if(iItems[i]->Title().Length() > 0 )
            {
            iUpperCaseTitle.Copy( iItems[i]->Title().Left( aHighlightText.Length() ) );
            iUpperCaseTitle.UpperCase();
            TInt result = iUpperCaseTitle.CompareC( aHighlightText );

            if(result == 0)
                {
                iSelectedIndex = i;
                FitSelectionToView();
                DrawDeferred();
                return ETrue;
                }
            else if( result > 0)
                {
                break;
                }
            }
        }
    
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CHgScroller::SetDefaultIconL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::SetDefaultIconL( CGulIcon* aDefaultIcon )
    {
    if( aDefaultIcon )
        {
        delete iDefaultIcon;
        iDefaultIcon = aDefaultIcon;
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::DisableScrollBuffer()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScroller::DisableScrollBuffer()
    {
    delete iManager;
    iManager = NULL;
    }

// -----------------------------------------------------------------------------
// CHgScroller::InitGraphicsL()
// -----------------------------------------------------------------------------
//
void CHgScroller::InitGraphicsL()
    {
    // Non-Skinned icons
    // Default icon
    if(iIndicatorManager)
        {
        iIndicatorManager->InitIconL(iDefaultIcon, 
                EMbmGanesQgn_prop_checkbox_on, EMbmGanesQgn_prop_checkbox_on_mask, iImageSize);

        iIndicatorManager->InitIndicatorsL(iIndicatorSize);
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::SelectionChanged()
// -----------------------------------------------------------------------------
//
void CHgScroller::SelectionChanged()
    {
    }

// -----------------------------------------------------------------------------
// CHgScroller::FitRowToView()
// -----------------------------------------------------------------------------
//
void CHgScroller::FitRowToView( TInt aRow )
    {
    if( iLandscapeScrolling )
        {
        if ( aRow*iRowHeight < iViewPosition.iX-(iWidth/2) )
            {
            // Item is at top but not fully visible
            iViewPosition.iX -= (iViewPosition.iX-(iWidth/2) - ((aRow)*iRowHeight));
            HandleViewPositionChanged();                            
            }    
        else if ( (aRow+1)*iRowHeight > iViewPosition.iX+(iWidth/2) )
            {
            // Item is at bottom but not fully visible
            iViewPosition.iX += ((aRow+1)*iRowHeight - (iViewPosition.iX+(iWidth/2)));
            HandleViewPositionChanged();                            
            }        
        }
    else
        {
        if ( aRow*iRowHeight < iViewPosition.iY-(iHeight/2) )
            {
            // Item is at top but not fully visible
            iViewPosition.iY -= (iViewPosition.iY-(iHeight/2) - ((aRow)*iRowHeight));
            HandleViewPositionChanged();                            
            }    
        else if ( (aRow+1)*iRowHeight > iViewPosition.iY+(iHeight/2) )
            {
            // Item is at bottom but not fully visible
            iViewPosition.iY += ((aRow+1)*iRowHeight - (iViewPosition.iY+(iHeight/2)));
            HandleViewPositionChanged();                            
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::MarqueeCallback()
// -----------------------------------------------------------------------------
//
TInt CHgScroller::MarqueeCallback( TAny* aSelf )
    {
    CHgScroller* self = static_cast<CHgScroller*>(aSelf);
    if( self->IsDisplayed( self->iSelectedIndex ) )
        {
        self->DrawDeferred();
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleGainingForeground()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleGainingForeground()
    {
    iSelectionMode = ENoSelection;
    TRect rect( PositionRelativeToScreen(), Size() );
    TRAP_IGNORE( InitScreenL( rect ); )
    iScrollbar->Reset();
    }

// -----------------------------------------------------------------------------
// CHgScroller::HandleLosingForeground()
// -----------------------------------------------------------------------------
//
void CHgScroller::HandleLosingForeground()
    {
    iPointerDown = EFalse;
    iPopupText1.Zero();
    iPopupText2.Zero();
    }

// ---------------------------------------------------------------------------
// CHgScroller::LaunchHighlightTimer()
// ---------------------------------------------------------------------------
//     
void CHgScroller::LaunchHighlightTimer()
    {
    if ( !iHighlightTimer )
        {
        return;
        }

    TInt highlightTimeout( 0 );
    if ( iPhysics )
        {
        highlightTimeout = iPhysics->HighlightTimeout() * 1000;
        }
    if ( highlightTimeout == 0 )
        {
        highlightTimeout = KDefaultHighlightTimeout;
        }

    iHighlightTimer->Cancel();
    iHighlightTimer->Start( 
        TTimeIntervalMicroSeconds32( highlightTimeout ),
        TTimeIntervalMicroSeconds32( highlightTimeout ), 
        TCallBack( HighlightTimerCallback, this ) );
    }


// ---------------------------------------------------------------------------
// CHgScroller::HighlightTimerCallback()
// ---------------------------------------------------------------------------
//     
TInt CHgScroller::HighlightTimerCallback( TAny* aPtr )
    {
    CHgScroller* scroller = 
        static_cast<CHgScroller*>( aPtr );

    TInt err = KErrNotFound;
        
    if ( scroller  )
        {
        TRAP( err, scroller->SetHighlightL() );
        }
    
    return err;
    }

// ---------------------------------------------------------------------------
// CHgScroller::SetHighlightL()
// ---------------------------------------------------------------------------
//     
void CHgScroller::SetHighlightL()
    {
    iHighlightTimer->Cancel();

    TInt index = GetSelected(iStart);
    if((index != KErrNotFound || !HasHighlight())
            && iPointerDown )
        {
        iSelectionToFocusedItem = index == iSelectedIndex;            
        iSelectedIndex = index;
        iFocusedIndex = index;
        // Selection has changed to valid item
        if( !iSelectionToFocusedItem && iSelectedIndex != KErrNotFound ) 
            {
            if( iSelectionObserver )
                iSelectionObserver->HandleSelectL(iSelectedIndex);

            FitSelectionToView();
            SelectionChanged();
            iDrawUtils->ResetMarquee();
            }
        DrawDeferred();
        }
    }

// ---------------------------------------------------------------------------
// CHgScroller::SetSelectionMode()
// ---------------------------------------------------------------------------
//     
void CHgScroller::SetSelectionMode( TSelectionMode aMode )
    {
    iSelectionMode = aMode;
    if( iSelectionMode == ESelectionPossible
            || iSelectionMode == ENoSelection )
        {
        iCoeEnv->InputCapabilitiesChanged();
        }
    }

// ---------------------------------------------------------------------------
// CHgScroller::SelectionMode()
// ---------------------------------------------------------------------------
//     
CHgScroller::TSelectionMode CHgScroller::SelectionMode() const
    {
    return iSelectionMode;
    }

// ---------------------------------------------------------------------------
// CHgScroller::KeyScrollingTimerCallback()
// ---------------------------------------------------------------------------
//     
TInt CHgScroller::KeyScrollingTimerCallback( TAny* aPtr )
    {
    CHgScroller* scroller = 
        static_cast<CHgScroller*>( aPtr );

    TInt err = KErrNotFound;
        
    if ( scroller  )
        {
        scroller->DoKeyScrolling();
        err = KErrNone;
        }
    
    return err;
    }

// ---------------------------------------------------------------------------
// CHgScroller::DoKeyScrolling()
// ---------------------------------------------------------------------------
//     
void CHgScroller::DoKeyScrolling()
    {
    TKeyEvent keyevent;
    
    switch( iKeyScrollingState )
        {
        case EKeyScrollingUp:
            {
            keyevent.iCode = EKeyUpArrow;
            HandleKeyEvent( keyevent );
            break;
            }
        case EKeyScrollingDown:
            {
            keyevent.iCode = EKeyDownArrow;
            HandleKeyEvent( keyevent );
            break;
            }
        case EKeyScrollingLeft:
            {
            keyevent.iCode = EKeyLeftArrow;
            HandleKeyEvent( keyevent );
            break;
            }
        case EKeyScrollingRight:        
            {
            keyevent.iCode = EKeyRightArrow;
            HandleKeyEvent( keyevent );
            break;
            }
        case ENoKeyScrolling:
        default:
            StopKeyScrolling();
            break;
        }

    DrawNow();
    }

// ---------------------------------------------------------------------------
// CHgScroller::StopKeyScrolling()
// ---------------------------------------------------------------------------
//     
void CHgScroller::StopKeyScrolling()
    {    
    iKeyScrollingTimer->Cancel();
    iKeyScrollingState = ENoKeyScrolling;
    }

// ---------------------------------------------------------------------------
// CHgScroller::FocusChanged()
// ---------------------------------------------------------------------------
//     
void CHgScroller::FocusChanged(TDrawNow aDrawNow)
    {
    if( iKeyUtils )
        {
        if( !(iFlags & EHgScrollerKeyMarkingDisabled) )
            {
            if(IsFocused())
                {
                iKeyUtils->HandleGainingFocus();
                }
            else
                {
                iKeyUtils->HandleLosingFocus();
                }
            }
        else
            {
            iKeyUtils->HandleLosingFocus();
            }
        }

    CCoeControl::FocusChanged( aDrawNow );
    }

// ---------------------------------------------------------------------------
// CHgScroller::HandleResourceChange()
// ---------------------------------------------------------------------------
//     
void CHgScroller::HandleResourceChange( TInt aType )
    {
    TRAP_IGNORE(
            // When skin changes the indicator icons must be reloaded.
        if ( aType == KAknsMessageSkinChange )
            {
            delete iIndicatorManager; iIndicatorManager = NULL;
            iIndicatorManager = CHgIndicatorManager::NewL();
            InitGraphicsL();
            }
        )
    }

// ---------------------------------------------------------------------------
// CHgScroller::HandleLongTapEventL()
// ---------------------------------------------------------------------------
//     
void CHgScroller::HandleLongTapEventL( const TPoint& /*aPenEventLocation*/,
                        const TPoint& aPenEventScreenLocation)
    {
    if( iActionMenu )
        {
        iPointerDown = EFalse;
        iActionMenu->ShowMenuL(aPenEventScreenLocation);
        }
    }

// ---------------------------------------------------------------------------
// CHgScroller::CollectionState()
// ---------------------------------------------------------------------------
//     
TUint CHgScroller::CollectionState() const
    {
    TUint ret = 0;
    
    if(IsFocused()) ret |= MAknCollection::EStateCollectionVisible;
    
    if(HasHighlight()) ret |= MAknCollection::EStateHighlightVisible; 
    
    if( iFlags & EHgScrollerSelectionMode ) ret |= MAknCollection::EStateMultipleSelection;
    
    return ret; 
    }

// ---------------------------------------------------------------------------
// CHgScroller::CollectionState()
// ---------------------------------------------------------------------------
//     
void CHgScroller::ItemActionMenuClosed()
    {
    DrawDeferred();
    }

// ---------------------------------------------------------------------------
// CHgScroller::CollectionState()
// ---------------------------------------------------------------------------
//     
TInt CHgScroller::CollectionExtension( TUint /*aExtensionId*/, TAny*& /*a0*/, TAny* /*a1*/ )
    {
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CHgScroller::HasHighlight()
// ---------------------------------------------------------------------------
//     
TBool CHgScroller::HasHighlight() const
    {
    return (iActionMenu == NULL) || iShowHighlight || (iFlags & EHgScrollerForceDoubleClick);
    }

// ---------------------------------------------------------------------------
// CHgScroller::ReleasePopupFont()
// ---------------------------------------------------------------------------
//     
void CHgScroller::ReleasePopupFont()
    {
    if (iPopupFont)
        {
        iCoeEnv->ScreenDevice()->ReleaseFont(iPopupFont);
        iPopupFont = NULL;
        }
    }

// ---------------------------------------------------------------------------
// CHgScroller::SetMenuProviderL()
// ---------------------------------------------------------------------------
//     
EXPORT_C void CHgScroller::SetMenuProviderL( MObjectProvider* aMenuProvider )
    {
    SetMopParent(aMenuProvider);
    
    if( iActionMenu )
        {
        iActionMenu->RemoveCollection( *this );
        iActionMenu = NULL;
        }
    
    CAknAppUi* appUi = static_cast<CAknAppUi*>(iEikonEnv->AppUi());
    if( appUi && appUi->IsSingleClickCompatible() )
        {
        iActionMenu = CAknItemActionMenu::RegisterCollectionL( *this, this );
        }
    }


// End of File
