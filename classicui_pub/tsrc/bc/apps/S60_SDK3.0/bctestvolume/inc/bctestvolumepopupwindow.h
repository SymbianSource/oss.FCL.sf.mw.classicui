/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares popup window for application
*
*/









#ifndef C_BCTESTVOLUMEPOPUPWINDOW_H
#define C_BCTESTVOLUMEPOPUPWINDOW_H

//  INCLUDES
#include <aknview.h>

// CLASS DECLARATION
/**
*  Popup window class
*/    
class CBCTestVolumePopUpWindow : public CCoeControl
    { 
    public:  // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CBCTestVolumePopUpWindow();

        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CBCTestVolumePopUpWindow();

    public: // Functions from base classes
        /**
        * From CCoeControl, SetColoe
        * @param aColor, aColor is the color set to.
        */
        void SetColor(TRgb aColor);

    private: // Functions from base classes

        /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw(const TRect& aRect) const;
       
    private:  // Data
        RWindowGroup iMyWindowGroup;
        TRgb iColor;
    };

#endif // C_BCTESTVOLUMEPOPUPWINDOW_H

// End of File
