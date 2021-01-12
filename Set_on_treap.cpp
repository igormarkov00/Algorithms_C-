#include <random>

int64_t GenerateRandom(int64_t left_bound = -1e18, int64_t right_bound = 1e18) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int64_t> dis(left_bound, right_bound);
    return dis(gen);
}

template <typename ValueType>
class Set {
public:
    struct Node {
        ValueType key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        int64_t priority = GenerateRandom();
        explicit Node(ValueType init_key);
        Node(const Node& other);
    };

    struct Treap {
        Treap() = default;
        Treap(const Treap& other);
        ~Treap();
        Node* Find(const ValueType& key) const;
        Node* LowerBound(const ValueType& key) const;
        void Insert(const ValueType& key);
        void Erase(const ValueType& key);

    private:
        friend class Set;
        friend class Set::iterator;
        Node* root_ = nullptr;
        Node* min_node = nullptr;
        Node* max_node = nullptr;
        size_t size_{};
        void CleanAll(Node* root);
        void DeepCopy(Node*& root, Node* other, Node* par);
        Node* FindImpl(Node* root, const ValueType& key) const;
        Node* LowerBoundImpl(Node* root, const ValueType& key, Node* cur_lb) const;
        Node* Successor(Node* cur_node) const;
        Node* Predecessor(Node* cur_node) const;
        void InsertImpl(Node*& root, Node* new_node, Node* parent);
        bool EraseImpl(Node*& root, const ValueType& key, Node* parent);
        void SetParentness(Node* cur_node, Node* parent);
        void SetMinNode();
        void SetMaxNode();
        void Split(Node* root, const ValueType& key, Node*& left_tree, Node*& right_tree);
        void Merge(Node*& root, Node* left_son, Node* right_son, Node* parent);
    };

    // 1
    Set() {}

    // 2
    template <typename InputIt>
    Set(InputIt fst, InputIt last) {
        for (;fst != last; ++fst) {
            tree_.Insert(*fst);
        }
    }

    // 3
    explicit Set(std::initializer_list<ValueType> init) : Set(init.begin(), init.end()) {
    }

    // 4
    Set(const Set& other) : tree_(other.tree_) {
    }
    
    // 5
    Set& operator=(const Set& other) {
        if (&other != this) {
            this->~Set();
            new (this) Set(other);
        }
        return *this;
    }

    // 7
    size_t size() const {
        return tree_.size_;
    }

    // 8
    bool empty() const {
        return !tree_.root_;
    }

    // 9
    void insert(const ValueType& value) {
        tree_.Insert(value);
    }

    // 10
    void erase(const ValueType& value) {
        tree_.Erase(value);
    }

    // 11
    class iterator {
    public:
        iterator() : node_(nullptr), it_tree_(nullptr) {}

        iterator& operator++() {
            node_ = it_tree_->Successor(node_);
            return *this;
        }
        iterator operator++(int) {
            iterator rv = *this;
            node_ = it_tree_->Successor(node_);
            return rv;
        }
        iterator& operator--() {
            node_ = it_tree_->Predecessor(node_);
            return *this;
        }
        iterator operator--(int) {
            iterator rv = *this;
            node_ = it_tree_->Predecessor(node_);
            return rv;
        }

        ValueType operator*() const {
            return node_->key;
        }
        const ValueType* operator->() const {
            return &(node_->key);
        }
        bool operator==(const iterator& other) const {
            return node_ == other.node_;
        }
        bool operator!=(const iterator& other) const {
            return node_ != other.node_;
        }
        
    private:
        friend class Set;
        iterator(Node* node, const Treap* tree) : node_(node), it_tree_(tree) {}
        Node* node_;
        const Treap *it_tree_;
    };

    iterator begin() const {
        return iterator(tree_.min_node, &tree_);
    }

    iterator end() const {
        return iterator(nullptr, &tree_);
    }

    // 12
    iterator find(const ValueType& value) const {
        return iterator(tree_.Find(value), &tree_);
    }

    // 13
    iterator lower_bound(const ValueType& value) const {
        return iterator(tree_.LowerBound(value), &tree_);
    }

    // 14 !!!!!!!!!!!!!!!!!!!!!
    bool CheckSetCorrectness() const {
        return tree_.root_ ? CheckImpl(tree_.root_, nullptr) : true;
    }
    bool CheckImpl(Node* cur_node, Node* parent) const {
        bool res = true;
        if (cur_node->left) {
            res &= CheckImpl(cur_node->left, cur_node);
        }
        if (cur_node->right) {
            res &= CheckImpl(cur_node->right, cur_node);
        }
        return res & (cur_node->parent == parent);
    }

private:
    Treap tree_;
};

// Node Implementation

template <typename ValueType>
Set<ValueType>::Node::Node(ValueType init_key) : key(init_key) {
}

template <typename ValueType>
Set<ValueType>::Node::Node(const Node& other) : key(other.key), priority(other.priority) {}

// Treap Implementation

template <typename ValueType>
Set<ValueType>::Treap::Treap(const Treap& other) : size_(other.size_) {
    DeepCopy(root_, other.root_, nullptr);
    SetMinNode();
    SetMaxNode();
}

template <typename ValueType>
Set<ValueType>::Treap::~Treap() {
    CleanAll(root_);
}

template <typename ValueType>
void Set<ValueType>::Treap::CleanAll(Node* root) {
    if (root) {
        CleanAll(root->left);
        CleanAll(root->right);
        delete root;
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::DeepCopy(Node*& root, Node* other, Node* parent) {
    if (!other) {
        return;
    }
    if (!root) {
        root = new Node(*other);
    }
    root->parent = parent;
    if (other->left) {
        root->left = new Node(*(other->left));
        DeepCopy(root->left, other->left, root);
    }
    if (other->right) {
        root->right = new Node(*(other->right));
        DeepCopy(root->right, other->right, root);
    }
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::Find(const ValueType& key) const {
    return FindImpl(root_, key);
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::FindImpl(Node* root,
                                                               const ValueType& key) const {
    if (!root || (!(key < root->key) && !(root->key < key))) {
        return root;
    }
    return FindImpl(key < root->key ? root->left : root->right, key);
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::LowerBound(const ValueType& key) const {
    return LowerBoundImpl(root_, key, nullptr);
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::LowerBoundImpl
        (Node* root, const ValueType& key, Node* cur_lb) const {
    if (!root) {
        return cur_lb;
    }
    if (!(key < root->key) && !(root->key < key)) {
        return root;
    }
    if (key < root->key && (!cur_lb || root->key < cur_lb->key)) {
        cur_lb = root;
    }
    return LowerBoundImpl(key < root->key ? root->left : root->right, key, cur_lb);
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::Successor(Node* cur_node) const {
    if (!cur_node) {
        return nullptr;
    }
    if (cur_node->right) {
        cur_node = cur_node->right;
        while (cur_node->left) {
            cur_node = cur_node->left;
        }
        return cur_node;
    }
    Node* cur_parent = cur_node->parent;
    while (cur_parent && cur_node == cur_parent->right) {
        cur_node = cur_parent;
        cur_parent = cur_parent->parent;
    }
    return cur_parent;
}

template <typename ValueType>
typename Set<ValueType>::Node* Set<ValueType>::Treap::Predecessor(Node* cur_node) const {
    if (!cur_node) {
        return max_node;
    }
    if (cur_node->left) {
        cur_node = cur_node->left;
        while (cur_node->right) {
            cur_node = cur_node->right;
        }
        return cur_node;
    }
    Node* cur_parent = cur_node->parent;
    while (cur_parent && cur_node == cur_parent->left) {
        cur_node = cur_parent;
        cur_parent = cur_parent->parent;
    }
    return cur_parent;
}

template <typename ValueType>
void Set<ValueType>::Treap::Insert(const ValueType& key) {
    Node* new_node = new Node(key);
    if (!Find(key)) {
        InsertImpl(root_, new_node, nullptr);
        ++size_;
        // SetParentness(root_, nullptr);
        SetMinNode();
        SetMaxNode();
    } else {
        delete new_node;
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::InsertImpl(Node*& root, Node* new_node, Node* parent) {
    if (!root) {
        root = new_node;
        root->parent = parent;
    } else if (new_node->priority > root->priority) {
        Split(root, new_node->key, new_node->left, new_node->right);
        if (root->left) {
            root->left->parent = root;
        }
        if (root->right) {
            root->right->parent = root;
        }
        root = new_node;
        if (root) {
            root->parent = parent;
            if (root->left) {
                root->left->parent = root;
            }
            if (root->right) {
                root->right->parent = root;
            }
        }
    } else {
        InsertImpl(new_node->key < root->key ? root->left : root->right, new_node, root);
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::Erase(const ValueType& key) {
    if (EraseImpl(root_, key, nullptr)) {
        --size_;
        // SetParentness(root_, nullptr);
        SetMinNode();
        SetMaxNode();
    }
}

template <typename ValueType>
bool Set<ValueType>::Treap::EraseImpl(Node*& root, const ValueType& key, Node* parent) {
    if (root && root->key == key) {
        Node* eraser = root;
        Merge(root, root->left, root->right, parent);
        delete eraser;
        return true;
    } else if (root) {
        return EraseImpl(key < root->key ? root->left : root->right, key, root);
    } else {
        return false;
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::SetParentness(Node* cur_node, Node* parent) {
    if (cur_node) {
        SetParentness(cur_node->left, cur_node);
        SetParentness(cur_node->right, cur_node);
        cur_node->parent = parent;
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::SetMinNode() {
    min_node = root_;
    if (root_) {
        while (min_node->left) {
            min_node = min_node->left;
        }
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::SetMaxNode() {
    max_node = root_;
    if (root_) {
        while (max_node->right) {
            max_node = max_node->right;
        }
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::Split(Node* root, const ValueType& key, Node*& left_tree,
                                  Node*& right_tree) {
    if (!root) {
        left_tree = right_tree = nullptr;
    } else if (key < root->key) {
        Split(root->left, key, left_tree, root->left);
        if (root->left) {
            root->left->parent = root;
        }
        right_tree = root;
    } else {
        Split(root->right, key, root->right, right_tree);
        if (root->right) {
            root->right->parent = root;
        }
        left_tree = root;
    }
}

template <typename ValueType>
void Set<ValueType>::Treap::Merge(Node*& root, Node* left_son, Node* right_son, Node* parent) {
    if (!left_son || !right_son) {
        if (left_son) {
            left_son->parent = parent;
        }
        if (right_son) {
            right_son->parent = parent;
        }
        root = left_son ? left_son : right_son;
    } else if (left_son->priority < right_son->priority) {
        Merge(right_son->left, left_son, right_son->left, right_son);
        right_son->parent = parent;
        root = right_son;
    } else {
        Merge(left_son->right, left_son->right, right_son, left_son);
        left_son->parent = parent;
        root = left_son;
    }
}

