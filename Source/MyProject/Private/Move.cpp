// Fill out your copyright notice in the Description page of Project Settings.


#include "Move.h"

// Sets default values
AMove::AMove()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SceneRoot);


}

// Called when the game starts or when spawned
void AMove::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	if (StaticMesh && CustomMaterial)
	{
		
		StaticMesh->SetMaterial(0, CustomMaterial);
	}
	
	
	
}

// Called every frame
void AMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation += MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);
	
	float DistanceMoved = FVector::Dist(CurrentLocation, StartLocation);
	
	if (DistanceMoved >= MaxRange)
	{
		MoveDirection = -MoveDirection;
		FVector BaseDirection = (CurrentLocation - StartLocation).GetSafeNormal();
		SetActorLocation(StartLocation + (BaseDirection * MaxRange));
	}

}

void AMove::DisappearPlatform()
{
	if (StaticMesh)
	{
		StaticMesh->SetVisibility(false);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle,this,&AMove::ReappearPlatform,DisappearDelay,false);
	}
}
void AMove::ReappearPlatform()
{
	if (StaticMesh)
	{
		StaticMesh->SetVisibility(true);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle,this,&AMove::DisappearPlatform,DisappearDelay,false);
	}
}
void AMove::MoveToRandomLocation()
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.X += FMath::RandRange(-500.0f, 500.0f);
	CurrentLocation.Y += FMath::RandRange(-500.0f, 500.0f);
	SetActorLocation(CurrentLocation);
	
	StartLocation = CurrentLocation;
}
void  AMove::SetPlatformVisuals(UStaticMesh* NewMesh, UMaterialInterface* NewMaterial)
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
	
void  AMove::ActivatePlatformTimers()
{
	if (bUseBlinking)
	{
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle, this, &AMove::DisappearPlatform,DisappearDelay,false);
	}
	if (bUseRandomTeleport)
	{
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,this,&AMove::MoveToRandomLocation,MoveDelay,true);
	}
	
}