#pragma once

#include "GameFramework/GameModeBase.h"
#include "UWGameGameMode.generated.h"

UCLASS()
class UWGAME_API AUWGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AUWGameGameMode();

	//~ AGameModeBase interface
	virtual void InitGameState() override;
	// ---

	UPROPERTY()
	float GameSessionTimeSeconds = 100.f;
};
