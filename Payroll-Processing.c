//PROGRAM-ID. Payroll-Processing.
//AUTHOR.  Joel Perkins.
//DATE-WRITTEN. May 4, 2008.

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main()
{
	char resp = 'y';
	int lineNum = 0;
	int empNum;
	char givenName[11];
	char surName[11];
	float ytd, gross, ficaTax;
	float tGross, tFicaTax;
	float ficaLimit = 69782.00;
	double tax = 0.0678;
	char string[80];

	struct tm *local;
  	time_t t;

	FILE *fp;
    int i;

    char fileOutName[26];

	printf("Enter output file name [25 Char Max]: ");
	scanf( "%s", fileOutName);

	fp = fopen(fileOutName, "w");
	if (fp == NULL)
	{
		printf("Could not open file for output.\n");
	    exit(0);
    }

    t = time(NULL);
    local = localtime(&t);

    //print file header.
   	fprintf(fp, "\t\t\tACME\t\t%s\n", asctime(local));
	fprintf(fp,"%-5s%-5s%-10s%-10s%10s%10s%10s\n","Line#", "Emp#", "Given Name", "SurName", "YTD($)", "Gross($)", "Fica Tax");

	//Loop that goes through data
	while(resp == 'y' || resp == 'Y')
	{
		printf("Please input Employee's Number: ");
		scanf("%d", &empNum);

		printf("Please input Employee's given Name[10 Char. Max]: ");
		scanf("%s", &givenName);

		printf("Please input Employee's SurName[10 Char. Max]: ");
		scanf("%s", &surName);

		printf("Please input Employee's YTD: ");
		scanf("%f", &ytd);

		printf("Please input Employee's Gross: ");
		scanf("%f", &gross);

		printf("Calculating Taxes\n");

		if(ytd > ficaLimit)		//No taxes
		{
			printf("YTD > ficaLimit, no tax.\n");
			ficaTax = 0.0;
		}
		else
		{
			if((ytd + gross) > ficaLimit)
			{
				printf("ytd + gross > ficaLimit, taxed only diffrence.\n");
				ficaTax = (ficaLimit - ytd) * tax;
			}
			else
			{
				printf("ytd + gross < ficaLimit, taxed all gross\n");
				ficaTax = gross * tax;
			}

		}


		//Adding up the totals
		tGross += gross;
		tFicaTax += ficaTax;
		//increment the line.
		lineNum++;


		//printing data.
		fprintf(fp,"%-5d%-5d%-10s%-10s%10.2f%10.2f%10.2f\n", lineNum, empNum, givenName, surName, ytd, gross, ficaTax);

		printf("Input more data? (y or n)\n");
		scanf("%s", &resp);
	}

	//Print totals
	//fprintf(fp,"%5s%5s%10s%10s%10s%10s%10s\n","Line#", "Emp#", "Given Name", "SurName", "YTD($)", "Gross($)", "Fica Tax");
	fprintf(fp,"%40s%10.2f%10.2f","Totals:\n", tGross, tFicaTax);



	//close(outFile);
	return 0;
}
