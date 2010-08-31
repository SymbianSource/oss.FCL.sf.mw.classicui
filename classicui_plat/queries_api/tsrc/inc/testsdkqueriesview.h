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


#ifndef TESTSDKQUERIESVIEW_H
#define TESTSDKQUERIESVIEW_H

// INCLUDES
#include <aknview.h>

// CLASS DECLARATION
class CTestSDKQueriesContainer;
/**
 *  Ctestsdkqueriesview
 * 
 */
class CTestSDKQueriesView : public CAknView
    {
public:// Constructors and destructor

    /**
     * Destructor.
     */
    ~CTestSDKQueriesView( );

    /**
     * Two-phased constructor.
     */
    static CTestSDKQueriesView* NewL( );

    /**
     * Two-phased constructor.
     */
    static CTestSDKQueriesView* NewLC( );
    
    CTestSDKQueriesContainer* Container();

private://from CAknView
    
    /*
     * Id
     */
    TUid Id() const;
    
    /*
     * HandleCommandL
     */
    void HandldCommandL(TInt aCommand);
    
    /*
     * DoActivateL
     */
    void DoActivateL(
        const TVwsViewId& aPrevViewId,
        TUid aCustomMessageId,
        const TDesC8& aCustomMessage );
    
    /*
     * DoDeactivate
     */
    void DoDeactivate();
    
    /**
     * Constructor for performing 1st stage construction
     */
    CTestSDKQueriesView( );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL( );

private: // data
    /*
     * iContainer
     */
    CTestSDKQueriesContainer* iContainer;
    
    /*
     * The id of view
     */
    TUid iId;
    };

#endif // TESTSDKQUERIESVIEW_H

//End file



