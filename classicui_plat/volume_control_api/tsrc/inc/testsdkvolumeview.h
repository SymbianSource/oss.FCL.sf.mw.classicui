/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  volume_control_api
 *
*/

#ifndef C_TESTSDKVOLUMEVIEW_H
#define C_TESTSDKVOLUMEVIEW_H
#include <aknview.h>

class CVolumeControlContainer;
    /**
     * view class
     */
class CVolumeControlView : public CAknView
    {
    
public:
    /**
     * constructors
     */
    CVolumeControlView();
    /**
     * Symbian 2nd constructor
     */
    static CVolumeControlView* NewL();
    /**
     * Symbian 2nd constructor
     */
    static CVolumeControlView* NewLC();  
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    /**
     * Destructor
     */
    virtual ~CVolumeControlView();
                        
    // from base class CAknView
    /**
     * Id
     */
    TUid Id() const;
    /**
     * HandleCommandL
     */
    void HandleCommandL( TInt aCommand );
    /**
     * CreateContainerL
     */
    CVolumeControlContainer* CreateContainerL();

protected:
    // from base class CAknView
    /**
     * DoActivateL
     */
    void DoActivateL(
        const TVwsViewId& aPrevViewId,
        TUid aCustomMessageId,
        const TDesC8& aCustomMessage );
    /**
     * DoDeactivate
     */
    void DoDeactivate();
    /**
     * HandleStatusPaneSizeChange
     */
    void HandleStatusPaneSizeChange();


private:
    /**
     * SetupStatusPaneL
     */
    void SetupStatusPaneL();
    /**
     * CleanupStatusPane
     */
    void CleanupStatusPane();
    
 
    CVolumeControlContainer* iVolumeControlContainer;

    };



#endif /*C_TESTSDKVOLUMEVIEW_H*/
