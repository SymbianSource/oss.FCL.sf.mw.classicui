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
* Description:  Test EIKPROGI.H
*
*/


#include <eikprogi.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <gulbordr.h>
#include <aknsconstants.h>
#include <e32base.h>
#include <s32mem.h>
#include <testsdknotes.rsg>

#include "testsdknotesprogressinfo.h"
#include "testsdknotes.h"

const TInt KLength = 10;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIDeconstructorL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo;
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    CleanupStack::Pop( progress );
    delete progress;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPICEikProgressInfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPICEikProgressInfoL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo;
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPICEikProgressInfoSinfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPICEikProgressInfoSinfoL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    CEikProgressInfo::SInfo sInfoGet = progress->Info();
    STIF_ASSERT_TRUE( sInfo.iFinalValue == sInfoGet.iFinalValue );
    STIF_ASSERT_TRUE( sInfo.iHeight == sInfoGet.iHeight );
    STIF_ASSERT_TRUE( sInfo.iSplitsInBlock == sInfoGet.iSplitsInBlock );
    STIF_ASSERT_TRUE( sInfo.iTextType == sInfoGet.iTextType );
    STIF_ASSERT_TRUE( sInfo.iWidth == sInfoGet.iWidth );

    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIIncrementAndDrawL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIIncrementAndDrawL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_NOTESPROGI );
    progress->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    progress->SetFinalValue( KLength );
    progress->IncrementAndDraw( 1 );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPISetAndDrawL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPISetAndDrawL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    progress->SetFinalValue( KLength );
    TInt length = KLength + 1;
    progress->SetAndDraw( length );
    
    CleanupStack::PopAndDestroy( progress );
    
    progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
        
    progress->SetFinalValue( KLength );
    progress->SetFinalValue( -1 );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIConstructFromResourceL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo;
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_NOTESPROGI );
    progress->ConstructFromResourceL( reader );
    
    CEikProgressInfo::SInfo sInfoGet = progress->Info();
    const TInt KFinalValue = 200;
    const TInt KWidth = 120;
    STIF_ASSERT_TRUE( sInfoGet.iFinalValue == KFinalValue );
    STIF_ASSERT_TRUE( sInfoGet.iHeight == KLength );
    STIF_ASSERT_TRUE( sInfoGet.iSplitsInBlock == 0 );
    STIF_ASSERT_TRUE( sInfoGet.iTextType == 0 );
    STIF_ASSERT_TRUE( sInfoGet.iWidth == KWidth );
    
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPISetLayoutL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPISetLayoutL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    CEikProgressInfo::SLayout sLayout;
    progress->SetLayout( sLayout );
    
    CEikProgressInfo::SLayout sLayoutGet = progress->Layout();
    STIF_ASSERT_TRUE( sLayout.iEmptyColor == sLayoutGet.iEmptyColor );
    STIF_ASSERT_TRUE( sLayout.iEmptyTextColor == sLayoutGet.iEmptyTextColor );
    STIF_ASSERT_TRUE( sLayout.iFillColor == sLayoutGet.iFillColor );
    STIF_ASSERT_TRUE( sLayout.iFillTextColor == sLayoutGet.iFillTextColor );
    STIF_ASSERT_TRUE( sLayout.iFont == sLayoutGet.iFont );
    STIF_ASSERT_TRUE( sLayout.iGapBetweenBlocks == sLayoutGet.iGapBetweenBlocks );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPISetBorderL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPISetBorderL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    TGulBorder gulBorder;
    progress->SetBorder( gulBorder );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPISetFinalValueL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPISetFinalValueL( CStifItemParser& aItem )
    {
    return TestNPIIncrementAndDrawL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIConstructL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    
    progress->ConstructL();
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIInfoL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIInfoL( CStifItemParser& aItem )
    {
    return TestNPICEikProgressInfoSinfoL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPILayoutL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPILayoutL( CStifItemParser& aItem )
    {
    return TestNPISetLayoutL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPICurrentValueL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPICurrentValueL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    TInt currentValue = progress->CurrentValue();
    STIF_ASSERT_EQUALS( currentValue, 0 );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIEvaluateTextL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIEvaluateTextL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    sInfo.iTextType = EEikProgressTextPercentage;
    CTestSDKNotesProgressInfo* progress = CTestSDKNotesProgressInfo::NewLC( sInfo );
    STIF_ASSERT_NOT_NULL( progress );
    
    TBuf<KLength> stackBuf;
    progress->EvaluateText( stackBuf );
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIActivateL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIActivateL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    progress->ActivateL();
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIMinimumSizeL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    TSize size = progress->MinimumSize();
    TPoint point = size.AsPoint();
    STIF_ASSERT_NOT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPISizeChangedL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPISizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    progress->SizeChanged();
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIGetColorUseListL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    CArrayFix <TCoeColorUse>* colorUseList = new( ELeave ) CArrayFix <TCoeColorUse>( ( TBufRep )CBufFlat::NewL, 1 );
    CleanupStack::PushL( colorUseList );
    progress->GetColorUseListL( *colorUseList );
    STIF_ASSERT_NOT_NULL( colorUseList );
    
    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIHandleResourceChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    const TInt KBCTestNoteProgressbarMaxLength = 256;
    progress->HandleResourceChange( KAknsMessageSkinChange );
    progress->HandleResourceChange( KBCTestNoteProgressbarMaxLength );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    CEikProgressInfo* progress = new (ELeave) CEikProgressInfo( sInfo );
    CleanupStack::PushL( progress );
    STIF_ASSERT_NOT_NULL( progress );
    progress->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    progress->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotes::TestNPIWriteInternalStateL
// -----------------------------------------------------------------------------
TInt CTestSDKNotes::TestNPIWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CEikProgressInfo::SInfo sInfo;
    sInfo.iTextType = EEikProgressTextPercentage;
    CTestSDKNotesProgressInfo* progress = CTestSDKNotesProgressInfo::NewLC( sInfo );
    STIF_ASSERT_NOT_NULL( progress );
    
    const TInt size = 2000;
    CBufFlat* buf = CBufFlat::NewL( size );
    STIF_ASSERT_EQUALS( 0, buf->Ptr( 0 ).Length() );
    CleanupStack::PushL( buf );
    
    RBufWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( *buf );
    progress->WriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( &stream );
    CleanupStack::PopAndDestroy( buf );
    CleanupStack::PopAndDestroy( progress );
    
    return KErrNone;
    
    }
