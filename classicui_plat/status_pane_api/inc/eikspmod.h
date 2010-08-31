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


#if !defined(__EIKSPMOD_H__)
#define __EIKSPMOD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKON_HRH__)
#include <uikon.hrh>
#endif

#if !defined(__EIKSRVC_H__)
#include <eiksrvc.h>
#endif


class TResourceReader;
class CEikStatusPaneLayoutTree;
class CEikonEnv;
class CAknSgcClient;
class CEikStatusPaneLayout;
namespace AknLayout { class CInstance; }
namespace AknLayoutScalable_Avkon { class CInstance; }

// Extra bit flags not defined in hrh file.
const TInt KEikStatusPaneDirectionBit		= 0x04;
const TInt KEikStatusPaneHiddenBit			= 0x08;
const TInt KEikStatusPaneInitInitializedBit	= 0x80000000;


typedef TUid TPaneId;

/**
*
* This class stores the details about status pane sub pane 
* ownership and initial contents. 
*
*/
class TEikStatusPaneInit
	{
public:
   /**
	* Default constructor.
	*/
	TEikStatusPaneInit();

   /**
	* Copy constructor.
	*/
	TEikStatusPaneInit(const TEikStatusPaneInit& aCopy);

   /**
	* Operator overload.
	*/
	TEikStatusPaneInit& operator=(const TEikStatusPaneInit& aCopy);
	
   /**
	* Gets pane id.
	* @return id of the pane.
	*/
	inline TPaneId Id() const;

   /**
	* Loads deafault values of the pane from given resource.
	* Resource reader should point to an entry from the arrays of 
	* SPANE_PANE structures  found in the STATUS_PANE_SYSTEM_MODEL 
	* and STATUS_PANE_APP_MODEL resource structures.
	*
	* @param @aResource Resource reader.
	*/
	void LoadDefaults(TResourceReader& aResource);

   /**
	* Gets flag that indicates if the sub pane is owned by the 
	* application or not.
	* @return ETrue if pane is application owned, otherwise EFalse.
	*/
	inline TBool AppOwned() const;
	
   /**
	* Returns control type id of the pane.
	* @return Id of the control inside the pane.
	*/	
	inline TInt ControlTypeId() const;

   /**
	* Returns resource id of the control in the pane.
	* @return Control resource id.
	*/	
	inline TInt ControlResourceId() const;

   /**
	* Sets hidden flag.
	*/	
	inline void SetHidden();

   /**
	* Clears hidden flag.
	*/	
	inline void ClearHidden();

   /**
	* Gets hidden flag.
	* @return ETrue if the pane is hidden.
	*/		
	inline TBool IsHidden() const;

private:
   /**
	* Gets initialized flag.
	* @return ETrue if the pane is initialized.
	*/		
	inline TBool Initialized();

   /**
	* Sets initialized flag.
	*/		
	inline void SetInitialized();

private:
	TPaneId iId;
	TInt iControlId;
	TInt iControlResource;
	TInt iFlags;
	};


/**
*
* This class stores array of TEikStatusPaneInit instances.
*
*/
NONSHARABLE_CLASS(CEikStatusPaneSetInit) : public CArrayFixFlat<TEikStatusPaneInit>
	{
public:
 
   /**
	* Two phase constructor.
	*/
	static CEikStatusPaneSetInit* NewL();

   /**
	* Destructor.
	*/
	~CEikStatusPaneSetInit();

   /**
	* Loads deafault values of the panes from given resource.
	* Values are read from SPANE_PANE structure found in the 
	* STATUS_PANE_SYSTEM_MODEL and STATUS_PANE_APP_MODEL resource 
	* structures
	* @param @aResource Resource reader.
	*/
	void LoadDefaultsL(TResourceReader& aResource);
	
   /**
	* Finds the pane init with a given id. If a pane init
	* is not found, method leaves with code KErrNotFound.
	* @return The pane init instance with given id.
	*/			
	TEikStatusPaneInit& FindL(const TPaneId& aPaneId);

private:
 
   /**
	* Private constructor.
	*/
	CEikStatusPaneSetInit();
	};


/**
*
* This abstract class is used for checking pane layout validity.
*
*/
class MEikStatusPaneLayoutTreeVisitor
	{
public:
   /**
	* Virtual function of which implementation should be provided 
	* by the classes that implement the layout check visitor design 
	* pattern.
	* @param aNode A layout node to be visited.
	*/
	virtual void VisitL(CEikStatusPaneLayoutTree* aNode) = 0;
	};



/**
*
* This class calculates and stores the screen area available 
* for each layout tree.
*
*/
NONSHARABLE_CLASS(CEikStatusPaneLayoutTree) : public CBase
	{
public:
	enum TDirection
		{
		/** Horizontal direction */
		EHorizontal,
		/** Vertical direction */
		EVertical
		};

public:
   /**
	* Destructor.
	*/
	~CEikStatusPaneLayoutTree();

   /**
	* Two phase constructor.
	* @param aLayout Layout data
	* @param aResource Resource of layout tree.
	* @param aDefaultDirection Default direction of the layout tree.
	*/
	static CEikStatusPaneLayoutTree* NewL(CEikStatusPaneLayout* aLayout, TResourceReader& aResource, TDirection aDefaultDirection = EHorizontal);

   /**
	* Finds the layout tree with a given pane id. 
	* @param aPaneId A id of the pane.
	* @return If layout tree was found, a pointer to layout tree 
	*         with given id. Otherwise NULL is returned.
	*/			
	CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId);
	
   /**
	* Calls given visitor objects VisitL, method. Additionally
	* calls AcceptL -method of each sub pane layouts inside this layout tree.
	* @param aVisitor A visitor object to be visited.
	*/			
	void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);

   /**
	* Gets pane id.
	* @return id of the pane.
	*/
	inline TPaneId Id() const;

   /**
	* Gets rectagle of the layout tree.
	* @return Rectangle of the layout tree.
	*/
	inline TRect Rect() const;

    /**
     * This method maps given layout resource id and subpane UID to correct
     * layout lines in the AknLayout system.
     *
     * @since   2.8
     * @param   aLayoutResourceId    Id of a statuspane layout.
     * @param   aPaneId              Uid of a statuspane subpane.
     * @return  A rectangle which specifies the given subpane size 
     *          and position in the given layout. 
     *
     */
    TRect AknLayoutRect(TInt aLayoutResourceId, TPaneId aPaneId);

private:

   /**
	* Private constructor.
	* @param aLayout Layout data
	* @param aDefaultDirection Default direction of the layout tree.
	*/
	CEikStatusPaneLayoutTree(CEikStatusPaneLayout* aLayout, TDirection aDefaultDirection);

   /**
	* Private 2nd phase constructor.
	* @param aResource Resource of layout tree.
	*/
	void ConstructL(TResourceReader& aResource);

   /**
	* Sets rectagle of the layout tree.
	* @param aRect Rectangle of the layout tree.
	*/
	void SetRect(const TRect& aRect);

   /**
	* Gets direction of the layout tree.
	* @return Direction of the layout tree.
	*/
	inline TDirection Direction();
	
   /**
	* Sets direction of the layout tree.
	* @param aDirection Direction of the layout tree.
	*/
	void SetDirection(TDirection aDirection);
	
   /**
	* Gets size of the layout tree.
	* @return size of the layout tree.
	*/
	inline TInt Size();
	
   /**
	* Gets stretchable flag of the layout tree.
	* @return Stretchable flag of the layout tree.
	*/
	inline TBool Stretchable();

   /**
	* Sets stretchable flag of the layout tree.
	* @param Stretchable flag of the layout tree.
	*/
	void SetStretchable(TBool aStretchable);
	
   /**
	* Sets the layout of the sub panes inside layout tree according to
	* layout tree attributes read from the resource structures.
	*/
	void Layout();

   /**
     * This methods purpose is eqvivalent of the Layout() method, but the difference
     * is that this method uses AknLayout system instead of the statuspane
     * resource definitions for determining the positions and sizes of the subpanes.
     *
     * If AknLayoutUsed flag has not been set then this method defaults to the behaviour
     * of the Layout() -method.
     *
     * @since   2.8
     * @param   aLayoutResourceId    Id of the statuspane layout which is to be laid out.
     *
     */
	void Layout(TInt aLayoutResourceId);

    /**
     * This method sets flag which tells wheter AknLayout system is
     * used or not for layout.
     *
     * @since   2.8
     * @param   aAknLayoutUsed  ETrue if AknLayout is to be used. EFalse otherwise.   
     *
     */
    void SetAknLayoutUsed(TBool aAknLayoutUsed);
    
    /**
     * This method gets flag which tells wheter AknLayout system is
     * used or not for layout.
     *
     * @since   2.8
     * @return  ETrue if AknLayout is to be used. EFalse otherwise.   
     *
     */
    TBool AknLayoutUsed();

private:
	TPaneId iId;
	TInt iFlags;
	TRect iRect;
	TInt iSize;

	typedef CArrayPtrFlat<CEikStatusPaneLayoutTree> CSubPaneArray;
	CSubPaneArray* iSubPanes;

	CEikStatusPaneLayout* iLayout;
	
private:
	friend class CEikStatusPaneLayout;
	};


/**
*
* This class calculates and stores the screen area available 
* for each sub pane layout.
*
*/
NONSHARABLE_CLASS(CEikStatusPaneLayout) : public CBase
	{
public:
   /**
	* Two phase constructor.
	* @param aResource Resource of sub pane layout.
	* @param aScreenRect Screen rectangle.
	*/
	static CEikStatusPaneLayout* NewL(TResourceReader& aResource, const TRect& aScreenRect);

   /**
	* Two phase constructor.
	* @param aResource Resource of sub pane layout.
	* @param aScreenRect Screen rectangle.
	* @param aLayoutId Id of the status pane layout.
	*/
	static CEikStatusPaneLayout* NewL(TResourceReader& aResource, const TRect& aScreenRect, TInt aLayoutId);
	
   /**
	* Destructor
	*/	
	~CEikStatusPaneLayout();

   /**
	* Finds the pane init with a given id. If a pane init
	* is not found NULL pointer is returned.
	* @return The layout tree instance with given id.
	*/			
	inline CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId) const;

   /**
	* Calls given visitor objects VisitL, method. 
	* @param aVisitor A visitor object to be visited.
	*/			
	inline void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);
	
   /**
	* Gets rectagle of the sub pane layout.
	* @return Rectangle of the sub pane layout.
	*/
	inline TRect Rect() const;

    /**
     * Re-reads layout data from AknLayout system. The data may have to be refreshed when e.g.
     * screen resolution, orientation or language variant layout is changed on the fly.
     *
     * @since   2.8
     * @param   aLayoutResourceId    Id of the statuspane layout which data is to be refreshed.
     *
     */
	void AknLayoutRefresh(TInt aLayoutResourceId);

    /**
     * This method tells if this layout is using AknLayout system for placing and sizing 
     * the statuspane subpanes.
     *
     * @since   2.8
     * @return  ETrue if this layout has been initailized to use AknLayout. EFalse if the default
     *          statuspane layout system is in use.
     *
     */
    TBool AknLayoutUsed();

    /**
     * This method maps given layout resource id and subpane UID to correct
     * layout lines in the AknLayout system.
     *
     * @since   3.1
     * @param   aLayoutResourceId    Id of a statuspane layout.
     * @param   aPaneId              Uid of a statuspane subpane.
     * @return  A rectangle which specifies the given subpane size 
     *          and position in the given layout. 
     *
     */
    TRect AknLayoutRect(TInt aLayoutResourceId, TPaneId aPaneId);

private:

   /**
	* Constructor.
	*/
	CEikStatusPaneLayout();

   /**
	* 2nd phase constructor.
	*/
	void ConstructL(TResourceReader& aResource, const TRect& aScreenRect, TInt aLayoutId);

private:
	CEikStatusPaneLayoutTree* iRoot;

private:

   /**
	* Updates layout data.
	* @param aLayoutResId Status pane layout resource id. 
	*/
	void UpdateLayoutData(TInt aLayoutResId);
	
private:	// layout data for all nodes in CEikStatusPaneLayoutTree
	friend class CEikStatusPaneLayoutTree;
	const AknLayout::CInstance& iAknLayout;
	const AknLayoutScalable_Avkon::CInstance& iAknLayoutScalable_Avkon;
    TRect iScreenRect; 
    TRect iMainPaneRect;
    TRect iUsualStatusPaneRect;
    TRect iApplicationWindowRect;
	TRect iStaconLayout1Rect;
	TRect iStaconLayout2Rect;
	TRect iSmallStatusPaneRect;
	};


/**
*
* Base class for status pane model.
*
*/
class CEikStatusPaneModelBase : public CBase
	{
public:

   /**
	* Destructor.
	*/
	IMPORT_C ~CEikStatusPaneModelBase();

   /**
	* Gets the pane inits of the status pane.
	* @return Pane inits.
	*/
	inline CEikStatusPaneSetInit* PaneInits() const;
	
   /**
	* Sets the status pane layout
	* @param aLayoutResId Resource id of the status pane layout.
	* @param aChangeStatusPaneNow A flag to indicate immediate status pane layout change.
	*/	
	IMPORT_C virtual void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);
	
   /**
	* Gets the current layout.
	* @return The current layout.
	*/
	inline CEikStatusPaneLayout* CurrentLayout() const;

   /**
	* Gets the current layout resource id.
	* @return The current layout resource id.
	*/
	IMPORT_C TInt CurrentLayoutResId() const;

    /**
     * Re-reads layout data for all existing layouts from AknLayout system. The data 
     * may have to be refreshed when e.g. screen resolution, orientation or language 
     * variant layout is changed on the fly.
     *
     * @since 2.8
     *
     */
	void AknLayoutRefresh();

    /**
     * This method tells if given layout is using AknLayout system for placing and sizing 
     * the statuspane subpanes.
     *
     * @since   2.8
     * @param   aLayoutId   Layout which layout type is wanted to be known.
     * @return  ETrue if given layout has been initailized to use AknLayout. EFalse if the default
     *          statuspane layout system is in use.
     *
     */
	TBool AknLayoutUsed(TInt aLayoutId);

protected:

	/**
	* Internal class to CEikStatusPaneModel, 
	* which ties layout resource IDs to layout structures.
	*/
	NONSHARABLE_CLASS(CIdLayoutPair) : public CBase
		{
	public:
      /**
		* Constructor.
		* @param aResId Resource id 
		* @param aLayout Sub pane layout
		*/
		CIdLayoutPair(TInt aResId, CEikStatusPaneLayout* aLayout);
       /**
		* Destructor.
		*/
		~CIdLayoutPair();
	public:
		TInt iResId;
		CEikStatusPaneLayout* iLayout;
		};
	typedef CArrayPtrFlat<CIdLayoutPair> CLayoutIdSet;
	typedef CArrayFixFlat<TInt> CIdSet;

protected:
	
   /**
	* Constructor.
	* @param aEikEnv An environment for creating controls.
	*/
	IMPORT_C CEikStatusPaneModelBase(CEikonEnv& aEikEnv);

   /**
	* Base constructor for 2nd phase construction.
	* @param aCoreResId Status pane core resource id.
	*/
	IMPORT_C void BaseConstructL(TInt aCoreResId);

   /**
	* Loads given layout from resource.
	* @param aLayoutResId Layout resource id.
	*/
	IMPORT_C CEikStatusPaneLayout* LoadLayoutL(TInt aLayoutResId);

   /**
	* Returns set of legal layout ids.
	* @return Set of allowed status pane layout ids.
	*/
	inline CIdSet* LegalIds() const;
	
   /**
	* Checks if given layout id is allowed.
	* @param aLayoutResId Layout id to be checked.
	* @return ETrue if given layout id is allowed.
	*/	
	TBool IsLegalId(TInt aLayoutResId) const;

private:
   /**
	* Gets given layout.
	* @param aLayoutResId Layout resource id.
	*/
	CEikStatusPaneLayout* Layout(TInt aLayoutResId);

   /**
	* Checks given layout.
	* @param aLayout Layout to be checked.
	*/
	void CheckLayoutL(CEikStatusPaneLayout* aLayout);

private:
	IMPORT_C virtual void Reserved_1();

private:
	NONSHARABLE_CLASS(TLayoutChecker) : public MEikStatusPaneLayoutTreeVisitor
		{
	public:
		TLayoutChecker(CEikStatusPaneSetInit* aPanes);
		void VisitL(CEikStatusPaneLayoutTree* aNode);
	private:
		CEikStatusPaneSetInit* iPanes;	
		};

protected:
	CLayoutIdSet* iLayouts;
	TInt iCurrentResId;
	CEikonEnv& iEikEnv;

private:
	CEikStatusPaneSetInit* iPanes;
	CEikStatusPaneLayout* iCurrentLayout;
	CIdSet* iLegalIds;
	};


/**
*
* Status pane model for application status pane.
*
*/
NONSHARABLE_CLASS(CEikAppStatusPaneModel) : public CEikStatusPaneModelBase
	{
public:
   /**
	* Two phase constructor.
    *
	* @param aEikEnv An environment for creating controls.
	* @param aCoreResId Status pane core resource id
	* @param aAppResId Application status pane resource id
	* @param aChangeStatusPaneNow A flag to indicate immediate status pane layout change.
	* @return Constructed instance.
	*/
	static CEikAppStatusPaneModel* NewL(CEikonEnv& aEikEnv, /*REikSrvSession,*/ TInt aCoreResId, TInt aAppResId = EEikStatusPaneUseDefaults, TBool aChangeStatusPaneNow = ETrue);
	
   /**
	* Destructor.
	*/
	~CEikAppStatusPaneModel();

   /**
	* Takes current layout into use.
	*/
	void ApplyCurrentLayoutL();

public:	
   /**
	* from CEikStatusPaneModelBase
	*/
	void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);
public:	
   /**
	* from CEikStatusPaneModelBase
	*/
	void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow, TBool aNotfiyServerSide);

private:
	CEikAppStatusPaneModel(CEikonEnv& aEikEnv);
	void ConstructL(TInt aCoreResId, TInt aAppResId, TBool aChangeStatusPaneNow = ETrue);
	};


inline TPaneId TEikStatusPaneInit::Id() const { return iId; }
inline TBool TEikStatusPaneInit::AppOwned() const { return iFlags & EEikStatusPaneAppOwned; }
inline TInt TEikStatusPaneInit::ControlTypeId() const { return iControlId; }
inline TInt TEikStatusPaneInit::ControlResourceId() const { return iControlResource; }
inline void TEikStatusPaneInit::SetHidden() {iFlags|=KEikStatusPaneHiddenBit;}
inline void TEikStatusPaneInit::ClearHidden() {iFlags&=~KEikStatusPaneHiddenBit;}
inline TBool TEikStatusPaneInit::IsHidden() const {return iFlags&KEikStatusPaneHiddenBit;}

inline CEikStatusPaneLayoutTree* CEikStatusPaneLayout::Find(const TPaneId& aPaneId) const { return iRoot->Find(aPaneId); }
inline void CEikStatusPaneLayout::AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor) { iRoot->AcceptL(aVisitor); }
inline TRect CEikStatusPaneLayout::Rect() const { return iRoot->Rect(); }

inline TPaneId CEikStatusPaneLayoutTree::Id() const { return iId; }
inline TRect CEikStatusPaneLayoutTree::Rect() const { return iRect; }


inline CEikStatusPaneSetInit* CEikStatusPaneModelBase::PaneInits() const { return iPanes; }
inline CEikStatusPaneLayout* CEikStatusPaneModelBase::CurrentLayout() const { return iCurrentLayout; }
inline CEikStatusPaneModelBase::CIdSet* CEikStatusPaneModelBase::LegalIds() const { return iLegalIds; }

#endif
