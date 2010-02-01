/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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

// AknPopupField.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include <barsread.h>
#include <gulicon.h>
#include <AknIconArray.h>
#include <eikmop.h>

#include "AknPopupField.h"
#include "AknQueryValue.h"
#include "aknlists.h"
#include "AknDef.h"
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <AknIconUtils.h>
#include <AknsPointerStore.h> 
#include <AknsFrameBackgroundControlContext.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <touchfeedback.h>

_LIT(KPopFieldLeadingLayoutTextActive, "1\t");
_LIT(KPopFieldLeadingLayoutTextInactive, "\t\t");
const TInt KDefaultMaxNoLines = 6;

class CAknPopupFieldExtension : public CBase
    {
public:
    TRect iFormFieldRect; // moved to extension
    TInt iEditTextPos; // position of editable text inside form. 0..5 based on Form data field texts, line 2 baseline from 2.6 spec.
    CAknsFrameBackgroundControlContext *iFrameSkinContext; // this will be linked to listbox's context as background.
    CAknsBasicBackgroundControlContext *iBgContext;
    MTouchFeedback* iFeedback;
    TInt iOldItemIndex;
    TBool iSingleClickEnabled;
    };


//*******************************************************************************************/
// AknPopupFieldBitmapButton

CAknPopupField::CAknPopupFieldBitmapButton::CAknPopupFieldBitmapButton()
    {
    // set all margins to zero, we just want the bitmap with no margin
    iMargins.iTop = 0;
    iMargins.iBottom = 0;
    iMargins.iLeft = 0;
    iMargins.iRight = 0;
    }


//*******************************************************************************************/
// CAknPopupField

EXPORT_C CAknPopupField::CAknPopupField()
: iCba( NULL ),
  iFormMode( EAknFormModeView ),
  iSelectionMode(EAknPopupFieldLabelMode),
  iMaxNoLines(KDefaultMaxNoLines)
    {
    }

EXPORT_C CAknPopupField::~CAknPopupField()
    {
    delete iAttemptExitAsync;
    delete iLabel;
    delete iButton;
    DestroyPopout();
    delete iLayoutDecorator;
    delete iOtherText;
    delete iEmptyText;
    delete iInvalidText;
    delete iCba;
    if (iExtension)
    delete iExtension->iBgContext;
    if (iExtension)
        delete iExtension->iFrameSkinContext;
    delete iExtension;
    }

EXPORT_C void CAknPopupField::ConstructL()
    {
    iEmptyText->Des() = KNullDesC;
    iInvalidText->Des() = KNullDesC;


    CommonConstructL();
    }

EXPORT_C void CAknPopupField::ConstructFromResourceL(TResourceReader& aReader)
    {
    iFlags=aReader.ReadInt16();
    iWidth=aReader.ReadInt16();
    iOtherText = aReader.ReadHBufCL();
    iEmptyNoteResourceId = aReader.ReadInt32();
    iEmptyText = aReader.ReadHBufCL();
    iInvalidText = aReader.ReadHBufCL();

    CommonConstructL();
    }
EXPORT_C void CAknPopupField::SetFormFieldRect(TRect aRect)
    { // captioned control will call this
    if (iExtension)
        iExtension->iFormFieldRect = aRect;
    }


void CAknPopupField::CommonConstructL()
    {
    iExtension = new(ELeave)CAknPopupFieldExtension;
    iExtension->iSingleClickEnabled = static_cast<CAknAppUi*>(
            iCoeEnv->AppUi() )->IsSingleClickCompatible();
    
    //iExtension = new(ELeave)CAknPopupFieldExtension;
    iExtension->iFormFieldRect = TRect(0,0,0,0);
    
    if (!iOtherText)
        iOtherText = HBufC::NewL(0); // set to zero length so we can then test for 0 length later

    iEmptyNoteTimeout = CAknNoteDialog::EShortTimeout;
    iEmptyNoteTone = CAknNoteDialog::ENoTone;
    
    ConstructLabelL();
    if (iFlags & EAknPopupFieldFlagButton)
        ConstructCommandButtonL();

    ConfigureDecorator();   
    ConstructLayoutDecoratorL();
    
    // layer 1, main_pane background
    iExtension->iBgContext =  CAknsListBoxBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMainListGene, TRect(0,0,1,1), ETrue,
        KAknsIIDQsnBgColumnAB, TRect(0,0,1,1) )  ;
    
    //CAknsBasicBackgroundControlContext::NewL( KAknsIIDQsnBgAreaMain, TRect(0,0,1,1), ETrue);
    // layer 2, form field highlight
    iExtension->iFrameSkinContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrInput, TRect(0,0,1,1), TRect(0,0,1,1), ETrue);
    
    iExtension->iFeedback = MTouchFeedback::Instance();
    }

void CAknPopupField::ConstructLabelL()
    {
    if (iLabel)
        return; // already exists
    iLabel=new(ELeave) CEikLabel();
    iLabel->SetContainerWindowL(*this);
    iLabel->SetTextL(KNullDesC);
    }

void CAknPopupField::ConstructCommandButtonL()
    {
    }

void CAknPopupField::ConstructSelectionListL()
    {
    if (iSelectionList)
        return; // already exists

    //TRect rect = Rect();
    if ( iFormMode==EAknFormModeEdit || iFormMode==EAknFormModeView )
        iSelectionList = new(ELeave) CAknFormGraphicStyleListBox;
    else if ( iFormMode==EAknFormModeEditWideWithoutGraphic || iFormMode==EAknFormModeViewWideWithoutGraphic )
        iSelectionList = new(ELeave) CAknFormGraphicWideStyleListBox;
    else // wide with bitmap for now use wide style
        iSelectionList = new(ELeave) CAknFormGraphicWideStyleListBox;

    iSelectionList->ConstructWithWindowL(this, EAknListBoxMultipleSelection);
    // We dont want captionedcontrol's skin context, since captionedcontrol has
    // different coordinates. (window starts with 0,0).
    iSelectionList->SetMopParent(NULL); 
    iSelectionList->SetParent(this); 

    iSelectionList->SetListBoxObserver(this);

    // set the array into the listbox
    iSelectionList->Model()->SetItemTextArray(iLayoutDecorator);
    iSelectionList->Model()->SetOwnershipType(ELbmDoesNotOwnItemArray);

    iSelectionList->SetObserver(this);

    InitialiseRadioButtonBitmapsL();
    iSelectionList->ItemDrawer()->FormattedCellData()->SetControl(iSelectionList);
    //TRect screenRect = AknLayout::screen().Rect();
    iSelectionList->ItemDrawer()->FormattedCellData()->SetBackgroundSkinStyle(&KAknsIIDQsnFrInput, iExtension->iFormFieldRect);
    }


void CAknPopupField::SetUpScrollBarL()
    {
    if ( !iExtension || !iExtension->iSingleClickEnabled )
        {
        __ASSERT_DEBUG( iCba, Panic( EAknPanicPopupFieldCBADoesntExist ) );
        }
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
    iSelectionList->SetMopParent(this); // to get remote scb
    iSelectionList->CreateScrollBarFrameL(ETrue, ETrue);
    iSelectionList->SetMopParent(NULL);
    iSelectionList->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
    }

void CAknPopupField::SetScrollBarSelectionL()
    {
    TInt selection = iValue->CurrentValueIndex();
    if (IsInvalid()) selection = 0;
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
    iSelectionList->SetCurrentItemIndex(selection);
    iSelectionList->View()->SelectItemL(selection);

    if ( iExtension )
        {
        iExtension->iOldItemIndex = iSelectionList->CurrentItemIndex();
        }
    }


void CAknPopupField::InitialiseRadioButtonBitmapsL()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_RADIOBUTT_BMP);

    HBufC* bmpFile = reader.ReadHBufCL();
    TInt bmpSelected = reader.ReadInt16();
    TInt bmpSelectedM = reader.ReadInt16();
    TInt bmp = reader.ReadInt16();
    TInt bmpM = reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader

    if (bmpFile == NULL)
        return;
    CleanupStack::PushL(bmpFile);   

    if (iFlags & EAknPopupFieldNoGraphic)
        {// no graphic
        SetShowIndicatorsL(EFalse);
        }
    
    CArrayPtr<CGulIcon>* icons = iSelectionList->ItemDrawer()->FormattedCellData()->IconArray();
    if ( icons )
        {
        icons->ResetAndDestroy();
        }
    else
        {
        icons = new(ELeave) CAknIconArray(2);
        iSelectionList->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons); // ownership transferred, cell data deletes all members of list
        }

    CFbsBitmap* bitmap = 0;
    CFbsBitmap* mask = 0;

    //AknIconUtils::CreateIconLC(bitmap, mask, *bmpFile, bmpSelected, bmpSelectedM);
    AknsUtils::CreateColorIconLC( skin, KAknsIIDQgnIndiRadiobuttOn,
                KAknsIIDQsnIconColors,
                EAknsCIQsnIconColorsCG15,
                bitmap, mask, *bmpFile,
                bmpSelected, 
                bmpSelectedM,
                KRgbBlack);

        
    CGulIcon* gulicon = CGulIcon::NewL(bitmap,mask); // ownership passed
    CleanupStack::Pop(); // mask
    CleanupStack::Pop(); // bitmap
    CleanupStack::PushL(gulicon);
    icons->AppendL(gulicon); 
    CleanupStack::Pop(); // gulicon
        
    bitmap = 0;
    mask = 0;

    //AknIconUtils::CreateIconLC(bitmap, mask, *bmpFile, bmp, bmpM);
    AknsUtils::CreateColorIconLC( skin, KAknsIIDQgnIndiRadiobuttOff,
            KAknsIIDQsnIconColors,
            EAknsCIQsnIconColorsCG15,
            bitmap, mask, *bmpFile,
            bmp, 
            bmpM,
            KRgbBlack);

    
    CGulIcon* gulicon2 = CGulIcon::NewL(bitmap,mask); // ownership passed
    CleanupStack::Pop(); // mask
    CleanupStack::Pop(); // bitmap
    CleanupStack::PushL(gulicon2);
    icons->AppendL(gulicon2);
    CleanupStack::Pop(); // gulicon2

    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));

    CleanupStack::PopAndDestroy(); // bmpfile
    }

EXPORT_C TSize CAknPopupField::MinimumSize()
    {
    TSize size(0,0);
    TSize minTabSize(0,0);

    switch(iSelectionMode)
        {
    case EAknPopupFieldLabelMode:
        if (iLabel)
            size=iLabel->MinimumSize();
        if (iButton)
            minTabSize = iButton->MinimumSize();
        size.iWidth+=minTabSize.iWidth+iBorder.Margins().iLeft;
        size.iHeight=Max(size.iHeight+iBorder.SizeDelta().iHeight,minTabSize.iHeight);
        break;
    case EAknPopupFieldSelectionListMode:
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
        size = iSelectionList->MinimumSize();
        break;
    default:
        __ASSERT_DEBUG(ETrue, Panic(EAknPanicPopupFieldUndefinedMode));
        break;
        }
    return size;
    }


EXPORT_C void CAknPopupField::SizeChanged()
    {
    TRAP_IGNORE(DoSizeChangedL());
    }

EXPORT_C void CAknPopupField::FocusChanged( TDrawNow aDrawNow )
    {
    CEikBorderedControl::FocusChanged( aDrawNow );
    if( iSelectionList )
        {
        iSelectionList->SetFocus( IsFocused() );
        }
    }

void CAknPopupField::DoSizeChangedL()
    {
    // captioned control is supposed to set the iFormFieldRect before SizeChanged().
    // note that the iLabel in Label mode is really implemented in wrong place -- popup field should not be
    // responsible of the label.
    __ASSERT_DEBUG(iExtension && iExtension->iFormFieldRect != TRect(0,0,0,0), Panic(EAknPanicPopupFieldNoFieldRectSet));
    const TRect rect(Rect());

    switch(iSelectionMode)
        {
    case EAknPopupFieldLabelMode:
            {
#if 0
            TInt mode = (( iFormMode==EAknFormModeEdit 
                           || iFormMode==EAknFormModeEditWideWithGraphic 
                           || iFormMode==EAknFormModeEditWideWithoutGraphic) 
                         && iButton) ? 0 : 1;
            TAknTextLineLayout labelLayout(AKN_LAYOUT_TEXT_List_pane_texts__form_graphic__Line_1(0,mode));
            if ( iFormMode==EAknFormModeEdit || iFormMode==EAknFormModeView )
                {
                labelLayout = AKN_LAYOUT_TEXT_List_pane_texts__form_graphic__Line_1(0,mode);
                }
            else if ( iFormMode==EAknFormModeEditWideWithoutGraphic || iFormMode==EAknFormModeViewWideWithoutGraphic )
                {
                labelLayout = AKN_LAYOUT_TEXT_List_pane_texts__form_graphic_wide__Line_1(0, mode, 0,0);
                }
            else // wide with bitmap for now use wide style
                {
                labelLayout = AKN_LAYOUT_TEXT_List_pane_texts__form_graphic_wide__Line_1(0, mode, 0,0);
                }
            TAknTextLineLayout labelLayoutFormView(AKN_LAYOUT_TEXT_Form_data_field_texts_Line_2(0));

//      labelLayout.iFont = labelLayoutFormView.iFont; // for view and edit mode need same font as in form, in expanded mode use from laf
            AknLayoutUtils::LayoutLabel(iLabel, rect, labelLayout, AknLayoutUtils::FontFromId(labelLayoutFormView.FontId()));
#endif
            TAknTextLineLayout labelLayout(AknLayout::Form_data_field_texts_Line_2(0));
            if (iFormMode == EAknFormModeEdit || iFormMode == EAknFormModeView)
                {
                labelLayout = AknLayout::Form_data_field_texts_Line_2(0);
                }
            else if ( iFormMode==EAknFormModeEditWideWithoutGraphic || iFormMode==EAknFormModeViewWideWithoutGraphic )
                {
                labelLayout = AknLayout::Form_data_wide_field_texts_Line_2(0);
                }
            else // wide with bitmap for now use wide style
                {
                labelLayout = AknLayout::Form_data_wide_graphic_field_texts_Line_2(0);
                }
            AknLayoutUtils::LayoutLabel(iLabel, iExtension ? iExtension->iFormFieldRect : Rect(), labelLayout);         

            if (iButton)
                AknLayoutUtils::LayoutControl(iButton, rect, AKN_LAYOUT_WINDOW_List_pane_elements__form_graphic__Line_2);

            if (IsInvalid())
                {
                if (iInvalidText)
                    {
                    iLabel->SetTextL(*iInvalidText); // takes copy
                    iLabel->CropText();
                    }
                else
                    iLabel->SetTextL(KNullDesC);
                }
            else if (!IsEmpty())
                {  
                // update the label if the text should be changed due to the size change
                HBufC* newText = iValue->CurrentValueTextLC(); // ownership passed
                iLabel->SetTextL(*newText); // takes copy
                CleanupStack::PopAndDestroy(); // newText
                iLabel->CropText();
                }
            else
                {
                if (iEmptyText)
                    {
                    iLabel->SetTextL(*iEmptyText); // takes copy
                    iLabel->CropText();
                    }
                else
                    iLabel->SetTextL(KNullDesC);
                }

            // reset the border to none
            if (iButton)
                iButton->SetBorder(TGulBorder::ENone);
            break;
            }
    case EAknPopupFieldSelectionListMode:
            {
            __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
            iSelectionList->SetRect(rect);
            AknsUtils::RegisterControlPosition(this);
            AknsUtils::RegisterControlPosition(iSelectionList);
            TRect listBoxRect = iExtension->iFormFieldRect; //iSelectionList->Rect();
            listBoxRect.iTl = TPoint(0,0);
            // Cannot use KAknsIIDNone here because highlight animation
            // creation would fail in eikfrlbd.cpp (with KAknsIIDNone there
            // would be no background to animate).
            iSelectionList->ItemDrawer()->FormattedCellData()->SetBackgroundSkinStyle(&KAknsIIDNone, listBoxRect);
            //iSelectionList->ItemDrawer()->FormattedCellData()->SetBackgroundSkinStyle(&KAknsIIDNone /*Center*/,  /*Rect()*/ /*TRect(0,0,176,208)*/);
            TAknLayoutRect frame_tl;
            frame_tl.LayoutRect(listBoxRect, SkinLayout::Input_field_skin_placing__general__Line_2());
            TAknLayoutRect frame_br;
            frame_br.LayoutRect(listBoxRect, SkinLayout::Input_field_skin_placing__general__Line_5());
            TRect center = TRect(frame_tl.Rect().iBr, frame_br.Rect().iTl);

            //
            // Skin contexts are in 3 layers:
            //  1) background
            //  2) form field highlight
            //  3) list context
            if (iExtension)
                {           
                TRect main_pane;
                AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, main_pane );

                TRect clientRect = main_pane;
                TPoint ctrlPoint = PositionRelativeToScreen();
                
                TPoint innerPoint = Rect().iTl;
                clientRect.iTl.iX -= ctrlPoint.iX;
                clientRect.iBr.iX -= ctrlPoint.iX;
                clientRect.iTl.iY -= ctrlPoint.iY;
                clientRect.iBr.iY -= ctrlPoint.iY;

                clientRect.iTl.iX += innerPoint.iX;
                clientRect.iBr.iX += innerPoint.iX;
                clientRect.iTl.iY += innerPoint.iY;
                clientRect.iBr.iY += innerPoint.iY;

                
                //TPoint p = clientRect.iTl;
                iExtension->iBgContext -> SetParentPos(main_pane.iTl);
                iExtension->iBgContext -> SetRect(clientRect /*TRect(c,clientRect.Size())*/);
                }

            if (iExtension)
                {
                // Calculate formfieldRect relative to screen.              
                TPoint p; 
                p = PositionRelativeToScreen();
                p.iX += iExtension->iFormFieldRect.iTl.iX;
                p.iY += iExtension->iFormFieldRect.iTl.iY;
                p.iX -= Rect().iTl.iX;
                p.iY -= Rect().iTl.iY;
                iExtension->iFrameSkinContext -> SetParentPos( p /*iSelectionList->PositionRelativeToScreen()*/ );
                

                iExtension->iFrameSkinContext -> SetFrameRects(listBoxRect, center);
                iExtension->iFrameSkinContext -> SetFrame(KAknsIIDQsnFrInput ); // frInput or frList?
                iExtension->iFrameSkinContext -> SetParentContext(iExtension->iBgContext);
                }
            CAknsBasicBackgroundControlContext *bgContext = (CAknsBasicBackgroundControlContext*)iSelectionList->ItemDrawer()->FormattedCellData()->SkinBackgroundContext();
            if (iExtension)
                {
                bgContext->SetParentContext(iExtension->iFrameSkinContext);
                //iExtension->iFrameSkinContext -> SetParentPos( iSelectionList->PositionRelativeToScreen() );

                }
            TRect main_pane = iAvkonAppUi->ClientRect();

            TAknLayoutRect listscroll_form_pane_rect;
            listscroll_form_pane_rect.LayoutRect(main_pane, AknLayoutScalable_Avkon::listscroll_form_pane());


            // set SVG icons (call SizeChanged between InitialiseRadioButtonBitmapsL and Draw)
            CArrayPtr<CGulIcon> *iconarray = 0;
            iconarray = iSelectionList->ItemDrawer()->FormattedCellData()->IconArray();
                
            if (iconarray)
                {
                TInt iconCount = iconarray->Count();
                if (iconCount)
                    {
                    TAknLayoutRect rect;
                    rect.LayoutRect(Rect(), AKN_LAYOUT_WINDOW_List_pane_elements__form_graphic__Line_2);
                    for (TInt i = 0 ; i < iconCount ; i++)
                        AknIconUtils::SetSize((*iconarray)[i]->Bitmap(), rect.Rect().Size());
                    }
                }
            break;
            }
    default:
            __ASSERT_DEBUG(ETrue, Panic(EAknPanicPopupFieldUndefinedMode));
            break;
        }
    iFlags |= EAknPopupFieldFlagInitialised;
    }


EXPORT_C TKeyResponse CAknPopupField::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    switch(iSelectionMode)
        {
    case EAknPopupFieldLabelMode:
        {
        TBool okPressed = aKeyEvent.iCode==EKeyTab || aKeyEvent.iCode == EKeyEnter || aKeyEvent.iCode == EKeyOK;
        switch(aKeyEvent.iCode)
            {
            case EKeyTab: // fall through
            case EKeyEnter: // fall through
            case EKeyOK:
                if ((okPressed) && (!(aKeyEvent.iModifiers&EModifierCtrl) || aKeyEvent.iModifiers&EModifierPureKeycode))
                    {
                    // note also that when page goes from view to edit mode, controls go from nonfocusing to focusing
                    // therefore we only want focusing controls that have the focus
                    if (!IsNonFocusing() && IsFocused())
                        {
                        if (!IsEmpty())
                            {
                            CreatePopoutL();
                            // In single click, enable highlight when opening
                            // with hw key
                            if ( iExtension
                                    && iExtension->iSingleClickEnabled
                                    && iSelectionList )
                                {
                                TKeyEvent enterEvent( aKeyEvent );
                                enterEvent.iCode = EKeyEnter;
                                iSelectionList->OfferKeyEventL(
                                        enterEvent, aType );
                                }
                            }
                        else
                            ShowEmptyListNoteL();
                        return EKeyWasConsumed;
                        }
                    else
                        return EKeyWasNotConsumed;
                    }
                break;
            case EKeyLeftArrow: // fall through
            case EKeyRightArrow:
                return HandleHorizontalKeyEventL(aKeyEvent.iCode);
            default:
                return EKeyWasNotConsumed;
            }
        }
        break;
    case EAknPopupFieldSelectionListMode:
        __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
        return iSelectionList->OfferKeyEventL(aKeyEvent,aType);
    default:
        __ASSERT_DEBUG(ETrue, Panic(EAknPanicPopupFieldUndefinedMode));
        break;
        }
    return EKeyWasConsumed;
    }

EXPORT_C void CAknPopupField::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent)
    {
    switch (aEvent)
        {
    case EEventRequestFocus: // drop through
    case EEventPrepareFocusTransition:
        ReportEventL(aEvent);
        break;
    case EEventStateChanged:
        if (aControl != NULL && aControl==iButton)
            CreatePopoutL();
        break;
    case EEventRequestExit:
        break;
    case EEventRequestCancel:
        if ( AknLayoutUtils::PenEnabled() )
            {
            AttemptExitL(EFalse);
            }
        break;
    default:
        break;
        }
    }

EXPORT_C void CAknPopupField::ProcessCommandL(TInt aCommandId)
    {
    // Respond to softkey events
    switch (aCommandId)
        {
        case EAknSoftkeyOk:
            AttemptExitL(ETrue);
            break;
        case EAknSoftkeyCancel:
            AttemptExitL(EFalse);
            break;
        default:
            break;
        }
    }

EXPORT_C void CAknPopupField::HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)
    {
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
    if (aListBox == iSelectionList)
        {
        switch ( aEventType )
            {
            case MEikListBoxObserver::EEventItemSingleClicked:
                {
                CListBoxView* view = iSelectionList->View();
                
                if ( view->CurrentItemIndex() != iExtension->iOldItemIndex )
                    {
                    view->DeselectItem( iExtension->iOldItemIndex );
                    iExtension->iOldItemIndex = view->CurrentItemIndex();
                    view->SelectItemL( iExtension->iOldItemIndex );
                    }
                }

            case MEikListBoxObserver::EEventItemDoubleClicked:
            case MEikListBoxObserver::EEventEnterKeyPressed:
                {
                // We can't delete the selection list until it's finished
                // processing the event, so call ourselves back and do it when
                // the list has finished.
                TCallBack cb( AttemptExitCallbackL, this );
                delete iAttemptExitAsync;
                iAttemptExitAsync = NULL;
                iAttemptExitAsync = new ( ELeave ) 
                    CAsyncCallBack( cb, CActive::EPriorityHigh );
                iAttemptExitAsync->CallBack();
                }    
                break;
                
            default:
                break;
            }
        }
    }


EXPORT_C TInt CAknPopupField::CountComponentControls() const
    {
    CCoeControl* controls[] = 
        {
        iButton,
        iLabel,
        iSelectionList
        };

    TInt count = 0;
    for (TUint ii=0; ii<sizeof(controls)/sizeof(CCoeControl*); ii++)
        if (controls[ii])
            count++;
    return count;
    }

EXPORT_C CCoeControl* CAknPopupField::ComponentControl(TInt aIndex) const
    {
    CCoeControl* controls[] = 
        {
        iButton,
        iLabel,
        iSelectionList
        };

    for (TUint ii=0; ii<sizeof(controls)/sizeof(CCoeControl*); ii++)
        if (controls[ii] && aIndex-- == 0)
            return controls[ii];
    return NULL;    
    }

TBool CAknPopupField::HandleInteractionConfirmedL()
    {
    if (IsEmpty())
        {
        iLabel->SetTextL(KNullDesC);
        }
    else if (IsInvalid())
        {
        if (iInvalidText)
        {
        iLabel->SetTextL(*iInvalidText);
        iLabel->CropText();
        }
        else iLabel->SetTextL(KNullDesC);
        ReportEventL(EEventStateChanged);
        if (iObserver)
         iObserver->HandlePopupFieldEventL(this, MAknPopupFieldObserver::EAknPopupFieldEventValueChange, 0);        
        }
    else
        {
        HBufC* newText = iValue->CurrentValueTextLC(); // ownership passed
        iLabel->SetTextL(*newText); // takes copy
        CleanupStack::PopAndDestroy(); // newText
        iLabel->CropText();
        ReportEventL(EEventStateChanged);
        if (iObserver)
            iObserver->HandlePopupFieldEventL(this, MAknPopupFieldObserver::EAknPopupFieldEventValueChange, 0);
        }
    return ETrue;
    }

void CAknPopupField::DestroyPopout()
    {
    if (iSelectionList)
        {
        iEikonEnv->RemoveFromStack(iSelectionList);
        delete iSelectionList;
        iSelectionList=NULL;
        }
    }

TBool CAknPopupField::IsEmpty() const
    {
    if (!iValue)
        return ETrue;
    if (iDecorator.MdcaCount() <= 0)
        return ETrue;
    return EFalse;
    }

TBool CAknPopupField::IsInvalid() const
    {
    if (IsEmpty()) return EFalse;
    TInt valueIndex = iValue->CurrentValueIndex();
    if (valueIndex < 0 || valueIndex >= iDecorator.MdcaCount())
        return ETrue;
    return EFalse;
    }

TKeyResponse CAknPopupField::HandleHorizontalKeyEventL(TUint aKeyEventCode)
    {
    TKeyResponse keyResponse = EKeyWasNotConsumed;
    TBool finished = EFalse;

    TInt decIndex = 0;
    if (IsEmpty() || (iDecorator.MdcaCount() == 1 && iDecorator.DecoratedIndex(decIndex)))
        finished = ETrue; // Popupfield was empty or just contained decorated item

    TInt changeIndexBy = 0;
    if (!finished)
        {
        TBool isMirrored = AknLayoutUtils::LayoutMirrored();

        switch(aKeyEventCode)
            {
            case EKeyLeftArrow:
                changeIndexBy = (isMirrored ? 1 : -1);
                break;
            case EKeyRightArrow:
                changeIndexBy = (isMirrored ? -1 : 1);
                break;
            default:
                finished = ETrue; // Not a horizontal key event
                break;
            }
        }

    if (!finished)
        {
        TInt newValue = iValue->CurrentValueIndex() + changeIndexBy;
        if (newValue < 0) // cycle around
            {
            newValue = iValue->MdcArray()->MdcaCount() - 1;
            }
        else if (newValue > (iValue->MdcArray()->MdcaCount() - 1)) // cycle around
            {
            newValue = 0;
            }
        if (newValue != iValue->CurrentValueIndex())
            {
            iValue->SetCurrentValueIndex(newValue);
            HandleInteractionConfirmedL();
            DrawDeferred();
            }
        keyResponse = EKeyWasConsumed;
        }

    return keyResponse;
    }

void CAknPopupField::CreatePopoutL()
    {
    if ( !iExtension || !iExtension->iSingleClickEnabled )
        {
        CreateCbaL();
        }
    ConstructSelectionListL();
    ChangeMode(EAknPopupFieldSelectionListMode);
    SetUpScrollBarL();
    // need to initialize the selection so that the list box is drawn in the correct place
    SetScrollBarSelectionL();
    // make the selection list visible and update the scrollbar
    SetScrollBarSelectionL();
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
    iSelectionList->MakeVisible(ETrue);
    iSelectionList->ActivateL();
    iSelectionList->SetFocus(ETrue);
    iSelectionList->UpdateScrollBarsL();

    // now let the container resize the list box
    if (iObserver)
        iObserver->HandlePopupFieldEventL(this, MAknPopupFieldObserver::EAknPopupFieldEventModeChange, NumLines());
    }


void CAknPopupField::CreateCbaL()
    {
    CEikButtonGroupContainer* cba = CEikButtonGroupContainer::NewL(
        CEikButtonGroupContainer::ECba,
        CEikButtonGroupContainer::EHorizontal, 
        this, // popup field is a command observer
        R_AVKON_SOFTKEYS_OK_CANCEL__OK);

    delete iCba;
    iCba = cba;

    const TSize screenSize=iAvkonAppUi->ApplicationRect().Size(); /*TSize(AKN_LAYOUT_WINDOW_screen.iW, AKN_LAYOUT_WINDOW_screen.iH);*/
    iCba->SetBoundingRect(TRect(screenSize));
    }


EXPORT_C void CAknPopupField::HandleResourceChange(TInt aType)
    {
    EAknFormMode newMode( iFormMode );
    TBool notEditable( EFalse );
    switch( aType )
        {
        case KEikMessageCaptionedControlEditableStateChange:
            {
            newMode = EAknFormModeEdit;
            break;
            }
        case KEikMessageCaptionedControlEditableStateChangeWideWithGraphic:
            {
            newMode = EAknFormModeEditWideWithGraphic;
            break;
            }
        case KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic:
            {
            newMode = EAknFormModeEditWideWithoutGraphic;
            break;
            }
        case KEikMessageCaptionedControlNotEditableStateChange:
            {
            newMode = EAknFormModeView;
            notEditable = ETrue;
            break;
            }
        case KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic:
            {
            newMode = EAknFormModeViewWideWithGraphic;
            notEditable = ETrue;
            break;
            }
        case KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic:
            {
            newMode = EAknFormModeViewWideWithoutGraphic;
            notEditable = ETrue;
            break;
            }
        default:
            {
            break;
            }
        }
    if ( newMode != iFormMode )
        {
        if ( iSelectionList && notEditable
                && iSelectionMode == EAknPopupFieldSelectionListMode
                && iExtension && iExtension->iSingleClickEnabled )
            {
            // Edit mode to view while popup is open -> first cancel popup
            AttemptExitL( EFalse );
            }
        else
            {
            __ASSERT_DEBUG( iSelectionMode == EAknPopupFieldLabelMode,
                    Panic( EAknPanicPopupFieldWrongMode ) );
            }
        iFormMode = newMode;
        if ( iButton &&
                ( notEditable || ( iValue && iDecorator.MdcaCount() != 0 ) ) )
            {
            iButton->MakeVisible( !notEditable );
            }
        }
    if ( iSelectionList && !IsEmpty() )
        {
        TRAP_IGNORE( InitialiseRadioButtonBitmapsL() );
        }

    CEikBorderedControl::HandleResourceChange(aType);
    }
    
//---------------------------------------------------------------------------------------
// CAknPopupField::HandlePointerEventL()
// Starts popuplist or empty popuplist when popup item is clicked
//---------------------------------------------------------------------------------------
//  
EXPORT_C void CAknPopupField::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {      
            // note also that when page goes from view to edit mode, controls go from nonfocusing to focusing
            // therefore we only want focusing controls that have the focus
            if (!IsNonFocusing() && IsFocused())
                {
                if ( iExtension && iExtension->iFeedback )
                    {
                    iExtension->iFeedback->InstantFeedback(
                                                        this,
                                                        ETouchFeedbackPopUp,
                                                        ETouchFeedbackVibra,
                                                        aPointerEvent );
                    }
                if (!IsEmpty())
                    {
                    CreatePopoutL();
                    }
                else
                    {
                    ShowEmptyListNoteL();
                    }
                }
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            if (!IsNonFocusing() 
              && IsFocused() 
              && iExtension->iFormFieldRect.Contains( aPointerEvent.iPosition ))
                {
                // clicked inside popup field, will open popup or note
                if ( iExtension && iExtension->iFeedback )
                    {
                    iExtension->iFeedback->InstantFeedback( ETouchFeedbackPopUp );
                    }
                }
            if ( iSelectionList && iSelectionMode == EAknPopupFieldSelectionListMode )
                {
                // Clicked outside popup form field, closing popup
                if ( !iExtension->iFormFieldRect.Contains( aPointerEvent.iParentPosition ) )
                    {
                    if ( iExtension && iExtension->iFeedback )
                        {
                        iExtension->iFeedback->InstantFeedback( ETouchFeedbackPopUp );
                        }
                    AttemptExitL( EFalse );
                    }
                }
            }
        }
    }


EXPORT_C void* CAknPopupField::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

    
EXPORT_C void CAknPopupField::Reserved_1()
    {}
EXPORT_C void CAknPopupField::Reserved_2()
    {}


    
EXPORT_C void CAknPopupField::SetAllowsUserDefinedEntry(TBool aAllows)
    {
    if (aAllows)
        {
        if (iOtherText->Length() > 0)
            iFlags |= EAknPopupFieldFlagAllowsUserDefinedEntry;
        }
    else
        iFlags &= ~EAknPopupFieldFlagAllowsUserDefinedEntry;
    
    ConfigureDecorator();
    }


EXPORT_C void CAknPopupField::ActivateSelectionListL()
    {
    if (!IsEmpty())
        {
        CreatePopoutL();
        }
    else
        {
        ShowEmptyListNoteL();
        }
    }

EXPORT_C void CAknPopupField::SetQueryValueL(MAknQueryValue* aValue)
    {
    __ASSERT_DEBUG(aValue, Panic(EAknPanicPopupFieldInvalidValue));

    iValue = aValue;
    
    if (iFlags & EAknPopupFieldFlagInitialised)
        {
        // put the current value text into the label
        HBufC* newText = iValue->CurrentValueTextLC();
        iLabel->SetTextL(*newText); // takes copy
        CleanupStack::PopAndDestroy(); // newText
        iLabel->CropText();
        if (iObserver)
            {
            iObserver->HandlePopupFieldEventL( this, 
            MAknPopupFieldObserver::EAknPopupFieldEventValueChange, 0 );
            }
        }

    // decorate the array from the query value
    const MDesCArray* array = iValue->MdcArray();
    iDecorator.SetArray(array);
    }

EXPORT_C void CAknPopupField::SetFont(const CFont* aFont) 
    {   
    if (iLabel)
        iLabel->SetFont(aFont);
    }

EXPORT_C void CAknPopupField::SetShowIndicatorsL(TBool aShowIndicators)
    {
    if (!aShowIndicators)
        {
        if (iLayoutDecorator)
            iLayoutDecorator->SetLeadingDecorationTextL(KPopFieldLeadingLayoutTextInactive);
        }
    }

EXPORT_C TInt CAknPopupField::NumLines() const
    {
    TInt lines = 0;

    switch(iSelectionMode)
        {
    case EAknPopupFieldLabelMode:
        lines = 1;
        break;
    case EAknPopupFieldSelectionListMode:
        lines = iDecorator.MdcaCount();
        break;
    default:
        __ASSERT_DEBUG(ETrue, Panic(EAknPanicPopupFieldUndefinedMode));
        break;
        }

    // we must restrict ourselves to the max number of lines.
    if (lines > iMaxNoLines)
        lines = iMaxNoLines;
    return lines;
    }

EXPORT_C void CAknPopupField::SetPopupFieldObserver(MAknPopupFieldObserver* aObserver)
    {
    iObserver = aObserver;
    }

EXPORT_C void CAknPopupField::SetEmptyListNoteL(TInt aResourceId, CAknNoteDialog::TTimeout aTimeout, CAknNoteDialog::TTone aTone)
    {
    iEmptyNoteResourceId = aResourceId;
    iEmptyNoteTimeout = aTimeout;
    iEmptyNoteTone = aTone;
    }

EXPORT_C void CAknPopupField::SetEmptyTextL(const TDesC& aEmptyText)
    {
    HBufC* newText = aEmptyText.AllocLC();
    delete iEmptyText;
    iEmptyText = NULL;
    iEmptyText = newText;
    CleanupStack::Pop(); // newText

    if (IsEmpty())
        {
        iLabel->SetTextL(*iEmptyText);
        iLabel->CropText();
        DrawDeferred();
        }
    }

EXPORT_C void CAknPopupField::SetOtherTextL(const TDesC& aOtherText)
    {
    if (aOtherText.Length() < 1)
        return;

    HBufC* newText = aOtherText.AllocLC();
    delete iOtherText;
    iOtherText = NULL;
    iOtherText = newText;
    CleanupStack::Pop(); // newText

    ConfigureDecorator();
    }

EXPORT_C void CAknPopupField::SetInvalidTextL(const TDesC& aInvalidText)
    {
    HBufC* newText = aInvalidText.AllocLC();
    delete iInvalidText;
    iInvalidText = NULL;
    iInvalidText = newText;
    CleanupStack::Pop(); // newText

    if (IsInvalid())
        {
        iLabel->SetTextL(*iInvalidText);
        iLabel->CropText();
        }
    }


void CAknPopupField::ConfigureDecorator()
    {
    __ASSERT_DEBUG(iOtherText, Panic(EAknPanicPopupFieldUninitialisedMember));

    iDecorator.SetDecorationText(*iOtherText);
    iDecorator.SetActive(iFlags & EAknPopupFieldFlagAllowsUserDefinedEntry);
    }

void CAknPopupField::ConstructLayoutDecoratorL()
    {
    if (iLayoutDecorator)
        return; // already exists
    iLayoutDecorator = CAknListBoxLayoutDecorator::NewL();
    TPtrC textPtr(KPopFieldLeadingLayoutTextActive);
    iLayoutDecorator->SetLeadingDecorationTextL(textPtr);
    iLayoutDecorator->SetArray(&iDecorator);
    iLayoutDecorator->SetActive(ETrue); // for now
    }

void CAknPopupField::ShowEmptyListNoteL()
    {
    if (!iEmptyNoteResourceId)
        return;
    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog(iEmptyNoteTone,iEmptyNoteTimeout);
    dlg->PrepareLC(iEmptyNoteResourceId);
    dlg->RunLD();
    }

void CAknPopupField::AttemptExitL(TBool aAccept)
    {
    // we must be in selection list mode in order to get the cba event
    __ASSERT_DEBUG(iSelectionMode == EAknPopupFieldSelectionListMode, Panic(EAknPanicPopupFieldWrongMode));
    __ASSERT_DEBUG(iSelectionList != NULL, Panic(EAknPanicPopupFieldSelectionListDoesntExist));
    TBool finished = ETrue;

    if (aAccept)
        {
        // get current selection
        const TInt selection=iSelectionList->CurrentItemIndex();
        TInt decoratedIndex;
        TBool decorated = iDecorator.DecoratedIndex(decoratedIndex);
        if (decorated && (selection == decoratedIndex))
            {
            TBool accepted = iValue->CreateEditorL();
            if (!accepted)
                {
                // dialog was cancelled, so popup list must remain
                finished = EFalse;
                }
            }
        else
            iValue->SetCurrentValueIndex(selection);
        }

    if (finished)
        {
        delete iCba;
        iCba = NULL;
        DestroyPopout();
        ChangeMode(EAknPopupFieldLabelMode);
        // Move up to make sure the following line is always executed
        if (iObserver)
            iObserver->HandlePopupFieldEventL(this, MAknPopupFieldObserver::EAknPopupFieldEventModeChange, NumLines());
                
        if (aAccept)
            HandleInteractionConfirmedL();

        }
    }

void CAknPopupField::ChangeMode(EAknPopupFieldSelectionMode aNewMode)
    {
    // change mode, and show / hide the appropriate controls
    switch(aNewMode)
        {
    case EAknPopupFieldLabelMode:
        iSelectionMode = EAknPopupFieldLabelMode;
        iLabel->MakeVisible(ETrue);
        if (iButton)
            iButton->MakeVisible(ETrue);
        break;
    case EAknPopupFieldSelectionListMode:
        iSelectionMode = EAknPopupFieldSelectionListMode;
        iLabel->MakeVisible(EFalse);
        if (iButton)
            iButton->MakeVisible(EFalse);
        break;
    default:
        __ASSERT_DEBUG(ETrue, Panic(EAknPanicPopupFieldUndefinedMode));
        break;
        }
    }

TInt CAknPopupField::AttemptExitCallbackL(TAny* aThis)
    {
    if (aThis)
        {
        static_cast<CAknPopupField*>(aThis)->DoAttemptExitL();
        }
    return 0;
    }

void CAknPopupField::DoAttemptExitL()
    {
    AttemptExitL(ETrue);
    delete iAttemptExitAsync;
    iAttemptExitAsync = NULL;
    }

EXPORT_C void CAknPopupField::SetMaxNumberOfLinesPermitted(TInt aMaxNoLines)
    {
    iMaxNoLines = aMaxNoLines;
    };

EXPORT_C TTypeUid::Ptr CAknPopupField::MopSupplyObject(TTypeUid aId)
    {
    // Only thing supplied at this level of descent in the class hierarchy
    // or in the object provider chain is the cba
    if ( iCba )
        {
        TTypeUid::Ptr myPtr( SupplyMopObject( aId, iCba ) );
        if ( myPtr.Pointer() )
            {
            return myPtr;
            }
        }
    return CEikBorderedControl::MopSupplyObject( aId );
    }

EXPORT_C void CAknPopupField::Draw(const TRect& aRect) const
	{
	if ( iSelectionMode == EAknPopupFieldSelectionListMode )
	    {
        TBool backgroundDrawn = EFalse;

        if ( AknsUtils::AvkonSkinEnabled() )
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            MAknsControlContext* edCc = AknsDrawUtils::ControlContext( this );
            CWindowGc& gc = SystemGc();
            backgroundDrawn = AknsDrawUtils::Background(  skin, edCc, this, gc, aRect );
            iLabel->SetBrushStyle(CGraphicsContext::ENullBrush);
            }
    
        if ( !backgroundDrawn )
            {
            // This should be the legacy behaviour (there was no draw routine before 2.0)
            CEikBorderedControl::Draw( aRect );
            iLabel->SetBrushStyleFromContext();
            }
	    }
	}

// End of File
