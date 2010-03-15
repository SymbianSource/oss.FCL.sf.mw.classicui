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


#ifndef HGSCROLLER_H_
#define HGSCROLLER_H_

// INCLUDES
#include <coecntrl.h>
#include <coemain.h>

#include <aknphysicsobserveriface.h>
#include <aknlongtapdetector.h>
#include <akncollection.h>
#include <ganes/HgBufferOwnerIface.h>
#include <ganes/HgScrollbarObserverIface.h>

// FORWARD DECLARATIONS
class CAknPhysics;
class MHgScrollBufferObserver;
class MHgSelectionObserver;
class MHgMarkingObserver;
class CHgItem;
class CHgScrollbar;
class CGulIcon;
class CHgScrollBufferManager;
class THgPopupDrawer;
class CHgIndicatorManager;
class CHgDrawUtils;
class CHgKeyUtils;
class CHgTextFind;
class CAknItemActionMenu;
class CFont;

// CLASS DECLARATION
class CHgScroller : 
    public CCoeControl, 
    public MHgBufferOwner,
    public MHgScrollbarObserver,
    public MCoeForegroundObserver,
    public MAknPhysicsObserver,
    public MAknLongTapDetectorCallBack,
    public MAknCollection
    {
public:
    
    // Flags that define possible scroller modes
    enum THgScrollerMode
        {
        EHgScrollerSelectionMode = 0x0001,
        EHgScrollerSearchWithQWERTY = 0x0002,
        EHgScrollerKeyMarkingDisabled = 0x0004,
        EHgScrollerScreenFreeze = 0x0008,
        EHgScrollerForceDoubleClick = 0x0010,
        EHgScrollerFlatStatusPane = 0x0020
        };

    // Scrollbar types
    enum THgScrollBarType
        {
        EHgScrollerScrollBar = 0,
        EHgScrollerLetterStrip,
        EHgScrollerTimeStrip,
        EHgScrollerLetterStripLite
        };
    
public: // Destructor.
    IMPORT_C virtual ~CHgScroller();
    
public: // CCoeControl
    void Draw(const TRect& aRect ) const;
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aEvent );
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    virtual TCoeInputCapabilities InputCapabilities() const;
    virtual void FocusChanged(TDrawNow aDrawNow);
    virtual void HandleResourceChange(TInt aType);

protected: // MAknPhysicsObserver
    void ViewPositionChanged( const TPoint& aNewPosition,
                                  TBool aDrawNow,
                                  TUint aFlags );
    void PhysicEmulationEnded();
    TPoint ViewPosition() const;
    
private: // MHgBufferOwner
    void Release(TInt aReleaseStart, TInt aReleaseEnd);

private: // MHgScrollbarObserver
    void ScrollBarPositionChanged( const TPoint& aNewPosition );
    void HandleNaviStripChar( const TChar& aChar );

protected: // MAknLongTapDetectorCallBack
    void HandleLongTapEventL( const TPoint& aPenEventLocation,
                            const TPoint& aPenEventScreenLocation);
    
protected: // MAknCollection
    TUint CollectionState() const;
    void ItemActionMenuClosed();
    TInt CollectionExtension( TUint aExtensionId, TAny*& a0, TAny* a1 );

public: // NEW FUNCTIONS
    /**
     * Re-inits the grid display area. DSA version.
     * 
     * @param aRect New display rect
     * @param aSession Window server session for DSA
     */
    IMPORT_C void InitScreenL( const TRect& aRect, RWsSession& aSession );
    
    /**
     * Re-inits the grid display area. Non-DSA version.
     * 
     * @param aRect New display rect
     */
    IMPORT_C void InitScreenL( const TRect& aRect );
    
    /**
     * Refreshes screen.
     * @param aIndex Index that was modified.
     */
    IMPORT_C void RefreshScreen( TInt aIndex );

    /**
     * Gives the first index on the screen.
     * 
     * Note: The index is not guaranteed to be in the range of the scroller items.
     * Index can be negative if the scroller is scrolled to the way up or 
     * over the count - 1 if scrolled way down.   
     * 
     * @return The index of the first item on the screen. 
     */
    IMPORT_C TInt FirstIndexOnScreen();
    
    /**
     * How many items fit on one screen. 
     * @return Item count.
     */
    IMPORT_C TInt ItemsOnScreen();
    
    /**
     * Get item at specified index.
     * 
     * @param aIndex Index of the item that is returned
     * @return Reference to item.
     */
    IMPORT_C CHgItem& ItemL( TInt aIndex );
    
    /**
     * Resets item at the index position. Old item is deleted.
     * 
     * @param aItem New item. Ownership transferred.
     * @param aIndex The index of the item.
     */
    IMPORT_C void SetItem(CHgItem* aItem, TInt aIndex);

    /**
     * Adds Item.
     * 
     * @param aItem New item. Ownership transferred.
     */
    IMPORT_C void AddItem(CHgItem* aItem);

    /**
     * Inserts item at index postion.
     * 
     * @param aItem New item. Ownership transferred.
     * @param aIndex The index of the item.
     */
    IMPORT_C void InsertItem(CHgItem* aItem, TInt aIndex);

    /**
     * Removes item at index position. Removed item is deleted.
     * 
     * @param aIndex The index of the item.
     */
    IMPORT_C void RemoveItem(TInt aIndex);

    /**
     * @return Selected index (KErrNotFound if nothing is selected)
     */
    IMPORT_C TInt SelectedIndex();

    /**
     * Sets selected index.
     * @param aIndex new selected index. Selection is also made visible.
     */
    IMPORT_C void SetSelectedIndex( TInt aIndex );
    
    /**
     * Marks item at index position.
     * @param aIndex Index of the item that is marked.
     */
    IMPORT_C void Mark( TInt aIndex );

    /**
     * Unmarks item at index position.
     * @param aIndex Index of the item that is unmarked.
     */
    IMPORT_C void UnMark( TInt aIndex );
    
    /**
     * Marks all items.
     */
    IMPORT_C void MarkAll();

    /**
     * Unmarks all items.
     */
    IMPORT_C void UnMarkAll();
    
    /**
     * Gets all marked item indexes.
     * @param aIndexes On return contains the indexes of marked items.
     */
    IMPORT_C void GetMarkedItemsL( RArray<TInt>& aIndexes );
    
    /**
     * Enables Buffering.
     * @param aObserver Buffer change observer.
     * @param aBufferSize The size of the buffer.
     * @param aBufferTreshold The minimum change needed for buffer to be modified.
     */
    IMPORT_C void EnableScrollBufferL( MHgScrollBufferObserver& aObserver, 
            TInt aBufferSize,
            TInt aBufferTreshold );
    
    /**
     * Sets selection observer.
     * @param aObserver Selection observer.
     */
    IMPORT_C void SetSelectionObserver( MHgSelectionObserver& aObserver );

    /**
     * Sets marking observer.
     * @param aObserver marking observer.
     */
    IMPORT_C void SetMarkingObserver( MHgMarkingObserver& aObserver );
    
    /**
     * Removes all items and presents empty text
     * */
    IMPORT_C void Reset();
    
    /**
     * Resizes Grid/List.
     * @param aItemCount New Count of items.
     */
    IMPORT_C void ResizeL( TInt aItemCount );

    /**
     * Set text that is displayed when there are no items in the view.
     * @param aEmptyText Empty text.
     */
    IMPORT_C void SetEmptyTextL( const TDesC& aEmptyText );
    
    /**
     * Fetch item count.
     * @return Total number of items.
     */
    IMPORT_C TInt ItemCount() const;
    
    /**
     * Set scrollbar type.
     * @param aType ScrollBar type
     */
    IMPORT_C void SetScrollBarTypeL( THgScrollBarType aType );
    
    /**
     * Set mode flags. Possible values are defined in THgScrollerMode.
     * @param aFlags flags to bet set.
     */
    IMPORT_C void SetFlags( TInt aFlags );
    
    /**
     * Clear mode flags. Possible values are defined in THgScrollerMode.
     * @param aFlags flags to be cleared.
     */
    IMPORT_C void ClearFlags( TInt aFlags );
    
    /**
     * Get flags. Possible values are defined in THgScrollerMode.
     * @return Current flags.
     */
    IMPORT_C TInt Flags();
    
    /**
     * Highlights item based on the descriptor given.
     * @param aHighlightText Text to be searched.
     * @return Was aHighlightText found.
     */
    IMPORT_C TBool HightlightItem( const TDesC& aHighlightText );
    
    /**
     * Sets new default icon.
     * @param aDefaultIcon New default icon to be used in scroller.
     */
    IMPORT_C void SetDefaultIconL( CGulIcon* aDefaultIcon );
    
    /**
     * Disables Scrollbuffer.
     */
    IMPORT_C void DisableScrollBuffer();

    // Selection modes. Used in internal key marking implemention.
    enum TSelectionMode
        {
        ENoSelection = 0,
        ESelectionPossible,
        ESelectionMark,
        ESelectionUnMark
        };
    
    /**
     * Set selection mode. Used in internal key marking implemention.
     * @param aMode New selection mode.
     */
    void SetSelectionMode( TSelectionMode aMode );
    
    /**
     * Get current selection mode. Used in internal key marking implemention.
     * @return Current selection mode.
     */
    TSelectionMode SelectionMode() const;
    
protected: // Pure Virtual Functions
    virtual TInt GetSelected( TPoint aPosition ) const = 0;
    virtual void HandleSizeChanged() = 0;
    virtual void InitItemsL() = 0;
    virtual TSize TotalSize() const = 0;
    virtual void DoDraw( const TRect& aRect ) const = 0;
    virtual TBool DoHandleKeyEvent( const TKeyEvent& aKeyEvent ) = 0;
    virtual void FitSelectionToView() = 0;
    virtual TInt CurrentIndex() = 0;
    virtual TBool IsDisplayed( TInt aIndex ) = 0;
    virtual void FitTopItemToView( TInt aIndex ) = 0;
    virtual void HandleScrollbarVisibilityChange(TBool aVisible) = 0;
    
protected: // Constructors
    CHgScroller( TInt aItemCount, 
            CGulIcon* aDefaultIcon );

    void ConstructL (const TRect& aRect, RWsSession* aSession );
    
protected:
    void InitPhysicsL();
    virtual void HandleViewPositionChanged( TBool aUpdateScrollbar = ETrue );
    void InitDrawBuffer() const;
    void SelectionChanged();
    void FitRowToView( TInt aRow );
    TBool HasHighlight() const;
    static TInt MarqueeCallback( TAny* aSelf );

private:
    TKeyResponse HandleKeyEvent(const TKeyEvent& aKeyEvent);
    
    void HandleItemCountChanged();
    void HandleSelectionL();

    TBool HandleScrollbarEventL( const TPointerEvent& aEvent );
    void HandleDownEventL( const TPointerEvent& aEvent );
    void HandleDragEventL( const TPointerEvent& aEvent );
    void HandleUpEventL( const TPointerEvent& aEvent );
    
    void KeyEventDown();
    void KeyEventUp();
    
    void InitGraphicsL();
    void InitScrollbarL();

    void HandleGainingForeground();
    void HandleLosingForeground();
    
    /**
     * Launches the highlight timer.
     */
    void LaunchHighlightTimer();

    /**
     * Callback method for highlight timer.
     *
     * @param aPtr Pointer to an instance of CHgScroller class.
     *
     * @return System wide error code.
     */
    static TInt HighlightTimerCallback( TAny* aPtr );
        
    /**
     * Sets highlight to focused item.
     */
    void SetHighlightL();

    /**
     * Callback method for key scrolling timer.
     *
     * @param aPtr Pointer to an instance of CHgScroller class.
     *
     * @return System wide error code.
     */
    static TInt KeyScrollingTimerCallback( TAny* aPtr );
        
    /**
     * Move view based on key scolling mode.
     */
    void DoKeyScrolling();
    
    /**
     * Sets item highlight and stops the scrolling timer.
     */
    void StopKeyScrolling();
    
    void ReleasePopupFont();
    
protected:
    CAknPhysics* iPhysics; // Physics engine. Own
    CHgScrollBufferManager* iManager; // Own
    CHgScrollbar* iScrollbar; // Scrollbar. Own
    CHgIndicatorManager* iIndicatorManager; // Utility for drawing indicators. Own
    CHgDrawUtils* iDrawUtils; // Drawing utility. Own
    CHgTextFind* iTextFind; // Text find utility to communicate with FEP. Own
    CAknLongTapDetector* iDetector; // Longtap detector for single click. Own
    CAknItemActionMenu* iActionMenu; // Item action menu for single click. Not Own
    CFont* iPopupFont; // font to be used with popup drawer
    
    // Observers
    MHgSelectionObserver* iSelectionObserver; // Not Own
    MHgMarkingObserver* iMarkingObserver; // Not Own
    
    // Arrays
    RPointerArray<CHgItem> iItems; // Items

    // For dragging
    TPoint iStart; // Drag start position
    TTime iStartTime; // Drag start time
    TPoint iPrev; // Previous pointer event position.

    // The Rest.
    CGulIcon* iDefaultIcon; // Default item icon
        
    TPoint iViewPosition; // Current view position
    
    TBool iLandscapeScrolling; // Scrolling landscape?
    
    TInt iWidth; // The width of the view
    TInt iHeight; // The height of the view
    TInt iRowHeight; // Row height (square images)
    TInt iItemCount; // Total number of items
    TInt iItemsOnScreen;
    
    TInt iCurrentRow; // The number of the first row that is drawn
    TInt iSelectedIndex; // The index of the selected item

    TInt iKeyRepeats; // How many key repeasts have been received
    
    TSize iImageSize; // Image Size
    TSize iIndicatorSize; // Size of the indicator in list or grid
    
    enum TKeyScrollingState
        {
        ENoKeyScrolling = 0,
        EKeyScrollingUp,
        EKeyScrollingDown,
        EKeyScrollingLeft,
        EKeyScrollingRight
        } iKeyScrollingState; // State of the key scrolling

    TInt iFlags; // Possible mode flags
    
    HBufC* iEmptyText; // text for empty list or grid.

    THgPopupDrawer* iPopupDrawer;
    TBool iPanning;
    TBool iShowHighlight;
    
    THgScrollBarType iScrollBarType; // Scrollbar type
    
    RBuf iUpperCaseTitle; // Used in search for uppercase conversion
    RBuf iPopupText1;
    RBuf iPopupText2;
    
    TBool iFirstTime; // Flag to indicating first time run.
    TBool iPointerDown;

    CPeriodic* iHighlightTimer; // Higlight timer, own.
    TBool iSelectionToFocusedItem; // Is focused item clicked
    TInt iFocusedIndex; // highlight timer updates this value
    
    CHgKeyUtils* iKeyUtils; // MSK key handler, own
    
    TSelectionMode iSelectionMode;
    
    CPeriodic* iKeyScrollingTimer; // Timer for key scrolling, own.
    };

#endif /*HGSCROLLER_H_*/
