#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
#include "student.h"
#include "stringFunctions.h"
#include "queryChecker.h"
#include "address.h"

int size = 6;
int sizeStudent = 10;
int sizeAddress = 10;
int studentIndex = 0;
int addressIndex = 0;

Pair** array = (Pair**)malloc(6 * sizeof(Pair*));
Student** studentArray = (Student**)malloc(10 * sizeof(Student*));
Address** infoArray = (Address**)malloc(10 * sizeof(Address*));

char* searchF(char* key) {

	int hashIndex = hashCode(key);

	Pair* node = array[hashIndex];

	while (node != NULL) {

		if (stringCompare(node->key, key) == 0)
			return node->data;

		else
			node = node->next;
	}

	return NULL;
}


void insert(char* key, char* data) {

	Pair *item = (Pair*)malloc(sizeof(Pair));
	stringCopy(item->data, data);
	stringCopy(item->key, key);
	item->next = NULL;

	int hashIndex = hashCode(key);

	Pair* node = array[hashIndex];

	if (node == NULL){

		array[hashIndex] = item;
	}
	else{

		while ((node != NULL)){

			if ((stringCompare(node->key, item->key) == 0)){

				printf("\nDuplicate key, %s exists in hashmap with value %s", node->key, node->data);
				break;
			}

			node = node->next;
		}
		item->next = node;
		node = item;
	}
}

bool parse(char* str, char* query){

	int i = 0;
	int j = 0;

	int len1 = getLength(str);
	int len2 = getLength(query);

	while (i<len1 && j<len2){

		char* compare1 = getString(str, &i);
		char* compare2 = getString(query, &j);

		if (isSpecial(compare1))
			insert(compare1, compare2);

		else{

			if (stringCompare(compare1, compare2) != 0){
				printf("\nError is at word : %s", compare2);
				return false;
			}

		}

		free(compare1);
		free(compare2);
	}


	if (i >= len1 && j >= len2){
		return true;
	}
	
	else{
		printf("\nQuery is Wrong\n");	
		return false;
	}
}

void printData(int j,int temp, bool flag,int index){

		if (index == 0){

			printf("\n\t%d", studentArray[j]->rollNo);
		}
		else if (index == 1){

			printf("\n\t%s", studentArray[j]->name);
		}

		else if (index == 2){

			printf("\n\t%d", studentArray[j]->mark1);
		}
		else if (index == 3){

			printf("\n\t%d", studentArray[j]->mark2);
		}
		else if (index == 4){

			printf("\n\t%d", studentArray[j]->mark3);
		}
		else if (index == 5){

			printf("\n\t%d", studentArray[j]->mark4);
		}
		else if (index == 6){

			printf("\n\t%.2f", studentArray[j]->avg);
		}
		else if (index == 7){

			printf("\n\t%.2f", studentArray[j]->cgpa);
		}
		else if (index == 8 && flag){

			printf("\n\t%s", infoArray[temp]->phone);
		}

		else if (index == 9 && flag){

			printf("\n\t%s", infoArray[temp]->address);
		}
		else if (index == 10 && flag){

			printf("\n\t%s", infoArray[temp]->city);
		}
		else if (index == 11 && flag){

			printf("\n\t%s", infoArray[temp]->pinCode);
		}		
}

void computeAvgMain(bool* flag1){

	if (studentIndex <= 0){

		printf("\nData was not loaded in main memory");
		return;

	}
	*flag1 = true;

	int j = 0;
	for (j = 0; j < studentIndex; j++){

		studentArray[j]->avg = computeAvg(studentArray[j]->mark1, studentArray[j]->mark2, studentArray[j]->mark3, studentArray[j]->mark4);
	}

}

void computeCgpaMain(bool* flag2){

	if (studentIndex <= 0){

		printf("Data was not loaded in main memory");
		return;

	}

	*flag2 = true;
	int j = 0;
	for (j = 0; j < studentIndex; j++){

		studentArray[j]->cgpa = computeCgpa(studentArray[j]->mark1, studentArray[j]->mark2, studentArray[j]->mark3, studentArray[j]->mark4);
	}

}


int search(int rollNo){

	int index;
	for (index = 0; index < addressIndex; index++){

		if (infoArray[index]->rollNo == rollNo)
			return index;
	}
	return -1;

}


void gotoString(char* variableIdentifier, char* comparatorIdentifier, char* valueIdentifier,int arr){

	if ((strcmp(comparatorIdentifier, "lt") == 0) || (strcmp(comparatorIdentifier, "ge") == 0) || (strcmp(comparatorIdentifier, "eq") == 0) || (strcmp(comparatorIdentifier, "gt") == 0) || (strcmp(comparatorIdentifier, "le") == 0)){

		printf("\nWrong Query!!");
		return;
	}
	
	else{

		int index = getType(comparatorIdentifier);

		if (index == -1){

			printf("\nWrong Query");
			return;
		}

		int temp = 0;
		int j = 0;
		if (index == 1){
			bool flag = true;

			int m = getIndexString(variableIdentifier);
			
			if (m==1){
		
					for (j = 0; j < studentIndex; j++){

						temp = search(studentArray[j]->rollNo);

							if (temp == -1 && subString(studentArray[j]->name,valueIdentifier)){

								printData(j, temp, false,arr);
							}

							else if (subString(studentArray[j]->name, valueIdentifier)){
								printData(j, temp, true,arr);
							}
							else
								continue;
					}
			}

			else if (m == 2){

				for (temp = 0; temp < addressIndex; temp++){
					
					if (subString(infoArray[temp]->phone, valueIdentifier)){

						printData(j, temp, true, arr);
					}
				}
			}

			else if (m == 3){

				for (temp = 0; temp < addressIndex; temp++){
					
					if (subString(infoArray[temp]->address, valueIdentifier)){

						printData(j, temp, true, arr);
					}
				}
			}

			else if (m == 4){

				for (temp = 0; temp < addressIndex; temp++){

					if (subString(infoArray[temp]->city, valueIdentifier)){

						printData(j, temp, true, arr);
					}
				}
			}

			else if (m == 5){

				for (temp = 0; temp < addressIndex; temp++){
					
					if (subString(infoArray[temp]->pinCode, valueIdentifier)){

						printData(j, temp, true, arr);
					}
				}
			}
		}

		else if (index == 2){

			int m = getIndexString(variableIdentifier);
			if (m == 1){

				for (j = 0; j < studentIndex; j++){

					temp = search(studentArray[j]->rollNo);				
					char c = valueIdentifier[0];
						
						if (temp == -1 && (studentArray[j]->name[0] == c)){
		
							printData(j, temp, false,arr);
						}

						else if ((studentArray[j]->name[0] == c)){
								
							printData(j, temp, true,arr);
						}					
				}
			}

			if (m == 2){

				char c = valueIdentifier[0];

				for (temp = 0; temp < addressIndex; temp++){
					
					if ((infoArray[j]->phone[0] == c)){

						printData(j, temp, true, arr);
					}
			
				}

			}
			
			if (m == 3){

				char c = valueIdentifier[0];

				for (temp = 0; temp < addressIndex; temp++){

					if ((infoArray[j]->address[0] == c)){

						printData(j, temp, true, arr);
					}

				}

			}
			if (m == 4){

				char c = valueIdentifier[0];

				for (temp = 0; temp < addressIndex; temp++){
					
					if ((infoArray[j]->city[0] == c)){

						printData(j, temp, true, arr);
					}

				}
			}

			if (m == 5){

				char c = valueIdentifier[0];

				for (temp = 0; temp < addressIndex; temp++){

					if ((infoArray[j]->pinCode[0] == c)){

						printData(j, temp, true, arr);
					}

				}

			}

		}

	}

}

void gotoNumber(char* variableIdentifier, char* comparatorIdentifier,char* valueIdentifier,int items){

	if ((strcmp(comparatorIdentifier, "contains") == 0) || (strcmp(comparatorIdentifier, "startswith") == 0)){

		printf("\nWrong Query!!");
		return;
	}

	int oper = getOperator(comparatorIdentifier);
	
	if (oper == -1){

		printf("\nInvalid Query");
		return;
	}
	bool flag = true;

	int j, index, num, temp = 0;

	switch (oper){

		case 1:
						
		   index = getIndex(variableIdentifier);

			if (index == -1){

				printf("\nInvalid Query");
				return;
			}

			num = atoi(valueIdentifier);

			for (j = 0; j < studentIndex; j++){

				temp = search(studentArray[j]->rollNo);

				if (index == 1){

					if (temp == -1 && studentArray[j]->rollNo < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->rollNo < num){
						printData(j, temp, true, items);
					}

				}

				else if (index == 2){

					if (temp == -1 && studentArray[j]->mark1 < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->mark1 < num){

						printData(j, temp, true, items);
					}
				}
				else if (index == 3){

					if (temp == -1 && studentArray[j]->mark2 < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->mark2 < num){

						printData(j, temp, true, items);
					}

				}
				else if (index == 4){

					if (temp == -1 && studentArray[j]->mark3 < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->mark3 < num){

						printData(j, temp, true, items);
					}
				}
				else if (index == 5){

					if (temp == -1 && studentArray[j]->mark4 < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->mark4 < num){
						printData(j, temp, true, items);
					}

				}

				else if (index == 6){

					if (temp == -1 && studentArray[j]->avg < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->avg < num){

						printData(j, temp, true, items);
					}

				}
				else if (index == 7){

					if (temp == -1 && studentArray[j]->cgpa < num){

						printData(j, temp, false, items);
					}

					else if (studentArray[j]->cgpa < num){
						printData(j, temp, true, items);
					}


				}
			}
			
			break;
			case 2:

				 index = getIndex(variableIdentifier);
				 num = atoi(valueIdentifier);
				 
				for (j = 0; j < studentIndex; j++){

					temp = search(studentArray[j]->rollNo);

					if (index == 1){

						if (temp == -1 && studentArray[j]->rollNo == num){

							printData(j, temp, false, items);
						}

						else if (studentArray[j]->rollNo == num){
							printData(j, temp, true, items);
						}

					}

					else if (index == 2){

						if (temp == -1 && studentArray[j]->mark1 == num){

							printData(j, temp, false, items);
						}

						else if (studentArray[j]->mark1 == num){
							printData(j, temp, true, items);
						}
					}
					else if (index == 3){

						if (temp == -1 && studentArray[j]->mark2 == num){

							printData(j, temp, false, items);
						}

						else if (studentArray[j]->mark2 == num){
							printData(j, temp, true, items);
						}

					}

					else if (index == 4){

						if (temp == -1 && studentArray[j]->mark3 == num){

							printData(j, temp, false, items);
						}

						else if (studentArray[j]->mark3 == num){
							printData(j, temp, true, items);
						}
					}
					else if (index == 5){

						if (temp == -1 && studentArray[j]->mark4 == num){
							
							printData(j, temp, false, items);
						}

						else if (studentArray[j]->mark4 == num){
							
							printData(j, temp, true, items);
						}
					}

					else if (index == 6){

						if (temp == -1 && (int)studentArray[j]->avg == num){	
							printData(j, temp, false, items);
						}

						else if ((int)studentArray[j]->avg == num){
							printData(j, temp, true, items);
						}
					}

					else if (index == 7){

						if (temp == -1 && studentArray[j]->cgpa == num){
	
							printData(j, temp, false, items);
						}

						else if (studentArray[j]->cgpa== num){
							
							printData(j, temp, true, items);
						}

					}

				}
				
				break;

				case 3:
						
					 index = getIndex(variableIdentifier);
					 num = atoi(valueIdentifier);
					
					for (j = 0; j < studentIndex; j++){

						temp = search(studentArray[j]->rollNo);

						if (index == 1){

							if (temp == -1 && studentArray[j]->rollNo > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->rollNo >num){
								printData(j, temp, true, items);
							}

						}

						else if (index == 2){

							if (temp == -1 && studentArray[j]->mark1 > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->mark1 > num){
								printData(j, temp, true, items);
							}
						}
						else if (index == 3){

							if (temp == -1 && studentArray[j]->mark2 > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->mark2 > num){
								printData(j, temp, true, items);
							}

						}

						else if (index == 4){

							if (temp == -1 && studentArray[j]->mark3 > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->mark3 > num){
								printData(j, temp, true, items);
							}
						}
						else if (index == 5){

							if (temp == -1 && studentArray[j]->mark4 > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->mark4 > num){
								printData(j, temp, true, items);
							}
						}

						else if (index == 6){

							if (temp == -1 && studentArray[j]->avg > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->avg > num){
								printData(j, temp, true, items);
							}
						}

						else if (index == 7){

							if (temp == -1 && studentArray[j]->cgpa > num){

								printData(j, temp, false, items);
							}

							else if (studentArray[j]->cgpa > num){
								printData(j, temp, true, items);
							}

						}
					}
					
					break;

					case 4:

						
						 index = getIndex(variableIdentifier);
						 num = atoi(valueIdentifier);
						 j = 0;
						 

						for (j = 0; j < studentIndex; j++){

							temp = search(studentArray[j]->rollNo);


							if (index == 1){

								if (temp == -1 && studentArray[j]->rollNo <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->rollNo <= num){
									printData(j, temp, true, items);
								}

							}

							else if (index == 2){

								if (temp == -1 && studentArray[j]->mark1 <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->mark1 <= num){
									printData(j, temp, true, items);
								}
							}
							else if (index == 3){

								if (temp == -1 && studentArray[j]->mark2 <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->mark2 <= num){
									printData(j, temp, true, items);
								}
							}

							else if (index == 4){

								if (temp == -1 && studentArray[j]->mark3 <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->mark3 <= num){
									printData(j, temp, true, items);
								}
							}
							else if (index == 5){

								if (temp == -1 && studentArray[j]->mark4 <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->mark4 <= num){
									printData(j, temp, true, items);
								}
							}
							else if (index == 6){

								if (temp == -1 && studentArray[j]->avg <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->avg <= num){
									printData(j, temp, true, items);
								}
							}

							else if (index == 7){

								if (temp == -1 && studentArray[j]->cgpa <= num){

									printData(j, temp, false, items);
								}

								else if (studentArray[j]->cgpa <= num){
									printData(j, temp, true, items);
								}
							}
						}
						
						break;

					case 5:

							index = getIndex(variableIdentifier);
							num = atoi(valueIdentifier);
							
							for (j = 0; j < studentIndex; j++){

								temp = search(studentArray[j]->rollNo);

								if (index == 1){

									if (temp == -1 && studentArray[j]->rollNo >= num){

										printData(j, temp, false, items);
									}

									else if (studentArray[j]->rollNo >= num){
										printData(j, temp, true, items);
									}

								}

								else if (index == 2){

									if (temp == -1 && studentArray[j]->mark1 >= num){

										printData(j, temp, false, items);
									}

									else if (studentArray[j]->mark1 >= num){
										printData(j, temp, true, items);
									}
								}
								else if (index == 3){

									if (temp == -1 && studentArray[j]->mark2 >= num){

										printData(j, temp, false, items);
									}

									else if (studentArray[j]->mark2 >= num){
										printData(j, temp, true, items);
									}


								}

								else if (index == 4){

									if (temp == -1 && studentArray[j]->mark3 >= num){


										printData(j, temp, false, items);
									}

									else if (studentArray[j]->mark3 >= num){

										printData(j, temp, true, items);
									}
								}
								else if (index == 5){

									if (temp == -1 && studentArray[j]->mark4 >= num){


										printData(j, temp, false, items);
									}

									else if (studentArray[j]->mark4 >= num){
										printData(j, temp, true, items);
									}


								}

								else if (index == 6){

									if (temp == -1 && studentArray[j]->avg >= num){


										printData(j, temp, false, items);
									}

									else if (studentArray[j]->avg >= num){

										printData(j, temp, true, items);
									}


								}

								else if (index == 7){

									if (temp == -1 && studentArray[j]->cgpa >= num){


										printData(j, temp, false, items);
									}

									else if (studentArray[j]->cgpa >= num){

										printData(j, temp, true, items);
									}

								}

							}
						
						break;
				}
}

int getFields(){


	if (stringCompare("rollno", searchF("{cn}")) == 0){

		return 0;
	}

	else if (stringCompare("name", searchF("{cn}")) == 0){

		return 1;
	}

	else if (stringCompare("m1", searchF("{cn}")) == 0){

		return 2;
	}
	else if (stringCompare("m2", searchF("{cn}")) == 0){

		return 3;
	}
	else if (stringCompare("m3", searchF("{cn}")) == 0){

		return 4;
	}
	else if (stringCompare("m4", searchF("{cn}")) == 0){

		return 5;
	}
	else if (stringCompare("avg", searchF("{cn}")) == 0){

		return 6;
	}
	else if (stringCompare("cgpa", searchF("{cn}")) == 0){

		return 7;
	}
	else if (stringCompare("phoneno", searchF("{cn}")) == 0){

		return 8;
	}
	else if (stringCompare("address", searchF("{cn}")) == 0){

		return 9;

	}

	else if (stringCompare("city", searchF("{cn}")) == 0){

		return 10;

	}

	else if (stringCompare("pincode", searchF("{cn}")) == 0){

		return 11;

	}

	else
		return -1;

}

// To check whether fields in query matches its table!
bool checkQuery(){


	char* temp = searchF("{dn}");
	if (strcmp(temp, "marks") == 0){

		char* temp1 = searchF("{cn}");
		if ((strcmp(temp1, "name") == 0) || (strcmp(temp1, "rollno") == 0) || (strcmp(temp1, "m1") == 0) || (strcmp(temp1, "m2") == 0) || (strcmp(temp1, "m3") == 0)
			|| (strcmp(temp1, "m4") == 0) || (strcmp(temp1, "avg") == 0) || (strcmp(temp1, "cgpa") == 0)){


			char* temp2 = searchF("{en}");
			if ((strcmp(temp2, "name") == 0) || (strcmp(temp2, "rollno") == 0) || (strcmp(temp2, "m1") == 0) || (strcmp(temp2, "m2") == 0) || (strcmp(temp2, "m3") == 0)
				|| (strcmp(temp2, "m4") == 0) || (strcmp(temp2, "avg") == 0) || (strcmp(temp2, "cgpa") == 0)){


				char* temp3 = searchF("{fn}");

				if ((strcmp(temp3, "lt") == 0) || (strcmp(temp3, "gt") == 0) || (strcmp(temp3, "eq") == 0) || (strcmp(temp3, "le") == 0) || (strcmp(temp3, "ge") == 0)
					|| (strcmp(temp3, "contains") == 0) || (strcmp(temp3, "startswith") == 0)){
					return true;
				}
			}
		}

	}

	else if (strcmp(temp, "info") == 0){

		char* temp1 = searchF("{cn}");
		if ((strcmp(temp1, "address") == 0) || (strcmp(temp1, "city") == 0) || (strcmp(temp1, "pincode") == 0)
			|| (strcmp(temp1, "phoneno") == 0)){

			char* temp2 = searchF("{en}");
			if ((strcmp(temp2, "address") == 0) || (strcmp(temp2, "city") == 0) || (strcmp(temp2, "pincode") == 0)
				|| (strcmp(temp2, "phoneno") == 0)){

				char* temp3 = searchF("{fn}");

				if ((strcmp(temp3, "contains") == 0) || (strcmp(temp3, "startswith") == 0) ){
					return true;
				}
			}
		}
	}

	return false;
}

void queryProcessor(){


	if (studentIndex <= 0 && addressIndex<=0){

		printf("\nPlease load both marks and info files before processing queries!");
		return;
	}

	char* query = (char*)malloc(50 * sizeof(char));
	char* variableIdentifier = (char*)malloc(30 * sizeof(char));
	char* comparatorIdentifier = (char*)malloc(30 * sizeof(char));
	char* valueIdentifier = (char*)malloc(30 * sizeof(char));
	char* str = "select {cn} from {dn} where {en} {fn} {gn}";

	int j = 0;
	for (j = 0; j < size; j++){
		array[j]=NULL;
	}

	printf("\nFetch data from marks or info table....");

	printf("\nEnter Query : ");
	scanf(" %[^\n]", query);

	
	bool flag = parse(str, query);
	bool verify = false;
	if (flag)
		verify = checkQuery();

	if (!verify || !flag){

		printQueryError();
		return;
	}
	if (flag && verify){

		int getItems = getFields();

		if (getItems == -1){

			printf("\nItem doesnot exist");
			return;
		}

		printf("\t%s\n", searchF("{cn}"));

		strcpy(variableIdentifier, searchF("{en}"));
		strcpy(comparatorIdentifier, searchF("{fn}"));
		strcpy(valueIdentifier, searchF("{gn}"));

		if ((strcmp(variableIdentifier, "m1") == 0) || (strcmp(variableIdentifier, "m2") == 0) || (strcmp(variableIdentifier, "m3") == 0) || ((strcmp(variableIdentifier, "m4") == 0) || (strcmp(variableIdentifier, "avg") == 0) || (strcmp(variableIdentifier, "cgpa") == 0))){			
			gotoNumber(variableIdentifier, comparatorIdentifier, valueIdentifier, getItems);

		}

		else if ((strcmp(variableIdentifier, "name") == 0) || (strcmp(variableIdentifier, "pincode") == 0) || (strcmp(variableIdentifier, "address") == 0) || ((strcmp(variableIdentifier, "city") == 0) || (strcmp(variableIdentifier, "phoneno") == 0))){

			gotoString(variableIdentifier, comparatorIdentifier, valueIdentifier, getItems);

		}

		else
			printf("\nWrong Query");
		
	}
	
	else
		printf("\nWrong Query");

	printf("\n\n");
	return;
}

//To increase the size of Student Array
void reallocateMemoryStudent(){

	int j = 0;

	Student** tempArray = (Student**)malloc((sizeStudent * 2)*sizeof(Student*));

	for (j; j < studentIndex; j++){

		tempArray[j] = studentArray[j];
	}

	sizeStudent = sizeStudent * 2;
	free(studentArray);
	studentArray = tempArray;

}

//To increase the size of Address Array
void reallocateAddressStudent(){

	int j = 0;

	Address** tempArray2 = (Address**)malloc((sizeAddress * 2)*sizeof(Address*));

	for (j; j < addressIndex; j++){

		tempArray2[j] = infoArray[j];
	}

	sizeAddress = sizeAddress * 2;
	free(infoArray);
	infoArray = tempArray2;
	
}

int checkRedundancyOfStudent(Student* temp){

	int j = 0;

	for (j; j < studentIndex; j++){

		if (temp->rollNo == studentArray[j]->rollNo)
			return j;
	}

	return - 1;

}


int checkRedundancyOfAddress(Address* temp){

	int j = 0;

	for (j; j < addressIndex; j++){

		if (temp->rollNo == infoArray[j]->rollNo)
			return j;
	}

	return -1;

}

void loadStudent(bool* flag1,bool* flag2){

	*flag1 = false;
	*flag2 = false;
	FILE* inFile;
	bool redundancy = false;
	char buf[256];
	char* str = (char*)malloc(50*sizeof(char));
	printf("\nEnter File to be Loaded : ");
	scanf(" %s", str);

	if (buf == NULL) {
		printf("No memory\n");
		return ;
	}

	if ((inFile = fopen(str, "r")) == NULL){
		printf("File could not be opened.\n");
		return;
	}
	//To skip fields present in file
	fgets(buf, 256, inFile);
	
	while (fgets(buf, 256, inFile) != NULL){

		Student* tempStuct = (Student*)malloc(sizeof(Student));

		tempStuct->rollNo = atoi(strtok(buf, ","));
		strcpy(tempStuct->name, strtok(NULL, ","));
		tempStuct->mark1 = atoi(strtok(NULL, ","));
		tempStuct->mark2 = atoi(strtok(NULL, ","));
		tempStuct->mark3 = atoi(strtok(NULL, ","));
		tempStuct->mark4 = atoi(strtok(NULL, ","));
		tempStuct->avg = -1;
		tempStuct->cgpa = -1;
		int duplicate = checkRedundancyOfStudent(tempStuct);

		if (duplicate != -1){

			//To Skip reasking Override or ignore
			if (redundancy)
				continue;
			
			printf("\nDuplicate Exists....Do You want to override or ignore?");
			printf("\n\t1.Override");
			printf("\n\t2.ignore");

			int option;

			do{
				printf("\n\tEnter Choice : ");
				scanf(" %d", &option);

			} while (option < 1 || option >2);


			if (option == 1){

				studentArray[duplicate] = tempStuct;
				redundancy = true;
				
			}

			else if (option == 2){
				redundancy = true;
				continue;
			}

		}
		else{

			studentArray[studentIndex] = tempStuct;

			(studentIndex)++;

			if (studentIndex > sizeStudent - 1){

				reallocateMemoryStudent();
			}
		}

	}
	fclose(inFile);
}

void showStudent(){

	if (studentIndex <= 0){

		printf("\nFile couldnot be loaded");
		return;

	}

	else{

		int j = 0;

		printf("\nRollNo\tName\tMarks1\tMarks2\tMarks3\tMarks4\tAverage\tCgpa");
		for (j; j < studentIndex; j++){

			printf("\n%d\t%s\t%d\t%d\t%d\t%d\t%.2f\t%.2f", studentArray[j]->rollNo, studentArray[j]->name, studentArray[j]->mark1, studentArray[j]->mark2, studentArray[j]->mark3, studentArray[j]->mark4, studentArray[j]->avg, studentArray[j]->cgpa);
		}
	}
}

void loadAddress(bool* flag3){
	
	FILE* inFile;
	*flag3 = true;
	char buf[256];
	char* str = (char*)malloc(50 * sizeof(char));
	printf("\nEnter File Path : ");
	scanf(" %s", str);

	if (buf == NULL) {
		printf("No memory\n");
		return;
	}

	if ((inFile = fopen(str, "r")) == NULL){
		printf("File could not be opened.\n");
		return;
	}

	bool redundancy = false;
	//To skip fields present in file
	fgets(buf, 256, inFile);

	while (fgets(buf, 256, inFile) != NULL){

		Address* temp = (Address*)malloc(sizeof(Address));
		temp->rollNo = atoi(strtok(buf, ","));
		strcpy(temp->phone, strtok(NULL, ","));
		strcpy(temp->address, strtok(NULL, ","));
		strcpy(temp->city, strtok(NULL, ","));
		strcpy(temp->pinCode, strtok(NULL, ","));

		int duplicate = checkRedundancyOfAddress(temp);

		if (duplicate != -1 ){

			//To Skip reasking Override or ignore
			if (redundancy)
				continue;

			printf("\nDuplicate Exists....Do You want to override or ignore?");
			printf("\n\t1.Override");
			printf("\n\t2.ignore");

			int option;

			do{
				printf("\n\tEnter Choice : ");
				scanf(" %d", &option);

			} while (option < 1 || option >2);


			if (option == 1){

				infoArray[duplicate] = temp;
				redundancy = true;
				
			}

			else {
				redundancy = true;
				continue;
			}

		}
		else{

			infoArray[addressIndex] = temp;
			
			(addressIndex)++;

			if (addressIndex > sizeAddress - 1){

				reallocateAddressStudent();
			}
		}

	}
	fclose(inFile);
}

void showAddress(){

	if (addressIndex <= 0){

		printf("\nFile couldnot be loaded");
		return;

	}

	else{

		int j = 0;
		printf("\nRollNo\tPhone\t\tAddress\t\tCity\t\tpinCode");
		for (j; j < addressIndex; j++){

			printf("\n%d\t%s\t%s\t%s\t%s", infoArray[j]->rollNo, infoArray[j]->phone, infoArray[j]->address, infoArray[j]->city, infoArray[j]->pinCode);

		}

	}

}


void merge(){

	if (studentIndex > 0 && addressIndex > 0){
		
		int index = 0;		
		int temp;

		printf("\nRollNo\tName\tMarks1\tMarks2\tMarks3\tMarks4\tAverage\tCgpa\tPhone\t\tAddress\t\tCity\tpinCode");

		for (index; index < studentIndex; index++){

			temp = search(studentArray[index]->rollNo);

			if (temp == -1){

				printf("\n%d\t%s\t%d\t%d\t%d\t%d\t%.2f\t%.2f", studentArray[index]->rollNo, studentArray[index]->name, studentArray[index]->mark1, studentArray[index]->mark2, studentArray[index]->mark3, studentArray[index]->mark4, studentArray[index]->avg, studentArray[index]->cgpa);
			}

			else{				
				printf("\n%d\t%s\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%s\t%s\t%s\t%s", studentArray[index]->rollNo, studentArray[index]->name, studentArray[index]->mark1, studentArray[index]->mark2, studentArray[index]->mark3, studentArray[index]->mark4, studentArray[index]->avg, studentArray[index]->cgpa, infoArray[temp]->phone, infoArray[temp]->address, infoArray[temp]->city, infoArray[temp]->pinCode);

			}
							
		}

	}
	else{

		printf("\nFiles have not loaded properly into ram.Please load both marks and info file");
	}

}

void saveFileAddress(){

	if (addressIndex <= 0){

		printf("\nData was not loaded in main memory");
		return;

	}

	FILE* outFile;
	int j = 0;
	char* str = (char*)malloc(50 * sizeof(char));
	printf("\nEnter Destination File Name : ");
	scanf(" %[^\n]", str);

	char buf[256];
	if (buf == NULL) {
		printf("No memory\n");
		return;
	}

	if ((outFile = fopen(str, "w")) == NULL){
		printf("\nFile could not be opened.\n");
	}

	fprintf(outFile, "rollNo,phone,address,city,pincode\n");
	for (j = 0; j < addressIndex; j++){


		fprintf(outFile, "%d,%s,%s,%s,%s\n", infoArray[j]->rollNo, infoArray[j]->phone, infoArray[j]->address, infoArray[j]->city, infoArray[j]->pinCode);
	
	}
	fclose(outFile);

	getchar();

	return;

}


void saveFileStudent(bool* flag1,bool*flag2){

	if (studentIndex <= 0){

		printf("\nData was not loaded in main memory");
		return;

	}
	char buf[256];

	FILE* outFile;
	int j = 0;
	char* str = (char*)malloc(50 * sizeof(char));
	printf("\nEnter Destination File Name : ");
	scanf(" %[^\n]", str);

	if (buf == NULL) {
		printf("No memory\n");
		return;
	}

	if ((outFile = fopen(str, "w")) == NULL){
		printf("File could not be opened.\n");
	}
	
	fprintf(outFile, "rollNo,name,m1,m2,m3,m4\n");
	for (j = 0; j < studentIndex; j++){

			fprintf(outFile, "%d,%s,%d,%d,%d,%d\n", studentArray[j]->rollNo, studentArray[j]->name, studentArray[j]->mark1, studentArray[j]->mark2, studentArray[j]->mark3, studentArray[j]->mark4);
	}
	fclose(outFile);
	
	getchar();
	
	return;

}


int main(void){

	bool flagAvg = false;
	bool flagCgpa = false;
	bool flag3 = false;	

	int option;
	
	int i = 0;
	// To initialize heap array
	for (i; i < size; i++){

		array[i] = NULL;
	}

	do{
		printMain();
		option = getMain();
		
		switch (option){

			case 1:	loadStudent(&flagAvg, &flagCgpa);
				break;
			case 2: showStudent();
				break;
			case 3:computeAvgMain(&flagAvg);
				break;
			case 4:computeCgpaMain(&flagCgpa);
				break;
			case 5:saveFileStudent(&flagAvg, &flagCgpa);
				break;
			case 6: loadAddress(&flag3);
				break;
			case 7:showAddress();
				break;
			case 8:saveFileAddress();
				break;
			case 9: merge();
				break;
			case 10: queryProcessor();
				break;
			case 11:
				exit(0);
				break;
		}

	} while (option!=11);
}