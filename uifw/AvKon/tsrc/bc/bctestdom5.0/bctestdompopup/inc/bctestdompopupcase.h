/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of test case
*
*/


#ifndef C_BTESTDOMAPOPUPCASE_H
#define C_BTESTDOMAPOPUPCASE_H

#include <aknpopupform.h>
#include <aknshortcuts.h>
#include <AknSctDialog.h>

#include "bctestcase.h"


class CBCDomainTestPopupContainer;
class CCoeControl;
class CAknCharMapDialog;

//class CAknCharMapDialogExtension;
#include <e32property.h>

/**
* AknListBoxShortCutsImplementation class.
*/

class CBCShortCutsImp: public AknListBoxShortCutsImplementation
{
    friend class CBCDomainTestPopupCase;
public:
    CBCShortCutsImp( CEikListBox* aListBox ):
        AknListBoxShortCutsImplementation( aListBox )
    {
        	
    }
    
};

/**
* CBCPopupForm class.
*/

class CBCPopupForm: public CAknPopupForm
    {
    friend class CBCDomainTestPopupCase;
public:
    /**
     * Symbian static 2nd constructor
     */
    static CBCPopupForm* NewL()
    {	
    CAknPopupForm* self = CAknPopupForm::NewL();
    CBCPopupForm* rSelf = static_cast<CBCPopupForm*> ( self );
    return rSelf;
    }
    
public:// From CEikondialog   
    void HandleDialogPageEventL(TInt) 
    {    	
    }
    
    CCoeControl * FadedComponent(TInt) 
    {
    return NULL;
    }
    
    TInt  CountFadedComponents()
    {  	
    return 1;
    }
    
    CEikCaptionedControl* GetFirstLineOnFirstPageOrNull() 
    {  
    return NULL;  	
    }
    
    TInt MappedCommandId( TInt )
    {
    return 1;
    }
    
    TInt BorderStyle()
    {
    return 1;
    }
    
    void HandleInteractionRefused(TInt)
    {	
    }
    
    void HandleControlStateChangeL(TInt)
    {
    }
    
    void SetInitialCurrentLine()
    {	
    }
    
    void PreLayoutDynInitL()
    {	
    }
    
    void HandleControlEventL(class CCoeControl *, MCoeControlObserver::TCoeEvent)
    {	
    }
    
    void Reserved_2(void)
    {	
    }
    
    void ConstructFromResourceL(class TResourceReader &)
    {	
    }
    
    TSize MinimumSize() 
    {
	return TSize();
    }
    
    void WriteInternalStateL( RWriteStream & ) const
    {	
    }
    
    void PrepareContext( CWindowGc & ) const
    {	
    }
    
    void GetCustomAutoValue(void *, TInt, CCoeControl const *)
    {	
    }
    
    TFormControlTypes ConvertCustomControlTypeToBaseControlType(TInt) const
    {    
    return EUnknownType;
    }

    SEikControlInfo CreateCustomControlL(TInt)
    {
    SEikControlInfo scontrol;
    return scontrol;
    }
    
    void PageChangedL( TInt )
    {
    }
    
    void PrepareForFocusTransitionL( ) 
    {
    }
    
    void MakeVisible(TInt) 
    {
    }
    
    TCoeInputCapabilities InputCapabilities() const 
    {	 
    return NULL;
    }
    
    void GetColorUseListL( CArrayFix<TCoeColorUse> &) const
    {
    }
    
    void LineChangedL( TInt )
    {
    }
    };

class CBCListBoxCuts: public AknListBoxShortCutsImplementation
    {   
    friend class CBCDomainTestPopupCase;
public:

    CBCListBoxCuts(CEikListBox* aListBox):
        AknListBoxShortCutsImplementation( aListBox )
    {     
    }
    
    ~CBCListBoxCuts()
    {
       AknListBoxShortCutsImplementation::~AknListBoxShortCutsImplementation();
    }
    
    };
    

// ----------------------------------------------------------------------------
// CAknCharMapDialog Extension class 
// From Aknsctdialog.cpp
// ----------------------------------------------------------------------------
//
class CAknCharMapDialogExtension: public CBase
    {
    public:
    static CAknCharMapDialogExtension* NewL(CAknCharMapDialog* aCaller);
    ~CAknCharMapDialogExtension();

    private:
    CAknCharMapDialogExtension(CAknCharMapDialog* aCaller);
    void ConstructL();
    static TInt QwertyModeChangeNotification(TAny* aObj);
    void HandleQwertyModeChangeNotification();

    public: // New method
    void SetCharacterCaseIfRequiredL();
    public:
    TInt iFlags;
    TBool iQwertyMode;
    CAknCharMapDialog* iCaller;

    private:
        NONSHARABLE_CLASS(CSubscriber) : public CActive
            {
            public:
                CSubscriber(TCallBack aCallBack, RProperty& aProperty);
                ~CSubscriber();

            public: // New functions
                void SubscribeL();
                void StopSubscribe();

            private: // from CActive
                void RunL();
                void DoCancel();

            private:
                TCallBack   iCallBack;
                RProperty&  iProperty;
            };

    private:
        CSubscriber* iQwertyModeStatusSubscriber;
        RProperty iQwertyModeStatusProperty;
        TInt iOldCharCase;
    };


    
class CBCTestCharMapDlg: public CAknCharMapDialog
    {
    friend class CBCDomainTestPopupCase;      
public:

    CBCTestCharMapDlg(TInt aCharCase, TDes& aSpecialChars):
        CAknCharMapDialog( aCharCase, aSpecialChars )
    {      	
    }
    
    TBool OkToExitL( TInt aCmd )
    {
        return CAknCharMapDialog::OkToExitL( aCmd );
    }
    
    void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
        CAknCharMapDialog::HandleControlEventL( aControl, aEventType);
    }
    
    TKeyResponse OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/, TEventCode)
    {
        HandleControlEventL( this, EEventRequestExit);
        return EKeyWasConsumed;
    }
    
    };
    
/**
* test case for various classes
*/

class CBCDomainTestPopupCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCDomainTestPopupCase* NewL( CBCDomainTestPopupContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCDomainTestPopupCase();
    
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
    void TestOtherL();
    void TestOtherElseL();
    void TestLeftL();
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCDomainTestPopupCase( CBCDomainTestPopupContainer* aContainer );
    
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
    CBCDomainTestPopupContainer* iContainer;
    
    };
    
#endif // C_BTESTDOMAPOPUPCASE_H

