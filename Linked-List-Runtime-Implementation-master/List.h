#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
using namespace std;


template <typename T>
class List
{
  private:

    // struct for singly-linked list nodes
    struct Node
    {
      T      data;
      Node   *next;

      Node( const T & d = T{}, Node * n = nullptr)
        : data{ d },  next{ n } { }

    };


  public:
    // constructors
    List( ) {
      init( );
    }

    ~List( ) {
      clear( );
    }
    /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     * (since the exposure to C++ is pretty variable it seems -- some students
     * having taken 141 before last semester; some students coming from 107,
     * etc.)
     */


    /**
     * function: clear
     * desc:  makes the calling list empty (but the list still
     *        exists).
     */
    void clear(){
      Node * p = front;
      Node *pnext;

      while(p != nullptr) {
        pnext = p->next;
        delete p;
        p = pnext;
      }
      front = back = nullptr;
    }





    /**
     * TODO
     *
     * function: length
     * desc:  returns the length of the calling list
     *
     * REQUIREMENTS:  this is a working implementation, but
     *   it takes linear time.
     *
     *   Your job (todo):  make modifications so that this
     *     operation becomes constant time (O(1)).
     *
     *   This task is different from most others in that most of
     *       the "real" work you do to make this work
     *	in O(1) time will be in _other_ functions which affect
     *	the length of lists.
     *
     *	HINT:  you are free to add data members to the List class...
     *	       maybe for "bookkeeping"??
     */
    int length( ) const {
      return size;
    }


  public:

    // Return true if the list is empty, false otherwise.
    bool is_empty( ) const {
      return front == nullptr;
    }


    void print() const {
      Node *p = front;

      cout << "[ ";
      while(p != nullptr) {
        cout << p->data << " ";
        p = p->next;
      }
      cout << "]\n";
    }

    void push_front(const T & data) {
      front = new Node(data, front);
      size++;
      if(back == nullptr)
        back = front;
    }

    bool pop_front(T &val) {
      Node *tmp;

      if(front==nullptr)
        return false;
      val = front->data;

      tmp = front;
      front = front->next;
      delete tmp;
      if(front==nullptr)
        back = nullptr;
      size--;
      return true;
    }

    void push_back(const T & val) {
      Node *tmp = new Node(val, nullptr);

      if(front == nullptr) {
        front = back = tmp;
      }
      else {
        back->next = tmp;
        back = tmp;
      }
      size++;
    }

    bool remove_first(const T &x) {
      Node *p, *tmp;
      T dummy;

      if(front==nullptr) return false;
      if(front->data == x) {
        pop_front(dummy);
        return true;
      }
      p = front;
      while(p->next != nullptr) {
        if(x == p->next->data) {
          tmp = p->next;
          p->next = tmp->next;
          if(tmp == back)
            back = p;
          delete tmp;
          return true;
        }
        p = p->next;
      }
      return false;
    }

    int slow_remove_all(const T &x) {
      int n=0;

      while(remove_first(x))
        n++;
      return n;
    }

    bool is_sorted() const {
      Node *p = front;

      while(p!=nullptr && p->next != nullptr) {
        if(p->data > p->next->data)
          return false;
        p = p->next;
      }
      return true;
    }

    /** TODO
     *    function:  count
     *     description:  Counts number of occurrences
     *     		of x in the list and returns that count.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    int count(const T &x) const {
      Node *p = front;
      int counter = 0;
      while(p != nullptr){
        if(p->data == x){
          counter++;
        }
        p = p->next;
      }
      return counter;
    }

    /* TODO
     *
     *  function:  pop_back
     *
     *  if list is empty, we do nothing and return false
     *  otherwise, the last element in the list is removed, its
     *      value (data field) is assigned to the reference parameter
     *      data (so the removed element can be 'passed-back' to the
     *      caller) and true is returned.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     *
     */
    bool pop_back(T &data) {
      if(front == nullptr)
        return false;
      else{
        Node *p = front;
        while(p->next->next != nullptr){
          p = p->next;
        }
        back = p;
        p = p->next;
        data = p->data;
        delete p;
        back->next = nullptr;
        size--;
        return true;
      }
    }

    /**
     * TODO:
     *   function:  equal_to
     *   description:  returns true if calling List and parameter
     *      List other contain exactly the same sequence of values.
     *      Returns false otherwise.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the shorter of the two lists.
     **/
    bool equal_to(const List<T> &other) const {
      Node *firstList = front;
      Node *secondList = other.front;
      if(size != other.size)
        return false;
      int i;
      for(i = 0; i < size; ++i){
        if(firstList->data != secondList->data){
          return false;
        }
        firstList = firstList->next;
        secondList = secondList->next;
      }
      return true;  // placeholder

    }

    /**
     * TODO:  print in reverse order
     *
     * Try to do without looking at notes!
     * Hints:  recursive helper function
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    void print_rev() const {
      Node * temp = front;
      cout << "[ ";
      reverseRecur(temp);
      cout << "]" << endl;
    }



    /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    void reverse() {
      Node *temp = front;
      T values[size];
      int i;
      for(i = size-1; i >= 0; i--){
        values[i] = temp->data;
        temp = temp->next;
      }
      temp = front;
      for(i = 0; i < size; ++i){
        temp->data = values[i];
        temp = temp->next;
      }
    }


    /** TODO
     *   function:  fast_remove_all
     *   description:  same behavior/semantics as
     *      slow_remove_all.  However, this function
     *      must guarantee linear time worst case
     *      runtime (hence, "fast").
     *
     *   REQUIREMENT:  linear worst-case runtime.
     *
     *   Note:  your solution may be either recursive or
     *   iteratieve.
     **/
    int fast_remove_all(const T &x) {
      Node *temp = front;
      Node *delNode;
      int counter = 0;
      while(front->data == x){
        remove_first(x);
      }
      while(temp->next != nullptr){
        if(temp->next->data == x){
          delNode = temp->next;
          temp->next = temp->next->next;
          delete delNode;
          counter++;
        }else
          temp = temp->next;
      }
      return counter;
    }

    /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order from
     *     smallest to largest and inserts x into the appropriate position
     * 	   retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  if given list not sorted, behavior is undefined/implementation
     * 		dependent.  We blame the caller.
     * 		So... you don't need to check ahead of time if it is sorted.
     *
     *
     * REQUIREMENTS:
     *
     *   O(n) runtime
     */
    void insert_sorted(const T &x) {
      Node *fr = front;
      Node *nxt;
      Node *newNode;
      if(front == nullptr){
        newNode = new Node(x, nullptr);
        back = newNode;
        front = newNode;
        size++;
        return;
      }
      if(fr->data >= x){
        nxt = fr->next;
        newNode = new Node(x, nullptr);
        newNode->next = front;
        front = newNode;
        size++;
        return;
      }
      while(fr->next != nullptr){
        if(fr->next->data >= x){
          nxt = fr->next;
          newNode = new Node(x, nullptr);
          fr->next = newNode;
          fr->next->next=nxt;
          size++;
          return;
        }
        fr=fr->next;
      }
      newNode = new Node(x, nullptr);
      size++;
      if(back == nullptr)
        back = newNode;
      else
        back->next = newNode;
      back = back->next;
    }

    /** TODO
     * function:  merge_with
     *
     * description:  assumes both list a and b are in
     * 	sorted (non-descending) order and merges them
     * 	into a single sorted list with the same
     * 	elements.
     *
     * 	This single sorted list is stored in a while
     * 	b becomes empty.
     *
     * 	if either of given lists are not sorted,
     * 	we blame the caller and the behavior is
     * 	implementation dependent -- i.e., don't worry
     * 	about it!
     *
     *      Condition in which both parameters are the same
     *      list (not merely "equal"), the function simply
     *      does nothing and returns.  This can be tested
     *      with simple pointer comparison.
     *
     * 	Example:
     *
     * 		a:  [2 3 4 9 10 30]
     * 		b:  [5 8 8 11 20 40]
     *
     * 		after call a.merge_with(b):
     *
     * 		  a:  [2 3 4 5 8 8 9 10 11 20 30 40]
     * 		  b:  []
     *
     *
     * REQUIREMENTS:
     *
     * 	Runtime Must be linear in the length of the
     * 	resulting merged list (or using variables above,
     * 	O(a.length()+b.length()).
     *
     *  should not allocate ANY new list
     * 	nodes -- it should just re-link existing
     * 	nodes.
     */
    void merge_with(List<T> &other){
      Node *fr = nullptr;
      Node *bk = nullptr;
      Node *list1 = front;
      Node *list2 = other.front;
      if(front == nullptr){
        front = other.front;
        other.front = nullptr;
        size = other.size;
        return;
      }
      if(list1->data >= list2->data){
        fr = list2;
        list2 = list2->next;
      }else if(list1->data < list2->data){
        fr = list1;
        list1 = list1->next;
      }
      bk = fr;
      while(list1 != nullptr && list2 != nullptr){
          if(list1->data >= list2->data){
            bk->next = list2;
            list2 = list2->next;
          }else if(list1->data < list2->data){
            bk->next = list1;
            list1 = list1->next;
          }
          bk = bk->next;
      }
      while(list1 != nullptr){
        bk->next = list1;
        bk = bk->next;
        list1 = list1->next;
      }
      while(list2 != nullptr){
        bk->next = list2;
        bk = bk->next;
        list2 = list2->next;
      }
      front = fr;
      back = bk;
      size = other.size + size;
      other.front = nullptr;
      other.back = nullptr;
      other.setSize(0);
    }

    /**
     * TODO
     * function:  clone
     *
     * description:  makes a "deep copy" of the given list a
     *   and returns it (as a List pointer).
     *
     * NOTE:  this functionality would normally be folded into
     *  a "copy constructor"
     *
     */
    List<T> * clone() const {
      List<T> *listClone = new List<T>();
      Node *copy = front;
      while(copy != nullptr){
        listClone->push_back(copy->data);
        copy = copy->next;
      }
      return listClone;
    }

    /**
     * TODO
     * function:  prefix
     *
     * description:  removes the first k elements from the
     *               calling list which are used to form a new list
     *		            which is then returned.
     *
     *		if n is the length of the given list, we have the
     *		following boundary conditions:
     *
     *		  if k==0:
     *			    calling list unchanged and an empty list returned
     *		  if k>=n:
     *			    calling becomes empty and a list containing
     *			    all elements previously in lst is returned.
     *
     *		examples:
     *
     *		  EX1:  lst:  [2, 3, 9, 7, 8]
     *			k:    3
     *
     *			call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [7, 8]
     *			   returned list (prefix):  [2, 3, 9]
     *
     *		  EX2  lst:  [2, 3, 9, 7, 8]
     *			k:    0
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
     *			   returned list:  []
     *
     *		  EX3  lst:  [2, 3, 9, 7, 8]
     *			k:    5
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(5);
     *
     *			after call:
     *			   lst:  []
     *			   returned list:  [2, 3, 9, 7, 8]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) worst case where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned prefix should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be
     *                  allocated or deallocated; you should just
     *                  "re-use" the existing nodes.  HOWEVER, you will
     *		               need to allocate a List object for the returned
     *		               prefix (but, again, the underlying Nodes should be
     *		               re-used from the calling list).
     */
    List<T> * prefix(unsigned int k) {
      List<T> *listPrefix = new List<T>();
      Node *fromList = front;
      Node *toList = listPrefix->front;
      Node *prevNode;
      int counter = 0;
      if(k == 0)
        return listPrefix;
      listPrefix->front = front;
      if(size <= k){
        front = nullptr;
        listPrefix->back = back;
        listPrefix->setSize(size);
        return listPrefix;
      }
      while(k != counter){
        listPrefix->setSize((listPrefix->size) + 1);
        size--;
        counter++;
        prevNode = fromList;
        fromList = fromList->next;
      }
      prevNode->next = nullptr;
      listPrefix->front = front;
      listPrefix->back = prevNode;
      front = fromList;
      return listPrefix;

    }

    /**
     * TODO
     * function:  filter_leq
     *
     * description:  removes all elements of the given list (lst) which
     *		are less than or equal to a given value (cutoff)
     *
     *		A list containing the removed elements is returned.
     *
     * examples:
     *
     *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
     *		cutoff:  4
     *
     *		after call:
     *			lst:  [9, 8, 12, 7]
     *			returned list:  [4, 2, 4, 3]
     *
     *       -----------------------------------------
     *	EX2: 	lst:  [6, 5, 2, 1]
     *		cutoff:  6
     *
     *		after call:
     *			lst:  []
     *	 		returned list:  [6, 5, 2, 1]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned list should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
     *		   you should just "re-use" the existing nodes.  HOWEVER, you will
     *		   need to allocate a LIST structure itself (i.e., for the returned
     *		   list).
     *
     */
    List<T> * filter_leq(const T & cutoff) {
      int value;
      List<T> *listFilter = new List<T>();
      if(front == nullptr){
        return listFilter;
      }else if(front->data <= cutoff){
        pop_front(value);
        listFilter->push_back(value);
      }
      Node *temp = front;
      Node *delNode;
      while(temp->next != nullptr){
        if(temp->next->data <= cutoff){
          delNode = temp->next;
          temp->next = delNode->next;
          if(delNode == back)
             back = temp;
          listFilter->push_back(delNode->data);
          delete delNode;
          continue;
        }
        temp = temp->next;
      }
      return listFilter;
    }

    /**
     * TODO
     * function:  concat
     *
     * description:  concatenates the calling list with parameter list (other)
     *    The resulting concatenation is reflected the calling list; the
     *    parameter list (other) becomes empty.
     *
     *    example:
     *
     *	EX1:  a: [2, 9, 1]
     *	      b: [5, 1, 2]
     *
     *	      call:
     *	            a.concat(b);
     *
     *	after call:
     *
     *		a: [2, 9, 1, 5, 1, 2]
     *		b: []
     *
     * REQUIREMENTS:
     *
     *     runtime:  O(1)
     *
     *     sanity:  this operation makes sense when a and b
     *		are distinct lists.  For example, we don't
     *		want/allow the caller to do something like
     *		this:
     *
     *			List<int> *my_list = new List<int>();;
     *
     *			my_list->push_front(my_lst, 4);
     *			my_list->push_front(my_lst, 2);
     *
     *			my_lst->concat(my_lst);
     *
     *		your implementation must detect if it is being
     *		called this way.  If so the function does nothing
     *		and (optionally) prints an error message to
     *		stderr.
     *
     */
    void concat(List<T> &other) {
      if(this == &other) {
        cerr << "warning:  List::concat():  calling object same as parameter";
        cerr << "\n          list unchanged\n";
        return;
      }else if(other.front == nullptr){
        return;
      }else if(front == nullptr){
        this->front = other.front;
        this->back = other.back;
        other.front = nullptr;
        other.back = nullptr;
        setSize(other.size);
        other.setSize(0);
        return;
      }
      back->next = other.front;
      back = other.back;
      other.front = nullptr;
      other.back =  nullptr;
      setSize(size + other.size);
      other.setSize(0);
    }


    /**
     * TODO
     *
     * function:  compare_with
     * description: compares the calling list with parameter list (other)
     *    "LEXICALLY" (essentially a generalization of dictionary
     *    ordering).
     *
     *    link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *    Return Value:
     *
     *       o if the two lists are identical, 0 is returned.
     *       o if the calling list is lexically BEFORE the other list,
     *             -1 is returned
     *       o otherwise, the other list is lexically before the calling
     *             list and 1 (positive one) is returned.
     *
     *    Properties and examples:
     *
     *        The empty list is lexically before all non-empty lists
     *          (you can say it is "less than" all non-empty lists).
     *
     *        Examples (using mathematical notation):
     *
     *          [2 5 1] < [3 1 1 1 1]    (think dictionary ordering!)
     *
     *          [4 1 3] < [4 1 3 0 0 0]  (prefix: just like "car" is before
     *                                            "cartoon" in the dictionary).
     *
     *          [4 5 6 1 2 3 9 9 9] < [4 5 6 1 4 0 0]
     *                   ^                     ^
     *                      (they have a common prefix of length 4; but at
     *                      the fifth position they differ and the left list
     *                      is the winner (smaller) -- no need to look further)
     *
     *
     *        Templates?
     *
     *          Since List is a template class, the elements of a particular
     *          list need not be integers.  For example, we could have
     *          lists of strings.
     *
     *          Good news:  the exact same principle applies because
     *          strings can be compared just like integers can be compared!
     *
     *          Great news:  you don't need to think about this at all!
     *          The exact same code you would write if you assumed the element
     *          type is integer will work for other types like strings.
     *
     *          Why?  Because, for example, all of these operators:
     *
     *                   <, <=, ==, > and >=
     *
     *          all work on strings.  They are not 'built-in' to C++, but
     *          the class string has "overloaded" these operators (they
     *          result in an appropriate function call).
     *
     *          (In a subsequent exercise, we will do this kind of
     *          overloading ourselves!)
     *
     *        Examples with lists of strings:
     *
     *          ["egg", "goat"] < ["egg", "globe", "apple"]
     *
     *          ["zebra", "fun"] < ["zebra", "funny"]
     *
     *        [Yes, the components of these lists are THEMSELVES compared
     *        lexically, but the string class is doing those comparisons)
     *
     */
    int compare_with(const List<T> &other) const {
        Node *firstList = front;
        Node *secondList = other.front;
        while(firstList != nullptr && secondList != nullptr){
          if(firstList->data < secondList->data)
            return -1;
          else if(firstList->data > secondList->data)
            return 1;
          firstList = firstList->next;
          secondList = secondList->next;
        }
        if(this->length() > other.length())
          return 1;
        else if(this->length() < other.length())
          return -1;
        return 0;
    }

    /*
     * TODO
     *
     * function:  suffix_maxes
     *
     * desc:  constructs a new list of the same length as the calling object
     *        with the value stored at position i of the new list is the MAXIMUM
     *        value in the suffix (or tail) of the calling list starting from
     *        position i.
     *
     *        This new list is returned and the calling list is unchanged.
     *
     *        Example:
     *
     *          Given List:  [6, -18, 12, 4, 1, 7, 2, 5  4]
     *                                    ^^^^^^^^^^^^^^^^
     *
     *          New list:    [12, 12, 12, 7, 7, 7, 5, 5, 4]
     *                                    ^
     *
     *              (as a sub-example, the marked entry in the new list
     *              (marked with '^') is the max of the marked suffix in the
     *              given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS:
     *
     *        Total Runtime:   O(n)
     *        Calling list is unchanged.
     *
     */
    List<T> * suffix_maxes() const{
      List<T> *listSuffix = new List<T>();
      Node *fromList = this->front;
      while(fromList != nullptr){
        listSuffix->push_back(suffixRecursive(fromList->data, fromList));
        fromList = fromList->next;
        // toList = toList->next;
      }
      return listSuffix;
    }



  private:
    Node *front;
    Node *back;
    int size = 0;

    void reverseRecur(Node * pCurrent) const {
      if(pCurrent == nullptr)
        return;
      reverseRecur(pCurrent->next);
      cout << pCurrent->data << " ";
    }

    int suffixRecursive(int bigNum, Node * p) const{
      if(p != nullptr){
        if(bigNum < p->data){
          bigNum = p->data;
        }
        return suffixRecursive(bigNum, p->next);
      }
      return bigNum;
    }

    void setSize(int newSize){
      size = newSize;
    }

    void init( ) {
      front = nullptr;
      back = nullptr;

    }
};

#endif
