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

#ifndef HGVGMEDIAWALL_H_
#define HGVGMEDIAWALL_H_

// INCLUDES
#include <coecntrl.h>
#include <coemain.h>
#include <EGL/egl.h>
#include <VG/openvg.h>
#include <ganes/HgBufferOwnerIface.h>
#include <ganes/HgScrollbarObserverIface.h>
#include <akntouchgesturefw.h>

// FORWARD DECLARATIONS
class MHgScrollBufferObserver;
class MHgSelectionObserver;
class CHgVgItem;
class CGulIcon;
class CHgScrollBufferManager;
class CHgVgScrollBar;
class CHgVgMediaWallRenderer;
class CHgVgSkinRenderer;
class CHgVgTimer;
class CHgVgPopup;
class CHgVgButton;
class MHgVgMediaWallObserver;
class CHgVgLabel;
class CHgVgEGL;
class THgVgSpring;
class CAlfCompositionSource;
class CFbsBitmap;

// CLASS DECLARATION
class CHgVgMediaWall : 
    public CCoeControl, 
    public MHgBufferOwner,
    public MHgScrollbarObserver,
    public MCoeForegroundObserver,
    public AknTouchGestureFw::MAknTouchGestureFwObserver
    {
public:
    
    /**
     * Style of the media wall to use.
     */
    enum THgVgMediaWallStyle
        {
        EHgVgMediaWallStyleCoverflowFullScreen,
        EHgVgMediaWallStyleCoverflowTBonePortrait,
        EHgVgMediaWallStyleCoverflowTBoneLandscape,
        EHgVgMediaWallStyleGrid,
        EHgVgMediaWallStyleUnknown
        };
    
    /**
     * Media walls current animation state.
     */
    enum THgVgAnimationState
        {
        EHgVgMediaWallAnimationStateIdle,
        EHgVgMediaWallAnimationStateTransition,
        EHgVgMediaWallAnimationStateFastTransition,
        EHgVgMediaWallAnimationStateOpening,
        EHgVgMediaWallAnimationStateClosing,
        EHgVgMediaWallAnimationStateItemOpened
        };
    
    /**
     * Media walls selection animation type.
     * Default behaviour is EHgSelectionAnimationFlipToFront.
     */
    enum THgVgOpeningAnimationType
        {
        EHgVgOpeningAnimationNone, // no animation takes place when item is tapped
        EHgVgOpeningAnimationFlipToFront, // flips the opened item by flip angle and fits to set opened item rect.
        EHgVgOpeningAnimationZoomToFront, // zooms the opened item to set opened item rect.
        EHgVgOpeningAnimationZoomIn // zooms the item to the back of the camera.        
        };
    
    /**
     * Event types, CHgVgMediaWall may send through MHgVgMediaWallObserver interface.
     */
    enum THgVgMediaWallEvent
        {
        EHgVgMediaWallEventRequestHideSoftkeys,
        EHgVgMediaWallEventRequestShowSoftkeys,
        EHgVgMediaWallEventButtonGotoNowPlaying,
        EHgVgMediaWallEventButtonBack
        };

    /**
     * Flags that define possible mediawall modes
     */
    enum THgVgMediaWallMode
        {
        EHgVgMediaWallDrawToWindowGC = 0x0001,
        EHgVgMediaWallFaded = 0x0002,
        EHgVgMediaWallUninitialized = 0x0004
        };
        
public: 
    
    /**
     * Creates new HgVgMediaWall.
     * 
     * @param aRect Rect that the control draws onto.
     * @param aItemCount Total count of items in the mediawall.
     * @param aStyle style of the mediawall.
     * @param aEnableScrollBar ETrue to enable scrollbar.
     * @param aDefaultIcon Default icon to be used.
     * 
     * @return HgVGMediaWall-object
     */
    IMPORT_C static CHgVgMediaWall* NewL ( const TRect& aRect, 
          TInt aItemCount,
          THgVgMediaWallStyle aStyle,
          TBool aEnableScrollBar,
          MObjectProvider* aParent,
          CGulIcon* aDefaultIcon = NULL); 
        
    // Destructor.
    IMPORT_C virtual ~CHgVgMediaWall();
    
public: // CCoeControl

    void Draw(const TRect& aRect ) const;
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aEvent );
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    void FocusChanged(TDrawNow aDrawNow);
    void HandleResourceChange(TInt aType);
    
private: // MHgBufferOwner
    void Release(TInt aReleaseStart, TInt aReleaseEnd);

private: // MHgScrollbarObserver

    void ScrollBarPositionChanged( const TPoint& aNewPosition );

    void HandleNaviStripChar( const TChar& aChar );

public: //MCoeForegroundObserver
    void HandleGainingForeground();
    void HandleLosingForeground();
    
private: // MAknTouchGestureFwObserver
    
    void HandleTouchGestureL( AknTouchGestureFw::MAknTouchGestureFwEvent& aEvent );    
    
public: // NEW FUNCTIONS
    /**
     * Re-inits rendering for new window rectangle.
     * 
     * @param aRect New display rect
     */
    IMPORT_C void InitScreenL( const TRect& aRect );
    
    /**
     * Refreshes screen.
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
    IMPORT_C CHgVgItem& ItemL( TInt aIndex );
    
    /**
     * Resets item at the index position. Old item is deleted.
     * 
     * @param aItem New item. Ownership transferred.
     * @param aIndex The index of the item.
     */
    IMPORT_C void SetItem(CHgVgItem* aItem, TInt aIndex);

    /**
     * Adds Item.
     * 
     * @param aItem New item. Ownership transferred.
     */
    IMPORT_C void AddItem(CHgVgItem* aItem);

    /**
     * Inserts item at index postion.
     * 
     * @param aItem New item. Ownership transferred.
     * @param aIndex The index of the item.
     */
    IMPORT_C void InsertItem(CHgVgItem* aItem, TInt aIndex);

    /**
     * Removes item at index position. Removed item is deleted.
     * 
     * @param aIndex The index of the item.
     */
    IMPORT_C void RemoveItem(TInt aIndex);

    /**
     * Returns index of currently selected item in MediaWall. 
     * In the case of EHgVgMediaWallStyleStyleGrid this method can only
     * return indices of the items at top row. The index of the item picked
     * by user is on grids case only passed through MHgSelectionObserver interface.
     * 
     * @return Selected index (KErrNotFound if nothing is selected)
     */
    IMPORT_C TInt SelectedIndex();

    /**
     * Sets selected index. Positions the mediwall into this index.
     * In case of a grid. The mediawall is positioned into row = aIndex / RowCount.
     * @param aIndex new selected index. Selection is also made visible.
     */
    IMPORT_C void SetSelectedIndex( TInt aIndex );
    
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
     * Sets new default icon.
     * @param aDefaultIcon New default icon to be used in scroller.
     */
    IMPORT_C void SetDefaultIconL( CGulIcon* aDefaultIcon );
    
    /**
     * Disables Scrollbuffer.
     */
    IMPORT_C void DisableScrollBuffer();
    
    /**
     *  Changes mediawalls style.
     *  
     *  @param aStyle style.
     *  @param aRect new window rectangle.
     *  @param aReuseSurface flag to indicate whether or not OpenVG surface should be reconstructed.
     */
    IMPORT_C void ChangeStyleL( THgVgMediaWallStyle aStyle, const TRect& aRect, TBool aReuseSurface );
    
    /**
     * Sets button observer. Client can use this to register it self to be 
     * notified when the user for example, presses hide softkeys button.
     * 
     * @param aObserver observer.
     */
    IMPORT_C void SetObserver(MHgVgMediaWallObserver* aObserver);
    
    /**
     * Sets type of selection animation to perform, when an item
     * is opened.
     * Default behaviour is EHgSelectionAnimationFlipToFront.
     * 
     * @param aType type of opening animation.
     */
    IMPORT_C void SetOpeningAnimationType(THgVgOpeningAnimationType aType);
    
    /**
     * Gets current MediaWall style.
     * 
     * @return THgVgMediaWallStyle.
     */
    IMPORT_C THgVgMediaWallStyle Style() const;
    
    /**
     * Gets current opening animation type
     * 
     * @return THgVgOpeningAnimationType.
     */
    IMPORT_C THgVgOpeningAnimationType OpeningAnimationType() const;
    
    /**
     * Starts opening animation to selected direction. After animation is complete,
     * Open event is sent to selection observer.
     * 
     * @param aOpening if this is true, the selected item is opened, otherwise closed.
     */
    IMPORT_C void StartOpeningAnimationL(TBool aOpening);
    
    /**
     * Set mode flags. Possible values are defined in THgVgMediaWallMode.
     * @param aFlags flags to bet set.
     */
    IMPORT_C void SetFlags( TInt aFlags );
    
    /**
     * Clear mode flags. Possible values are defined in THgVgMediaWallMode.
     * @param aFlags flags to be cleared.
     */
    IMPORT_C void ClearFlags( TInt aFlags );
    
    /**
     * Get flags. Possible values are defined in THgVgMediaWallMode.
     * @return Current flags.
     */
    IMPORT_C TInt Flags();
    
    /**
     * Sets item at index as selected and opened item. HandleOpenL not called for observers.
     * If index is out of range, does nothing. Using this function sets item at index
     * to the state where it is when it was selected and opened by the user.
     * One can use for example. StartOpeningAnimationL to togle animation backwards from
     * this state to normal. This can be useful for example. when returning from a 
     * a different view and there is a need to pop the item back to the wall from front.
     * 
     * @param aIndex of the item to open.  
     */
    IMPORT_C void SetItemToOpenedState(TInt aIndex);
    
    /**
     * Sets the rectangle where item fit at the end of opening animation.
     * 
     * @param aRect target rectangle where opened item is fitted at the end of opening animation.
     */
    IMPORT_C void SetOpenedItemRect(const TRect& aRect);
                        
protected: // Constructors
    
    CHgVgMediaWall( TInt aItemCount, 
            CGulIcon* aDefaultIcon, THgVgMediaWallStyle aStyle, 
            TBool aEnableScrollBar );

    void ConstructL (const TRect& aRect, MObjectProvider* aParent );
    
private:

    /**
     * Handles viewposition change.
     */
    void HandleViewPositionChanged(TBool aDontUpdateObserver=EFalse);
            
    /**
     * Initializes items.
     */
    void InitItemsL();
    
        
    /**
     * 
     */
    void HandleKeyDown();

    /**
     * Handles key events.
     * 
     * @param aKeyEvent TKeyEvent-object.
     */
    TKeyResponse HandleKeyEvent(const TKeyEvent& aKeyEvent);
    
    /**
     * 
     */
    void HandleKeyUp();
    
    /**
     * 
     */
    void StopKeyScrolling();
    
    /**
     * 
     */
    void DoKeyScrolling();
    
    /**
     * 
     */
    static TInt KeyScrollingTimerCallback( TAny* aPtr );
        
    /**
     * Handles items count change.
     */
    void HandleItemCountChanged();
                
    /**
     * Initializes default icon and
     * creates VGImage for it.
     */
    void InitDefaultIconL();
        
    /**
     * Draws using OpenVG
     */
    void DrawOpenVG() const;
                                
    /**
     * Called by callback to do actual animation.
     */
    void DoAnimation();
    
    /**
     * Does transition animation, called by DoAnimation.
     */
    TBool DoTransitionAnimation();
        
    /**
     * Does selection animation
     */
    TBool DoSelectionAnimation();
    
    /**
     * Callback method for animation
     *
     * @param aPtr Pointer to an instance of CHgVgMediaWall class.
     *
     * @return System wide error code.
     */
    static TInt AnimationTimerCallback( TAny* aPtr );
                    
    /**
     * Updates bitmaps used to render album and artist titles.
     */
    void UpdateLabelsAndPopup();

    /**
     * Draws album and artist titles.
     */
    void DrawTitles(TReal aAlpha);
        
    
    /**
     * Initializes scroll bar.
     */
    void InitScrollBarL(TBool aResize);
    
    /**
     * Initializes skin rendering.
     */
    void InitSkinRendererL();
    
    /**
     * Initializes whole rendering functionality.
     */
    void InitRenderingL(TBool aRecreateSurface);
    
    /**
     * Frees videomemory used by items.
     */
    void FreeItemsImages();
    
    /**
     * Reloads images to items.
     */
    void ReloadItemsImages();
    
    /**
     * 
     */
    void HandleTapEventL(const TPoint& aPosition);
        
    /**
     * 
     */
    void HandleFlick(const TPoint& aSpeed);
 
    /**
     *
     */ 
    void HandleDragging(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent);
    
    /**
     * 
     */
    TInt GetStepsFromSpeed(TInt aSpeed) const;
    
    /**
     * 
     */
    void StartAnimationTimer();
                       
    /**
     * 
     */
    TReal GetAsPercentageOfScreenWidth(TInt aPixels) const;
    
    /**
     * 
     */
    TReal GetAsPercentageOfScreenHeight(TInt aPixels) const;
        
    /**
     * 
     */
    void DrawScene();
            
    /**
     * 
     */
    void HandleDragStart(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent);
    
    /**
     * 
     */
    void HandleDragOn(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent);
    
    /**
     * 
     */
    void HandleDragStop(const AknTouchGestureFw::MAknTouchGestureFwDragEvent& aEvent);
        
    /**
     * 
     */
    void HandleTransitionAnimationStop();
        
    /**
     * 
     */
    void DrawLetterStripAndTitles();
    
    /**
     * 
     */
    void DrawButtonsAndScrollbar();
       
    /**
     * 
     */
    void InitButtonsL();
           
    /**
     * 
     */
    CGulIcon* CreateIconL(TInt aId1, TInt aId2, const TSize& aSize);

    /**
     * 
     */
    TBool HandleButtons(const TPointerEvent& aEvent);
    
    /**
     * 
     */
    TInt MaxViewPosition() const;
    
    
    /**
     * 
     */
    TBool BeginSelection(TInt aIndex);
    
    /**
     * 
     */
    void EndSelection();
    
    /**
     * 
     */
    void DoStartOpeningAnimationL();
    
    /**
     * 
     */
    void StartAnimationToPosition(TReal aX, TBool aUpdateScrollBar);
       
    /**
     * 
     */
    void StartAnimationToPosition(TReal aX, TReal aY, TBool aUpdateScrollBar);

    /**
     * 
     */
    CFbsBitmap* DrawToBitmap();
    
    /**
     * 
     */
    void DestroyRendering();
    
    /**
     * 
     */
    TBool DrawAll();
    
    /**
     * 
     */
    void InitMediaWallFullScreenLandscapeL();
    
    /**
     * 
     */
    void InitMediaWallTBonePortraitL();
    
    /**
     * 
     */
    void InitMediaWallGridLandscapeL();

    /**
     * 
     */
    void InitLabelsL(TInt aLayoutVariant);
    
    /**
     * 
     */
    void InitPopupL(TInt aLayoutVariant);
    
    /**
     * 
     */
    static TInt DelayedInit( TAny* aSelf);
    
    /**
     * 
     */
    void FillSystemGcWithSkin( ) const;
    
    /**
     * 
     */
    void SetConstantsForStyle();

protected:
    CHgScrollBufferManager* iManager; // Own
    
    HBufC* iEmptyText; // text for empty list or grid.
    
    // Observers
    MHgSelectionObserver* iSelectionObserver; // Not Own
    
    // Arrays
    RPointerArray<CHgVgItem> iItems; // Items

    // For dragging
    TTime iPrevTime; // Previous pointer position time.
                
    TInt iItemCount; // Total number of items
    
    TInt iItemsOnScreen; // Max items on screen.    
        
    TInt iSelectedIndex; // The index of the selected item
                                    
    CGulIcon* iDefaultIcon; // Default item icon, owns
                
    THgVgAnimationState iAnimationState; // current animation state
    TInt64 iAnimationDuration; // total length of the animation    
    TTime iAnimationStartTime; // starting time of the animation   
    TReal iAnimationAlpha; // value going from 0-1 during animation    
    CHgVgTimer* iAnimationTimer;  
             
    TBool iScrollBarEnabled;
    CHgVgScrollBar* iScrollBar; // Scrollbar, owns
    TBool iScrollBarHit;
    TBool iUpdateScrollBar;
    
    CHgVgMediaWallRenderer* iRenderer; // Renderer for current media wall style, owns
            
    CHgVgSkinRenderer* iSkinRenderer; // Renderer for drawing skin, owns.

    THgVgMediaWallStyle iMediaWallStyle; // Style of mediawall.
                                
    //TTime iKeyPressStartTime;
 
    AknTouchGestureFw::CAknTouchGestureFw* iTouchFw; // touch gesture fw, own.
    
    TReal iViewPositionAtDragStart;
    
    CHgVgPopup* iLetterPopup; // letter popup show when using scrollbar, own.
    
    CHgVgButton* iHideSKButton; // button for hiding softkeys, own.
    
    MHgVgMediaWallObserver* iMediaWallObserver;
    
    TRect iRect;
    
    THgVgOpeningAnimationType iOpeningAnimationType;
        
    TInt iPreviousPointerDelta;

    TBool iIsForeground;
    TBool iUsingDefaultIcon;
            
    TBool iButtonsHit;
        
    TBool iPointerDown; 
    
    CHgVgLabel* iArtistLabel; // label for artist text, own.
    CHgVgLabel* iAlbumLabel; // label for album text, own.
    CHgVgLabel* iEmptyLabel; // label for empty text, own.

    enum TKeyScrollingState
        {
        ENoKeyScrolling = 0,
        EKeyScrollingUp,
        EKeyScrollingDown,
        EKeyScrollingLeft,
        EKeyScrollingRight
        } iKeyScrollingState; // State of the key scrolling
    
    TInt iKeyRepeats;
    CPeriodic* iKeyScrollingTimer; // Timer for key scrolling, own.    

    CHgVgEGL* iEGL; // encapsulated egl stuff, own.
    
    TInt iRowCount; // number of rows in grid style

    TReal iCameraRotationFactor; // max amount of camera rotation in radians
    TReal iCameraZoomFactor; // max amount of zoom out
    TReal iSpringVelocityToAnimationFactor; // factor used to convert spring velocity to animation alpha
    
    RBuf iPopupText1; // text1 shown in popup 
    RBuf iPopupText2; // text2 shown in popup
                
    TBool iSelectionMode; // used to indicate when user is selectin items in grid style
    
    THgVgSpring* iSpring; // spring physics simulator, own.
    
    TInt iBufferPosition;
    
    CHgVgItem* iTempItem;

    TInt iPickedGridItem; // item picked from grid
    
    TInt iPrevGridItem; // prev item selected from grid
    TInt iSelGridItem; // selected it from grid
    
    TReal iItemsToMoveOnFullScreenDrag;
    
    TInt iFlags;
    
    CAlfCompositionSource* iCompositionSource;    
    
    CFbsBitmap* iSurfaceBitmap;
    CPeriodic* iDelayedInit;

    
    TBool iFirstTime;

    TReal iSpringDragVel;
    TReal iSpringVelAtDragStart;
    TInt iDragFrames;
    TBool iObserverNotified;

    TRect iOpenedItemRect;
    };

       
#endif /*HGVGMEDIAWALL_H_*/
