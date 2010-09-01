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
* Description: 
*   Implementation of the query control for multiline queries
*
*/


  
#ifndef __AKN_MULTILINE_QUERY_CONTROL_H
#define __AKN_MULTILINE_QUERY_CONTROL_H 

//  INCLUDES
#include <coecntrl.h>
#include <aknQueryControl.h>

enum TLinePosition  
    {   
    EFirstLine = 0, 
    ESecondLine 
    };  

class TAknWindowLineLayout;

/**
 * Multiline query control class.
 */
class CAknMultilineQueryControl : public CAknQueryControl 
    {
    public: // Constructors and destructor
        /**
         * C++ Constructor.
         */
        IMPORT_C CAknMultilineQueryControl();

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknMultilineQueryControl();

    public://new API functions
        /**
        * Set number of prompt lines to controls. 
        * This have to call before setting sizs of the components
        *
        * @param aNbrOfPromptLinesFirstLine     Numbers of lines in first prompt text
        * @param aNbrOfPromptLinesSecondLine    Numbers of lines in Second prompt text
        */
        IMPORT_C void SetNbrOfPromptLines(TInt aNbrOfPromptLinesFirstLine, TInt aNbrOfPromptLinesSecondLine);
    
        /**
         * Return true if control is the first query in the dialog
         */
        IMPORT_C TBool IsFirst() const;

        /**
         * Return true if control is the second query in the dialog
         */
        IMPORT_C TBool IsSecond() const;

    public: //Functions from CAknQueryControl

        /**
        * Get pointer to query controls control (editor)
        *
        * @param aLayout    Controls layout (for multiline queries use
        *                   EMultiDataFirstEdwin, EMultiDataSecondEdwin...)
        * @return           Pointer to control, NULL if not found 
        */
        IMPORT_C virtual CCoeControl* ControlByLayoutOrNull(TInt aLayout);

    public: // Functions from CCoeControl

        /**
        * From CCoeControl  Give the control a mimimum size. 
        * 
        * @return           The minimum size required by the control.
        */
        IMPORT_C TSize MinimumSize();

        /**
        * From CCoeControl.     
        * Handles pointer events
        * @param aPointerEvent     The pointer event.
        */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    	
	    
	    IMPORT_C void HandleResourceChange(TInt aType); 

    public:
        /**
         * LAF indexing 
         *
         * Manage indexes into LAF tables
         */
        class TIndex 
        {   
        public: 
            TIndex(const TLinePosition& aLinePos, TInt aFirstQueryPromptLines,TInt aSecondQueryPromptLines);
        
        public: 
            TInt MainPanePQDCWindow() const;    
            TInt CDCQPWindowLine1() const;  
            TInt CDCQPWindowLine2() const;  
            TInt CDCQPWindowLine3() const;  
            TInt CDCQPWindowRectangles() const; 
            TInt CDCQPWindowLine5() const;  

            TInt CDCQPWindowTextsLine1(TInt aLineNum) const;
            TInt CDCQPWindowTextsLine2() const; 
            TInt CDCQPWindowTextsLine3(TInt aLineNum) const;
            TInt CDCQPWindowTextsLine4() const; 

            TInt CDCPQWindowGraphicsLine5() const;  

        public:
            const TInt LinePos() const { return iLinePos; }
        
        private:    
            TInt FirstQueryPromptLines() const;
            TInt SecondQueryPromptLines() const;

            void SelfTest() const;
    
        private:
            TLinePosition  iLinePos;    
            TInt           iFirstQueryPromptLines;  
            TInt           iSecondQueryPromptLines;
        };
        
    protected: // From CAknQueryControl
        /**
        * Set line widths for query prompt
        */
        void SetLineWidthsL();

        /**
        * Read the query data from resource file
        */
        void ConstructQueryL(TResourceReader& aRes);

        /**
         * Layout rectangle (shift up and left by margins)
         */
        TRect LayoutRect();

    private://From CCoeControl
        void SizeChanged();
        void Draw(const TRect& aRect) const;
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:    //Layout methods
        void LayoutPrompt(const TLayoutMethod& aLayoutM);
        void LayoutSeparator(const TLayoutMethod& aLayoutM);
        
        void LayoutEditor(const TLayoutMethod& aLayoutM);
        void LayoutEditorFrame(const TLayoutMethod& aLayoutM);
        void LayoutEditorIndicator(const TLayoutMethod& aLayoutM);

        /**
        * Return window layout depending on Layout 
        * Window layout is done by the dialog
        */
        void WindowLayout( TAknWindowLineLayout& aLayout ) const;

    private: //Implementation methods
        void   SetLinePosition();
        TInt16 FirstLineHeight() const;
        TInt16 SecondLineHeight() const;

    private:
        TAknLayoutRect iLayoutLineBetweenEntryFields; /// Layout rect for line between two entry fields
        TLinePosition  iLinePos;    
        TInt           iFirstQueryPromptLines;  
        TInt           iSecondQueryPromptLines; 
    };



/**
 * Derived Multiline query control class.
 * 
 * @since 2.1
 */
 class CAknExtMultilineQueryControl : public CAknExtQueryControl
    {
    public: // Constructors and destructor
        /**
         * C++ Constructor.
         */
        IMPORT_C CAknExtMultilineQueryControl();

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknExtMultilineQueryControl();

    public://new API functions
        /**
        * Set number of prompt lines to controls. 
        * This have to call before setting sizs of the components
        *
        * @param aNbrOfPromptLinesFirstLine     Numbers of lines in first prompt text
        * @param aNbrOfPromptLinesSecondLine    Numbers of lines in Second prompt text
        */
        IMPORT_C void SetNbrOfPromptLines(TInt aNbrOfPromptLinesFirstLine, TInt aNbrOfPromptLinesSecondLine);
    
        /**
         * Return true if control is the first query in the dialog
         */
        IMPORT_C TBool IsFirst() const;

        /**
         * Return true if control is the second query in the dialog
         */
        IMPORT_C TBool IsSecond() const;

    public: //Functions from CAknQueryControl

        /**
        * Get pointer to query controls control (editor)
        *
        * @param aLayout    Controls layout (for multiline queries use
        *                   EMultiDataFirstIpEd, EMultiDataSecondIpEd...)
        * @return           Pointer to control, NULL if not found 
        */
        IMPORT_C virtual CCoeControl* ControlByLayoutOrNull(TInt aLayout);

    public: // Functions from CCoeControl

        /**
        * From CCoeControl  Give the control a mimimum size. 
        * 
        * @return           The minimum size required by the control.
        */
        IMPORT_C TSize MinimumSize();

        /**
        * From CCoeControl.     
        * Handles pointer events
        * @param aPointerEvent     The pointer event.
        */
	    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	    
	    IMPORT_C void HandleResourceChange(TInt aType);   

    public:
        /**
         * LAF indexing 
         *
         * Manage indexes into LAF tables
         */
        class TIndex 
        {   
        public: 
            TIndex(const TLinePosition& aLinePos, TInt aFirstQueryPromptLines,TInt aSecondQueryPromptLines);
        
        public: 
            TInt MainPanePQDCWindow() const;    
            TInt CDCQPWindowLine1() const;  
            TInt CDCQPWindowLine2() const;  
            TInt CDCQPWindowLine3() const;  
            TInt CDCQPWindowRectangles() const; 
            TInt CDCQPWindowLine5() const;  

            TInt CDCQPWindowTextsLine1(TInt aLineNum) const;
            TInt CDCQPWindowTextsLine2() const; 
            TInt CDCQPWindowTextsLine3(TInt aLineNum) const;
            TInt CDCQPWindowTextsLine4() const; 

            TInt CDCPQWindowGraphicsLine5() const;  

        public:
            const TInt LinePos() const { return iLinePos; }
        
        private:    
            TInt FirstQueryPromptLines() const;
            TInt SecondQueryPromptLines() const;

            void SelfTest() const;
    
        private:
            TLinePosition  iLinePos;    
            TInt           iFirstQueryPromptLines;  
            TInt           iSecondQueryPromptLines;
        };
        
    protected: // From CAknQueryControl
        /**
        * Set line widths for query prompt
        */
        void SetLineWidthsL();

        /**
        * Read the query data from resource file
        */
        void ConstructQueryL(TResourceReader& aRes);

        /**
         * Layout rectangle (shift up and left by margins)
         */
        TRect LayoutRect();

    private://From CCoeControl
        void SizeChanged();
        void Draw(const TRect& aRect) const;
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:    //Layout methods
        void LayoutPrompt(const TLayoutMethod& aLayoutM);
        void LayoutSeparator(const TLayoutMethod& aLayoutM);
        
        void LayoutEditor(const TLayoutMethod& aLayoutM);
        void LayoutEditorFrame(const TLayoutMethod& aLayoutM);
        void LayoutEditorIndicator(const TLayoutMethod& aLayoutM);

        /**
        * Return window layout depending on Layout 
        * Window layout is done by the dialog
        */
        void WindowLayout( TAknWindowLineLayout& aLayout ) const;

    private: //Implementation methods
        void   SetLinePosition();
        TInt16 FirstLineHeight() const;
		TInt16 SecondLineHeight() const;
    private:
        TAknLayoutRect iLayoutLineBetweenEntryFields; /// Layout rect for line between two entry fields
        TLinePosition  iLinePos;    
        TInt           iFirstQueryPromptLines;  
        TInt           iSecondQueryPromptLines;
        TAny*          iSpare_1;


    };

#endif 
