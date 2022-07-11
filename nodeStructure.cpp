#include <iostream>
#include <cmath>
#include "node.cpp"

class NodeList{
    private:
        Node * head;
        Node * tail;
    public:
        NodeList(){head = tail = NULL;}
        void add(int value){
            Node * n = new Node(value);
            if(this->head == NULL){
                head = tail = n;
                return;
            }
            if(value < head->value){
                n->next = head;
                head->prev = n;
                head = n;
                return;
            }
            if(value > tail->value){
                n->prev = tail;
                tail->next = n;
                tail = n;
                return;
            }

            Node * iter = head;
            while(iter->value < value) iter = iter->next;

            iter->prev->next = n;
            n->prev = iter->prev;
            n->next = iter;
            iter->prev = n;
        }
        void print(){
            Node * iter = head;
            std::cout << "List: ";
            while (iter != NULL) {
                std::cout << iter->value << " ";
                iter = iter->next;
            }std::cout << std::endl;
        }
        void reversePrint(){
            Node * iter = tail;
            std::cout << "List in reverse order: ";
            while(iter != NULL) {
                std::cout << iter->value << " ";
                iter = iter->prev;
            }std::cout << std::endl;
        }

        void removeItemByValue(int value){
            Node * iter;
            if(abs(head->value - value) < abs(tail->value - value)) iter = head;
            else iter = tail;

            if(iter == head) while(iter->value != value) iter = iter->next;
            else while(iter->value != value) iter = iter->prev;

            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            delete iter;
        }

        void clear(){
            Node * iter;
            while (iter != NULL){
                iter = this->head;
                this->head = iter->next;
                delete iter;
            }
        }
};

class NodeTree{
    private:
        Node * root;
        static void inFix(Node * root){
            if(root == NULL) return;

            inFix(root->left);
            std::cout << root->value << " ";
            inFix(root->right);
        }
        static void preFix(Node * root){
            if(root == NULL) return;

            std::cout << root->value << " ";
            preFix(root->left);
            preFix(root->right);
        }
        static void postFix(Node * root){
            if(root == NULL) return;

            postFix(root->left);
            postFix(root->right);
            std::cout << root->value << " ";
        }
        static Node* getMax(Node * root){ 
            Node * iter = root;
            while(iter->right != NULL) iter = iter->right;

            return iter;
        }
        static Node* getMin(Node * root){
            Node * iter = root;
            while (iter->left != NULL) iter = iter->left;

            return iter;
        }
        static void mainClear(Node * root){
            if(root == NULL) return;
            mainClear(root->left);
            mainClear(root->right);
            delete root;
        }
        Node* mainRemove(Node * root , int data){
            if(root == NULL) return NULL;
            
            if(data < root->value) root->left = mainRemove(root->left , data);
            else if(data > root->value) root->right = mainRemove(root->right , data);
            else{
                if(root->left == NULL && root->right == NULL){
                    delete root;
                    root = NULL;
                }else if(root->left != NULL && root->right == NULL){
                    root->value = this->getMax(root->left)->value;
                    root->left = mainRemove(root->left , root->value);
                }else if(root->left == NULL && root->right != NULL){
                    root->value = this->getMin(root->right)->value;
                    root->right = mainRemove(root->right , root->value);
                }else{
                    root->value = this->getMax(root->left)->value;
                    root->left = mainRemove(root->left , root->value);
                }
            }
            
            return root;
        }
    public:
        NodeTree(){root = NULL;}
        void add(int value){
            Node * n = new Node(value);
            if(root == NULL){
                root = n;
                return;
            }

            Node * iter = root;
            bool left = true;
            while(true){
                if(iter->value == value) return; //to avoid duplicates in the tree

                if(value < iter->value) {
                    if(iter->left != NULL) iter = iter->left;
                    else break;
                }else{
                    if(iter->right != NULL) iter = iter->right;
                    else{
                        left = false;
                        break;
                    }
                }
            }

            if(left) iter->left = n;
            else iter->right = n;
        }
        void inOrderTraversal(){
            std::cout << "In Order Traversal: ";
            NodeTree::inFix(this->root);
            std::cout << std::endl;
        }
        void preOrderTraversal(){
            std::cout << "Pre Order Traversal: ";
            NodeTree::preFix(this->root);
            std::cout << std::endl;
        }
        void postOrderTraversal(){
            std::cout << "Post Order Traversal: ";
            NodeTree::postFix(this->root);
            std::cout << std::endl;
        }
        void print(){
            this->inOrderTraversal();
            this->preOrderTraversal();
            this->postOrderTraversal();
        }
        void remove(int value){mainRemove(this->root ,value);}
        void clear(){mainClear(this->root);}
};

class NodeArray{
    private:
        Node** list;
        int numberOfElements;
        int maxSize;
        void arrangeSize(){
                Node** a = new Node*[maxSize/2];
                for(int i=0;i<numberOfElements;i++){
                    a[i] = list[i];
                }

                delete list;
                list = a;
                maxSize /= 2;
        }
    public:
        NodeArray(){
            this->list = new Node*[2];
            this->numberOfElements = 0;
            this->maxSize = 2;
        }
        void add(int value){
            Node * n = new Node(value);
            
            if(numberOfElements < maxSize){
                list[numberOfElements] = n;
                numberOfElements++;
                return;
            }

            Node ** ar = new Node*[2 * maxSize];
            for(int i=0;i<numberOfElements;i++) ar[i] = list[i];

            delete list;
            list = ar;
            maxSize *= 2;
            numberOfElements++;
            list[numberOfElements - 1] = n;
        }
        void removeByValue(int value){
            int counter = 0;
            Node * iter = list[counter];
            while(iter->value != value){
                counter++;
                if(counter == numberOfElements) break;
                iter = list[counter];
            }

            if(counter == numberOfElements) return; // the case it does not exist in the list

            for(int i=counter;i<numberOfElements-1;i++){
                int t = list[i]->value;
                list[i]->value = list[i+1]->value;
                list[i+1]->value = t;
                iter = list[i+1];
            }
            delete iter;
            numberOfElements--;
            //////////decreasing the size of array if needed//////////////////
            if (numberOfElements != 1 && numberOfElements == maxSize / 2)
            arrangeSize();
        }
        int removeByIndex(int index){
            if(index < 0) index = abs(index);
            if(index >= numberOfElements) {
                std::cout << "Given index does not exist in the list." << std::endl;
                return 0;
            }
            int i = index;
            for(;i<numberOfElements-1;i++){
                int t = list[i]->value;
                list[i]->value = list[i+1]->value;
                list[i+1]->value = t;
            }

            int j = list[i]->value;
            delete list[i];
            numberOfElements--;

            if(numberOfElements == maxSize / 2 && numberOfElements != 1) arrangeSize();
            return j;
        }
        void print(){

            for(int i=0;i<numberOfElements;i++)
                std::cout << list[i]->value << " ";
            
            std::cout << std::endl;
        }
        int getNumberOfElements(){return numberOfElements;}
        int getElementByIndex(int index){return list[index]->value;}
        void clear(){
            for(int i=0;i<numberOfElements;i++){
                delete list[i];
            }
            delete list;
        }
};

class NodeStack{
    private:
        Node * head;
    public:
        NodeStack(){
            this->head = NULL;
        }
        void push(int value){
            Node * n = new Node(value);
            if(this->head == NULL) {
                this->head = n;
                return;
            }

            n->next = this->head;
            this->head = n;
        }
        int top(){return this->head->value;}
        void pop(){
            Node * iter = head;
            head = head->next;
            delete iter;
        }
        bool empty(){return head == NULL ? true : false;}
};






