// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/LyUserWidget.h"


void ULyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
