# A quick intro to libfluid_base {#intro}
**libfluid_base** (namespace fluid_base) defines a client-server architecture, 
in which a controller is a server and a switch is a client. It provides a base 
class upon which you can build your controller (by inheritance): 
fluid_base::OFServer. 

## Build and install
**libfluid_base** has been tested on Ubuntu 12.04 and Fedora 19. It should run 
on other flavors of Linux. MacOS, Windows and BSD variations are currently not 
supported, but they should run with some simple changes (we plan to support 
them oficially in the future).

**libfluid_base** requires [libevent](http://libevent.org/) 2.0 and 
(optionally) OpenSSL 1.0.

### Ubuntu 12.04
Install the dependencies:
~~~{.sh}
$ sudo apt-get install autoconf libtool build-essential pkg-config
$ sudo apt-get install libevent-dev libssl-dev
~~~

Build:
~~~{.sh}
$ ./configure
$ make
$ sudo make install
~~~
> If you want to compile without TLS support, pass the `--disable-tls` flag to 
> `configure`. This will remove the dependency on OpenSSL.

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
$ sudo yum install libevent-devel openssl-devel
~~~

Build:
~~~{.sh}
$ ./configure
$ make
$ sudo make install
~~~
> If you want to compile without TLS support, pass the `--disable-tls` flag to 
> `configure`. This will remove the dependency on OpenSSL.

Configure your system to find libraries in `/usr/local/lib`:
~~~{.sh}
$ sudo sh -c "echo /usr/local/lib > /etc/ld.so.conf.d/libfluid.conf"
$ sudo ldconfig
~~~

## Usage
To use **libfluid_base**, you will need to include:
~~~{.cc}
#include <fluid/OFServer.hh>
~~~

Link with your code with `-lfluid_base`.

## Coding with libfluid_base
> For more examples on how to use the library, see the examples included in 
> the **libfluid** bundle. 

fluid_base::OFServer takes a port number, the number of workers to use, 
optional TLS support and few configuration parameters 
(fluid_base::OFServerSettings) that define how it should deal with some basic 
OpenFlow features. It also expects you to implement two callback method for 
dealing with connection events and messages.

The number of workers will define how many of them will be created when the 
server starts. Every worker will run in its own thread (which are automatically 
managed for you), and each will handle a certain number of connections, 
distributed in a round-robin fashion. Typically, these connections will be 
presented to you as fluid_base::OFConnection objects in the callbacks.

Finally, these are the callbacks you should implement:

* fluid_base::OFServer::message_callback: called when a new message arrives
* fluid_base::OFServer::connection_callback: called when a connection event 
happens (e.g.: establishment or disconnection).

These methods can be called from any of the threads that handle connections, so 
they must be thread-safe and return as quickly as possible (so the other 
connections don't starve waiting for a callback to complete). You can quickly 
build up a representation of the events and put them in an asynchronous queue 
for use by other parts of your controller or application, for instance. The 
examples provided with **libfluid** don't do this for the sake of simplicity.

The image below illustrates how your implementation can use **libfluid_base**.

![Using libfluid](img/libfluid.png)

This image is a rough representation of the architecture and workflow; if you 
see something slightly different or better defined in code, the code is right 
:)

For more advanced use cases, take a look at fluid_base::BaseOFServer and 
fluid_base::BaseOFConnection. They provide the basic functionalities upon which 
fluid_base::OFServer and fluid_base::OFConnection are built. However, you 
shouldn't need to deal with them most of the time.
