//
// Created by  sky on 2017/11/25.
//

#ifndef BITREE_BITREE_H
#define BITREE_BITREE_H

#endif //BITREE_BITREE_H



struct Node
{
    DataType data;
    Node *left;
    Node *right;

    Node(const DataType &d):data(d), left(NULL), right(NULL)
    {

    }

    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
};

class BiTree {
private:
    Node *root;

public:
    BiTree() {
        root = new Node();      // with head node
    }

    virtual ~BiTree() {
        Destroy(&root);
    }

    Node* GetRoot()
    {
        return root;
    }

    Node* InsertLeftNode(Node* current, DataType x)
    {
        if (current == NULL)
        {
            cout << "current node is null." << endl;
            return NULL;
        }

        Node *s = new Node();
        s->data = x;

        s->left = current->left;
        current->left = s;

        return current->left;
    }

    Node* InsertRightNode(Node* current, DataType x)
    {
        if (current == NULL)
        {
            cout << "current node is null." << endl;
            return NULL;
        }

        Node *s = new Node();
        s->data = x;

        s->right = current->right;
        current->right = s;

        return current->right;
    }

    Node* DeleteLeftTree(Node* current)
    {
        if (current == NULL || current->left == NULL)
        {
            cout << "current or current's left node is null." << endl;
            return NULL;
        }

        Destroy(&current->left);
        current->left = NULL;

        return  current;
    }

    Node* DeleteRightTree(Node* current)
    {
        if (current == NULL || current->right == NULL)
        {
            cout << "current or current's right node is null." << endl;
            return NULL;
        }

        Destroy(&current->right);
        current->right = NULL;

        return  current;
    }

    void Destroy(Node** root)
    {
        if ((*root) != NULL && (*root)->left != NULL)
        {
            Destroy(&(*root)->left);
        }

        if ((*root) != NULL && (*root)->right != NULL)
        {
            Destroy(&(*root)->right);
        }

        delete (*root);
    }

    void PreOrder(Node* root, void Visit(DataType item))
    {
        if (root != NULL)
        {
            Visit(root->data);
            PreOrder(root->left, Visit);
            PreOrder(root->right, Visit);
        }
    }

    void InOrder(Node* root, void Visit(DataType item))
    {
        if (root != NULL)
        {
            InOrder(root->left, Visit);
            Visit(root->data);
            InOrder(root->right, Visit);
        }
    }

    void PostOrder(Node* root, void Visit(DataType item))
    {
        if (root != NULL)
        {
            PostOrder(root->left, Visit);
            PostOrder(root->right, Visit);
            Visit(root->data);
        }
    }

    static void Visit(DataType item)
    {
        cout << '\t' << item;
    }

    void PrintTree(Node* root, int n)
    {
        if (root == NULL)
        {
            return;
        }

        PrintTree(root->right, n+1);

        for (int i=0; i<n; ++i)
        {
            cout << '\t';
        }

        if (n >=0)
        {
            cout << "----";
            cout << root->data << endl;
        }

        PrintTree(root->left, n+1);
    }


    bool PreOrderNotRecursion(Node* root, void Visit(DataType x))
    {
        if (root == NULL)
        {
            cout << "current node is null." << endl;
            return false;
        }

        stack<Node*> s;
        Node *p = NULL;

        // root node push
        s.push(root);

        while (!s.empty())
        {
            p = s.top();
            Visit(p->data);
            s.pop();                    // root node pop

            if (p->right != NULL)
            {
                s.push(p->right);       // right tree push
            }

            if (p->left != NULL)
            {
                s.push(p->left);        // left tree push
            }
        }

        cout << endl << "preorder not recursion success." << endl;
        return true;
    }

    bool InOrderNotRecursion(Node* root, void Visit(DataType x))
    {
        if (root == NULL)
        {
            cout << "current node is null." << endl;
            return false;
        }

        stack<Node*> s;
        Node *p = root;

        while (p != NULL /*first enter condition*/ || !s.empty()/*last node exit condition*/)
        {
            while (p != NULL)
            {
                s.push(p);
                p = p->left;
            }

            p = s.top();
            Visit(p->data);
            s.pop();

            if (p->right == NULL)
            {
                p = NULL;
            }
            else
            {
                p = p->right;
            }
        }

        cout << endl << "inorder not recursion success." << endl;
        return true;
    }

    bool PostOrderNotRecursion(Node* root, void Visit(DataType x))
    {
        if (root == NULL)
        {
            cout << "current node is null." << endl;
            return false;
        }

        stack<Node*> s;
        Node *p = root;
        Node *visited = NULL;

        while (p != NULL || !s.empty())
        {
            while (p != NULL)
            {
                s.push(p);
                p = p->left;
            }

            p = s.top();

            if (p->right == visited || p->right == NULL)
            {
                Visit(p->data);
                s.pop();
                visited = p;
                p = NULL;
            }
            else
            {
                p = p->right;
            }
        }

        cout << endl << "postorder not recursion success." << endl;
        return true;
    }

    bool LevelOrderTraverse(Node* root, void Visit(DataType x))
    {
        if (root == NULL)
        {
            cout << "current node is null." << endl;
            return false;
        }

        queue<Node*> q;
        Node *p = NULL;
        q.push(root);

        while (!q.empty())
        {
            p = q.front();
            Visit(p->data);
            q.pop();

            if (p->left != NULL)
            {
                q.push(p->left);
            }

            if (p->right != NULL)
            {
                q.push(p->right);
            }
        }

        cout << endl << "level order traverse success." << endl;
        return true;
    }

    int GetTreeLevel(Node* current)
    {
        if (current == NULL)
        {
            cout << "current node is null." << endl;
            return 0;
        }
        else
        {
            int deep_left = GetTreeLevel(root->left);
            int deep_right = GetTreeLevel(root->right);

            int deep_size = 1 + max(deep_left, deep_right);
            cout << endl << "get tree level with recursion. " + deep_size << endl;
            return deep_size;
        }
    }

    int GetTreeLevelNotRecursion()
    {
        int deep_size = 0;
        int deep_left = 0;
        int deep_right = 0;

        if (root == NULL)
        {
            cout << "root node is null." << endl;
            return deep_size;
        }

        queue<Node*> q;
        Node *p = NULL;
        q.push(root);

        while (!q.empty())
        {
            p = q.front();
            q.pop();

            if (p->left != NULL)
            {
                q.push(p->left);
                deep_left++;
            }

            if (p->right != NULL)
            {
                q.push(p->right);
                deep_right++;
            }
        }

        if (deep_left > deep_right)
        {
            deep_size += deep_left;
        }
        else
        {
            deep_size += deep_right;
        }

        cout << endl << "get tree level deep: " + deep_size << endl;
        return deep_size;
    }

    Node* SearchNodeByData(Node* current, DataType x)
    {
        Node *p = NULL;

        if (current == NULL)
        {
            cout << "current node is null, search fail." << endl;
            return NULL;
        }

        if (current->data == x)
        {
            cout << "current node matches: " << x << endl;
            return current;
        }

        if (current->left != NULL)
        {
            p = SearchNodeByData(current->left, x);

            if (p != NULL)
            {
                cout << "here just end the left recursion." << endl;
                return p;
            }
        }

        if (current->right != NULL)
        {
            p = SearchNodeByData(current->right, x);

            if (p != NULL)
            {
                cout << "here just end the right recursion." << endl;
                return p;
            }
        }

        return NULL;
    }

};
