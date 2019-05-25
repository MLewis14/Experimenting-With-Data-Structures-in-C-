#include <assert.h>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <list>
#include <vector>

#include "dlist.h"
#include "llist.h"

#define ARRSIZE 1000

template <class Iter>
void selectionSort(Iter, Iter);	// implement

int main(int argc, char** argv) {
    int num = 0;
	// generate random array
	srand (time(NULL));
	int arr[ARRSIZE];
	for (int i = 0; i < ARRSIZE; i++) {
		arr[i] = rand() % 100;
	}

	// vector
	std::vector<int> vec, vec2;
	for (int i = 0; i < ARRSIZE; i++) vec.push_back(arr[i]);
	vec2 = vec;
	selectionSort(vec.begin(), vec.end());

	// singly linked list
	List<int> lst;
	for (int i = 0; i < ARRSIZE; i++) lst.push_front(arr[i]);
	selectionSort(lst.begin(), lst.end());

	// doubly linked list
	DList<int> dlst;
	for (int i = 0; i < ARRSIZE; i++) dlst.push_front(arr[i]); //Fix push front
	for(auto DIT = dlst.begin(); DIT != dlst.end();++DIT){
	std::cout << "hello: " << *DIT << std::endl;
	num++;
	std::cout << num << " elements now." << std::endl;
	}
    selectionSort(dlst.begin(), dlst.end());

	// check sort
	std::sort(vec2.begin(), vec2.end());
	assert(vec==vec2);

	std::list<int> stlist;
	for (int i = 0; i < ARRSIZE; i++) { stlist.push_front(arr[i]); }
	stlist.sort();
	auto dit = dlst.begin();
	auto stlit = stlist.begin();
	while (dit != dlst.end() && stlit != stlist.end()) {
        std::cout << *dit << " and " << *stlit << std::endl;
		assert(*dit == *stlit);
		++dit; ++stlit;
	}
}

// TODO: fill in with selection sort implementation
template <class Iter>
void selectionSort(Iter begin, Iter end) {

    for(begin; begin != end; begin++){
        Iter lowestIndex = begin;
        Iter inLoop = begin;
        inLoop++;
        for(inLoop; inLoop != end; inLoop++){
            if(*inLoop < *lowestIndex){
                lowestIndex = inLoop;
            }
        }
        if(begin != lowestIndex){
            std::swap(*begin, *lowestIndex);
        }
    }
}
