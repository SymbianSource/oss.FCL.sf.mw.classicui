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

#include "HgVgLabel.h"
#include "HgVgHelper.h"
#include "HgVgDrawBuffer.h"
#include "HgDrawUtils.h"

#include <ganes.mbg>
#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <touchfeedback.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <e32math.h>
#include <gulcolor.h>

#include <AknsDrawUtils.h>


// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgTitleRenderer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgLabel* CHgVgLabel::NewL(const TRect& aRect, const TDesC& aText)
    {
    CHgVgLabel* self = new ( ELeave ) CHgVgLabel(aRect);
    CleanupStack::PushL (self );
    self->ConstructL(aText);
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgTitleRenderer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgLabel::ConstructL (const TDesC& aText)
    {
    iText = aText.AllocL();
    
    iTextRenderer = CHgVgDrawBuffer::NewL(iRect.Size(), EGray2);
        
    iTextImage = vgCreateImage(VG_A_1, 
            iRect.Width(), iRect.Height(), 
            VG_IMAGE_QUALITY_NONANTIALIASED);
    
    if (iTextImage == VG_INVALID_HANDLE)
        {
        User::Leave(KErrNoMemory);
        }
        
    // get text color from skin
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( 
                AknsUtils::SkinInstance(),
                iTextColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG6 );
        }
    
    if (iTextColor.Red() < 128)
        {
        iShadowColor = KRgbWhite;
        }
    else
        {
        iShadowColor = KRgbBlack;
        }
        
    }

// -----------------------------------------------------------------------------
// CHgVgTitleRenderer::CHgVgTitleRenderer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgLabel::CHgVgLabel(const TRect& aRect) : 
iRect(aRect),
iTextColor(KRgbDarkGray),
iShadowColor(KRgbBlack),
iDirty(ETrue)
    {
    
    }
        
// -----------------------------------------------------------------------------
// CHgVgTitleRenderer::~CHgVgTitleRenderer()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgLabel::~CHgVgLabel ( )
    {
    delete iText;
    delete iTextRenderer;    
    // then parent
    vgDestroyImage(iTextImage);
    }

// -----------------------------------------------------------------------------
// CHgVgLabel::SetText()
// -----------------------------------------------------------------------------
//
void CHgVgLabel::SetTextL(const TDesC& aText)
    {
    if (aText != *iText)
        {
        delete iText;
        iText = 0;
        iText = aText.AllocL();
        iDirty = ETrue;
        }
    }

// -----------------------------------------------------------------------------
// CHgVgLabel::Draw()
// -----------------------------------------------------------------------------
//
void CHgVgLabel::Draw(const TRect& aWindowRect, TReal aAlpha)
    {
    if (iDirty)
        {
        Update();
        iDirty = EFalse;
        }
    
    TRgb color = iTextColor;
    color.SetAlpha(255.0f * aAlpha);
    TRgb shadowColor = iShadowColor;
    shadowColor.SetAlpha(255.0f * aAlpha);

    //HgVgHelper::DrawImageColorized(iTextImage, shadowColor, iRect.iTl+TPoint(1,1), aWindowRect);    
    HgVgHelper::DrawImageColorized(iTextImage, color, iRect.iTl, aWindowRect, EFalse, iLandscape);    
    }

// -----------------------------------------------------------------------------
// CHgVgLabel::Update()
// -----------------------------------------------------------------------------
//
void CHgVgLabel::Update()
    {
    iTextRenderer->Clear(iRect.Size(), KRgbBlack);
/*    iTextRenderer->Gc().SetPenColor(KRgbWhite);    
        
    iTextRenderer->Gc().UseFont(iFont);
    iTextRenderer->Gc().DrawText(*iText, TPoint(
            iRect.Width() / 2 - iFont->TextWidthInPixels(*iText) / 2, 
            iFont->HeightInPixels()));
*/
    TAknLayoutText text;
            
    text.LayoutText(iParentRect, iLayout);
    text.DrawText(iTextRenderer->Gc(), *iText, ETrue, KRgbWhite);
    
    iTextRenderer->GetDrawBufferToVgImage(TRect(TPoint(0,0), iRect.Size()), 
            TPoint(0, 0), iTextImage, VG_A_1);    
    }


void CHgVgLabel::SetLayout(const TAknTextComponentLayout& aLayout, const TRect& aParentRect)
    {
    iLayout = aLayout;
    iLayout.Sett(0);
    iLayout.Setl(0);
    iParentRect = aParentRect;
    }

void CHgVgLabel::DrawEmptyText(const TRect& aClientRect, const TDesC& aText)
    {
    iTextRenderer->Clear(iRect.Size(), KRgbBlack);
    DrawEmptyListImpl_real(aClientRect, iTextRenderer->Gc(), aText, KRgbWhite);
    iTextRenderer->GetDrawBufferToVgImage(TRect(TPoint(0,0), iRect.Size()), 
            TPoint(0, 0), iTextImage, VG_A_1);
    iDirty = EFalse;
    Draw(aClientRect, 1.0f);
    }

void CHgVgLabel::EnableLandscapeRendering(TBool enabled)
{
    iLandscape = enabled;
}


// End of File
