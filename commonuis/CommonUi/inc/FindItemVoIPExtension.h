/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Get count of VoIP profiles.
*
*/

#ifndef FINDITEMVOIPEXTENSION_H
#define FINDITEMVOIPEXTENSION_H

#include <e32base.h>
#ifndef RD_VOIP_REL_2_2
#include <CenRepNotifyHandler.h>

// FORWARD DECLARATIONS
class CRepository;
class CCenRepNotifyHandler;
#else
class CSPSettings;
class CSPSettingsVoIPUtils;
#endif // RD_VOIP_REL_2_2

// CLASS DECLARATION

/**
* Internal class to get count of VoIP profiles and
* the value of the settings Preferred Telephone.
* Allows also to drop RCSE component from rom.
*
*  @since Series 60 3.0
*/
NONSHARABLE_CLASS(CFindItemVoIPExtension):
    public CBase
#ifndef RD_VOIP_REL_2_2
    ,public MCenRepNotifyHandlerCallback
#endif // RD_VOIP_REL_2_2
    {
    public:
        /**
        * Two-phased constructor.
        */
        static CFindItemVoIPExtension* NewL();

        /**
        * Destructor.
        */
        ~CFindItemVoIPExtension();

        /**
        * Check if any VoIP profiles saved in the phone.
        * @since Series60 3.0
        * @return ETrue if VoIP profiles exist, else EFalse.
        */
        TBool VoIPProfilesExistL() const;

        /**
        * Check Preferred Telephony key value VoIP
        * @since Series60 3.0
        * @return ETrue if Send key creates VoIP call, else EFalse.
        */
        TBool IsPreferredTelephonyVoIP();

        /**
        * Returns information of general VoIP feature
        * @since Series60 3.0
        * @return ETrue if Send key creates VoIP call, else EFalse.
        */
        TBool IsVoIPSupported();

#ifndef RD_VOIP_REL_2_2
        /**
         * From MCentRepNotifyHandlerCallback.
         * @since Series S60 3.0
         * @param aId Id of the key that has changed.
         * @param aNewValue The new value of the key.
         */
        void HandleNotifyInt(
            TUint32 aId, TInt aNewValue );

        /**
         * From MCentRepNotifyHandlerCallback.
         * @since Series S60 3.0
         * @param aId Id of the key this instance listens to or if notifications for
         *            whole repository are listened, could also be KInvalidNotificationId.
         * @param aError Error code.
         * @param aHandler Pointer to the handler instance. 
         *                 This pointer can be used to identify the handler or restart the listening.
         */
        void HandleNotifyError(
            TUint32 aId, TInt aError, CCenRepNotifyHandler* aHandler );
#endif // !RD_VOIP_REL_2_2

    private:
        /**
        * C++ default constructor.
        */
        CFindItemVoIPExtension();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:
#ifndef RD_VOIP_REL_2_2
        /**
         * Dynamic VoIP status
         */
        TBool iVoIPSupported;

        /**
         * Preferred Telephony settings value. EFalse=CS and ETrue=PS.
         */
        TBool iPreferredTelephonyVoIP;

        /**
         * A CR session & notifier
         * Own.
         */
        CRepository* iCenRepSession;
        CCenRepNotifyHandler* iNotifier;

        /**
         *  A CR session & notifier for dynamic VoIP
         * Own. 
         */
        CRepository*                    iVoIPVariation;
        CCenRepNotifyHandler*           iVoIPVariationNotifier;
#else // RD_VOIP_REL_2_2
        /**
         * A Service provider settings
         * Own.  
         */
        CSPSettings* iSPSettings;
        CSPSettingsVoIPUtils* iSPSettingsVoipUtils;
#endif // !RD_VOIP_REL_2_2
    };
#endif      // FINDITEMVOIPEXTENSION_H

// End of File