/*! \file
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(ZFORCETYPES_H) && !defined(CONTAINS_CARTESIANCOORDINATES) && !defined(CONTAINS_TOUCHACTIVEAREA) \
&& !defined(CONTAINS_REVERSETOUCHACTIVEAREA)

#ifdef COMPILING_ZFORCE_SDK
typedef struct zForceHandler zForceHandler;
#endif // COMPILING_ZFORCE_SDK
//! \sa struct zForce
typedef struct zForce zForce;
//! \sa struct Connection
typedef struct Connection Connection;
//! \sa struct Device
typedef struct Device Device;
//! \sa struct PlatformDevice
typedef struct PlatformDevice PlatformDevice;
//! \sa struct SensorDevice
typedef struct SensorDevice SensorDevice;
//! \sa struct CoreDevice
typedef struct CoreDevice CoreDevice;
//! \sa struct AirDevice
typedef struct AirDevice AirDevice;
//! \sa struct PlusDevice
typedef struct PlusDevice PlusDevice;
//! \sa struct LightingDevice
typedef struct LightingDevice LightingDevice;
//! \sa struct Protocol
typedef struct Protocol Protocol;
//! \sa struct ProtocolEntry
typedef struct ProtocolEntry ProtocolEntry;
//! \sa struct Transport
typedef struct Transport Transport;
//! \sa struct TransportEntry
typedef struct TransportEntry TransportEntry;
//! \sa struct DataFrame
typedef struct DataFrame DataFrame;
//! \sa struct StreamingDataFrame
typedef struct StreamingDataFrame StreamingDataFrame;
//! \sa struct Message
typedef struct Message Message;
//! \sa struct EnableMessage
typedef struct EnableMessage EnableMessage;
//! \sa struct DisableMessage
typedef struct DisableMessage DisableMessage;
//! \sa struct OperationModesMessage
typedef struct OperationModesMessage OperationModesMessage;
//! \sa struct ResolutionMessage
typedef struct ResolutionMessage ResolutionMessage;
//! \sa struct TouchActiveAreaMessage
typedef struct TouchActiveAreaMessage TouchActiveAreaMessage;
//! \sa struct TouchMessage
typedef struct TouchMessage TouchMessage;
//! \sa struct NumberOfTrackedObjectsMessage
typedef struct NumberOfTrackedObjectsMessage NumberOfTrackedObjectsMessage;
//! \sa struct FingerFrequencyMessage
typedef struct FingerFrequencyMessage FingerFrequencyMessage;
//! \sa struct IdleFrequencyMessage
typedef struct IdleFrequencyMessage IdleFrequencyMessage;
//! \sa struct DetectedObjectSizeRestrictionMessage
typedef struct DetectedObjectSizeRestrictionMessage DetectedObjectSizeRestrictionMessage;
//! \sa struct ReverseTouchActiveAreaMessage
typedef struct ReverseTouchActiveAreaMessage ReverseTouchActiveAreaMessage;
//! \sa struct McuUniqueIdentifierMessage
typedef struct McuUniqueIdentifierMessage McuUniqueIdentifierMessage;
//! \sa struct OffsetMessage
typedef struct OffsetMessage OffsetMessage;
//! \sa struct HidDisplaySizeMessage
typedef struct HidDisplaySizeMessage HidDisplaySizeMessage;
//! \sa struct FlipXYMessage
typedef struct FlipXYMessage FlipXYMessage;
//! \sa struct ReflectiveEdgeMessage
typedef struct ReflectiveEdgeFilterMessage ReflectiveEdgeFilterMessage;
//! \sa struct MergeTouchesMessage
typedef struct MergeTouchesMessage MergeTouchesMessage;

//! Enum describing the different device types that exists.
enum DeviceType
{
    None = 0,
    Platform = 1,
    Sensor = 2,
    Core = 4,
    Air = 8,
    Plus = 16,
    Lighting = 32
};
//! \sa enum DeviceType
typedef enum DeviceType DeviceType;

//! Enum describing the different message types that exists.
enum MessageType
{
    EnableMessageType,
    DisableMessageType,
    OperationModesMessageType,
    ResolutionMessageType,
    TouchActiveAreaMessageType,
    TouchMessageType,
    DetectedObjectSizeRestrictionMessageType,
    NumberOfTrackedObjectsMessageType,
    FingerFrequencyMessageType,
    IdleFrequencyMessageType,
    ReverseTouchActiveAreaMessageType,
    McuUniqueIdentifierMessageType,
    OffsetMessageType,
    HidDisplaySizeMessageType,
    FlipXYMessageType,
    ReflectiveEdgeFilterMessageType,
    MergeTouchesMessageType,
    HighestValidMessageType = MergeTouchesMessageType
};
//! \sa enum MessageType
typedef enum MessageType MessageType;


//! Enum describing the different groups a message can belong to.
enum MessageGroup
{
    Request,
    Response,
    Notification,
    HighestValidMessageGroup = Notification
};
//! \sa enum MessageGroup
typedef enum MessageGroup MessageGroup;


//! Enum describing the action of a message.
enum MessageAction
{
    GetAction,   //!< Get information from device.
    SetAction    //!< Set information on device.
};
//! \sa enum MessageAction
typedef enum MessageAction MessageAction;

//! Enum describing the OperationModes that a sensor can operate in.
enum OperationModes
{
    NoOperationMode = 0,  //!< No Mode set.
    DetectionMode = 1,    //!< Detection Mode (Touch).
    SignalsMode = 2,      //!< Signals Mode.
    LedLevelsMode = 4,    //!< Led Levels Mode.
    DetectionHidMode = 8, //!< Detection Mode for Hid Devices.
    GesturesMode = 16,    //!< Gestures Mode.
    //! Special value used for error checking.
    HighestValidOperationMode = (GesturesMode * 2) - 1
};
//! \sa enum OperationModes
typedef enum OperationModes OperationModes;


//! Enum describing what state a touch can be in.
enum TouchEvent
{
    DownEvent,          //!< New Touch object detected.
    MoveEvent,          //!< The Touch object is moving.
    UpEvent,            //!< The Touch object is no longer detected.
    UpPendingEvent,     //!< Panding state.
    DownPendingEvent,   //!< Panding state.
    InvalidEvent,       //!< Invalid Touch event reported by Device.
    GhostEvent          //!< Ghost touch detected.
};
//! \sa enum TouchEvent
typedef enum TouchEvent TouchEvent;

//! Enum describing what orientation touches are generated in.
enum TouchOrientation
{
    PortraitOrientation, //!< Object is in Portrait orientation.
    LandscapeOrientation //!< Object is in Landscape orientation.
};
//! \sa enum TouchOrientation
typedef enum TouchOrientation TouchOrientation;

//! \sa enum CartesianCoordinates
typedef struct CartesianCoordinates CartesianCoordinates;
/*!
* \brief Struct representing a coordinate.
*
* Struct representing a coordinate with up to three dimensions.
*/
struct CartesianCoordinates
{
#endif // !defined(ZFORCETYPES_H) && !defined(CON_CARTESIAN) && !defined (CON_TAA) && !defined (CON_REVTAA)
#if !defined(ZFORCETYPES_H) || defined(CONTAINS_CARTESIANCOORDINATES)
    uint32_t X;    //!< X axis value.
    bool     HasX; //!< Is set to true if the coordinate system has a X axis.
    uint32_t Y;    //!< Y axis value.
    bool     HasY; //!< Is set to true if the coordinate system has a Y axis.
    uint32_t Z;    //!< Z axis value.
    bool     HasZ; //!< Is set to true if the coordinate system has a Z axis.
#endif // !defined(ZFORCETYPES_H) || defined(CONTAINS_CARTESIANCOORDINATES)
#if !defined(ZFORCETYPES_H) && !defined(CONTAINS_CARTESIANCOORDINATES) && !defined(CONTAINS_TOUCHACTIVEAREA) \
&& !defined(CONTAINS_REVERSETOUCHACTIVEAREA)
};

//! \sa enum TouchActiveArea
typedef struct TouchActiveArea TouchActiveArea;
/*!
 * \brief This structure represents the Touch Active Area of a sensor.
 *
 * This structure represents the Touch Active Area of a sensor.
 * The Touch Active Area is the area which a sensor will report touches from.
 */
struct TouchActiveArea
{
#endif
#if !defined(ZFORCETYPES_H) || defined(CONTAINS_TOUCHACTIVEAREA)
    uint32_t LowerBoundaryX; //!< Start of the Touch Active Area X axis.
    uint32_t UpperBoundaryX; //!< End of the Touch Active Area X axis.
    bool     HasX;           //!< True if the coordinate system has a X axis.
    uint32_t LowerBoundaryY; //!< Start of the Touch Active Area Y axis.
    uint32_t UpperBoundaryY; //!< End of the Touch Active Area Y axis.
    bool     HasY;           //!< True if the coordinate system has a Y axis.
#endif // !defined(ZFORCETYPES_H) || defined(CONTAINS_TOUCHACTIVEAREA)
#if !defined(ZFORCETYPES_H) && !defined(CONTAINS_CARTESIANCOORDINATES) && !defined(CONTAINS_TOUCHACTIVEAREA) \
&& !defined(CONTAINS_REVERSETOUCHACTIVEAREA)
};

//! \sa enum ReverseTouchActiveArea
typedef struct ReverseTouchActiveArea ReverseTouchActiveArea;
/*!
 * \brief This structure represents whether the Touch Active Area coordinates are reversed or not.
 *
 * This structure represents whether the Touch Active Area axes are reversed or not.
 * The X and Y axes can be reversed individually by setting respective boolean to true or false.
 */
struct ReverseTouchActiveArea
{
#endif
#if !defined(ZFORCETYPES_H) || defined(CONTAINS_REVERSETOUCHACTIVEAREA)
    bool XIsReversed;   //!< True if the X axis is reversed.
    bool YIsReversed;   //!< True if the Y axis is reversed.
#endif // !defined(ZFORCETYPES_H) || defined(CONTAINS_REVERSETOUCHACTIVEAREA)
#if !defined(ZFORCETYPES_H) && !defined(CONTAINS_CARTESIANCOORDINATES) && !defined(CONTAINS_TOUCHACTIVEAREA) \
&& !defined(CONTAINS_REVERSETOUCHACTIVEAREA)
};

#define ZFORCETYPES_H
#endif // !defined(ZFORCETYPES_H) && !defined(CON_CARTESIAN) && !defined (CON_TAA) && !defined (CON_REVTAA)
