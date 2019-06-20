// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Projekt_2_RokCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Save_Game.h"
#include "PlayerInventory.h"
#include "SaveGamePlayerComponent.h"
#include "FakeUpGameInstanceBase.h"
#include "Components/SphereComponent.h"

//////////////////////////////////////////////////////////////////////////
// AProjekt_2_RokCharacter

AProjekt_2_RokCharacter::AProjekt_2_RokCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AProjekt_2_RokCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AProjekt_2_RokCharacter::OnOverlapEnd);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjekt_2_RokCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjekt_2_RokCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjekt_2_RokCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjekt_2_RokCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjekt_2_RokCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjekt_2_RokCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjekt_2_RokCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjekt_2_RokCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AProjekt_2_RokCharacter::onPickableInteract);

	PlayerInputComponent->BindAction("QuickSave", IE_Pressed, this, &AProjekt_2_RokCharacter::SaveGame);

	PlayerInputComponent->BindAction("QuickLoad", IE_Pressed, this, &AProjekt_2_RokCharacter::LoadGame);
}

void AProjekt_2_RokCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		if (OtherActor->IsA(APickupableActor::StaticClass()))
		{
			pickactor = Cast<APickupableActor>(OtherActor);
		}
	}
}

void AProjekt_2_RokCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	pickactor = pickactordef;
}

void AProjekt_2_RokCharacter::onPickableInteract()
{
	if (pickactor != pickactordef)
	{
		pickactor->OnInteractPress();
	}
}

APickupableActor * AProjekt_2_RokCharacter::SpawnActor(FString path, FRotator rotator, FVector spawnLocation, int32 Quantity)
{
	UPlayerInventory* PlayerInventoryInstance = Cast<UPlayerInventory>(this->GetComponentByClass(UPlayerInventory::StaticClass()));
	UWorld* world = GetWorld();
	TSubclassOf <class APickupableActor> ToSpawn;

	UClass* blueprintClass = FindObject<UClass>(ANY_PACKAGE, *path);

	ToSpawn = blueprintClass;

	FActorSpawnParameters spawnParams;

	spawnParams.Owner = this;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APickupableActor* InventoryItem = world->SpawnActor<APickupableActor>(ToSpawn, spawnLocation, rotator, spawnParams);

	if (InventoryItem)
	{
		InventoryItem->GoldVal = 0;

		InventoryItem->Quantity = Quantity;

		//	InventoryItem->SetHidden(SaveGameInstance->SaveWorldActorVisibility[i]);

		//	InventoryItem->SetActorHiddenInGame(false);
		return InventoryItem;
	}
	else
	{
		return nullptr;
	}	
}

void AProjekt_2_RokCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjekt_2_RokCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AProjekt_2_RokCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AProjekt_2_RokCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjekt_2_RokCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjekt_2_RokCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		IsMovingForward = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Value = Value * Speed;
		if (IsMovingForward && IsMovingSideways)
		{
			Value = Value * 0.5f;
			AddMovementInput(Direction, Value);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
			return;
		}
		IsMovingForward = false;
		AddMovementInput(Direction, Value);
		//UE_LOG(LogTemp, Warning, TEXT("Direction %s %f"), *Direction.ToString(), Value);
	}
}

void AProjekt_2_RokCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		IsMovingSideways = true;
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction

		Value = Value * Speed;

		
		if (IsMovingForward && IsMovingSideways)
		{
			Value = Value * 0.5f;
			AddMovementInput(Direction, Value);
			return;
		}
		AddMovementInput(Direction, Value);
		IsMovingSideways = false;
	}
}

void AProjekt_2_RokCharacter::SaveGame()
{
	USaveGamePlayerComponent* SaveGameComponent = Cast<USaveGamePlayerComponent>(this->GetComponentByClass(USaveGamePlayerComponent::StaticClass()));

	SaveGameComponent->SaveGame("QuickSave");
}

void AProjekt_2_RokCharacter::LoadGame()
{
	SaveOnUpdateInventory.Broadcast();

	USaveGamePlayerComponent* SaveGameComponent = Cast<USaveGamePlayerComponent>(this->GetComponentByClass(USaveGamePlayerComponent::StaticClass()));

	SaveGameComponent->LoadGame("QuickSave");
}