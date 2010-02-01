/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKKWIN_H__)
#define __EIKKWIN_H__

#include <AknControl.h>

class CEikKeyWindow : public CAknControl
	{
public:
	enum TType
		{
		EHorizontal,
		EVertical
		};

	IMPORT_C CEikKeyWindow();
	IMPORT_C ~CEikKeyWindow();
	IMPORT_C void ConstructL(const TPoint& aPoint,const TSize& aSize,TInt aDeadSpaceAtStart, TInt aDeadSpaceAtEnd, TInt aScanCode,TInt numButtons,TType aType,RWindowGroup* aParent=NULL);

    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
	};


#endif
