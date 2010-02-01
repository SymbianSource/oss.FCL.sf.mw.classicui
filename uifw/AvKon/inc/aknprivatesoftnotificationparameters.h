/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility implementation for CAknSoftNotificationParameters
*
*/

#ifndef AKN_PRIVATE_SOFT_NOTIFICATION_PARAMETERS
#define AKN_PRIVATE_SOFT_NOTIFICATION_PARAMETERS

//  INCLUDES
#include <aknsoftnotificationparameters.h> 

// CLASS DECLARATION
/**
*  Utility implementation for CAknSoftNotificationParameters
*
*  @lib AknNotifyPlugin.dll
*  @since 1.2
*/

class CAknPrivateSoftNoteParameters: public CAknSoftNotificationParameters
{
    public:
        /**
        * Two-phased constructor.
        */
        static CAknPrivateSoftNoteParameters* NewL()
            {
            return (new (ELeave) CAknPrivateSoftNoteParameters);
            };

        void InternalizeL( RReadStream& aStream );		
	    void ExternalizeL( RWriteStream& aStream ) const;	

    friend class CAknSoftNotificationPlugin;
};


#endif
