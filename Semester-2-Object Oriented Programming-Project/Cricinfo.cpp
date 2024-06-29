#include "Cricinfo.h"
double stringToDouble(string str) {
	int i = 0; double d = 0; int dot = -1, div = 1;
	while (str[i] != '\0') {
		char ch = str[i];
		if (dot != -1) { div *= 10; }
		if (ch >= '0' && ch <= '9') {
			d = (d * 10) + (ch - '0');
		}
		else if (ch == '.' && dot == -1) {
			dot = i;
		}
		else {
			return -1;
		}
		i++;
	}
	if (str != "") { return d / div; }
	else { return -1; }

}

int stringToInt(string str) {
	int i = 0; int f = 0;
	while (str[i] != '\0') {
		char ch = str[i];
		if (ch >= '0' && ch <= '9') {
			f = (f * 10) + (ch - '0');
		}
		else { return -1; }
		i++;
	}
	if (str != "") { return f; }
	else { return -1; }
}

Player getPlayerData(Player temp = Player()) {
	string str; double tempFloat; int tempInt;
	if (cin.fail()) { cin.ignore(512, '\n'); }
	cout << "Enter Player Name: "; getline(cin, str);
	if (str != "") { temp.Name = str; }
	cout << "Enter Shirt No: "; getline(cin, str);
	if (str != "") { temp.ShirtNo = str; }
	cout << "Enter Average: "; getline(cin, str);
	tempFloat = stringToDouble(str);
	if (tempFloat != -1) { temp.Average = tempFloat; }
	cout << "Enter T20 Rank: "; getline(cin, str);
	tempInt = stringToInt(str);
	if (tempInt != -1) { temp.Rank.T20 = tempInt; }
	cout << "Enter ODI Rank: "; getline(cin, str);
	tempInt = stringToInt(str);
	if (tempInt != -1) { temp.Rank.ODI = tempInt; }
	cout << "Enter Matches played: "; getline(cin, str);
	tempInt = stringToInt(str);
	if (tempInt != -1) { temp.Matches_played = tempInt; }
	cout << "Enter Total Runs: "; getline(cin, str);
	tempInt = stringToInt(str);
	if (tempInt != -1) { temp.Total_runs = tempInt; }
	cout << "Enter Wickets: "; getline(cin, str);
	tempInt = stringToInt(str);
	if (tempInt != -1) { temp.Total_wickets = tempInt; }

	return temp;
}

Match* GetMatchesList(int& count) {
	count = 0;
	Match* MatchList = new Match[0];
	fstream matchesFile;
	matchesFile.open("Matches.txt", ios::in);
	if (!matchesFile.is_open())
	{
		cout << "Error Displaying Matches! No Record Found.\n";
	}
	else {

		string t1NameF, t2NameF, date, venue, type, torName,
			com1, com2, ump1, ump2, ump3, status, line;
		int i = 0;
		while (getline(matchesFile, line)) { count++; };

		delete[] MatchList;
		MatchList = new Match[count];

		matchesFile.close();
		matchesFile.open("Matches.txt", ios::in);

		while (getline(matchesFile >> ws, t1NameF, '|')) {
			getline(matchesFile >> ws, t2NameF, '|'); getline(matchesFile >> ws, date, '|');
			getline(matchesFile >> ws, venue, '|'); getline(matchesFile >> ws, type, '|');
			getline(matchesFile >> ws, torName, '|'); getline(matchesFile >> ws, com1, '|');
			getline(matchesFile >> ws, com2, '|'); getline(matchesFile >> ws, ump1, '|');
			getline(matchesFile >> ws, ump2, '|'); getline(matchesFile >> ws, ump3, '|');
			getline(matchesFile >> ws, status);

			MatchList[i].Team1.loadTeam(t1NameF);
			MatchList[i].Team2.loadTeam(t2NameF);
			MatchList[i].Date = date;
			MatchList[i].Venue = venue;
			MatchList[i].MatchType = type[0];
			MatchList[i].Tournament_Name = torName;
			MatchList[i].Commentators[0] = com1;
			MatchList[i].Commentators[1] = com2;
			MatchList[i].Umpires[0] = ump1;
			MatchList[i].Umpires[1] = ump2;
			MatchList[i].Umpires[2] = ump3;
			MatchList[i].Match_status = status;

			i++;
		}
		return MatchList;
	}
	matchesFile.close();
	return MatchList;
}

void displayMatch(Match* list, int size, string str1, string str2 = "") {

	for (int i = 0; i < size; i++) {
		cout << i + 1 << ":-\n";
		if (list[i].Match_status == str1 || list[i].Match_status == str2) {
			cout << list[i].Team1.getTeamName() << " vs " << list[i].Team2.getTeamName() << endl;
			cout << "Date: " << list[i].Date << endl;
			cout << "Venue: " << list[i].Venue << endl;
			cout << "Match Type: ";
			if (list[i].MatchType == 'o') { cout << "ODI\n"; }
			else if (list[i].Date == "f") { cout << "First-Class\n"; }
			else { cout << "T20\n"; }
			cout << "Tournament Name: " << list[i].Tournament_Name << endl;
			cout << "Commentators: " << list[i].Commentators[0] << ", " << list[i].Commentators[1] << endl;
			cout << "Umpires: " << list[i].Umpires[0] << ", " << list[i].Umpires[1] << ", " << list[i].Umpires[2] << endl << endl;
		}
	}

}

//=================================| Player Class |=================================
Player::Player() {
	Name = "";
	ShirtNo = "";
	Average = 0;
	Rank.T20 = 0;
	Rank.ODI = 0;
	Total_runs = 0;
	Matches_played = 0;
	Total_wickets = 0;
}
void Player::addPlayer(Player plrs[], int& size, Player newPlayer) {
	Player* tempPlayers = new Player[size + 1];
	for (int i = 0; i < size; i++) {
		tempPlayers[i] = plrs[i];
	}
	tempPlayers[size] = newPlayer; size++;
	for (int i = 0; i < size; i++) {
		plrs[i] = tempPlayers[i];
	}
	delete[] tempPlayers;
}
bool Player::removePlayer(Player* plrs, int& size, string shrtNo) {

	int FoundAt = searchPlayer(plrs, size, shrtNo);

	if (FoundAt != -1) {
		for (int i = FoundAt; i < size - 1; i++) {
			plrs[i] = plrs[i + 1];
		}
		size--;
		return true;
	}
	return false;

}
int Player::searchPlayer(Player* plrs, int& size, string shrtNo) {
	int foundAt = -1;
	for (int i = 0; i < size; i++) {
		if (plrs[i].ShirtNo == shrtNo) {
			foundAt = i;
			break;
		}
	}
	return foundAt;
}
void Player::updatePlayer(string Name, string ShirtNo, double Average, int T20, int ODI,
	int Total_runs, int Matches_played, int Total_wickets) {
	this->Name = Name;
	this->ShirtNo = ShirtNo;
	this->Average = Average;
	this->Rank.T20 = T20;
	this->Rank.ODI = ODI;
	this->Total_runs = Total_runs;
	this->Matches_played = Matches_played;
	this->Total_wickets = Total_wickets;
}
void Player::displayStatus() {
	cout << "Name: " << Name << "( " << ShirtNo << " )\n";
	cout << "Average Score: " << Average << endl;
	cout << "ICC Ranking" << endl;
	cout << "T20: " << Rank.T20 << "\tODI: " << Rank.ODI << endl;
	cout << "Match Details (" << Matches_played << "-matches Played):\n";
	cout << "--->Total Runs: " << Total_runs << "\n--->Total Wickets: " << Total_wickets << endl << endl;
}

void Player::autoUpdAverage() {
	if (Matches_played != 0) {
		Average = Total_runs / Matches_played;
	}
	else {
		Average = 0;
	}
}

//=================================| Team Class |=================================
Team::Team() { totalPlayers = 0; }
void Team::addPlayer() {
	if (totalPlayers < 11) {
		//Get new Player details
		cout << "Adding a new Player into Team - " << Name << endl;
		Player temp = getPlayerData();
		players[0].addPlayer(players, totalPlayers, temp);

		//Now Save in the file VVVV
		//Need to call .teamSave(string str) function
	}
	else {
		cout << "Already 11 Players in Team!" << endl;
	}
}
void Team::removePlayer() {
	//Not 0 Check
	if (totalPlayers > 0) {
		string shirtNo;
		cout << "Removing a Player from Team - " << Name << endl;
		cout << "Enter Shirt No: "; getline(cin, shirtNo);
		int index = players[0].searchPlayer(players, totalPlayers, shirtNo);
		if (index != -1) {
			string plrName = players[index].Name;
			players[0].removePlayer(players, totalPlayers, shirtNo);
			cout << "Player:- " << plrName << " removed!" << endl;
		}
		else { cout << "No Such Player Found!" << endl; }
		//Now Save in the file VVVV
		//Need to call .teamSave(string str) function
	}
	else { cout << "Can not remove anymore Players!" << endl; }
}
void Team::searchPlayer() {
	//Simple Check
	string shirtNo;
	cout << "Search a Player from Team - " << Name << endl;
	cout << "Enter Shirt No: "; getline(cin >> ws, shirtNo);
	int index = players[0].searchPlayer(players, totalPlayers, shirtNo);
	if (index == -1) {
		cout << "No Such Player Found!" << endl;
	}
	else {
		cout << "Player FOUND" << endl << endl;
		players[index].displayStatus();
		cout << endl << endl;
	}
}
void Team::updatePlayer() {
	string shirtNo;
	cout << "Enter Player's Current Shirt Number to Update Player Data: ";
	cin >> shirtNo;
	int index = players[0].searchPlayer(players, totalPlayers, shirtNo);
	if (index != -1) {
		cout << "Enter Updated Data!" << endl;
		Player tempPlr = getPlayerData(players[index]);
		players[index] = tempPlr;
	}
	else { cout << "UpdatePlayer >> No Such Player Found!\n"; }
}
void Team::displayMatches() {
	//Displays ALL Matches for this Team
	fstream matchesFile;
	matchesFile.open("Matches.txt", ios::in);
	if (!matchesFile.is_open())
	{
		cout << "Error Displaying Matches! No Record Found.\n";
	}
	else {
		string t1NameF, t2NameF, date, venue, type, torName, com1, com2, ump1, ump2, ump3, upcom;
		cout << "Match Details!" << endl;
		while (getline(matchesFile >> ws, t1NameF, '|')) {
			getline(matchesFile >> ws, t2NameF, '|'); getline(matchesFile >> ws, date, '|');
			getline(matchesFile >> ws, venue, '|'); getline(matchesFile >> ws, type, '|');
			getline(matchesFile >> ws, torName, '|'); getline(matchesFile >> ws, com1, '|');
			getline(matchesFile >> ws, com2, '|'); getline(matchesFile >> ws, ump1, '|');
			getline(matchesFile >> ws, ump2, '|'); getline(matchesFile >> ws, ump3, '|');
			getline(matchesFile >> ws, upcom, '|');
			string t1Name, t2Name;
			fstream file1, file2;
			file1.open(t1NameF, ios::in);
			file2.open(t2NameF, ios::in);

			file1 >> t1Name;
			file1.close();
			file2 >> t2Name;
			file2.close();

			if (t1Name == Name || t2Name == Name) {
				if (upcom == "upcoming " || upcom == "recent ") {
					cout << t1Name << " vs " << t2Name << endl;
					cout << "Date: " << date << endl;
					cout << "Venue: " << venue << endl;
					cout << "Match Type: ";
					if (type == "0" || type == "o") { cout << "ODI\n"; }
					else if (type == "F" || type == "f") { cout << "First-Class\n"; }
					else { cout << "T20\n"; }
					cout << "Tournament Name: " << torName << endl;
					cout << "Commentators: " << com1 << ", " << com2 << endl;
					cout << "Umpires: " << ump1 << ", " << ump2 << ", " << ump3 << endl << endl;
				}
			}

		}
	}
	matchesFile.close();
}
void Team::updateCaptain(string cap) {
	Team_Captain = cap;
}
void Team::updateCoach(string coach) {
	Team_Coach = coach;
}
void Team::displayTeam() {
	cout << "Team: " << Name << endl;
	cout << "Total Win/Loss: " << TotalWins << "/" << TotalLosts << endl;
	cout << "Team Captain, Coach: " << Team_Captain << ", " << Team_Coach << endl;
	cout << "All Players(" << totalPlayers << "):" << endl;
	for (int i = 0; i < totalPlayers; i++) {
		players[i].displayStatus();
	}
}
bool Team::loadTeam(string file) {
	fstream TeamFile;
	TeamFile.open(file, ios::in);
	this->file = file;
	bool loaded = false;
	if (TeamFile.is_open()) {
		loaded = true;
		TeamFile >> Name;
		TeamFile >> rank.T20;
		TeamFile >> rank.ODI;
		TeamFile >> TotalWins;
		TeamFile >> TotalLosts;
		TeamFile >> Team_Captain;
		TeamFile >> Team_Coach;
		TeamFile >> Admin_Username;
		TeamFile >> Admin_Password;
		TeamFile >> totalPlayers;
		for (int i = 0; i < totalPlayers; i++) {
			string name, shirt, avg, t20, odi, runs, matches, wickets;
			getline(TeamFile >> ws, name, '|');
			getline(TeamFile >> ws, shirt, '|');
			getline(TeamFile >> ws, avg, '|');
			getline(TeamFile >> ws, t20, '|');
			getline(TeamFile >> ws, odi, '|');
			getline(TeamFile >> ws, matches, '|');
			getline(TeamFile >> ws, runs, '|');
			getline(TeamFile >> ws, wickets, '|');
			players[i].Name = name;
			players[i].ShirtNo = shirt;
			players[i].Average = stof(avg);
			players[i].Rank.T20 = stoi(t20);
			players[i].Rank.ODI = stoi(odi);
			players[i].Matches_played = stoi(matches);
			players[i].Total_runs = stoi(runs);
			players[i].Total_wickets = stoi(wickets);
		}
		TeamFile.close();
	}
	else { cout << "Unable to Load Team\n"; }
	return loaded;
}
void Team::teamSave() {
	fstream TeamFile;
	TeamFile.open(file, ios::out);
	if (!TeamFile.is_open()) {
		cout << "Unable to Save Team(" << file << ")" << endl;
		return;
	}
	//cout << "Save File: " << file << endl; _getch();

	TeamFile << Name << endl;
	TeamFile << rank.T20 << endl;
	TeamFile << rank.ODI << endl;
	TeamFile << TotalWins << endl;
	TeamFile << TotalLosts << endl;
	TeamFile << Team_Captain << endl;
	TeamFile << Team_Coach << endl;
	TeamFile << Admin_Username << endl;
	TeamFile << Admin_Password << endl;
	TeamFile << totalPlayers << endl;
	for (int i = 0; i < totalPlayers; i++) {
		Player p = players[i];
		TeamFile << p.Name << "| " << p.ShirtNo << "| " << p.Average << " | " <<
			p.Rank.T20 << " | " << p.Rank.ODI << " | " << p.Matches_played << " | " <<
			p.Total_runs << " | " << p.Total_wickets << " |" << endl;
	}

	TeamFile.close();
}

//=================================| Match Class |=================================

void Match::play_match(Match& M) {
	Team TeamA = M.Team1;
	Team TeamB = M.Team2;

	int teamATotalScore = 0, teamBTotalScore = 0;
	int teamAWickets = 0, teamBWickets = 0;
	int decider;


	if (TeamA.totalPlayers < 11) { cout << "Not Enough Players in Team A!\n"; return; }
	if (TeamB.totalPlayers < 11) { cout << "Not Enough Players in Team B!\n"; return; }
	srand(time(0));
	int totalBalls = 0, currentBall = 0;
	switch (M.MatchType) {
	case 'f':
		totalBalls = 5000;
		break;
	case 'o':
		totalBalls = 300;
		break;
	case 't':
		totalBalls = 120;
		break;
	}

	for (int i = 0; i < 11; i++) {
		while (currentBall <= totalBalls) {
			decider = rand() % 10;
			if (decider < 2) {			//0 - 1
				TeamA.players[i].Total_runs++;
				teamATotalScore++;
			}
			else if (decider < 4) {		//2 - 3
				TeamA.players[i].Total_runs += 2;
				teamATotalScore += 2;
			}
			else if (decider < 5) {		//4
				TeamA.players[i].Total_runs += 3;
				teamATotalScore += 3;
			}
			else if (decider < 6) {		//5
				TeamA.players[i].Total_runs += 4;
				teamATotalScore += 4;
			}
			else if (decider < 7) {		//6
				TeamA.players[i].Total_runs += 6;
				teamATotalScore += 6;
			}
			else if (decider < 8) {		//7
				teamAWickets++; break;
			}
			currentBall++;
		}
	}
	for (int i = 0; i < teamAWickets; i++) {
		decider = rand() % 11;
		TeamA.players[decider].Total_wickets++;
	}

	currentBall = 0;

	for (int i = 0; i < 11; i++) {
		while (currentBall <= totalBalls &&
			teamATotalScore > teamBTotalScore) {
			decider = rand() % 10;
			if (decider < 2) {			//0 - 1
				TeamB.players[i].Total_runs++;
				teamBTotalScore++;
			}
			else if (decider < 4) {		//2 - 3
				TeamB.players[i].Total_runs += 2;
				teamBTotalScore += 2;
			}
			else if (decider < 5) {		//4
				TeamB.players[i].Total_runs += 3;
				teamBTotalScore += 3;
			}
			else if (decider < 6) {		//5
				TeamB.players[i].Total_runs += 4;
				teamBTotalScore += 4;
			}
			else if (decider < 7) {		//6
				TeamB.players[i].Total_runs += 6;
				teamBTotalScore += 6;
			}
			else if (decider < 8) {		//7
				teamBWickets++; break;
			}
			currentBall++;
		}
	}
	for (int i = 0; i < teamBWickets; i++) {
		decider = rand() % 11;
		TeamB.players[decider].Total_wickets++;
	}

	if (teamATotalScore == teamBTotalScore) {
		cout << "Match Draw\n";
		cout << "Team:= " << TeamA.Name << endl;
		cout << "Scored: " << teamATotalScore << endl;
		cout << "Team:= " << TeamB.Name << endl;
		cout << "Scored: " << teamBTotalScore << endl;
	}
	else if (teamATotalScore > teamBTotalScore) {
		cout << "Team (" << TeamA.Name << ") Won!\n";
		cout << "Team:= " << TeamA.Name << endl;
		cout << "Scored: " << teamATotalScore << endl;
		cout << "Team:= " << TeamB.Name << endl;
		cout << "Scored: " << teamBTotalScore << endl;
		M.Team1.TotalWins++;
		M.Team2.TotalLosts++;
	}
	else {
		cout << "Team (" << TeamB.Name << ") Won!\n";
		cout << "Team:= " << TeamA.Name << endl;
		cout << "Scored: " << teamATotalScore << endl;
		cout << "Team:= " << TeamB.Name << endl;
		cout << "Scored: " << teamBTotalScore << endl;
		M.Team2.TotalWins++;
		M.Team1.TotalLosts++;
	}

	for (int i = 0; i < 11; i++) {
		TeamA.players[i].Matches_played++;
		TeamB.players[i].Matches_played++;
	}

	M.Team1 = TeamA;
	M.Team2 = TeamB;

}

void Match::conductMatch(string* teamsList, int teamsSize) {
	int matchesListSize = 0, num;
	Match* Match_List = GetMatchesList(matchesListSize);
	char ch;
	cout << "Enter 1 to Conduct a Match" << endl;
	cout << "Enter 2 to Schedule a Match" << endl;
	cin >> ch;
	switch (ch) {
	case '1':
		do {
			system("cls");
			displayMatch(Match_List, matchesListSize, "upcoming");
			cout << "Enter 1-" << matchesListSize << ": ";
			cin >> num;
		} while (num <= 0 || num > matchesListSize);
		num--;

		play_match(Match_List[num]);
		Match_List[num].Team1.teamSave();
		Match_List[num].Team2.teamSave();
		updatePlayerRanking();
		updateTeamRanking();
		updateWorldRecords();

		{
			fstream file("Matches.txt", ios::out);
			Match_List[num].Match_status = "recent";
			for (int i = 0; i < matchesListSize; i++) {
				file << Match_List[i].Team1.file << " | " << Match_List[i].Team2.file << " | " <<
					Match_List[i].Date << " | " << Match_List[i].Venue << " | " << Match_List[i].MatchType <<
					" | " << Match_List[i].Tournament_Name << " | " << Match_List[i].Commentators[0] <<
					" | " << Match_List[i].Commentators[1] << " | " << Match_List[i].Umpires[0] << " | " <<
					Match_List[i].Umpires[1] << " | " << Match_List[i].Umpires[2] << " | "
					<< Match_List[i].Match_status << endl;
			}
		}


		break;
	case '2':
		scheduleMatch(teamsList, teamsSize);
		break;
	default:
		cout << "Not a valid Choice\n";
	}
	delete[] Match_List;
}

void Match::scheduleMatch(string* teamsList, int teamsSize) {
	int select, select2, totalTeams = 0;
	string* strArr = new string[teamsSize];
	string t1Txt = "", t2Txt = "";
	//Conduct Match --> Play_Match()
	for (int i = 0; i < teamsSize; i++) {
		fstream fileGetName;
		fileGetName.open(teamsList[i], ios::in);
		if (fileGetName.is_open()) {
			fileGetName >> strArr[i];
			totalTeams++;
		}
		else { cout << "Error Getting Teams List!\n"; }
	}
	if (!(totalTeams >= 2)) { cout << "Not Enough Teams Exists!(" << totalTeams << ")\n"; }
	cout << "List of Teams:\n";
	for (int i = 0; i < totalTeams; i++) {
		cout << i + 1 << ": " << strArr[i] << endl;
	}

	cout << "\nEnter 1st Team no. to select: ";
	do {
		cin >> select; select--;
		if (select <= teamsSize && select >= 0) { t1Txt = teamsList[select]; }
		else { cout << "Invalid Team Selection\n"; }
	} while (t1Txt == "");

	cout << "\nEnter 2nd Team no. to select: ";
	do {
		cin >> select2; select2--;
		if (select2 <= teamsSize && select2 >= 0 && select2 != select) { t2Txt = teamsList[select2]; }
		else { cout << "Invalid Team Selection\n"; }
	} while (t2Txt == "");

	int day, month, year; char ch1, ch2; bool valid_date;
	do {
		valid_date = true;
		cout << "Enter date in format (dd-mm-yyy): ";
		cin >> day >> ch1 >> month >> ch2 >> year;
		if (day >= 31 || month >= 12) {
			valid_date = false;
		}
	} while ((ch1 != ch2 && ch1 != '-') || !valid_date);

	string ven1, m_t, torName, c1, c2, u1, u2, u3, ms;
	cout << "Enter Venue: ";
	getline(cin >> ws, ven1);

	cout << "Enter Match Type";
	do {
		cout << "\nFirst-Class = f, Oneday = o, T20 = t: ";
		getline(cin, m_t);
	} while (!(m_t == "o" || m_t == "f" || m_t == "t"));

	cout << "Enter Tournament Name: "; getline(cin, torName);
	cout << "Enter Commentator 1: "; getline(cin, c1);
	cout << "Enter Commentator 2: "; getline(cin, c2);
	cout << "Enter Umpire 1: "; getline(cin, u1);
	cout << "Enter Umpire 2: "; getline(cin, u2);
	cout << "Enter Umpire 3: "; getline(cin, u3);

	ms = "upcoming";

	fstream fileSave;
	fileSave.open("Matches.txt", ios::app);

	fileSave << t1Txt << " | " << t2Txt << " | " << day << ch1 << month << ch2 << year <<
		" | " << ven1 << " | " << m_t << " | " << torName << " | " <<
		c1 << " | " << c2 << " | " << u1 << " | " << u2 << " | " <<
		u3 << " | " << ms << "\n";

	fileSave.close();
}

void Match::updateWorldRecords() {
	string htr_t20, htr_odi, hpr_t20, hpr_odi, hp_runs, hp_avg, hp_wick;
	double Higest_Avg = 0;
	int Higest_Runs = 0, Higest_Wickets = 0;
	int size = 0;

	string* teamList = new string[0];

	fstream file;
	file.open("TeamsList.txt", ios::in);
	if (!(file.is_open())) {
		cout << "Error Getting Teams List! File Not Found!" << endl;
		return;
	}
	else {
		string str;
		while (file >> str) { size++; }
		file.close();
		file.open("TeamsList.txt", ios::in);

		teamList = new string[size];

		for (int i = 0; i < size; i++) {
			file >> str;
			teamList[i] = str;
		}

		file.close();
	}
	Team* TeamObj = new Team[size];
	for (int i = 0; i < size; i++) {
		TeamObj[i].loadTeam(teamList[i]);
		if (TeamObj[i].rank.T20 == 1) { htr_t20 = TeamObj[i].Name; }
		if (TeamObj[i].rank.ODI == 1) { htr_odi = TeamObj[i].Name; }

		for (int j = 0; j < TeamObj[i].totalPlayers; j++) {
			if (TeamObj[i].players[j].Rank.T20 == 1) { hpr_t20 = TeamObj[i].players[j].Name; }
			if (TeamObj[i].players[j].Rank.ODI == 1) { hpr_odi = TeamObj[i].players[j].Name; }
			if (TeamObj[i].players[j].Average > Higest_Avg) {
				hpr_t20 = TeamObj[i].players[j].Name;
				Higest_Avg = TeamObj[i].players[j].Average;
			}
			if (TeamObj[i].players[j].Total_runs > Higest_Runs) {
				hp_runs = TeamObj[i].players[j].Name;
				Higest_Runs = TeamObj[i].players[j].Total_runs;
			}
			if (TeamObj[i].players[j].Total_wickets > Higest_Wickets) {
				hp_wick = TeamObj[i].players[j].Name;
				Higest_Wickets = TeamObj[i].players[j].Total_wickets;
			}
		}
	}
	fstream file2;
	file2.open("WorldRankings.txt", ios::out);
	if (!(file2.is_open())) { cout << "An Error Occured.\n"; return; }

	file2 << "Team with Higest Ranking(T20): " << htr_t20 << endl;
	file2 << "Team with Higest Ranking(ODI): " << htr_odi << endl;
	file2 << "Player with Higest Ranking(T20): " << hpr_t20 << endl;
	file2 << "Player with Higest Ranking(ODI): " << hpr_odi << endl;
	file2 << "Player with Higest Avg: " << hp_avg << "( " << Higest_Avg << "-average )" << endl;
	file2 << "Player with Higest runs: " << hp_runs << "( " << Higest_Runs << "-runs )" << endl;
	file2 << "Player with Higest wickets: " << hp_wick << "( " << Higest_Wickets << "-wickets )" << endl;


	file2.close();
	delete[] TeamObj;
	delete[] teamList;

}
void Match::updateTeamRanking() {
	string* teamList = new string[0];
	int size = 0;
	fstream file;
	file.open("TeamsList.txt", ios::in);
	if (!(file.is_open())) {
		cout << "Error Getting Teams List! File Not Found!" << endl;
		return;
	}
	else {
		string str;
		while (file >> str) { size++; }
		file.close();
		file.open("TeamsList.txt", ios::in);

		teamList = new string[size];

		for (int i = 0; i < size; i++) {
			file >> str;
			teamList[i] = str;
		}

		file.close();
	}
	//Loaded all teams
	Team* teams = new Team[size];
	float* teamAvgRankT20 = new float[size];
	float* teamAvgRankODI = new float[size];
	for (int i = 0; i < size; i++) {
		teams[i].loadTeam(teamList[i]);
		float t20Avg = 0, OdiAvg = 0;
		for (int j = 0; j < teams[i].totalPlayers; j++) {
			t20Avg += teams[i].players[j].Rank.T20;
			OdiAvg += teams[i].players[j].Rank.ODI;
		}
		teamAvgRankT20[i] = t20Avg / teams[i].totalPlayers;
		teamAvgRankODI[i] = OdiAvg / teams[i].totalPlayers;
	}


	//sort Ranks
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (teamAvgRankT20[j] > teamAvgRankT20[j + 1]) {
				float temp = teamAvgRankT20[j];
				teamAvgRankT20[j] = teamAvgRankT20[j + 1];
				teamAvgRankT20[j + 1] = temp;
			}
			if (teamAvgRankODI[j] > teamAvgRankODI[j + 1]) {
				float temp = teamAvgRankODI[j];
				teamAvgRankODI[j] = teamAvgRankODI[j + 1];
				teamAvgRankODI[j + 1] = temp;
			}
		}
	}

	//asign ranks
	for (int i = 0; i < size; i++) {
		teams[i].loadTeam(teamList[i]);
		float t20Avg = 0, OdiAvg = 0;
		for (int j = 0; j < teams[i].totalPlayers; j++) {
			t20Avg += teams[i].players[j].Rank.T20;
			OdiAvg += teams[i].players[j].Rank.ODI;
		}
		t20Avg /= teams[i].totalPlayers;
		OdiAvg /= teams[i].totalPlayers;
		for (int k = 0; k < size; k++) {
			if (t20Avg == teamAvgRankT20[k]) {
				teams[i].rank.T20 = k + 1;
				teamAvgRankT20[k] = -1;
			}
			if (OdiAvg == teamAvgRankODI[k]) {
				teams[i].rank.ODI = k + 1;
				teamAvgRankODI[k] = -1;

			}
		}
	}

	for (int i = 0; i < size; i++) {
		teams[i].teamSave();
	}

	delete[] teamAvgRankT20;
	delete[] teamAvgRankODI;
	delete[] teams;
	delete[] teamList;
}
void Match::updatePlayerRanking() {
	//get all players in objs
	string* teamList = new string[0];
	int size = 0;
	fstream file;
	file.open("TeamsList.txt", ios::in);
	if (!(file.is_open())) {
		cout << "Error Getting Teams List! File Not Found!" << endl;
		return;
	}
	else {
		string str;
		while (file >> str) { size++; }
		file.close();
		file.open("TeamsList.txt", ios::in);

		teamList = new string[size];

		for (int i = 0; i < size; i++) {
			file >> str;
			teamList[i] = str;
		}

		file.close();
	}
	//Loaded all teams
	Team* teams = new Team[size];
	int totalPlayers = 0;
	for (int i = 0; i < size; i++) {
		teams[i].loadTeam(teamList[i]);
		for (int j = 0; j < teams[i].totalPlayers; j++) {
			//Update all player avg.
			teams[i].players[j].autoUpdAverage();
		}
		totalPlayers += teams[i].totalPlayers;
	}

	double* t20R = new double[totalPlayers];
	double* ODIR = new double[totalPlayers];
	//Store all Avgs
	int k = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < teams[i].totalPlayers; j++) {
			t20R[k] = teams[i].players[j].Average;
			ODIR[k] = (teams[i].players[j].Total_runs +
				(2 * teams[i].players[j].Total_wickets)) /
				(teams[i].players[j].Matches_played + 1);
			k++;
		}
	}

	//Sort the Avg List
	for (int i = 0; i < totalPlayers - 1; i++) {
		for (int j = 0; j < totalPlayers - i - 1; j++) {
			if (t20R[j] < t20R[j + 1]) {
				//swap
				double t = t20R[j];
				t20R[j] = t20R[j + 1];
				t20R[j + 1] = t;
			}
			if (ODIR[j] > ODIR[j + 1]) {
				//swap
				double t = ODIR[j];
				ODIR[j] = ODIR[j + 1];
				ODIR[j + 1] = t;
			}
		}
	}
	//index shows player rank.
	//Give New Ranks
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < teams[i].totalPlayers; j++) {
			double avg = teams[i].players[j].Average;
			double avg2 = (teams[i].players[j].Total_runs +
				(2 * teams[i].players[j].Total_wickets)) /
				(teams[i].players[j].Matches_played + 1);
			//cout << "AVG: " << avg << endl;
			for (int k = 0; k < totalPlayers; k++) {
				if (avg == t20R[k]) {
					teams[i].players[j].Rank.T20 = k + 1;
					t20R[k] = -1;
				}
				if (avg2 == ODIR[k]) {
					teams[i].players[j].Rank.ODI = k + 1;
					ODIR[k] = -1;
				}
			}
		}
	}


	for (int i = 0; i < size; i++) {
		teams[i].teamSave();
	}

	delete[] t20R;
	delete[] ODIR;
	delete[] teams;
	delete[] teamList;
}

void Match::displayUpcomingMatches() {
	system("cls");
	int matchesListSize;
	Match* Match_List = GetMatchesList(matchesListSize);
	displayMatch(Match_List, matchesListSize, "upcoming");
	delete[] Match_List;
	_getch(); system("cls");
}

void Match::displayRecentMatches() {
	system("cls");
	int matchesListSize;
	Match* Match_List = GetMatchesList(matchesListSize);
	displayMatch(Match_List, matchesListSize, "recent");
	delete[] Match_List;
	_getch(); system("cls");
}