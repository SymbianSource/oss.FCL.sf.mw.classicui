// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __EIKENV_H__
#define __EIKENV_H__

#include <uikon.hrh>
#include <coemain.h>
#include <coedef.h>
#include <eikdef.h>
#include <gulalign.h>
#include <apaflrec.h>
#include <apacmdln.h>
#include <badesca.h>
#include <baerrhan.h>
#include <gulcolor.h>
#include <eikaufty.h>
#include <eikamnt.h>
#include <lafmain.h>
#include <eikvcurs.h>
#include <babitflags.h>
#include <eikpicturefactory.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikdgfty.h>
#include <eiklibry.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikfctry.h>

class CEikProcess;
class MEikInfoMsgWin;
class MEikBusyMsgWin;
class CEikAppUi;
class CEikHotKeyTable;
class CCoeControl;
class CParaFormatLayer;
class CCharFormatLayer;
class CCoeBrushAndPenContext;
class CEikCommandButton;
class CPrintSetup;
class CDictionaryStore;
class CApaWindowGroupName;
class CEikErrorIdler;
class CEikApplication;
class MEikInfoDialog;
class MEikAlertWin;
class CEikDialog;
class MEikDebugKeys;
class CEikLibrary;
class MEikAppUiFactory;
class MEikIrFactory;
class CGulIcon;
class CApaMaskedBitmap;
class CEikLogicalBorderProxy;
class CEikLafEnv;
class TLogicalFont;
class CEikPictureFactory;
class CEikEnvExtra;
class TApaApplicationFactory;
class CEikAppServer;
class CLafSystemFont;
class RApaLsSession;
class MEikCDlgDialogFactory;
class MEikPrintDialogFactory;
class MEikFileDialogFactory;
class CEikAutoMenuTitleArray;


/**
@publishedAll
@released
*/
typedef void (*TRequestDialogFunc)();

/** An environment for creating controls and utility functions for manipulating 
them. 

Every GUI application is provided with an instance of CEikonEnv 
by the framework, which can be accessed through either CEikonEnv::Static() 
or the iEikonEnv macro of CEikApplication.

@publishedAll 
@released */
class CEikonEnv : public CCoeEnv
	{
public:
	enum TErrorValidity
		{ EErrorNumValid, EErrorNumInvalid };
public: 
	// Properties
	IMPORT_C static TVersion Version();
	inline static CEikonEnv* Static();
	// Construction and destruction
	IMPORT_C ~CEikonEnv();
	IMPORT_C CEikonEnv();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	IMPORT_C void ConstructL(TBool aInitialFocusState, TInt aWindowGroupID);
	IMPORT_C void ConstructAppFromCommandLineL(const TApaApplicationFactory& aApplicationFactory, const CApaCommandLine& aCommandLine);
	IMPORT_C void ControlStackReadyL();
	IMPORT_C void DestroyEnvironment();
	//
	inline CEikAppUi* EikAppUi() const;
	inline CEikProcess* Process() const;
	// Legacy font support (see new TCoeFont and CCoeControl::ScreenFont())
	IMPORT_C const CFont* AnnotationFont() const;
	IMPORT_C const CFont* TitleFont() const;
	IMPORT_C const CFont* LegendFont() const;
	IMPORT_C const CFont* SymbolFont() const;
	IMPORT_C const CFont* DenseFont() const;
	IMPORT_C const CFont* Font(const TLogicalFont& aLogicalFont) const;
	IMPORT_C void UpdateSystemFontsL();
	// System bitmaps
	IMPORT_C const CFbsBitmap* TexturedBitmap() const;			// deprecated
	IMPORT_C const CFbsBitmap* GrayBitmap() const;				// deprecated
	IMPORT_C const CFbsBitmap* OptionBitmap() const;			// deprecated
	IMPORT_C const CFbsBitmap* HighlightedOptionBitmap() const;
	IMPORT_C const CFbsBitmap* OptionMaskBitmap() const;		// deprecated
	IMPORT_C const CFbsBitmap* Bitmap(TUid aUidBmp) const;
public:
	IMPORT_C TBool ConfirmLossOfAllChangesL() const;
	
	IMPORT_C MPictureFactory* PictureFactory() const;
	IMPORT_C MEikPictureFactory* ExtendedPictureFactory(TUid aPictureType) const;
	IMPORT_C void AddPictureFactoryL(MEikPictureFactory& aFactory);
	IMPORT_C void RemovePictureFactory(TUid aFactoryId);
	// Alert dialogs
	IMPORT_C void AlertWin(const TDesC& aMsg);
	IMPORT_C void AlertWin(const TDesC& aMsg1, const TDesC& aMsg2);
	inline const MEikAlertWin* Alert() const;
	IMPORT_C void SetAlertWin(MEikAlertWin* aAlertWin);
	// Error handling
	IMPORT_C void LeaveWithInfoMsg(TInt aResourceId,...);
	IMPORT_C void LeaveWithErrorContext(TInt aError, const TDesC& aContextText);		// deprecated
	IMPORT_C void GetErrorText(TDes& aDes,TInt aError) const;
	IMPORT_C TErrorValidity GetErrorText(TDes& aErrorText, TInt aError, TUid aAppUid) const;
	IMPORT_C TErrorValidity GetErrorTextAndTitle(TDes& aErrorText, TInt aError, TDes& aTitleText) const;
	IMPORT_C void ResolveError(TInt aError, TUid aAppUid = KNullUid) const;
	IMPORT_C void NotifyIdleErrorWhileRedrawing(TInt aError);
	IMPORT_C void NotifyIdleError(TInt aError, TInt aContextResourceId);
	IMPORT_C void HandleErrorWithContext(TInt aError,TInt aContextResourceId);
	// Info prints
	IMPORT_C void InfoMsg(const TDesC& aDes);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,const TDesC& aDes);
	IMPORT_C void InfoMsg(TInt aResourceId, ...);
	IMPORT_C void InfoMsg(TInt aResourceId, VA_LIST aList);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner, TInt aResourceId,...);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner, TInt aResourceId, VA_LIST aList);
	IMPORT_C void InfoMsgWithDuration(const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, ...);
	IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner, const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner, TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, ...);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner, TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList);
	IMPORT_C void InfoMsgCancel();
	IMPORT_C void VerboseInfoMsg(const TDesC& aDes);
	IMPORT_C void SetVerboseInfoReporting(TBool aVerbose);	// deprecated
	// Busy messages
	IMPORT_C void BusyMsgL(const TDesC& aDes);
	IMPORT_C void BusyMsgL(const TDesC& aDes, TGulAlignment aCorner);
	IMPORT_C void BusyMsgL(TInt aResourceId);
	IMPORT_C void BusyMsgL(const TDesC& aDes, TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgL(const TDesC& aDes, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgL(TInt aResourceId, TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgCancel();
	// Query dialogs
	IMPORT_C static TBool QueryWinL(const TDesC& aFirstLine, const TDesC& aSecondLine);
	IMPORT_C TBool QueryWinL(TInt aFirstLineId, TInt aSecondLineId = 0) const;
	IMPORT_C void SetQueryDialog(MEikInfoDialog* aQueryDialog);
	IMPORT_C void SetRequestQueryDialogFunc(TRequestDialogFunc aQueryDialogFunc);
	// Info dialogs
	IMPORT_C static void InfoWinL(const TDesC& aFirstLine, const TDesC& aSecondLine);
	IMPORT_C void InfoWinL(TInt aFirstLineId, TInt aSecondLineId = 0) const;
	IMPORT_C void SetInfoDialog(MEikInfoDialog* aInfoDialog);
	IMPORT_C void SetRequestInfoDialogFunc(TRequestDialogFunc aInfoDialogFunc);
	IMPORT_C void AllocInfoMsg();
	IMPORT_C void WservAllocInfoMsg();
	IMPORT_C void FservAllocInfoMsg();
	// Sound notificatons
	IMPORT_C static void Beep();	// deprecated
	// Bitmap  utilities
	IMPORT_C CWsBitmap* CreateBitmapL(const TDesC& aFileName, TInt aId);
	IMPORT_C CWsBitmap* CreateBitmapL(const TDesC& aFileName, TInt aId, TBool aShowDlgIfErr);
	IMPORT_C CGulIcon* CreateIconL(const TDesC& aFileName, TInt aBitmapId, TInt aMaskId = KErrNotFound);
	IMPORT_C static CGulIcon* CreateIconFromMaskedBitmapL(const CApaMaskedBitmap& aApaMaskedBitmap);
	// Debugging
	IMPORT_C void SetDebugKeys(MEikDebugKeys* aDebugKeys);
	// Menu utilities
	IMPORT_C void LaunchPopupMenuL(TInt aResourceId, const TPoint& aTargetPos, TPopupTargetPosType aTargetType = EPopupTargetTopLeft, const CEikHotKeyTable* aHotKeyTable = NULL);
	// Graphical effects
	IMPORT_C static void AddWindowShadow(CCoeControl* aWinArea);
	IMPORT_C RAnimDll& ClockDllL();
	// Text formatting parameters
	IMPORT_C CParaFormatLayer* SystemSingleLineParaFormatLayerL();
	IMPORT_C CParaFormatLayer* SystemParaFormatLayerL();
	IMPORT_C CCharFormatLayer* SystemCharFormatLayerL();
	IMPORT_C static CParaFormatLayer* NewDefaultSingleLineParaFormatLayerL();
	IMPORT_C static CParaFormatLayer* NewDefaultParaFormatLayerL();
	IMPORT_C static CCharFormatLayer* NewDefaultCharFormatLayerL();
  	// Control stack utilities
	IMPORT_C void AddDialogLikeControlToStackL(CCoeControl* aControl);
	IMPORT_C void AddAlertDialogLikeControlToStackL(CCoeControl* aControl);
	IMPORT_C void RemoveFromStack(CCoeControl* aControl);
	IMPORT_C void AddSleepingDialogToStackL(CCoeControl* aControl);
	IMPORT_C void AddSleepingAlertDialogToStackL(CCoeControl* aControl);
	IMPORT_C void RouseSleepingDialog(CCoeControl* aControl, TBool aRoused);
	// Text cursors
	IMPORT_C void DrawCursor(const CCoeControl* aControl, const TPoint& aPosition, TInt aWidth);
	IMPORT_C void DrawCursor(const CCoeControl* aControl, const TPoint& aPosition, TInt aWidth, TInt aAscent, TInt aHeight);
	IMPORT_C void HideCursor(const CCoeControl* aControl);
	// Virtual pointer device cursor
	IMPORT_C TEikVirtualCursor& VirtualCursor();
	// Control of the application's ordinal position
	IMPORT_C void BringForwards(TBool aForwards, TInt aPriority = ECoeWinPriorityAlwaysAtFront);
	IMPORT_C void SetAutoForwarding(TBool aAutoBringToForeground);
	// 
	IMPORT_C TPtrC KeyPressLabel(TInt aIndex) const;	// deprecated
	// Printing
	IMPORT_C CPrintSetup* NewDefaultPrintSetupL();
	IMPORT_C static void GetPrinterNamesL(CPrinterModelList* aModelNameList, CDesCArray& aPrinterNameList);
	// Application properties
	IMPORT_C void UpdateTaskNameL();
	IMPORT_C void SetBusy(TBool aBusy);
	IMPORT_C TBool IsBusy() const;
	IMPORT_C void SetSystem(TBool aSystem);
	IMPORT_C TBool IsSystem() const;
	IMPORT_C void SetDocNameIsAFile(TBool aDocNameIsAFile);
	IMPORT_C TBool DocNameIsAFile() const;
	IMPORT_C void SetRespondsToShutdownEvent(TBool aRespondsToShutdownEvent);
	IMPORT_C TBool RespondsToShutdownEvent() const;
	IMPORT_C void SetRespondsToSwitchFilesEvent(TBool aRespondsToSwitchFilesEvent);
	IMPORT_C TBool RespondsToSwitchFilesEvent() const;
	// Task list dialog
	IMPORT_C void DisplayTaskList();
	IMPORT_C void DismissTaskList();
public: // Internal (for Symbian and partners only)
	// Dialog factories
	inline MEikCDlgDialogFactory* CDlgDialogFactory() const;
	inline MEikPrintDialogFactory* PrintDialogFactory() const;
	inline MEikFileDialogFactory* FileDialogFactory() const;
	inline MEikIrFactory* IrFactory() const;
	inline void SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory);
	inline void SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory);
	inline void SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory);
	inline void SetIrFactory(MEikIrFactory* aIrFactory);
	CArrayFix<TCreateByTypeFunction>* ControlFactoryFuncArray() const;
	// Color scheme
	inline CColorList& ColorList() const;
	inline TRgb Color(TLogicalColor aLogicalColor) const;
	inline void SetColor(TLogicalColor aLogicalColor, TRgb aColor);
	IMPORT_C TRgb ControlColor(TLogicalColor aLogicalColor,const CCoeControl& aControl) const;
	inline CColorArray& CustomColorArray() const;
	IMPORT_C CColorList* CreateSystemColorListL();
	IMPORT_C CColorList* CreateSystemColorListL(const CColorList& aColorList);
	IMPORT_C void UpdateSystemColorListL(const CColorList& aColorList);
	IMPORT_C CColorList* PopulateColorArrayL();
	// Library loading and unloading
	IMPORT_C TInt AddLibraryL(TCreateByTypeFunction aControlFactory, TFileName* aResourceFile);
	inline TInt AddLibraryL(TCreateByTypeFunction aControlFactory);
	inline TInt AddLibraryL(TFileName* aResourceFile);
	IMPORT_C void RemoveLibrary(TCreateByTypeFunction aControlFactory, TInt aResourceFileOffset);
	inline void RemoveLibrary(TCreateByTypeFunction aControlFactory);
	inline void RemoveLibrary(TInt aResourceFileOffset);
	// Legacy UI utilities
	inline TChar NudgeCharMinus() const;
	inline TChar NudgeCharPlus() const;
	// Status pane
	inline TInt StatusPaneCoreResId() const;
	inline void SetStatusPaneCoreResId(TInt aStatusPaneCoreResId);
	// Auto menus
	IMPORT_C void AddAutoMenuTitleL(CEikAutoMenuTitle* aTitle);
	inline CEikAutoMenuTitleArray* AutoMenuTitleArray() const;
	// Display mode
	IMPORT_C TDisplayMode DefaultDisplayMode() const;
public: // internal
	IMPORT_C MLafEnv& LafEnv() const;				// deprecated
	inline TInt EditableControlStandardHeight() const;
	IMPORT_C void SendEventToEikonServer(TInt aEvent,const TAny* aPtr,TInt aLength);
	// Object factories
	IMPORT_C MEikAppUiFactory* AppUiFactory() const;
	IMPORT_C MEikAppUiFactory* AppUiFactory(const CEikAppUi& aAppUi) const;
	IMPORT_C void SetAppUiFactoryL(MEikAppUiFactory* aAppUiFactory);
	IMPORT_C void AddAppUiFactoryL(MEikAppUiFactory* aAppUiFactory);
	IMPORT_C void RemoveAppUiFactory();
public: // Internal. Do not use!
	IMPORT_C void SetExtension(CBase* aExtension);	// deprecated
	inline CBase* Extension() const;				// deprecated
	IMPORT_C void HandleError(TInt aError);
	IMPORT_C void WriteInternalStateOfStackedControlsL();
	IMPORT_C void DoGetErrorText(TDes& aDes,TInt aError) const;
	IMPORT_C TErrorValidity DoGetErrorTextAndTitle(TDes& aErrorText, TInt aError, TInt& aTextId, TUint& aFlags, TDes& aTitleText, TBool aIsMemoryAllocatedByErrResolver = EFalse) const;
	void InitSystemBitmapsL();
	void UpdateColorListL();
	void PostAppUiInitializeL();
	TLanguage ApplicationLanguage() const;
	void PostAppUiDestroy();
	TInt ConstructorError() const;
private:
	IMPORT_C virtual void CEikonEnv_Reserved_1();
	IMPORT_C virtual void CEikonEnv_Reserved_2();
	IMPORT_C virtual void CEikonEnv_Reserved_3();
	IMPORT_C virtual void CEikonEnv_Reserved_4();
	IMPORT_C virtual void CEikonEnv_Reserved_5();	
private: // framework functions
	IMPORT_C void DestroyScreen();
	IMPORT_C void InitSystemFontsL();
	IMPORT_C TInt ResourceFileVersionNumber() const;
public:
	IMPORT_C MEikInfoDialog* QueryDialog() const;
	IMPORT_C MEikInfoDialog* InfoDialog() const;
public:
	IMPORT_C CEikAppServer* AppServer() const;
	IMPORT_C TBool StartedAsServerApp() const;
protected:
	friend class CEikServAppUi;
private: // Internal
	void InitSystemResourceFileL();
	void InitPrivateResourceFileL();
	void InitInfoMsgL();
	void PrepareBusyMsgL();
	void InitAlertWinL();
	void InitDebugKeysL();
	TErrorHandlerResponse PrepareToHandleError(TInt aError);
	void DoHandleError(TErrorHandlerResponse aType);
	static TInt IdleErrorCallBack(TAny* aThis);
	void InitColorSchemeL();
	void LoadParserListL();
	void LoadLibrariesL();
	void CloseLibraries();
	TRequestDialogFunc RequestQueryDialogFunc();
	TRequestDialogFunc RequestInfoDialogFunc();
	void SetAppReady();
public:
	TBool IsEiksrvThread() const;
private:
	TBool InfoWinOrQueryWinL(TInt aFirstLineId,TInt aSecondLineId,TBool aIsQueryWin=EFalse) const;
	void SetCommandLineDebugMemFailL(const CApaCommandLine& aCommandLine);
	void StoreAppLanguageL(const RApaLsSession& aLsSession);
	void ErrorContextL(TInt aError,const TDesC& aContextText);
private:
	IMPORT_C virtual void CEikonEnv_Reserved_6();
	IMPORT_C virtual void CEikonEnv_Reserved_7();
	IMPORT_C virtual void CEikonEnv_Reserved_8();
	IMPORT_C virtual void CEikonEnv_Reserved_9();
	IMPORT_C virtual void CEikonEnv_Reserved_10();	
private:
	NONSHARABLE_CLASS(TEikAppUiFactory)
		{
	public:
		MEikAppUiFactory* iFactory;
		CEikAppUi* iAppUi;
		};
private:
	TBitFlags iEikonEnvFlags;
	TInt iForwardsCount;
	TInt iBusyCount;
	CEikProcess* iProcess;
	RAnimDll* iClockDll;
	CArrayPtr<CLafSystemFont>* iFontArray;
	MEikInfoMsgWin* iInfoMsgWin;
	MEikBusyMsgWin* iBusyMsgWin;
	MEikAlertWin* iAlertWin;
	TInt iSystemResourceFileOffset;
	HBufC8* iKeyPressLabels;
	CParaFormatLayer* iSingleLineParaFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	const CCoeControl* iCursorWindow;
	TInt iEditableControlStandardHeight;
	CApaWindowGroupName* iWgName;
	CEikErrorIdler* iErrorIdler;
	TInt iPrivateResourceFileOffset;
	CColorList* iColorList;
	CEikPictureFactory* iPictureFactory;
	TBuf<2> iNudgeChars;
	MEikInfoDialog* iQueryDialog;
	MEikInfoDialog* iInfoDialog;
	TRequestDialogFunc	iQueryDialogFunc;
	TRequestDialogFunc	iInfoDialogFunc;
	CArrayFix<TCreateByTypeFunction>* iControlFactoryFuncArray;
	CArrayFix<TInt>* iResourceFileOffsetArray;
	TBool iAlertWinInitialized;
	MEikDebugKeys* iDebugKeys;
	MEikCDlgDialogFactory* iCDlgDialogFactory;
	MEikPrintDialogFactory* iPrintDialogFactory;
	MEikFileDialogFactory* iFileDialogFactory;
	CArrayFix<TEikAppUiFactory>* iAppUiFactoryArray;
	MEikIrFactory* iIrFactory;
	CArrayPtr<CEikLibrary>* iLibraries;
	TInt iEmbeddedAppLevel;
	TInt iAutoLoadedResourceFiles;
	TInt iAutoLoadedControlFactories;
	CBase* iExtension;
	TInt iStatusPaneCoreResId;
	CEikAutoMenuTitleArray* iAutoMenuTitleArray;
	TEikVirtualCursor iVirtualCursor;
	CEikLogicalBorderProxy* iLogicalBorderProxy;
	CEikLafEnv* iLafEnv;
	CArrayPtrFlat<CFbsBitmap>* iBitmapArray;
	CEikEnvExtra* iEikEnvExtra; // used to be TInt iSpare1;
	HBufC* iOOMErrorText;		// used to be TInt iSpare2;
	TInt iSpare3;
	};


/** Interface for launching a dialog with a title and a message, for instance a 
query dialog.

Dialogs implementing this interface can be passed to CEikonEnv::SetQueryDialog() 
or CEikonEnv::SetInfoDialog(). 

@publishedAll
@released */
class MEikInfoDialog
	{
public:
	/** Initialises and executes the dialog.
	
	@param aResource The ID of the DIALOG resource that identifies the dialog's 
	type. For instance, a query dialog (with Yes/No buttons) or an info dialog 
	(with a Continue button).
	@param aTitle The dialog's title.
	@param aMsg The message to display in the dialog.
	@return True if the Confirm button (or equivalent) was pressed, false if the 
	dialog was cancelled. */
	virtual TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg) = 0;
	};

IMPORT_C void InternalizeL(TEikPortFlag& aThing,RReadStream& aStream);
inline RWriteStream& operator<<(RWriteStream& aStream,const TEikPortFlag& aThing)
	{aStream.WriteUint8L(aThing);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TEikPortFlag& aThing)
	{InternalizeL(aThing,aStream);return aStream;}

/**
@publishedAll
@released
*/
class MEikAlertWin
    {
public:
    virtual void ConstructL() = 0;
    virtual void RunAlert(const TDesC& aTitle, const TDesC& aMsg) = 0;
    virtual void Release() = 0;
    virtual CEikDialog* AsEikDialog() = 0;
    inline const CEikDialog* AsEikDialog() const;
    IMPORT_C virtual CCoeControl* AsCoeControl();
    inline const CCoeControl* AsCoeControl() const;
private:
    IMPORT_C virtual void MEikAlertWin_Reserved2();
    IMPORT_C virtual void MEikAlertWin_Reserved3();
    };


/**
@publishedAll
@released 
*/
class MEikDebugKeys
    {
public:
    virtual void ConstructL() = 0;
    virtual void Release() = 0;
private:
    IMPORT_C virtual void MEikDebugKeys_Reserved1();
    IMPORT_C virtual void MEikDebugKeys_Reserved2();
    IMPORT_C virtual void MEikDebugKeys_Reserved3();
    };

#include <eikenv.inl>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

#endif	// __EIKENV_H__
