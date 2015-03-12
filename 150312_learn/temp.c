

//�ж������Ƿ��л�
int isCircle(Node *head, Node **pcircleNode, Node **plastNode)
{
	Node *fast = head;
	Node *slow = head;
	int isfind = -1;
	
	*pcircleNode = NULL;
	*plastNode = NULL;
	
	//�ж��Ƿ��л�
	while (fast)
	{
		if (fast == slow)
		{
			isfind = 1;
			*pcircleNode = fast; //�����ڵ�
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



// �ж����������Ƿ��ཻ
// �����������һ���ཻ�ڵ��Ȼ����һ������
// �������������β�ڵ���ͬ���ཻ
// һ������һ������������
int isListsMeet(Node *head1, Node *head2)
{
	Node *circleNode1;
	Node *circleNode2;
	Node *lastNode1;
	Node *lastNode2;
	Node *temp;

	//�ж��Ƿ�
	int isCircle1 = isCircle(head1, &circleNode1, &lastNode1);
	int isCircle2 = isCircle(head2, &circleNode2, &lastNode2);

	if (isCircle1 != isCircle2) //һ����һ��û
		return -1;

	else if ( isCircle1 == 1 ) //���л�
	{
		if (circleNode1 == circleNode2) return 1;

		temp = circleNode1->link; //����ѭ��һȦ
		while ( temp != circleNode1)
		{
			if (temp == circleNode2) //��ͬ
				return 1;
		}
		return -1;
	}
	else	//��û�л�
	{
		if (lastNode1 == lastNode2) return 1;
		else
			return -1;
	}
}


//������
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

//����β�ڵ���ͬ������ĵ�һ������
Node *getListsFirstCommonNode(Node *head1, Node *head2)
{
	size_t len1, len2;
	size_t difflen;
	Node *phead1 = head1;
	Node *phead2 = head2;

	len1 = listLength(phead1);
	len2 = listLength(phead2);
	
	//��������
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



