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

#ifndef HGVGIMAGECREATOR_H_
#define HGVGIMAGECREATOR_H_

// INCLUDES
#include <e32base.h>
#include <e32std.h>
#include <coemain.h>
#include <gdi.h>
#include <VG/openvg.h>

// FORWARD DECLARATIONS
class CHgVgEGL;
class CNvgEngine;

NONSHARABLE_CLASS(CHgVgImageCreator) : public CCoeStatic
    {
public:
    /**
     * 
     */
    static CHgVgImageCreator* InstanceL();

private:
    
    CHgVgImageCreator();
    ~CHgVgImageCreator();

    void ConstructL();
    
public:     
    /**
     * This must be called to set current EGL, before calling any other methods.
     */
    void Initialize(CHgVgEGL* aEGL);

    /**
     * Creates new VGImage from given CFbsBitmap.
     * Bitmap must be extended bitmap containing NVGData in data address.
     * 
     * @param aIcon icon used to create the image.
     * @return VGImage-handle to created image.
     */
    VGImage RenderImageFromIconL(const CFbsBitmap* aBitmap);
        
    //CNvgEngine* iNvgEngine;
    CHgVgEGL* iEGL;
    };



#endif /* HGVGIMAGECREATOR */
