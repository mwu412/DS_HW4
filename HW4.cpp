#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Tree {
private:
    class node {
    public:
        int key;
        node * left;
        node * right;
        node * up;
        node * down;
        node(int key) {
            this->key = key;
            left = right = up = down = NULL;
        }
    };
    node * root = NULL;
//    node * current = root;
    int n_node = 0;
    int count = 0;
    int width, height, x, y;
    int **arr;
public:
    void MakeMatrix() {
        n_node = 0;
        cin>> width >> height >> x >> y;
        arr = new int *[height];
        for (int j = 0; j < height; j++) {
            arr[j] = new int[width];
        }
        for (int m = 0; m < height; m++) {
            for (int n = 0; n < width; n++) {
                cin >> arr[m][n];
            }
        }
    }
    void Walk() {
        Walk(y, x, 4, root);
    }
    void Walk(int r, int c, int dir, node* current) {
        current = new node(arr[r][c]);
        n_node++;
        
        if (c - 1 >= 0 && arr[r][c - 1] != 0 && dir != 3) {    //L
            Walk(r, c - 1, 0, current->left);
        }
        if (r + 1 < height && arr[r + 1][c] != 0 && dir != 1) {    //D
            Walk(r + 1, c, 2, current->down);
        }
        if (c + 1 < width && arr[r][c + 1] != 0 && dir != 0) {    //R
            Walk(r, c + 1, 3, current->right);
        }
        if (r - 1 >= 0 && arr[r - 1][c] != 0 && dir != 2) {    //U
            Walk(r - 1, c, 1, current->up);
        }
        return;
    }
    void Preorder() {
        count = 0;
        Preorder(root);
    }
    void Preorder(node* search) {
        if (search) {
            if (count == n_node - 1) cout << search->key;
            else cout << search->key << ' ';
            count++;
            if (search->left) Preorder(search->left);
            if (search->down) Preorder(search->down);
            if (search->right) Preorder(search->right);
            if (search->up) Preorder(search->up);
        }
    }
    void Postorder() {
        count = 0;
        Postorder(root);
    }
    void Postorder(node* search) {
        if (search) {
            if (search->left) Postorder(search->left);
            if (search->down) Postorder(search->down);
            if (search->right) Postorder(search->right);
            if (search->up) Postorder(search->up);
            if (count == n_node - 1) cout << search->key;
            else cout << search->key << ' ';
            count++;
        }
    }
    void Levelorder() {
        count = 0;
        queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node* current = q.front();
            q.pop();
            if (count == n_node - 1) cout << current->key;
            else cout << current->key << ' ';
            count++;
            if (current->left) q.push(current->left);
            if (current->down) q.push(current->down);
            if (current->right) q.push(current->right);
            if (current->up) q.push(current->up);
        }
    }
};

int main() {
    int n_matrix;
    string str;
    cin >> n_matrix;
    for (int i = 0; i < n_matrix; i++) {
        Tree tree;
        tree.MakeMatrix();
        tree.Walk();
        cin >> str;
        if (str == "Level-order-traversal") tree.Levelorder();
        if (str == "Pre-order-traversal") tree.Preorder();
        if (str == "Post-order-traversal") tree.Postorder();
        cout << endl;
    }
    return 0;
}
