/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup form for adding custom controls to popup dialog
*
*/


// INCLUDE FILES
#include <barsread.h>
#include <eikdpage.h>
#include <eikdpsel.h>
#include <eikcapc.h>
#include <eikspace.h>
#include <eikprogi.h>
#include <eikrted.h>
#include <w32std.h>

#include <aknappui.h>
#include <AknsDrawUtils.h>
#include <aknconsts.h>
#include <AknUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsFrameBackgroundControlContext.h>

#include <layoutmetadata.cdl.h>

#include <aknsoundsystem.h>
#include <AknBidiTextUtils.h>
#include <AknBitmapAnimation.h>

#include <AknPanic.h>
#include <AknPopupform.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <avkon.mbg>
#include <AknIconUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h>

// CONSTANTS
const TInt KMaxNoOfEditorLines = 6;

NONSHARABLE_CLASS(CAknPopupFormExtension) :
    public CCoeControl,
    public MAknPictographAnimatorCallBack,
    public MEikScrollBarObserver
    {
    public:
        static CAknPopupFormExtension* NewL( CAknPopupForm& aOwner );
        ~CAknPopupFormExtension();
        void Draw( const TRect& aRect ) const;

    private: // From MAknPictographAnimatorCallBack
        void DrawPictographArea();

    protected: // From MEikScrollBarObserver
        virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
    private:
        CAknPopupFormExtension( CAknPopupForm& aOwner );
        void ConstructL();

    public:
        CAknPopupForm& iOwner;
        CAknPictographInterface* iPictoInterface;
        TInt iWaitAnimationResourceIndex;
        TBool iHasLabelBackground;
        TInt iCursorLine;
        TBool iToBold;
    };


CAknPopupFormExtension::CAknPopupFormExtension( CAknPopupForm& aOwner )
    : iOwner( aOwner ), iWaitAnimationResourceIndex ( -1 ), iHasLabelBackground( EFalse )
    {
    }

CAknPopupFormExtension* CAknPopupFormExtension::NewL( CAknPopupForm& aOwner )
    {
    CAknPopupFormExtension* self = new( ELeave ) CAknPopupFormExtension( aOwner );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

void CAknPopupFormExtension::ConstructL()
    {
    }

CAknPopupFormExtension::~CAknPopupFormExtension()
    {
    delete iPictoInterface;
    }

void CAknPopupFormExtension::DrawPictographArea()
    {
    iOwner.RedrawHeading();
    }

void CAknPopupFormExtension::HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType)
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CEikCaptionedControl* captionedControl = iOwner.GetControlByControlType( EEikCtRichTextEditor );
        CEikRichTextEditor* ed = NULL;
        if ( captionedControl )
            {
            CCoeControl* coe = captionedControl->iControl;
            ed = reinterpret_cast<CEikRichTextEditor*>( coe );
            }
        TInt lpp = KMaxNoOfEditorLines;
        if ( ed && iOwner.TextIsScrollable() )
            {
            if ( iOwner.iFlags.IsSet ( EPopupFormHasEditor ) )
                {
                if ( !iOwner.iFlags.IsSet( EPopupFormUsesPlainFont ) )
                    {
                    lpp--;
                    }
                if ( iOwner.iFlags.IsSet( EPopupFormHasProgbar )|| iOwner.iFlags.IsSet( EPopupFormHasWaitAnim ) )
                    {
                    lpp--;
                    }
                }   
            // Using ed->MoveDisplayL to scroll text will cause some display 
            // error, so use ed->MoveCursorL to instead of it.            
            switch (aEventType)
                {
                case EEikScrollUp:
                    if ( (iOwner.iCurrentLine-1) >= 1 )
                        {
                        iOwner.iCurrentLine--;
                        iOwner.UpdateScrollIndicatorL();
                        while( iCursorLine > iOwner.iCurrentLine )
                            {
                            ed->MoveCursorL( TCursorPosition::EFLineUp, EFalse );
                            iCursorLine--;
                            }                        
                        }
                break;
                case EEikScrollPageUp:
                    {
                   if ( iOwner.iCurrentLine - lpp >= 1)
                        {
                        iOwner.iCurrentLine = iOwner.iCurrentLine - lpp + 1;
                        }
                   else
                        {
                        iOwner.iCurrentLine=1;
                        }
                    iOwner.UpdateScrollIndicatorL();
                    while ( iCursorLine > iOwner.iCurrentLine )
                        {
                        ed->MoveCursorL( TCursorPosition::EFLineUp, EFalse );
                        iCursorLine--;
                        }
                    }
                break;
                case EEikScrollDown:
                    if ( (iOwner.iNoOfEditorLines - iOwner.iCurrentLine) >= lpp )
                        {
                        iOwner.iCurrentLine++;
                        iOwner.UpdateScrollIndicatorL();                                              
                        while ( iCursorLine < iOwner.iCurrentLine - 1 + lpp )
                            {
                            ed->MoveCursorL( TCursorPosition::EFLineDown, EFalse );
                            iCursorLine++;    
                            }
                        }               
                break;
                case EEikScrollPageDown:
                    {
                    if ( (iOwner.iNoOfEditorLines - iOwner.iCurrentLine - lpp) >= (lpp - 1))
                        {
                        iOwner.iCurrentLine = iOwner.iCurrentLine + lpp - 1;
                        }
                   else
                        {
                        iOwner.iCurrentLine = iOwner.iNoOfEditorLines - lpp + 1;
                        }                    
                    iOwner.UpdateScrollIndicatorL();
                    TInt bottomLine = iOwner.iCurrentLine - 1 + lpp;
                    TInt destLine = bottomLine > iOwner.iNoOfEditorLines ? 
                                iOwner.iNoOfEditorLines : bottomLine;
                    while ( iCursorLine < destLine )
                        {
                        ed->MoveCursorL( TCursorPosition::EFLineDown, EFalse );
                        iCursorLine++;                                                                
                        }                    
                    }
                break;
                case EEikScrollThumbDragVert:
                    {
                    TInt currentLine = aScrollBar->Model()->iThumbPosition + 1;
                    if ( ( currentLine >= 1 ) && ( currentLine <= iOwner.iNoOfEditorLines ) )
                        {
                        if (currentLine>iOwner.iCurrentLine)
                            {
                            iOwner.iCurrentLine = currentLine;
                            iOwner.UpdateScrollIndicatorL();
                            TInt bottomLine = currentLine - 1 + lpp;
                            TInt destLine = bottomLine > iOwner.iNoOfEditorLines ? 
                                iOwner.iNoOfEditorLines : bottomLine;
                            while ( iCursorLine < destLine )
                                {
                                ed->MoveCursorL( TCursorPosition::EFLineDown, EFalse );
                                iCursorLine++;                                                                
                                }
                            }
                        if (currentLine<iOwner.iCurrentLine)                        
                            {                            
                            iOwner.iCurrentLine = currentLine;
                            iOwner.UpdateScrollIndicatorL();
                            while( iCursorLine > currentLine )
                                {
                                ed->MoveCursorL( TCursorPosition::EFLineUp, EFalse );
                                iCursorLine--;
                                }                                                       
                            }                        
                        }
                    }
                    break;
            default:
                // Do nothing
                break;
                }
            }
        }
    }

void CAknPopupFormExtension::Draw( const TRect& /* aRect */ ) const
    {
    if ( iHasLabelBackground )
        {
        CWindowGc &gc = SystemGc();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TAknLayoutRect headingArea;
        TAknLayoutRect headingBackground;
        TAknLayoutRect headingCenter;

        headingArea.LayoutRect( Parent()->Rect(), AknLayoutScalable_Avkon::heading_pane( 0 ).LayoutLine() );
        headingBackground.LayoutRect( headingArea.Rect(), AknLayoutScalable_Avkon::bg_popup_heading_pane(  0 ).LayoutLine() );
        headingCenter.LayoutRect( headingBackground.Rect(), AknLayoutScalable_Avkon::bg_popup_heading_pane_g1().LayoutLine() );

        AknsDrawUtils::DrawFrame( skin, gc, headingBackground.Rect(), headingCenter.Rect(),
                                         KAknsIIDQsnFrPopupHeading,
                                         KAknsIIDQsnFrPopupHeadingCenter);

        }
    }



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknPopupForm::CAknPopupForm
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm::CAknPopupForm():
 iTimeoutInSeconds( 0 ), iTone( ENoTone ), iType( EAknNote )
    {
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::CAknPopupForm
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm::CAknPopupForm( const TTone& aTone, const TInt aTimeout,
                             const TPopupFormType& aType ) :
iTimeoutInSeconds( aTimeout ), iTone( aTone ), iType( aType )
    {
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::ConstructL()
    {
    iExtension = CAknPopupFormExtension::NewL( *this );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm* CAknPopupForm::NewLC( const TTone& aTone,
                                              const TInt aTimeout,
                                              const TPopupFormType& aType )
    {
    CAknPopupForm* self = new ( ELeave ) CAknPopupForm( aTone, aTimeout, aType );
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknPopupForm" );
    return self;
    }
// -----------------------------------------------------------------------------
// CAknPopupForm::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm* CAknPopupForm::NewL( const TTone& aTone,
                                             const TInt aTimeout,
                                             const TPopupFormType& aType )
    {
    CAknPopupForm* self = NewLC( aTone, aTimeout, aType );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm* CAknPopupForm::NewLC()
    {
    CAknPopupForm* self = new ( ELeave ) CAknPopupForm();
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknPopupForm" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknPopupForm* CAknPopupForm::NewL()
    {
    CAknPopupForm* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// Destructor
EXPORT_C CAknPopupForm::~CAknPopupForm()
    {
    AKNTASHOOK_REMOVE();
    delete iTimer;
    delete iSBFrame;
    delete iBrushAndPenContext;
    delete iExtension;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetTimeout
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetTimeout( const TInt aTimeoutInSeconds )
    {
    iTimeoutInSeconds = aTimeoutInSeconds;

    if ( IsVisible() )
        {
        TRAP_IGNORE( StartTimeoutTimerL() );
        }
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::SetTone
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetTone( const TTone aTone )
    {
    iTone = aTone;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetPopupFormType
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetPopupFormType( const TPopupFormType aType )
    {
    iType = aType;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetTitleL
// Set the title text. If the given text is too long, truncate it.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetTitleL( const TDesC& aTitle )
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtLabel );
    CEikLabel* head = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        head = reinterpret_cast<CEikLabel*>( coe );
        }

    if ( head )
        {
        HBufC* clippedString = HBufC::NewLC( aTitle.Length() + KAknBidiExtraSpacePerLine );
        *clippedString = aTitle;
        TPtr clippedStringPtr = clippedString->Des();

        // get the parent rect before it necessarily has been calculated in SetSizeAndPosition
        TRect parentRect = PopupWindowRect();

        TAknLayoutRect layRect;
        layRect.LayoutRect( parentRect, AknLayoutScalable_Avkon::heading_pane( 0 ) );
        TAknLayoutText txtLay;
        txtLay.LayoutText(layRect.Rect(), AknLayoutScalable_Avkon::heading_pane_t1( 0 ) );
        TInt width = txtLay.TextRect().Width();
        if ( clippedString->Length() > 0 )
            {
            _LIT( KCR, "\r" );
            _LIT( KLF, "\n" ); 
            _LIT( KLS, "\x2028" );
            _LIT( KLS1, "\u2028" );       
            
            TInt run = ETrue;
            while( run )
                {
                TInt lf = clippedStringPtr. Find( KLF );
                if ( lf != KErrNotFound )
                    {
                    clippedStringPtr.Replace( lf, 1, KNullDesC );
                    }
                TInt cr = clippedStringPtr.Find( KCR );
                if ( cr != KErrNotFound )
                    {
                    clippedStringPtr.Replace( cr, 1, KNullDesC );
                    }
                TInt ls = clippedStringPtr.Find( KLS );
                if ( ls != KErrNotFound )
                    {
                    clippedStringPtr.Replace( ls, 1, KNullDesC );
                    }
                else 
                    {
                    ls = clippedStringPtr.Find( KLS1 );
                    if ( ls != KErrNotFound )
                        {
                        clippedStringPtr.Replace( ls, 1, KNullDesC );
                        }                                            
                    }                
                if ( lf == KErrNotFound && cr == KErrNotFound &&
                     ls == KErrNotFound )
                    {
                    run = EFalse;
                    }
                }
            }
        
        AknBidiTextUtils::ConvertToVisualAndClipL(
            clippedStringPtr, *( head->Font() ), width, width );
                
        head->SetTextL( clippedStringPtr );
        head->UseLogicalToVisualConversion( EFalse );
        CleanupStack::PopAndDestroy(); // clippedString
        if ( aTitle.Length() == NULL )
            {
            UpdateFlags( EPopupFormHeading, EFalse );
            }
        else if ( !iFlags.IsSet( EPopupFormHasHeading ) )
            {
            UpdateFlags( EPopupFormHeading, ETrue );
            }

        if ( IsActivated() )
            {
            LayoutAndDraw();    
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetTextL
// Set the text. Move the cursor to the start of the text.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetTextL( const TDesC* aText )
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtRichTextEditor );
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        CEikRichTextEditor* ed = reinterpret_cast<CEikRichTextEditor*>( coe );
        if ( ed )
            {
            TInt oldNoOfLines = iNoOfEditorLines;
            
            // In CTextView, only \f is a newline character,
            // so '\n', '\r' and '\u2028' have to be onverted to '\f'.
            HBufC* text = aText->AllocL();
            CleanupStack::PushL( text );            
            TPtr ptr = text->Des();            
                        
            if ( ptr.Length() > 0 )
                {
                _LIT( KLF, "\n" );
                _LIT( KCR, "\r" );
                _LIT( KLS, "\u2028" ); 
                _LIT( KLS1, "\x2028" );
                _LIT( KLineBreak, "\f" );           
                            
                //'\n\r' and '\r\n' are newline characters, and individual
                //'\n' or '\r' is also newline character.  
                TBool run = ETrue;            
                while ( run )
                    {              
                    //if newline character is the form of '\n\r' or '\r\n',
                    //the first character will be replaced with a '\f' and 
                    //the redundant second character will be removed
                    TBool removeCR = EFalse;   
                    TInt ret = ptr.Find( KLF );
                    TInt rcr = ptr.Find( KCR );                
                    
                    if ( ret == KErrNotFound )
                        {
                        ret = rcr;
                        }                
                    else if ( rcr != KErrNotFound )
                        {                                        
                        if ( rcr < ret )
                            {
                            //make sure the conversion is happened in order, 
                            //from the begining to the end.                        
                            TInt temp = ret;
                            ret = rcr;
                            rcr = temp;
                            }                    
                        if ( ( rcr - ret ) == 1 )
                            { 
                            //'\n' and '\r' are adjacent, remove 
                            //the second character                                                 
                            removeCR = ETrue;
                            }                    
                        }
                    if ( ret == KErrNotFound )
                        { 
                        //'\u2028' is always a newline character                   
                        ret = ptr.Find( KLS );
                        } 
                    if ( ret == KErrNotFound )
                        { 
                        //'\u2028' is always a newline character                   
                        ret = ptr.Find( KLS1 );
                        }                    
                    if ( ret == KErrNotFound )
                        {
                        run = EFalse;
                        }
                    else
                        {
                        ptr.Replace( ret, 1, KLineBreak );
                        }
                    if ( removeCR )
                        {
                        ptr.Replace( rcr, 1, KNullDesC );
                        }
                    }
                }
            iCurrentLine = 1;
            iExtension->iCursorLine = 1;
            ed->SetCursorPosL( 0, EFalse );

            ed->SetTextL( &ptr );                      
            CleanupStack::PopAndDestroy( text );
            
            CalculateNumberOfScreens();
            if (oldNoOfLines != iNoOfEditorLines && IsActivated() )
                {
                ClearArea( Rect() );
                UpdateScrollIndicatorL();
                LayoutAndDraw();
                }
            else if ( IsActivated() )
                {
                ClearArea( ed->Rect() );
                ed->DrawNow();
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::IncrementProgressBarAndDraw
// If there is a progress bar, increment it with the given value
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::IncrementProgressBarAndDraw( const TInt aIncrement )
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtProgInfo );
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        CEikProgressInfo* pri = reinterpret_cast<CEikProgressInfo*>( coe );
        if ( pri )
            {
            pri->IncrementAndDraw( aIncrement );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetProgressBarAndDraw
// If there is a progress bar, sets it with the given value
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetProgressBarAndDraw( const TInt aIncrement )
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtProgInfo );
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        CEikProgressInfo* pri = reinterpret_cast<CEikProgressInfo*>( coe );
        if ( pri )
            {
            pri->SetAndDraw( aIncrement );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::Draw
// Draw the dialog
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();
    TRect rect( Rect() );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        AknsDrawUtils::Background( skin, cc, this, gc, rect, KAknsDrawParamNoClearUnderImage );
        }
    else
        {
        AknsDrawUtils::Background( skin, cc, this, gc, rect );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::GetControlByControlType
// Loop through the array and return the control of given type. If a control of
// the given type was not found, return NULL
// -----------------------------------------------------------------------------
//
EXPORT_C CEikCaptionedControl* CAknPopupForm::GetControlByControlType( TInt aControlType ) const
    {
    CEikCaptionedControl* controlPtr;
    TInt activePage = ActivePageIndex();

    for ( TInt i = 0; i < iNoOfDialogLines; i++ )
        {
        controlPtr = GetLineByLineAndPageIndex( i, activePage);
        if ( controlPtr && controlPtr->iControlType == aControlType )
            {
            TRAP_IGNORE( controlPtr->iControl->SetContainerWindowL( *this ) );
            controlPtr->iControl->SetControlContext( iBrushAndPenContext );
            return controlPtr;
            }
        }
    return NULL;
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::PrepareLC
// Call the base class' PrepareLC to handle the construction.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::PrepareLC( TInt aResourceID )
    {

    iBrushAndPenContext = CCoeBrushAndPenContext::NewL();
    iBrushAndPenContext->SetBrushStyle( CGraphicsContext::ENullBrush );

    SetControlContext( iBrushAndPenContext );

    CAknDialog::PrepareLC( aResourceID );

    TInt activePage = ActivePageIndex();
    iNoOfDialogLines = GetNumberOfLinesOnPage( activePage );

    for ( TInt i = 0; i < iNoOfDialogLines; i++ )
        {
        CEikCaptionedControl* item = ( CEikCaptionedControl* )
                                    GetLineByLineAndPageIndex( i, activePage );
        item->SetContainerWindowL( *this );
        item->SetMopParent( this );
        item->SetDrawNoWhiteBackground( ETrue );
        item->SetControlContext( iBrushAndPenContext );

        if( item->iControlType == EAknCtBitmapAnimation )
            {
            if( i == iExtension->iWaitAnimationResourceIndex )
                {
                UpdateFlags( EPopupFormWaitAnim, ETrue );
                SetAnimationSize( EPopupFormWaitAnim, item );
                SetWaitAnimationResourceIndex( item->iId );
                }
            else
                {
                UpdateFlags( EPopupFormAnimation, ETrue );
                SetAnimationSize( EPopupFormAnimation, item );
                }
            }
        else
            {
            TPopupFormControlType aPFCtrl = PopupFormControlType( item );
            UpdateFlags( aPFCtrl, ETrue );
            }
        }

    if ( iFlags.IsSet( EPopupFormHasHeading ) )
        {
        // background context for the label
        if ( !iExtension->iHasLabelBackground )
            {
            iExtension->iHasLabelBackground = ETrue;
            iExtension->SetRect( TRect( 0, 0, 1, 1 ) );
            iExtension->SetParent( this );
            iExtension->SetControlContext( iBrushAndPenContext );
            }

        // Pictograph drawer is only needed here if heading exists.
        // Editor has its own.
        Extension()->iPictoInterface =
        CAknPictographInterface::NewL( *this, *Extension() );

        CCoeControl* ctrl = GetControlByControlType( EEikCtLabel );
        if ( Extension()->iPictoInterface )
            {
            if ( ctrl )
                {
                static_cast<CEikLabel*>( ctrl )->EnablePictographsL(
                    *( Extension()->iPictoInterface ) );
                }
            }
        }
   }

// -----------------------------------------------------------------------------
// CAknPopupForm::HandleResourceChange
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::HandleResourceChange( TInt aType )
    {
    CEikDialog::HandleResourceChange( aType );
    if( aType == KEikDynamicLayoutVariantSwitch || aType == KAknsMessageSkinChange ) 
        {
        LayoutAndDraw();
        }
    return;
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::RunLD
//
//
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknPopupForm::RunLD()
    {
    PlayTone();
    ReportUserActivity();
    return CAknDialog::RunLD();
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetSizeAndPosition
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetSizeAndPosition( const TSize& aSize )
    {
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPaneRect );

    // Get the base 2-lines-of-text variety according to softkey location..
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
    TInt variety( 0 );

    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
        {
        variety = 3;
        }
    else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
        {
        variety = 6;
        }
    else
        {
        variety = 0;
        }

    TAknWindowLineLayout layout;
    if ( AknLayoutUtils::ScalableLayoutInterfaceAvailable() )
        {
        layout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window( variety );
        }
    else
        {
        layout = AKN_LAYOUT_WINDOW_popup_note_window( 0 );
        }

    if ( iFlags.IsSet( EPopupFormUsesPlainFont ) )
        {
        layout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window( variety + 2 );
        iExtension->iToBold = EFalse;
        }
    else // bold font
        {
        if ( ( ( iFlags.IsSet( EPopupFormHasProgbar ) || iFlags.IsSet( EPopupFormHasWaitAnim ) )
            && iNoOfEditorLines >= KMaxNoOfEditorLines - 2 )
            || iNoOfEditorLines >= KMaxNoOfEditorLines - 1 )
            {
            layout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window( variety + 2 );
            iExtension->iToBold = ETrue;
            }
        else if ( ( ( iFlags.IsSet( EPopupFormHasProgbar ) || iFlags.IsSet( EPopupFormHasWaitAnim ) )
            && iNoOfEditorLines >= KMaxNoOfEditorLines - 3 )
            || iNoOfEditorLines >= KMaxNoOfEditorLines - 2 )
            {
            layout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window( variety + 1 );
            iExtension->iToBold = ETrue;
            }
        }

    TAknLayoutRect layoutWindow;
    layoutWindow.LayoutRect( mainPaneRect, layout );
    TRect winRect( layoutWindow.Rect() );
    
    CEikCba* cba( static_cast<CEikCba*>( ButtonGroupContainer().ButtonGroup() ) );
    if ( cba->IsVisible() && !cba->IsEmpty() )
        {
        TRect screen;
        AknLayoutUtils::LayoutMetricsRect( 
            AknLayoutUtils::EScreen, screen );

        TAknLayoutRect cbaRect;
        cbaRect.LayoutRect( screen, 
            AknLayoutScalable_Avkon::popup_sk_window( 0 ).LayoutLine() );

        winRect.iBr.iY += cbaRect.Rect().Height();
        }

    if ( iFlags.IsSet ( EPopupFormHasHeading ) )
        {

        TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
        TAknLayoutRect headingRect;
        headingRect.LayoutRect( Rect(), headingLayout );
        if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight || cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
            {
            winRect.iTl.iY -= headingRect.Rect().Height() / 2;
            winRect.iBr.iY += headingRect.Rect().Height() / 2;

            }
        else
            {
            winRect.iTl.iY -= headingRect.Rect().Height();
            }
        }
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        TSize dlgSize;
        dlgSize.iHeight = Max( winRect.Height(), aSize.iHeight );
        dlgSize.iWidth = Max( winRect.Width(), aSize.iWidth );
        CAknDialog::SetSizeAndPosition( dlgSize );
        }
    else
        {
        // do the layout again, this time with corrected values
        SetRect( winRect );
        SizeChanged();
        }
    
    const TInt activePage = ActivePageIndex();

    // Set captioned control's rect to be the same as the control's it contains
    CEikCaptionedControl* line;
    for ( TInt i=0; i < iNoOfDialogLines; i++ )
        {
        line = ( CEikCaptionedControl* )GetLineByLineAndPageIndex( i, activePage );
        line->SetRect( line->iControl->Rect() );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ActivateL
// Set the correct initial value to scroll indicator.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::ActivateL()
    {
    // put the popupform to the control stack with a lower
    // priority to allow the menu to have key events.
    iEikonEnv->EikAppUi()->RemoveFromStack(this);
    iEikonEnv->EikAppUi()->AddToStackL(this, ECoeStackPriorityDefault);

    CAknDialog::ActivateL();
    LayoutAndDraw();
    UpdateScrollIndicatorL();
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::PlayTone
// If there is a tone and a sound system, play the tone
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::PlayTone()
    {
    if ( iTone != 0 && SoundSystem() )
        {
        SoundSystem()->PlaySound( iTone );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::StaticDeleteL
// Cancel the timer and delete the self-pointer received as a parameter.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknPopupForm::StaticDeleteL( TAny *aThis )
    {
    CAknPopupForm* self = reinterpret_cast<CAknPopupForm*>( aThis );
    if ( self->iTimer )
        self->iTimer->Cancel();
    delete self;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SoundSystem
// Return the sound system. If AppUi doesn't exist, return NULL.
//
// -----------------------------------------------------------------------------
//
EXPORT_C CAknKeySoundSystem* CAknPopupForm::SoundSystem() const
    {
    if ( iEikonEnv->AppUi() )
        {
        return iAvkonAppUiBase->KeySounds();
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::LayoutAndDraw
// If control is activated re-do layout and draw
// Hide the control during setting the size and position in order
// to avoid unwanted drawing
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::LayoutAndDraw()
    {
    SetSizeAndPosition( PreferredSize( iCoeEnv->ScreenDevice()->SizeInPixels() ) );
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::PostLayoutDynInitL
// Start the animation and the timer ( if needed).
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::PostLayoutDynInitL()
    {
    if ( iFlags.IsSet( EPopupFormHasAnimation ) || iFlags.IsSet( EPopupFormHasWaitAnim ) )
        {
        StartAnimationL();
        }

    StartTimeoutTimerL();
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::SizeChanged
// Lay the controls out.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SizeChanged()
    {

    CAknDialog::SizeChanged();

    if ( iFlags.IsSet( EPopupFormHasHeading ) )
        {
        LabelLayout();
        if ( iFlags.IsSet( EPopupFormHasSpacer ) )
            {
            SpacerLayout();
            }
        }
    if ( iFlags.IsSet( EPopupFormHasAnimation ) )
        {
        TRAP_IGNORE( AnimationLayoutL() );
        }
    if ( iFlags.IsSet( EPopupFormHasWaitAnim ) )
        {
        TRAP_IGNORE( WaitAnimationLayoutL() );
        }
    if ( iFlags.IsSet( EPopupFormHasEditor ) )
        {
        EditorLayout();
        }
    if ( iFlags.IsSet( EPopupFormHasImage ) )
        {
        ImageLayout();
        }
    if( iFlags.IsSet( EPopupFormHasProgbar ) )
        {
        ProgressBarLayout();
        }
    }



// -----------------------------------------------------------------------------
// CAknPopupForm::OfferKeyEventL
// Grab the up/down arrow key events and scroll the text if needed.
//
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknPopupForm::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                            TEventCode /*aType*/ )
  {
    if ( !iFlags.IsSet( EPopupFormHasEditor ) )
        {
        return EKeyWasNotConsumed;
        }

    TKeyResponse response = EKeyWasNotConsumed;
    TInt code=aKeyEvent.iCode;

    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtRichTextEditor );
    CEikRichTextEditor* ed = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        ed = reinterpret_cast<CEikRichTextEditor*>( coe );
        }
    TInt lpp = KMaxNoOfEditorLines;
    if ( !iFlags.IsSet( EPopupFormUsesPlainFont ) )
         {
         lpp--;
         }
    if ( iFlags.IsSet( EPopupFormHasProgbar )|| iFlags.IsSet( EPopupFormHasWaitAnim ) )
         {
         lpp--;
         }
    switch ( code )
        {
        case EKeyUpArrow:
            if ( ed )
                {
                if ( TextIsScrollable() )
                    {
                    if ( iCurrentLine > 1 )
                        {
                        iCurrentLine--;
                        UpdateScrollIndicatorL();
                        while( iExtension->iCursorLine > iCurrentLine )
                            {
                            ed->MoveCursorL( TCursorPosition::EFLineUp, EFalse );
                            iExtension->iCursorLine--;
                            }                        
                        }
                    }
                response = EKeyWasConsumed;
                }
            break;
        case EKeyDownArrow:
            if ( ed )
                {
                if ( TextIsScrollable() )
                    {
                    if ( iCurrentLine <= iNoOfEditorLines - lpp )
                        {
                        iCurrentLine++;
                        UpdateScrollIndicatorL();                                              
                        while ( iExtension->iCursorLine < iCurrentLine - 1 + lpp )
                            {
                            ed->MoveCursorL( TCursorPosition::EFLineDown, EFalse );
                            iExtension->iCursorLine++;    
                            }                                                
                        }
                    }
                response = EKeyWasConsumed;
                }
            break;
        }
    return response;
    }


EXPORT_C void CAknPopupForm::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CCoeControl::HandlePointerEventL( aPointerEvent );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::CountComponentControls
// Return the number of controls in the dialog
//
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknPopupForm::CountComponentControls() const
    {
    //  If the editor text is scrollable, scrollbar acts as an additional control
    if ( ( iSBFrame && iNoOfScreens > 1 ) )
        {
        return GetNumberOfLinesOnPage( ActivePageIndex() ) + 2; // plus backgroundcontext for heading and scrollbar
        }
    return GetNumberOfLinesOnPage( ActivePageIndex() ) + 1;  // plus backgroundcontext for heading desc
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ComponentControl
// Return a component at given index
//
// -----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknPopupForm::ComponentControl( TInt aIndex ) const
    {
    // First control is the extension class
    if ( aIndex == NULL )
        {
        return iExtension;
        }
    //  If the editor text is scrollable, scrollbar acts as an additional control
    else if ( ( iSBFrame && iNoOfScreens > 1 ) && aIndex == iNoOfDialogLines + 1)
        {
        return iSBFrame->VerticalScrollBar();
        }
    CEikCaptionedControl* captionedControl = GetLineByLineAndPageIndex( aIndex - 1, ActivePageIndex() );
    if ( captionedControl )
        {
        return captionedControl->iControl;
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::LabelLayout
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::LabelLayout()
    {

    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtLabel  );
    CCoeControl* coe = NULL;
    CEikLabel* head = NULL;
    if ( captionedControl )
        {
        coe = captionedControl->iControl;
        head = reinterpret_cast<CEikLabel*>( coe );
        }
    if ( head )
        {
        TAknLayoutRect headingArea;
        headingArea.LayoutRect( Rect(), AknLayoutScalable_Avkon::heading_pane( 0 ).LayoutLine());


        head->SetBrushStyle( CGraphicsContext::ENullBrush );
        TAknTextComponentLayout headingText = AknLayoutScalable_Avkon::heading_pane_t1( 0 );

        AknLayoutUtils::LayoutLabel( head,  headingArea.Rect(), headingText, iEikonEnv->NormalFont());

        // ceiklabel needs additional margins for the drawing
        head->iMargin.iBottom = head->Size().iHeight - head->Font()->HeightInPixels();
        // heading background rect
        iExtension->SetRect( headingArea.Rect() );

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TRgb color;
        TInt error = AknsUtils::GetCachedColor( skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *head,
                EColorLabelText, color ) );
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::EditorLayout
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::EditorLayout()
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtRichTextEditor );
    CEikRichTextEditor* ed = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        ed = reinterpret_cast<CEikRichTextEditor*>( coe );
        }

    if ( ed )
        {
        // update flags to get the font type
        UpdateFlags( EPopupFormEditor, ETrue );

        TRect layParent = Rect();

        TAknMultiLineTextLayout layWin;
        layWin = EditorTextLineLayout();
        if ( iFlags.IsSet( EPopupFormHasHeading ) )
            {
            TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
            TAknLayoutRect headingRect;
            headingRect.LayoutRect( Rect(), headingLayout );

            // Add the height of the heading to the position of the editor
            layParent.iTl.iY += headingRect.Rect().Height();
            }
        AknLayoutUtils::LayoutEdwin( ed, layParent, layWin, /*EAknsCIQsnTextColorsCG27*/ EAknsCIQsnTextColorsCG19 );
        CalculateNumberOfScreens();
        TRAP_IGNORE( UpdateScrollIndicatorL() );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ImageLayout
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::ImageLayout()
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtImage );
    CEikImage* img = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        img = reinterpret_cast<CEikImage*>( coe );
        }

    TAknWindowLineLayout layWin;
    // If scrollbar is enabled
    if ( TextIsScrollable() )
        {
        layWin = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_g1(8);
        }
    else
        {
        layWin = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_g1( 0 );
        }

    TRect layParent = Rect();
    if ( iFlags.IsSet( EPopupFormHasHeading ) )
        {
        TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
        TAknLayoutRect headingRect;
        headingRect.LayoutRect( Rect(), headingLayout );

        // Add the height of the heading to the position of the editor
        layParent.iTl.iY += headingRect.Rect().Height();
        }
    if ( img )
        {
        AknLayoutUtils::LayoutImage( img, layParent, layWin );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ProgressBarLayout
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::ProgressBarLayout()
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtProgInfo );
    CEikProgressInfo* pri = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        pri = reinterpret_cast<CEikProgressInfo*>( coe );
        }

    if ( pri )
        {

        TAknWindowLineLayout layWin =
               AknLayoutScalable_Avkon::wait_bar_pane_cp1( DetermineBarLayoutVariant() );
        TRect layParent = Rect();
        if ( iFlags.IsSet( EPopupFormHasHeading ) )
            {
            TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
            TAknLayoutRect headingRect;
            headingRect.LayoutRect( Rect(), headingLayout );

            // Add the height of the heading to the position of the progbar
            layParent.iTl.iY += headingRect.Rect().Height();
            }

        AknLayoutUtils::LayoutControl( pri, layParent, layWin);
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SpacerLayout
// Get layout information for the control and use this layout
// information to do the layout.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::SpacerLayout()
    {
    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtSpacer );
    CEikSpacer* space = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        space = reinterpret_cast<CEikSpacer*>( coe );
        }

    if ( space )
        {
           space->MakeVisible( EFalse );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::AnimationLayoutL
// Get layout information for the control and use this layout
// information to do the layout.
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::AnimationLayoutL()
    {
    CEikCaptionedControl* captionedControl = GetControlByControlTypeL( EPopupFormAnimation );

    CAknBitmapAnimation* ani = NULL;
    CCoeControl* coe = NULL;
    if ( captionedControl )
        {
        coe = captionedControl->iControl;
        ani = reinterpret_cast<CAknBitmapAnimation*>( coe );
        }

    TAknWindowLineLayout layWin;

    if ( ani )
        {
        // If scrollbar is enabled
        if ( TextIsScrollable() )
            {
            layWin = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_g1( 8 );
            }
        else
            {
            layWin = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_g1( 0 );
            }
        TRect layParent = Rect();
        if ( iFlags.IsSet( EPopupFormHasHeading ) )
            {
            TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
            TAknLayoutRect headingRect;
            headingRect.LayoutRect( Rect(), headingLayout );

            // Add the height of the heading to the position of the editor
            layParent.iTl.iY += headingRect.Rect().Height();
            }
        AknLayoutUtils::LayoutControl( coe, layParent, layWin);
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::WaitAnimationLayoutL
// Get layout information for the control and use this layout
// information to do the layout.
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::WaitAnimationLayoutL()
    {

    CEikCaptionedControl* captionedControl = GetControlByControlTypeL( EPopupFormWaitAnim );
    CCoeControl* coe = NULL;
    CAknBitmapAnimation* ani = NULL;
    if ( captionedControl )
        {
        coe =captionedControl->iControl;
        ani = reinterpret_cast<CAknBitmapAnimation*>( coe );
        }

    if ( ani )
        {
        TAknWindowLineLayout layWin = AknLayoutScalable_Avkon::wait_bar_pane_cp1( DetermineBarLayoutVariant() );
        TRect layParent = Rect();

        if ( iFlags.IsSet( EPopupFormHasHeading ) )
            {
            TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
            TAknLayoutRect headingRect;
            headingRect.LayoutRect( Rect(), headingLayout );

            // Add the height of the heading to the position of the wait animation
            layParent.iTl.iY += headingRect.Rect().Height();
            }

        // make sure that the wait animation fills the whole wait animation rectangle
        ani->SetScaleModeForAnimationFrames(EAspectRatioNotPreserved);

        AknLayoutUtils::LayoutControl( coe, layParent, layWin);
        }
    }
// -----------------------------------------------------------------------------
// CAknPopupForm::CalculateNumberOfScreens
// Calculate the number of screens needed to show all the text in the editor.
// Text scrolls so that the last line of the previous page is the first line
// of the new page.
// Store the value to the iNoOfScreens member.
// -----------------------------------------------------------------------------
//
void CAknPopupForm::CalculateNumberOfScreens()
    {
    if ( iFlags.IsSet ( EPopupFormHasEditor ) )
        {
        TInt maxLines = KMaxNoOfEditorLines;

        if ( !iFlags.IsSet( EPopupFormUsesPlainFont ) )
            {
            --maxLines;
            }
        CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtRichTextEditor );
        CEikRichTextEditor* ed = NULL;
        if ( captionedControl )
            {
            CCoeControl* coe = captionedControl->iControl;
            ed = reinterpret_cast<CEikRichTextEditor*>( coe );
            }
        if ( ed )
            {

            if ( ed->TextLength() >= ed->UpperFullFormattingLength() && ed->TextView() != NULL )
                {
                // Force formatting of all text
                ed->TextLayout()->SetAmountToFormat( CTextLayout::EFFormatAllText );
                TRAP_IGNORE(ed->TextView()->FormatTextL());
                TRAP_IGNORE(ed->TextView()->FinishBackgroundFormattingL());
                }

            iNoOfEditorLines = ed->TextLayout()->NumFormattedLines();

            if ( iFlags.IsSet( EPopupFormHasProgbar )
                || iFlags.IsSet( EPopupFormHasWaitAnim ) )
                {
                --maxLines;
                }
            if ( iNoOfEditorLines <= maxLines )
                {
                iNoOfScreens = 1;
                }
            else
                {
                if ( ( ( iNoOfEditorLines - 1 ) % ( maxLines - 1 ) ) == 0 )
                    {
                    iNoOfScreens = ( iNoOfEditorLines - 1 ) / ( maxLines - 1 );
                    }
                else
                    {
                    iNoOfScreens = ( iNoOfEditorLines - 1 ) / ( maxLines- 1 ) + 1;
                    }
                }

            iCurrentLine = 1;
            iExtension->iCursorLine = 1;
            TRAP_IGNORE(ed->SetCursorPosL( 0, EFalse ));
            }
        }
    else
        {
        iNoOfScreens = 1;
        iNoOfEditorLines = 0;
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::UpdateScrollIndicatorL
// Updates the scroll indicator to reflect current text position.
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::UpdateScrollIndicatorL()
    {
    if ( !iFlags.IsSet( EPopupFormHasEditor ) || iNoOfScreens <= 1 )
        {
        if ( iSBFrame )
            {
            delete iSBFrame;
            iSBFrame = NULL;
            }
        return;
        }
    if ( !iSBFrame )
        {
        iSBFrame=NULL;

        // EDoubleSpan type scrollbar
        if( AknLayoutUtils::PenEnabled() )
            {
            iSBFrame=new (ELeave) CEikScrollBarFrame( this, NULL, ETrue );
            iSBFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse, ETrue, EFalse ); // window owning scrollbar
            }
        else
            {
            iSBFrame=new (ELeave) CEikScrollBarFrame( this, NULL, ETrue );
            iSBFrame->CreateDoubleSpanScrollBarsL( EFalse, EFalse, ETrue, EFalse ); // non-window owning scrollbar
            }
        iSBFrame->SetTypeOfVScrollBar( CEikScrollBarFrame::EDoubleSpan );
        iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff,
                                           CEikScrollBarFrame::EAuto );

        }
    TRect parentRect = Rect();

    if ( AknLayoutUtils::PenEnabled() )
        {
        CEikCba* cba = static_cast<CEikCba*>(
                ButtonGroupContainer().ButtonGroup() );
        if ( cba->IsVisible() && !cba->IsEmpty() )
            {
            parentRect.iBr.iY -= cba->Rect().Height();
            }
        }

    if ( iFlags.IsSet( EPopupFormHasHeading ) )
        {
        TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
        TAknLayoutRect headingRect;
        headingRect.LayoutRect( Rect(), headingLayout );

        // Add the height of the heading to the position of the wait animation
        parentRect.iTl.iY += headingRect.Rect().Height();
        }

    AknLayoutUtils::LayoutVerticalScrollBar( iSBFrame, parentRect, AknLayoutScalable_Avkon::scroll_pane_cp17( 0 ).LayoutLine() ); //cp7 0-3 varietys
    iSBFrame->SetScrollBarFrameObserver( iExtension );
    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;
    vSbarModel.iThumbPosition = iCurrentLine - 1; // -1 because the value has already
                                                    // been incremented in OfferKeyEvent
    vSbarModel.iScrollSpan = iNoOfEditorLines;
    
    if( iFlags.IsSet( EPopupFormUsesPlainFont ) )
        {
        vSbarModel.iThumbSpan = KMaxNoOfEditorLines;
        }
    else if( iFlags.IsSet( EPopupFormWaitAnim ) || iFlags.IsSet( EPopupFormProgbar ))
    	{
    	vSbarModel.iThumbSpan = KMaxNoOfEditorLines-2;
    	}
    else
        {
    	vSbarModel.iThumbSpan = KMaxNoOfEditorLines-1;
        }
    

    TEikScrollBarFrameLayout layout;
    iSBFrame->TileL( &hSbarModel, &vSbarModel, parentRect, parentRect,layout );
    iSBFrame->SetVFocusPosToThumbPos( vSbarModel.iThumbPosition );
    iSBFrame->DrawScrollBarsNow();
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ReportUserInactivity
//
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::ReportUserActivity() const
    {
    User::ResetInactivityTime();
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::StartAnimationL
// If there is an animation, start it
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::StartAnimationL()
    {
    // We can have two animations (wait and regular).
    // Check if they exist and start them.
    CEikCaptionedControl* captionedControl = GetControlByControlTypeL( EPopupFormAnimation );
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        CAknBitmapAnimation* ani = reinterpret_cast<CAknBitmapAnimation*>( coe );
        if ( ani )
            {
            ani->StartAnimationL();
            }
        }
    CEikCaptionedControl* cap2 = GetControlByControlTypeL( EPopupFormWaitAnim );
    if ( cap2 )
        {
        CCoeControl* coe = cap2->iControl;
        CAknBitmapAnimation* ani = reinterpret_cast<CAknBitmapAnimation*>( coe );
        if ( ani )
            {
            ani->StartAnimationL();
            }
        }

    }

// -----------------------------------------------------------------------------
// CAknPopupForm::DetermineAnimationType
// Check if wait animation resource index is defined to
// to see if popupform has a wait animation.
// -----------------------------------------------------------------------------
//
TAnimationType CAknPopupForm::DetermineAnimationType( const CAknBitmapAnimation* anAnimation )
    {
    // if wait animation hasn't been defined, animation has to be of regular type
    if ( iExtension->iWaitAnimationResourceIndex < 0 )
        {
        return ERegularAnimation;
        }

    // the given control is the same as the wait animation
    if ( Control( iExtension->iWaitAnimationResourceIndex ) == anAnimation )
        {
        return EWaitAnimation;
        }
    // the given control is not wait animation, but regular animation
    else
        {
        return ERegularAnimation;
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ProgressInfo
// If there is a progress info control on the form, return it.
//
// -----------------------------------------------------------------------------
//
EXPORT_C CEikProgressInfo* CAknPopupForm::ProgressInfo()
    {
    if( iFlags.IsSet( EPopupFormHasProgbar ) )
        {
        CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtProgInfo );
        CEikProgressInfo* pri = NULL;
        if ( captionedControl )
            {
            CCoeControl* coe = captionedControl->iControl;
            pri = reinterpret_cast<CEikProgressInfo*>( coe );
            }
        return pri;
        }
    else
        {
        return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetImage
// Change the image.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetImageL( const CEikImage* aImage )
    {
    // if the parameter is null, remove the image if there is one
    if( !aImage )
        {
        if ( iFlags.IsSet ( EPopupFormHasImage ) )
            {
            DeleteControl( EEikCtImage );
            }
        return;
        }

    CEikCaptionedControl* captionedControl = GetControlByControlType( EEikCtImage );
    CEikImage* img = NULL;
    if ( captionedControl )
        {
        CCoeControl* coe = captionedControl->iControl;
        img = reinterpret_cast<CEikImage*>( coe );
        }

    if ( img )
        {
        // There must already be an image on the form.
        __ASSERT_ALWAYS( img, Panic( EAknPanicNullPointer ) );

        ClearArea( img->Rect() );

        CFbsBitmap* bitmap = new  (ELeave) CFbsBitmap();
        CleanupStack::PushL( bitmap );

        bitmap->Duplicate( aImage->Bitmap()->Handle() );
        img->SetPicture( bitmap ); // set the image

        const CFbsBitmap* maskImage = aImage->Mask();
        if( maskImage )
            {
            CFbsBitmap* mask = new (ELeave) CFbsBitmap();
            CleanupStack::PushL( mask );
            mask->Duplicate( maskImage->Handle() );
            img->SetMask(mask);
            //img->SetPicture( bitmap, mask);
            CleanupStack::Pop(); // mask
            }

        CleanupStack::Pop(); // bitmap
        LayoutAndDraw();
        }
    }
// -----------------------------------------------------------------------------
// CAknPopupForm::SetCallback
// Set the callback pointer.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetCallback( MPopupFormProgressCallback* aCallback )
    {
    iCallback = aCallback;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::OkToExitL
// Dismiss the dialog by calling the callback class' DialogDismissedL
//
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknPopupForm::OkToExitL(TInt aButtonId)
    {
    if ( aButtonId == EAknSoftkeyEmpty )
        {
        return EFalse;
        }
    if ( iCallback )
        {
        iCallback->DialogDismissedL( aButtonId );
        }
     return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ProcessFinishedL
// Called when the process the progress bar is measuring finishes.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::ProcessFinishedL()
    {
    ReportUserActivity();
    PlayTone();
    TryExitL( EAknSoftkeyDone );
    }

// -----------------------------------------------------------------------------



// CAknPopupForm::InsertControlL
// Insert a control to the popupform.
// Deprecated; use the three parameter version instead!
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::InsertControlL( const TInt aIndex, const TInt aResourceId )
    {
    InsertControlL( aIndex, aResourceId, EFalse );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::DeleteControl
// Delete control on the popupform.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::DeleteControl( const TInt aControlType )
    {
    CEikCaptionedControl* ctrl;
    ctrl = GetControlByControlType( aControlType );

    TPopupFormControlType aPFCtrl = PopupFormControlType( ctrl );
    UpdateFlags( aPFCtrl, EFalse );

    if ( ctrl )
        {
        TRAP_IGNORE( DoDeleteControlL( ctrl ) );
        }
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::UpdateFlags
// Set/clear flags.
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::UpdateFlags( const TPopupFormControlType aControlType, const TBool aInsert )
    {
    if ( aInsert )
        {
        // add a flag if needed
        switch ( aControlType )
            {
            case EPopupFormImage:
                iFlags.Set( EPopupFormHasImage );
                break;

            case EPopupFormAnimation:
                iFlags.Set( EPopupFormHasAnimation );
                break;

            case EPopupFormWaitAnim:
                iFlags.Set( EPopupFormHasWaitAnim );
                break;

            case EPopupFormHeading:
                iFlags.Set( EPopupFormHasHeading );
                break;

            case EPopupFormSpacer:
                iFlags.Set( EPopupFormHasSpacer );
                break;

            case EPopupFormProgbar:
                iFlags.Set( EPopupFormHasProgbar );
                break;

            case EPopupFormEditor:
                iFlags.Set( EPopupFormHasEditor );
                break;
            case EPopupFormUnknown:
            default:
                break;
            }
        }
    else
        {
        // remove a flag if needed
        switch ( aControlType )
            {
            case EPopupFormImage:
                iFlags.Clear( EPopupFormHasImage );
                break;

            case EPopupFormAnimation:
                iFlags.Clear( EPopupFormHasAnimation );
                break;

            case EPopupFormWaitAnim:
                iFlags.Clear( EPopupFormHasWaitAnim );
                break;

            case EPopupFormHeading:
                iFlags.Clear( EPopupFormHasHeading );
                iExtension->iHasLabelBackground = EFalse;
                break;

            case EPopupFormSpacer:
                iFlags.Clear( EPopupFormHasSpacer );
                break;

            case EPopupFormProgbar:
                iFlags.Clear( EPopupFormHasProgbar );
                break;

            case EPopupFormEditor:
                iFlags.Clear( EPopupFormHasEditor );
                break;

            case EPopupFormUnknown:
            default:
                break;
            }
        }
    // set the font type, plain font is used only  with scrollable
    // text without icon, anim or progbar
    if ( iFlags.IsSet( EPopupFormHasProgbar )
        || iFlags.IsSet( EPopupFormHasWaitAnim )
        || iFlags.IsSet( EPopupFormHasImage )
        || iFlags.IsSet( EPopupFormHasAnimation )
        || iNoOfEditorLines < KMaxNoOfEditorLines)
        {
        iFlags.Clear( EPopupFormUsesPlainFont );
        }
    else
        {
        iFlags.Set( EPopupFormUsesPlainFont );
        }
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::ClearArea
// -----------------------------------------------------------------------------
//
void CAknPopupForm::ClearArea( const TRect& aRect )
    {
    CWindowGc& gc = SystemGc();
    ActivateGc();
    gc.Clear( aRect );
    DeactivateGc();
    }


// -----------------------------------------------------------------------------
// CAknPopupForm::RedrawHeading
// -----------------------------------------------------------------------------
//
void CAknPopupForm::RedrawHeading()
    {
    if ( iFlags.IsSet( EPopupFormHasHeading ) )
        {
        CEikCaptionedControl* captionedControl = GetControlByControlType(  EEikCtLabel );
        CCoeControl* ctrl = NULL;
        if ( captionedControl )
            {
            ctrl = captionedControl->iControl;
            if ( ctrl )
                {
                ctrl->DrawNow();
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::Extension
// -----------------------------------------------------------------------------
//
CAknPopupFormExtension* CAknPopupForm::Extension()
    {
    __ASSERT_DEBUG( iExtension,
        Panic( EAknPanicObjectNotFullyConstructed ) );

    return iExtension;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::StartTimeoutTimerL
// -----------------------------------------------------------------------------
//
void CAknPopupForm::StartTimeoutTimerL()
    {
    if ( iTimeoutInSeconds > 0 )
        {
        if ( !iTimer )
            {
            TRAP_IGNORE( iTimer = CPeriodic::NewL( 0 ) );
            }
        if ( iTimer->IsActive() )
            {
            iTimer->Cancel();
            }
        TInt timeoutInMicroseconds = iTimeoutInSeconds * 1000000;
        iTimer->Start( timeoutInMicroseconds, timeoutInMicroseconds,
            TCallBack( StaticDeleteL,this ) );
        }
    else // iTimeoutInSeconds <= 0
        {
        if ( iTimer && iTimeoutInSeconds == 0 )
            {
            iTimer->Cancel();
            }
        }
    }
// -----------------------------------------------------------------------------
// CAknPopupForm::TextIsScrollable
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknPopupForm::TextIsScrollable()
    {
    return ( ( iSBFrame && iNoOfScreens > 1 ) ? ETrue : EFalse );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::Flags()
// -----------------------------------------------------------------------------
//
EXPORT_C TBitFlags& CAknPopupForm::Flags()
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::GetControlByControlTypeL
// Loop through the array and return the control of given type. If a control of
// the given type was not found, return NULL
// -----------------------------------------------------------------------------
//
EXPORT_C CEikCaptionedControl* CAknPopupForm::GetControlByControlTypeL( TPopupFormControlType aControl ) const
    {
    CEikCaptionedControl* controlPtr;
    TInt activePage = ActivePageIndex();

    // get the type of this control
    TInt controlType = ControlType( aControl );

    for ( TInt i = 0; i < iNoOfDialogLines; i++ )
        {
        controlPtr = GetLineByLineAndPageIndex( i, activePage);

        if ( controlPtr && controlPtr->iControlType == controlType )
            {
            if ( controlType == EAknCtBitmapAnimation )
                {
                // wait animation is requested and this is it
                if ( aControl == EPopupFormWaitAnim // function wants to find wait animation
                     && iExtension->iWaitAnimationResourceIndex >= 0 // wait animation exists
                     // it is the same as current control
                     && Line( iExtension->iWaitAnimationResourceIndex ) == controlPtr )
                    {
                    controlPtr->iControl->SetContainerWindowL( *this );
                    controlPtr->iControl->SetControlContext( iBrushAndPenContext );
                    return controlPtr;
                    }
                // regular animation is requested and this is it
                else if ( aControl == EPopupFormAnimation // function wants to find regular animation
                    &&  ( ( iExtension->iWaitAnimationResourceIndex < 0 ) // and wait animation doesn't exists
                        // or wait animation exist but this is not it
                        || Line( iExtension->iWaitAnimationResourceIndex ) != controlPtr ) )
                    {
                    controlPtr->iControl->SetContainerWindowL( *this );
                    controlPtr->iControl->SetControlContext( iBrushAndPenContext );
                    return controlPtr;
                    }
                // no match
                else
                    {
                    continue;
                    }
                }

            controlPtr->iControl->SetContainerWindowL( *this );
            controlPtr->iControl->SetControlContext( iBrushAndPenContext );
            return controlPtr;
            }
        }
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::DeleteControl
// Delete control from the popup form.
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::DeleteControl( const TPopupFormControlType aControl)
    {
    CEikCaptionedControl* ctrl = NULL;
    TRAP_IGNORE( { ctrl = GetControlByControlTypeL( aControl ); } );
    UpdateFlags( aControl, EFalse );
    if ( ctrl )
        {
        TRAP_IGNORE( DoDeleteControlL( ctrl ) );
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::DoDeleteControlL
// Really delete control from the popup form.
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::DoDeleteControlL( CEikCaptionedControl* aControl )
    {
    ClearArea( Rect() );

    // If editor control is deleted, the popupform formats the number of editorlines to zero
    if( aControl->iControlType == EEikCtRichTextEditor)
        {
        iNoOfEditorLines = 0;
        }
    // The location of waitanimationresourceindex is invalidated
    // when the wait animation control is destroyed
    else if ( aControl->iControlType == EAknCtBitmapAnimation )
        {
        TAnimationType animType = DetermineAnimationType( reinterpret_cast<CAknBitmapAnimation*>(
            aControl->iControl ));
        if ( animType == EWaitAnimation )
            {
            SetWaitAnimationResourceIndex( -1 );
            }
        }
    DeleteLine( aControl->iId, EFalse );
    iNoOfDialogLines = GetNumberOfLinesOnPage( ActivePageIndex() );

    CalculateNumberOfScreens();
    LayoutAndDraw();    
    TRAP_IGNORE( UpdateScrollIndicatorL() );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::ControlType
//
// -----------------------------------------------------------------------------
//
TInt CAknPopupForm::ControlType( const TPopupFormControlType aControl ) const
    {
    switch( aControl )
        {
        case EPopupFormHeading:
            return EEikCtLabel;

        case EPopupFormImage:
            return EEikCtImage;

        case EPopupFormAnimation:
            return EAknCtBitmapAnimation;

        case EPopupFormWaitAnim:
            return EAknCtBitmapAnimation;

        case EPopupFormProgbar:
            return EEikCtProgInfo;

        case EPopupFormEditor:
            return EEikCtRichTextEditor;

        case EPopupFormSpacer:
            return EEikCtSpacer;

        default:
            return KErrNotFound;
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::PopupFormControlType
//
// -----------------------------------------------------------------------------
//
TPopupFormControlType CAknPopupForm::PopupFormControlType( CEikCaptionedControl* aControl )
    {
    if ( !aControl )
        {
        return EPopupFormUnknown;
        }
    TPopupFormControlType theControlType = EPopupFormUnknown;
    switch ( aControl->iControlType )
        {
        case EEikCtImage:
            theControlType = EPopupFormImage;
            break;

        case EAknCtBitmapAnimation:
            switch ( DetermineAnimationType(
                reinterpret_cast<CAknBitmapAnimation*>( aControl->iControl ) ) )
                {
                case ERegularAnimation:
                    theControlType = EPopupFormAnimation;
                    break;
                case EWaitAnimation:
                    theControlType = EPopupFormWaitAnim;
                    break;
                }
            break;

        case EEikCtLabel:
            theControlType = EPopupFormHeading;
            break;

        case EEikCtSpacer:
            theControlType = EPopupFormSpacer;
            break;

        case EEikCtProgInfo:
            theControlType = EPopupFormProgbar;
            break;

        case EEikCtRichTextEditor:
            theControlType = EPopupFormEditor;
            break;

        default:
            theControlType = EPopupFormUnknown;
            break;
        }
    return theControlType;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::DetermineBarLayoutVariant
//
// -----------------------------------------------------------------------------
//
TInt CAknPopupForm::DetermineBarLayoutVariant() const
    {

    TInt numberOfLines = NumberOfVisibleLines();
    //  Scrollbared popup form uses different layouts
    if ( ( iSBFrame && iNoOfScreens > 1 ) )
        {
        return 7;
        }
    else
        {
        switch( numberOfLines )
            {
            case 0:
            case 1:
            case 2:
                {
                return 3;
                }
            case 3:
                {
                return 2;
                }
            case 4:
            default:
                {
                return 0;
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetWaitAnimationResourceIndex
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::SetWaitAnimationResourceIndex( const TInt aIndex )
    {
    iExtension->iWaitAnimationResourceIndex = aIndex;
    }
// -----------------------------------------------------------------------------
// CAknPopupForm::InsertControlL
// Insert control with info whether it is a wait animation or not
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknPopupForm::InsertControlL( const TInt aIndex, const TInt aResourceId, const TBool aIsWaitAnimation )
    {
    TInt activePage = ActivePageIndex();

    InsertLineL( aIndex, aResourceId, activePage );

    CEikCaptionedControl* ctrl = ( CEikCaptionedControl* )
                          GetLineByLineAndPageIndex( aIndex, activePage );
    if ( !ctrl )
        {
        return;
        }
    ctrl->SetContainerWindowL( *this );
    ctrl->SetMopParent( this );
    ctrl->SetDrawNoWhiteBackground( ETrue );
    ctrl->SetControlContext( iBrushAndPenContext );
    iNoOfDialogLines = GetNumberOfLinesOnPage( activePage );

    TPopupFormControlType ctrlType;
    if( ctrl->iControlType == EAknCtBitmapAnimation )
        {
        if( aIsWaitAnimation )
            {
            ctrlType = EPopupFormWaitAnim;
            SetAnimationSize( EPopupFormWaitAnim, ctrl );
            SetWaitAnimationResourceIndex( ctrl->iId );
            }
        else
            {
            ctrlType = EPopupFormAnimation;
            SetAnimationSize( EPopupFormAnimation, ctrl );
            }
        }
    else
        {
        ctrlType = PopupFormControlType( ctrl );

        // background context for the label
      if ( ctrlType == EPopupFormHeading && !iExtension->iHasLabelBackground )
            {
                iExtension->iHasLabelBackground = ETrue;
                iExtension->SetRect( Rect() );
                iExtension->SetParent( this );
                iExtension->SetControlContext( iBrushAndPenContext );
            }
        }


    UpdateFlags( ctrlType, ETrue );

    CalculateNumberOfScreens();
    LayoutAndDraw();
    UpdateScrollIndicatorL();

    if( ctrl->iControlType == EAknCtBitmapAnimation && IsActivated() )
        {
        CAknBitmapAnimation* ani = reinterpret_cast<CAknBitmapAnimation*>( ctrl->iControl );
        if ( ani )
            {
            ani->StartAnimationL();
            }
        }
    }


TInt CAknPopupForm::NumberOfVisibleLines() const
    {

    TInt maxLines = KMaxNoOfEditorLines;
    if ( !iFlags.IsSet( EPopupFormUsesPlainFont ) )
        {
        // bold font
        maxLines--;

        if ( iFlags.IsSet( EPopupFormHasProgbar )
             || iFlags.IsSet( EPopupFormHasWaitAnim ) )
             {
             maxLines--;
             }
        }
    return Min( maxLines, iNoOfEditorLines );
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::SetAnimationSize
//
// -----------------------------------------------------------------------------
//
void CAknPopupForm::SetAnimationSize( TPopupFormControlType aType, CEikCaptionedControl* anAnimation )
    {
    if ( !anAnimation )
        {
        return;
        }

    CAknBitmapAnimation* ani = reinterpret_cast<CAknBitmapAnimation*>( anAnimation->iControl );
    if( ani )
        {
        // Get the right rect for the animation
        // (before it necessarily has been calculated in SetSizeAndPosition)
        TRect parentRect = PopupWindowRect();

        TAknLayoutRect layoutWindow;
        if( aType == EPopupFormWaitAnim )
            {
            layoutWindow.LayoutRect( parentRect, AknLayoutScalable_Avkon::wait_bar_pane_cp1( DetermineBarLayoutVariant() ) );
            }
        else
            {
            layoutWindow.LayoutRect( parentRect, AknLayoutScalable_Avkon::popup_midp_note_alarm_window_g1( 0 ) );
            }
        TRect animRect( layoutWindow.Rect() );

        TInt endFrame = ani->BitmapAnimData()->FrameArray().Count() - 1;

        for ( TInt i=0; i<=endFrame; i++ )
            {
            CFbsBitmap* bit = ani->BitmapAnimData()->FrameArray().At( i )->Bitmap();
            AknIconUtils::SetSize(bit, animRect.Size() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::EditorTextLineLayout
//
// -----------------------------------------------------------------------------
//
TAknMultiLineTextLayout CAknPopupForm::EditorTextLineLayout()
    {
    TInt numberOfLines = NumberOfVisibleLines();
    TInt firstVariant = 3;

    TAknTextComponentLayout firstlineLayout;
    TAknTextComponentLayout secondlineLayout;

    // If no other controls inside dialog than text editor
    if ( !( iFlags.IsSet( EPopupFormHasProgbar )
                    || iFlags.IsSet( EPopupFormHasWaitAnim ) ) &&
                  !( iFlags.IsSet( EPopupFormHasImage )
                    || iFlags.IsSet( EPopupFormHasAnimation ) ) )
        {
        firstlineLayout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_t6( 0 );
        secondlineLayout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_t7( 0 );
        }
    else
        {
        // If uses scrollbar
        if ( TextIsScrollable() )
                {
                // Image
                if ( iFlags.IsSet( EPopupFormHasImage ) || iFlags.IsSet( EPopupFormHasAnimation ) )
                    {
                    firstVariant = 12;
                    }
                // Progress bar, no image
                else
                    {
                    firstVariant = 11;
                    }
                }
        else
            {
                // Image
                if ( iFlags.IsSet( EPopupFormHasImage ) || iFlags.IsSet( EPopupFormHasAnimation ) )
                    {
                    firstVariant = 0;
                    }
                // Progress bar, no image
                else
                    {
                    firstVariant = 4;
                    }
            }
        firstlineLayout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_t1( firstVariant );
        secondlineLayout = AknLayoutScalable_Avkon::popup_midp_note_alarm_window_t2( firstVariant );
        }

    TAknTextLineLayout fLayout = firstlineLayout.LayoutLine();

    TAknMultiLineTextLayout multiline;
    multiline.iC = fLayout.iC;
    multiline.il = fLayout.il;
    multiline.ir = fLayout.ir;
    multiline.iW = fLayout.iW;
    multiline.iJ = fLayout.iJ;
    multiline.iFont = fLayout.iFont;
    multiline.iB = fLayout.iB;

    if ( numberOfLines >= 2 )
        {
        TAknTextLineLayout sLayout = secondlineLayout.LayoutLine();
        multiline.iBaselineSkip = secondlineLayout.t() - firstlineLayout.t();
        multiline.iNumberOfLinesShown = numberOfLines;
        }
    else
        {
        multiline.iBaselineSkip = 0;
        multiline.iNumberOfLinesShown = 1;
        }
    return multiline;
    }

// -----------------------------------------------------------------------------
// CAknPopupForm::PopupWindowRect
//
// -----------------------------------------------------------------------------
//
TRect CAknPopupForm::PopupWindowRect() const
    {
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPaneRect );

    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
    TInt variety( 0 );

    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
        {
        variety = 3;
        }
    else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
        {
        variety = 6;
        }
    else
        {
        variety = 0;
        }
    TAknLayoutRect popupWindow;
    popupWindow.LayoutRect( mainPaneRect, AknLayoutScalable_Avkon::popup_note_window( variety ) );

    TRect popupRect = popupWindow.Rect();
    if ( iFlags.IsSet ( EPopupFormHasHeading ) )
        {

        TAknWindowLineLayout headingLayout = AknLayoutScalable_Avkon::heading_pane( 0 );
        TAknLayoutRect headingRect;
        headingRect.LayoutRect( popupRect, headingLayout );
        if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight || cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
            {
            popupRect.iTl.iY -= headingRect.Rect().Height() / 2;
            popupRect.iBr.iY += headingRect.Rect().Height() / 2;

            }
        else
            {
            popupRect.iTl.iY -= headingRect.Rect().Height();
            }
        }

    return popupRect;
    }



// End of file
