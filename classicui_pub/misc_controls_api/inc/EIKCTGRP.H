/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKCTGRP_H__)
#define __EIKCTGRP_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#include <lafpublc.h>

class TEikGroupControl
	{
public:
	/** Constructor
	 */
	inline TEikGroupControl();
    /** Constructor
     */
	inline TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags);
public:
	CCoeControl* iControl;
	TInt iId;
	TInt iLongId;
public:
	/** IsLengthSet() whether length has been set
	 */
	inline TBool IsLengthSet() const;
    /** Length() returns value of the length
     */
	inline TInt Length() const;
    /** IsStretchable() whether controlgroup is stretchable
     */
	inline TBool IsStretchable() const;
    /** SetLength() sets the length
     */
	inline void SetLength(TInt aLength);
    /** SetStretchable() sets to be stretchable
     */
	inline void SetStretchable();
public:
	enum TControlFlags
		{
		ESetLength		=0x01,
		EAllowStretch	=0x02
		};
private:
	TInt iLength;
	TInt iFlags;
	};

class CEikControlGroup : public CEikBorderedControl
	{
friend class CTestControlGroup; // test code

// CEikCba made a friend to get at Orientation() private method
friend class CEikCba;
// -> 
public:
	enum TStartCorner
		{
		EFromTopLeft=SLafControlGroup::EFromTopLeft,
		EFromTopRight=SLafControlGroup::EFromTopRight,
		EFromBottomLeft=SLafControlGroup::EFromBottomLeft,
		EFromBottomRight=SLafControlGroup::EFromBottomRight
		};
	enum TOrientation
		{
		ELayHorizontally=SLafControlGroup::ELayHorizontally,
		ELayVertically	=SLafControlGroup::ELayVertically	
		};
public: // new functions
	/** Constructor
	 */
	IMPORT_C CEikControlGroup();
    /** Destructor
     */
	IMPORT_C ~CEikControlGroup();
    /** ConstructL() constructs the CEikControlGroup
     * @param aStart corner to start
     * @param aOrientation whether controlgroup is vertical or horizontal
     */
	IMPORT_C void ConstructL(TStartCorner aStart,TOrientation aOrientation);
	/** AddControlL() adds a new control to the controlgroup
	 * @param aControl control to be added
	 * @param aId id of the control
	 */
	IMPORT_C virtual void AddControlL(CCoeControl* aControl,TInt aId);
	/** AddControlL() adds new control to the controlgroup
     * @param aControlGroup a control and it's id packed into TEikGroupControl struct
	 */
	IMPORT_C virtual void AddControlL(TEikGroupControl& aGroupControl);
    /** InsertControlL() inserts a control to specific position
     * @param aGroupControl control and its id packed to a struct
     * @param aIndex index of the array where new control is to be inserted
     */
	IMPORT_C void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);
    /** DeleteControl() removes control from the group
     * @param aIndex at which position of the array to delete
     * @param aCount how many controls to delete
     */
	IMPORT_C void DeleteControl(TInt aIndex,TInt aCount);
    /** SetLengthInPixels() sets length of the control group in pixels
     * @param aLength length of the whole control group in pixels
     */
	IMPORT_C void SetLengthInPixels(TInt aLength);
    /** SetBreadthInPixels() sets width of the control group
     * @param aBreadth width of the control group
     */
	IMPORT_C void SetBreadthInPixels(TInt aBreadth);
    /** SetControlSpacing sets horizontal and vertical spacing
     * @param aHSpacing horizontal spacing between controls
     * @param aVSpacing vertical spacing between controls
     */
	IMPORT_C void SetControlSpacing(TInt aHSpacing,TInt aVSpacing);
    /** SetControlLayout sets control layout parameters
     * @param aStart start corner
     * @param aOrientation vertical or horizontal orientation
     */
	IMPORT_C void SetControlLayout(TStartCorner aStart,TOrientation aOrientation);
    /** SetNumberOfLines() sets number of lines of the control group
     * @param aNumLines number of lines
     * @param aDistributeEvenly whether controls distribute evenly to the group
     */
	IMPORT_C void SetNumberOfLines(TInt aNumLines,TBool aDistributeEvenly);
    /** SetControlsAllSameSize() sets all controls to be the same size
     */
	IMPORT_C void SetControlsAllSameSize();
    /** LayoutControls layouts the controls
     */
	IMPORT_C void LayoutControls();
    /** ControlById() fetches individual controls by id
     * @param aId id of the control
     */
	IMPORT_C CCoeControl* ControlById(TInt aId) const;
    /** IndexById() gets array index from id
     * @param aId id number of the control
     * @return index number to the array
     */
	IMPORT_C TInt IndexById(TInt aId) const;
    /** Reset() clears the control array
     */
	IMPORT_C void Reset();
    /** ControlId() finds id of the control based on CCoeCOntrol pointer
     * @param aControl control stored in a control group
     * @return id of the control
     */
	IMPORT_C TInt ControlId(CCoeControl* aControl) const;
    /** Control() returns CCoeControl pointer based on array index
     * @param aIndex index to the internal array
     * @return control in that position of the array
     */
	IMPORT_C CCoeControl* Control(TInt aIndex) const; // as requested by Bill
    /** ControlArray() access to the actual array representation
     * @return array
     */
	IMPORT_C CArrayFix<TEikGroupControl>* ControlArray() const;
    /** Orientation orientation of the control group
     * @return either horizontal or vertical orientation
     */
	IMPORT_C TOrientation Orientation() const;
	/** ControlSpacing() gets control's spacing
	 * @aHSpacing modifies variable to get horizontal spacing
	 * @aVSpacing modifies variable to get vertical spacing
     */
 	IMPORT_C void ControlSpacing(TInt& aHSpacing,TInt& aVSpacing) const;
public: // from CCoeControl
	/** MinimumSize() gets minimumsize
	 */
	IMPORT_C TSize MinimumSize();
    /** CountComponentControls returns component controls count
     */
    IMPORT_C TInt CountComponentControls() const;
    /** GetColorUseListL() sets the color use list of the control group
     */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
    /** HandleResourceChange() handles resource change event
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
    /** HandlePointerEventL() handles touch pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected:
	enum
		{
		EDistributeEvenly	=0x40,
		EAllSameSize		=0x80,
		EDisableMSKDrawing  =0x100
		};
protected: // from CCoeControl
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	// only used from CEikCba
	void SetMSKVisibility(TBool aEnable);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // new functions
	IMPORT_C TInt Adjacent(TInt aRow,TInt aColumn,TInt aCtrlIndex,TInt aTotalRows,TInt aTotalColumns) const;
	IMPORT_C TStartCorner StartCorner() const;
	IMPORT_C void DeleteAllComponents();
	IMPORT_C TSize ControlMinimumSize(TInt aIndex) const;
	IMPORT_C TInt ControlMinimumLength(TInt aIndex);
	IMPORT_C TSize LargestControlSize() const;
	IMPORT_C TBool DistributeEvenly() const;
	IMPORT_C TBool AllSameSize();
private: // from CCoeControl
    IMPORT_C void SizeChanged();
	IMPORT_C void Draw(const TRect& aRect) const;
protected:
	CArrayFix<TEikGroupControl>* iControlArray;
private:
	TInt iLayout;
	TInt iLines;
	TInt iHSpacing;
	TInt iVSpacing;
	TInt iBreadth;
	TInt iLength;
	TSize iLargestControl;
	};


inline TEikGroupControl::TEikGroupControl()
	{ iControl=NULL; iId=iFlags=iLength=0; }
inline TEikGroupControl::TEikGroupControl(CCoeControl* aControl,TInt aId,TInt aLength,TInt aFlags)
	: iControl(aControl),iId(aId),iLength(aLength),iFlags(aFlags)
	{}
inline TBool TEikGroupControl::IsLengthSet() const
	{ return iFlags&ESetLength; }
inline TInt TEikGroupControl::Length() const
	{ return iLength; }
inline TBool TEikGroupControl::IsStretchable() const
	{ return iFlags&EAllowStretch; }
inline void TEikGroupControl::SetLength(TInt aLength)
	{ iLength=aLength; iFlags|=ESetLength; }
inline void TEikGroupControl::SetStretchable()
	{ iFlags|=EAllowStretch; }

#endif
