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
* Description:    Test aiwserviceifmenu
*
*/




#ifndef C_TESTSERVICEIFMENUPROTECTED_H
#define C_TESTSERVICEIFMENUPROTECTED_H

#include <aiwserviceifmenu.h>

#include "testdomserviceim.h"

 /**
  *     CServiceIfMenu is used to finish the CAiwServiceIfMenu class 
  */
class CTestServiceIfMenu : public CAiwServiceIfMenu
{
public:
    /**
     * Constructor.
     */
	CTestServiceIfMenu();
	/**
     * Destructor.
     */
	virtual ~CTestServiceIfMenu();
	/**
     *  This function inherit from  CAiwServiceIfMenu class 
     */
	void InitializeMenuPaneL(
        CAiwMenuPane& aMenuPane,
        TInt aIndex,
        TInt aCascadeId,
        const CAiwGenericParamList& aInParamList);
	/**
     *  This function inherit from  CAiwServiceIfMenu class 
     */
	void HandleMenuCmdL(
        TInt aMenuCmdId,
        const CAiwGenericParamList& aInParamList,
        CAiwGenericParamList& aOutParamList,
        TUint aCmdOptions = 0,
        const MAiwNotifyCallback* aCallback = NULL);
	/**
     *  This function inherit from  CAiwServiceIfBase class 
     */
	virtual void InitialiseL(
	        MAiwNotifyCallback& aFrameworkCallback,
	        const RCriteriaArray& aInterest);
   /**
     *  This function inherit from  CAiwServiceIfBase class 
     */
    virtual void HandleServiceCmdL(
        const TInt& aCmdId,
        const CAiwGenericParamList& aInParamList,
        CAiwGenericParamList& aOutParamList,
        TUint aCmdOptions = 0,
        const MAiwNotifyCallback* aCallback = NULL);
    /**
     *  This function inherit from  CAiwServiceIfBase class 
     */
    virtual void* ExtensionInterface(TUid aInterface);
};

#endif /*CSERVICEIFMENU_H_*/
