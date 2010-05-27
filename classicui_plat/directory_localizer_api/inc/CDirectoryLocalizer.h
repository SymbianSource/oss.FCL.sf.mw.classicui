/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Directory Localizer interface class
*
*/



#ifndef C_CDIRECTORYLOCALIZER_H
#define C_CDIRECTORYLOCALIZER_H

#include <e32def.h>

class TResourceReader;


/**
 *  Directory Localizer interface class.
 *
 *  @lib directorylocalizer.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS(CDirectoryLocalizer) : public CBase
    {
public: // Constructors and destructor    

    /**
     * Two-phased constructor.
     * Construct a CDirectoryLocalizer and initialize it with platform specific 
     * default localization data.
     * 
     * @return apointer to the created instance of CDirectoryLocalizer.
     */
    IMPORT_C static CDirectoryLocalizer* NewL();

    /**
     * Two-phased constructor.
     * Construct a CDirectoryLocalizer and initialize it from resource pointed 
     * by aReader.
     * 
     * @param aReader Reference to an initialized resource reader instance.
     * @return apointer to the created instance of CDirectoryLocalizer.
     */
    IMPORT_C static CDirectoryLocalizer* NewL( TResourceReader& aReader );

    /**
     * Two-phased constructor.
     * Construct a CDirectoryLocalizer and initialize it from a resource ID.
     * 
     * @param aResourceId Resource identifier to DIRECTORYLOCALIZER resource.
     * @return apointer to the created instance of CDirectoryLocalizer.
     */
    IMPORT_C static CDirectoryLocalizer* NewL( TInt aResourceId );

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CDirectoryLocalizer();

public: // New methods
	
    /**
     * Adds entries to the localizer from resource pointed by aReader.
     *
     * @param aReader Reference to an initialized resouce reader instance.
     * @return None.
     */
    IMPORT_C void AddFromResourceL( TResourceReader& aReader );

    /**
     * Adds entries to the localizer from resource pointed by aResourceId.
     *
     * @param aResourceId Resource identifier to DIRECTORYLOCALIZER resource.
     * @return None.
     */
    IMPORT_C void AddFromResourceL( TInt aResourceId );

    /**
     * This method is used to set the absolute path to be localized.
     * For example "c:\\nokia\\images\\pictures". Take care that the path
     * is given with or without the trailing backslash depending on
     * how the paths are defined in the resource. localizer can utilize 
     * pathinfo to retrieve predefined folder paths.
     *
     * @param aFullPath Full path name.
     * @return None. 
     *
     * @code
     *  #include <PathInfo.h>
     *
     *  // Get the the full path of the contacts folder in the memory card.
     *  TFileName path = PathInfo::GetPath( PathInfo::EImagesPath );
     *
     *  // 'path' contains now the images path to be appended to a root path.
     *
     * CDirectoryLocalizer loc = CDirectoryLocalizer::NewL();
     * loc->SetFullPath ( path );
     * @endcode     
     *
     * @see PathInfo
     */
    IMPORT_C void SetFullPath( const TDesC& aFullPath );

    /**
     * Tells if the last given path is recognized as a localized directory.
     *
     * @return ETrue if last given path is localized and EFalse if not.
     */
    IMPORT_C TBool IsLocalized() const;

    /**
     * Returns a reference to a TDesC that contains the last given path's
     * localized name. If the path is not a localized directory, then
     * a pointer to KNullDesc is returned.
     *
     * @return the last given path's localized name.
     */
    IMPORT_C const TDesC& LocalizedName() const;

    /**
     * Returns a reference to a TDesC that contains the last given path's
     * extra data. If the path is not a localized directory or no extra
     * data is defined, then a pointer to KNullDesc is returned.
     *
     * @return the last given path's extra data.
     */
    IMPORT_C const TDesC& ExtraData() const;

    /**
     * Returns the icon index of the last given path. If the path is not a
     * localized directory KErrGeneral is returned.
     *
     * @return the icon index of the last given path.
     *
     * @code
     * CDirectoryLocalizer loc = CDirectoryLocalizer::NewL();
     * loc-> SetFullPath( aDir );
     * if ( loc->Icon() != KErrGeneral )
     *     {
     *     //...
     *     }
     * @endcode       
     */
    IMPORT_C TInt Icon() const;

protected:

    /**
     * C++ default constructor.
     */
    CDirectoryLocalizer();
 
    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();

private: // data

    /**
     * The index of the current entry.
     */
    TInt iCurrentEntry;

    /**
     * A pointer to the array for paths.
     * Own.
     */
    CArrayPtrFlat<TDesC>* iPaths;

    /**
     * A pointer to the array for localised names.
     * Own.
     */
    CArrayPtrFlat<TDesC>* iLocalizedNames;

    /**
     * A pointer to the array for extra data.
     * Own.
     */
    CArrayPtrFlat<TDesC>* iExtraData;

    /**
     * The array for icon indices.
     */
    RArray<TInt> iIconIndices;
    
    };

#endif // C_CDIRECTORYLOCALIZER_H
