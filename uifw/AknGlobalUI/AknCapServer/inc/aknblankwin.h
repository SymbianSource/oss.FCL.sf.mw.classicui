/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKN_BLANK_WIN__
#define __AKN_BLANK_WIN__

#include <aknclearer.h>
#include <eiksrvsp.h>

//
// CAknServBlankWin
//
// Normally, CAknAppUi is the status pane observer. But since there is no CAknAppUi here,
// CAknServBlankWin can be the status pane observer.
class CAknServBlankWin : public CAknScreenClearerBase, MEikStatusPaneObserver
    {
public:
    ~CAknServBlankWin();
    static CAknServBlankWin* NewL(RWindowGroup& aParent, CEikServStatusPane* aSp);
    void SetLayoutBlank(TBool aLayoutBlank);
private:
    CAknServBlankWin(CEikServStatusPane* aSp);
    void HandleStatusPaneSizeChange();
private:
    CEikServStatusPane* iSp;
    TBool iLayoutBlank;
    };
    
#endif // __AKN_BLANK_WIN__
