/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*  Description:
*       Classes used for holding inline text for Phone number editors for the 
*       Form MTmInlineTextSource interface.
*
*
*/


#ifndef AKNPHONENUMBERINLINETEXTSOURCE_H
#define AKNPHONENUMBERINLINETEXTSOURCE_H

// INCLUDES

#include "AknInlineText.h"
#include "txtetext.h"

class CPNGNumberGrouping;
class CEikEdwin;
class CTextLayout;

// CONSTANTS

// CLASS DECLARATION

/**
* Base class for all phone number oriented inline text source classes
*
* This class offers some standard services:
* <ul>
* <li>management of the re-sizeing/re-construction of a CPNGPhoneNumber engine</li>
* <li>storage of a CPlainText reference for access to the editor buffer</li>
* <li>generation and storage of inline texts in the inline text store using the services of the
*   phone number grouping engine</li>
* </ul>
* 
*  @lib EikCoCtl
*  @since 2.6
*/
NONSHARABLE_CLASS(CAknPhoneNumberInlineTextSource) : public CAknInlineTextSource
    {
    public: 
        /**
        * C++ constructor
        */
        CAknPhoneNumberInlineTextSource( const CPlainText& aText );

        /**
        * Destructor.
        */
        ~CAknPhoneNumberInlineTextSource();

    protected: // new Methods

        /**
        * Accessor for the reference to the backing store
        *
        * @since 2.6
        * @return   reference to the text buffer interface
        */
        const CPlainText& Text() const;

        /**
        * Method to construct or re-construct the owned Number Grouping engine
        *
        * This method must be called during the 2nd stage construction of concrete subclasses, using a
        * default max phone number length determined by the subclass.
        * 
        * It is called by this class in FormatPhoneNumberL whenever a too-big phone number needs 
        * to be grouped.
        *
        * The method performs the safe deletion and re-construction of the new, resized engine.
        *
        * It may be called again by subclasses when it is determined that the numbers to be
        * grouped will all be smaller than a given size. Current size can be determined with
        * PhoneNumberGrouping().MaxDisplayLength()
        * 
        * @param    aSize   new maximum size for the (ungrouped) phone number in the engine
        * @since 2.6
        */
        void ConstructNumberGroupingEngineL( TInt aSize );

        /**
        * Method to format and store inline texts for a phone number
        *
        * @param    aPhoneNumberBuf     Ungrouped phone number to be grouped and inline
        *                               texts generated.
        * @param    aOffset             Document position for the beginning of aPhoneNumberBuf
        * @since 2.6
        */
        void FormatPhoneNumberL( const TDesC& aPhoneNumberBuf, TInt aOffset );

        /**
        * Access to the phone number grouping engine
        * 
        * @since 2.6
        * @return   pointer to the owned phone number grouping engine
        */
        CPNGNumberGrouping* PhoneNumberGrouping() const;

    private:
        // reference to the text buffer for the editor
        const CPlainText& iText; 
        // owned pointer to a phone number grouping engine instance
        CPNGNumberGrouping* iPhoneNumberGrouping;
        
    };

/**
* Class performing the custom formatting of an entire CEikEdwin buffer treated as a phone number.
* 
* The class adds the parsing ("which text is a phone number?") and implements the inline text
* update policy.  The parsing is simple: the entire contents of the editor, short of the end of 
* paragraph mark, are treated as phone number.  The update of inline texts is driven not by observing
* editing events (they are not available for CEikEdwin) but by the CheckFormattingL framework driven
* by the Form inline text fetches themselves.
* 
*  @lib EikCoCtl
*  @since 2.6
*/
NONSHARABLE_CLASS(CAknPlainPhoneNumberInlineTextSource) : public CAknPhoneNumberInlineTextSource
    {

    public: 
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknPlainPhoneNumberInlineTextSource* NewL( const CPlainText& aText );
    
        /**
        * Destructor.
        */
        virtual ~CAknPlainPhoneNumberInlineTextSource();

    private: // From CAknInlineTextSource
        /**
        * Implementation of framework method. Documented in header
        */
        virtual void CheckFormattingL(const TTmDocPos& aFrom, const TTmDocPos& aTo );

    private: // New Methods

        /**
        * C++ default constructor.
        */
        CAknPlainPhoneNumberInlineTextSource( const CPlainText& aText );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * non-virtual implementation method for CheckFormattingL
        */
        void DoFormatL();

        /**
        * Extract text from the editor with all extraneous characters removed
        *
        * @since 2.6
        * @return   TPtrC pointing to purely textual part of the CPlainText object
        */
        TPtrC PhoneNumberFromEditor(TInt& aStartPos) const;

        /**
        * wrap-up of the comparison of the phone number with that stored in the phone number engine
        */
        TInt CompareTextWithUnformattedNumber() const;
    
        /**
        * wrap-up of the access to the length of the number stored in the phone number engine
        */
        TInt StoredNumberLength() const;

    private:   // Data

    };

#endif

// End of File
