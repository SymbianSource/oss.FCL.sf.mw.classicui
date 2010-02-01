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
* Description:         Test BC for Utilities control API.
*
*/









#ifndef C_BCTESRUTILITIESVIEW_H
#define C_BCTESRUTILITIESVIEW_H

#include <aknview.h>

const TUid KBCTestUtilitiesViewId = { 1 };

class CBCTestUtilitiesContainer;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestUtilitiesView : public CAknView
    {
public: 

// Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestUtilitiesView* NewL();
    
    /**
     * dtor
     */
    virtual ~CBCTestUtilitiesView();

// from CAknView
    
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
    CBCTestUtilitiesView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL();

private: // data

    /**
     * pointor to the BC Test framework utility.
     * own
     */
    CBCTestUtil*  iTestUtil;

    /**
     * pointor to the container.
     * own
     */
    CBCTestUtilitiesContainer*  iContainer;

    };

#endif // C_BCTESRUTILITIESVIEW_H

