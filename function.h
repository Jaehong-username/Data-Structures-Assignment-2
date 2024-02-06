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


#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include <windows.h>

typedef struct duration
{
	int seconds;
	int minutes;

} Duration;


typedef struct record
{
	char artist[50];
	char album_title[50];
	char song_title[50];
	char genre[20];
	Duration song_length; //struct duration song_length; ?? what's the difference??
	int numbers_times_played;
	int rating; // 1 ~ 5

} Record;

typedef struct node
{
	Record data;
	struct node* pNext;  //vs Node* pNext;
	struct node* pPrev;  //vs Node* pPrev;

} Node;


void load_func(FILE* infile, Node** pList);

void display_func(Node* pList);

void printList(Node* pList);

int search_func(Node* pList, char artist_name[100]);

void store_func(FILE* outfile, Node* pList);

void edit_func(Node* pList);

void rate_func(Node* pList);

void play_func(Node* pList);

bool exit_func(bool exit);

#endif
