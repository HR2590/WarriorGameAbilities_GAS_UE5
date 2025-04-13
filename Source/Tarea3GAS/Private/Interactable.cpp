// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "CoreAttributeSet.h"
#include "GASDataComponent.h"
#include "UTHUB_ASC.h"
#include "Components/BoxComponent.h"


// Sets default values
AInteractable::AInteractable()
{
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CoreAttributeSet=CreateDefaultSubobject<UCoreAttributeSet>(TEXT("CoreAttributes"));
	GASDataComponent=CreateDefaultSubobject<UGASDataComponent>(TEXT("GASData"));
	ASC=CreateDefaultSubobject<UUTHUB_ASC>(TEXT("GAS Component"));
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxComponent->SetupAttachment(Mesh);
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	
	
}







