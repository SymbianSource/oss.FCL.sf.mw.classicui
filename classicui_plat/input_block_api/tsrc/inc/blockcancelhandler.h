/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test AknInputBlock.h
*
*/



#ifndef C_BLOCKCANCELHANDLER_H
#define C_BLOCKCANCELHANDLER_H

/*
 *INCLUDES
 */
#include <akninputblock.h>
#include <e32def.h>

/*
 * The class CBlockCancelHandler is inherit from MAknInputBlockCancelHandler,
 * this class is used for test function's parameter
 */
class CBlockCancelHandler : public CBase, public MAknInputBlockCancelHandler
{
public:
    /*
     * Construction
     */
	CBlockCancelHandler();
	/*
	 * Destruction
	 */
	virtual ~CBlockCancelHandler();
	/*
	 * This function is rewrited to implement pure virtual function
	 */
	virtual void AknInputBlockCancel();
	/*
	 * This function is return the value of flag
	 */
	TBool Getflag();
	/*
	 * This function is used to set the value of flag
	 */
	void Setfalg( TBool aFlag );
private:
    /*
     * This is a flag for justice test function if correct;
     */
    TBool iFlag;
};

#endif /*MBLOCKCANCELHANDLER_H_*/

// End of File
