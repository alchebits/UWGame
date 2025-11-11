#pragma once

#include "UWGameLog.h"
#include "Subsystems/WorldSubsystem.h"
#include "UWBoidSubsystem.generated.h"

struct FBoid
{
	uint32 ID;
	FVector Position;
	FVector Velocity;
};

UCLASS()
class UUWBoidSubsystem : public UTickableWorldSubsystem
{
public:
	GENERATED_BODY()

	//~ UWorldSubsystem
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	//~ ---
	
	//~ UTickableWorldSubsystem
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// ---

protected:
	FVector ApplySeparation(const FBoid& Boid);
	FVector ApplyAlignment(const FBoid& Boid);
	FVector ApplyCohesion(const FBoid& Boid);
	FVector LimitVectorLength(const FVector& Vector, float MaxSize);
	
private:
	uint32 NextID = 0;
	TArray<FBoid> Boids;
	float NeighborRadius = 500.f;
	float SeparationWeight = 1.f;
	float AlignmentWeight = 1.f;
	float CohesionWeight = 2.f;
	float MaxSpeed = 100.f;
	float MaxForce = 100.f;
};
