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
* Description:  Test EikMFNE.h
*
*/



// [INCLUDE FILES]

#include <eikmfne.h>
#include <lbsposition.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <eikenv.h>
#include <e32const.h>
#include <avkon.hrh>
#include <aknsitemid.h>
#include <aknsbasicbackgroundcontrolcontext.h>
#include <aknextendedinputcapabilities.h>
#include <akndef.h>
#include <s32mem.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorsmfne.h"
#include "testsdkeditorseikmfne.h"
#include "testsdkeditorscontrol.h"

//CONST
const TInt KLength = 10;
const TInt KMin = 0;
const TInt KMax = 99999;
const TInt KInitial = 100;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNECEikMfneFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNECEikMfneFieldL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsMFNE* mfne = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEIsEditableL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEIsEditableL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsMFNE* mfne = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    STIF_ASSERT_FALSE( mfne->IsEditable() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEIsValidL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEIsValidL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsMFNE* mfne = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    STIF_ASSERT_TRUE( mfne->IsValid() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEHighlightTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEHighlightTypeL( CStifItemParser& /*aItem*/ )
    {
// This function will call panic directly on debug mode, so no need to test it temporary
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEHandleKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEHandleKeyL( CStifItemParser& /*aItem*/ )
    {
// This function will call panic directly on debug mode, so no need to test it temporary
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEHandleDeHighlightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEHandleDeHighlightL( CStifItemParser& /*aItem*/ )
    {
// This function will call panic directly on debug mode, so no need to test it temporary
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEHandleLeftOrRightArrowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEHandleLeftOrRightArrowL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsMFNE* mfne = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    TBool dataAltered;
    TInt highlightIncrement;
    mfne->HandleLeftOrRightArrow( EKeyLeftArrow, dataAltered, highlightIncrement );
    STIF_ASSERT_EQUALS( -1, highlightIncrement );
    STIF_ASSERT_TRUE( dataAltered );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SEPARATOR );
    
    CEikMfneSeparator* separator = CEikMfneSeparator::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( separator );
    STIF_ASSERT_NOT_NULL( separator );
    
    CleanupStack::Pop( separator );
    delete separator;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNERNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNERNewL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SEPARATOR );
    
    CEikMfneSeparator* separator = CEikMfneSeparator::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( separator );
    STIF_ASSERT_NOT_NULL( separator );
    
    CleanupStack::PopAndDestroy( separator );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEHNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEHNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KText, "text" );
    TBuf<KLength> buf( KText );
    HBufC* text = buf.AllocLC();
    CEikMfneSeparator* separator = CEikMfneSeparator::NewL( text );
    CleanupStack::PushL( separator );
    STIF_ASSERT_NOT_NULL( separator );
    
    CleanupStack::PopAndDestroy( separator );
    CleanupStack::Pop( text );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESetTextL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SEPARATOR );
    
    CEikMfneSeparator* separator = CEikMfneSeparator::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( separator );
    STIF_ASSERT_NOT_NULL( separator );
    
    _LIT( KText, "text" );
    TBuf<KLength> buf( KText );
    HBufC* text = buf.AllocLC();
    separator->SetText( text );
    
    CleanupStack::Pop( text );
    CleanupStack::PopAndDestroy( separator );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::Pop( mfne );
    delete mfne;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENRNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENRNewL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENVNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENVNewL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetMinimumAndMaximum( KMin, KMax, *font );
    TInt min;
    TInt max;
    mfne->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_EQUALS( KMin, min );
    STIF_ASSERT_EQUALS( KMax, max );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNENSetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENSetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENSetValueL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetValue( KInitial, *font );
    STIF_ASSERT_EQUALS( KInitial, mfne->Value() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENValueL( CStifItemParser& aItem )
    {
    return TestMFNENSetValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENIsValidL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENIsValidL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    STIF_ASSERT_TRUE( mfne->IsValid() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENSetUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENSetUninitialisedL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetUninitialised( EFalse );
    STIF_ASSERT_FALSE( mfne->IsUninitialised() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENIsUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENIsUninitialisedL( CStifItemParser& aItem )
    {
    return TestMFNENSetUninitialisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENSetDigitTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENSetDigitTypeL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetDigitType( EDigitTypeAllTypes, *font );
    STIF_ASSERT_TRUE( EDigitTypeAllTypes == mfne->DigitType() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENDigitTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENDigitTypeL( CStifItemParser& aItem )
    {
    return TestMFNENSetDigitTypeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENRefreshDigitTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENRefreshDigitTypeL( CStifItemParser& /*aItem*/ )
    {
    const CFont* font = ivEikonEnv->LegendFont();
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MFNENUMBER );
    
    CEikMfneNumber* mfne = CEikMfneNumber::NewL( *font, reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->RefreshDigitType( *font );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESCDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESCDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ITEM );
    
    CEikMfneSymbol::CItem* item = CEikMfneSymbol::CItem::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CleanupStack::Pop( item );
    delete item;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESCRNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESCRNewL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ITEM );
    
    CEikMfneSymbol::CItem* item = CEikMfneSymbol::CItem::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );

    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESCNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESCNewL( CStifItemParser& /*aItem*/ )
    {
    const TInt keyToMacth = 10;
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    HBufC* buf = text.AllocLC();
    
    CEikMfneSymbol::CItem* item = CEikMfneSymbol::CItem::NewL( 0, keyToMacth, buf );
    CleanupStack::Pop( buf );
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESCSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESCSetTextL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ITEM );
    
    CEikMfneSymbol::CItem* item = CEikMfneSymbol::CItem::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    HBufC* buf = text.AllocLC();
    item->SetText( buf );
    CleanupStack::Pop( buf );
    
    CleanupStack::PopAndDestroy( item );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SYMBOL );
    
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    CleanupStack::Pop( symbol );
    delete symbol;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESRNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESRNewL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SYMBOL );
    
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    CleanupStack::PopAndDestroy( symbol );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESNewL( CStifItemParser& /*aItem*/ )
    {
    const TInt numSymbolicItems = 2; 
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( numSymbolicItems );
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    CleanupStack::PopAndDestroy( symbol );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESAddSymbolicItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESAddSymbolicItemL( CStifItemParser& /*aItem*/ )
    {
    const TInt numSymbolicItems = 2; 
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( numSymbolicItems );
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_ITEM );
    
    CEikMfneSymbol::CItem* item = CEikMfneSymbol::CItem::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( item );
    STIF_ASSERT_NOT_NULL( item );
    CleanupStack::Pop( item );
    
    symbol->AddSymbolicItem( item, ETrue );
    
    CleanupStack::PopAndDestroy( symbol );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESSetCurrentSymbolicItemToIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESSetCurrentSymbolicItemToIdL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SYMBOL );
    
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    symbol->SetCurrentSymbolicItemToId( 0 );
    STIF_ASSERT_EQUALS( 0, symbol->IdOfCurrentSymbolicItem() );
    
    CleanupStack::PopAndDestroy( symbol );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESIdOfCurrentSymbolicItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESIdOfCurrentSymbolicItemL( CStifItemParser& aItem )
    {
    return TestMFNESSetCurrentSymbolicItemToIdL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESSetUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESSetUninitialisedL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SYMBOL );
    
    CEikMfneSymbol* symbol = CEikMfneSymbol::NewL( reader );
    CleanupStack::PopAndDestroy();
    CleanupStack::PushL( symbol );
    STIF_ASSERT_NOT_NULL( symbol );
    
    symbol->SetUninitialised( ETrue );
    STIF_ASSERT_TRUE( symbol->IsUninitialised() );
    
    CleanupStack::PopAndDestroy( symbol );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNESIsUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNESIsUninitialisedL( CStifItemParser& aItem )
    {
    return TestMFNESSetUninitialisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMCEikMfneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMCEikMfneL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::Pop( mfne );
    delete mfne;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMCreateFieldArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMCreateFieldArrayL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMAddFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMAddFieldL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    mfne->ResetFieldArray();
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMResetFieldArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMResetFieldArrayL( CStifItemParser& aItem )
    {
    return TestMFNEMAddFieldL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMBorderMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMBorderMarginsL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    TMargins margin = mfne->BorderMargins();
    STIF_ASSERT_EQUALS( 1, margin.iLeft );
    STIF_ASSERT_EQUALS( 1, margin.iRight );
    STIF_ASSERT_EQUALS( 1, margin.iTop );
    STIF_ASSERT_EQUALS( 1, margin.iBottom );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMDrawNowAndLeaveWithTimeDateFormatInfoMsgL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMDrawNowAndLeaveWithTimeDateFormatInfoMsgL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    TTime time;
    TRAP_IGNORE( mfne->DrawNowAndLeaveWithTimeDateFormatInfoMsgL( R_TESTSDK_GLOBALTEXT, time ) );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMFieldL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    STIF_ASSERT_TRUE( field == mfne->Field( 0 ) );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMReadTimeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMReadTimeL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIME );
    TTime time = CEikMfne::ReadTime( reader );
    const TInt KTime = 10; 
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Hour() );
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Second() );
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Minute() );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMReadDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMReadDateL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DATE );
    TTime time = CEikMfne::ReadDate( reader );
    const TInt KYear = 2008;
    const TInt KDay = 8;
    STIF_ASSERT_EQUALS( KYear, time.DateTime().Year() );
    STIF_ASSERT_EQUALS( EAugust, time.DateTime().Month() );
    STIF_ASSERT_EQUALS( KDay, time.DateTime().Day() );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMReadTimeAndDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMReadTimeAndDateL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEANDDATE );
    TTime time = CEikMfne::ReadTimeAndDate( reader );
    const TInt KYear = 2008;
    const TInt KDay = 8;
    STIF_ASSERT_EQUALS( KYear, time.DateTime().Year() );
    STIF_ASSERT_EQUALS( EAugust, time.DateTime().Month() );
    STIF_ASSERT_EQUALS( KDay, time.DateTime().Day() );
    const TInt KTime = 10; 
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Hour() );
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Second() );
    STIF_ASSERT_EQUALS( KTime, time.DateTime().Minute() );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMReadDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMReadDurationL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DURATION );
    TTimeIntervalSeconds time = CEikMfne::ReadDuration( reader );
    const TTimeIntervalSeconds KTime = 10;
    STIF_ASSERT_EQUALS( KTime, time );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMReadTimeOffsetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMReadTimeOffsetL( CStifItemParser& /*aItem*/ )
    {
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEOFFSET );
    TTimeIntervalSeconds time = CEikMfne::ReadTimeOffset( reader );
    const TTimeIntervalSeconds KTime = 10;
    STIF_ASSERT_EQUALS( KTime, time );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMConvertL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMConvertL( CStifItemParser& /*aItem*/ )
    {
    TTime time;
    TTimeIntervalSeconds second = CEikMfne::Convert( time );
    TTime timeGet = CEikMfne::Convert( second );
    
    STIF_ASSERT_EQUALS( timeGet.DateTime().Hour(), time.DateTime().Hour() );
    STIF_ASSERT_EQUALS( timeGet.DateTime().Minute(), time.DateTime().Minute() );
    STIF_ASSERT_EQUALS( timeGet.DateTime().Second(), time.DateTime().Second() );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMTConvertL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMTConvertL( CStifItemParser& aItem )
    {
    return TestMFNEMConvertL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMCurrentFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMCurrentFieldL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    TInt current = mfne->CurrentField();
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMNumFieldsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMNumFieldsL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    STIF_ASSERT_EQUALS( 1, mfne->NumFields() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetMfneAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetMfneAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->SetMfneAlignment( EAknEditorAlignLeft  );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetUpAndDownKeysConsumedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetUpAndDownKeysConsumedL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetUpAndDownKeysConsumed( ETrue );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetSuppressBackgroundDrawingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetSuppressBackgroundDrawingL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->SetSuppressBackgroundDrawing( ETrue );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetFeatureL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    STIF_ASSERT_TRUE( mfne->SupportsFeature( CEikMfne::EClipGcToRect ) );
    STIF_ASSERT_EQUALS( KErrNone, mfne->SetFeature( CEikMfne::EClipGcToRect, CEikMfne::EClipGcToRect ) );
    TInt para;
    STIF_ASSERT_FALSE( mfne->GetFeature( CEikMfne::EDisablePenInput, para ) );
    STIF_ASSERT_EQUALS( 0, para );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMGetFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMGetFeatureL( CStifItemParser& aItem )
    {
    return TestMFNEMSetFeatureL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSupportsFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSupportsFeatureL( CStifItemParser& aItem )
    {
    return TestMFNEMSetFeatureL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMFontL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    const CFont* font = ivEikonEnv->LegendFont();
    mfne->SetFont( font );
    STIF_ASSERT_EQUALS( font, mfne->Font() );
    
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetFontL( CStifItemParser& aItem )
    {
    return TestMFNEMFontL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetSkinBackgroundControlContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetSkinBackgroundControlContextL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );

    TAknsItemID itemId;
    TRect rect( 0, 0, KLength, KLength );
    CAknsBasicBackgroundControlContext* context = CAknsBasicBackgroundControlContext::NewL( itemId, rect, ETrue );
    CleanupStack::PushL( context );
    
    mfne->SetSkinBackgroundControlContextL( context );
    
    CleanupStack::PopAndDestroy( context );
    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMHandleMfneCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMHandleMfneCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    mfne->HandleMfneCommandL( MAknMfneCommandObserver::EMfneIncrementCurrentFieldValue );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetUseOverrideColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetUseOverrideColorsL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    mfne->SetUseOverrideColors( ETrue );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->SetContainerWindowL( *control );
    
    TKeyEvent event;
    event.iCode = EKeyLeftArrow;
    TKeyResponse response = mfne->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );

    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->SetContainerWindowL( *control );
    
    mfne->PrepareForFocusLossL();

    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    TSize size = mfne->MinimumSize();

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    CArrayFix <TCoeColorUse>* colorUseList = new( ELeave ) CArrayFix <TCoeColorUse>( ( TBufRep )CBufFlat::NewL, 1 );
    CleanupStack::PushL( colorUseList );
    mfne->GetColorUseListL( *colorUseList );
    STIF_ASSERT_NOT_NULL( colorUseList );
    
    CleanupStack::PopAndDestroy( colorUseList );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->HandleResourceChange( KEikDynamicLayoutVariantSwitch );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    TCoeInputCapabilities capa = mfne->InputCapabilities();

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->SetContainerWindowL( *control );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    mfne->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = mfne->MopSupplyObject( CAknExtendedInputCapabilities::ETypeId );
    CAknExtendedInputCapabilities* point = static_cast<CAknExtendedInputCapabilities*> ( ptr.Pointer() );
    STIF_ASSERT_NOT_NULL( point );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSetSkinTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSetSkinTextColorL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    mfne->SetSkinTextColorL( 1 );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    mfne->SetContainerWindowL( *control );
    
    mfne->FocusChanged( EDrawNow );

    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
        
    STIF_ASSERT_NOT_LEAVES( mfne->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMHandleInteractionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMHandleInteractionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    mfne->SetContainerWindowL( *control );
    
    TBool dataAltered;
    TBool error;
    mfne->HandleInteraction( ETrue, 0, 1, CEikMfneField::ECursor, dataAltered, error );

    CleanupStack::PopAndDestroy( mfne );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMFieldIsAboutToBeDeHighlightedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMFieldIsAboutToBeDeHighlightedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    TBool drawAllFields;
    mfne->FieldIsAboutToBeDeHighlighted( field, drawAllFields );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMMfneSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMMfneSizeL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    TSize size = mfne->MfneSize();

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMPMfneSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMPMfneSizeL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    CTestSDKEditorsMFNE* field = new (ELeave) CTestSDKEditorsMFNE;
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    TSize size = mfne->MfneSize( ETrue );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEIKMFNE* mfne = new ( ELeave ) CTestSDKEditorsEIKMFNE;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );

    mfne->SizeChanged();

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEMMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEMMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    STIF_ASSERT_NOT_NULL( mfne );
    
    mfne->CreateFieldArrayL( 1 );
    const CFont* font = ivEikonEnv->LegendFont();
    CEikMfneNumber* field = CEikMfneNumber::NewL( *font, KMin, KMax, KInitial, 0 );
    
    CleanupStack::PushL( field );
    STIF_ASSERT_NOT_NULL( field );
    
    mfne->AddField( field );
    CleanupStack::Pop( field );
    
    mfne->MakeVisible( ETrue );

    CleanupStack::PopAndDestroy( mfne );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENECEikNumberEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENECEikNumberEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    CleanupStack::PopAndDestroy( numberEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    numberEditor->ConstructL( KMin, KMax, KInitial );
    
    CleanupStack::PopAndDestroy( numberEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    numberEditor->ConstructL( KMin, KMax, KInitial );
    numberEditor->SetMinimumAndMaximum( KMin, KMax );
    TInt min;
    TInt max;
    numberEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_EQUALS( min, KMin );
    STIF_ASSERT_EQUALS( max, KMax );
    
    CleanupStack::PopAndDestroy( numberEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNENESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENESetNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENESetNumberL( CStifItemParser& /*aItem*/ )
    {
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    numberEditor->ConstructL( KMin, KMax, KInitial );
    numberEditor->SetNumber( KMax );
    STIF_ASSERT_EQUALS( KMax, numberEditor->Number() );
    
    CleanupStack::PopAndDestroy( numberEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENENumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENENumberL( CStifItemParser& aItem )
    {
    return TestMFNENESetNumberL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_NUMBEREDITOR );
    numberEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( numberEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNENEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNENEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikNumberEditor* numberEditor = new (ELeave) CEikNumberEditor;
    CleanupStack::PushL( numberEditor );
    STIF_ASSERT_NOT_NULL( numberEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_NUMBEREDITOR );
    numberEditor->ConstructFromResourceL( reader );
    numberEditor->SetContainerWindowL( *control );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    numberEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( numberEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNERECEikRangeEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNERECEikRangeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );

    CleanupStack::PopAndDestroy( rangeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEREConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEREConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    SEikRange eikRange;
    eikRange.iLowerLimit = KMin;
    eikRange.iUpperLimit = KMax;
    _LIT( KText, "range" );
    TFileName text( KText );
    HBufC* buf = text.AllocLC();
    rangeEditor->ConstructL( KMin, KMax, eikRange, buf );
    
    CleanupStack::Pop( buf );
    CleanupStack::PopAndDestroy( rangeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNERESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNERESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    SEikRange eikRange;
    eikRange.iLowerLimit = KMin;
    eikRange.iUpperLimit = KMax;
    _LIT( KText, "range" );
    TFileName text( KText );
    HBufC* buf = text.AllocLC();
    rangeEditor->ConstructL( KMin, KMax, eikRange, buf );
    
    rangeEditor->SetMinimumAndMaximum( KMin, KMax );
    TInt min;
    TInt max;
    rangeEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_EQUALS( min, KMin );
    STIF_ASSERT_EQUALS( max, KMax );
    
    CleanupStack::Pop( buf );
    CleanupStack::PopAndDestroy( rangeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEREGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEREGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNERESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNERESetRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNERESetRangeL( CStifItemParser& /*aItem*/ )
    {
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    SEikRange eikRange;
    eikRange.iLowerLimit = KMin;
    eikRange.iUpperLimit = KMax;
    _LIT( KText, "range" );
    TFileName text( KText );
    HBufC* buf = text.AllocLC();
    rangeEditor->ConstructL( KMin, KMax, eikRange, buf );
    
    rangeEditor->SetRange( eikRange );
    STIF_ASSERT_TRUE( eikRange.iLowerLimit == rangeEditor->Range().iLowerLimit );
    STIF_ASSERT_TRUE( eikRange.iUpperLimit == rangeEditor->Range().iUpperLimit );
    
    CleanupStack::Pop( buf );
    CleanupStack::PopAndDestroy( rangeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNERERangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNERERangeL( CStifItemParser& aItem )
    {
    return TestMFNERESetRangeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEREConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEREConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RANGEEDITOR );
    rangeEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( rangeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEREHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEREHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikRangeEditor* rangeEditor = new (ELeave) CEikRangeEditor;
    CleanupStack::PushL( rangeEditor );
    STIF_ASSERT_NOT_NULL( rangeEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RANGEEDITOR );
    rangeEditor->ConstructFromResourceL( reader );
    rangeEditor->SetContainerWindowL( *control );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    rangeEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( rangeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETECEikTimeEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETECEikTimeEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    CleanupStack::Pop( timeEditor );
    delete timeEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( maxdatetime );
    
    timeEditor->ConstructL( mintime, maxtime, time , 0 );
    
    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETESetTimeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETESetTimeL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( maxdatetime );
    
    timeEditor->ConstructL( mintime, maxtime, time , 0 );
    timeEditor->SetTime( maxtime );
    STIF_ASSERT_TRUE( maxtime == timeEditor->Time() );
    
    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETETimeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETETimeL( CStifItemParser& aItem )
    {
    return TestMFNETESetTimeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETESetUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETESetUninitialisedL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( maxdatetime );
    
    timeEditor->ConstructL( mintime, maxtime, time , 0 );
    timeEditor->SetUninitialised( ETrue );
    STIF_ASSERT_TRUE( timeEditor->IsUninitialised() );
    
    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEIsUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEIsUninitialisedL( CStifItemParser& aItem )
    {
    return TestMFNETESetUninitialisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TDateTime datetime( 0, TMonth( 0 ), 0, 20, 20, 20, 0 );
    TTime time( datetime );
    TDateTime mindatetime( 0, TMonth( 0 ), 0, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 0, TMonth( 0 ), 0, 23, 59, 59, 0 );
    TTime maxtime( maxdatetime );
    
    timeEditor->ConstructL( mintime, maxtime, time , 0 );
    timeEditor->SetMinimumAndMaximum( mintime, maxtime );
    TTime min;
    TTime max;
    timeEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_TRUE( max == maxtime );
    STIF_ASSERT_TRUE( min == mintime );
    
    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNETESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEEDITOR );
    timeEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( timeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEEDITOR );
    timeEditor->ConstructFromResourceL( reader );
    timeEditor->SetContainerWindowL( *control );
    
    timeEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( timeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeEditor* timeEditor = new (ELeave) CEikTimeEditor;
    CleanupStack::PushL( timeEditor );
    STIF_ASSERT_NOT_NULL( timeEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEEDITOR );
    timeEditor->ConstructFromResourceL( reader );
    timeEditor->SetContainerWindowL( *control );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    timeEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( timeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDECEikDateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDECEikDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    CleanupStack::Pop( dateEditor );
    delete dateEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    
    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDESetDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDESetDateL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetDate( datetime );
    TTime dateGet = dateEditor->Date();
    STIF_ASSERT_TRUE( date == dateGet );
    
    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEDateL( CStifItemParser& aItem )
    {
    return TestMFNEDESetDateL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDESetUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDESetUninitialisedL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetUninitialised( ETrue );
    STIF_ASSERT_TRUE( dateEditor->IsUninitialised() );
    
    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEIsUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEIsUninitialisedL( CStifItemParser& aItem )
    {
    return TestMFNEDESetUninitialisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetMinimumAndMaximum( mintime, maxtime );
    TTime min;
    TTime max;
    dateEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_TRUE( min == mintime );
    STIF_ASSERT_TRUE( max == maxtime );
    
    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNEDESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetContainerWindowL( *control );

    TKeyEvent event;
    event.iCode = EKeyLeftArrow;
    TKeyResponse response = dateEditor->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    CleanupStack::PopAndDestroy( dateEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DATEEDITOR );
    dateEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( dateEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetContainerWindowL( *control );

    dateEditor->PrepareForFocusLossL();
    
    
    CleanupStack::PopAndDestroy( dateEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNEDEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNEDEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikDateEditor* dateEditor = new (ELeave) CEikDateEditor;
    CleanupStack::PushL( dateEditor );
    STIF_ASSERT_NOT_NULL( dateEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintime( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 0, 0, 0, 0 );
    TTime maxtime( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 0, 0, 0, 0 );
    TTime date( datetime );
    
    dateEditor->ConstructL( mintime, maxtime, date , ETrue );
    dateEditor->SetContainerWindowL( *control );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    dateEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( dateEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDECEikTimeAndDateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDECEikTimeAndDateEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    CleanupStack::Pop( datetimeEditor );
    delete datetimeEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDESetTimeAndDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDESetTimeAndDateL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetTimeAndDate( timeanddate );
    STIF_ASSERT_TRUE( timeanddate == datetimeEditor->TimeAndDate() );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDETimeAndDateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDETimeAndDateL( CStifItemParser& aItem )
    {
    return TestMFNETDESetTimeAndDateL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDESetUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDESetUninitialisedL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetUninitialised( ETrue );
    STIF_ASSERT_TRUE( datetimeEditor->IsUninitialised() );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEIsUninitialisedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEIsUninitialisedL( CStifItemParser& aItem )
    {
    return TestMFNETDESetUninitialisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetMinimumAndMaximum( mintimeanddate, maxtimeanddate );
    TTime min;
    TTime max;
    datetimeEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_TRUE( min == mintimeanddate );
    STIF_ASSERT_TRUE( max == maxtimeanddate );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNETDESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetContainerWindowL( *control );

    TKeyEvent event;
    event.iCode = EKeyLeftArrow;
    TKeyResponse response = datetimeEditor->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_TIMEDATEEDITOR );
    datetimeEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( datetimeEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetContainerWindowL( *control );

    datetimeEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeAndDateEditor* datetimeEditor = new (ELeave) CEikTimeAndDateEditor;
    CleanupStack::PushL( datetimeEditor );
    STIF_ASSERT_NOT_NULL( datetimeEditor );

    TDateTime mindatetime( 1900, TMonth( 0 ), 1, 0, 0, 0, 0 );
    TTime mintimeanddate( mindatetime );
    TDateTime maxdatetime( 2100, TMonth( 11 ), 30, 23, 59, 59, 0 );
    TTime maxtimeanddate( maxdatetime );
    TDateTime datetime( 2008, TMonth( 7 ), 8, 20, 20, 20, 0 );
    TTime timeanddate( datetime );
    
    datetimeEditor->ConstructL( mintimeanddate, maxtimeanddate, timeanddate , 0 );
    datetimeEditor->SetContainerWindowL( *control );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    datetimeEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( datetimeEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUECEikDurationEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUECEikDurationEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    CleanupStack::PopAndDestroy( durationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    CleanupStack::Pop( durationEditor );
    delete durationEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minduration( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxduration( maxC );
    const TInt durationC = 1000;
    TTimeIntervalSeconds duration( durationC );
    
    durationEditor->ConstructL( minduration, maxduration, duration , 0 );
    
    CleanupStack::PopAndDestroy( durationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minduration( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxduration( maxC );
    const TInt durationC = 1000;
    TTimeIntervalSeconds duration( durationC );
    
    durationEditor->ConstructL( minduration, maxduration, duration , 0 );
    durationEditor->SetMinimumAndMaximum( minduration, maxduration );
    TTimeIntervalSeconds min;
    TTimeIntervalSeconds max;
    durationEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_TRUE( min == minduration );
    STIF_ASSERT_TRUE( max == maxduration );
    
    CleanupStack::PopAndDestroy( durationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNETDUESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUESetDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUESetDurationL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minduration( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxduration( maxC );
    const TInt durationC = 1000;
    TTimeIntervalSeconds duration( durationC );
    
    durationEditor->ConstructL( minduration, maxduration, duration , 0 );
    durationEditor->SetDuration( duration );
    STIF_ASSERT_TRUE( duration == durationEditor->Duration() );
    
    CleanupStack::PopAndDestroy( durationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEDurationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEDurationL( CStifItemParser& aItem )
    {
    return TestMFNETDUESetDurationL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DURATIONEDITOR );
    durationEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( durationEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DURATIONEDITOR );
    durationEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    durationEditor->SetContainerWindowL( *control );

    durationEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( durationEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETDUEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETDUEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikDurationEditor* durationEditor = new (ELeave) CEikDurationEditor;
    CleanupStack::PushL( durationEditor );
    STIF_ASSERT_NOT_NULL( durationEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_DURATIONEDITOR );
    durationEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    durationEditor->SetContainerWindowL( *control );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    durationEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( durationEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOECEikTimeOffsetEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOECEikTimeOffsetEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    CleanupStack::PopAndDestroy( offsetEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    CleanupStack::Pop( offsetEditor );
    delete offsetEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minTimeOffset( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxTimeOffset( maxC );
    const TInt timeOffsetC = 1000;
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    
    offsetEditor->ConstructL( minTimeOffset, maxTimeOffset, timeOffset , 0 );
    
    CleanupStack::PopAndDestroy( offsetEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOESetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOESetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minTimeOffset( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxTimeOffset( maxC );
    const TInt timeOffsetC = 1000;
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    
    offsetEditor->ConstructL( minTimeOffset, maxTimeOffset, timeOffset , 0 );
    offsetEditor->SetMinimumAndMaximum( minTimeOffset, maxTimeOffset );
    TTimeIntervalSeconds min;
    TTimeIntervalSeconds max;
    offsetEditor->GetMinimumAndMaximum( min, max );
    STIF_ASSERT_TRUE( min == minTimeOffset );
    STIF_ASSERT_TRUE( max == maxTimeOffset );
    
    CleanupStack::PopAndDestroy( offsetEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEGetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEGetMinimumAndMaximumL( CStifItemParser& aItem )
    {
    return TestMFNETOESetMinimumAndMaximumL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOESetTimeOffsetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOESetTimeOffsetL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    const TInt minC = 0;
    TTimeIntervalSeconds minTimeOffset( minC );
    const TInt maxC = 1000000;
    TTimeIntervalSeconds maxTimeOffset( maxC );
    const TInt timeOffsetC = 1000;
    TTimeIntervalSeconds timeOffset( timeOffsetC );
    
    offsetEditor->ConstructL( minTimeOffset, maxTimeOffset, timeOffset , 0 );
    offsetEditor->SetTimeOffset( timeOffset );
    STIF_ASSERT_TRUE( timeOffset == offsetEditor->TimeOffset() );
    
    CleanupStack::PopAndDestroy( offsetEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOETimeOffsetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOETimeOffsetL( CStifItemParser& aItem )
    {
    return TestMFNETOESetTimeOffsetL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_OFFSETEDITOR );
    offsetEditor->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( offsetEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_OFFSETEDITOR );
    offsetEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    offsetEditor->SetContainerWindowL( *control );

    offsetEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( offsetEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestMFNETOEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestMFNETOEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikTimeOffsetEditor* offsetEditor = new (ELeave) CEikTimeOffsetEditor;
    CleanupStack::PushL( offsetEditor );
    STIF_ASSERT_NOT_NULL( offsetEditor );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_OFFSETEDITOR );
    offsetEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    offsetEditor->SetContainerWindowL( *control );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    offsetEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( offsetEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }
