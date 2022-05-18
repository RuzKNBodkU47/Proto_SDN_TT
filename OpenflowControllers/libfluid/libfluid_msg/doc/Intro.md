# A quick intro to libfluid_msg
**libfluid_msg** is a library to create, serialize and deserialize OpenFlow 1.0 
and OpenFlow 1.3 messages.

## Build and install
**libfluid_msg** has been tested on Ubuntu 12.04 and Fedora 19. It should run 
on other flavors of Linux. MacOS, Windows and BSD variations are currently not 
supported, but they should run with some simple changes (we plan to support 
them oficially in the future).

### Ubuntu 12.04
Install the dependencies:
~~~{.sh}
$ sudo apt-get install autoconf libtool build-essential pkg-config
~~~

Build:
~~~{.sh}
$ ./configure
$ make
$ sudo make install
~~~

Configure your system to find libraries in `/usr/local/lib`:
~~~{.sh}
$ sudo sh -c "echo /usr/local/lib > /etc/ld.so.conf.d/libfluid.conf"
$ sudo ldconfig
~~~
> You can skip this last step by running `./configure --prefix=/usr` in the 
> build.

### Fedora 19
Install the dependencies:
~~~{.sh}
$ sudo yum install autoconf automake gcc-g++ libtool
~~~

Build:
~~~{.sh}
$ ./configure
$ make
$ sudo make install
~~~

Configure your system to find libraries in `/usr/local/lib`:
~~~{.sh}
$ sudo sh -c "echo /usr/local/lib > /etc/ld.so.conf.d/libfluid.conf"
$ sudo ldconfig
~~~

## Usage
To use OpenFlow 1.0 messages, you will need to include:
~~~{.cc}
#include <fluid/of10msg.h>
~~~

And for OpenFlow 1.3:
~~~{.cc}
#include <fluid/of13msg.h>
~~~

Link with your code with `-lfluid_msg`.

## Coding with libfluid_msg

**libfluid_msg** provides classes for all OpenFlow 1.0 and 1.3 message types 
along with classes that represent common structures. These classes have two 
methods to serialize and deserialize OpenFlow messages.

Here's how to pack a Hello message:
~~~{.cc}
#include <fluid/of10msg.h>   
using namespace fluid_msg;

[...]

of10::Hello h();
h.xid(42);
uint8_t *buff = h.pack();

// Just an illustration of a method to send the message
// send(buff);
// delete [] buff;
~~~
The message is serialized into a binary format, ready to be sent
through the wire. The user is responsible for the memory management 
of the generated packed message. 

And then unpack another:
~~~{.cc}
#include <fluid/of10msg.h>   

using namespace fluid_msg;

[...]

// Message arrived from the OpenFlow Channel
of10::Hello h;

// Unpack and check for error
of_error err = h.unpack(buff);
~~~
The unpack method returns an OpenFlow error message. Most of the
error handling is related to the length of the messages, but some
messages, like fluid_msg::of13::FlowMod, have other types of error
checking.
To retrieve the error type and code use the following functions:

~~~{.cc}
uint16_t err_type = of_error_type(err);
uint16_t err_code = of_error_code(err);
~~~

Here is an example of how to create a message composed by other
OpenFlow elements.
To create a fluid_msg::of10::FlowMod message:
~~~{.cc}
#include <fluid/of10msg.h>

using namespace fluid_msg;

[...]

of10::FlowMod fm();

// Creates Output Action with in_port=1 and send_len=1024
of10::OutputAction oa(1, 1024);

// Add Output Action to Flow mod
fm.add_action(oa);

// Creates Set Vlan ID action with vlan id=12 and add to Flow Mod 
fm.add_action(new of10::SetVLANVIDAction(12));
~~~
The example creates a fluid_msg::of10::FlowMod message with all
fields wildcarded and with two actions. Notice that we are passing
static and dynamic objects to the fluid_msg::of10::FlowMod class.
The class takes ownership of the objects, deleting objects dinamically allocated.
So the user should not delete that memory.

To create a fluid_msg::of13::FlowMod, with OXM Fields of13::InPort and of13::EthType;
and with and  of13::ApplyActions instruction containing the action of13::OutputAction:

~~~{.cc}
#include <fluid/of13msg.h>

using namespace fluid_msg;

[...]

of13::FlowMod fm();

// Creates in_port oxm_field with value=1
of13::InPort *port = new InPort(1);

// Add in_port to Flow Mod
fm.add_oxm_field(port);

// Create eth_type oxm_field with value=0x0800 and add to Flow Mod
fm.add_oxm_field(new of13::EthType(0x0800));

// Creates Output Action with in_port=1 and send_len=1024
of13::OutputAction act(out_port, 1024);

// Creates ApplyAction and add action
of13::ApplyActions inst; 
inst.add_action(act);
//Add the ApplyAction to FlowMod
fm.add_instruction(inst);
~~~

