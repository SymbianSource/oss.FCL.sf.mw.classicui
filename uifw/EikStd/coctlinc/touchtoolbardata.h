/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class for passing data between touchpane and toolbar.
*
*/


#ifndef __TOUCH_TOOLBAR_DATA_H__
#define __TOUCH_TOOLBAR_DATA_H__

#include <akntransitionutils.h>
  
// Data utility class for communication between the touchpane and the toolbar.
NONSHARABLE_CLASS( CTouchToolbarData ) : public MAknTransitionUtilsObserver
    {
    public:
    static TInt SetData( const CCoeControl* aControl, TRect aDemarcationRect,
                         TBool aDemarcationRectSet );
    static CTouchToolbarData* GetData( const CCoeControl* aControl );
    
    TRect& DemarcationRect();
    TBool DemarcationRectSet() const;    
    TBool BetweenRegisterAndBegin() const;
    TBool SelectPressed() const;
    
    void SetBetweenRegisterAndBegin( TBool aBetweenRegisterAndBegin );
    void SetSelectPressed( TBool aSelectPressed );
    void SetFocusedItem( CCoeControl* aItem );
    
    // From MAknTransitionUtilsObserver
    TInt AknTransitionCallback(TInt aEvent, TInt aState, const TDesC8* aParams);
    
    private:
    CTouchToolbarData();
    
    TRect iDemarcationRect;
    TBool iDemarcationRectSet;
    TBool iBetweenRegisterAndBegin;
    TBool iSelectPressed;
    CCoeControl* iFocusedItem;
    };

#endif // __TOUCH_TOOLBAR_DATA_H__
