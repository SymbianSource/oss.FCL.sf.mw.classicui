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

#ifndef __COEFONTPROVIDER_H__
#define __COEFONTPROVIDER_H__

#include <e32base.h>
#include <e32def.h>
#include <coefont.h>
#include <coemain.h>
#include <coeaui.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <coecntss.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

/** A helper object designed to make obtaining a font easier, taking into account
zoom factors.

@publishedAll
@released
*/
class CCoeFontProvider : public CBase 
        { 
public:        // life 
        IMPORT_C static CCoeFontProvider* NewL(); 
        IMPORT_C static CCoeFontProvider* NewL(const TDesC& aTypefaceName); 
        ~CCoeFontProvider(); 
public:        // methods 
        IMPORT_C const CFont& Font(const TCoeFont& aFont, const TZoomFactor& aZoomFactor) const; 
public:        // properties                 
        IMPORT_C void SetTypeface(const TTypeface aTypeface); 
        IMPORT_C void UseSystemTypeface(); 
        IMPORT_C TTypeface Typeface() const;
public:			//but not exported
		void RefetchPixelMappingL();

private: 
        CCoeFontProvider(const TDesC& aTypefaceName); 
        void ConstructL(); 
        void ReleaseAllFonts(); 
private: 
        class TFont 
                { 
        public: 
                TFont(const TCoeFont& aFontSpec, TInt aZoomFactor, const CFont* aFont = NULL); 
                static TInt Compare(const TFont& aFirst, const TFont& aSecond); 
        public: 
                const TCoeFont iCoeFont; 
                const TInt iZoomFactor; 
                const CFont* iFont; 
                }; 
private: 
        mutable RArray<TFont> iFonts; 
        TTypeface iTypeface; 
        RArray<TInt> iLogicalToPixelSizes; 
        }; 

#endif	// __COEFONTPROVIDER_H__
