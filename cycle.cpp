bool removeCycle(Node* head) {
    Node *slow = head, *fast = head;

    // Phase 1: detect cycle (Floyd's)
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!fast || !fast->next) return false;  // no cycle

    // Phase 2: find cycle start
    slow = head;
    if (slow == fast) {
        // cycle starts at head: walk to the last node in the cycle
        while (fast->next != slow) fast = fast->next;
    } else {
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // fast is now the last node of the cycle
    fast->next = nullptr;
    return true;
}
