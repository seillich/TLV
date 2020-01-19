#pragma once
#include <cstring>
#include <cstdint>

enum types
{
	TLV = 7,
	INT_T = 1,
	CHAR_T = 2 
};

class Tlv
{
public:
	struct tlv_t {
		uint16_t mType;
		uint16_t mLength;
		unsigned char *mValue;
	} tlv;
	Tlv* next = nullptr;
	Tlv();
	Tlv(int type, int value);
	Tlv(int type, char* value);
	Tlv(int type, Tlv& value);
	Tlv(int type, unsigned char *value, int length);
	~Tlv();

private:
	void Initialize(const void *value, uint16_t length);
	//uint16_t intToUint16(int value);
};

