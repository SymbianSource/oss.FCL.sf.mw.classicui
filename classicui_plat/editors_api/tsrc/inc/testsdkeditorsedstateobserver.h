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
* Description:  Test Aknsedsts.H
*
*/

#ifndef C_TESTSDKEDITORSEDSTATEOBSERVER_H
#define C_TESTSDKEDITORSEDSTATEOBSERVER_H

//  INCLUDES
#include <aknedsts.h>
#include <aknedstsobs.h>
#include <coemop.h>
#include <coecntrl.h>
#include <e32std.h>
#include <eikrted.h>

    /**
    *  CTestSDKEditorsEdStateObserver test class 
    */
class CTestSDKEditorsEdStateObserver : public CCoeControl,
                                       public MAknEdStateObserver,
                                       public MEikMenuObserver,
                                       public MEikRichTextEditorParserObserver
    {
public:
    /**
     * Two-phased constructor.
     */
    static CTestSDKEditorsEdStateObserver* NewL();
    
    /**
     * Destructor.
     */
    ~CTestSDKEditorsEdStateObserver();
    
private:
    
    /**
     * Constructor.
     */
    CTestSDKEditorsEdStateObserver();
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();
    
    /**
     * Receive key events.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
    /**
     * Draw control.
     */
    void Draw(const TRect& aRect) const;
    
    /**
     * Return number of controls in its window.
     */
    TInt CountComponentControls() const;
    
    /**
     * Controls in its window.
     */
    CCoeControl* ComponentControl(TInt aIndex) const;
    
    /**
     * Resize screen.
     */
    void SizeChanged();
    
    // from class MAknBackgroundProcess
    void  HandleAknEdwinStateEventL ( CAknEdwinState *aAknEdwinState, 
                                     EAknEdwinStateEvent aEventType );
    
    // from class MEikMenuObserver
    void SetEmphasis( CCoeControl *aMenuControl, TBool aEmphasis );
    
    // from class MEikMenuObserver
    void ProcessCommandL( TInt aCommandId );
    
    // from class MEikRichTextEditorParserObserver
    void HandleCursorOverParserL( const TDesC& aDoItText );
    };

#endif /*C_TESTSDKEDITORSEDSTATEOBSERVER_H*/
