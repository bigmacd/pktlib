.SUFFIXES:
.SUFFIXES : .cpp .o

CC= gcc 
#CFLAGS = -g -lnsl
INCLUDES = -I. 

CFILES= CounterVarbind.cpp Counter64Varbind.cpp GaugeVarbind.cpp GenericPacket.cpp IntVarbind.cpp IpAddrVarbind.cpp OidVarbind.cpp OpaqueVarbind.cpp Packet.cpp ScalarVarbind.cpp Scalar64Varbind.cpp SnmpException.cpp SnmpParser.cpp StringVarbind.cpp TimeTickVarbind.cpp V1GetNextPdu.cpp V1GetPdu.cpp V1Pdu.cpp V1ResponsePdu.cpp V1SetPdu.cpp V1TrapPdu.cpp V2TrapPdu.cpp V2GetBulkPdu.cpp InformPdu.cpp Varbind.cpp VarbindList.cpp VbPair.cpp V2Notification.cpp Udp.cpp UdpClient.cpp UdpServer.cpp Thread.cpp Poller.cpp

OBJECTS = ${CFILES:.cpp=.o}

LDSHARED = g++ $(CFLAGS) -shared -o

LDSTATIC = ar rv

lib: $(OBJECTS)
	$(LDSHARED) libPktLib.so $(OBJECTS)
	$(LDSTATIC) libPktLib.a $(OBJECTS)

all:	$(OBJECTS) $(lib)

% : %.cpp
	$(CC) $(CFLAGS) $< -o $*

%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -D_USE_PACKETLIB -D_LINUX -c $< -o $*.o

.c.i :
	$(CC) $(CFLAGS) $(INCLUDES) -E -C $< > $*.i

.c.s :
	$(CC) $(CFLAGS) $(INCLUDES) -S $< > $*.s

%.mk:	%.c
	$(CC) $(INCLUDES) -M $< >$@
	${edit_depend}


