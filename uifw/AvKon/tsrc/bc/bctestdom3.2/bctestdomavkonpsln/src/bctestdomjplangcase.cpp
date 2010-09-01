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
* Description:  ?Description
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <jplangutil.h>
#include <numbergrouping.h>
#include <genericparamconsumer.h>
#include <aiwgenericparam.h>


#include <bctestdomavkonpsln.rsg>

#include "bctestdomjplangcase.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestdomavkonpslnext.h"
#include "bctestdomavkonpsln.hrh"

//CONSTANTS

const TInt KDesLength = 24;
_LIT( KText, "Text" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomJPLangCase* CBCTestDomJPLangCase::NewL( CBCTestDomAvkonPslnContainer* 
    aContainer )
    {
    CBCTestDomJPLangCase* self = new( ELeave ) CBCTestDomJPLangCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomJPLangCase::CBCTestDomJPLangCase( CBCTestDomAvkonPslnContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomJPLangCase::~CBCTestDomJPLangCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomJPLangCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomJPLangCase::BuildScriptL()
    { 
    const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, 3 ),
        KeyOK,
        TEND
        };
    AddTestScriptL( scripts, sizeof(scripts)/sizeof(TInt) );  
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomJPLangCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline4 )
        {
        return;
        }
    switch ( aCmd )  
        {
        case EBCTestCmdOutline4:
            TestJPLangUtilL();
            TestNumberGroupL();
            TestGenericParamConsumerL();
            break;
        default:
            break;
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestDomJPLangCase::TestJPLangUtilL()
    {
    // Test some API here
    
    _LIT( KConvertHalfToFullWidth, 
        "JPLangUtil::ConvertHalfToFullWidth() invoked" );
    _LIT( KConvertFullToHalfWidth, 
        "JPLangUtil::ConvertFullToHalfWidth() invoked" );
    _LIT( KConvertHalfToFullWidthKatakana, 
        "JPLangUtil::ConvertHalfToFullWidthKatakana() invoked" );
    _LIT( KConvertFullHiragnaToFullKatakana, 
        "JPLangUtil::ConvertFullHiragnaToFullKatakana() invoked" );
    _LIT( KIsKatakana, "JPLangUtil::IsKatakana() invoked" );    
    _LIT( KIsHiragana, "JPLangUtil::IsHiragana() invoked" );    
    _LIT( KIsKanji, "JPLangUtil::IsKanji() invoked" );        
    _LIT( KIsHalfWidth, "JPLangUtil::IsKanji() invoked" );    
    _LIT( KIsFullWidth, "JPLangUtil::IsFullWidth() invoked" );    
    
    TBuf<KDesLength> unisrc( KText );
    TBuf<KDesLength> unides;                
    JPLangUtil::ConvertHalfToFullWidth( unisrc, unides );
    AssertTrueL( ETrue, KConvertHalfToFullWidth );
    
    JPLangUtil::ConvertFullToHalfWidth( unisrc, unides );
    AssertTrueL( ETrue, KConvertFullToHalfWidth );
    
    JPLangUtil::ConvertHalfToFullWidthKatakana( unisrc, unides );
    AssertTrueL( ETrue, KConvertHalfToFullWidthKatakana );

    JPLangUtil::ConvertFullToHalfWidthKatakana( unisrc, unides );
    AssertTrueL( ETrue, KConvertHalfToFullWidthKatakana );
    
    JPLangUtil::ConvertFullHiragnaToFullKatakana( unisrc, unides );
    AssertTrueL( ETrue, KConvertFullHiragnaToFullKatakana );
    
    JPLangUtil::IsKatakana( *unisrc.Ptr() );
    AssertTrueL( ETrue, KIsKatakana );
    
    JPLangUtil::IsHiragana( *unisrc.Ptr() );
    AssertTrueL( ETrue, KIsHiragana );
    
    JPLangUtil::IsKanji( *unisrc.Ptr() );
    AssertTrueL( ETrue, KIsKanji );
    
    JPLangUtil::IsHalfWidth( *unisrc.Ptr() );
    AssertTrueL( ETrue, KIsHalfWidth );
    
    JPLangUtil::IsFullWidth( *unisrc.Ptr() );
    AssertTrueL( ETrue, KIsFullWidth );
    
    }
 
// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::TestNumberGroupL()
// ---------------------------------------------------------------------------
//       
void CBCTestDomJPLangCase::TestNumberGroupL()
    {
    
    _LIT( KNewL, "CPNGNumberGrouping::NewL() invoked" );
    _LIT( KDes, "CPNGNumberGrouping::~CPNGNumberGrouping() invokde" );
    _LIT( KNewLC, "CPNGNumberGrouping::NewLC() invoked" );
    _LIT( KInsert, "CPNGNumberGrouping::Insert() invoked" );
    _LIT( KDelete, "CPNGNumberGrouping::Delete() invoked" );
    _LIT( KAppend, "CPNGNumberGrouping::Append() invoked" );
    _LIT( KSet, "CPNGNumberGrouping::Set() invoked" );
    _LIT( KUnFormattedLength, 
        "CPNGNumberGrouping::UnFormattedLength() invoked" );
    _LIT( KMaxDisplayLength, 
        "CPNGNumberGrouping::MaxDisplayLength() invoked" );
    _LIT( KIsSpace, "CPNGNumberGrouping::IsSpace() invoked" );
    
    _LIT( KFormattedNumber, 
        "CPNGNumberGrouping::FormattedNumber() invoked" );
    _LIT( KFormattedNumberOverLoad, 
        "CPNGNumberGrouping::FormattedNumber() overload invoked" );
    _LIT( KReverseFormattedNumber, 
        "CPNGNumberGrouping::ReverseFormattedNumber() invoked" );
    _LIT( KReverseFormattedNumberOverLoad, 
        "CPNGNumberGrouping::ReverseFormattedNumber() overload invoked" );
    _LIT( KSelection, 
        "CPNGNumberGrouping::Selection() invoked" );
    _LIT( KUnFormattedNumber, 
        "CPNGNumberGrouping::UnFormattedNumber() invoked" );
    _LIT( KIsCharacterInsertedByNumberGrouping, 
        "CPNGNumberGrouping::IsCharacterInsertedByNumberGrouping() invoked" );
    _LIT( KIsChangedByGrouping, 
        "CPNGNumberGrouping::IsChangedByGrouping() overload invoked" );
    
    CPNGNumberGrouping* group = CPNGNumberGrouping::NewL();
    CleanupStack::PushL( group );
    AssertNotNullL( group, KNewL );
    
    CleanupStack::Pop( group );
    delete group;
    group = NULL;
    AssertTrueL( ETrue, KDes );
    
    group = CPNGNumberGrouping::NewLC();
    AssertNotNullL( group, KNewLC );
    
    const TInt index = 0;
    TText chr( 'a' );
    TBuf<KDesLength>  numstr( KText );
    
    group->Insert( index, chr );
    AssertTrueL( ETrue, KInsert );
    
    group->Delete( index );
    AssertTrueL( ETrue, KDelete );
    
    group->Append( chr );
    AssertTrueL( ETrue, KAppend );
    
    group->Set( numstr );
    AssertTrueL( ETrue, KSet );
    
    group->UnFormattedLength();
    AssertTrueL( ETrue, KUnFormattedLength );
    
    group->MaxDisplayLength();
    AssertTrueL( ETrue, KMaxDisplayLength );
    
    group->IsSpace( index );
    AssertTrueL( ETrue, KIsSpace );
    
    group->FormattedNumber( index, index );
    AssertTrueL( ETrue, KFormattedNumber );
    
    group->FormattedNumber();
    AssertTrueL( ETrue, KFormattedNumberOverLoad );
    
    group->ReverseFormattedNumber( index, index );
    AssertTrueL( ETrue, KReverseFormattedNumber );
    
    group->ReverseFormattedNumber();
    AssertTrueL( ETrue, KReverseFormattedNumberOverLoad );
    
    group->Selection( index, index );
    AssertTrueL( ETrue, KIsSpace );
    
    group->UnFormattedNumber( index, index );
    AssertTrueL( ETrue, KSelection );
    
    group->UnFormattedNumber();
    AssertTrueL( ETrue, KUnFormattedNumber );
    
    group->IsCharacterInsertedByNumberGrouping( index );
    AssertTrueL( ETrue, KIsCharacterInsertedByNumberGrouping );
    
    group->IsChangedByGrouping();
    AssertTrueL( ETrue, KIsChangedByGrouping );
    
    CleanupStack::PopAndDestroy( group );
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomJPLangCase::TestGenericParamConsumerL()
// ---------------------------------------------------------------------------
//    
void CBCTestDomJPLangCase::TestGenericParamConsumerL()
    {
    
    _LIT( KAiwGenericParamConsumer, 
        "CAiwGenericParamConsumer::CAiwGenericParamConsumer() invoked" );
    _LIT( KDes, 
        "CAiwGenericParamConsumer::~CAiwGenericParamConsumer() invoked" );
    _LIT( KRestoreL, 
        "CAiwGenericParamConsumer::RestoreL() invoked" );
        
    CEikAppUi* appui = static_cast<CEikAppUi*>( CCoeEnv::Static()->AppUi() );
    CAiwGenericParamConsumerExt* consumer = 
        new ( ELeave ) CAiwGenericParamConsumerExt( *appui->Application() );
    CleanupStack::PushL( consumer );
    AssertNotNullL( consumer, KAiwGenericParamConsumer );
    
    CAiwGenericParamList* list = CAiwGenericParamList::NewL();
    CleanupStack::PushL( list );
    TRAP_IGNORE( consumer->SetOutputParamsL( list ) );

    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CStreamStore* strm = doc->EditStore();
    CStreamDictionary* dict = CStreamDictionary::NewLC();
    TRAP_IGNORE( consumer->RestoreL( *strm, *dict ) );
    AssertTrueL( ETrue, KRestoreL );
     
    CleanupStack::PopAndDestroy( dict );
    CleanupStack::PopAndDestroy( list );
    CleanupStack::PopAndDestroy( consumer );
    AssertTrueL( ETrue, KDes );
    }
 //end of file
