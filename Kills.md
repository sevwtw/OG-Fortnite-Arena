### SDK (AFortPlayerController.cpp in function ClientOnPawnDied)
### Solos (Required)
```cpp
KillerPlayerState->KillScore()++;
KillerPlayerState->OnRep_Kills();
KillerPlayerState->ClientReportKill(DeadPlayerState);

KillerPlayerState->TeamKillScore()++; // From my testing, you need this for the elimination pop-up
KillerPlayerState->OnRep_TeamKillScore();
KillerPlayerState->ClientReportTeamKill(KillerPlayerState->TeamKillScore());
```

### SDK (AFortPlayerController.h)
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

