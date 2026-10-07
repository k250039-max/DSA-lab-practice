struct Node {
    int val;
    Node* next;
    Node* child;
    Node(int v) : val(v), next(nullptr), child(nullptr) {}
};

Node* flatten(Node* head) {
    Node* curr = head;
    while (curr) {
        if (!curr->child) {
            curr = curr->next;
            continue;
        }

        // find the tail of the child list
        Node* tail = curr->child;
        while (tail->next) {
            tail = tail->next;
        }

        // attach the old next after the child's tail
        tail->next = curr->next;

        // splice the child in after curr
        curr->next = curr->child;
        curr->child = nullptr;

        curr = curr->next;
    }
    return head;
}
