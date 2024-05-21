#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>//������������� ������
#include <vector>
#include <algorithm>
using namespace std;


struct UserCommits {
	string username;
	int commitCount;

	UserCommits(string name, int count) : username(move(name)), commitCount(count){}
};


bool compareUsers(const UserCommits& a, const UserCommits& b) {
	return a.commitCount > b.commitCount;
}


void otchot() {
	ifstream inputFile("commits.txt");

	if (!inputFile) { // ��������
		cout << "������ ��� �������� �����";
	}
	//{"Andrew":9, "IGOR":8, "Bree":7, "AIvanov":5}
	//� ���������� ������ ��������� ��������� ����� ����(result.txt), ���������� ���������� �� ������ 3 - � ����� �������� ������������� �� ������ � ������ ������ � ������� �������� ����� � ��������.������ ����������� ����� :
	//AIvanov
	//AKalinina
	//CodeKiller777
	unordered_map<string, int> commitCounts;	
	string line;
	//AIvanov 25ec001 2024 - 04 - 24T13:56 : 39.492

	while (getline(inputFile, line)) {

		istringstream iss(line);
		string username, commitHash, commitData;

		
		if (!(iss >> username >> commitHash >> commitData)) {
			cout << "������ ��� ������ ������";
			cout << line;
			continue;
		}
		commitCounts[username]++;
	}
	inputFile.close();

	vector<UserCommits> users;
	//pair.first ����
	//pair.second ��������
	for (const auto& pair : commitCounts) {
		users.emplace_back(pair.first, pair.second);
	}
	//soft ��������� ������ - 3 ��������� ��������� - ������; �����; � �������, ��� �������� ������ ����������
	sort(users.begin(), users.end(), compareUsers); 

	ofstream outputFile("result.txt");
	if (!outputFile) {
		cout << "������ ��� �������� �����";
		return;
	}


	for (int i = 0; i < 3; i++) {
		outputFile << users[i].username << endl;
	}
	outputFile.close();

}


int main() {
	otchot();
}