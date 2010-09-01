/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknChoiceList - Choice list for S60 
*
*/



#ifndef AKNCHOICELIST_H
#define AKNCHOICELIST_H

// includes 
#include <AknControl.h>
#include <coecobs.h>

// forward declarations  
class CAknButton;
class CEikLabel;
class CAknChoiceListPopup;
class CAknChoiceListPopupList;
class CAknsFrameBackgroundControlContext;
class CAknInfoPopupNoteController;

// Class declaration

/**
 *  CAknChoiceList
 *  Choice list is new component, which allows selection from vertical list of choices.
 *  By default choice list shows currently selected item and a arrow for opening the 
 *  the choice list. Choice list can be used also without showing current selection. 
 *  @lib avkon.lib
 *  @since S60 5.0
 */ 
class CAknChoiceList : public CAknControl, public MCoeControlObserver
    {   
public:

    /* Flags for choice list types and positioning */   
    enum TAknChoiceListFlags
        {
        /* Using default choice list with popup list */
        EAknChoiceListWithCurrentSelection = 0x01,
        /* Using user defined button to open choice list */
        EAknChoiceListWithoutCurrentSelection = 0x02,
        /* Popup positioning flags */
        EAknChoiceListPositionLeft = 0x04,   
        EAknChoiceListPositionRight = 0x08,   
        EAknChoiceListPositionBottom = 0x10  
        };    
     
     /* Tooltip positioning */
     enum TTooltipPosition
        {
        EPositionTop = 1, /* Tooltip alignment vertically to top */
        EPositionBottom, /* Tooltip alignment vertically to bottom */
        EPositionLeft, /* Tooltip alignment horizontally to left */
        EPositionRight /* Tooltip alignment horizontally to right */
        };
public: 

    /**
     * Two-phased constructor.
     * If the default flag is used then choice list shows an opening arrow and selected item on its 
     * left side. If flag EAknChoiceListUsesButton is and user has defined own button then choice list
     * open with items in the given array. Selected item is not show when choice list is closed. 
     * @param aParent the parent control for choice list
     * @param aItemArray Array of items to be shown in the choicelist. Transfers ownership.
     * @param aFlags Flags for choice list type and positioning
     * @param aButton user defined button for choicelist. Button replaces the typical choice list. 
     * Transfers ownership.
     */
    IMPORT_C static CAknChoiceList* NewL( CCoeControl* aParent, CDesCArray* aItemArray, TInt aFlags = EAknChoiceListWithCurrentSelection, CAknButton* aButton = NULL );

    /**
     * Two-phased constructor.
     * If the default flag is used then choice list shows an opening arrow and selected item on its 
     * left side. If flag EAknChoiceListUsesButton is and user has defined own button then choice list
     * open with items in the given array. Selected item is not show when choice list is closed. 
     * @param aParent the parent control for choice list
     * @param aItemArray Array of items to be shown in the choicelist. Transfers ownership.
     * @param aFlags Flags for choice list type and positioning
     * @param aButton user defined button for choicelist. Button replaces the typical choice list. 
     * Transfers ownership.
     */
    IMPORT_C static CAknChoiceList* NewLC( CCoeControl* aParent, CDesCArray* aItemArray, TInt aFlags = EAknChoiceListWithCurrentSelection, CAknButton* aButton = NULL );
    
    /**
     * Destructor
     */
    ~CAknChoiceList();
    
    /**
     * Open choice list.
     * Choicelist can be opened with this function. If the choicelist is already
     * open nothing will happen.
     * @return KErrNone if succeeded
     */
    IMPORT_C TInt ShowChoiceListL();
    
    /**
     * Set certain index of the choice list array to selected
     * @param aIndex Index of the array to be selected as default
     */
    IMPORT_C void SetSelectedIndex( const TInt aIndex );
    
    /**
     * Returns selected index from the choice list array
     * @return TInt selected index
     */
    IMPORT_C TInt SelectedIndex() const;
    
    /**
     * Set certain array as the contents of the choice list. 
     * It's recommended to use CDesCArrayFlat. The ownership of the array is transferred
     * to choice list.
     * @param aArray Array of text items to be inserted as the content for choice list
     */
    IMPORT_C void SetItems( CDesCArray* aArray );
    
    /**
     * Set certain array as the contents of the choice list. 
     * It's recommended to use CDesCArrayFlat. 
     * @param aResourceId Resource id for an array. 
     */
    IMPORT_C void SetItemsL( TInt aResourceId );
    
    /**
     * Add a text as a new item in the end of the choice list array. 
     * @param aDesC Pointer to a descriptor item that should be appended to the array. 
     * Transfers ownership.
     * @return index in the choicelist array for newly added item. 
     */
    IMPORT_C TInt AddItemL( const TDesC* aDesC );
    
    /**
     * Removes an item from the choice list array with the given index. 
     * @param aIndex index for the item that should be removed from the choice list array
     */
    IMPORT_C void RemoveItem( const TInt aIndex );    
    
    /**
     * Sets flags for choice list.
     * Choice lists position can be changed in runtime with right flags. 
     * @param aFlags The flags to be set for choice list
     */        
    IMPORT_C void SetFlags( const TInt aFlags );
    
    /**
     * Return choice list specific flags.
     * @return choice list flags
     */
    IMPORT_C TInt Flags() const;
    
    /**
     * Set the button that launches choice list opening.
     * @param aButton The Button for opening choice list control 
     */
    IMPORT_C void SetButtonL( CAknButton* aButton );
    
    /**
     * Hide choice list popup. Current selection is not selected.
     */
    IMPORT_C void HideChoiceList();

    /**
     * Set text for tooltip
     * @param aText The text shown as tooltip
     */
    IMPORT_C void SetTooltipTextL( const TDesC& aText );

    /**
     * Set the delays for tooltip
     * @param aBeforeTimeout The delay in milliseconds before tooltip
     *        is shown. The default is 150 milliseconds
     * @param aInViewTiemout The interval in milliseconds how long the
     *        tooltip is displayed. The default is 3000 milliseconds.
     */
    IMPORT_C void SetTooltipTimeouts( const TInt aBeforeTimeout,
                                      const TInt aInViewTimeout );
    /**
     * Set the postion of tooltip
     * @param aPosition The position expressed with TTooltipPosition
     *        The default is EPositionTop
     */                                      
    IMPORT_C void SetTooltipPosition( const TTooltipPosition aPosition );
    
// From CCoeControl
    
    /**
     * From CCoeControl. Returns the control inside control with given index.
     * @param aIndex Index of a control be returned
     * @return A Pointer to control.
     */
    IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * From CCoeControl. Returns number of controls inside the control.
     * @return Number of component controls.
     */
    IMPORT_C TInt CountComponentControls() const;

    /**
     * From CCoeControl. Returns the Minimum size needed by the control. 
     * @return TSize minimum size. 
     */
    IMPORT_C TSize MinimumSize();    
    
    /**
     * From CCoeControl. Handles a change to the control's resources.
     * @param aType A message UID value.   
     */
    IMPORT_C void HandleResourceChange( TInt aType );    
    
    /**
     * From CCoeControl. Handles key events.
     * @param aKeyEvent the key event    
     * @param aType The type of key event
     * @return Indicates whether or not the keyevent was used by this control   
     */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );    
    
    /**
     * From CCoeControl. Draws control to given area
     * @param aRect The rectangle that should be drawn by the control. 
     */
    IMPORT_C void Draw( const TRect& aRect ) const;
    

    /**
    * from CCoeControl 
    *
    * Responds to changes in the position of a control.
    *
    */
    IMPORT_C virtual void PositionChanged();


// From MCoeControlObserver
    
    /**
     * From MCoeControlObserver. Handles an event from an observed control.
     * If this component has observer, then a EEventStateChanged is sent to it
     * when a item is selected from choice list
     * @param aControl The control that sent the event.
     * @param aEventType The event type. 
     */
    IMPORT_C void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

public: 
    // new functions
    /**
    * Insert new item to a certain index. The rest of the array will be reindexed. 
    * If given index is beyond current array then it's just appended to the end of the array.
    * @param aIndex The array index where new item is going to be inserted.
    * @param aText Items text
    * @return The index of newly inserted item. Index can be other than passed if given index 
    * is out of array bounds
    */
    IMPORT_C TInt InsertItemL( const TInt aIndex, const TDesC& aText );
    
protected: 

// from CCoeControl         
    
    /**
     * From CCoeControl. Sets the size and position of the component. 
     */
    void SizeChanged();
    
    /**
     * From CCoeControl. Handles pointer events
     * @param aPointerEvent the pointer event be be handled.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );    

private:

    /**
     * C++ Default Constructor 
     */
    CAknChoiceList(); 

    /**
     * 2nd phase constructor
     * @param aParent the parent control for choice list
     * @param aItemArray Array of items to be shown in the choicelist
     * @param aFlags Flags for choice list type and positioning
     * @param aButton user defined button for choicelist. Button replaces the typical choice list
     */
    void ConstructL( CCoeControl* aParent, CDesCArray* aItemArray, TInt aFlags, CAknButton* aButton );    
    
    /**
     * Construct the typical choice list that open with arrow and show current selection 
     * even in the closed state.
     */
    void ConstructTypicalChoiceListL();
    
    /**
     * Calculate positioning for the opened choice list popup by the given position flag.
     */
    void SetPopupRect();
    
    /**
     * Update labels text 
     */
    void UpdateLabelL();

    /**
     * Show tooltip text
     */
    void ShowTooltipL();

    
private: // data

    /**
     * Flags for choice list
     */
    TInt iFlags;
    
    /** 
     * Currently selected index of an item that is stored in choice list array.
     */
    TInt iSelectedIndex;
    
    /** 
     * Used to store if the choice list is closed mode or not. 
     */
    TBool iIsClosed;    
    
    /**
     * Button for opening the choicelist. If choice lists type is 
     * EAknChoiceListWithCurrentSelection this is the arrow button. 
     * Otherwise this is user defined.
     * Own.
     */
    CAknButton* iButton;
    
    /**
     * Label that shows the currently selected item if choice list type is 
     * EAknChoiceListWithCurrentSelection. Otherwise this will not be used. 
     * Own.
     */
    CEikLabel* iLabel;

    /**
     * Array that stores all the items in the choice list. 
     * Own.
     */
    CDesCArray* iArray;    
    
    /**
     * Pointer to current choice list popup window. Popup window is 
     * used only internally and it cannot be accessed from outside.
     * Own.
     */
    CAknChoiceListPopup* iPopup;

    /**
     * Component used to show tooltip
     * Own.
     */
    CAknInfoPopupNoteController* iTooltip;

    /**
     * Stores the text for tooltip
     * Own.
     */
    HBufC* iTooltipText;

    /**
     * Stores the delay in milliseconds when the tooltip is shown
     * Own.
     */
    TInt iTooltipWaitInterval;

    /**
     * Stores the time interval in milliseconds how long the tooltip is shown
     * Own.
     */
    TInt iTooltipInViewInterval;

    /**
     * Stores the tool tip positioning
     * Own.
     */
    TTooltipPosition iTooltipPosition;

    
    };    

#endif // AKNCHOICELIST_H

// end of file
