// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController()); 
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FHitResult HitResult;
    if (TankPlayerController)
    {
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }      
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

void ATank::Move(float Value)
{
    FVector DeltaLocation(0.f);
    double DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = Value * DeltaSeconds * Speed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation(0.f);
    double DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = Value * DeltaSeconds * TurnRate;
    AddActorLocalRotation(DeltaRotation, true);
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}





