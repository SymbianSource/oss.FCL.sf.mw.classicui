/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of view
*
*/









#ifndef C_BCTESTMIX50VIEW_H
#define C_BCTESTMIX50VIEW_H

#include <aknview.h>

const TUid KBCTestMix50ViewId = { 1 };

class CBCTestMix50Container;
class CBCTestUtil;

/**
 *  CBCTestMix50View class
 *
 */
class CBCTestMix50View : public CAknView
    {

public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestMix50View* NewL( CBCTestUtil* aUtil );

    /**
     * destructor
     */
    virtual ~CBCTestMix50View();

public:

    /**
     * getter of Container
     */
    CBCTestMix50Container* Container();

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
    CBCTestMix50View();

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
    CBCTestMix50Container*  iContainer;

    };

#endif // C_BCTESTMIX50VIEW_H
