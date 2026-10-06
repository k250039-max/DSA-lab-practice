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
