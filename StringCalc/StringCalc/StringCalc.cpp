#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_NUM (32)
#define A_NUMBER (0)
#define B_NUMBER (1)
#define C_NUMBER (2)
#define D_NUMBER (3)
#define E_NUMBER (4)

static int ConvertQuinaryToDecimal(const int*, int);
static int ConvertStringToQuinary(const char*, int*);
static void ConvertDecimalToString(int ,char*);
static bool checkInputParam(const char*, char*, char*);

 int main(void)
 {
	char inputString[MAX_NUM] = "";
	char calculatedString[MAX_NUM] = "";
	char string1[MAX_NUM] = "";
	char string2[MAX_NUM] = "";
	int firstQuinary[MAX_NUM] = {};
	int secondQuinary[MAX_NUM] = {};
	int firstDecimal = 0;
	int secondDecimal = 0;
	int fullDecimal = 0;
	int firstStringLength = 0;
	int secondStringLength = 0;

	fgets(inputString, sizeof(inputString), stdin);
	if (strlen(inputString) == 0 || !checkInputParam(inputString, string1, string2)) {
		printf_s("Pleas Input Correct Param\n");
		return 0;
	}

	firstStringLength = ConvertStringToQuinary(string1, firstQuinary);
	secondStringLength = ConvertStringToQuinary(string2, secondQuinary);

	firstDecimal = ConvertQuinaryToDecimal(firstQuinary, firstStringLength);
	secondDecimal = ConvertQuinaryToDecimal(secondQuinary, secondStringLength);

	fullDecimal = firstDecimal + secondDecimal;

	ConvertDecimalToString(fullDecimal, calculatedString);

	printf("%s\n", calculatedString);

	return 0;
};

/*
 *	入力した文字列を確認しs_1, s_2に分割。
 *	分割後、s_1, s_2の先頭がAになっていないか確認
 *	@method	checkInputParam
 *	@in		char[]	inputString	入力された文字列
 *	@out	char*	string1		分割した文字列の1つめ(s_1に相当)
 *	@out	char*	string2		分割した文字列の2つめ(s_2に相当)
 *	return	boolean	true:分割した文字列の先頭がAでない、false:分割した文字列の先頭がA(エラー)
 */
static bool checkInputParam(const char *inputString, char* string1, char* string2)
{
	int inputStringLength = strlen(inputString);
	int count = 0;
	int name_count = 0;
	int hour_count = 0;

	//スペースまで読み込み、s_1とs_2を分割
	for (int firstCount = 0; count < inputStringLength && inputString[count] != ' '; count++, firstCount++) {
		string1[firstCount] = inputString[count];
	}
	count++;
	for (int secondCount = 0 ; count < inputStringLength && inputString[count] != '\n'; count++, secondCount++) {
		string2[secondCount] = inputString[count];
	}

	if (strlen(string1) == 0 || (strlen(string1) > 1 && string1[0] == 'A')) {
		return false;
	}

	if (strlen(string2) == 0 || (strlen(string2) == 1 && string2[0] == 'A')) {
		return false;
	}

	return true;
}

/*
 *	入力された文字列を5進数に変換
 *	@method	ConvertStringToQuinary
 *	@in		char*	string	分割された文字列
 *	@out	int*	quinary	文字列を5進数に変換したint配列
 *
 */
static int ConvertStringToQuinary(const char *string, int *quinary)
{
	// stringで渡ってきた文字列を読み込み、各文字に一致するNUMBERをquinaryに格納
	int stringLength = strlen(string);
	for (int count = 0; count < stringLength; count++) {
		switch (string[count]) {
			case 'A':
				quinary[count] = A_NUMBER;
				break;
			case 'B':
				quinary[count] = B_NUMBER;
				break;
			case 'C':
				quinary[count] = C_NUMBER;
				break;
			case 'D':
				quinary[count] = D_NUMBER;
				break;
			case 'E':
				quinary[count] = E_NUMBER;
				break;
		}
	}
	return stringLength;
}

/*
 *	5進数を10進数に変換
 *	@method	ConvertQuinaryToDecimal
 *	@in		int*	quinary			入力された文字列を5進数に変換した値を格納する配列
 *	@out	int		quinaryLength	quinaryの配列数
 */
static int ConvertQuinaryToDecimal(const int *quinary, int quinaryLength)
{
	/* quinaryの中を舐め、quinaryの要素数の累乗をbaseNumとし
	   baseNumとquinaryの中の値を掛け合わせたものをdecimalに加算*/
	int decimal = 0;
	int baseNum = 0;
	for (int count = 0; count < quinaryLength; count++) {
		baseNum = pow(5, (quinaryLength - (count + 1)));
		decimal += baseNum * quinary[count];

	}
	return decimal;
}

/**
 *	10進数を5進数に対する文字に変換
 *	@method ConvertDecimalToString
 *	@in		int		fullDecimal		入力された文字を合算した10進数の値
 *	@out	char[]	string			10進数を5進数に対する文字に変換した文字列
 */
static void ConvertDecimalToString(int fullDecimal, char *string)
{
	int mod = 0;
	int devide = fullDecimal;
	int tempNumbers[MAX_NUM] = {};
	int decimalLength = 1;

	// fullDecimalを5で割った余りと除値を5進数格納用のtempNumbersに順次格納していく
	while (1) {
		mod = devide % 5;
		devide /= 5;
		tempNumbers[decimalLength] = mod;
		if (devide <= 5) {
			tempNumbers[decimalLength -1] = devide;
			decimalLength++;
			break;
		}
		decimalLength++;
	}

	// 5進数に変換された値に対する文字をstringに詰めていく
	for (int stringCount = 0; stringCount < decimalLength; stringCount++) {
		switch (tempNumbers[stringCount]) {
		case A_NUMBER:
			string[stringCount] = 'A';
			break;
		case B_NUMBER:
			string[stringCount] = 'B';
			break;
		case C_NUMBER:
			string[stringCount] = 'C';
			break;
		case D_NUMBER:
			string[stringCount] = 'D';
			break;
		case E_NUMBER:
			string[stringCount] = 'E';
			break;
		}
	}
}