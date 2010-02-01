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
* Description:         test case
*
*/









#ifndef BCTEST_PrivateUIFrmCASE_H
#define BCTEST_PrivateUIFrmCASE_H

#include <eikalert.h>
#include <coecobs.h>
#include <eikbtpan.h>
#include <eiklbbut.h>
#include <eikdpage.h>
#include <eikhfdlg.h>
#include <eikhkeyc.h>
#include <eikhkeyt.h> 

#include "bctestcase.h"

class CBCTestPrivateUIFrmContainer;
class CCoeControl;

class CSonEikHotKeyControl: public CEikHotKeyControl
{
    public:
        
        CSonEikHotKeyControl(CEikHotKeyTable* aTable,MEikCommandObserver* aObserver);
        void TestKC_WriteInternalStateL(RWriteStream& aWriteStream);
};

class CSonEikButtonPanel : public CEikButtonPanel
{
    public:
        void TestBP_WriteInternalStateL(RWriteStream& aWriteStream);
        // from MEikButtonGroup
 	    void SetCommandL(TInt /*aPosition*/,
 	                     TInt /*aCommandId*/,
 	                     const TDesC* /*aText*/,
 	                     const CFbsBitmap* /*aBitmap*/,
 	                     const CFbsBitmap* /*aMask*/){};
	    void SetCommandL(TInt /*aPosition*/,
	                     TInt /*aResourceId*/){};
    	void SetCommandSetL(TInt /*aResourceId*/){};
	    void AddCommandL(TInt /*aPosition*/,
	                     TInt /*aCommandId*/,
	                     const TDesC* /*aText*/,
	                     const CFbsBitmap* /*aBitmap*/,
	                     const CFbsBitmap* /*aMask*/){};
    	void AddCommandToStackL(TInt /*aPosition*/,
    	                        TInt /*aCommandId*/,
    	                        const TDesC* /*aText*/,
    	                        const CFbsBitmap* /*aBitmap*/,
    	                        const CFbsBitmap* /*aMask*/){};
    	void AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/){};
    	void AddCommandSetToStackL(TInt /*aResourceId*/){};
    	void SetDefaultCommand(TInt /*aCommandId*/){};
    	TSize CalcMinimumSizeL(TInt /*aResourceId*/)
    	    { 
    	    return TSize(0,0); 
    	    };
    	void RemoveCommandFromStack(TInt /*aPosition*/,TInt /*aCommandId*/){};
    	TInt CommandPos(TInt /*aCommandId*/) const
    	    { 
    	    return 0; 
    	    };
    	void DimCommand(TInt /*aCommandId*/,TBool /*aDimmed*/){};
    	TBool IsCommandDimmed(TInt /*aCommandId*/) const
    	    { 
    	    return ETrue; 
    	    };
    	void MakeCommandVisible(TInt /*aCommandId*/,TBool /*aVisible*/){};
    	TBool IsCommandVisible(TInt /*aCommandId*/) const
    	    { 
    	    return ETrue; 
    	    };
    	CCoeControl* AsControl()
    	    { 
    	    return NULL; 
    	    };
    	const CCoeControl* AsControl() const
    	    { 
    	    return NULL; 
    	    };
    	void SetBoundingRect(const TRect& /*aBoundingRect*/){};
    	void ReduceRect(TRect& /*aBoundingRect*/) const{};
    	CCoeControl* GroupControlById(TInt /*aCommandId*/) const
    	    { 
            return NULL; 
    	    };
    	CEikCommandButton* GroupControlAsButton(TInt /*aCommandId*/) const
            { 
            return NULL; 
            };
    	TInt CommandId(TInt /*aCommandPos*/) const
    	    { 
    	    return 0; 
    	    };
    	TInt ButtonCount() const
    	    { 
    	    return 0; 
    	    };
    	TUint ButtonGroupFlags() const
    	    { 
    	    return 0; 
    	    };
		void AnimateCommandByPosition( TInt ){};
		TBool IsCommandVisibleByPosition( TInt ) const { return ETrue; };
		void MakeCommandVisibleByPosition( TInt, TBool ){};
		TBool IsCommandDimmedByPosition( TInt ) const { return EFalse; };
		void DimCommandByPosition( TInt, TBool ){};
		void SetMSKCommandObserver( MEikCommandObserver* ){};
};

class CBCTestObserver : public MEikCommandObserver, public CBase
{
    public:
    //from MEikCommandObserver
        void ProcessCommandL(TInt aCommandId);
};
/**
* test case for various list classes
*/
class CBCTestPrivateUIFrmCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPrivateUIFrmCase* NewL( CBCTestPrivateUIFrmContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestPrivateUIFrmCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void TestFunctionL();
    void TestAlertL();
    void TestBtpanL();
    void TestProtectedBtpanL();
    void TestDpageL();
    void TestHfdlgL();
    void TestHkeycL();     
       
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestPrivateUIFrmCase( CBCTestPrivateUIFrmContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPrivateUIFrmContainer* iContainer;
    
    };

#endif // BCTEST_PrivateUIFrmCASE_H