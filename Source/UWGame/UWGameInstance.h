#pragma once

#include "Engine/GameInstance.h"
#include "UWGameInstance.generated.h"

UCLASS()
class UUWGameInstance : public UGameInstance
{
public:
	GENERATED_BODY()

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	float GetScoreSum() const;

	UFUNCTION(BlueprintCallable)
	float GetHighestScore() const;

	UFUNCTION(BlueprintCallable)
	void SetScoreSum(float NewScoreSum);

	UFUNCTION(BlueprintCallable)
	void SetHighestScore(float NewHighestScore);
	
protected:
	UPROPERTY()
	float ScoreSum = 0.f;

	UPROPERTY()
	float HighestScore = 0.f;
};
