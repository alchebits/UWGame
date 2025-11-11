#pragma once

#include "GameFramework/DefaultPawn.h"
#include "UWPlayerPawn.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class AUWPlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void HandleMovementInput(const FInputActionValue& InputValue);
	void HandleCameraInput(const FInputActionValue& InputValue);

	// Changing speed to acceleration per second, because now, ADefaultPawn gives us FloatingMovementComponent features with max speed defined there
	UPROPERTY(EditAnywhere, Category = "Movement")
	float AccelerationPerSecond = 10.f;

	UPROPERTY(EditAnywhere, Category = "EI")
	TObjectPtr<UInputMappingContext> WolfInputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "EI")
	TObjectPtr<UInputAction> MovementInputAction;

	UPROPERTY(EditAnywhere, Category = "EI")
	TObjectPtr<UInputAction> CameraInputAction;
};

