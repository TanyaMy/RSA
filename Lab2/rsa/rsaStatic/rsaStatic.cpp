#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "..\rsa\rsa.h"


int _tmain() {

	/*unsigned E, D;
	unsigned n = generateKeys(E, D);
	unsigned OpenMsg, CryptMsg, AfterDecryptMsg;
	int i;
	for (i = 0; i < 10; i++) {
		OpenMsg = rand() % n;
		crypt(OpenMsg, E, n, &CryptMsg);
		decrypt(CryptMsg, D, n, &AfterDecryptMsg);
		if (OpenMsg == AfterDecryptMsg)
			printf("OpenMsg = %u CryptMsg = %u AfterDecryptMsg = %u - OK\n", OpenMsg, CryptMsg, AfterDecryptMsg);
		else
			printf("OpenMsg = %u CryptMsg = %u AfterDecryptMsg = %u - Error\n", OpenMsg, CryptMsg, AfterDecryptMsg);
	}
	printf_s("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");*/

	multiLangExecute();

	system("pause");

	return 0;
}
