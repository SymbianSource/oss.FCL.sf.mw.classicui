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

#ifndef HGVGMEDIAWALLRENDERER_H_
#define HGVGMEDIAWALLRENDERER_H_

// INCLUDES
#include <e32base.h>
#include <VG/openvg.h>
#include <ganes/HgVgMediaWall.h>

/**
 * Helper abstract base class for drawing mediawall.
 */
NONSHARABLE_CLASS(CHgVgMediaWallRenderer) : public CBase
    {
public:
    
    /**
     * Factory method for constructing new MediaWallRenderer-Object
     */
    static CHgVgMediaWallRenderer* NewL(TInt aMaxQuads, const TRect& aWindowRect, 
            const TRect& aFrontRect, TReal aZOffset);

    /**
     * Destructor
     */
    virtual ~CHgVgMediaWallRenderer();
    
    
private:
    
    CHgVgMediaWallRenderer(const TRect& aWindowRect, 
            const TRect& aFrontRect, TReal aZOffset);
    
    void ConstructL(TInt aMaxQuads);
     
public:
            
    /**
     * Draws the mediawall.
     * 
     * @param aItems items to draw.
     * @param aSelectedIndex index of the selected item.
     * @param aViewPosition views position
     * @param aAnimationAlpha alpha from going from 0-1 during animation states.
     * @param aState current state of the animation.
     * @param aSelectionAnimationType type of the selection animation to use
     */
    void Draw(RPointerArray<CHgVgItem>& aItems,
            TInt aSelectedIndex, TReal aNextIndex,
            TReal aViewPosition,
            TReal aAnimationAlpha,
            CHgVgMediaWall::THgVgAnimationState aAnimationState, 
            CHgVgMediaWall::THgVgOpeningAnimationType aSelectionAnimationType, 
            CHgVgMediaWall::THgVgMediaWallStyle aStyle, 
            TReal aStartIndex, 
            TReal aSpringVelocity);

    /**
     * 
     */
    void DrawGrid(
            TInt aRowCount,
            RPointerArray<CHgVgItem>& aItems,
            TReal aViewX, TReal aViewY,
            TInt aCurItem, 
            TInt aPrevItem,
            TReal aAnimationAlpha,
            CHgVgMediaWall::THgVgAnimationState aAnimationState, 
            TInt aPickedItem, 
            CHgVgMediaWall::THgVgOpeningAnimationType aAnimationType);
    
    /**
     * Sets default icon for rendering items with no icons.
     * Ownership of the icon is not transfered.
     * 
     * @param aIcon reference to CGulIcon-object
     */
    void SetDefaultIconL(const CGulIcon& aIcon);
    
    /**
     * Sets Camera position modifier to use in rendering.
     * 
     * @param aCameraPosition camera position
     */
    void SetCameraPosition(TReal aX, TReal aY, TReal aZ);
    
    /**
     * Sets camera rotation modifiers to use in rendering.
     * 
     * @param aAngle angle in radians.
     */
    void SetCameraRotation(TReal aAngle);
                            
    /**
     * Gets ItemIndex of a quad at pointer position.
     * NOTE: This is only valid after drawing.
     * 
     * @param aPointerPosition position of the pointer
     * @return ItemIndex or KErrNotFound if nothings if no hit.
     */
    TInt GetItemIndex(const TPoint& aPointerPosition) const;
    
    /**
     * This should be called by the client. When skin change event is triggered.
     * This rebuilds all renderers skin related internal resources.
     */
    void HandleSkinChange();
        
    /**
     * 
     */
    TReal GetWorldSpaceRowHeight() const;
    
    /**
     * 
     */
    void SetReflections(TBool aEnabled);
        

    /**
     * 
     */
    TBool ReflectionsEnabled() const;
    
    /**
     * 
     */
    TSize ImageSize() const;
        
    /**
     * 
     */
    void SetFlippedRect(const TRect& aFlippedRect);
    
    /*
     * 
     */
    void SetFlipAngle(TReal aAngle);

    /**
     * 
     */
    void EnableBlurOnFlip(TBool aEnabled, TReal aBlurX, TReal aBlurY);
    
    
    /**
     * 
     */
    void SetOffset(const TPoint& aOffset);
    
    /**
     * 
     */
    void EnableFlipXY(TBool aEnabled);
    
    /**
     * 
     */
    void EnableLandscapeMode(TBool enabled);
    
    
private:
    
    class TQuad
        {
    public:
        // quads world-space position
        VGfloat iX;
        VGfloat iY;
        VGfloat iZ;
        // quads angle
        VGfloat iAngle;
        // image used to draw this quad
        VGImage iImage;
        // transform constructed in TransformQuads for rendering
        VGfloat iTM[9];
        // transformed 2d points
        VGfloat iPoints[2*4];
        // index from CHgVgItem
        TInt iItemIndex;
        // flag indicating iImage is not valid, uses iDefaultImage then.
        TBool iNoImage;
        //
        VGfloat iAlpha;
        VGfloat iMirroredPoints[2*4];
        VGfloat iMirroredTM[9];
        
        TBool iFlipped;
        };
       
    /**
     * 
     */
    void GetGroundColorFromSkin(VGfloat* aColor);

    /**
     * Transforms quads
     */
    void TransformQuads(TInt aNumVisibleQuads, TBool aMirrored, 
            VGfloat aFov, CHgVgMediaWall::THgVgOpeningAnimationType aOpeningAnimationType);
    
    /**
     * Sorts quads by z from iQuads to sorted quads.
     */
    void SortQuadsL(TInt aNumVisibleNumQuads);
   
    /**
     * Draws quads using VG
     */
    void DrawQuads(TBool aDrawMirrored);
    
    /**
     * Draws one quad using OpenVG
     */
    void DrawQuad(TQuad* q, TBool aDrawMirrored);
    
    /**
     * Setups quads into their positions/orientations, after this they can by transformed
     * and rendered.
     */
    TInt SetupQuads(RPointerArray<CHgVgItem>& aItems,
            TInt aSelectedIndex, TReal aNextIndex,
            VGfloat aViewPosition,
            VGfloat aAnimationAlpha,
            CHgVgMediaWall::THgVgAnimationState aState, 
            CHgVgMediaWall::THgVgOpeningAnimationType aAnimationType, 
            TReal aStartIndex, 
            TReal aSpringVelocity);


    /**
     * Setups quads for grid mediawall style.
     */
    void SetupQuadsToRow(
            TInt aRow,
            TInt aRowCount,
            TInt& aItemsOnScreen,
            RPointerArray<CHgVgItem>& aItems,
            TReal aViewX, TReal aViewY,
            TInt aCurItem, TInt aPrevItem, 
            TReal aAnimationAlpha,
            CHgVgMediaWall::THgVgAnimationState aAnimationState, 
            TInt aPickedItem, 
            CHgVgMediaWall::THgVgOpeningAnimationType aAnimationType);
    
    /**
     * Applies flip animation to a quad.
     */
    void ApplyOpeningAnimation(CHgVgMediaWallRenderer::TQuad* aQuad, 
            TReal aAnimationAlpha, TReal aZNear, CHgVgMediaWall::THgVgMediaWallStyle aMediaWallStyle, 
            CHgVgMediaWall::THgVgOpeningAnimationType aAnimationStyle);

    /**
     * Creates path and paint for ground.
     */
    void CreateGround();
        
    /**
     * Draws ground.
     * @param aWidth width of the ground.
     * @param aHeight height of the ground.
     */
    void DrawGround(TInt aWidth, TInt aHeight);
    
    
    /**
     * 
     */
    void TransformAndDraw(TInt itemsOnScreen, 
            CHgVgMediaWall::THgVgOpeningAnimationType aOpeningAnimationType);
    
    /**
     * 
     */
    void AdjustSettingsBasedOnRects(const TRect& aFrontRect, 
            TReal aZOffset);
    
    /**
     * 
     */
    VGfloat GetZInWorldSpaceBasedOnWidth(VGfloat aWidth);
    
    /**
     * 
     */
    void UpdateBlurChildImage(VGImage aImage);
    
private: 
        
    VGint iMaxQuads;
    TRect iRect;    
    VGfloat iCameraX;
    VGfloat iCameraY;
    VGfloat iCameraZ;
    VGfloat iCameraRotation;
    VGImage iDefaultImage;
    RPointerArray<TQuad> iQuads;
    RPointerArray<TQuad> iSortedQuads;
            
    VGPaint iGroundPaint;
    VGPath iGroundPath;     

    VGfloat iSelectedQuadStartX;
    VGfloat iSelectedQuadStartY;
        
    TBool iReflectionsEnabled;
    
    TSize iImageSize;
    
    VGfloat iCameraBaseX;
    VGfloat iCameraBaseY;
    VGfloat iCameraBaseZ;
    
    VGfloat iFlippedX;
    VGfloat iFlippedY;
    VGfloat iFlippedZ;
    
    // Which item is the front item in coverflow
    TInt iSelectedItemIndex;
    // Ending position of the left album stack
    TReal iLeftStackEndX;
    // Ending position of the right album stack
    TReal iRightStackStartX;
    // Z-coordinate of the frontmost album
    TReal iZNear;
    // Z-coordinate of the albums on the back
    TReal iZFar;
    // Space between albums in stacks
    TReal iSpaceBetween;    
    // How much to zoom when fast swiped
    TReal iFov;
    // angle to flip the item around X-axis in flip opening animation
    TReal iFlipAngle;
    
    VGImage iBlurImage;
    VGfloat iBlurAlpha;
    VGfloat iBlurDeviationX;
    VGfloat iBlurDeviationY;
    
    VGfloat iFlippedWidth;
    VGfloat iFlippedHeight;
    
    VGint iBlurImageWidth;
    VGint iBlurImageHeight;
    VGImage iChildBlurImage;
        
    TPoint iOffset;
    
    TBool iFlipXY;

    TBool iLandscape;
    };

#endif /* HGVGMEDIAWALLRENDERER */
