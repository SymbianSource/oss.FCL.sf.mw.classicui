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
#define GRAPHICS_BUILD_WSERV2 1

#include <e32std.h>
#include <bitdev.h>
#include <bitdraw.h>
#include <bitdrawinterfaceid.h>
#include <bmalphablend.h>

#include "AknExtendedFaderImpl.h"
#include "AknExtendedFaderGfx.h"
#include "AknExtendedFaderTraces.h"


_LIT(KAknExtendedFaderName, "AknExtendedFader");


class CHelperFbsDevice : public CFbsBitmapDevice
{
public:
	CFbsDrawDevice* DrawDevice() { return iDrawDevice; }
};

CAknExtendedFader* CAknExtendedFader::CreateL()
	{
	TRACE("CAknExtendedFader::CreateL");
	return new (ELeave) CAknExtendedFader;
	}
	
void CAknExtendedFader::ConstructL(MWsGraphicDrawerEnvironment& aEnv,const TDesC8& /*aData*/)
	{
	TRACE("CAknExtendedFader::ConstructL >>");
	
	BaseConstructL(aEnv);
	
	// Start P&S watchers
	//iStartupWatcher = CAknExtendedFaderStartupWatcher::NewL(*this);  <-- Can be added if needs to watch startup, but probably not needed
	iColorSchemeWatcher = CAknExtendedFaderColorSchemeWatcher::NewL(*this);
	
	TRACE("CAknExtendedFader::ConstructL <<");
	}

// By default do white fader
CAknExtendedFader::CAknExtendedFader() : 
	iColorOverlayR(0xFF), iColorOverlayG(0x00), iColorOverlayB(0x00),
  	iBlackMap(16), iWhiteMap(140)
	{
	}
	
CAknExtendedFader::~CAknExtendedFader()
	{
	TRACE("CAknExtendedFader::~CAknExtendedFader");
	
	delete iStartupWatcher; iStartupWatcher = 0;
	delete iColorSchemeWatcher; iColorSchemeWatcher = 0;
	
	TRACE("CAknExtendedFader::~CAknExtendedFader <<");
	}

TBool CAknExtendedFader::DoFastFading(CFbsBitGc* aBitGc, const TRegion * aRegion)
	{
	TRACE("CAknExtendedFader::DoFastFading >>");
	
	// Get the drawdevice
	CHelperFbsDevice* device = static_cast<CHelperFbsDevice*>(aBitGc->Device());
	if(!device)
		{
		TRACE("CAknExtendedFader::DoFastFading: !device");
		return EFalse;
		}
	
	CFbsDrawDevice* drawDevice = device->DrawDevice();
	if(!drawDevice)
		{
		TRACE("CAknExtendedFader::DoFastFading: !drawDevice");
		return EFalse;
		}
	
	device->DrawingBegin();
	
	// Display mode
	TDisplayMode displayMode = drawDevice->DisplayMode();
	TRACE1("CAknExtendedFader::DoFastFading: display mode = %d", displayMode);
	
	TBool ret = EFalse;
	switch(displayMode)
		{
		case EColor64K:
			ret = DoFastFading64K(drawDevice, aRegion);
			break;
			
		case EColor16MU:
			// fall-through
			
		case EColor16MA:
			ret = DoFastFading16MX(drawDevice, aRegion);
			break;
			
		default:
			// Other modes not supported
			ret = EFalse;
			break;
		}
	
	device->DrawingEnd();
	
	TRACE("CAknExtendedFader::DoFastFading <<");
	return ret;
	}
	
TBool CAknExtendedFader::DoFastFading16MX(CFbsDrawDevice* aDrawDevice, const TRegion * aRegion)
	{
	// Do fast fading for 32-bit graphics
	TRACE("CAknExtendedFader::DoFastFading16MX >>");	
	
	TAny* ptr = NULL;
	TInt ret = aDrawDevice->GetInterface(KFastBlit2InterfaceID, ptr);
	if(ret!=KErrNone)
		{
		// We need to get the fastblit2 interface to access the image data
		TRACE("CAknExtendedFader::DoFastFading16MX: !fastblit2");
		return EFalse;
		}
	
	MFastBlit2* interface = static_cast<MFastBlit2*>(ptr);
		
	TUint32* dataAddress = const_cast<TUint32*>(interface->Bits());
	if(!dataAddress)
		{
		TRACE("CAknExtendedFader::DoFastFading16MX: !dataAddress");
		return EFalse;
		}

	// Image width often != scanline length
	TSize size(aDrawDevice->SizeInPixels());
	TInt strideInPixels = aDrawDevice->ScanLineBytes() >> 2;

	TInt rectCount = aRegion->Count();
	
	TInt fadeMapFactor = iWhiteMap - iBlackMap;
	TInt fadeMapOffset = iBlackMap;

	for(TInt i=0; i<rectCount; i++)
		{
		const TRect& rect((*aRegion)[i]);
		
		TRACE5("CAknExtendedFader::DoFastFading16MX: rect %d = %d.%d -> %d.%d", i+1, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY);

		TAknExtendedFaderGfx::FadeRect_GrayColorize_16MX(dataAddress, strideInPixels, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY, fadeMapFactor, fadeMapOffset, iColorOverlayR, iColorOverlayG, iColorOverlayB);
		
		// Ensure screen device is informed of area to update
		aDrawDevice->UpdateRegion(rect);
		}

	TRACE("CAknExtendedFader::DoFastFading16MX <<");	
	return ETrue;
	}

TBool CAknExtendedFader::DoFastFading64K(CFbsDrawDevice* aDrawDevice, const TRegion * aRegion)
	{
	// Do fast fading for 16-bit graphics
	TRACE("CAknExtendedFader::DoFastFading64K >>");	
	
	TAny* ptr = NULL;
	TInt ret = aDrawDevice->GetInterface(KFastBlit2InterfaceID, ptr);
	if(ret!=KErrNone)
		{
		// We need to get the fastblit2 interface to access the image data
		TRACE("CAknExtendedFader::DoFastFading64K: !fastblit2");
		return EFalse;
		}
	
	MFastBlit2* interface = static_cast<MFastBlit2*>(ptr);
		
	TUint32* dataAddress = const_cast<TUint32*>(interface->Bits());
	if(!dataAddress)
		{
		TRACE("CAknExtendedFader::DoFastFading64K: !dataAddress");
		return EFalse;
		}

	// Image width often != scanline length
	TSize size(aDrawDevice->SizeInPixels());
	TInt strideInPixels = aDrawDevice->ScanLineBytes() >> 1;

	TInt rectCount = aRegion->Count();
	
	TInt fadeMapFactor = iWhiteMap - iBlackMap;
	TInt fadeMapOffset = iBlackMap;

	for(TInt i=0; i<rectCount; i++)
		{
		const TRect& rect((*aRegion)[i]);
		
		TRACE5("CAknExtendedFader::DoFastFading64K: rect %d = %d.%d -> %d.%d", i+1, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY);

		TAknExtendedFaderGfx::FadeRect_GrayColorize_64K((TUint16*)dataAddress, strideInPixels, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY, fadeMapFactor, fadeMapOffset, iColorOverlayR, iColorOverlayG, iColorOverlayB);

		// Ensure screen device is informed of area to update
		aDrawDevice->UpdateRegion(rect);
		}

	TRACE("CAknExtendedFader::DoFastFading64K <<");	
	return ETrue;
	}

void CAknExtendedFader::FadeArea(CFbsBitGc* aBitGc,const TRegion * aRegion)
	{
	if(!aBitGc || !aRegion)
		{
		return;
		}

	TRACE("CAknExtendedFader::FadeArea >>");
		
	TInt rectCount = aRegion->Count();
	if(!rectCount)
		{
		// Quick bailout if there is nothing to fade
		return;
		}

  	aBitGc->Reset();
	if(!DoFastFading(aBitGc, aRegion))
	{
		// For some reason fast fading was not possible (wrong display mode?), use legacy fading.
		TRACE("CAknExtendedFader::FadeArea: Do traditional fading");
	  	aBitGc->SetFadingParameters(iBlackMap,iWhiteMap);
		aBitGc->FadeArea(aRegion);
	}
		
	TRACE("CAknExtendedFader::FadeArea <<");
	}

void CAknExtendedFader::SetFadingParameters(const TDesC8& /*aData*/)
  	{
	// No implementation needed
  	}

TAny* CAknExtendedFader::ResolveObjectInterface(TUint aTypeId)
	{
	switch (aTypeId)
		{
		case MWsFader::EWsObjectInterfaceId:
			return static_cast<MWsFader*>(this);
		}

	return NULL;
	}

const TDesC& CAknExtendedFader::PluginName() const
	{
	return KAknExtendedFaderName;
	}

void CAknExtendedFader::GlobalSystemStateChangedL(TPSGlobalSystemState aState)
	{
	TRACE1("CAknExtendedFader::GlobalSystemStateChangedL: aState = %d", aState);
	}

void CAknExtendedFader::ColorSchemeChanged(const TUint32 &aNewColor, const TUint8& aNewBlackMap, const TUint8& aNewWhiteMap)
	{
	TRACE3("CAknExtendedFader::ColorSchemeChanged: aNewColor=%08X, aNewBlackMap=%08X, aNewWhiteMap=%08X", aNewColor, aNewBlackMap, aNewWhiteMap);
		
	// Save fader values
	iBlackMap = aNewBlackMap;
	iWhiteMap = aNewWhiteMap;
	
	// Save color scheme as separate R,G,B
	iColorOverlayR = (aNewColor>>16)&0xFF;
	iColorOverlayG = (aNewColor>>8)&0xFF;
	iColorOverlayB = aNewColor&0xFF;
	
	//iBlackMap = 16;
	//iWhiteMap = 140;
	
	//iColorOverlayR = 0xFF;
	//iColorOverlayG = 0x00;
	//iColorOverlayB = 0x00;
	}

