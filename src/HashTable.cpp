#include "HashTable.h"

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

size_t HashTable::custom_hash(const string& key)
{
	const int prime = 31;
	size_t hasher = 0;
	for (char ch : key)
		hasher = (hasher * prime) + ch;
	return hasher;
}

void HashTable::Insert()
{
	User u;
	u.getUser_SignUP();
	tree.insert(u, custom_hash(u.getKey()));
}

void HashTable::Detete(User& u)
{
	tree.Delete(u, custom_hash(u.getKey()));
}

void HashTable::Delete()
{
	User u;
	u.getUser_SignIN();
	tree.Delete(u, custom_hash(u.getKey()));
}

User* HashTable::Search()
{
	User u;
	u.getUser_SignIN();
	return (tree.search(u, custom_hash(u.getKey())) );
}

void HashTable::Dispaly()
{
	tree.display();
}
