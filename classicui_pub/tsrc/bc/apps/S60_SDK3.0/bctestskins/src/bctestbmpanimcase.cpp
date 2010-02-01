/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <aknsitemdata.h> 

#include "bctestbmpanimcase.h"
#include "bctestskinscontainer.h"
#include "bctestskins.hrh"


struct TAknsBmpAnimFrameInfo
    {
    /**
    * Frame time in milliseconds or -1 if not defined.
    */
    TInt16 iTime;

    /**
    * Frame position X-coordinate.
    */
    TInt16 iPosX;

    /**
    * Frame position Y-coordinate.
    */
    TInt16 iPosY;
    };
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestBmpAnimCase* CBCTestBmpAnimCase::NewL( 
    CBCTestSkinsContainer* aContainer )
    {
    CBCTestBmpAnimCase* self = new( ELeave ) CBCTestBmpAnimCase( 
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
CBCTestBmpAnimCase::CBCTestBmpAnimCase( 
    CBCTestSkinsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestBmpAnimCase::~CBCTestBmpAnimCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestBmpAnimCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestBmpAnimCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestBmpAnimCase::BuildScriptL()
    { 
   const TInt scripts[] =
        {
        DELAY(1),    // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 2),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestBmpAnimCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestBmpAnimCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline3 || aCmd > EBCTestCmdOutline3 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline3:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestBmpAnimCase::TestFunctionL
// ---------------------------------------------------------------------------
//   
void CBCTestBmpAnimCase::TestFunctionL()
    {
    // Test CAknsBmpAnimItemData APIs
    CAknsBmpAnimItemData* itemData = CAknsBmpAnimItemData::NewL();
    CleanupStack::PushL(itemData);
    _LIT( KItemData, "CAknsBmpAnimItemData::NewL" );
    AssertNotNullL( itemData, KItemData );

    // set images then set its frame info    
    const TInt n = 5;
    TAknsItemID ids[n];
    TAknsBmpAnimFrameInfo infos[n];
    for(int i=0; i<n; ++i)
        {
        ids[i].Set(i, i);
        infos[i].iTime = 0;
        infos[i].iPosX = 0;
        infos[i].iPosY = 0;
        }
        
    itemData->SetImagesL(n, ids);
    itemData->SetFrameInfosL(infos);
    _LIT( KSetFrameInfos, "CAknsBmpAnimItemData::SetFrameInfosL() invoked");
    AssertTrueL(ETrue, KSetFrameInfos);
    
    
    itemData->SetFlash( ETrue );
    _LIT( KFlash, "CBCTestBmpAnimCase::Flash" );
    AssertTrueL( itemData->Flash(), KFlash );

    itemData->SetPlayMode( 20 );
    _LIT( KPlayMode, "CBCTestBmpAnimCase::PlayMode" );
    AssertIntL( 20, itemData->PlayMode(), KPlayMode );
    
    itemData->SetFrameInterval( 1000*3 );
    _LIT( KFrmIntvl, "CBCTestBmpAnimCase::FrameInterval" );
    AssertIntL( 1000*3, itemData->FrameInterval(), KFrmIntvl );
 
    itemData->SetLastFrameBackground( ETrue );
    _LIT( KBkgrd, "CBCTestBmpAnimCase::LastFrameBackground" );
    AssertTrueL( itemData->LastFrameBackground(), KBkgrd );
    
    TAny* frameInfo = itemData->FrameInfos();
    _LIT( KFrameInfos, "CBCTestBmpAnimCase::FrameInfos" );
    AssertTrueL( ETrue, KFrameInfos );
    //delete frameInfo; //can not delete, becuase it is owned by itemData
   
    CleanupStack::PopAndDestroy( itemData );
    
    // Test CAknsStringItemData APIs
    CAknsStringItemData* strItemData =  CAknsStringItemData::NewL();
    CleanupStack::PushL( strItemData );
    _LIT( KStrItemData, "CAknsStringItemData::NewL");
    AssertNotNullL( strItemData, KStrItemData );
    
    _LIT( KStr, "A String");
    TBuf<16> str( KStr );   
    strItemData->SetStringL( str );
    _LIT( KSetString, "CAknsStringItemData::SetStringL");
    AssertNotNullL( strItemData, KSetString);

    _LIT( KString, "CAknsStringItemData::String");
    AssertTrueL( ( strItemData->String() == str ), KString );
    CleanupStack::PopAndDestroy( strItemData );
    
    // Test CAknsImageTableItemData APIs
	CAknsImageTableItemData* tableItemData = CAknsImageTableItemData::NewL();  
    CleanupStack::PushL( tableItemData );
    _LIT( KTableItemData, "CAknsImageTableItemData::NewL" );
    AssertNotNullL( tableItemData, KTableItemData );
    
    TAknsItemID* imageArray; 
	imageArray = tableItemData->Images();
	delete [] imageArray;
	imageArray = NULL;
	
    CleanupStack::PopAndDestroy( tableItemData );
   	}
    
