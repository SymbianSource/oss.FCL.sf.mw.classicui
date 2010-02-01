/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Loads AknsWallpaperUtils dynamically.
*
*/


#ifndef C_PSLNWALLPAPERUTILSLOADER
#define C_PSLNWALLPAPERUTILSLOADER

#include <e32base.h>

/**
*  Interface class for wallpaper utils library.
*  
*  @lib PslnWallpaperUtilsLoader.lib
*  @since Series 60 3.1
*/
class MPslnWallpaperUtilsLoader
    {
    public:
        
        /**
        * Pure virtual method for setting Idle wallpaper.
        * @param aFilename filename of image.
        * @param aCoeEnv coe environment.
        * @param aWaitNoteTextResourceID wait note text if any.
        * @param aWaitNoteResourceID resource ID for wait note, if any.
        * @return error code, or KErrNone.
        */
        virtual TInt SetIdleWallpaper( 
            const TDesC& aFilename, 
            CCoeEnv* aCoeEnv, 
            TInt aWaitNoteTextResourceID = 0, 
            TInt aWaitNoteResourceID = 0 ) = 0;

    };

/**
*  This class is for dynamically loading AknsWallpaperUtils.dll that 
*  enables setting of wallpaper.
*
*  @lib PslnWallpaperUtilsLoader.lib
*  @since Series 60 3.1
*/
class CPslnWallpaperUtilsLoader : public CBase, public MPslnWallpaperUtilsLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CPslnWallpaperUtilsLoader.
    */
    static CPslnWallpaperUtilsLoader* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CPslnWallpaperUtilsLoader();

    /**
    * Sets Idle wallpaper.
    * @param aFilename filename of image.
    * @param aCoeEnv coe environment.
    * @param aWaitNoteTextResourceID wait note text if any.
    * @param aWaitNoteResourceID resource ID for wait note, if any.
    * @return error code, or KErrNone.
    */
    TInt SetIdleWallpaper( 
        const TDesC& aFilename, 
        CCoeEnv* aCoeEnv, 
        TInt aWaitNoteTextResourceID = 0, 
        TInt aWaitNoteResourceID = 0 );

private:

    /**
    * C++ default constructor.
    */
    CPslnWallpaperUtilsLoader();

    };

// Environment gate function
IMPORT_C TAny* GateFunction();

#endif // C_PSLNWALLPAPERUTILSLOADER
            
// End of File
