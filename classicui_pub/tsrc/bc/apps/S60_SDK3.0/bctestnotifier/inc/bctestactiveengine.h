/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares main application class.
*
*/









#ifndef C_BCTEST_ACTIVE_ENGINE_H
#define C_BCTEST_ACTIVE_ENGINE_H

// INCLUDES
#include <e32base.h>
#include <aknglobalnote.h>

// CLASS DECLARATION

/**
* CBCTestActiveEngine application class.
* Provides factory to create concrete document object.
*/
class CBCTestActiveEngine : public CActive
    {
    public: 
		CBCTestActiveEngine();
		virtual ~CBCTestActiveEngine();

	public:
		TRequestStatus* GetStatus();
		TBool Active();
		void MakeActive();


	protected: // From CActive
		void RunL();
		void DoCancel();
    };

class CWaitGlobalNote : public CActive
    {
    public: 
        static CWaitGlobalNote* NewL();
    	CWaitGlobalNote();
		virtual ~CWaitGlobalNote();

	public:
		void ShowGlobalNoteAsyncL();

	protected:
		void RunL();
		void DoCancel();
        void ConstructL();
    private:
        TInt noteId;
        CAknGlobalNote* iNote;		
    };
#endif

// End of File
