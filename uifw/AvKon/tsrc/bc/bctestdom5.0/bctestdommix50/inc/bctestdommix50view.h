/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of view
*
*/


#ifndef C_BCTESTDOMMIX50VIEW_H
#define C_BCTESTDOMMIX50VIEW_H

#include <aknview.h>

const TUid KBCTestDomMix50ViewId = { 1 };

class CBCTestDomMix50Container;
class CBCTestUtil;

/**
 *  CBCTestDomMix50View class
 *
 */
class CBCTestDomMix50View : public CAknView
    {

public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomMix50View* NewL( CBCTestUtil* aUtil );

    /**
     * destructor
     */
    virtual ~CBCTestDomMix50View();

public:

    /**
     * getter of Container
     */
    CBCTestDomMix50Container* Container();

// from CAknView

    /**
     * from CAknView
     * Return view Id.
     */
    TUid Id() const;

    /**
     * From CAknView, HandleCommandL.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL( TInt aCommand );

protected: 

// from CAknView

    /**
     * from CAknView
     * When view is activated, do something
     */
    void DoActivateL( const TVwsViewId&, TUid, const TDesC8& );
    
    /**
     * from CAknView
     * When view is deactivated, do something
     */
    void DoDeactivate();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestDomMix50View();

    /**
     * symbian 2nd constructor
     */
    void ConstructL( CBCTestUtil* aUtil );

private: // member data

    /**
     * pointor to the BC Test framework utility.
     * not own just refer to
     */
    CBCTestUtil*  iTestUtil;

    /**
     * pointor to the container.
     * own
     */
    CBCTestDomMix50Container*  iContainer;

    };

#endif // C_BCTESTDOMMIX50VIEW_H
