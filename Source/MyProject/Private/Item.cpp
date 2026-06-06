// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "MaterialHLSLTree.h"
#include "Misc/MapErrors.h"


// Sets default values
AItem::AItem()
{
 	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SceneRoot);

	
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	
	
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		FRotator NewRotation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);
		AddActorLocalRotation(NewRotation);
	}
}
void AItem::ReverseRotationDirection()
{
	RotationSpeed *= -1.0f;
}
void AItem::DisappearPlatform()
{
	if (StaticMesh)
	{
		StaticMesh->SetVisibility(false);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle,this,&AItem::ReappearPlatform,DisappearDelay,false);
	}
}
void AItem::ReappearPlatform()
{
	if (StaticMesh)
	{
		StaticMesh->SetVisibility(true);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle,this,&AItem::DisappearPlatform,DisappearDelay,false);
	}
}
void AItem::MoveToRandomLocation()
{
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation.X += FMath::RandRange(-500.0f, 500.0f);
	CurrentLocation.Y += FMath::RandRange(-500.0f, 500.0f);
	
	SetActorLocation(CurrentLocation);
}
void  AItem::SetPlatformVisuals(UStaticMesh* NewMesh, UMaterialInterface* NewMaterial)
{
	if (StaticMesh && NewMesh)
	{
		StaticMesh->SetStaticMesh(NewMesh);
	}
	if (StaticMesh && NewMaterial)
	{
		StaticMesh->SetMaterial(0, NewMaterial);
	}
}
	
void  AItem::ActivatePlatformTimers()
{
	if (bUseBlinking)
	{
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle, this, &AItem::DisappearPlatform,DisappearDelay,false);
	}
	if (bUseRandomTeleport)
	{
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,this,&AItem::MoveToRandomLocation,MoveDelay,true);
	}
	if (bUseReverse)
		GetWorld()->GetTimerManager().SetTimer(ReverseTimerHandle,this,&AItem::ReverseRotationDirection,ReserveDelay,true);
}
