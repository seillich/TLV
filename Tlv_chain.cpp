#include "Tlv_chain.h"

Tlv_chain::Tlv_chain()
{
}


Tlv_chain::~Tlv_chain()
{
	if (mSerializedBuffer != NULL) {
		delete[] mSerializedBuffer;
		mSerializedBuffer = NULL;
	}

}

bool Tlv_chain::Parse(const unsigned char *buffer, int buffersize)
{
	if (buffer == NULL) {
		return false;
	}

	unsigned char *cached = new unsigned char[buffersize];
	memcpy(cached, buffer, buffersize);

	int offset = 0;
	while (offset < buffersize) {
		uint16_t type = (*(uint16_t *)(cached + offset));
		offset += sizeof(uint16_t);
		uint16_t length = (*(uint16_t *)(cached + offset));
		offset += sizeof(uint16_t);
		PutValue(new Tlv(type, cached + offset, length));
		if (type == TLV) {
			Parse(cached + offset, length);
		}
		offset += length;
	}

	mSerializedBuffer = cached;
	mSerializedBytes = buffersize;

	return true;
}

bool Tlv_chain::PutValue(Tlv * value)
{
	mTlv_vector.push_back(value);
	mSerializedBytes += (sizeof(uint16_t) * 2 + value->tlv.mLength);
	return true;
}

bool Tlv_chain::Serialize()
{
	int offset = 0;
	mSerializedBuffer = new unsigned char[mSerializedBytes];
	for (auto tlv_: mTlv_vector) {
		uint16_t type = (tlv_->tlv.mType);
		memcpy(mSerializedBuffer + offset, &type, sizeof(uint16_t));
		offset += sizeof(uint16_t);
		uint16_t length = (tlv_->tlv.mLength);
		memcpy(mSerializedBuffer + offset, &length, sizeof(uint16_t));
		offset += sizeof(uint16_t);
		if (tlv_->next != nullptr) SerializeForNext(offset, tlv_->next);
		else memcpy(mSerializedBuffer + offset, tlv_->tlv.mValue, length);
		offset += length;
	}

	return true;
}


bool Tlv_chain::SerializeForNext(int offset, Tlv* next) {
	uint16_t type = (next->tlv.mType);
	memcpy(mSerializedBuffer + offset, &type, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	uint16_t length = (next->tlv.mLength);
	memcpy(mSerializedBuffer + offset, &length, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	if (next->next != nullptr) SerializeForNext(offset, next->next);
	else memcpy(mSerializedBuffer + offset, next->tlv.mValue, length);
	offset += length;

	return true;
}