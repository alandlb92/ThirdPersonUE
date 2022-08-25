// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InteractableBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerPawn.h"
#include "../ThirdPerson_SScreenGameModeBase.h" 
#include "Managers/InteractableManager.h"
#include "Player/PlayerHUD.h"


// Sets default values
AInteractableBase::AInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_sceneComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	_sceneComponent->AddWorldRotation(FRotator(0, 0, 0));
	_sceneComponent->SetupAttachment(RootComponent);
	_sceneComponent->SetRelativeLocation(FVector(0, 0, 0));

	_mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->AddWorldRotation(FRotator(0, 0, 0));
	_mesh->SetupAttachment(_sceneComponent);
	_mesh->SetRelativeLocation(FVector(0, 0, 0));

	_interactArea = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("Interactable Area"));
	_interactArea->AddWorldRotation(FRotator(0, 0, 0));
	_interactArea->SetupAttachment(_sceneComponent);
	_interactArea->SetRelativeLocation(FVector(0, 0, 0));

	_widget3D = CreateAbstractDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	_widget3D->AddWorldRotation(FRotator(0, 0, 0));
	_widget3D->SetupAttachment(_sceneComponent);
	_widget3D->SetRelativeLocation(FVector(0, 0, 0));
	_widget3D->SetUsingAbsoluteRotation(true);

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	_interactArea->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::OnTriggerOverlapBegin);
	_interactArea->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnTriggerOverlapEnd);
	_gameMode = Cast<AThirdPerson_SScreenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	_gameMode->GetInteractableManager()->Register(this);
}


void AInteractableBase::Destroyed()
{
	Super::Destroyed();
	if (_gameMode && _gameMode->GetInteractableManager())
		_gameMode->GetInteractableManager()->Unregister(this);
}


// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBase::EnableUI()
{
	_widget3D->SetVisibility(true);
}

void AInteractableBase::DisableUI()
{
	_widget3D->SetVisibility(false);
}

void AInteractableBase::Interact(int playerId)
{
}

void AInteractableBase::Desinteract(int playerId)
{
}


void AInteractableBase::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playersInteractingCount++;
	_widget3D->SetVisibility(false);
	DisableUI();

	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);
	if (Player)
		Player->SetCanInteractWith(this);
}

void AInteractableBase::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnTriggerOverlapEnd"));
		playersInteractingCount--;
		if (playersInteractingCount <= 0)
			EnableUI();
		Player->SetCleanInteractable();
	}
}