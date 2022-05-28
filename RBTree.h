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

// 初始化新的节点
Node* init(int val, int color, Node* father);

// 插入新的节点
Node* insert(Node* root, int val);

// 辅助修改有3节点情况的树
Node* helpFor3NodeCase(Node* pap, Node* L, Node* M, Node* R, Node* LL, Node* LR, Node* RL, Node* RR);

// 删除val为参数值的节点
Node* pop(Node* root, int val, Node* this_ = nullptr);

// 检查颜色约束
bool checkColorConstraints(Node* root);

// 检查黑高度约束
int blackHeight(Node* root);

// 打印RBTree
void Display(Node* root, int ident);

#endif