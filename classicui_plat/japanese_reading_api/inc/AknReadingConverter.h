/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef AKNREADINGCONVERTER_H
#define AKNREADINGCONVERTER_H

// INCLUDES
#include <e32base.h>
#include <fepbase.h>

// FORWARD DECLARATIONS
class CEikEdwin;

// CLASS DECLARATION

/**
*
* This utility class is used for updating reading fields in the Japanese Series 60 platform. 
* Class binds two editors together: user enters kanji characters to the "main" editor. 
* When a kanji character entry is completed this object updates the "reading" editor.
*
* This class is not intended for further derivation.
*
* @since 2.6
*
* @internal
*/
NONSHARABLE_CLASS(CReadingConverter) : public CBase, MCoeFepObserver
    {
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @since 2.6
        * @param aMainEditor      Reference to main editor. Ownership is not transferred.  
        * @param aReadingEditor   Reference to reading editor. Ownership is not transferred.  
        *
        * @return Newly constructed object.
        */
        IMPORT_C static CReadingConverter* NewL(CEikEdwin& aMainEditor, CEikEdwin& aReadingEditor);

        /**
        * Two-phased constructor.
        *
        * @since 2.6
        * @return Newly constructed object.
        */
        IMPORT_C static CReadingConverter* NewL();

        /**
        * Destructor.
        */
        virtual ~CReadingConverter();

    public: // From MCoeFepObserver

        /**
        * This method is the main method of this class. It is called by the FEP and
        * it checks that main editor has focus, requests reading text from CAknJapaneseReading
        * class and sets the received text into reading editor.
        *
        * @since 2.6
        */
        IMPORT_C virtual void HandleCompletionOfTransactionL(); 

    public: // New functions

        /**
        * Set method for setting main editor.
        *
        * @since 2.6
        * @param aReadingEditor   Reference to main editor. Ownership is not transferred.
        *
        */
        IMPORT_C void SetMainEditor(CEikEdwin& aMainEditor);

        /**
        * Get method for main editor.
        *
        * @since 2.6
        * @return Reference to main editor
        *
        */
        IMPORT_C CEikEdwin& MainEditor() const;

        /**
        * Set method for setting reading editor.
        *
        * @since 2.6
        * @param aReadingEditor   Reference to reading editor. Ownership is not transferred.
        *
        */
        IMPORT_C void SetReadingEditor(CEikEdwin& aReadingEditor);

        /**
        * Get method for reading editor.
        *
        * @since 2.6
        * @return Reference to reading editor
        *
        */
        IMPORT_C CEikEdwin& ReadingEditor() const;

    private:

        /**
        * C++ default constructor.
        */
        CReadingConverter(CEikEdwin* aMainEditor, CEikEdwin* aReadingEditor);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private: // Data

        CEikEdwin*      iMainEditor;      // Not owned
        CEikEdwin*      iReadingEditor;   // Not owned  
        HBufC*          iPreviousMainText; // own
    };

#endif // AKNREADINGCONVERTER_H
