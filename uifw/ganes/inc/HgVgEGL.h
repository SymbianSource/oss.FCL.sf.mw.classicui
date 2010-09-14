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

#ifndef HGVGEGL_H_
#define HGVGEGL_H_

// INCLUDES
#include <e32base.h>
#include <EGL/egl.h>
#include <VG/openvg.h>

class RWindow;
class CFbsBitmap;

/**
 * Wrapper for EGL
 */
NONSHARABLE_CLASS(CHgVgEGL) : CBase
    {
public:

    /**
     * Creates new CHgVgEGL
     * 
     * @param aRect window rectangle.
     * @return HgVgSkinRenderer-object.
     */
    static CHgVgEGL* NewL (RWindow& aWindow); 
        
    // Destructor.
    virtual ~CHgVgEGL();
    
public: // Methods
    
    void InitWindowSurfaceL(RWindow& aWindow);
    
    void FreeWindowSurface();

    TBool ReadyToRender() const;
    
    void SwapBuffers();

    EGLDisplay Display() const;
    
    EGLSurface Surface() const;
    
    EGLContext Context() const;
    
    EGLConfig CurrentConfig() const;
    
    CFbsBitmap* GetSurfaceToBitmap(const TRect& aRect, TBool aLandscape = EFalse) const;
    
    static TBool EglInitialized();
    
protected: // Constructors

    CHgVgEGL();

    void ConstructL (RWindow& aWindow);

    void InitEGL(RWindow& aWindow);
    
    void DestroyEGL();

    void InitEGLWindowSurfaceL(RWindow& aWindow);

private: // Data

    EGLDisplay iDisplay; // handle to egl display
    EGLSurface iSurface; // handle to egl surface, owns
    EGLContext iContextVg; // handle to vgl context, owns
    EGLConfig iChosenConfig; // current config used to create surface.

    };

#endif /* HGVGSKINRENDERER */
