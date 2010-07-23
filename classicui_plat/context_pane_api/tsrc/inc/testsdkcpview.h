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
* Description:  
*
*/


#ifndef c_TESTSDKCPVIEW_H
#define c_TESTSDKCPVIEW_H

#include <aknview.h>

const TUid KBCTestGridsViewId = { 1 };

class CTestSDKCPContainer;

/**
 *  Application UI class
 */
class CTestSDKCPView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CTestSDKCPView* NewL();
    
    /**
     * dtor
     */
    virtual ~CTestSDKCPView();

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
    CTestSDKCPView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: // data
    /**
     * pointor to the container.
     * own
     */
    CTestSDKCPContainer*  iContainer;
    };

#endif /*c_TESTSDKCPVIEW_H*/

