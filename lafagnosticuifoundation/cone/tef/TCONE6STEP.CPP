// Copyright (c) 2005-2010 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests interface between container control and component controls.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include "TCone6Step.h"
#include <gdi.h>

/**   Constructor fo CCtlBase class.\n */

CCtlBase::CCtlBase()
	{
	}
	
/**
  Second phase constructor for CCtlBase Class.\n
  Creates a font for the default graphics device, based on the specified TFontSpec.\n
  Initiazes the screen font for the control.\n
*/	
void CCtlBase::ConstructL()
	{
	TFontSpec spec(_L("Arial"),240);
	iFont = iCoeEnv->CreateScreenFontL( spec ) ;
	}
/**   Destructor for CCtlBase class.\n */	

CCtlBase::~CCtlBase()
	{
 	iCoeEnv->ReleaseScreenFont(iFont);
	}
/**
  Writes the text "aText" on the control.\n
  Sets the font,pen colour,brush style used for writing the text.\n
  Draws the text uisng Draw Text function of Graphics context.\n
*/	
void CCtlBase::WriteName( CWindowGc& aGc, const TDesC& aText ) const 
	{
    TRect rect = Rect() ;
    rect.Shrink( 3, 3 ) ;
    aGc.UseFont( iFont ) ;
    TInt ascent = ( rect.iBr.iY - rect.iTl.iY-iFont->HeightInPixels() ) / 2 + iFont->AscentInPixels() ;
    aGc.SetPenColor( KRgbBlack ) ;
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
    aGc.DrawText( aText, rect, ascent, CGraphicsContext::ECenter ) ;	
	}
/**
  Draw function for the CCtlBase class.\n
  
*/	
void CCtlBase::DoDraw( CWindowGc& aGc, TRect aRect ) const
	{
	aGc.DrawRect( aRect ) ;
	aRect.Shrink( 1, 1 ) ;
	aGc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
	aGc.DrawRect( aRect ) ;
	WriteName( aGc, *iName ) ;
	}

/** 
  Constructor for CTestMCoeFocusObserver class.\n
*/
CTestMCoeFocusObserver::CTestMCoeFocusObserver(CCoeControl& aContainer) : iCtlContainer(aContainer)
	{
	}
/** 
  Destructor for CTestMCoeFocusObserver class.\n
*/
CTestMCoeFocusObserver::~CTestMCoeFocusObserver()
	{
	}

void CTestMCoeFocusObserver::HandleChangeInFocus()
	{
	}
/**
  Handles destruction of any control. It is called by framework if any control is destroyed.\n
  Accesses the component controls to make sure the components are not removed from
  CCoeControlArray before notifying the observer.\n
*/
void CTestMCoeFocusObserver::HandleDestructionOfFocusedItem()
	{
	TInt cnt = iCtlContainer.CountComponentControls();
	while(cnt--)
		{
		CCoeControl* child = iCtlContainer.ComponentControl(cnt);
		child->SetFocus(ETrue); // use control to make sure its not deleted
		}
	}

/**
  Constructor for the CCtlContainer class.\n
*/
CCtlContainer::CCtlContainer()
	{	
	}
/**
  Destructor for CCtlContainer class.\n
  Deletes the iName member variable.\n
*/	
CCtlContainer::~CCtlContainer()
	{
	// kids should be destroyed automatically	
	delete iName ;
	}
/**
  Second phase constructor for CCtlContainer class.\n
  Invokes the base class "CCtlBase" second phase constructor.\n
  Adds three  objects each of CCtlContainee class as component controls.\n
  The first two are added using a component Id while the same is not provided for the third control.\n
  The container control window is activated.\n
*/	
void CCtlContainer::ConstructL( const TDesC& aName )
	{
	CCtlBase::ConstructL() ;
	// construct the kids, add them to the array.	
	iName = aName.AllocL() ;
	CreateWindowL() ;
	InitComponentArrayL();
	
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	Components().AppendLC( child, KChildOneID ) ;
	child->ConstructL( _L("child1") ) ;
	CleanupStack::Pop( child ) ;

	child = new (ELeave) CCtlContainee ;
	Components().AppendLC( child, KChildTwoID ) ;
	child->ConstructL( _L("child2") ) ;
	CleanupStack::Pop( child ) ;
	
	CCtlContainee* temp = new (ELeave) CCtlContainee ;
	Components().AppendLC( temp ) ;
	temp ->ConstructL( _L("orphan") ) ;
	CleanupStack::Pop( temp ) ;	
	iOrphan = temp ;		
	
	ActivateL() ;
	}
/**
  Sets the size of the component objects based on the present size of the container window.\n
  Calculates the present size of the container control and also the number of component objects.\n
  Sets the component object dimensions accordingly.\n
*/	
void CCtlContainer::SizeChanged() 
	{
	// set the size of the children
	TRect rect = Rect() ;
	TSize size = rect.Size() ;
	TPoint tl = rect.iTl ;
	TInt childCount = CountComponentControls() ;
	if ( childCount > 0 )
		{
		size.iWidth = size.iWidth/childCount ;
		size.iHeight = size.iHeight/childCount ;
		CCoeControl* child ;
		for ( TInt ii = 0; ii < childCount ; ++ii )
			{
			child = ComponentControl( ii ) ;
			child->SetRect( TRect( tl, size ) ) ;
			tl.iX += size.iWidth ;
			tl.iY += size.iHeight ;
			}
		}
	}
/**
  Draw function to draw the container control.\n
  Gets a handle to the Windows Graphic context.\n
  Calculates the present dimensions of the control and invokes the DoDraw function.\n
*/
void CCtlContainer::Draw( const TRect& /*aRect*/ ) const
	{
	// get a graphics contect - outline the control
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushColor( KRgbBlue ) ;
	DoDraw( gc, rect ) ;
	}

/**
  @SYMTestCaseID UIF-TCone6Step-TestRemoveControlById
 
  @SYMPREQ
 
  @SYMTestCaseDesc Removes a component with Id KChildTwoID using API RemoveComponentById.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Removes a component control using Component Id.\n
  Removes a component with Id KChildTwoID using API RemoveComponentById.\n
  The API removes a component control from a component array.
  It also sets the component's parent to <code>NULL</code>.\n
  The component control is later deleted.\n
 
  @SYMTestExpectedResults : Boolean, True if Component control is deleted.\n
 
  @SYMTestType : CIT 
*/
TBool CCtlContainer::TestRemoveControlById() 
	{
	TBool seemsOK ;
	TInt count = CountComponentControls() ;
	CCoeControl* runt = NULL ;
	runt = Components().RemoveById( KChildTwoID ) ;

	seemsOK = ( ( runt != NULL ) && ( CountComponentControls() == (count - 1) )) ;

	// So far, so good.  This is a good time to test RemoveComponent() for non-existant
	if ( seemsOK )
		{
		TInt err =  Components().Remove( runt ) ; // should return KErrNotFound
		seemsOK = ( err == KErrNotFound ) ;
		}

	delete runt ;
	return seemsOK  ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestCleanupL
 
  @SYMPREQ
 
  @SYMTestCaseDesc The functions tests clean up after forced memory fail.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : The functions tests clean up after forced memory fail.\n
  The present number of component controls is obtained  using CountComponentControls.\n
  The next memory allocation is caused to fail using macro "__UHEAP_FAILNEXT".\n
  A new component is added using AddComponentByIdLC API.\n
  The number of component controls should remain the same after memory allocation failure also .\n
 
  @SYMTestExpectedResults : Boolean, True if Clean up is successful after memory allocation failure.\n
 
  @SYMTestType : CIT 
*/	
TBool CCtlContainer::TestCleanupL()
	{
	
	TBool seemsOK = EFalse ;
	 
	// Initial count of controls
	TInt count = CountComponentControls() ;	
	
	// Create a new control to add to the array
	CCtlContainee* child = NULL ;	
	child = new (ELeave) CCtlContainee ;
 
 	// Set memory allocation to fail 
	__UHEAP_MARK ;
	__UHEAP_SETFAIL((RHeap::EDeterministic),1);

 	// Expect addition of the control to the array to fail
	TRAPD(err, 
		{
		Components().AppendLC( child );
		CleanupStack::Pop(child);
		} );
  
   	// Re-align the heap
	__UHEAP_RESET ;
	__UHEAP_MARKEND ;

	// The no of controls should be the same as at the start 
	// as appending should have failed with KErrNoMemory
	seemsOK = ( (count == CountComponentControls()) && 
								(err == KErrNoMemory)) ;
 
	return seemsOK ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestGetControlL
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests the ability to obtain handle to the component control using Component Id.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Third component control is added using AddComponentByIdLC API with KChildThreeID as component ID.\n
  Later the ID is passed to ComponentById API which returns the pointer to the component control.\n
  The name of the control obtained  is verified against the one set.\n
 
  @SYMTestExpectedResults : Boolean, True if names match.\n
 
  @SYMTestType : CIT
*/
TBool CCtlContainer::TestGetControlL()
	{
	_LIT( KNameDes, "childx") ;
	// construct a control, add it.  Get one back.  is it the same one?
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	Components().AppendLC( child, KChildThreeID ) ;
	child->ConstructL( KNameDes ) ;
	CleanupStack::Pop( child ) ;
	
	CCoeControl* anotherChild = NULL ;
 	anotherChild = Components().ControlById<CCtlContainee>(KChildThreeID);
	TInt match = 1 ;
	if ( anotherChild )
		{
		match = KNameDes().Compare( static_cast<CCtlContainee*>(anotherChild)->WhoAmI() ) ;
		}
	return ( match == 0 ) ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestGetControlConstL
 
  @SYMPREQ
 
  @SYMTestCaseDesc Gets a constant handle to the component control.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Gets a constant handle to the component control.\n
  Handle to component with Id KChildThreeID is obtained using ComponentById API.\n
  The name of the control obtained  is verified against the KNameDes descriptor.\n
 
  @SYMTestExpectedResults : Boolean, True if names match.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestGetControlConstL()  const
	{ // dependant on TestGetControlL()
	_LIT( KNameDes, "childx") ;
 	const  CCtlContainee* anotherChild = NULL ;
 	anotherChild = Components().ControlById<CCtlContainee>(KChildThreeID);

	TInt match = 1 ;
	if ( anotherChild )
		{
		match = KNameDes().Compare((anotherChild)->WhoAmI() ) ;	
		}
	return ( match == 0 ) ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestGetUnknownControlConstL
 
  @SYMPREQ
 
  @SYMTestCaseDesc Gets a constant handle to the non existant component control .\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Component control with ID KChildTwoID does not exist.\n
  Handle to component with Id KChildTwoID is obtained using ComponentById API.\n
 
  @SYMTestExpectedResults : Boolean, True if obtained component control pointer is NULL.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestGetUnknownControlConstL() const 
	{ // dependant on TestGetControlL and TestRemoveControl which removes child2
	const CCoeControl* anotherChild = NULL ;
	anotherChild = Components().ControlById<CCoeControl>( KChildTwoID ) ; 
	return ( anotherChild == NULL ) ;
	}
	
/**
  @SYMTestCaseID UIF-TCone6Step-TestAddDuplicateControlL
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests adding a component control using an already used Id.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Tests adding a component control using an already used Id.\n
  A component is created and added with Id 'KChildThreeID' which is already used.\n
  
  @SYMTestExpectedResults : Boolean, True if addition of duplicate control fails.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestAddDuplicateControlL() 
	{
	_LIT( KNameDes, "childx") ;
	// construct a control, add it using an already used ID.  Dependant on TestGetControlL()
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	TInt err ;
	__UHEAP_MARK ;
	TRAP( err, Components().AppendLC( child, KChildThreeID ) ) ;
	__UHEAP_MARKEND ;
	if ( err == KErrNone )
		{
		child->ConstructL( KNameDes ) ;
		CleanupStack::Pop( child ) ;
		return EFalse ; // test failed
		}
	else 
		{
		return ETrue ; 
		}
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestRemoveNonExistantById
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests removal of a control using a non existant component ID.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Tests removal of a control using a non existant component ID.\n
  The number  of component controls is obtained uisng CountComponentControls.\n
  The a control with Id '99' which is non existant is removed using API 'RemoveComponentById'.\n
  
  @SYMTestExpectedResults : Boolean, True if the number of controls remains the same and object pointer returned by 
  RemoveComponentById is NULL.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestRemoveNonExistantById() 
	{
	TBool seemsOK ;
	TInt count = CountComponentControls() ;
	CCoeControl* runt = NULL ;
 
	runt = Components().RemoveById( 99 ) ;

	TInt postCount = CountComponentControls() ;
	seemsOK = ( ( runt == NULL ) && ( CountComponentControls() == count ) ) ;
	return seemsOK  ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestRemoveControlL
 
  @SYMPREQ
 
  @SYMTestCaseDesc  Tests removal of a control without using a control ID.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions :  Tests removal of a control without using a control ID.\n
  A new component control is created and is added to the container control using API 'AddComponentByIdLC'.\n
  The number of component controls is obtained using 'CountComponentControls' API.\n
  The newly added component control is removed using API 'RemoveComponent' passing the pointer as argument.\n
  
  @SYMTestExpectedResults : Boolean, True if RemoveComponent returns KErrNone and 
  number of component control is decreased by One.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestRemoveControlL() // See also TestRemoveControById()
	{
	_LIT( KNameDes, "child4") ;
	// construct a control, add it.  Remove it.  Is it removed?  
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	Components().AppendLC( child, KChildFourID ) ;
	child->ConstructL( KNameDes ) ;
	CleanupStack::Pop( child ) ;
	
	TInt count = CountComponentControls() ;
	TInt err =  Components().Remove( child ) ; // should return KErrNone
	TInt seemsOK = ( ( err == KErrNone ) && ( CountComponentControls() == (count - 1) )) ;
	
	delete child ;
	return seemsOK ;
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestGetUnsetUniqueHandle
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests getting a unique handle to a component control without prior setting.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Gets the handle to a component control with ID (KChildOneID).\n
  A unique handle(KUniqueId) is not set to the above control using 'SetUniqueHandle' API prior to calling the get function.\n
  
  @SYMTestExpectedResults : Boolean, True if the obtained handle is equal to Zero.\n
 
  @SYMTestType : CIT
*/
TBool CCtlContainer::TestGetUnsetUniqueHandle() 
	{
	// will panic in debug
	TInt  handle = Components().ControlById<CCoeControl>( KChildOneID )->UniqueHandle() ;
	// ignore error
	return ( handle == KErrNotFound ) ;

	}
//! Unique Id used to identify a component control.\n	
const TInt KUniqueId = 0x5AD ; 
/**
  @SYMTestCaseID UIF-TCone6Step-TestSetUniqueHandle
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests setting a unique handle to a component control.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Sets a Unique Handle( KUniqueId )to a component Control with ID( KChildOneID).\n
  
  @SYMTestExpectedResults : Boolean,True if SetUniqueHandle returns KErrNone.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestSetUniqueHandle()
	{
	TInt err = Components().ControlById<CCoeControl>( KChildOneID )->SetUniqueHandle( KUniqueId ) ;
	return ( err == KErrNone ) ; 
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestGetUniqueHandle
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests getting a unique handle to a component control.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Gets the handle to a component control with ID (KChildOneID).\n
  A unique handle(KUniqueId) is set to the above control using 'SetUniqueHandle' API prior to calling the get function.\n
  
  @SYMTestExpectedResults : Boolean, True if the obtained handle is equal to KUniqueId.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestGetUniqueHandle()
	{
	TInt handle = Components().ControlById<CCoeControl>( KChildOneID )->UniqueHandle() ;
	return ( handle == KUniqueId ) ; 
	}
/**
  @SYMTestCaseID UIF-TCone6Step-TestSetUniqueHandleOOM
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests Setting a unique handle to a component control with forced memory allocation failure.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : A new component control is created .\n
  The next memory allocation is caused to fail using macro '__UHEAP_FAILNEXT( 1 )'.\n
  A unique handle(KUniqueId) is set to the above control using 'SetUniqueHandle' API.\n
  
  @SYMTestExpectedResults : Boolean, True if SetUniqueHandle returns KErrNoMemory.\n
 
  @SYMTestType : CIT
*/	
TBool CCtlContainer::TestSetUniqueHandleOOM()
	{
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	child->SetContainerWindowL(*this);
	child->ActivateL();	// By activating the control its reserved memory is purged, so that the SetUniqueHandle() call can fail below.
	__UHEAP_MARK ;
	__UHEAP_FAILNEXT( 1 ) ;
	TInt err = child->SetUniqueHandle( KUniqueId ) ;
	__UHEAP_RESET ;
	__UHEAP_MARKEND ;
	delete child ;
	return ( err == KErrNoMemory ) ;
	}

// Check that we can still insert into the array even when OOM
TBool CCtlContainer::TestInsertAfter()
    {
    _LIT(KNameDes, "child3");
    CCtlContainee* child = NULL;
    TInt err;

    TRAP(err,
        {
        child = new (ELeave) CCtlContainee;
        child->ConstructL(KNameDes);
        });
    
    if(err ==KErrNone)
        {
        // Now check that the next insert succeeds even when OOM
        __UHEAP_FAILNEXT(1);
        
        TRAP(err,
            {
            Components().InsertAfterLC(KChildOneID, child, KChildFiveID);
            CleanupStack::Pop(child);
            });
            
        __UHEAP_RESET;
        
        if(err == KErrNone)
            {
            if(Components().At(1).iId == KChildFiveID)
                {
                return ETrue;   // Insert succeeded, test has passed
                }
            }
        }

    return EFalse;   // An error has occurred, fail the test
    }


//Tests the Insertion of the control after the last control using InsertAfterLC 
TBool CCtlContainer::TestInsertLast()
	{	
	_LIT(KNameDes, "child6");
	CCtlContainee* child = NULL;
	child = new (ELeave) CCtlContainee;
		
	TRAPD(err,
		{
		Components().InsertAfterLC(KChildOneID, child, KChildSixID);
		child->ConstructL(KNameDes);
		CleanupStack::Pop(child);
		});	
	if (err == KErrNone)
		{
		if (Components().At(3).iId == KChildSixID)
			{
			return ETrue;
			}
		else
			{
			return EFalse;
			}
		}
	else
		{
		return EFalse;
		}
	}

/**
  @SYMTestCaseID UIF-TCone6Step-TestFailingInsertAfter
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests that InsertAfterLC() works correctly when invalid reference component id is given.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Creates a child and tries to add it using invalid reference component id.\n
  
  @SYMTestExpectedResults : Boolean, True.\n
 
  @SYMTestType : CIT
*/		
TBool CCtlContainer::TestFailingInsertAfter()
	{
	__UHEAP_MARK;
	CCtlContainee* child = new(ELeave) CCtlContainee;
	TRAPD(err, Components().InsertAfterLC(KErrNotFound, child));
	__UHEAP_MARKEND;
	return (err == KErrNotFound);
	}

TBool CCtlContainer::TestId()
	{
	if (Components().Id(*Components().At(0).iControl) == KChildOneID)
		{
		return ETrue;
		}
	else
		{
		return EFalse;
		}
	}
	
TBool CCtlContainer::TestCursor()
	{
	CCoeControlArray::TCursor cursor = Components().Begin();
	CCoeControl* child = cursor.Control<CCoeControl>();
	// Check that begin points to the first control
	if (Components().Id(*child) != KChildOneID)
		{
		return EFalse;
		}
	// Check that next points to the second control
	// The test TestInsertAfter will have put the corresponding
	// control in the second position
	if (cursor.Next())
		{
		CCoeControl* child = cursor.Control<CCoeControl>();
		if (Components().Id(*child) != KChildFiveID)
			{
			return EFalse;
			}
		}
	else
		{
		return EFalse;
		}
	// Go back by one and check again
	if (cursor.Prev())
		{
		CCoeControl* child = cursor.Control<CCoeControl>();
		if (Components().Id(*child) != KChildOneID)
			{
			return EFalse;
			}
		}
	else
		{
		return EFalse;
		}
	
	// Check == and !=
	CCoeControlArray::TCursor cursor2 = Components().Begin();
	if (!(cursor == cursor2) || (cursor != cursor2))
		{
		return EFalse;
		}
	cursor.Next();
	if ((cursor == cursor2) || !(cursor != cursor2))
		{
		return EFalse;
		}
		
	return ETrue;
	}
	
TBool CCtlContainer::TestFind()
	{
	CCoeControlArray::TCursor cursor = Components().Find(KChildOneID);
	if (!cursor.IsValid())
		{
		return EFalse;
		}
	CCoeControl* control = Components().At(0).iControl;
	CCoeControlArray::TCursor cursor2 = Components().Find(control);
	if (!cursor2.IsValid())
		{
		return EFalse;
		}
	// Check that an inexistent id returns a "null" cursor
	CCoeControlArray::TCursor cursor3 = Components().Find(76765);
	if (cursor3.IsValid())
		{
		return EFalse;
		}
	// Check that an inexistent control returns a "null" cursor
	CCoeControl* dummyControl = new CCoeControl();
	CCoeControlArray::TCursor cursor4 = Components().Find(dummyControl);
	delete dummyControl;
	if (cursor4.IsValid())
		{
		return EFalse;
		}
	
	return ETrue;
	}

TBool CCtlContainer::TestSort()
	{
	//Removing the orphan control from array and deleting the control
	User::LeaveIfError(Components().Remove(iOrphan));
	delete iOrphan;
	iOrphan = 0;
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	Components().InsertAfterLC(KChildOneID, child, KChildTwoID);
	_LIT(KNameDes2, "child2");
	child->ConstructL(KNameDes2 ) ;
	CleanupStack::Pop( child ) ;

	//Creates an object of 'TLinearOrder'.
	TLinearOrder<TCoeControlWithId> order(CCtlContainer::CompareControls);

	//Sorts the controls stored in the object.
	//Before sorting the order of control in the array is 0, 1, 2.
	Components().Sort(order);
	
	TBool sorted=ETrue;
	
	//Checking whether the controls are sorted in descending order or not
	for(TInt i=0; i < Components().Count(); i++)
		{
		TInt k=Components().At(i).iId;
		if (Components().At(i).iId != Components().Count() - i -1)
			{
			sorted=EFalse;
			break;
			}
		}
	return sorted;
	}
TInt CCtlContainer::CompareControls(const TCoeControlWithId& aFirst, const TCoeControlWithId& aSecond)
	{
	//Algorithm to sort the controls in descending order based on the control id
	//It will return 1,0 or -1.
	return aSecond.iId - aFirst.iId;
	}
TBool CCtlContainer::TestRemove()
	{
	CCoeControlArray::TCursor cursor = Components().Find(KChildFiveID);
	if (!cursor.IsValid())
		{
		return EFalse;
		}
	CCoeControl* control = Components().Remove(cursor);
	if (!control)
		{
		return EFalse;
		}
	delete control;
	
	return ETrue;
	}
	
TBool CCtlContainer::TestReplace()
	{
	CCoeControlArray::TCursor cursor = Components().Find(KChildOneID);
	if (!cursor.IsValid())
		{
		return EFalse;
		}
	CCoeControl* ctrl = cursor.Control<CCoeControl>();
	CCtlContainee* child = new (ELeave) CCtlContainee;
	TInt err = Components().Replace(ctrl, child);
	if (err != KErrNone)
		{
		delete child;
		return EFalse;
		}
	delete ctrl;
	
	// Check replacement of inexistent control
	err = Components().Replace(ctrl, child);
	if (err != KErrNotFound)
		{
		return EFalse;
		}
	
	return ETrue;
	}
	
TBool CCtlContainer::TestSetArrayLocked()
	{
	Components().SetArrayLocked();
	if (!Components().IsArrayLocked())
		{
		return EFalse;
		}
	CCtlContainee* child = NULL ;
	child = new (ELeave) CCtlContainee ;
	TRAPD(err, Components().AppendLC(child, KChildOneID));
	if (err != KErrLocked)
		{
		return EFalse;
		}
	return ETrue;
	}

/**
  @SYMTestCaseID UIF-TCone6Step-TestOwnedExternally
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests that CCoeControlArray is behaving correctly when adding controls when they are owned externally.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Creates a child removes and deletes it.\n
  Creates a child and makes the cleanupstack item remove the child, and deletes the child.\n
  Tries to add a CCtlUnparentableContainee and deletes it.\n
  Creates a child and adds it using InsertAfterLC().\n
  Tries to add a child but using an invalid component id for InsertAfterLC().\n
  
  @SYMTestExpectedResults : Boolean, True.\n
 
  @SYMTestType : CIT
*/		
TBool CCtlContainer::TestOwnedExternally()
	{
	Components().ResetAndDestroy();
	Components().SetControlsOwnedExternally(ETrue);
	
	// Test InsertLC()
	
	//normal usage
	CCtlContainee* child = new(ELeave) CCtlContainee;
	CleanupStack::PushL(child);
	Components().AppendLC(child);
	CleanupStack::Pop(child);
	Components().Remove(child);
	CleanupStack::PopAndDestroy(child);

	//emulate leave
	child = new(ELeave) CCtlContainee;
	CleanupStack::PushL(child);
	Components().AppendLC(child);
	CleanupStack::PopAndDestroy(child); //"leave"
	CleanupStack::PopAndDestroy(child);
	if(Components().Find(child).IsValid()) return EFalse;
	
	//SetParent() is called before the cleanup stack is created
	//make sure there's no double deletion when the SetParent() call fails
	CCtlUnparentableContainee* childOfNoone = new(ELeave) CCtlUnparentableContainee;
	CleanupStack::PushL(childOfNoone);
	TRAP_IGNORE(Components().AppendLC(childOfNoone));
	CleanupStack::PopAndDestroy(childOfNoone);
	if(Components().Find(childOfNoone).IsValid()) return EFalse;
	
	// Test InsertAfterLC()
	
	//add a reference child
	CCtlContainee* firstChild = new(ELeave) CCtlContainee;
	CleanupStack::PushL(firstChild);
	Components().AppendLC(firstChild, KChildOneID);
	CleanupStack::Pop(firstChild);
	
	//insert successfully, remove by emulating leave
	child = new(ELeave) CCtlContainee;
	CleanupStack::PushL(child);
	Components().InsertAfterLC(KChildOneID, child);
	CleanupStack::PopAndDestroy(child); //"leave"
	CleanupStack::PopAndDestroy(child);
	if(Components().Find(child).IsValid()) return EFalse;
	
	//insert with invalid reference component id
	child = new(ELeave) CCtlContainee;
	CleanupStack::PushL(child);
	TRAP_IGNORE(Components().InsertAfterLC(KErrNotFound, child));
	CleanupStack::PopAndDestroy(child);
	if(Components().Find(child).IsValid()) return EFalse;
	
	//cleanup reference child
	Components().Remove(firstChild);
	CleanupStack::PopAndDestroy(firstChild);
	
	return (CountComponentControls() == 0);
	}

/**
  @SYMTestCaseID UIF-TCone6Step-TestHandleDestructionOfFocusedItemL
 
  @SYMDEF DEF087937 MMS: MMS Editor - Messaging crash using jog dial to scroll through message wh...
 
  @SYMTestCaseDesc Tests the CCoeControl's destructor notifies the observer before 
  CCoeControl's CCoeControlArray components are deleted and the array is shrinked.\n
  The observer should access CCoeControl::CountComponentsControl() and ComponentControl().\n
  
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : The parent control is created and two child controls are added to it.\n
  The parent control is registered with observer to get notification.\n
  Delete both parent control and observer.\n
  
  @SYMTestExpectedResults : The CCoeControl's destructor notifies the observer before deleting 
  and shrinking the CCoeCotrolArray.\n
  The observer accesses CoeControl::CountComponentsControl() and ComponentControl().
  
  @SYMTestType : CIT
*/
void CCtlContainer::TestHandleDestructionOfFocusedItemL()
	{
	CParentControl* parent = new (ELeave) CParentControl;
	CleanupStack::PushL(parent);
	parent->SetContainerWindowL(*this);
	parent->InitComponentArrayL();

	CCoeControl* child1 = new (ELeave) CCoeControl;
	parent->Components().AppendLC(child1) ;
	CleanupStack::Pop( child1 ); 
	
	CCoeControl* child2 = new (ELeave) CCoeControl;
	parent->Components().AppendLC(child2) ;
	CleanupStack::Pop( child2 );
	
	CTestMCoeFocusObserver* obs = new (ELeave) CTestMCoeFocusObserver(*parent) ;
	CleanupStack::PushL(obs);
	CCoeEnv::Static()->AddFocusObserverL(*obs);
	CleanupStack::Pop(obs);
	
	// set both focused to make the test independent of deletion order
	child1->SetFocus(ETrue);	
	child2->SetFocus(ETrue);
	
	// parent will delete its children
	// obs will be notified via HandleDestructionOfFocusedItem
	// obs will refer to deleted child1	
	CleanupStack::PopAndDestroy(parent);	
	CCoeEnv::Static()->RemoveFocusObserver(*obs);
	delete obs;
	}
	
CCtlContainee::CCtlContainee()
	{
	}
/**
  Destructor for CCtlContainee classused for creating component controls.\n
*/	
CCtlContainee::~CCtlContainee()
	{
	delete iName ;
	}
/**
  Second phase constructor for CCtlContainee classused for creating component controls.\n
  Invokes the base class second phase construtor.\n
  Allocates a string which contains the ID of the component control.\n
*/	
void CCtlContainee::ConstructL( const TDesC& aName )
	{
	CCtlBase::ConstructL() ;
	iName = aName.AllocL() ;
	}
/**
  Function to draw the component control.\n
  Obtains a handle to Windows Graphic Context.\n
  Sets the Brush colour and invokes the DoDraw function.\n
*/
void CCtlContainee::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushColor( KRgbYellow ) ;
	DoDraw( gc, rect ) ;
	}	
/**
  Returns the string associated with the component control.\n
 
  @return String associated with the control.\n
*/
const TDesC& CCtlContainee::WhoAmI() const
	{
	return *iName ;
	}


/** 
  Constructor for CCone6TestAppUi class.\n
  Sets the Test step Name.\n
*/
CCone6TestAppUi::CCone6TestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

/**
  Destructor for CCone6TestAppUi class.\n
*/
CCone6TestAppUi::~CCone6TestAppUi()
	{
	delete iContainer ;
	}

/**
  Second phase constructor for the CCone6TestAppUi class.\n
  Invokes the base class CTestCoeAppUi ConstructL function.\n
  Instantiates a container control object.\n
  Sets the container control's extent using CCoeControl::SetExtent API.\n
  Starts the asynchronous execution of tests using Auto test manager.\n
*/ 
void CCone6TestAppUi::ConstructL()
	{
	INFO_PRINTF1(_L("App UI ConstructL"));

	CTestCoeAppUi::ConstructL();
	
	ReinitializeContainerL();
		
	AutoTestManager().StartAutoTest();
	}
/**
  Makes sure the container is in its initial state.\n
  Must be called by tests that make the container change state so that following
  tests knows what to expect.
*/
void CCone6TestAppUi::ReinitializeContainerL()
	{
	delete iContainer;
	iContainer = NULL;
	
	iContainer = new (ELeave) CCtlContainer;
	
	iContainer->ConstructL( _L("Container") ) ;
	iContainer->SetExtent( TPoint(20,20),TSize(600,200) ) ;
	}

/**
  The function handles the key events received by CCone6Test AppUi.\n
  Exits the application in case Ctrl + E is received.\n
 
  @return TKeyResponse, Indicating whether the key event has been handled or not.\n
*/	
TKeyResponse CCone6TestAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyResponse ret=EKeyWasNotConsumed;
    	if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
	}

/**
  Auxilliary Function for all test cases.\n
  This function is iteratively called by the RunL function of the Autotestmanager
  asynchronously.\n
  Calls the following function\n
  1. Draw the container.\n
  2. Make the control invisible and invoke Draw.\n
  3. Make the control visible and invoke Draw.\n
  4. Test the cleanup after forced memory fail.\n
  5. Test removing a component control using Id.\n
  6. Test Getting a control using a component Id.\n
  7. Test Getting a const pointer to a control .\n
  8. Addition of a duplicate control.\n
  9. Removal of a non existant control.\n
  10. Unsetting a unique handle.\n
  11. Setting a unique handle.\n
  12. Getting a unique handle.\n
  
  25. Externally owned component controls.\n
  26. Failing InsertAfterLC().\n
*/
void CCone6TestAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	switch(aStepNum)
		{
		case 0 :
		case 1 :
			INFO_PRINTF1(_L("Test 6 case 1"));
			iContainer->DrawNow() ;
			break ;
		case 2 :
			INFO_PRINTF1(_L("Test 6: Case 2"));
			iContainer->MakeVisible( EFalse ) ;
			iContainer->DrawNow() ;
			break ;
		case 3 :
			INFO_PRINTF1(_L("Test 6: Case 3"));
			iContainer->MakeVisible( ETrue ) ;
			iContainer->DrawNow() ;
			break ;
		case 4 :
			INFO_PRINTF1(_L("Test 6: Case 4"));	 
#if defined( _DEBUG )
		TEST(iContainer->TestCleanupL());
#endif
			iContainer->DrawNow() ;
			break ;
		case 5 :
			SetTestStepID(_L("UIF-TCone6Step-TestRemoveControlById"));
			INFO_PRINTF1(_L("Test 6: Case 5"));
			TEST( iContainer->TestRemoveControlById() ) ;
			iContainer->DrawNow() ;
			RecordTestResultL();
			break ;
		case 6 :
			SetTestStepID(_L("UIF-TCone6Step-TestGetControlL"));
			INFO_PRINTF1(_L("Test 6: Case 6"));
			TEST( iContainer->TestGetControlL() ) ;
			RecordTestResultL();
			break ;
		case 7 :
			SetTestStepID(_L("UIF-TCone6Step-TestGetControlConstL"));
			INFO_PRINTF1(_L("Test 6: Case 7"));
			TEST( iContainer->TestGetControlConstL() ) ;
			RecordTestResultL();
			break ;	
		case 8 :
			SetTestStepID(_L("UIF-TCone6Step-TestGetUnknownControlConstL"));
			INFO_PRINTF1(_L("Test 6: Case 8"));
			TEST( iContainer->TestGetUnknownControlConstL() ) ;
			RecordTestResultL();
			break ;
		case 9 :
			SetTestStepID(_L("UIF-TCone6Step-TestAddDuplicateControlL"));
			INFO_PRINTF1(_L("Test 6: Case 9"));
	//		TEST( iContainer->TestAddDuplicateControlL() ) ;
			RecordTestResultL();
			break ;
		case 10 :
			SetTestStepID(_L("UIF-TCone6Step-TestRemoveNonExistantById"));
			INFO_PRINTF1(_L("Test 6: Case 10"));
			TEST( iContainer->TestRemoveNonExistantById() ) ;
			RecordTestResultL();
			break ;
		case 11 :
			SetTestStepID(_L("UIF-TCone6Step-TestRemoveControlL"));
			INFO_PRINTF1(_L("Test 6: Case 11"));
			TEST( iContainer->TestRemoveControlL() ) ;
			RecordTestResultL();
			break ;
		case 12 :
			SetTestStepID(_L("UIF-TCone6Step-TestGetUnsetUniqueHandle"));
			INFO_PRINTF1(_L("Test 6: Case 12"));
			TEST( iContainer->TestGetUnsetUniqueHandle() ) ;
			RecordTestResultL();
			break ;
		case 13 :
			SetTestStepID(_L("UIF-TCone6Step-TestSetUniqueHandle"));
			INFO_PRINTF1(_L("Test 6: Case 13"));
			TEST( iContainer->TestSetUniqueHandle() ) ;
			RecordTestResultL();
			break ;
		case 14 :
			SetTestStepID(_L("UIF-TCone6Step-TestGetUniqueHandle"));
			INFO_PRINTF1(_L("Test 6: Case 14"));
			TEST( iContainer->TestGetUniqueHandle() ) ;
			RecordTestResultL();
			break ;
		case 15 :
			INFO_PRINTF1(_L("Test 6: Case 15"));
			TEST( iContainer->TestInsertAfter());
			break;
		case 22 :
			INFO_PRINTF1(_L("Test 6: Case 22"));
			TEST( iContainer->TestInsertLast());
			break;		
		case 16 :
			INFO_PRINTF1(_L("Test 6: Case 16"));
			TEST( iContainer->TestId());
			break;
		case 17 :
			INFO_PRINTF1(_L("Test 6: Case 17"));
			TEST( iContainer->TestCursor());
			break;
		case 18 :
			INFO_PRINTF1(_L("Test 6: Case 18"));
			TEST( iContainer->TestFind());
			break;
		case 19 :
			INFO_PRINTF1(_L("Test 6: Case 19"));
			TEST( iContainer->TestRemove());
			break;
		case 20 :
			INFO_PRINTF1(_L("Test 6: Case 20"));
			TEST( iContainer->TestReplace());
			break;
		case 21 :
			INFO_PRINTF1(_L("Test 6: Case 21"));
			TEST( iContainer->TestSort());
			break ;
		case 23	:
			SetTestStepID(_L("UIF-TCone6Step-TestHandleDestructionOfFocusedItemL"));
			INFO_PRINTF1(_L("Test 6: Case 23"));
			TRAPD(ret,iContainer->TestHandleDestructionOfFocusedItemL());
			TEST(ret == KErrNone);
			RecordTestResultL();
			break;
		case 24 :
			INFO_PRINTF1(_L("Test 6: Case 24"));
#if defined( __WINS__ )
			TEST( iContainer->TestSetUniqueHandleOOM() ) ;
#else	// No memory failure testing on hardware because UREL
			TEST( ETrue) ;
#endif
			break ;
		case 25:
			SetTestStepID(_L("UIF-TCone6Step-TestOwnedExternally"));
			INFO_PRINTF1(_L("Test 6: Case 25"));
			TEST( iContainer->TestOwnedExternally() );
			ReinitializeContainerL();
			RecordTestResultL();
			break;
		case 26:
			SetTestStepID(_L("UIF-TCone6Step-TestFailingInsertAfter"));
			INFO_PRINTF1(_L("Test 6: Case 26"));
			TEST( iContainer->TestFailingInsertAfter() );
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		case 27 :
			INFO_PRINTF1(_L("Test 6: Case 27"));
			TEST( iContainer->TestSetArrayLocked());
			break;
		default :
			INFO_PRINTF1(_L("Test 6: Case default"));
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;

		}
	}


/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone6TestAppUi class which serves as a AppUi class.\n
  Sets the CCone6TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone6Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone6TestAppUi* appUi= new (ELeave) CCone6TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTCone6Step class.\n
  Sets the test step name.\n
*/
CTCone6Step::CTCone6Step()
	{
	SetTestStepName(KTCone6Step);
	}
/**
  Destructor for CTCone6Step class.\n
*/
CTCone6Step::~CTCone6Step()
{}

/**
  Entry function for CTCone6 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone5 Test application.\n
*/
TVerdict CTCone6Step::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test 6 Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;

	TRAPD(err,ConstructAppL(coe));

	if (!err)
		{
		coe->ExecuteD();
		}
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	REComSession::FinalClose();	

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


