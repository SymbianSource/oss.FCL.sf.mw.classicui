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
* Description:  
*
*/

#ifndef C_TESTSDKLISTSCLBDATA_H
#define C_TESTSDKLISTSCLBDATA_H

#include <eikclbd.h>

/**
 * Class for testing protected API of CColumnListBoxData
 */
class CTestSDKColumnListBoxData : public CColumnListBoxData
    {
public: // constructor and destructor

    /**
     * C++ default constructor
     */
    CTestSDKColumnListBoxData();

    /**
     * C++ default constructor
     */
    ~CTestSDKColumnListBoxData();

public: 

// new fuctions

    /**
     * Test ConsturctLD
     */
    void ConstructLD();

    void ConstructLD( const TAknsItemID& aAnimationIID );

    /**
     * Test DrawText
     */
    void DrawText( CWindowGc& aGc, const TRect& aTextRect, 
        const TDesC& aText, const TDesC& aClippedText, 
        const TInt aBaselineOffset, 
        const CGraphicsContext::TTextAlign aAlign, 
        const CFont& aFont, const TBool aHighlight, 
        const TBool aIsTextClipped );

};

/**
 * Fake observer class for test
 */
class TTestListBoxAnimBgDrawer: public MColumnListBoxAnimBackgroundDrawer
    {
public:
    /**
     * Draws the background under the current highlight.
     *
     * Should be implemented in the derived class .
     *
     * @param aGc bitmapped graphics context to be drawn.
     * @return @c ETrue if Succeeded.
     */
    TBool DrawHighlightAnimBackground( CFbsBitGc& aGc ) const;
    
    };

#endif /*C_TESTSDKLISTSCLBDATA_H*/
