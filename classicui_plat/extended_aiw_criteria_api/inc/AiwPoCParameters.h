/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Defines the data used with S60 PoC UI AIW API
*
*/





#ifndef AIWPOCPARAMETERS_H
#define AIWPOCPARAMETERS_H

//  INCLUDES
#include <AiwPoCParameters.hrh>
#include <logwrap.h>

// DATA TYPES

/*
*   Following section defines both; the menus preferred by the consumer-
*   application from PoC-implementation in AIW's InitializeMenuPaneL and
*   in case of using AIW's HandleServiceCmdL commands identifying the 
*   commands themselves.
*
*   For menus all the choices are usable, but for AIW service command 
*   handling only the ones should be used which have 'Cmd' in their name.
*   For menus use the iPreferredMenu-field and for AIW service command
*   handling iCommandId-field in TAiwPocParameterData. 
*
*   See more info from documentation.
*
*   KAiwPoCMenuDataBased
*
*       Indicates consumer-application doesn't have any preferred menu 
*       items and PoC-implementation can base the menu items it offers
*       only to provided address data. Used only for menu requests.
*
*   EAiwPoCCmdTalk1to1
*
*       Indicates consumer-application prefers to have atleast PoC Talk 
*       1-to-1 menu  item regardless of the address data provided. Can 
*       be used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdTalkMany
*
*       Indicates consumer-application prefers to have atleast PoC Talk 
*       To Many menu item regardless of the address data provided. Can be 
*       used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdTalkGroup
*
*       Indicates consumer-application prefers to have atleast PoC Talk 
*       To Group menu item regardless of the address data provided. Can be 
*       used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdSendCallBackRequest
*
*       Indicates consumer-application prefers to have atleast Send PoC 
*       Callback Request menu item regardless of the address data provided.
*       Can be used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdJoinChatRoom
*
*       Indicates consumer-application prefers to have atleast PoC Join
*       Chatroom menu item regardless of the address data provided. Can be 
*       used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdShowCallerDetails
*
*       Indicates consumer-application prefers to have atleast PoC Caller
*       Details item regardless of the address data provided. Can be 
*       used with both; menu requests and as AIW service command.
*
*   EAiwPoCCmdShowDetails
*
*       Indicates consumer-application prefers to have atleast PoC 
*       Details menu item regardless of the address data provided. Can be 
*       used with both; menu requests and as AIW service command.
*
*/
// DATA BASED
// data based menu construction
const TInt KAiwPoCMenuDataBased = 0x00000000;
// See individual menu / command items from AiwPoCParameters.hrh where these
// items are actually located.

// DATA TYPES

/*
* enum TPoCOperationTypeId
*
*   PoC specific operation types used with TAiwPocParameterData
*   to identify the operation between AIW PoC Consumer (mainly 
*   Logs app.) and PoC Implementation.
*   (Use EPoCNoOpTypeId and EEndOfPoCOpTypeIdRange only for checking the validity of the id.)
*/
enum TPoCOperationTypeId
    {
    EPoCNoOpTypeId = 0, // Not actual op.type id, use only for checking validity of the ids.
    EPoC1to1MO,
    EPoC1to1MT,
    EPoCCallbackRequestMO,
    EPoCCallbackRequestMT,
    EPoCAdhocDialoutGroupMO,
    EPoCAdhocDialoutGroupMT,
    EPoCPredefDialoutGroupMO,
    EPoCPredefDialoutGroupMT,
    EPoCDialinGroupMO,
    EEndOfPoCOpTypeIdRange // Not actual op.type id, use only for checking validity of the ids.
    };

// CLASS DECLARATION

/**
*  Data class used to transfer menu and AIW service command related 
*  information between AIW consumer and provider. Please see more 
*  info from documentation.
*
*  @lib ?library
*  @since Series 60 3.0
*/
class TAiwPocParameterData
    {
    public: // Constructors and destructor

        /**
        * C++ default constructor.
        */
        inline TAiwPocParameterData();

    public: // New functions
        
        /**
        * Returns the version of data class.
        * @since Series 60 3.0
        * @return version
        */
        inline TInt Version() const;

    private:// Data

        // Version of the data class
        TInt iVersion;

    public: // Data

        // Consumer UID
        TUid iConsumerAppUid;
        // Consumer Window Group ID
        TInt iConsumerWindowGroup;
        // Menu items preferred by consumer-application. 
        // TAiwPoCMenuCommandItems should be used.
        TInt iPreferredMenu;
        // Command ID for service command operations
        TInt iCommandId;
        // Unique Log db id (used mainly by Logs app.)
        TLogId iLogId;
        // PoC operation type (used mainly by Logs app.)
        TPoCOperationTypeId iLogOperation;
    };

// To package the TAiwPocParameterData to TPckgBuf to be able to use it
// through AIW consumer and provider API 
typedef TPckgBuf<TAiwPocParameterData> TAiwPocParameterDataPckg;


// DATA TYPES

/*
* enum TAiwPoCLaunchView
*
*   Defines the view to be launched in PoC-application. Used with 
*   AIW Generic Param EGenericParamPoCLaunchView through AIW's
*   HandleServiceCmdL (not for HandleMenuCmdL).
*
*   Please see documentation for more info.
*
*   EPoCCurrentView
*
*           If PoC-application is running background, then this should
*           bring the PoC-application in foreground without changing 
*           the view. In case PoC-application is not running, then this
*           should start the PoC-application.
*
*   EPoCMainView 
*
*           This should launch the view which is considered as main 
*           view of the PoC-application. Can for example be the view 
*           which is shown when PoC-application is launched manually.
*
*   EPoCNCNListMissedPoCCallView
*
*           This should be used only by the NCN List, when it is launching
*           a view if user chooses to see "Missed PoC Calls".
*
*   EPoCNCNListNewPoCInvitationView
*
*           This should be used only by the NCN List, when it is launching
*           a view if user chooses to see "New PoC Invitation".
*  
*/
enum TAiwPoCViews
    {
    EAiwPoCCurrentView = 0,
    EAiwPoCMainView,

    // View definitions used only by the New Contacts Note
    EAiwPoCNCNListMissedPoCCallView = 200,
    EAiwPoCNCNListNewPoCInvitationView
    };

// Inline methods
#include <AiwPoCParameters.inl>

#endif      // AIWPOCPARAMETERS_H   
            
// End of File
