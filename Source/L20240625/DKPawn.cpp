// Fill out your copyright notice in the Description page of Project Settings.


#include "DKPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DKRocket.h"

// Sets default values
ADKPawn::ADKPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetBoxExtent(FVector(12.0f, 12.0f, 12.0f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}


	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.f, -21.0f, 0));
	
	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.f, 21.0f, 0));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));

	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}


	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(100.f, 0, -20.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->TargetArmLength = 300.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Scale = 0.5;
	RotateSpeed = 3600.f;
}

// Called when the game starts or when spawned
void ADKPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), Scale);
	Left->AddRelativeRotation(FRotator(0, 0, DeltaTime * RotateSpeed));
	Right->AddRelativeRotation(FRotator(0, 0, DeltaTime * RotateSpeed));



}

// Called to bind functionality to input
void ADKPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADKPawn::Fire);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ADKPawn::Boost);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &ADKPawn::BoostReleased);

	PlayerInputComponent->BindAxis("Pitch", this, &ADKPawn::Pitch);

	PlayerInputComponent->BindAxis("Roll", this, &ADKPawn::Roll);



}

void ADKPawn::Fire()
{
	GetWorld()->SpawnActor<ADKRocket>(Arrow->K2_GetComponentLocation(), Arrow->K2_GetComponentRotation());
}

void ADKPawn::Boost()
{
	Scale = 1.0f;
}

void ADKPawn::BoostReleased()
{
	Scale = 0.5f;
}

void ADKPawn::Pitch(float Value)
{
	float Dir = FMath::Clamp(Value, -1.0f, 1.0f);
	AddActorLocalRotation(FRotator(Dir * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));
}

void ADKPawn::Roll(float Value)
{
	float Dir = FMath::Clamp(Value, -1.0f, 1.0f);
	AddActorLocalRotation(FRotator(0, 0, Dir * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));

}

