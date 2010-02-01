/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test EIKGTED.h
 *
*/


#ifndef C_TESTSDKEDITORSDIALOGFACTORY_H
#define C_TESTSDKEDITORSDIALOGFACTORY_H

#include <eikdgfty.h>

class CTestSDKEditorsDialogFactory : public CBase,
                                     public MEikPrintDialogFactory,
                                     public MEikCDlgDialogFactory
    {
public:
    
    /**
    * C++ default constructor.
    */
    CTestSDKEditorsDialogFactory();
    
    /**
     * Destructor.
     */
    ~CTestSDKEditorsDialogFactory();
    
    /**
     * from MEikPrintDialogFactory
     */
    TBool RunPaginateDlgLD( CEikGlobalTextEditor* aEditor,
                            CPrintSetup* aPrintSetup,
                            CArrayFix<TInt>* aCharsPerPage );
    
    /**
     * from MEikPrintDialogFactory
     */
    CPrintSetup* NewDefaultPrintSetupL();
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunCharMapDlgLD( CCoeControl* aControl );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunFontDlgLD( TCharFormat& aFormat, TCharFormatMask& aAttribChangedMask,
                        TCharFormatMask& aUndeterminedMask, TDesC& aTextSelection,
                        TInt aFonts, CGraphicsDevice* aGraphicsDevice, 
                        TInt aFontControlFlags, const TRgb aBackGroundColor );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunInsertObjectDlgLD( CEikEmbeddableAppList* aList, TInt& aChoice );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunObjectInfoDlgLD( const TDesC& aCaption );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunFormatObjectDlgLD( CApaDoor& aDoor, CApaDocument& aDoc,
                                const TSize& aDefaultIconSize );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunEdwinFindDlgLD( SEdwinFindModel* aModel, CDesCArray* aFindList );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunEdwinReplaceDlgLD( SEdwinFindModel* aModel, CDesCArray*     aFindList,
                                CDesCArray* aReplaceList );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunEdwinReplaceOptionDlgLD( CEikGlobalTextEditor* aEdwin,
                                      SEdwinFindModel* aModel );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunAlignDlgLD( CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, 
                         TParaFormatMask& aUndeterminedMask );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunBorderDlgLD( CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, 
                          TParaFormatMask& aUndeterminedMask );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunSpaceDlgLD( CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, 
                         TParaFormatMask& aUndeterminedMask );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunTabsDlgLD( CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, 
                        TParaFormatMask& aUndeterminedMask, const TInt aPageWidth );
    
    /**
     * from MEikCDlgDialogFactory
     */
    TBool RunIndentDlgLD( CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, 
                          TParaFormatMask& aUndeterminedMask, const TInt aPageWidth );

    /**
     * from MEikCDlgDialogFactory
     */
    void RunEdwinFindAndReplaceDlgLD( MEikFindAndReplaceDlgObserver& aObserver,
                                      SEdwinFindModel& aModel, 
                                      TBool aFindOnly, 
                                      TRect aEdwinRect );
    };

#endif /*C_TESTSDKEDITORSDIALOGFACTORY_H*/
