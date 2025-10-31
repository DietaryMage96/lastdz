#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class character {
public:
	int health;
	character(double h) : health(h) {}
	virtual int attack() = 0;
	virtual void heal(int a) {
		health += a;
		cout << "Healed (+" << a << ")!" << endl << "Current: " << health << endl;
	}
	virtual void info() = 0;
	virtual string get() = 0;
	virtual ~character() {};
};

class warrior : public character{
public:
	int strength;
	warrior(int h, int s) : character(h), strength(s) {}
	int attack() override {
		return strength * 2;
	}
	void info() override {
		cout << "Warrior:" << endl << "Strength: " << strength << ", Health : " << health << endl;
	}
	string get() override {
		return "warrior;" + to_string(health) + ";" + to_string(strength);
	}
};

class mage final : public character{
public:
	int mana;
	mage(int h, int m) : character(h), mana(m) {}
	int attack() override {
		return mana * 1.5;
	}
	void info() override {
		cout << "Mage:" << endl << "Mana: " << mana << ", Health: " << health << endl;
	}
	string get() override {
		return "mage;" + to_string(health) + ";" + to_string(mana);
	}
};

class archer : public character{
public:
	int quickness;
	archer(int h, int q) : character(h), quickness(q) {}
	int attack() override {
		return quickness * 1.8;
	}
	void info() override {
		cout << "Archer:" << endl << "Quickness: " << quickness << ", Health: " << health << endl;
	}
	string get() override {
		return "archer;" + to_string(health) + ";" + to_string(quickness);
	}
};

int main()
{
	vector<character*> team;
	int a;
	cout << "Enter team from the:" << endl << "1 - keyboard" << endl << "2 - file" << endl;
	cin >> a;
	if (a == 1) {
		for (int i = 0; i < 5; i++) {
			cout << "Choose type (1 - Warrior, 2 - Mage, 3 - Archer): ";
			int type;
			cin >> type;

			int smthg, health;
			if (type == 1) {
				cout << "Enter strength: ";
				cin >> smthg;
				cout << "Enter health: ";
				cin >> health;
				team.push_back(new warrior(health,smthg));
			}
			else if (type == 2) {
				cout << "Enter mana: ";
				cin >> smthg;
				cout << "Enter health: ";
				cin >> health;
				team.push_back(new mage(health, smthg));
			}
			else if (type == 3) {
				cout << "Enter agility: ";
				cin >> smthg;
				cout << "Enter health: ";
				cin >> health;
				team.push_back(new archer(health, smthg));
			}
		}
	}
	else if(a == 2) {
		ifstream file("team.txt");
		if (!file.is_open()) {
			cout << "Error" << endl;
		}
		else {
			string line;
			while (getline(file, line)) {
				string type, health, smthg;
				string field;
				int count = 0;

				for (int i = 0; i < line.length(); i++) {
					if (line[i] == ';') {
						if (count == 0) type = field;
						else if (count == 1) health = field;
						field = "";
						count++;
					}
					else {
						field += line[i];
					}
				}
				smthg = field;

				if (type == "warrior")
					team.push_back(new warrior(stoi(health), stoi(smthg)));
				else if (type == "mage")
					team.push_back(new mage(stoi(health), stoi(smthg)));
				else if (type == "archer")
					team.push_back(new archer(stoi(health), stoi(smthg)));
			}
		}
		file.close();
	}
	
	int power = 0;
	for (int i = 0; i < team.size(); i++) {
		power += team[i]->attack();
	}
	cout << "Total team power: " << power << endl;

	ofstream file("team.txt");
	for (int i = 0; i < team.size(); i++) {
		file << team[i]->get() << endl;
	}



	file.close();
	for (int i = 0; i < team.size(); i++)
		delete team[i];
	team.clear();
}
