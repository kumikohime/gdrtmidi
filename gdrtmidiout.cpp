#include "gdrtmidiout.h"

using namespace godot;

void GDRtMidiOut::_register_methods()
{
    register_method("_process", &GDRtMidiOut::_process);
    register_method("initialize", &GDRtMidiOut::initialize);
    register_method("getCurrentApi", &GDRtMidiOut::getCurrentApi);
    register_method("openPort", &GDRtMidiOut::openPort);
    register_method("closePort", &GDRtMidiOut::closePort);
    register_method("isPortOpen", &GDRtMidiOut::isPortOpen);
    register_method("openVirtualPort", &GDRtMidiOut::openVirtualPort);
    register_method("getPortCount", &GDRtMidiOut::getPortCount);
    register_method("getPortName", &GDRtMidiOut::getPortName);
    register_method("sendMessage", &GDRtMidiOut::sendMessage);
    register_method("isPortOpen", &GDRtMidiOut::isPortOpen);
}

// GDRtMidiOut ::GDRtMidiOut()
// {
//     auto api_ = static_cast<RtMidi::Api>(api);
//     std::string c_name = std::string(clientName.alloc_c_string());
//     this->midiout = new RtMidiOut(api_, c_name);
//     Godot::print(clientName);
//     Godot::print(Variant(api));
// }

GDRtMidiOut::GDRtMidiOut()
{
}

GDRtMidiOut::~GDRtMidiOut()
{
    // add your cleanup here
    delete midiout;
}

void GDRtMidiOut::_init()
{
    this->midiout = new RtMidiOut;
}

void GDRtMidiOut::_process(float delta)
{
}

/*********** API ***********/

//TODO: Implement enums to remove need for casts
void GDRtMidiOut::initialize(int api, String clientName)
{
    auto c_name = std::string(clientName.alloc_c_string());
    auto api_ = static_cast<RtMidi::Api>(RtMidi::UNIX_JACK);
    // if (midiout == NULL)
    // {
    //     RtMidiOut *tmp = new RtMidiOut(api_, c_name);
    //     delete this->midiout;
    //     this->midiout = tmp;
    // }
    // else
    this->midiout = new RtMidiOut(api_, c_name);

    Godot::print(Variant(api));
    Godot::print(clientName);
}

RtMidi::Api GDRtMidiOut::getCurrentApi(void) throw()
{
    RtMidi::Api api = this->midiout->getCurrentApi();
    return api;
}

void GDRtMidiOut::openPort(unsigned int portNumber, String portName)
{
    try
    {
        unsigned int u_pnum = (unsigned int)portNumber;
        std::string p_name = std::string(portName.alloc_c_string());
        this->midiout->openPort(portNumber, p_name);
        // Godot::print(portName);
    }
    catch (RtMidiError e)
    {
        // Godot::print("error opening port");
        // Godot::print(e.getMessage().c_str());
        std::cout << (e.getMessage());
    }
}

void GDRtMidiOut::closePort(void)
{
    Godot::print("attempting to close port");
    this->midiout->closePort();
}

bool GDRtMidiOut::isPortOpen() const
{
    return this->midiout->isPortOpen();
}

void GDRtMidiOut::openVirtualPort(const String portName)
{
    auto p_name = std::string(portName.alloc_c_string());
    this->midiout->openVirtualPort(p_name);
}

unsigned int GDRtMidiOut::getPortCount(void)
{
    return this->midiout->getPortCount();
}

godot::String GDRtMidiOut::getPortName(unsigned int portNumber)
{
    std::string p_name = this->midiout->getPortName(portNumber);
    auto p_name_ = godot::String(p_name.c_str());
    return p_name_;
}

void GDRtMidiOut::sendMessage(PoolByteArray message)
{
    if (message.size() <= 0)
        return;
    try
    {
        std::vector<unsigned char> c_msg;
        PoolByteArray::Read read_ptr = message.read();
        for (int i = 0; i < message.size(); i++)
        {
            c_msg.push_back(read_ptr[i]);
        }
        this->midiout->sendMessage(&c_msg);
    }
    catch (RtMidiError e)
    {
        std::cout << e.getMessage();
    }
}

void GDRtMidiOut::setErrorCallback(RtMidiErrorCallback errorCallback, void *userData)
{
    this->midiout->setErrorCallback(errorCallback, userData);
}

/*********** API ***********/
