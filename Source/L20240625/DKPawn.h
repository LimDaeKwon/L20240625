// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DKPawn.generated.h"

UCLASS()
class L20240625_API ADKPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADKPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	TObjectPtr<class UBoxComponent> Box;

	TObjectPtr<class UStaticMeshComponent> Body;

	TObjectPtr<class UStaticMeshComponent> Left;

	TObjectPtr<class UStaticMeshComponent> Right;

	TObjectPtr<class UArrowComponent> Arrow;

	TObjectPtr<class UFloatingPawnMovement> Movement;

	TObjectPtr<class UCameraComponent> Camera;

	TObjectPtr<class USpringArmComponent> SpringArm;

	void Fire();
	void Boost();
	void BoostReleased();
	void Pitch(float Value);
	void Roll(float Value);




	float Scale;
	float RotateSpeed;

};
