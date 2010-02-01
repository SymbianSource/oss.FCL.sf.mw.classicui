/*
* Copyright (c) 1997-2000 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikbgfty.h>
#include <eikpanic.h>

const TUid KUidButtonGroupFactoryContainerTls={0x100090DD};

EXPORT_C EikButtonGroupFactory::TCreationData::TCreationData(CEikButtonGroupContainer::TUse aUse,MEikCommandObserver* aCommandObserver,TInt aResourceId,RWindowGroup* aParentWg,TUint aFlags,CEikButtonGroupContainer::TOrientation aOrientation)
							:iUse(aUse),
							iCommandObserver(aCommandObserver),
							iResourceId(aResourceId),
							iParentWg(aParentWg),
							iFlags(aFlags),
							iOrientation(aOrientation)						
	{
	}

/**
 * Creates a button group of type aButtonGroupType, if it exists in any registered button group 
 * factory function, and returns a handle to the button group interface the constructed object implements.
 * Extra required information is supplied in aCreationData.  If the button group is to be added
 * to the button group stack then this can be set in aAddToButtonGroupStack.  Returns NULL if
 * aButtonGroupType doesn't exist in any registered button group factory function.
 *
 * @internal
 * Internal to Symbian
 */
MEikButtonGroup* EikButtonGroupFactory::CreateButtonGroupByTypeL(TInt aButtonGroupType,TCreationData& aCreationData,TBool& aAddToButtonGroupStack)
	{// static
	MEikButtonGroup* buttonGroup = NULL;

	CArrayFixFlat<TCreateButtonGroupByTypeFunction>* buttonGroupFactoryFuncArray = CEikButtonGroupFactoryArray::ButtonGroupFactoryFuncArray();
	TInt count = 0;
	if(buttonGroupFactoryFuncArray)
		count = buttonGroupFactoryFuncArray->Count();
	for(TInt i = 0; i < count; i++)
		{
		TCreateButtonGroupByTypeFunction buttonGroupFactoryFunc = (*buttonGroupFactoryFuncArray)[i];
		buttonGroup = (*buttonGroupFactoryFunc)(aButtonGroupType,aCreationData,aAddToButtonGroupStack);
		if(buttonGroup)
			break;
		}
		
	return buttonGroup;
    }

CEikButtonGroupFactoryArray::~CEikButtonGroupFactoryArray()
	{
	delete iButtonGroupFactoryFuncArray;	
	}

/**
 * Adds a button group factory to the iButtonGroupFactoryFuncArray array.  If the array
 * doesn’t yet exist, then it creates a new one and appends it in as the first element.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void CEikButtonGroupFactoryArray::AppendFactoryFunctionL(TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction)
	{//static
	CEikButtonGroupFactoryArray* self = CEikButtonGroupFactoryArray::Self();
	if (!self)
		{
		self=new(ELeave) CEikButtonGroupFactoryArray(); // CCoeEnv takes ownership immediately
		}
	if(!self->iButtonGroupFactoryFuncArray)
		self->iButtonGroupFactoryFuncArray = new(ELeave) CArrayFixFlat<TCreateButtonGroupByTypeFunction>(2);
	self->iButtonGroupFactoryFuncArray->AppendL(aCreateButtonGroupByTypeFunction);
	}

/**
 * Removes a button group factory from the iButtonGroupFactoryFuncArray array.
 *
 * @since App-Framework_6.1
 */
EXPORT_C void CEikButtonGroupFactoryArray::RemoveFactoryFunction(TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction)
	{//static
	CEikButtonGroupFactoryArray* self = CEikButtonGroupFactoryArray::Self();
	__ASSERT_ALWAYS(self,Panic(EEikPanicNoButtonGroupFactory));

	TInt count;
	if(aCreateButtonGroupByTypeFunction && self->iButtonGroupFactoryFuncArray)
		{
		count = self->iButtonGroupFactoryFuncArray->Count();
		for(TInt ii = 0; ii < count; ii++)
			{
			if((*(self->iButtonGroupFactoryFuncArray))[ii] == aCreateButtonGroupByTypeFunction)
				{
				self->iButtonGroupFactoryFuncArray->Delete(ii);
				break;
				}
			}
		}
	}

/**
 * Returns the array of pointers to the registered button group factory creation methods
 *
 * @internal
 * Internal to Symbian
 * @since App-Framework_6.1
 */
CArrayFixFlat<TCreateButtonGroupByTypeFunction>* CEikButtonGroupFactoryArray::ButtonGroupFactoryFuncArray()
	{//static
	CEikButtonGroupFactoryArray* self = CEikButtonGroupFactoryArray::Self();
	__ASSERT_ALWAYS(self,Panic(EEikPanicNoButtonGroupFactory));
	return self->iButtonGroupFactoryFuncArray;
	}

inline CEikButtonGroupFactoryArray::CEikButtonGroupFactoryArray()
	: CCoeStatic(KUidButtonGroupFactoryContainerTls)
	{}
inline CEikButtonGroupFactoryArray* CEikButtonGroupFactoryArray::Self()//static
	{return static_cast<CEikButtonGroupFactoryArray*>(CCoeEnv::Static(KUidButtonGroupFactoryContainerTls));}
