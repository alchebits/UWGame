#pragma once

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
	UUWBoidSubsystem();
	
	//~ UWorldSubsystem
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	//~ ---
	
	//~ UTickableWorldSubsystem
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// ---

	bool RegisterActor(AActor* AuwSheep, uint32& RetID);
	bool UnregisterActor(uint32 ID);

protected:
	FVector ApplySeparation(const FBoid& Boid);
	FVector ApplyAlignment(const FBoid& Boid);
	FVector ApplyCohesion(const FBoid& Boid);
	FVector LimitVectorLength(const FVector& Vector, float MaxSize);
	
private:
	uint32 NextID = 0;
	TArray<FBoid> Boids;
	float NeighborRadius;
	float SeparationWeight;
	float AlignmentWeight;
	float CohesionWeight;
	float MaxSpeed;
	float MaxForce;

	UPROPERTY()
	TMap<uint32, AActor*> BoidActors;
};
