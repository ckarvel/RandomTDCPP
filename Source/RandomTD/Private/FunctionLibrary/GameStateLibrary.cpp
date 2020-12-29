#include "FunctionLibrary/GameStateLibrary.h"

/////////////////////////////////////////////////////////////////////////////////////
UGameStateLibrary::UGameStateLibrary(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
}

/////////////////////////////////////////////////////////////////////////////////////
int UGameStateLibrary::GetCurrentLevel(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    return GI->GetLevelManager().GetCurrentLevel();
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
int UGameStateLibrary::GetSecondsPerLevel(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    return GI->GetLevelManager().GetSecondsPerLevel();
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
int UGameStateLibrary::GetPreLevelSeconds(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    return GI->GetLevelManager().GetPreLevelSeconds();
  }
  return -1;
}
