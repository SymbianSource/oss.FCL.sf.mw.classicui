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
// Header containing the CoeScheduler.

#ifndef COESCHEDULER_H 
#define COESCHEDULER_H 

/** Implements the active scheduler presupposed by the control environment.

@publishedPartner
@deprecated
*/
class CCoeScheduler : public CBaActiveScheduler
	{
public:
	IMPORT_C CCoeScheduler(CCoeEnv* aCoeEnv);
	IMPORT_C virtual void WaitForAnyRequest();
	IMPORT_C virtual void DisplayError(TInt aError) const;
	/** Gets the control environment.
	
	@return A pointer to the control environment. */
	inline CCoeEnv* CoeEnv() {return iCoeEnv;}
	TBool Flush() const; // not to be called from outside CONE
	void SetFlush(TBool aFlush); // not to be called from outside CONE
private:
	// from CBaActiveScheduler
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private:
	CCoeEnv* iCoeEnv;
	TBool iFlush;
	};



#endif /* COESCHEDULER_H */
