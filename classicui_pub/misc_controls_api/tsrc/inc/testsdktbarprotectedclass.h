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
* Description:  misc_controls_api
*
*/

#ifndef C_TESTSDKTBARPROTECTEDCLASS_H
#define C_TESTSDKTBARPROTECTEDCLASS_H
//  INCLUDES
#include <eiktbar.h>
#include "testsdkmisccontrols.h"
/**
*  CTestSDKMiscControls test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestSDKMiscControls;
class CTestToolBar : public CEikToolBar
    {
    friend class CTestSDKMiscControls;
public:
    /**
     * AsControl const
     */
    const CCoeControl* AsControl() const;
    /**
     * AsControl
     */
    CCoeControl* AsControl();
    /**
     * GroupControlById
     */
    CCoeControl* GroupControlById(TInt /*aCommandId*/) const;
    /**
     * GroupControlAsButton
     */
    CEikCommandButton* GroupControlAsButton(TInt /*aCommandId*/) const;
    /**
     * CalcMinimumSizeL
     */
    TSize CalcMinimumSizeL(TInt /*aResourceId*/);
    /**
     * CommandId
     */
    TInt CommandId(TInt /*aCommandPos*/) const;
    /**
     * ButtonCount
     */
    TInt ButtonCount() const;
    /**
     * CommandPos
     */
    TInt CommandPos(TInt /*aCommandId*/) const;
    /**
     * IsCommandDimmed
     */
    TBool IsCommandDimmed(TInt /*aCommandId*/) const;
    /**
     * IsCommandDimmedByPosition
     */
    TBool IsCommandDimmedByPosition(TInt /*aPosition*/) const;
    /**
     * IsCommandVisible
     */
    TBool IsCommandVisible(TInt /*aCommandId*/) const;
    /**
     * IsCommandVisibleByPosition
     */
    TBool IsCommandVisibleByPosition(TInt /*aPosition*/) const;
    /**
     * ButtonGroupFlags
     */
    TUint ButtonGroupFlags() const;
    /**
     * AddCommandL
     */
    void AddCommandL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                      const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ );
    /**
     * AddCommandSetToStackL
     */
    void AddCommandSetToStackL(TInt /*aResourceId*/);
    /**
     * AddCommandToStackL
     */
    void AddCommandToStackL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                             const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ );
    /**
     * AddCommandToStackL
     */
    void AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/);
    /**
     * AnimateCommandByPosition
     */
    void AnimateCommandByPosition(TInt /*aPosition*/);
    /**
     * DimCommand
     */
    void DimCommand(TInt /*aCommandId*/,TBool /*aDimmed*/);
    /**
     * DimCommandByPosition
     */
    void DimCommandByPosition(TInt /*aPosition*/,TBool /*aDimmed*/);
    /**
     * MakeCommandVisible
     */
    void MakeCommandVisible(TInt /*aCommandId*/,TBool /*aVisible*/);
    /**
     * MakeCommandVisibleByPosition
     */
    void MakeCommandVisibleByPosition(TInt /*aPosition*/,TBool /*aVisible*/);
    /**
     * RemoveCommandFromStack
     */
    void RemoveCommandFromStack(TInt /*aPosition*/,TInt /*aCommandId*/);
    /**
     * SetCommandL
     */
    void SetCommandL(TInt /*aPosition*/,TInt /*aResourceId*/);
    /**
     * SetCommandL
     */
    void SetCommandL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                      const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ );
    /**
     * SetCommandSetL
     */
    void SetCommandSetL(TInt /*aResourceId*/);
    /**
     * SetDefaultCommand
     */
    void SetDefaultCommand(TInt /*aCommandId*/);
    /**
     * SetMSKCommandObserver
     */
    void SetMSKCommandObserver(MEikCommandObserver* /*aCommandObserver*/);
    };
#endif /*C_TESTSDKTBARPROTECTEDCLASS_H*/
