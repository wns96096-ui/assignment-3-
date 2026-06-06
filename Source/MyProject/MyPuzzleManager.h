// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPuzzleManager.generated.h"

class AMove;
class AItem;

UCLASS()
class MYPROJECT_API AMyPuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPuzzleManager();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Puzzle | Classes")
	TSubclassOf<AMove> MovingPlatformClass;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle | Classes")
	TSubclassOf<AItem> RotatingPlatformClass;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle | Settings")
	int32 TotalSpawnCount = 10;
	UPROPERTY(EditAnywhere, Category = "RandomRangeX")
	float RandXRange = 1200.0f;
	UPROPERTY(EditAnywhere, Category = "RandomRangeY")
	float RandYRange = 1200.0f;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle | Visuals")
	TArray<UStaticMesh*> MeshPool;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle | Visuals")
	TArray<UMaterialInterface*> MaterialPool;
	UPROPERTY(EditAnywhere, Category = "Puzzle | Master Switches")
	bool bAllowBlinking = true;

	UPROPERTY(EditAnywhere, Category = "Puzzle | Master Switches")
	bool bAllowRandomTeleport = true;

	UPROPERTY(EditAnywhere, Category = "Puzzle | Master Switches")
	bool bAllowReverse = true;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
