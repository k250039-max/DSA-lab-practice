void reverse()
    {
        if(head==NULL || head==tail) return;
        Node *prev = NULL;
        Node* curr=head;
        while(curr!=NULL)
        {
            Node* nextnode = curr->next;
            curr->next=prev;
            prev = curr;
            curr = nextnode;
        }
        Node* temp = head;
        head = tail;
        tail = temp;
    }
    void specifiedreverse(int start,int end)
    {
        if(head==NULL || head==tail) return;
         Node* before = NULL;                       // FIX: NULL when start==1
        Node* first = head;                        // FIX: first node of the range
        for(int i=1;i<start;i++) { before = first; first = first->next; }
        Node* after = head;
        for(int i=1;i<=end;i++) after = after->next;
        Node* prev = after;
        Node* curr = before->next;
        for(int i= start;i<=end;i++)
        {
            Node* nextnode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextnode;
        }
        // Node* currbefore = head;
        // for(int i=0;i<start;i++) currbefore=currbefore->next;
        // Node* currafter = head;
        // for(int i=0;i<end;i++) currafter=currafter->next;
        if(before!=NULL)before->next=prev;
        else head=prev;
       if(after==NULL) tail = before ;
    }
void reverseInGroups(int k)
{
    if(head == NULL || head == tail || k <= 1) return;

    int n = 0;
    for(Node* t = head; t != NULL; t = t->next) n++;

    int groups = n / k;                 // number of full groups
    if(groups == 0) return;             // k larger than the list

    Node* prevEnd = NULL;               // last node of the previous group
    Node* curr = head;

    for(int g = 0; g < groups; g++)
    {
        Node* groupFirst = curr;        // becomes this group's last node
        Node* prev = NULL;
        for(int i = 0; i < k; i++)      // reverse k nodes
        {
            Node* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        // prev = new first of the group, curr = node after the group
        groupFirst->next = curr;        // connect to the next group (or leftover)
        if(prevEnd == NULL) head = prev;
        else prevEnd->next = prev;
        prevEnd = groupFirst;
    }

    if(n % k == 0) tail = prevEnd;      // no leftover: last group's end is the tail
}
