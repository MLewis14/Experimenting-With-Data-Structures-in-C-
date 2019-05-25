// author: levitan
// Program #3 main for testing
// do not modify

#include <iostream>
#include <vector>

#include "NTree.h"

int main(int argc, char** argv) {
	std::vector<std::string> values = {"Food", "Plant", "Animal", "Roots", "Leaves", "Fruits", "Fish", "Mammals", "Birds", "Potatoes", "Carrots", "Lettuce", "Cabbage", "Apples", "Pears", "Plums", "Oranges", "Salmon", "Tuna", "Beef", "Lamb", "Chicken", "Duck", "Wild", "Farm", "GrannySmith", "Gala" };
	std::vector<int> parents = {-1, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 17, 17, 13, 13 };
	NTree<std::string> foodtree(values, parents);
	std::cout << foodtree;

	// serialize method should write foodtree to foodtree.out
	foodtree.serialize("foodtree.out");

	// default constructor creates empty tree
	NTree<std::string> foodtree2;
	// foodtree2 should be come the tree deserialized from filepath
	foodtree2.deserialize("foodtree.out");

	// overload equality operator
	assert(foodtree==foodtree2);

	// everything you write must work on all types of T
	std::vector<int> intvalues = { 9, 6, 5, 4, 2, 10, 7, 1, 3, 8, 11, 12, 13, 14 };
	std::vector<int> intparents = { -1, 0, 1, 1, 1, 2, 2, 2, 3, 3, 8, 8, 8, 8 };
	NTree<int> inttree(intvalues, intparents);
	std::cout << inttree;

	NTree<int> inttree2;
	inttree.serialize("inttree.out");
	inttree2.deserialize("inttree.out");
	assert(inttree==inttree2);

}
