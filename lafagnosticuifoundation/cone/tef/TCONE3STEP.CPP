// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests for Object provider mechanism.\n
// An interface that allows an object to be part of a network of object providers.
// The object provider mechanism can be used to find and access objects of a 
// given type, where the type is defined by a TTypeUid object. Object providers 
// may be arranged in a hierarchy, i.e. an object provider may have a parent-child 
// relationship with another object provider.
// An object provider must provide an implementation for the MopSupplyObject() 
// function and can choose to provide an implementation for the MopNext() function. 
// Typically, it will also have functionality to define who its parent is.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
 @test
*/

#include <e32std.h>
#include <coeaui.h>
#include <coemop.h>
#include "TCone3Step.h"
#include "statecon.h"


//				Object Tree

/**
					A
				   / \
				 /	  \
			   /		\
			 /			  \
			B				E
		  /   \			  /   \
		C		D		F		G

*/



/**   Destructor for Class CSquareObj.\n */

CSquareObj::~CSquareObj()
	{}

/**   Sets the parent object provider's class name.\n  */

void CSquareObj::SetParentClassName(TDesC& aName)
	{
	iName.Set( aName );
	}

TPtrC CSquareObj::GetParentClassName() const
	{
	return iName;
	}
//! A CBase Derived Class.\n

/**   The class is used to test the object provider mechanism.\n */

class CTriangleObj : public CBase
	{
public:
	DECLARE_TYPE_ID(0x10004C75)
    ~CTriangleObj();
	void SetParentClassName(TDesC& aName);
	TPtrC GetParentClassName()  const;
private:
	TPtrC	iName;
   };

/**   Destructor for class CTriangleObj.\n */
    
CTriangleObj::~CTriangleObj()
    {}

/**   Sets the Parent class name of CTriangleObj class to aName.\n */

void CTriangleObj::SetParentClassName(TDesC& aName)
	{
	iName.Set( aName );
	}
/**   Returns the Parent class name of CTriangleObj class.\n */
	
TPtrC CTriangleObj::GetParentClassName() const
	{
	return iName;
	}

/**   Destructor for class COctagonObj.\n */
  
COctagonObj::~COctagonObj()
    {}

/**   Sets the Parent class name of COctagonObj class to aName.\n */
void COctagonObj::SetParentClassName(TDesC& aName)
	{
	iName.Set( aName );
	}
/**   Returns the Parent class name of COctagonObj class.\n */		
TPtrC COctagonObj::GetParentClassName() const
	{
	return iName;
	}
//! A Class derived from CBase and MObjectProvider.\n

/**
  CObjectNode is an object provider implementing the MObjectProvider interface.\n
  MObjectProvider interface that allows an object to be part of a network of object providers.\n
  This class contains objects of classes CTriangleObj,CSquareObj and COctagonObj.\n
*/
class CObjectNode : public CBase, public MObjectProvider
	{
public:
	CObjectNode();
	CObjectNode(CTriangleObj* aTriangleObj, CSquareObj* aSquareObj, COctagonObj* aOctagonObj);
    ~CObjectNode();
	void SetMopParent(MObjectProvider* aParent);
	
	CTriangleObj* GetTriangleObject();	
	CTriangleObj* GetTriangleObjNoChaining();
	
	CSquareObj* GetSquareObject();
	CSquareObj* GetSquareObjNoChaining();
	
	COctagonObj* GetOctagonObject();
	COctagonObj* GetOctagonObjNoChaining();

protected: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	MObjectProvider* MopNext();
private:
	inline TTypeUid::Ptr SupplyMopObject(const TTypeUid aId);
public:
	//! Array to store objects linked through object provider mechanism.\n
	RPointerArray<CObjectNode> iArray;
private:
	//! Parent object provider.\n
	MObjectProvider* iMopParent;
	//! Pointer to the CTriangleObj returned searched by object provider mechanism.\n
	CTriangleObj* iTriangleObj;
	//! Pointer to the CSquareObj returned searched by object provider mechanism.\n	
	CSquareObj* iSquareObj;
	//! Pointer to the COctagonObj returned searched by object provider mechanism.\n	
	COctagonObj* iOctagonObj;
    };
/**   Default Constructor for CObjectNode class.\n */

CObjectNode::CObjectNode()
	{}
/**
  Three argument constructor for CObjectNode class.\n
  Initializes iTriangleObj,iSquareObj and iOctagonObj member objects.\n
*/
CObjectNode::CObjectNode(CTriangleObj* aTriangleObj, CSquareObj* aSquareObj, COctagonObj* aOctagonObj)
: iTriangleObj(aTriangleObj), iSquareObj(aSquareObj), iOctagonObj(aOctagonObj)
	{}
/**
  Destructor for CObjectNode class.\n
  Deletes the member objects of CTriangleObj,CSquareObj and COctagonObj classes.\n
*/
CObjectNode::~CObjectNode()
    {
	delete iTriangleObj;
	delete iSquareObj;
	delete iOctagonObj;

	iArray.ResetAndDestroy();
	iArray.Close();
    }

/**
 
  Support for the object provider mechanism is in the construction of 
  top-level controls in an application or view.\n
  Top level controls must have the view or app UI set as their object provider.\n
  The view or app UI does this by calling the control's SetMopParent() function.\n
*/
void CObjectNode::SetMopParent(MObjectProvider* aParent)
	{
	iMopParent = aParent;
	}
/**
  Gets the parent object provider.\n
  This is called by the private function MopGetById() when a call to MopGetObject()
  returns NULL.\n
  
*/
MObjectProvider* CObjectNode::MopNext()
	{
	return iMopParent;
	}
/**
  Gets an object whose type is encapsulated by the specified TTypeUid object.\n
  Calls the inline function SupplyMopObject .\n
*/
TTypeUid::Ptr CObjectNode::MopSupplyObject(TTypeUid aId)
	{
	return SupplyMopObject(aId);
	}
/**
  This function is called by the MopSupplyObject when there is a request
  to get an object whose type is encapsulated by the specified TTypeUid object.\n
  The type uid is compared with the Uids of the three component objects namely
  aTriangleObj,aSquareObj and aOctagonObj.\n
  If the Uid matches,pointer to the matched object is returned.\n
*/
inline TTypeUid::Ptr CObjectNode::SupplyMopObject(const TTypeUid aId)
	{
	if (iTriangleObj)
		{
		if(aId.iUid == CTriangleObj::ETypeId)
			{
			return aId.MakePtr(iTriangleObj);
			}
		}

	if (iSquareObj)
		{
		if(aId.iUid == CSquareObj::ETypeId)
			{
			return aId.MakePtr(iSquareObj);
			}
		}

	if (iOctagonObj)
		{
		if(aId.iUid == COctagonObj::ETypeId)
			{
			return aId.MakePtr(iOctagonObj);
			}
		}

	return TTypeUid::Null();
	}
/**
  The function tests the ability to get the triangle object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
CTriangleObj* CObjectNode::GetTriangleObject()
	{
	CTriangleObj* triangle = MopGetObject(triangle);
	return triangle;
	}
	
/**
  The function tests the ability to get the square object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
CSquareObj* CObjectNode::GetSquareObject()
	{
	CSquareObj* square = MopGetObject(square);
	return square;
	}
/**
  The function tests the ability to get the octagon object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
COctagonObj* CObjectNode::GetOctagonObject()
	{
	COctagonObj* octagon = MopGetObject(octagon);
	return octagon;
	}
	
/**
  The function tests the ability to get the triangle object pointer 
  using the Object provider mechanism without chaining.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
CTriangleObj* CObjectNode::GetTriangleObjNoChaining()
	{
	CTriangleObj* triangle = MopGetObjectNoChaining(triangle);
	return triangle;
	}
	
/**
  The function tests the ability to get the square object pointer 
  using the Object provider mechanism without chaining.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
CSquareObj* CObjectNode::GetSquareObjNoChaining()
	{
	CSquareObj* square = MopGetObjectNoChaining(square);
	return square;
	}
/**
  The function tests the ability to get the octagon object pointer 
  using the Object provider mechanism without chaining.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
COctagonObj* CObjectNode::GetOctagonObjNoChaining()
	{
	COctagonObj* octagon = MopGetObjectNoChaining(octagon);
	return octagon;
	}
	


//! A class derived from CBase and MObjectProvider interface.\n
/**
  The CObjectNodeConst tests the object provider mechanism by providing 
  a constant interface. All the Get functions are constant to ensure that no changes
  are made to the objects.\n
*/
class CObjectNodeConst : public CBase, public MObjectProvider
	{
public:
	CObjectNodeConst();
	CObjectNodeConst(const CTriangleObj* aTriangleObj, const CSquareObj* aSquareObj, const COctagonObj* aOctagonObj);
    ~CObjectNodeConst();
	void SetMopParent(MObjectProvider* aParent);
	
	const CTriangleObj* GetTriangleObject();
	const CTriangleObj* GetTriangleObjNoChaining();
	
	const CSquareObj* GetSquareObject();
	const CSquareObj* GetSquareObjNoChaining();
	
	const COctagonObj* GetOctagonObject();
	const COctagonObj* GetOctagonObjNoChaining();

protected: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	MObjectProvider* MopNext();
private:
	inline const TTypeUid::Ptr SupplyMopObject(TTypeUid aId);

public:
		//! Array to store objects linked through object provider mechanism.\n
	RPointerArray<CObjectNodeConst> iArray;
private:
	//! Parent object provider.\n
	MObjectProvider* iMopParent;
	//! Pointer to the CTriangleObj returned searched by object provider mechanism.\n
	const CTriangleObj* iTriangleObj;
	//! Pointer to the CSquareObj returned searched by object provider mechanism.\n
	const CSquareObj* iSquareObj;
	//! Pointer to the COctagonObj returned searched by object provider mechanism.\n
	const COctagonObj* iOctagonObj;
    };

/**   Default constructor for CObjectNodeConst class.\n */

CObjectNodeConst::CObjectNodeConst()
	{}
/**
  Three argument constructor for CObjectNodeConst class.\n
  Initializes iTriangleObj,iSquareObj and iOctagonObj member objects.\n
*/
CObjectNodeConst::CObjectNodeConst(const CTriangleObj* aTriangleObj, 
						 const CSquareObj* aSquareObj, 
						 const COctagonObj* aOctagonObj)
: iTriangleObj(aTriangleObj), iSquareObj(aSquareObj), iOctagonObj(aOctagonObj)
	{}
/**
  Destructor for CObjectNodeConst class.\n
  Deletes the iTriangleObj,iSquareObj and iOctagonObj objects.\n
*/
CObjectNodeConst::~CObjectNodeConst()
    {
	delete iTriangleObj;
	delete iSquareObj;
	delete iOctagonObj;

	iArray.ResetAndDestroy();
	iArray.Close();
    }

/**
  Sets the context - that is, the enclosing parent object - for this object.\n
*/
void CObjectNodeConst::SetMopParent(MObjectProvider* aParent)
	{
	iMopParent = aParent;
	}
/**
  Retrieves the parent object provider.\n
  This function may be overridden to continue the chain of object providers 
  which are to be asked to supply an object.\n
  This is called by the private function MopGetById() when a call to MopGetObject()
  returns NULL.\n
*/
MObjectProvider* CObjectNodeConst::MopNext()
	{
	return iMopParent;
	}
/**
  Gets an object whose type is encapsulated by the specified TTypeUid object.\n
  Calls the inline function SupplyMopObject .\n
*/
TTypeUid::Ptr CObjectNodeConst::MopSupplyObject(TTypeUid aId)
	{
	return SupplyMopObject(aId);
	}

/**
  This function is called by the MopSupplyObject when there is a request
  to get an object whose type is encapsulated by the specified TTypeUid object.\n
  The type uid is compared with the Uids of the three component objects namely
  aTriangleObj,aSquareObj and aOctagonObj.\n
  If the Uid matches,pointer to the matched object is returned.\n
*/
inline const TTypeUid::Ptr CObjectNodeConst::SupplyMopObject(TTypeUid aId)
	{
	if (iTriangleObj)
		{
		if(aId.iUid == CTriangleObj::ETypeId)
			{
			return aId.MakePtr(const_cast<CTriangleObj*>(iTriangleObj));
			}
		}

	if (iSquareObj)
		{
		if(aId.iUid == CSquareObj::ETypeId)
			{
			return aId.MakePtr(const_cast<CSquareObj*>(iSquareObj));
			}
		}

	if (iOctagonObj)
		{
		if(aId.iUid == COctagonObj::ETypeId)
			{
			return aId.MakePtr(const_cast<COctagonObj*>(iOctagonObj));
			}
		}

	return TTypeUid::Null();
	}

/**
  The function tests the ability to get the triangle object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/	
const CTriangleObj* CObjectNodeConst::GetTriangleObject()
	{
	const CTriangleObj* triangle = MopGetObject(triangle);
	return triangle;
	}
/**
  The function tests the ability to get the square object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/	
const CSquareObj* CObjectNodeConst::GetSquareObject()
	{
	const CSquareObj* square = MopGetObject(square);
	return square;
	}
/**
  The function tests the ability to get the octagon object pointer 
  using the Object provider mechanism.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
const COctagonObj* CObjectNodeConst::GetOctagonObject()
	{
	const COctagonObj* octagon = MopGetObject(octagon);
	return octagon;
	}
/**
  The function tests the ability to get the triangle object pointer 
  using the Object provider mechanism without chaining for constant functions.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/	
const CTriangleObj* CObjectNodeConst::GetTriangleObjNoChaining()
	{
	const CTriangleObj* triangle = MopGetObjectNoChaining(triangle);
	return triangle;
	}
/**
  The function tests the ability to get the square object pointer 
  using the Object provider mechanism without chaining for constant functions.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/	
const CSquareObj* CObjectNodeConst::GetSquareObjNoChaining()
	{
	const CSquareObj* square = MopGetObjectNoChaining(square);
	return square;
	}
/**
  The function tests the ability to get the octagon object pointer 
  using the Object provider mechanism without chaining for constant functions.\n
  The object will be supplied directly by this object provider, or NULL 
  will be returned, this function does not recurse through the object chain.\n
  The function calls MopGetObject passing a pointer reference.\n
*/
const COctagonObj* CObjectNodeConst::GetOctagonObjNoChaining()
	{
	const COctagonObj* octagon = MopGetObjectNoChaining(octagon);
	return octagon;
	}

/**   Single Argument Constructor for CCone3TestAppUi class.\n */

CCone3TestAppUi::CCone3TestAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}

/**   Destructor for CCone3TestAppUi class.\n */

CCone3TestAppUi::~CCone3TestAppUi()
	{}

 /**
  Second phase Constructor for CCone3TestAppUi class.\n
  Invokes the base class CTestCoeAppUi second phase constructor.\n
  Executes the testcases asynchronously using Autotest Manager.\n
*/
void CCone3TestAppUi::ConstructL()
    {
    CTestCoeAppUi::ConstructL();	
	AutoTestManager().StartAutoTest();
    }

/**
   @SYMTestCaseID UIF-TCone3Step-DoTestsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests the object provider mechanism
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Three types of component objects are created.\n
   a. Triangle object.\n
   b. Square Object.\n
   c. Octagon Object.\n
   Node objects instantiated from CObjectNode are created and a network
   is created using object provider mechanism.\n
   The details of the network are as follows.\n
   0. Node A - Contains Triangle A.\n
   1. Node B - Contains Square B.\n
   2. Node C - Contains Triangle C.\n
   3. Node D - Contains no component objects.\n
   4. Node E - Contains Triangle E and Octogen E as component objects.\n
   5. Node F - Contains Square F.\n
   6. Node G - Contains Triangle G.\n
   Parent-child relationships are set using SetMopParent at each node.\n
   Adds the pointers to above six object providers to iArray.\n
   Component objects are retrieved using GetMopObject() at every node.\n
   If the node does not have an object of particular type a search is made
   at the parent object provider also.\n
   These pointers are verified.\n  
  
   @SYMTestExpectedResults The pointers of component objects obtained should match 
   with the original objects.\n
  
   @SYMTestType : CIT 
 */
void CCone3TestAppUi::DoTestsL()
    {
	__UHEAP_MARK;

	TPtrC nodeA(_L("A"));
	TPtrC nodeB(_L("B"));
	TPtrC nodeC(_L("C"));
	TPtrC nodeE(_L("E"));
	TPtrC nodeF(_L("F"));
	TPtrC nodeG(_L("G"));

	CTriangleObj* triangleA = new(ELeave) CTriangleObj();
	triangleA->SetParentClassName(nodeA);

	CSquareObj* squareB = new(ELeave) CSquareObj();
	squareB->SetParentClassName(nodeB);

	CTriangleObj* triangleC = new(ELeave) CTriangleObj();
	triangleC->SetParentClassName(nodeC);

	CTriangleObj* triangleE = new(ELeave) CTriangleObj();
	triangleE->SetParentClassName(nodeE);

	COctagonObj* octagonE = new(ELeave) COctagonObj() ;
	octagonE->SetParentClassName(nodeE);

	CSquareObj* squareF = new(ELeave) CSquareObj();
	squareF->SetParentClassName(nodeF);

	CTriangleObj* triangleG = new(ELeave) CTriangleObj();
	triangleG->SetParentClassName(nodeG);
	
	CObjectNode* node = new (ELeave) CObjectNode();
	CleanupStack::PushL(node);

	node->iArray.Append(new (ELeave) CObjectNode(triangleA, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(NULL, squareB, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(triangleE, NULL, octagonE));

	node->iArray.Append(new (ELeave) CObjectNode(triangleC, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(NULL, NULL, NULL));

	node->iArray.Append(new (ELeave) CObjectNode(NULL, squareF, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(triangleG, NULL, NULL));

	node->iArray[1]->SetMopParent(node->iArray[0]);
	node->iArray[2]->SetMopParent(node->iArray[0]);

	node->iArray[3]->SetMopParent(node->iArray[1]);
	node->iArray[4]->SetMopParent(node->iArray[1]);

	node->iArray[5]->SetMopParent(node->iArray[2]);
	node->iArray[6]->SetMopParent(node->iArray[2]);


	//Node0 - A
	CTriangleObj*	getTriangle = NULL;
	CSquareObj*		getSquare = NULL;
	COctagonObj*	getOctagon = NULL;
	INFO_PRINTF1(_L("Testing Node A"));
	getTriangle = node->iArray[0]->GetTriangleObject();
	getSquare	= node->iArray[0]->GetSquareObject();
	getOctagon	= node->iArray[0]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node B"));
	//Node1 - B
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[1]->GetTriangleObject();
	getSquare	= node->iArray[1]->GetSquareObject();
	getOctagon	= node->iArray[1]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node C"));
	//Node3 - C
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[3]->GetTriangleObject();
	getSquare	= node->iArray[3]->GetSquareObject();
	getOctagon	= node->iArray[3]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeC) == KErrNone);
	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node D"));
	//Node4 - D
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[4]->GetTriangleObject();
	getSquare	= node->iArray[4]->GetSquareObject();
	getOctagon	= node->iArray[4]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node E"));
	//Node2 - E
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[2]->GetTriangleObject();
	getSquare	= node->iArray[2]->GetSquareObject();
	getOctagon	= node->iArray[2]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);

	INFO_PRINTF1(_L("Testing Node F"));
	//Node5 - F
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[5]->GetTriangleObject();
	getSquare	= node->iArray[5]->GetSquareObject();
	getOctagon	= node->iArray[5]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeF) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);

	INFO_PRINTF1(_L("Testing Node G"));
	//Node6 - G
	getTriangle = NULL;
	getSquare	= NULL;
	getOctagon	= NULL;	
	
	getTriangle = node->iArray[6]->GetTriangleObject();
	getSquare	= node->iArray[6]->GetSquareObject();
	getOctagon	= node->iArray[6]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeG) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);
	
	CleanupStack::PopAndDestroy(); // node

//	test.Printf(_L("TEST COMPLETE [Press any key]"));
	__UHEAP_MARKEND;
    }
/**
   @SYMTestCaseID UIF-TCone3Step-DoMopConstTestsL
  
   @SYMPREQ 
 
   @SYMTestCaseDesc Tests the object provider mechanism using constant Mop functions.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Three types of component objects are created.\n
   a. Triangle object.\n
   b. Square Object.\n
   c. Octagon Object.\n
   Node objects instantiated from CObjectNode are created and a network
   is created using object provider mechanism.\n
   The details of the network are as follows.\n
   0. Node A - Contains Triangle A.\n
   1. Node B - Contains Square B.\n
   2. Node C - Contains Triangle C.\n
   3. Node D - Contains no component objects.\n
   4. Node E - Contains Triangle E and Octogen E as component objects.\n
   5. Node F - Contains Square F.\n
   6. Node G - Contains Triangle G.\n
   Parent-child relationships are set using SetMopParent at each node.\n
   Adds the pointers to above six object providers to iArray.\n
   Component objects are retrieved using GetMopObject() at every node.\n
   If the node does not have an object of particular type a search is made
   at the parent object provider also.\n
   These pointers are verified.\n  
  
   @SYMTestExpectedResults The pointers of component objects obtained should match 
   with the original objects.\n
   
 */    

void CCone3TestAppUi::DoMopConstTestsL()
    {
	__UHEAP_MARK;

	TPtrC nodeA(_L("A"));
	TPtrC nodeB(_L("B"));
	TPtrC nodeC(_L("C"));
	TPtrC nodeE(_L("E"));
	TPtrC nodeF(_L("F"));
	TPtrC nodeG(_L("G"));

	CObjectNodeConst* node = new (ELeave) CObjectNodeConst();
	CleanupStack::PushL(node);

	const CTriangleObj* triangleA = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleA))->SetParentClassName(nodeA);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleA));

	const CSquareObj* squareB = new(ELeave) CSquareObj();
	(const_cast<CSquareObj*>(squareB))->SetParentClassName(nodeB);
	CleanupStack::PushL(const_cast<CSquareObj*>(squareB));

	const CTriangleObj* triangleC = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleC))->SetParentClassName(nodeC);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleC));

	const CTriangleObj* triangleE = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleE))->SetParentClassName(nodeE);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleE));
	

	const COctagonObj* octagonE = new(ELeave) COctagonObj() ;
	(const_cast<COctagonObj*>(octagonE))->SetParentClassName(nodeE);
	CleanupStack::PushL(const_cast<COctagonObj*>(octagonE));

	const CSquareObj* squareF = new(ELeave) CSquareObj();
	(const_cast<CSquareObj*>(squareF))->SetParentClassName(nodeF);
	CleanupStack::PushL(const_cast<CSquareObj*>(squareF));

	const CTriangleObj* triangleG = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleG))->SetParentClassName(nodeG);
	
	CleanupStack::Pop(6);

	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleA, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, squareB, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleE, NULL, octagonE));

	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleC, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, NULL, NULL));

	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, squareF, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleG, NULL, NULL));

	node->iArray[1]->SetMopParent(node->iArray[0]);
	node->iArray[2]->SetMopParent(node->iArray[0]);

	node->iArray[3]->SetMopParent(node->iArray[1]);
	node->iArray[4]->SetMopParent(node->iArray[1]);

	node->iArray[5]->SetMopParent(node->iArray[2]);
	node->iArray[6]->SetMopParent(node->iArray[2]);


	//Node0 - A
	const CTriangleObj*	getTriangle = NULL;
	const CSquareObj*		getSquare = NULL;
	const COctagonObj*	getOctagon = NULL;
	INFO_PRINTF1(_L("Testing Node A Const"));
	getTriangle = node->iArray[0]->GetTriangleObject();
	getSquare	= node->iArray[0]->GetSquareObject();
	getOctagon	= node->iArray[0]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node B Const"));
	//Node1 - B
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[1]->GetTriangleObject();
	getSquare	= node->iArray[1]->GetSquareObject();
	getOctagon	= node->iArray[1]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node C Const"));
	//Node3 - C
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[3]->GetTriangleObject();
	getSquare	= node->iArray[3]->GetSquareObject();
	getOctagon	= node->iArray[3]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeC) == KErrNone);
	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node D Const"));
	//Node4 - D
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[4]->GetTriangleObject();
	getSquare	= node->iArray[4]->GetSquareObject();
	getOctagon	= node->iArray[4]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node E Const"));
	//Node2 - E
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[2]->GetTriangleObject();
	getSquare	= node->iArray[2]->GetSquareObject();
	getOctagon	= node->iArray[2]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);

	INFO_PRINTF1(_L("Testing Node F Const"));
	//Node5 - F
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[5]->GetTriangleObject();
	getSquare	= node->iArray[5]->GetSquareObject();
	getOctagon	= node->iArray[5]->GetOctagonObject();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeF) == KErrNone);
	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);

	INFO_PRINTF1(_L("Testing Node G Const"));
	//Node6 - G
	getTriangle = NULL;
	getSquare	= NULL;
	getOctagon	= NULL;	
	
	getTriangle = node->iArray[6]->GetTriangleObject();
	getSquare	= node->iArray[6]->GetSquareObject();
	getOctagon	= node->iArray[6]->GetOctagonObject();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeG) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);
	
	CleanupStack::PopAndDestroy(); // node

//	test.Printf(_L("TEST COMPLETE [Press any key]"));
	__UHEAP_MARKEND;
    }
    
/**
   @SYMTestCaseID UIF-TCone3Step-DoMopNoChainingTestsL
 
   @SYMPREQ
  
   @SYMTestCaseDesc Tests the object provider mechanism without no chaining.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Three types of component objects are created.\n
   a. Triangle object.\n
   b. Square Object.\n
   c. Octagon Object.\n
   Node objects instantiated from CObjectNode are created and a network
   is created using object provider mechanism.\n
   The details of the network are as follows.\n
   0. Node A - Contains Triangle A.\n
   1. Node B - Contains Square B.\n
   2. Node C - Contains Triangle C.\n
   3. Node D - Contains no component objects.\n
   4. Node E - Contains Triangle E and Octogen E as component objects.\n
   5. Node F - Contains Square F.\n
   6. Node G - Contains Triangle G.\n
   Parent-child relationships are set using SetMopParent at each node.\n
   Adds the pointers to above six object providers to iArray.\n
   Component objects are retrieved using GetMopObject() at every node.\n
   If the node does not have an object of particular type a search is made
   at the parent object provider also.\n
   These pointers are verified.\n  
  
   @SYMTestExpectedResults The pointers of component objects obtained should match 
   with the original objects.\n
 
   @SYMTestType : CIT 
 */
void CCone3TestAppUi::DoMopNoChainingTestsL()
	{
	__UHEAP_MARK;

	TPtrC nodeA(_L("A"));
	TPtrC nodeB(_L("B"));
	TPtrC nodeC(_L("C"));
	TPtrC nodeE(_L("E"));
	TPtrC nodeF(_L("F"));
	TPtrC nodeG(_L("G"));

	CObjectNode* node = new (ELeave) CObjectNode();
	CleanupStack::PushL(node);

	CTriangleObj* triangleA = new(ELeave) CTriangleObj();
	triangleA->SetParentClassName(nodeA);
	CleanupStack::PushL(triangleA);

	CSquareObj* squareB = new(ELeave) CSquareObj();
	squareB->SetParentClassName(nodeB);
	CleanupStack::PushL(squareB);

	CTriangleObj* triangleC = new(ELeave) CTriangleObj();
	triangleC->SetParentClassName(nodeC);
	CleanupStack::PushL(triangleC);

	CTriangleObj* triangleE = new(ELeave) CTriangleObj();
	triangleE->SetParentClassName(nodeE);
	CleanupStack::PushL(triangleE);
	

	COctagonObj* octagonE = new(ELeave) COctagonObj() ;
	octagonE->SetParentClassName(nodeE);
	CleanupStack::PushL(octagonE);

	CSquareObj* squareF = new(ELeave) CSquareObj();
	squareF->SetParentClassName(nodeF);
	CleanupStack::PushL(squareF);

	CTriangleObj* triangleG = new(ELeave) CTriangleObj();
	triangleG->SetParentClassName(nodeG);
	
	CleanupStack::Pop(6, triangleA);
	node->iArray.Append(new (ELeave) CObjectNode(triangleA, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(NULL, squareB, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(triangleE, NULL, octagonE));

	node->iArray.Append(new (ELeave) CObjectNode(triangleC, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(NULL, NULL, NULL));

	node->iArray.Append(new (ELeave) CObjectNode(NULL, squareF, NULL));
	node->iArray.Append(new (ELeave) CObjectNode(triangleG, NULL, NULL));

	node->iArray[1]->SetMopParent(node->iArray[0]);
	node->iArray[2]->SetMopParent(node->iArray[0]);

	node->iArray[3]->SetMopParent(node->iArray[1]);
	node->iArray[4]->SetMopParent(node->iArray[1]);

	node->iArray[5]->SetMopParent(node->iArray[2]);
	node->iArray[6]->SetMopParent(node->iArray[2]);

	//Node0 - A
	CTriangleObj*	getTriangle = NULL;
	CSquareObj*		getSquare = NULL;
	COctagonObj*	getOctagon = NULL;
	INFO_PRINTF1(_L("Testing Node A No Chaining"));
	getTriangle = node->iArray[0]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[0]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[0]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node B No Chaining"));
	//Node1 - B
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[1]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[1]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[1]->GetOctagonObjNoChaining();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node C No Chaining"));
	//Node3 - C
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[3]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[3]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[3]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeC) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node D No Chaining"));
	//Node4 - D
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[4]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[4]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[4]->GetOctagonObjNoChaining();

	TEST(getSquare == NULL);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node E No Chaining"));
	//Node2 - E
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[2]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[2]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[2]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);

	INFO_PRINTF1(_L("Testing Node F No Chaining"));
	//Node5 - F
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[5]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[5]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[5]->GetOctagonObjNoChaining();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeF) == KErrNone);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node G No Chaining"));
	//Node6 - G
	getTriangle = NULL;
	getSquare	= NULL;
	getOctagon	= NULL;	
	
	getTriangle = node->iArray[6]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[6]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[6]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeG) == KErrNone);
	TEST(getOctagon == NULL);
	TEST(getSquare == NULL);
	
	CleanupStack::PopAndDestroy(node);

	__UHEAP_MARKEND;
	
	}

/**
   @SYMTestCaseID UIF-TCone3Step-DoMopNoChainingConstTestsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests the object provider mechanism without no chaining 
   and using constant functions only.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Three types of component objects are created.\n
   a. Triangle object.\n
   b. Square Object.\n
   c. Octagon Object.\n
   Node objects instantiated from CObjectNode are created and a network
   is created using object provider mechanism.\n
   The details of the network are as follows.\n
   0. Node A - Contains Triangle A.\n
   1. Node B - Contains Square B.\n
   2. Node C - Contains Triangle C.\n
   3. Node D - Contains no component objects.\n
   4. Node E - Contains Triangle E and Octogen E as component objects.\n
   5. Node F - Contains Square F.\n
   6. Node G - Contains Triangle G.\n
   Parent-child relationships are set using SetMopParent at each node.\n
   Adds the pointers to above six object providers to iArray.\n
   Component objects are retrieved using GetMopObject() at every node.\n
   If the node does not have an object of particular type a search is made
   at the parent object provider also.\n
   These pointers are verified.\n  
  
   @SYMTestExpectedResults The pointers of component objects obtained should match 
   with the original objects.\n
  
   @SYMTestType : CIT 
 */
void CCone3TestAppUi::DoMopNoChainingConstTestsL()
	{
	__UHEAP_MARK;

	TPtrC nodeA(_L("A"));
	TPtrC nodeB(_L("B"));
	TPtrC nodeC(_L("C"));
	TPtrC nodeE(_L("E"));
	TPtrC nodeF(_L("F"));
	TPtrC nodeG(_L("G"));

	CObjectNodeConst* node = new (ELeave) CObjectNodeConst();
	CleanupStack::PushL(node);

	const CTriangleObj* triangleA = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleA))->SetParentClassName(nodeA);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleA));

	const CSquareObj* squareB = new(ELeave) CSquareObj();
	(const_cast<CSquareObj*>(squareB))->SetParentClassName(nodeB);
	CleanupStack::PushL(const_cast<CSquareObj*>(squareB));

	const CTriangleObj* triangleC = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleC))->SetParentClassName(nodeC);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleC));

	const CTriangleObj* triangleE = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleE))->SetParentClassName(nodeE);
	CleanupStack::PushL(const_cast<CTriangleObj*>(triangleE));
	

	const COctagonObj* octagonE = new(ELeave) COctagonObj() ;
	(const_cast<COctagonObj*>(octagonE))->SetParentClassName(nodeE);
	CleanupStack::PushL(const_cast<COctagonObj*>(octagonE));

	const CSquareObj* squareF = new(ELeave) CSquareObj();
	(const_cast<CSquareObj*>(squareF))->SetParentClassName(nodeF);
	CleanupStack::PushL(const_cast<CSquareObj*>(squareF));

	const CTriangleObj* triangleG = new(ELeave) CTriangleObj();
	(const_cast<CTriangleObj*>(triangleG))->SetParentClassName(nodeG);
	
	CleanupStack::Pop(6);

	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleA, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, squareB, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleE, NULL, octagonE));

	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleC, NULL, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, NULL, NULL));

	node->iArray.Append(new (ELeave) CObjectNodeConst(NULL, squareF, NULL));
	node->iArray.Append(new (ELeave) CObjectNodeConst(triangleG, NULL, NULL));

	node->iArray[1]->SetMopParent(node->iArray[0]);
	node->iArray[2]->SetMopParent(node->iArray[0]);

	node->iArray[3]->SetMopParent(node->iArray[1]);
	node->iArray[4]->SetMopParent(node->iArray[1]);

	node->iArray[5]->SetMopParent(node->iArray[2]);
	node->iArray[6]->SetMopParent(node->iArray[2]);

	//Node0 - A
	const CTriangleObj*	getTriangle = NULL;
	const CSquareObj*		getSquare = NULL;
	const COctagonObj*	getOctagon = NULL;
	INFO_PRINTF1(_L("Testing Node A No Chaining Const"));
	getTriangle = node->iArray[0]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[0]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[0]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeA) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node B No Chaining Const"));
	//Node1 - B
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[1]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[1]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[1]->GetOctagonObjNoChaining();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeB) == KErrNone);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node C No Chaining Const"));
	//Node3 - C
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[3]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[3]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[3]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeC) == KErrNone);
	TEST(getSquare == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node D No Chaining Const"));
	//Node4 - D
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[4]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[4]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[4]->GetOctagonObjNoChaining();

	TEST(getSquare == NULL);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node E No Chaining Const"));
	//Node2 - E
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[2]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[2]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[2]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getOctagon != NULL);
	TEST(getOctagon->GetParentClassName().Compare(nodeE) == KErrNone);
	TEST(getSquare == NULL);

	INFO_PRINTF1(_L("Testing Node F No Chaining Const"));
	//Node5 - F
	getTriangle = NULL;
	getSquare = NULL;
	getOctagon = NULL;	
	
	getTriangle = node->iArray[5]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[5]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[5]->GetOctagonObjNoChaining();

	TEST(getSquare != NULL);
	TEST(getSquare->GetParentClassName().Compare(nodeF) == KErrNone);
	TEST(getTriangle == NULL);
	TEST(getOctagon == NULL);

	INFO_PRINTF1(_L("Testing Node G No Chaining Const"));
	//Node6 - G
	getTriangle = NULL;
	getSquare	= NULL;
	getOctagon	= NULL;	
	
	getTriangle = node->iArray[6]->GetTriangleObjNoChaining();
	getSquare	= node->iArray[6]->GetSquareObjNoChaining();
	getOctagon	= node->iArray[6]->GetOctagonObjNoChaining();

	TEST(getTriangle != NULL);
	TEST(getTriangle->GetParentClassName().Compare(nodeG) == KErrNone);
	TEST(getOctagon == NULL);
	TEST(getSquare == NULL);
	
	CleanupStack::PopAndDestroy(node);

	__UHEAP_MARKEND;
	
	}

/**
   @SYMTestCaseID UIF-CONE-DoStateObserverTestL

   @SYMCR CR1251

   @SYMTestCaseDesc Tests calling MakeVisible or SetDimmed calls the new Mop interface
   when only the control itself provides the relevant Mop interface

   @SYMTestPriority High

   @SYMTestStatus Implemented

   @SYMTestActions Makes many calls to MakeVisible or SetDimmed in different situations 
   and checks if the new Mop interface is called or not on each time.

   @SYMTestExpectedResults The new interface is called if there is a change in the controls state

   @SYMTestType : Unit Test
 */
void CCone3TestAppUi::DoStateObserverTestL()
	{
	//Creating the first font allocates memory that is never deleted so must do this outside heap checks
	CFbsFont* font=iCoeEnv->CreateScreenFontL(CStateObserverControl::iFontSpec);
	iCoeEnv->ReleaseScreenFont(font);
	__UHEAP_MARK;
	CStateObserverControl* stateObCnt=new(ELeave) CStateObserverControl();
	CleanupStack::PushL(stateObCnt);
	stateObCnt->ConstructL();
	stateObCnt->SetReturnObserver(CStateObserverControl::EObserver);
	stateObCnt->SetRecievers(ETrue,EFalse);
	TInt failAt=stateObCnt->DoTest();
	CleanupStack::PopAndDestroy(stateObCnt);
	if (failAt>0)
		{
		TEST(EFalse);
		_LIT(KLog,"StateObserverTest failed on subtest: %d");
		INFO_PRINTF2(KLog,failAt);
		}
	__UHEAP_MARKEND;
	}

/**
   Auxiliary Function for all Test Cases.\n
 
   The method is an override from CTestCoeAppUi.\n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Calls the following functions one by one.\n
   1. DoTestsL().\n
   2. DoMopConstTestsL().\n
   3. DoMopNoChainingTestsL().\n
   4. DoMopNoChainingConstTestsL().\n
   5. DoStateObserverTestL().
 */
void CCone3TestAppUi::RunTestStepL(TInt aStepNum)
	{
	_LIT(KTest1,"Tests Mop interface returns right object");
	_LIT(KTest2,"Tests MCoeControlStateObserver is called at the right times");
	switch(aStepNum)
		{
		case 1:
			SetTestStepID(_L("UIF-TCone3Step-DoMopNoChainingConstTestsL"));			
			INFO_PRINTF1(KTest1);
			DoTestsL();
			DoMopConstTestsL();
			DoMopNoChainingTestsL();
			DoMopNoChainingConstTestsL();
			RecordTestResultL();			
			break;
		case 2:
			SetTestStepID(_L("UIF-CONE-DoStateObserverTestL"));			
			INFO_PRINTF1(KTest2);
			DoStateObserverTestL();
			RecordTestResultL();	
			CloseTMSGraphicsStep();
			break;
		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone3TestAppUi class which serves as a AppUi class.\n
  Sets the CCone3TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone3Step::ConstructCone3AppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone3TestAppUi* appUi=new(ELeave) CCone3TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTCone3Step class.\n
  Sets the test step name.\n
*/
CTCone3Step::CTCone3Step()
	{
	SetTestStepName(KTCone3Step);
	}

/**   Destructor for CTCone3Step class.\n */

CTCone3Step::~CTCone3Step()
{}

/**
  Entry function for CTCone3 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone3 Test application.\n
*/
TVerdict CTCone3Step::doTestStepL()
	{
    INFO_PRINTF1(_L("Test Started"));
	CCoeEnv* coe=new(ELeave) CCoeEnv;
    TRAPD(err,ConstructCone3AppL(coe));
    if (!err)
        coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


