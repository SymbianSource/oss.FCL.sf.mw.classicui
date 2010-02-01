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


#ifndef C_BCTESTDOMAVKONPSLNVIEW_H
#define C_BCTESTDOMAVKONPSLNVIEW_H

#include <aknview.h>

const TUid KBCTestDomainViewId = { 1 };

class CBCTestDomAvkonPslnContainer;
class CBCTestUtil;

/**
 *  CBCTestDomAvkonPslnView class
 *
 *  @lib bctestutil.lib
 */
class CBCTestDomAvkonPslnView : public CAknView
    {
    
public: 
// Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomAvkonPslnView* NewL( CBCTestUtil* aUtil );
    
    /**
     * destructor
     */
    virtual ~CBCTestDomAvkonPslnView();

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

    /**
    * getter of Container
    */
    CBCTestDomAvkonPslnContainer* Container();
    
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
    CBCTestDomAvkonPslnView();

    /**
     * symbian 2nd constructor
     */
    void ConstructL( CBCTestUtil* aUtil );

private: // data

    /**
     * pointor to the BC Test framework utility.
     * not own just refer to
     */
    CBCTestUtil*  iTestUtil;

    /**
     * pointor to the container.
     * own
     */
    CBCTestDomAvkonPslnContainer*  iContainer;

    };

#endif // C_BCTESTDOMAVKONPSLNVIEW_H

// End of File
