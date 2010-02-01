/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef HGVGLETTERPOPUP_H_
#define HGVGLETTERPOPUP_H_

// INCLUDES
#include <e32base.h>
#include <VG/openvg.h>
#include <gulcolor.h>
#include <AknLayout2ScalableDef.h>

class CHgVgDrawBuffer;
class CFont;

/**
 * Helper class for drawing letter strip.
 */
NONSHARABLE_CLASS(CHgVgPopup) : CBase
    {
public:

    /**
     * Creates new CHgVgLetterStrip.
     *
     * @param aSize size of the letter strip in pixels.
     * @param aFont font to use for letter rendering.
     * @return HgVgLetterStrip-object
     */
    static CHgVgPopup* NewL (const TRect& aRect, const CFont* aFont); 
        
    // Destructor.
    virtual ~CHgVgPopup();

private:
    CHgVgPopup(const TRect& aRect, const CFont* aFont);
    
public: // METHODS
        
    /**
     * Sets letter in letter strip.
     * 
     * @param aLetter
     */
    void SetTextL(const TDesC& aText);
   
    /**
     * Set two text to popupup
     * 
     * @param aText1
     * @param aText2
     */
    void SetTexts(const TDesC& aText1, const TDesC& aText2);

    
    /**
     * Draws lettter strip at position.
     * 
     * @param aPosition position to draw letter strip.
     */
    void Draw(const TRect& aWindowRect, TReal aAlpha);
    
    /**
     * 
     */
    void SetLayouts(const TAknWindowComponentLayout& aPopupLayout, 
            const TAknTextComponentLayout& aTextLayout, const TRect& aParentRect);
    
protected: // Constructors
    CHgVgPopup();

    void ConstructL ( );

private: 

    TRect iRect;
    const CFont* iFont;
    CHgVgDrawBuffer* iDrawBuffer; // renderer for drawing glyphs, owns;
    VGImage iLetterImage;
    VGPath iLetterBgPath;
    VGPaint iLetterBgPaint;
    HBufC* iPrevText;
    
    TAknWindowComponentLayout iPopupLayout;
    TAknTextComponentLayout iTextLayout;
    TRect iParentRect;
    };

#endif /* HGVGLETTERPOPUP_H */
