### SDK (FortPlayerController.cpp)
- Put this in the ClientOnPawnDiedHook function, it should look something like this.
<img width="1034" height="560" alt="image" src="https://github.com/user-attachments/assets/29d96450-6b56-4020-a79f-64cdd1ee1394" />

```cpp
KillerPlayerState->KillScore()++;
KillerPlayerState->OnRep_Kills();
KillerPlayerState->ClientReportKill(DeadPlayerState);

KillerPlayerState->TeamKillScore()++;
KillerPlayerState->OnRep_TeamKillScore();
KillerPlayerState->ClientReportTeamKill(KillerPlayerState->TeamKillScore()); // From my testing, you need this for the elimination pop-up

// Reboot version
if (MemberOffsets::FortPlayerStateAthena::KillScore != -1)
	KillerPlayerState->Get<int>(MemberOffsets::FortPlayerStateAthena::KillScore)++;

if (MemberOffsets::FortPlayerStateAthena::TeamKillScore != -1)
	KillerPlayerState->Get<int>(MemberOffsets::FortPlayerStateAthena::TeamKillScore)++;

KillerPlayerState->OnRep_Kills();
KillerPlayerState->ClientReportKill(DeadPlayerState);

KillerPlayerState->OnRep_TeamKillScore();
KillerPlayerState->ClientReportTeamKill(KillerPlayerState->TeamKillScore()); // From my testing, you need this for the elimination pop-up
```

### SDK (AFortPlayerStateAthena.h)
- Put this in the ClientOnPawnDiedHook function, it should look something like this.
<img width="1057" height="683" alt="image" src="https://github.com/user-attachments/assets/d944aeec-e01c-4a33-b4d4-024d04a79437" />

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

