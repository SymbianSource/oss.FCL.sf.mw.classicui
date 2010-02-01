/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This is a duplicated sound server session class.
*                Duplication is done because the original is private, see
*                s60/mw/classicui/uifw/AvKon/src/aknsoundplayer.cpp.
*
*/

#ifndef R_AKNSOUNDSERVERSESSION_H
#define R_AKNSOUNDSERVERSESSION_H

#include <barsread.h>

class RAknSoundServerSession : public RSessionBase
    {
public:
    TInt Connect();                                                           // Tested
    TBool Init(TInt aUid);                                                    // Tested
    void AddSoundInfoResourceL(TInt aUid, TResourceReader aReader);           // Unable to test with STIF
    void PlaySound(TInt aSid);                                                // Tested
    void StopSound(TInt aSid);                                                // Tested
    void PushContextL(TInt aUid, TResourceReader& aReader, TInt aResourceId); // Unable to test with STIF
    void PopContext();                                                        // Tested
    void BringToForeground();                                                 // Tested
    void KeyPressed(TInt aKey, TBool aRepeat);                                // Tested
    void LockContext();                                                       // Tested
    void ReleaseContext();                                                    // Tested
    TInt ServerRequest(TInt aFunction,const TIpcArgs& aArgs);                 // Tested
    TInt TopContext();                                                        // Tested
private:
    TBool iKeySoundServerExists;
    };
        
#endif
    
// End of file
    