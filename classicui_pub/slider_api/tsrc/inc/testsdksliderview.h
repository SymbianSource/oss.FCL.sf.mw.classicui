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
* Description:  slider_api
 *
*/

#ifndef C_TESTSDKSLIDERVIEW_H
#define C_TESTSDKSLIDERVIEW_H
#include <aknview.h>

class CSliderContainer;
/**
 * view class
 */
class CSliderView : public CAknView
    {
    
public:
    /**
     * constructors
     */
    CSliderView();
    /**
     * Symbian 2nd constructor
     */
    static CSliderView* NewL();
    /**
     * Symbian 2nd constructor
     */
    static CSliderView* NewLC();        
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    /**
     * Destructor
     */
    virtual ~CSliderView();
                        
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
    CSliderContainer* CreateContainerL();

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
    
 
    CSliderContainer* iSliderContainer;

    };

#endif /*C_TESTSDKSLIDERVIEW_H*/
