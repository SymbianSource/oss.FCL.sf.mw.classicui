/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Records AknLayoutFont registrations. List of pointers to CAknLayoutFont is
*  maintained by AknEnv.
*
*
*/


#ifndef AKNFONTREGISTRY_H
#define AKNFONTREGISTRY_H

#include <e32base.h>

// FORWARD DECLARATIONS
class CFont;
class CAknLayoutFont;

/**
* CAknLayoutFont registration.  This is implemented with an RArray of pointers.  They can be searched
* to give a type check for the client to see if their CFont pointers are actually CAknLayoutFont pointers.
*
*/
NONSHARABLE_CLASS(CAknFontRegistry) : public CBase
    {
public:
	
    /**
    * Two-phased constructor.
    *
    * @return Fully constructed object if there was no Leave
    */
    static CAknFontRegistry* NewL();
   
    /** 
    * Called to put the CAknLayoutFont object's pointer in the list
    * @param    aFont   Pointer to a valid CAknLayoutFont-conformant object
    */
    void RegisterFont( const CAknLayoutFont* aFont );

    /** 
    * Called to remove the CAknLayoutFont object's pointer from the list. This will not
    * panic under OOM or if the pointer is not registered.
    * 
    * @param    aFont   Pointer to a valid CAknLayoutFont-conformant object
    */
    void DeRegisterFont( const CAknLayoutFont* aFont );

    /** 
    * Used to find out if a CFont is amoung the registered CAknLayoutFonts
    * @param    aFont   Pointer to a valid CFont-conformant object
    * @return   EFalse  iff the pointer is not in the registed CAknLayoutFont pointers
    */
    TBool IsRegistered( const CFont* aFont ) const;

    /** 
    * Destructor
    *
    */
    virtual ~CAknFontRegistry();

private: 
    /** 
    * Default constructor
    */
    CAknFontRegistry();

    /**
    * @return index of the found font, or KErrNotFound
    */
    TInt FindFont( const CFont* aFont ) const;

private:    // Data
    RPointerArray<CFont> iArray;
    };

#endif // AKNFONTREGISTRY_H
