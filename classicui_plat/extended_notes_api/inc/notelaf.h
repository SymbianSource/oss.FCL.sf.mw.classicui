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
*
*/

	
/**
 * Maximum number of lines for notes
 * Ideally should have been taken from layout 
 * compiler but could not extract this info 
 * from any table
 */
const TInt KGNMaxNumLines = 5;
const TInt KPNMaxNumLines = 4;
const TInt KINMaxNumLines = 3;

/**
 * These values are deprecated and should not be used
 * Use values from layout compiler instead
 */

//These two are used by autolock application
const TInt KGeneralNoteLineB[KGNMaxNumLines] = {22,40,58,76,94};
const TInt KNoteWidth = 176;

//This is used by system progress popup
const TInt KProgressNoteLineW[2][KPNMaxNumLines] = {{124,155,155,155}, //NO NUMB TYPE INDIC
													{124,140,155,155}};//NUMB TYPE INDIC

