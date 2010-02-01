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
#ifndef AKNEXTENDEDFADER_H__
#define AKNEXTENDEDFADER_H__

#include <graphics/wsplugin.h> // For window server plugin interface

#include "AknExtendedFaderStartupWatcher.h"
#include "AknExtendedFaderColorSchemeWatcher.h"

class CFbsDrawDevice;
class MWsGraphicDrawerEnvironment;

    
class CAknExtendedFader : public CWsPlugin, 
                          public MWsFader, 
                          public MAknExtendedFaderStartupObserver,
                          public MAknExtendedFaderColorSchemeObserver
	{
	friend class CFbsDevice;
	
public:
	enum { EImplUid = 0x2001B299 };
	
public:
	static CAknExtendedFader* CreateL();
	~CAknExtendedFader();
	void ConstructL(MWsGraphicDrawerEnvironment& aEnv,const TDesC8& aData);
	const TDesC& PluginName() const;

private: // Own implementation
	CAknExtendedFader();
	
	TBool DoFastFading(CFbsBitGc* aBitGc, const TRegion * aRegion);
	TBool DoFastFading16MX(CFbsDrawDevice* aDrawDevice, const TRegion * aRegion);
	TBool DoFastFading64K(CFbsDrawDevice* aDrawDevice, const TRegion * aRegion);	
	
protected: // from MWsObjectProvider
	TAny* ResolveObjectInterface(TUint aTypeId);

	
protected: // from MWsFader
	void SetFadingParameters(const TDesC8& aData);
	void FadeArea(CFbsBitGc* aBitGc,const TRegion * aRegion);

	
protected: // MAknExtendedFaderStartupObserver
	void GlobalSystemStateChangedL(TPSGlobalSystemState aState);


protected: // MAknExtendedFaderColorChangeObserver
	void ColorSchemeChanged(const TUint32& aNewColor, const TUint8& aNewBlackMap, const TUint8& aNewWhiteMap);
	
	
private:
	CAknExtendedFaderStartupWatcher* iStartupWatcher;
	CAknExtendedFaderColorSchemeWatcher* iColorSchemeWatcher;
	
	TUint32 iColorOverlayR, iColorOverlayG, iColorOverlayB;
	TUint8 iBlackMap, iWhiteMap;
	};

#endif //__CFADER_H__
