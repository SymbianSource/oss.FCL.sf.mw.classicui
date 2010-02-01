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


#ifndef __EIKSLBPROT_H__
#define __EIKSLBPROT_H__

// INCLUDES

#include <eikslb.h>

// FORWARD DECLARATIONS

class MTextListBoxModel;
class CFont;
class CSettingsListBoxData;
class CEikListBox;
class TRect;

/**
* Setting listbox item drawer that is used when 'settings protection'
* feature is enabled.
*/
NONSHARABLE_CLASS(CSettingsProtListBoxItemDrawer) : public CSettingsListBoxItemDrawer
    {
    public:
	    CSettingsProtListBoxItemDrawer(
            MTextListBoxModel* aTextListBoxModel,
		    const CFont* aFont,
			CSettingsListBoxData* aSettingsData,
			CEikListBox* aListBox );    

    public: // from CTextListItemDrawer
	    void DrawItemText(
            TInt aItemIndex,
		    const TRect& aItemTextRect,
			TBool aItemIsCurrent,
			TBool aViewIsEmphasized,
			TBool aItemIsSelected) const;

    private:
	    CEikListBox* iListBox;
        TInt iSpare;
    };

#endif // __EIKSLBPROT_H__

// End of File
