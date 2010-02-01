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
* Description: 
*     Classes used for holding inline text for the Form MTmInlineTextSource interface.
* 
*
*/


#ifndef AKNRICHTEXTPHONENUMBERINLINETEXTSOURCE_H
#define AKNRICHTEXTPHONENUMBERINLINETEXTSOURCE_H

// INCLUDES

#include "AknInlineText.h"
#include "AknPhoneNumberInlineTextSource.h"
#include "txtrich.h"

class CPNGNumberGrouping;
class CEikEdwin;
class CTextLayout;
class CFindItemEngine;

// CONSTANTS


// CLASS DECLARATION

/**
* Specialized inline text source for the formatting of phone numbers recognized in general text.
*
* Such an implementation is restricted to CEikRichTextEditors because only there is there an
* edit observer mechanism that allows the re-formatting of the text into phone numbers to be
* performed only when necessary.
*
*  @lib EikCoCtl
*  @since 2.6
*/
NONSHARABLE_CLASS(CAknRichTextPhoneNumberInlineTextSource) : public CAknPhoneNumberInlineTextSource
    {
    public:

        /**
        * Two-phased constructor.
        */
        static CAknRichTextPhoneNumberInlineTextSource* NewL( const CRichText& aText );

        /**
        * Destructor.
        */
        virtual ~CAknRichTextPhoneNumberInlineTextSource();

    public: // Functions from MEditObserver

        /**
        * See medobsrv.h
        */
        virtual void EditObserver( TInt aStart, TInt aExtent );

    private:

        /**
        * C++ constructor.
        */
        CAknRichTextPhoneNumberInlineTextSource( const CRichText& aText);

        /**
        * 2nd phase constructor
        */
        void ConstructL();

        /**
        * Method for determining if the next character after a phone number is valid.
        * 
        * @param    aNextPos  a position in the RichText buffer immediately after the candidate phone number
        * @returns  ETrue       if the next character does not exist or is valid
        */
        TBool FollowingCharIsValid( TInt aNextPos ) const;


    private: // Data

        // owned pointer to an engine to find the phone numbers
        CFindItemEngine* iFindItemEngine;
    };

#endif

// End of File
