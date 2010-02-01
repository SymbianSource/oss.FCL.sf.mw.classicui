/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNSGCC_H
#define AKNSGCC_H

#include <AknCapServerClient.h>
#include <eikenv.h>
#include <eikdef.h>
#include <AknSyncDraw.h>
#include <AknLayoutConfig.h>
class CAknAppUiBase;
class CEikStatusPane;
class CEikAppUi;

class MAknSgcStatusPaneRedrawCoordinator
	{
public:
	virtual void BlockServerStatusPaneRedrawsL() = 0;
	virtual void RedrawServerStatusPane() = 0;
private:
	IMPORT_C virtual void MAknSgcStatusPaneRedrawCoordinator_Reserved_1();
	IMPORT_C virtual void MAknSgcStatusPaneRedrawCoordinator_Reserved_2();
	};

enum TSgcMoveAppToWhere
	{
	ESgcMoveAppToForeground,
	ESgcMoveAppToBackground
	};

class CAknSgcImpl : public CBase
	{
public:
    virtual void MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere) = 0;
	};


NONSHARABLE_CLASS(CAknSgcClient) : public CCoeStatic
	{
public:
	enum EAppFlags
		{
		EFullScreen,
		ELegacyLayout,
		EOrientationSpecified,
		EOrientationLandscape
		};

public:
 	IMPORT_C static void CreateL();

	IMPORT_C static void HandleChangeL();	// for change in foreground, partial foreground, full screen, status pane, app embedding
	IMPORT_C static RAknUiServer* AknSrv();

	IMPORT_C static void SetStatusPaneRedrawCoordinator(MAknSgcStatusPaneRedrawCoordinator* aSpRedrawCoord);
	IMPORT_C static void BlockServerStatusPaneRedrawsL();
	IMPORT_C static void RedrawServerStatusPane();

	IMPORT_C static CAknDrawSynchronizer* DrawSynchronizer();

	IMPORT_C static void PrepareForAppExit();

	IMPORT_C static void SetSystemFaded(TBool aFade);
	IMPORT_C static TBool IsSystemFaded();

	IMPORT_C static TPixelsTwipsAndRotation PixelsAndRotation();		// for local app
	IMPORT_C static TPixelsTwipsAndRotation CalculatePixelsAndRotation(TBool aFullScreen, TBool aLegacyApp, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape);
	IMPORT_C static CAknLayoutConfig::TScreenMode ScreenMode();		// for local app
	IMPORT_C static CAknLayoutConfig::TScreenMode CalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape);
	IMPORT_C static CAknLayoutConfig::TScreenMode CalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode);

    IMPORT_C static void SetKeyBlockMode(TAknKeySoundOpcode aMode);
    IMPORT_C static void SetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate);
    /** 
    * Returns resource id of currently active statuspane. If current environment does not contain
    * statuspane, resource id is fecthed from akncapserver. Returns zero on error.
    */ 
    IMPORT_C static TInt CurrentStatuspaneResource();
    
    IMPORT_C static CAknLayoutConfig& LayoutConfig();
    IMPORT_C static const TDesC8& LayoutConfigBuf();
    
    IMPORT_C static void MoveApp(TInt aAppWindowGroupId, TSgcMoveAppToWhere aWhere);
	IMPORT_C static void SetImpl(CAknSgcImpl* aImpl);

	// internal
    static void RelinquishPriorityToForegroundAppLC(TBool aIsForeground);

protected:
	CAknSgcClient();
	~CAknSgcClient();
	void BaseConstructL();

private:
	inline static CAknSgcClient* Static();
	virtual void ConstructL();

	void DoHandleChangeL();

	CEikStatusPane* StatusPane(CEikAppUi* aAppUi);
	void SetAppUiForegroundL(CAknAppUiBase* aAppUi, TBool aForeground);
	void SetAppUiPartialFgL(CAknAppUiBase* aAppUi, TBool aPartialFg);

	void SimulateWsEventL(CEikAppUi* aAppUi, TInt aEventId);

	static void ClearHandlingChangeFlag(TAny* aThis);

	void DoPrepareForAppExit();

	void DoSetSystemFaded(TBool aFade);
	TBool DoIsSystemFaded() const;

	void SetLegacyOrientationAndScreenModeAppUiFlags(TBitFlags& aAppFlags, TInt& aScreenMode, CAknAppUiBase* aAppUi);

	TPixelsTwipsAndRotation DoCalculatePixelsAndRotation(TBool aFullScreen, TBool aLegacyApp, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode);
	CAknLayoutConfig::TScreenMode DoCalculateScreenMode(TBool aFullScreen, TBool aAppOrientationSpecified, TBool aAppOrientationLandscape, TInt aAppScreenMode);

    void DoSetKeyBlockMode(TAknKeySoundOpcode aMode);
    void DoSetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate);
    TInt DoAskCurrentStatuspaneResource();

    void DoRelinquishPriorityToForegroundAppLC(TBool aIsForeground);
    virtual const TDesC8& DoLayoutConfigBuf();

	void StartupBlankL();
	static TInt StartupUnblank(TAny* aThis);
	void DoStartupUnblank();

protected:
	TBitFlags iFlags;
	CAknLayoutConfig* iLayoutConfig;
private:
	CCoeEnv* iCoeEnv;
	RAknUiServer iAknSrv;
	TInt iSpLayout;
	TInt iSpFlags;
	TBitFlags iAppFlags;
	MAknSgcStatusPaneRedrawCoordinator* iSpRedrawCoord;
	CAknDrawSynchronizer* iDrawSync;
	CIdle *iStartupBlank;
	TInt iAppScreenMode;
	CAknSgcImpl* iImpl;
	};



#endif

// End of File
