/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
#include <bitdev.h>
#include <eikenv.h>
#include <eikspane.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>

#include "AknIndicatorFader.h"
#include "AknIndicatorContainer.h"
#include "AknIndicator.h"


// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknIndicatorFader::CAknIndicatorFader
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknIndicatorFader::CAknIndicatorFader(TSize aSize)
    {
    iSize = aSize;
    }

// -----------------------------------------------------------------------------
// CAknIndicatorFader::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknIndicatorFader::ConstructL()
    {
    iFadedBitmap = new (ELeave) CFbsBitmap();
    iFadedBitmap->Create(iSize, EGray256);    

    iFadingBitmap = new (ELeave) CFbsBitmap();
    iFadingBitmap->Create(iSize, EGray256);
    
    iInvertingBitmap = new (ELeave) CFbsBitmap();
    iInvertingBitmap->Create(iSize, EGray2);

    iInvertedBitmap = new (ELeave) CFbsBitmap();
    iInvertedBitmap->Create(iSize, EGray2);
  
    InitializeL();

    SetActiveFadeEffect(EEffectNone);
    }

// -----------------------------------------------------------------------------
// CAknIndicatorFader::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknIndicatorFader* CAknIndicatorFader::NewL(TSize aSize)
    {
    CAknIndicatorFader* self = 
        new (ELeave) CAknIndicatorFader(aSize);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknIndicatorFader::~CAknIndicatorFader()
    {
    delete iFadedBitmap;
    delete iFaderDevice;
    delete iFaderGc;

    delete iFadingBitmap;
    delete iFadingDevice;
    delete iFadingGc;

    delete iInvertingBitmap;
    delete iInvertingDevice;
    delete iInvertingGc;
    
    delete iInvertedBitmap;
    delete iInvertedDevice;
    delete iInvertedGc;

    }

CFbsBitmap* CAknIndicatorFader::FadeMask(CFbsBitmap* aOriginalMask) const
    {
    if (aOriginalMask &&
        iActiveEffect != EEffectNone &&
        Initialized())
        {
        CFbsBitmap* usedMask = aOriginalMask;
        TDisplayMode displayMode = aOriginalMask->DisplayMode();
        TSize size = aOriginalMask->SizeInPixels();
        TRect rect = TRect(0,0,size.iWidth, size.iHeight);       
        TRgb rgbValue = 0x00000000;        

         // If given mask is hardmask, it must inverted.            
        if (displayMode == EGray2)
            {
            // clear the area first
            iInvertedGc->SetPenStyle(CGraphicsContext::ENullPen);
            iInvertedGc->SetBrushStyle(CGraphicsContext::ESolidBrush);    
            iInvertedGc->SetBrushColor(KRgbWhite);    
            iInvertedGc->DrawRect(TRect(TPoint(0,0), iSize));

            iInvertedGc->BitBltMasked(TPoint(0,0),
                iInvertingBitmap,
                rect,
                aOriginalMask,
                EFalse); 
            usedMask = iInvertedBitmap;
            }

        rgbValue = 0x00000000;
        for (TInt x=0; x < iSize.iWidth; x++)
            {
            iFaderGc->SetPenColor(TRgb(rgbValue));
            iFaderGc->DrawLine(TPoint(x,0), TPoint(x,iSize.iHeight));
            }

        iFaderGc->BitBltMasked(TPoint(0,0),
            iFadingBitmap,
            rect,
            usedMask,
            EFalse);        

        return iFadedBitmap;
        }
    else
        {
        return aOriginalMask;
        }

    }


void CAknIndicatorFader::SetActiveFadeEffect(TInt aActiveEffect)
    {
    if (aActiveEffect == iActiveEffect)
        return;
    
    iActiveEffect = aActiveEffect;
    CreateEffect(aActiveEffect);
    }


void CAknIndicatorFader::CreateEffect(TInt aEffect)
    {
    if (!Initialized())
        return;

    switch (aEffect)
        {
        case EEffectFadeToLeft:
            {
            TInt KStartValue = 30;
            TInt KEndValue   = 90;

            TInt KMaxFadeSteps = KEndValue - KStartValue;
            TInt usedFadeStep = 0;
            
            if (iSize.iWidth < KMaxFadeSteps && 
                iSize.iWidth != 0)
                {
                usedFadeStep = KMaxFadeSteps/iSize.iWidth;
                }
            else
                {
                usedFadeStep = iSize.iWidth/KMaxFadeSteps;
                }

            TRgb rgb;
            rgb.SetRed(KStartValue);
            rgb.SetGreen(KStartValue);
            rgb.SetBlue(KStartValue);
            
            for (TInt x=0; x < iSize.iWidth;x++)
                {
                iFadingGc->SetPenColor(rgb);
                iFadingGc->DrawLine(TPoint(x,0), TPoint(x,iSize.iHeight));
                rgb.SetRed(rgb.Red() + usedFadeStep);
                rgb.SetGreen(rgb.Green() + usedFadeStep);
                rgb.SetBlue(rgb.Blue() + usedFadeStep);
                }
            
            break;
            }

        case EEffectFadeToRight:
            {
            TInt KStartValue = 30;
            TInt KEndValue   = 90;

            TInt KMaxFadeSteps = KEndValue - KStartValue;
            TInt usedFadeStep = 0;
            
            if (iSize.iWidth < KMaxFadeSteps && 
                iSize.iWidth != 0)
                {
                usedFadeStep = KMaxFadeSteps/iSize.iWidth;
                }
            else
                {
                usedFadeStep = iSize.iWidth/KMaxFadeSteps;
                }

            TRgb rgb;
            rgb.SetRed(KStartValue);
            rgb.SetGreen(KStartValue);
            rgb.SetBlue(KStartValue);

            for (TInt x=iSize.iWidth - 1; x >= 0;x--)
                {
                iFadingGc->SetPenColor(rgb);
                iFadingGc->DrawLine(TPoint(x,0), TPoint(x,iSize.iHeight));
                rgb.SetRed(rgb.Red() + usedFadeStep);
                rgb.SetGreen(rgb.Green() + usedFadeStep);
                rgb.SetBlue(rgb.Blue() + usedFadeStep);
                }
            break;
            }
        case EEffectNone:
        default:
            {
            break;
            }
        }

    }


void CAknIndicatorFader::SetActiveFadeSize(TSize aSize)
    {
    if (aSize == iSize)
        return;

    iSize = aSize;
    TRAP_IGNORE(InitializeL());
    CreateEffect(iActiveEffect);
    }

void CAknIndicatorFader::InitializeL()
    {
    iFadedBitmap->Resize(iSize);
    iFadingBitmap->Resize(iSize);
    iInvertingBitmap->Resize(iSize);
    iInvertedBitmap->Resize(iSize);    

    delete iFaderDevice;
    iFaderDevice = NULL;
    delete iFaderGc;
    iFaderGc = NULL;
    iFaderDevice = CFbsBitmapDevice::NewL( iFadedBitmap );
    iFaderDevice->CreateContext( iFaderGc );

    delete iFadingDevice; 
    iFadingDevice = NULL;
    delete iFadingGc;
    iFadingGc = NULL;
    iFadingDevice = CFbsBitmapDevice::NewL( iFadingBitmap );
    iFadingDevice->CreateContext( iFadingGc );
   
    delete iInvertingDevice;
    iInvertingDevice = NULL;
    delete iInvertingGc;
    iInvertingGc = NULL;
    iInvertingDevice = CFbsBitmapDevice::NewL( iInvertingBitmap );
    iInvertingDevice->CreateContext( iInvertingGc );
    
    delete iInvertedDevice;
    iInvertedDevice = NULL;
    delete iInvertedGc;
    iInvertedGc = NULL;
    iInvertedDevice = CFbsBitmapDevice::NewL( iInvertedBitmap );
    iInvertedDevice->CreateContext( iInvertedGc );

    if (Initialized())
        {
        iFadingGc->SetPenColor(KRgbGray);
        iFadingGc->SetPenStyle(CGraphicsContext::ESolidPen);
        iFadingGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
       
        iInvertingGc->SetPenStyle(CGraphicsContext::ENullPen);
        iInvertingGc->SetBrushStyle(CGraphicsContext::ESolidBrush);    
        iInvertingGc->SetBrushColor(KRgbBlack);    
        iInvertingGc->DrawRect(TRect(TPoint(0,0), iSize));
        }
    }

TBool CAknIndicatorFader::Initialized() const
    {
    if (iFadedBitmap &&
        iFaderDevice &&
        iFaderGc &&
        iFadingBitmap &&
        iFadingDevice &&
        iFadingGc &&
        iInvertingBitmap &&
        iInvertingDevice &&
        iInvertingGc &&
        iInvertedBitmap &&
        iInvertedDevice &&
        iInvertedGc)
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }
