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


#ifndef C_BCTESTMIXMCLVIEW_H
#define C_BCTESTMIXMCLVIEW_H

#include <aknview.h>

const TUid KBCTestMixMCLViewId = { 1 };

class CBCTestMixMCLContainer;
class CBCTestUtil;

/**
 *  CBCTestMixMCLView class
 *
 */
class CBCTestMixMCLView : public CAknView
    {

public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestMixMCLView* NewL( CBCTestUtil* aUtil );

    /**
     * destructor
     */
    virtual ~CBCTestMixMCLView();

public:

    /**
     * getter of Container
     */
    CBCTestMixMCLContainer* Container();

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
    CBCTestMixMCLView();

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
    CBCTestMixMCLContainer*  iContainer;
    };

#endif // C_BCTESTMIX50VIEW_H
