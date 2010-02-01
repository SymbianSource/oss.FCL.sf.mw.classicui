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
* Description:  Functions implement
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <barsread.h>
#include <eikcmobs.h>
#include <testdomstylusactivepopup.rsg>

#include "testdomstylusactivepopup.h"

// CONSTANTS
const TInt KBufSize = 64;
_LIT( KTitleName, "title" );
_LIT( KTextName, "content" );

// FORWARD DECLARATIONS
// Observer instance for MEikCommandObserver
class CTestCommandObserver : public CBase, public MEikCommandObserver
    {
    // from MEikCommandObserver, not used
    void ProcessCommandL( TInt /*aCommandId*/ ){};
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestCAknStylActivePopUpContentNewL", CTestDomStylusActivePopup::TestCAknStylActivePopUpContentNewL ),
        ENTRY( "TestCAknStylActivePopUpContentConstructFromResourceL", CTestDomStylusActivePopup::TestCAknStylActivePopUpContentConstructFromResourceL ),
        ENTRY( "TestCAknStylActivePopUpContentSetCommandObserverL", CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetCommandObserverL ),
        ENTRY( "TestCAknStylActivePopUpContentSetContainerWindowLL", CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetContainerWindowLL ),
        ENTRY( "TestCAknStylActivePopUpContentHandleEventL", CTestDomStylusActivePopup::TestCAknStylActivePopUpContentHandleEventL ),
        
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::TestCAknStylActivePopUpContentNewL
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::TestCAknStylActivePopUpContentNewL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBufC<KBufSize> titlebuf( KTitleName );
    TBufC<KBufSize> textbuf( KTextName );
    
    switch ( num )
        {
        case ECaseOne:
            {
            CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                            titlebuf,
                                                            textbuf
                                                            );
            CleanupStack::PushL( content );
            STIF_ASSERT_NOT_NULL( content);
            CleanupStack::PopAndDestroy( content );
            break;
            }
        case ECaseTwo:
            {
            RArray<TAknContentLink> array;
            
            TAknContentLink link = { &textbuf, 1, NULL };
            array.Append( link );
            CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                            titlebuf,
                                                            textbuf,
                                                            array
                                                            );
            CleanupStack::PushL( content );
            STIF_ASSERT_NOT_NULL( content);
            CleanupStack::PopAndDestroy( content );
            break;
            }
        case ECaseThree:
            {
            CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                           R_STYLUS_CONTENT );
            CleanupStack::PushL( content );
            STIF_ASSERT_NOT_NULL( content);
            CleanupStack::PopAndDestroy( content );
            break;
            }
        case ECaseFour:
            {
            TResourceReader reader;
            CEikonEnv::Static()->CreateResourceReaderLC( reader, R_STYLUS_CONTENT );
            CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                            reader );
            CleanupStack::PushL( content );
            STIF_ASSERT_NOT_NULL( content);
            CleanupStack::PopAndDestroy( 2 );
            break;
            }
        default:
            return KErrNotSupported;
        }
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::TestCAknStylActivePopUpContentConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::TestCAknStylActivePopUpContentConstructFromResourceL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    TBufC<KBufSize> titlebuf( KTitleName );
    TBufC<KBufSize> textbuf( KTextName );
    CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                                titlebuf,
                                                                textbuf
                                                                );
    CleanupStack::PushL( content );
    
    switch ( num )
        {
        case ECaseOne:
            {
            
            content->ConstructFromResourceL( R_STYLUS_CONTENT );
            break;
            }
        case ECaseTwo:
            {
            TResourceReader reader;
            CEikonEnv::Static()->CreateResourceReaderLC( reader, R_STYLUS_CONTENT );
            content->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy();
            break;
            }
        default:
            CleanupStack::PopAndDestroy( content );
            return KErrNotSupported;
        }
    CleanupStack::PopAndDestroy( content );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetCommandObserverL
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetCommandObserverL( CStifItemParser& /*aItem*/ )
    {
    TBufC<KBufSize> titlebuf( KTitleName );
    TBufC<KBufSize> textbuf( KTextName );
    CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                                titlebuf,
                                                                textbuf
                                                                );
    CleanupStack::PushL( content );
    content->ConstructFromResourceL( R_STYLUS_CONTENT );
    CTestCommandObserver* ob = new ( ELeave ) CTestCommandObserver;
    CleanupStack::PushL( ob );
    content->SetCommandObserver( *ob );
    CleanupStack::PopAndDestroy( ob );
    CleanupStack::PopAndDestroy( content );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetContainerWindowLL
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::TestCAknStylActivePopUpContentSetContainerWindowLL( CStifItemParser& /*aItem*/ )
    {
    TBufC<KBufSize> titlebuf( KTitleName );
    TBufC<KBufSize> textbuf( KTextName );
    CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                                titlebuf,
                                                                textbuf
                                                                );
    CleanupStack::PushL( content );
    content->ConstructFromResourceL( R_STYLUS_CONTENT );
    content->SetContainerWindowL( *iContainer );

    CleanupStack::PopAndDestroy( content );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::TestCAknStylActivePopUpContentHandleEventL
// -----------------------------------------------------------------------------
//
TInt CTestDomStylusActivePopup::TestCAknStylActivePopUpContentHandleEventL( CStifItemParser& /*aItem*/ )
    {
    TBufC<KBufSize> titlebuf( KTitleName );
    TBufC<KBufSize> textbuf( KTextName );
    CAknStylusActivatedPopUpContent* content = CAknStylusActivatedPopUpContent::NewL(
                                                                titlebuf,
                                                                textbuf
                                                                );
    CleanupStack::PushL( content );
    content->ConstructFromResourceL( R_STYLUS_CONTENT );
    content->SetContainerWindowL( *iContainer );
    content->HandleResourceChange( 0 );
    content->HandleControlEventL( iContainer, MCoeControlObserver::EEventStateChanged );
    CleanupStack::PopAndDestroy( content );
    
    return KErrNone;
    }

// End of file


