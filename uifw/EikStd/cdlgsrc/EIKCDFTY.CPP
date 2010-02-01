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


#include "EIKCDFTY.H"

TBool NotDefined()
	{
	User::Leave(KErrNotSupported);
	return ETrue;
	};

EXPORT_C CEikCDlgDialogFactory* CEikCDlgDialogFactory::NewL()
	{
	CEikCDlgDialogFactory* self = new(ELeave) CEikCDlgDialogFactory;
	return self;
	}

CEikCDlgDialogFactory::CEikCDlgDialogFactory()
	{
	}

TBool CEikCDlgDialogFactory::RunCharMapDlgLD(CCoeControl* /*aControl*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunFontDlgLD(TCharFormat& /*aFormat*/,
												TCharFormatMask& /*aAttribChangedMask*/,
												TCharFormatMask& /*aUndeterminedMask*/,
												TDesC& /*aTextSelection*/,
												TInt /*aFonts*/,
												CGraphicsDevice* /*aGraphicsDevice*/, 
												TInt /*aFontControlFlags*/,
												const TRgb /*aBackGroundColor*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

void CEikCDlgDialogFactory::RunEdwinFindAndReplaceDlgLD(MEikFindAndReplaceDlgObserver& /*aObserver*/, 
		SEdwinFindModel& /*aModel*/, TBool /*aFindOnly*/, TRect /*aEdwinRect*/)
	{
	User::Leave(KErrNotSupported);
	}

TBool CEikCDlgDialogFactory::RunInsertObjectDlgLD(	
										CEikEmbeddableAppList*	/*aList*/,
										TInt&					/*aChoice*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunObjectInfoDlgLD(const TDesC& /*aCaption*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunFormatObjectDlgLD(	CApaDoor&		/*aDoor*/,
														CApaDocument&	/*aDoc*/,
														const TSize&	/*aDefaultIconSize*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}


TBool CEikCDlgDialogFactory::RunEdwinFindDlgLD(	SEdwinFindModel*	/*aModel*/,
													CDesCArray*		/*	aFindList*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunEdwinReplaceDlgLD(	
										SEdwinFindModel* /* aModel*/,
										CDesCArray*		/*aFindList*/,
										CDesCArray*		/*aReplaceList*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunEdwinReplaceOptionDlgLD(	
										CEikGlobalTextEditor*	/*aEdwin*/,
										SEdwinFindModel*		/*aModel*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunAlignDlgLD(
									CParaFormat*		/*aFormat*/, 
									TParaFormatMask&	/*aAttribChangedMask*/, 
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunSpaceDlgLD(
									CParaFormat*		/*aFormat*/, 
									TParaFormatMask&	/*aAttribChangedMask*/, 
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunBorderDlgLD(
									CParaFormat*		/*aFormat*/, 
									TParaFormatMask&	/*aAttribChangedMask*/, 
									TParaFormatMask&	/*aUndeterminedMask*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunTabsDlgLD(	
									CParaFormat*		/*aFormat*/, 
									TParaFormatMask&	/*aAttribChangedMask*/, 
									TParaFormatMask&	/*aUndeterminedMask*/,
									const TInt			/*aPageWidth*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}

TBool CEikCDlgDialogFactory::RunIndentDlgLD(	
									CParaFormat*		/*aFormat*/, 
									TParaFormatMask&	/*aAttribChangedMask*/, 
									TParaFormatMask&	/*aUndeterminedMask*/,
									const TInt			/*aPageWidth*/)
	{
	// stubbed as this code has been thinned
	return NotDefined();
	}
										
										
////////////////////////////////////////////////////////////////////////////////////////
//
// END OF FILE
//
////////////////////////////////////////////////////////////////////////////////////////
