#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      bst_node *right;
      int numNodes;
      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr)
        : val { _val },  left { l }, right {r} 
      { numNodes = 0;}
    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success){
      if(r == nullptr){
        success = true;
        return new bst_node(x, nullptr, nullptr);
      }

      if(r->val == x){
        success = false;
        return r;
      }
      if(x < r->val){
        r->numNodes = r->numNodes + 1;//modifies the number of nodes in the tree
        r->left = _insert(r->left, x, success);
        return r;
      }
      else {
        r->numNodes = r->numNodes + 1;//modifies the number of nodes in the tree
        r->right = _insert(r->right, x, success);
        return r;
      }
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      if(contains(x))//checks if it's already in the tree
        success = false;
      else
        root = _insert(root, x, success);//not in the tree
      check_size_balance(root);//check if size balance property was broken
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success){
      bst_node *tmp;
      bool sanity;
      r->numNodes = r->numNodes - 1;//decreases the number of nodes at root r
      if(r==nullptr){
        success = false;
        return nullptr;
      }
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->right = _remove(r->right, r->val, sanity);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        return r;
      }
      if(x < r->val){
        r->left = _remove(r->left, x, success);
      }
      else {
        r->right = _remove(r->right, x, success);
      }
      return r;

    }

  public:

    bool remove(T & x){
      bool success;
      if(!contains(x))//checks if x is in the tree before going through it
        success = false;
      else
        root = _remove(root, x, success);//gets the tree without the value x
      check_size_balance(root);//checks if its still size balanced
      return success;
    }


  private:
    //fuinction that checks if the tree is size balanced
    void check_size_balance(bst_node *r){
      int nL, nR, max, min, totalNodes;
      if(r == nullptr) return;
      if(r->left == nullptr && r->right == nullptr)//base cases
        return;
      //checks if it's a leaf
      if(r->left == nullptr)  nL = 0;
      else
        nL = r->left->numNodes + 1;
      if(r->right == nullptr) nR = 0;
      else
        nR = r->right->numNodes + 1;
      //determine which subtree is max and min
      if(nL > nR){
        max = nL;
        min = nR;
      }else{
        max = nR;
        min = nL;
      }
      //checks if the node meets the requirement for size balance
      if(max <= 2*min + 1){
        check_size_balance(r->left);
        check_size_balance(r->right);
      }else{//fix the tree rooted at r so that it's size balanced
        totalNodes = nL + nR + 1;
        std::vector<T> *vec = to_vector(r);
        delete_nodes(r);//deallocated the tree
        //builds a tree that is as balanced as possible
        r = from_sorted_vec(*vec,totalNodes)->root;
      }
    }

    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/

  private:
    //helper function for the to vector function
    void _to_vector(std::vector<T> * vec,bst_node *r){
      if(r == nullptr)//base case
        return;
      _to_vector(vec,r->left);//recursive left subtree
      vec->push_back(r->val);//push value
      _to_vector(vec,r->right);//recursive right subtree
    }

  public:

    // TODO
    std::vector<T> * to_vector() {
      std::vector<T> *elements = new std::vector<T>();//allocate memory for a new vector
      _to_vector(elements,root);//populate the vector
      return elements;
    }

    //overloaded function used in the size balanced function
    //Description: creates a vector with sorted values given a root r
    std::vector<T> * to_vector(bst_node *r) {
      std::vector<T> *elements = new std::vector<T>();
      _to_vector(elements,r);
      return elements;
    }

    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T &x) {
      if(root == nullptr)
        return false;
      int n = size();
      if(i < 1 || i > n){
        x = root->val;
        return false;
      }
      //i is a valid input
      return _get_ith(root, i, x);
    }

  private:
    //helper function for get_ith
    bool _get_ith(bst_node * r, int i, T &x){
      if(i <= 1){//must get the left most node
        if(r->left == nullptr){//reached the left
          x = r->val;
          return true;
        }else{
          return _get_ith(r->left,i,x);//recursive call to reach the left
        }
      }if(r->left->numNodes + 2 == i){//the root is the ith number
        x = r->val;
        return true;
      }else if(r->left->numNodes < i){// the ith number is on the right subtree
        i = i - r->left->numNodes - 2;
        return _get_ith(r->right, i, x);
      }else{//the ith number is on the left subtree
        return _get_ith(r->left, i , x);
      }
    }

  public:

    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }


    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
  
    int num_geq(const T & x) {
      return _num_geq(root, x);
    }

  private:
    //helper function for num_geq
    int _num_geq(bst_node * r, const T & x){
      if(r == nullptr)//base case
        return 0;
      else if(x <= r->val){//values are in the left subtree
        if(r->right == nullptr)//checks to see if the right subtree is empty
          return 1 + _num_geq(r->left,x);
        else
          return r->right->numNodes + 2 + _num_geq(r->left,x);//add the right subtree nodes
      }else
        return _num_geq(r->right,x);//the values are on the right subtree
    }
    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *
     */
  public:

    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }
    

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T &x) {
      return _num_leq_SLOW(root, x);
    }

  public:
    //helper function for num_leq
    int _num_leq(bst_node * r, const T & x){
      if(r == nullptr)//base case
        return 0;
      else if(x >= r->val){//values are on the right subtree
        if(r->left == nullptr)//checks if the left subtree is empty
          return 1 + _num_leq(r->right,x);
        else
          return r->left->numNodes + 2 + _num_leq(r->right,x);//add the left subtree nodes
      }else
        return _num_leq(r->left,x);//the values are on the left subtree
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
  public:

    int num_range(const T & min, const T & max) {
      bst_node * tempRoot = root;
      //conditions to check before traversing the tree
      if(min > max)
        return 0;
      else if(min == max){//same number, just check if the value exists
        if(contains(min))
          return 1;
        else
          return 0;
      }else{//min and max are valid inputs
        while(true){
          if(tempRoot != nullptr){
            if(max < tempRoot->val){//checks if the root is within max range
              tempRoot = tempRoot->left;//must be on the left subtree
              continue;
            }else if(min > tempRoot->val){//checks if root is within the min range
              tempRoot = tempRoot->right;//must be on the right subtree
              continue;
            }
            break;//root must be in the range
            }
          return 0;
        }

        //use num_leq and num_geq to find the numbers < max and > min
        return _num_leq(tempRoot->right, max) + _num_geq(tempRoot->left, min) + 1;//plus 1 for the root
      }
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *
     */
  public:
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:


    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }

    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }





  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

    /* 
     * TODO:
     * Complete the (recursive) helper function for the post-order traversal.
     * Remember: the indentation needs to be proportional to the height of the node!
     */
    static void _postorder(bst_node *r, int margin){

      std::cout << "\n   WARNING:  POSTORDER UNIMPLEMENTED...\n";
    }

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

    // indentation is proportional to depth of node being printed
    //   depth is #hops from root.
    void postorder() {

      std::cout << "\n======== BEGIN POSTORDER ============\n";
      _postorder(root, 0);
      std::cout << "\n========  END POSTORDER  ============\n";

    }

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * bst_from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) return nullptr;
      m = (low+hi)/2;
      root = new bst_node(a[m]);
      root->left  = _from_vec(a, low, m-1);
      root->right = _from_vec(a, m+1, hi);
      //modifies the bookeeping for the number of nodes in the tree
      if(root->left == nullptr && root->right == nullptr){
        root->numNodes = 0;
      }else if(root->left == nullptr){
        root->numNodes = root->right->numNodes + 1;
      }else if(root->right == nullptr){
        root->numNodes = root->left->numNodes + 1;
      }else{
        root->numNodes = root->left->numNodes + root->right->numNodes + 2;
      }
      return root;

    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){

      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);
      return t;
    }

    // TODO:  num_leaves
    //   Hint:  feel free to write a helper function!!
    int num_leaves() {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }

    // TODO:  num_at_level
    // description:  returns the number of nodes at specified level
    //   in tree.
    // note:  the root is at level 0.
    // Hint:  recursive helper function?
    int num_at_level(int level) {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }


  private:
    bst_node *root;


}; // end class bst

#endif
