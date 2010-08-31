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
*
*/


#include <aknnotecontrol.h>
#include <AknUtils.h>
#include <aknappui.h>
#include <aknborders.h>
#include <eikcapc.h>
#include <eikimage.h>
#include <aknconsts.h>
#include <aknstaticnotedialog.h>

#include <avkon.mbg>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>

#include <AknTasHook.h> // for testability hooks
class CAknStackIndicatorAttributes: public CBase
	{
public:
	TSize iTwoNotesInStackBitmapSize;
	TSize iManyNotesInStackBitmapSize;
	TInt iStackDepth;
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// class CAknStaticNoteStackIndicator

CAknStaticNoteStackIndicator::~CAknStaticNoteStackIndicator()
	{
	delete iAttributes;
	}

void CAknStaticNoteStackIndicator::DoSetExtent()
	{

	TSize size = TSize(0,0);
	TPoint pos = iParentNote->Position();

	if ( iAttributes->iStackDepth == 1 )
		{
		pos -= TPoint(0,iAttributes->iTwoNotesInStackBitmapSize.iHeight);
		size = iAttributes->iTwoNotesInStackBitmapSize;
		}
	else if (  iAttributes->iStackDepth > 1 )
		{
		pos -= TPoint(0,iAttributes->iManyNotesInStackBitmapSize.iHeight);
		size = iAttributes->iManyNotesInStackBitmapSize;
		}

	// We want to avoid unnecessary SizeChanged Events
	if ( pos != Position() || size != Size() )	
		{ 	 
		SetExtent(pos, size);
		}
	}

EXPORT_C void CAknStaticNoteStackIndicator::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknStaticNoteStackIndicator::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

void CAknStaticNoteStackIndicator::ConstructL(CCoeControl* aParentNote, TInt aStackDepth)
	{
	iAttributes = new (ELeave) CAknStackIndicatorAttributes();
	iAttributes->iStackDepth = aStackDepth;

	iParentNote = aParentNote;

	HandleResourceChange(KAknsMessageSkinChange);

	CreateWindowL();

	DoSetExtent();

	ActivateL();
	}

void CAknStaticNoteStackIndicator::UpdateDepth(TInt aDepth)
	{
	iAttributes->iStackDepth = aDepth;
	DoSetExtent();
	if ( aDepth >= 1 )	
		DrawDeferred();
	}

void CAknStaticNoteStackIndicator::Draw(const TRect& /*aRect*/) const
	{
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();

	TAknsItemID id;
	id.Set(0,0);

	if ( iAttributes->iStackDepth == 1 )
		{
		id = KAknsIIDQgnGrafSnoteAdd1;
		}
	else if ( iAttributes->iStackDepth > 1 )
		{
		id = KAknsIIDQgnGrafSnoteAdd2;
		}

	// if following method fails, we draw nothing, no big deal
	AknsDrawUtils::DrawCachedImage( skin, SystemGc(), Rect(), id);
	}

EXPORT_C void CAknStaticNoteStackIndicator::HandleResourceChange(TInt aType)
	{
	if ( !iAttributes )
		return;

	if( aType == KAknsMessageSkinChange )
		{
		MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TAknLayoutRect rect;
        rect.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_Notification_pop_up_window_elements__text__Line_1 );

		CFbsBitmap* bitmap = NULL;

		bitmap = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnGrafSnoteAdd1 );		
		if (bitmap)
			{
            AknIconUtils::SetSize( bitmap, rect.Rect().Size() );        
			iAttributes->iTwoNotesInStackBitmapSize = bitmap->SizeInPixels();
			bitmap = NULL;
			}
		bitmap = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnGrafSnoteAdd2 );		
		if (bitmap)
			{
            AknIconUtils::SetSize( bitmap, rect.Rect().Size() );        
			iAttributes->iManyNotesInStackBitmapSize = bitmap->SizeInPixels();
			}	

		}
	}


/**
 * Default constructor
 *
 * Just call CAknNoteDialog constructor
 */
EXPORT_C CAknStaticNoteDialog::CAknStaticNoteDialog() : CAknNoteDialog()
	{
	AKNTASHOOK_ADD( this, "CAknStaticNoteDialog" );
	}

/**
 * Another class constructor
 *
 * Accept self pointer to CEikDialog* in order to NULL 
 * client pointer when a non modal note is dismissed.
 *
 * @param aSelfPtr Address of the dialog pointer
 */
EXPORT_C CAknStaticNoteDialog::CAknStaticNoteDialog(CEikDialog** aSelfPtr) : CAknNoteDialog(aSelfPtr)
	{
	AKNTASHOOK_ADD( this, "CAknStaticNoteDialog" );
	}

/**
 * Class destructor
 *
 * Delete the stack indicator
 */
EXPORT_C CAknStaticNoteDialog::~CAknStaticNoteDialog()
	{
	AKNTASHOOK_REMOVE();
	delete iStackIndicator;
	}

/**
 * Set the number of borders
 *
 * Update the stack indicator depth to the specified number of borders. 
 * 
 * @param aNumber    The number of borders
 */
EXPORT_C void CAknStaticNoteDialog::SetNumberOfBorders(TInt aNumber)
	{
	iStackDepth = aNumber - 1;
	if (iStackIndicator)
		iStackIndicator->UpdateDepth(iStackDepth);
	};

EXPORT_C void CAknStaticNoteDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknNoteDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknStaticNoteDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 * Part of dialog framework, called after layout has been performed
 *
 * Call PostLayoutDynInitL as implemented in the base, CAknNoteDialog
 * and create a stack indicator
 * 
 */
EXPORT_C void CAknStaticNoteDialog::PostLayoutDynInitL()
    {
	CAknNoteDialog::PostLayoutDynInitL();
	if (!iStackIndicator)
		{
		iStackIndicator = new(ELeave)CAknStaticNoteStackIndicator();
		iStackIndicator->ConstructL(this, iStackDepth);
		}
    }

/**
 * Part of the dialog framework, process a key event.
 *
 * Call the implementation of OfferKeyEventL provided by
 * CEikDialog, bypassing the direct base, CAknNoteDialog.
 */

EXPORT_C TKeyResponse CAknStaticNoteDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	return CEikDialog::OfferKeyEventL(aKeyEvent,aType);
	}

EXPORT_C void CAknStaticNoteDialog::CEikDialog_Reserved_1()
	{
	}

EXPORT_C void CAknStaticNoteDialog::CEikDialog_Reserved_2()
	{
	}

EXPORT_C void CAknStaticNoteDialog::CAknNoteDialog_Reserved()
	{
	}

EXPORT_C void CAknStaticNoteDialog::CAknStaticNoteDialog_Reserved()
	{
	}


// End of File
