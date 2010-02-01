/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknjavalists.h, aknshortcuts.h and eikslbd.h
*
*/



#ifndef C_TESTDOMLISTSEXT_H
#define C_TESTDOMLISTSEXT_H


// forward declarations
class AknListBoxShortCuts;
class AknListBoxShortCutsImplementation;

// class declaration
class AknListBoxShortCutsExt : public AknListBoxShortCuts
    {
public:
    /**
     * Concrete actions (these will not change the state machine
     * They should only call methods of external objects to do their job)
     */
    virtual TBool DoTest( TConcreteQuery q );

    /**
     * DoAction
     */
    virtual void DoActionL( TConcreteShortcutActions a );

    /**
     * ShortcutValueForNextList
     */
    virtual TInt ShortcutValueForNextList();

    /**
     * SetShortcutValueFromPrevList
     */
    virtual void SetShortcutValueFromPrevList( TInt aValue );

public:
    /**
     * test ChangeStateL method
     */
    void DoChangeStateL();

    /**
     * test StartTimerL method
     */
    void DoStartTimerL();

    };

class AknListBoxShortCutsImplementationExt : public AknListBoxShortCutsImplementation
    {
public:
    /**
     * default constructor
     */
    AknListBoxShortCutsImplementationExt( CEikListBox* aListBox );

public:
    /**
     * test DoTest method
     */
    TBool TestDoTest();

    /**
     * test DoActionL method
     */
    void TestDoActionL();

    };


#endif // C_TESTDOMLISTSEXT_H
