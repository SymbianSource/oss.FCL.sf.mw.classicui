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
* Description:  Notifier app server definition.
*
*/

#ifndef __AKNNOTIFIERAPPSERVER_H__
#define __AKNNOTIFIERAPPSERVER_H__

#include <e32std.h>
#include <e32cmn.h>
#include <eiknotapi.h>
#include <badesca.h> 
#include <AknServerApp.h>
#include "AknNotifierAppServer.h"

class MNotifLibraryOwningServer
    {
public:    
    virtual MEikSrvNotifierBase2* FindImplementation(TUid aUid) const = 0;
    virtual void UnbalanceReferenceCount(TUid aUid, TBool aAddCount) = 0;
    virtual void NotifierExtension(TUid aExtensionUid, TAny*& aGenParam) = 0;
    };

class CNotifierNames;

class CAknNotifierAppServer: public CAknAppServer, public MEikSrvNotifierManager
    {                   
public:
    IMPORT_C ~CAknNotifierAppServer();
    IMPORT_C CAknNotifierAppServer();       

public: // from MEikSrvNotifierManager
    IMPORT_C void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
    IMPORT_C void CancelNotifier(TUid aNotifierUid);
    IMPORT_C void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);

public: // new methods 
    IMPORT_C virtual void StartNotifierAndGetResponseL(
        TUid aNotifierUid, 
        TDesC8& aBuffer, 
        const RMessagePtr2& aMsg, 
        TInt aReplySlot);
        
    // Appends given name to list of notifier libraries
    // It is ok to give full path for this method, RLibrary::Load() ignores paths anyway 
    // when plat sec is turned on.
    IMPORT_C void AppendNotifierLibNameL(const TDesC& aLibraryName);
    
    // Loads notifier libraries which were given using AppendNotifierLibNameL 
    IMPORT_C void LoadNotifiersL();
    
public:  // from CEikAppServer
    IMPORT_C CApaAppServiceBase* CreateServiceL(TUid aServiceType) const;

public: // New since 3.1
    IMPORT_C void SetImplementationFinderL(MNotifLibraryOwningServer* aFinder);
    IMPORT_C void UnbalanceReferenceCountForNotif(TUid aUid, TBool aAddCount);
    
public: // Since 3.2
    IMPORT_C void UpdateNotifierAndGetResponseL(
        TUid aNotifierUid, 
        TDesC8& aBuffer, 
        const RMessagePtr2& aMsg, 
        TInt aReplySlot);
    
private:                
    MEikSrvNotifierBase2* FindImplementation(TUid aUid) const;
    
    CArrayPtr<MEikSrvNotifierBase2>* CreateImplementationsL(
        const TDesC& aLibName, 
        const TUidType& aUidType);
                    
private:            
    RArray<RLibrary>                    iLibraries;
    RPointerArray<MEikSrvNotifierBase2> iNotifierArray;
    
    CNotifierNames*                     iNotifierNames;
    };
    
#endif  // __AKNNOTIFIERAPPSERVER_H__

// End of file
