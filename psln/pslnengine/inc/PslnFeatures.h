/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class that defines supported features for Psln.
*
*/


#ifndef PSLNFEATURES_H
#define PSLNFEATURES_H

// INCLUDE FILES

#include <e32std.h>

// CLASS DECLARATION

/**
* Static class that defines features supported by Personalisation application.
*
*/
NONSHARABLE_CLASS( PslnFeatures )
    {
    public:

        /**
        * Checks whether help functionality is supported.
        * @return ETrue is Help is supported.
        */
        IMPORT_C static TBool IsHelpSupported();

        /**
        * Checks whether enhanced embedded links are supported.
        * @return ETrue if enhanced embedded links are supported.
        */
        IMPORT_C static TBool IsEnhancedEmbeddedLinksSupported();

        /**
        * Checks whether sounds in skins are supported.
        * @return ETrue if sounds in skins are supported.
        */
        IMPORT_C static TBool IsSoundsInSkinsSupported();

        /**
        * Checks whether memory card is supported.
        * @return ETrue if memory card is supported.
        */
        static TBool IsMMCSupported();

        /**
        * Checks whether APAC specific layouts are supported.
        * @return ETrue if APAC specific layouts are supported.
        */
        static TBool IsAPACSupported();
        
        /**
        * Check if given feature is supported or not. 
        * See feature IDs from PslnVariant.hrh.
        */
        IMPORT_C static TBool IsSupported( TInt aLocalVariationID );

    private:

        /**
        * Checks whether seamless links OR enhanced embedded links OR both
        * are supported.
        * @return ETrue if seamless links OR enchanced embedded links OR both
        * are supported.
        */
        static TBool IsSeamlessLinksSupported();

        /*
        * Same as above, but possibly leaves.
        */
        static TBool IsSupportedL( TInt aLocalVariationID );
    };

#endif // PSLNFEATURES_H
            
// End of File
