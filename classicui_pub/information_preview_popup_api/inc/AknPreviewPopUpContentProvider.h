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
* Description:  Interface used for asynchronous content building for preview 
*                popup.
*
*/


#ifndef AKNPREVIEWPOPUPCONTENTPROVIDER_H
#define AKNPREVIEWPOPUPCONTENTPROVIDER_H

// CLASS DECLARATION

/**
*  Interface used for asynchronous content building for a preview popup.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
class MAknPreviewPopUpContentProvider
    {
    public: // New functions

        /**
        * Called by the preview popup controller when content building should be
        * started.
        */
        virtual void StartContentBuildingL() = 0;
        
        /**
        * Called by the preview popup controller if ongoing content building
        * operation should be cancelled.
        */
        virtual void CancelContentBuilding() = 0;
    };

#endif // AKNPREVIEWPOPUPCONTENTPROVIDER_H

//  End of File  
