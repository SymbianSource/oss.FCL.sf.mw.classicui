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
* Description:  Constant definitions for Slide set dialog.
*
*/


#ifndef PSLNSLIDESETCONST_H
#define PSLNSLIDESETCONST_H

// Image selection: index for Image selection.
const TInt KPslnSlideSetImageSelImageSet = 0;

// Image selection: index for Random
const TInt KPslnSlideSetRandomIndex = 1;

// UID of Personlisation application
const TUid KUidPsln = { 0x10005A32 };

// Feature IDs.
enum 
    {
    // Random slide set selection.
    EPslnSlideSetFeatureRandom,
    // Remove Back Light Setting
    EPslnSlideSetBacklightRemoved,
    
    /*Intert new item here*/
    
    // last feature should be max value
    KPslnMaxFeatureID
    };
  

#endif // PSLNSLIDESETCONST_H
