#ifndef HASHTABLE_H
#define HASHTABLE_H


#include "User.h"
#include "AVLtree.h"

class HashTable
{
private:
	AVLtree<User> tree;
	size_t custom_hash(const string& key);
public:
	HashTable();
	~HashTable();

	void Detete(User& u);
	void Delete();
	void Insert();
	User* Search();
	void Dispaly();
};


#endif // HASHTABLE_H
