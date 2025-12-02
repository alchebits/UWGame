#pragma once

#include "GameFramework/GameModeBase.h"
#include "UWGameGameMode.generated.h"

UCLASS()
class UWGAME_API AUWGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AUWGameGameMode();

	// AActor interface
	virtual void Tick(float DeltaSeconds) override;
	// ---
	
	//~ AGameModeBase interface
	virtual void InitGameState() override;
	// ---

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(float ScoreToAdd);

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenNextLevel(int32 LevelNumber);

	UFUNCTION(BlueprintImplementableEvent)
	void OnScoreChanged(float CurrentScore);
	
	UPROPERTY()
	float GameSessionTimeSeconds = 15.f;

	UPROPERTY()
	float ScoreToNextLevel = 3.f;
};
