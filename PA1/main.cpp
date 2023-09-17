/*  ADVANTAGES / DISADVANTAGES LINKED LIST:
	
	An advantage to using a linked list is inserting in O(1) time. 
	In the assignment, I insert to the linked list at the end using
	a pointer to the last node, making it constant time. 
	A disadvantage to using a linked list 

	A disadvantage to using linked lists is it's harder to immediately
	seach for an index. Instead of searching for a specific index, I
	have to use a pointer and use a loop to get to the profile I want


	ADVANTAGES/DISADVANTAGES ARRAY:
	An advantage to using arrays is the ability to use indexes. If
	I wanted to find a specific profile in the array, I could get the
	index and keep track of the index

	A disadvantage to using an array is having to move all other array 
	members when inserting. I had to move all other profiles to insert
	a profile in the front of the array.

*/

#include "Game.h"

int main(void) {

	Game<std::string, std::string> newGame;

	return 0;
}