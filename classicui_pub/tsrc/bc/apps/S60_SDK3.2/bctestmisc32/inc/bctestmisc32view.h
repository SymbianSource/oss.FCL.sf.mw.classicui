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
* Description:         Test BC for misc control API.
*
*/









#ifndef C_BCTESTMISC32VIEW_H
#define C_BCTESTMISC32VIEW_H

#include <aknview.h>

const TUid KBCTestmisc32ViewId = { 1 };

class CBCTestmisc32Container;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestmisc32View : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestmisc32View* NewL(CBCTestUtil* aUtil);
    
    /**
     * dtor
     */
    virtual ~CBCTestmisc32View();

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
	CBCTestmisc32Container* Container();
    
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
    CBCTestmisc32View();

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
    CBCTestmisc32Container*  iContainer;

    };

#endif // C_BCTESTMISC32VIEW_H

// End of File
