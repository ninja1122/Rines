// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueNPC.h"


// Sets default values
ADialogueNPC::ADialogueNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = MeshComp;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADialogueNPC::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADialogueNPC::OnOverlapEnd);
	BoxComponent->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ADialogueNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ADialogueNPC::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	//auto player = GetWorld()->GetFirstPlayerController();
	//EnableInput(player);
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void ADialogueNPC::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	auto player = GetWorld()->GetFirstPlayerController();
	DisableInput(player);
	
}

void ADialogueNPC::OnInteractPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));

}

// Called every frame
void ADialogueNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

