/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Statuspane related utilities.
*
*/


#ifndef __AKNSTATUSPANEUTILS_H__
#define __AKNSTATUSPANEUTILS_H__

#include <e32base.h>

/**
 * This class contains statuspane related utility methods.
 */
class AknStatuspaneUtils
    {
public:

   /**
    * This method checks if statuspane layout is currently a stacon layout.
    * (stacon = combined status & control pane, side softkeys).
    *
    * @return ETrue if one of stacon layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool StaconPaneActive();

   /**
    * This method checks if statuspane layout is currently a stacon layout 
    * which has softkeylabels at the left side of the screen.
    *
    * @return ETrue if one of stacon layout with left softkeys is active, 
    *         otherwise EFalse.
    *
    */
    IMPORT_C static TBool StaconSoftKeysLeft();

   /**
    * This method checks if statuspane layout is currently a stacon layout 
    * which has softkeylabels at the right side of the screen.
    *
    * @return ETrue if one of stacon layout with right softkeys is active, 
    *         otherwise EFalse.
    *
    */
    IMPORT_C static TBool StaconSoftKeysRight();

   /**
    * This method checks if any of "idle" statuspane layouts is
    * active. Also video telephony statuspane is considered as
    * idle layout.
    *
    * @return ETrue if one of "idle" layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool IdleLayoutActive();

   /**
    * This method checks if any of flat statuspane layouts is
    * active. 
    *
    * @return ETrue if one of flat layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool FlatLayoutActive();    

   /**
    * This method checks if any of "usual" statuspane layouts is
    * active. 
    *
    * @return ETrue if one of "usual" layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool UsualLayoutActive();
    
   /**
    * This method checks if any of small statuspane layouts is
    * active. 
    *
    * @return ETrue if one of small layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool SmallLayoutActive();

    /**
     * This method checks if the active statuspane layout is compatible with
     * the touch pane.
     *
     * @return ETrue if the active layout is compatible with touch pane,
     *      otherwise EFalse.
     */
     IMPORT_C static TBool TouchPaneCompatibleLayoutActive();

   /**
    * This method checks if any of extended status pane portrait mode layouts is
    * active. 
    *
    * @return ETrue if any extended portrait layout is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool ExtendedLayoutActive();
    
    /**
     * This method checks if an nHD status pane layout is active.
     *
     * @return  @c ETrue if an nHD status pane layout is active,
     *          otherwise @c EFalse.
     */
    static TBool HDLayoutActive();
    
   /**
    * This method checks if statuspane layout is currently any of extended stacon layouts.
    * (stacon = combined status & control pane, side softkeys).
    *
    * @return ETrue if one of extended stacon layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool ExtendedStaconPaneActive();    

   /**
    * This method checks if statuspane layout is currently any of extended flat layouts.
    *
    * @return ETrue if one of extended flat layouts is active, otherwise EFalse.
    *
    */
    IMPORT_C static TBool ExtendedFlatLayoutActive();
    
    /**
     * This method can be used the check the status pane layout resource ID
     * of the current application. If the application has no status pane the
     * resource ID is checked from AknCapServer.
     *
     * @return The layout resource ID of the status pane.
     * @see @c R_AVKON_STATUS_PANE in avkon.rss
     *
     */
    IMPORT_C static TInt CurrentStatusPaneLayoutResId();
    
     /**
     * This method checks if the status pane belongs to active idle.
     *
     * @return  @c ETrue if the status pane belongs to active idle,
     *          otherwise @c EFalse.
     */
    static TBool IsActiveIdle();
    };

#endif //  __AKNSTATUSPANEUTILS_H__
