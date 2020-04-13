#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
using namespace std;

#define N 997
#define bucketSize 2

struct Student
{
    char id[10];
    char name[50];
    char address[50];
    student()
	{
    	strcpy(id, "//");
	}
};

struct PDataArea
{
	Student data[bucketSize];
	int start;
	int used;
	PrimaryDataArea()
	{
		start = -1;
		used = 0;
	}
};

struct OFArea
{
	Student data[bucketSize];
	int next, used;
	OverflowArea()
	{
		next = -1;
		used = 0;
	}
};

PDataArea PD[N];
OFArea OF[N];
int overflowStart = 0;

int multiplicationHash(const char* id)
{
	string conv(id);
	stringstream obj;
	obj << conv;
	int id_int;
	obj >> id_int;
    int ratioInt = id_int * 0.6180339887;
    double ratioDecimal = (double)id_int * 0.6180339887;
    double extraction = ratioDecimal - ratioInt;
    return (int)(N * extraction);
}

void save(int hash, int bucketIndex, Student temp, string fileName)
{
	fstream file(fileName, ios::out | ios::binary | ios::in);
	file.seekp(hash * 110 + bucketIndex * 110, ios::beg);
	/*char buffer[110];
	strcpy(buffer, temp.id);
	strcat(buffer, "|");
	strcat(buffer, temp.name);
	strcat(buffer, "|");
	strcat(buffer, temp.address);
	strcat(buffer, "|");
	file.write(buffer, 110);*/
	string id(temp.id), name(temp.name), Add(temp.address);
	string all = ' ' + id + '|' + name + '|' + Add + '|';
	file << all;
	file.close();
}

void add(const char* id, const char* name, const char* address)
{
	Student temp;
	strcpy(temp.id, id);
	strcpy(temp.name, name);
	strcpy(temp.address, address);
	int hash = multiplicationHash(temp.id);
	if(PD[hash].used < 2)
	{
		PD[hash].data[PD[hash].used] = temp;
		save(hash, PD[hash].used, temp, "primary.txt");
		PD[hash].used++;
	}
	else
	{
		int start = PD[hash].start;
		if(start == -1)
		{
			start = overflowStart;
			overflowStart++;
			OF[start].data[0] = temp;
			PD[hash].start = start;
			save(start, OF[start].used, temp, "overflow.txt");
			OF[start].used++;
		}
		else if(OF[start].used < 2)
		{
			OF[start].data[OF[start].used] = temp;
			save(start, OF[start].used, temp, "overflow.txt");
			OF[start].used++;
		}
		else
		{
			int next;
			while(1)
			{
				next = OF[start].next;
				if(next == -1)
				{
					overflowStart = OF[start].next;
					OF[overflowStart].data[0] = temp;
				}
				else if(OF[next].used < 2)
				{
					OF[next].data[1] = temp;
					break;
				}
				else
					start = next;
			}
		}
	}
}

void print()
{
	Student temp;
	fstream file1("primary.txt", ios::binary | ios::in);
	for (int i = 0; i < N; i++)
		if (PD[i].used != 0)
		{
			if (strcmp(PD[i].data[0].id, "//") != 0)
			{
				file1.seekg(i * 110, ios::beg);
				file1.getline(temp.id, 9, '|');
				file1.getline(temp.name, 49, '|');
				file1.getline(temp.address, 49, '|');
				cout << "ID: " << temp.id << "\tName: " << temp.name << "\tAddress: " << temp.address << '\n';
			}
			if (strcmp(PD[i].data[1].id, "//") != 0)
			{
				file1.seekg(i * 110 + 110, ios::beg);
				file1.getline(temp.id, 9, '|');
				file1.getline(temp.name, 49, '|');
				file1.getline(temp.address, 49, '|');
				cout << "ID: " << temp.id << "\tName: " << temp.name << "\tAddress: " << temp.address << '\n';
			}
		}
	file1.close();
	fstream file2("overflow.txt", ios::binary | ios::in);
	for (int i = 0; i < N; i++)
	{
		if (OF[i].used != 0)
		{
			if (strcmp(OF[i].data[0].id, "//") != 0)
			{
				file2.seekg(i * 110, ios::beg);
				file2.getline(temp.id, 9, '|');
				file2.getline(temp.name, 49, '|');
				file2.getline(temp.address, 49, '|');
				cout << "ID: " << temp.id << "\tName: " << temp.name << "\tAddress: " << temp.address << '\n';
			}
			if (strcmp(OF[i].data[1].id, "//") != 0)
			{
				file2.seekg(i * 110 + 110, ios::beg);
				file2.getline(temp.id, 9, '|');
				file2.getline(temp.name, 49, '|');
				file2.getline(temp.address, 49, '|');
				cout << "ID: " << temp.id << "\tName: " << temp.name << "\tAddress: " << temp.address << '\n';
			}
		}
	}
	file2.close();
}

void Delete(const char* id)
{
	int hash = multiplicationHash(id);
	if(strcmp(PD[hash].data[0].id, id) == 0)
	{
		strcpy(PD[hash].data[0].id, "//");
		PD[hash].used--;
	}
	else if(strcmp(PD[hash].data[1].id, id) == 0)
	{
		strcpy(PD[hash].data[1].id, "//");
		PD[hash].used--;
	}
	else if(PD[hash].start != -1)
	{
		int next = PD[hash].start;
		while(1)
		{
			if(strcmp(OF[next].data[0].id, id) == 0)
			{
				strcpy(OF[next].data[0].id, "//");
				OF[next].used--;
				break;
			}
			else if(strcmp(OF[next].data[1].id, id) == 0)
			{
				strcpy(OF[next].data[1].id, "//");
				OF[next].used--;
				break;
			}
			else if(OF[next].next == -1)
				break;
			else
				next = OF[next].next;
		}
	}
}

int main()
{
	fstream f("Primary.txt", ios::out);
	f.close();
	fstream f2("overflow.txt", ios::out);
	f2.close();
	add("23", "Yusuf", "giza");
	add("23", "Yusuf", "giza");
	add("23", "Yusuf", "giza");
	add("23", "Yusuf", "giza");
	/*add("324", "mido", "giza");
	add("2341", "joe", "giza");
	add("234", "ahmed", "giza");
	add("1", "ali", "giza");
	add("111", "Nermine TEMPLATE", "giza");
	add("3423", "farah", "giza");
	add("23444", "shaymaa", "giza");
	add("499", "menna", "giza");
	add("678", "arwa", "giza");
	add("6977", "assem", "giza");
	add("654", "khaled", "giza");
	add("8", "doaa", "giza");
	add("331", "rodaina", "giza");
	add("5675", "laura", "giza");
	add("456", "lara", "giza");
	add("64", "John", "giza");
	add("4", "Ali", "giza");
	add("870", "Haha", "giza");
	add("453", "Sondos", "giza");*/
	cout << endl;
	print();
	Delete("23");
	/*Delete("5675");
	Delete("456");
	Delete("23444");
	Delete("870");*/
	cout << endl;
	print();
    return 0;
}
