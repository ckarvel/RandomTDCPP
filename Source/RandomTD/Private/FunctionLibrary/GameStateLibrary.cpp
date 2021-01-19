#include "FunctionLibrary/GameStateLibrary.h"
#include "Game/RandomTDGameInstance.h"
#include "Managers/PlayerStateManager.h"
#include "Components/ItemMgmtComponent.h"
#include "Components/PriceMgmtComponent.h"
#include "Components/InventoryMgmtComponent.h"

/////////////////////////////////////////////////////////////////////////////////////
UGameStateLibrary::UGameStateLibrary(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
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

/////////////////////////////////////////////////////////////////////////////////////
UItemMgmtComponent* UGameStateLibrary::GetItemManager(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* TDGameInstance = Cast<URandomTDGameInstance>(GameInstance))
  {
    return TDGameInstance->GetItemManager();
  }
  return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////
ULevelMgmtComponent* UGameStateLibrary::GetLevelManager(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* TDGameInstance = Cast<URandomTDGameInstance>(GameInstance))
  {
    return TDGameInstance->GetLevelManager();
  }
  return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////
UPriceMgmtComponent* UGameStateLibrary::GetPriceManager(UGameInstance* GameInstance)
{
  if (URandomTDGameInstance* TDGameInstance = Cast<URandomTDGameInstance>(GameInstance))
  {
    return TDGameInstance->GetPriceManager();
  }
  return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////
UInventoryMgmtComponent* UGameStateLibrary::GetInventoryManager(APlayerState* PlayerState)
{
  if (APlayerStateManager* TDPS = Cast<APlayerStateManager>(PlayerState))
  {
    return TDPS->GetInventoryManager();
  }
  return nullptr;
}
