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

#include "HgVgHelper.h"
#include "HgVgDrawBuffer.h"
#include "HgVgImageCreator.h"

#include <e32math.h>
#include <gulicon.h>
#include <fbs.h>
#include <nvg.h>
#include <AknIconHeader.h>
#include <AknIconUtils.h>

const TInt KVertexX(0);
const TInt KVertexY(1);
const TInt KVertexZ(2);
const TInt KNumColorValues(4);
const TInt KNumColorTransformValues(8);
const VGfloat KColorByteToFloatFactor(255.0f);


namespace HgVgHelper
    {

static VGImage CreateNonMaskedVgImageL( const CFbsBitmap& aBitmap )
    {
    TSize size = aBitmap.SizeInPixels();    
    VGImage image = vgCreateImage(VG_sRGB_565, size.iWidth, size.iHeight,VG_IMAGE_QUALITY_NONANTIALIASED);        

    if ( image == VG_INVALID_HANDLE )
        {
        User::Leave(KErrNoMemory);
        }
    
    if (aBitmap.DisplayMode() == EColor64K && !aBitmap.IsCompressedInRAM())
        {
        aBitmap.BeginDataAccess();
        TInt stride = aBitmap.DataStride();
        TUint8* ptr = (TUint8*)aBitmap.DataAddress();
        vgImageSubData (image, ptr, stride, VG_sRGB_565, 0, 0, size.iWidth, size.iHeight );        
        aBitmap.EndDataAccess();
        }
    else
        {
        TSize size = aBitmap.SizeInPixels();
        CHgVgDrawBuffer* temp = CHgVgDrawBuffer::NewL(size, EColor64K);
        temp->Gc().BitBlt(TPoint(0,0), &aBitmap);
        temp->GetDrawBufferToVgImage(size, TPoint(0,0), image, 
                VG_sRGB_565);
        delete temp;        
        }
    return image;
    }

static VGImage CreateMaskedVgImageL( CFbsBitmap* aBitmap, CFbsBitmap* aMask )
    {
    TSize size = aBitmap->SizeInPixels();
    CHgVgDrawBuffer* temp = CHgVgDrawBuffer::NewL(size, EColor16MA);
    temp->Gc().SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
    temp->Gc().SetBrushColor(TRgb(0,0,0,0));
    temp->Gc().Clear();
    temp->Gc().BitBltMasked(TPoint(0,0), aBitmap, size, aMask, EFalse);
    
    VGImage image = vgCreateImage(VG_sRGBA_8888, size.iWidth, size.iHeight,VG_IMAGE_QUALITY_NONANTIALIASED);
    temp->GetDrawBufferToVgImage(size, TPoint(0,0), image, 
            VG_sARGB_8888);
    
    delete temp;
    return image;
    }
    
// ---------------------------------------------------------------------------
// HgVgHelper::CreateVgImageFromIconL()
// ---------------------------------------------------------------------------
//     
VGImage CreateVgImageFromIconL(const CGulIcon& aIcon)
    {
        
    CFbsBitmap* bitmap = aIcon.Bitmap();
    User::LeaveIfNull(bitmap);
    CFbsBitmap* mask = aIcon.Mask();
    
    // if this is NVG image, rasterize it using 
    // nvg engine
    if (bitmap->ExtendedBitmapType() != KNullUid)
        {
        return CHgVgImageCreator::InstanceL()->RenderImageFromIconL(bitmap);
        }
    else
        {
        // otherwise just blit/copy to vg image.
        if (mask)
            {
            return CreateMaskedVgImageL(bitmap, mask);
            }
        else
            {
            return CreateNonMaskedVgImageL(*bitmap); 
            }
        }
    
    }
        
// ---------------------------------------------------------------------------
// HgVgHelper::Clamp()
// ---------------------------------------------------------------------------
//     
VGfloat Clamp(VGfloat value, VGfloat min, VGfloat max)
    {
    VGfloat result = (value < min) ? min : value;
    return (result > max) ? max : result;
    }

// ---------------------------------------------------------------------------
// HgVgHelper::Lerp()
// ---------------------------------------------------------------------------
//     
VGfloat Lerp(VGfloat start, VGfloat end, VGfloat t)
    {
    return start * (1.0f - t) + end * t;
    }

// ---------------------------------------------------------------------------
// HgVgHelper::Abs()
// ---------------------------------------------------------------------------
//     
VGfloat Abs(VGfloat value)
    {
    return (value < 0) ? -value : value;
    }

// ---------------------------------------------------------------------------
// HgVgHelper::CalculateBoudingRect()
// ---------------------------------------------------------------------------
//     
void CalculateBoundingRect(TRect& aRect, VGfloat* aPoints, TInt aNumPoints, 
        const TRect& aWindowRect)
    {
    TInt height = aWindowRect.Height();
    
    TPoint min((TInt)aPoints[0], height - (TInt)aPoints[1]);
    TPoint max((TInt)aPoints[0], height - (TInt)aPoints[1]);
    
    for (TInt i = 0; i < aNumPoints; i++)
        {
        
        TPoint temp((TInt)aPoints[i*2+0], height - (TInt)aPoints[i*2+1]);
        
        min.iX = (temp.iX < min.iX) ? temp.iX : min.iX;
        max.iX = (temp.iX > max.iX) ? temp.iX : max.iX;

        min.iY = (temp.iY < min.iY) ? temp.iY : min.iY;
        max.iY = (temp.iY > max.iY) ? temp.iY : max.iY;

        }
    
    // Top Left
    aRect.iTl = min;
    
    // Bottom Right
    aRect.iBr = max;        

    }

void TVertex::ProjectPoint(VGfloat aScreenWidth, VGfloat aScreenHeight, VGfloat aFov)
    {
    VGfloat hw = aScreenWidth * 0.5f;
    VGfloat hh = aScreenHeight * 0.5f;
    VGfloat alpha = aFov / 2.0f;
    double tanAlpha;
    Math::Tan(tanAlpha, alpha);
    VGfloat d = hw / tanAlpha;    
    iScreenX = (VGfloat)(hw + d * iTx / iTz);
    iScreenY = (VGfloat)(hh + d * iTy / iTz);    
    }

void TVertex::TransformPoint(const TMatrix& aMatrix)
    {
    iTx = iX * aMatrix.iM[0][0] + iY * aMatrix.iM[1][0] + iZ * aMatrix.iM[2][0] + aMatrix.iM[3][0];
    iTy = iX * aMatrix.iM[0][1] + iY * aMatrix.iM[1][1] + iZ * aMatrix.iM[2][1] + aMatrix.iM[3][1];
    iTz = iX * aMatrix.iM[0][2] + iY * aMatrix.iM[1][2] + iZ * aMatrix.iM[2][2] + aMatrix.iM[3][2];
    }

TMatrix::TMatrix()
    {
    }

TMatrix::TMatrix(const TMatrix& rhs)
    {
            (*this) = rhs;
    }

TMatrix::~TMatrix()
    {
    }

TMatrix& TMatrix::operator=(const TMatrix& rhs)
    {
        for (int i = 0; i < 4; ++i)
        {
                for (int j = 0; j < 4; ++j)
                {
                        iM[i][j] = rhs.iM[i][j];
                }
        }
        return *this;
        }
            
void TMatrix::Identity()
    {
            iM[0][0] = 1.0f;
            iM[0][1] = 0.0f;
            iM[0][2] = 0.0f;
            iM[0][3] = 0.0f;

            iM[1][0] = 0.0f;
            iM[1][1] = 1.0f;
            iM[1][2] = 0.0f;
            iM[1][3] = 0.0f;

            iM[2][0] = 0.0f;
            iM[2][1] = 0.0f;
            iM[2][2] = 1.0f;
            iM[2][3] = 0.0f;

            iM[3][0] = 0.0f;
            iM[3][1] = 0.0f;
            iM[3][2] = 0.0f;
            iM[3][3] = 1.0f;
    }
   
       
void TMatrix::Multiply(const TMatrix& rhs)
    {
        VGfloat temp[4][4];
        for (int i = 0; i < 4; ++i)
        {
                for (int j = 0; j < 4; ++j)
                {
                        temp[i][j] =
                        iM[i][0] * rhs.iM[0][j] +
                        iM[i][1] * rhs.iM[1][j] +
                        iM[i][2] * rhs.iM[2][j] +
                        iM[i][3] * rhs.iM[3][j];
                }
        }
        for (int i = 0; i < 4; ++i)
        {
                for (int j = 0; j < 4; ++j)
                {
                iM[i][j] = temp[i][j];
                }
        }
    }
    
    
void TMatrix::RotationX(VGfloat angle)
    {
    double sa, ca;
    Math::Sin(sa, angle);
    Math::Cos(ca, angle);

    iM[0][0] = 1.0f;
    iM[0][1] = 0.0f;
    iM[0][2] = 0.0f;
    iM[0][3] = 0.0f;

    iM[1][0] = 0.0f;
    iM[1][1] = ca;
    iM[1][2] = sa;
    iM[1][3] = 0.0f;

    iM[2][0] = 0.0f;
    iM[2][1] = -sa;
    iM[2][2] = ca;
    iM[2][3] = 0.0f;

    iM[3][0] = 0.0f;
    iM[3][1] = 0.0f;
    iM[3][2] = 0.0f;
    iM[3][3] = 1.0f;
    }


void TMatrix::RotationY(float angle)
    {
    double sa, ca;
    Math::Sin(sa, angle);
    Math::Cos(ca, angle);

    iM[0][0] = ca;
    iM[0][1] = 0.0f;
    iM[0][2] = -sa;
    iM[0][3] = 0.0f;

    iM[1][0] = 0.0f;
    iM[1][1] = 1.0f;
    iM[1][2] = 0.0f;
    iM[1][3] = 0.0f;

    iM[2][0] = sa;
    iM[2][1] = 0.0f;
    iM[2][2] = ca;
    iM[2][3] = 0.0f;

    iM[3][0] = 0.0f;
    iM[3][1] = 0.0f;
    iM[3][2] = 0.0f;
    iM[3][3] = 1.0f;
    }

void TMatrix::Scale(VGfloat aSx, VGfloat aSy, VGfloat aSz)
    {
    Identity();
    iM[0][0] = aSx;
    iM[1][1] = aSy;
    iM[2][2] = aSz;
    }

void TMatrix::Translation(VGfloat aX, VGfloat aY, VGfloat aZ)
{
    Identity();

    iM[3][0] = aX;
    iM[3][1] = aY;
    iM[3][2] = aZ;
}


// ---------------------------------------------------------------------------
// HgVgHelper::ComputeRotationMatrixByY
// ---------------------------------------------------------------------------
//     
void ComputeRotationMatrixByY(VGfloat* matrix, VGfloat angle)
    {
    // Build rotation matrix around Y-axis
    double sinrad, cosrad;
    Math::Sin (sinrad, angle );
    Math::Cos (cosrad, angle );
    VGfloat sa = sinrad;
    VGfloat ca = cosrad;

    VGfloat rotMatrix[] =
        {
        ca, 0, sa, 
        0, 1, 0, 
        sa, 0, -ca
        };

    // copy to result.
    for (int i = 0; i < 9; i++ )
        matrix[i] = rotMatrix[i];    
    }


// ---------------------------------------------------------------------------
// HgVgHelper::MultiplyMatrix()
// ---------------------------------------------------------------------------
//     
void MultiplyMatrix(VGfloat* aResult, VGfloat* aA, VGfloat* aB)
    {
    for (VGint i = 0; i < 3; ++i)
        {
            for (VGint j = 0; j < 3; ++j)
            {
                    aResult[i*3+j] =
                    aA[j*3+0] * aB[i*3+0] +
                    aA[j*3+1] * aB[i*3+1] +
                    aA[j*3+2] * aB[i*3+2];
            }
        }
    }


// ---------------------------------------------------------------------------
// HgVgHelper::TransformVertex
// ---------------------------------------------------------------------------
//         
void TransformVertex(const VGfloat* inVertex, VGfloat* outVertex, 
        const VGfloat* matrix)
    {
    VGfloat x = inVertex[KVertexX];
    VGfloat y = inVertex[KVertexY];
    VGfloat z = inVertex[KVertexZ];

    outVertex[KVertexX] = x * matrix[0] + y * matrix[3] + z * matrix[6];
    outVertex[KVertexY] = x * matrix[1] + y * matrix[4] + z * matrix[7];
    outVertex[KVertexZ] = x * matrix[2] + y * matrix[5] + z * matrix[8];
    }

// ---------------------------------------------------------------------------
// HgVgHelper::PerspectiveTransformVertex
// ---------------------------------------------------------------------------
//         
void PerspectiveTransformVertex(VGfloat* aInVertex, VGfloat* aOutVertex,
        VGfloat aScreenWidth, VGfloat aScreenHeight, VGfloat aFov)
    {
/*    VGfloat x = inVertex[KVertexX];
    VGfloat y = inVertex[KVertexY];
    VGfloat z = inVertex[KVertexZ];

    outVertex[KVertexX] = screenWidth * 0.5f + fov * x / z;
    outVertex[KVertexY] = screenHeight * 0.5f + fov * y / z;
*/    
    VGfloat hw = aScreenWidth * 0.5f;
    VGfloat hh = aScreenHeight * 0.5f;
    VGfloat alpha = aFov / 2.0f;
    double tanAlpha;
    Math::Tan(tanAlpha, alpha);
    VGfloat d = hw / tanAlpha;    
    aOutVertex[KVertexX] = (VGfloat)(hw + d * aInVertex[KVertexX] / aInVertex[KVertexZ]);
    aOutVertex[KVertexY] = (VGfloat)(hh + d * aInVertex[KVertexY] / aInVertex[KVertexZ]);    
        
    }

// ---------------------------------------------------------------------------
// HgVgHelper::DrawAlphaImage()
// ---------------------------------------------------------------------------
//         
void DrawImage(VGImage aImage, 
        const TPoint& aPos, const TRect& aWindowRect, TBool aCentered)
    {
            
    vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
    vgLoadIdentity();

    if (!aCentered)
        {
        vgScale(1, -1);
        vgTranslate(aPos.iX, -(aWindowRect.Height() - aPos.iY));
        }
    else
        {
        VGint w = vgGetParameteri(aImage, VG_IMAGE_WIDTH);
        VGint h = vgGetParameteri(aImage, VG_IMAGE_HEIGHT);        
        vgTranslate(aPos.iX, (aWindowRect.Height() - aPos.iY));
        vgScale(1, -1);        
        vgTranslate(-(VGfloat)w/2,-(VGfloat)h/2);
        }
    
    vgDrawImage(aImage);        

    }

// ---------------------------------------------------------------------------
// HgVgHelper::DrawImageColorized
// ---------------------------------------------------------------------------
//         
void DrawImageColorized(VGImage aImage, const TRgb& aColor, 
        const TPoint& aPos, const TRect& aWindowRect, TBool aCentered)
    {
    
    VGfloat values[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    
    values[0] = (VGfloat)aColor.Red() / KColorByteToFloatFactor;
    values[1] = (VGfloat)aColor.Green() / KColorByteToFloatFactor;
    values[2] = (VGfloat)aColor.Blue() / KColorByteToFloatFactor;
    values[3] = (VGfloat)aColor.Alpha() / KColorByteToFloatFactor;
            
    vgSetfv(VG_COLOR_TRANSFORM_VALUES, KNumColorTransformValues, values);
    vgSeti(VG_COLOR_TRANSFORM, VG_TRUE);
    
    HgVgHelper::DrawImage(aImage, aPos, aWindowRect, aCentered);

    vgSeti(VG_COLOR_TRANSFORM, VG_FALSE);        
    }



// ---------------------------------------------------------------------------
// HgVgHelper::CreatePath()
// ---------------------------------------------------------------------------
//         
VGPath CreatePath(VGuint aNumSegments, const VGubyte* aSegments, const VGfloat* aPoints)
    {
    VGPath path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
            1.0f, 0.0f, 4, 4, (unsigned int)VG_PATH_CAPABILITY_ALL);
          
    vgAppendPathData(path, aNumSegments, aSegments, aPoints);
    
    return path;
    }
    
// ---------------------------------------------------------------------------
// HgVgHelper::CreateColorPaint()
// ---------------------------------------------------------------------------
//         
VGPaint CreateColorPaint(const VGfloat* aColor)
    {
    VGPaint paint = vgCreatePaint();
    
    vgSetParameteri(paint, VG_PAINT_TYPE, 
        VG_PAINT_TYPE_COLOR);
    
    vgSetParameterfv(paint, VG_PAINT_COLOR,
        KNumColorValues, aColor);        
    
    return paint;
    }

// ---------------------------------------------------------------------------
// HgVgHelper::CreateColorPaint()
// ---------------------------------------------------------------------------
//         
VGPaint CreateColorPaint(const TRgb& aColor)
    {
    VGfloat values[4];
    
    values[0] = (VGfloat)aColor.Red() / KColorByteToFloatFactor;
    values[1] = (VGfloat)aColor.Green() / KColorByteToFloatFactor;
    values[2] = (VGfloat)aColor.Blue() / KColorByteToFloatFactor;
    values[3] = (VGfloat)aColor.Alpha() / KColorByteToFloatFactor;

    return CreateColorPaint(values);
    }

    }

// End of File
