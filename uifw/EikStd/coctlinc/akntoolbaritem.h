/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  toolbar item
*
*/


#ifndef CAKNTOOLBARITEM_H
#define CAKNTOOLBARITEM_H

#include <e32def.h>
#include <e32base.h>
#include <coecntrl.h>

/**
 *  Class that contains information about toolbar items
 *
 *  @lib eikcoctl.lib
 *  @since S60 v5.0
 */

NONSHARABLE_CLASS( CAknToolbarItem ) : public CBase
    {

public:
    /**
     * Constructor
     */
    CAknToolbarItem();

    /**
     * Constructor
     */
    CAknToolbarItem( CCoeControl* aControl, TInt aType, TInt aId, TInt aFlags );

    /**
     * Destructor
     */
    ~CAknToolbarItem();

    /**
     * Constructs toolbar item from resources
     * @param aReader resource reader
     */
    void ConstructFromResourceL( TResourceReader& aReader );

    /**
     * CCoeControl that the item contains 
     * @return control of this toolbar item
     */
    CCoeControl* Control() const;

    /**
     * ControlType of the toolbar item
     * @return controltype defined in avkon.hrh
     */
    TInt ControlType() const;

    /**
     * Command id of the toolbar item
     * @return command id
     */
    TInt CommandId() const;

    /**
     * Flags of toolbar item
     * @return flags
     */
    TInt Flags() const;

    /**
     * Is used for quering if item is selected
     * @return boolean to indicate if selected
     */
    TBool IsSelected() const;

    /**
     * @param aIsSelected if item should be selected or not. 
     * @return boolean to indicate if item was succesfully selected
     */
    TBool SetIsSelectedL( TBool aIsSelected );

    /**
     * Sets buttons to close on command 
     * @param boolean to indicate if closing on command or not
     */
    void SetCloseOnCommand( const TBool aCloseOnCommand );

    /**
     * Sets highlightrect for toolbar items
     * @param aRect highlightrect
     */
    void SetHighlightRect( const TRect& aRect );


    /**
     * Returns highlightrect
     * @return highlightrect
     */
    TRect HighlightRect() const;

    /**
     * Sets toolbar item focused, used only with buttons
     * @param aFocus if to give focus or to take it away
     * @param aPrepareControl to tell if PrepareForFocusLossL and 
     * PrepareForFocusGailL are called on the control
     * @param aDrawNow if to draw again or not
     * @param aParent item parent
     */
    void SetFocusL( TBool aFocus, TBool aPrepareControl, TDrawNow aDrawNow,
                    const CCoeControl* aParent );

    /**
     * Registers parent positions
     * @param aParentPosition position of parent
     */
    void RegisterPosition( const TPoint& aParentPosition ) const;

    /**
     * returns boolean to inform if hidden
     * @return boolean to indicate if hidden or not
     */
    TBool IsHidden() const; 

    /**
     * Sets item hidden or unhidden
     * @param boolean to indicate if item should be hidden or not
     */
    void SetHidden( TBool aHidden ); 

    /**
     * Indicates if item refuses key events
     * @return ETrue if refuses key events 
     */
    TBool RefusesKeys() const;

private:

    /**
     * Sets item(editors) to refuse key events
     */
    void SetKeyRefuse();
        
private: // data
    // The control of the item
    // own
    CCoeControl* iControl;

    // type of the control to keep a track on whether this item is supported 
    // by a toolbar component
    TInt iControlType; 

    // command ID of this toolbar item 
    TInt iCommandId;    

    // item flags
    TInt iFlags;

    // if ETrue, all key events will go to it.  
    TBool iIsSelected;  

    // Highligh rect for toolbar item
    TRect iHighlightRect;

    // If ETrue, this item is hidden
    TBool iHidden; 
        
    // ETrue if key events are not redirected for the control
    TBool iRefusesKeys;
    };
#endif //CAKNTOOLBARITEM_H