/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  General Avkon Utilities. Includes:
*                   - listbox utilities
*                   - layout utilities
*                   - text utilities
*
*/


#include "AknUtils.h"
#include "AknBidiTextUtils.h"
#include <eikfrlb.h>
#include <eikfrlbd.h>
#include <eikclb.h>
#include <eikclbd.h>
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <eikappui.h>
#include <eikslb.h>
#include <eikslbd.h>
#include <gulicon.h>
#include <AknGrid.h>
#include <eikbtgpc.h>
#include <eikcapc.h>

#include "avkon.hrh"
#include <avkon.rsg>

#include "aknappui.h"
#include "AknPanic.h"
#include "aknkeys.h"
#include <barsread.h>
#include "AknLib.h"
#include "akntitle.h"

#include <eikedwin.h>
#include <eikmfne.h>
#include <eikimage.h>

#include <txtfrmat.h>
#include <txtglobl.h>
#include <txtrich.h>

#include "aknsfld.h"
#include "AknTextWrapper.h"
#include <eikdialg.h>


#include <aknenv.h>
#include <coemain.h>
#include <eikseced.h>

#include <lafpanic.h> 

#include <eikmenup.h>

#include "aknlists.h"
#include <fontids.hrh>
#include <gulfont.h>
#include <eikapp.h>
#include <FindUtil.h>

#include <AknsDrawUtils.h>
#include <AknsControlContext.h>

#include <AknsUtils.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <AknsConstants.h>

#include <numberconversion.h>

#include <linebreak.h>
#include "AknLineBreaker.h"
#include "AknBuildVariant.h"
#include <biditext.h>
#include <AknSettingCache.h>

#include <featmgr.h>

#include <aknlayout.cdl.h>
#include <skinlayout.cdl.h>

#include <AknTextDecorationMetrics.h>
#include <AknFontSpecification.h>
#include <AknLayoutFont.h>
#include <AknFontId.h>
#include <AknFontProvider.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include "AknFontSpecificationLayoutFont.h"
#include <AknIconUtils.h>
#include <languages.hrh>
#include <AknSystemFont.h>
#include "AvkonVariant.hrh"

#include <AknStatuspaneUtils.h>
#include <StringLoader.h>
#include <AknSgcc.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <akntoolbar.h>
#include <akntouchpane.h>
#include "AknLayoutUtilsHelpers.h"

#include "AknAdaptiveSearch.h"
#include <PtiEngine.h>

#include <akntrace.h> 

#ifdef RD_HINDI_PHONETIC_INPUT
#include <ptiindicdefs.h>
#endif

using namespace AknLayout;

// CONSTANTS

const TInt KAknStringBufferSize = 256;
const TInt KTextColorNone = -1;
const TInt KFontHeightComparisonDivisor = 20;
const TInt KInvalidIndex = -1;

enum TAknLayoutEdwinPanic
    {
    EAknLayoutEdwinPanicNoEdwin,
    EAknLayoutEdwinPanicNoLinesOverMaxNoLines,
    EAknLayoutEdwinPanicNotSupported
    };

void Panic(TAknLayoutEdwinPanic aPanic)
    {
    _LIT(KAknLayoutUtilsLayoutEdwin,"AknLayoutUtils::LayoutEdwin");
    User::Panic(KAknLayoutUtilsLayoutEdwin, aPanic);
    };

void Panic(TLafPanic aPanic)
    {
    _LIT(KLafEnv,"LafEnv");
    User::Panic(KLafEnv, aPanic);
    };

// For debugging purposes.
#ifdef AKNUTILS_ENABLE_TRACES
        #define LOGTEXT(AAA)                     RDebug::Print(AAA)
        #define LOGTEXT1(AAA,BBB)                RDebug::Print(AAA,BBB)
        #define LOGTEXT2(AAA,BBB,CCC)            RDebug::Print(AAA,BBB,CCC)
        #define LOGTEXT3(AAA,BBB,CCC,DDD)        RDebug::Print(AAA,BBB,CCC,DDD)
        #define LOGTEXT4(AAA,BBB,CCC,DDD,EEE)    RDebug::Print(AAA,BBB,CCC,DDD,EEE)
#else
        #define LOGTEXT(AAA)                     NULL
        #define LOGTEXT1(AAA,BBB)                NULL
        #define LOGTEXT2(AAA,BBB,CCC)            NULL
        #define LOGTEXT3(AAA,BBB,CCC,DDD)        NULL
        #define LOGTEXT4(AAA,BBB,CCC,DDD,EEE)    NULL  
#endif 

//
// Automatic numbering for columnlistbox.
// CListBoxNumbers
//
EXPORT_C CListBoxNumbers::CListBoxNumbers(CEikTextListBox *aListBox)
    {
    iListBox = aListBox;
    }

EXPORT_C void CListBoxNumbers::ConstructL()
    {
    UpdateL();
    }


EXPORT_C void CListBoxNumbers::UpdateL()
    {
    TInt e = iListBox->Model()->NumberOfItems();
    MDesCArray* itemList = iListBox->Model()->ItemTextArray();
    CDesCArray* itemArray = STATIC_CAST(CDesCArray*,itemList);
    for (int i=0;i<e;i++)
        {
        TPtrC item = (*itemArray)[i];
        TInt pos = item.Locate('\t');
        TBuf<KAknStringBufferSize> data; 
        data.Num(i+1);
        data+=item.Right(item.Length()-pos);
        itemArray->Delete(i);
        itemArray->InsertL(i,data);
        }   
    }


// Fonts

EXPORT_C const CFont *LatinPlain12()
    { 
    switch (AknLayoutUtils::Variant())
        {
        case EEuropeanVariant:
            return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlp12)));

        case EApacVariant:
            // should not come here ever
            return ApacPlain12();

        default:
            return 0;
        }

    }

EXPORT_C const CFont *LatinBold12() 
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb12))); 
    }

EXPORT_C const CFont *LatinBold13()
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb13)));
    }
EXPORT_C const CFont *LatinBold16()
    {
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb16)));
    }

EXPORT_C const CFont *LatinBold17()
    { 
    switch (AknLayoutUtils::Variant())
        {
        case EEuropeanVariant:
            return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb17)));

        case EApacVariant:
            return LatinBold13();

        default:
            return 0;
        }
    }

EXPORT_C const CFont *LatinBold19() 
    { 
        switch (AknLayoutUtils::Variant())
        {
        case EEuropeanVariant:
            return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb19)));

        case EApacVariant:
            return LatinBold17();

        default:
            return 0;
        }
  
    }
EXPORT_C const CFont *ClockBold30()
    {
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAcb30)));
    }

EXPORT_C const CFont *NumberPlain5()
    {
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAcp5)));
    }

EXPORT_C const CFont *LatinClock14() 
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAcb14)));
    }

const CFont *CalcBold21() 
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAcalc21)));
    }

const CFont *CalcOperBold21() 
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAco21)));
    }

const CFont *CalcOperBold13() 
    { 
    return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAco13)));
    }

EXPORT_C const CFont *ApacPlain12() 
    { 
    // Combined font is used for all subvariants
    if ( AknLayoutUtils::Variant() == EApacVariant )
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidCombinedChinesePlain12)));
        }
    else
        {
        //this should not be called in Western builds
        //__ASSERT_DEBUG(0, Panic(ELafPanicUsingFontFromWrongVariant));
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb13)));
        }

    }

EXPORT_C const CFont *ApacPlain16() 
    {
    // Combined font is used for all subvariants
    if ( AknLayoutUtils::Variant() == EApacVariant )
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidCombinedChinesePlain16)));
        }
    else
        {
        //this should not be called in Western builds
        //__ASSERT_DEBUG(0, Panic(ELafPanicUsingFontFromWrongVariant));
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb13)));
        }
    }

const CFont* PrimaryFont()
    {
    if ( AknLayoutUtils::Variant() == EApacVariant )
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidCombinedChinesePlain16)));
        }
    else
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb13)));
        }
    }

const CFont* SecondaryFont()
    {
    if ( AknLayoutUtils::Variant() == EApacVariant )
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidCombinedChinesePlain12)));
        }
    else
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlp12)));
        }
    }

const CFont* TitleFont()
    {
    if ( AknLayoutUtils::Variant() == EApacVariant )
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidCombinedChinesePlain16)));
        }
    else
        {
        return CEikonEnv::Static()->Font(TLogicalFont(TUid::Uid(KScreenFontUidAlb19)));
        }
    }


//
// Find implementation
//

EXPORT_C
void AknFind::HandleFindPopupProcessCommandL( TInt aCommand,
                                              CEikListBox * aListBox,
                                              CAknSearchField *aSearch,
                                              CCoeControl *aParentControl )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aSearch && aCommand == EAknCmdFindPopupActivated )
        {
        if ( aListBox )
            {
            aSearch->SetOldItemIndex( aListBox->CurrentItemIndex() );
            }
        aSearch->MakeVisible( ETrue );
        aSearch->SetFocus( ETrue );
        HandlePopupFindSizeChanged( aParentControl, aListBox, aSearch );
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C
void AknFind::HandleFixedFindSizeChanged( CCoeControl *aParentControl,
                                          CAknColumnListBox *aListBox,
                                          CAknSearchField *aSearchField )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknWindowLineLayout empty;
    empty.iC = 0;
    empty.il = 0;
    empty.it = 0;
    empty.ir = 0;
    empty.ib = 0;
    empty.iW = ELayoutEmpty;
    empty.iH = ELayoutEmpty;

    TAknWindowLineLayout findPane = AknLayoutScalable_Avkon::find_pane().LayoutLine();
    TAknWindowLineLayout listPane;

    // listPane should equal to parent's rect
    listPane.il = aParentControl->Rect().iTl.iX;
    listPane.ir = ELayoutEmpty;
    listPane.it = aParentControl->Rect().iTl.iY;
    listPane.ib = ELayoutEmpty;

    // this check is required since it's not guaranteed that listbox's SetRect
    // has been called when this code is executed
    if ( aParentControl->Size().iWidth > 0 )
        {
        listPane.iW = aParentControl->Size().iWidth;
        listPane.ir = ELayoutEmpty;
        }
    else
        {
        listPane.iW = ELayoutEmpty;
        listPane.ir = 0;
        }
    
    // but findpane's height should be subtracted
    listPane.iH = aParentControl->Size().iHeight - findPane.iH;

    // findPane's width should equal to listPane's width
    findPane.iW = listPane.iW;
    
    HandleFindSizeChangedLayouts( aParentControl,
                                  aListBox,
                                  aSearchField,
                                  findPane,
                                  listPane,
                                  EFalse,
                                  empty );
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C
void AknFind::HandlePopupFindSizeChanged( CCoeControl *aParentControl,
                                          CEikListBox *aListBox,
                                          CAknSearchField *aSearchField )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknWindowLineLayout findPane = AknLayoutScalable_Avkon::popup_find_window().LayoutLine();
    TAknWindowLineLayout listPane;

    // listPane should equal to parent's rect
    listPane.il = aParentControl->Rect().iTl.iX;
    listPane.it = aParentControl->Rect().iTl.iY;
    listPane.ib = 0;
    listPane.iH = ELayoutEmpty;
    
    // this check is required since it's not guaranteed that listbox's SetRect
    // has been called when this code is executed
    if ( aParentControl->Size().iWidth > 0 )
        {
        listPane.iW = aParentControl->Size().iWidth;
        listPane.ir = ELayoutEmpty;
        }
    else
        {
        listPane.iW = ELayoutEmpty;
        listPane.ir = 0;
        }
    
    // findPane's width should equal to listPane's width
    findPane.iW = listPane.iW;
    
    HandleFindSizeChangedLayouts( aParentControl,
                                  aListBox,
                                  aSearchField,
                                  findPane,
                                  listPane,
                                  ETrue,
                                  main_pane( screen().Rect(), 0, 1, 1) );
    _AKNTRACE_FUNC_EXIT;
    }


// THIS METHOD IS DEPRECATED
EXPORT_C void AknFind::HandleFindSizeChanged(CCoeControl *aParentControl, 
                         CEikListBox *aListBox, 
                         CAknSearchField *aSearchField, 
                         TBool ispopup, 
                         TInt aFindWindowResourceId, 
                         TInt aListAreaResourceId, 
                         TInt aListResourceIdWithFindPopup, 
                         TInt aFindWindowParentResourceId)
    {
    _AKNTRACE_FUNC_ENTER;
    if (aSearchField)
    {
    aSearchField->SetListbox(aListBox);
    aSearchField->SetParentCtrl(aParentControl);
    STATIC_CAST(CAknFilteredTextListBoxModel*,aListBox->Model())->Filter()->SetParentControl(aParentControl);
    TRect parentrect = aParentControl->Rect();
    if (ispopup)
        { // popup find position is different
        ((CAknFilteredTextListBoxModel*)aListBox->Model())->Filter()->SetPopup();
        parentrect = iAvkonAppUi->ApplicationRect();
        TBuf<KAknStringBufferSize> criteria;
        aSearchField->GetSearchText(criteria);
        if (aSearchField->IsVisible() )
        aListAreaResourceId = aListResourceIdWithFindPopup;
        } 
    else 
        { // normal find has different empty list
        CAknColumnListBoxView *view = STATIC_CAST(CAknColumnListBoxView*,aListBox->View());
        view->EnableFindEmptyList();
        }
    TAknLayoutRect lrect;
    lrect.LayoutRect(parentrect, aFindWindowParentResourceId);
    AknLayoutUtils::LayoutControl(aSearchField, lrect.Rect(), aFindWindowResourceId);
    _AKNTRACE( "[%s][%s] SearchField Rect iTl: %d,%d; iBr: %d,%d", 
                "AknFind", __FUNCTION__, 
                lrect.Rect().iTl.iX, lrect.Rect().iTl.iY, 
                lrect.Rect().iBr.iX, lrect.Rect().iBr.iY 
                );
    }
    AknLayoutUtils::LayoutControl(aListBox, aParentControl->Rect(), aListAreaResourceId);
    _AKNDEBUG(
            if ( aListBox )
                {
    		_AKNTRACE( "[%s][%s] ListBox Rect iTl: %d,%d; iBr: %d,%d", 
    				"AknFind", __FUNCTION__, 
    				aParentControl->Rect().iTl.iX, aParentControl->Rect().iTl.iY, 
    				aParentControl->Rect().iBr.iX, aParentControl->Rect().iBr.iY 
				);
                }
        );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void AknFind::HandleFindSizeChangedLayouts(
    CCoeControl *aParentControl, 
    CEikListBox *aListBox, 
    CAknSearchField *aSearchField, 
    const TAknWindowLineLayout& aFindWindow,
    const TAknWindowLineLayout& aListArea,
    TBool aIsPopup, 
    const TAknWindowLineLayout& aFindWindowParent)
    {
    _AKNTRACE_FUNC_ENTER;
    TAknWindowLineLayout tempListArea = aListArea;
    
    if (aSearchField)
        {
        aSearchField->SetParentCtrl(aParentControl);
        aSearchField->SetListbox(aListBox);
        CAknFilteredTextListBoxModel* m = static_cast <CAknFilteredTextListBoxModel*> ( aListBox->Model() );
        if ( m->Filter() )
            {
            m->Filter()->SetParentControl( aParentControl );
            }

        TRect parentrect( aParentControl->Rect() );
        
        if (aIsPopup)
            { // popup find position is different
            if ( m->Filter() )
                {
                m->Filter()->SetPopup();
                }
            // TPTN-7AXDMZ. For fixed toolbar.
            TRect rect;
            parentrect = AknLayoutUtils::LayoutMetricsRect( 
                AknLayoutUtils::EApplicationWindow, rect) ? 
                rect : 
                iAvkonAppUi->ApplicationRect();

            if ( iAvkonAppUi->CurrentFixedToolbar() 
                 && AknLayoutUtils::PenEnabled() 
                 && !Layout_Meta_Data::IsLandscapeOrientation() )
                {
                CAknToolbar* toolbar = iAvkonAppUi->CurrentFixedToolbar();
                TInt flags = toolbar->ToolbarFlags(); 
                if ( flags & KAknToolbarFixed 
                     && !( flags & KAknToolbarDefault )
                     && toolbar->IsShown() ) 
                    {
                    parentrect.iBr.iY -= toolbar->Rect().Height();
                    }
                }
            TBuf<KAknStringBufferSize> criteria;
            aSearchField->GetSearchText(criteria);
            if (aSearchField->IsVisible() )
                {
                if (tempListArea.iH == ELayoutEmpty) 
                    { 
                    tempListArea.iH = TInt16(ELayoutP - tempListArea.it - tempListArea.ib); 
                    }
                
                tempListArea.iH = 
                    TUint16(tempListArea.iH - ( AknLayoutScalable_Avkon::popup_find_window().LayoutLine().iH - 1 ) );
                }
            } 
        else 
            { // normal find has different empty list
            CAknColumnListBoxView *view = STATIC_CAST(CAknColumnListBoxView*,aListBox->View());
            view->EnableFindEmptyList();
            }
            
        TAknLayoutRect lrect;
        lrect.LayoutRect(parentrect, aFindWindowParent);
        AknLayoutUtils::LayoutControl(aSearchField, lrect.Rect(), aFindWindow);
        _AKNTRACE( "[%s][%s] SearchField Rect iTl: %d,%d; iBr: %d,%d", 
                    "AknFind", __FUNCTION__, 
                    lrect.Rect().iTl.iX, lrect.Rect().iTl.iY, 
                    lrect.Rect().iBr.iX, lrect.Rect().iBr.iY 
                    );
        }
        
    AknLayoutUtils::LayoutControl(aListBox, aParentControl->Rect(), tempListArea);
    _AKNDEBUG(
    		if ( aListBox )
                {
                _AKNTRACE( "[%s][%s] ListBox Rect iTl: %d,%d; iBr: %d,%d", 
                            "AknFind", __FUNCTION__,
                            aListBox->Rect().iTl.iX, aListBox->Rect().iTl.iY, 
                            aListBox->Rect().iBr.iX, aListBox->Rect().iBr.iY 
                            );
                }
		);
    if ( aListBox )
        {
        aListBox->DrawNow();
        }
    _AKNTRACE_FUNC_EXIT;
    }

void AknFind::HandleFindPaneVisibility(CAknSearchField *aSearchField, TBool ispopup, TBool textnotchanged, TBool &aNeedRefresh)
    {
    if (ispopup)
        {
        TBuf<KAknStringBufferSize> criteria;
        aSearchField->GetSearchText(criteria);
        TBool oldvisibility = aSearchField->IsVisible();
        TBool findboxvisible;
        TInt newlength = criteria.Length();
        
        _AKNTRACE( "[%s][%s] Text Length is: %d", 
                    "AknFind", __FUNCTION__, newlength );
               
        if (newlength == 0)
            {
            findboxvisible = EFalse;
            if (textnotchanged && oldvisibility)
                {
                findboxvisible=ETrue;
                }
            }
        else
            {
            findboxvisible = ETrue;
            }
        if (findboxvisible != oldvisibility)
            {
            aSearchField->SetFocus(findboxvisible);
            aSearchField->MakeVisible(findboxvisible);            
            aNeedRefresh = ETrue;
            }
        _AKNTRACE( "[%s][%s] SearchField's visibility is: %d", 
                    "AknFind", __FUNCTION__, aNeedRefresh );
        }
    }

#define ISFINDWORDSEPARATOR( aCh ) ( (aCh) == ' ' || (aCh) == '-' || (aCh) == '\t' )
const TInt KMatchingBufferLength(256);
const TInt KLitSpace(' ');
const TInt KLitStar('*');
const TInt KLitTab('\t');

EXPORT_C TBool AknFind::IsFindMatch( const TDesC &aItemString, const TDesC &aSearchText )
    {
    TInt length = aItemString.Length();
    for( TInt i = 0; i < length; i++ )
        {
        if ( i==0 || ISFINDWORDSEPARATOR( aItemString[i-1] ) )
            {
            if ( aItemString.Mid(i).FindC( aSearchText ) == 0 )
                {               
                return ETrue;
                }
            }
        }
    return EFalse;
    }

EXPORT_C TBool AknFind::IsFindWordSeparator(TChar aCh)
    {
    return ISFINDWORDSEPARATOR( aCh );
    }
    
// -----------------------------------------------------------------------------
// For Vietnamese AS
// 
// -----------------------------------------------------------------------------
//
inline TChar ReplaceVietnameseChar( const TChar aCh )   
    {
    TChar Char = aCh.GetUpperCase();
    if ( (Char >= 0x00C0 && Char <= 0x00C3) || Char == 0x102  ||
         ((Char >= 0x1EA0 && Char <= 0x1EB6) && Char%2 == 0) )  
        {
        Char = 0x0041; // A
        return Char; 
        }
    if ( (Char >= 0x00C8 && Char <= 0x00CA) || 
        ((Char >= 0x1EB8 && Char <= 0x1EC6) && Char%2 == 0) )
        {
        Char = 0x0045; // E
        return Char; 
        }               
    if ( Char == 0x00CC || Char == 0x00CD || Char == 0x0128 || 
         Char == 0x1EC8 || Char == 0x1ECA  )
        {
        Char = 0x0049; // I
        return Char; 
        }    
    if ( (Char >= 0x00D2 && Char <= 0x00D5 ) || Char == 0x1ECE || Char == 0x1ECC ||
        ((Char >= 0x1ED0 && Char <= 0x1ED8) && Char%2 == 0)) 
        {
        Char = 0x004F; // O
        return Char; 
        }            
    if ( Char == 0x1EDA || Char == 0x1EDC || Char == 0x1EDE || 
         Char == 0x1EE0 || Char == 0x1EE2  )
        {
        Char = 0x01A0; // O-horn
        return Char; 
        }          
    if ( Char == 0x00DA || Char == 0x00D9 || Char == 0x0168 || 
         Char == 0x1EE4 || Char == 0x1EE6  )
        {
        Char = 0x0055; // U
        return Char; 
        }         
     if ( (Char >= 0x1EE8 && Char <= 0x1EF0) && Char%2 == 0 )
        {
        Char = 0x01AF; // U-horn        
        return Char; 
        }         
     if ( ((Char >= 0x1EF2 && Char <= 0x1EF8) && Char%2 == 0) || Char == 0x00DD ) 
        {
        Char = 0x0059; // Y
        return Char; 
        }              
    return Char;
    } 
    
 /**
 * Checks current character is it special character from Vietnamese language . 
 *
 * @since 5.0
 * @return @c ETrue If it is accent from Vietnamese language, otherwise EFalse. 
 */	
inline TBool IsVietnameseSpecialCharacter( TChar aCh )
    {  
    if ( ( aCh >= 0x0300 && aCh <= 0x0303 ) || aCh == 0x0306 ||     
           aCh == 0x0309 || aCh == 0x0323 || aCh == 0x031B )
            {
            return ETrue;            
            }
     return EFalse;
    }
  
// ---------------------------------------------------------------------------
// Checks the current character for special character from Thai language . 
// ---------------------------------------------------------------------------
inline TBool IsThaiSpecialCharacter( TChar aCh )
    {    
    if( ( aCh > 0xE46 && aCh < 0xE4F ) ||  aCh == 0xE3A )
		{
		return ETrue;
		}       
	return EFalse;
    }
  
// ---------------------------------------------------------------------------
// IsAdaptiveFindMatch
// ---------------------------------------------------------------------------
//
EXPORT_C TBool AknFind::IsAdaptiveFindMatch( const TDesC& aItemText, 
										     const TDesC& aSearchText,
 										 	 HBufC*& aNextChars )
	{	
	HBufC16* searchText( NULL );
	TRAPD( error, searchText = HBufC16::NewL( KMatchingBufferLength ) );
	if ( error == KErrNone )
	    {
	    TInt itemStringLength = aItemText.Length();
        TInt searchTextLength = aSearchText.Length();    
        
        if ( searchTextLength < KMatchingBufferLength )
        	{
        	searchText->Des().Append( aSearchText );
        	}
        else
        	{
        	searchText->Des().Append( aSearchText.Left(KMatchingBufferLength-1) );
        	}    
    	
        searchText->Des().Append( KLitStar );
            
        TInt all_result = KErrNotFound;
        for( TInt i = 0; i < itemStringLength; i++ )
            {
            if ( i==0 || IsFindWordSeparator( aItemText[i-1] ) )
                {
                TInt result = aItemText.Mid(i).MatchC( searchText->Des() );
                
                if( result != KErrNotFound ) 
                    {
                    all_result = result;
                    if( i < (itemStringLength-searchTextLength) )                	   	       	   		
                        {                 
                	   	 if( !(IsThaiSpecialCharacter(aItemText[i+searchTextLength])) && !(IsVietnameseSpecialCharacter( aItemText[i+searchTextLength]) ))
                                {
                                TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemText[i+searchTextLength]) );   
                                }   
                        }
                    }                                                                  	   	
                } // if (i==0 ..)        
      	    } // for	 
	    
  	    if( all_result != KErrNotFound )
            {
            delete searchText;
            return ETrue;
           	}    
        else 
            {
            delete searchText;
            return EFalse;
            }
        	            		
         } // if (error == KErrNone)   

    delete searchText;                 
    return EFalse;
	}
	

/**
 * For Devanagari AS
 * Checks if the passed string denotes one of the four special
 * Devanagari ligatures - refer UI specs for the description of special ligatures
 * @param aCharString - The string containing set of characters to be checked
 * @return ETrue if a special ligature is found EFalse otherwise.    
 */
inline TBool IsSpecialIndicLigature(const TDesC& aCharString )
    {
    TBool ret = EFalse;
    if( aCharString.Length() >= 3 )
     {
        //First check for Devanagari special ligatures
        if(
            ( ( (aCharString[0] == 0x915) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x937) ) ||
              ( (aCharString[0] == 0x91C) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x91E) ) ||
              ( (aCharString[0] == 0x936) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x930) ) ||
              ( (aCharString[0] == 0x924) && (aCharString[1] == 0x94D)&& (aCharString[2] == 0x930) )  ))            
            {
            ret = ETrue;
            }       
        }
    return ret;
    }

/**
 * For Devanagari AS
 * Checks if the given character is a Indic consonant. 
 * @param aSearchChar - Character to be checked.  
 * @return ETrue if this is an independent character EFalse otherwise.           
 */
inline TBool IsIndicConsonant(const TChar aSearchChar)
    {    
    if  (
        ( aSearchChar >= 0x0915 && aSearchChar <= 0x0939 ) 
        || ( aSearchChar >= 0x0958 && aSearchChar <= 0x0961 )
        )
        {
        return ETrue;
        }
    else 
        {
        return EFalse;
        }
    }


/**
 * For Devanagari AS
 * Checks if aCh denotes a consonant with nukta. 
 * @param aCh - character to be checked
 * @return ETrue if aCh is a consonant with nukta EFalse otherwise.
 */
inline TBool IsIndicCombinedChar( const TChar aCh )
    {   
    if ( aCh < 0x0900 || aCh > 0x0980 )
        {
        return EFalse;
        }
    else
        {
        return ( aCh == 0x0929 || aCh == 0x0931 
                || aCh == 0x0934 || (aCh >= 0x0958 && aCh <= 0x095F) );
        }
    }

/**
 * For Devanagari AS
 * This is to check if the character can be displayed on the 
 * adaptive search grid or not. 
 * @param aCh character to be displayed on adaptive search grid
 * @return ETrue if the character is valid for AS Grid EFalse otherwise.    
 */
TBool inline IsValidCharForASGrid(TChar aCh)
    {
    //first check for Devanagari character range. 
    if ( aCh < 0x0900 || aCh > 0x0980 )
        {
        return ETrue;
        }
    else 
        {
        return (
        !( (aCh >= 0x0901 && aCh <= 0x0903) || //Devanagari modifier
           (aCh >= 0x093C && aCh <= 0x094D) //Devanagari dependent vowels
         ) );
        }
    }


/**
 * For Devanagari AS
 * Returns the correcponding character without nukta
 * @param aCh - character to be stripped of nukta * 
 * @return corresponding character with nukta
 */
inline TChar RemoveIndicNukta( const TChar aCh )
    {
    switch (aCh)
        {
        case 0x0929 : return 0x0928; //vocallic 'nna' to 'na'
        case 0x0931 : return 0x0930; //vocallic 'rra' to 'ra'
        case 0x0934 : return 0x0933; //vocallic 'lllla' to 'lla'
        case 0x0958 : return 0x0915; //vocallic 'qa' to 'ka'
        case 0x0959 : return 0x0916; //vocallic 'khha' to 'kha'
        case 0x095A : return 0x0917; //vocallic 'ghha' to 'ga'
        case 0x095B : return 0x091C; //letter 'za' to 'ja'
        case 0x095C : return 0x0921; //vocallic 'dddha' to 'da'
        case 0x095D : return 0x0922; //vocallic 'rha' to 'ddha'
        case 0x095E : return 0x092B; //letter 'fa' to 'pha'
        case 0x095F : return 0x092F; //letter 'yya' to 'ya'
        
        default : return aCh;
        }
    }


// -----------------------------------------------------------------------------
// For Devanagari AS
// Checks if the last character entered is a Indic halant character.
// @param aCh - character to be checked  
// @return ETrue if this is a halant character EFalse otherwise 
// -----------------------------------------------------------------------------
inline TBool IsIndicHalantChar(const TChar aCh)
    {    
    return ( aCh == 0x094D );
    }

// ---------------------------------------------------------------------------
// For Devanagari AS
// AknFind::UpdateNextCharsL
// ---------------------------------------------------------------------------
//
void AknFind::UpdateNextCharsL( HBufC*& aNextChars, const TDesC& aItemString )
	{
	_AKNTRACE_FUNC_ENTER;
	TChar searchChar = aItemString[0];
	    //Check if this is an Indic special ligature
	    if ( IsIndicConsonant(searchChar) && aItemString.Length() > 2
	            && IsSpecialIndicLigature(aItemString) 
	            && KErrNotFound == (*aNextChars).Find(aItemString.Mid(0,3)) )
	        {
	        //Check if we have enough space for 3 more characters
	        if( aNextChars->Des().Length() >= aNextChars->Des().MaxLength()-3 )
	            {
	            aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
	            TInt length1 = aNextChars->Des().Length();
	            TInt maxlength1 = aNextChars->Des().MaxLength();
	            }       
	        aNextChars->Des().Append( aItemString.Mid(0,3) );        
	        }
	    else
	        {
	        if ( !IsValidCharForASGrid(searchChar) ) 
	            {
	            return;	            
	            }
	        //check if this is an Indic combined Char
	        if ( IsIndicCombinedChar(searchChar) )
	            {
	            searchChar = RemoveIndicNukta( searchChar );
	            }
	        //Now update the nextChars string
            TInt strLength = aNextChars->Length();
            for ( TInt i(0); i < strLength ; ++i )
                {
                if ( IsSpecialIndicLigature( (*aNextChars).Mid(i) ) )
                    {
                    //As aItemString is not a special ligature (checked above)
                    //we can move directly to the 3rd character from here
                    i+=2;
                    continue;
                    }
                else if ( searchChar.GetUpperCase() == (*aNextChars)[i] ||
                            searchChar.GetLowerCase() == (*aNextChars)[i] )
                    {
                    //already exists - do nothing
                    return;
                    }
                //else continue the loop
                }
            //So this character is not yet in the list of nextChars.
            if( aNextChars->Des().Length() == aNextChars->Des().MaxLength() )
                {
                aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
                }       
            aNextChars->Des().Append( searchChar );   
	        }
	    _AKNTRACE_FUNC_EXIT;
	}

// -----------------------------------------------------------------------------
// AknFind::UpdateNextCharsL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
void AknFind::UpdateNextCharsL( HBufC*& aNextChars, TChar aCh )
    {
    TChar ch_temp = aCh;  
    aCh = ReplaceVietnameseChar ( ch_temp );      
    if( ( aNextChars->Locate(aCh.GetLowerCase() ) == KErrNotFound ) &&
        ( aNextChars->Locate(aCh.GetUpperCase() ) == KErrNotFound ) )
        {               
        if( aNextChars->Des().Length() == aNextChars->Des().MaxLength() )
            {
            aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
            TInt length1 = aNextChars->Des().Length();
            TInt maxlength1 = aNextChars->Des().MaxLength();
            }       
        aNextChars->Des().Append( aCh );            
        }
    }

// ---------------------------------------------------------------------------
// UpdateNextCharsFromString
// ---------------------------------------------------------------------------
//
EXPORT_C void AknFind::UpdateNextCharsFromString( HBufC*& aNextChars, const TDesC& aItemString )
	{
	TInt itemStringLength = aItemString.Length();
	     
	for( TInt i = 0; i < itemStringLength; i++ )
	    {
	    if ( i == 0 || IsFindWordSeparator( aItemString[i-1] ) )
	        {  
	        // If Indic letter
	        if ( aItemString[i] >= 0x0900 && aItemString[i] <= 0x0980 )
	            {
	            TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString.Mid(i) ) );
	            }
	        else  if (!(IsVietnameseSpecialCharacter( aItemString[i])))
	            {
	            TRAP_IGNORE( UpdateNextCharsL( aNextChars, aItemString[i] ) );
	            }
	        }
	    }
	}

// ---------------------------------------------------------------------------
// UpdateItemTextAccordingToFlag
// ---------------------------------------------------------------------------
//
EXPORT_C void AknFind::UpdateItemTextAccordingToFlag( const TDesC& aInputText, 
                                                      TBitFlags32 aColumnFlag, 
                                                      TDes& aOutText )
    {
    TInt MaxColumn = 32; 
    TPtrC tmptext;   
    for ( TInt column=0; column<MaxColumn; column++ )
        {
        if ( aColumnFlag.IsSet( column ) )
            {
            if( KErrNone == TextUtils::ColumnText(tmptext, column, &aInputText, KLitTab) )
                {  
                aOutText.Append( tmptext );
                aOutText.Append( KLitSpace );
                }
            else 
                {
                // no more columns
                column = MaxColumn;
                }
            }
        }
    // remove the last added space
    TInt deleteTrailingSpace = aOutText.Length() - 1;
    if( deleteTrailingSpace > 0 )
        {
        // delete the trailing whitespace
        aOutText.Delete( (aOutText.Length()-1), 1 ); 
        }        
    aOutText.UpperCase(); 
    }   
    
    

EXPORT_C
TKeyResponse AknFind::HandleFindOfferKeyEventL( const TKeyEvent &aKeyEvent,
                                                TEventCode aType,
                                                CCoeControl * /*aListBoxParent*/,
                                                CEikListBox *aListBox,
                                                CAknSearchField *aSearchField,
                                                TBool ispopup,
                                                TBool &aNeedRefresh )
    {
    if (aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }
    
    if (aKeyEvent.iCode == '#')
        {
        return EKeyWasNotConsumed;
        }        
        
    aNeedRefresh = EFalse;

    if (!aSearchField || !aListBox)
        {
        return EKeyWasNotConsumed;
        }


    TBool removePopup = EFalse;
    
    /* THE case where normal letters come from keyboard */
    TKeyResponse result = EKeyWasNotConsumed;
    TBuf<256> criteria;
    aSearchField->GetSearchText(criteria);
    TInt oldlength = criteria.Length();

    if ( !aSearchField->IsVisible() && oldlength == 0 )
        {
        aSearchField->SetOldItemIndex( aListBox->CurrentItemIndex() );
        }
    
    // EHLI-7PKBEJ Old code just support ITUT keypad... now we extend it
    // to QWERTY keyboard.
    if ( aSearchField->IsVisible() == EFalse && ispopup && oldlength == 0
         && TChar(aKeyEvent.iCode).IsPrint())
        {
        aSearchField->SetFocus(ETrue);
        aSearchField->MakeVisible(ETrue);
        
        ((CAknFilteredTextListBoxModel*)aListBox->Model())->Filter()->DeferredSendFullKeyEventToFepL(aKeyEvent);
        
        aNeedRefresh = ETrue;
        return EKeyWasConsumed;
        }
    
    if ( aSearchField->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
        {
        result = EKeyWasConsumed;
        }
    
    ((CAknFilteredTextListBoxModel*)aListBox->Model())->Filter()->HandleOfferkeyEventL();

    // remove popup if search criteria is empty and backspace is pressed
    if ( aSearchField->IsVisible() && ispopup
         && aKeyEvent.iCode == EKeyBackspace && oldlength == 0 )
        {
        removePopup = ETrue;
        TInt olditem = aSearchField->OldItemIndex();
        if ( olditem >= 0 )  // when list is empty, olditem is -1
            {
            aListBox->SetCurrentItemIndex( olditem );
            }
        }
    HandleFindPaneVisibility(aSearchField, ispopup, !removePopup, aNeedRefresh);
    return result;
    }  


EXPORT_C void CAknFilteredTextListBoxModel::CreateFilterL(CEikListBox *aListBox, CAknSearchField *aSearchField)
    {
    __ASSERT_DEBUG(iFilter==0, Panic(EAknPanicOutOfRange));
    iFilter = new(ELeave) CAknListBoxFilterItems(aListBox, aSearchField,this, aListBox->View());
    iFilter->ConstructL();
    }
EXPORT_C void CAknFilteredTextListBoxModel::RemoveFilter()
    {
    delete iFilter;
    iFilter = NULL;
    }

EXPORT_C CAknListBoxFilterItems *CAknFilteredTextListBoxModel::Filter() const
    {
    return iFilter;
    }


EXPORT_C const MDesCArray *CAknFilteredTextListBoxModel::MatchableTextArray() const {return this; }

EXPORT_C TInt CAknFilteredTextListBoxModel::MdcaCount() const
    {
    return ItemTextArray()->MdcaCount();
    }

EXPORT_C TPtrC CAknFilteredTextListBoxModel::MdcaPoint(TInt aIndex) const
    {
    if (iFilter)
    return iFilter->DefaultMatchableItemFromItem(ItemTextArray()->MdcaPoint(aIndex));
    else
    return ItemTextArray()->MdcaPoint(aIndex);                            
    }

EXPORT_C CAknFilteredTextListBoxModel::~CAknFilteredTextListBoxModel()
    {
    delete iFilter;
    }

EXPORT_C TInt CAknFilteredTextListBoxModel::NumberOfItems() const
    {
    return iFilter ? iFilter->FilteredNumberOfItems() : CTextListBoxModel::NumberOfItems();
    }

EXPORT_C TPtrC CAknFilteredTextListBoxModel::ItemText(TInt aItemIndex) const
    {
    return CTextListBoxModel::ItemText(iFilter? iFilter->FilteredItemIndex(aItemIndex) : aItemIndex);
    }

EXPORT_C TAny*  CAknFilteredTextListBoxModel::MListBoxModel_Reserved() 
    {
    return NULL;
    }

class CFindExtension : public CBase
    {
public:
    CIdle* iIdle;
    CFindUtil* iFindUtil;
    HBufC16* iNextChars; // for adaptive search    
    HBufC* iDigraphChars;  
    TKeyEvent iKeyEvent;

    };

EXPORT_C void CAknListBoxFilterItems::DeferredSendKeyEventToFepL(TUint aValue)
    {
    __ASSERT_DEBUG(iKeyValue == 0, Panic(EAknPanicOutOfRange));
    if (iExtension)
        {
        iExtension->iKeyEvent.iCode = aValue;
        iExtension->iKeyEvent.iScanCode = aValue;
        if ( iExtension->iIdle )
            {
            delete iExtension->iIdle;
            iExtension->iIdle = 0;
            }
        iExtension->iIdle = CIdle::New(-20);
        if (iExtension->iIdle)
            {
            iExtension->iIdle->Start(TCallBack(IdleCallBack, this));
            }
        }
    }

void CAknListBoxFilterItems::DeferredSendFullKeyEventToFepL( 
    const TKeyEvent& aEvent )
    {
    if ( iExtension )
        {
        iExtension->iKeyEvent = aEvent;
        if ( iExtension->iIdle )
            {
            delete iExtension->iIdle;
            iExtension->iIdle = 0;
            }
        iExtension->iIdle = CIdle::New(-20);
        if ( iExtension->iIdle )
            {
            iExtension->iIdle->Start( TCallBack( IdleCallBack, this));
            }
        }
    }

TInt CAknListBoxFilterItems::IdleCallBack(TAny *aFilterItems)
    {
    TInt err = KErrNone;
    CAknListBoxFilterItems *items = 
        static_cast<CAknListBoxFilterItems*>(aFilterItems);
    if ( items->iExtension )
        {
        TKeyEvent& event(items->iExtension->iKeyEvent);
        CCoeEnv *coeEnv = CCoeEnv::Static();
        // THE PART THAT COMMUNICATES WITH FEP.
        TRAP_IGNORE(
            {
            coeEnv->SimulateKeyEventL(event,EEventKeyDown);
            coeEnv->SimulateKeyEventL(event,EEventKey);
            coeEnv->SimulateKeyEventL(event,EEventKeyUp);
            }
            );
        delete items->iExtension->iIdle;
        items->iExtension->iIdle = 0;
        }
    else
        {
        err = KErrArgument;
        }
    return err;
    }

EXPORT_C CAknListBoxFilterItems::CAknListBoxFilterItems(CEikListBox *aListBox, CAknSearchField *aSearchField, MListBoxModel *aModel, CListBoxView *aView) 
    : iModel(aModel), iView(aView), iListBox(aListBox), iSearchField(aSearchField)
    {
    }

EXPORT_C void CAknListBoxFilterItems::SetParentControl(CCoeControl *aControl)
    {
    iParentControl = aControl;
    }

EXPORT_C void CAknListBoxFilterItems::SetPopup()
    {
    iIsPopup = ETrue;
    }

EXPORT_C void CAknListBoxFilterItems::SetListBox(CEikListBox *aListBox)
    {
    iListBox = aListBox;
    }

EXPORT_C void CAknListBoxFilterItems::SetSearchField(CAknSearchField *aSearchField)
    {
    iSearchField = aSearchField;
    if (iSearchField)
        iSearchField->SetObserver(this);
    }

EXPORT_C void CAknListBoxFilterItems::SetModel(MListBoxModel *aModel)
    {
    iModel = aModel;
    }

EXPORT_C void CAknListBoxFilterItems::SetView(CListBoxView *aView)
    {
    iView = aView;
    }

EXPORT_C CCoeControl *CAknListBoxFilterItems::FindBox() const
    {
    return iSearchField;
    }

EXPORT_C void CAknListBoxFilterItems::ConstructL()
    {
    __ASSERT_DEBUG(iShownIndexes==0, Panic(EAknPanicOutOfRange));
    iShownIndexes = new(ELeave) CArrayFixFlat<TInt>(5);
    iSelectionIndexes = new(ELeave) CArrayFixFlat<TInt>(5);
    iOldSearchCriteria = _L("").AllocL();    
    iExtension = new(ELeave)CFindExtension;
    
    // Returns NULL if findutil not supported
    iExtension->iFindUtil = CFindUtil::NewL();    
    
    iExtension->iNextChars = HBufC16::NewL( 10 );    
    iExtension->iDigraphChars = StringLoader::LoadL( R_QTN_ADS_DIGRAPH );; 
        
    NoCriteriaL();
    HandleItemAdditionL();  
    if (iSearchField)
        iSearchField->SetObserver(this);

    const MDesCArray *array = iModel->MatchableTextArray();
    iOldItemCount = array->MdcaCount();   
    }

EXPORT_C CAknListBoxFilterItems::~CAknListBoxFilterItems()
    {
    if (iExtension)
        {
        delete iExtension->iIdle;
        delete iExtension->iFindUtil;
        delete iExtension->iNextChars;
        delete iExtension->iDigraphChars;
        delete iExtension;        
        }
    delete iShownIndexes;
    delete iSelectionIndexes;
    delete iOldSearchCriteria;    
    delete iEmptyListText;    
    }

EXPORT_C void CAknListBoxFilterItems::HandleItemArrayChangeL()
    {
    HBufC16* newcriteria = HBufC16::NewL( KMatchingBufferLength ); 
    TPtr ptr_newcriteria( newcriteria->Des() );    
    
    if ( iSearchField )
        {
        iSearchField->GetSearchText( ptr_newcriteria );
        }

    CleanupStack::PushL( newcriteria );
    ReleaseCriteriaL( ptr_newcriteria );

    delete iOldSearchCriteria;
    iOldSearchCriteria = NULL;
    iOldSearchCriteria = newcriteria->Des().AllocL();

    CleanupStack::PopAndDestroy ( newcriteria );
    // We should redraw the listbox
    HandleItemAdditionL();  // calls DrawDeferred()

   // If adaptive search manage with next characters
    if( iSearchField && IsAdaptiveSearch() )
        {
        // Handles filtering
        
        // Clear next characters
        ClearNextChars();
        TBitFlags32 columnFlag = iSearchField->ListColumnFilterFlags();
                
        HBufC16* temptext = HBufC16::NewL( KMatchingBufferLength );    
        TPtr ptr_temptext( temptext->Des() );    
        CleanupStack::PushL( temptext );
        const MDesCArray *array = iModel->MatchableTextArray();
        const CAknFilteredTextListBoxModel* arr = (CAknFilteredTextListBoxModel*)(iModel->MatchableTextArray());
        
        for ( TInt i = iShownIndexes->Count()-1; i>=0; i-- )
            {           
            TPtrC itemtext = arr->ItemText( i );   
            AknFind::UpdateItemTextAccordingToFlag( itemtext, columnFlag, ptr_temptext );

            // this need to be done for update next characters for AdaptiveGrid
            // ESMG-7LKAE4, use FindUtil is slow, but it is necessary for Chinese
            if ( AknLayoutUtils::Variant() == EApacVariant )
                {
                iExtension->iFindUtil->Interface()->MatchAdaptiveRefineL(
                    ptr_temptext, KNullDesC, iExtension->iNextChars);
                }
            else
                {
                AknFind::UpdateNextCharsFromString( iExtension->iNextChars, temptext->Des() );
                }
            ptr_temptext.Zero(); 
            }
        iSearchField->SetAdaptiveGridChars( *(iExtension->iNextChars) ); 
        CleanupStack::PopAndDestroy ( temptext );
        }
    iOldItemCount = iModel->MatchableTextArray()->MdcaCount(); 
    if ( iOldItemCount>0 && iListBox ) 
        {
        iListBox->SetCurrentItemIndex(0);  
        }       
    }  

    
/** 
 * Editor sends messages to this object as control events. 
 */
EXPORT_C void CAknListBoxFilterItems::HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType)
    {
    TBool refresh = EFalse;
    switch(aEventType)
    {
    case EEventStateChanged:
        if (iParentControl)
            {
            HandleOfferkeyEventL();
        if (iSearchField)
                {
                AknFind::HandleFindPaneVisibility(iSearchField, iIsPopup, ETrue, refresh);
                }
            if (refresh)
                {
                if (iListBox)
                    {
                    if (iIsPopup)
                        {
                        AknFind::HandlePopupFindSizeChanged(iParentControl, iListBox, iSearchField);
                        }
                    else
                        {
                        AknFind::HandleFixedFindSizeChanged(iParentControl, (CAknColumnListBox*)iListBox, iSearchField);
                        }
                    }
                    iParentControl -> DrawDeferred();
                }
            }
        break;
    default:
        break;
    }
    if (iObserver) iObserver->HandleControlEventL(aControl, aEventType);
    }

void CAknListBoxFilterItems::HandleItemAdditionL()
    {
    iDisableChangesToShownIndexes = ETrue;
    if (iListBox) 
        {
        TRAP_IGNORE(iListBox->HandleItemAdditionL());
        }
    iDisableChangesToShownIndexes = EFalse;
    }

void CAknListBoxFilterItems::HandleItemRemovalL()
    {
    iDisableChangesToShownIndexes = ETrue;
    if (iListBox) 
        {
    TRAP_IGNORE(iListBox->HandleItemRemovalL());
    }
    iDisableChangesToShownIndexes = EFalse;
    }

EXPORT_C void CAknListBoxFilterItems::SetObserver(MCoeControlObserver *aObserver)
    {
    iObserver = aObserver;
    }

EXPORT_C void CAknListBoxFilterItems::HandleOfferkeyEventL()
    {
    if (!iOldSearchCriteria)
        {
        // This can happen if we have leaved on one of our AllocL()'s and the application resumes the execution.
        // Thus, we'll leave and feel safe later in this method to use iOldSearchCriteria without checking it.
        iOldSearchCriteria = _L("").AllocL(); // try to resume to valid state...
        User::Leave(KErrNoMemory);
        }
    //
    // NOTE! Order of calls to iListBox is important in this method.
    // The SetCurrentItemIndex(0) call MUST be before HandleItemAdditionL()
    // and handleitemremovalL() calls.
    //
    // Check if search string has changed.
    TBuf<256> newcriteria;
    if (iSearchField)
        iSearchField->GetSearchText(newcriteria);

    // Check if item count has changed.
    const MDesCArray *array = iModel->MatchableTextArray();
    if (array->MdcaCount() != iOldItemCount)
        {
        ReleaseCriteriaL(newcriteria);
        if (newcriteria.Compare(*iOldSearchCriteria) != 0 && iShownIndexes->Count()>0) 
            { 
            if (iListBox)
                iListBox->SetCurrentItemIndex(0);
            }
        HandleItemAdditionL();
        iOldItemCount = array->MdcaCount();
        } 
    else
       {    
        if (newcriteria.Compare(*iOldSearchCriteria) == 0) return;
        if (iShownIndexes->Count()>0) 
            if (iListBox)
                iListBox->SetCurrentItemIndex(0);
        
        FetchSelectionIndexesFromListBoxL();
        if (newcriteria.Length() == 0)
            {
            NoCriteriaL();
            HandleItemAdditionL();
            } 
        else if ( newcriteria.Length() > (*iOldSearchCriteria).Length() && 
                 newcriteria.Find(*iOldSearchCriteria) == 0 )
            {
            TightenCriteriaL(newcriteria);
            HandleItemRemovalL();
            }
        else
            {
            ReleaseCriteriaL(newcriteria);
            HandleItemAdditionL();
            }
        PushSelectionIndexesToListBoxL();
        }
        
        delete iOldSearchCriteria;
        iOldSearchCriteria = NULL;
        iOldSearchCriteria = newcriteria.AllocL();
        if (iListBox)   
            iListBox->DrawDeferred();
    }


EXPORT_C TPtrC CAknListBoxFilterItems::DefaultMatchableItemFromItem( TPtrC aText )
    {   
    // This implementation requirescolumnlistbox or formattedcelllistbox itemdrawer/data..    
    iMatchableText = aText.Left(Min(aText.Length(), iMatchableText.MaxLength()-1));
    AknTextUtils::ReplaceCharacters(iMatchableText, KAknReplaceListControlChars, TChar(' '));
    _LIT(KSpace," ");
    AknTextUtils::PackWhiteSpaces(iMatchableText, KSpace);
    
    if ( iMatchableText.Length() && iMatchableText[0] == ' ' )
        {
        // remove one space if its at beginning of the string.
        iMatchableText = iMatchableText.Mid(1);
        }    
    return iMatchableText;
    }

EXPORT_C TInt CAknListBoxFilterItems::FilteredNumberOfItems() const
    {
    return iShownIndexes->Count();
    }

EXPORT_C TInt CAknListBoxFilterItems::FilteredItemIndex(TInt aVisibleItemIndex) const
    {
    return iShownIndexes->At(aVisibleItemIndex);
    }

EXPORT_C TInt CAknListBoxFilterItems::VisibleItemIndex(TInt aOriginalIndex) const
    {
    TKeyArrayFix key(0, ECmpTInt);
    TInt pos;
    if (!(iShownIndexes->Find(aOriginalIndex, key,pos)))
    return pos; // found
    else
    return -1; // not found    
    }

EXPORT_C CArrayFix<TInt> *CAknListBoxFilterItems::SelectionIndexes()
    {
    return iSelectionIndexes;
    }

EXPORT_C void CAknListBoxFilterItems::UpdateSelectionIndexesL()
    {
    FetchSelectionIndexesFromListBoxL();
    }

EXPORT_C void CAknListBoxFilterItems::UpdateSelectionIndexL(TInt aVisibleIndex)
    {
    if (!iView) return;
    TInt realindex = FilteredItemIndex(aVisibleIndex);
    if (!iView->ItemIsSelected(aVisibleIndex))
        { 
        // Not selected - remove the item from selection indexes if it still exists there.
        TKeyArrayFix key(0, ECmpTInt);
        TInt pos;
        if (!(iSelectionIndexes->Find(realindex, key,pos)))
            {
            iSelectionIndexes->Delete(pos);
            }
        }
    else
        { // Selected -- add the item to seletion indexes if it didnt exists there yet
        TKeyArrayFix key(0,ECmpTInt);
        TInt pos;
        if (iSelectionIndexes->Find(realindex, key, pos))
            {
            iSelectionIndexes->AppendL(realindex);
            }
        }
    }

EXPORT_C TInt CAknListBoxFilterItems::NonFilteredNumberOfItems() const
    {
    if (iModel->MatchableTextArray())
        return iModel->MatchableTextArray()->MdcaCount();
    else 
        return iModel->NumberOfItems();
    }

void CAknListBoxFilterItems::InstallEmptyTextL()
    {
    if (iEmptyListText) return; // Do not install, if we have one already
    if (!iListBox ||!iListBox->View()) return; // Do not install, if we do not have listbox yet.
 
    iEmptyListText = iListBox->View()->EmptyListText()->AllocL();
    TResourceReader rr;
    CEikonEnv::Static()->CreateResourceReaderLC(rr, R_AVKON_FIND_NO_MATCHES);
    TPtrC ptr = rr.ReadTPtrC();
    if (iListBox && iListBox->View())
        iListBox->View()->SetListEmptyTextL(ptr);
    CleanupStack::PopAndDestroy(); // resourcereader rr
    }

void CAknListBoxFilterItems::UninstallEmptyTextL()
    {
    if (!iEmptyListText) return;
    if (!iListBox || !iListBox->View()) return;
    iListBox->View()->SetListEmptyTextL(iEmptyListText->Des());
    delete iEmptyListText;
    iEmptyListText = 0;
    }

void CAknListBoxFilterItems::FetchSelectionIndexesFromListBoxL()
    {
    // go through all visible items, and update 
    //the iSelectionIndexes (of this class, not listbox) to match
    // with all visible item selection states!
    TInt count = FilteredNumberOfItems();
    for(TInt i=0; i<count; i++)
        {
        UpdateSelectionIndexL(i);
        }
    }

void CAknListBoxFilterItems::PushSelectionIndexesToListBoxL()
    {
    if (!iView) return;
    // Builds a new selection indexes table for list based on 
    // new iShownIndexes and iSelectionIndexes
    // Go through all visible items and determine if they've been selected
    TInt count = FilteredNumberOfItems();
    for( TInt i=0; i<count; i++ )
        {
        TInt realindex = FilteredItemIndex(i);
        TKeyArrayFix key(0,ECmpTInt);
        TInt pos;
        if ( iSelectionIndexes->Find(realindex,key,pos) )
            iView->DeselectItem(i);
        else
            iView->SelectItemL(i);
        }  
    }

EXPORT_C void CAknListBoxFilterItems::ResetFilteringL()
    {
    if (iDisableChangesToShownIndexes) return;
    
    // needs to be done or selections go broken.
    FetchSelectionIndexesFromListBoxL(); 

    delete iOldSearchCriteria;
    iOldSearchCriteria = NULL;
    iOldSearchCriteria = _L("").AllocL();

    NoCriteriaL();
    // needs to be done or scrollbar crashes
    HandleItemAdditionL(); 
    PushSelectionIndexesToListBoxL();
    }

EXPORT_C void CAknListBoxFilterItems::UpdateCachedDataL()
    {
    TBuf<256> newcriteria;
    if (iSearchField)
        iSearchField->GetSearchText(newcriteria);

    delete iOldSearchCriteria;
    iOldSearchCriteria = NULL;
    iOldSearchCriteria = newcriteria.AllocL();

    FetchSelectionIndexesFromListBoxL();
    }


void CAknListBoxFilterItems::NoCriteriaL(TBool aUpdateAS)
    {
    if (iDisableChangesToShownIndexes) return;
    // Handles filtering
    TInt count =0; 
    if (iModel->MatchableTextArray()) 
        count = iModel->MatchableTextArray()->MdcaCount();
    else
        count = iModel->NumberOfItems();

    iShownIndexes->Reset();
        
    const MDesCArray *array = iModel->MatchableTextArray();
    const CAknFilteredTextListBoxModel* arr = (CAknFilteredTextListBoxModel*)(iModel->MatchableTextArray());
    
    // If adaptive search manage with next characters
    if( iSearchField && IsAdaptiveSearch() )
        {
        ClearNextChars();
        TBitFlags32 columnFlag = iSearchField->ListColumnFilterFlags();
        HBufC* temptext = HBufC::NewL( KMatchingBufferLength ); 
        CleanupStack::PushL( temptext );
        TPtr ptr_temptext( temptext->Des() );  

        for( TInt i = 0; i < count; i++ )
            {           
            TPtrC itemtext = arr->ItemTextArray()->MdcaPoint(i);
            AknFind::UpdateItemTextAccordingToFlag( itemtext, columnFlag, ptr_temptext );
 
            // this need to be done for update iNextChars for AdaptiveGrid
            // ESMG-7LKAE4, use FindUtil is slow, but it is necessary for Chinese
            if ( AknLayoutUtils::Variant() == EApacVariant )
                {
                iExtension->iFindUtil->Interface()->MatchAdaptiveRefineL(
                    ptr_temptext, KNullDesC, iExtension->iNextChars);
                }
            else
                {
                AknFind::UpdateNextCharsFromString( iExtension->iNextChars, temptext->Des() );
                }
            iShownIndexes->AppendL( i );
            ptr_temptext.Zero(); 
            }
        if( aUpdateAS )
            {
            TPtr nextChars = iExtension->iNextChars->Des(); 
            CDesCArray* array = new (ELeave) CDesCArrayFlat(10);
            CleanupStack::PushL(array);
            
            TInt length = nextChars.Length();                 
            TInt count(0);      
              
            for( TInt i = 0; i < length; i++ )
                {
                if ( (i < length-2) && IsIndicHalantChar( nextChars[i+1] ) )
                   {
                   array->AppendL( nextChars.Mid(i,3) );
                   i+=2;
                   ++count;
                   }
               else
                   {
                   array->AppendL( nextChars.Mid(i,1) );
                   ++count;
                   }
                }  
            
            // Alphabetical sort        
            array->Sort( ECmpCollated );
            nextChars.Delete( 0, nextChars.Length() );

            for( TInt i = 0; i < count; i++ )
                {
                nextChars.Append(array->MdcaPoint(i));
                }  
            CleanupStack::PopAndDestroy(array);   
            
            iSearchField->SetAdaptiveGridChars( *(iExtension->iNextChars) );
            }
        CleanupStack::PopAndDestroy( temptext );   
        }
    else
        {
        for( TInt i = 0; i < count; i++ )
            {
            iShownIndexes->AppendL( i );
            }           
        }   

    // empty text
    UninstallEmptyTextL();
    }

void CAknListBoxFilterItems::TightenCriteriaL(const TDesC &aCriteria)
    {
    if (iDisableChangesToShownIndexes) 
        {
        return;
        }
    // This loop goes backwards to avoid changing the indexes in the shownindexes list before we need them
    const MDesCArray *array = iModel->MatchableTextArray();    
    const CAknFilteredTextListBoxModel* arr = (CAknFilteredTextListBoxModel*)(iModel->MatchableTextArray());    
    
    // If adaptive search manage with next characters
    if ( iExtension->iDigraphChars->Length() != 0 )
        {
        NoCriteriaL( EFalse );
        }
    
    // an index to end of array
    TInt indexEnd = iShownIndexes->Count();
    // If adaptive search manage with next characters
    if( iSearchField && IsAdaptiveSearch() )
        {        
        ClearNextChars();
        TBitFlags32 columnFlag = iSearchField->ListColumnFilterFlags(); 
        HBufC16* temptext = HBufC16::NewL( KMatchingBufferLength );  
        CleanupStack::PushL( temptext );  
        TPtr ptr_temptext( temptext->Des() );  
        for ( TInt i = iShownIndexes->Count()-1; i>=0; i-- )
           {
           TInt realindex = iShownIndexes->At( i );        
           TPtrC itemtext = arr->ItemTextArray()->MdcaPoint(realindex);
           AknFind::UpdateItemTextAccordingToFlag( itemtext, columnFlag, ptr_temptext );
           TBool isItemVisible = IsItemVisible(ptr_temptext, aCriteria);
           TBool isItemSelected = IsItemSelected(realindex);
           // set it as current index when found item
           if ( isItemVisible )
               {        
               indexEnd = iShownIndexes->Count() - i;
               }
           else if ( !(isItemVisible || isItemSelected) )
                {
                iShownIndexes->Delete(i);
                }
            ptr_temptext.Zero();    
            }           
   
        TPtr nextChars = iExtension->iNextChars->Des(); 
        CDesCArray* array = new (ELeave) CDesCArrayFlat(10);
        CleanupStack::PushL(array);
        
        TInt length = nextChars.Length();                 
        TInt count(0);      
          
        for( TInt i = 0; i < length; i++ )
            {
            if ( (i < length-2) && IsIndicHalantChar( nextChars[i+1] ) )
               {
               array->AppendL( nextChars.Mid(i,3) );
               i+=2;
               ++count;
               }
           else
               {
               array->AppendL( nextChars.Mid(i,1) );
               ++count;
               }
            }  
        
        // Alphabetical sort        
        array->Sort( ECmpCollated );
        nextChars.Delete( 0, nextChars.Length() );

        for( TInt i = 0; i < count; i++ )
            {
            nextChars.Append(array->MdcaPoint(i));
            }  
        CleanupStack::PopAndDestroy(array);   

        iSearchField->SetAdaptiveGridChars( *(iExtension->iNextChars) ); 
        CleanupStack::PopAndDestroy( temptext );
        }
    else
        {
        for (TInt i = iShownIndexes->Count()-1; i>=0 ; i--)
            {
            TInt realindex = iShownIndexes->At(i);
            TPtrC itemtext = array->MdcaPoint(realindex);
            TBool isItemVisible = IsItemVisible(itemtext, aCriteria);
            TBool isItemSelected = IsItemSelected(realindex);
            // EAJA-7SK9UC set indexToSet as current index when found item
            if ( isItemVisible )
                {           
                indexEnd = iShownIndexes->Count() - i;
                }
            else if ( !(isItemVisible || isItemSelected) )
                {
                iShownIndexes->Delete(i);
                }
            }  
        }   
    InstallEmptyTextL();

    // Set highlight to the first match item in markable list
    if (iListBox)
        {
        iListBox->SetCurrentItemIndex( Max( iShownIndexes->Count() - indexEnd, 0 ));    
        }
    }

void CAknListBoxFilterItems::ReleaseCriteriaL( const TDesC &aCriteria )
    {
    if ( iDisableChangesToShownIndexes )
        {
        return;
        }    
    
    // An index to set highlight after find pane updating
    TInt indexToSet = KInvalidIndex;    
    iShownIndexes->Reset();
    // If adaptive search field 
    if( iSearchField && IsAdaptiveSearch() )
        {        
        ClearNextChars();
        TBitFlags32 columnFlag = iSearchField->ListColumnFilterFlags();
        HBufC16* temptext = HBufC16::NewL( KMatchingBufferLength ); 
        CleanupStack::PushL( temptext );
        TPtr ptr_temptext( temptext->Des() );       
        const MDesCArray *array = iModel->MatchableTextArray();
        const CAknFilteredTextListBoxModel* arr = (CAknFilteredTextListBoxModel*)(iModel->MatchableTextArray());
        TInt count = array->MdcaCount();
        
        for (TInt i = 0; i < count; i++)
           {            
            TPtrC itemtext = arr->ItemTextArray()->MdcaPoint(i);    
            AknFind::UpdateItemTextAccordingToFlag( itemtext, columnFlag, ptr_temptext );
            TBool isItemVisible = IsItemVisible(temptext->Des(), aCriteria);
            // Find first match item to set highlight
            if ( (indexToSet == KInvalidIndex) && isItemVisible )
                {
                indexToSet = iShownIndexes->Count();
                }
            if ( isItemVisible || IsItemSelected(i))
                {
                iShownIndexes->AppendL(i);
                }
            ptr_temptext.Zero();    
           }                
        iSearchField->SetAdaptiveGridChars( *(iExtension->iNextChars) ); 
        InstallEmptyTextL(); 
        CleanupStack::PopAndDestroy( temptext );
        }
    else
        {
        const MDesCArray *array = iModel->MatchableTextArray();
        TInt count = array->MdcaCount();
        TInt i;

        if ( aCriteria.Length() == 0)
            {
            /* If there is no search criteria - most commonly when list is
            *  created - there is no point to test each item separately,
            *  just append them all. This results to a HUGE performance
            *  gain in large lists.
            */
            for( i = 0; i < count ; i++ )
                {
                iShownIndexes->AppendL(i);
                }
            UninstallEmptyTextL();
            }
        else
            {
            for( i = 0; i < count ; i++ )
                {
                TPtrC itemtext = array->MdcaPoint(i);
                TBool isItemVisible = IsItemVisible(itemtext, aCriteria);
                
                // Find first match item to set highlight
                if ((indexToSet == KInvalidIndex) && isItemVisible)
                    {
                    indexToSet = iShownIndexes->Count();
                    }
                if ( isItemVisible || IsItemSelected(i))
                    {
                    iShownIndexes->AppendL(i);
                    }
                } 
            InstallEmptyTextL();
            }
        }
    
    // Set highlight to the first match item in markable list
    if ( iListBox && indexToSet != KInvalidIndex )
        {
        iListBox->SetCurrentItemIndex( Max(indexToSet, 0) );    
        }
    }

void CAknListBoxFilterItems::ClearNextChars()
    {
    if( iExtension->iNextChars )
        {
        TPtr ptr = iExtension->iNextChars->Des();
        ptr.Delete( 0, ptr.Length() );
        ptr.Zero();
        }
    }

TBool CAknListBoxFilterItems::IsAdaptiveSearch() const
    {   
    if ( iSearchField->SearchFieldStyle() == CAknSearchField::EAdaptiveSearch || 
         iSearchField->SearchFieldStyle() == CAknSearchField::EAdaptive ||
         iSearchField->SearchFieldStyle() == CAknSearchField::EPopupAdaptiveSearch ||
         iSearchField->SearchFieldStyle() == CAknSearchField::EPopupAdaptiveSearchWindow )
        return ETrue;
    else
        return EFalse;
    }

TBool CAknListBoxFilterItems::IsItemSelected(TInt aRealIndex) const
    {
    TKeyArrayFix key(0, ECmpTInt);
    TInt pos;
    if (iSelectionIndexes->Find(aRealIndex, key, pos))
        return EFalse;
    else
        return ETrue;
    }

TBool CAknListBoxFilterItems::IsItemVisible(const TDesC &aItemString, const TDesC &aSearchText)
    {
    TBool val = ETrue;
    // If findutil supported
    if ( iExtension->iFindUtil )
         {
         if( iSearchField && IsAdaptiveSearch() )
            {
            TRAP_IGNORE(             
               val = iExtension->iFindUtil->Interface()->MatchAdaptiveRefineL(aItemString, aSearchText, iExtension->iNextChars));
            }
         else
            {
            TRAP_IGNORE( 
                val = iExtension->iFindUtil->Interface()->MatchRefineL(aItemString, aSearchText));
            }           
        }
    else
        {
        if( iSearchField && IsAdaptiveSearch() )
            {
            val = AknFind::IsAdaptiveFindMatch( aItemString, aSearchText, iExtension->iNextChars );
            }
        else
            {
            val = AknFind::IsFindMatch( aItemString, aSearchText );
            }          
        }
    return val;
    }

TBool CAknListBoxFilterItems::IsSeparatorCharacter(TChar c)
    {
    return AknFind::IsFindWordSeparator(c);
    }


EXPORT_C void AknSelectionService::HandleSelectionListProcessCommandL(TInt /*aCommand*/, 
                              CEikListBox* /*aListBox*/) 
    { }

EXPORT_C void AknSelectionService::HandleMultiselectionListProcessCommandL(TInt aCommand, 
                               CEikListBox* aListBox) 
{
  switch(aCommand)
      {
  case EAknSoftkeyOk:
      if (aListBox->SelectionIndexes()->Count()==0 && aListBox->View()->CurrentItemIndex()>=0)
      {
      aListBox->View()->SelectItemL(aListBox->View()->CurrentItemIndex());
      }
      }
}

EXPORT_C void AknSelectionService::HandleMarkableListProcessCommandL(TInt aCommand, 
                        CEikListBox* aListBox) 
    {
    switch(aCommand) 
    {
    
    case EAknCmdMark:
        aListBox->View()->SelectItemL(aListBox->View()->CurrentItemIndex());
        aListBox->View()->DrawItem(aListBox->View()->CurrentItemIndex());
        break;
    case EAknCmdUnmark:
        aListBox->View()->DeselectItem(aListBox->View()->CurrentItemIndex());
        aListBox->View()->DrawItem(aListBox->View()->CurrentItemIndex());
        break;
    case EAknMarkAll:
        {
        aListBox->ClearSelection();
        TInt num = aListBox->Model()->NumberOfItems();
        if (num < 1) return;
        TInt ii=0;
        CArrayFixFlat<TInt>* array = new(ELeave) CArrayFixFlat<TInt>(20);
        CleanupStack::PushL(array);
        array->SetReserveL(num);
        for(ii=0;ii<num;ii++) 
        {
        array->AppendL(ii);
        }
        aListBox->SetSelectionIndexesL(array);
        CleanupStack::PopAndDestroy(); //array
        break;
        }
    case EAknUnmarkAll:
        aListBox->ClearSelection();
        break;
    };
    }
EXPORT_C void AknSelectionService::HandleMarkableListDynInitMenuPane(TInt aResourceId, CEikMenuPane *aMenu, CEikListBox *aListBox)
    {
    if (aResourceId == R_AVKON_MENUPANE_MARKABLE_LIST_IMPLEMENTATION)
    {
    TInt currentItemIndex = aListBox->View()->CurrentItemIndex();
    TBool markHidden = aListBox->View()->ItemIsSelected(currentItemIndex);
    TBool unmarkHidden = !aListBox->View()->ItemIsSelected(currentItemIndex);
    TBool markAllHidden = aListBox->Model()->NumberOfItems() == 0 || aListBox->SelectionIndexes()->Count()==aListBox->Model()->NumberOfItems();
    TBool unmarkAllHidden = aListBox->Model()->NumberOfItems() == 0 || aListBox->SelectionIndexes()->Count() == 0;

    aMenu->SetItemDimmed(EAknCmdMark, markHidden);
    aMenu->SetItemDimmed(EAknCmdUnmark, unmarkHidden);
    aMenu->SetItemDimmed(EAknMarkAll, markAllHidden);
    aMenu->SetItemDimmed(EAknUnmarkAll, unmarkAllHidden);    
    }
    if (aResourceId == R_AVKON_MENUPANE_MARKABLE_LIST_EDIT_LIST_IMPLEMENTATION
            || aResourceId == R_AVKON_MENUPANE_FIND_POPUP_IMPLEMENTATION_MARKABLE
        )
    {
    TBool editListHidden = aListBox->Model()->NumberOfItems()==0;
    
    aMenu->SetItemDimmed(EAknCmdEditListMenu, editListHidden);
    }

    }

EXPORT_C void AknSelectionService::HandleMarkableListDynInitMenuItem(CEikMenuPane *aMenu, CEikListBox *aListBox, TInt aCommandId, TBool aCanBeAppliedToMultipleItems)
    {
    TBool itemhidden = EFalse;
    if (!aCanBeAppliedToMultipleItems && aListBox->SelectionIndexes()->Length() > 0)
    {
    itemhidden = ETrue;
    } 
    aMenu->SetItemDimmed(aCommandId, itemhidden); 
    }
EXPORT_C void AknSelectionService::HandleMarkableListUpdateAfterCommandExecution(CEikListBox *aListBox)
    {
    aListBox->ClearSelection();
    }

EXPORT_C TKeyResponse AknSelectionService::HandleMenuListOfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType, CEikListBox *aListBox)
    {
    // Ignore number keys, clear key and shift key
    if (AknKeys::IsNumberKey(aKeyEvent,aType)) return EKeyWasConsumed;
    switch(aKeyEvent.iCode)
        {
        case EKeyDelete: 
        case EKeyLeftShift:
        case EKeyRightShift:
            return EKeyWasConsumed;
        default:
            break;
        };
   
    return aListBox->OfferKeyEventL(aKeyEvent, aType);
    }
EXPORT_C void AknSelectionService::HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, CArrayFix<TInt> &aIndexesToRemovedItemsBeforeRemoval)
    {
    AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(aListBox, aValueOfCurrentItemIndexBeforeRemoval, aIndexesToRemovedItemsBeforeRemoval);
    }

EXPORT_C void AknSelectionService::HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, TBool aCurrentItemWasRemoved)
    {
    AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(aListBox, aValueOfCurrentItemIndexBeforeRemoval, aCurrentItemWasRemoved);
    }

EXPORT_C void AknEditUtils::ConstructEditingL(CEikEdwin *aEdwin, TInt aResourceId)
    {
    TResourceReader rr;
    CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
    ConstructEditingL(aEdwin, rr);
    CleanupStack::PopAndDestroy();
    }

EXPORT_C void AknEditUtils::ConstructEditingL(CEikEdwin *aEdwin, const SAknEditorParameters &aParams)
    {
    ConstructEditingL(aEdwin,
              aParams.iEditingSpace,
              aParams.iEditingWindow,
              aParams.iCharacterCase,
              aParams.iJustification,
              aParams.iAllowedToMoveInsertionPoint,
              aParams.iCursorYesNo,
              aParams.iOverflowYesNo);
    }

EXPORT_C void AknEditUtils::ConstructEditingL(CEikEdwin *aEdwin, TResourceReader &aReader)
    {
    TInt editingSpace = aReader.ReadInt16();
    TInt editingWindow = aReader.ReadInt16();
    TInt characterCase = aReader.ReadInt16();
    TInt justification = aReader.ReadInt16();
    TInt allowedToMoveInsertionPoint = aReader.ReadInt16();
    TInt cursorYesNo = aReader.ReadInt16();
    TInt overflowYesNo = aReader.ReadInt16();
    ConstructEditingL(aEdwin, editingSpace, editingWindow, characterCase, justification, allowedToMoveInsertionPoint, cursorYesNo, overflowYesNo);
    }


EXPORT_C void AknEditUtils::ConstructEditingL(CEikEdwin* aEdwin, 
                                              TInt aEditingSpace, 
                                              TInt aEditingWindow, 
                                              TInt aCharacterCase, 
                                              TInt aJustification, 
                                              TBool aAllowedToMoveInsertionPoint, 
                                              TBool aCursorYesNo, 
                                              TBool aOverflowYesNo)
    {
    ConstructEditingL(aEdwin,aEditingSpace,aEditingWindow,aCharacterCase,aJustification, 
                      aAllowedToMoveInsertionPoint, aCursorYesNo, aOverflowYesNo, ETrue);
    }

//
// CAknLayoutUtils
//
EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, TInt aResourceId, const CFont *aCustomFont)
    {
    TResourceReader rr;
    TRAPD(error,
      {
      CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
      LayoutLabel(aLabel, aLabelParent, rr, aCustomFont);
      CleanupStack::PopAndDestroy();
      });
    if (error != KErrNone)
    {
    aLabel->SetRect(TRect(aLabelParent.iTl, TSize(2,2)));
    }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("AknLayoutUtils:LayoutLabel: Resource reader failed.")));
#endif // AKNUTILS_ENABLE_TRACES
    }

EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, const SAknLayoutLabel &aL, const CFont *aCustomFont)
    {
    LayoutLabel(aLabel,aLabelParent, aL.iFont, aL.iC, aL.iL, aL.iR, aL.iB, aL.iW, aL.iJ, aL.iNextLineB, aCustomFont);
    }

EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, const TAknMultiLineTextLayout &aL, const CFont *aCustomFont)
    {
    // if we are using non-encoded fonts, baseline is top relative
    // however for encoded fonts, at this stage baseline is actually bottom 
    // however baseline skip is always a positive delta
    TInt correctNextBaseline = TAknFontId::IsEncodedFont(aL.FontId()) ? aL.iB - aL.BaselineSkip() : aL.iB + aL.BaselineSkip();
    LayoutLabel(aLabel,aLabelParent, aL.FontId(), aL.iC, aL.il, aL.ir, aL.iB, aL.iW, aL.iJ, correctNextBaseline, aCustomFont);
    }

EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, const TAknTextLineLayout &aL, const CFont *aCustomFont)
    {
    LayoutLabel(aLabel,aLabelParent, aL.FontId(), aL.iC, aL.il, aL.ir, aL.iB, aL.iW, aL.iJ, aL.iB, aCustomFont);
    }

EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, TResourceReader& aReader, const CFont *aCustomFont)
    {
    TInt fontid = aReader.ReadInt16();
    TInt C = aReader.ReadInt16();
    TInt lm = aReader.ReadInt16();
    TInt rm = aReader.ReadInt16();
    TInt B = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt J = aReader.ReadInt16();
    TInt NB = aReader.ReadInt16();
    if (NB == 0) NB = B;
    LayoutLabel(aLabel, aLabelParent, fontid, C, lm, rm, B, W, J,NB, aCustomFont);
    }

EXPORT_C void AknLayoutUtils::LayoutLabel(CEikLabel* aLabel, const TRect &aLabelParent, TInt fontid, TInt aColor, TInt aLeftMargin, TInt aRightMargin, TInt aBaseline, TInt aWidth, TInt aJustification, TInt aNextLineB, const CFont *aCustomFont)
    {
    aBaseline = CorrectBaseline(aLabelParent.Height(), aBaseline, fontid);
    aNextLineB = CorrectBaseline(aLabelParent.Height(), aNextLineB, fontid);

    TInt lastBaseLine(0);
    if(aNextLineB!=0)
        lastBaseLine = (aNextLineB - aBaseline) * aLabel->NumberOfLines() - (aNextLineB - aBaseline);

    const CFont *font = FontFromId(fontid, aCustomFont);
    TRect rect = AknLayoutUtils::TextRectFromCoords(aLabelParent, font, aLeftMargin, aRightMargin, aBaseline, aWidth, lastBaseLine);    
    // Default color is 215 and 99% of cases uses it -- and we want to avoid extra leaving function here.
    TRAP_IGNORE(OverrideControlColorL(*aLabel, EColorLabelText, AKN_LAF_COLOR_STATIC(aColor)));
    // The semantics of "Gap between lines" is relative to the CFont::HeightInPixels
    // That is, the "Gap" is DEFINED to be the difference between the baseline separation and CFont::HeightInPixels
    aLabel->SetPixelGapBetweenLines(aNextLineB - aBaseline - font->HeightInPixels());
    aLabel->SetLabelAlignment(aJustification);
    aLabel->SetFont(font);
    aLabel->SetRect(rect);
    }


EXPORT_C void AknLayoutUtils::LayoutEdwin(CEikEdwin *aEdwin, const TRect &aEdwinParent, TInt aResourceId, TInt aNumberOfLines, const CFont *aCustomFont, TBool aMinimizeEdwinView)
    {
    TResourceReader rr;
    TRAPD(error,
        {
        CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
        LayoutEdwin(aEdwin, aEdwinParent, rr, aNumberOfLines, aCustomFont,aMinimizeEdwinView);
        CleanupStack::PopAndDestroy();
        });
    if (error != KErrNone)
        {
        aEdwin->SetRect(TRect(aEdwinParent.iTl, TSize(2,2)));
        }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("AknLayoutUtils:LayoutEdwin: Resource reader failed.")));
#endif // AKNUTILS_ENABLE_TRACES
    }


EXPORT_C void AknLayoutUtils::LayoutEdwin(CEikEdwin* aEdwin, const TRect &aEdwinParent, const SAknLayoutEdwin &aL, const CFont *aCustomFont, TBool aMinimizeEdwinView)
    {
    LayoutEdwin(aEdwin,aEdwinParent, aL.iFont, aL.iC, aL.iL, aL.iR, aL.iB, aL.iW, aL.iJ, aL.iNumberOfLinesShown, aL.iNextLineB, aCustomFont,aMinimizeEdwinView);
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin* aEdwin,
                                           const TRect &aEdwinParent,
                                           const TAknMultiLineTextLayout &aL,
                                           const CFont *aCustomFont,
                                           TBool aMinimizeEdwinView )
    {
    LayoutEdwin( aEdwin, aEdwinParent, aL, (TAknsQsnTextColorsIndex)KTextColorNone,
                 aCustomFont, aMinimizeEdwinView );
    }


EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin* aEdwin,
                                           const TRect &aEdwinParent,
                                           const TAknMultiLineTextLayout &aL,
                                           TAknsQsnTextColorsIndex aOverrideColor,
                                           const CFont *aCustomFont,
                                           TBool aMinimizeEdwinView )
    {
    TInt B = aL.iB;
    TInt secondBaseline = 0;
    TInt baselineDelta =  aL.BaselineSkip();

    if (IsParentRelative(B)) 
        B = B - ELayoutP + aEdwinParent.Height();
    if (baselineDelta != 0) 
        secondBaseline = TAknFontId::IsEncodedFont(aL.FontId()) ? B - baselineDelta : B + baselineDelta;

    LayoutEdwin( aEdwin,
                 aEdwinParent,
                 aL.FontId(),
                 aL.iC,
                 aL.il,
                 aL.ir,
                 aL.iB,
                 aL.iW,
                 aL.iJ,
                 aL.NumberOfLinesShown(),
                 secondBaseline,
                 aOverrideColor,
                 aCustomFont,
                 aMinimizeEdwinView );

    }

EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin* aEdwin,
                                           const TRect &aEdwinParent,
                                           const TAknTextLineLayout &aL,
                                           TAknsQsnTextColorsIndex aOverrideColor,
                                           const CFont *aCustomFont,
                                           TBool aMinimizeEdwinView )
    {
    /* 
    Handle the different system of defaults in the layout dll and this routine:
    In Aknlayout dll, zero baselineSkip() means that there is no 2nd baseline. 
    So in that case, 0 should be passed as secondBaseline to the called LayoutEdwin method
    */
    TInt B = aL.iB;
    TInt secondBaseline = 0;
    TInt baselineDelta =  aL.BaselineSkip();

    if (IsParentRelative(B)) 
        B = B - ELayoutP + aEdwinParent.Height();
    if (baselineDelta != 0) 
        secondBaseline = TAknFontId::IsEncodedFont(aL.FontId()) ? B - baselineDelta : B + baselineDelta;

    LayoutEdwin( aEdwin, aEdwinParent, aL.FontId(), aL.iC, aL.il, aL.ir, aL.iB,
                 aL.iW, aL.iJ, aL.NumberOfLinesShown(), secondBaseline,
                 aOverrideColor, aCustomFont, aMinimizeEdwinView );
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin(CEikEdwin* aEdwin, const TRect &aEdwinParent, const TAknTextLineLayout &aL, const CFont *aCustomFont, TBool aMinimizeEdwinView)
    {
    LayoutEdwin( aEdwin, aEdwinParent, aL, (TAknsQsnTextColorsIndex) KTextColorNone,
                 aCustomFont, aMinimizeEdwinView);
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin(CEikEdwin *aEdwin, const TRect &aEdwinParent, TResourceReader &aReader, TInt aNumberOfLines, const CFont *aCustomFont, TBool aMinimizeEdwinView)
    {
    TInt fontid = aReader.ReadInt16();
    TInt C = aReader.ReadInt16();
    TInt lm = aReader.ReadInt16();
    TInt rm = aReader.ReadInt16();
    TInt B = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt J = aReader.ReadInt16();
    TInt numberOfLinesShown = aReader.ReadInt16();
    if ( aNumberOfLines )
        numberOfLinesShown = aNumberOfLines ;
    TInt aNextLineBaseline = aReader.ReadInt16();
    LayoutEdwin(aEdwin, aEdwinParent, fontid, C, lm, rm, B, W, J, numberOfLinesShown, aNextLineBaseline, aCustomFont,aMinimizeEdwinView);
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin *aEdwin,
                                           const TRect &aEdwinParent,
                                           TInt fontid,
                                           TInt aColor,
                                           TInt aLeftMargin,
                                           TInt aRightMargin,
                                           TInt aBaseline,
                                           TInt aWidth,
                                           TInt aJustification,
                                           TInt aNumberOfLinesShown,
                                           TInt aSecondLineBaseline,
                                           const CFont *aCustomFont,
                                           TBool aMinimizeEdwinView )
    {
    LayoutEdwin( aEdwin,
                 aEdwinParent,
                 fontid,
                 aColor,
                 aLeftMargin,
                 aRightMargin,
                 aBaseline,
                 aWidth,
                 aJustification,
                 aNumberOfLinesShown,
                 aSecondLineBaseline,
                 (TAknsQsnTextColorsIndex) KTextColorNone,
                 aCustomFont,
                 aMinimizeEdwinView );
     
    }

TBool IsEmpty(TInt aValue)
    {
    return aValue == ELayoutEmpty;
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin *aEdwin,
                                           const TRect &aEdwinParent,
                                           TInt fontid,
                                           TInt aColor,
                                           TInt aLeftMargin,
                                           TInt aRightMargin,
                                           TInt aBaseline,
                                           TInt aWidth,
                                           TInt aJustification,
                                           TInt aNumberOfLinesShown,
                                           TInt aSecondLineBaseline,
                                           TAknsQsnTextColorsIndex aOverrideColor,
                                           const CFont *aCustomFont,
                                           TBool aMinimizeEdwinView )
    {
// Whether we test on IsEncodedFont is determined by how well the code
// can cope with "lay file" layouts and legacy and logical font ids.
// It is highly desirable that we can manage with only the layoutEdwinScalable implementation
//    if(TAknFontSpecification::IsEncodedFont(aFontId))
    if ( aCustomFont )
        {
        __ASSERT_DEBUG( CAknLayoutFont::AsCAknLayoutFontOrNull( aCustomFont ), Panic( EAknPanicFontProvisionFailure ) ); 
        }

    AknLayoutUtilsHelpers::LayoutEdwinScalable( aEdwin, 
                        aEdwinParent, 
                        fontid, 
                        aColor, 
                        aLeftMargin, 
                        aRightMargin, 
                        aBaseline, 
                        aWidth, 
                        aJustification, 
                        aNumberOfLinesShown, 
                        aSecondLineBaseline, 
                        aOverrideColor, 
                        static_cast<const CAknLayoutFont*>(aCustomFont), 
                        aMinimizeEdwinView);
    }

EXPORT_C void AknLayoutUtils::LayoutEdwin( CEikEdwin* aEdwin,
                         const TRect& aEdwinParent,
                         const TAknTextLineLayout& aLayout,
                         TInt aNumberOfLinesToShowOverride,
                         TInt aBaselineSeparationOverride,
                         TAknsQsnTextColorsIndex aOverrideColor,
                         TInt& aNumberOfVisibleLines )
    {
    __ASSERT_DEBUG(aEdwin,Panic(EAknLayoutEdwinPanicNoEdwin));
    
    TInt fontId = aLayout.FontId();

    // EFontCustom id not supported
    __ASSERT_DEBUG( fontId!=EFontCustom ,Panic(EAknLayoutEdwinPanicNotSupported));
   
    const CAknLayoutFont* font = AknLayoutUtils::LayoutFontFromId( fontId, NULL);
    
    TInt firstBaseline = CorrectBaseline(aEdwinParent.Height(), aLayout.iB, fontId);
    firstBaseline += 1; // This puts baseline into a more natural definition
    // baseline now refers to the distance from the top of the parent down to the baseline

    TInt leftMargin = aLayout.ir;
    TInt rightMargin = aLayout.il;
    TInt width = aLayout.iW;
    if (IsParentRelative(leftMargin)) { leftMargin = aEdwinParent.Width() - ELayoutP + leftMargin; }
    if (IsParentRelative(rightMargin)) { rightMargin = aEdwinParent.Width() - ELayoutP + rightMargin; }
    if (IsParentRelative(width)) { width = aEdwinParent.Width() - ELayoutP + width; }

    if (IsEmpty(leftMargin)) { leftMargin = aEdwinParent.Width() - rightMargin - width; }
    if (IsEmpty(rightMargin)) { rightMargin = aEdwinParent.Width() - leftMargin - width; }
    if (IsEmpty(width)) { width = aEdwinParent.Width() - leftMargin - rightMargin; }

    TAknTextDecorationMetrics metrics( fontId );
    
    TInt numberOfLinesToShow = aLayout.NumberOfLinesShown();
    if ( aNumberOfLinesToShowOverride > 0)
        numberOfLinesToShow = aNumberOfLinesToShowOverride;
    __ASSERT_DEBUG(!(aEdwin->MaximumHeightInLines())||numberOfLinesToShow<=aEdwin->MaximumHeightInLines(),Panic(EAknLayoutEdwinPanicNoLinesOverMaxNoLines));
    
    TInt secondBaseline = 0;
    if ( numberOfLinesToShow < 2)
        {
        secondBaseline = 0;
        }
    else
        {
        TInt baselineDelta =  aLayout.BaselineSkip();
        if ( aBaselineSeparationOverride > 0)
            baselineDelta = aBaselineSeparationOverride;
    
        if (baselineDelta != 0) 
            secondBaseline = firstBaseline + baselineDelta;
        }   
    
    AknLayoutUtilsHelpers::LayoutEdwinScalableWithCorrectedParametersAndDecorationMetrics(
                                 aEdwin, 
                                 aEdwinParent, 
                                 font, 
                                 aLayout.iC, 
                                 leftMargin, 
                                 rightMargin, 
                                 firstBaseline,
                                 width, 
                                 aLayout.iJ, 
                                 numberOfLinesToShow, 
                                 secondBaseline, 
                                 aOverrideColor,
                                 metrics,
                                 ETrue, // Constrain to fit within parent
                                 aNumberOfVisibleLines);
     
    }


EXPORT_C TRect AknLayoutUtils::MinimizedEdwinRect(const CEikEdwin *aEdwin) 
    {
    if (!aEdwin->TextView() || aEdwin->TextView()->AlteredViewRect().Size().iHeight == 0)
        {
        return aEdwin->Rect();
        }
    return aEdwin->TextView()->AlteredViewRect();
    } 

EXPORT_C void AknLayoutUtils::LayoutMfne(CEikMfne *aMfne, const TRect &aMfneParent, TInt aResourceId)
    {
    TResourceReader rr;
    TRAPD(error,
      {
      CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
      LayoutMfne(aMfne, aMfneParent, rr);
      CleanupStack::PopAndDestroy();
      });
    if (error != KErrNone)
    {
    aMfne->SetRect(TRect(aMfneParent.iTl, TSize(2,2)));
    aMfne->SetMfneAlignment(-1); // nasty
    }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("AknLayoutUtils:LayoutLabel: Resource reader failed.")));
#endif // AKNUTILS_ENABLE_TRACES
    }

EXPORT_C void AknLayoutUtils::LayoutMfne(CEikMfne* aMfne, const TRect &aMfneParent, const SAknLayoutMfne &aL)
    {
    LayoutMfne(aMfne,aMfneParent, aL.iFont, aL.iC, aL.iL, aL.iR, aL.iB, aL.iW, aL.iJ);
    }

EXPORT_C void AknLayoutUtils::LayoutMfne(CEikMfne* aMfne, const TRect &aMfneParent, const TAknTextLineLayout &aL)
    {
    LayoutMfne(aMfne,aMfneParent, aL.FontId(), aL.iC, aL.il, aL.ir, aL.iB, aL.iW, aL.iJ);
    }

EXPORT_C void AknLayoutUtils::LayoutMfne(CEikMfne *aMfne, const TRect &aMfneParent, TResourceReader &aReader)
    {
    TInt fontid = aReader.ReadInt16();
    TInt C = aReader.ReadInt16();
    TInt lm = aReader.ReadInt16();
    TInt rm = aReader.ReadInt16();
    TInt B = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt J = aReader.ReadInt16();
    LayoutMfne(aMfne, aMfneParent, fontid, C, lm, rm, B, W, J);
    }

EXPORT_C void AknLayoutUtils::LayoutMfne(CEikMfne *aMfne, const TRect &aMfneParent, TInt fontid, TInt /*aColor*/, TInt aLeftMargin, TInt aRightMargin, TInt aBaseline, TInt aWidth, TInt aJustification)
    {
    // This routine adds top, bottom and left and right margins to the text 

    // Corrects the baseline in the case of using new scalable layout data
    aBaseline = CorrectBaseline(aMfneParent.Height(), aBaseline, fontid);

    aMfne->SetBorder(TGulBorder::ENone);
    const CFont *font = FontFromId(fontid);  
    aMfne->SetFont(font);

    TRect rect = TextRectFromCoords(aMfneParent, font, aLeftMargin, aRightMargin, aBaseline, aWidth );
    // Margin correction done already at the top
    TAknTextDecorationMetrics decoration( fontid );
    TInt extension1(0);
    TInt extension2(0);
    decoration.GetLeftAndRightMargins( extension1, extension2 );

    // Since these margins are the ones drawn in by the MFNE, we expand the MFNE to include these margins
    rect.iTl.iX -= extension1;
    rect.iBr.iX += extension2;

    // In scalable UI, these margins are also included in the height
    // Done by magic numbers previously
    decoration.GetTopAndBottomMargins( extension1, extension2 );
    rect.iTl.iY -= extension1;
    rect.iBr.iY += extension2;

    aMfne->SetRect( rect );
    aMfne->SetMfneAlignment(aJustification); // let MNFE realign it self
    }


EXPORT_C void AknLayoutUtils::LayoutControl(CCoeControl *aControl, const TRect &aParent, TInt aResourceId)
    {
    TResourceReader rr;
    TRAPD(error,
      {
      CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
      LayoutControl(aControl, aParent, rr);
      CleanupStack::PopAndDestroy();
      });
    if (error != KErrNone)
    {
    aControl->SetRect(TRect(aParent.iTl, TSize(2,2)));
    }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("AknLayoutUtils:LayoutControl: Resource reader failed.")));
#endif // AKNUTILS_ENABLE_TRACES
    }

EXPORT_C void AknLayoutUtils::LayoutControl(CCoeControl *aControl, const TRect &aParent, const SAknLayoutControl &aL)
    {
    LayoutControl(aControl, aParent, aL.iC,aL.iL, aL.iT, aL.iR, aL.iB, aL.iW, aL.iH);
    }

EXPORT_C void AknLayoutUtils::LayoutControl(CCoeControl *aControl, const TRect &aParent, const TAknWindowLineLayout &aL)
    {
    LayoutControl(aControl, aParent, aL.iC,aL.il, aL.it, aL.ir, aL.ib, aL.iW, aL.iH);
    }

EXPORT_C void AknLayoutUtils::LayoutControl(CCoeControl *aControl, const TRect &aParent, TResourceReader &aReader)
    {
    TInt C = aReader.ReadInt16();
    TInt l = aReader.ReadInt16();
    TInt t = aReader.ReadInt16();
    TInt r = aReader.ReadInt16();
    TInt b = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt H = aReader.ReadInt16();
    LayoutControl(aControl, aParent, C,l,t,r,b,W,H);
    }

EXPORT_C void AknLayoutUtils::LayoutControl(CCoeControl *aControl, const TRect &aParent, TInt /*C*/, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H)
    {
    TRect rect = RectFromCoords(aParent, l, t, r, b, W, H);
    aControl->SetRect(rect);
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(aControl->Size() == rect.Size(), LOGTEXT(_L("AknLayoutUtils/LayoutControl: ERROR: Control changed its size in SizeChanged() - That is NOT allowed")));
#endif // AKNUTILS_ENABLE_TRACES
    }


EXPORT_C void AknLayoutUtils::LayoutImage(CEikImage *aImage, const TRect &aParent, TInt aResourceId)
    {
    LayoutControl(aImage, aParent, aResourceId);
    }

EXPORT_C void AknLayoutUtils::LayoutImage(CEikImage *aImage, const TRect &aParent, const SAknLayoutControl &aL)
    {
    LayoutImage(aImage, aParent, aL.iC,aL.iL, aL.iT, aL.iR, aL.iB, aL.iW, aL.iH);
    }

EXPORT_C void AknLayoutUtils::LayoutImage(CEikImage *aImage, const TRect &aParent, const TAknWindowLineLayout &aL)
    {
    LayoutImage(aImage, aParent, aL.iC,aL.il, aL.it, aL.ir, aL.ib, aL.iW, aL.iH);
    }

EXPORT_C void AknLayoutUtils::LayoutImage(CEikImage *aImage, const TRect &aParent, TResourceReader &aReader)
    {
    LayoutControl(aImage,aParent,aReader);
    }

EXPORT_C void AknLayoutUtils::LayoutImage(CEikImage *aImage, const TRect &aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H)
    {
    LayoutControl(aImage, aParent,C,l,t,r,b,W,H);
    TRect rect = RectFromCoords(aParent, l, t, r, b, W, H);
    if (aImage->Bitmap())
       AknIconUtils::SetSize(const_cast<CFbsBitmap*>(aImage->Bitmap()), rect.Size());
    }

EXPORT_C void AknLayoutUtils::LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const SAknLayoutText &aLayout)
    {
    TInt left = aLayout.iL;
    TInt right = aLayout.iR;
    TInt baseline = AknLayoutUtils::CorrectBaseline(aParent.Height(), aLayout.iB, aLayout.iFont);
    if (IsParentRelative(left)) { left = left - ELayoutP + aParent.Width(); }
    if (IsParentRelative(right)) { right = right - ELayoutP + aParent.Width(); }
    const CFont *font = FontFromId(aLayout.iFont);
    CGraphicsContext::TTextAlign align = TextAlignFromId(aLayout.iJ);
    aSecEd->AknSetFont(*font);
    aSecEd->AknSetAlignment(align);
    aSecEd->SetBorder(TGulBorder::ENone);
    TRect rect = TextRectFromCoords(aParent, font, left, right, baseline, aLayout.iW);
    // give secret editor margin as well in scalable
    TAknTextDecorationMetrics decoration( font );
    TInt extension1(0);
    TInt extension2(0);

    decoration.GetLeftAndRightMargins( extension1, extension2 );
    rect.iTl.iX -= extension1;
    rect.iBr.iX += extension2;

    // In scalable UI, these margins are also included in the height
    decoration.GetTopAndBottomMargins( extension1, extension2 );
    rect.iTl.iY -= extension1;
    rect.iBr.iY += extension2;
    aSecEd->SetRect(rect);
    }

EXPORT_C void AknLayoutUtils::LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const TAknTextLineLayout &aLayout)
    {
    SAknLayoutText layoutStruct = { aLayout.FontId(), aLayout.iC, aLayout.il, aLayout.ir, aLayout.iB, aLayout.iW, aLayout.iJ};
    AknLayoutUtils::LayoutSecretEditor(aSecEd, aParent, layoutStruct);
    }


// Notice, if you use this, you must ensure that the control you use this with does not have any extra borders or
// other such things -> if you see fonts clipped from bottom, then you have borders somewhere.
EXPORT_C TRect AknLayoutUtils::TextRectFromCoords(
    const TRect &aParent, 
    const CFont *aFont, 
    TInt aLeftMargin, 
    TInt aRightMargin, 
    TInt aBaseline,
    TInt aWidth, 
    TInt aLastBaseline)
    {
    if (IsParentRelative(aLeftMargin)) { aLeftMargin = aParent.Width() - ELayoutP + aLeftMargin; }
    if (IsParentRelative(aRightMargin)) { aRightMargin = aParent.Width() - ELayoutP + aRightMargin; }
    if (IsParentRelative(aWidth)) { aWidth = aParent.Width() - ELayoutP + aWidth; }

    if (IsEmpty(aLeftMargin)) { aLeftMargin = aParent.Width() - aRightMargin - aWidth; }
    if (IsEmpty(aRightMargin)) { aRightMargin = aParent.Width() - aLeftMargin - aWidth; }
    if (IsEmpty(aWidth)) { aWidth = aParent.Width() - aLeftMargin - aRightMargin; }

    (void)aWidth;
    TRect rect = aParent;

    // Use these as measures of baseline -> top of pane, and baseline -> bottom of pane
    // If its a CAknLayoutFont, then we can use exactly what we need for this
    TInt effectiveAscent(0);
    TInt effectiveDescent(0);
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( aFont );
    if ( layoutFont )
        {
        effectiveAscent = layoutFont->TextPaneTopToBaseline();
        effectiveDescent = layoutFont->BaselineToTextPaneBottom();
        }
    else
        {
        effectiveAscent = aFont->AscentInPixels();
        effectiveDescent = aFont->DescentInPixels();
        }

    rect.iTl.iX += aLeftMargin;
    rect.iBr.iX -= aRightMargin;
    // Add one to account for the series 60 layout definition of baseline
    rect.iTl.iY += aBaseline + 1 - effectiveAscent; 
    // Meaning of aLastBaseline is actually (nLines-1)*baselineSeparation
    // So bottom position is first baseline + aLastbaseline + descent + extra 
    // An extra pixel is added in the non-scalable code above, but in scalable we decide not to 
    // add it:
    rect.iBr.iY = aParent.iTl.iY + aBaseline + 1 + aLastBaseline + effectiveDescent; //Vesa

#ifdef _DEBUG
    TInt error = 0;

    __ASSERT_DEBUG(rect.Size().iWidth > 0, (error = 1, LOGTEXT1(_L("AknLayoutUtils: Rect width %d > 0"),rect.Size().iWidth)));
    __ASSERT_DEBUG(rect.Size().iHeight > 0, (error = 2, LOGTEXT1(_L("AknLayoutUtils: Rect height %d > 0"), rect.Size().iHeight)));
    __ASSERT_DEBUG(rect.Size().iWidth == aWidth, (error = 3, LOGTEXT2(_L("AknLayoutUtils: Calculated rect %d different from one from LAF %d"),rect.Size().iWidth, aWidth)));
    if (error)
        {
        /* a good place for a breakpoint */
        error = error;
        }
#endif

    return rect;
    }


TBool IsParentRelative(TInt aVal)
    {
    return aVal > ELayoutP-ELayoutPRange && aVal <= ELayoutP;
    }

EXPORT_C TRect AknLayoutUtils::RectFromCoords(const TRect& aParent,  TInt l, TInt t, TInt r, TInt b, TInt W, TInt H)
    {
    // TP HACK
    if (l==0&&t==0&&r==0&&b==0&&W==0&&H==0)
        {
#ifdef _AKNUTILS_ENABLE_TRACES
        LOGTEXT(_L("Error in layout data; ALL ZEROS!"));
#endif // AKNUTILS_ENABLE_TRACES
        W=ELayoutEmpty;
        H=ELayoutEmpty;
        }
    // END OF HACK
    
    TSize sz=aParent.Size();
    if (IsParentRelative(W)) { W = sz.iWidth - ELayoutP + W; }
    if (IsParentRelative(H)) { H = sz.iHeight - ELayoutP + H; }
    if (IsParentRelative(r)) { r = sz.iWidth - ELayoutP + r; }
    if (IsParentRelative(b)) { b = sz.iHeight - ELayoutP + b; }
    if (IsParentRelative(l)) { l = sz.iWidth - ELayoutP + l; }
    if (IsParentRelative(t)) { t = sz.iHeight - ELayoutP + t; }


    if (l==ELayoutEmpty)     
        l=sz.iWidth-W-r; 
    else if (W==ELayoutEmpty) 
        W=sz.iWidth-r-l;

    if (t==ELayoutEmpty)     
        t=sz.iHeight-H-b; 
    else if (H==ELayoutEmpty) 
        H=sz.iHeight-b-t;

#ifdef _DEBUG
    TInt error = 0;

    __ASSERT_DEBUG(t>=0, 
           (error=1,LOGTEXT1(_L("AknLayoutUtils: Layout error: t=%d < 0 "),t)));
    __ASSERT_DEBUG(aParent.Size().iWidth >= W, 
           (error=2,LOGTEXT2(_L("AknLayoutUtils: parent rect Width smaller than required %d >= %d"), aParent.Size().iWidth, W)));
    __ASSERT_DEBUG(aParent.Size().iHeight >= H, 
           (error=3, LOGTEXT2(_L("AknLayoutUtils: parent rect Height smaller than required %d >= %d"), aParent.Size().iHeight, H)));
    __ASSERT_DEBUG(l>=0, 
           (error=4,LOGTEXT1(_L("AknLayoutUtils: Layout error: l=%d >= 0"),l)));
    __ASSERT_DEBUG(r==ELayoutEmpty || r>=0, 
           (error=5,LOGTEXT1(_L("AknLayoutUtils: Layout error: r=%d <= 0"),r)));
    if (error)
        {
        /* A good place for breakpoint */
        error = error;
        }
#endif

    return TRect(TPoint(aParent.iTl.iX+l, aParent.iTl.iY+t), TSize(W, H));
    }

EXPORT_C TGulAlignment AknLayoutUtils::GulAlignFromId(TInt aJId)
    {
    TGulAlignment align;
    align.SetVAlignment(EVTop);
    switch(aJId) {
    case ELayoutAlignNone: align.SetHAlignment(EHLeft); break;
    case ELayoutAlignCenter: align.SetHAlignment(EHCenter); break;
    case ELayoutAlignLeft: align.SetHAlignment(EHLeft); break;
    case ELayoutAlignRight: align.SetHAlignment(EHRight); break;
    case ELayoutAlignBidi: align.SetHAlignment(EHLeft); break; // mapping onto left as there seems to be no equivalent
    default: align.SetHAlignment(EHLeft); break;    
    };
    return align;
    }

EXPORT_C CGraphicsContext::TTextAlign AknLayoutUtils::TextAlignFromId(TInt aJId)
    {
    CGraphicsContext::TTextAlign align;
    switch(aJId) 
    {
    case ELayoutAlignNone: align = CGraphicsContext::ELeft; break; 
    case ELayoutAlignCenter: align = CGraphicsContext::ECenter; break; 
    case ELayoutAlignLeft: align = CGraphicsContext::ELeft; break; 
    case ELayoutAlignRight: align = CGraphicsContext::ERight; break; 
    case ELayoutAlignBidi: align = CGraphicsContext::ELeft; break; // mapping onto left as there seems to be no equivalent
    default: align = CGraphicsContext::ECenter; break;
    };
    return align;
    }

EXPORT_C const CFont* AknLayoutUtils::FontFromId(TInt aId, const CFont *aCustomFont)
    {
    const CFont *font = 0;
    if ( aId == EFontCustom )
        {
        font = aCustomFont;
        if (!font) 
            { // Fall-back font when null custom font is given
            font = CEikonEnv::Static()->
                Font( TLogicalFont( TUid::Uid( EAknLogicalFontSecondaryFont ) ) ); //Vesa
            }
        }
    else
        {
        font = CEikonEnv::Static()->Font( TLogicalFont( TUid::Uid( aId ) ) );
        }
    return font;
    }

EXPORT_C const CAknLayoutFont* AknLayoutUtils::LayoutFontFromId(TInt aId, const CAknLayoutFont *aCustomFont)
    {
    const CAknLayoutFont *font = 0;
    const CFont* cFont = 0;
    if ( aId == EFontCustom )
        {
        cFont = aCustomFont;
        if (!cFont)
            { // Fall-back font when null custom font is given
            cFont = CEikonEnv::Static()->
                Font( TLogicalFont( TUid::Uid( EAknLogicalFontSecondaryFont ) ) );
            }
        }
    else
        {
        cFont = CEikonEnv::Static()->Font( TLogicalFont( TUid::Uid( aId ) ) );
        }
    // Ensure type of font is correct
    __ASSERT_DEBUG( CAknLayoutFont::AsCAknLayoutFontOrNull( cFont ), Panic( EAknPanicFontProvisionFailure ) );
    font = static_cast<const CAknLayoutFont*>(cFont);
    return font;
    }

EXPORT_C CAknLayoutFont* AknLayoutUtils::CreateLayoutFontFromSpecificationL( 
    const TAknFontSpecification& aSpec)
    {
    CWsScreenDevice*  aBitmapDevice = CCoeEnv::Static()->ScreenDevice();
    return CAknFontSpecificationLayoutFont::NewL( *aBitmapDevice, aSpec );
    }

EXPORT_C CAknLayoutFont* AknLayoutUtils::CreateLayoutFontFromSpecificationL( 
    const TTypeface& aTypeface, 
    const TAknFontSpecification& aSpec )
    {
    CWsScreenDevice*  aBitmapDevice = CCoeEnv::Static()->ScreenDevice();
    return CAknFontSpecificationLayoutFont::NewL( *aBitmapDevice, aTypeface, aSpec );
    }


EXPORT_C const CFont* AknLayoutUtils::FontFromName(const TDesC& aName) 
    {
    _LIT(KLatinPlain12,"LatinPlain12");
    _LIT(KLatinBold12,"LatinBold12");
    _LIT(KLatinBold13,"LatinBold13");
    _LIT(KLatinBold16,"LatinBold16");
    _LIT(KLatinBold17,"LatinBold17");
    _LIT(KLatinBold19,"LatinBold19");
    _LIT(KNumberPlain5,"NumberPlain5");
    _LIT(KClockBold30,"ClockBold30");
    _LIT(KLatinClock14,"LatinClock14");
    _LIT(KCombinedChinesePlain16,"CombinedChinesePlain16");
    _LIT(KCombinedChinesePlain12,"CombinedChinesePlain12");
    _LIT(KNewThai12cl,"NewThai12cl");
    _LIT(KNewThai16g,"NewThai16g");
    _LIT(KJapanPlain12,"JapanPlain12");
    _LIT(KJapanPlain16,"JapanPlain16");
    _LIT(KCalcBold21,"CalcBold21");
    _LIT(KCalcOperBold21,"CalcOperBold21");
    _LIT(KCalcOperBold13,"CalcOperBold13");

    TInt fontId = -1;
    if (aName == KLatinPlain12)      fontId = ELatinPlain12;
    else if (aName == KLatinBold12)  fontId = ELatinBold12;
    else if (aName == KLatinBold13)  fontId = ELatinBold13;
    else if (aName == KLatinBold16)  fontId = ELatinBold16;
    else if (aName == KLatinBold17)  fontId = ELatinBold17;
    else if (aName == KLatinBold19)  fontId = ELatinBold19;
    else if (aName == KNumberPlain5) fontId = ENumberPlain5;
    else if (aName == KClockBold30)  fontId = EClockBold30;
    else if (aName == KLatinClock14) fontId = ELatinClock14;
    else if (aName == KCombinedChinesePlain16) fontId = EApacPlain16;
    else if (aName == KCombinedChinesePlain12) fontId = EApacPlain12;
    else if (aName == KNewThai16g) fontId = EApacPlain16;
    else if (aName == KNewThai12cl) fontId = EApacPlain12;
    else if (aName == KJapanPlain16) fontId = EApacPlain16;
    else if (aName == KJapanPlain12) fontId = EApacPlain12;
    else if (aName == KCalcBold21) fontId = ECalcBold21;
    else if (aName == KCalcOperBold21) fontId = ECalcOperBold21;
    else if (aName == KCalcOperBold13) fontId = ECalcOperBold13;
    return FontFromId(fontId);
    }

/**
Return cursor height.
Cursor height depends on font. It is 15 for font latin bold 13 and 14 for
font latin bold 12. This means two pixels higher than font ascent and
descent. For other fonts it is not specified, nevertheless the sum of font
ascent and descent, plus 2 is returned.
*/
EXPORT_C TInt AknLayoutUtils::CursorHeightFromFont(const TFontSpec& aFont)
    {       
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );
    TInt textPaneHeight(0);
    // First look in system font array.  Match the fontspec there
    const CAknLayoutFont* font = AknLayoutUtils::MatchFontFromSystemFontArray( aFont, NULL );
    if ( font )
        textPaneHeight = font->TextPaneHeight();
    else // Use the value that was converted in TAknFontSpecification
        textPaneHeight = spec.TextPaneHeight();
    TAknTextDecorationMetrics metrics( spec );
    TInt top(0);
    TInt bottom(0);
    metrics.GetTopAndBottomMargins( top, bottom );
    return top + bottom + textPaneHeight;
    }

/**
Return cursor width.
The cursor width depends on font. It's 2 pixels for latin bold 13 and 1
pixel for latin bold 12. It is not specified for any other font and therefore
left to 1 pixel.
*/
EXPORT_C TInt AknLayoutUtils::CursorWidthFromFont (const TFontSpec& aFont)
    {
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );
    TAknTextDecorationMetrics decorationMetrics( spec );
    return(decorationMetrics.CursorWidth());
    }
/**
* Return cursor ascent.
* Cursor ascent depends on font.
* The cursor position is 3 pixels below the base line, the ascent is equal to
* the height minus 3.
* 
*/
EXPORT_C TInt AknLayoutUtils::CursorAscentFromFont(const TFontSpec& aFont)
    {
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );

    // Could address font provider for this:   
    /*
    TInt dummyIndex;
    const CFont* font = AknFontProvider::CreateFontFromMetrics( EFontNone, spec, dummyIndex);
    TInt ascent = font->AscentInPixels();
    TAknTextDecorationMetrics metrics( spec );
    TInt topExtension;
    TInt bottomExtension;
    metrics.GetTopAndBottomMargins( topExtension, bottomExtension );
    return ascent + topExtension;
    */
    // ...but currently return just the height
    return spec.TextPaneHeight();
    }

/**
* Returns cursor extensions
* This API takes a TFontSpec.  Height in the fontspec should be in Twips, which is the default unit.
* The values returned are not only the true extensions above and below the text pane, but also includes
* any extra height or depth that is required to account for the font's maximum drawing beyond AscentInPixels 
* and DescentInPixels, respectively.
*
* Thus the pixel values returned are appropriate for passing into for instance 
*   CTextView::SetCursorExtensions(aFirstExtension,aSecondExtension);
*
* Note that the return values are defined such that, for cursors to extend above and below the glyphs, 
* both values would be positive.
* 
* @param    aFont           Input. FontSpec of the font being used 
* @param    aFirstExtension  Output. Distance (measured upward) to extend the cursor above CFont::AscentInPixels()
* @param    aSecondExtension Output. Distance (measured downward) to extend the cursor below CFont::DescentInPixels()
*/
EXPORT_C void AknLayoutUtils::CursorExtensionsFromFont(const TFontSpec& aFont, TInt& aFirstExtension, TInt& aSecondExtension)
    {
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );
    TAknTextDecorationMetrics metrics(spec);
    metrics.GetTopAndBottomMargins( aFirstExtension, aSecondExtension );

    // Also, correct the numbers for any excesses/shortfalls in the font metrics
    const CAknLayoutFont* font = AknLayoutUtils::MatchFontFromSystemFontArray( aFont, NULL );
    if ( font )
        {
        aFirstExtension += font->TextPaneTopToBaseline() - font->AscentInPixels();
        aSecondExtension += font->BaselineToTextPaneBottom() - font->DescentInPixels();
        }

    }

/**
Pixels for text highlight on the left of the text. By default there are 0 pixels
on the left of the text when highlighting. There should be 1 pixel regardless of
the font type.
*/
EXPORT_C TInt AknLayoutUtils::HighlightLeftPixelsFromFont(const TFontSpec& aFont)
    {
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );
    TAknTextDecorationMetrics metrics(spec);
    TInt left(0);
    TInt right(0);
    metrics.GetLeftAndRightMargins( left, right);
    return left;
    }
/**
Pixels for text hightlight on the right of the text. By default there are 2 pixels
on the right for Font 13 and 1 pixel for Font 12. There should be 1 pixel for font
13 and 0 for Font 12. The value returned by this method will be subtracted from the
default one.
*/
EXPORT_C TInt AknLayoutUtils::HighlightRightPixelsFromFont(const TFontSpec& aFont)
    {
    TAknFontSpecification spec( EAknFontCategoryUndefined, aFont, NULL );
    TAknTextDecorationMetrics metrics(spec);
    TInt left(0);
    TInt right(0);
    metrics.GetLeftAndRightMargins( left, right);
    return right;
    }

/**
* Highlight Extensions.
* The values returned DO NOT include any extra extension required to account for glyphs that extend beyond
* CFont::AscentInPixels and CFont::DescentInPixels()
* 
*/
void AknLayoutUtils::HighlightExtensionsFromFont(const TInt fontid, TInt& aLeft, TInt& aRight, TInt&  aTop, TInt& aBottom)
    {
    TAknFontSpecification spec( fontid );
    TAknTextDecorationMetrics decorationMetrics( spec );
    decorationMetrics.GetLeftAndRightMargins(aLeft, aRight);
    decorationMetrics.GetTopAndBottomMargins(aTop, aBottom);
    }

/**
* This method is used internally for matching fonts in the system font array
* when you only have a TFontSpec. 
*
* (If you have a CFont, you can use CAknLayoutFont::AsCAknLayoutFontOrNull
* to detect if the font is a CAknLayoutFont.)  
*
* This routine avoids having to go to the server to regenerate the font. Some
* approximations are made here.  Because the == operator used in the comparison 
* of TFontSpecs is not always reliable (aliases are not resolved, for instance), 
* the comparison here is made based upon size and boldness only. As a result, this
* method should only be used for operations such as the determination of cursor 
* and highlight metrics.
*/
const CAknLayoutFont* AknLayoutUtils::MatchFontFromSystemFontArray( 
    const TFontSpec& aSpec, MGraphicsDeviceMap* /*aMap*/ )
    {
    const CAknLayoutFont* font = NULL;

    CAknEnv* env = AVKONENV;
    if ( env )
        {
        const CArrayPtr<CAknSystemFont>* fontArray = env->SystemFontArray();
        if ( fontArray )
            {
            // Search the array
            TInt count = fontArray->Count();
            for (TInt index = 0; index < count; index++)
                {
                CAknSystemFont* info = fontArray->At(index);
                CFont* thisFont = info->Font();
                TFontSpec thisSpec = thisFont->FontSpecInTwips();
                
                // Need to make the twips check fuzzy because one or both of
                // the twips values may have been through more than one twips-pixel
                // or pixel-twips transformation.
                TInt diff = aSpec.iHeight - thisSpec.iHeight;
                if ( diff < 0 )
                    diff = 0-diff;
                if ( diff/KFontHeightComparisonDivisor == 0 )
                    {
                    if ( aSpec.iFontStyle.StrokeWeight() == thisSpec.iFontStyle.StrokeWeight() )
                        {
                        font = static_cast<const CAknLayoutFont*>(thisFont);
                        break;
                        }
                    }
                }
            }
        }
    return font;
    }
EXPORT_C TBool AknLayoutUtils::LayoutMirrored()
    {
    TAknLayoutId layoutId;
    CAknEnv::Static()->GetCurrentLayoutId(layoutId);

    TInt retVal( EFalse );

    if ( layoutId == EAknLayoutIdABRW )
        {
        retVal = ETrue;
        }
    
    return retVal;
    }

EXPORT_C EVariantFlag AknLayoutUtils::Variant()
    {
    return AknBuildVariant();
    }

EXPORT_C ESubVariantFlag AknLayoutUtils::SubVariant()
    {
    switch (Variant())
        {
        case EEuropeanVariant:
            return ENoSubVariant;

        case EApacVariant:
            {
            // Subvariant comes from UI language:
            switch (AknLangUtils::UserLanguage())
                {
                case ELangTaiwanChinese:
                return ETaiwanSubVariant;
                case ELangHongKongChinese:
                return EHongKongSubVariant;
                case ELangPrcChinese:
                return EPrcSubVariant;
                default:
                return EPrcSubVariant;
                }            
            }
        default:
            break;
        }
        __ASSERT_ALWAYS(0,User::Panic(_L("Variant should only return ELAF or APAC"),0));
        return EPrcSubVariant;
    }

EXPORT_C void AknLayoutUtils::OverrideControlColorL(CCoeControl& aControl, TLogicalColor aLogicalColor, TRgb aColor)
    {
    CEikonEnv& env = static_cast<CEikonEnv&>(*aControl.ControlEnv());
    TRgb currentColor = env.ControlColor(aLogicalColor, aControl);
    if (aColor == currentColor)
        {
        // recurse to contained controls to see if they need a color override
        TInt count = aControl.CountComponentControls();
        for (TInt ii=0; ii<count; ii++)
            OverrideControlColorL(*aControl.ComponentControl(ii), aLogicalColor, aColor);
        }
    else
        {
        // OverrideColorL recurses through contained controls
        aControl.OverrideColorL(aLogicalColor, aColor);
        }
    }

EXPORT_C CEikScrollBarFrame::TScrollBarType AknLayoutUtils::DefaultScrollBarType(CAknAppUiBase* aApplication)
    {
    CEikScrollBarFrame::TScrollBarType preferredScrollBarType(CEikScrollBarFrame::EArrowHead);

    preferredScrollBarType = CEikScrollBarFrame::EDoubleSpan;

    if (aApplication && aApplication->IsLayoutAwareApp())
        {
        return preferredScrollBarType;
        }
    else
        {
        // For non-layout aware apps, arrowhead scrollbar is default. 
        // In that case also Avkon components defaults to this.
        return CEikScrollBarFrame::EArrowHead;
        }
    }

EXPORT_C void AknLayoutUtils::LayoutVerticalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout)
    {
    if (aScrollBarFrame && aScrollBarFrame->VerticalScrollBar())
        {
        // Only EDoubleSpan type scrollbar layout can be set
        if (aScrollBarFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
            {
            CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (aScrollBarFrame->VerticalScrollBar());
            TRect rect = RectFromCoords(aControlParent, aLayout.il, aLayout.it, aLayout.ir, aLayout.ib, aLayout.iW, aLayout.iH);
            if (scrollbar && (rect != TRect(scrollbar->Position(), scrollbar->Size())))
                {
                scrollbar->SetFixedLayoutRect(rect);
                scrollbar->SetRect(rect);
                }
            }
        }
    }

EXPORT_C void AknLayoutUtils::LayoutHorizontalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout)
    {
    if (aScrollBarFrame && aScrollBarFrame->GetScrollBarHandle(CEikScrollBar::EHorizontal))
        {
        // Only EDoubleSpan type scrollbar layout can be set
        if (aScrollBarFrame->TypeOfHScrollBar() == CEikScrollBarFrame::EDoubleSpan)
            {
            CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (aScrollBarFrame->GetScrollBarHandle(CEikScrollBar::EHorizontal));
            TRect rect = RectFromCoords(aControlParent, aLayout.il, aLayout.it, aLayout.ir, aLayout.ib, aLayout.iW, aLayout.iH);
            if (scrollbar && (rect != TRect(scrollbar->Position(), scrollbar->Size())))
                {
                scrollbar->SetFixedLayoutRect(rect);
                scrollbar->SetRect(rect);
                }
            }
        }
    }



EXPORT_C TBool AknLayoutUtils::LayoutMetricsRect( TAknLayoutMetrics aParam,
                                                  TRect& aRect )
    {
    TAknWindowComponentLayout line;
    TAknLayoutRect rect;
    TRect screenRect(0, 0, AKN_LAYOUT_WINDOW_screen.iW, AKN_LAYOUT_WINDOW_screen.iH);
    aRect.SetRect( 0, 0, 0, 0 );
    
    // No stacon pane active etc. cheking is done here before the switch-case so that we can 
    // have slightly better performance for some other lookups (e.g. screen).
    
    switch (aParam)
        {
        case EScreen:
            aRect = screenRect;
            return ETrue;

        case EApplicationWindow:
            rect.LayoutRect(
                screenRect,
                AknLayoutScalable_Avkon::application_window( 0 ) );
            aRect = rect.Rect();
            return ETrue;

        case EStatusPane:
            {
            CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
            
            if ( statusPane )
                {
                TInt currentStatusPaneLayoutResId = statusPane->CurrentLayoutResId();
                
                if ( AknStatuspaneUtils::StaconPaneActive() )
                    {
                    // flat status pane in landscape mode is the whole top pane area  
                    if ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT ||
                         currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT )
                        {
                        rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::area_top_pane(8) ); // flat area_top_pane in lsc
                        aRect = rect.Rect();
                        return ETrue;
                        }    
                    else
                        {
                        rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::area_top_pane(2) ); // classic area_top_pane in lsc
                        aRect = rect.Rect();
                        rect.LayoutRect( aRect, AknLayoutScalable_Avkon::stacon_top_pane() );
                        aRect = rect.Rect();
                        rect.LayoutRect( aRect, AknLayoutScalable_Avkon::control_top_pane_stacon(0) );
                        aRect.iBr.iX = rect.Rect().iTl.iX;  // Status pane top = stacon top - control pane top.
                        return ETrue;   
                        }
                    }
                else
                    {
                    TAknWindowComponentLayout parent;
                        
                    switch ( currentStatusPaneLayoutResId )
                        {
                        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE:
                        case R_AVKON_STATUS_PANE_LAYOUT_USUAL:
                        case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE:
                        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED:
                        case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED:
                        case R_AVKON_STATUS_PANE_LAYOUT_VT:
                        case R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED:
                        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT:
                        default:
                            parent = AknLayoutScalable_Avkon::area_top_pane(0);
                            line = AknLayoutScalable_Avkon::status_pane(0); // classic status pane
                            break;
                        
                        case R_AVKON_STATUS_PANE_LAYOUT_IDLE:
                        case R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED:
                            parent = AknLayoutScalable_Avkon::area_top_pane(7);
                            line = AknLayoutScalable_Avkon::status_idle_pane(); // idle status pane
                            break;
                            
                        case R_AVKON_STATUS_PANE_LAYOUT_SMALL:
                        case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE:
                        case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED:
                            // Small status pane is the whole top area.
                            parent = AknLayoutScalable_Avkon::application_window(0);
                            if ( Layout_Meta_Data::IsLandscapeOrientation() &&
                                 AknLayoutUtils::CbaLocation() == AknLayoutUtils::EAknCbaLocationBottom )
                                {
                                line = AknLayoutScalable_Avkon::area_top_pane(2);
                                }
                            else
                                {
                                line = AknLayoutScalable_Avkon::area_top_pane(1);
                                }
                                
                            break;
                            
                        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT:
                        case R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT: // fallthrough
                            {
                            if ( Layout_Meta_Data::IsLandscapeOrientation() &&
                                 Layout_Meta_Data::IsPenEnabled() )
                                {
                                parent = AknLayoutScalable_Avkon::area_top_pane( 2 );
                                }
                            else
                                {
                                parent = AknLayoutScalable_Avkon::area_top_pane( 6 );
                                }
                            line   = AknLayoutScalable_Avkon::status_pane( 1 ); // flat status pane
                            break;
                            }

                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL:
                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE: // fallthrough
                            {
                            parent = AknLayoutScalable_Avkon::area_top_pane( 8 );
                            line   = AknLayoutScalable_Avkon::status_pane( 1 );
                            break;
                            }

                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT:
                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT: // fallthrough
                            {
                            parent = AknLayoutScalable_Avkon::area_top_pane( 19 );
                            line   = AknLayoutScalable_Avkon::status_pane( 4 );
                            break;
                            }
                            
                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS:
                        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS: // fallthrough
                            {
                            parent = AknLayoutScalable_Avkon::area_top_pane( 20 );
                            line   = AknLayoutScalable_Avkon::status_pane( 5 );
                            break;
                            }
                        }
                        
                    rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose( parent, line ) );
                    aRect = rect.Rect();
                    }
                return ETrue;
                }
            return EFalse;
            }
        case EPopupParent:
            {
            if ( screenRect.iBr.iX == 640 && screenRect.iBr.iY == 360 )
                {
                TInt variety = 16;

                if ( AVKONENV->StatusPaneResIdForCurrentLayout(
                         AknStatuspaneUtils::CurrentStatusPaneLayoutResId() ) ==
                             R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS )
                    {
                    variety = 25;
                    }

                rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose(
                                     AknLayoutScalable_Avkon::application_window( 0 ),
                                     AknLayoutScalable_Avkon::main_pane( variety ) ) );
                aRect = rect.Rect();
                return ETrue;
                }
            else if ( screenRect.iBr.iX == 360 && screenRect.iBr.iY == 640 )
                {
                TInt variety = 1;
                rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose(
                                     AknLayoutScalable_Avkon::application_window( 0 ),
                                     AknLayoutScalable_Avkon::main_pane( variety ) ) );
                aRect = rect.Rect();
                return ETrue;
                }
            else
                {
                return LayoutMetricsRect( EMainPane, aRect );
                }
            }
        case EMainPane:
            {
            TInt variety = 3; // classic main pane variety by default
            
            TInt currentStatusPaneLayoutResId = AknStatuspaneUtils::CurrentStatusPaneLayoutResId();

            switch ( currentStatusPaneLayoutResId )
                {
                case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT:
                case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT:
                case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT:
                case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT:
                case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT:
                case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT:
                    {
                    // This is quite awkward but necessary since the fixed
                    // toolbar area can be used by the application main pane
                    // if the application doesn't use toolbar.
                    TBool toolbarVisible( EFalse );
                    if ( iAvkonAppUi )
                        {
                        CAknToolbar* fixedToolbar =
                        iAvkonAppUi->CurrentFixedToolbar();
                        if ( fixedToolbar )
                            {
                            TInt toolbarFlags(  fixedToolbar->ToolbarFlags() );
                            if ( toolbarFlags & KAknToolbarFixed &&
                                 !( toolbarFlags & KAknToolbarDefault ) &&
                                 fixedToolbar->IsShown() )
                                {
                                toolbarVisible = ETrue;
                                }
                            }
                        }

                    variety = toolbarVisible ? 21 : 4;
                    }
                    break;

                case R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE:
                case R_AVKON_STATUS_PANE_LAYOUT_USUAL:
                case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE:
                case R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED:
                case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED:
                case R_AVKON_STATUS_PANE_LAYOUT_VT:
                case R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED:
                case R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT:
                    {
                    // main pane variety for usual portrait main pane with
                    // 'area_top_pane' and 'area_bottom_pane'
#ifdef RD_SCALABLE_UI_V2
                    variety = 3; 
                    if ( iAvkonAppUi && iAvkonAppUi->TouchPane() && iAvkonAppUi->TouchPane()->IsVisible() )
                        {
                        variety = 15;
                        }
                    else if ( iAvkonAppUi && iAvkonAppUi->CurrentFixedToolbar() )
                        {
                        if ( AknLayoutUtils::PenEnabled() )
                             {
                             CAknToolbar* toolbar = iAvkonAppUi->CurrentFixedToolbar(); 
                             TInt flags = toolbar->ToolbarFlags(); 
                             if ( flags & KAknToolbarFixed && !( flags & KAknToolbarDefault )
                                && toolbar->IsShown() ) 
                                 {
                                 variety = 18; 
                                 }
                             }
                        }
#else
                    variety = 3;
#endif // RD_SCALABLE_UI_V2    
                    }
                    break;

                case R_AVKON_STATUS_PANE_LAYOUT_IDLE:
                case R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED:
                    {
                    // main pane variety for idle state portrait main pane with
                    // 'area_top_pane' and 'area_bottom_pane'
                    variety = 8;                    
                    }
                    break;

                case R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT:
                case R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT:
                    {                    
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        if ( PenEnabled() )
                            {
                            // This is quite awkward but necessary since the fixed
                            // toolbar area can be used by the application main pane
                            // if the application doesn't use toolbar.
                            TBool toolbarVisible( EFalse );
                            if ( iAvkonAppUi )
                                {
                                CAknToolbar* fixedToolbar =
                                    iAvkonAppUi->CurrentFixedToolbar();
                                if ( fixedToolbar )
                                    {
                                    TInt toolbarFlags(  fixedToolbar->ToolbarFlags() );
                                    if ( toolbarFlags & KAknToolbarFixed &&
                                         !( toolbarFlags & KAknToolbarDefault ) &&
                                         fixedToolbar->IsShown()  )
                                        {
                                        toolbarVisible = ETrue;
                                        }
                                    }
                                }

                            variety = toolbarVisible ? 21 : 4;
                            }
                        else
                            {
                            // main pane variety with 'area_top_pane' and 
                            // 'area_bottom_pane' in landscape (without touch pane).
                            variety = 9;             
                            }                    
                        }
                    else
                        {
                        // main pane variety with thin portrait status pane 
                        variety = 7;
                        }                                                            
                    break;
                    }
                case R_AVKON_STATUS_PANE_LAYOUT_SMALL:
                case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE:
                case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED:
                    {
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        if ( PenEnabled() )
                            {
                            // main pane variety with small status pane in landscape
                            // mode with 'area_top_pane', 'area_bottom_pane' and
                            // touch pane
                            variety = 4;
                            }
                        else
                            {
                            // main pane variety with 'area_top_pane' and
                            // 'area_bottom_pane' in landscape (without touch pane)
                            variety = 9;
                            }
                        }
                    else
                        {
                        // main pane variety with small status pane in portrait mode
                        // (with 'area_top_pane' and 'area_bottom_pane').
                        variety = 6;                    
                        }
                    }
                    break;

                case R_AVKON_STATUS_PANE_EMPTY:
                case R_AVKON_STATUS_PANE_LAYOUT_EMPTY:
                    if ( AknStatuspaneUtils::HDLayoutActive() )
                        {
                        variety = 16;
                        }
                    else
                        {
                        variety = 1; // no variety without cba
                        }
                    break;
                    
                case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL:
                case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE:
                    {
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        variety = 4;
                        }
                    break;
                    }
                    
                case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT:
                case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT:
                    {
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        variety = 21;
                        }
                    break;
                    }

                case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS:
                    {
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        variety = 22;
                        }
                    break;
                    }

                case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS:
                    {
                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        variety = 25;
                        }
                    break;
                    }
                    
                default:
                    break;
                }

            rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose(
                                     AknLayoutScalable_Avkon::application_window( 0 ),
                                     AknLayoutScalable_Avkon::main_pane( variety ) ) );
                
            aRect = rect.Rect();
            return ETrue;
            }

        case EControlPane:
            {
            if ( AknStatuspaneUtils::StaconPaneActive() )
                {
                rect.LayoutRect(
                    screenRect,
                    AknLayoutScalable_Avkon::area_top_pane( 2 ) );
                TRect parent( rect.Rect() );

                rect.LayoutRect(
                    parent,
                    AknLayoutScalable_Avkon::stacon_top_pane() );
                parent = rect.Rect();

                rect.LayoutRect(
                    parent,
                    AknLayoutScalable_Avkon::control_top_pane_stacon( 0 ) );
                
                aRect = rect.Rect();
                return ETrue;
                }
            else if ( AknStatuspaneUtils::HDLayoutActive() &&
                      AknStatuspaneUtils::CurrentStatusPaneLayoutResId() !=
                          R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS )
                {
                rect.LayoutRect(
                    screenRect,
                    AknLayoutScalable_Avkon::application_window( 0 ) );
                TRect parent( rect.Rect() );
                rect.LayoutRect(
                    parent,
                    AknLayoutScalable_Avkon::area_side_right_pane( 5 ) );
                aRect = rect.Rect();
                return ETrue;
                }
            // Control pane in flat status pane landscape mode is the
            // whole bottom pane area.  
            else if ( Layout_Meta_Data::IsLandscapeOrientation() &&
                      AknStatuspaneUtils::FlatLayoutActive() )
                {
                rect.LayoutRect(
                    screenRect,
                    AknLayoutScalable_Avkon::area_bottom_pane( PenEnabled() ? 2 : 6 ) );
                aRect = rect.Rect();
                return ETrue;
                }
            else
                {
                rect.LayoutRect(
                    screenRect,
                    AknLayoutScalable_Avkon::area_bottom_pane( 0 ) );
                aRect = rect.Rect();
                return ETrue;
                }
            }
                
        case EControlPaneBottom:
            if (AknStatuspaneUtils::StaconPaneActive())
                {
                rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::area_bottom_pane(2) ); // area_bottom_pane in lsc
                TRect parent = rect.Rect();
                rect.LayoutRect( parent, AknLayoutScalable_Avkon::stacon_bottom_pane() );
                parent = rect.Rect();
                rect.LayoutRect( parent, AknLayoutScalable_Avkon::control_bottom_pane_stacon(0) );
                aRect = rect.Rect();
                return ETrue;
                }
             return EFalse;
             
        case EStatusPaneBottom:
             if (AknStatuspaneUtils::StaconPaneActive())
                {
                rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::area_bottom_pane(2) ); // area_bottom_pane in lsc
                aRect = rect.Rect();
                rect.LayoutRect( aRect, AknLayoutScalable_Avkon::stacon_bottom_pane() );
                aRect = rect.Rect();
                rect.LayoutRect( aRect, AknLayoutScalable_Avkon::control_bottom_pane_stacon(0) );
                aRect.iBr.iX = rect.Rect().iTl.iX;  // Status pane bottom = stacon bottom - control pane bottom.
                return ETrue;   
                }
             return EFalse;
             
        case EStaconTop:
            if (AknStatuspaneUtils::StaconPaneActive())
                {
                rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose(
                                 AknLayoutScalable_Avkon::area_top_pane(2),
                                 AknLayoutScalable_Avkon::stacon_top_pane() ) );
                aRect = rect.Rect();
                return ETrue;
                }
            return EFalse;

        case EStaconBottom:
            if (AknStatuspaneUtils::StaconPaneActive())
                {
                rect.LayoutRect( screenRect, TAknWindowComponentLayout::Compose(
                                 AknLayoutScalable_Avkon::area_bottom_pane(2),
                                 AknLayoutScalable_Avkon::stacon_bottom_pane() ) );
                aRect = rect.Rect();
                return ETrue;
                }
            return EFalse;
            
        default:
            break;
        }

    // Main pane descendants
    
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::main_pane(4) );
        }
    else
        {
        rect.LayoutRect( screenRect, AknLayoutScalable_Avkon::main_pane(3) );
        }

    TRect mainpane = rect.Rect();

    switch (aParam)
        {
        case EFindPane:
            rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::find_pane() );
            aRect = rect.Rect();
            return ETrue;

        case EWallpaperPane:
            if ( Layout_Meta_Data::IsLandscapeOrientation() )
                {  
                rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::wallpaper_pane(1) );
                }
            else
                {
                rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::wallpaper_pane(0) );
                }              
            aRect = rect.Rect();
            return ETrue;

        case EIndicatorPane:
            // indicator pane on the left side on landscape mode
            if ( Layout_Meta_Data::IsLandscapeOrientation() && LayoutMirrored() )
                {
                rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::indicator_pane(2) );
                }
            // indicator pane on the right side on landscape mode
            else if ( Layout_Meta_Data::IsLandscapeOrientation() && !LayoutMirrored() )
                {
                rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::indicator_pane(1) );
                }
            // portrait mode
            else
                {
                rect.LayoutRect( mainpane, AknLayoutScalable_Avkon::indicator_pane(0) );
                }
            aRect = rect.Rect();
            return ETrue;

        case EAColunm:  
            {                   
            TAknLayoutRect listPaneRect;
            listPaneRect.LayoutRect(mainpane, AknLayoutScalable_Avkon::bg_list_pane(0));                    
            rect.LayoutRect(listPaneRect.Rect(), AknLayoutScalable_Avkon::bg_list_pane_g1(1));
            aRect = rect.Rect();
            return ETrue;
            }
        case EBColunm:
            {           
            TAknLayoutRect listPaneRect;
            listPaneRect.LayoutRect(mainpane, AknLayoutScalable_Avkon::bg_list_pane(0));                    
            TAknLayoutRect columnA;
            columnA.LayoutRect(listPaneRect.Rect(), AknLayoutScalable_Avkon::bg_list_pane_g1(1));
            // A+B column           
            rect.LayoutRect(listPaneRect.Rect(), AknLayoutScalable_Avkon::bg_list_pane_g1(2));
            aRect = rect.Rect();
            // Reduce A column
            aRect.iTl.iX += columnA.Rect().Width();
            return ETrue;
            }
        case ECColunm:
            {           
            TAknLayoutRect listPaneRect;
            listPaneRect.LayoutRect(mainpane, AknLayoutScalable_Avkon::bg_list_pane(0));                    
            rect.LayoutRect(listPaneRect.Rect(), AknLayoutScalable_Avkon::bg_list_pane_g2(2));
            aRect = rect.Rect();
            return ETrue;
            }
        case EDColunm:
            {
            TAknLayoutRect listScrollPaneRect;
            listScrollPaneRect.LayoutRect(mainpane, AknLayoutScalable_Avkon::listscroll_gen_pane(0));
            TAknLayoutRect listGenPaneRect;
            listGenPaneRect.LayoutRect(listScrollPaneRect.Rect(), AknLayoutScalable_Avkon::list_gen_pane(1));
            TAknLayoutRect listSinglePaneRect;
            listSinglePaneRect.LayoutRect(listGenPaneRect.Rect(), AknLayoutScalable_Avkon::list_single_pane(0));
            TAknLayoutRect listSinglePaneG2Rect;
            listSinglePaneG2Rect.LayoutRect(listSinglePaneRect.Rect(), AknLayoutScalable_Avkon::list_single_pane_g2(0));
            
            aRect = listSinglePaneRect.Rect();
            
            if ( LayoutMirrored() )
                {               
                aRect.iBr.iX = listSinglePaneG2Rect.Rect().iBr.iX;
                }
            else
                {               
                aRect.iTl.iX = listSinglePaneG2Rect.Rect().iTl.iX;
                }
            
            // Adjust the height of the rect to match with the height of the other columns. 
            TAknLayoutRect listPaneRect;
            listPaneRect.LayoutRect(mainpane, AknLayoutScalable_Avkon::bg_list_pane(0));                    
            rect.LayoutRect(listPaneRect.Rect(), AknLayoutScalable_Avkon::bg_list_pane_g1(1));
            aRect.iTl.iY = rect.Rect().iTl.iY;
            aRect.iBr.iY = rect.Rect().iBr.iY;
            
            return ETrue;
            }
        default:
            break;
        }

    // Status pane descendants
    
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TInt err = KErrNotFound;
   
    if (statusPane)
        {
        switch (aParam)
        {
            case ESignalPane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidSignal )));                   
                 break;

            case EContextPane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidContext )));                  
                 break;

            case ETitlePane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidTitle )));                    
                 break;

            case EBatteryPane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidBattery )));                  
                 break;

            case EUniversalIndicatorPane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidIndic )));                    
                 break;

            case ENaviPane:
                 TRAP(err,  aRect = statusPane->PaneRectL(TUid::Uid( EEikStatusPaneUidNavi )));                 
                 break;

            default:
                break;
            }
        }

            
    if (err != KErrNone)    
        {
        aRect = TRect(TPoint(0,0), TPoint(0,0));
        return EFalse;      
        }
        
    return ETrue;
    }


EXPORT_C TBool AknLayoutUtils::LayoutMetricsSize(TAknLayoutMetrics aParam, TSize& aSize)
    {
    TRect rect;
    
    TBool ret = LayoutMetricsRect(aParam, rect);
    aSize = rect.Size();
    return ret;
    }

    
EXPORT_C TBool AknLayoutUtils::LayoutMetricsPosition(TAknLayoutMetrics aParam, TPoint& aPos)
    {
    TRect rect;
    
    TBool ret = LayoutMetricsRect(aParam, rect);
    aPos = rect.iTl;
    return ret;
    }


TInt AknLayoutUtils::CorrectBaseline(TInt aParentHeight, TInt aBaseline, TInt aFontId)
    {
    TInt B = aBaseline;

    if( TAknFontId::IsEncodedFont(aFontId) && aFontId != ELayoutEmpty ) // This tells us that the font id has come from scalable layout API
        {
        TInt b = aBaseline;
        if (IsParentRelative(b)) { b = aParentHeight - ELayoutP + b; }

        const CAknLayoutFont *font = LayoutFontFromId(aFontId);
        TInt descent = font->BaselineToTextPaneBottom();

        // calculate distance down from top of parent to bottom of maximal glyph
        TInt top2bog = aParentHeight - b;

        // distance down to baseline is distance down to bottom of glyph minus descent
        // A further 1 is subtracted to account for the definition of baseline in the
        // Series 60 pre-2.8 layout specifications.
        B = top2bog - descent - 1;
        }

    return B;
    }
    
void AknLayoutUtils::CorrectFontId(TRect aParent, TInt at, TInt /*aH*/, TInt ab, TInt &aFontId)
{
    // Only ELayoutEmpty's allowed in aFontId and encoded as 0x100 in font height.
    const static TUint heightMask = 0x7FC0;
    TUint heightScaledBy6Bits = aFontId & heightMask;
    if (heightScaledBy6Bits == 0x100 << 6)
        { // ELayoutEmpty
        TInt height = aParent.Height() - at - ab;
        heightScaledBy6Bits = height << 6;
        heightScaledBy6Bits &= heightMask; // truncate if over allocated area.
        }
    TInt fontId = aFontId;
    fontId &= ~heightMask;
    fontId |= heightScaledBy6Bits;
    aFontId = fontId;
}

EXPORT_C TBool AknLayoutUtils::ScalableLayoutInterfaceAvailable()
    {
    TBool available = ETrue;
    
    // Use layout.iW and .iH to find out the resolution, and check for those that
    // do not have scalable layout interface.
    /*
    TAknWindowLineLayout layout = AKN_LAYOUT_WINDOW_screen;
    if (layout.iW == 42 && layout.iH == 42)
        {
        available = EFalse;
        }
    */
    
    return available;
    }
    

// ---------------------------------------------------------------------------
// AknLayoutUtils::CbaLocation
// Returns location of softkeys (bottom, right or left)
// ---------------------------------------------------------------------------
//
EXPORT_C AknLayoutUtils::TAknCbaLocation AknLayoutUtils::CbaLocation()
    {
    // Bottom by default.
    AknLayoutUtils::TAknCbaLocation cbaLocation(
        AknLayoutUtils::EAknCbaLocationBottom );
    
    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        //in portrait mode always bottom
        return cbaLocation;
        }
    
    TInt currentStatusPaneLayout(
        AknStatuspaneUtils::CurrentStatusPaneLayoutResId() );
    if ( Layout_Meta_Data::IsPenEnabled() &&
         AknStatuspaneUtils::HDLayoutActive() )
        {
        if ( currentStatusPaneLayout ==
                R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS )
            {
            // In the fullscreen width landscape flat status pane layout
            // the softkeys are on the bottom.
            cbaLocation = AknLayoutUtils::EAknCbaLocationBottom;
            return cbaLocation;
            }
        else
            {
            cbaLocation = AknLayoutUtils::EAknCbaLocationRight;
            }
        }
    
    if ( iAvkonAppUi->IsFullScreenApp() )
        {
        //it means this is a normal application
        if ( !iAvkonAppUi->StatusPane() )
            {
            //no status pane
            return cbaLocation;
            }
        
        if ( currentStatusPaneLayout == R_AVKON_STATUS_PANE_LAYOUT_EMPTY )
            {
            //or status pane layout is empty
            return cbaLocation;         
            }
        
        if( !AknStatuspaneUtils::StaconPaneActive() )
            {            
            //or Stacon not active
            return cbaLocation;
            }

        if ( AknStatuspaneUtils::StaconSoftKeysRight() )
            {
            // Softkey location is always on the right side in
            // widescreen status pane layouts.
            cbaLocation = AknLayoutUtils::EAknCbaLocationRight;
            }
        else if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
            {
            cbaLocation = AknLayoutUtils::EAknCbaLocationLeft;
            }
        
        return cbaLocation;
        }

    //else it means this is server application
    CAknLayoutConfig::TScreenMode screenMode = CAknSgcClient::ScreenMode();
    
    TAknPrivSoftkeyLocation privcba = screenMode.SoftkeyLocation();
    
    switch( privcba )
        {
        case EAknPrivSoftkeyLocationRight:
            cbaLocation = AknLayoutUtils::EAknCbaLocationRight;
            break;
        case EAknPrivSoftkeyLocationLeft:
            cbaLocation = AknLayoutUtils::EAknCbaLocationLeft;
            break;
        case EAknPrivSoftkeyLocationBottom:
            cbaLocation = AknLayoutUtils::EAknCbaLocationBottom;
            break;
        default:
            cbaLocation = AknLayoutUtils::EAknCbaLocationBottom;
            break;
        }
     
    return cbaLocation;
    }


// -----------------------------------------------------------------------------
// AknLayoutUtils::HighlightBasedRect
// -----------------------------------------------------------------------------
//
TRect AknLayoutUtils::HighlightBasedRect( const TRect& aHighlightRect, 
                                          CCoeControl* aControl )
    {
    TAknWindowComponentLayout unitData = AknLayoutScalable_Avkon::aid_value_unit2();
    TInt layoytDataUnit = unitData.LayoutLine().iW / 10;

    TRect clientRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, clientRect );
    
    // Control is allowed to be on top of the status pane but it cannot
    // overlay either stacon pane or control pane.
    if ( !AknStatuspaneUtils::StaconPaneActive() ) 
        {
        TRect statusPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane, 
                                           statusPaneRect );
        clientRect.BoundingRect( statusPaneRect );
        }

    TPoint location[4];
    TInt count( 0 );
            
    TSize controlSize( aControl->MinimumSize() );
    TInt leftX( aHighlightRect.iTl.iX + layoytDataUnit );
    TInt rightX( aHighlightRect.iBr.iX - controlSize.iWidth - layoytDataUnit );


    // If aHighlightRect's width is remarkably smaller than client rect's
    // width then assume we're working with a grid. Otherwise list-specific 
    // positioning rules are used.
    if ( aHighlightRect.Width() < clientRect.Width() / 2 ) // grid
        {
        count = 4;

        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            // top left
            location[0] = TPoint( leftX, aHighlightRect.iTl.iY - 
                                         controlSize.iHeight - layoytDataUnit );
            
            // bottom left
            location[1] = TPoint( leftX, aHighlightRect.iBr.iY + layoytDataUnit );

            // top right
            location[2] = TPoint( rightX, aHighlightRect.iTl.iY - 
                                          controlSize.iHeight - layoytDataUnit );
            
            // bottom right
            location[3] = TPoint( rightX, aHighlightRect.iBr.iY + layoytDataUnit );
            }
        else
            {
            // top right
            location[0] = TPoint( rightX, aHighlightRect.iTl.iY - 
                                          controlSize.iHeight - layoytDataUnit );
            
            // bottom right
            location[1] = TPoint( rightX, aHighlightRect.iBr.iY + layoytDataUnit );

            // top left
            location[2] = TPoint( leftX, aHighlightRect.iTl.iY - 
                                         controlSize.iHeight - layoytDataUnit );
            
            // bottom left
            location[3] = TPoint( leftX, aHighlightRect.iBr.iY + layoytDataUnit );
            }
        }
    else // listbox
        {
        count = 2;
        
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            // top right
            location[0] = TPoint( rightX, aHighlightRect.iTl.iY + layoytDataUnit );
                
            // bottom right
            location[1] = TPoint( rightX, aHighlightRect.iBr.iY - 
                                          controlSize.iHeight - layoytDataUnit );
            }
        else
            {
            // top left
            location[0] = TPoint( leftX, aHighlightRect.iTl.iY + layoytDataUnit );
                
            // bottom left
            location[1] = TPoint( leftX, aHighlightRect.iBr.iY - 
                                         controlSize.iHeight - layoytDataUnit );
            }
        }

    // loop through all positions and pick up the first suitable one
    for ( TInt i = 0; i < count; ++i )
        {
        if ( clientRect.Contains( location[i] ) &&
             clientRect.Contains( location[i] + aControl->Size() ) )
            {
            return TRect( location[i], controlSize );
            }
        }

    // None of the possible rectangles was big enough. Simply return the primary
    // rectangle.
    return TRect( location[0], controlSize );
    }

EXPORT_C AknLayoutUtils::TAknMainPaneState AknLayoutUtils::MainPaneState()
{
    AknLayoutUtils::TAknMainPaneState state = AknLayoutUtils::TAknMainPaneState(0);
    
    if (AknStatuspaneUtils::FlatLayoutActive() && !Layout_Meta_Data::IsLandscapeOrientation())
        {
        state = AknLayoutUtils::TAknMainPaneState(state | AknLayoutUtils::EAknMainPaneForTinyStatusPane);
        }


    return state;

}

EXPORT_C TBool AknLayoutUtils::PenEnabled()
    {
#ifdef RD_SCALABLE_UI_V2
    return Layout_Meta_Data::IsPenEnabled();
#else    
    return EFalse;
#endif // RD_SCALABLE_UI_V2    
    }

EXPORT_C TBool AknLayoutUtils::MSKEnabled()
    {
    // Check the middle softkey status from CenRep.
    // Value will be cached in future.
    if ( CEikonEnv::Static()->AppUi() && iAvkonAppUiBase )
        {
        if ( iAvkonAppUiBase->IsMSKEnabledApp() )
            {
            return ETrue;
            }
        }
    else // Cached value can't be used - fetch MSK value from CenRep.
        {
        if ( !Layout_Meta_Data::IsMSKEnabled() )
            {
            return EFalse; 
            }

        TInt MSKenabled( 0 );
        CRepository* cenRep = NULL;
        TRAPD( err, cenRep = CRepository::NewL( KCRUidAvkon ) );
        if ( !err )
            {
            err = cenRep->Get( KAknMiddleSoftkeyEnabled, MSKenabled );
            delete cenRep;
            }
            
        if ( err != KErrNone || MSKenabled == 0 )
            {
            return EFalse;
            }
            
        return ETrue;
        }

    return EFalse;
    }


EXPORT_C void AknLayoutUtils::GetEdwinVerticalPositionAndHeightFromLines(
        TInt aEdwinParent,
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverRide,
        TInt aNumberOfLinesToShowOverRide,
        TInt& aEdwinVerticalPositionRelativeToParent,
        TInt& aEdwinHeight )
    {
    aEdwinHeight = AknLayoutUtilsHelpers::EdwinHeightFromLines(
        aEdwinParent, 
        aLayout,
        aBaselineSeparationOverRide,
        aNumberOfLinesToShowOverRide,
        aEdwinVerticalPositionRelativeToParent );
    }
       
EXPORT_C TInt AknLayoutUtils::EdwinLinesWithinHeight (
        const TAknTextLineLayout& aLayout,
        TInt aBaselineSeparationOverride,
        TInt aMaxHeight,
        TInt& aUsedHeight )
    {
    return AknLayoutUtilsHelpers::EdwinLinesWithinHeight(
        aLayout,
        aBaselineSeparationOverride,
        aMaxHeight,
        aUsedHeight );
    }

EXPORT_C TAknLayoutRect::TAknLayoutRect() : iRect(-666,-666,-666,-666) { }

EXPORT_C void TAknLayoutRect::LayoutRect(const TRect &aParent, TInt aResourceId)
    {
    TResourceReader rr;
    TRAPD(error,
      {
      CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
      LayoutRect(aParent, rr);
      CleanupStack::PopAndDestroy();
      });
    if (error != KErrNone)
    {
    iColor = 0;
    iRect = TRect(aParent.iTl, TSize(2,2));
    
    }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("TAknLayoutRect: Resource reader failed. Not everything will be drawn correctly")));
#endif // AKNUTILS_ENABLE_TRACES
    }


EXPORT_C void TAknLayoutRect::LayoutRect(const TRect &aParent, const AknLayoutUtils::SAknLayoutRect &aL)
    {
    LayoutRect(aParent, aL.iC,aL.iL, aL.iT, aL.iR, aL.iB, aL.iW, aL.iH);
    }

EXPORT_C void TAknLayoutRect::LayoutRect(const TRect &aParent, const TAknWindowLineLayout &aL)
    {
    LayoutRect(aParent, aL.iC,aL.il, aL.it, aL.ir, aL.ib, aL.iW, aL.iH);
    }

EXPORT_C void TAknLayoutRect::LayoutRect(const TRect &aParent, TResourceReader &aReader)
    {
    TInt C = aReader.ReadInt16();
    TInt l = aReader.ReadInt16();
    TInt t = aReader.ReadInt16();
    TInt r = aReader.ReadInt16();
    TInt b = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt H = aReader.ReadInt16();
    LayoutRect(aParent, C,l,t,r,b,W,H);
    }

EXPORT_C void TAknLayoutRect::LayoutRect(const TRect &aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H)
    {
    if (C == ELayoutEmpty) 
            iColor = 0;
    else
            iColor = C;
    iRect = AknLayoutUtils::RectFromCoords(aParent,l,t,r,b,W,H);
    }

 EXPORT_C TRect TAknLayoutRect::Rect() const 
     {
    __ASSERT_DEBUG(iRect != TRect(-666,-666,-666,-666), Panic(EAknPanicLayoutRectNotCalled));
     return iRect;
     }
 TBool TAknLayoutRect::Valid() const
     {
    return iRect != TRect(-666,-666,-666,-666);
     }

EXPORT_C TRgb TAknLayoutRect::Color() const
    {
    __ASSERT_DEBUG(iRect != TRect(-666,-666,-666,-666), Panic(EAknPanicLayoutRectNotCalled));
    return AKN_LAF_COLOR_STATIC(iColor);
    }

EXPORT_C void TAknLayoutRect::DrawRect(CWindowGc &aGc) const
    {
    __ASSERT_DEBUG(iRect != TRect(-666,-666,-666,-666), Panic(EAknPanicLayoutRectNotCalled));
    aGc.SetBrushColor(AKN_LAF_COLOR_STATIC(iColor));
    aGc.Clear(iRect);
    }
 
EXPORT_C void TAknLayoutRect::DrawOutLineRect(CWindowGc &aGc) const
    {
    __ASSERT_DEBUG(iRect != TRect(-666,-666,-666,-666), Panic(EAknPanicLayoutRectNotCalled));
    aGc.SetBrushColor(0xffffff);
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
    aGc.SetPenColor(AKN_LAF_COLOR_STATIC(iColor));
    aGc.DrawRect(iRect);
    aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    }

EXPORT_C void TAknLayoutRect::DrawImage(CBitmapContext &aGc, CFbsBitmap *aBitmap, CFbsBitmap *aMask) const
     {
    __ASSERT_DEBUG(iRect != TRect(-666,-666,-666,-666), Panic(EAknPanicLayoutRectNotCalled));
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(iRect.Size() == aBitmap->SizeInPixels(), LOGTEXT4(_L("LayoutRect/DrawImage, displayed area and image size does not match: (%d,%d) != (%d,%d)"), iRect.Size().iWidth, iRect.Size().iHeight, aBitmap->SizeInPixels().iWidth, aBitmap->SizeInPixels().iHeight));
#endif // AKNUTILS_ENABLE_TRACES
    if (aMask) 
        { 
        TSize s = iRect.Size();
             TRect rect(TPoint(0,0), s);
            aGc.BitBltMasked(iRect.iTl, aBitmap, rect, aMask, ETrue); 
        }
     else
        {
        aGc.SetClippingRect(iRect);
        aGc.BitBlt(iRect.iTl, aBitmap);
        aGc.CancelClippingRect();
        }
    }

EXPORT_C TAknLayoutText::TAknLayoutText() : iFont(0) { }

EXPORT_C void TAknLayoutText::LayoutText(const TRect &aParent, TInt aResourceId, const CFont *aCustomFont)
    {
    TRAPD(error, 
      {
      TResourceReader rr;
      CEikonEnv::Static()->CreateResourceReaderLC(rr, aResourceId);
      LayoutText(aParent, rr, aCustomFont);
      CleanupStack::PopAndDestroy();
      });
    if (error != KErrNone)
    {
    iFont = LatinPlain12();
    iTextRect = TRect(aParent.iTl, TSize(aParent.Size().iWidth,2));
    iColor = 0;
    iAlign = CGraphicsContext::ECenter;
    iOffset = 0;
    }
#ifdef AKNUTILS_ENABLE_TRACES
    __ASSERT_DEBUG(error == KErrNone, LOGTEXT(_L("TAknLayoutText: Resource reader failed. Not everything will be drawn correctly.")));
#endif // AKNUTILS_ENABLE_TRACES
    }

EXPORT_C void TAknLayoutText::LayoutText(const TRect &aParent, const AknLayoutUtils::SAknLayoutText &aL, const CFont *aCustomFont)
    {
    LayoutText(aParent, aL.iFont, aL.iC, aL.iL, aL.iR, aL.iB, aL.iW, aL.iJ, aCustomFont);
    }

EXPORT_C void TAknLayoutText::LayoutText(const TRect &aParent, const TAknTextLineLayout &aL, const CFont *aCustomFont)
    {
    LayoutText(aParent, aL.FontId(), aL.iC, aL.il, aL.ir, aL.iB, aL.iW, aL.iJ, aCustomFont);
    }

EXPORT_C void TAknLayoutText::LayoutText(const TRect &aParent, TResourceReader &aReader, const CFont *aCustomFont)
    {
    TInt fontid = aReader.ReadInt16();
    TInt C = aReader.ReadInt16();
    TInt lm = aReader.ReadInt16();
    TInt rm = aReader.ReadInt16();
    TInt B = aReader.ReadInt16();
    TInt W = aReader.ReadInt16();
    TInt J = aReader.ReadInt16();
    LayoutText(aParent, fontid, C, lm, rm, B, W, J, aCustomFont);
    }

EXPORT_C void TAknLayoutText::LayoutText( const TRect &aParent,
                                          TInt aFontId,
                                          TInt aColor,
                                          TInt aLeftMargin,
                                          TInt aRightMargin,
                                          TInt aBaseLine,
                                          TInt aWidth,
                                          TInt aJustification,
                                          const CFont *aCustomFont )
    {
    // this is most likely broken if custon font is used!
    aBaseLine = AknLayoutUtils::CorrectBaseline(aParent.Height(), aBaseLine, aFontId);

    if (IsParentRelative(aLeftMargin)) { aLeftMargin = aLeftMargin - ELayoutP + aParent.Width(); }
    if (IsParentRelative(aRightMargin)) { aRightMargin = aRightMargin - ELayoutP + aParent.Width(); }
    if (IsParentRelative(aWidth)) { aWidth = aParent.Width() - ELayoutP + aWidth; }
    
    if (IsEmpty(aLeftMargin)) { aLeftMargin = aParent.Width() - aRightMargin - aWidth; }
    if (IsEmpty(aRightMargin)) { aRightMargin = aParent.Width() - aLeftMargin - aWidth; }
    if (IsEmpty(aWidth)) { aWidth = aParent.Width() - aLeftMargin - aRightMargin; }

    TInt fontId = aCustomFont ? EFontCustom : aFontId;
    iFont = AknLayoutUtils::FontFromId(fontId, aCustomFont);

    iTextRect = aParent;
    iColor = aColor;
    iAlign = AknLayoutUtils::TextAlignFromId( aJustification );

    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( iFont );
    TInt textPaneHeight(0);
    TInt textPaneAscent(0);
    if ( layoutFont )
        {
        textPaneHeight = layoutFont->TextPaneHeight();
        textPaneAscent = layoutFont->TextPaneTopToBaseline();
        }
    else
        {
        textPaneHeight = iFont->HeightInPixels();
        textPaneAscent = iFont->AscentInPixels();
        }
    
    // everything is measured from the top down
    iOffset = textPaneAscent; // Gives position of baseline relative to top of rectangle, as used in DrawText primitive
    iTextRect.iTl.iY += aBaseLine + 1 - iOffset; // +1 for strange series 60 layout def'n of baseline
    iTextRect.iBr.iY = iTextRect.iTl.iY + textPaneHeight; // Top to bottom is text pane height
    iTextRect.iTl.iX += aLeftMargin;
    iTextRect.iBr.iX -= aRightMargin;
    }


EXPORT_C void TAknLayoutText::DrawText(CGraphicsContext &aGc, const TDesC& aText) const
    {
    DrawText( aGc, aText, ETrue );
    }

EXPORT_C void TAknLayoutText::DrawText(
    CGraphicsContext& aGc,
    const TDesC& aText,
    TBool aUseLogicalToVisualConversion ) const
    {
    DrawText(aGc, aText, aUseLogicalToVisualConversion, Color());
    }

EXPORT_C void TAknLayoutText::DrawText(
    CGraphicsContext& aGc,
    const TDesC& aText,
    TBool aUseLogicalToVisualConversion, 
    const TRgb &aColor
    ) const
    {
    __ASSERT_DEBUG( iFont, Panic( EAknPanicLayoutTextNotCalled ) );
    aGc.UseFont( iFont );
    aGc.SetPenColor( aColor );
    if ( aText.Length() )
        {
        HBufC* visualBuf = NULL;
        TPtrC text( aText );
        
        if ( aUseLogicalToVisualConversion )
            {
            visualBuf = HBufC::New( aText.Length() + KAknBidiExtraSpacePerLine );
            
            // In OOM, logical to visual conversion is not performed...
            
            if ( visualBuf )
                {
                *visualBuf = aText; // copy
                TPtr ptr = visualBuf->Des();
                
                TInt maxWidth = iTextRect.Size().iWidth;
                
                // Logical to visual conversion.
                AknBidiTextUtils::ConvertToVisualAndClip(
                    aText,
                    ptr,
                    *iFont,
                    maxWidth,
                    maxWidth );

                text.Set( ptr );
                }
            }
        
        // Calculate x-offset based on the used alignment
        TInt margin = 0;
        if ( iAlign != CGraphicsContext::ELeft )
            {
            // Measure the full width of the text (ie. what DrawText needs)
            TInt textWidth = AknBidiTextUtils::MeasureTextBoundsWidth( *iFont, text,CFont::TMeasureTextInput::EFVisualOrder );
            
            const TInt extraWidth = iTextRect.Width() - textWidth;
            if ( iAlign == CGraphicsContext::ECenter )
                {
                margin = extraWidth / 2;
                }
            else // right aligned
                {
                margin = extraWidth;
                }
            }

        // Need to make the drawing rectangle bigger to account for underlines
        TRect drawRect(iTextRect);
        TInt height = drawRect.Height();
        // The underline position is not available from the GC. The following code imitates what Symbian CFbsBitGC implements.
        // (height-iOffset) is the part below the baseline. Check if it sufficient
        TInt extraHeightForUnderlining =   1 + Max(1, height/10)-(height-iOffset);
        if ( extraHeightForUnderlining > 0 )
            drawRect.iBr.iY += extraHeightForUnderlining;

        aGc.DrawText( text, drawRect, iOffset, CGraphicsContext::ELeft, margin );
        delete visualBuf;
        }
    aGc.DiscardFont(); // Release the font cache    
    }

EXPORT_C TRect TAknLayoutText::TextRect() const
    {
    __ASSERT_DEBUG(iFont, Panic(EAknPanicLayoutTextNotCalled));
    return iTextRect;
    }
   
TInt TAknLayoutText::BaselineOffset() const
    {
    __ASSERT_DEBUG(iFont, Panic(EAknPanicLayoutTextNotCalled));
    return iOffset;
    }

EXPORT_C void AknDrawWithSkins::DrawWindowShadow(CWindowGc &aGc, const TAknLayoutRect &aCoverRect, const TAknLayoutRect &aSecondShadowRect, const TAknLayoutRect &aFirstShadowRect, const TAknLayoutRect &aOutlineFrameRect, const TAknLayoutRect &aInsideAreaRect, CCoeControl *aControl)
    {
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = NULL;
    if (aControl) cc = AknsDrawUtils::ControlContext( aControl );

    TBool windowFrameDrawn = EFalse;
    TRect windowRect = aCoverRect.Rect();
    TAknLayoutRect topLeft;
    topLeft.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());
    
    TAknLayoutRect bottomRight;
    bottomRight.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());
    
    TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
    TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
    aGc.SetPenStyle(CGraphicsContext::ENullPen);
    const TAknsItemID *frameId = &KAknsIIDQsnFrPopup;
    const TAknsItemID *frameCenterId = &KAknsIIDQsnFrPopupCenter;
    windowFrameDrawn = AknsDrawUtils::DrawFrame(skin, aGc, outerRect, innerRect, *frameId, *frameCenterId);

    if (!windowFrameDrawn)
        {
//    TInt x0 = aCoverRect.Rect().iTl.iX;
//    TInt x1 = aOutlineFrameRect.Rect().iTl.iX;
        TInt x2 = aFirstShadowRect.Rect().iTl.iX;
        TInt x3 = aSecondShadowRect.Rect().iTl.iX;

//    TInt y0 = aCoverRect.Rect().iTl.iY;
//    TInt y1 = aOutlineFrameRect.Rect().iTl.iY;
        TInt y2 = aFirstShadowRect.Rect().iTl.iY;
        TInt y3 = aSecondShadowRect.Rect().iTl.iY;

        TInt x4 = aOutlineFrameRect.Rect().iBr.iX;
        TInt x5 = aFirstShadowRect.Rect().iBr.iX;
        TInt x6 = aSecondShadowRect.Rect().iBr.iX;
//    TInt x7 = aCoverRect.Rect().iBr.iX;

        TInt y4 = aOutlineFrameRect.Rect().iBr.iY;
        TInt y5 = aFirstShadowRect.Rect().iBr.iY;
        TInt y6 = aSecondShadowRect.Rect().iBr.iY;
//    TInt y7 = aCoverRect.Rect().iBr.iY;

        aGc.SetBrushColor(aCoverRect.Color());
    AknsDrawUtils::Background(skin, cc, aControl, aGc, aCoverRect.Rect());
        
        AknsDrawUtils::BackgroundBetweenRects( skin, cc, aControl, aGc, TRect(x2,y2,x4-1,y4-1), aInsideAreaRect.Rect()); 
        aOutlineFrameRect.DrawOutLineRect(aGc);
        aGc.SetBrushColor(aFirstShadowRect.Color());
        aGc.Clear(TRect(x2,y4,x5,y5));
        aGc.Clear(TRect(x4,y2,x5,y4));
        aGc.SetBrushColor(aSecondShadowRect.Color());
        aGc.Clear(TRect(x3,y5,x6,y6));
        aGc.Clear(TRect(x5,y3,x6,y5));
        }
    }

EXPORT_C void AknDraw::DrawWindowShadow(CWindowGc &aGc, 
                                        const TAknLayoutRect &aCoverRect, 
                                        const TAknLayoutRect &aSecondShadowRect, 
                                        const TAknLayoutRect &aFirstShadowRect, 
                                        const TAknLayoutRect &aOutlineFrameRect, 
                                        const TAknLayoutRect &aInsideAreaRect)
    {
    AknDrawWithSkins::DrawWindowShadow(aGc, aCoverRect, aSecondShadowRect, aFirstShadowRect, aOutlineFrameRect, aInsideAreaRect, NULL);
    }

static void DrawEmptyListImpl_real( const TRect &aClientRect,
                                    CWindowGc &aGc,
                                    TPtrC text,
                                    CCoeControl *aControl = NULL,
                                    TBool aSettingPageList = EFalse );
                                  

// Drawing with skins support.
EXPORT_C
void AknDrawWithSkins::DrawEmptyListWithFind( const TRect &/*aClientRect_1*/,
                                              CWindowGc &aGc,
                                              TPtrC text,
                                              CCoeControl *aControl )
    {
    // this method is called when a list with fixed find is used.
    // should pass info on find further on up the road, but
    // that makes no sense since laf is brain damaged
    DrawEmptyListImpl_real( TRect(0,0,0,0), aGc, text, aControl );
    }

EXPORT_C void AknDrawWithSkins::DrawEmptyListHeading(const TRect &aClientRect, CWindowGc& aGc, TPtrC aText, CCoeControl *aControl)
    {
    DrawEmptyListImpl_real( aClientRect, aGc, aText, aControl );
    }

EXPORT_C void AknDrawWithSkins::DrawEmptyListForSettingPage(const TRect &aRect, CWindowGc &aGc, TPtrC text, CCoeControl *aControl)
    {
    if ( aControl && aControl->FindBackground() )
        {        
		DrawEmptyListImpl_real(  aRect, aGc, text, NULL, ETrue);        
        return;
        }

    DrawEmptyListImpl_real( aRect, aGc, text, aControl, ETrue);
    }

EXPORT_C void AknDrawWithSkins::DrawEmptyList(const TRect& /*aClientRect_1*/, CWindowGc &aGc, TPtrC text, CCoeControl *aControl)
    {
    DrawEmptyListImpl_real( TRect(0,0,0,0),
                            aGc,
                            text,
                            aControl );
    }


// Plain drawing without skins

EXPORT_C void AknDraw::DrawEmptyListWithFind(const TRect &aClientRect_1, CWindowGc &aGc, TPtrC text)
    {
    AknDrawWithSkins::DrawEmptyListWithFind(aClientRect_1, aGc, text, NULL);
    }

EXPORT_C void AknDraw::DrawEmptyListHeading(const TRect &aClientRect, CWindowGc& aGc, TPtrC aText)
    {
    AknDrawWithSkins::DrawEmptyListHeading(aClientRect, aGc, aText, NULL);
    }

EXPORT_C void AknDraw::DrawEmptyListForSettingPage(const TRect &aRect, CWindowGc &aGc, TPtrC text)
    {
    AknDrawWithSkins::DrawEmptyListForSettingPage(aRect, aGc, text, NULL);
    }


EXPORT_C void AknDraw::DrawEmptyList(const TRect &aClientRect_1, CWindowGc &aGc, TPtrC text)
    {
    AknDrawWithSkins::DrawEmptyList(aClientRect_1, aGc, text, NULL);
    }

/* should be deprecated */
EXPORT_C void AknDraw::DrawEmptyListImpl(const TRect &aClientRect, CWindowGc &aGc, TPtrC text, TInt /*line1layout*/, TInt /*line2layout*/)
    {
    DrawEmptyListImpl_real( aClientRect, aGc, text );
    }

TBool DrawEmptyListImpl_real_DrawBg( CWindowGc &aGc,
                                     CCoeControl *aControl,
                                     TBool /*aSettingPageList*/ )
    
    {
    // Clearing area
    TRect mainPane; 
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    // aItemTextRect is list item's rect, width of which is smaller than width of the list
    // with a scroll bar. List needs to draw under scroll bar anyway, so we need to
    // modify given rect here.
    TRect mainPaneRect( mainPane.Size() );  
    
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = NULL; 
    TBool owned = EFalse;

    if (aControl)
        {
        cc = AknsDrawUtils::ControlContext( aControl );
        }

    if (!cc) 
        {
        TRAPD(error,
            {
            const TAknsItemID *id = &KAknsIIDNone;  
            if (AknsUtils::AvkonSkinEnabled())
                {
                cc = CAknsListBoxBackgroundControlContext::NewL(
                    KAknsIIDQsnBgAreaMainListGene,
                    mainPaneRect, EFalse, *id, mainPaneRect );
                }
            });
        if (error == KErrNone)
            {
            owned = ETrue;
            }
        }
    
    TBool isPopupList( EFalse );
    if ( aControl )
        {
        // unfortunately, there is no other way to check this.
        TAknLayoutRect lr;
        lr.LayoutRect( mainPane, AknLayoutScalable_Avkon::popup_menu_window( 0 ) );
        lr.LayoutRect( lr.Rect(), AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ) );
        lr.LayoutRect( lr.Rect(), AknLayoutScalable_Avkon::list_menu_pane( 0 ) );
        lr.LayoutRect( lr.Rect(), AknLayoutScalable_Avkon::list_single_pane_cp2( 0 ) );

        if ( aControl->Size().iWidth == lr.Rect().Width() )
            {
            isPopupList = ETrue;
            }

        AknsDrawUtils::Background( skin, cc, aControl, aGc, aControl->Rect(),
                                   KAknsDrawParamNoClearUnderImage |
                                   KAknsDrawParamBottomLevelRGBOnly );
        }
    
    if (owned)
        {
        delete cc;
        }
    
    return isPopupList;
    }

void DrawEmptyListImpl_real_DrawUpToTwoLines( CWindowGc &aGc,
                                              TPtrC aText,
                                              TAknLayoutText &aLine1,
                                              TAknLayoutText &aLine2,
                                              TInt aLine1length,
                                              TInt aLine2length,
                                              const CFont* aFont,
                                              TRgb aColor,
                                              TDes& aBuffer,
                                              TBool aPopupList,
                                              TRect aParentRect,
                                              TBool /*aSettingPageList*/)
    {
    TRAPD( error,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(10);
        CleanupStack::PushL( wrapWidthArray );

        wrapWidthArray->AppendL( aLine1length );
        wrapWidthArray->AppendL( aLine2length );
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL( 
            aText, *wrapWidthArray, *aFont, aBuffer, ETrue );
        
        CleanupStack::PopAndDestroy(); // wrapWidthArray
        } ); // TRAP end
    
    if ( error != KErrNone )
        {
        aBuffer = aText;
        }
    
    // Drawing text
    aGc.Reset();
    TBool oneline( EFalse );
    TPtrC ptr = aBuffer;
    TPtrC top = ptr;
    TInt off = ptr.Locate('\n');
    if ( off >= 0 )
        {
        top.Set(ptr.Left(off));
        ptr.Set(ptr.Mid(off+1));

        TInt off1 = ptr.Locate('\n');
        if ( off1 >= 0 )
            {
            ptr.Set(ptr.Left(off1));
            }
        else
            {
            oneline = ETrue;
            }
        }
    
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
    aGc.SetOpaque( ETrue ); // transparency off

    // no layout exist for popup list - mainpane layout is ok for X
    // coords, center vertically.  Also need to calculate vertical
    // position for mainpane lists, since laf is broken as designed.
    // If you don't believe this, try using laf values in phonebook.
    aGc.UseFont( aFont );
    aGc.SetPenColor( aColor );
    
    // center horizontally
    CGraphicsContext::TTextAlign textAlign( CGraphicsContext::ECenter );
    
    // center vertically
    TInt h = aParentRect.Height();
    TInt lineh = aLine1.TextRect().Height();
    TRect r1( aLine1.TextRect() );
    TRect r2( aLine2.TextRect() );

    TInt baseLineOffset( aLine1.BaselineOffset() );
    
    // gap between lines - must be calculated this way, since no other
    // way really exists. Could be calculated from layout data, but
    // data is wrong, as 1st line is calculated from top of parent
    // rect, and 2nd line is calculated from bottom of the parent
    // rect. iAvkonAppUi->ClientRect() as parent rect would otherwise
    // be ok and give nice results, but in phonebook ClientRect() is
    // not what it should be - it is some strange amount too large.
    // This can not be fixed unless layout data is fixed to use only
    // top marginals.
    TInt lineGap( lineh / 6 );

    TInt m;  // // middle point of texts
    if ( aPopupList )
        {
        m = aParentRect.iTl.iY + h / 2;// + lineh + lineGap / 2;
        if ( oneline )
            {
            m += lineh / 2;
            }
        }
    else
        {
        m = aParentRect.iTl.iY + h / 3 + lineh + lineGap / 2;
        }
    
    TInt b1( m - lineGap / 2 );           // bottom of 1st line
    TInt b2( m + lineh + lineGap / 2 );   // botton of 2nd line
    
    // rects of texts
    r1.iTl.iY = b1 - lineh;
    r1.iBr.iY = b1;
        
    r2.iTl.iY = b2 - lineh;
    r2.iBr.iY = b2;
        
    aGc.DrawText( top, r1, baseLineOffset, textAlign );
    if ( !oneline )
        {
        aGc.DrawText( ptr, r2, baseLineOffset, textAlign );
        }
    
    
    aGc.DiscardFont();
    aGc.SetOpaque( EFalse ); // transparency back on
    }    

void DrawEmptyListImpl_real_DrawMoreThanTwoLines( const TRect &aParentRect,
                                                  CWindowGc &aGc,
                                                  TPtrC aText,
                                                  TRgb aColor,
                                                  TDes& buffer )

    {
    // fetch layouts
    TAknLayoutText line[4];
    
    line[0].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t1(2) );
    line[1].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t3(0) );
    line[2].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t4(0) );
    line[3].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t5(0) );

    TInt lineLength[4];
    TInt i;
    for ( i = 0; i < 4; i++ )
        {
        lineLength[i] = line[i].TextRect().Width();
        }
    
    const CFont *bigFont = line[0].Font();
    const CFont *smallFont = line[1].Font(); 

    // wrap text
    TInt off = aText.Locate('\n');
    TPtrC rest( aText );
    rest.Set( aText.Right(aText.Length() - off - 1 ));

    HBufC* firstLine = NULL;
    
    TRAPD( error1, 
            {
            firstLine = HBufC::NewL(
                aText.Left(off).Length() + KAknBidiExtraSpacePerLine );
            });

    if (error1 == KErrNone)
        {
        TPtr firstLinePtr = firstLine->Des();
        AknBidiTextUtils::ConvertToVisualAndClip(
                                aText.Left(off),
                                firstLinePtr,
                                *bigFont,
                                lineLength[0],
                                lineLength[0] );
        }
    
    TRAPD( error2,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(10);
        CleanupStack::PushL( wrapWidthArray );
        
        // wrap small font lines
        wrapWidthArray->Reset();
        for ( i = 1; i <= 3; i++ )
            {
            wrapWidthArray->AppendL( lineLength[i] );
            }
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL( 
            rest, *wrapWidthArray, *smallFont, buffer, ETrue );
        
        CleanupStack::PopAndDestroy(); // wrapWidthArray
        } ); // TRAP end
    
    
    TPtrC ptr[4];
    TInt n = 0;
    
    if (error1 == KErrNone)
        {
        ptr[0].Set( firstLine->Des() );
        }
    if ( error1 != KErrNone || error2 != KErrNone )
        {
        ptr[0].Set(aText.Left(off));
        }
    else
        {
        TInt newlines[3];
        n = 0;
        for ( i = 0; i < buffer.Length(); i++ )
            {
            if ( buffer[i] != '\n' )
                {
                continue;
                }
            newlines[n] = i;
            
            n++;
            if ( n >= 3 )
                {
                break;
                }
            }
        
        if ( n >= 1 )
            {
            ptr[1].Set( buffer.Left( newlines[0] ) );
            }
        if ( n >= 2 )
            {
            ptr[2].Set( buffer.Mid( newlines[0] + 1, newlines[1] - newlines[0] - 1 ) );
            }
        if ( n >= 3 )
            {
            ptr[3].Set( buffer.Mid( newlines[1] + 1, newlines[2] - newlines[1] - 1 ) );
            }
        }
    
    // draw texts
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
    aGc.SetOpaque( ETrue ); // transparency off
    
    for ( i = 0; i < 4; i++ )
        {
        line[i].DrawText( aGc, ptr[i], EFalse, aColor );
        }
    aGc.SetOpaque( EFalse ); // transparency back on  
    delete firstLine;
    }

void DrawEmptyListImpl_real( const TRect &aClientRect,
                             CWindowGc &aGc,
                             TPtrC aText,
                             CCoeControl *aControl,
                             TBool aSettingPageList )
    {
    TBool popupList = DrawEmptyListImpl_real_DrawBg( aGc, aControl, aSettingPageList );
    if ( !aText.Length() )
        {
        return;
        }

    HBufC* hbuf = HBufC::New( aText.Size() + 3 * ( KAknBidiExtraSpacePerLine  +1 )
                              + 10 );  // reserve space for newlines
    if ( !hbuf )
        { // can't really do anything
        return;
        }

    TPtr buffer(hbuf->Des());
    
    TRgb color( KRgbBlack );
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        TRgb c;
        MAknsSkinInstance *skin = AknsUtils::SkinInstance();
        TInt err = AknsUtils::GetCachedColor( skin,
                                              c,
                                              KAknsIIDQsnTextColors,
                                              EAknsCIQsnTextColorsCG6 );
        if ( !err )
            {
            color = c;
            }
        }

    /*
    * input text can be either
    * - "line1"
    * - "line1 which will be wrapped to 2 lines and truncated with..."
    * - "line1\nline2"
    * - "line1\nMany other lines which will be wrapped to several lines"
    *
    * there are 3 layouts
    * - 1 line with big font,
    * - 2 lines with big font
    * - 1 line with big font + 1..3 lines with small font (not for popup lists)
    *
    *  so first we need to check if given text has a newline,
    *  if so, then we need to check if given text fits to 2 lines or
    *  should it be split to several small font lines
    */

    TInt i, n;
    n = 0;
    for (i = 0; i < aText.Length(); i ++)
        {
        if ( aText[i] == '\n' )
            {
            n++;
            }
        }

    
    TAknTextComponentLayout layout1( AknLayoutScalable_Avkon::main_pane_empty_t1( 0 ) );
    TAknTextComponentLayout layout2( AknLayoutScalable_Avkon::main_pane_empty_t2( 0 ) );
    TAknLayoutText line1;
    TAknLayoutText line2;
    TRect clientRect( iAvkonAppUi->ClientRect() );
    TRect parentRect;

    if( aSettingPageList )
        {
        parentRect = aClientRect;
        }
    else if( aControl )
        {
        parentRect = aControl->Rect();
        }
    else
        {
        parentRect = TRect(0,0,clientRect.Width(),clientRect.Height());
        }

    line1.LayoutText( parentRect, layout1 );
    TInt line1length = line1.TextRect().Size().iWidth;

    line2.LayoutText( parentRect, layout2 ); 
    TInt line2length = line2.TextRect().Size().iWidth;

    const CFont *font = line1.Font();

    if ( n == 0 )
        { // one line, or one line which will be wrapped to two
        DrawEmptyListImpl_real_DrawUpToTwoLines( aGc, aText, line1, line2,
                                                 line1length, line2length,
                                                 font, color, buffer,
                                                 popupList, parentRect, aSettingPageList );
        delete hbuf;
        return;
        }
    
    TRAPD( error,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(10);
        CleanupStack::PushL( wrapWidthArray );

        wrapWidthArray->AppendL( line1length );
        wrapWidthArray->AppendL( line2length );
        wrapWidthArray->AppendL( line2length ); // allow wrap to 3 lines
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL(
            aText, *wrapWidthArray, *font, buffer, ETrue );

        CleanupStack::PopAndDestroy(); // wrapWidthArray
        } ); // TRAP end

    // there is no layout for empty popuplist
    if ( error != KErrNone || popupList )
        {
        DrawEmptyListImpl_real_DrawUpToTwoLines( aGc, aText, line1, line2,
                                                 line1length, line2length,
                                                 font, color, buffer,
                                                 popupList, parentRect, aSettingPageList );
        }
    else
        { // 1 line with big font + 1..3 lines with small font
        DrawEmptyListImpl_real_DrawMoreThanTwoLines( parentRect, aGc, aText, color, buffer );
        }

    delete hbuf;
    }



EXPORT_C TBool AknTextUtils::ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikFormattedCellListBox *aListBox, TInt aItemIndex, TInt aSubCellNumber)
    {
    CFormattedCellListBoxData *data = aListBox->ItemDrawer()->FormattedCellData();
    const CFont *font = data->Font(aListBox->ItemDrawer()->Properties(aItemIndex), aSubCellNumber);
    TSize cellsize = data->SubCellSize(aSubCellNumber);
    TMargins margin = data->SubCellMargins(aSubCellNumber);
    TInt width = cellsize.iWidth - margin.iLeft - margin.iRight;
    TInt clipgap = data->SubCellTextClipGap(aSubCellNumber);
    return ClipToFit(aBuffer, *font, width, aDir, width + clipgap);
    }

EXPORT_C TBool AknTextUtils::ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikColumnListBox *aListBox, TInt aItemIndex, TInt aColumnNumber)
    {
    CColumnListBoxData *data = aListBox->ItemDrawer()->ColumnData();
    const CFont *font = data->Font(aListBox->ItemDrawer()->Properties(aItemIndex), aColumnNumber);
    TInt cellsize = data->ColumnWidthPixel(aColumnNumber);
    TMargins margin = data->ColumnMargins(aColumnNumber);
    TInt width = cellsize - margin.iLeft - margin.iRight;
    TInt clipgap = data->ColumnTextClipGap(aColumnNumber);
    return ClipToFit(aBuffer, *font, width, aDir, width + clipgap);
    }

EXPORT_C TBool AknTextUtils::ClipToFit(
    TDes& aBuffer,
    const CFont& aFont,
    TInt aMaxWidthInPixels,
    AknTextUtils::TClipDirection aDir,
    TInt aClipWidth,
    const TDesC& aClipString )
    {
    TAknLocVariant variants[KAknMaxLocVariants];
    TInt numVariants = TAknTextWrapper::GetLocVariants( aBuffer, variants );

    TBool truncated = ETrue;
    TInt i = 0;

    TPtr buffer( NULL, 0 );

    while ( i < numVariants && truncated )
        {
        buffer.Set( NULL, 0, 0 );
        TInt length = variants[i].iEnd - variants[i].iStart;
        if ( length )
            {
            buffer.Set( &(aBuffer[variants[i].iStart]), length, length );
            }

        truncated = DoClipToFit(
            buffer,
            aFont,
            aMaxWidthInPixels,
            aDir,
            aClipWidth,
            aClipString );

        i++;
        }

    // Move the selected variant in the beginning of the target buffer
    // or if it is already, set the length correctly.
    i--;

    TInt start = variants[i].iStart;

    if ( start > 0 )
        {
        TPtrC selected = aBuffer.Mid( start, buffer.Length() );
        aBuffer.Copy( selected );
        }
    else
        {
        aBuffer.SetLength( buffer.Length() );
        }

    return truncated;
    }

// -----------------------------------------------------------------------------
// AknTextUtils::DoClipToFit()
// -----------------------------------------------------------------------------
//
TBool AknTextUtils::DoClipToFit(
    TDes& aBuffer,
    const CFont& aFont,
    TInt aMaxWidthInPixels,
    AknTextUtils::TClipDirection aDir,
    TInt aClipWidth,
    const TDesC& aClipString )
    {
    if ( !aBuffer.Length() )
        {
        return EFalse;
        }

    TInt textWidth = aFont.TextWidthInPixels( aBuffer );

    if ( textWidth <= aMaxWidthInPixels )
        {
        return EFalse;
        }

    TText clipChar = 0;
    TInt extraWidth = 0;
    if ( aClipString.Length() )
        {
        clipChar = KDefaultClipChar;
        extraWidth = aFont.CharWidthInPixels( clipChar );
        }

    if ( aClipWidth == KDefaultClipWidth )
        {
        aClipWidth = aMaxWidthInPixels;
        }

    // Not enough space even for clip char alone - return empty descriptor.
    if ( aClipWidth < extraWidth )
        {
        aBuffer.Zero();
        return ETrue;
        }

    switch( aDir )
        {
        case AknTextUtils::EClipFromEnd:
            {
            TInt cutOff = aFont.TextCount( aBuffer, aClipWidth - extraWidth );

            // This is "avkon rule": should not insert ellipsis right after a space.
            if ( cutOff > 1 && 
                 aBuffer[cutOff - 1] == ' ' &&
                 aBuffer[cutOff - 2] != ' ' )
                {
                cutOff--;
                }
            aBuffer.SetLength( cutOff );
            if ( aClipString.Length() )
                {
                aBuffer.Append( clipChar );
                }
            break;
            }

        case AknTextUtils::EClipFromBeginning:
            {
            TPtrC ptr = aBuffer;

            while ( textWidth > aClipWidth - extraWidth )
                {
                TChar c = ptr[0];
                textWidth -= aFont.CharWidthInPixels( c );
                ptr.Set( ptr.Mid( 1 ) );
                }

            if ( ptr.Length() && ptr[0] == ' ' )
                {
                ptr.Set( ptr.Mid( 1 ) );
                }
            aBuffer.Zero();
            if ( aClipString.Length() )
                {
                aBuffer.Append( clipChar );
                }
            aBuffer.Append( ptr );
            break;
            }

        case AknTextUtils::EDoNotClip:
            break;

        default:
            __ASSERT_DEBUG( 0, User::Invariant() );
            break;
        };

    return ETrue;
    }

/**
 *   EXPORTED TEXT WRAPPING METHODS 
 */
EXPORT_C void AknTextUtils::WrapToArrayL(
        const TDesC& aStringToWrap, 
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray ) 
    {
    TPtr ptr(
        (TText*)aStringToWrap.Ptr(),
        aStringToWrap.Length(),
        aStringToWrap.Length() );

    WrapToArrayL(
        ptr,
        &aLineWidthArray,
        aFont,
        aWrappedArray,
        0,
        0,
        AknBidiTextUtils::EImplicit );
    }

EXPORT_C void AknTextUtils::WrapToArrayL(
        const TDesC& aStringToWrap, 
        TInt aLineWidth, 
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray ) 
    {
    TPtr ptr(
        (TText*)aStringToWrap.Ptr(),
        aStringToWrap.Length(),
        aStringToWrap.Length() );

    WrapToArrayL(
        ptr,
        NULL,
        aFont,
        aWrappedArray,
        aLineWidth,
        0,
        AknBidiTextUtils::EImplicit );
    }

EXPORT_C void AknTextUtils::WrapToArrayAndClipL(
        TDes& aStringToWrap,             
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont,                    
        CArrayFix<TPtrC>& aWrappedArray)      
    {
    WrapToArrayL(
        aStringToWrap,
        &aLineWidthArray,
        aFont,
        aWrappedArray,
        0,
        TAknTextWrapper::EClip,
        AknBidiTextUtils::EImplicit );
    }

EXPORT_C void AknTextUtils::ChopToArrayAndClipL(
        TDes& aStringToChop,             
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont,                    
        CArrayFix<TPtrC>& aChoppedArray)      
    {
    AknTextUtils::ChopToArrayAndClipL(
        aStringToChop,             
        &aLineWidthArray,
        aFont,                 
        aChoppedArray,
        0 );
    }

EXPORT_C void AknTextUtils::ChopToArrayAndClipL(
        TDes& aStringToChop,             
        TInt aLineWidth, 
        const CFont& aFont,                    
        CArrayFix<TPtrC>& aChoppedArray )      
    {
    AknTextUtils::ChopToArrayAndClipL(
        aStringToChop,             
        NULL,
        aFont,                 
        aChoppedArray,
        aLineWidth );
    }

EXPORT_C void AknTextUtils::WrapToStringL(
        const TDesC& aStringToWrap, 
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont, 
        TDes& aWrappedString ) 
    {
    WrapToStringL( 
        aStringToWrap,
        aLineWidthArray,
        aFont,
        aWrappedString,
        0,
        AknBidiTextUtils::EImplicit );
    }


EXPORT_C void AknTextUtils::WrapToStringAndClipL(
        const TDesC& aStringToWrap, 
        const CArrayFix<TInt>& aLineWidthArray, 
        const CFont& aFont, 
        TDes& aWrappedString) 
    {
    WrapToStringL( 
        aStringToWrap,
        aLineWidthArray,
        aFont,
        aWrappedString,
        TAknTextWrapper::EClip,
        AknBidiTextUtils::EImplicit );
    }

EXPORT_C void AknTextUtils::ReplaceCharacters(TDes &aDes, const TDesC &aChars, TChar aReplacement)
    //
    // Running time O(aDes.Length() * aChars.Length())
    // Does not change length of the string.
    // 
    {
    TInt src = 0;
    TInt srclength = aDes.Length();
    while(src < srclength)
    {
    TChar c = aDes[src];
    if (aChars.LocateF(c) != KErrNotFound)
        aDes[src] = TUint16(aReplacement);
    ++src;
    }
    }

EXPORT_C void AknTextUtils::PackWhiteSpaces(TDes &aDes, const TDesC &aWhiteSpaceChars)
    //
    // This one finds several whitespace characters and packs them into one
    // character. O(aDes.Length() * aChars.Length())
    // 
    {
    TInt target=0;
    TInt src = 0;
    TInt srclength = aDes.Length();
    TBool lastWasWhiteSpace = EFalse;

    while (src < srclength)
    {
    aDes[target] = aDes[src];
    TChar c = aDes[src];

    TBool currentIsWhiteSpace = aWhiteSpaceChars.LocateF(c) != KErrNotFound;

    if (!( lastWasWhiteSpace && currentIsWhiteSpace ))
        ++target;

    ++src;
    lastWasWhiteSpace = currentIsWhiteSpace;
    }
    aDes.SetLength(target);
    
    }

EXPORT_C void AknTextUtils::StripCharacters(TDes &aDes, const TDesC &aChars)
    {
    //
    // This algorithm has running time of O(aDes.Length() * aChars.Length()).
    //
    TInt target=0;
    TInt src = 0;
    TInt srclength = aDes.Length();
    while (src < srclength)
    {
    aDes[target] = aDes[src];
    TChar c = aDes[src];
    if (aChars.LocateF(c) == KErrNotFound) 
        ++target;
    ++src;
    }
    aDes.SetLength(target);
    }

/** 
* This routine scans the descriptor passed to it, searching for a character that
* is neither space nor ECoCategory nor ECfCategory. 
*
* Currently not exported outside Avkon
*/ 
TBool AknTextUtils::IsEmptyText( const TDesC& aTextToTest )
    {
    TBool ret = EFalse;
    for(TInt i = 0; i < aTextToTest.Length(); i++)
        {
        TChar c (aTextToTest[i]);

        TChar::TCategory cat = c.GetCategory();
        if ( !c.IsSpace() && cat != TChar::ECoCategory && cat != TChar::ECfCategory ) 
            { // not space and not private use char 
            ret = ETrue;
            break;
            }
        }

    return ret;
    }


static TChar NumberToBase(TChar ch)
    {
    TDigitType d[] = { EDigitTypeWestern, EDigitTypeArabicIndic, EDigitTypeEasternArabicIndic, EDigitTypeDevanagari, EDigitTypeThai };
    TInt i = 0;
    TInt num = sizeof(d)/sizeof(d[0]);
    while(i<num)
        {
        if (ch>TChar(d[i]) && ch<TChar(d[i]+10)) { return d[i]; }
        i++;
        }
    return ch;
    }

EXPORT_C void AknTextUtils::LanguageSpecificNumberConversion(TDes &aDes)
    {   
    if (DigitModeQuery())
    {
    TLocale locale;
    locale.Refresh();
    TDigitType d = locale.DigitType();
    TChar toArea = 0x030;
    switch(d)
        {
        case EDigitTypeWestern:
        case EDigitTypeArabicIndic:
        case EDigitTypeEasternArabicIndic:
        case EDigitTypeDevanagari:
        case EDigitTypeThai:
            toArea = d;
            break;
        case EDigitTypeUnknown:
        case EDigitTypeAllTypes:
            return;
        }
    TInt length = aDes.Length();
    for(TInt i=0;i<length;i++)
        {
        TChar ch = aDes[i];
        TChar fromArea = NumberToBase(ch);
        TChar::TBdCategory cat = ch.GetBdCategory();
        switch(cat)
            {
            case TChar::EArabicNumber:
            case TChar::EEuropeanNumber:
                ch += toArea;
                ch -= fromArea;
                aDes[i] = TUint16(ch);
                break;

            default: ; break;
            };
        }
    }

    }

EXPORT_C void AknTextUtils::ConvertDigitsTo( TDes& aDes, TDigitType aDigitType ) 
    {
    TChar toArea = aDigitType;
    TInt length = aDes.Length();
    for(int i=0; i<length; i++) 
        {
        TChar ch = aDes[i];
        TChar base = NumberToBase(ch);
        switch (base) 
            {
            case EDigitTypeWestern:
            case EDigitTypeArabicIndic:
            case EDigitTypeEasternArabicIndic:
            case EDigitTypeDevanagari:
            case EDigitTypeThai:
                ch += toArea - base; 
                aDes[i] = TUint16(ch);
                break;
            default:
                break;
            };
        }
    }

/**
* This implementation uses the Avkon setting cache to get the input language and 
* Then puts it through the method provided by the GDI component
*
*/
EXPORT_C TBidiText::TDirectionality AknTextUtils::CurrentScriptDirectionality()
    {
    CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
    return TBidiText::ScriptDirectionality( cache.InputLanguage() );
    }


/**
Derive the digit type for text editor display from the current locale settings and 
current input language.
The digit type should be retrieved on construction and each time the locale settings change.
This implementation is really only handling Arabic at the moment.
*/
TDigitType AknTextUtils::InputLanguageFilteredDigitType()
    {
    TBool useNonLatin = DigitModeQuery(EDigitModeEditorDefault);
    TDigitType retDigitType(EDigitTypeWestern);
    if (useNonLatin)
        {
        TLocale locale;
        retDigitType = locale.DigitType();
        }
    return retDigitType;    
    }

/**
Derive the digit type for umeric editors where the localized digit setting must be filtered
to have an appropriate display text language.
This implementation is pretty thorough and should be OK for Farsi, Urdu, Thai as well as Arabic.
*/
TDigitType AknTextUtils::DisplayTextLanguageFilteredDigitType()
    {
    TBool useNonLatin = DigitModeQuery(EDigitModeNumberEditor);
    TDigitType retDigitType(EDigitTypeWestern);
    if (useNonLatin)
        {
        TLocale locale;
        retDigitType = locale.DigitType();
        }
    return retDigitType;    
    }
/**
* This implementation maps the specification issue that purely numeric editors should filter
* on display text language.
*/
EXPORT_C TDigitType AknTextUtils::NumericEditorDigitType()
    {
    return DisplayTextLanguageFilteredDigitType();
    }

/**
* This implementation maps the specification issue that alphanumeric editors should filter
* on input language.
*/
EXPORT_C TDigitType AknTextUtils::TextEditorDigitType()
    {
    return InputLanguageFilteredDigitType();
    }

/**
* This convenience method converts a display text to presentation form based upon the digit 
* type setting and the current display text language.
*/
EXPORT_C void AknTextUtils::DisplayTextLanguageSpecificNumberConversion(TDes &aDes)
    {
    TDigitType d = DisplayTextLanguageFilteredDigitType();
    TChar toArea = d;
    const TChar maxDigitTypeChar(0x1000);

    TInt length = aDes.Length();
    for(TInt i=0;i<length;i++)
        {
        TChar ch = aDes[i];
        TChar fromArea = NumberToBase(ch);
        TChar::TBdCategory cat = ch.GetBdCategory();
        switch(cat)
            {
            case TChar::EArabicNumber:
            case TChar::EEuropeanNumber:
                // The max range of DigitType is EDigitTypeThai(= 0x0E50) + 10.
                // No convert the charcter of U+1000 over unicode
                // (e.g. circled digits(U+2460-2473), full-width numbers?iU+FF00-FF10))
                if (maxDigitTypeChar > ch)
                    {
                    ch += toArea;
                    ch -= fromArea;
                    aDes[i] = TUint16(ch);
                    }
                break;

            default: 
//                  #ifdef RD_HINDI
                        if(ch >= 0x0966 && ch <= 0x096F) //Code range for Devanagari Number range. 
                        {
                            ch += toArea;
                                        ch -= fromArea;
                        aDes[i] = TUint16(ch);
                        }
//                  #endif//RD_HINDI
                    
             break;
            };
        }

    }

// arabic-indic digits are only available in arabic language. (not on hebrew)
static TBool IsArabicLanguage(TLanguage lang) 
    {
    lang = (TLanguage)((TInt)lang & KAknLanguageMask);
    return ((lang == ELangArabic) || (lang == ELangUrdu) || (lang == ELangFarsi)); 
    }
static TBool IsDigitTypeArabic(TDigitType dt) { return ((dt == EDigitTypeArabicIndic) || (dt == EDigitTypeEasternArabicIndic)); }
//#ifdef RD_HINDI
static TBool IsIndicLanguage(TLanguage lang)
    {
    lang = (TLanguage)((TInt)lang & KAknLanguageMask);
    TBool ret = EFalse;
    if ((lang == ELangHindi)
#ifdef RD_MARATHI
        || ( lang == ELangMarathi )
#endif // RD_MARATHI
    #ifdef RD_HINDI_PHONETIC_INPUT
    || (lang == KLangHindiPhonetic)
    #endif
    )
        ret = ETrue;
    return ret;
    }
static TBool IsDigitTypeIndic(TDigitType dt) { return dt == EDigitTypeDevanagari; }
//#endif//RD_HINDI


EXPORT_C TBool AknTextUtils::DigitModeQuery(TDigitModeQueryType t)
    {
    CAknSettingCache* settingsCache =   NULL;
    // some apps call this from their own threads, so need to check CEikonEnv::Static().
    if (CEikonEnv::Static()) settingsCache = &CAknEnv::Static()->SettingCache();
    TLocale locale;
    locale.Refresh();

    // Collect input for the algorithm to local variables
    TLanguage displayLanguage = User::Language(); // UI Language
    TLanguage inputLanguage = settingsCache ? settingsCache->InputLanguage() : displayLanguage;
    TDigitType digitType = locale.DigitType();

    //Hindi
    TBool inputBool;
    TBool uiBool;
    TBool digitBool;
    inputBool = 
//                          #ifdef RD_HINDI
                            IsIndicLanguage(inputLanguage)|
//                          #endif //RD_HINDI
                            IsArabicLanguage(inputLanguage);
    uiBool =        
//                          #ifdef RD_HINDI
                            IsIndicLanguage(displayLanguage)|
//                          #endif  //RD_HINDI
                            IsArabicLanguage(displayLanguage);
    digitBool = 
//                          #ifdef RD_HINDI 
                            IsDigitTypeIndic(digitType)|
//                          #endif  //RD_HINDI
                            IsDigitTypeArabic(digitType);
                            
    // Actual work of the method starts here
    TBool editor=EFalse, numberEditor=EFalse, changeable=EFalse, display = EFalse;

    if (!inputBool && !uiBool)             { editor = EFalse;                                         display = EFalse; }
    if (!inputBool && uiBool && digitBool) { editor = EFalse; numberEditor = ETrue;                   display = ETrue; }
    if (!inputBool && uiBool && !digitBool){ editor = EFalse;                                         display = EFalse; }
    if (inputBool && uiBool && digitBool)  { editor = ETrue;  numberEditor = ETrue; changeable=ETrue; display = ETrue; }
    if (inputBool && uiBool && !digitBool) { editor = EFalse;                       changeable=ETrue; display = EFalse; }
    if (inputBool && !uiBool)              { editor = EFalse;                       changeable=ETrue; display = EFalse; }

    // Choose correct output depending on what the caller wants.
    TBool result = EFalse;
    switch(t)
        {
        case EDigitModeEditorDefault:
            result = editor; 
            break;

        case EDigitModeUserModifiableEditor:
            result = changeable; 
            break;

        case EDigitModeShownToUser:
            result = display;
            break;

        case EDigitModeNumberEditor:
            result = numberEditor; 
            break;
            
        case EDigitModeLatinNumberEditor:
            result = EFalse; // conversion is never needed
            break;
        };
    return result;
    }

// LRM = 200e
// RLM = 200f
// LRE = 202a // embedding
// RLE = 202b
// PDF = 202c
// LRO = 202d // override
// RLO = 202e
_LIT( KConvLRE, "\x202a" );
_LIT( KConvRLE, "\x202b" );
_LIT( KConvPDF, "\x202c" );
_LIT( KConvLRM, "\x200e" );
_LIT( KConvRLM, "\x200f" );
EXPORT_C HBufC* AknTextUtils::ConvertFileNameL(const TDesC& aDes)
    {
    TPtrC fileName = aDes;
    TPtrC extension = _L("");
    TInt pos = aDes.Locate(TChar('.'));
    if (pos != KErrNotFound && pos > 0)
        {
        fileName.Set(aDes.Left(pos));
        extension.Set(aDes.Mid(pos));
        }
    HBufC *buf = HBufC::NewL(fileName.Length()+extension.Length()+4);
    TPtr bufptr = buf->Des();
    TBool found = EFalse;
    TBool rtl = TBidiText::TextDirectionality(fileName, &found) == TBidiText::ERightToLeft;
    if (!found) 
        {
        rtl=EFalse;
        
        // The file name does not contain any strongly directional characters.
        // File name is still rendered from the right to left if the
        // file name contains arabic or arabic-indic digits with neutral characters.
        TInt length = fileName.Length();
        TInt ii = 0;
        while ((ii < length) && !rtl)
            {
            TChar c = fileName[ii++];
            // GetBdCategory() for arabic-indic digits return value EEuropeanNumber.
            // For this reason this method cannot be used for arabic-indic digits.
            // Arabic-indic digits start from unicode 0x06f0 and end to unicode 0x06f9
            if (c.GetBdCategory() == TChar::EArabicNumber ||
                 ( c >= 0x06f0 && c <= 0x06f9 ) )               
                {
                rtl = ETrue;
                }
            }
        }
    
    if (rtl) 
        {
        bufptr.Append(KConvRLE);
        }
    else 
        { 
        bufptr.Append(KConvLRE);
        }

    bufptr.Append(fileName);
    bufptr.Append(KConvPDF);
    if (rtl) 
        { 
        bufptr.Append(KConvRLM);
        }
    else 
        { 
        bufptr.Append(KConvLRM);
        }
    bufptr.Append(extension);
    bufptr.Append(KConvPDF); // PDF  
    return buf;
    }



// AVKON TEXT WRAPPING

_LIT( KWrapToStringSeparator, "\n" );

// -----------------------------------------------------------------------------
// AknTextUtils::WrapToStringL()
// -----------------------------------------------------------------------------

void AknTextUtils::WrapToStringL(
    const TDesC& aStringToWrap, 
    const CArrayFix<TInt>& aLineWidthArray, 
    const CFont& aFont, 
    TDes& aWrappedString,
    TInt aFlags,
    TInt aDirectionality )
    {
    if ( aWrappedString.MaxLength() < aStringToWrap.Length() )
        {
        User::Leave( KErrOverflow );
        }

    aWrappedString.Copy( aStringToWrap );

    CArrayFixFlat<TPtrC>* wrappedArray =
        new( ELeave ) CArrayFixFlat<TPtrC>( 5 );

    CleanupStack::PushL( wrappedArray );

    WrapToArrayL( 
        aWrappedString,
        &aLineWidthArray,
        aFont,
        *wrappedArray,
        0,
        aFlags,
        aDirectionality );

    // Here we copy using the same descriptor as source and destination,
    // so have to be careful not to overwrite "source" before it is copied.

    TInt count( wrappedArray->Count() );
    aWrappedString.Zero();

    // first copy actual lines 

    for ( TInt i = 0 ; i < count ; i++ )
        {
        aWrappedString.Append( (*wrappedArray)[i] );
        }

    // then add newlines

    TInt index( 0 );

    for ( TInt j = 0 ; j < count ; j++ )
        {
        index += (*wrappedArray)[j].Length();

        if ( index >= aWrappedString.MaxLength() )
            {
            User::Leave( KErrOverflow );
            }

        aWrappedString.Insert( index, KWrapToStringSeparator );
        index++;
        }

    CleanupStack::PopAndDestroy(); // wrappedArray
    }

// -----------------------------------------------------------------------------
// AknTextUtils::WrapToArrayL()
// -----------------------------------------------------------------------------

void AknTextUtils::WrapToArrayL( 
    TDes& aStringToWrap,
    const CArrayFix<TInt>* aLineWidthArray, 
    const CFont& aFont,
    CArrayFix<TPtrC>& aWrappedArray,
    TInt aLineWidth,
    TInt aFlags,
    TInt aDirectionality )
    {
    TAknTextWrapper wrapper(
        aStringToWrap,
        aLineWidthArray,
        aFont,
        aWrappedArray,
        aLineWidth,
        aFlags,
        (AknBidiTextUtils::TParagraphDirectionality)aDirectionality );

    wrapper.WrapToArrayL();
    }

// -----------------------------------------------------------------------------
// AknTextUtils::ChopToArrayAndClipL()
// -----------------------------------------------------------------------------

void AknTextUtils::ChopToArrayAndClipL(
    TDes& aStringToChop,             
    const CArrayFix<TInt>* aLineWidthArray,
    const CFont& aFont,                 
    CArrayFix<TPtrC>& aChoppedArray,
    TInt aLineWidth )
    {
    TAknTextWrapper wrapper(
        aStringToChop,
        aLineWidthArray,
        aFont,
        aChoppedArray,
        aLineWidth,
        TAknTextWrapper::EClip,
        AknBidiTextUtils::EImplicit );

    wrapper.ChopToArrayAndClipL();
    }

EXPORT_C HBufC* AknTextUtils::LoadScalableTextL(CCoeEnv& aCoe, TInt aResourceId)
    {   
#ifdef _AKNUTILS_ENABLE_TRACES
    LOGTEXT( _L("WARNING: Deprecated method used: AknTextUtils::LoadScalableTextL") );
#endif // AKNUTILS_ENABLE_TRACES
    HBufC* ret = LoadScalableTextLC(aCoe,aResourceId);
    CleanupStack::Pop();
    return ret;
    }

EXPORT_C HBufC* AknTextUtils::LoadScalableTextLC(CCoeEnv& aCoe, TInt aResourceId)
    {
#ifdef AKNUTILS_ENABLE_TRACES
    LOGTEXT( _L("WARNING: Deprecated method used: AknTextUtils::LoadScalableTextLC") );
#endif // AKNUTILS_ENABLE_TRACES
    HBufC* ret = aCoe.AllocReadResourceL(aResourceId);
    ret = ClipAccordingScreenOrientationLC(aCoe, ret);
    return ret;
    }

EXPORT_C TInt AknTextUtils::LoadScalableText(CCoeEnv& aCoe, TInt aResourceId, TDes& aBuffer ) 
    {
#ifdef AKNUTILS_ENABLE_TRACES
    LOGTEXT( _L("WARNING: Deprecated method used: AknTextUtils::LoadScalableText") );
#endif // AKNUTILS_ENABLE_TRACES

    HBufC* temp = 0;
    TRAPD( result, temp = LoadScalableTextL(aCoe,aResourceId) );
    if (result == KErrNone)
        {
        aBuffer.Zero();
        aBuffer.Append(temp->Length() > aBuffer.Length()?temp->Des().Left(aBuffer.Length()-1):temp->Des());
        }
    delete temp;
    return result;
    }

EXPORT_C HBufC* AknTextUtils::ClipAccordingScreenOrientationLC(CCoeEnv& aCoe, HBufC* aBuf) 
    {
#ifdef AKNUTILS_ENABLE_TRACES
    LOGTEXT( _L("WARNING: Deprecated method used: AknTextUtils::ClipAccordingScreenOrientationLC") );
#endif // AKNUTILS_ENABLE_TRACES

    CleanupStack::PushL(aBuf);
    TInt separatorPos = aBuf->Des().Locate('|');
    if (separatorPos != KErrNotFound )
        {
        // solve screen orientation
        CAknAppUiBase::TAppUiOrientation screenOrientation= ((CAknAppUiBase*)aCoe.AppUi())->Orientation();
        if ( screenOrientation == CAknAppUiBase::EAppUiOrientationLandscape 
             && separatorPos != aBuf->Length() )
            {
            aBuf=aBuf->Des().Right(separatorPos+1).AllocL();
            }
        else
            {
            aBuf=aBuf->Des().Left(separatorPos).AllocL();            
            }
        CleanupStack::PopAndDestroy(); // old buf
        CleanupStack::PushL(aBuf); // resized buffer
        }
    return aBuf;
    }

// -----------------------------------------------------------------------------
// AknTextUtils::ChooseScalableText
// -----------------------------------------------------------------------------
//  
EXPORT_C TPtrC AknTextUtils::ChooseScalableText(
    const TDesC& aText,
    const CFont& aFont,
    TInt aMaxWidthInPixels )
    {
    // Get loc variants in an array.
    TAknLocVariant variants[KAknMaxLocVariants];
    TInt numVariants = TAknTextWrapper::GetLocVariants( aText, variants );

    TInt chosen = KErrNotFound;
    TInt chosenWidth = KMinTInt;

    TInt shortest = KErrNotFound;
    TInt shortestWidth = KMaxTInt;

    TInt start;

    for ( TInt i = 0 ; i < numVariants ; i++ )
        {
        start = variants[i].iStart;

        TInt width = aFont.TextWidthInPixels( 
            aText.Mid( start, variants[i].iEnd - start ) );

        // Update info of longest fitting one.
        if ( width <= aMaxWidthInPixels && width > chosenWidth )
            {
            chosen = i;
            chosenWidth = width;
            }

        // Update info of shortest one.
        if ( width < shortestWidth )
            {
            shortest = i;
            shortestWidth = width;
            }
        }

    // If none of the variants fits, return the shortest one in pixels.
    if ( chosen < 0 )
        {
        chosen = shortest;
        }

    start = variants[chosen].iStart;
    return aText.Mid( start, variants[chosen].iEnd - start );
    }

/**
* CompletePathWithAppPath
*   All the components that are specified in the given descriptor (drive letter,
*   path and file name, including extension) are put into the result;
*   any missing components (path and drive letter) are taken from the app's path.
*
*   Can be used e.g. to load a bitmap file when an application don't know where
*   it has been installed.
*
*   Example1:
*        TFilename fname = _L("\testdir\pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\testdir\pics.mbm" if application was installed to c:
*
*   Example2:
*        TFilename fname = _L("pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\system\apps\myapp\pics.mbm" if application was 
*                installed to c:\system\apps\myapp
*
*/
EXPORT_C TInt CompleteWithAppPath( TDes& aFileName )
    {
    TParse parse;
    TInt error = KErrNotSupported;
    
    CEikonEnv* env = CEikonEnv::Static(); 
    if ( env && 
        env->EikAppUi() && 
        env->EikAppUi()->Document() && 
        env->EikAppUi()->Application() )
        {
        TFileName appName = env->EikAppUi()->Application()->AppFullName();
        // Remove app name and extension
        TParsePtr appNamePtr(appName);
        appName = appNamePtr.DriveAndPath();
        error = parse.Set( aFileName, &appName, NULL);
        if ( !error )
            {
            aFileName.Zero();
            aFileName.Append( parse.FullName() );
            }
        }

    return error;
    }

EXPORT_C void AknEditUtils::ConstructEditingL(CEikEdwin* aEdwin, 
                                              TInt aEditingSpace, 
                                              TInt aEditingWindow, 
                                              TInt aCharacterCase, 
                                              TInt aJustification, 
                                              TBool aAllowedToMoveInsertionPoint, 
                                              TBool aCursorYesNo, 
                                              TBool aOverflowYesNo,
                                              TBool aIsResizable)
    {
    TMargins8 editorMargins;  
    editorMargins.iBottom = 0;
    editorMargins.iTop = 0;
    editorMargins.iRight = 0;
    editorMargins.iLeft = 0;

    aEdwin->SetBorderViewMargins(editorMargins); 
    TInt flags = 0;
    if (!aCursorYesNo) flags = CEikEdwin::EAvkonDisableCursor;
    if (aIsResizable && aEditingWindow != 1) flags |= CEikEdwin::EResizable; // max one row editor should not be resizable

    aEdwin->ConstructL(CEikEdwin::EWidthInPixels|CEikEdwin::ENoAutoSelection|flags, 0, aEditingSpace, aEditingWindow);

    TCharFormat charFormat;
    TCharFormatMask formatMask;
    CParaFormat paraFormat;
    TParaFormatMask paraFormatMask;

    TCursorSelection selection = aEdwin->Selection();
    STATIC_CAST(CGlobalText*, aEdwin->Text())->ApplyParaFormatL(&paraFormat,paraFormatMask,selection.LowerPos(),selection.Length());
    STATIC_CAST(CGlobalText*, aEdwin->Text())->ApplyCharFormatL(charFormat,formatMask,selection.LowerPos(),selection.Length());

    // Setting editor alignment must be done after
    // other editor paragraph formatting
    aEdwin->SetAlignment(aJustification);
    
    aEdwin->SetAknEditorCase( aCharacterCase ); // Argument is no longer and enum
    
    if ( !aAllowedToMoveInsertionPoint ) 
        {        
        // No implementation here
        }
    
    if ( aOverflowYesNo ) 
        {
        // No implementation here
        }
    }

static void IsAvailableLanguageL( const TInt aLanguage, TBool& aSupported )
    {
    aSupported = EFalse;
    
    CPtiEngine* ptiEngine = CPtiEngine::NewL();
    CleanupStack::PushL( ptiEngine );
    RArray<TInt> language(6);
    CleanupClosePushL( language );
    ptiEngine->GetAvailableLanguagesL( language );
    for ( int i = 0; i < language.Count(); i++ )
        {
        if ( language[i] == aLanguage )
            {
            aSupported = ETrue;
            break;
            }
        }
    CleanupStack::PopAndDestroy( &language );
    CleanupStack::PopAndDestroy( ptiEngine );
    }

EXPORT_C TInt DefaultInputLanguageFromUILanguage(const TInt aUiLanguage)
    {
    // Remove operator variant bits
    TInt inputLanguage = aUiLanguage & KAknLanguageMask;
    TBool supportedLang = EFalse;
    
    TRAP_IGNORE( IsAvailableLanguageL( inputLanguage, supportedLang ) );
    if ( supportedLang )
        {
        return inputLanguage;
        }
    
    // unknown, use default hard-coded convert code
    switch (inputLanguage)
        {
        case ELangAmerican:
        case KLangTaiwanEnglish:
        case KLangHongKongEnglish:
        case KLangPrcEnglish:
        case KLangThaiEnglish:
        case KLangApacEnglish:
        case KLangIndicEnglish:
             inputLanguage = ELangEnglish;
             break;
        case KLangJapaneseEnglish:
             inputLanguage = ELangJapanese;
             break;
        case ELangBrazilianPortuguese:
             inputLanguage = ELangPortuguese;
             break;
        case ELangCanadianFrench:
             inputLanguage = ELangFrench;
             break;
        case ELangBelgianFlemish:
             inputLanguage = ELangDutch;
             break;
        case ELangLatinAmericanSpanish:
             inputLanguage = ELangSpanish;
             break;
        case KLangApacMalay:
             inputLanguage = ELangMalay;
             break;
        case KLangApacIndonesian:
             inputLanguage = ELangIndonesian;
             break;
        default:
             break;
        }
    return inputLanguage;    
    }
    
// -----------------------------------------------------------------------------
// SetKeyblockMode
// -----------------------------------------------------------------------------
//
EXPORT_C void SetKeyblockMode( TAknKeyBlockMode aMode )
    {
    RAknUiServer client;
    if ( client.Connect() == KErrNone )
        {
        client.SetKeyblockMode( (TAknKeySoundOpcode) aMode );
        client.Close();
        }
    }

// -----------------------------------------------------------------------------
// AknDateTimeUtils::ConvertUtcTimeToHomeTime
// -----------------------------------------------------------------------------
//
EXPORT_C void AknDateTimeUtils::ConvertUtcTimeToHomeTime( TTime& aTime )
    {
    TTimeIntervalSeconds universalTimeOffset( User::UTCOffset() );
    aTime += universalTimeOffset;
    }

// -----------------------------------------------------------------------------
// AknLangUtils::DisplayLanguageTagL
// -----------------------------------------------------------------------------
//
EXPORT_C HBufC* AknLangUtils::DisplayLanguageTagL()
    {
    HBufC* tag = StringLoader::LoadL( R_QTN_LANGUAGE_RFC3066_TAG, CEikonEnv::Static() );
    return tag;
    }

// -----------------------------------------------------------------------------
// AknLangUtils::UserLanguage
// -----------------------------------------------------------------------------
//
TLanguage AknLangUtils::UserLanguage()
    {
    return (TLanguage)(User::Language() & KAknLanguageMask);
    }

// -----------------------------------------------------------------------------
// AknPopupUtils::Position
// -----------------------------------------------------------------------------
//
EXPORT_C TPoint AknPopupUtils::Position( const TSize& aSize, 
        TBool aSoftkeysVisible )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( TRect(), AknLayoutScalable_Avkon::Screen( 0 ) );
    
    TRect screen( layoutRect.Rect() );
    
    TInt x = ( screen.Width() - aSize.iWidth ) >> 1;
    TInt y = screen.Height() - aSize.iHeight;

    // Popups are centered on y-axis if screen orientation is landscape or
    // softkeys are not visible.
    if ( !aSoftkeysVisible || Layout_Meta_Data::IsLandscapeOrientation() )
        {
        y >>= 1; 
        }

    return TPoint( x, y );
    }


// -----------------------------------------------------------------------------
// AknPopupUtils::Position
// -----------------------------------------------------------------------------
//
EXPORT_C TPoint AknPopupUtils::Position( const TSize& aSize, 
        CCoeControl* aControl )
    {
    TBool softkeys = EFalse;
    
    if ( aControl )
        {
        CEikCba* cba = aControl->MopGetObjectNoChaining( cba );

        if ( cba )
            {
            softkeys = ( cba->IsVisible() && !cba->IsEmpty() );
            }
        }
    
    return Position( aSize, softkeys );
    }
    
// End of file

