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

/////////////////////////////////////////////////////////////////////////////////////
FHitResult UGameStateLibrary::GetHitOnCustomObjectTypes(APlayerController* PC, bool UseChannel, ECollisionChannel Channel)
{
  FHitResult Hit;
  if (UseChannel)
  {
    TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
    Objects.Add(UEngineTypes::ConvertToObjectType(Channel));
    PC->GetHitResultUnderCursorForObjects(Objects, false, Hit);
  }
  else
  {
    TArray<TEnumAsByte<EObjectTypeQuery>> _CustomObjectTypes;
    _CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(GridTraceChannel));
    _CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(TowerTraceChannel));
    PC->GetHitResultUnderCursorForObjects(_CustomObjectTypes, false, Hit);
  }
  return Hit;
}
