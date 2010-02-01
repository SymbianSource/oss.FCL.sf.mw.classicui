/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikclbd.h>
#include <aknlists.h>
#include <AknsEffectAnim.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <AknMarqueeControl.h>
#include <eikpanic.h>
#include <eikcoctlpanic.h>
#include <gulicon.h>
#include <AknBidiTextUtils.h>
#include <skinlayout.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknphysics.h>


#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST

#include <touchfeedback.h>

#include "akntrace.h"

const TInt KColumnListBoxGranularity=4;
const TInt KNoActualColumnFont=-1;
const TInt KMaxColumn = 6;

// colored tick marks support
const TInt KColorIconFlag = -1;
const TInt KColorIconIdx  =  0;


/**
* About animation usage:
* All animation usage is implemented in this class. Animation is eye candy and
* low priority when it comes to resources -> on resource failures animation
* fails fast to release resources for more critical functionality. Also, no
* attempt to (re)construct failed animation is made.
*
* User inactivity is not being observed. Only one animation is used. Extension
* is CActive to make it possible to postpone animation deletion on animation
* failure.
*/
NONSHARABLE_CLASS(CColumnListBoxDataExtension) :
    public CActive,
    public MAknPictographAnimatorCallBack,
    public MCoeForegroundObserver,
    public MAknsEffectAnimObserver,
    public MListBoxItemChangeObserver
    {
public:
    enum TFlag
        {
        // Set if current item background should be copied to animation as
        // input layer.
        EFlagUpdateBg      = 0,

        // Set if animation has been resized at least once
        EFlagHasLayers     = 1,

        // Set if foreground has been gained.
        EFlagHasForeground = 2
        };
    enum TSubCellType
        {
        EEikSLGraphic,
        EEikSLText,
        EEikSLNumeric
        };

public:
    CColumnListBoxDataExtension();
    void ConstructL( CColumnListBoxData* aListBoxData,
                     const TAknsItemID& aAnimationIID );
    ~CColumnListBoxDataExtension();
    static TInt RedrawEvent(TAny* aControl);
    TBool IsMarqueeOn();
    struct SRowAndColumn
        {
        TInt iIndex; // 24 bits for row and 8 bits for column
        const CFont* iFont;
        };
    SRowAndColumn& At(TInt aArrayIndex);
    const SRowAndColumn& At(TInt aArrayIndex) const;
    void AddRowAndColumnL(TInt aRow,TInt aColumn);
    TInt FindRowAndColumnIndex(TInt& aArrayIndex,TInt aRow,TInt aColumn) const;
    void FindRowAndColumnIndexOrAddL(TInt& aArrayIndex,TInt aRow,TInt aColumn);

    inline void NoAnimIfError( TInt aError );
    void TryCreateAnimation();
    TBool SyncAnim( const TSize& aSize );
    TBool SyncAndDrawAnim( CBitmapContext& aGc, const TRect& aRect );
    MAknsControlContext* SkinBackgroundContext() const;
    void DeleteAnim();
    void FocusGained();
    void FocusLost();
    void SkinChanged();
    void SetControl( CCoeControl* aControl );

    // Implementation of MCoeForegroundObserver
    void HandleGainingForeground();
    void HandleLosingForeground();

    // Implementation of MAknsEffectAnimObserver
    void AnimFrameReady( TInt aError, TInt );

    // Implementation of MListBoxItemChangeObserver
    void ListBoxItemsChanged(CEikListBox* aListBox);

    // Overloads CActive::DoCancel
    void DoCancel();
    // Overloads CActive::RunL
    void RunL();

    void Play();
    void CreateColorBitmapsL();
    
    TBool DrawPressedDownEffectL( MAknsSkinInstance* aInstance, 
                                 CWindowGc& aGc, 
                                 const TRect& aOutRect, 
                                 const TRect& aInnerRect ) const;
public: //for handling column alignment
    struct TColumnExt
        {
        TInt    iColumn; // Must be first entry 
        TBool   iLayoutAlign;//is layout alignment or Set by client 
        };    
    TInt  AddColumnExtL(TInt aColumn);        
    void  FindColumnExtIndexOrAddL(TInt& aArrayIndex,TInt aColumn);  
    void  SetColumnLayoutAlignmentL(TInt aColumn);  
            
          
    TBool FindColumnExtIndex(TInt& aArrayIndex,TInt aColumn) const; 
    TBool ColumnLayoutAlignment(TInt aColumn) const;  
    
public: // new list layout system
    struct SRowAndSubCell
        {
        TInt iIndex; // 24 bits for row and 8 bits for subcell
        const CFont* iFont;
        };
    struct SSLSubCell
        {
        TInt iSubCell; // Must be first entry
        TAknTextLineLayout iTextLayout;
        TAknWindowLineLayout iGraphicLayout;
        TInt iSubCellType;
        TInt iConditionValue; // used with conditional layouts for not always drawn subcells
        };

    SSLSubCell& AtSL(TInt aArrayIndex);
    const SSLSubCell& AtSL(TInt aArrayIndex) const;
    void AddSLSubCellL(TInt aSubCell);
    TInt FindSLSubCellIndex(TInt& aArrayIndex, TInt aSubCell) const;
    void FindSLSubCellIndexOrAddL(TInt& aArrayIndex, TInt aSubCell);
    void ResetSLSubCellArray();

    
private: // New internal methods
    TBool DrawHighlightBackground( CFbsBitGc& aGc );
    void PostDeleteAnimation();
    void CreateAnimationL();
    void DoResizeL( const TSize& aHighlightSize, TBool aAboutToStart );

private: // from MAknPictographAnimatorCallback
    void DrawPictographArea();

public:
    CArrayPtr<CGulIcon>* iIconArray;
    CCoeControl *iControl; // not owned
    CAknsListBoxBackgroundControlContext* iSkinControlContext;
    const TAknsItemID *iSkinHighlightFrameId;
    const TAknsItemID *iSkinHighlightFrameCenterId;
    TBool iSkinEnabled;
    CAknPictographInterface* iPictoInterface;
    CAknMarqueeControl*   iMarquee;
    CAknMarqueeControl*   i2ndLineMarquee;
    TInt                  iCurrentItem; // Marquee:
    TInt iCurrentRow; // Current list row being drawn.
    CArrayFix<SRowAndColumn>* iRowAndColumnArray;
    TSize iSubCellIconSize[6]; // Store icon sizes for each column
    TAknSeparatorLinePosition iSeparatorLinePosition;
    CAknsEffectAnim* iAnimation;
    /**
    * Stored flags are explained in enumeration TFlags.
    */
    TBitFlags32 iAnimFlags;
    CColumnListBoxData* iListBoxData;
    TRgb iHighlightedTextColor;
    TRgb iTextColor;

    TAknsItemID iAnimIID;
    MColumnListBoxAnimBackgroundDrawer* iHighlightBgDrawer;
    TSize iAnimSize; // TODO Deprecating old style anim API and removing this
    TBool       iUnderlineFlagSet;  // underlining support for more than
    TBitFlags32 iUnderlineFlags;    // one text subcell
    TBool iUseLayoutData;
    TBool iStretchingEnabled;
    CArrayFix<SRowAndSubCell>* iRowAndSubCellArray;
    CArrayFix<SSLSubCell>* iSLSubCellArray;
    TBool iSubCellsMightIntersect;
    TRect iParent;  // parent for size calculations

    // colorskin highlight icons
    CFbsBitmap* iColorBmp;
    CFbsBitmap* iHiliBmp;
    TRgb        iIconColor;
    TRgb        iHiliIconColor;
    TInt        iConditionalCells;

    // which columns of highlighted item have clipped text ?
    TUint32     iClippedColumns;
    
    TBool iKineticScrolling;

   
    
    CArrayFix<TColumnExt>* iColumnExtArray; //for column alignment
    TRect iMarginRect;
    };

/**
* High priority is well argumented because running the active object will
* result in animation deletion -> results in freeing resources.
*/
CColumnListBoxDataExtension::CColumnListBoxDataExtension():
    CActive( EPriorityHigh )
    {}

void CColumnListBoxDataExtension::ConstructL(
    CColumnListBoxData* aListBoxData,
    const TAknsItemID& aAnimationIID )
    {
    _AKNTRACE_FUNC_ENTER;

    ASSERT( aListBoxData );
    iListBoxData = aListBoxData;
    iRowAndColumnArray=new(ELeave) CArrayFixFlat<SRowAndColumn>(4);

    iSeparatorLinePosition = ENoLine;
    
    iAnimIID = aAnimationIID;
    CActiveScheduler::Add( this );
    TryCreateAnimation(); // Animations are created by default

    // try to set ESS text colors here so that they will be set at least somewhere...
    iTextColor = NULL; // just in case
    iHighlightedTextColor = NULL; // just in case
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;

    // set ESS text color
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG6 );
    if ( !error )
        {
        iTextColor = color;
        }

    // set ESS highlighted text color
    error = AknsUtils::GetCachedColor( skin,
                                       color,
                                       KAknsIIDQsnTextColors,
                                       EAknsCIQsnTextColorsCG10 );
    if ( !error )
        {
        iHighlightedTextColor = color;
        }

    iRowAndSubCellArray=new(ELeave) CArrayFixFlat<SRowAndSubCell>(4);

    iSLSubCellArray=new(ELeave) CArrayFixFlat<SSLSubCell>(4);
    
    iColumnExtArray = new(ELeave) CArrayFixFlat<TColumnExt>(KColumnListBoxGranularity);

#ifdef RD_LIST_STRETCH
    // check list stretching from cenrep
    CRepository* cenRep = CRepository::NewL( KCRUidAvkon );
    cenRep->Get( KAknAutomaticListStretching, iStretchingEnabled );
    delete cenRep;
#endif // RD_LIST_STRETCH

    
    iKineticScrolling = CAknPhysics::FeatureEnabled();
    _AKNTRACE_FUNC_EXIT;
    }

CColumnListBoxDataExtension::~CColumnListBoxDataExtension()
    {

    Cancel();

    // Stop receiving foreground events
    CCoeEnv* env = CCoeEnv::Static();
    env->RemoveForegroundObserver( *this );

    delete iRowAndColumnArray;
    iRowAndColumnArray = NULL;
    delete iSkinControlContext;
    delete iPictoInterface;
    delete iMarquee;
    delete i2ndLineMarquee;
    delete iAnimation;
    delete iRowAndSubCellArray;
    delete iSLSubCellArray;
    delete iColorBmp;
    delete iHiliBmp;
    delete  iColumnExtArray;
    }

MAknsControlContext* CColumnListBoxDataExtension::SkinBackgroundContext() const
    {
    if ( iSkinEnabled )
        {
        return iSkinControlContext;
        }
        
    return NULL;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::NoAnimIfError
// -----------------------------------------------------------------------------
//
inline void CColumnListBoxDataExtension::NoAnimIfError( TInt aError )
    {
    if( KErrNone != aError )
        {
        DeleteAnim();
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::TryCreateAnimation
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::TryCreateAnimation()
    {

    if( !iControl )
        {
        return;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST  
    CEikListBox* list = static_cast<CEikListBox*>( iControl );
    CListBoxView* view = list->View();
    if ( !view || !view->ItemDrawer() )
        {
        return;
        }
    CWindowGc* gc = view->ItemDrawer()->Gc();
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( gc );
    if ( transApi && transApi->VerifyKml() == KErrNone )
        {
        return;
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST      

    // Ideally we should not create animation if the list has zero items.
    // Unfortunately, this will cause problems elsewhere as setting item text
    // array to list requires not calling HandleItemAddition (or similar
    // method) -> in some situations animation would not be created at all as
    // we don't receive item change event. Fortunately, creating animation to
    // empty list doesn't carry much overhead as layer creation is delayed to
    // first render.

    if( !iAnimation )
        {
        // This must be the first call because animation does not exist.
        // Animation layers are created when the animation is rendered for the
        // first time.
        TRAPD( err, CreateAnimationL() );
        NoAnimIfError( err );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::SyncAnim
// -----------------------------------------------------------------------------
//
TBool CColumnListBoxDataExtension::SyncAnim( const TSize& aSize )
    {

    if( !iAnimation || aSize.iWidth <= 0 || aSize.iHeight <= 0 )
        {
        return EFalse;
        }

    if( iAnimation->Size() != aSize || iAnimation->NeedsInputLayer() )
        {
        // Resizing will update animation background
        iAnimFlags.Clear( EFlagUpdateBg );

        // Animation exists but its size is out of sync or input layers have
        // been released
        TRAPD( err, DoResizeL( aSize, iAnimFlags.IsSet( EFlagHasForeground ) ) );

        if( err )
            {
            DeleteAnim();
            return EFalse;
            }
        iAnimFlags.Set( EFlagHasLayers );
        }

    // Highlight animation background needs update (current item has changed)
    if( iAnimFlags.IsSet( EFlagUpdateBg ) )
        {
        iAnimFlags.Clear( EFlagUpdateBg );

        if( iAnimation->InputRgbGc() )
            {
            DrawHighlightBackground( *iAnimation->InputRgbGc() );
            // We need to update the output frame (otherwise the highlight
            // would drawn with the old output before the next new animation
            // frame).
            NoAnimIfError( iAnimation->UpdateOutput() );
            if( !iAnimation )
                {
                return EFalse;
                }
            }
        }

    return ETrue;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::SyncAndDrawAnim
// -----------------------------------------------------------------------------
//
TBool CColumnListBoxDataExtension::SyncAndDrawAnim(
        CBitmapContext& aGc, const TRect& aRect )
    {
    if( iAnimation )
        {
        // When application loses foreground or has not yet gained foreground
        // animation is in stopped state and input layers are not present. It
        // is possible that list is repainted in this situation. Calling
        // SyncAnim will create the non-present layers -> WSERV flush ->
        // flicker. To prevent flickering we just render the existing frame.
        // This can lead to incorrect draw if the current item index is changed
        // when the app has no foreground (very unlikely). If EFlagHasLayers is
        // not set we need to do SyncAnim because it is the first call to draw
        // (and flicker is not an issue).
        if( EAknsAnimStateStopped == iAnimation->State() &&
            !iAnimFlags.IsSet( EFlagHasForeground ) &&
            iAnimFlags.IsSet( EFlagHasLayers )  &&
            !iAnimFlags.IsSet( EFlagUpdateBg ) )
            {
            return iAnimation->Render( aGc, aRect );
            }
        }

    if( SyncAnim( aRect.Size() ) )
        {
        return iAnimation->Render( aGc, aRect );
        }

    return EFalse;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::DeleteAnim
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::DeleteAnim()
    {
    // Stop receiving foreground events
    CCoeEnv* env = CCoeEnv::Static();
    env->RemoveForegroundObserver( *this );

    delete iAnimation;
    iAnimation = NULL;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::FocusGained
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::FocusGained()
    {
    Play();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::FocusLost
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::FocusLost()
    {
    if( iAnimation )
        {
        NoAnimIfError( iAnimation->Pause() );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::SkinChanged
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::SkinChanged()
    {
    DeleteAnim();
    TryCreateAnimation();
    CreateColorBitmapsL();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::SetControl
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::SetControl( CCoeControl* aControl )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if( iControl )
        {
        CEikListBox* list = (CEikListBox*) iControl;
        list->RemoveItemChangeObserver( this );
        }

    iControl = aControl;

    if( iControl )
        {
        CEikListBox* list = (CEikListBox*) iControl;
        TRAP_IGNORE( list->AddItemChangeObserverL(this) );

        if( !iAnimation )
            {
            TryCreateAnimation();
            }

        if( iAnimation )
            {
            Play();
            }
        }
    else
        {
        DeleteAnim();
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::HandleGainingForeground
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::HandleGainingForeground()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    // Most of the time focus focus events happen between foreground events.
    // Unfortunately, there are embedded app related cases where this does not
    // always hold (it is possible to focus in non-foreground application or
    // gain foreground without getting a focus gained). Therefore animations
    // must be started here. This causes potential problem case: foreground
    // events are broadcasted to all animations, if there are multiple lists
    // that have focus the result will be multiple animations running at the
    // same time.
    iAnimFlags.Set( EFlagHasForeground );

    if( iAnimation )
        {
        // Because we are gaining foreground we must restore input layers
        // (which are released when animation stops to reduce memory usage).
        SyncAnim( iAnimation->Size() );
        }

    if( iControl )
        {
        if( iControl->IsFocused() )
            {
            Play();
            }
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::HandleLosingForeground
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::HandleLosingForeground()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    iAnimFlags.Clear( EFlagHasForeground );
    if( iAnimation )
        {
        NoAnimIfError( iAnimation->Stop() );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::AnimFrameReady
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::AnimFrameReady( TInt aError, TInt )
    {
    if( KErrNone != aError )
        {
        // Animation has failed to run -> schedule the animation for
        // deletion to fall back to normal rendering.
        PostDeleteAnimation();
        return;
        }

    // This situation should never happen because we start/stop animation when
    // the extension's control is set.
    if( !iControl )
        return;

    // From now on, we have a valid control pointer
    CEikColumnListBox* list = static_cast<CEikColumnListBox*>( iControl );
    CListBoxView* view = list->View();

    if( !view )
        return;

    // We should not run animation when control is in certain states. When
    // control is in these states we idle the animation until the control state
    // becomes valid again.
    TBool invalid = !iControl->IsVisible() ||
                    iControl->IsDimmed() ||
                    (view->ItemDrawer()->Flags() & CListItemDrawer::EDisableHighlight);

    // Check for idling
    if( iAnimation->IsIdling() )
        {
        if( invalid )
            {
            // We are idling and the control is still invalid -> keep on
            // idling.
            return;
            }
        else
            {
            // Control is in valid state, animation should be continued
            TInt err = iAnimation->Continue();
            if( err )
                PostDeleteAnimation();
            return;
            }
        }
    else if( invalid ) // Not idling and invalid control -> start idling
        {
        iAnimation->SetIdling( KAknsEffectAnimDefaultIdleInterval );
        // If the highlight has been disabled, render once to clear the
        // highlight (not returning in that case).
        if( !(view->ItemDrawer()->Flags() & CListItemDrawer::EDisableHighlight) )
            return;
        }

    // No items, no drawing
    if( list->Model()->NumberOfItems() == 0 )
        {
        return;
        }

    // Column array is not ready yet
    if( iListBoxData->LastColumn() < 0 )
        {
        return;
        }

    // Repaint the highlighted cell only
    view->DrawItem( view->CurrentItemIndex() );
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::ListBoxItemsChanged

// we get here from:
// - CEikListBox::Reset()
// - CEikListBox::HandleItemRemoval{WithoutSelections}L()
// - CEikListBox::HandleItemAdditionL()
// - CEikListBox::FireItemChange()
// In all cases:
// - feedback areas might be invalid
// - application is responsible for redrawing the listbox.
//
// since re-drawing listbox fixes feedback areas, those can be reset here.

// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::ListBoxItemsChanged(
        CEikListBox* aListBox)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    TInt items = aListBox->Model()->NumberOfItems();

    if( iAnimation )
        {
        if( 0 == items )
            {
            DeleteAnim();
            }
        else
            {
            Play();
            }
        }
    else if( !iAnimation )
        {
        // Animation doesn't exist and we have > 0 items
        TryCreateAnimation();
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::DoCancel
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::DoCancel()
    {
    // Required method, but not needed
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::RunL
// Postponed animation deletion is done here.
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::RunL()
    {
    DeleteAnim();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::Play
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::Play()
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

    // Check that application is on foreground because there are cases where
    // focus changes are done after foreground is lost -> potentially leads to
    // multiple running animations.
    if( !iAnimFlags.IsSet( EFlagHasForeground ) )
        {
        return;
        }

    // Animation cannot run if we don't have control (nowhere to draw)
    if( !iControl )
        {
        return;
        }

    // The control must also have the focus
    if( !iControl->IsFocused() )
        {
        return;
        }

    // Don't animate empty list
    CEikColumnListBox* list = static_cast<CEikColumnListBox*>( iControl );
    if( list->Model()->NumberOfItems() == 0 )
        {
        return;
        }

    // All preconditions are met: we have animation, foreground, focus, more
    // than zero items and animation is either paused or stopped. Invisibility,
    // dimming and disabled highlight are handled by idling the animation (see
    // AnimFrameReady).

    if( EAknsAnimStatePaused == iAnimation->State() )
        {
        NoAnimIfError( iAnimation->Continue() );
        }
    else if( EAknsAnimStateStopped == iAnimation->State() )
        {
        NoAnimIfError( iAnimation->Start() );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::DrawHighlightBackground
// -----------------------------------------------------------------------------
//
TBool CColumnListBoxDataExtension::DrawHighlightBackground( CFbsBitGc& aGc )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if( iHighlightBgDrawer ) // Bg drawing is done externally (in derived class)
        {
        return iHighlightBgDrawer->DrawHighlightAnimBackground( aGc );
        }

    // Draw the background under the current highlight. This is simplified
    // drawing, we only grab a piece from the list background bitmap.
    CEikColumnListBox* list =
        static_cast<CEikColumnListBox*>( iControl );
    CListBoxView* view = list->View();
    TRect itemRect;
    TInt index = view->CurrentItemIndex();

    // It is possible that the animation is constructed when the list is
    // empty. In this case draw the first element background (drawing works ok
    // even if the list has no items).
    if( list->Model()->NumberOfItems() == 0 )
        {
        index = 0;
        }

    itemRect.SetRect( view->ItemPos( index ), iAnimation->Size() );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( iControl );

    if( !cc )
        cc = SkinBackgroundContext();

    return AknsDrawUtils::DrawBackground( skin, cc, iControl, aGc, TPoint(0,0),
                                          itemRect, KAknsDrawParamBottomLevelRGBOnly );
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::PostDeleteAnimation
// Schedules the animation for deletion by activating the extension itself.
// Deletion is postponed because in many error/failure occasions the caller has
// been animation and direct deletion is possibly not safe (because function
// stack would return through the deleted object).
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::PostDeleteAnimation()
    {
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::CreateAnimationL
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::CreateAnimationL()
    {

    DeleteAnim();

    // Check if derived class wants to disable highligh animation
    if( KAknsIIDNone == iAnimIID )
        {
        return;
        }

    // Create animation
    CCoeEnv* env = CCoeEnv::Static();
    env->AddForegroundObserverL( *this );

    iAnimation = CAknsEffectAnim::NewL( this );
    TBool ok = iAnimation->ConstructFromSkinL( iAnimIID );

    if( !ok ) // Animation for the ID was not found from the skin
        {
        User::Leave( KErrNotFound );
        }

    // Sync the local foreground flag state. Foreground state is stored locally
    // because calling AppUi::IsForeground causes WSERV flush (shocking) and
    // therefore it cannot be used in draw routines.
    CAknAppUi* aui = static_cast<CAknAppUi*>(CEikonEnv::Static()->AppUi());
    iAnimFlags.Assign( EFlagHasForeground, aui->IsForeground() );

    Play();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxDataExtension::DoResizeL
// -----------------------------------------------------------------------------
//
void CColumnListBoxDataExtension::DoResizeL(
    const TSize& aHighlightSize, TBool aAboutToStart )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    iAnimation->BeginConfigInputLayersL( aHighlightSize, aAboutToStart );

    if( iAnimation->InputRgbGc() )
        {
        DrawHighlightBackground( *iAnimation->InputRgbGc() );
        }

    iAnimation->EndConfigInputLayersL();
    }

void CColumnListBoxDataExtension::DrawPictographArea()
    {
    iControl->DrawNow();
    }

TInt CColumnListBoxDataExtension::RedrawEvent(TAny* aControl)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (!((CCoeControl*)aControl)->IsVisible())
        {
        return EFalse;
        }
    CEikColumnListBox* listBox = 
            (CEikColumnListBox*)aControl;
    
    // HWET-7BDDD4
    CListBoxView* view = listBox->View();
    TInt index = listBox->CurrentItemIndex();
    if ( view->ItemIsVisible( index ) )
        {
        listBox->DrawItem( index );
        }
     return ETrue;
    }

TBool CColumnListBoxDataExtension::IsMarqueeOn()
    {
    TBool isOn = EFalse;
    if (iMarquee)
        isOn = iMarquee->IsMarqueeOn();
    _AKNTRACE( "[%s][%s] isOn = %d",
                            "CColumnListBoxDataExtension", __FUNCTION__, isOn );
    return isOn;
    }
void CColumnListBoxDataExtension::AddSLSubCellL(TInt aSubCell)
    {
    SSLSubCell subcell;
    subcell.iSubCell = aSubCell;
    subcell.iTextLayout = NULL;
    subcell.iGraphicLayout = NULL;
    subcell.iSubCellType = 0;
    subcell.iConditionValue = -1;

    TKeyArrayFix key(0,ECmpTInt32);
    iSLSubCellArray->InsertIsqL(subcell,key);
    }

void 
CColumnListBoxDataExtension::AddRowAndColumnL(TInt aRow,TInt aColumn)
    {
    SRowAndColumn column;
    column.iIndex = (aRow << 8) | (aColumn & 0xff);
    TKeyArrayFix key(0,ECmpTInt32);
    iRowAndColumnArray->InsertIsqL(column,key);
    }


CColumnListBoxDataExtension::SRowAndColumn& 
CColumnListBoxDataExtension::At(TInt aArrayIndex)
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iRowAndColumnArray->Count(),Panic(EEikPanicOutOfRange));
    return(iRowAndColumnArray->At(aArrayIndex));
    }

const CColumnListBoxDataExtension::SRowAndColumn& 
CColumnListBoxDataExtension::At(TInt aArrayIndex) const
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iRowAndColumnArray->Count(),Panic(EEikPanicOutOfRange));
    return(iRowAndColumnArray->At(aArrayIndex));
    }

TInt CColumnListBoxDataExtension::FindRowAndColumnIndex(TInt& aArrayIndex,
                                                                TInt aRow,
                                                                TInt aColumn) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (iRowAndColumnArray->Count()==0)
        return(KErrNotFound);
    TKeyArrayFix key(0,ECmpTInt32);
    SRowAndColumn rowAndColumn;
    rowAndColumn.iIndex = (aRow << 8) | (aColumn & 0xff);
    return(iRowAndColumnArray->FindIsq(rowAndColumn,key,aArrayIndex));
    }

void CColumnListBoxDataExtension::FindRowAndColumnIndexOrAddL(TInt& aArrayIndex,
                                                                      TInt aRow,
                                                                      TInt aColumn)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (FindRowAndColumnIndex(aArrayIndex,aRow,aColumn)!=0) //==KErrNotFound)
        {
        AddRowAndColumnL(aRow,aColumn);
        FindRowAndColumnIndex(aArrayIndex,aRow,aColumn);
        }
    }
    
/////////////handling TColumnExt,start

TInt CColumnListBoxDataExtension::AddColumnExtL(TInt aColumn)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    TColumnExt column;
    column.iColumn=aColumn;
    column.iLayoutAlign = ETrue;
    TKeyArrayFix key(0,ECmpTInt);
    return iColumnExtArray->InsertIsqL(column,key);
    }
void CColumnListBoxDataExtension::FindColumnExtIndexOrAddL(TInt& aArrayIndex,TInt aColumn)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (!FindColumnExtIndex(aArrayIndex,aColumn))
        {
        aArrayIndex = AddColumnExtL(aColumn);
        
        }
    }
    
void CColumnListBoxDataExtension::SetColumnLayoutAlignmentL(TInt aColumn)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    TInt index;
    FindColumnExtIndexOrAddL(index,aColumn);  
    iColumnExtArray->At(index).iLayoutAlign = EFalse;
    }
    
    
TBool CColumnListBoxDataExtension::FindColumnExtIndex(TInt& aArrayIndex,TInt aColumn) const
    {
    if (aColumn<0 || iColumnExtArray->Count()==0)
        return EFalse;
    TKeyArrayFix key(0,ECmpTInt);
    TColumnExt column;
    column.iColumn=aColumn;

    // Returns zero if key was found, otherwise non-zero
    TInt ret = iColumnExtArray->FindIsq(column,key,aArrayIndex);
    return (ret == 0);
    }
        
TBool CColumnListBoxDataExtension::ColumnLayoutAlignment(TInt aColumn) const
    {
    TInt index;
    if (!FindColumnExtIndex(index,aColumn))
        return(ETrue);
    return(iColumnExtArray->At(index).iLayoutAlign); 
    }    
    
/////////////handling TColumnExt,end    
CColumnListBoxDataExtension::SSLSubCell& 
CColumnListBoxDataExtension::AtSL(TInt aArrayIndex)
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iSLSubCellArray->Count(),Panic(EEikPanicOutOfRange));
    return(iSLSubCellArray->At(aArrayIndex));
    }

const CColumnListBoxDataExtension::SSLSubCell& 
CColumnListBoxDataExtension::AtSL(TInt aArrayIndex) const
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iSLSubCellArray->Count(),Panic(EEikPanicOutOfRange));
    return(iSLSubCellArray->At(aArrayIndex));
    }

TInt CColumnListBoxDataExtension::FindSLSubCellIndex(TInt& aArrayIndex,
                                                            TInt aSubCell) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (iSLSubCellArray->Count()==0)
        return(KErrNotFound);
    TKeyArrayFix key(0,ECmpTInt32);
    SSLSubCell SLSubCell;
    SLSubCell.iSubCell = aSubCell;
    return(iSLSubCellArray->FindIsq(SLSubCell,key,aArrayIndex));
    }

void CColumnListBoxDataExtension::FindSLSubCellIndexOrAddL(TInt& aArrayIndex,
                                                                  TInt aSubCell)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    if (FindSLSubCellIndex(aArrayIndex, aSubCell)!=0) //==KErrNotFound)
        {
        AddSLSubCellL(aSubCell);
        FindSLSubCellIndex(aArrayIndex,aSubCell);
        }
    }

void CColumnListBoxDataExtension::ResetSLSubCellArray()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    iSLSubCellArray->Reset();
    iRowAndSubCellArray->Reset();
    }

TBool CColumnListBoxDataExtension::DrawPressedDownEffectL( MAknsSkinInstance* aInstance, 
                                                          CWindowGc& aGc,const TRect& aOutRect, 
                                                          const TRect& aInnerRect ) const
    {
    return AknsDrawUtils::DrawFrame( aInstance,
                                     aGc,
                                     aOutRect,
                                     aInnerRect,
                                     KAknsIIDQsnFrListPressed,
                                     KAknsIIDQsnFrListCenterPressed );
    }

EXPORT_C CCoeControl *CColumnListBoxData::Control() const 
    {
    return iExtension->iControl;
    }

EXPORT_C void CColumnListBoxData::SetControl(CCoeControl *aControl)
    {
    iExtension->SetControl( aControl );
    }


EXPORT_C MAknsControlContext* CColumnListBoxData::SkinBackgroundContext() const
    {
    if (iExtension->iSkinEnabled)
        {
        return iExtension->iSkinControlContext;
        }
        
    return NULL;
    }

void CColumnListBoxData::SetSkinBackgroundContext(CAknsListBoxBackgroundControlContext *aContext)
    {
    delete iExtension->iSkinControlContext;
    iExtension->iSkinControlContext = aContext;
    }

void CColumnListBoxData::CreatePictographInterfaceL()
    {
    if ( !iExtension->iPictoInterface )
        {
        iExtension->iPictoInterface = CAknPictographInterface::NewL(
            *iExtension->iControl, *iExtension );
        }
    }

EXPORT_C void CColumnListBoxData::SetSkinHighlightFrame(const TAknsItemID *aFrameId, const TAknsItemID *aFrameCenterId)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    iExtension->iSkinHighlightFrameId = aFrameId;
    iExtension->iSkinHighlightFrameCenterId = aFrameCenterId;
    }

EXPORT_C void CColumnListBoxData::SetSkinEnabledL(TBool aEnabled)
    {
    CListBoxData::SetSkinEnabledL(aEnabled);
    iExtension->iSkinEnabled = aEnabled;
    }

EXPORT_C void CColumnListBoxData::SetSkinStyle(const TAknsItemID *aId, const TRect &aTileRect)
    {
    if (iExtension->iSkinControlContext)
        {
        iExtension->iSkinControlContext->SetTiledBitmap(*aId);
        iExtension->iSkinControlContext->SetTiledRect(aTileRect);
        }
    }

EXPORT_C void CColumnListBoxData::SetListEndSkinStyle(const TAknsItemID *aId, const TRect &aTileRect)
    {
    if (iExtension->iSkinControlContext)
        {
        iExtension->iSkinControlContext->SetBottomBitmap(*aId);
        iExtension->iSkinControlContext->SetBottomRect(aTileRect);
        }
    }

void CColumnListBoxData::CreateMarqueeControlL()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( !iExtension->iMarquee )
        {
        iExtension->iMarquee = CAknMarqueeControl::NewL();
        }
    
     if ( !iExtension->i2ndLineMarquee )
        {
        iExtension->i2ndLineMarquee = CAknMarqueeControl::NewL();
        }
    
    TCallBack callBack(CColumnListBoxDataExtension::RedrawEvent, 
                        iExtension->iControl);
    iExtension->iMarquee->SetRedrawCallBack(callBack);
    iExtension->i2ndLineMarquee->SetRedrawCallBack(callBack);
    }

void CColumnListBoxData::ResetMarquee()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (iExtension->iMarquee)
        {
        iExtension->iMarquee->Reset();
        }
    if (iExtension->i2ndLineMarquee)
        {
        iExtension->i2ndLineMarquee->Reset();
        }
    }

TInt CColumnListBoxData::CurrentMarqueeItemIndex()
    {
    return iExtension->iCurrentItem;
    }

void CColumnListBoxData::SetCurrentMarqueeItemIndex(TInt aIndex)
    {
    iExtension->iCurrentItem = aIndex;
    }

//
// Enables or disables marquee.
//
EXPORT_C void CColumnListBoxData::EnableMarqueeL(TBool aEnable)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    // CreateMarqueeControlL does nothing if marquee already exists,
    // so let's just call it just in case.
    CreateMarqueeControlL();
    iExtension->iMarquee->EnableMarquee(aEnable);
    iExtension->i2ndLineMarquee->EnableMarquee(aEnable);
    }

EXPORT_C void CColumnListBoxData::SetSeparatorLinePosition(TAknSeparatorLinePosition aPosition)
    {
    if (iExtension)
        iExtension->iSeparatorLinePosition = aPosition;
    }
EXPORT_C TAknSeparatorLinePosition CColumnListBoxData::SeparatorLinePosition() const
    {
    if (iExtension)
        return iExtension->iSeparatorLinePosition;
    else
        return ENoLine;
    }
EXPORT_C CAknLayoutData *CColumnListBoxData::LayoutData() const
    {
    return NULL;
    }

EXPORT_C TBool CColumnListBoxData::LayoutInit() const
    {
    return EFalse;
    }

EXPORT_C void CColumnListBoxData::SetLayoutInit(TBool /*aValue*/) const
    {
    }


//
//    Class CColumnListBoxData::TColors
//

/**
 * Constructs and intialises the data colors to blacks and whites.
 */
EXPORT_C CColumnListBoxData::TColors::TColors()
    : iText(KRgbBlack), iBack(KRgbWhite), iHighlightedText(KRgbWhite), iHighlightedBack(KRgbBlack)
    {
    }

//
//    Class CColumnListBoxData
//

EXPORT_C CColumnListBoxData* CColumnListBoxData::NewL()
//
//    Public c'tor
//
    {
    CColumnListBoxData* self=new(ELeave) CColumnListBoxData();
    self->ConstructLD();
    return(self);
    }

EXPORT_C CColumnListBoxData::CColumnListBoxData()
                : CListBoxData()
//
//  Protected c'tor
//
    {
    __DECLARE_NAME(_S("CColumnListBoxData"));
    }

EXPORT_C CColumnListBoxData::~CColumnListBoxData()
//
//    D'tor
//
    {
    delete iColumnArray;
    if (IconArray())
        {
        IconArray()->ResetAndDestroy();
        if (iExtension)
            delete iExtension->iIconArray;
        }
    delete iExtension;
    }

EXPORT_C void CColumnListBoxData::ConstructLD()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TRAPD( err, DoConstructL( KAknsIIDQsnAnimList ) );
    if( err )
        {
        delete(this);
        User::Leave( err );
        }
    }

EXPORT_C void CColumnListBoxData::ConstructLD(
    const TAknsItemID& aAnimationIID )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TRAPD( err, DoConstructL( aAnimationIID ) );
    if( err )
        {
        delete(this);
        User::Leave( err );
        }
    }

void CColumnListBoxData::DoConstructL( const TAknsItemID& aAnimationIID )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    iColumnArray = new(ELeave) CArrayFixFlat<SColumn>(KColumnListBoxGranularity);
    iExtension = new(ELeave) CColumnListBoxDataExtension;

    iExtension->iSkinEnabled = AknsUtils::AvkonSkinEnabled();
    SetupSkinContextL();

    iExtension->ConstructL( this, aAnimationIID );

    CListBoxData::SetSkinBackgroundControlContextL(iExtension->iSkinControlContext);

    // preallocate columns so that we dont need to leave on
    // SizeChanged().
    // AddColumnL(0);
    // AddColumnL(1);
    // AddColumnL(2);
    // AddColumnL(3);
    // AddColumnL(4);
    }

EXPORT_C TInt CColumnListBoxData::LastColumn() const
//
//    The last column defined
//
    {
    TInt count=iColumnArray->Count();
    if (!count)
        return(KErrNotFound);
    return(At(count-1).iColumn);
    }

EXPORT_C TInt CColumnListBoxData::ColumnWidthPixel(TInt aColumn) const
//
//    Return the width for a column
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(0);
    return(At(index).iWidth);
    }

EXPORT_C void CColumnListBoxData::SetColumnWidthPixelL(TInt aColumn,TInt aWidth)
//
//    Set a columns width
//
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iWidth=aWidth;
    if ( iExtension && iExtension->iUseLayoutData )
        {
        iExtension->iUseLayoutData = EFalse;
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
#ifdef RD_UI_TRANSITION_EFFECTS_LIST 
        MAknListBoxTfxInternal* transApi =
             CAknListLoader::TfxApiInternal( view->ItemDrawer()->Gc() );
        if ( transApi )
            {
            transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, TPoint( 0, 0 ) );
            transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin, TPoint( 0, 0 ) );
            }
#endif
        }
    }

EXPORT_C TInt CColumnListBoxData::ColumnHorizontalGap(TInt aColumn) const
//
//  Return the vertical for a column
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(0);
    return(At(index).iVerticalCap);
    }

EXPORT_C void CColumnListBoxData::SetColumnHorizontalGapL(TInt aColumn,TInt aGap)
//
//  Set a columns vertical cap
//
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iVerticalCap=aGap;
    }


EXPORT_C TInt 
CColumnListBoxData::ColumnTextClipGap(TInt aColumnIndex) const
    {
    TInt index;
    if (!FindColumnIndex(index,aColumnIndex))
        return TInt(0);
    return(iColumnArray->At(index).iTextClipGap);
    }

EXPORT_C void 
CColumnListBoxData::SetColumnTextClipGapL(TInt aColumnIndex, TInt aGap)
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumnIndex);
    At(index).iTextClipGap=aGap;
    }

EXPORT_C TInt CColumnListBoxData::ColumnBaselinePos(TInt aColumn) const
//
//  Return the vertical for a column
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(0);
    return(At(index).iBaseline);
    }

EXPORT_C void CColumnListBoxData::SetColumnBaselinePosL(TInt aColumn,TInt aPos)
//
//  Set a columns baseline position
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iBaseline=aPos;
    
    // can not be nicely supported by new drawing system
    // --> revert to Symbian style drawing
    if ( iExtension && iExtension->iUseLayoutData )
        {
        iExtension->iUseLayoutData = EFalse;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        MAknListBoxTfxInternal* transApi =
             CAknListLoader::TfxApiInternal( view->ItemDrawer()->Gc() );
        if ( transApi )
            {
            transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, TPoint( 0, 0 ) );
            transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin, TPoint( 0, 0 ) );
            } 
#endif
        }
    }

EXPORT_C TMargins CColumnListBoxData::ColumnMargins(TInt aColumn) const
//
//  Return the vertical for a column
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        {    
        TMargins m = {0,0,0,0};
        return m;
        }
    return(At(index).iMargins);
    }

EXPORT_C void CColumnListBoxData::SetColumnMarginsL(TInt aColumn,TMargins aMargins)
//
//  Set a columns vertical cap
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iMargins=aMargins;

    // can not be nicely supported by new drawing system
    // --> revert to Symbian style drawing
    if ( iExtension && iExtension->iUseLayoutData )
        {
        iExtension->iUseLayoutData = EFalse;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        MAknListBoxTfxInternal* transApi =
             CAknListLoader::TfxApiInternal( view->ItemDrawer()->Gc() );
        if ( transApi )
            {
            transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, TPoint( 0, 0 ) );
            transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin, TPoint( 0, 0 ) );
            } 
#endif
        }
    }


EXPORT_C TInt CColumnListBoxData::ColumnX(TInt aColumn) const
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        {    
        return 0;

        }
    return(At(index).iX);
    }

EXPORT_C void CColumnListBoxData::SetColumnXL(TInt aColumn,TInt aX) const
    {
    TInt index;
    MUTABLE_CAST(CColumnListBoxData*,this)->FindColumnIndexOrAddL(index,aColumn);
    MUTABLE_CAST(TInt&,At(index).iX)=aX;
    }


EXPORT_C TInt CColumnListBoxData::ColumnEndX(TInt aColumn) const
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        {    
        return 0;
        }
    return(At(index).iEndX);
    }

EXPORT_C void CColumnListBoxData::SetColumnEndXL(TInt aColumn,TInt aEndX) const
    {
    TInt index;
    MUTABLE_CAST(CColumnListBoxData*,this)->FindColumnIndexOrAddL(index,aColumn);
    MUTABLE_CAST(TInt&,At(index).iEndX)=aEndX;
    }

EXPORT_C const CFont* CColumnListBoxData::ColumnFont(TInt aColumn) const
//
//    Return the font for a column
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(NULL);
    return(iColumnArray->At(index).iBaseFont);
    }

EXPORT_C void CColumnListBoxData::SetColumnFontL(TInt aColumn,const CFont* aFont)
//
//    Set a font for a column
//
    {
// This corrects error report KBAA-53GEQ5.
#if NOT_NEEDED_IN_SERIES60
    TInt columns=iColumnArray->Count();
#endif
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    if (!At(index).iBaseFont)
        {
// This corrects error report KBAA-53GEQ5.
#if NOT_NEEDED_IN_SERIES60
        TInt actualFontIndex=0;
        TRAPD(err, actualFontIndex=AddActualFontL(aFont));
        if (err)
            {
            if (columns!=iColumnArray->Count())
                {
                iColumnArray->Delete(index);
                }
            User::Leave(err);
            }
        At(index).iActualFontIndex=actualFontIndex;
#endif
        // TPFIX(moved down) At(index).iBaseFont=aFont;
        }
    At(index).iBaseFont=aFont;
    }

EXPORT_C CGraphicsContext::TTextAlign CColumnListBoxData::ColumnAlignment(TInt aColumn) const
//
//    Return a columns alignment
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(CGraphicsContext::ELeft);
    return(iColumnArray->At(index).iAlign);
    }

EXPORT_C void CColumnListBoxData::SetColumnAlignmentL(TInt aColumn,CGraphicsContext::TTextAlign aAlign)
//
//    Set a columns alignment
//
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iAlign=aAlign;
    iExtension->SetColumnLayoutAlignmentL( aColumn);  
    }


EXPORT_C CGraphicsContext::TPenStyle CColumnListBoxData::ColumnSeparatorStyle(TInt aColumn) const
//
//    Return a columns separator style
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(CGraphicsContext::ENullPen);
    return(iColumnArray->At(index).iSeparator);
    }

EXPORT_C void CColumnListBoxData::SetColumnSeparatorStyleL(TInt aColumn,CGraphicsContext::TPenStyle aSeparator)
//
//    Set a columns separator style
//
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iSeparator=aSeparator;
    }


EXPORT_C TBool CColumnListBoxData::ColumnIsGraphics(TInt aColumn) const
//
//    Return true if the column contains graphics
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(EFalse);
    return(iColumnArray->At(index).iGraphics);
    }

EXPORT_C void CColumnListBoxData::SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics)
//
//    Sets whether a column shows graphics
//
    {
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iGraphics=aIsGraphics;
    }

EXPORT_C TBool CColumnListBoxData::ColumnIsNumber(TInt aColumn) const
//
//    Return true if the column contains graphics
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(EFalse);
    return(iColumnArray->At(index).iNumberColumn);
    }

EXPORT_C void CColumnListBoxData::SetNumberColumnL(TInt aColumn,TBool aIsNumber)
//
//    Sets whether a column shows graphics
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iNumberColumn=aIsNumber;
    }


EXPORT_C TBool CColumnListBoxData::ColumnIsOptional(TInt aColumn) const
//
//    Return true if the column contains graphics
//
    {
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(EFalse);
    return(iColumnArray->At(index).iOptional);
    }

EXPORT_C void CColumnListBoxData::SetOptionalColumnL(TInt aColumn,TBool aIsOptional)
//
//    Sets whether a column shows graphics
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TInt index;
    FindColumnIndexOrAddL(index,aColumn);
    At(index).iOptional=aIsOptional;
    }

EXPORT_C CArrayPtr<CGulIcon>* CColumnListBoxData::IconArray() const
//
//    Return the list of icons
//
    {
    if (iExtension)
        return iExtension->iIconArray;
    else
        return 0;
    }

EXPORT_C void CColumnListBoxData::SetIconArray(CArrayPtr<CGulIcon>* aArray)
//
//    Passes ownership of the icon list aArray (assumes any previous list has been deleted by the caller)
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (iExtension)
        iExtension->iIconArray=aArray;
    else
        {
        aArray->ResetAndDestroy();
        delete aArray;
        }    
    }

EXPORT_C CFont* CColumnListBoxData::Font(const TListItemProperties& /*aItemProperties*/, TInt aColumn) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    return const_cast<CFont*>(this->ColumnFont(aColumn));
#if NOT_NEEDED_IN_SERIES60
    TInt index;
    if (!FindColumnIndex(index,aColumn))
        return(NULL);
    TInt actualFontIndex=iColumnArray->At(index).iActualFontIndex;
    if (actualFontIndex==KNoActualColumnFont)
        return(NULL);
    if ((aItemProperties.IsBold()) && (aItemProperties.IsItalics()))
        {
        return iBoldItalicFont.iFonts->At(actualFontIndex);
        }
    else if (aItemProperties.IsBold())
        {
        return iBoldFont.iFonts->At(actualFontIndex);
        }
    else if (aItemProperties.IsItalics())
        {
        return iItalicFont.iFonts->At(actualFontIndex);
        }
    else return iNormalFont.iFonts->At(actualFontIndex);
#endif
    }

void CColumnListBoxData::DrawHighLight( CWindowGc& aGc, const TRect& aRect, TBool aHighlight, MAknsSkinInstance* aSkin ) const
    {
    // SERIES60 Highlight drawing.
    if( aHighlight )
        {
        // same as CFormattedCellListBoxData::DrawDefaultHighlight
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        TBool pressedDown = view->ItemDrawer()->Flags() & CListItemDrawer::EPressedDownState;

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( &aGc );
        if ( transApi )
            {
            transApi->Invalidate(MAknListBoxTfxInternal::EListHighlight ); // This will remove the old bitmap
            transApi->BeginRedraw( MAknListBoxTfxInternal::EListHighlight, aRect );
            transApi->StartDrawing( MAknListBoxTfxInternal::EListHighlight );
            aGc.SetClippingRect( view->ViewRect() );
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST      
        // Try drawing the animated highlight
        TBool highlightDrawn = EFalse;
        if ( iExtension->iAnimation )
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST        
            if ( transApi && transApi->VerifyKml() == KErrNone )
                {
                iExtension->DeleteAnim();
                }
            else
                {
#endif
            TAknLayoutRect topLeft;
            topLeft.LayoutRect(aRect, SkinLayout::List_highlight_skin_placing__general__Line_2());
            
            TAknLayoutRect bottomRight;
            bottomRight.LayoutRect(aRect, SkinLayout::List_highlight_skin_placing__general__Line_5());
            
            TRect outerRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
            
            aGc.SetPenStyle(CGraphicsContext::ENullPen);
            highlightDrawn = iExtension->SyncAndDrawAnim( aGc, outerRect );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST        
                }
#endif
            }
        
        if (!highlightDrawn)
            {
            // Animated highlight was not available, use normal skinned
            // rendering.
            MAknsControlContext *cc = AknsDrawUtils::ControlContext( Control() );
            if (!cc) cc = SkinBackgroundContext();
            if (cc)
                {
                TAknLayoutRect topLeft;
                topLeft.LayoutRect(aRect, SkinLayout::List_highlight_skin_placing__general__Line_2());
                
                TAknLayoutRect bottomRight;
                bottomRight.LayoutRect(aRect, SkinLayout::List_highlight_skin_placing__general__Line_5());
                
                TRect outerRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
                TRect innerRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
                aGc.SetPenStyle(CGraphicsContext::ENullPen);

                
                if ( pressedDown )
                    {
                    highlightDrawn = iExtension->DrawPressedDownEffectL( aSkin, aGc, outerRect, innerRect );
                    //view->ItemDrawer()->ClearFlags( CListItemDrawer::EItemPressedDown );
                    }
                else
                    {
                    highlightDrawn = AknsDrawUtils::DrawFrame( aSkin,
                                                           aGc,
                                                           outerRect,
                                                           innerRect,
                                                           *iExtension->iSkinHighlightFrameId,
                                                           *iExtension->iSkinHighlightFrameCenterId );
                    }
                }
            }
        
        // Both animated highlight and normal highlight drawing have failed.
        if (!highlightDrawn)
            {
            TAknLayoutRect highlightshadow;
            TAknLayoutRect highlight;
            highlightshadow.LayoutRect(aRect, AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_1(aRect));
            highlight.LayoutRect(aRect, AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_2(aRect));
            highlightshadow.DrawRect(aGc);
            highlight.DrawRect(aGc);
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST    
        if ( transApi )
            {
            aGc.CancelClippingRect();
            transApi->StopDrawing();
            transApi->EndRedraw( MAknListBoxTfxInternal::EListHighlight );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
    }

    
void CColumnListBoxData::BitBltColored( CWindowGc&      aGc,
                                        TBool           aHighlight,
                                        const CGulIcon* aIcon,
                                        TInt            aSubcell,
                                        TBool           aColorIcon,
                                        const TRect&    aGraphicRect ) const
    {
    // see also eikfrlbd.cpp ( sigh ).
    CFbsBitmap* bitmap( aIcon->Bitmap() );
    CFbsBitmap* mask( aIcon->Mask() );

    // possibly colorskinnable icon. Check must be after SetSize()
    TBool bw( bitmap->DisplayMode() == EGray2 ); 
    
    // center graphics
    TSize size=bitmap->SizeInPixels();
    TInt yDiff = ( aGraphicRect.Height() - size.iHeight ) / 2;
    TInt xDiff = ( aGraphicRect.Width()  - size.iWidth )  / 2;
    TPoint posInBitmap( 0,0 );

    if (xDiff < 0) // icon's width bigger than subcell's width
        {          // possible, if icon is not a aknicon
        posInBitmap.iX = -xDiff;
        xDiff = 0;
        }
    
    if (yDiff < 0) // icon's height bigger than subcell's height
        {
        posInBitmap.iY = -yDiff;
        yDiff = 0;
        }
    
    TPoint bmpPos( aGraphicRect.iTl + TPoint( xDiff, yDiff ) );
    TRect sourcerect( posInBitmap, aGraphicRect.Size() );

    if ( mask )
        {
        TInt i( 0x01 );
        i = i << aSubcell;
        if ( ((i & iExtension->iConditionalCells) && bw) || aColorIcon  )
            {
            aGc.BitBltMasked( bmpPos,
                              aHighlight ? iExtension->iHiliBmp : iExtension->iColorBmp,
                              TRect(posInBitmap, size), mask, ETrue );
            }
        else
            {
            aGc.BitBltMasked( bmpPos, bitmap, sourcerect, mask, ETrue );
            }
        }
    else
        {
        aGc.BitBlt( bmpPos, bitmap ,sourcerect );
        }
    }

void CColumnListBoxData::DrawSimple( const TListItemProperties& aItemProperties,
                                     CWindowGc& aGc,
                                     const TDesC* aText,
                                     const TRect& aRect,
                                     TBool aHighlight,
                                     const TColors& aColors ) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );    

    TInt lastColumn = Min( LastColumn(), KMaxColumn );
    TInt column=0;
    TPtrC text;
    TPtrC tempText;

    TRgb aTextColor = aHighlight ? aColors.iHighlightedText : aColors.iText;

    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( Control() );
    if (!cc)
        {
        cc = SkinBackgroundContext();
        }

    TAknTextLineLayout textLines[KMaxColumn];
    TBool rectClipped[KMaxColumn];
    
    Mem::FillZ( &rectClipped[0], KMaxColumn * sizeof( TBool ) );
    
    if ( iExtension->iSubCellsMightIntersect )
        {
        CheckIfSubCellsIntersect( &textLines[0], &rectClipped[0], *aText, aRect );
        }

    CEikListBox* listbox = static_cast<CEikListBox*>( iExtension->iControl );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( &aGc );
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if ( !listbox || !listbox->BackgroundDrawingSuppressed() )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        aGc.SetPenStyle(CGraphicsContext::ESolidPen);

        if ( listbox )
            {
            AknsDrawUtils::Background( skin, cc, listbox, aGc, aRect );
            }
        else
            {
            aGc.Clear(aRect);
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST   
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }

    DrawHighLight( aGc, aRect, aHighlight, skin );
    
    // The column draw loop
    column = 0;
    TInt subCellIndex = 0;

    if ( !iExtension ) { return; }
    
#ifdef RD_UI_TRANSITION_EFFECTS_LIST   
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        aGc.SetClippingRect( view->ViewRect() );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    
    for( column = 0; column <= lastColumn; column++ )
        {
        TextUtils::ColumnText( text, column, aText );
        if ( text == KNullDesC ) { continue; }

        if ( iExtension->FindSLSubCellIndex( subCellIndex, column )!=0 ) { continue; }
        
        CGraphicsContext::TTextAlign align=ColumnAlignment(column);
        TBool isLayoutAlignment = iExtension->ColumnLayoutAlignment(column);
        
        if ( iExtension->AtSL(subCellIndex).iSubCellType == CColumnListBoxDataExtension::EEikSLText )
            {
            aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
            
            TRgb textColor( aTextColor );
            
            if (aHighlight)
                {
                textColor = aColors.iHighlightedText;
                aGc.SetBrushColor(aColors.iHighlightedBack);    
                }
            if (AknsUtils::AvkonSkinEnabled())
                {
                if (iExtension->iTextColor != NULL)
                    {
                    textColor = iExtension->iTextColor;
                    }
                
                if (aHighlight && iExtension->iHighlightedTextColor != NULL)
                    {
                    textColor = iExtension->iHighlightedTextColor;
                    }
                }
                
            const CFont* rowAndColFont=RowAndColumnFont(iExtension->iCurrentRow,column);
            const CFont* colFont=Font(aItemProperties, column);
            const CFont* tempFont=(colFont) ? colFont : NULL;
            const CFont* usedFont=(rowAndColFont) ? rowAndColFont : tempFont;
            
            TAknTextLineLayout textLineLayout = NULL;

            if ( rectClipped[column] )
                {
                textLineLayout = textLines[column];
                }
            else
                {
                // check if there are icons affecting this text layout
                TInt gSC = iExtension->AtSL(subCellIndex).iConditionValue; // graphical subcell which might affect this text subcell
                
                if (gSC > -1)
                    {
                    TInt tempIndex;
                    while (gSC > -1) // when gSC == -1, we have found our graphical subcell
                        {
                        if (iExtension->FindSLSubCellIndex(tempIndex,gSC)!=0) break;
                        TextUtils::ColumnText(tempText,gSC, aText);
                        if (tempText != KNullDesC)
                            {
                            textLineLayout = iExtension->AtSL(tempIndex).iTextLayout;
                            break;                      
                            }
                        gSC = iExtension->AtSL(tempIndex).iConditionValue;
                        }
                    }
                    
                if (gSC == -1) // no affecting icons -> use default layout
                    {
                    textLineLayout = iExtension->AtSL(subCellIndex).iTextLayout;
                    }
                }
            
  
            if( !isLayoutAlignment )
                { 
                switch(align) 
                    {
                    case CGraphicsContext::ELeft : 
                        {
                        textLineLayout.iJ = ELayoutAlignLeft;    
                        }
                        break; 
                    case CGraphicsContext::ECenter: 
                        {
                        textLineLayout.iJ = ELayoutAlignCenter;
                        }
                        break; 
                    case CGraphicsContext::ERight:  
                        {
                        textLineLayout.iJ = ELayoutAlignRight;
                        }
                        break; 
                    default:  break;
                    };
                }
            
            TAknLayoutText textLayout;
            textLayout.LayoutText( aRect, textLineLayout, usedFont );
            // *2 == leave some room for marquee
            const TInt maxlen( KMaxColumnDataLength * 2 ); 
            TBuf<maxlen> convBuf = text.Left(maxlen);

            // Note that this potentially modifies the text so its lenght in pixels
            // might increase. Therefore, this should always be done before
            // wrapping/clipping text. In some cases, WordWrapListItem is called
            // before coming here. Is it certain that it is not done for number subcells?

            // Do number conversion if required.
            if ( ColumnIsNumber( column ) )
                {
                AknTextUtils::LanguageSpecificNumberConversion( convBuf );
                }

            // Check whether logical to visual conversion should be done here or not.
            TBool bidiConv = ETrue;  // TODO

//             if (ColumnIsNumber(column))
//                 {
//                 AknTextUtils::LanguageSpecificNumberConversion( convBuf );
//                }

            // marquee & clipping detection
            TBool doesNotFit( aHighlight &&
                              textLayout.Font()->TextWidthInPixels( convBuf ) > textLayout.TextRect().Width() );

            // iClippedColumns was cleared in ::Draw() so no need to
            // clear anything here
            if ( doesNotFit )
                {
                iExtension->iClippedColumns |= ( 1 << column );
                }

            TBool marqueeDisabled(EFalse);
            if (listbox != NULL && 
                listbox->View() != NULL && 
                listbox->View()->ItemDrawer() != NULL)
                {
                marqueeDisabled = listbox->View()->ItemDrawer()->Flags() & CListItemDrawer::EDisableMarquee;
                }
            
            if ( iExtension->IsMarqueeOn() && doesNotFit && !marqueeDisabled )
                {
                iExtension->iMarquee->UseLogicalToVisualConversion( bidiConv );
                
                if ( iExtension->iMarquee->DrawText( aGc, aRect, textLineLayout, convBuf, usedFont, textColor ) )
                    {
                    // all the loops have been executed
                    textLayout.DrawText( aGc, convBuf, bidiConv, textColor );
                    }
                }
            else
                {
                if ( iExtension->iMarquee && marqueeDisabled )
                    {
                    iExtension->iMarquee->Stop();
                    }

                textLayout.DrawText( aGc, convBuf, bidiConv, textColor );
                }
            
            
            if ( iExtension->iPictoInterface )
                {                
                TRect  pictoRect = textLayout.TextRect();
                pictoRect.Normalize();
                if ( convBuf.Length() && bidiConv )
                    {                      
                    TInt maxWidth = pictoRect.Size().iWidth; 
                    TInt charsCanBeDisplayed = textLayout.Font()->TextCount( 
                                                convBuf, maxWidth );  
                    if ( charsCanBeDisplayed < convBuf.Length() )
                        {
                        TInt clipCharWidth = textLayout.Font()->CharWidthInPixels( 
                                                KEllipsis /*aClipChar*/ ); 
                         // Check how many characters fit in given space with truncation char. 
                         charsCanBeDisplayed = textLayout.Font()->TextCount( 
                         convBuf, maxWidth - clipCharWidth );

                        // This is "avkon rule": should not insert ellipsis right after a space.
                        if ( charsCanBeDisplayed > 1 && 
                             convBuf[charsCanBeDisplayed - 1] == ' ' &&
                             convBuf[charsCanBeDisplayed - 2] != ' ' )
                            {
                            charsCanBeDisplayed--;
                            }

                        TInt pictoRectWidth = textLayout.Font()->TextWidthInPixels( 
                        convBuf.Left( charsCanBeDisplayed ) );
                        pictoRect.SetWidth( pictoRectWidth );
                        } 
                    } 

               
                iExtension->iPictoInterface->Interface()->DrawPictographsInText(
                    aGc, *usedFont, convBuf,
                    pictoRect,
                    usedFont->AscentInPixels(),
                    textLayout.Align(), 0 );
                }

            aGc.SetUnderlineStyle(EUnderlineOff); // disable underline after first text.
            }
        else if ( iExtension->AtSL(subCellIndex).iSubCellType == CColumnListBoxDataExtension::EEikSLGraphic ) 
            {
            TLex lex(text);
            TInt index;
            __ASSERT_ALWAYS(lex.Val(index)==KErrNone,Panic(EEikPanicColumnListInvalidBitmapIndex));

            TBool colorIcon( EFalse );
            if ( index == KColorIconFlag )
                {
                if ( iExtension->iColorBmp && iExtension->iHiliBmp )
                    {
                    colorIcon = ETrue;
                    }
                index = KColorIconIdx;
                }

            if ( !IconArray() )
                {
                continue;
                }

            if (aHighlight && (index > 0xffff))
                {
                index = index >> 16; // we have different icon for highlight
                }

             index = index & 0xffff; // mask off possible highlight icon
            __ASSERT_DEBUG((index>=0 && index<IconArray()->Count()),Panic(EEikPanicColumnListInvalidBitmapIndex));
            
            TAknWindowLineLayout graphicLayout = iExtension->AtSL(subCellIndex).iGraphicLayout;
            TAknLayoutRect graphicRect; 
            
            graphicRect.LayoutRect(aRect,graphicLayout);
            TSize graphicSize( graphicRect.Rect().Size() );
            
            if (index>=0 && IconArray())
                {
                CGulIcon* icon=(*IconArray())[index];
                CFbsBitmap* bitmap=icon->Bitmap();
                // Sometimes we get fake bitmap...
                if ( bitmap )
                    {
                    TSize size( bitmap->SizeInPixels() );
                    
                    if (size.iWidth != graphicSize.iWidth &&
                        size.iHeight != graphicSize.iHeight )
                        {
                        AknIconUtils::SetSize( bitmap,
                                               graphicSize,
                                               EAspectRatioPreservedAndUnusedSpaceRemoved );
                        }

                    BitBltColored( aGc, aHighlight, icon, column, colorIcon, graphicRect.Rect() );
                    }
                }
            aGc.SetPenStyle(CGraphicsContext::ESolidPen);
            }
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        aGc.CancelClippingRect();
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    }

EXPORT_C
void CColumnListBoxData::Draw( const TListItemProperties& aItemProperties,
                               CWindowGc& aGc,
                               const TDesC* aText,
                               const TRect& aRect,
                               TBool aHighlight,
                               const TColors& aColors ) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ ); 

    if ( aHighlight )
        {
        iExtension->iClippedColumns = 0;
        }

    if ( UsesScalableLayoutData() )
        {
        DrawSimple( aItemProperties, aGc, aText, aRect, aHighlight, aColors );
        return;
        }
    
    const CFont* font=ColumnFont(0);
    CEikonEnv* eikonEnv=CEikonEnv::Static();
    if (font==NULL)
        {
        font=eikonEnv->NormalFont();
        }

    TInt lastColumn=LastColumn();
    if (lastColumn==KErrNotFound)
        {
        if ( font )
            {
            // use draw text so that dont need to change pen color/style
            aGc.UseFont( font );
            aGc.DrawText(TPtrC(),aRect,0);
            aGc.DiscardFont();
            }
        return;
        }

    TInt extraVerticalSpace=(aRect.Height()-font->HeightInPixels());
    TInt baseLineOffset=extraVerticalSpace/2+font->AscentInPixels();
    TRect textRect( aRect );
    TRect textMRect; // textrect with margins.
    textRect.iBr.iX=aRect.iTl.iX;
    TInt column=0;
    TPtrC text;

    TRgb aTextColor = aHighlight ? aColors.iHighlightedText : aColors.iText;

    // Turned the drawing to multipass algorithm, because optionalcolumns drawing will
    // be too difficult to do without - and this is cleaner solution.
    
    // pass 1, figures out x-coordinates for columns.
    TInt x = aRect.iTl.iX;
    TBool mirror = AknLayoutUtils::LayoutMirrored();
    if (mirror)
        {
        x = aRect.iBr.iX;
        }
    TInt maxx = x;
    while(column <= lastColumn)
        {
        // order of instructions is important here, do not change.
        if (!ColumnIsOptional(column)) 
            {
            TRAP_IGNORE(SetColumnXL(column,maxx));

            if (!mirror)
                x = maxx + ColumnWidthPixel(column);
            else
                x = maxx - ColumnWidthPixel(column);

            maxx = x;
            }
        else
            {
            if (!mirror)
                x -= ColumnWidthPixel(column);
            else
                x += ColumnWidthPixel(column);

            TRAP_IGNORE(SetColumnXL(column,x));
            }
        column++;
        }

    // pass 2, figures out the end x coordinates
    column = 0;
    TInt endx;
    TInt tmpcolumn;
    while(column <= lastColumn)
        {
        if (!mirror)
            endx = ColumnX(column) + ColumnWidthPixel(column);
        else
            endx = ColumnX(column) - ColumnWidthPixel(column);
        
        if (!ColumnIsOptional(column)) 
            {
            tmpcolumn = column+1;
            while(ColumnIsOptional(tmpcolumn))
                {
                TextUtils::ColumnText(text,tmpcolumn,aText);
                if (text!=KNullDesC) endx = ColumnX(tmpcolumn);
                tmpcolumn++;
                }
            }
        if (!mirror) 
            {
            __ASSERT_ALWAYS(ColumnX(column)<endx,Panic(EEikPanicColumnListLayoutError));
            }
        else
            {
            __ASSERT_ALWAYS(ColumnX(column)>endx,Panic(EEikPanicColumnListLayoutError));
            }
        TRAP_IGNORE(SetColumnEndXL(column,endx));
        
        column++;
        }

    // pass 3 drawing

    // SERIES60 Background drawing.
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( Control() );
    if (!cc)
        {
        cc = SkinBackgroundContext();
        }

    // aRect is list item's rect, width of which is smaller than width of the list
    // with a scroll bar. List needs to draw under scroll bar anyway, so we need to
    // modify given rect here.
    TRect r(aRect);
    
    CEikListBox* listbox = static_cast<CEikListBox*>( iExtension->iControl );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST

    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( &aGc );

#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if ( !listbox || !listbox->BackgroundDrawingSuppressed() )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        aGc.SetPenStyle(CGraphicsContext::ESolidPen);

        if ( listbox )
            {
            AknsDrawUtils::Background( skin, cc, listbox, aGc, aRect );
            }
        else
            {
            aGc.Clear(aRect);
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST   
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
    
 // LISTBOX LINES NEED TO BE DRAWN HERE.
    DrawHighLight( aGc, aRect, aHighlight, skin );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        aGc.SetClippingRect( view->ViewRect() );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    // The column draw loop
    column = 0;
    FOREVER
        {
        if (column > lastColumn) break;

        if (!mirror)
            {
            textRect.iTl.iX = ColumnX(column);
            textRect.iBr.iX = ColumnEndX(column);
            }
        else
            {
            textRect.iBr.iX = ColumnX(column);
            textRect.iTl.iX = ColumnEndX(column);
            }

        TextUtils::ColumnText(text,column,aText);

        TBool exit_condition = textRect.iBr.iX==textRect.iTl.iX;
        if (ColumnIsOptional(column) && text == KNullDesC)
            {
            exit_condition = ETrue;
            }

        if (!exit_condition)
            {
            // Margins support.
            TMargins m = ColumnMargins(column);
            textMRect.SetRect(textRect.iTl+TSize(m.iLeft,m.iTop),textRect.Size()-TSize(m.iRight+m.iLeft,m.iBottom+m.iTop));
            // end of margins support.
            
            CGraphicsContext::TTextAlign align=ColumnAlignment(column);

            if (!ColumnIsGraphics(column))
                {

                //if (align == CGraphicsContext::ECenter || align == CGraphicsContext::ERight)
                //    {
                //    textMRect.iTl.iX+=1;
                //    textMRect.iBr.iX+=1;
                //    }
                aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
                aGc.SetPenStyle(CGraphicsContext::ESolidPen);
                aGc.SetPenColor(aTextColor);
                SetUnderlineStyle( aItemProperties, aGc, column );

                if (aHighlight)
                    {
                    aGc.SetPenColor(aColors.iHighlightedText);
                    aGc.SetBrushColor(aColors.iHighlightedBack);    
                    }

                if (AknsUtils::AvkonSkinEnabled() && iExtension)
                    {
                    if (iExtension->iTextColor != NULL)
                        {
                        aGc.SetPenColor(iExtension->iTextColor);
                        }

                    if (aHighlight && iExtension->iHighlightedTextColor != NULL)
                        {
                        aGc.SetPenColor(iExtension->iHighlightedTextColor);
                        }
                    }

                const CFont* rowAndColFont=RowAndColumnFont(iExtension->iCurrentRow,column);
                const CFont* colFont=Font(aItemProperties, column);
                const CFont* tempFont=(colFont) ? colFont : font;
                const CFont* usedFont=(rowAndColFont) ? rowAndColFont : tempFont;

                aGc.UseFont(usedFont);

                // baseline calc needed for each column because of margins.
                baseLineOffset = ColumnBaselinePos(column);
                if (!baseLineOffset)
                    {
                    baseLineOffset = (textMRect.Size().iHeight-usedFont->HeightInPixels())/2 + usedFont->AscentInPixels();
                    }
                baseLineOffset -= m.iTop;

                // SERIES60 LAF
                TBuf<200+KAknBidiExtraSpacePerLine> clipbuf;
                
                TInt clipgap = ColumnTextClipGap(column);
                                   
                TBool clipped = AknBidiTextUtils::ConvertToVisualAndClip(
                    text.Left(200), 
                    clipbuf,
                    *usedFont,
                    textMRect.Size().iWidth, 
                    textMRect.Size().iWidth+clipgap);

                if (clipped)
                    {
                    if (!mirror)
                        {
                        textMRect.iBr.iX+=clipgap;
                        }
                    else
                        {
                        textMRect.iTl.iX-=clipgap;
                        }
                    
                    if ( aHighlight )
                        {
                        iExtension->iClippedColumns |= ( 1 << column );
                        }
                    }

                if (ColumnIsNumber(column))
                    {
                    AknTextUtils::LanguageSpecificNumberConversion(clipbuf);
                    }

                // end of SERIES60 LAF

                CAknMarqueeControl* marquee =
                    column == 1 || column == 3 ? iExtension->iMarquee :
                                                 iExtension->i2ndLineMarquee;
                                                 
                TBool marqueeDisabled =
                    listbox->View()->ItemDrawer()->Flags() & CListItemDrawer::EDisableMarquee;

                if ( iExtension->IsMarqueeOn() && aHighlight && clipped && !marqueeDisabled )
                    {
                    // Bidi conversion has already been done.
                    marquee->UseLogicalToVisualConversion( EFalse );
                    
                    if ( marquee->DrawText( aGc, textMRect, text, baseLineOffset, align, *usedFont ) )
                        {
                        // All the loops have been executed -> the text needs to be truncated.
                        aGc.DrawText( clipbuf, textMRect, baseLineOffset, align, 0 );
                        }
                    }
                else
                    {
                    if ( marquee && marqueeDisabled )
                        {
                        marquee->Stop();
                        }

                    aGc.DrawText( clipbuf, textMRect, baseLineOffset, align, 0 );
                    }

                if ( iExtension->iPictoInterface )
                    {
                    iExtension->iPictoInterface->Interface()->DrawPictographsInText(
                        aGc, *usedFont, clipbuf, textMRect, baseLineOffset, align, 0 );
                    }

                aGc.SetUnderlineStyle(EUnderlineOff); // disable underline after first text.
                }
            else
                {
                aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
                if (aHighlight  /*&&  (LastColumn()==0) */ )
                    {
                    aGc.SetBrushColor(aColors.iHighlightedBack);
                    }

                TLex lex(text);
                TInt index;
                TInt err = lex.Val(index);
                __ASSERT_DEBUG(err==KErrNone,Panic(EEikPanicColumnListInvalidBitmapIndex));
                
                if ( index == KColorIconFlag )
                    {
                    index = KColorIconIdx;
                    }

                if ( !err )
                    {
                    if ( !IconArray() )
                        {
                        ++column;
                        continue;
                        }

                    __ASSERT_DEBUG((index>=0 && index<IconArray()->Count()),Panic(EEikPanicColumnListInvalidBitmapIndex));
                    TRect bmpRect;
                    bmpRect.iTl=textMRect.iTl;
                    if (index>=0 && IconArray())
                        {
                        CGulIcon* icon=(*IconArray())[index];
                        
                        if ( iExtension
                             && iExtension->iSubCellIconSize[column] != TSize(0,0) )
                            {
                            TSize wanted( iExtension->iSubCellIconSize[column] );
                            TSize got( icon->Bitmap()->SizeInPixels() );
                            
                            // correct w or h is enough
                            if ( wanted.iWidth != got.iWidth
                                 && wanted.iHeight != got.iHeight )
                                {
                                AknIconUtils::SetSize( icon->Bitmap(),
                                                       wanted,
                                                       EAspectRatioPreservedAndUnusedSpaceRemoved );
                                }
                            }

                        CFbsBitmap* bitmap=icon->Bitmap();
                        
                        TSize size(bitmap->SizeInPixels());
                        
                        // next two lines are SERIES60 additions
                        if (size.iWidth>textMRect.Size().iWidth) size.iWidth = textMRect.Size().iWidth;
                        if (size.iHeight>textMRect.Size().iHeight) size.iHeight = textMRect.Size().iHeight;
                        
                        TPoint bmpPos(textMRect.iTl); // was aRect, I dunno why
                        bmpPos.iY+=(textMRect.Height()-size.iHeight)>>1; // was aRect too...
                        switch (align)
                            {
                            case ELeft:
                                break;
                            case ECenter:
                                bmpPos.iX+=(textMRect.Width()-size.iWidth)>>1;
                                break;
                            case ERight:
                                bmpPos.iX=textMRect.iBr.iX-size.iWidth;
                                break;
                            }
                        bmpRect.SetRect(bmpPos,size);
                        TPoint posInBitmap;
                        posInBitmap += bitmap->SizeInPixels() - textMRect.Size();
                        posInBitmap.iX >>= 1;
                        posInBitmap.iY >>= 1;
                        if (posInBitmap.iX < 0) posInBitmap.iX = 0;
                        if (posInBitmap.iY < 0) posInBitmap.iY = 0;
                        TRect rect(posInBitmap,textMRect.Size());

                        
                        if (icon->Mask())
                            {
                            aGc.BitBltMasked( bmpPos, bitmap, rect, icon->Mask(), ETrue );
                            }
                        else
                            {
                            aGc.BitBlt(bmpPos, bitmap,rect);
                            }
                        }
                    aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
                    }
                }
            }
        
        ++column;
        }
    
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        aGc.CancelClippingRect();
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    }


void CColumnListBoxData::AddColumnL(TInt aColumn)
//
//    Add a column's worth of data
//
    {
    SColumn column;
    column.iColumn=aColumn;
    column.iWidth=0;
    TMargins m = {0,0,0,0};
    column.iMargins=m;
    column.iBaseFont=NULL;
    column.iActualFontIndex=KNoActualColumnFont;
    column.iGraphics=EFalse;
    column.iNumberColumn = EFalse;
    column.iOptional=EFalse;
    column.iBaseline = 0;
    column.iAlign=CGraphicsContext::ELeft;
    column.iSeparator=CGraphicsContext::ENullPen;
    column.iTextClipGap = 0;
    TKeyArrayFix key(0,ECmpTInt);
    iColumnArray->InsertIsqL(column,key);
    }

CColumnListBoxData::SColumn& CColumnListBoxData::At(TInt aArrayIndex)
//
//    Return a column of data
//
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iColumnArray->Count(),Panic(EEikPanicOutOfRange));
    return(iColumnArray->At(aArrayIndex));
    }

const CColumnListBoxData::SColumn& CColumnListBoxData::At(TInt aArrayIndex) const
//
//    Return a column of data
//
    {
    __ASSERT_DEBUG(aArrayIndex>=0 && aArrayIndex<iColumnArray->Count(),Panic(EEikPanicOutOfRange));
    return(iColumnArray->At(aArrayIndex));
    }

TBool CColumnListBoxData::FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const
//
//    Find a column if it has been set
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ ); 
    if (aColumn<0 || iColumnArray->Count()==0)
        return EFalse;
    TKeyArrayFix key(0,ECmpTInt);
    SColumn column;
    column.iColumn=aColumn;

    // Returns zero if key was found, otherwise non-zero
    TInt ret = iColumnArray->FindIsq(column,key,aArrayIndex);
    return (ret ? EFalse: ETrue);
    }

void CColumnListBoxData::FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn)
//
//    Find a column or add it
//
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (!FindColumnIndex(aArrayIndex,aColumn))
        {
        AddColumnL(aColumn);
        FindColumnIndex(aArrayIndex,aColumn);
        }
    }

TInt CColumnListBoxData::AddActualFontL(const CFont* aBaseFont)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (!iNormalFont.iFonts)
        {
        iNormalFont.iFonts=new (ELeave) CArrayPtrFlat<CFont> (1);
        iBoldFont.iFonts=new (ELeave) CArrayPtrFlat<CFont> (1);
        iItalicFont.iFonts=new (ELeave) CArrayPtrFlat<CFont> (1);
        iBoldItalicFont.iFonts=new (ELeave) CArrayPtrFlat<CFont> (1);
        }

    // Reserves extra space for each font array.
    TInt fontCount=iNormalFont.iFonts->Count()+1;
    iNormalFont.iFonts->SetReserveL(fontCount);
    iBoldFont.iFonts->SetReserveL(fontCount);
    iItalicFont.iFonts->SetReserveL(fontCount);
    iBoldItalicFont.iFonts->SetReserveL(fontCount);

    // Add Fonts.
    TFontStyle style=aBaseFont->FontSpecInTwips().iFontStyle;
    ConstructFontL(aBaseFont, style, iNormalFont);
    ConstructFontL(aBaseFont, style, iBoldFont);
    ConstructFontL(aBaseFont, style, iItalicFont);
    ConstructFontL(aBaseFont, style, iBoldItalicFont);

    return fontCount-1;
    }

EXPORT_C TBool CColumnListBoxData::MakeColumnRect( TInt aColumn, TRect& aRect )
    // Returns given column rect
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TInt lastColumn = LastColumn();
    if ( ( aColumn < 0 ) || ( aColumn > lastColumn ) ) return EFalse;

    TRect colRect(aRect);  // we need to save original item rect
    for ( TInt column=0; column<lastColumn; column++ )
        // loop throuhg columns except last one (scroll bar eats small rect from it)
        {
        TInt colWidth = ColumnWidthPixel( column );
        colRect.iBr.iX = colRect.iTl.iX + colWidth;     // set column rect width
        if ( column == aColumn ) break;              // if the column, quit
        aRect.iTl.iX += colWidth;               // shrink origial rect by column with
        colRect = aRect;                            // set colRect for the LAST column
        }
    aRect = colRect;

    return ETrue;
    }

EXPORT_C void CColumnListBoxData::SetColumnFontForRowL(TInt aRow,
                                                       TInt aColumn,
                                                       const CFont* aFont)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (!iExtension) return;
    TInt index = 0;
    iExtension->FindRowAndColumnIndexOrAddL(index,aRow,aColumn);
    iExtension->At(index).iFont=aFont;
    }

EXPORT_C const CFont* 
CColumnListBoxData::RowAndColumnFont(TInt aRow,TInt aColumn) const
    {
    if (!iExtension) return 0;
    TInt index = 0;
    if (iExtension->FindRowAndColumnIndex(index,aRow,aColumn)!=0)
        return 0;
    return(iExtension->At(index).iFont);
    }

void CColumnListBoxData::SetCurrentItemIndex(TInt aIndex)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if( iExtension->iCurrentRow != aIndex )
        {
        iExtension->iAnimFlags.Set( CColumnListBoxDataExtension::EFlagUpdateBg );
        }
    iExtension->iCurrentRow = aIndex;
    }


// ---------------------------------------------------------------------------
// Wraps the text drawing functinality with & without marquee into one
// function, so that inherited classes can modify their own drawing
// behaviour more easily.
// ---------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::DrawText(
    CWindowGc& aGc,
    const TRect& aTextRect,
    const TDesC& aText,
    const TDesC& aClippedText,
    const TInt aBaselineOffset,
    const CGraphicsContext::TTextAlign aAlign,
    const CFont& aFont,
    const TBool aHighlight,
    const TBool aIsTextClipped ) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    TBool marqueeDisabled =
        static_cast<CEikListBox*>(
            Control() )->View()->ItemDrawer()->Flags() & CListItemDrawer::EDisableMarquee;

    if ( iExtension->IsMarqueeOn() && aHighlight && aIsTextClipped && !marqueeDisabled )
        {
        if ( iExtension->iMarquee->DrawText( aGc, aTextRect, aText, aBaselineOffset, aAlign, aFont ) )
            {
            // All the loops have been executed -> the text needs to be truncated.
            aGc.DrawText( aClippedText, aTextRect, aBaselineOffset, aAlign, 0 );    
            }
        }
    else
        {
        if ( iExtension->iMarquee && marqueeDisabled )
            {
            iExtension->iMarquee->Stop();
            }

        aGc.DrawText( aClippedText, aTextRect, aBaselineOffset, aAlign, 0 );
        }                           
    }


EXPORT_C void CColumnListBoxData::SetMarqueeParams(const TInt aLoops, const TInt aScrollAmount, const TInt aScrollDelay)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( iExtension->iMarquee )
        {
        iExtension->iMarquee->SetLoops( aLoops );
        iExtension->iMarquee->SetSpeedInPixels( aScrollAmount );
        iExtension->iMarquee->SetDelay( aScrollDelay );
        }
    if ( iExtension->i2ndLineMarquee )
        {
        iExtension->i2ndLineMarquee->SetLoops( aLoops );
        iExtension->i2ndLineMarquee->SetSpeedInPixels( aScrollAmount );
        iExtension->i2ndLineMarquee->SetDelay( aScrollDelay );
        }
    }
    
EXPORT_C void CColumnListBoxData::SetMarqueeParams(const TInt aLoops, const TInt aScrollAmount, 
                                                   const TInt aScrollDelay, const TInt aInterval)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( iExtension->iMarquee )
        {
        iExtension->iMarquee->SetInterval( aInterval );
        iExtension->i2ndLineMarquee->SetInterval( aInterval );
        SetMarqueeParams( aLoops, aScrollAmount, aScrollDelay );
        }
    }    


EXPORT_C
void CColumnListBoxData::SetSubCellIconSize(TInt aIndex, TSize aSize)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (iExtension && aIndex < 6 && aIndex >= 0)
        {
        iExtension->iSubCellIconSize[aIndex] = aSize;
        }
    }

TSize CColumnListBoxData::GetSubCellIconSize(TInt aIndex)
    {
    if (iExtension && aIndex < 6 && aIndex >= 0)
        {
        return iExtension->iSubCellIconSize[aIndex];
        }
    return TSize(0,0);
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::HighlightAnim
// -----------------------------------------------------------------------------
//
EXPORT_C const CAknsEffectAnim* CColumnListBoxData::HighlightAnim() const
    {
    if( iExtension )
        return iExtension->iAnimation;
    return NULL;
    }

// -----------------------------------------------------------------------------
// AboutToDrawHighlightAnim
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::AboutToDrawHighlightAnim() const
    {
    if( !iExtension )
        {
        return;
        }
    if( !iExtension->iAnimation || !iExtension->iControl )
        {
        return;
        }

    CEikListBox* list = static_cast<CEikListBox*>( iExtension->iControl );
    CListBoxView* view = list->View();
    if( !view )
        {
        return;
        }

    if( view->CurrentItemIndex() != iExtension->iCurrentRow )
        {
        iExtension->iAnimFlags.Set( CColumnListBoxDataExtension::EFlagUpdateBg );
        iExtension->iCurrentRow = view->CurrentItemIndex();
        }

    iExtension->SyncAnim( iExtension->iAnimSize );
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetHighlightAnimBackgroundDrawer
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetHighlightAnimBackgroundDrawer(
    MColumnListBoxAnimBackgroundDrawer* aDrawer )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if( iExtension )
        {
        iExtension->iHighlightBgDrawer = aDrawer;
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetItemCellSize
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetItemCellSize( const TSize& aSizeInPixels )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if( iExtension )
        {
        if( iExtension->iAnimSize != aSizeInPixels )
            {
            iExtension->Play();
            }
        iExtension->iAnimSize = aSizeInPixels;
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::HasHighlightAnim
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CColumnListBoxData::HasHighlightAnim() const
    {
    if( !iExtension )
        return EFalse;
    if( !iExtension->iAnimation )
        return EFalse;
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::DrawHighlightAnim
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CColumnListBoxData::DrawHighlightAnim(
        CBitmapContext& aGc, const TRect& aRect ) const
    {
    if( !iExtension )
        return EFalse;

    if( !iExtension->iAnimation )
        return EFalse;

    return iExtension->SyncAndDrawAnim( aGc, aRect );
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::FocusGained
// -----------------------------------------------------------------------------
//
void CColumnListBoxData::FocusGained()
    {
    iExtension->FocusGained();
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::FocusLost
// -----------------------------------------------------------------------------
//
void CColumnListBoxData::FocusLost()
    {
    iExtension->FocusLost();
    }

void CColumnListBoxData::HandleResourceChange( TInt aType )
    {
    _AKNTRACE( "[%s][%s] aType = %d", "CColumnListBoxData", __FUNCTION__, aType  );
    // Animation is skin dependent, whenever skin changes animation changes
    // too.
    if( KAknsMessageSkinChange == aType )
        {
        iExtension->SkinChanged();
        }
    else if(aType == KEikDynamicLayoutVariantSwitch)
        {
        // What is under highlight may have changed -> we need to update
        // highlight background to animation.
        iExtension->iAnimFlags.Set( CColumnListBoxDataExtension::EFlagUpdateBg );
        }
    else if( ( aType == KEikMessageUnfadeWindows ) ||
             ( aType == KEikMessageFadeAllWindows ) )
        {
        if( iExtension->iMarquee )
            {
            iExtension->iMarquee->HandleResourceChange( aType );
            }
        if( iExtension->i2ndLineMarquee )
            {
            iExtension->i2ndLineMarquee->HandleResourceChange( aType );
            }
        }
    }

void CColumnListBoxData::SetupSkinContextL()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    __ASSERT_DEBUG( iExtension, Panic( EEikPanicNullPointer ));

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    
    TRect mainPaneRect( mainPane.Size() );
    
    if ( !iExtension->iSkinControlContext )
        {
        iExtension->iSkinControlContext = CAknsListBoxBackgroundControlContext::NewL(
            KAknsIIDQsnBgAreaMainListGene,
            mainPaneRect,
            EFalse,
            KAknsIIDQsnBgColumnA,
            mainPaneRect );

        iExtension->iSkinHighlightFrameId = &KAknsIIDQsnFrList;
        iExtension->iSkinHighlightFrameCenterId = &KAknsIIDQsnFrListCenter;
        }
    else
        {
        iExtension->iSkinControlContext->SetRect( mainPaneRect );
        }
    }

void CColumnListBoxData::SetESSTextColor(TRgb aTextColor)
    {
    if (iExtension)
        iExtension->iTextColor = aTextColor;
    }

void CColumnListBoxData::SetESSHighlightedTextColor(TRgb aHighlightedTextColor)
    {
    if (iExtension)
        iExtension->iHighlightedTextColor = aHighlightedTextColor;
    }

EXPORT_C void CColumnListBoxData::SetColumnUnderlined( TBitFlags32 aUnderlinedColumns )
    {
    if ( iExtension )
        {
        iExtension->iUnderlineFlagSet = ETrue;
        iExtension->iUnderlineFlags   = aUnderlinedColumns;
        }
    }

void CColumnListBoxData::SetUnderlineStyle( TListItemProperties aProperties,
                                            CWindowGc& aGc,
                                            TInt aColumn ) const
    {
    if ( !iExtension )
        {
        return;
        }

    if ( !iExtension->iUnderlineFlagSet )
        {
        // underlining is already either on or off and
        // hardcoded off turning will ensure old style
        // behaviour
        return;
        }
    
    if ( aProperties.IsUnderlined()
         && iExtension->iUnderlineFlagSet
         && iExtension->iUnderlineFlags.IsSet( aColumn ) )
        {
        aGc.SetUnderlineStyle( EUnderlineOn );
        }
    else
        {
        aGc.SetUnderlineStyle( EUnderlineOff );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::ResetSLSubCellArray
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::ResetSLSubCellArray()
    {
    if ( !iExtension )
        {
        return;
        }

    iExtension->iMarginRect = TRect::EUninitialized;
    if ( iExtension && iExtension->iUseLayoutData )
        {
        iExtension->iUseLayoutData = EFalse;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST 
        CListBoxView* view = static_cast<CEikListBox*>( iExtension->iControl )->View();
        MAknListBoxTfxInternal* transApi =
             CAknListLoader::TfxApiInternal( view->ItemDrawer()->Gc() );
        if ( transApi )
            {
            transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, TPoint( 0, 0 ) );
            transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin, TPoint( 0, 0 ) );
            } 
#endif
        }
    iExtension->ResetSLSubCellArray();
    // This function gets called always when size changes, so here is called
    // SetupSkinContextL to update the layout rect of the background skin 
    // context (mainpane rect can change for example if toolbar is hidden.
    TRAP_IGNORE( SetupSkinContextL() );
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetGraphicSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetGraphicSubCellL(TInt aSubCell,
                                                   const TAknWindowLineLayout &aGraphicLayout)       
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (!iExtension) return;
    TInt index = 0;
    iExtension->FindSLSubCellIndexOrAddL(index,aSubCell);
    iExtension->AtSL(index).iTextLayout=NULL;
    iExtension->AtSL(index).iGraphicLayout=aGraphicLayout;
    iExtension->AtSL(index).iSubCellType=CColumnListBoxDataExtension::EEikSLGraphic;
    
    // needed for compatibility
    CEikColumnListBox* list = static_cast<CEikColumnListBox*>( iExtension->iControl );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( list->View()->ItemDrawer()->ItemCellSize(), aGraphicLayout );
    TRect rect( layoutRect.Rect() );
    
    SetSubCellIconSize( aSubCell, rect.Size() );
    SetColumnWidthPixelL( aSubCell, rect.Width() );
    SetGraphicsColumnL( aSubCell, ETrue );
    SetColumnXL( aSubCell, rect.iTl.iX );
    SetColumnEndXL( aSubCell, rect.iBr.iX );
    iExtension->iUseLayoutData=ETrue; // might go to own method...
    if ( iExtension->iMarginRect == TRect::EUninitialized )
        {
        iExtension->iMarginRect = rect;
        }
    else
        {
        iExtension->iMarginRect.BoundingRect( rect );
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi =
        CAknListLoader::TfxApiInternal( list->View()->ItemDrawer()->Gc() );
    if ( transApi )
        {
        transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, iExtension->iMarginRect.iTl );
        TSize size = list->View()->ItemDrawer()->ItemCellSize();
        TPoint br( size.AsPoint() - iExtension->iMarginRect.iBr );
        transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin,
            br );
        }
#endif
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetTextSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetTextSubCellL(TInt aSubCell,
                                                const TAknTextLineLayout &aTextLayout)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if (!iExtension) return;
    TInt index = 0;
    iExtension->FindSLSubCellIndexOrAddL(index,aSubCell);
    iExtension->AtSL(index).iTextLayout=aTextLayout;
    iExtension->AtSL(index).iGraphicLayout=NULL;
    iExtension->AtSL(index).iSubCellType=CColumnListBoxDataExtension::EEikSLText;
    
    // needed for compatibility
    CEikColumnListBox* list = static_cast<CEikColumnListBox*>( iExtension->iControl );
    TAknLayoutText textLayout;
    textLayout.LayoutText( list->View()->ItemDrawer()->ItemCellSize(), aTextLayout );
    TRect rect( textLayout.TextRect() );
    
    SetColumnWidthPixelL( aSubCell, rect.Width() );
    SetColumnFontL( aSubCell, textLayout.Font() );
    SetColumnXL( aSubCell, rect.iTl.iX );
    SetColumnEndXL( aSubCell, rect.iBr.iX );
    SetColumnBaselinePosL( aSubCell, aTextLayout.iB );
    iExtension->iUseLayoutData=ETrue; // might go to own method...
    if ( iExtension->iMarginRect == TRect::EUninitialized )
        {
        iExtension->iMarginRect = rect;
        }
    else
        {
        iExtension->iMarginRect.BoundingRect( rect );
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi =
        CAknListLoader::TfxApiInternal( list->View()->ItemDrawer()->Gc() );
    if ( transApi )
        {
        transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, iExtension->iMarginRect.iTl );
        TSize size = list->View()->ItemDrawer()->ItemCellSize();
        TPoint br( size.AsPoint() - iExtension->iMarginRect.iBr );
        transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin,
            br );
        }
#endif
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetConditionalSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetConditionalSubCellL(TInt aSubCell,
                                                         const TAknTextLineLayout &aTextLayout,
                                                         TInt aAffectedSubCell)  
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    // iConditionValue of affected subcell (=text subcell, which has different layouts)
    // contains index of graphical subcell, which existence should be checked first.
    // This graphical subcell has in iConditionValue index of graphical subcell,
    // which existence should be checked second etc. Each graphical subcell can
    // affect only to 1 text subcell (or none).

    // for compabitility - needed at least for text wrapping
    SetOptionalColumnL( aSubCell, ETrue );
    if (!iExtension) return;

    TInt i = 0x01;
    i = i << aSubCell;
    iExtension->iConditionalCells = iExtension->iConditionalCells | i;

    TInt graphicalIndex = 0;
    if (iExtension->FindSLSubCellIndex(graphicalIndex, aSubCell)!=0) return; // subcell not found
    // conditional layoutline can be only added to graphical subcells
    if (iExtension->AtSL(graphicalIndex).iSubCellType!=CColumnListBoxDataExtension::EEikSLGraphic) return;
    
    TInt textIndex = 0; // index of affected subcell
    if (iExtension->FindSLSubCellIndex(textIndex, aAffectedSubCell)!=0) return; // subcell not found
    // affected subcell can only be text subcell
    if (iExtension->AtSL(textIndex).iSubCellType==CColumnListBoxDataExtension::EEikSLGraphic) return;
    
    TInt gSC = iExtension->AtSL(textIndex).iConditionValue; // text subcell to be added in priority chain

    while (gSC > -1)
        {
        if (iExtension->FindSLSubCellIndex(textIndex, gSC)!=0) return; // subcell not found
        gSC = iExtension->AtSL(textIndex).iConditionValue;
        }
    iExtension->AtSL(textIndex).iConditionValue = aSubCell; // add next subcell to chain
    iExtension->AtSL(graphicalIndex).iTextLayout=aTextLayout;
    iExtension->CreateColorBitmapsL();

    CEikColumnListBox* list = static_cast<CEikColumnListBox*>( iExtension->iControl );
    TAknLayoutText textLayout;
    textLayout.LayoutText( list->View()->ItemDrawer()->ItemCellSize(), aTextLayout );

    if ( iExtension->iMarginRect == TRect::EUninitialized )
        {
        iExtension->iMarginRect = textLayout.TextRect();
        }
    else
        {
        iExtension->iMarginRect.BoundingRect( textLayout.TextRect() );
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi =
        CAknListLoader::TfxApiInternal( list->View()->ItemDrawer()->Gc() );
    if ( transApi )
        {
        transApi->SetPosition( MAknListBoxTfxInternal::EListTLMargin, iExtension->iMarginRect.iTl );
        TSize size = list->View()->ItemDrawer()->ItemCellSize();
        TPoint br( size.AsPoint() - iExtension->iMarginRect.iBr );
        transApi->SetPosition( MAknListBoxTfxInternal::EListBRMargin,
            br );
        }
#endif
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SetStretchableGraphicSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetStretchableGraphicSubCellL(
    TInt aSubCell, 
    const TAknWindowComponentLayout& aNormalLayout, 
    const TAknWindowComponentLayout& aStretchedLayout )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         StretchingEnabled() )
        {
        SetGraphicSubCellL( aSubCell, aStretchedLayout.LayoutLine() );
        }
    else
        {
        SetGraphicSubCellL( aSubCell, aNormalLayout.LayoutLine() );
        }
    }
    
// -----------------------------------------------------------------------------
// CColumnListBoxData::SetStretchableTextSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetStretchableTextSubCellL(
    TInt aSubCell, 
    const TAknTextComponentLayout& aNormalLayout, 
    const TAknTextComponentLayout& aStretchedLayout )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         StretchingEnabled() )
        {
        SetTextSubCellL( aSubCell, aStretchedLayout.LayoutLine() );
        }
    else
        {
        SetTextSubCellL( aSubCell, aNormalLayout.LayoutLine() );
        }
    }
    
// -----------------------------------------------------------------------------
// CColumnListBoxData::SetStretchableConditionalSubCellL
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SetStretchableConditionalSubCellL(
    TInt aSubCell,
    const TAknTextComponentLayout& aNormalLayout,
    const TAknTextComponentLayout& aStretchedLayout,
    TInt aNormalSubCell,
    TInt aStretchedSubCell )
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         StretchingEnabled() )
        {
        SetConditionalSubCellL( aSubCell, aStretchedLayout.LayoutLine(), aStretchedSubCell );
        }
    else
        {
        SetConditionalSubCellL( aSubCell, aNormalLayout.LayoutLine(), aNormalSubCell );
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::UsesScalableLayoutData
// -----------------------------------------------------------------------------
//
TBool CColumnListBoxData::UsesScalableLayoutData() const
    {
    if (iExtension)
        return iExtension->iUseLayoutData;

    return EFalse;
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::EnableStretching
// -----------------------------------------------------------------------------
//
void CColumnListBoxData::EnableStretching( const TBool aEnabled )
    {
    if ( !iExtension )
        {
        return;
        }
        
    iExtension->iStretchingEnabled = aEnabled;        
    }

#ifdef RD_LIST_STRETCH
// -----------------------------------------------------------------------------
// CColumnListBoxData::StretchingEnabled
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CColumnListBoxData::StretchingEnabled() const
    {
    if ( !iExtension )
        {
        return EFalse;
        }
        
    return iExtension->iStretchingEnabled;        
    }

#else
// -----------------------------------------------------------------------------
// CColumnListBoxData::StretchingEnabled
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CColumnListBoxData::StretchingEnabled() const
    {
    return EFalse;
    }

#endif // RD_LIST_STRETCH

// -----------------------------------------------------------------------------
// CColumnListBoxData::CheckIfSubCellsIntersect
// -----------------------------------------------------------------------------
//
void CColumnListBoxData::CheckIfSubCellsIntersect( 
    TAknTextLineLayout* aLayouts, 
    TBool* aResults, 
    const TDesC& aText, 
    const TRect& aItemRect ) const
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxData", __FUNCTION__, __LINE__ );

    TInt column = 0;
    TInt column2;
    TInt subCellIndex;
    TInt subCellIndex2;
    TInt lastColumn = Min( LastColumn(), KMaxColumn );
    TPtrC text;
    TBool isEmpty[KMaxColumn];

    // cache the empty text states
    while ( ETrue )
        {
        if ( column > lastColumn )
            {
            break;
            }

        TextUtils::ColumnText( text, column, &aText );

        if ( text == KNullDesC || ColumnIsOptional( column ) )
            {
            isEmpty[column] = ETrue;
            }
        else
            {
            isEmpty[column] = EFalse;
            }

        ++column;
        }

    column = 0;

    while ( ETrue )
        {
        if ( column > lastColumn )
            {
            break;
            }

        if ( iExtension->FindSLSubCellIndex( subCellIndex, column ) != 0 ) 
            {
            break;
            }
        
        if ( isEmpty[column] )
            {
            ++column;
            continue;
            }
        
        TRect bRect( ColumnX( column ), 0, ColumnEndX( column ), 10 );
        
        for ( column2 = column + 1; column2 <= lastColumn; column2++ )
            {
            if ( isEmpty[column2] )
                {
                continue;
                }

            if ( iExtension->FindSLSubCellIndex( subCellIndex2, column2 ) != 0 ) 
                {
                break;
                }

            TRect bRect2( ColumnX( column2 ), 0, ColumnEndX( column2 ), 10 );

            if ( bRect.Intersects( bRect2 ) ) 
                {
                aResults[column] = ETrue;

                if ( !AknLayoutUtils::LayoutMirrored() )
                    {
                    bRect.iBr.iX = bRect2.iTl.iX;
                    }
                else
                    {
                    bRect.iTl.iX = bRect2.iBr.iX;
                    }
                }
            }
            
        if ( aResults[column] )
            {
            if ( iExtension->AtSL( subCellIndex ).iSubCellType == CColumnListBoxDataExtension::EEikSLText )
                {
                TAknTextLineLayout textLine = iExtension->AtSL( subCellIndex ).iTextLayout;
                
                textLine.iW = bRect.Width();

                if ( !AknLayoutUtils::LayoutMirrored() )
                    {
                    textLine.ir = aItemRect.iBr.iX - bRect.iBr.iX;
                    }
                else
                    {
                    textLine.il = bRect.iTl.iX - aItemRect.iTl.iX;
                    }
                
                aLayouts[column] = textLine;
                }
            }

        ++column;
        }
    }

// -----------------------------------------------------------------------------
// CColumnListBoxData::SubCellsMightIntersect
// -----------------------------------------------------------------------------
//
EXPORT_C void CColumnListBoxData::SubCellsMightIntersect( const TBool aMightIntersect )
    {
    iExtension->iSubCellsMightIntersect = aMightIntersect;
    }
    
void CColumnListBoxDataExtension::CreateColorBitmapsL()
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxDataExtension", __FUNCTION__, __LINE__ );
    /* size calculation relies on fact, that currently all additional
    * icons in column lists are same size. Size could be calculated
    * from sizes availble in setconditionalsubcelll(), but that would
    * be too unreliable. And there is no way to calculate size of
    * icons created by symbian's old api.
    */
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    TAknLayoutRect r;
    r.LayoutRect( mainPane, AknLayoutScalable_Avkon::listscroll_gen_pane(0) );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Avkon::list_gen_pane(0) );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Avkon::list_single_pane(0) );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Avkon::list_single_pane_g1(0) );
    TSize aSize = r.Rect().Size();
    
    TRgb color, hiliColor;
    TInt error;
    // icon #13 main area   additional list icons   #215
    // icon #16 list highlight  additional list iconsform checkbox, radio button    #215

    error = AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                       color,
                                       KAknsIIDQsnIconColors,
                                       EAknsCIQsnIconColorsCG13 );
    if ( error )
        {
        return;
        }
    error = AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                       hiliColor,
                                       KAknsIIDQsnIconColors,
                                       EAknsCIQsnIconColorsCG16 );
    if ( error )
        {
        return;
        }
    
     if ( iColorBmp && iColorBmp->SizeInPixels() == aSize
          && color == iIconColor && hiliColor == iHiliIconColor )
         {
         return;
         }

    iIconColor = color;
    iHiliIconColor = hiliColor;

    if ( !iColorBmp )
        {
        iColorBmp = new( ELeave ) CFbsBitmap();
        iColorBmp->Create( aSize, CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
        }
    else if ( iColorBmp->SizeInPixels() != aSize )
        {
        iColorBmp->Resize( aSize );
        }
    if ( !iHiliBmp )
        {
        iHiliBmp = new( ELeave ) CFbsBitmap();
        iHiliBmp->Create( aSize, CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
        }
    else if ( iHiliBmp->SizeInPixels() != aSize )
        {
        iHiliBmp->Resize( aSize );
        }

    CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );

    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( iColorBmp );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );
    fbsBitGc->SetPenStyle(CGraphicsContext::ENullPen);
    fbsBitGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    fbsBitGc->SetBrushColor( color );
    fbsBitGc->Clear();
    CleanupStack::PopAndDestroy( bmpDevice );
    bmpDevice = NULL;
    
    bmpDevice = CFbsBitmapDevice::NewL( iHiliBmp );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );
    fbsBitGc->SetPenStyle(CGraphicsContext::ENullPen);
    fbsBitGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    fbsBitGc->SetBrushColor( hiliColor );
    fbsBitGc->Clear();
    CleanupStack::PopAndDestroy( bmpDevice );
    bmpDevice = NULL;

    CleanupStack::PopAndDestroy( fbsBitGc );
    }


EXPORT_C TUint32 CColumnListBoxData::CurrentItemTextWasClipped() const
    {
    return iExtension ? iExtension->iClippedColumns : 0;
    }

TBool CColumnListBoxData::KineticScrollingEnabled() const
    {
    if ( iExtension )
        {
        return iExtension->iKineticScrolling;       
        }
    return EFalse;
    }


// End of File
