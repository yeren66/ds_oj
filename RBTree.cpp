#include "RBTree.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;/*
constexpr auto Red = 0;
constexpr auto Black = 1;
constexpr auto Ok = 0;
constexpr auto RBR = 1;
constexpr auto BRB = 2;
constexpr auto RRB = 3;
constexpr auto BRR = 4;*/

Node* init(int val, int color, Node* father) {
	Node* node = new Node();
	node->val = val;
	node->color = color;
	node->cur = BRB;  // Ok, RBR, BRB, RRB, BRR
	node->left = nullptr;
	node->right = nullptr;
	node->father = father;
	return node;
}

Node* insert(Node* root, int val) {
	// 如果val已在树中，则直接返回
	if (val == root->val)
		return root;
	// 将val插入到叶节点下
	if (root->left == nullptr && val < root->val) {
		root->left = init(val, Red, root);
		if (root->color == Red && root->right == nullptr)
			root->cur = RRB;
		else if (root->color == Black && root->right != nullptr && root->right->color == Red)
			root->cur = RBR;
		return root;
	}
	else if (root->right == nullptr && val > root->val) {
		root->right = init(val, Red, root);
		if (root->color == Red && root->left == nullptr)
			root->cur = BRR;
		else if (root->color == Black && root->left != nullptr && root->left->color == Red)
			root->cur = RBR;
		return root;
	}
	// 如果树未到叶节点，则递归调用
	if (val <= root->val) {
		root->left = insert(root->left, val);
	}
	else {
		root->right = insert(root->right, val);
	}

	// 下面为调整部分

	// 首先讨论当前根节点为黑的情况
	if (root->color == Black) {
		// 因为叶节点的左右子节点设为了nullptr，所以需要排除该情况，否则会出现访问空指针情况
		// 我认为这里可以进行优化，将叶节点的左右子节点声明为value为null的一个空节点，就可以少几个特殊情况需要考虑
		if (root->left != nullptr && root->right != nullptr) {
			// 需要调整的情况只有子节点为RRB和BRR，首先判断左子节点
			if (root->left->cur != RRB && root->left->cur != BRR) {
				// 该情况下需要调整右子节点
				if (root->right->cur == RRB) {
					// 子节点为RRB或BRR时，又有两种情况，分为3节点情况和4节点情况
					if (root->left->color == Black) {
						// 3节点情况
						Node* father_ = root->father;
						Node* temp = helpFor3NodeCase(root->father, root, root->right->left, root->right, root->left, root->right->left->left, root->right->left->right, root->right->right);
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = temp;
							else
								father_->right = temp;
						}
						root = temp;
						root->cur = RBR;
						root->left->cur = BRB;
						root->right->cur = BRB;
						return root;
					}
					else {
						// 4节点情况
						root->left->color = Black;
						root->right->color = Black;
						root->color = Red;
						root->cur = BRB;
						root->left->cur = Ok;
						root->right->cur = Ok;
						return root;
					}
				}
				else if (root->right->cur == BRR) {
					// BRR也是
					if (root->left->color == Black) {
						// 3节点情况
						Node* father_ = root->father;
						Node* temp = helpFor3NodeCase(root->father, root, root->right, root->right->right, root->left, root->right->left, root->right->right->left, root->right->right->right);
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = temp;
							else
								father_->right = temp;
						}
						root = temp;
						root->cur = RBR;
						root->left->cur = BRB;
						root->right->cur = BRB;
						return root;
					}
					else {
						// 4节点情况
						root->left->color = Black;
						root->right->color = Black;
						root->color = Red;
						root->cur = BRB;
						root->left->cur = Ok;
						root->right->cur = Ok;
						return root;
					}
				}
				else {
					// 当情况既不为BRR也不为RRB时，说明不需要调整，则current为Ok
					root->cur = Ok;
					return root;
				}
			}
			else {
				// 该情况下需要调整左子节点
				if (root->left->cur == RRB) {
					if (root->right->cur == Black) {
						// 3节点情况
						Node* father_ = root->father;
						Node* temp = helpFor3NodeCase(root->father, root->left->left, root->left, root, root->left->left->left, root->left->left->right, root->left->right, root->right);
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = temp;
							else
								father_->right = temp;
						}
						root = temp;
						root->cur = RBR;
						root->left->cur = BRB;
						root->right->cur = BRB;
						return root;
					}
					else {
						// 4节点情况
						root->right->color = Black;
						root->left->color = Black;
						root->color = Red;
						root->cur = BRB;
						root->left->cur = Ok;
						root->right->cur = Ok;
						return root;
					}
				}
				else if (root->left->cur == BRR) {
					if (root->right->color == Black) {
						// 3节点情况
						Node* father_ = root->father;
						Node* temp = helpFor3NodeCase(root->father, root->left, root->left->right, root, root->left->left, root->left->right->left, root->left->right->right, root->right);
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = temp;
							else
								father_->right = temp;
						}
						root = temp;
						root->cur = RBR;
						root->left->cur = BRB;
						root->right->cur = BRB;
						return root;
					}
					else {
						// 4节点情况
						root->right->color = Black;
						root->left->color = Black;
						root->color = Red;
						root->cur = BRB;
						root->left->cur = Ok;
						root->right->cur = Ok;
						return root;
					}
				}
				else {
					// 不需要调整
					root->cur = Ok;
					return root;
				}
			}

		}
		// 当根节点只有单根时，可推出LL，LR，RL，RR均为nullptr，此时为特殊情况
		else if (root->left != nullptr && root->right == nullptr) {
			if (root->left->cur == BRR) {
				// 3节点情况
				root->left->right->right = root;
				root->left->right->left = root->left;
				root->left->right->father = root->father;
				if (root->father != nullptr) {
					if (root->father->left == root)
						root->father->left = root->left->right;
					else
						root->father->right = root->left->right;
				}
				Node* father_ = root->father;
				root->father = root->left->right;
				root->left->father = root->left->right;
				root = root->left->right;
				root->father = father_;
				root->color = Black;
				root->left->color = Red;
				root->right->color = Red;
				root->cur = RBR;
				root->left->cur = BRB;
				root->right->cur = BRB;
				root->left->left = nullptr;
				root->left->right = nullptr;
				root->right->left = nullptr;
				root->right->right = nullptr;
			}
			else if (root->left->cur == RRB) {
				// 3节点情况
				root->left->right = root;
				if (root->father != nullptr) {
					if (root->father->left == root)
						root->father->left = root->left;
					else
						root->father->right = root->left;
				}
				Node* father_ = root->father;
				root->father = root->left;
				root = root->left;
				root->father = father_;
				root->color = Black;
				root->left->color = Red;
				root->right->color = Red;
				root->cur = RBR;
				root->left->cur = BRB;
				root->right->cur = BRB;
				root->left->left = nullptr;
				root->left->right = nullptr;
				root->right->left = nullptr;
				root->right->right = nullptr;
			}
		}
		else if (root->right != nullptr && root->left == nullptr) {
			if (root->right->cur == BRR) {
				// 3节点情况
				root->right->left = root;
				if (root->father != nullptr) {
					if (root->father->left == root)
						root->father->left = root->right;
					else
						root->father->right = root->right;
				}
				Node* father_ = root->father;
				root->father = root->right;
				root = root->right;
				root->father = father_;
				root->color = Black;
				root->left->color = Red;
				root->right->color = Red;
				root->cur = RBR;
				root->left->cur = BRB;
				root->right->cur = BRB;
				root->left->left = nullptr;
				root->left->right = nullptr;
				root->right->left = nullptr;
				root->right->right = nullptr;
			}
			else if (root->right->cur == RRB) {
				// 3节点情况
				root->right->left->left = root;
				root->right->left->right = root->right;
				if (root->father != nullptr) {
					if (root->father->left == root)
						root->father->left = root->right->left;
					else
						root->father->right = root->right->left;
				}
				Node* father_ = root->father;
				root->father = root->right->left;
				root->right->father = root->right->left;
				root = root->right->left;
				root->father = father_;
				root->color = Black;
				root->left->color = Red;
				root->right->color = Red;
				root->cur = RBR;
				root->left->cur = BRB;
				root->right->cur = BRB;
				root->left->left = nullptr;
				root->left->right = nullptr;
				root->right->left = nullptr;
				root->right->right = nullptr;
			}
		}
		else {
			root->cur = Ok;
		}
	}
	// 当前根节点为红色时，除非是根节点，否则不需要调整，只需要将current修改，返回上级节点
	else if (root->color == Red) {
		if (root->father == nullptr) {
			root->color = Black;
			root->cur = Ok;
		}
		else if (root->left != nullptr && root->left->color == Red) {
			root->cur = RRB;
			return root;
		}
		else if (root->right != nullptr && root->right->color == Red) {
			root->cur = BRR;
			return root;
		}
		else {
			root->cur = Ok;
			return root;
		}
	}

}

Node* helpFor3NodeCase(Node* pap, Node* L, Node* M, Node* R, Node* LL, Node* LR, Node* RL, Node* RR) {
	// 3节点情况下的调整方式，返回新的根节点
	L->color = Red;
	R->color = Red;
	M->color = Black;
	M->left = L;
	L->father = M;
	M->right = R;
	R->father = M;
	L->right = LR;
	R->left = RL;
	if(LR != nullptr)
		LR->father = L;
	if(RL != nullptr)
		RL->father = R;
	M->father = pap;
	return M;
}

int vec_left[100] = { 0 };


void Display(Node* root, int ident){
	// 显示二叉树的函数，只要调用Display(root, 0)即可
	if (ident > 0)
	{
		for (int i = 0; i < ident - 1; ++i)
		{
			printf(vec_left[i] ? "│   " : "    ");
		}
		printf(vec_left[ident - 1] ? "├── " : "└── ");
	}

	if (!root)
	{
		printf("(null)\n");
		return;
	}
	if(root->color == Red)
		printf("\033[31m%d\n\033[0m", root->val);
	else
		printf("%d\n", root->val);
	if (!root->left && !root->right)
	{
		return;
	}

	vec_left[ident] = 1;
	Display(root->left, ident + 1);
	vec_left[ident] = 0;
	Display(root->right, ident + 1);
}


Node* pop(Node* root, int val, Node* this_) {
	if (root == nullptr)
		return root;
	if (this_ != nullptr) {
		if (root->left != nullptr)
			root->left = pop(root->left, val, this_);
		else {
			this_->val = root->val;
			if (root->right != nullptr) {
				root->val = root->right->val;
				delete root->right;
				root->right = nullptr;
			}
			else {
				Node* father_ = root->father;
				if (father_ == nullptr){
					delete root;
					return father_;
					}
				else if (father_->left == root) {
					delete root;
					father_->left = nullptr;
					return father_;
				}
				else {
					delete root;
					father_->right = nullptr;
					return father_;
				}
			}
		}
	}
	else if (root->val > val) {
		root->left = pop(root->left, val, this_);
	}
	else if(root->val < val) {
		root->right = pop(root->right, val, this_);
	}
	else {
		if (root->left == nullptr) {
			if (root->right != nullptr) {
				root->val = root->right->val;
				delete root->right;
				root->right = nullptr;
			}
			else {
				Node* father_ = root->father;
				if (father_ == nullptr) {
					delete root;
					return nullptr;
				}
				else if (father_->left == root) {
					delete root;
					father_->left = nullptr;
					return nullptr;
				}
				else {
					delete root;
					father_->right = nullptr;
					return nullptr;
				}
			}
		}
		else {
			if (root->right == nullptr) {
				root->val = root->left->val;
				delete root->left;
				root->left = nullptr;
			}
			else {
				root->right = pop(root->right, val, root);
			}
		}
	}

	// 调整
	
	int leftHeight = blackHeight(root->left);
	int rightHeight = blackHeight(root->right);
	if (leftHeight == rightHeight)
		return root;
	else if (leftHeight < rightHeight) {
		if (root->color == Red && ((root->right->left == nullptr && root->right->right == nullptr) || (root->right->left->color == Black && root->right->right->color == Black))) {
			if (root->left == nullptr) {
				root->color = Black;
				root->right->color = Red;
				return root;
			}
			else {
				// the case: l is black, p is red
				Node* s = root->right;
				Node* p = root;
				Node* l = root->right->left;
				Node* father_ = root->father;
				if (father_ != nullptr) {
					if (father_->left == p)
						father_->left = s;
					else
						father_->right = s;
				}
				s->father = father_;
				s->left = p;
				p->father = s;
				p->right = l;
				l->father = p;
				return s;
			}
		}
		else { // root color is black      or      root color is red meanwhile grandson root color is red
			if (root->left == nullptr) {
				assert(root->right != nullptr);
				if (root->right->color == Red) {
					// the case: l,p,r is black, s is red
					Node* p = root;
					Node* s = root->right;
					Node* l = root->right->left;
					Node* father_ = root->father;
					if (father_ != nullptr) {
						if (father_->left == p)
							father_->left = s;
						else
							father_->right = s;
					}
					s->father = father_;
					s->color = Black;
					if (l->left == nullptr && l->right == nullptr) {
						s->left = p;
						p->father = s;
						p->right = l;
						l->father = p;
						p->color = Black;
						l->color = Red;
					}
					else if (l->left != nullptr) {
						Node* ll = l->left;
						s->left = ll;
						ll->father = s;
						ll->left = p;
						p->father = ll;
						p->right = nullptr;
						ll->right = l;
						l->father = ll;
						ll->color = Red;
					}
					else if (l->right != nullptr) {
						s->left = l;
						l->father = s;
						l->left = p;
						p->father = l;
						p->right = nullptr;
						l->color = Red;
					}
					return s;
				}
				else { // root->right->color == Black 
					if (root->right->left == nullptr && root->right->right == nullptr) {
						root->color = Black;
						root->right->color = Red;
						return root;
					}
					else if (root->right->left != nullptr && root->right->right != nullptr) {
						// the case that slide don't mention
						Node* p = root;
						Node* s = root->right;
						Node* r = root->right->right;
						Node* l = root->right->left;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->left = p;
						p->father = s;
						p->right = l;
						r->color = Red;
						s->color = p->color;
						p->color = Black;
						return s;
					}
					else if (root->right->right != nullptr) {
						// the case: l,p is black, r is red   
						// tips: the slide offered this case. But I think p,l can be red, otherwise some case may be missed
						Node* p = root;
						Node* s = root->right;
						Node* r = root->right->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->left = p;
						p->father = s;
						p->right = nullptr;
						r->color = Red;
						s->color = p->color;
						p->color = Black;
						return s;
					}
					else if (root->right->left != nullptr) {
						// the case: l is red
						// tips: color of p is uncertain
						Node* p = root;
						Node* s = root->right;
						Node* l = root->right->left;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = l;
							else
								father_->right = l;
						}
						l->father = father_;
						l->left = p;
						p->father = l;
						l->right = s;
						s->father = l;
						l->color = p->color;
						p->color = Black;
						s->left = nullptr;
						p->right = nullptr;
						return l;
					}
				}
			}
			else {
				if (root->right->color == Red) {
					// the case: l,p,r is black, s is red
					Node* p = root;
					Node* s = root->right;
					Node* l = root->right->left;
					Node* father_ = root->father;
					if (father_ != nullptr) {
						if (father_->left == root)
							father_->left = s;
						else
							father_->right = s;
					}
					s->father = father_;
					s->left = p;
					p->father = s;
					p->right = l;
					l->father = p;
					s->color = Black;
					p->color = Red;
					return s;
				}
				else { // root->right->color == Black
					if (root->right->left->color == Red) {
						// the case: l is red
						Node* p = root;
						Node* s = root->right;
						Node* l = root->right->left;
						Node* ll = root->right->left->left;
						Node* lr = root->right->left->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = l;
							else
								father_->right = l;
						}
						l->father = father_;
						l->left = p;
						p->father = l;
						l->right = s;
						s->father = l;
						p->right = ll;
						ll->father = p;
						s->left = lr;
						lr->father = s;
						l->color = p->color;
						p->color = Black;
						return l;
					}
					else if (root->right->right->color == Red) {
						// the case: l,p is black, r is red
						Node* p = root;
						Node* s = root->right;
						Node* l = root->right->left;
						Node* r = root->right->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->left = p;
						p->father = s;
						s->right = r;
						r->father = s;
						p->right = l;
						l->father = p;
						r->color = Black;
						s->color = p->color;
						p->color = Black;
						return s;
					}
					else {
						// the case: all are black
						root->right->color = Red;
						return root;
					}
				}
			}
		}
	}
	else {
		if (root->color == Red && ((root->left->left == nullptr && root->left->right == nullptr) || (root->left->left->color == Black && root->left->right->color == Black))) {
			if (root->right == nullptr) {
				root->color = Black;
				root->left->color = Red;
				return root;
			}
			else {
				// the mirror case: l is black, p is red
				Node* p = root;
				Node* s = root->left;
				Node* r = root->left->right;
				Node* father_ = root->father;
				if (father_ != nullptr) {
					if (father_->left == p)
						father_->left = s;
					else
						father_->right = s;
				}
				s->father = father_;
				s->right = p;
				p->father = s;
				p->left = r;
				r->father = p;
				return s;
			}
		}
		else { // root color = black       or        root color = red and grandson root have red root
			if (root->right == nullptr) {
				if (root->left->color == Red) {
					// the mirror case: l,p,r is black, s is red
					Node* p = root;
					Node* s = root->left;
					Node* r = root->left->right;
					Node* father_ = root->father;
					if (father_ != nullptr) {
						if (father_->left == root)
							father_->left = s;
						else
							father_->right = s;
					}
					s->color = Black;
					s->father = father_;
					if (r->left == nullptr && r->right == nullptr) {
						s->right = p;
						p->father = s;
						p->left = r;
						r->father = p;
						p->color = Black;
						r->color = Red;
					}
					else if (r->right != nullptr) {
						Node* rr = r->right;
						s->right = rr;
						rr->father = s;
						rr->right = p;
						p->father = rr;
						p->left = nullptr;
						rr->left = r;
						r->father = rr;
						r->right = nullptr;
						rr->color = Red;
					}
					else if (r->left != nullptr) {
						s->right = r;
						r->father = s;
						r->right = p;
						p->father = r;
						p->left = nullptr;
						p->color = Red;
					}
					return s;
				}
				else { // root->left->color == black
					if (root->left->left == nullptr && root->left->right == nullptr) {
						root->color = Black;
						root->left->color = Red;
						return root;
					}
					else if (root->left->left != nullptr && root->left->right != nullptr) {
						// the mirror case that slide don't mention
						Node* p = root;
						Node* s = root->left;
						Node* l = root->left->left;
						Node* r = root->left->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->right = p;
						p->father = s;
						p->left = r;
						l->color = Black;
						s->color = p->color;
						p->color = Black;
						return s;
					}
					else if (root->left->left != nullptr) {
						// the mirror case: l is red
						// tips: p color maybe red
						Node* p = root;
						Node* s = root->left;
						Node* l = root->left->left;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->right = p;
						p->father = s;
						p->left = p->right = nullptr;
						l->color = Black;
						s->color = p->color;
						p->color = Black;
						return s;
					}
					else if (root->left->right != nullptr) {
						// the mirror csae: l,p is black, r is red
						Node* p = root;
						Node* s = root->left;
						Node* r = root->left->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = r;
							else
								father_->right = r;
						}
						r->father = father_;
						r->left = s;
						s->father = r;
						r->right = p;
						p->father = r;
						s->left = s->right = nullptr;
						p->left = p->right = nullptr;
						r->color = p->color;
						p->color = Black;
						return r;
					}
				}
			}
			else { // root->right != nullptr
				if (root->left->color == Red) {
					// the mirror case: l,p,r is black, s is red
					Node* p = root;
					Node* s = root->left;
					Node* r = root->left->right;
					Node* father_ = root->father;
					if (father_ != nullptr) {
						if (father_->left == root)
							father_->left = s;
						else
							father_->right = s;
					}
					s->father = father_;
					s->right = p;
					p->father = s;
					p->left = r;
					r->father = p;
					s->color = Black;
					p->color = Red;
					return s;
				}
				else { // root left color is Balck
					if (root->left->left->color == Red) {
						// the mirror case: l is red
						// tips: p color maybe red
						Node* p = root;
						Node* s = root->left;
						Node* l = root->left->left;
						Node* r = root->left->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = s;
							else
								father_->right = s;
						}
						s->father = father_;
						s->right = p;
						p->father = s;
						p->left = r;
						r->father = p;
						s->color = p->color;
						p->color = Black;
						l->color = Black;
						return s;
					}
					else if (root->left->right->color == Red) {
						// the mirror case: l,p is black, r is red
						// tips: p color maybe red
						Node* p = root;
						Node* s = root->left;
						Node* r = root->left->right;
						Node* rl = root->left->right->left;
						Node* rr = root->left->right->right;
						Node* father_ = root->father;
						if (father_ != nullptr) {
							if (father_->left == root)
								father_->left = r;
							else
								father_->right = r;
						}
						r->father = father_;
						r->left = s;
						s->father = r;
						r->right = p;
						p->father = r;
						s->right = rl;
						rl->father = s;
						p->left = rr;
						rr->father = p;
						r->color = p->color;
						p->color = Black;
						return r;
					}
					else {
						// the mirror case: all are black
						root->left->color = Red;
						return root;
					}
				}
			}
		}
	}

}

bool checkColorConstraints(Node* root) {
	return true;
}

int blackHeight(Node* root) {
	if (root == nullptr)
		return 0;
	else if (root->color == Black)
		return blackHeight(root->left) + 1;
	else
		return blackHeight(root->left);
}