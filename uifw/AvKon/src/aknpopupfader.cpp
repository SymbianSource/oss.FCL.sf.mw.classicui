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

// AknPopupFader.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include "AknPopupFader.h"

#include <coecntrl.h>
#include <eikdef.h>
#include <coemain.h>
#include <eikon.hrh>
#include <eikenv.h>
#include <aknappui.h>
#include <w32std.h>
#include <eikdialg.h>
#include <AknSgcc.h>

const TUid KUidFadeStackTls = {0x101f760b};
const TInt KFadeStackGranularity = 4;

EXPORT_C TInt MAknFadedComponent::CountFadedComponents()
	{
	return 0;
	}

EXPORT_C CCoeControl* MAknFadedComponent::FadedComponent(TInt /*aIndex*/)
	{
	return NULL;
	}


NONSHARABLE_CLASS(CAknFadeStack) : public CCoeStatic, public MCoeForegroundObserver
	{
public:
    enum TStackPosition
        {
        EStackTop = 0,
        EStackNextToTop
        };
public:
	static void CreateL();
	static CAknFadeStack* Static();

	void PushPopupFaderL(MAknFadedComponent* aPopup);
	void PopPopupFader(MAknFadedComponent* aPopup);

private:
	CAknFadeStack();
	~CAknFadeStack();
	void ConstructL();
	void SetComponentFaded(MAknFadedComponent* aPopup, TBool aFade);
	MAknFadedComponent* PopupFader(TStackPosition aPosition) const;
    TBool IsFullscreenDialog(MAknFadedComponent* aPopup);
	void SetFade();
	void RemovePopupFader(MAknFadedComponent* aPopup);
    void SetSystemFadeOff();
    
private: // from MCoeForegroundObserver
	void HandleGainingForeground();
	void HandleLosingForeground();

private:
	CArrayFixFlat<MAknFadedComponent*>* iFadeStack;
	TBool iIsForeground;
	CCoeEnv* iCoeEnv;
	TBool iSystemFaded;
	};

CAknFadeStack::CAknFadeStack()
: CCoeStatic(KUidFadeStackTls), iCoeEnv(CCoeEnv::Static())
	{
	    iSystemFaded = EFalse;
	}

CAknFadeStack::~CAknFadeStack()
	{
	iCoeEnv->RemoveForegroundObserver(*this);
	delete iFadeStack;
	}

void CAknFadeStack::ConstructL()
	{
	iFadeStack = new(ELeave) CArrayFixFlat<MAknFadedComponent*>(KFadeStackGranularity);
	iCoeEnv->AddForegroundObserverL(*this);
	}

CAknFadeStack* CAknFadeStack::Static()
	{
	return static_cast<CAknFadeStack*>(CCoeEnv::Static(KUidFadeStackTls));
	}

void CAknFadeStack::CreateL()
	{ // static
	CAknFadeStack* self=CAknFadeStack::Static();
	if (!self)
		{
		self=new(ELeave) CAknFadeStack(); // CCoeEnv takes ownership immediately
		CleanupStack::PushL(self);
		self->ConstructL();
		CleanupStack::Pop();
		}
	}

void CAknFadeStack::HandleGainingForeground()
	{
	iIsForeground = ETrue;
	SetFade();
	}

void CAknFadeStack::HandleLosingForeground()
	{
	iIsForeground = EFalse;
	iSystemFaded = EFalse;
    SetFade();
	}

void CAknFadeStack::PushPopupFaderL(MAknFadedComponent* aPopup)
	{
	RemovePopupFader(aPopup);
	iFadeStack->AppendL(aPopup);
	SetFade();
	}

void CAknFadeStack::PopPopupFader(MAknFadedComponent* aPopup)
	{
	RemovePopupFader(aPopup);
	SetFade();
	}

void CAknFadeStack::RemovePopupFader(MAknFadedComponent* aPopup)
	{
	TInt end = iFadeStack->Count() - 1;
	for (TInt ii=end; ii>=0; ii--)
		{
		if (iFadeStack->At(ii) == aPopup)
			iFadeStack->Delete(ii);
		}
	}

void CAknFadeStack::SetSystemFadeOff()
    {
    if ( iSystemFaded || CAknSgcClient::IsSystemFaded() )
        {
        CAknAppUi* appUi = iAvkonAppUi;
        TRAP_IGNORE( appUi->SetFadedL(EFalse) );
        iSystemFaded = EFalse;
        }
    }

void CAknFadeStack::SetComponentFaded(MAknFadedComponent* aPopup, TBool aFade)
	{
	TInt count = aPopup->CountFadedComponents();
	for (TInt ii=0; ii<count; ii++)
		{
		CCoeControl* control = aPopup->FadedComponent(ii);
		//fix for TSW error EHLN-7HHFPX
		if ( control != NULL )
		    {
		    control->DrawableWindow()->SetFaded(aFade, RWindowTreeNode::EFadeIncludeChildren);    
		    }
		}
	}

TBool CAknFadeStack::IsFullscreenDialog(MAknFadedComponent* aPopup)
{
	TInt count = aPopup->CountFadedComponents();
	for (TInt ii=0; ii<count; ii++)
		{
		CCoeControl* control = aPopup->FadedComponent(ii);
	    CEikDialog* dialg = NULL;
	    //fix for TSW error EHLN-7HHFPX
	    if ( control != NULL )
	        {
	        dialg = control->MopGetObjectNoChaining(dialg);
	        if(dialg != NULL)
	            {
	            // is a dialog, get flags
	            TInt flags = dialg->DialogFlags();
	            if ((flags&EEikDialogFlagFillAppClientRect) || (flags&EEikDialogFlagFillScreen) || (flags&EEikDialogFlagNoBackgroundFade) )
	                {
	                return ETrue;
	                }
	            }    
	        }
		}
    return EFalse;
}

MAknFadedComponent* CAknFadeStack::PopupFader(TStackPosition aPosition) const
    {
    TInt count = iFadeStack->Count();
    return count > aPosition ? iFadeStack->At(count-1-aPosition) : NULL;
    }

void CAknFadeStack::SetFade()
	{
	MAknFadedComponent* top = PopupFader(EStackTop);
	CAknAppUi* appUi = iAvkonAppUi;

	if (iIsForeground || appUi->IsForeground())
		{
		if(top) 
		    {
		    if(!IsFullscreenDialog(top))
		        {
    		    if(!iSystemFaded)
	    	        {
    		        TRAP_IGNORE( appUi->SetFadedL(ETrue) );
	    	        iSystemFaded = ETrue;
		            }
		        else
    		        {
    		        // If a popup comes on top of another, system fade is not
    		        // called but the previous top popup is faded
    		        MAknFadedComponent* prevTop = PopupFader(EStackNextToTop);
                    if (prevTop)
                        {
                        SetComponentFaded(prevTop, ETrue);
                        }
	    	        }
    			SetComponentFaded(top, EFalse);
		        }
		    else
		        {
                // Remove fading for fullscreen dialogs		            
                SetSystemFadeOff();                		            
	    	    }
		    }
		else
		    {
            SetSystemFadeOff();
		    }
		}
	else if (top)
		{
		SetComponentFaded(top, appUi->IsFaded());
		}
	}


EXPORT_C void TAknPopupFader::FadeBehindPopup(MAknFadedComponent* aComponent,  CCoeControl* aParent, TBool aFade)
	{
	TRAP_IGNORE(FadeBehindPopupL(aComponent, aParent, aFade));
	}

void TAknPopupFader::FadeBehindPopupL(MAknFadedComponent* aComponent,  CCoeControl* /*aParent*/, TBool aFade)
	{
	CAknFadeStack* stack=CAknFadeStack::Static();
	if (stack)
		{
		if (aFade)
			{
			stack->PushPopupFaderL(aComponent);
			}
		else
			{
			stack->PopPopupFader(aComponent);
			}
		}
	}

void TAknPopupFader::CreateStaticL()
	{
	CAknFadeStack::CreateL();
	}

// End of File
