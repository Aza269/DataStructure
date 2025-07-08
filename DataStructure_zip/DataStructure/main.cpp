#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <memory>

using namespace std;

/////////////////////////////////////////// THIS FOR LINKED LIST //////////////////////////////////////////////////

class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(NULL) {}
};


class LinkedList {
    public:Node* head;

    public:
        void insert(int num) {
            Node* temp = new Node(num);
            if(head == NULL) {
                head = temp;
                return;
            }
            Node* now = head;
            while(now->next != NULL) {
                now = now->next;
            }
            now->next = temp;
        }
        void insert(int num, int index) {
            Node* temp = new Node(num);
            if(index == 0) {                
                temp->next = head;
                head = temp;
                return;
            }
            Node* now = head;
            while(index > 1 && now != NULL) {
                now = now->next;
                index--;
            }
            if(now == NULL) {
                cout << "Position out of bounds!" << endl;
                delete temp;
                return;
            }
            temp->next = now->next;
            now->next = temp;
        }
        void reverse() {
            Node* prev = head;
            Node* now = prev->next;
            Node* next = now->next;
            prev->next = NULL;
            while(now != NULL) {
                next = now->next;
                now->next = prev;
                prev = now;
                now = next;   
            }   
            head = prev;
        }
        void recursion_reverse(Node* n) {
            if(n->next == NULL) {
                this->head = n;
                return;
            }
            recursion_reverse(n->next);
            (n->next)->next = n; 
            n->next = NULL;

        }
        int operator[](int index) {
            Node* now = head; 
            while(index > 0 && now != NULL) {
                now = now->next;
                index--;
            }
            if(now == NULL) {
                throw out_of_range("Index out of bounds!");
            }
            return now->data;
        }

    
};

//////////////////////////////////////////////////// THIS FOR QUEUE ///////////////////////////////////////////////

class Order {
    public:
        int data;
        Order* next = nullptr;
    public:
        Order(int value) : data(value) {}
};

class Queue {
    Order* head = nullptr;
    Order* tail = nullptr;
    public:
        void push(int x) {
            Order* temp = new Order(x); 
            if(head == nullptr) {
                head = temp;
                tail = temp;
                return;
            }
            tail->next = temp;
            tail = temp;
        } 
        void pop() {
            if(head == nullptr) throw runtime_error("Empty queue!!!");
            Order* temp = head;
            head = head->next;
            delete temp;
        }
        int front() {
            if(head == nullptr) throw runtime_error("Empty queue!!!");
            return head->data;
        }
        bool empty() {
            return !head;
        }
        ~Queue() {
            while(head != nullptr) {
                pop();
            }
        }
};

///////////////////////////////////////////////////////// THIS FOR STACK ///////////////////////////////////////////////////

class Link {
    public:
        Link(int data) : x(data) {}
        int x;
        Link* prev = NULL;
    
};

class Stack {
    Link* head = NULL;
    public:
        void push(int x) {
            Link* temp = new Link(x);
            temp->prev = head;
            head = temp;
        }
        void pop() {
            if(head == NULL) {
                throw runtime_error("Stack is empty nothing to remove");
            }
            Link* temp = head;
            head = head->prev;
            delete temp;
        }
        void top() const{
            if(head == NULL) {
                throw runtime_error("Nothing in stack");
            }
            cout << head->x << endl;
        }
        ~Stack() {
            while(head != NULL) {
                pop();
            }
        }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool paren() {
    string user;
    cin >> user;
    stack<char> open;
    for(auto u : user) {
        if(u == '(' || u == '{' || u == '[') open.push(u);
        else if(u == ')' || u == '}' || u == ']') {
            if(open.empty()) return false;
            switch(open.top()) {
                case '(':
                    if(u == ')') open.pop();
                    else return false;
                    break;
                case '{':
                    if(u == '}') open.pop();
                    else return false;
                    break;
                case '[':
                    if(u == ']') open.pop();
                    else return false;
                    break;
            }
        }
        else return false;
    }
    return open.empty();
}


///////////////////////////////////////////////////////////// THIS FOR BINARY SEARCH TREE /////////////////////////////////////////////////////

class BstNode {
    public:
        int data;
        BstNode* left = nullptr;
        BstNode* right = nullptr;
        BstNode(int value) : data(value) {}
};

class Bst {
    
    public:
    BstNode* root = nullptr;
    void delete_lrn(BstNode*& r) {
        if(r != nullptr) {
            delete_lrn(r->left);
            delete_lrn(r->right);
        }
        delete r;
        r = nullptr;
    }
    BstNode* left = nullptr;
    BstNode* right = nullptr;
    void delete_nlr(BstNode*& r) {
        if(r != nullptr) {
            left = r->left;
            right = r->right;
            delete r;
            r = nullptr;
            delete_nlr(left);
            delete_nlr(right);
        }
    }
    void level_order() const{
        if(root == nullptr) return;
        queue<BstNode*> q;
        q.push(root);
        BstNode* node = nullptr;
        while(!q.empty()) {
            node = q.front();
            cout << node->data << endl;
            if(node->left != nullptr)q.push(node->left);
            if(node->right != nullptr)q.push(node->right);
            q.pop();
        }       
    }

    int Max(BstNode* r) const{
        return r->right == nullptr ? r->data : Max(r->right);
    }
    int Min(BstNode* r) const{
        return r->left == nullptr ? r->data : Min(r->left);
    }
    bool search(int x, BstNode* root) const{
        return root == nullptr ? false : root->data == x ? true : x > root->data ? search(x, root->right) : search(x, root->left);
    }

    void recursion_insert(int x, BstNode*& r) const{     
        if(r == nullptr) {
            r = new BstNode(x);
            return;
        }
        else if(x > r->data) {
            recursion_insert(x, r->right);
        }
        else {
            recursion_insert(x, r->left);
        }
    }

    void insert(int x) {
        BstNode* node = new BstNode(x);
        if(root == nullptr) {
            root = node;
            return;
        }
        BstNode* temp = root;
        while(true) {
            if(node->data > temp->data) {
                if(temp->right != nullptr){
                    temp = temp->right;
                    continue;
                }
                temp->right = node;
                break;
            }
            if(node->data < temp->data) {
                if(temp->left != nullptr){
                    temp = temp->left;
                    continue;
                }
                temp->left = node;
                break;
            }
            delete node;
            break;
        }
    }
};


unique_ptr<int[]> generateSquares(int n) { 
    unique_ptr<int[]> result = make_unique<int[]>(n); 
    for(int i = 1; i <=n; i++) {
        result[i-1] = i*i; 
    }
    return result;
}



bool lessernode(BstNode* node, int data) {
    if(node == nullptr)return true;
    if(node->data < data && lessernode(node->left, data) && lessernode(node->right, data))return true;
    else return false;
}
bool greaternode(BstNode* node, int data) {
    if(node == nullptr)return true;
    if(node->data > data && greaternode(node->left, data) && greaternode(node->right, data))return true;
    else return false;
}
bool ibst(BstNode* root) {
    if(root == nullptr)return true;
    if(lessernode(root->left, root->data)&&greaternode(root->right, root->data)&&ibst(root->left)&&ibst(root->right))return true;
    else return false;
}


///////////////////////////// THIS FOR LINKEDLIST(CIRCULAR) ///////////////////////////////////////////////////////////////////

class Circular {
    public:
    int data;
    Circular* next = nullptr;
    Circular(int data) : data(data) {}
};

class CircularList {
    Circular* head = nullptr;
    Circular* tail = nullptr;
    public:
    void insert(int data) {
        Circular* temp = new Circular(data);
        if(head == nullptr) {
            head = temp;
            tail = temp;
            head->next = head;
            return;
        }
        tail->next = temp;
        tail = temp;
        tail->next = head;

    }
    void print() {
        Circular* temp = head;
        for(int i = 0; i < 10; i++) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};




int main() {
   
    

    return 0;
}