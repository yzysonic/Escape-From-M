#include "UIElement.h"

UIElement::UIElement(int x, int y) : NumberUI(3, x, y, "number", "ui_element_title")
{
	SetOffset(5, -5);
	SetNumberScale(0.8f);
	SetNumberSpace(29);
}
