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

//Include files
#include "testaknsettingitemlistprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSettingItem::CTestSettingItem
// -----------------------------------------------------------------------------
//
CTestSettingItem::CTestSettingItem( TInt aIdentifier ):CAknSettingItem( aIdentifier )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::~CTestSettingItem
// -----------------------------------------------------------------------------
//
CTestSettingItem::~CTestSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoCreateBitmapL
// -----------------------------------------------------------------------------
//
CFbsBitmap* CTestSettingItem::DoCreateBitmapL()
    {
    return CreateBitmapL();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSetSettingPage
// -----------------------------------------------------------------------------
//
void CTestSettingItem::DoSetSettingPage( CAknSettingPage* aSettingPage )
    {
    SetSettingPage( aSettingPage );
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSettingPage
// -----------------------------------------------------------------------------
//
CAknSettingPage* CTestSettingItem::DoSettingPage() const
    {
    return SettingPage();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSetUpStandardSettingPageL
// -----------------------------------------------------------------------------
//
void CTestSettingItem::DoSetUpStandardSettingPageL()
    {
    SetUpStandardSettingPageL();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoEmptyItemText
// -----------------------------------------------------------------------------
//
TDesC& CTestSettingItem::DoEmptyItemText() const
    {
    return EmptyItemText();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSettingPageResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingItem::DoSettingPageResourceId() const
    {
    TInt settingpageId = SettingPageResourceId();
    return settingpageId;
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSettingEditorResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingItem::DoSettingEditorResourceId() const
    {
    return SettingEditorResourceId();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoAssociatedResourceId
// -----------------------------------------------------------------------------
//
TInt CTestSettingItem::DoAssociatedResourceId() const
    {
    return AssociatedResourceId();
    }

// -----------------------------------------------------------------------------
// CTestSettingItem::DoSetIconMask
// -----------------------------------------------------------------------------
//
TBool CTestSettingItem::DoSetIconMask( CFbsBitmap* aMask )
    {
    return SetIconMask( aMask );
    }

// -----------------------------------------------------------------------------
// CTestTextSettingItem::CTestTextSettingItem
// -----------------------------------------------------------------------------
//
CTestTextSettingItem::CTestTextSettingItem( TInt aIdentifier, 
    TDes& aText ):CAknTextSettingItem( aIdentifier, aText )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTextSettingItem::~CTestTextSettingItem
// -----------------------------------------------------------------------------
//
CTestTextSettingItem::~CTestTextSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestTextSettingItem::DoInternalTextPtr
// -----------------------------------------------------------------------------
//
TPtr& CTestTextSettingItem::DoInternalTextPtr()
    {
    return InternalTextPtr();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingItem::DoExternalText
// -----------------------------------------------------------------------------
//
TPtrC CTestTextSettingItem::DoExternalText()
    {
    return ExternalText();
    }

// -----------------------------------------------------------------------------
// CTestTextSettingItem::DoSetExternalText
// -----------------------------------------------------------------------------
//
void CTestTextSettingItem::DoSetExternalText( TDesC& aNewExternalText )
    {
    return SetExternalText( aNewExternalText );
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::CTestIntegerSettingItem
// -----------------------------------------------------------------------------
//
CTestIntegerSettingItem::CTestIntegerSettingItem( TInt aIdentifier, 
    TInt& aValue ):CAknIntegerSettingItem( aIdentifier, aValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::~CTestIntegerSettingItem
// -----------------------------------------------------------------------------
//
CTestIntegerSettingItem::~CTestIntegerSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::EditItemL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingItem::EditItemL( TBool /*aCalledFromMenu*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::DoInternalValueRef
// -----------------------------------------------------------------------------
//
TInt& CTestIntegerSettingItem::DoInternalValueRef()
    {
    return InternalValueRef();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::DoExternalValueRef
// -----------------------------------------------------------------------------
//
TInt& CTestIntegerSettingItem::DoExternalValueRef()
    {
    return ExternalValueRef();
    }

// -----------------------------------------------------------------------------
// CTestIntegerSettingItem::DoSetExternalValue
// -----------------------------------------------------------------------------
//
void CTestIntegerSettingItem::DoSetExternalValue( TInt& aValue )
    {
    SetExternalValue( aValue );
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingItem::CTestPasswordSettingItem
// -----------------------------------------------------------------------------
//
CTestPasswordSettingItem::CTestPasswordSettingItem( TInt aIdentifier, 
    TAknPasswordSettingItemMode aMode, TDes& aPassword ):CAknPasswordSettingItem( aIdentifier,
    aMode, aPassword )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingItem::~CTestPasswordSettingItem
// -----------------------------------------------------------------------------
//
CTestPasswordSettingItem::~CTestPasswordSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestPasswordSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestPasswordSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingItem::CTestVolumeSettingItem
// -----------------------------------------------------------------------------
//
CTestVolumeSettingItem::CTestVolumeSettingItem( TInt aIdentifier, 
    TInt& aExternalVolume ):CAknVolumeSettingItem( aIdentifier, aExternalVolume )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingItem::~CTestVolumeSettingItem
// -----------------------------------------------------------------------------
//
CTestVolumeSettingItem::~CTestVolumeSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingItem::DoInternalVolumeValue
// -----------------------------------------------------------------------------
//
TInt& CTestVolumeSettingItem::DoInternalVolumeValue()
    {
    return InternalVolumeValue();
    }

// -----------------------------------------------------------------------------
// CTestVolumeSettingItem::DoCreateBitmapL
// -----------------------------------------------------------------------------
//
CFbsBitmap* CTestVolumeSettingItem::DoCreateBitmapL()
    {
    return CreateBitmapL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::CTestSliderSettingItem
// -----------------------------------------------------------------------------
//
CTestSliderSettingItem::CTestSliderSettingItem( TInt aIdentifier, 
    TInt& aExternalSliderValue ):CAknSliderSettingItem( aIdentifier,
    aExternalSliderValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::~CTestSliderSettingItem
// -----------------------------------------------------------------------------
//
CTestSliderSettingItem::~CTestSliderSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::DoCreateSettingPageL
// -----------------------------------------------------------------------------
//
CAknSettingPage* CTestSliderSettingItem::DoCreateSettingPageL()
    {
    return CreateSettingPageL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::DoCreateAndExecuteSettingPageL
// -----------------------------------------------------------------------------
//
void CTestSliderSettingItem::DoCreateAndExecuteSettingPageL()
    {
    CreateAndExecuteSettingPageL();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::DoInternalSliderValue
// -----------------------------------------------------------------------------
//
TInt& CTestSliderSettingItem::DoInternalSliderValue()
    {
    return InternalSliderValue();
    }

// -----------------------------------------------------------------------------
// CTestSliderSettingItem::DoCreateBitmapL
// -----------------------------------------------------------------------------
//
CFbsBitmap* CTestSliderSettingItem::DoCreateBitmapL()
    {
    return CreateBitmapL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextSettingItem::CTestEnumeratedTextSettingItem
// -----------------------------------------------------------------------------
//
CTestEnumeratedTextSettingItem::CTestEnumeratedTextSettingItem( TInt aResourceId ):
    CAknEnumeratedTextSettingItem( aResourceId )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextSettingItem::~CTestEnumeratedTextSettingItem
// -----------------------------------------------------------------------------
//
CTestEnumeratedTextSettingItem::~CTestEnumeratedTextSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextSettingItem::DoSetSettingPageTextL
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextSettingItem::DoSetSettingPageTextL()
    {
    SetSettingPageTextL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextSettingItem::DoSettingPageTextArray
// -----------------------------------------------------------------------------
//
CDesCArray* CTestEnumeratedTextSettingItem::DoSettingPageTextArray() const
    {
    return SettingPageTextArray();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::CTestEnumeratedTextPopupSettingItem
// -----------------------------------------------------------------------------
//
CTestEnumeratedTextPopupSettingItem::CTestEnumeratedTextPopupSettingItem( TInt aResourceId, 
    TInt& aValue ):CAknEnumeratedTextPopupSettingItem( aResourceId, aValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::~CTestEnumeratedTextPopupSettingItem
// -----------------------------------------------------------------------------
//
CTestEnumeratedTextPopupSettingItem::~CTestEnumeratedTextPopupSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoCreateSettingPageL
// -----------------------------------------------------------------------------
//
CAknSettingPage* CTestEnumeratedTextPopupSettingItem::DoCreateSettingPageL()
    {
    return CreateSettingPageL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoCreateAndExecuteSettingPageL
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextPopupSettingItem::DoCreateAndExecuteSettingPageL()
    {
    CreateAndExecuteSettingPageL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextPopupSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoSetExternalValue
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextPopupSettingItem::DoSetExternalValue( TInt aNewValue )
    {
    SetExternalValue( aNewValue );
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoSetInternalValue
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextPopupSettingItem::DoSetInternalValue( TInt aNewValue )
    {
    SetInternalValue( aNewValue );
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoSetSelectedIndex
// -----------------------------------------------------------------------------
//
void CTestEnumeratedTextPopupSettingItem::DoSetSelectedIndex( TInt aNewIndex )
    {
    SetSelectedIndex( aNewIndex );
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoIndexFromValue
// -----------------------------------------------------------------------------
//
TInt CTestEnumeratedTextPopupSettingItem::DoIndexFromValue( TInt aInputValue ) const 
    {
    return IndexFromValue( aInputValue );
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoExternalValue
// -----------------------------------------------------------------------------
//
TInt CTestEnumeratedTextPopupSettingItem::DoExternalValue() const
    {
    return ExternalValue();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoInternalValue
// -----------------------------------------------------------------------------
//
TInt CTestEnumeratedTextPopupSettingItem::DoInternalValue() const
    {
    return InternalValue();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoQueryValue
// -----------------------------------------------------------------------------
//
MAknQueryValue* CTestEnumeratedTextPopupSettingItem::DoQueryValue() const
    {
    return QueryValue();
    }

// -----------------------------------------------------------------------------
// CTestBinaryPopupSettingItem::CTestBinaryPopupSettingItem
// -----------------------------------------------------------------------------
//
CTestBinaryPopupSettingItem::CTestBinaryPopupSettingItem( TInt aIdentifier, 
    TBool& aBinaryValue ):CAknBinaryPopupSettingItem( aIdentifier, aBinaryValue )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestBinaryPopupSettingItem::~CTestBinaryPopupSettingItem
// -----------------------------------------------------------------------------
//
CTestBinaryPopupSettingItem::~CTestBinaryPopupSettingItem()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestBinaryPopupSettingItem::DoCompleteConstructionL
// -----------------------------------------------------------------------------
//
void CTestBinaryPopupSettingItem::DoCompleteConstructionL()
    {
    CompleteConstructionL();
    
    }

// -----------------------------------------------------------------------------
// CTestBinaryPopupSettingItem::DoExternalValue
// -----------------------------------------------------------------------------
//
TInt CTestBinaryPopupSettingItem::DoExternalValue() const
    {
    return ExternalValue();
    }

// -----------------------------------------------------------------------------
// CTestEnumeratedTextPopupSettingItem::DoSetInternalValue
// -----------------------------------------------------------------------------
//
void CTestBinaryPopupSettingItem::DoSetInternalValue( TInt aNewValue )
    {
    SetInternalValue( aNewValue );
    }

// -----------------------------------------------------------------------------
// CTestBigSettingItemBase::CTestBigSettingItemBase
// -----------------------------------------------------------------------------
//
CTestBigSettingItemBase::CTestBigSettingItemBase( TInt aIdentifier ):
    CAknBigSettingItemBase( aIdentifier )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestBigSettingItemBase::~CTestBigSettingItemBase
// -----------------------------------------------------------------------------
//
CTestBigSettingItemBase::~CTestBigSettingItemBase()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestBigSettingItemBase::DoSettingTextL
// -----------------------------------------------------------------------------
//
const TDesC& CTestBigSettingItemBase::DoSettingTextL()
    {
    return SettingTextL();
    }

// -----------------------------------------------------------------------------
// CTestSettingItemArray::CTestSettingItemArray
// -----------------------------------------------------------------------------
//
CTestSettingItemArray::CTestSettingItemArray( TInt aGranularity, TBool aIsNumbered, 
    TInt aInitialOrdinal ):CAknSettingItemArray( aGranularity, aIsNumbered, aInitialOrdinal )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItemArray::~CTestSettingItemArray
// -----------------------------------------------------------------------------
//
CTestSettingItemArray::~CTestSettingItemArray()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItemArray::DoSetVisibleCount
// -----------------------------------------------------------------------------
//
void CTestSettingItemArray::DoSetVisibleCount( TInt aCount )
    {
    SetVisibleCount( aCount );
    }

// -----------------------------------------------------------------------------
// CTestSettingItemArray::DoVisibleCount
// -----------------------------------------------------------------------------
//
TInt CTestSettingItemArray::DoVisibleCount() const
    {
    return VisibleCount();
    }

// -----------------------------------------------------------------------------
// CTestSettingItemList::CTestSettingItemList
// -----------------------------------------------------------------------------
//
CTestSettingItemList::CTestSettingItemList()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItemList::~CTestSettingItemList
// -----------------------------------------------------------------------------
//
CTestSettingItemList::~CTestSettingItemList()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSettingItemList::DoCreateSettingItemL
// -----------------------------------------------------------------------------
//
CAknSettingItem* CTestSettingItemList::DoCreateSettingItemL( TInt aSettingId )
    {
    return CreateSettingItemL( aSettingId );
    }

//End file


