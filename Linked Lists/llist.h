#ifndef LLIST_H
#define LLIST_H

#include <iterator>

template <class T>
class List {
	struct Node {
		T data;
		Node* next;
		Node(const T& x, Node* y = NULL) : data(x), next(y) {}
	};

	Node* head;

	public:

	class iterator {
		Node* nd;

		public:
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		friend class List;		// List objects have access to private members of List::iterator.

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

	List() : head(NULL) {}
	~List() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	bool empty() { return !head; }

	void push_front(const T& x) {
		Node* nd = new Node(x);
		nd->next = head;
		head = nd;
	}

	void pop_front() {
		if (head) {
			Node* nd = head->next;
			delete head;
			head = nd;
		}
	}

	void insert(const iterator position, const T& val) {
		Node* nd = new Node(val, position.nd);	// new node's next will be position's node

		if (head == position.nd) head = nd;
		else {
			Node* pnd = head;
			while (pnd && pnd->next != position.nd) pnd = pnd->next;
			pnd->next = nd;
		}
	}

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(NULL); }
};	// end list


#endif
