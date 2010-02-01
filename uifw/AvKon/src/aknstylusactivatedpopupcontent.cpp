/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Content for stylus activated pop-up.
*
*/


#include <AknUtils.h>
#include <AknPanic.h>
#include <AknPreviewPopUpController.h>
#include <barsread.h> // TResourceReader
#include <eiklabel.h>
#include <fbs.h>
#include <aknappui.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsDrawUtils.h>
#include <AknBidiTextUtils.h>
#include <touchfeedback.h>
    
#include "akntextcontrol.h"
#include "aknstylusactivatedpopupcontent.h"

#ifdef RD_SCALABLE_UI_V2
// CONSTANTS
const TInt KMaxNbrOfInfoLines = 2; 
const TInt KMaxNbrOfCmdLinks = 2;
const TInt KNoItemHighlighted = -1; 

#endif // RD_SCALABLE_UI_V2 


NONSHARABLE_CLASS( CAknStylusActivatedItem ) : public CBase 
    {
public: 
    CAknStylusActivatedItem(); 
    ~CAknStylusActivatedItem(); 
    void ConstructL( TDesC& aText, TInt aCommandId ); 
public: 
    //Member data
    TRect iRect; 
    HBufC* iText; 
    TInt iCommandId; 
    }; 

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------
//
CAknStylusActivatedItem::CAknStylusActivatedItem()
    {
    }

// -----------------------------------------------------------------------------
// CAknStylusActivatedItem::ConstructL
// -----------------------------------------------------------------------------
//
void CAknStylusActivatedItem::ConstructL( TDesC& aText, TInt aCommandId )
    {
    iText = aText.AllocL(); 
    iCommandId = aCommandId; 
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknStylusActivatedItem::~CAknStylusActivatedItem()
    {
    delete iText; 
    }


// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// Default constructor.
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
CAknStylusActivatedPopUpContent::CAknStylusActivatedPopUpContent(): 
    iHighlightedItem( KNoItemHighlighted )
    {
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::NewL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL(
        const TDesC& aTitleText,
        const TDesC& aText )
    {
    CAknStylusActivatedPopUpContent* self =
                            new ( ELeave ) CAknStylusActivatedPopUpContent();
                                
    CleanupStack::PushL( self );
    self->ConstructL( aTitleText, aText );
    CleanupStack::Pop(); // self
    return self;
    }
#else
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL(
        const TDesC& /*aTitleText*/,
        const TDesC& /*aText*/ )
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::NewL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL(
        const TDesC& aTitleText,
        const TDesC& aText,
        const RArray<TAknContentLink>& aLinkArray )
    {
    CAknStylusActivatedPopUpContent* self =
                            new ( ELeave ) CAknStylusActivatedPopUpContent();
                                
    CleanupStack::PushL( self );
    self->ConstructL( aTitleText, aText, aLinkArray );
    CleanupStack::Pop(); // self
    return self;
    }
#else
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL(
        const TDesC& /*aTitleText*/,
        const TDesC& /*aText*/,
        const RArray<TAknContentLink>& /*&aLinkArray*/ )
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::NewL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL( TResourceReader& aReader )
    {
    CAknStylusActivatedPopUpContent* self =
                            new ( ELeave ) CAknStylusActivatedPopUpContent();
                                
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aReader );
    CleanupStack::Pop(); // self
    return self;
    }
#else
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL( TResourceReader& /*aReader*/ )
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::NewL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL( const TInt aResourceId )
    {
    CAknStylusActivatedPopUpContent* self =
                            new ( ELeave ) CAknStylusActivatedPopUpContent();
                                
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId );
    CleanupStack::Pop(); // self
    return self;
    }
#else
EXPORT_C CAknStylusActivatedPopUpContent*
        CAknStylusActivatedPopUpContent::NewL( const TInt /*aResourceId*/ )
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
CAknStylusActivatedPopUpContent::~CAknStylusActivatedPopUpContent()
    {
    iLinkArray.ResetAndDestroy();     
    delete iTitleText;
    delete iText;
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::ConstructFromResourceL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknStylusActivatedPopUpContent::ConstructFromResourceL(
        const TInt aResourceId )
    {
    if ( aResourceId )
        {
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
        ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // reader
        }
    }
#else
EXPORT_C void CAknStylusActivatedPopUpContent::ConstructFromResourceL(
        const TInt /*aResourceId*/ )
    {
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::SetCommandObserver
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknStylusActivatedPopUpContent::SetCommandObserver(
        MEikCommandObserver& aCommandObserver )
    {
    iCommandObserver = &aCommandObserver;
    }
#else
EXPORT_C void CAknStylusActivatedPopUpContent::SetCommandObserver(
        MEikCommandObserver& /*aCommandObserver*/ )
    {
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::ConstructFromResourceL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknStylusActivatedPopUpContent::ConstructFromResourceL(
        TResourceReader& aReader )
    {
    // read title and info texts
    TPtrC titleText = aReader.ReadTPtrC();
    TPtrC infotext = aReader.ReadTPtrC();
        
    // read function link count
    TInt numberOfLinks = aReader.ReadInt16();

    __ASSERT_ALWAYS( numberOfLinks <= KMaxNbrOfCmdLinks,
        Panic( EAknPanicOutOfRange ) );

    if ( numberOfLinks > 0 )
        {
        RArray<TAknContentLink> linkArray;
        CleanupClosePushL( linkArray ); 
        for ( TInt i = 0; i < numberOfLinks; i++ )
            {
            TAknContentLink link;
            link.iLinkId = aReader.ReadInt8();
            TPtrC linkTextTPtrC = aReader.ReadTPtrC();
            HBufC* buf = linkTextTPtrC.AllocLC();
              
            link.iLinkText = buf;
            linkArray.AppendL( link );
                
            // possible extension
            aReader.ReadInt32();
            }
        ConstructL( titleText, infotext, linkArray );
        CleanupStack::PopAndDestroy( numberOfLinks ); 
        CleanupStack::PopAndDestroy( &linkArray ); 
        }
    else
        {
        ConstructL( titleText, infotext );
        }
    }
#else
EXPORT_C void CAknStylusActivatedPopUpContent::ConstructFromResourceL(
        TResourceReader& /*aReader*/ )
    {
    }
#endif // RD_SCALABLE_UI_V2 


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::HandleResourceChange
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknStylusActivatedPopUpContent::HandleResourceChange(
        TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SizeChanged();
        }
    }
#else
EXPORT_C void CAknStylusActivatedPopUpContent::HandleResourceChange(
        TInt /*aType*/ )
    {
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::SetContainerWindowL
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C void CAknStylusActivatedPopUpContent::SetContainerWindowL(
        const CCoeControl& aContainer )
    {
    CCoeControl::SetContainerWindowL( aContainer );
        
    if( iText )
        {
        iText->SetContainerWindowL( aContainer );
        }
            
    iTitleText->SetContainerWindowL( aContainer );
    }
#else
EXPORT_C void CAknStylusActivatedPopUpContent::SetContainerWindowL(
        const CCoeControl& /*aContainer*/ )
    {
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// From class MCoeControlObserver.
// CAknStylusActivatedPopUpContent::HandleControlEventL
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStylusActivatedPopUpContent::HandleControlEventL(
        CCoeControl* /*aControl*/,
        TCoeEvent /*aEventType*/ )
    {
    }

#ifdef RD_SCALABLE_UI_V2

// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::ConstructL
// -----------------------------------------------------------------------------
//
void CAknStylusActivatedPopUpContent::ConstructL( const TDesC& aTitleText,
                                                  const TDesC& aText )
    {
    // titletext must be always given
    __ASSERT_ALWAYS( aTitleText.Length(), Panic( EAknPanicNullPointer ) );
    // either of infotext or cmds must be given
    __ASSERT_ALWAYS( aText.Length() > 0 || iLinkArray.Count() > 0,
        Panic( EAknPanicOutOfRange ) );

    iTitleText = new ( ELeave ) CEikLabel;
    iTitleText->SetTextL( aTitleText );
        
    if( aText.Length() > 0 )
        {
        iText = CAknTextControl::NewL();
        iText->SetTextL( aText );
        }
    TInt numOfLines = iLinkArray.Count(); 
    if ( iText )
        {
        numOfLines++; 
        }

    TInt variety = GetVariety( numOfLines ); 

    TRect rectPopUpWindow = PopUpWindowRectFromLayout(
        AknLayoutScalable_Avkon::popup_touch_info_window( variety ) );

    TRect rectHeadingSubPane = RectFromLayout( rectPopUpWindow,
        AknLayoutScalable_Avkon::heading_sub_pane() );

    TAknLayoutText layoutText;
    layoutText.LayoutText( rectHeadingSubPane,
       AknLayoutScalable_Avkon::heading_sub_pane_t1() );
            
    iTitleText->SetFont( layoutText.Font() );
      
    TAknWindowComponentLayout infoPaneLayout =
        AknLayoutScalable_Avkon::list_touch_info_pane( 1 ); // with heading
    TRect rectInfoPane = RectFromLayout( rectPopUpWindow, infoPaneLayout );

    TAknTextComponentLayout textLayout =
        AknLayoutScalable_Avkon::list_single_touch_info_pane_t1();
    TAknLayoutText textRect;
    textRect.LayoutText( rectInfoPane, textLayout );


    TRgb textColor = KRgbBlack;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG55 );
    AknLayoutUtils::OverrideControlColorL( *iTitleText, EColorLabelText,
        textColor );


    // Font for command links
    iFont = textRect.Font();

    if( iText )
        {
        textRect.LayoutText( rectInfoPane, textLayout );

        CArrayFixFlat<TInt>* lineWidths 
            = new ( ELeave ) CArrayFixFlat<TInt>( KMaxNbrOfInfoLines );
        CleanupStack::PushL( lineWidths );

        for ( TInt i = 0; i < KMaxNbrOfInfoLines; i++ )
            {
            lineWidths->AppendL( textRect.TextRect().Width() );
            }
                
        // get correct font from layout
        const CFont *font = textRect.Font();
            
        // parse text
        iText->ParseTextL( font, lineWidths );
        CleanupStack::PopAndDestroy( lineWidths );
            
        if ( iText->Line( 1 ) )
            {
            // text didn't fit in one line -> change layout to allow 2 lines
            variety++;

            rectPopUpWindow = PopUpWindowRectFromLayout(
                AknLayoutScalable_Avkon::popup_touch_info_window( variety ) );
                
            rectInfoPane = RectFromLayout( rectPopUpWindow, infoPaneLayout );
            textRect.LayoutText( rectInfoPane, textLayout );

            lineWidths 
                = new ( ELeave ) CArrayFixFlat<TInt>( KMaxNbrOfInfoLines );
            CleanupStack::PushL( lineWidths );
            for ( TInt i = 0; i < KMaxNbrOfInfoLines; i++ )
                {
                lineWidths->AppendL( textRect.TextRect().Width() );
                }
            // parse text
            iText->ParseTextL( font, lineWidths );
            CleanupStack::PopAndDestroy( lineWidths );
            }
        AknLayoutUtils::OverrideControlColorL( *iText, EColorLabelText,
            textColor );
        }
    }


// -----------------------------------------------------------------------------
// CAknStylusActivatedPopUpContent::ConstructL
// -----------------------------------------------------------------------------
//
void CAknStylusActivatedPopUpContent::ConstructL(
        const TDesC& aTitleText, 
        const TDesC& aText, 
        const RArray<TAknContentLink>& aLinkArray )
    {
    if ( &aLinkArray )
        {
        __ASSERT_ALWAYS( ( aLinkArray.Count() > 0 ) && 
                         ( aLinkArray.Count() <= KMaxNbrOfCmdLinks ),
                         Panic( EAknPanicOutOfRange ) );


        for ( TInt i = 0; i < aLinkArray.Count(); i++ )
            {
            CAknStylusActivatedItem* item = 
                new (ELeave) CAknStylusActivatedItem; 
            CleanupStack::PushL( item ); 
            item->ConstructL( *( aLinkArray[i].iLinkText ), 
                aLinkArray[i].iLinkId ); 
            iLinkArray.AppendL( item ); 
            CleanupStack::Pop( item ); 
            }
        ConstructL( aTitleText, aText );
        }
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::ComponentControl
// -----------------------------------------------------------------------------
//
#ifdef RD_SCALABLE_UI_V2
EXPORT_C CCoeControl* CAknStylusActivatedPopUpContent::ComponentControl(
        TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return iTitleText;
        case 1:
            if( iText )
                {
                return iText;
                }
        default:
            __ASSERT_ALWAYS( aIndex >= 0, Panic( EAknPanicOutOfRange ) );
            return NULL;
        }
    }
#else
EXPORT_C CCoeControl* CAknStylusActivatedPopUpContent::ComponentControl(
        TInt /*aIndex*/ ) const
    {
    return NULL;
    }
#endif // RD_SCALABLE_UI_V2


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::CountComponentControls
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknStylusActivatedPopUpContent::CountComponentControls() const
    {
#ifdef RD_SCALABLE_UI_V2
    TInt count = 0;
    if( iTitleText ) 
        {
        count++;
        }
    if( iText ) 
        {
        count++;
        }
    return count;
#else
    return 0;
#endif // RD_SCALABLE_UI_V2
    }


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::Draw
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStylusActivatedPopUpContent::Draw(
        const TRect& aRect ) const
    {
#ifdef RD_SCALABLE_UI_V2
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if ( aRect.Intersects( Rect() ) )
        {
        TRect rect( Rect() );
        
        TRect headingAreaRect( AlignedRectFromLayout( 
            AknLayoutScalable_Avkon::heading_sub_pane() ) );
            
        TRect headingBgRect( RectFromLayout( headingAreaRect,
            AknLayoutScalable_Avkon::bg_popup_heading_pane_cp() ) );

        TRect headingCenterRect( RectFromLayout( headingBgRect,
            AknLayoutScalable_Avkon::bg_popup_heading_pane_g1() ) );
        
        AknsDrawUtils::DrawFrame( skin, gc, headingBgRect, headingCenterRect,
                                  KAknsIIDQsnFrPopupHeading,
                                  KAknsIIDQsnFrPopupHeadingCenter );
        }

    gc.Reset(); 

    TRgb textColor;
    AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnHighlightColors,
                               EAknsCIQsnHighlightColorsCG3 );

    gc.SetPenStyle( CGraphicsContext::ESolidPen ); 
    gc.SetPenColor( textColor );

    TRgb highlightcolor = AKN_LAF_COLOR( 244 );
    AknsUtils::GetCachedColor( skin, highlightcolor, 
        KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG1 ); 

    gc.SetBrushColor( highlightcolor ); 
    const CFont* font = iFont;
    if ( !font )
        {
        font = iCoeEnv->NormalFont();
        }
    gc.UseFont( font );

    gc.SetUnderlineStyle( EUnderlineOn );

    for ( TInt i=0; i < iLinkArray.Count(); i++ )
        {
        if ( !aRect.Intersects( iLinkArray[i]->iRect ) )
            {
            continue; 
            }

        TRect rect( iLinkArray[i]->iRect );
        if ( Background() )
            {
            Background()->Draw( gc, *this, rect );
            }

        // buffer for visually ordered text
        HBufC* visualText(NULL);
        TRAPD( err, visualText = HBufC::NewL( 255 + 
            KAknBidiExtraSpacePerLine ) ); 
        if ( err != KErrNone )
            {
            return; 
            }
        TPtr ptr = visualText->Des(); 
        TInt clipWidth = rect.Width();

        if ( iHighlightedItem == i ) 
            {
            gc.SetBrushStyle( CGraphicsContext::ESolidBrush ); 
            }
        else
            {
            gc.SetBrushStyle( CGraphicsContext::ENullBrush );
            }

        // bidi processing - using AknBidiTextUtils.
        AknBidiTextUtils::ConvertToVisualAndClip(
            *(iLinkArray[i]->iText),
            ptr,
            *font,
            clipWidth,
            clipWidth );

        TInt baselineOffset = 0;
        baselineOffset = font->AscentInPixels() +
            ( rect.Height() - font->AscentInPixels() ) / 2;
        gc.DrawText( ptr, rect, baselineOffset, 
            CGraphicsContext::ELeft );
        delete visualText; 
        }
#endif // RD_SCALABLE_UI_V2
    }


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::MinimumSize
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CAknStylusActivatedPopUpContent::MinimumSize()
    {    
#ifdef RD_SCALABLE_UI_V2
    TInt nbrOfInfoLines = 0;
    if( iText )
        {
        nbrOfInfoLines = iText->NumberOfLines();
        }
            
    TPtrC ptrLabel =( *iTitleText->Text() );
    TInt minWidth = iTitleText->CalcMinimumSize( ptrLabel ).iWidth;
      
    CEikLabel* textLabel; 
    for ( TInt i=0; i < nbrOfInfoLines; i++ )
        {
        textLabel = static_cast<CEikLabel*>(iText->ComponentControl(i));
        TPtrC ptrText = ( *textLabel->Text() );
        minWidth = Max( textLabel->CalcMinimumSize( ptrText ).iWidth, minWidth ); 
        }

    // choose the longest one
    for ( TInt i = 0; i < iLinkArray.Count(); i++ )
        {
        TInt tempWidth = iFont->TextWidthInPixels( *( iLinkArray[i]->iText ) );
        minWidth = Max( minWidth, tempWidth );
        }

    TRect tempRect; 
    TInt rectWidth = 0;  
    TAknWindowComponentLayout infoPaneLayout = 
        AknLayoutScalable_Avkon::list_touch_info_pane( 1 ); // with heading
    
    // Check layout data varieties from largest to smallest    
    for ( TInt i=7; i >= 4; i-- )
        {
        tempRect = RectFromLayout( iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_touch_info_window( i ) );

        TRect rectInfoPane = RectFromLayout( tempRect, infoPaneLayout );

        TAknTextComponentLayout textLayout =
            AknLayoutScalable_Avkon::list_single_touch_info_pane_t1();
        TAknLayoutText textRect;
        textRect.LayoutText( rectInfoPane, textLayout );

            
        if ( textRect.TextRect().Width() > minWidth || !rectWidth )
            {
            rectWidth = rectInfoPane.Width(); 
            }
        else 
            {
            break; 
            }
        }
    TInt variety = GetVariety( nbrOfInfoLines +
                                   iLinkArray.Count() );
    TRect rectPopUpWindow =  PopUpWindowRectFromLayout( 
        AknLayoutScalable_Avkon::popup_touch_info_window( variety ) );

    TAknWindowComponentLayout headingPaneLayout = 
        AknLayoutScalable_Avkon::heading_sub_pane(); // with heading

    TRect rectInfoPane = RectFromLayout( rectPopUpWindow, infoPaneLayout );
    TRect rectHeadingPane = RectFromLayout( rectPopUpWindow, headingPaneLayout );
    TInt rectHeight = rectInfoPane.Height() + rectHeadingPane.Height(); 

    return TSize( rectWidth, rectHeight ); 
#else
    return TSize();
#endif // RD_SCALABLE_UI_V2
    }


// -----------------------------------------------------------------------------
// From class CCoeControl.
// CAknStylusActivatedPopUpContent::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStylusActivatedPopUpContent::SizeChanged()
    {
#ifdef RD_SCALABLE_UI_V2
    TInt nbrOfInfoLines = 0;
    if( iText )
        {
        nbrOfInfoLines = iText->NumberOfLines();
        }
    TInt nbrOfCmdLines = iLinkArray.Count();

    TInt variety = GetVariety( nbrOfInfoLines + nbrOfCmdLines );

    TRect rectHeadingSubPane( AlignedRectFromLayout(
        AknLayoutScalable_Avkon::heading_sub_pane() ) );

    TAknLayoutText layoutText;
    layoutText.LayoutText( rectHeadingSubPane,
        AknLayoutScalable_Avkon::heading_sub_pane_t1() );
          
    iTitleText->SetRect( layoutText.TextRect() );
    iTitleText->SetFont( layoutText.Font() );

    TAknTextLineLayout textLayout;
    TRect rectSingleInfoPane;
    TInt textrow = 0;
    
    // with heading
    TRect rectInfoPane( AlignedRectFromLayout(
        AknLayoutScalable_Avkon::list_touch_info_pane( 1 ) ) );

    if( iText )
        {
        iText->SetRect( rectInfoPane );
        textLayout =
            AknLayoutScalable_Avkon::list_single_touch_info_pane_t1();
        TAknLayoutText layoutText; 
            
        // set rects/layouts for info text lines
        for ( ; textrow < nbrOfInfoLines; textrow++ )
            {
            rectSingleInfoPane = RectFromLayout( rectInfoPane,
                AknLayoutScalable_Avkon::list_single_touch_info_pane( textrow ) );
            layoutText.LayoutText( rectSingleInfoPane, textLayout ); 
            iText->Line( textrow )->SetRect( layoutText.TextRect() ); 
            iText->Line( textrow )->SetFont( layoutText.Font() ); 
            }
        }

    // layout data for cmd texts
    textLayout = AknLayoutScalable_Avkon::list_single_touch_info_pane_t2();

    // set rects/layouts for cmd links
    for ( TInt i = 0; i < nbrOfCmdLines; i++ )
        {
        rectSingleInfoPane = RectFromLayout( rectInfoPane,
            AknLayoutScalable_Avkon::list_single_touch_info_pane( textrow++ ) );

        layoutText.LayoutText( rectSingleInfoPane, textLayout );
        if ( i == 0 )
            {
            iFont = layoutText.Font(); 
            }
        TInt tempWidth = iFont->TextWidthInPixels( *(iLinkArray[i]->iText) );
        TRect tempRect = TRect( layoutText.TextRect() ); 
        tempRect.SetWidth( Min( tempWidth, layoutText.TextRect().Width() ) );

        iLinkArray[i]->iRect = tempRect;
        }
#endif // RD_SCALABLE_UI_V2
    }

// -----------------------------------------------------------------------------
// RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknStylusActivatedPopUpContent::RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, lineLayout );
    return layoutRect.Rect();
    }

// -----------------------------------------------------------------------------
// PopUpWindowRectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknStylusActivatedPopUpContent::PopUpWindowRectFromLayout( const
    TAknWindowComponentLayout& aComponentLayout ) const
    {
    // get popup window width from the widest variety
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    lineLayout.iW = AknLayoutScalable_Avkon::
        popup_touch_info_window( 3 ).LayoutLine().iW;
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( iAvkonAppUi->ApplicationRect(), lineLayout );

    return layoutRect.Rect();
    }

// -----------------------------------------------------------------------------
// AlignedRectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknStylusActivatedPopUpContent::AlignedRectFromLayout( 
    const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    
    TRect rect( Rect() );
    layoutRect.LayoutRect( rect, lineLayout );
    
    TRect result( rect.iTl.iX, layoutRect.Rect().iTl.iY - rect.iTl.iY, rect.iBr.iX, 
        layoutRect.Rect().iBr.iY - rect.iTl.iY );
    
    return result;
    }

// -----------------------------------------------------------------------------
// GetVariety
// -----------------------------------------------------------------------------
//
TInt CAknStylusActivatedPopUpContent::GetVariety( const TInt aNbrOfLines )
    {
    // Heading is mandatory -> varieties 0...3 are omitted
    switch ( aNbrOfLines )
        {
        case 1:
            // 1 row of text (info/command)
            return 4;
        case 2:
            // 2 rows of text (2 info / 2 cmds / 1 info, 1 cmds)
            return 5;
        case 3:
            // 3 rows of text (1 info, 2 cmds / 2 info, 1 cmd)
            return 6;
        case 4:
            // 4 rows of text (2 info, 2 cmds)
            return 7;
        default:
            return 4;
        }
    }
    
    
// -----------------------------------------------------------------------------
// From class CCoeControl
// CAknStylusActivatedPopUpContent::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknStylusActivatedPopUpContent::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )     
    {
#ifdef RD_SCALABLE_UI_V2
    for ( TInt i=0; i < iLinkArray.Count(); i++ )
        {
        if ( iLinkArray[i]->iRect.Contains( aPointerEvent.iPosition ) )
            {
            if ( iHighlightedItem != i )
                {
                TInt previousItem = iHighlightedItem; 
                iHighlightedItem = i; 
                if ( previousItem != KNoItemHighlighted )
                    {
                    DrawNow( iLinkArray[previousItem]->iRect );
                    }
                DrawNow( iLinkArray[iHighlightedItem]->iRect );
                }
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                
                if ( feedback )
                    {
                    feedback->InstantFeedback( ETouchFeedbackBasic );
                    }
                }

            // Nofity command observer  
            if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                {
                iCommandObserver->ProcessCommandL( iLinkArray[i]->iCommandId );
                }
            }
        }
#endif // RD_SCALABLE_UI_V2
    }
    
