// Fill out your copyright notice in the Description page of Project Settings.


#include "DKRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADKRocket::ADKRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	Rocket->SetupAttachment(Box);
	Box->SetBoxExtent(FVector(12.0f, 12.0f, 12.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Rocket->SetStaticMesh(SM_Rocket.Object);
	}
	Rocket->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Movement->InitialSpeed = 1000.f;
	Movement->MaxSpeed = 1000.f;
	Movement->ProjectileGravityScale = 0;


}

// Called when the game starts or when spawned
void ADKRocket::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(2.0f);
	
}

// Called every frame
void ADKRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

