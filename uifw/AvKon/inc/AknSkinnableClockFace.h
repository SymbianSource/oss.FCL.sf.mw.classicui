/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AVKON skinnable clock face.
*
*/


#ifndef C_AKNSKINNABLECLOCKFACE_H
#define C_AKNSKINNABLECLOCKFACE_H

// INCLUDES
#include <e32base.h>
#include <gdi.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CAknAlphaComposite;
class CFbsBitmapDevice;
//class CFbsBitGc;

// CLASS DECLARATIONS

/**
* Base class for clock faces.
*
* This is an internal class not visible outside the library.
* This class is not intended for derivation outside the library.
*
* @since 2.0
*
* @internal
*/
class CAknSkinnableClockFace : public CBase
    {
    public: // Destructor
        
        /**
        * Destructor.
        */
        virtual inline ~CAknSkinnableClockFace() {};

    public: // New methods

        /**
        * Draws the given time to the given buffer bitmap.
        *
        * @since 2.0
        *
        * @param aBuffer Buffer bitmap to be used for drawing. The bitmap may
        *   contain background graphics.
        *
        * @param aBufferGc Graphics context that can be used to draw to
        *   the buffer bitmap.
        *
        * @param aTime Time to be used for drawing.
        */
        virtual void DrawTimeToBitmapL( TRect& aRect, 
                CBitmapContext& aBufferGc,  TTime& aTime ) =0;
    };

/**
* Concrete drawer class for digital clock face.
*
* This is an internal class not visible outside the library.
* This class is not intended for further derivation.
*
* @since 2.0
*
* @internal
*/
NONSHARABLE_CLASS(CAknSkinnableClockFaceDigital) : public CAknSkinnableClockFace
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CAknSkinnableClockFaceDigital* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CAknSkinnableClockFaceDigital();
    
    public:  // Functions from MAknSkinnableClockFace
        
        /**
        * Draws the given time to the given buffer bitmap.
        *
        * @since 2.0
        *
        * @param aBuffer Buffer bitmap to be used for drawing. The bitmap may
        *   contain background graphics.
        *
        * @param aBufferGc Graphics context that can be used to draw to
        *   the buffer bitmap.
        *
        * @param aTime Time to be used for drawing.
        */
        void DrawTimeToBitmapL( TRect& aRect, CBitmapContext& aBufferGc,
             TTime& aTime );

    private: // New functions

        /**
        * Blends a single digit into the buffer bitmap.
        *
        * @param aBuffer Buffer bitmap to be used as destination.
        *
        * @param aPos Position of the top left corner of the digit.
        * 
        * @param aDigit Digit as an integer between 0 and 9 (inclusive).
        */
        void BlendDigitL(  CBitmapContext& aBufferGc,
            const TRect& aRect, const TInt aDigit, const TBool aHardMask );

    private:

        /**
        * C++ default constructor.
        */
        CAknSkinnableClockFaceDigital();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data

    };

/**
* Concrete drawer class for analog clock face.
*
* This is an internal class not visible outside the library.
* This class is not intended for further derivation.
*
* @since 2.0
*
* @internal
*/
NONSHARABLE_CLASS(CAknSkinnableClockFaceAnalogue) : public CAknSkinnableClockFace
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CAknSkinnableClockFaceAnalogue* NewL( const TBool aShowDate );
        
        /**
        * Destructor.
        */
        virtual ~CAknSkinnableClockFaceAnalogue();
    
    public:  // Functions from MAknSkinnableClockFace
        
        /**
        * Draws the given time to the given buffer bitmap.
        *
        * @since 2.0
        *
        * @param aBuffer Buffer bitmap to be used for drawing. The bitmap may
        *   contain background graphics.
        *
        * @param aBufferGc Graphics context that can be used to draw to
        *   the buffer bitmap.
        *
        * @param aTime Time to be used for drawing.
        */
        void DrawTimeToBitmapL( TRect& aRect, CBitmapContext& aBufferGc,
             TTime& aTime );

    private: // New functions

        /**
        * Draws the hands of the clock.
        *
        * @param aBufferGc Graphics context that can be used to draw to the
        *   buffer bitmap.
        *
        * @param aBufferRect Rectangle defining the size of the buffer.
        *
        * @param aDateTime Time to be used for drawing.
        */
        void DrawHands( CBitmapContext& aBufferGc, const TRect& aBufferRect, 
            const TDateTime& aDateTime );

    private:

        /**
        * C++ default constructor.
        */
        CAknSkinnableClockFaceAnalogue( const TBool aShowDate );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data

        TBool iShowDate;
    };

#endif      // C_AKNSKINNABLECLOCKFACE_H
            
// End of File
