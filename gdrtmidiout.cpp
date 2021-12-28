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
    // register_method("setErrorCallback", &GDRtMidiOut::setErrorCallback);
}

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
}

void GDRtMidiOut::_process(float delta)
{
}

/*********** API ***********/

//TODO: Implement enums to remove need for casts
void GDRtMidiOut::initialize(int api, String clientName)
{
    auto c_name = std::string(clientName.alloc_c_string());
    auto api_ = static_cast<RtMidi::Api>(api);
    if (midiout == NULL)
    {
        RtMidiOut *tmp = new RtMidiOut(api_, c_name);
        delete this->midiout;
        this->midiout = tmp;
    }
    else
        this->midiout = new RtMidiOut(api_, c_name);
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
    }
    catch (RtMidiError e)
    {
        std::cout << (e.getMessage());
    }
}

void GDRtMidiOut::closePort(void)
{
    this->midiout->closePort();
}

bool GDRtMidiOut::isPortOpen() const
{
    return this->midiout->isPortOpen();
}

void GDRtMidiOut::openVirtualPort(const String portName)
{
    try
    {
        auto p_name = std::string(portName.alloc_c_string());
        this->midiout->openVirtualPort(p_name);
    }
    catch (RtMidiError e)
    {
        std::cout << (e.getMessage());
    }
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

// void GDRtMidiOut::setErrorCallback(RtMidiErrorCallback errorCallback, void *userData)
// {
//     this->midiout->setErrorCallback(errorCallback, userData);
// }

/*********** API ***********/
