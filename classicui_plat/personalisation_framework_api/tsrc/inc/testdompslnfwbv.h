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
* Description:  extended class for abstruct class declaration
*
*/

#ifndef C_TESTDOMPSLNFWBV_H
#define C_TESTDOMPSLNFWBV_H

#include <pslnfwbaseview.h>
#include <coneresloader.h>

/**
 *  Test Class CTestPslnFWBaseView 
 */   
class CTestPslnFWBaseView : public CPslnFWBaseView
    {
public:

    /**
     * Symbian 2nd static constructor
     */
    void ConstructL();

    /**
     * NewContainerL()
     */
    void NewContainerL();

    /**
     * HandleListBoxSelectionL()
     */
    void HandleListBoxSelectionL();
    
    /**
     * GetCaptionL() from CPslnFWPluginInterface
     */
    void GetCaptionL( TDes& ) const;
    
    /**
     * GetTabTextL() from CPslnFWPluginInterface
     */
    virtual void GetTabTextL( TDes& ) const;
    
    /**
     * CreateIconL() from CPslnFWPluginInterface
     */
    virtual CGulIcon* CreateIconL();

    /*
     * protected function
     */
    virtual void SetNaviPaneL();

    /*
     * protected function
     */
    virtual void CreateNaviPaneContextL( TInt aResourceId );

    /*
     * protected function
     */
    virtual void CreateContainerL();

    /*
     * protected function
     */
    virtual void SetNaviPaneL( const TInt aTabLocation );

    /*
     * protected function
     */
    virtual void SetMiddleSoftKeyLabelL( const TInt aResourceId, const TInt aCommandId );

    /*
     * protected function
     */
    virtual void HandleCommandL( TInt aCommand );

    /*
     * protected function
     */
    virtual void SetTitlePaneL( TInt& aResourceId );

    /**
     * Id()
     */
    TUid Id() const;
    };

#endif /*C_TESTDOMPSLNFWBV_H*/
