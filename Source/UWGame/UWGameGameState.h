#pragma once

#include "GameFramework/GameState.h"
#include "UWGameGameState.generated.h"

UCLASS()
class UWGAME_API AUWGameGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AUWGameGameState();

	// AActor interface
	virtual void Tick(float DeltaSeconds) override;
	// ---
	
protected:
	UPROPERTY()
	float TimeLeftInSession = 0.f;

	UPROPERTY()
	float CurrentScore = 0.f;

	UPROPERTY()
	int32 CurrentLevel = 1;
	
	friend class AUWGameGameMode;
};
