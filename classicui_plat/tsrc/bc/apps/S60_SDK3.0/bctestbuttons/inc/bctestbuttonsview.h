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
* Description:         Test BC for Buttons control API.
*
*/









#ifndef C_CBCTESTBUTTONSVIEW_H
#define C_CBCTESTBUTTONSVIEW_H

#include <aknview.h>

const TUid KBCTestButtonsViewId = { 1 };

class CBCTestButtonsContainer;
class CBCTestUtil;

/**
 *  Application UI class
 */
class CBCTestButtonsView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestButtonsView* NewL();
    
    /**
     * dtor
     */
    virtual ~CBCTestButtonsView();
   
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
    CBCTestButtonsView();

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
    CBCTestButtonsContainer*  iContainer;

    };

#endif // BCTESTBUTTONSVIEW_H

