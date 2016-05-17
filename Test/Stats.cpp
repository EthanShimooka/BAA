#include "Stats.h"

struct Stats::teamStats Stats::purple {};
struct Stats::teamStats Stats::yellow {};
int Stats::localTeam { 0 };

Stats::Stats()
{
}


Stats::~Stats()
{
}

void Stats::resetStats(){
	// Base health
	purple.baseHealthLost = 0;
	yellow.baseHealthLost = 0;
	// Minion killed
	purple.otherTeamMinionsKilled = 0;
	yellow.otherTeamMinionsKilled = 0;
	// Players killed
	purple.otherTeamPlayersKilled = 0;
	yellow.otherTeamPlayersKilled = 0;
}