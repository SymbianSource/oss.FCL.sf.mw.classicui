/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Defines types used in AIW call creation.
*
*/





#ifndef AIWDIALDATATYPES_H
#define AIWDIALDATATYPES_H  

#include <cntdef.h>  // For KNullContactId
#include <tpbkcontactitemfield.h> // For contact item field

// CONSTANTS

// Lengths of various strings.
const TInt KAiwTelephoneNumberLength = 100; // Telephony number length.
const TInt KAiwNameBufferLength      = 50;  // The name length.
const TInt KAiwSubAddressLength      = 21;  // The subaddress length, see
                                            // ITU-T I.330 and 3GPP TS 11.14.
const TInt KAiwBearerLength          = 14;  // The bearer length.

// No number type.
const TInt KAiwDefaultNumberType     = -1;  // No number type.

// Constant for no contact
const TInt KAiwNoContact             = KNullContactId;

// Constant used as window group id to indicate that we wish to go to idle.
const TInt KAiwGoToIdle              = 0;

// Constants used in Redial parameter
const TInt KAiwRedialDefault         = -1;  // Default redial.
const TInt KAiwRedialOff             = -2;  // Redial is off.
const TInt KAiwRedialWithDefaultTime = -3;  // Redial on, with default time.

// Match is allowed by default.
const TBool KAiwDefaultAllowMatch    = ETrue;

// Type for telephone number.
typedef TBuf< KAiwTelephoneNumberLength > TAiwTelephoneNumber;

// Type for name.
typedef TBuf< KAiwNameBufferLength > TAiwNameBuffer;

// Type for contact item id.
typedef TContactItemId TAiwContactId;

// Type for calling party subaddress.
typedef TBuf< KAiwSubAddressLength > TAiwSubAddress;

// Type for bearer capability.
typedef TBuf8< KAiwBearerLength > TAiwBearerCapability;

// Type for contact item field
typedef TPbkContactItemField TAiwContactItemField;

/**
* Call type.
*/
enum TAiwCallType
    {
    EAiwVoice       = 0, // Voice call.
    EAiwVideo       = 1, // Video call.
    EAiwForcedVideo = 2, // Forced video call.
    EAiwVoIPCall    = 3  // VOIP call
    };




// CLASS DECLARATION

/**
* It defines the structure containing dial information.
*
**************************************************************************
* MUST Fields (change at least these before you use TCallUIDialDataV1):
**************************************************************************
*
*  iTelNumber      - String that is to be dialled.
*                    Default: Empty.
* 
**************************************************************************
* OPTIONAL fields:
**************************************************************************
* 
*  iCallType       - Type of the call, i.e. voice (default) or video call.
*                    Default: Voice call.
* 
*  iName           - Name corresponding to number. Name must be defined
*                    if show number equals to EFalse.
*                    Default: Empty.
* 
*  iNumberType     - Number type override. See PbkFields.hrh. Only phone
*                    number fields are supported.
*                    Default: KPhCltDefaultNumberType.
* 
*  iContactId      - Contact id. You should put always when you are dialing
*                    from phonebook contact.
*                    Default: No contact.
* 
*  iWindowGroup    - Window group of the application that wants to dial.
*                    Default: GoToIdle.
* 
*  iRedial         - Automatic redial override.
*                    Default: KPhCltRedialDefault.
* 
*  iShowNumber     - Permission to show number. ETrue iff it is allowed.
*                    Default: ETrue.
* 
*  iAllowMatch     - Permission to allow match. ETrue iff match is to be done.
*                    If you are dialing from sim pd or fdn, then this should
*                    be EFalse.
*                    Default: KPhCltDefaultAllowMatch.
* 
*  iEndOtherCalls  - Information if the existing calls are ended before
*                    this new one is made.
*                    Default: EFalse.
* 
*  iEmergencyCall  - Information whether this is an emergency call or not.
*                    Not mandatory. Set only if you know that the call is an 
*                    emergency call.
*                    Default: EFalse.
* 
*  iSubAddress     - The calling party subaddress. Supports SAT features.
*                    Defined in ITU-T I.330 and 3GPP TS 11.14.
*                    Default: Empty.
* 
*  iSATCall        - Set whether this is SAT originated call or not. 
*                    Supports SAT features.
*                    Default: EFalse.
* 
*  iBearer         - Bearer capabilities. Supports SAT features.
*                    Default: Empty.
*
*  iRemoveInvalidChars         
*                  - Information whether the invalid characters should be 
*                    removed from telephone number before dial or not.
*                    Default: EFalse.
*
*  iContactItemField         
*                  - Contact item field. Tells focused field for address select.
*                    Default: NULL.
*
*  @since 2.6
*/
class TAiwDialDataV1
    {          
    public:  // Constructors and destructor

        /**
        * Construct a dial data package
        */
        inline TAiwDialDataV1();


    public:  // Reset

        /**
        * Reset, i.e. set the default values as in constructor. 
        */
        inline void Reset();


    public: // Access - Setters

        /**
        * Set the number of the person to be called.
        * This is mandatory.
        *
        * @param aNumber The number of the person being called.
        */
        inline void SetTelephoneNumber( 
            const TAiwTelephoneNumber& aNumber );

        /**
        * Set the call type. Default: EPhCltVoice.
        *
        * @param aCallType The call type.
        */
        inline void SetCallType( TAiwCallType aCallType );

        /**
        * Set the name of the person who is to be called.
        *
        * @param aName The name of the person being called.
        */
        inline void SetName( const TAiwNameBuffer& aName );

        /**
        * Set the number type. 
        * 
        * See PbkFields.hrh. Only phone number fields are supported.
        *
        * @param aNumberType The number type.
        */
        inline void SetNumberType( TInt aNumberType );

        /**
        * Set the contact Id of the person being called.
        *
        * @param aContactId The contacts model contact id of the person being
        *                   called.
        */
        inline void SetContactId( TAiwContactId aContactId );

        /**
        * Set the window group of requesting application.
        *
        * @param aWindowGroupId The window group identifier.
        */
        inline void SetWindowGroup( TInt aWindowGroupId );

        /**
        * Set the number visibility in the phone app.
        *
        * If this is set to EFalse, then number is not shown or written to 
        * log event.
        *
        * @param aShowNumber Whether or not to show the number.
        */
        inline void SetShowNumber( TBool aShowNumber );

        /**
        * Change the redial mode.
        *
        * @param aRedial The new redial status
        */
        inline void SetRedial( TInt aRedial );

        /**
        * Set whether the name entered in SetName should be matched
        * against the personal directory (=phonebook).
        *
        * This should be set EFalse only if phone number has not been
        * taken from phonebook.
        *
        * @param aAllowMatch Whether to allow matches.
        */
        inline void SetAllowMatch( TBool aAllowMatch );

        /**
        * Set parameter for end other calls. 
        * 
        * If this is set to ETrue, other calls will be terminated before
        * dial.
        *
        * @param aEndCalls Are the other calls ended.
        */
        inline void SetEndOtherCalls( TBool aEndCalls );

        /**
        * Set whether this is known to be an emergency call or not.
        * If this function is not called, it is assumed that the call
        * is not an emergency call. However, in Phone application side it is 
        * checked whether the call actually is an emergency call or not before 
        * dialing.
        *
        * @param aEmergency 
        *        ETrue if the call is known to be an emergency call.
        *        EFalse if the call is not known to be an emergency call
        *        (default).
        */
        inline void SetEmergency( TBool aEmergency );

        /**
        * Set the calling party subaddress.
        * Defined in ITU-T I.330 and 3GPP TS 11.14.
        *
        * @param aSubAddress The calling party subaddress.
        */
        inline void SetSubAddress( const TAiwSubAddress& aSubAddress );

        /**
        * Set whether this is a SAT originated call or not.
        * If this function is not called, the originator is assumed to 
        * be other than SAT.
        *
        * @param aSATCall ETrue if SAT originated the call, EFalse otherwise.
        */
        inline void SetSATCall( TBool aSATCall );

        /**
        * Set the bearer capability.
        *
        * @param aBearer The bearer capabilities as defined in GSM 04.08.
        */
        inline void SetBearer( const TAiwBearerCapability& aBearer );

        /**
        * Set whether invalid characters should be removed before dial or not.
        *
        * @param aRemoveInvalidChars ETrue if invalid characters must be 
        *                            removed before dial, EFalse otherwise.
        */
        inline void SetRemoveInvalidChars( TBool aRemoveInvalidChars );

        /**
        * Set contact item field used in address selectors
        *
        * @since 3.0
        *
        * @param aContactItemField Contact item field information.
        */
        inline void SetContactItemField( const TAiwContactItemField& aContactItemField );
/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
        /**
        * Sets the service id.
        *
        * @since 3.2
        * 
        * @param aServiceId the service ID to be used when dialing.
        */
        inline void SetServiceId( TUint aServiceId );
// BRANCH_END 07-04-10 :janneluo

    public: // Access - Getters

        /** 
        * Telephone number
        * 
        * @return Returns the telephone number.
        */
        inline const TAiwTelephoneNumber& TelephoneNumber() const;

        /** 
        * Call type.
        *
        * @return Return the call type.
        */
        inline TAiwCallType CallType() const;

        /** 
        * Name
        * 
        * @return Return the name of the recipient.
        */
        inline const TAiwNameBuffer& Name() const;

        /** 
        * Number type.
        *
        * @return Return the number type.
        */
        inline TInt NumberType() const;

        /** 
        * Contact ID
        * 
        * @return Returns the contact id or KPhCltNoContact if none specified.
        */
        inline TAiwContactId ContactId() const;

        /**
        * Return the window group id. 
        *
        * @return Returns KPhCltGoToIdle if no id has previously been specified.
        */
        inline TInt WindowGroupId() const;

        /** 
        * Redial information.
        * 
        * @return Return the redial status,
        */
        inline TInt Redial() const;

        /** 
        * Number showing.
        * 
        * @return Returns the number visibility.
        */
        inline TBool ShowNumber() const;

        /** 
        * Is match allowed.
        * 
        * @return Returns the allow match setting.
        */
        inline TBool AllowMatch() const;

        /** 
        * End other calls
        * 
        * @return Returns ETrue if other calls should be ended before dial.
        */
        inline TBool EndOtherCalls() const;

        /** 
        * Emergency status (is emergency call or not).
        * 
        * @return Returns ETrue if the call is emergency call.
        *                 EFalse if the call is not emergency call.
        */
        inline TBool Emergency() const;

        /** 
        * Calling party subaddress.
        * 
        * @return Returns the calling party subaddress.
        */
        inline const TAiwSubAddress& SubAddress() const;

        /** 
        * SAT call information.
        * 
        * @return Returns ETrue if SAT is the originator of the call.
        *                 EFalse otherwise.
        */
        inline TBool SATCall() const;

        /** 
        * Bearer capability.
        * 
        * @return Returns the bearer capabilities as defined in GSM 04.08.
        */
        inline const TAiwBearerCapability& Bearer() const;

        /** 
        * Character removal information.
        * 
        * @return Returns ETrue if invalid characters will be removed.
        *                 EFalse otherwise.
        */
        inline TBool RemoveInvalidChars() const;

        /** 
        * Contact item field
        * 
        * @return Returns the contact item field or NULL if not specified.
        */
        inline const TAiwContactItemField* ContactItemField() const;

/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
        /**
        * Service id.
        *
        * @return the service ID to be used when dialing.
        */
        inline TUint ServiceId( ) const;
// BRANCH_END 07-04-10 :janneluo


    private:    // Data

        // Telephony number storage. MUST.
        TAiwTelephoneNumber       iTelNumber;
        
        // Call type.
        TAiwCallType              iCallType;

        // The name information storage.
        TAiwNameBuffer            iName;

        // The number type information storage.
        TInt                      iNumberType;

        // The contact ID storage.
        TAiwContactId             iContactId;

        // The window group identifier storage.
        TInt                      iWindowGroup;

        // The new redial status storage.
        TInt                      iRedial;

        // The number visibility information storage.
        TBool                     iShowNumber;

        // Allow match information storage.
        TBool                     iAllowMatch;

        // Information storage of the other call termination.
        TBool                     iEndOtherCalls;

        // The emergency call information.
        TBool                     iEmergencyCall;

        // The calling party subaddress.
        TAiwSubAddress            iSubAddress;

        // The information whether this is SAT originated call or not.
        TBool                     iSATCall;

        // The bearer capability.
        TAiwBearerCapability      iBearer;

        // Information if the not allowed characters should be removed 
        // before call from the telephony number.
        TBool                     iRemoveInvalidChars;

        // Contact item field
        const TAiwContactItemField*     iContactItemField;

/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
        // The service ID for dialing.
        TUint                      iServiceId;
// BRANCH_END 07-04-10 :janneluo
    };


// DATA TYPES

// A typedef'd packaged TAiwDialDataV1 for passing through a generic 
// API function member. 
typedef TPckgC< TAiwDialDataV1 >  TAiwDialDataV1Pckg;


// Inline methods
#include    <aiwdialdatatypes.inl>


#endif // AIWDIALDATATYPES_H
            
// End of File
