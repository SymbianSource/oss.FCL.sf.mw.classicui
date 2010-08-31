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









#ifndef C_CBCTESTAPPFRMVIEW_H
#define C_CBCTESTAPPFRMVIEW_H

#include <aknview.h>

const TUid KBCTestAppFrmViewId = { 1 };

class CBCTestAppFrmContainer;
class CBCTestUtil;
class CAknViewAppUi;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestAppFrmView : public CAknView
    {
public: // Constructors and destructor

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestAppFrmView* NewL(CAknViewAppUi* aUI);
    
    /**
     * dtor
     */
    virtual ~CBCTestAppFrmView();

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
 
    void AppFrmView_HandleCommandL( TInt aCommand );
    
    void AppFrmView_cba();
     
    void AppFrmView_StatusPane();
     
    void AppFrmView_ViewScreenDeviceChangedL();    
     
    void AppFrmView_DoActivateL(const TVwsViewId& aViewId, TUid aId , const TDesC8& aDes);  
      
    void AppFrmView_MopNext();     
     
    void AppFrmView_MopSupplyObject( TTypeUid aId );    
          
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
    CBCTestAppFrmView();

    /**
     * symbian 2nd ctor
     */
    void ConstructL(CAknViewAppUi* aUI);

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
    CBCTestAppFrmContainer*  iContainer;

    };

#endif // C_CBCTESTAPPFRMVIEW_H

