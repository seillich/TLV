#pragma once
#include <vector>
#include "Tlv.h"




class Tlv_chain
{
public:
	Tlv_chain();
	~Tlv_chain();
	unsigned char *mSerializedBuffer;
	int mSerializedBytes = 0;
	bool Parse(const unsigned char *buffer, int buffersize);
	bool PutValue(Tlv *value);
	bool Serialize();
	std::vector<Tlv*> mTlv_vector;
private:
	bool SerializeForNext(int offset, Tlv* next);
};

