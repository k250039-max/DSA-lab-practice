string infixToPrefix(string infix) {
    string prefix = "";
    Stack st(infix.length());

    for (int i = infix.length() - 1; i >= 0; i--) {
        char c = infix[i];

        if (isalnum(c)) {
            prefix = c + prefix;
        } else if (c == ')') {
            st.push(c);
        } else if (c == '(') {
            while (!st.isEmpty() && st.pop() != ')') {
                prefix = st.pop() + prefix;
            }
        } else if (isOperator(c)) {
            while (!st.isEmpty() && getPrecedence(st.peek()) >= getPrecedence(c)) {
                prefix = st.pop() + prefix;
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        prefix = st.pop() + prefix;
    }

    return prefix;
}
string infixToPostfix(string infix) {
    string postfix = "";
    Stack s(infix.length());

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.top() != '(') {
                char op = s.pop();
                postfix += op;
            }
            if (s.top() == '(') {
                s.pop();
            }
        } else {
            while (!s.isEmpty() && precedence(c) <= precedence(s.top())) {
                char op = s.pop();
                postfix += op;
            }
            s.push(c);
        }
    }
    while (!s.isEmpty()) {
        char op = s.pop();
        postfix += op;
    }
    return postfix;
}
