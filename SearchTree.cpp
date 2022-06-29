#include "SearchTree.h"
using namespace std;


SearchTree::SearchTree(): root_(nullptr), numberOfNodes(0){

}

SearchTree::~SearchTree() {
	makeEmpty();
	numberOfNodes = 0;
}

SearchTree::SearchTree(const SearchTree& copyTree){ 
	this->numberOfNodes = copyTree.numberOfNodes; 
	copyHelper(copyTree.root_, this->root_);
	
}

const SearchTree& SearchTree::operator=(const SearchTree& rhs) {
	if (rhs != *this) {
		//delete tree
		this->makeEmpty();
		copyHelper(rhs.root_, this->root_);
	}
	return *this;
}



bool SearchTree::operator==(const SearchTree& rhs) const {
	return comparingHelper(rhs.root_, this->root_); 
}

bool SearchTree::operator!=(const SearchTree& rhs) const {
	return !comparingHelper(rhs.root_, this->root_);
}


bool SearchTree::comparingHelper(Node* otherRoot, Node* thisRoot) const {
	if (otherRoot == nullptr && thisRoot == nullptr) {
		return true;
	}
	else if (otherRoot == nullptr && thisRoot != nullptr) {
		return false;
	}
	else if (otherRoot != nullptr && thisRoot == nullptr) {
		return false;
	}
	else {
		if (*otherRoot->data == *thisRoot->data &&
			otherRoot->count == thisRoot->count &&
			comparingHelper(otherRoot->leftChild, thisRoot->leftChild) &&
			comparingHelper(otherRoot->rightChild, thisRoot->rightChild)) {
			return true;
		}
		else {
			return false;
		}
	}
}


void SearchTree::copyHelper(Node* copyRoot, Node*& thisRoot) {
	
	if (copyRoot != nullptr) {
		thisRoot = new Node(); 
		thisRoot->data = new Comparable;
		*thisRoot->data = *copyRoot->data; 
		thisRoot->count = copyRoot->count; 
		copyHelper(copyRoot->leftChild, thisRoot->leftChild);
		copyHelper(copyRoot->rightChild, thisRoot->rightChild);
	}
	else {
		thisRoot = nullptr;
	}
}

bool SearchTree::insert(Comparable* data) {
	if (root_ == nullptr) {
		root_ = new Node();
		root_->data = data;
		root_->leftChild = nullptr;
		root_->rightChild = nullptr;
		root_->count++;
		this->numberOfNodes++;
		return true;
	}
	else {
		return insertHelper(root_, data);
	}

}

bool SearchTree::insertHelper(Node*& root, Comparable* data) {
	if (*root->data == *data) {
		root->count++;
		return false;
	}
	if (*data < *root->data) {
		if (root->leftChild == nullptr) {
			Node* newNode = new Node;
			newNode->data = data;
			root->leftChild = newNode;
			root->leftChild->count++;
			this->numberOfNodes++;
			return true;
		}
		return insertHelper(root->leftChild, data);
	}
	if (*data > *root->data) {
		if (root->rightChild == nullptr) {
			Node* newNode = new Node;
			newNode->data = data;
			root->rightChild = newNode;
			root->rightChild->count++;
			this->numberOfNodes++;
			return true;
		}
		return insertHelper(root->rightChild, data);
	}
	return false;
}

bool SearchTree::remove(const Comparable& data) {
	return deleteNode(root_, data);
}


bool SearchTree::deleteNode(Node*& root, const Comparable& data)
{
	if (root == nullptr)
		return false;
	else if (data == *root->data) {
		root->count--;
		deleteRoot(root);
		this->numberOfNodes--;
		return true;
	}
	else if (data < *root->data)
		return deleteNode(root->leftChild, data);
	else
		return deleteNode(root->rightChild, data);
}

void SearchTree::deleteRoot(Node*& root)
{
	delete root->data;

	if (root->leftChild == nullptr && root->rightChild == nullptr) {  
		delete root;
		root = nullptr;
	}
	else if (root->leftChild == nullptr || root->rightChild == nullptr) {
		Node* tmp = root;
		root = root->leftChild == nullptr ? root->rightChild : root->leftChild;
		delete tmp;
	}
	else {
		root->data = findAndDeleteMostLeft(root->rightChild);
	}
}

// Pre-condition: root is not nullptr
Comparable* SearchTree::findAndDeleteMostLeft(Node*& root)
{
	if (root->leftChild == nullptr) {
		Comparable* data = root->data;
		Node* junk = root;
		root = root->rightChild;
		delete junk;
		return data;
	}
	else
		return findAndDeleteMostLeft(root->leftChild);
}

const Comparable* SearchTree::retrieve(const Comparable& data) const {
	return retrieveHelper(root_, data);
}

const Comparable* SearchTree::retrieveHelper(const Node* root, const Comparable& data) const
{
	if (root == nullptr)
		return nullptr;
	else if (data == *root->data)
		return root->data;
	else if (data < *root->data)
		return retrieveHelper(root->leftChild, data);
	else
		return retrieveHelper(root->rightChild, data);
}

int SearchTree::depth(const Comparable& data) const {
	return depthHelper(root_, data);
}

int SearchTree::depthHelper(Node* root, const Comparable& data) const
{
	if (root == nullptr) {
		return -1;
	}
	if (*root->data == data) {
		return 0;
	}

	int branch = depthHelper(root->leftChild, data);
	//if branch in leftChild is nullptr, then try rightChild
	if (branch == -1) {
		branch = depthHelper(root->rightChild, data);
	}
	//if rightChild is nullptr return -1
	if (branch == -1) {
		return -1;
	}
	//if either left or right child is not nullptr add 1 
	else {
		return 1 + branch;
	}
}

int SearchTree::height(const Comparable& data) const {
	//start with height of -1
	int height = -1;
	//call heightHelper to update height 
	int maxHeight = heightHelper(root_, data, height);
	return height;
}

int SearchTree::heightHelper(Node* root, const Comparable& data,
	int& height) const {

	if (root == nullptr) {
		return -1;
	}

	int leftHeight = heightHelper(
		root->leftChild, data, height);

	int rightHeight
		= heightHelper(
			root->rightChild, data, height);

	//update height of the current node (root)
	int nodeHeight = max(leftHeight, rightHeight) + 1;

	//check to see if the current node is the node with data 
	if (*root->data == data)
		height = nodeHeight;

	return nodeHeight;
}


void SearchTree::makeEmpty() {
	makeEmptyHelper(this->root_);
}

void SearchTree::makeEmptyHelper(Node*& root) {
	if (root != nullptr) {
		makeEmptyHelper(root->leftChild);
		makeEmptyHelper(root->rightChild);
		root->data = nullptr; //set data to nullptr
		delete root;
		root = nullptr;
	}
}


ostream& operator<<(ostream& os, SearchTree& tree) {
	tree.inorderPrint(tree.root_);
	return os;
}

void SearchTree::inorderPrint(Node* root) {
	if (root != nullptr) {
		inorderPrint(root->leftChild);
		cout << *root->data << " " << root->count << endl;
		inorderPrint(root->rightChild);
	}
}

