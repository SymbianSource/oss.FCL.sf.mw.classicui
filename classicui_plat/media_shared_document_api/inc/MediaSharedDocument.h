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
* Description: 
*     This class extends standard CAknDocument behaviour by adding
*     means of simple data exchange between two applications sharing
*     document of this class type.  The application that is being
*     called has to be running as an embedded process
*     of the calling application.
*
*/


#ifndef __CMEDIASHAREDDOCUMENT_H__
#define __CMEDIASHAREDDOCUMENT_H__

// INCLUDES
#include <akndoc.h>
#include <eikapp.h>

// CLASS DEFINITION
/**
* This class extends standard CAknDocument behaviour by adding
* means of simple data exchange between two applications sharing
* document of this class type.  The application that is being
* called has to be running as an embedded process
* of the calling application.
*/
class CMediaSharedDocument : public CAknDocument
    {
    public: // Enumerations

        enum TMediaSharedMode
            {
            EModeNormal = 0,
            EModeNew,
            EModeNewMany
            };

    protected:  // Constructors

        /**
        * Constructor.
        * @param aApp Reference to the application object.
        */
        CMediaSharedDocument( CEikApplication& aApp ) : CAknDocument( aApp ),
            iAppStartMode( EModeNormal ) { }

    public: // New methods

        /**
        * Set application's embedding mode.
        * @param aMode The new mode.
        */
        inline void SetAppModeArg( const TInt aMode = EModeNormal );

        /**
        * Return application's embedding mode.
        * @return The current mode.
        */
        inline TInt GetAppModeArg();

        /**
        * Set application's data file name or path.
        * Caller may set target path where producer should place
        * generated file(s). If empty producer uses its default
        * location.
        * @param aFileName The new file name
        */
        inline void SetFileName( const TDesC& aFileName );

        /**
        * Get application's data file name.
        * @param aFileName The current file name
        */
        inline void GetFileName( TDes& aFileName );

        /**
         * Set application specific data.
         * @param aMode The new data value.
         */
        inline void SetAppData( const TInt aData );

        /**
         * Return application specific data.
         * @return The current data value.
         */
        inline TInt GetAppData();


    protected:  // data

        /**
        * Embedding launch mode argument.
        */
        TInt iAppStartMode;

        /**
        * Full path and name of media content passed from/to the parent process.
        */
        TFileName iFileName;

        /**
        * Application specific data.
        */
        TInt iAppData;

    };

inline void CMediaSharedDocument::SetAppModeArg( const TInt aMode )
    {
    iAppStartMode = aMode;
    }

inline TInt CMediaSharedDocument::GetAppModeArg()
    {
    return iAppStartMode;
    }

inline void CMediaSharedDocument::SetFileName( const TDesC& aFileName )
    {
    iFileName.Copy( aFileName );
    }

inline void CMediaSharedDocument::GetFileName( TDes& aFileName )
    {
    aFileName.Copy( iFileName );
    }

inline void CMediaSharedDocument::SetAppData( const TInt aData )
    {
    iAppData = aData;
    }

inline TInt CMediaSharedDocument::GetAppData()
    {
    return iAppData;
    }

#endif // __CMEDIASHAREDDOCUMENT_H__

// End of File
