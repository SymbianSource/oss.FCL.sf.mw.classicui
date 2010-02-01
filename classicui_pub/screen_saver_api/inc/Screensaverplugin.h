/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Defines screensaver plugin interface.
*
*/


#ifndef SCREEN_SAVER_PLUGIN_H
#define SCREEN_SAVER_PLUGIN_H

//  INCLUDES
#include <e32base.h>
#include <gulicon.h>
#include <coecntrl.h>

#include <ScreensaverpluginIntDef.hrh> // For TScPluginCaps

// CONSTANTS

//
// Enumerations for screensaver indicators.
//
enum TScreensaverIndicatorIndex
    {      
    EScreensaverIndicatorIndexNewMessages,
    EScreensaverIndicatorIndexNewMissedCalls,
    EScreensaverIndicatorIndexKeyGuardState,
    EScreensaverIndicatorIndexProfileName,
    EScreensaverIndicatorIndexChatMessage,
    EScreensaverIndicatorIndexEmail,
    EScreensaverIndicatorIndexVoicemail,
    EScreensaverIndicatorIndexAmPm
    };


// Screensaver indicator payload types
enum TScreensaverPayloadType
    {
    EPayloadTypeUnknown = 0,
    EPayloadTypeInteger,   // Icon and and number, or just icon (integer -1)
    EPayloadTypeText,      // E.g. profile, AM/PM
    EPayloadTypeIcon       // Icon only
    };


// Enumerations for possible partial mode types.
enum TScreensaverPartialModeType
    {
    EPartialModeTypeDefault = 0,         // Default partial mode (usually same as "most power saving"): 
    EPartialModeTypeFull,                // Partial mode with maximum number of colors.
    EPartialModeTypeReduced,
    EPartialModeTypeMostPowerSaving      // Most power saving partial mode (usually only limited number of color available).
    };


// Events sent to plugin by Screensaver 
enum TScreensaverEvent
    {
    // Null event
    EScreensaverEventNothing = 0x00,
    // Screensaver starting, plugin should get Draw() calls soon, or
    // disable Screensaver timer to do it's own draw timing
    EScreensaverEventStarting,
    // Screensaver stopping, plugin should stop drawing
    EScreensaverEventStopping,
    // Resolution, orientation, window etc has changed
    EScreensaverEventDisplayChanged,
    // Plugin-requested timeout has elapsed. Plugins
    // can use this for e.g. running a certain
    // amount of time and suspending to normal
    // screen saver after the timeout occurs
    EScreensaverEventTimeout,
    // Screensaver is about to enter preview mode. Next start and stop events
    // will indicate preview start and end 
    EScreensaverEventPreview
    };


// In Rel 3.0 TScPluginCaps is moved to ScreensaverpluginIntDef.hrh
#if 0
// Screen saver plugin capabilities
enum TScPluginCaps
    {
    // Plugin has no special capabilities
    EScpCapsNone = 0x00,
    // Plugin implements the configure function
    EScpCapsConfigure = 0x01,
    // Plugin wants to be notified when selected as the active screensaver
    EScpCapsSelectionNotification = 0x02, 
    // Plugin wants to be notified when preview command is selected
    EScpCapsPreviewNotification = 0x04
    };
#endif

const TInt KMaxPayloadTextLength = 30;
const TInt KScreensaverMaxPartialModes = 6;

// Maximum time (secs) lights can be requested to be on
const TInt KMaxLightsOnTime = 30;

// MACROS

// DATA TYPES

class TScreensaverPartialMode
    {
public: 
    TScreensaverPartialModeType iType;   // Id of this partial mode level. 
    TInt iBpp;                           // How many bits per pixels is actually used
                                         // if this partial mode level is activated.
    };


// More or less obsolete - may or may not work. As a rule displays
// seem to support only a single partial mode
class TScreensaverColorModel
    {
public:
    TInt iNumberOfPartialModes;      // Number of partial mode levels supported
                                     // by current display hardware.
    TScreensaverPartialMode iPartialModes[KScreensaverMaxPartialModes];  // Array of
                                     // supported partial modes; 
    TScreensaverPartialMode iSystemPartialMode;  // Partial mode level that default
                                     // screensaver uses when drawing standard
                                     // screensaver bar.
    TInt16 iColors[8];               // Array of possible background colors
                                     // for standard screensaver bar in 
                                     // single background color mode.
    TRgb iDarkGradient[6];           // Darker shades for gradient effect 
                                     // in standard screensaver bar 
                                     // (these are used only if there is enough
                                     // colors to draw gradient effect). 
    TRgb iLightGradient[6];          // Lighter shades for gradient 
                                     // effect in standard screensaver bar.
    };  


// Screensaver indicator payload. For integer types 
class TIndicatorPayload
    {
public:
    TScreensaverPayloadType iType;  
    TInt iInteger;
    TBuf16<KMaxPayloadTextLength> iText;
    TBool iIsDisplayed;   // Read-only, cannot be set externally
    CGulIcon* iIcon;      // Read-only, cannot be set externally
        
public:
    TIndicatorPayload()
        : iType(EPayloadTypeUnknown),
          iInteger(-1),
          iIsDisplayed(EFalse),
          iIcon(NULL)
        {}
    };


class TScreensaverDisplayInfo
    {
public:
    TInt iSize;            // Size of struct, MUST be set by caller
    TRect iRect;           // Rect of display area, may not be whole screen
    CCoeControl* iParent;  // Parent control, has a window
    };


// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* This class defines plugin host interface. Plugin module uses
* this interface for communicating with its host application. An instance
* of this interface is given as a parameter to plugin module when
* it is created.
*/
class MScreensaverPluginHost 
    {
public:
    /**
     * Sets screensaver application to use standard indicator view.
     * This is default mode for indicator drawing.
     */
    virtual void UseStandardIndicators() = 0;

    /**
     * Notifies plugin host that plugin module is going to take care
     * of drawing indicator view and host shouldn't display them anymore.
     * If not overridden, normal screensaver will display when there
     * are indicators to show. Overriding the indicators does not mean they
     * _have_ to be drawn by the plugin, but that screensaver will not try to
     * do it.
     */
    virtual void OverrideStandardIndicators() = 0;

    /**
     * Returns boolean value indicating whether standard indicator
     * drawing is used or not.
     *
     * @return ETrue  if standard indicator drawing is used
     *         EFalse if plugin module takes care of drawing indicators 
     */
    virtual TBool StandardIndicatorsUsed() const = 0;

    /**
     * Sets timeout value for refresh timer. Plugin module's draw
     * method is called every time when refresh timer expires.
     *
     * @param aValue  Timeout value for refresh timer in microseconds.
     */
    virtual void SetRefreshTimerValue(TInt aValue) = 0;

    /**
     * Returns the current timeout value of refresh timer.
     *
     * @return The current timeout value of refresh timer in microseconds.
     */
    virtual TInt RefreshTimerValue() const = 0;

    /**
     * Returns payload associated with given screensaver indicator.
     * For list of supported indcicator indices see definition of 
     * TScreensaverIndicatorIndex. Also see definition of
     * TIndicatorPayload class.
     *
     * @param aIndex  Index of requested indicator.
     * @param aResult Structure where query results will be stored.
     * @return KErrNone if query was succesful.
     */
    virtual TInt GetIndicatorPayload(
        TScreensaverIndicatorIndex aIndex,
        TIndicatorPayload& aResult) const = 0;

    /**
     * This method is used for activating so called screensaver partial mode.
     * Partial mode area specifies an area on the screen where screensaver
     * plugin module is going to draw during next refresh period. When partial
     * mode is activated the screen segments outside given area are 
     * physically turned off to decrease power consumption. Whether partial
     * mode is supported or not depends on actual display hardware.
     * It is also possible that some devices support only limited number of
     * colors in partial mode area.
     * The actual size of the partial mode area may be restricted by the
     * display hardware, and differ from the size requested. Note that both
     * minimum and/or maximum size may be restricted.
     * If partial mode is not supported this method does nothing (that's
     * always the case in WINS environment). 
     *
     * @param aStartRow  Specifies the topmost pixel row of active 
     *                   display area on the screen.
     * @param aEndRow    Specifies the bottom pixel row of active display area.
     *
     * @param aMode      Partial mode to be set.
     * 
     * @return KErrNone  if partial mode was successfully activated.
     *                   otherwise system wide error code.
     * @deprecated       Should use the rect-version from S60 v3.0 on
     */
    virtual TInt SetActiveDisplayArea(
        TInt aStartRow,
        TInt aEndRow,
        const TScreensaverPartialMode& aMode) = 0;

    /**
     * Cancels the effect of SetActiveDisplayArea method. The whole display area 
     * is activated.
     */
    virtual void ExitPartialMode() = 0;

    /**
     * Queries screensaver color in current environment (includes
     * partial modes supported by display hardware).
     *
     * @param aResult  A structure for storing the results of the query.
     */
    virtual const TScreensaverColorModel& GetColorModel() const = 0;

    /**
     * This method suspends plugin module drawing for given time.
     * During that time standard screensaver view is drawn. 
     *
     * @param aTime Suspension time in microseconds. Values below
     *        500000 are rounded up to 500000. A negative value
     *        suspends the plugin indefinitely.
     */
    virtual void Suspend(TInt aTime) = 0;

    /**
     * With this method the plugin may request screen backlight to be
     * turned on or off. 
     *
     * @param aSecs Desired time in seconds the screen backlight should be
     *        turned on (1 - 30). Less than 1 will turn the lights off,
     *        more than 30 will be treated as 30. The plugin host has the
     *        final control over the lights, so time may be less than
     *        requested, or the lights may be switched off even without
     *        request before the time is up.
     */
    virtual void RequestLights(TInt aSecs) = 0;

    /**
     * Plugin may use this function to enquire display properties. Should
     * be called e.g. in response to EScreensaverEventDisplayChanged to
     * retrieve the new information.
     *
     * @param aDisplayInfo Struct to receive the display information. NOTE
     *        that iSize must be set by the caller.
     *
     */
    virtual TInt DisplayInfo(TScreensaverDisplayInfo* aDisplayInfo) = 0;
    
    /**
     * This method is used for activating so called screensaver partial mode.
     * Partial mode area specifies an area on the screen where screensaver
     * plugin module is going to draw during next refresh period. When partial
     * mode is activated the screen segments outside given area are 
     * physically turned off to decrease power consumption. Whether partial
     * mode is supported or not depends on actual display hardware.
     * It is also possible that some devices support only limited number of
     * colors in partial mode area.
     * The actual size of the partial mode area may be restricted by the
     * display hardware, and differ from the size requested. Note that both
     * minimum and/or maximum size may be restricted.
     * If partial mode is not supported this method does nothing (that's
     * always the case in WINS environment). 
     *
     * @param aRect      Specifies the active area on the screen. Parts outside
     *                   this area will not be visible. Note that x-dimension
     *                   needs to be set, even if it's not currently used
     *
     * @param aMode      Partial mode to be set.
     * 
     * @return KErrNone  if partial mode was successfully activated.
     *                   otherwise system wide error code.
     * @since            S60 v3.0
     */
    virtual TInt SetActiveDisplayArea(TRect& aRect, const TScreensaverPartialMode& aMode) = 0;

    /**
     * With this method the plugin may request Draw() timer to be
     * turned on or off. When on (the default) the plugins Draw() function
     * is called in intervals specified in SetRefreshTimerValue().
     *
     * @param aOn  Specifies whether the refresh timer is used to initiate
     *             Draw() calls.
     */
    virtual void UseRefreshTimer(TBool aOn = ETrue) = 0;

    /**
     * With this method the plugin may request a one-shot timeout event
     * (EScreensaverEventTimeout) after the specified amount of seconds
     * has passed.
     * If the plugin only wants to be displayed for a certain time, this
     * can be used instead of defining a timer in the plugin. Note that the
     * maximum time is about 35 minutes (TTimeIntervalMicroSeconds32).
     * If the screensaver is stopped before the time has passed, the
     * timer will be canceled and callback not issued. The timer is also
     * cancelled after the timeout has occurred. New timeout requests also
     * cancel any pending timeouts before issuing a new one. A time value
     * of 0 just cancels a pending timeout.
     *
     * @param aSecs Desired time in seconds after which a timeout callback
     *              event should be issued. 
     */
    virtual void RequestTimeout(TInt aSecs) = 0;

    /**
     * With this method the plugin can revert to the default screensaver.
     * The plugin will be unloaded, and not used any more until the
     * user re-selects the plugin to be the active screensaver.
     * Should be used when the plugin encounters an unrecoverable error,
     * such as a missing file or expired DRM, and will not be able to run
     * any more.
     * NOTE: A plugin should not expect any events after calling this
     * function.
     */
    virtual void RevertToDefaultSaver() = 0;
    };


/**
* The base class for screensaver plugin modules. Every plugin module
* must inherit and implement this class.
*/
class MScreensaverPlugin 
    {
public:         
    /**
     *  Virtual desctructor.
     */
    virtual ~MScreensaverPlugin() {}

    /**
     * Used to initialize the plugin module after creation.
     * Name() function may be called without the plugin being initialized,
     * to enable name query from modules that are not plugin hosts.
     *
     * @param aHost Screensaver plugin host.
     * @return KErrNone if everything went ok. Otherwise 
     *         system wide error code.
     */
    virtual TInt InitializeL(MScreensaverPluginHost *aHost) = 0;

    /**
     * When a plugin module is active this method is called every time 
     * when refresh timer expires in screensaver application.
     *
     * @param aGc  Graphics context for plugin module to draw to.
     * @return KErrNone if everything went ok. Otherwise 
     *         system wide error code (doesn't have any effect in
     *         current version).
     */
    virtual TInt Draw(CWindowGc& aGc) = 0;

    /**
     * Returns the name of plugin module. Returned name is displayed in
     * the list of installed plugin modules in Themes application.
     * If this function returns an empty name (KNullDesC), displayed name is 
     * taken from ECom registration resource.
     *
     * @return Descriptor containing the name of the plugin module.
     */
    virtual const TDesC16& Name() const = 0;

    /**
     * Handler function for screensaver events.
     *
     * @param aEvent Event to be handled.
     * @param aData  Data related to the event. To be decided on a case-by-case
     * basis.
     *
     * @return KErrNone if OK, otherwise an error code.
     */
    virtual TInt HandleScreensaverEventL(
        TScreensaverEvent aEvent,
        TAny* aData) = 0;

    /**
     * Screensaver plugin capabilities query. The capabilitities
     * reveal which functions the plugin implements, that can be
     * used by calling PluginFunction().
     *
     * @return Bit mask of plugin capabilities.
     *
     * @note Capabilites need to be defined as opaque_data in ECom plugin
     *       registration file as well.
     */
    virtual TInt Capabilities() { return EScpCapsNone; }

    /**
     * Screensaver plugin function method. Only the functions
     * returned by Capabilities() can be used, and only one
     * function at a time.
     *
     * @paran aFunction
     * @param aParam Parameters to the function. TBD function-by-function.
     * 
     * @return System wide error code. KErrNone on success.
     */
    virtual TInt PluginFunction(
        TScPluginCaps /*aFunction*/,
        TAny* /*aParam*/)
        {
        return KErrNone;
        }
    };


#endif   // SCREEN_SAVER_PLUGIN_H

// End of file.
