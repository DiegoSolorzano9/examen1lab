// PlantaLanzadoraLoca.cpp

#include "LanzadoraLoca.h"

// Include adicional para obtener acceso a las clases de proyectiles si es necesario
#include "PVZ_USFX_LAB02Projectile.h" // Asumiendo que tienes una clase Proyectil

// Sets default values
ALanzadoraLoca::ALanzadoraLoca()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALanzadoraLoca::BeginPlay()
{
    Super::BeginPlay();
    float InitialDelay = FMath::RandRange(1.0f, 3.0f); // Retraso inicial aleatorio
    FireRate = FMath::RandRange(2.0f, 5.0f); // Utiliza el miembro de clase FireRate
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ALanzadoraLoca::FireRandomProjectile, FireRate, true, InitialDelay);
}


// Called every frame
void ALanzadoraLoca::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Función para disparar proyectiles aleatorios
void ALanzadoraLoca::FireRandomProjectile()
{
    // Generar una dirección de disparo aleatoria
    FVector LaunchDirection = FMath::VRand();

    // Ubicación de origen del disparo (puedes ajustarlo según tus necesidades)
    FVector SpawnLocation = GetActorLocation();

    // Spawn y lanzamiento del proyectil (debes tener una clase Proyectil)
    APVZ_USFX_LAB02Projectile* NewProjectile = GetWorld()->SpawnActor<APVZ_USFX_LAB02Projectile>(APVZ_USFX_LAB02Projectile::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
    if (NewProjectile)
    {
        NewProjectile->Launch(LaunchDirection);
    }
}
