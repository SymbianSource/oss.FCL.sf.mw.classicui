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
* Description:  Test grids_api
*
*/


#ifndef C_TESTSDKGRIDSVIEW_H
#define C_TESTSDKGRIDSVIEW_H

/*
 * Include files
 */
#include <aknview.h>

const TUid KBCTestGridsViewId = { 1 };

class CTestSDKGridsContainer;

/**
 *  Application UI class
 */
class CTestSDKGridsView : public CAknView
    {
public: 

    /**
     * Symbian static 2nd constructor
     */
    static CTestSDKGridsView* NewL();
    
    /**
     * dtor
     */
    virtual ~CTestSDKGridsView();

    /**
     * Return view Id.
     */
    TUid Id() const;
    
    /**
    * From CAknView, HandleCommandL.
    * @param aCommand Command to be handled.
    */
    void HandleCommandL( TInt aCommand );
    
protected:
    
    /**
     * When view is activated, do something
     */
    void DoActivateL( const TVwsViewId&, TUid, const TDesC8& );
    
    /**
     * When view is deactivated, do something
     */
    void DoDeactivate();

private: 

    /**
     * C++ default constructor
     */
    CTestSDKGridsView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: 
    /**
     * pointor to the container.
     * own
     */
    CTestSDKGridsContainer*  iContainer;
    };

#endif /*TESTSDKGRIDSVIEW_H_*/

/*
 * End file
 */
