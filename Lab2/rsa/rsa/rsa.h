#pragma once
#ifdef RSA_EXPORTS
#define RSAAPI extern "C" _declspec (dllexport)
#else 
#define RSAAPI extern "C" _declspec (dllimport) 
#endif 


// ����������
RSAAPI bool crypt(unsigned openMsg, unsigned e, unsigned n, unsigned *cryptMsg);

// �����������
RSAAPI bool decrypt(unsigned cryptMsg, unsigned d, unsigned n, unsigned *openMsg);

// ��������� ������
RSAAPI unsigned generateKeys(unsigned &e, unsigned &d);
