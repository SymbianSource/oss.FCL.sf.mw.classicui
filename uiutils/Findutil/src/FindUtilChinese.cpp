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
* Description:         Chinese Find Utilities implementation file.
*
*/









#include <PtiEngine.h>
#include <centralrepository.h>
#include <AknFepInternalCRKeys.h>
#include <AvkonInternalCRKeys.h>
#include <aknedsts.h>
#include <coeaui.h>
#include <aknenv.h> //phonebook
#include <aknappui.h>
#include <aknapp.h>
#include <eikenv.h>
#include <eikapp.h>
#include <eikappui.h>


#include "FindUtilChinese.h"
#include "ChineseFindUtils.h"

// CONSTANTS 
const TUint16 KStarChar = 0x002a;   
const TUint16 KZhuyinstart = 0x3105;
const TInt KZhuyincount = 37;
const TInt KSeperator = 2626;
const TInt KMaxWordInterpretationLen = 255;
const TInt16 KMinUnicodeHz = 0x4e00;
const TInt16 KStrokeHorizontalValue = 0x4e00; 
const TInt16 KStrokeVerticalValue = 0x4e28;
const TInt16 KStrokeDownToLeftValue = 0x4e3f;
const TInt16 KStrokeDownToRightValue = 0x4e36;
const TInt16 KStrokeBendingValue = 0x4e5b;
const TInt KSysInputMode = -1;
const TInt KLeftToRightFlag =0x200e;
const TInt KRightToLeftFlag =0x200f;
const TUid KUidPhoneBook = {0x101F4CCE};
const TUid KUidPhoneBookServer = {0x10207277};

_LIT(KWildChar, "*");
_LIT(KUnderLine, "_");
_LIT(KMiddleLine, "-");
_LIT(KBlank, " ");
_LIT(KTab, "\t");

const TInt KLitLineFeed(8233);
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------
// Factory function at first ordinal to create concrete object of MFindUtil
// ---------------------------------------------------------
//
EXPORT_C MFindUtil* FindUtilFactoryFunctionL()
    {
    MFindUtil* util = CFindUtilChinese::NewL();
    return util;
    }

// ---------------------------------------------------------
// Symbian constructor
// ---------------------------------------------------------
//
CFindUtilChinese* CFindUtilChinese::NewL()
    {
    CFindUtilChinese* self = new (ELeave) CFindUtilChinese();
    
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);//self

    return self;
    }

// ---------------------------------------------------------
// Symbian second-phase constructor
// ---------------------------------------------------------
//
void CFindUtilChinese::ConstructL()
    {
    iRepositoryFind = CRepository::NewL(KCRUidAknFep);
    
    iRepositoryFindAdaptive = CRepository::NewL(KCRUidAvkon);

    iWatcher = CFindRepositoryWatcher::NewL(KCRUidAknFep,
                                            TCallBack(HandleFindRepositoryCallBack, this),
                                            iRepositoryFind);
                                            
    iWatcherAdaptive = CFindRepositoryWatcher::NewL(KCRUidAvkon,
                                            TCallBack(HandleFindRepositoryCallBack, this),
                                            iRepositoryFindAdaptive);                                        
    }

// ---------------------------------------------------------
// CFindUtilChinese utils class
// ---------------------------------------------------------
//
CFindUtilChinese::CFindUtilChinese():
    iLanguage(ELangTest),
    iSupportPRCChinese(EFalse),
    iCurInputMode(KSysInputMode),
    iSearchMethodPRC(EAdptSearchPinyin),
    iSearchMethodTaiWan(EAdptSearchZhuyin),
    iSearchMethodHongKong(EAdptSearchStroke),
    iSearchMethodAdaptive(EFalse)
    {
    }

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
//
CFindUtilChinese::~CFindUtilChinese()
    {
    delete iPtiEngine;
    delete iWatcher;
    delete iPtiEnginePrc;
    delete iRepositoryFind;
    delete iWatcherAdaptive;
    delete iRepositoryFindAdaptive;
    }

// ---------------------------------------------------------
// Open ptiengine and active it by input language
// ---------------------------------------------------------
//
TBool CFindUtilChinese::OpenT9InterfaceL(TLanguage aLanguage)
    {
    if (!iPtiEngine)
        {
        iPtiEngine = CPtiEngine::NewL();
        iSupportPRCChinese = IsSupportLanguage(ELangPrcChinese);
        }

    if (aLanguage != iLanguage)
        {
        iLanguage = aLanguage;
        iPtiEngine->ActivateLanguageL(iLanguage);
        iPtiEngine->EnableToneMarks(EFalse);
        }

    return ETrue;
    }

// ---------------------------------------------------------
// Close ptiengine
// ---------------------------------------------------------
//
void CFindUtilChinese::CloseT9InterfaceL()
    {
    iLanguage = ELangTest; 
    iPtiEngine->CloseCurrentLanguageL();
    }

// ---------------------------------------------------------
// Translate Chinese word to its spelling
// ---------------------------------------------------------
//
TBool CFindUtilChinese::DoTranslationL(TInt16 aHZUnicode,  
                                       RPointerArray<HBufC>& aSpellList)
    {
    if(CEikonEnv::Static())
        {
        if (iSearchMethodAdaptive &&(CEikonEnv::Static()->EikAppUi()->Application()->AppDllUid() == KUidPhoneBook ||
                CEikonEnv::Static()->EikAppUi()->Application()->AppDllUid() == KUidPhoneBookServer ))
                {
                if (!T9ChineseTranslationAdaptiveL(aHZUnicode, aSpellList))
                    {
                    return EFalse;
                    }    
                }
            else
                {
                if (!T9ChineseTranslationL(aHZUnicode, aSpellList))
                    {
                    return EFalse;
                    }    
                }
        }
    else
        {
        if (iSearchMethodAdaptive)
            {
            if (!T9ChineseTranslationAdaptiveL(aHZUnicode, aSpellList))
                {
                return EFalse;
                }
            }
        else
            {
            if (!T9ChineseTranslationL(aHZUnicode, aSpellList))
                {
                return EFalse;
                }
            }
        }
    return ETrue;
    
    }

// ---------------------------------------------------------
// Find pane text is including stroke symbol
// ---------------------------------------------------------
//
TInt CFindUtilChinese::IsStrokeSymbol(const TInt aFindWord)
    {
    TInt strokeValue = 0;

    switch (aFindWord)
        {
        case KStrokeHorizontalValue:
            strokeValue = 1;
            break;
        case KStrokeVerticalValue:
            strokeValue = 2;
            break;
        case KStrokeDownToLeftValue:
            strokeValue = 3;
            break;
        case KStrokeDownToRightValue:
            strokeValue = 4;
            break;
        case KStrokeBendingValue:
            strokeValue = 5;
            break;
        default:
            return strokeValue;
        }// switch

    return strokeValue;
    }

// ---------------------------------------------------------
// Do translate for Chinese word
// ---------------------------------------------------------
//
TBool CFindUtilChinese::T9ChineseTranslationL(TInt16 aHZUnicode,  
                                             RPointerArray<HBufC>& aSpellList)
    {
    TBuf<KMaxWordInterpretationLen> wordInterpretationBuf;
    
    if ( iLanguage == ELangPrcChinese )
        {
        if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiPinyin) 
                                    != KErrNone)
            {
            return EFalse;
            }
        }
    else if ( iLanguage == ELangTaiwanChinese )
        {
        if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiZhuyin) 
                                    != KErrNone)
            {
            return EFalse;
            }
        }
    else if ( iLanguage == ELangHongKongChinese )
        {
        if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiStrokes) 
                                    != KErrNone)
            {
            return EFalse;
            }
        }
    else if ( iLanguage == ELangEnglish )
        {
        if (!iSupportPRCChinese)
            {
            return EFalse;
            }
            
        TInt err = KErrNone;
        if (!iPtiEnginePrc)
            {
            iPtiEnginePrc = CPtiEngine::NewL(EFalse);
            TRAP(err, iPtiEnginePrc->ActivateLanguageL(ELangPrcChinese));
            }   
                   
        if (err == KErrNone)
            {
            if (iPtiEnginePrc->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiPinyin) 
                                           != KErrNone) 
                
                return EFalse;
            }
        }
    else
        {
        return EFalse;
        }
                
    const TInt len = wordInterpretationBuf.Length();
    TInt start = 0;
    
  
	for (TInt i =0; i < len; i++)
	    {
	    if (wordInterpretationBuf[i] == KSeperator) 
	        {
	        aSpellList.Append((wordInterpretationBuf.MidTPtr(start, i-start)).Alloc());
	        start = i + 1;
	        }
	    }
	        
	aSpellList.Append((wordInterpretationBuf.MidTPtr(start, len-start)).Alloc());   	

    
    return ETrue;
	}

// ---------------------------------------------------------
// Do translate for Chinese word
// ---------------------------------------------------------
//
TBool CFindUtilChinese::T9ChineseTranslationAdaptiveL(TInt16 aHZUnicode,  
                                             RPointerArray<HBufC>& aSpellList)
    {
    TBuf<KMaxWordInterpretationLen> wordInterpretationBuf;
    
    if ( iLanguage == ELangPrcChinese )
        {
        if(iSearchMethodPRC == EAdptSearchPinyin)
	        {
	        if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiPinyin) 
                                    != KErrNone)
	            {
	            return EFalse;
	            }	
	        }
	    else if(iSearchMethodPRC == EAdptSearchStroke)    
		    {
		    if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiStrokes) 
                                    != KErrNone)
	            {
	            return EFalse;
	            }	
		    }
		else
			{
			return EFalse;	
			}    
        
        }
    else if ( iLanguage == ELangTaiwanChinese )
        {
        if(iSearchMethodTaiWan == EAdptSearchZhuyin)
	        {
	        if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiZhuyin) 
                                    != KErrNone)
	            {
	            return EFalse;
	            }	
	        }
	    else if(iSearchMethodTaiWan == EAdptSearchStroke)    
		    {
		    if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiStrokes) 
                                    != KErrNone)
	            {
	            return EFalse;
	            }	
		    }
		else
			{
			return EFalse;	
			}       
        }
    else if ( iLanguage == ELangHongKongChinese )
        {
        switch(iSearchMethodHongKong)
	        {
	        case EAdptSearchNormalCangjie:
        	     if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiCangJie) 
	                                    != KErrNone)
		            {
		            return EFalse;
		            }
        	     break;
        	case EAdptSearchEasyCangjie:
        		if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiEasyCangjie) 
	                                    != KErrNone)
		            {
		            return EFalse;
		            }
        	     break;
        	case EAdptSearchAdvCangjie:
        	     if ((iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiCangJie) != KErrNone)
        	         &&(iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiEasyCangjie) != KErrNone))
		            {
		            return EFalse;
		            }
        	     break;
        	case EAdptSearchStroke:
	        	if (iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiStrokes) 
	                                    != KErrNone)
		            {
		            return EFalse;
		            }
        	     break;
        	default:
        	     return EFalse;        	
	        }
     
        }
    else if ( iLanguage == ELangEnglish )
        {
        if (!iSupportPRCChinese)
            {
            return EFalse;
            }
            
        TInt err = KErrNone;
        if (!iPtiEnginePrc)
            {
            iPtiEnginePrc = CPtiEngine::NewL(EFalse);
            TRAP(err, iPtiEnginePrc->ActivateLanguageL(ELangPrcChinese));
            }   
                   
        if (err == KErrNone)
            {
            if (iPtiEnginePrc->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiPinyin) 
                                           != KErrNone) 
                
                return EFalse;
            }
        }
    else
        {
        return EFalse;
        }
                
    TInt len = wordInterpretationBuf.Length();
    TInt start = 0;
    
    if( iSearchMethodHongKong != EAdptSearchAdvCangjie )
	    {
	    for (TInt i =0; i < len; i++)
	        {
	        if (wordInterpretationBuf[i] == KSeperator) 
	            {
	            aSpellList.Append((wordInterpretationBuf.MidTPtr(start, i-start)).Alloc());
	            start = i + 1;
	            }
	        }
	        
	    aSpellList.Append((wordInterpretationBuf.MidTPtr(start, len-start)).Alloc());   	
	    }
    //Could look advanced cangjie as normal and easy cangjie
    else 
	    {
	    iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiEasyCangjie);
	    len = wordInterpretationBuf.Length();
        start = 0;
	    for (TInt i =0; i < len; i++)
	        {
	        if (wordInterpretationBuf[i] == KSeperator) 
	            {
	            aSpellList.Append((wordInterpretationBuf.MidTPtr(start, i-start)).Alloc());
	            start = i + 1;
	            }
	        }
        
    	aSpellList.Append((wordInterpretationBuf.MidTPtr(start, len-start)).Alloc()); 
    	 
    	
    	iPtiEngine->GetSpelling(aHZUnicode, wordInterpretationBuf, EPtiCangJie);
	    len = wordInterpretationBuf.Length();
        start = 0;
	    for (TInt i =0; i < len; i++)
	        {
	        if (wordInterpretationBuf[i] == KSeperator) 
	            {
	            aSpellList.Append((wordInterpretationBuf.MidTPtr(start, i-start)).Alloc());
	            start = i + 1;
	            }
	        }
        
    	aSpellList.Append((wordInterpretationBuf.MidTPtr(start, len-start)).Alloc());  
	    }
    
    return ETrue;
    } 

// ---------------------------------------------------------
// Find pane text is including separator
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsFindWordSeparator(TChar aCh)
    {
    return aCh ==' '|| aCh=='-'|| aCh =='\t' || aCh == '_'|| aCh == KLitLineFeed;
    } 

// ---------------------------------------------------------
// Create ptiengine and initialize member data 
// ---------------------------------------------------------
//
void CFindUtilChinese::OpenL()
    {
    CFindUtilBase::OpenL();
    TInt inputLanguage = 0;
    TInt searchMode =0;
   
    if (iRepositoryFind != NULL)
        {
        iRepositoryFind->Get(KAknFepInputTxtLang, inputLanguage);
        }

    OpenT9InterfaceL((TLanguage)inputLanguage);
    
    if (iRepositoryFindAdaptive != NULL)
        {
        iRepositoryFindAdaptive->Get(KAknAvkonAdaptiveSearchEnabled, iSearchMethodAdaptive);
        }
    if( inputLanguage == ELangPrcChinese)
	    {
	    iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChinesePRC , searchMode);	
	    if(searchMode ==0)
		    {
		    iSearchMethodPRC = EAdptSearchPinyin;	
		    }
	    else if(searchMode ==1)
		    {
		    iSearchMethodPRC = EAdptSearchStroke;	
		    }
	    }
    else if(inputLanguage == ELangTaiwanChinese)
	    {
	    iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseTW , searchMode);
	    if(searchMode ==0)
		    {
		    iSearchMethodTaiWan = EAdptSearchZhuyin;	
		    }
	    else if(searchMode ==1)
		    {
		    iSearchMethodTaiWan = EAdptSearchStroke;	
		    }	
	    }
    else if(inputLanguage == ELangHongKongChinese)
	    {
	    iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseHongkong  , searchMode);
	    if(searchMode ==1)
		    {	    
		    iRepositoryFind->Get(KAknFepCangJieMode , searchMode);

		    switch (searchMode)
			    {
			    case 0:
		    	   iSearchMethodHongKong = EAdptSearchNormalCangjie;
		    	   break;
		    	case 1:
		    	   iSearchMethodHongKong = EAdptSearchEasyCangjie;
		    	   break;
		    	case 2:
		    	   iSearchMethodHongKong = EAdptSearchAdvCangjie;
		    	   break;
			    }
		    	   
		    }
	    else if(searchMode ==0)
		    {
		    iSearchMethodHongKong = EAdptSearchStroke;	
		    }
		    	
	    }
    
    }

// ---------------------------------------------------------
// Close ptiEngine 
// ---------------------------------------------------------
//
void CFindUtilChinese::Close()
    {
    // Only close T9 interface if this was the last reference
    if (iReferenceCount == 1)
        {
        TRAP_IGNORE(CloseT9InterfaceL());    
        }
        
    CFindUtilBase::Close();
    }

// ---------------------------------------------------------
// Match arithmetic for general search
// ---------------------------------------------------------
//
TBool CFindUtilChinese::Match(const TDesC& aContactsField, const TDesC& aWord)
    {
    // Check function parameter
    if (aWord.Length() == 0)
        {
        return ETrue;
        }
 
    if (aContactsField.Length() == 0)
        {
        return EFalse;
        }
    
    TBool ret = EFalse; 
    
    // Check Chinese word in find pane
    TBool chineseWord = IsChineseWord(aWord);
    
    if (chineseWord)
        {
        ret = IncludeString(aContactsField, aWord);
       
        if (ret)
            {
            // Included return ETrue
            return ret;
            }
   /*     else// If it do not find, check the symbol
            {
            // if Stroke Symbol in HongKong
            TBool strokeSymHK = (IsStrokeSymbolInString(aWord)) && 
                               (iLanguage == ELangHongKongChinese);
                               
            // it is not include stroke symbol
            if (!strokeSymHK)
                {
                return ret;
                }
            }*/
       }
    
    // Array for item string
    RPointerArray<STRINGINFO> stringInfoArr;
    // Split item string
    TRAPD(err, SplitItemStringL(stringInfoArr, aContactsField));
    if (err != KErrNone)
        {
        stringInfoArr.ResetAndDestroy();
        stringInfoArr.Close();
        return ret;
        }
    
    TInt index = 0;
    STRINGINFO* pStringInfo;
    const TInt arrayCount = stringInfoArr.Count();

    if (!chineseWord)
        {
        // Search English word
        for (index = 0; index < arrayCount; index ++)
            {
            pStringInfo = stringInfoArr[index];
            if (!pStringInfo->isChinese &&
                pStringInfo->segmentString.MatchC(aWord) != KErrNotFound)
                {
                ret = ETrue;
                break;
                }
            }
        }
    
    if (!ret)// If not find, search Chinese word 
        {
        TRAP(err, ret = MatchChineseInitialStringL(stringInfoArr, aWord));
        }

    stringInfoArr.ResetAndDestroy();
    stringInfoArr.Close();

    return ret;
    }

// ---------------------------------------------------------
// Initial character search 
// ---------------------------------------------------------
//
TBool CFindUtilChinese::MatchChineseInitialStringL(RPointerArray<STRINGINFO>& aStringInfoArr, 
                                                  const TDesC& aSearchStr)
    {
    TInt spellCount = 0;
    TInt i = 0;
    TInt chineseWordCount;
    TInt chineseWordIndex;
    STRINGINFO* pStringInfo;	
    TBool ret = EFalse;
    const TInt arrayCount = aStringInfoArr.Count();
    
    for (TInt index = 0; index < arrayCount; index ++)
        {
        pStringInfo = aStringInfoArr[index];
        // English word, continue
        if (!pStringInfo->isChinese)
            {
            continue;
            }
    
        chineseWordCount = pStringInfo->segmentString.Length();

        for (chineseWordIndex = 0; chineseWordIndex < chineseWordCount; chineseWordIndex ++)
            {
            RPointerArray<HBufC> spellList;
                            
            if (!DoTranslationL(TInt16(pStringInfo->segmentString[chineseWordIndex]), spellList))
                {
                spellList.ResetAndDestroy();//destroy spellList
                spellList.Close();                
                continue;
                }
                    
            spellCount = spellList.Count();
            // Search all spelling
            for (i = 0; i < spellCount; i++)
                {                
                if (spellList[i]->MatchC(aSearchStr) != KErrNotFound)
                    {
                    // If find, break
                    ret = ETrue;
                    break;
                    }
                }//end for
                    
            spellList.ResetAndDestroy();//destroy spellList
            spellList.Close();
              
            if (ret)
                {
                // If find, return
                return ret;
                }
            }
       }
 
    return ret;    
    }

// ---------------------------------------------------------
// Remove separator from search text
// ---------------------------------------------------------
//
void CFindUtilChinese::RemoveSeparator(TDes& aSearchText)
    {
    TInt index = -1;
    TBuf<1> temp;
    
    temp.Copy(KUnderLine);
    while ((index = aSearchText.FindC(temp)) > 0)
        {
        aSearchText.Replace(index, 1, KNullDesC);
        }
    
    temp.Copy(KMiddleLine);    
    while ((index = aSearchText.FindC(temp)) > 0)
        {
        aSearchText.Replace(index, 1, KNullDesC);
        }
       
    temp.Copy(KBlank);    
    while ((index = aSearchText.FindC(temp)) > 0)
        {
        aSearchText.Replace(index, 1, KNullDesC);
        }
       
    temp.Copy(KTab);    
    while ((index = aSearchText.FindC(temp)) > 0)
        {
        aSearchText.Replace(index, 1, KNullDesC);
        }              
    }

// ---------------------------------------------------------
// Match arithmetic for accurate search 
// ---------------------------------------------------------
//
TBool CFindUtilChinese::MatchRefineL( const TDesC& aItemString, const TDesC &aSearchText)
    {
    TBuf<KMaxWordLength> tempBuf;    
    TBuf<KMaxWordLength> itemString;
       
    itemString.Zero();
    if ( KMaxWordLength > aItemString.Length() )
        {
        itemString.Copy( aItemString );
        }
    else
        {
        itemString.Copy( aItemString.Left( KMaxWordLength ) );
        }
    
    //trim the sepcial char
    if(itemString.Length()>0)
        {
        if(itemString[0]== KLeftToRightFlag || itemString[0]== KRightToLeftFlag)
            {
            itemString.Delete(0,1);
            itemString.Delete((itemString.Length()-1),1);    
            }
        }
    
    TBool haschineseword = EFalse; 
    
    // Check function parameter
    if (aSearchText.Length() == 0)
        {
        return ETrue;
        }
 
    if (aItemString.Length() == 0)
        {
        return EFalse;
        }
        
    TBool ret = EFalse;
    
    tempBuf.Zero();
    if ( KMaxWordLength > aSearchText.Length() )
        {
        tempBuf.Copy( aSearchText );
        }
    else
        {
        tempBuf.Copy( aSearchText.Left( KMaxWordLength ) );
        } 
    
    RemoveSeparator(tempBuf);
    
    if (iLanguage == ELangHongKongChinese)
        {
        UpdateCurrentInputMode();
        }
    else
        {
        iCurInputMode = KSysInputMode;
        }
             
    // Check Chinese word in find pane
    if (IsChineseWord(tempBuf))
        {
        haschineseword = ETrue;
        ret = IncludeString(aItemString, tempBuf);
        
        if (ret || ChineseWord( tempBuf ))
            {
            return ret;
            }
    /*    else
            {
            // if Stroke Symbol in HongKong
            TBool strokeSymHK = (IsStrokeSymbolInString(tempBuf)) && 
                                 (iLanguage == ELangHongKongChinese) &&
                                 iCurInputMode == 0x0020;
                                
            if (!strokeSymHK)
                {
                return ret;
                }
            }*/
        }

    //Find if search string has chinese word. 
    //Compare with item string if find chinese word in item string then delete it from search and item string.
    //if not then return EFalse.
    TBool InputMethodStroke = EFalse;
    if(iLanguage == ELangHongKongChinese && iCurInputMode == 0x0020)
        {
        InputMethodStroke = ETrue;
        }
    
    if (haschineseword)
        {
        TInt ii=0;
        TBuf<KMaxWordLength> tmpBuf;
        tmpBuf.Zero();
        
        ////translate the whole searchstring to spelllist
        while (ii< tempBuf.Length())
            {
            
            //if it is a valid chinese character
            if ((TInt)tempBuf[ii]>= KMinUnicodeHz && (!InputMethodStroke
                    ||(InputMethodStroke && !IsStrokeSymbol(tempBuf[ii]))))
                {
                
                RPointerArray<HBufC> spellList;
                
                //translate the chinese charater to spellList( pinyin or stroke )
                if( DoTranslationL(TInt16(tempBuf[ii]), spellList)
                    && ( tmpBuf.Length() + spellList[0]->Length() < KMaxWordLength)  )
                	{
                    tmpBuf.Append( spellList[0]->Des() );
                    }
                    
                spellList.ResetAndDestroy();
                spellList.Close();
                ii++;
                }
            //if not, just append it     
            else
                {
                if( tmpBuf.Length() + 1 < KMaxWordLength )
                	{
                    tmpBuf.Append( tempBuf[ii] );
                    }
                    
                ii++;
                }
            }
            
            tempBuf.Zero();
            tempBuf.Copy(tmpBuf);
        }

    // Array for item string
    RPointerArray<STRINGINFO> stringInfoArr;
    // Split item string
    SplitItemStringL(stringInfoArr, itemString);
    
    if (stringInfoArr.Count() > 0)
        {
        ret = MatchSegmentL(stringInfoArr, tempBuf);
        }

    stringInfoArr.ResetAndDestroy();
    stringInfoArr.Close();

    return ret;
    }

// ---------------------------------------------------------
// Splite the input text to sgement by language
// ---------------------------------------------------------
//
void CFindUtilChinese::SplitItemStringL(RPointerArray<STRINGINFO>& aStringInfoArr, 
                                        const TDesC &aItemString)
    {
    TBuf<KMaxWordLength> tempBuf;
    TBuf<KMaxWordLength> englishBuf;
    TBuf<KMaxWordLength> chineseBuf;
    
    tempBuf.Zero();
    englishBuf.Zero();
    chineseBuf.Zero();
    
    TInt index = 0;
    TUint32 temp = 0;
    TInt32 distance = 0;
    const TInt strLength = aItemString.Length();
    
    for (; index < strLength; index++)
        {
        if (IsFindWordSeparator(aItemString[index]))
            {
            // Check Chinese and English Buf. If it is not empty, 
            // add buf to Array
            InsertStrInforArrayL(aStringInfoArr, chineseBuf, ETrue);
            InsertStrInforArrayL(aStringInfoArr, englishBuf, EFalse);
            continue;
            }
        
        temp = aItemString[index];
        distance = (TInt32)(temp - KMinUnicodeHz);
        
        if (distance < 0)// English word
            {
            // Chinese word is end and add to array
            InsertStrInforArrayL(aStringInfoArr, chineseBuf, ETrue);
          
            // Add English word to array
            englishBuf.Append((TChar)aItemString[index]);
            }
        else // Chinese word
            {
            // English word is end and add to array
            InsertStrInforArrayL(aStringInfoArr, englishBuf, EFalse);
        
            // Add Chinese word to array
            chineseBuf.Append((TChar)aItemString[index]);
            }
        }
       
    // Finish loop check buffer is empty
    InsertStrInforArrayL(aStringInfoArr, chineseBuf, ETrue);
    InsertStrInforArrayL(aStringInfoArr, englishBuf, EFalse);
    }

// ---------------------------------------------------------
// Insert segment to list
// ---------------------------------------------------------
//
void CFindUtilChinese::InsertStrInforArrayL(RPointerArray<STRINGINFO>& aStringInfoArr, 
                                            TDes &aSegmentStr, const TBool aChinese)    
    {
    if (aSegmentStr.Length() <= 0)
        {
        return;
        }
   
    STRINGINFO* strInfo = new(ELeave) STRINGINFO;
           
    strInfo->segmentString.Zero();
    strInfo->segmentString.Copy(aSegmentStr);
    strInfo->segmentString.LowerCase();
    strInfo->isChinese = aChinese;
              
    aStringInfoArr.AppendL(strInfo);
    aSegmentStr.Zero();
    }

// ---------------------------------------------------------
// This segment is matched by search text
// ---------------------------------------------------------
//
TBool CFindUtilChinese::MatchSegmentL(RPointerArray<STRINGINFO>& aStringInfoArr, 
                                     const TDesC &aSearchText)
    {
    const TInt arrayLength = aStringInfoArr.Count();
    const TInt searchStrLength = aSearchText.Length();
    TInt searchStrIndex = 0;
    STRINGINFO* pStringInfo;
    TBuf<KMaxWordLength> tempBuf;
    TInt index = 0;

    // First only check English
    for (; index < arrayLength; index ++)
        {
        tempBuf.Zero();	
        pStringInfo = aStringInfoArr[index];
        
        tempBuf = aSearchText.Mid(searchStrIndex, searchStrLength - searchStrIndex);
   
        // Compare word
        if (!pStringInfo->isChinese)
            {
            searchStrIndex += MatchString(pStringInfo->segmentString, tempBuf);
            }
              
        if (searchStrIndex >= searchStrLength)
            {
            return ETrue;
            }       	
        }

    TBuf<KMaxWordLength> bufcurrent;
    TBuf<KMaxWordLength> tempbufcurrent;
    TInt searchStrIndextemp = 0;
    TInt searchStrIndexMax = 0;
    // Find Chinese and English
    searchStrIndex = 0;
    index = 0;
   
    for (; index < arrayLength; index ++)
        {
        tempBuf.Zero();
        pStringInfo = aStringInfoArr[index];
        
        tempBuf = aSearchText.Mid(searchStrIndex, searchStrLength - searchStrIndex);
        
        searchStrIndexMax = 0;
        
        bufcurrent = pStringInfo->segmentString;
        
        for(TInt i =0;i< pStringInfo->segmentString.Length();i++)
            {
            tempbufcurrent = bufcurrent.Mid(i);
            if (pStringInfo->isChinese)
                {
                TInt temp=0;
                searchStrIndextemp = MatchChineseStringL(tempbufcurrent, tempBuf,temp);  
                if(searchStrIndextemp > searchStrIndexMax)
                    {
                    searchStrIndex -= searchStrIndexMax;
                    searchStrIndexMax = searchStrIndextemp;
                    searchStrIndex += searchStrIndexMax;
                    }
                }
            else
                {
                searchStrIndex += MatchString(pStringInfo->segmentString, tempBuf);
                }
                  
            if (searchStrIndex >= searchStrLength)
                {
                return ETrue;
                }
            else if(!pStringInfo->isChinese)
                {
                break;
                }
            }          
        }
   
    return EFalse;   
    }

// ---------------------------------------------------------
// Search Chinese word in input text 
// ---------------------------------------------------------
//
TInt CFindUtilChinese::MatchChineseStringL(const TDesC& aFirst, const TDesC& aSecond,TInt& aIndex)
    {
    const TInt stringLength = aFirst.Length();
    const TInt searchLength = aSecond.Length();	
    TInt index = 0;
    TBuf<KMaxWordLength> tempBuf;
    TBuf<KMaxWordLength> previousBuf;
    TInt curMatchCount = 0;
    TInt preMatchCount = 0;
    TInt matchIndex = 0;
    TInt curSearchIndex = 0;
    TBool bFullMatched = EFalse;
    TBool bContinue = EFalse;
      
    for(; index < stringLength; index++)
        {
        RPointerArray<HBufC> spellList;
                        
        if (!DoTranslationL(TInt16(aFirst[index]), spellList) )
            {
            spellList.ResetAndDestroy();//destroy spellList
            spellList.Close();
                
            continue;
            }
            
        matchIndex = 0;
        bContinue = EFalse;
        
        // Get left string
        tempBuf = aSecond.Mid(curSearchIndex, searchLength - curSearchIndex);             
        
        // Get Matched count and the matched index in list     
        curMatchCount = MaxMatchInList(spellList, tempBuf, previousBuf, matchIndex, 
                                       bFullMatched, preMatchCount, bContinue);     
        
        // There is a string matched in list 
        if (curMatchCount != 0)
            {
            previousBuf.Copy(spellList[matchIndex]->Des());
           
            if (curMatchCount == previousBuf.Length())
                {
                bFullMatched = ETrue;
                }
            else
                {
                bFullMatched = EFalse;
                }

            // If it is repeat match, continue     
            if (!bContinue)
                {
                curSearchIndex += curMatchCount;    
                }
            else
                {
                bFullMatched = EFalse;
                previousBuf.Zero();
                curMatchCount = 0;
                }
            }
        else
            {
            bFullMatched = EFalse;
            previousBuf.Zero();
            if (curSearchIndex != 0)
                {
                index--;
                }
                
            curSearchIndex = 0;
            }

        spellList.ResetAndDestroy();//destroy spellList
        spellList.Close();
        preMatchCount = curMatchCount;
        
        // Search to End and return
        if (curSearchIndex >= searchLength)
           {
           break;
           }
      }
   aIndex = index;
   return curSearchIndex;
   }

// ---------------------------------------------------------
// Maximal matched count in spelling list  
// ---------------------------------------------------------
//
TInt CFindUtilChinese::MaxMatchInList(RPointerArray<HBufC> &spellList, TDesC& aSearchStr, 
    TDesC& aPreviouStr, TInt& aMatchIndex, const TBool aFullMatched, const TInt aMatchedCount, TBool& aAgain)
   {
   const TInt itemCount = spellList.Count();
   TInt matchCount = 0;
   TBool selfMatch = EFalse;
   aMatchIndex = 0;
   
   // If list is empty, then return
   if (itemCount == 0)
      {
      return matchCount;
      }
   
   TInt index = 0;
   TInt temp = 0;
   TBuf<KMaxWordLength> tempBuf;
   TInt repeatCount = 0;
   TBool loopFlag = EFalse;
   
   for (; index < itemCount; index++)
       {
       temp = 0;
       repeatCount = 0;
       loopFlag = EFalse;
       tempBuf.Zero();
       tempBuf.Copy(spellList[index]->Des());
        
       temp = MatchString(tempBuf, aSearchStr);
       if(temp != 0)
           {
           selfMatch = ETrue;
           }
       else
           {
           selfMatch = EFalse;
           }
       // Not find and previous word is not empty
       if (temp == 0 && aPreviouStr.Length() != 0)
           {
           // Previous word is fully matched
           if (aFullMatched)
               {
               repeatCount = ReverseMatchString(aPreviouStr, tempBuf);
               // Find repeat and remove it, search again
               if (repeatCount != 0)
                   {
                   temp = MatchString(tempBuf.Right(tempBuf.Length() - repeatCount), aSearchStr); 
                   
                   if (temp == 0)
                       {
                       loopFlag = ETrue;
                       temp = repeatCount;
                       }
                   }              
               }
           else
               {
               repeatCount = MatchString(aPreviouStr, tempBuf);

               // Find repeat and remove it, search again
               if (repeatCount != 0)
                   {
                   if (aMatchedCount <= repeatCount)
                       {
                       temp = MatchString(tempBuf.Right(tempBuf.Length() - aMatchedCount), aSearchStr);   
                       
                       if (temp == 0)
                           {
                           loopFlag = ETrue;
                           temp = aMatchedCount;                           
                           }
                       }
                   }
                   
               if (temp == 0)
                   {
                   repeatCount = ReverseMatchString(aPreviouStr.Left(aMatchedCount), tempBuf);
                   
                   if (repeatCount != 0)
                       {
                       temp = MatchString(tempBuf.Right(tempBuf.Length() - repeatCount), aSearchStr);
                       
                       if (temp == 0)
                           {
                           loopFlag = ETrue;
                           temp = repeatCount;
                           }
                       }                        
                   }
               }
           }
       
       // Find count is longer than before
       // Record new data
       if ((loopFlag == aAgain) &&
           (temp > matchCount))
           {
           matchCount = temp;
           aMatchIndex = index;
           aAgain = loopFlag;
           }
           
       if (loopFlag != aAgain &&
           loopFlag &&
           (temp > matchCount))
           {
           matchCount = temp;
           aMatchIndex = index;
           aAgain = loopFlag;            
           }           
           
       if (loopFlag != aAgain &&
           !loopFlag &&
           temp != 0)
           {
           matchCount = temp;
           aMatchIndex = index;
           aAgain = loopFlag;            
           }
        if(matchCount == aSearchStr.Length() && selfMatch)
            {
            break;
            }
       }
    return matchCount;	
   }

// ---------------------------------------------------------
// Search the taxt is include the input text  
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IncludeString(const TDesC& aFirst, const TDesC& aSecond)
    {
    TBuf<KMaxWordLength> tempBuf;
    tempBuf.Zero();
       
    if (TInt16(aSecond[0]) != KStarChar)
        {
        tempBuf.Append(KWildChar);
        }
      
    tempBuf.Append(aSecond);
      
    if (TInt16(aSecond[aSecond.Length() -1]) != KStarChar)
        {
        tempBuf.Append(KWildChar);
        }
        
    if (aFirst.MatchC(tempBuf) != KErrNotFound)
        {
        return ETrue;
        }
        
    return EFalse;
    }

// ---------------------------------------------------------
// Search text in other text  
// ---------------------------------------------------------
//
TInt CFindUtilChinese::MatchString(const TDesC& aFirst, const TDesC& aSecond)
    {
    const TInt secondStrLength = aSecond.Length();
    const TInt firstStrLength = aFirst.Length();
    const TInt compareCount = firstStrLength > secondStrLength ? secondStrLength : firstStrLength;
    TInt index = 0;
   
    TBuf<KMaxWordLength> tempStr;
    // translate search target string into numeric string before match
    if (iConverter)
        {
        iConverter->Converter( aFirst, tempStr );
        }
    else
        {
        tempStr.Copy(aFirst);
        }
    
    for (; index < compareCount; index++)
        {
		if (tempStr.Left(index + 1).FindC(aSecond.Left(index + 1)) == KErrNotFound)
            {
            break;
            }
        }
    // Match count
    return index;
    }
    
// ---------------------------------------------------------
// Search text by reverse  
// ---------------------------------------------------------
//
TInt  CFindUtilChinese::ReverseMatchString(const TDesC& aFirst, const TDesC& aSecond)
    {
    const TInt secondStrLength = aSecond.Length();
    const TInt firstStrLength = aFirst.Length();
    TInt compareCount = firstStrLength > secondStrLength ? secondStrLength : firstStrLength;
    TInt index = 0;
    TInt matchCount = 0;
   
    for (; index < compareCount; index++)
        {
        TBuf<KMaxWordLength> firstConvStr;
        TBuf<KMaxWordLength> secondConvStr;
        
        // translate compared target string into numeric string before match
        if ( iConverter )
            {
            iConverter->Converter( aFirst, firstConvStr );
            iConverter->Converter( aSecond, secondConvStr );
            }
        else
            {
            firstConvStr.Copy( aFirst );
            secondConvStr.Copy( aSecond );
            }
            
        if( firstConvStr.Right( index + 1 ).FindC( secondConvStr.Left( index + 1 ) ) != KErrNotFound )
            {
            matchCount = index + 1;
            }
        }
   
    return matchCount;	
    }

// ---------------------------------------------------------
// Current input text is handled by this model  
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsWordValidForMatching(const TDesC& /*aWord*/)
    {
    return ETrue;
    }

// ---------------------------------------------------------
// Find pane text is including Chinese word  
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsChineseWord(const TDesC& aWord)
    {
    TBool IsChineseSearchStr = EFalse;
    const TInt len = aWord.Length();
    
    for (TInt ii = 0; ii< len; ii++)
        {
        if ((TInt)aWord[ii] >= KMinUnicodeHz )
            {
            IsChineseSearchStr = ETrue;
            break;
            }
        }

    return IsChineseSearchStr;
    }

// --------------------------------------------------------
// Find pane text is just Chinese word
// --------------------------------------------------------
//
TBool CFindUtilChinese::ChineseWord(const TDesC& aWord)
	{
	TBool isChineseWord = ETrue;
	const TInt len = aWord.Length();
	
    TBool InputMethodStroke = EFalse;
    if(iLanguage == ELangHongKongChinese && iCurInputMode == 0x0020)
        {
        InputMethodStroke = ETrue;
        }
	
	for( TInt i = 0; i < len; i++ )
		{
		if( ( ( TInt )aWord[i] < KMinUnicodeHz ) || ( InputMethodStroke && IsStrokeSymbol(aWord[i]) ) )
			{
			isChineseWord = EFalse;
			break;
			}
		}
	return isChineseWord;
	}
    
// ---------------------------------------------------------
// Find pane text is including stroke symbol  
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsStrokeSymbolInString(const TDesC& aWord)
    {
    const TInt len = aWord.Length();
    
    for (TInt index = 0; index < len; index++)
        {
        if (IsStrokeSymbol(TInt(aWord[index])) != 0)
            {
            return ETrue;
            }
        }

    return EFalse;
    }

// ---------------------------------------------------------
// Find pane text is including zhuyin symbol  
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsZhuyinSymbolInString(const TDesC& aWord)
    {
    const TInt len = aWord.Length();
    
    for (TInt index = 0; index < len; index++)
        {
        if ((aWord[index] >= KZhuyinstart) && 
            (aWord[index] < KZhuyinstart + KZhuyincount))
            {
            return ETrue;
            }
        }

    return EFalse;
    }

// ---------------------------------------------------------
// This language is support by this model 
// ---------------------------------------------------------
//
TBool CFindUtilChinese::IsSupportLanguage(TLanguage aLang)    
    {
    if (iPtiEngine->GetLanguage(aLang))
        {
        return ETrue;
        }
        
    return EFalse;
    }    

// ---------------------------------------------------------
// Callback method to notify client about language change.
// ---------------------------------------------------------
//
TInt CFindUtilChinese::HandleFindRepositoryCallBack(TAny* aPtr)
    {
    TInt ret = KErrNone;
    CFindUtilChinese *self = static_cast<CFindUtilChinese*>(aPtr);
    TInt searchMode = 0;
    
    if (self->iWatcher->ChangedKey() == KAknFepInputTxtLang)
        {
        TInt inputLanguage = 0;
        self->iRepositoryFind->Get(KAknFepInputTxtLang, inputLanguage);

        TRAP(ret, self->OpenT9InterfaceL(TLanguage(inputLanguage)));
        }
    if(self->iWatcherAdaptive->ChangedKey() == KAknAvkonAdaptiveSearchEnabled)
        {
        self->iRepositoryFindAdaptive->Get(KAknAvkonAdaptiveSearchEnabled, self->iSearchMethodAdaptive);
        }
    
    if (self->iWatcherAdaptive->ChangedKey() == KAknAdaptiveSearchChinesePRC)
        {
        self->iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChinesePRC, searchMode);
       
        if(searchMode ==0)
		    {
		    self->iSearchMethodPRC = EAdptSearchPinyin;	
		    }
	    else if(searchMode ==1)
		    {
		    self->iSearchMethodPRC = EAdptSearchStroke;	
		    }
        }
    
    if (self->iWatcherAdaptive->ChangedKey() == KAknAdaptiveSearchChineseTW )
        {
        self->iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseTW , searchMode);
       
        if(searchMode ==0)
		    {
		    self->iSearchMethodTaiWan = EAdptSearchZhuyin;	
		    }
	    else if(searchMode ==1)
		    {
		    self->iSearchMethodTaiWan = EAdptSearchStroke;	
		    }
        }
        
    if (self->iWatcherAdaptive->ChangedKey() == KAknAdaptiveSearchChineseHongkong )
        {
        self->iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseHongkong , searchMode);
       
        if(searchMode ==1)
		    {
		    self->iRepositoryFind->Get(KAknFepCangJieMode , searchMode);
       
	        switch (searchMode)
		        {
		        case 0:
			       self->iSearchMethodHongKong = EAdptSearchNormalCangjie;
			       break;
			    case 1:
			       self->iSearchMethodHongKong = EAdptSearchEasyCangjie;
			       break;
			   	case 2:
			       self->iSearchMethodHongKong = EAdptSearchAdvCangjie;
			   	   break;	
		        }
			    
		    }
	    else if(searchMode ==0)
		    {
		    self->iSearchMethodHongKong = EAdptSearchStroke;	
		    }
        }
    
    if (self->iWatcher->ChangedKey() == KAknFepCangJieMode )
        {
        self->iRepositoryFind->Get(KAknFepCangJieMode , searchMode);
       
        switch (searchMode)
	        {
	        case 0:
		       self->iSearchMethodHongKong = EAdptSearchNormalCangjie;
		       break;
		    case 1:
		       self->iSearchMethodHongKong = EAdptSearchEasyCangjie;
		       break;
		   	case 2:
		       self->iSearchMethodHongKong = EAdptSearchAdvCangjie;
		   	   break;	
	        }
		    
        }
    
    return ret;    
    }

// ---------------------------------------------------------
// Update input method in ptiengine from find pane
// ---------------------------------------------------------
//
void CFindUtilChinese::UpdateCurrentInputMode()
    {
	CCoeEnv* coeEnv = NULL;
	coeEnv = CCoeEnv::Static();
	iCurInputMode = KSysInputMode;
	if (coeEnv)
        {
	    CAknEdwinState* pState = NULL;
	  
	    if (coeEnv->AppUi() == NULL)                              
	    	return;
	    	
	    TCoeInputCapabilities inputCapabilities = static_cast<const CCoeAppUi*>(coeEnv->AppUi())->InputCapabilities();
        MCoeFepAwareTextEditor* fepAvareTextEditor = inputCapabilities.FepAwareTextEditor();
        if (fepAvareTextEditor)
            {
            pState =  static_cast<CAknEdwinState*>(fepAvareTextEditor->Extension1()->State(KNullUid));
            if (pState)
                {
                iCurInputMode = pState->CurrentInputMode();
                }            
            }
        }
    }
// ---------------------------------------------------------------------------
// UpdateNextChar
// ---------------------------------------------------------------------------
//
void CFindUtilChinese::UpdateNextCharsL(HBufC*& aNextChars, TChar aCh)
	{
    if( aNextChars->Locate(aCh) == KErrNotFound )
		{			
		if( aNextChars->Des().Length() == aNextChars->Des().MaxLength())
			{
			aNextChars = aNextChars->ReAllocL( aNextChars->Des().MaxLength()+10 );
			}		
		aNextChars->Des().Append(aCh);								
		}
	}    

// ---------------------------------------------------------------------------
// UpdateNextCharFromString
// ---------------------------------------------------------------------------
//
void CFindUtilChinese::UpdateNextCharsFromStringL(HBufC*& aNextChars, const TDesC& aItemString)
	{
		
	 // Array for item string
    RPointerArray<STRINGINFO> stringInfoArr;
    // Split item string
    TRAPD(err, SplitItemStringL(stringInfoArr, aItemString));
    
    if (err != KErrNone)
        {
        stringInfoArr.ResetAndDestroy();
        stringInfoArr.Close();
        }
        
    TInt index = 0;
    STRINGINFO* pStringInfo;
    const TInt arrayCount = stringInfoArr.Count();


    for (index = 0; index < arrayCount; index ++)
        {
        pStringInfo = stringInfoArr[index];
        if (!pStringInfo->isChinese )
	        {
	        UpdateNextCharsL( aNextChars, pStringInfo->segmentString[0]);	
	        }
        else
	        {
            TInt chineseworkcount =  pStringInfo->segmentString.Length();
            
            for(TInt i =0;i<chineseworkcount;i++) 
            	{
    	        RPointerArray<HBufC> spellList;
                TBuf<KMaxWordLength> tempBuf;
            	if (!DoTranslationL(TInt16(pStringInfo->segmentString[i]), spellList))
	                {
	                UpdateNextCharsL( aNextChars, pStringInfo->segmentString[i]);
	                }
	            else
	                {
	                //for multiphnetic spell
                    TInt spellCount = spellList.Count();
                    // Search all spelling
                    for (TInt j = 0; j < spellCount; j++)
                        {
                	    tempBuf.Copy(spellList[j]->Des());
                	    UpdateNextCharsL( aNextChars, tempBuf[0]);                                        
                        }//end for
            	    }
            spellList.ResetAndDestroy();//destroy spellList
            spellList.Close();       	
	        }
        }
        }
    stringInfoArr.ResetAndDestroy();
    stringInfoArr.Close();
    		
	}

// ---------------------------------------------------------------------------
// TrimChineseCharacter
// ---------------------------------------------------------------------------
//
TBool CFindUtilChinese::TrimChineseCharacterL(TDes& aItemString, TDes& aSearchText,HBufC*& aNextChars)
    {
    TBuf<KMaxWordLength> tempBuf;    
    TBuf<KMaxWordLength> itemString;
    
    tempBuf.Zero();
        
    tempBuf.Copy(aSearchText);
       
    itemString.Zero();
        
    itemString.Copy(aItemString);
    
    TInt searchMode;
    TBool InputMethodStroke= EFalse;
    
    if ( iLanguage == ELangPrcChinese )
        {
        iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChinesePRC, searchMode);
        if(searchMode == 1)
            {
            InputMethodStroke = ETrue;
            }
        }
    else if ( iLanguage == ELangHongKongChinese)
        {
        iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseHongkong, searchMode);
        if(searchMode == 1)
            {
            InputMethodStroke = ETrue;
            }
        }
    else if( iLanguage == ELangTaiwanChinese)
        {
        iRepositoryFindAdaptive->Get(KAknAdaptiveSearchChineseTW, searchMode);
        if(searchMode == 0)
            {
            InputMethodStroke = ETrue;
            }
        }
    TInt ii =0;
    while (ii< tempBuf.Length())
        {
        if ((TInt)tempBuf[ii]>= KMinUnicodeHz && (!InputMethodStroke
                ||(InputMethodStroke && !IsStrokeSymbol(tempBuf[ii]))))
            {
            TInt Findcursor = itemString.Locate(tempBuf[ii]);
            if (Findcursor != KErrNotFound)
                {
                if ((Findcursor == itemString.Length()-1) && (ii
                        == tempBuf.Length()-1))
                    {
                    return ETrue;
                    }
                itemString.Delete(0, Findcursor+1);
                tempBuf.Delete(0, ii+1);
                if (tempBuf.Length()==0)
                    {
                    TBuf<KMaxWordLength> usefortrim;
                    usefortrim.Append(itemString[0]);
                    UpdateNextCharsFromStringL(aNextChars, usefortrim);
                    return ETrue;
                    }
                ii=0;
                }
            else
                {
                ii++;
                }
            }
        else
            {
            ii++;
            }
        
        }
     aSearchText.Zero();
     
     aSearchText.Copy(tempBuf);
     
     aItemString.Zero();
     
     aItemString.Copy(itemString);
     
     return EFalse;
     
    }
// ---------------------------------------------------------------------------
// CheckEnglishFirst
// ---------------------------------------------------------------------------
//
TBool CFindUtilChinese::CheckEnglishFirstL( RPointerArray<STRINGINFO>& aarray, TDes& aSearchText,HBufC*& aNextChars)
    {
    TBool ret = EFalse ;
    if (aarray.Count() > 0)
        {
        const TInt arrayLength = aarray.Count();
        const TInt searchStrLength = aSearchText.Length();
        TBuf<KMaxWordLength> tempBuf;
        TBuf<KMaxWordLength> temp;

        TInt searchStrIndex = 0;
        STRINGINFO* pStringInfo= NULL;
        TBuf<KMaxWordLength> transSearchBuf;
        TInt index = 0;

        tempBuf.Zero();

        tempBuf.Copy(aSearchText);
        // First only check English
        for (; index < arrayLength; index ++)
            {
            transSearchBuf.Zero();
            pStringInfo = aarray[index];

            transSearchBuf = tempBuf.Mid(searchStrIndex, searchStrLength
                    - searchStrIndex);

            // Compare word
            if (!pStringInfo->isChinese)
                {
                searchStrIndex += MatchString(pStringInfo->segmentString,
                        transSearchBuf);
                }

            if (searchStrIndex >= searchStrLength)
                {
                ret = ETrue;

                //append to next char
                if (pStringInfo->segmentString.Length() > searchStrIndex)
                    {
                    UpdateNextCharsL(aNextChars,
                            pStringInfo->segmentString[searchStrIndex]);
                    }
                break;
                }
            }
        //for english string add next character directly    
        if (ret)
            {
            if (arrayLength <= index+1)
                {
                return ret;
                }
            
            AppendCharInNextSegmentL(aarray,index+1,aNextChars);
            }
        }
    return ret;
    }
// ---------------------------------------------------------------------------
// AddNextIfOverlapL to check if overlap problem 
// ---------------------------------------------------------------------------
//
void CFindUtilChinese::AddNextIfOverlapL(const RPointerArray<STRINGINFO>& astringInfoArr ,
            const TInt aindex, const TInt aindexforfind, const TDes& aCurrentBuf,HBufC*& aNextChars )
{
    TBuf<KMaxWordLength> temp;
    TBuf<KMaxWordLength> tempNext;
    RPointerArray<HBufC> tempSpellList;
    STRINGINFO* pStringInfo;
    STRINGINFO* pStringInfoNext;
    
    if(astringInfoArr.Count()>aindex)
        {
        pStringInfo= astringInfoArr[aindex];
        }
    
    if (pStringInfo->isChinese)
        {
        if((pStringInfo->segmentString).Length()>aindexforfind+1)//in same segment
            {
            if (DoTranslationL(TInt16((pStringInfo->segmentString)[aindexforfind+1]), tempSpellList))
                {
                temp.Copy(tempSpellList[0]->Des());
                }
            }
        else if(astringInfoArr.Count()>aindex+1)//next segment should be english
            {
            temp.Copy(astringInfoArr[aindex+1]->segmentString);
            }
        }
    else
        {
        if(astringInfoArr.Count()>aindex+1)
            {
            pStringInfo= astringInfoArr[aindex+1]; //next segment should be chinese
            if (!DoTranslationL(TInt16((pStringInfo->segmentString)[0]), tempSpellList))
                {
                temp.Copy(pStringInfo->segmentString);
                }
            else
                {
                temp.Copy(tempSpellList[0]->Des());
                }
            }
        
        }
    tempSpellList.ResetAndDestroy();
    if(ReverseMatchString(aCurrentBuf,temp)>0)
        {
        if (pStringInfo->isChinese)
            {
            if((pStringInfo->segmentString).Length()>aindexforfind+2)//in same segment
                {
                if (!DoTranslationL(TInt16((pStringInfo->segmentString)[aindexforfind+2]), tempSpellList))
                    {
                    tempNext.Append((pStringInfo->segmentString)[aindexforfind+2]);
                    }
                else
                    {
                    tempNext.Copy(tempSpellList[0]->Des());
                    }
                }
            else if(astringInfoArr.Count()>aindex+2)//next segment should be english
                {
                pStringInfoNext = astringInfoArr[aindex+2];
                if(pStringInfoNext->isChinese)
                    {
                    if (!DoTranslationL(TInt16((pStringInfoNext->segmentString)[0]),
                                tempSpellList))
                            {
                            tempNext.Append((pStringInfoNext->segmentString)[0]);
                            }
                        else
                            {
                            tempNext.Copy(tempSpellList[0]->Des());
                            }
                    }
                else
                    {
                    tempNext.Copy(pStringInfoNext->segmentString);
                    }
                }
            }
        else
            {
            if(astringInfoArr.Count()>aindex+2)
                {
                pStringInfo= astringInfoArr[aindex+2]; //next segment should be chinese
                if (!DoTranslationL(TInt16((pStringInfo->segmentString)[0]), tempSpellList))
                    {
                    tempNext.Copy(pStringInfo->segmentString);
                    }
                else
                    {
                    tempNext.Copy(tempSpellList[0]->Des());
                    }
                }        
            }
        }

    if(tempNext.Length()>0)
        {
        UpdateNextCharsL(aNextChars,tempNext[0]);
        }  
    tempSpellList.ResetAndDestroy();
    tempSpellList.Close();
}
// ---------------------------------------------------------------------------
// AppendCharInNextSegmentL this segment is english
// ---------------------------------------------------------------------------
//
void CFindUtilChinese::AppendCharInNextSegmentL(const RPointerArray<STRINGINFO>& astringInfoArr ,
            const TInt aindex,HBufC*& aNextChars)
    {
    TBuf<KMaxWordLength> temp;

    RPointerArray<HBufC> tempSpellList;
    
    if ( !astringInfoArr[aindex]->isChinese)
        {
        UpdateNextCharsL(aNextChars,
                astringInfoArr[aindex]->segmentString[0]);
        }
    else
        {
        if (!DoTranslationL(
                TInt16(astringInfoArr[aindex]->segmentString[0]),
                tempSpellList))
            {
            UpdateNextCharsL(aNextChars,
                   astringInfoArr[aindex]->segmentString[0]);
            }
        else
            {
            //for multiphnetic spell
            TInt spellCount = tempSpellList.Count();
            // Search all spelling
            for (TInt j = 0; j < spellCount; j++)
                {
                temp = tempSpellList[j]->Des();
                UpdateNextCharsL(aNextChars, temp[0]);
                }//end for
            }

        }
    tempSpellList.ResetAndDestroy();
    tempSpellList.Close();
    }

// ---------------------------------------------------------------------------
// AppendNextSegmentFirstChar this segment is chinese
// ---------------------------------------------------------------------------
//
TBool CFindUtilChinese::AppendNextSegmentFirstCharL(const RPointerArray<STRINGINFO>& astringInfoArr ,
const TInt aindex ,const TInt aindexforfind,const TDes& aCurrentBuf ,const TDes& aTranSearchBuf,HBufC*& aNextChars)
    {
    STRINGINFO* pStringInfo= astringInfoArr[aindex];
    TBuf<KMaxWordLength> temp;
    TInt ret(0);
    if (pStringInfo->isChinese)
        {
        if (aCurrentBuf.Length() > aindexforfind + 1)
            {
            RPointerArray<HBufC> tempSpellList;
            if (!DoTranslationL(
                    TInt16(aCurrentBuf[aindexforfind + 1]),
                    tempSpellList))
                {
                UpdateNextCharsL(aNextChars,
                        aCurrentBuf[aindexforfind + 1 ]);
                }
            else
                {
                //for multiphnetic spell
                TInt spellCount = tempSpellList.Count();
                // Search all spelling
                for (TInt j = 0; j < spellCount; j++)
                    {
                    temp = tempSpellList[j]->Des();
                    UpdateNextCharsL(aNextChars, temp[0]);
                    if (temp.Length()>1)
                        {
                        TBuf<KMaxWordLength>
                                useforminan(aTranSearchBuf);
                        useforminan.Append(temp[1]);
                        if (MatchRefineL(aCurrentBuf, useforminan))
                            {
                            UpdateNextCharsL(aNextChars,temp[1]);
                            }
                        }
                    }//end for                               
                }
            tempSpellList.ResetAndDestroy();
            tempSpellList.Close();
            }
        else
            {
            //if space exist in chinese words, it will split them into differenct segments.
            if (aindex < astringInfoArr.Count() - 1)
                {
                STRINGINFO* pStringInfo1 =
                        astringInfoArr[aindex + 1];
                if (pStringInfo1->isChinese)
                    {
                    RPointerArray<HBufC> tempSpellList;
                    if (!DoTranslationL(TInt16((pStringInfo1->segmentString)[0]),
                            tempSpellList))
                        {
                        UpdateNextCharsL(aNextChars,(pStringInfo1->segmentString)[0]);
                        }
                    else
                        {
                        //for multiphnetic spell
                        TInt spellCount = tempSpellList.Count();
                        // Search all spelling
                        for (TInt j = 0; j < spellCount; j++)
                            {
                            temp = tempSpellList[j]->Des();
                            UpdateNextCharsL(aNextChars,temp[0]);
                            }//end for
                        }
                    tempSpellList.ResetAndDestroy();
                    tempSpellList.Close();
                    }
                else
                    {
                    UpdateNextCharsL(aNextChars,
                            pStringInfo1->segmentString[0]);
                    }
                }
            }

        }
    else
        {
        //have no next element in array
        if (astringInfoArr.Count() <= aindex+1)
            {
            ret = ETrue;
            return ret;
            }
        
        AppendCharInNextSegmentL(astringInfoArr,aindex+1,aNextChars);
        
        }
    return ret;
    }

// ---------------------------------------------------------------------------
// IsAdaptiveFindMatchL
// ---------------------------------------------------------------------------
//
TBool CFindUtilChinese::IsAdaptiveFindMatchL( const TDesC& aItemString, const TDesC& aSearchText,
 HBufC*& aNextChars )
{
    
    TBuf<KMaxWordLength> tempBuf;    
    TBuf<KMaxWordLength> itemString;
    
    TBool ret = EFalse;
    
    tempBuf.Zero();
    if ( KMaxWordLength > aSearchText.Length() )
        {
        tempBuf.Copy( aSearchText );
        }
    else
        {
        tempBuf.Copy( aSearchText.Left( KMaxWordLength ) );
        }
    
    itemString.Zero();
     
    if ( KMaxWordLength > aItemString.Length() )
        {
        itemString.Copy( aItemString );
        }
    else
        {
        itemString.Copy( aItemString.Left( KMaxWordLength ) );
        }
    
    RemoveSeparator(tempBuf);
    
    RPointerArray<HBufC> spellList;
    
    //trim the sepcial char
    if(itemString.Length()>0)
        {
        if(itemString[0]== KLeftToRightFlag || itemString[0]== KRightToLeftFlag)
            {
            itemString.Delete(0,1);
            itemString.Delete((itemString.Length()-1),1);     
            } 
        }                
    
    //Find if search string has chinese word. 
    //Compare with item string if find chinese word in item string then delete it from search and item string.
    
    if(IsChineseWord(tempBuf))
        {
        if(TrimChineseCharacterL(itemString,tempBuf,aNextChars))
            {
            spellList.ResetAndDestroy();//destroy spellList
            spellList.Close();
            return ETrue;
            }
        }
       
    // Array for item string
    RPointerArray<STRINGINFO> stringInfoArr;
    // Split item string
    SplitItemStringL(stringInfoArr, itemString);
    
    // For store temp data 
    TBuf<KMaxWordInterpretationLen> temp;
        
    //First only check English
    
    if(CheckEnglishFirstL(stringInfoArr,tempBuf,aNextChars))
        {
        spellList.ResetAndDestroy();//destroy spellList
        spellList.Close();
        stringInfoArr.ResetAndDestroy();
        stringInfoArr.Close();
        return ETrue;
        }
    
    const TInt arrayLength = stringInfoArr.Count();
    const TInt searchStrLength = tempBuf.Length();
    TInt searchStrIndex = 0;
    STRINGINFO* pStringInfo= NULL;
    TBuf<KMaxWordLength> transSearchBuf;
    TInt index = 0; 
    TInt indexforfind =0;
    TInt indexlast=0;
    
    TBuf<KMaxWordLength> bufcurrent;
    TBuf<KMaxWordLength> tempbufcurrent;
    
    // Find Chinese and English
    for (; index < arrayLength; index ++)
        {
        TInt matchLength = 0;
        transSearchBuf.Zero();
        pStringInfo = stringInfoArr[index];

        transSearchBuf = tempBuf.Mid(searchStrIndex, searchStrLength
                - searchStrIndex);
        if (transSearchBuf.Length()==0)
            {
            break;
            }

        bufcurrent = pStringInfo->segmentString;

        for (TInt j =0; j < pStringInfo->segmentString.Length(); j++)
            {
            TInt indexforfindtemp = 0;
            TInt searchStrIndextemp = 0;
            if (pStringInfo->isChinese)
                {
                tempbufcurrent = bufcurrent.Mid(j);
                matchLength = MatchChineseStringL(tempbufcurrent,
                        transSearchBuf, indexforfindtemp);
                searchStrIndextemp +=matchLength;
                if (indexforfindtemp>=indexforfind)
                    {
                    if (indexlast == index && searchStrIndextemp
                            >= searchStrIndex)
                        {
                        searchStrIndex = searchStrIndextemp;
                        }
                    else
                        if (indexlast != index)
                            {
                            searchStrIndex += searchStrIndextemp;
                            }
                    indexforfind = indexforfindtemp;
                    indexlast = index;
                    }
                }
            else
                {//english words and chinese words don't coexist in same segment
                matchLength = MatchString(bufcurrent, transSearchBuf);
                searchStrIndex +=matchLength;
                if (searchStrIndex >= searchStrLength)
                    {
                    //append next char in the same segment
                    ret = ETrue;

                    if (bufcurrent.Length() > matchLength)
                        {
                        UpdateNextCharsL(aNextChars, bufcurrent[matchLength]);
                        }
                    if (arrayLength <= index+1)
                        {
                        spellList.ResetAndDestroy();//destroy spellList
                        spellList.Close();
                        stringInfoArr.ResetAndDestroy();
                        stringInfoArr.Close();
                        return ret;
                        }
                    
                    AppendCharInNextSegmentL(stringInfoArr,index+1,aNextChars);
                    
                    }
                break;
                }
            // Append next character in same segment this segment is chinese
            if (searchStrIndex >= searchStrLength)
                {
                ret = ETrue;
                RPointerArray<HBufC> tempSpellList;
                if (tempbufcurrent.Length()>indexforfind)
                    {
                    if (!DoTranslationL(TInt16(tempbufcurrent[indexforfind]),
                            tempSpellList))
                        {
                        UpdateNextCharsL(aNextChars,
                                tempbufcurrent[indexforfind]);
                        }
                    else
                        {
                        //for multiphnetic spell
                        TInt spellCount = tempSpellList.Count();
                        TInt matchMaxIndex = 0;
                        TInt matchMax = 0;
                        TInt matchMaxPre = 0;
                        // Search all spelling
                        for (TInt j = 0; j < spellCount; j++)
                            {
                            //for multiphnetic spell
                            TInt spellCount = tempSpellList.Count();
                            TInt matchMaxIndex = 0;
                            TInt matchMax = 0;
                            TInt matchMaxPre = 0;
                            TBool fullmatch = EFalse;
                            TBool offset = KErrNotFound;
                            // Search all spelling
                            for (TInt j = 0; j < spellCount; j++)
                                {
                                temp = tempSpellList[j]->Des();
                                for (TInt k = 1; k <= searchStrLength; k++)
                                    {
                                    TBuf<KMaxWordLength> tmpBuf = tempBuf.Mid(
                                            searchStrLength - k, k);
                                    offset = temp.Find(tmpBuf);
                                    if (offset != KErrNotFound)
                                        {
                                        TBuf<KMaxWordLength> buf = temp.Mid(0,k);
                                        if (buf == tmpBuf)
                                            {
                                            fullmatch = ETrue;
                                            }
                                        }
                                    if (offset != KErrNotFound && fullmatch)
                                        {
                                        matchMax = k;
                                        }
                                    fullmatch = EFalse;
                                    }
                                if (matchMax > matchMaxPre)
                                    {
                                    matchMaxPre = matchMax;
                                    matchMaxIndex = j;
                                    }
                                if (matchMax == searchStrLength && fullmatch)
                                    {
                                    if (matchMaxPre <temp.Length())
                                        {
                                        UpdateNextCharsL(aNextChars, temp[matchMax]);
                                        }
                                    }
                                fullmatch = EFalse;
                                offset = KErrNotFound;
                                }
                            temp = tempSpellList[matchMaxIndex]->Des();
                            if (matchMaxPre <temp.Length())
                                {
                                UpdateNextCharsL(aNextChars,temp[matchMaxPre]);
                                }
                            }
                        tempSpellList.ResetAndDestroy();
                        tempSpellList.Close();
                        }
                    }
                //Append first translated character or english letter in next segment.
                if (ret)
                    { 
                    AppendNextSegmentFirstCharL(stringInfoArr,index,
                            indexforfind,tempbufcurrent,transSearchBuf,aNextChars);
                    
                    AddNextIfOverlapL(stringInfoArr,index,indexforfind+j,transSearchBuf,aNextChars);
                    }
                searchStrIndex = 0;
                }
            indexforfind = 0;
            }
        }

    spellList.ResetAndDestroy();//destroy spellList
	spellList.Close(); 		
    stringInfoArr.ResetAndDestroy();
    stringInfoArr.Close();

    return ret;
}
    
// -----------------------------------------------------------------------------
// CFindUtilChinese::MatchAdaptiveRefineL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//  
TBool CFindUtilChinese::MatchAdaptiveRefineL( const TDesC& aItemString, 
	const TDesC &aSearchText, HBufC*& aNextChars )
	{
	//Get default adaptive search method.
	if ( aItemString.Length() == 0 )
        {
        return EFalse;
        }
    if ( aSearchText.Length() == 0 )
        {
        UpdateNextCharsFromStringL( aNextChars, aItemString );
        return ETrue;
        } 
               
    return IsAdaptiveFindMatchL( aItemString, aSearchText, aNextChars);		    
    	
	}

// ---------------------------------------------------------
// Match arithmetic for accurate search, special translation 
// for aItemString is implemented with MFindTargetStrTranslation
// before the final match
// ---------------------------------------------------------
//
TBool CFindUtilChinese::MatchRefineL( const TDesC& aItemString, const TDesC& aSearchText, 
                                      TMatchPolicy aPolicy, MFindStringConverter* aConverter)
    {
    TBool ret = EFalse;
    
    if (aPolicy == ECustomConverter)
        {
        iConverter = aConverter;
        }

    ret = MatchRefineL(aItemString, aSearchText);
    iConverter = NULL;
    
    return ret;
    }    

// end of file
