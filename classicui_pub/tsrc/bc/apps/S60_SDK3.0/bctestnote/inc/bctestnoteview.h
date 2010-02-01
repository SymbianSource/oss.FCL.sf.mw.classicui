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
* Description:         Declares test bc for note control view.
*
*/









#ifndef C_CBCTESTNOTEVIEW_H
#define C_CBCTESTNOTEVIEW_H

#include <aknview.h>

class CBCTestNoteContainer;
class CBCTestUtil;

const TUid KBCTestNoteViewId = { 1 };

/**
 *  Application View class
 */
class CBCTestNoteView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestNoteView* NewL();

    /**
     * dtor
     */
    virtual ~CBCTestNoteView();

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

protected: 

// from CAknView

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
    CBCTestNoteView();

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
    CBCTestNoteContainer*  iContainer;

    };

#endif // C_CBCTESTNOTEVIEW_H

