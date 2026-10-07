bool isPal(const string& s)
{
    int i = 0, j = s.size() - 1;
    while (i < j)
        if (s[i++] != s[j--]) return false;
    return true;
}

void longestPalindrome()
{
    if (head == NULL)
    {
        cout << "List is empty!" << endl;
        return;
    }
    string best = "";
    int bs = -1, be = -1, i = 0;
    for (Node* a = head; a != NULL; a = a->next, i++)
    {
        string cur = "";
        int j = i;
        for (Node* b = a; b != NULL; b = b->next, j++)
        {
            cur += to_string(b->data);
            if (cur.size() > best.size() && isPal(cur))
            {
                best = cur;
                bs = i;
                be = j;
            }
        }
    }
    cout << "Longest palindrome: " << best
         << " (nodes " << bs << " to " << be << ")" << endl;
}
