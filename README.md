# Introduction
GDRtMidi is a wrapper for the popular C++ midi library RtMidi. 

__Currently only the Midi Out interface is supported.__

# Installation

1. Download from releases the version appropriate for your target platform(s). Prebuilt binaries for Windows and Linux are currently available.

2. Copy the addons folder in your godot project.

# Building

1. Clone the repo.

2. Compile godot-cpp. ``cd godot-cpp && scons platform=windows -j12 && cd ..`` then build the gdnative libs ``scons platform=windows/linux/osx``
Note: you might need to build rtmidi yourself if compiling for windows/osx
``cd rtmidi && ./autogen.sh && make``

3. Create a folder named ``gdrtmidi``. Copy the contents of ``gd`` into this folder.
Copy the built library from step 2 somewhere inside this folder. By default it should be in
``lib/x11`` for linux or ``lib/win`` for windows. If you choose to choose an arbitrary location, update the ``gdrtmidi.gdnlib`` accordingly.

4. Copy the ``gdrtmidi`` folder under the ``addons`` directory in your godot project.

# Usage

1. Docs are currently under construction. For the time being refer to the RtMidiOut Class Interface

https://www.music.mcgill.ca/~gary/rtmidi/classRtMidiOut.html