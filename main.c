/******************************************************************************************************************
* Programmer: Jaehong Lee
* Class: CptS 122, Fall 2023; Lab Section 3 (Tuesday 1:30PM - 4:20PM)
* Programming Assignment: PA2
* Date: September 19, 2023
* Description: This PA assignment is creating a Digital Music Manager program. The data of song is stored
* in double-linked lists copied over from musicPlayList.csv. Depending on which menu selected, this program
* will implement function micmicking following menus: load, store, display, insert, delete, edit, sort
* rate, play, shuffle, exit. After the device runs a certain menu function, it will return back to
* the main menu display, unless you exited out of the main menu by entering 11.
******************************************************************************************************************/


#include "function.h"


int main(void)
{
	//Enter you clicked right before running into fgets func. '\n' automatically filled in fgets that's why
	// it does not wait for the user input. simply way of solving this issue.
	//char testing_line[10];
	//printf("\nEnter a string input: ");
	//fgets(testing_line, 100, stdin);
	//printf("\n\nString output %s\n", testing_line);
	//putchar('\n');
	//system("pause");

	int menu = 0;
	bool exit = false;;
	FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pList = NULL; //head ptr initially pointing to NULL
	Record music;

	do
	{
		printf("\n\n*********************************************************\n\n");
		printf("\n\nWelcome to the Digital Music Manager!!");
		printf("\n\n\nMenu of options:\n\n"); //PA2
		printf("(1) load\n"); //pa2
		printf("(2) store\n"); //pa2
		printf("(3) display\n"); //pa2
		printf("(4) insert\n");
		printf("(5) delete\n");
		printf("(6) edit\n"); //pa2
		printf("(7) sort\n");
		printf("(8) rate\n"); //pa2
		printf("(9) play\n"); //pa2
		printf("(10) shuffle\n");
		printf("(11) exit\n"); //pa2
		printf("\n\n*********************************************************\n\n");
		printf("Enter the number 1 ~ 11 to run your music manager device: ");
		scanf("%d", &menu);



		switch (menu)
		{
		case 1:
			system("cls");
			load_func(infile, &pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 2:
			system("cls");
			FILE* outfile = fopen("musicPlayList.csv", "w"); //writing mode!
			store_func(outfile, pList);
			fclose(outfile);
			printf("\nThe updated Music Playlisted stored on the musicPlayList.csv file complete!");
			system("pause");
			system("cls");
			break;

		case 3:
			system("cls");
			display_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 4: //For the next PA assignment
			break;

		case 5: //For the next PA assignment
			break;

		case 6: 
			system("cls");
			edit_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 7: //For the next PA assignment
			break;

		case 8:
			system("cls");
			rate_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 9:
			system("cls");
			play_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 10: //For the next PA assignment
			break;

		case 11:
			exit = exit_func(exit);
			break;

		}

	} while (!exit);

	fclose(infile); 


	return 0;
}