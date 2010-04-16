/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

#include "AknPhoneNumberEditor.h"
#include "AknPhedView.h"

#include <AknUtils.h>
#include <frmtlay.h>
#include <eikenv.h>
#include <barsread.h>
#include <aknedsts.h>
#include <featmgr.h>    
#include <aknextendedinputcapabilities.h>
#include <eikcoctl.rsg>
#include <txtetext.h>

#include <AknTasHook.h>
#include <touchfeedback.h>
#include <aknnotedialog.h>

static const TInt KPlainTextPos = 0;

typedef CArrayFixFlat<CAknPhoneNumberEditor::TFormat> CFormatArray;

NONSHARABLE_CLASS( CAknPhoneNumberEditorExtension ) : public CBase, 
    public MObjectProvider
    {
    public:
        CAknPhoneNumberEditorExtension();
        ~CAknPhoneNumberEditorExtension();
    
    protected:  // from MObjectProvider        
         TTypeUid::Ptr MopSupplyObject( TTypeUid aId );       
    
    public:
        CFormatArray* iFormats;
        CAknExtendedInputCapabilities* iExtendedInputCapabilities;
        TInt iPointPos;
        CAknCcpuSupport* iCcpuSupport; 
        HBufC* iPasteText;       
      };

CAknPhoneNumberEditorExtension::CAknPhoneNumberEditorExtension()
    {
    iFormats = NULL;
    iExtendedInputCapabilities = NULL;
    }


CAknPhoneNumberEditorExtension::~CAknPhoneNumberEditorExtension()
    {
    delete iPasteText;
    delete iFormats;
    delete iExtendedInputCapabilities;    
    delete iCcpuSupport;
    }

// ---------------------------------------------------------
// CAknPhoneNumberEditorExtension::MopSupplyObject
// ---------------------------------------------------------
//
TTypeUid::Ptr CAknPhoneNumberEditorExtension::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CAknExtendedInputCapabilities::ETypeId )
        {
        return aId.MakePtr( iExtendedInputCapabilities );
        }
    
    return TTypeUid::Null();
    }

enum TAknPhedFlags
    {
    ERedrawAll,
    EInlineEditInProgress,
    EFeaturePhoneNumberGrouping
    };

enum TAknPhedControlPanic
    {
    ELeaveInStateChange,
    EIncorrectInlineEditState
    };

void PhedControlPanic( TAknPhedControlPanic aPanic )
    {
    _LIT( KAknPhedControl,"AknPhedControl" );
    User::Panic( KAknPhedControl, aPanic );
    }


EXPORT_C CAknPhoneNumberEditor::TFormat::TFormat()
    {
    Mem::FillZ( this, sizeof( *this ) );
    }

EXPORT_C CAknPhoneNumberEditor::TFormat::TFormat( TResourceReader& aReader )
    {
    Mem::FillZ( this, sizeof( *this ) );

    TInt top = aReader.ReadInt16();
    TInt left = aReader.ReadInt16();
    TInt bottom = aReader.ReadInt16();
    TInt right = aReader.ReadInt16();
    iOuterRect = TRect( TPoint( left, top ), TPoint( right, bottom ) );

    iBorderType = aReader.ReadInt32();
    iNumLines = aReader.ReadInt16();
    iBottomBaselineOffset = aReader.ReadInt16();
    iBaselineSeparation = aReader.ReadInt16();
    iFont = AknLayoutUtils::FontFromId( aReader.ReadInt16() );
    }

EXPORT_C CAknPhoneNumberEditor::TFormat::TFormat( const TRect& aOuterRect, TInt aBorderType, 
    TInt aNumLines, TInt aBottomBaselineOffset, TInt aBaselineSeparation, const CFont* aFont )
    : iOuterRect( aOuterRect ), iBorderType( aBorderType ), iNumLines( aNumLines ), 
      iBottomBaselineOffset( aBottomBaselineOffset ), iBaselineSeparation( aBaselineSeparation ), 
      iFont( aFont )
    {
    }



EXPORT_C CAknPhoneNumberEditor::CAknPhoneNumberEditor()
    {
    iFlags.Set( ERedrawAll );
    AKNTASHOOK_ADD( this, "CAknPhoneNumberEditor" );
    }

EXPORT_C CAknPhoneNumberEditor::~CAknPhoneNumberEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iView;
    delete iModel;
    delete iExtension;
    delete iFepState;
    }

EXPORT_C void CAknPhoneNumberEditor::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt maxChars = aReader.ReadInt16();
    TInt maxLines = aReader.ReadInt16();
    HBufC* truncation = aReader.ReadHBufCL();
    CleanupStack::PushL( truncation );
    TInt formatCount = aReader.ReadInt16();
    ConstructL( maxChars, maxLines, formatCount, *truncation );
    CleanupStack::PopAndDestroy();  // truncation

    for ( TInt ii=0; ii<formatCount; ii++ )
        {
        AddFormat( TFormat(aReader ) );
        }

    SetFormat( 0 );
    
    TUint cap = iExtension->iExtendedInputCapabilities->Capabilities();
    cap |= CAknExtendedInputCapabilities::EInputEditorDisableVKB;
    iExtension->iExtendedInputCapabilities->SetCapabilities( cap );
    
    }

EXPORT_C void CAknPhoneNumberEditor::ConstructL( TInt aMaxChars, 
                                                 TInt aMaxLines, 
                                                 TInt aMaxFormats, 
                                                 const TDesC& aTruncation )
    {
    iExtension = new(ELeave) CAknPhoneNumberEditorExtension();
    iExtension->iFormats = new(ELeave) CFormatArray( 1 );
    iExtension->iFormats->ResizeL( aMaxFormats );
    iModel = CAknPhedModel::NewL( aMaxChars );
    iView = new(ELeave) CAknPhedView( iModel );
    iView->ConstructL( aMaxLines, aTruncation );
    iView->SetWindows( &iEikonEnv->RootWin(), DrawableWindow() );
    iView->SetChangeReceiver( this );
    CreateFepStateL();
    iExtension->iExtendedInputCapabilities = CAknExtendedInputCapabilities::NewL();
    
    TUint cap = iExtension->iExtendedInputCapabilities->Capabilities();
    cap |= CAknExtendedInputCapabilities::EInputEditorDisableVKB;
    iExtension->iExtendedInputCapabilities->SetCapabilities( cap );

    EnableDragEvents();      
    EnableCcpuSupportL( ETrue );
    }

EXPORT_C void CAknPhoneNumberEditor::AddFormat( const TFormat& aFormat )
    {
    iExtension->iFormats->At( iNumFormats++ ) = aFormat;
    }

EXPORT_C TInt CAknPhoneNumberEditor::CountFormats() const
    {
    return iNumFormats;
    }

EXPORT_C CAknPhoneNumberEditor::TFormat& CAknPhoneNumberEditor::Format( TInt aFormatIndex ) const
    {
    return iExtension->iFormats->At( aFormatIndex );
    }

EXPORT_C TInt CAknPhoneNumberEditor::CurrentFormatIndex() const
    {
    return iCurrentFormatIndex;
    }

EXPORT_C TBool CAknPhoneNumberEditor::WouldTextFitInFormat( TInt aFormatIndex ) const
    {
    TFormat& format = Format( aFormatIndex );

    // create a line and see how many times the text takes to fit it.
    TAknPhedViewLine line;
    line.SetModel( iModel );
    line.SetFormat( format.iFont, Border().InnerRect( format.iOuterRect ),
                    format.iBaselineSeparation );

    TInt count = 1;
    line.SetRightPos( 0 );
    if ( line.LeftPos() > 0 )
        {
    while ( line.LeftPos() != iModel->Length() )
        {
        line.SetRightPos( line.LeftPos() );
        line.SetRightLine( &line );
        count++;
        }
        }
    return count <= format.iNumLines;
    }

EXPORT_C void CAknPhoneNumberEditor::SetFormat( TInt aFormatIndex )
    {
    iCurrentFormatIndex = aFormatIndex;
    TFormat& format = Format( aFormatIndex );
    SetBorder( format.iBorderType );
    SetRect( format.iOuterRect );
    }

EXPORT_C TPtrC CAknPhoneNumberEditor::Text( TInt aFrom ) const
    {
    return iModel->UnFormattedText(aFrom);
    }

EXPORT_C void CAknPhoneNumberEditor::SetText( const TDesC& aText )
    {
    iModel->SetText( aText );
    }

void CAknPhoneNumberEditor::DrawChanges()
    {
    // DrawChanges actually draws everything. Flicker is not
    // a problem now.
    DrawDeferred();
    }

EXPORT_C void CAknPhoneNumberEditor::SizeChanged()
    {
    TFormat& format = Format( CurrentFormatIndex() );
    TPoint pt = DrawableWindow()->Position();
    TSize size = DrawableWindow()->Size();
    TRect rect = Rect();
    TInt offset = rect.iBr.iX - ( pt.iX + size.iWidth );   
    if ( offset > 0 )
        {        
        rect.iTl.iX -= offset;
        rect.iBr.iX = pt.iX + size.iWidth;    
        SetRect( rect );
        }     
    iView->SetFormat( format.iNumLines, format.iFont, Border().InnerRect( Rect() ),
        format.iBottomBaselineOffset, format.iBaselineSeparation);
    }

EXPORT_C TKeyResponse CAknPhoneNumberEditor::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                             TEventCode aType )
    {
    if ( aType != EEventKey )
        return EKeyWasNotConsumed;

    TKeyResponse resp = EKeyWasConsumed;

    TInt cursorX = iView->CursorPosition().iX;
    TBool targetPosUsed = EFalse;
    
    // when user inputs digit, the screen should be drawn, otherwise
    // we need to check whether the screen will be drawn by view
    TBool needDraw = EFalse;

    // record cursorline before cursor moves for preventing flicker
    TInt cursorLinePre = iView->CursorLine();

    // record leftpos of current line to help to decide how the 
    // cursor moves between different lines.
    const CAknPhedViewLineArray* lineArray = iView->LineArray();
    TInt leftPosPre = lineArray->At( cursorLinePre ).LeftPos();

    // phone number editor does not respond to shift key.
    // The code is still here because it may need to be turned back on if
    // the phone number editor needs to support selection, cut, copy and paste.
    TBool shift = ( ( aKeyEvent.iModifiers & EModifierShift ) == EModifierShift );
    TBool cousorChanged = EFalse;
    switch(aKeyEvent.iCode)
        {
        case EKeyLeftArrow:
            if (shift)
                iModel->SelectLeft();
            else
                iModel->CursorLeft();
            cousorChanged = ETrue;
            break;

        case EKeyRightArrow:
            if (shift)
                iModel->SelectRight();
            else
                iModel->CursorRight();
            cousorChanged = ETrue;
            break;

        case EKeyUpArrow:
            if ( shift )
                targetPosUsed = iView->SelectUp( TargetCursorPos( cursorX ) );
            else
                targetPosUsed = iView->CursorUp( TargetCursorPos( cursorX ) );
            cousorChanged = ETrue;
            break;

        case EKeyDownArrow:
            if ( shift )
                targetPosUsed = iView->SelectDown( TargetCursorPos( cursorX ) );
            else
                targetPosUsed = iView->CursorDown( TargetCursorPos( cursorX ) );
            cousorChanged = ETrue;
            break;

        case EKeyBackspace:
            iModel->DeleteLeft();
            needDraw = ETrue;
            break;

        default:
            if ( aKeyEvent.iCode < ENonCharacterKeyBase )
                {
                iModel->Insert( TText( aKeyEvent.iCode ) );
                needDraw = ETrue;
                }
            else
                resp = EKeyWasNotConsumed;
            break;
        }
        
    if ( iExtension->iExtendedInputCapabilities )
        {
        iExtension->iExtendedInputCapabilities->ReportEventL( 
            CAknExtendedInputCapabilities::
            MAknEventObserver::EControlContentUpdatedInternally,
            NULL );
        }
        
    if ( shift && iExtension->iCcpuSupport )
        {
        iExtension->iCcpuSupport->HandleSelectionChangeL();
        }
    if ( cousorChanged )
    	{
        ReportAknEdStateEventL( MAknEdStateObserver::EAknCursorPositionChanged );
    	}
    // see if we want to remember the old cursor X position
    if ( targetPosUsed )
        {
        if ( iTargetCursorPos == CAknPhedView::KNoPos )
            iTargetCursorPos = cursorX;
        }
    else
        iTargetCursorPos = CAknPhedView::KNoPos;

    // To prevent flicker by avoiding drawing screen multi-times in short 
    // time. When cursor moves between two lines that are both shown at 
    // the same time, the screen will be drawn by CAknPhedView, and the 
    // DrawNow need not be called, otherwise the screen should be drawn here. 
    TInt leftPosPost = lineArray->At( iView->CursorLine() ).LeftPos();    
    if ( needDraw || 
        Abs( leftPosPost - leftPosPre ) != lineArray->At( 0 ).LineWidth() )
        {
        DrawNow();
        }
    ReportEventL( MCoeControlObserver::EEventStateChanged );
    return resp;
    }

EXPORT_C TSize CAknPhoneNumberEditor::MinimumSize()
    {
    return iView->Rect().Size();
    }

EXPORT_C void CAknPhoneNumberEditor::FocusChanged( TDrawNow aDrawNow )
    {
    if ( iView )
        {
        if ( IsFocused() )
            iView->EnableCursor();
        else
            iView->DisableCursor(); 
        }
            
    if ( iExtension->iCcpuSupport )
        {
        TRAP_IGNORE( iExtension->iCcpuSupport->HandleFocusChangeL() );        
        }    
    if ( ! IsFocused() )
        {
        TRAP_IGNORE( ReportAknEdStateEventL( MAknEdStateObserver::EAknSyncEdwinState ) );
        }
    if ( aDrawNow )
        DrawNow();
    }

EXPORT_C void CAknPhoneNumberEditor::Draw( const TRect& aRect ) const
    {
    CEikBorderedControl::Draw( aRect );
    iView->Draw( SystemGc(), iFlags[ERedrawAll], this );
    }

EXPORT_C TCoeInputCapabilities CAknPhoneNumberEditor::InputCapabilities() const
    {
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        TCoeInputCapabilities inputCaps(
            TCoeInputCapabilities::EWesternAlphabetic | 
            TCoeInputCapabilities::ENavigation, 
            const_cast<CAknPhoneNumberEditor*>( this ), NULL ); 
            
        // Voip-enabled phone editor wants to use edit-key style hash key mode selection.    
        iExtension->iExtendedInputCapabilities->SetEditorType( 
            CAknExtendedInputCapabilities::EPhoneNumberEditor );                    
        iExtension->iExtendedInputCapabilities->SetCapabilities(
            CAknExtendedInputCapabilities::EForceHashKeySelectionStatusFlagOff |
            CAknExtendedInputCapabilities::EForceEditSubmenuStatusFlagOff );              
        inputCaps.SetObjectProvider( 
            const_cast<CAknPhoneNumberEditorExtension*>( iExtension ) );                        
                        
        return inputCaps;                                                   
        }
    else if ( FeatureManager::FeatureSupported( KFeatureIdCsVideoTelephony ) )
        {
        TCoeInputCapabilities inputCaps(
            TCoeInputCapabilities::EDialableCharacters | 
            TCoeInputCapabilities::ENavigation, 
            const_cast<CAknPhoneNumberEditor*>(this), NULL); 
            
        iExtension->iExtendedInputCapabilities->SetEditorType(
            CAknExtendedInputCapabilities::EPhoneNumberEditor );                                                                                          
        inputCaps.SetObjectProvider(
            const_cast<CAknPhoneNumberEditorExtension*>( iExtension ) );                                
                    
        return inputCaps;                                  
        }  
    return TCoeInputCapabilities( 0, const_cast<CAknPhoneNumberEditor*>(this), NULL );
    }

EXPORT_C TInt CAknPhoneNumberEditor::TextLength() const
    {
    return iModel->Length();
    }

EXPORT_C TInt CAknPhoneNumberEditor::CursorPos() const
    {
    return iModel->CursorPosition();
    }

EXPORT_C TInt CAknPhoneNumberEditor::SelectionLength() const
    {
    return iModel->SelectionWidth();
    }

EXPORT_C TCursorSelection CAknPhoneNumberEditor::Selection() const
    {
    return TCursorSelection( iModel->CursorPosition(), iModel->AnchorPosition() );
    }

EXPORT_C void CAknPhoneNumberEditor::ClearSelectionL()
    {
    if ( iModel->SelectionExists() )
        iModel->DeleteLeft();
    }

EXPORT_C void CAknPhoneNumberEditor::SetSelectionL( TInt aCursorPos,TInt aAnchorPos )
    {
    iModel->SetRealCursorPosition(aCursorPos);
    iModel->SetAnchorPosition( aAnchorPos );
    ReportAknEdStateEventL( 
            MAknEdStateObserver::EAknCursorPositionChanged );
    }

EXPORT_C void CAknPhoneNumberEditor::SetCursorPosL( TInt aCursorPos,TBool aSelect )
    {
    TInt anchor = iModel->AnchorPosition();
    iModel->SetRealCursorPosition( aCursorPos );
    if ( aSelect )
        iModel->SetAnchorPosition( anchor );
    ReportAknEdStateEventL( 
        MAknEdStateObserver::EAknCursorPositionChanged );
    }

EXPORT_C void CAknPhoneNumberEditor::SelectAllL()
    {
    iModel->SetRealCursorPosition(iModel->Length());
    iModel->SetAnchorPosition( 0 );
    }

EXPORT_C void CAknPhoneNumberEditor::GetText( TDes& aDes ) const
    {
    if ( Text().Length() <= aDes.MaxLength() )
        {
        aDes = Text();
        }
    else
        {
        aDes = Text().Left( aDes.MaxLength() );
        }
    }

EXPORT_C HBufC* CAknPhoneNumberEditor::GetTextInHBufL() const
    {
    return Text().AllocL();
    }

EXPORT_C void CAknPhoneNumberEditor::SetTextL( const TDesC* aDes )
    {
    if ( aDes )
        iModel->SetText( *aDes );
    else
        iModel->SetText( KNullDesC() );
    }

EXPORT_C void CAknPhoneNumberEditor::CancelFepTransaction()
    {
    CCoeFep* fep = iCoeEnv->Fep();
    if ( fep )
        {
        fep->CancelTransaction();
        }   
    }

EXPORT_C void CAknPhoneNumberEditor::UpdateScrollBarsL()
    {
    }

EXPORT_C CEikScrollBarFrame* CAknPhoneNumberEditor::CreateScrollBarFrameL()
    {
    return NULL;
    }

EXPORT_C TInt CAknPhoneNumberEditor::LineCursorWidth() const
    {
    return 0;
    }

EXPORT_C TMargins8 CAknPhoneNumberEditor::Margins() const
    {
    return TMargins8();
    }

void CAknPhoneNumberEditor::StartFepInlineEditL( 
         const TDesC& aInitialInlineText, 
         TInt /*aPositionOfInsertionPointInInlineText*/, 
         TBool /*aCursorVisibility*/, 
         const MFormCustomDraw* /*aCustomDraw*/, 
         MFepInlineTextFormatRetriever& /*aInlineTextFormatRetriever*/, 
         MFepPointerEventHandlerDuringInlineEdit& /*aPointerEventHandlerDuringInlineEdit*/)
    {
    if ( aInitialInlineText.Length() == 0 )
        {
        // This method used to ignore aInitialInlineText. For improved 
        // backwards compatibility just do what it did before.  
        // That is, do not admit a new state of "in inline edit", but with no text.
        iFlags.Clear( EInlineEditInProgress );
        }
    else
        {
        // flag is set by a StartFepInlineEdit with text
        // or by UpdateFepInlineTextL. Should not get a 2nd start.
        __ASSERT_DEBUG( !iFlags[EInlineEditInProgress], 
                        PhedControlPanic(EIncorrectInlineEditState) );
        iModel->Insert( aInitialInlineText[0] );
        iFlags.Set( EInlineEditInProgress );
        DrawChanges();
        }
    }

void CAknPhoneNumberEditor::UpdateFepInlineTextL(const TDesC& aNewInlineText, 
    TInt /*aPositionOfInsertionPointInInlineText*/ )
    {
    if ( iFlags[EInlineEditInProgress] )
        iModel->DeleteLeft();
    
    if ( aNewInlineText != KNullDesC )
        {
        iModel->Insert( aNewInlineText[0] );    
        }
    else
        {
        iModel->DeleteLeft();
        }
    
    iFlags.Set( EInlineEditInProgress );
    DrawChanges();
    }

void CAknPhoneNumberEditor::SetInlineEditingCursorVisibilityL(TBool /*aCursorVisibility*/)
    {
    }

void CAknPhoneNumberEditor::CancelFepInlineEdit()
    {
    iFlags.Clear( EInlineEditInProgress );
    }

TInt CAknPhoneNumberEditor::DocumentLengthForFep() const
    {
    return iModel->UnFormattedText( 0 ).Length();
    }

TInt CAknPhoneNumberEditor::DocumentMaximumLengthForFep() const
    {
    // Lie to FEP about the maximum length, because we handle our own overflow.
    return iModel->MaxDisplayLength() + 1;
    }

void CAknPhoneNumberEditor::SetCursorSelectionForFepL( const TCursorSelection& aCursorSelection )
    {
    iModel->SetRealCursorPosition( iModel->Uncompensate( aCursorSelection.iCursorPos ) );
    iModel->SetAnchorPosition( iModel->Uncompensate( aCursorSelection.iAnchorPos  ) );
    
    ReportAknEdStateEventL( 
            MAknEdStateObserver::EAknCursorPositionChanged );
    DrawNow();
    }

void CAknPhoneNumberEditor::GetCursorSelectionForFep( TCursorSelection& aCursorSelection ) const
    {
    aCursorSelection.iCursorPos = iModel->CursorPosition();
    aCursorSelection.iAnchorPos = iModel->AnchorPosition();
    }

void CAknPhoneNumberEditor::GetEditorContentForFep( TDes& aEditorContent, 
                                                    TInt aDocumentPosition, 
                                                    TInt aLengthToRetrieve ) const
    {
    TInt realLength = Min( iModel->Length() - aDocumentPosition, aLengthToRetrieve );
    if ( iModel->Length() > 0 )
        {
        if ( iModel->UnFormattedText( 0 ).Length() >= aDocumentPosition + realLength )
            {
            aEditorContent.Copy(
                iModel->UnFormattedText( 0 ).Mid( aDocumentPosition, realLength ) );
            }
        }
    }
void CAknPhoneNumberEditor::GetFormatForFep( TCharFormat& /*aFormat*/, 
                                             TInt /*aDocumentPosition*/ ) const
    {
    }

void CAknPhoneNumberEditor::GetScreenCoordinatesForFepL( TPoint& /*aLeftSideOfBaseLine*/, 
                                                         TInt& /*aHeight*/, 
                                                         TInt& /*aAscent*/, 
                                                         TInt /*aDocumentPosition*/) const
    {
    }

void CAknPhoneNumberEditor::DoCommitFepInlineEditL()
    {
    iFlags.Clear( EInlineEditInProgress );
    }

MCoeFepAwareTextEditor_Extension1* CAknPhoneNumberEditor::Extension1(TBool& aSetToTrue)
    {
    aSetToTrue=ETrue;
    return STATIC_CAST( MCoeFepAwareTextEditor_Extension1*, this );
    }

TInt CAknPhoneNumberEditor::TargetCursorPos( TInt aCurrentPos )
    {
    if ( iTargetCursorPos == CAknPhedView::KNoPos )
        return aCurrentPos;
    else
        return iTargetCursorPos;
    }

void CAknPhoneNumberEditor::StateChanged()
    {
#ifdef _DEBUG
    TRAPD(err, ReportEventL( MCoeControlObserver::EEventStateChanged ) );
    // phone number editor should never leave.
    TRAP_IGNORE(__ASSERT_DEBUG( err == KErrNone, PhedControlPanic( ELeaveInStateChange ) ) ); 
#else
    TRAP_IGNORE( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
#endif // _DEBUG
    }

CEikScrollBarFrame* CAknPhoneNumberEditor::CreateScrollBarFrameL(TBool /*aPreAlloc*/)
    {
    return NULL;
    }

void CAknPhoneNumberEditor::SetStateTransferingOwnershipL( CState* aState,
                                                           TUid /*aTypeSafetyUid*/)
    {
    if ( iFepState )
        delete iFepState;
    iFepState=aState;
    }

MCoeFepAwareTextEditor_Extension1::CState* CAknPhoneNumberEditor::State( TUid /*aTypeSafetyUid*/ )
    {
    return iFepState;
    }

void CAknPhoneNumberEditor::CreateFepStateL()
    {
    CAknEdwinState* fepState = new(ELeave) CAknEdwinState();
    iFepState = fepState;
    
    fepState->SetObjectProvider( this );
    fepState->SetFlags( EAknEditorFlagFixedCase | EAknEditorFlagNoT9 | 
        EAknEditorFlagNoEditIndicators | EAknEditorFlagSelectionVisible ); 
    fepState->SetDefaultInputMode( EAknEditorNumericInputMode );
    fepState->SetCurrentInputMode( EAknEditorNumericInputMode );
    fepState->SetPermittedInputModes( EAknEditorNumericInputMode );
    fepState->SetDefaultCase( EAknEditorLowerCase );
    fepState->SetCurrentCase( EAknEditorLowerCase );
    fepState->SetPermittedCases( EAknEditorLowerCase|EAknEditorUpperCase );
    fepState->SetSpecialCharacterTableResourceId( 0 );
    fepState->SetNumericKeymap( EAknEditorStandardNumberModeKeymap );
    }

EXPORT_C void CAknPhoneNumberEditor::MCoeFepAwareTextEditor_Reserved_2()
    {
    }

EXPORT_C void CAknPhoneNumberEditor::MCoeFepAwareTextEditor_Extension1_Reserved_2()
    {
    }

EXPORT_C void CAknPhoneNumberEditor::MCoeFepAwareTextEditor_Extension1_Reserved_3()
    {
    }

EXPORT_C void CAknPhoneNumberEditor::MCoeFepAwareTextEditor_Extension1_Reserved_4()
    {
    }


// ---------------------------------------------------------
// CAknPhoneNumberEditor::ChangeEditorMode
// ---------------------------------------------------------
//
EXPORT_C TInt CAknPhoneNumberEditor::ChangeEditorMode( TBool aDefaultMode )
    {
    TInt value( EAknEditorNumericInputMode ); // Return value.
    
    if ( FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
        {
        CAknEdwinState* fepState = ( CAknEdwinState* )iFepState; 

        // Get current input mode.
        TInt currentInputMode = fepState->CurrentInputMode();
    
        // Set default values.
        if ( aDefaultMode )
            {
            fepState->SetCurrentInputMode( EAknEditorNumericInputMode );   
            value = EAknEditorNumericInputMode;
            }
        // Set next input mode. 123 -> abc -> 123...    
        else
            {
            if ( currentInputMode == EAknEditorNumericInputMode )
                {
                fepState->SetCurrentInputMode( EAknEditorTextInputMode );
                fepState->SetSpecialCharacterTableResourceId( 
                    R_AVKON_URL_SPECIAL_CHARACTER_TABLE_DIALOG );
                value = EAknEditorTextInputMode;
                }
            else if ( currentInputMode == EAknEditorTextInputMode )
                {
                fepState->SetCurrentInputMode(EAknEditorNumericInputMode);
                fepState->SetSpecialCharacterTableResourceId( 0 );
                value = EAknEditorNumericInputMode;
                }
            }   
            
        fepState->SetCurrentCase(EAknEditorLowerCase);        
        // Set some other VoIP specific editor settings.    
        if ( FeatureManager::FeatureSupported( KFeatureIdOnScreenDialer ) ) 
            {
            fepState->SetFlags( EAknEditorFlagNoT9  
                | EAknEditorFlagLatinInputModesOnly | EAknEditorFlagNoEditIndicators );
            }
        else
            {
            fepState->SetFlags( EAknEditorFlagNoT9  
                | EAknEditorFlagLatinInputModesOnly );
            }
        
        fepState->SetPermittedInputModes( 
            EAknEditorNumericInputMode|EAknEditorTextInputMode );       
        fepState->SetNumericKeymap(EAknEditorAlphanumericNumberModeKeymap);
    
        // Report FEP from new settings.
        TRAP_IGNORE( fepState->ReportAknEdStateEventL(
            MAknEdStateObserver::EAknEdwinStateEventStateUpdate ) ); 
        
        fepState->SetMenu();  
        }
    DrawChanges();
    return value;
    }
    
// ---------------------------------------------------------
// CAknPhoneNumberEditor::GetEditorMode
// ---------------------------------------------------------
//
EXPORT_C TInt CAknPhoneNumberEditor::GetEditorMode() const
    {
    CAknEdwinState* fepState = ( CAknEdwinState* )iFepState; 

    TInt currentInputMode = fepState->CurrentInputMode();

    fepState->SetCurrentCase(EAknEditorLowerCase);    
    if ( currentInputMode == EAknEditorNumericInputMode )
        {
        fepState->SetSpecialCharacterTableResourceId( 0 );        
        }
    else if ( currentInputMode == EAknEditorTextInputMode )
        {
        
        fepState->SetSpecialCharacterTableResourceId( 
            R_AVKON_URL_SPECIAL_CHARACTER_TABLE_DIALOG );
        } 
        
    fepState->SetMenu(); 
    return currentInputMode;
    }

// ---------------------------------------------------------
// CAknPhoneNumberEditor::ResetEditorToDefaultValues
// ---------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::ResetEditorToDefaultValues()
    {
    CAknEdwinState* fepState = ( CAknEdwinState* )iFepState; 
    CloseVKB();
    // Set FEP-state to default values. 
    fepState->SetFlags( EAknEditorFlagFixedCase | EAknEditorFlagNoT9 | 
        EAknEditorFlagNoEditIndicators );
    fepState->SetDefaultInputMode( EAknEditorNumericInputMode );
    fepState->SetCurrentInputMode( EAknEditorNumericInputMode );
    fepState->SetPermittedInputModes( EAknEditorNumericInputMode );
    fepState->SetDefaultCase( EAknEditorLowerCase );
    fepState->SetCurrentCase( EAknEditorLowerCase );
    fepState->SetPermittedCases( EAknEditorLowerCase | EAknEditorUpperCase );
    fepState->SetSpecialCharacterTableResourceId( 0 );
    fepState->SetNumericKeymap( EAknEditorStandardNumberModeKeymap );
    
    DrawChanges();
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::HandlePointerEventL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::HandlePointerEventL(
    const TPointerEvent& aPointerEvent)
    {   
    TCursorSelection selectionBefore = Selection();
    TInt cursor = iView->GetCursorPosByPoint( aPointerEvent.iPosition );
    // if cursro is not in accepted range. cancel current selection
    
    if ( cursor < 0 ) 
        {
        cursor = CursorPos();
        DrawNow();
        return;
        }
    
    const CAknPhedViewLineArray* lineArray = iView->LineArray(); 
    TInt cursorLinePre = iView->CursorLine();
    TInt leftPosPre = lineArray->At( cursorLinePre ).LeftPos();
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            
            if ( feedback )
                {
                feedback->InstantFeedback( this, ETouchFeedbackEditor );
                }
            }
            //cancel previous selection
            if ( iExtension->iPointPos != cursor )
                {                
                SetCursorPosL( iModel->Uncompensate( cursor ), EFalse  );              
                iExtension->iPointPos = cursor;
                }
            break;
        case TPointerEvent::EButton1Up:
            if ( iExtension->iPointPos == cursor )
                {
                SetCursorPosL( iModel->Uncompensate( cursor ), EFalse );
                }
            else
                {
                SetSelectionL( iModel->Uncompensate( cursor ), 
                    iModel->Uncompensate( iExtension->iPointPos ) );
                }
            break;
        case TPointerEvent::EButtonRepeat:
        case TPointerEvent::EDrag:
            {              
            SetSelectionL( iModel->Uncompensate( cursor ), 
                iModel->Uncompensate( iExtension->iPointPos ) );
            TCursorSelection selectionAfter = Selection();
            TBool selectionChanged = 
                   (  ( selectionAfter.iCursorPos != selectionBefore.iCursorPos )
                   || ( selectionAfter.iAnchorPos != selectionBefore.iAnchorPos ) );
            if ( selectionChanged )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( this, ETouchFeedbackTextSelection );
                    }
                }
            }
            break;        
        default:
            break;          
        }    
    
    // same handling as OfferKeyEvent to prevent flicker.   
    TInt leftPosPost = lineArray->At( iView->CursorLine() ).LeftPos();    
    if ( Abs( leftPosPost - leftPosPre ) != lineArray->At( 0 ).LineWidth() )
        {
        DrawNow();
        }
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::MopSupplyObject
// --------------------------------------------------------------------------
//    
EXPORT_C TTypeUid::Ptr CAknPhoneNumberEditor::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CEikMenuBar::ETypeId )    
        {
        return aId.MakePtr( iEikonEnv->AppUiFactory()->MenuBar() );
        }
    return TTypeUid::Null();
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuIsFocused
// --------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhoneNumberEditor::CcpuIsFocused() const
    {
    return IsFocused();
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCanCut
// --------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhoneNumberEditor::CcpuCanCut() const
    {
    return ( iExtension->iCcpuSupport && SelectionLength() != 0 );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCutL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::CcpuCutL()
    {
    ClipboardL( EFalse );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCanCopy
// --------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhoneNumberEditor::CcpuCanCopy() const
    {
    return ( iExtension->iCcpuSupport && SelectionLength() != 0 );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCopyL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::CcpuCopyL()
    {
    ClipboardL( ETrue );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCanPaste
// --------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhoneNumberEditor::CcpuCanPaste() const
    {
    if ( !iExtension->iCcpuSupport )
        return EFalse;
    
    if ( iExtension->iPasteText )
        {
        delete iExtension->iPasteText;
        iExtension->iPasteText = NULL;
        }   
    TRAPD( err, DoCanPasteL() );    
    return ( err == KErrNone );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::DoCanPasteL
// Check if there are data in clipboard and if the format of the data is 
// accepted by phone number editor
// --------------------------------------------------------------------------
//  
void CAknPhoneNumberEditor::DoCanPasteL() const
    {    
    CClipboard* cb = NULL;
    cb = CClipboard::NewForReadingL( iCoeEnv->FsSession() );
    CleanupStack::PushL( cb );
    CStreamStore& store = cb->Store();
    CStreamDictionary& dict = cb->StreamDictionary();
    
    // get plain text data from clipboard
    CPlainText* text = CPlainText::NewL();
    CleanupStack::PushL( text );
    TInt dataLength = text->PasteFromStoreL( store, dict, KPlainTextPos);   
    if ( dataLength == 0 )  
        {
        User::Leave( KErrNotFound );
        }       
    HBufC* hBuf = HBufC::NewL( dataLength );    
    TPtr buf = hBuf->Des(); 
    text->Extract( buf, KPlainTextPos, dataLength );
    CleanupStack::PopAndDestroy( text );
    CleanupStack::PushL( hBuf );
    
    // get the list of allowed characters in phone number editor
    CAknEdwinState* fepState = ( CAknEdwinState* )iFepState;
    HBufC* specTable = NULL;        
    if ( fepState->NumericKeymap() == 
         EAknEditorAlphanumericNumberModeKeymap )
        {
        TInt resId = fepState->SpecialCharacterTableResourceId();
        if ( resId > 0 )
            {
            specTable = iEikonEnv->AllocReadResourceLC( resId );
            }       
        }       
    HBufC* allowChars = iEikonEnv->AllocReadResourceLC( 
        R_EIK_ALLOWED_STANDARDNUMBERMODEKEYMAP );   
    
    // check if the characters are allowed, if one character is not allowed, 
    // it will not be pasted into phone number editor
	if ( fepState->CurrentInputMode() != EAknEditorTextInputMode )
		{
		TInt pos = 0;
		TInt index = 0;
		while ( index < buf.Length() )
			{
            pos = allowChars->Locate( buf[index] );     
			if ( pos == KErrNotFound && specTable && specTable->Length() > 0 )
				{
				pos = specTable->Locate( buf[index] );
				}           
			if ( pos == KErrNotFound )
				{
				buf.Delete( index, 1 );
				}
			else
				{
				index++;
				}
			}
		if ( buf.Length() == 0 )
			{
			User::Leave( KErrNotFound );
			}
		}
    iExtension->iPasteText = HBufC::NewL( buf.Length() );
    TPtr pasteBuf = iExtension->iPasteText->Des();
    pasteBuf.Copy( buf );
    CleanupStack::PopAndDestroy( allowChars );
    if ( specTable )
        {
        CleanupStack::PopAndDestroy( specTable );
        }   
    CleanupStack::PopAndDestroy( hBuf );
    CleanupStack::PopAndDestroy( cb );    
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuPasteL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::CcpuPasteL()
    {
    if ( iExtension->iPasteText )
        {
        iModel->Paste( iExtension->iPasteText->Des() );
        DrawNow();
        }
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuCanUndo
// --------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhoneNumberEditor::CcpuCanUndo() const
    {
    return EFalse;
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CcpuUndoL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknPhoneNumberEditor::CcpuUndoL()
    {
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::EnableCcpuSupportL
// --------------------------------------------------------------------------
//
void CAknPhoneNumberEditor::EnableCcpuSupportL( TBool aSupport )
    {
    CAknCcpuSupport* ccpu = NULL;
    CAknEdwinState* edwinState = ( CAknEdwinState* )iFepState;
    
    if ( aSupport )
        {
        ccpu = new( ELeave ) CAknCcpuSupport( this );
        ccpu->SetMopParent( this );
        CleanupStack::PushL( ccpu );
        ccpu->ConstructL();
        CleanupStack::Pop( ccpu );
        if ( edwinState )
            {
            edwinState->SetCcpuState( this );                   
            }
        }
    else
        {       
        if ( edwinState )
            {
            edwinState->SetCcpuState( NULL );                   
            }
        }        
    delete iExtension->iCcpuSupport;
    iExtension->iCcpuSupport = ccpu;
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::ClipboardL
// implementate copy and cut
// --------------------------------------------------------------------------
//  
void CAknPhoneNumberEditor::ClipboardL( TBool aIsCopy )
    {
    CancelFepTransaction();
    TInt selectLength = SelectionLength();      
    if ( selectLength == 0 )
        {
        iEikonEnv->InfoMsg( aIsCopy ? 
            R_EIK_TBUF_NOTHING_TO_COPY : R_EIK_TBUF_NOTHING_TO_CUT );
        }           
    else
        {
        HBufC* buf = HBufC::NewLC( selectLength );
        TPtr text = buf->Des();
        if ( aIsCopy )
            {
            iModel->Copy( text );               
            }
        else
            {
            iModel->Cut( text );
            DrawNow();
            }
        PlaceDataOnClipboardL( text );      
        CleanupStack::PopAndDestroy( buf );             
        iEikonEnv->InfoMsg( R_EIK_TBUF_COPIED );
        if ( iExtension->iCcpuSupport )
            {
            iExtension->iCcpuSupport->HandleSelectionChangeL();
            }           
        CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog();
        dlg->SetTimeout( CAknNoteDialog::EShortTimeout );
        dlg->SetTone( CAknNoteDialog::ENoTone );
        dlg->ExecuteLD( R_AVKON_NOTE_CONF_COPIED );           
        }        
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::PlaceDataOnClipboardL
// --------------------------------------------------------------------------
//  
void CAknPhoneNumberEditor::PlaceDataOnClipboardL( const TDesC& aText )
    {   
    CClipboard* cb = CClipboard::NewForWritingLC( iCoeEnv->FsSession() );
    
    CStreamStore& store = cb->Store();
    CStreamDictionary& dict = cb->StreamDictionary();
    
    CPlainText* text = CPlainText::NewL();
    CleanupStack::PushL( text );
    text->InsertL( KPlainTextPos, aText );
    text->CopyToStoreL( store, dict, KPlainTextPos, aText.Length() );
    CleanupStack::PopAndDestroy( text );
    cb->CommitL();
    
    CleanupStack::PopAndDestroy( cb );
    }
    
// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::OpenVKB
// --------------------------------------------------------------------------
// 
EXPORT_C void CAknPhoneNumberEditor::OpenVKB( )
    {
    TUint cap = iExtension->iExtendedInputCapabilities->Capabilities();
    cap &= ~CAknExtendedInputCapabilities::EInputEditorDisableVKB;
    iExtension->iExtendedInputCapabilities->SetCapabilities( cap );
    TRAP_IGNORE( ReportAknEdStateEventL( 
    		     MAknEdStateObserver::EAknActivatePenInputRequest ) );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::CloseVKB
// --------------------------------------------------------------------------
//
void CAknPhoneNumberEditor::CloseVKB( )
    {
    TUint cap = iExtension->iExtendedInputCapabilities->Capabilities();
    cap |= CAknExtendedInputCapabilities::EInputEditorDisableVKB;
    iExtension->iExtendedInputCapabilities->SetCapabilities( cap );
    ReportAknEdStateEventL( MAknEdStateObserver::EAknClosePenInputRequest );
    }

// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::ReportAknEdStateEventL
// --------------------------------------------------------------------------
//
void CAknPhoneNumberEditor::ReportAknEdStateEventL( 
         MAknEdStateObserver::EAknEdwinStateEvent aStateEvent )
    {
    CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*,State(KNullUid) );
    if ( edwinState )
        {                   
        TRAP_IGNORE( edwinState->ReportAknEdStateEventL( aStateEvent ) );
        }
    }
// --------------------------------------------------------------------------
// CAknPhoneNumberEditor::AknEditorFlags
// --------------------------------------------------------------------------
//
EXPORT_C TInt CAknPhoneNumberEditor::AknEditorFlags() 
	{
	CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*,State(KNullUid) ); 	  
    if ( !edwinState )
    	{
    	return 0;
    	}
	return edwinState->Flags();	
	}


// End of file
