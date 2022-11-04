// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "PlayerCharacter.h"


AMainPlayerController::AMainPlayerController()
{

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<APlayerCharacter>(GetPawn());
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis(TEXT("Move Forward"), this, &AMainPlayerController::CallMoveForwards);
	InputComponent->BindAxis(TEXT("Strafe"), this, &AMainPlayerController::CallStrafe);
	InputComponent->BindAxis(TEXT("Turn"), this, &AMainPlayerController::CallTurn);
	InputComponent->BindAxis(TEXT("Look Up"), this, &AMainPlayerController::CallLookUp);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMainPlayerController::CallJump);
	InputComponent->BindAction(TEXT("BuildMode"), IE_Pressed, this, &AMainPlayerController::SpawnDrone);
}

void AMainPlayerController::CallMoveForwards(float AxisAmount)
{
	if (Character)
	{

		Character->MoveForwards(AxisAmount);
	}
	if (Drone)
	{
		Drone->MoveForwards(AxisAmount);
	}
}

//Allows the player to move the character left and right
void AMainPlayerController::CallStrafe(float AxisAmount)
{
	if (Character)
	{
		Character->Strafe(AxisAmount);
	}
	if (Drone)
	{
		Drone->Strafe(AxisAmount);
	}
}

//Allows the player to rotate the character up and down
void AMainPlayerController::CallLookUp(float AxisAmount)
{
	if (Character)
	{
		Character->LookUp(AxisAmount);
	}
	if (Drone)
	{
		Drone->LookUp(AxisAmount);
	}
}

//Allows the player to rotate the character left and right
void AMainPlayerController::CallTurn(float AxisAmount)
{
	if (Character)
	{
		Character->Turn(AxisAmount);
	}
	if (Drone)
	{
		Drone->Turn(AxisAmount);
	}
}

void AMainPlayerController::CallJump()
{
	if (Character)
	{
		Character->Jump();
	}
}

void AMainPlayerController::SpawnDrone()
{

	//Check if the drone doesn't exist so that we can correctly spawn it 
	if (!Drone)
	{

		//Current spawn parameters for the drone
		FVector SpawnVector = Character->GetActorLocation() + FVector{0.0f, 10.0f, 0.0f};

		//Spawn the drone 
		Drone = GetWorld()->SpawnActor<ADroneCharacter>(DronePawn, SpawnVector, FRotator(0.0f, 0.0f, 0.0f));

		//Check if the Drone was correctly spawned and then possess the new drone
		if (Drone)
		{
			UnPossess();
			Possess(Drone);
		}		
	}

	//Check if we are in build mode and then Possess the player's character while destroying the Drone actor that was palced in the world
	if (BuildMode)
	{

		UnPossess();
		if(Character)
			Possess(Character);

		if(Drone)
			Drone->Destroy();

		Drone = nullptr;
	}
	
	BuildMode = !BuildMode;
}

