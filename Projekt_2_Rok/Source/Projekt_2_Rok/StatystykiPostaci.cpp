// Fill out your copyright notice in the Description page of Project Settings.

#include "StatystykiPostaci.h"


// Sets default values for this component's properties
UStatystykiPostaci::UStatystykiPostaci()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatystykiPostaci::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatystykiPostaci::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}




void UStatystykiPostaci::NowyPoziomPostaci()
{
	if (doswiadczenie >= doswiadczenieNaKoloejnyPoziom)
	{
		doswiadczenieNaKoloejnyPoziom = doswiadczenieNaKoloejnyPoziom + (doswiadczenieNaKoloejnyPoziom * 1.5);
		maxZdrowie = maxZdrowie + (maxZdrowie * 0.25);
		zdrowie = maxZdrowie;
		levelPostaci++;
		punktyRozwoju++;
	}
}

void UStatystykiPostaci::DodajDoswiadczenie(int32 ExpQuantity)
{
	doswiadczenie += ExpQuantity;
	NowyPoziomPostaci();
}


void UStatystykiPostaci::NowyPoziomKulaOgnia()
{
	this->obrazeniaKulaOgnia = this->obrazeniaKulaOgnia + (this->obrazeniaKulaOgnia * 0.5);
}


void UStatystykiPostaci::NowyPoziomKolce()
{
	obrazeniaKolce = obrazeniaKolce + (obrazeniaKolce * 0.5);
}

void UStatystykiPostaci::NowyPoziomFalaWody()
{
	obrazeniaFalaWody = obrazeniaFalaWody + (obrazeniaFalaWody * 0.5);
	leczenieFalaWody = leczenieFalaWody + (leczenieFalaWody * 0.5);
}