/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

#ifndef __AKNNFYSRVUI__
#define __AKNNFYSRVUI__

#include <AknNotifierWrapperDefs.h>
#include <AknNotiferAppServerApplication.h> // link against AknNotifierWrapper.lib
#include <AknNotifierAppServer.h>
#include <AknNotifierControllerPlugin.h>

#include "AknCapServerDefs.h"

//----------------------------------
// Application
//----------------------------------
class CAknNfySrvApplication : public CAknNotifierAppServerApplication
    {
public:
    CAknNfySrvApplication();
    void NewAppServerL(CApaAppServer*& aAppServer);
    CApaDocument* CreateDocumentL();
    TUid AppDllUid() const 
        {
        return KCommonNotifierAppSrvUid;    
        }
    TFileName ResourceFileName() const
        {
        return KNullDesC();            
        }
    };

//----------------------------------
// Document
//----------------------------------
class CAknNfySrvDocument : public CAknDocument
    {
public:
    CAknNfySrvDocument(CEikApplication& aApp):CAknDocument(aApp){};
private: // from CAknDocument
    CEikAppUi* CreateAppUiL();
    };


//----------------------------------
// AppUi
//----------------------------------
class CAknNfySrvAppUi: public CAknNotifierAppServerAppUi
    {
public:
    CAknNfySrvAppUi();
    ~CAknNfySrvAppUi();

public: // from CAknNotifierAppServerAppUi
    void ConstructL();

private: // from CCoeAppUi
    TBool FrameworkCallsRendezvous() const;
    };

#endif // __AKNNFYSRVUI__

// End of file
