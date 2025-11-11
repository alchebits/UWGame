#pragma once

#include "GameFramework/GameState.h"
#include "UWGameGameState.generated.h"

UCLASS()
class UWGAME_API AUWGameGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AUWGameGameState();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	float TimeLeftInSession = 0.f;

	friend class AUWGameGameMode;
};
