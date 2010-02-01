// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef __TALARM_H
#define __TALARM_H

#include <asshdalarm.h>

/**
Copy of TASShdAlarmFlags from asshdalarm_internal.h as this enum is no longer exported but is needed by this test code.
*/
enum TASShdAlarmFlags
    {
    EASShdAlarmFlagsHasAssociatedData   = 0,
    EASShdAlarmFlagsHasOwningSession    = 1,
    EASShdAlarmFlagsHasBecomeOrphaned   = 2,
    /*
     * Set if alarm is disabled manually so that can not be enabled when
     * locale changes.
     */
    EASShdAlarmFlagsPermanentDisabled   = 4
    };

/**
TASShdAlarm derivate for accessing iFlags member.
*/
class TTAlarm : public TASShdAlarm
	{
public:
	void SetHasAssociatedData(const TBool aHasData)
		{
		if(aHasData) 
			{
			iFlags.Set(EASShdAlarmFlagsHasAssociatedData);
			}
		else 
			{
			iFlags.Clear(EASShdAlarmFlagsHasAssociatedData);
			}
		}
	};

#endif // __TALARM_H
