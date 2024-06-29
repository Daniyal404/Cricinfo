#pragma once
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
using namespace std;

struct ICC_Ranking {
	int T20 = -1;
	int ODI = -1;
};

class Player {
protected:
	string Name;
	string ShirtNo;
	double Average;
	ICC_Ranking Rank;	//T20 = avg | ODI = (runs + 2*wickets)/total matches
	int Total_runs;
	int Matches_played;
	int Total_wickets;
public:
	Player();
	void addPlayer(Player plrs[], int& size, Player newPlayer);
	bool removePlayer(Player* plrs, int& size, string shrtNo);
	int searchPlayer(Player* plrs, int& size, string shrtNo);
	void updatePlayer(string Name, string ShirtNo, double Average, int T20, int ODI,
		int Total_runs, int Matches_played, int Total_wickets);
	void displayStatus();
	void autoUpdAverage();

	friend class Team;
	friend class Match;
	friend Player getPlayerData(Player);
};


class Team {
private:
	string file;
protected:
	Player players[11];
	string Name;
	ICC_Ranking rank;	//T20 = Win/Lose | ODI = Win/Lose
	int totalPlayers;
	int TotalWins;
	int TotalLosts;
	string Team_Captain;
	string Team_Coach;
	string Admin_Username;
	string Admin_Password;
public:
	Team();
	void addPlayer();
	void removePlayer();
	void searchPlayer();
	void updatePlayer();
	void displayMatches();
	void updateCaptain(string cap);
	void updateCoach(string coach);
	void displayTeam();
	bool loadTeam(string file);
	void teamSave();
	Team operator = (Team& t) {
		file = t.file;
		for (int i = 0; i < 11; i++) {
			players[i] = t.players[i];
		}
		rank = t.rank;
		totalPlayers = t.totalPlayers;
		TotalWins = t.TotalWins;
		TotalLosts = t.TotalLosts;
		Team_Captain = t.Team_Captain;
		Team_Coach = t.Team_Coach;
		Admin_Username = t.Admin_Username;
		Admin_Password = t.Admin_Password;
		return *this;
	}
	string getTeamName() { return Name; }
	string getUsername() { return Admin_Username; }
	string getPassword() { return Admin_Password; }
	friend class Match;
};

class Match {
private:
	Team Team1;
	Team Team2;
	string Date;
	string Venue;
	char MatchType;	//first-class = f, oneday = o, T20 = t
	string Tournament_Name;	//(T20 World Cup, IPL, PSL, etc.)
	string Commentators[2];
	string Umpires[3];
	string Match_status; //(upcoming, recent, etc.)
public:
	Match() { }
	void play_match(Match&);
	//T20 = 120balls
	//ODI = 300balls
	//f = no limit
	//Total Runs / matches * 100
	void conductMatch(string* teamsList, int teamsSize);
	void scheduleMatch(string* teamsList, int teamsSize);

	void updateWorldRecords();		//Called After Conduct Match
	void updateTeamRanking();		//Called After Conduct Match
	void updatePlayerRanking();		//Called After Conduct Match

	void displayUpcomingMatches();
	void displayRecentMatches();
	friend Match* GetMatchesList(int&);
	friend void displayMatch(Match* list, int size, string str1, string str2);
};

