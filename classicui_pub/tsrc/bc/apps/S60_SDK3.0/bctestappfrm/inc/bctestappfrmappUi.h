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









#ifndef C_CBCTESTAPPFRMAPPUI_H
#define C_CBCTESTAPPFRMAPPUI_H

#include <aknviewappui.h>
#include <aknappui.h>
class CBCTestAppFrmView;

/**
 *  Application UI class
 *
 *  @lib bctestutil.lib
 */
class CBCTestAppFrmAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
         * ctor
         */
        CBCTestAppFrmAppUi();

        /**
         * symbian 2nd ctor
         */
        void ConstructL();

        /**
         * dtor
         */
        virtual ~CBCTestAppFrmAppUi();

// from CAknViewAppUi

        void HandleStatusPaneSizeChange();
//from CAknAppUi
        void AppFrm_SetKeyBlockMode();

//from CAknAppUiBase        
        void AppFrm_HandleStatusPaneSizeChange();
        
        void AppFrm_HandleApplicationSpecificEventL(TInt aType,
                                            const TWsEvent& aEvent);
        void AppFrm_HandleScreenDeviceChangedL();
        
        void AppFrm_ReplaceKeySoundsL(TInt aUid);
    private:

        /**
         * From CEikAppUi
         */
        void HandleCommandL( TInt aCommand );
        
    private: // data
        
        /**
         * pointor to the view.
         * own
         */
        CBCTestAppFrmView*  iView;
    };

#endif // C_CBCTESTAPPFRMAPPUI_H
