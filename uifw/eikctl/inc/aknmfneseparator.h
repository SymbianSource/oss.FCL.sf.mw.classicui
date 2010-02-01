/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Separator field for CEikMfne
*
*/

#ifndef CAknMfneSeparator_H
#define CAknMfneSeparator_H

//  INCLUDES
#include <eikmfne.h>

// CLASS DECLARATION

/** Reimplementation of CEikMfneSeparator
 *  Allows run-time changing of text
 */
class CAknMfneSeparator : public CEikMfneField
    {
    private:
        CAknMfneSeparator();

    public:
        virtual ~CAknMfneSeparator();
        static CAknMfneSeparator* NewL(const TDesC& aText);
        void SetTextL(const TDesC& aText);
        const TDesC& Text() const;
        void MakeVisible( TBool aVisible );

    private: // from CEikMfneField
        TInt MaximumWidthInPixels(
            const CFont& aFont,
            TBool aShrinkToMinimumSize);

        TCoeInputCapabilities InputCapabilities() const;

    private:
        HBufC* iText;
        TBool iVisible;
    };

#endif
