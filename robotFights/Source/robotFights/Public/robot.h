// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "robot.generated.h"

UCLASS()
class ROBOTFIGHTS_API Arobot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Arobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* AzimutGimbal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxSpeedBackward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeToReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float accelerationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float stopRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float inertionRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rotatationAcceleration;

	FTimerHandle accelerationHandle;
	FTimerHandle inertionHandle;
	FTimerHandle stopHandle;
	FTimerHandle leftHandle;
	FTimerHandle rightHandle;

	FVector forwardDirection;

	void Accelerate();
	void Inertion();
	void Stop();
	void increaseSpeed();
	void inertionSpeed();
	void stopSpeed();

	void left();
	void right();
	void turnLeft();
	void turnRight();
	void stopRotation();
	void rotation(float Value);

	void rotateX(float Value);
	void rotateY(float Value);



};
