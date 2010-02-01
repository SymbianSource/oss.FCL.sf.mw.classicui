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
* Description:  container
*
*/

#ifndef C_BCTESTPHYSICSVIEW_H
#define C_BCTESTPHYSICSVIEW_H

#include <aknview.h>

const TUid KBCTestPhysicsViewId = { 1 };

class CBCTestPhysicsContainer;
class CBCTestUtil;

/**
 *  CBCTestPhysicsView class
 *
 *  @lib bctestutil.lib
 */
class CBCTestPhysicsView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestPhysicsView* NewL( CBCTestUtil* aUtil );
    
    /**
     * destructor
     */
    virtual ~CBCTestPhysicsView();

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
	CBCTestPhysicsContainer* Container();
    
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
    CBCTestPhysicsView();

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
    CBCTestPhysicsContainer*  iContainer;

    };

#endif // C_BCTESTPHYSICSVIEW_H

// End of File
