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
* Description:  header file for application installer launcher.  
*
*/

#ifndef DOCAPPINSTLAUCHER_H
#define DOCAPPINSTLAUCHER_H

//  INCLUDES
#include <e32base.h>
#include <SWInstApi.h>

class RFile;

NONSHARABLE_CLASS(CDocAppInstLauncher) : public CActive
    {
    public:  // Constructors and destructor
     
        /**
        * Two-phased constructor.
        */
        static CDocAppInstLauncher* NewL();

        /**
        * Destructor.
        */
        virtual ~CDocAppInstLauncher();

    public: // New functions

        /**
        * Handle install request.
        * @since 3.0
        */
        void InstallL( RFile& aFile );
        
        /**
        * Handle install request.
        * @since 3.0
        */
        void InstallL( RFile& aFile, const TDesC8& aOptions );
        
        /**
        * Registered exit observer will be informed when installer exits
        * @since 3.0
        */
        void SetExitObserver( MAknServerAppExitObserver* aObserver );
        
    public: // Functions from base classes

        /**
        * From CActive, Called by framework when request is finished.
        * @since 3.0
        */
        void RunL();

        /**
        * From CActive, Called by framework when request is cancelled.
        * @since 3.0
        */        
        void DoCancel();  


        /**
        * C++ default constructor.
        */
        CDocAppInstLauncher();

        /**
        * 2nd phase constructor.
        */
        void ConstructL();
                
    private: // Data

        SwiUI::RSWInstLauncher iLauncher;    
        MAknServerAppExitObserver* iExitObserver;    
        TBool iCalledWithParams;        
    };


#endif      
            
// End of File
