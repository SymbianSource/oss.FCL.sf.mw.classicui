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
* Description:  Toolbar extension component
*
*/


#ifndef CAKNTOOLBAREXTENSION_H
#define CAKNTOOLBAREXTENSION_H

#include <aknbutton.h>

class CAknToolbarItem;
class CAknToolbarExtensionView;
class CAknToolbar; 


/**
 *  Toolbar extension. 
 *
 *  Toolbar extension component. Opens an extension view when this extension
 *  is pressed.   
 *
 *  @lib eikcoctl
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknToolbarExtension ) : public CAknButton, 
    public MCoeControlObserver
    {

public:

    /**
     * Creates toolbar extension
     *
     * @return extension
     */
    static CAknToolbarExtension* NewL( );


    /**
     * Creates toolbar extension
     *
     * @param aResourceid The ID for this component's resource
     * @return extension
     */
    IMPORT_C static CAknToolbarExtension* NewL( TInt aResourceId );


    /**
     * Creates toolbar extension
     *
     * @param aResourceid The ID for this component's resource
     * @return extension
     */
    IMPORT_C static CAknToolbarExtension* NewLC( TInt aResourceId );

    /**
     * Destructor
     */
    ~CAknToolbarExtension();

// from base class CCoeControl

    /**
     * From CAknButton
     * constructs the extension from resource
     *
     * @param aReader resource reader
     */
    void ConstructFromResourceL( TResourceReader& aReader );

    /**
     * From CCoeControl
     * 
     * @param aKeyEvent information about the key event
     * @param aType type of the key event
     * @return boolean indicating if key event was consumed or not
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /**
     * From CCoeControl
     * Handles resource changes
     *
     * @param aType the type of the resource change
     */
    void HandleResourceChange( TInt aType ); 

    /**
     * From CCoeControl.
     * Makes extension and extension view visible or hides them
     *
     * @param aVisible boolean to tell if showing or hiding
     */
    void MakeVisible( TBool aVisible ); 


// from base class MCoeControlObserver

    /**
     * From MCoeControlObserver.
     * Here the events from the extension itself and extension view components
     * are handled
     *
     * @param aControl control that sent this event
     * @param aEventType type of the event
     */
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );


// new functions
    
    /**
     * Using this the extension view can get extension position in fixed toolbar
     *
     * @return index of the position
     */
    TInt ExtensionPosition(); 

    /**
     * Creates idle if it does not exist yet and calls it by giving 
     * a callback for notifying when ready to draw extension view. 
     */
    void ShowViewViaIdle(); 

    /**
     * Callback to get notified when ready to show extension view again
     * @param aThis pointer to this object
     * @return error code
     */
    static TInt ShowView( TAny* aThis ); 

    /**
     * Extension view tells extension to change state using this method. This is 
     * used when tapping outside extension view. 
     */
    void ViewClosed(); 

    /**
     * Gets a pointer to the specified control.
     *
     * @param aControlId The ID of the control for which a pointer is required.
     * @return Pointer to the control with the specified ID.
     */
    IMPORT_C CCoeControl* ControlOrNull( TInt aCommandId ) const; 

    /**
     * Adds one item to the specified place. Takes ownership. Leaves with 
     * value KErrNotSupported, if called when extension view is shown and 
     * with KErrArgument if aItem does not exist or aIndex is out of bound. 
     *
     * @param aItem The control.
     * @param aType The type of the new toolbar item.
     * @param aCommandId The command ID for this item.
     * @param aFlags The flags.
     * @param aIndex The index in array at which item should be added.
     */
    IMPORT_C void AddItemL( CCoeControl* aItem,
                            TInt aType,
                            TInt aCommandId,
                            TInt aFlags,
                            TInt aIndex );


    /**
     * Removes one item from the extension view. Leaves with value 
     * KErrNotSupported if called when extension view is shown. 
     *
     * @param aCommandId The ID of the item which should be removed.
     */
    IMPORT_C void RemoveItemL( TInt aCommandId );

    /**
     * Gets extension flags
     * 
     * @return extension flags
     */
    TInt ExtensionFlags(); 

    /**
     * Returns boolean indicating if extension view is shown. 
     * 
     * @return ETrue if shown, EFalse if not
     */
    IMPORT_C TBool IsShown() const; 

    /**
     * Shows or hides extension view. 
     * 
     * @param aShown to show or to hide 
     */
    IMPORT_C void SetShown( TBool aShown ); 

    /**
     * Returns pointer to extension view
     * 
     * @return pointer to extension view
     */
    CCoeControl* ExtensionView(); 

    /**
     * Sets item dimmed or undimmed
     * 
     * @param aCommandId command id of the item to be dimmed/undimmed 
     * @param aDimmed to dim or undim
     */
    IMPORT_C void SetItemDimmed( TInt aCommandId, TBool aDimmed ); 

    /**
     * Hides or unhides item. Leaves with value KErrNotSupported if called
     * when extension view is shown. 
     * 
     * @param aCommandId command id of the item to be hidden/unhidden 
     * @param aHide to hide or unhide
     */
    IMPORT_C void HideItemL( TInt aCommandId, TBool aHide ); 

private:

    /**
     * Constructor
     */
    CAknToolbarExtension();

    /**
     * Constructs the extension button by adding button states with icons
     */
    void BaseConstructL();

    /**
     * Constructs a control from resource
     *
     * @param aResourceId The id for this component's resource.
     */
    void ConstructFromResourceL( const TInt aResourceId );  

private: // data

    /**
     * Pointer to extension view. 
     * Own.  
     */
    CAknToolbarExtensionView* iView;

    /**
     * Pointer to toolbar, so that extension can notify toolbar about 
     * extension events   
     * Not own. 
     */
    CAknToolbar* iToolbar; 

    /**
     * idle to show extension again on top of other components when 
     * extension is shown when coming back to view. 
     * Own. 
     */
    CIdle* iIdle; 

    /**
     * Extension flags 
     */
    TInt iFlags; 
    };

#endif // CAKNTOOLBAREXTENSION_H
