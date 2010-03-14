/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:         Interface of project pen input plugin utils
*
*/









#ifndef C_CHINESE_FIND_COMMON_H
#define C_CHINESE_FIND_COMMON_H

// INCLUDES
#include <w32std.h>
#include <e32base.h>
#include <cenrepnotifyhandler.h>

// FORWARD DECLARATION
class CRepository;


class CFindRepositoryWatcher : public CBase, public MCenRepNotifyHandlerCallback
    {
public:
    static CFindRepositoryWatcher* NewL(
        const TUid aUid,
        const TUint32 aKey,
        CCenRepNotifyHandler::TCenRepKeyType aKeyType,
        TCallBack aCallBack,
        CRepository* aRepository);

     static CFindRepositoryWatcher* NewL(
        const TUid aUid,
        TCallBack aCallBack,
        CRepository* aRepository);

     ~CFindRepositoryWatcher();

     TUint32 ChangedKey();

public: // from MCenRepNotifyHandlerCallback
     void HandleNotifyInt    (TUint32 aKey, TInt aNewValue);
     void HandleNotifyError  (TUint32 aKey, TInt aError, CCenRepNotifyHandler* aHandler);
	 void HandleNotifyGeneric(TUint32 aId);    

private:
    CFindRepositoryWatcher(
        const TUid aUid,
        const TUint32 aKey,
        TCallBack aCallBack,
        CRepository* aRepository);

    void ConstructL(CCenRepNotifyHandler::TCenRepKeyType aKeyType);

    void ConstructL();

private:
    TUid                    iUid;
    TUint32                 iKey;
    TUint32                 iChangedKey;
    TCallBack               iCallBack;
    CRepository*            iRepository;
    CCenRepNotifyHandler*   iNotifyHandler;

    }; 

#endif // C_CHINESE_FIND_COMMON_H

// End Of File
