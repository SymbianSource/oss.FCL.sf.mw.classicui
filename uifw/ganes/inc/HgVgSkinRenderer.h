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

#ifndef HGVGSKINRENDERER_H_
#define HGVGSKINRENDERER_H_

// INCLUDES
#include <e32base.h>
#include <VG/openvg.h>
#include <AknUtils.h>

// FORWARD DECLARATIONS
class CHgVgDrawBuffer;


/**
 * Helper class for rendering skin to media wall.
 */
NONSHARABLE_CLASS(CHgVgSkinRenderer) : CBase
    {
public:

    /**
     * Creates new CHgVgSkinRenderer.
     * 
     * @param aRect window rectangle.
     * @return HgVgSkinRenderer-object.
     */
    static CHgVgSkinRenderer* NewL (const TRect& aRect); 
        
    // Destructor.
    virtual ~CHgVgSkinRenderer();

    void SetRect( const TRect& aRect );
    
public: // Methods
    /**
     * Draws skin to draw buffer. Should be called from controls Draw method.
     * 
     * @param aProvider provider
     * @param aControl control
     */
    void UpdateSkinL(const MObjectProvider* aProvider, 
            const CCoeControl* aControl);
    
    /**
     * Renders skin using vg.
     * 
     * @param aRect window rectangle.
     */
    void Draw() const;
    

    /**
     * 
     */
    void EnableLanscapeRendering(TBool aLandscape);
protected: // Constructors
    CHgVgSkinRenderer(const TRect& aRect);

    void ConstructL ();
    
private: // Data

    CHgVgDrawBuffer* iDrawBuffer;
    
    VGImage iSkinImage;

    TRect iRect;
    
    TBool iLandscape;
    };

#endif /* HGVGSKINRENDERER */
