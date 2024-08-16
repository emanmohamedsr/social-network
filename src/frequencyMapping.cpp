#include "frequencyMapping.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
frequencyMapping::frequencyMapping() :root(nullptr)
{
}

frequencyMapping::~frequencyMapping()
{
    destroyTree(root);
}

void frequencyMapping::destroyTree(frequencyMappingNode* start)
{
    if (!start)  return;
    destroyTree(start->left);
    destroyTree(start->right);
    start->left = start->right = nullptr;
    delete start;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
frequencyMappingNode* frequencyMapping::insert(frequencyMappingNode* current, std::string key)
{
    if (!current) {
        current = new frequencyMappingNode(key);
        return current;
    }
    if (key < current->key)//smaller key
        current->left = insert(current->left, key);
    else if (key > current->key)//greater key
        current->right = insert(current->right, key);
    else { // key found
        current->frequency++;
        return current;
    }
    current->height = nodeHeight(current);
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
}
bool frequencyMapping::Delete(frequencyMappingNode* current, std::string key)
{
    if (!current)
        return 0;
    if (current->key > key)
        return Delete(current->left, key);
    else if (current->key < key)
        return Delete(current->right, key);
    else {
        if (current->frequency > 0) {
            current->frequency--;
            return 1;
        }
        else
            return 0;
    }
}
int frequencyMapping::search(frequencyMappingNode* current, std::string key)
{
    if (!current)
        return 0;
    if (current->key == key)
        return current->frequency;
    if (current->key > key)
        return search(current->left, key);
    return search(current->right, key);
}
//BALANCE HELPERS--------------------------------------------------------------
int frequencyMapping::nodeHeight(frequencyMappingNode* node)
{
    int nl = (node && node->left ? node->left->height : 0);
    int nr = (node && node->right ? node->right->height : 0);
    return std::max(nl, nr) + 1;
}

int frequencyMapping::treeeHeight(frequencyMappingNode* current)
{
    if (!current)
        return 0;
    return std::max(treeeHeight(current->left), treeeHeight(current->right)) + 1;
}

int frequencyMapping::balanceFactor(frequencyMappingNode* node)
{
    int nl = (node && node->left ? node->left->height : 0);
    int nr = (node && node->right ? node->right->height : 0);
    return nl - nr;
}

frequencyMappingNode* frequencyMapping::InPre(frequencyMappingNode* p) {
    while (p && p->right)
        p = p->right;
    return p;
}

frequencyMappingNode* frequencyMapping::InSuc(frequencyMappingNode* p) {
    while (p && p->left)
        p = p->left;
    return p;
}

//ROTATIONS--------------------------------------------------------------------
frequencyMappingNode* frequencyMapping::LL_Rotation(frequencyMappingNode* p) {
    frequencyMappingNode* pl = p->left;
    frequencyMappingNode* plr = pl->right;
    pl->right = p;
    p->left = plr;
    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);
    if (root == p)
        root = pl;
    return pl;
}//->->->->->->->->->->->->->->->->->->
frequencyMappingNode* frequencyMapping::LR_Rotation(frequencyMappingNode* p) {
    frequencyMappingNode* pl = p->left;
    frequencyMappingNode* plr = pl->right;
    pl->right = plr->left;
    p->left = plr->right;
    plr->left = pl;
    plr->right = p;
    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);
    plr->height = nodeHeight(plr);
    if (root == p)
        root = plr;
    return plr;
}//->->->->->->->->->->->->->->->->->->
frequencyMappingNode* frequencyMapping::RR_Rotation(frequencyMappingNode* p) {
    frequencyMappingNode* pr = p->right;
    frequencyMappingNode* prl = pr->left;
    p->right = prl;
    pr->left = p;
    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);
    if (root == p)
        root = pr;
    return pr;
}//->->->->->->->->->->->->->->->->->->
frequencyMappingNode* frequencyMapping::RL_Rotation(frequencyMappingNode* p) {
    frequencyMappingNode* pr = p->right;
    frequencyMappingNode* prl = pr->left;
    p->right = prl->left;
    pr->left = prl->right;
    prl->left = p;
    prl->right = pr;
    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);
    prl->height = nodeHeight(prl);
    if (root == p)
        root = prl;
    return prl;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
frequencyMappingNode* frequencyMapping::maxFrequency(frequencyMappingNode* current) {
    if (!current) return nullptr;

    frequencyMappingNode* leftMax = maxFrequency(current->left);
    frequencyMappingNode* rightMax = maxFrequency(current->right);

    frequencyMappingNode* maxNode = current;
    if (leftMax && leftMax->frequency > maxNode->frequency)
        maxNode = leftMax;
    if (rightMax && rightMax->frequency > maxNode->frequency)
        maxNode = rightMax;

    return maxNode;
}
frequencyMappingNode* frequencyMapping::minFrequency(frequencyMappingNode* current) {
    if (!current) return nullptr;

    frequencyMappingNode* leftMin = minFrequency(current->left);
    frequencyMappingNode* rightMin = minFrequency(current->right);

    frequencyMappingNode* minNode = current;
    if (leftMin && leftMin->frequency < minNode->frequency)
        minNode = leftMin;
    if (rightMin && rightMin->frequency < minNode->frequency)
        minNode = rightMin;

    return minNode;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void frequencyMapping::insert(std::string key)
{
    root = insert(root, key);
}

int frequencyMapping::search(std::string key)
{
    return search(root, key);
}

bool frequencyMapping::Delete(std::string key)
{
    return Delete(root, key);
}

int frequencyMapping::treeeHeight()
{
    return treeeHeight(root);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
std::string frequencyMapping::maxFrequency()
{
    frequencyMappingNode* node = maxFrequency(root);
    return (node ? node->key : "No Activities Yet");
}
std::string frequencyMapping::minFrequency()
{
    frequencyMappingNode* node = minFrequency(root);
    return (node ? node->key : "No Activities Yet");
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
