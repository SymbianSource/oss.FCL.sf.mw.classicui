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
* Description:  Class defining a specific skin within Psln.
*
*/


#ifndef C_PSLNSKINNAMEENTRY_H
#define C_PSLNSKINNAMEENTRY_H

#include <e32base.h>
#include <AknsSrvSkinInformationPkg.h>

/**
* Class defining a specific skin within Psln.
* Defined attributes are name, ID and location.
* @since S60 v2.5
*/
class CPslnSkinNameEntry : public CBase    
    {
    public:
        
    /**
    * Two-phased constructor.
    * @return new instance of CPslnSkinNameEntry.
    */
    static CPslnSkinNameEntry* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CPslnSkinNameEntry();

    /**
    * Method for getting skin name.
    * @param aDst returns skin name for the entry.
    */
    void GetName( TDes& aDst ) const;
    
    /**
    * Method for setting skin name.
    * @param aName sets skin name for the entry to this descriptor.
    */
    void SetNameL( const TDesC& aName );

    /**
    * Method for fetching the location of skin package.
    * @see details from AknsSrvSkinInformationPkg.h.
    * @return skin package location.
    */
    TAknSkinSrvSkinPackageLocation Location() const;
    
    /**
    * Method for setting skin package location.
    * @see details from AknsSrvSkinInformationPkg.h.
    * @param aLocation skin package location.
    */
    void SetLocation( const TAknSkinSrvSkinPackageLocation aLocation );

    /**
    * Method for getting skin package name.
    * @return skin package ID.
    */
    TAknsPkgID PkgID() const;
    
    /**
    * Method for setting skin package name.
    * @param aPID skin package ID.
    */
    void SetPkgID( const TAknsPkgID& aPID );

    /**
    * Determines the order of two objects.
    * Default system skin is always less than anything else.
    * Otherwise the order is the (folded) order of names.
    *
    * @param aFirst First object to be compared.
    *
    * @param aSecond Second object to be compared.
    *
    * @return 0 if the two objects are equal, negative value if the first 
    *   object is less than the second and positive value if the first 
    *   object is greater than the second.
    */
    static TInt LinearOrder( 
        const CPslnSkinNameEntry& aFirst, 
        const CPslnSkinNameEntry& aSecond );
        
    /**
    * Returns skin package location, based on path parameter.
    * @param aPath path of skin package
    * @return skin package location
    */
    static TAknSkinSrvSkinPackageLocation LocationFromPath( 
        const TDesC& aPath );

protected:

    /* Copies data honoring size. */
    static void CopyHonoringSize( TDes& aDst, const TDesC* aSrc );
    
    /* Copies data honoring size. */
    static void CopyHonoringSize( TDes& aDst, const TDesC& aSrc );        

    /* Base construct.  */
    void BaseConstructL( CAknsSrvSkinInformationPkg* aInfo = NULL );

    /**
    * C++ default constructor.
    */
    CPslnSkinNameEntry();

private: // data

    /**
    * Skin name.
    * Own
    */
    HBufC* iName;

    /** 
    * Skin package location.
    */
    TAknSkinSrvSkinPackageLocation iLocation;

    /**
    * Skin package ID.
    */
    TAknsPkgID iPID;

    };


#endif // C_PSLNSKINNAMEENTRY_H


// End of File