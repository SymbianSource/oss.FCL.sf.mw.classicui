/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declares main application class.
*
*/


#ifndef C_CBCTESTDOMPTICORE_H
#define C_CBCTESTDOMPTICORE_H

#include <pticore.h>

class CBCTestDomPtiCore : public CPtiCore
    {
public:
    static CBCTestDomPtiCore* NewL(); 
    
    ~CBCTestDomPtiCore(); 

    void InitializeL(CPtiEngine* aOwner, TDes* aTextBuffer,
                            CArrayPtrFlat<CPtiCoreLanguage>* aLanguageList,
                            TBool aUseDefautUserDictionary);

    void DropLanguages(CArrayPtrFlat<CPtiCoreLanguage>* /*aLanguageList*/)
    {
    }
    
    TInt OpenLanguageL(CPtiCoreLanguage* /*aLanguage*/)
    {
    return 0;
    }
    
    TInt CloseLanguageL()
    {
    return 0;
    }
    
    TPtrC GetCurrentWord() const
    {
    return CPtiCore::GetCurrentWord();
    }
    
    TInt CommitCurrentWord()		
    {
    return CPtiCore::CommitCurrentWord();
    }
    
    MPtiCoreInfo* GetCoreInfo()
    {
    return NULL;
    }
    
    TInt SetReordering(TBool /*aStatus*/)
    {
    return 0;
    }
    
    void AppendKeyPress(TPtiKey /*aKey*/)
    {
    }
    
    void DeleteKeyPress()
    {
    }
    
    void ClearBuffer()
    {
    }
    
    TInt SetCurrentInputSequence(TPtrC8 aInput)
    {
    return CPtiCore::SetCurrentInputSequence( aInput );
    }
    
    TInt Convert(TPtiCharConversion aType,
                 TAny* aInput,
                 TInt aInputLength,
                 TAny* aOutput)
    {
    return CPtiCore::Convert( aType, aInput, aInputLength, aOutput);
    }
    
    TInt SetExternalKeyMapL(TPtiEngineInputMode aMode,
			                TPtiKey aKey,
			                TDesC& aKeyMap,
			                TPtiTextCase aCase)
    {
    return CPtiCore::SetExternalKeyMapL( aMode,aKey,aKeyMap,aCase);
    }
    
    TInt GetSpelling(TUint16 aInput, TDes& aOutput, TPtiSpelling aType)
    {
    return CPtiCore::GetSpelling( aInput,  aOutput, aType);
    }
    
    TInt CancelTimerActivity()
    {
    return 0;
    }
    
    TInt HandleCommandL(TPtiEngineCommand /*aCommand*/, TAny* /*aParams*/)
    {
    return 0;
    }
    
    TInt NumberOfCandidates()
    {
    return CPtiCore::NumberOfCandidates();
    }
    
    TInt GetCandidateListL(CDesCArray& aList)
    {
    return CPtiCore::GetCandidateListL( aList );
    }
    
    TInt GetNextWordCandidateListL(CDesCArray& aList)
    {
    return CPtiCore::GetNextWordCandidateListL( aList );
    }
    
    TInt GetFirstCandidate(TDes& aResult)
    {
    return CPtiCore::GetFirstCandidate( aResult );
    }

    TInt GetNextCandidate(TDes& aResult)
    {
    return CPtiCore::GetNextCandidate( aResult );
    }
    
    TInt GetPreviousCandidate(TDes& aResult)
    {
    return CPtiCore::GetPreviousCandidate( aResult );
    }
    
    TInt AddUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict)
    {
    return CPtiCore::AddUserDictionaryEntry( aEntry,  aDict);
    }
    
    TInt RemoveUserDictionaryEntry(MPtiUserDictionaryEntry& aEntry, CPtiUserDictionary* aDict)
    {
    return CPtiCore::RemoveUserDictionaryEntry( aEntry,  aDict);
    }
    
    TInt NumberOfEntriesInUserDictionary(CPtiUserDictionary* aDict)
    {
    return CPtiCore::NumberOfEntriesInUserDictionary( aDict );
    }
    
    TInt GetUserDictionaryEntry(TInt aIndex, MPtiUserDictionaryEntry& aResult, CPtiUserDictionary* aDict)
    {
    return CPtiCore::GetUserDictionaryEntry( aIndex,  aResult, aDict);    
    }
    
    CPtiUserDictionary* CreateEmptyUserDictionaryL(TInt aMaxSize)
    {
    return CPtiCore::CreateEmptyUserDictionaryL( aMaxSize );
    }
    
    TInt AttachUserDictionary(CPtiUserDictionary* aDict)
    {
    return CPtiCore::AttachUserDictionary( aDict );
    }
    
    TBool DetachUserDictionary(CPtiUserDictionary* aDict)		
    {
    return CPtiCore::DetachUserDictionary( aDict );
    }
    
    TPtrC GetCandidatePage()
    {
    return CPtiCore::GetCandidatePage();
    }
    
    TBool NextCandidatePage()
    {
    return CPtiCore::NextCandidatePage();
    }
    
    TBool PreviousCandidatePage()
    {
    return CPtiCore::PreviousCandidatePage();
    }
    
    TBool MoreCandidatePages()
    {
    return CPtiCore::MoreCandidatePages();
    }
    
    void SetCandidatePageLength(TInt aLength)
    {
    return CPtiCore::SetCandidatePageLength( aLength );
    }
    
    TPtrC GetPhoneticSpelling(TInt aIndex) const 
    {
    return CPtiCore::GetPhoneticSpelling( aIndex );
    }
    
    TInt PhoneticSpellingCount() const	
    {
    return CPtiCore::PhoneticSpellingCount();
    }
    
    TBool SelectPhoneticSpelling(TInt aIndex)
    {
    return CPtiCore::SelectPhoneticSpelling( aIndex );
    }
    
    TInt SelectedPhoneticSpelling() const 
    {
    return CPtiCore::SelectedPhoneticSpelling();
    }
    
    TBool ToneMark(TText& aToneMark) const
    {
    return CPtiCore::ToneMark( aToneMark );
    }
    
    TBool IsToneMarkValidForSpelling()
    {
    return CPtiCore::IsToneMarkValidForSpelling();
    }
    
    TBool SetPredictiveChineseChar(const TDesC& aChar)
    {
    return CPtiCore::SetPredictiveChineseChar( aChar );
    }
    
    TBool SetToneMark(TInt aToneMark)
    {
    return CPtiCore::SetToneMark( aToneMark );
    }
    
    TPtrC ReadingTextL()
    {
    return CPtiCore::ReadingTextL();
    }
    
    MPtiEngineCompositionDataInterface* CompositionData()
    {
    return CPtiCore::CompositionData();
    }
    
    HBufC* GetCandidatesByInputString(const TDesC& aInputString, 
                                      RPointerArray<HBufC>& aList, 
                                      const TBool aIsPredictive)    
    {
    return CPtiCore::GetCandidatesByInputString( aInputString, aList, aIsPredictive );
    }
    
private:

    /**
     * C++ default constructor
     */
    CBCTestDomPtiCore();

    /**
    * Second phase constructor
    *
    * @return None
    */
    void ConstructL();
    };

#endif
