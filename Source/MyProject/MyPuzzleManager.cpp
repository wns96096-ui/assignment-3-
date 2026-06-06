// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Item.h"
#include "Public/Move.h"
#include "MyPuzzleManager.h"



// Sets default values
AMyPuzzleManager::AMyPuzzleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMyPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	if (MovingPlatformClass && RotatingPlatformClass)
	{
		for (int32 i = 0; i < TotalSpawnCount;++i)
		{
			FVector ManageLocation = GetActorLocation();
			FVector SpawnLocation;
			SpawnLocation.X = ManageLocation.X+FMath::RandRange(-RandXRange,RandXRange);
			SpawnLocation.Y = ManageLocation.Y+FMath::RandRange(-RandYRange,RandYRange);
			SpawnLocation.Z = ManageLocation.Z;
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			int32 PlatformTypeDice = FMath::RandRange(0,1);
			UStaticMesh* SelectedMesh = (MeshPool.Num() > 0) ? MeshPool[FMath::RandRange(0, MeshPool.Num() - 1)] : nullptr;
			UMaterialInterface* SelectedMaterial = (MaterialPool.Num() > 0) ? MaterialPool[FMath::RandRange(0, MaterialPool.Num() - 1)] : nullptr;
			
			if (PlatformTypeDice == 0)
			{
				AItem* NewItem = GetWorld()->SpawnActor<AItem>(RotatingPlatformClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
				if (NewItem)
				{
					NewItem->SetPlatformVisuals(SelectedMesh, SelectedMaterial);
					
					NewItem->bUseBlinking = bAllowBlinking;
					NewItem->bUseRandomTeleport = bAllowRandomTeleport ;
					NewItem->bUseReverse = bAllowReverse ;
					
					NewItem->ActivatePlatformTimers();
				}
			}
			else
			{
				AMove* NewMove = GetWorld()->SpawnActor<AMove>(MovingPlatformClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
				if (NewMove)
				{
					NewMove->SetPlatformVisuals(SelectedMesh, SelectedMaterial);
					
					NewMove->bUseBlinking = bAllowBlinking;
					NewMove->bUseRandomTeleport = bAllowRandomTeleport;

					NewMove->ActivatePlatformTimers();
				}
			}
		}
	}
}

// Called every frame
void AMyPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

