/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiley utility class
*
*/

#ifndef C_SMILEYINFOREADER_H
#define C_SMILEYINFOREADER_H

#include <e32base.h>
#include <e32std.h>

class CSmileyModel;
class CSmileyInfo;
class TResourceReader;

/**
 *  class for reading and interpreting infomation stored in CenRep
 *
 *  @lib ?library
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CSmileyInfoReader ) : public CBase
    {
public:
// constructor
    CSmileyInfoReader( CSmileyModel& aModel );
    
    ~CSmileyInfoReader();
    
// new functions
    void LoadSmileysFromResourceL();

private:    
// new functions
    void ReadCenRepInfoL( TInt& aResourceId, TDes& aResourceFile,
        TDes& aIconFile );
    void ReadSmileyL( CSmileyInfo& aInfo, TResourceReader& aReader );
    
private:
    // not own
    CSmileyModel* iModel;
    };

#endif C_SMILEYINFOREADER_H
