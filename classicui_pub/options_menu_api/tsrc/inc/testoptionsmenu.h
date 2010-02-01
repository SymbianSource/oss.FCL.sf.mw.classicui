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
* Description:  test options_menu_api
 *
*/

#ifndef C_TESTOPTIONSMENU_H
#define C_TESTOPTIONSMENU_H

//  INCLUDES
#include <aiwserviceifmenu.h>
#include <eikmenup.h>
#include <e32base.h>
#include <eikmenub.h>
#include <eikmobs.h>
#include <coecntrl.h>
#include <coemop.h>

#include "testoptionsmenu.h"

/**
 *  CTestOptionsMenu test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class CTestOptionsMenu : public CEikMenuPane
{
// Constructors and destructor
public:
    /**
    * C++ default constructor.
    */
    CTestOptionsMenu( MEikMenuObserver* aObserver );
    /**
     * Destructor.
    */
    virtual ~CTestOptionsMenu();
    
public:// Functions inherit from CEikMenuPane classes
    /**
    * From Draw Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
    */
    void DoDraw( const TRect& aRect );
    /**
    * From FocusChanged Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
    */
    void DoFocusChanged( TDrawNow aDrawNow );
    /**
    * From ConstructFromResourceL Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
    */
    void DoConstructFromResourceL( TResourceReader& aReader );
    /**
    * From ActivateGc Runs a script line.
    * @since S60 5.0
    * @return Symbian OS error code
    */
    void DoActivateGc();
    /**
    * From DeactivateGc Runs a script line.
    * @since S60 5.0
    * @return Symbian OS error code
    */
    void DoDeactivateGc();
};


/**
 *  CMenuObserver test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class CMenuObserver : public CBase, public MEikMenuObserver
    {
public:
    /**
    * C++ default constructor.
    */
    CMenuObserver(){}
    /**
     * Destructor.
    */
    ~CMenuObserver(){}
    
    /**
    * From SetEmphasis Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
    */
    void SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/){}
    /**
    * From ProcessCommandL Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
    */
    void ProcessCommandL(TInt /*aCommandId*/){}
    };


/**
 *  CTestOptionsMenuMop test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class CTestOptionsMenuMop : public CEikMenuPane

{
public:
    /**
    * C++ default constructor.
    */
    CTestOptionsMenuMop( MEikMenuObserver* aMenuObserver );
    /**
     * Destructor.
    */
    virtual ~CTestOptionsMenuMop();
    
public:// Functions inherit from CEikMenuPane classes
    /**
    * From MopSupplyObject Runs a script line.
    * @since S60 5.0
    * @return Symbian type TTypeUid
    */
    TTypeUid::Ptr DoMopSupplyObject( TTypeUid aId );

};

#endif /*C_TESTOPTIONSMENU_H*/
// End of File
