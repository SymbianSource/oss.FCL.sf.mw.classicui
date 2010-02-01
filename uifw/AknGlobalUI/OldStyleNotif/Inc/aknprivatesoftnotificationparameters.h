/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility implementation for CAknSoftNotificationParameters.
*
*/

#ifndef AKN_PRIVATE_SOFT_NOTIFICATION_PARAMETERS
#define AKN_PRIVATE_SOFT_NOTIFICATION_PARAMETERS

// INCLUDES
#include <AknSoftNotificationParameters.h> 
#include <aknSDData.h>

// CLASS DECLARATION

/**
*  Utility implementation for CAknSoftNotificationParameters.
*
*  @lib AknNotifyPlugin.dll
*  @since S60 1.2
*/
NONSHARABLE_CLASS(CAknPrivateSoftNoteParameters) : public CAknSoftNotificationParameters
    {
public:
    /**
    * Two-phased constructor.
    */
    static CAknPrivateSoftNoteParameters* NewL()
        {
        return (new (ELeave) CAknPrivateSoftNoteParameters);
        };
        
    /**
     * Destructor.
     */
    ~CAknPrivateSoftNoteParameters()
        {
        delete iSecondaryDisplayData;
        }
        
    void InternalizeL( RReadStream& aStream );      
    void ExternalizeL( RWriteStream& aStream ) const;   

    friend class CAknSoftNotificationPlugin;
    friend class CCustomNotifParams;
    
public: // Since S60 3.1
    CAknSDData* iSecondaryDisplayData;
    };

#endif // AKN_PRIVATE_SOFT_NOTIFICATION_PARAMETERS

// End of File
