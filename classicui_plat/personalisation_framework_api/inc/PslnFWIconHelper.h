/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class to get icons to setting lists and 
*                   help with loc strings.
*
*/


#ifndef C_PSLNFWICONHELPER_H
#define C_PSLNFWICONHELPER_H

#include <e32base.h>

class CCoeEnv;
class CEikTextListBox;
class CAknIconArray;
class TAknsItemID;

// Icons in list views.
_LIT( KPslnFWNonActiveListItemFormat, "0\t" );
_LIT( KPslnFWActiveListItemFormat, "1\t" );
_LIT( KPslnFWEmbeddedLinkListItemFormat, "2\t" );
_LIT( KPslnFWListItemFormatMMCSuffix, "\t3" );
_LIT( KPslnFWListItemFormatDRMProtectedSuffix, "\t4" );
_LIT( KPslnFWListItemFormatDRMExpiredSuffix, "\t5" );
_LIT( KPslnFWListItemFormatMassDriveSuffix, "\t6" );

/**
 *  Utility class to get icons to setting lists and help with loc strings.
 *
 *  @lib PslnFramework.lib
 *  @since S60 v3.1
 */
NONSHARABLE_CLASS( CPslnFWIconHelper ) : public CBase
    {

public:

    /**
    * Two-phased constructor.
    */
    IMPORT_C static CPslnFWIconHelper* NewL();
    
    /**
    * Destructor.
    */
    IMPORT_C virtual ~CPslnFWIconHelper();
    
    /**
    * Adds icon array to a given listbox.
    * 
    * @param aAll ETrue if adding all the available icons.
    * @param aMaxIndexToAdd if aAll is EFalse, indicates the max index
    *        of icon to add to the icon array.
    * @param aListBox listbox that the icon array is added.
    */
    IMPORT_C void AddIconsToSettingItemsL( 
        TBool aAll, 
        TInt aMaxIndexToAdd, 
        CEikTextListBox* aListBox );

    /**
    * Gets localized string from given loc-file.
    * 
    * @param aPath path and filename of the loc-file.
    * @param aResourceID resource ID of the string to load.
    * @param aCoeEnv control environment.
    * @return localized version of given resource.
    */
    IMPORT_C HBufC* GetLocalizedStringLC( 
        const TDesC& aPath, 
        TInt aResourceID, 
        CCoeEnv* aCoeEnv );

private:

    /**
    * C++ default constructor.
    */
    CPslnFWIconHelper();

    /**
    * Adds new icon to icon array.
    */
    void AddIconL(
        CAknIconArray* aIcons,
        const TAknsItemID& aSkinId,
        const TDesC& aFileName, 
        TInt aBitmapId,
        TInt aMaskId, 
        TBool aColorIcon = EFalse );

    /**
    * Returns path to file containing icons.
    */
    void GetIconFilePath( TDes& aPath );

    };

#endif // C_PSLNFWICONHELPER_H

// End of File
