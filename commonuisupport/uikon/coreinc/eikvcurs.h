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
// class TEikVirtualCursor
// 
//

#ifndef __EIKVCURS_H__
#define __EIKVCURS_H__

#include <e32std.h>
#include <coemain.h>


/** Provides support for the virtual cursor's state within an application.

There is one instance of this object per CEikonEnv. 

@publishedAll
@released */
class TEikVirtualCursor
	{
public:
	/** Specifies the virtual cursor's state. 

	The state may be on, off or suspended. The suspended state is for use by applications 
	that wish to temporarily disable the cursor, but do not want to switch it 
	off completely. For example, an editor control which when focused needs to 
	capture arrow keys would disable the virtual cursor when it gains focus, 
	and enable it when unfocused. */
	enum TState
		{
		/** Sets the virtual cursor off. */
		EOff=0,
		/** Sets the virtual cursor on. */
		EOn,
		/** Sets the virtual cursor as suspended. */
		ESuspended
		};
public:
	TEikVirtualCursor();
private: //prevent passing by value
	inline TEikVirtualCursor(const TEikVirtualCursor&);
public:
	IMPORT_C void SetCursorStateL(TState aState, CCoeEnv& aEnv);
	IMPORT_C TState CursorState(CCoeEnv& aEnv);
public: // but not exported
	void HandleAppToForeground(CCoeEnv& aEnv);
private:
	void SwitchOffEmulationAndBitmap(CCoeEnv& aEnv);
	void SwitchOnEmulationAndBitmap(CCoeEnv& aEnv);
private:
	TState iState;
	};


// inlines

/** Constructor.

Sets the cursor's state to ESuspended so that the call to switch off the virtual 
cursor will succeed when the application starts. Required due to the efficient 
implementation of SetCursorState(). */
inline TEikVirtualCursor::TEikVirtualCursor(const TEikVirtualCursor&)
	{}

#endif
