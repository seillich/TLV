#include "Tlv.h"



Tlv::Tlv()
{
}

Tlv::Tlv(int type, int value)
{
	tlv.mType = (uint16_t)type;
	Initialize(&value, sizeof(int));
}

Tlv::Tlv(int type, char * value)
{
	tlv.mType = (uint16_t)type;
	Initialize(value, uint16_t(strlen(value) + 1));
}

Tlv::Tlv(int type, Tlv & value)
{
	tlv.mType = (uint16_t)type;
	tlv.mLength = sizeof(uint16_t) * 2 + value.tlv.mLength;
	next = &value;
}

Tlv::Tlv(int type, unsigned char * value, int length)
{
	tlv.mType = (uint16_t)type;
	Initialize(value, length);
}


Tlv::~Tlv()
{
	delete[] tlv.mValue;
}

void Tlv::Initialize(const void * value, uint16_t length)
{
	tlv.mLength = length;
	tlv.mValue = new unsigned char[length];
	memcpy(tlv.mValue, value, length);
}
