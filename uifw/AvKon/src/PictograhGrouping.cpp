/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Defined avkon pictograph ranges to show in SCT
*
*/



// INCLUDE FILES
#include    "PictograhGrouping.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// PictograhGrouping::AllocStringLC
// Return pictograph string to show in SCT
// -----------------------------------------------------------------------------
//
HBufC* PictograhGrouping::AllocStringLC(
    TAknPictographGroupType aType)
    {

    struct TPictograhGrouping
        {
        TUint iStart;
        TUint iEnd;
        };
    static const TPictograhGrouping pictograph1[] = 
        {
        { 0xE63E, 0xE6A5 },
        { 0xE6AC, 0xE6AE },
        { 0xE6B1, 0xE6B3 },
        { 0xE6B7, 0xE6BA },
        { 0xE6CE, 0xE70B }
        };
    static const TPictograhGrouping pictograph2[] = 
        {
        { 0xE70C, 0xE757 }
        };

    const TPictograhGrouping* base = 
                (aType == TAknPictographGroup2)? pictograph2 : pictograph1;
    const TInt sizeoftable = 
                (aType == TAknPictographGroup2)? sizeof(pictograph2) : sizeof(pictograph1);
    const TPictograhGrouping* end = base + 
                ( sizeoftable / sizeof(base[0]) -1);
    const TUint len = end->iEnd - base->iStart + 1;

    HBufC* buf = HBufC::NewLC(len);
    TPtr ptr(buf->Des());

    TInt count = 0;
    while (base <= end)
        {
        for ( TChar ch = base->iStart; ch <= TChar(base->iEnd); )
            {
            ptr.Append(ch);
            count++;
            ch += 1;
            }
        base++;
        }
    return buf;
    }

//  End of File  
