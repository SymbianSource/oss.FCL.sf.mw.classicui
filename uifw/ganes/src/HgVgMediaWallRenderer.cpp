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

// INCLUDE FILES

#include "HgVgMediaWallRenderer.h"
#include "HgVgHelper.h"
#include "HgConstants.h"
#include "HgVgConstants.h"

#include <VG/vgu.h>
#include <ganes/HgVgItem.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <AknLayout2ScalableDef.h>
#include <AknsDrawUtils.h>
#include <e32math.h>

using namespace HgVgConstants;

const VGfloat KColorByteToFloat(255.0f);
// Ending position of the left album stack
const VGfloat KLeftStackEndX(-1.04);//-235.0f);
// Ending position of the right album stack
const VGfloat KRightStackStartX(1.04);//235.0f);

// Space between albums in stacks
const VGfloat KSpaceBetween(1.04);//235);

const TInt KGroundHeightFactor(2);
const TInt KNumGroundGradientValues(4);
const VGfloat KGroundGradient[] = {
        0.0f, 0.0f, 0.0f, 1.0f
};
const TInt KGroundVerticesHint(4);
const TInt KGroundSegmentsHint(4);
const VGfloat KGroundScale(1.0f);
const VGfloat KGroundBias(0.0f);

const VGfloat KFov(PI/2);

const VGfloat KFlipAngle(PI);

const VGfloat KQuadVerts[] =
            {
                    -1.0f, -1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f
            };


VGfloat EaseOutQuad(VGfloat start, VGfloat end, VGfloat t)
{
    VGfloat s = t - 1.0f;
    VGfloat f = -(s*s*s*s) + 1.0f;    
    return start * (1.0f - f) + end * f;
}   

VGfloat EaseInQuad(VGfloat start, VGfloat end, VGfloat t)
{
    VGfloat s = t;
    VGfloat f = (s*s*s*s);    
    return start * (1.0f - f) + end * f;
}   


VGfloat BoundValue(VGfloat value, VGfloat min, VGfloat max)
{
    if (value > max) return max;
    if (value < min) return min;

    return value;
}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHgVgCoverflowRenderer::NewL()
// -----------------------------------------------------------------------------
//
CHgVgMediaWallRenderer* CHgVgMediaWallRenderer::NewL(TInt aMaxQuads, const TRect& aRect, 
        const TRect& aFrontRect, TReal aZOffset )
    {
    CHgVgMediaWallRenderer* self = new (ELeave) CHgVgMediaWallRenderer( aRect, 
            aFrontRect, aZOffset);
    CleanupStack::PushL( self );
    self->ConstructL(aMaxQuads);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWallRenderer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::ConstructL (TInt aMaxQuads)
    {
    for (TInt i = 0; i < aMaxQuads; i++)
        {
        TQuad* q = new (ELeave)TQuad;
        q->iItemIndex = -1;
        iQuads.Append(q);
        }
    CreateGround();
    }

// -----------------------------------------------------------------------------
// CHgVgMediaWallRenderer::CHgVgMediaWallRenderer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgMediaWallRenderer::CHgVgMediaWallRenderer(
        const TRect& aWindowRect, 
        const TRect& aFrontRect, 
        TReal aZOffset) :
        iRect(aWindowRect),
        iReflectionsEnabled(ETrue), 
        iSelectedItemIndex(KSelectedItemIndex),
        iLeftStackEndX(KLeftStackEndX),
        iRightStackStartX(KRightStackStartX),
        iSpaceBetween(KSpaceBetween),
        iFov(KFov),
        iFlipAngle(KFlipAngle)
    {
    AdjustSettingsBasedOnRects(aFrontRect, aZOffset);
    }
        
// -----------------------------------------------------------------------------
// CHgVgScrollBar::~CHgVgScrollBar()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgMediaWallRenderer::~CHgVgMediaWallRenderer ( )
    {
    if (iDefaultImage != VG_INVALID_HANDLE)
        vgDestroyImage(iDefaultImage);
    
    if (iChildBlurImage != VG_INVALID_HANDLE)
        vgDestroyImage(iChildBlurImage);
    
    if (iBlurImage != VG_INVALID_HANDLE)
        vgDestroyImage(iBlurImage);
    
    vgDestroyPaint(iGroundPaint);
    vgDestroyPath(iGroundPath);
    
    iQuads.ResetAndDestroy();
    iSortedQuads.Reset();
    }

// -----------------------------------------------------------------------------
// CHgMediaWallRenderer::SetDefaultImage()
// Setter for default image used to draw quads.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::SetDefaultIconL(const CGulIcon& aIcon)
    {    
    iDefaultImage = HgVgHelper::CreateVgImageFromIconL(aIcon);
    }

// -----------------------------------------------------------------------------
// CHgMediaWallRenderer::SetCameraPosition()
// Setter for camera position modifier.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::SetCameraPosition(TReal aX, TReal aY, TReal aZ)
    {
    iCameraX = aX;
    iCameraY = aY;
    iCameraZ = aZ;
    }

// -----------------------------------------------------------------------------
// CHgMediaWallRenderer::SetCameraRotation()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::SetCameraRotation(TReal aAngle)
    {
    iCameraRotation = aAngle;
    }

// -----------------------------------------------------------------------------
// CHgVgScrollBar::SortQuads
// Sorts quads from iQuads to iSortedQuads.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::SortQuads(TInt aNumQuads)
    {
    
    iSortedQuads.Reset();
    
    for(TInt i = 0; i < aNumQuads; ++i)
        {
        iSortedQuads.Append(iQuads[i]);
        }
    
    for (TInt i = 1; i < aNumQuads; i++)
        {
        for (int j = 0; j < aNumQuads; j++)
            {
            if( iSortedQuads[i]->iZ > iSortedQuads[j]->iZ )
                {
                TQuad* q1 = iSortedQuads[i];
                TQuad* q2 = iSortedQuads[j];
                iSortedQuads[i] = q2;
                iSortedQuads[j] = q1;
                }
            }
        }
        
    }


// -----------------------------------------------------------------------------
// CHgVgScrollBar::GetItemIndex
// gets index of the item under pointer position.
// -----------------------------------------------------------------------------
//
TInt CHgVgMediaWallRenderer::GetItemIndex(const TPoint& aPointerPosition) const
    {
    for (TInt i = 0; i < iSortedQuads.Count(); i++)
        {
        VGfloat* verts = iSortedQuads[iSortedQuads.Count()-i-1]->iPoints;
        TRect rect;
        HgVgHelper::CalculateBoundingRect(rect, verts, 4, iRect);
        if (rect.Contains(aPointerPosition))
            {
            TInt index = iSortedQuads.Count()-i-1;
            return iSortedQuads[index]->iItemIndex;
            }
        }
    return KErrNotFound;    
    }


// -----------------------------------------------------------------------------
// CHgVgScrollBar::TransformQuads
// Draws quads using OpenVG.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::TransformQuads(TInt aNumVisibleQuads,
        TBool aMirrored, VGfloat aFov, CHgVgMediaWall::THgVgOpeningAnimationType aOpeningAnimationType)
    {

    VGfloat scW = (VGfloat) iRect.Width();
    VGfloat scH = (VGfloat) iRect.Height();
        
    VGfloat imW = (VGfloat)iImageSize.iWidth;
    VGfloat imH = (VGfloat)iImageSize.iHeight;
  
    // construct mirror matrix
    HgVgHelper::TMatrix mirrorMatrix;
    mirrorMatrix.Scale(1, -1, 1);

    // construct camera rotation matrix
    HgVgHelper::TMatrix cameraRotMatrix;    
    if (iFlipXY)
        {
        cameraRotMatrix.RotationX(iCameraRotation);
        }
    else
        {
        cameraRotMatrix.RotationY(iCameraRotation);
        }

    // mat[0] = transform
    // mat[1] = mirrored transform
    HgVgHelper::TMatrix mat[2];
    
    VGfloat cameraX = iCameraBaseX + iCameraX;
    VGfloat cameraY = iCameraBaseY + iCameraY;
    VGfloat cameraZ = iCameraBaseZ + iCameraZ;
    
    if (iFlipXY)
        {
        VGfloat foobar = cameraX;
        cameraX = cameraY;
        cameraY = foobar;
        }
        
    // scaling matrix is used to set correct size for the 
    // quad by image size
    VGfloat hImW = (VGfloat)KWorldQuadWidth * 0.5f;
    VGfloat hImH = (VGfloat)imH * (KWorldQuadWidth / imW) * 0.5f;
    VGfloat oldHImH = hImH;
    
    // flips image upside down
    HgVgHelper::TMatrix scaleMatrix;
    scaleMatrix.Scale(hImW, -hImH, 1); // negative scale because our all images are updaside down.

    TBool deform = 
            (aOpeningAnimationType == CHgVgMediaWall::EHgVgOpeningAnimationFlipToFront) ||
            (aOpeningAnimationType == CHgVgMediaWall::EHgVgOpeningAnimationZoomToFront);
    
    for (TInt j = 0; j < aNumVisibleQuads; j++)
        {
        TQuad* q = iQuads[j];
                                
        if (q->iFlipped && deform)
            {
            // animate scaling to flipped rect size
            VGfloat newH = (VGfloat)iFlippedHeight * (KWorldQuadWidth / iFlippedWidth) * 0.5f;
            hImH = HgVgHelper::Lerp(hImH, newH, iBlurAlpha);
            mat[0].Identity();
            mat[0].Scale(hImW, -hImH, 1);
            }
        else
            {
            // restore old normal half image height
            hImH = oldHImH;
            mat[0] = scaleMatrix;        
            }

        // rotMatrix rotates by quads angle
        HgVgHelper::TMatrix rotMatrix;
        rotMatrix.RotationY(-q->iAngle);

        // trMatrix translates by quads position
        HgVgHelper::TMatrix trMatrix;
        trMatrix.Translation(q->iX, q->iY + hImH, q->iZ);
                                
        // then rotate
        if (q->iAngle != 0)
            {
            mat[0].Multiply(rotMatrix);
            }
        
        // then translate to position
        mat[0].Multiply(trMatrix);
                
        // construct mirroring matrix
        if (aMirrored)
            {
            mat[1] = mat[0];
            mat[1].Multiply(mirrorMatrix);
            }
        
        // construct camera translation matrix
        HgVgHelper::TMatrix cameraMatrix;
        cameraMatrix.Translation(-cameraX, -cameraY - hImH, -cameraZ);

        // apply camera movement
        mat[0].Multiply(cameraMatrix);

        // apply camera rotation hack
        mat[0].Multiply(cameraRotMatrix);
        
        // apply to mirror matrix also
        if (aMirrored)
            {
            mat[1].Multiply(cameraMatrix);
            mat[1].Multiply(cameraRotMatrix);
            }

        // transform all points by resulting transformation matrix
        // and project to screen coordinates.
        TInt count = aMirrored ? 2 : 1;
        for (TInt k = 0; k < count; k++)            
            {
            VGfloat* tverts = NULL;
            VGfloat* tm = NULL; 
            
            if (k == 0)
                {
                tverts = q->iPoints;
                tm = q->iTM;
                }
            else
                {
                tverts = q->iMirroredPoints;
                tm = q->iMirroredTM;
                }

            for (TInt i = 0; i < 4; i++)
                {
                
                HgVgHelper::TVertex v;
    
                v.iX = KQuadVerts[i*3+0];
                v.iY = KQuadVerts[i*3+1];
                v.iZ = KQuadVerts[i*3+2];
    
                v.TransformPoint(mat[k]);
                
                v.ProjectPoint(scW, scH, aFov);
                
                tverts[i*2+0] = v.iScreenX;
                tverts[i*2+1] = v.iScreenY;
                
                }

            VGImage image = q->iNoImage ? iDefaultImage : q->iImage;
            VGfloat pxWidth = vgGetParameteri(image, VG_IMAGE_WIDTH);
            VGfloat pxHeight = vgGetParameteri(image, VG_IMAGE_HEIGHT); 
            
            // use screen coordinates to build warp matrix
            // for rendering the image
            vguComputeWarpQuadToQuad(tverts[0], tverts[1], tverts[2], tverts[3],
                    tverts[4], tverts[5], tverts[6], tverts[7], 0, 0, pxWidth, 0,
                    pxWidth, pxHeight, 0, pxHeight, tm);

            }
        }    
    }

// -----------------------------------------------------------------------------
// CHgVgScrollBar::DrawQuads
// Draws quads using OpenVG.
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::DrawQuads(TBool aDrawMirrored)
    {    

    VGfloat values[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
                
    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    
    for (TInt j = 0; j < iSortedQuads.Count(); j++)
        {
        TQuad* q = iSortedQuads[j];
        
        if (q->iAlpha < 0.01f)
            continue;

        values[3] = q->iAlpha;
        
        vgSetfv(VG_COLOR_TRANSFORM_VALUES, 8, values);
        
        if (q->iZ < 0)
            continue;
        
        DrawQuad(q, aDrawMirrored);
        
        }

    vgSeti(VG_COLOR_TRANSFORM, VG_FALSE);

    }

// -----------------------------------------------------------------------------
// CHgVgMediaWallRenderer::DrawQuad
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::DrawQuad(CHgVgMediaWallRenderer::TQuad* q, TBool aDrawMirrored)
    {
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);    
    vgLoadIdentity();
    
    if (iLandscape)
    {
        vgTranslate(0.0f, 640.0f); 
        vgRotate(-90.0f);
    }
         
    vgTranslate(iOffset.iX, iOffset.iY);

    
    VGImage image = q->iImage;
    if (q->iNoImage)
        {
        image = iDefaultImage;
        }

    if (aDrawMirrored)
        {
        vgMultMatrix(q->iMirroredTM);
        }
    else
        {
        vgMultMatrix(q->iTM);
        if ((iBlurImage != VG_INVALID_HANDLE) && (iChildBlurImage != VG_INVALID_HANDLE) && q->iFlipped)
            {
            vgGaussianBlur(iChildBlurImage, image, iBlurDeviationX*iBlurAlpha, 
                    iBlurDeviationY*iBlurAlpha, VG_TILE_PAD);
            image = iChildBlurImage;
            }
        }
    
    
    vgDrawImage(image);    
    }


// -----------------------------------------------------------------------------
// CHgVgScrollBar::Draw()
// -----------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::Draw(RPointerArray<CHgVgItem>& aItems,
        TInt aSelectedIndex, TReal aNextIndex,
        TReal aViewPosition,
        TReal aAnimationAlpha,
        CHgVgMediaWall::THgVgAnimationState aState, 
        CHgVgMediaWall::THgVgOpeningAnimationType aSelectionAnimationType, 
        CHgVgMediaWall::THgVgMediaWallStyle /*aStyle*/,
        TReal aStartIndex, 
        TReal aSpringVelocity)
    { 
    
    TInt itemsOnScreen = 0;
    itemsOnScreen = SetupQuads(aItems,
            aSelectedIndex, aNextIndex,
            aViewPosition,
            aAnimationAlpha,
            aState, aSelectionAnimationType, aStartIndex, aSpringVelocity);
    
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    vgRotate(-90.0f);
    vgTranslate(0.0f, -640.0f);
     
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();
    vgRotate(-90.0f);
    vgTranslate(0.0f, -640.0f);

    
    TransformAndDraw(itemsOnScreen, aSelectionAnimationType);
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::DrawGrid()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWallRenderer::DrawGrid(
        TInt aRowCount, 
        RPointerArray<CHgVgItem>& aItems, 
        TReal aViewX, TReal aViewY, 
        TInt aCurItem, TInt aPrevItem, 
        TReal aAnimationAlpha,
        CHgVgMediaWall::THgVgAnimationState aAnimationState, 
        TInt aPickedItem, 
        CHgVgMediaWall::THgVgOpeningAnimationType aAnimationType)
    {
    TInt itemsOnScreen = 0;

    for (TInt i = 0; i < aRowCount; i++)
        {
        SetupQuadsToRow(i, aRowCount, itemsOnScreen, 
                aItems, aViewX, aViewY, aCurItem, aPrevItem, 
                aAnimationAlpha, aAnimationState, aPickedItem,
                aAnimationType);
        }
    
    TransformAndDraw(itemsOnScreen, aAnimationType);
    }


TReal CHgVgMediaWallRenderer::GetWorldSpaceRowHeight() const
    {
    // TODO: replace these macig numbers
    return (120.0 / 90.0 * 0.25 + 0.02);
    }


// ---------------------------------------------------------------------------
// CHgVgCoverflowRenderer::CreateGround()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWallRenderer::CreateGround()
{
    // Create path and paint for drawing ground plane
    
    iGroundPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, KGroundScale, KGroundBias, 
            KGroundVerticesHint, KGroundSegmentsHint, (unsigned int)VG_PATH_CAPABILITY_ALL);
    
    vguRect(iGroundPath, 0, 0, 1, 1);
        
    VGfloat gradientStops[] = {
            0, 0.0f, 0.0f, 0.0f, 1.0f,
            0.01f, 0.0f, 0.0f, 0.0f, 0.95f,
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };
    
    VGfloat groundColor[4];
    GetGroundColorFromSkin(groundColor);

    gradientStops[1] = groundColor[0]; 
    gradientStops[2] = groundColor[1]; 
    gradientStops[3] = groundColor[2]; 
    
    gradientStops[6] = groundColor[0]; 
    gradientStops[7] = groundColor[1]; 
    gradientStops[8] = groundColor[2]; 

    gradientStops[11] = groundColor[0]; 
    gradientStops[12] = groundColor[1]; 
    gradientStops[13] = groundColor[2]; 

    iGroundPaint = vgCreatePaint();
            
    vgSetParameteri(iGroundPaint, VG_PAINT_TYPE, 
        VG_PAINT_TYPE_LINEAR_GRADIENT);
        
    vgSetParameterfv(iGroundPaint, VG_PAINT_LINEAR_GRADIENT,
        KNumGroundGradientValues, KGroundGradient);
    
    vgSetParameteri(iGroundPaint, VG_PAINT_COLOR_RAMP_SPREAD_MODE,
            VG_COLOR_RAMP_SPREAD_PAD);
    
    vgSetParameterfv(iGroundPaint, VG_PAINT_COLOR_RAMP_STOPS,
        5*3, gradientStops);


}

// ---------------------------------------------------------------------------
// CHgVgCoverflowRenderer::DrawGround()
// ---------------------------------------------------------------------------
//     
void CHgVgMediaWallRenderer::DrawGround(TInt aWidth, TInt aHeight)
    {
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
    vgLoadIdentity();
    if (iLandscape)
    {
        vgTranslate(0.0f, 640.0f); 
        vgRotate(-90.0f);
    }

    //vgTranslate(iOffset.iX, iOffset.iY);
    vgScale(aWidth, aHeight);
    vgSetPaint(iGroundPaint, VG_FILL_PATH);            
    vgDrawPath(iGroundPath, VG_FILL_PATH);
    }



// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::SetupQuadsToRow()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::SetupQuadsToRow(
        TInt aRow,
        TInt aRowCount,
        TInt &aItemsOnScreen,
        RPointerArray<CHgVgItem>& aItems,
        TReal aViewX, TReal aViewY,
        TInt aCurItem, TInt aPrevItem, 
        TReal aAnimationAlpha,
        CHgVgMediaWall::THgVgAnimationState aState, 
        TInt aPickedItem, 
        CHgVgMediaWall::THgVgOpeningAnimationType aAnimationType)
    {
        
    if (aItems.Count() <= 0)
        return;
        
    TReal src = aViewX;
    TReal frac;
    Math::Frac(frac, src);
    VGfloat fDiff = frac;

    TBool isSelectionToFocusedItem = 
        (
        (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateOpening) ||
        (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateClosing) ||
        (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateItemOpened)
        ) &&
        (aAnimationType != CHgVgMediaWall::EHgVgOpeningAnimationNone);

    TReal selectionAnimationAlpha = aAnimationAlpha;
    if (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateItemOpened)
        selectionAnimationAlpha = 1.0f;

    VGfloat leftIndex = (VGfloat)(iSelectedItemIndex - 1);
    VGfloat leftX = iLeftStackEndX;
    VGfloat step = iSpaceBetween;
    
    if (AknLayoutUtils::LayoutMirrored())
        {
        leftX = iRightStackStartX;
        step = -step;
        }

    TInt i = 0;
    
    TInt currentRow = ((TInt)aViewX - (iSelectedItemIndex)) * aRowCount; 
        
    VGfloat zFar = iZNear;
    VGfloat zNear = zFar - 0.8;
    
    TInt itemsOnRow = 0;
    
    TInt selX = aCurItem / 3;
    TInt selY = aCurItem % 3;
        
    TReal div = (TReal)(iQuads.Count()/aRowCount/2-1);
    
    while (itemsOnRow < (iQuads.Count()/aRowCount))
        {
                                            
        TInt itemIndex = currentRow + i * 3 + aRow;
        
        if (itemIndex < 0)
            {
            i++;
            continue;
            }
        
        // all items drawn and at the end of the list, lets bail out.
        if (itemIndex >= aItems.Count())
            {
            break;
            }

        TQuad* q = iQuads[aItemsOnScreen + itemsOnRow];        

        q->iZ = zFar;
        q->iAngle = 0;
        q->iFlipped = EFalse;
        
        VGfloat fi = (VGfloat)i - fDiff;
                        
        q->iX = leftX - step * (leftIndex - fi);
        q->iAlpha = 1;
        
        q->iItemIndex = itemIndex;
        
        if  (aItems[itemIndex]->VgImage() == VG_INVALID_HANDLE)
            {
            q->iNoImage = ETrue;
            }
        else
            {
            q->iNoImage = EFalse;
            q->iImage = aItems[itemIndex]->VgImage();
            }

                        
        VGfloat imW = (VGfloat) iImageSize.iWidth;
        VGfloat imH = (VGfloat) iImageSize.iHeight;

        // width is constant but same aspect ratio must be preserved
        VGfloat worldImageHeight = imH * (KWorldQuadWidth / imW);
        
        q->iY = (2 - aRow) * (worldImageHeight + KSpaceBetweenGridItems);
        
        if (aCurItem != KErrNotFound && itemIndex == aCurItem)
            {
            TReal alphaX = 1.0 - Min(Abs(aViewX - (TReal)selX), 1);
            TReal alphaY = 1.0 - Min(Abs(aViewY - (TReal)selY), 1);

            q->iZ = HgVgHelper::Lerp(zFar, zNear, Min(alphaX, alphaY));            
            }
        else if (aPrevItem != KErrNotFound && itemIndex == aPrevItem)
            {
            TReal alphaX = 1.0 - Min(Abs(aViewX - (TReal)selX), 1);
            TReal alphaY = 1.0 - Min(Abs(aViewY - (TReal)selY), 1);
            
            q->iZ = HgVgHelper::Lerp(zFar, zNear, 1.0f - Min(alphaX, alphaY));
            }
        
        q->iAlpha = HgVgHelper::Lerp(1, 0, Max(0.0, (Abs(q->iX)-1.0) / div));         

        if (isSelectionToFocusedItem && (itemIndex == aPickedItem))
            {
            q->iAlpha = 1;
            q->iFlipped = ETrue;
            iBlurAlpha = selectionAnimationAlpha;
            ApplyOpeningAnimation(q, selectionAnimationAlpha, zFar, 
                    CHgVgMediaWall::EHgVgMediaWallStyleGrid, 
                    aAnimationType);
            }
        
        if (iFlipXY)
            {
            VGfloat temp = q->iX;
            q->iX = q->iY;
            q->iY = -temp;
            }
        
        i++;
        itemsOnRow++;
        }
        
    aItemsOnScreen += itemsOnRow;
    
    }



// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::SetupQuads()
// ---------------------------------------------------------------------------
//
TInt CHgVgMediaWallRenderer::SetupQuads(RPointerArray<CHgVgItem>& aItems,
        TInt aSelectedIndex, TReal /*aNextIndex*/,
        VGfloat aViewPosition,
        VGfloat aAnimationAlpha,
        CHgVgMediaWall::THgVgAnimationState aState, 
        CHgVgMediaWall::THgVgOpeningAnimationType aOpeningAnimationType, 
        TReal /*aStartIndex*/, 
        TReal aSpringVelocity)
    {
    
    
    if (aItems.Count() <= 0)
        return 0;
           
    VGfloat selectionAnimationAlpha = aAnimationAlpha;

    TBool isSelectionToFocusedItem = 
        ((aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateOpening) ||
        (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateClosing) ||
        (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateItemOpened)) &&
        (aOpeningAnimationType != CHgVgMediaWall::EHgVgOpeningAnimationNone);

    if (aState == CHgVgMediaWall::EHgVgMediaWallAnimationStateItemOpened)
        selectionAnimationAlpha = 1.0f;
        
    TReal src = aViewPosition;
    TReal frac;
    Math::Frac(frac, src);
    VGfloat fDiff = frac;
            
    VGfloat leftIndex = (VGfloat)(iSelectedItemIndex - 1);
    VGfloat leftX = iLeftStackEndX;
    VGfloat step = iSpaceBetween;

    // support mirrored layouts (right-to-left reading)
    if (AknLayoutUtils::LayoutMirrored())
        {
        leftX = -iLeftStackEndX;
        step = -step;
        }
    
    TInt i = 0;
    TInt itemsOnScreen = 0;
    TInt currentRow = (TInt)aViewPosition - KSelectedItemIndex;
        
    TReal zAlpha = Abs(aSpringVelocity / KSpringVelocityToZAlpha);
    VGfloat zNear = HgVgHelper::Lerp(iZFar, iZNear, 1.0f - BoundValue(zAlpha, 0, 1));
        
    while (itemsOnScreen < iQuads.Count())
        {
        TInt itemIndex = currentRow + i;

        // not really an item
        if (itemIndex < 0)
            {
            i++;
            continue;
            }
        
        // got past all items
        if (itemIndex  >= aItems.Count())
            {
            break;
            }

        // setup quads to represent coverflow
        TQuad* q = iQuads[itemsOnScreen];        

        q->iY = 0;
        q->iZ = iZFar;
        q->iAngle = 0;

        q->iFlipped = EFalse;

        VGfloat fi = (VGfloat)i - fDiff;
        
        q->iX = leftX - step * (leftIndex - fi);
        
        
        /*if (aStartIndex != aNextIndex)
            {
            // if start and next index are not same, we can just interpolate
            // items at these indices.
            if (itemIndex == (TInt)aStartIndex ||
                    itemIndex == (TInt)aNextIndex)
                {
                q->iZ = EaseInQuad((VGfloat)zNear, (VGfloat)iZFar, BoundValue(Abs(q->iX / leftX), 0, 1));
                q->iZ = Min(q->iZ, (VGfloat)iZFar);            
                }
            }
        else*/
            {
            // in this case we are just dragging and startindex and left index are
            // same so we need to interpolate z for all items coming/leaving center 
            // of the screen.
            
            q->iZ = EaseInQuad((VGfloat)zNear, (VGfloat)iZFar, BoundValue(Abs(q->iX / leftX), 0, 1));
            q->iZ = Min(q->iZ, (VGfloat)iZFar);                    
            }
        
        // calculate alpha so that items further are more transparent.
        q->iAlpha = HgVgHelper::Lerp(1, 0, Max(0.0, (Abs(q->iX)-2.0) / (TReal)(iQuads.Count()/2-2)));         
                    
        q->iItemIndex = itemIndex;
        
        // setup image to quad from item
        if  (aItems[itemIndex]->VgImage() == VG_INVALID_HANDLE)
            {
            q->iNoImage = ETrue;
            }
        else
            {
            q->iNoImage = EFalse;
            q->iImage = aItems[itemIndex]->VgImage();
            }

        // apply opening animation to item if needed
        if (isSelectionToFocusedItem && (itemIndex == aSelectedIndex))
            {
            q->iAlpha = 1;
            q->iFlipped = ETrue;
            iBlurAlpha = selectionAnimationAlpha;
            ApplyOpeningAnimation(q, selectionAnimationAlpha, q->iZ, 
                    CHgVgMediaWall::EHgVgMediaWallStyleCoverflowFullScreen, 
                    aOpeningAnimationType);
            }

        i++;
        itemsOnScreen++;
        }
        
    return itemsOnScreen;
    }


// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::ApplyFlipAnimation()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::ApplyOpeningAnimation(CHgVgMediaWallRenderer::TQuad* aQuad, 
        TReal aAnimationAlpha, TReal aZNear, CHgVgMediaWall::THgVgMediaWallStyle /*aMediaWallStyle*/, 
        CHgVgMediaWall::THgVgOpeningAnimationType aAnimationStyle)
    {
    VGfloat wz = 0.0f;
    VGfloat wy = (iCameraBaseY + iCameraY);
    VGfloat wx = (iCameraBaseX + iCameraX);
    VGfloat angle = 0;
    
    if (aAnimationStyle == CHgVgMediaWall::EHgVgOpeningAnimationFlipToFront)
        {    
        wz = iFlippedZ;    
        angle = iFlipAngle;
        wx += iFlippedX;
        wy += iFlippedY;
        }
    else if (aAnimationStyle == CHgVgMediaWall::EHgVgOpeningAnimationZoomToFront)
        {
        wz = iFlippedZ;    
        wx += iFlippedX;
        wy += iFlippedY;    
        }
    
    if (iBlurImage != VG_INVALID_HANDLE)
        {
        VGImage image = aQuad->iNoImage ? iDefaultImage : aQuad->iImage;
        UpdateBlurChildImage(image);
        }

    aQuad->iZ = HgVgHelper::Lerp(aZNear, wz, aAnimationAlpha);                
    aQuad->iX = HgVgHelper::Lerp(aQuad->iX, wx, aAnimationAlpha);
    aQuad->iY = HgVgHelper::Lerp(aQuad->iY, wy, aAnimationAlpha);
    aQuad->iAngle = -aAnimationAlpha * angle;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::GetGroundColorFromSkin()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::GetGroundColorFromSkin(VGfloat* aColor)
    {
    TRgb color(KRgbBlack);
    // get text color from skin
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( 
                AknsUtils::SkinInstance(),
                color,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG6 );
        }
    
    if (color.Blue() < 128)
        color = KRgbWhite;
    else
        color = KRgbBlack;
    
    aColor[0] = (VGfloat)color.Red() / KColorByteToFloat;
    aColor[1] = (VGfloat)color.Green() / KColorByteToFloat;
    aColor[2] = (VGfloat)color.Blue() / KColorByteToFloat;
    aColor[3] = 1.0f;
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::HandleSkinChange()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::HandleSkinChange()
    {
    vgDestroyPaint(iGroundPaint);
    vgDestroyPath(iGroundPath);
    CreateGround();    
    }

// ---------------------------------------------------------------------------
// CHgVgMediaWallRenderer::AdjustSettingsBaseOnFrontRect()
// ---------------------------------------------------------------------------
//
void CHgVgMediaWallRenderer::AdjustSettingsBasedOnRects(const TRect& aFrontRect, 
        TReal aZOffset)
    {
    
    // size of the images should be the same as given for aFrontRect
    iImageSize = aFrontRect.Size();
    
    // calculate screen center point
    TPoint center(iRect.Width()/2, iRect.Height()/2);
        
    // near z coordinate is calculated so that the size of the quad at front matches
    // aFrontRect
    iZNear = GetZInWorldSpaceBasedOnWidth(aFrontRect.Width());
    iZFar = iZNear + aZOffset;

    // width is always constant
    VGfloat ImW = KWorldQuadWidth;
    // height is altered by image aspect ratio
    VGfloat ImH = (VGfloat)(iImageSize.iHeight) * (KWorldQuadWidth / (VGfloat)iImageSize.iWidth);    
    
    // camera coordinates are altered so that the front quad 
    // is at correct place
    VGfloat deltaX = aFrontRect.Center().iX - center.iX;
    VGfloat deltaY = aFrontRect.Center().iY - center.iY;

    iCameraBaseX = ImW * (deltaX / (VGfloat)iImageSize.iWidth);
    iCameraBaseY = ImH * (deltaY / (VGfloat)iImageSize.iHeight);
    iCameraBaseZ = 0;

    }


void CHgVgMediaWallRenderer::TransformAndDraw(TInt itemsOnScreen, 
        CHgVgMediaWall::THgVgOpeningAnimationType aOpeningAnimationType)
    {
/*    
    vgSeti( VG_SCISSORING, VG_TRUE );
    VGfloat rects[4];
    rects[0]= 0;
    rects[1]= 0;
    rects[2]= iRect.Width();
    rects[3]= iRect.Height();
    vgSetfv( VG_SCISSOR_RECTS, 4, rects );
*/    
    vgSeti( VG_SCISSORING, VG_FALSE );    

    if (itemsOnScreen > 0)
        {    

        // draw reflections
        
        TransformQuads(itemsOnScreen, 
                iReflectionsEnabled, iFov, aOpeningAnimationType);

        SortQuads(itemsOnScreen);
        
        if (iReflectionsEnabled)
            DrawQuads(ETrue);
    
        DrawGround(iRect.Width(), iRect.Height() / KGroundHeightFactor);
    
        DrawQuads(EFalse);
                
        }
    else
        {
       
        // if no items exists, just draw ground plane.
        DrawGround(iRect.Width(), iRect.Height() / KGroundHeightFactor);
        
        }
    
    //vgSeti( VG_SCISSORING, VG_FALSE );    

    }

void CHgVgMediaWallRenderer::SetReflections(TBool aEnabled)
    {
    iReflectionsEnabled = aEnabled;
    }

TBool CHgVgMediaWallRenderer::ReflectionsEnabled() const
    {
    return iReflectionsEnabled;
    }

TSize CHgVgMediaWallRenderer::ImageSize() const
    {
    return iImageSize;
    }


void CHgVgMediaWallRenderer::SetFlippedRect(const TRect& aFlippedRect)
    {
    iFlippedWidth = aFlippedRect.Width();
    iFlippedHeight = aFlippedRect.Height();
    iFlippedZ = GetZInWorldSpaceBasedOnWidth(aFlippedRect.Width());
    TPoint center = iRect.Center();
    
    VGfloat ImW = KWorldQuadWidth;
    VGfloat ImH = (VGfloat)(iImageSize.iHeight) * (KWorldQuadWidth / (VGfloat)iImageSize.iWidth);    
    VGfloat deltaX = aFlippedRect.Center().iX - center.iX;
    VGfloat deltaY = aFlippedRect.Center().iY - center.iY;
    
    iFlippedY = -ImH * (deltaY / (VGfloat)aFlippedRect.Height());
    iFlippedX = ImW * (deltaX / (VGfloat)aFlippedRect.Width());
    }

VGfloat CHgVgMediaWallRenderer::GetZInWorldSpaceBasedOnWidth(VGfloat aWidth)
    {
    
    // calculate screen center point
    TPoint center(iRect.Width()/2, iRect.Height()/2);
    
    // Z-coordinate is set so that the front quad has 
    // the correct size
    TReal hw = iRect.Width() * 0.5f;
    TReal alpha = iFov / 2.0f;
    TReal tanAlpha;
    Math::Tan(tanAlpha, alpha);
    TReal d = hw / tanAlpha;    

    return (d * (-KWorldQuadWidth/2)) / ((TReal)(center.iX - aWidth/2) - hw);    

    }

void CHgVgMediaWallRenderer::SetFlipAngle(TReal aAngle)
    {
    iFlipAngle = aAngle;
    }


void CHgVgMediaWallRenderer::EnableBlurOnFlip(TBool aEnabled, TReal aBlurX, TReal aBlurY)
    {
    if (iBlurImage != VG_INVALID_HANDLE)
        {        
        vgDestroyImage(iBlurImage);
        iBlurImage = VG_INVALID_HANDLE;
        }
    if (aEnabled)
        {
        iBlurDeviationX = aBlurX;
        iBlurDeviationY = aBlurY;
        iBlurImage = vgCreateImage(VG_sRGBA_8888_PRE, iImageSize.iWidth, iImageSize.iHeight, 
                VG_IMAGE_QUALITY_NONANTIALIASED);
        }
    }

void CHgVgMediaWallRenderer::UpdateBlurChildImage(VGImage aImage)
    {
    VGint width = vgGetParameteri(aImage, VG_IMAGE_WIDTH);
    VGint height = vgGetParameteri(aImage, VG_IMAGE_HEIGHT);

    if (iBlurImageWidth != width || iBlurImageHeight != height)
        {                
        vgDestroyImage(iChildBlurImage);            
        iChildBlurImage = vgChildImage(iBlurImage, 0, 0, width, height);    
        iBlurImageWidth = width;
        iBlurImageHeight = height;
        }    
    }


void CHgVgMediaWallRenderer::SetOffset(const TPoint& aOffset)
    {
    iOffset = aOffset;
    }

void CHgVgMediaWallRenderer::EnableFlipXY(TBool aEnabled)
    {
    iFlipXY = aEnabled;
    }

void CHgVgMediaWallRenderer::EnableLandscapeMode(TBool enabled)
{
    iLandscape = enabled;
}


// End of File
