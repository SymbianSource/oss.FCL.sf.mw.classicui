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
* Description:  Changes cba button's label to image. 
*
*/



#ifndef EIKSOFTKEYIMAGE_H
#define EIKSOFTKEYIMAGE_H

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;

// CLASS DECLARATION

/**
*  Changes cba button's label to image. 
*
*  @lib EIKCOCTL
*  @since 2.0
*/
class EikSoftkeyImage
    {
    public:

        /**
        * Set image to cba button by replacing label
        * @since 2.0
        * @param aButtonGroupContainer Button container
        * @param aImage Image to button,
        *               Takes Images ownership
        * @param aLeft  Boolean: left or right button. 
        *                        If true, then change left, 
        *                        if false, change right
        */
        IMPORT_C static void SetImage(CEikButtonGroupContainer* aButtonGroupContainer, CEikImage& aImage, TBool aLeft);

        /**
        * Change to cba button image back to label
        * @since 2.0
        * @param aButtonGroupContainer Button container
        * @param aLeft Boolean: left or right button. 
        *                        If true, then change left, 
        *                        if false, change right
        */
        IMPORT_C static void SetLabel(CEikButtonGroupContainer* aButtonGroupContainer, TBool aLeft);
    
    private:

        /**
        * C++ default constructor.
        */
        EikSoftkeyImage() {};


    };

#endif      // EIKSOFTKEYIMAGE_H   
            
// End of File

