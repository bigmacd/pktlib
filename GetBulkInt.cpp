/* GetBULKInt.cpp                                              */
/* A program to use SNMP v2c to fetch the interface names      */
/* from a device                                               */
/*                                                             */
/* GetBULKInt agent community count oid                           */
/*                                                             */
/*  agent = IP address of device (or DNS name)                 */
/*  community = SNMP read/write community name on device       */
/*  count = Number of OIDs to fetch                            */
/*  oid = OID to start fetching                                */
/***************************************************************/
#include <iostream.h>
#include <vbs.h>
#include <UdpClient.h>
#include <stdio.h>
#include <mgmtapi.h>
#include <string.h>
#include <time.h>        /* Needed for reading time */

/********************/
/* Global Variables */
/********************/
char	Agent[100];
char	Community[100];

void ReadInterfaceNamesBulk();
void dumpPacket(Packet* gPacket);

/****************************************/
/* MAIN FUNCTION                        */
/* Returns: 0 on success, < 0 on error. */
/****************************************/
int __cdecl main(int nArgc, char *pArgv[] )
{
    WSAData             w;

	/************************/
	/* Print program header */
	/************************/
	printf("GetBulkInt v1.0 Copyright 2011 www.PathSolutions.com\n");

    /********************/
    /* Check for syntax */
    /********************/
	if (nArgc != 3)
	{
        printf("  A program to use SNMP v2c to fetch the interface names from a device.\n");
        printf("\n  Usage:\t%s ipAddress community\n\n", strupr(pArgv[0]));
        printf("  Arguments:\tipAddress = IP address of switch (or DNS name)\n");
        printf("\t\tcommunity = SNMP read community name on switch\n");
        return 1;
    }

	/******************/
	/* Save variables */
	/******************/
	strcpy(Agent, pArgv[1]);
	strcpy(Community, pArgv[2]);

	/********************/
	/* Start up WinSock */
	/********************/
	printf("Winsock Startup...");
    WSAStartup(0x101, &w);
    printf("successful\n\n");

	{
		ReadInterfaceNamesBulk();
	}

	/********************/
	/* WinSock shutdown */
	/********************/
	printf("\nWinsock cleanup...");
	WSACleanup();
	printf("completed\n");

    return 0;
}




/*****************************/
/* Read Interface Names Bulk */
/*****************************/
void ReadInterfaceNamesBulk()
{
	BOOL                Done=FALSE;
	char				*OIDString;
	OidVarbind*         oid;
	VbPair*             vbp;
	const char			*RawRetP=NULL;
	Packet*             retP;
	DWORD				Retries;
	DWORD				x;						/* Counter */
	Packet				p(GETBULK, 1);			// create an SNMP v2c GETBULK command
	int					vbLen;
	int					vbCounter;
	int					len;

	unsigned int		IntNumber;

	/***************/
	/* Set up OIDs */
	/***************/
	OIDString = (char *)malloc(1000);
	sprintf(OIDString, "1.3.6.1.2.1.2.2.1.2");

	/*************************/
	/* Create GETBULK packet */
	/*************************/
	p.Community(Community);				// set the community string
	p.RequestId(123);					// use device number to track the request
	p.ErrorStatus(0);					// set non-repeaters to zero
	p.ErrorIndex(5);					// set number of max-repititions
	oid = new OidVarbind(OIDString);	// OID for first MAC address
	vbp = new VbPair(oid, NULL);		// Create vbpairs
	p.Add(vbp);							// Add vbpair to the packet
	UdpClient udp(161, Agent);			// Set to port 161 and IP address (or host name)
	udp.Timeout(5);						// Set timeout to PollDeviceTimeout
	udp.ReadBufferSize(65535);			// set buffer size to be large enough to handle response

	/*******************/
	/* Collection loop */
	/*******************/
	IntNumber=0;
	Done = FALSE;
 	while (!Done)
	{
		Retries=0;

		do
		{
		  dumpPacket(&p);
			udp.Send(&p);									// Send the packet
			Retries++;
			RawRetP = udp.Receive();						// Receive the reply
		} while ((!RawRetP) && (Retries < 3));

		/*************************************/
		/* If the packet is valid, save info */
		/*************************************/
		if ( RawRetP )
		{
			// Determine length and parse packet
			len = udp.ReadLength();
			SnmpParser parser((unsigned char*)RawRetP, len);
			retP = parser.packet();

			if (retP != NULL)
			{
				// Packet was parsed successfully
				if ( retP->RequestId() == 123 )
				{
					// RequestID matches
					if ( retP->ErrorStatus() == NOERROR )
					{
						// No SNMP error found, learn how many OIDs were returned
						vbLen = retP->VbListLength();

						// Loop through for each returned OID
						for (vbCounter=1 ; vbCounter <= vbLen ; vbCounter++)
						{
							sprintf(OIDString, "%s", retP->VbOID(vbCounter));
							if (strncmp(OIDString, "1.3.6.1.2.1.2.2.1.2.", 20) == 0)
							{
								// OID is still correct, print the results
								printf("%s: %s\n", retP->VbOID(vbCounter), retP->VbData(vbCounter));
							}
							else
							{
								// OID does not match, we're done
								Done=TRUE;
								break;
							}

						}	// Loop through all OIDs

						// Set up next packet
						delete oid;
						printf("assigning new oid of <%s>\r\n", OIDString);
						oid = new OidVarbind(OIDString);
						p.VbList()->FirstVbPair()->OIDVarbind(oid);
					}
					else
					{
						// ErrorStatus returned an SNMP error
						printf("ERROR: ErrorStatus returned an SNMP error.\n");
						break;
					}
				}
				else
				{
					// RequestID does not match
					printf("ERROR: RequestID does not match.\n");
					break;
				}
			}
			else
			{
				// Packet could not be parsed correctly, some error somewhere
				printf("ERROR: Packet could not be parsed.  Error code: %u\n", udp.ErrorCode());
				break;
			}

			/******************************/
			/* Delete packet if it exists */
			/******************************/
			if ( retP != NULL )
			{
				delete retP;
				retP=NULL;
			}
		}
		else
		{
			// No packet received
			printf("ERROR: No packet returned.  Error code: %u\n", udp.ErrorCode());
			break;
		}
	}

	free(OIDString);

	return;
}

void 
dumpPacket(Packet* gPacket)
{

  printf("Length: %d\r\n", gPacket->TotalLength());
  int version = gPacket->Version();
  printf("Version: ");
  if (version == 0)
    printf("SNMPv1\r\n");
  else
    if (version == 1)
      printf("SNMPv2\r\n");

  printf("Community: %s\r\n", gPacket-> Community());

  int vblen = gPacket->VbListLength();
  for (int x = 1; x <= vblen; x++)
  {
    printf("Varbind Number %d\r\n", x);
    printf("%cOid: %s\r\n", '\t', gPacket->VbOID(x));
    // there is no generic varbid in the pair (oid only)
    //    cout << '\t' << "Type: " << gPacket->VbType(x) << endl;
    //    cout << '\t' << "Data: " << gPacket->VbData(x) << endl;
  }
  printf("\r\n");
}
