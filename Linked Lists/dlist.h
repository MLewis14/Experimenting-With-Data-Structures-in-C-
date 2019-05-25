#ifndef DLIST_H
#define DLIST_H

#include <iterator>

template <class T>
class DList {
	struct Node {
		T data;
		Node* next;
		Node* previous;
		Node(const T& x, Node* y = NULL) : data(x), next(y), previous(NULL) {}		// TODO
	};

	Node* head; //Pointer to Null Dummy Node at start of DList
	Node* tail; //Pointer to Null Dummy Node at end of Dlist

	public:

	class iterator {
		Node* nd;

		public:
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		friend class DList;		// List objects have access to private members of List::iterator.

		// constructors
		inline iterator(Node* x=NULL) : nd(x) {}	// construct from node pointer
		inline iterator(const iterator& x) : nd(x.nd) {}	// construct from another iterator

		// operator overloads
		inline iterator& operator=(const iterator& x) {
			nd = x.nd;
			return *this;
		}	// assignment

		inline iterator& operator++() {
			nd = nd->next;
			return *this;
		}	// prefix increment

		inline iterator operator++(int) {
			iterator tmp(*this);	// make copy of current iterator for return
			nd = nd->next;				// advance current iterator
			return tmp;
		}	// postfix increment

		inline T& operator*() const { return nd->data; }	// dereference

		inline bool operator==(const iterator& x) const {
			return nd == x.nd;
		}	// equal

		inline bool operator !=(const iterator& x) const {
			return nd != x.nd;
		}	// not equal
	};		// end iterator

	DList(){
	    head = new Node(NULL);  //Create a new dummy node header
	    tail = new Node(NULL);  //Create a new dummy node tail
	}		// TODO: header node should be allocated and linked to itself
	~DList() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	// TODO: with sentinel node, head is never null
	bool empty() { return !head->next; }

	// TODO: with sentinel node, head always stays the same. Links: link head to new first node, new first node to head, new first node to former first node, former first node to new first node.
	void push_front(const T& x) {
		Node* nd = new Node(x);

		if(head->next == NULL){
            nd->next = tail; //Node next now points to the end of the DList
            nd->previous = head; //Node previous now points to head of DList
            head->next = nd; //Head now points to the first Node
            tail->previous = nd; //Tail previous now points to last element in DList
		}
		else if(head->next){ //If a first Node is currently present
            nd->next = head->next; //New first node's next is now the former first node
            nd->next->previous = nd; //Former first node's previous is now new First node
            nd->previous = head; //New first node's previous is now head
            head->next = nd; //Head now points to new First Node
		}

	}

	// TODO: with sentinel node, head always exists. Links: link head to *second* node, and link second node to head.
	void pop_front() {
       ;

        if(head->next == tail->previous){ //Checks if this is last element in DList
            std::cout << "Deleting element: " << head->next->data << std::endl;
            delete head->next; //Deletes first element in DList
            head->next = NULL; //Eliminates dangling pointer
        }
        else{
            head->next = head->next->next; //Points head->next to second Node
            std::cout << "Deleting element: " << head->next->previous->data << std::endl;
            delete head->next->previous; //Deletes former first node
            head->next->previous = head; //New first Node's previous now points to head
        }

	}

	// TODO: with sentinel node, head never changes. With prev links, don't need to search list for node before position. Four links. //Edit
	void insert(const iterator position, const T& val) {
		Node* nd = new Node(val, position.nd);	// new node's next will be position's node

		nd->previous = position->nd->previous; //Link new node to former nodes previous node
		position->nd->previous->next = nd; //Link former nodes previous node to the new node
		position->nd->previous = nd; //Links former nodes previous to new node
	}

	// TODO: fill in - Has been filled
	void erase(const iterator position) {
	    Node* temp = position.nd.previous; //Points to node behind position
	    temp->next = position.nd.next;     //Sets previous Node's next to the Node in front of position
	    position.nd.next.previous = temp;  //Sets next Node's previous to the Node behind position
	    std::cout << "Deleting element: " << position.nd.data << std::endl;
	    delete position.nd;
	}

	// TODO: with sentinel node, head is not the first valid node, and null is not one past the last valid node
	iterator begin() { return iterator(head->next); } //Points to the first Node with value after head
	iterator end() { return iterator(tail); } //Points to the Null dummy Node tail - right after last element
};	// end list


#endif
