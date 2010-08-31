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
* Description:   List box implementation.
*
*/

  
#include <e32base.h>
#include <e32keys.h>
#include <bamatch.h>
#include <badesca.h>
#include <barsread.h>
#include <eiklbx.h>
#include <eiklbv.h>
#include <eiklbi.h>
#include <eiklbm.h>
#include <eikenv.h>
#include <eiklbx.pan>
#include <gulbordr.h>
#include <eikbutb.h>
#include <coemain.h>
#include <w32std.h>
#include <gulutil.h>
#include <uikon.hrh>
#include <eikkeys.h>
//#include <laflistb.h>
#include <laflbx.h>

#include <eikpanic.h>
#include <eikcmobs.h>

// Needed to use MopGetObject
#include <coemop.h>
#include <eikmenub.h> 
#include <AknLayout.lag>
#include <aknenv.h>
#include <AknDef.h>
#include <AknUtils.h>

#include <aknappui.h>
#include <aknPopup.h>

#include <AknTasHook.h>
// For hash key marking.
#include <e32property.h>
#include <featmgr.h>
#include <centralrepository.h>
#include <cenrepnotifyhandler.h>
#include <AknFepInternalCRKeys.h> // KAknFepHashKeySelection
#include <AvkonInternalCRKeys.h>  // KAknQwertyInputModeActive
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknphysics.h>
#include <aknphysicsobserveriface.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistboxtfxinternal.h> // LISTBOX EFFECTS IMPLEMENTATION
#include <aknlistloadertfx.h>
#include <aknlistboxtfx.h>
#endif

#include <touchfeedback.h>
#include <akncollection.h>
#include <aknitemactionmenu.h>
#include <aknlongtapdetector.h>
#include <AknPriv.hrh>
#include "akntrace.h"

// timeout for long keypress used in markable lists
const TInt KLongPressInterval = 600000; // 0,6 seconds
const TInt KEikListBoxPointerRepeatInterval = 100000;  // in micro conds (= 0.1 secod)

// Maximum scroll speed ( max amount of items moved one time )
const TInt KDefaultMaxSpeed = 30;
const TInt KDefaultStepSpeed = 5;
const TInt KEikListBoxInvalidIndex=-1;
//interval time for disable second point event
const TInt KTwoPointerUpEventInterval = 120;    //  120 millisecond ( = 0.12 second ) 
// -----------------------------------------------------------------------------
// If a parent to the supplied control has its Gc set, this function will find 
// it and return it.
// -----------------------------------------------------------------------------
//
LOCAL_C CWindowGc* ReplaceGcWithCustomGc( const CEikListBox* aListBox )
    {
    _AKNTRACE_FUNC_ENTER;
    const CCoeControl* parent = aListBox;
    CWindowGc* customGc;
    while(parent)
        {
        customGc = parent->GetGc();
        if ( customGc )
            {
            CListItemDrawer* itemDrawer = aListBox->View()->ItemDrawer();
            CWindowGc* originalGc = itemDrawer->Gc();
            if ( customGc == originalGc )
            {
                _AKNTRACE_FUNC_EXIT;
                return NULL;
                }
            else
                {
                itemDrawer->SetGc( customGc );
                _AKNTRACE_FUNC_EXIT;
                return originalGc;
                }
            }
        parent = parent->Parent();
        }
    _AKNTRACE_FUNC_EXIT;
    return NULL;
    }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
// ---------------------------------------------------------------------------
// Helper function that selects list items
// ---------------------------------------------------------------------------
//
LOCAL_C void SelectL( CListBoxView* aView, MAknListBoxTfxInternal* transApi, TInt aIndex, TBool select, TBool force = EFalse )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aView->ItemIsSelected( aIndex ) == select )
        {
        if ( force || transApi->SetPosition( MAknListBoxTfxInternal::EListItem, aView->ItemPos( aIndex ), aIndex ) != KErrNone )
            {
            aView->DrawItem( aIndex );
            }
        }
    else if ( select )
        {
        if ( aIndex >= aView->TopItemIndex() && aIndex <= aView->BottomItemIndex() )
            {
            aView->SelectItemL( aIndex );
            }
        else if ( !transApi->Exist( MAknListBoxTfxInternal::EListItem, aIndex ) )
            {
            aView->SelectItemL( aIndex );
            }
        else
            {
            TInt topItemIndex = aView->TopItemIndex();
            aView->SetTopItemIndex( aIndex );
            aView->SelectItemL( aIndex );
            aView->SetTopItemIndex( topItemIndex );
            }
        }
    else
        {
        if ( aIndex >= aView->TopItemIndex() && aIndex <= aView->BottomItemIndex() )
            {
            aView->DeselectItem( aIndex );
            }
        else if ( !transApi->Exist( MAknListBoxTfxInternal::EListItem, aIndex ) )
            {
            aView->DeselectItem( aIndex );
            }
        else
            {
            TInt topItemIndex = aView->TopItemIndex();
            aView->SetTopItemIndex( aIndex );
            aView->DeselectItem( aIndex );
            aView->SetTopItemIndex( topItemIndex );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// Helper function that updates list item selections
// ---------------------------------------------------------------------------
//
LOCAL_C void UpdateSelectionsL( CListBoxView* aView, MAknListBoxTfxInternal* transApi, TInt aHl, TInt aOld, TInt aAnchor, TBool aSelect )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aHl < aOld )
        {
        // Going up
        if ( aOld <= aAnchor )
            {
            // Going up away
            SelectL( aView, transApi, aOld, aSelect, ETrue );
            for ( TInt i = aOld - 1; i > aHl; i-- )
                {
                SelectL( aView, transApi, i, aSelect );
                }
            SelectL( aView, transApi, aHl, aSelect, ETrue );
            }
        else if ( aHl >= aAnchor )
            {
            // Going up against
            for ( TInt i = aOld; i > aHl; i-- )
                {
                SelectL( aView, transApi, i, !aSelect );
                }
            SelectL( aView, transApi, aHl, aSelect, ETrue );
            }
        else
            {
            // Passing anchor
            for ( TInt i = aOld; i > aAnchor; i-- )
                {
                SelectL( aView, transApi, i, !aSelect );
                }
            for ( TInt i = aAnchor; i >= aHl; i-- )
                {
                SelectL( aView, transApi, i, aSelect );
                }
            }
        for ( TInt i = aView->BottomItemIndex(); i >= aView->TopItemIndex(); i-- )
            {
            if ( i < aHl || i > aOld )
                {
                if ( transApi->SetPosition( MAknListBoxTfxInternal::EListItem, aView->ItemPos( i ), i ) != KErrNone )
                    {
                    aView->DrawItem( i );
                    }
                }
            }
        }
    else if ( aHl >= aOld )
        {
        // Going down
        if ( aOld >= aAnchor )
            {
            // Going down away
            SelectL( aView, transApi, aOld, aSelect, ETrue );
            for ( TInt i = aOld + 1; i < aHl; i++ )
                {
                SelectL( aView, transApi, i, aSelect );
                }
            SelectL( aView, transApi, aHl, aSelect, ETrue );
            }
        else if ( aHl <= aAnchor )
            {
            // Going down against
            for ( TInt i = aOld; i < aHl; i++ )
                {
                SelectL( aView, transApi, i, !aSelect );
                }
            SelectL( aView, transApi, aHl, aSelect, ETrue );
            }
        else
            {
            // Passing anchor
            for ( TInt i = aOld; i < aAnchor; i++ )
                {
                SelectL( aView, transApi, i, !aSelect );
                }
            for ( TInt i = aAnchor; i <= aHl; i++ )
                {
                SelectL( aView, transApi, i, aSelect );
                }
            }
        for ( TInt i = aView->BottomItemIndex(); i >= aView->TopItemIndex(); i-- )
            {
            if ( i > aHl || i < aOld )
                {
                if ( transApi->SetPosition( MAknListBoxTfxInternal::EListItem, aView->ItemPos( i ), i ) != KErrNone )
                    {
                    aView->DrawItem( i );
                    }
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

//
// class CMatchBuffer
//

NONSHARABLE_CLASS(CMatchBuffer) : public CBase
    {   
public:
    enum TExtent
        { EFull, EMinimal };
public:
    static CMatchBuffer* NewL(TExtent aExtent);
    ~CMatchBuffer();
    void ConstructMatchBufferL();
public:
    RIncrMatcherBase* iMatchBuffer;
    TInt iPressedIndex; 
    TBool iDragToAnotherItem; 
    };

CMatchBuffer* CMatchBuffer::NewL(TExtent aExtent)
    {
    CMatchBuffer* buffer=new(ELeave) CMatchBuffer;
    if (aExtent==EFull)
        {
        CleanupStack::PushL(buffer);
        buffer->iMatchBuffer=new(ELeave)RIncrMatcherBuf<CEikListBox::KEikMaxMatchingBufferLength>;
        CleanupStack::Pop( buffer );
        }
    return buffer;
    }

CMatchBuffer::~CMatchBuffer()
    {
    delete iMatchBuffer;
    }

void CMatchBuffer::ConstructMatchBufferL()
    {
    iMatchBuffer=new(ELeave)RIncrMatcherBuf<CEikListBox::KEikMaxMatchingBufferLength>;
    }

//
// class CLBMSKCommandObserver
//

NONSHARABLE_CLASS(CLBMSKCommandObserver) : public MEikCommandObserver
    {
public:
    CLBMSKCommandObserver(CEikButtonGroupContainer *aCba, CEikListBox *aListBox);
    void ProcessCommandL(TInt aCommandId);
    CEikButtonGroupContainer *iCba;
    CEikListBox *iListBox;
    TInt iCurrentResource;
    };


CLBMSKCommandObserver::CLBMSKCommandObserver(CEikButtonGroupContainer *aCba, CEikListBox *aListBox)
     : iCba(aCba), iListBox(aListBox)
    {
    }

void CLBMSKCommandObserver::ProcessCommandL(TInt aCommandId)
    {
    switch ( aCommandId )
        {
        case EAknSoftkeyMark:
            {
            TInt index = iListBox->CurrentItemIndex();
            iListBox->View()->SelectItemL(index);
            iCba->SetCommandL(3,R_AVKON_SOFTKEY_UNMARK);
            iCba->DrawNow();
            iCurrentResource = R_AVKON_SOFTKEY_UNMARK;        
            }
            break;
        case EAknSoftkeyUnmark:
            {
            TInt index = iListBox->CurrentItemIndex();
            iListBox->View()->DeselectItem(index);
            iCba->SetCommandL(3,R_AVKON_SOFTKEY_MARK);
            iCba->DrawNow();
            iCurrentResource = R_AVKON_SOFTKEY_MARK;        
            }
            break;
        case EAknSoftkeyShiftMSK:
            {
            iListBox->DoShiftMSKMarkingL();
            }
            break;
        default:
            break;
        }
    }

//
// class CListBoxExt
//

NONSHARABLE_CLASS(CListBoxExt) : public CBase, public MListVisibilityObserver,
    public MCenRepNotifyHandlerCallback,
    public MAknPhysicsObserver,
    public MAknCollection,
    public MAknLongTapDetectorCallBack
    {
public:
    static CListBoxExt* NewL(CEikListBox& aListBox);
    ~CListBoxExt();

    // new functions
    void CreateMatchBufferL();
    void CheckCreateBufferL();
    CMatchBuffer* Buffer() const;
    TBool IsMatchBuffer() const;
    void SetReasonForFocusLost(CEikListBox::TReasonForFocusLost aReasonForFocusLost);
    CEikListBox::TReasonForFocusLost ReasonForFocusLost() const;

    /// @since 3.0
    void AddItemChangeObserverL( MListBoxItemChangeObserver* aObserver );
    /// @since 3.0
    TBool RemoveItemChangeObserver( MListBoxItemChangeObserver* aObserver );
    /// @since 3.0
    void FireItemChange(CEikListBox* aListBox);
    
    void CreateMSKObserverL(CEikButtonGroupContainer *aCba, 
                                     CEikListBox *aListBox);
    void RemoveMSKObserver(CEikListBox *aListBox);

    // @since 3.2
    void AddSelectionObserverL( MListBoxSelectionObserver* aObserver );
    TBool RemoveSelectionObserver( MListBoxSelectionObserver* aObserver );
    // Starts the long press timer.
    void StartLongPressTimerL();
    TBool IsInIgnoreRect( const TPoint& aPoint ) const;
    //Tests the item needs to handle all point event or not.
    TBool IsInHandleAllPointEventArray(const TInt aIndex);
public: // from MListVisibilityObserver
    TBool IsVisible() const;
    void SetUpdateScrollBarsColors(TBool aUpdate);
    TBool UpdateScrollBarsColors() const;
public: // from MCenRepNotifyHandlerCallback
    void HandleNotifyInt(TUint32 aId, TInt aNewValue);
    
public: // MAknPhysicsObserver
    virtual void ViewPositionChanged( const TPoint& aNewPosition,
                                      TBool aDrawNow = ETrue,
                                      TUint aFlags = 0 );
    virtual void PhysicEmulationEnded();
    virtual TPoint ViewPosition() const;

// From MAknCollection
    /**
     * Returns the collection state. The state is combination of
     * flags defined in MAknCollection::TStateFlag. 
     *
     * @return  Collection state.
     */
    TUint CollectionState() const;

    /**
     * Notifies that item action menu (CAknItemActionMenu)
     * was closed. 
     */
    void ItemActionMenuClosed();

    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    TInt CollectionExtension( TUint aExtensionId, TAny*& a0, TAny* a1 );

// From MAknLongTapDetectorCallBack
    /**
     * Long tap detector callback 
     *
     * @param aPenEventLocation Long tap event location relative to parent control.
     * @param aPenEventScreenLocation Long tap event location relative to screen.
     */
    void HandleLongTapEventL( const TPoint& aPenEventLocation,
                              const TPoint& aPenEventScreenLocation );

// New single click related methods
    /**
     * Reports collection change event.
     */
    void ReportCollectionChangedEvent();

    /**
     * Enables or disables the highlight 
     * @param aEnabled ETrue to enable EFalse to disable
     * @param aPointerEnabled ETrue if highlight was enabled by pointer event.
     */
    void EnableHighlight( TBool aEnabled, TBool aPointerEnabled = EFalse );

    /**
     * Sets the highlight for the first item visible after single click 
     * is disabled
     */
    void DisableSingleClick();

    /**
     * Disables item specific menu.
     */
    void DisableItemSpecificMenu();

    /**
     * Sends pointer event to long tap detector if necessary.
     * 
     * @aPointerEvent Pointer event to send to long tap detector.
     */
    void LongTapPointerEventL( const TPointerEvent& aPointerEvent );

    /**
     * Cancels long tap detecting if detector is active.
     */
    void CancelLongTapL();

    /**
     * Enables highlight with key event if listbox is single click enabled.
     * 
     * @param aKeyEvent Received key event.
     * @param aType Key event type.
     * @return ETrue if key should be consumed.
     */
    TBool EnableHighlightWithKeyEventL(
            TInt aTopItemIndex,
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

    /**
     * Returns ETrue if list has currently marked items.
     * 
     * @return ETrue if list has marked items.
     */
    TBool MarkedItems() const;

public:
    void InitPhysicsL();
	
    /**
    * Moves the current item cursor in the specified direction. This function 
    * is called by @c CEikListBox in response to user input when physics 
    * is enabled.
     *
    * @return @c ETrue if the event was consumed.
    *
    * @param aCursorMovement The cursor movement to apply. 
    * @param aSelectionMode The selection mode of the calling list box.
    */
    TBool MovePhysicsCursorL(CListBoxView::TCursorMovement aCursorMovement, 
                             CListBoxView::TSelectionMode aSelectionMode);
   
    static TInt HighlightTimerCallback( TAny* aPtr );
	void CheckScrollBarVisibility();
    void StartHighlightTimer();
    void CancelHighlightTimer();
    TBool HighlightTimerActive() const;
    void ImmediateFeedback( TTouchLogicalFeedback aFeedback,
                            TTouchFeedbackType aFeedbackType,
                            const TPointerEvent& aPointerEvent );
    TBool FeedbackEnabledOnUpEvent();
    void SetFlickOngoing( TBool );
    void SetPanningOngoing( TBool );
    TBool FlickOrPanningOngoing();
    TInt ListBottomLimit();
    
private: 
    CListBoxExt(CEikListBox& aListBox);
    void ConstructL();    
    static TInt QwertyModeChangeNotification(TAny* aObj);  
    void HandleQwertyModeChangeNotification();
    // Callback method for long press timer.
    static TInt ReportLongPressL( TAny* aThis );
    // Handles long press.
    void DoHandleLongPressL();
       
private:
    enum {
        EUpdateScrollBarsColors =0x1,
        EMSKKeyDownEventReceived = 0x2,
        EHighlightEnabledByPointer = 0x4
    };

private: 
    NONSHARABLE_CLASS(CSubscriber) : public CActive
        {
    public:
        CSubscriber(TCallBack aCallBack, RProperty& aProperty);
        ~CSubscriber();

    public: // New functions
        void SubscribeL();
        void StopSubscribe();

    private: // from CActive
        void RunL();
        void DoCancel();

    private:
        TCallBack   iCallBack;
        RProperty&  iProperty;
        };    
public:

    // The index of an item, which has received the latest pointer down event.
    // This value is used in pointer up event handling to check whether or
    // not the same item received both down and up events.
    TInt iLastDownTappedItem;

    TInt iEventModifiers;
    TBool iWesternVariant;
    TBool iAknFepHashKeySelection;
    TBool iQwertyMode;
    TBool iMSKObserverEnabled;
    TBool iMSKButtonGroupAlive; // status of buttongroup, which is used for MSK observer
    // these are used for shift, ctrl and hash keys in markable lists    
    CPeriodic* iLongPressTimer; 
    TBool iSelectionModeEnabled;
    TBool iShortHashMark;
    // Contains only references, observers not owned
    RPointerArray<MListBoxSelectionObserver> iSelectionObservers;
    // used in CEikListBox::HandlePointerEventL and
    // CEikListBox::OfferKeyEventL to enable multiselection with hash key
    TBool iShiftKeyPressed;
    // Last stuly down position
    TBool iIsDownOnItem;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    TBool iSelect;
    TInt iAnchor;
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    TInt iSpeed;
    // Last pointer event pos
    TPoint iLastPoint;

    TInt iMaxSpeed;
    TInt iStepSpeed;
    TInt iInterval;
    CPeriodic* iHighlightTimer;    
    CAknPhysics *iPhysics;
    TPoint iDragStartPosition;
    TPoint iLastPointerPos;
    TBool iBackgroundDrawingSuppressed;
    TBool iClickEventsAllowed;
    TBool iScrolling;
    TSize iViewSize;
    TSize iWorldSize;
    TBool iItemDraggingReported;
    TTime iStartTime;
    TInt iItemsInSingleLine;
    TBool iEffectsEnabled;
    
    TPoint iViewPosition; // Current view position
    TInt iSelectedIndex;
    //Array of items need to handle point event everytime.
    RArray< TInt > iMutiTappingItems;
    // To calculate twice click interval  time on same item.
    TUint32 iListPointUpTime;
    TInt iLastItemIndex;
    
    // Used to disable list scrolling in certain list types.
    TBool iScrollingDisabled;
    
    // Whether or not pen down on item should be reported on highlight
    // timer callback.
    TBool iReportDelayedPenDown;
    
    // Whether or not multiselection should be done on highlight
    // timer callback.
    TBool iDelayedMultiselection;
    
    // Marking mode for multiselection lists is disabled when flicking.
    TBool iMarkingDisabled;
 
    // part of HandlePointerEventL for marking is moved to highlight timer with this flag
    TBool iMarkableListMarking;
    TBool iMarkableListShiftKeyPressed;
    TInt iMarkableListSelectionMode;
   
    // previous top item 
    TInt iPrevTopItemIndex;
    // is flick stopped by down event
    TBool iFlickStopped;
    
    TTouchLogicalFeedback iFeedbackType;
    
    /**
     * Pointer to item action menu.
     * Not own.
     */
    CAknItemActionMenu* iItemActionMenu;    
    
   /**
    * Long tap detector
    */
    CAknLongTapDetector* iLongTapDetector;

   /**
    * Single click mode enabled or not.
    */
    TBool iSingleClickEnabled;

   /**
    * Item that opened the item action menu
    */
    TInt iLongTappedItem;
    /**
     * Pointer event to be forwarded to the long tap detector upon
     * highlight timer completion.
     */
    TPointerEvent iDelayedPointerDownEvent;
    
private:
    CMatchBuffer* iBuffer;
    CEikListBox& iListBox;
    CEikListBox::TReasonForFocusLost iReasonForFocusLost;
    TInt iFlags;
    // Contains only references, observers not owned
    RPointerArray<MListBoxItemChangeObserver> iItemChangeObservers;

    // For hash key selection.    
    CRepository* iCenRep;
    CCenRepNotifyHandler* iCenRepNotifyHandler;      
    CSubscriber* iQwertyModeStatusSubscriber;
    RProperty iQwertyModeStatusProperty;    
    MEikCommandObserver *iMSKCommandObserver; // this is for markable/multiselection list query
    /**
     * Pointer to the feedback object. Not owned.
     */    
    MTouchFeedback* iFeedback;

    /**
     * Is flick ongoing or not.
     */    
    TBool iFlickOngoing;

    /**
     * Is panning ongoing or not.
     */    
    TBool iPanningOngoing;

    /**
     * Height of the list in pixels.
     */    
    TInt iListBottomLimit;
    };
    
// CEikListBoxExt    

CListBoxExt* CListBoxExt::NewL( CEikListBox& aListBox )
    { // static
    _AKNTRACE_FUNC_ENTER;
    CListBoxExt* self = new (ELeave) CListBoxExt( aListBox );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }

CListBoxExt::CListBoxExt(CEikListBox& aListBox)
    : iLastDownTappedItem(KErrNotFound), iWesternVariant(ETrue), 
      iAknFepHashKeySelection(EFalse), 
      iQwertyMode(EFalse), iLongPressTimer(NULL), iSelectionModeEnabled(EFalse),
      iLastPoint(0,0), iMaxSpeed( KDefaultMaxSpeed ), iStepSpeed( KDefaultStepSpeed ),
      iInterval( KEikListBoxPointerRepeatInterval ),
      iClickEventsAllowed( ETrue ),
      iWorldSize(0,0),
      iSelectedIndex( KErrNotFound ),
      iListPointUpTime(0),
      iLastItemIndex(-1),
      iItemActionMenu( NULL ),
      iLongTapDetector( NULL ),
      iSingleClickEnabled( iAvkonAppUi->IsSingleClickCompatible() ),
      iLongTappedItem( KErrNotFound ),
      iListBox(aListBox)      
    {
    }

CListBoxExt::~CListBoxExt()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iItemActionMenu )
        {
        iItemActionMenu->RemoveCollection( *this );
        }
    if ( iLongTapDetector )
        {
        delete iLongTapDetector;
        }

    delete iPhysics;
    delete iHighlightTimer;
    iMutiTappingItems.Close();
    delete iLongPressTimer;    
    FeatureManager::UnInitializeLib();
    iItemChangeObservers.Reset();
    iSelectionObservers.Reset();    
    delete iBuffer;

    // Stop listening CenRep.
    if (iCenRepNotifyHandler)
        {
        iCenRepNotifyHandler->StopListening();
        }
    delete iCenRepNotifyHandler;
    delete iCenRep; 
    
    // Stop subscribe in PubSub
    if (iQwertyModeStatusSubscriber)
        {
        iQwertyModeStatusSubscriber->StopSubscribe();
        }
    iQwertyModeStatusProperty.Close();
    delete iQwertyModeStatusSubscriber;   
    if (iMSKCommandObserver)
        {
        delete iMSKCommandObserver;
        iMSKCommandObserver = NULL;
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CListBoxExt::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Check the mode for hash key selection.
    // Eastern (short hash doesn't mark) == Chinese, Japanese or Vietnamese
    // Western (short hash marks) == All others.
    FeatureManager::InitializeLibL();
    if (FeatureManager::FeatureSupported(KFeatureIdChinese)  ||
        FeatureManager::FeatureSupported(KFeatureIdJapanese) || 
        (User::Language() & KAknLanguageMask) == ELangVietnamese)
        {
        iWesternVariant = EFalse;
        }
    
    // Start listening a CenRep key indicating whether hash key selection is active.
    TRAPD(err, iCenRep = CRepository::NewL(KCRUidAknFep));
    if (err == KErrNone)
        {
        iCenRepNotifyHandler = CCenRepNotifyHandler::NewL(*this,
            *iCenRep,
            CCenRepNotifyHandler::EIntKey,
            KAknFepHashKeySelection);

        iCenRepNotifyHandler->StartListeningL();
        iCenRep->Get(KAknFepHashKeySelection, iAknFepHashKeySelection);
        } 
        
    // Start also listening qwerty mode status. Hash key selection is disabled when
    // qwerty mode is active.
    User::LeaveIfError(iQwertyModeStatusProperty.Attach(KCRUidAvkon, 
        KAknQwertyInputModeActive));

    iQwertyModeStatusSubscriber = new (ELeave) CSubscriber(
        TCallBack(QwertyModeChangeNotification, this), iQwertyModeStatusProperty);
        
    iQwertyModeStatusSubscriber->SubscribeL();       
    
    // Get the initial value.
    HandleQwertyModeChangeNotification();
    
    iMSKObserverEnabled = ETrue; // By default listbox handles MSK
    iShortHashMark = EFalse;
    
    iLongPressTimer = CPeriodic::NewL( CActive::EPriorityStandard );    

    if ( CAknPhysics::FeatureEnabled() )
        {
        iPhysics = CAknPhysics::NewL( *this, &iListBox );
        iHighlightTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    iItemsInSingleLine = 1;
    iFeedback = MTouchFeedback::Instance();

    iItemActionMenu = CAknItemActionMenu::RegisterCollectionL( *this );

    if ( !( iListBox.iListBoxFlags & CEikListBox::EDisableItemSpecificMenu )
            && iItemActionMenu )
        {
        iLongTapDetector = CAknLongTapDetector::NewL( this );
        }
    if ( iSingleClickEnabled )
        {
        EnableHighlight( EFalse );
        }
    _AKNTRACE_FUNC_EXIT;
    } 


void CListBoxExt::AddSelectionObserverL(
        MListBoxSelectionObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    iSelectionObservers.AppendL( aObserver );
    _AKNTRACE_FUNC_EXIT;
    }

TBool CListBoxExt::RemoveSelectionObserver(
        MListBoxSelectionObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    TInt index = iSelectionObservers.Find( aObserver );
    if( KErrNotFound == index )
        {
        _AKNTRACE_FUNC_EXIT;
        return EFalse;
        }

    iSelectionObservers.Remove( index );
    _AKNTRACE_FUNC_EXIT;
    return ETrue;
    }

TPoint CListBoxExt::ViewPosition() const
    {
    return iViewPosition;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::CollectionState
// -----------------------------------------------------------------------------
//
TUint CListBoxExt::CollectionState() const
    {
    _AKNTRACE_FUNC_ENTER;
    TUint state( 0 );
    if ( iListBox.IsVisible()
            && ( !iListBox.DrawableWindow()
            || !iListBox.DrawableWindow()->IsFaded() ) )
        {
        state |= MAknCollection::EStateCollectionVisible;
        }
    if ( iListBox.iItemDrawer )
        {
        TInt drawerFlags( iListBox.iItemDrawer->Flags() );
        if ( !( drawerFlags 
                & CListItemDrawer::ESingleClickDisabledHighlight )
                && !( iFlags & EHighlightEnabledByPointer ) )
            {
            state |=  MAknCollection::EStateHighlightVisible;
            }
        if ( drawerFlags & CListItemDrawer::EDisableHighlight )
            {
            state |= MAknCollection::EStateViewOnly;
            }
        }
    if ( iListBox.iListBoxFlags & CEikListBox::EMultipleSelection )
        {
        state |= MAknCollection::EStateMultipleSelection;
        }
    _AKNTRACE_FUNC_EXIT;
    return state;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::ItemActionMenuClosed
// -----------------------------------------------------------------------------
//
void CListBoxExt::ItemActionMenuClosed()
    {
    if ( iLongTappedItem != KErrNotFound )
        {
        EnableHighlight( EFalse );
        iListBox.iView->DrawItem( iLongTappedItem );
        iLongTappedItem = KErrNotFound;
        }
    }


// -----------------------------------------------------------------------------
// CListBoxExt::CollectionExtension
// -----------------------------------------------------------------------------
//
TInt CListBoxExt::CollectionExtension(
        TUint /*aExtensionId*/, TAny*& /*a0*/, TAny* /*a1*/ )
    {
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CListBoxExt::HandleLongTapEventL
// ---------------------------------------------------------------------------
//
void CListBoxExt::HandleLongTapEventL( const TPoint& /*aPenEventLocation*/, 
                                       const TPoint& aPenEventScreenLocation )
    {
    _AKNTRACE_FUNC_ENTER;
    iLongTappedItem = iLastDownTappedItem;
    iLastDownTappedItem = KErrNotFound;
    iItemActionMenu->ShowMenuL( aPenEventScreenLocation, 0 );
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::ReportCollectionChangedEvent
// -----------------------------------------------------------------------------
//
void CListBoxExt::ReportCollectionChangedEvent()
    {
    if ( iItemActionMenu )
        {
        iItemActionMenu->CollectionChanged( *this );
        }
    }


// -----------------------------------------------------------------------------
// CListBoxExt::EnableHighLight
// -----------------------------------------------------------------------------
//
void CListBoxExt::EnableHighlight( TBool aEnabled, TBool aPointerEnabled )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iListBox.iItemDrawer && iSingleClickEnabled )
        {
        TBool wasEnabled( !( iListBox.iItemDrawer->Flags()
                & CListItemDrawer::ESingleClickDisabledHighlight ) );
        iFlags &= ( ~EHighlightEnabledByPointer );
        if ( aEnabled )
            {
            iListBox.iItemDrawer->ClearFlags(
                    CListItemDrawer::ESingleClickDisabledHighlight );
            if ( aPointerEnabled )
                {
                iFlags |= EHighlightEnabledByPointer;
                }
            }
        else
            {
            iListBox.iItemDrawer->SetFlags(
                    CListItemDrawer::ESingleClickDisabledHighlight );
            }
        if ( !aPointerEnabled
                && ( ( wasEnabled && !aEnabled )
                        || ( !wasEnabled && aEnabled ) ) )
            {
            ReportCollectionChangedEvent();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CListBoxExt::DisableSingleClick
// -----------------------------------------------------------------------------
//
void CListBoxExt::DisableSingleClick()
    {
    _AKNTRACE_FUNC_ENTER;
    EnableHighlight( ETrue );
	
    if ( iListBox.iView->ViewRect() != TRect() )
        {
        TInt topItemIndex = iListBox.iView->TopItemIndex();
        if ( iListBox.iView->ItemIsPartiallyVisible( topItemIndex) )
            {
            topItemIndex++; 
            }    
        TRAP_IGNORE( iListBox.UpdateHighlightL( topItemIndex ) );
        }
    
    DisableItemSpecificMenu();
    if ( iItemActionMenu )
        {
        iItemActionMenu->RemoveCollection( *this );
        iItemActionMenu = NULL;
        }
    iSingleClickEnabled = EFalse;

    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::DisableItemSpecificMenu
// -----------------------------------------------------------------------------
//
void CListBoxExt::DisableItemSpecificMenu()
    {
    _AKNTRACE_FUNC_ENTER;
    
    delete iLongTapDetector;
    iLongTapDetector = NULL;

    iListBox.iListBoxFlags |= CEikListBox::EDisableItemSpecificMenu;

    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CListBoxExt::LongTapPointerEventL
// -----------------------------------------------------------------------------
//
void CListBoxExt::LongTapPointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( iSingleClickEnabled && iLongTapDetector && iItemActionMenu  )
        {
        // Send event on down only if no marked items and item specific items
        // were found
        if ( aPointerEvent.iType != TPointerEvent::EButton1Down
                || ( !MarkedItems() && iItemActionMenu->InitMenuL() ) )
            {
            iLongTapDetector->PointerEventL ( aPointerEvent );
            }
        }
    }


// -----------------------------------------------------------------------------
// CListBoxExt::CancelLongTapL
// -----------------------------------------------------------------------------
//
void CListBoxExt::CancelLongTapL()
    {
    if ( iLongTapDetector && iLongTapDetector->IsActive() )
        {
        iLongTapDetector->CancelAnimationL();
        }
    }


// -----------------------------------------------------------------------------
// CListBoxExt::EnableHighlightWithKeyEventL
// -----------------------------------------------------------------------------
//
TBool CListBoxExt::EnableHighlightWithKeyEventL(
        TInt aTopItemIndex,
        const TKeyEvent& aKeyEvent,
        TEventCode aType )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aTopItemIndex is %d", aTopItemIndex );
    _AKNTRACE( "aKeyEvent.iCode is %d", aKeyEvent.iCode );
    _AKNTRACE( "aType is %d", aType );
    TBool consumeKey( EFalse );
    // With single click first key event enables highlight
    if ( iListBox.iItemDrawer->Flags()
            & CListItemDrawer::ESingleClickDisabledHighlight
            && iSingleClickEnabled )
        {
        TBool enableHighlight( EFalse );
        // Normal case: up, down, enter, msk pressed
        if ( aKeyEvent.iCode == EKeyUpArrow
                || aKeyEvent.iCode == EKeyDownArrow
                || aKeyEvent.iCode == EKeyEnter 
                || aKeyEvent.iCode == EKeyOK )
            {
            consumeKey = ETrue;
            enableHighlight = ETrue;
            }
        else if ( aType == EEventKeyDown
                && aKeyEvent.iScanCode == EStdKeyDevice3 )
            {
            iFlags |= EMSKKeyDownEventReceived;
            }
        // Msk pressed when MSK not visible
        else if ( iFlags & EMSKKeyDownEventReceived
                && aType == EEventKeyUp
                && aKeyEvent.iScanCode == EStdKeyDevice3 )
            {
            iFlags &= ( ~EMSKKeyDownEventReceived );
            enableHighlight = ETrue;
            }
        // Handle also left and right when grid in use.
        else if ( iItemsInSingleLine > 1
                && ( aKeyEvent.iCode == EKeyLeftArrow 
                || aKeyEvent.iCode == EKeyRightArrow ) )
            {
            consumeKey = ETrue;
            enableHighlight = ETrue;
            }
        if ( enableHighlight )
            {
            if ( iListBox.iView->ItemIsPartiallyVisible( aTopItemIndex ) )
                {
                aTopItemIndex++;
                }          
            // Enable marquee
            if ( iListBox.iItemDrawer->Flags() 
                    & CListItemDrawer::EDisableMarquee )
                {
                iListBox.iItemDrawer->
                    ClearFlags( CListItemDrawer::EDisableMarquee );
                }           
            EnableHighlight( ETrue );
            iListBox.UpdateHighlightL( aTopItemIndex );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return consumeKey;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::MarkedItems
// -----------------------------------------------------------------------------
//
TBool CListBoxExt::MarkedItems() const
    {
    return ( iListBox.iListBoxFlags & CEikListBox::ES60StyleMarkable
            || iListBox.iListBoxFlags & CEikListBox::EMultipleSelection )
            && iListBox.SelectionIndexes()->Count() > 0;
    }


// -----------------------------------------------------------------------------
// CListBoxExt::StartLongPressTimerL
// -----------------------------------------------------------------------------
//
void CListBoxExt::StartLongPressTimerL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iLongPressTimer )
        {
        if ( iLongPressTimer->IsActive() )
            {
            iLongPressTimer->Cancel();
            }

        iLongPressTimer->Start( KLongPressInterval, KLongPressInterval,
            TCallBack( ReportLongPressL, this ) );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CListBoxExt::ReportLongPressL
// -----------------------------------------------------------------------------
//
TInt CListBoxExt::ReportLongPressL( TAny* aThis )
    {
    _AKNTRACE_FUNC_ENTER;
    static_cast<CListBoxExt*>( aThis )->DoHandleLongPressL();
    _AKNTRACE_FUNC_EXIT;
    return 0;
    }

TBool CListBoxExt::IsInIgnoreRect( const TPoint& aPoint ) const
    {
    TInt offset = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine().iW / 5;
    TRect rect( iLastPoint.iX - offset, iLastPoint.iY - offset, 
                iLastPoint.iX + offset, iLastPoint.iY + offset ); 
    return rect.Contains( aPoint );
    }
    
TBool CListBoxExt::IsInHandleAllPointEventArray(const TInt aIndex)  
    {
    return iMutiTappingItems.FindInOrder( aIndex ) != KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CListBoxExt::DoHandleLongPressL
// -----------------------------------------------------------------------------
//
void CListBoxExt::DoHandleLongPressL()
    {
    _AKNTRACE_FUNC_ENTER;
    iSelectionModeEnabled = ETrue;
    if ( iLongPressTimer && iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }
    iListBox.ChangeSelectionMode( ETrue );
    _AKNTRACE_FUNC_EXIT;
    }


void CListBoxExt::CheckCreateBufferL()
    {
    if (!iBuffer)
        iBuffer=CMatchBuffer::NewL(CMatchBuffer::EMinimal);
    }

CMatchBuffer* CListBoxExt::Buffer() const
    {
    return iBuffer;
    }

void CListBoxExt::CreateMatchBufferL()
    {
    _AKNTRACE_FUNC_ENTER;
    if (iBuffer==NULL)
        iBuffer=CMatchBuffer::NewL(CMatchBuffer::EFull);
    else if (iBuffer->iMatchBuffer==NULL)
        iBuffer->ConstructMatchBufferL();
    _AKNTRACE_FUNC_EXIT;
    }

TBool CListBoxExt::IsVisible() const
    {
    return iListBox.IsVisible();
    }

TBool CListBoxExt::IsMatchBuffer() const
    {
    return (iBuffer && iBuffer->iMatchBuffer);
    }

void CListBoxExt::SetReasonForFocusLost(CEikListBox::TReasonForFocusLost aReasonForFocusLost)
    {
    iReasonForFocusLost = aReasonForFocusLost;
    }
 
TInt CListBoxExt::QwertyModeChangeNotification(TAny* aObj)
    {
    _AKNTRACE_FUNC_ENTER;
    if (aObj != NULL)
        {
        static_cast<CListBoxExt*>(aObj)->HandleQwertyModeChangeNotification();
        _AKNTRACE_FUNC_EXIT;
        return KErrNone;
        }
    else
        {
        _AKNTRACE_FUNC_EXIT;
        return KErrArgument;
        }
    }
    
void CListBoxExt::HandleQwertyModeChangeNotification()
    {
    TInt value = 0;
    iQwertyModeStatusProperty.Get(value);
    iQwertyMode = value;
    } 


void CListBoxExt::CreateMSKObserverL(CEikButtonGroupContainer *aCba, CEikListBox *aListBox)
    {
    _AKNTRACE_FUNC_ENTER;
    RemoveMSKObserver(aListBox); // only one observer can be set at a time
    iMSKCommandObserver = new(ELeave)CLBMSKCommandObserver(aCba, aListBox);
    iMSKButtonGroupAlive = ETrue;
    // if UpdateMSKCommandOpserver fails (there already is MSK observer set),
    // iMSKButtonGroupAlive will be set EFalse
    aCba->UpdateMSKCommandObserver(aListBox, iMSKCommandObserver);
    _AKNTRACE_FUNC_EXIT;
    }

void CListBoxExt::RemoveMSKObserver(CEikListBox *aListBox)
    {
    _AKNTRACE_FUNC_ENTER;
    if (iMSKCommandObserver)
        {
        if (iMSKButtonGroupAlive)
            {
            STATIC_CAST(CLBMSKCommandObserver*,iMSKCommandObserver)->iCba->UpdateMSKCommandObserver(aListBox, NULL);
            }
        delete iMSKCommandObserver;
        iMSKCommandObserver = NULL;
        }
    _AKNTRACE_FUNC_EXIT;
    }


// CEikListBoxExt::CSubscriber

CListBoxExt::CSubscriber::CSubscriber(TCallBack aCallBack, RProperty& aProperty)
    : CActive(EPriorityNormal), iCallBack(aCallBack), iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

CListBoxExt::CSubscriber::~CSubscriber()
    {
    Cancel();
    }

void CListBoxExt::CSubscriber::SubscribeL()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

void CListBoxExt::CSubscriber::StopSubscribe()
    {
    Cancel();
    }
    
void CListBoxExt::CSubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        SubscribeL();
        }
    }
    
void CListBoxExt::CSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

// CEikListBox

CEikListBox::TReasonForFocusLost CListBoxExt::ReasonForFocusLost() const
    {
    return iReasonForFocusLost;
    }

void CListBoxExt::AddItemChangeObserverL(
        MListBoxItemChangeObserver* aObserver )
    {
    iItemChangeObservers.AppendL( aObserver );
    }

TBool CListBoxExt::RemoveItemChangeObserver(
        MListBoxItemChangeObserver* aObserver )
    {
    TInt index = iItemChangeObservers.Find( aObserver );
    if( KErrNotFound == index )
        {
        return EFalse;
        }

    iItemChangeObservers.Remove( index );
    return ETrue;
    }

void CListBoxExt::FireItemChange(CEikListBox* aListBox)
    {
    TInt count = iItemChangeObservers.Count();
    for( int i=0; i < count; i++ )
        {
        iItemChangeObservers[i]->ListBoxItemsChanged(aListBox);
        }
    }

void CListBoxExt::SetUpdateScrollBarsColors(TBool aUpdate)
    {
    if (aUpdate)
        iFlags |= EUpdateScrollBarsColors;
    else
        iFlags &= ~EUpdateScrollBarsColors;
    }

TBool CListBoxExt::UpdateScrollBarsColors() const
    {
    return (iFlags&EUpdateScrollBarsColors);
    }

void CListBoxExt::CheckScrollBarVisibility()
    {
    // Kinetic scrolling is disabled if scrollbar is not visible
    if ( iListBox.iSBFrame )
        {
        TBool allowScrolling( iListBox.iSBFrame->ScrollBarVisibility(
            CEikScrollBar::EVertical ) != CEikScrollBarFrame::EOff );
                
        iScrollingDisabled = !allowScrolling;
        }   
    }
    
void CListBoxExt::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if (aId == KAknFepHashKeySelection)
        {
        iAknFepHashKeySelection = (TBool)aNewValue;
        }
    }


// ---------------------------------------------------------------------------
// Static callback function for the highlight timer. This should draw
// the highlight to the correct item and send the pen down event to the
// listbox observer.
// ---------------------------------------------------------------------------
//
TInt CListBoxExt::HighlightTimerCallback( TAny* aPtr )
    {
    _AKNTRACE_FUNC_ENTER;
    CListBoxExt* me = static_cast<CListBoxExt*>( aPtr );

    if ( me )
        {
        if ( me->iSingleClickEnabled )
            {
            me->EnableHighlight( ETrue, ETrue );
            }

        TRAP_IGNORE( me->iListBox.UpdateHighlightL(
                         me->iLastDownTappedItem ) );
        
        me->ImmediateFeedback( me->iFeedbackType, 
                               TTouchFeedbackType(ETouchFeedbackVibra | ETouchFeedbackAudio),
                               TPointerEvent() ); 
        
        me->CancelHighlightTimer();
        }
    _AKNTRACE_FUNC_EXIT;
    return 0;
    }


// ---------------------------------------------------------------------------
// Starts the highlight timer.
// ---------------------------------------------------------------------------
//
void CListBoxExt::StartHighlightTimer()
    {
    _AKNTRACE_FUNC_ENTER;
    CancelHighlightTimer();

    TTimeIntervalMicroSeconds32 timeout(
        iPhysics->HighlightTimeout() * 1000 );
    iHighlightTimer->Start( 
        timeout,
        timeout,
        TCallBack( CListBoxExt::HighlightTimerCallback, this ) );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Cancels the highlight timer and the delayed functions to be run upon
// its completion.
// ---------------------------------------------------------------------------
//
void CListBoxExt::CancelHighlightTimer()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iHighlightTimer )
        {
        iHighlightTimer->Cancel();
        }
    iReportDelayedPenDown = EFalse;
    iDelayedMultiselection = EFalse;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Checks if the highlight timer is currently running.
// ---------------------------------------------------------------------------
//
TBool CListBoxExt::HighlightTimerActive() const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE_FUNC_EXIT;
    return ( iHighlightTimer && iHighlightTimer->IsActive() );
    }


// ---------------------------------------------------------------------------
// CListBoxExt::ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CListBoxExt::ViewPositionChanged( const TPoint& aNewPosition,
                                       TBool aDrawNow,
                                       TUint /*aFlags*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    TInt delta = iViewPosition.iY - aNewPosition.iY;

#ifdef _DEBUG
    _LIT( KDMsg, "CListBoxExt::ViewPositionChanged, delta = %d, aDrawNow = %d" );
    RDebug::Print( KDMsg, delta, aDrawNow );
#endif // _DEBUG

    iListBox.ScrollView( delta, aDrawNow );
    iViewPosition = aNewPosition;
    _AKNTRACE_FUNC_EXIT;
    }
    

// ---------------------------------------------------------------------------
// CListBoxExt::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//
void CListBoxExt::PhysicEmulationEnded()
    {
    _AKNTRACE_FUNC_ENTER;    
    if ( iScrolling )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        iListBox.SuspendEffects( EFalse );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        TRAP_IGNORE( iListBox.ReportListBoxEventL(
                         MEikListBoxObserver::EEventFlickStopped ) );
        }
    
    iScrolling = EFalse;
    iListBox.iView->SetScrolling( iScrolling );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CListBoxExt::InitPhysicsL
// ---------------------------------------------------------------------------
//
void CListBoxExt::InitPhysicsL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iPhysics )
        {
        // calculate view center based on CEikListBoxView::iTopItemIndex
        TInt topItemIndex = iListBox.iView->TopItemIndex();
        TInt itemHeight = iListBox.iView->ItemHeight();
        TInt numberOfItems = iListBox.iModel->NumberOfItems();

        TSize viewSize( iListBox.iView->ViewRect().Size() );
        TSize worldSize( viewSize.iWidth, itemHeight * numberOfItems );
        
        // grid has several items in one line
        if ( iItemsInSingleLine > 1 )
            {
            worldSize.iHeight = 
                itemHeight * ( numberOfItems / iItemsInSingleLine );
            
            // handle non-full grid row
            if ( numberOfItems % iItemsInSingleLine )
                {
                worldSize.iHeight += itemHeight;
                }
            }
            
        // Reset offset if view's size has changed - this is needed if e.g.
        // HandleResourceChange is overridden by a derived implementation.
        if ( viewSize != iViewSize && iViewSize != TSize( 0, 0 ) )
            {
            iListBox.iView->SetItemOffsetInPixels( 0 );
            }

        TPoint viewCenter( viewSize.iWidth / 2, ( topItemIndex / iItemsInSingleLine ) * itemHeight - iListBox.iView->ItemOffsetInPixels() + ( viewSize.iHeight / 2 ) );

        // Make sure that world's size is always at least view size.
        worldSize.iHeight = Max( worldSize.iHeight, viewSize.iHeight );

        iPhysics->InitPhysicsL( worldSize, viewSize, EFalse );
        
        iWorldSize = worldSize;
        iViewSize = viewSize;
        iViewPosition = viewCenter;

#ifdef _DEBUG
        RDebug::Print( _L( "CListBox::InitPhysicsL, iViewSize = %d, %d" ), iViewSize.iWidth, iViewSize.iHeight );
        RDebug::Print( _L( "CListBox::InitPhysicsL, iViewPosition = %d, %d" ), iViewPosition.iX, iViewPosition.iY );
        RDebug::Print( _L( "CListBox::InitPhysicsL, verticalOffset = %d" ), iListBox.iView->ItemOffsetInPixels() );
#endif // _DEBUG
        iPrevTopItemIndex = iListBox.iView->TopItemIndex();
        iListBottomLimit = worldSize.iHeight;
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::MovePhysicsCursorL
// ---------------------------------------------------------------------------
//
TBool CListBoxExt::MovePhysicsCursorL(CListBoxView::TCursorMovement aCursorMovement, 
		                             CListBoxView::TSelectionMode aSelectionMode)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aCursorMovement = %d, aSelectionMode = %d", 
         aCursorMovement, aSelectionMode );    
    if ( !iPhysics || iScrollingDisabled )
        {
        _AKNTRACE_FUNC_EXIT;
        return EFalse;
        }
                    
    InitPhysicsL();
    TInt curViewPosY = iViewPosition.iY;
    TInt worldHeight = iWorldSize.iHeight;
    TInt viewHeight = iViewSize.iHeight;
    TInt offsetHeight = curViewPosY - ( viewHeight / 2 );
    TInt deltaPixels = 0;
    switch (aCursorMovement)
        {
        case CListBoxView::ECursorNextScreen:
            {
            if ( viewHeight > worldHeight - offsetHeight - viewHeight )
                {
                if ( worldHeight - offsetHeight - viewHeight > 0 )
                    {
                    iListBox.iView->MoveCursorL(CListBoxView::ECursorLastItem, aSelectionMode);
                    }
                break;
                }
            deltaPixels = viewHeight;
            break;
            }
        case CListBoxView::ECursorPrevScreen:
            {
            if ( viewHeight > offsetHeight )
                {
                if ( offsetHeight > 0 )
                    {
                    iListBox.iView->MoveCursorL(CListBoxView::ECursorFirstItem, aSelectionMode);
                    }
                break;
                }
            deltaPixels = -viewHeight;
            break;
            }
        default:
            {
            _AKNTRACE_FUNC_EXIT;
            return EFalse;
            }
        }
   
    if ( deltaPixels != 0 )
        {	
        TPoint newPosition( iViewPosition.iX,
                        deltaPixels + curViewPosY );
        ViewPositionChanged( newPosition );
        }
    _AKNTRACE_FUNC_EXIT;
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::ImmediateFeedback
// ---------------------------------------------------------------------------
//
void CListBoxExt::ImmediateFeedback( TTouchLogicalFeedback aFeedback,
                                     TTouchFeedbackType aFeedbackType,
                                     const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iFeedback )
        {
        iFeedback->InstantFeedback( &iListBox, aFeedback, aFeedbackType, aPointerEvent );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::FeedbackEnabledOnUpEvent
// ---------------------------------------------------------------------------
//
TBool CListBoxExt::FeedbackEnabledOnUpEvent()
    {
    _AKNTRACE_FUNC_ENTER;
    TBool enabled( EFalse );
    if ( ( iListBox.iItemDrawer->Flags() & CListItemDrawer::EPressedDownState ) &&
         !iFlickStopped )
        {
        enabled = ETrue;
        }
    _AKNTRACE_FUNC_EXIT;
    return enabled;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::SetFlickOngoing
// ---------------------------------------------------------------------------
//
void CListBoxExt::SetFlickOngoing( TBool aFlickOngoing )
    {
    iFlickOngoing = aFlickOngoing;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::SetPanningOngoing
// ---------------------------------------------------------------------------
//
void CListBoxExt::SetPanningOngoing( TBool aPanningOngoing )
    {
    iPanningOngoing = aPanningOngoing;
    }

// ---------------------------------------------------------------------------
// CListBoxExt::FlickOrPanningOngoing
// ---------------------------------------------------------------------------
//
TBool CListBoxExt::FlickOrPanningOngoing()
    {
    return ( iFlickOngoing | iPanningOngoing );
    }

// ---------------------------------------------------------------------------
// CListBoxExt::ListBottomLimit
// ---------------------------------------------------------------------------
//
TInt CListBoxExt::ListBottomLimit()
    {
    return iListBottomLimit;
    }

//
// class CEikListBox
//

const TInt KEikListBoxHNudgeSizeAsFractionOfViewRectWidth = 20; 
// const TInt KEikListBoxBackgroundColor = 15;      later, this will be a data member of the listbox  
const TInt KEikListBoxItemVGap = 6; // to allow a box to be drawn around each item
const TInt KEikListBoxInterItemGap = 2;

GLDEF_C void Panic(TEikListBoxPanic aPanic)
    {
    _LIT(KPanicCat,"EIKON-LISTBOX");
    User::Panic(KPanicCat,aPanic);
    }

EXPORT_C CEikListBox::CEikListBox()
/*DFRD can setup 4 margins (top, bottom, left, right) by setting iHorizontalMargin
to KLafListboxUseLafHorizMargins and iVerticalMargin to KLafListboxUseLafVertMargins.
The DFRD can also use 3 margins by setting either of these 2 values (iHorizonatalMargin
or iVerticalMargin) to another integer.  The application developer can only set 2
margins; iHorizontalMargin and iVerticalMargin*/
    :   iItemEditor(NULL)
    {
    _AKNTRACE_FUNC_ENTER;
    LafListBox::GetDefaultBorder(iBorder);
    iMargins = LafListBox::Margins();

    iItemHeight = iEikonEnv->NormalFont()->HeightInPixels() + KEikListBoxItemVGap;
    iBackColor = iEikonEnv->Color(EColorControlBackground);

    SetComponentsToInheritVisibility(EFalse);
    AKNTASHOOK_ADD( this, "CEikListBox" );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SetItemsInSingleLine( TInt aItems )
    {
    if ( iListBoxExt )
        {
        iListBoxExt->iItemsInSingleLine = aItems;
        }
    }

EXPORT_C void CEikListBox::UpdateViewColors()
    {
    _AKNTRACE_FUNC_ENTER;
    if(!iView)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if(IsDimmed())
        {
        iView->SetTextColor(iEikonEnv->ControlColor(EColorControlDimmedText,*this));
        iView->SetBackColor(iEikonEnv->ControlColor(EColorControlDimmedBackground,*this));
        iView->SetMatcherCursorColor(iEikonEnv->ControlColor(EColorControlHighlightBackground,*this));
        }
    else
        {
        iView->SetTextColor(iEikonEnv->ControlColor(EColorControlText,*this));
        iView->SetBackColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
        iView->SetMatcherCursorColor(iEikonEnv->ControlColor(EColorControlDimmedHighlightBackground,*this));
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::UpdateItemDrawerColors()
    {
    _AKNTRACE_FUNC_ENTER;
    if(!iItemDrawer)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if(IsDimmed())
        {
        iItemDrawer->SetTextColor(iEikonEnv->ControlColor(EColorControlDimmedText,*this));
        iItemDrawer->SetHighlightedTextColor(iEikonEnv->ControlColor(EColorControlDimmedHighlightText,*this));
        iItemDrawer->SetDimmedTextColor(iEikonEnv->ControlColor(EColorControlDimmedText,*this));
        iItemDrawer->SetBackColor(iEikonEnv->ControlColor(EColorControlDimmedBackground,*this));
        iItemDrawer->SetHighlightedBackColor(iEikonEnv->ControlColor(EColorControlDimmedHighlightBackground,*this));
        iItemDrawer->SetDimmedBackColor(iEikonEnv->ControlColor(EColorControlDimmedBackground,*this));
        }
    else
        {
        iItemDrawer->SetTextColor(iEikonEnv->ControlColor(EColorControlText,*this));
        iItemDrawer->SetHighlightedTextColor(iEikonEnv->ControlColor(EColorControlHighlightText,*this));
        iItemDrawer->SetDimmedTextColor(iEikonEnv->ControlColor(EColorControlDimmedText,*this));
        iItemDrawer->SetBackColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
        iItemDrawer->SetHighlightedBackColor(iEikonEnv->ControlColor(EColorControlHighlightBackground,*this));
        iItemDrawer->SetDimmedBackColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::FireItemChange()
    {
    if( iListBoxExt )
        {
        iListBoxExt->FireItemChange( this );
        }
    }

EXPORT_C CEikListBox::~CEikListBox()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    if (iCoeEnv && iEikonEnv && iAvkonEnv) 
        iAvkonEnv->RemoveCbaObserver();

    if (iListBoxExt)
        {
        iListBoxExt->RemoveMSKObserver(this);    
        delete iListBoxExt;
        iListBoxExt = NULL;
        }
        
    delete iSBFrame;
    
    if (!(iListBoxFlags & EKeepModel))
        delete iModel;
    
    if (iView)
        delete iView;
    else
        delete iItemDrawer;
    
    if (iLaunchingButton)
        {
        TPointerEvent event;
        event.iType=TPointerEvent::EButton1Up;
        event.iModifiers=0;
        event.iPosition=iLaunchingButton->Position();
        TRAP_IGNORE(iLaunchingButton->HandlePointerEventL(event));
        }
    
    ResetItemEditor();
    _AKNTRACE_FUNC_EXIT;
    }

void CEikListBox::InformMSKButtonGroupDeletion()
    {
    if (iListBoxExt)
        {
        iListBoxExt->iMSKButtonGroupAlive = EFalse;
        }
    }
    
EXPORT_C TBool CEikListBox::ItemExists(TInt aItemIndex) const
    {
    return ((aItemIndex >= 0) && (aItemIndex < iModel->NumberOfItems()));
    }

EXPORT_C void CEikListBox::RestoreCommonListBoxPropertiesL(TResourceReader& aReader)
    {
    _AKNTRACE_FUNC_ENTER;
    aReader.ReadInt8(); // version
    iListBoxFlags = aReader.ReadInt32();  
        
    iRequiredHeightInNumOfItems = aReader.ReadInt16();

    if (! (iListBoxFlags & EPageAtOnceScrolling))
        { // no loop scroll for viewers
        iListBoxFlags |= ELoopScrolling; // All lists will have loop scrolling.
        }

    if (iListBoxFlags & EIncrementalMatching)
        CreateMatchBufferL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C MListBoxModel* CEikListBox::Model() const
    {
    return iModel;
    }

EXPORT_C CListBoxView* CEikListBox::View() const
    {
    return iView;
    }

EXPORT_C void CEikListBox::CreateMatchBufferL()
    {
    CheckCreateExtensionL();
    iListBoxExt->CreateMatchBufferL();
    }

EXPORT_C void CEikListBox::SetItemHeightL(TInt aHeight)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aHeight = %d", aHeight );
    // won't actually leave if the horizontal/vertical scrollbars have both been turned off
    __ASSERT_ALWAYS((aHeight > 0), Panic(EEikPanicListBoxInvalidItemHeightSpecified));
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    TRect lastViewRect( iView->ViewRect() );
#endif
    iItemHeight = aHeight;
    TRect clientRect = iBorder.InnerRect(Rect());
    iView->SetItemHeight(aHeight);
    SetViewRectFromClientRect(clientRect);
    HandleViewRectSizeChangeL();

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if( iView->ViewRect() != lastViewRect )
        {
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
        if ( transApi )
            {
            transApi->Remove( MAknListBoxTfxInternal:: EListEverything );
            }
        }
#endif
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::ItemHeight() const
    {
    return iItemHeight;
    }

EXPORT_C TInt CEikListBox::CalcWidthBasedOnNumOfChars(TInt aNumOfChars) const
    {
    return CalcWidthBasedOnRequiredItemWidth(aNumOfChars * iEikonEnv->NormalFont()->MaxNormalCharWidthInPixels());
    }

EXPORT_C TInt CEikListBox::CalcWidthBasedOnRequiredItemWidth(TInt aTextWidthInPixels) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("aTextWidthInPixels = %d", aTextWidthInPixels);    
    TInt width = aTextWidthInPixels;
    if (iItemDrawer->Flags()&CListItemDrawer::EDrawMarkSelection)
        {
        width += iItemDrawer->MarkColumn() + iItemDrawer->MarkGutter();
        }
    width += (LafListBox::InnerGutter() + ListBoxMargins().iLeft + ListBoxMargins().iRight);
    width += iBorder.SizeDelta().iWidth;
    if (iSBFrame)
        {
#if COMMENTED_FOR_SERIES60_BECAUSE_SCROLLBAR_BREADTH_IS_NONZERO
        if (iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
            width += CEikScrollBar::DefaultScrollBarBreadth();
#endif
        }
    _AKNTRACE( "width = %d", width );    
    _AKNTRACE_FUNC_EXIT;
    return width;
    }

EXPORT_C TInt CEikListBox::CalcHeightBasedOnNumOfItems(TInt aNumOfItems) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aNumOfItems = %d", aNumOfItems );      
    TInt height;
    height = (aNumOfItems * iItemHeight);
    height += (ListBoxMargins().iTop + ListBoxMargins().iBottom);
    height += iBorder.SizeDelta().iHeight;
    if (iSBFrame)
        {
        if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
            height += CEikScrollBar::DefaultScrollBarBreadth();
        }
    _AKNTRACE( "height = %d", height );  
    _AKNTRACE_FUNC_EXIT;
    return height;
    }

EXPORT_C TSize CEikListBox::MinimumSize()
    {
    _AKNTRACE_FUNC_ENTER;
    TSize size;
    TSize minCellSize(iItemDrawer->MinimumCellSize());
    size.iWidth = minCellSize.iWidth + ListBoxMargins().iLeft + ListBoxMargins().iRight;
    size.iHeight = (ListBoxMargins().iTop + ListBoxMargins().iBottom) + (iRequiredHeightInNumOfItems * minCellSize.iHeight);
    if ((!(iListBoxFlags & EScrollBarSizeExcluded)) && iSBFrame)
        {
        if (iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
            size.iWidth += CEikScrollBar::DefaultScrollBarBreadth();
        if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
            size.iHeight += CEikScrollBar::DefaultScrollBarBreadth();
        }
    size += iBorder.SizeDelta();
    _AKNTRACE( "width = %d, height = %d", size.iWidth, size.iHeight ); 
    _AKNTRACE_FUNC_EXIT;
    return size;
    }

EXPORT_C TSize CEikListBox::CalcSizeInPixels(TInt aWidthAsNumOfChars, TInt aHeightAsNumOfItems) const
    {
    return TSize(CalcWidthBasedOnNumOfChars(aWidthAsNumOfChars), CalcHeightBasedOnNumOfItems(aHeightAsNumOfItems));
    }

EXPORT_C CEikScrollBarFrame* CEikListBox::CreateScrollBarFrameL(TBool aPreAlloc)
    {
    return CreateScrollBarFrameL(aPreAlloc, EFalse);
    }

EXPORT_C void CEikListBox::HandleViewRectSizeChangeL()
    {
    _AKNTRACE_FUNC_ENTER;
    iView->CalcBottomItemIndex();
    iView->CalcDataWidth();
    TInt currentItemIndex = iView->CurrentItemIndex();

    if ( ItemExists(currentItemIndex) )
        {
        TInt topItemIndex( iView->TopItemIndex() );
        TInt numberOfItems = iView->NumberOfItemsThatFitInRect( iView->ViewRect() );    
        TInt newTopItemIndex( KEikListBoxInvalidIndex ); 

        // Current item not visible or current item is the last item (not fully visible)
        if ( !iView->ItemIsVisible(currentItemIndex)
        	|| iListBoxExt && iListBoxExt->iPhysics 
        	&& currentItemIndex == ( topItemIndex + numberOfItems - 1 ) )
            {
            newTopItemIndex = iView->CalcNewTopItemIndexSoItemIsVisible( currentItemIndex );
            }
        else
            {
            // recalculates top index of list when mode be changed
            TInt totalItems = iModel->NumberOfItems();
            if ( (totalItems - topItemIndex) < numberOfItems )
                {
                newTopItemIndex = Max( 0, totalItems - numberOfItems );
                }
            }

        if ( newTopItemIndex != KEikListBoxInvalidIndex )
        	{
        	iView->SetTopItemIndex( newTopItemIndex );
        	if ( iListBoxExt && iListBoxExt->iPhysics )
        		{
        		iListBoxExt->InitPhysicsL();
        		}
            }
        }
    UpdateScrollBarsL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect clientRect = iBorder.InnerRect(Rect());
    SetViewRectFromClientRect(clientRect);
    TRAP_IGNORE(HandleViewRectSizeChangeL());
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::CountComponentControls() const
    {
    TInt count=CEikBorderedControl::CountComponentControls();
    if (iSBFrame && (iSBFrameOwned == ENotOwnedExternally))
        {
        if(iSBFrame->VerticalScrollBar()) 
           { 
           count+=iSBFrame->CountComponentControls(); 
           }
        }
    return count;
    }

EXPORT_C CCoeControl* CEikListBox::ComponentControl(TInt aIndex) const
    {
    TInt baseCount=CEikBorderedControl::CountComponentControls();
    if (aIndex<baseCount)
        {
        return CEikBorderedControl::ComponentControl(aIndex);
        }
    aIndex-=baseCount;
    if( iSBFrame && iSBFrame->VerticalScrollBar() ) 
        { 
        return iSBFrame->ComponentControl(aIndex); 
        } 
    else
        {
        return NULL;
        }
    }

EXPORT_C void CEikListBox::SetViewRectFromClientRect(const TRect& aClientRect)
    {
    _AKNTRACE_FUNC_ENTER;
    TRect rect(aClientRect);
    rect.SetRect(rect.iTl.iX + ListBoxMargins().iLeft, rect.iTl.iY + ListBoxMargins().iTop,
        rect.iBr.iX - ListBoxMargins().iRight, rect.iBr.iY - ListBoxMargins().iBottom);

    if ( iListBoxExt && iListBoxExt->iPhysics )
        {
        iViewRectHeightAdjustment = 0;
        iView->SetViewRect(rect);
        }
    else
        {
        iItemHeight = iView->ItemSize().iHeight;
        iViewRectHeightAdjustment = AdjustRectHeightToWholeNumberOfItems(rect);
        iView->SetViewRect(rect);
        }
        
    if ( iListBoxExt && 
         (iListBoxExt->iViewSize != rect.Size() ))
        {
        iListBoxExt->iViewSize = rect.Size();
        }    
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::RestoreClientRectFromViewRect(TRect& aClientRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    aClientRect=iView->ViewRect();
    aClientRect.SetRect(aClientRect.iTl.iX - ListBoxMargins().iLeft, aClientRect.iTl.iY - ListBoxMargins().iTop,
        aClientRect.iBr.iX + ListBoxMargins().iRight, aClientRect.iBr.iY + ListBoxMargins().iBottom);
    // height may have been rounded so correct it
    if (!iViewRectHeightAdjustment)
        return;
#ifdef ORIGINAL_UIKON_CODE
    if (iViewRectHeightAdjustment % 2 !=0)
        aClientRect.iBr.iY += 1;
    aClientRect.Grow(0, iViewRectHeightAdjustment/2);
#else // Series60 code
    aClientRect.iBr.iY += iViewRectHeightAdjustment;
#endif
    _AKNTRACE_FUNC_EXIT;
    // aClientRect.iBr.iY += iViewRectHeightAdjustment;
    }

EXPORT_C TInt CEikListBox::AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    // round down the height of aRect (if necessary) so that only a whole number of items can be displayed inside the listbox
    // returns the number of pixels reduced.
#ifdef ORIGINAL_UIKON_CODE
    TInt remainder = aRect.Height() % iItemHeight;
    if (remainder != 0) 
        {
        // need to adjust viewRect 
        aRect.Shrink(0, remainder/2);
        if (remainder % 2 != 0)     
            aRect.iBr.iY -= 1;
        // aRect.iBr.iY -= remainder;
        }
#else // Series 60 code
    // To catch places which use this in series 60
    // -- should use derived class version
    // from CAknColumnList or CEikFormattedCellListBox or something else.
    //__ASSERT_DEBUG(0, Panic(0));
    // This is dead code, can be reverted to original once we've tested
    // noone uses this.
    TInt remainder = aRect.Height() % iItemHeight;
    if (remainder != 0)
    {
        aRect.iBr.iY -= remainder;
        }
#endif
    _AKNTRACE_FUNC_EXIT;
    return remainder;
    }

EXPORT_C void CEikListBox::CalculatePopoutRect(TInt aTargetItemIndex, TInt aTargetYPos, TRect& aListBoxRect, TInt aMinHeightInNumOfItems) 
    {
    _AKNTRACE_FUNC_ENTER;
    /*controlling the maximum width, in pixels, of a choice list*/
    if((LafListBox::MaxCellWidthInNumOfPixels() != KLafListBoxNoMaxCellWidth) && (aListBoxRect.Width() > LafListBox::MaxCellWidthInNumOfPixels()))
        {
        aListBoxRect.iBr.iX = aListBoxRect.iTl.iX + LafListBox::MaxCellWidthInNumOfPixels();
        }
    // this function is designed for use by the choice list control
    TInt listBoxHeight = 0;
    TInt listBoxYPos = 0;
    TInt screenHeight = iAvkonAppUi->ApplicationRect().Height(); /*iCoeEnv->ScreenDevice()->SizeInPixels().iHeight;*/
    TInt maxDisplayedItems = (screenHeight - (ListBoxMargins().iTop + ListBoxMargins().iBottom) - iBorder.SizeDelta().iHeight) / iItemHeight;

    /*controlling the maximum number of items displayed in a choice list*/
    if(LafListBox::MaxHeightInNumOfItems() != KLafListBoxNoMaxHeightInNumOfItems)
        {
        maxDisplayedItems = Min(maxDisplayedItems,LafListBox::MaxHeightInNumOfItems());
        }
    TInt desiredHeightInNumOfItems = Max(iModel->NumberOfItems(), aMinHeightInNumOfItems);
    if (desiredHeightInNumOfItems > maxDisplayedItems)
        {
        listBoxHeight = CalcHeightBasedOnNumOfItems(maxDisplayedItems);     
        listBoxYPos = (screenHeight - listBoxHeight) / 2;
        TInt numOfDisplayedItemsAboveTarget = (aTargetYPos-listBoxYPos-ListBoxMargins().iTop)/iItemHeight;
        
        TInt topItemOrdinal=Max(0, (aTargetItemIndex-numOfDisplayedItemsAboveTarget));
        topItemOrdinal=Min(iModel->NumberOfItems()-maxDisplayedItems,topItemOrdinal);
        iView->SetTopItemIndex(iView->TopItemIndex()+topItemOrdinal);
        aListBoxRect.iTl.iY = listBoxYPos;
        aListBoxRect.iBr.iY = listBoxYPos + listBoxHeight;
        return;
        }
    listBoxHeight = CalcHeightBasedOnNumOfItems(desiredHeightInNumOfItems);
    TInt numOfItemsAbove = aTargetItemIndex;
    TInt potentialPixelsAboveTarget = 0;
    if (numOfItemsAbove > 0)
        {
        potentialPixelsAboveTarget = numOfItemsAbove * iItemHeight + ListBoxMargins().iTop + iBorder.Margins().iTop;
        }
    listBoxYPos = aTargetYPos - potentialPixelsAboveTarget;
    if ((listBoxYPos + listBoxHeight) >= screenHeight)
        listBoxYPos = screenHeight - listBoxHeight;
    if (potentialPixelsAboveTarget>aTargetYPos)
        listBoxYPos = 0;
    // find number of items below aTargetItemIndex
    TInt numberOfItemsBelowTarget = 0;
    TInt targetIndex = aTargetItemIndex;
    while (ItemExists(++targetIndex))
        ++numberOfItemsBelowTarget;
    TInt potentialPixelsBelowTarget = 0;
    if (numberOfItemsBelowTarget > 0)
        {
        potentialPixelsBelowTarget = numberOfItemsBelowTarget * iItemHeight + ListBoxMargins().iBottom + iBorder.Margins().iBottom;
        }
    if ((potentialPixelsBelowTarget + iItemHeight) > (screenHeight-aTargetYPos))
        listBoxYPos = screenHeight - listBoxHeight;
    aListBoxRect.iTl.iY = listBoxYPos;
    aListBoxRect.iBr.iY = listBoxYPos + listBoxHeight;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::TopItemIndex() const
    {
    _AKNTRACE( "iTopItemIndex = %d", iView->TopItemIndex() );
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    return iView->TopItemIndex();
    }

EXPORT_C TInt CEikListBox::BottomItemIndex() const
    {
    _AKNTRACE( "iBottomItemIndex = %d", iView->BottomItemIndex() );
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    return iView->BottomItemIndex();
    }

EXPORT_C void CEikListBox::SetTopItemIndex(TInt aItemIndex) const
    {
    _AKNTRACE( "aItemIndex = %d", aItemIndex );
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    iView->SetTopItemIndex(aItemIndex);
    UpdateScrollBarThumbs();
    }

EXPORT_C void CEikListBox::AdjustTopItemIndex() const
    {
    _AKNTRACE_FUNC_ENTER;
    TInt maxTopItemIndex=iView->BottomItemIndex() - iView->NumberOfItemsThatFitInRect(iView->ViewRect()) +1;
    maxTopItemIndex=Max(0, maxTopItemIndex);
    if (iView->TopItemIndex() > maxTopItemIndex)
        SetTopItemIndex(maxTopItemIndex);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::CurrentItemIndex() const
    {
    _AKNTRACE( "iView->CurrentItemIndex() is %d", iView->CurrentItemIndex() );
    __ASSERT_ALWAYS(iView, Panic(EEikPanicListBoxNoView));
    return iView->CurrentItemIndex();
    }

EXPORT_C void CEikListBox::UpdateCurrentItem(TInt aItemIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    TInt oldCurrentItemIndex = iView->CurrentItemIndex();
    iView->SetCurrentItemIndex(aItemIndex);
    if ( IsReadyToDraw() )
        {
        iView->DrawItem(oldCurrentItemIndex);
        }
    if (!(iView->ItemIsVisible(aItemIndex)) || iView->ItemIsPartiallyVisible(aItemIndex) )
        {
        SetTopItemIndex(iView->CalcNewTopItemIndexSoItemIsVisible(aItemIndex));
        
        if ( !iView->RedrawDisabled() )
            {           
            DrawNow();
            }
        }
#if NOT_USED_IN_SERIES60
// This is not used in Series 60 because in FIND, we do not want
// selectionindexes to have a list of indexes...
    if (!(iListBoxFlags & EMultipleSelection))
        {
        TRAPD(err,iView->UpdateSelectionL(CListBoxView::ESingleSelection));
        if (err!=KErrNone)
            iEikonEnv->NotifyIdleErrorWhileRedrawing(err);
        }
#endif

    iView->DrawItem(aItemIndex);
    TRAP_IGNORE(UpdateMarkUnmarkMSKL());
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SetCurrentItemIndex(TInt aItemIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aItemIndex = %d", aItemIndex );
    __ASSERT_ALWAYS(iView, Panic(EEikPanicListBoxNoView));
    TBool redrawDisabled = iView->RedrawDisabled();
    iView->SetDisableRedraw(ETrue);
    UpdateCurrentItem(aItemIndex);
    iView->SetDisableRedraw(redrawDisabled);
    
    if ( iListBoxExt && iListBoxExt->iPhysics && aItemIndex == 0 )
        {
        iView->SetItemOffsetInPixels( 0 );        
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SetCurrentItemIndexAndDraw(TInt aItemIndex) const
    {
    __ASSERT_ALWAYS(iView, Panic(EEikPanicListBoxNoView));
    UpdateCurrentItem(aItemIndex);
    }

EXPORT_C void CEikListBox::ConstructL(const CCoeControl* aParent,TInt aFlags)
    {
    _AKNTRACE_FUNC_ENTER;
    iListBoxFlags = aFlags;
    if (! (iListBoxFlags & EPageAtOnceScrolling))
        { // no loop scroll for viewers
        iListBoxFlags |= ELoopScrolling; // All lists will have loop scrolling.
        }
    if (aParent)
        SetContainerWindowL(*aParent);
    else
        {
        CreateWindowL(aParent);

        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            Window().SetRequiredDisplayMode( EColor16MA );
            TInt err = Window().SetTransparencyAlphaChannel();

            if ( err == KErrNone )
                {
                Window().SetBackgroundColor(~0);
                }
            }

        EnableDragEvents();
        Window().SetPointerGrab(ETrue);
        }
    if (iListBoxFlags & EPopout)
        {
        if (!LafListBox::FadeBehind())
            DrawableWindow()->EnableBackup();
        LafListBox::GetDefaultPopoutBorder(iBorder);
        }
    if (iListBoxFlags & EIncrementalMatching)
        CreateMatchBufferL();
    CreateViewL();
    
    if(iItemDrawer && (iItemDrawer->MinimumCellSize().iHeight != 0))
        iItemHeight = iItemDrawer->MinimumCellSize().iHeight;

    if ( iListBoxExt->iLongTapDetector
            && iListBoxFlags & EDisableItemSpecificMenu )
        {
        delete iListBoxExt->iLongTapDetector;
        iListBoxExt->iLongTapDetector = NULL;
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent,TInt aFlags)
    {
    _AKNTRACE_FUNC_ENTER;
    __ASSERT_DEBUG(aListBoxModel!=NULL,Panic(EEikPanicListBoxInvalidModelSpecified));
    __ASSERT_DEBUG(aListItemDrawer!=NULL,Panic(EEikPanicListBoxInvalidItemDrawerSpecified));
    iModel = aListBoxModel;
    iItemDrawer = aListItemDrawer;
    ConstructL(aParent,aFlags);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aListItemDrawer, const CCoeControl* aParent, TGulBorder aBorder, TInt aFlags)
    {
    _AKNTRACE_FUNC_ENTER;
    iBorder = aBorder;
    CEikListBox::ConstructL(aListBoxModel, aListItemDrawer, aParent, aFlags);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SetListBoxObserver(MEikListBoxObserver* aObserver)
    {
    iListBoxObserver = aObserver;
    }

EXPORT_C void CEikListBox::SetContainerWindowL(const CCoeControl& aParent)
    {
    _AKNTRACE_FUNC_ENTER;
    if ((iListBoxFlags & ECreateOwnWindow) || (iListBoxFlags & EPopout))
        {
        CreateWindowL(&aParent);
        if (iListBoxFlags & EPopout)
            DrawableWindow()->EnableBackup();
        }
    else
        CCoeControl::SetContainerWindowL(aParent);
    EnableDragEvents();
    Window().SetPointerGrab(ETrue);
    
    if ( iListBoxExt && iListBoxExt->iPhysics )
        {
        iListBoxExt->iPhysics->UpdateViewWindowControl();
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CListBoxView* CEikListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CListBoxView);
    }

EXPORT_C void CEikListBox::CreateViewL()
    {
    _AKNTRACE_FUNC_ENTER;
    // assert that the model and item drawer aren't null
    if (iView)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    iView = MakeViewClassInstanceL();
    iView->ConstructL(iModel, iItemDrawer, iEikonEnv->ScreenDevice(), &(iEikonEnv->RootWin()), &Window(), Rect(), iItemHeight);
    iView->iExtension->iListBox = this;    

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    // LISTBOX EFFECTS IMPLEMENTATION
    //
    // Creates a CTfxGc and replaces the original CWindowGc with that gc.
    //
    CWindowGc* transGc = CAknListLoader::CreateTfxGc( *this );
    if( transGc )
        {
        iView->iGc = transGc;
        iView->ItemDrawer()->SetGc(transGc);
        }
    // END OF LISTBOX EFFECTS IMPLEMENTATION
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if (iListBoxFlags & EIncrementalMatching)
        {
        iView->SetMatcherCursor(ETrue);
        if(IsDimmed())
            iView->SetMatcherCursorColor(EColorControlHighlightBackground);
        else
            iView->SetMatcherCursorColor(EColorControlDimmedHighlightBackground);
        }
    iItemDrawer->SetVerticalInterItemGap(KEikListBoxItemVGap);
    if (iListBoxFlags & EMultipleSelection) iItemDrawer->SetDrawMark(ETrue);
    if (ItemExists(0))
        SetCurrentItemIndex(0);
    CheckCreateExtensionL();
    
    if ( iListBoxExt && iListBoxExt->iPhysics )
        {
        iView->iExtension->iScrollingDisabled = EFalse;
        }
    
    iView->SetVisibilityObserver(iListBoxExt);
    if ( iListBoxFlags & EPaintedSelection )
        {
        iView->SetPaintedSelection( ETrue );
        iItemDrawer->SetDrawMark( EFalse );
        iItemDrawer->SetFlags( CListItemDrawer::EPaintedSelection );
        }
    if (iListBoxFlags & EDisableHighlight)
    {
    iItemDrawer->SetFlags( CListItemDrawer::EDisableHighlight );
    }

    if ( iListBoxExt && iListBoxExt->iSingleClickEnabled )
        {
        iListBoxExt->EnableHighlight( EFalse );
        iListBoxExt->ReportCollectionChangedEvent();
        }    
        
    UpdateViewColors();
    UpdateItemDrawerColors();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::DrawMatcherCursor() const
    {
    if (!IsMatchBuffer())
        return;
    TInt currentItemIndex = iView->CurrentItemIndex();
    if (ItemExists(currentItemIndex)) 
        {
        if (! iView->ItemIsVisible(currentItemIndex))
            ScrollToMakeItemVisible(currentItemIndex);
        iView->DrawMatcherCursor();
        }
    }

EXPORT_C TInt CEikListBox::InterItemGap()
    { // static
    return KEikListBoxInterItemGap;
    }


EXPORT_C void CEikListBox::DrawItem( TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !IsReadyToDraw() )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    __ASSERT_ALWAYS( iView, Panic( EEikPanicListBoxNoView ) );
    
    TBool viewScrolled = EFalse;
    if ( iView->ItemIsPartiallyVisible( aItemIndex ) ||
         !iView->ItemIsVisible( aItemIndex ) )
        {
        viewScrolled = iView->ScrollToMakeItemVisible( aItemIndex );
        }

    if ( !viewScrolled )
        {
        iView->DrawItem( aItemIndex );
        }
    else
        {
        UpdateScrollBarThumbs();
        }
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CEikListBox::ScrollToMakeItemVisible(TInt aItemIndex) const 
    {
    _AKNTRACE_FUNC_ENTER;
    __ASSERT_ALWAYS(iView, Panic(EEikPanicListBoxNoView));
    TBool scrollingTookPlace = iView->ScrollToMakeItemVisible(aItemIndex);
    if (scrollingTookPlace)
        UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::RedrawItem( TInt aItemIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    if (!IsReadyToDraw())
        {
        _AKNTRACE_FUNC_EXIT;        
        return;
        }
    __ASSERT_ALWAYS(iView, Panic(EEikPanicListBoxNoView));
    if ( iView->ItemIsVisible( aItemIndex ) )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );

        TBool redraw = !IsBackedUp() && ( transApi == NULL || transApi->EffectsDisabled() );
#else
        TBool redraw = !IsBackedUp();
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        if ( redraw )
            {
            TRect redrawRect( 
                iView->ItemPos( aItemIndex ), 
                iItemDrawer->ItemCellSize() );
            redrawRect.Intersection( iView->ViewRect() );

            Window().Invalidate( redrawRect );
            Window().BeginRedraw( redrawRect );
            }

        iView->DrawItem( aItemIndex );

        if ( redraw )
            {
            Window().EndRedraw();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::ActivateL()
    {
    _AKNTRACE_FUNC_ENTER;
    CCoeControl::ActivateL();
    UpdateScrollBarThumbs();

    CEikButtonGroupContainer *cba;
    MopGetObject(cba);
    
    if (!cba) 
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    if (iListBoxFlags & EEnterMarks)
        {
        // Unfortunately, we need to do this here. It belongs to 
        // CAknSelectionListDialog, but we need this change also 
        // to code that does not yet use CAknSelectionListDialog.
        TRAP_IGNORE(iAvkonEnv->CreateCbaObserverL(cba, this));
        }
    if ( iListBoxExt && iListBoxExt->iMSKObserverEnabled &&
        ( (iListBoxFlags & EShiftEnterMarks) ||
          (iListBoxFlags & EEnterMarks) ) )
        {
        TRAP_IGNORE(iListBoxExt->CreateMSKObserverL(cba, this));
        TRAP_IGNORE(UpdateMarkUnmarkMSKL());
        }
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CEikListBox::Draw(const TRect& aRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    // If a parent has a custom gc, draw listbox using that gc
    CWindowGc* replacedGc = ReplaceGcWithCustomGc( this );
    
    CWindowGc* gc = iItemDrawer->Gc();
    TGulBorder::TColors borderColors;
    iBorder.Draw(*gc, Rect(), borderColors);

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
    if ( transApi )
        {
        transApi->BeginRedraw( MAknListBoxTfxInternal::EListView, View()->ViewRect() );
        transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST


    ClearMargins(); 
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    iView->Draw(&aRect);

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->EndViewRedraw( aRect );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if ( replacedGc )
        {
        // Stop using the custom gc
        iItemDrawer->SetGc( replacedGc );
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::ClearMargins() const
    {
     if (!iView->RedrawDisabled())
         {
         CWindowGc* gc = iItemDrawer->Gc();
         if (gc)
     {
     TRect viewRect=iView->ViewRect();
     TRect clientRect;
     RestoreClientRectFromViewRect(clientRect);
             gc->SetBrushColor(iBackColor);
             DrawUtils::ClearBetweenRects(*gc, clientRect, viewRect);
             }
         }
    }

EXPORT_C void CEikListBox::UpdateScrollBarsL()
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iSBFrame)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;
    TRect rect=iView->ViewRect();
//#ifdef NOT_NEEDED_IN_SERIES60
    if (!(iListBoxFlags & EScrollBarSizeExcluded))
        {
        // Ignore scrollbars presence to set the model, Scrollbar Frame will change it as required
        rect = iBorder.InnerRect(Rect());
        rect.SetRect(rect.iTl.iX + ListBoxMargins().iLeft, rect.iTl.iY + ListBoxMargins().iTop,
            rect.iBr.iX - ListBoxMargins().iRight, rect.iBr.iY - ListBoxMargins().iBottom);
        AdjustRectHeightToWholeNumberOfItems(rect);
        // rect is now viewRect when ignoring scrollbars
        }
//#endif
    TInt itemHeight = iView->ItemHeight();
    TSize viewSize( iView->ViewRect().Size() );
    
    if (iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
        {
        if (!(iListBoxFlags & EPageAtOnceScrolling))
            {
            if (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
                {
                // For EDoubleSpan type scrollbar
				vSbarModel.iThumbPosition = iView->TopItemIndex()*iView->ItemHeight() - iView->ItemOffsetInPixels();
                }
            else
                {
                // For EArrowHead type scrollbar
                vSbarModel.iThumbPosition = iView->CurrentItemIndex();
                }
            vSbarModel.iScrollSpan = iModel->NumberOfItems()*iView->ItemHeight();
           }
        else
            { // Viewer
			vSbarModel.iThumbPosition = iView->TopItemIndex()*iView->ItemHeight() - iView->ItemOffsetInPixels();
			vSbarModel.iScrollSpan = iModel->NumberOfItems()*iView->ItemHeight();
            }
        if ( vSbarModel.iScrollSpan == viewSize.iHeight )
            {
            vSbarModel.iThumbSpan = viewSize.iHeight;
            }
        else
            {
            vSbarModel.iThumbSpan = viewSize.iHeight - viewSize.iHeight % 2;            
            }
//#ifdef NOT_NEEDED_IN_SERIES60
        if ( IsActivated() )
            {            
            if (vSbarModel.iScrollSpan-vSbarModel.iThumbPosition<vSbarModel.iThumbSpan)
                {
                vSbarModel.iThumbPosition=Max(0,vSbarModel.iScrollSpan-vSbarModel.iThumbSpan);
                // This call causes redraw that should not be done in SizeChanged phase.
                iView->ScrollToMakeItemVisible(vSbarModel.iThumbPosition/iView->ItemHeight()); // force a scroll if neccessary
                }
            }
//#endif
        }
    if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
        {
        iView->CalcDataWidth();
        hSbarModel.iThumbPosition = iView->HScrollOffset();
        hSbarModel.iScrollSpan = iView->DataWidth();
        hSbarModel.iThumbSpan = iView->VisibleWidth(rect);
        }

    if (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        // For EDoubleSpan type scrollbar        
        TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
        TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );
              
        TRect clientRect = Rect();      
        TRect inclusiveRect = Rect();
        TEikScrollBarFrameLayout layout;
        layout.iTilingMode=TEikScrollBarFrameLayout::EInclusiveRectConstant;
        layout.SetClientMargin(0);
        layout.SetInclusiveMargin(0);
        if(iSBFrameOwned == EOwnedExternally)
            iSBFrame->Tile(&hDsSbarModel, &vDsSbarModel);
        else
            {
            TBool sizeChanged=EFalse;
            sizeChanged=iSBFrame->TileL(&hDsSbarModel, &vDsSbarModel, clientRect, inclusiveRect, layout);
            if (sizeChanged)
                {               
                iSBFrame->DrawScrollBarsDeferred();
                }
            }
        }
    else
        {
        // For EArrowHead type scrollbar
        TRect clientRect;
        RestoreClientRectFromViewRect(clientRect);
        TRect inclusiveRect=Rect();
        TEikScrollBarFrameLayout layout;
        CreateScrollBarFrameLayout(layout);
        TBool sizeChanged=iSBFrame->TileL(&hSbarModel, &vSbarModel, clientRect, inclusiveRect, layout);
        if (iListBoxExt->UpdateScrollBarsColors())
            UpdateScrollBarsColors();
        if (!sizeChanged)
            return;
        // else size of client/inclusive rect has changed
        if (layout.iTilingMode==TEikScrollBarFrameLayout::EClientRectConstant)
            SetSizeWithoutNotification(inclusiveRect.Size());
        else
            {
            SetViewRectFromClientRect(clientRect);
            ClearMargins();
            }        
        }
    
    if ( iListBoxExt )
        {    
        iListBoxExt->CheckScrollBarVisibility();
        }
    
    AdjustTopItemIndex();
    _AKNTRACE_FUNC_EXIT;
    }
                                                            
EXPORT_C void CEikListBox::CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout)    const
    {
    _AKNTRACE_FUNC_ENTER;
    aLayout.iInclusiveMargin=iBorder.Margins();

    aLayout.iClientMargin.iTop=ListBoxMargins().iTop;
    aLayout.iClientMargin.iBottom=ListBoxMargins().iBottom;
    aLayout.iClientMargin.iLeft=ListBoxMargins().iLeft;
    aLayout.iClientMargin.iRight=ListBoxMargins().iRight;

    aLayout.iClientAreaGranularity=TSize(HorizScrollGranularityInPixels(), iItemHeight); 
    aLayout.iTilingMode=(!(iListBoxFlags & EScrollBarSizeExcluded))? TEikScrollBarFrameLayout::EInclusiveRectConstant : TEikScrollBarFrameLayout::EClientRectConstant;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::HorizScrollGranularityInPixels() const
    {
    return 1; // horiz scroll bar model set in pixels for standard listbox
    }

EXPORT_C void CEikListBox::Reset()
    {
    _AKNTRACE_FUNC_ENTER;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
    if ( transApi )
        {
        transApi->Remove( MAknListBoxTfxInternal:: EListEverything );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    ((CListBoxView::CSelectionIndexArray*)iView->SelectionIndexes())->Reset();
    iView->SetTopItemIndex(0);
    iView->SetCurrentItemIndex(0);
    iView->ClearSelectionAnchorAndActiveIndex();
    iView->SetHScrollOffset(0);

    FireItemChange();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::AddItemChangeObserverL(
        MListBoxItemChangeObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    if( !aObserver )
        {
        User::Leave( KErrArgument );
        }

    CheckCreateExtensionL();
    iListBoxExt->AddItemChangeObserverL( aObserver );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TBool CEikListBox::RemoveItemChangeObserver(
        MListBoxItemChangeObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    if( !iListBoxExt )
        {
        _AKNTRACE_FUNC_EXIT;
        return EFalse;
        }
    _AKNTRACE_FUNC_EXIT;
    return iListBoxExt->RemoveItemChangeObserver( aObserver );
    }

EXPORT_C void CEikListBox::AddSelectionObserverL( MListBoxSelectionObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    if( !aObserver )
        {
        User::Leave( KErrArgument );
        }

    CheckCreateExtensionL();
    iListBoxExt->AddSelectionObserverL( aObserver );
    _AKNTRACE_FUNC_EXIT;
    }
    
EXPORT_C void CEikListBox::RemoveSelectionObserver( MListBoxSelectionObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    if( iListBoxExt )
        {
        iListBoxExt->RemoveSelectionObserver( aObserver );
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CEikListBox::ChangeSelectionMode( TBool aEnable )
    // Nonexported helper function.
    {
    _AKNTRACE_FUNC_ENTER;
    // UI Spec does not mention this, but it is reasonable not to
    // change selection mode on unmarkable item.
    TInt index = CurrentItemIndex();
    if ( index >= 0 && aEnable 
         && iItemDrawer->Properties(index).IsSelectionHidden() )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    if( !iListBoxExt )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    CEikButtonGroupContainer *bgc;
    CCoeControl* MSK( NULL );
    CEikCba* cba( NULL );
    CONST_CAST( CEikListBox*,this )->MopGetObject( bgc );
    if ( !bgc )
        {
        _AKNTRACE_FUNC_EXIT;
        return; // No bgc -> no cba -> nothing can be done here (and no need to inform observers)
        }
        
    cba = ( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup

    if ( !cba )
        {
        _AKNTRACE_FUNC_EXIT;
        return; // No cba -> nothing can be done here (and no need to inform observers)
        }

    MSK = cba->Control( 3 ); // MSK's position is 3

    TInt newResourceId( NULL );
    if ( MSK && View()->ItemIsSelected( CurrentItemIndex() ) )
        {
        newResourceId = R_AVKON_SOFTKEY_UNMARK;
        }
    if ( MSK && !View()->ItemIsSelected( CurrentItemIndex() ) )
        {
        newResourceId = R_AVKON_SOFTKEY_MARK;
        }

    if ( aEnable && newResourceId )
        {
        TRAPD( err, bgc->AddCommandToStackL( 3, newResourceId ) );
        // in case of error, don't inform observers
        // marking still works even MSK isn't changed
        if ( err )
            {
            iListBoxExt->iSelectionModeEnabled = EFalse;
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        cba->DrawNow();
        iListBoxExt->iSelectionModeEnabled = ETrue;
        }

    // remove stacked MSK
    if( !aEnable && iListBoxExt->iSelectionModeEnabled )
        {
        if( ( MSK && cba->ControlId( MSK ) == EAknSoftkeyMark ) ||
            ( MSK && cba->ControlId( MSK ) == EAknSoftkeyUnmark ) )
            {
            bgc->RemoveCommandFromStack( 3, cba->ControlId( MSK ) );
            }
        iListBoxExt->iSelectionModeEnabled = EFalse; // just in case
        }
        
    TInt count = iListBoxExt->iSelectionObservers.Count();
    for ( int i=0; i < count; i++ )
        {
        iListBoxExt->iSelectionObservers[i]->SelectionModeChanged( this, aEnable );
        }
    _AKNTRACE_FUNC_EXIT;
    }


void CEikListBox::HandleItemRemovalWithoutSelectionsL()
    // Nonexported helper function.
    {
    _AKNTRACE_FUNC_ENTER;
    // this will force update of physics parameters next time when list is panned
    iView->SetItemOffsetInPixels( 0 );
    iView->SetFlags(CListBoxView::EItemCountModified);
    iView->CalcDataWidth();
    iView->CalcBottomItemIndex();
    UpdateScrollBarsL();
    UpdateScrollBarThumbs();
    iView->ClearFlags(CListBoxView::EItemCountModified);

    FireItemChange();
    
    if ( iListBoxExt && iListBoxExt->iPhysics )
        {
        iListBoxExt->InitPhysicsL();
        }    
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::HandleItemRemovalL(CArrayFix<TInt> &aArrayOfOldIndexes)
    // NOTE, This algorithm cannot handle position of the list highlight
    // nor can it update the topitemindex correctly.
    {
    _AKNTRACE_FUNC_ENTER;
    TKeyArrayFix key(0,ECmpTInt);
    aArrayOfOldIndexes.Sort(key);

    // remove removed items from selection index array
    TInt changedcount = aArrayOfOldIndexes.Count();
    for(TInt iii=0;iii<changedcount;iii++)
        {
        iView->DeselectItem(aArrayOfOldIndexes.At(iii));
        }

    // decrease selectionindexes. Does not change their order, so resorting
    // the array is not necessary
    CListBoxView::CSelectionIndexArray* array = CONST_CAST(CListBoxView::CSelectionIndexArray*,iView->SelectionIndexes());
    TInt selectioncount = array->Count();
    TInt removedcount = aArrayOfOldIndexes.Count();
    for(TInt ii = 0;ii<removedcount;ii++)
        {
        for(TInt i=0;i<selectioncount;i++)
            {
            // since we deselected the item, its not possible that
            // the removed item is still in selectionindexes array.
            __ASSERT_DEBUG(array->At(i) != aArrayOfOldIndexes.At(ii), Panic(EEikPanicOutOfRange));
            if (array->At(i) > aArrayOfOldIndexes.At(ii))
                {
                (*array)[i]-=1;
                }
            }
        }
 
    HandleItemRemovalWithoutSelectionsL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::HandleItemAdditionL(CArrayFix<TInt> &aArrayOfNewIndexesAfterAddition)
    // NOTE, This algorithm cannot handle position of the list highlight
    // nor can it update the topitemindex correctly.
    {
    _AKNTRACE_FUNC_ENTER;
    // Updates selectionindexes array

    // Sort indexes first
    TKeyArrayFix key(0,ECmpTInt);
    aArrayOfNewIndexesAfterAddition.Sort(key);
    
    // increase selectionindexes.
    CListBoxView::CSelectionIndexArray* array = CONST_CAST(CListBoxView::CSelectionIndexArray*,iView->SelectionIndexes());
    TInt selectioncount = array->Count();
    TInt newindexcount = aArrayOfNewIndexesAfterAddition.Count();
    for(TInt ii = 0;ii<newindexcount;ii++)
        {
        for(TInt i=0;i<selectioncount;i++)
            {
            if (array->At(i) >= aArrayOfNewIndexesAfterAddition.At(ii))
                {
                (*array)[i]+=1;
                }
            }
        }

    // other features that does not depend on the items added.
    HandleItemAdditionL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::HandleItemAdditionL()
    {
    _AKNTRACE_FUNC_ENTER;
     //fix the bug EGGO-7SQA4S and EVSG-7TD9WZ 
    TInt curItemIndex = iView->CurrentItemIndex();
    if(curItemIndex >= 0 && curItemIndex < iModel->NumberOfItems() )
      {
      TInt newTopItemIndex = iView->CalcNewTopItemIndexSoItemIsVisible( curItemIndex );
      iView->SetTopItemIndex( newTopItemIndex );
      }
    iView->SetFlags(CListBoxView::EItemCountModified);
    // following breaks lists in square layout, not needed in SERIES60?
    //iView->CalcDataWidth();
    iView->CalcBottomItemIndex();
    UpdateScrollBarsL();
    UpdateScrollBarThumbs();
    if (IsReadyToDraw()) DrawDeferred();
    iView->ClearFlags(CListBoxView::EItemCountModified);

    FireItemChange();
    
    if ( iListBoxExt )
        {    
        iListBoxExt->CheckScrollBarVisibility();
        // Physics engine world size needs to be updated here, otherwise aknphysics 
        // cone observer may block pointer events on new items. this can happen 
        // when item addition inserts new row to taskswapper's grid and reuses list in Common Dialog
        if ( iListBoxExt->iPhysics )
            {
            iListBoxExt->InitPhysicsL();
            }
        }     
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::HandleItemRemovalL()
    {
    // Should be called after one or more items have been removed from the model
    // It is up to the application to then make sure that the current item index is set to an appropriate value and to redraw the listbox
    _AKNTRACE_FUNC_ENTER;
    ((CListBoxView::CSelectionIndexArray*)iView->SelectionIndexes())->Reset();
    HandleItemRemovalWithoutSelectionsL();
    _AKNTRACE_FUNC_EXIT;
    // Please do not add anything here. Add them to the HandleItemRemovalWithoutSelectionsL().
    }

EXPORT_C const CArrayFix<TInt>* CEikListBox::SelectionIndexes() const
    {
    return iView->SelectionIndexes();
    }

EXPORT_C void CEikListBox::SetSelectionIndexesL(CListBoxView::CSelectionIndexArray* aArrayOfSelectionIndexes)
    {
    if (! aArrayOfSelectionIndexes)
        iView->ClearSelection();
    else
        iView->SetSelectionIndexesL(aArrayOfSelectionIndexes);
    }

void CEikListBox::HorizontalScroll(TInt aScrollAmountInPixels)
    {
    iView->HScroll(aScrollAmountInPixels);
    if (iSBFrame)
        {
        if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
            iSBFrame->MoveThumbsBy(aScrollAmountInPixels, 0);
        }
    }

EXPORT_C void CEikListBox::HandleLeftArrowKeyL(CListBoxView::TSelectionMode /*aSelectionMode*/)
    {
    HorizontalScroll(-(iView->ViewRect().Width() / KEikListBoxHNudgeSizeAsFractionOfViewRectWidth));
    }


EXPORT_C void CEikListBox::HandleRightArrowKeyL(CListBoxView::TSelectionMode /*aSelectionMode*/)
    {
    HorizontalScroll((iView->ViewRect().Width() / KEikListBoxHNudgeSizeAsFractionOfViewRectWidth));
    }
//#define KEY_DEBUG

#if defined(_DEBUG) && defined(KEY_DEBUG)
#define __KeyDebug(b,text) { _LIT(blah, "LbxKeys %d:%d:%c%c%c " ## L ## text); RDebug::Print(blah, aKeyEvent.iCode, aKeyEvent.iScanCode, shiftKeyPressed ? 's' : '_', enterKeyPressed ? 'e' : '_', aType == EEventKey ? 'K' : (aType == EEventKeyDown ? 'D' : (aType == EEventKeyUp ? 'U' : '_'))); }
#else
#define __KeyDebug(b,text)
#endif


EXPORT_C TKeyResponse CEikListBox::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    TKeyEvent keyEvent=aKeyEvent;
    keyEvent.iCode=LafListBox::MapKeyCode(aKeyEvent,aType);
    _AKNTRACE_FUNC_EXIT;
    return DoOfferKeyEventL(keyEvent,aType);
    }

TBool IsSelectionMarkKeys(TInt aCode, TInt aScanCode, TBool aWesternVariant)
    {
    return aCode == EKeyUpArrow   || 
           aCode == EKeyDownArrow ||
           aCode == EKeyOK        ||
        /* aCode == EKeyEnter     || */
           (aCode == 0 && aScanCode == EStdKeyLeftShift)  ||
           (aCode == 0 && aScanCode == EStdKeyRightShift) ||           
           (aCode == 0 && aScanCode == EStdKeyRightCtrl)  ||
           (!aWesternVariant && (aCode == 0 && aScanCode == EStdKeyHash));
    }

TKeyResponse CEikListBox::DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    TInt topItemIndex = iView->TopItemIndex();
    if (ItemExists(topItemIndex) == EFalse)
        {
        return (aKeyEvent.iScanCode == EStdKeyYes ? EKeyWasNotConsumed:EKeyWasConsumed);
        }
        
    TInt code = aKeyEvent.iCode;

    // With single click first key event enables highlight
    if ( iListBoxExt && iListBoxExt->EnableHighlightWithKeyEventL(
            topItemIndex, aKeyEvent, aType ) )
        {
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }
    
    (void)aType; // to prevent a warning.

    TBool shiftKeyPressed = (aKeyEvent.iModifiers & EModifierShift) ||
                            (aKeyEvent.iModifiers & EModifierLeftShift) ||
                            (aKeyEvent.iModifiers & EModifierRightShift);

    // Downpressed hash key already generates shift modifier and
    // in Chinese variant hash (shift) + movement/MSK should not mark
    if ( iListBoxExt &&
         iListBoxExt->iWesternVariant == EFalse &&
         iListBoxExt->iAknFepHashKeySelection )
        {
        shiftKeyPressed = EFalse;
        }

    TBool controlKeyPressed = (aKeyEvent.iModifiers & EModifierCtrl) || 
                              (aKeyEvent.iModifiers & EModifierRightCtrl);  
    TInt oldCurrentItemIndex = iView->CurrentItemIndex();
    
    TBool enterKeyPressed=EFalse;
    TBool escapeKeyPressed=EFalse;
    TBool sideBarKeyPressed=EFalse;
    TBool switchMSK=EFalse; // for mark/unmark in selection lists
    
    // if we have markable list and either shift, ctrl or hash is long pressed
    // down, we will enter selection (marking) mode, where MSK is Mark/Unmark
    if( iListBoxExt && (iListBoxFlags & EMultipleSelection) &&
        (iListBoxFlags & EShiftEnterMarks) &&
         aType == EEventKeyDown &&
         ( (iListBoxExt->iWesternVariant &&
            iListBoxExt->iAknFepHashKeySelection && 
            iListBoxExt->iQwertyMode == EFalse && 
            aKeyEvent.iScanCode == EStdKeyHash)  ||
         aKeyEvent.iScanCode == EStdKeyLeftShift ||
         aKeyEvent.iScanCode == EStdKeyRightShift ||
         aKeyEvent.iScanCode == EStdKeyLeftCtrl ||
         aKeyEvent.iScanCode == EStdKeyRightCtrl ) )
        {
        iListBoxExt->StartLongPressTimerL();
        iListBoxExt->iShortHashMark = ETrue;        
        iListBoxExt->iShiftKeyPressed = ETrue;        
        }

    if( iListBoxExt && (iListBoxFlags & EMultipleSelection) &&
        (iListBoxFlags & EShiftEnterMarks) &&
         aType == EEventKeyUp &&
         ( (iListBoxExt->iWesternVariant &&
            iListBoxExt->iAknFepHashKeySelection && 
            iListBoxExt->iQwertyMode == EFalse && 
            aKeyEvent.iScanCode == EStdKeyHash)  ||
         aKeyEvent.iScanCode == EStdKeyLeftShift ||
         aKeyEvent.iScanCode == EStdKeyRightShift ||
         aKeyEvent.iScanCode == EStdKeyLeftCtrl ||
         aKeyEvent.iScanCode == EStdKeyRightCtrl ) )
        {
        iListBoxExt->iShiftKeyPressed = EFalse;
        if ( iListBoxExt->iLongPressTimer &&
             iListBoxExt->iLongPressTimer->IsActive() )
            {
            iListBoxExt->iLongPressTimer->Cancel();
            }
        if( iListBoxExt->iSelectionModeEnabled )
            {
            ChangeSelectionMode( EFalse );
            iListBoxExt->iSelectionModeEnabled = EFalse;
            View()->ClearSelectionAnchorAndActiveIndex();
            }
        }


    // SERIES60 LAF
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
    if (iListBoxFlags & EMultipleSelection)
        {
        if ((shiftKeyPressed || controlKeyPressed) && iListBoxFlags & EShiftEnterMarks && aType == EEventKey)
            {
            __KeyDebug(ETrue, "shift + enter marks");
            View()->SetAnchor(View()->CurrentItemIndex());
            selectionMode = CListBoxView::EDisjointMarkSelection;
            }
        else
            {
            selectionMode = CListBoxView::ENoSelection;
            UpdateMarkUnmarkMSKL();
            if (IsSelectionMarkKeys(code, aKeyEvent.iScanCode, iListBoxExt->iWesternVariant)) 
                {
                __KeyDebug(ETrue, "SelectionMarkKey")
                View()->ClearSelectionAnchorAndActiveIndex();
                }
            }
        }


    // CAknGrid marking is implemeted in avkon.dll. But we still need to disable short
    // hash mark in here.
    if ( iListBoxFlags & EMultipleSelection && 
         iListBoxFlags & EShiftEnterMarks && aType == EEventKeyUp )
        {
        if ( aKeyEvent.iScanCode == EStdKeyLeftArrow ||
             aKeyEvent.iScanCode == EStdKeyUpArrow ||
             aKeyEvent.iScanCode == EStdKeyRightArrow ||
             aKeyEvent.iScanCode == EStdKeyDownArrow )
            {
            iListBoxExt->iShortHashMark = EFalse;
            }
        // for some applications this is the only way to catch marking with MSK
        if ( aKeyEvent.iScanCode == EStdKeyDevice3 )
            {
            iListBoxExt->iShortHashMark = EFalse;
            }
        }


    TInt oldMatcherCursorPos = iView->MatcherCursorPos();
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    // LISTBOX EFFECTS IMPLEMENTATION
    // 
    // Fetch internal listbox transition API.
    //
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    
    switch (code)
        {
        case EKeyPrevious:
            {
            _AKNTRACE( "EKeyPrevious" );
            const TBool disableRedraw = aKeyEvent.iRepeats;
            
            TBool redrawDisabled = iView->RedrawDisabled();
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(ETrue);
                }
            
            TInt count = 1 + aKeyEvent.iRepeats;
            TInt currentItemIndex = iView->CurrentItemIndex();
            if( ( currentItemIndex - count) < 0)
                {
                count = currentItemIndex;
                //  moveto = CListBoxView::ECursorLastItem;
                }
            if ( !count )
                {
                  count = 1;
                }  


            for ( TInt ii = 0; ii < count; ii++ )
                {
                CListBoxView::TCursorMovement moveto = CListBoxView::ECursorPreviousItem;
                if (iListBoxFlags & EPageAtOnceScrolling) 
                    { 
                    moveto = CListBoxView::ECursorPrevScreen; 
                    }

                TInt currentItemIndex = iView->CurrentItemIndex();
                if(!(iListBoxFlags & EPopout) && (currentItemIndex==0 || currentItemIndex==-1))
                    {
                    if (iListBoxFlags & ELoopScrolling)
                        {
                        moveto = CListBoxView::ECursorLastItem;
                        }
                    else
                        {
                        break;
                        }
                    }
                iView->MoveCursorL(moveto, selectionMode);
                ClearMatchBuffer();
                }

            if ( disableRedraw )
                {
                iView->SetDisableRedraw(redrawDisabled);
                if ( !redrawDisabled )
                    {
                    DrawNow();
                    }
                }
                
            if (iListBoxFlags & EMultipleSelection)
                {
                switchMSK = ETrue; // we need to check MSK later
                }
            }
            if(AknLayoutUtils::PenEnabled())
                {
                // update scroll bar thumbs here, because it is needed when scrolled.   
                UpdateScrollBarThumbs();
                }
            break;
        case EKeyNext:
            {
            _AKNTRACE( "EKeyNext" );
            const TBool disableRedraw = aKeyEvent.iRepeats;
            TBool redrawDisabled = iView->RedrawDisabled();
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(ETrue);
                }
            
            TInt count = 1 + aKeyEvent.iRepeats;
            TInt currentItemIndex = iView->CurrentItemIndex();
            if(currentItemIndex + count > Model()->NumberOfItems()-1 )
                {
                count = ( Model()->NumberOfItems() - 1 ) - currentItemIndex;
                }
            if ( !count )
                {
                  count = 1;
                }  

            
            for ( TInt ii = 0; ii < count; ii++ )
                {
                CListBoxView::TCursorMovement moveto = CListBoxView::ECursorNextItem;
                if (iListBoxFlags & EPageAtOnceScrolling) 
                    { 
                    moveto = CListBoxView::ECursorNextScreen; 
                    }
                
                TInt currentItemIndex = iView->CurrentItemIndex();
                if(!(iListBoxFlags & EPopout) && 
                    (currentItemIndex==Model()->NumberOfItems()-1 || currentItemIndex==-1))
                    {
                    if (iListBoxFlags & ELoopScrolling)
                        {
                        moveto = CListBoxView::ECursorFirstItem;
                        }
                    else
                        {
                        break;
                        }
                    }
                iView->MoveCursorL(moveto, selectionMode);
                ClearMatchBuffer();
                }

            if ( disableRedraw )
                {
                iView->SetDisableRedraw(redrawDisabled);
                if ( !redrawDisabled )
                    {
                    DrawNow();
                    }
                }
                
            if (iListBoxFlags & EMultipleSelection)
                {
                switchMSK = ETrue; // we need to check MSK later
                }
            }
            if(AknLayoutUtils::PenEnabled())
                {
                // update scroll bar thumbs here, because it is needed when scrolled.   
                UpdateScrollBarThumbs();
                }
            break;
        case EKeyApplicationF:
            // avkonenv can send these events to listbox.
            // CR PKEA-4YSASZ
            _AKNTRACE( "EKeyApplicationF" );
            if (SelectionIndexes()->Count()==0)
                {
                TInt currentItem = View()->CurrentItemIndex();
                if (currentItem >= 0)
                    {
                    View()->SelectItemL(currentItem);
                    }
                }
            _AKNTRACE_FUNC_EXIT;
            return EKeyWasConsumed;
        case EKeyUpArrow:
            {
            _AKNTRACE( "EKeyUpArrow" );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            // LISTBOX EFFECTS IMPLEMENTATION
            // 
            // Set type of momement
            //
            if ( transApi )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListMoveUp );
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

            // Note, in Series 60  we always eat uparrow and downarrow 
            // in lists, even though it does not really change list state.
            CListBoxView::TCursorMovement moveto = CListBoxView::ECursorPreviousItem;
            if (iListBoxFlags & EPageAtOnceScrolling) 
                { 
                moveto = CListBoxView::ECursorPrevScreen; 
                }
            if(!(iListBoxFlags & EPopout) && (oldCurrentItemIndex==0 || oldCurrentItemIndex==-1))
                {
                if (iListBoxFlags& ELoopScrolling)
                    {
                    moveto = CListBoxView::ECursorLastItem;
                    }
                else if ( ScrollingDisabled() && topItemIndex == 0 )
                    {
                    _AKNTRACE_FUNC_EXIT;
                    return( EKeyWasConsumed );
                    }
                }
		
            if ( ScrollingDisabled() || ( !iListBoxExt->MovePhysicsCursorL( moveto, selectionMode ) ) )
                {
                iView->MoveCursorL(moveto, selectionMode);
                }
            ClearMatchBuffer();
            if( iListBoxFlags & EMultipleSelection )
                {
                switchMSK = ETrue; // we need to check MSK later
                }
            }
            if( AknLayoutUtils::PenEnabled() )
                {
                // update scroll bar thumbs here, because it is needed when scrolled.   
                UpdateScrollBarThumbs();
                }
            break;
        case EKeyDownArrow:
            {
            _AKNTRACE( "EKeyDownArrow" );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            // LISTBOX EFFECTS IMPLEMENTATION
            // 
            // Set type of momement
            //
            if ( transApi )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListMoveDown );
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
            
            CListBoxView::TCursorMovement moveto = CListBoxView::ECursorNextItem;
            if (iListBoxFlags & EPageAtOnceScrolling)  
                { 
                moveto = CListBoxView::ECursorNextScreen; 
                }
            if(!(iListBoxFlags & EPopout) && 
                (oldCurrentItemIndex==Model()->NumberOfItems()-1 || oldCurrentItemIndex==-1))
                {
                if (iListBoxFlags & ELoopScrolling)
                    {
                    moveto = CListBoxView::ECursorFirstItem;
                    }
                else if ( ScrollingDisabled() && ( topItemIndex != 0 ) )
                    {
                    _AKNTRACE_FUNC_EXIT;
                    return(EKeyWasConsumed);    
                    }
                }

            if ( ScrollingDisabled() || ( !iListBoxExt->MovePhysicsCursorL( moveto, selectionMode ) ) )
                {
                iView->MoveCursorL(moveto, selectionMode);
                }
            ClearMatchBuffer();
            if (iListBoxFlags & EMultipleSelection)
                {
                switchMSK = ETrue; // we need to check MSK later
                }
            }
            if(AknLayoutUtils::PenEnabled())
                {
                // update scroll bar thumbs here, because it is needed when scrolled.   
                UpdateScrollBarThumbs();
                }
            break;
        case EKeyEnter:
        case EKeyOK:
            {
            _AKNTRACE( "EKeyEnter or EKeyOK" );
            if (aKeyEvent.iRepeats != 0) 
                {
                break;
                }
            // Series 60  case where ok or shift+ok is pressed
            if (iListBoxFlags & EMultipleSelection)
                {
                if ((shiftKeyPressed || controlKeyPressed) && iListBoxFlags & EShiftEnterMarks 
                    || iListBoxFlags & EEnterMarks)
                    {
                    __KeyDebug(ETrue, "shift+ok or ok in markable/multiselection");

                    iView->UpdateSelectionL(CListBoxView::EDisjointSelection);
                    iListBoxFlags |= EStateChanged;
                    switchMSK = ETrue;
                    break;
                    }
            
                // Markable list CR JLEO-4VQJ75
                if (!shiftKeyPressed && iListBoxFlags & EShiftEnterMarks)
                    { 
                    // enter key pressed on markable list without shift
                    if (SelectionIndexes()->Count() > 0)
                        { 
                        // when there's marked items, should open options menu.
                        __KeyDebug(ETrue, "ok without shift => ok options menu");

                        CEikMenuBar *bar;
                        MopGetObject(bar);
                        if (bar) 
                            {
                            bar->TryDisplayMenuBarL();
                            }
                        _AKNTRACE_FUNC_EXIT;
                        return EKeyWasConsumed;
                        }
                    }
                }

            // Series 60  ok key
            __KeyDebug(ETrue, "open item");
            enterKeyPressed = ETrue;
            }
            break;
        default:
            if (iListBoxFlags & EIncrementalMatching) 
                {
                if (TChar(aKeyEvent.iCode).IsPrint())
                    {
                    MatchTypedCharL(aKeyEvent.iCode);
                    }
                else
                    {
                    _AKNTRACE_FUNC_EXIT;
                    return (aKeyEvent.iScanCode == EStdKeyYes ? 
                        EKeyWasNotConsumed : EKeyWasConsumed);
                    }
                }
            break;
        }
    //
    // Switch/case ends here
    //
    if(switchMSK)
        {
        if( selectionMode == CListBoxView::EDisjointMarkSelection )
            {
             // if hash and either up or down pressed -> no short marking
            iListBoxExt->iShortHashMark = EFalse;
            }
        UpdateMarkUnmarkMSKL();
        }

    if(!AknLayoutUtils::PenEnabled())
        {
        // do update only when needed and in correct place. (prevents flicker). 
        // This place is called three times for every button event (down, key-event and up)     
        UpdateScrollBarThumbs();
        }

    if (oldCurrentItemIndex != iView->CurrentItemIndex())
        {
        iListBoxFlags |= EStateChanged;
        DrawMatcherCursor();
        }
    else if (oldMatcherCursorPos != iView->MatcherCursorPos() && IsMatchBuffer())
        {
        DrawMatcherCursor();
        }

    if (iListBoxFlags & EStateChanged)
        {
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        iListBoxFlags &= (~EStateChanged);
        }

    if (enterKeyPressed)
        {
        ReportListBoxEventL(MEikListBoxObserver::EEventEnterKeyPressed);
        if (iListBoxFlags & EPopout)
            {
            ReportEventL(MCoeControlObserver::EEventRequestExit);
            }
        }

    if (escapeKeyPressed || sideBarKeyPressed)
        {
        if (iListBoxFlags & EPopout)
            {
            ReportEventL(MCoeControlObserver::EEventRequestCancel);
            }
        }

    if (sideBarKeyPressed)
        {
        _AKNTRACE_FUNC_EXIT;
        return(EKeyWasNotConsumed);
        }
        
    // This code block watches for hash key presses, and simulates shift + ok 
    // if short hash key presses are used for selections. The events are simulated 
    // only if a markable list is active, otherwise the simulated event might open 
    // the selected item, which we don't want.    
    if((iListBoxFlags & EMultipleSelection) && (iListBoxFlags & EShiftEnterMarks) &&
        iListBoxExt->iWesternVariant &&
        iListBoxExt->iAknFepHashKeySelection && 
        iListBoxExt->iQwertyMode == EFalse && 
        aType == EEventKeyUp && aKeyEvent.iScanCode == EStdKeyHash &&
        IsFocused() )
        {
        if( iListBoxExt->iShortHashMark )
            {
            TKeyEvent keyEvent;
            keyEvent.iCode = EKeyDevice3;
            keyEvent.iScanCode = EStdKeyDevice3;
            keyEvent.iRepeats = 0;
            keyEvent.iModifiers = EModifierShift;             
            CCoeEnv::Static()->SimulateKeyEventL(keyEvent, EEventKey);
            }
        else
            {
            // some items has been un/marked with hash+up or down
            // so don't do short hash mark - just clear selection mode
            View()->ClearSelectionAnchorAndActiveIndex();
            }
        }
    
    if ( aKeyEvent.iScanCode == EStdKeyYes )
        {
        _AKNTRACE( "EStdKeyYes" );
        _AKNTRACE_FUNC_EXIT;
        return EKeyWasNotConsumed;
        }
    _AKNTRACE_FUNC_EXIT;    
    return(EKeyWasConsumed);
    }

void CEikListBox::UpdateMarkUnmarkMSKL() const
    {
    // for markable lists if MSK is either mark/unmark
    // and highlighted item has changed, try to switch
    // MSK according to item's selection state
    _AKNTRACE_FUNC_ENTER;
    CEikButtonGroupContainer *bgc;
    CCoeControl* MSK(NULL);
    CEikCba* cba(NULL);
    CONST_CAST(CEikListBox*,this)->MopGetObject(bgc);
    if ( bgc )
        {
        cba = ( static_cast<CEikCba*>( bgc->ButtonGroup() ) ); // downcast from MEikButtonGroup
        if ( cba )
            {
            MSK = cba->Control(3); // MSK's position is 3
            }
        }
    TInt newResourceId(NULL);
    if ( MSK && ( cba->ControlId( MSK ) == EAknSoftkeyMark ) &&
        View()->ItemIsSelected( CurrentItemIndex() ) )
        {
        newResourceId = R_AVKON_SOFTKEY_UNMARK;
        }
    if ( MSK && ( cba->ControlId( MSK ) == EAknSoftkeyUnmark ) &&
        !View()->ItemIsSelected( CurrentItemIndex() ) )
        {
        newResourceId = R_AVKON_SOFTKEY_MARK;
        }

    if ( newResourceId )
        {
        bgc->SetCommandL( 3,newResourceId );
        cba->DrawNow();
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::UpdateScrollBarThumbs() const
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iSBFrame)
        {
        _AKNTRACE_FUNC_EXIT;        
        return;
        }
    TInt hThumbPos=iView->HScrollOffset();
    TInt vThumbPos=iView->CurrentItemIndex();

    if ((iListBoxFlags & EPageAtOnceScrolling) || (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan))
        {
        TInt delta = iView->ItemHeight() + iView->ItemOffsetInPixels();
        vThumbPos = iView->TopItemIndex()*iView->ItemHeight() - iView->ItemOffsetInPixels();
        }

    iSBFrame->MoveHorizThumbTo(hThumbPos);
    iSBFrame->MoveVertThumbTo(vThumbPos);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::ReportListBoxEventL(MEikListBoxObserver::TListBoxEvent aEvent)
    {
    _AKNTRACE_FUNC_ENTER;
    switch ( aEvent )
        {
        case MEikListBoxObserver::EEventFlickStarted:
        case MEikListBoxObserver::EEventPanningStarted:
            {
            iItemDrawer->SetFlags( CListItemDrawer::EDisableMarquee );
            if ( aEvent == MEikListBoxObserver::EEventFlickStarted )
                iListBoxExt->SetFlickOngoing( ETrue );
            else            
                iListBoxExt->SetPanningOngoing( ETrue );
            break;
            }
            
        case MEikListBoxObserver::EEventFlickStopped:
        case MEikListBoxObserver::EEventPanningStopped:
            {
            iItemDrawer->ClearFlags( CListItemDrawer::EDisableMarquee );
            if ( aEvent == MEikListBoxObserver::EEventFlickStopped )
                {
                iListBoxExt->SetFlickOngoing( EFalse );
                }
            else 
                {
                iListBoxExt->SetPanningOngoing( EFalse );
                }
            
            break;
            }
        }
    
    if ( iListBoxObserver )
        {
        TBool allowed = ETrue;

        if ( iListBoxExt && iListBoxExt->iPhysics
             && aEvent != MEikListBoxObserver::EEventFlickStopped )
            {
            allowed = iListBoxExt->iClickEventsAllowed;
            }
        
        if ( allowed )
            {
            iListBoxObserver->HandleListBoxEventL(this, aEvent);
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CEikListBox::HorizontalNudgeValue() const
    {
    return (iView->ViewRect().Width() / KEikListBoxHNudgeSizeAsFractionOfViewRectWidth);
    }

EXPORT_C CEikScrollBarFrame* const CEikListBox::ScrollBarFrame()
    { 
    return iSBFrame;
    }

EXPORT_C void CEikListBox::SetScrollBarFrame(CEikScrollBarFrame* aScrollBarFrame, TScrollBarOwnerShip aOwnerShip)
    {
    if (iSBFrameOwned == ENotOwnedExternally) { delete iSBFrame; iSBFrame = 0; }
    iSBFrame = aScrollBarFrame; 
    iSBFrameOwned = aOwnerShip;
    }


// ---------------------------------------------------------------------------
// Scrolls the view by the given amount of pixels while keeping the
// physics parameters up-to-date.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::HandlePhysicsScrollEventL( TInt aDeltaPixels )
    {    
    _AKNTRACE_FUNC_ENTER;
    if ( iListBoxExt->iPhysics )
        {
        iListBoxExt->InitPhysicsL();
        
        TPoint newPosition( iListBoxExt->iViewPosition.iX,
                            aDeltaPixels + iListBoxExt->iViewPosition.iY );
        iListBoxExt->ViewPositionChanged( newPosition );
        }
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CEikListBox::HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType)
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iListBoxExt->iSingleClickEnabled )
        {
        iListBoxExt->EnableHighlight( EFalse );
        iView->DrawItem( iView->CurrentItemIndex() );
        }

    // When the scrollbar is scrolling, marquee will be disabled 
    // temporarily for performance reason. And before leaving this function,
    // this flag must be cleaned.
    iItemDrawer->SetFlags( CListItemDrawer::EDisableMarquee );

    TInt oldThumbPos = (aEventType & KEikScrollEventBarMask) ? iView->HScrollOffset() : iView->TopItemIndex();
    TInt newThumbPos = aScrollBar->ThumbPosition();
    
    TInt pageSize = 0;    
    TInt maxThumbPos = 0;
    
    if ( aScrollBar->Model()->ScrollBarModelType() == 
         TEikScrollBarModel::EAknDoubleSpanScrollBarModel )
        {
        const TAknDoubleSpanScrollBarModel* dblSpanModel = 
            static_cast<const TAknDoubleSpanScrollBarModel*>( 
                aScrollBar->Model() );
        pageSize = dblSpanModel->WindowSize();
        maxThumbPos = dblSpanModel->ScrollSpan() - 
            dblSpanModel->WindowSize();
        }
    else
        {
        pageSize = aScrollBar->Model()->iThumbSpan;
        maxThumbPos = aScrollBar->Model()->MaxThumbPos();
        }  
    
    TBool update = ETrue; // for the case EEikScrollThumbRelease so that after it there is now update.
    TInt newThumbPosBeforeCorrecting = newThumbPos;

    switch (aEventType & KEikScrollEventBarMask)
        { 
    case KEikScrollEventFromHBar:
        switch (aEventType)
            {
        case EEikScrollLeft:
            newThumbPos -= HorizontalNudgeValue();
            break;
        case EEikScrollRight:
            newThumbPos += HorizontalNudgeValue();
            break;
        case EEikScrollPageLeft:
            newThumbPos -= pageSize;
            break;
        case EEikScrollPageRight:
            newThumbPos += pageSize;
            break;
        case EEikScrollThumbDragHoriz:
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SuspendEffects( ETrue );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            if(AknLayoutUtils::PenEnabled())
                {
                break;
                }
        case EEikScrollThumbReleaseHoriz:
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SuspendEffects( EFalse );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            // in the case of drag events, the scrollbar automatically updates its thumb pos...
            if(AknLayoutUtils::PenEnabled())
                {
                update = EFalse;            
                }
            break;
        default:
            break;
            }
        newThumbPos = Max(0, Min(newThumbPos, maxThumbPos));
        iView->HScroll(newThumbPos - oldThumbPos);
        if (aEventType != EEikScrollThumbDragHoriz)
            aScrollBar->SetModelThumbPosition(iView->HScrollOffset());
        break;
        
    case KEikScrollEventFromVBar:
        switch (aEventType)
            {
        case EEikScrollUp:
                if ( oldThumbPos == 0  && (iListBoxFlags & ELoopScrolling))
                    {
                    newThumbPos = maxThumbPos;              
                    }
            break;
                
        case EEikScrollDown:
                if ( oldThumbPos == maxThumbPos && (iListBoxFlags & ELoopScrolling) )
                    {
                    newThumbPos = 0;                
                    }
            break;
                
        case EEikScrollPageUp:
            break;
                
        case EEikScrollPageDown:
            break;
                
        case EEikScrollThumbDragVert:
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SuspendEffects( ETrue );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            if(AknLayoutUtils::PenEnabled())
                {
                break;
                }
        case EEikScrollThumbReleaseVert:
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SuspendEffects( EFalse );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            // in the case of drag events, the scrollbar automatically updates its thumb pos...
            if(AknLayoutUtils::PenEnabled())
                {
                update = EFalse;            
                }
            break;
                
        default:
            break;
            }           
            
        newThumbPos = Max(0, Min(newThumbPos, maxThumbPos));
        
        if ( (!AknLayoutUtils::PenEnabled()) || update )
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal(
                                                                    iView->iGc );
            TBool effects = transApi && !transApi->EffectsDisabled();

            if ( effects )
                {
                transApi->SetMoveType( newThumbPos < oldThumbPos ?
                                       MAknListBoxTfxInternal::EListScrollUp :
                                       MAknListBoxTfxInternal::EListScrollDown );
                }
#endif
            
        if ( iListBoxExt->iPhysics )
            {
            iListBoxExt->InitPhysicsL();
            TInt deltaPixels = newThumbPos;
    
#ifdef _DEBUG
            RDebug::Print( _L( "CListBox::HandleScrollEventL, deltaPixels = %d" ), deltaPixels );
#endif // _DEBUG
            
            TPoint newPosition( iListBoxExt->iViewPosition.iX, deltaPixels + iView->ViewRect().Height() / 2 );
            iListBoxExt->ViewPositionChanged( newPosition );
            }
        else
            {
            iView->VScrollTo(newThumbPos/iView->ItemHeight());
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( effects )
                {
                transApi->Draw( Rect() );
                }
#endif
            if (aEventType != EEikScrollThumbDragVert)
                {               
                aScrollBar->SetModelThumbPosition(iView->TopItemIndex()*iView->ItemHeight() - iView->ItemOffsetInPixels());
                }
            }
        
        // If the event has changed thumb position, then update scroll bar
        // unless physics is used. In that case thumb is updated via 
        // CEikListBox::ScrollView.
        if ( AknLayoutUtils::PenEnabled() && newThumbPos != newThumbPosBeforeCorrecting && !iListBoxExt->iPhysics )
            {
            UpdateScrollBarThumbs();
            }
        }
    iItemDrawer->ClearFlags(CListItemDrawer::EDisableMarquee);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::HandleDragEventL(TPoint aPointerPos)
    {
    // return immediately if kinetic scrolling is enabled, this needs to be modified afterwards
    _AKNTRACE_FUNC_ENTER;
    if ( iListBoxExt && iListBoxExt->iPhysics )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    CheckCreateExtensionL();
    if (!(iListBoxFlags & ELeftDownInViewRect))
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    
    TRect viewRect(iView->ViewRect());
    if( !AknLayoutUtils::PenEnabled() )
        {
        // We do not want highlight to move when dragged left/rightside of lists
        if ((aPointerPos.iX > viewRect.iBr.iX) || (aPointerPos.iX < viewRect.iTl.iX))
            {
            aPointerPos.iX = viewRect.iTl.iX;
            }
        }
    TInt itemIndex( 0 );
    TBool pointerIsOverAnItem = iView->XYPosToItemIndex(aPointerPos, itemIndex);
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
    TInt oldCurrentItemIndex = iView->CurrentItemIndex();
    TInt oldTopItemIndex = iView->TopItemIndex();
    TInt oldBottomItemIndex = iView->BottomItemIndex();
    TInt topItemIndex ( oldTopItemIndex );
    TInt bottomItemIndex( oldBottomItemIndex );
    TInt interval = iListBoxExt->iInterval;
    TInt speed = 0;
    const TInt KBrakeL1 = 5;
    const TInt KBrakeL2 = 10;
    TInt lastItem = iModel->NumberOfItems() - 1;
    TInt yDistance = aPointerPos.iY - iListBoxExt->iLastPoint.iY;
    if(pointerIsOverAnItem && (itemIndex == oldBottomItemIndex) && yDistance > 0 )
        {
        speed = 1;
        }
    else if(pointerIsOverAnItem && (itemIndex == oldTopItemIndex) && yDistance < 0 )
        {
        speed = -1;
        }
    else if( pointerIsOverAnItem && 
             oldTopItemIndex < itemIndex && 
             oldBottomItemIndex > itemIndex )
        {
        // highlight the item
        speed = 0;    
        }
    else if (aPointerPos.iY < viewRect.iTl.iY)
        {
        speed = - Min((( viewRect.iTl.iY + ItemHeight()) - aPointerPos.iY ) 
                                    / ( ItemHeight() / 2 ) * iListBoxExt->iStepSpeed, 
                                    iListBoxExt->iMaxSpeed );
        if ( oldTopItemIndex <= KBrakeL1 )
        {
            speed = -1;
        }
        else if ( oldTopItemIndex + speed < KBrakeL1)
        {
            speed = KBrakeL1 - oldTopItemIndex;
            }
        }
    else if (aPointerPos.iY > viewRect.iBr.iY)
                {
        speed = Min(( aPointerPos.iY - ( viewRect.iBr.iY - ItemHeight())) 
                                  / (ItemHeight() / 2) * iListBoxExt->iStepSpeed, 
                                  iListBoxExt->iMaxSpeed );
        if ( oldBottomItemIndex >= iModel->NumberOfItems() - 1 - KBrakeL1 )
                    {
            speed = 1;
                }
        else if ( oldBottomItemIndex + speed > lastItem - KBrakeL1 )
            {
            speed = lastItem - oldBottomItemIndex - KBrakeL1;
            }
        }
    // Brake level 2
    if ( ( speed < 0 && oldTopItemIndex + speed < KBrakeL2 )
         || ( speed > 0 && oldBottomItemIndex + speed > lastItem - KBrakeL2 ))
        {
        interval *= 2;        
        }
            
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal(
                                                                iView->iGc );
    TBool effects = transApi && !transApi->EffectsDisabled();
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
    TBool edge = EFalse;
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    if ( !ItemExists( oldTopItemIndex + speed ) ||
         !ItemExists( oldBottomItemIndex + speed))
        {
        speed = 0;
        }
    iListBoxExt->iSpeed = speed;
    if ( speed != 0 )
        {
        topItemIndex = oldTopItemIndex + speed;
        
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( !effects )
            {
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        iView->SetTopItemIndex( topItemIndex );
        UpdateScrollBarThumbs();
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        if ( pointerIsOverAnItem ) 
            {
            Window().RequestPointerRepeatEvent(interval, 
                                               viewRect );
            }
        // Pointer outside of list
        else
            {
            TRect screenRect(TPoint(-1000, -1000), TPoint(1000, 1000));
            TRect ignoreDragRect;
            
            if ( AknLayoutUtils::PenEnabled() &&
            ( (aPointerPos.iY < viewRect.iTl.iY) || (aPointerPos.iY > viewRect.iBr.iY) ) && 
            !( (aPointerPos.iX > viewRect.iBr.iX) || (aPointerPos.iX < viewRect.iTl.iX) ) ) 
                {
                if (aPointerPos.iY < viewRect.iTl.iY)
                    {
                    ignoreDragRect.SetRect( screenRect.iTl, 
                                            TPoint(screenRect.iBr.iX, viewRect.iTl.iY ));
                    }
                else
                    {
                    ignoreDragRect.SetRect( TPoint( screenRect.iTl.iX, viewRect.iBr.iY), 
                                            screenRect.iBr );
                    }
                }
            else if ( !AknLayoutUtils::PenEnabled() &&
              ((aPointerPos.iY < viewRect.iTl.iY) || (aPointerPos.iY > viewRect.iBr.iY)) )
                {
                if (aPointerPos.iY < viewRect.iTl.iY)
                    {
                    ignoreDragRect.SetRect( screenRect.iTl, 
                                            TPoint( screenRect.iBr.iX, viewRect.iTl.iY ));
                    }
                else
                    {
                    ignoreDragRect.SetRect( TPoint( screenRect.iTl.iX, viewRect.iBr.iY), 
                                            screenRect.iBr);
                    }
                }
            Window().RequestPointerRepeatEvent( interval, 
                                                ignoreDragRect );
            }
            
        pointerIsOverAnItem = iView->XYPosToItemIndex(aPointerPos, itemIndex);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( effects )
            {
            bottomItemIndex = topItemIndex + oldBottomItemIndex - oldTopItemIndex;
            }
        else
            {
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            topItemIndex = iView->TopItemIndex();
            bottomItemIndex = iView->BottomItemIndex();
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        // When scrolling don't focus first / last item unless it's really
        // the first / last item of the list
        if ( speed > 0 /*&& itemIndex == bottomItemIndex*/ )
            {
            if ( ItemExists ( bottomItemIndex +1 ) )
                {
                itemIndex = bottomItemIndex - 1;
                }
                else
                {
                itemIndex = bottomItemIndex;
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                edge = ETrue;
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                }
            }
        if ( speed < 0 /*&& itemIndex == topItemIndex*/ )
            {
            if ( ItemExists ( topItemIndex -1 ) )
                {
                itemIndex = topItemIndex + 1;
                }
                else
                {
                itemIndex = topItemIndex;                    
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                edge = ETrue;
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                }
            }
        
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( speed != 0 && !effects )
#else
        if(speed != 0)
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            {
            SetCurrentItemIndex(itemIndex);
            DrawNow();
            }
            
        }
    
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( effects )
        {
        if ( AknLayoutUtils::PenEnabled() &&
             ( iListBoxFlags & ES60StyleMultiselection || 
                ((iListBoxFlags & ES60StyleMarkable) && 
                ( (iListBoxExt->iEventModifiers & EModifierShift) ||
                  (iListBoxExt->iEventModifiers & EModifierCtrl) ))))
            {
            if ( speed == 0 )
                {
                if ( itemIndex == oldCurrentItemIndex )
                    {
                    _AKNTRACE_FUNC_EXIT;
                    return;
                    }
                transApi->SetMoveType( MAknListBoxTfxInternal::EListDrag );
                transApi->BeginRedraw( MAknListBoxTfxInternal::EListNotSpecified,
                                       viewRect );
                iView->SetTopItemIndex( topItemIndex );
                iView->SetItemIndex( itemIndex );
                UpdateSelectionsL( iView, transApi, itemIndex, oldCurrentItemIndex, iListBoxExt->iAnchor, iListBoxExt->iSelect );
                }
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
            else if ( edge )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListHitBorder );
                transApi->BeginRedraw( MAknListBoxTfxInternal::EListNotSpecified,
                                       viewRect );
                iView->SetTopItemIndex( topItemIndex );
                iView->SetItemIndex( itemIndex );
                UpdateSelectionsL( iView, transApi, itemIndex, oldCurrentItemIndex, iListBoxExt->iAnchor, iListBoxExt->iSelect );
                }
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
            else
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListDrag );
                transApi->BeginRedraw( MAknListBoxTfxInternal::EListNotSpecified,
                                       viewRect );
                iView->SetTopItemIndex( topItemIndex );
                iView->SetItemIndex( itemIndex );
                UpdateSelectionsL( iView, transApi, itemIndex, oldCurrentItemIndex, iListBoxExt->iAnchor, iListBoxExt->iSelect );
                }            
            }
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
        else if ( edge || iListBoxExt->iSpeed == 0 )
#else
        else if ( iListBoxExt->iSpeed == 0 )
#endif
            {
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
            if ( iListBoxExt->iSpeed == 0 )
                {
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                if ( itemIndex == oldCurrentItemIndex || itemIndex < 0 )
                    {
                    // If itemIndex didn't change or itemIndex doesn't
                    // exist, just return
                    _AKNTRACE_FUNC_EXIT;
                    return;
                    }
                transApi->SetMoveType( MAknListBoxTfxInternal::EListDrag );
#ifdef RD_UI_TRANSITION_EFFECTS_TOUCH_P2
                }
            else
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListHitBorder );
                }
#endif // RD_UI_TRANSITION_EFFECTS_TOUCH_P2
            transApi->BeginRedraw( MAknListBoxTfxInternal::EListNotSpecified,
                                   viewRect );
            iView->SetTopItemIndex( topItemIndex );
            iView->SetItemIndex( itemIndex );
            iView->DrawItem( itemIndex );
            iView->DrawItem( oldCurrentItemIndex );
            for ( TInt i = iView->TopItemIndex(); i <= iView->BottomItemIndex(); i++ )
                {
                if ( i != itemIndex && i != oldCurrentItemIndex &&
                     transApi->SetPosition( MAknListBoxTfxInternal::EListItem, iView->ItemPos( i ), i ) != KErrNone )
                    {
                    iView->DrawItem( i );
                    }
                }
            }
        else
            {
            transApi->SetMoveType( MAknListBoxTfxInternal::EListDrag );
            transApi->BeginRedraw( MAknListBoxTfxInternal::EListNotSpecified,
                                   viewRect );
            iView->SetItemIndex( itemIndex );
                iView->DrawItem( oldCurrentItemIndex );
            iView->SetTopItemIndex( topItemIndex );
            transApi->SetPosition( MAknListBoxTfxInternal::EListHighlight, iView->ItemPos( itemIndex ) );
            for ( TInt i = iView->TopItemIndex(); i <= iView->BottomItemIndex(); i++ )
                {
                iView->DrawItem( i );
                }
            }
        transApi->SetPosition( MAknListBoxTfxInternal::EListHighlight, iView->ItemPos( itemIndex ) );
        UpdateScrollBarThumbs();
        if ( AknLayoutUtils::PenEnabled() )
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            // drag feedback, also for viewers
            TBool feedbackNeeded = !(iListBoxFlags & EPageAtOnceScrolling) // editor case
                                || (oldTopItemIndex != topItemIndex || oldBottomItemIndex != bottomItemIndex); // viewer case
            if ( feedback && feedbackNeeded )
                {
                feedback->InstantFeedback( ETouchFeedbackSensitive );
                }
            ReportListBoxEventL( MEikListBoxObserver::EEventItemDraggingActioned );
            }

        transApi->EndRedraw( MAknListBoxTfxInternal::EListNotSpecified );
        _AKNTRACE_FUNC_EXIT;
        return;
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if (pointerIsOverAnItem)
        {
        // drag event occurred within the listbox
        if ( itemIndex == oldCurrentItemIndex )
            {
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        if ( AknLayoutUtils::PenEnabled() &&
             ( iListBoxFlags & ES60StyleMultiselection || 
                ((iListBoxFlags & ES60StyleMarkable) && 
                ( (iListBoxExt->iEventModifiers & EModifierShift) ||
                  (iListBoxExt->iEventModifiers & EModifierCtrl) ))))
            {
            iView->VerticalMoveToItemL( itemIndex, CListBoxView::EPenMultiselection );
            iListBoxFlags |= EStateChanged;
            }
        else               
            {
            iView->VerticalMoveToItemL( itemIndex, selectionMode );
            UpdateMarkUnmarkMSKL(); 
            }
        UpdateScrollBarThumbs();
        }
    else if (viewRect.Contains(aPointerPos))
        {
        // find item nearest to the pointer pos and make that the current item
        if( iListBoxExt->iIsDownOnItem )
            {
            if( yDistance>0 && itemIndex != oldBottomItemIndex )
                {
                iView->SetCurrentItemIndex( oldBottomItemIndex );
                }
            else if( yDistance<0 && itemIndex != oldTopItemIndex )
                {
                iView->SetCurrentItemIndex( oldTopItemIndex );
                }
            DrawDeferred();
            }
        }
    else if ( AknLayoutUtils::PenEnabled() &&
              ( (aPointerPos.iY < viewRect.iTl.iY) || (aPointerPos.iY > viewRect.iBr.iY) ) && 
              !( (aPointerPos.iX > viewRect.iBr.iX) || (aPointerPos.iX < viewRect.iTl.iX) ) &&
              // Scroll when stulying donw on item other than empty area.
              iListBoxExt->iIsDownOnItem ) 
        {
        // drag event occurred outside the listbox's viewRect

        if ( iListBoxFlags & ES60StyleMultiselection || 
            ((iListBoxFlags & ES60StyleMarkable) && 
                ( (iListBoxExt->iEventModifiers & EModifierShift) ||
                  (iListBoxExt->iEventModifiers & EModifierCtrl) )))
            {
            iView->SetCurrentItemIndex(itemIndex);
            iView->UpdateSelectionL(CListBoxView::EPenMultiselection);          
            iListBoxFlags |= EStateChanged;
            }
        }
    else if ( !AknLayoutUtils::PenEnabled() &&
              ((aPointerPos.iY < viewRect.iTl.iY) || (aPointerPos.iY > viewRect.iBr.iY)) ) 
        {
        // drag event occurred outside the listbox's viewRect
        TRect screenRect(TPoint(-1000, -1000), TPoint(1000, 1000));
        TRect ignoreDragRect;
        TInt oldTopItemIndex = iView->TopItemIndex();
        TInt oldBottomItemIndex = iView->BottomItemIndex();
        if (aPointerPos.iY < viewRect.iTl.iY)
            {
            ignoreDragRect.SetRect(screenRect.iTl, TPoint(screenRect.iBr.iX, viewRect.iTl.iY));
            itemIndex = ItemExists(oldTopItemIndex-1) ? (oldTopItemIndex-1) : oldTopItemIndex;
            }
        else
            {
            ignoreDragRect.SetRect(TPoint(screenRect.iTl.iX, viewRect.iBr.iY), screenRect.iBr);
            itemIndex = ItemExists(oldBottomItemIndex+1) ? (oldBottomItemIndex+1) : oldBottomItemIndex;
            }
 
        SetCurrentItemIndexAndDraw(itemIndex);
        UpdateScrollBarThumbs();
        Window().RequestPointerRepeatEvent( interval, ignoreDragRect);
        }

    if (itemIndex != oldCurrentItemIndex)
        {
        iView->UpdateSelectionL(selectionMode);
 
        if(AknLayoutUtils::PenEnabled())
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            // drag feedback, also for viewers
            TBool feedbackNeeded = !(iListBoxFlags & EPageAtOnceScrolling) // editor case
                                || (oldTopItemIndex != topItemIndex || oldBottomItemIndex != bottomItemIndex); // viewer case
            if ( feedback && feedbackNeeded )
                {
                feedback->InstantFeedback( ETouchFeedbackSensitive );
                }

            ReportListBoxEventL(MEikListBoxObserver::EEventItemDraggingActioned);
            }
 
        iListBoxFlags |= EStateChanged;
        if (IsMatchBuffer())
            {
            ClearMatchBuffer();
            DrawMatcherCursor();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// The function EnableRedraw was declared but never put to use.
//LOCAL_C void EnableRedraw(TAny* aPtr)
//    {
//    CListBoxView& lbv=*(CListBoxView*)aPtr;
//    lbv.SetDisableRedraw(EFalse);
//    }

EXPORT_C void* CEikListBox::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    _AKNTRACE_FUNC_ENTER;

    CheckCreateBufferL(); // don't need to create the full matching buffer here - only the iPressedIndex
    TInt itemIndex( KErrNotFound );
    TPoint pointerPos(aPointerEvent.iPosition);
    TBool pointerIsOverAnItem = iView->XYPosToItemIndex(pointerPos, itemIndex);
    TInt oldCurrentItemIndex;    
    TBool listEmpty = !ItemExists( iView->TopItemIndex() );
    
    // Handle empty list area events
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
            !iListBoxExt->iScrolling )
        {
        if ( listEmpty )
            {
            // No items, empty list was clicked
            ReportListBoxEventL( MEikListBoxObserver::EEventEmptyListClicked );
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        else if ( !pointerIsOverAnItem )
            {
            // Items exist, empty list area was clicked
            ReportListBoxEventL( MEikListBoxObserver::EEventEmptyAreaClicked );
            _AKNTRACE_FUNC_EXIT;
            return;
            }        
        }     
    else if ( listEmpty )
        {
        // Return always if list empty to avoid tactile feedback
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    
    // When in marking mode, pointer events should not be forwarded to 
    // long tap detector, this boolean indicates if marking mode is active
    TBool markingMode( iListBoxExt->MarkedItems() );
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        if ( iListBoxExt->iSingleClickEnabled && 
             itemIndex != iView->CurrentItemIndex() )
            {
            iListBoxExt->EnableHighlight( EFalse );
            iView->DrawItem( iView->CurrentItemIndex() );
            }

        iListBoxExt->iFeedbackType = ETouchFeedbackBasicItem;

        if ( itemIndex != iView->CurrentItemIndex() ||
             iListBoxFlags & ES60StyleMultiselection )
            {
            iListBoxExt->iFeedbackType = ETouchFeedbackSensitiveItem;
            }

        if ( iListBoxExt->iPhysics &&
             iListBoxExt->iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking )
            {
            iListBoxExt->iFeedbackType = ETouchFeedbackBasicItem;
            }
        
        if ( !iListBoxExt->iPhysics || itemIndex == iView->CurrentItemIndex() )
            {
            iListBoxExt->ImmediateFeedback( iListBoxExt->iFeedbackType,
                                            TTouchFeedbackType(ETouchFeedbackVibra | ETouchFeedbackAudio),
                                            aPointerEvent );
            }
        }
    iListBoxExt->iEventModifiers = aPointerEvent.iModifiers;
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
    TBool shiftKeyPressed = EFalse;
    TBool controlKeyPressed = EFalse;

    if (iListBoxFlags & EMultipleSelection)
        {
        // determine selection mode
        if ( iListBoxExt->iShiftKeyPressed )
            {
            shiftKeyPressed = ETrue;
            }
        else
            {
            shiftKeyPressed = (aPointerEvent.iModifiers) & EModifierShift;
            }
        controlKeyPressed = (aPointerEvent.iModifiers) & EModifierCtrl;
        if (shiftKeyPressed)    
            selectionMode = CListBoxView::EContiguousSelection;
        else if (controlKeyPressed)
            selectionMode = CListBoxView::EDisjointSelection;
        }

    TBool s60StyleMultiselection = EFalse;
    TBool s60StyleMarkable = EFalse;

    if (iListBoxFlags & ENoExtendedSelection)
        {
        controlKeyPressed = ETrue;
        selectionMode = CListBoxView::EDisjointSelection;
        }
        
    if (iListBoxFlags & ES60StyleMultiselection )
        {
        s60StyleMultiselection = ETrue;
        selectionMode = CListBoxView::EDisjointSelection;
        }
    else if (iListBoxFlags & ES60StyleMarkable )
        {
        s60StyleMarkable = ETrue;
        }
        
    if ( (aPointerEvent.iModifiers&EModifierDoubleClick)
         && pointerIsOverAnItem && selectionMode == CListBoxView::ENoSelection
         && ( !iListBoxExt->IsInHandleAllPointEventArray( itemIndex ) ))
    {
    // Do not return here if S60StyleMultiselection is used
    if ( !(iListBoxFlags & ES60StyleMultiselection) &&
          !(iListBoxFlags & ES60StyleMarkable) )
        {
        iListBoxExt->iEventModifiers = 0;
        }
    
    if(Buffer()->iPressedIndex == itemIndex)
        {
        Buffer()->iPressedIndex = KEikListBoxInvalidIndex;
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    }
    
    TBool simulateOkKey = EFalse;
    
    TBool hasPhysics = ( iListBoxExt && iListBoxExt->iPhysics );
    TBool wasFlicking = EFalse;

    if ( hasPhysics )
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            wasFlicking = ( iListBoxExt->iPhysics
                    && iListBoxExt->iPhysics->OngoingPhysicsAction() ==
                    CAknPhysics::EAknPhysicsActionFlicking );
            }
        if ( HandlePhysicsPointerEventL( aPointerEvent ) )
            {
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        }
                
    switch (aPointerEvent.iType)
        {
        case TPointerEvent::EButton1Down:
            _AKNTRACE("TPointerEvent::EButton1Down");
            // For drag outside listbox
            iListBoxExt->iIsDownOnItem = pointerIsOverAnItem;
            iListBoxExt->iLastPoint = pointerPos;

            // update index of the last down tapped item
            iListBoxExt->iLastDownTappedItem = itemIndex;

            if ((! (Rect().Contains(aPointerEvent.iPosition))) && (iListBoxFlags & EPopout)) 
                {
                ReportEventL(MCoeControlObserver::EEventRequestCancel);
                iListBoxExt->iEventModifiers = 0;
                _AKNTRACE_FUNC_EXIT;
                return;
                }
            if (iView->ViewRect().Contains(aPointerEvent.iPosition))
                iListBoxFlags|=ELeftDownInViewRect;
            else
                {
                iListBoxExt->iEventModifiers = 0;
                _AKNTRACE_FUNC_EXIT;
                return;
                }
        
            oldCurrentItemIndex = iView->CurrentItemIndex();
            Buffer()->iDragToAnotherItem = EFalse; 
            if (pointerIsOverAnItem)
                {
                // check if pressed in the same position, if not reset pressed
                Buffer()->iPressedIndex = (itemIndex==oldCurrentItemIndex ? itemIndex : KEikListBoxInvalidIndex);

                if ( !hasPhysics && !iListBoxExt->iSingleClickEnabled )
                    {
                    iItemDrawer->ClearFlags ( CListItemDrawer::EDisableHighlight );
                    }

                if ( !hasPhysics || !iListBoxExt->HighlightTimerActive() )
                    {   
                    // If single click mode is enabled and no physics enabled,
                    // set highlight visible on pointer down.
                    if ( iListBoxExt->iSingleClickEnabled )
                        {
                        // If flick was stopped - give only tactile feedback
                        if ( !wasFlicking )
                            {
                            iListBoxExt->EnableHighlight( ETrue, ETrue );
                            UpdateHighlightL( itemIndex );
                            CCoeEnv::Static()->WsSession().Finish();
                            }
                        if ( itemIndex != oldCurrentItemIndex )
                            {
                        	iListBoxExt->ImmediateFeedback( 
                                iListBoxExt->iFeedbackType,
                                TTouchFeedbackType( ETouchFeedbackVibra | 
                                ETouchFeedbackAudio ),
                                aPointerEvent );
                        	}
                        if ( !wasFlicking )
                            {
                            ReportListBoxEventL( 
                                    MEikListBoxObserver::EEventPenDownOnItem );
                            iListBoxExt->LongTapPointerEventL( aPointerEvent );
                            }
                        }
                    else
                        {
                        ReportListBoxEventL( 
                                MEikListBoxObserver::EEventPenDownOnItem );    
                        }
                    }
                else
                    {
                    iListBoxExt->iReportDelayedPenDown = ETrue;
                    iListBoxExt->iDelayedPointerDownEvent = aPointerEvent;
                    }
 
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                    if ( itemIndex != oldCurrentItemIndex )
                        {
                        MAknListBoxTfxInternal* transApi =
                                    CAknListLoader::TfxApiInternal( iView->iGc );
                        if ( transApi && !transApi->EffectsDisabled() )
                            {
                            transApi->SetMoveType( MAknListBoxTfxInternal::EListTap );
                            }
                        }
#endif
                if (!(iListBoxFlags & EMultipleSelection))      // i.e. this is a single selection listbox
                    {
                    if (itemIndex == oldCurrentItemIndex)
                        {
                        iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );
                        iView->DrawItem( itemIndex );

                        iListBoxExt->iEventModifiers = 0;
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                    
                    if ( !hasPhysics )
                        {
                        iView->SetItemIndex(itemIndex);
                        iView->DrawItem(oldCurrentItemIndex);
                        iView->DrawItem(itemIndex);
                        }
                    
                    iListBoxFlags |= EStateChanged;
                    }
                else if ( s60StyleMultiselection )
                    {
                    if ( !hasPhysics || !iListBoxExt->HighlightTimerActive() )
                        {
                        iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );

                        iView->SetItemIndex(itemIndex);
                        iView->DrawItem(oldCurrentItemIndex);
                        iView->DrawItem(itemIndex);
                        iListBoxFlags |= EStateChanged;
                        Buffer()->iPressedIndex = itemIndex;

                        if ( !hasPhysics )
                            {
                            ReportEventL(MCoeControlObserver::EEventStateChanged);
                            }
                        
                        ReportListBoxEventL(MEikListBoxObserver::EEventItemClicked);
                        }
                    else
                        {
                        iListBoxExt->iDelayedMultiselection = ETrue;
                        }
                    }
                else if ( s60StyleMarkable )
                    {
                    if ( !hasPhysics )
                        {
                        iView->SetItemIndex( itemIndex );
                        }
                    else
                        { // shift key will be handled in highlight timer
                        iListBoxExt->iMarkableListMarking = ETrue; 
                        if ( shiftKeyPressed )
                            {
                            iListBoxExt->iMarkableListShiftKeyPressed = ETrue;
                            // EPenMultiSelection moved to timer callback
                            // CListBoxView::EPenMultiselection;
                            selectionMode = CListBoxView::ENoSelection;
                            }
                        else
                            {
                            iListBoxExt->iMarkableListShiftKeyPressed = EFalse;
                            }
                        }

                    if ( itemIndex == oldCurrentItemIndex )
                        {
                        if ( shiftKeyPressed )
                            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                            iListBoxExt->iAnchor = oldCurrentItemIndex;
                            iListBoxExt->iSelect =
                                !iView->ItemIsSelected( iView->CurrentItemIndex() );
#endif // RD_UI_TRANSITION_EFFECTS_LIST

                            iView->SetAnchor( oldCurrentItemIndex );                      
                            iView->UpdateSelectionL( CListBoxView::EChangeMarkMode );
                            selectionMode = CListBoxView::EPenMultiselection;
                            iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );
                            }
                        else
                            {
                            iView->SetAnchor( itemIndex - 1 );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                            iListBoxExt->iAnchor = itemIndex - 1;
#endif // RD_UI_TRANSITION_EFFECTS_LIST
                            }
                        }

                    if ( !hasPhysics )
                        {
                        iView->DrawItem( oldCurrentItemIndex );
                        }

                    iView->UpdateSelectionL( selectionMode );
                    iListBoxFlags |= EStateChanged;

                    if ( !hasPhysics )
                        {
                        iView->DrawItem( itemIndex );
                        }
                    }
                else    // multiple selection listbox
                    {
                    if ((itemIndex == oldCurrentItemIndex) && (iView->ItemIsSelected(itemIndex)) && (! controlKeyPressed))
                        {
                        iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );
                        iView->DrawItem( itemIndex );
                        iListBoxExt->iEventModifiers = 0;
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }

                    if ( !hasPhysics )
                        {
                        iView->SetItemIndex(itemIndex);
                        iView->DrawItem(oldCurrentItemIndex);
                        }
                    
                    iView->UpdateSelectionL(selectionMode);
                    iListBoxFlags |= EStateChanged;
                    } 
                if (itemIndex != oldCurrentItemIndex)
                    {
                    iListBoxFlags |= EStateChanged;
                    // Fixed for TSW error ETLN-7T2CSR.
                    if ( !hasPhysics && IsMatchBuffer() )
                        {
                        ClearMatchBuffer();
                        DrawMatcherCursor();
                        }
                    }
                else
                    {
                    iItemDrawer->SetFlags( 
                        CListItemDrawer::EPressedDownState );
                    iView->DrawItem( itemIndex ); 
                    }
                }
            break;
            
        case TPointerEvent::EButton1Up:
            _AKNTRACE("TPointerEvent::EButton1Up");
            if ( iListBoxExt->FeedbackEnabledOnUpEvent() && iListBoxExt->iClickEventsAllowed )
                {
                TTouchLogicalFeedback fbType = ETouchFeedbackBasicItem;
                if ( iListBoxFlags & ES60StyleMultiselection )
                    {
                    fbType = ETouchFeedbackCheckbox;
                    }
                iListBoxExt->ImmediateFeedback( fbType,
                                                ETouchFeedbackVibra,
                                                aPointerEvent );
                }
            if ((! (Rect().Contains(aPointerEvent.iPosition))) && (iListBoxFlags & EPopout)) 
                {
                ReportEventL(MCoeControlObserver::EEventRequestCancel);
                iListBoxExt->iEventModifiers = 0;
                _AKNTRACE_FUNC_EXIT;
                return;
                }
            if (!(iListBoxFlags & ELeftDownInViewRect))
                {
                iListBoxExt->iEventModifiers = 0;
                _AKNTRACE_FUNC_EXIT;
                return;
                }
                
            if (iListBoxFlags & EStateChanged)
                {
                iListBoxFlags &= (~EStateChanged);
                if ( !s60StyleMultiselection )
                    {
                    ReportEventL(MCoeControlObserver::EEventStateChanged);
                    UpdateMarkUnmarkMSKL();
                    }
                }
            iListBoxFlags&=(~ELeftDownInViewRect);
            if (pointerIsOverAnItem)
                {
                TUint32 lastPointUpTime = iListBoxExt->iListPointUpTime;
                iListBoxExt->iListPointUpTime = User::NTickCount();

                TInt lastItemIndex = iListBoxExt->iLastItemIndex;
                iListBoxExt->iLastItemIndex = itemIndex;

                if ( ( iListBoxExt->iListPointUpTime - lastPointUpTime < KTwoPointerUpEventInterval )
                     && lastItemIndex == itemIndex
                     && ( !iListBoxExt->IsInHandleAllPointEventArray( itemIndex ) )
                     && !hasPhysics )
                {
                    iListBoxExt->iLastItemIndex = KEikListBoxInvalidIndex;
                    _AKNTRACE_FUNC_EXIT;
                    return;
                }

                if ( !hasPhysics )
                    {
                    iListBoxExt->LongTapPointerEventL( aPointerEvent );
                    }
                if ( !s60StyleMultiselection )
                    {
                    if ( !iListBoxExt->iSingleClickEnabled )
                        {
                        ReportListBoxEventL(MEikListBoxObserver::EEventItemClicked);
                        }
                    else if ( itemIndex == iListBoxExt->iLastDownTappedItem )
                        {
                        // Single click item activation
                        iListBoxExt->EnableHighlight( EFalse );
                        UpdateHighlightL( itemIndex );
                        ReportListBoxEventL( 
                            MEikListBoxObserver::EEventItemSingleClicked );
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                    }
                else if ( s60StyleMultiselection && 
                          iListBoxExt->iLastDownTappedItem == itemIndex &&
                          !Buffer()->iDragToAnotherItem )
                    {
                    iListBoxFlags |= EStateChanged;
                    Buffer()->iPressedIndex = itemIndex;
                    iView->SetAnchor(itemIndex-1); // zero indexed
                    iView->UpdateSelectionL(selectionMode);
                    ReportEventL(MCoeControlObserver::EEventStateChanged);

                    // Single click item activation
                    if ( iListBoxExt->iSingleClickEnabled )
                        {
                        iListBoxExt->EnableHighlight( EFalse );
                        UpdateHighlightL( itemIndex );
                        ReportListBoxEventL( 
                            MEikListBoxObserver::EEventItemSingleClicked );
                        }
                    else
                        {
                        ReportListBoxEventL(MEikListBoxObserver::EEventItemClicked);
                        }

                    UpdateMarkUnmarkMSKL();
                    }

                if ((iListBoxFlags & EPopout) && (!(shiftKeyPressed || controlKeyPressed)))
                    ReportEventL(MCoeControlObserver::EEventRequestExit);
                else if ((Buffer()->iPressedIndex != KEikListBoxInvalidIndex) &&
                        (itemIndex==Buffer()->iPressedIndex) &&
                        ( !Buffer()->iDragToAnotherItem ) && 
                        (selectionMode == CListBoxView::ENoSelection))
                    {
                    if ( iAvkonAppUi->IsTouchCompatible() )
                        {
                        //In some cases, listbox will be blocked here for dialog(such as launch out a CAknQueryDialog).
                        //And then, if App does not wait for dialog's back, and deletes container of listbox directly,
                        //iListBoxExt will be a null point.
                        iListBoxExt->iEventModifiers = 0;

                        // Clear pressed highlight and redraw item
                        iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
                        UpdateHighlightL( itemIndex );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
                        if ( transApi && !transApi->EffectsDisabled() )
                            {
                            DrawNow();
                            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
                        if ( !iListBoxExt->iSingleClickEnabled )
                            {
                            ReportListBoxEventL(MEikListBoxObserver::EEventItemDoubleClicked);
                            }
                        _AKNTRACE_FUNC_EXIT;
                        return;
                        }
                    else
                        {
                        simulateOkKey = ETrue;
                        }
                    }
                else
                    {
                    Buffer()->iPressedIndex=KEikListBoxInvalidIndex;
                    }
                }
            iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
            iView->DrawItem( iView->CurrentItemIndex() );            
            iListBoxExt->iIsDownOnItem = EFalse;         
            break;
            
        case TPointerEvent::EDrag:
            _AKNTRACE("TPointerEvent::EDrag");
            // CAUTION: on hw, drag is too easy. Add a threshold for it.
            if ( iListBoxExt->IsInIgnoreRect( pointerPos ) )
                {
                break;
                }

            if ( !hasPhysics && ( itemIndex != iView->CurrentItemIndex() ) )
                {
                // If single click mode is enabled, make sure that 
                // highlight is cleared when dragging to other item.
                if ( iListBoxExt->iSingleClickEnabled )
                    {
                    iListBoxExt->EnableHighlight( EFalse );
                    iListBoxExt->iLastDownTappedItem = KErrNotFound;
                    
                    // Cancel long tap animation 
                    iListBoxExt->CancelLongTapL();

                    }
                else
                    {
                    iItemDrawer->SetFlags( CListItemDrawer::EDisableHighlight );
                    }
                ReportListBoxEventL( MEikListBoxObserver::EEventItemDraggingActioned );
                }
            
            if( ( Buffer()->iPressedIndex != KEikListBoxInvalidIndex ) 
                && ( Buffer()->iPressedIndex != itemIndex)
                )
                {
                Buffer()->iDragToAnotherItem = ETrue;

                if ( !hasPhysics && 
                        ( iItemDrawer->Flags() & CListItemDrawer::EPressedDownState ) )
                    {
                    iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
                    iView->DrawItem( iView->CurrentItemIndex() );
                    }
                }
        
            if( static_cast<CAknAppUi*>(iEikonEnv->EikAppUi())->IsFaded() && !IsFocused() )
                {
                iListBoxFlags&=(~ELeftDownInViewRect);
                _AKNTRACE_FUNC_EXIT;
                return;
                }
            if ( !s60StyleMultiselection )
                {
                HandleDragEventL(pointerPos);
                }
            else
                {
                // selection mode needs to be disabled in multiselection lists
                // since dragging is not supported
                iListBoxFlags &= ~ES60StyleMultiselection;
                HandleDragEventL( pointerPos );
                iListBoxFlags |= ES60StyleMultiselection;
                }            
            break;
            
        case TPointerEvent::EButtonRepeat:
            _AKNTRACE("TPointerEvent::EButtonRepeat");
            // CAUTION: on hw, drag is too easy. Add a threshold for it.
            if ( iListBoxExt->IsInIgnoreRect( pointerPos ) )
                {
                break;
                }
            
            // make sure that highlight is cleared when dragging to other item.
            if ( !hasPhysics && itemIndex != iView->CurrentItemIndex() )
                {
                if ( iListBoxExt->iSingleClickEnabled )
                    {
                    iListBoxExt->EnableHighlight( EFalse );
                    iListBoxExt->iLastDownTappedItem = KErrNotFound;
                    }
                else
                    {
                    iItemDrawer->SetFlags( CListItemDrawer::EDisableHighlight );
                    }
                }
            
            if (!(iListBoxFlags & ELeftDownInViewRect))
                {
                iListBoxExt->iEventModifiers = 0;
                _AKNTRACE_FUNC_EXIT;
                return;
                }

            if ( !s60StyleMultiselection )
                {
                HandleDragEventL(pointerPos);
                }
            else
                {
                // selection mode needs to be disabled in multiselection lists
                // since dragging is not supported
                iListBoxFlags &= ~ES60StyleMultiselection;
                HandleDragEventL( pointerPos );
                iListBoxFlags |= ES60StyleMultiselection;
                }            
            break;
            
        default:
            break;
        }
        
    iListBoxExt->iEventModifiers = 0;
    
    if ( simulateOkKey )
        {
        TKeyEvent keyEvent;
        keyEvent.iCode = EKeyOK;
        keyEvent.iScanCode = EStdKeyDevice3;// EStdKeyOK;
        keyEvent.iRepeats = 0;
        keyEvent.iModifiers = 0;
        CCoeEnv::Static()->SimulateKeyEventL( keyEvent, EEventKey );
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SimulateArrowKeyEventL(TKeyCode aKeyCode)
    {
    TKeyEvent keyEvent;
    keyEvent.iCode = aKeyCode;
    if (iListBoxFlags & EMultipleSelection)
        keyEvent.iModifiers = EModifierShift;
    OfferKeyEventL(keyEvent, EEventKey);
    }

EXPORT_C void CEikListBox::ClearSelection()
    {
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    iView->ClearSelection();
    }

EXPORT_C void CEikListBox::FocusChanged(TDrawNow aDrawNow)
    {
    _AKNTRACE_FUNC_ENTER;
    if (iListBoxFlags & EEnterMarks || iListBoxFlags & EShiftEnterMarks )
        {
        CEikButtonGroupContainer *cba;
        MopGetObject(cba);
        // CR PKEA-4YSASZ
        // Unfortunately, we need to do this here. It belongs to 
        // CAknSelectionListDialog, but we need this change also 
        // to code that does not yet use CAknSelectionListDialog.
        if (cba && IsFocused())
            {
            if (iListBoxFlags & EEnterMarks)
                {
                TRAP_IGNORE(iAvkonEnv->CreateCbaObserverL(cba, this));
                }
            if (iListBoxExt && iListBoxExt->iMSKObserverEnabled)
                {
                TRAP_IGNORE(iListBoxExt->CreateMSKObserverL(cba, this));
                }
            }
        else
            {
            if (iListBoxFlags & EEnterMarks)
                {
                iAvkonEnv->RemoveCbaObserver();
                }
            if (iListBoxExt)
                {
                iListBoxExt->RemoveMSKObserver(this);
                }
            }
        }
        
    if (IsFocused())
        {
        // Some client does not let list get button1up, so we do it there...
        if ( iItemDrawer->Flags() & CListItemDrawer::EPressedDownState )
            {
            iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
            DrawItem( iView->CurrentItemIndex() );
            }        
        iView->SetEmphasized(ETrue);
        // This is needed or dialog pages do not work correctly.
        // See for example multi-item fetch.
        UpdateScrollBarThumbs();

        if (IsMatchBuffer())
            iView->DrawMatcherCursor();
        if ( iListBoxFlags & EPaintedSelection ) // added
            {
            TRAP_IGNORE(iView->SelectItemL(CurrentItemIndex()));
            }
        }
    else
        {
        // switch off selection (marking) mode when we lose focus
        // this also corrects situation, where FEP-menu is launched
        // and thus listbox doesn't receive shift up event
        if (NULL != iListBoxExt)
            {
            if ((iListBoxFlags & EMultipleSelection) && (iListBoxFlags & EShiftEnterMarks))
                {
                iListBoxExt->iShiftKeyPressed = EFalse;
                if (iListBoxExt->iLongPressTimer && iListBoxExt->iLongPressTimer->IsActive())
                    {
                    iListBoxExt->iLongPressTimer->Cancel();
                    }
                ChangeSelectionMode(EFalse);
                iListBoxExt->iSelectionModeEnabled = EFalse;
                }
            
            // Cancel long tap detecting if focus is lost
            iListBoxExt->CancelLongTapL();
            }
    
        iView->SetEmphasized(EFalse);
        iView->HideMatcherCursor();
        
        if (iItemEditor && 
            (iListBoxFlags & EPaintedSelection) && 
            (NULL != iListBoxExt && iListBoxExt->ReasonForFocusLost() == EFocusLostToExternalControl))
            {
            iView->DeselectItem(CurrentItemIndex());
            }
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    // LISTBOX EFFECTS IMPLEMENTATION
    if ( aDrawNow && !CAknListLoader::TfxApiInternal( iView->iGc ) )
#else
    if (aDrawNow)
#endif //RD_UI_TRANSITION_EFFECTS_LIST
        {
        // redraw items affected by change in emphasis
        TInt numOfSelectedItems = iView->SelectionIndexes()->Count();
        TInt selectionIndex = 0;
        for (TInt i = 0; i < numOfSelectedItems; i++)
            {
            selectionIndex = (*(iView->SelectionIndexes()))[i];
            if (ItemExists(selectionIndex))
                    iView->DrawItem(selectionIndex);
            }
       }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::SetDimmed(TBool aDimmed)
    {
    // should panic if view does not exist
    CCoeControl::SetDimmed(aDimmed);
    iView->SetDimmed(aDimmed);
    HandleResourceChange(KEikMessageColorSchemeChange);
    }

EXPORT_C void CEikListBox::ClearMatchBuffer() const
    {
    if(IsMatchBuffer())
        {
        iView->SetMatcherCursorPos(0);
        MatchBuffer()->Clear();
        }
    }

//
// Shortcut support functions (no default implementation available)
//
EXPORT_C TInt CEikListBox::ShortcutValueForNextList() 
    { 
    //__ASSERT_DEBUG(0,Panic(EEikPanicInvalidUseOfListBoxShortcuts)); 
    return 0;
    }
EXPORT_C void CEikListBox::SetShortcutValueFromPrevList(TInt /*aValue*/) 
    {
    //__ASSERT_DEBUG(0,Panic(EEikPanicInvalidUseOfListBoxShortcuts));
    }

// pop-up positioning support
EXPORT_C TRect CEikListBox::HighlightRect() const
    {
    TPoint topLeft( View()->ItemPos( CurrentItemIndex() ) );
    topLeft += iAvkonAppUi->ClientRect().iTl;

    TRect rect( topLeft, iItemDrawer->ItemCellSize() );

    return rect;
    }

EXPORT_C TBool CEikListBox::BackgroundDrawingSuppressed() const
    {
    if ( iListBoxExt )
        {
        return iListBoxExt->iBackgroundDrawingSuppressed;
        }
        
    return EFalse;
    }

// Series 60  needs this to control the state machine that determines how
// shortcuts work.
EXPORT_C TBool CEikListBox::LastCharMatched() const
    {
    return iLastCharMatched;
    }

EXPORT_C void CEikListBox::MatchTypedCharL(TUint aCode)
    {
    _AKNTRACE_FUNC_ENTER;
    iLastCharMatched = EFalse;
    if (iListBoxFlags&ENoFirstLetterMatching)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    const MDesCArray* matchableTextArray = iModel->MatchableTextArray();
    if (! matchableTextArray)
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    if (IsMatchBuffer())
        {
        TInt matcherCursorPos = iView->MatcherCursorPos();
        if (MatchBuffer()->MatchLength() == KEikMaxMatchingBufferLength)
            {
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        MatchBuffer()->AppendChar(aCode);
        TInt selectedItemIndex;
        TInt ret = MatchBuffer()->FirstMatchingIndexF(selectedItemIndex, *matchableTextArray);
        if (ret == KErrNone)
            {
            ++matcherCursorPos;
/*
            if (matcherCursorPos >= matchableTextArray->MdcaPoint(selectedItemIndex).Length())
                {
                iListBoxExt->iBuffer->iMatchBuffer->DeleteLastChar();
                --matcherCursorPos;
                }
*/
            iView->VerticalMoveToItemL(selectedItemIndex, CListBoxView::ESingleSelection);
            // SetCurrentItemIndexAndDraw(selectedItemIndex);
            iView->SetMatcherCursorPos(matcherCursorPos);
            iLastCharMatched = ETrue;
            }
        else   // No match with buf with new letter: discard new char
            {       
            iLastCharMatched = EFalse;      
            MatchBuffer()->DeleteLastChar();
            }
        }
    else
        {
        // do first later matching here
        TChar matchCharacter(aCode);
        matchCharacter.Fold();
        TInt currentItemIndex = iView->CurrentItemIndex();   
        TChar firstCharOfItem;
        TBool foundMatch = EFalse;
        TInt itemIndex = currentItemIndex + 1;
        // look for match, starting at item below the current one
        while ((itemIndex != currentItemIndex) && !foundMatch)
            {
            // if end of list reached, restart search from the beginning of the list
            if (ItemExists(itemIndex) == EFalse)
                {
                itemIndex = 0;
                if (itemIndex == currentItemIndex)
                    {
                    foundMatch = ETrue;
                    break;
                    }
                }
            TPtrC buf=matchableTextArray->MdcaPoint(itemIndex);
            if (buf.Length())
                {
                firstCharOfItem = buf[0];
                firstCharOfItem.Fold();
                if (matchCharacter == firstCharOfItem)
                    {
                    foundMatch = ETrue;
                    break;
                    }
                }
            ++itemIndex;
            }
        if (foundMatch)
            {
            iLastCharMatched = ETrue;
            // SetCurrentItemIndexAndDraw(itemIndex);
            iView->VerticalMoveToItemL(itemIndex, CListBoxView::ESingleSelection);
        }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikListBox::UndoLastChar()
    {
    __ASSERT_DEBUG(MatchBuffer(), Panic(EEikPanicListBoxNoMatchBuffer));
    __ASSERT_DEBUG(iModel->MatchableTextArray(), Panic(EEikPanicListBoxNoMatchTextArray));
    iView->SetMatcherCursorPos(iView->MatcherCursorPos() - 1);
    MatchBuffer()->DeleteLastChar();
    TInt selectedItemIndex;
    const MDesCArray* matchableTextArray = iModel->MatchableTextArray(); 
    TInt retcode = MatchBuffer()->FirstMatchingIndexF(selectedItemIndex, *matchableTextArray);
    if (!retcode)
        SetCurrentItemIndexAndDraw(selectedItemIndex);
    }

EXPORT_C void CEikListBox::SetLaunchingButton(CEikButtonBase* aButton)
    {
    iLaunchingButton=aButton;
    }

EXPORT_C TCoeInputCapabilities CEikListBox::InputCapabilities() const
    {
    if (iListBoxFlags&EIncrementalMatching)
        return TCoeInputCapabilities(TCoeInputCapabilities::ENavigation|TCoeInputCapabilities::EAllText);
    if (iListBoxFlags&ENoFirstLetterMatching)
        return TCoeInputCapabilities(TCoeInputCapabilities::ENavigation);
    return TCoeInputCapabilities(TCoeInputCapabilities::ENavigation|TCoeInputCapabilities::EAllText/*,1*/);
    }

/**
*   @ since uikon_1.2
*   A method which returns a TMargins object for the list box.
*   The TMargins object has 4 values, one for each side of the list box.
*   Depending on use of the Laf, the DFRD can program 2, 3 or 4 margins ...
*   ... but although the application developer can see up to 4 different margins ...
*   ... they can only set 2 (ie. iHorizontalMargin and iVerticalMargin)
*/
EXPORT_C TMargins8 CEikListBox::ListBoxMargins() const
    {
    /*
    TMargins margins;
    if(iHorizontalMargin == KLafListBoxUseLafHorizMargins) // if the Laf is being used
    {
        margins.iLeft = LafListBox::LeftMargin();
        margins.iRight = LafListBox::RightMargin();
        }
    else
        {
        // SERIES60 LAF
        margins.iLeft=HorizontalMargin();
        margins.iRight=0;
        // END OF SERIES60 LAF
        }
    if(iVerticalMargin == KLafListBoxUseLafVertMargins) // if the Laf is being used
        {
        margins.iTop = LafListBox::TopMargin();
        margins.iBottom = LafListBox::BottomMargin();
    }
    else
        {
        // SERIES60 LAF
        margins.iTop=VerticalMargin();
        margins.iBottom = 0;
        // END OF SERIES60 LAF

        // Old implementation (not good for Series 60)
        //margins.iTop=margins.iBottom=VerticalMargin();
        //
     
        }
    */
    // SERIES60 LAF
    TMargins8 margins = iMargins ;
    margins.iTop=TInt8(VerticalMargin());
    margins.iBottom = 0;
    margins.iLeft=TInt8(HorizontalMargin());
    margins.iRight = 0;
    // END OF SERIES60 LAF
    return margins;
    }

/**
*   @ deprecated
*   Use CEikListBox::ListBoxMargins() instead, to get more accurate values,
*   as use of this method may cause a single pixel error if the laf
*   is being used, due to the bit shifting involved
*/
EXPORT_C TInt CEikListBox::HorizontalMargin() const
    {
    return ((iMargins.iLeft + iMargins.iRight) >> 1);
    }

/**
*   @ deprecated
*   Use CEikListBox::ListBoxMargins() instead, to get more accurate values,
*   as use of this method may cause a single pixel error if the laf
*   is being used, due to the bit shifting involved
*/
EXPORT_C TInt CEikListBox::VerticalMargin() const
    {
    return ((iMargins.iTop + iMargins.iBottom) >> 1);
    }

EXPORT_C void CEikListBox::SetVerticalMargin(TInt aMargin)
    {
    iMargins.iTop = iMargins.iBottom = (TInt8) aMargin;
    }

EXPORT_C void CEikListBox::SetHorizontalMargin(TInt aMargin)
    {
    iMargins.iLeft = iMargins.iRight = (TInt8) aMargin;
    }

EXPORT_C RIncrMatcherBase* CEikListBox::MatchBuffer() const
    {
    if(CONST_CAST(CEikListBox*,this)->CheckCreateExtension() && Buffer())
        return Buffer()->iMatchBuffer;
    return NULL;
    }

EXPORT_C TInt CEikListBox::ViewRectHeightAdjustment() const
    {
    return iViewRectHeightAdjustment;
    }

EXPORT_C void CEikListBox::SetViewRectHeightAdjustment(TInt aAdjustment)
    {
    iViewRectHeightAdjustment = aAdjustment;
    }

EXPORT_C TRgb CEikListBox::BackColor() const
    {
    return iBackColor;
    }

EXPORT_C TInt CEikListBox::VerticalInterItemGap() const
    {
    return KEikListBoxItemVGap;
//  return ListBoxLaf()->LBxItemVGap();
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikBorderedControl::GetColorUseListL(aColorUseList);
    LafListBox::GetColorUseListL(aColorUseList);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikListBox::HandleResourceChange(TInt aType)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aType = %d", aType );
    CEikBorderedControl::HandleResourceChange(aType);
    
    if(aType==KEikDynamicLayoutVariantSwitch)
        {    
        if( iListBoxExt && iListBoxExt->iPhysics )
            {
            //stop flicking 
            iListBoxExt->iPhysics->StopPhysics();

            //If touch down and hold view,
            //kinetic scrolling should not be started after rotate screen.
            iListBoxFlags &= ( ~ELeftDownInViewRect );
            }
        
        if ( iView )
            {
            iView->SetItemOffsetInPixels( 0 );
            }
        
        // make sure that highlight is removed and long tap is canceled 
        // on layout switch, if single click is enabled and there is 
        // pointer down on any item
        if ( iListBoxExt && iListBoxExt->iSingleClickEnabled 
             && iListBoxExt->iLastDownTappedItem != KErrNotFound )
            {                   
            iListBoxExt->EnableHighlight( EFalse );
            iListBoxExt->CancelLongTapL();
            }              
                      
        SizeChanged();

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
        if ( transApi )
            {
            transApi->Remove( MAknListBoxTfxInternal:: EListEverything );
            }
#endif
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iView->iGc );
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    if ( aType == KEikMessageColorSchemeChange || aType == KAknsMessageSkinChange )
        {
        if ( !CAknEnv::Static()->TransparencyEnabled() && OwnsWindow())
            {
            Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
            }
        iBackColor=iEikonEnv->ControlColor(IsDimmed() ? 
                                    EColorControlDimmedBackground : EColorControlBackground,*this);
        UpdateViewColors();
        UpdateItemDrawerColors();
        
        SizeChanged();
        UpdateScrollBarsColors();
        
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->Remove( MAknListBoxTfxInternal:: EListEverything );
            }
        }
    else if ( transApi && aType == KEikMessageUnfadeWindows && IsReadyToDraw() )
        {
        DrawDeferred();
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
        
    switch ( aType )
        {
        case KEikMessageWindowsFadeChange:
            {
            if ( iListBoxExt )
                {
                iListBoxExt->ReportCollectionChangedEvent();
                }
            } // fall through
        case KEikMessageUnfadeWindows:
        case KEikMessageFadeAllWindows:
            {
            // Some client does not let list get button1up, so we do it there...
            iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
            TInt index = View()->CurrentItemIndex();
            if ( index != KErrNotFound )
            	{
                Window().Invalidate( TRect( View()->ItemPos(index), 
            		                 View()->ItemSize() ) );
            	}
            break;
            }
        case KEikDynamicLayoutVariantSwitch:
        case KEikMessageColorSchemeChange:
        case KAknsMessageSkinChange:
            DrawDeferred();
            break;

        case KAknMessageFocusLost:
            {
            if ( iListBoxExt && iListBoxExt->iSingleClickEnabled )
                {
                TBool enabled( iItemDrawer && !( iItemDrawer->Flags()
                    & CListItemDrawer::ESingleClickDisabledHighlight ) );
                           
                if ( enabled )
                    {
                    iListBoxExt->EnableHighlight( EFalse );
                    if ( iView && IsVisible() )
                        {
                        iView->DrawItem( CurrentItemIndex() );
                        }
                    }
                }
            }
            break;
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CEikListBox::UpdateScrollBarsColors()
    {
    }

void CEikListBox::UpdateScrollBarColors(CEikScrollBar* /*aScrollBar*/)
    {
    }

//-----------------------------------------------------------
// CEikListBox::IsMultiselection()
// Returns true if ES60StyleMultiselection flag is on
//-----------------------------------------------------------
EXPORT_C TBool CEikListBox::IsMultiselection()
    {
    /* note, that this method is very misleading. To have this method
    * return true, you need to construct your listbox with
    * EAknListBoxPointerMultiselectionList flag, not with
    * EAknListBoxMultipleSelection as ES60StyleMultiselection might
    * suggest. However, to make multiselection work, you need
    * to or those flags together...
    */
    return (iListBoxFlags & ES60StyleMultiselection );     
    }
  
//-----------------------------------------------------------
// CEikListBox::EventModifiers()
// Returns pointerevent modifiers.
//-----------------------------------------------------------  
EXPORT_C TInt CEikListBox::EventModifiers()
    {
    if (iListBoxExt)
        {
        return iListBoxExt->iEventModifiers;
        }
    return NULL;
    }

EXPORT_C void CEikListBox::CEikListBox_Reserved()
    {}

TBool CEikListBox::CheckCreateExtension()
    {
    TInt err=KErrNone;
    if (!iListBoxExt)
        {
        TRAP(err,iListBoxExt=CListBoxExt::NewL(*this));
        }
    return err==KErrNone;
    }

void CEikListBox::CheckCreateExtensionL()
    {
    if (!iListBoxExt)
        iListBoxExt=CListBoxExt::NewL(*this);
    }

void CEikListBox::CheckCreateBufferL()
    {
    CheckCreateExtensionL();
    iListBoxExt->CheckCreateBufferL();
    }

CMatchBuffer* CEikListBox::Buffer() const
    {
    if(CONST_CAST(CEikListBox*,this)->CheckCreateExtension())
        return iListBoxExt->Buffer();
    return NULL;
    }

EXPORT_C TBool CEikListBox::IsMatchBuffer() const
    {
    return (CONST_CAST(CEikListBox*,this)->CheckCreateExtension() && iListBoxExt->IsMatchBuffer());
    }

EXPORT_C void CEikListBox::SetReasonForFocusLostL(TReasonForFocusLost aReasonForFocusLost)
    {
    CheckCreateExtensionL();
    iListBoxExt->SetReasonForFocusLost(aReasonForFocusLost);
    }

EXPORT_C CEikListBox::TReasonForFocusLost CEikListBox::ReasonForFocusLostL()
    {
    CheckCreateExtensionL();
    return iListBoxExt->ReasonForFocusLost();
    }

/**
 * Sets the item editor to aEditor and transfers ownership.
 *
 * @since ER5U
 */
EXPORT_C void CEikListBox::SetItemEditor(MEikListBoxEditor* aEditor)
    {
    if (iItemEditor)
        iItemEditor->Release();
    iItemEditor=aEditor;
    }

/**
 * Deletes and NULLs the item editor.
 *
 * @since ER5U
 */
EXPORT_C void CEikListBox::ResetItemEditor()
    {
    if (iItemEditor)
        iItemEditor->Release();
    iItemEditor=NULL;
    }

/**
 * Returns a pointer to the item editor. Does not imply transfer of ownership.
 *
 * @since ER5U
 */
EXPORT_C MEikListBoxEditor* CEikListBox::ItemEditor()
    {
    return iItemEditor;
    }

/**
 * Creates an item editor, if one does not already exist, and starts editing the
 * current item up to a maximum length of aMaxLength characters. Also reports an
 * EEventEditingStarted event to any list box observer by default.
 *
 * @since ER5U
 */
EXPORT_C void CEikListBox::EditItemL(TInt aMaxLength)
    {
    _AKNTRACE_FUNC_ENTER;
    CEikListBoxTextEditor* itemEditor = STATIC_CAST(CEikListBoxTextEditor*,ItemEditor());
    if ( !itemEditor || (itemEditor && !(itemEditor->Editor())) )
        {
        SetItemEditor(new(ELeave) CEikListBoxTextEditor(Model()));
        itemEditor = STATIC_CAST(CEikListBoxTextEditor*,ItemEditor());
        const TInt index = View()->CurrentItemIndex();
        itemEditor->SetFont( ((CTextListItemDrawer*)iItemDrawer)->Font(index) );
        TRect rect = TRect( View()->ItemPos( index ), View()->ItemSize() );
        rect.iTl.iX += LafListBox::InnerGutter();
        if (iItemDrawer->Flags()&CListItemDrawer::EDrawMarkSelection)
            {
            rect.iTl.iX += iItemDrawer->MarkColumn() + iItemDrawer->MarkGutter();
            }
        iListBoxExt->SetReasonForFocusLost(EFocusLostToInternalEditor);
        itemEditor->StartEditingL(*this,rect,index,aMaxLength);
        iListBoxExt->SetReasonForFocusLost(EFocusLostToExternalControl);
        ReportListBoxEventL( MEikListBoxObserver::EEventEditingStarted );
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
 * Stops editing and deletes the item editor, reporting an EEventEditingStopped event
 * to any list box observer. Updates the list box model if aUpdateModel is ETrue.
 *
 * @since ER5U
 */
EXPORT_C void CEikListBox::StopEditingL( TBool aUpdateModel )
    {
    MEikListBoxEditor* editor = ItemEditor();
    if ( editor )
        {
        if ( aUpdateModel ) editor->UpdateModelL();
        editor->StopEditingL();
        ResetItemEditor();
        ReportListBoxEventL( MEikListBoxObserver::EEventEditingStopped );
        }
    }

EXPORT_C CEikScrollBarFrame* CEikListBox::CreateScrollBarFrameL(TBool aPreAlloc, TBool aRemote)
    {
    // CEikListBox creates a window owning scroll bar by default. This causes
    // scroll bar flicker during listbox open when transparency is enabled.
    // With CAknPopupList the listbox and scroll bar are created outside of
    // the CAknPopupList component. In order not to have to change source
    // code of all CAknPopupList users to create a non window owning scroll
    // bar, the default is changed for this case.
    _AKNTRACE_FUNC_ENTER;
    TBool windowOwning = ETrue;
    if (Parent())
        {
        CAknPopupList* popupList;
        Parent()->MopGetObjectNoChaining(popupList);
        if (popupList)
            {
            windowOwning = EFalse;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return CreateScrollBarFrameL(aPreAlloc, aRemote, windowOwning);
    }

EXPORT_C CEikScrollBarFrame* CEikListBox::CreateScrollBarFrameL(TBool aPreAlloc, TBool aRemote, TBool aWindowOwning)
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iSBFrame)
        {
        iSBFrame=new(ELeave) CEikScrollBarFrame(this, this, aPreAlloc, ETrue); 
        
        // Check which type of scrollbar is to be shown
        if (AknLayoutUtils::DefaultScrollBarType(iAvkonAppUi) == CEikScrollBarFrame::EDoubleSpan)
            {
            iSBFrame->CreateDoubleSpanScrollBarsL(aWindowOwning, aRemote, ETrue, EFalse);

            if ( CAknEnv::Static()->TransparencyEnabled() && iListBoxExt && iListBoxExt->iPhysics )
                {
                iSBFrame->DrawBackground(EFalse,EFalse);
                }
            }

        if (CheckCreateExtension())
            iListBoxExt->SetUpdateScrollBarsColors(ETrue);
        if(aRemote)
            iSBFrameOwned = EOwnedExternally;
        else
            iSBFrameOwned = ENotOwnedExternally;
        }
    _AKNTRACE_FUNC_EXIT;
    return iSBFrame;
    }

EXPORT_C void CEikListBox::EnableMSKObserver(TBool aEnable)
    {
    _AKNTRACE_FUNC_ENTER;
    if (iListBoxExt)
        {
        if (aEnable == EFalse)
            {
            iListBoxExt->RemoveMSKObserver(this); // remove disabled observer
            }
        else
            {
            if (iListBoxFlags & EEnterMarks || iListBoxFlags & EShiftEnterMarks)
                {
                CEikButtonGroupContainer *cba;
                MopGetObject(cba);
                if (cba)
                    {
                    TRAP_IGNORE(iListBoxExt->CreateMSKObserverL(cba, this));
                    TRAP_IGNORE(UpdateMarkUnmarkMSKL());
                    }
                }
            }
        iListBoxExt->iMSKObserverEnabled = aEnable;
        }
    _AKNTRACE_FUNC_EXIT;
    }
    
void CEikListBox::DoShiftMSKMarkingL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iListBoxExt && iListBoxExt->iWesternVariant &&
        ( iListBoxFlags & EShiftEnterMarks || iListBoxFlags & EEnterMarks ) )
        {
        // if the user marks item with hash+MSK, releasing MSK should not
        // do the marking again
        iListBoxExt->iShortHashMark = EFalse;

        iView->UpdateSelectionL(CListBoxView::EDisjointSelection);
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        UpdateMarkUnmarkMSKL();
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Disables the kinetic scrolling functionality in the list.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::DisableScrolling( TBool aDisabled )
    {
    _AKNTRACE_FUNC_ENTER;
    iListBoxExt->iScrollingDisabled = aDisabled;
    iView->iExtension->iScrollingDisabled = aDisabled;
    
    if ( aDisabled && iListBoxExt->iPhysics )
        {
        delete iListBoxExt->iPhysics;
        iListBoxExt->iPhysics = NULL;
        iView->SetItemOffsetInPixels( 0 );
        }
    else if ( !aDisabled && !iListBoxExt->iPhysics && CAknPhysics::FeatureEnabled() )
        {
        iListBoxExt->iPhysics = CAknPhysics::NewL( *iListBoxExt, this);      
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Checks if the kinetic scrolling functionality is disabled in the list.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikListBox::ScrollingDisabled()
    {
    return !iListBoxExt->iPhysics || iListBoxExt->iScrollingDisabled;
    }


EXPORT_C void CEikListBox::SetPointerEventFilterDisabledL( const CArrayFix<TInt>& aItemIndexes )
    {
    _AKNTRACE_FUNC_ENTER;
    iListBoxExt->iMutiTappingItems.Reset();

    for(TInt i=0; i<aItemIndexes.Count(); i++ )
        {
        iListBoxExt->iMutiTappingItems.InsertInOrderL( aItemIndexes.At(i) ); 
        }   
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CEikListBox::SuspendEffects
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::SuspendEffects( TBool aSuspend )
    {
    _AKNTRACE_FUNC_ENTER;
    TBool effectsEnabled = EFalse;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal(
            iView->ItemDrawer()->Gc() );

    effectsEnabled = transApi && !transApi->EffectsDisabled();
#endif    
    // Record effect's state before those are suspended so that calling this
    // method doesn't turn effects on if they were disabled already.
    if ( iListBoxExt )
        {
        if ( effectsEnabled && !iListBoxExt->iEffectsEnabled )
            {
            iListBoxExt->iEffectsEnabled = ETrue;
            }
        
        if ( !aSuspend )
            {
            aSuspend = !iListBoxExt->iEffectsEnabled;
            }
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    
    MAknListBoxTfx* tfxApi = CAknListLoader::TfxApi( iView->ItemDrawer()->Gc() );
    
    if (  aSuspend && effectsEnabled && tfxApi )
        {
        tfxApi->EnableEffects( EFalse );
        }
    else if ( !aSuspend && !effectsEnabled && tfxApi )
        {
        tfxApi->EnableEffects( ETrue );
        }
#endif// RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Disables the single click functionality in the list.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::DisableSingleClick( TBool aDisabled )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aDisabled && iListBoxExt->iSingleClickEnabled )
        {
        iListBoxExt->DisableSingleClick(); 
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CEikListBox::DisableItemSpecificMenu
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::DisableItemSpecificMenu()
    {
    if ( iListBoxExt )
        {
        iListBoxExt->DisableItemSpecificMenu();
        }
    }


void CEikListBox::ScrollView( const TInt aOffset, TBool aDrawNow )
	{
	_AKNTRACE_FUNC_ENTER;
#ifdef _DEBUG
	RDebug::Print( _L( "CEikListBox::ScrollView, aOffset = %d, aDrawNow = %d" ), aOffset, aDrawNow );
#endif // _DEBUG

	if ( aOffset != 0 )
	    {
        TInt itemHeight = iView->ItemHeight();
        TInt viewHeight = iView->ViewRect().Size().iHeight;
        TInt itemsInSingleLine = iListBoxExt->iItemsInSingleLine;
        TInt oldListTopPos = ( iView->TopItemIndex() / itemsInSingleLine ) * itemHeight 
            - iView->ItemOffsetInPixels();
        TInt newListTopPos = oldListTopPos - aOffset;
        
        // calculate new top item index and offset
        TInt newTopItemIndex = ( newListTopPos / itemHeight ) * itemsInSingleLine;
        TInt newTopItemIndexBck = newTopItemIndex;
        if ( newTopItemIndex >= Model()->NumberOfItems() )
            {
            newTopItemIndexBck = Model()->NumberOfItems() - 1;
            newTopItemIndex = Model()->NumberOfItems();
            }

        // feedback during flicking and panning
        TInt newListBottomPos = newListTopPos + viewHeight;
        
        TInt newListLastItemPos = ( Model()->NumberOfItems()/itemsInSingleLine ) * itemHeight - newListTopPos;
        if ( newTopItemIndex != iListBoxExt->iPrevTopItemIndex )
            {
            iListBoxExt->iPrevTopItemIndex = newTopItemIndex;
            if( iListBoxExt->FlickOrPanningOngoing() )
                {
                if( ( newListBottomPos < iListBoxExt->ListBottomLimit() && newListTopPos > 0 ) || 
                    ( newListBottomPos >= iListBoxExt->ListBottomLimit() ) ||
                    ( newListTopPos <= 0 && newListTopPos + viewHeight >= 0 && newListLastItemPos > viewHeight ) )
                    {
                    if ( CAknPhysics::EAknPhysicsActionFlicking == iListBoxExt->iPhysics->OngoingPhysicsAction() || 
                         CAknPhysics::EAknPhysicsActionBouncing == iListBoxExt->iPhysics->OngoingPhysicsAction() )
                        {
                        iListBoxExt->ImmediateFeedback( ETouchFeedbackSensitiveItem,
                                                        TTouchFeedbackType( ETouchFeedbackVibra ),
                                                        TPointerEvent() );
                        }
                    else if ( CAknPhysics::EAknPhysicsActionDragging == iListBoxExt->iPhysics->OngoingPhysicsAction() )
                        {
                        iListBoxExt->ImmediateFeedback( iListBoxExt->iFeedbackType,
                                                        TTouchFeedbackType( ETouchFeedbackVibra | ETouchFeedbackAudio ),
                                                        TPointerEvent() );
                        }
                    }
                }
            }
        newTopItemIndex = newTopItemIndexBck;
        if ( newTopItemIndex < 0 )
            {
            newTopItemIndex = 0;
            }
        
        // Top item index should always be the first item index in a row.
        TInt notFirstInRow = newTopItemIndex % itemsInSingleLine;
    
        if ( notFirstInRow > 0 )
            {
            newTopItemIndex -= notFirstInRow;
            }
        
        TInt offset = ( newTopItemIndex / itemsInSingleLine ) * itemHeight - newListTopPos;
    
        iView->SetItemOffsetInPixels( offset );
#ifdef _DEBUG
        RDebug::Print( _L( "CEikListBox::ScrollView, newTopItemIndex = %d" ), newTopItemIndex );
#endif // _DEBUG
        iView->SetTopItemIndex( newTopItemIndex );
        }
    if ( aDrawNow )
        {
        TRect rect(Rect());
        
        // list position changed
        iListBoxExt->iBackgroundDrawingSuppressed = ETrue;
        UpdateScrollBarThumbs();
        DrawNow();
        if (iSBFrame && iSBFrame->VerticalScrollBar() && !iSBFrame->VerticalScrollBar()->OwnsWindow())
            {
            TRect srect( iSBFrame->VerticalScrollBar()->Rect() );
            if ( !srect.Intersects( rect ))
                {
                iSBFrame->DrawScrollBarsNow();                
                }
            }
        iListBoxExt->iBackgroundDrawingSuppressed = EFalse;
        }        
    _AKNTRACE_FUNC_EXIT;
	}


// ---------------------------------------------------------------------------
// Handles pointer events if physics are enabled.
// ---------------------------------------------------------------------------
//
TBool CEikListBox::HandlePhysicsPointerEventL( const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aPointerEvent.iType = %d", aPointerEvent.iType );
    if ( iListBoxExt->iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionBouncing )
        { 
        // Block scrolling events outside listbox area. Note that pointer
        // event ignore must be done for the window-owning control or it
        // doesn't have any effect!
        CCoeControl* windowOwningControl = this;
        
        while ( windowOwningControl && !windowOwningControl->OwnsWindow() )
            {
            windowOwningControl = windowOwningControl->Parent();
            }

        if ( windowOwningControl )
            {
            windowOwningControl->IgnoreEventsUntilNextPointerUp();
            _AKNTRACE_FUNC_EXIT;
            return ETrue;
            }
        }

    TBool blockEvent = EFalse;
    
    TBool allowDragEvent( ( iListBoxFlags & ELeftDownInViewRect ) && iSBFrame && !iListBoxExt->iScrollingDisabled );

    
    switch ( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            TInt tappedItemIndex = KErrNotFound;
            iListBoxExt->iItemDraggingReported = EFalse;
            
            // If list is tapped while flicking then EEventItemClicked etc are not sent
            if ( iListBoxExt->iPhysics->OngoingPhysicsAction() == CAknPhysics::EAknPhysicsActionFlicking )
                {
                iListBoxExt->iClickEventsAllowed = EFalse;
                if ( iItemDrawer->Flags() & CListItemDrawer::EPressedDownState )
                    {
                    iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState ); 
                    }
                
                // Multiselection list tapped while flicking.
                // Just move the highlight, pressed down highlight and
                // item marking are ignored.     
                if ( iListBoxFlags & ES60StyleMultiselection )
                    {
                    iListBoxExt->iIsDownOnItem =
                        iView->XYPosToItemIndex( aPointerEvent.iPosition,
                                                 tappedItemIndex );
                    if ( iListBoxExt->iIsDownOnItem )
                        {
                        iListBoxExt->iLastDownTappedItem = tappedItemIndex;
                        iListBoxExt->iMarkingDisabled = ETrue;
                        blockEvent = ETrue;
                        }
                    }
                }
            else
                {
                iListBoxExt->iClickEventsAllowed = ETrue;
                }
            
            if ( iView->XYPosToItemIndex( aPointerEvent.iPosition, tappedItemIndex ) )
                {
                // Start highlight timer if needed
                if ( tappedItemIndex != iView->CurrentItemIndex() ||
                     iListBoxExt->iSingleClickEnabled )
                    {                   
                    if ( !iListBoxExt->iSingleClickEnabled )
                        {
                        iListBoxExt->StartHighlightTimer();
                        }                    
                    else if ( !( iItemDrawer->Flags() & CListItemDrawer::EDisableMarquee ) )
                        {
                        // Disable marquee
                        iItemDrawer->SetFlags( CListItemDrawer::EDisableMarquee );
                        }
                    }
                }

            iListBoxExt->iPhysics->StopPhysics();
            iListBoxExt->iPhysics->ResetFriction();
            iListBoxExt->iDragStartPosition = aPointerEvent.iPosition;
            iListBoxExt->iLastPointerPos = aPointerEvent.iPosition;
            iListBoxExt->iScrolling = EFalse;
            iListBoxExt->InitPhysicsL();
            iListBoxExt->iStartTime.HomeTime();
            }
            break;
        case TPointerEvent::EButtonRepeat: // fall through
        case TPointerEvent::EDrag:
            {
            if ( allowDragEvent )
                {
                TPoint drag( iListBoxExt->iDragStartPosition - aPointerEvent.iPosition );

                TInt currentItemIndex = iView->CurrentItemIndex();
                TInt touchedItemIndex( KErrNotFound );

                if ( Abs( drag.iY ) > iListBoxExt->iPhysics->DragThreshold() &&
                        !iListBoxExt->iScrolling )
                    {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                    SuspendEffects( ETrue );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
                    iListBoxExt->iScrolling = ETrue;
                    iListBoxExt->CancelHighlightTimer();

                    // Cancel long tap detecting
                    iListBoxExt->CancelLongTapL();
                    // Remove highlight if single click enabled
                    if ( iListBoxExt->iSingleClickEnabled )
                        {
                        iListBoxExt->EnableHighlight( EFalse );
                        iListBoxExt->iLastDownTappedItem = KErrNotFound;
                        iView->SetItemIndex( 0 );
                        }

                    if ( iView->ItemIsVisible( currentItemIndex ) )
                        {
                        iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
                        iView->DrawItem( currentItemIndex );
                        }
                    
                    ReportListBoxEventL( MEikListBoxObserver::EEventPanningStarted );
                    }
                else if ( !iListBoxExt->iScrolling &&
                          iView->XYPosToItemIndex( aPointerEvent.iPosition, touchedItemIndex ) )
                    {
                    // Don't send the dragging actioned event if the
                    // highlight timer hasn't yet completed as in that case
                    // the current item index isn't updated yet.
                    if ( currentItemIndex != touchedItemIndex &&
                         !iListBoxExt->iItemDraggingReported &&
                         !iListBoxExt->HighlightTimerActive() )
                        {
                        iListBoxExt->iItemDraggingReported = ETrue;
                        ReportListBoxEventL( MEikListBoxObserver::EEventItemDraggingActioned );
                        }
                    }
                if ( iItemDrawer->Flags() & CListItemDrawer::EPressedDownState
                          && !iView->ItemIsVisible( currentItemIndex ) )
                    {
                    iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
                    }
                
                if ( iListBoxExt->iScrolling )
                    {
                    iListBoxExt->iPhysics->RegisterPanningPosition( 
                        TPoint( 0, iListBoxExt->iLastPointerPos.iY - aPointerEvent.iPosition.iY ) );

#ifdef _DEBUG
                    RDebug::Print( _L( "CEikListBox::HandlePhysicsPointerEventL, newViewPosition.iX = %d, iY = %d" ), iListBoxExt->iViewPosition.iX, iListBoxExt->iViewPosition.iY );
                    RDebug::Print( _L( "CEikListBox::HandlePhysicsPointerEventL, iListBoxExt->iLastPointerPos.iY = %d" ), iListBoxExt->iLastPointerPos.iY );
                    RDebug::Print( _L( "CEikListBox::HandlePhysicsPointerEventL, aPointerEvent.iPosition.iY = %d" ), aPointerEvent.iPosition.iY );
#endif // _DEBUG
    
                    blockEvent = ETrue;
                    }
    
                iListBoxExt->iLastPointerPos = aPointerEvent.iPosition;
                }
            }
            break;
        
        case TPointerEvent::EButton1Up:
            {          
            if ( iListBoxFlags & ES60StyleMultiselection 
                 && iListBoxExt->iMarkingDisabled )
                {
                // Allow marking again on next up event.
                iListBoxExt->iMarkingDisabled = EFalse;
                blockEvent = ETrue;
                }
            
            // update selected item in case highlight timer is still running
            if ( iListBoxExt->HighlightTimerActive() )
                {
                // Must cancel highlight timer directly instead of using
                // CListBoxExt::CancelHighlightTimer(), because it will
                // also clear the flags used in the highlight timer
                // callback function.
                iListBoxExt->iHighlightTimer->Cancel();
                CListBoxExt::HighlightTimerCallback( iListBoxExt );
                }
                
            TPoint drag( iListBoxExt->iDragStartPosition - aPointerEvent.iPosition );

            iListBoxExt->LongTapPointerEventL( aPointerEvent );
            
            if (  allowDragEvent &&
                 iListBoxExt->iPhysics->StartPhysics( drag, iListBoxExt->iStartTime ) )
                {
                iListBoxExt->CancelLongTapL();

                if ( !iListBoxExt->iScrolling )
                    {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                    SuspendEffects( ETrue );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
                    iItemDrawer->ClearFlags( CListItemDrawer::EPressedDownState );
                    iView->DrawItem( iView->CurrentItemIndex() );
                    iListBoxExt->iScrolling = ETrue;
                    }
                else
                    {
                    ReportListBoxEventL( MEikListBoxObserver::EEventPanningStopped );
                    }
                
                blockEvent = ETrue;

                // Clearing ELeftDownInViewRect should be done by rest code in
                // CEikListBox::HandlePointerEventL, but since the event is 
                // blocked, do it here
                iListBoxFlags&=(~ELeftDownInViewRect);

                ReportListBoxEventL( MEikListBoxObserver::EEventFlickStarted );
                }
            else
                {
                iListBoxExt->iScrolling = EFalse;
                }

            if ( iListBoxExt->iSingleClickEnabled
                     && iListBoxExt->iLongTappedItem == KErrNotFound ) 
                {
                iListBoxExt->EnableHighlight( EFalse );
                TInt itemIndex( 0 );
                if ( !iView->XYPosToItemIndex(
                        aPointerEvent.iPosition, itemIndex ) )
                    {
                    iListBoxExt->iLastDownTappedItem = KErrNotFound;
                    }
                }
            }
            iListBoxExt->iIsDownOnItem = EFalse;
            break;
            
        default:
            break;
        }

    iView->SetScrolling( iListBoxExt->iScrolling );
    _AKNTRACE_FUNC_EXIT;
    return blockEvent;
    }


// ---------------------------------------------------------------------------
// Draws the highlight to the current item.
// ---------------------------------------------------------------------------
//
void CEikListBox::UpdateHighlightL( TInt aItemIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    TInt oldCurrentItemIndex = iView->CurrentItemIndex();

    if ( iListBoxExt->iReportDelayedPenDown && !iListBoxExt->iScrolling )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( aItemIndex != oldCurrentItemIndex )
            {
            MAknListBoxTfxInternal* transApi =
                        CAknListLoader::TfxApiInternal( iView->iGc );
            if ( transApi && !transApi->EffectsDisabled() )
                {
                transApi->SetMoveType( MAknListBoxTfxInternal::EListTap );
                }
            }
#endif
        iView->SetItemIndex( aItemIndex );
        ReportListBoxEventL(
            MEikListBoxObserver::EEventPenDownOnItem );
        
        // The long tap animation should start after the highlight has
        // been made visible.
        iListBoxExt->LongTapPointerEventL(
            iListBoxExt->iDelayedPointerDownEvent );
        }

    if ( iListBoxExt->iDelayedMultiselection )
        {
        iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );
        }
    
    iView->SetItemIndex( aItemIndex );

    if ( iListBoxExt->iMarkableListMarking )
        {
        if ( iListBoxExt->iMarkableListShiftKeyPressed )
           {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
           iListBoxExt->iAnchor = oldCurrentItemIndex;
           iListBoxExt->iSelect =
               !iView->ItemIsSelected( iView->CurrentItemIndex() );
#endif // RD_UI_TRANSITION_EFFECTS_LIST

           iView->SetAnchor( oldCurrentItemIndex );
           iView->UpdateSelectionL( CListBoxView::EChangeMarkMode );
           iItemDrawer->SetFlags( CListItemDrawer::EPressedDownState );
           iView->UpdateSelectionL( CListBoxView::EPenMultiselection );
           }
      else
           {
           iView->SetAnchor( aItemIndex - 1 );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
           iListBoxExt->iAnchor = aItemIndex - 1;
#endif // RD_UI_TRANSITION_EFFECTS_LIST
           }

        iListBoxExt->iMarkableListMarking = EFalse;
        }

    iView->DrawItem( oldCurrentItemIndex );
    iView->DrawItem( aItemIndex );
    
    if ( iListBoxExt->iDelayedMultiselection )
        {
        iListBoxFlags |= EStateChanged;
        Buffer()->iPressedIndex = aItemIndex;
        }

    ReportEventL( MCoeControlObserver::EEventStateChanged );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Sets this control as visible or invisible.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikListBox::MakeVisible( TBool aVisible )
    {
    CEikBorderedControl::MakeVisible( aVisible );
    if ( iListBoxExt )
        {
        if ( !aVisible )
            {
            iListBoxExt->EnableHighlight( EFalse );
            }
        else
            {
            iListBoxExt->ReportCollectionChangedEvent();
            }
        }
    }

//
// class CEikSnakingListBox
//

EXPORT_C CEikSnakingListBox::CEikSnakingListBox()
    {
    AKNTASHOOK_ADD( this, "CEikSnakingListBox" );
    }

EXPORT_C CEikSnakingListBox::~CEikSnakingListBox()
    {
    AKNTASHOOK_REMOVE();
    }

EXPORT_C CListBoxView* CEikSnakingListBox::MakeViewClassInstanceL() 
    {
    return (new(ELeave) CSnakingListBoxView);
    }

EXPORT_C TInt CEikSnakingListBox::ColumnWidth() const
    {
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    return ((CSnakingListBoxView*)iView)->ColumnWidth();
    }

EXPORT_C void CEikSnakingListBox::SetColumnWidth(TInt aColumnWidth)
    {
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    ((CSnakingListBoxView*)iView)->SetColumnWidth(aColumnWidth);
    }

EXPORT_C void CEikSnakingListBox::HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode)
    {
    iView->MoveCursorL(CListBoxView::ECursorPreviousColumn, aSelectionMode);
    ClearMatchBuffer();
    }

EXPORT_C void CEikSnakingListBox::HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode)
    {
    iView->MoveCursorL(CListBoxView::ECursorNextColumn, aSelectionMode);
    ClearMatchBuffer();
    }

EXPORT_C TInt CEikSnakingListBox::HorizontalNudgeValue() const
    {
    return 1;   // scroll horizontal by one column when the left/right scroll arrows (i.e. the nudge buttons) are tapped
    }

EXPORT_C TInt CEikSnakingListBox::HorizScrollGranularityInPixels() const
    {
    return ColumnWidth(); // horiz scrollbar model set in columns for snaking list box
    }

EXPORT_C void CEikSnakingListBox::SetTopItemIndex(TInt aItemIndex) const
    {
    __ASSERT_DEBUG(iView, Panic(EEikPanicListBoxNoView));
    iView->SetTopItemIndex(aItemIndex);
    }

EXPORT_C void CEikSnakingListBox::HandleViewRectSizeChangeL()
    {
    _AKNTRACE_FUNC_ENTER;
    iView->CalcBottomItemIndex();
    TInt oldTopItemIndex = TopItemIndex();
    TInt newTopItemIndex = TopItemIndex();
    TInt currentItemIndex = CurrentItemIndex();
    TInt numOfItemsPerColumn = 0;   
    UpdateScrollBarsL();
    numOfItemsPerColumn = iView->ViewRect().Height() / iItemHeight;
    numOfItemsPerColumn = Max(1, numOfItemsPerColumn);
    if (currentItemIndex != oldTopItemIndex)
        {
        TInt colIndexOfTargetItem = currentItemIndex / numOfItemsPerColumn;
        TInt numOfColsThatFitInViewRect = iView->VisibleWidth(iView->ViewRect());
        TInt adjustment = newTopItemIndex % numOfItemsPerColumn;
        if (adjustment != 0)
            // adjust newTopItemIndex till it refers to the index of an item at the top of a column
            newTopItemIndex -= adjustment;
        TInt newBottomItemIndex = newTopItemIndex + (numOfColsThatFitInViewRect * numOfItemsPerColumn) - 1;
        if (currentItemIndex < newTopItemIndex)
            newTopItemIndex = colIndexOfTargetItem * numOfItemsPerColumn;
        else if (currentItemIndex > newBottomItemIndex)
            {
            TInt colIndexOfNewBottomItem = colIndexOfTargetItem;
            TInt colIndexOfNewTopItem = colIndexOfNewBottomItem - (numOfColsThatFitInViewRect - 1);
            newTopItemIndex = colIndexOfNewTopItem * numOfItemsPerColumn;
            }
        }
    else if ((newTopItemIndex != 0) && (numOfItemsPerColumn != 0))
        {
        TInt adjustment = newTopItemIndex % numOfItemsPerColumn;
        if (adjustment != 0)
            // adjust newTopItemIndex till it refers to the index of an item at the top of a column
            newTopItemIndex -= adjustment;
        }
    SetTopItemIndex(newTopItemIndex);
    iView->CalcDataWidth();
    UpdateScrollBarsL();
    iView->CalcBottomItemIndex();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikSnakingListBox::SizeChanged()
    {
    TRect clientRect = iBorder.InnerRect(Rect());
    SetViewRectFromClientRect(clientRect);
    TRAP_IGNORE(HandleViewRectSizeChangeL());
    }

EXPORT_C void CEikSnakingListBox::AdjustTopItemIndex() const
    {
    _AKNTRACE_FUNC_ENTER;
    // assumes we know # of items in the model
    TInt numOfItemsPerCol = iView->ViewRect().Height() / iItemHeight;
    numOfItemsPerCol = Max(1, numOfItemsPerCol);
    TInt numOfVisCols = iView->VisibleWidth(iView->ViewRect());
    TInt numOfItems = iModel->NumberOfItems();
    TInt colIndexOfRightmostCol = numOfItems / numOfItemsPerCol;
    TInt maxTopItemIndex = Max (0, (colIndexOfRightmostCol - (numOfVisCols - 1)) * numOfItemsPerCol);
    if (iView->TopItemIndex() > maxTopItemIndex)
        SetTopItemIndex(maxTopItemIndex);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikSnakingListBox::HandleDragEventL(TPoint aPointerPos)
    {
    _AKNTRACE_FUNC_ENTER;
    if (!(iListBoxFlags & ELeftDownInViewRect))
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }
    TRect ignoreDragRect(TPoint(aPointerPos.iX-20, aPointerPos.iY-20), TPoint(aPointerPos.iX+20, aPointerPos.iY+20));
    TRect viewRect(iView->ViewRect());
    TInt itemIndex;
    TBool pointerIsOverAnItem = iView->XYPosToItemIndex(aPointerPos, itemIndex);
    // SERIES60 LAF
#if 1 
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
#else
    CListBoxView::TSelectionMode selectionMode = (iListBoxFlags & EMultipleSelection) ? CListBoxView::EContiguousSelection : CListBoxView::ESingleSelection;
#endif
    // END OF SERIES60 LAF
    TInt oldCurrentItemIndex = iView->CurrentItemIndex();
    TRect currentItemRect(iView->ItemPos(oldCurrentItemIndex), iView->ItemSize(oldCurrentItemIndex));
    if (pointerIsOverAnItem)
        {
        // drag event occurred within the listbox
        iView->SetCurrentItemIndex(itemIndex);
        if (itemIndex != oldCurrentItemIndex) 
            {
            iView->SetCurrentItemIndex(itemIndex);
            iView->DrawItem(oldCurrentItemIndex);
            iView->UpdateSelectionL(selectionMode);
            iView->DrawItem(itemIndex);
            }
        }
    else if ((aPointerPos.iX < viewRect.iTl.iX) || (aPointerPos.iX > viewRect.iBr.iX))
        {
        // drag event occurred outside the listbox's viewRect
        if (aPointerPos.iX < viewRect.iTl.iX)
            iView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
        else if (aPointerPos.iX > viewRect.iBr.iX)
            iView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
        MoveToNextOrPreviousItemL(aPointerPos);     
        UpdateScrollBarThumbs();
        Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
//      Window().RequestPointerRepeatEvent(ListBoxLaf()->LBxPointerRepeatInterval(), ignoreDragRect);
        }
    else
        {
        // find item nearest to the pointer pos and make that the current item
        if (viewRect.Contains(aPointerPos))
            {
            }
        else
            {
            if (aPointerPos.iX > currentItemRect.iBr.iX)
                iView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
            else if (aPointerPos.iX < currentItemRect.iTl.iX)
                iView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
            MoveToNextOrPreviousItemL(aPointerPos);
            UpdateScrollBarThumbs();
            Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
//          Window().RequestPointerRepeatEvent(ListBoxLaf()->LBxPointerRepeatInterval(), ignoreDragRect);
            }
        }
    if (iView->CurrentItemIndex() != oldCurrentItemIndex)
        {
        iListBoxFlags |= EStateChanged;
        if (IsMatchBuffer())
            {
            ClearMatchBuffer();
            DrawMatcherCursor();
            }
        }
    }

EXPORT_C void CEikSnakingListBox::MoveToNextOrPreviousItemL(TPoint aPointerPos)
    {
    // AVKON LAF
#if 1
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
#else
    CListBoxView::TSelectionMode selectionMode = (iListBoxFlags & EMultipleSelection) ? CListBoxView::EContiguousSelection : CListBoxView::ESingleSelection;
#endif
    // END OF AVKON LAF
    TInt cix = iView->CurrentItemIndex();
    TRect currentItemRect(iView->ItemPos(cix), iView->ItemSize(cix));
    TInt numOfRows =  ((CSnakingListBoxView*)iView)->NumberOfItemsPerColumn();
    TBool currItemIsInLastRow = ((cix % numOfRows) == (numOfRows-1));
    TBool currItemIsLastItem = (cix == (iModel->NumberOfItems()-1));
    TBool currItemIsInFirstRow = ((cix % numOfRows) == 0);
    if ((aPointerPos.iY > currentItemRect.iBr.iY) && (! (currItemIsInLastRow || currItemIsLastItem)))
        iView->MoveCursorL(CListBoxView::ECursorNextItem, selectionMode);
    else if ((aPointerPos.iY < currentItemRect.iTl.iY) && (! currItemIsInFirstRow))
        iView->MoveCursorL(CListBoxView::ECursorPreviousItem, selectionMode);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikSnakingListBox::RestoreClientRectFromViewRect(TRect& aClientRect) const
    {
    aClientRect=iView->ViewRect();
    aClientRect.SetRect(aClientRect.iTl.iX - ListBoxMargins().iLeft, aClientRect.iTl.iY - ListBoxMargins().iTop,
        aClientRect.iBr.iX + ListBoxMargins().iRight, aClientRect.iBr.iY + ListBoxMargins().iBottom);
    if (!ViewRectHeightAdjustment())
        return;
    aClientRect.iBr.iY += ViewRectHeightAdjustment();
    }

EXPORT_C TInt CEikSnakingListBox::AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const
    {
    TInt remainder = aRect.Height() % iItemHeight;
    if (remainder != 0) 
        aRect.iBr.iY -= remainder;
    return remainder;
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSnakingListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
    {
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSnakingListBox::HandleResourceChange(TInt aType)
    {
    CCoeControl::HandleResourceChange(aType);
    }

EXPORT_C void CEikSnakingListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikListBox::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikSnakingListBox::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikSnakingListBox::Reserved_1()
    {}

EXPORT_C void CEikSnakingListBox::Reserved_2()
    {}

EXPORT_C void CEikSnakingListBox::CEikListBox_Reserved()
    {}
