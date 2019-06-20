// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableActor.generated.h"

class APickupableActor;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupAddedDelegate, APickupableActor*, Pickup);

class USphereComponent;

UCLASS()
class PROJEKT_2_ROK_API APickupableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	USceneComponent* MoveScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	USphereComponent* SphereComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bIsHiddenInGameW = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FPickupAddedDelegate pickupAddedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FPickupAddedDelegate pickupRemovedDelegate;

	UFUNCTION(BlueprintCallable)
	void OnInteractPress();

	UFUNCTION(BlueprintCallable)
	void SetHidden(bool bactorhidden);

	UFUNCTION(BlueprintCallable)
	bool GetIsHidden();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FString NameShow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 Quantity;

	UPROPERTY(BlueprintReadOnly)
	FString QuantityFString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FString ItemBuyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 GoldVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubclassOf<UUserWidget> PressEWidget;

	UPROPERTY()
	UUserWidget* PressEWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool useAnimation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool useAura = false;

	UPROPERTY()
	FQuat randomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float animationTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UCurveFloat* curve;
};
