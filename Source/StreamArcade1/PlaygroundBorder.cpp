// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundBorder.h"
#include "Components/BoxComponent.h"
#include "MyPawn.h"


APlaygroundBorder::APlaygroundBorder()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    SetRootComponent(Trigger);

    Trigger->SetCollisionProfileName("OverlapAll");
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);
    
    if (!OtherActor) return;
    if (Cast<AMyPawn>(OtherActor)) return;

    OtherActor->Destroy();
}
