using System;
using System.Collections.Generic;

class Node<T>
{
    public Node<T> lchild { get; set; }
    public T data { get; set; }
    public Node<T> rchild { get; set; }
    public int height { get; set; }

    public Node()
    {
        lchild = null;
        rchild = null;
        height = 1;
    }
    public Node(T data) : this()
    {
        this.data = data;
    }

    public Node(Node<T> other)
    {
        this.data = other.data;
        this.lchild = other.lchild;
        this.rchild = other.rchild;
        this.height = other.height;
    }
}

class AVL<T>
{
    public Node<T> root;

    public AVL()
    {
        root = null;
    }

    public int NodeHeight(Node<T> p)
    {
        if (p == null)
            return 0;

        int hl = (p.lchild != null) ? p.lchild.height : 0;
        int hr = (p.rchild != null) ? p.rchild.height : 0;

        return Math.Max(hl, hr) + 1;
    }

    public int BalanceFactor(Node<T> p)
    {
        if (p == null)
            return 0;

        int hl = (p.lchild != null) ? p.lchild.height : 0;
        int hr = (p.rchild != null) ? p.rchild.height : 0;

        return hl - hr;
    }

    public Node<T> LLRotation(Node<T> p)
    {
        Node<T> pl = p.lchild;
        Node<T> plr = pl.rchild;

        pl.rchild = p;
        p.lchild = plr;

        p.height = NodeHeight(p);
        pl.height = NodeHeight(pl);

        if (root == p)
            root = pl;

        return pl;
    }

    public Node<T> RRRotation(Node<T> p)
    {
        Node<T> pr = p.rchild;
        Node<T> prl = pr.lchild;

        pr.lchild = p;
        p.rchild = prl;

        p.height = NodeHeight(p);
        pr.height = NodeHeight(pr);

        if (root == p)
            root = pr;

        return pr;
    }

    public Node<T> LRRotation(Node<T> p)
    {
        Node<T> pl = p.lchild;
        Node<T> plr = pl.rchild;

        pl.rchild = plr.lchild;
        p.lchild = plr.rchild;

        plr.lchild = pl;
        plr.rchild = p;

        pl.height = NodeHeight(pl);
        p.height = NodeHeight(p);
        plr.height = NodeHeight(plr);

        if (p == root)
            root = plr;

        return plr;
    }

    public Node<T> RLRotation(Node<T> p)
    {
        Node<T> pr = p.rchild;
        Node<T> prl = pr.lchild;

        pr.lchild = prl.rchild;
        p.rchild = prl.lchild;

        prl.rchild = pr;
        prl.lchild = p;

        pr.height = NodeHeight(pr);
        p.height = NodeHeight(p);
        prl.height = NodeHeight(prl);

        if (root == p)
            root = prl;

        return prl;
    }

    public Node<T> rInsert(Node<T> p, T key)
    {
        if (p == null)
        {
            Node<T> t = new Node<T>(key);
            return t;
        }

        if (Comparer<T>.Default.Compare(key, p.data) < 0)
            p.lchild = rInsert(p.lchild, key);
        else if (Comparer<T>.Default.Compare(key, p.data) > 0)
            p.rchild = rInsert(p.rchild, key);

        p.height = NodeHeight(p);

        if (BalanceFactor(p) == 2 && BalanceFactor(p.lchild) == 1)
            return LLRotation(p);
        else if (BalanceFactor(p) == 2 && BalanceFactor(p.lchild) == -1)
            return LRRotation(p);
        else if (BalanceFactor(p) == -2 && BalanceFactor(p.rchild) == -1)
            return RRRotation(p);
        else if (BalanceFactor(p) == -2 && BalanceFactor(p.rchild) == 1)
            return RLRotation(p);

        return p;
    }

    public void Inorder(Node<T> p)
    {
        //recursive
        if (p != null)
        {
            Inorder(p.lchild);
            Console.Write(p.data + ", ");
            Inorder(p.rchild);
        }
        //iterative
        /*Stack<Node<T>> stack = new Stack<Node<T>>();
        Node<T> current = p;

        while (current != null || stack.Count > 0)
        {
            while (current != null)
            {
                stack.Push(current);
                current = current.lchild;
            }

            current = stack.Pop();
            Console.Write(current.data + ", ");
            current = current.rchild;
        }
        */
    }

    public void Preorder(Node<T> p)
    {
        //recursive
        if (p != null)
        {
            Console.Write(p.data + ", ");
            Preorder(p.lchild);
            Preorder(p.rchild);
        }
        //iterative
        /*if (p == null)
            return;

        Stack<Node<T>> stack = new Stack<Node<T>>();
        stack.Push(p);

        while (stack.Count > 0)
        {
            Node<T> current = stack.Pop();
            Console.Write(current.data + ", ");

            if (current.rchild != null)
                stack.Push(current.rchild);

            if (current.lchild != null)
                stack.Push(current.lchild);
        }
        */
    }

    public void Postorder(Node<T> p)
    {   //recursive
        if (p != null)
        {
            Postorder(p.lchild);
            Postorder(p.rchild);
            Console.Write(p.data + ", ");
        }
        //iterative
        /*
        Stack<Node<T>> stack1 = new Stack<Node<T>>();
        Stack<Node<T>> stack2 = new Stack<Node<T>>();

        stack1.Push(p);

        while (stack1.Count > 0)
        {
            Node<T> current = stack1.Pop();
            stack2.Push(current);

            if (current.lchild != null)
                stack1.Push(current.lchild);

            if (current.rchild != null)
                stack1.Push(current.rchild);
        }

        while (stack2.Count > 0)
        {
            Node<T> current = stack2.Pop();
            Console.Write(current.data + ", ");
        }
        */
    }
    public Node<T> InPre(Node<T> p)
    {
        if (p != null && p.lchild != null)
        {
            p = p.lchild;
            while (p.rchild != null)
                p = p.rchild;
        }

        return p;
    }

    public Node<T> InSucc(Node<T> p)
    {
        if (p != null && p.rchild != null)
        {
            p = p.rchild;
            while (p.lchild != null)
                p = p.lchild;
        }

        return p;
    }
    public Node<T> Delete(Node<T> p, T key)
    {
        if (p == null)
            return null;

        if (p.lchild == null && p.rchild == null)
        {
            if (p == root)
                root = null;

            return null;
        }

        if (Comparer<T>.Default.Compare(key, p.data) < 0)
            p.lchild = Delete(p.lchild, key);
        else if (Comparer<T>.Default.Compare(key, p.data) > 0)
            p.rchild = Delete(p.rchild, key);
        else
        {
            Node<T> q;

            if (NodeHeight(p.lchild) > NodeHeight(p.rchild))
            {
                q = InPre(p.lchild);
                p.data = q.data;
                p.lchild = Delete(p.lchild, q.data);
            }
            else
            {
                q = InSucc(p.rchild);
                p.data = q.data;
                p.rchild = Delete(p.rchild, q.data);
            }
        }

        p.height = NodeHeight(p);

        if (BalanceFactor(p) == 2 && BalanceFactor(p.lchild) == 1)
            return LLRotation(p);
        else if (BalanceFactor(p) == 2 && BalanceFactor(p.lchild) == -1)
            return LRRotation(p);
        else if (BalanceFactor(p) == -2 && BalanceFactor(p.rchild) == -1)
            return RRRotation(p);
        else if (BalanceFactor(p) == -2 && BalanceFactor(p.rchild) == 1)
            return RLRotation(p);
        else if (BalanceFactor(p) == 2 && BalanceFactor(p.lchild) == 0)
            return LLRotation(p);
        else if (BalanceFactor(p) == -2 && BalanceFactor(p.rchild) == 0)
            return RRRotation(p);

        return p;
    }
}

class Program
{
    static void Main(string[] args)
    {
        AVL<int> avl = new AVL<int>();
        avl.root = avl.rInsert(avl.root, 30);
        avl.root = avl.rInsert(avl.root, 20);
        avl.root = avl.rInsert(avl.root, 40);
        avl.root = avl.rInsert(avl.root, 10);
        avl.root = avl.rInsert(avl.root, 5);
        avl.root = avl.rInsert(avl.root, 50);

        Console.WriteLine("Inorder Traversal:");
        avl.Inorder(avl.root);
        Console.WriteLine();

        Console.WriteLine("Preorder Traversal:");
        avl.Preorder(avl.root);
        Console.WriteLine();

        Console.WriteLine("Postorder Traversal:");
        avl.Postorder(avl.root);
        Console.WriteLine();

        avl.root = avl.Delete(avl.root, 10);
        avl.root = avl.Delete(avl.root, 40);

        Console.WriteLine("Inorder Traversal after deletion:");
        avl.Inorder(avl.root);
        Console.WriteLine();
        Console.ReadLine();
    }
}