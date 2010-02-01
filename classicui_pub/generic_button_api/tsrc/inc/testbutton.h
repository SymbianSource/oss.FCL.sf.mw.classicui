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


#ifndef C_TESTBUTTON_H
#define C_TESTBUTTON_H
/*
 * Include files
 */
#include <aknbutton.h>
#include <aknpictographdrawerinterface.h>
#include "testsdkgenericbutton.h"

/*
 * This class is wrote for test the protected function which are belong to 
 * the CAknButton class 
 */
class CTestButton:public CAknButton
    {
public:
    /*
     * constructor
     */
    CTestButton( const TInt aFlags );
    /*
     * Destructor
     */
    ~CTestButton();
    /*
     * NewL() function
     */
    static CTestButton* NewL();
    /*
     * NewLC() function
     */
    static CTestButton* NewLC();
    /*
     * Justice if the iStates which is CAknButton class's member data is null
     */
    TBool DetectiStatesIfNull();
    /*
     * Get the iStates's object number
     */
    TInt DetectiStatesCount();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void* DoExtensionInterface( TUid aInterface );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    const TDesC&  DoGetCurrentText() const;
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt DoChangeState( TBool aDrawNow );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoConstructL();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoConstructLComplexL( CGulIcon* aIcon,
                                CGulIcon* aDimmedIcon,
                                CGulIcon* aPressedIcon,
                                CGulIcon* aHoverIcon,
                                const TDesC& aText,
                                const TDesC& aHelpText,
                                const TInt aStateFlags);
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoConstructLMoreComplexL( const TDesC& aFilePath, 
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
                                    const TInt aStateFlags,
                                    const TAknsItemID& aId = KAknsIIDNone, 
                                    const TAknsItemID& aDimmedId = KAknsIIDNone, 
                                    const TAknsItemID& aPressedId = KAknsIIDNone,
                                    const TAknsItemID& aHoverId = KAknsIIDNone  );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    CGraphicsContext::TTextAlign GetiHorizontalAlignment();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoSizeChanged();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TBool DetectIfShowHelp();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TBool DetectIfiDimmedHelpText();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoShowHelpL();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoHideHelp();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    const CFont* GetiFont();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TAknsItemID& GetiTextColorTableId();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt GetiTextColorIndex();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    CAknButton::TAlignment GetiVerticalAlignment();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt GetiHelpNoteWaitInterval();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt GetiHelpNoteInViewInterval();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt GetiKeyRepeatDelay();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TInt GetiKeyRepeatInterval();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TBool GetiButtonPressed();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void SetiButtonPressed( TBool aButtonPressed );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TBool GetiShowHelp();
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void SetiShowHelp( TBool aShowHelp );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void DoFocusChanged( TDrawNow aDrawNow );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    const CGulIcon* DoGetCurrentIcon() const;
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    void SetiKeyDownReported( TBool keydownreported );
    /*
     * This function is wrote for testing CAknButton's protected function
     */
    TBool GetiKeyDownReported();
    };

#endif

//End file


