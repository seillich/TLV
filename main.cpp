#include "Tlv.h"
#include <iostream>
#include "Tlv_chain.h"

int main() {
/*Создаем TLV, есть три типа TLV, int, char в TLV мы можем помещать любой тип из предложенных
Дальше мы добавляем(chain.PutValue) эти значения в TLV_Chain и кодируем(chain.Serialize).
После чего мы декодируем эти данные (decoder.Parse), и через цикл воспроизводим эти данные.*/
	char q[] = "hell";
	Tlv t = Tlv(CHAR_T, q);
	Tlv m = Tlv(TLV, t);
	Tlv e = Tlv(TLV, m);
	Tlv u = Tlv(TLV, e);
	Tlv a = Tlv(INT_T, 200);
	Tlv_chain chain;
	chain.PutValue(&u);
	chain.PutValue(&a);
	chain.Serialize();
	unsigned char *Buffer = chain.mSerializedBuffer;

	Tlv_chain decoder;
	/*unsigned char Buffer[] = {
		0x00, 0x01, 0x00, 0x04, 0x05, 0x00, 0x00,0x00
	};*/
	decoder.Parse(Buffer, chain.mSerializedBytes);
	for (auto c : decoder.mTlv_vector) {
		if (c->tlv.mType == INT_T) {
			int value = (*(int *)(c->tlv.mValue));
			std::cout << "Type = " << c->tlv.mType << "\t length = " << c->tlv.mLength << "\t value = " << value << std::endl;
		}
		else std::cout << "Type = " << c->tlv.mType << "\t length = " << c->tlv.mLength << "\t value = " << c->tlv.mValue << std::endl;
	}
	return 0;
}