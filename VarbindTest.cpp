// g++ VarbindTest.cpp -o wrongOrder -L/home/mcooley/git/pktlib -l PktLib -lpthread

#include "vbs.h" 

#include <iostream>
using namespace std;
 
int  main(int argc, char** argv); 

int main(int argc, char** argv) 
{ 
  unsigned char mypdu[2000];
  unsigned char* pdu = mypdu;
  VarbindList* newVbl = new VarbindList();  // make a new varbindlist
  // retrieve the values one by one
  OidVarbind* oid = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv = new IntVarbind(55);
  VbPair* newVbp = new VbPair(); // make a new varbind pair

  oid->Build(pdu);
  iv->Build(pdu);
}




