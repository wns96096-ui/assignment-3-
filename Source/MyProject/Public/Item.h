// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"



UCLASS()
class MYPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool bUseBlinking = true; 

	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool bUseRandomTeleport = true; 
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool bUseReverse = true; 
protected:
	UPROPERTY(visibleAnywhere,BlueprintReadOnly,Category="Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(editAnywhere,BlueprintReadWrite,Category="Item|Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* CustomMaterial;
	UPROPERTY(EditAnywhere, Category = "Timer")
	float ReserveDelay = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Timer")
	float DisappearDelay = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Timer")
	float MoveDelay = 3.0f;
	
	
	FTimerHandle DisappearTimerHandle;
	void DisappearPlatform();
	void ReappearPlatform();
	
	FTimerHandle ReverseTimerHandle;
	void ReverseRotationDirection();
	
	FTimerHandle MoveTimerHandle;
	void MoveToRandomLocation();
	
	
	UPROPERTY(editAnywhere,BlueprintReadWrite,Category="Item|Properties")
	float RotationSpeed;;
	
	virtual void BeginPlay()override;
	virtual void Tick( float DeltaSeconds )override;
	
	public:
	void SetPlatformVisuals(UStaticMesh* NewMesh, UMaterialInterface* NewMaterial);
	
	void ActivatePlatformTimers();
	

};

