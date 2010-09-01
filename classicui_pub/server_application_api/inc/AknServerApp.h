/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Server applications framework.
 *
 *
*/


#ifndef AKNSERVERAPP_H
#define AKNSERVERAPP_H

#include <eikserverapp.h>

/**
 * Allows a server app client to connect to a new server app, which
 * will be chained from the client app, giving it the appearance
 * of being embedded within the client.
 *
 * Series 60 client-side service IPC implementations should be
 * derived from this class.
 */
class RAknAppServiceBase : public REikAppServiceBase
    {
public:
    /**
    * Launch a new server app instance, which will be chained
    * from the current application.
    * Note, this function can only be used from the context of
    * an application thread, as it depends on the existence of
    * a CEikonEnv object.
    * If you want to launch a chained server app in a situation
    * where a CEikonEnv does not exist, use REikAppServiceBase::ConnectNewChildAppL()
    * instead.
    * @param aAppUid The UID of the server app which you wish to
    * launch.
    */
    IMPORT_C void ConnectChainedAppL(TUid aAppUid);
    /**
    * Close the server app session.
    */
    IMPORT_C void Close();
    };


/**
 * Interface for monitoring the lifetime of a server app.
 * This class adds Series 60 common behavior to the handling
 * of server app exits.
 */
class MAknServerAppExitObserver : public MApaServerAppExitObserver
    {
public: // from MApaServerAppExitObserver
    /**
    * Handle the exit of a connected server app.
    * This implementation provides Series 60 default behavior
    * for handling of the EAknCmdExit exit code. Derived classes
    * should base-call this implementation if they override this
    * function.
    * @param aReason The reason that the server application exited.
    * This will either be an error code, or the command id that caused
    * the server app to exit.
    */
    IMPORT_C virtual void HandleServerAppExit(TInt aReason);
    };


/**
 * Base class for server app service IPC implementations.
 * This class provides notifications of service creation and
 * destruction to the server, to give the server the ability
 * to handle the case where all clients have closed their
 * sessions.
 */
class CAknAppServiceBase : public CApaAppServiceBase
    {
public:
    /**
    * Constructor
    */
    IMPORT_C CAknAppServiceBase();
    /**
    * Destructor
    */
    IMPORT_C ~CAknAppServiceBase();

protected: // from CSession2
    /**
    * Override of CSession2::CreateL().
    * If further overridden, this function must be base-called.
    */
    IMPORT_C void CreateL();
    /**
    * Override of CSession2::ServiceL().
    * If further overridden, this function must be base-called.
    * @param aMessage The client message
    */
    IMPORT_C void ServiceL(const RMessage2& aMessage);
    /**
    * Override of CSession2::ServiceError().
    * If further overridden, this function must be base-called.
    * @param aMessage The client message.
    * @param aError The error code to which occured during message servicing
    */
    IMPORT_C void ServiceError(const RMessage2& aMessage,TInt aError);
    };


/**
 * Base class for server app's servers.
 * Series 60 applications that want to implement services should
 * derive their server class from this.
 * This class already supports the standard Series 60 services,
 * and is instantiated by default if an application is launched
 * as a server app, but does not override CAknApp::NewServerAppL().
 */
class CAknAppServer : public CEikAppServer
    {
public: // from CAknAppServer
    /**
    * Destructor
    */
	IMPORT_C ~CAknAppServer();
    /**
    * Second stage construction.
    * Derived classes may override this to add extra second
    * stage constuction, but they must base-call.
    * @param aFixedServerName the name that this server will have,
    * must be passed through in the base-call.
    */
    IMPORT_C void ConstructL(const TDesC& aFixedServerName);
    /**
    * Create a new service implementation.
    * This implementation creates common Series 60 services.
    * Derived classes can override this to add support for specific
    * services that they support. They must base-call for any
    * service UIDs that they do not support.
    * @param aServiceType the UID of the service that has been requested
    * @return a new service instance of the type requested
    */
    IMPORT_C CApaAppServiceBase* CreateServiceL(TUid aServiceType) const;
public: // new
    /**
    * Allows the server to handle the case when all client sessions
    * have closed.
    * The default implementation provides the Series 60 policy of
    * closing the server application. If this is not appropriate for
    * a server app, it should override this function to provide its
    * own behavior.
    */
    IMPORT_C virtual void HandleAllClientsClosed();
public: // not exported
    void HandleSessionClose();
    void HandleSessionOpen();
private:
    TInt iSessionCount;
    };


#endif

// End of file.
