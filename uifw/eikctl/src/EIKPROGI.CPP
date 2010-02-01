/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikprogi.h>
#include <eikon.hrh>
#include <eikpanic.h>
#include <coemain.h>
#include <barsread.h>
#include <gulbordr.h>
#include <eikenv.h>

#include <gulcolor.h>
#include <avkon.mbg>
#include <aknconsts.h>

#include <AknsUtils.h>
#include <AknsDrawUtils.h>

#include <AknUtils.h> // for arabic texts support

#include <AknIconUtils.h>

#include <applayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknappui.h>
#include <bitdev.h>
using namespace AppLayout;

const TInt KDefaultSpaceBetweenBlocks=1;

class CEikProgressInfoExtension : public CBase
    {
public:
        CEikProgressInfoExtension();
        ~CEikProgressInfoExtension();

        void DeleteBitmaps();
        
        CFbsBitmap* iFrameLeft;
        CFbsBitmap* iFrameCenter;
        CFbsBitmap* iFrameRight;

        CFbsBitmap* iFrameLeftMask;
        CFbsBitmap* iFrameCenterMask;
        CFbsBitmap* iFrameRightMask;
        
        CFbsBitmap* iOldBackgroundBitmapMask;
    };

CEikProgressInfoExtension::CEikProgressInfoExtension()
    {
    }
CEikProgressInfoExtension::~CEikProgressInfoExtension()
    {
    }

void CEikProgressInfoExtension::DeleteBitmaps()
    {
    delete iFrameLeft;
    iFrameLeft = NULL;
    delete iFrameCenter;
    iFrameCenter = NULL;
    delete iFrameRight;
    iFrameRight = NULL;
    delete iFrameLeftMask;
    iFrameLeftMask = NULL;
    delete iFrameCenterMask;
    iFrameCenterMask = NULL;
    delete iFrameRightMask;
    iFrameRightMask = NULL;
    delete iOldBackgroundBitmapMask;
    iOldBackgroundBitmapMask = NULL;
    }

EXPORT_C CEikProgressInfo::~CEikProgressInfo()
    {
    DeleteBitmaps();
    delete iExtension;
    AknsUtils::DeregisterControlPosition(this);
    }

EXPORT_C CEikProgressInfo::CEikProgressInfo()
    {
    __DECLARE_NAME(_S("CEikProgressInfo"));
    }

EXPORT_C CEikProgressInfo::CEikProgressInfo(const SInfo& aProgInfo)
    {
    __DECLARE_NAME(_S("CEikProgressInfo"));
    iInfo=aProgInfo;
    Construct();
    }

void CEikProgressInfo::Construct()
    {
    SetNonFocusing();
    iBorder=TGulBorder(TGulBorder::ENone);

    iLayout.iFillColor= iEikonEnv->ControlColor(EColorControlHighlightBackground, *this); //KEikProgressInfoDefaultFillColor;
    iLayout.iEmptyColor=iEikonEnv->ControlColor(EColorControlBackground, *this); //KEikProgressInfoDefaultEmptyColor;
    iLayout.iFillTextColor=iEikonEnv->ControlColor(EColorControlHighlightText, *this); //KEikProgressInfoDefaultFillTextColor;
    iLayout.iEmptyTextColor=iEikonEnv->ControlColor(EColorControlText, *this); //KEikProgressInfoDefaultEmptyTextColor;

    iLayout.iGapBetweenBlocks=KDefaultSpaceBetweenBlocks;
    if (iInfo.iHeight)
        iHeightWasSupplied=ETrue;
    }

// AKNLAF start
EXPORT_C void CEikProgressInfo::ConstructL()
    {
//    /* TODO: Commented out temporarily. Do we need this?

//    TAknLayoutRect voiceRecordRect, prNoteRect, addInfoRect;
//    voiceRecordRect.LayoutRect(Rect(), Voice_Recorder_elements_Line_4());
//    prNoteRect.LayoutRect(Rect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_2);
//    addInfoRect.LayoutRect(Rect(), AKN_LAYOUT_WINDOW_Note_with_additional_information_popup_window_elements_Line_2( 1 ));
//    TInt voiceRecordWidth = voiceRecordRect.Rect().Width();
//    TInt prNoteWidth = prNoteRect.Rect().Width();
//    TInt addInfoWidth = addInfoRect.Rect().Width();
//    __ASSERT_ALWAYS( iInfo.iWidth==voiceRecordWidth/*Voice_Recorder_elements_Line_4().iW*/
//                    || iInfo.iWidth==prNoteWidth/*AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_2.iW*/
//                    || iInfo.iWidth==addInfoWidth/*AKN_LAYOUT_WINDOW_Note_with_additional_information_popup_window_elements_Line_2( 1 ).iW*/,
//                    Panic(EEikPanicOutOfRange) );
//    */
    iExtension = new (ELeave) CEikProgressInfoExtension;
    LoadBitmapsL();
    }
// AKNLAF end

EXPORT_C void CEikProgressInfo::ConstructFromResourceL(TResourceReader &aReader)
    {
    iInfo.iTextType=(TEikProgressTextType)aReader.ReadInt16();
    iInfo.iSplitsInBlock=aReader.ReadInt16();
    iInfo.iFinalValue=aReader.ReadInt32();
    iInfo.iWidth=aReader.ReadInt32();
    iInfo.iHeight=aReader.ReadInt32();
    Construct();
    ConstructL();
    }

EXPORT_C void CEikProgressInfo::SetLayout(const SLayout& aLayout)
    {
    iLayout=aLayout;
    }

EXPORT_C void CEikProgressInfo::SetBorder(const TGulBorder& aBorder)
    {
    iBorder=aBorder;
    }

void CEikProgressInfo::CheckSizeCalculated()
    {
    if (!iLayout.iFont)
        iLayout.iFont=iCoeEnv->NormalFont();
    if (iSize.iWidth)
        return;
    if (!iHeightWasSupplied)
        iInfo.iHeight=iLayout.iFont->HeightInPixels()+1;
    const TSize margins=iBorder.SizeDelta();
    iSize.SetSize(iInfo.iWidth+margins.iWidth,iInfo.iHeight+margins.iHeight);
    }

EXPORT_C void CEikProgressInfo::SetFinalValue(TInt aFinalValue)
    {
    iInfo.iFinalValue=aFinalValue? aFinalValue : 1;
    }

EXPORT_C void CEikProgressInfo::SizeChanged()
    {
    const TSize margins=iBorder.SizeDelta();
    iInfo.iWidth=iSize.iWidth-margins.iWidth;
    iInfo.iHeight=iSize.iHeight-margins.iHeight;
   
   SetBitmapSizes();

    AknsUtils::RegisterControlPosition(this);
    }

EXPORT_C TSize CEikProgressInfo::MinimumSize()
    {
    if (!iLayout.iFont)
        iLayout.iFont=iCoeEnv->NormalFont();
    if (!iHeightWasSupplied)
        iInfo.iHeight=iLayout.iFont->HeightInPixels()+1;
    const TSize margins=iBorder.SizeDelta();
    return TSize(iInfo.iWidth+margins.iWidth,iInfo.iHeight+margins.iHeight);
    }

EXPORT_C void CEikProgressInfo::ActivateL()
    {
    CheckSizeCalculated();
    CCoeControl::ActivateL();
    SetBitmapSizes();
    }

// AKNLAF start
EXPORT_C void CEikProgressInfo::Draw(const TRect& /*aRect*/) const
    {                                       
    CWindowGc& gc = SystemGc();           
    DrawProgressBarForeground(gc);
    DrawProgressBarBackground(gc);
    }        

void CEikProgressInfo::DrawPartial() const
    {
    ActivateGc();
    DrawProgressBarForeground(SystemGc());
    DeactivateGc();
    }

TInt CEikProgressInfo::FilledWidth() const
    {
    const TInt64 infoWidth = iInfo.iWidth;
    const TInt64 currentValue = iCurrentValue;
    const TInt64 width = infoWidth * currentValue / iInfo.iFinalValue;
    return I64LOW(width);
    }

void CEikProgressInfo::DrawProgressBarForeground(CWindowGc& aGc) const
    {
    if (!iBitmap)
        {
        return;
        }
        
    TRect visibleRect = TRect( 0, 0, FilledWidth(), iInfo.iHeight );
    
    if (iBitmapMask)
        {
        aGc.BitBltMasked(TPoint(iPosition.iX, iPosition.iY), iBitmap, visibleRect, iBitmapMask, EFalse);
        }
    else
        {
        aGc.BitBlt(TPoint(iPosition.iX, iPosition.iY), iBitmap, visibleRect);
        }      
    }

void CEikProgressInfo::DrawProgressBarBackground(CWindowGc& aGc) const
    {
    if (!iExtension)
        {
        return;
        }
        
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TRect backgroundFrameRect = TRect( 0, 0, iInfo.iWidth, iInfo.iHeight );    

    TInt filledWidth = FilledWidth();
    TRect backRedrawRect(TPoint(iPosition.iX + filledWidth, iPosition.iY), TSize(backgroundFrameRect.Width() - filledWidth, backgroundFrameRect.Height()));
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, aGc, backRedrawRect );

    aGc.BitBltMasked( TPoint( iPosition.iX, iPosition.iY ),
        iExtension->iFrameLeft,
        TRect( iExtension->iFrameLeft->SizeInPixels() ),
        iExtension->iFrameLeftMask,
        EFalse);
                                
    aGc.BitBltMasked( TPoint( iPosition.iX + iExtension->iFrameLeft->SizeInPixels().iWidth, 
        iPosition.iY), iExtension->iFrameCenter,
        TRect( iExtension->iFrameCenter->SizeInPixels() ),
        iExtension->iFrameCenterMask, EFalse);

    aGc.BitBltMasked( TPoint( iPosition.iX + iExtension->iFrameLeft->SizeInPixels().iWidth +
        iExtension->iFrameCenter->SizeInPixels().iWidth, 
        iPosition.iY), iExtension->iFrameRight,
        TRect( iExtension->iFrameRight->SizeInPixels() ),
        iExtension->iFrameRightMask, EFalse);
    }
// AKNLAF end


EXPORT_C const TDesC* CEikProgressInfo::EvaluateText(TDes& aTextBuf) const
    {
    if (!iInfo.iTextType)
        return(NULL);
    _LIT(KTextPercent,"%3d%%");
    _LIT(KOver,"%c");
    if (iInfo.iTextType==EEikProgressTextPercentage)
        aTextBuf.Format(KTextPercent,iCurrentValue*100/iInfo.iFinalValue);
    else
        aTextBuf.Format(KOver,iCurrentValue,iInfo.iFinalValue);
    // Support for arabic indic digits:
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion(aTextBuf);
    return(&aTextBuf); // subclassers may wish to use their own buffer
    }

EXPORT_C void CEikProgressInfo::SetAndDraw(TInt aValue)
    {
    if (aValue < 0)
        aValue = 0;
    else if (aValue > iInfo.iFinalValue)
    {
        //aValue = iInfo.iFinalValue;   
        //no need for redrawing
        return;
    }
    
    if(iCurrentValue != aValue)
        {
        TInt oldWidth =  FilledWidth();
        iCurrentValue = aValue;    
        if( FilledWidth() != oldWidth )
            {
            DrawNow();
            }
        }
    }

EXPORT_C void CEikProgressInfo::IncrementAndDraw(TInt aInc)
    {
    SetAndDraw(iCurrentValue+aInc);
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U
 */
EXPORT_C void CEikProgressInfo::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikBorderedControl::GetColorUseListL(aColorUseList);

    TInt commonAttributes = TCoeColorUse::EContents|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
    TCoeColorUse colorUse;

    colorUse.SetLogicalColor(EColorControlText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlHighlightText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EHighlights|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlBackground);
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlHighlightBackground);
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EHighlights|commonAttributes);
    aColorUseList.AppendL(colorUse);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U
 */
EXPORT_C void CEikProgressInfo::HandleResourceChange(TInt aType)
    {
    if (aType == KAknsMessageSkinChange)
        {
        //load the new skin graphics
        DeleteBitmaps();
        TRAP_IGNORE(LoadBitmapsL());
        SetBitmapSizes();
        }
    
    CEikBorderedControl::HandleResourceChange(aType);
    }

// from CCoeControl
/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikProgressInfo::WriteInternalStateL(RWriteStream&) const
    {}
#else
EXPORT_C void CEikProgressInfo::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CEikBorderedControl::WriteInternalStateL(aWriteStream);
    }
#endif

EXPORT_C void CEikProgressInfo::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikBorderedControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikProgressInfo::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikProgressInfo::Reserved_2()
    {
    }

void CEikProgressInfo::LoadBitmapsL()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    AknsUtils::CreateIconL( skin, KAknsIIDQgnGrafBarProgress,
            iBitmap, iBitmapMask, KAvkonBitmapFile,
            EMbmAvkonQgn_graf_bar_progress,
            EMbmAvkonQgn_graf_bar_progress_mask );

    // Preserve icon data to improve performance, because the icon is subsequently
    // scaled to different sizes. No need to call DestroyIconData in this case.
    // It is done automatically, when iBitmap is deleted.
    AknIconUtils::PreserveIconData( iBitmap );

    if ( iExtension )
        {
        // Load the three frame icons and assign a proper size to them.
        AknsUtils::CreateIconL( skin, KAknsIIDQgnGrafBarFrameSideL,
            iExtension->iFrameLeft, iExtension->iFrameLeftMask, KAvkonBitmapFile,
            EMbmAvkonQgn_graf_bar_frame_side_l,
            EMbmAvkonQgn_graf_bar_frame_side_l_mask );

	    AknsUtils::CreateIconL( skin, KAknsIIDQgnGrafBarFrameCenter,
            iExtension->iFrameCenter, iExtension->iFrameCenterMask, KAvkonBitmapFile,
            EMbmAvkonQgn_graf_bar_frame_center,
            EMbmAvkonQgn_graf_bar_frame_center_mask );

	    AknsUtils::CreateIconL( skin, KAknsIIDQgnGrafBarFrameSideR,
            iExtension->iFrameRight, iExtension->iFrameRightMask, KAvkonBitmapFile,
            EMbmAvkonQgn_graf_bar_frame_side_r,
            EMbmAvkonQgn_graf_bar_frame_side_r_mask );
        }
    }

void CEikProgressInfo::SetBitmapSizes()
    { 
    TRect barRect ( TSize ( iInfo.iWidth, iInfo.iHeight ) );
    AknIconUtils::SetSize( iBitmap, barRect.Size(), EAspectRatioNotPreserved );
        
    if ( iExtension )
        {
        TAknLayoutRect frameLayout;
        frameLayout.LayoutRect( barRect, AknLayoutScalable_Avkon::wait_border_pane_g1() );
        AknIconUtils::SetSize( iExtension->iFrameLeft, frameLayout.Rect().Size(), EAspectRatioNotPreserved );
        frameLayout.LayoutRect( barRect, AknLayoutScalable_Avkon::wait_border_pane_g2() );
        AknIconUtils::SetSize( iExtension->iFrameCenter, frameLayout.Rect().Size(), EAspectRatioNotPreserved );
        frameLayout.LayoutRect( barRect, AknLayoutScalable_Avkon::wait_border_pane_g3() );
        AknIconUtils::SetSize( iExtension->iFrameRight, frameLayout.Rect().Size(), EAspectRatioNotPreserved );
        }    
    }

void CEikProgressInfo::DeleteBitmaps()
    {
    //delete iBackgroundBitmapMask; // AKNLAF
    //iBackgroundBitmapMask = NULL;
	if (iExtension)
		iExtension->DeleteBitmaps();
    delete iBackgroundBitmap; // AKNLAF
    iBackgroundBitmap = NULL;
	delete iBitmap; // AKNLAF
    iBitmap = NULL;
    delete iBitmapMask;
    iBitmapMask = NULL;
    }
