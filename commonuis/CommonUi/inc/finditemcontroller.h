/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef FINDITEMCONTROLLER_H
#define FINDITEMCONTROLLER_H

//  INCLUDES
#include <e32base.h>
#include <finditemengine.h>

// FORWARD DECLARATIONS
class CPlainText;
class CRichText;
class MFindItemDialogCallBack;

// CLASS DECLARATION

/**
*   FindItem's controller class.
*       - Takes care of communication between dialog and engine classes
*       - Updates editor (directly or inderectly using the dialog class)
*/
NONSHARABLE_CLASS(CFindItemController) :public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        * 
        * @param aDialog        Callback pointer to a dialog class
        * @param aRichText      Pointer to richtext that needs to be edited (underlined)
        * @param aText Text     that needs to be parsed
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumber
        *                           EFindItemSearchMailAddress
        *                           EFindItemSearchURL
        *
        * @return   Pointer to constructed controller
        */
        static CFindItemController* NewL( 
            MFindItemDialogCallBack* aDialog, 
            CRichText* aRichText, 
            const TDesC& aText, 
            const CFindItemEngine::TFindItemSearchCase aSearchCase );
        
        /**
        * Destructor.
        */
        virtual ~CFindItemController();

    public: // New functions
        /**
        * Gives the currently 'selected' item
        *
        * @param aItem Holds currently selected item
        *
        * @return EFalse if no items were found
        */
        inline TBool Item( CFindItemEngine::SFoundItem& aItem ) const;

        /**
        * Moves the selection to next item
        *
        * @return EFalse if there's no next item.
        */
        TBool NextItemL();
        
        /**
        * Moves the selections to previous item
        *
        * @return EFalse if there's no previous item.
        */
        TBool PrevItemL();

        /**
        * Move into next row, where found item is
        */
        void MoveDownL();

        /**
        * Move into previous row, where found item is
        */
        void MoveUpL();

        /**
        * Marks found items
        *   - Underlines all found strings
        *   - Updates the selection
        *
        * @return Returns EFalse if zero items were found
        */
        void MarkFoundItemsL();

        /**
        * Fills array with items (TInts) which causes scrollbar to move
        *   i.e. items that are not in the same line
        *
        * @param aArray Array that needs to be filled
        */
        void FillScrollBarItemsArrayL( CArrayFixFlat<TInt>* aArray );

        /**
        * Position and count methods
        */
        inline const TInt Position() const; // Returns current position
        inline const TBool FirstItem() const; // Returns ETrue if at first item
        inline const TBool LastItem() const; // Returns ETrue if at last item

        inline const TInt ItemCount() const; // Returns the number of found items

        /**
        * Check if item is at the same line as first item
        *   Needed for Scrollbar (if text's length is over 2000 chars)
        */
        TBool IsAtSameLineAsFirstItem();

        /**
        * Check if item is at the same line as last item
        *   Needed for Scrollbar (if text's length is over 2000 chars)
        */
        TBool IsAtSameLineAsLastItem();

        /*
        * Moves the selections to tapped item.
        *
        * @return EFalse if no tapped item selected.
        */
        TBool TappedItemL( const TInt index );
        
        /**
        * Get indexed item from find engine.    
        *
        * @param aIndex Item index in engine side.
        * @param aItem item to be retrieved.
        *
        * @return EFalse if no item was found.
        */
        TBool Item( 
            const TInt aIndex, 
            CFindItemEngine::SFoundItem& aItem ) const;

    private:

        /**
        * C++ default constructor.
        */
        CFindItemController();

        /**
        * EPOC constructor
        *
        * @param aText          Text that will be parsed
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumber
        *                           EFindItemSearchMailAddress
        *                           EFindItemSearchURL
        */
        void ConstructL( 
        	const TDesC& aText, 
        	const CFindItemEngine::TFindItemSearchCase aSearchCase );
        	
    	/**
		* Get minimum number of digits to find.
		*/
		TInt GetMinDigitsToFindL();
     

    private:    // Data
        // Engine
        CFindItemEngine* iEngine;
        // Found item
        CFindItemEngine::SFoundItem iItem;
        // Association to EEikRichTextEditor's RichText
        CRichText* iRichText;
        // CallBack to dialog
        MFindItemDialogCallBack* iDialog;

    };

#include "finditemcontroller.inl" // inline methods

#endif      // FINDITEMCONTROLLER_H   

// End of File
