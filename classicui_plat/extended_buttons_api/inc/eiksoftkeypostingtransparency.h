/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Method to enable softkey transparency for display posting
*
*/


#ifndef EIKSOFTKEYPOSTINGTRANSPARENCY_H
#define EIKSOFTKEYPOSTINGTRANSPARENCY_H

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;

// CLASS DECLARATION

/**
*  Enable or disable transparent soft-key rendering for applications using
*  S60 Posting API.
*
*  @lib eikcoctl.lib
*  @since S60 v5.0
*/
NONSHARABLE_CLASS( EikSoftkeyPostingTransparency )
    {
    public:
        /**
        *  Enable or disable transparent soft-key rendering for applications
        *  using S60 Posting API.
        *
        * Transparency is implemented by drawing transparency data into the
        * alpha channel of the screen buffer. It is designed to be used to
        * draw transparent CBA buttons on top of an image or video feed that
        * is rendered through S60 Posting API. The screen buffer must be in
        * EColor16MA display mode.
        *
        * There is no background for CBA buttons when transparency is enabled.
        *
        * @since S60 v5.0
        * @param aButtonGroupContainer Button container.
        * @param aEnable               ETrue to enable transparency,
        *                              EFalse to disable.
        * @return                      Error code.
        */
        IMPORT_C static TInt MakeTransparent(
            CEikButtonGroupContainer& aButtonGroupContainer,
            TBool aEnable );

    private:

        /**
        * C++ default constructor.
        */
        EikSoftkeyPostingTransparency();

    };

#endif // EIKSOFTKEYPOSTINGTRANSPARENCY_H   
