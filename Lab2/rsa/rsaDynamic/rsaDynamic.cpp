#include "stdafx.h"
#include <locale.h>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>

#define MAX_INPUT_LENGTH 50

// Визначення типів для адрес функцій
typedef bool (*TCRYPT)(unsigned, unsigned, unsigned, unsigned *);
typedef bool(*TDECRYPT)(unsigned, unsigned, unsigned, unsigned *);
typedef unsigned (*GENERATEKEYS)(unsigned *, unsigned *);


int _tmain(int argc, _TCHAR* argv[]) {
	HMODULE h = LoadLibrary(_T("rsa.dll"));
	if (h != 0) { // Визначення адрес для функцій, що експортуються
		TCRYPT crypt = (TCRYPT)GetProcAddress(h, "crypt");
		TDECRYPT decrypt = (TDECRYPT)GetProcAddress(h, "decrypt");
		GENERATEKEYS generateKeys = (GENERATEKEYS)GetProcAddress(h, "generateKeys");

		if (crypt && decrypt && generateKeys) {
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);

			TCHAR str[MAX_INPUT_LENGTH];
			unsigned e, d;
			unsigned n = generateKeys(&e, &d);
			int lang;
			const wchar_t *msg1;
			const wchar_t *msg2;
			const wchar_t *msg3;


			printf_s("Choose language: 1 - English, 2 - Russian, 3 - Ukrainian\n");
			scanf_s("%d", &lang);

			if (lang == 1) {
				_tprintf(_T("\nEnter the message to encode:\n"));
				msg1 = _T("\nSource message: ");
				msg2 = _T("\nEncrypted message: ");
				msg3 = _T("\nDecripted message: ");
			}

			else if (lang == 2) {
				_tsetlocale(LC_ALL, _T("Russian"));
				_tprintf(_T("\nВведите сообщение для шифрования:\n"));
				msg1 = _T("\nИсходное сообщение: ");
				msg2 = _T("\nЗашифрованное сообщение: ");
				msg3 = _T("\nРасшифрованное сообщение: ");
			}

			else if (lang == 3) {
				_tsetlocale(LC_ALL, _T("Ukrainian"));
				_tprintf(_T("\nВведіть повідомлення для шифрування:\n"));
				msg1 = _T("\nВихідне повідмлення: ");
				msg2 = _T("\nЗашифрование повідомлення: ");
				msg3 = _T("\nРозшифрование повідомлення: ");
			}
			
			
			_tscanf_s(_T(" %[^\n]s"), str, MAX_INPUT_LENGTH);

			const size_t size = _tcslen(str);
			
			_tprintf(msg1);
			for (int i = 0; i < size; i++)
			{
				_tprintf(_T("%c"), str[i]);
			}

			
			unsigned* encryptedStr = new unsigned[size];

			_tprintf(msg2);
			for (int i = 0; i < size; i++)
			{
				crypt(str[i], e, n, &encryptedStr[i]);
				_tprintf(_T("%d "), encryptedStr[i]);
			}

			unsigned* decryptedStr = new unsigned[size + 1];


			int counter = 0;
			_tprintf(msg3);
			for (counter = 0; counter < size; counter++)
			{
				unsigned a;
				decrypt(encryptedStr[counter], d, n, &a);
				decrypt(encryptedStr[counter], d, n, &decryptedStr[counter]);
			}

			decryptedStr[counter] = _T('\0');

			for (int i = 0; i < size; i++)
			{
				_tprintf(_T("%c"), decryptedStr[i]);
			}


			delete[] encryptedStr;
			delete[] decryptedStr;

			_tprintf(_T("\n"));

			system("pause");

			return 0;
		}
	}
}
