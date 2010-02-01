/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __MY_MENU_PANE__
#define __MY_MENU_PANE__


class CMyMenuPane:public CEikMenuPane
    {
public:
    CMyMenuPane( MEikMenuObserver* aMenuObserver):CEikMenuPane(aMenuObserver){};
    ~CMyMenuPane(){};
    void ConstructFromResourceL(TResourceReader& r)
        {
        CreateWindowL(iEikonEnv->RootWin());
        CEikMenuPane::ConstructFromResourceL(r);
        };
    };

#endif      // __MY_MENU_PANE__
            
// End of File
