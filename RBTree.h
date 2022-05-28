#pragma once
#ifndef _RBTREE_
#define _RBTREE_
constexpr auto Red = 0;
constexpr auto Black = 1;
constexpr auto Ok = 0;
constexpr auto RBR = 1;
constexpr auto BRB = 2;
constexpr auto RRB = 3;
constexpr auto BRR = 4;

typedef struct Node {
	int val;
	int color; // Red or Balck
	int cur;   // Ok , RBR, BRB, RRB, BRR
	Node* left;
	Node* right;
	Node* father = nullptr;
}Node;

// ��ʼ���µĽڵ�
Node* init(int val, int color, Node* father);

// �����µĽڵ�
Node* insert(Node* root, int val);

// �����޸���3�ڵ��������
Node* helpFor3NodeCase(Node* pap, Node* L, Node* M, Node* R, Node* LL, Node* LR, Node* RL, Node* RR);

// ɾ��valΪ����ֵ�Ľڵ�
Node* pop(Node* root, int val, Node* this_ = nullptr);

// �����ɫԼ��
bool checkColorConstraints(Node* root);

// ���ڸ߶�Լ��
int blackHeight(Node* root);

// ��ӡRBTree
void Display(Node* root, int ident);

#endif