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

#include "HgVgImageCreator.h"
#include "HgVgEGL.h"

#include <e32math.h>
#include <gulicon.h>
#include <fbs.h>
#include <nvg.h>
#include <AknIconHeader.h>
#include <AknIconUtils.h>


static const TUid KUidMySingleton = { 0x100000E9 };


static TAknIconHeader GetNvgIconHeader(HBufC8* aNVGData)
    {
    // Parse the icon header info from the extended data
    TPtr8 IconHeaderPtr((TUint8*)aNVGData->Des().Ptr(), KIconHeaderLength, KIconHeaderLength);
    TAknIconHeader iconheader(IconHeaderPtr);
    
    return iconheader;
    }
    
static TPtr8 GetNvgDataWithoutHeader(HBufC8* aNVGData)
    {
    // The rest of the data (after the iconheader) are the OVG drawing instructions
    TInt lengthAfterHeader = aNVGData->Length() - KIconHeaderLength;
    TPtr8 nvgDataVoidIC((TUint8 *)aNVGData->Des().Ptr() + KIconHeaderLength, lengthAfterHeader, lengthAfterHeader);
    
    return nvgDataVoidIC;
    }

static HBufC8* ReadNVGDataL(const CFbsBitmap& aBitmap)
    {
    // Fetch the extended data
    aBitmap.BeginDataAccess();
    const TUint32* data = aBitmap.DataAddress();
    TInt dataSize = aBitmap.DataSize();
    TUint8* compressedData = new (ELeave) TUint8[dataSize];
    CleanupStack::PushL(compressedData);
    Mem::Copy(compressedData, data, dataSize);
    aBitmap.EndDataAccess(ETrue);
    
    // Create a descriptor out of the extended bitmap data. The iNVGData
    // will now contain the direct OpenVG commands
    TPtr8 nvgDataPtr(compressedData, dataSize, dataSize);
    HBufC8* dataBuf = nvgDataPtr.AllocL();
    
    CleanupStack::PopAndDestroy(compressedData);
    return dataBuf;
    }

VGImage CHgVgImageCreator::RenderImageFromIconL( const CFbsBitmap* aBitmap )
    {
    User::LeaveIfNull(aBitmap);
    User::LeaveIfNull(iEGL);
        
    HBufC8* nvgData = ReadNVGDataL(*aBitmap);

    TSize size = aBitmap->SizeInPixels();

    VGImage image = vgCreateImage(VG_sARGB_8888_PRE, size.iWidth, size.iHeight,VG_IMAGE_QUALITY_NONANTIALIASED);
    
    const EGLint    KColorAttribList[] =
            {
            EGL_NONE
            };

    CNvgEngine* nvgEngine = CNvgEngine::NewL();
    CleanupStack::PushL(nvgEngine);
    
    EGLSurface newSurface = eglCreatePbufferFromClientBuffer(
        iEGL->Display(), EGL_OPENVG_IMAGE,
        static_cast<EGLClientBuffer>(image),    // Use the image as buffer
        iEGL->CurrentConfig(), KColorAttribList );
    
    eglMakeCurrent( iEGL->Display(), newSurface, newSurface, iEGL->Context() );
    
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();    
    vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
    vgSeti( VG_SCISSORING, VG_FALSE );
    

    TAknIconHeader iconheader = GetNvgIconHeader(nvgData);        
    // Set preserve aspect ratio according to the header info
    TNvgAlignStatusType alignTypeValue = ENvgPreserveAspectRatio_XmidYmid;
    TNvgMeetOrSliceType meetOrSliceTypeValue = ENvgMeet;
    if ( iconheader.GetScaleMode() == EAspectRatioPreserved )
        {
        
        }
    else if (iconheader.GetScaleMode() == EAspectRatioPreservedSlice)
        {
        meetOrSliceTypeValue = ENvgSlice;
        }
    else if (iconheader.GetScaleMode() == EAspectRatioPreservedAndUnusedSpaceRemoved || 
            iconheader.GetScaleMode() == EAspectRatioNotPreserved )
        {
        alignTypeValue = ENvgPreserveAspectRatio_None;
        }

    nvgEngine->SetPreserveAspectRatio(alignTypeValue, meetOrSliceTypeValue);
    nvgEngine->Rotate(iconheader.GetRotation(),size.iWidth >>1, size.iHeight >>1);
    
    nvgEngine->DrawNvg(GetNvgDataWithoutHeader(nvgData), size, NULL, NULL);
        
    // TODO: Error handling. DrawNvg mey fail icon rendering.
    
    delete nvgData;

    CleanupStack::PopAndDestroy(nvgEngine);
    
    // TODO: should we call explicitly vgFlush at this point to force all commands
    // complete before eglMakeCurrent?
    
    eglMakeCurrent(iEGL->Display(), iEGL->Surface(), iEGL->Surface(), iEGL->Context());
        
    if ( newSurface != EGL_NO_SURFACE )
        {
        eglDestroySurface( iEGL->Display(), newSurface );
        }

    // reset states, and matrices which nvg lefts dirty.    
    vgSeti( VG_BLEND_MODE, VG_BLEND_SRC_OVER );
    vgSeti( VG_SCISSORING, VG_FALSE );
    vgSeti( VG_MASKING, VG_FALSE );
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER );
    vgLoadIdentity();
    vgSeti( VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER );
    vgLoadIdentity();
    
    return image;

    }

CHgVgImageCreator* CHgVgImageCreator::InstanceL()
    {
    CHgVgImageCreator* instance = static_cast<CHgVgImageCreator*>( CCoeEnv::Static( KUidMySingleton ) );
    
    if ( !instance )
        {
        instance = new ( ELeave ) CHgVgImageCreator;
        CleanupStack::PushL( instance );
        instance->ConstructL();
        CleanupStack::Pop();
        }
    
    return instance;
    }

    
CHgVgImageCreator::CHgVgImageCreator() : CCoeStatic( KUidMySingleton )
     {
     }

CHgVgImageCreator::~CHgVgImageCreator()
    {
    //delete iNvgEngine;
    }

void CHgVgImageCreator::ConstructL()
    {
    //iNvgEngine = CNvgEngine::NewL();
    }
    
void CHgVgImageCreator::Initialize(CHgVgEGL* aEGL)
    {
    iEGL = aEGL;
    }

// End of File
