#include "Stats.h"

std::unordered_map<uint64_t, Stats::playerStats> Stats::allPlayersStats{};
struct Stats::teamStats Stats::purple {};
struct Stats::teamStats Stats::yellow {};
int Stats::localTeam { 0 };

Stats::Stats()
{
}


Stats::~Stats()
{
}


void Stats::addPlayer(uint64_t PID, int team){
	playerStats player(team);
	allPlayersStats.emplace(PID, player);
}

void Stats::playerDied(uint64_t PID, int& kills, int& deaths){
	playerStats temp = allPlayersStats.find(PID)->second;
	kills = temp.kills;
	deaths = temp.deaths;
}

void Stats::resetStats(){
	// Base health
	purple.baseHealth = 0;
	yellow.baseHealth = 0;
	// Minion killed
	purple.otherTeamMinionsKilled = 0;
	yellow.otherTeamMinionsKilled = 0;
	// Players killed
	purple.otherTeamPlayersKilled = 0;
	yellow.otherTeamPlayersKilled = 0;
	// feathers fired
	purple.feathersFired = 0;
	yellow.feathersFired = 0;
	// abilities used
	purple.abilitiesUsed = 0;
	yellow.abilitiesUsed = 0;
	// clear the map
	allPlayersStats.clear();
}

void Stats::incBaseHealth(int team){
	if (team == 1)
		++yellow.baseHealth;
	else if (team == 2)
		++purple.baseHealth;
}

void Stats::incMinionsDied(int team){
	if (team == 1)
		++purple.otherTeamMinionsKilled;
	else if (team == 2)
		++yellow.otherTeamMinionsKilled;
}

void Stats::incPlayersDied(int team){
	if (team == 1)
		++purple.otherTeamPlayersKilled;
	else if (team == 2)
		++yellow.otherTeamPlayersKilled;
}

void Stats::incFeathersFired(int team){
	if (team == 1)
		++yellow.feathersFired;
	else if (team == 2)
		++purple.feathersFired;
}

void Stats::incAbilitiesUsed(int team){
	if (team == 1)
		++yellow.abilitiesUsed;
	else if (team == 2)
		++purple.abilitiesUsed;
}

int Stats::baseHealth(int team){
	if (team == 1)
		return yellow.baseHealth;
	else if (team == 2)
		return purple.baseHealth;
	return -1;
}

int Stats::otherTeamMinionsKilled(int team){
	if (team == 1)
		return yellow.otherTeamMinionsKilled;
	else if (team == 2)
		return purple.otherTeamMinionsKilled;
	return -1;
}

int Stats::otherTeamPlayersKilled(int team){
	if (team == 1)
		return yellow.otherTeamPlayersKilled;
	else if (team == 2)
		return purple.otherTeamPlayersKilled;
	return -1;
}

int Stats::abilitiesUsed(int team){
	if (team == 1)
		return yellow.abilitiesUsed;
	else if (team == 2)
		return purple.abilitiesUsed;
	return -1;
}
