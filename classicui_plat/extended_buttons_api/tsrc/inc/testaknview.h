/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  For testing extended_buttons_api
*
*/



#ifndef C_TESTAKNVIEW_H
#define C_TESTAKNVIEW_H


// INCLUDES
#include <aknview.h>

// CLASS
class CTestAknView : public CAknView
    {
public:
    /**
     * constructor
     */
    CTestAknView();
    
    /**
     * From CAknView
     */
    TUid Id() const;
    
    /**
     * From CAknView
     * @param aPrevViewId is not used.
     * @param aCustomMessageId is not used.
     * @param aCustomMessage is not used.
     */
    void DoActivateL( const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage );
    
    /**
     * From CAknView
     */
    void DoDeactivate();
    
    };

#endif // C_TESTAKNVIEW_H

// End of File
