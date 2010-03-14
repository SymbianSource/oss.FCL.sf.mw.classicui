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
#include <ganes/HgVgMediaWall.h>
#include <ganes/HgVgMediaWallObserverIface.h>
#include <ganes/HgScroller.h>

#include "HgVgDrawBuffer.h"
#include "HgVgScrollBar.h"
#include "HgVgHelper.h"
#include "HgVgMediaWallRenderer.h"
#include "HgVgSkinRenderer.h"
#include "HgVgTimer.h"
#include "HgVgLetterPopup.h"
#include "HgVgButton.h"
#include "HgVgLabel.h"
#include "HgVgEGL.h"
#include "HgVgSpring.h"
#include "HgVgImageCreator.h"
#include "HgPopupDrawer.h"

#include <ganes/HgScrollBufferObserverIface.h>
#include <ganes/HgSelectionObserverIface.h>
#include <ganes/HgMarkingObserverIface.h>
#include <ganes/HgVgItem.h>
#include "HgScrollbar.h"
#include "HgScrollBufferManager.h"
#include "HgConstants.h"
#include "HgVgConstants.h"
#include <ganes.mbg>
//#include <aknappui.h>
#include <touchfeedback.h>
#include <gulicon.h>
#include <e32math.h>
#include <gulcolor.h>
#include <e32cmn.h> // Abs

#include <alf/alfcompositionutility.h>

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_apps.cdl.h>



using namespace AknTouchGestureFw;
using namespace HgVgConstants;



// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgMediaWall::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgMediaWall* CHgVgMediaWall::NewL(
        const TRect& aRect, 
        TInt aItemCount,
        THgVgMediaWallStyle aStyle,
        TBool aScrollBarEnabled,
        MObjectProvider* aParent,
        CGulIcon* aDefaultIcon )
    {
    CHgVgMediaWall* self = new ( ELeave ) CHgVgMediaWall( 
            aItemCount, 
            aDefaultIcon, aStyle, aScrollBarEnabled );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aParent );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::ConstructL (const TRect& aRect, MObjectProvider* aParent )
    {
    iPopupText1.CreateL( KMaxPopupTextLength );
    iPopupText2.CreateL( KMaxPopupTextLength );    

    iSpring = new (ELeave) THgVgSpring(KSpringK, KSpringDamping, 
            KMaxSpringVelocity, KPositionSnap, KMinSpringVelocity);
    
    iSpring->Reset(0,0);
                
    iAnimationTimer = CHgVgTimer::NewL();
        
    iKeyScrollingTimer = CPeriodic::NewL( CActive::EPriorityStandard );

    SetEmptyTextL(KNullDesC);

    // Create a window for this application view
    CreateWindowL ( );
       
    EnableDragEvents();
    
    ClaimPointerGrab();

    InitScreenL( aRect );

    InitItemsL();
        
    HandleViewPositionChanged(ETrue);
    
    iCoeEnv->AddForegroundObserverL( *this );
            
    // setup Avkon gesture framework.
    iTouchFw = AknTouchGestureFw::CAknTouchGestureFw::NewL(*this, *this);
    iTouchFw->SetGestureInterestL(AknTouchGestureFw::EAknTouchGestureFwGroupDrag |
            AknTouchGestureFw::EAknTouchGestureFwGroupTap | 
            AknTouchGestureFw::EAknTouchGestureFwGroupFlick);
            
    ActivateL ( );

    SetMopParent( aParent );
                        
    // skin needs to be updated after parent is set.
    iSkinRenderer->UpdateSkinL(this, this);
    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::InitScreenL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::InitScreenL( const TRect& aRect )
    {               
    // Set the windows size       
    SetRect ( aRect );
        
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::RefreshScreen( TInt aIndex )
    {
    
    if( !iIsForeground  )
        {
        return;
        }
  
    //RDebug::Print(_L("\t\tMediaWall FirstIndexOnScreen=%d"), FirstIndexOnScreen());
    
    if( !iAnimationTimer->IsActive() )
        {    
        if( /*iMediaWallStyle == EHgVgMediaWallStyleGrid ||*/ 
                (aIndex >= FirstIndexOnScreen() && aIndex <= FirstIndexOnScreen() + ItemsOnScreen()) )
            {
  
            UpdateLabelsAndPopup();
            if(iFlags & EHgVgMediaWallDrawToWindowGC)
                {
                DrawNow();
                }
            else
                {
                DrawOpenVG();
                }
        
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::FirstIndexOnScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgVgMediaWall::FirstIndexOnScreen()
    {
    return iBufferPosition - iItemsOnScreen / 2;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgVgMediaWall::ItemsOnScreen()
    {
    return iItemsOnScreen;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgVgMediaWall::SelectedIndex()
    {
    return iSelectedIndex * iRowCount;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::RefreshScreen()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetSelectedIndex( TInt aIndex )
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        iUpdateScrollBar = ETrue;
        iSpring->Reset(aIndex / iRowCount, iSpring->EndY());
        HandleViewPositionChanged(ETrue);
        }
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::EnableScrollBufferL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::EnableScrollBufferL( 
        MHgScrollBufferObserver& aObserver, 
        TInt aBufferSize,
        TInt aBufferTreshold  )
    {

    delete iManager; 
    iManager = NULL;
    
    iManager = CHgScrollBufferManager::NewL(
            aObserver, 
            aBufferSize, 
            aBufferTreshold, 
            (TInt)iSpring->GetX() * iRowCount, 
            iItemCount);
    
    iManager->SetBufferOwner( *this );
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetSelectionObserver()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetSelectionObserver( MHgSelectionObserver& aObserver )
    {
    iSelectionObserver = &aObserver;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::CHgVgMediaWall()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgMediaWall::CHgVgMediaWall( 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon, 
        THgVgMediaWallStyle aStyle, 
        TBool aEnableScrollBar) :
    iItemCount(aItemCount),
    iItemsOnScreen(KMaxCoversVisible),
    iDefaultIcon( aDefaultIcon ),
    iAnimationState(EHgVgMediaWallAnimationStateIdle),
    iScrollBarEnabled(aEnableScrollBar),
    iMediaWallStyle(aStyle),
    iOpeningAnimationType(CHgVgMediaWall::EHgVgOpeningAnimationFlipToFront),
    iIsForeground(ETrue),
    iUsingDefaultIcon(ETrue),
    iRowCount(1),
    iCameraRotationFactor(KCameraRotationFactor),
    iCameraZoomFactor(KCameraZoomFactor),
    iSpringVelocityToAnimationFactor(KSpringVelocityToAnimationFactor),
    iPrevGridItem(KErrNotFound),
    iSelGridItem(KErrNotFound)
    // other intialized to 0 or EFalse
    {
    }
        
// -----------------------------------------------------------------------------
// CHgVgMediaWall::~CHgVgMediaWall()
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgMediaWall::~CHgVgMediaWall ( )
    {
    
    if (iAnimationTimer->IsActive())
        iAnimationTimer->Cancel();
        
    iItems.ResetAndDestroy();
    
    iCoeEnv->RemoveForegroundObserver( *this );
    
    if(MTouchFeedback::Instance())
        {
        MTouchFeedback::Instance()->RemoveFeedbackArea(this, 0);     
        }

    DestroyRendering();
        
    delete iTouchFw;    
    delete iEmptyText;
    delete iDefaultIcon;
    delete iManager;
    delete iKeyScrollingTimer;
    delete iAnimationTimer;
    //delete iCompositionSource;
    delete iEGL;
    delete iSpring;
    delete iSurfaceBitmap;
    
    iPopupText1.Close();
    iPopupText2.Close();

    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::Style()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgMediaWall::THgVgMediaWallStyle CHgVgMediaWall::Style() const
    {
    return iMediaWallStyle;
    }


// -----------------------------------------------------------------------------
// CHgVgMediaWall::OpeningAnimationType()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgMediaWall::THgVgOpeningAnimationType CHgVgMediaWall::OpeningAnimationType() const
    {
    return iOpeningAnimationType;
    }


// -----------------------------------------------------------------------------
// CHgVgMediaWall::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::Draw ( const TRect& /*aRect*/ ) const
    {
    //RDebug::Print(_L("CHgVgMediaWall::Draw begin"));

    CHgVgMediaWall* self = const_cast<CHgVgMediaWall*>(this);           

    if (iIsForeground)
        {
        if( iFlags & EHgVgMediaWallDrawToWindowGC )
            {
            CFbsBitmap* screenshot = NULL;
            screenshot = self->DrawToBitmap();
            if (screenshot)
                {
                SystemGc().BitBlt( Rect().iTl,screenshot );
                delete screenshot;
                }
            else
                {
                SystemGc().SetBrushColor(KRgbRed);
                SystemGc().Clear();
                }
            }
        else
            {
            
            // draw with alpha to make a hole to composition layer
            SystemGc().SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
            SystemGc().SetBrushColor(TRgb(0,0,0,0));
            SystemGc().Clear();
            
            DrawOpenVG();        
            }
        }
    else
        {
        if (iSurfaceBitmap)
            {
            //RDebug::Print(_L("CHgVgMediaWall::Draw blit screenshot"));

            SystemGc().BitBlt( Rect().iTl, iSurfaceBitmap );
            }
        else
            {
            //RDebug::Print(_L("CHgVgMediaWall::Draw clear red"));

            // we should not get here, ever
            // still, clear with red color for debug purposes
            SystemGc().SetBrushColor(KRgbRed);
            SystemGc().Clear();
            }
        }

    //RDebug::Print(_L("CHgVgMediaWall::Draw end"));
    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::SizeChanged ( )
    {
    
    iRect = Rect();    
    TRAPD(error, InitRenderingL(ETrue));
    if( error != KErrNone )
        {
        // if out of memory
        if (error == KErrNoMemory)
            {
            // free all resources
            FreeItemsImages();
            // try again
            TRAPD(error, InitRenderingL(ETrue));
            // if still fails, need to give up
            if (error != KErrNone)
                {
                User::Panic(_L("USER"), error);
                }
            // reload all images we can
            ReloadItemsImages();
            }
        else
            {
            // some other error occured during initialization
            // TODO: should we try again?
            User::Panic(_L("USER"), error);            
            }
        }
    
    if(MTouchFeedback::Instance())
        {
        MTouchFeedback::Instance()->SetFeedbackArea(this, 
                0, 
                iRect, 
                ETouchFeedbackBasic, 
                ETouchEventStylusDown);        
        }
    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::ChangeStyleL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::ChangeStyleL( THgVgMediaWallStyle aStyle, const TRect& aRect, TBool /*aReuseSurface*/ )
    {
    
    // If animation is on, stop it before changing style.    
    HandleTransitionAnimationStop();
               
    iMediaWallStyle = aStyle;

    iAnimationState = EHgVgMediaWallAnimationStateIdle;
        
    // TODO: if (!aReUseSurface...)

    InitScreenL( aRect );
    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandleItemCountChaged()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleItemCountChanged()
    {

    TRAP_IGNORE( InitScrollBarL(ETrue); )
    
    if( iSelectedIndex >= MaxViewPosition() )
        {
        iSpring->Reset((TReal)(MaxViewPosition()-1), 0);
        HandleViewPositionChanged();         
        }
        
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandlePointerEventL()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::HandlePointerEventL( const TPointerEvent& aEvent )
    {
    
    if (iAnimationState != EHgVgMediaWallAnimationStateItemOpened)
        {
            
        // handle buttons
        iButtonsHit = HandleButtons(aEvent);
        
        if (iScrollBar && iScrollBar->HandlePointerEventL(aEvent))
            {
            iScrollBarHit = ETrue;
            }        
        if (aEvent.iType == TPointerEvent::EButton1Up)
            {
            iScrollBarHit = EFalse;
            // need to draw once at this point if animation is not going
            // on because the state has changed (when finger is lifted popup must disappear)
            if (!iAnimationTimer->IsActive())
                {
                DrawOpenVG();
                }
            }
                    
        }
    
    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::OfferKeyEventL()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgVgMediaWall::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if (iIsForeground)
        {    
        switch( aType )        
            {
            case EEventKeyDown:
                HandleKeyDown();
                break;
            case EEventKey:    
                return HandleKeyEvent( aKeyEvent );
            case EEventKeyUp:
                HandleKeyUp();
                break;
            default:
                break;
            }
        }
    
    // Let CCoeControl handle other cases.
    return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetItem(CHgVgItem* aItem, TInt aIndex)
    {
    if( aItem && aIndex >= 0 && aIndex < iItems.Count() )
        {
        delete iItems[aIndex];
        iItems[aIndex] = aItem;
        }
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::AddItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::AddItem(CHgVgItem* aItem)
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
// CHgVgMediaWall::InsertItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::InsertItem(CHgVgItem* aItem, TInt aIndex)
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
// CHgVgMediaWall::RemoveItem()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::RemoveItem(TInt aIndex)
    {
    if( aIndex >= 0 && aIndex < iItems.Count() )
        {
        delete iItems[aIndex]; 
        iItems[aIndex] = NULL;
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
// CHgVgMediaWall::ResizeL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::ResizeL( TInt aItemCount )
    {
    // Add More
    if( iItems.Count() < aItemCount )
        {
        while( iItems.Count() < aItemCount )
            {
            iItems.AppendL( CHgVgItem::NewL() );
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
// CHgVgMediaWall::ItemL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgItem& CHgVgMediaWall::ItemL(TInt aIndex)
    {
    if( aIndex < 0 || aIndex >= iItems.Count() )
        {
        User::Leave( KErrArgument );
        }

    return *iItems[aIndex];
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandleViewPositionChanged()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleViewPositionChanged(TBool aDontUpdateObserver)
    {
    // save previous index
    TInt prevIndex = iSelectedIndex;    
    
    // calculate new selected index
    TReal frac;
    Math::Frac(frac, iSpring->GetX());
    iSelectedIndex = (frac > 0.5f) ? iSpring->GetX() + 1 : iSpring->GetX();
   
    // limit index to items    
    if (iSelectedIndex < 0)
        iSelectedIndex = 0;
    else if (iSelectedIndex >= MaxViewPosition())
        iSelectedIndex = MaxViewPosition() - 1;

    // if index has changed
    if (iSelectedIndex != prevIndex)
        {
        // update titles
        UpdateLabelsAndPopup();

        // update scrollbar if needed
        if (iUpdateScrollBar && iScrollBar)
            iScrollBar->SetViewPosition(TPoint((TInt)iSelectedIndex, 0));

        }
                
    // inform observer if needed
    if (iMediaWallStyle != EHgVgMediaWallStyleGrid && 
            (iItems.Count() > 0 && iSelectionObserver && !aDontUpdateObserver && !iPointerDown))
        {
        TRAP_IGNORE(iSelectionObserver->HandleSelectL(iSelectedIndex, this);)
        }

    // update scroll buffer manager position
    TInt newCol = (TInt)iSpring->GetX() * iRowCount;    
    if( newCol != iBufferPosition )
        {
        iBufferPosition = newCol;
        if( iManager )
            {
            iManager->SetPosition((TInt)iBufferPosition);
            }
        }  
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandleKeyDown()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleKeyDown()
    {
    iKeyRepeats = 0;
    iKeyScrollingState = ENoKeyScrolling;    
    iPointerDown = EFalse;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandleKeyEvent()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgVgMediaWall::HandleKeyEvent(const TKeyEvent& aKeyEvent)
    {
    iKeyRepeats++;

    TKeyScrollingState possibleKeyScrollingState = ENoKeyScrolling;

    TBool handled = EFalse;
    
    // handle input
    switch( aKeyEvent.iCode )
        {
        case EKeyUpArrow:
            {
            if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                {
            
                TInt posY = (TInt)iSpring->EndY();
                TInt posX = (TInt)iSpring->EndX();
                            
                posY--;
                if (posY < 0)
                    {
                    if (posX > 0)
                        {
                        posX--;
                        posY = iRowCount - 1;
                        }
                    else
                        {
                        posY = 0;
                        }
                    }
    
                BeginSelection(posX * iRowCount + posY);
    
                possibleKeyScrollingState = EKeyScrollingUp;
                handled = ETrue;
                }
            
            } break;
        case EKeyDownArrow:
            {
            
            if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                {
    
                TInt posY = (TInt)iSpring->EndY();
                TInt posX = (TInt)iSpring->EndX();
                
                posY++;
                if (posY >= iRowCount)
                    {
                    if (posX < MaxViewPosition())
                        {
                        posY = 0;
                        posX++;
                        }
                    else
                        {
                        posY = iRowCount - 1;
                        }
                    }            
                
                BeginSelection(posX * iRowCount + posY);
    
                possibleKeyScrollingState = EKeyScrollingDown;
                handled = ETrue;
            
                }
            
            } break;
        case EKeyLeftArrow:
            {
            TInt posY = (TInt)iSpring->EndY();
            TInt posX = (TInt)iSpring->EndX();

            if (AknLayoutUtils::LayoutMirrored())
                {
                posX++;
                }
            else
                {
                posX--;
                }

            BeginSelection(posX * iRowCount + posY);
            
            possibleKeyScrollingState = EKeyScrollingLeft;
            handled = ETrue;
            } break;
        case EKeyRightArrow:
            {
            TInt posY = (TInt)iSpring->EndY();
            TInt posX = (TInt)iSpring->EndX();

            if (!AknLayoutUtils::LayoutMirrored())
                {
                posX++;
                }
            else
                {
                posX--;
                }

            BeginSelection(posX * iRowCount + posY);

            possibleKeyScrollingState = EKeyScrollingRight;
            handled = ETrue;
            } break;
        case EKeyEnter:
            {
            if( iSelectedIndex != KErrNotFound && iSelectionObserver )
                {
                TRAP_IGNORE( StartOpeningAnimationL(ETrue ); )                
                return EKeyWasConsumed;
                }
            return EKeyWasNotConsumed;
            }
        default: 
            break;
        }
    
    // start key scrolling timer if enough key repeats hit
    // and we are not yet scrolling
    if( possibleKeyScrollingState != ENoKeyScrolling && iKeyRepeats > KPhysLaunchKeyCount )
        {
        if( !iKeyScrollingTimer->IsActive() )
            {
            iKeyScrollingState = possibleKeyScrollingState;
            iKeyScrollingTimer->Start(
                    TTimeIntervalMicroSeconds32( 0 ),
                    TTimeIntervalMicroSeconds32( KMediaWallKeyScrollingUpdateInterval ), 
                    TCallBack( KeyScrollingTimerCallback, this ) );
            }
        }
        
    return handled ? EKeyWasConsumed : EKeyWasNotConsumed;
    }
    
// -----------------------------------------------------------------------------
// CHgVgMediaWall::HandleKeyUp()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleKeyUp()
    {
    StopKeyScrolling();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::StopKeyScrolling()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::StopKeyScrolling()
    {
    if (iKeyScrollingTimer->IsActive())
        iKeyScrollingTimer->Cancel();
    
    iKeyScrollingState = ENoKeyScrolling;    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::DoKeyScrolling()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::DoKeyScrolling()
    {
    TKeyEvent keyEvent;
    if (iKeyScrollingState == EKeyScrollingRight)
        {
        keyEvent.iCode = EKeyRightArrow;        
        HandleKeyEvent(keyEvent);        
        }
    else if (iKeyScrollingState == EKeyScrollingLeft)
        {
        keyEvent.iCode = EKeyLeftArrow;
        HandleKeyEvent(keyEvent);
        }
    else if (iKeyScrollingState == EKeyScrollingUp)
        {
        keyEvent.iCode = EKeyUpArrow;
        HandleKeyEvent(keyEvent);    
        }
    else if (iKeyScrollingState == EKeyScrollingDown)
        {
        keyEvent.iCode = EKeyDownArrow;
        HandleKeyEvent(keyEvent);        
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::KeyScrollingTimerCallback()
// ---------------------------------------------------------------------------
//     
TInt CHgVgMediaWall::KeyScrollingTimerCallback( TAny* aPtr )
    {
    CHgVgMediaWall* self = 
        static_cast<CHgVgMediaWall*>( aPtr );

    TInt err = KErrNotFound;
        
    if ( self  )
        {
        self->DoKeyScrolling();
        err = KErrNone;
        }
    
    return err;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::Release()
// From MHgBufferOwner
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::Release(TInt aReleaseStart, TInt aReleaseEnd)
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
// CHgVgMediaWall::Reset()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::Reset()
    {
    iItems.ResetAndDestroy();
    iItemCount = 0;
    HandleItemCountChanged();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetEmptyTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetEmptyTextL( const TDesC& aEmptyText )
    {
    delete iEmptyText;
    iEmptyText = 0;
    iEmptyText = aEmptyText.AllocL();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::ItemCount()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgVgMediaWall::ItemCount() const
    {
    return iItems.Count();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetDefaultIconL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetDefaultIconL( CGulIcon* aDefaultIcon )
    {
    
    if (iDefaultIcon)
        {
        delete iDefaultIcon;
        }
    
    iDefaultIcon = aDefaultIcon;
    
    iUsingDefaultIcon = EFalse;
    
    InitDefaultIconL();

    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::DisableScrollBuffer()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::DisableScrollBuffer()
    {
    delete iManager;
    iManager = NULL;
    }


// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetObserver()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetObserver(MHgVgMediaWallObserver* aObserver)
    {
    iMediaWallObserver = aObserver;
    }


// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetSelectionAnimationType()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetOpeningAnimationType(THgVgOpeningAnimationType aType)
    {
    iOpeningAnimationType = aType;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::StartOpeningAnimation()
// ---------------------------------------------------------------------------
//     
EXPORT_C void CHgVgMediaWall::StartOpeningAnimationL(TBool aOpening)
    {
    // stop possible animation
    HandleTransitionAnimationStop();

    if (iOpeningAnimationType == EHgVgOpeningAnimationNone)
        {
        if (iSelectionObserver)
            {
            if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                {
                iSelectionObserver->HandleOpenL(iPickedGridItem, this);
                }
            else
                {
                iSelectionObserver->HandleOpenL((TInt)iSpring->EndX(), this);            
                }
            }
        }
    else
        {
        iAnimationState = aOpening ? EHgVgMediaWallAnimationStateOpening : EHgVgMediaWallAnimationStateClosing;        
        
        StartAnimationTimer();        
        }    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawToWindow()
// ---------------------------------------------------------------------------
//     
CFbsBitmap* CHgVgMediaWall::DrawToBitmap()
    {

    if (!DrawAll())
        return NULL;
        
    return iEGL->GetSurfaceToBitmap(iRect);
        
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::InitDefaultIconL()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::InitDefaultIconL()
    {  
    // if no icon is set, load ganes default icon
    if (!iDefaultIcon && iUsingDefaultIcon)
        {
        
        iDefaultIcon = CreateIconL(EMbmGanesQgn_prop_checkbox_on, 
                EMbmGanesQgn_prop_checkbox_on_mask, 
                iRenderer->ImageSize());
        
        }

    if (iDefaultIcon && iRenderer)
        {
        iRenderer->SetDefaultIconL(*iDefaultIcon);
        }        

    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::FocusChanged()
// From CCoeControl
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleResourceChange()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::HandleResourceChange( TInt aType )
    {
    if ( aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE (
                InitButtonsL();
                InitScrollBarL(ETrue);
                if (iRenderer)
                    iRenderer->HandleSkinChange();
                // if the default icon is not set by client, 
                // we need to reload our new default icon from skin.
                if (iUsingDefaultIcon)
                    {
                    delete iDefaultIcon;
                    iDefaultIcon = NULL;
                    InitDefaultIconL();
                    }
                if (iSkinRenderer)    
                    iSkinRenderer->UpdateSkinL(this, this);
                )
        }    
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::InitItemsL()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::InitItemsL()
    {
    for(TInt i = 0; i < iItemCount; ++i)
        {
        iItems.Append( CHgVgItem::NewL() );
        }    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleGainingForeground()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::HandleGainingForeground()
    {
    
    // draw previous screenshot
    DrawNow();
        
    // delete it
    delete iSurfaceBitmap;
    iSurfaceBitmap = NULL;

    iIsForeground = ETrue;

    // init egl and openvg again
    TRAP_IGNORE( InitRenderingL(EFalse); )
    
    // reload images to ive
    ReloadItemsImages();
        
    // draw using openvg
    DrawNow();
    
    }    

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleLosingForeground()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::HandleLosingForeground()
    {
    
    // make sure we are not animating
    HandleTransitionAnimationStop();
    
    if (iAnimationTimer->IsActive())
        {
        if (iAnimationState == EHgVgMediaWallAnimationStateClosing)
            iAnimationState = EHgVgMediaWallAnimationStateIdle;
        else if (iAnimationState == EHgVgMediaWallAnimationStateOpening)
            iAnimationState = EHgVgMediaWallAnimationStateItemOpened;
        else
            iAnimationState = EHgVgMediaWallAnimationStateIdle;

        iAnimationTimer->Cancel();
        }

    iIsForeground = EFalse;
    
    // take a screenshot 
    delete iSurfaceBitmap;
    iSurfaceBitmap = NULL;
    iSurfaceBitmap = DrawToBitmap();

    // draw screenshot using window gc, this is needed
    // for nga effects to work
    DrawNow();
    
    // free textures    
    FreeItemsImages();
    // free other resources
    DestroyRendering();
    
    iCoeEnv->WsSession().Flush();

    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawOpenVG()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::DrawOpenVG() const
    {
    
    if( iFlags & EHgVgMediaWallDrawToWindowGC || !iIsForeground )
        {
        // Window GC drawing mode is on or we are on backround.
        return;
        }    
    
    CHgVgMediaWall* self = const_cast<CHgVgMediaWall*>(this);           
        
    //RDebug::Print(_L("\t\tMediaWall FirstIndexOnScreen=%d"), self->FirstIndexOnScreen());

    if (!self->DrawAll())
        return;
      
    iEGL->SwapBuffers();
    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DoAnimation()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::DoAnimation()
    {    
    switch (iAnimationState)
        {
        case EHgVgMediaWallAnimationStateTransition:
        case EHgVgMediaWallAnimationStateFastTransition:
            {
            DoTransitionAnimation();
            } break;
        case EHgVgMediaWallAnimationStateOpening:
        case EHgVgMediaWallAnimationStateClosing:
        case EHgVgMediaWallAnimationStateIdle:
        case EHgVgMediaWallAnimationStateItemOpened:
            {
            DoSelectionAnimation();
            } break;
        }

    DrawOpenVG();
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DoSelectionAnimation()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::DoSelectionAnimation()
    {
    TTime now;
    now.HomeTime();
    TInt diff = now.MicroSecondsFrom(iAnimationStartTime).Int64();        
    
    // limit to max duration
    if (diff > KSelectionAnimationDuration)
        diff = KSelectionAnimationDuration;
    
    // calculate animation alpha
    TReal alpha = (TReal)diff / (TReal)KSelectionAnimationDuration;

    switch (iAnimationState)
        {
        case EHgVgMediaWallAnimationStateClosing:
            {
            iAnimationAlpha = 1.0f - alpha;
            if (diff == KSelectionAnimationDuration)
                iAnimationState = EHgVgMediaWallAnimationStateIdle;            
            } break;
        case EHgVgMediaWallAnimationStateOpening:
            {
            iAnimationAlpha = alpha;
            if (diff == KSelectionAnimationDuration)
                iAnimationState = EHgVgMediaWallAnimationStateItemOpened;
            } break;
        case EHgVgMediaWallAnimationStateItemOpened:
            {
            iAnimationTimer->Cancel();
            if (iSelectionObserver)
                {   
                if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                    {
                    TRAP_IGNORE( iSelectionObserver->HandleOpenL(iPickedGridItem, this); )                    
                    }
                else
                    {
                    TRAP_IGNORE( iSelectionObserver->HandleOpenL(iSelectedIndex, this); )
                    }
                }
            } break;
        case EHgVgMediaWallAnimationStateIdle:
            {
            iAnimationTimer->Cancel();
            } break;
        }    
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::DoTransitionAnimation()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::DoTransitionAnimation()
    {
    TTime now;
    now.HomeTime();
    TReal deltaTime = (TReal)now.MicroSecondsFrom(iPrevTime).Int64() / (TReal)KOneSecondInMicroSeconds;        
    iPrevTime = now;
    
    if (iSpring->IntegratePhysics(deltaTime, !iPointerDown))
        {
        // snap
        HandleTransitionAnimationStop();    
        }
    else
        {
        // update view position dependant stuff
        HandleViewPositionChanged(ETrue);    
        }
                        
    }

void CHgVgMediaWall::HandleTransitionAnimationStop()
    {
    if (iAnimationTimer->IsActive() && (iAnimationState == EHgVgMediaWallAnimationStateTransition ||
            iAnimationState == EHgVgMediaWallAnimationStateFastTransition))
        {
        // stop to this location
        iSpring->Reset();    
        iAnimationState = EHgVgMediaWallAnimationStateIdle;
    
        // cancel animation
        iAnimationTimer->Cancel();
    
        // handle view position change
        HandleViewPositionChanged();
        }
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::AnimationTimerCallback()
// Timer callback for selection animation.
// ---------------------------------------------------------------------------
//     
TInt CHgVgMediaWall::AnimationTimerCallback( TAny* aPtr )
    {
    CHgVgMediaWall* scroller = static_cast<CHgVgMediaWall*>(aPtr);

    TInt err = KErrNotFound;

    if( scroller )
        {
        scroller->DoAnimation();
        err = KErrNone;
        }

    return err;        
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::ScrollBarViewPositionChanged()
// Called by scroll bar when its position has changed.
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::ScrollBarPositionChanged( const TPoint& aNewPosition )
    {
    iScrollBarHit = ETrue;
    if (iSpring->GetX() != aNewPosition.iX)
        {
        StartAnimationToPosition(aNewPosition.iX, EFalse);
        }
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleNaviStripChar()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::HandleNaviStripChar( const TChar& /*aChar*/ )
    {
    // do nothing
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::UpdateTitles()
// Updates album and artist titles.
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::UpdateLabelsAndPopup()
    {
    if (iItems.Count() == 0)
        return;
    
    CHgVgItem* item = NULL;
    
    if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
        {
        TInt pos = (iSpring->GetX() * (TReal)KGridRowCount);
        if (pos >= 0 && pos < iItems.Count() && iItems.Count() == iItemCount)
            {
            item = iItems[pos];
            }
        }
    else
        {
        if (iSelectedIndex >= 0 && iSelectedIndex < iItems.Count())
            item = iItems[iSelectedIndex];
        }
        
    // set album and artist titles from item
    if( item )
        {
        if (iArtistLabel && iAlbumLabel)
            {
            TRAP_IGNORE(
            iArtistLabel->SetTextL(item->Title());
            iAlbumLabel->SetTextL(item->Text()); )
            }
        
        if (iLetterPopup)
            {
            if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                {
                if (item != iTempItem)
                    {
                    iTempItem = item;

                    TRAP_IGNORE(
                    item->Time().FormatL( iPopupText1, KGanesMonthString );
                    item->Time().FormatL( iPopupText2, KGanesYearString );
                        )
                    
                    // To display year correctly in arabic.
                    AknTextUtils::LanguageSpecificNumberConversion( iPopupText2 );
    
                    iLetterPopup->SetTexts(iPopupText1, iPopupText2); 
                    }
                }
            else
                {
                TRAP_IGNORE( iLetterPopup->SetTextL(item->Title().Left(1)); )
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawTitles()
// Draws album and artist titles.
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::DrawTitles(TReal aAlpha)    
    {
    TReal alpha = aAlpha;
    if( iAnimationState == EHgVgMediaWallAnimationStateOpening || 
            iAnimationState == EHgVgMediaWallAnimationStateClosing)
        {
        alpha = 1.0f - iAnimationAlpha;
        }
    else if (iAnimationState == EHgVgMediaWallAnimationStateItemOpened)
        {
        alpha = 0.0f;
        }

    if( iAlbumLabel && iArtistLabel )
        {
        iArtistLabel->Draw(iRect, alpha);
        iAlbumLabel->Draw(iRect, alpha);
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::InitScrollBarL()
// Inits scroll bar
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWall::InitScrollBarL(TBool /*aResize*/)
    {
    delete iScrollBar;
    iScrollBar = NULL;
    
    if (iMediaWallStyle != CHgVgMediaWall::EHgVgMediaWallStyleCoverflowFullScreen &&
        iMediaWallStyle != CHgVgMediaWall::EHgVgMediaWallStyleGrid)
        return;
        
    iScrollBar = CHgVgScrollBar::NewL(*this, iRect,
            TSize(MaxViewPosition(), 1), TSize(1, 1), 
            ETrue, CHgScroller::EHgScrollerScrollBar);
    
    iScrollBar->SetViewPosition( TPoint(iSelectedIndex, 0) );        
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::InitRenderingL()
// Inits all rendering.
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::InitRenderingL(TBool aRecreateSurface)
    {
    if (!iEGL)
        {
        iEGL = CHgVgEGL::NewL(Window());
        CHgVgImageCreator::InstanceL()->Initialize(iEGL);
        }
    else
        {
        if (aRecreateSurface)
            iEGL->InitWindowSurfaceL(Window());
        }

    delete iRenderer; iRenderer = NULL;    
    delete iArtistLabel; iArtistLabel = NULL;
    delete iAlbumLabel; iAlbumLabel = NULL;
    delete iLetterPopup; iLetterPopup = NULL;
    delete iSkinRenderer; iSkinRenderer = NULL;
    iSkinRenderer = CHgVgSkinRenderer::NewL(iRect);
    iSkinRenderer->UpdateSkinL(this, this);

    delete iEmptyLabel; iEmptyLabel = NULL;
    iEmptyLabel = CHgVgLabel::NewL(
            /*TRect(TPoint(iRect.Center().iX - 100, iRect.Center().iY - 50),
            TSize(200, 100))*/iRect, &ScreenFont( TCoeFont( KMediaWallGridPopupFontSize, TCoeFont::EPlain )), 
            *iEmptyText);
    
    switch (iMediaWallStyle)
        {
        case EHgVgMediaWallStyleCoverflowFullScreen:
            {
            InitMediaWallFullScreenLandscapeL();
            } break;
        case EHgVgMediaWallStyleCoverflowTBonePortrait:
            {
            InitMediaWallTBonePortraitL();
            } break;
        case EHgVgMediaWallStyleGrid:
            {
            InitMediaWallGridLandscapeL();                        
            } break;
        default: 
            {
            User::Leave(KErrNotSupported);
            } break;
        }
        
    // load default icon
    InitDefaultIconL();

    // invalidate selected index so
    // that HandleViewPositionChanged does
    // all updates needed.
    iSelectedIndex = KErrNotFound;
    HandleViewPositionChanged(ETrue);
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::InitButtonsL()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::InitButtonsL()
    {
        
    CGulIcon* icon = CreateIconL(EMbmGanesQgn_indi_button_exit_fs, 
            EMbmGanesQgn_indi_button_exit_fs_mask, TSize(41,41));
    
    CleanupStack::PushL(icon);
    
    delete iHideSKButton; iHideSKButton = NULL;
    
    TAknLayoutRect rect;
    rect.LayoutRect(iRect, AknLayoutScalable_Apps::main_cf0_pane_g1(0));
    
    iHideSKButton = CHgVgButton::NewL(rect.Rect().Size(), rect.Rect().iTl, *icon);

    CleanupStack::PopAndDestroy(icon);
    
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::CreateIconL()
// ---------------------------------------------------------------------------
//
CGulIcon* CHgVgMediaWall::CreateIconL(TInt aId1, TInt aId2, const TSize& aSize)
    {
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    
    AknIconUtils::CreateIconL( 
            bitmap, 
            mask, 
            KGanesMif, 
            aId1, 
            aId2 );
    
    CGulIcon* icon = CGulIcon::NewL(bitmap, mask);

    AknIconUtils::SetSize(icon->Bitmap(), 
            aSize);
    AknIconUtils::SetSize(icon->Mask(), 
            aSize);
    
    return icon;    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::FreeItemImages()
// Frees all loaded images.
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::FreeItemsImages()
    {
    for (TInt i = 0; i < iItems.Count(); i++)
        {
        iItems[i]->FreeOpenVgImage();
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::ReloadItemsImages()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::ReloadItemsImages()
    {
    for (TInt i = 0; i < iItems.Count(); i++)
        {
        iItems[i]->ReloadOpenVgImage();
        }
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleTouchGestureL()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleTouchGestureL( MAknTouchGestureFwEvent& aEvent )
    {
    
    if (iScrollBarHit || iButtonsHit || iAnimationState == EHgVgMediaWallAnimationStateOpening ||
            iAnimationState == EHgVgMediaWallAnimationStateClosing)
        return;
    
    if (iAnimationState == EHgVgMediaWallAnimationStateItemOpened)
        {
        StartOpeningAnimationL(EFalse);
        }
    else
        {
        
        switch (aEvent.Group())
            {
            case EAknTouchGestureFwGroupTap:
                {
                MAknTouchGestureFwTapEvent* tapEvent = AknTouchGestureFwEventTap(aEvent);            
                if (tapEvent && aEvent.Type() == EAknTouchGestureFwTap)
                    {
                    HandleTapEventL(tapEvent->Position());                    
                    }
                } break;
            case EAknTouchGestureFwGroupFlick:
                {
                MAknTouchGestureFwFlickEvent* flickEvent = AknTouchGestureFwEventFlick(aEvent);            
                if ((flickEvent && aEvent.Type() == EAknTouchGestureFwFlickLeft) ||
                    (flickEvent && aEvent.Type() == EAknTouchGestureFwFlickRight))
                    {
                    EndSelection();
                    HandleFlick(flickEvent->Speed());
                    }
                } break;         
            case EAknTouchGestureFwGroupDrag:
                {
                MAknTouchGestureFwDragEvent* dragEvent = AknTouchGestureFwEventDrag(aEvent);            
                if (dragEvent && aEvent.Type() == EAknTouchGestureFwDrag)
                    {
                    EndSelection();
                    HandleDragging(*dragEvent);
                    }
                } break;
            }
    
        }

    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleTapEvent()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleTapEventL(const TPoint& aPosition)
    {
    if (iRenderer)
        {
        TInt index = iRenderer->GetItemIndex(aPosition);
        if (index != KErrNotFound)
            {
            if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
                {
                iPickedGridItem = index;
                DoStartOpeningAnimationL();            
                }
            else
                {
                if (index == iSelectedIndex && index == (TInt)iSpring->EndX())
                    {
                    DoStartOpeningAnimationL();
                    }
                else
                    {
                    StartAnimationToPosition(index, ETrue);
                    }
                }
            }
        }          
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleFlick()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleFlick(const TPoint& aSpeed)
    {

    // mirror for mirrored layouts
    TInt speed = aSpeed.iX;
    if (AknLayoutUtils::LayoutMirrored())
        speed = -speed;
        
    TReal fspeed = GetAsPercentageOfScreenWidth((TReal)speed);
    
    if (Abs(fspeed) < KMinFlickSpeed) // Discard small and slow flicks
        return;
    
    TInt steps = -GetStepsFromSpeed(speed);

    iSpring->SetVelocity(iSpring->VelX() - fspeed, iSpring->VelY());
    
    if (Abs(steps) > 0)
        {
        TReal x = iSpring->EndX() + steps;
        x = Min(x, (TReal)(MaxViewPosition() - 1));
        x = Max(x, 0);
        if (x != iSpring->EndX())
            {
            StartAnimationToPosition(x, ETrue);
            }
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::GetStepsFromSpeed()
// ---------------------------------------------------------------------------
//
TInt CHgVgMediaWall::GetStepsFromSpeed(TInt aSpeed) const
    {
    TInt steps = aSpeed > 0 ? 1 : -1;    
    TReal speed = GetAsPercentageOfScreenWidth(aSpeed);
    TReal absSpeed = Abs(speed);    
    if (absSpeed > 1.0f)
        {
        steps = (TInt)(speed / KSwipeSpeedFactor);
        }
    return steps;
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleDragging()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleDragging(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent)
    {    

    switch (aEvent.State())
        {
        case AknTouchGestureFw::EAknTouchGestureFwStart:
            {
            HandleDragStart(aEvent);
            } break;
        case AknTouchGestureFw::EAknTouchGestureFwStop:
            {
            HandleDragStop(aEvent);
            } break;
        case AknTouchGestureFw::EAknTouchGestureFwOn:
            {
            HandleDragOn(aEvent);
           } break;            
        }                       
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleDragging()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::StartAnimationTimer()
    {
    
    // animation may start event when 
    // timer was previously active.
    iAnimationStartTime.HomeTime();
        
    if (!iAnimationTimer->IsActive())
        {
        iPrevTime.HomeTime();
        iAnimationTimer->Start(
            TTimeIntervalMicroSeconds32( 0 ),
            TTimeIntervalMicroSeconds32( KViewUpdateInterval ), 
            TCallBack( AnimationTimerCallback, this ) );
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::GetAsPercentageOfScreenWidth()
// ---------------------------------------------------------------------------
//
TReal CHgVgMediaWall::GetAsPercentageOfScreenWidth(TInt aPixels) const
    {
    return (TReal)aPixels / (TReal)iRect.Width();
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::GetAsPercentageOfScreenHeight()
// ---------------------------------------------------------------------------
//
TReal CHgVgMediaWall::GetAsPercentageOfScreenHeight(TInt aPixels) const
    {
    return (TReal)aPixels / (TReal)iRect.Height();
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawScene()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::DrawScene()
    {

    TReal t = iSpring->VelX() / iSpringVelocityToAnimationFactor;
    if (Abs(t) > 1.0f) 
        t = t / Abs(t);
  
    if (AknLayoutUtils::LayoutMirrored())
        t = -t;
    
    iRenderer->SetCameraRotation(-t * iCameraRotationFactor);
                
    if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
        {        
        TReal cameraY = (TReal)(iRowCount - 1) - iSpring->GetInterpolatedY();
        iRenderer->SetCameraPosition(0, 0,//cameraY * iRenderer->GetWorldSpaceRowHeight(), 
                -Abs(t)*iCameraZoomFactor);                                
        iRenderer->DrawGrid(iRowCount, iItems, 
                iSpring->GetInterpolatedX(), iSpring->GetInterpolatedY(),
                iSelGridItem, iPrevGridItem, iAnimationAlpha, iAnimationState, 
                iPickedGridItem, iOpeningAnimationType);
        }
    else
        {
        iRenderer->Draw(iItems, /*iSelectedIndex*/iSpring->GetX(), iSpring->EndX(), 
                iSpring->GetInterpolatedX(), iAnimationAlpha, iAnimationState, 
                iOpeningAnimationType, iMediaWallStyle, iSpring->StartX());
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleDragStart()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleDragStart(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& /*aEvent*/)
    {
    
    // cancel ongoing animation.
    if (iAnimationTimer->IsActive())
        {
        iAnimationTimer->Cancel();
        if (iMediaWallStyle != EHgVgMediaWallStyleGrid)
            {
            iSpring->SetEnd(iSelectedIndex, iSpring->EndY());
            }
        }
    
    iPointerDown = ETrue;
    iViewPositionAtDragStart = iSpring->GetX();
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleDragOn()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleDragOn(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent)
    {

    // calculate delta of dragging
    TInt delta = aEvent.StartPosition().iX - aEvent.CurrentPosition().iX;
    TReal fDelta = GetAsPercentageOfScreenWidth(delta);
    
    // flip for mirrored layout
    if (AknLayoutUtils::LayoutMirrored())
        {
        fDelta = -fDelta;
        }

    if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
        {
        // for grid we set new position to dragpos and start animation
        // to get camera rotation effect for dragging also.
        TReal newPosition = iViewPositionAtDragStart + fDelta * iItemsToMoveOnFullScreenDrag;
        StartAnimationToPosition(newPosition, ETrue);
        }
    else
        {
        // for normal mediawall we move view position according to drag
        TReal x = iViewPositionAtDragStart + fDelta * iItemsToMoveOnFullScreenDrag;
        iUpdateScrollBar = ETrue;
        iSpring->Reset(x, 0);
        HandleViewPositionChanged(ETrue);        
        // draw view at new view position
        DrawOpenVG();
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleDragStop()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::HandleDragStop(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& /*aEvent*/)
    {   
    iPointerDown = EFalse;
    if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
        {
        // if we dragged grids position outside bounds, 
        // we need to animate it back.
        TReal x = iSpring->EndX();
        x = Min(x, (TReal)(MaxViewPosition() - 1));
        x = Max(x, 0);
        if (x != iSpring->EndX())
            {
            StartAnimationToPosition(x, ETrue);
            }
        }
    else
        {
        // animate back to current selected index, because
        // we dont want to be between items in mediawall
        StartAnimationToPosition(iSelectedIndex, ETrue);
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawLetterStripAndTitles()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::DrawLetterStripAndTitles()
    {
    if (iItems.Count() == 0)
        {
        DrawTitles(1.0f);
        }
    else
        {
    
        // get distance to next target item
        TReal dist = Abs(iSpring->GetX() - iSpring->EndX());    
    
        if (iMediaWallStyle == EHgVgMediaWallStyleCoverflowTBonePortrait)
            {
            // we bring letter popup when we are far enough from next item 
            if (iLetterPopup && (dist > KDrawLetterPopupDistance && iSpring->GetX() >= 0 && iSpring->GetX() < iItems.Count()))
                {
                iLetterPopup->Draw(iRect, KMaxLetterPopupOpacity * Max(1.0f, (dist - KDrawLetterPopupDistance)/KDrawLetterPopupDistance));        
                }
            else
                {
                DrawTitles(1.0f - dist/KDrawLetterPopupDistance);                
                }
            }
        else if (iMediaWallStyle == EHgVgMediaWallStyleCoverflowFullScreen ||
                iMediaWallStyle == EHgVgMediaWallStyleGrid)
            {
            // when scrollbar is being dragged we draw letter popup
            if (iLetterPopup && (iScrollBarHit || (iKeyScrollingState != ENoKeyScrolling && dist > KDrawLetterPopupDistance)))
                {
                iLetterPopup->Draw(iRect, KMaxLetterPopupOpacity);                    
                }
            else
                {
                DrawTitles(1.0f);                                
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DrawButtonsAndScrollbar()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::DrawButtonsAndScrollbar()
    {
    if (iScrollBar || iHideSKButton)
        {
        TReal alpha = 1.0f;
        if (iAnimationState == EHgVgMediaWallAnimationStateOpening || iAnimationState == EHgVgMediaWallAnimationStateClosing)
            alpha = 1.0f - iAnimationAlpha;
        else if (iAnimationState == EHgVgMediaWallAnimationStateItemOpened)
            alpha = 0.0f;
        if (iScrollBar && iItems.Count() > 0)
            iScrollBar->Draw(iRect, alpha);
        if (iHideSKButton)
            iHideSKButton->Draw(iRect, alpha);
        }    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::HandleButtons()
// ---------------------------------------------------------------------------
//
TBool CHgVgMediaWall::HandleButtons(const TPointerEvent& aEvent)
    {
    // handle hitting buttons
    TBool ret = EFalse;
    if (iHideSKButton)
        {
        // if buttons is hit, hide scrollbar and button
        if (iHideSKButton->HandlePointerEvent(aEvent))
            {
            
            if (iScrollBar)
                iScrollBar->SetEnabled(EFalse);

            iHideSKButton->SetEnabled(EFalse);
            
            ret = ETrue;
            
            DrawOpenVG();

            if (iMediaWallObserver)
                iMediaWallObserver->HandleMediaWallEvent((TInt)EHgVgMediaWallEventRequestShowSoftkeys, this);

            }
        // if screen is hit when button is not visible, show button and scrollbar
        else if (!iHideSKButton->IsEnabled() && aEvent.iType == TPointerEvent::EButton1Down)
            {
            
            if (iScrollBar)    
                iScrollBar->SetEnabled(ETrue);
            
            iHideSKButton->SetEnabled(ETrue);
                       
            DrawOpenVG();

            if (iMediaWallObserver)
                iMediaWallObserver->HandleMediaWallEvent((TInt)EHgVgMediaWallEventRequestHideSoftkeys, this);
            
            }
        }
    
    return ret;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::MaxViewPosition()
// ---------------------------------------------------------------------------
//
TInt CHgVgMediaWall::MaxViewPosition() const
    {
    return iItemCount / iRowCount;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::BeginSelection()
// ---------------------------------------------------------------------------
//
TBool CHgVgMediaWall::BeginSelection(TInt aIndex)
    {
    if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
        {
        if (iSelectionObserver)
            {
            TRAP_IGNORE( iSelectionObserver->HandleSelectL(aIndex, this); )
            }
        iPrevGridItem = iSelGridItem;
        iSelGridItem = aIndex;
        iSelectionMode = ETrue;
        TInt x = aIndex / iRowCount;
        TInt y = aIndex % iRowCount;
        StartAnimationToPosition(x, y, ETrue);
        }
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::EndSelection()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::EndSelection()
    {
    if (iSelectionMode)
        {
        iSelGridItem = KErrNotFound;
        iPrevGridItem = KErrNotFound;
        iSelectionMode = EFalse;
        StartAnimationToPosition(iSpring->EndX(), iRowCount - 1, ETrue);
        }
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::DoStartOpeningAnimationL()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::DoStartOpeningAnimationL()
    {
    TBool opening = ETrue;
                      
    if (iAnimationState == EHgVgMediaWallAnimationStateItemOpened)
        opening = EFalse;
    
    StartOpeningAnimationL(opening);                    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::StartAnimationToPosition()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::StartAnimationToPosition(TReal aX, TBool aUpdateScrollBar)
    {
    StartAnimationToPosition(aX, iSpring->EndY(), aUpdateScrollBar);
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWall::StartAnimationToPosition()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWall::StartAnimationToPosition(TReal aX, TReal aY, TBool aUpdateScrollBar)
    {
    iSpring->SetEnd(aX, aY);
    iUpdateScrollBar = aUpdateScrollBar;
    iAnimationState = EHgVgMediaWallAnimationStateTransition;
    StartAnimationTimer();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetFlags()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetFlags(TInt aFlags)
    {
    iFlags |= aFlags;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::ClearFlags()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::ClearFlags(TInt aFlags)
    {
    iFlags &= ~aFlags;    
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::Flags()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgVgMediaWall::Flags()
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetItemToOpenedState()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetItemToOpenedState(TInt aIndex)
    {
    if (aIndex >= 0 && aIndex < iItemCount)
        {
        HandleTransitionAnimationStop();
        SetSelectedIndex(aIndex);
        if (iMediaWallStyle == EHgVgMediaWallStyleGrid)
            {
            iPickedGridItem = aIndex;
            }
        iAnimationAlpha = 1.0f;
        iAnimationState = EHgVgMediaWallAnimationStateItemOpened;
        }
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::SetFlippedRect()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgMediaWall::SetOpenedItemRect(const TRect& aRect)
    {
    if (iRenderer)
        {
        iRenderer->SetFlippedRect(aRect);
        }
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::DeleteComponents()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::DestroyRendering()
    {
    delete iHideSKButton; iHideSKButton = NULL;
    delete iScrollBar; iScrollBar = NULL;
    delete iRenderer; iRenderer = NULL;    
    delete iArtistLabel; iArtistLabel = NULL;
    delete iAlbumLabel; iAlbumLabel = NULL;
    delete iLetterPopup; iLetterPopup = NULL;
    delete iSkinRenderer; iSkinRenderer = NULL;
    delete iEmptyLabel; iEmptyLabel = NULL;
    delete iEGL; iEGL = NULL;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::DrawAll()
// -----------------------------------------------------------------------------
//
TBool CHgVgMediaWall::DrawAll()
    {
    if ( !iEGL || !iEGL->ReadyToRender() || !iRenderer )
        {
        return EFalse;
        }
    
    if (iSkinRenderer)
        iSkinRenderer->Draw();

    DrawScene();        
        
    DrawButtonsAndScrollbar();

    if (iItems.Count() == 0)
        {
        if (iEmptyLabel)
            {
            iEmptyLabel->DrawEmptyText(iRect, *iEmptyText);
            }
        }
    else
        {        
    
        DrawLetterStripAndTitles();        
        }
            
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::CreateMediaWallFullScreenLandscapeL()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::InitMediaWallFullScreenLandscapeL()
    {
                
    // set some factors to mediawall fullscreen mode specific values
    iCameraZoomFactor = KMediaWallFullScreenCameraZoomFactor;
    iCameraRotationFactor = KMediaWallFullScreenCameraRotationFactor;            
    iItemsOnScreen = KMediaWallFullScreenItemsOnScreen;
    iSpringVelocityToAnimationFactor = KMediaWallFullScreenSpringVelocityToAnimationFactor;
    iItemsToMoveOnFullScreenDrag = KMediaWallFullScreenItemsToMoveOnFullScreenDrag;
    iRowCount = KMediaWallFullScreenRowCount;
    
    // get front rectange from layout
    TAknLayoutRect frontRect;
    frontRect.LayoutRect( iRect, AknLayoutScalable_Apps::cf0_flow_pane_g1(0) );

    // set items at the back a bit further in the fullscreen mode.
    iRenderer = CHgVgMediaWallRenderer::NewL(KMaxCoversVisible, iRect, frontRect.Rect(), 
            KMediaWallFullScreenZOffset);

    // set some default flipped rect for opening animation
    iRenderer->SetFlippedRect(TRect(TPoint(iRect.Center().iX - iRect.Height() / 2,
            iRect.Center().iY - iRect.Height() / 2),
            TSize(iRect.Height(), iRect.Height())));

    // in full screen, enable blurring on flip/zoom
    iRenderer->EnableBlurOnFlip(ETrue, KDefaultBlurDeviation, 
            KDefaultBlurDeviation);
     
    InitLabelsL(Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0);
    
    InitPopupL(0);
    
    InitButtonsL();
    
    InitScrollBarL(EFalse);

    iSpring->SetConstants(
            KMediaWallFullScreenSpringK, 
            KMediaWallFullScreenSpringDamping, 
            KMediaWallFullScreenSpringMaxVelocity, 
            KPositionSnap, KMinSpringVelocity);    

    }

// -----------------------------------------------------------------------------
// CHgVgMediaWall::CreateMediaWallTBonePortraitL()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWall::InitMediaWallTBonePortraitL()
    {
    
    // set some factors to mediawall fullscreen mode specific values
    iCameraZoomFactor = KMediaWallTBoneCameraZoomFactor;
    iCameraRotationFactor = KMediaWallTBoneCameraRotationFactor;            
    iItemsOnScreen = KMediaWallTBoneItemsOnScreen;
    iSpringVelocityToAnimationFactor = KMediaWallTBoneSpringVelocityToAnimationFactor;
    iItemsToMoveOnFullScreenDrag = KMediaWallTBoneItemsToMoveOnFullScreenDrag;
    iRowCount = KMediaWallTBoneRowCount;
    iOpeningAnimationType = EHgVgOpeningAnimationZoomToFront;
    
    // get front rectange from layout
    TAknLayoutRect frontRect;
    frontRect.LayoutRect( iRect, AknLayoutScalable_Apps::cf0_flow_pane_g1(1) );

    iRenderer = CHgVgMediaWallRenderer::NewL(KMaxCoversVisible, iRect, frontRect.Rect(), 
            KMediaWallTBoneZOffset);
                
    iRenderer->SetFlippedRect(TRect(TPoint(iRect.Center().iX - iRect.Height() / 2,
            iRect.Center().iY - iRect.Height() / 2),
            TSize(iRect.Height(), iRect.Height())));
    
    InitLabelsL(0);
    
    InitPopupL(0);
    
    iSpring->SetConstants(
            KMediaWallTBoneSpringK, 
            KMediaWallTBoneSpringDamping, 
            KMediaWallTBoneSpringMaxVelocity, 
            KPositionSnap, KMinSpringVelocity);
        
    }

void CHgVgMediaWall::InitMediaWallGridLandscapeL()
    {

    TRect frontRect;
    TSize size(120,90);            
    
    // TODO: set this from layout data
    frontRect = TRect(TPoint(iRect.Center().iX - size.iWidth/2, iRect.Center().iY - 45 + 90), 
            size);
                
    iCameraZoomFactor = KMediaWallGridCameraZoomFactor;
    iCameraRotationFactor = KMediaWallGridCameraRotationFactor;            
    iItemsOnScreen = KMediaWallGridItemsOnScreen;
    iSpringVelocityToAnimationFactor = KMediaWallGridSpringVelocityToAnimationFactor;
    iItemsToMoveOnFullScreenDrag = KMediaWallGridItemsToMoveOnFullScreenDrag;
    iRowCount = KMediaWallGridRowCount;
    iOpeningAnimationType = EHgVgOpeningAnimationZoomIn;
    
    iRenderer = CHgVgMediaWallRenderer::NewL((KMaxCoversVisible+1) * KMediaWallGridRowCount, 
            iRect, frontRect, KMediaWallGridZOffset);
    
    iRenderer->SetFlippedRect(iRect);
                                        
    InitButtonsL();
    
    InitScrollBarL(EFalse);
    
    //iRenderer->EnableFlipXY(ETrue);
    
    // TODO: set this from layout data
    TSize lsize(300, 70);
    iLetterPopup = CHgVgPopup::NewL(TRect(TPoint(iRect.Center().iX - lsize.iWidth / 2, 
            iRect.Center().iY - lsize.iHeight / 2), lsize), 
            &ScreenFont( TCoeFont( KMediaWallGridPopupFontSize, TCoeFont::EPlain )));
    
    iSpring->SetConstants(
            KMediaWallGridSpringK, 
            KMediaWallGridSpringDamping, 
            KMediaWallGridSpringMaxVelocity, 
            KPositionSnap, 
            KMinSpringVelocity);
    }


void CHgVgMediaWall::InitLabelsL(TInt aLayoutVariant)
    {
    TAknTextComponentLayout l0 = AknLayoutScalable_Apps::main_cf0_pane_t1(aLayoutVariant);
    TAknTextComponentLayout l1 = AknLayoutScalable_Apps::main_cf0_pane_t2(aLayoutVariant);
    
    TAknLayoutText t0;
    TAknLayoutText t1;
    
    t0.LayoutText(iRect, l0);
    t1.LayoutText(iRect, l1);            
    
    iAlbumLabel = CHgVgLabel::NewL(t0.TextRect(), 
                    &ScreenFont( TCoeFont( KMediaWallTBoneLabelFontSize, TCoeFont::EBold )) );

    iArtistLabel = CHgVgLabel::NewL(t1.TextRect(), 
            &ScreenFont( TCoeFont( KMediaWallTBoneLabelFontSize, TCoeFont::EBold )) );

    iAlbumLabel->SetLayout(l0, iRect);
    iArtistLabel->SetLayout(l1, iRect);    
    }

void CHgVgMediaWall::InitPopupL(TInt aLayoutVariant)
    {
    TAknLayoutRect popupRect;
    popupRect.LayoutRect( iRect, AknLayoutScalable_Apps::cf0_flow_pane_g2(aLayoutVariant) );
    iLetterPopup = CHgVgPopup::NewL(popupRect.Rect(), 
            &ScreenFont( TCoeFont( KMediaWallTBonePopupFontSize, TCoeFont::EPlain )));

    iLetterPopup->SetLayouts(AknLayoutScalable_Apps::cf0_flow_pane_g2(aLayoutVariant), 
            AknLayoutScalable_Apps::cf0_flow_pane_t1(aLayoutVariant), iRect);    
    }



// End of File
