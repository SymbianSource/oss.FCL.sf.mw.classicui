/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for Psln plugin containers.
*
*/


#ifndef C_PSLNFWBASECONTAINER_H
#define C_PSLNFWBASECONTAINER_H

#include    <coeccntx.h>
#include    <eikclb.h>
#include    <mpslnfwmsklabelobserver.h>

/**
 *  Base class for Psln view containers.
 *
 *  @lib PslnFramework.lib
 *  @since S60 3.1
 */
class CPslnFWBaseContainer : public CCoeControl
    {

public:

    /**
    * Symbian OS default constructor.
    */
    IMPORT_C virtual void ConstructL( const TRect& aRect ) = 0;

    /**
    * Constructs all common parts of the container.
    *
    * @param aRect Listbox control's rect.
    * @param aResTitleId Resource id for title.
    * @param aResLbxId Resource id for listbox.
    */
    IMPORT_C void BaseConstructL(   const TRect& aRect,
                                    TInt aResTitleId,
                                    TInt aResLbxId );

    /**
    * Constructor.
    */
    IMPORT_C CPslnFWBaseContainer();

    /**
    * Destructor.
    */
    IMPORT_C virtual ~CPslnFWBaseContainer();
    
    /**
    * Sets the middle softkey label observer.
    * @param aObserver observer for msk label updations.
    * @since S60 v3.1
    */
    IMPORT_C void CPslnFWBaseContainer::SetMiddleSoftkeyObserver( 
        MPslnFWMSKObserver* aObserver );

protected:

    /**
    * Constructs listbox.
    * @param aResLbxId Resource id for listbox.
    */
    virtual void ConstructListBoxL( TInt aResLbxId );

private:

    /**
    * From CCoeControl.
    * Handles a change to the control's resources.
    * @param aType type of change.
    */
    IMPORT_C void HandleResourceChange( TInt aType );

    /**
    * From CCoeControl.
    * Responds to changes to the size and position of the contents 
    * of this control.
    */
    IMPORT_C void SizeChanged();

    /**
    * From CCoeControl.
    * Gets the number of controls contained in a compound control.
    * @return the number of controls this component contains.
    */
    IMPORT_C TInt CountComponentControls() const;

    /**
    * From CCoeControl.
    * Gets an indexed component of a compound control.
    */
    IMPORT_C CCoeControl* ComponentControl( TInt /*aIndex*/ ) const;

    /**
    * From CCoeControl.
    * Handles key events.
    * @param aKeyEvent key event.
    * @param aType type of key event.
    */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                          TEventCode aType );

    /**
    * From CCoeControl.
    * Responds to a change in focus.
    * @param aDrawNow Contains the value that was passed to it by SetFocus().
    */
    IMPORT_C void FocusChanged( TDrawNow aDrawNow );

public: // data

    /**
     * Pointer to newly created list box.
     * Owned.
     */
    CEikTextListBox* iListBox;

    /**
    * Observer for middle softkey label changes.
    * Owned.
    */
    MPslnFWMSKObserver* iMSKObserver;    

    };

#endif // C_PSLNFWBASECONTAINER_H

// End of File
