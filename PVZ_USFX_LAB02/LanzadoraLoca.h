// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "LanzadoraLoca.generated.h"

/**
 * 
 *//
UCLASS()
class PVZ_USFX_LAB02_API ALanzadoraLoca : public APlant
{
	GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    ALanzadoraLoca();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Timer para controlar la frecuencia de disparo
    FTimerHandle FireTimerHandle;

    // Función para disparar proyectiles aleatorios
    void FireRandomProjectile();
};
