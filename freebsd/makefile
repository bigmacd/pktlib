#CFLAGS = -L/opt/FSFlibg++/lib 
CPPFLAGS= -D_USE_PACKETLIB -D_FREEBSD
CC=gcc

# The command to create a shared library.  This command will be used
# in this manner : $(LDSHARED) <libname> <objects> so make sure that
# whatever argument is needed to set the resulting library name comes
# last and that the command takes a series of objects as the final
# argument.
LDSHARED = $(CC) $(CFLAGS) -shared -o

LDSTATIC = ar rv

# Command to build the dependencies file.  This command must be structured
# in a manner to take a series of source files and write the data to
# standard output.
MKDEPEND = g++ -M $(CPPFLAGS)

SRCS = CounterVarbind.cpp \
Counter64Varbind.cpp \
GaugeVarbind.cpp \
GenericPacket.cpp \
IntVarbind.cpp \
IpAddrVarbind.cpp \
OidVarbind.cpp \
OpaqueVarbind.cpp \
Packet.cpp \
ScalarVarbind.cpp \
Scalar64Varbind.cpp \
SnmpException.cpp \
SnmpParser.cpp \
StringVarbind.cpp \
TimeTickVarbind.cpp \
V1GetNextPdu.cpp \
V1GetPdu.cpp \
V1Pdu.cpp \
V1ResponsePdu.cpp \
V1SetPdu.cpp \
V1TrapPdu.cpp \
V2TrapPdu.cpp \
Varbind.cpp \
VarbindList.cpp \
VbPair.cpp \
Udp.cpp \
UdpClient.cpp \
UdpServer.cpp \
InformPdu.cpp \
V2Notification.cpp \
Thread.cpp \
Poller.cpp


OBJS = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .o
.cpp.o: 
	$(CC) $(CPPFLAGS) -c $<

lib: objs
	$(LDSTATIC) libPktLib.a $(OBJS)
	$(LDSHARED) libPktLib.so $(OBJS)

objs: $(OBJS)

clean:
	$(RM) *.o *~ *.so *.a

.depend : $(SRCS)
	$(MKDEPEND) $(SRCS) > .depend
include .depend


