#ifndef GDRTMIDIOUT_H
#define GDRTMIDIOUT_H

#include <Godot.hpp>
#include <Node.hpp>
#include <RtMidi.h>

namespace godot
{
    class GDRtMidiOut : public Node
    {
        GODOT_CLASS(GDRtMidiOut, Node)

    private:
        RtMidiOut *midiout = 0;

    public:
        static void
        _register_methods();

        GDRtMidiOut();
        ~GDRtMidiOut();

        void _init();
        void _process(float delta);

        /*********** API ***********/
        //! Needed to work around not being able to pass args to NativeScript ctors. Should be called after instancing with .new() in GDScript
        void initialize(int api = 0, String clientName = "RtMidi Output Client");

        //! Returns the MIDI API specifier for the current instance of RtMidiOut.
        RtMidi::Api getCurrentApi(void) throw();

        void openPort(unsigned int portNumber = 0, String portName = "RtMidi Output");

        //! Close an open MIDI connection (if one exists).
        void closePort(void);

        //! Returns true if a port is open and false if not.
        /*!
        Note that this only applies to connections made with the openPort()
        function, not to virtual ports.
        */
        bool isPortOpen() const;

        //! Create a virtual output port, with optional name, to allow software connections (OS X, JACK and ALSA only).
        /*!
        This function creates a virtual MIDI output port to which other
        software applications can connect.  This type of functionality
        is currently only supported by the Macintosh OS-X, Linux ALSA
        and JACK APIs (the function does nothing with the other APIs).
        An exception is thrown if an error occurs while attempting to
        create the virtual port.
        */
        void openVirtualPort(const String portName);

        //! Return the number of available MIDI output ports.
        unsigned int getPortCount(void);

        //! Return a string identifier for the specified MIDI port type and number.
        /*!
        \return The name of the port with the given Id is returned.
        \retval An empty string is returned if an invalid port specifier
                is provided. User code should assume a UTF-8 encoding.
        */
        godot::String getPortName(unsigned int portNumber = 0);

        //! Immediately send a single message out an open MIDI output port.
        /*!
        An exception is thrown if an error occurs during output or an
        output connection was not previously established.
        */
        void sendMessage(PoolByteArray message);

        //! Set an error callback function to be invoked when an error has occured.
        /*!
        The callback function will be called whenever an error has occured. It is best
        to set the error callback function before opening a port.
        */
        virtual void setErrorCallback(RtMidiErrorCallback errorCallback = NULL, void *userData = 0);

        /*********** API ***********/
    };

}

#endif