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

		cout << n->key << endl;		//сначала выводим значение
		preorderPrint(n->l);		//идем в самое лево (параллельно выводя)
		preorderPrint(n->r);		//идем по правым веткам (пока не встретится левое)
	}
	void postorderPrint(Node* n) const {
		if (n == nullptr)		//если дошли до конца возврат
			return;

		postorderPrint(n->l);	//идем по левой до макс
		postorderPrint(n->r);	//идем по правой до макс
		cout << n->key << endl;	//выводим значение

	}
	void inorderPrint(Node* n) const {
		if (n == nullptr)
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return;
		}
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				cout << top[i]->key << " ";	//выводим ключ вершин
				if (top[i]->l)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
			tops_.clear();
			cout << endl;
		}
	}

	int hight(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				if (top[i]->l)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
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
		cout << "1. Добавить элемент" << endl;
		cout << "2. Найти элемент по ключу (yes-если ключ есть, no-если ключа нет)" << endl;
		cout << "3. Вывести список на экран (прямой preorder)" << endl;
		cout << "4. Вывести список на экран (обратный postorder)" << endl;
		cout << "5. Вывести список на экран (симметричный inorder)" << endl;
		cout << "6. Вывести список на экран (по ширине)" << endl;
		cout << "7. Удалить элемент по ключу" << endl;
		cout << "8. Добавить кучу элементов" << endl;
		cout << "9.  Вывести высоту дерева" << endl;
		cout << "10. Среднее время удаления" << endl;
		cout << "0. Завершить программу" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "Выберите действие: ";
		cin >> choice;
		cout << "---------------------------------------------------------------------" << endl;

		switch (choice)
		{
		case 1:
			
			cout << endl << "Введите ключ для добавления: ";
			cin >> key;
			
	
			binaryTree.insert(key);
			break;
		case 2:
			cout << endl << "Введите ключ поиска: ";
			cin >> key;
			if (binaryTree.findKey(key))
				cout << "Yes. Ключ присутствует в дереве" << endl;
			else
				cout << "No. Ключа в дереве нет" << endl;
			break;

		case 3:
			cout << endl << "Список: " << endl;
			binaryTree.preorderPrint();
			break;

		case 4:
			cout << endl << "Список: " << endl;
			binaryTree.postorderPrint();
			break;

		case 5:
			cout << endl << "Список: " << endl;
			binaryTree.inorderPrint();
			break;

		case 6:
			cout << endl << "Список: " << endl;
			binaryTree.widthPrint();
			break;

		case 7:
			cout << endl << "Введите ключ для удаления: ";
			cin >> key;
			binaryTree.deleteKey(key);
			break;


		case 9:
			cout << "Высота дерева: ";
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
			
			cout << endl << "Вычисление среднего времени удаления: ";
			int deleteKey;
			
			int time = 0;
			
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//начало таймера
				binaryTree.deleteKey(deleteKey);
				end = steady_clock::now();//начало таймера
				time += duration_cast<nanoseconds>(end - begin).count();
				binaryTree.insert(deleteKey);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "Cреднее время выполнения (в мс): " << befor << "," << after << endl;

		}

		if (choice == 8) {
			cout << endl << "Множественное добавление: ";
			
			int time = 0;
			
			begin = steady_clock::now();//начало таймера
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];
				binaryTree.insert(key);
			}
			end = steady_clock::now();//начало таймера
			time = (end - begin).count();
			int befor = (end - begin).count() / 1000000;
			int after = ((end - begin).count() % 1000000)/10000;
			
			cout << endl << "Время выполнения (в мс): " << befor<<","<<after << endl;
			cout << "Высота дерева: ";
			binaryTree.hight();

		}
	} while (choice != 0);

}




class AvlTree {				//авл дерево
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
		while ((n != nullptr) and (key != n->key)) {		//происк по ключу
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

	int getHeight(Node* n) {		//получить высоту
		if (!n) return 0;
		else return n->height;
	}
	int bFactor(Node* n) {			//разность высот наследников
		return (getHeight(n->r) - getHeight(n->l));
	}
	void updateHeight(Node* n) {	//обнововление высоты родителя
		n->height = max(getHeight(n->l), getHeight(n->r)) + 1;
	}
	void swap(Node* a, Node* b) {	//обмен ключами для поворота
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
	Node* balance(Node* n) {		//балансировка
		updateHeight(n);			//рекурсивно обновим все высоты
		int balance = bFactor(n);
		if (balance == -2) {		//проверяем, нужен ли поворот
			if (bFactor(n->l) > 0) leftRotate(n->l);	//левый-правый поворот
			return rightRotate(n);
		}
		else if (balance == 2) {
			if (bFactor(n->r) < 0) rightRotate(n->r);	//правый-левый поворот
			return leftRotate(n);
		}
		return n;
	}

	Node* insert(Node* n, int key) { //вставка по ключу
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

		cout << n->key << endl;		//сначала выводим значение
		preorderPrint(n->l);		//идем в самое лево (параллельно выводя)
		preorderPrint(n->r);		//идем по правым веткам (пока не встретится левое)
	}
	void postorderPrint(Node* n) const {
		if (n == nullptr)		//если дошли до конца возврат
			return;

		postorderPrint(n->l);	//идем по левой до макс
		postorderPrint(n->r);	//идем по правой до макс
		cout << n->key << endl;	//выводим значение

	}
	void inorderPrint(Node* n) const {
		if (n == nullptr)
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return;
		}
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				cout << top[i]->key << "|" << top[i]->height << " ";	//выводим ключ вершин
				if (top[i]->l)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
			tops_.clear();
			cout << endl;
		}
	}

	int hight(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				if (top[i]->l)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
			tops_.clear();
		}
		return hight;
	}

	Node* findMin(Node* n) {		//находим минимальное в правой ветке
		if (n->l) return findMin(n->l);
		else return n;
	}
	Node* removeMin(Node* n) {		//находим правую ветку родителя минимального из правого
		if (n->l == 0)
			return n->r;
		n->l = removeMin(n->l);
		return balance(n);
	}
	Node* remove(Node* n, int key) {		//удаление узла
		if (!n) return 0;
		if (key < n->key) n->l = remove(n->l, key);	//находим нужный узел
		else if (key > n->key)n->r = remove(n->r, key);
		else		//когда нашли
		{
			Node* left = n->l;
			Node* right = n->r;
			delete n;
			if (!right) return left;	//если нет справа ребенка, то просто присоединяем
			Node* min = findMin(right);	//если правый есть, то находим минимальный из правой ветки
			min->r = removeMin(right);	//к минимальному справа присваеваем правую ветвь родителя
			min->l = left;				//к минимальному слева присваиваем левую часть от удаляемого
			return balance(min);		//балансируем (а потом по рекурсии это присваевается к дереву)
		}
		return balance(n);
	}
	void destroy(Node* n) {		//удалить дерево
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
		cout << "1. Добавить элемент" << endl;
		cout << "2. Найти элемент по ключу (yes-если ключ есть, no-если ключа нет)" << endl;
		cout << "3. Вывести список на экран (прямой preorder)" << endl;
		cout << "4. Вывести список на экран (обратный postorder)" << endl;
		cout << "5. Вывести список на экран (симметричный inorder)" << endl;
		cout << "6. Вывести список на экран (по ширине)" << endl;
		cout << "7. Удалить элемент по ключу" << endl;
		cout << "8. Среднее время всатвки" << endl;
		cout << "9. Вывести высоту дерева" << endl;
		cout << "10. Среднее время удаления" << endl;
		cout << "0. Завершить программу" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "Выберите действие: ";
		
		cout << "---------------------------------------------------------------------" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
			int i;
			cout << endl << "Введите ключ для добавления: ";
			cin >> key;
			int j;
			
			
			avltree.insert(key);
			
			break;

		case 2:
			cout << endl << "Введите ключ поиска: ";
			cin >> key;
			if (avltree.findKey(key))
				cout << "Yes. Ключ присутствует в дереве" << endl;
			else
				cout << "No. Ключа в дереве нет" << endl;
			break;

		case 3:
			cout << endl << "Список: " << endl;
			avltree.preorderPrint();
			break;

		case 4:
			cout << endl << "Список: " << endl;
			avltree.postorderPrint();
			break;

		case 5:
			cout << endl << "Список: " << endl;
			avltree.inorderPrint();
			break;

		case 6:
			cout << endl << "Список: " << endl;
			avltree.widthPrint();
			break;
		case 7:
			cout << endl << "Введите ключ для удаления: ";
			cin >> key;
			avltree.remove(key);
			break;

		case 9:
			cout << "Высота дерева: ";
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
			cout << endl << "Вычисление среднего времени добавления: "<<endl;
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];	//заполняем дерево
				avltree.insert(key);
			}

			cout << "Высота дерева: ";
			avltree.hight();
			cout << endl << "Кол-во элементов: " << lengthMas;

			int time = 0;
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				key = mas[i];
				begin = steady_clock::now();//начало таймера
				avltree.insert(key);
				end = steady_clock::now();//начало таймера
				time += duration_cast<nanoseconds>(end - begin).count();
				avltree.remove(key);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;
			

			cout << endl << "Cреднее время выполнения (в мс): " << time << endl;

			
		}

		if (choice == 10) {
			cout << endl << "Вычисление среднего времени удаления: ";
			int deleteKey;
			//cin >> deleteKey;
			int time = 0;
			//clock_t startTime, endTime;
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//начало таймера
				avltree.remove(deleteKey);
				end = steady_clock::now();//начало таймера
				time += duration_cast<nanoseconds>(end - begin).count();
				avltree.insert(deleteKey);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "Cреднее время выполнения (в мс): " << time << endl;


			

		}
	} while (choice != 0);

}


class redBlackTree {				//rb дерево
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

	Node* nil = new Node();	//нода с черным цветом
	void createNode(Node* n, int key) {	//создание ноды для вставки
		n->p = nil;
		n->l = nil;
		n->r = nil;
		n->key = key;
		n->color = red;	//вставляемая нода имеет красный цвет
	}

	bool nodeExist(Node* n) {	//существует ли нода
		return ((n != nil) and (n != nullptr));
	}

	void swap(Node* a, Node* b) {	//обмен ключами для поворота
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

	Node* findMin(Node* n) {		//находим минимальное в правой ветке
		if (n->l != nil) return findMin(n->l);
		else return n;
	}
	int hight(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				if (top[i]->l != nil)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
			tops_.clear();
		}
		return hight;
	}
	void insert(Node* n, int key) {	//вставка
		Node* currentNode = n;
		Node* parent = nil;
		while (nodeExist(currentNode)) {	//пока ребенок существует
			parent = currentNode;	//идем по списку
			if (key < currentNode->key) currentNode = currentNode->l;
			else currentNode = currentNode->r;
		}
		Node* newNode = new Node();	//создаем ноду
		createNode(newNode, key);
		newNode->p = parent;	//присваиваем родителя для ноды
		if (newNode->p == nil) { root = newNode; }	//несли родителя нет, то корень
		else if (key < parent->key) parent->l = newNode;
		else parent->r = newNode;
		balanceTree(newNode);	//балансируем дерево
	}
	Node* findKey(Node* n, int key) {
		while ((nodeExist(n)) and (key != n->key)) {		//происк по ключу
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
			if (n->p == n->p->p->l) {	//если родитель слева
				uncle = n->p->p->r;		//находим дядю
				if (uncle->color == red) {//если дядя красный
					uncle->color = black;//меняем цвет дяди, родителя
					n->p->color = black;
					n->p->p->color = red;//дедушка красный
					n = n->p->p;//переходим наверх(к дедушке)
				}
				else {
					if (n == n->p->r) {	//если сын справа
						leftRotate(n->p);
					}
					n->p->color = red;//цвет родителя меняем
					n->p->p->color = black;
					n = n->p->p;
					rightRotate(n);
				}
			}
			else {
				uncle = n->p->p->l;	//то же самое для левого дяди (поворот в другую сторону)
				if (uncle->color == red) {//если дядя красный
					uncle->color = black;//меняем цвет дяди, родителя
					n->p->color = black;
					n->p->p->color = red;//дедушка красный
					n = n->p->p;//переходим наверх(к дедушке)
				}
				else {
					if (n == n->p->l) {	//если сын справа
						rightRotate(n->p);
					}
					n->p->color = red;//цвет родителя меняем
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
			if (n == n->p->l) {		//если элемент левый ребенок
				brother = n->p->r;	//его брат справа
				if (brother->color == red) {	//если брат красный
					brother->color = black;		//цвет брата черный
					n->p->color = red;			//родитель красный
					leftRotate(n->p);
					return;
				}

				if (brother->l->color == black && brother->r->color == black) {	//если у брата дети черные
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

					n = n->p;	//если родитель был красным, он в итоге поменят цвет(потом)
				}
				else {
					if (brother->r->color == black) {	//если правй черный(левый красный)
						brother->l->color = black;
						brother->color == red;
						rightRotate(brother);
						brother = n->p->r;
					}
					brother->color = n->p->color;	//цвет брата=цветц родителя
					//на высоте брата не отобразится, а на высоте родителя да
					n->p->color = black;		//родитель черный
					brother->r->color = black;	//првый черный
					leftRotate(n->p);
					//после поворота брат встал на первое место (у него цвет родителя)
					n = root;	//чтобы перекрасить корень в черный, если он таким станет
				}
			}
			else {
				brother = n->p->l;
				if (brother->color == red) {		//ИСПРАВИЛ
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

		cout << n->key << endl;		//сначала выводим значение
		preorderPrint(n->l);		//идем в самое лево (параллельно выводя)
		preorderPrint(n->r);		//идем по правым веткам (пока не встретится левое)
	}
	void postorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		postorderPrint(n->l);	//идем по левой до макс
		postorderPrint(n->r);	//идем по правой до макс
		cout << n->key << endl;	//выводим значение

	}
	void inorderPrint(Node* n) {

		if (!nodeExist(n))
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (root == nullptr) {
			return;
		}
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня

				cout << "\t" << top[i]->key << "|";	//выводим ключ вершин
				if (top[i]->color) cout << "red  ";
				else cout << "black  ";
				if (top[i]->l != nil)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
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
		cout << "1. Добавить элемент" << endl;
		cout << "2. Найти элемент по ключу (yes-если ключ есть, no-если ключа нет)" << endl;
		cout << "3. Вывести список на экран (прямой preorder)" << endl;
		cout << "4. Вывести список на экран (обратный postorder)" << endl;
		cout << "5. Вывести список на экран (симметричный inorder)" << endl;
		cout << "6. Вывести список на экран (по ширине)" << endl;
		cout << "7. Удалить элемент по ключу" << endl;
		cout << "8. Среднее время вставки" << endl;
		cout << "9. Вывести высоту дерева" << endl;
		cout << "10. Среднее время удаления" << endl;
		cout << "0. Завершить программу" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		cout << endl << "Выберите действие: ";
		cin >> choice;
		cout << "---------------------------------------------------------------------" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			
			cout << endl << "Введите ключ для добавления: ";
			cin >> key;
			int i;
			if (key == 0) {
				i = 1 + rand() % lengthMas;
				key = mas[i];
			}
			
			rbtree.insert(key);
			
			break;
		case 2:
			cout << endl << "Введите ключ поиска: ";
			cin >> key;
			if (rbtree.findKey(key))
				cout << "Yes. Ключ присутствует в дереве" << endl;
			else
				cout << "No. Ключа в дереве нет" << endl;
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
			cout << endl << "Введите ключ для удаления: ";
			cin >> key;
			rbtree.remove(key);
			break;


		case 9:
			cout << "Высота дерева: ";
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
			cout << endl << "Вычисление среднего времени удаления: ";
			int deleteKey;
			long time = 0;
			
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				deleteKey = mas[i];
				begin = steady_clock::now();//начало таймера
				rbtree.remove(deleteKey);
				end = steady_clock::now();//начало таймера
				time += duration_cast<nanoseconds>(end - begin).count();
				rbtree.insert(deleteKey);
			}

			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;

			cout << endl << "Cреднее время выполнения (в мс): " <<time << endl;


		}

		if (choice == 8) {
			cout << endl << "Вычисление среднего времени добавления: " << endl;
			for (int i = 0; i < lengthMas; i++) {
				key = mas[i];	//заполняем дерево
				rbtree.insert(key);
			}

			cout << "Высота дерева: ";
			rbtree.hight();
			cout << endl << "Кол-во элементов: " << lengthMas;

			int time = 0;
			for (int j = 0; j < lengthMas / 2; j++) {
				int i = 1 + rand() % lengthMas;
				key = mas[i];
				begin = steady_clock::now();//начало таймера
				rbtree.insert(key);
				end = steady_clock::now();//начало таймера
				time += duration_cast<nanoseconds>(end - begin).count();
				rbtree.remove(key);
			}
			time = time / (lengthMas / 2);
			int befor = time / 1000000;
			int after = (time % 1000000) / 10000;
			

			cout << endl << "Cреднее время выполнения (в мс): " << time << endl;
		}
	} while (choice != 0);

}


class redBlackTree1 {				//rb дерево
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

	Node* nil = new Node();	//нода с черным цветом
	void createNode(Node* n, int key) {	//создание ноды для вставки
		n->p = nullptr;
		n->l = nil;
		n->r = nil;
		n->key = key;
		n->color = red;	//вставляемая нода имеет красный цвет
	}

	bool nodeExist(Node* n) {	//существует ли нода
		return ((n != nil) and (n != nullptr));
	}

	void swap(Node* a, Node* b) {	//обмен ключами для поворота
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

	Node* findMin(Node* n) {		//находим минимальное в правой ветке
		if (n->l != nil) return findMin(n->l);
		else return n;
	}
	int hight(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (!root) {
			return 0;
		}
		int hight = 0;
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
				if (top[i]->l != nil)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			hight++;
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
			tops_.clear();
		}
		return hight;
	}
	void insert(Node* n, int key) {	//вставка
		Node* currentNode = n;
		Node* parent = nil;
		while (nodeExist(currentNode)) {	//пока ребенок существует
			parent = currentNode;	//идем по списку
			if (key < currentNode->key) currentNode = currentNode->l;
			else currentNode = currentNode->r;
		}
		Node* newNode = new Node();	//создаем ноду
		createNode(newNode, key);
		newNode->p = parent;	//присваиваем родителя для ноды
		if (newNode->p == nil) { root = newNode; root->p = nullptr; }	//несли родителя нет, то корень
		else if (key < parent->key) parent->l = newNode;
		else parent->r = newNode;
		balanceTree(newNode);	//балансируем дерево
	}
	Node* findKey(Node* n, int key) {
		while ((nodeExist(n)) and (key != n->key)) {		//происк по ключу
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
			if (n->p == n->p->p->l) {	//если родитель слева
				uncle = n->p->p->r;		//находим дядю
				if (uncle->color == red) {//если дядя красный
					uncle->color = black;//меняем цвет дяди, родителя
					n->p->color = black;
					n->p->p->color = red;//дедушка красный
					n = n->p->p;//переходим наверх(к дедушке)
				}
				else {
					if (n == n->p->r) {	//если сын справа
						leftRotate(n->p);
					}
					n->p->color = red;//цвет родителя меняем
					n->p->p->color = black;
					n = n->p->p;
					rightRotate(n);
				}
			}
			else {
				uncle = n->p->p->l;	//то же самое для левого дяди (поворот в другую сторону)
				if (uncle->color == red) {//если дядя красный
					uncle->color = black;//меняем цвет дяди, родителя
					n->p->color = black;
					n->p->p->color = red;//дедушка красный
					n = n->p->p;//переходим наверх(к дедушке)
				}
				else {
					if (n == n->p->l) {	//если сын справа
						rightRotate(n->p);
					}
					n->p->color = red;//цвет родителя меняем
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
			if (n == n->p->l) {		//если элемент левый ребенок
				brother = n->p->r;	//его брат справа
				if (brother->color == red) {	//если брат красный
					brother->color = black;		//цвет брата черный
					n->p->color = red;			//родитель красный
					leftRotate(n->p);
					return;
				}

				if (brother->l->color == black && brother->r->color == black) {	//если у брата дети черные
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

					n = n->p;	//если родитель был красным, он в итоге поменят цвет(потом)
				}
				else {
					if (brother->r->color == black) {	//если правй черный(левый красный)
						brother->l->color = black;
						brother->color == red;
						rightRotate(brother);
						brother = n->p->r;
					}
					brother->color = n->p->color;	//цвет брата=цветц родителя
					//на высоте брата не отобразится, а на высоте родителя да
					n->p->color = black;		//родитель черный
					brother->r->color = black;	//првый черный
					leftRotate(n->p);
					//после поворота брат встал на первое место (у него цвет родителя)
					n = root;	//чтобы перекрасить корень в черный, если он таким станет
				}
			}
			else {
				brother = n->p->l;
				if (brother->color == red) {		//ИСПРАВИЛ
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

		cout << n->key << endl;		//сначала выводим значение
		preorderPrint(n->l);		//идем в самое лево (параллельно выводя)
		preorderPrint(n->r);		//идем по правым веткам (пока не встретится левое)
	}
	void postorderPrint(Node* n) {

		if (!nodeExist(n))
			return;

		postorderPrint(n->l);	//идем по левой до макс
		postorderPrint(n->r);	//идем по правой до макс
		cout << n->key << endl;	//выводим значение

	}
	void inorderPrint(Node* n) {

		if (!nodeExist(n))
			return;
		inorderPrint(n->l);
		cout << n->key << endl;
		inorderPrint(n->r);
	}
	void widthPrint(Node* root) {
		vector<Node*> top;		//вектор вершин (ссылки)
		vector<Node*> tops_;	//промежуточный вектор
		if (root == nullptr) {
			return;
		}
		top.push_back(root);	//присваиваем первую вершину
		while (!top.empty()) {	//пока есть вершины
			for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня

				cout << "\t" << top[i]->key << "|";	//выводим ключ вершин
				if (top[i]->color) cout << "red  ";
				else cout << "black  ";
				if (top[i]->l != nil)				//формируем веришны след уровня
					tops_.push_back(top[i]->l);
				if (top[i]->r != nil)
					tops_.push_back(top[i]->r);
			}
			top.clear();
			top = tops_;	//вектор вершин переходит на след уровень
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
		cout << "Выберите дерево: ";
		cout << endl << "---------------------------------------------------------------------" << endl;
		cout << "1. Бинарное дерево" << endl;
		cout << "2. АВЛ дерево" << endl;
		cout << "3. Черно-красное дерево" << endl;
		cout << "0. Выйти из программы";
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