#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

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

const int mx = 10001;

// implement trie with array, less space and faster, recommended
class Trie
{
public:
    int arr[mx][26];
    int pass[mx];
    int end[mx];
    int cnt;

    Trie()
    {
        cnt = 1;
        init();
    }

    // insert s into trie
    void insert(string s)
    {
        int cur = 1;
        for (int i = 0; i < sz(s); i++)
        {
            int ord = s[i] - 'a';
            if (arr[cur][ord] == 0)
            {
                arr[cur][ord] = ++cnt;
            }
            cur = arr[cur][ord];
            pass[cur]++;
        }
        end[cur] = 1;
    }

    // remove s, check contains before remove
    void remove(string s)
    {
        if (contains(s))
        {
            int cur = 1;
            for (int i = 0; i < sz(s); i++)
            {
                int ord = s[i] - 'a';
                cur = arr[cur][ord];
                pass[cur]--;
                if (pass[cur] == 0)
                {
                    arr[cur][ord] = 0;
                    return;
                }
            }
            end[cur] = 0;
        }
    }

    // check if trie contains s
    bool contains(string s)
    {
        int cur = 1;
        for (int i = 0; i < sz(s); i++)
        {
            int ord = s[i] - 'a';
            if (arr[cur][ord] == 0)
            {
                return false;
            }
            cur = arr[cur][ord];
        }
        return end[cur] == 1;
    }

    // count word with prefix as s
    int prefix(string s)
    {
        int cur = 1;
        for (int i = 0; i < sz(s); i++)
        {
            int ord = s[i] - 'a';
            if (arr[cur][ord] == 0)
            {
                return false;
            }
            cur = arr[cur][ord];
        }
        return pass[cur];
    }

    void init()
    {
        memset(arr, 0, sizeof(arr));
        memset(pass, 0, sizeof(pass));
        memset(end, 0, sizeof(end));
    }
};

int main()
{
    Trie trie;
    trie.insert("abc");
    trie.insert("abcd");
    trie.insert("abcde");
    trie.remove("abcd");
    trie.remove("abc");
    cout << trie.contains("abc") << "\n";
    cout << trie.prefix("abc") << "\n";
    return 0;
}