#ifndef LINKED_LIST_TYPE_H
#define LINKED_LIST_TYPE_H

//define a class of list
//define of the node

template<class Type> 
struct nodeType
{
	Type info;
	nodeType<Type> *link;
}

template <class Type>
class LinkdeListType
{
public :
	const LinkdeListType<Type>& operator=
					(const LinkdeListType<Type>&);
	//overload the assignedment opeartor
	
	void initializeList();

	bool isEmptyList();

	bool isFullList();

	void print();

	int length();

	void destroyList();

	void retrieverFirst(Type& firstElement);

	void search(const Type& searchItem);

	void insertFitrst(const Type& newItem);

	void insertLast(const Type& newItem);
	
	void deleteNode(const Type& deleteItem);

	LinkdeListType();

	LinkdeListType(const LinkdeListType<Type>& otherList);

	~LinkdeListType();

protected :
	nodeType<Type> *first;
	nodeType<Type> *last;
	int length;
};


#endif

