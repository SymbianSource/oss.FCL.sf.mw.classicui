/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view class
*
*/

#ifndef C_TESTSDKVIEW_H
#define C_TESTSDKVIEW_H

#include <aknview.h>

const TUid KBCTestGridsViewId = { 1 };

class CTestSDKContainer;

/**
 *  Application UI class
 */
class CTestSDKView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CTestSDKView* NewL();
    
    /**
     * dtor
     */
    virtual ~CTestSDKView();

    /**
     * Return view Id.
     */
    TUid Id() const;
    
    /**
    * From CAknView, HandleCommandL.
    * @param aCommand Command to be handled.
    */
    void HandleCommandL( TInt aCommand );
    
protected: // from CAknView
    
    /**
     * When view is activated, do something
     */
    void DoActivateL( const TVwsViewId&, TUid, const TDesC8& );
    
    /**
     * When view is deactivated, do something
     */
    void DoDeactivate();

private: // constructor

    /**
     * C++ default constructor
     */
    CTestSDKView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: // data
    /**
     * pointor to the container.
     * own
     */
    CTestSDKContainer*  iContainer;
    };

#endif /*C_TESTSDKVIEW_H*/
