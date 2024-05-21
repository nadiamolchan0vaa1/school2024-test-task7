#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>//Ассоциативный массив
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

	if (!inputFile) { // проверка
		cout << "Ошибка при открытии файла";
	}
	//{"Andrew":9, "IGOR":8, "Bree":7, "AIvanov":5}
	//В результате работы процедура формирует новый файл(result.txt), содержащий информацию об именах 3 - х самых активных пользователей по одному в каждой строке в порядке убывания места в рейтинге.Пример содержимого файла :
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
			cout << "Ошибка при чтении строки";
			cout << line;
			continue;
		}
		commitCounts[username]++;
	}
	inputFile.close();

	vector<UserCommits> users;
	//pair.first ключ
	//pair.second значение
	for (const auto& pair : commitCounts) {
		users.emplace_back(pair.first, pair.second);
	}
	//soft сортирует вектор - 3 аргумента принимает - начало; конец; и функцию, что помогает делать сортировку
	sort(users.begin(), users.end(), compareUsers); 

	ofstream outputFile("result.txt");
	if (!outputFile) {
		cout << "Ошибка при создании файла";
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