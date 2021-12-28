class_name GDRtMidiOut
extends Reference

# Helper class for RtMidiOut

var _rtmidiout

enum Api {
	UNSPECIFIED,  # Search for a working compiled API.
	MACOSX_CORE,  # Macintosh OS-X CoreMIDI API.
	LINUX_ALSA,   # The Advanced Linux Sound Architecture API.
	UNIX_JACK,    # The JACK Low-Latency MIDI Server API.
	WINDOWS_MM,   # The Microsoft Multimedia MIDI API.
	RTMIDI_DUMMY, # A compilable but non-functional API.
	WEB_MIDI_API, # W3C Web MIDI API.
#	NUM_APIS      # Number of values in this enum.
}

func _init(api: int = Api.UNSPECIFIED, client_name: String = "GDRtMidi Client"):
	_rtmidiout = load("res://addons/gdrtmidi/gdrtmidi.gdns").new()

	if api == Api.UNSPECIFIED:
		# try to detect platform
		# might be unnecessary since the rtmidi backend automatically falls back to the first available api, if available
		# api priority: LINUX_ALSA > UNIX_JACK(for linux), CORE_MIDI > UNIX_JACK (for osx)
		var platform = OS.get_name()
		match platform:
			"X11":
				api = Api.UNIX_JACK
			"Windows":
				api = Api.WINDOWS_MM
			"OSX":
				api = Api.UNIX_JACK
#			"HTML5":
#				api = Api.WEB_MIDI_API
			_:
				print("Could not detect platform. Interface may not work correctly.")

	_rtmidiout.initialize(api, client_name)

# returns an int representing the currently set api

func get_current_api() -> int:
	return _rtmidiout.getCurrentApi()

# opens a port to the designated port number

func open_port(port_number: int = 0, port_name: String = "GDRtMidi Port"):
	_rtmidiout.openPort(port_number, port_name)

# closes open port, if any

func close_port():
	_rtmidiout.closePort()

# returns true if any port is opened
## only applies to connections made with open_port()

func is_port_open() -> bool:
	return _rtmidiout.isPortOpen()

# creates a virtual output port, with optional name, to allow software connections (OS X, JACK and ALSA only).
## doesnt do anything in other apis

func open_virtual_port(port_name: String):
	_rtmidiout.openVirtualPort(port_name)

# returns the total number of ports available

func get_port_count() -> int:
	return _rtmidiout.getPortCount()

# returns the port name of the specified port

func get_port_name(port_number: int = 0) -> String:
	return _rtmidiout.getPortName(port_number)

# send a midi message crafted using raw bytes

func send_raw(message: PoolByteArray):
	_rtmidiout.sendMessage(message)

# TODO: validate values

func send_control_change(channel: int, cc_number: int, value: int):
	_rtmidiout.sendMessage(PoolByteArray([0xB0 + channel, cc_number, value]))

func send_note_on(channel: int, note_number: int, velocity: int):
	_rtmidiout.sendMessage(PoolByteArray([0x90 + channel, note_number, velocity]))

func send_note_off(channel: int, note_number: int, velocity: int):
	_rtmidiout.sendMessage(PoolByteArray([0x80 + channel, note_number, velocity]))

func send_polyphonic_aftertouch(channel: int, note_number: int, pressure: int):
	_rtmidiout.sendMessage(PoolByteArray([0xA0 + channel, note_number, pressure]))

func send_program_change(channel: int, program_number: int):
	_rtmidiout.sendMessage(PoolByteArray([0xC0 + channel, program_number]))

func send_pitch_bend(channel: int, bend: int):
	var bend_byte_1 = bend >> 8
	var bend_byte_2 = bend << 8
	_rtmidiout.sendMessage(PoolByteArray([0xE0 + channel, bend_byte_1, bend_byte_2]))
