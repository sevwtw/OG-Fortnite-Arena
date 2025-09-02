# OG-Fortnite-Arena
Displays Arena points with elimination pop-ups, placement scoring, and full widget support. Made for OG Fortnite Private Servers.

Credits to wiktorwiktor12 for the Widget code

### SDK (AFortPlayerStateAthena.cpp in function ClientOnPawnDied)
### Solos (Required)
```cpp
KillerPlayerState->KillScore()++;
KillerPlayerState->OnRep_Kills();
KillerPlayerState->ClientReportKill(DeadPlayerState);

KillerPlayerState->TeamKillScore()++; // From my testing, you need this for the elimination pop-up
KillerPlayerState->OnRep_TeamKillScore();
KillerPlayerState->ClientReportTeamKill(KillerPlayerState->TeamKillScore());
```

### SDK (AFortPlayerStateAthena.h)
```cpp
int32& KillScore()
{
  static auto KillScore = GetOffset("KillScore");
  return Get<int32>(KillScore);
}

int32& TeamKillScore()
{
  static auto TeamKillScore = GetOffset("TeamKillScore");
  return Get<int32>(TeamKillScore);
}

void ClientReportTeamKill(int32 TeamKills) 
{
  static auto Function = FindFunction("ClientReportTeamKill");
  this->ProcessEvent(Function, &TeamKills);
}

void ClientReportKill(AFortPlayerStateAthena* Player)
{
  static auto Function = FindFunction("ClientReportKill");
  this->ProcessEvent(Function, &Player);
}

void OnRep_TeamKillScore()
{
  static auto Function = FindFunction("OnRep_TeamKillScore");
  this->ProcessEvent(Function);
}

void OnRep_Kills()
{
  static auto Function = FindFunction("OnRep_Kills");
  this->ProcessEvent(Function);
}
```

