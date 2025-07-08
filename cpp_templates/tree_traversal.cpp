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

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v)
    {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

// recursive
void preorder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->val << "\n";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->val << "\n";
    inorder(root->right);
}

void postorder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->val << "\n";
}

// iterative
void preorderit(TreeNode *root)
{
    stack<TreeNode *> s;
    s.push(root);

    while (!s.empty())
    {
        TreeNode *cur = s.top();
        cout << cur->val << "\n";
        s.pop();
        if (cur->right != nullptr)
        {
            s.push(cur->right);
        }
        if (cur->left != nullptr)
        {
            s.push(cur->left);
        }
    }
}

void inorderit(TreeNode *root)
{
    stack<TreeNode *> s;
    while (!s.empty() || root != nullptr)
    {
        if (root != nullptr)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            root = s.top();
            cout << root->val;
            s.pop();
            root = root->right;
        }
    }
}

// void postorderit(TreeNode *root)
// {
//     stack<TreeNode *> s;
//     while (!s.empty()) {

//     }
// }

int main()
{
    TreeNode *root = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node6 = new TreeNode(6);
    TreeNode *node7 = new TreeNode(7);
    root->left = node2;
    root->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    preorderit(root);
    return 0;
}

/*

*/
