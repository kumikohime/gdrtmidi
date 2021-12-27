# Introduction
GDRtMidi is a wrapper for the popular C++ midi library RtMidi. 

__Currently only the Midi Out interface is supported.__

# Installation

1. Download from releases the version appropriate for your target platform(s). As of the time of this writing only linux is supported, but  support for windows and osx is planned.

2. Copy the folder somewhere in your godot project.

# Compiling

1. Clone the repo.

2. Use scons to build ``scons platform=windows/linux/osx``
Note: you might need to build rtmidi yourself if compiling for windows/osx
``cd rtmidi && ./autogen.sh && make``
In a future update this will be addressed.

# Usage

1. Refer to the RtMidiOut Class Interface

https://www.music.mcgill.ca/~gary/rtmidi/classRtMidiOut.html