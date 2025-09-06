# Placement Points
Displays Arena points with placement scoring.

### [Tutorial](https://www.youtube.com/watch?v=250LWiWNcLE)

### SDK (FortPlayerController.cpp)
```cpp
Code is buggy, wait until fix
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
