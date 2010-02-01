/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares view for application.
*
*/









#ifndef C_CBCTESTLAUNCHERVIEW_H
#define C_CBCTESTLAUNCHERVIEW_H

#include <aknview.h>

// UID of view
const TUid KViewId = { 1 };

class CBCTestLauncherContainer;
class CBCTestApplication;

/**
 *  CBCTestLauncherView view class.
 */
class CBCTestLauncherView : public CAknView
    {
public : 
// Constructors and destructor

    /**
    * C++ default constructor
    */
    CBCTestLauncherView(RArray<CBCTestApplication*>* aList);

    /**
    * Symbian 2nd phase constructor
    */
    void ConstructL();

    /**
    * Destructor
    */
    virtual ~CBCTestLauncherView();

// From CAknView

    /**
    * From CAknView, Id.
    * Returns the ID of view.
    * @return The ID of view.
    */        
    TUid Id() const;

    /**
    * From CAknView, Handles the commands.
    * @param aCommand Command to be handled.
    */
    void HandleCommandL( TInt aCommand );

    /**
    * From CAknView, Handles the clientrect.
    */
    void HandleClientRectChange();

// New Functions
    TBool SelectL();
	void  Reset();

private: 
// From CAknView

    /**
    * From CAknView, Creates the Container class object.
    * @param aPrevViewId ID of previous view.
    * @param aCustomMessageId ID of the custom message.
    * @param aCustomMessage Custom message.
    */
    void DoActivateL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
        const TDesC8& aCustomMessage );

    /**
    * From CAknView, Deletes the Container class object.
    */
    void DoDeactivate();

//From MEikMenuObsever

	/**
	 * init menu according to the bc test applications loaded.
	 */
	void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

private: // Data

    CBCTestLauncherContainer*	 iContainer;	// own
	RArray<CBCTestApplication*>* iSelectApps;	// not own, only refer to
    };

#endif // C_CBCTESTLAUNCHERVIEW_H

