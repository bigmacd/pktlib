// g++ VarbindTest.cpp -o vbtest -L/home/mcooley/git/pktlib -l PktLib -lpthread

#include "vbs.h" 

#include <iostream>

using namespace std;
#include <assert.h>
 
int  main(int argc, char** argv); 

int main(int argc, char** argv) 
{ 
  unsigned char mypdu[2000];
  VarbindList* newVbl = new VarbindList();  // make a new varbindlist

  VbPair* newVbp = new VbPair(); // make a new varbind pair
  VbPair* newVbp2 = new VbPair(); // make a new varbind pair
  VbPair* newVbp3 = new VbPair(); // make a new varbind pair
  VbPair* newVbp4 = new VbPair(); // make a new varbind pair
  VbPair* newVbp5 = new VbPair(); // make a new varbind pair
  VbPair* newVbp6 = new VbPair(); // make a new varbind pair
  VbPair* newVbp7 = new VbPair(); // make a new varbind pair
  VbPair* newVbp8 = new VbPair(); // make a new varbind pair
  VbPair* newVbp9 = new VbPair(); // make a new varbind pair
  VbPair* newVbp10 = new VbPair(); // make a new varbind pair

  // retrieve the values one by one
  OidVarbind* oid1 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv1 = new IntVarbind(55);
  OidVarbind* oid2 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv2 = new IntVarbind(55);
  OidVarbind* oid3 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv3 = new IntVarbind(55);
  OidVarbind* oid4 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv4 = new IntVarbind(55);
  OidVarbind* oid5 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv5 = new IntVarbind(55);
  OidVarbind* oid6 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv6 = new IntVarbind(55);
  OidVarbind* oid7 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv7 = new IntVarbind(55);
  OidVarbind* oid8 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv8 = new IntVarbind(55);
  OidVarbind* oid9 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv9 = new IntVarbind(55);
  OidVarbind* oid10 = new OidVarbind("1.3.6.1.4.1.2859.1.2.3.0");
  IntVarbind* iv10 = new IntVarbind(55);

  newVbp->OIDVarbind(oid1);
  newVbp->VarBind(iv1);
  newVbp2->OIDVarbind(oid2);
  newVbp2->VarBind(iv2);
  newVbp3->OIDVarbind(oid3);
  newVbp3->VarBind(iv3);
  newVbp4->OIDVarbind(oid4);
  newVbp4->VarBind(iv4);
  newVbp5->OIDVarbind(oid5);
  newVbp5->VarBind(iv5);
  newVbp6->OIDVarbind(oid6);
  newVbp6->VarBind(iv6);
  newVbp7->OIDVarbind(oid7);
  newVbp7->VarBind(iv7);
  newVbp8->OIDVarbind(oid8);
  newVbp8->VarBind(iv8);
  newVbp9->OIDVarbind(oid9);
  newVbp9->VarBind(iv9);
  newVbp10->OIDVarbind(oid10);
  newVbp10->VarBind(iv10);

  memset(mypdu, 0, 2000);
  unsigned char* pdu = mypdu;
  oid1->Build(pdu);
  for (int x = 0; x < oid1->Length(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;
  cout << "Oid Length should be 13, actual is " << oid1->Length() << endl;

  memset(mypdu, 0, 2000);
  pdu = mypdu;
  iv1->Build(pdu);
  for (int x = 0; x < iv1->Length(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;
  cout << "Int Length should be 3, actual is " << iv1->Length() << endl;

  memset(mypdu, 0, 2000);
  pdu = mypdu;
  newVbp->Build(pdu);
  for (int x = 0; x < newVbp->Length(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;
  cout << "VbPair Length is " << newVbp->Length() << ", should be 18" << endl;

  assert((oid1->Length() + iv1->Length() + 2) == newVbp->Length());

  memset(mypdu, 0, 2000);
  pdu = mypdu;

  newVbl->Add(newVbp);
  cout << "VarbindList with one varbind pair length: " << newVbl->Length() << endl;

  memset(mypdu, 0, 2000);
  pdu = mypdu;
  newVbl->Build(pdu);
  for (int x = 0; x < newVbl->Length(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;


  newVbl->Add(newVbp2);
  newVbl->Add(newVbp3);
  newVbl->Add(newVbp4);
  newVbl->Add(newVbp5);
  newVbl->Add(newVbp6);
  newVbl->Add(newVbp7);
  newVbl->Add(newVbp8);
  newVbl->Add(newVbp9);
  newVbl->Add(newVbp10);
  const int numberOfVarbinds = 10;
  cout << "VarbindList with " << numberOfVarbinds << " varbind pairs length: " << newVbl->Length() << endl;

  //////////////////////////////////////////////////////////////
  VbPair* tvbp = newVbl->FirstVbPair();
  int lengthLength = 2;
  int currentLength = 0;
  while (tvbp != NULL) {
    memset(mypdu, 0, 2000);
    pdu = mypdu;

    OidVarbind* oidvb = tvbp->OIDVarbind();
    Varbind* vvb = tvbp->VarBind();

    currentLength += oidvb->Length();
    currentLength += vvb->Length();
    cout << "In varbindlist loop: oid length is " << oidvb->Length() << " and vb length is " << vvb->Length() << endl;

    tvbp = tvbp->Next;
  }

  if (currentLength > 127)
    lengthLength = 3;

  ////////////////////////////////
  memset(mypdu, 0, 2000);
  pdu = mypdu;
  newVbl->Build(pdu);
  for (int x = 0; x < newVbl->Length(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;

  cout << "expecting: " << ((  (oid1->Length() + iv1->Length() + 2) * numberOfVarbinds) + lengthLength) << endl;
  cout << "got: " << newVbl->Length() << endl;

  assert(((  (oid1->Length() + iv1->Length() + 2) * numberOfVarbinds) + lengthLength)  == newVbl->Length());

  cout << endl;


  Packet p(V1RESPONSE, 1);
  p.VbList(newVbl);

  ////////////////////////////////
  memset(mypdu, 0, 2000);
  pdu = mypdu;
  p.Build(pdu);
  for (int x = 0; x < p.TotalLength(); x++) {
    printf("%02x ", mypdu[x]);
  }
  cout << endl;

}
// length is 208 + 1
/*
30 81 ce
02 01 01
04 06 70 75 62 6c 69 63
a2
81 c0
02 01 0f
02 01 00
02 01 00
30 81 b4
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00 02 01 37
30 10 06 0b 2b 06 01 04 01 96 2b 01 02 03 00
*/