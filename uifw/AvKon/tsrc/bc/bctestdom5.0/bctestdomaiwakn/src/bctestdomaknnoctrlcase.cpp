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
* Description:  test case
*
*/


#include <coecntrl.h>
#include <aknenv.h> 
#include <aknconsts.h>
#include <bctestdomaiwakn.rsg>
#include <ecom.h>
#include <finditemmenu.rsg>
#include <aknkeyrotator.h>      // test APIs in aknkeyrotator.h
#include <aknlib.h>             // test APIs in aknlib.h
#include <aknlinebreaker.h>     // test APIs in AknLineBreaker.h
#include <aknlaunchappservice.h> // test APIs in AknLaunchAppService.h
#include <aknjapanesereading.h> // test APIs in aknjapanesereading.h
#include <ptiengine.h>          
#include <akndateformatutils.h>   // test APIs in akndateformatutils.h
#include <aknedformaccessor.h>  // test APIs in aknedformaccessor.h
#include <aknfontidlayoutfont.h>  
#include <aknextendedinputcapabilities.h>  
#include <aknecs.h> // test APIs in aknecs.h
#include <AknSgcc.h> // for indirectly testing APIs in AknLayoutConfig.h

#include "bctestdomaknnoctrlcase.h" 
#include "bctestdomaiwakncontainer.h" 
#include "bctestdomaiwakn.hrh"
#include "bctestdomaiwaknview.h"
#include "bctestdomaknecsdetector.h"// test APIs in aknecs.h
#include "bctestdomaiwaknapp.h"   // for test APIs in AknLaunchAppService.h
#include "bctestdomaknanimview.h"  // for testing APIs in aknanimview.h   
#include "bctestdomakncharmap.h" // test APIs in akncharmap.h
#include "bctestdomaknbatterypane.h" 
#include "bctestdomaknanimdata.h" 



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknNoCtrlCase* CBCTestDomAknNoCtrlCase::NewL( 
    CBCTestDomAiwAknContainer*  aContainer )
    {
    CBCTestDomAknNoCtrlCase* self = 
        new( ELeave ) CBCTestDomAknNoCtrlCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknNoCtrlCase::CBCTestDomAknNoCtrlCase( 
    CBCTestDomAiwAknContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknNoCtrlCase::~CBCTestDomAknNoCtrlCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknNoCtrlCase::ConstructL()
    { 
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknNoCtrlCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), 
              //  EBCTestDomCmdOutline2
              LeftCBA,REP( Down, 1 ),LeftCBA, 
              
              TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomAknNoCtrlCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestDomCmdOutline2 )
        {
        return;
        }        
        
    switch ( aCmd )  
        {
        case EBCTestDomCmdOutline2: 
            {        
               
            TestAknDateFormatUtils(); //Not Ctrl              
            TestAknEcsDetector();    //Not Ctrl              
            TestAknEdwinFormAccessor(); //Not Ctrl   
            
            TestAknExtendedInputCapabilities(); //Not Ctrl               
            TestAknFontIdLayoutFont();  //Not Ctrl              
               
               
            TestAknJapaneseReading();//Not Ctrl
            TestAknKeyRotator();   //Not Ctrl 
            TestAknLaunchAppService();//Not Ctrl 
            TestAknLayoutConfig();  //Not Ctrl         
            TestCAknLibrary();      //Not Ctrl  
            TestTAknLineBreaker();//Not Ctrl    
              
            }
            break;                                         
        default:            
            break;
        }
    }

// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknNoCtrlCase::ProcessCommandL(TInt /*aCommandId*/) 
    {    
    }
    
// ---------------------------------------------------------------------------
// From class MEikMenuObserver.
// ---------------------------------------------------------------------------
//
void CBCTestDomAknNoCtrlCase::SetEmphasis(
    CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
    {    
    }    
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknDateFormatUtils()
// test APIs in akndateformatutils.h, which are all static fucntions.                         
// ---------------------------------------------------------------------------
//      
void CBCTestDomAknNoCtrlCase::TestAknDateFormatUtils()    
    {    
    AknDateFormatUtils::MapSymbianDateFormatToVisualDateFormat( 
        EDateAmerican,
        NULL );//static fucntion
    _LIT( 
        KDateFormatToVisualDateFormat, 
        "MapSymbianDateFormatToVisualDateFormat() test" );
    AssertTrueL( ETrue, KDateFormatToVisualDateFormat );          
    
    
    AknDateFormatUtils::MapVisualDateFormatToSymbianDateFormat( 
        EVisualDayMonthYear, 
        NULL );//static fucntion
    _LIT( 
        KVisualDateFormatToSymbianDateFormat, 
        "MapVisualDateFormatToSymbianDateFormat() test" );
    AssertTrueL( ETrue, KVisualDateFormatToSymbianDateFormat );          
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknEcsDetector()
// test APIs in aknecs.h
// Test Result: OK
//           
// ---------------------------------------------------------------------------
//      
void CBCTestDomAknNoCtrlCase::TestAknEcsDetector()    
    {
    CAknEcsDetector* ecsDetector = CAknEcsDetector::NewL();
    CleanupStack::PushL( ecsDetector );
    _LIT( 
        KCAknEcsDetectorNewL, 
        "CAknEcsDetector::NewL() test" );
    AssertNotNullL( ecsDetector,  KCAknEcsDetectorNewL );      
    
    
    ecsDetector->SetObserver( NULL ); 
    _LIT( 
        KEcsDetectorSetObserver, 
        "CAknEcsDetector::SetObserver() test" );
    AssertTrueL( ETrue,  KEcsDetectorSetObserver );      
     
    
    TWsEvent wsEvent;
    wsEvent.SetType( EEventNull );
    ecsDetector->HandleWsEventL( wsEvent,NULL );
    _LIT( 
        KEcsDetectorHandleWsEventL, 
        "CAknEcsDetector::HandleWsEventL() test" );
    AssertTrueL( ETrue,  KEcsDetectorHandleWsEventL );      


    ecsDetector->AddChar( EStdKeyYes );
    _LIT( 
        KEcsDetectorAddChar, 
        "CAknEcsDetector::AddChar() test" );
    AssertTrueL( ETrue,  KEcsDetectorAddChar );      


    TBuf<10>    newBuf;  
    ecsDetector->SetBuffer( newBuf );
    _LIT( 
        KEcsDetectorSetBuffer, 
        "CAknEcsDetector::SetBuffer() test" );
    AssertTrueL( ETrue,  KEcsDetectorSetBuffer );      


    ecsDetector->Reset();
    _LIT( 
        KEcsDetectorReset, 
        "CAknEcsDetector::Reset() test" );
    AssertTrueL( ETrue,  KEcsDetectorReset );      


    ecsDetector->State();
    _LIT( 
        KEcsDetectorState, 
        "CAknEcsDetector::State() test" );
    AssertTrueL( ETrue,  KEcsDetectorState );      

    ecsDetector->CurrentMatch();    
    _LIT( 
        KEcsDetectorCurrentMatch, 
        "CAknEcsDetector::CurrentMatch() test" );
    AssertTrueL( ETrue,  KEcsDetectorCurrentMatch );      
    
    
    CleanupStack::PopAndDestroy( ecsDetector ); 
    _LIT( 
        KDelCAknEcsDetector, 
        "~CAknEcsDetector() test" );
    AssertTrueL( ETrue,  KDelCAknEcsDetector );      
    
    
    CBCTestDomAknEcsDetector* derivedEcsDetector = 
        CBCTestDomAknEcsDetector::NewLC(); //CBCTestDomAknEcsDetector
    
    derivedEcsDetector->ConnectToEventSource();
    _LIT( 
        KEcsDetectorConnectToEventSource, 
        "CAknEcsDetector::ConnectToEventSource() test" );
    AssertTrueL( ETrue,  KEcsDetectorConnectToEventSource );      
    
    derivedEcsDetector->ReportEvent( CAknEcsDetector::ENotFullyConstructed );
    _LIT( 
        KEcsDetectorReportEvent, 
        "CAknEcsDetector::ReportEvent() test" );
    AssertTrueL( ETrue,  KEcsDetectorReportEvent );      
    
    derivedEcsDetector->SetState( CAknEcsDetector::ENotFullyConstructed );
    _LIT( 
        KEcsDetectorSetState, 
        "CAknEcsDetector::SetState() test" );
    AssertTrueL( ETrue,  KEcsDetectorSetState );     

    
    derivedEcsDetector->OfferEmergencyCall();
    _LIT( 
        KEcsDetectorOfferEmergencyCall, 
        "CAknEcsDetector::OfferEmergencyCall() test" );
    AssertTrueL( ETrue,  KEcsDetectorOfferEmergencyCall );
          
    
       
    CleanupStack::PopAndDestroy( derivedEcsDetector );     
       
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknEdwinFormAccessor()
// test APIs in aknedformaccessor.h                
// ---------------------------------------------------------------------------
//      
void CBCTestDomAknNoCtrlCase::TestAknEdwinFormAccessor()    
    {
    
    CAknEdwinFormAccessor* formAccessor 
        = new( ELeave ) CAknEdwinFormAccessor( NULL );
    CleanupStack::PushL( formAccessor );  
    _LIT( KCreateFormAccessor, "CAknEdwinFormAccessor() test" );
    AssertNotNullL( formAccessor, KCreateFormAccessor );     

    formAccessor->SetEdwin( NULL );
    _LIT( 
        KSetEdwin, 
        "CAknEdwinFormAccessor::SetEdwin() test" );
    AssertTrueL( ETrue, KSetEdwin );          
 
    
    CleanupStack::PopAndDestroy( formAccessor );  
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknExtendedInputCapabilities()
// test APIs in aknextendedinputcapabilities.h
// Test Result: OK
//           
// ---------------------------------------------------------------------------
//           
void CBCTestDomAknNoCtrlCase::TestAknExtendedInputCapabilities() 
    {    
    CAknExtendedInputCapabilities*  extInputCapabilities = 
        CAknExtendedInputCapabilities::NewL();  
    CleanupStack::PushL( extInputCapabilities );
    _LIT( 
        KCAknExtendedInputCapabilitiesNewL, 
        "CAknExtendedInputCapabilities::NewL() test" );
    AssertNotNullL( extInputCapabilities,  
        KCAknExtendedInputCapabilitiesNewL );      
    
    
    
    CleanupStack::PopAndDestroy( extInputCapabilities );
    _LIT( 
        KDelCAknExtendedInputCapabilities, 
        "~CAknExtendedInputCapabilities() test" );
    AssertTrueL( ETrue, KDelCAknExtendedInputCapabilities );      
    

    extInputCapabilities = 
        CAknExtendedInputCapabilities::NewLC();
    _LIT( 
        KCAknExtendedInputCapabilitiesNewLC, 
        "CAknExtendedInputCapabilities::NewLC() test" );
    AssertNotNullL( extInputCapabilities,  
        KCAknExtendedInputCapabilitiesNewLC );      
    
    extInputCapabilities->ReportEventL( 0, NULL );
    _LIT( 
        KExtInputCapabilitiesReportEventL, 
        "CAknExtendedInputCapabilities::ReportEventL() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesReportEventL );      
    
    
    TUint inputcapabilities = 0;
    extInputCapabilities->SetCapabilities( inputcapabilities  );
    _LIT( 
        KExtInputCapabilitiesSetCapabilities, 
        "CAknExtendedInputCapabilities::SetCapabilities() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesSetCapabilities );      
    
    
    extInputCapabilities->Capabilities();
    _LIT( 
        KExtInputCapabilitiesCapabilities, 
        "CAknExtendedInputCapabilities::Capabilities() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesCapabilities );      
    
    
    extInputCapabilities->SupportsCapabilities( inputcapabilities );
    _LIT( 
        KExtInputCapabilitiesSupportsCapabilities, 
        "CAknExtendedInputCapabilities::SupportsCapabilities() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesSupportsCapabilities );      
    
    TUint mIDPConstraints = 0;
    extInputCapabilities->SetMIDPConstraints( mIDPConstraints );
    _LIT( 
        KExtInputCapabilitiesSetMIDPConstraints, 
        "CAknExtendedInputCapabilities::SetMIDPConstraints() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesSetMIDPConstraints );      
    
    
    extInputCapabilities->MIDPConstrainst();  
    _LIT( 
        KExtInputCapabilitiesMIDPConstrainst, 
        "CAknExtendedInputCapabilities::MIDPConstrainst() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesMIDPConstrainst );      
    
    
    const TInt aEditorType = 0;
    extInputCapabilities->SetEditorType( aEditorType );    
    _LIT( 
        KExtInputCapabilitiesSetEditorType, 
        "CAknExtendedInputCapabilities::SetEditorType() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesSetEditorType );      
 

    extInputCapabilities->EditorType(); 
    _LIT( 
        KExtInputCapabilitiesEditorType, 
        "CAknExtendedInputCapabilities::EditorType() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesEditorType );      
    
    
    extInputCapabilities->RegisterObserver( NULL );
     _LIT( 
        KExtInputCapabilitiesRegisterObserver, 
        "CAknExtendedInputCapabilities::RegisterObserver() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesRegisterObserver );      

    extInputCapabilities->UnregisterObserver( NULL );
    _LIT( 
        KExtInputCapabilitiesUnregisterObserver, 
        "CAknExtendedInputCapabilities::UnregisterObserver() test" );
    AssertTrueL( ETrue,  KExtInputCapabilitiesUnregisterObserver );      
    
    
    CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider* 
        capabilitiesProvider= 
        new( ELeave ) CAknExtendedInputCapabilities
                    ::CAknExtendedInputCapabilitiesProvider();
    CleanupStack::PushL( capabilitiesProvider );        
    
    
    capabilitiesProvider->SetExtendedInputCapabilities( 
        extInputCapabilities );
    _LIT( KSetExtendedInputCapabilities, 
        "CAknExtendedInputCapabilitiesProvider::\
        SetExtendedInputCapabilities() test" );
    AssertTrueL( ETrue,  KSetExtendedInputCapabilities );      
    
    
    capabilitiesProvider->ExtendedInputCapabilities();
    _LIT( 
        KExtendedInputCapabilities, 
        "CAknExtendedInputCapabilitiesProvider::\
        ExtendedInputCapabilities() test" );
    AssertTrueL( ETrue,  KExtendedInputCapabilities );      

    
    capabilitiesProvider->SetMopParent( NULL );
    _LIT( 
        KCapabilitiesProviderSetMopParent, 
        "CAknExtendedInputCapabilitiesProvider::SetMopParent() test" );
    AssertTrueL( ETrue,  KCapabilitiesProviderSetMopParent );      
    
    
    CleanupStack::Pop( capabilitiesProvider );
    delete capabilitiesProvider; //capabilitiesProvider delete
    _LIT( 
        KDelCapabilitiesProvider, 
        "~CAknExtendedInputCapabilitiesProvider() test" );
    AssertTrueL( ETrue,  KDelCapabilitiesProvider );      
    
    
    
    CleanupStack::PopAndDestroy(  extInputCapabilities ); 
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknFontIdLayoutFont()
// test APIs in AknFontIdLayoutFont.h   
// Test Result: OK.            
// ---------------------------------------------------------------------------
//      
void CBCTestDomAknNoCtrlCase::TestAknFontIdLayoutFont()    
    {
    CWsScreenDevice& screenDev = 
        *(CEikonEnv::Static()->ScreenDevice());    
    CAknFontIdLayoutFont* layoutFont = 
        CAknFontIdLayoutFont::NewL( 
            screenDev , 
            EAknLogicalFontSecondaryFont );
    CleanupStack::PushL( layoutFont );
    _LIT( 
        KCAknFontIdLayoutFontNewL, 
        "CAknFontIdLayoutFont::NewL() test" );
    AssertNotNullL( layoutFont, KCAknFontIdLayoutFontNewL );     
    
    
    layoutFont->FontId(); 
    _LIT( 
        KFontId, 
        "CAknFontIdLayoutFont::FontId() test" );
    AssertTrueL( ETrue,  KFontId );   
    
        
    layoutFont->UpdateId( EAknLogicalFontPrimaryFont );
    _LIT( 
        KUpdateId, 
        "CAknFontIdLayoutFont::UpdateId() test" );
    AssertTrueL( ETrue,  KUpdateId );   
    
    CleanupStack::PopAndDestroy( layoutFont );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknJapaneseReading()
// test APIs in aknjapanesereading.h   
// test Result: OK.                            
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknNoCtrlCase::TestAknJapaneseReading()
    {  
    CPtiEngine* ptiEngine = CPtiEngine::NewL();
    CleanupStack::PushL( ptiEngine );
    
    CAknJapaneseReading::CreateL( ptiEngine );
    _LIT( KCreateL, "CAknJapaneseReading::CreateL() test" );
    AssertTrueL( ETrue, KCreateL ); 
    
    
    CAknJapaneseReading::ReadingTextL();
    _LIT( KReadingTextL, "CAknJapaneseReading::CreateL() test" );
    AssertTrueL( ETrue, KReadingTextL ); 
    
    CleanupStack::PopAndDestroy( ptiEngine );     
    }
                                  
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknKeyRotator()
// for test APIs in AknKeyRotator.h, which are all static fucntions. 
// test Result: OK.  
// ---------------------------------------------------------------------------
// 
void CBCTestDomAknNoCtrlCase::TestAknKeyRotator()
    {
 
    CAknKeyRotator*  aknKeyRotator = 
        AknKeyRotatorFactory::CreateAknKeyRotatorL();// static function
    CleanupStack::PushL( aknKeyRotator );    
    _LIT( KCreateAknKeyRotatorL, 
        "AknKeyRotatorFactory::CreateAknKeyRotatorL() test" );
    AssertTrueL( ETrue, KCreateAknKeyRotatorL );
    
    CleanupStack::PopAndDestroy( aknKeyRotator ); 
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknLaunchAppService()
// test APIs in AknLaunchAppService.h, which are all static fucntions.
// test Result: OK.  
// ---------------------------------------------------------------------------
//          
void CBCTestDomAknNoCtrlCase::TestAknLaunchAppService()  
    {
    TUid  appUid = { 0  };
    CAknLaunchAppService* launchAppService = NULL;
     
    TRAPD(err,  
    launchAppService  = 
        CAknLaunchAppService::NewL( // static function
            appUid, 
            NULL, 
            NULL )  
    );
    CleanupStack::PushL( launchAppService  );    
    _LIT( KCAknLaunchAppService, "CAknLaunchAppService::NewL() test" );
    AssertIntL( err,err, KCAknLaunchAppService);
    
    
    CleanupStack::Pop( launchAppService  ); 
    delete launchAppService  ;
    }
 
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestAknLayoutConfig()
// Indirectly test APIs in AknLayoutConfig.h through AknSgcc.h
// Test Result: OK
//              
// ---------------------------------------------------------------------------
//        
void   CBCTestDomAknNoCtrlCase::TestAknLayoutConfig()
    {
    CAknLayoutConfig& layoutConfig = 
        CAknSgcClient::LayoutConfig();    
    
    CAknLayoutConfig::THardwareStateArray hardwareStates = 
        layoutConfig.HardwareStates();//THardwareStateArray,start
    _LIT( 
        KLayoutConfigHardwareStates, 
        "CAknLayoutConfig::HardwareStates() test" );
    AssertTrueL( ETrue,  KLayoutConfigHardwareStates ); 

    TInt stateCount = hardwareStates.Count(); 
    _LIT( 
        KTHardwareStateArrayCount, 
        "THardwareStateArray::Count() test" );
    AssertTrueL( ETrue,  KTHardwareStateArrayCount ); 
    
    if ( 0 < stateCount )
        {
        hardwareStates.At( 0 );
        _LIT( 
            KTHardwareStateArrayAt, 
            "THardwareStateArray::At() test" );
        AssertTrueL( ETrue,  KTHardwareStateArrayAt ); 
        }
    
    TInt stateNumber = 0;
    CAknLayoutConfig::THardwareState  hardwareState = 
        hardwareStates.Find( stateNumber );
    _LIT( 
        KTHardwareStateArrayFind, 
        "THardwareStateArray::Find() test" );
    AssertTrueL( ETrue,  KTHardwareStateArrayFind ); 
    
    
    hardwareState.StateNumber();//THardwareState,start
     _LIT( 
        KTHardwareStateStateNumber, 
        "THardwareState::StateNumber() test" );
    AssertTrueL( ETrue,  KTHardwareStateStateNumber ); 

	hardwareState.KeyCode();
     _LIT( 
        KTHardwareStateKeyCode, 
        "THardwareState::KeyCode() test" );
    AssertTrueL( ETrue,  KTHardwareStateKeyCode ); 

	hardwareState.ScreenMode();
    _LIT( 
        KTHardwareStateScreenMode, 
        "THardwareState::ScreenMode() test" );
    AssertTrueL( ETrue,  KTHardwareStateScreenMode ); 

	hardwareState.AlternateScreenMode();
    _LIT( 
        KTHardwareStateAlternateScreenMode, 
        "THardwareState::AlternateScreenMode() test" );
    AssertTrueL( ETrue,  KTHardwareStateAlternateScreenMode ); 
    


	CAknLayoutConfig::TScreenModeArray screenModes = 
	    layoutConfig.ScreenModes();//TScreenModeArray,start
    _LIT( 
        KLayoutConfigScreenModes, 
        "CAknLayoutConfig::ScreenModes() test" );
    AssertTrueL( ETrue,  KLayoutConfigScreenModes ); 
    
    screenModes.At( 0 ); 
    _LIT( 
        KTScreenModeArrayAt, 
        "TScreenModeArray::At() test" );
    AssertTrueL( ETrue,  KTScreenModeArrayAt ); 
    
    TInt modeNumber = 0;
    CAknLayoutConfig::TScreenMode screenMode =
        screenModes.Find( modeNumber ); 
    _LIT( 
        KTScreenModeArrayFind, 
        "TScreenModeArray::Find() test" );
    AssertTrueL( ETrue,  KTScreenModeArrayFind ); 
     
    screenMode.PixelsTwipsAndRotation() ;//TScreenMode,start
     _LIT( 
        KTScreenModePixelsTwipsAndRotation, 
        "TScreenMode::PixelsTwipsAndRotation() test" );
    AssertTrueL( ETrue,  KTScreenModePixelsTwipsAndRotation ); 

	screenMode.SoftkeyLocation();
     _LIT( 
        KTScreenModeSoftkeyLocation, 
        "TScreenMode::SoftkeyLocation() test" );
    AssertTrueL( ETrue,  KTScreenModeSoftkeyLocation ); 
	
	
    screenMode.ScreenStyleHash();     
     _LIT( 
        KTScreenModeScreenStyleHash, 
        "TScreenMode::ScreenStyleHash() test" );
    AssertTrueL( ETrue,  KTScreenModeScreenStyleHash ); 
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestCAknLibrary()
// for test static APIs in AknLib.h .
// test Result: OK.  
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknNoCtrlCase::TestCAknLibrary()
    {
    CAknLibrary::ResourceFile();// static function
    _LIT( KResourceFile, "CAknLibrary::ResourceFile() test" );
    AssertTrueL( ETrue, KResourceFile );


	CAknLibrary::PrivateResourceFile();// static function
    _LIT( KPrivateResourceFile, 
        "CAknLibrary::PrivateResourceFile() test" );
    AssertTrueL( ETrue, KPrivateResourceFile );

	
	CAknLibrary::ControlFactory();// static function
    _LIT( KControlFactory, 
        "CAknLibrary::ControlFactory() test" );
    AssertTrueL( ETrue, KControlFactory ); 
    }
        
// ---------------------------------------------------------------------------
// CBCTestDomAknNoCtrlCase::TestTAknLineBreaker()
// for test APIs in AknLineBreaker.h  .
// test Result: OK. 
// ---------------------------------------------------------------------------
//  
void CBCTestDomAknNoCtrlCase::TestTAknLineBreaker()
    {
    TUint code =0, rangeStart = 0,rangeEnd = 0,  class0 =0;
    TAknLineBreaker::IsSpecialVariantChar( 
        code, rangeStart, rangeEnd, class0 );// static function
    _LIT( KIsSpecialVariantChar, 
        "TAknLineBreaker::IsSpecialVariantChar() test" );
    AssertTrueL( ETrue, KIsSpecialVariantChar );    
    }

