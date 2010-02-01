/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*     A private interface for controlling the behaviour of edwin's drawing
*
*
*/


#ifndef __AKNEDWINDRAWINGMODIFIER_H__
#define __AKNEDWINDRAWINGMODIFIER_H__

#include <e32base.h>
#include <coemop.h>
#include <babitflags.h>

class CAknEdwinDrawingModifier : public CBase
	{
public: 
// Type UID
DECLARE_TYPE_ID(0x101FE529) 
private:
    enum TFlagIndex
        {
        EInhibitNotifyNewFormatDrawing = 0
        };
public:
	inline void SetInhibitNotifyNewFormatDrawing( TBool aInhibit );
   	TBool InhibitNotifyNewFormatDrawing() const;
private:
	TBitFlags iFlags;
    };

inline void CAknEdwinDrawingModifier::SetInhibitNotifyNewFormatDrawing( TBool aInhibit )
    { iFlags.Assign( EInhibitNotifyNewFormatDrawing, aInhibit ); }

#endif
