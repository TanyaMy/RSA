#include "stdafx.h"
#include "rsa.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h> 
#include <Windows.h>
#include <tchar.h>


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
