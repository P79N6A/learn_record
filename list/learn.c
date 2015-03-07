typedef struct
{
	int info;
	nodeType *link;
} nodeType;

typedef struct
{
	nodeType *head;
	nodeType *tail;
	nodeType *current;
}listType;

listType list;


