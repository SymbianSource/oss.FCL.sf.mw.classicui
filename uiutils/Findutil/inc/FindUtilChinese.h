/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:         findutilchinese header file.
*
*/









#ifndef __FINDUTILCHINESE__
#define __FINDUTILCHINESE__

// INCLUDES
#include <e32base.h>

#include "FindUtilBase.h"

// FORWARD DECLARATION
class CPtiEngine;
class CFindRepositoryWatcher;
class CRepository;

// CONSTANTS
const TInt KMaxWordLength = 128;
/**

Defines flags that can be used to indicate what is the default search method for each language.
*/
enum TDefaultAdaptiveSearchMethod
    {
    EAdptSearchPinyin =0,
    EAdptSearchStroke,
    EAdptSearchZhuyin,
    EAdptSearchNormalCangjie,
    EAdptSearchEasyCangjie,
    EAdptSearchAdvCangjie
    };
/**
 *  STRINGINFO struct
 *
 *  This data struct is for splited taxt in find pane. 
 *  It includes two type word, which is Chinese or no-Chinese 
 *
 *  @lib FindUtil.dll
 *  @since S60 v3.2
 */
struct STRINGINFO
    {
    TBuf<KMaxWordLength> segmentString; 
    TBool isChinese;
    };

/**
 * Factory function at first ordinal to create concrete object of MFindUtil
 *
 * @since S60 v3.2
 * @return Pointer to created MFindUtil object
 */  
IMPORT_C MFindUtil* FindUtilFactoryFunctionL();

/**
 *  CFindUtilChinese utils class
 *
 *  This class is Chinese find utils class. It handle Chinese variant find
 *  in PhoneBook, LandMark, Clock and so on.
 *
 *  @lib FindUtil.dll
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS(CFindUtilChinese) : public CFindUtilBase
    {
public:

// From MFindUtil

    /**
     * From MFindUtil
     * Match arithmetic for general search
     *
     * @since S60 v3.2
     * @param aContactsField Reference to the searching target
     * @param aWord Reference to text in find pane
     * @return ETrue for the text are matched; otherwise EFalse
     */
    virtual TBool Match(const TDesC& aContactsField, const TDesC& aWord);	

    /**
     * From MFindUtil
     * Match arithmetic for accurate search 
     *
     * @since S60 v3.2
     * @param aItemString Reference to the searching target
     * @param aWord Reference to text in find pane
     * @return ETrue for the text are matched; otherwise EFalse
     */
    virtual TBool MatchRefineL( const TDesC& aItemString, const TDesC &aSearchText);
    
    /**
     * From MFindUtil
     * Current input text is handled by this model 
     *
     * @since S60 v3.2
     * @param aWord Reference to text in find pane
     * @return ETrue for handling by this model; otherwise EFalse
     */
    virtual TBool IsWordValidForMatching(const TDesC& aWord);

        /**
         * From MFindUtil It tests a partial matching.
         * @since 5.0
         * @param aItemString is a field string
         * @param aSearchText is a search string
         * @param aNextChars is a reference to buffer where next possible characters are saved. 
         *        The HBufC buffer may be re-allocated by this method. 
         *        In that case the pointer reference is modified to point to the re-allocated object.                              
         * @return If aSearchText has been found in aItemString, 
         *         ETrue is returned.
         */
        TBool MatchAdaptiveRefineL( const TDesC& aItemString, 
        							const TDesC& aSearchText, 
        							HBufC*& aNextChars);
									
    /**
     * From MFindUtil
     * Current input text is handled by this model 
     *
     * @since S60 v3.2.3
     * @param aItemString Reference to the searching target
     * @param aSearchText Reference to text in find pane
     * @param aPolicy Reference to identify the different match policy
     * @param aConverter Reference to the converter interface, with which the aSearchText
     *  will be converted into other kind of str, such numeric string according to
     *  the ITUT keyboard key map
     * @return ETrue for handling by this model; otherwise EFalse
     */
    virtual TBool MatchRefineL( const TDesC& aItemString, const TDesC& aSearchText, 
                                TMatchPolicy aPolicy, MFindStringConverter* aConverter);									

// From CFindUtilBase

    /**
     * From CFindUtilBase
     * Create ptiengine and initialize member data 
     *
     * @since S60 v3.2
     * @return none
     */
    virtual void OpenL();
    
    /**
     * From CFindUtilBase
     * Close ptiEngine 
     *
     * @since S60 v3.2
     * @return none
     */
    virtual void Close();
    
    /**
     * Symbian constructor
     *
     * @since S60 v3.2
     * @return Pointer to created CFindUtilChinese object
     */    
    static CFindUtilChinese* NewL();
    
public:

    /**
     * C++ default constructor
     *
     * @since S60 v3.2
     * @return None
     */  
    CFindUtilChinese();

    /**
     * Destructor
     *
     * @since S60 v3.2
     * @return None
     */
    ~CFindUtilChinese();

private:

    /**
     * Symbian second-phase constructor
     *
     * @since S60 v3.2
     * @return None
     */ 
    void ConstructL();
    
    /**
     * Open ptiengine and active it by input language
     *
     * @since S60 v3.2
     * @param aLanguage Actived language
     * @return ETrue for opening ptiengine successfully; otherwise EFalse
     */ 
    TBool OpenT9InterfaceL(TLanguage aLanguage);

    /**
     * Close ptiengine
     *
     * @since S60 v3.2
     * @return none
     */ 
    void CloseT9InterfaceL();

    /**
     * Translate Chinese word to its spelling
     *
     * @since S60 v3.2
     * @param aHZUnicode For translate word
     * @param aSpellList Reference to spelling list for polyphonic word
     * @return ETrue for this word can be translated; otherwise EFalse
     */ 
    TBool DoTranslationL(TInt16 aHZUnicode, RPointerArray<HBufC>& aSpellList);

    /**
     * This letter is stroke symbol
     *
     * @since S60 v3.2
     * @param aFindWord For analyse
     * @return ETrue for it is stroke symbol; otherwise EFalse
     */ 
    TInt IsStrokeSymbol(const TInt aFindWord);

    /**
     * Do translate for Chinese word
     *
     * @since S60 v3.2
     * @param aHZUnicode For translate word
     * @param aSpellList Reference to spelling list for polyphonic word
     * @return ETrue for it can be translated; otherwise EFalse
     */
    TBool T9ChineseTranslationL(TInt16 aHZUnicode, RPointerArray<HBufC>& aSpellList);
    
    /**
     * Do translate for Chinese word
     *
     * @since S60 v5.0.1
     * @param aHZUnicode For translate word
     * @param aSpellList Reference to spelling list for polyphonic word
     * @return ETrue for it can be translated; otherwise EFalse
     */
    TBool T9ChineseTranslationAdaptiveL(TInt16 aHZUnicode, RPointerArray<HBufC>& aSpellList);

    /**
     * Find pane text is including separator
     *
     * @since S60 v3.2
     * @param aCh Analyze word
     * @return ETrue it is separator; otherwise EFalse
     */
    TBool IsFindWordSeparator(TChar aCh);

    /**
     * Find pane text is including Chinese word
     *
     * @since S60 v3.2
     * @param aWord Reference to text for analyse
     * @return ETrue it includes Chinese; otherwise EFalse
     */
    TBool IsChineseWord(const TDesC& aWord);
    
    /**
     * Find pane text is just Chinese word
     * 
     * @param aWord Reference to text for analyse
     * @return ETrue it is a Chinese word; otherwise EFalse
     */
    TBool ChineseWord(const TDesC& aWord);

    /**
     * Find pane text is including stroke symbol
     *
     * @since S60 v3.2
     * @param aWord Reference to text for analyse
     * @return ETrue it is stroke symbol; otherwise EFalse
     */
    TBool IsStrokeSymbolInString(const TDesC& aWord);

    /**
     * Find pane text is including zhuyin symbol
     *
     * @since S60 v3.2
     * @param aWord Reference to text for analyse
     * @return ETrue it includes zhuyin symbol; otherwise EFalse
     */
    TBool IsZhuyinSymbolInString(const TDesC& aWord);

    /**
     * This language is support by this model
     *
     * @since S60 v3.2
     * @param aLang Language for support
     * @return ETrue it supports; otherwise EFalse
     */
    TBool IsSupportLanguage(TLanguage aLang);
    
    /**
     * Callback method to notify client about language change.
     *
     * @since S60 v3.2
     * @param aPtr Pointer to the callback data
     * @return Error code
     */
    static TInt HandleFindRepositoryCallBack(TAny* aPtr);
    
    /**
     * Splite the input text to sgement by language
     *
     * @since S60 v3.2
     * @param aStringInfoArr Reference to segment list
     * @param aItemString Reference to input text
     * @return none
     */
    void SplitItemStringL(RPointerArray<STRINGINFO>& aStringInfoArr, const TDesC &aItemString);


    /**
     * Insert segment to list
     *
     * @since S60 v3.2
     * @param aStringInfoArr Reference to segment list
     * @param aSegmentStr Reference to segment text
     * @param aChinese The segment is Chinese
     * @return none
     */
    void InsertStrInforArrayL(RPointerArray<STRINGINFO>& aStringInfoArr, TDes &aSegmentStr,
                              const TBool aChinese);
                              
    /**
     * This segment is matched by search text
     *
     * @since S60 v3.2
     * @param aStringInfoArr Reference to segment list
     * @param aSearchText Reference to searching text
     * @return ETrue it is matched; otherwise EFalse
     */
    TBool MatchSegmentL(RPointerArray<STRINGINFO>& aStringInfoArr, const TDesC &aSearchText);

    /**
     * Search text by reverse
     *
     * @since S60 v3.2
     * @param aFirst Reference to matched text
     * @param aSecond Reference to matched text
     * @return Matched count
     */
    TInt ReverseMatchString(const TDesC& aFirst, const TDesC& aSecond);

    /**
     * Search text in other text 
     *
     * @since S60 v3.2
     * @param aFirst Reference to matched text
     * @param aSecond Reference to matched text
     * @return Matched count
     */
    TInt MatchString(const TDesC& aFirst, const TDesC& aSecond);

    /**
     * Search Chinese word in input text 
     *
     * @since S60 v3.2
     * @param aFirst Reference to matched text
     * @param aSecond Reference to matched text
     * @return Matched count
     */
    TInt MatchChineseStringL(const TDesC& aFirst, const TDesC& aSecond, TInt& aIndex);

    /**
     * Initial character search 
     *
     * @since S60 v3.2
     * @param aStringInfoArr Reference to spelling list
     * @param aSearchStr Reference to search text
     * @return ETrue it is matched; otherwise EFalse
     */
    TBool MatchChineseInitialStringL(RPointerArray<STRINGINFO>& aStringInfoArr, 
                                     const TDesC& aSearchStr);

    /**
     * Maximal matched count in spelling list  
     *
     * @since S60 v3.2
     * @param spellList Reference to spelling list
     * @param aSearchStr Reference to search text
     * @param aPreviouStr Reference to previous matched word
     * @param aMatchIndex Reference to match index in Search text
     * @param aFullMatched Previous word is fully matched
     * @param aMatchedCount Previous word matched count
     * @param aAgain Search again
     * @return Matched count
     */
    TInt MaxMatchInList(RPointerArray<HBufC> &spellList, TDesC& aSearchStr, TDesC& aPreviouStr, 
                        TInt& aMatchIndex, const TBool aFullMatched, const TInt aMatchedCount, TBool& aAgain);

    /**
     * Search the taxt is include the input text 
     *
     * @since S60 v3.2
     * @param aFirst Reference to matched text
     * @param aSecond Reference to matched text
     * @return Matched count
     */
    TBool IncludeString(const TDesC& aFirst,  const TDesC& aSecond);    

    /**
     * Update input method in ptiengine from find pane
     *
     * @since S60 v3.2
     * @return none
     */
    void  UpdateCurrentInputMode();

    /**
     * Remove separator from search text
     *
     * @since S60 v3.2
     * @param aSearchText Reference to search text
     * @return none
     */
    void RemoveSeparator(TDes& aSearchText);    
    
     /**
     * From MFindUtil It return next char.
     * @since 5.0
     * @param aNextChars is a buffer where next possible characters are saved
     * @param aCh is a char need to be input to aNextChars
     * 
     */
    void UpdateNextCharsL(HBufC*& aNextChars, TChar aCh);
     /**
     * From MFindUtil It return next chars.
     * @since 5.0
     * @param aNextChars is a buffer where next possible characters are saved
     * @param aItemString is a Contact field string
     */
    void UpdateNextCharsFromStringL(HBufC*& aNextChars, const TDesC& aItemString);   
    
     /**
     * From MFindUtil It return next chars.
     * @since 5.0
     * @param aNextChars is a buffer where next possible characters are saved
     * @param aItemString is a Contact field string
     * @param aSearchText Reference to search text
     * @param aInputLang for the input language 
     */
    TBool IsAdaptiveFindMatchL( const TDesC& aItemString, const TDesC& aSearchText,
                               HBufC*& aNextChars);
                               
    
    /**
    * Trim chinese charater if it is exist in search text
    * @since 5.0
    * @Param aItemString is a contact field string
    * @param aSearchText is a search  text   
    * @param aNextChars is a buffer to store the charcaters needed to display.    
    */ 
    TBool TrimChineseCharacterL(TDes& aItemString, TDes& aSearchText,HBufC*& aNextChars);

    /**
       * Trim chinese charater if it is exist in search text
       * @since 5.0
       * @Param aarray is a contact field string which had to segments
       * @param aSearchText is a search  text
       * @param aNextChars is a buffer to store the charcaters needed to display.    
       */ 
    TBool CheckEnglishFirstL( RPointerArray<STRINGINFO>& aarray, TDes& aSearchText,HBufC*& aNextChars);
    
    /**
     * Trim chinese charater if it is exist in search text
     * @since 5.0
     * @Param AstringInfoArr is a contact field string which had to segments
     * @param aindex is the current find cursor
     * @param aNextChars is a buffer to store the charcaters needed to display.    
     */ 
    void AppendCharInNextSegmentL(const RPointerArray<STRINGINFO>& astringInfoArr ,
            const TInt aindex,HBufC*& aNextChars);
    
    /**
     * Trim chinese charater if it is exist in search text
     * @since 5.0
     * @Param AstringInfoArr is a contact field string which had to segments
     * @param aindex is the current find cursor
     * @paran aindexforfind is the temp cursor for find
     * @param aCurrentBuf the data in this segment
     * @param aTranSearchBuf is the left search data
     * @param aNextChars is a buffer to store the charcaters needed to display.    
     */ 
    
    TBool AppendNextSegmentFirstCharL(const RPointerArray<STRINGINFO>& astringInfoArr ,
            const TInt aindex ,const TInt aindexforfind ,
            const TDes& aCurrentBuf ,const TDes& aTranSearchBuf ,
            HBufC*& aNextChars);
    
    /**
         * Check and add next char if existed overlap problem (tang ang)
         * @since 5.0
         * @Param AstringInfoArr is a contact field string which had to segments
         * @param aindex is the current find cursor
         * @paran aindexforfind is the temp cursor for find
         * @param aCurrentBuf is the search string
         * @param aNextChars is a buffer to store the charcaters needed to display.    
         */ 
    void AddNextIfOverlapL(const RPointerArray<STRINGINFO>& astringInfoArr ,
                const TInt aindex,const TInt aindexforfind ,
                const TDes& aCurrentBuf,HBufC*& aNextChars );
private:

    /**
     * Ptiengine for Chinese translation (Own)
     */
    CPtiEngine* iPtiEngine;
    
    /**
     * Ptiengine for Chinese translation in English language (Own)
     */    
    CPtiEngine* iPtiEnginePrc;
    
    /**
     * Current text input language 
     */    
    TLanguage iLanguage;
    
    /**
     * It is support Chinese Language
     */      
    TBool iSupportPRCChinese;

    /**
     * Current input mode
     */     
    TInt iCurInputMode;	

    /**
     * Repository for input mode (Own)
     */     
    CRepository* iRepositoryFind;	 

    /**
     * The repository watcher(Own);
     */
    CFindRepositoryWatcher* iWatcher;
    
   
        /**
     * Repository for input mode (Own)
     */     
    CRepository* iRepositoryFindAdaptive;	 

    /**
     * The repository watcher(Own);
     */
    CFindRepositoryWatcher* iWatcherAdaptive;
    
   
    /**
     * The default adaptive search method;
     */
    TDefaultAdaptiveSearchMethod iSearchMethodPRC;
    
    /**
     * The default adaptive search method;
     */
    TDefaultAdaptiveSearchMethod iSearchMethodTaiWan;
    
    /**
     * The default adaptive search method;
     */
    TDefaultAdaptiveSearchMethod iSearchMethodHongKong;
    
    
    /**
     * The search method;
     */
    TBool iSearchMethodAdaptive;
    
	
	/**
     * Numeric Converter interface (Not Own);
     */
    MFindStringConverter* iConverter;
    
    
    };

#endif // __FINDUTILCHINESE__

// End of File
