// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __LAFSPANE_H__
#define __LAFSPANE_H__

#include <e32std.h>

// forward declaration
class CEikStatusPaneBackground;

class LafStatusPaneContainer
/** Status pane LAF support.

@publishedPartner 
@released */
	{
public:
	/** Tests if fading the status pane is allowed.
	
	@return True if fading is allowed.
	@see CEikStatusPane::SetFaded() */
	IMPORT_C static TBool AllowFading();

 	/** Creates a background object for the status pane. The background 
 	object class is derived from the virtual class CEikStatusPaneBackground 
 	
 	@return Pointer to a background object derived from CEikStatusPaneBackground */
	IMPORT_C static CEikStatusPaneBackground* CreateStatusPaneBackgroundL();
	};

#endif // __LAFSPANE_H__
