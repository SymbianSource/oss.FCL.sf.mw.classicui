/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control container for fastswap
*
*/

#ifndef __AKNFASTSWAPWINDOWCONTROL_H__
#define __AKNFASTSWAPWINDOWCONTROL_H__

// INCLUDES
#include <AknPopupFader.h>
#include <eiklbo.h>
#include <coecntrl.h>
#include <eikcmobs.h>
#include <bldvariant.hrh>
#include <apgcli.h>
#include <coecobs.h> // MCoeControlObserver
#include <eikmobs.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknQueryDialog;
class CAknsFrameBackgroundControlContext;
class CAknCapAppServerAppUi;
class CEikFormattedCellListBox;
class CAknGrid;
class CEikButtonGroupContainer;
class CGulIcon;
class CAknInfoPopupNoteController;
class CEikLabel;
class CAknAlwaysShownAppList;
class CAknChoiceList;
class CAknStylusPopUpMenu;
class CAknLongTapAnimation;
class CPeriodic;
class CAknPointerEventSuppressor;
class CRepository;
// CLASS DECLARATION

/**
 *  Control container for fastswap.
 */
NONSHARABLE_CLASS(CAknFastSwapWindowControl) : 
    public CCoeControl,
    public MEikListBoxObserver,
    public MAknFadedComponent,
    public MEikMenuObserver,
    public MCoeControlObserver
    {
public: // Constructors and destructor
    /**
     * C++ default constructor.
     * @param aAppUi AppUi of Eikon server.
     */
    CAknFastSwapWindowControl( CAknCapAppServerAppUi& aAppUi );
    
    /**
     * Two-phased constructor.
     */
    void ConstructL();
    
    /**
     * Destructor.
     */
    ~CAknFastSwapWindowControl();

public: // New functions
    /**
     * Called from akncapserver appui to run fastswap.
     */
    void RunFastSwapL();
    
    /**
     * Called from akncapserver appui to close fastswap.
     */
    void CloseFastSwap();
    
    /**
     * Updates window group lists (the list of applications).
     *
     * @param        aWaitForWGRemoval Changes are only made if a deleted 
     *               application has been removed from the window group list. 
     * @return       ETrue if the window group list has changed.
     *               EFalse if the window group list hasn't changed.
     */
    TBool InitializeWindowGroupListL( TInt aWaitForWGRemoval );
    
    /**
     * Calls InitializeWindowGroupListL() and returns the number of 
     * the window groups visible to the user.
     * 
     * @return        Number of winfow groups found in the system.
     */
    TInt VisibleWindowGroupsCountL();
    
    /**
     * Fast swap window is visible on the screen.
     *
     * @return        ETrue if full functional and visible.
     *                EFalse if in closed mode.
     */        
    TBool IsDisplayed(); 
    
    /**
     * Performs a short apps key press action.
     */
    void HandleShortAppsKeyPressL();
    
    /**
     * Performs a long apps key press action.
     */
    void HandleLongAppsKeyPressL();
    
    /**
     * Performs a long apps key press action.
     */
    void HandleChangeInWindowGroupListL();
    
    /**
     * Show tooltip when touch input is used.
     * Also AknFastSwapWindowGrid uses this when
     * drag scrolled to new item.
     *
     * @param aPointerOverItem      Is pointer currently over item in grid.
     */       
    void ShowTooltipTouchL(TBool aPointerOverItem);
    
public: // Functions from base classes.
    /**
     * From CCoeControl    
     * Function where control's drawing is done.
     *
     * @param aRect Control's area.
     */
    void Draw( const TRect &aRect ) const;
    
    void HandleResourceChange( TInt aType );
    
    /**
     * Needed to handle background animation.
     */
    void FocusChanged( TDrawNow aDrawNow );
    
    /**
     * Overloads CCoeControl::SizeChanged. Needed to handle highlight animation.
     */
    void SizeChanged();

private:
    /**
     * From CCoeControl.
     * Key event handling
     *
     * @return TKeyResponse  Indicates whether or not the key event was used by this control.
     * @param aKeyEvent      Key event.
     * @param aType          Type of key event.
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    
    /**
     * From MEikCommandObserver.
     *
     * @param aCommandId     Id of command.
     */
    void ProcessCommandL(TInt aCommandId );
    
    /**
     * From MEikListBoxObserver.
     *
     * @param aListBox        List handling the event.
     * @param aEventType      Type of listbox event.
     */
    void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );

    /**
     * From MCoeControlObserver.
     *
     * @param aControl        Control sending the event
     * @param aEventType      Event type
     */
    void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);
    
    /**
     * From CCoeControl      Method handling the pointer events while the fsw is used.
     *
     * @param aPointerEvent  Information about the event.
     */
    void HandlePointerEventL( const TPointerEvent &aPointerEvent );
    
    /**
     * from MEikMenuObserver
     * @param aMenuControl The menu control.
	 * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise
     */
    void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    
private: // Functions that create/update/delete the child controls  
    /**
     * Updates UI components.
     */        
    void UpdateViewL();
    
    /**
     * Creates CCoeControlArray for child controls.
     */
    void CreateComponentArrayL();
    
    /**
     * Grid construction, called from CAknFastswapWindowControl:ConstructL().
     */
    void CreateGridL();
    
    /**
     * Updates grid.
     */
    void UpdateGridL();
    
    /**
     * Creates item (text and icon) arrays.
     */
    void CreateItemArraysL();
    
    /**
     * Creates updated item arrays.
     */
    void UpdateItemArraysL();
    
    /**
     * Clears the item arrays from dynamically loaded content.
     *
     * @param     TBool aCompress if the size of the item arrays
     *            is compressed as well.
     */
    void ClearItemArrays( TBool aCompress );
    
    /**
     * Creates tooltip control for fsw.
     */
    void CreateTooltipL();
    
    /**
     * Shows the tooltip control for highlighted application icon.
     */        
    void UpdateTooltipL();
    
    /**
     * Creates title for fsw.
     */
    void CreateLabelL();
    
    /**
     * Update label layouts and skinning.
     */        
    void UpdateLabelL(); 
    
    /**
     * Reserves the default application icon for the low memory situation.
     */
    void UpdateDefaultAppIconL();
            
    /**
     * Reserves heading icon for the heading pane.
     */        
    void UpdateHeadingIconL();
    
    /**
     * Update control context (especially rect size).
     */
    void UpdateControlContext();
    
    /**
     * CBA construction, called from CAknFastswapWindowControl:ConstructL().
     */
    void CreateCbaL();
       
private: // Utility functions 
    /**
     * Fades the background application.
     *
     * @param aFade        State of fading.
     */
    void FadeBackground( TBool aFade );
    
    /**
     * Either Brings a task forward and dismisses fastswap or launches a new application.
     *
     * @param aIndex      The grid index of the task to switch to.
     */
    void SwitchToApplicationL( TInt aIndex );
    
    /**
     * Brings a task forward and dismisses fastswap.
     *
     * @param aWgId       The window group of the task.
     */
    void SwitchToTask( TInt aWgId );
    
    /**
     * Launches an application to the phone memory based on the given application uid.
     *
     * @param aAppUid      The uid of the application.
     */
    void LaunchAppL( TUid aAppUid );
    
    /**
     * Cleanup and closes FastSwap.
     */
    static void CleanupRunFastSwap( TAny* aThis );
    
    /**
     * Closes named application.
     * 
     * @param aName App name (given in fastswap grid).
     */
    TBool OfferCloseSelectedAppL( const TDesC& aName );
    
    /**
     * Test if given window id is among fastswaps shown windows ids
     * 
     * @param aWgId Id to be tested,
     */
    TBool IsWgIdInShownList( TInt aWgId );
    
    /**
     * Calculates Fastswap window size and position in the screen.
     * 
     * @return    TRect the window rect.
     */                
    TRect FastSwapWindowRect();
    
    /** 
     * Calculates and returns the icon size used in the fast swap list.
     *
     * @return Icon size.
     */
    TSize IconSize();      
    
    /**
     * Deletes aCount number of icons from the icon array starting from index aIndex.
     *
     * @param     TInt aIndex Index from which deletion begins .
     * @param     TInt ACount How many icons are deleted.
     */
    void DeleteIcons( TInt aIndex, TInt aCount );
    
    /**
     * Returns the number of rows shown in the fast swap window (1-3).
     *
     * @return Number of rows.
     */
    TInt NumberOfVisibleRows();
     
    /**
     * Shows the tooltip control for highlighted application icon.
     *
     * @return Name of the application with current highlight.
     */        
    TPtrC CurrentAppName();
    
    /**
     * The rect of current highlighted grid item.
     *
     * @return Rect of the selected grid item.
     */
    TRect CurrentGridItemRect();
    
    /**
     * Application icon is added to the item arrays.
     *
     * @param    TUid aAppUid the application uid.  
     * @return   ETrue addition was successful.
     *           EFalse icon wasn't added to the list.
     */        
    TBool AddIconToArrayL( TUid aAppUid );      

private: // From MObjectProvider.
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    
    virtual TInt CountFadedComponents();
    virtual CCoeControl* FadedComponent( TInt aIndex );
    
    /**
     * Try to close a application.
     * @param aIndex  the index of the current item. 
     * @param aIsShift whether press Modifier key  
     */
    void TryCloseApplicationL(TInt aIndex, TBool aIsShift = EFalse);
    
    /**
     * Set a flag that directs Stylus Popup Menu is Hidden .
     */
    void SetHiddenFlag();
    
    /**
     * create a stylus popup menu .
     */
    void CreateStylusPopupMenuL();
    
    /**
     * Show stylus popup menu .
     */
    void ShowPopupMenuL();
    
    /**
     * Handle long Tap.
     * @param aEvent current pointer event 
     */
    void PointerEventL( const TPointerEvent& aEvent );
        
    /**
     * Start long tap animation.
     */    
    void StartAnimationL();
    
    /**
     * Stop long tap animation.
     */   
    void StopAnimation();   
    
    /**
     * Start showing long tap animation.
     */ 
    void ShowAnimationL();
    
    /**
     * A call back function used by iTimeOut.
     * @param aPtr a ponter to any object 
     */ 
    static TInt TimeOutCallBackL( TAny* aPtr );
    
    /**
     * A call back function used by iToolTipTimer.
     * @param aPtr a ponter to any object 
     */ 
    static TInt ToolTipTimeOutCallBackL( TAny* aPtr );
    
    /**
     * hide Tooltip after pointer up event .
     */ 
    void HideTooltip();
    
    void CancelAnimationAndPressDownEffect();
        
private: // Data
    struct SWindowGroupInfo
        {
        TInt iWgId;
        TBool iIsSystemApp;
        };
        
    // for animation 
    enum TFswLongTapState
        {
        EWaiting, 				// normal state
        EWaitingForAnimation,	// Only "Pen down" event received, CTimer started
        EShowingAnimation,		// Long tap animation started
        EShowingPressedDownEffect // Pressed down effect started  
        };
        
    CAknGrid* iGrid;
    
    CArrayFixFlat<SWindowGroupInfo>* iShownWgIds;
    RArray<RWsSession::TWindowGroupChainInfo>* iAllWgIds;
    CDesCArray* iItemTextArray;
    TInt iNumberOfWGs;
    TAknPopupFader iPopupFader;
    TInt iBackgroundWgId;
    CEikButtonGroupContainer* iCba;
    CAknCapAppServerAppUi& iAppUi;
    TBool iIsDisplayed;
    CArrayPtrFlat<CGulIcon>* iIconArray;
    CAknQueryDialog* iConfirmCloseDialog;
    TInt iConfirmCloseWgId;
    CAknsFrameBackgroundControlContext *iFrameContext;
    
    // Low memory situation handling.
    TBool iLowMemory;  
    TBool iLowMemIcons; 
    
    // Previous mdca count.
    TInt iOldCount;
    
    // Default application icon fsw uses if there is no memory left for individual application 
    // icons.
    CGulIcon* iDefaultAppIcon;
    
    // AppArc session is created only once and handle is stored in the class.
    TBool iAppArcSessionInitiated;
    RApaLsSession iAppArcSession;

    // Tooltip that shows application names.
    CAknInfoPopupNoteController* iTooltip;
    CEikLabel* iLabel;        
    CGulIcon* iHeadingIcon;
    
    CAknAlwaysShownAppList* iAlwaysShownList;
    friend class CAknAlwaysShownAppList;
    TBool iDisableFSWEffect;
    TBool iStylusDownIn;
    TBool iTooltipModeTouch;
    TBool iTransparencyEnabled;
    
    CAknStylusPopUpMenu* iPopupMenu; // Own 
    TBool iIsStylusPopupShow; 
    TFswLongTapState iState; //state variant
    CAknLongTapAnimation* iLongTapAnimation; //own

    CPeriodic* iTimeOut; //own, used for showing Animation and Stylus popup menu
    
    TBool iItemDraggingActioned;

    TPoint iAnimationPosition; // will show animation in this position 
      
    CPeriodic* iToolTipTimer; //own, used for showing ToolTip   
    TBool iIsAnimationShowing;    
    TBool iIsPointerDownOutOfGrid;
    TInt iFirstAppWgId;  
    TBool iIsClosing;
    TTime iPressDownTime;
    
    /** Indicates that an item has received highlight. */
    TBool iItemHighlighted;

    // Own. CenRep object for themes application keys.
    CRepository* iThemesAppRepository;
    };

#endif // __AKNFASTSWAPWINDOWCONTROL_H__   
            
// End of File
