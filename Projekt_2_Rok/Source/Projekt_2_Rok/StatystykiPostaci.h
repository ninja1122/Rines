// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatystykiPostaci.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_2_ROK_API UStatystykiPostaci : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatystykiPostaci();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int levelPostaci = 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int doswiadczenie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int doswiadczenieNaKoloejnyPoziom = 200;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int zdrowie = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int maxZdrowie = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int punktyRozwoju = 0;


	UFUNCTION(BlueprintCallable, Category = Statystyki)
		void NowyPoziomPostaci();

	UFUNCTION(BlueprintCallable, Category = Statystyki)
		void DodajDoswiadczenie(int32 ExpQuantity);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int poziomKulaOgnia = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int obrazeniaKulaOgnia;

	UFUNCTION(BlueprintCallable, Category = Statystyki)
		void NowyPoziomKulaOgnia();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int poziomKolce = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int obrazeniaKolce = 10;

	UFUNCTION(BlueprintCallable, Category = Statystyki)
		void NowyPoziomKolce();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int poziomFalaWody = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int obrazeniaFalaWody = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statystyki)
		int leczenieFalaWody = 10;

	UFUNCTION(BlueprintCallable, Category = Statystyki)
		void NowyPoziomFalaWody();
	
};
