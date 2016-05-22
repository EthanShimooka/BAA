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
		int baseHealthLost;
		int otherTeamMinionsKilled;
		int otherTeamPlayersKilled;
		int feathersFired;
		int abilitiesUsed;
		teamStats() : baseHealthLost(0), otherTeamMinionsKilled(0), 
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
	static void incBaseHealthLost_purple() { ++purple.baseHealthLost; }
	static void incBaseHealthLost_yellow() { ++yellow.baseHealthLost; }
	// Minion killed
	static void incOtherTeamMinionsKilled_purple() { ++purple.otherTeamMinionsKilled; }
	static void incOtherTeamMinionsKilled_yellow() { ++yellow.otherTeamMinionsKilled; }
	// Players killed
	static void incOtherTeamPlayersKilled_purple() { ++purple.otherTeamPlayersKilled; }
	static void incOtherTeamPlayersKilled_yellow() { ++yellow.otherTeamPlayersKilled; }
	// Featehrs fired
	static void incFeathersFired_purple() { ++purple.feathersFired; }
	static void incFeathersFired_yellow() { ++yellow.feathersFired; }
	// Abilities used
	static void incAbilitiesUsed_purple() { ++purple.abilitiesUsed; }
	static void incAbilitiesUsed_yellow() { ++yellow.abilitiesUsed; }

	static void addPlayer(uint64_t PID, int team);

	static void incPlayerDied(uint64_t killed, uint64_t killer) {
		++(allPlayersStats.find(killed)->second.deaths);
		++(allPlayersStats.find(killer)->second.kills);
	}

	// Getter
	// Base health
	static int baseHealthLost_purple() { return purple.baseHealthLost; }
	static int baseHealthLost_yellow() { return yellow.baseHealthLost; }
	// Minion killed
	static int otherTeamMinionsKilled_purple() { return purple.otherTeamMinionsKilled; }
	static int otherTeamMinionsKilled_yellow() { return yellow.otherTeamMinionsKilled; }
	// Players killed
	static int otherTeamPlayersKilled_purple() { return purple.otherTeamPlayersKilled; }
	static int otherTeamPlayersKilled_yellow() { return yellow.otherTeamPlayersKilled; }
	// Featehrs fired
	static int feathersFired_purple() { return purple.feathersFired; }
	static int feathersFired_yellow() { return yellow.feathersFired; }
	// Abilities used
	static int abilitiesUsed_purple() { return purple.abilitiesUsed; }
	static int abilitiesUsed_yellow() { return yellow.abilitiesUsed; }
	// player stats
	static const playerStats& getPlayerStats(uint64_t PID) { return allPlayersStats.find(PID)->second; }
	static const mapStat& getPlayersStatsMap() { return allPlayersStats; }
	static void playerDied(uint64_t PID, int& kills, int& deaths);


	static void resetStats();
	static void setLocalTeam(int localTeam) { localTeam = localTeam; }
	static int getLocalTeam() { return localTeam; }



	
};