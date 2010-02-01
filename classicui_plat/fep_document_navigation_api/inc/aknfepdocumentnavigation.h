/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface to document that FEP navigates
*
*/


#ifndef M_AKNFEPDOCUMENTNAVIGATION_H
#define M_AKNFEPDOCUMENTNAVIGATION_H

#include <e32std.h>
#include <tagma.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <tagmalayoutandsource.h>
#endif
#include <coemop.h>

/**
 * Interface for document navigation.
 * FEP uses this interface to navigate through the 
 * edited text.
 *
 * @since S60 3.2
 */
class MAknFepDocumentNavigation
    {
public:
	DECLARE_TYPE_ID(0x10283502)
	
    /**
     * Get the current position in the document.
     * 
     * @param aPos Holds the postion information on return.
     */
    virtual void GetDocPos( TTmDocPos& aPos ) const = 0; 
    
    /**
     * Moves to a new document position. The view is scrolled so
     * that the line containing the new cursor position is at the top, or the 
     * bottom, if the scroll direction was downwards.
     * 
     * @param aDocPos The new document position.
     * @param aDragSelectOn ETrue if the region between the old and new
     *                      positions should be selected, EFalse if not. If ETrue, 
     *                      any existing selection remains selected, so that this 
     *                      function can be used to extend or shorten a selected 
     *                      region. EFalse cancels any existing selection.
     */
    virtual void SetDocPosL( const TTmDocPosSpec& aDocPos, 
                               TBool aDragSelectOn = EFalse ) = 0; 

    /**
     * Finds a document position and returns information about it and the line 
     * it is in. 
     *
     * @param aDocPos The position to find.
     * @param aPosInfo Returns information on the found position.
     * @param aLineInfo Returns information on the line containing the 
     *                  position found.
     * @return ETrue if the position was found within the formatted text. 
     *         EFalse if the position was not in the formatted text.
     */
    virtual TBool FindDocPos( const TTmDocPosSpec& aDocPos,
                              TTmPosInfo2& aPosInfo,
                              TTmLineInfo& aLineInfo ) const = 0;
    
    /**
     * Returns information (including line number and formatting information) 
     * of the line containing a given document position.
     *
     * @param aDocPos Position to find.
     * @param aLineInfo Returns information about the line containing aDocPos 
     *                  if aDocPos is within the formatted text, or an 
     *                  undefined value if not.
     * @return ETrue if the aDocPos was within the formatted text.
     */

    virtual TBool DocPosToLine(const TTmDocPosSpec& aDocPos,
                               TTmLineInfo& aLineInfo) const = 0;
         
    /**
     * Find the nearest document position to the current one in the visual 
     * direction specified. This only works if the document position is 
     * within formatted text. EFalse is returned if this condition is not met.
     *
     * @param aDocPos Start position.
     * @param aInfo Returns the position found, or an undefined value if aDocPos 
     *              is not in formatted text or is already at the end of the line 
     *              in the direction being searched.
     * @param aToLeft ETrue if the direction to search in is leftwards.
     * @return ETrue if the next position was found (see the description of aInfo).
     */
                      
    virtual TBool GetNextVisualCursorPos(const TTmDocPosSpec& aDocPos,
                                       TTmPosInfo2& aInfo,
                                       TBool aToLeft) const = 0;
      
    /** 
     * Sets the visibility of the line and text cursors.
     * 
     * @param aLineCursor Sets whether the line cursor should be displayed. 
     *                    For possible values, see the TCursor::TVisibility 
     *                    enumeration. 
     * @param aTextCursor Sets whether the text cursor should be displayed 
     *                    and if so, whether it should flash. For possible 
     *                    values, see the TCursor::TVisibility enumeration.
     */               
    virtual void SetCursorVisibilityL(TUint aLineCursor,TUint aTextCursor) = 0; 
        
    /**
     * Returns next visual document position.
     * 
     * @param aStart Starting visual position. The returned position will be greater than this.
     * @return Next visual position.
     */                            
    virtual TInt FindNextPos(TInt aStart) const = 0; 

    /**
     * Returns the text runs of the document adjacent to aPos.
     * 
     * @param aLeft Returns a description of the run on the left of the cursor.
     * @param aRight Returns a description of the run on the right.
     * @return EFalse if the call failed because the line is not formatted or 
     *         contains no text.
     */
    virtual TBool FindAdjacentChunks(const TTmDocPosSpec& aPos, 
                                    CTmTextLayout::TTmChunkDescription& aLeft, 
                                    CTmTextLayout::TTmChunkDescription& aRight) const = 0;
    
    /** 
     * Returns given interface if supported.
     * Currently returns NULL - reserved for future needs.
     *
     * @param aInterfaceUid
     * @return Pointer to interface. NULL if not supported.
     */ 
    virtual TAny* MAknFepDocumentNavigation_Extension1( const TUid& aInterfaceUid ) = 0;
    
    };

#endif // M_AKNFEPDOCUMENTNAVIGATION_H
