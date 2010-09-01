/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for DRM functionality.
*
*/


#ifndef PSLNDRMIMPLEMENTATION_H
#define PSLNDRMIMPLEMENTATION_H

#include <e32base.h>
#include <MMGFetchVerifier.h>

class CDRMHelper;

/**
* Implementation for DRM functionality.
*
* @since 2.6
*/
class CPslnDRMImplementation : public CBase, public MMGFetchVerifier
    {
    public:
        
        /**
        * Two-phased constructor.
        */
        static CPslnDRMImplementation* NewL();
        
        /**
        * Destructor.
        */
        ~CPslnDRMImplementation();

        /**
        * From MFLDFileObserver.
        */
        TBool VerifySelectionL( const MDesCArray* aSelectedFiles );
        
           /* Shows error note. */
        static void ShowErrorNoteL( TInt  aResourceId  );
     
    private:

        /**
        * C++ default constructor.
        */
        CPslnDRMImplementation();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

     

    private:    // Data
    
        /**
        * DRM helper.
        * Own.
        */
        CDRMHelper* iDRMHelper;
        
    };

#endif // PSLNDRMIMPLEMENTATION_H
            
// End of File
