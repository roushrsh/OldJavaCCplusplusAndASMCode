//Soroush Hajizadeh
//SENG 265
//UVIC October 2015
////////////////////////////////////



#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_set.h"

using namespace std;

string_set::string_set() {		 			//constructor, create/declare the hash table, make each value null, create iterator_index and node
	iterator_index = 0;
	iterator_node = NULL;
		for (int i = 0; i < HASH_TABLE_SIZE; i++){	//give the NULL value /initate the table
			hash_table[i] = NULL;
	}
}

void string_set::add(const char *s) {				//adds given node(containing s) to hash table. If it i
		if (contains(s) == 1){
			throw duplicate_exception{};		//If s is already present, it throws a duplicate exception
		}
		int location = hash_function(s);
		node *x = new node;
		x->s = new char[strlen(s)+1];			//create new string of length+1
		strcpy(x->s, s);				//copy desired input s into the string
		x->next = hash_table[location];			//push into the table
		hash_table[location] = x;
		reset();
}

void string_set::remove(const char *s) { //removes a specific node (containing s) from the list and rellocates location/space as needed
		if (contains(s) == 0){
			throw not_found_exception{};
		}

	int location = hash_function(s);
	node* curr = hash_table[location];			//declaring curr and prev to help travers through later
	node* prev = NULL;


	if ( (strcmp(hash_table[location]->s, s) == 0) && (hash_table[location]->next == NULL) ){  	// When the table head itself is equal to the desired value S, and the next is null
	hash_table[location] = NULL;									// simply make whole array null
	return;
	}

	if ( (strcmp(hash_table[location]->s, s) == 0) && (hash_table[location]->next != NULL) ){	//when the table head itself has the desired value s, and the next is not null
	hash_table[location] = curr->next;
	delete curr;
	}

	while (curr->next != NULL){		//for all cases where the array contains the desired value however it is not in the head
		prev = curr;
		curr = curr->next;

		if(strcmp(curr->s,s) == 0){		//all cases when not head nor end
			if(curr->next != NULL){
				prev->next = curr->next;
				delete curr;
			}else{					//specifically for when it is the last node
			prev->next = NULL;
			}
		}
	}
reset();
}

int string_set::contains(const char *s) { // Looks for and returns 1(true) if it finds a desired value S value, or 0(false) if not

	 for (node *p = hash_table[hash_function(s)]; p != NULL; p = p->next){
		if (strcmp(s, p->s) == 0){
			return 1;
		}
	}
	return 0;
}

void string_set::reset() { // Resets the iterator to the first element. Always occurs after add and remove. Needed for next to function properly aswell
	iterator_index = 0;
	iterator_node = NULL;
}

const char *string_set::next() {	//returns the next available string, or NULL if none remain. Going through the hash table top to down

	if (iterator_index > HASH_TABLE_SIZE -1){	//to not overshoot array, as it is 100, but goes from 0 to 99
		return NULL;
	}

	node *hold = new node;

	while (iterator_index < HASH_TABLE_SIZE){

		if (iterator_node == NULL){			//skip over when the node it empty
			iterator_index++;
			iterator_node = hash_table[iterator_index];
			continue;
		}
		if ((iterator_node->next != NULL) || (iterator_node != NULL)){  // if either the next node is not NULL or node itself is not null

			hold->s = iterator_node->s; 			//hold the value

			if(iterator_node -> next == NULL){			//only in case where node itself isn't null but the next one is
				iterator_index++;
				iterator_node = hash_table[iterator_index];
				return hold->s;
			}

			iterator_node = iterator_node -> next;			//for the case where the next node isn't null
			return hold->s;
		}
	}
return NULL;

}

string_set::~string_set() {
			// the deconstructor for the array, runs through and deletes every value to reset it to be like its original position. Delete dynamic storage allocated for nodes and strings.
	node *curr;
	node *next;
		for(int i = 0; i <HASH_TABLE_SIZE; i++){		//scan through
		curr = hash_table[i];
			while(curr != NULL){
				next = curr->next;
				delete curr;				//delete nodes
				curr = next;
			}
			hash_table[i] = NULL; 			//return table to original

		}

	for(int i = 0; i<HASH_TABLE_SIZE; i++){    		//can be run if you'd like to open all memory after, rather than return array to NULL state;
	delete hash_table[i];
	}
}

int string_set::hash_function(const char *s) { 		//calculates position in hash table from string by taking numerical value of letters and modding it by the index size
	reset();
	int i = 0;
	while (s[i] != '\0'){
		iterator_index = (iterator_index + s[i])%(HASH_TABLE_SIZE); 		//actual calculation taking place after each addition to remain within range
		i++;
	}
	return iterator_index;

}
