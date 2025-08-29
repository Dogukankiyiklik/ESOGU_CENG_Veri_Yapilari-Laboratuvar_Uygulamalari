#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode *curr = this->min();

	while (curr != NULL){
		BSTNode *n = this->next(curr);
		delete curr;
		curr = n;
	} // end-while
	
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	BSTNode* node = new BSTNode(key);
	if (root == NULL) {
		root = node;
	}

	else {
		BSTNode* p = root;
		BSTNode* q = NULL;

		// find the insertion index
		while (p) {
			q = p;
			if (q->key == key) return;
			else if (q->key > key) {
				if (p->leftLinkType == THREAD) {
					p = NULL;
				}
				else {
					p = p->left;
				}
			}

			else if (q->key < key) {
				if (p->rightLinkType == THREAD) {
					p = NULL;
				}
				else {
					p = p->right;
				}
			}
		}

		// key < q->key
		if (q->key > key) {

			if (q->leftLinkType == THREAD) {
				node->left = q->left;
				node->right = q;

				q->left = node;
				q->leftLinkType = CHILD;
			}

			else if (q->left == NULL) {
				node->left = NULL;
				node->right = q;

				q->left = node;
				q->leftLinkType = CHILD;
			}
		}

		// key > q->key
		else if (q->key < key) {

			if (q->rightLinkType == THREAD) {
				node->left = q;
				node->right = q->right;

				q->right = node;
				q->rightLinkType = CHILD;
			}

			else if (q->right == NULL) {
				node->left = q;
				node->right = NULL;

				q->right = node;
				q->rightLinkType = CHILD;
			}
		}
	}
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	BSTNode* p = root;
	BSTNode* q = NULL;

	while (p->key != key) {
		q = p;

		if (p->key > key) p = p->left;
		else if (p->key < key) p = p->right;
	}

	// if key exist
	if (p != NULL) {
		// there are no child
		if (p->leftLinkType == THREAD && p->rightLinkType == THREAD) {
			if (p->key < q->key) {
				q->left = p->left;
				q->leftLinkType = THREAD;
			}
			else {
				q->right = p->right;
				q->rightLinkType = THREAD;
			}
		}

		// there is one child
		if ((p->leftLinkType == CHILD && p->rightLinkType == THREAD) || (p->leftLinkType == THREAD && p->rightLinkType == CHILD)) {
			// left side child
			if (p->leftLinkType == CHILD) {
				p->left->right = p->right;

				// right side
				if (q->key < p->key) {
					q->right = p->left;
					p->left->left = q;
				}
				// left side
				else {
					q->left = p->left;
				}
			}

			// right side child
			else if (p->rightLinkType == CHILD) {
				p->right->left = p->left;

				// right side
				if (q->key < p->key) {
					q->right = p->right;
				}

				// left side
				else {
					q->left = p->right;
				}
			}
		}

		// there are two child 
		if (p->rightLinkType == CHILD && p->leftLinkType == CHILD) {
			p->left->left = q;
			p->left->right = p->right;

			// right side
			if (q->key < p->key) {
				q->right = p->left;
				p->left->left = q;
			}
			// left side
			else {
				q->left = p->left;
			}
		}
		
	}
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {
	if (root == NULL) return NULL;

	BSTNode* current = root;

	while (current) {
		if (current->key == key) return current;

		else if (key < current->key) {
			if (current->leftLinkType == CHILD) {
				current = current->left;
			}
			else return NULL;
		}

		else if (key > current->key) {
			if (current->rightLinkType == CHILD) {
				current = current->right;
			}
			else return NULL;
		}
	}

	if (current == NULL) return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	if (root == NULL) return NULL;

	BSTNode* p = root;
	BSTNode* q = NULL;

	while (p) {
		q = p;
		p = p->left;
	}

	return q;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	if (root == NULL) return NULL;

	BSTNode* p = root;
	BSTNode* q = NULL;

	while (p) {
		q = p;
		p = p->right;
	}

	return q;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	if (node->leftLinkType == CHILD) {
		BSTNode* current = node->left;
		while (current->rightLinkType == CHILD) {
			current = current->right;
		}
		return current;
	}
	else {
		BSTNode* current = node->left;
		while (current != NULL && current->rightLinkType == THREAD) {
			current = current->right;
		}
		return current;
	}
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	if (node->rightLinkType == CHILD) {
		BSTNode* current = node->right;
		while (current->leftLinkType == CHILD) {
			current = current->left;
		}
		return current;
	}
	else {
		BSTNode* current = node->right;
		while (current != NULL && current->leftLinkType == THREAD) {
			current = current->left;
		}
		return current;
	}
} // end-next