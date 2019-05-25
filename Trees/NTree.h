// author: levitan

#ifndef NTREE_H
#define NTREE_H

#include <assert.h>
#include <list>
#include <map>
#include <numeric>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

namespace std {
	std::string to_string(const std::string& str) { return str; }
}

template <class T>
class NTree {
	struct tnode {
		T data;
		tnode* parent;
		std::vector<tnode*> children;

		tnode (T x) : data(x), parent(NULL) {}

		void addChild(tnode* c) { children.push_back(c); }
	};

	tnode* root;

	// recursive private method called by >> operator
	std::queue<std::string> toStrings(tnode* nd) const {
		std::queue<std::string> rq;
		if (!nd) {	// base case: empty child: return empty vector
			return rq;
		}
		if (nd->children.size()==0) {	// base case: leaf: return vector with just that node's value
			rq.push(std::to_string(nd->data));
			return rq;
		}

		// get queue of strings representing each subtree
		std::vector<std::queue<std::string> > subtrees;
		for (tnode* c : nd->children) {
			subtrees.push_back(toStrings(c));
		}

		// add current value to return queue (will be at front)
		// pad to width of the next level
		int stringWidth = 0;
		int maxDepth = 0;
		for (auto st : subtrees) {
			stringWidth += st.front().length();
			maxDepth = std::max(maxDepth, (int)st.size());
		}
		int levelpad = (stringWidth + subtrees.size() - 1 - std::to_string(nd->data).length())/2;
		rq.push(std::string(levelpad, '_') + std::to_string(nd->data) +
				std::string(levelpad, '_'));

		// add space-padded string(s) to subtrees with fewer levels than max
		for (auto& st : subtrees) {
			int width = st.front().length();
			while (st.size() < maxDepth) {
				st.push(std::string(width, '_'));
			}
		}

		// combine subtrees at each level
		while (!subtrees.front().empty()) {		// all subtrees now have same depth
			std::vector<std::string> levelstrings;	// hold strings at this level
			for (auto& st : subtrees) {
				levelstrings.push_back(st.front());
				st.pop();
			}

			// levelstrings now contains string from each subtree
			// combine into single string and add to rq
			std::string levelstr = std::accumulate(levelstrings.begin(),
					levelstrings.end(), std::string(),
					[](const std::string& a, const std::string& b) -> std::string {
							return a + (a.length() > 0 ? " " : "") + b;
					});
			rq.push(levelstr);

		}	// iterate to next level

		// all subtrees have been processed
		return rq;
	}

	std::string toString(tnode* nd) const {
		std::queue<std::string> q = toStrings(nd);
		std::string str;
		while (!q.empty()) {
			str += (q.front() + "\n");
			q.pop();
		}
		return str;
	}

	public:
	NTree() : root(NULL) {}

	NTree(const std::vector<T>& values, const std::vector<int>& parents) {
		if (values.size() != parents.size()) {
			std::cout << "Error: values has " << values.size() << " elements and parents has " << parents.size() << " elements.\n";
			throw std::exception();
		}

		std::map<T, tnode*> valmap;	// will map values to node addresses
		for (int i = 0; i < values.size(); i++) {
			tnode* nd = new tnode(values[i]);
			valmap[values[i]] = nd;
			if (parents[i] >= 0) {		// -1 signals root
				nd->parent = valmap[values[parents[i]]];
				nd->parent->addChild(nd);
			}
			else root = nd;
		}

	}

	~NTree() {
		if (!root) return;
		std::queue<tnode*> q;
		q.push(root);

		while (!q.empty()) {
			tnode* nd = q.front();
			q.pop();
			for (tnode* c : nd->children) q.push(c);
			delete nd;
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const NTree& tree) {
		stream << tree.toString(tree.root);
		return stream;
	}

	// TODO: replace dummy return value with test for equality
	bool operator==(const NTree<T>& rhs) {
		return true;
	}

	// TODO: implement method to write tree in recoverable format to file
	void serialize(const std::string& filename) {
	    std::ofstream outfile;
	    outfile.open(filename);

        subSerialize(outfile, root);

        outfile.close();
    }
	// TODO: implement method to read tree in from file
	void deserialize(const std::string& filename) {
        std::ifstream infile;
        infile.open(filename);

        std::string input;
        T value;
        infile >> input;
        std::cout << input << std::endl;
        std::istringstream(input) >> value;

        tnode* newNode = new tnode(value);
        root = newNode;
        //infile >> root->data;
        subDeserialize(infile, root);

        infile.close();
	}
//Recursive serialization to file
	void subSerialize(std::ofstream &outfile, tnode* currNode){
	    if(!currNode){ //checks if current node exists
            outfile << "Null \t";
            return;
	    }
	    else if(currNode){
            outfile << currNode->data << "\t"; //outputs node data with a space
            if(currNode->children.size() > 0){ //outputs each child of this current node
                for(int a = 0; a < currNode->children.size(); a++){
                    subSerialize(outfile, currNode->children[a]);
                }
            }
            else if(currNode->children.size() == 0){ //otherwise output that the node has no children
                outfile << "Null \t";
            }
	    }
	    return;
	}

	void subDeserialize(std::ifstream &infile, tnode*& currNode){
        std::string node; //take in a nodes data as a string
        infile >> node;

        if(infile.eof()) return; //check if end of file

        if(node == "Null"){
            currNode = currNode->parent; //If there is no child node, subserialize on the parent once again for possible children
            std::cout << "No kids" << std::endl;
            subDeserialize(infile, currNode);
            return;
        }
        else{
            T val;
            std::istringstream(node) >> val; //parse the string for data of a primitive type, convert it to the templated type
            std::cout << val << std::endl;
            tnode* newNode = new tnode(val); //create a new node and link it to it's parent, and vice versa
            newNode->parent = currNode;
            currNode->addChild(newNode);
            currNode = newNode;

            subDeserialize(infile, currNode); //serialize on the new child, goes left to right
        }
        return;
	}

};

#endif
