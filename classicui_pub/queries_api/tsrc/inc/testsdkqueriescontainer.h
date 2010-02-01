/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test queries_api
*
*/

#ifndef TESTSDKQUERIESCONTAINER_H
#define TESTSDKQUERIESCONTAINER_H

// INCLUDES
#include <coecntrl.h>
/**
 *  CTestSDKQueriesContainer
 * 
 */
class CTestSDKQueriesContainer : public CCoeControl
    {
public:// Constructors and destructor

    /**
     * Destructor.
     */
    ~CTestSDKQueriesContainer( );

    /**
     * Two-phased constructor.
     */
    static CTestSDKQueriesContainer* NewL( 
        const TRect& aRect, const CCoeControl* aParent );

    /**
     * Two-phased constructor.
     */
    static CTestSDKQueriesContainer* NewLC( 
        const TRect& aRect, const CCoeControl* aParent );

public:
    // from base class CCoeControl
    TInt CountComponentControls( ) const;
    
    /*
     * ComponentControl
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;
    
    /*
     * OfferKeyEventL
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    
    /*
     * HandleResourceChange
     */
    void HandleResourceChange( TInt aType );    
    
    /*
     * ActivateGc
     */
    void ActivateGc() const;
    
    /*
     * DeactivateGc
     */
    void DeactivateGc() const;

protected:
    
    // from base class CCoeControl
    void SizeChanged( );

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CTestSDKQueriesContainer( );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL( const TRect& aRect, const CCoeControl* aParent );

private:
    // from base class CCoeControl
    void Draw( const TRect& aRect ) const;

private://data
    enum TControls
        {        
        ELastControl
        };
    };

#endif // TESTSDKQUERIESCONTAINER_H

//End file


