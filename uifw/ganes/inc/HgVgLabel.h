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

#ifndef HGVGLABEL_H_
#define HGVGLABEL_H_

// INCLUDES
#include <e32base.h>
#include <VG/openvg.h>
#include <gulcolor.h>
#include <AknLayout2ScalableDef.h>


// FORWARD DECLARATIONS
class CHgVgDrawBuffer;
class CFont;

/**
 * Helper class for rendering titles to media wall
 */
NONSHARABLE_CLASS(CHgVgLabel) : CBase
    {
public:

    /**
     * Creates new CHgVgLabel
     * 
     * @param aRect Rectangle of the drawing area.
     * @return HgVgLabel-object.
     */
    static CHgVgLabel* NewL (const TRect& aRect, const TDesC& aText=KNullDesC); 
        
    // Destructor.
    virtual ~CHgVgLabel();
   
public: // Methods
    
    void SetTextL(const TDesC& aText);
    
    void Draw(const TRect& aWindowRect, TReal aAlpha=1.0);
    
    void SetLayout(const TAknTextComponentLayout& aLayout, const TRect& aParentRect);
    
    void DrawEmptyText(const TRect& aClientRect, const TDesC& aText);

    void EnableLandscapeRendering(TBool enabled);

protected: // Constructors

    CHgVgLabel(const TRect& aRect);

    void ConstructL (const TDesC& aText);
    
    void Update();
    
private: // Data

    TRect iRect;
    
    HBufC* iText; // Item title. Own

    CHgVgDrawBuffer* iTextRenderer; // used to renrer text to bit gc, owns
        
    TRgb iTextColor;
    
    TRgb iShadowColor;
        
    VGImage iTextImage; // image containing texts, owns

    TBool iDirty;
    
    TAknTextComponentLayout iLayout;
    
    TRect iParentRect;
    
    TBool iLandscape;
    };

#endif /* HGVGLABEL */
