    // returns the node at position pos (1 = first), or nullptr if pos is invalid
    ExprNode* getNode(int pos) {
        if (pos < 1) return nullptr;
        ExprNode* c = head;
        for (int i = 1; c && i < pos; i++) c = c->next;
        return c;
    }

    // swaps the nodes at positions a and b by relinking pointers
    // returns false if either position is invalid
    bool swapNodes(int a, int b) {
        if (a == b) return getNode(a) != nullptr;
        if (a > b) { int t = a; a = b; b = t; }      // make sure x comes before y

        ExprNode* x = getNode(a);
        ExprNode* y = getNode(b);
        if (!x || !y) return false;

        ExprNode* xp = x->previous;
        ExprNode* xn = x->next;
        ExprNode* yp = y->previous;
        ExprNode* yn = y->next;

        if (xn == y) {                               // adjacent: xp x y yn -> xp y x yn
            y->previous = xp;
            y->next = x;
            x->previous = y;
            x->next = yn;
            if (xp) xp->next = y;
            if (yn) yn->previous = x;
        } else {                                     // xp x xn ... yp y yn -> xp y xn ... yp x yn
            y->previous = xp;
            y->next = xn;
            x->previous = yp;
            x->next = yn;
            if (xp) xp->next = y;
            xn->previous = y;
            yp->next = x;
            if (yn) yn->previous = x;
        }

        if (head == x) head = y;                     // fix head and tail
        if (tail == y) tail = x;
        return true;
    }
