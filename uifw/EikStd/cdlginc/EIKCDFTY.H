/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKCDFTY_H__)
#define __EIKCDFTY_H__

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

#if !defined(__EIKDGFTY_H__)
#include <eikdgfty.h>
#endif

class MEikFindAndReplaceDlgObserver;
class CGraphicsDevice;

NONSHARABLE_CLASS(CEikCDlgDialogFactory) : public CBase, public MEikCDlgDialogFactory
	{
public:
	IMPORT_C static CEikCDlgDialogFactory* NewL();
private:
	CEikCDlgDialogFactory();
	TBool RunCharMapDlgLD(CCoeControl* aControl);
	TBool RunFontDlgLD(		TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TCharFormatMask& aUndeterminedMask,
							TDesC& aTextSelection,
							TInt aFonts,
							CGraphicsDevice* aGraphicsDevice, 
							TInt aFontControlFalgs,
							const TRgb aBackGroundColor);

	TBool RunInsertObjectDlgLD(	CEikEmbeddableAppList*	aList,
								TInt&					aChoice);

	TBool RunObjectInfoDlgLD(const TDesC& aCaption);
	TBool RunFormatObjectDlgLD(	CApaDoor&		aDoor,
								CApaDocument&	aDoc,
								const TSize&	aDefaultIconSize);

	void RunEdwinFindAndReplaceDlgLD(MEikFindAndReplaceDlgObserver& aObserver,
		SEdwinFindModel& aModel, TBool aFindOnly, TRect aEdwinRect);
	
	TBool RunEdwinFindDlgLD(	SEdwinFindModel*	aModel,
								CDesCArray*			aFindList);

	TBool RunEdwinReplaceDlgLD(	SEdwinFindModel* aModel,
								CDesCArray*		aFindList,
								CDesCArray*		aReplaceList);

	TBool RunEdwinReplaceOptionDlgLD(	CEikGlobalTextEditor*	aEdwin,
										SEdwinFindModel*		aModel);

	TBool RunAlignDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunBorderDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunSpaceDlgLD(
						CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask);

	TBool RunTabsDlgLD(	CParaFormat*		aFormat, 
						TParaFormatMask&	aAttribChangedMask, 
						TParaFormatMask&	aUndeterminedMask,
						const TInt			aPageWidth);

	TBool RunIndentDlgLD(	CParaFormat*		aFormat, 
							TParaFormatMask&	aAttribChangedMask, 
							TParaFormatMask&	aUndeterminedMask,
							const TInt			aPageWidth);
	};

#endif
