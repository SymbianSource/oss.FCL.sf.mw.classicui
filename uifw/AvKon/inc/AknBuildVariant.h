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
* Description:  Build variant information (European vs. APAC)
*
*
*/



#ifndef AKNBUILDVARIANT_H
#define AKNBUILDVARIANT_H

//  INCLUDES
#include <e32base.h>
#include "avkon.hrh"

/**
* Returns the build variant.
* @since 2.0
*
* @return EEuropeanVariant or EApacVariant, depending on the build.
*/
GLREF_C EVariantFlag AknBuildVariant();

#endif      // AKNBUILDVARIANT_H
            
// End of File
