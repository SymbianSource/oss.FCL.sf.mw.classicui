// Copyright (c) 1997-2010 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

// #define PROFILE_MEMORY	// Uncomment to profile ammount of saved memory.

#ifdef PROFILE_MEMORY
static TInt MEMORY_SAVED = 0;	// In bytes
const TInt KCurrentNumberOfOptionalVaraiblesInCCoeControl = 13;
#endif

/** 
This class implements a container for (in most cases, pointers to) optional 
CCoeControl members.

The size of the class is 12 bytes: one 32-bit pointer to a C-style array 
of 32-bit data, and one long long (64 bits) variable used as an array of 4-bit 
indices into said C-style array. 

Each optional CCoeControl data is assigned an index into the long long member, 
used to look up the variables actual index in the C-style array. This way, the 
first time a new optional CCoeControl variable is set it is appended to the C-style 
array, and the index of the new item is recorded in the variable's assigned 
4-bit slot in the long long. 

The 4-bits used for each index allows for 16 indices to be stored in the long long. 
However, one value (say 0xF) is required to signal that the optional variable has 
not yet been added to the C-style array, so this leaves 15 optional CCoeControl members. 

This also leaves the last 4 bits in the long long unused. Now, we also need a way 
to record the current size of the C-style array. As the size range from 0 to 15, 
4-bit is enough, which means that we can use the last 4 spare bits in the long long 
instead of adding another variable to the RCoeDynamicDataStorage!

Thus, each first time an optional member is set, we need to re-allocate the C-style 
array, and this operation might of course fail. All of the data kept in the 
RCoeDynamicDataStorage must therefore be optional, and the code able to cope 
with this. To minimize the number of re-allocations, the RCoeDynamicDataStorage 
allows pre-allocation of the maximum amount needed. Currently, pre-allocation is 
attempted at CCoeControl construction (in the c'tor), and compression is attempted 
when the control is activated. The RCoeDynamicDataStorage will still work if either 
fails.

@internalComponent */
class RCoeDynamicDataStorage
	{
public:
	RCoeDynamicDataStorage();
	TInt Open();
	void Close();
	TInt Count() const;
	void ResetCount();
	void IncCount();
	TInt ReserveData();
	TBool HasReservedData() const;
	void AttemptCompress();
	inline TAny* Data(TInt aSlotIndex, TAny* aDefaultValue) const;	//mm Will this method be expanded inline when used inside coecntrl.cpp?
	TInt SetData(TInt aSlotIndex, TAny* aAny);
	inline TInt DataIndex(TInt aSlotIndex) const;
	void SetDataIndex(TInt aSlotIndex, TInt aDataIndex);
	
private:
	static const TInt KMaxDataItems;
	static const TInt KCounterSlotIndex;
	static const TInt KIndexSlotSize;
	static const Uint64 KIndexSlotMask;
	static const TInt KUndefinedIndex;

private:
	TInt Append(TAny* aAny);
	
private:	
	Uint64 iIndices;	// array of slots containing indices into the data array
	TAny** iDynamicData;		// dynamic array of 32-bit data (mostly pointers)
	};
	

const TInt RCoeDynamicDataStorage::KMaxDataItems = 15;
const TInt RCoeDynamicDataStorage::KCounterSlotIndex = 0xF;
const TInt RCoeDynamicDataStorage::KIndexSlotSize = 4;
const Uint64 RCoeDynamicDataStorage::KIndexSlotMask = 0xFLL;	//long long
const TInt RCoeDynamicDataStorage::KUndefinedIndex = 0xF;

RCoeDynamicDataStorage::RCoeDynamicDataStorage()
: iIndices(~0x0), iDynamicData(NULL)	// Set iIndices to all ones
	{
	ResetCount();
	}

TInt RCoeDynamicDataStorage::Open()
	{
	ASSERT(!iDynamicData);
	TInt err = ReserveData();

#ifdef PROFILE_MEMORY
	if (err==KErrNone)
		{
		MEMORY_SAVED += KCurrentNumberOfOptionalVaraiblesInCCoeControl*sizeof(TAny*);
		MEMORY_SAVED -= sizeof(RCoeDynamicDataStorage);
		}
#endif

	return err;
	}

void RCoeDynamicDataStorage::Close()
	{
#ifdef PROFILE_MEMORY
	MEMORY_SAVED += sizeof(RCoeDynamicDataStorage);
	if(HasReservedData())
		MEMORY_SAVED +=  KMaxDataItems*sizeof(TAny*);
	else
		MEMORY_SAVED += Count()*sizeof(TAny*);
	
	MEMORY_SAVED -= KCurrentNumberOfOptionalVaraiblesInCCoeControl*sizeof(TAny*);
#endif	
	delete [] iDynamicData;
	}

TInt RCoeDynamicDataStorage::Count() const
	{
	if(HasReservedData())
		{
		TInt count = 0;
		for(TInt i = 0; i < KMaxDataItems; i++)
			{
			if(DataIndex(i) != KUndefinedIndex)
				count++;
			}
		return count;	
		}
	else
		return DataIndex(KCounterSlotIndex);	
	}

void RCoeDynamicDataStorage::ResetCount()
	{
	SetDataIndex(KCounterSlotIndex, 0);
	}
	
void RCoeDynamicDataStorage::IncCount()
	{
	TInt count = Count();
	count++;
	SetDataIndex(KCounterSlotIndex, count);
	ASSERT(count <= KMaxDataItems);
	}

TInt RCoeDynamicDataStorage::SetData(TInt aSlotIndex, TAny* aAny)
	{
	if(!this)
		return KErrNoMemory;
	
	const TInt dataIndex = DataIndex(aSlotIndex);

	if(dataIndex != KUndefinedIndex)
		iDynamicData[dataIndex] = aAny;
	else if(HasReservedData())
		{
		const TInt count = Count();
		iDynamicData[count] = aAny;
		SetDataIndex(aSlotIndex, count);
		}
	else
		{
		const TInt err = Append(aAny);
		if(err)
			return err;
		else
			SetDataIndex(aSlotIndex, Count()-1);
		}
	ASSERT(Data(aSlotIndex, NULL) == aAny);	
	return KErrNone;
	}

inline TAny* RCoeDynamicDataStorage::Data(TInt aSlotIndex, TAny* aDefaultValue) const
	{
	if (!this)
		return aDefaultValue;

	const TInt dataIndex = DataIndex(aSlotIndex);
	if (dataIndex!=KUndefinedIndex && iDynamicData!=NULL)	//Defensive Code
		return iDynamicData[dataIndex];
	else
		return aDefaultValue;
	}

inline TInt RCoeDynamicDataStorage::DataIndex(TInt aSlotIndex) const
	{
	const Uint64 mask = KIndexSlotMask << KIndexSlotSize*aSlotIndex;
	return ((iIndices&mask) >> KIndexSlotSize*aSlotIndex);
	}
	
void RCoeDynamicDataStorage::SetDataIndex(TInt aSlotIndex, TInt aDataIndex)
	{
	const Uint64 mask = KIndexSlotMask << KIndexSlotSize*aSlotIndex;
	const Uint64 dataIndex = Uint64(aDataIndex) << KIndexSlotSize*aSlotIndex;
	iIndices &= ~mask;	// clear the old index
	iIndices |= dataIndex; // set the new index
	}

TInt RCoeDynamicDataStorage::Append(TAny* aAny)
	{
	ASSERT(!HasReservedData());	// Should never have reserved data if we get here
	
	const TInt count = Count();
	TAny** newData = new TAny*[count+1];
	if(!newData)
		return KErrNoMemory;
	
	memcpy(newData, iDynamicData, count * sizeof(TAny*));
		
	newData[count]	= aAny;
	IncCount();
#ifdef PROFILE_MEMORY
	MEMORY_SAVED -= (1 * sizeof(TAny*));
#endif
		
	delete [] iDynamicData;
	iDynamicData = newData;
	return KErrNone;
	}


TInt RCoeDynamicDataStorage::ReserveData()
	{
	ASSERT(!iDynamicData);
	iDynamicData = new TAny*[KMaxDataItems];	// Attempt to pre-alloc data
	if(!iDynamicData)
		return KErrNoMemory;	
	
#ifdef PROFILE_MEMORY
	MEMORY_SAVED -= KMaxDataItems*sizeof(TAny*);
#endif	
	return KErrNone;
	}
		
TBool RCoeDynamicDataStorage::HasReservedData() const
	{
	return (iDynamicData && DataIndex(KCounterSlotIndex) == 0);
	}

void RCoeDynamicDataStorage::AttemptCompress()
	{
	if(!HasReservedData()) 
		return;
	
	const TInt count = Count();
	if(!count)	// "new TAny*[0]" gives undefined result!
		{
		delete [] iDynamicData;
		iDynamicData = NULL;
		}
	else
		{
		TAny** newData = new TAny*[count];
		if(!newData)
			return;
		
		memcpy(newData, iDynamicData, count * sizeof(TAny*));
					
		delete [] iDynamicData;
		iDynamicData = newData;
		SetDataIndex(KCounterSlotIndex, count);
		}
		
#ifdef PROFILE_MEMORY		
	MEMORY_SAVED += (sizeof(TAny*) * (0xF - count));
#endif	
	}

// 
// class TCoeZoomWithType 
// 

class TCoeZoomWithType 
    { 
public:                 
    TInt iZoomFactor; 
    CCoeControl::TZoomType iZoomType; 
    }; 

// 
// class SColorOverride
// 

struct SColorOverride	
	{
	TRgb iColor;
	TInt iLogicalColor;
	};

enum TData
	{
	ECoeControlParent = 0x0,
	ECoeControlObserver = 0x1,
	ECoeComponentArray = 0x2,
	ECoeLayoutManager = 0x3,
	ECoeControlBackground = 0x4,
	EMaximumWidthTInt = 0x5,
	EUniqueHandleTInt = 0x6,
	EColorOverrides = 0x7,
	EFocusObserverNotificationIdentifier = 0x8,
	ECoeControlHitTest = 0x9,
	EZoomWithType = 0xA,
	ECustomGc = 0xB,
	EFontProvider = 0xC,
	
	EMaxOptionlData = 0xF
	};

// CoeControlParent
inline CCoeControl* DoGetParent(const RCoeDynamicDataStorage& aData)
	{ return static_cast<CCoeControl*>(aData.Data(ECoeControlParent, NULL)); }

inline TInt DoSetParent(RCoeDynamicDataStorage& aData, CCoeControl* aParent) 
	{ return aData.SetData(ECoeControlParent, aParent); }

// Observer
inline MCoeControlObserver* DoGetObserver(const RCoeDynamicDataStorage& aData)
	{ return static_cast<MCoeControlObserver*>(aData.Data(ECoeControlObserver, NULL)); }

inline TInt DoSetObserver(RCoeDynamicDataStorage& aData, MCoeControlObserver* aObserver) 
	{ return aData.SetData(ECoeControlObserver, aObserver); }

// ComponentArray
inline CCoeControlArray* DoGetComponentArray(const RCoeDynamicDataStorage& aData)
	{ return static_cast<CCoeControlArray*>(aData.Data(ECoeComponentArray, NULL)); }

inline TInt DoSetComponentArray(RCoeDynamicDataStorage& aData, CCoeControlArray* aComponentArray) 
	{ return aData.SetData(ECoeComponentArray, aComponentArray); }

// LayoutManager
inline MCoeLayoutManager* DoGetLayoutManager(const RCoeDynamicDataStorage& aData)
	{ return static_cast<MCoeLayoutManager*>(aData.Data(ECoeLayoutManager, NULL)); }

inline TInt DoSetLayoutManager(RCoeDynamicDataStorage& aData, MCoeLayoutManager* aLayoutManager) 
	{ return aData.SetData(ECoeLayoutManager, aLayoutManager); }

// Background
inline const MCoeControlBackground* DoGetBackground(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<const MCoeControlBackground*>(aData.Data(ECoeControlBackground, NULL)); }

inline TInt DoSetBackground(RCoeDynamicDataStorage& aData, const MCoeControlBackground* aBackground) 
	{ return aData.SetData(ECoeControlBackground, const_cast<MCoeControlBackground*>(aBackground)); }

// Max width
inline TInt DoGetMaximumWidth(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<TInt>(aData.Data(EMaximumWidthTInt, NULL)); }

inline TInt DoSetMaximumWidth(RCoeDynamicDataStorage& aData, TInt aMaxWidth) 
	{ return aData.SetData(EMaximumWidthTInt, reinterpret_cast<TAny*>(aMaxWidth)); }

// Unique Id
inline TInt DoGetUniqueHandle(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<TInt>(aData.Data(EUniqueHandleTInt, reinterpret_cast<TAny*>(KErrNotFound))); }

inline TInt DoSetUniqueHandle(RCoeDynamicDataStorage& aData, TInt aUniqueHandle) 
	{ return aData.SetData(EUniqueHandleTInt, reinterpret_cast<TAny*>(aUniqueHandle)); }

// ColorOverrides
inline CArrayFix<SColorOverride>* DoGetColorOverrides(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<CArrayFix<SColorOverride>*>(aData.Data(EColorOverrides, NULL)); }

inline TInt DoSetColorOverrides(RCoeDynamicDataStorage& aData, CArrayFix<SColorOverride>* aColorOverrides) 
	{ return aData.SetData(EColorOverrides, static_cast<TAny*>(aColorOverrides)); }

// FocusObserverNotificationIdentifier
inline TInt DoGetFocusObserverNotificationIdentifier(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<TInt>(aData.Data(EFocusObserverNotificationIdentifier, NULL)); }

inline TInt DoSetFocusObserverNotificationIdentifier(RCoeDynamicDataStorage& aData, TInt aFocusObserverNotificationIdentifier) 
	{ return aData.SetData(EFocusObserverNotificationIdentifier, reinterpret_cast<TAny*>(aFocusObserverNotificationIdentifier)); }

// HitTest
inline const MCoeControlHitTest* DoGetHitTest(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<const MCoeControlHitTest*>(aData.Data(ECoeControlHitTest, NULL)); }

inline TInt DoSetHitTest(RCoeDynamicDataStorage& aData, const MCoeControlHitTest* aHitTest) 
	{ return aData.SetData(ECoeControlHitTest, const_cast<MCoeControlHitTest*>(aHitTest)); }

// ZoomWithType
inline TCoeZoomWithType* DoGetZoomWithType(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<TCoeZoomWithType*>(aData.Data(EZoomWithType, NULL)); }

inline TInt DoSetZoomWithType(RCoeDynamicDataStorage& aData, const TCoeZoomWithType* aZoomWithType) 
	{ return aData.SetData(EZoomWithType, const_cast<TCoeZoomWithType*>(aZoomWithType)); }

// CustomGc
inline CWindowGc* DoGetCustomGc(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<CWindowGc*>(aData.Data(ECustomGc, NULL)); }

inline TInt DoSetCustomGc(const RCoeDynamicDataStorage& aData, CWindowGc* aGc) 
	{ return const_cast<RCoeDynamicDataStorage&>(aData).SetData(ECustomGc, aGc); }

// FontProvider
inline const CCoeFontProvider* DoGetFontProvider(const RCoeDynamicDataStorage& aData)
	{ return reinterpret_cast<const CCoeFontProvider*>(aData.Data(EFontProvider, NULL)); }

inline TInt DoSetFontProvider(const RCoeDynamicDataStorage& aData, const CCoeFontProvider* aFontProvider) 
	{ return const_cast<RCoeDynamicDataStorage&>(aData).SetData(EFontProvider, const_cast<CCoeFontProvider*>(aFontProvider)); }

