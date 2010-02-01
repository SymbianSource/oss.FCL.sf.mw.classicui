/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Internal extension class for Avkon query control
*
*/



#ifndef AKNQUERYEXTENSION_H
#define AKNQUERYEXTENSION_H

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CAknQueryControl;
class CAknsFrameBackgroundControlContext;

// CLASS DECLARATION

/**
* Internal extension class for CAknQueryControl and derived classes.
*
* @since 2.6
*
* @internal
*/
NONSHARABLE_CLASS(CAknQueryExtension) : public CBase
    {
    public: // New methods

        enum TVirtualInputStatus
            {
            EVirtualInputCheckedAlready,
            EVirtualInputEnabled
            };
        /**
        * Creates a new editor control context (with QsnFrInput),
        * but does not initialize rectangles.
        *
        * @since 2.6
        */
        void CreateEditorContextL();

        /**
        * Returns the editor context.
        *
        * @since 2.6
        */
        CAknsFrameBackgroundControlContext* EditorContext();

    private: // New methods (only used by CAknQueryControl)

        /**
        * Retrieves the extension instance.
        * This method is only used internally by CAknQueryControl.
        * Generally, @c CAknQueryControl::QueryExtension should be used to 
        * access the instance.
        */
        static CAknQueryExtension* Instance(
            const CAknQueryControl* aQueryControl );

    private: // Construction and destruction (only used by CAknQueryControl)

        /**
        * Creates the extension.
        */
        static void CreateExtensionL(
            const CAknQueryControl* aQueryControl );

        /**
        * Destroyes the extension.
        */
        static void DestroyExtension(
            const CAknQueryControl* aQueryControl );

        /**
        * Static constructor.
        */
        static CAknQueryExtension* NewL();

        /**
        * Destructor.
        */
        virtual ~CAknQueryExtension();

    private: // Data
        CAknsFrameBackgroundControlContext* iEditorContext;
        TBool iAllowEmptyInput;
        TBitFlags iVirtualInputStatusFlags;

    private: // Friend classes
        friend class CAknQueryControl;
        friend class CAknMultilineQueryControl;
    };

#endif      // AKNQUERYEXTENSION_H
            
// End of File
