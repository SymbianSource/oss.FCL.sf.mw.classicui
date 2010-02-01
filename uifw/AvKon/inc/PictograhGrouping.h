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



#ifndef PICTOGRAPH_GROUPING_H
#define PICTOGRAPH_GROUPING_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION

/**
*  Pictograph grouping.
*  This class is used for Japanese variant only.
*
*  @lib Avkon.lib
*  @since Series 60 2.6
*/
class PictograhGrouping
    {
   
    public:  // enum
        enum TAknPictographGroupType
            {
            TAknPictographGroup1,
            TAknPictographGroup2
            };

    public: // New functions
        /**
        * Return pictograph string to show in SCT.
        * @since Series 60 2.6
        * @param aType Pictograph group type
        *              set TAknPictographGroup1 or TAknPictographGroup2
        * @return Heap descriptor containing the Pictograph characters

        */
        static HBufC* AllocStringLC(TAknPictographGroupType aType);

    };

#endif      // PICTOGRAPH_GROUPING_H
            
// End of File
