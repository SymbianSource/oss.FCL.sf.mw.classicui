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
* Description:  Test AknButton.h
*
*/


#ifndef C_TESTBUTTONSTATE_H
#define C_TESTBUTTONSTATE_H

/*
 * Include files
 */
#include <aknbutton.h>
#include <aknpictographdrawerinterface.h>
#include "testsdkgenericbutton.h"

/*
 * Class declare
 */
class CAknButtonStateExtension;

/*
 * This class inherit from CAknButtonState class, it use to construction 
 * CAknButtonState object,and test the protected function which come from 
 * CAknButtonState class
 */
class CTestButtonState : public CAknButtonState
{
public:
    /*
     * Constructor
     */
    CTestButtonState( const TInt aFlags );
    /*
     * Destructor
     */
    virtual ~CTestButtonState();
    /*
     * This function is wrote for test constructor function in 
     * CAknButtonState class
     */
    void DoConstructL( CGulIcon* aIcon,
        CGulIcon* aDimmedIcon, 
        CGulIcon* aPressedIcon,
        CGulIcon* aHoverIcon,
        const TDesC& aText, 
        const TDesC& aHelpText );
    /*
     * This function is wrote for test constructor function in 
     * CAknButtonState class
     */
    void DoConstructDeepL( const TDesC& aFilePath, 
        const TInt aBmpId, 
        const TInt aMaskId,
        const TInt aDimmedBmpId, 
        const TInt aDimmedMaskId,
        const TInt aPressedBmpId, 
        const TInt aPressedMaskId,
        const TInt aHoverBmpId,
        const TInt aHoverMaskId,
        const TDesC& aText, 
        const TDesC& aHelpText,
        const TAknsItemID& aId = KAknsIIDNone, 
        const TAknsItemID& aDimmedId = KAknsIIDNone, 
        const TAknsItemID& aPressedId = KAknsIIDNone,
        const TAknsItemID& aHoverId = KAknsIIDNone );
    /*
     * This function is wrote for testing the constructfromresourcel function
     * in CAknButtonState class
     */
    void DoConstructFromResourceL( TResourceReader& aReader );
    
    TBool DoHasText();
    TBool DoHasHelp();
    TBool StifHasText() const;
    void DoSizeChanged( const TRect& aRect, TScaleMode aScaleMode );
};

#endif /*CStifButtonState_H_*/

//End file


