#include <iostream>
#include <string>
#include <queue>

using namespace std;

class KSNode{
  // Key to String Node
  int height;
  KSNode *left;
  KSNode *right;
  KSNode *parent;
  int key;
  string str;
  int order;
  int size;
  friend class MAVLTree;

public:
  KSNode(){
    height = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
    size = 0;
  }
  KSNode(int k, string s, int o){
    key = k;
    str = s;
    order = o;
    left = NULL;
    right = NULL;
    parent = NULL;
    height = 1;
    size = 1;
  }
};

class MAVLTree{

  int len;
  KSNode *root;
  KSNode *iroot;
  int toDelOrder;
  string defRet;
    public:
        MAVLTree();  //Initialize the ADT 
      int size() const; // number of elements
      bool isEmpty() const; // is the queue empty?
    void insert(const int k, string s);//insert key k,s into the tree
      void remove(const int k);//remove k from the tree, if exists
      string search(const int k);//search for key k in the tree
    void delete_by_place(int i); //Delete from the entry at the  ith place (as determined by the order of insertion)
        int get_place(int k);//Return the place (which is determined by the order of insertion), if x does not exist, return -1 
      void display();
      void display2();

    private:
      void addNewKS(KSNode *&ksR, const int k, string s, int o, KSNode *parent); // Helper function to add a new KS node
      void rotateLeft(KSNode *);  // Left Rotation
      void rotateRight(KSNode *); // Right Rotation
      void rotateRightLeft(KSNode *); // Right Left Rotation
      void rotateLeftRight(KSNode *); // Left Right Rotation
      void deleteKS(KSNode *&ksR, int k);
      KSNode* minVal(KSNode *);
      int height(KSNode*);
      int getBalance(KSNode *);
      int subNode(KSNode*);
      int elementsBefore(KSNode *);
      int searchOrder(int k, KSNode*);
};



MAVLTree::MAVLTree(){
  len = 0;
  root = NULL;
  iroot = NULL;
}

int MAVLTree::size() const{
  return len;
}

bool MAVLTree::isEmpty() const{
  return len==0;
}

void MAVLTree::insert(const int k, string s){
  addNewKS(root, k, s,len+1, NULL);
  addNewKS(iroot,len+1,s, k, NULL);
  len++;
}

void MAVLTree::addNewKS(KSNode *&ksR, const int k, string s, int o, KSNode *parent){

  if (ksR == NULL){
        KSNode *toAdd = new KSNode(k,s,o);
      toAdd->parent = parent;
      ksR = toAdd;
      return;
    }

    if(k < ksR->key){
      addNewKS(ksR->left, k, s, o, ksR);
      int rightHeight = 0;
      int leftHeight = ksR->left->height;
      if(ksR->right) rightHeight = ksR->right->height;
      if(leftHeight - rightHeight == 2){
        if(k < ksR->left->key)  rotateLeft(ksR);
        else rotateRightLeft(ksR);
      }
    }
    else{
      addNewKS(ksR->right, k, s, o, ksR);
      int leftHeight = 0;
      int rightHeight = ksR->right->height;
      if(ksR->left) leftHeight = ksR->left->height;
      if(rightHeight - leftHeight == 2){
        if(ksR->right->key < k) rotateRight(ksR);
        else rotateLeftRight(ksR);
      }
    }
    int leftHeight = 0;
    int rightHeight = 0;
    if(ksR->left) leftHeight = ksR->left->height;
  if(ksR->right) rightHeight = ksR->right->height;
    ksR->height = max(leftHeight, rightHeight) + 1;
    ksR->size= subNode(ksR->left) + subNode(ksR->right) + 1;
}

void MAVLTree::rotateLeft(KSNode *z){
  KSNode *y = z->left;
  z->left = y->right;
  if(y->right)y->right->parent = z;
  y->right = z;
  y->parent = z->parent;
  if(z->parent && z == z->parent->left) z->parent->left = y;
  else if(z->parent) z->parent->right = y;
  z->parent = y;

  int leftHeight = 0;
    int rightHeight = 0;
    if(z->left) leftHeight = z->left->height;
  if(z->right) rightHeight = z->right->height;
  z->height = max(leftHeight, rightHeight) + 1;
  z->size= subNode(z->left) + subNode(z->right) + 1;


  leftHeight = 0;
  rightHeight = 0;
  if(y->left) leftHeight = y->left->height;
  if(y->right) rightHeight = y->right->height;
  y->height = max(leftHeight, rightHeight) + 1;
  y->size= subNode(y->left) + subNode(y->right) + 1;

  if(z==root) root = y;
  if(z==iroot) iroot = y;



}

void MAVLTree::rotateRight(KSNode *z){
  KSNode *y = z->right;
  z->right = y->left;
  if(y->left) y->left->parent = z;
  y->left = z;
  y->parent = z->parent;
  if(z->parent && z == z->parent->left) z->parent->left = y;
  else if(z->parent) z->parent->right = y;
  z->parent = y;


  int leftHeight = 0;
    int rightHeight = 0;
    if(z->left) leftHeight = z->left->height;
  if(z->right) rightHeight = z->right->height;
  z->height = max(leftHeight, rightHeight) + 1;
  z->size= subNode(z->left) + subNode(z->right) + 1;

  leftHeight = 0;
  rightHeight = 0;
  if(y->left) leftHeight = y->left->height;
  if(y->right) rightHeight = y->right->height;
  y->height = max(leftHeight, rightHeight) + 1;
  y->size= subNode(y->left) + subNode(y->right) + 1;

  if(z==root) root = y;
  if(z==iroot) iroot = y;
}


void MAVLTree::rotateRightLeft(KSNode *ksR){
  rotateRight(ksR->left);
  rotateLeft(ksR);
}


void MAVLTree::rotateLeftRight(KSNode *ksR){
  rotateLeft(ksR->right);
  rotateRight(ksR);
}

void MAVLTree::display(){
  queue <KSNode *> q;
  q.push(root);
  q.push(NULL);
  cout<<root->key<<"("<<root->size<<")"<<endl;
  while(!q.empty()){
    KSNode *cur=q.front();
    q.pop();
    if(cur==NULL){
      cout<<endl;
      if(!q.empty()) q.push(NULL);
      continue;
    }
    if(cur->left){
      cout<<cur->left->key<<"("<<cur->left->size<<")"<<" ";
      q.push(cur->left);
    }
    //i++;
    if(cur->right){
      cout<<cur->right->key<<"("<<cur->right->size<<")"<<" ";
      q.push(cur->right);
    }
}
}


void MAVLTree::display2(){
  queue <KSNode *> q;
  q.push(iroot);
  q.push(NULL);
  cout<<iroot->key<<"("<<iroot->size<<")"<<endl;
  while(!q.empty()){
    KSNode *cur=q.front();
    q.pop();
    if(cur==NULL){
      cout<<endl;
      if(!q.empty()) q.push(NULL);
      continue;
    }
    if(cur->left){
      cout<<cur->left->key<<"("<<cur->left->size<<")"<<" ";
      q.push(cur->left);
    }
    //i++;
    if(cur->right){
      cout<<cur->right->key<<"("<<cur->right->size<<")"<<" ";
      q.push(cur->right);
    }
}
}



void MAVLTree::deleteKS(KSNode *&cur, int k){
  if(cur == NULL) return;

  if(k < cur->key) deleteKS(cur->left, k);
  else if(k > cur->key) deleteKS(cur->right, k);
  else{
    toDelOrder = cur->order;
    if(cur->left == NULL || cur->right == NULL){
      KSNode *temp = NULL;
      if(temp == cur->left) temp = cur->right;
      else temp = cur->left;

      if(temp == NULL){
        // No child
        temp = cur;
        KSNode *parent = cur->parent;
        if(parent && parent->left == cur){
          // Left child
          parent->left = NULL;
        }
        else if(parent){
          // Right child
          parent->right = NULL;
        }
        else{
          // It is root
          cur = NULL;
        }
        delete(temp);
      }
      else{
        //cout<<"Here"<<endl;
        KSNode *parent = cur->parent;
        temp->parent = parent;

        if(parent && parent->left == cur){
          // Left child
          parent->left = temp;
        }
        else if(parent){
          // Right child
          parent->right = temp;
        }
        cur = temp; 
      }
    }
    else{
      KSNode *pre = minVal(cur->right);
      cur->key = pre->key;
      deleteKS(cur->right, pre->key);
    }
  }

  if(cur==NULL) return;

  cur->height = max(height(cur->left), height(cur->right)) +1;
  cur->size= subNode(cur->left) + subNode(cur->right) + 1;

  int balance = getBalance(cur);
  //cout<<cur->key<<endl;
  if(balance > 1 && getBalance(cur->left)>=0) rotateLeft(cur);
  else if(balance > 1 && getBalance(root->left)< 0) rotateRightLeft(cur);
  else if(balance < -1 && getBalance(root->right) <=0 ) rotateRight(cur);
  else if(balance < -1 && getBalance(root->right) > 0) rotateLeftRight(cur);
}

KSNode* MAVLTree::minVal(KSNode *cur){
  KSNode *goLeft = cur;
  while(goLeft->left){
    goLeft = goLeft->left;
  }
  return goLeft;
}

int MAVLTree::height(KSNode *t){
  if(t==NULL) return 0;
  return t->height;
}

int MAVLTree::getBalance(KSNode *t){
  if(t==NULL) return 0;
  return height(t->left) - height(t->right);
}

void MAVLTree::remove(int k){
  deleteKS(root,k);
  deleteKS(iroot, toDelOrder);
  len--;
}

int MAVLTree::subNode(KSNode *t){
  if(t==0) return 0;
  return t->size;
}

string MAVLTree::search(const int k){
  string toRet = "Not Found";
  KSNode *it = root;
  while(it){
    if(k < it->key) it = it->left;
    else if(k > it->key) it = it->right;
    else{
      toRet = it->str;
      break;
    }
  }
  return toRet;
}

int MAVLTree::get_place(int k){
  int order = searchOrder(k,root);
  int toRet = 0;
  KSNode *it = iroot;
  while(it){
    if(order < it->key) it = it->left;
    else if(order > it->key) it = it->right;
    else{
      toRet = elementsBefore(it);
      break;
    }
  }
  if(it) return toRet+1;
  else return -1;
}

int MAVLTree::searchOrder(int k, KSNode *r){
  int toRet;
  KSNode *it = r;
  while(it){
    if(k < it->key) it = it->left;
    else if(k > it->key) it = it->right;
    else{
      toRet = it->order;
      break;
    }
  }
  return toRet;
}

int MAVLTree::elementsBefore(KSNode *t){
  if(t==NULL) return 0;
  int toRet = subNode(t->left);
  KSNode *parent = t->parent;
  if(parent && parent->right == t){
    toRet++;
    toRet += elementsBefore(parent);
  }
  else if(parent){
    // Is left child
    toRet+= elementsBefore(parent) - subNode(parent->left);
  }
  return toRet;
}

void MAVLTree::delete_by_place(int i){
  KSNode *it = iroot;

  if(i > it->size) return;
  int z;
  while(it){
    if(it->left) z = subNode(it->left);
    else z = 0;

    if(i <= z) it = it->left;

    else if(i == z + 1){
      //cout<<it->order<<endl;
      remove(it->order);
      break;
    }
    else{
      i = i - (z+1);
      it = it->right;
    }
  }
}