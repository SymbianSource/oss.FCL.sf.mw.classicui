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
* Description:  Implementation for the default control in the
*                status pane's title pane.
*
*/


// SYSTEM INCLUDE FILES
#include <eikclbd.h>
#include <eikfutil.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikspane.h>
#include <apgcli.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <gulalign.h>
#include <avkon.rsg>
#include <AknLayout.lag>
#include <AknsDrawUtils.h>
#include <AknBidiTextUtils.h>
#include <PUAcodes.hrh>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <eikenv.h>
#include <layoutmetadata.cdl.h>

#include <AknTasHook.h>
// USER INCLUDE FILES
#include "aknappui.h"
#include "AknUtils.h"
#include "avkon.hrh"
#include "AknPanic.h"
#include "akntitle.h"
#include "aknconsts.h"
#include "AknStatuspaneUtils.h"
#include "AknTitlePaneLabel.h"
#include "AknTitlePaneObserver.h"
#include "aknnavi.h"
#include "aknnavide.h"

// Titlepane flags
enum TTitlePaneControlFlags
    {
    EAknTitlePaneButton1DownInTitleRect = 0x00000001
    };

// Scrolling related constants
const TInt KScrollPauseBeforeScroll     = 1000000; // 1.0s
const TInt KScrollPauseBeforeFadeOut    = 2000000; // 2s
const TInt KScrollPauseBeforeFadeIn     = 500000;  // 0.5s
const TInt KScrollFadeInFadeOutDuration = 1000000; // 1s

const TInt KTitleMaxLines = 2;

NONSHARABLE_CLASS( CAknTitlePaneExtension )
    : public CBase,
      public MAknPictographAnimatorCallBack
    {
public:
    static CAknTitlePaneExtension* NewL( CAknTitlePane& aOwner );
    ~CAknTitlePaneExtension();

private: // From MAknPictographAnimatorCallBack
    void DrawPictographArea();

private:
    CAknTitlePaneExtension( CAknTitlePane& aOwner );
    void ConstructL();

public:
    CAknTitlePane&           iOwner;
    CEikImage*               iTitleImage;
    CAknPictographInterface* iPictoInterface;

    TInt                     iFlags;

    TBool                    iSmallImageShown;
    TBool                    iScrollEffectEnabled;
    TBool                    iScrollEffectNeeded;
    TInt                     iCurrentNumberOfTextLines;
    TInt                     iLimitedNumberOfTextLines;

    TBool                    iImageAutoscaling;
    TBool                    iSmallImageAutoscaling;
    };


// ----------------------------------------------------------------------------
// CAknTitlePaneExtension::NewL
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknTitlePaneExtension* CAknTitlePaneExtension::NewL( CAknTitlePane& aOwner )
    {
    CAknTitlePaneExtension* self =
        new( ELeave ) CAknTitlePaneExtension( aOwner );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }


// ----------------------------------------------------------------------------
// CAknTitlePaneExtension::~CAknTitlePaneExtension
// Destructor.
// ----------------------------------------------------------------------------
//
CAknTitlePaneExtension::~CAknTitlePaneExtension()
    {
    delete iTitleImage;
    delete iPictoInterface;
    }


// ----------------------------------------------------------------------------
// CAknTitlePaneExtension::CAknTitlePaneExtension
// C++ constructor.
// ----------------------------------------------------------------------------
//
CAknTitlePaneExtension::CAknTitlePaneExtension( CAknTitlePane& aOwner )
    : iOwner( aOwner )
    {
    }


// ----------------------------------------------------------------------------
// CAknTitlePaneExtension::ConstructL
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
void CAknTitlePaneExtension::ConstructL()
    {
    iTitleImage = new( ELeave ) CEikImage;
    iTitleImage->SetContainerWindowL( iOwner );
    iTitleImage->SetNonFocusing();
    iTitleImage->ActivateL();

    // Returns NULL if not supported.
    iPictoInterface = CAknPictographInterface::NewL( iOwner, *this );
    iScrollEffectEnabled = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknTitlePaneExtension::DrawPictographArea
// Draws the pictographs.
// ----------------------------------------------------------------------------
//
void CAknTitlePaneExtension::DrawPictographArea()
    {
    iOwner.DrawDeferred();
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::CAknTitlePane
// Default constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknTitlePane::CAknTitlePane()
    {
    AKNTASHOOK_ADD( this, "CAknTitlePane" );
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::~CAknTitlePane
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknTitlePane::~CAknTitlePane()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );

    delete iTitleText;
    delete iDefaultTitleText;
    delete iTitleLabel;
    delete iExtension;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::ConstructL
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::ConstructL()
    {
    CommonConstructL();
    SetTextToDefaultL();

    if ( AknLayoutUtils::PenEnabled() )
        {
        // set flags to default values
        iExtension->iFlags = 0;
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::ConstructFromResourceL
// Resource constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::ConstructFromResourceL( TResourceReader& aReader )
    {
    CommonConstructL();
    ReadFromResourceFileL( aReader );
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetTextL
// Sets the title pane text.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetTextL( const TDesC& aText )
    {
    SetText( aText.AllocL(), EFalse );
    }



// ----------------------------------------------------------------------------
// CAknTitlePane::SetText
// Sets the title pane text.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetText( HBufC* aText )
    {
    SetText( aText, EFalse );
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetSmallPicture
// Sets the small title pane picture.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetSmallPicture( const CFbsBitmap* aBitmap,
                                              const CFbsBitmap* aMaskBitmap,
                                              TBool aVisible )
    {
    if ( iExtension->iTitleImage )
        {
        // If NULL image is given, previous (existing) image is shown.
        if ( aBitmap )
            {
            iExtension->iTitleImage->SetPictureOwnedExternally( EFalse );
            iExtension->iTitleImage->SetPicture( aBitmap, aMaskBitmap );

            if ( iExtension->iTitleImage->Bitmap() &&
                 iExtension->iTitleImage->Bitmap()->SizeInPixels() == TSize( 0, 0 ) )
                {
                // Picture is scaled by title pane if the bitmap's
                // size is not set.
                iExtension->iSmallImageAutoscaling = ETrue;
                }
            else
                {
                iExtension->iSmallImageAutoscaling = EFalse;
                }
            }

        if ( aVisible )
            {
            iExtension->iSmallImageShown = ETrue;
            iImageShown = EFalse;
            }
        else
            {
            iExtension->iSmallImageShown = EFalse;
            iImageShown = EFalse;
            }

        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetPicture
// Sets the large title pane picture (operator logo).
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetPicture( const CFbsBitmap* aBitmap,
                                         const CFbsBitmap* aMaskBitmap )
    {
    if ( iExtension && iExtension->iTitleImage )
        {
        // If NULL image is given, previous (existing) image is shown.
        if ( aBitmap )
            {
            iExtension->iTitleImage->SetPictureOwnedExternally( EFalse );
            iExtension->iTitleImage->SetPicture( aBitmap, aMaskBitmap );

            if ( iExtension->iTitleImage->Bitmap() &&
                 iExtension->iTitleImage->Bitmap()->SizeInPixels() == TSize( 0, 0 ) )
                {
                // Picture is scaled by title pane if the bitmap's
                // size is not set.
                iExtension->iImageAutoscaling = ETrue;
                }
            else
                {
                iExtension->iImageAutoscaling = EFalse;
                }
            }

        iImageShown = ETrue;
        iExtension->iSmallImageShown = EFalse;
        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetSmallPictureFromFileL
// Sets the small title pane picture from a file.
// Used by the resource constructor.
// ----------------------------------------------------------------------------
//
void CAknTitlePane::SetSmallPictureFromFileL( const TDesC& aFileName,
                                              TInt aMainId,
                                              TInt aMaskId )
    {
    if ( iExtension && iExtension->iTitleImage )
        {
        CEikImage*& img = iExtension->iTitleImage;
        delete img;
        img = NULL;

        img = new (ELeave) CEikImage;
        img->CreatePictureFromFileL( aFileName, aMainId, aMaskId );

        iImageShown = EFalse;
        iExtension->iSmallImageShown = ETrue;

        iExtension->iTitleImage->SetPictureOwnedExternally( EFalse );

        if ( iExtension->iTitleImage->Bitmap() &&
             iExtension->iTitleImage->Bitmap()->SizeInPixels() == TSize( 0, 0 ) )
                {
                // Picture is scaled by title pane if the bitmap's
                // size is not set.
                iExtension->iSmallImageAutoscaling = ETrue;
                }
            else
                {
                iExtension->iSmallImageAutoscaling = EFalse;
                }

        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetPictureFromFileL
// Sets the large title pane picture (operator logo) from a file.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetPictureFromFileL( const TDesC& aFileName,
                                                  TInt aMainId,
                                                  TInt aMaskId )
    {
    CEikImage*& img = iExtension->iTitleImage;

    delete img;
    img = NULL;

    img = new (ELeave) CEikImage;
    img->SetContainerWindowL( *this );
    img->SetNonFocusing();
    img->ActivateL();
    img->CreatePictureFromFileL( aFileName, aMainId, aMaskId );

    iImageShown = ETrue;
    iExtension->iSmallImageShown = EFalse;

    if ( iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         iExtension->iTitleImage->Bitmap()->SizeInPixels() == TSize( 0, 0 ) )
        {
        iExtension->iImageAutoscaling = ETrue;
        }
    else
        {
        iExtension->iImageAutoscaling = EFalse;
        }

    SizeChanged();
    DrawDeferred();
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetFromResourceL
// Sets the title pane content from a resource.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetFromResourceL( TResourceReader& aReader )
    {
    if ( !iTitleLabel && !iExtension ) // not constructed yet
        {
        ConstructFromResourceL( aReader );
        }
    else // update from resource
        {
        ReadFromResourceFileL(aReader);
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetTextToDefaultL
// Sets the title pane text to default (application name).
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetTextToDefaultL()
    {
    iExtension->iScrollEffectEnabled = EFalse;

    if ( iDefaultTitleText )
        {
        SetTextL( *iDefaultTitleText );
        return;
        }

    TBool textSet = EFalse;
    RApaLsSession lsSession;
    TInt ret = lsSession.Connect();
    if ( ret == KErrNone )
        {
        CleanupClosePushL( lsSession );
        TApaAppInfo appInfo;
        ret = lsSession.GetAppInfo( appInfo, AppUid() );
        if ( ret == KErrNone )
            {
            iDefaultTitleText = appInfo.iCaption.AllocL();
            SetTextL( *iDefaultTitleText );
            textSet = ETrue;
            }
        CleanupStack::PopAndDestroy( &lsSession);
        }

    if ( !textSet )
        {
        SetTextL( KTitlePaneDefaultText );
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::PrepareContext
// Updates the text color for the window context from skin.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::PrepareContext( CWindowGc& aGc ) const
    {
    if ( !iImageShown )
        {
        TRgb color;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TInt error = AknsUtils::GetCachedColor( skin,
                                                color,
                                                KAknsIIDQsnTextColors,
                                                EAknsCIQsnTextColorsCG1 );
        if ( !error )
            {
            aGc.SetPenColor( color );
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SizeChanged
// Handles size change events.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SizeChanged()
    {
    // No fading if staconpane is active, because status pane
    // and control pane are combined.
    SetContainerWindowNonFading( AknStatuspaneUtils::StaconPaneActive() );

    // If fonts are destroyed with ENV destruction sequence, then abort.
    // TBD is a way to detect it right, we use this hack instead for now.
    if ( !( iEikonEnv->Alert() ) )
        {
        return;
        }

    TInt spLayout( AknStatuspaneUtils::CurrentStatusPaneLayoutResId() );
    
    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        SizeChangedInStaconPane();
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        SizeChangedInFlatStatusPane();
        }
    else if ( AknStatuspaneUtils::ExtendedLayoutActive() ||
              spLayout == R_AVKON_STATUS_PANE_LAYOUT_VT ||
              spLayout == R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED )
        {
        // Use the extended title pane layout also for
        // the video telephony status pane layout, since
        // two-row title text is no longer supported.
        SizeChangedInExtendedStatusPane();
        }
    else
        {
        SizeChangedInNormalStatusPane();
        }
        
    // Update also the navi pane size, because in flat status pane layout
    // it draws part of the title pane if narrow navi pane
    // layout is in use.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* naviPane = NULL;
        
        TRAP_IGNORE(
            naviPane = statusPane->ContainerControlL(
                TUid::Uid( EEikStatusPaneUidNavi ) ) );
        
        if ( naviPane )
            {
            naviPane->DrawDeferred();
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::PositionChanged
// Handles position change events.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::HandleResourceChange
// Handles resource change events.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KEikColorResourceChange ||
         aType == KAknsMessageSkinChange )
        {
        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::CountComponentControls
// Returns the amount of component controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTitlePane::CountComponentControls() const
    {
    TInt controls( 0 );

    if ( ( AknStatuspaneUtils::StaconPaneActive() ||
           AknStatuspaneUtils::FlatLayoutActive() ||
           AknStatuspaneUtils::ExtendedLayoutActive()) &&
           !iImageShown )
        {
        // Both small image and text can be show simultaneusly
        if ( iTitleLabel )
            {
            controls++;
            }

        if ( iExtension->iSmallImageShown &&
             iExtension->iTitleImage )
            {
            controls++;
            }
        }
    else
        {
        // Only image or text can be shown simultaneusly
        if ( ( iImageShown &&
               iExtension->iTitleImage ) ||
             ( !iImageShown && iTitleLabel ) )
            {
            controls++;
            }
        }

    return controls;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::ComponentControl
// Gets a component control by a control index.
// ----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknTitlePane::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* componentControl = NULL;

    if ( ( AknStatuspaneUtils::StaconPaneActive() ||
           AknStatuspaneUtils::FlatLayoutActive() ||
           AknStatuspaneUtils::ExtendedLayoutActive() ) &&
         !iImageShown )
        {
        // Both image and text can be show simultaneusly
        if ( aIndex == 0 && iExtension->iSmallImageShown )
            {
            componentControl = iExtension->iTitleImage;
            }
        else
            {
            componentControl = iTitleLabel;
            }
        }
    else
        {
        // Only image or text can be shown simultaneusly
        if ( iImageShown )
            {
            componentControl = iExtension->iTitleImage;
            }
        else
            {
            componentControl = iTitleLabel;
            }
        }

    return componentControl;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::Draw
// Draws the title pane.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::Draw( const TRect& aRect ) const
    {
    const TUid KActiveIdle2Uid = {0x102750F0};

    if ( AppUid() == KActiveIdle2Uid )
        {
        CWindowGc& gc = SystemGc();
        TRgb rgb(TRgb::Color16MA(0));
        gc.SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetBrushColor(rgb);
        gc.Clear( aRect );
        return;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TRect rect( Rect() );

    CWindowGc& gc=SystemGc();

    if ( AknStatuspaneUtils::StaconPaneActive() ||
         AknStatuspaneUtils::FlatLayoutActive() )
        {
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

        if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
            {
            gc.SetPenStyle( CGraphicsContext::ENullPen );
            gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
            gc.SetBrushColor(
                AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
            gc.DrawRect( rect );
            }
        }
    else
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor( AKN_LAF_COLOR( KStatusPaneBackgroundColor ) );
        AknsDrawUtils::Background( skin,
                                   AknsDrawUtils::ControlContext( this ),
                                   this,
                                   gc,
                                   rect );
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::CommonConstructL
// Common second-phase constructor for normal and resource construction.
// ----------------------------------------------------------------------------
//
void CAknTitlePane::CommonConstructL()
    {
    iTitleLabel = new (ELeave) CAknTitlePaneLabel;
    // we do logical to visual conversion ourselves while wrapping text
    iTitleLabel->UseLogicalToVisualConversion( EFalse );

    iExtension = CAknTitlePaneExtension::NewL( *this );

    if ( iExtension->iPictoInterface )
        {
        iTitleLabel->SetPictographInterface( *iExtension->iPictoInterface );
        }

    iTitleLabel->SetContainerWindowL( *this );
    iTitleLabel->SetNonFocusing();
    iTitleLabel->ActivateL();

    // Observer is needed with pensupport
    iTitlePaneObserver = NULL;

    SetControlContext( this );
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::AppUid
// Gets the application UID.
// ----------------------------------------------------------------------------
//
TUid CAknTitlePane::AppUid() const
    {
    CEikApplication* app = iEikonEnv->EikAppUi()->Application();
    if ( app )
        {
        return app->AppDllUid();
        }
    else
        {
        return KNullUid;
        }
    }


NONSHARABLE_CLASS( CTextLayoutManager ) : public CBase
    {
public:
    enum TLayout
        {
        ENoLayout,
        EOneLineLayout,
        ETwoLineLayout
        };

public:
    CTextLayoutManager( const TInt aOneLineLayoutWidth,
                        const TInt aTwoLineLayoutWidth,
                        const CFont* aOneLineFont,
                        const CFont* aTwoLineFont )
      : iOneLineWidth( aOneLineLayoutWidth ),
        iTwoLineWidth( aTwoLineLayoutWidth ),
        iOneLineFont( aOneLineFont ),
        iTwoLineFont( aTwoLineFont )
        {}

    static CTextLayoutManager* NewLC( const TInt aOneLineLayoutWidth,
                                      const TInt aTwoLineLayoutWidth,
                                      const CFont* aOneLineFont,
                                      const CFont* aTwoLineFont );
    void ConstructL();
    ~CTextLayoutManager();

    void Reset();
    void DoLayoutL( TInt aLineNum, const TDesC& aText );
    const TLayout& Layout() const;

    TInt Lines() const;
    const TDesC& Text() const;

private:
    TInt                  iOneLineWidth;
    TInt                  iTwoLineWidth;
    const CFont*          iOneLineFont; // not owned
    const CFont*          iTwoLineFont; // not owned

    CArrayFixFlat<TInt>*  iLineWidthArray;
    HBufC*                iText;
    TLayout               iLayout;

    };


CTextLayoutManager* CTextLayoutManager::NewLC( const TInt aOneLineLayoutWidth,
                                               const TInt aTwoLineLayoutWidth,
                                               const CFont* aOneLineFont,
                                               const CFont* aTwoLineFont )
    {
    CTextLayoutManager* self = new (ELeave) CTextLayoutManager(
        aOneLineLayoutWidth, aTwoLineLayoutWidth, aOneLineFont, aTwoLineFont );
    CleanupStack::PushL( self );

    self->ConstructL();
    return self;
    }


void CTextLayoutManager::ConstructL()
    {
    iLineWidthArray = new (ELeave) CArrayFixFlat<TInt>( KTitleMaxLines );
    }


CTextLayoutManager::~CTextLayoutManager()
    {
    if ( iLineWidthArray )
        {
        iLineWidthArray->Reset();
        }

    delete iLineWidthArray;
    delete iText;
    }


void CTextLayoutManager::Reset()
    {
    delete iText;
    iText = NULL;

    if ( iLineWidthArray )
        {
        iLineWidthArray->Reset();
        }
    iLayout = ENoLayout;
    }


void CTextLayoutManager::DoLayoutL( TInt aLineNum, const TDesC& aText )
    {
    __ASSERT_DEBUG( aLineNum == 1 || aLineNum == 2,
                    Panic( EAknPanicNotSupported ) );

    __ASSERT_DEBUG( iLineWidthArray->Count() == 0,
                    Panic( EAknPanicSelfCheckFailure ) );

    const CFont* font = NULL;

    if ( aLineNum == 1 )
        {
        iLineWidthArray->AppendL( iOneLineWidth );
        if ( iTwoLineWidth )
            {
            // Added only if there exists 2nd line.
            iLineWidthArray->AppendL( iTwoLineWidth );
            }
        font    = iOneLineFont;
        iLayout = EOneLineLayout;
        }
    else
        {
        iLineWidthArray->AppendL( iOneLineWidth );
        if ( iTwoLineWidth )
            {
            // Added only if there exists 2nd line.
            iLineWidthArray->AppendL( iTwoLineWidth );
            }
        font    = iTwoLineFont;
        iLayout = ETwoLineLayout;
        }

    __ASSERT_DEBUG( iText == NULL, Panic( EAknPanicNullPointer ) );

    if ( !iText )
        {
        // +1 is for line ends
        iText = HBufC::NewL(
            aText.Length() + KTitleMaxLines * (KAknBidiExtraSpacePerLine + 1) );
        }

    TPtr ptr = iText->Des();
    AknBidiTextUtils::ConvertToVisualAndWrapToStringL(
        aText, *iLineWidthArray, *font, ptr, ETrue );

    }


/**
 * Return type of layout set in DoLayout operation, either one line
 * layout or two line layout.
 */
const CTextLayoutManager::TLayout& CTextLayoutManager::Layout() const
    {
    return iLayout;
    }


/**
 * Return number of lines by locating \n chars
 * in the text. These have been inserted by wrapping
 * algorithm.
 */
TInt CTextLayoutManager::Lines() const
    {
    __ASSERT_DEBUG( iText, Panic( EAknPanicNullPointer ) );
    TInt nLines = 0;
    TInt pos = iText->Length();

    do
        {
        TPtrC ptrC( iText->Left( pos ) );
        pos = ptrC.LocateReverseF( '\n' );
        }
    while ( pos >= 0 && ++nLines );
    return nLines;
    }


const TDesC& CTextLayoutManager::Text() const
    {
    __ASSERT_DEBUG( iText, Panic( EAknPanicNullPointer ) );
    return *iText;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::FormatTitlePaneLabelL
// Formats the title pane text.
// ----------------------------------------------------------------------------
//
TInt CAknTitlePane::FormatTitlePaneLabelL( const TInt aOneLineLayoutWidth,
                                           const TInt aTwoLineLayoutWidth,
                                           const CFont* aOneLineFont,
                                           const CFont* aTwoLineFont )
    {
    if ( !iTitleLabel )
        {
        return 0;
        }

    if ( Rect().Width() < 1 )
        {
        iTitleLabel->SetTextL( *iTitleText );
        return 0;
        }

    TPtr ptr( iTitleText->Des() );
    TBuf<1> stripCharacters;
    stripCharacters.Append( KPuaCodeLineFeedSymbol );
    AknTextUtils::StripCharacters( ptr, stripCharacters );

    // Check if 2nd line usage has been limited
    TInt oneLineLayoutWidth = aOneLineLayoutWidth;
    TInt twoLineLayoutWidth = aTwoLineLayoutWidth;
    if ( iExtension && iExtension->iLimitedNumberOfTextLines > 0 &&
         iExtension->iLimitedNumberOfTextLines < MaxNumberOfVisibleTextRows() )
        {
        twoLineLayoutWidth = 0;
        }

    // We remove control chars here if one line layout is in use,
    // but we don't touch the original text because if we go to
    // 2-line layout we would not have the line feeds anymore
    // that some text may contain.
    HBufC* titleText = iTitleText->AllocLC();

    if ( twoLineLayoutWidth == 0 )
        {
        iTitleLabel->ReplaceControlCharacters( titleText, ETrue );
        }
    else
        {
        iTitleLabel->ReplaceControlCharacters( titleText, EFalse );
        }

    CTextLayoutManager* layoutMgr = CTextLayoutManager::NewLC(
        oneLineLayoutWidth, twoLineLayoutWidth, aOneLineFont, aTwoLineFont );

    layoutMgr->DoLayoutL( 1, *titleText );
    if ( layoutMgr->Lines() > 1 )
        {
        layoutMgr->Reset();
        layoutMgr->DoLayoutL( 2, *titleText );
        }

    const CTextLayoutManager::TLayout& layout( layoutMgr->Layout() );

    TInt lines =
        layout == CTextLayoutManager::ETwoLineLayout ? 2 : layoutMgr->Lines();

    iTitleLabel->SetTextL( layoutMgr->Text() );

    TBool truncated = iTitleLabel->Text()->Locate( KEllipsis ) != KErrNotFound;

    if ( iExtension )
        {
        iExtension->iCurrentNumberOfTextLines = lines;
        }

    if ( iExtension )
        {
        iExtension->iScrollEffectNeeded = truncated;
        }

    CleanupStack::PopAndDestroy( 2, titleText ); // titleText, layoutMgr
    return lines;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::ReadFromResourceFileL
// Updates title pane content from a resource file.
// ----------------------------------------------------------------------------
//
void CAknTitlePane::ReadFromResourceFileL( TResourceReader& aReader )
    {
    if ( iTitleLabel )
        {
        iTitleLabel->InvalidateText();
        }

    delete iTitleText;
    iTitleText = NULL;
    iTitleText = aReader.ReadHBufCL();

    HBufC* bitmapFile = aReader.ReadHBufCL(); // bmp filename
    TInt bitmapId     = aReader.ReadInt16();  // bmp id
    TInt maskId       = aReader.ReadInt16();  // bmp mask id

    if ( !iTitleText )
        {
        if ( bitmapFile )
            {
            CleanupStack::PushL( bitmapFile );
            if ( bitmapId != KErrNotFound )
                {
                SetPictureFromFileL( *bitmapFile, bitmapId, maskId );
                }
            else
                {
                SetTextToDefaultL();
                }
            CleanupStack::PopAndDestroy( bitmapFile );
            }
        else
            {
            SetTextToDefaultL();
            }
        }
    else
        {
        if ( bitmapFile )
            {
            CleanupStack::PushL( bitmapFile );
            if ( bitmapId != KErrNotFound )
                {
                SetSmallPictureFromFileL( *bitmapFile, bitmapId, maskId );
                }
            else
                {
                SetTextToDefaultL();
                }
            CleanupStack::PopAndDestroy( bitmapFile );
            }

        iImageShown = EFalse;
        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SizeChangedInNormalStatusPane
// Handles size change events in normal status pane layout.
// ----------------------------------------------------------------------------
//
void CAknTitlePane::SizeChangedInNormalStatusPane()
    {
    AknsUtils::RegisterControlPosition( this );

    TRect rect( Rect() );

    if ( iTitleLabel && !iImageShown )
        {
        __ASSERT_DEBUG( iTitleText, Panic( EAknPanicNullPointer ) );

        TInt indexW( 0 );
        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {   // Is battery pane visible in current layout
            indexW = 1;
            }

        TAknTextLineLayout oneLineLayout(
            AknLayoutScalable_Avkon::title_pane_t1( 0 ).LayoutLine() );

        const TAknMultiLineTextLayout twoLineLayout(
            AKN_LAYOUT_MULTILINE_TEXT_Title_pane_texts_Line_2( indexW, 2 ) );

        // if text would truncate, then try to use
        // smaller font with one line layout
        if ( !TextFits( oneLineLayout ) )
            {
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t2( 1 ).LayoutLine();
            }

        TAknLayoutText oneLineLayoutText;
        oneLineLayoutText.LayoutText( rect, oneLineLayout);
        TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

        TAknLayoutText twoLineLayoutText;
        twoLineLayoutText.LayoutText( rect, twoLineLayout);
        TRect twoLineLayoutRect( twoLineLayoutText.TextRect() );

        TInt lines = 0;
        
        TRAP_IGNORE(
            lines = FormatTitlePaneLabelL(
                oneLineLayoutRect.Width(),
                twoLineLayoutRect.Width(),
                AknLayoutUtils::FontFromId( oneLineLayout.FontId() ),
                AknLayoutUtils::FontFromId( twoLineLayout.FontId() ) )
            ); // Ignore leave. Only layout of the title pane
               // suffers if leave happens.

        if ( lines <= 1 )
            {
            AknLayoutUtils::LayoutLabel( iTitleLabel, rect, oneLineLayout );
            }
        else
            {
            AknLayoutUtils::LayoutLabel( iTitleLabel, rect, twoLineLayout );
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;

        TInt error = AknsUtils::GetCachedColor( skin,
                                                color,
                                                KAknsIIDQsnTextColors,
                                                EAknsCIQsnTextColorsCG1 );

        if ( !error )
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                *iTitleLabel, EColorLabelText, color ) );
            }

        if ( iExtension &&
             ( iExtension->iScrollEffectEnabled ||
               iTitleLabel->TextEffect() ||
               !iTitleLabel->EffectQueueIsEmpty() ) )
            {
            TRAP_IGNORE( SetupTitleLabelEffectL() );
            if ( !iTitleLabel->TextEffect() )
                {
                if ( lines <= 1 )
                    {
                    AknLayoutUtils::LayoutLabel( iTitleLabel,
                                                 rect,
                                                 oneLineLayout );
                    }
                else
                    {
                    AknLayoutUtils::LayoutLabel( iTitleLabel,
                                                 rect,
                                                 twoLineLayout );
                    }
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                    *iTitleLabel, EColorLabelText, color ) );
                }
            }
        }
    else if ( iExtension && iExtension->iTitleImage )
        {
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rect, AknLayoutScalable_Avkon::title_pane_g1() );
        TRect bmpRect( layoutRect.Rect() );
        TSize bmpSize( bmpRect.Size() );

        if ( iExtension->iImageAutoscaling &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, bmpSize );
            }
        else if ( !iExtension->iImageAutoscaling &&
                  iExtension->iTitleImage->Bitmap() )
            {
            bmpSize = iExtension->iTitleImage->Bitmap()->SizeInPixels();
            }

        TGulAlignment iAlignment;
        iAlignment.SetVAlignment( EVCenter );
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            iAlignment.SetHAlignment( EHRight );
            }
        else
            {
            iAlignment.SetHAlignment( EHLeft );
            }

        iExtension->iTitleImage->SetAlignment( iAlignment );

        TInt topMargin    = bmpRect.iTl.iY;
        TInt leftMargin   = bmpRect.iTl.iX;
        TInt bottomMargin = rect.iBr.iY - layoutRect.Rect().iBr.iY;
        TInt rightMargin  = rect.iBr.iX - layoutRect.Rect().iBr.iX;

        iExtension->iTitleImage->SetRect(
            iAlignment.InnerRect(
            TRect( rect.iTl.iX + leftMargin,
                   rect.iTl.iY + topMargin,
                   rect.iBr.iX - rightMargin,
                   rect.iBr.iY - bottomMargin),
            bmpSize ) );
        }
    }


void CAknTitlePane::SizeChangedInStaconPane()
    {
    TRect rect( Rect() );

    AknsUtils::RegisterControlPosition( this );
    TInt leftOrRightSoftKeysVariety = 0;
    if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
        {
        leftOrRightSoftKeysVariety = 1;
        }

    if ( iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         iExtension->iSmallImageShown )
        {
        TAknWindowComponentLayout imageLayout(
            AknLayoutScalable_Avkon::title_pane_stacon_g1(
                leftOrRightSoftKeysVariety ) );
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rect, imageLayout );

        if ( iExtension->iSmallImageAutoscaling &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, layoutRect.Rect().Size() );
            }

        TGulAlignment alignment;
        alignment.SetHAlignment( EHCenter );
        alignment.SetVAlignment( EVCenter );
        iExtension->iTitleImage->SetRect(
            alignment.InnerRect(
                layoutRect.Rect(),
                iExtension->iTitleImage->Bitmap()->SizeInPixels() ) );
        }

    if ( iTitleLabel && !iImageShown )
        {
        __ASSERT_DEBUG( iTitleText, Panic( EAknPanicNullPointer ) );

        // If image is shown, then select shorter text
        if ( iExtension->iTitleImage &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iSmallImageShown )
            {
            leftOrRightSoftKeysVariety += 2;
            }

        TAknTextLineLayout oneLineLayout(
            AknLayoutScalable_Avkon::title_pane_stacon_t1(
                leftOrRightSoftKeysVariety ).LayoutLine() );
        TAknLayoutText oneLineLayoutText;
        oneLineLayoutText.LayoutText( rect, oneLineLayout );
        TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );
        
        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( oneLineLayout.FontId() );
        
        TRAP_IGNORE(
            TInt lines = FormatTitlePaneLabelL( oneLineLayoutRect.Width(),
                                                0,
                                                fontUsed,
                                                fontUsed ) ); // Ignore leave.
            // Only layout of the title pane suffers if leave happens.

        AknLayoutUtils::LayoutLabel( iTitleLabel, rect, oneLineLayout );

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;

        TInt error = 0;

        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            error = AknsUtils::GetCachedColor( skin,
                                               color,
                                               KAknsIIDQsnTextColors,
                                               EAknsCIQsnTextColorsCG38 );
            }
        else
            {
            error = AknsUtils::GetCachedColor( skin,
                                               color,
                                               KAknsIIDQsnTextColors,
                                               EAknsCIQsnTextColorsCG37 );
            }

        if ( !error )
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                *iTitleLabel, EColorLabelText, color ) );
            }

        if ( iExtension &&
             ( iExtension->iScrollEffectEnabled ||
               iTitleLabel->TextEffect() ||
               !iTitleLabel->EffectQueueIsEmpty() ) )
            {
            TRAP_IGNORE( SetupTitleLabelEffectL() );
            if ( !iTitleLabel->TextEffect() )
                {
                AknLayoutUtils::LayoutLabel( iTitleLabel, rect, oneLineLayout );
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                    *iTitleLabel, EColorLabelText, color ) );
                }
            }
        }
    else if ( iExtension && iExtension->iTitleImage )
        {
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::title_pane_stacon_g2( 0 ) );
        TRect bmpRect( layoutRect.Rect() );
        TSize bmpSize( bmpRect.Size() );

        if  ( iExtension->iImageAutoscaling &&
              iExtension->iTitleImage->Bitmap() &&
              iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, bmpSize );
            }
        else if ( !iExtension->iImageAutoscaling &&
                  iExtension->iTitleImage->Bitmap() )
            {
            bmpSize = iExtension->iTitleImage->Bitmap()->SizeInPixels();
            }            

        TGulAlignment iAlignment;
        iAlignment.SetVAlignment( EVCenter );
        if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
            {
            iAlignment.SetHAlignment( EHRight );
            }
        else
            {
            iAlignment.SetHAlignment( EHLeft );
            }

        iExtension->iTitleImage->SetAlignment( iAlignment );

        TInt topMargin    = bmpRect.iTl.iY;
        TInt leftMargin   = bmpRect.iTl.iX;
        TInt bottomMargin = rect.Height() - ( bmpRect.Height() + topMargin );
        TInt rightMargin  = leftMargin;

        iExtension->iTitleImage->SetRect(
            iAlignment.InnerRect(
            TRect( rect.iTl.iX + leftMargin,
                   rect.iTl.iY + topMargin,
                   rect.iBr.iX - rightMargin,
                   rect.iBr.iY - bottomMargin ),
            bmpSize ) );
        }
    }


void CAknTitlePane::SizeChangedInFlatStatusPane()
    {
    AknsUtils::RegisterControlPosition( this );

    TRect rect( Rect() );

    if ( iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         iExtension->iSmallImageShown )
        {
        TBool touchLsc( Layout_Meta_Data::IsLandscapeOrientation() &&
                        AknLayoutUtils::PenEnabled() );

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::title_pane_g2( touchLsc ? 4 : 0 ) );

        if ( iExtension->iSmallImageAutoscaling &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, layoutRect.Rect().Size() );
            }

        TGulAlignment alignment;
        alignment.SetHAlignment( EHCenter );
        alignment.SetVAlignment( EVCenter );
        iExtension->iTitleImage->SetRect( alignment.InnerRect(
            layoutRect.Rect(),
            iExtension->iTitleImage->Bitmap()->SizeInPixels() ) );
        }

    if ( iTitleLabel && !iImageShown )
        {
        __ASSERT_DEBUG( iTitleText, Panic( EAknPanicNullPointer ) );

        TAknTextLineLayout oneLineLayout;
        TBool touchLsc( Layout_Meta_Data::IsLandscapeOrientation() &&
                        AknLayoutUtils::PenEnabled() );
        
        if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
            {
            // if image is shown, use shorter version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 11 : 3 ).LayoutLine();
            }
        else
            {
            // if image is not shown, use longer version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 10 : 2 ).LayoutLine();
            }

        TAknLayoutText oneLineLayoutText;
        oneLineLayoutText.LayoutText( rect, oneLineLayout );
        TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( oneLineLayout.FontId() );

        TRAP_IGNORE(
            TInt lines = FormatTitlePaneLabelL(
                oneLineLayoutRect.Width(),
                0,
                fontUsed,
                fontUsed )
            ); // Ignore leave.
               // Only layout of the title pane suffers if leave happens.

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color = 0;

        // Flat statuspane uses same color skinning as stacon pane
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG37 );

        // Ignore error
        TRAP_IGNORE(AknLayoutUtils::OverrideControlColorL(
            *iTitleLabel, EColorLabelText, color ) );

        TRAP_IGNORE( SetupTitleLabelEffectL() );
        if ( !iTitleLabel->TextEffect() )
            {
            AknLayoutUtils::LayoutLabel( iTitleLabel, rect, oneLineLayout );
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                *iTitleLabel, EColorLabelText, color ) );
            }
        }
    else if ( iExtension && iExtension->iTitleImage )
        {
        TRect bmpRect( rect );
        TSize bmpSize( bmpRect.Size() );

        if ( !Layout_Meta_Data::IsLandscapeOrientation() )
            {
            // Stacon layout is used for this layout too.
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::title_pane_stacon_g2( 0 ) );
            bmpRect = layoutRect.Rect();
            bmpSize = bmpRect.Size();
            }

        if  ( iExtension->iImageAutoscaling &&
              iExtension->iTitleImage->Bitmap() &&
              iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, bmpSize );
            }
        else if ( !iExtension->iImageAutoscaling &&
                  iExtension->iTitleImage->Bitmap() )
            {
            bmpSize = iExtension->iTitleImage->Bitmap()->SizeInPixels();
            }

        TGulAlignment iAlignment;
        iAlignment.SetVAlignment( EVCenter );
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            iAlignment.SetHAlignment( EHRight );
            }
        else
            {
            iAlignment.SetHAlignment( EHLeft );
            }

        iExtension->iTitleImage->SetAlignment( iAlignment );

        TInt topMargin    = bmpRect.iTl.iY;
        TInt leftMargin   = bmpRect.iTl.iX;
        TInt bottomMargin = rect.Height() - ( bmpRect.Height() + topMargin );
        TInt rightMargin  = leftMargin;

        iExtension->iTitleImage->SetRect(
            iAlignment.InnerRect(
            TRect( rect.iTl.iX + leftMargin,
                   rect.iTl.iY + topMargin,
                   rect.iBr.iX - rightMargin,
                   rect.iBr.iY - bottomMargin ),
            bmpSize ) );
        }
    }


void CAknTitlePane::SizeChangedInExtendedStatusPane()
    {
    AknsUtils::RegisterControlPosition( this );

    TRect rect( Rect() );
    
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool hdLayout( AknStatuspaneUtils::HDLayoutActive() );
    
    if (iExtension->iTitleImage && iExtension->iTitleImage->Bitmap() && iExtension->iSmallImageShown)
        {
        TAknWindowComponentLayout imageLayout(
            AknLayoutScalable_Avkon::title_pane_g2( hdLayout ? 4 : 1) );

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rect, imageLayout );

        if ( iExtension->iSmallImageAutoscaling &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, layoutRect.Rect().Size() );
            }

        TGulAlignment alignment;
        alignment.SetHAlignment( EHCenter );
        alignment.SetVAlignment( EVCenter );
        iExtension->iTitleImage->SetRect(
            alignment.InnerRect(
                layoutRect.Rect(),
                iExtension->iTitleImage->Bitmap()->SizeInPixels() ) );
        }

    if ( iTitleLabel && !iImageShown )
        {
        __ASSERT_DEBUG( iTitleText, Panic( EAknPanicNullPointer ) );

        TAknTextLineLayout oneLineLayout;
        if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
            {
            // if image is shown, use shorter version of text
            oneLineLayout = AknLayoutScalable_Avkon::title_pane_t1( hdLayout ? 11 : 6 ).LayoutLine();                
            if ( !TextFits( oneLineLayout ) )
                {
                if ( hdLayout )
                    {
                    oneLineLayout =
                        AknLayoutScalable_Avkon::title_pane_t1( 13 ).LayoutLine();
                    }
                else
                    {
                    oneLineLayout =
                        AknLayoutScalable_Avkon::title_pane_t2( 2 ).LayoutLine();
                    }
                }
            }
        else
            {
            // if image is not shown, use longer version of text
            oneLineLayout = AknLayoutScalable_Avkon::title_pane_t1( hdLayout ? 10 : 5 ).LayoutLine();                
            if ( !TextFits( oneLineLayout ) )
                {
                if ( hdLayout )
                    {
                    oneLineLayout =
                        AknLayoutScalable_Avkon::title_pane_t1( 12 ).LayoutLine();
                    }
                else
                    {
                    oneLineLayout =
                        AknLayoutScalable_Avkon::title_pane_t2( 1 ).LayoutLine();
                    }
                }
            }

        TAknLayoutText oneLineLayoutText;
        oneLineLayoutText.LayoutText( rect, oneLineLayout );
        TRect oneLineLayoutRect = oneLineLayoutText.TextRect();
        
        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( oneLineLayout.FontId() );
        
        TRAP_IGNORE(
            TInt lines = FormatTitlePaneLabelL(
                oneLineLayoutRect.Width(),
                0,
                fontUsed,
                fontUsed )
            ); // Ignore leave.
               // Only layout of the title pane suffers if leave happens.

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color = 0;

        // Same color skinning as normal status pane
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG1 );

        // Ignore error
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
            *iTitleLabel, EColorLabelText, color ) );

        TRAP_IGNORE( SetupTitleLabelEffectL() );
        if ( !iTitleLabel->TextEffect() )
            {
            AknLayoutUtils::LayoutLabel( iTitleLabel, rect, oneLineLayout );
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                *iTitleLabel, EColorLabelText, color ) );
            }
        }
    else if ( iExtension && iExtension->iTitleImage )
        {
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::title_pane_g1( hdLayout ) );
        TRect bmpRect( layoutRect.Rect() );
        TSize bmpSize( bmpRect.Size() );

        if  ( iExtension->iImageAutoscaling &&
              iExtension->iTitleImage->Bitmap() &&
              iExtension->iTitleImage->Mask() )
            {
            CFbsBitmap* bitmap =
                const_cast<CFbsBitmap*> ( iExtension->iTitleImage->Bitmap() );
            AknIconUtils::SetSize( bitmap, bmpSize );
            }
        else if ( !iExtension->iImageAutoscaling &&
                  iExtension->iTitleImage->Bitmap() )
            {
            bmpSize = iExtension->iTitleImage->Bitmap()->SizeInPixels();
            }

        TGulAlignment iAlignment;
        iAlignment.SetVAlignment( EVCenter );
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            iAlignment.SetHAlignment( EHRight );
            }
        else
            {
            iAlignment.SetHAlignment( EHLeft );
            }

        iExtension->iTitleImage->SetAlignment( iAlignment );

        TInt topMargin    = bmpRect.iTl.iY;
        TInt leftMargin   = bmpRect.iTl.iX;
        TInt bottomMargin = rect.Height() - ( bmpRect.Height() + topMargin );
        TInt rightMargin  = leftMargin;

        iExtension->iTitleImage->SetRect(
            iAlignment.InnerRect(
            TRect( rect.iTl.iX + leftMargin,
                   rect.iTl.iY + topMargin,
                   rect.iBr.iX - rightMargin,
                   rect.iBr.iY - bottomMargin ),
            bmpSize ) );
        }
    }


RWindow* CAknTitlePane::StatuspaneContainerWindow() const
    {
    RWindow* window = NULL;
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE( control = statusPane->ContainerControlL(
            TUid::Uid( EEikStatusPaneUidTitle ) ) );
        if( control )
            {
            RDrawableWindow* drawableWindow = control->DrawableWindow();
            if ( drawableWindow )
                {
                // Trust that container is always RWindow.
                window = static_cast <RWindow*> ( drawableWindow );
                }
            }
       }

    return window;
    }


void  CAknTitlePane::SetupTitleLabelEffectL()
    {
    if ( iTitleLabel )
        {
        iTitleLabel->InitEffectQueueL();
        }

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        if ( iExtension &&
             iExtension->iScrollEffectEnabled )
            {
            SetupStaconPaneScrollEffectL();
            }
        else
            {
            SetupNoEffectL(); // Default is no effect
            }
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        if ( iExtension &&
             iExtension->iScrollEffectEnabled )
            {
            SetupFlatStatusPaneFadeEffectL();
            SetupFlatStatusPaneScrollEffectL();
            SetupFlatStatusPaneFadeEffectL();
            }
        else
            {
            SetupFlatStatusPaneFadeEffectL(); // Default is fade effect
            }
        }
    else if ( AknStatuspaneUtils::ExtendedLayoutActive() )
        {
        if ( iExtension &&
             iExtension->iScrollEffectEnabled )
            {
            SetupExtendedStatusPaneScrollEffectL();
            }
        else
            {
            SetupNoEffectL(); // Default is no effect
            }
        }
    else
        {
        if ( iExtension &&
             iExtension->iScrollEffectEnabled )
            {
            SetupNormalStatusPaneScrollEffectL();
            }
        else
            {
            SetupNoEffectL(); // Default is no effect
            }
        }

    if ( iTitleLabel && iTitleLabel->EffectQueueIsEmpty() )
        {
        SetupNoEffectL();
        }

    if ( iTitleLabel )
        {
        iTitleLabel->ActivateEffectQueue();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetTitlePaneObserver()
// Set's aObserver as title pane observer
// ----------------------------------------------------------------------------
EXPORT_C void CAknTitlePane::SetTitlePaneObserver(
    MAknTitlePaneObserver* aObserver)
    {
    iTitlePaneObserver = aObserver;
    }


EXPORT_C void* CAknTitlePane::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::HandlePointerEventL()
// Processes TitlePane's pointer event's by informing observer about tapping
// ----------------------------------------------------------------------------

EXPORT_C void CAknTitlePane::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( IsDimmed() )
            {
            iExtension->iFlags &= ( ~EAknTitlePaneButton1DownInTitleRect );
            return;
            }

        // get rect of SignalPane
        TRect rect( Rect() );

        // Switch by type
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                // if signalPane's rect contains pointer down position
                if ( rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // set flag that down was inside titlePane
                    iExtension->iFlags |= EAknTitlePaneButton1DownInTitleRect;
                    }
                }
                break;

            case TPointerEvent::EButton1Up:
                {
                // if signalPane's rect contains pointer down position
                if ( iExtension->iFlags&EAknTitlePaneButton1DownInTitleRect &&
                     rect.Contains( aPointerEvent.iPosition ) )
                    {
                    if ( iTitlePaneObserver )
                        {
                        iTitlePaneObserver->HandleTitlePaneEventL(
                            MAknTitlePaneObserver::EAknTitlePaneTapped );
                        }
                    }

                // Up happened, reset button down flag
                iExtension->iFlags &= ( ~EAknTitlePaneButton1DownInTitleRect );
                }
                break;

            default:
                break;
            }
        }
    }


CEikLabel* CAknTitlePane::TextLabel()
    {
    return iTitleLabel;
    }


CEikImage* CAknTitlePane::TitleImage()
    {
    if ( iExtension &&
         iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         !iExtension->iSmallImageShown )
        {
        return iExtension->iTitleImage;
        }

    return NULL;
    }


void CAknTitlePane::SetContainerWindowNonFading( TBool aNonFading )
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE( control =
            statusPane->ContainerControlL(
                TUid::Uid( EEikStatusPaneUidTitle ) ) );

        if( control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }


void CAknTitlePane::SetupStaconPaneScrollEffectL()
    {
    if ( !iExtension->iScrollEffectNeeded )
        {
        return;
        }

    TRect rect( Rect() );

    // If image is shown, then select shorter text
    TInt leftOrRightSoftKeysVariety = 0;
    if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
        {
        leftOrRightSoftKeysVariety = 1;
        }
    if ( iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         iExtension->iSmallImageShown )
        {
        leftOrRightSoftKeysVariety += 2;
        }

    TAknTextLineLayout oneLineLayout(
        AknLayoutScalable_Avkon::title_pane_stacon_t1(
            leftOrRightSoftKeysVariety ).LayoutLine() );
    TAknLayoutText oneLineLayoutText;
    oneLineLayoutText.LayoutText( rect, oneLineLayout );
    TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

    TRect effectRect( rect );

    CAknTitlePaneLabel::SAknTitleLableEffect effect;

    // First show text without effect
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = oneLineLayoutRect;
    effect.iLabelRect      = rect;
    effect.iObserver       = NULL;
    effect.iTitleText      = iTitleText;
    effect.iTextLayout     = oneLineLayoutText;
    effect.iTextLayoutLine = oneLineLayout;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectRect     = effectRect;
    effect.iEffectDuration = KScrollPauseBeforeScroll;
    iTitleLabel->AddToEffectQueueL( effect );

    // Scroll text once
    effect.iEffect     = CAknTitlePaneLabel::EEffectScrollOnceWithFade;
    effect.iEffectRect = oneLineLayoutRect;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectRect     = rect;
    effect.iEffectDuration = KScrollPauseBeforeFadeOut;
    iTitleLabel->AddToEffectQueueL( effect );

    // Fade out
    effect.iEffect         = CAknTitlePaneLabel::EEffectFadeOut;
    effect.iEffectDuration = KScrollFadeInFadeOutDuration;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeIn;
    iTitleLabel->AddToEffectQueueL( effect );

    // Default
    effect.iEffect = CAknTitlePaneLabel::EEffectToggleScrolledTextTruncation;
    iTitleLabel->AddToEffectQueueL( effect );

    // No fade in because we don't do it in other layouts either

    // Finally show text without effect
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = oneLineLayoutRect;
    iTitleLabel->AddToEffectQueueL( effect );
    }

void CAknTitlePane::SetupExtendedStatusPaneScrollEffectL()
    {
    if ( !iExtension->iScrollEffectNeeded )
        {
        return;
        }

    TRect rect( Rect() );
    TBool hdLayout( AknStatuspaneUtils::HDLayoutActive() );

    TInt variety = hdLayout ? 10 : 5;
    TBool imageShown = EFalse;

    // If image is shown, then select shorter text
    if ( iExtension->iTitleImage &&
         iExtension->iTitleImage->Bitmap() &&
         iExtension->iSmallImageShown )
        {
        variety = hdLayout ? 11 : 6;
        imageShown = ETrue;
        }

    TAknTextLineLayout oneLineLayout(
        AknLayoutScalable_Avkon::title_pane_t1( variety ).LayoutLine() );

    // if text would truncate, then use smaller font.
    // (No smaller font layout with image exist)
    if ( !TextFits( oneLineLayout ) )
        {
        if ( !imageShown )
            {
            if ( hdLayout )
                {
                oneLineLayout =
                    AknLayoutScalable_Avkon::title_pane_t1( 12 ).LayoutLine();
                }
            else
                {
                oneLineLayout =
                    AknLayoutScalable_Avkon::title_pane_t2( 1 ).LayoutLine();
                }
            }
        else
            {
            if ( hdLayout )
                {
                oneLineLayout =
                    AknLayoutScalable_Avkon::title_pane_t1( 13 ).LayoutLine();
                }
            else
                {
                oneLineLayout =
                    AknLayoutScalable_Avkon::title_pane_t2( 2 ).LayoutLine();
                }
            }
        }

    TAknLayoutText oneLineLayoutText;
    oneLineLayoutText.LayoutText( rect, oneLineLayout );
    TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

    TRect effectRect( rect );

    CAknTitlePaneLabel::SAknTitleLableEffect effect;

    // First show text without effect
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = oneLineLayoutRect;
    effect.iLabelRect      = rect;
    effect.iObserver       = NULL;
    effect.iTitleText      = iTitleText;
    effect.iTextLayout     = oneLineLayoutText;
    effect.iTextLayoutLine = oneLineLayout;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectRect     = effectRect;
    effect.iEffectDuration = KScrollPauseBeforeScroll;
    iTitleLabel->AddToEffectQueueL( effect );

    // Scroll text once
    effect.iEffect     = CAknTitlePaneLabel::EEffectScrollOnceWithFade;
    effect.iEffectRect = oneLineLayoutRect;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectRect     = rect;
    effect.iEffectDuration = KScrollPauseBeforeFadeOut;
    iTitleLabel->AddToEffectQueueL( effect );

    // Fade out
    effect.iEffect         = CAknTitlePaneLabel::EEffectFadeOut;
    effect.iEffectDuration = KScrollFadeInFadeOutDuration;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeIn;
    iTitleLabel->AddToEffectQueueL( effect );

    // Default
    effect.iEffect = CAknTitlePaneLabel::EEffectToggleScrolledTextTruncation;
    iTitleLabel->AddToEffectQueueL( effect );

    // No fade in because we don't do it in other layouts either

    // Finally show text without effect
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = oneLineLayoutRect;
    iTitleLabel->AddToEffectQueueL( effect );
    }


void CAknTitlePane::SetupFlatStatusPaneScrollEffectL()
    {
    if ( !iExtension->iScrollEffectNeeded )
        {
        return;
        }

    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TBool fade                               = EFalse;
    TBool narrowNaviPane                     = EFalse;
    TBool forcedNormalNaviPane               = EFalse;
    
    RWindow* naviwindow                      = NULL;
    RWindow* titlewindow                     = NULL;
    CCoeControl* naviContainerControl        = NULL;
    CCoeControl* titleContainerControl       = NULL;
    CAknNavigationControlContainer* naviPane = NULL;
    CAknNavigationDecorator* decorator       = NULL;

    TPoint naviControlPosition;
    TSize naviControlSize;

    if ( statusPane )
        {
        naviContainerControl = statusPane->ContainerControlL(
            TUid::Uid( EEikStatusPaneUidNavi ) );
        titleContainerControl = statusPane->ContainerControlL(
            TUid::Uid( EEikStatusPaneUidTitle ) );
        if ( naviContainerControl && titleContainerControl )
            {
            RDrawableWindow* drawableWindow =
                naviContainerControl->DrawableWindow();
            if ( drawableWindow )
                {
                // Trust that container is always RWindow.
                naviwindow = static_cast <RWindow*> ( drawableWindow );
                }

            drawableWindow = titleContainerControl->DrawableWindow();
            if ( drawableWindow )
                {
                // Trust that container is always RWindow.
                titlewindow = static_cast <RWindow*> ( drawableWindow );
                }


            naviControlPosition = naviContainerControl->Position();
            naviControlSize     = naviContainerControl->Size();
            }

        CCoeControl* control = NULL;
        TRAP_IGNORE( control =
            statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
        if ( control )
            {
            // Control cannot be casted directly because someone may have
            // swapped the control. Use this method instead.
            control->MopGetObject( naviPane );
            if ( naviPane )
                {
                decorator = naviPane->Top( EFalse );
                if ( decorator )
                    {
                    if ( decorator->NaviControlLayoutStyle() ==
                            CAknNavigationDecorator::ENaviControlLayoutNarrow )
                        {
                        naviControlPosition +=
                            CAknNavigationDecorator::DecoratedControlNarrowRect(
                                decorator->ControlType() ).iTl;
                        naviControlSize =
                            CAknNavigationDecorator::DecoratedControlNarrowRect(
                                decorator->ControlType() ).Size();
                        narrowNaviPane = ETrue;
                        }
                    if ( decorator->NaviControlLayoutStyle() == CAknNavigationDecorator::ENaviControlLayoutNormal &&
                         decorator->NaviControlLayoutMode() == CAknNavigationDecorator::ENaviControlLayoutModeForced )
                        {
                        forcedNormalNaviPane = ETrue;
                        }
                    }
                }
            }
        }

    if ( naviwindow && titlewindow )
        {
        // Fade title text only if navipane window is above titlepane
        TInt naviWindowOrdinalPosition = naviwindow->OrdinalPosition();
        TInt titleWindowOrdinalPosition = titlewindow->OrdinalPosition();
        fade = naviWindowOrdinalPosition < titleWindowOrdinalPosition;
        }


    TAknTextLineLayout oneLineLayout;

    TBool touchLsc( Layout_Meta_Data::IsLandscapeOrientation() &&
                    AknLayoutUtils::PenEnabled() );
    
    if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
        {
        // if image is shown, use shorter version of text
        oneLineLayout =
            AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 11 : 3 ).LayoutLine();
        }
    else
        {
        // if image is not shown, use longer version of text
        oneLineLayout =
            AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 10 : 2 ).LayoutLine();
        }

    TAknLayoutText oneLineLayoutText;
    oneLineLayoutText.LayoutText( Rect(), oneLineLayout );
    TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

    TRect effectRect( oneLineLayoutText.TextRect() );
    if ( fade )
        {
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            effectRect.iBr.iX =
                naviControlPosition.iX - titleContainerControl->Position().iX;
            }
        else
            {
            effectRect.iTl.iX = naviControlSize.iWidth + naviControlPosition.iX;
            }
        }
    else
        {
        effectRect = oneLineLayoutText.TextRect();
        }

    // Decide scrolling need
    if ( narrowNaviPane || forcedNormalNaviPane )
        {
        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( oneLineLayout.FontId() );
        CFont::TMeasureTextInput input;
        input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;
        TInt textLength = fontUsed->MeasureText( *iTitleText, &input );

        TRect visibleTextRect( effectRect );

        if ( textLength > visibleTextRect.Width() )
            {
            iExtension->iScrollEffectNeeded = ETrue;
            }
        }
    else
        {
        // No scroll if navipane is not in short mode but fade is on.
        if ( fade )
            {
            iExtension->iScrollEffectNeeded = EFalse;
            }
        }

    // This is the earliest place where we really know
    // if scrolling is needed or not.
    if ( !iExtension->iScrollEffectNeeded )
        {
        return;
        }

    CAknTitlePaneLabel::SAknTitleLableEffect effect;

    // Initilize effect struct
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = Rect();
    effect.iLabelRect      = Rect();
    effect.iObserver       = static_cast <CCoeControl*> ( naviPane );
    effect.iTitleText      = iTitleText;
    effect.iTextLayout     = oneLineLayoutText;
    effect.iTextLayoutLine = oneLineLayout;

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeScroll;
    iTitleLabel->AddToEffectQueueL( effect );

    // Scroll text once
    effect.iEffectDuration = 0;
    effect.iEffectRect     = effectRect;
    effect.iEffect         = CAknTitlePaneLabel::EEffectScrollOnceWithFade;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeOut;
    iTitleLabel->AddToEffectQueueL( effect );

    // Fade out
    effect.iEffect         = CAknTitlePaneLabel::EEffectFadeOut;
    effect.iEffectDuration = KScrollFadeInFadeOutDuration;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeIn;
    iTitleLabel->AddToEffectQueueL( effect );

    // Default
    effect.iEffect = CAknTitlePaneLabel::EEffectToggleScrolledTextTruncation;
    iTitleLabel->AddToEffectQueueL( effect );

    // No fade in because we don't support fade in with
    // other effects (fade left or right).

    // Finally text is shown with fade effect if needed
    // (setup in its own method).
    }

void CAknTitlePane::SetupNormalStatusPaneScrollEffectL()
    {
    if ( !iExtension->iScrollEffectNeeded )
        {
        return;
        }

    TRect rect( Rect() );

    // Is battery pane visible in current layout
    TInt indexW = AknStatuspaneUtils::IdleLayoutActive() ? 1 : 0;

    TAknTextLineLayout oneLineLayout(
         AknLayoutScalable_Avkon::title_pane_t1( 0 ).LayoutLine() );

    const TAknMultiLineTextLayout twoLineLayout(
        AKN_LAYOUT_MULTILINE_TEXT_Title_pane_texts_Line_2( indexW, 2 ) );

    // if text would truncate, then try to use smaller font with one line layout
    if ( !TextFits( oneLineLayout ) )
        {
        oneLineLayout =
            AknLayoutScalable_Avkon::title_pane_t2( 1 ).LayoutLine();
        }

    TAknLayoutText oneLineLayoutText;
    oneLineLayoutText.LayoutText(rect, oneLineLayout);
    TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

    TAknLayoutText twoLineLayoutText;
    twoLineLayoutText.LayoutText(rect, twoLineLayout);
    TRect twoLineLayoutRect( twoLineLayoutText.TextRect() );

    CAknTitlePaneLabel::SAknTitleLableEffect effect;

    effect.iEffect         = 0;
    effect.iEffectDuration = 0;
    effect.iLabelRect      = rect;
    effect.iObserver       = NULL;
    effect.iTitleText      = iTitleText;
    effect.iEffectRect     = oneLineLayoutRect;
    effect.iTextLayout     = oneLineLayoutText;
    effect.iTextLayoutLine = oneLineLayout;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeScroll;
    iTitleLabel->AddToEffectQueueL( effect );

    // Scroll text once
    effect.iEffect     = CAknTitlePaneLabel::EEffectScrollOnceWithFade;
    effect.iEffectRect = oneLineLayoutRect;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeOut;
    iTitleLabel->AddToEffectQueueL( effect );

    // Fade out
    effect.iEffect         = CAknTitlePaneLabel::EEffectFadeOut;
    effect.iEffectRect     = rect;
    effect.iEffectDuration = KScrollFadeInFadeOutDuration;
    iTitleLabel->AddToEffectQueueL( effect );

    // Pause
    effect.iEffect         = CAknTitlePaneLabel::EEffectPause;
    effect.iEffectDuration = KScrollPauseBeforeFadeIn;
    iTitleLabel->AddToEffectQueueL( effect );

    // No fade in done, drawing two line text with effects is not supported.

    // Finally show text without effect
    effect.iEffect = 0;
    if ( iExtension && iExtension->iCurrentNumberOfTextLines == 2 )
        {
        effect.iEffectRect     = twoLineLayoutRect;
        effect.iLabelRect      = rect;
        effect.iTextLayout     = twoLineLayoutText;
        effect.iTextLayoutLine = twoLineLayout;
        }
    else
        {
        effect.iEffectRect     = oneLineLayoutRect;
        effect.iLabelRect      = rect;
        effect.iTextLayout     = oneLineLayoutText;
        effect.iTextLayoutLine = oneLineLayout;
        }
    iTitleLabel->AddToEffectQueueL( effect );
    }


void CAknTitlePane::SetupFlatStatusPaneFadeEffectL()
    {
    // For flat statuspane we fade the titletext under navipane
    // in situations where navipane is covering part of titlepane.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TBool fade                               = EFalse;
    TBool narrowNaviPane                     = EFalse;
    TBool forcedNormalNaviPane               = EFalse;
    RWindow* naviwindow                      = NULL;
    RWindow* titlewindow                     = NULL;
    CCoeControl* naviContainerControl        = NULL;
    CCoeControl* titleContainerControl       = NULL;
    CAknNavigationControlContainer* naviPane = NULL;
    CAknNavigationDecorator* decorator       = NULL;

    TPoint naviControlPosition( 0, 0 );
    TSize  naviControlSize( 0, 0 );
    TRect  rect( Rect() );

    if ( statusPane )
        {
        naviContainerControl =
            statusPane->ContainerControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
        titleContainerControl =
            statusPane->ContainerControlL( TUid::Uid( EEikStatusPaneUidTitle ) );

        if ( naviContainerControl && titleContainerControl )
            {
            RDrawableWindow* drawableWindow =
                naviContainerControl->DrawableWindow();

            if ( drawableWindow )
                {
                // Trust that container is always RWindow.
                naviwindow = static_cast <RWindow*> ( drawableWindow );
                }

            drawableWindow = titleContainerControl->DrawableWindow();
            if ( drawableWindow )
                {
                // Trust that container is always RWindow.
                titlewindow = static_cast <RWindow*> ( drawableWindow );
                }

            naviControlPosition = naviContainerControl->Position();
            naviControlSize     = naviContainerControl->Size();
            }

        CCoeControl* control = NULL;
        TRAP_IGNORE( control =
            statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );

        if ( control )
            {
            // Control cannot be casted directly beacause someone
            // may have swapped the control.
            // Use this workaround instead.
            control->MopGetObject( naviPane );
            if ( naviPane )
                {
                decorator = naviPane->Top( EFalse );
                if ( decorator )
                    {
                    if ( decorator->NaviControlLayoutStyle() ==
                            CAknNavigationDecorator::ENaviControlLayoutNarrow )
                        {
                        naviControlPosition +=
                            CAknNavigationDecorator::DecoratedControlNarrowRect(
                                decorator->ControlType() ).iTl;
                                
                        naviControlSize =
                            CAknNavigationDecorator::DecoratedControlNarrowRect(
                                decorator->ControlType() ).Size();
                                
                        narrowNaviPane = ETrue;
                        }
                    if ( decorator->NaviControlLayoutStyle() == CAknNavigationDecorator::ENaviControlLayoutNormal &&
                         decorator->NaviControlLayoutMode() == CAknNavigationDecorator::ENaviControlLayoutModeForced )
                        {
                        forcedNormalNaviPane = ETrue;
                        }
                    }
                }
            }
        }

    if ( naviwindow && titlewindow )
        {
        // Fade title text only if navipane window is above titlepane
        TInt naviWindowOrdinalPosition  = naviwindow->OrdinalPosition();
        TInt titleWindowOrdinalPosition = titlewindow->OrdinalPosition();
        fade =  titleWindowOrdinalPosition >  naviWindowOrdinalPosition;
        }

    if ( fade )
        {
        TAknTextLineLayout oneLineLayout;
        TBool touchLsc( Layout_Meta_Data::IsLandscapeOrientation() &&
                        AknLayoutUtils::PenEnabled() );
        if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
            {
            // if image is shown, use shorter version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 11 : 3 ).LayoutLine();
            }
        else
            {
            // if image is not shown, use longer version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 10 : 2 ).LayoutLine();
            }      


        TAknLayoutText oneLineLayoutText;
        oneLineLayoutText.LayoutText(rect, oneLineLayout);
        TRect oneLineLayoutRect( oneLineLayoutText.TextRect() );

        TRect effectRect( rect );
        TInt effectType = 0;

        // In landscape mode fade about 25% of the title, and in portrait
        // fade the whole title.
        TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

            if ( !AknLayoutUtils::LayoutMirrored() )
                {
                effectType = CAknTitlePaneLabel::EEffectFadeToRight;
                effectRect.iBr.iX = naviControlPosition.iX - titleContainerControl->Position().iX;
                effectRect.iTl.iX = effectRect.iBr.iX - effectRect.iBr.iX / 4;
                }
            else
                {
                effectType = CAknTitlePaneLabel::EEffectFadeToLeft;
                effectRect.iTl.iX = naviControlPosition.iX + naviControlSize.iWidth;
                effectRect.iBr.iX = rect.iBr.iX;
                effectRect.iTl.iX -= titleContainerControl->Position().iX;
                effectRect.iBr.iX -= effectRect.Size().iWidth * 3 / 4;
                }

        CAknTitlePaneLabel::SAknTitleLableEffect effect;
        effect.iEffectDuration = 0;
        effect.iEffect         = effectType;
        effect.iEffectRect     = effectRect;
        effect.iLabelRect      = rect;
        effect.iObserver       = naviPane;
        effect.iTitleText      = iTitleText;
        effect.iTextLayout     = oneLineLayoutText;
        effect.iTextLayoutLine = oneLineLayout;
        iTitleLabel->AddToEffectQueueL( effect );

        // Decide scrolling need
        if ( narrowNaviPane || forcedNormalNaviPane )
            {
            const CFont* fontUsed =
                AknLayoutUtils::FontFromId( oneLineLayout.FontId() );
            CFont::TMeasureTextInput input;
            input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;
            TInt textLength = fontUsed->MeasureText( *iTitleText, &input );

            TRect visibleTextRect( oneLineLayoutRect );
            if ( !AknLayoutUtils::LayoutMirrored() )
                {
                visibleTextRect.iBr.iX = effectRect.iTl.iX;
                }
            else
                {
                visibleTextRect.iTl.iX = effectRect.iBr.iX;
                }

            if ( textLength > visibleTextRect.Width() )
                {
                iExtension->iScrollEffectNeeded = ETrue;
                }
            }
        else
            {
            // No scroll if navipane is not in short mode but fade is on.
            if ( fade )
                {
                iExtension->iScrollEffectNeeded = EFalse;
                }
            }
        }
    else
        {
        SetupNoEffectL();
        }
    }


void CAknTitlePane::SetupNoEffectL()
    {
    TAknLayoutText     oneLineLayoutText;
    TAknTextLineLayout oneLineLayout;
    
    TRect rect( Rect() );

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        // If image is shown, then select shorter text
        TInt leftOrRightSoftKeysVariety = 0;
        if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
            {
            leftOrRightSoftKeysVariety = 1;
            }
        if ( iExtension->iTitleImage &&
             iExtension->iTitleImage->Bitmap() &&
             iExtension->iSmallImageShown )
            {
            leftOrRightSoftKeysVariety += 2;
            }

        oneLineLayout =
            AknLayoutScalable_Avkon::title_pane_stacon_t1(
                leftOrRightSoftKeysVariety ).LayoutLine();
        }
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        TBool touchLsc( Layout_Meta_Data::IsLandscapeOrientation() &&
                        AknLayoutUtils::PenEnabled() );
        if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
            {
            // if image is shown, use shorter version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 11 : 3 ).LayoutLine();
            }
        else
            {
            // if image is not shown, use longer version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( touchLsc ? 10 : 2 ).LayoutLine();
            }      
        }
    else if ( AknStatuspaneUtils::ExtendedLayoutActive() )
        {
        if ( iExtension->iTitleImage && iExtension->iSmallImageShown )
            {
            // if image is shown, use shorter version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( 6 ).LayoutLine();
            }
        else
            {
            // if image is not shown, use longer version of text
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t1( 5 ).LayoutLine();
            }
        }
    else
        {
        // Is battery pane visible in current layout
        TInt indexW = AknStatuspaneUtils::IdleLayoutActive() ? 1 : 0;
        oneLineLayout =
            AknLayoutScalable_Avkon::title_pane_t1( 0 ).LayoutLine();

        if ( !TextFits( oneLineLayout ) )
            {
            oneLineLayout =
                AknLayoutScalable_Avkon::title_pane_t2( 1 ).LayoutLine();
            }

        TAknMultiLineTextLayout twoLineLayout(
            AKN_LAYOUT_MULTILINE_TEXT_Title_pane_texts_Line_2( indexW, 2 ) );

        if ( iExtension && iExtension->iCurrentNumberOfTextLines == 2 )
            {
            oneLineLayout = twoLineLayout;
            }
        }

    oneLineLayoutText.LayoutText( rect, oneLineLayout );
    CAknTitlePaneLabel::SAknTitleLableEffect effect;
    effect.iEffectDuration = 0;
    effect.iEffect         = 0;
    effect.iEffectRect     = rect;
    effect.iLabelRect      = rect;
    effect.iObserver       = NULL;
    effect.iTitleText      = iTitleText;
    effect.iTextLayout     = oneLineLayoutText;
    effect.iTextLayoutLine = oneLineLayout;
    iTitleLabel->AddToEffectQueueL( effect );
    }

// ----------------------------------------------------------------------------
// CAknTitlePane::SetTextL
// Sets the title pane text and scrolling effect.
// CAknTitlePane takes the ownership of aText.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetText( HBufC* aText, TBool aScroll )
    {
    __ASSERT_ALWAYS( aText, Panic( EAknPanicNullPointer ) );

    TBool textChanged = !iTitleText || aText != iTitleText || *aText != *iTitleText
                        || iImageShown || aScroll != iExtension->iScrollEffectEnabled;
    
    iExtension->iScrollEffectEnabled = aScroll;
    if ( iTitleLabel )
        {
        iTitleLabel->InvalidateText();
        }
    if ( iTitleText != aText )
        {
        delete iTitleText;
        iTitleText = aText;
        }

    if ( textChanged )
        {
        iImageShown = EFalse;
        SizeChanged();
        DrawDeferred();
        }
    }


// ----------------------------------------------------------------------------
// CAknTitlePane::SetTextL
// Sets the title pane text and scrolling effect.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknTitlePane::SetTextL( const TDesC& aText, TBool aScroll )
    {
    SetText( aText.AllocL(), aScroll );
    }


EXPORT_C TInt CAknTitlePane::MaxNumberOfVisibleTextRows() const
    {
    if ( AknStatuspaneUtils::StaconPaneActive() ||
         AknStatuspaneUtils::FlatLayoutActive() ||
         AknStatuspaneUtils::ExtendedLayoutActive() )
        {
        return 1;
        }
    else
        {
        return 2;
        }
    }


EXPORT_C void CAknTitlePane::SetNumberOfVisibleTextRows( TInt aRows )
    {
    if ( iExtension && aRows > 0 && aRows <= MaxNumberOfVisibleTextRows() )
        {
        if ( iExtension->iLimitedNumberOfTextLines != aRows )
            {
            iExtension->iLimitedNumberOfTextLines = aRows;
            SizeChanged();
            DrawDeferred();
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknTitlePane::TextFits
// Checks if the text fits inside the title pane area.
// ---------------------------------------------------------------------------
//	
TBool CAknTitlePane::TextFits( TAknTextLineLayout& aTextLayout )
    {
    TInt textLength = 0;
    TInt maxLength  = 0;

    const CFont* fontUsed = AknLayoutUtils::FontFromId( aTextLayout.FontId() );
    CFont::TMeasureTextInput input;
    
    // We need to check if the title text's directionality
    // is from right to left to measure it correctly.
    TBool rtl =
        TBidiText::TextDirectionality( *iTitleText ) == TBidiText::ERightToLeft;
    if ( !rtl )
        {
        input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;
        }
    else
        {
        input.iFlags = CFont::TMeasureTextInput::EFVisualOrderRightToLeft;
        }
    textLength = fontUsed->MeasureText( *iTitleText, &input );

    TAknLayoutText oneLineLayoutText;
    oneLineLayoutText.LayoutText( Rect(), aTextLayout );
    maxLength = oneLineLayoutText.TextRect().Width();

    if ( textLength < maxLength )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

//  End of File
