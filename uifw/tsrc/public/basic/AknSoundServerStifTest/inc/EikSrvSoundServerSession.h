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
*                s60/mw/classicui/uifw/AvKon/animdllinc/AknAnimKeySound.h.
*
*/

#ifndef R_EIKSRVSOUNDSERVERSESSION_H
#define R_EIKSRVSOUNDSERVERSESSION_H

/**
 * Sound server session.
 */
class REikSrvSoundServerSession : public RSessionBase
    {
public: // New functions
    /**
    * Connects to sound server.
    * @return error code.
    */
    TInt Connect();

    /**
    * Informs sound server of key press.
    * @param aKey key pressed.
    * @param aRepeat ETrue if repeat, EFalse otherwise.
    * Asynch
    */
    void KeyPressed( TInt aKey, TRequestStatus& aStatus, TBool aRepeat = EFalse );
    
    /**
    * This method has been added for testing purposes and is not included in AknAnimKeySound.h!
    */
    void Init( TInt aUid );
    };
    
#endif
    
// End of file
    