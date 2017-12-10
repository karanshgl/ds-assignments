#include <iostream>
//#include <queue>
using namespace std;


template<typename E, typename C> class Heap;

//TNode as node of the tree

template <typename E, typename C>
class TNode{
  E data;
  TNode <E,C> *parent;
  TNode <E,C> *left;
  TNode <E,C> *right;

  friend class Heap<E,C>;

public:
  TNode();
  TNode(const E &info);
  const E& getData() const;
};

template <typename E, typename C>
TNode<E,C>::TNode(){
  parent = NULL;
  left = NULL;
  right = NULL;
}


template <typename E, typename C>
TNode<E,C>::TNode(const E &info){
  data = info;
  parent = NULL;
  left = NULL;
  right = NULL;
}


template <typename E, typename C>
const E& TNode<E,C>::getData() const { return data; }


//LNode as nodes of the linked list 
template <typename E, typename C>
class LNode{
  E data;
  LNode <E,C> *next;

  friend class Heap<E,C>;

public:
  LNode();
  LNode(E info);

};


  template <typename E, typename C>     // element and comparator
  class Heap {                 // priority-queue interface
  public:
    Heap(); //Constructor
    int size() const;         // number of elements
    bool isEmpty() const;       // is the queue empty?
    void insert(const E& e);        // insert element
    const E& min() const;   // minimum element
    void removeMin();     // remove minimum
    void mergeHeaps(Heap <E,C>H); //MODIFIED 
    void buildHeap(E A[], int size);  
    //One function to do the traversal 
    E* preorder(); // Returns an array of the heap
   // void disp(){display(root);}
  private:
    C cmp;
    TNode<E,C> *root;
    TNode<E,C> *last;

    int len;
    void heapify(E A[], int size, int iElement);
    void deleteTree(TNode<E,C> *toDel);
    void heapifyUp(TNode<E,C> *goUp);
    void heapifyDown(TNode<E,C> *goUp);
    //void display(TNode<E,C> *tree);
    void preorder_helper(E*A,TNode<E,C> *cur, int &index);
    TNode<E,C> *makeTree(E A[], int init, int size, TNode<E,C> *parent);
    TNode<E,C>* insertTo();
    TNode<E,C>* updateLast(TNode<E,C>* cur);
  };


template <typename E, typename C>
Heap<E,C>::Heap(){
  root = NULL;
  last = NULL;
  len = 0;
}


template <typename E, typename C>
int Heap<E,C>::size() const{ return len; }

template <typename E, typename C>
bool Heap<E,C>::isEmpty() const { return len==0; }

template <typename E, typename C>
void Heap<E,C>::buildHeap(E A[], int size){
  // Builds a Heap out of an array A
  deleteTree(root); // Delete the existing Tree
  len = size;
  int bottom = size/2;

  while(bottom>-1){
    // Heapify the array
    heapify(A,size,bottom);
    bottom--;
  }

  root = makeTree(A,0,size,NULL);
}



template <typename E, typename C>
TNode<E,C>* Heap<E,C>::makeTree(E A[], int init, int size, TNode<E,C> *parent){
  // Converts the array into a Tree
  if(init >= size) return NULL;
  TNode<E,C> *curRoot = new TNode<E,C>(A[init]);
  curRoot->parent = parent;

  // Recursive Calls
  curRoot->left = makeTree(A, 2*init + 1, size,curRoot);
  curRoot->right = makeTree(A, 2*init + 2, size, curRoot);

  if(init==size-1) last = curRoot;
  return curRoot;
}

template <typename E, typename C>
const E& Heap<E,C>::min() const{
  return root->getData();
}

template <typename E, typename C>
void Heap<E,C>::deleteTree(TNode<E,C> *toDel){
  if(toDel==NULL) return;

  deleteTree(toDel->left);
  deleteTree(toDel->right);
  delete toDel;
}

template <typename E, typename C>
void Heap<E,C>::insert(const E& e){

  TNode<E,C> *newNode = new TNode<E,C>(e);

  if(root==NULL){
    root = newNode;
    last = root;
    return;
  }

  TNode<E,C> *lastParent = insertTo();
  if(lastParent->left == NULL) lastParent->left = newNode;
  else lastParent->right = newNode;

  newNode->parent = lastParent;

  last = newNode;
  heapifyUp(newNode);
  ++len;
}

template <typename E, typename C>
void Heap<E,C>::heapifyUp(TNode<E,C> *goUp){
  if(root==goUp) return;

  TNode<E,C> *parNode = goUp->parent;
  while(goUp->parent){
    parNode = goUp->parent;
    if(cmp(goUp->data,parNode->data)) swap(parNode->data, goUp->data);
    goUp=parNode;
  }
}

template <typename E, typename C>
TNode<E,C>* Heap<E,C>::insertTo(){
  TNode<E,C> *cur = last;
  TNode<E,C> *par = last->parent;

  if(par == NULL) return cur;

  while(par){
    if(par->left == cur){
      if(par->right == NULL) return par;
      par = par->right;
      while(par->left){
        par = par->left;
      }
      return par;
    }
    cur = cur->parent;
    par = cur->parent;
  }

  // We have reached the root

  while(cur->left){
    cur=cur->left;
  }
  return cur;
}


template <typename E, typename C>
TNode<E,C>* Heap<E,C>::updateLast(TNode<E,C>* cur){
  TNode<E,C> *par = cur->parent;
  while(par){
    if(par->right == cur){
      par = par->left;
      while(par->right){
        par = par->right;
      }
      return par;
    }
    cur = cur->parent;
    par = cur->parent;
  }
  // Root is reached
  while(cur->right){
    cur=cur->right;
  }
  return cur;
}

template <typename E, typename C>
void Heap<E,C>::removeMin(){

  if(last==root){
    delete last;
    root = NULL;
    last = NULL;
    return;
  }

  swap(root->data,last->data);
  TNode<E,C>* par = last->parent;

  if(par->right == last){
    par->right = NULL;
    delete last;
    last = par->left;
  }
  else{
    par->left = NULL;
    delete last;
    last = updateLast(par);
  }
  heapifyDown(root);
  --len;
}


template <typename E, typename C>
void Heap<E,C>::heapifyDown(TNode<E,C>* cur){

    if(cur==NULL) return;

    TNode<E,C>* priority = cur;
    TNode<E,C>* left = cur->left;
    TNode<E,C>* right = cur->right;
 
    if ((left != NULL) && cmp(left->data, priority->data)) priority = left;
 
    if (right != NULL && cmp(right->data, priority->data)) priority = right;
 
    if (priority == cur) return;

    swap(cur->data, priority->data); 
    heapifyDown(priority);

  
}


template <typename E, typename C>
void Heap<E,C>::heapify(E A[], int size, int iElement){
   int priority = iElement; 
    int l = 2*iElement + 1; 
    int r = 2*iElement + 2; 
 
    if (l < size && cmp(A[l], A[priority])) priority = l;
 
    if (r < size && cmp(A[r], A[priority])) priority = r;
 
    if (priority == iElement) return;

    swap(A[iElement], A[priority]); 
    heapify(A, size, priority);
}


template <typename E, typename C>
E* Heap<E,C>::preorder(){
  E *toRet = new E[len];
  int a =0;
  preorder_helper(toRet,root,a);
  return toRet;
}

template <typename E, typename C>
void Heap<E,C>::preorder_helper(E* A, TNode<E,C> *cur, int &index){
  if(cur==NULL) return;

  A[index] = cur->data;
  ++index;
  preorder_helper(A,cur->left,index);
  preorder_helper(A,cur->right,index);
}


template <typename E, typename C>
void Heap<E,C>::mergeHeaps(Heap<E,C> H){
  E *A = H.preorder();
  E *B = preorder();
  E *temp = new E[H.size() + size() + 1];
  int k = 0;
  for(int i=0;i<H.size();i++) temp[k++] = A[i]; 
  for(int i=0;i<size();i++) temp[k++] = B[i];
  buildHeap(temp,k);

}
