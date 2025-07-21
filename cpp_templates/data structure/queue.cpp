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

// implement queue with doublely linkedlist
class Queue
{
public:
    Node *head;
    Node *end;

    Queue()
    {
        head = new Node(-1);
        end = head;
    }

    void push(int v)
    {
        Node *temp = end;
        end->next = new Node(v);
        end = end->next;
        end->prev = temp;
    }

    void pop()
    {
        if (!is_empty())
        {
            head = head->next;
            head->next = nullptr;
        }
    }

    int front()
    {
        if (!is_empty())
        {
            return head->val;
        }
        return -1;
    }

    bool is_empty()
    {
        return end == head;
    }
};

// implement queue with array
// O(1)
class Queue1
{
public:
    int queue[10];
    int i, j;
    Queue1()
    {
        i = 0;
        j = -1;
    }

    void push(int v)
    {
        queue[++j] = v;
    }

    void pop()
    {
        if (i <= j)
        {
            queue[i] = 0;
            i++;
        }
    }

    int front()
    {
        if (!is_empty())
        {
            return queue[i];
        }
        return -1;
    }

    bool is_empty()
    {
        return i > j;
    }
};

// implement queue with stacks
// O(1) average for all operation, each element is added/poped into each stack at most once.
class Queue2
{
public:
    stack<int> in;
    stack<int> out;

    void push(int v)
    {
        in.push(v);
    }

    void pop()
    {
        if (!is_empty())
        {
            if (sz(out) > 0)
            {
                out.pop();
                return;
            }
            else
            {
                while (sz(in) > 0)
                {
                    int temp = in.top();
                    in.pop();
                    out.push(temp);
                }
                out.pop();
            }
        }
    }

    int front()
    {
        if (!is_empty())
        {
            if (sz(out) == 0)
            {
                while (sz(in) > 0)
                {
                    int temp = in.top();
                    in.pop();
                    out.push(temp);
                }
            }
            return out.top();
        }
        return -1;
    }

    bool is_empty()
    {
        return (sz(in) == 0 && sz(out) == 0);
    }
};

// circular queue
class CircularQueue
{
public:
    int arr[5];
    int size, l, r;
    CircularQueue()
    {
        size = 0;
        l = 0;
        r = 0;
    }

    void push(int v)
    {
        if (size < 5)
        {
            arr[r] = v;
            r++;
            size++;
            if (r == 5)
            {
                r = 0;
            }
        }
    }

    void pop()
    {
        if (size > 0)
        {
            arr[l] = 0;
            l++;
            size--;
            if (l == 5)
            {
                l = 0;
            }
        }
    }

    int front()
    {
        if (size > 0)
        {
            return arr[l];
        }
        return -1;
    }

    bool is_empty()
    {
        return size == 0;
    }
};

int main()
{
    CircularQueue q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(5);
    q.push(6);
    q.pop();
    q.pop();
    q.push(4);
    q.push(7);
    cout << q.front();

    return 0;
}

/*

*/
