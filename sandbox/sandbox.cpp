
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Student {
private:
	string fullName;
	int number;
	map<string, double> subjectGrades;
public:

	Student(string name_, int number_) {
		this->fullName = name_;
		this->number = number_;
	}

	void setSubjectGrade(string subject,double grade) {
		this->subjectGrades[subject] = grade;
	};

	void print() {
		cout << fullName << " with number in class " << number << " and grades: " << endl;
		map<string, double>::iterator it = subjectGrades.begin();
		
		for (auto m : subjectGrades) {

			cout << m.first << " " << m.second << endl;

		}
	}

};

int main()
{
	vector<Student> students;
	string name;

	getline(cin >> ws, name);

	while (name != "end") {
		int number;
		cin >> number;

		Student current = Student(name, number);

		string subject;
		double grade;
		cin >> subject;

		while (subject != ".") {
			cin >> grade;

			current.setSubjectGrade(subject, grade);

			cin >> subject;

		}
		students.push_back(current);

		getline(cin >> ws, name);
	}

	for (size_t i = 0;i < students.size();i++) {

		students[i].print();

	}

	return 0;
}
