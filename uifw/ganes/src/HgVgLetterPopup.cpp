/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "HgVgLetterPopup.h"
#include "HgVgDrawBuffer.h"
#include "HgVgHelper.h"
#include <VG/vgu.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>



const VGfloat KLetterStripColor[] = { 0.2f, 0.2f, 0.2f, 0.8f };
const VGfloat KLetterStripCurviness(10);


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgPopup::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgPopup* CHgVgPopup::NewL( const TRect& aRect, const CFont* aFont )
    {
    CHgVgPopup* self = new ( ELeave ) CHgVgPopup( aRect, aFont );
    CleanupStack::PushL (self );
    self->ConstructL( );
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgPopup::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgPopup::ConstructL (  )
    {
    iPrevText = ((TDesC)KNullDesC).AllocL();

    iDrawBuffer = CHgVgDrawBuffer::NewL(iRect.Size(), EGray2);

    iDrawBuffer->Gc().UseFont(iFont);
    iDrawBuffer->Gc().SetPenColor(KRgbWhite);
    iDrawBuffer->Gc().SetBrushColor(KRgbBlack);
    
    // Create VG Image to use
    iLetterImage = vgCreateImage(VG_A_1, 
            iRect.Width(), iRect.Height(), 
            VG_IMAGE_QUALITY_NONANTIALIASED);

    if( iLetterImage == VG_INVALID_HANDLE )
        {
        User::Leave(KErrNoMemory);
        }
        
    iLetterBgPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
            1.0f, 0.0f, 4, 4, (unsigned int)VG_PATH_CAPABILITY_ALL);
            
    vguRoundRect(iLetterBgPath, 0, 0, iRect.Width(), 
            iRect.Height(), KLetterStripCurviness, KLetterStripCurviness);
    
    iLetterBgPaint = vgCreatePaint();
    
    vgSetParameteri(iLetterBgPaint, VG_PAINT_TYPE, 
        VG_PAINT_TYPE_COLOR);
    
    vgSetParameterfv(iLetterBgPaint, VG_PAINT_COLOR, 4, KLetterStripColor);
    
    }

// -----------------------------------------------------------------------------
// CHgVgPopup::CHgVgPopup()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgPopup::CHgVgPopup( const TRect& aRect, const CFont* aFont) :
iRect(aRect),
iFont(aFont)
    {


    }
        
// -----------------------------------------------------------------------------
// CHgVgPopup::~CHgVgLetterStrip()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgPopup::~CHgVgPopup ( )
    {

    delete iDrawBuffer;

    delete iPrevText;
    
    vgDestroyImage(iLetterImage);
    
    vgDestroyPath(iLetterBgPath);    
    vgDestroyPaint(iLetterBgPaint);
    
    }

// -----------------------------------------------------------------------------
// CHgVgPopup::SetLetter()
// -----------------------------------------------------------------------------
//
void CHgVgPopup::SetTextL(const TDesC& aText)
    {
    User::LeaveIfNull(iPrevText);
    if (*iPrevText != aText)
        {
        delete iPrevText;
        iPrevText = 0;
        iPrevText = aText.AllocL();
        iDrawBuffer->Clear(iRect.Size(), KRgbBlack);
        
        TAknLayoutText layout;
        layout.LayoutText(iParentRect, iTextLayout);
        layout.DrawText(iDrawBuffer->Gc(), aText, ETrue, KRgbWhite);
        
/*        TInt width = iFont->TextWidthInPixels(aText);
        TInt height = iFont->HeightInPixels();
        TPoint pos(iRect.Width() / 2 - width / 2, 
                iRect.Height() / 2 + height / 2);
        iDrawBuffer->DrawText(aText, iFont, KRgbWhite, pos);*/
        iDrawBuffer->GetDrawBufferToVgImage(iRect.Size(), TPoint(0,0), iLetterImage, VG_A_1);
        }
    }

// -----------------------------------------------------------------------------
// CHgVgPopup::SetTexts()
// -----------------------------------------------------------------------------
//
void CHgVgPopup::SetTexts(const TDesC& aText1, const TDesC& aText2)
    {
    iDrawBuffer->Clear(iRect.Size(), KRgbBlack);
    TInt w1 = iFont->TextWidthInPixels(aText1);
    TInt w2 = iFont->TextWidthInPixels(aText2);
    TInt height = iFont->HeightInPixels();
    TPoint pos(iRect.Width() / 2 - w1 / 2, iRect.Height() / 2);
    iDrawBuffer->Gc().DrawText(aText1, pos);
    pos.iY += height;
    pos.iX = iRect.Width() / 2 - w2 / 2;
    iDrawBuffer->Gc().DrawText(aText2, pos);
    iDrawBuffer->GetDrawBufferToVgImage(iRect.Size(), TPoint(0,0), iLetterImage, VG_A_1);    
    }

// -----------------------------------------------------------------------------
// CHgVgPopup::Draw()
// -----------------------------------------------------------------------------
//
void CHgVgPopup::Draw(const TRect& aWindowRect, TReal aAlpha) 
    {
    
    VGfloat w = iRect.Width();
    VGfloat h = iRect.Height();
    
    TRgb color;
    AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), 
            color, 
            KAknsIIDQsnTextColors, 
            EAknsCIQsnTextColorsCG6 );
    
    TRgb bgColor(KRgbWhite);
    if (color.Blue() > 128)
        {
        bgColor = KRgbBlack;
        }

    // draw background     
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    if (iLandscape)
    {
        vgTranslate(0.0f, 640.0f); 
        vgRotate(-90.0f);        
    }
    
    vgTranslate(iRect.iTl.iX, (aWindowRect.Height() - iRect.iBr.iY));

    VGfloat bgv[4];
    bgv[0] = (VGfloat)bgColor.Red() / 255.0f;
    bgv[1] = (VGfloat)bgColor.Green() / 255.0f;
    bgv[2] = (VGfloat)bgColor.Blue() / 255.0f;    
    bgv[3] = aAlpha;
    vgSetParameterfv(iLetterBgPaint, VG_PAINT_COLOR, 4, bgv);
    
    vgSetPaint(iLetterBgPaint, VG_FILL_PATH);
    vgDrawPath(iLetterBgPath, VG_FILL_PATH);

    // draw letter
    color.SetAlpha(aAlpha * 255.0f);
    HgVgHelper::DrawImageColorized(iLetterImage, 
            color, iRect.iTl, aWindowRect, EFalse, iLandscape);
    }

void CHgVgPopup::SetLayouts(const TAknWindowComponentLayout& aPopupLayout, 
        const TAknTextComponentLayout& aTextLayout, const TRect& aParentRect)
    {
    iPopupLayout = aPopupLayout;
    iTextLayout = aTextLayout;
    iTextLayout.Setl(0);
    iTextLayout.Sett(0);
    iParentRect = aParentRect;
    }

void CHgVgPopup::EnableLanscapeRendering(TBool enabled)
{
    iLandscape = enabled;
}


// End of File
