#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node* previous;
    Node(char d) : data(d), next(nullptr), previous(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    Node* tail;
    string error;

    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* t = head;
            head = head->next;
            delete t;
        }
    }

    void append(char d) {
        Node* n = new Node(d);
        if (!head) head = tail = n;
        else {
            tail->next = n;
            n->previous = tail;
            tail = n;
        }
    }

    void build(const string& expr) {
        for (int i = 0; i < expr.length(); i++)
            if (expr[i] != ' ' && expr[i] != '\t') append(expr[i]);
    }

    // single function: walks the list once using two stacks
    // returns false (and sets error) if the expression is invalid
    bool evaluate(double& result) {
        stack<double> nums;
        stack<char> ops;
        bool expectNum = true;   // true at start, after '(' or after an operator
        Node* cur = head;

        while (true) {
            char c = cur ? cur->data : '\0';   // '\0' marks the end of the list

            // number: join consecutive digit nodes into one number
            if ((c >= '0' && c <= '9') || c == '.') {
                string num = "";
                while (cur && ((cur->data >= '0' && cur->data <= '9') || cur->data == '.')) {
                    num += cur->data;
                    cur = cur->next;
                }
                nums.push(stod(num));
                expectNum = false;
                continue;
            }
            // opening bracket
            if (c == '(') {
                ops.push(c);
                expectNum = true;
                cur = cur->next;
                continue;
            }
            // unary minus: treat as 0 - x
            if (c == '-' && expectNum) {
                nums.push(0);
                ops.push('-');
                cur = cur->next;
                continue;
            }
            if (c != '+' && c != '-' && c != '*' && c != '/' && c != ')' && c != '\0') {
                error = string("Invalid character: ") + c;
                return false;
            }

            // here c is an operator, ')' or the end
            if (expectNum) {
                error = (c == '\0') ? "Unexpected end of expression" : "Invalid expression";
                return false;
            }

            // solve everything that must be done before c
            int p = (c == '+' || c == '-') ? 1 : 2;
            while (!ops.empty() && ops.top() != '(') {
                char t = ops.top();
                int pt = (t == '+' || t == '-') ? 1 : 2;
                if (c != ')' && c != '\0' && pt < p) break;

                double b = nums.top(); nums.pop();
                double a = nums.top(); nums.pop();
                ops.pop();
                if (t == '+') nums.push(a + b);
                else if (t == '-') nums.push(a - b);
                else if (t == '*') nums.push(a * b);
                else {
                    if (b == 0) { error = "Division by zero"; return false; }
                    nums.push(a / b);
                }
            }

            if (c == ')') {
                if (ops.empty()) { error = "Missing '('"; return false; }
                ops.pop();               // remove matching '('
                expectNum = false;
            }
            else if (c == '\0') {
                if (!ops.empty()) { error = "Missing ')'"; return false; }
                break;
            }
            else {
                ops.push(c);
                expectNum = true;
            }
            cur = cur->next;
        }

        result = nums.top();
        return true;
    }
};

int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    LinkedList list;
    list.build(input);

    double answer;
    if (list.evaluate(answer)) cout << "Answer: " << answer << endl;
    else cout << "Error: " << list.error << endl;
    return 0;
}
