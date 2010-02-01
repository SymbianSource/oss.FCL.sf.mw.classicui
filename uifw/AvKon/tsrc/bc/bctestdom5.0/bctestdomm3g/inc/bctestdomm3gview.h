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
* Description:  Define view class
*
*/


#ifndef C_CBCTESTDOMM3GVIEW_H
#define C_CBCTESTDOMM3GVIEW_H

#include <aknview.h>

const TUid KBCTestM3gViewId = { 1 };

class CBCTestDomM3gContainer;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestDomM3gView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomM3gView* NewL( CBCTestUtil* aUtil );
    
    /**
     * dtor
     */
    virtual ~CBCTestDomM3gView();
 
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
    CBCTestDomM3gView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL(CBCTestUtil* aUtil);

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
    CBCTestDomM3gContainer*  iContainer;

    };

#endif //C_CBCTESTDOMM3GVIEW_H
