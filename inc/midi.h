#define STM32F40XX
#ifndef MIDI_H
#define MIDI_H

#if defined MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "fifo.h"
#include "velocity.h"

EXTERN FIFO8(128) midiMessagesArray; //Array for midi messages buffer
EXTERN FIFO8(8) notes; //Array for current note
EXTERN FIFO16(8) durations; //Array for duration for current note

/*! Type definition for practical use (because "unsigned char" is a bit long to write.. )*/
typedef uint8_t byte;
typedef uint16_t word;

/*! Enumeration of MIDI types */
enum kMIDIType {
	NoteOff = 0x80, ///< Note Off
	NoteOn = 0x90, ///< Note On
	HiresPrefix1 = 0xB0, ///<Hi res Prefix
	HiresPrefix2 = 0x58, ///<Hi res Prefix
	AfterTouchPoly = 0xA0, ///< Polyphonic AfterTouch
	ControlChange = 0xB0, ///< Control Change / Channel Mode
	ProgramChange = 0xC0, ///< Program Change
	AfterTouchChannel = 0xD0, ///< Channel (monophonic) AfterTouch
	PitchBend = 0xE0, ///< Pitch Bend
	SystemExclusive = 0xF0, ///< System Exclusive
	TimeCodeQuarterFrame = 0xF1, ///< System Common - MIDI Time Code Quarter Frame
	SongPosition = 0xF2, ///< System Common - Song Position Pointer
	SongSelect = 0xF3, ///< System Common - Song Select
	TuneRequest = 0xF6, ///< System Common - Tune Request
	Clock = 0xF8, ///< System Real Time - Timing Clock
	Start = 0xFA, ///< System Real Time - Start
	Continue = 0xFB, ///< System Real Time - Continue
	Stop = 0xFC, ///< System Real Time - Stop
	ActiveSensing = 0xFE, ///< System Real Time - Active Sensing
	SystemReset = 0xFF, ///< System Real Time - System Reset
	InvalidType = 0x00 ///< For notifying errors
};

void sendNoteOn(byte NoteNumber, word Velocity, byte Channel);
void sendNoteOff(byte NoteNumber, word Velocity, byte Channel);

void sendProgramChange(byte ProgramNumber, byte Channel);
void sendControlChange(byte ControlNumber, byte ControlValue, byte Channel);
void sendPitchBend(byte Value, byte Channel);
void sendPolyPressure(byte NoteNumber, byte Pressure, byte Channel);
void sendAfterTouch(byte Pressure, byte Channel);

void sendMidiData(void); //Send one midi message per run from buffer array

#endif //MIDI_H
