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

#include "HgVgDrawBuffer.h"

#include <AknIconUtils.h>
#include <AknsDrawUtils.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <e32math.h>
#include <gulcolor.h>
#include <AknsDrawUtils.h>
#include <imageconversion.h> 

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgDrawBuffer* CHgVgDrawBuffer::NewL(const TSize& aBufferSize, const TDisplayMode& aMode )
    {
    CHgVgDrawBuffer* self = new ( ELeave ) CHgVgDrawBuffer();

    CleanupStack::PushL (self );
    self->ConstructL(aBufferSize, aMode);
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgDrawBuffer::ConstructL (const TSize& aBufferSize, const TDisplayMode& aMode )
    {

    // Create draw buffer
    iDrawBuffer = new (ELeave) CFbsBitmap();
    iDrawBuffer->Create(aBufferSize, aMode);
    iBufferSize = aBufferSize;

    // Create device and context for drawing
    iDevice = CFbsBitmapDevice::NewL(iDrawBuffer);
    iDevice->CreateContext(iGc);

        
    }

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::CHgVgDrawBuffer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgDrawBuffer::CHgVgDrawBuffer()
    {
    
    }
        
// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::~CHgVgDrawBuffer()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgDrawBuffer::~CHgVgDrawBuffer ( )
    {
    delete iGc; iGc = NULL;
    delete iDevice; iDevice = NULL;
    delete iDrawBuffer; iDrawBuffer = NULL;    
    }


// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::BufferSize()
// -----------------------------------------------------------------------------
//
const TSize& CHgVgDrawBuffer::BufferSize() const
{
    return iBufferSize;
}

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::Gc()
// Gets drawcontext.
// -----------------------------------------------------------------------------
//
CFbsBitGc& CHgVgDrawBuffer::Gc()
    {
    return *iGc;
    }


CFbsBitmap& CHgVgDrawBuffer::DrawBuffer()
    {
    return *iDrawBuffer;
    }

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::Clear
// Clear draw buffer to color
// -----------------------------------------------------------------------------
//
void CHgVgDrawBuffer::Clear(const TRect& aRect, 
        const TRgb& aColor)
    {
    iGc->SetBrushColor(aColor);
    iGc->Clear(aRect);
    }

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::DrawText()
// Draws text to buffer
// -----------------------------------------------------------------------------
//
void CHgVgDrawBuffer::DrawText(const TDesC& aText, const CFont* aFont, 
        const TRgb& aColor, const TPoint& aPosition)
    {
    iGc->SetPenColor(aColor);
    iGc->UseFont(aFont);
    iGc->DrawText(aText, aPosition);             
    }

// -----------------------------------------------------------------------------
// CHgVgDrawBuffer::GetDrawBufferToVgImage()
// Copies drawbuffer to vg image.
// -----------------------------------------------------------------------------
//
void CHgVgDrawBuffer::GetDrawBufferToVgImage(const TRect& aSrcRect, 
        const TPoint& aDest, VGImage destImage, VGImageFormat destFormat)
    {
    
    iDrawBuffer->BeginDataAccess();
    TInt stride = iDrawBuffer->DataStride();
    TInt sizeOfPixel = stride / iBufferSize.iWidth;
    
    TUint8* ptr = (TUint8*)iDrawBuffer->DataAddress();
    ptr += aSrcRect.iTl.iY * stride;
    ptr += aSrcRect.iTl.iX * sizeOfPixel;
        
    vgImageSubData (destImage, ptr, stride, destFormat, aDest.iX, aDest.iY, aSrcRect.Width(), 
            aSrcRect.Height());

    iDrawBuffer->EndDataAccess();
        
    
    }




// End of File
