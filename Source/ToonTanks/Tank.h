// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = 1), Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = 1), Category = "Components")
	class UCameraComponent* Camera;	

	void Move(float Value);	
	void Turn(float Value);

	UPROPERTY(EditAnywhere)
	float Speed = 600.f;

	UPROPERTY(EditAnywhere)
	float TurnRate = 200.f;

	APlayerController* TankPlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
