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

#ifndef HGVGCONSTANTS_H_
#define HGVGCONSTANTS_H_

// INCLUDES
#include <e32base.h>

namespace HgVgConstants
    {

    // maximum velocity of the spring (max velocity of view movement)
    const TReal KMaxSpringVelocity(300.0f);
    
    //
    const TReal KSpringVelocityToAnimationFactor(10.0f);


    // maximum quads in coverflow
    const TInt KMaxCoversVisible(17);
    
    // selected item index
    const TInt KSelectedItemIndex(8);

    // fi
    const TReal KMinFlickSpeed(0.5f);

    const TInt KViewUpdateInterval( 15000 ); // > ~60 fps
    
    // The amound of pixels one item (virtually) takes on the screen (if you think coverflow as uniform list)
    const TReal KRowHeight(1.0f);
    const TInt KRowHeightStep(10);
    
    // PI
    const TReal PI(3.1415926535897932f);

    // Spring constant
    const TReal KSpringK(20.0f);
    
    // Spring damping
    const TReal KSpringDamping(11.0f);
    
    // maximum distance from target to snap 
    const TReal KPositionSnap(0.01);
    
    // maximum speed where to snap to item
    const TReal KMinSpringVelocity(0.01);
    
    // how far user must have dragged an item before 
    // we move to next item when user has stopped dragging gesture.
    const TReal KDragForwardThreshold(0.2f);
    
    // how many albums it is threoretically possible to go forward/backward
    // if the distance of a drag is fullscreen in length
    const TReal KItemsToDragOnFullScreenDrag(5.0f);
    
    // Physics update timestep
    const TReal KTimeStep(0.008333333333f); // we update physics 120 fps
    
    // Width of one quad in 3d space
    const TReal KWorldQuadWidth(1);
    
    // size of default icon in pixels
    const TInt KDefaultIconWidth(240);
    const TInt KDefaultIconHeight(240);
    
    // duration of album cover flip selection animation
    const TInt KSelectionAnimationDuration(400000); // 0.4 seconds
    
    // EGL surface bits
    const TInt KSurfaceRedBits(8);
    const TInt KSurfaceGreenBits(8);
    const TInt KSurfaceBlueBits(8);
    const TInt KSurfaceAlphaBits(8);
    
    // used for conversions
    const TInt KOneSecondInMicroSeconds(1000000);
    // how long a flick gesture can tage before it is interpreted as dragging only
    const TInt KMaxFlickDuration(200000); // 2 ms
    // how long it user must press to move one index further
    const TInt KKeyPressDuration(800000);
    // factor used for converting swipe speed to view movement
    const TReal KSwipeSpeedFactor(0.5f);
    
    // Camera rotation factor to use in animation
    // when swiping
    const TReal KCameraRotationFactor(PI/12.0f);
    
    // zooming factor to use in animation
    const TReal KCameraZoomFactor(0);
        
    // maximum opacity of the letter popup (1.0 would be fully opaque)
    const TReal KMaxLetterPopupOpacity(0.85);
    
    // update rate for the key scrolling timer
    const TInt KMediaWallKeyScrollingUpdateInterval( 50000 );
    
    // number of rows in grid mediawall
    const TInt KGridRowCount(3);
    
    // flipping angle in flip animation in grid mediawall
    const TReal KGridFlipAngle(PI * 2);
    
    // space between items in grid mediawall
    const TReal KSpaceBetweenGridItems(0.02f);
    
    // blur deviation factor for blur in zoom animation
    const TReal KDefaultBlurDeviation(4);

    //
    const TReal KSpringVelocityToZAlpha(10.0f);
    
    const TInt KFramesToZeroVelocity(60);
    
    const TReal KHalfItemWidth(0.5);
    
    // Specific constants for full screen coverflow mediawall
    const TInt KMediaWallFullScreenItemsOnScreen(5);
    const TReal KMediaWallFullScreenCameraZoomFactor(1.5);
    const TReal KMediaWallFullScreenCameraRotationFactor(KCameraRotationFactor*1.5);
    const TReal KMediaWallFullScreenSpringVelocityToAnimationFactor(10);
    const TReal KMediaWallFullScreenZOffset(1);
    const TInt KMediaWallFullScreenRowCount(1);
    const TReal KMediaWallFullScreenSpringK(KSpringK);
    const TReal KMediaWallFullScreenSpringDamping(KSpringDamping);
    const TReal KMediaWallFullScreenSpringMaxVelocity(KMaxSpringVelocity);
    const TReal KMediaWallFullScreenItemsToMoveOnFullScreenDrag(5);

    // distance to target item where titles get rendered in fullscreen mediawall
    // eg. if distance is greater than this, titles are not rendered
    const TReal KTitleDrawDistance(2.0);
    
    // Specific constants for tbone "portrait" mediawall
    const TInt KMediaWallTBoneItemsOnScreen(3);
    const TReal KMediaWallTBoneCameraZoomFactor(2);
    const TReal KMediaWallTBoneCameraRotationFactor(KCameraRotationFactor);
    const TReal KMediaWallTBoneSpringVelocityToAnimationFactor(KSpringVelocityToAnimationFactor);
    const TInt KMediaWallTBonePopupFontSize(100);
    const TInt KMediaWallTBoneLabelFontSize(18);
    const TReal KMediaWallTBoneZOffset(0.5);
    const TInt KMediaWallTBoneRowCount(1);
    const TReal KMediaWallTBoneSpringK(KSpringK);
    const TReal KMediaWallTBoneSpringDamping(KSpringDamping);
    const TReal KMediaWallTBoneSpringMaxVelocity(KMaxSpringVelocity);
    const TReal KMediaWallTBoneItemsToMoveOnFullScreenDrag(3);

    // if distance to target item is over this in tbone mediawall, it shows letter popup
    const TReal KDrawLetterPopupDistance(2.0);

    // Specific constants for mediawall grid (for photos application)
    const TInt KMediaWallGridItemsOnScreen(3*7);
    const TReal KMediaWallGridCameraZoomFactor(0.2);
    const TReal KMediaWallGridCameraRotationFactor(KCameraRotationFactor);
    const TReal KMediaWallGridSpringVelocityToAnimationFactor(KSpringVelocityToAnimationFactor/3);
    const TInt KMediaWallGridPopupFontSize(30);
    const TReal KMediaWallGridZOffset(0.5);
    const TInt KMediaWallGridRowCount(3);
    const TReal KMediaWallGridSpringK(KSpringK);
    const TReal KMediaWallGridSpringDamping(KSpringDamping*2);
    const TReal KMediaWallGridSpringMaxVelocity(KMaxSpringVelocity/3);
    const TReal KMediaWallGridItemsToMoveOnFullScreenDrag(15);
    
    }

#endif /* HGVGCONSTANTS */
