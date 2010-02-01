/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/


#ifndef __EIKSLBPROTFACTORY_H__
#define __EIKSLBPROTFACTORY_H__

// INCLUDES

#include <e32base.h>

// FORWARD DECLARATIONS

class CSettingsProtListBoxItemDrawer;
class MTextListBoxModel;
class CFont;
class CSettingsListBoxData;
class CEikListBox;

/**
* Setting listbox item drawer that is used when 'settings protection'
* feature is enabled.
*/
class SettingsProtListBoxItemDrawerFactory
    {
    public:

        /**
        * Factory function for settings listbox item drawer that is
        * used when 'settings protection' feature is enabled
        *
        * @return If 'settings protection' feature is enabled,
        *         new CSettingsProtListBoxItemDrawer object.
        *
        *         If 'settings protection' feature is disabled, NULL.
        */
        static CSettingsProtListBoxItemDrawer* 
            CreateSettingsProtListBoxItemDrawerL(
                MTextListBoxModel* aTextListBoxModel,
			    const CFont* aFont,
			    CSettingsListBoxData* aSettingsData,
			    CEikListBox* aListBox );    

    private:

        SettingsProtListBoxItemDrawerFactory();
    };

#endif // __EIKSLBPROTFACTORY_H__

// End of File
