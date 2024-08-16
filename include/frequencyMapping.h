
#pragma once
#include <iostream>
#include <string>

struct frequencyMappingNode {
    std::string key;
    int frequency;
    int height;
    frequencyMappingNode* left;
    frequencyMappingNode* right;
    frequencyMappingNode(const std::string& k) :key(k), frequency(1), height(1), left(nullptr), right(nullptr) {}
};
class frequencyMapping
{
private:
    frequencyMappingNode* root;

    void destroyTree(frequencyMappingNode* start);

    frequencyMappingNode* insert(frequencyMappingNode* current, std::string key);
    bool Delete(frequencyMappingNode* current, std::string key);
    int search(frequencyMappingNode* current, std::string key);

    int nodeHeight(frequencyMappingNode* node);
    int balanceFactor(frequencyMappingNode* node);
    int treeeHeight(frequencyMappingNode* current);
    frequencyMappingNode* InPre(frequencyMappingNode* p);
    frequencyMappingNode* InSuc(frequencyMappingNode* p);

    frequencyMappingNode* LL_Rotation(frequencyMappingNode* p);
    frequencyMappingNode* LR_Rotation(frequencyMappingNode* p);
    frequencyMappingNode* RR_Rotation(frequencyMappingNode* p);
    frequencyMappingNode* RL_Rotation(frequencyMappingNode* p);

    frequencyMappingNode* maxFrequency(frequencyMappingNode* current);
    frequencyMappingNode* minFrequency(frequencyMappingNode* current);
public:
    frequencyMapping();
    ~frequencyMapping();

    void insert(std::string key);
    int search(std::string key);
    bool Delete(std::string key);
    int treeeHeight();

    std::string maxFrequency();
    std::string minFrequency();

};


