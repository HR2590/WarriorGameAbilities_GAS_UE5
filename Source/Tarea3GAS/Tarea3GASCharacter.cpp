// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tarea3GASCharacter.h"
#include "UTHUB_ASC.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATarea3GASCharacter::ATarea3GASCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CoreAttributeSet=CreateDefaultSubobject<UCoreAttributeSet>(TEXT("CoreAttributes"));
	GASDataComponent=CreateDefaultSubobject<UGASDataComponent>(TEXT("GASData"));
	ASC=CreateDefaultSubobject<UUTHUB_ASC>(TEXT("GAS Component"));


}

void ATarea3GASCharacter::OnHealthChanged(float OldHealth, float NewHealth)
{
	
	
	if (FMath::IsNearlyZero(NewHealth)||FMath::IsNegativeOrNegativeZero(NewHealth))
	{
		
	
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			
			MoveComp->StopMovementImmediately();
			MoveComp->DisableMovement();
			MoveComp->Deactivate();
			StopJumping();

		}

		if(ASC)
		{
			ASC->CancelAllAbilities();
			ASC->ClearAllAbilities();
			ASC->ClearAllAbilitiesWithInputID();
		}
		
		
		for (auto Delegate :CoreAttributeSet->OnAttributeChanged)
		{
			Delegate.Value.RemoveAll(this);
		}
		
		Destroy();
	}
		
	
}



void ATarea3GASCharacter::OnSpeedChanged(float OldSpeed, float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}


void ATarea3GASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(ensure(CoreAttributeSet)&&!CoreAttributeSet->OnAttributeChanged.IsEmpty())
	{
	
		if(auto Attribute=CoreAttributeSet->OnAttributeChanged.Find(CoreAttributeSet->GetHealthAttribute()))
		{
			Attribute->AddDynamic(this,&ATarea3GASCharacter::OnHealthChanged);
		}
		if(auto Attribute=CoreAttributeSet->OnAttributeChanged.Find(CoreAttributeSet->GetSpeedAttribute()))
		{
			Attribute->AddDynamic(this,&ATarea3GASCharacter::OnSpeedChanged);
		}
		
	}
	

}














