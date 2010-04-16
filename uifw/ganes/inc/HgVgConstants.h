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
    const TReal KSpringVelocityToAnimationFactor(20.0f);


    // maximum quads in coverflow
    const TInt KMaxCoversVisible(17);
    
    // selected item index
    const TInt KSelectedItemIndex(8);

    // 
    const TReal KMinFlickSpeed(0.5f);

    const TInt KViewScrollingUpdateInterval( 16000 ); // > ~60 fps
    
    // The amound of pixels one item (virtually) takes on the screen (if you think coverflow as uniform list)
    const TReal KRowHeight(1.0f);
    const TInt KRowHeightStep(10);
    
    // PI
    const TReal PI(3.1415926535897932f);

    // Spring constant
    const TReal KSpringK(35.0f);
    
    // Spring damping
    const TReal KSpringDamping(11.0f);
    
    // maximum distance from target to snap 
    const TReal KPositionSnap(0.02);
    
    // maximum speed where to snap to item
    const TReal KMinSpringVelocity(0.05);
    
    // how far user must have dragged an item before 
    // we move to next item when user has stopped dragging gesture.
    const TReal KDragForwardThreshold(0.2f);
    
    // how many albums it is threoretically possible to go forward/backward
    // if the distance of a drag is fullscreen in length
    const TReal KItemsToDragOnFullScreenDrag(5.0f);
    
    // Physics update timestep
    const TReal KTimeStep(0.01f); // we update physics 100 fps
    
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
    const TReal KSwipeSpeedFactor(0.4f);
    
    // Camera rotation factor to use in animation
    // when swiping
    const TReal KCameraRotationFactor(PI/8.0f);
    
    // zooming factor to use in animation
    const TReal KCameraZoomFactor(0);
    
    const TInt KLetterPopupSizeX(128);
    const TInt KLetterPopupSizeY(128);
    const TInt KLetterPopupFontSize(100);
    const TReal KMaxLetterPopupOpacity(0.85);
        
    const TReal KZOffset(1.0f);

    const TInt KMediaWallKeyScrollingUpdateInterval( 50000 );
    
    
    const TInt KGridRowCount(3);
    
    const TReal KGridFlipAngle(PI * 2);
    
    const TReal KSpaceBetweenGridItems(0.02f);
    
    const TReal KDefaultBlurDeviation(4);
    }

#endif /* HGVGCONSTANTS */
