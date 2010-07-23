/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling stylus specific popup menu.
*
*/


#ifndef CAKNSTYLUSPOPUPMENU_H
#define CAKNSTYLUSPOPUPMENU_H


#include <e32base.h>
#include <coecobs.h> // MCoeControlObserver
#include <babitflags.h>

class CAknPreviewPopUpController;
class CAknStylusPopUpMenuContent;
class MEikMenuObserver;
class TResourceReader;

/**
 *  Stylus specific popup menu
 *
 *  A floating popup menu which is meant for stylus usage only.
 *  The menu appears near to the tapping position. When an item is 
 *  tapped the menu calls its observer's (iMenuObserver) ProcessCommandL. 
 *  Typically the observer is application's AppUi. It is then the
 *  observer's responsibility to handle the command appropriately.
 *  The observer is informed with KErrCancel if the menu is closed without 
 *  making a selection. 
 *
 *  @lib eikcoctl.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknStylusPopUpMenu ) : public CBase, 
                                           public MCoeControlObserver
    {
public:
    enum TPositionType
        {
        EPositionTypeRightTop = 0,
        EPositionTypeLeftTop,
        EPositionTypeRightBottom,
        EPositionTypeLeftBottom      
        };
    /**
     * Two-phased constructor
     *
     * @param aObserver Menu observer (not owned) that handles 
     *                  stylus popup events.
     * @param aPoint The position where stylus was tapped
     * @param aPopup Preview popup from which stylus popup
     *               menu was launched, can be NULL.
     */
    IMPORT_C static CAknStylusPopUpMenu* NewL( MEikMenuObserver* aObserver, 
                                         const TPoint& aPoint,
                                         CAknPreviewPopUpController* aPopup );
    
    /**
     * Two-phased constructor
     *
     * @param aObserver Menu observer (not owned) that handles 
     *                  stylus popup events.
     * @param aPoint The position where stylus was tapped
     */
    IMPORT_C static CAknStylusPopUpMenu* NewL( MEikMenuObserver* aObserver, 
                                         const TPoint& aPoint );

    /**
     * Two-phased constructor
     *
     * @param aObserver Menu observer (not owned) that handles 
     *                  stylus popup events.
     * @param aPoint The position where stylus was tapped
     * @param aPopup Preview popup from which stylus popup
     *               menu was launched, can be NULL.
     */
    IMPORT_C static CAknStylusPopUpMenu* NewLC( MEikMenuObserver* aObserver, 
                                         const TPoint& aPoint,
                                         CAknPreviewPopUpController* aPopup );
    /**
     * Destructor
     */    
    ~CAknStylusPopUpMenu();
    
    /**
     * Adds a menu item. If the menu contains maximum amount of
     * items, the function will do nothing. Inserted item will be
     * placed last.
     *
     * @param aItem The menu item to be added.
     * @param aCommandId Item's command id.
     */
    IMPORT_C void AddMenuItemL( const TDesC& aItem, const TInt aCommandId );
    
    /**
     * Removes a menu item.
     *
     * @param aCommandId Command id of the item to be removed.
     */
    IMPORT_C void RemoveMenuItem( const TInt aCommandId );

    /**
     * Hides / shows a menu item.
     *
     * @param aCommandId Command id of the item to be hidden / shown.
     * @param aDimmed ETrue to hide item and EFalse to show item
     */
    IMPORT_C void SetItemDimmed( const TInt aCommandId, const TBool aDimmed );

    /**
     * Shows the stylus popup menu. If it's already visible,
     * nothing happens.
     */
    IMPORT_C void ShowMenu();
        
    /**
     * Sets the position of the stylus popup menu. 
     * Position will be adjusted if the menu doesn't fit on the screen
     * properly.
     *
     * @param aPoint Position of the left-top corner of the stylus popup menu.
     */
    IMPORT_C void SetPosition( const TPoint& aPoint );    
    /**
     * Sets the position of the stylus popup menu. 
     * Position will be adjusted if the menu doesn't fit on the screen
     * properly.
     *
     * @param aPoint Position of the stylus popup menu.
     * @param aPosType  Position type e.g. left-top corner or right-top corner  
     */
    IMPORT_C void SetPosition( const TPoint& aPoint, TPositionType aPosType );    

    /**
     * Tells the popup menu to recalculate its position. This can be used e.g.
     * after layout transition.
     */
    void UpdatePosition();

    /**
     * Removes all menu items.
     * 
     * @internal
     * @since s60 v5.2
     */
    void Clear();

// from base class CCoeControl

    /**
     * Constructs the menu from resource.
     *
     * @param aReader Resource reader.
     */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

// from base class MCoeControlObserver
    
    /**
     * Method to handle events that occur when user selects a menu item.
     *
     * @param aControl The control that sent the event.
     * @param aEventType The event type.
     */
    IMPORT_C void HandleControlEventL( CCoeControl* aControl,
                                       TCoeEvent aEventType );


private:

    /**
     * Default constructor
     *
     * @param aObserver Menu observer (not owned) that handles 
     *                  stylus popup events.
     * @param aPoint The position where stylus was tapped
     * @param aPopup Preview popup from which stylus popup
     *               menu was launched, can be NULL.
     */
    CAknStylusPopUpMenu( MEikMenuObserver* aObserver, const TPoint& aPoint,
                         CAknPreviewPopUpController* aPopup );

    /**
     * 2nd phase constructor
     */
    void ConstructL();

    /**
     * Starts the CIdle
     */
    void StartControllerIdleL();
    
    /**
     * CIdle callback function 
     */
    static TInt ControllerCallBack( TAny* aThis );
    
    /**
     * Removes the controller
     */
    void RemoveController();
    
private: // data

    /**
     * Screen relative position where stylus was tapped.
     */
    TPoint iPosition;
    
    /**
     * Controller for the actual popup.
     * Own.
     */
    CAknPreviewPopUpController* iController;
    
    /**
     * Popup's content.
     * Own.
     */
    CAknStylusPopUpMenuContent* iContent;
    
    /**
     * Observer which will be used to forward selected menu command id.
     * Not own.
     */
    MEikMenuObserver* iMenuObserver;
    
    /**
     * Preview popup which launches stylus popup menu.
     * If NULL, menu wasn't launched from a preview popup.
     * If not NULL, stylus popup menu will close also the preview popup
     * when an option is selected in the stylus popup menu.
     * Not own.
     */
    CAknPreviewPopUpController* iPreviewPopup;
    
    /**
     * An idle time active object 
     * Own
     */
    CIdle* iControllerIdle;
    
    /**
     * Position type
     */
    TInt iPositionType;

    /**
     * Internal flags.
     */
    TBitFlags iFlags;
    
    /**
     * Used to track if object has been deleted while calling client callback.
     */
    TBool* iIsDeleted;
    };


#endif // CAKNSTYLUSPOPUPMENU_H
