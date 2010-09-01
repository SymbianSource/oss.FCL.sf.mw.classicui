/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  View declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTESTGLOBALLISTMSGQUERYVIEW_H
#define BCTESTGLOBALLISTMSGQUERYVIEW_H

#include <aknview.h>

const TUid KBCTestGlobalListMsgQueryViewId = { 1 };

class CBCTestGlobalListMsgQueryContainer;
class CBCTestUtil;

/**
 *  Application view class.
 */
class CBCTestGlobalListMsgQueryView : public CAknView
    {
public: // Constructors and destructor
    /**
     * Symbian static constructor
     */
    static CBCTestGlobalListMsgQueryView* NewL();

    /**
     * Destructor.
     */
    virtual ~CBCTestGlobalListMsgQueryView();

public: // from CAknView
    /**
     * Return view Id.
     */
    TUid Id() const;

    /**
    * From CAknView.
    *
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
    CBCTestGlobalListMsgQueryView();

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();

private: // data
    /**
     * Pointer to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    /**
     * Pointer to the container.
     * own
     */
    CBCTestGlobalListMsgQueryContainer*  iContainer;
    };

#endif

// End of file
