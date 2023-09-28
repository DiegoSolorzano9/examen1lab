// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Plant.h"


// Sets default values
AZombie::AZombie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Registra la función para la detección de colisiones
	//OnActorBeginOverlap.AddDynamic(this, &AZombie::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ZombieMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ZombieMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	ZombieMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZombieMesh"));
	ZombieMeshComponent->SetStaticMesh(ZombieMesh.Object);
	ZombieMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	ZombieMeshComponent->SetSimulatePhysics(true);
	//ZombieMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ZombieMeshComponent;

	Tags.Add(TEXT("Enemy"));
	Health = 100.0f;
	MovementSpeed = 0.02f;
	bCanMove = false;
}

void AZombie::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	// Verifica si el otro actor es un zombie
	APlant* ActualPlant = Cast<APlant>(OtherActor);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Plant energy: %f"), ActualPlant->Health));

	if (ActualPlant)
	{
		ActualPlant->TakeDamage(DamageGenerates, FDamageEvent(), nullptr, this);

		// Reduce la energía de la planta cuando un zombie está cerca
		// Puedes implementar tu propia lógica para reducir la energía aquí
		// Por ejemplo, disminuir una variable que represente la energía de la planta
		// También puedes programar el tiempo entre las reducciones de energía
	}
}


// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
	//SetLifeSpan(10);
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		Destroy();
	}

	if (bCanMove && !this->IsHidden())
	{
		MoveToTarget(FVector(-800.0f, -600.0f, 160.0f));
	}
}

float AZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Aquí puedes manejar el daño como desees, por ejemplo, actualizando la salud del actor.
	Health -= DamageAmount;

	// Devuelve la cantidad de daño que se aplicó realmente.
	return Health;
}

void AZombie::MoveToTarget(FVector TargetLocation)
{
	FVector Direction = TargetLocation - FVector(-800.0f, 400.0f, 160.0f);
	float DistanceToTarget = FVector::Dist(TargetLocation, FVector(-800.0f, 400.0f, 160.0f));

	// Calcula el desplazamiento en este frame
	float DeltaMove = MovementSpeed * GetWorld()->DeltaTimeSeconds;

	if (DeltaMove > DistanceToTarget)
	{
		// Si el desplazamiento excede la distancia al objetivo, mueve directamente al objetivo
		this->SetActorLocation(TargetLocation);
	}
	else
	{
		// Mueve el objeto en la direcci�n calculada
		this->AddActorWorldOffset(Direction * DeltaMove);
	}

}
