#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

/*********************OtherGLobalFunctions***********/

string intToString(int num) {
    string stringNum;
    int tempNum = num;
    int digits = 0;
    do {
        tempNum /= 10;
        digits++;
    } while (tempNum != 0);
    int m = 0;
    do {
        tempNum = (num / pow(10, digits - 1)) - (10 * static_cast<int>(num / pow(10, digits)));
        stringNum += tempNum + 48;
        digits--;
        m++;
    } while (digits != 0);
    return stringNum;
}

int lengthOfString(const string str) //calculates length of a string
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

bool compareStrings(const string str1, const string str2) //compares 2 strings
{
    int count = 0;
    for (int i = 0; ; i++)
    {
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            break;
        }
        else if (str1[i] == '\0' || str2[i] == '\0')
        {
            return false; //both strings have different length i.e. also unequal
        }
        if (str1[i] == str2[i])
        {
            count++;
        }
    }
    if (count == lengthOfString(str2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkForDouble(const string str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            return true;
        }
    }
    return false;
}

double stringToIntDouble(string stringNum) {
    bool isDouble = checkForDouble(stringNum);
    if (isDouble) {
        int digits = lengthOfString(stringNum);
        digits--;
        int intPart = 0;
        int i = 0;
        for (;; i++, digits--) {
            if (stringNum[i] == '.') {
                i++;
                break;
            }
            intPart *= 10;
            intPart += stringNum[i] - 48;
        }
        double floatPart = 0;
        for (; digits != 0; i++, digits--) {
            floatPart *= 0.1;
            floatPart += static_cast<double>((stringNum[i] - 48)) * 0.1;
        }
        return static_cast<double>(intPart) + floatPart;
    }
    else {
        int digits = lengthOfString(stringNum);
        int num = 0;
        for (int i = 0; digits != 0; i++, digits--) {
            num *= 10;
            num += stringNum[i] - 48;
        }
        return num;
    }
}

bool doesStringInclude(string mainStr, string subStr) {
    bool firstCharFound = false;
    int lengthOfSubStr = lengthOfString(subStr);
    int count = 0;
    for (int i = 0, j = 0; mainStr[i] != '\0'; i++) {
        if (subStr[j] == '\0') {
            break;
        }
        if (!firstCharFound) {
            if (mainStr[i] == subStr[j]) {
                firstCharFound = true;
            }
        }
        if (firstCharFound == true) {
            if (mainStr[i] == subStr[j]) {
                count++;
                j++;
            }
            else {
                firstCharFound = false;
                j = 0;
                count = 0;
            }
        }
    }
    if (count == lengthOfSubStr) {
        return true;
    }
    return false;
}

int indexOfSubstring(string mainStr, string subStr) {
    bool firstCharFound = false;
    int lengthOfSubStr = lengthOfString(subStr);
    int count = 0;
    int indexOfSubStr = 0;
    for (int i = 0, j = 0; mainStr[i] != '\0'; i++) {
        if (subStr[j] == '\0') {
            break;
        }
        if (!firstCharFound) {
            if (mainStr[i] == subStr[j]) {
                firstCharFound = true;
                indexOfSubStr = i;
            }
        }
        if (firstCharFound == true) {
            if (mainStr[i] == subStr[j]) {
                count++;
                j++;
            }
            else {
                firstCharFound = false;
                j = 0;
                count = 0;
            }
        }
    }
    return indexOfSubStr;
}


/*********************LinkedList*********************/

template <class T>
struct ListNode {
    T value;
    ListNode<T>* next;
    ListNode(T value) {
        this->value = value;
        next = NULL;
    }
    ListNode() {}
    T getData() {
        return value;
    }
    void setData(T value) {
        this->value = value;
    }
    ListNode<T>* getNext() {
        return next;
    }
    void addToData(T value) { //adds a value to value
        this->value += value;
    }
};

template <class T>
struct LinkedList {
    ListNode<T>* head;
    LinkedList() {
        head = NULL;
    }
    ListNode<T>* insert(T value) { //inserts at back of the node
        ListNode<T>* newNode = new ListNode<T>(value);
        if (head == NULL) {
            newNode->next = NULL;
            head = newNode;
            return newNode;
        }
        ListNode<T>* currentNode;
        currentNode = head;
        ListNode<T>* prevNode;
        prevNode = NULL;
        while (currentNode != NULL) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        newNode->next = NULL;
        prevNode->next = newNode;
        return newNode;
    }
    ListNode<T>* insert(T value, int index) {
        if (index < 0) {
            return NULL;
        }
        if (head == NULL) {
            if (index == 0) {
                ListNode<T>* newNode = new ListNode<T>(value);
                newNode->next = head; //head is NULL
                head = newNode;
                return newNode;
            }
            else {
                return NULL;
            }
        }
        int currentIndex = 1;
        ListNode<T>* currentNode = head;
        while (index > currentIndex && currentNode != NULL) {
            currentNode = currentNode->next;
            currentIndex++;
        }
        if (index > 0 && currentNode == NULL) {
            return NULL;
        }
        ListNode<T>* newNode = new ListNode<T>(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }
        return newNode;
    }
    int findNode(T value) {
        int currentIndex = 1;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentNode->value == value) {
                return currentIndex - 1;
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
        return -1;
    }
    T getValue(int index) {
        int currentIndex = 0;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentIndex == index) {
                return currentNode->value;
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
        return NULL;
    }
    void add(T value, int index) { //adds T in the index (not inser)
        int currentIndex = 0;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentIndex == index) {
                currentNode->addToData(value);
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
    }
    ListNode<T>* deleteNode(T value) { //return the node next of previous node when a node gets deleted
        ListNode<T>* previousNode = NULL;
        ListNode<T>* currentNode = head;
        while (currentNode && currentNode->value != value) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode) {
            if (previousNode) {
                previousNode->next = currentNode->next;
                delete currentNode;
                return previousNode->next;
            }
            else {
                head = currentNode->next;
                delete currentNode;
                return head;
            }
        }
        return NULL;
    }
    ListNode<T>* deleteNodeByIndex(int index) { //return the node next of previous node when a node gets deleted
        ListNode<T>* previousNode = NULL;
        ListNode<T>* currentNode = head;
        int currentIndex = 0;
        while (currentNode && index > currentIndex) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            currentIndex++;
        }
        if (currentNode) {
            if (previousNode) {
                previousNode->next = currentNode->next;
                delete currentNode;
                return previousNode->next;
            }
            else {
                head = currentNode->next;
                delete currentNode;
                return head;
            }
        }
        return NULL;
    }
    ListNode<T>* getHead() {
        return head;
    }
    void swapNodes(int index1, int index2) {
        if (index1 == index2) {
            return;
        }
        int indexFirstNode = 0;
        int indexSecondNode = 0;
        ListNode<T>* firstNode = head;
        ListNode<T>* secondNode = head;
        ListNode<T>* prevNodeIndex1 = NULL;
        ListNode<T>* prevNodeIndex2 = NULL;
        while (firstNode != NULL) {
            if (indexFirstNode == index1) {
                break;
            }
            prevNodeIndex1 = firstNode;
            firstNode = firstNode->next;
            indexFirstNode++;
        }
        while (secondNode != NULL) {
            if (indexSecondNode == index2) {
                break;
            }
            prevNodeIndex2 = secondNode;
            secondNode = secondNode->next;
            indexSecondNode++;
        }
        if (firstNode == NULL || secondNode == NULL) {
            return;
        }
        if (index1 > 0 && index2 > 0) { //if both the nodes are not being pointed by head
            if (index1 - index2 == -1) { //two consecutive nodes
                prevNodeIndex1->next = secondNode;
                firstNode->next = secondNode->next;
                secondNode->next = firstNode;
            }
            else if (index1 - index2 == 1) {//two consecutive nodes
                secondNode->next = firstNode->next;
                firstNode->next = secondNode;
                prevNodeIndex2->next = firstNode;
            }
            else {
                prevNodeIndex1->next = secondNode;
                ListNode<T>* tempNode = secondNode->next;
                secondNode->next = firstNode->next;
                firstNode->next = tempNode;
                prevNodeIndex2->next = firstNode;
            }
        }
        else if (index1 == 0) { //1st node is being pointed by head
            //index2>index1
            prevNodeIndex2->next = firstNode;
            ListNode<T>* tempNode = firstNode->next;
            firstNode->next = secondNode->next;
            secondNode->next = tempNode;
            head = secondNode;
        }
        else { //2nd node is being pointed by head
            //index1>index2
            prevNodeIndex1->next = secondNode;
            ListNode<T>* tempNode = secondNode->next;
            secondNode->next = firstNode->next;
            firstNode->next = tempNode;
            head = firstNode;
        }
    }
    void display() {
        if (head == NULL) {
            return;
        }
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            cout << currentNode->value << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
    void insertAtHead(T value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = head;
        head = newNode;
    }
    void makeNull() {
        ListNode<T>* currentNode = head;
        ListNode<T>* nextNode = NULL;
        while (currentNode != NULL) {
            nextNode = currentNode->getNext();
            delete currentNode;
            currentNode = nextNode;
        }
        head = NULL;
    }
    bool isEmpty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }
};

/*************************STACK_LL******************************/

template <class T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode() {
        next = NULL;
    }
    StackNode(T data) {
        this->data = data;
        next = NULL;
    }
};

template <class T>
struct Stack {
    StackNode<T>* top;
    Stack() {
        top = NULL;
    }
    void push(T value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
    }
    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return NULL;
        }
        StackNode<T>* tempNode;
        T tempData;
        tempNode = top;
        tempData = top->data;
        top = top->next;
        delete tempNode;
        return tempData;
    }
    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        return false;
    }
    void display() {
        if (top == NULL) {
            return;
        }
        StackNode<T>* currentNode;
        currentNode = top;
        while (currentNode != NULL) {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }
};

//***********************RUNTIME*STACK*************************/

template <class T>
struct RuntimeNode
{
    T data;
    int nodeAddress;
    RuntimeNode* next;
    RuntimeNode(T value, int nodeAddress) {
        this->data = value;
        this->nodeAddress = nodeAddress;
    }
};

template <class T>
struct RuntimeStack {
    RuntimeNode<T>* top;
    RuntimeStack() {
        top = NULL;
    }
    void push(T value, int nodeAddress) {
        RuntimeNode<T>* newNode = new RuntimeNode<T>(value, nodeAddress);
        newNode->next = top;
        top = newNode;
    }
    RuntimeNode<T>* pop() {
        if (isEmpty()) {
            cout << "RuntimeStack is empty" << endl;
            return NULL;
        }
        RuntimeNode<T>* tempNode;
        //T tempData;
        tempNode = top;
        //tempData = top->data;
        top = top->next;
        //delete tempNode;
        return tempNode;
    }
    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        return false;
    }
    void display() {
        if (top == NULL) {
            return;
        }
        RuntimeNode<T>* currentNode;
        currentNode = top;
        LinkedList<T> tempLL;
        while (currentNode != NULL) {
            tempLL.insertAtHead(currentNode->data);
            //cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
        ListNode<T>* tempNode;
        tempNode = tempLL.head;
        while (tempNode != NULL) {
            cout << tempNode->getData() << endl;
            tempNode = tempNode->next;
        }
    }
    void write(string outputFile) {
        ofstream outFile;
        outFile.open(outputFile);
        if (top == NULL) {
            return;
        }
        RuntimeNode<T>* currentNode;
        currentNode = top;
        LinkedList<T> tempLL;
        while (currentNode != NULL) {
            tempLL.insertAtHead(currentNode->data);
            //cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
        ListNode<T>* tempNode;
        tempNode = tempLL.head;
        while (tempNode != NULL) {
            outFile << tempNode->getData();
            if (tempNode->next == NULL) {

            }
            else {
                outFile << endl;
            }
            tempNode = tempNode->next;
        }
        outFile.close();
    }
};

/*************************STACK_ARR******************************/

template <class T>
class StackArr {
    T* arr;
    int size;
    int top;
public:
    StackArr() {
        arr = nullptr;
        size = 0;
        top = -1;
    }
    StackArr(int size) {
        arr = new T[size];
        this->size = size;
        top = -1;
    }
    void push(T value) {
        if (isFull()) {
            cout << "StackArr is full" << endl;
            return;
        }
        top++;
        arr[top] = value;
    }
    T pop() {
        if (isEmpty()) {
            cout << "StackArr is empty" << endl;
            return NULL;
        }
        T tempData;
        tempData = arr[top];
        top--;
        return tempData;
    }
    bool isFull() {
        if (top == size - 1) {
            return true;
        }
        else {
            return false;
        }
    }
    bool isEmpty() {
        return (top == -1);
    }
    void display() {
        int tempNum = top;
        while (tempNum != -1) {
            cout << arr[tempNum] << endl;
            tempNum--;
        }
    }
};

/************************QUEUE_LL*********************************/

template <class T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
    QueueNode() {
        next = NULL;
    }
    QueueNode(T data) {
        this->data = data;
        next = NULL;
    }
};

template <class T>
struct Queue {
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int numOfNodes;
    Queue() {
        front = NULL;
        rear = NULL;
        numOfNodes = 0;
    }
    void enqueue(T value) {
        QueueNode<T>* newNode = new QueueNode<T>(value);
        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode; //we need to change rear
        }
        numOfNodes++;
    }
    T dequeue() {
        QueueNode<T>* tempNode;
        T tempData;
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return NULL;
        }
        else {
            tempData = front->data;
            tempNode = front->next;
            delete front;
            front = tempNode;
            numOfNodes--;
            if (!numOfNodes) {
                rear = NULL;
            }
        }
        return tempData;
    }
    T peek() {
        T tempData;
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return NULL;
        }
        else {
            return front->data;
        }
    }
    bool isEmpty() {
        return !numOfNodes;
    }
    void makeNull() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    void display() {
        if (front == NULL) {
            return;
        }
        QueueNode<T>* currentNode;
        currentNode = front;
        while (currentNode != rear) {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        cout << currentNode->data << " ";
        cout << endl;
    }
};

/***************************VARIABLES*****************************/

template <class T>
struct Variables { //A linked list of Variables can be use for finding the variable and associated value 
    T value;
    string Name;
};

/********************SPECIAL*STACK*****************************/

template <class T>
class SpecialStack {
public:
    Queue<T> queue1;
    Queue<T> queue2;
    SpecialStack() {
        queue1.makeNull();
        queue2.makeNull();
    }
    bool isEmpty() {
        if (queue1.isEmpty()) {
            return true;
        }
        return false;
    }
    void push(T value) {
        if (queue1.isEmpty()) {
            queue1.enqueue(value);
            return;
        }
        while (!queue1.isEmpty()) {
            queue2.enqueue(queue1.dequeue());
        }
        queue1.enqueue(value);
        while (!queue2.isEmpty()) {
            queue1.enqueue(queue2.dequeue());
        }
    }
    T pop() {
        if (queue1.isEmpty()) {
            cout << "Special Stack is empty" << endl;
            return NULL;
        }
        return queue1.dequeue();
    }
    T peek() {
        if (queue1.isEmpty()) {
            cout << "Special Stack is empty" << endl;
            return NULL;
        }
        return queue1.peek();
    }
    void display() {
        queue1.display();
    }
};

string readFile(string);
string removeLines(string);
string prependLineAddress(string);
string checkIndentationErrors(string);

// Simply just read the file
// Use '\n' to sperate each line of code
string readFile(string a = "code.txt") {
    ifstream infile;
    infile.open(a);
    string str = "";
    char ch;
    while (!infile.eof()) {
        ch = infile.get();
        if (ch == '\xFF') {
            continue;
        }
        else {
            str += ch;
        }
    }
    infile.close();
    str += '\n';
    return str;
}

// Remove useless lines so line addressing is done properly
string removeLines(string code) {
    string temp = "";
    string codeToReturn = "";
    bool isBlankLine;
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '\n') {
            isBlankLine = true;
            for (int j = 0; temp[j] != '\0'; j++) {
                if (temp[j] == ' ' || temp[j] == '\t' || temp[j] == '\n') {
                    //do nothing
                }
                else {
                    isBlankLine = false;
                    break;
                }
            }
            if (isBlankLine) {
                //do nothing
            }
            else {
                codeToReturn += temp;
            }
            temp = "";
        }
        temp += code[i];
    }
    codeToReturn += "\n";
    return codeToReturn;
}

// This prepends a line address to every single line in program
string prependLineAddress(string code) {
    int lineNumInt = 100;
    string lineNumStr = "C" + intToString(lineNumInt);
    string codeToReturn = lineNumStr + "    ";
    for (int i = 0; code[i] != '\0'; i++) {
        codeToReturn += code[i];
        if (code[i] == '\n' && code[i + 1] == '\0') {
            break;
        }
        if (code[i] == '\n') {
            lineNumStr = "C" + intToString(++lineNumInt);
            codeToReturn += lineNumStr + "    ";
        }
    }
    return codeToReturn;
}

int getOutStackPrec(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 3;
    case '%':
    case '$':
    case '^':
        return 6;
    case '(':
        return 7;
    case ')':
        return 0;
    }
}

int getInStackPrec(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 4;
    case '%':
    case '$':
    case '^':
        return 5;
    case '(':
        return 0;
    }
}

string infixToPostfix(string expression) {
    SpecialStack<char> ss;
    string postfix = "";
    for (int i = 0; expression[i] != '\0'; i++) {
        if ((expression[i] >= 97 && expression[i] <= 122) || (expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 48 && expression[i] <= 57)) { //variable
            postfix += expression[i];
        }
        else if (ss.isEmpty()) {
            ss.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (ss.peek() != '(') {
                postfix += ss.pop();
            }
            ss.pop();
        }
        else if (getOutStackPrec(expression[i]) > getInStackPrec(ss.peek())) {
            ss.push(expression[i]);
        }
        else if (getOutStackPrec(expression[i]) <= getInStackPrec(ss.peek())) {
            while (getOutStackPrec(expression[i]) <= getInStackPrec(ss.peek())) {
                postfix += ss.pop();
            }
            ss.push(expression[i]);
        }
    }
    while (!ss.isEmpty()) {
        postfix += ss.pop();
    }
    return postfix;
}

template<class T>
T performOperation(T first, T second, char operand) {
    switch (operand) {
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
        return first / second;
    case '^':
    case '$':
        return pow(first, second);
    case '%':
        return static_cast<int>(first) % static_cast<int>(second);
    }
}

template<class T>
T Solving_PostfixExpression(string expression, LinkedList<T> values) {
    //cout << endl << endl << endl;
    //cout << expression << endl;
    //values.display();
    StackArr<T> stack(20);
    T temp1;
    T temp2;
    T tempOperation;
    int linkedListIndex = 0;
    for (int i = 0, j = 0; expression[i] != '\0'; i++) {
        if ((expression[i] >= 97 && expression[i] <= 122) || (expression[i] >= 65 && expression[i] <= 90)) { //variable
            stack.push(values.getValue(linkedListIndex));
            linkedListIndex++;
        }
        else if (expression[i] >= 48 && expression[i] <= 57) {
            string tempStr = "";
            while ((expression[i] >= 48 && expression[i] <= 57) || expression[i] == '.') {
                tempStr += expression[i];
                i++;
            }
            i--;
            stack.push(stringToIntDouble(tempStr));
        }
        else { //expression[i] == operand
            temp1 = stack.pop();
            temp2 = stack.pop();
            tempOperation = performOperation(temp2, temp1, expression[i]);
            stack.push(tempOperation);
        }
    }
    return stack.pop();
}

template <class T>
struct VariableStorage {
    string variableName;
    string type;
    T value;
    char alias;
    void display() {
        cout << type << " " << variableName << " = " << value << " alias: " << alias << endl;
    }
    template <class U>
    friend ostream& operator<<(ostream&, VariableStorage<U>&);
};

template <class U>
ostream& operator<<(ostream& ostreamObj, VariableStorage<U>& varStor) {
    ostreamObj << varStor.type << " " << varStor.variableName << " = " << varStor.value << " alias: " << varStor.alias << endl;
    return ostreamObj;
}

void assignAlias(LinkedList<VariableStorage<float>> vars) {
    ListNode<VariableStorage<float>>* varsNode = vars.getHead();
    char tempChar = 'A';
    while (varsNode != NULL) {
        varsNode->value.alias = tempChar;
        varsNode = varsNode->getNext();
        tempChar++;
    }
}

struct FunctionDeclaration {
    string lineNumber;
    string returnType;
    string functionName;
    string endLineNumber;
    LinkedList<string> argumentType;
    LinkedList<string> argumentVar;
    int noOfArguments;
    FunctionDeclaration() {
        noOfArguments = 0;
    }
    void display() {
        ListNode<string>* currentNode;
        ListNode<string>* currentNode2;
        currentNode = argumentType.getHead();
        currentNode2 = argumentVar.getHead();
        cout << lineNumber << " ";
        cout << returnType << " " << functionName << "(";
        while (currentNode != NULL) {
            cout << currentNode->getData() << " " << currentNode2->getData();
            if (currentNode2->next != NULL) {
                cout << ", ";
            }
            currentNode = currentNode->next;
            currentNode2 = currentNode2->next;
        }
        cout << ")";
        cout << " NoOfArgs: " << noOfArguments << "\t" << endLineNumber << endl;
    }
    friend ostream& operator<<(ostream& os, FunctionDeclaration& funcDec);
};

ostream& operator<<(ostream& os, FunctionDeclaration& funcDec) {
    ListNode<string>* currentNode;
    ListNode<string>* currentNode2;
    currentNode = funcDec.argumentType.getHead();
    currentNode2 = funcDec.argumentVar.getHead();
    os << funcDec.lineNumber << " ";
    os << funcDec.returnType << " " << funcDec.functionName << "(";
    while (currentNode != NULL) {
        os << currentNode->getData() << " " << currentNode2->getData();
        if (currentNode2->next != NULL) {
            os << ", ";
        }
        currentNode = currentNode->next;
        currentNode2 = currentNode2->next;
    }
    os << ")";
    os << " NoOfArgs: " << funcDec.noOfArguments << "\t" << funcDec.endLineNumber << endl;
    cout << endl;
    return os;
}

bool isFunction(string line, FunctionDeclaration& tempFd) {
    bool isVoid = false;
    bool spaceDetected = false;
    string returnType;
    string funcName;
    string temp = "";
    string lineNum = "";
    //string permanentReturnType;
    bool returnTypeFound = false;
    bool funcNameFound = false;
    int i = 0;
    for (; i < 4; i++) {
        lineNum += line[i];
    }
    tempFd.lineNumber = lineNum;
    while (line[i] == ' ') {
        i++;
    }
    //if (line[i+1] == '{' || line[i+1] == '}') {
    //    return false;
    //}
    for (; line[i] != '\0'; i++) {
        if (returnTypeFound == false && line[i] == '\n') {
            return false;
        }
        if (line[i] == ' ') {
            spaceDetected = true;
        }
        if (returnTypeFound == false) {
            if (spaceDetected) {
                if (compareStrings(temp, "float") || compareStrings(temp, "int") || compareStrings(temp, "void")) {
                    //permanentReturnType = returnType;
                    returnTypeFound = true;
                    spaceDetected = false;
                    if (compareStrings(temp, "void")) {
                        isVoid = true;
                    }
                }
                else {
                    return false;
                }
            }
            else {
                //spaceDetected = false;
                temp += line[i];
            }
        }
        else {
            break;
        }
    }
    tempFd.returnType = temp;
    temp = "";
    for (; line[i] != '\0'; i++) {
        if (line[i] == ' ') {
            continue;
        }
        else if (line[i] == '(') {
            if (line[i + 1] == ')') {
                tempFd.functionName = temp;
                return true;
            }
            i++;
            break;
        }
        else if (line[i] == '\n') {
            return false;
        }
        else if (line[i] == '=') {
            return false;
        }
        else {
            temp += line[i];
        }
    }
    tempFd.functionName = temp;
    temp = "";
    string tempArgType;
    string tempVarName;
    spaceDetected = false;
    for (; line[i] != '\0'; i++) {
        if (line[i] == ' ') {
            spaceDetected = true;
        }
        if (spaceDetected == false) {
            temp += line[i];
        }
        if (spaceDetected == true) {
            if (compareStrings(temp, "float") || compareStrings(temp, "int")) {
                tempArgType = temp;
                temp = "";
                for (;; i++) {
                    if (line[i] == ' ') {
                        continue;
                    }
                    if (line[i] == ')') {
                        tempVarName = temp;
                        tempFd.argumentType.insert(tempArgType);
                        tempFd.argumentVar.insert(tempVarName);
                        temp = "";
                        tempFd.noOfArguments++;
                        return true;
                    }
                    else if (line[i] == ',') {
                        tempVarName = temp;
                        tempFd.argumentType.insert(tempArgType);
                        tempFd.argumentVar.insert(tempVarName);
                        temp = "";
                        i++;
                        tempFd.noOfArguments++;
                        while (line[i] != ' ') {
                            i++;
                        }
                        break;
                    }
                    else {
                        temp += line[i];
                    }
                }
            }
            else {
                return false;
            }
            spaceDetected = false;
        }
    }
}

void findEndLineNum(string& code, FunctionDeclaration& tempFd) {
    bool isVoid = false;
    if (compareStrings(tempFd.returnType, "void")) {
        isVoid = true;
    }
    string temp;
    int i = 0;
    for (; code[i] != '\0'; i++) {
        temp = "";
        for (int j = i; j < i + 4; j++) {
            temp += code[j];
        }
        if (compareStrings(temp, tempFd.lineNumber)) {
            //cout << endl << temp << endl;
            break;
        }
        while (code[i] != '\n') {
            i++;
        }
    }
    //now the function declaration has been found
    //now finding the end line number
    for (; code[i] != '{'; i++) {

    }
    Stack<char> stack;
    //cout << endl << endl;
    //cout << code[i] << endl;
    stack.push(code[i]);
    i++;
    bool endLineDetected = false;
    for (; code[i] != '\0'; i++) {
        temp = "";
        if (endLineDetected) {
            for (int j = i; i < j + 4; i++) {
                temp += code[i];
            }
            while (code[i] == ' ') {
                i++;
            }
            endLineDetected = false;
        }
        if (code[i] == '\n') {
            endLineDetected = true;
        }
        if (code[i] == '{' || code[i] == '(') {
            stack.push(code[i]);
        }
        else if (code[i] == '}' || code[i] == ')') {
            stack.pop();
        }
        else {
            //do nothing
        }
        if (stack.isEmpty()) {
            tempFd.endLineNumber = temp;
            if (isVoid) {
                string tempStr2 = "";
                int j = 0;
                for (; j < i; j++) {
                    tempStr2 += code[j];
                }
                tempStr2 += "return ";
                for (; code[j] != '\0'; j++) {
                    tempStr2 += code[j];
                }
                code = tempStr2;
            }
            break;
        }
    }
}

void readFunctions(string& code, LinkedList<FunctionDeclaration>& functionsLL) {
    string line;
    line = "";
    for (int i = 0; code[i] != '\0'; i++) {
        FunctionDeclaration tempFd;
        line += code[i];
        if (code[i] == '\n') {
            if (isFunction(line, tempFd)) {
                findEndLineNum(code, tempFd);
                functionsLL.insert(tempFd);
            }
            line = "";
        }
    }
}

int navigateToLine(string code, string passedLineNum) {
    //string line = "";
    string lineNum = "";
    bool newLineDetected = true;
    for (int i = 0; code[i] != '\0'; i++) {
        //line += code[i];
        lineNum = "";
        if (newLineDetected) {
            for (int j = i; j < i + 4; j++) {
                lineNum += code[j];
            }
            newLineDetected = false;
        }
        if (compareStrings(lineNum, passedLineNum)) {
            return i;
        }
        for (; code[i] != '\n'; i++) {
            if (code[i] == '\0') {
                return -1;
            }
            newLineDetected = true;
        }
    }

}

string ignoreLineNum(string& line) { //removes line number from passed line and returns line number in another string
    string lineNum = "";
    string lineWithoutNumber = "";
    bool lineNumSaved = false;
    for (int i = 0; line[i] != '\0'; i++) {
        if (lineNumSaved == false) {
            for (int j = i; i < j + 4; i++) {
                lineNum += line[i];
            }
            while (line[i] == ' ') {
                i++;
            }
            lineNumSaved = true;
            i--;
        }
        else {
            lineWithoutNumber += line[i];
        }
    }
    line = lineWithoutNumber;
    return lineNum;
}

void checkForVariablesAssignment(string line, LinkedList<VariableStorage<float>>& mainVars) {
    string temp = "";
    int i = 0;
    VariableStorage<float> tempVar;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    for (; line[i] != '\0'; i++) {
        if (line[i] == ' ' || line[i] == '\t') {
            break;
        }
        temp += line[i];
    }
    if (compareStrings(temp, "float")) {
        tempVar.type = "float";
    }
    else if (compareStrings(temp, "int")) {
        tempVar.type = "int";
    }
    else {
        //cout << endl << line << endl;
        return;
    }
    while (line[i] == ' ') {
        i++;
    }
    temp = "";
    for (; line[i] != '\0'; i++) {
        while (line[i] == ' ') {
            i++;
        }
        if (line[i] == '=') {
            i++;
            break;
        }
        temp += line[i];
    }
    if (line[i] == '\0') {
        return;
    }
    tempVar.variableName = temp;
    while (line[i] == ' ') {
        i++;
    }
    temp = "";
    for (; line[i] != '\0'; i++) {
        if (line[i] == ';') {
            tempVar.value = stod(temp);
            mainVars.insert(tempVar);
            return;
        }
        temp += line[i];
    }
    return;
}

//VariableStorage<float> variables;

string checkForFunctionCall(string line, LinkedList<FunctionDeclaration>& functionsLL, string lineNum) {//, LinkedList<VariableStorage<float>>& mainVars) {
    bool isTheFuncDeclarationLine = false;
    ListNode<FunctionDeclaration>* tempFLLNode = functionsLL.head;
    while (tempFLLNode != NULL) {
        if (compareStrings(tempFLLNode->value.lineNumber, lineNum)) {
            isTheFuncDeclarationLine = true;
            break;
        }
        tempFLLNode = tempFLLNode->next;
    }
    if (isTheFuncDeclarationLine) {
        return "NULL";
    }
    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    while (node != NULL) {
        if (doesStringInclude(line, node->value.functionName)) {
            return node->value.lineNumber;
        }
        node = node->next;
    }
    return "NULL";
}

bool terminatingCondition(string line) {
    string temp = "";
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    for (; line[i] != '\0'; i++) {
        if (compareStrings(temp, "return")) {
            return true;
        }
        else if (compareStrings(temp, "print")) {
            while (line[i] == ' ') {
                i++;
            }
            temp = "";
        }
        temp += line[i];
    }
    return false;
}

bool isPurelyInteger(string value) { //returns true if string only has integers
    for (int i = 0; value[i] != '\0'; i++) {
        if (value[i] >= 48 && value[i] <= 57) {

        }
        else {
            return false;
        }
    }
    return true;
}

bool isVariable(string value) {
    for (int i = 0; value[i] != '\0'; i++) {
        if (value[i] >= 65 && value[i] <= 90) {
            continue;
        }
        else if (value[i] >= 97 && value[i] <= 122) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

bool isIfElse(string line) {
    if (line[0] == '\0') {
        return false;
    }
    if (line[1] == '\0') {
        return false;
    }
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    if (line[i] == 'i' && line[i + 1] == 'f') {

    }
    else {
        return false;
    }
    bool openingBracket = false;
    bool closingBracket = false;
    for (int i = 2; line[i] != '\0'; i++) {
        if (line[i] == '(') {
            openingBracket = true;
        }
        if (line[i] == ')') {
            closingBracket = true;
        }
    }
    if (openingBracket && closingBracket) {
        return true;
    }
    else {
        return false;
    }
}

bool isPrintLine(string line) {
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    string tempStr = "";
    for (; line[i] != '\0'; i++) {
        if (line[i] == '\t' || line[i] == ' ') {
            break;
        }
        tempStr += line[i];
    }
    return compareStrings(tempStr, "print");
}

//FunctionDeclaration getFunc(string returnLineNum, string code, LinkedList< FunctionDeclaration> functionsLL) {
//    ListNode<FunctionDeclaration>* fNode = functionsLL.getHead();
//    while (fNode != NULL) {
//        string startLine = fNode->value.lineNumber;
//        string endLine = fNode->value.endLineNumber;
//        string startLineInt = startLine[1]; +startLine[2] + startLine[3];
//        string endLineInt;
//        fNode = fNode->next;
//    }
//}

string assignAliasToExpression(string exp, LinkedList<VariableStorage<float>> vars) {
    string infix = "";
    string temp = ""; //exp is like abc-xyz
    bool operatorFound = false;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] >= 65 && exp[i] <= 90) {
            if (operatorFound) {
                temp += " ";
                operatorFound = false;
            }
        }
        else if (exp[i] >= 97 && exp[i] <= 122) {
            if (operatorFound) {
                temp += " ";
                operatorFound = false;
            }
        }
        else if (exp[i] >= 48 && exp[i] <= 57) {
            if (operatorFound) {
                temp += " ";
                operatorFound = false;
            }
        }
        else {
            temp += " ";
            operatorFound = true;
        }
        temp += exp[i];
    }
    exp = temp; // now exp is line abc - xyz
    temp = "";
    bool isVariable;
    for (int i = 0; exp[i] != '\0'; i++) {
        isVariable = false;
        if (exp[i] == ' ') {
            if (isPurelyInteger(temp)) {
                infix += temp;
                temp = "";
                continue;
            }
            else {
                if (lengthOfString(temp) > 1) { //it is a variable confirm
                    isVariable = true;
                }
                else {
                    if (temp[0] >= 65 && temp[0] <= 90) {
                        isVariable = true;
                    }
                    else if (temp[0] >= 97 && temp[0] <= 122) {
                        isVariable = true;
                    }
                    else if (temp[0] >= 48 && temp[0] <= 57) {
                        isVariable = true;
                    }
                    else {
                        //arithmetic operator
                        infix += temp[0];
                        temp = "";
                        continue;
                    }
                }
            }
        }
        if (isVariable) {
            //LinkedList<VariableStorage<float>> vars;
            ListNode<VariableStorage<float>>* varNode = vars.head;
            while (varNode != NULL) {
                if (compareStrings(varNode->value.variableName, temp)) {
                    infix += varNode->value.alias;
                    break;
                }
                varNode = varNode->next;
            }
            temp = "";
            continue;
        }
        temp += exp[i];
    }
    if (isPurelyInteger(temp)) {
        infix += temp;
    }
    else {
        ListNode<VariableStorage<float>>* varNode = vars.head;
        while (varNode != NULL) {
            if (compareStrings(varNode->value.variableName, temp)) {
                infix += varNode->value.alias;
                break;
            }
            varNode = varNode->next;
        }
    }
    return infix;
}

bool evaluateIfElse(string line, LinkedList<VariableStorage<float>> vars) {
    string typeOfExpression = "";
    string temp = "";
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    i++; i++; //to skip 'if'
    for (; line[i] != '\0'; i++) {
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '(') {
            i++;
        }
        if (line[i] == '=' || line[i] == '<' || line[i] == '>' || line[i] == '!') {
            if (line[i] == '=') {
                typeOfExpression += line[i];
            }
            else if (line[i] == '<') {
                typeOfExpression += line[i];
            }
            else if (line[i] == '>') {
                typeOfExpression += line[i];
            }
            else if (line[i] == '!') {
                typeOfExpression += line[i];
            }
            if (line[i + 1] == '=') {
                typeOfExpression += line[i + 1];
                i++;
            }
            i++;
            break;
        }
        temp += line[i];
    }
    string firstExp = temp;
    temp = "";
    for (; line[i] != '\0'; i++) {
        while (line[i] == ' ') {
            i++;
        }
        if (line[i] == ')') {
            break;
        }
        temp += line[i];
    }
    string secondExp = temp;
    //cout << endl << endl;
    //cout << firstExp << " " << typeOfExpression << " " << secondExp << endl << endl;
    //now the expressions have been created
    //now creating their postfix versions and evaluating them
    string newExpression = assignAliasToExpression(firstExp, vars);
    string postfixExpression = infixToPostfix(newExpression);
    LinkedList<float> tempLst;
    for (int i = 0; postfixExpression[i] != '\0'; i++) {
        if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
            ListNode<VariableStorage<float>>* tempNode = vars.head;
            while (tempNode != NULL) {
                if (postfixExpression[i] == tempNode->value.alias) {
                    //cout << tempNode->value.value << endl;
                    tempLst.insert(tempNode->value.value);
                    break;
                }
                tempNode = tempNode->next;
            }
        }
    }
    //cout << Solving_PostfixExpression(postfixExpression, tempLst);
    string firstExpSolved = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
    //second exp
    newExpression = assignAliasToExpression(secondExp, vars);
    postfixExpression = infixToPostfix(newExpression);
    LinkedList<float> tempLst2;
    for (int i = 0; postfixExpression[i] != '\0'; i++) {
        if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
            ListNode<VariableStorage<float>>* tempNode = vars.head;
            while (tempNode != NULL) {
                if (postfixExpression[i] == tempNode->value.alias) {
                    //cout << tempNode->value.value << endl;
                    tempLst2.insert(tempNode->value.value);
                    break;
                }
                tempNode = tempNode->next;
            }
        }
    }
    string secondExpSolved = intToString(Solving_PostfixExpression(postfixExpression, tempLst2));
    //now evaluating exps
    if (compareStrings(typeOfExpression, "=="))
    {
        return (stringToIntDouble(firstExpSolved) == stringToIntDouble(secondExpSolved));
    }
    if (compareStrings(typeOfExpression, ">="))
    {
        return (stringToIntDouble(firstExpSolved) >= stringToIntDouble(secondExpSolved));
    }
    if (compareStrings(typeOfExpression, "<="))
    {
        return (stringToIntDouble(firstExpSolved) <= stringToIntDouble(secondExpSolved));
    }
    if (compareStrings(typeOfExpression, ">"))
    {
        return (stringToIntDouble(firstExpSolved) > stringToIntDouble(secondExpSolved));
    }
    if (compareStrings(typeOfExpression, "<"))
    {
        return (stringToIntDouble(firstExpSolved) < stringToIntDouble(secondExpSolved));
    }
    if (compareStrings(typeOfExpression, "!="))
    {
        return (stringToIntDouble(firstExpSolved) != stringToIntDouble(secondExpSolved));
    }
}

int findElseStatement(string code, int i) {
    i -= 5;
    while (code[i] != '{') {
        i++;
    }
    StackArr<char> tempStk(20);
    tempStk.push(code[i]);
    i++;
    for (int j = i; ; j++) {
        if (tempStk.isEmpty()) {
            while (code[j] == ' ' || code[j] == '\t') {
                j++;
            }
            if (code[j] == '\n') {
                j++;
            }
            j--;
            //runTimeStack.display();
            //cout << endl << endl;
            return j;
        }
        if (code[j] == '{') {
            tempStk.push(code[j]);
        }
        if (code[j] == '}') {
            tempStk.pop();
        }
    }
    return -1;
}

bool isInMainFunc(int i, string mainFuncLine, string mainFuncEndLine, string code) {
    if (i >= navigateToLine(code, mainFuncLine) && i <= navigateToLine(code, mainFuncEndLine)) {
        return true;
    }
    return false;
}

void CreateRunTimeStack(string filename, string outputFile) {
    RuntimeStack<string> runTimeStack;
    LinkedList<FunctionDeclaration> functionsLL;
    int EBP = 1004;
    int ESP;
    ofstream outFile;
    outFile.open(outputFile, ios::trunc);
    outFile.close();
    //to renew the file^
    bool firstCall = false;
    string code = readFile(filename);
    code = removeLines(code);
    code = prependLineAddress(code);
    readFunctions(code, functionsLL);
    //cout << code;
    //ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    //while (node != NULL) {
    //    FunctionDeclaration temp = node->getData();
    //    temp.display();
    //    cout << endl << endl;
    //    node = node->getNext();
    //}
    //cout << code;
    //cout << endl << endl;
    //now we will first find the main function
    string mainFuncLine;
    string mainFuncEndLine;
    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    while (node != NULL) {
        FunctionDeclaration temp = node->getData();
        if (compareStrings(temp.functionName, "main")) {
            mainFuncLine = temp.lineNumber;
            mainFuncEndLine = temp.endLineNumber;
            //cout << endl << endl << temp.endLineNumber <<"xx"<<  endl << endl;
            break;
        }
        node = node->getNext();
    }
    string line;
    line = "";
    LinkedList<VariableStorage<float>> mainVars;
    LinkedList<VariableStorage<float>> nextFuncVars;

    int i = 0;
    i = navigateToLine(code, mainFuncLine);
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            break;
        }
        if (code[i] == '\n') {
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            checkForVariablesAssignment(line, mainVars);
            line = "";
        }
        else {
            line += code[i];
        }
    }
    assignAlias(mainVars);
    LinkedList<VariableStorage<float>> currentFuncVars = mainVars;

    i = navigateToLine(code, mainFuncLine);
    while (code[i] != '\n') {
        i++;
    }
    //now i is at the first line after main func
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            //cout << i << " " << mainFuncEndLine << endl;
            return;
            break;
        }
        if (code[i] == '\n') {
            //cout << line << endl;
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            string funcLine = checkForFunctionCall(line, functionsLL, lineNum);// , mainVars);
            if (compareStrings(funcLine, "NULL")) {
                if (terminatingCondition(line)) {
                    ListNode<VariableStorage<float>>* currFunVarNode = currentFuncVars.head;
                    while (currFunVarNode != NULL) {
                        currFunVarNode = currFunVarNode->next;
                    }
                    //runTimeStack.display();
                    runTimeStack.write(outputFile);
                    return;
                }
                else if (isIfElse(line)) {
                    //cout << endl << endl;
                    //cout << lineNum << " " << "\t\t" << line << endl;
                    //cout << endl << endl;
                    bool ifElseEvaluation = evaluateIfElse(line, currentFuncVars);
                    if (ifElseEvaluation == true) { //enter if statement
                        //do nothing
                    }
                    else { //enter else statement
                        i = findElseStatement(code, i);
                        //cout << "ELSE" << endl;
                        //cout << lineNum << " " << "\t\t" << line << endl;
                        //cout << code[i] << endl;
                        //cout << "ELSE" << endl;
                    }
                }
                else if (isPrintLine(line)) {
                    //cout << endl << line << endl;
                    string tempStr2 = "";
                    bool stringStarted = false;
                    int tempCount = 0;
                    while (line[tempCount] != '\"') {
                        tempCount++;
                    }
                    tempCount++;
                    int i = 0;
                    for (; line[tempCount] != '\0'; tempCount++) {
                        if (line[tempCount] == '\"') {
                            break;
                        }
                        else if (line[tempCount] == '\\') {//\' && line[tempCount + 1] == '\n') {
                            tempStr2 += '\n';
                            tempCount++;
                            continue;
                        }
                        else {
                            tempStr2 += line[tempCount];
                            i++;
                        }
                    }
                    //ofstream outFile;
                    //outFile.open(outputFile, ios::app);
                    //outFile << tempStr2;
                    //outFile.close();
                    //string tempStrr = readFile(outputFile);
                    //tempStrr = removeLines(tempStrr);
                    //outFile.open(outputFile, ios::trunc);
                    //outFile << tempStrr;
                    //outFile.close();
                }
            }
            else {
                LinkedList<VariableStorage<float>> nextFuncVars;
                ListNode<FunctionDeclaration>* funcNode = functionsLL.getHead();
                while (funcNode != NULL) {
                    if (compareStrings(funcLine, funcNode->getData().lineNumber)) {
                        break;
                    }
                    funcNode = funcNode->getNext();
                }
                VariableStorage<float>* tempVarStor;
                tempVarStor = new VariableStorage<float>;
                ListNode<string>* tempVarNames = new ListNode<string>;
                tempVarNames = funcNode->value.argumentVar.head;
                ListNode<string>* tempVarTypes = new ListNode<string>;
                tempVarTypes = funcNode->value.argumentType.head;
                int varNum = 0;
                bool funcCallStarted = false;
                string tempVar2 = "";
                for (int j = 0; line[j] != '\0'; j++) {
                    if (line[j] == '(') { //function call started
                        j++;
                        while (line[j] == ' ') {
                            j++;
                        }
                        funcCallStarted = true;
                    }
                    if (funcCallStarted) {
                        while (line[j] == ' ') {
                            j++;
                        }
                        if (line[j] == ')') {
                            if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                if (firstCall == true) {
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;
                                }
                                else {
                                    EBP = 1004;
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;

                                }
                            }
                            else if (isVariable(tempVar2)) {
                                //LinkedList<VariableStorage<float>> currentFuncVars = mainVars;
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                if (firstCall == true) {
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;
                                }
                                else {
                                    EBP = 1004;
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;
                                }
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                //cout << line << endl;
                                //cout << endl << endl << tempVar2 << endl << endl;
                                if (firstCall == true) {
                                    runTimeStack.push(tempVar2, EBP);
                                    runTimeStack.push(lineNum, EBP);
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;
                                }
                                else {
                                    EBP = 1004;
                                    runTimeStack.push(tempVar2, EBP);
                                    runTimeStack.push(lineNum, EBP);
                                    runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                    ESP = EBP;
                                    EBP = EBP - 4;
                                    EBP = EBP - 8;
                                }
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);
                            firstCall = true;
                            break;
                        }
                        if (line[j] == ',') {
                            if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else if (isVariable(tempVar2)) {
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    //cout << tempVar2 << " ";
                                    //tempNode->value.display();
                                    //cout << endl;
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);

                            tempVar2 = "";
                            continue;
                        }
                        tempVar2 += line[j];
                    }
                }
                assignAlias(nextFuncVars);
                currentFuncVars = nextFuncVars;
                i = navigateToLine(code, funcLine);
                i--;
            }
            line = "";
        }
        else {
            line += code[i];
        }
    }

    //ListNode<VariableStorage<float>>* node2 = mainVars.getHead();
    //while (node2 != NULL) {
    //    VariableStorage<float> temp = node2->getData();
    //    temp.display();
    //    cout << endl << endl;
    //    node2 = node2->getNext();
    //}
}

void ExecuteCode(string filename, string outputFile) {
    CreateRunTimeStack(filename, outputFile);
    //CreateRunTimeStack(filename, outputFile);
    LinkedList<FunctionDeclaration> functionsLL;
    int EBP = 1008;
    int ESP;
    ofstream outFile;
    outFile.open(outputFile, ios::trunc);
    outFile.close();
    //to renew the file^
    string code = readFile(filename);
    code = removeLines(code);
    code = prependLineAddress(code);
    readFunctions(code, functionsLL);
    //cout << code;
    //ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    //while (node != NULL) {
    //    FunctionDeclaration temp = node->getData();
    //    temp.display();
    //    cout << endl << endl;
    //    node = node->getNext();
    //}
    //cout << code;
    //cout << endl << endl;
    //now we will first find the main function
    string mainFuncLine;
    string mainFuncEndLine;
    RuntimeStack<string> runTimeStack;
    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    while (node != NULL) {
        FunctionDeclaration temp = node->getData();
        if (compareStrings(temp.functionName, "main")) {
            mainFuncLine = temp.lineNumber;
            mainFuncEndLine = temp.endLineNumber;
            //cout << endl << endl << temp.endLineNumber <<"xx"<<  endl << endl;
            break;
        }
        node = node->getNext();
    }
    string line;
    line = "";
    LinkedList<VariableStorage<float>> mainVars;
    LinkedList<VariableStorage<float>> nextFuncVars;
    LinkedList<string> lineNumbersList;
    LinkedList<LinkedList<VariableStorage<float>>> allVars;
    int i = 0;
    i = navigateToLine(code, mainFuncLine);
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            break;
        }
        if (code[i] == '\n') {
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            checkForVariablesAssignment(line, mainVars);
            line = "";
        }
        else {
            line += code[i];
        }
    }
    assignAlias(mainVars);
    LinkedList<VariableStorage<float>> currentFuncVars = mainVars;
    i = navigateToLine(code, mainFuncLine);
    while (code[i] != '\n') {
        i++;
    }
    //functionsLL.display();
    //now i is at the first line after main func
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            //cout << i << " " << mainFuncEndLine << endl;
            return;
        }
        if (code[i] == '\n') {
            //cout << line << endl;
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            string funcLine = checkForFunctionCall(line, functionsLL, lineNum);
            if (compareStrings(funcLine, "NULL")) {
                //cout << lineNum << " " << line << endl;
                if (terminatingCondition(line)) {
                    //cout << lineNum << " " << "\t\t" << line << endl;
                    if (!compareStrings(functionsLL.head->value.returnType, "void")) {
                        //cout << lineNum << " " << line << endl;
                        //runTimeStack.display();
                        //runTimeStack.write(outputFile);
                        //lineNumbersList.display();
                        //****************************************************//
                        //now we will solve the expressions
                        string expression = "";
                        string retFind = "";
                        int i = 0;
                        for (; line[i] != '\0'; i++) {
                            if (compareStrings(retFind, "return")) {
                                break;
                            }
                            while (line[i] == ' ' || line[i] == '\t') {
                                i++;
                            }
                            retFind += line[i];
                        }
                        for (; line[i] != '\0'; i++) {
                            while (line[i] == ' ' || line[i] == '\t') {
                                i++;
                            }
                            if (line[i] == ';') {
                                break;
                            }
                            expression += line[i];
                        }
                        //now we have the expression. Evaluating it now
                        if (isPurelyInteger(expression)) {
                            //expression = expression
                        }
                        else if (isVariable(expression)) {
                            ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                            while (tempNode != NULL) {
                                if (compareStrings(tempNode->value.variableName, expression)) {
                                    expression = intToString(tempNode->value.value);
                                    break;
                                }
                                tempNode = tempNode->next;
                            }
                            //expression = value
                        }
                        else { //if it is an expression
                            //string newExpression = assignAliasToExpression(expression, currentFuncVars);
                            //string postfixExpression = infixToPostfix(newExpression);
                            //LinkedList<float> tempLst;
                            //for (int i = 0; postfixExpression[i] != '\0'; i++) {
                            //    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                            //        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                            //        while (tempNode != NULL) {
                            //            if (postfixExpression[i] == tempNode->value.alias) {
                            //                //cout << tempNode->value.value << endl;
                            //                tempLst.insert(tempNode->value.value);
                            //                break;
                            //            }
                            //            tempNode = tempNode->next;
                            //        }
                            //    }
                            //}
                            ////cout << Solving_PostfixExpression(postfixExpression, tempLst);
                            //tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                            //runTimeStack.push(tempVar2, EBP);
                            //EBP = EBP - 4;
                        }
                        int x;
                        while (!lineNumbersList.isEmpty()) {
                            string returnLineNum = lineNumbersList.getHead()->getData();
                            x = navigateToLine(code, returnLineNum);
                            x += 4;
                            while (code[x] == ' ' || code[x] == '\t') {
                                x++;
                            }
                            string expression2 = "";
                            string retFind2 = "";
                            for (; code[x] != '\0'; x++) {
                                if (compareStrings(retFind2, "return")) {
                                    break;
                                }
                                else if (compareStrings(retFind2, "print")) {
                                    break;
                                }
                                while (code[x] == ' ' || code[x] == '\t') {
                                    x++;
                                }
                                retFind2 += code[x];
                            }
                            x++;
                            for (; code[x] != '\0'; x++) {
                                while (code[x] == ' ' || code[x] == '\t') {
                                    x++;
                                }
                                if (code[x] == ';') {
                                    break;
                                }
                                expression2 += code[x];
                            }
                            //cout << expression2 << endl;
                            //now we have expression2;
                            //now we have to replace the function part with the number that is returned
                            ListNode<FunctionDeclaration>* fNode = functionsLL.head;
                            int y;
                            while (fNode != NULL) {
                                if (doesStringInclude(expression2, fNode->value.functionName)) {
                                    y = indexOfSubstring(expression2, fNode->value.functionName);
                                    break;
                                }
                                fNode = fNode->next;
                            }
                            string expression3 = expression2;
                            for (int i1 = y; expression3[i1] != '\0'; i1++) {
                                expression3[i1] = NULL;
                                if (expression3[i1] == ')') {
                                    break;
                                }
                                //finalExpression += expression3[abc];
                            }
                            bool startAppending = false;
                            string finalExpression = "";
                            for (int i2 = 0; i2 != lengthOfString(expression3) + 1; i2++) {
                                if (i2 == y) {
                                    startAppending = true;
                                }
                                if (startAppending) {
                                    for (int i3 = 0; expression[i3] != '\0'; i3++) {
                                        finalExpression += expression[i3];
                                    }
                                    startAppending = false;
                                }
                                finalExpression += expression3[i2];
                            }
                            //cout << finalExpression << endl;
                            //expression3[y]+=
                            //FunctionDeclaration funcNodeCurr = getFunc(returnLineNum, code, functionsLL);
                            //for (int y = indexOfSubstring(expression2, ); expression2[y] != '\0'; y++) {
                            //}
                            //*******************************************//
                            LinkedList<VariableStorage<float>> currentFuncVars2 = allVars.head->value;
                            string newExpression = assignAliasToExpression(finalExpression, currentFuncVars2);
                            //cout << endl << endl << newExpression << endl << endl;
                            //currentFuncVars2.display();
                            string postfixExpression = infixToPostfix(newExpression);
                            LinkedList<float> tempLst;
                            for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                    ListNode<VariableStorage<float>>* tempNode = currentFuncVars2.head;
                                    while (tempNode != NULL) {
                                        if (postfixExpression[i] == tempNode->value.alias) {
                                            //cout << tempNode->value.value << endl;
                                            tempLst.insert(tempNode->value.value);
                                            break;
                                        }
                                        tempNode = tempNode->next;
                                    }
                                }
                            }
                            finalExpression = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                            expression = finalExpression;
                            //cout << finalExpression << endl;
                            allVars.deleteNodeByIndex(0);
                            //*******************************************//

                            lineNumbersList.deleteNodeByIndex(0);

                        }
                        ofstream outFile;
                        outFile.open(outputFile, ios::app);
                        outFile << expression;
                        outFile.close();
                    }
                    //****************************************************//
                    return;
                }
                else if (isIfElse(line)) {
                    //cout << endl << endl;
                    //cout << lineNum << " " << "\t\t" << line << endl;
                    //cout << endl << endl;
                    bool ifElseEvaluation = evaluateIfElse(line, currentFuncVars);
                    if (ifElseEvaluation == true) { //enter if statement
                        //do nothing
                    }
                    else { //enter else statement
                        i = findElseStatement(code, i);
                    }
                }
                else if (isPrintLine(line)) {
                    //cout << endl << line << endl;
                    string tempStr2 = "";
                    bool stringStarted = false;
                    int tempCount = 0;
                    while (line[tempCount] != '\"') {
                        tempCount++;
                    }
                    tempCount++;
                    int i = 0;
                    for (; line[tempCount] != '\0'; tempCount++) {
                        if (line[tempCount] == '\"') {
                            break;
                        }
                        else if (line[tempCount] == '\\') {//\' && line[tempCount + 1] == '\n') {
                            tempStr2 += '\n';
                            tempCount++;
                            continue;
                        }
                        else {
                            tempStr2 += line[tempCount];
                            i++;
                        }
                    }
                    ofstream outFile;
                    outFile.open(outputFile, ios::app);
                    outFile << tempStr2;
                    outFile.close();
                    //string tempStrr = readFile(outputFile);
                    //tempStrr = removeLines(tempStrr);
                    //outFile.open(outputFile, ios::trunc);
                    //outFile << tempStrr;
                    //outFile.close();
                }
                else {
                    //cout << lineNum << " " << line << endl;
                }
            }
            else {
                //cout << lineNum << " " << line << endl;
                lineNumbersList.insertAtHead(lineNum);
                LinkedList<VariableStorage<float>> nextFuncVars;
                ListNode<FunctionDeclaration>* funcNode = functionsLL.getHead();
                while (funcNode != NULL) {
                    if (compareStrings(funcLine, funcNode->getData().lineNumber)) {
                        break;
                    }
                    funcNode = funcNode->getNext();
                }
                VariableStorage<float>* tempVarStor;
                tempVarStor = new VariableStorage<float>;
                ListNode<string>* tempVarNames = new ListNode<string>;
                tempVarNames = funcNode->value.argumentVar.head;
                ListNode<string>* tempVarTypes = new ListNode<string>;
                tempVarTypes = funcNode->value.argumentType.head;
                int varNum = 0;
                bool funcCallStarted = false;
                string tempVar2 = "";
                for (int j = 0; line[j] != '\0'; j++) {
                    if (line[j] == '(') { //function call started
                        j++;
                        while (line[j] == ' ') {
                            j++;
                        }
                        funcCallStarted = true;
                        //cout << line[j] << line[j + 1] << line[j + 2] << endl;
                    }
                    if (funcCallStarted) {
                        while (line[j] == ' ') {
                            j++;
                        }
                        if (line[j] == ')') {
                            if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            else if (isVariable(tempVar2)) {
                                //LinkedList<VariableStorage<float>> currentFuncVars = mainVars;
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                //cout << line << endl;
                                //cout << endl << endl << tempVar2 << endl << endl;
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);
                            break;
                        }
                        if (line[j] == ',') {
                            if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else if (isVariable(tempVar2)) {
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    //cout << tempVar2 << " ";
                                    //tempNode->value.display();
                                    //cout << endl;
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);

                            tempVar2 = "";
                            continue;
                        }
                        tempVar2 += line[j];
                    }
                }
                allVars.insertAtHead(currentFuncVars);
                assignAlias(nextFuncVars);
                currentFuncVars = nextFuncVars;
                i = navigateToLine(code, funcLine);
                i--;
            }
            line = "";
        }
        else {
            line += code[i];
        }
    }
}

string checkIndentationErrors(string code) {
    bool indentationErrorDetected = false;
    Stack<char> indentationStack;
    char temp;
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '(' || code[i] == '{') {
            indentationStack.push(code[i]);
        }
        if (code[i] == ')' || code[i] == '}') {
            if (indentationStack.isEmpty()) {
                indentationErrorDetected = true;
                break;
            }
            temp = indentationStack.pop();
            if (code[i] == ')' && temp == '{') {
                indentationErrorDetected = true;
                break;
            }
            if (code[i] == '}' && temp == '(') {
                indentationErrorDetected = true;
                break;
            }
        }
    }
    if (!indentationStack.isEmpty()) {
        indentationErrorDetected = true;
    }
    if (indentationErrorDetected) {
        return "Indentation error detected";
    }
    else {
        return "Indentation error NOT detected";
    }
}

bool isAnArgument(string data) {
    if (lengthOfString(data) < 4) {
        return false;
    }
    string temp = "";
    int i = 0;
    for (; i < 4; i++) {
        temp += data;
    }
    if (compareStrings(temp, "EBP=")) {
        return false;
    }
    if (temp[0] == 'C' && (temp[1] >= 48 && temp[1] <= 57) && (temp[2] >= 48 && temp[2] <= 57) && (temp[3] >= 48 && temp[3] <= 57)) {
        return true;
    }
    return false;
}

string checkInfiniteLoop(string code) {
    LinkedList<FunctionDeclaration> functionsLL;
    int EBP = 1008;
    int ESP;
    static int functionCallCounter = 0;
    int i = 0;
    while (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') {
        i++;
    }
    string temp = "";
    for (int j = 0; j < 3; i++, j++) {
        temp += code[i];
    }
    string funcName = "";
    if (compareStrings(temp, "int")) {
        i--; i--; i--;
        string tempStr2 = "";
        for (int k = 0; k < i; k++) {
            tempStr2 += code[k];
        }
        tempStr2 += "void";
        for (int j = 0; j < 3; i++, j++) {
            //do nothing
        }
        for (int x = i; code[x] != '('; x++) {
            while (code[x] == ' ' || code[x] == '\t') {
                x++;
            }
            funcName += code[x];
        }
        for (int k = i; code[k] != '\0'; k++) {
            tempStr2 += code[k];
        }
        code = tempStr2;
    }
    else if (compareStrings(temp, "flo")) {
        i--; i--; i--;
        string tempStr2 = "";
        for (int k = 0; k < i; k++) {
            tempStr2 += code[k];
        }
        tempStr2 += "void";
        for (int j = 0; j < 5; i++, j++) {
            //do nothing
        }
        for (int x = i; code[x] != '('; x++) {
            while (code[x] == ' ' || code[x] == '\t') {
                x++;
            }
            funcName += code[x];
        }
        for (int k = i; code[k] != '\0'; k++) {
            tempStr2 += code[k];
        }
        code = tempStr2;
    }
    else {
        i--; i--; i--;
        string tempStr2 = "";
        for (int k = 0; k < i; k++) {
            tempStr2 += code[k];
        }
        tempStr2 += "void";
        for (int j = 0; j < 4; i++, j++) {
            //do nothing
        }
        for (int x = i; code[x] != '('; x++) {
            while (code[x] == ' ' || code[x] == '\t') {
                x++;
            }
            funcName += code[x];
        }
        for (int k = i; code[k] != '\0'; k++) {
            tempStr2 += code[k];
        }
        code = tempStr2;
    }
    string tempCode = code;
    tempCode = removeLines(code);
    tempCode = prependLineAddress(code);
    readFunctions(tempCode, functionsLL);
    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
    bool mainExists = false;
    while (node != NULL) {
        if (compareStrings(node->value.functionName, "main")) {
            mainExists = true;
        }
        node = node->next;
    }
    RuntimeStack<string> runTimeStack;
    //cout << endl << funcName << endl;
    //code += "\nvoid main()\n{\n\tMessage();\n}\n";
    if (!mainExists) {
        code += "\nvoid main()\n{\n\t";// Message(); \n}\n";
        code += funcName;
        code += "(); \n}\n";
    }
    code = removeLines(code);
    code = prependLineAddress(code);
    //cout << code;
    //cout << endl << endl;
    functionsLL.makeNull();
    readFunctions(code, functionsLL);
    //now we will first find the main function
    string mainFuncLine;
    string mainFuncEndLine;
    node = functionsLL.getHead();
    while (node != NULL) {
        FunctionDeclaration temp = node->getData();
        if (compareStrings(temp.functionName, "main")) {
            mainFuncLine = temp.lineNumber;
            mainFuncEndLine = temp.endLineNumber;
            //cout << endl << endl << temp.endLineNumber <<"xx"<<  endl << endl;
            break;
        }
        node = node->getNext();
    }
    string line;
    line = "";
    LinkedList<VariableStorage<float>> mainVars;
    LinkedList<VariableStorage<float>> nextFuncVars;

    i = 0;
    i = navigateToLine(code, mainFuncLine);
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            break;
        }
        if (code[i] == '\n') {
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            checkForVariablesAssignment(line, mainVars);
            line = "";
        }
        else {
            line += code[i];
        }
    }
    bool ifElseDet = false;
    assignAlias(mainVars);
    LinkedList<VariableStorage<float>> currentFuncVars = mainVars;

    i = navigateToLine(code, mainFuncLine);
    while (code[i] != '\n') {
        i++;
    }
    //now i is at the first line after main func
    for (; code[i] != '\0'; i++) {
        if (i == navigateToLine(code, mainFuncEndLine)) {
            return "This is NOT a recursive function";
            break;
        }
        if (code[i] == '\n') {
            //cout << line << endl;
            string lineNum = ignoreLineNum(line);
            //cout << lineNum << " " << line << endl;
            string funcLine = checkForFunctionCall(line, functionsLL, lineNum);// , mainVars);
            if (compareStrings(funcLine, "NULL")) {
                if (terminatingCondition(line)) {
                    ListNode<VariableStorage<float>>* currFunVarNode = currentFuncVars.head;
                    while (currFunVarNode != NULL) {
                        currFunVarNode = currFunVarNode->next;
                    }
                    runTimeStack.display();
                    return "This is NOT a recursive function";
                }
                else if (isIfElse(line)) {
                    ifElseDet = true;
                    //cout << endl << endl;
                    //cout << lineNum << " " << "\t\t" << line << endl;
                    //cout << endl << endl;
                    bool ifElseEvaluation = evaluateIfElse(line, currentFuncVars);
                    if (ifElseEvaluation == true) { //enter if statement
                        //do nothing
                    }
                    else { //enter else statement
                        i = findElseStatement(code, i);
                        //cout << "ELSE" << endl;
                        //cout << lineNum << " " << "\t\t" << line << endl;
                        //cout << code[i] << endl;
                        //cout << "ELSE" << endl;
                    }
                }
                else if (isPrintLine(line)) {
                    //cout << endl << line << endl;
                    string tempStr2 = "";
                    bool stringStarted = false;
                    int tempCount = 0;
                    while (line[tempCount] != '\"') {
                        tempCount++;
                    }
                    tempCount++;
                    int i = 0;
                    for (; line[tempCount] != '\0'; tempCount++) {
                        if (line[tempCount] == '\"') {
                            break;
                        }
                        else if (line[tempCount] == '\\') {//\' && line[tempCount + 1] == '\n') {
                            tempStr2 += '\n';
                            tempCount++;
                            continue;
                        }
                        else {
                            tempStr2 += line[tempCount];
                            i++;
                        }
                    }
                    //ofstream outFile;
                    //outFile.open(outputFile, ios::app);
                    //outFile << tempStr2;
                    //outFile.close();
                }
            }
            else {
                if (functionCallCounter > 1) {
                    if (ifElseDet == false) {
                        return "Infinite loop detected";
                    }
                    bool noArguments = true;
                    RuntimeStack<string> tempRunTimeStack;
                    while (!runTimeStack.isEmpty()) {
                        RuntimeNode<string>* tempRTN = runTimeStack.pop();
                        if (isAnArgument(tempRTN->data)) {
                            noArguments = false;
                        }
                        tempRunTimeStack.push(tempRTN->data, tempRTN->nodeAddress);
                    }
                    while (!tempRunTimeStack.isEmpty()) {
                        RuntimeNode<string>* tempRTN = tempRunTimeStack.pop();
                        runTimeStack.push(tempRTN->data, tempRTN->nodeAddress);
                    }
                    if (noArguments) {
                        return "Infinite loop detected";
                    }
                    //bool sameArguments = true;
                    //ListNode<VariableStorage<float>>* nodeA = currentFuncVars.head;
                    //ListNode<VariableStorage<float>>* nodeB =  nextFuncVars.head;
                    //while (nodeA != NULL) {
                    //    if (nodeB == NULL) {
                    //        break;
                    //    }
                    //    if (nodeA->value.value != nodeB->value.value) {
                    //        sameArguments = false;
                    //        break;
                    //    }
                    //    nodeA = nodeA->next;
                    //    nodeB = nodeB->next;
                    //}
                    //if (sameArguments) {
                    //    return "Infinite loop detected";
                    //}
                    //if (noArguments) {
                    //    return "Infinite loop detected";
                    //}
                }
                functionCallCounter++;
                LinkedList<VariableStorage<float>> nextFuncVars;
                ListNode<FunctionDeclaration>* funcNode = functionsLL.getHead();
                while (funcNode != NULL) {
                    if (compareStrings(funcLine, funcNode->getData().lineNumber)) {
                        break;
                    }
                    funcNode = funcNode->getNext();
                }
                //funcNode->value.display();
                VariableStorage<float>* tempVarStor;
                tempVarStor = new VariableStorage<float>;
                ListNode<string>* tempVarNames = new ListNode<string>;
                tempVarNames = funcNode->value.argumentVar.head;
                ListNode<string>* tempVarTypes = new ListNode<string>;
                tempVarTypes = funcNode->value.argumentType.head;
                int varNum = 0;
                bool funcCallStarted = false;
                string tempVar2 = "";
                for (int j = 0; line[j] != '\0'; j++) {
                    if (line[j] == '(') { //function call started
                        j++;
                        while (line[j] == ' ') {
                            j++;
                        }
                        funcCallStarted = true;
                    }
                    if (funcCallStarted) {
                        while (line[j] == ' ') {
                            j++;
                        }
                        if (line[j] == ')') {
                            if (tempVar2 == "") {
                                // skip
                                break;
                            }
                            else if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            else if (isVariable(tempVar2)) {
                                //LinkedList<VariableStorage<float>> currentFuncVars = mainVars;
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                //cout << line << endl;
                                //cout << endl << endl << tempVar2 << endl << endl;
                                runTimeStack.push(tempVar2, EBP);
                                runTimeStack.push(lineNum, EBP);
                                runTimeStack.push("EBP=" + intToString(EBP), EBP);
                                ESP = EBP;
                                EBP = EBP - 4;
                                EBP = EBP - 8;
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);
                            break;
                        }
                        if (line[j] == ',') {
                            if (isPurelyInteger(tempVar2)) {
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else if (isVariable(tempVar2)) {
                                ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                while (tempNode != NULL) {
                                    if (compareStrings(tempNode->value.variableName, tempVar2)) {
                                        tempVar2 = intToString(tempNode->value.value);
                                        break;
                                    }
                                    //cout << tempVar2 << " ";
                                    //tempNode->value.display();
                                    //cout << endl;
                                    tempNode = tempNode->next;
                                }
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            else { //if it is an expression
                                string newExpression = assignAliasToExpression(tempVar2, currentFuncVars);
                                string postfixExpression = infixToPostfix(newExpression);
                                LinkedList<float> tempLst;
                                for (int i = 0; postfixExpression[i] != '\0'; i++) {
                                    if ((postfixExpression[i] >= 65 && postfixExpression[i] <= 90) || (postfixExpression[i] >= 97 && postfixExpression[i] <= 122)) {
                                        ListNode<VariableStorage<float>>* tempNode = currentFuncVars.head;
                                        while (tempNode != NULL) {
                                            if (postfixExpression[i] == tempNode->value.alias) {
                                                //cout << tempNode->value.value << endl;
                                                tempLst.insert(tempNode->value.value);
                                                break;
                                            }
                                            tempNode = tempNode->next;
                                        }
                                    }
                                }
                                //cout << Solving_PostfixExpression(postfixExpression, tempLst);
                                tempVar2 = intToString(Solving_PostfixExpression(postfixExpression, tempLst));
                                runTimeStack.push(tempVar2, EBP);
                                EBP = EBP - 4;
                            }
                            tempVarStor = new VariableStorage<float>;
                            tempVarStor->type = tempVarTypes->value;
                            tempVarTypes = tempVarTypes->next;
                            tempVarStor->value = stringToIntDouble(tempVar2);
                            tempVarStor->variableName = tempVarNames->value;
                            tempVarNames = tempVarNames->next;
                            nextFuncVars.insert(*tempVarStor);

                            tempVar2 = "";
                            continue;
                        }
                        tempVar2 += line[j];
                    }
                }
                if (functionCallCounter > 1) {
                    //bool noArguments = true;
                    //RuntimeStack<string> tempRunTimeStack;
                    //while (!runTimeStack.isEmpty()) {
                    //    RuntimeNode<string>* tempRTN = runTimeStack.pop();
                    //    if (isAnArgument(tempRTN->data)) {
                    //        noArguments = false;
                    //    }
                    //    tempRunTimeStack.push(tempRTN->data, tempRTN->nodeAddress);
                    //}
                    //while (!tempRunTimeStack.isEmpty()) {
                    //    RuntimeNode<string>* tempRTN = tempRunTimeStack.pop();
                    //    runTimeStack.push(tempRTN->data, tempRTN->nodeAddress);
                    //}
                    //if (noArguments) {
                    //    return "Infinite loop detected";
                    //}
                    bool sameArguments = true;
                    ListNode<VariableStorage<float>>* nodeA = currentFuncVars.head;
                    ListNode<VariableStorage<float>>* nodeB = nextFuncVars.head;
                    while (nodeA != NULL) {
                        if (nodeB == NULL) {
                            break;
                        }
                        if (nodeA->value.value != nodeB->value.value) {
                            sameArguments = false;
                            break;
                        }
                        nodeA = nodeA->next;
                        nodeB = nodeB->next;
                    }
                    if (sameArguments) {
                        return "Infinite loop detected";
                    }
                }
                assignAlias(nextFuncVars);
                currentFuncVars = nextFuncVars;
                i = navigateToLine(code, funcLine);
                i--;
            }
            line = "";
        }
        else {
            line += code[i];
        }
    }
}

//string removeLines(string code) {
//    string temp = "";
//    string codeToReturn = "";
//    bool isBlankLine;
//    for (int i = 0; code[i] != '\0'; i++) {
//        if (code[i] == '\n') {
//            isBlankLine = true;
//            for (int j = 0; temp[j] != '\0'; j++) {
//                if (temp[j] == ' ' || temp[j] == '\t' || temp[j] == '\n') {
//                    //do nothing
//                }
//                else {
//                    isBlankLine = false;
//                    break;
//                }
//            }
//            if (isBlankLine) {
//                //do nothing
//            }
//            else {
//                codeToReturn += temp;
//            }
//            temp = "";
//        }
//        temp += code[i];
//    }
//    codeToReturn += "\n";
//    return codeToReturn;
//}


//int findElseStatement(string code, int i) {
//    i++;
//    while (code[i] != '{') {
//        i++;
//    }
//    StackArr<char> tempStk(20);
//    tempStk.push(code[i]);
//    i++;
//    for (int j = i; ; j++) {
//        if (tempStk.isEmpty()) {
//            while (code[j] != '{') {
//                j++;
//            }
//            //runTimeStack.display();
//            //cout << endl << endl;
//            return j;
//        }
//        if (code[j] == '{') {
//            tempStk.push(code[j]);
//        }
//        if (code[j] == '}') {
//            tempStk.pop();
//        }
//    }
//    return -1;
//}


//for (; line[tempCount] != '\0'; tempCount++) {
//    if (line[tempCount] == '\"') {
//        tempStk.push('\"');
//        stringStarted = true;
//        continue;
//    }
//    if (stringStarted) {
//        if (line[tempCount] == '\"') {// || line[tempCount] == ';') {
//            tempStk.pop();
//            //stringStarted = false;
//        }
//        else {
//            tempStr2 += line[tempCount];
//        }
//    }
//    if (tempStk.isEmpty()) {
//        break;
//    }
//}

//string checkForFunctionCall(string line, LinkedList<FunctionDeclaration>& functionsLL) {//, LinkedList<VariableStorage<float>>& mainVars) {
//    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
//    while (node != NULL) {
//        string temp = "";
//        int i = 0;
//        while (line[i] == ' ' || line[i] == '\t') {
//            i++;
//        }
//        for (; line[i] != '\0'; i++) {
//            if (compareStrings(temp, "return")) {
//                while (line[i] == ' ') {
//                    i++;
//                }
//                temp = "";
//            }
//            else if (compareStrings(temp, "print")) {
//                while (line[i] == ' ') {
//                    i++;
//                }
//                temp = "";
//            }
//            else if (compareStrings(temp, node->getData().functionName)) {
//
//                return node->getData().lineNumber;
//            }
//            temp += line[i];
//        }
//        node = node->next;
//    }
//    return "NULL";
//}



//string checkForFunctionCall(string line, LinkedList<FunctionDeclaration>& functionsLL) {//, LinkedList<VariableStorage<float>>& mainVars) {
//
//
//
//    ListNode<FunctionDeclaration>* node = functionsLL.getHead();
//    bool printFound = false;
//    bool returnFound = false;
//    while (node != NULL) {
//        string temp = "";
//        int i = 0;
//        while (line[i] == ' ' || line[i] == '\t') {
//            i++;
//        }
//        for (; line[i] != '\0'; i++) {
//            if (compareStrings(temp, "return")) {
//                returnFound = true;
//                while (line[i] == ' ') {
//                    i++;
//                }
//                temp = "";
//            }
//            else if (compareStrings(temp, "print")) {
//                printFound = true;
//                while (line[i] == ' ') {
//                    i++;
//                }
//                temp = "";
//            }
//            //else if (compareStrings(temp, node->getData().functionName)) {
//            else if (doesStringInclude(temp, node->getData().functionName)) {
//                if (returnFound || printFound) {
//                    return node->getData().lineNumber;
//                }
//            }
//            temp += line[i];
//        }
//        node = node->next;
//    }
//    return "NULL";
//}
