#include "stdafx.h"
#include <locale.h>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>


typedef bool (*TCRYPT)(unsigned, unsigned, unsigned, unsigned *);
typedef bool(*TDECRYPT)(unsigned, unsigned, unsigned, unsigned *);
typedef unsigned (*GENERATEKEYS)(unsigned *, unsigned *);
typedef void(*MULTILANGEXECUTE)();


int _tmain(int argc, _TCHAR* argv[]) {
	HMODULE h = LoadLibrary(_T("rsa.dll"));
	if (h != 0) { 
		TCRYPT crypt = (TCRYPT)GetProcAddress(h, "crypt");
		TDECRYPT decrypt = (TDECRYPT)GetProcAddress(h, "decrypt");
		GENERATEKEYS generateKeys = (GENERATEKEYS)GetProcAddress(h, "generateKeys");
		MULTILANGEXECUTE multiLangExecute = (MULTILANGEXECUTE)GetProcAddress(h, "multiLangExecute");

		if (crypt && decrypt && generateKeys && multiLangExecute) {
			
			multiLangExecute();

			system("pause");

			return 0;
		}
	}
}
