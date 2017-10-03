#pragma once

#ifndef AL_SOURCE_RELATIVE
	/** Indicate Source has relative coordinates. */
	#define AL_SOURCE_RELATIVE                        0x202
#endif // !AL_SOURCE_RELATIVE

#ifndef AL_CONE_INNER_ANGLE
	/**
	* Directional source, inner cone angle, in degrees.
	* Range:    [0-360]
	* Default:  360
	*/
	#define AL_CONE_INNER_ANGLE                       0x1001
#endif // !AL_CONE_INNER_ANGLE

#ifndef AL_CONE_OUTER_ANGLE
	/**
	* Directional source, outer cone angle, in degrees.
	* Range:    [0-360]
	* Default:  360
	*/
	#define AL_CONE_OUTER_ANGLE                       0x1002
#endif // !AL_CONE_OUTER_ANGLE

#ifndef AL_PITCH
	/**
	* Specify the pitch to be applied, either at source,
	*  or on mixer results, at listener.
	* Range:   [0.5-2.0]
	* Default: 1.0
	*/
	#define AL_PITCH                                  0x1003
#endif // !AL_PITCH

#ifndef AL_POSITION
	/**
	* Specify the current location in three dimensional space.
	* OpenAL, like OpenGL, uses a right handed coordinate system,
	*  where in a frontal default view X (thumb) points right,
	*  Y points up (index finger), and Z points towards the
	*  viewer/camera (middle finger).
	* To switch from a left handed coordinate system, flip the
	*  sign on the Z coordinate.
	* Listener position is always in the world coordinate system.
	*/
	#define AL_POSITION                               0x1004
#endif // !AL_POSITION

#ifndef AL_DIRECTION
	/** Specify the current direction. */
	#define AL_DIRECTION                              0x1005
#endif // !AL_DIRECTION

#ifndef AL_VELOCITY
	/** Specify the current velocity in three dimensional space. */
	#define AL_VELOCITY                               0x1006
#endif // !AL_VELOCITY

#ifndef AL_LOOPING
	/**
	* Indicate whether source is looping.
	* Type: ALboolean?
	* Range:   [AL_TRUE, AL_FALSE]
	* Default: FALSE.
	*/
	#define AL_LOOPING                                0x1007
#endif // !AL_LOOPING

#ifndef AL_BUFFER
	/**
	* Indicate the buffer to provide sound samples.
	* Type: ALuint.
	* Range: any valid Buffer id.
	*/
	#define AL_BUFFER                                 0x1009
#endif // !AL_BUFFER

#ifndef AL_GAIN
	/**
	* Indicate the gain (volume amplification) applied.
	* Type:   ALfloat.
	* Range:  ]0.0-  ]
	* A value of 1.0 means un-attenuated/unchanged.
	* Each division by 2 equals an attenuation of -6dB.
	* Each multiplicaton with 2 equals an amplification of +6dB.
	* A value of 0.0 is meaningless with respect to a logarithmic
	*  scale; it is interpreted as zero volume - the channel
	*  is effectively disabled.
	*/
	#define AL_GAIN                                   0x100A
#endif // !AL_GAIN

#ifndef AL_MIN_GAIN
	/*
	* Indicate minimum source attenuation
	* Type: ALfloat
	* Range:  [0.0 - 1.0]
	*
	* Logarthmic
	*/
	#define AL_MIN_GAIN                               0x100D
#endif // !AL_MIN_GAIN

#ifndef AL_MAX_GAIN
	/**
	* Indicate maximum source attenuation
	* Type: ALfloat
	* Range:  [0.0 - 1.0]
	*
	* Logarthmic
	*/
	#define AL_MAX_GAIN                               0x100E
#endif // !AL_MAX_GAIN

#ifndef AL_ORIENTATION
	/**
	* Indicate listener orientation.
	*
	* at/up
	*/
	#define AL_ORIENTATION                            0x100F
#endif // !AL_ORIENTATION

#ifndef AL_CHANNEL_MASK
	/**
	* Specify the channel mask. (Creative)
	* Type: ALuint
	* Range: [0 - 255]
	*/
	#define AL_CHANNEL_MASK                           0x3000
#endif // !AL_CHANNEL_MASK

#if !defined(AL_SOURCE_STATE) && !defined(AL_INITIAL) && !defined(AL_PLAYING) && !defined(AL_PAUSED) && !defined(AL_STOPPED)
	/**
	* Source state information.
	*/
	#define AL_SOURCE_STATE                           0x1010
	#define AL_INITIAL                                0x1011
	#define AL_PLAYING                                0x1012
	#define AL_PAUSED                                 0x1013
	#define AL_STOPPED                                0x1014
#endif // !AL_SOURCE_STATE && AL_INITIAL && AL_PLAYING && AL_PAUSED && AL_STOPPED

#if !defined(AL_BUFFERS_QUEUED) && !defined(AL_BUFFERS_PROCESSED)
	/**
	* Buffer Queue params
	*/
	#define AL_BUFFERS_QUEUED                         0x1015
	#define AL_BUFFERS_PROCESSED                      0x1016
#endif // !AL_BUFFERS_QUEUED && AL_BUFFERS_PROCESSED

#if !defined(AL_SEC_OFFSET) && !defined(AL_SAMPLE_OFFSET) && !defined(AL_BYTE_OFFSET)
	/**
	* Source buffer position information
	*/
	#define AL_SEC_OFFSET                             0x1024
	#define AL_SAMPLE_OFFSET                          0x1025
	#define AL_BYTE_OFFSET                            0x1026
#endif // !AL_SEC_OFFSET && AL_SAMPLE_OFFSET && AL_BYTE_OFFSET

#if !defined(AL_SOURCE_TYPE) && !defined(AL_STATIC) && !defined(AL_STREAMING) && !defined(AL_UNDETERMINED)
	/*
	* Source type (Static, Streaming or undetermined)
	* Source is Static if a Buffer has been attached using AL_BUFFER
	* Source is Streaming if one or more Buffers have been attached using alSourceQueueBuffers
	* Source is undetermined when it has the NULL buffer attached
	*/
	#define AL_SOURCE_TYPE                            0x1027
	#define AL_STATIC                                 0x1028
	#define AL_STREAMING                              0x1029
	#define AL_UNDETERMINED                           0x1030
#endif // !AL_SOURCE_TYPE && AL_STATIC && AL_STREAMING && AL_UNDETERMINED

#if !defined(AL_FORMAT_MONO8) && !defined(AL_FORMAT_MONO16) && !defined(AL_FORMAT_STEREO8) && !defined(AL_FORMAT_STEREO16)
	/** Sound samples: format specifier. */
	#define AL_FORMAT_MONO8                           0x1100
	#define AL_FORMAT_MONO16                          0x1101
	#define AL_FORMAT_STEREO8                         0x1102
	#define AL_FORMAT_STEREO16                        0x1103
#endif // !AL_FORMAT_MONO8 && AL_FORMAT_MONO16 && AL_FORMAT_STEREO8 && AL_FORMAT_STEREO16

#ifndef AL_REFERENCE_DISTANCE
	/**
	* source specific reference distance
	* Type: ALfloat
	* Range:  0.0 - +inf
	*
	* At 0.0, no distance attenuation occurs.  Default is
	* 1.0.
	*/
	#define AL_REFERENCE_DISTANCE                     0x1020
#endif // !AL_REFERENCE_DISTANCE

#ifndef AL_ROLLOFF_FACTOR
	/**
	* source specific rolloff factor
	* Type: ALfloat
	* Range:  0.0 - +inf
	*
	*/
	#define AL_ROLLOFF_FACTOR                         0x1021
#endif // !AL_ROLLOFF_FACTOR

#ifndef AL_CONE_OUTER_GAIN
	/**
	* Directional source, outer cone gain.
	*
	* Default:  0.0
	* Range:    [0.0 - 1.0]
	* Logarithmic
	*/
	#define AL_CONE_OUTER_GAIN                        0x1022
#endif // !AL_CONE_OUTER_GAIN

#ifndef AL_MAX_DISTANCE
	/**
	* Indicate distance above which sources are not
	* attenuated using the inverse clamped distance model.
	*
	* Default: +inf
	* Type: ALfloat
	* Range:  0.0 - +inf
	*/
	#define AL_MAX_DISTANCE                           0x1023
#endif // !AL_MAX_DISTANCE

#if !defined(AL_FREQUENCY) && !defined(AL_BITS) && !defined(AL_CHANNELS) && !defined(AL_SIZE)
	/**
	* Sound samples: frequency, in units of Hertz [Hz].
	* This is the number of samples per second. Half of the
	*  sample frequency marks the maximum significant
	*  frequency component.
	*/
	#define AL_FREQUENCY                              0x2001
	#define AL_BITS                                   0x2002
	#define AL_CHANNELS                               0x2003
	#define AL_SIZE                                   0x2004
#endif // !AL_FREQUENCY && AL_BITS && AL_CHANNELS && AL_SIZE