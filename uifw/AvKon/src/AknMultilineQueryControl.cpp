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
*/



// INCLUDE FILES
#include <aknmultilinequerycontrol.h>   //This class
#include <barsread.h>                   //For TResourceReader
#include <eikenv.h>                     //For CEikEnv
#include <AknLayoutDef.h>               //For layout definitions
#include <AknLayout.lag>                //For layout macros
#include <avkon.mbg>

#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>

#include "akntextcontrol.h"
#include "aknqueryeditorindicator.h"
#include "AknQueryExtension.h"
#include <skinlayout.cdl.h>
#include "aknappui.h"
#include "AknQueryExtension.h"

#include <layoutmetadata.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>

#if defined( RD_SCALABLE_UI_V2)
//class CAknButton is available from week 20 version 5.0 onwards
#include <aknbutton.h>
// For MAknMfneCommandObserver
#include <aknmfnecommandobserver.h>
#endif //if defined( RD_SCALABLE_UI_V2)

#include <aknlocationed.h>
#include <aknconsts.h>

#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks


EXPORT_C CAknMultilineQueryControl::CAknMultilineQueryControl() 
    : CAknQueryControl(), iLinePos(EFirstLine)
    {
    AKNTASHOOK_ADD( this, "CAknMultilineQueryControl" );
    }

//
//Destructor
//
EXPORT_C CAknMultilineQueryControl::~CAknMultilineQueryControl()

    {
    AKNTASHOOK_REMOVE();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl( this );
        }
    }

/**
 *Initializes the member data from resource
 */
void CAknMultilineQueryControl::ConstructQueryL(TResourceReader& aRes)
    {
    SetLinePosition();

    switch(iQueryType)
        {
        case EMultiDataFirstEdwin:
        case EMultiDataSecondEdwin:
            {
            iEdwin = new(ELeave)CEikEdwin;
            iEdwin->SetContainerWindowL(*this);
            iEdwin->ConstructFromResourceL(aRes);
            iEdwin->SetObserver(this);
            iEdwin->AddFlagToUserFlags(EEikEdwinNoWrap);
            }
            break;
        case EMultiDataFirstEdwinAllowEmpty:
            {
            iEdwin = new(ELeave)CEikEdwin;
            iEdwin->SetContainerWindowL(*this);
            iEdwin->ConstructFromResourceL(aRes);
            iEdwin->SetObserver(this);
            iEdwin->AddFlagToUserFlags(EEikEdwinNoWrap);
                
            CAknQueryExtension* extension = QueryExtension();
            if( extension )
                {
                extension->iAllowEmptyInput = ETrue;
                }
            iQueryType = EMultiDataFirstEdwin;
            }
            break;
        case EMultiDataSecondEdwinAllowEmpty:
            {
            iEdwin = new(ELeave)CEikEdwin;
            iEdwin->SetContainerWindowL(*this);
            iEdwin->ConstructFromResourceL(aRes);
            iEdwin->SetObserver(this);
            iEdwin->AddFlagToUserFlags(EEikEdwinNoWrap);
                
            CAknQueryExtension* extension = QueryExtension();
            if( extension )
                {
                extension->iAllowEmptyInput = ETrue;
                }
            iQueryType = EMultiDataSecondEdwin;
            }
            break;
        case EMultiDataFirstSecEd:
        case EMultiDataSecondSecEd:
            {
            iSecretEd = new(ELeave)CEikSecretEditor;
            iSecretEd->SetContainerWindowL(*this);
            iSecretEd->ConstructFromResourceL(aRes);
            iSecretEd->SetObserver(this);
            iSecretEd->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
            }
            break;
        case EMultiDataFirstTimeEd:
        case EMultiDataSecondTimeEd:
            {
            iTimeEdwin = new(ELeave)CEikTimeEditor;
            iTimeEdwin->SetContainerWindowL(*this);
            iTimeEdwin->ConstructFromResourceL(aRes);
            iTimeEdwin->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
#if defined( RD_SCALABLE_UI_V2)

            if ( AknLayoutUtils::PenEnabled() )
                {
                iTimeEdwin->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
                }
                            
#endif //if defined( RD_SCALABLE_UI_V2)
            }
            break;
        case EMultiDataFirstDateEd:
        case EMultiDataSecondDateEd:
            {
            iDateEdwin = new(ELeave)CEikDateEditor;
            iDateEdwin->SetContainerWindowL(*this);
            iDateEdwin->ConstructFromResourceL(aRes);
            iDateEdwin->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
#if defined( RD_SCALABLE_UI_V2)

            if ( AknLayoutUtils::PenEnabled() )
                {
                iDateEdwin->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
                //SizeChanged();
                }
    
#endif //if defined( RD_SCALABLE_UI_V2)
            }
            break;
        case EMultiDataFirstDurEd:
        case EMultiDataSecondDurEd:
            {
            iDurationEdwin = new(ELeave)CEikDurationEditor;
            iDurationEdwin->SetContainerWindowL(*this);
            iDurationEdwin->ConstructFromResourceL(aRes);
            iDurationEdwin->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
            if ( AknLayoutUtils::PenEnabled() )
                {
                iDurationEdwin->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
                }
            }
            break;
        case EMultiDataFirstPhoneEd:
        case EMultiDataSecondPhoneEd:
            {
            iEdwin = new(ELeave)CEikEdwin;
            iEdwin->AddFlagToUserFlags(EEikEdwinAlternativeWrapping | EEikEdwinNoWrap);
            iEdwin->SetContainerWindowL(*this);
            iEdwin->SetEdwinObserver(this);
            iEdwin->ConstructFromResourceL(aRes);
            iEdwin->SetObserver(this);
            iEdwin->SetAknEditorInputMode(EAknEditorNumericInputMode);
            iEdwin->SetAknEditorAllowedInputModes(EAknEditorNumericInputMode);
            }
            break;
        case EMultiDataFirstNumEd:
        case EMultiDataSecondNumEd:
            {
            iNumberEdwin = new(ELeave)CAknIntegerEdwin;
            iNumberEdwin->SetContainerWindowL(*this);
            iNumberEdwin->ConstructFromResourceL(aRes);
            iNumberEdwin->SetObserver(this);
            iNumberEdwin->AddFlagToUserFlags(EEikEdwinNoWrap);
            }
            break;
        case EMultiDataFirstPinEd:
        case EMultiDataSecondPinEd:
            {
            iPinEdwin = new(ELeave)CAknNumericSecretEditor;
            iPinEdwin->SetContainerWindowL(*this);
            iPinEdwin->ConstructFromResourceL(aRes);
            iPinEdwin->SetObserver(this);
            iPinEdwin->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
            }
            break;
        case EMultiDataFirstLocationEd:
        case EMultiDataSecondLocationEd:
            {
            LocationEd() = new(ELeave)CAknLocationEditor;
            LocationEd()->SetContainerWindowL(*this);
            LocationEd()->ConstructFromResourceL(aRes);
            LocationEd()->SetObserver(this);
            LocationEd()->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
            if ( AknLayoutUtils::PenEnabled() )
                {
                LocationEd()->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
                }
            }
        default:
            break;
        }

    // Construct editor context
    CAknQueryExtension* extension = QueryExtension();
    if( extension )
        {
        extension->CreateEditorContextL();
        }
        
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    CFeedbackSpec* spec = CFeedbackSpec::New();
    if ( feedback && spec )
        {
        spec->AddFeedback( ETouchEventStylusDown,
                           ETouchFeedbackSensitiveItem );
        feedback->SetFeedbackArea( this, 0, Rect(), spec );
        delete spec;
        }
    }

/** 
 * Layout rectangle (shift up and left by margins)
 */
TRect CAknMultilineQueryControl::LayoutRect()
    {
    TPoint topLeft(0,0);
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    TAknLayoutRect layout;
    layout.LayoutRect(DialogRect(), AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(DialogRect(), LAFIndex.CDCPQWindowGraphicsLine5()));

    TRect rect(layout.Rect());
    topLeft.iX -= rect.iTl.iX;
    topLeft.iY -= rect.iTl.iY;

    TPoint bottomRight (topLeft);
    TSize  size (MinimumSize());
    bottomRight.iY += size.iHeight; 
    bottomRight.iX += size.iWidth;

    return TRect(topLeft,bottomRight);
    }


/**
 * Depending on layout type determine control position in the dialog
 */
void CAknMultilineQueryControl::SetLinePosition()
    {
    if ( iQueryType == EMultiDataSecondEdwin || iQueryType == EMultiDataSecondSecEd
        || iQueryType == EMultiDataSecondTimeEd || iQueryType == EMultiDataSecondDateEd
        || iQueryType == EMultiDataSecondDurEd  || iQueryType == EMultiDataSecondPhoneEd
        || iQueryType == EMultiDataSecondNumEd  || iQueryType == EMultiDataSecondPinEd 
        || iQueryType == EMultiDataSecondLocationEd
        )
        {   
        iLinePos = ESecondLine;
        }
    }

/**
 * Set the line width for the prompt lines
 *
 * This is a virtual method called by CAknQueryControl::DoSetPromptL()
 *
 * Depending on LAF information and on weather we are the first or the second 
 * query line, we can work out the line widths by indexing the LAF tables.
 *
 */
void CAknMultilineQueryControl::SetLineWidthsL()
    {
    if (!iLineWidths)
        return;
    
    iLineWidths->Reset();

    TAknLayoutRect parentLayoutRect;
    if (Layout_Meta_Data::IsLandscapeOrientation())
        parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_window(0));
    else
        parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_code_window(0));
    
    //parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_code_window(0));
    TAknLayoutText textRect;

    for (TInt i = 0; i < 2; i++)
        {
        if (iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            {
            textRect.LayoutText(parentLayoutRect.Rect(), AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_1(0));
            iLineWidths->AppendL(textRect.TextRect().Width());
            }
        else if (iLinePos == ESecondLine)
            {
            textRect.LayoutText(parentLayoutRect.Rect(), AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_3(0));
            iLineWidths->AppendL(textRect.TextRect().Width());
            }
        }
    }

/**
 * Set the number of prompt lines.
 *
 * The query dialog calls this method in order to communicate the number of prompt lines
 * in the other query line. Indexing into LAF tables depends on this.
 *
 */
EXPORT_C void CAknMultilineQueryControl::SetNbrOfPromptLines( 
                                            TInt aNbrOfPromptLinesFirstLine, 
                                            TInt aNbrOfPromptLinesSecondLine)
    {
    iFirstQueryPromptLines  = aNbrOfPromptLinesFirstLine;
    iSecondQueryPromptLines = aNbrOfPromptLinesSecondLine;
    }       


EXPORT_C CCoeControl* CAknMultilineQueryControl::ControlByLayoutOrNull(TInt aLayout)
    {
    CCoeControl* ctrl=NULL;
    switch ( aLayout )
        {
        case EMultiDataFirstEdwin:
        case EMultiDataSecondEdwin:
        case EMultiDataFirstPhoneEd:
        case EMultiDataSecondPhoneEd:
            ctrl=iEdwin;
            break;
        case EMultiDataFirstSecEd:
        case EMultiDataSecondSecEd:
            ctrl=iSecretEd;
            break;
        case EMultiDataFirstDateEd:
        case EMultiDataSecondDateEd:
            ctrl=iDateEdwin;
            break;
        case EMultiDataFirstTimeEd:
        case EMultiDataSecondTimeEd:
            ctrl=iTimeEdwin;
            break;
        case EMultiDataFirstDurEd:
        case EMultiDataSecondDurEd:
            ctrl=iDurationEdwin;
            break;
        case EMultiDataFirstNumEd:
        case EMultiDataSecondNumEd:
            ctrl=iNumberEdwin;
            break;
        case EMultiDataFirstPinEd:
        case EMultiDataSecondPinEd:
            ctrl=iPinEdwin;
            break;
        case EMultiDataFirstLocationEd:
        case EMultiDataSecondLocationEd:
            ctrl=LocationEd();
            break;
        default:
            break;
        }
    return ctrl;
    }

EXPORT_C TBool CAknMultilineQueryControl::IsFirst() const
    {
    return iLinePos == EFirstLine;
    }

EXPORT_C TBool CAknMultilineQueryControl::IsSecond() const
    {
    return !IsFirst();
    }

/**
 * Return control minimum size
 *
 * Size is calculated by using LAF tables. Index in this table depends on the 
 * total number of prompt lines in both queries
 */
EXPORT_C TSize CAknMultilineQueryControl::MinimumSize()
    {
    TAknLayoutRect layout;  
    TAknWindowLineLayout window;
    WindowLayout( window );    
    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    layout.LayoutRect( mainPane, window );
    TRect rect2(layout.Rect()); 
    TSize size = rect2.Size();

    if (IsFirst())
        {
        size.iHeight = FirstLineHeight(); 
        }
    else if (Layout_Meta_Data::IsLandscapeOrientation() && IsSecond())
        {
        size.iHeight = SecondLineHeight();
        }
    else if (IsSecond())
        {
        TAknWindowLineLayout layoutLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(rect2/*DialogRect()*/,0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(rect2/*DialogRect()*/, layoutLine);
        TRect rect(layoutRect.Rect());
        size.iHeight = rect.Height() - FirstLineHeight();
        }
      
    else
        __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
    
    return size;
  }

/**
 * Return height of first line control, use separator to determine this.
 */
TInt16 CAknMultilineQueryControl::FirstLineHeight() const
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
    TAknWindowLineLayout separator;
    if(!AknLayoutUtils::PenEnabled())
    {
        separator = 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3());
    }   
    else
    {
        separator = AknLayoutScalable_Avkon::popup_query_data_code_window_g1(5);    
    }

    TAknLayoutRect layout;
    layout.LayoutRect(TRect(), separator);
    TRect rect(layout.Rect());
    return (TInt16)(rect.iTl.iY + rect.Height());
    }

TInt16 CAknMultilineQueryControl::SecondLineHeight() const
    {
    TIndex LAFIndex(iLinePos,iSecondQueryPromptLines,iFirstQueryPromptLines);
    
    TAknWindowLineLayout separator;
    if(!AknLayoutUtils::PenEnabled())
    {
        separator = 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3());
    }
    else
    {
        separator = AknLayoutScalable_Avkon::popup_query_data_code_window_g1(5);    
    }
    TAknLayoutRect layout;
    layout.LayoutRect(TRect(), separator);
    TRect rect(layout.Rect());
    return (TInt16)(rect.iTl.iY + rect.Height());
    }


/**
 * Draw method.
 *
 * Draw line between query lines only if we are the first line.
 */
void CAknMultilineQueryControl::Draw(const TRect& aRect) const
    {
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        CAknQueryControl::Draw(aRect);
        return;
        }
        
    CWindowGc& gc=SystemGc(); 
    TRect rect(Rect());    
    
    if (IsSecond())
        {                
        TAknWindowLineLayout dimension;
        WindowLayout( dimension );

        TAknLayoutRect layout;
        layout.LayoutRect(iAvkonAppUi->ClientRect(), dimension);
        TRect rect2(layout.Rect());
        TAknWindowLineLayout layoutLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(rect2,0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(rect2, layoutLine);
        TRect rect3(layoutRect.Rect());
        rect.iBr.iY += rect3.Height() - rect.Height();
        }           

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        RRegion clipReg;
        clipReg.AddRect( rect );
    
        if ( iHasEditor )
            {
            clipReg.SubRect( iEditorFrame.Rect() );
            }
    
        if ( iEditIndicator )
            {
            clipReg.SubRect( 
                TRect( iEditIndicator->Position(),
                iEditIndicator->Size() ) );
            }

        gc.SetClippingRegion( clipReg );
        clipReg.Close();
        
        AknsDrawUtils::Background( skin, cc, this, gc, rect, KAknsDrawParamNoClearUnderImage );
    
        clipReg.AddRect( rect );

        CCoeControl* ctrl = const_cast<CAknMultilineQueryControl*>(this)->ControlByLayoutOrNull( iQueryType );
        if ( ctrl )
            {
            clipReg.SubRect( ctrl->Rect() );
            }

        gc.CancelClippingRegion();        
        gc.SetClippingRegion( clipReg );
        clipReg.Close();
        }
    else
        {
        AknsDrawUtils::Background( skin, cc, this, gc, rect );
        }

    DrawEditorFrame(gc,rect);
 
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.CancelClippingRegion();
        }

    //if (iLinePos == EFirstLine || !Layout_Meta_Data::IsLandscapeOrientation())
    //   iLayoutLineBetweenEntryFields.DrawRect(SystemGc());
    }

void CAknMultilineQueryControl::WindowLayout( TAknWindowLineLayout& aLayout ) const
    {
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {   
        TInt variety = 0;   
        TInt promptLines = ( iLinePos == EFirstLine ? iFirstQueryPromptLines-1 : iSecondQueryPromptLines-1 );       
        
        if (promptLines < 0)
            {
            promptLines = 0;
            }
            
        AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();
       
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {13, 12, 11, 10, 9, 8, 7}; // variety numbers for right CBA are 7-13 
            
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
        else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {20, 19, 18, 17, 16, 15, 14}; // variety numbers for left CBA are 14-20 
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
        else // bottom
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {0, 1, 2, 3, 4, 5, 6}; // variety numbers for bottom CBA are 0-6
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
            
        if(!AknLayoutUtils::PenEnabled())
            {
                aLayout = AknLayoutScalable_Avkon::popup_query_data_window(variety);
            }
        else
            {
            TBool button=EFalse;
            
            if(button || promptLines)
                {
                aLayout = AknLayoutScalable_Avkon::popup_query_code_window(4);      
                }
            else
                {
                aLayout = AknLayoutScalable_Avkon::popup_query_code_window(3);      
                }
            }
        }
    else
        {
        if(!AknLayoutUtils::PenEnabled())
            {
            TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
            aLayout = AKN_LAYOUT_WINDOW_popup_query_data_code_window(LAFIndex.MainPanePQDCWindow());        
            }                  
        else
            {
            aLayout = AknLayoutScalable_Avkon::popup_query_data_code_window(2); 
            }
        }
    }

void CAknMultilineQueryControl::SizeChanged()
    {
    DialogSizeChanged();

    LayoutPrompt(ECombinedCodeDataQueryLayoutM);
    LayoutSeparator(ECombinedCodeDataQueryLayoutM);
    LayoutEditor(ECombinedCodeDataQueryLayoutM);

    CAknQueryExtension* extension = QueryExtension();
    if( iHasEditor && extension && extension->EditorContext() )
        {
        // Layout editor context
        TAknLayoutRect topLeft;
        TAknLayoutRect bottomRight;
        
        topLeft.LayoutRect(iEditorFrame.Rect(), SkinLayout::Input_field_skin_placing__general__Line_2());                
        bottomRight.LayoutRect(TRect(iEditorFrame.Rect().iBr, iEditorFrame.Rect().iBr), SkinLayout::Input_field_skin_placing__general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

        extension->EditorContext()->SetFrameRects( outerRect, innerRect );
        // Chain with the background (since the frame doesn't occupy the entire
        // layout and it may even be transparent)
        extension->EditorContext()->SetParentContext( AknsDrawUtils::ControlContextOfParent( this ) );
         
        }
    
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->ChangeFeedbackArea( this, 0, Rect() );
        feedback->EnableFeedbackForControl( this, !(IsFocused() || Layout_Meta_Data::IsLandscapeOrientation()) );
        }
    }
    
EXPORT_C void CAknMultilineQueryControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknQueryControl::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CAknMultilineQueryControl::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 * Layout the query prompt
 */
void CAknMultilineQueryControl::LayoutPrompt(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    iPrompt->SetRect(DialogRect());
    TRect rect = LayoutRect();
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

    for (TInt i = 0; i < NbrOfPromptLines(); i++)
        {
        if (iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            AknLayoutUtils::LayoutLabel(iPrompt->Line(i), rect, 
                AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_1
                    (LAFIndex.CDCQPWindowTextsLine1(i)));
        
        else if (iLinePos == ESecondLine)
        {
          if(!AknLayoutUtils::PenEnabled())
          {
            AknLayoutUtils::LayoutLabel(iPrompt->Line(i),rect,
                AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_3
                    (LAFIndex.CDCQPWindowTextsLine3(i)));
          }
          else
          {
            TAknTextComponentLayout promtLineVariant;
            if(i == 0)
            {
                promtLineVariant = AknLayoutScalable_Avkon::popup_query_data_code_window_t3(0);
            }           
            else 
            {   
                promtLineVariant = AknLayoutScalable_Avkon::popup_query_data_code_window_t4(0);
            }
            AknLayoutUtils::LayoutLabel(iPrompt->Line(i),rect,promtLineVariant);    
          }
        }
        
        else
            __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
        
        if (!error)      
            {
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iPrompt->Line(i), EColorLabelText, color ) );        
            }

        }
    }
/**
 * Layout the separation line between the two queries
 */
void CAknMultilineQueryControl::LayoutSeparator(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    iLayoutLineBetweenEntryFields.LayoutRect(LayoutRect(), 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3()));
    }

/**
 * Following four function classes allow passing the AknLayoutUtils fcn as as
 * parameter to DoLayoutEditor()
 */

/**
 * Layout text editors 
 */
class FLayoutEdwin
    {
public:
    FLayoutEdwin() { }
    void operator() (CEikEdwin* aEd, const TRect& aRect, const TAknWindowComponentLayout& aLay, 
        const CFont* aFont, TBool aMinimizedView) const
        {
        TAknTextLineLayout lay = TAknWindowComponentLayout::ComposeText(aLay, AknLayoutScalable_Avkon::query_popup_data_pane_t1(0)).LayoutLine();
        AknLayoutUtils::LayoutEdwin(aEd,aRect,lay,EAknsCIQsnTextColorsCG27,aFont,aMinimizedView);
        AknsUtils::RegisterControlPosition(aEd);
        }
    };

/**
 * Layout editors containing secret codes
 */
class FLayoutSecretEditor
    {
public:
    FLayoutSecretEditor() { }
    void operator() (CEikSecretEditor* aEd, const TRect& aRect, const TAknWindowComponentLayout& aLay,
        const CFont* /*aFont*/, TBool /*aMinimizedView*/) const
        { 
        TAknTextLineLayout lay = TAknWindowComponentLayout::ComposeText(aLay, AknLayoutScalable_Avkon::query_popup_pane_t1()).LayoutLine();
        AknLayoutUtils::LayoutSecretEditor(aEd,aRect,lay);
        AknsUtils::RegisterControlPosition(aEd);
        }
    };

/**
 * Layout numeric editors 
 */
class FLayoutNumericEdwin
    {
public:
    FLayoutNumericEdwin() { }
    void operator() (CAknNumericEdwin* aEd, const TRect& aRect, const TAknWindowComponentLayout& aLay, 
        const CFont* aFont, TBool aMinimizedView) const
        {
        TAknTextLineLayout lay = TAknWindowComponentLayout::ComposeText(aLay, AknLayoutScalable_Avkon::query_popup_data_pane_t1(0)).LayoutLine();
        AknLayoutUtils::LayoutEdwin(aEd,aRect,lay,EAknsCIQsnTextColorsCG27,aFont,aMinimizedView);
        AknsUtils::RegisterControlPosition(aEd);
        }
    };

/**
 * Layout multifield numeric editors (MFNEs) 
 */
class FLayoutMfne
    {
public:
    FLayoutMfne(){ }
    void operator() (CEikMfne* aEd, const TRect& aRect, const TAknWindowComponentLayout& aLay,
        const CFont* /*aFont*/, TBool /*aMinimizedView*/) const
        {
        TAknTextLineLayout lay = TAknWindowComponentLayout::ComposeText(aLay, AknLayoutScalable_Avkon::query_popup_pane_t1()).LayoutLine();
        AknLayoutUtils::LayoutMfne(aEd,aRect,lay);
        AknsUtils::RegisterControlPosition(aEd);
        }
    };

/**
 * Layout a single editor
 */
template<class Edt, class Fct> 
void DoLayoutEditor(const TRect& aRect, Edt* aEd, Fct aFcn, const CAknMultilineQueryControl::TIndex& aLAFIndex,TBool aButton,TInt aNbrPromptLines,
    const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse)
    {
    if (aEd)
        {
        if (aLAFIndex.LinePos() == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            {
                if(!AknLayoutUtils::PenEnabled() || !aButton)
                {
            aFcn(aEd, aRect,
                AknLayoutScalable_Avkon::query_popup_data_pane_cp2(aLAFIndex.CDCQPWindowTextsLine2()),aCustomFont,aMinimizeEdwinView);
                }
                else
                {
                TAknLayoutRect editRect;
                editRect.LayoutRect(aRect,AknLayoutScalable_Avkon::cont_query_data_pane());
                aFcn(aEd, editRect.Rect(),
                    AknLayoutScalable_Avkon::query_popup_pane_cp3(),aCustomFont,aMinimizeEdwinView);    
                }
            }
    
        else if (aLAFIndex.LinePos() == ESecondLine)
            {
                if(!AknLayoutUtils::PenEnabled())
                {
            aFcn(aEd, aRect,
                AknLayoutScalable_Avkon::query_popup_pane_cp2(aLAFIndex.CDCQPWindowTextsLine4()),aCustomFont,aMinimizeEdwinView);
                }
                else
                {
                 if(!aButton)
                 {
                    if(aNbrPromptLines == 1)
                    {
                        aFcn(aEd, aRect,AknLayoutScalable_Avkon::query_popup_pane_cp2(5),aCustomFont,aMinimizeEdwinView);          
                    }
                    else //aNbrPromptLines = 2
                    {
                        aFcn(aEd, aRect,AknLayoutScalable_Avkon::query_popup_pane_cp2(0),aCustomFont,aMinimizeEdwinView);                               
                    }
                 }
                 else
                 {
                    TAknLayoutRect editRect;
                    editRect.LayoutRect(aRect,AknLayoutScalable_Avkon::cont_query_data_pane_cp1());
                    aFcn(aEd, editRect.Rect(),
                    AknLayoutScalable_Avkon::query_popup_pane_cp3(),aCustomFont,aMinimizeEdwinView);            
                 }    
                }                                               
            }
        
        else
        #ifdef _DEBUG
            __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
        #endif
        
        aEd->SetBorder(TGulBorder::ENone); 
        }
    }

/**
 * Layout every editor
 *
 */
void CAknMultilineQueryControl::LayoutEditor(const TLayoutMethod& aLayoutM)
    {
    TRect rect = LayoutRect();
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
    TIndex LAFIndex2(iLinePos,iSecondQueryPromptLines,iSecondQueryPromptLines);

    const TIndex *index = &LAFIndex;
    if (Layout_Meta_Data::IsLandscapeOrientation() && iLinePos == ESecondLine)
        {
        index = &LAFIndex2;
        }

    iHasEditor = ETrue;
    LayoutEditorFrame(aLayoutM);
    LayoutEditorIndicator(aLayoutM);

    TBool button=EFalse;
    
    TInt nbrPromptLines = CAknQueryControl::NbrOfPromptLines();
    DoLayoutEditor(rect,iEdwin,FLayoutEdwin(),*index,button,nbrPromptLines,0,ETrue);
    DoLayoutEditor(rect,iSecretEd,FLayoutSecretEditor(),*index,button,nbrPromptLines);
    
    DoLayoutEditor(rect,iTimeEdwin,FLayoutMfne(),*index,button,nbrPromptLines);
    DoLayoutEditor(rect,iDateEdwin,FLayoutMfne(),*index,button,nbrPromptLines);
    
    DoLayoutEditor(rect,iDurationEdwin,FLayoutMfne(),*index,button,nbrPromptLines);
    DoLayoutEditor(rect,iNumberEdwin,FLayoutNumericEdwin(),*index,button,nbrPromptLines);
    
    DoLayoutEditor(rect,iPinEdwin,FLayoutSecretEditor(),*index,button,nbrPromptLines);
    DoLayoutEditor(rect,LocationEd(),FLayoutMfne(),*index,button,nbrPromptLines);
    }

/**
 * Layout the editor frame
 */
void CAknMultilineQueryControl::LayoutEditorFrame(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
    TIndex LAFIndex2(EFirstLine,iSecondQueryPromptLines,iSecondQueryPromptLines);
    TRect rect = LayoutRect();

    const TIndex *index = &LAFIndex;
    if (Layout_Meta_Data::IsLandscapeOrientation() && iLinePos == ESecondLine)
        {
        index = &LAFIndex2;
        }
    iEditorVerShadow.LayoutRect(rect, 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_1(!IsFocused(),index->CDCQPWindowLine1()));
    
    iEditorHorShadow.LayoutRect(rect, 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_2(!IsFocused(),index->CDCQPWindowLine2()));

    TBool button=EFalse;
    
    if(!AknLayoutUtils::PenEnabled())
        {
    iEditorFrame.LayoutRect    (rect, 
        AknLayout::Combined_data_and_code_query_pop_up_window_elements_Line_4(index->CDCQPWindowRectangles()));
        }
    else
        {
            if(!button)                       
            {
               if(iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
               {
                    if(NbrOfPromptLines() == 1)
                    {
                iEditorFrame.LayoutRect(rect,AknLayoutScalable_Avkon::query_popup_pane_cp2(4));      
                    }                     
                    else //2 lines
                    {
                        iEditorFrame.LayoutRect(rect,AknLayoutScalable_Avkon::query_popup_data_pane_cp2(0));            
                    }
               }
               else
               {
                    if(NbrOfPromptLines() == 1)
                    {
                iEditorFrame.LayoutRect(rect,AknLayoutScalable_Avkon::query_popup_pane_cp2(5));      
                    }
                    else
                    {
                       iEditorFrame.LayoutRect(rect,AknLayoutScalable_Avkon::query_popup_pane_cp2(0));                                               
                    }
               }
            }    
            else
            {
                TAknLayoutRect rectEditorFrame;                
                TAknLayoutRect popupRect;                                
                if(iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
                {
                    popupRect.LayoutRect(rect,AknLayoutScalable_Avkon::cont_query_data_pane());         
                }
                else
                {
                    popupRect.LayoutRect(rect,AknLayoutScalable_Avkon::cont_query_data_pane_cp1());
                }
            iEditorFrame.LayoutRect(popupRect.Rect(),AknLayoutScalable_Avkon::query_popup_pane_cp3());                          
            }
        }                                               
    }

/**
 * Layout the editor indicator icons
 */
void CAknMultilineQueryControl::LayoutEditorIndicator(const TLayoutMethod& /*aLayoutM*/)
    {
    CCoeControl* editor = ControlByLayoutOrNull(iQueryType);
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    if (!iEditIndicator || !editor || iFlags.IsSet(EEditorIndicatorOff))
        return;
        
    if (editor->IsFocused())
        {
        TAknWindowLineLayout indicatorLine;
        
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            TInt promptLines = ( iLinePos == EFirstLine ?
                iFirstQueryPromptLines : iSecondQueryPromptLines );
            
            static const TInt lineTable[4] = { 2, 2, 1, 3 };
                
            indicatorLine = AknLayoutScalable_Avkon::indicator_popup_pane_cp4( lineTable[promptLines] ).LayoutLine();
            }
        else
            {
                if(iLinePos == ESecondLine && AknLayoutUtils::PenEnabled())
                {
                    if(NbrOfPromptLines() == 1)
                    {
                    indicatorLine = AknLayoutScalable_Avkon::indicator_popup_pane_cp2(5);                       
                    }
                    else
                    {
                        indicatorLine = AknLayoutScalable_Avkon::indicator_popup_pane_cp2(0);
                    }
                }
                else
                {
            indicatorLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_5(LAFIndex.CDCQPWindowLine5());
                }
            }
            
        AknLayoutUtils::LayoutControl( iEditIndicator, LayoutRect(), indicatorLine );
        }
    else
        iEditIndicator->SetRect(TRect(TPoint(0,0),TPoint(0,0)));
    }
    

EXPORT_C void CAknMultilineQueryControl::HandleResourceChange( TInt aType ) 
    {
    CCoeControl::HandleResourceChange( aType );
        
    if ( aType == KAknsMessageSkinChange )
        {
        CAknQueryExtension* extension = QueryExtension();
        if( iHasEditor && extension && extension->EditorContext() )
            {
            extension->EditorContext()->SetParentContext( AknsDrawUtils::ControlContextOfParent( this ) );
            }
        }
    else if( aType == KEikDynamicLayoutVariantSwitch ) // JLa 22.09.2006 
        {
        SizeChanged();
        }
    }    


/*****************************************************************
 * CAknMultilineQueryControl::TIndex
 *
 * Manage indexes into LAF tables
 *
 * PQDC stands for 'Popup Query Data Code'
 *
 * CDCQP stands for 'Combined Data Code Query Popup'
 ******************************************************************/

/**
 * Construction, iLinePos is the position of the current line, either first or
 * second. iFirstLine is the numeber of prompt lines for the first query, either 1
 * or 2. iSecondline is the number of prompt lines for the second query, either 1 or 2
 */ 
CAknMultilineQueryControl::TIndex::TIndex(const TLinePosition& aLinePos, 
                                                 TInt aFirstQueryPromptLines, TInt aSecondQueryPromptLines) :
    iLinePos(aLinePos), iFirstQueryPromptLines(aFirstQueryPromptLines), iSecondQueryPromptLines(aSecondQueryPromptLines)
        {
        }

/**
 * Check that we are in a consistent state for retrieving correct indexes
 *
 */
void CAknMultilineQueryControl::TIndex::SelfTest() const
    {
    __ASSERT_DEBUG(iLinePos == EFirstLine || iLinePos == ESecondLine,
        Panic(EAknPanicInvalidValue));
    __ASSERT_DEBUG(iFirstQueryPromptLines >= 0  && iFirstQueryPromptLines <= 2, 
        Panic(EAknPanicInvalidValue));
    __ASSERT_DEBUG(iSecondQueryPromptLines >= 0 && iSecondQueryPromptLines <= 2, 
        Panic(EAknPanicInvalidValue));
    }

/**
 * We tolerate a null number of prompt lines. If this is the case we set
 * the number of lines to 1 (empty query will use layout of a query with a
 * line of text).
 */
TInt CAknMultilineQueryControl::TIndex::FirstQueryPromptLines() const
    {
    SelfTest();
    return iFirstQueryPromptLines > 0 ? iFirstQueryPromptLines - 1 : 1;
    }

/**
 * We tolerate a null number of prompt lines. If this is the case we set
 * the number of lines to 1 (empty query will use layout of a query with a
 * line of text).
 */
TInt CAknMultilineQueryControl::TIndex::SecondQueryPromptLines() const
    {
    SelfTest();
    return iSecondQueryPromptLines > 0 ? iSecondQueryPromptLines - 1: 1;
    }


/**
 * Return index into Main Pane PQDC Window, which
 * depends on total number of prompt lines minus 2, e.g.
 * index 0 for 2 prompt lines total.
 *
 */
TInt CAknMultilineQueryControl::TIndex::MainPanePQDCWindow() const
    {
    SelfTest();
    static const TInt KMainPanePQDCWindow[3] = {0,1,2}; 
    return KMainPanePQDCWindow[FirstQueryPromptLines() + SecondQueryPromptLines()];
    }

/**
 * Return index into PQDC Window Rectangles, which
 * depends on line position and number or prompt lines in
 * both queries.
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowLine1() const
    {
    SelfTest();
    static const TInt KPQDCWindowRectanglesIndex[2][2][2] = 
        {    
            {{0,4},{2,6}},   //First  line
            {{1,5},{3,7}}    //Second line
        };
    return KPQDCWindowRectanglesIndex[(TInt)iLinePos][FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

TInt CAknMultilineQueryControl::TIndex::CDCQPWindowLine2() const
    {
    return CDCQPWindowLine1();
    }

/**
 * Return index into PQDC Window Line 3, which depends on number of prompt
 * lines in both queries
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowLine3() const
    {
    SelfTest();
    static const TInt KCDCQPWindowLine3Index[2][2] = 
        {    
            {0,2},
            {1,3}    
        };  
    return KCDCQPWindowLine3Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

TInt CAknMultilineQueryControl::TIndex::CDCQPWindowRectangles() const
    {
    return CDCQPWindowLine1();
    }

TInt CAknMultilineQueryControl::TIndex::CDCQPWindowLine5() const
    {
    return CDCQPWindowLine1();
    }


/**
 * Return index into 'CDCQP Window texts Line 1', which 
 * depends on total number of promt lines and current 
 * prompt line number (received as parameter)
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowTextsLine1(TInt aLineNum) const
    {
    SelfTest();
    __ASSERT_DEBUG(aLineNum >= 0 && aLineNum < 2,Panic(EAknPanicInvalidValue));

    static const TInt KPQDCWindowTextsLine1Index[2][3] = {
        {0,0,2}, //First prompt line
        {1,1,3}  //Second prompt line
        };
    return KPQDCWindowTextsLine1Index[aLineNum][FirstQueryPromptLines() + SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window texts Line 2', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowTextsLine2() const
    {
    static const TInt KPQDCWindowTextsLine2Index[2][2] = {
        {3,2},
        {1,0}
        };
    return KPQDCWindowTextsLine2Index[FirstQueryPromptLines()][SecondQueryPromptLines()];

    }

/**
 * Return index into 'CDCQP Window texts Line 3', which 
 * depends on number of promt lines and current 
 * prompt line number (received as parameter)
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowTextsLine3(TInt aLineNum) const
    {
    SelfTest();
    __ASSERT_DEBUG(aLineNum >= 0 && aLineNum < 2,Panic(EAknPanicInvalidValue));

    static const TInt KPQDCWindowTextsLine3Index[2][2][2] = {
        {{0,0}, {2,3}},  //First prompt line
        {{1,1}, {2,4}}   //Second Prompt Line
        };
    return KPQDCWindowTextsLine3Index[aLineNum][FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window texts Line 4', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknMultilineQueryControl::TIndex::CDCQPWindowTextsLine4() const
    {
    static const TInt KPQDCWindowTextsLine4Index[2][2] = {
        {3,2},
        {1,0}
        };
    return KPQDCWindowTextsLine4Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window graphics Line 5', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknMultilineQueryControl::TIndex::CDCPQWindowGraphicsLine5() const
    {
    static const TInt KCDCPQWindowGraphicsLine5Index[2][2] = {
        {0,0}, 
        {0,1}  
        };
    return KCDCPQWindowGraphicsLine5Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }




/*****************************
 * CAknExtMultilineQueryControl
 *****************************/



EXPORT_C CAknExtMultilineQueryControl::CAknExtMultilineQueryControl() 
    : CAknExtQueryControl(), iLinePos(EFirstLine)
    {
    AKNTASHOOK_ADD( this, "CAknExtMultilineQueryControl" );
    }

//
//Destructor
//
EXPORT_C CAknExtMultilineQueryControl::~CAknExtMultilineQueryControl()

    {
    AKNTASHOOK_REMOVE();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl( this );
        }
    }

/**
 *Initializes the member data from resource
 */
void CAknExtMultilineQueryControl::ConstructQueryL(TResourceReader& aRes)
    {
    SetLinePosition();

    if ( iQueryType == EMultiDataFirstIpEd || iQueryType == EMultiDataSecondIpEd )
        {           
        iIpEditor = new(ELeave)CAknIpFieldEditor;
        iIpEditor->SetContainerWindowL(*this);
        iIpEditor->ConstructFromResourceL(aRes);
        iIpEditor->SetObserver(this);
        iIpEditor->SetSkinTextColorL(EAknsCIQsnTextColorsCG27);
        if ( AknLayoutUtils::PenEnabled() )
            {
            iIpEditor->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
            }
        }  

    // Construct editor context
    CAknQueryExtension* extension = QueryExtension();
    if( extension )
        {
        extension->CreateEditorContextL();
        }
        
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    CFeedbackSpec* spec = CFeedbackSpec::New();
    if ( feedback && spec )
        {
        spec->AddFeedback( ETouchEventStylusDown,
                           ETouchFeedbackSensitiveItem );
        feedback->SetFeedbackArea( this, 0, Rect(), spec );
        delete spec;
        }
    }


/** 
 * Layout rectangle (shift up and left by margins)
 */
TRect CAknExtMultilineQueryControl::LayoutRect()
    {
    TPoint topLeft(0,0);
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    TAknLayoutRect layout;
    layout.LayoutRect(DialogRect(), AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(DialogRect(), LAFIndex.CDCPQWindowGraphicsLine5()));

    TRect rect(layout.Rect());
    topLeft.iX -= rect.iTl.iX;
    topLeft.iY -= rect.iTl.iY;

    TPoint bottomRight (topLeft);
    TSize  size (MinimumSize());
    bottomRight.iY += size.iHeight; 
    bottomRight.iX += size.iWidth;

    return TRect(topLeft,bottomRight);
    }


/**
 * Depending on layout type determine control position in the dialog
 */
void CAknExtMultilineQueryControl::SetLinePosition()
    {
    if ( iQueryType == EMultiDataSecondIpEd )
        {   
        iLinePos = ESecondLine;
        }
    }


/**
 * Set the line width for the prompt lines
 *
 * This is a virtual method called by CAknQueryControl::DoSetPromptL()
 *
 * Depending on LAF information and on weather we are the first or the second 
 * query line, we can work out the line widths by indexing the LAF tables.
 *
 */
void CAknExtMultilineQueryControl::SetLineWidthsL()
    {
    if (!iLineWidths)
        return;
    
    iLineWidths->Reset();

    TAknLayoutRect parentLayoutRect;
    
    if (Layout_Meta_Data::IsLandscapeOrientation())
        parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_window(0));
    else
        parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_code_window(0));
    
    //parentLayoutRect.LayoutRect(iAvkonAppUi->ClientRect(), AKN_LAYOUT_WINDOW_popup_query_data_code_window(0));
    TAknLayoutText textRect;

    for (TInt i = 0; i < 2; i++)
        {
        if (iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            {
            textRect.LayoutText(parentLayoutRect.Rect(), AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_1(0));
            iLineWidths->AppendL(textRect.TextRect().Width());
            }
        else if (iLinePos == ESecondLine)
            {
            textRect.LayoutText(parentLayoutRect.Rect(), AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_3(0));
            iLineWidths->AppendL(textRect.TextRect().Width());
            }
        }
    }


EXPORT_C TBool CAknExtMultilineQueryControl::IsFirst() const
    {
    return iLinePos == EFirstLine;
    }

EXPORT_C TBool CAknExtMultilineQueryControl::IsSecond() const
    {
    return !IsFirst();
    }

/**
 * Set the number of prompt lines.
 *
 * The query dialog calls this method in order to communicate the number of prompt lines
 * in the other query line. Indexing into LAF tables depends on this.
 *
 */
EXPORT_C void CAknExtMultilineQueryControl::SetNbrOfPromptLines( 
                                            TInt aNbrOfPromptLinesFirstLine, 
                                            TInt aNbrOfPromptLinesSecondLine)
    {
    iFirstQueryPromptLines  = aNbrOfPromptLinesFirstLine;
    iSecondQueryPromptLines = aNbrOfPromptLinesSecondLine;
    }


EXPORT_C CCoeControl* CAknExtMultilineQueryControl::ControlByLayoutOrNull(TInt aLayout)
    {
    CCoeControl* ctrl=NULL;
    if ( aLayout == EMultiDataFirstIpEd || aLayout == EMultiDataSecondIpEd )
        {
        ctrl = iIpEditor;
        }   
    return ctrl;
    }


/**
 * Return control minimum size
 *
 * Size is calculated by using LAF tables. Index in this table depends on the 
 * total number of prompt lines in both queries
 */
EXPORT_C TSize CAknExtMultilineQueryControl::MinimumSize()
    {
    TAknLayoutRect layout;  
    TAknWindowLineLayout window;
    WindowLayout( window );    
    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    layout.LayoutRect( mainPane, window );
    TRect rect2(layout.Rect()); 
    TSize size = rect2.Size();

    if (IsFirst())
        {
        size.iHeight = FirstLineHeight(); 
        }        
    else if (Layout_Meta_Data::IsLandscapeOrientation() && IsSecond())
        {
        size.iHeight = SecondLineHeight();
        }    
    else if (IsSecond())
        {
        TAknWindowLineLayout layoutLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(DialogRect(),0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(rect2, layoutLine);
        TRect rect(layoutRect.Rect());
        size.iHeight = rect.Height() - FirstLineHeight();
        }
      
    else
        __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
    
    return size;
  }


/**
 * Return height of first line control, use separator to determine this.
 */
TInt16 CAknExtMultilineQueryControl::FirstLineHeight() const
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    TAknWindowLineLayout separator = 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3());

    TAknLayoutRect layout;
    layout.LayoutRect(TRect(), separator);
    TRect rect(layout.Rect());
    return (TInt16)(rect.iTl.iY + rect.Height());
    }
    
TInt16 CAknExtMultilineQueryControl::SecondLineHeight() const
    {
    TIndex LAFIndex(iLinePos,iSecondQueryPromptLines,iFirstQueryPromptLines);

    TAknWindowLineLayout separator = 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3());

    TAknLayoutRect layout;
    layout.LayoutRect(TRect(), separator);
    TRect rect(layout.Rect());
    return (TInt16)(rect.iTl.iY + rect.Height());
    }


/**
 * Draw method.
 *
 * Draw line between query lines only if we are the first line.
 */

void CAknExtMultilineQueryControl::Draw(const TRect& aRect) const
    {
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        if( CAknEnv::Static()->TransparencyEnabled() )
            {
            if ( IsFocused() )
                {
                CAknExtQueryControl::Draw(aRect);
                }
            }
        else
            {
            CAknExtQueryControl::Draw(aRect);
            }
        return;
        }
        
    CWindowGc& gc=SystemGc(); 
    TRect rect(Rect());    
    
    if (IsSecond())
        {                
        TAknWindowLineLayout dimension;
        WindowLayout( dimension );

        TAknLayoutRect layout;
        layout.LayoutRect(iAvkonAppUi->ClientRect(), dimension);
        TRect rect2(layout.Rect());
        TAknWindowLineLayout layoutLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_graphics_Line_5(rect2,0);
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(rect2, layoutLine);
        TRect rect3(layoutRect.Rect());
        rect.iBr.iY += rect3.Height() - rect.Height();
        }           

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        RRegion clipReg;
        clipReg.AddRect( rect );

        if ( iHasEditor )
            {
            clipReg.SubRect( iEditorFrame.Rect() );
            }

        if ( iEditIndicator )
            {
            clipReg.SubRect(
                TRect( iEditIndicator->Position(),
                iEditIndicator->Size() ) );
            }

        gc.SetClippingRegion( clipReg );
        clipReg.Close();
        
        AknsDrawUtils::Background( skin, cc, this, gc, rect, KAknsDrawParamNoClearUnderImage );
    
        clipReg.AddRect( rect );

        CCoeControl* ctrl = const_cast<CAknExtMultilineQueryControl*>(this)->ControlByLayoutOrNull( iQueryType );
        if ( ctrl )
            {
            clipReg.SubRect( ctrl->Rect() );
            }

        gc.CancelClippingRegion();        
        gc.SetClippingRegion( clipReg );
        clipReg.Close();
        }
    else
        {
        AknsDrawUtils::Background( skin, cc, this, gc, rect );
        }

    DrawEditorFrame(gc,rect);
 
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.CancelClippingRegion();
        }
    }
  
    
EXPORT_C void CAknExtMultilineQueryControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknExtQueryControl::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CAknExtMultilineQueryControl::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

void CAknExtMultilineQueryControl::WindowLayout( TAknWindowLineLayout& aLayout ) const
    {
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        TInt variety = 0;   
        TInt promptLines = ( iLinePos == EFirstLine ? iFirstQueryPromptLines-1 : iSecondQueryPromptLines-1 );       
        
        if (promptLines < 0)
            {
            promptLines = 0;
            }
            
        AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();
       
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {13, 12, 11, 10, 9, 8, 7}; // variety numbers for right CBA are 7-13 
            
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
        else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {20, 19, 18, 17, 16, 15, 14}; // variety numbers for left CBA are 14-20 
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
        else // bottom
            {
            static const TInt KPopupQueryDataWindowIndex[7] = 
                {0, 1, 2, 3, 4, 5, 6}; // variety numbers for bottom CBA are 0-6
            variety = KPopupQueryDataWindowIndex[promptLines];
            }
            
        aLayout = AknLayoutScalable_Avkon::popup_query_data_window(variety);    
        }
    else
        {
        TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
        aLayout = AKN_LAYOUT_WINDOW_popup_query_data_code_window(LAFIndex.MainPanePQDCWindow());        
        }
    }



void CAknExtMultilineQueryControl::SizeChanged()
    {
    DialogSizeChanged();
    
    LayoutPrompt(ECombinedCodeDataQueryLayoutM);
    LayoutSeparator(ECombinedCodeDataQueryLayoutM);
    LayoutEditor(ECombinedCodeDataQueryLayoutM);

    CAknQueryExtension* extension = QueryExtension();
    if( iHasEditor && extension && extension->EditorContext() )
        {
        // Layout editor context
        TAknLayoutRect topLeft;
        TAknLayoutRect bottomRight;
        
        topLeft.LayoutRect(iEditorFrame.Rect(), SkinLayout::Input_field_skin_placing__general__Line_2());                
        bottomRight.LayoutRect(TRect(iEditorFrame.Rect().iBr, iEditorFrame.Rect().iBr), SkinLayout::Input_field_skin_placing__general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);

        extension->EditorContext()->SetFrameRects( outerRect, innerRect );
        // Chain with the background (since the frame doesn't occupy the entire
        // layout and it may even be transparent)
        extension->EditorContext()->SetParentContext( AknsDrawUtils::ControlContextOfParent( this ) );
        }
        
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->ChangeFeedbackArea( this, 0, Rect() );
        feedback->EnableFeedbackForControl( this, !(IsFocused() || Layout_Meta_Data::IsLandscapeOrientation()) );
        } 
    }

/**
 * Layout the query prompt
 */
void CAknExtMultilineQueryControl::LayoutPrompt(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    iPrompt->SetRect(DialogRect());
    TRect rect = LayoutRect();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );

    for (TInt i = 0; i < NbrOfPromptLines(); i++)
        {
        if (iLinePos == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            AknLayoutUtils::LayoutLabel(iPrompt->Line(i), rect, 
                AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_1
                    (LAFIndex.CDCQPWindowTextsLine1(i)));
        
        else if (iLinePos == ESecondLine)
            AknLayoutUtils::LayoutLabel(iPrompt->Line(i),rect,
                AKN_LAYOUT_TEXT_Combined_data_and_code_query_pop_up_window_texts_Line_3
                    (LAFIndex.CDCQPWindowTextsLine3(i)));
        
        else
            __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));

        if (!error)      
            {
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iPrompt->Line(i), EColorLabelText, color ) );        
            }
        }
    }
/**
 * Layout the separation line between the two queries
 */
void CAknExtMultilineQueryControl::LayoutSeparator(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    iLayoutLineBetweenEntryFields.LayoutRect(LayoutRect(), 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_3
            (LAFIndex.CDCQPWindowLine3()));
    }


/**
 * Layout multifield numeric editors (MFNEs) 
 */
class FLayoutMfne2
    {
public:
    FLayoutMfne2(){ }
    void operator() (CEikMfne* aEd, const TRect& aRect, const TAknWindowComponentLayout& aLay,
        const CFont* /*aFont*/, TBool /*aMinimizedView*/) const
        {
        TAknTextLineLayout lay = TAknWindowComponentLayout::ComposeText(aLay, AknLayoutScalable_Avkon::query_popup_pane_t1()).LayoutLine();
        AknLayoutUtils::LayoutMfne(aEd,aRect,lay);
        AknsUtils::RegisterControlPosition(aEd);
        }
    };

/**
 * Layout a single editor
 */
template<class Edt, class Fct> 
void DoLayoutEditor(const TRect& aRect, Edt* aEd, Fct aFcn, const CAknExtMultilineQueryControl::TIndex& aLAFIndex,
    const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse)
    {
    if (aEd)
        {
        if (aLAFIndex.LinePos() == EFirstLine || Layout_Meta_Data::IsLandscapeOrientation())
            {
            aFcn(aEd, aRect,
                AknLayoutScalable_Avkon::query_popup_data_pane_cp2(aLAFIndex.CDCQPWindowTextsLine2()),aCustomFont,aMinimizeEdwinView);
            }                
        else if (aLAFIndex.LinePos() == ESecondLine)
            {
            aFcn(aEd, aRect,
                AknLayoutScalable_Avkon::query_popup_pane_cp2(aLAFIndex.CDCQPWindowTextsLine4()),aCustomFont,aMinimizeEdwinView);
            }                    
        else
        #ifdef _DEBUG
            __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
        #endif
        
        aEd->SetBorder(TGulBorder::ENone); 
        }
    }


/**
 * Layout every editor
 *
 */
void CAknExtMultilineQueryControl::LayoutEditor(const TLayoutMethod& aLayoutM)
    {
    TRect rect = LayoutRect();
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
    TIndex LAFIndex2(iLinePos,iSecondQueryPromptLines,iSecondQueryPromptLines);

    const TIndex *index = &LAFIndex;
    if (Layout_Meta_Data::IsLandscapeOrientation() && iLinePos == ESecondLine)
        {
        index = &LAFIndex2;
        }

    iHasEditor = ETrue;
    LayoutEditorFrame(aLayoutM);
    LayoutEditorIndicator(aLayoutM);
    
    DoLayoutEditor(rect,iIpEditor,FLayoutMfne2(), *index);
    }

/**
 * Layout the editor frame
 */
void CAknExtMultilineQueryControl::LayoutEditorFrame(const TLayoutMethod& /*aLayoutM*/)
    {
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);
    TIndex LAFIndex2(EFirstLine,iSecondQueryPromptLines,iSecondQueryPromptLines);
    TRect rect = LayoutRect();
    
    const TIndex *index = &LAFIndex;
    if (Layout_Meta_Data::IsLandscapeOrientation() && iLinePos == ESecondLine)
        {
        index = &LAFIndex2;
        }

    iEditorVerShadow.LayoutRect(rect, 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_1(!IsFocused(), index->CDCQPWindowLine1()));
    
    iEditorHorShadow.LayoutRect(rect, 
        AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_2(!IsFocused(), index->CDCQPWindowLine2()));

    iEditorFrame.LayoutRect    (rect, 
        AknLayout::Combined_data_and_code_query_pop_up_window_elements_Line_4(index->CDCQPWindowRectangles()));
    }

/**
 * Layout the editor indicator icons
 */
void CAknExtMultilineQueryControl::LayoutEditorIndicator(const TLayoutMethod& /*aLayoutM*/)
    {
    CCoeControl* editor = ControlByLayoutOrNull(iQueryType);
    TIndex LAFIndex(iLinePos,iFirstQueryPromptLines,iSecondQueryPromptLines);

    if (!iEditIndicator || !editor || iFlags.IsSet(EEditorIndicatorOff))
        return;
        
    if (editor->IsFocused())
        {
        TAknWindowLineLayout indicatorLine;
        
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            TInt promptLines = ( iLinePos == EFirstLine ? iFirstQueryPromptLines : iSecondQueryPromptLines );            
            static const TInt lineTable[4] = { 2, 2, 1, 3 };                
            indicatorLine = AknLayoutScalable_Avkon::indicator_popup_pane_cp4( lineTable[promptLines] ).LayoutLine();
            }
        else
            {
            indicatorLine = AKN_LAYOUT_WINDOW_Combined_data_and_code_query_pop_up_window_elements_Line_5(LAFIndex.CDCQPWindowLine5());
            }
            
        AknLayoutUtils::LayoutControl( iEditIndicator, LayoutRect(), indicatorLine );
        }
    else
        iEditIndicator->SetRect(TRect(TPoint(0,0),TPoint(0,0)));
    }
    
    
EXPORT_C void CAknExtMultilineQueryControl::HandleResourceChange( TInt aType ) 
    {
    CCoeControl::HandleResourceChange( aType );
        
    if ( aType == KAknsMessageSkinChange )
        {
        CAknQueryExtension* extension = QueryExtension();
        if( iHasEditor && extension && extension->EditorContext() )
            {
            extension->EditorContext()->SetParentContext( AknsDrawUtils::ControlContextOfParent( this ) );
            }
        }
    else if( aType == KEikDynamicLayoutVariantSwitch ) 
        {
        SizeChanged(); 
        }
    }    


/*****************************************************************
 * CAknExtMultilineQueryControl::TIndex
 *
 * Manage indexes into LAF tables
 *
 * PQDC stands for 'Popup Query Data Code'
 *
 * CDCQP stands for 'Combined Data Code Query Popup'
 ******************************************************************/

/**
 * Construction, iLinePos is the position of the current line, either first or
 * second. iFirstLine is the numeber of prompt lines for the first query, either 1
 * or 2. iSecondline is the number of prompt lines for the second query, either 1 or 2
 */ 
CAknExtMultilineQueryControl::TIndex::TIndex(const TLinePosition& aLinePos, 
                                                 TInt aFirstQueryPromptLines, TInt aSecondQueryPromptLines) :
    iLinePos(aLinePos), iFirstQueryPromptLines(aFirstQueryPromptLines), iSecondQueryPromptLines(aSecondQueryPromptLines)
        {
        }

/**
 * Check that we are in a consistent state for retrieving correct indexes
 *
 */
void CAknExtMultilineQueryControl::TIndex::SelfTest() const
    {
    __ASSERT_DEBUG(iLinePos == EFirstLine || iLinePos == ESecondLine,
        Panic(EAknPanicInvalidValue));
    __ASSERT_DEBUG(iFirstQueryPromptLines >= 0  && iFirstQueryPromptLines <= 2, 
        Panic(EAknPanicInvalidValue));
    __ASSERT_DEBUG(iSecondQueryPromptLines >= 0 && iSecondQueryPromptLines <= 2, 
        Panic(EAknPanicInvalidValue));
    }

/**
 * We tolerate a null number of prompt lines. If this is the case we set
 * the number of lines to 1 (empty query will use layout of a query with a
 * line of text).
 */
TInt CAknExtMultilineQueryControl::TIndex::FirstQueryPromptLines() const
    {
    SelfTest();
    return iFirstQueryPromptLines > 0 ? iFirstQueryPromptLines - 1 : 1;
    }

/**
 * We tolerate a null number of prompt lines. If this is the case we set
 * the number of lines to 1 (empty query will use layout of a query with a
 * line of text).
 */
TInt CAknExtMultilineQueryControl::TIndex::SecondQueryPromptLines() const
    {
    SelfTest();
    return iSecondQueryPromptLines > 0 ? iSecondQueryPromptLines - 1: 1;
    }


/**
 * Return index into Main Pane PQDC Window, which
 * depends on total number of prompt lines minus 2, e.g.
 * index 0 for 2 prompt lines total.
 *
 */
TInt CAknExtMultilineQueryControl::TIndex::MainPanePQDCWindow() const
    {
    SelfTest();
    static const TInt KMainPanePQDCWindow[3] = {0,1,2}; 
    return KMainPanePQDCWindow[FirstQueryPromptLines() + SecondQueryPromptLines()];
    }

/**
 * Return index into PQDC Window Rectangles, which
 * depends on line position and number or prompt lines in
 * both queries.
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowLine1() const
    {
    SelfTest();
    static const TInt KPQDCWindowRectanglesIndex[2][2][2] = 
        {    
            {{0,4},{2,6}},   //First  line
            {{1,5},{3,7}}    //Second line
        };
    return KPQDCWindowRectanglesIndex[(TInt)iLinePos][FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowLine2() const
    {
    return CDCQPWindowLine1();
    }

/**
 * Return index into PQDC Window Line 3, which depends on number of prompt
 * lines in both queries
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowLine3() const
    {
    SelfTest();
    static const TInt KCDCQPWindowLine3Index[2][2] = 
        {    
            {0,2},
            {1,3}    
        };  
    return KCDCQPWindowLine3Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowRectangles() const
    {
    return CDCQPWindowLine1();
    }

TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowLine5() const
    {
    return CDCQPWindowLine1();
    }


/**
 * Return index into 'CDCQP Window texts Line 1', which 
 * depends on total number of promt lines and current 
 * prompt line number (received as parameter)
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowTextsLine1(TInt aLineNum) const
    {
    SelfTest();
    __ASSERT_DEBUG(aLineNum >= 0 && aLineNum < 2,Panic(EAknPanicInvalidValue));

    static const TInt KPQDCWindowTextsLine1Index[2][3] = {
        {0,0,2}, //First prompt line
        {1,1,3}  //Second prompt line
        };
    return KPQDCWindowTextsLine1Index[aLineNum][FirstQueryPromptLines() + SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window texts Line 2', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowTextsLine2() const
    {
    static const TInt KPQDCWindowTextsLine2Index[2][2] = {
        {3,2},
        {1,0}  
        };
    return KPQDCWindowTextsLine2Index[FirstQueryPromptLines()][SecondQueryPromptLines()];

    }

/**
 * Return index into 'CDCQP Window texts Line 3', which 
 * depends on number of promt lines and current 
 * prompt line number (received as parameter)
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowTextsLine3(TInt aLineNum) const
    {
    SelfTest();
    __ASSERT_DEBUG(aLineNum >= 0 && aLineNum < 2,Panic(EAknPanicInvalidValue));

    static const TInt KPQDCWindowTextsLine3Index[2][2][2] = {
        {{0,0}, {2,3}},  //First prompt line
        {{1,1}, {2,4}}   //Second Prompt Line
        };
    return KPQDCWindowTextsLine3Index[aLineNum][FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window texts Line 4', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCQPWindowTextsLine4() const
    {
    static const TInt KPQDCWindowTextsLine4Index[2][2] = {
        {3,2},
        {1,0}
        };
    return KPQDCWindowTextsLine4Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

/**
 * Return index into 'CDCQP Window graphics Line 5', which 
 * depends on number of prompt lines in both queries
 */
TInt CAknExtMultilineQueryControl::TIndex::CDCPQWindowGraphicsLine5() const
    {
    static const TInt KCDCPQWindowGraphicsLine5Index[2][2] = {
        {0,0}, 
        {0,1}  
        };
    return KCDCPQWindowGraphicsLine5Index[FirstQueryPromptLines()][SecondQueryPromptLines()];
    }

// End of File
