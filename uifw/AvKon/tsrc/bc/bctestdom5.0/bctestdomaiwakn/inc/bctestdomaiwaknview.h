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
* Description: 
*
*/

#ifndef C_CBCTESTDOMAIWAKNVIEW_H
#define C_CBCTESTDOMAIWAKNVIEW_H

#include <aknview.h>

const TUid KBCTestAiwAknViewId = { 1 };

class CBCTestDomAiwAknContainer;
class CBCTestUtil;
class CEikMenuPane;
 
/**
 *  CBCTestDomAiwAknView class.
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib  bctestutil.lib
 *  @since S60 v5.0
 */
class CBCTestDomAiwAknView : public CAknView
    {
    
public:  

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomAiwAknView* NewL( CBCTestUtil* aUtil );
    
    /**
     * destructor
     */
    virtual ~CBCTestDomAiwAknView();
 

// from base class CAknView   

    /**
     * From CAknView.
     * Return view Id.
     *
     * @since S60 v5.0
     * @param view Id.
     */     
    TUid Id() const;
    
    /**
     * From CAknView.
     * HandleCommandL()
     *
     * @since S60 v5.0
     * @param aCommand Command to be handled.
     */     
    void HandleCommandL( TInt aCommand );

    /**
     * From CAknView.
     * getter of Container
     *
     * @since S60 v5.0
     * @return pointer to CBCTestDomAiwAknContainer object.
     */ 	
	CBCTestDomAiwAknContainer* Container();
    
protected:  

// from base class MEikMenuObserver  

    /**
     * From MEikMenuObserver.
     * DynInitMenuPaneL
     *
     * @since S60 v5.0
     * @param aResourceId   Menu pane Id.
     * @param aMenuPane  Pointer to menu pane.
     */  
    void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

// from base class CAknView  
    
    /**
     * From CAknView.
     * When view is activated, do something
     *
     * @since S60 v5.0
     * @param aPrevViewId Specifies the view previously active.
     * @param aCustomMessageId Specifies the message type.
     * @param aCustomMessage The activation message.
     */       
    void DoActivateL( 
                    const TVwsViewId& aPrevViewId, 
                    TUid aCustomMessageId, 
                    const TDesC8& aCustomMessage);
    
    /**
     * From CAknView.
     * When view is deactivated, do something
     *
     * @since S60 v5.0
     */     
    void DoDeactivate();
    

private: 

    /**
     * C++ default constructor
     */
    CBCTestDomAiwAknView();

    /**
     * symbian 2nd constructor
     */
    void ConstructL( CBCTestUtil* aUtil );

private: // data

    /**
     * pointor to the BC Test framework utility.
     * not own just refer to
     */
    CBCTestUtil*  iTestUtil;

    /**
     * pointor to the container.
     * own
     */
    CBCTestDomAiwAknContainer*  iContainer;
    
    /**
     * pointor to the CEikMenuPane object.
     * not own just refer to
     */    
    TBool iHaveActivateAppsMenuPane;

    /**
     * the times that autotest runs.
     * 
     */    
    TInt iAutotestCounter;
    };

#endif // C_CBCTESTDOMAIWAKNVIEW_H

// End of File