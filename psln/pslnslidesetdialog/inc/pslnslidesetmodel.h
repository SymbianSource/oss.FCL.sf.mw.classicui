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
* Description:  Slide set settings model.
*
*/


#ifndef C_PSLNSLIDESETMODEL_H
#define C_PSLNSLIDESETMODEL_H

#include <e32base.h>
#include <badesca.h>

class CRepository;

/**
 *  This is model class for slide set settings. 
 *
 *  It stores and retrieves setting values.
 *
 *  @lib pslnslidesetsettings.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CPslnSlideSetModel ): public CBase
    {
public:

    /**
     * Symbian OS two-phased constructor
     * @return CPslnSlideSetModel instance.
     */
    static CPslnSlideSetModel* NewL();

    /**
     * Symbian OS two-phased constructor
     * @return CPslnSlideSetModel instance.
     */
    static CPslnSlideSetModel* NewLC();

    /**
     * Destructor.
     */
    virtual ~CPslnSlideSetModel();

    /**
     * Returns current selection for slide set type: random / image set.
     *
     * @param aSlideSetType slide set type: wallpaper / screensaver.
     * @return current value for slide set type. In case of error, 
     *         default value is returned.
     */
    TInt GetSlideSetType( const TInt aSlideSetType ) const;

    /**
     * Stores new slide set image selection type value to repository
     *
     * @param aSlideSetType slide set type: wallpaper / screensaver.
     * @param aValue new value for slide set image selection type.
     * @return KErrNone, if operation is successful; otherwise either
     *         repository given error code, or if the aValue is not 
     *         valid, KErrArgument.
     */
    TInt SetSlideSetType( const TInt aSlideSetType, const TInt aValue );

    /**
     * Returns current selection for screensaver slide set duration.
     *
     * @return current value for slide set type. In case of error, 
     *         default value is returned.
     */
    TInt GetSlideSetDuration() const;

    /**
     * Stores new slide set duration value to repository.
     *
     * @param aValue new value for slide set duration.
     * @return KErrNone, if operation is successful; otherwise either
     *         repository given error code, or if the aValue is not 
     *         valid, KErrArgument.
     */
    TInt SetSlideSetDuration( const TInt aValue );

    /**
     * Returns current selection for screensaver slide set backlight period.
     *
     * @return current value for slide set backlight period. In case of error, 
     *         default value is returned.
     */
    TInt GetSlideSetBacklight() const;

    /**
     * Stores new slide set backlight period value to repository.
     *
     * @param aValue new value for slide set backlight period.
     * @return KErrNone, if operation is successful; otherwise either
     *         repository given error code, or if the aValue is not 
     *         valid, KErrArgument.
     */
    TInt SetSlideSetBacklight( const TInt aValue );

    /**
     * Returns current selection for screensaver slide set image interval.
     *
     * @return current value for slide set image interval. In case of error, 
     *         default value is returned.
     */
    TInt GetSlideSetInterval() const;

    /**
     * Stores new slide set image interval value to repository.
     *
     * @param aValue new value for slide set image interval.
     * @return KErrNone, if operation is successful; otherwise either
     *         repository given error code, or if the aValue is not 
     *         valid, KErrArgument.
     */
    TInt SetSlideSetInterval( const TInt aValue );

    /**
     * Stores list of image filenames to be used as slide set image set.
     *
     * @param aSelectedFiles list of files to set as wallpaper slide set.
     */
    void SetImageListL( 
        const TInt aSlideSetType, 
        CDesCArray& aSelectedFiles, 
        const TInt aLaunchMode );

    /**
    * Checks if the slide set file exists.
    * 
    * @param aSlideSetType type of slide set (wallpaper/screensaver).
    * @return ETrue if file exists, otherwise EFalse.
    */
    TBool SlideSetImageFileExistsL( const TInt aSlideSetType ) const;

    /**
    * Checks if there has been changes to image list. 
    * 
    * @return ETrue if image list has been changed, EFalse otherwise.
    */
    TBool HasDialogUpdatedValues() const;

    /**
    * Count the number of images in the image file.
    * @param aSlideSetType type of slide set (wallpaper/screensaver).
    * @return number of images in the file, or zero if no file exists.
    */
    TInt GetImageCountInSlideSetL( const TInt aSlideSetType ) const;
    
    /**
    * Sets feature support - see pslnslidesetconst.h for feature list.
    * @param aFeatureBitFlags feature support bitflags.
    */
    void GetFeatureSupportL( TBitFlags& aFeatureBitFlags ) const;

private:

    /**
    * C++ constructor.
    */
    CPslnSlideSetModel();

    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

    /**
    * Stores image list to a file.
    */
    void StoreImageListToFileL( 
        const TInt aSlideSetType, CDesCArray& aSelectedFiles ) const;

    /**
    * Opens image list file for operations.
    */
    void OpenImageFileL( RFile& aImageFile, const TInt aSlideSetType ) const;

private: // data

    /**
     * Central repository object. Used for storing and retrieving data.
     * Own.
     */
    CRepository* iRepository;

    /**
     * Indicates if the slide set image list has been changed.
     */
    TBool iImageListChanged;
    
    /**
     * Coe environment reference.
     * Own.
     */
    CCoeEnv* iCoeEnv;
    };


#endif // C_PSLNSLIDESETMODEL_H
