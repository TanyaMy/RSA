#include "stdafx.h"
#include "rsa.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h> 
#include <Windows.h>
#include <tchar.h>

#define MAX_MES_LENGTH 50

unsigned getPrime(){
	unsigned n = ((rand() % 256) | 1) + 2; //нечетное число

	for (unsigned i = 3; i * i <= n; i += 2)//проверка на простоту
		if (n % i == 0) {//если составное, увеличиваем n и идем сначала
			n += 2;
			i = 1;
		}
	return n;
}

unsigned gcd(unsigned x, unsigned y) {
	while (x && y) {
		if (x > y)x %= y; else y %= x;
	}
	return x + y;
}

unsigned powMod(unsigned a, unsigned key, unsigned n) {
	int count = 0;
	unsigned tempKey = key;

	while (tempKey != 1)
	{
		tempKey /= 2;
		count++;
	}

	unsigned result = a;

	for (int i = count - 1; i >= 0; i--)
	{
		result *= result;
		result %= n;
		if ((key >> i) & 1)
		{
			result *= a;
			result %= n;
		}
	}

	return result;
}

//Генерация ключей
RSAAPI unsigned generateKeys (unsigned &e, unsigned &d){
	unsigned p = getPrime();
	unsigned q = getPrime();

	while (p == q)
	{
		q = getPrime();
	}

	unsigned n = p*q;

	unsigned fi = (p - 1)*(q - 1);

	for (e = 3; ; e += 2) {
		if (gcd(e, fi) == 1) {
			break;
		}
	}

	for (d = 2; ; d++) {
		if (e * d % fi == 1) {
			break;
		}
	}

	return n;
}

// Шифрование
RSAAPI bool crypt (unsigned openMsg, unsigned e, unsigned n, unsigned *cryptMsg){
	if (openMsg > n) return false;
		*cryptMsg = powMod(openMsg, e, n);
	return true;
}

// Расшифровка
RSAAPI bool decrypt (unsigned cryptMsg, unsigned d, unsigned n, unsigned *openMsg){
	if (cryptMsg > n) return false;
		*openMsg = powMod(cryptMsg, d, n);
	return true;
}


RSAAPI void multiLangExecute() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TCHAR str[MAX_MES_LENGTH];
	unsigned e, d;
	unsigned n = generateKeys(e, d);
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
	else {
		_tprintf(_T("\nERROR!\n\n"));
	}

	_tscanf_s(_T(" %[^\n]s"), str, MAX_MES_LENGTH);

	const size_t size = _tcslen(str);

	_tprintf(msg1);
	for (int i = 0; i < size; i++)
	{
		_tprintf(_T("%c"), str[i]);
	}
	
	unsigned* encMsg = new unsigned[size];

	_tprintf(msg2);
	for (int i = 0; i < size; i++)
	{
		crypt(str[i], e, n, &encMsg[i]);
		_tprintf(_T("%d "), encMsg[i]);
	}

	unsigned* decMsg = new unsigned[size + 1];

	int counter = 0;
	_tprintf(msg3);
	for (counter = 0; counter < size; counter++)
	{
		unsigned a;
		decrypt(encMsg[counter], d, n, &a);
		decrypt(encMsg[counter], d, n, &decMsg[counter]);
	}

	decMsg[counter] = _T('\0');

	for (int i = 0; i < size; i++)
	{
		_tprintf(_T("%c"), decMsg[i]);
	}

	_tprintf(_T("\n\n"));

	delete[] encMsg;
	delete[] decMsg;
}