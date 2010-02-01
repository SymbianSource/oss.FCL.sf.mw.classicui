/*
* Copyright (c) 2002, 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: A control that can be used to display an animation. It can be constructed from 
*   a skin, or from resource.
* 
*
*/

// AKNBITMAPANIMATION.H
//

#if !defined(__AKNBITMAPANIMATION_H__)
#define __AKNBITMAPANIMATION_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#include <bmpancli.h>
#include <AknControl.h>
#include <AknIconUtils.h>

/**
 * Client class for wserv animations based on bitmaps.
 * 
 * Enables a client to package animation data, and send it to the window server for display.
 * Requires the RAnimDll to be already instantiated. Also provides functionality for sending
 * specific messages to configure the animation.
 *
 *  @lib avkon
 *  @since S60 0.9
 */
class RAknBitmapAnim : public RBitmapAnim
    {
public:
    /**
     * Constructor. 
     *
     * @param aAnimDll must be already instantiated.
     */
    RAknBitmapAnim(RAnimDll& aAnimDll);

    /**
     * Starts the animation, and displays the last frame when finished.
     */
    void StartAndKeepLastFrameL();

    /**
     * Stops the animation.
     *
     * @return the error value returned from wserv
     */
    TInt Stop();
    };

// FORWARD DECLARATIONS
class TResourceReader;
class TAknsItemID;

/*
 * A control that can be used to display an animation.
 */
NONSHARABLE_CLASS(CAknBitmapAnimation) : public CAknControl
    {
public:
    /**
     * 2 phase construction. The pattern for constructing this class is non-standard. Call 
     * NewL, set the container window, then call the appropriate method to contruct from
     * either skin or resource.
     */
    IMPORT_C static CAknBitmapAnimation* NewL();

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CAknBitmapAnimation();

public:
    /**
     * gives access to RBitmapAnimation.
     *
     * @return the RBitmapAnim
     */
    IMPORT_C RBitmapAnim& Animation();

    /**
     * gives access to CBitmapAnimClientData.
     *
     * @return the CBitmapAnimClientData
     */
    IMPORT_C CBitmapAnimClientData* BitmapAnimData() const;

    /**
     * Cancels the animation.
     *
     * @return the error code from stopping the animation
     */
    IMPORT_C TInt CancelAnimation();

    /**
     * Sets the frame index, initialising the animation if necessary.
     *
     * @param aIndex the frame index
     */
    IMPORT_C void SetFrameIndexL(TInt aIndex);

    /**
     * Sets the frame interval in milliSeconds, initialising the animation if necessary.
     *
     * @param aFrameIntervalInMilliSeconds the frame interval
     */
    IMPORT_C void SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds);

    /**
     * Starts the animation, initialising the animation if necessary, and starting the timer
     * if necessary.
     */
    IMPORT_C void StartAnimationL();

    /**
    * Sets the scale mode for the animation frames that is used when the
    * animation frames are scaled to the size of the control.
    * Default scale mode is EAspectRatioPreserved.
    *
    * @since 3.1
    * @param aMode scale mode
    */
    IMPORT_C void SetScaleModeForAnimationFrames(TScaleMode aMode);

    /**
    * Sets the scale mode for the animation background frame that is used when the
    * animation background frame is scaled to the size of the control.
    * Default scale mode is EAspectRatioPreserved.
    *
    * @since 3.1
    * @param aMode scale mode
    */
    IMPORT_C void SetScaleModeForAnimationBackgroundFrame(TScaleMode aMode);

    /**
    * Excludes the animation frames from the icon cache.    
    * Note that this method should be called before setting the size of the control
    * to be in effect. If the animation frames are created outside of the scope of this 
    * class method AknIconUtils::ExcludeFromCache should be called for animation frames
    * to get the same effect.
    * 
    * By default scalable animation frames are being put to icon cache after they are
    * no longer used. 
    * This makes it possible to retrieve recently used animation frames fast
    * without the need to render them again.
    * Excluding infrequently used animation frames from icon cache could 
    * improve performance and memory usage of the system.
    * 
    * @since 3.1    
    */
    IMPORT_C void ExcludeAnimationFramesFromCache();
    
public: 
    /**
     * Records whether the animation has started. If there is a timer, it is cancelled.
     *
     * @param aHasStarted if ETrue, started flag is recorded; if EFalse, the existing flag value is not changed.
     * @return returns KErrNone in the case of no error occurring.
     */
    TInt AnimationHasStarted(TBool aHasStarted);

public:
    /**
    * Construct the animation from skin.
    *
    * Usually this method should be called before ConstructFromResourceL,
    * and if EFalse is returned the caller should try to construct the
    * same animation with ConstructFromResourceL. The ownership of the
    * constructed animation and its frames is vested in this class.
    * Furthermore, the animation is not automatically updated during
    * a skin change.
    *
    * @since 2.0
    * @param aItemID Item ID of the animation.
    * @return ETrue if the animation was found and succesfully constructed.
    *   EFalse if the animation (or at least one of its frames) was not
    *   found.
    */
    IMPORT_C TBool ConstructFromSkinL( const TAknsItemID& aItemID );

public: // from CCoeControl
    /**
     * Construct animation from resource. This can be called after a call to NewL. Can
     * also be called after a failed attempt to call ConstructFromSkinL.
     * 
     * @param aResourceReader the resource reader
     */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

    /**
     * Minimum size.
     */
    IMPORT_C virtual TSize MinimumSize();
    
public:
    /**
     * Starts the animation, initialising the animation if necessary, and starting the timer
     * if necessary.
     */
    IMPORT_C void StartAnimationL( TBool aKeepLastFrame );

private: // from CCoeControl
    
    /*
     * Size changed.
     */
    virtual void SizeChanged();
    
    /*
     * Position Changed
     */
    virtual void PositionChanged();
    
    /*
     * Draw
     *
     * @parm aRect the drawing rect
     */
    virtual void Draw(const TRect& aRect) const;

    /*
     * Focus Changed
     */
    virtual void FocusChanged(TDrawNow aDrawNow);
private:

    /* 
     * Constructor
     */
    CAknBitmapAnimation();
    
    /*
     * Second phase construction
     */
    void ConstructL();
    
    /*
     * Complete animation initialisation. Sets the animation window, 
     * the position, and the animation data. Records the fact that 
     * initialisation has occurred.
     */
    void CompleteAnimationInitialisationL();
    
    /*
     * Checks the animation initialisation completion flag
     *
     * @return the initialisation flag
     */
    TBool IsInitialisationCompleted();
    
    /*
     * Create frame data, by extracting the interval and position from
     * the resource, and the frame data from the animation itself.
     *
     * @param aFramesReader the resource reader
     * @param aFileName the animation file
     * @param aVersion version of BMPANIM_DATA
     * @return the frame data
     */
	CBitmapFrameData* CreateFrameDataFromResourceL(TResourceReader& aFramesReader, const TDesC& aFileName, const TInt8 aVersion);
    
    /*
     * Set animation window
     */
    void SetAnimationWindowL();

private: // timer
    /*
     * Callback for the animation timer
     *
     * @param aPtr pointer to the owning class
     * @return any error value from the timer
     */
    static TInt AnimationStartedCallback(TAny* aPtr);

private:
    CBitmapAnimClientData* iBitmapAnimData;
    RAnimDll iAnimDll;
    RAknBitmapAnim iAnimation;
    TInt iFlags;
    CPeriodic* iTimer;
    TScaleMode iScaleModeFrames;
    TScaleMode iScaleModeBackgroundFrame;
    TBool iGainedFocus;
    };

#endif
