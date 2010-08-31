/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A default dummy non-window owning control. Can be used to
*                draw skinned background in in area where not other
*                controls exists.
*
*/


#ifndef C_AKNEMPTYCONTROL_H
#define C_AKNEMPTYCONTROL_H

#include <bacntf.h>
#include <coecntrl.h>
#include <AknControl.h>


/**
* Empty control that draws background with skinning.
* This control also directs pointer events it receives to it's adjacent
* status pane sub-pane to enhance the touch responsivity.
* 
* This class is not intended for further derivation.
*
* @since 3.1
*
* @internal Used by the UI Framework.
*/
NONSHARABLE_CLASS( CAknEmptyControl ) : public CAknControl
	{
public:

    /**
    * Standard constructor.
    */
    CAknEmptyControl();
    
    /**
    * Destructor.
    */
    ~CAknEmptyControl();
        
    /** 
    * Constructs from resource.
    *
    * @param aReader resource reader.
    */
    void ConstructFromResourceL( TResourceReader& aReader );
    
public: // From @c CCoeControl.
    
    /**
    * Handles pointer events
    *
    * @param aPointerEvent The pointer event.
    */
    virtual void HandlePointerEventL( const TPointerEvent& aPointerEvent );

protected: // From @c CCoeControl.

    /**
    * Handles size change events.
    */
    void SizeChanged();
    
    /**
    * Handles a change to the control's resources of type aType
    * which are shared across the environment.
    * @param aType Event type.
    */
    void HandleResourceChange( TInt aType );

private: // From @c CCoeControl.

    /**
    * Draws the control.
    */
    void Draw( const TRect& aRect ) const;
    
private: // New methods.
    
    /**
    * Directs a pointer event received by this control to a pointer
    * responsive adjacent status pane sub-pane. In this method the
    * recipient of the pointer event is decided based on the layouts.
    *
    * @param aPointerEvent The pointer event.
    * 
    * @return  @c ETrue if the pointer event was passed on,
    *          @c EFalse otherwise.
    */
    TBool PassPointerEventToAdjacentControlL(
        const TPointerEvent& aPointerEvent );

private:

    TInt iSpare;
    TBool iIsActiveIdle;
    };

#endif // C_AKNEMPTYCONTROL_H

