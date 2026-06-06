// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Move.generated.h"

UCLASS()
class MYPROJECT_API AMove : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMove();
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool bUseBlinking = true; 

	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool bUseRandomTeleport = true; 
	
	void SetPlatformVisuals(UStaticMesh* NewMesh, UMaterialInterface* NewMaterial);
	
	void ActivatePlatformTimers();

protected:
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Move|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(editAnywhere,BlueprintReadWrite,Category="Move|Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* CustomMaterial;
	FTimerHandle DisappearTimerHandle;
    
	FTimerHandle MoveTimerHandle;
	void MoveToRandomLocation();
	
	void DisappearPlatform();
	void ReappearPlatform();
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRange = 500.0f;
	
	UPROPERTY(EditAnywhere, Category = "Timer")
	float DisappearDelay = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Timer")
	float MoveDelay = 3.0f;
	
	
	
	FVector StartLocation;
	
	FVector MoveDirection = FVector(1.0f,0.0f,0.0f);
	
	virtual void Tick( float DeltaSeconds )override;
	virtual void BeginPlay()override;

};
