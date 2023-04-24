//
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) Contributors to the OpenEXR Project.
//

#ifndef INCLUDED_IMF_STANDARD_ATTRIBUTES_H
#define INCLUDED_IMF_STANDARD_ATTRIBUTES_H

//-----------------------------------------------------------------------------
//
//	Optional Standard Attributes -- these attributes are "optional"
//	because not every image file header has them, but they define a
//	"standard" way to represent commonly used data in the file header.
//
//	For each attribute, with name "foo", and type "T", the following
//	functions are automatically generated via macros:
//
//	void			   addFoo (Header &header, const T &value);
//	bool			   hasFoo (const Header &header);
//	const TypedAttribute<T> &  fooAttribute (const Header &header);
//	TypedAttribute<T> &	   fooAttribute (Header &header);
//	const T &		   foo (const Header &Header);
//	T &			   foo (Header &Header);
//
//-----------------------------------------------------------------------------

#include "ImfBoxAttribute.h"
#include "ImfChromaticitiesAttribute.h"
#include "ImfDeepImageStateAttribute.h"
#include "ImfEnvmapAttribute.h"
#include "ImfExport.h"
#include "ImfFloatAttribute.h"
#include "ImfHeader.h"
#include "ImfIDManifestAttribute.h"
#include "ImfIntAttribute.h"
#include "ImfKeyCodeAttribute.h"
#include "ImfMatrixAttribute.h"
#include "ImfNamespace.h"
#include "ImfRationalAttribute.h"
#include "ImfStringAttribute.h"
#include "ImfStringVectorAttribute.h"
#include "ImfTimeCodeAttribute.h"
#include "ImfVecAttribute.h"

#define IMF_ADD_SUFFIX(suffix) add##suffix
#define IMF_HAS_SUFFIX(suffix) has##suffix
#define IMF_NAME_ATTRIBUTE(name) name##Attribute

#define IMF_STD_ATTRIBUTE_DEF(name, suffix, object)                            \
                                                                               \
    OPENEXR_IMF_INTERNAL_NAMESPACE_HEADER_ENTER                                \
    IMF_EXPORT void IMF_ADD_SUFFIX (suffix) (                                  \
        Header & header, const object& v);                                     \
    IMF_EXPORT bool  IMF_HAS_SUFFIX (suffix) (const Header& header);           \
    IMF_EXPORT const TypedAttribute<object>& IMF_NAME_ATTRIBUTE (name) (       \
        const Header& header);                                                 \
    IMF_EXPORT TypedAttribute<object>& IMF_NAME_ATTRIBUTE (name) (             \
        Header & header);                                                      \
    IMF_EXPORT const object& name (const Header& header);                      \
    IMF_EXPORT object&       name (Header& header);                            \
    OPENEXR_IMF_INTERNAL_NAMESPACE_HEADER_EXIT

#define IMF_STD_ATTRIBUTE_DEF_DEPRECATED(name, suffix, object, msg)            \
                                                                               \
    OPENEXR_IMF_INTERNAL_NAMESPACE_HEADER_ENTER                                \
    OPENEXR_DEPRECATED (msg)                                                   \
    IMF_EXPORT void IMF_ADD_SUFFIX (suffix) (                                  \
        Header & header, const object& v);                                     \
    OPENEXR_DEPRECATED (msg)                                                   \
    IMF_EXPORT bool IMF_HAS_SUFFIX (suffix) (const Header& header);            \
    OPENEXR_DEPRECATED (msg)                                                   \
    IMF_EXPORT const TypedAttribute<object>& IMF_NAME_ATTRIBUTE (name) (       \
        const Header& header);                                                 \
    OPENEXR_DEPRECATED (msg)                                                   \
    IMF_EXPORT TypedAttribute<object>& IMF_NAME_ATTRIBUTE (name) (             \
        Header & header);                                                      \
    OPENEXR_DEPRECATED (msg)                                                   \
    IMF_EXPORT const object&                    name (const Header& header);   \
    OPENEXR_DEPRECATED (msg) IMF_EXPORT object& name (Header& header);         \
    OPENEXR_IMF_INTERNAL_NAMESPACE_HEADER_EXIT

//
// In attribute definition comments below, 'UTF-8-encoded' signifies
//   a sequence of zero or more characters encoded using Unicode UTF-8 encoding
//   in NFC normal form, as defined in the Unicode standard.

//
// originalDataWindow -- if application software crops an image, then it
// should save the data window of the original, un-cropped image in the
// originalDataWindow attribute.
//

IMF_STD_ATTRIBUTE_DEF (
    originalDataWindow, OriginalDataWindow, IMATH_NAMESPACE::Box2i)

//
// worldToCamera -- for images generated by 3D computer graphics rendering,
// a matrix that transforms 3D points from the world to the camera coordinate
// space of the renderer.
//
// The camera coordinate space is left-handed.  Its origin indicates the
// location of the camera.  The positive x and y axes correspond to the
// "right" and "up" directions in the rendered image.  The positive z
// axis indicates the camera's viewing direction.  (Objects in front of
// the camera have positive z coordinates.)
//
// Camera coordinate space in OpenEXR is the same as in Pixar's Renderman.
//

IMF_STD_ATTRIBUTE_DEF (worldToCamera, WorldToCamera, IMATH_NAMESPACE::M44f)

//
// worldToNDC -- for images generated by 3D computer graphics rendering, a
// matrix that transforms 3D points from the world to the Normalized Device
// Coordinate (NDC) space of the renderer.
//
// NDC is a 2D coordinate space that corresponds to the image plane, with
// positive x and pointing to the right and y positive pointing down.  The
// coordinates (0, 0) and (1, 1) correspond to the upper left and lower right
// corners of the OpenEXR display window.
//
// To transform a 3D point in word space into a 2D point in NDC space,
// multiply the 3D point by the worldToNDC matrix and discard the z
// coordinate.
//
// NDC space in OpenEXR is the same as in Pixar's Renderman.
//

IMF_STD_ATTRIBUTE_DEF (worldToNDC, WorldToNDC, IMATH_NAMESPACE::M44f)

//
// ascFramingDecisionList -- JSON-encoded description of framing decisions
// associated with the captured image, in a format termed 'ASC-FDL', designed
// and documented by the American Society of Cinematographers (ASC).
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (ascFramingDecisionList, AscFramingDecisionList, std::string)

//
// xDensity -- horizontal output density, in pixels per inch.
// The image's vertical output density is xDensity * pixelAspectRatio.
//

IMF_STD_ATTRIBUTE_DEF (xDensity, XDensity, float)

//
// longitude, latitude, altitude -- for images of real objects, the
// location where the image was recorded.  Longitude and latitude are
// in degrees east of Greenwich and north of the equator.  Altitude
// is in meters above sea level.  For example, Kathmandu, Nepal is
// at longitude 85.317, latitude 27.717, altitude 1305.
//

IMF_STD_ATTRIBUTE_DEF (longitude, Longitude, float)
IMF_STD_ATTRIBUTE_DEF (latitude, Latitude, float)
IMF_STD_ATTRIBUTE_DEF (altitude, Altitude, float)

//
// cameraMake -- manufacturer or vendor of the camera
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (cameraMake, CameraMake, std::string)

//
// cameraModel -- model name or model number of the camera
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (cameraModel, CameraModel, std::string)

//
// cameraSerialNumber -- serial number of the camera
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//
// Note that despite the name, the value can include non-digits
// as well as digits.
//

IMF_STD_ATTRIBUTE_DEF (cameraSerialNumber, CameraSerialNumber, std::string)

//
// cameraFirmwareVersion -- the firmware version of the camera
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (cameraFirmwareVersion, CameraFirmwareVersion, std::string)

//
// cameraUuid -- identifies this camera uniquely among all
// cameras from all vendors
//
// Uniqueness could be accomplished with, e.g., a MAC address, a
// concatenation of cameraMake, cameraModel, cameraSerialNumber, etc.
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (cameraUuid, CameraUuid, std::string)

//
// cameraLabel -- text label identifying how the camera was used or
// assigned, e.g. "Camera 1 Left", "B Camera", "POV", etc
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (cameraLabel, CameraLabel, std::string)

//
// cameraCCTSetting -- color temperature, in Kelvin, configured
// for the physical or virtual camera creating or capturing the image.
//
// The cameraCCTSetting is primarily forensic, and indicates the
// stated color balance of a film stock, the color temperature setting
// on a physical digital camera or the nominal color temperature of the
// scene adopted white as passed to a virtual camera's API.
//
// A professional digital cinema cameras is not constrained to map every
// supplied correlated color temperature to a point on the curve of a
// Planckian radiator, or map every supplied color temperature to a
// chromaticity corresponding to a combination of the three principal
// components forming a basis for the CIE D series of illuminants.
//
// Often, lower color temperatures are on the Planckian locus, higher
// color temperatures are on a locus of CIE D series chromaticities, and
// the camera performs a crossfade (typically a linear crossfade) between
// the two for intermediate temperatures. That the start and end of the
// crossfade could differ for every camera vendor -- or even across cameras
// offered by the same vendor -- means that no universal algorithm can map
// a camera color temperature setting (combined with a tint setting,
// see below) into a scene adopted white chromaticity.
//
// The most common use for the cameraCCTSetting attribute is to feed its
// value into a camera-vendor-provided application or API, along with
// a cameraTintSetting attribute value, to reproduce the color processing
// done in-camera on set.
//
// If a cameraCCTSetting attribute is provided, and no cameraTintSetting
// is provided, then a value of zero should be passed to any application
// or API using the cameraCCTSetting and cameraTintSetting.
//

IMF_STD_ATTRIBUTE_DEF (cameraCCTSetting, CameraCCTSetting, float)

//
// cameraTintSetting -- green / magenta tint configured for the physical
// or virtual camera creating or capturing the image.
//
// The cameraTintSetting is primarily forensic. There is no vendor-
// independent mapping from a unit of tint to a distance on a chromaticity
// diagram. One camera vendor might choose a color space (e.g. the
// CIE 1960 UCS) and have a unit amount of tint represent some delta uv
// distance from the point by the cammeraCCTSetting and a tint value of 0.
// Another might choose to express the effect of tint by analogy to a
// traditional unit from a film workflow, e.g. a Kodak or Rosco color
// correction filter. About the only guaranteed commonality is that all
// camera vendor tint schemes have positive values shift the adopted
// scene white towards green, and negative values toward magenta.
//
// If the camera vendor maps cameraCCTSetting to a point defined by
// a linear crossfade between a Planckian blackbody locus and loci of
// CIE D Series illuminants, the slope of the tint isotherm at the
// exact points where the linear crossfade starts and ends can be 
// indeterminate and an inverse mapping from chromaticity to a pair
// of CCT and tint can be one-to-many.
//
// The most common use for the cameraTintSetting attribute is to feed its
// value into a camera-vendor-provided application or API, along with
// a cameraCCTSetting attribute value, to reproduce the color processing
// done in-camera on set.
//

IMF_STD_ATTRIBUTE_DEF (cameraTintSetting, CameraTintSetting, float)

//
// cameraColorBalance -- chromaticity in CIE 1960 UCS coordinates
// indicating a color the user of the camera would like the camera
// to treat as neutral, and corresponding to a particular camera
// configuration of make, model, camera firmware version, CCT setting
// and tint setting.
//
// Note that this is not necessarily (or even probably) the same
// chromaticity as that of the scene adopted white stored in an
// adoptedNeutral attribute (if present).
//
// For example, if a physical digital cinema camera was configured with
// a CCT of 3200K and a tint of -3 (in some camera vendor dependent unit),
/// and the camera output had been processed such that the image containing
// this attribute was encoded as per SMPTE ST 2065-4:2023, then 
// the adoptedNeutral attribute would have the value corresponding to
// the ACES neutral chromaticity, very near that of CIE Illuminant D60,
// whereas the cameraColorBalance would have a chromaticity much, much
// warmer than that of the adoptedNeutral attribute.
// 

IMF_STD_ATTRIBUTE_DEF (cameraColorBalance, CameraColorBalance, IMATH_NAMESPACE::V2f)

//
// isoSpeed -- the ISO speed of the film or the ISO setting of the camera
// that was used to record the image
//

IMF_STD_ATTRIBUTE_DEF (isoSpeed, IsoSpeed, float)

//
// exposure -- exposure time, in seconds
//

IMF_STD_ATTRIBUTE_DEF (expTime, ExpTime, float)

//
// shutterAngle -- shutter angle, in degrees
//
// For a physical film or digital camera, changing the shutter angle
// inexorably affects both motion blur and exposure. For a CG camera,
// the parameters to the renderer control whether or not changing the
// shutter angle affects simulation of either or both of these phenomena.
//

IMF_STD_ATTRIBUTE_DEF (shutterAngle, ShutterAngle, float)

//
// captureRate -- capture rate, in frames per second, of the image
// sequence to which the image belongs, represented as a rational
// number
// 
// For variable frame rates, time-lapse photography, etc. the capture
// rate r is calculated as
//
//   r = 1 / (tN - tNm1)
//
// where tn is the time, in seconds, of the center of frame N's 
// exposure interval, and tNm1 is the time, in seconds, of the center
// of frame N-1's exposure interval.
//
// Both the numerator and denominator of r must be strictly positive.
//

IMF_STD_ATTRIBUTE_DEF (captureRate, CaptureRate, Rational)

//
// lensMake -- manufacturer or vendor of the lens
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (lensMake, LensMake, std::string)

//
// lensModel -- model name or model number of the lens
//
// If present, the value should be UTF-8-e coded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (lensModel, LensModel, std::string)

//
// lensSerialNumber -- serial number of the lens
//
// Note that despite the name, the value can include non-digits
// as well as digits.
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (lensSerialNumber, LensSerialNumber, std::string)

//
// lensFirmwareVersion -- firmware version of the lens
//

// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (lensFirmwareVersion, LensFirmwareVersion, std::string)

//
// nominalFocalLength -- number printed on barrel of a prime lens, or
// number next to index mark on a zoom lens, in units of millimeters.
//
// Nominal focal length is appropriate for asset tracking of lenses (e.g.
// a camera rental house catalogs its lens stock by nominal focal length).
//

IMF_STD_ATTRIBUTE_DEF (nominalFocalLength, NominalFocalLength, float)

//
// pinholeFocalLength -- in the simplest model of image formation, the
// distance between the pinhole and the image plane, in units of millimeters.
//
// When a CGI application supplies a method for an artist to provide focal
// length to some calculation, pinhole focal length is almost always the
// appropriate number to convey to the application.
//

IMF_STD_ATTRIBUTE_DEF (pinholeFocalLength, PinholeFocalLength, float)

//
// effectiveFocalLength -- in the thick lens model, the effective focal
// length is the distance between the front focal point and the front
// nodal point, or equivalently the back focal point and the back nodal
// point, in units of millimeters.
//
// The effective focal length is an abstraction used in lens design and,
// unless a CGI application is sophisticated enough to be using the thick
// lens model, should not be supplied to the application; for normal
// CGI applications, pinhole focal length should be used.
//
// Note that the forward and back lens nodal points mentioned above are
// distinct in meaning and in position from the forward and back lens
// entrance pupils. A 'no-parallax' rotation is rotation around the
// forward lens entrance pupil.
//

IMF_STD_ATTRIBUTE_DEF (effectiveFocalLength, EffectiveFocalLength, float)

//
// entrancePupilOffset -- the axial distance from the image plane
// to the ientrance pupil, in units of millimeters. A larger entrance
// pupil offset means the entrance pupil is closer to the object.
//
// Note that in some lens configurations, the entrance pupil offset can
// be negative.
//

IMF_STD_ATTRIBUTE_DEF (entrancePupilOffset, EntrancePupilOffset, float)

//
// aperture -- the f-number of the lens, computed as the ratio of
// lens focal length to diameter of lens entrance pupil at the time
// the image was created or captured
// 
// The lens focal length used in the calculation is the nominal focal
// length which would be stored in the focalLength attribute, even if
// the effective focal length (compensating for any focus breathing)
// is known and stored in an effectiveFocalLength attribute.
//

IMF_STD_ATTRIBUTE_DEF (aperture, Aperture, float)

//
// tStop -- ratio of lens focal length to diameter of entrance pupil,
// divided by the square root of the transmittance the lens presents
// to a paraxial ray.
//
// Note that tStop, like aperture, must be strictly positive;
// and that tStop will always be a larger number than aperture.
//

IMF_STD_ATTRIBUTE_DEF (tStop, TStop, float)

//
// focus -- the camera's focus distance, in meters
//

IMF_STD_ATTRIBUTE_DEF (focus, Focus, float)

//
// owner -- name of the owner of the image
//

IMF_STD_ATTRIBUTE_DEF (owner, Owner, std::string)

//
// comments -- additional image information in human-readable
// form, for example a verbal description of the image.
//

IMF_STD_ATTRIBUTE_DEF (comments, Comments, std::string)

//
// capDate -- the date when the image was created or captured,
// in local time, and formatted as
//
//    YYYY:MM:DD hh:mm:ss
//
// where YYYY is the year (4 digits, e.g. 2003), MM is the month
// (2 digits, 01, 02, ... 12), DD is the day of the month (2 digits,
// 01, 02, ... 31), hh is the hour (2 digits, 00, 01, ... 23), mm
// is the minute, and ss is the second (2 digits, 00, 01, ... 59).
//

IMF_STD_ATTRIBUTE_DEF (capDate, CapDate, std::string)

//
// utcOffset -- offset of local time at capDate from
// Universal Coordinated Time (UTC), in seconds:
//
//    UTC == local time + utcOffset
//

IMF_STD_ATTRIBUTE_DEF (utcOffset, UtcOffset, float)

//
// keyCode -- for motion picture film frames.  Identifies film
// manufacturer, film type, film roll and frame position within
// the roll.
//

IMF_STD_ATTRIBUTE_DEF (keyCode, KeyCode, KeyCode)

//
// timeCode -- time and control code
//

IMF_STD_ATTRIBUTE_DEF (timeCode, TimeCode, TimeCode)

//
// framesPerSecond -- defines the nominal playback frame rate for image
// sequences, in frames per second.  Every image in a sequence should
// have a framesPerSecond attribute, and the attribute value should be
// the same for all images in the sequence.  If an image sequence has
// no framesPerSecond attribute, playback software should assume that
// the frame rate for the sequence is 24 frames per second.
//
// In order to allow exact representation of NTSC frame and field rates,
// framesPerSecond is stored as a rational number.  A rational number is
// a pair of integers, n and d, that represents the value n/d.
//
// For the exact values of commonly used frame rates, please see header
// file ImfFramesPerSecond.h.
//

IMF_STD_ATTRIBUTE_DEF (framesPerSecond, FramesPerSecond, Rational)

//
// timecodeRate -- the nominal playback rate associated with
// the image sequence to which the image belongs, specified in
// timecodes per second.
//
// The integer timecodeRate attribute is a rounding of the
// framesPerSecond attribute.
//
// The rounding is atypical: in the special case of the nominal
// playback rate corresponding exactly to the midpoint of two
// adjacent integer values, timecodeRate is defined to always
// be the rounding up to the next larlgest integer.
//
// This stands in contrast to the default IEEE 754 rounding for
// decimal arithmetic in which such a midpoint value would always
// be rounded to the nearest even integer.
//

IMF_STD_ATTRIBUTE_DEF (timecodeRate, TimecodeRate, int)

//
// imageCounter -- an image number
//
// For a sequence of images, the image number increases 
// when the images are accessed in the intended play order. 
// imageCounter can be used to order frames when more standard
// ordering systems are inapplicable, including but not limited
// to uniquely identifying frames of high-speed photography that
// would have identical time codes, ordering sequences of frames
// where some frames may have been captured and discarded due to
// real-time constraints, or ordering frames in a sequence that
// is intermittently accumulated from devices such as security
// cameras triggered by motion in an environment.
//

IMF_STD_ATTRIBUTE_DEF (imageCounter, ImageCounter, int)

//
// reelName -- name for a sequence of unique images.
//
// If present, the value should be UTF-8-encoded and have a nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (reelName, ReelName, std::string)

//
// chromaticities -- for RGB images, specifies the CIE (x,y)
// chromaticities of the primaries and the white point
//

IMF_STD_ATTRIBUTE_DEF (chromaticities, Chromaticities, Chromaticities)

//
// whiteLuminance -- for RGB images, defines the luminance, in Nits
// (candelas per square meter) of the RGB value (1.0, 1.0, 1.0).
//
// If the chromaticities and the whiteLuminance of an RGB image are
// known, then it is possible to convert the image's pixels from RGB
// to CIE XYZ tristimulus values (see function RGBtoXYZ() in header
// file ImfChromaticities.h).
//

IMF_STD_ATTRIBUTE_DEF (whiteLuminance, WhiteLuminance, float)

//
// adoptedNeutral -- specifies the CIE (x,y) coordinates that should
// be considered neutral during color rendering.  Pixels in the image
// file whose (x,y) coordinates match the adoptedNeutral value should
// be mapped to neutral values on the display.
//

IMF_STD_ATTRIBUTE_DEF (adoptedNeutral, AdoptedNeutral, IMATH_NAMESPACE::V2f)

//
// renderingTransform, lookModTransform -- specify the names of the
// CTL functions that implements the intended color rendering and look
// modification transforms for this image.
//
// If present, values should be UTF-8-encoded and have nonzero length.
//

IMF_STD_ATTRIBUTE_DEF (renderingTransform, RenderingTransform, std::string)
IMF_STD_ATTRIBUTE_DEF (lookModTransform, LookModTransform, std::string)

//
// envmap -- if this attribute is present, the image represents
// an environment map.  The attribute's value defines how 3D
// directions are mapped to 2D pixel locations.  For details
// see header file ImfEnvmap.h
//

IMF_STD_ATTRIBUTE_DEF (envmap, Envmap, Envmap)

//
// wrapmodes -- determines how texture map images are extrapolated.
// If an OpenEXR file is used as a texture map for 3D rendering,
// texture coordinates (0.0, 0.0) and (1.0, 1.0) correspond to
// the upper left and lower right corners of the data window.
// If the image is mapped onto a surface with texture coordinates
// outside the zero-to-one range, then the image must be extrapolated.
// This attribute tells the renderer how to do this extrapolation.
// The attribute contains either a pair of comma-separated keywords,
// to specify separate extrapolation modes for the horizontal and
// vertical directions; or a single keyword, to specify extrapolation
// in both directions (e.g. "clamp,periodic" or "clamp").  Extra white
// space surrounding the keywords is allowed, but should be ignored
// by the renderer ("clamp, black " is equivalent to "clamp,black").
// The keywords listed below are predefined; some renderers may support
// additional extrapolation modes:
//
//	black		pixels outside the zero-to-one range are black
//
//	clamp		texture coordinates less than 0.0 and greater
//			than 1.0 are clamped to 0.0 and 1.0 respectively
//
//	periodic	the texture image repeats periodically
//
//	mirror		the texture image repeats periodically, but
//			every other instance is mirrored
//

IMF_STD_ATTRIBUTE_DEF (wrapmodes, Wrapmodes, std::string)

//
// multiView -- defines the view names for multi-view image files.
// A multi-view image contains two or more views of the same scene,
// as seen from different viewpoints, for example a left-eye and
// a right-eye view for stereo displays.  The multiView attribute
// lists the names of the views in an image, and a naming convention
// identifies the channels that belong to each view.
//
// For details, please see header file ImfMultiView.h
//

IMF_STD_ATTRIBUTE_DEF (multiView, MultiView, StringVector)

//
// deepImageState -- specifies whether the pixels in a deep image are
// sorted and non-overlapping.
//
// Note: this attribute can be set by application code that writes a file
// in order to tell applications that read the file whether the pixel data
// must be cleaned up prior to image processing operations such as flattening.
// The OpenEXR library does not verify that the attribute is consistent with
// the actual state of the pixels.  Application software may assume that the
// attribute is valid, as long as the software will not crash or lock up if
// any pixels are inconsistent with the deepImageState attribute.
//

IMF_STD_ATTRIBUTE_DEF (deepImageState, DeepImageState, DeepImageState)

//
// dwaCompressionLevel -- sets the quality level for images compressed
// with the DWAA or DWAB method.
//
// DEPRECATED: use the methods directly in the header
IMF_STD_ATTRIBUTE_DEF_DEPRECATED (
    dwaCompressionLevel,
    DwaCompressionLevel,
    float,
    "use compression method in ImfHeader")

//
// ID Manifest
//

IMF_STD_ATTRIBUTE_DEF (idManifest, IDManifest, CompressedIDManifest)

#endif
