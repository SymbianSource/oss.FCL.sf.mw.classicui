/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies). 
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









#ifndef __FINDUTILWESTERN__
#define __FINDUTILWESTERN__

#include <e32std.h>
#include <centralrepository.h>
#include <AknFepInternalCRKeys.h>
#include <cenrepnotifyhandler.h>
#include "FindUtilBase.h"

class CFindUtilKorean;
// Factory function at first ordinal
IMPORT_C MFindUtil* FindUtilFactoryFunctionL();

NONSHARABLE_CLASS(CFindUtilWestern) : public CFindUtilBase, public MCenRepNotifyHandlerCallback
    {
    public:  // Constructors and destructor
        /**
         * C++ default constructor.
         */
        CFindUtilWestern();

        /**
         * Destructor.
         */
        virtual ~CFindUtilWestern();

    private:  // From MFindUtil
        /**
         * From MFindUtil It tests a matching.
         * @since 2.6
         * @param aContactsField is a contact field string.
         * @param aWord is a search string.
         * @return If aWord has been matched with aContactsField, 
         *         ETrue is returned.
         */
        TBool Match(const TDesC& aContactsField, const TDesC& aWord);

        /**
         * From MFindUtil It tests a partial matching.
         * @since 2.6
         * @param aItemString is a Contact field string
         * @param aSearchText is a search string
         * @return If aSearchText has been found in aItemString, 
         *         ETrue is returned.
         */
        TBool MatchRefineL( const TDesC& aItemString, const TDesC &aSearchText);      
        

        /**
         * From MFindUtil It checks whether aWord is valid.
         * @since 2.6
         * @param aWord 
         * @return ETrue is returned always.
         */
        TBool IsWordValidForMatching(const TDesC& aWord);
        
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
        
         /**
         * From CFindUtilBase. Overrides the base function to find the input language
         * @since 3.1
         */
        void CFindUtilWestern::OpenL();
	private:
        /**
        * Derived from MCenRepNotifyHandlerCallback
        * Receive a notification from central repository server
        */
        void HandleNotifyInt(TUint32 aId, TInt aNewValue);
	private:
		CRepository* iRepository;        
		TInt iInputLanguage;
		CCenRepNotifyHandler* iNotifyHandler;
        CFindUtilKorean *iFindUtilKorean;
        HBufC* iDigraphChars;
    };


#endif // __FINDUTILWESTERN__

// End of File
