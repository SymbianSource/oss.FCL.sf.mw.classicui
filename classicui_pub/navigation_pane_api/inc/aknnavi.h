/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A default control in the status pane's navigation pane.
*
*/


#ifndef C_AKNNAVI_H
#define C_AKNNAVI_H

#include <AknControl.h>
#include <coeccntx.h>
#include <Aknvolumecontrol.h>

// FORWARD DECLARATIONS
class CAknNavigationDecorator;
class CEikStatusPaneBase;
class CFbsBitmap;
class MAknTabObserver;
class CAknNavigationControlContainerExtension;
class MAknsControlContext;

class MAknNavigationDecoratorInterface
    {
public:
    virtual ~MAknNavigationDecoratorInterface() { }
    virtual CCoeControl* DecoratedControl() = 0;
    };

class MAknNavigationContainerInterface
    {
public:
    virtual ~MAknNavigationContainerInterface() { }
    virtual CAknNavigationDecorator* CreateMessageLabelL(const TDesC& aText) = 0;
    virtual CAknNavigationDecorator* CreateTabGroupL() = 0;
    virtual void PushL( CAknNavigationDecorator& ) = 0;
    virtual void Pop() = 0;
    };

/**
 * A default control in the status pane's navigation pane.
 */
class CAknNavigationControlContainer : public CAknControl,
                                       public MCoeControlContext,
                                       public MCoeControlObserver,
                                       public MAknNavigationContainerInterface
    {

public:

    DECLARE_TYPE_ID( 0x101F8740 )

public:

    /**
     * C++ default constructor.
     *
     * This object does not own the contents of the navi pane controls stack.
     */
    IMPORT_C CAknNavigationControlContainer();

    /**
     * Destructor.
     *
     * This object does not own the contents of the navi pane controls stack.
     */
    IMPORT_C ~CAknNavigationControlContainer();

    /**
     * Handles 2nd phase construction.
     */
    IMPORT_C void ConstructL();

    /**
     * Constructs from a resource. Created object is owned by this object until
     * @c ResourceDecorator() method is called. If the application does not
     * fetch the object it is deleted in destructor.
     *
     * @param aReader Resource reader.
     */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

    /**
     * Resource constructor that returns a new object to the application.
     *
     * @param aReader Resource reader.
     * @return Navigation decorator object that contains navigation pane
     *         control read from resources.
     */
    IMPORT_C CAknNavigationDecorator*
                    ConstructNavigationDecoratorFromResourceL(
                                                TResourceReader& aReader);

    /**
     * Creates and returns a new navigation decorator object containing tab
     * group.
     * The ownership of the object is transferred to the application.
     *
     * @return Navigation decorator object that contains tab group.
     */
    IMPORT_C CAknNavigationDecorator* CreateTabGroupL();

    /**
     * Creates and returns a new navigation decorator object containing tab
     * group. The ownership of the object is transferred to the application.
     *
     * @param aObserver Pointer to tab group observer
     * @return Navigation decorator object that contains tab group.
     */
    IMPORT_C CAknNavigationDecorator* CreateTabGroupL(
                                            MAknTabObserver* aObserver);

    /**
     * Creates from a resource and returns a new navigation decorator object
     * containing tab group.
     * The ownership of the object is transferred to the application.
     *
     * @param aReader Resource reader.
     * @return Navigation decorator object that contains tab group.
     */
    IMPORT_C CAknNavigationDecorator* CreateTabGroupL(
                                                TResourceReader& aReader);

    /**
     * Creates from a resource and returns a new navigation decorator object
     * containing tab group.
     * The ownership of the object is transferred to the application.
     *
     * @param aReader Resource reader.
     * @param aObserver Pointer to tab group observer.
     * @return Navigation decorator object that contains tab group.
     */
    IMPORT_C CAknNavigationDecorator* CreateTabGroupL(
                                            TResourceReader& aReader,
                                            MAknTabObserver* aObserver);

    /**
     * Creates and returns a new navigation decorator object containing
     * navigation label.
     * The ownership of the object is transferred to the application.
     *
     * @param aText Label text to the navigation pane.
     * @return Navigation decorator object that contains navigation label.
     */
    IMPORT_C CAknNavigationDecorator* CreateNavigationLabelL(
                                            const TDesC& aText = KNullDesC);

    /**
     * Creates from a resource and returns a new navigation decorator object
     * containing navigation label.
     * The ownership of the object is transferred to the application.
     *
     * @param aReader Resource reader.
     * @return Navigation decorator object that contains navigation label.
     */
    IMPORT_C CAknNavigationDecorator* CreateNavigationLabelL(
                                                    TResourceReader& aReader);

    /**
     * Creates and returns a new navigation decorator object containing
     * navigation image.
     * The ownership of the returned object is transferred to the application.
     * Moves ownership of @c aBitmap and @c aMaskBitmap to the navigation
     * decorator object at the end of the method.
     *
     * @param aBitmap Image to be shown in the navigation pane.
     * @param aMaskBitmap Mask of the image to be shown in the
     *        navigation panel.
     * @return Navigation decorator object that contains navigation image.
     */
    IMPORT_C CAknNavigationDecorator* CreateNavigationImageL(
                                        const CFbsBitmap* aBitmap = NULL,
                                        const CFbsBitmap* aMaskBitmap = NULL);

    /**
     * Creates from a resource and returns a new navigation decorator object
     * containing navigation image.
     * The ownership of the returned object is transferred to the application.
     *
     * @param aReader Resource reader.
     * @return Navigation decorator object that
     *         contains navigation image.
     */
    IMPORT_C CAknNavigationDecorator* CreateNavigationImageL(
                                            TResourceReader& aReader);

    /**
     * Creates and returns a new navigation decorator object containing
     * help text.
     * The ownership of the object is transferred to the application.
     *
     * @param aText Help text label to be shown in the navigation pane.
     * @return Navigation decorator object that
     *         contains message label (=hint text).
     */
    IMPORT_C CAknNavigationDecorator* CreateMessageLabelL(
                                        const TDesC& aText = KNullDesC);

    /**
     * Creates from a resource and returns a new navigation decorator object
     * containing help text.
     * The ownership of the object is transferred to the application.
     *
     * @param aReader Resource reader.
     * @return Navigation decorator object that contains message label
     *         (=hint text).
     */
    IMPORT_C CAknNavigationDecorator* CreateMessageLabelL(
                                            TResourceReader& aReader);

    /**
     * Creates volume control indicator to the navi pane.
     * The ownership of the object is transferred to the application.
     *
     * @param aResourceId Resource file id for the volume control
     * @return Navigation decorator object that contains volume indicator.
     *
     * @deprecated  Navi pane volume control is not supported anymore.
     */
    IMPORT_C CAknNavigationDecorator* CreateVolumeIndicatorL(TInt aResourceId);

    /**
     * Creates editor indicator container control to the navi pane.
     * The ownership of the object is transferred to the application.
     *
     * @return Navigation decorator object that contains editor indicator
     *         container.
     */
    IMPORT_C CAknNavigationDecorator* CreateEditorIndicatorContainerL();

    /**
     * Pushes default content (empty navigation pane) to the navigation pane's
     * object stack.
     * This operation also draws default content to the navigation pane.
     *
     * @param  aAllowDuplicates  If this is @c ETrue, duplicate default
     *                           navi pane contents are allowed.
     */
    IMPORT_C void PushDefaultL( TBool aAllowDuplicates = EFalse );

    /**
     * Pushes a navigation decorator object to the navigation pane's object
     * stack.
     * This operation also draws the control to the navigation pane. An object
     * can be on the stack only once. If the object already exists in the stack
     * it is moved to topmost object. Ownership is not transfered.
     * Editor indicator control has priority over others. It is always at the
     * top if it exists. In this case all other controls are pushed under
     * the editor indicator object.
     *
     * @param aNaviPaneControl Object to be added at the top of the stack.
     */
    IMPORT_C void PushL( CAknNavigationDecorator& aNaviPaneControl );

    /**
     * Pops topmost object from the navigation pane's object stack. If editor
     * indicator control is topmost, it is not popped. The next control
     * is popped instead.
     * It is not possible to pop editor indicator object with this method.
     * Use @c Pop(CAknNavigationDecorator* aControl) or @c delete(aControl)
     * instead if editor indicator control is needed to be popped.
     */
    IMPORT_C void Pop();

    /**
     * Pops (remove) certain object from the navigation pane's object stack.
     * The removed object does not need to be topmost.
     *
     * @param aControl Object to be removed from the stack.
     */
    IMPORT_C void Pop( CAknNavigationDecorator* aControl );

    /**
     * Returns topmost object from navigation pane's object stack.
     * Editor indicator object is transparent for this operation. If editor
     * indicators exist on the navi pane, next object on the stack is returned.
     *
     * @return Navigation decorator object that is topmost in navigation pane's
     *         object stack.
     */
    IMPORT_C CAknNavigationDecorator* Top();

    /**
    * Return topmost object from navigation pane's object stack.
    * FEP Editor indicator object is transparent or visible for this operation
    * depending on the given parameter value. If editor indicator object is to
    * be ignored and it exist on the navi pane, next object on the stack is
    * returned. Note that generally FEP does all the needed visibility etc.
    * handling for FEP editor indicators, so by default applications should
    * ignore FEP editor indicators.
    *
    * @since 3.1
    * @param  aIgnoreFepEditorIndicator  Tells if editor indicator
    *                                    object is ignored.
    *
    * @return Navigation decorator object that is topmost in
    *         navigation pane's object stack.
    */
    IMPORT_C CAknNavigationDecorator* Top(TBool aIgnoreFepEditorIndicator) const;


    /**
     * Replaces existing navigation decorator object in the navigation pane's
     * object stack. Any object can be on the stack only once. If the
     * replacement object already exists in the stack, previous copy is
     * removed from the stack. Ownership is not transfered.
     * Navi pane is redrawn if top item is changed.
     *
     * @param aToBeReplaced An object to be replaced.
     * @param aReplacement An object that is put to the stack instead.
     * @return Error number. @c KErrNone if the operation succeeds.
     *         @c KErrNotFound if @c 'aToBeReplaced' object cannot be
     *         found from the stack.
     */
    IMPORT_C TInt ReplaceL( CAknNavigationDecorator& aToBeReplaced,
                            CAknNavigationDecorator& aReplacement );

    /**
     * Returns the object constructed from resources with
     * @c ConstrucFromResourcesL() -method to the application.
     * Ownership of the object is transferred to the application.
     *
     * @return Navigation Decorator object that was
     *         created from resources.
     */
    IMPORT_C CAknNavigationDecorator* ResourceDecorator();

    /**
     * This non-exported method returns reference to navi arrow bitmaps.
     *
     * @param  aId  Id of the bitmap.
     * @return Reference to the navi arrow bitmap.
     */
    CFbsBitmap& NaviArrowBitmap( TInt aId );

public:

    /**
     * This method can be used to set preferred layout style for navi decorator
     * objects that are pushed into navistack.
     * Given layout is applied to objects only if that object supports it and
     * status pane layout allows that mode to be used.
     *
     * @since 3.1
     *
     * @param aLayoutStyle CAknNavigationDecorator::ENaviControlLayoutNormal,
     *                     CAknNavigationDecorator::ENaviControlLayoutNarrow or
     *                     CAknNavigationDecorator::ENaviControlLayoutWide
     *
     */
    IMPORT_C void SetPreferredNaviDecoratorLayoutStyle( TInt aLayoutStyle );

    /**
     * Static method to return current color scheme.
     * @return Current color scheme value.
     */
    IMPORT_C static TInt ColorScheme();

    /**
     * Used by the UI framework. Notifies context and signal
     * panes wheter navi wipe graphichs is to be drawn or not.
     */
    void NotifyNaviWipeStatusL();

    /**
     * Gets current wipe bitmap for navi pane.
     *
     * @return Wipe bitmap Id
     */
    static TInt CurrentNaviWipeBitmap();

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
     * Used to notify the navi pane when it goes to background.
     * @internal Used by the UI framework.
     */
    void HandleLosingForeground();
    
    /**
     * Used to notify the navi pane when it gains foreground.
     * @internal Used by the UI framework.
     */
    void HandleGainingForegroundL();

protected: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Handles the size change events.
     */
    IMPORT_C virtual void SizeChanged();

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources of type @c aType
     * which are shared across the environment, e.g. color scheme change.
     *
     * @param aType Event type.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
     * From @c CCoeControl.
     *
     * Returns number of controls inside the context pane control.
     *
     * @return Number of component controls.
     */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
     * From @c CCoeControl.
     *
     * Returns a control determined by control id.
     *
     * @param aIndex Index of a control to be returned.
     * @return Pointer to control.
     */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

protected: // from MCoeControlObserver

    /**
     * From @c  MCoeControlObserver.
     *
     * Handles Control event.
     *
     * @param aControl Control that caused the event.
     * @param aEventType Type of the event.
     */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl,
                                      TCoeEvent aEventType);

private: // from CCoeControl

    IMPORT_C virtual void Draw(const TRect& aRect) const;

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

public:

    /**
     * Not used / implemented
     *
     * @deprecated
     *
     * @since S60 3.0
     *
     * @return @c EFalse
     */
    TBool NaviWipeUsed() const;

    /**
     * Gets navi bitmap.
     *
     * @return Bitmap's colour.
     */
    CFbsBitmap* NaviColorBitmap() const;

    /**
     * Not used / implemented
     *
     * @deprecated
     *
     * @since S60 3.0
     */
    static void SetBackgroundContextAttributes( CCoeControl* aControl,
                                                TBool aNaviWipeUsed );

private:
    TBool IsFepOwnedEditorIndicatorControl(
        CAknNavigationDecorator* aDecorator ) const;

    void HandleVisibilityOfNonFepOwnedIndicatorControl(
        CAknNavigationDecorator* aDecorator, TBool aVisible);

    /**
    * Checks wheter default navi wipe bitmap can be drawn to navipane and draws
    * it if it is possible.
    *
    * @since S60 2.6
    * @param aGc Used graphics context.
    * @param aRect Rect of the navipane.
    * @return @c ETrue if draw operation was done, otherwise @c EFalse.
    *
    */
    TBool DrawDefaultNaviWipe(CWindowGc& aGc, const TRect& aRect) const;

    /**
    * Checks wheter default navi solid bitmap can be drawn to navipane and draws
    * it if it is possible.
    *
    * @since S60 2.6
    * @param aGc Used graphics context.
    * @param aRect Rect of the navipane.
    * @return ETrue if draw operation was done, otherwise EFalse.
    *
    */
    TBool DrawDefaultNaviSolid(CWindowGc& aGc, const TRect& aRect) const;

    /**
    * Checks wheter skinned navi wipe bitmap can be drawn to navipane and draws
    * it if it is possible. Also skinned background bitmap is drawn.
    *
    * @since S60 2.6
    * @param aGc Used graphics context.
    * @param aRect Rect of the navipane.
    * @param aSkin Used skin instance.
    * @param aCc Used skin control context.
    * @return ETrue if draw operation was done, otherwise EFalse.
    */
    TBool DrawSkinnedNaviWipe( CWindowGc& aGc,
                               const TRect& aRect,
                               MAknsSkinInstance* aSkin,
                               MAknsControlContext* aCc ) const;

    /**
    * Checks wheter skinned navi solid bitmap can be drawn to navipane and draws
    * it if it is possible. Also skinned background bitmap is drawn.
    *
    * @since S60 2.6
    * @param aGc Used graphics context.
    * @param aRect Rect of the navipane.
    * @param aSkin Used skin instance.
    * @param aCc Used skin control context.
    * @return ETrue if draw operation was done, otherwise EFalse.
    */
    TBool DrawSkinnedNaviSolid( CWindowGc& aGc,
                                const TRect& aRect,
                                MAknsSkinInstance* aSkin,
                                MAknsControlContext* aCc ) const;

    /**
     * Loads a color bitmap for CAknNavigationDecorator.
     * @since S60 2.8
     */
    void LoadNaviColorBitmapL();

    void SetContainerWindowNonFading( TBool aNonFading );
    
    TRect VolumePopupRect();

protected: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Retrieves an object of the same type as that encapsulated in aId.
     *
     * This function is used to allow controls to ask their owners for
     * access to other objects that they own.
     *
     * Other than in the case where NULL is returned, the object returned
     * must be of the same object type - that is, the @c ETypeId member of
     * the object pointed to by the pointer returned by this function must
     * be equal to the @c iUid member of @c aId.
     *
     * @param aId An encapsulated object type ID.
     * @return Encapsulated pointer to the provided object.
     *         Note that the encapsulated pointer may be NULL.
     */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

private:

    CEikStatusPaneBase* iStatusPane;

    CAknNavigationDecorator* iNaviDecoratorFromResource;

    typedef CArrayPtrFlat<CAknNavigationDecorator> CAknNaviPaneStack;
    CAknNaviPaneStack* iNaviPaneControls;

    CFbsBitmap* iNaviArrowBitmap[4];

    TInt  iSpare;
    CAknNavigationControlContainerExtension* iExtension;
    };

#endif // C_AKNNAVI_H
