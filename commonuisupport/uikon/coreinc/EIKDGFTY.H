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

#ifndef __EIKDGFTY_H__
#define __EIKDGFTY_H__

#include <badesca.h>

class MEikFindAndReplaceDlgObserver;
class CCoeControl;
class CEikEmbeddableAppList;
class CGraphicsDevice;
class CApaDoor;
class CApaDocument;
class TCharFormat;
class TCharFormatMask;
class TRgb;
class CEikGlobalTextEditor;
struct SEdwinFindModel;
class CParaFormat;
class TParaFormatMask;
class CPrintSetup;


/**
@publishedPartner
@released
*/
class MEikCDlgDialogFactory
	{
public:
	// These functions are wrappers around the constructors of each dialog
	// so parameters mirror those of the constructor
	// Return value is from dialog's ExecuteLD function
	virtual TBool RunCharMapDlgLD(CCoeControl* aControl) = 0;
	virtual TBool RunFontDlgLD(	TCharFormat& aFormat,
								TCharFormatMask& aAttribChangedMask,
								TCharFormatMask& aUndeterminedMask,
								TDesC& aTextSelection,
								TInt aFonts,
								CGraphicsDevice* aGraphicsDevice, 
								TInt aFontControlFlags,
								const TRgb aBackGroundColor) = 0;

	virtual TBool RunInsertObjectDlgLD(	CEikEmbeddableAppList*	aList,
										TInt&					aChoice) = 0;

	virtual TBool RunObjectInfoDlgLD(const TDesC& aCaption) = 0;

	virtual TBool RunFormatObjectDlgLD(	CApaDoor&		aDoor,
										CApaDocument&	aDoc,
										const TSize&	aDefaultIconSize) = 0;

	virtual TBool RunEdwinFindDlgLD(SEdwinFindModel* aModel,
									CDesCArray* aFindList) = 0;

	virtual TBool RunEdwinReplaceDlgLD(	SEdwinFindModel* aModel,
										CDesCArray*		aFindList,
										CDesCArray*		aReplaceList) = 0;

	virtual void RunEdwinFindAndReplaceDlgLD(MEikFindAndReplaceDlgObserver& aObserver,
		SEdwinFindModel& aModel, TBool aFindOnly, TRect aEdwinRect)=0;

	virtual TBool RunEdwinReplaceOptionDlgLD(	CEikGlobalTextEditor*	aEdwin,
												SEdwinFindModel*		aModel) = 0;

	virtual TBool RunAlignDlgLD( CParaFormat*		aFormat, 
								TParaFormatMask&	aAttribChangedMask, 
								TParaFormatMask&	aUndeterminedMask) = 0;

	virtual TBool RunBorderDlgLD( CParaFormat*		aFormat, 
								TParaFormatMask&	aAttribChangedMask, 
								TParaFormatMask&	aUndeterminedMask) = 0;

	virtual TBool RunSpaceDlgLD( CParaFormat*		aFormat, 
								TParaFormatMask&	aAttribChangedMask, 
								TParaFormatMask&	aUndeterminedMask) = 0;

	virtual TBool RunTabsDlgLD(	CParaFormat*		aFormat, 
								TParaFormatMask&	aAttribChangedMask, 
								TParaFormatMask&	aUndeterminedMask,
								const TInt			aPageWidth) = 0;

	virtual TBool RunIndentDlgLD(	CParaFormat*		aFormat, 
									TParaFormatMask&	aAttribChangedMask, 
									TParaFormatMask&	aUndeterminedMask,
									const TInt			aPageWidth) = 0;
protected:
	IMPORT_C MEikCDlgDialogFactory();
private:
	IMPORT_C virtual void MEikCDlgDialogFactory_Reserved1();
	IMPORT_C virtual void MEikCDlgDialogFactory_Reserved2();
private:
	TInt iMEikCDlgDialogFactory_Spare;
	};


/**
@publishedPartner
@released 
*/
class MEikPrintDialogFactory
	{
public:
	// The print observer requires the global text editor to break the 
	// dependency of the control on the print library
	virtual TBool RunPaginateDlgLD(	CEikGlobalTextEditor*	aEditor,
									CPrintSetup*			aPrintSetup,
									CArrayFix<TInt>*		aCharsPerPage) = 0;

	virtual CPrintSetup* NewDefaultPrintSetupL() = 0;
protected:
	IMPORT_C MEikPrintDialogFactory();
private:
	IMPORT_C virtual void MEikPrintDialogFactory_Reserved1();
	IMPORT_C virtual void MEikPrintDialogFactory_Reserved2();
private:
	TInt iMEikPrintDialogFactory_Spare;
	};


/**
@publishedPartner
@released
*/
class MEikFileDialogFactory
	{
public:
	// These functions are wrappers around the constructors of each dialog
	// so parameters mirror those of the constructor
	// Return value is from dialog's ExecuteLD function
	virtual TBool RunFileSaveAsDlgLD(	TDes*	aFileName,
										TBool*	aUseNewFile,
										TInt	aTitleId,
										TBool	aAppendExtension) = 0;

	virtual TBool RunScreenCaptureDlgLD(TDes*	aFileName,
										TBool&	aSaveAsMonochromeImage,
										TInt	aTitleId) = 0;
protected:
	IMPORT_C MEikFileDialogFactory();
private:
	IMPORT_C virtual void MEikFileDialogFactory_Reserved1();
	IMPORT_C virtual void MEikFileDialogFactory_Reserved2();
private:
	TInt iMEikFileDialogFactory_Spare;
	};


#endif	// __EIKDGFTY_H__
