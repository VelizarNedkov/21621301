#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<fstream>
#include<iterator>
#include<algorithm>
using namespace std;

class Student
{
private:
	int mark;
	string fn;
public:
	//Default constructor 
	Student() {
		mark = 0;
		fn = "xxxxxxxx";
	}
	//Explicit constructor
	Student(const int& tmark, const string& tfn) {
		mark = tmark;
		fn = tfn;
	}
	//Get
	int GetMark()const
	{
		return mark;
	}
	string GetFn()const
	{
		return fn;
	}
	//Operator <
	friend bool operator<(const Student& obj1, const Student& obj2)
	{
		if (obj1.mark < obj2.mark)
			return true;
		else
			return false;
	}
	//Opertor ==
	friend bool operator==(const Student& obj1, const Student& obj2)
	{
		if (obj1.fn == obj2.fn && obj1.mark == obj2.mark)

			return true;
		else
			return false;
	}
	//Operator <<
	friend ostream& operator <<(ostream& out, const Student& obj1)
	{
		out << "Fac number: " << obj1.fn << " " << "Mark: " << obj1.mark << endl;
		return out;
	}
	//Operator >>
	friend istream& operator >>(istream& in, Student& obj1)
	{
		in >> obj1.fn >> obj1.mark;
		return in;
	}
};

class BestStudent
{
private:
	virtual Student& ExtractBestStudent(const set<Student>& exreport1, const set<Student>& exreport2) = 0;
};

class Protocol :BestStudent
{
private:
	string pname;
	vector<Student>students;
public:
	//Default constructor
	Protocol() {}
	//Explicit constructor
	Protocol(const string& filename) {
		ifstream filein(filename);
		if (filein.good())
		{
			filein >> this->pname;
			Student temp;
			while (!filein.eof())
			{
				filein >> temp;
				students.push_back(temp);
			}
		}
		else
			throw runtime_error("File is not found!");
	}
	//Get
	string GetPname()const
	{
		return pname;
	}
	//Operator <
	friend bool operator<(const Protocol& obj1, const Protocol& obj2)
	{
		if (obj1.students < obj2.students)
			return true;
		else
			return false;
	}
	//Operator ==
	bool operator==(const Protocol& obj1)
	{
		if (this->pname == obj1.pname && this->students == obj1.students)
			return true;
		else
			return false;
	}
	//Operator <<
	friend ostream& operator <<(ostream& out, const Protocol& obj1)
	{
		out << "Protocol name: " << obj1.pname << endl
			<< "Danni na student: " << endl;
		for (auto itr = obj1.students.begin(); itr != obj1.students.end(); itr++) {
			out << *itr;
		}
		out << endl;
		return out;
	}
	//Operator >>
	friend istream& operator >>(istream& in, Protocol& obj1)
	{
		in >> obj1.pname;
		return in;
	}
	//Virtual functon
	Student& ExtractBestStudent(const set<Student>& exreport1, const set<Student>& exreport2)
	{
		Student bestStudent;
		set<Student> resultreport;
		double highestmark = 2.0;
		for (const Student student1 : exreport1) {
			if (student1.GetMark() > highestmark) {
				highestmark = student1.GetMark();
				bestStudent = student1;
			}
		}
		set_intersection(exreport1.begin(), exreport1.end(), exreport2.begin(),
			exreport2.end(), inserter(resultreport, resultreport.begin()), comp);
		return bestStudent;
	}
	multiset<Student> CreateSet()
	{
		multiset<Student> resultreport(students.begin(), students.end());
		return resultreport;
	}
	//Функция, която връща най добрият студент.Извисва Createset() и извиква BestStudent. Тази функция ще се използва в main(). 
	//upper_bound, lower_bound
	Student HightestMark()
	{
		Student bestStudent;
		ExtractBestStudent();
		return bestStudent;
	}
	//Функция Compare comp(), която се използва от set_intersection();
	static bool comp(const Student& student1, const Student& student2)
	{
		if (student1.GetMark() < student2.GetMark()
			|| (student1.GetMark() == student2.GetMark() && student1.GetFn() < student2.GetFn()))
		{
			return true;
		}
		else
			return false;
	}
};

int main()
{
	Protocol protocol1("data.txt");
	cout << protocol1;
	Protocol protocol2("data1.txt");
	cout << protocol2;
	return 0;
}
