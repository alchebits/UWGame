#pragma once

#include "GameFramework/Pawn.h"
#include "UWPlayerPawn.generated.h"

UCLASS()
class AUWPlayerPawn : public APawn
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float UnUnit);
	void MoveRight(float UnUnit);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float PlayerSpeedPerSecond = 10.f;
};

