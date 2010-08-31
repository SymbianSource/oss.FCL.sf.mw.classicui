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
* Description:  test private_ui_framework_api
*
*/


#ifndef C_TESTSDKPRIVATEUIFRAMOBSERVER_H
#define C_TESTSDKPRIVATEUIFRAMOBSERVER_H

//INCLUDE
#include "testsdkprivateuiframework.h"

/**
 *  CTestSdkPrivateUiFramObserver test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class CTestSdkPrivateUiFramObserver: public CBase, public MEikMenuObserver
{
public:
    /**
     * Two-phased constructor.
     */
    CTestSdkPrivateUiFramObserver();
    /**
     * Destructor.
     */
    virtual ~CTestSdkPrivateUiFramObserver();
    /**
     * From SetEmphasis Runs a script line.
     * @since S60 5.0
     * @all parameters are not used
     * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise. 
     */
    
    void SetEmphasis(CCoeControl* /*aMenuControl*/, TBool /*aEmphasis*/)
        {
        }
    /**
     * From ProcessCommandL Runs a script line.
     * @since S60 5.0
     * @param never used
     * @return Symbian OS error code
     */
    void ProcessCommandL(TInt /*aCommandId*/)
        {
        }
};

class CTestSdkPrivateUiFramButtonPanel :public CEikButtonPanel
    {
public:
    /**
     * Two-phased constructor.
     */
    CTestSdkPrivateUiFramButtonPanel();
    /**
     * Destructor.
     */
    virtual ~CTestSdkPrivateUiFramButtonPanel();
    
public://functions
    /**
     * inherit from CEikButtonPanel
     * @since S60 5.0
     * @param aWriteStream Script line containing parameters
     * @return Symbian OS error code
     */

    void DoWriteInternalStateL( RWriteStream& aWriteStream ) const;
    /**
     * SetCommandL function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */

    void SetCommandL(TInt /*aPosition*/,
                     TInt /*aCommandId*/,
                     const TDesC* /*aText*/,
                     const CFbsBitmap* /*aBitmap*/,
                     const CFbsBitmap* /*aMask*/){};
    /**
     * SetCommandL function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    
    void SetCommandL(TInt /*aPosition*/,
                     TInt /*aResourceId*/){};
    /**
     * SetCommandSetL function of CEikButtonPanel
     * @since S60 5.0
     * @parameter aItem is never used
     * @return Symbian OS error code
     */
    
    void SetCommandSetL(TInt /*aResourceId*/){};
    /**
     * AddCommandL function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void AddCommandL(TInt /*aPosition*/,
                     TInt /*aCommandId*/,
                     const TDesC* /*aText*/,
                     const CFbsBitmap* /*aBitmap*/,
                     const CFbsBitmap* /*aMask*/){};
    /**
     * AddCommandToStackL function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void AddCommandToStackL(TInt /*aPosition*/,
                            TInt /*aCommandId*/,
                            const TDesC* /*aText*/,
                            const CFbsBitmap* /*aBitmap*/,
                            const CFbsBitmap* /*aMask*/){};
    /**
     * AddCommandToStackL function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/){};
    /**
     * AddCommandSetToStackL function of CEikButtonPanel
     * @since S60 5.0
     * @parameter is never used
     * @return Symbian OS error code
     */
    void AddCommandSetToStackL(TInt /*aResourceId*/){};
    /**
     * SetDefaultCommand function of CEikButtonPanel
     * @since S60 5.0
     * @parameter is never used
     * @return Symbian OS error code
     */
    void SetDefaultCommand(TInt /*aCommandId*/){};
    /**
     * CalcMinimumSizeL function of CEikButtonPanel
     * @since S60 5.0
     * @parameter is never used
     * @return Symbian OS error code
     */
    TSize CalcMinimumSizeL(TInt /*aResourceId*/)
        { 
        return TSize(0,0); 
        };
    /**
     * RemoveCommandFromStack function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void RemoveCommandFromStack(TInt /*aPosition*/,TInt /*aCommandId*/){};
    /**
     * CommandPos function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    TInt CommandPos(TInt /*aCommandId*/) const
        { 
        return 0; 
        };
    /**
     * DimCommand function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void DimCommand(TInt /*aCommandId*/,TBool /*aDimmed*/){};
    /**
     * IsCommandDimmed function of CEikButtonPanel
     * @since S60 5.0
     * @parameter is never used
     * @return Symbian OS error code
     */
    TBool IsCommandDimmed(TInt /*aCommandId*/) const
        { 
        return ETrue; 
        };
    /**
     * MakeCommandVisible function of CEikButtonPanel
     * @since S60 5.0
     * @all parameters are not used
     * @return Symbian OS error code
     */
    void MakeCommandVisible(TInt /*aCommandId*/,TBool /*aVisible*/){};
    /**
     * IsCommandVisible function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    TBool IsCommandVisible(TInt /*aCommandId*/) const
        { 
        return ETrue; 
        };
    /**
     * AsControl function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    CCoeControl* AsControl()
        { 
        return NULL; 
        };
    /**
     * AsControl function of CEikButtonPanel
     * @since S60 5.0
     * no parameters
     * @return Symbian OS error code
     */
    const CCoeControl* AsControl() const
        { 
        return NULL; 
        };
    /**
     * SetBoundingRect function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void SetBoundingRect(const TRect& /*aBoundingRect*/){};
    /**
     * ReduceRect function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void ReduceRect(TRect& /*aBoundingRect*/) const{};
    /**
     * GroupControlById function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    CCoeControl* GroupControlById(TInt /*aCommandId*/) const
        { 
        return NULL; 
        };
    /**
     * GroupControlAsButton function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    CEikCommandButton* GroupControlAsButton(TInt /*aCommandId*/) const
        { 
        return NULL; 
        };
    /**
     * CommandId function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    TInt CommandId(TInt /*aCommandPos*/) const
        { 
        return 0; 
        };
    /**
     * ButtonCount function of CEikButtonPanel
     * @since S60 5.0
     * @no parameters
     * @return Symbian OS error code
     */
    TInt ButtonCount() const
        { 
        return 0; 
        };
    /**
     * ButtonGroupFlags function of CEikButtonPanel
     * @since S60 5.0
     * @no parameters
     * @return Symbian OS error code
     */
    TUint ButtonGroupFlags() const
        { 
        return 0; 
        };
    /**
     * AnimateCommandByPosition function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void AnimateCommandByPosition( TInt ){};
    /**
     * IsCommandVisibleByPosition function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    TBool IsCommandVisibleByPosition( TInt ) const { return ETrue; };
    /**
     * MakeCommandVisibleByPosition function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void MakeCommandVisibleByPosition( TInt, TBool ){};
    /**
     * IsCommandDimmedByPosition function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    TBool IsCommandDimmedByPosition( TInt ) const { return EFalse; };
    /**
     * DimCommandByPosition function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void DimCommandByPosition( TInt, TBool ){};
    /**
     * SetMSKCommandObserver function of CEikButtonPanel
     * @since S60 5.0
     * @param is never used
     * @return Symbian OS error code
     */
    void SetMSKCommandObserver( MEikCommandObserver* ){};

    };


#endif /*C_TESTSDKPRIVATEUIFRAMOBSERVER_H*/

// End of File


