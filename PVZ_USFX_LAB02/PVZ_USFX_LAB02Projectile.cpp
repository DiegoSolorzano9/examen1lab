#include "PVZ_USFX_LAB02Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "LanzadoraLoca.h"

APVZ_USFX_LAB02Projectile::APVZ_USFX_LAB02Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Genera una dirección de lanzamiento aleatoria

	// Establece la velocidad del proyectil en función de la dirección y la velocidad inicial

	// Programa la destrucción del proyectil después de cierto tiempo (si es necesario)
	SetLifeSpan(InitialLifeSpan);
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &APVZ_USFX_LAB02Projectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 250.0f;
	ProjectileMovement->MaxSpeed = 250.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	MaxDistance = 1000.0f;
	//InitialLifeSpan = 10.0f;
	InitialLifeSpan = MaxDistance / ProjectileMovement->InitialSpeed;
	Damage = 10.0f;

	// No necesitas declarar 'LaunchDirection' nuevamente aquí
	// Calcula la velocidad inicial del proyectil (puedes ajustarla según tus necesidades)
	// FVector LaunchDirection = FVector::ForwardVector; // Por ejemplo, avanza hacia adelante
	// Velocity = LaunchDirection * InitialSpeed;

	// Programa la destrucción del proyectil después de cierto tiempo (si es necesario)
	// SetLifeSpan(InitialLifeSpan);
}

void APVZ_USFX_LAB02Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			OtherActor->TakeDamage(Damage, FDamageEvent(), nullptr, this);
		}
		Destroy();
	}
}

void APVZ_USFX_LAB02Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation);
	// Actualiza la posición del proyectil basado en su velocidad
}
void APVZ_USFX_LAB02Projectile::Launch(const FVector& LaunchDirection)
{
	// Lógica para lanzar el proyectil en la dirección especificada
	// ...
}
