/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AknConf view
*
*/

#ifndef C_AKNCONFVIEW_H
#define C_AKNCONFVIEW_H


#include <aknview.h>
#include "aknconf.hrh"

class CAknConfSettingList;

const TInt KPhysicsViewUid( EAknConfView );
const TInt KGestureViewUid( EGestureConfView );

/**
 *  AknConf view
 */
class CAknConfView : public CAknView
    {

public:

    /**
     * C++ constructor.
     */
    CAknConfView( const TInt aViewId );

    /**
     * Destructor.
     */
    ~CAknConfView();

    /**
     * Symbian 2nd phase constructor.
     * 
     * @param aResId Resource ID used to create the view
     */
    void ConstructL( TInt aResId );

// From base class CAknView.
    
    /**
     * From CAknView.
     * Return Uid.
     * 
     * @return Uid Uid value
     */
    TUid Id() const;

private:

// From base class CAknView.

    /**
     * From CAknView.
     * Takes care of command handling.
     * 
     * @param aCommand Command
     */
    void HandleCommandL( TInt aCommand );

    /**
     * From CAknView.
     * Handles the view activation.
     * 
     * @param aPrevViewId Specifies the view previously active.
     * @param aCustomMessageId Specifies the message type.
     * @param aCustomMessage The activation message.
     */
    void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

    /**
     * From CAknView.
     * Handles the view deactivation.
     */
    void DoDeactivate();

    /** 
     * From CAknView.
     * 
     * @param aResourceId menu pane resource ID
     * @param aMenuPane menu pane pointer
     */
    void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

private:

    /**
     * The view container.
     * Own.
     */
    CAknConfSettingList* iSettingList;

    /**
     * The view id.
     */
    TInt iId;

    };

#endif // C_AKNCONFVIEW_H
