#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sstream>
using namespace std;

class students
{

private:

	struct hashed
	{
		char pk[9];
		int offset;
		hashed()
		{
			offset = 0;
			strcpy(pk, "");
		}
	};

	hashed arr[997];
	void initializearray()
	{
		for (int i = 0; i < 977; i++)
		{
			arr[i].offset = 0;
			strcpy(arr[i].pk,"");
		}
	}
	struct student
	{
		char ID[9];
		char Name[49];
		char Address[49];
	};
public:
	students()
	{
		initializearray();
	}

	int hashingfunction(string ID)
	{
		float index, m, a;
		float key = atoi(ID.c_str());
		a = 0.6180339887;
		m = 997;
		index = (key*a);
		return floor(m *fmod(index, 1));
	}
	void addstudent()
	{
		student ob;
		cout << "Enter student ID:";
		cin.getline(ob.ID, 9);
		cout << "Enter Name:";
		cin.getline(ob.Name, 49);
		cout << "Enter Address:";
		cin.getline(ob.Address, 49);

		fstream out;
		out.open("student.txt", ios::out | ios::app | ios::binary);
		char buff[110];
		strcpy(buff, ob.ID);
		strcat(buff, "|");
		strcat(buff, ob.Name);
		strcat(buff, "|");
		strcat(buff, ob.Address);
		strcat(buff, "|");

		short size = strlen(buff);
		out.seekp(0, ios::end);
		int offset = out.tellp();
        cout << offset << '\n';
		string key = ob.ID;
		int index = hashingfunction(key);

		while (strcmp(arr[index].pk ,"") != 0 )
		{
			index += 1;
		}

		strcpy(arr[index].pk, ob.ID);
		arr[index].offset = offset;
		out.write((char*)&size, sizeof(size));
		out.write(buff, size);
		out.close();
	}

	int searchstudent(char key[],int x = 0)
	{
		int index = hashingfunction(key);
		while (index<997)
		{
			if (strcmp(arr[index].pk, key) == 0)
			{
				if (x != 0) {
					strcpy(arr[index].pk,"#");
				}
				return arr[index].offset;
			}

			else if(strcmp(arr[index].pk,"")==0 || arr[index].pk[0]=='#')
			{
				return -1;
			}
			else
			{
				index++;
			}
		}
		return -1;
	}
	void printstudent(char key[])
	{
		student b;
		ifstream in;
		in.open("student.txt", ios::in);
		cout << key << '\n';
		int x = searchstudent(key);
		if (x == -1)
		{
			cout << "student is not found" << endl;
		}
		else
		{
			in.seekg(x, ios::beg);
			short size = 0;
			in.read((char*)&size, 2);
			char *buffer = new char[size];
			in.read(buffer, size);
			istringstream stream(buffer);
			stream.getline(b.ID, 10, '|');
			stream.getline(b.Name, 50, '|');
			stream.getline(b.Address, 50, '|');
			cout << "student id:" << b.ID << " " << "student name:" << b.Name << " " << "student address:" << b.Address << endl;

		}
	}

	void deletestudent(char key[])
	{
		int offset = searchstudent(key, 1);
		if (offset == -1)
		{
			cout << "student is not found" << endl;
		}
		else
		{
		    short length;
			ofstream out;
			out.open("student.txt", ios::out | ios::binary | ios::app);
			cout << offset << '\n';
			out.seekp(offset + 2, ios::beg);
			cout << out.tellp();
			out<<'*';
		}
	}
	void loadstudent()
	{
		int i = 0;
		ifstream in;
		in.open("primary.txt", ios::in);
		if (!in.fail())
		{
			while (1) {
				hashed t;
				in.read((char*)&t, sizeof(t));
				if (in.eof())
					break;
				strcpy(arr[i].pk, t.pk);
				arr[i].offset = t.offset;
				i++;

			}
		}
		else
		{
			cout << "file failure" << endl;
		}
		in.close();
	}
	void savestudent()
	{
		ofstream out;
		out.open("primary.txt", ios::out | ios::trunc);
		for (int i = 0; i<977; i++)
		{
			hashed temp = arr[i];
			out.write((char*)&temp, sizeof(temp));
		}
		out.close();
	}
};



int main()
{

	students ob;
	//ob.loadstudent();
	/*ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();*/
	ob.addstudent();
	ob.addstudent();
	ob.addstudent();
	char id1[9];
	cout << "Enter ID you want to delete:";
	cin >> id1;
	ob.deletestudent(id1);
	cout << "Enter ID you want to delete:";
	cin >> id1;
	ob.deletestudent(id1);
	cout << "Please Enter ID you want to search:";
	cin >> id1;
	ob.printstudent(id1);
	cout << "Please Enter ID you want to search:";
	cin >> id1;
	ob.printstudent(id1);
	//ob.savestudent();


	system("pause");
	return 0;

}

