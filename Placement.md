# Placement Points
Displays Arena points with placement scoring.

### SDK (FortPlayerController.cpp)
- Put this below the if (!bIsRespawningAllowed) block, it should look something like this.
<img width="1038" height="348" alt="image" src="https://github.com/user-attachments/assets/3c0aa578-9770-4cb0-bb21-ae2ea0f842de" />


```cpp
auto GameMode = Cast<AFortGameModeAthena>(GetWorld()->GetGameMode());

auto AllPlayerStates = UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFortPlayerStateAthena::StaticClass());
TArray<AFortPlayerControllerAthena*> AllPlayerControllers = GameMode->GetAlivePlayers();

bool bDidSomeoneWin = AllPlayerStates.Num() == 0;

for (int i = 0; i < AllPlayerStates.Num(); ++i)
{
	auto CurrentPlayerState = (AFortPlayerStateAthena*)AllPlayerStates.at(i);

	if (CurrentPlayerState->GetPlace() <= 1)
	{
		auto Controller = (AFortPlayerControllerAthena*)AllPlayerControllers.at(i);
		if (!Controller) continue;

		Controller->ClientReportTournamentPlacementPointsScored(1, 15); // Victory Royale points

		break;
	}
}

auto AllPlayerStates = UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFortPlayerStateAthena::StaticClass());
TArray<AFortPlayerControllerAthena*> AllPlayerControllers = GameMode->GetAlivePlayers();

for (int32 i = 0; i < AllPlayerControllers.Num(); ++i) {
	auto Controller = (AFortPlayerControllerAthena*)AllPlayerControllers.at(i);
	if (!Controller) continue;

	auto CurrentPlayerState = (AFortPlayerStateAthena*)AllPlayerStates.at(i);
	if (!CurrentPlayerState) continue;

	int32 Placement = CurrentPlayerState->GetPlace();
	if (Placement == 1) continue;

	if (Placement <= 3) Controller->ClientReportTournamentPlacementPointsScored(Placement, 10);
	else if (Placement <= 5) Controller->ClientReportTournamentPlacementPointsScored(Placement, 8);
	else if (Placement <= 10) Controller->ClientReportTournamentPlacementPointsScored(Placement, 6);
	else if (Placement <= 20) Controller->ClientReportTournamentPlacementPointsScored(Placement, 4);
	else if (Placement <= 25) Controller->ClientReportTournamentPlacementPointsScored(Placement, 2);
}
```

### SDK (AFortPlayerControllerAthena.h)
```cpp
void ClientReportTournamentPlacementPointsScored(int32 Placement, int32 PointsEarned) 
{
  static auto Function = FindFunction("ClientReportTournamentPlacementPointsScored");

  struct { int32 Placement; int32 PointsEarned; }
  
  Params{ Placement, PointsEarned };

  this->ProcessEvent(Function, &Params);
}
```
