

// classes
#define UNIVERSAL           0x00
#define APPLICATION         0x40
#define CONTEXTSPECIFIC     0x80
#define PRIVATE             0xc0

// forms
#define PRIMITIVE           0x00
#define CONSTRUCTED         0x20

// tags
#define INTEGERTAG          (UNIVERSAL | PRIMITIVE   | 0x02)
#define STRINGTAG           (UNIVERSAL | PRIMITIVE   | 0x04)
#define NULLTAG             (UNIVERSAL | PRIMITIVE   | 0x05)
#define OID                 (UNIVERSAL | PRIMITIVE   | 0x06)
#define SEQUENCE            (UNIVERSAL | CONSTRUCTED | 0x10)
#define SETOF               (UNIVERSAL | CONSTRUCTED | 0x11)

#define IPADDRESS           (APPLICATION | PRIMITIVE | 0x00)
#define PHYSADDRESS  IPADDRESS
#define NETWORKADDRESS IPADDRESS
#define COUNTER32           (APPLICATION | PRIMITIVE | 0x01)
#define GAUGE32             (APPLICATION | PRIMITIVE | 0x02)
#define TIMETICK            (APPLICATION | PRIMITIVE | 0x03)
#define SNMPOPAQUE          (APPLICATION | PRIMITIVE | 0x04)
#define NSAP                (APPLICATION | PRIMITIVE | 0x05)
#define COUNTER64           (APPLICATION | PRIMITIVE | 0x06)
#define UINTEGER32          (APPLICATION | PRIMITIVE | 0x07)

// commands
#define V1GETCOMMAND        (CONTEXTSPECIFIC | CONSTRUCTED | 0x00)
#define V1GETNEXTCOMMAND    (CONTEXTSPECIFIC | CONSTRUCTED | 0x01)
#define V1RESPONSE          (CONTEXTSPECIFIC | CONSTRUCTED | 0x02)
#define V1SETCOMMAND        (CONTEXTSPECIFIC | CONSTRUCTED | 0x03)
#define V1TRAP              (CONTEXTSPECIFIC | CONSTRUCTED | 0x04)

// V2 specific
#define GETBULK             (CONTEXTSPECIFIC | CONSTRUCTED | 0x05)
#define INFORMPDU           (CONTEXTSPECIFIC | CONSTRUCTED  | 0x06)
#define V2TRAP              (CONTEXTSPECIFIC | CONSTRUCTED  | 0x07)
#define REPORT              (CONTEXTSPECIFIC | CONSTRUCTED  | 0x08)

// errors
#define NOSUCHOBJECT        (CONTEXTSPECIFIC | PRIMITIVE  | 0x00)
#define NOSUCHINSTANCE      (CONTEXTSPECIFIC | PRIMITIVE  | 0x01)
#define LASTINVIEW          (CONTEXTSPECIFIC | PRIMITIVE  | 0x02)

#define NOERROR             0
#define TOOBIG              1
#define NOSUCHNAME          2
#define BADVALUE            3
#define READONLY            4
#define GENERR              5
#define NOACCESS            6
#define WRONGTYPE           7
#define WRONGLENGTH         8
#define WRONGENCODING       9
#define WRONGVALUE          10
#define NOCREATION          11
#define INCONSISTENTVALUE   12
#define RESOURCEUNAVAILABLE 13
#define COMMITFAILED        14
#define UNDOFAILED          15
#define AUTHORIZATIONERROR  16
#define NOTWRITABLE         17
#define INCONSISTENTNAME    18

// trap types
#define COLDSTART           0
#define WARMSTART           1
#define LINKDOWN            2
#define LINKUP              3
#define AUTHFAILURE         4
#define EGPNEIGHBORLOSS     5
#define ENTERPRISESPECIFIC  6

#define VERSIONV1           0  

#define TRAPOIDBASE               "1.3.6.1.6.3.1.1.5" 
#define COLDSTARTOID              ".1"                
#define WARMSTARTOID              ".2"                
#define LINKDOWNOID               ".3"                
#define LINKUPOID                 ".4"                
#define AUTHENTICATIONFAILUREOID  ".5"                
#define EGPNEIGHBORLOSSOID        ".6"                


