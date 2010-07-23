/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Test BC for ServiceHandler control API.
*
*/









#ifndef BCTEST_SERVICEHANDLER_VIEW_H
#define BCTEST_SERVICEHANDLER_VIEW_H

#include <aknview.h>

const TUid KBCTestServiceHandlerViewId = { 1 };

class CBCTestServiceHandlerContainer;
class CBCTestServiceHandlerAppUi;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestServiceHandlerView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestServiceHandlerView* NewL();
    
    /**
     * dtor
     */
    virtual ~CBCTestServiceHandlerView();

public: // from CAknView
    
    /**
     * Return view Id.
     */
    TUid Id() const;
    
    /**
    * From CAknView, HandleCommandL.
    * @param aCommand Command to be handled.
    */
    void HandleCommandL( TInt aCommand );

	/**
	* getter of Container
	*/
	CBCTestServiceHandlerContainer* Container();
    
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
    CBCTestServiceHandlerView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to the BC Test framework utility.
     * Owned
     */
    CBCTestUtil*  iTestUtil;

    /**
     * Pointer to the container.
     * Owned
     */
    CBCTestServiceHandlerContainer*  iContainer;

    };

#endif // BCTEST_SERVICEHANDLER_VIEW_H

// End of File
