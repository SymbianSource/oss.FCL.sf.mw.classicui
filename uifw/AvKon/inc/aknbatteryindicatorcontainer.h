/*
* Copyright (c) 2006-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Application side control in the status pane battery area. 
*
*/


#ifndef C_AKNBATTERYINDICATORCONTAINER_H
#define C_AKNBATTERYINDICATORCONTAINER_H

#include <bacntf.h>
#include <coecntrl.h>
#include <AknControl.h>

class CAknBatteryPane;

/**
* Application side control in the status pane battery area.
*
* @since 3.2
* @lib Avkon
*/
NONSHARABLE_CLASS(CAknBatteryIndicatorContainer) : public CAknControl
	{
public:

    /**
    * Standard constructor
    */
    CAknBatteryIndicatorContainer();
    
    /**
    * Destructor
    */
    ~CAknBatteryIndicatorContainer();
        
    /** 
    * Construct from resources.
    *
    * @param aReader resource reader.
    */
    void ConstructFromResourceL(TResourceReader& aReader);

public: // From CCoeControl

    /**
    * From CCoeControl. Returns the number of component controls.
    */
    TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns the specified component control.
    */
    CCoeControl* ComponentControl(TInt aIndex) const;

protected: // From CCoeControl

    /**
    * From CCoeControl. Handles the size change events.
    */
    void SizeChanged();

private:

    CAknBatteryPane* iPane;
    TInt iSpare1;
    TInt iSpare2;

    };

#endif // C_AKNBATTERYINDICATORCONTAINER_H

