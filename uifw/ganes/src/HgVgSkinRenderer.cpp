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

#include "HgVgSkinRenderer.h"
#include "HgVgHelper.h"
#include "HgVgDrawBuffer.h"

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
// CHgVgSkinRenderer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgSkinRenderer* CHgVgSkinRenderer::NewL(const TRect& aRect)
    {
    CHgVgSkinRenderer* self = new ( ELeave ) CHgVgSkinRenderer(aRect);
    CleanupStack::PushL (self );
    self->ConstructL();
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgSkinRenderer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgSkinRenderer::ConstructL ()
    {
        
    iDrawBuffer = CHgVgDrawBuffer::NewL( TSize(iRect.Width(), iRect.Height()), EColor64K );

    
    }

// -----------------------------------------------------------------------------
// CHgVgSkinRenderer::CHgVgSkinRenderer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgSkinRenderer::CHgVgSkinRenderer(const TRect& aRect) : iRect(aRect)
    {
    
    }
        
// -----------------------------------------------------------------------------
// CHgVgSkinRenderer::~CHgVgSkinRenderer()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgSkinRenderer::~CHgVgSkinRenderer ( )
    {

    delete iDrawBuffer;
    
    vgDestroyImage(iSkinImage);

    }

// -----------------------------------------------------------------------------
// CHgVgSkinRenderer::UpdateSkin()
// Updates skin image.
// -----------------------------------------------------------------------------
//
void CHgVgSkinRenderer::UpdateSkinL(const MObjectProvider* aProvider, 
        const CCoeControl* aControl)
    {
    // render skin to draw buffer
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( aProvider );
    AknsDrawUtils::DrawBackground( skin, cc, aControl, iDrawBuffer->Gc(), TPoint(0,0), 
            aControl->Rect(), KAknsDrawParamDefault );

    // destroy old vg image
    if (iSkinImage != VG_INVALID_HANDLE)
        {
        vgDestroyImage(iSkinImage);
        iSkinImage = VG_INVALID_HANDLE;
        }

    // create new image for the skin
    iSkinImage = vgCreateImage(VG_sRGB_565, 
            iRect.Width(), iRect.Height(), 
            VG_IMAGE_QUALITY_NONANTIALIASED);
    
    // handle out of memory
    if( iSkinImage == VG_INVALID_HANDLE )
        {
        User::Leave(KErrNoMemory);
        }
            
    // Copy to draw buffer to vg image
    iDrawBuffer->GetDrawBufferToVgImage(TRect(TPoint(0,0), TPoint(iRect.Width(), iRect.Height())), 
            TPoint(0,0), iSkinImage, VG_sRGB_565);    
    }

void CHgVgSkinRenderer::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    }

// -----------------------------------------------------------------------------
// CHgVgSkinRenderer::Draw
// Draws skin.
// -----------------------------------------------------------------------------
//
void CHgVgSkinRenderer::Draw() const
    {
    HgVgHelper::DrawImage(iSkinImage, TPoint(0, 0), iRect, EFalse, iLandscape);
    }

void CHgVgSkinRenderer::EnableLanscapeRendering(TBool aLandscape)
{
    iLandscape = aLandscape;
}


// End of File
