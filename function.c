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



/********************************************************************************************************************
* Function: load_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/17/2023
* Description: This function loads data from csvfile into a data of struct, which is stored in doubled linked lists.
* Input parameters: infile: a pointer to the musicPlayList.csv file for reading what's inside of the file
*                           before loading it on the double linked lists.
*                   pList: a pointer to the header pointer of the linked list. Used double star signs, so that
*                          dereferencing the memory address value is possible. 
* Returns: Nothing
* Preconditions: musicPlayList.csv File must be opened successfully to read the csv data before implementing the function.
*********************************************************************************************************************/
void load_func(FILE* infile, Node** pList)
{

	if (infile != NULL) //csv file opened successfully
	{
		//Node* pPrev = NULL;
		//Node* pCur = *pList;

		int how_many_songs = 1;
		char line[200];
		char name_with_double_quotes[200];

		while (fgets(line, 200, infile) != NULL)
		{

			Node* pMem = malloc(sizeof(Node));

			if (pMem != NULL) //node created successfully
			{
				if (line[0] == '\"')
				{
					name_with_double_quotes[0] = '"';
					strcpy(&name_with_double_quotes[1], strtok(&line[1], "\""));

					for (int i = 0;; i++)
					{
						if (name_with_double_quotes[i] == '\0')
						{
							name_with_double_quotes[i] = '"';
							name_with_double_quotes[i + 1] = '\0';
							break;
						}
					}

					strcpy(pMem->data.artist, name_with_double_quotes);
					//strcpy(pMem->data.artist, strtok(&line[1], "\"")); //this would output withot double quotes
				}

				else if (line[0] != '\"')
				{
					strcpy(pMem->data.artist, strtok(line, ","));
				}
				//strtok returns char* //first filling out the data first!!
				//const char* last_name = strtok(line, "\n,\":"); //delimiter: \n , "
				//const char* first_name = strtok(NULL, "\n,\":");
				//strcat(last_name, first_name);                       //how can I ignore ,????????????????????
				//strcpy(pMem->data.artist, last_name);
				strcpy(pMem->data.album_title, strtok(NULL, "\n,:"));
				strcpy(pMem->data.song_title, strtok(NULL, "\n,:"));
				strcpy(pMem->data.genre, strtok(NULL, "\n,\":"));
				pMem->data.song_length.minutes = atoi(strtok(NULL, "\n,:"));
				pMem->data.song_length.seconds = atoi(strtok(NULL, "\n,:"));
				pMem->data.numbers_times_played = atoi(strtok(NULL, "\n,:"));
				pMem->data.rating = atoi(strtok(NULL, "\n,:"));

				pMem->pNext = NULL;
				pMem->pPrev = NULL; //now this node has two dangling pointers pointing to NULL
			}


			//insertion in the first nodetakes place!!!

			if (*pList == NULL) // if if there is no preexisting node inserting in the first position.
			{
				*pList = pMem;
			}

			else if (*pList != NULL) //inserting in the first position
			{
				pMem->pNext = *pList;
				(*pList)->pPrev = pMem;
				*pList = pMem;
			}

		}

		printf("\n\nAll the songs from the csvfile are loaded on the Digital Music Manager successfully!!");

		//this comment goes to the display function!!!
		//Node* pCur = *pList; //pcur pointing to the head pointer right now.

		//while (pCur != NULL)
		//{
		//	printf("*******************************Music %d*******************************\n\n", how_many_songs);
		//	printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
		//	printf("Album Title: %s\n", pCur->data.album_title);
		//	printf("Song Title: %s\n", pCur->data.song_title);
		//	printf("Genre: %s\n", pCur->data.genre);
		//	printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
		//	printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
		//	printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
		//	printf("Rating: %d\n\n", pCur->data.rating);
		//	printf("**********************************************************************\n\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n\n");

		//	how_many_songs++;
		//	pCur = pCur->pNext;

		//}

	}

	else if (infile == NULL) //file never opened
	{
		printf("\n\nError occured in uploading music file. Please doublecheck your file");
		return;
	}

}




/********************************************************************************************************************
* Function: display_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function displays what's loaded inside of the linked lists in two different ways.
*              (1): Priting all the records of songs on the playlist. (2): Printing all records that match an artist typed.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void display_func(Node* pList)
{
	int how_many_songs = 1;
	//Node* pCur = pList; //pcur pointing to the head pointer right now.
	int method_choice = 0;

	char artist_name[100];
	//char* artist_name = malloc(sizeof(char) * 100);

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist!");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	printf("\n\nFor display method, which one would you like to choose? Enter 1 or 2");
	printf("\n\n1. Print all records\n\n\n");
	printf("2. Print all records that match an artist\n\n");
	scanf(" %d", &method_choice);

	if (method_choice == 1)
	{
		system("cls");
		printf("\n\n\nChose Method 1: Print all records\n\n\n");

		printList(pList);

		printf("\n\n\nALright! These are all the songs displayed from the csv file!\n\n\n");

		return;
	}

	else if(method_choice == 2)
	{
		system("cls");
		printf("\n\n\nChose Method 2: Print all records that match an artist\n\n\n");
		
		search_func(pList, artist_name);
		
		printf("\n\n\nALright, the is the search result based on the song records from the csv file!\n\n\n");

		return;
	}
	
}




/********************************************************************************************************************
* Function: display_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function displays what's loaded inside of the linked lists in two different ways.
*              (1): Priting all the records of songs on the playlist. (2): Printing all records that match an artist typed.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void printList(Node* pList)
{
	Node* pCur = pList;
	int how_many_songs = 1;

	while (pCur != NULL)
	{
		printf("*******************************Music %d*******************************\n\n", how_many_songs);
		printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", pCur->data.album_title);
		printf("Song Title: %s\n", pCur->data.song_title);
		printf("Genre: %s\n", pCur->data.genre);
		printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
		printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
		printf("Rating: %d\n\n", pCur->data.rating);
		printf("**********************************************************************\n\n");
		printf("                                     :\n");
		printf("                                     :\n");
		printf("                                     :\n");
		printf("                                     :\n\n");

		how_many_songs++;
		pCur = pCur->pNext;

	}


}






/********************************************************************************************************************
* Function: search_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: THis function gives a search result of song based on the artist name from an user input.
*              Linked node pointer will traverse through each one untill the end of the node. In the meantime,
*              If the node pointer finds the match, this will printout what's stored in that particular node.
* Input parameters: pList: a pointer to the head node in the double linked lists.
*                   artist_name: This array accepts an array of chars based on the user input using fgets and stdin.
* Returns: This function returns the number of the songs found based on artist name match.
* Postconditions: If no song has been found in the list, this will print out "No songs found!".
*********************************************************************************************************************/
int search_func(Node* pList, char artist_name[100])
{

	Node* pCur = pList;
	int how_many_songs = 0;
	//char artist_name[100];
	printf("Type the name of the artist, whose songs from the Digital Music Manager\n");
	printf("\nLast name, First name order!!! Comma also matters!\n");

	
	printf("\n\nArtist name:");
	fgets(artist_name, 100, stdin);
	fgets(artist_name, 100, stdin);

	for (int i = 0;; i++) 
	//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
	{
		if (artist_name[i] == '\n') //\n must right before the null terminator added by the fgets!
		{
			artist_name[i] = '\0';
			break;
		}
	}

	printf("\nSearching for: %s\n\n", artist_name);
	
	//char* artist_name = malloc(sizeof(char) * 100);
	//printf("\n\nArtis name: ");
	//scanf("%99[^\n]", artist_name);
	//printf("\n\nSearching for: %s\n", artist_name);

	while (pCur != NULL)
	{

		if (strcmp(pCur->data.artist, artist_name) == 0)  //gotta initialize this!!! by *pCur = pList;
		{
			how_many_songs++; //here so that first song index will be 1 instead of 0
			printf("*******************************Music %d*******************************\n\n", how_many_songs);
			printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
			printf("Album Title: %s\n", pCur->data.album_title);
			printf("Song Title: %s\n", pCur->data.song_title);
			printf("Genre: %s\n", pCur->data.genre);
			printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
			printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
			printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
			printf("Rating: %d\n\n", pCur->data.rating);
			printf("**********************************************************************\n\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n\n");
			//how_many_songs++;
			//pCur = pCur->pNext; //I cannot put it here! otherwise the loop never ends without traversign
			//if the first node doesn't match with the name.
		}

		pCur = pCur->pNext;

	}

	if (how_many_songs == 0) printf("\n\nNo songs found!");

	return how_many_songs;
}







/********************************************************************************************************************
* Function: store_func()
* Date Created: 9/17/2023
* Date Last Modified: 9/18/2023
* Description: This function will store all records of the songs that have been edited up to date on the playlist
*              into the outfile csv file named musicPlaylist.
* Input parameters: outfile: a output file pointer to the musicPlayList.csv in the writing mode.
*                   pList: a pointer to the head node in the double linked lists.        
* Returns: Nothing
* Preconditions: musicPlayList.csv file in the writing mode must be opened, so that what's inside of the doubled linked list
*                can be stored in the csv file through the stream.
* Postcondtions: musicPlayList.csv file in the writing mode must be closed to get access to the output.
*********************************************************************************************************************/
void store_func(FILE* outfile, Node* pList)
{
	//FILE* outfile = fopen("musicPlayList.csv", "w"); //I took it out to the main

	Node* pCur = pList;

	char integer_to_string[10];

	while (pCur != NULL)
	{
		fputs(pCur->data.artist, outfile);
		fputc(',', outfile);
		fputs(pCur->data.album_title, outfile);
		fputc(',', outfile);
		fputs(pCur->data.song_title, outfile);
		fputc(',', outfile);
		fputs(pCur->data.genre, outfile);
		fputc(',', outfile);
		//Why _itoa not working?????
		_itoa(pCur->data.song_length.minutes, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(':', outfile);
		_itoa(pCur->data.song_length.seconds, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(',', outfile);
		_itoa(pCur->data.numbers_times_played, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(',', outfile);
		_itoa(pCur->data.rating, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc('\n', outfile);


		pCur = pCur->pNext;
	}

	//fclose(outfile);  //I took it out to the main

	return;
}





/********************************************************************************************************************
* Function: edit_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function makes an user able to modify all attributes of a certain song searched by the user input.
*              After the modification, the edited values will replaced the old ones in the node of the field Record Struct.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void edit_func(Node* pList)
{
	Node* count_ptr = pList;
	int how_many_songs_found = 0;
	char song_search[100] = "";
	Node* search_ptr = pList;
	int new_rating = 0;
	bool again = false;

	char edited_artist[50] = "";
	char edited_album_title[50] = "";
	char edited_song_title[50] = "";
	char edited_genre[20] = "";
	int edited_song_length_minutes = 0; //struct duration song_length; ?? what's the difference??
	int edited_song_length_seconds = 0;
	int edited_numbers_times_played = 0;
	int edited_rating = 0; // 1 ~ 5

	char artist_name[100];

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist! for rating");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	else if (pList != NULL) //songs loaded
	{
		how_many_songs_found = search_func(pList, artist_name);

		if (how_many_songs_found == 0)
		{
			printf("\n\nNo songs found matched with the name. Make sure to check the name of the song! before rating");
			return;
		}

		printf("\nALright this is the result we found for you!");


		if (how_many_songs_found != 1) // at least more than one song from the same artist
		{
			printf("\nWe found more than one song from the same artist!");
			printf("\nWhich song would you like to choose for editing the rating?");

			printf("\n\nType the song name:\n");
			fgets(song_search, 100, stdin);
			//fgets(song_search, 100, stdin); //only one line of fgets needed.

			for (int i = 0;; i++)
				//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
			{
				if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
				{
					song_search[i] = '\0';
					break;
				}
			}

			while (strcmp(search_ptr->data.song_title, song_search) != 0)
			{
				search_ptr = search_ptr->pNext;
			}

		}

		//now search ptr currently pointing to the first node, need to get it to  move!
		while (strcmp(search_ptr->data.artist, artist_name) != 0)
		{
			search_ptr = search_ptr->pNext;
		}

		system("cls");
		printf("\n\nWe found the song match!\n\n");
		printf("\n\nThis is the record information within the manager device for this song\n\n");


		printf("**********************************************************************\n\n");
		printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", search_ptr->data.album_title);
		printf("Song Title: %s\n", search_ptr->data.song_title);
		printf("Genre: %s\n", search_ptr->data.genre);
		printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
		printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
		printf("Rating: %d\n\n", search_ptr->data.rating);
		printf("**********************************************************************\n\n");


		///////////editing takes place
		printf("\nCurrent Artist: %s", search_ptr->data.artist);
		printf("\n\nPlease type an edited artist:");
		fgets(edited_artist, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_artist[i] == '\n')
			{
				edited_artist[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.artist, edited_artist);
		printf("\nEdited Artist: %s\n\n\n", search_ptr->data.artist);


		printf("\nCurrent Album Title: %s", search_ptr->data.album_title);
		printf("\n\nPlease type an edited album title:");
		fgets(edited_album_title, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_album_title[i] == '\n')
			{
				edited_album_title[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.album_title, edited_album_title);
		printf("\nEdited Album Title: %s\n\n\n", search_ptr->data.album_title);

		printf("\nCurrent Song Title: %s", search_ptr->data.song_title);
		printf("\n\nPlease type an edited song title:");
		fgets(edited_song_title, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_song_title[i] == '\n')
			{
				edited_song_title[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.song_title, edited_song_title);
		printf("\nEdited Song Title: %s\n\n\n", search_ptr->data.song_title);

		printf("\nCurrent Genre: %s", search_ptr->data.genre);
		printf("\n\nPlease type an edited genre:");
		fgets(edited_genre, 20, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_genre[i] == '\n')
			{
				edited_genre[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.genre, edited_genre);
		printf("\nEdited Genre: %s\n\n\n", search_ptr->data.genre);

		printf("\nCurrent Song Minutes: %d", search_ptr->data.song_length.minutes);
		printf("\n\nPleas type an edited song minute:");
		scanf("%d", &edited_song_length_minutes);
		search_ptr->data.song_length.minutes = edited_song_length_minutes;
		printf("\nEdited Song Minutes: %d\n\n\n", search_ptr->data.song_length.minutes);

		printf("\nCurrent Song Seconds: %d", search_ptr->data.song_length.seconds);
		printf("\n\nPleas type an edited song seconds:");
		scanf("%d", &edited_song_length_seconds);
		search_ptr->data.song_length.seconds = edited_song_length_seconds;
		printf("\nEdited Song Seconds: %d\n\n\n", search_ptr->data.song_length.seconds);
		
		printf("\nCurrent Number Times Played: %d", search_ptr->data.numbers_times_played);
		printf("\n\nPleas type an edited numbers times played:");
		scanf("%d", &edited_numbers_times_played);
		search_ptr->data.numbers_times_played = edited_numbers_times_played;
		printf("\nEdited Number Times Played: %d", edited_numbers_times_played);

		do
		{
			again = false;
			printf("\nCurrent Rating: %d", search_ptr->data.rating);
			printf("\n\nPleas type an edited rating:");
			scanf("%d", &edited_rating);

			if (edited_rating == 1 || edited_rating == 2 || edited_rating == 3 ||
				edited_rating == 4 || edited_rating == 5)
			{
				again = false;
				search_ptr->data.rating = edited_rating;
				printf("\nEdited Rating: %d", edited_rating);

			}

			else
			{
				again = true;
				printf("\n\nInvalid Rating! The rating number ranges from 1 to 5! Please type your rating again!");
			}
		} while (again == true);
		

		//what's the whole point of making the rating function?????????????????????????????


		printf("\n\n\n\n\nTHis is the edited version for this song!\n\n");
		printf("**********************************************************************\n\n");
		printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", search_ptr->data.album_title);
		printf("Song Title: %s\n", search_ptr->data.song_title);
		printf("Genre: %s\n", search_ptr->data.genre);
		printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
		printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
		printf("Rating: %d\n\n", search_ptr->data.rating);
		printf("**********************************************************************\n\n");



		return;
	}
}


/********************************************************************************************************************
* Function: rate_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function enables an user to exaclusively access to the rating of the song selected from user input
*              and modifies the current rating. Then, the updated rating replaces old value in the node of the 
*              field Record Struct.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void rate_func(Node* pList)
{

	Node* count_ptr = pList;
	int how_many_songs_found = 0;
	char song_search[100];
	Node* search_ptr = pList;
	Node* another_search_ptr = pList;
	int new_rating = 0;
	bool again = false;
	char artist_name[100];

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist! for rating");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	else if (pList != NULL) //songs loaded
	{
		how_many_songs_found = search_func(pList, artist_name);

		if (how_many_songs_found == 0)
		{
			printf("\n\nNo songs found matched with the name. Make sure to check the name of the song! before rating");
			return;
		}

		printf("\nALright this is the result we found for you!");

		/*while (count_ptr != NULL)
		{
			how_many_songs_found++;
			count_ptr = pList->pNext;
		}*/

		if (how_many_songs_found != 1) // at least more than one song from the same artist
		{
			printf("\nWe found more than one song from the same artist!");
			printf("\nWhich song would you like to choose for editing the rating?");

			printf("\n\nType the song name:");
			fgets(song_search, 100, stdin);
			//fgets(song_search, 100, stdin); why is it here only one line of fgets needed!!??????????????????????

			for (int i = 0;; i++)
				//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
			{
				if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
				{
					song_search[i] = '\0';
					break;
				}
			}

			while (strcmp(another_search_ptr->data.song_title, song_search) != 0)
			{
				another_search_ptr = another_search_ptr->pNext;
			}

			search_ptr = another_search_ptr;
		}


		//now search ptr currently pointing to the first node, need to get it to  move!
		while (strcmp(search_ptr->data.artist, artist_name) != 0)
		{
			search_ptr = search_ptr->pNext;
		}


			printf("\nSearched the song named: %s", search_ptr->data.song_title);
			printf("\nCurrent Rating for this song: %d", search_ptr->data.rating);
		
			do
			{
				printf("\n\nWhich new rating would you like to give to this song?: ");
				scanf("%d", &new_rating);

				if (new_rating == 1 || new_rating == 2 || new_rating == 3 ||
					new_rating == 4 || new_rating == 5)
				{
					again = false;
					search_ptr->data.rating = new_rating;
					printf("\n\nNew rating for the song named  %s: %d", search_ptr->data.song_title, new_rating);
				}

				else
				{
					printf("\nRating ranges from 1 to 5 Please type your rating again!\n");
					again = true;
				}


			} while (again == true);
		
	}
}



/********************************************************************************************************************
* Function: play_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/17/2023
* Description: This function lets an user decide which song to start from on the playlist. Based on the order of the 
*              double linked nodes, the starting pointer to the node will traver through each node all the way to the
*              end of the linked list.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void play_func(Node* pList)
{
	Node* search_ptr = pList;
	char song_search[100];
	//Node* search_ptr = pList;

	printf("\nPlaying music on your list!!");
	printf("\n\nWhich song do you want to start playinf on the list?: ");
	printf("\n\nSong name:");
	fgets(song_search, 100, stdin);
	fgets(song_search, 100, stdin); //here two lines of fgets needed!!!

	for (int i = 0;; i++)
		//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
	{
		if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
		{
			song_search[i] = '\0';
			break;
		}
	}

	while (strcmp(search_ptr->data.song_title, song_search) != 0) //not found the match
	{
		if (search_ptr->pNext == NULL) //pointing to the last song but still a mismatch of the song.
		{
			printf("\nThe song not found on the playlist");
			return;
		}
		search_ptr = search_ptr->pNext;
	}

	printf("\n\nPlaying the music list starting from %s", search_ptr->data.song_title); //found the song

	while (search_ptr != NULL) //song will be played until the end of the playlist
	{

			printf("\n\n**********************Currently Playing the song************************\n\n");
			printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
			printf("Album Title: %s\n", search_ptr->data.album_title);
			printf("Song Title: %s\n", search_ptr->data.song_title);
			printf("Genre: %s\n", search_ptr->data.genre);
			printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
			printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
			printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
			printf("Rating: %d\n\n", search_ptr->data.rating);
			printf("**********************************************************************\n\n");
			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n\n");

			search_ptr = search_ptr->pNext;

			Sleep(3000);
			system("cls");

	}

	printf("\n\nThe end of the song playlist!");

}






/********************************************************************************************************************
* Function: exit_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/15/2023
* Description: This function lets an user terminate the Digital Music Manager program successfully.
* Input parameters: exit: a boolean data type variable to indicate whether to exit or not to the exit function.
* Returns: This function returns boolean values if it returns true, this will end the Digital Music Manager program.
*********************************************************************************************************************/
bool exit_func(bool exit)
{
	int yes_or_no = 0;
	int invalid_input = 0;

	do
	{
		invalid_input = 0;
		system("cls");
		printf("\n\nAre you sure you want to exit? Enter 1 if yes enter 2 otherwise");
		printf("\n\n(1): Yes        (2): No\n\n");
		scanf(" %d", &yes_or_no); 

		if (yes_or_no == 1)
		{
			printf("\n\nSee you next time!!!");
			exit = true;
			return exit;
		}

		else if (yes_or_no == 2)
		{
			system("cls");
			exit = false;
			return exit;
		}

		else
		{
			printf("\n\nMake sure to enter either 1 or 2!\n\n");
			system("pause");
			invalid_input = 1;

		}

	} while (invalid_input == 1);

}

