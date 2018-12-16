// Fill out your copyright notice in the Description page of Project Settings.

#include "robot.h"


// Sets default values
Arobot::Arobot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void Arobot::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetSimulatePhysics(true);
	maxSpeed;
	speed;
	accelerationRate;
	maxSpeedBackward;




}

// Called every frame
void Arobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector forwardDirection = GetActorForwardVector();

	//FVector ForceToAdd = forwardDirection * speed;
	//Mesh->AddForce(ForceToAdd);

	FVector Direction = GetActorForwardVector();
	SetActorRelativeLocation(FVector(GetActorLocation().X + speed * Direction.X, GetActorLocation().Y + speed * Direction.Y,
		GetActorLocation().Z + speed * Direction.Z));

}

// Called to bind functionality to input
void Arobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Accelerate", IE_Pressed, this, &Arobot::Accelerate);
	InputComponent->BindAction("Accelerate", IE_Released, this, &Arobot::Inertion);
	InputComponent->BindAction("Suppress", IE_Pressed, this, &Arobot::Stop);
	InputComponent->BindAction("Suppress", IE_Released, this, &Arobot::Inertion);

	InputComponent->BindAction("Left", IE_Pressed, this, &Arobot::left);
	InputComponent->BindAction("Left", IE_Released, this, &Arobot::stopRotation);
	InputComponent->BindAction("Right", IE_Pressed, this, &Arobot::right);
	InputComponent->BindAction("Right", IE_Released, this, &Arobot::stopRotation);



}

void Arobot::Accelerate()
{
	GetWorld()->GetTimerManager().ClearTimer(stopHandle);
	GetWorld()->GetTimerManager().ClearTimer(inertionHandle);
	GetWorldTimerManager().SetTimer(accelerationHandle, this, &Arobot::increaseSpeed, accelerationRate, true, timeToReact);
}

void Arobot::increaseSpeed()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("acelerate"));
	if (speed < maxSpeed)
	{
		speed += 1.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));
	}
}


void Arobot::Inertion()
{
	GetWorld()->GetTimerManager().ClearTimer(stopHandle);
	GetWorld()->GetTimerManager().ClearTimer(accelerationHandle);
	GetWorldTimerManager().SetTimer(inertionHandle, this, &Arobot::inertionSpeed, inertionRate, true, 0.1f);

}


void Arobot::inertionSpeed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));

	if (speed > 0)
	{
		speed -= 0.2f;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));
	}
	else if (speed < 0)
	{
		speed += 0.2f;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));
	}
}


void Arobot::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(inertionHandle);
	GetWorld()->GetTimerManager().ClearTimer(accelerationHandle);
	GetWorldTimerManager().SetTimer(stopHandle, this, &Arobot::stopSpeed, stopRate, true, timeToReact);
}






void Arobot::stopSpeed()
{
	if (speed > maxSpeedBackward)
	{
		speed -= 1.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), speed));
	}
}

void Arobot::left()
{
	GetWorldTimerManager().SetTimer(leftHandle, this, &Arobot::turnLeft, 0.003f, true, timeToReact);
}

void Arobot::right()
{
	GetWorldTimerManager().SetTimer(rightHandle, this, &Arobot::turnRight, 0.003f, true, timeToReact);
}

void Arobot::turnLeft()
{

	rotation(-0.01f * speed + rotatationAcceleration);
}

void Arobot::turnRight()
{

	rotation(0.01f * speed + rotatationAcceleration);
}

void Arobot::stopRotation()
{
	GetWorld()->GetTimerManager().ClearTimer(leftHandle);
	GetWorld()->GetTimerManager().ClearTimer(rightHandle);
}

void Arobot::rotation(float Value)
{


	FRotator NewRotation = FRotator(0.0f, Value, 0.0f);

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

}









