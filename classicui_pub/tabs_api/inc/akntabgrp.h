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
* Description:  Tab control for the status pane's navigation pane.
*
*/


#ifndef AKNTABGRP_H
#define AKNTABGRP_H

//  INCLUDES
#include <AknControl.h>
#include <coeccntx.h>
#include <coecobs.h>
#include <AknNaviDecoratorObserver.h>
#include "aknconsts.h"
#include "AknUtils.h"

#include <avkon.mbg>


// FORWARD DECLARATIONS

class CEikLabel;
class CEikImage;
class CAknTabGroup;
class CAknTabGroupExtension;
class MAknTabObserver;
class MAknNaviDecoratorObserver;
class TAknWindowLineLayout;
class CAknTabExtension;

/**
*  Tab item control used inside a tab group.
*
*  @lib avkon.lib
*  @since 0.9
*/
NONSHARABLE_CLASS( CAknTab ) : public CAknControl
    {
friend class CAknTabGroup;

public:

    /**
    * Indicates a tab title's type
    */
    enum TAknTabDataType
        {
        /** Tab title is empty.*/
        EAknTabNone,
        /** Tab title has only text. */
        EAknTabText,
        /** Tab title has only icon */
        EAknTabIcon,
        /** Tab title has both text and icon. */
        EAknTabTextAndIcon
        };

public:

    /**
    * Destructor
    */
    ~CAknTab();

    /**
    * Two-phased constructor.
    *
    * @param  aParent  Reference to parent control.
    * @param  aReader  Reference to resource reader.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewL( const CCoeControl& aParent,
                          TResourceReader& aReader );

    /**
    * Two-phased constructor.
    *
    * @param  aParent  Reference to parent control.
    * @param  aReader  Reference to resource reader.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewLC( const CCoeControl& aParent,
                           TResourceReader& aReader );

    /**
    * Two-phased constructor.
    *
    * @param  aId       Tab ID.
    * @param  aParent   Reference to parent control.
    * @param  aTabText  Reference to title text.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewL( TInt aId,
                          const CCoeControl& aParent,
                          const TDesC& aTabText );

    /**
    * Two-phased constructor.
    *
    * @param  aId       Tab ID.
    * @param  aParent   Reference to parent control.
    * @param  aTabText  Reference to title text.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewLC( TInt aId,
                           const CCoeControl& aParent,
                           const TDesC& aTabText );

    /**
    * Two-phased constructor.
    *
    * @param  aId         Tab ID.
    * @param  aParent     Reference to parent control.
    * @param  aTabText    Reference to title text.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewL( TInt aId,
                          const CCoeControl& aParent,
                          const TDesC& aTabText,
                          const CFbsBitmap* aTabBitmap,
                          const CFbsBitmap* aMask = NULL );

    /**
    * Two-phased constructor.
    *
    * @param  aId         Tab ID.
    * @param  aParent     Reference to parent control.
    * @param  aTabText    Reference to title text.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewLC( TInt aId,
                           const CCoeControl& aParent,
                           const TDesC& aTabText,
                           const CFbsBitmap* aTabBitmap,
                           const CFbsBitmap* aMask = NULL );

    /**
    * Two-phased constructor.
    *
    * @param  aId         Tab ID.
    * @param  aParent     Reference to parent control.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewL( TInt aId,
                          const CCoeControl& aParent,
                          const CFbsBitmap* aTabBitmap,
                          const CFbsBitmap* aMask = NULL );

    /**
    * Two-phased constructor.
    *
    * @param  aId         Tab ID.
    * @param  aParent     Reference to parent control.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    *
    * @return A pointer to constructed @c CAknTab object.
    */
    static CAknTab* NewLC( TInt aId,
                           const CCoeControl& aParent,
                           const CFbsBitmap* aTabBitmap,
                           const CFbsBitmap* aMask = NULL );

    /**
    * Replace the tab title.
    *
    * @param  aTabText  New title text.
    */
    void ReplaceTextL( const TDesC& aTabText );

    /**
    * Activate or deactive this tab.
    *
    * @param  aActive   @c ETrue for activation, @c EFalse for deactivation.
    * @param  aDrawNow  Indicates whether control need to be redrawn.
    */
    void SetActive( TBool aActive, TDrawNow aDrawNow );

    /**
    * Determines whether this tab is active.
    *
    * @return @c ETrue if a tab is active, @c EFalse if not.
    */
    TBool Active() const;

    /**
    * Gets tab's ID.
    *
    * @return Tabs' ID.
    */
    TInt Id() const;

    /**
    * Gets this tab's type.
    *
    * @return Tab's type.
    */
    enum TAknTabDataType TabType() const;


    /**
    * Sets the total amount of tabs in the tabgroup where this tab belongs to.
    */
    void SetTotalAmountOfTabs( TInt aAmount );

    /**
    * Sets the narrow tab layout.
    * @internal Used by the UI framework.
    * Applications can set the narrow layout using @c CAknNaviDecorator class.
    */
    void SetNarrowTabLayout( TBool aNarrow );
    
    /**
    * Sets the flag indicating whether or not this tab contains
    * a multi-colored title icon.
    *
    * The multi-color mode should be used with color icons,
    * otherwise the tab icon is drawn using a color
    * defined in the current skin.
    * 
    * @param  aMultiColor  @c ETrue to set the multi-color mode on,
    *                      @c EFalse to turn it off.
    */
    void SetMultiColorMode( TBool aMultiColor );
    
    /**
    * Checks whether or not this tab is drawn using multi-color mode or not.
    *
    * @return @c ETrue if this tab contains a multi-color icon,
    *         @c EFalse otherwise.
    */
    TBool MultiColorMode() const;
    
    /**
    * Sets the long tab layout.
    * @internal Used by the UI framework.
    */
    void SetLongTabLayout( TBool aLongTab );

public: // From base class @c CCoeControl.

    /**
    * Gets the minimum size of the tab.
    *
    * @return Minimum size of the tab.
    */
    virtual TSize MinimumSize();

    /**
    * Sets the tab dimmed.
    *
    * @param  aDimmed  @c ETrue to dim the control,
    *                  @c EFalse to set the control as not dimmed.
    */
    virtual void SetDimmed( TBool aDimmed );

    /**
    * Gets the list of logical colors employed
    * in the drawing of the control, paired with an explanation of how
    * they are used. Appends the list into @c aColorUseList.
    *
    * @param[in,out]  aColorUseList  The color list.
    */
    virtual void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList ) const;

protected: // From base class @c CCoeControl.

    /**
    * Responds to size changes events to sets the size and
    * position of the contents of this control.
    */
    virtual void SizeChanged();

    /**
    * Gets the number of controls contained in a compound control.
    *
    * @return The number of component controls contained by this control.
    */
    virtual TInt CountComponentControls() const;

    /**
    * Gets the specified component of a compound control.
    *
    * @param  aIndex  The index of the control to get.
    *
    * @return The component control with an index of @c aIndex.

    */
    virtual CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * Handles pointer events.
    * This function is called by framework whenever a pointer event
    * occurs in the control.
    *
    * @param  aPointerEvent  The pointer event.
    */
    virtual void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // From base class @c CAknControl.

    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // From base class @c CCoeControl.

    virtual void Draw( const TRect& aRect ) const;

private:

    CAknTab( TInt aId );

    void ConstructFromResourceL( TResourceReader& aReader );
    
    void ConstructL( const TDesC& aTabText );
    
    void ConstructL( const CFbsBitmap* aTabBitmap,
                     const CFbsBitmap* aMask = NULL );

    void LoadColorBitmapL();

    /**
    * Handles a change to the control's resources.
    *
    * @param  aType  The event type.
    */
    void HandleResourceChange( TInt aType );

    void SizeChangedInNormalLayout();
    void SizeChangedInFlatLayout();
    void SizeChangedInNarrowLayout();

private:

    CEikLabel* iLabel;
    TInt       iId;
    TBool      iActive;

    const CFbsBitmap* iBitmap;
    const CFbsBitmap* iBitmapMask;
    TAknLayoutRect    iBitmapRect;

    CAknTabExtension* iExtension;
    
    typedef CArrayPtrFlat<CFbsBitmap> CAknTabColorBitmapArray;
    CAknTabColorBitmapArray* iColorBitmaps;
    };


/**
* Tab group functionality for navigation pane.
*
* @lib avkon.lib
* @since 0.9
*/
class CAknTabGroup : public CAknControl,
                     public MCoeControlObserver,
                     public MCoeControlContext,
                     public MAknNaviDecoratorObserver
    {
public:
    /**
    * Destructor.
    */
    IMPORT_C ~CAknTabGroup();

    /**
    * Creates new tab group.
    *
    * @param  aParent  Parent control.
    */
    IMPORT_C static CAknTabGroup* NewL( const CCoeControl& aParent );

    /**
    * Creates new tab group and pushes it to the clean up stack.
    *
    * @param  aParent  Parent control.
    */
    IMPORT_C static CAknTabGroup* NewLC( const CCoeControl& aParent );

public:

    /**
    * Add a tab to the tab group from resources.
    *
    * @param  aReader  Resource reader.
    *
    * @return ID of the added tab.
    */
    IMPORT_C TInt AddTabL( TResourceReader& aReader );

    /**
    * Add a tab to the tab group.
    *
    * @param  aTabId    ID of the tab to be added.
    * @param  aTabText  Text for the tab.
    */
    IMPORT_C void AddTabL( TInt aTabId, const TDesC& aText );

    /**
    * Add a tab to the tab group.
    *
    * @param  aTabId      ID of the tab.
    * @param  aTabText    Text for the tab.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    */
    IMPORT_C void AddTabL( TInt aTabId,
                           const TDesC& aText,
                           const CFbsBitmap* aTabBitmap,
                           const CFbsBitmap* aMask = NULL );

    /**
    * Add a tab to the tab group.
    *
    * @param  aTabId      ID of the tab.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    */
    IMPORT_C void AddTabL( TInt aTabId,
                           const CFbsBitmap* aTabBitmap,
                           const CFbsBitmap* aMask = NULL );
    /**
    * Replaces a tab with a new one from resources.
    * Tab with same ID is replaced.
    *
    * @param  aReader  Resource reader.
    */
    IMPORT_C void ReplaceTabL( TResourceReader& aReader );

    /**
    * Replaces a tab with a new one.
    *
    * @param  aTabId    ID of the tab to be replaced.
    * @param  aTabText  Text for the new tab.
    */
    IMPORT_C void ReplaceTabL( TInt aTabId, const TDesC& aText );

    /**
    * Replaces a tab with a new one.
    *
    * @param  aTabId      ID of the tab to be replaced.
    * @param  aTabText    Text for the new tab.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    */
    IMPORT_C void ReplaceTabL( TInt aTabId,
                               const TDesC& aText,
                               const CFbsBitmap* aTabBitmap,
                               const CFbsBitmap* aMask = NULL );

    /**
    * Replaces a tab with a new one.
    *
    * @param  aTabId      ID of the tab to be replaced.
    * @param  aTabBitmap  Bitmap for the tab. Ownership of the bitmap is taken.
    * @param  aMask       Bitmap's mask. Ownership of the mask is taken.
    */
    IMPORT_C void ReplaceTabL( TInt aTabId,
                               const CFbsBitmap* aTabBitmap,
                               const CFbsBitmap* aMask = NULL );

    /**
    * Replaces a tab text with a new one.
    *
    * @param  aTabId    ID of the tab containing the text to be replaced.
    * @param  aTabText  New tab text.
    */
    IMPORT_C void ReplaceTabTextL( TInt aTabId, const TDesC& aTabText );

    /**
    * Delete a tab from the tab group.
    *
    * @param  aTabId  ID of the tab to be deleted.
    */
    IMPORT_C void DeleteTabL( TInt aTabId );

    /**
    * Activate (highlight) a tab.
    *
    * @param  aTabId  ID of the tab to be highlighted.
    */
    IMPORT_C void SetActiveTabById( TInt aTabId );

    /**
    * Activate (highlight) a tab.
    *
    * @param  aTabIndex  Index of the tab to be highlighted.
    */
    IMPORT_C void SetActiveTabByIndex( TInt aTabIndex );

    /**
    * Returns the ID of the currently active (highlighted) tab.
    *
    * @return ID of the highlighted tab.
    */
    IMPORT_C TInt ActiveTabId() const;

    /**
    * Returns the index of the currently active (highlighted) tab.
    *
    * @return Index of the highlighted tab.
    */
    IMPORT_C TInt ActiveTabIndex() const;

    /**
    * Set width of each tab.
    * This width determines what tab layout is used.
    * To get a specific tab layout, use the following constants:
    *  - KTabWidthWithOneTab         One tab layout
    *  - KTabWidthWithTwoTabs        Two tabs layout
    *  - KTabWidthWithThreeTabs      Three tabs layout
    *  - KTabWidthWithFourTabs       Four tabs layout
    *  - KTabWidthWithTwoLongTabs    Two long tabs layout
    *  - KTabWidthWithThreeLongTabs  Three long tabs layout
    *
    * @param  aWidth  Width of each tab, @see aknconsts.h.
    */
    IMPORT_C void SetTabFixedWidthL( TInt aWidth );
    
    /**
    * Sets a tab dimmed/not dimmed.
    *
    * @param  aTabId   ID of the tab.
    * @param  aDimmed  @c ETrue to set the tab dimmed,
    *                  @c EFalse otherwise.
    */
    IMPORT_C void DimTab( TInt aTabId, TBool aDimmed );
    
    /**
    * Used to check whether or not a tab is dimmed.
    *
    * @param  aTabId  ID of the tab.
    *
    * @return @c ETrue if the tab is dimmed, @c EFalse otherwise.
    */
    IMPORT_C virtual TBool IsTabDimmed( TInt aTabId ) const;

    /**
    * Returns the index of a tab.
    *
    * @param  aTabId  ID of a tab.
    *
    * @return Index of the tab.
    */
    IMPORT_C virtual TInt TabIndexFromId( TInt aTabId ) const;

    /**
    * Returns the ID of a tab.
    *
    * @param  aTabIndex  Index of a tab.
    *
    * @return ID of the tab.
    */
    IMPORT_C virtual TInt TabIdFromIndex( TInt aTabIndex ) const;

    /**
    * Number of tabs in the tab group.
    *
    * @return  Number of tabs in the tab group.
    */
    IMPORT_C virtual TInt TabCount() const;

    /**
    * Sets the tab observer for this tab group.
    *
    * @param  aObserver  Tab observer to set.
    */
    IMPORT_C void SetObserver( MAknTabObserver* aObserver );

public: // From base class @c CCoeControl.

    /**
    * Return minimum size of the control.
    *
    * @return Minimum size of the control.
    */
    IMPORT_C virtual TSize MinimumSize();

    /**
    * Handles key events.
    *
    * @param  aKeyEvent  The key event.
    * @param  aType      The type of the event.
    *
    * @return Indicates whether or not the key event was used by this control.
    */
    IMPORT_C virtual TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                  TEventCode aType );

    /**
    * Gets the list of logical colors employed in the drawing of the control,
    * paired with an explanation of how they are used.
    * Appends the list into @c aColorUseList.
    *
    * @param[in,out]  aColorUseList  The color list.
    */
    IMPORT_C virtual void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList ) const;

    /**
    * Handles a change to the control's resources.
    *
    * @param  aType  The type of resource change.
    */
    void HandleResourceChange( TInt aType );

    /**
    * Handles pointer events in tabs.
    *
    * @param  aPointerEvent  Pointer event to be handled.
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

public: // From base class @c MCoeControlObserver.

    /**
    * Handles an event from an observed control.
    *
    * @param  aControl    Control that caused the event.
    * @param  aEventType  Type of the event.
    */
    IMPORT_C virtual void HandleControlEventL( CCoeControl* aControl,
                                               TCoeEvent aEventType );

public: // From base class @c MCoeControlContext.

    /**
    * Allows to modify graphics context before Draw.
    *
    * @param  aGc  Graphics context to be modified.
    */
    IMPORT_C virtual void PrepareContext( CWindowGc& aGc ) const;

public: // From base class @c MAknNaviDecoratorObserver.

    /*
    * Handles events from navi decorator parent control.
    *
    * @param  aEventID  ID of event to be handled.
    */
    IMPORT_C virtual void HandleNaviDecoratorEventL( TInt aEventID );

protected: // From base class @c CCoeControl.

    /**
    * Handles the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * Returns number of controls inside this control.
    *
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * Returns a component control determined by control index.
    *
    * @param  aIndex  Index of a control to be returned.
    *
    * @return Pointer to the control.
    */
    IMPORT_C virtual CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
    * This is called when the focus is changed.
    *
    * @param  aDrawNow  Whether or not to draw the control.
    */
    IMPORT_C virtual void FocusChanged( TDrawNow aDrawNow );

    /**
    * Reverse the order of tabs in tab array.
    */
    void ReverseTabOrderL();
    
private:

    /*
    * Reserved
    */
    IMPORT_C virtual void Reserved1();

    /*
    * Reserved
    */
    IMPORT_C virtual void Reserved2();

    /*
    * Reserved
    */
    IMPORT_C virtual void Reserved3();


private:
    IMPORT_C CAknTabGroup();

    /**
    * Tab groups can be mirrored depending on current locale. To client
    * application everything always seems like tabs are not mirrored but
    * the internal order of tabs in tab group may or may not be mirrored.
    * If mirroring is off then this function just returns given
    * parameter as it is. If mirroring is on then this function returns
    * unmirrored index if given index was mirrord and vice versa. Two
    * nested calls to this function cancels its effect
    * (ConvertTabIndex(ConvertTabIndex(aIndex)) == aIndex).
    *
    * @param  aIndex  Index to be converted.
    * @return Converted index.
    */
    TInt ConvertTabIndex(TInt aIndex) const;

private: // From base class @c CCoeControl.

    IMPORT_C virtual void Draw( const TRect& aRect ) const;

private: // From base class @c CAknControl.

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
public: // New methods

    /**
    * Sets the multi-color drawing mode of a tab.
    * This should be called after adding a tab to the tab group
    * if the icon in the tab should be drawn as multi-colored.
    * The tab icon will be drawn using a color specified in the
    * active skin if multi-color mode is not defined.
    *
    * This function should be called right after a tab containing
    * a multi-color icon is added to the tab group.
    * 
    * @param  aTabId       ID of the tab.
    * @param  aMultiColor  @c ETrue to set the multi-color mode on,
    *                      @c EFalse to turn it off.
    */
    IMPORT_C void SetTabMultiColorMode( TInt aTabId, TBool aMultiColor );

    /** Directions in which the tab group focus can be moved. */
    enum TDirection
        {
        ELeft,
        ERight
        };

private:
    void ConstructL();
    void CommonAddTabL(CAknTab* aTab);
    void CommonReplaceTabL(CAknTab* aTab);
    void HandleTabStateChanged(CCoeControl* aControl);
    TInt Index(TInt aTabId) const;
    TBool CycleFocus(TDirection aDirection,TDrawNow aDrawNow);
    TInt LeftMostTabIndex() const;
    TInt RightMostTabIndex() const;
    void DrawLowerBorder(TDrawNow aDrawNow) const;
    void DoDrawLowerBorder() const;
    void ReportNavigationEvent();
    void LoadTabBitmapsL(TInt aNumberOfTabsShown, TBool aLongTabs);
    TBool TabsVisibleInCurrentLayout() const;
    void CurrentLayout( TAknWindowLineLayout& aLayout ) const;
    void InitTabGroupGraphicsL();

    void InitTabAnimationEventTimer();
    void CancelTabAnimationEventTimer();
    static TInt TabAnimationEvent(TAny * aPtr);
    void DoTabAnimationEvent();

    TBool NarrowTabLayoutNext();
    TBool NarrowTabLayout();

public:

    /**
    * Sets the navigation decorator layout so that it corresponds
    * the current tab group layout.
    * 
    * @param  aNarrow  @c ETrue if narrow tab group layout is used,
    *                  @c EFalse if normal layout is used.
    */
    void SetDecoratorLayout( TBool aNarrow );

private:

    void SizeChangedInNormalLayout();
    void SizeChangedInFlatLayout();
    void SizeChangedInNarrowLayout();
    void InitTabAnimationL();
    

    /**
    * Gets the rectangle for the tab group.
    * If the tab arrows are not shown, then the tab group gets a wider
    * rectangle.
    *
    * @param  aArrowsUsed  @c ETrue if tab arrows are shown,
    *                      @c EFalse otherwise.
    */
    static TRect ParentRect( TBool aArrowsUsed );
    
    /**
    * @internal Used by the UI framework.
    *
    * Starts the animation shown when tab focus is cycled.
    * Note that this starts the animation only when required, i.e.
    * when layout that needs cycle animation is used and when the first
    * shown tab in the tab group changes.
    *
    * @param  aDirection  Direction which the focus in cycled to.
    * @param  aNewTab     Index of the tab that receives the focus.
    */
    void StartCycleAnimationL( TDirection aDirection, TInt aNewTab );
    
    /**
    * Called on the dynamic layout switch event, switches the current tab
    * layout to a corresponding one that is usable in the new layout.
    */ 
    void SwitchTabLayoutL();

public:

    /**
    * @internal Used by the UI framework.
    * Applications can set the narrow layout using @c CAknNaviDecorator class.
    */
    void SetNarrowTabLayoutL( TBool aNarrow, TBool aUseAnimation = EFalse );
    
    /**
    * @internal Used by the UI framework.
    *
    * Sets the tab arrows' visibility.
    *
    * @param  aVisible  @c ETrue to set the arrows visible,
    *                   @c EFalse to hide them.
    */
    void SetNaviArrowsVisible( TBool aVisible );

private:
    CArrayPtr<CAknTab>*     iTabArray;
    TInt                    iActiveTab;
    TRect                   iSpareRect;

    TInt                    iTabFixedWidth;
    TBool                   iLongTabs;
    TInt                    iNumberOfTabsShown;
    TInt                    iFirstShownTab;

    CFbsBitmap*             iTabBitmaps[KTabNumberOfTabBitmaps];
    CFbsBitmap*             iTabMaskBitmaps[KTabNumberOfTabBitmaps];

    TInt                    iBitmapNames[KTabNumberOfTabBitmaps];
    TInt                    iBitmapMaskNames[KTabNumberOfTabBitmaps];
    CAknTabGroupExtension*  iExtension;

    MAknTabObserver*        iTabObserver;
    TBool                   iMirrored;
    };

#endif // AKNTABGRP_H
