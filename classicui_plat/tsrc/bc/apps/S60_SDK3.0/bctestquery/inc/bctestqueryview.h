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
* Description:         view
*
*/








#ifndef C_CBCTESTLISTVIEW_H
#define C_CBCTESTLISTVIEW_H

#include <aknview.h>

const TUid KBCTestListViewId = { 1 };

class CBCTestQueryContainer;
class CBCTestUtil;

/**
* view class
*/
class CBCTestQueryView: public CAknView
    {
public: 
    
// constructor and destructor
    
    static CBCTestQueryView* NewL( CBCTestUtil* aUtil );
    
    ~CBCTestQueryView();
   
// from CAknView
    
    TUid Id() const;
    
    /**
     * From CAknView, HandleCommandL.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL( TInt aCommand );
    
protected: // from CAknView
    
    void DoActivateL( const TVwsViewId&, TUid, const TDesC8& );
    
    void DoDeactivate();
    
private: // constructor

    CBCTestQueryView( CBCTestUtil* aUtil ); 
    
    void ConstructL();
    
private:    // data
    
    /**
     * Own
     */
    CBCTestQueryContainer* iContainer; // own
    
    /**
     * Not Own
     */
    CBCTestUtil* iTestUtil;
        
    };

#endif // C_CBCTESTLISTVIEW_H