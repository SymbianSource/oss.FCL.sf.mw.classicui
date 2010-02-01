/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  UI component taking care of showing the long tap animation.
*
*/


#ifndef C_CAKNLONGTAPANIMATION_H
#define C_CAKNLONGTAPANIMATION_H

#include <AknControl.h>

class CAknBitmapAnimation;
class CAknLongTapAnimationExtension;

/**
 *  UI component showing a long tap animation on the screen.
 *
 *  CAknLongTapAnimation presents a short animation on screen
 *  indicating the user that he/she has performed a long tap with the stylus.
 *
 *  @lib avkon
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknLongTapAnimation) : public CCoeControl
    {

public:

    IMPORT_C static CAknLongTapAnimation* NewL();
    
    IMPORT_C static CAknLongTapAnimation* NewLC();
    
    /** 
     * Creates long tap animation to own window group or to the window group of the client.
     *
     * @param aOwnWindowGroup sets whether long tap animation creates own window group
     * @since s60 5.0 
     */
    IMPORT_C static CAknLongTapAnimation* NewL( TBool aOwnWindowGroup );
   
    virtual ~CAknLongTapAnimation();

    /**
     * Shows the long tap animation.
     *
     * @param aX X coordinate of animation's position relative to the screen.
     * @param aY Y coordinate of animation's position relative to the screen.
     */
    IMPORT_C void ShowAnimationL( const TInt aX, const TInt aY );

    /**
     * Hides and stops the long tap animation.
     */
    IMPORT_C void HideAnimation();

private:

    CAknLongTapAnimation();
        
    void ConstructL( TBool aOwnWindowGroup );
    
    void SetVisibility( TBool aVisibility );
    
// from base class CCoeControl

    /**
     * From CCoeControl.
     *
     */
    void Draw(const TRect& aRect) const;
    
      
       
    void StartAnimation();
    
    void CancelAnimation();
        
    void NextFrame();
	
	TInt static AnimationCallback(TAny* aPtr);
        
private: // data

    /**
     * Animation's window group.
     */
    RWindowGroup iWindowGroup;

	/**
     * Extension.
     */
	CAknLongTapAnimationExtension* iExtension;

    /**
     * Animation object which does the actual drawing.
     * Own.
     */
    CAknBitmapAnimation* iAnim;
    
    };


#endif      
// C_CAKNLONGTAPANIMATION_H
