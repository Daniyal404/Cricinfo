#include"Cricinfo.h"

Match matchHandler;
string* teamList = new string[0];
int teamsSize = 0;

void displayWorldRanking() {
	system("cls");
	fstream file("WorldRankings.txt", ios::in);

	if (!(file.is_open())) { cout << "Unable to display, no data found!\n"; return; }

	string line;
	while (!file.eof()) {
		getline(file, line);
		cout << line << endl;
	}
	cout << "Enter any key to continue.." << endl;
	_getch();
}

string* getTeamsList() {
	fstream file;
	file.open("TeamsList.txt", ios::in);
	if (!(file.is_open())) {
		cout << "Error Getting Teams List! File Not Found!" << endl;
	}
	else {
		string str;
		while (file >> str) { teamsSize++; }
		file.close(); file.open("TeamsList.txt", ios::in);

		string* arr = new string[teamsSize];

		for (int i = 0; i < teamsSize; i++) {
			file >> str;
			arr[i] = str;
		}
		return arr;

		file.close();
	}

	string* arr = new string[0];
	return arr;
}

void AdminTeamMenu(Team team) {
	cout << "Welcome " << team.getTeamName() << "!!\n";
	char ch;
	cout << "Select An Option from below:\n";
	cout << "1.Add Player to Team.\n2.Remove Player from Team\n";
	cout << "3.Search Player in team\n4.Update Player\n";
	cout << "5.Display Team Status.\n6.Display Team's matches list.\n";
	cin >> ch;
	switch (ch) {
	case '1':
		team.addPlayer();
		break;
	case '2':
		team.removePlayer();
		break;
	case '3':
		team.searchPlayer();
		break;
	case '4':
		team.updatePlayer();
		break;
	case '5':
		team.displayTeam();
		break;
	case '6':
		team.displayMatches();
		break;
	}

	_getch();
}

void menu() {
	char ch;

	do {
		cout << "Enter a selection to perform an action!" << endl;
		cout << "1.conductMatch()\n2.scheduleMatch()\n3.displayUpcomingMatches()\n";
		cout << "4.displayRecentMatches()\n5. Display World Ranking" << endl;
		cout << "6.Team Login\n";
		cout << "\nEnter 'x' To Exit!" << endl;
		cin >> ch;
		switch (ch) {
		case '1':
			matchHandler.conductMatch(teamList, teamsSize);
			break;
		case '2':
			matchHandler.scheduleMatch(teamList, teamsSize);
			break;
		case '3':
			matchHandler.displayUpcomingMatches();
			break;
		case '4':
			matchHandler.displayRecentMatches();
			break;
		case '5':
			displayWorldRanking();
			break;
		case '6':
			string user, pass;
			cout << "Enter UserNmae: ";
			getline(cin >> ws, user);
			cout << "Enter Password: ";
			getline(cin >> ws, pass);
			Team t1;
			bool login = false;
			for (int i = 0; i < teamsSize; i++) {
				t1.loadTeam(teamList[i]);
				if (user == t1.getUsername() && pass == t1.getPassword()) {
					login = true; break;
				}
			}
			if (login) {
				AdminTeamMenu(t1);
			}
			else {
				cout << "No Such Username & Password Combination Found!\n";
			}
			break;
		}

	} while (ch != 'x' && ch != ' ');

}

int main() {
	teamList = getTeamsList();
	srand(time(0));

	menu();

	delete[] teamList;

	return 0;
}