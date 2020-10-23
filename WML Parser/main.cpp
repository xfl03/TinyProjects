#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Property {
    string name;
    string value;

    Property(string name, string value) {
        this->name = name;
        this->value = value;
    }
};

struct Node {
    string label;
    string content;
    vector<Property *> properties;
    vector<Node *> children;

    Node(string label) {
        this->label = label;
    }
};

void printDepth(int depth) {
    if(depth == 0) return;
    for (int i = 0; i < depth*2; ++i) {
        cout << " ";
    }
    //cout<<"|-";
}

void printNode(Node *node, int depth) {
    printDepth(depth);
    cout << node->label;
    for (Property *p:node->properties) {
        cout << " " << p->name << "=" << p->value;
    }
    cout << endl;
    if (!node->content.empty()) {
        printDepth(depth + 1);
        cout << node->content << endl;
    }
}

void dfs(Node *node, int depth) {
    printNode(node, depth);
    for (Node *n:node->children) {
        dfs(n, depth + 1);
    }
}

bool isBlank(char c) {
    return c == '\r' || c == '\n' || c == ' ' || c == '\t';
}

bool isContent(char c) {
    return c != '<' && c != '>' && c != '"' && c != '\'';
}

bool isToken(char c) {
    return !isBlank(c) && isContent(c);
}

int state = 0;
int pos = 0;
char ch = '\0';

void error() {
    cout << "Exception happened while parsing WML:" << endl;
    cout << "state = " << state << ", pos = " << pos << ", ch = " << ch << endl;
    exit(0);
}

void mismatch(string excepted, string found) {
    cout << "Label mismatch:" << endl;
    cout << "expected = " << excepted << ", found = " << found << endl;
    error();
}

Node *work;
stack<Node *> workingStack;

void newNode(string label) {
    //cout << "New node: " << label << endl;
    Node *ptr = new Node(label);
    if (work != nullptr) {
        work->children.push_back(ptr);
    }
    workingStack.push(ptr);
    work = ptr;
}

void newNode(char c) {
    string s;
    s += c;
    newNode(s);
}

void finishNode() {
    //cout << "Finish node: " << work->label << endl;
    workingStack.pop();
    work = workingStack.top();
}

int main() {
    //Input
    ifstream fs("test.wml");
    string s;
    char t;
    while (!fs.eof()) {
        fs.get(t);
        s += t;
    }
    fs.close();

    //Parse
    newNode("root");
    string label;
    string name;
    string value;
    for (char c:s) {
        ch = c;
        //cout << "state = " << state << ", pos = " << pos << ", ch = " << ch << endl;
        switch (state) {
            case 0:
                if (ch == '<') {
                    state = 2;
                } else {
                    error();
                }
                break;
            case 1:
                if (ch == '<') {
                    state = 17;
                } else if (!isBlank(c)) {
                    error();
                }
                break;
            case 2:
                if (isToken(c)) {
                    newNode(c);
                    state = 3;
                } else {
                    error();
                }
                break;
            case 3:
                if (isToken(c)) {
                    work->label += c;
                } else if (c == '>') {
                    state = 16;
                } else if (c == '/') {
                    state = 4;
                } else if (c == ' ') {
                    name = "";
                    state = 10;
                } else {
                    error();
                }
                break;
            case 4:
                if (c == '>') {
                    finishNode();
                    state = 1;
                } else {
                    error();
                }
                break;
            case 6:
                if (isContent(c)) {
                    work->content += c;
                } else if (c == '<') {
                    state = 7;
                } else {
                    error();
                }
                break;
            case 7:
                if (c == '/') {
                    state = 8;
                } else {
                    error();
                }
                break;
            case 8:
                if (isToken(c)) {
                    label = "";
                    label += c;
                    state = 9;
                } else {
                    error();
                }
                break;
            case 9:
                if (isToken(c)) {
                    label += c;
                } else if (c == '>') {
                    if (label != work->label) {
                        mismatch(work->label, label);
                    } else {
                        finishNode();
                        state = 1;
                    }
                } else {
                    error();
                }
                break;
            case 10:
                if (isToken(c)) {
                    name += c;
                    state = 11;
                } else {
                    error();
                }
                break;
            case 11:
                if (c == '=') {
                    state = 12;
                } else if (isToken(c)) {
                    name += c;
                } else {
                    error();
                }
                break;
            case 12:
                if (c == '"') {
                    value = "";
                    state = 13;
                } else if (c == '\'') {
                    value = "";
                    state = 15;
                } else {
                    error();
                }
                break;
            case 13:
                if (c == '"') {
                    Property *p = new Property(name, value);
                    work->properties.push_back(p);
                    state = 14;
                } else if (isContent(c)) {
                    value += c;
                } else {
                    error();
                }
                break;
            case 14:
                if (c == ' ') {
                    name = "";
                    state = 10;
                } else if (c == '/') {
                    state = 4;
                } else if (c == '>') {
                    state = 16;
                } else {
                    error();
                }
                break;
            case 15:
                if (c == '\'') {
                    Property *p = new Property(name, value);
                    work->properties.push_back(p);
                    state = 14;
                } else if (isContent(c)) {
                    value += c;
                } else {
                    error();
                }
                break;
            case 16:
                if (c == '<') {
                    state = 2;
                } else if (isToken(c)) {
                    work->content += c;
                    state = 6;
                } else if (!isBlank(c)) {
                    error();
                }
                break;
            case 17:
                if (c == '/') {
                    state = 8;
                } else if (isToken(c)) {
                    newNode(c);
                    state = 3;
                } else {
                    error();
                }
        }
        //cout << c;
        pos++;
    }
    if (workingStack.size() != 1) {
        mismatch(work->label, "");
    }

    //Output
    dfs(work, 0);

    return 0;
}
