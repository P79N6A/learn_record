

//判断链表是否有环
int isCircle(Node *head, Node **pcircleNode, Node **plastNode)
{
	Node *fast = head;
	Node *slow = head;
	int isfind = -1;
	
	*pcircleNode = NULL;
	*plastNode = NULL;
	
	//判断是否有环
	while (fast)
	{
		if (fast == slow)
		{
			isfind = 1;
			*pcircleNode = fast; //相遇节点
			break;
		}
		
		if (fast->link != NULL)
			fast = fast->link;
		
		if (slow->link == NULL)
			*plastNode = slow;
		
		if (fast->link == NULL)
			*plastNode = fast;

		fast = fast->link;
		slow = show->link;
	}
	return isfind;
}



// 判断两个链表是否相交
// 如果都带环，一个相交节点必然在另一个环内
// 如果都不带环，尾节点相同必相交
// 一个带环一个不带，扯淡
int isListsMeet(Node *head1, Node *head2)
{
	Node *circleNode1;
	Node *circleNode2;
	Node *lastNode1;
	Node *lastNode2;
	Node *temp;

	//判断是否环
	int isCircle1 = isCircle(head1, &circleNode1, &lastNode1);
	int isCircle2 = isCircle(head2, &circleNode2, &lastNode2);

	if (isCircle1 != isCircle2) //一个有一个没
		return -1;

	else if ( isCircle1 == 1 ) //都有环
	{
		if (circleNode1 == circleNode2) return 1;

		temp = circleNode1->link; //用于循环一圈
		while ( temp != circleNode1)
		{
			if (temp == circleNode2) //相同
				return 1;
		}
		return -1;
	}
	else	//都没有环
	{
		if (lastNode1 == lastNode2) return 1;
		else
			return -1;
	}
}


//链表长度
size_t listLength(Node *head)
{
	size_t len = 0;
	Node *pCurrent = head;
	assert(head != NULL);
	
	while(pCurrent != NULL)
	{
		++len;
		pCurrent = pCurrent->link;
	}
	return len;
}

//两个尾节点相同的链表的第一个交点
Node *getListsFirstCommonNode(Node *head1, Node *head2)
{
	size_t len1, len2;
	size_t difflen;
	Node *phead1 = head1;
	Node *phead2 = head2;

	len1 = listLength(phead1);
	len2 = listLength(phead2);
	
	//长的先走
	if (len1 > len2)
	{
		difflen = len1 - len2;
		while (diffen--) phead1 = phead1->link;
	}
	else
	{
		difflen = len2 - len1;
		while (diffen--) phead2 = phead2->link;
	}

	while( phead1 != NULL && phead2 != NULL && phead1 != phead2)
	{
		phead1 = phead1->link;
		phead2 = phead2->link;
	}		

	return phead1; 
}



