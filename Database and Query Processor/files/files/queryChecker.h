typedef struct Pair {
	char data[50];
	char key[40];
	struct Pair* next;
}Pair;

int getValue(char c){

	return c - '0';

}

int hashCode(char* key) {

	int i = 0;
	int result = 0;
	for (i = 0; key[i] != '\0'; i++){

		result += getValue(key[i]);

	}

	return result % 6;
}

bool isSpecial(char* str){

	bool flag1 = false;
	bool flag2 = false;

	int len = getLength(str);

	if (str[0] == '{' && str[len - 1] == '}')
		return true;

	return false;

}

int getOperator(char* str){


	if ((stringCompare(str, "lt") == 0))
		return 1;

	if ((stringCompare(str, "eq") == 0))
		return 2;

	if ((stringCompare(str, "gt") == 0))
		return 3;

	if ((stringCompare(str, "le") == 0))
		return 4;

	if ((stringCompare(str, "ge") == 0))
		return 5;

	else return -1;

}

int getType(char* str){


	if ((stringCompare(str, "contains")) == 0)
		return 1;

	if ((stringCompare(str, "startswith")) == 0)
		return 2;
	else return -1;

}