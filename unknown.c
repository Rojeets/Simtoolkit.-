#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct sim
{
	char user_name[50];
	long int phone_number;
	float balance;
	float data;
};
int welcome_page(struct sim s[], int size);
int login(struct sim s[], int size);
int interface(struct sim s[], int size, int i);
int balance_query(struct sim s[], int i);
int balance_topup(struct sim s[], int size, int i);
int data_query(struct sim s[], int i);
int data_topup(struct sim s[], int size, int i);
int transfer_balance(struct sim s[], int size, int i);
int main()
{
	int size = 5;
	struct sim s[size];
	int i;
	FILE *p = fopen("users.bin", "rb+");
	fseek(p, 0, SEEK_SET);
	for (i = 0; i < size; i++)
	{
		fscanf(p, "%s\t%ld\t%f\t%f\n", &s[i].user_name, &s[i].phone_number, &s[i].balance, &s[i].data);
	}
	fclose(p);
	welcome_page(s, size);
}
int welcome_page(struct sim s[], int size)
{
	int choice;
	while (1)
	{
		getch();

		system("cls");
		printf("!!Wellcome to SIM TOOLKIT!!");
		getch();
		system("cls");
		printf("\n1. Login\n2. Exit");
		printf("\nEnter choice:");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			login(s, size);
			break;
		case 2:
			printf("Have a good day :)");
			break;

		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}
int login(struct sim s[], int size)
{
	int i;
	char name[50];
	long int number;
	system("cls");
	printf("Enter your name:");
	scanf("%s", name);
	for (i = 0; i < size; i++)
	{
		while (strcmp(s[i].user_name, name) == 0)
		{
			system("cls");
			printf("Hey %s", name);
			printf("\nEnter your number:");
			scanf("%ld", &number);
			if (number == s[i].phone_number)
			{
				system("cls");
				printf("Welcome %s !!", name);
				getch();
				interface(s, size, i);
				break;
			}
			else
			{
				printf("Invaild number.");
				break;
			}
		}
	}
}
int interface(struct sim s[], int size, int i)
{
	system("cls");
	int choice;
	while (1)
	{
		printf("Welcome %s !! ", s[i].user_name);

		printf("\nFor balance query press 1.\nFor balance topup press 2.\nFor data query press 3.\nFor data topup press 4\nFor balance transfer press 5\n ");
		printf("______");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			balance_query(s, i);
			break;

		case 2:
			balance_topup(s, size, i);
			break;

		case 3:
			data_query(s, i);
			break;

		case 4:
			data_topup(s, size, i);
			break;

		case 5:
			transfer_balance(s, size, i);
			break;

		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}
int balance_query(struct sim s[], int i)
{
	printf("Dear %s, your current balance is Rs. %f.\n Expires on 2025.", s[i].user_name, s[i].balance);
	if (s[i].balance < 10)
	{
		printf("\n\n\n\nYour balance is less than Rs. 10.\nPlease recharge before expiry date.");
		getch();
	}
	getch();
	system("cls");
}
int balance_topup(struct sim s[], int size, int i)
{
	int amount;
	FILE *p = fopen("users.bin", "rb");
	FILE *temp = fopen("temp.bin", "wb");
	system("cls");
	printf("Enter amount:");
	scanf("%d", &amount);
	int j;
	for (j = 0; j < size; j++)
	{
		if (fscanf(p, "%s\t%ld\t%f\t%f\n", s[j].user_name, &s[j].phone_number, &s[j].balance, &s[j].data) != EOF)
		{
			while (s[j].phone_number == s[i].phone_number)
			{
				s[j].balance = s[j].balance + amount;
				printf("Dear %s, Your new balance is %f.\nThank you??.", s[j].user_name, s[j].balance);
				break;
			}
			fprintf(temp, "%s\t%ld\t%f\t%f\n", s[j].user_name, s[j].phone_number, s[j].balance, s[j].data);
		}
	}
	fclose(p);
	fclose(temp);
	remove("users.bin");
	rename("temp.bin", "users.bin");
	system("cls");
}

int data_query(struct sim s[], int i)
{
	if (s[i].data == 0)
	{
		system("cls");
		printf("you haven't subscribed any data pack.");
		getch();
	}
	else
	{
		system("cls");
		printf("you have %.2fmb data left", s[i].data);
		getch();
	}
}
int data_topup(struct sim s[], int size, int i)
{
	int j;
	FILE *p = fopen("users.bin", "rb");
	FILE *temp = fopen("temp.bin", "wb");
	system("cls");
	int choice;
	printf("Available data packs:\n");
	printf("1. 150mb  ----- Rs. 25\n2. 250mb  ----- Rs. 30\n3. 500mb  ----- Rs. 50\n4. 750mb  ----- Rs. 75\n5. 1024mb  ----- Rs. 100\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	if (p == NULL || temp == NULL)
	{
		printf("Error opening files");
		return 1;
	}

	for (j = 0; j < size; j++)
	{
		if (s[j].phone_number == s[i].phone_number)
		{
			switch (choice)
			{
			case 1:
				if (s[j].balance >= 25)
				{
					s[j].data += 150;
					s[j].balance -= 25;
					system("cls");
					printf("\nYou have sucessfully subscribed 150 mb data pack.");
					getch();
					break;
				}
				else
				{
					system("cls");
					printf("Insufficient balance");
					getch();
					break;
				}
				break;

			case 2:
				if (s[j].balance >= 30)
				{
					s[j].data += 250;
					s[j].balance -= 30;
					system("cls");
					printf("\nYou have sucessfully subscribed 250 mb data pack.");
					getch();
					break;
				}
				else
				{
					system("cls");
					printf("Insufficient balance");
					getch();
					break;
				}
				break;

			case 3:
				if (s[j].balance >= 50)
				{
					s[j].data += 500;
					s[j].balance -= 50;
					system("cls");
					printf("\nYou have sucessfully subscribed 500 mb data pack.");
					getch();
					break;
				}
				else
				{
					system("cls");
					printf("Insufficient balance");
					getch();
				}
				break;

			case 4:
				if (s[j].balance >= 75)
				{
					s[j].data += 750;
					s[j].balance -= 75;
					system("cls");
					printf("\nYou have sucessfully subscribed 750 mb data pack.");
					getch();
					break;
				}
				else
				{
					system("cls");
					printf("Insufficient balance");
					getch();
					break;
				}
				break;

			case 5:
				if (s[j].balance >= 100)
				{
					s[j].data += 1024;
					s[j].balance -= 100;
					system("cls");
					printf("\nYou have sucessfully subscribed 1024 mb data pack.");
					getch();
					break;
				}
				else
				{
					system("cls");
					printf("Insufficient balance");
					getch();
					break;
				}
				break;

			default:
				system("cls");
				printf("Invalid choice. Please try again.\n");
				getch();
			}

			fprintf(temp, "%s\t%ld\t%f\t%f\n", s[j].user_name, s[j].phone_number, s[j].balance, s[j].data);
		}
	}

	fclose(p);
	fclose(temp);
	remove("users.bin");
	rename("temp.bin", "users.bin");
	system("cls");
}
int transfer_balance(struct sim s[], int size, int i)
{
	int j;
	FILE *p = fopen("users.bin", "rb");
	FILE *temp = fopen("temp.bin", "wb");
	system("cls");
	long int n;
	float amount;
	printf("Enter reciver no. :");
	scanf("%ld", &n);
	if (p == NULL || temp == NULL)
	{
		system("cls");
		printf("Error opening files");
		getch();
		return 1;
	}
	for (j = 0; j < size; j++)
	{
		if (s[j].phone_number == n)
		{
			printf("Reciver name : %s\nReciver number :%ld", s[j].user_name, s[j].phone_number);
			printf("\nEnter amount :");
			scanf("%f", &amount);
			getch();
			printf("\nPress 'ENTER' to proceed");
			getch();
			if (s[i].balance < amount)
			{
				system("cls");
				printf("\nInsufficient balance");
				getch();
				system("cls");
				return 1;
			}
			s[j].balance += amount;
			system("cls");
			printf("\nAmount transfer sucessfull");
			getch();
			system("cls");
			printf("Rs. %f has been transfered sucessfully to %s", amount, s[j].user_name);
			getch();
			system("cls");

			getch();
			system("cls");
		}
		fprintf(temp, "%s\t%ld\t%f\t%f\n", s[j].user_name, s[j].phone_number, s[j].balance, s[j].data);
	}
	fclose(p);
	fclose(temp);
	remove("users.bin");
	rename("temp.bin", "users.bin");
	FILE *pt = fopen("users.bin", "rb");
	FILE *ftemp = fopen("temp.bin", "wb");
	for (j = 0; j < size; j++)
	{
		if (s[i].phone_number == s[j].phone_number)
		{
			s[j].balance -= amount;
			printf("\nYour new balance is %f", s[i].balance);
			getch();
			system("cls");
		}
		fprintf(temp, "%s\t%ld\t%f\t%f\n", s[j].user_name, s[j].phone_number, s[j].balance, s[j].data);
	}
	fclose(pt);
	fclose(ftemp);
	remove("users.bin");
	rename("temp.bin", "users.bin");
	return 0;
	system("cls");
}
