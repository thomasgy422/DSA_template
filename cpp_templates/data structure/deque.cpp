#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>

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

// implement deque with doubly linkedlist
class Deque
{
public:
    Node *head;
    Node *end;
    int size;
    Deque()
    {
        head = nullptr;
        end = nullptr;
        size = 0;
    }

    void push_back(int v)
    {
        Node *temp = new Node(v);
        if (is_empty())
        {
            head = temp;
            end = temp;
        }
        else
        {
            end->next = temp;
            temp->prev = end;
            end = end->next;
        }
        size++;
    }

    void pop_back()
    {
        if (!is_empty())
        {
            end = end->prev;
            end->next = nullptr;
            size--;
        }
    }

    void push_front(int v)
    {
        Node *temp = new Node(v);
        if (is_empty())
        {
            head = temp;
            end = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        size++;
    }

    void pop_front()
    {
        if (!is_empty())
        {
            Node *temp = head;
            head = head->next;
            temp->next = nullptr;
            head->prev = nullptr;
        }
    }

    int get_front()
    {
        if (!is_empty())
        {
            return head->val;
        }
        return -1;
    }

    int get_back()
    {
        if (!is_empty())
        {
            return end->val;
        }
        return -1;
    }

    bool is_empty()
    {
        return (head == nullptr) || (end == nullptr);
    }

    int get_size()
    {
        return size;
    }
};

// implement deque with array
const int mx = 10;
class Deque1
{
public:
    int arr[mx];
    int l;
    int r;
    int size;
    Deque1()
    {
        l = 0;
        r = 0;
        size = 0;
    }

    bool is_empty()
    {
        return size == 0;
    }

    int get_size()
    {
        return size;
    }

    void push_back(int v)
    {
        if (size < mx)
        {
            if (l == r && arr[r] == 0)
            {
                arr[r] = v;
            }
            else
            {
                r++;
                if (r == mx)
                {
                    r = 0;
                }
                arr[r] = v;
            }
            size++;
        }
    }

    void pop_back()
    {
        if (!is_empty())
        {
            arr[r] = 0;
            r--;
            if (r < 0)
            {
                r = mx - 1;
            }
            size--;
        }
    }

    void push_front(int v)
    {
        if (size < mx)
        {
            if (l == r && arr[l] == 0)
            {
                arr[l] = v;
            }
            else
            {
                l--;
                if (l == -1)
                {
                    l = mx - 1;
                }
                arr[l] = v;
            }
            size++;
        }
    }

    void pop_front()
    {
        if (!is_empty())
        {
            arr[l] = 0;
            l++;
            if (l == mx)
            {
                l = 0;
            }
            size--;
        }
    }

    int get_back()
    {
        if (!is_empty())
        {
            return arr[r];
        }
        return -1;
    }

    int get_front()
    {
        if (!is_empty())
        {
            return arr[l];
        }
        return -1;
    }
};

int main()
{
    Deque1 dq;

    dq.push_back(2);
    dq.push_front(2);
    dq.push_back(5);
    dq.pop_back();
    dq.push_front(3);
    cout << dq.get_back() << " " << dq.get_size();

    return 0;
}

/*

    1 0 0
*/
