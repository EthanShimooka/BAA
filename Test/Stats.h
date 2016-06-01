#pragma once
#include <unordered_map>
#include <stdint.h>

class Stats
{
public:
	struct playerStats{
		int team;
		int kills;
		int deaths;
		playerStats(int team) : team(team), kills(0), deaths(0) {}
	};

	typedef std::unordered_map<uint64_t, playerStats> mapStat;
private:
	struct teamStats{
		int baseHealth;
		int otherTeamMinionsKilled;
		int otherTeamPlayersKilled;
		int feathersFired;
		int abilitiesUsed;
		teamStats() : baseHealth(0), otherTeamMinionsKilled(0), 
			otherTeamPlayersKilled(0), feathersFired(0), abilitiesUsed(0) {}
	};

	static mapStat allPlayersStats;
	static teamStats purple;
	static teamStats yellow;
	static int localTeam;

public:
	Stats();
	~Stats();

	// Increments
	// Base health
	static void incBaseHealth_purple() { ++purple.baseHealth; }
	static void incBaseHealth_yellow() { ++yellow.baseHealth; }
	static void incBaseHealth(int team);
	static void setBaseHealth(int team, int value);
	// Minion killed
	static void incOtherTeamMinionsKilled_purple() { ++purple.otherTeamMinionsKilled; }
	static void incOtherTeamMinionsKilled_yellow() { ++yellow.otherTeamMinionsKilled; }
	static void incMinionsDied(int team);
	// Players killed
	static void incOtherTeamPlayersKilled_purple() { ++purple.otherTeamPlayersKilled; }
	static void incOtherTeamPlayersKilled_yellow() { ++yellow.otherTeamPlayersKilled; }
	static void incPlayersDied(int team);
	// Featehrs fired
	static void incFeathersFired_purple() { ++purple.feathersFired; }
	static void incFeathersFired_yellow() { ++yellow.feathersFired; }
	static void incFeathersFired(int team);
	// Abilities used
	static void incAbilitiesUsed_purple() { ++purple.abilitiesUsed; }
	static void incAbilitiesUsed_yellow() { ++yellow.abilitiesUsed; }
	static void incAbilitiesUsed(int team);

	static void addPlayer(uint64_t PID, int team);

	static void incPlayerDied(uint64_t killed, uint64_t killer) {
		++(allPlayersStats.find(killed)->second.deaths);
		++(allPlayersStats.find(killer)->second.kills);
	}

	// Getter
	// Base health
	static int baseHealth_purple() { return purple.baseHealth; }
	static int baseHealth_yellow() { return yellow.baseHealth; }
	static int baseHealth(int team);
	// Minion killed
	static int otherTeamMinionsKilled_purple() { return purple.otherTeamMinionsKilled; }
	static int otherTeamMinionsKilled_yellow() { return yellow.otherTeamMinionsKilled; }
	static int otherTeamMinionsKilled(int team);
	// Players killed
	static int otherTeamPlayersKilled_purple() { return purple.otherTeamPlayersKilled; }
	static int otherTeamPlayersKilled_yellow() { return yellow.otherTeamPlayersKilled; }
	static int otherTeamPlayersKilled(int team);
	// Featehrs fired
	static int feathersFired_purple() { return purple.feathersFired; }
	static int feathersFired_yellow() { return yellow.feathersFired; }
	static int feathersFired(int team);
	// Abilities used
	static int abilitiesUsed_purple() { return purple.abilitiesUsed; }
	static int abilitiesUsed_yellow() { return yellow.abilitiesUsed; }
	static int abilitiesUsed(int team);
	// player stats
	static const playerStats& getPlayerStats(uint64_t PID) { return allPlayersStats.find(PID)->second; }
	static const mapStat& getPlayersStatsMap() { return allPlayersStats; }
	static void playerDied(uint64_t PID, int& kills, int& deaths);


	static void resetStats();
	static void setLocalTeam(int localTeam) { localTeam = localTeam; }
	static int getLocalTeam() { return localTeam; }



	
};