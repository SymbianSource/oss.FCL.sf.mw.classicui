/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#include "akntransitionutils.h"
// ======== MEMBER FUNCTIONS ========


	
EXPORT_C void AknTransitionUtils::SetAllParents( const CCoeControl* aControl )
	{
	CCoeControl* child = NULL;
	CCoeControl* parent = const_cast<CCoeControl*>( aControl );
		
	TInt compControlCount( 0 );

		compControlCount = parent->CountComponentControls();
		
		for( TInt i( 0 ); i < compControlCount; i++ )
			{
			child = parent->ComponentControl( i );
			child->SetParent( parent );
			SetAllParents( child );				
			}
	}

// --- EOF ---




 
