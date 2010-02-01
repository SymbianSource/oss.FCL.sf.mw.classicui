/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon pointer event modifier.
*
*/


#include <aknpointereventmodifier.h>
#include <coecntrl.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::NewL
// ---------------------------------------------------------------------------
//
CAknPointerEventModifier* CAknPointerEventModifier::NewL()
    {
    CAknPointerEventModifier* self = new ( ELeave ) CAknPointerEventModifier;
    return self;
    }
    
// ---------------------------------------------------------------------------
// CAknPointerEventModifier::~CAknPointerEventModifier()
// ---------------------------------------------------------------------------
//
CAknPointerEventModifier::~CAknPointerEventModifier()
    {
    iStack.Close();
    }
    
// ---------------------------------------------------------------------------
// CAknPointerEventModifier::CAknPointerEventModifier
// ---------------------------------------------------------------------------
//
CAknPointerEventModifier::CAknPointerEventModifier()
    {
    }

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::Push
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPointerEventModifier::Push( CCoeControl& aControl, 
    const TRect& aRect )
    {
    // Figure out aControl's window-owning parent. This will also work as a
    // sanity check for the aControl argument.
    CCoeControl* parent = aControl.Parent();
    
    while ( parent && !parent->OwnsWindow() )
        {
        parent = parent->Parent();
        }
        
    if ( !parent )
        {
        return;
        }
    
    if ( !ControlIsInStack( aControl ) )
        {
        TStackItem item;
        item.iControl = &aControl;
        item.iParent = parent;
        item.iExtensionArea = aRect;
        
        if ( iStack.Insert( item, 0 ) == KErrNone )
            {
            iIsValid = EFalse;
            }
        }
    }

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::Pop
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPointerEventModifier::Pop( const CCoeControl& aControl )
    {
    for ( TInt i = 0; i < iStack.Count(); ++i )
        {
        if ( iStack[i].iControl == &aControl )
            {
            iStack.Remove( i );
            iIsValid = EFalse;
            return;
            }
        }
    }

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::Update
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPointerEventModifier::Update( const CCoeControl& aControl, 
    const TRect& aRect )
    {
    for ( TInt i = 0; i < iStack.Count(); ++i )
        {
        if ( iStack[i].iControl == &aControl )
            {
            iStack[i].iExtensionArea = aRect;
            break;
            }
        }
    }
    
// ---------------------------------------------------------------------------
// CAknPointerEventModifier::HandlePointerEvent
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPointerEventModifier::HandlePointerEvent( TPointerEvent& aEvent, 
    CCoeControl*& aDestination )
    {
    if ( iStack.Count() > 0 && aEvent.iType == TPointerEvent::EButton1Down )
        {
        if ( !iIsValid )
            {
            iStack.Sort( CAknPointerEventModifier::Compare );
            }
            
        for ( TInt i = 0; i < iStack.Count(); ++i )
            {
            if ( ModifyEvent( iStack[i], aEvent, aDestination ) )
                {
                break;
                }
            }
        }
    }
    
// ---------------------------------------------------------------------------
// CAknPointerEventModifier::Invalidate
// ---------------------------------------------------------------------------
//
void CAknPointerEventModifier::Invalidate()
    {
    iIsValid = ETrue;
    }

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::ControlIsInStack
// ---------------------------------------------------------------------------
//
TBool CAknPointerEventModifier::ControlIsInStack( const CCoeControl& aControl )
    {
    for ( TInt i = 0; i < iStack.Count(); ++i )
        {
        if ( iStack[i].iControl == &aControl )
            {
            return ETrue;
            }
        }
    
    return EFalse;
    }

// ---------------------------------------------------------------------------
// CAknPointerEventModifier::ModifyEvent
// ---------------------------------------------------------------------------
//
TBool CAknPointerEventModifier::ModifyEvent( TStackItem& aItem, 
    TPointerEvent& aEvent, CCoeControl*& aDestination )
    {
    TBool wasModified = EFalse;
    
    // Control window's existence has been checked already in 
    // CAknPointerEventModifier::Push.
    if ( !aItem.iControl->DrawableWindow()->IsFaded() )
        {
        TBool isVertical = ( aItem.iControl->Size().iHeight > aItem.iControl->Size().iWidth );
        
        if ( aDestination == aItem.iParent )
            {
            // calculate hit area
            TRect hitArea( aItem.iControl->Position() + 
                aItem.iExtensionArea.iTl, aItem.iExtensionArea.Size() );
            TSize controlSize( aItem.iControl->Size() );

            if ( hitArea.Contains( aEvent.iPosition ) )
                {
                if ( aItem.iControl->OwnsWindow() )
                    {
                    aDestination = aItem.iControl;
                    
                    if ( isVertical )
                        {
                        aEvent.iPosition.iX = controlSize.iWidth >> 1;
                        aEvent.iPosition.iY -= aItem.iControl->Position().iY;
                        }
                    else
                        {
                        aEvent.iPosition.iX -= aItem.iControl->Position().iX;
                        aEvent.iPosition.iY = controlSize.iHeight >> 1;
                        }
                    }
                else
                    {
                    if ( isVertical )
                        {
                        aEvent.iPosition.iX = aItem.iControl->Position().iX + 
                            ( controlSize.iWidth >> 1 );
                        }
                    else
                        {
                        aEvent.iPosition.iY = aItem.iControl->Position().iY +
                            ( controlSize.iHeight >> 1 );
                        }
                    }
                    
                wasModified = ETrue;
                }
            }
        else if ( aDestination->Parent() && 
            aDestination->Parent()->DrawableWindow() == aItem.iParent->DrawableWindow() &&
             ( aDestination->Parent() != aItem.iParent ))
            {
            // This branch handles external scrollbars. It should be checked
            // via MOP chain if the aItem.iControl really is a scrollbar before
            // this API is taken into use with other controls.
            TPoint topLeft( aItem.iControl->Position().iX - 
                aDestination->Position().iX, 
                aItem.iControl->Position().iY - aDestination->Position().iY );
            TRect hitArea( topLeft + 
                aItem.iExtensionArea.iTl, aItem.iExtensionArea.Size() );

            if ( hitArea.Contains( aEvent.iPosition ) )
                {
                TInt controlPosition = aItem.iControl->Position().iY;
                TInt positionInParent = aEvent.iPosition.iY + aDestination->Position().iY;
                
                if ( isVertical )
                    {
                    aEvent.iPosition.iX = aItem.iControl->Size().iWidth >> 1;
                    aEvent.iPosition.iY = positionInParent - controlPosition;
                    }
                else
                    {
                    aEvent.iPosition.iX = aEvent.iPosition.iX + 
                        aDestination->Position().iX - aItem.iControl->Position().iX;
                    aEvent.iPosition.iY = aItem.iControl->Size().iHeight >> 1;
                    }
                    
                aDestination = aItem.iControl;
                
                wasModified = ETrue;
                }
            }
        }
        
    return wasModified;
    }
    
// ---------------------------------------------------------------------------
// CAknPointerEventModifier::Compare
// ---------------------------------------------------------------------------
//
TInt CAknPointerEventModifier::Compare( const TStackItem& aFirst, 
    const TStackItem& aSecond )
    {
    TInt retval = -1; // aFirst is in front of aSecond
    TInt firstPosition = aFirst.iParent->DrawableWindow()->OrdinalPosition();
    TInt secondPosition = aSecond.iParent->DrawableWindow()->OrdinalPosition();
    
    if ( secondPosition < firstPosition && secondPosition >= 0 )
        {
        // aSecond is in front of aFirst in z-order
        retval = 1;
        }
    else if ( firstPosition == secondPosition )
        {
        // aFirst and aSecond have the same parent window
        retval = 0;
        }
    
    return retval;
    }
