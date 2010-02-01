/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKIMAGE_H__)
#define __EIKIMAGE_H__

#if !defined(__EIKALIGN_H__)
#include <eikalign.h>
#endif 

class CFbsBitmap;
class CBitmapContext;
 
/**
 *  The package class @c CEikImage enables bitmaps to be packaged into an
 *  image. Two bitmaps can be packaged, one for the image itself and, 
 *  optionally, another for the image’s mask. 
 */
class CEikImage : public CEikAlignedControl
    {
	
public:
    
    /**
     * C++ default constructor.
     */
    IMPORT_C CEikImage();
    
    /**
     * Destructor.
     */
    IMPORT_C ~CEikImage();

public: // framework
    
    /**
     * Gets the minimum size required to draw the image.
     *
     * @return The minimum size required to draw the image.
     */
    IMPORT_C TSize MinimumSize();
    
    /**
     * Constructs an image from resource using the specified resource reader. 
     *
     * @param aReader The resource reader.
     */	
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

public: // new functions

    /**
     * Creates a bitmap and a mask for an icon. If @c aMaskId is not negative
     * then function allocates bitmap and mask objects and sets member variables
     * to point at them. These bitmaps are not ready for drawing until they are 
     * initialized with @c SetSize() method. Usually, UI controls do this. Note
     * also that a single @c SetSize() call initializes both the bitmap and the 
     * mask. 
     *
     * If @c aMaskId is not needed and not given then this function creates the 
     * bitmap for an icon. Returned object is saved to the member variable. The
     * bitmap is not ready for drawing until it is initialized with @c 
     * SetSize() method. Usually, UI controls do this.
     *
     * @param aFilename File name. Can be either MBM or MIF file. 
     *        Extension is changed based on the given bitmap ID.
     * @param aMainId Bitmap id.
     * @param aMaskId Mask id, by default -1.
     */
	IMPORT_C void CreatePictureFromFileL(const TDesC& aFilename,
	                                     TInt aMainId,
                                         TInt aMaskId=-1);	
	 
    /** 
     * Sets picture parameters.
     *
     * @param aBitmap A bitmap.
     * @param aMaskBitmap A bitmap mask.
     */
	IMPORT_C void SetPicture(const CFbsBitmap* aBitmap,
                             const CFbsBitmap* aMaskBitmap=NULL);
	 
    /**
     * Sets emphasis.
     *
     * @param aEmphasis Full emphasis if @c ETrue and if not then @c EFalse.
     */
	IMPORT_C void SetEmphasis(TBool aEmphasis);
    
    /**
     * Sets the owner of the picture.
     *
     * @param aOwnership @c Etrue if owner is external and @c EFalse if not.
     */
    IMPORT_C void SetPictureOwnedExternally(TBool aOwnership);
    
    /**
     * Gets a pointer of @c CFbsBitmap object.
     *
     * @return Pointer to handle to the bitmap or NULL.
     */
    IMPORT_C const CFbsBitmap* Bitmap() const;
    
    /**
     * Gets pointer of @c CFbsBitmap object.
     *
     * @return Pointer to handle to the bitmap's mask or NULL.
     */
    IMPORT_C const CFbsBitmap* Mask() const;
    
    /**
     * Sets new bitmap.
     *
     * @param aBitmap Pointer to @c CFbsBitmap object containing the bitmap.
     */
    IMPORT_C void SetBitmap(const CFbsBitmap* aBitmap);
    
    /**
     * Sets new bitmap mask.
     *
     * @param aMaskBitmap Pointer to @c CFbsBitmap object containing the bitmap
     *        mask.
     */
	IMPORT_C void SetMask(const CFbsBitmap* aMaskBitmap);
    
    /**
     * Sets new bitmap and bitmap's mask.
     *
     * @param aNewBitmap A bitmap.
     * @param aNewMask A bitmap mask.
     */
    IMPORT_C void SetNewBitmaps(const CFbsBitmap* aNewBitmap,
                                const CFbsBitmap* aNewMask);
    
    /**
     * Checks whether picture is owned externally.
     *
     * @return @c ETrue if picture owned externally and @c EFalse if 
     *         not.
     */ 
    IMPORT_C TBool IsPictureOwnedExternally(); 
    
    /**
     * Sets the brush style.
     *     
     * @param aBrushStyle A brush style.
     */
    IMPORT_C void SetBrushStyle(CGraphicsContext::TBrushStyle aBrushStyle);

public: // from CCoeControl   

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when
     * the control has grabbed the pointer. The control should implement this
     * function to handle pointer events.
     *
     * Note: events of type @c EButton1Down are processed before 
     * @c HandlePointerEventL() is called in order to transfer keyboard focus 
     * to the control in which the @c EButton1Down event occurred.
     *
     * If overriding @c HandlePointerEventL(), the implementation must include 
     * a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event.
     */   
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected: // from CCoeControl

    /**
     * From @c CCoeControl
     *
     * Writes the internal state of the control and its components to a stream.
     * Does nothing in release mode. Designed to be overidden and base called 
     * by subclasses.
     *
     * @since App-Framework_6.1
     * @param[in,out] aWriteStream The pointer writestream.
     */   
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: // from CCoeControl

	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void Reserved_2();

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:

	const CFbsBitmap* iBitmap;
	const CFbsBitmap* iMaskBitmap;
	TInt iImFlags;
	TInt iSpare;
	CGraphicsContext::TBrushStyle iBrushStyle;
	};

#endif  //  __EIKIMAGE_H__
