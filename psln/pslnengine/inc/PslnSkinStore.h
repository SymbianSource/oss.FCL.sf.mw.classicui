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
* Description:  Store for all found skins.
*
*/


#ifndef C_PSLNSKINSTORE_H
#define C_PSLNSKINSTORE_H

#include <e32base.h>
#include <AknsSrvSkinInformationPkg.h>

class CPslnModel;
class CPslnSkinEntry;
class CPslnSkinNameEntry;
class TAknsPkgID;
class RFs;

/**
* Store for all found skins.
*/
NONSHARABLE_CLASS( CPslnSkinStore ) : public CBase
    {
    public:

        /**
        * Two-phased constructor.
        * @param aModel pointer to model.        
        * @return new instance of CPslnSkinStore.
        */
        static CPslnSkinStore* NewL( CPslnModel* aModel );

        /**
        * Destructor.
        */
        virtual ~CPslnSkinStore();

        /**
        * Tries to retrieve all skins. 
        * @param aFsSession File server session.
        */
        void UpdateAllSkinsL( RFs& aFsSession );

        /**
        * Tries to find a specific skin from specified location.
        * @param aPID skin instance ID.
        * @param aLocation location from where to search (memory card, or flash)
        * @return pointer to retrieved skin instance.
        */
        CPslnSkinEntry* Find(
            const TAknsPkgID& aPID,
            TAknSkinSrvSkinPackageLocation aLocation );

        /**
        * Creates an array of skin names.
        *
        * @return Newly created array. Ownership is transferred.
        */
        RPointerArray<CPslnSkinNameEntry>* CreateNameArrayL();

    private:

        /**
        * Updates or adds the skin into array.
        *
        * @param aInfo Information structure. Ownership is transferred.
        */
        CPslnSkinEntry* UpdateOrAddL( 
            CAknsSrvSkinInformationPkg* aInfo,
            RFs& aFsSession );

        /* Updates all skins from given location. */
        void UpdateAllSkinsL( 
            TAknSkinSrvSkinPackageLocation aLocation, RFs& aFsSession );

        /* Appends one entry to array. */
        void AppendEntryL( 
            RPointerArray<CPslnSkinNameEntry>& aArray, const TInt aIndex );

        /**
        * C++ default constructor.
        */
        CPslnSkinStore();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL( CPslnModel* aModel );

    private:    // Data

        /**
        * Pointer to model.
        * Not own.
        */
        CPslnModel* iModel;

        /**
        * Skin array.
        */
        RPointerArray<CPslnSkinEntry> iSkinArray;

        /**
        * Default skin PID.
        */        
        TAknsPkgID iDefaultSkinPID;
    };

#endif // C_PSLNSKINSTORE_H

// End of File
