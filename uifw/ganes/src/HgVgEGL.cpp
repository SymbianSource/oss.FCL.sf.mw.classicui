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
#include "HgVgEGL.h"
#include "HgVgConstants.h"
#include <coecntrl.h>


using namespace HgVgConstants;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgEGL::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgEGL* CHgVgEGL::NewL(RWindow& aWindow)
    {
    CHgVgEGL* self = new ( ELeave ) CHgVgEGL();
    CleanupStack::PushL (self );
    self->ConstructL(aWindow);
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgEGL::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgEGL::ConstructL (RWindow& aWindow)
    {
    InitEGL(aWindow);
    }

// -----------------------------------------------------------------------------
// CHgVgEGL::CHgVgEGL()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgEGL::CHgVgEGL()
    {
    }
        
// -----------------------------------------------------------------------------
// CHgVgEGL::~CHgVgEGL()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgEGL::~CHgVgEGL ( )
    {
    DestroyEGL();
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::InitWindowSurfaceL()
// ---------------------------------------------------------------------------
//     
void CHgVgEGL::InitWindowSurfaceL(RWindow& aWindow)
    {
    //RDebug::Print(_L("CHgVgEGL::InitWindowSurface"));

    InitEGL(aWindow);
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::FreeWindowSurface()
// ---------------------------------------------------------------------------
//     
void CHgVgEGL::FreeWindowSurface()
    {
    //RDebug::Print(_L("CHgVgEGL::FreeWindowSurface"));

    // make sure there is nothing pending.
    vgFinish();
    
    // unbind current surface.
    eglMakeCurrent(iDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, iContextVg);

    // destroy surface
    eglDestroySurface(iDisplay, iSurface);
    iSurface = VG_INVALID_HANDLE;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::ReadyToRender()
// ---------------------------------------------------------------------------
//     
TBool CHgVgEGL::ReadyToRender() const
    {
    return iSurface && iDisplay && iContextVg;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::SwapBuffers()
// ---------------------------------------------------------------------------
//     
void CHgVgEGL::SwapBuffers()
    {
    eglSwapBuffers(iDisplay, iSurface);
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::Display()
// ---------------------------------------------------------------------------
//     
EGLDisplay CHgVgEGL::Display() const
    {
    return iDisplay;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::Surface
// ---------------------------------------------------------------------------
//     
EGLSurface CHgVgEGL::Surface() const
    {
    return iSurface;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::Context()
// ---------------------------------------------------------------------------
//     
EGLContext CHgVgEGL::Context() const
    {
    return iContextVg;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::CurrentConfig()
// ---------------------------------------------------------------------------
//     
EGLConfig CHgVgEGL::CurrentConfig() const
    {
    return iChosenConfig;
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::InitEGL()
// ---------------------------------------------------------------------------
//     
void CHgVgEGL::InitEGL(RWindow& aWindow)
    {
    
    // if we are just resizing or recreating
    if (iContextVg != VG_INVALID_HANDLE)
        {

        
        // save old surface
        EGLSurface oldSurface = VG_INVALID_HANDLE;
        if (iSurface != VG_INVALID_HANDLE)
            {        
            // make sure there is nothing pending.
            vgFinish();

            oldSurface = iSurface;
        
            // unbind current surface.
            eglMakeCurrent(iDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, iContextVg);            
            }
        
        // create new surface
        InitEGLWindowSurfaceL(aWindow);
        
        // bind new surface
        eglMakeCurrent(iDisplay, iSurface, iSurface, iContextVg);
        
        if (oldSurface != VG_INVALID_HANDLE)
            {
            // free old surface
            eglDestroySurface(iDisplay,oldSurface);
            }

        }
    else
        {

        // get display
        iDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        
        // intialize egl
        eglInitialize(iDisplay, NULL, NULL);
        
        // find suitable display config
        EGLint numConfigs;
        iChosenConfig = 0;
        
        const EGLint    KColorAttribList[] =
                {
                EGL_RED_SIZE,           KSurfaceRedBits,
                EGL_GREEN_SIZE,         KSurfaceGreenBits,
                EGL_BLUE_SIZE,          KSurfaceBlueBits,
                EGL_ALPHA_SIZE,         KSurfaceAlphaBits,
                EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
                EGL_RENDERABLE_TYPE,    EGL_OPENVG_BIT,
                EGL_NONE
                };
        
        eglChooseConfig(iDisplay, KColorAttribList, &iChosenConfig, 1, &numConfigs);
    
        // we need openvg
        eglBindAPI(EGL_OPENVG_API);
    
        InitEGLWindowSurfaceL(aWindow);
            
        // Create context for our thread.
        iContextVg = eglCreateContext(iDisplay, iChosenConfig, EGL_NO_CONTEXT, NULL);    
               
        // bind surface to context
        eglMakeCurrent(iDisplay, iSurface, iSurface, iContextVg);

        }
    
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::InitEGLWindowSurfaceL()
// ---------------------------------------------------------------------------
//
void CHgVgEGL::InitEGLWindowSurfaceL(RWindow& aWindow)
    {


    // Create surface with premodulated alpha.
    const EGLint KAttriblist[] = 
            {
            EGL_VG_ALPHA_FORMAT, EGL_VG_ALPHA_FORMAT_PRE,
            EGL_NONE
            };
    iSurface = eglCreateWindowSurface(iDisplay, iChosenConfig, &aWindow, KAttriblist);
    EGLint error = eglGetError();
    if (error == EGL_BAD_ALLOC)
        {
        //RDebug::Print(_L("CHgVgEGL:: Can't create surface! (out of memory)"));
        User::Leave(KErrNoMemory);
        }
    else if (error == EGL_BAD_SURFACE || iSurface == EGL_NO_SURFACE)
        {
        //RDebug::Print(_L("CHgVgEGL:: Can't create surface! (general)"));
        User::Leave(KErrGeneral);
        }
    
    eglSurfaceAttrib(iDisplay, iSurface, EGL_SWAP_BEHAVIOR, EGL_BUFFER_DESTROYED);
    
    }

// ---------------------------------------------------------------------------
// CHgVgEGL::DestroyEGL()
// ---------------------------------------------------------------------------
//     
void CHgVgEGL::DestroyEGL()
    {
    // deinitialize egl
    eglMakeCurrent(iDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(iDisplay,iSurface);
    eglDestroyContext( iDisplay, iContextVg );
    eglTerminate(iDisplay);    
    }


// ---------------------------------------------------------------------------
// CHgVgEGL::GetSurfaceToBitmap()
// ---------------------------------------------------------------------------
//     
CFbsBitmap* CHgVgEGL::GetSurfaceToBitmap(const TRect& aRect) const
    {
    // make sure every thing is in back buffer
    vgFinish();

    VGuint dataStride = 4 * aRect.Width();
    
    CFbsBitmap* bitmap = new CFbsBitmap();        
    
    if (bitmap)
        {
        // create temporary buffer for data
        RBuf8 buf;
        buf.Create(aRect.Height() * dataStride);
        buf.Fill(0xFF);

        // read data from vg (this is sloooww)
        vgReadPixels((void*)buf.Ptr(), 
                dataStride, VG_sARGB_8888, 0, 0, aRect.Width(), aRect.Height());                

        // because of bug in vg driver we need to swap memory using for loop, because
        // negative datastrides case crash
        bitmap->Create(TSize(aRect.Width(), aRect.Height()), EColor16MA);
        bitmap->BeginDataAccess();
        TUint8* ptrTrg = (TUint8*)bitmap->DataAddress();
        TUint8* ptrSrc = (TUint8*)buf.Ptr();
        for (TInt i = 0; i < aRect.Height(); i++)
            {
            Mem::Copy(ptrTrg + dataStride * i, 
                    ptrSrc + dataStride * (aRect.Height() - i - 1), dataStride);
            }
        bitmap->EndDataAccess();
        buf.Close();
        }
    
    return bitmap;    
    }

// End of File
