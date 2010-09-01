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
* Description:         Implements test bc for heading pane testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknpopupheadingpane.h>
#include <aknlists.h>
#include <bctestpopups.mbg>
#include <bctestpopups.rsg> 
#include <barsread.h> // TResourceRead

#include "bctestheadingpanecase.h"
#include "bctestpopupscontainer.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h"

// constant
_LIT( KAknPopupList, "PopupList created" );
_LIT( KAknPopupHeadingPane, "Headingpane created" );
_LIT( KHeading, "Heading pane" );
_LIT( KConstructL, "Invoke CAknPopupHeadingPane's ConstructL()" );
_LIT( KMinimumSize, "Invoke CAknPopupHeadingPane's MinimumSize()" );
_LIT( KHandlePointerEventL,
    "Invoke CAknPopupHeadingPane's HandlePointerEventL()" );
_LIT( KSizeChanged, "Invoke CAknPopupHeadingPane's SizeChanged()" );
_LIT( KPrompt, "Invoke CAknPopupHeadingPane's Prompt()" );
_LIT( KPromptText, "Invoke CAknPopupHeadingPane's PromptText()" );
_LIT( KOtherHeading, "Modify Heading" );
_LIT( KSetTextL, "Invoke CAknPopupHeadingPane's SetTextL()" );
_LIT( KSetLayout, "Invoke CAknPopupHeadingPane's SetLayout()" );
_LIT( KSetHeaderImageL,
    "Invoke CAknPopupHeadingPane's SetHeaderImageL()" );
_LIT( KSetSkinFrameId,
    "Invoke CAknPopupHeadingPane's SetSkinFrameId()" );
_LIT( KSetSkinFrameCenterId,
    "Invoke CAknPopupHeadingPane's SetSkinFrameCenterId()" );
_LIT( KSetHeaderAnimationL,
    "Invoke CAknPopupHeadingPane's SetHeaderAnimationL()" );
_LIT( KStartAnimationL,
    "Invoke CAknPopupHeadingPane's StartAnimationL()" );
_LIT( KCancelAnimation,
    "Invoke CAknPopupHeadingPane's CancelAnimation()" );
_LIT( KConstructFromResourceL,
    "Invoke CAknPopupHeadingPane's ConstructFromResourceL()" );
    
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFifteen = 15;
const TInt KTwenty = 20;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestHeadingPaneCase* CBCTestHeadingPaneCase::NewL(
    CBCTestPopupsContainer* aContainer )
    {
    CBCTestHeadingPaneCase* self = new( ELeave ) CBCTestHeadingPaneCase(
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
CBCTestHeadingPaneCase::CBCTestHeadingPaneCase(
    CBCTestPopupsContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestHeadingPaneCase::~CBCTestHeadingPaneCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestHeadingPaneCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestHeadingPaneCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestHeadingPaneCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline7
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        KeyOK,

        //outline8
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        REP( Down, KOne ),
        KeyOK,

        //outline9
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        REP( Down, KTwo ),
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestHeadingPaneCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestHeadingPaneCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestPopupsCmdOutline07 )
        || ( aCmd > EBCTestPopupsCmdOutline09 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestPopupsCmdOutline07:
            TestHeadingPaneL();
            break;
        case EBCTestPopupsCmdOutline08:
            break;
        case EBCTestPopupsCmdOutline09:

            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestHeadingPaneCase::TestHeadingPaneL
// ---------------------------------------------------------------------------
//
void CBCTestHeadingPaneCase::TestHeadingPaneL()
    {
    CEikFormattedCellListBox* listBox =
        new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listBox );

    CAknPopupList* popupList = CAknPopupList::NewL( listBox,
        R_AVKON_SOFTKEYS_SELECT_BACK,
        AknPopupLayouts::EPopupSNotePopupWindow );
    CleanupStack::PushL( popupList );
    AssertNotNullL( popupList, KAknPopupList );

    listBox->ConstructL( popupList, EAknListBoxMenuList );

    CAknPopupHeadingPane* head = new( ELeave ) CAknPopupHeadingPane();
    CleanupStack::PushL( head );
    AssertNotNullL( head, KAknPopupHeadingPane );
    head->SetContainerWindowL( *iContainer );

    TBufC<KFifteen> bufc( KHeading );
    TPtrC ptrc = bufc.Des();
    // Invoke CAknPopupHeadingPane's ConstructL()
    head->ConstructL( ptrc );
    AssertTrueL( ETrue, KConstructL );

    // Invoke CAknPopupHeadingPane's MinimumSize()
    TSize s = head->MinimumSize();
    AssertTrueL( ETrue, KMinimumSize );    

    // Invoke CAknPopupHeadingPane's HandlePointerEventL()
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;
    head->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KHandlePointerEventL );    

    // Invoke CAknPopupHeadingPane's SizeChanged()
    head->SizeChanged();
    AssertTrueL( ETrue, KSizeChanged );

    // Invoke CAknPopupHeadingPane's Prompt()
    head->Prompt();
    AssertTrueL( ETrue, KPrompt );

    // Invoke CAknPopupHeadingPane's PromptText()
    head->PromptText();
    AssertTrueL( ETrue, KPromptText );

    // Invoke CAknPopupHeadingPane's SetTextL()
    TBufC<KTwenty> otherBufc( KOtherHeading );
    TPtrC otherPtrc = otherBufc.Des();
    head->SetTextL( otherPtrc );
    AssertTrueL( ETrue, KSetTextL );

    // Invoke CAknPopupHeadingPane's SetLayout()
    head->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
    AssertTrueL( ETrue, KSetLayout );

    // Invoke CAknPopupHeadingPane's SetHeaderImageL()
    TBuf<KMaxFileName> iconFile;
    iContainer->GetCoeEnv()->ReadResource( iconFile, 
                                           R_BCTESTPOPUPS_ICONFILE );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image ); // image
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;
    AknIconUtils::CreateIconL( bitmap,
                               bitmapM,
                               iconFile,
                               EMbmBctestpopupsTel,
                               EMbmBctestpopupsTelm ); 

    CleanupStack::PushL( bitmap ); // bitmap
    CleanupStack::PushL( bitmapM ); // bitmap mask

    image->SetPictureOwnedExternally( TBool( 0 ) );
    image->SetPicture( bitmap, bitmapM );

    head->SetHeaderImageL( image );
    AssertTrueL( ETrue, KSetHeaderImageL );

    CleanupStack::Pop( bitmapM );  
    CleanupStack::Pop( bitmap );
    CleanupStack::Pop( image );

     // Invoke CAknPopupHeadingPane's SetSkinFrameId()
    TAknsItemID aknsItemID;
    head->SetSkinFrameId( aknsItemID );
    AssertTrueL( ETrue, KSetSkinFrameId );

     // Invoke CAknPopupHeadingPane's SetSkinFrameCenterId()
    head->SetSkinFrameCenterId( aknsItemID );
    AssertTrueL( ETrue, KSetSkinFrameCenterId );    
    
    // Invoke CAknPopupHeadingPane's SetHeaderAnimationL()
    head->SetHeaderAnimationL( R_BCTESTPOPUPS_BITMAP_ANIMATION );
    AssertTrueL( ETrue, KSetHeaderAnimationL );    

    // Invoke CAknPopupHeadingPane's StartAnimationL()
    head->StartAnimationL();
    AssertTrueL( ETrue, KStartAnimationL );

    // Invoke CAknPopupHeadingPane's CancelAnimation()
    head->CancelAnimation();
    AssertTrueL( ETrue, KCancelAnimation );
         
    CleanupStack::PopAndDestroy( head ); 
    head = NULL;

    head = new( ELeave ) CAknPopupHeadingPane();
    CleanupStack::PushL( head );

    // Invoke CAknPopupHeadingPane's ConstructFromResourceL()
    TResourceReader reader;
    iContainer->GetCoeEnv()->CreateResourceReaderLC(
        reader, R_BCTESTPOPUPS_AVKON_HEADING );
    head->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader    

    CleanupStack::PopAndDestroy( head );    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    
    delete image;
    }















