#include <algorithm>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <chrono>
#include <ctime>
#define LANGUAGE 1251

using namespace std;
const int lengthMas = 100000;
using namespace std::chrono;
int m = 1 + rand() % lengthMas;


enum Color
{
	black,
	red
};

enum Color1
{
	BLACK,
	RED
};


class BinaryTreeClass {
	struct Node
	{
		int key;
		Node* l = nullptr, * r = nullptr;
		Node(int key) {
			this->key = key;
		}
	} *root = nullptr;

	bool findKey(Node* n, int key, Node*& adressParent, Node*& adressChild) const {
		while ((n != nullptr) and (key != n->key)) {
			if (key > n->key) {
				adressParent = n;
				n = n->r;

			}
			else if (key < n->key) {
				adressParent = n;
				n = n->l;

			}
			if (n == nullptr)
				return false;
			if (key == n->key) {
				adressChild = n;
				return true;
			}
		}
	}
	bool findKey(Node* n, int key) const {
		while ((n != nullptr) and (key != n->key)) {
			if (key > n->key)
				n = n->r;
			else if (key < n->key)
				n = n->l;
			if (n == nullptr)
				return false;
			if (key == n->key)

				return true;
		}
	}



	Node* insert(Node* n, int key) {

		if (!n) {
			return new Node(key);

		}
		if (n->key < key) n->r = insert(n->r, key);
		else if (n->key > key) n->l = insert(n->l, key);
		return n;
	}

	void preorderPrint(Node* n) const {
		if (n == nullptr)
			return;

		cout << n->key << endl;		//������� ������� ��������
		preorderPrint(n->l);		//���� � ����� ���� (����������� ������)
		preorderPrint(n->r);		//���� �� ������ ������ (���� �� ���������� �����)
	}
	void postorderPrint(Node* n) const {
		if (n == nullptr)		//���� ����� �� ����� �������
			return;

		postorderPrint(n->l);	//���� �� ����� �� ����
		postorderPrint(n->r);	//���� �� ������ �� ����
		cout << n->key << endl;	//������� ��������

	}
	void inorderPrint(Node* n) const {
		if (n == nullptr)
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return;
		}
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				cout << top[i]->key << " ";	//������� ���� ������
				if (top[i]->l)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
			cout << endl;
		}
	}

	int hight(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				if (top[i]->l)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
		}
		return hight;
	}
	void destroy(Node* n) {
		if (n == nullptr) return;
		destroy(n->l);
		destroy(n->r);
		delete n;
	}

	Node* findMin(Node* n) {
		if (n->l) return findMin(n->l);
		else return n;
	}
	Node* removeMin(Node* n) {
		if (n->l == 0)
			return n->r;
		n->l = removeMin(n->l);
		//return n;
	}
	Node* remove(Node* n, int key) {
		if (!n) return 0;
		if (key < n->key) n->l = remove(n->l, key);
		else if (key > n->key)n->r = remove(n->r, key);
		else
		{
			Node* left = n->l;
			Node* right = n->r;
			delete n;
			if (!right) return left;
			Node* min = findMin(right);
			min->r = removeMin(right);
			min->l = left;
			return min;
		}
		return n;
	}

public:
	bool findKey(int key) const {
		return findKey(root, key);
	}
	void insert(int key) {
		root = insert(root, key);
	}
	void preorderPrint() {
		preorderPrint(root);
	}
	void postorderPrint() {
		postorderPrint(root);
	}
	void inorderPrint() {
		inorderPrint(root);
	}

	void deleteKey(int key) {
		root = remove(root, key);
	}

	void widthPrint() {
		widthPrint(root);
	}

	void destroy() {
		destroy(root);
	}
	void hight() {
		cout << hight(root);
	}
};
void bTree(int mas[]) {
	BinaryTreeClass binaryTree;

	int key;
	int choice;

	do {
		cout << endl << "---------------------------------------------------------------------" << endl;
		cout << "1. �������� �������" << endl;
		cout << "2. ����� ������� �� ����� (yes-���� ���� ����, no-���� ����� ���)" << endl;
		cout << "3. ������� ������ �� ����� (������ preorder)" << endl;
		cout << "4. ������� ������ �� ����� (�������� postorder)" << endl;
		cout << "5. ������� ������ �� ����� (������������ inorder)" << endl;
		cout << "6. ������� ������ �� ����� (�� ������)" << endl;
		cout << "7. ������� ������� �� �����" << endl;
		cout << "8. �������� ���� ���������" << endl;
		cout << "9.  ������� ������ ������" << endl;
		cout << "10. ������� ����� ��������" << endl;
		cout << "0. ��������� ���������" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "�������� ��������: ";
		cin >> choice;
		cout << "---------------------------------------------------------------------" << endl;

		switch (choice)
		{
		case 1:
			
			cout << endl << "������� ���� ��� ����������: ";
			cin >> key;
			
	
			binaryTree.insert(key);
			break;
		case 2:
			cout << endl << "������� ���� ������: ";
			cin >> key;
			if (binaryTree.findKey(key))
				cout << "Yes. ���� ������������ � ������" << endl;
			else
				cout << "No. ����� � ������ ���" << endl;
			break;

		case 3:
			cout << endl << "������: " << endl;
			binaryTree.preorderPrint();
			break;

		case 4:
			cout << endl << "������: " << endl;
			binaryTree.postorderPrint();
			break;

		case 5:
			cout << endl << "������: " << endl;
			binaryTree.inorderPrint();
			break;

		case 6:
			cout << endl << "������: " << endl;
			binaryTree.widthPrint();
			break;

		case 7:
			cout << endl << "������� ���� ��� ��������: ";
			cin >> key;
			binaryTree.deleteKey(key);
			break;


		case 9:
			cout << "������ ������: ";
			binaryTree.hight();
			break;
		case 0:
			binaryTree.destroy();
			break;
		
		}
		srand(time(0));
		auto begin = steady_clock::now();
		auto end = steady_clock::now();
		
		if (choice == 10) {
			
			cout << endl << "���������� �������� ������� ��������: ";
			int deleteKey;
			
			int time = 0;
			
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//������ �������
				binaryTree.deleteKey(deleteKey);
				end = steady_clock::now();//������ �������
				time += duration_cast<nanoseconds>(end - begin).count();
				binaryTree.insert(deleteKey);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "C������ ����� ���������� (� ��): " << befor << "," << after << endl;

		}

		if (choice == 8) {
			cout << endl << "������������� ����������: ";
			
			int time = 0;
			
			begin = steady_clock::now();//������ �������
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];
				binaryTree.insert(key);
			}
			end = steady_clock::now();//������ �������
			time = (end - begin).count();
			int befor = (end - begin).count() / 1000000;
			int after = ((end - begin).count() % 1000000)/10000;
			
			cout << endl << "����� ���������� (� ��): " << befor<<","<<after << endl;
			cout << "������ ������: ";
			binaryTree.hight();

		}
	} while (choice != 0);

}




class AvlTree {				//��� ������
	struct Node
	{
		int height;
		int key;
		Node* l = nullptr, * r = nullptr;
		Node(int key) {
			this->key = key;
			this->height = 1;

		}
	} *root = nullptr;


	bool findKey(Node* n, int key) const {
		while ((n != nullptr) and (key != n->key)) {		//������ �� �����
			if (key > n->key)
				n = n->r;
			else if (key < n->key)
				n = n->l;
			if (n == nullptr)
				return false;
			if (key == n->key)
				return true;
		}
	}

	int getHeight(Node* n) {		//�������� ������
		if (!n) return 0;
		else return n->height;
	}
	int bFactor(Node* n) {			//�������� ����� �����������
		return (getHeight(n->r) - getHeight(n->l));
	}
	void updateHeight(Node* n) {	//������������ ������ ��������
		n->height = max(getHeight(n->l), getHeight(n->r)) + 1;
	}
	void swap(Node* a, Node* b) {	//����� ������� ��� ��������
		int temp = a->key;
		a->key = b->key;
		b->key = temp;
	}
	Node* rightRotate(Node* n) {
		swap(n, n->l);
		Node* temp = n->r;
		n->r = n->l;
		n->l = n->r->l;
		n->r->l = n->r->r;
		n->r->r = temp;
		updateHeight(n->r);
		updateHeight(n);
		return n;

	}
	Node* leftRotate(Node* n) {
		swap(n, n->r);
		Node* temp = n->l;
		n->l = n->r;
		n->r = n->l->r;
		n->l->r = n->l->l;
		n->l->l = temp;
		updateHeight(n->l);
		updateHeight(n);
		return n;
	}
	Node* balance(Node* n) {		//������������
		updateHeight(n);			//���������� ������� ��� ������
		int balance = bFactor(n);
		if (balance == -2) {		//���������, ����� �� �������
			if (bFactor(n->l) > 0) leftRotate(n->l);	//�����-������ �������
			return rightRotate(n);
		}
		else if (balance == 2) {
			if (bFactor(n->r) < 0) rightRotate(n->r);	//������-����� �������
			return leftRotate(n);
		}
		return n;
	}

	Node* insert(Node* n, int key) { //������� �� �����
		if (!n) {
			return new Node(key);

		}

		if (key < n->key)
			n->l = insert(n->l, key);
		else
			n->r = insert(n->r, key);
		return balance(n);
	}

	void preorderPrint(Node* n) const {
		if (n == nullptr)
			return;

		cout << n->key << endl;		//������� ������� ��������
		preorderPrint(n->l);		//���� � ����� ���� (����������� ������)
		preorderPrint(n->r);		//���� �� ������ ������ (���� �� ���������� �����)
	}
	void postorderPrint(Node* n) const {
		if (n == nullptr)		//���� ����� �� ����� �������
			return;

		postorderPrint(n->l);	//���� �� ����� �� ����
		postorderPrint(n->r);	//���� �� ������ �� ����
		cout << n->key << endl;	//������� ��������

	}
	void inorderPrint(Node* n) const {
		if (n == nullptr)
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return;
		}
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				cout << top[i]->key << "|" << top[i]->height << " ";	//������� ���� ������
				if (top[i]->l)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
			cout << endl;
		}
	}

	int hight(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				if (top[i]->l)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
		}
		return hight;
	}

	Node* findMin(Node* n) {		//������� ����������� � ������ �����
		if (n->l) return findMin(n->l);
		else return n;
	}
	Node* removeMin(Node* n) {		//������� ������ ����� �������� ������������ �� �������
		if (n->l == 0)
			return n->r;
		n->l = removeMin(n->l);
		return balance(n);
	}
	Node* remove(Node* n, int key) {		//�������� ����
		if (!n) return 0;
		if (key < n->key) n->l = remove(n->l, key);	//������� ������ ����
		else if (key > n->key)n->r = remove(n->r, key);
		else		//����� �����
		{
			Node* left = n->l;
			Node* right = n->r;
			delete n;
			if (!right) return left;	//���� ��� ������ �������, �� ������ ������������
			Node* min = findMin(right);	//���� ������ ����, �� ������� ����������� �� ������ �����
			min->r = removeMin(right);	//� ������������ ������ ����������� ������ ����� ��������
			min->l = left;				//� ������������ ����� ����������� ����� ����� �� ����������
			return balance(min);		//����������� (� ����� �� �������� ��� ������������� � ������)
		}
		return balance(n);
	}
	void destroy(Node* n) {		//������� ������
		if (n == nullptr) return;
		destroy(n->l);
		destroy(n->r);
		delete n;
	}

public:
	bool findKey(int key) const {
		return findKey(root, key);
	}
	void insert(int key) {
		root = insert(root, key);

	}

	void preorderPrint() {
		preorderPrint(root);
	}
	void postorderPrint() {
		postorderPrint(root);
	}
	void inorderPrint() {
		inorderPrint(root);
	}
	void widthPrint() {
		widthPrint(root);
	}


	void remove(int key) {
		root = remove(root, key);
	}

	void destroy() {
		destroy(root);
	}
	void hight() {
		cout << hight(root);
	}
};
void avlTree(int mas[]) {
	AvlTree avltree;

	int key;
	int choice;

	do {
		cout << endl << "---------------------------------------------------------------------" << endl;
		cout << "1. �������� �������" << endl;
		cout << "2. ����� ������� �� ����� (yes-���� ���� ����, no-���� ����� ���)" << endl;
		cout << "3. ������� ������ �� ����� (������ preorder)" << endl;
		cout << "4. ������� ������ �� ����� (�������� postorder)" << endl;
		cout << "5. ������� ������ �� ����� (������������ inorder)" << endl;
		cout << "6. ������� ������ �� ����� (�� ������)" << endl;
		cout << "7. ������� ������� �� �����" << endl;
		cout << "8. ������� ����� �������" << endl;
		cout << "9. ������� ������ ������" << endl;
		cout << "10. ������� ����� ��������" << endl;
		cout << "0. ��������� ���������" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "�������� ��������: ";
		
		cout << "---------------------------------------------------------------------" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
			int i;
			cout << endl << "������� ���� ��� ����������: ";
			cin >> key;
			int j;
			
			
			avltree.insert(key);
			
			break;

		case 2:
			cout << endl << "������� ���� ������: ";
			cin >> key;
			if (avltree.findKey(key))
				cout << "Yes. ���� ������������ � ������" << endl;
			else
				cout << "No. ����� � ������ ���" << endl;
			break;

		case 3:
			cout << endl << "������: " << endl;
			avltree.preorderPrint();
			break;

		case 4:
			cout << endl << "������: " << endl;
			avltree.postorderPrint();
			break;

		case 5:
			cout << endl << "������: " << endl;
			avltree.inorderPrint();
			break;

		case 6:
			cout << endl << "������: " << endl;
			avltree.widthPrint();
			break;
		case 7:
			cout << endl << "������� ���� ��� ��������: ";
			cin >> key;
			avltree.remove(key);
			break;

		case 9:
			cout << "������ ������: ";
			avltree.hight();
			break;
		case 0:
			avltree.destroy();
			break;
		
		}
		srand(time(0));
		auto begin = steady_clock::now();
		auto end = steady_clock::now();
		
		if (choice == 8) {
			cout << endl << "���������� �������� ������� ����������: "<<endl;
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];	//��������� ������
				avltree.insert(key);
			}

			cout << "������ ������: ";
			avltree.hight();
			cout << endl << "���-�� ���������: " << lengthMas;

			int time = 0;
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				key = mas[i];
				begin = steady_clock::now();//������ �������
				avltree.insert(key);
				end = steady_clock::now();//������ �������
				time += duration_cast<nanoseconds>(end - begin).count();
				avltree.remove(key);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;
			

			cout << endl << "C������ ����� ���������� (� ��): " << time << endl;

			
		}

		if (choice == 10) {
			cout << endl << "���������� �������� ������� ��������: ";
			int deleteKey;
			//cin >> deleteKey;
			int time = 0;
			//clock_t startTime, endTime;
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//������ �������
				avltree.remove(deleteKey);
				end = steady_clock::now();//������ �������
				time += duration_cast<nanoseconds>(end - begin).count();
				avltree.insert(deleteKey);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "C������ ����� ���������� (� ��): " << time << endl;


			

		}
	} while (choice != 0);

}


class redBlackTree {				//rb ������
	struct Node
	{
		int key;
		boolean color;
		Node* l = nullptr, * r = nullptr, * p = nullptr;
		Node() {
			Node* l = nullptr,
				* r = nullptr,
				* p = nullptr;
			this->color = black;
		}
		Node(int key) {
			this->key = key;
			this->color = red;
			this->p = nullptr;
		}
	}
	*root = nil;

	void destroy(Node* n) {
		if (n == nullptr) return;
		destroy(n->l);
		destroy(n->r);
		delete n;
	}

	Node* nil = new Node();	//���� � ������ ������
	void createNode(Node* n, int key) {	//�������� ���� ��� �������
		n->p = nil;
		n->l = nil;
		n->r = nil;
		n->key = key;
		n->color = red;	//����������� ���� ����� ������� ����
	}

	bool nodeExist(Node* n) {	//���������� �� ����
		return ((n != nil) and (n != nullptr));
	}

	void swap(Node* a, Node* b) {	//����� ������� ��� ��������
		int temp = a->key;
		a->key = b->key;
		b->key = temp;
		temp = a->color;
		a->color = b->color;
		b->color = temp;
	}


	void rightRotate(Node* n) {
		swap(n, n->l);
		Node* temp = n->r;
		n->r = n->l;
		n->l = n->r->l;
		n->l->p = n;
		n->r->l = n->r->r;
		n->r->r = temp;
		n->r->r->p = n->r;

	}
	void leftRotate(Node* n) {
		swap(n, n->r);
		Node* temp = n->l;
		n->l = n->r;
		n->r = n->l->r;
		n->r->p = n;
		n->l->r = n->l->l;
		n->l->l = temp;
		n->l->l->p = n->l;
	}

	Node* findMin(Node* n) {		//������� ����������� � ������ �����
		if (n->l != nil) return findMin(n->l);
		else return n;
	}
	int hight(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				if (top[i]->l != nil)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
		}
		return hight;
	}
	void insert(Node* n, int key) {	//�������
		Node* currentNode = n;
		Node* parent = nil;
		while (nodeExist(currentNode)) {	//���� ������� ����������
			parent = currentNode;	//���� �� ������
			if (key < currentNode->key) currentNode = currentNode->l;
			else currentNode = currentNode->r;
		}
		Node* newNode = new Node();	//������� ����
		createNode(newNode, key);
		newNode->p = parent;	//����������� �������� ��� ����
		if (newNode->p == nil) { root = newNode; }	//����� �������� ���, �� ������
		else if (key < parent->key) parent->l = newNode;
		else parent->r = newNode;
		balanceTree(newNode);	//����������� ������
	}
	Node* findKey(Node* n, int key) {
		while ((nodeExist(n)) and (key != n->key)) {		//������ �� �����
			if (key > n->key)
				n = n->r;
			else if (key < n->key)
				n = n->l;
			if (!nodeExist(n))
				return nullptr;
			if (key == n->key)
				return n;
		}
	}

	void balanceTree(Node* n) {
		Node* uncle;
		while (n->p->color == red) {
			if (n->p == n->p->p->l) {	//���� �������� �����
				uncle = n->p->p->r;		//������� ����
				if (uncle->color == red) {//���� ���� �������
					uncle->color = black;//������ ���� ����, ��������
					n->p->color = black;
					n->p->p->color = red;//������� �������
					n = n->p->p;//��������� ������(� �������)
				}
				else {
					if (n == n->p->r) {	//���� ��� ������
						leftRotate(n->p);
					}
					n->p->color = red;//���� �������� ������
					n->p->p->color = black;
					n = n->p->p;
					rightRotate(n);
				}
			}
			else {
				uncle = n->p->p->l;	//�� �� ����� ��� ������ ���� (������� � ������ �������)
				if (uncle->color == red) {//���� ���� �������
					uncle->color = black;//������ ���� ����, ��������
					n->p->color = black;
					n->p->p->color = red;//������� �������
					n = n->p->p;//��������� ������(� �������)
				}
				else {
					if (n == n->p->l) {	//���� ��� ������
						rightRotate(n->p);
					}
					n->p->color = red;//���� �������� ������
					n->p->p->color = black;
					n = n->p->p;
					leftRotate(n);
				}
			}
		}
		root->color = black;
	}

	int childrenCount(Node* n) {
		if ((nodeExist(n->l)) and (nodeExist(n->r))) {
			return 2;
		}
		else if ((nodeExist(n->l)) or (nodeExist(n->r))) {
			return 1;
		}
		else
			return 0;
	}
	Node* getChild(Node* n) {
		if (nodeExist(n->l)) return n->l;
		else return n->r;
	}
	void transportNode(Node* toNode, Node* fromNode) {
		if (toNode == root) root = fromNode;
		else if (toNode == toNode->p->l) toNode->p->l = fromNode;
		else toNode->p->r = fromNode;
		fromNode->p = toNode->p;


	}

	void delete_balance(Node* node) {
		while (node != root && node->color == black) {
			if (node == node->p->l) {
				Node* leftCh = node->p->r;
				if (leftCh->color == red) {
					leftCh->color = black;
					node->p->color = red;
					leftRotate(node->p);
					//leftCh = node->p->r;
				}
				if (leftCh->l->color == black && leftCh->r->color == black) {
					leftCh->color = red;
					node = node->p;
				}
				else {
					if (leftCh->r->color == black) {
						leftCh->l->color = black;
						leftCh->color = red;
						rightRotate(leftCh);
						//leftCh = node->p->r;
					}
					leftCh->color = node->p->color;
					node->p->color = black;
					leftCh->r->color = black;
					leftRotate(node->p);
					node = root;
				}
			}
			else {
				Node* rightCh = node->p->l;
				if (rightCh->color == red) {
					rightCh->color = black;
					node->p->color = red;
					rightRotate(node->p);
					rightCh = node->p->l;
				}
				if (rightCh->r->color == black && rightCh->l->color == black) {
					rightCh->color = red;
					node = node->p;
				}
				else {
					if (rightCh->l->color == black) {
						rightCh->r->color = black;
						rightCh->color = red;
						leftRotate(rightCh);
						rightCh = node->p->l;
					}
					rightCh->color = node->p->color;
					node->p->color = black;
					rightCh->l->color = black;
					rightRotate(node->p);
					node = root;
				}
			}
		}
		node->color = black;
	}

	void fixAfterRemove(Node* n) {
		while (n != root && n->color == black) {
			Node* brother;
			if (n == n->p->l) {		//���� ������� ����� �������
				brother = n->p->r;	//��� ���� ������
				if (brother->color == red) {	//���� ���� �������
					brother->color = black;		//���� ����� ������
					n->p->color = red;			//�������� �������
					leftRotate(n->p);
					return;
				}

				if (brother->l->color == black && brother->r->color == black) {	//���� � ����� ���� ������
					if (brother->p == root) {
						brother->color = red;
					}
					else if (brother->p->color == red) {
						brother->p->color = black;
						brother->color = red;
					}
					else {
						brother->p->color = red;
						leftRotate(n->p);
					}

					n = n->p;	//���� �������� ��� �������, �� � ����� ������� ����(�����)
				}
				else {
					if (brother->r->color == black) {	//���� ����� ������(����� �������)
						brother->l->color = black;
						brother->color == red;
						rightRotate(brother);
						brother = n->p->r;
					}
					brother->color = n->p->color;	//���� �����=����� ��������
					//�� ������ ����� �� �����������, � �� ������ �������� ��
					n->p->color = black;		//�������� ������
					brother->r->color = black;	//����� ������
					leftRotate(n->p);
					//����� �������� ���� ����� �� ������ ����� (� ���� ���� ��������)
					n = root;	//����� ����������� ������ � ������, ���� �� ����� ������
				}
			}
			else {
				brother = n->p->l;
				if (brother->color == red) {		//��������
					brother->color = black;
					n->p->color = red;
					rightRotate(n->p);
					return;
				}
				if (brother->l->color == black && brother->r->color == black) {
					rightRotate(n->p);
					brother = n->p->l;
				}
				else {
					if (brother->l->color == black) {
						brother->r->color = black;
						brother->color == red;
						leftRotate(brother);
						brother = n->p->l;
					}
					brother->color = n->p->color;
					n->p->color = black;
					brother->l->color = black;
					rightRotate(n->p);
					n = root;
				}
			}
		}
		n->color = black;
	}

	void remove(Node* n, int key) {
		Node* nodeRemove = findKey(root, key);
		bool nodeRemoveColor = nodeRemove->color;
		Node* child;
		if (childrenCount(nodeRemove) < 2) {
			child = getChild(nodeRemove);
			transportNode(nodeRemove, child);
		}
		else {
			Node* minNode = findMin(nodeRemove->r);
			nodeRemove->key = minNode->key;
			nodeRemoveColor = minNode->color;
			child = getChild(minNode);
			transportNode(minNode, child);
		}
		//if (nodeRemoveColor == black) fixAfterRemove(child);
		if (nodeRemoveColor == black) delete_balance(child);
	}

	void preorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		cout << n->key << endl;		//������� ������� ��������
		preorderPrint(n->l);		//���� � ����� ���� (����������� ������)
		preorderPrint(n->r);		//���� �� ������ ������ (���� �� ���������� �����)
	}
	void postorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		postorderPrint(n->l);	//���� �� ����� �� ����
		postorderPrint(n->r);	//���� �� ������ �� ����
		cout << n->key << endl;	//������� ��������

	}
	void inorderPrint(Node* n) {

		if (!nodeExist(n))
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (root == nullptr) {
			return;
		}
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������

				cout << "\t" << top[i]->key << "|";	//������� ���� ������
				if (top[i]->color) cout << "red  ";
				else cout << "black  ";
				if (top[i]->l != nil)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
			cout << endl;
		}
	}


public:
	void insert(int key) {
		insert(root, key);
		
	}
	void destroy() {
		destroy(root);
	}

	bool findKey(int key) {
		Node* n;
		n = findKey(root, key);
		if (n == nullptr) return false;
		else return true;
	}

	void preorderPrint() {
		preorderPrint(root);
	}
	void postorderPrint() {
		postorderPrint(root);
	}
	void inorderPrint() {
		inorderPrint(root);
	}
	void widthPrint() {
		widthPrint(root);
	}
	void remove(int key) {

		remove(root, key);
	}
	void hight() {
		cout << hight(root);
	}
	

};
void rbTree(int mas[]) {
	redBlackTree rbtree;
	clock_t startTime, endTime;
	int key;
	int choice;


	do {
		cout << endl << "---------------------------------------------------------------------" << endl;
		cout << "1. �������� �������" << endl;
		cout << "2. ����� ������� �� ����� (yes-���� ���� ����, no-���� ����� ���)" << endl;
		cout << "3. ������� ������ �� ����� (������ preorder)" << endl;
		cout << "4. ������� ������ �� ����� (�������� postorder)" << endl;
		cout << "5. ������� ������ �� ����� (������������ inorder)" << endl;
		cout << "6. ������� ������ �� ����� (�� ������)" << endl;
		cout << "7. ������� ������� �� �����" << endl;
		cout << "8. ������� ����� �������" << endl;
		cout << "9. ������� ������ ������" << endl;
		cout << "10. ������� ����� ��������" << endl;
		cout << "0. ��������� ���������" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "�������� ��������: ";
		cin >> choice;
		cout << "---------------------------------------------------------------------" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			
			cout << endl << "������� ���� ��� ����������: ";
			cin >> key;
			int i;
			if (key == 0) {
				i = 1 + rand() % lengthMas;
				key = mas[i];
			}
			
			rbtree.insert(key);
			
			break;
		case 2:
			cout << endl << "������� ���� ������: ";
			cin >> key;
			if (rbtree.findKey(key))
				cout << "Yes. ���� ������������ � ������" << endl;
			else
				cout << "No. ����� � ������ ���" << endl;
			break;
		case 3:
			rbtree.preorderPrint();
			break;
		case 4:
			rbtree.postorderPrint();
			break;
		case 5:
			rbtree.inorderPrint();
			break;
		case 6:
			rbtree.widthPrint();
			break;
		case 7:
			cout << endl << "������� ���� ��� ��������: ";
			cin >> key;
			rbtree.remove(key);
			break;


		case 9:
			cout << "������ ������: ";
			rbtree.hight();
			break;

			break;
		case 0:
			rbtree.destroy();
			break;

		
		}
		srand(time(0));
		auto begin = steady_clock::now();
		auto end = steady_clock::now();

		if (choice == 10) {
			cout << endl << "���������� �������� ������� ��������: ";
			int deleteKey;
			long time = 0;
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//������ �������
				rbtree.remove(deleteKey);
				end = steady_clock::now();//������ �������
				time += duration_cast<nanoseconds>(end - begin).count();
				rbtree.insert(deleteKey);
			}

			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "C������ ����� ���������� (� ��): " <<time << endl;


		}

		if (choice == 8) {
			cout << endl << "���������� �������� ������� ����������: " << endl;
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];	//��������� ������
				rbtree.insert(key);
			}

			cout << "������ ������: ";
			rbtree.hight();
			cout << endl << "���-�� ���������: " << lengthMas;

			int time = 0;
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				key = mas[i];
				begin = steady_clock::now();//������ �������
				rbtree.insert(key);
				end = steady_clock::now();//������ �������
				time += duration_cast<nanoseconds>(end - begin).count();
				rbtree.remove(key);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;
			

			cout << endl << "C������ ����� ���������� (� ��): " << time << endl;
		}
	} while (choice != 0);

}


class redBlackTree1 {				//rb ������
	struct Node
	{
		int key;
		boolean color;
		Node* l = nullptr, * r = nullptr, * p = nullptr;
		Node() {
			Node* l = nullptr,
				* r = nullptr,
				* p = nullptr;
			this->color = black;
		}
		Node(int key) {
			this->key = key;
			this->color = red;
			this->p = nullptr;
		}
	}
	*root = nil;

	void destroy(Node* n) {
		if (n == nullptr) return;
		destroy(n->l);
		destroy(n->r);
		delete n;
	}

	Node* nil = new Node();	//���� � ������ ������
	void createNode(Node* n, int key) {	//�������� ���� ��� �������
		n->p = nullptr;
		n->l = nil;
		n->r = nil;
		n->key = key;
		n->color = red;	//����������� ���� ����� ������� ����
	}

	bool nodeExist(Node* n) {	//���������� �� ����
		return ((n != nil) and (n != nullptr));
	}

	void swap(Node* a, Node* b) {	//����� ������� ��� ��������
		int temp = a->key;
		a->key = b->key;
		b->key = temp;
		temp = a->color;
		a->color = b->color;
		b->color = temp;
	}


	void rightRotate(Node* n) {
		swap(n, n->l);
		Node* temp = n->r;
		n->r = n->l;
		n->l = n->r->l;
		n->l->p = n;
		n->r->l = n->r->r;
		n->r->r = temp;
		n->r->r->p = n->r;

	}
	void leftRotate(Node* n) {
		swap(n, n->r);
		Node* temp = n->l;
		n->l = n->r;
		n->r = n->l->r;
		n->r->p = n;
		n->l->r = n->l->l;
		n->l->l = temp;
		n->l->l->p = n->l;
	}

	Node* findMin(Node* n) {		//������� ����������� � ������ �����
		if (n->l != nil) return findMin(n->l);
		else return n;
	}
	int hight(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������
				if (top[i]->l != nil)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
		}
		return hight;
	}
	void insert(Node* n, int key) {	//�������
		Node* currentNode = n;
		Node* parent = nil;
		while (nodeExist(currentNode)) {	//���� ������� ����������
			parent = currentNode;	//���� �� ������
			if (key < currentNode->key) currentNode = currentNode->l;
			else currentNode = currentNode->r;
		}
		Node* newNode = new Node();	//������� ����
		createNode(newNode, key);
		newNode->p = parent;	//����������� �������� ��� ����
		if (newNode->p == nil) { root = newNode; root->p = nullptr; }	//����� �������� ���, �� ������
		else if (key < parent->key) parent->l = newNode;
		else parent->r = newNode;
		balanceTree(newNode);	//����������� ������
	}
	Node* findKey(Node* n, int key) {
		while ((nodeExist(n)) and (key != n->key)) {		//������ �� �����
			if (key > n->key)
				n = n->r;
			else if (key < n->key)
				n = n->l;
			if (!nodeExist(n))
				return nullptr;
			if (key == n->key)
				return n;
		}
	}

	void balanceTree(Node* n) {
		Node* uncle;
		while (n->p->color == red) {
			if (n->p == n->p->p->l) {	//���� �������� �����
				uncle = n->p->p->r;		//������� ����
				if (uncle->color == red) {//���� ���� �������
					uncle->color = black;//������ ���� ����, ��������
					n->p->color = black;
					n->p->p->color = red;//������� �������
					n = n->p->p;//��������� ������(� �������)
				}
				else {
					if (n == n->p->r) {	//���� ��� ������
						leftRotate(n->p);
					}
					n->p->color = red;//���� �������� ������
					n->p->p->color = black;
					n = n->p->p;
					rightRotate(n);
				}
			}
			else {
				uncle = n->p->p->l;	//�� �� ����� ��� ������ ���� (������� � ������ �������)
				if (uncle->color == red) {//���� ���� �������
					uncle->color = black;//������ ���� ����, ��������
					n->p->color = black;
					n->p->p->color = red;//������� �������
					n = n->p->p;//��������� ������(� �������)
				}
				else {
					if (n == n->p->l) {	//���� ��� ������
						rightRotate(n->p);
					}
					n->p->color = red;//���� �������� ������
					n->p->p->color = black;
					n = n->p->p;
					leftRotate(n);
				}
			}
		}
		root->color = black;
	}

	int childrenCount(Node* n) {
		if ((nodeExist(n->l)) and (nodeExist(n->r))) {
			return 2;
		}
		else if ((nodeExist(n->l)) or (nodeExist(n->r))) {
			return 1;
		}
		else
			return 0;
	}
	Node* getChild(Node* n) {
		if (nodeExist(n->l)) return n->l;
		else return n->r;
	}
	void transportNode(Node* toNode, Node* fromNode) {
		if (toNode == root) root = fromNode;
		else if (toNode == toNode->p->l) toNode->p->l = fromNode;
		else toNode->p->r = fromNode;
		fromNode->p = toNode->p;


	}

	void delete_balance(Node* node) {
		while (node != root && node->color == black) {
			if (node == node->p->l) {
				Node* leftCh = node->p->r;
				if (leftCh->color == red) {
					leftCh->color = black;
					node->p->color = red;
					leftRotate(node->p);
					//leftCh = node->p->r;
				}
				if (leftCh->l->color == black && leftCh->r->color == black) {
					leftCh->color = red;
					node = node->p;
				}
				else {
					if (leftCh->r->color == black) {
						leftCh->l->color = black;
						leftCh->color = red;
						rightRotate(leftCh);
						//leftCh = node->p->r;
					}
					leftCh->color = node->p->color;
					node->p->color = black;
					leftCh->r->color = black;
					leftRotate(node->p);
					node = root;
				}
			}
			else {
				Node* rightCh = node->p->l;
				if (rightCh->color == red) {
					rightCh->color = black;
					node->p->color = red;
					rightRotate(node->p);
					rightCh = node->p->l;
				}
				if (rightCh->r->color == black && rightCh->l->color == black) {
					rightCh->color = red;
					node = node->p;
				}
				else {
					if (rightCh->l->color == black) {
						rightCh->r->color = black;
						rightCh->color = red;
						leftRotate(rightCh);
						rightCh = node->p->l;
					}
					rightCh->color = node->p->color;
					node->p->color = black;
					rightCh->l->color = black;
					rightRotate(node->p);
					node = root;
				}
			}
		}
		node->color = black;
	}

	void fixAfterRemove(Node* n) {
		while (n != root && n->color == black) {
			Node* brother;
			if (n == n->p->l) {		//���� ������� ����� �������
				brother = n->p->r;	//��� ���� ������
				if (brother->color == red) {	//���� ���� �������
					brother->color = black;		//���� ����� ������
					n->p->color = red;			//�������� �������
					leftRotate(n->p);
					return;
				}

				if (brother->l->color == black && brother->r->color == black) {	//���� � ����� ���� ������
					if (brother->p == root) {
						brother->color = red;
					}
					else if (brother->p->color == red) {
						brother->p->color = black;
						brother->color = red;
					}
					else {
						brother->p->color = red;
						leftRotate(n->p);
					}

					n = n->p;	//���� �������� ��� �������, �� � ����� ������� ����(�����)
				}
				else {
					if (brother->r->color == black) {	//���� ����� ������(����� �������)
						brother->l->color = black;
						brother->color == red;
						rightRotate(brother);
						brother = n->p->r;
					}
					brother->color = n->p->color;	//���� �����=����� ��������
					//�� ������ ����� �� �����������, � �� ������ �������� ��
					n->p->color = black;		//�������� ������
					brother->r->color = black;	//����� ������
					leftRotate(n->p);
					//����� �������� ���� ����� �� ������ ����� (� ���� ���� ��������)
					n = root;	//����� ����������� ������ � ������, ���� �� ����� ������
				}
			}
			else {
				brother = n->p->l;
				if (brother->color == red) {		//��������
					brother->color = black;
					n->p->color = red;
					rightRotate(n->p);
					return;
				}
				if (brother->l->color == black && brother->r->color == black) {
					rightRotate(n->p);
					brother = n->p->l;
				}
				else {
					if (brother->l->color == black) {
						brother->r->color = black;
						brother->color == red;
						leftRotate(brother);
						brother = n->p->l;
					}
					brother->color = n->p->color;
					n->p->color = black;
					brother->l->color = black;
					rightRotate(n->p);
					n = root;
				}
			}
		}
		n->color = black;
	}

	void remove(Node* n, int key) {
		Node* nodeRemove = findKey(root, key);
		bool nodeRemoveColor = nodeRemove->color;
		Node* child;
		if (childrenCount(nodeRemove) < 2) {
			child = getChild(nodeRemove);
			transportNode(nodeRemove, child);
		}
		else {
			Node* minNode = findMin(nodeRemove->r);
			nodeRemove->key = minNode->key;
			nodeRemoveColor = minNode->color;
			child = getChild(minNode);
			transportNode(minNode, child);
		}
		//if (nodeRemoveColor == black) fixAfterRemove(child);
		if (nodeRemoveColor == black) delete_balance(child);
	}

	void preorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		cout << n->key << endl;		//������� ������� ��������
		preorderPrint(n->l);		//���� � ����� ���� (����������� ������)
		preorderPrint(n->r);		//���� �� ������ ������ (���� �� ���������� �����)
	}
	void postorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		postorderPrint(n->l);	//���� �� ����� �� ����
		postorderPrint(n->r);	//���� �� ������ �� ����
		cout << n->key << endl;	//������� ��������

	}
	void inorderPrint(Node* n) {

		if (!nodeExist(n))
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//������ ������ (������)
		vector<Node*> tops_;	//������������� ������
		if (root == nullptr) {
			return;
		}
		top.push_back(root);	//����������� ������ �������
		while (!top.empty()) {	//���� ���� �������
			for (int i = 0; i < top.size(); i++) {	//�������� �� ���� �������� ������

				cout << "\t" << top[i]->key << "|";	//������� ���� ������
				if (top[i]->color) cout << "red  ";
				else cout << "black  ";
				if (top[i]->l != nil)				//��������� ������� ���� ������
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//������ ������ ��������� �� ���� �������
			tops_.clear();
			cout << endl;
		}
	}


public:
	void insert(int key) {
		insert(root, key);

	}
	void destroy() {
		destroy(root);
	}

	bool findKey(int key) {
		Node* n;
		n = findKey(root, key);
		if (n == nullptr) return false;
		else return true;
	}

	void preorderPrint() {
		preorderPrint(root);
	}
	void postorderPrint() {
		postorderPrint(root);
	}
	void inorderPrint() {
		inorderPrint(root);
	}
	void widthPrint() {
		widthPrint(root);
	}
	void remove(int key) {

		remove(root, key);
	}
	void hight() {
		cout << hight(root);
	}


};

int main()
{
	SetConsoleCP(LANGUAGE);
	SetConsoleOutputCP(LANGUAGE);

	int key;
	int choice;
	int choiceTree;
	int mas[lengthMas];
	srand(time(NULL));
	for (int i = 0; i < lengthMas+1; i++) {
		mas[i] = rand()+rand()+rand();
	}
	do {
		cout << endl << endl << endl << "---------------------------------------------------------------------" << endl;
		cout << "�������� ������: ";
		cout << endl << "---------------------------------------------------------------------" << endl;
		cout << "1. �������� ������" << endl;
		cout << "2. ��� ������" << endl;
		cout << "3. �����-������� ������" << endl;
		cout << "0. ����� �� ���������";
		cout << endl << "---------------------------------------------------------------------" << endl;
		cin >> choiceTree;
		switch (choiceTree)
		{
		case 1:
			bTree(mas);
			break;

		case 2:
			avlTree(mas);
			break;
		case 3:
			rbTree(mas);
			break;
		}

	} while (choiceTree != 0);
	return 0;
	_getch();

}