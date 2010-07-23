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
* Description:  
*
*/


#ifndef __LAFPUBLC_H__
#define __LAFPUBLC_H__

#include <e32std.h>

/** @deprecated */
const TInt KLafScrollBarButtonPositionMask = 0x00C0;

/** @deprecated */
struct SLafScrollButton
	{
	enum TType
		{
		ENudgeLeft,
		ENudgeUp,
		ENudgeRight,
		ENudgeDown,
		EPageLeft,
		EPageUp,
		EPageRight,
		EPageDown,
		EHome,
		ETop,
		EEnd,
		EBottom
		};
	};

struct SLafScrollBar
	{
    /** 
     * Scroll bar initialisation flags. The default is for the scroll bar
     * to have both a shaft and a thumb. 
     */	
	enum TEikScrollBarFlags
		{
    	/** Default */	
		EEikScrollBarDefaultBehaviour	=0x0000,
    	/** Does not display nudge buttons.*/	
		EEikScrollBarNoNudgeButtons		=0x0001,
    	/** Has buttons which move it a page at a time. */	
		EEikScrollBarHasPageButtons		=0x0002,
    	/** Has buttons which move it its entire extent. */	
		EEikScrollBarHasHomeEndButtons  =0x0004,
    	/** Central area is empty. */	
		EEikScrollBarNoShaftOrThumb 	=0x0008,
    	/** Central area has no scroll thumb. */	
		EEikScrollBarShaftButNoThumb 	=0x0010,
    	/** Buttons are placed at the start of the bar. */	
		EButtonsAtStartOfShaft  		=0x0040,
    	/** Buttons are placed at the end of the bar. */	
		EButtonsAtEndOfShaft 			=0x0080,
    	/** 
    	 * Buttons are placed at either end of the bar @c
    	 * (EButtonsAtStartOfShaft | @c EButtonsAtEndOfShaft).
    	 */	
		EButtonsEitherSideOfShaft 		=EButtonsAtStartOfShaft|EButtonsAtEndOfShaft,
    	/** 
    	 * Buttons do not automatically dim when scroll bar is at its maximum
    	 * extent.
    	 */	
		ENoAutoDimming					=0x0100
		};

    /** Scroll bar orientation enumerations. */
	enum TOrientation
		{
        /** Scroll bar is oriented vertically. */
		EVertical,
        /** Scroll bar is oriented horizontally. */
		EHorizontal
		};

	};

/** Flags for listboxes */
struct SLafListBox
	{
	/**
    * Listbox construction flags.
    */
    enum TFlags
		{
        /**
         * Construction flag for a list box from which the user can
         * select multiple items.
         */
		EMultipleSelection			= 0x0001,
        /**
         * Construction flag for disabling extended selection. 
         * If this is set the user cannot select multiple items by
         * using @c SHIFT button.
         */
		ENoExtendedSelection		= 0x0002,
        /**
         * Construction flag that sets the list box to match user’s keystrokes 
         * incrementally.
         */
		EIncrementalMatching		= 0x0004,
        /**
         * Construction flag for setting the list box as a pop-out list box. 
         * Pop-out list boxes handle certain keystrokes and events differently.
         */
		EPopout						= 0x0008,
        /**
         * Construction flag that enables the indication of pointer press 
         * inside the view of the list box.
         */
		ELeftDownInViewRect			= 0x0010,
        /**
         * Construction flag for enabling @c CEiklist box item double click 
         * indication.
         */
		EItemDoubleClicked			= 0x0020,
        /**
         * Construction flag for removing the ownership of the supplied list box
         * model from the @c CEikListBox so that the list box model will not be 
         * deleted with the @c CEikListBoxes destruction.
         */
		EKeepModel					= 0x0040,
        /**
         * Construction flag for excluding the scroll bar.
         * If the flag is set the scroll bas is drawn ouside the window that 
         * describes the scroll bars extent.
         */
		EScrollBarSizeExcluded		= 0x0080,
        /**
         * Construction flag for enabling @c CEikListBox change indication.
         */
		EStateChanged				= 0x0100,
        /**
         * Construction flag that indicates that the list box should be created 
         * to its own window.
         */
		ECreateOwnWindow			= 0x0200,
        /**
         * Construction flag for disabling key matching.
         */
        ENoFirstLetterMatching      = 0x0400,
        /**
         * Construction flag for enabling painting of selected items.
         */
		EPaintedSelection			= 0x0800,
        /**
         * Construction flag for enabling S60 style selection of multiple items 
         * from the list box.
         */
		ES60StyleMultiselection     = 0x00010000, //32 bits
        /**
         * Construction flag for enabling S60 style markable items.
         */
		ES60StyleMarkable           = 0x00020000  //32 bits		
		};
    /** List item attributes */
    enum TListItemAttribute
        {
		ECurrent    = 0x0001,		// may be drawn with a frame
		/** Item is emphasized */
		EEmphasized = 0x0002,		// special highlight (not selected)
		/** Item is selected */
		ESelected   = 0x0004,		// usually different than emphasized
		// This last attribute is used to control that one can use only
		// valid attributes above. So do not use it at all.	
		/** Sum of all other attributes. Do not use */
		EMask		= 0x0007
        };
    /** deprecated */
	enum TListItemFlags
		{
        /** deprecated */
		EItemDrawMarkSelection			= 0x0001,
        /** deprecated */
		EItemPaintedSelection			= 0x0002,
        /** deprecated */
		EItemDrawOnlyActiveSelection	= 0x0004
		};
	};

/** Scroll bar thumb orientation enumerations */
struct SLafScrollThumb
	{
	enum TOrientation
		{
		/** Vertical orientation */
		EVertical,
		/** Horizontal orientation */
		EHorizontal
		};
	};

struct SLafScrollBarFrame
	{
	/** Defines the scroll bar’s visibility.*/
	enum TScrollBarVisibility
		{
		/** Scroll bar not visible. */
		EOff,
		/** Scroll bar visible. */
		EOn,
		/** Scroll bar visible if required. */
		EAuto
		};

	/** Defines where the scroll bar is located. */
	enum TScrollBarSide
		{
		/** 
		 *  Scroll bar located at the bottom, or to the right of the scroll bar 
		 *  frame 
		 */
		EBottomOrRight,
		/** 
		 *  Scroll bar located at the top, or to the left of the scroll bar 
		 *  frame 
		 */
		ETopOrLeft
		};

	/** Determines how the scroll bar frame manages scroll bars.*/
    enum TScrollBarManagement
		{
        /** 
         *  The scroll bar frame creates, destroys and recreates, scroll bars
         *  according to the visibility mode. The scroll bar frame also acts as
         *  an intermediary with its owning control so that the scroll bars can
         *  be treated as component controls.
         */
		EComponent,
        /** 
         *  The scroll bar frame creates, destroys and recreates, scroll bars 
         *  according to the visibility mode. In this case, the scroll bars are
         *  not treated as component controls. Instead, the scroll bars are 
         *  geometry managed in windows floating above the control window and
         *  their position is determined in relation to the frame’s position on
         *  the screen.
         */
		EFloating,
        /** 
         *  The scroll bar frame uses the central application scroll bar as held
         *  in the environment. This scroll bar is neither owned by the frame 
         *  nor treated as a component control of the frame’s owner.
         */
		EApplicationScrollBar
		};
	};

/** Control group attributes */
struct SLafControlGroup
	{
	enum TStartCorner
		{
		EFromTopLeft=0x1,
		EFromTopRight=0x2,
		EFromBottomLeft=0x3,
		EFromBottomRight=0x4
		};
	enum TOrientation
		{
		ELayHorizontally=0x10,
		ELayVertically=0x20
		};
	};

/**  Look of button group container */
struct SLafButtonGroupContainer
	{
	/** The controls where the button group container is used. */
	enum TUse
		{
		/** View */
		EView,
		/** Dialog */
		EDialog,
		/** Toolbar */
		EToolbar,
		/** Command button area */
		ECba,
		/** Dialog buttons */
		EDialogButtons
		};
    /** Orientation of the button group container */
	enum TOrientation
		{
		/** Vertical orientation */
		EVertical,
		/** Horizontal orientation */
		EHorizontal
		};
	enum TLocation
		{
		/** Button group container used internally for example in dialog buttons */
		EInternal,
		/** Button group container used externally for example 
		 *  in toolbar or CBA (Command Button Area) 
		 */
		EExternal
		};
	};

struct SLafMenuBar
	{
	enum { ENominalTextLength = 40 };
	};

/** Menu pane highlight type enumerations */
struct SLafMenuPane
	{
	enum THighlightType
		{
		ENoHighlight,
		EDrawHighlight,
		ERemoveHighlight
		};
	};

struct SLafButtonBase
	{
	/** The draw state enumerations of the button. */
	enum TDrawState
		{
		EDrawClear					=0x00,
		EDrawSet					=0x01,
		EDrawIndeterminate			=0x02,
		EDrawClearPressed			=0x10,
		EDrawSetPressed				=0x11,
		EDrawIndeterminatePressed	=0x12
		};
	};


#endif // __LAFPUBLC_H__
