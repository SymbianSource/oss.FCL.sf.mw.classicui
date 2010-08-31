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
* Description:  Test aknsettingitemlist.h
*
*/

#ifndef C_TESTAKNSETTINGITEMLISTPROTECTED_H
#define C_TESTAKNSETTINGITEMLISTPROTECTED_H
//INLCUDE
#include <aknsettingitemlist.h>

/*
 * This class inherit from the CAknSettingItem class for 
 * testing the class CAknSettingItem's protected function
 */ 
class CTestSettingItem:public CAknSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestSettingItem( TInt aIdentifier );
    /*
     * Destructor
     */
    ~CTestSettingItem();
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    /*
     * This fuction is wrote for testing CreateBitmapL() function
     */
    CFbsBitmap* DoCreateBitmapL();
    
    void DoSetSettingPage( CAknSettingPage* aSettingPage );
    /*
     * This fuction is wrote for testing SettingPage() function
     */
    CAknSettingPage* DoSettingPage() const;
    /*
     * This fuction is wrote for testing SetUpStandardSettingPageL() function
     */
    void DoSetUpStandardSettingPageL();
    /*
     * This fuction is wrote for testing EmptyItemText() function
     */
    TDesC& DoEmptyItemText() const;
    /*
     * This fuction is wrote for testing SettingPageResourceId()() function
     */
    TInt DoSettingPageResourceId() const;
    /*
     * This fuction is wrote for testing SettingEditorResourceId() function
     */
    TInt DoSettingEditorResourceId() const;
    /*
         * This fuction is wrote for testing AssociatedResourceId() function
         */
    TInt DoAssociatedResourceId() const;
    /*
         * This fuction is wrote for testing SetIconMask() function
         */
    TBool DoSetIconMask( CFbsBitmap* aMask );
    };

/*
 * This class inherit from the CAknTextSettingItem class for 
 * testing the class CAknTextSettingItem's protected function
 */ 
class CTestTextSettingItem:public CAknTextSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestTextSettingItem( TInt aIdentifier, TDes& aText );
    /*
     * Destructor
     */
    ~CTestTextSettingItem();
    /*
     * This fuction is wrote for testing InternalTextPtr() function
     */
    TPtr& DoInternalTextPtr();
    /*
     * This fuction is wrote for testing ExternalText() function
     */
    TPtrC DoExternalText();
    /*
     * This fuction is wrote for testing SetExternalText() function
     */
    void DoSetExternalText( TDesC& aNewExternalText );
    
    };

/*
 * This class inherit from the CAknIntegerSettingItem class for 
 * testing the class CAknIntegerSettingItem's protected function
 */ 
class CTestIntegerSettingItem:public CAknIntegerSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestIntegerSettingItem( TInt aIdentifier, TInt& aValue );
    /*
     * Destructor
     */
    ~CTestIntegerSettingItem();
    /*
     * This fuction is wrote for testing EditItemL() function
     */
    void EditItemL( TBool /*aCalledFromMenu*/ );
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    /*
     * This fuction is wrote for testing InternalValueRef() function
     */
    TInt& DoInternalValueRef();
    /*
     * This fuction is wrote for testing ExternalValueRef() function
     */
    TInt& DoExternalValueRef();
    /*
     * This fuction is wrote for testing SetExternalValue() function
     */
    void DoSetExternalValue( TInt& aValue );
    
    };

/*
 * This class inherit from the CAknPasswordSettingItem class for 
 * testing the class CAknPasswordSettingItem's protected function
 */ 
class CTestPasswordSettingItem:public CAknPasswordSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestPasswordSettingItem( TInt aIdentifier, 
        enum TAknPasswordSettingItemMode aMode, TDes& aPassword );
    /*
     * Destructor
     */
    ~CTestPasswordSettingItem();
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    };

/*
 * This class inherit from the CAknVolumeSettingItem class for 
 * testing the class CAknVolumeSettingItem's protected function
 */ 
class CTestVolumeSettingItem:public CAknVolumeSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestVolumeSettingItem( TInt aIdentifier, TInt& aExternalVolume );
    /*
     * Destructor
     */
    ~CTestVolumeSettingItem();
    /*
     * This fuction is wrote for testing InternalVolumeValue() function
     */
    TInt& DoInternalVolumeValue();
    /*
     * This fuction is wrote for testing CreateBitmapL() function
     */
    CFbsBitmap* DoCreateBitmapL();
    };

/*
 * This class inherit from the CAknSliderSettingItem class for 
 * testing the class CAknSliderSettingItem's protected function
 */ 
class CTestSliderSettingItem:public CAknSliderSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestSliderSettingItem( TInt aIdentifier, TInt& aExternalSliderValue );
    /*
     * Destructor
     */
    ~CTestSliderSettingItem();
    /*
     * This fuction is wrote for testing CreateSettingPageL() function
     */
    CAknSettingPage* DoCreateSettingPageL();
    /*
     * This fuction is wrote for testing CreateAndExecuteSettingPageL() function
     */
    void DoCreateAndExecuteSettingPageL();
    /*
     * This fuction is wrote for testing InternalSliderValue() function
     */
    TInt& DoInternalSliderValue();
    /*
     * This fuction is wrote for testing CreateBitmapL() function
     */
    CFbsBitmap* DoCreateBitmapL();
    
    };

/*
 * This class inherit from the CAknEnumeratedTextSettingItem class for 
 * testing the class CAknEnumeratedTextSettingItem's protected function
 */ 
class CTestEnumeratedTextSettingItem:public CAknEnumeratedTextSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestEnumeratedTextSettingItem( TInt aResourceId );
    /*
     * Destructor
     */
    ~CTestEnumeratedTextSettingItem();
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    /*
     * This fuction is wrote for testing SetSettingPageTextL() function
     */
    void DoSetSettingPageTextL();
    /*
     * This fuction is wrote for testing SettingPageTextArray() function
     */
    CDesCArray* DoSettingPageTextArray() const;
    
    };

/*
 * This class inherit from the CAknEnumeratedTextPopupSettingItem class for 
 * testing the class CAknEnumeratedTextPopupSettingItem's protected function
 */ 
class CTestEnumeratedTextPopupSettingItem:public CAknEnumeratedTextPopupSettingItem
    {
public:
    /*
     *Constructor
     */
    CTestEnumeratedTextPopupSettingItem( TInt aResourceId, TInt& aValue );
    /*
     * Destructor
     */
    ~CTestEnumeratedTextPopupSettingItem();
    /*
     * This fuction is wrote for testing CreateSettingPageL() function
     */
    CAknSettingPage* DoCreateSettingPageL();
    /*
     * This fuction is wrote for testing CreateAndExecuteSettingPageL() function
     */
    void DoCreateAndExecuteSettingPageL();
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    /*
     * This fuction is wrote for testing SetExternalValue() function
     */
    void DoSetExternalValue( TInt aNewValue );
    /*
     * This fuction is wrote for testing SetInternalValue() function
     */
    void DoSetInternalValue( TInt aNewValue );
    /*
     * This fuction is wrote for testing SetSelectedIndex() function
     */
    void DoSetSelectedIndex( TInt aNewIndex );
    /*
     * This fuction is wrote for testing IndexFromValue() function
     */
    TInt DoIndexFromValue( TInt aInputValue ) const ;
    /*
     * This fuction is wrote for testing ExternalValue() function
     */
    TInt DoExternalValue() const;
    /*
     * This fuction is wrote for testing InternalValue() function
     */
    TInt DoInternalValue() const;
    /*
     * This fuction is wrote for testing QueryValue() function
     */
    MAknQueryValue* DoQueryValue() const;
    
    };

/*
 * This class inherit from the CAknBinaryPopupSettingItem class for 
 * testing the class CAknBinaryPopupSettingItem's protected function
 */ 
class CTestBinaryPopupSettingItem:public CAknBinaryPopupSettingItem
    {
public:
    /*
     * Constructor
     */
    CTestBinaryPopupSettingItem( TInt aIdentifier, TBool& aBinaryValue );
    /*
     * Destructor
     */
    ~CTestBinaryPopupSettingItem();
    /*
     * This fuction is wrote for testing CompleteConstructionL() function
     */
    void DoCompleteConstructionL();
    /*
     * This fuction is wrote for testing ExternalValue() function
     */
    TInt DoExternalValue() const;
    /*
     * This fuction is wrote for testing SetInternalValue() function
     */
    void DoSetInternalValue( TInt aNewValue );
    };

/*
 * This class inherit from the CAknBigSettingItemBase class for 
 * testing the class CAknBigSettingItemBase's protected function
 */ 
class CTestBigSettingItemBase:public CAknBigSettingItemBase
    {
public:
    /*
     * Constructor
     */
    CTestBigSettingItemBase( TInt aIdentifier );
    /*
     * Destructor
     */
    ~CTestBigSettingItemBase();
    /*
     * This fuction is wrote for testing SettingTextL() function
     */
    const TDesC& DoSettingTextL();
    };

/*
 * This class inherit from the CAknSettingItemArray class for 
 * testing the class CAknSettingItemArray's protected function
 */ 
class CTestSettingItemArray:public CAknSettingItemArray
    {
public:
    /*
     * Constructor
     */
    CTestSettingItemArray( TInt aGranularity, TBool aIsNumbered,
        TInt aInitialOrdinal );
    /*
     * Destructor
     */
    ~CTestSettingItemArray();
    /*
     * This fuction is wrote for testing SetVisibleCount() function
     */
    void DoSetVisibleCount( TInt aCount );
    /*
     * This fuction is wrote for testing VisibleCount() function
     */
    TInt DoVisibleCount() const;
    
    };

/*
 * This class inherit from the CAknSettingItemList class for 
 * testing the class CAknSettingItemList's protected function
 */ 
class CTestSettingItemList:public CAknSettingItemList
    {
public:
    /*
     * Constructor
     */
    CTestSettingItemList();
    /*
     * Destructor
     */
    ~CTestSettingItemList();
    /*
     * This fuction is wrote for testing CreateSettingItemL() function
     */
    CAknSettingItem* DoCreateSettingItemL( TInt aSettingId );
    };

#endif/*C_TESTAKNSETTINGITEMLISTPROTECTED_H*/

//End file


