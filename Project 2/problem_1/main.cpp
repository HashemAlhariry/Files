#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student
{
	char id[10];
	char name[50];
	char address[50];
};

struct PK
{
	char id[10];
	short offset;
	bool operator<(const PK& pk)
	{
		if(strcmp(id, pk.id) < 0)
			return true;
		else return false;
	}
	bool operator>(const PK& pk)
	{
		if(strcmp(id, pk.id) > 0)
			return true;
		else return false;
	}
	bool operator==(const PK& pk)
	{
		if(strcmp(id, pk.id) == 0)
			return true;
		else return false;
	}
	friend ostream& operator<<(ostream& out, PK pk)
	{
		for(int i = 0; i < 10; i++)
            out << pk.id[i];
		out << ' ' << pk.offset;
		return out;
	}
};

class AVL
{
	public:
		class node
		{
			public:
			    PK data;
			    int height;
			    node* leftChild;
			    node* rightChild;
			    node()
				{
				    leftChild = NULL;
				    rightChild = NULL;
				}
			    node(PK data, node *rightChild, node *leftChild) : data(data), leftChild(leftChild), rightChild(rightChild)
				{
				    height = 1;
				}
				node* getMinNode()
				{
				    node* iterator = leftChild;
				    while(iterator -> rightChild)
				        iterator = iterator -> rightChild;
				    return iterator;
				}
				node* getMaxNode() {
				    node* iterator = rightChild;
				    while(iterator -> leftChild)
				        iterator = iterator -> leftChild;
				    return iterator;
				}
				int getChildMaxHeight() const
				{
				    return std::max(leftChild ? leftChild -> height : 0, rightChild ? rightChild -> height : 0);
				}

				int getBalance() const
				{
				    return (leftChild ? leftChild -> height : 0) - (rightChild ? rightChild -> height : 0);
				}

				node* rotateLeft()
				{
				    node* tmp = rightChild;
				    rightChild = tmp -> leftChild;
				    tmp -> leftChild = this;

				    this -> height = getChildMaxHeight() + 1;
				    tmp -> height = getChildMaxHeight() + 1;

				    return tmp;
				}

				node* rotateRight()
				{
				    node* tmp = leftChild;
				    leftChild = tmp -> rightChild;
				    tmp -> rightChild = this;

				    this -> height = getChildMaxHeight() + 1;
				    tmp -> height = getChildMaxHeight() + 1;

				    return tmp;
				}
		};
	private:
	    node* root;
	    node* insertRec(PK data, node* parent)
		{
		    if(parent == NULL)
		        return new node(data, NULL, NULL);
		    if(parent -> data < data)
		        parent -> rightChild = insertRec(data, parent -> rightChild);
		    else
		        parent -> leftChild  = insertRec(data, parent -> leftChild);

		    parent -> height = parent -> getChildMaxHeight() + 1;
		    int balance = parent -> getBalance();

		    if(balance > 1 && parent -> leftChild -> data > data)
		        return parent-> rotateRight();

		    if(balance > 1 && parent -> leftChild -> data < data)
		    {
		        parent -> leftChild = parent -> leftChild -> rotateLeft();
		        return parent -> rotateRight();
		    }

		    if(balance < -1 && parent -> rightChild -> data < data)
		        return parent->rotateLeft();

		    if(balance < -1 && parent -> rightChild -> data > data) {
		        parent -> rightChild = parent -> rightChild -> rotateRight();
		        return parent -> rotateLeft();
		    }

		    return parent;
		}
	    node* eraseRec(PK data, node *parent)
		{
		    if(parent == NULL)
		        return parent;
		    if(data < parent -> data)
		        parent -> leftChild  = eraseRec(data, parent -> leftChild);
		    else if(data > parent -> data)
		        parent-> rightChild = eraseRec(data, parent -> rightChild);
		    else
		    {
		        node* leftChild = parent -> leftChild;
		        node* rightChild = parent -> rightChild;
		        if(leftChild == NULL && rightChild == NULL)
		        {
		            node* tmp = parent;
		            parent = NULL;
		            delete tmp;
		        }
		        else if(leftChild == NULL || rightChild == NULL)
		        {
		            node *tmp = parent;
		            parent = leftChild ? leftChild : rightChild;
		            delete tmp;
		        }
		        else
		        {
		            node* successor = parent -> getMaxNode();
		            parent -> data = successor -> data;
		            parent -> rightChild =  eraseRec(successor -> data, rightChild);
		        }
		    }
				    if(parent == NULL)
		        return parent;

		    parent -> height = parent -> getChildMaxHeight() + 1;
		    int balance = parent -> getBalance();
		    int rightBalance = parent -> rightChild ? parent -> rightChild -> getBalance(): 0;
		    int leftBalance  = parent -> leftChild  ? parent -> leftChild -> getBalance() : 0;

		    if(balance > 1 && leftBalance >= 0)
		        return parent -> rotateRight();

		    if(balance > 1 && leftBalance < 0)
		    {
		        parent -> leftChild = parent -> leftChild -> rotateLeft();
		        return parent -> rotateRight();
		    }

		    if(balance < -1 && rightBalance <= 0)
		        return parent -> rotateLeft();

		    if(balance < -1 && rightBalance > 0)
		    {
		        parent -> rightChild = parent -> rightChild -> rotateRight();
		        return parent -> rotateLeft();
		    }

		    return parent;
		}
	    void recursivePrint(node* parent)
		{
		    if(parent == NULL)
		        return;
		    recursivePrint(parent -> leftChild);
		    cout << parent -> data << " ";
		    recursivePrint(parent -> rightChild);
		}

		void rPrintPreOrder(node* parent)
		{
		    if(parent == NULL)
		        return;
		    cout << parent -> data << " ";
		    rPrintPreOrder(parent -> leftChild);
		    rPrintPreOrder(parent -> rightChild);
		}

		void rPrintPostOrder(node* parent)
		{
		    if(parent == NULL)
		        return;
		    rPrintPostOrder(parent -> leftChild);
		    rPrintPostOrder(parent -> rightChild);
		    cout << parent -> data << " ";
		}
	public:
	    AVL()
		{
		    root = NULL;
		}
		PK min()
		{
		    if(root == NULL)
		        throw 6800;
		    node* iterator = root;
		    while(iterator -> leftChild)
		        iterator = iterator -> leftChild;
		    return iterator -> data;
		}
		PK max()
		{
		    if(root == NULL)
		        throw 6800;
		    node* iterator = root;
		    while(iterator -> rightChild)
		        iterator = iterator -> rightChild;
		    return iterator -> data;
		}
	    void insert(PK data)
		{
		    if(root == NULL)
		        root = new node(data, NULL, NULL);
		    else
		        root = insertRec(data, root);
		    return;
		}
		void erase(PK data)
		{
		    root = eraseRec(data, root);
		}
	    PK search(PK data)
		{
		    PK empty;
		    empty.offset = -1;
		    node* iterator = root;
		    while(iterator)
		    {
		        if(iterator -> data == data)
		            return iterator -> data;
		        else if (iterator -> data < data)
		            iterator = iterator -> rightChild;
		        else
		            iterator = iterator -> leftChild;
		    }
		    return empty;
		}
	    void printInOrder()
		{
		    cout << "InOrder:   ";
		    recursivePrint(root);
		    cout << "\n";
		}

		void printPreOrder()
		{
		    cout << "PreOrder:  ";
		    rPrintPreOrder(root);
		    cout << "\n";
		}

		void printPostOrder()
		{
		    cout << "PostOrder: ";
		    rPrintPostOrder(root);
		    cout << "\n";
		}
	    node* getRoot() const
		{
		    return root;
		}
};

AVL primarykey;

void insert(fstream& file, Student student)
{

	PK temp;
	char buffer[110];
	strcpy(buffer, student.id);
	strcat(buffer, "|");
	strcat(buffer, student.name);
	strcat(buffer, "|");
	strcat(buffer, student.address);
	strcat(buffer, "|");
	short length = strlen(buffer);
	short offset = file.tellp();
	file.write((char*)&length, sizeof(length));
	file.write(buffer, length);
	strcpy(temp.id, student.id);
	temp.offset = offset;
	primarykey.insert(temp);

}

void print(ifstream& file, AVL::node* root)
{
	if(root == NULL)
        return;
    print(file, root -> leftChild);
    file.seekg(root -> data.offset, ios::beg);
    //cout << root -> data.id << ' ' << root -> data.offset << ' ' << file.tellg() << '\n';
    short length;
    file.read((char*)&length, sizeof(length));
    //cout << length << ' ';
    char* buffer = new char[length];
    //buffer[length - 1] = '\0';
    file.read(buffer, length);
    cout << buffer << '\n';
    delete buffer;
    print(file, root -> rightChild);
}

void printAll()
{
	ifstream file("data.txt");
	print(file, primarykey.getRoot());
	file.close();
}

void Delete(fstream& file)
{
	PK temp;
	cin >> temp.id;
	temp = primarykey.search(temp);
	if(temp.offset == -1)
		cout << "not found.\n";
	else
	{
		file.seekp(temp.offset + 2);
		file.put('*');
		primarykey.erase(temp);
	}
}

int main()
{
	fstream file("data.txt", ios::out | ios::trunc);
    file.close();

	file.open("data.txt", ios::out | ios::binary | ios::app);
    for(int i = 0; i < 20; i++)
    {
        char id[10] = "";
        id[0] = 'A' + i;
        Student temp;
        strcpy(temp.id, id);
        strcpy(temp.name, "saif");
        strcpy(temp.address, "maadi");
        insert(file, temp);
    }
    file.close();
    printAll();

    file.open("data.txt", ios::out | ios::binary | ios::in);
    for(int i = 0; i < 5; i++)
        Delete(file);
    file.close();
    printAll();
    return 0;
}
