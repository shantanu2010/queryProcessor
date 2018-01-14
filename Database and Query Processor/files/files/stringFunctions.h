int getLength(char* str){

	int index = 0;

	while (str[index] != '\0'){

		index++;
	}
	return index;
}

void stringCopy(char* destination, char* source){

	int i = 0;

	while (source[i] != '\0'){

		destination[i] = source[i];
		i++;

	}

	destination[i] = '\0';

}
int stringCompare(char* str1, char* str2){

	int i = 0;
	bool flag = false;

	for (i = 0; str1[i] != '\0'; i++){

		if (str1[i] == str2[i])
			continue;

		else{
			flag = true;
			break;
		}
	}
	if (flag)
		return -1;
	else
		return 0;

}

int subString(char* str, char* search){

	int count1 = 0, count2 = 0, m, n, flag;

	while (str[count1] != '\0')
		count1++;

	while (search[count2] != '\0')
		count2++;

	for (m = 0; m <= count1 - count2; m++){
		for (n = m; n < m + count2; n++){

			flag = 1;
			
			if (str[n] != search[n - m]){
				flag = 0;
				break;
			}
		}
		
		if (flag == 1)
			break;
	}
	if (flag == 1)
		return 1;
	else
		return 0;
}


char* getString(char* str, int* index){

	int iter = 0;
	char* temp = (char*)malloc(20 * sizeof(char));

	while (str[*index] == ' '){
		(*index)++;
	}

	while (str[*index] != '\0' && str[*index] != ' '){

		temp[iter] = str[*index];
		iter++;
		(*index)++;

	}
	temp[iter] = '\0';

	return temp;
}

int getIndexString(char* variableIdentifier){

	if (stringCompare(variableIdentifier, "name") == 0)
		return 1;

	else if (stringCompare(variableIdentifier, "phoneno") == 0)
		return 2;

	else if (stringCompare(variableIdentifier, "address") == 0)
		return 3;

	else if (stringCompare(variableIdentifier, "city") == 0)
		return 4;

	else if (stringCompare(variableIdentifier, "pincode") == 0)
		return 5;

	else return -1;


}

int getIndex(char* variableIdentifier){


	if (stringCompare(variableIdentifier, "rollno") == 0)
		return 1;
	else if (stringCompare(variableIdentifier, "m1") == 0)
		return 2;
	else if (stringCompare(variableIdentifier, "m2") == 0)
		return 3;
	else if (stringCompare(variableIdentifier, "m3") == 0)
		return 4;
	else if (stringCompare(variableIdentifier, "m4") == 0)
		return 5;
	else if (stringCompare(variableIdentifier, "avg") == 0)
		return 6;
	else if (stringCompare(variableIdentifier, "cgpa") == 0)
		return 7;

	else
		return -1;

}

