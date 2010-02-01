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
* Description:  
*
*/


#include <AknControl.h> // CAknControl
#include <coecobs.h>    // MCoeControlObserver
#include <aknbutton.h>	// CAknButton
#include <aknEditStateIndicator.h> // TAknEditingState

class CAknKeypad;

NONSHARABLE_CLASS( CAknKeypadButton ) : public CAknButton
    {
    public:
  
        static CAknKeypadButton* NewL( const TDesC& aText, const TInt aScanCode, CAknKeypad* aKeypad );
        virtual ~CAknKeypadButton();
                                          
    public: // Functions from base class

        /**
         * Handles pointer events.
         *
         * @param aPointerEvent The pointer event.
         */
        void HandlePointerEventL( const TPointerEvent& aPointerEvent );

        void Draw( const TRect& /*aRect*/ ) const;
        
    public:
    
   		void SetUpperAndLowerTextL( const TDesC& aUpperText, const TDesC& aLowerText );
          

    protected: // Constructors
 
        CAknKeypadButton( const TInt aFlags, const TInt aScanCode, CAknKeypad* aKeypad );
        
        /**
         * Symbian 2nd phase constructor.
         */
        void ConstructL(const TDesC& aText);
        
    private:
		 void DrawText(  CWindowGc& aGc, const TDesC& aText, TAknTextComponentLayout& aLayout, TInt aMargin ) const;

    private:
    	TInt iScanCode;
    	HBufC* iUpperText;
    	HBufC* iLowerText;
    	CAknKeypad* iKeypad;
 	};



/**
 *  Class that contains avkon keypad
 *
 *  @lib avkon.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknKeypad ) : public CAknControl
    {
public:
    /**
     * NewL
     * @param aParent the parent of this control
     * @return instance of this class
     */
    static CAknKeypad* NewL( CCoeControl& aParent, TInt aQueryType );
      
    /**
     * Destructor
     */
    ~CAknKeypad();

protected: // from CCoeControl
    /**
     * This is called when the size of this control is changed. Here the buttons
     * are layouted. 
     */
    void SizeChanged();

public:

	void SetState(TAknEditingState aState);
	TAknEditingState State();
	TInt QueryType();

    
private:
    /**
     * Constructor
     */
    CAknKeypad();

    /**
     * 2nd phase constructor
     */
    void ConstructL( CCoeControl& aParent, TInt aQueryType );
        
private: // data

	TAknEditingState iState;
	TInt iQueryType;
    };

