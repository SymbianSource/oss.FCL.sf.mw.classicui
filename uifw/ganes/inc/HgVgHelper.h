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

#ifndef HGVHELPER_H_
#define HGVHELPER_H_

// INCLUDES
#include <e32base.h>
#include <e32std.h>
#include <gdi.h>
#include <VG/openvg.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CHgVgEGL;
class CGulIcon;

#define RGBA(r, g, b, a) ((VGuint) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a)))


/**
 * Helper classes and methods for CHgVg* classes.
 */
namespace HgVgHelper
{
    /**--------------------------------------------------------------
     * Vertex and Matrix manipulations helper classes
     --------------------------------------------------------------*/

     // Forward declarations
    class TMatrix;
    class TVertex;

     /**
     * 3D Vertex class
     */
    class TVertex
       {
       public:
           // model coordinates
           VGfloat iX, iY, iZ;

           // transformed mode-view-coordinates
           VGfloat iTx, iTy, iTz;

           // projected screen coordinates
           VGfloat iScreenX;
           VGfloat iScreenY;

           /**
            * Projects model-view-coordinates to screen space coordinates.
            * 
            * @param aScreenWidth width of the rendering window
            * @param aScreenHeight height of the rendering window
            * @param aFov field of view to use
            */
           void ProjectPoint(VGfloat aScreenWidth, VGfloat aScreenHeight, VGfloat aFov);
           
           /**
            * Transform model coordinates by matrix given and sets
            * result to tranformed model-view-coordinates.
            * 
            * @param aMatrix model-view-transformation matrix.
            */
           void TransformPoint(const TMatrix& aMatrix);
       };

     /**
      * 4x4 Matrix class
      */
     class TMatrix
       {
       public:
           // matrix data
           VGfloat iM[4][4];

           // Construction and destruction.
           TMatrix();
           TMatrix(const TMatrix& rhs);
           ~TMatrix();

           // Operators
           TMatrix& operator=(const TMatrix& rhs);

           /**
            * Makes this matrix identity matrix.
            */
           void Identity();
           
           /**
            * Multiplies this matrix by rhs matrix.
            * 
            * @param rhs Right hand side matrix.
            */
           void Multiply(const TMatrix& rhs);
          
           /**
            * Sets this matrix to rotation matrix around X-axis.
            * 
            * @param aAngle angle in radians.
            */
           void RotationX(VGfloat aAngle);
           
           /**
            * Sets this matrix to rotation matrix around Y-axis.
            * 
            * @param aAngle angle in radians.
            */
           void RotationY(VGfloat aAngle);
           
           /**
            * Sets this matrix to rotation matrix around Z-axis.
            * 
            * @param aAngle angle in radians.
            */
           void RotationZ(VGfloat aAngle);
           
           /**
            * Sets this matrix to scale matrix.
            * 
            * @param aSx scaling on X-axis
            * @param aSy scaling on Y-axis
            * @param aSz scaling on Z-axis
            */
           void Scale(VGfloat aSx, VGfloat aSy, VGfloat aSz);
           
           /**
            * Sets this matrix to translation matrix.
            * 
            * @param aTx translation on X-axis.
            * @param aTy translation on Y-axis.
            * @param aTz translation on Z-axis. 
            */
           void Translation(VGfloat aTx, VGfloat aTy, VGfloat aTz);
       };

     /**--------------------------------------------------------------
      * IMAGE HANDLING ROUTINES
     --------------------------------------------------------------*/
     
    /**
     * Creates VGImage from CGuiIcon.
     * May leave for example if runs out of video memory.
     * 
     * @param aIcon valid CGuiIcon-object.
     * @return VGImage-object.
     */
    VGImage CreateVgImageFromIconL( const CGulIcon& aIcon );
    
        
    /**--------------------------------------------------------------
     * Misc. Helpers.
     --------------------------------------------------------------*/

    /**
     * Clamps value between lower and upper limits.
     * 
     * @param aValue value.
     * @param aUpper upper limit.
     * @param aLower lower limit.
     * @return clamped value.
     */
    VGfloat Clamp(VGfloat aValue, VGfloat aUpper, VGfloat aLower);
    
    /**
     * Linearly interpolates value between start and end.
     * 
     * @param aStart starting value.
     * @param aEnd ending value.
     * @param aT t value between 0.0f - 1.0f.
     */
    VGfloat Lerp(VGfloat aStart, VGfloat aEnd, VGfloat aT);

    /**
     * Gets values absolute.
     * 
     * @param aValue value.
     * @return absolute of the value.
     */
    VGfloat Abs(VGfloat aValue);    
        
    
    /**
     * Calculates bounding rect from points.
     * 
     * @param aRect destination rect-object, rectangle in symbian screen coordinates.
     * @param aPoints source points in vg coordinates (x, y, x, y...). 
     * @param aNumPoints number of points in aPoints.
     */
    void CalculateBoundingRect(TRect& aRect, VGfloat* aPoints, TInt aNumPoints, 
            const TRect& aWindowRect);    
    
        
    /**
     * Draws vg image to current vg surface.
     * NOTE: Assumes that the image is in vg coordinates.
     * 
     * @param aImage image to draw.
     * @param aPos position where to draw (in symbian screen coordinates).
     * @param aWindowRect drawing windows rectangle.
     */
    void DrawImage(VGImage aImage, const TPoint& aPos, const TRect& aWindowRect, TBool aCentered = EFalse);
    
    /**
     * Draws vg image to current vg surface multiplying its colors by a color.
     * NOTE: Assumes that the image is in vg coordinates.
     * 
     * @param aImage image to draw.
     * @param aColor color which is multiplied with image colors.
     * @param aPos position where the image is drawn (in sumbian screen coordinates)
     * @param aWindowRect drawing windows renctangle.
     */
    void DrawImageColorized(VGImage aImage, const TRgb& aColor, 
            const TPoint& aPos, const TRect& aWindowRect, TBool aCentered = EFalse);
    
    
    /**
     * Wrapper for creating paths.
     * 
     * @param aNumSegment
     * @param aSegments
     * @param aPoints
     */
    VGPath CreatePath(VGuint aNumSegments, const VGubyte* aSegments, const VGfloat* aPoints);
        
    /**
     * Wrapper for creating single color paints.
     * 
     * @param aColor
     */
    VGPaint CreateColorPaint(const TRgb& aColor);
    
    /**
     * Wrapper for creating single color paints.
     * 
     * @param aColor
     */
    VGPaint CreateColorPaint(const VGfloat* aColor);
       
    }

#endif /* HGVGHELPER */
