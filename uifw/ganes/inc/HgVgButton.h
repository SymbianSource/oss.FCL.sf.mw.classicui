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

#ifndef HGVGBUTTON_H_
#define HGVGBUTTON_H_

// INCLUDES
#include <e32base.h>
#include <coemain.h>
#include <VG/openvg.h>

class MHgVgMediaWallButtonObserver;
class CGulIcon;

/**
 * Button class, which draws buttons using OpenVG.
 */
NONSHARABLE_CLASS(CHgVgButton) : public CBase
    {
public:
        
    /**
     * Creates new CHgVgButton.
     *
     * @param aSize sizeof the button.
     * @param aPosition position of the button.
     * @return HgVgButton-object
     */
    static CHgVgButton* NewL (const TSize& aSize, const TPoint& aPosition, 
            const CGulIcon& aIcon); 
        
    // Destructor.
    virtual ~CHgVgButton();

private:
    CHgVgButton(const TSize& aSize, const TPoint& aPosition);
    
    void ConstructL(const CGulIcon& aIcon);
    
public: // METHODS

    /**
     * 
     */
    TBool HandlePointerEvent(const TPointerEvent& aEvent);
    
    /**
     * 
     */
    TBool IsEnabled() const;
    
    
    /**
     * 
     */
    const TPoint& Position() const;
    
    /**
     * 
     */
    const TSize& Size() const;
        
    /**
     * 
     */
    void SetEnabled(TBool aEnabled);
    
    /**
     * 
     */
    void SetPosition(const TPoint& aPosition);
    
    /**
     * 
     */
    void SetSize(const TSize& aSize);
            
    /**
     * 
     */
    void Draw(const TRect& aWindowRect, TReal aAlpha=1);
    
private: 

    TSize iSize;
    TPoint iPosition;
    VGImage iImage;
    TBool iEnabled;
    TBool iPointerDown;
    
    };

#endif /* HGVGBUTTON_H */
