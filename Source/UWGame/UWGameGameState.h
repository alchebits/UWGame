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

	void AddPointsToNextLevel(float PointsToAdd);
	
protected:
	UPROPERTY()
	float TimeLeftInSession = 0.f;

	UPROPERTY()
	float CurrentPointsToNextLevel = 0.f;
	
	friend class AUWGameGameMode;
};
