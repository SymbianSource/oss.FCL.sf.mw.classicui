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
* Description:  Class defining a specific skin within Psln.
*
*/


#ifndef C_PSLNSKINENTRY_H
#define C_PSLNSKINENTRY_H

#include <e32base.h>
#include <babitflags.h>
#include <AknsSrvSkinInformationPkg.h>

#include "PslnSkinNameEntry.h"

/**
* Class defining a specific skin within Psln.
*/
NONSHARABLE_CLASS( CPslnSkinEntry ) : public CPslnSkinNameEntry
    {
    public:
        
        /**
        * Two-phased constructor.
        * @param aInfo skin information package.
        * @return new instance of CPslnSkinEntry.
        */
        static CPslnSkinEntry* NewL( CAknsSrvSkinInformationPkg* aInfo );
        
        /**
        * Destructor.
        */
        virtual ~CPslnSkinEntry();

        /**
        * Gets skin path.
        * @param aDst copies skin path to this descriptor.
        */
        IMPORT_C void GetSkinPath( TDes& aDst ) const;

        /**
        * Checks if skin entry has corrupted flag set.
        * @return ETrue if corrupted flag is set.
        */
        IMPORT_C TBool IsCorrupted() const;

		/**
        * Checks if skin entry has animation background support.
        * @return ETrue if supprot animation background.
        */
        IMPORT_C TBool IsSupportAnimBg() const;
        /**
        * Returns protection type of skin.
        * @return protection type of the skin (@see AknsSrvSkinInformatioPkg.h)
        */
        IMPORT_C TAknsSkinSrvSkinProtectionType Protection() const;

        /**
        * Returns full name of the skin.
        * @return full name of the skin.
        */
        IMPORT_C TDesC& FullName() const;

        /**
        * Returns ETrue if skin is on mass drive,
        * @return is skin on mass drive.
        *
        * @since 5.0
        */
        IMPORT_C TBool IsOnMassDrive() const;

        /**
        * Returns ETrue if skin is on memory card,
        * @return is skin on memory card.
        *
        * @since 5.0
        */
        IMPORT_C TBool IsOnMemoryCard() const;

        /**
        * Gets ini-file path.
        * @param aDst copies ini-file path to this descriptor.
        */
        void GetIniPath( TDes& aDst ) const;
        
        /**
        * Sets protection type for the skin.
        * @param aProtection protection type for the skin.
        */
        void SetProtection( const TAknsSkinSrvSkinProtectionType aProtection );       

        /**
        * Sets delete flag.
        */
        void SetDeleteFlag( const TBool& aValue );
        
        /**
        * Checks is delete flag has been set.
        * @return ETrue if delete flag has been set.
        */
        TBool IsDeleteFlag() const;

        /**
        * Checks the order of the items. The least of items should
        * be first in the skin list, followed by 'greater' items.
        * @param aFirst first skin entry
        * @param aSecond second skin entry
        * @return zero, if items are equal, 
        *         -1, if first item is 'less' than second item.
        *         1, if first item is 'greater' than second one item
        */
        static TInt LinearOrder( 
            const CPslnSkinEntry& aFirst, 
            const CPslnSkinEntry& aSecond ); 

        /**
        * Sets memory card flag.
        * @param aValue new flag value,
        * @since 5.0
        */
        void SetMemoryCardFlag( const TBool& aValue );

        /**
        * Sets mass drive flag.
        * @param aValue new flag value,
        * @since 5.0
        */
        void SetMassDriveFlag( const TBool& aValue );
        
    private:

        /**
        * C++ default constructor.
        */
        CPslnSkinEntry();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data
        
        /**
        * Protection type of the skin.
        */
        TAknsSkinSrvSkinProtectionType iProtection;
        
        /**
        * Skin information package.
        * Own.
        */
        CAknsSrvSkinInformationPkg* iInfo;

        /*
        * Internal state of the class.
        */
        enum TPslnSkinEntryState
            {
            // initial state
            EPslnSkinEntryStateInitial = 0x00000000,
            // skin has been marked as deleted.
            EPslnSkinEntryStateDeleted = 0x00000001,
            // skin is on memory card
            EPslnSkinEntryStateMemoryCard = 0x00000002,
            // skin is mass drive
            EPslnSkinEntryStateMassDrive = 0x00000004
            };
        TBitFlags iInternalState;

    };

#endif // C_PSLNSKINENTRY_H
            
// End of File
