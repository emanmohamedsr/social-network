#ifndef AVLTREE_H
#define AVLTREE_H

#include "FeaturedArray.h"

template<typename T>
struct treeNode {
    size_t key;
    FeaturedArray<T> data;
    int nodeHeight;
    treeNode* left;
    treeNode* right;
    treeNode() :nodeHeight(1), left(nullptr), right(nullptr) {}
    treeNode(long long k) :key(k), nodeHeight(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class AVLtree {
private:
    treeNode<T>* root;

    void destroyTree(treeNode<T>* current);

    treeNode<T>* insert(treeNode<T>* current, T val, size_t key);
    treeNode<T>* Delete(treeNode<T>* current, T val, size_t key);
    T* search(treeNode<T>* current, T val, size_t key);

    int nodeHeight(treeNode<T>* node);
    int balanceFactor(treeNode<T>* node);
    int treeeHeight(treeNode<T>* current);
    treeNode<T>* InPre(treeNode<T>* p);
    treeNode<T>* InSuc(treeNode<T>* p);

    treeNode<T>* LL_Rotation(treeNode<T>* p);
    treeNode<T>* LR_Rotation(treeNode<T>* p);
    treeNode<T>* RR_Rotation(treeNode<T>* p);
    treeNode<T>* RL_Rotation(treeNode<T>* p);

    void inOrder(treeNode<T>* current);
public:
    AVLtree();
    ~AVLtree();
    void insert(T val, size_t key);
    T* search(T val, size_t key);
    void Delete(T val, size_t key);
    void display();
    int treeeHeight();
};
//CONSTRUCTOR & DESTRUCTOR->(DESTROY FUNCTION)---------------------------------
template<typename T>
AVLtree<T>::AVLtree() : root(nullptr) {}
template<typename T>
AVLtree<T>::~AVLtree() {
    destroyTree(root);
}
template<typename T>
void AVLtree<T>::destroyTree(treeNode<T>* current) {
    if (!current) return;
    destroyTree(current->left);
    destroyTree(current->right);
    current->left = nullptr;
    current->right = nullptr;
    delete current;
}
//INTERFACES-------------------------------------------------------------------
template<typename T>
void AVLtree<T>::insert(T val, size_t key) {
    root = insert(root, val, key);
}
template<typename T>
T* AVLtree<T>::search(T val, size_t key) {
    return search(root, val, key);
}
template<typename T>
void AVLtree<T>::Delete(T val, size_t key) {
    Delete(root, val, key);
}
template<typename T>
void AVLtree<T>::display() {
    inOrder(root);
}
template<typename T>
int AVLtree<T>::treeeHeight() {
    return treeeHeight(root);
}
//INSERT , DELETE & SEARCH-----------------------------------------------------
template<typename T>
treeNode<T>* AVLtree<T>::insert(treeNode<T>* current, T val, size_t key) {
    if (!current) {
        current = new treeNode<T>(key);
        current->data.sortedInsert(val);
        return current;
    }
    if (key < current->key)//smaller key
        current->left = insert(current->left, val, key);
    else if (key > current->key)//greater key
        current->right = insert(current->right, val, key);
    else { // key found
        current->data.sortedInsert(val);
        return current;
    }
    current->nodeHeight = nodeHeight(current);
    int BF = balanceFactor(current);
    if (BF > 1) { // ll || lr
        if (key < current->left->key)
            return LL_Rotation(current);
        else
            return LR_Rotation(current);
    }
    else if (BF < -1) { // rr || rl
        if (key > current->right->key)
            return RR_Rotation(current);
        else
            return RL_Rotation(current);
    }

    return current;
}//->->->->->->->->->->->->->->->->->->
template<typename T>
treeNode<T>* AVLtree<T>::Delete(treeNode<T>* current, T val, size_t key) {
    treeNode<T>* preORsuc;
    if (!current)
        return nullptr;
    if (key < current->key)//smaller
        current->left = Delete(current->left, val, key);
    else if (key > current->key)//greater
        current->right = Delete(current->right, val, key);
    else {//found
        if (!current->data.Delete(val))//not found in array
            return nullptr;
        if (!current->data.isEmpty())//deleted but still have elements
            return current;
        //node is empty => dalete node
        if (!current->left && !current->right) {//leaf
            current->data.Delete(val);
            if (current->data.isEmpty()) {
                if (current == root)
                    root = nullptr;
                delete(current);
                return nullptr;
            }
            return current;
        }
        else {
            if (treeeHeight(current->left) > treeeHeight(current->right)) {
                preORsuc = InPre(current->left);
                current->key = preORsuc->key;
                current->data = preORsuc->data;
                preORsuc->data.deleteExceptFirst();
                current->left = Delete(current->left, preORsuc->data[0], preORsuc->key);
            }
            else {
                preORsuc = InSuc(current->right);
                current->key = preORsuc->key;
                current->data = preORsuc->data;
                preORsuc->data.deleteExceptFirst();
                current->right = Delete(current->right, preORsuc->data[0], preORsuc->key);
            }
        }
    }
    //rotations
    int BF = balanceFactor(current);
    // Left Heavy   {delete from right}
    if (BF > 1) {
        // (L1 && L-0) -> LL-Rotation
        if (balanceFactor(current->left) >= 0)
            return LL_Rotation(current);
        // ( L-1 ) -> LR-Rotation
        else
            return LR_Rotation(current);
    }
    // Right Heavy  {delete from left}
    else if (BF < -1) {
        // ( R-1 && R-0 ) ->RR-Rotation
        if (balanceFactor(current->right) <= 0)
            return RR_Rotation(current);
        // ( R1 )
        else
            return RL_Rotation(current);
    }
    else
        current->nodeHeight = nodeHeight(current);
    return current;
}//->->->->->->->->->->->->->->->->->->
template<typename T>
T* AVLtree<T>::search(treeNode<T>* current, T val, size_t key) {
    if (!current)
        return nullptr;
    if (current->key == key)
        return current->data.searchData(val);
    if (current->key > key)
        return search(current->left, val, key);
    return search(current->right, val, key);
}
//BALANCE HELPERS--------------------------------------------------------------
template<typename T>
int AVLtree<T>::nodeHeight(treeNode<T>* node)
{
    int nl = (node && node->left ? node->left->nodeHeight : 0);
    int nr = (node && node->right ? node->right->nodeHeight : 0);
    return max(nl, nr) + 1;
}
template<typename T>
int AVLtree<T>::treeeHeight(treeNode<T>* current)
{
    if (!current)
        return 0;
    return max(treeeHeight(current->left), treeeHeight(current->right)) + 1;
}
template<typename T>
int AVLtree<T>::balanceFactor(treeNode<T>* node)
{
    int nl = (node && node->left ? node->left->nodeHeight : 0);
    int nr = (node && node->right ? node->right->nodeHeight : 0);
    return nl - nr;
}
template<typename T>
treeNode<T>* AVLtree<T>::InPre(treeNode<T>* p) {
    while (p && p->right)
        p = p->right;
    return p;
}
template<typename T>
treeNode<T>* AVLtree<T>::InSuc(treeNode<T>* p) {
    while (p && p->left)
        p = p->left;
    return p;
}
//ROTATIONS--------------------------------------------------------------------
template<typename T>
treeNode<T>* AVLtree<T>::LL_Rotation(treeNode<T>* p) {
    treeNode<T>* pl = p->left;
    treeNode<T>* plr = pl->right;
    pl->right = p;
    p->left = plr;
    p->nodeHeight = nodeHeight(p);
    pl->nodeHeight = nodeHeight(pl);
    if (root == p)
        root = pl;
    return pl;
}//->->->->->->->->->->->->->->->->->->
template<typename T>
treeNode<T>* AVLtree<T>::LR_Rotation(treeNode<T>* p) {
    treeNode<T>* pl = p->left;
    treeNode<T>* plr = pl->right;
    pl->right = plr->left;
    p->left = plr->right;
    plr->left = pl;
    plr->right = p;
    p->nodeHeight = nodeHeight(p);
    pl->nodeHeight = nodeHeight(pl);
    plr->nodeHeight = nodeHeight(plr);
    if (root == p)
        root = plr;
    return plr;
}//->->->->->->->->->->->->->->->->->->
template<typename T>
treeNode<T>* AVLtree<T>::RR_Rotation(treeNode<T>* p) {
    treeNode<T>* pr = p->right;
    treeNode<T>* prl = pr->left;
    p->right = prl;
    pr->left = p;
    p->nodeHeight = nodeHeight(p);
    pr->nodeHeight = nodeHeight(pr);
    if (root == p)
        root = pr;
    return pr;
}//->->->->->->->->->->->->->->->->->->
template<typename T>
treeNode<T>* AVLtree<T>::RL_Rotation(treeNode<T>* p) {
    treeNode<T>* pr = p->right;
    treeNode<T>* prl = pr->left;
    p->right = prl->left;
    pr->left = prl->right;
    prl->left = p;
    prl->right = pr;
    p->nodeHeight = nodeHeight(p);
    pr->nodeHeight = nodeHeight(pr);
    prl->nodeHeight = nodeHeight(prl);
    if (root == p)
        root = prl;
    return prl;
}
//TRAVERSALS-------------------------------------------------------------------
template<typename T>
void AVLtree<T>::inOrder(treeNode<T>* current) {
    if (!current) return;
    inOrder(current->left);
    size_t s = current->data.getSize();
    for (size_t i = 0; i < s; i++)
        std::cout << current->data[i] << std::endl;
    inOrder(current->right);
}
#endif // AVLTREE_H
