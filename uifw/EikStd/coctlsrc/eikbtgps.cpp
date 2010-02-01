/*
* Copyright (c) 1998 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikbtgps.h>

const TUid KEikButtonGroupStackUid={0x10006015};

//
// class TBtGrpStackIter
//

class TBtGrpStackIter : public TDblQueIter<CEikButtonGroupContainer>
	{
public:
	TBtGrpStackIter(TDblQue<CEikButtonGroupContainer>& aList);
	};

TBtGrpStackIter::TBtGrpStackIter(TDblQue<CEikButtonGroupContainer>& aList)
	: TDblQueIter<CEikButtonGroupContainer>(aList)
	{
	SetToFirst();
	}

//
// class CEikButtonGroupStack
//

CEikButtonGroupContainer* CEikButtonGroupStack::Current()
	{ // static
	CEikButtonGroupContainer* ret=NULL;
	CEikButtonGroupStack* self=CEikButtonGroupStack::Self();
	if (self)
		{
		TBtGrpStackIter iter(self->iBtStack);
		CEikButtonGroupContainer* obj=NULL;
		TInt ordinalPos=KMinTInt;
		while ((obj=iter++)!=NULL)
			{
			if (obj->IsVisible())
				{
				const TInt winPos=obj->DrawableWindow()->OrdinalPosition();
				if (winPos>=0 && (winPos<ordinalPos || ordinalPos<0))
					{
					ordinalPos=winPos;
					ret=obj;
					}
				}
			}
		}
	return ret;
	}

/**
 * Returns the minimum size required by the button group stack.
 *
 * @since App-Framework_6.1 
 */
EXPORT_C TSize CEikButtonGroupStack::MinimumSize()
	{ // static
	TSize ret;
	CEikButtonGroupStack* self=CEikButtonGroupStack::Self();
	if (self)
		{
		TBtGrpStackIter iter(self->iBtStack);
		CEikButtonGroupContainer* obj=NULL;
		while ((obj=iter++)!=NULL)
			{
			if (obj->IsVisible())
				{
				const TSize size=obj->Size();
				ret.iHeight=Max(ret.iHeight,size.iHeight);
				ret.iWidth=Max(ret.iWidth,size.iWidth);
				}
			}
		}
	return ret;
	}

void CEikButtonGroupStack::AddL(CEikButtonGroupContainer& aGroup)
	{ // static
	CEikButtonGroupStack* self=CEikButtonGroupStack::Self();
	if (!self)
		{
		self=new(ELeave) CEikButtonGroupStack(); // CCoeEnv takes ownership immediately
		self->iBtStack.AddFirst(aGroup);
		}
	else
		self->iBtStack.AddLast(aGroup);
	}

void CEikButtonGroupStack::Remove(CEikButtonGroupContainer& aGroup)
	{ // static
	CEikButtonGroupStack* self=CEikButtonGroupStack::Self();
	if (self)
		{
		TBtGrpStackIter iter(self->iBtStack);
		CEikButtonGroupContainer* obj=NULL;
		while ((obj=iter++)!=NULL)
			{
			if ((TInt)obj==(TInt)&aGroup)
				{
				obj->iBtLink.Deque();
				break;
				}
			}
		}
	}

inline CEikButtonGroupStack::CEikButtonGroupStack()
	: CCoeStatic(KEikButtonGroupStackUid),
	 iBtStack(_FOFF(CEikButtonGroupContainer,iBtLink))
	{}

inline CEikButtonGroupStack* CEikButtonGroupStack::Self()
	{return STATIC_CAST(CEikButtonGroupStack*,CCoeEnv::Static(KEikButtonGroupStackUid));}
