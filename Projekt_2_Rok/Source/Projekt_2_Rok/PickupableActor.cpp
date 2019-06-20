// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Projekt_2_RokCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerInventory.h"


// Sets default values
APickupableActor::APickupableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionProfileName(TEXT("PlayerInteractable"));
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickupableActor::OnOverlapBegin);
	//SphereComp->OnComponentEndOverlap.AddDynamic(this, &APickupableActor::OnOverlapEnd);
	RootComponent = SphereComp;

	MoveScene = CreateDefaultSubobject<USceneComponent>(TEXT("MoveScene"));
	MoveScene->SetupAttachment(SphereComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(MoveScene);
}

// Called when the game starts or when spawned
void APickupableActor::BeginPlay()
{
	Super::BeginPlay();
	
	PressEWidgetInstance = CreateWidget<UUserWidget>(GetGameInstance(), PressEWidget);

	FString ItemImagePath = "Texture2D'/Game/Blueprints/Inventory/";
	ItemImagePath.Append(this->Name);
	ItemImagePath.Append("_2d");
	ItemImagePath.Append(".");
	ItemImagePath.Append(this->Name);
	ItemImagePath.Append("_2d");
	ItemImagePath.Append("'");

	UTexture2D * ItemImagee = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ItemImagePath));

	this->ItemImage = ItemImagee;
	
	randomRotation = FQuat(FRotator(0.f, 180.f, 0.f));
}

// Called every frame
void APickupableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(useAnimation) {
		animationTime += GetWorld()->DeltaTimeSeconds;
		animationTime = FMath::Clamp(animationTime, 0.f, 1.f);

		float currentScale = animationTime;
		if(curve)
			currentScale = curve->GetFloatValue(animationTime);

		auto transform = MoveScene->GetRelativeTransform();
		transform.SetLocation(FVector(0.f, 0.f, FMath::Sin(GetWorld()->UnpausedTimeSeconds) * 50.f));

		auto currentRotation = FQuat::Slerp(FQuat::Identity, randomRotation, GetWorld()->DeltaTimeSeconds * 0.1f);
		transform.SetRotation(currentRotation * transform.GetRotation());
		transform.SetScale3D(FVector(currentScale));
		MoveScene->SetRelativeTransform(transform);
	}
}

void APickupableActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == Player)
	{
		PressEWidgetInstance->AddToViewport();
	}	
}

void APickupableActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == Player)
	{
		PressEWidgetInstance->RemoveFromViewport();
		PressEWidgetInstance->RemoveFromParent();
	}
}

void APickupableActor::OnInteractPress()
{
	AProjekt_2_RokCharacter* player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	UPlayerInventory* playerinventory = Cast<UPlayerInventory>(player->GetComponentByClass(UPlayerInventory::StaticClass()));

	if (player)
	{
		if (playerinventory)
		{
			playerinventory->AddToInventory(this);
			this->SetHidden(true);
		}
	}
}

void APickupableActor::SetHidden(bool bactorhidden)
{
	this->SetActorEnableCollision(!bactorhidden);
	this->SetActorHiddenInGame(bactorhidden);
	bIsHiddenInGameW = bactorhidden;
}

bool APickupableActor::GetIsHidden()
{
	return bIsHiddenInGameW;
}
