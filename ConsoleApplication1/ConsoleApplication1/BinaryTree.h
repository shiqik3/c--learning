#pragma once
#include<iostream>

class BinaryTree {
public:
	static class Node {
	public:
		int val;
		Node* left;
		Node* right;
		Node(int value, Node* a, Node* b) :val(value), left(a), right(b) {}
	};
	Node* head;
	BinaryTree() :head(NULL) {}
	void constucts(int *a, int *b, int len) {
		int lens = len;
		int *sp, *si, *ep, *ei;
		sp = a;
		ep = a + len - 1;
		si = b;
		ei = b + len - 1;
		head = constuct(sp, ep, si, ei);
	}
	Node* constuct(int *sp, int *ep, int *si, int *ei) {
		int *spa, *sia, *epa, *eia, *zh;
		int tmp, llen, rlen;
		Node *root;
		spa = sp;
		epa = ep;
		sia = si;
		eia = ei;
		root = new Node(*sp, NULL, NULL);
		for (zh = si; zh != ei; zh++) {
			if (*zh == *sp) {
				break;
			}
		}
		llen = zh - si;
		if (llen > 0) {
			root->left = constuct(sp + 1, sp + llen, si, zh - 1);   //构建左子树
		}
		rlen = ei - zh;
		if (rlen > 0) {
			root->right = constuct(sp + llen + 1, ep, zh + 1, ei);    //构建右子树
		}
		return root;
	}

	void print() {
		ptree(head);
	}
	void ptree(Node* node) {
		if (node != NULL) {
			printf("%d   ", node->val);
			ptree(node->left);
			ptree(node->right);
		}
		else {

		}
	}
};