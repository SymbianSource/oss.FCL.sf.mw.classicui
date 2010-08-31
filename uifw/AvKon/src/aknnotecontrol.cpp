/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/


#include <eikimage.h>
#include <eikprogi.h>

#include <avkon.mbg>
#include <aknconsts.h>
#include <AknPanic.h>
#include <AknUtils.h>
#include <AknLayoutDef.h>
#include <AknLayout.lag>

#include "aknnotecontrol.h"
#include "notelaf.h"
#include "aknnoteattributes.h"
#include "akntextcontrol.h"

#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <eikbtgpc.h>  // CEikButtonGroupContainer

// Skin layout macros
#include <skinlayout.cdl.h>
using namespace SkinLayout;

#include <AknIconUtils.h>
#include "aknappui.h"

#include <eikdialg.h>
#include <eikdialogext.h>
#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks
const TInt KRate = 95;    // 95% similar rate
const TInt KFullColor = 255;

// ---------------------------------------------
// CONSTRUCTION - DESTRUCTION
// ---------------------------------------------

/**
 * The class default constructor. 
 *
 * 
 */
EXPORT_C CAknNoteControl::CAknNoteControl()
    {
    AKNTASHOOK_ADD( this, "CAknNoteControl" );
    }

/**
 * The class destructor. 
 *
 * 
 */
EXPORT_C CAknNoteControl::~CAknNoteControl()
    {
    AKNTASHOOK_REMOVE();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl( this );
        }

    delete iAttributes;
    delete iLineWidths;
    }

void CAknNoteControl::ConstructFromResourceL(TResourceReader &aRes)
    {
    
    delete iLineWidths;
    iLineWidths = 0;

    iLineWidths = new(ELeave)CArrayFixFlat<TInt>(5);
    iNoteLayout = aRes.ReadUint16();

    delete iAttributes;
    iAttributes = NULL;
    iAttributes = new (ELeave)CAknNoteAttributes(this);
    iAttributes->ConstructFromResourceL(aRes);
    
    CreateDefaultImageL();
    ReduceImageIfNeeded();

    ParseTextL();
    
    iAttributes->iBgContext->SetCenter(KAknsIIDQsnFrPopupCenterNote);
    
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        CEikDialog* dlg;
        MopGetObject( dlg );
        if ( dlg )
            {
            dlg->Extension()->iPublicFlags.Set( CEikDialogExtension::EClipChildControlRect );
            }
        }
    }

void CAknNoteControl::Reset()
    {
    // Used by sleeping notes when going to background,
    // in order to stop and delete animations
    CancelAnimation();
    }


// -----------------------------------------
//  CCOECONTROL METHODS
// -----------------------------------------
void CAknNoteControl::Draw(const TRect& /*aRect*/) const
    {   
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    MAknsControlContext* cc = iAttributes->iBgContext;
    
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    //Controls _have_to_ get gc through CCoeControl::SystemGc to be transition compatible.
    CWindowGc& gc = SystemGc();
#else    
    //iAttributes->iBgRect should be always valid
    CWindowGc& gc = iCoeEnv->SystemGc();
#endif  

    TBool oomError = EFalse;
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        oomError = !AknsDrawUtils::Background( skin, cc, this, gc,
            iAttributes->iBgRect.IsEmpty()?LayoutRect():iAttributes->iBgRect, KAknsDrawParamNoClearUnderImage);
        }
    else
        {
        oomError = !AknsDrawUtils::Background( skin, cc, this, gc,
            iAttributes->iBgRect.IsEmpty()?LayoutRect():iAttributes->iBgRect, KAknsDrawParamDefault);
        }

    if( oomError )
    {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;
        TInt error = AknsUtils::GetCachedColor( skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

        TInt redcolor = color.Red();
        TInt bluecolor = color.Blue();
        TInt greencolor = color.Green();
        // test if the color is too similar to white color
        if ( redcolor > KFullColor * KRate / 100 || 
             bluecolor > KFullColor * KRate / 100 || 
             greencolor > KFullColor * KRate / 100 )
            {
            color = KRgbBlack;
            }
        for (TInt i=0; i < NumberOfLines(); i++)
            {
            AknLayoutUtils::LayoutLabel
             ( TextControl()->Line( i ),LayoutRect(),AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1( i ) );

            if (!error)
                {
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *TextControl()->Line(i), 
                    EColorLabelText, color ) );
                }
            }
    }
    if (iImageHasShadow)
        {
        iShadowRect.DrawRect( gc );
        }   
    }
    
EXPORT_C void CAknNoteControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    if (iAttributes->iFlags.IsSet( ENoteLeftSKWhenTapped ) && 
       (aPointerEvent.iType == TPointerEvent::EButton1Up) &&
       Rect().Contains( aPointerEvent.iPosition ) )
        {
        // Left soft key press
        TRawEvent event;
        event.Set(TRawEvent::EKeyDown, EStdKeyDevice0);
        CEikonEnv::Static()->WsSession().SimulateRawEvent(event);
        event.Set(TRawEvent::EKeyUp, EStdKeyDevice0);
        CEikonEnv::Static()->WsSession().SimulateRawEvent(event);
        }
    }

EXPORT_C void* CAknNoteControl::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

CCoeControl* CAknNoteControl::ComponentControl(TInt aIndex) const
    {
    const CCoeControl* controls[] = {Icon(),TextControl(),ProgressBar(),
                                        Image(),Animation()};
    for (TUint ii=0;ii<sizeof(controls)/sizeof(CCoeControl*);ii++)
      if (controls[ii] && aIndex-- == 0)
          return const_cast<CCoeControl*>(controls[ii]);
    return NULL;
    }


TInt CAknNoteControl::CountComponentControls() const
    {
    if (!Attributes())
        {
        return 0;
        }
    TInt count = 0;
    const CCoeControl* controls[] = { Icon(),TextControl(),ProgressBar(),
                                        Image(), Animation() };
    for (TUint ii=0;ii<sizeof(controls)/sizeof(CCoeControl*);ii++)
        if (controls[ii])
            count++;
    return count;
    }

TSize CAknNoteControl::MinimumSize()
    {   
    TAknWindowLineLayout dialogLay;
    WindowLayout( dialogLay );

    TAknLayoutRect dialogLayRect;
    dialogLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(), dialogLay);
    TSize dialogSize = dialogLayRect.Rect().Size();
#ifndef RD_NO_DIALOG_BORDERS
    TRect parent(TPoint(0,0),dialogSize);

    TAknWindowLineLayout internalLay = AKN_LAYOUT_WINDOW_Note_pop_up_window_graphics_Line_5(parent);

    if ( iNoteLayout == ENotificationWithGraphicsLayout ||
         iNoteLayout == ETextualNotificationLayout )
        {
        internalLay = AKN_LAYOUT_WINDOW_Notification_pop_up_window_graphics__text__Line_5(parent);
        }

    TAknLayoutRect internalLayRect;
    internalLayRect.LayoutRect(parent, internalLay);

    return internalLayRect.Rect().Size();
#else
    return dialogSize;
#endif
    }

/**
 * Do layout. 
 *
 * Always do layout even when there might be no need for it (e.g.
 * because nothing has changed). This method is called by the 
 * CONE framework when the size or position of the control is
 * changed and hence layout must always be done. 
 *
 * Do not call this method when you need to do layout for reasons
 * different than the size or position of the control changing.
 * Call Layout instead.
 */
void CAknNoteControl::SizeChanged()
    {  
    DoLayout();
    }

/** 
 * Code shared between SizeChanged() and Layout().
 *
 */
void CAknNoteControl::DoLayout()
    {
    TextControl()->SetRect(LayoutRect());
    switch(iNoteLayout)
        {
    case EGeneralLayout:
        GeneralNoteLayout();
        if(iAttributes->iFlags.IsSet(ENoteAnimationStarted))
            {
            CancelAnimation();
            TRAP_IGNORE(StartAnimationL());
            }
        break;
    case EProgressLayout:
    case EWaitLayout:
        {
        ProgressNoteLayout();
        if(iAttributes->iFlags.IsSet(ENoteAnimationStarted))
            {
            iAttributes->CancelAnimation();
            TRAP_IGNORE(iAttributes->StartAnimationL());
            }
        break;
        }
    case ENoteWithImageLayout:
    case ETextualNotificationLayout:
    case ENotificationWithGraphicsLayout:
        ImageNoteLayout();
        break;
        }

    Attributes()->SetLayoutDone(CAknNoteAttributes::EControl);

    if ( iAttributes->iFlags.IsSet( ENoteLeftSKWhenTapped ) )
        {
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        CFeedbackSpec* spec = CFeedbackSpec::New();
        if ( feedback && spec )
            {
            spec->AddFeedback( ETouchEventStylusDown, 
                               ETouchFeedbackBasicButton );
            spec->AddFeedback( ETouchEventStylusUp, 
                               ETouchFeedbackBasicButton,
                               ETouchFeedbackVibra );
            feedback->SetFeedbackArea( this, 0, Rect(), spec );
            delete spec;
            }
        }
    }

/**
 *
 * This is used by a dialog to layout the control correctly.
 *
 */
void CAknNoteControl::WindowLayout( TAknWindowLineLayout& aLayout ) const
    {
    TIndex laf(NumberOfLines());
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
    TInt variety( 0 );
    
    switch(iNoteLayout)
        {
        case ENoteWithImageLayout:
            if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
                {
                variety = 1;
                }
            else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
                {
                variety = 2;
                }
            else
                {
                variety = 0;
                }
                        
            aLayout = AknLayoutScalable_Avkon::popup_note_image_window( variety );
            break;
        case ETextualNotificationLayout:
            if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
                {
                variety = 4;
                }
            else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
                {
                variety = 8;
                }
            else
                {
                variety = 0;
                }
            
            aLayout = AknLayoutScalable_Avkon::popup_snote_single_text_window( variety +
                (laf.Lines() >= 2 ? laf.Lines() - 1 : 0) );
            break;
        case ENotificationWithGraphicsLayout:
            if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
                {
                variety = 4;
                }
            else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
                {
                variety = 8;
                }
            else
                {
                variety = 0;
                }
            
            aLayout = AknLayoutScalable_Avkon::popup_snote_single_graphic_window( variety +
                (laf.Lines() >= 2 ? laf.Lines() - 1 : 0) );
            break;
        case EProgressLayout:
        case EWaitLayout:
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
            
            aLayout = AknLayoutScalable_Avkon::popup_note_wait_window( variety +
                laf.PopupNoteWaitWindow() );
            break;

        case EGeneralLayout:
        default: //default case should never be the case
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
            
            aLayout = AknLayoutScalable_Avkon::popup_note_window( variety +
                laf.PopupNoteWindow() );
            break;
        }
    }

/**
 * Return the note height 
 *
 * The note height is taken from the layout compiler and
 * depends on number of lines and the note layout type. 
 * 
 * @return The note height in pixels.
 */
EXPORT_C TInt CAknNoteControl::NoteHeight() const
    {
    TAknWindowLineLayout dialogLay;
    WindowLayout( dialogLay );

    TAknLayoutRect windowLayRect;
    windowLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(), dialogLay);
    return windowLayRect.Rect().Height();
    }

/**
 * Return the note width 
 *
 * The note width is taken from the layout compiler. 
 * Contrary to the note height, the note width does not depend on
 * from note layout type or on number of lines. 
 * 
 * @return The note width in pixels
 */
EXPORT_C TInt CAknNoteControl::NoteWidth() const
    {
    TAknWindowLineLayout dialogLay;
    WindowLayout( dialogLay );

    TAknLayoutRect windowLayRect;
    windowLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(), dialogLay);
    return windowLayRect.Rect().Width();
    }


// ----------------------------------------
//  LAYOUT METHODS
// ----------------------------------------

/**
 *  GENERAL NOTES LAYOUT
 */
void CAknNoteControl::GeneralNoteLayout()
    {
    GeneralNoteLabelLayout();
    GeneralNoteIconLayout();
    }

/**
 * Layout for text in general notes
 */
void CAknNoteControl::GeneralNoteLabelLayout()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

    for (TInt i=0; i < NumberOfLines(); i++)
        {
        AknLayoutUtils::LayoutLabel
         (TextControl()->Line(i),LayoutRect(),AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(i));

        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *TextControl()->Line(i), 
                EColorLabelText, color ) );
            }
        }
    }

/**
 * Layout for image or animation in general notes
 */
void CAknNoteControl::GeneralNoteIconLayout()
    {
    if (Image())
        AknLayoutUtils::LayoutImage(Image(), LayoutRect(), AKN_LAYOUT_WINDOW_Note_pop_up_window_elements_Line_1);

    if (Animation())
        AknLayoutUtils::LayoutControl(Animation(), LayoutRect(), AKN_LAYOUT_WINDOW_Note_pop_up_window_elements_Line_1);
    }



/**
 *  PROGRESS NOTES LAYOUT
 */
void CAknNoteControl::ProgressNoteLayout()
    {
    ProgressNoteLabelLayout();
    ProgressNoteProgressBarLayout();
    ProgressNoteIconLayout();
    ProgressNoteNumberTypeIndicationLayout();
    }

/**
 * Layout for text in progress notes
 */
void CAknNoteControl::ProgressNoteLabelLayout()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

    TInt nLines = Min (KPNMaxNumLines, NumberOfLines());
    TIndex lafIndex(nLines,Icon()!=NULL);

    for (TInt i=0; i < nLines; i++)
        {
        AknLayoutUtils::LayoutLabel( TextControl()->Line(i),
            LayoutRect(),AKN_LAYOUT_TEXT_Wait_or_progress_note_pop_up_window_texts_Line_1
         (lafIndex.WNPWindowTextsLine1(i),i,i));

        if (!error)
          {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *TextControl()->Line(i), 
                EColorLabelText, color ) );
            }
        }
    }

/**
 * Layout for progress bar in progress notes
 */
void CAknNoteControl::ProgressNoteProgressBarLayout()
    {
    TInt nLines = Min (KPNMaxNumLines, NumberOfLines());

    // New parameter added to Wait_or_progress_note_pop_up_window_elements_Line_2 layout API.
    TInt tIndex = 0;
    if (nLines == 3)
        {
        tIndex = 1;
        }
    if (nLines >= 4)
        {
        tIndex = 2;
        }

    if (ProgressBar())
        AknLayoutUtils::LayoutControl(ProgressBar(), LayoutRect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_2(tIndex));
    
    if(Animation()) //Progress Bar Animation
        AknLayoutUtils::LayoutControl(Animation(), LayoutRect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_2(tIndex));
    }

/**
 * Layout for icon in progress notes
 */
void CAknNoteControl::ProgressNoteIconLayout()
    {   
    if (Image())
        AknLayoutUtils::LayoutImage(Image(), LayoutRect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_1);
    }

/**
 * Layout for nti (number type indication) icon in progress notes
 */
void CAknNoteControl::ProgressNoteNumberTypeIndicationLayout()
    {
    if (Icon())
        AknLayoutUtils::LayoutImage(Icon(), LayoutRect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_4);
    }

/**
 * IMAGE NOTES LAYOUT
 */
void CAknNoteControl::ImageNoteLayout()
    {
    ImageNoteLabelLayout();
    if ( iNoteLayout != ENotificationWithGraphicsLayout &&
         iNoteLayout != ETextualNotificationLayout )
        {
        ImageNoteShadowLayout();
        }
    else if ( iAttributes )
        {
        iAttributes->iBgContext->SetCenter(KAknsIIDQsnFrPopupCenterSnote);
        }
    
    ImageNoteImageLayout();
    AnimationNoteLayout();
    ImageNoteNumberTypeIndicationLayout();
    }

/**
 * Layout for text in image notes
 */
void CAknNoteControl::ImageNoteLabelLayout()
    {
    
    TInt nLines = NumberOfLines();

    TSize imageSize = Image() ? Image()->Bitmap()->SizeInPixels() : 
        Animation() ? Animation()->BitmapAnimData()->Size() : TSize(0,0);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

    if ( iNoteLayout == ENoteWithImageLayout ) 
        {
        nLines = Min(KINMaxNumLines, nLines);
    
        TIndex lafIndex(nLines,Icon()!=NULL,imageSize);
        
        for (TInt i=0; i < nLines; i++)
            {

            AknLayoutUtils::LayoutLabel(TextControl()->Line(i),LayoutRect(),
                AKN_LAYOUT_TEXT_Note_with_an_image_pop_up_window_texts_Line_1(
                lafIndex.NWIPWindowTextsLine1L(i),lafIndex.NWIPWindowTextsLine1R(i),
                lafIndex.NWIPWindowTextsLine1B(i),lafIndex.NWIPWindowTextsLine1W(i)));

            if (!error)
              {
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *TextControl()->Line(i), 
                    EColorLabelText, color ) );
              }
            }
        }
    else // Soft Notification layouts
        {   
        for (TInt i=0; i < nLines; i++)
            {
            AknLayoutUtils::LayoutLabel(
                TextControl()->Line(i),
                LayoutRect(),
                (!imageSize.iWidth)?
                AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__text__Line_1(i):
                AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__graphic__Line_1(i));

            if (!error)
              {
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *TextControl()->Line(i), 
                    EColorLabelText, color ) );
              }
            }

        }
    }

/**
 * Layout for animation in image notes
 */
void CAknNoteControl::AnimationNoteLayout()
    {
    if (Animation())
        AknLayoutUtils::LayoutControl(Animation(), LayoutRect(), 
                GetImageLayout(Animation()->BitmapAnimData()->Size()) );
    }


/**
 * Layout for image in image notes
 */
void CAknNoteControl::ImageNoteImageLayout()
    {
    if (Image())
        {
        AknLayoutUtils::LayoutImage(Image(), LayoutRect(), 
            GetImageLayout(Image()->Bitmap()->SizeInPixels()));
        }
    }

/**
 * Layout for image shadow in image notes
 */
void CAknNoteControl::ImageNoteShadowLayout()
    {
    if (Image())
        {
        iShadowRect.LayoutRect( LayoutRect(), 
            GetImageShadowLayout(Image()->Bitmap()->SizeInPixels()) );
        
        iImageHasShadow = ETrue;
        }
    }

/**
 * Layout for number type indication in image notes
 */
void CAknNoteControl::ImageNoteNumberTypeIndicationLayout()
    {
    if ( iNoteLayout == ETextualNotificationLayout || iNoteLayout == ENotificationWithGraphicsLayout )
        {
        return;
        }   

    if (Icon())
        {
        AknLayoutUtils::LayoutImage(Icon(), LayoutRect(), AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_13);
        }
    }

/**
 * Return layout table to be used for images in image notes.
 * Table is different according to image size,
 *
 * Images with a size different from the supported sizes are laid out 
 * as if they were 44X48 images. If they are smaller their
 * size is used. If they are bigger the are cropped to 44X48 
 * (@see ReduceImageIfNeeded)
 */
TAknWindowLineLayout CAknNoteControl::GetImageLayout(const TSize& /*aSize*/) 
    {
    // can go on with the biggest
    TAknWindowLineLayout lay (AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_12);

    if ( iNoteLayout == ENotificationWithGraphicsLayout )
        {
        lay = AKN_LAYOUT_WINDOW_Notification_pop_up_window_elements__graphic__Line_2;
        }

    return lay;
    }

/**
 * Return layout table to be used for image shadows in image notes.
 * Table is different according to image size.
 *
 * Shadows for images with a size different than the supported sizes are laid 
 * out as if they were biggest supported images. If they are smaller their
 * size is used. If they are bigger the are cropped to the biggest supported size 
 * (@see ReduceImageIfNeeded)
 */
TAknWindowLineLayout CAknNoteControl::GetImageShadowLayout(const TSize& /*aSize*/) 
    {
    // can go on with the biggest
    TAknWindowLineLayout lay (AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_11);
    return lay; 
    }


/**
 * Do layout.
 *
 * Before doing layout parse the text (This might be redundant except
 * when the control attributs are trasfered but is left here to avoid
 * breaking the functionality of this exported method).
 *
 * Layout is done only if it is needed, i.e. if the attributes indicates
 * that something has changed in such a way that layout needs to be performed
 * again, e.g. a line of text has been added.
 *
 * This method assumes that the rect of the control has not been changed. On the
 * contrary, SizeChanged does not assume that the rect is the same and hence 
 * always performs layout.
 */
EXPORT_C void CAknNoteControl::Layout()
    {
    TRAP_IGNORE(ParseTextL());

    if (!Attributes()->IsLayoutNeeded(CAknNoteAttributes::EControl))
        return;

    DoLayout();

    }

/**
 * Return rectangle used in layout operations. 
 *
 * Layout information in LAF is relative to the size of the dialog and not to the
 * size of the internal area (dialog size - margins from UIKLAF). Therefore when
 * doing layout do not use Rect(), but LayoutRect() - which returns the size of the
 * dialog. Position is always (0,0) - top 
 *
 * @return Rectangle equal to dialog rectangle only shifted by the dialog margins
 */
TRect CAknNoteControl::LayoutRect() const
    {   
    TAknLayoutRect layout;
    
    TAknWindowLineLayout window;
    WindowLayout( window );    
    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    layout.LayoutRect( mainPane, window );
    TRect rect = layout.Rect().Size();
       
    if ( iNoteLayout == ENotificationWithGraphicsLayout ||
         iNoteLayout == ETextualNotificationLayout )
        {
        TAknLayoutRect layRect;
        TPoint topLeft = Position();
        layRect.LayoutRect(rect, AknLayoutScalable_Avkon::bg_popup_window_pane_cp9(0));
            
        topLeft.iX -= layRect.Rect().iTl.iX;
        topLeft.iY -= layRect.Rect().iTl.iY;

        TPoint bottomRight (topLeft);
        bottomRight.iY += rect.Height(); 
        bottomRight.iX += rect.Width();

        rect = TRect(topLeft,bottomRight);      
        }        
    return rect;
    }

/**
 * Use layout information to determine line widths
 */
void CAknNoteControl::SetLineWidthsL()
    {
    if (!iLineWidths)
        return;

    iLineWidths->Reset();

    TAknLayoutText text;
    switch(iNoteLayout)
        {
        case EGeneralLayout:
            {
            for (TInt i=0; i < KGNMaxNumLines; i++)
                {
                TAknTextLineLayout lay = AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(i);
                text.LayoutText(LayoutRect(), lay);
                TInt width = text.TextRect().Width();
                
                iLineWidths->AppendL(width,1);
                }
            }
            break;
        case EProgressLayout:
        case EWaitLayout:
            {
            TIndex lafIndex(KPNMaxNumLines,Icon()!=NULL);
            for (TInt i=0; i < KPNMaxNumLines; i++)
                {
                TAknTextLineLayout lay = AKN_LAYOUT_TEXT_Wait_or_progress_note_pop_up_window_texts_Line_1
                    (lafIndex.WNPWindowTextsLine1(i),i,i);
                text.LayoutText(LayoutRect(), lay);
                TInt width = text.TextRect().Width();
                
                iLineWidths->AppendL(width,1);
                }

            }
            break;
        case ENoteWithImageLayout:
            {        
            TSize imageSize = Image() ? Image()->Bitmap()->SizeInPixels() : 
                Animation() ? Animation()->BitmapAnimData()->Size() : TSize(0,0);

            TIndex lafIndex(KINMaxNumLines,Icon()!=NULL,imageSize);
        
            for (TInt i=0; i < KINMaxNumLines; i++)
                {
                TAknTextLineLayout lay = AKN_LAYOUT_TEXT_Note_with_an_image_pop_up_window_texts_Line_1(
                    lafIndex.NWIPWindowTextsLine1L(i),lafIndex.NWIPWindowTextsLine1R(i),
                    lafIndex.NWIPWindowTextsLine1B(i),lafIndex.NWIPWindowTextsLine1W(i));
                text.LayoutText(LayoutRect(), lay);
                TInt width = text.TextRect().Width();
            
                iLineWidths->AppendL(width,1);
                }
            }
            break;
        case ETextualNotificationLayout:
            {
            TAknTextLineLayout lay = AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__text__Line_1(0);                
            for (TInt i=0; i < KGNMaxNumLines; i++)
                {
                text.LayoutText(LayoutRect(), lay);
                TInt width = text.TextRect().Width();
                iLineWidths->AppendL(width,1);
                }
            }
            break;

        case ENotificationWithGraphicsLayout:
            {       
            for (TInt i=0; i < KGNMaxNumLines; i++)
                {
                TAknTextLineLayout lay = AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__graphic__Line_1(i>=2?i-1:0);
                text.LayoutText(LayoutRect(), lay);
                TInt width = text.TextRect().Width();
                iLineWidths->AppendL(width,1);
                }
            }
            break;
        }
    }

void CAknNoteControl::CreateDefaultImageL()
    {

    if (iNoteLayout == EWaitLayout || iNoteLayout == EProgressLayout) 
        {
        CEikImage* image = new(ELeave) CEikImage;
        CleanupStack::PushL(image);
        
        // Check if skinned image could be used
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
       
        AknsUtils::CreateIconL(
            skin, KAknsIIDQgnNoteProgress,
            bitmap, mask,
            KAvkonBitmapFile,
            EMbmAvkonQgn_note_progress, EMbmAvkonQgn_note_progress_mask);

        image->SetPicture(bitmap,mask);

        CleanupStack::Pop(); //image
        Attributes()->SetImageL(image);
        }
    }

/**
 *
 * The CONST CAST is ok because the bitmap is owned by the image
 */
void CAknNoteControl::ReduceImageIfNeeded()
    {
    if (Image())
        {
        // set the size of the image
        TAknLayoutRect rect;
        rect.LayoutRect( Rect(), 
            AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_12 );
        AknIconUtils::SetSize( CONST_CAST( CFbsBitmap*, Image()->Bitmap() ), 
            rect.Rect().Size() );
 
        // see if the bitmap size needs to be reduced
        TSize size = Image()->Bitmap()->SizeInPixels();

        TInt width = rect.Rect().Width();
        TInt height = rect.Rect().Height();
        if ( size.iWidth >= width || size.iHeight >= height )
            {//image does not fit
            TInt newWidth  = Min( size.iWidth,  width );
            TInt newHeight = Min( size.iHeight, height );

            if (Image()->Bitmap())
                CONST_CAST(CFbsBitmap*,Image()->Bitmap())->Resize(TSize(newWidth,newHeight));
            
            if (Image()->Mask())
                CONST_CAST(CFbsBitmap*,Image()->Mask())->Resize(TSize(newWidth,newHeight));
            }
        }
    }

void CAknNoteControl::ParseTextL()
    {
    TAknLayoutText textRect;

    if ( iNoteLayout == ENotificationWithGraphicsLayout || iNoteLayout == ETextualNotificationLayout )
        {
        textRect.LayoutText(LayoutRect(), AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__text__Line_1(1));
        }
    else 
        {
        textRect.LayoutText(LayoutRect(), AKN_LAYOUT_TEXT_Wait_or_progress_note_pop_up_window_texts_Line_1(1,1,1));
        }  

    const CFont *font = textRect.Font();
        
    SetLineWidthsL(); // Make the division again to prevent errors when resolution has changed
    Attributes()->ParseTextL( font, iLineWidths);
    }


// -------------------------------------------
// EXPORTED API
// -------------------------------------------

/**
 * Set the note image 
 *
 * Set the image in the note attributes. This reduces the
 * size of the image if necessary (only fixed set of
 * image sizes if supported). Perform layout only for
 * the control. The dialog will not be resized. 
 * 
 */
EXPORT_C void CAknNoteControl::SetImageL(CEikImage* aImage)
    {
    Attributes()->SetImageL(aImage);
    Layout();
    }

/**
 * Set the note animation 
 *
 * Set the animation in the note attributes.
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 * 
 */
EXPORT_C void CAknNoteControl::SetAnimationL(TInt aResource)
    {
    Attributes()->SetAnimationL(aResource);
    Layout();
    }

/**
 * Set the note icon 
 *
 * Set the icon in the note attributes.
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 * 
 */
EXPORT_C void CAknNoteControl::SetIconL(CEikImage* aIcon)
    { 
    Attributes()->SetIconL(aIcon);
    Layout();
    }

/**
 * Set the progress bar final value 
 *
 * Set the progress bar final value in the note attributes. 
 * 
 */
EXPORT_C void CAknNoteControl::SetFinalProgressValue(TInt aValue)
    {
    Attributes()->SetFinalProgressValue(aValue);
    }

/**
 * Increment the progress bar and draw
 * 
 * @see CEikProgressInfo
 */
EXPORT_C TInt CAknNoteControl::IncrementBarsAndDraw(TInt aIncrement)
    {
    return Attributes()->IncrementBarsAndDraw(aIncrement);
    }

/**
 * Create the progress bar
 *
 * @see CEikProgressInfo
 */
EXPORT_C void CAknNoteControl::CreateProgressBarL()
    {
    if ( ( iNoteLayout == EProgressLayout ) || ( iNoteLayout == EWaitLayout ) )
        {
        Attributes()->CreateProgressBarL();
        }
    else
        {
        User::Leave( KErrGeneral );
        }
    }

/**
 * Return the progress bar
 *
 * @return The progress bar
 *
 * @see CEikProgressInfo
 */

EXPORT_C CEikProgressInfo* CAknNoteControl::GetProgressInfo()
    {
    return ProgressBar();
    }

/**
 * Start the note animation
 *
 * @see CAknBitmapAnimation
 */
EXPORT_C void CAknNoteControl::StartAnimationL()
    {
    Attributes()->StartAnimationL();
    }

/**
 * Stop the note animation
 *
 * @see CAknBitmapAnimation
 */
EXPORT_C TInt CAknNoteControl::CancelAnimation()
    {
    return Attributes()->CancelAnimation();
    }

/**
 * Reset the note text
 *
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 *
 * @see CAknTextControl
 */
EXPORT_C void CAknNoteControl::ResetText()
    {
    // This can not Leave so no need to use TRAP 
    Attributes()->SetTextL(KNullDesC);
    Layout();
    }

/**
 * Set whole text for the note control.
 *
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 *
 */
EXPORT_C void CAknNoteControl::SetTextL(const TDesC& aText)
    {
    Attributes()->SetTextL(aText);
    Layout();
    }

/**
 * Set text for a specific line. Any previous text will be overwritten, 
 * except for the text that was set for other lines via this method.
 *
 * This method prevents ParseTextL from having any effect, hence text
 * control needs to know font and line width to allocate space.
 * 
 * This method is kept for backwards compatibility as the same 
 * results could be achieved by the other SetTextL with no wrapping 
 * enabled (flag in note attributes) and newline characters in the text to indicate
 * a new line.
 *
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 *
 */
EXPORT_C void CAknNoteControl::SetTextL(const TDesC& aText, TInt aLineNum)
    {
    TAknLayoutText textRect;
    
    if ( iNoteLayout == ENotificationWithGraphicsLayout || iNoteLayout == ETextualNotificationLayout )
        {
        textRect.LayoutText(LayoutRect(), AKN_LAYOUT_TEXT_Notification_pop_up_window_texts__text__Line_1(1));
        }
    else 
        {
        textRect.LayoutText(LayoutRect(), AKN_LAYOUT_TEXT_Wait_or_progress_note_pop_up_window_texts_Line_1(1,1,1));
        }  
    
    const CFont *font = textRect.Font();    

    Attributes()->SetTextL(aText, aLineNum, font, iLineWidths);
    Layout();
    }

/**
 * Set the number inside the note text. The text must have been 
 * previously set via resource or via SetTextL and must have a
 * \%d or \%N in it.
 *
 * Note:- This method could be replaced by a SetTextL method with 
 * a variable number of arguments.
 *
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 *
 */
EXPORT_C void CAknNoteControl::SetTextNumberL(const TInt aNumber)
    {
    Attributes()->SetTextNumberL(aNumber);      
    Layout();
    }

/**
 * Determine which text is to be used, either the text for
 * singular notes, e.g. "You have 1 new message" or the text
 * for plural notes, e.g. "You have %N new messages". These
 * texts must have been set via resource.
 *
 * Note:- This method could be replaced by a SetTextL method with 
 * a variable number of arguments.
 *
 * Perform layout only for the control. 
 * The dialog will not be resized. 
 *
 */
EXPORT_C void CAknNoteControl::SetTextPluralityL(const TBool aIsPlural)
    {
    Attributes()->SetTextPluralityL(aIsPlural); 
    Layout();
    }

/**
 * Return the number of lines.
 *
 */
EXPORT_C TInt CAknNoteControl::NumberOfLines() const
    {
    return TextControl()->NumberOfLines();
    }

/**
 *  @deprecated - use SetTextL instead
 */
EXPORT_C void CAknNoteControl::SetDynamicTextL(const TDesC& aText)
    {
    SetTextL(aText);
    }

/**
 * @deprecated - use SetTextL instead
 */
EXPORT_C void CAknNoteControl::UpdateAndFormatLabelsL(const TDesC& aLabels)
    {
    SetTextL(aLabels);
    }

/**
 * @deprecated - use SetTextL instead
 */
EXPORT_C void CAknNoteControl::UpdateLabelsL(const TDesC& aLabel1, const TDesC& aLabel2, const TDesC& aLabel3)
    {
    SetTextL(aLabel1, 0);
    SetTextL(aLabel2, 1);
    SetTextL(aLabel3, 2);
    }

/**
 * @deprecated - use SetTextL instead
 */
EXPORT_C void CAknNoteControl::UpdateLabels(const TDesC& aLabel1, const TDesC& aLabel2, const TDesC& aLabel3)
    {
    TRAP_IGNORE(UpdateLabelsL(aLabel1,aLabel2,aLabel3));
    }

/**
 * @deprecated - label length is taken care of already
 *
 * Don't use this method anymore.
 */
EXPORT_C void CAknNoteControl::SetLabelReserveLengthL(TInt /*aLength1*/, TInt /*aLength2*/, TInt /*aLength3*/)
    { 
    }

/**
* Following methods give access to note attributes
* Because these attributes are stored in CAknNoteAttributes,
* I've used indirection in case this changes in future
*/

CAknNoteAttributes* CAknNoteControl::Attributes() const 
    {
    return iAttributes;
    }

CAknTextControl* CAknNoteControl::TextControl() const 
    { 
    if (iAttributes)
        return iAttributes->iNoteText; 
    return NULL;
    }
    
CEikImage* CAknNoteControl::Image() const 
    {
    if (iAttributes)
        return iAttributes->iImage; 
    return NULL;
    }

CEikImage* CAknNoteControl::Icon() const 
    {
    if (iAttributes)
        return iAttributes->iIcon; 
    return NULL;
    }
    
CEikProgressInfo* CAknNoteControl::ProgressBar() const 
    {
    if (iAttributes)
        return iAttributes->iProgressBar; 
    return NULL;
    }
    
CAknProgressTimer* CAknNoteControl::Timer() const 
    {
    if (iAttributes)
        return iAttributes->iTimer;
    return NULL;
    }

CAknBitmapAnimation* CAknNoteControl::Animation() const 
    {
    if (iAttributes)
        return iAttributes->iAnimation; 
    return NULL;
    }
    
TBitFlags&  CAknNoteControl::Flags() const 
    {
    return Attributes()->iFlags;
    } 

/*****************************************************************
 * CAknNoteControl::TIndex
 *
 * Manage indexes into LAF tables
 *
 * NP   stands for "Note Popup"
 * WNP  stands for "Waiting/progress Note Popup"
 * NWIP stands for "Note With Image Popup"
 *
 ******************************************************************/

  
CAknNoteControl::TIndex::TIndex(TInt aNumberOfLines,TBool aHasNti, TSize aImageSize)
    : iNumberOfLines(aNumberOfLines),iHasNti(aHasNti), iImageSize (aImageSize)
    {
    }
        
void CAknNoteControl::TIndex::SelfTest() const
    {
    __ASSERT_DEBUG(iNumberOfLines >= 0  && iNumberOfLines <= 5,
        Panic(EAknPanicInvalidValue));
    }

TInt CAknNoteControl::TIndex::ImageWidthIndex() const
    {
    TInt ret = 0;
    TRect rect(0,0,0,0);
    if (iImageSize.iWidth == 0)
        return ret;
    else
        {
        TAknLayoutRect layRect;
        layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_6);
        ret++;
        if (iImageSize.iWidth > layRect.Rect().Width())
            {
            layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_2);
            ret++;
            if (iImageSize.iWidth > layRect.Rect().Width())
                {
                layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_8);
                ret++;
                if (iImageSize.iWidth > layRect.Rect().Width())
                    {
                    ret++;
                    }
                }
            }
        }
    return ret;
    }

TInt CAknNoteControl::TIndex::ImageHeightIndex() const
    {
    TInt ret = 0;
    TRect rect(0,0,0,0);
    if (iImageSize.iHeight == 0)
        return ret;
    else
        {
        TAknLayoutRect layRect;
        layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_6);
        ret++;
        if (iImageSize.iHeight > layRect.Rect().Height())
            {
            layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_2);
            ret++;
            if (iImageSize.iHeight > layRect.Rect().Height())
                {
                layRect.LayoutRect(rect, AKN_LAYOUT_WINDOW_Note_with_an_image_pop_up_window_elements_Line_8);
                ret++;
                if (iImageSize.iHeight > layRect.Rect().Height())
                    {
                    ret++;
                    }
                }
            }
        }
    return ret;
    }

TInt CAknNoteControl::TIndex::HasNtiIndex() const
    {
    if (iHasNti)
        return 1;
    return 0;
    }

TInt CAknNoteControl::TIndex::Lines() const
    {
    SelfTest();
    return iNumberOfLines > 0 ? iNumberOfLines - 1 : 0;
    }

/**
 * Return index into table "Waiting/progress Note Popup Window Texts Line 1"
 * Index depends on the number of text lines and whether or not there is a
 * number type indication (NTI). See table in *.lay and
 * LAF specs for working out indexes.
 */
TInt CAknNoteControl::TIndex::WNPWindowTextsLine1(TInt aLineNum) const
    {
    SelfTest();

    if(iHasNti && aLineNum == 1)
        return KPNMaxNumLines;

    return aLineNum;
    }


/**
 * Return Left index into table "Note With Image Popup Window Texts Line 1"
 * Index depends on number of text lines, whether or not there is a
 * number type indication (NTI). See table in *.lay and
 * LAF specs for working out indexes.
 */
TInt CAknNoteControl::TIndex::NWIPWindowTextsLine1L(TInt aLineNum) const
    {
    SelfTest();
    static const TInt  KNWIPWindowTextsLine1IndexL[2][3] = 
    {   
        {0, 0, 0}, //NO NTI
        {0, 0, 2}  //NTI
    }; 
    
    return KNWIPWindowTextsLine1IndexL[HasNtiIndex()][aLineNum];
    }

/**
 * Return Right index into table "Note With Image Popup Window Texts Line 1"
 * Index depends on number of text lines and image size. 
 * See table in *.lay and LAF specs for working out indexes.
 *
 * Table has 3 dimensions:-
 * - Dimension 1 is the line number
 * - Dimension 2 is the image width  
 * - Dimension 3 is the image height 
 */
TInt CAknNoteControl::TIndex::NWIPWindowTextsLine1R(TInt aLineNum) const
    {
    SelfTest();

    static const TInt  KNWIPWindowTextsLine1IndexR[3][5][5] = 
    {   
        {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //FIRST LINE
        {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //SECOND LINE
        {{0, 0, 0, 0, 0}, {0, 0, 0, 3, 3}, {0, 0, 0, 5, 5}, {0, 0, 0, 7, 7}, {0, 0, 0, 9, 9} }  //THIRD LINE
    }; 
    
    return KNWIPWindowTextsLine1IndexR[aLineNum][ImageWidthIndex()][ImageHeightIndex()];

    }

/**
 * Return Bottom index into table "Note With Image Popup Window Texts Line 1"
 * Index is the same as the number of text lines minus one. See table in *.lay and
 * LAF specs for working out indexes.
 */
TInt CAknNoteControl::TIndex::NWIPWindowTextsLine1B(TInt aLineNum) const
    {
    return aLineNum;
    }

/**
 * Return Width index into table "Note With Image Popup Window Texts Line 1"
 * Index depends on number of text lines, whether or not there is a
 * number type indication (NTI) and image size. See table in *.lay and
 * LAF specs for working out indexes.
 *
 * Table has 4 dimensions:-
 * - Dimension 1 indicates the presence of an NTI (index 0 = NO NTI, index 1 = NTI)
 * - Dimension 2 is the line number
 * - Dimension 3 is the image width
 * - Dimension 4 is the image height
 */
TInt CAknNoteControl::TIndex::NWIPWindowTextsLine1W(TInt aLineNum) const
    {
    SelfTest();

    static const TInt  KNWIPWindowTextsLine1IndexW[2][3][5][5] = 
    {   
        {
            {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //FIRST LINE  
            {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //SECOND LINE
            {{0, 0, 0, 0, 0}, {0, 0, 0, 3, 3}, {0, 0, 0, 5, 5}, {0, 0, 0, 7, 7}, {0, 0, 0, 9, 9} }  //THIRD LINE
        },//NO NTI 
        {
            {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //FIRST LINE  
            {{0, 0, 0, 0, 0}, {0, 3, 3, 3, 3}, {0, 5, 5, 5, 5}, {0, 7, 7, 7, 7}, {0, 9, 9, 9, 9} }, //SECOND LINE
            {{2, 2, 2, 2, 2}, {2, 2, 2, 4, 4}, {2, 2, 2, 6, 6}, {2, 2, 2, 8, 8}, {2, 2, 2, 10, 10} }//THIRD LINE
        }//NTI
    }; 
    
    return KNWIPWindowTextsLine1IndexW[HasNtiIndex()][aLineNum][ImageWidthIndex()][ImageHeightIndex()];

    }

/**
 * Return indexes for table AKN_LAYOUT_WINDOW_popup_note_window 
 * If there are 0-2 lines the
 * index is 0. If there are 3 lines the index is 1, if there 
 * are 4 or more lines the index is 2.
 */
TInt CAknNoteControl::TIndex::PopupNoteWindow() const
    {
    if (Lines() >= 4)
        return 2;
    
    else if (Lines() == 3)
        return 1;

    else
        return 0;
    }

/**
 * Return indexes for table AKN_LAYOUT_WINDOW_popup_note_wait_window 
 * If there are 0-2 lines the
 * index is 0. If there are 3 lines the index is 1, if there are 4 lines the
 * index is 2.
 */
TInt CAknNoteControl::TIndex::PopupNoteWaitWindow() const
    {
    if (Lines() >= 3)
        return 2;
    
    else if (Lines() == 2)
        return 1;

    else
        return 0;
    }

EXPORT_C TTypeUid::Ptr CAknNoteControl::MopSupplyObject(TTypeUid aId)
    {   
    
    if (Attributes())
        {
        return MAknsControlContext::SupplyMopObject(aId, iAttributes->iBgContext );
        }
    
    return CCoeControl::MopSupplyObject(aId);
    }

EXPORT_C void CAknNoteControl::SetBgRect(const TRect& aRect, const TPoint& aPos, TBool /*aOwnerNotDialog*/)
    {
    if (Attributes())
        {
        TRect windowRect = aRect;

        TAknLayoutRect topLeft;
        topLeft.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_2());

        TAknLayoutRect bottomRight;
        bottomRight.LayoutRect(windowRect, Popup_windows_skin_placing__frame_general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

        if (Attributes()->iBgContext)
        {
            Attributes()->iBgContext->SetFrameRects( outerRect, innerRect );
            Attributes()->iBgContext->SetParentPos(aPos);
        }

        Attributes()->iBgRect = outerRect;
        }
    }
        
TInt CAknNoteControl::NoteLayout() const
    {
    return iNoteLayout;
    }

// End of File
