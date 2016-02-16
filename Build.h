#ifndef __BUILD_H__
#define __BUILD_H__

class Builder
{
  public:

    Builder() {};
    virtual ~Builder() {};


    virtual void     Build(unsigned char*& pdu) = 0;

};
#endif
