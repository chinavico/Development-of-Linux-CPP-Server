// SLinkListDemos.cpp : 定义控制台应用程序的入口点。
// 单链表

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结点类型：数据域，指针域
struct sNode{
	int data;	
	struct sNode *next;
};

// 创建单链表（表头）
struct sNode *CreateListFunc()
{
	struct sNode *headNode = (struct sNode*)malloc(sizeof(struct sNode));
	headNode->next = NULL;

	return headNode;
}

// 生成单链表结点
struct sNode*CreateNodeFunc(int data)
{
	// 生成新的结点
	struct sNode *newNode = (struct sNode*)malloc(sizeof(struct sNode));

	// 初始化新结点数据域和指针
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

// 打印输出链表中的结点（遍历结点）
void PrintListFunc(struct sNode *headNode)
{
	struct sNode *pTemp = headNode->next;
	while (pTemp){
		printf("%d\t", pTemp->data);
		pTemp = pTemp->next;
	}
}

// 插入结点
void InsertNodeHead(struct sNode *headNode, int data)
{
	struct sNode *insretNode = CreateNodeFunc(data); // 调用创建新结点的函数
	insretNode->next = headNode->next;
	headNode->next = insretNode;
}

// 删除结点
void DeleteNodeFunc(struct sNode *headNode, int posData)
{
	struct sNode *posNode = headNode->next;
	struct sNode *posNodeFront = headNode;

	if (posNode == NULL)
		printf("\n单链表为空.\n\n");
	else
	{
		while (posNode->data != posData)
		{
			posNodeFront = posNode;
			posNode = posNodeFront->next;

			if (posNode == NULL)
			{
				printf("\n无法找到指定的位置.\n");
				return;
			}
		}
		posNodeFront->next = posNode->next;
		free(posNode);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	// 创建一个链表list
	struct sNode *list = CreateListFunc();

	printf("\n\n【单链表操作（插入/删除/输出）】\n");

	PrintListFunc(list);  // 打印输出链表

	printf("初始化单链表操作:\n");
	InsertNodeHead(list, 55);
	InsertNodeHead(list, 77);
	InsertNodeHead(list, 44);
	InsertNodeHead(list, 22);
	InsertNodeHead(list, 99);
	PrintListFunc(list);  // 打印输出链表

	// 删除结点
	printf("\n删除单链表中的结点操作:\n");
	DeleteNodeFunc(list, 22);
	PrintListFunc(list);  // 打印输出链表
	
	printf("\n");

	return 0;
}

