# Placement Points
Displays Arena points with placement scoring.

### SDK (FortPlayerController.cpp)
- Replace your bIsRespawningAllowed code with this snippet
```cpp
if (!bIsRespawningAllowed)
{
	auto GameMode = Cast<AFortGameModeAthena>(GetWorld()->GetGameMode());

	LOG_INFO(LogDev, "PlayersLeft: {} IsDBNO: {}", GameState->GetPlayersLeft(), DeadPawn->IsDBNO());

	if (!DeadPawn->IsDBNO())
	{
		if (bHandleDeath)
		{
			if (Fortnite_Version > 1.8 || Fortnite_Version == 1.11)
			{
				static void (*RemoveFromAlivePlayers)(AFortGameModeAthena * GameMode, AFortPlayerController * PlayerController, APlayerState * PlayerState, APawn * FinisherPawn,
					UFortWeaponItemDefinition * FinishingWeapon, uint8_t DeathCause, char a7)
					= decltype(RemoveFromAlivePlayers)(Addresses::RemoveFromAlivePlayers);

				AActor* DamageCauser = *(AActor**)(__int64(DeathReport) + MemberOffsets::DeathReport::DamageCauser);
				UFortWeaponItemDefinition* KillerWeaponDef = nullptr;

				static auto FortProjectileBaseClass = FindObject<UClass>(L"/Script/FortniteGame.FortProjectileBase");

				if (DamageCauser)
				{
					if (DamageCauser->IsA(FortProjectileBaseClass))
					{
						auto Owner = Cast<AFortWeapon>(DamageCauser->GetOwner());
						KillerWeaponDef = Owner->IsValidLowLevel() ? Owner->GetWeaponData() : nullptr; // I just added the IsValidLowLevel check because what if the weapon destroys (idk)?
					}
					if (auto Weapon = Cast<AFortWeapon>(DamageCauser))
					{
						KillerWeaponDef = Weapon->GetWeaponData();
					}
				}

				RemoveFromAlivePlayers(GameMode, PlayerController, KillerPlayerState == DeadPlayerState ? nullptr : KillerPlayerState, KillerPawn, KillerWeaponDef, DeathCause, 0);

				LOG_INFO(LogDev, "Removed!");
			}

			// LOG_INFO(LogDev, "KillerPlayerState->Place: {}", KillerPlayerState ? KillerPlayerState->GetPlace() : -1);

			LOG_INFO(LogDev, "TeamsLeft: {}", GameState->GetTeamsLeft()); // Important for launcher don't remove!
		}
	}

	// Commented this out for testing in my own gameserver, you don't need to comment this out
	//if (Fortnite_Version < 6) // Spectating (is this the actual build or is it like 6.10 when they added it auto).
	//{
	//	if (GameState->GetGamePhase() > EAthenaGamePhase::Warmup)
	//	{
	//		static auto bAllowSpectateAfterDeathOffset = GameMode->GetOffset("bAllowSpectateAfterDeath");
	//		bool bAllowSpectate = GameMode->Get<bool>(bAllowSpectateAfterDeathOffset);

	//		LOG_INFO(LogDev, "bAllowSpectate: {}", bAllowSpectate);

	//		if (bAllowSpectate)
	//		{
	//			LOG_INFO(LogDev, "Starting Spectating!");

	//			static auto PlayerToSpectateOnDeathOffset = PlayerController->GetOffset("PlayerToSpectateOnDeath");
	//			PlayerController->Get<APawn*>(PlayerToSpectateOnDeathOffset) = KillerPawn;

	//			UKismetSystemLibrary::K2_SetTimer(PlayerController, L"SpectateOnDeath", 5.f, false); // Soo proper its scary
	//		}
	//	}
	//}

	if (Fortnite_Version >= 15) // dk if this is correct
	{
		PlayerController->GetStateName() = UKismetStringLibrary::Conv_StringToName(L"Spectating");
	}

	auto AllPlayerStates = UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFortPlayerStateAthena::StaticClass());
	TArray<AFortPlayerControllerAthena*> AllPlayerControllers = GameMode->GetAlivePlayers();

	bool bDidSomeoneWin = AllPlayerStates.Num() == 1;

	for (int i = 0; i < AllPlayerStates.Num(); ++i)
	{
		auto CurrentPlayerState = (AFortPlayerStateAthena*)AllPlayerStates.at(i);

		if (bDidSomeoneWin && CurrentPlayerState->GetPlace() <= 1)
		{
			auto Controller = (AFortPlayerControllerAthena*)AllPlayerControllers.at(i);
			if (!Controller) continue;

			Controller->ClientReportTournamentPlacementPointsScored(CurrentPlayerState->GetPlace(), 50); // Victory Royale points
			break;
		}
	}
}

auto GameMode = Cast<AFortGameModeAthena>(GetWorld()->GetGameMode());

auto AllPlayerStates = UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFortPlayerStateAthena::StaticClass());
auto AllPlayerControllers = GameMode->GetAlivePlayers();

for (int32 i = 0; i < AllPlayerControllers.Num(); ++i) {
	auto Controller = (AFortPlayerControllerAthena*)AllPlayerControllers.at(i);
	if (!Controller) continue;

	auto CurrentPlayerState = (AFortPlayerStateAthena*)AllPlayerStates.at(i);
	if (!CurrentPlayerState) continue;

	int32 Placement = CurrentPlayerState->GetPlace();
	int32 Points = 0;

	else if (Placement == 3) Points += 10;
	else if (Placement == 5) Points += 20;
	else if (Placement <= 10) Points += 10;
	else if (Placement <= 20) Points += 15;
	else if (Placement <= 25) Points += 15;

	//else if (Placement == 2) Points += 25; // Uncomment if you want Top 2 Placement
	//else if (Placement == 4) Points += 10; // Uncomment if you want Top 4 Placement
	//else if (Placement <= 30) Points += 10; // Uncomment if you want Top 30 Placement
	//else if (Placement <= 40) Points += 10; // Uncomment if you want Top 40 Placement
	//else if (Placement <= 50) Points += 10; // Uncomment if you want Top 50 Placement

	if (Points > 0) {
		Controller->ClientReportTournamentPlacementPointsScored(Placement, Points);
	}
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
