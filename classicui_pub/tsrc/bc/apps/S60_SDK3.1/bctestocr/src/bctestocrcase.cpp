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
* Description:         Implements test bc for ocrl.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestocr.rsg>
#include <AknWaitDialog.h>
#include <avkon.hrh>

#include "bctestocrcase.h"
#include "bctestocrcontainer.h"
#include "bctestocr.hrh"
#include "autotestcommands.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestOCRCase* CBCTestOCRCase::NewL(
    CBCTestOCRContainer* aContainer )
    {
    CBCTestOCRCase* self = new( ELeave ) CBCTestOCRCase(
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
CBCTestOCRCase::CBCTestOCRCase(
    CBCTestOCRContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestOCRCase::~CBCTestOCRCase()
    {   
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY(1),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        KeyOK,
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::RunL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestOCRCmdOutline01:
            {
            TestFunctionsForOCRL();
            break;
            }
         default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::TestFunctionsForOCRL
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::TestFunctionsForOCRL()
    {
    iEngineEnv.iPriority = EPriorityNormal;
    iEngineEnv.iMaxHeapSize = KMinHeapGrowBy * 1200 + 1; 

            
    _LIT( KErrorReport, "The OCREngine is not supported" );

    TRAPD( ERR, iEngine = static_cast<MOCREngineLayoutRecognize*> 
              ( OCREngineFactory::CreateOCREngineL( *this, iEngineEnv, 
              OCREngineFactory::EEngineLayoutRecognize ) ) );
    if( ERR == -1 || ERR == -5 )
        {
        AssertTrueL( ETrue, KErrorReport );
        return;
        }

    _LIT( KMOCREngineLayoutRecognizeEngine , 
        "MOCREngineLayoutRecognize created" );
    AssertNotNullL( iEngine, KMOCREngineLayoutRecognizeEngine );
    
   iEngine2 = static_cast<MOCREngineRecognizeBlock*> 
              ( OCREngineFactory::CreateOCREngineL( *this, iEngineEnv, 
              OCREngineFactory::EEngineRecognizeBlock ) ); 
    _LIT( KMOCREngineRecognizeBlockEngine , 
        "MOCREngineRecognizeBlock created" );
    AssertNotNullL( iEngine2, KMOCREngineRecognizeBlockEngine );                 
    
    OCREngineFactory::ReleaseOCREngine( iEngine );
    iEngine = NULL;
    _LIT( KMOCREngineLayoutRecognizeReleaseOCREngine , 
        "OCREngineFactory's ReleaseOCREngine invoked" );
    AssertTrueL( ETrue, KMOCREngineLayoutRecognizeReleaseOCREngine );    
    if(iEngine2)
        {
        OCREngineFactory::ReleaseOCREngine( iEngine2 );
        iEngine2 = NULL;
        }  
    _LIT( KMOCREngineRecognizeBlockReleaseOCREngine , 
        "OCREngineFactory's ReleaseOCREngine invoked again" );
    AssertTrueL( ETrue, KMOCREngineRecognizeBlockReleaseOCREngine );             
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::RecognizeComplete
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::RecognizeComplete( 
                               TInt /*aError*/, 
                               const TOCRTextRgnInfo* /*aBlock*/, 
                               const TInt /*aBlockCount*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::RecognizeBlockComplete
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::RecognizeBlockComplete( 
                               TInt /*aError*/, 
                               const TOCRTextRgnInfo* /*aBlock*/, 
                               const TInt /*aBlockCount*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::RecognizeSpecialRegionComplete
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::RecognizeSpecialRegionComplete( 
                               TInt /*aError*/, 
                               const TOCRTextRgnInfo* /*aBlock*/, 
                               const TInt /*aBlockCount*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::RecognizeProcess
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::RecognizeProcess( const TUint /*aPercent*/ )
    {    
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::LayoutComplete
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::LayoutComplete( 
                               TInt /*aError*/, 
                               const TOCRBlockInfo* /*aBlock*/, 
                               const TInt /*aBlockCount*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::DialogDismissedL
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::DialogDismissedL ( TInt /*aButtonId*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::DoRecgonizeBlock
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::DoRecgonizeBlock()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRCase::DoRecgonizeSpecialRegion
// ---------------------------------------------------------------------------
//
void CBCTestOCRCase::DoRecgonizeSpecialRegion()
    { 
    }    
    


    





    
   

    
