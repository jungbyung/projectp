#include "UIManager.h"

void CUIManager::AddWidget(const FString& Name, UBaseUserWidget* Widget)
{
	if (widgetMap.Contains(Name))
		return;

	widgetMap.Add(Name, Widget);
}

void CUIManager::DeleteWidget(const FString& Name)
{
	if (!widgetMap.Contains(Name)) return;

	widgetMap.Remove(Name);
}

//UBaseUserWidget* CUIManager::FindWidget(const FString& Name)
//{
//	return widgetMap.FindRef(Name);
//}
