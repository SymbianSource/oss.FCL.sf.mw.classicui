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
* Description:         Test BC for Template control API.
*
*/









#ifndef BCTEST_TEMPLATE_VIEW_H
#define BCTEST_TEMPLATE_VIEW_H

#include <aknview.h>

const TUid KBCTestTemplateViewId = { 1 };

class CBCTestTemplateContainer;
class CBCTestUtil;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestTemplateView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestTemplateView* NewL(CBCTestUtil* aUtil);
    
    /**
     * dtor
     */
    virtual ~CBCTestTemplateView();

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
	CBCTestTemplateContainer* Container();
    
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
    CBCTestTemplateView();

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
    CBCTestTemplateContainer*  iContainer;

    };

#endif // BCTEST_TEMPLATE_VIEW_H

// End of File
