bool checkMain(int n){


	if (n >= 1 && n <= 11)
		return true;

	return false;
}

int getMain(){


	int temp;
	bool flag = false;

	do{
		printf("\nEnter Choice(1-11): ");
		scanf(" %d", &temp);

		flag = checkMain(temp);
	}

	while (!flag);

	return temp;
}




void printMain(){


		printf("\n1.Load Marks File");
		printf("\n2.Show Marks");
		printf("\n3.Compute Avg");
		printf("\n4.Compute Cgpa");
		printf("\n5.Save Marks");
		printf("\n6.Load Info File");
		printf("\n7.Show Info");
		printf("\n8.Save Info");
		printf("\n9.Left Join");
		printf("\n10.Query");
		printf("\n11.Exit\n");
	
}

void welcomeMessage(){

	printf("\n1.Insert");
	printf("\n2.search");
	printf("\n3.ParseString");
	printf("\n4.Exit");

}

bool check(int num){

	if (num == 1 || num == 2 || num == 3 || num == 4)
		return true;

	return false;

}

void printQueryError(){


	printf("\nWrong Query ......Wrong data is fetched from wrong tables");
	printf("\nPlease see whether the query fields matches with table fields");
	printf("\nQuery should be of form : ");
	printf("\nselect ! from @ where # $ *");

	printf("\nHere values might be : ");
	printf("\n ! - name,rollno,m1,m2,m3,m4,avg,cgpa,city,address,phoneno,pincode");
	printf("\n @ - marks,info");
	printf("\n # - name,rollno,m1,m2,m3,m4,avg,cgpa,city,address,phoneno,pincode");
	printf("\n $ - lt,gt,eq,le,ge,contains,startswith");
	printf("\n * - num,string,character\n\n");

	printf("\nfields in info table - ");
	printf("\nphoneno,address,pincode,city");

	printf("\nfields in marks table - ");
	printf("\nname,rollno,m1,m2,m3,m4,avg,cgpa\n\n");


}