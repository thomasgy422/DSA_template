#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interver from l to r r inclusive
#define forr0(i, n) for (int i = (int)(n) - 1; i >= 0; --i)      // reverse 0 based.
#define forr1(i, n) for (int i = (int)(n); i >= 1; --i)          // reverse 1 based

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

class Node
{
public:
    int val;
    Node *next;
    Node *prev;
    Node(int v)
    {
        val = v;
        next = nullptr;
        prev = nullptr;
    }
};

// implement stack with doublely linkedlist
class Stack
{
public:
    Node *head;
    Node *cur;

    Stack()
    {
        head = new Node(-1);
        cur = head;
    }

    void push(int v)
    {
        Node *temp = cur;
        cur->next = new Node(v);
        cur = cur->next;
        cur->prev = temp;
    }

    void pop()
    {
        if (!is_empty())
        {
            cur = cur->prev;
            cur->next = nullptr;
        }
    }

    int peek()
    {
        if (cur != head)
        {
            return cur->val;
        }
        return -1;
    }

    bool is_empty()
    {
        return cur == head;
    }
};

// implement stack with array
class Stack1
{
public:
    int stack[10];
    int i;
    Stack1()
    {
        i = 0;
    }

    void push(int v)
    {
        stack[++i] = v;
    }

    void pop()
    {
        if (i > 0)
        {
            stack[i] = 0;
            i--;
        }
    }

    int peek()
    {
        if (!is_empty())
        {
            return stack[i];
        }
        return -1;
    }

    bool is_empty()
    {
        return i == 0;
    }
};

class Stack2
{
public:
    queue<int> q;

    // O(n) time
    void push(int v)
    {
        int n = sz(q);
        q.push(v);
        for (int i = 0; i < n; i++)
        {
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
    }

    void pop()
    {
        q.pop();
    }

    int peek()
    {
        q.front();
    }

    bool is_empty()
    {
        return sz(q) == 0;
    }
};

// support all the func of stack and getMin in O(1)
class MinStack
{
public:
    stack<int> s;
    stack<int> minStack;
    MinStack()
    {
    }

    void push(int v)
    {
        s.push(v);
        if (sz(minStack) == 0 || v <= minStack.top())
        {
            minStack.push(v);
        }
    }

    void pop()
    {
        int cur = s.top();
        s.pop();
        if (minStack.top() == cur)
        {
            minStack.pop();
        }
    }

    int getMin()
    {
        if (sz(s) > 0)
        {
            return minStack.top();
        }
        return -1;
    }

    int top()
    {
        if (!is_empty())
        {
            return s.top();
        }
        return -1;
    }

    bool is_empty()
    {
        return sz(s) > 0;
    }
};

int main()
{
    // Stack1 s;

    // s.push(1);
    // s.push(2);
    // cout << s.peek();

    MinStack ms;
    ms.push(3);
    ms.push(2);
    ms.push(2);
    ms.pop();
    ms.pop();
    cout << ms.getMin();

    return 0;
}

/*

*/
