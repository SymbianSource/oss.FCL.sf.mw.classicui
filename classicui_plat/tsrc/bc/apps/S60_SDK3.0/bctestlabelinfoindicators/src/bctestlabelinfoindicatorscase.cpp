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
* Description:         Implements test bc for labelinfoindicators.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestlabelinfoindicators.rsg>
#include <eikfnlab.h>                       // CEikFileNameLabel
#include <eiklabel.h>                       // CEikLabel
#include <eikenv.h>                         // CEikonEnv
#include <barsread.h>                       // TResourceRead
#include <s32mem.h>                         // RBufWriteStream
#include <aknindicatorcontainer.h>          // CAknIndicatorContainer
#include <avkon.hrh>  
#include <akninfopopupnotecontroller.h>     // CAknInfoPopupNoteController
#include <gulalign.h>                       // TGulAlignmentValue
#include <aknsconstants.h>                  // KAknsMessageSkinChange
#include <akndef.h>                         // KEikDynamicLayoutVariantSwitch
#include <aknpictographinterface.h>         // CAknPictographInterface
#include <e32debug.h>

#include "bctestlabelinfoindicatorscase.h"
#include "bctestsubeiklabel.h"
#include "bctestsubaknindicator.h"
#include "bctestsubakninfopopupnoteobserver.h"
#include "bctestsubaknpictographanimatorcallback.h"
#include "bctestsubeikfilenamelabel.h"
#include "bctestlabelinfoindicatorscase.h"
#include "bctestlabelinfoindicatorscontainer.h"
#include "bctestlabelinfoindicators.hrh"
#include "autotestcommands.h"

// Constant for CEikFileNameLabel
_LIT( KEFNLEikFileNameLabel, "EikFileNameLabel created" );
_LIT( KEFNLConstructL, "Invoke CEikFileNameLabel's ConstructL()" );
_LIT( KEFNLGetColorUseListL, 
    "Invoke CEikFileNameLabel's GetColorUseListL()" );
_LIT( KEFNLHandlePointerEventL, 
    "Invoke CEikFileNameLabel's HandlePointerEventL()" );
_LIT( KEFNLHandleResourceChange, 
    "Invoke CEikFileNameLabel's HandleResourceChange()" );
_LIT( KEFNLMinimumSize, "Invoke CEikFileNameLabel's MinimumSize()" );
_LIT( KEFNLUpdateL, "Invoke CEikFileNameLabel's UpdateL()" );
_LIT( KEFNLDraw, "Invoke CEikFileNameLabel's Draw()" );

// Constant for CEikLabel
_LIT( KELEikLabel, "EikLabel created" );
_LIT( KELSetFont, "Invoke CEikFileNameLabel's SetFont()" );
_LIT( KELSetTextL, "Invoke CEikFileNameLabel's SetTextL()" );
_LIT( KELText, "This is eik label" );
_LIT( KELCalcMinimumSize, 
    "Invoke CEikFileNameLabel's CalcMinimumSize()" );
_LIT( KELEnablePictographsL, 
    "Invoke CEikFileNameLabel's EnablePictographsL()" );
_LIT( KELBufferReserveLength, 
    "Invoke CEikFileNameLabel's BufferReserveLength()" );
_LIT( KELCropText, "Invoke CEikFileNameLabel's CropText()" );
_LIT( KELDisablePictographs, 
    "Invoke CEikFileNameLabel's DisablePictographs()" );
_LIT( KELGetColorUseListL, 
    "Invoke CEikLabel's GetColorUseListL()" );
_LIT( KELHandlePointerEventL, 
    "Invoke CEikLabel's HandlePointerEventL()" );
_LIT( KELHandleResourceChange, 
    "Invoke CEikLabel's HandleResourceChange()" );
_LIT( KELMinimumSize, "Invoke CEikLabel's MinimumSize()" );
_LIT( KELPixelGapBetweenLines, 
    "Invoke CEikLabel's PixelGapBetweenLines()" );
_LIT( KELSetPixelGapBetweenLines, 
    "Invoke CEikLabel's SetPixelGapBetweenLines()" );
_LIT( KELLogicalToVisualConversionUsed, 
    "Invoke CEikLabel's LogicalToVisualConversionUsed()" );
_LIT( KELSetBrushStyle, 
    "Invoke CEikLabel's SetBrushStyle()" );
_LIT( KELSetBrushStyleFromContext, 
    "Invoke CEikLabel's SetBrushStyleFromContext()" );
_LIT( KELSetBufferReserveLengthL, 
    "Invoke CEikLabel's SetBufferReserveLengthL()" );
_LIT( KELSetEmphasis, "Invoke CEikLabel's SetEmphasis()" );
_LIT( KELSetLabelAlignment, 
    "Invoke CEikLabel's SetLabelAlignment()" );
_LIT( KELSetStrikethrough, 
    "Invoke CEikLabel's SetStrikethrough()" );
_LIT( KELSetUnderlining, 
    "Invoke CEikLabel's SetUnderlining()" );
_LIT( KELUseLogicalToVisualConversion, 
    "Invoke CEikLabel's UseLogicalToVisualConversion()" );
_LIT( KELConstructFromResourceL, 
    "Invoke CEikLabel's ConstructFromResourceL()" );
_LIT( KELWriteInternalStateL, 
    "Invoke CEikLabel's WriteInternalStateL()" );
_LIT( KELDraw, "Invoke CEikLabel's Draw()" );

// Constant for CAknIndicatorContainer
_LIT( KAICAknIndicatorContainer, "CAknIndicatorContainer created" );
_LIT( KAICConstruct, 
    "Invoke CAknIndicatorContainer's ConstructL()" );
_LIT( KAICSetIncallBubbleFlags, 
    "Invoke CAknIndicatorContainer's SetIncallBubbleFlags()" );
_LIT( KAICAknIndicatorContainerOver, 
    "CAknIndicatorContainer created again" );
_LIT( KAICConstructFromResourceL, 
    "Invoke CAknIndicatorContainer's ConstructFromResourceL()" );
_LIT( KAICHandlePointerEventL, 
    "Invoke CAknIndicatorContainer's HandlePointerEventL()" );
_LIT( KAICHandleStatusPaneSizeChange, 
    "Invoke CAknIndicatorContainer's HandleStatusPaneSizeChange()" );
_LIT( KAICIndicatorContext, 
    "Invoke CAknIndicatorContainer's IndicatorContext()" );
_LIT( KAICSetIndicatorState, 
    "Invoke CAknIndicatorContainer's SetIndicatorState()" );
_LIT( KAICIndicatorState, 
    "Invoke CAknIndicatorContainer's IndicatorState()" );
_LIT( KAICSetIncallBubbleAllowedInIdle, 
    "Invoke CAknIndicatorContainer's SetIncallBubbleAllowedInIdle()" );
_LIT( KAICSetIncallBubbleAllowedInUsual, 
    "Invoke CAknIndicatorContainer's SetIncallBubbleAllowedInUsual()" );
_LIT( KAICSetIndicatorValue, 
    "Invoke CAknIndicatorContainer's SetIndicatorValue()" );
_LIT( KAICString, "This is indicator" );
_LIT( KAICSetIndicatorValueL, 
    "Invoke CAknIndicatorContainer's SetIndicatorValueL()" );
_LIT( KAICSetIndicatorObserver, 
    "Invoke CAknIndicatorContainer's SetIndicatorObserver()" );
_LIT( KAICCountComponentControls, 
    "Invoke CAknIndicatorContainer's CountComponentControls()" );
_LIT( KAICHandleResourceChange, 
    "Invoke CAknIndicatorContainer's HandleResourceChange()" );
_LIT( KAICPositionChanged, 
    "Invoke CAknIndicatorContainer's PositionChanged()" );
_LIT( KAICSizeChanged, 
    "Invoke CAknIndicatorContainer's SizeChanged()" );

// Constant for CAknInfoPopupNoteController
_LIT( KAIPNCCAknInfoPopupNoteController, 
    "CAknInfoPopupNoteController created" );
_LIT( KAIPNCText, "This is infopopupnote" );
_LIT( KAIPNCSetTextL, "Invoke CAknIndicatorContainer's SetTextL()" );
_LIT( KAIPNCShowInfoPopupNote, 
    "Invoke CAknIndicatorContainer's ShowInfoPopupNote()" );
_LIT( KAIPNCHideInfoPopupNote, 
    "Invoke CAknIndicatorContainer's HideInfoPopupNote()" );
_LIT( KAIPNCRestoreDefaultPosition, 
    "Invoke CAknIndicatorContainer's RestoreDefaultPosition()" );
_LIT( KAIPNCSetPositionAndAlignment, 
    "Invoke CAknIndicatorContainer's SetPositionAndAlignment()" );
_LIT( KAIPNCSetPositionByHighlight, 
    "Invoke CAknIndicatorContainer's SetPositionByHighlight()" );
_LIT( KAIPNCSetTooltipModeL, 
    "Invoke CAknIndicatorContainer's SetTooltipModeL()" );
_LIT( KAIPNCSetTimeDelayBeforeShow, 
    "Invoke CAknIndicatorContainer's SetTimeDelayBeforeShow()" );
_LIT( KAIPNCSetTimePopupInView, 
    "Invoke CAknIndicatorContainer's SetTimePopupInView()" );
_LIT( KAIPNCAddObserverL, 
    "Invoke CAknIndicatorContainer's AddObserverL()" );
_LIT( KAIPNCRemoveObserver, 
    "Invoke CAknIndicatorContainer's RemoveObserver()" );
    
const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFour = 4;
const TInt KFive = 5;
const TInt KTen = 10;
const TInt KFifty = 50;
const TInt KTwoHundred = 200;
const TInt KTenThousand = 10000;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsCase* CBCTestLabelInfoIndicatorsCase::NewL(
    CBCTestLabelInfoIndicatorsContainer* aContainer )
    {
    CBCTestLabelInfoIndicatorsCase* self = new( ELeave ) 
        CBCTestLabelInfoIndicatorsCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsCase::CBCTestLabelInfoIndicatorsCase(
    CBCTestLabelInfoIndicatorsContainer* aContainer ) 
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsCase::~CBCTestLabelInfoIndicatorsCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::ConstructL()
    {
    iEikEnv = static_cast<CEikonEnv*> ( iContainer->GetCoeEnv() );
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY( KOne ),  // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        KeyOK,
        KeyOK,

        //outline2
        LeftCBA,
        Down,
        KeyOK,
        KeyOK,
        
        //outline3
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        KeyOK,

        //outline4
        LeftCBA,
        REP( Down, KThree ),
        KeyOK,
        KeyOK       
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestLabelInfoIndicatorsCmdOutline01 ) 
        || ( aCmd > EBCTestLabelInfoIndicatorsCmdOutline04 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestLabelInfoIndicatorsCmdOutline01:
            TestFunctionsForFileNameLabelL();
            break;
        case EBCTestLabelInfoIndicatorsCmdOutline02:
            TestFunctionsForEikLabelL();
            break;
        case EBCTestLabelInfoIndicatorsCmdOutline03:
            TestFunctionsForIndicatorsL();
            break;
        case EBCTestLabelInfoIndicatorsCmdOutline04:
            TestFunctionsForInfoPopupNoteL();
            break;            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::TestFunctionsForFileNameLabelL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::TestFunctionsForFileNameLabelL()
    {
    CEikFileNameLabel* filenameLabel = new( ELeave ) CEikFileNameLabel;
    CleanupStack::PushL( filenameLabel ); 
    AssertNotNullL( filenameLabel, KEFNLEikFileNameLabel );
    
    // Invoke CEikFileNameLabel's ConstructL()
    filenameLabel->ConstructL();
    AssertTrueL( ETrue, KEFNLConstructL );
    
    // Invoke CEikFileNameLabel's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    filenameLabel->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KEFNLGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    // Invoke CEikFileNameLabel's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    filenameLabel->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KEFNLHandlePointerEventL );    
    
    // Invoke CEikFileNameLabel's HandleResourceChange()  
    filenameLabel->HandleResourceChange( KAknsMessageSkinChange );
    filenameLabel->HandleResourceChange( KEikDynamicLayoutVariantSwitch );    
    AssertTrueL( ETrue, KEFNLHandleResourceChange );  
    
    // Invoke CEikFileNameLabel's MinimumSize()  
    filenameLabel->MinimumSize();
    AssertTrueL( ETrue, KEFNLMinimumSize ); 
    
    // Invoke CEikFileNameLabel's UpdateL()  
    filenameLabel->UpdateL();
    AssertTrueL( ETrue, KEFNLUpdateL );    
     
    // Invoke CEikFileNameLabel's Draw()  
    CBCTestSubEikFileNameLabel* subFilenamelabel = 
        static_cast<CBCTestSubEikFileNameLabel*> ( filenameLabel );
    subFilenamelabel->DrawNow();
    AssertTrueL( ETrue, KEFNLDraw ); 
    
    CleanupStack::PopAndDestroy( filenameLabel );     
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::TestFunctionsForEikLabelL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::TestFunctionsForEikLabelL()
    {
    CEikLabel* eikLabel = new(ELeave) CEikLabel;
    CleanupStack::PushL( eikLabel ); 
    AssertNotNullL( eikLabel, KELEikLabel );

	// Invoke CEikLabel's SetFont()
	eikLabel->SetFont( iEikEnv->LegendFont() );
    AssertTrueL( ETrue, KELSetFont );
	
	// Invoke CEikLabel's SetTextL()
	eikLabel->SetTextL( TPtrC() );
    AssertTrueL( ETrue, KELSetTextL );
    
	// Invoke CEikLabel's CalcMinimumSize()
	TPtrC ptr( KELText );
	eikLabel->CalcMinimumSize( ptr );
    AssertTrueL( ETrue, KELCalcMinimumSize );
    
	// Invoke CEikLabel's EnablePictographsL()
	TBCTestSubAknPictographAnimatorCallBack subCallBack;
	CAknPictographInterface* interface = 
	    CAknPictographInterface::NewL( *iContainer, subCallBack );
	CleanupStack::PushL( interface );
	eikLabel->EnablePictographsL( *interface );
    AssertTrueL( ETrue, KELEnablePictographsL );
    CleanupStack::PopAndDestroy( interface );  
        
	// Invoke CEikLabel's BufferReserveLength()
	eikLabel->BufferReserveLength();
    AssertTrueL( ETrue, KELBufferReserveLength );
    
	// Invoke CEikLabel's CropText()
	eikLabel->CropText();
    AssertTrueL( ETrue, KELCropText );
    
	// Invoke CEikLabel's DisablePictographs()
	eikLabel->DisablePictographs();
    AssertTrueL( ETrue, KELDisablePictographs ); 
    
    // Invoke CEikLabel's GetColorUseListL()
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KFour );
    CleanupStack::PushL( colorUseList );
    eikLabel->GetColorUseListL( *colorUseList );
    AssertTrueL( ETrue, KELGetColorUseListL );
    colorUseList->Reset();
    CleanupStack::PopAndDestroy( colorUseList );
    
    // Invoke CEikLabel's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    eikLabel->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KELHandlePointerEventL );    
    
    // Invoke CEikLabel's HandleResourceChange()  
    eikLabel->HandleResourceChange( KAknsMessageSkinChange );
    AssertTrueL( ETrue, KELHandleResourceChange ); 
    
    // Invoke CEikLabel's MinimumSize()  
    eikLabel->MinimumSize();
    AssertTrueL( ETrue, KELMinimumSize ); 
    
    // Invoke CEikLabel's PixelGapBetweenLines()  
    TInt pixelGap = eikLabel->PixelGapBetweenLines();
    AssertTrueL( ETrue, KELPixelGapBetweenLines ); 
    
    // Invoke CEikLabel's SetPixelGapBetweenLines()  
    eikLabel->SetPixelGapBetweenLines( pixelGap );
    AssertTrueL( ETrue, KELSetPixelGapBetweenLines );
    
    // Invoke CEikLabel's LogicalToVisualConversionUsed()  
    eikLabel->LogicalToVisualConversionUsed();
    AssertTrueL( ETrue, KELLogicalToVisualConversionUsed );
    
    // Invoke CEikLabel's SetBrushStyle()  
    eikLabel->SetBrushStyle( CWindowGc::ESolidBrush );
    AssertTrueL( ETrue, KELSetBrushStyle );

    // Invoke CEikLabel's SetBrushStyleFromContext()  
    eikLabel->SetBrushStyleFromContext();
    AssertTrueL( ETrue, KELSetBrushStyleFromContext );
    
    // Invoke CEikLabel's SetBufferReserveLengthL()  
    eikLabel->SetBufferReserveLengthL( KTen );
    AssertTrueL( ETrue, KELSetBufferReserveLengthL );
    
    // Invoke CEikLabel's SetEmphasis()  
    eikLabel->SetEmphasis( CEikLabel::EFullEmphasis );
    AssertTrueL( ETrue, KELSetEmphasis );
    
    // Invoke CEikLabel's SetLabelAlignment()  
    eikLabel->SetLabelAlignment( KZero );
    AssertTrueL( ETrue, KELSetLabelAlignment );
    
    // Invoke CEikLabel's SetStrikethrough()  
    eikLabel->SetStrikethrough( ETrue );
    AssertTrueL( ETrue, KELSetStrikethrough );
    
    // Invoke CEikLabel's SetUnderlining()  
    eikLabel->SetUnderlining( ETrue );
    AssertTrueL( ETrue, KELSetUnderlining );
    
    // Invoke CEikLabel's UseLogicalToVisualConversion()  
    eikLabel->UseLogicalToVisualConversion( ETrue );
    AssertTrueL( ETrue, KELUseLogicalToVisualConversion );
        	
    CleanupStack::PopAndDestroy( eikLabel );     
    eikLabel = NULL;
    
    eikLabel = new(ELeave) CEikLabel;
    CleanupStack::PushL( eikLabel ); 
    
    // Invoke CEikLabel's ConstructFromResourceL()  
    TResourceReader reader;
    iEikEnv->CreateResourceReaderLC( 
        reader, R_BCTESTLABELINFOINDICATORS_LABEL );
    eikLabel->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KELConstructFromResourceL );  
    CleanupStack::PopAndDestroy(); //reader 
    
    CBCTestSubEikLabel* subEikLabel = 
        static_cast<CBCTestSubEikLabel*> ( eikLabel );
        
    CBufFlat* buf = CBufFlat::NewL( KTwoHundred );
    CleanupStack::PushL( buf );
    RBufWriteStream stream;
    stream.Open( *buf );
    subEikLabel->WriteInternalStateL( stream );
    AssertTrueL( ETrue, KELWriteInternalStateL ); 
    stream.Close();
    CleanupStack::PopAndDestroy( buf );
    
    subEikLabel->DrawNow();
    AssertTrueL( ETrue, KELDraw );    
        
    CleanupStack::PopAndDestroy( eikLabel );
    }    
    
// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::TestFunctionsForIndicatorsL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::TestFunctionsForIndicatorsL()
    {
    CAknIndicatorContainer* indicator = 
        new( ELeave ) CAknIndicatorContainer();
    CleanupStack::PushL( indicator ); 
    AssertNotNullL( indicator, KAICAknIndicatorContainer );    

    // Invoke CAknIndicatorContainer's ConstructL()  
    indicator->ConstructL();
    AssertTrueL( ETrue, KAICConstruct ); 
    
    // Invoke CAknIndicatorContainer's SetIncallBubbleFlags()  
    indicator->SetIncallBubbleFlags( EAknStatusBubbleVisible );
    AssertTrueL( ETrue, KAICSetIncallBubbleFlags );  
    
    CBCTestSubAknIndicator* subIndicator =
        static_cast<CBCTestSubAknIndicator*> ( indicator );
            
    // Invoke CAknIndicatorContainer's HandleResourceChange()  
    subIndicator->HandleResourceChange( KEikColorResourceChange );
    subIndicator->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    subIndicator->HandleResourceChange( KEikMessageFadeAllWindows );
    AssertTrueL( ETrue, KAICHandleResourceChange );       
    
    CleanupStack::PopAndDestroy( indicator );
    indicator = NULL;
    
    indicator = new( ELeave ) CAknIndicatorContainer( 
        CAknIndicatorContainer::EQueryEditorIndicators );
    CleanupStack::PushL( indicator );
    AssertNotNullL( indicator, KAICAknIndicatorContainerOver );      
    
    // Invoke CAknIndicatorContainer's ConstructFromResourceL() & ConstructL()  
    TResourceReader reader;
    iEikEnv->CreateResourceReaderLC( 
        reader, R_BCTESTLABELINFOINDICATORS_INDICATOR );
    indicator->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KAICConstructFromResourceL );  
    CleanupStack::PopAndDestroy(); //reader 
    
    // Invoke CAknIndicatorContainer's HandlePointerEventL()  
    TPointerEvent pointEvent;
    pointEvent.iType = TPointerEvent::EButton1Down;  
    indicator->HandlePointerEventL( pointEvent );
    AssertTrueL( ETrue, KAICHandlePointerEventL );  
    
    // Invoke CAknIndicatorContainer's HandleStatusPaneSizeChange()  
    indicator->HandleStatusPaneSizeChange();
    AssertTrueL( ETrue, KAICHandleStatusPaneSizeChange );  
 
    // Invoke CAknIndicatorContainer's IndicatorContext()  
    indicator->IndicatorContext();
    AssertTrueL( ETrue, KAICIndicatorContext );  
    
    // Invoke CAknIndicatorContainer's SetIndicatorState()  
    indicator->SetIndicatorState( 
        TUid::Uid( EAknNaviPaneEditorIndicatorProgressBar ), 
        EAknIndicatorStateAnimate );
    AssertTrueL( ETrue, KAICSetIndicatorState );  
    
    // Invoke CAknIndicatorContainer's IndicatorState()  
    indicator->IndicatorState( 
        TUid::Uid( EAknNaviPaneEditorIndicatorProgressBar ) );
    AssertTrueL( ETrue, KAICIndicatorState ); 

    // Invoke CAknIndicatorContainer's SetIncallBubbleAllowedInIdle()  
    indicator->SetIncallBubbleAllowedInIdle( ETrue );
    AssertTrueL( ETrue, KAICSetIncallBubbleAllowedInIdle ); 
    
    // Invoke CAknIndicatorContainer's SetIncallBubbleAllowedInUsual()  
    indicator->SetIncallBubbleAllowedInUsual( ETrue );
    AssertTrueL( ETrue, KAICSetIncallBubbleAllowedInUsual );
    
    // Invoke CAknIndicatorContainer's SetIndicatorValue()  
    indicator->SetIndicatorValue( 
        TUid::Uid( EAknNaviPaneEditorIndicatorProgressBar ), KZero, KFive );
    AssertTrueL( ETrue, KAICSetIndicatorValue );
    
    // Invoke CAknIndicatorContainer's SetIndicatorValueL()  
    indicator->SetIndicatorValueL( 
        TUid::Uid( EAknNaviPaneEditorIndicatorMessageLength ), KAICString );
    AssertTrueL( ETrue, KAICSetIndicatorValueL );
        
    // Invoke CAknIndicatorContainer's SetIndicatorObserver()  
    indicator->SetIndicatorObserver( NULL,
        TUid::Uid( EAknNaviPaneEditorIndicatorWaitBar ) );
    AssertTrueL( ETrue, KAICSetIndicatorObserver ); 

    subIndicator =
        static_cast<CBCTestSubAknIndicator*> ( indicator ); 
        
    // Invoke CAknIndicatorContainer's CountComponentControls()  
    subIndicator->CountComponentControls();
    AssertTrueL( ETrue, KAICCountComponentControls );    
    
    // Invoke CAknIndicatorContainer's PositionChanged()  
    subIndicator->PositionChanged();
    AssertTrueL( ETrue, KAICPositionChanged ); 
    
    TPoint p( KZero, KZero );
    TSize s( KTen, KFifty );
    subIndicator->SetExtent( p, s );
    
    // Invoke CAknIndicatorContainer's SizeChanged()  
    subIndicator->SizeChanged();
    AssertTrueL( ETrue, KAICSizeChanged );
        
    // Invoke CAknIndicatorContainer's HandleResourceChange()  
    subIndicator->HandleResourceChange( KEikColorResourceChange );
    subIndicator->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    subIndicator->HandleResourceChange( KEikMessageFadeAllWindows );
    AssertTrueL( ETrue, KAICHandleResourceChange );
         
    CleanupStack::PopAndDestroy( indicator );
    TestFunctionsForIndicatorsOverLoadL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::TestFunctionsForIndicatorsOverLoadL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::TestFunctionsForIndicatorsOverLoadL()
    {
    CAknIndicatorContainer* indicator = 
        new( ELeave ) CAknIndicatorContainer();
    CleanupStack::PushL( indicator );
    AssertNotNullL( indicator, KAICAknIndicatorContainerOver );      
    
    // Invoke CAknIndicatorContainer's ConstructFromResourceL() & ConstructL()  
    TResourceReader reader;
    iEikEnv->CreateResourceReaderLC( 
        reader, R_BCTESTLABELINFOINDICATORS_INDICATOR_PANE );
    indicator->ConstructFromResourceL( reader );
    AssertTrueL( ETrue, KAICConstructFromResourceL );  
    CleanupStack::PopAndDestroy(); //reader 
    
    // Invoke CAknIndicatorContainer's SetIndicatorState()  
    indicator->SetIndicatorState( 
        TUid::Uid( EAknIndicatorEnvelope ), 
        EAknIndicatorStateAnimate );
    AssertTrueL( ETrue, KAICSetIndicatorState );  
    
    // Invoke CAknIndicatorContainer's IndicatorState()  
    indicator->IndicatorState( 
        TUid::Uid( EAknIndicatorEnvelope ) );
    AssertTrueL( ETrue, KAICIndicatorState ); 
    
    // Invoke CAknIndicatorContainer's SetIndicatorValue()  
    indicator->SetIndicatorValue( 
        TUid::Uid( EAknIndicatorEnvelope ), KZero, KFive );
    AssertTrueL( ETrue, KAICSetIndicatorValue );
    
    // Invoke CAknIndicatorContainer's SetIndicatorValueL()  
    indicator->SetIndicatorValueL( 
        TUid::Uid( EAknIndicatorMissedCalls ), KAICString );
    AssertTrueL( ETrue, KAICSetIndicatorValueL );       

    CBCTestSubAknIndicator* subIndicator =
        static_cast<CBCTestSubAknIndicator*> ( indicator ); 
        
    // Invoke CAknIndicatorContainer's CountComponentControls()  
    subIndicator->CountComponentControls();
    AssertTrueL( ETrue, KAICCountComponentControls );
    
    subIndicator->ComponentControl( KThree );
            
    TPoint p( KZero, KZero );
    TSize s( KTen, KFifty );
    subIndicator->SetExtent( p, s );
    
    CleanupStack::PopAndDestroy( indicator );
    }    

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsCase::TestFunctionsForInfoPopupNoteL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsCase::TestFunctionsForInfoPopupNoteL()
    {
    CAknInfoPopupNoteController* infoPopupNote = 
        CAknInfoPopupNoteController::NewL();        
    CleanupStack::PushL( infoPopupNote ); 
    AssertNotNullL( infoPopupNote, KAIPNCCAknInfoPopupNoteController );     

    // Invoke CAknInfoPopupNoteController's SetTextL()  
    infoPopupNote->SetTextL( KAIPNCText );
    AssertTrueL( ETrue, KAIPNCSetTextL ); 

    // Invoke CAknInfoPopupNoteController's ShowInfoPopupNote()  
    infoPopupNote->ShowInfoPopupNote();
    AssertTrueL( ETrue, KAIPNCShowInfoPopupNote ); 

    // Invoke CAknInfoPopupNoteController's HideInfoPopupNote()  
    infoPopupNote->HideInfoPopupNote();
    AssertTrueL( ETrue, KAIPNCHideInfoPopupNote ); 
    
    // Invoke CAknInfoPopupNoteController's RestoreDefaultPosition()  
    infoPopupNote->RestoreDefaultPosition();
    AssertTrueL( ETrue, KAIPNCRestoreDefaultPosition ); 
    
    // Invoke CAknInfoPopupNoteController's SetPositionAndAlignment()  
    TPoint posi( KTen, KTen );
    infoPopupNote->SetPositionAndAlignment( posi, EHLeftVTop );
    AssertTrueL( ETrue, KAIPNCSetPositionAndAlignment );

    // Invoke CAknInfoPopupNoteController's SetPositionByHighlight()  
    TRect rect( KZero, KZero, KFifty, KFifty );
    infoPopupNote->SetPositionByHighlight( rect );
    AssertTrueL( ETrue, KAIPNCSetPositionByHighlight );
    
    // Invoke CAknInfoPopupNoteController's SetTooltipModeL()  
    infoPopupNote->SetTooltipModeL( ETrue );
    AssertTrueL( ETrue, KAIPNCSetTooltipModeL );
    
    // Invoke CAknInfoPopupNoteController's SetTimeDelayBeforeShow()  
    infoPopupNote->SetTimeDelayBeforeShow( KTenThousand );
    AssertTrueL( ETrue, KAIPNCSetTimeDelayBeforeShow );    

    // Invoke CAknInfoPopupNoteController's SetTimePopupInView()  
    infoPopupNote->SetTimePopupInView( KTenThousand );
    AssertTrueL( ETrue, KAIPNCSetTimePopupInView ); 
    
    // Invoke CAknInfoPopupNoteController's AddObserverL()  
    TBCTestSubAknInfoPopupNoteObserver subObserver;
    infoPopupNote->AddObserverL( subObserver );
    AssertTrueL( ETrue, KAIPNCAddObserverL ); 
    
    infoPopupNote->RemoveObserver( subObserver );
    AssertTrueL( ETrue, KAIPNCRemoveObserver ); 
    
    CleanupStack::PopAndDestroy( infoPopupNote );             
    }


    





    
   

    
