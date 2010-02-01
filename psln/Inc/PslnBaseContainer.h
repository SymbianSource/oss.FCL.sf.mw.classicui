/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for Psln's view containers.
*
*/


#ifndef C_PSLNBASECONTAINER_H
#define C_PSLNBASECONTAINER_H

#include    <coeccntx.h>
#include    <eikclb.h>

class CPslnModel;
class MPslnFWMSKObserver;

/**
* Base class for Psln's view containers.
*
*/
class CPslnBaseContainer : public CCoeControl
    {
    public:

        /**
        * Symbian default constructor.
        */
        CPslnBaseContainer();

        /**
        * Symbian two-phase constructor.
        * @param aRect Listbox's rect.
        */
        virtual void ConstructL( const TRect& aRect ) = 0;

        /**
        * Constructs all common parts of the container.
        * @param aRect Listbox control's rect.
        * @param aResLbxId Resource id for listbox.
        */
        void BaseConstructL( const TRect& aRect, TInt aResLbxId );

        /**
        * Constructs all common parts of the container.
        * @param aRect Listbox control's rect.
        * @param aResTitleId Resource id for title.
        * @param aResLbxId Resource id for listbox.
        */
        void BaseConstructL(
            const TRect& aRect,
            TInt aResTitleId, 
            TInt aResLbxId );

        /**
        * Destructor.
        */
        ~CPslnBaseContainer();

        /**
        * Sets listbox observer.
        * @param aObserver observer object.
        */
        void SetListBoxObserver( MEikListBoxObserver* aObserver );

        /**
        * Returns currently selected item index.
        * @return currently selected item index.
        */
        virtual TInt CurrentItemIndex() const;

        /**
        * Sets current item index and draws container. If index is invalid, 
        * it is set to zero (=first item).
        * @param aNewIndex new current index.
        */
        virtual void SetCurrentItemIndexAndDraw( TInt aNewIndex );
	        
        /**
        * Sets current item index. If index is invalid, 
        * it is set to zero (=first item).
        * @param aNewIndex new current index.
        */
        virtual void SetCurrentItemIndex( TInt aNewIndex );
        
        /**
        * Defines observer for the middle softkey label changes.
        * Can only be set once. Further attempts are ignored.
        * @since S60 v3.1
        */
        virtual void SetMiddleSoftkeyObserver( MPslnFWMSKObserver* aObserver );

        /**
        * Returns MSK Observer, if any.
        * @return observer for MSK label changes, or NULL if it is not defined.
        * @since S60 v3.2
        */
        MPslnFWMSKObserver* GetMiddleSoftkeyObserver();

    protected:

        /**
        * Updates listbox or specific one item.
        */
        virtual void UpdateListBoxL();

        /**
        * Constructs listbox.
        * @param aResLbxId Resource id for listbox.
        */
        virtual void ConstructListBoxL( TInt aResLbxId ) = 0;

        /**
        * Processes key events.
        * @param aKeyEvent
        * @param aType
        * @return response
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent, 
            TEventCode aType );

        /**
        * Creates list box items.
        */
        virtual void CreateListBoxItemsL() = 0;

    private:

        /* From CCoeControl. */
        void SizeChanged();

        /* From CCoeControl. */
        TInt CountComponentControls() const;

        /* From CCoeControl. */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /* From CCoeControl. */
        virtual void HandleResourceChange( TInt aType );

        /* Handles focus change events in list item. */
        void FocusChanged( TDrawNow aDrawNow );

    protected:

        /**
        * Model reference.
        * Not own.
        */
        CPslnModel* iModel;

        /**
        * Listbox.
        * Own.
        */
        CEikTextListBox* iListBox;

        /**
        * List of items in listbox.
        * Not own (owned by listbox).
        */
        CDesCArray* iItemArray;

        /**
        * Middle softkey label observer.
        * Own.
        */
        MPslnFWMSKObserver* iMSKObserver;
    };

#endif // C_PSLNBASECONTAINER_H

// End of File
