#include <iostream>
#include <fstream>
#include "nodeStructure.cpp"

template <class T> void fillStructureFromFile(T&, std::string);
template <class T> void printStack(T&);
void myStackTest(std::string);
void myArrayTest(std::string);
void myLinkedListTest(std::string);
void myTreeTest(std::string);
void mainTestingProgram(std::string);



int main(int argc , char* argv[]){
    if(argv[1] == NULL) mainTestingProgram("numbers.txt");
    else mainTestingProgram(argv[1]);

    return 0;
}





void mainTestingProgram(std::string fileName){
    int choice;
    bool loop = true;
    while (loop){
        std::cout << "Choose a number (1. Stack , 2. Array , 3. List , 4. Tree): ";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {
            case 1: myStackTest(fileName);
            break;
            case 2: myArrayTest(fileName);
            break;
            case 3: myLinkedListTest(fileName);
            break;
            case 4: myTreeTest(fileName);
            break;
            default : loop = false;
            break;
        }

    }
}
template <class T> void fillStructureFromFile(T& structure , std::string fileName){
    std::ifstream myFile;
    myFile.open(fileName);
    int numberOfElements;
    myFile >> numberOfElements;
    for(int i=0;i<numberOfElements;i++) {
        int value;
        myFile >> value;
        structure.add(value);
    }

    myFile.close();
}
template <class T> void printStack(T& s){
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}
void myStackTest(std::string fileName){
    NodeStack nodeStack;
    std::ifstream myFile;
    myFile.open(fileName);
    int numberOfElements;
    myFile >> numberOfElements;
    for (int i=0;i<numberOfElements;i++){
        int temp;
        myFile >> temp;
        nodeStack.push(temp);
    }
    myFile.close();
    printStack(nodeStack);
}
void myArrayTest(std::string fileName){
    NodeArray nodeArray;
    fillStructureFromFile(nodeArray , fileName);
    nodeArray.print();
    std::cout << "The element at index 5: " << nodeArray.getElementByIndex(5) << std::endl;
    std::cout << "Element removed at index 5: " << nodeArray.removeByIndex(5) << std::endl;
    std::cout << "The last element is removed by its value: " << nodeArray.getElementByIndex(
        nodeArray.getNumberOfElements()-1
    ) << std::endl;
    nodeArray.removeByValue(nodeArray.getElementByIndex(nodeArray.getNumberOfElements()-1));
    std::cout << "After final removal: ";
    nodeArray.print();
    std::cout << std:: endl;
nodeArray.clear();
}
void myLinkedListTest(std::string fileName){
    NodeList nodeList;
    fillStructureFromFile(nodeList , fileName);
    nodeList.print();
    std::cout << "A random node is removed from the list by its value." << std::endl;
    nodeList.removeItemByValue(8);
    std::cout << "After removal: " << std::endl;
    nodeList.print();
    nodeList.reversePrint();

    nodeList.clear();
}
void myTreeTest(std::string fileName){
    NodeTree nodeTree;
    fillStructureFromFile(nodeTree , fileName);
    nodeTree.print();
    std::cout << "Value 24 is being deleted." << std::endl;
    nodeTree.remove(24);
    std::cout << "After the removal: " << std::endl;
    nodeTree.print();
    nodeTree.clear();
}

