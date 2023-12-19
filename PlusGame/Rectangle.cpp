#include "Rectangle.h"

int Rectangle::GetRight()
{
	return X + Width;
}

int Rectangle::GetLeft()
{
	return X;
}

int Rectangle::GetTop()
{
	return Y;
}

int Rectangle::GetBottom()
{
	return Y + Height;
}

bool Rectangle::IsEmpty()
{
	return ((((this->Width == 0) && (this->Height == 0)) && (this->X == 0)) && (this->Y == 0));;
}

Point Rectangle::GetLocation()
{
	return Point(X, Y);
}

Point Rectangle::GetSize()
{
	return Point(Width, Height);
}

Point Rectangle::GetCenter()
{
	return Point(this->X + (this->Width / 2), this->Y + (this->Height / 2));
}

Rectangle::Rectangle(Point position, Point size)
{
	X = position.X;
	Y = position.Y;
	Width = size.X;
	Height = size.Y;
}

/// <summary>
/// Gets whether or not the provided coordinates lie within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="x">The x coordinate of the point to check for containment.</param>
/// <param name="y">The y coordinate of the point to check for containment.</param>
/// <returns><c>true</c> if the provided coordinates lie inside this <see cref="Rectangle"/>; <c>false</c> otherwise.</returns>
bool Rectangle::Contains(int x, int y)
{
	return ((((this->X <= x) && (x < (this->X + this->Width))) && (this->Y <= y)) && (y < (this->Y + this->Height)));
}

/// <summary>   
/// Gets whether or not the provided coordinates lie within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="x">The x coordinate of the point to check for containment.</param>
/// <param name="y">The y coordinate of the point to check for containment.</param>
/// <returns><c>true</c> if the provided coordinates lie inside this <see cref="Rectangle"/>; <c>false</c> otherwise.</returns>
bool Rectangle::Contains(float x, float y)
{
	return ((((this->X <= x) && (x < (this->X + this->Width))) && (this->Y <= y)) && (y < (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Point"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The coordinates to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <returns><c>true</c> if the provided <see cref="Point"/> lies inside this <see cref="Rectangle"/>; <c>false</c> otherwise.</returns>
bool Rectangle::Contains(Point value)
{
	return ((((this->X <= value.X) && (value.X < (this->X + this->Width))) && (this->Y <= value.Y)) && (value.Y < (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Point"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The coordinates to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <param name="result"><c>true</c> if the provided <see cref="Point"/> lies inside this <see cref="Rectangle"/>; <c>false</c> otherwise. As an output parameter.</param>
void Rectangle::Contains(Point& value, bool& result)
{
	result = ((((this->X <= value.X) && (value.X < (this->X + this->Width))) && (this->Y <= value.Y)) && (value.Y < (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Vector2"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The coordinates to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <returns><c>true</c> if the provided <see cref="Vector2"/> lies inside this <see cref="Rectangle"/>; <c>false</c> otherwise.</returns>
bool Rectangle::Contains(Vector2& value)
{
	return ((((this->X <= value.X) && (value.X < (this->X + this->Width))) && (this->Y <= value.Y)) && (value.Y < (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Vector2"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The coordinates to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <param name="result"><c>true</c> if the provided <see cref="Vector2"/> lies inside this <see cref="Rectangle"/>; <c>false</c> otherwise. As an output parameter.</param>
void Rectangle::Contains(Vector2& value, bool& result)
{
	result = ((((this->X <= value.X) && (value.X < (this->X + this->Width))) && (this->Y <= value.Y)) && (value.Y < (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Rectangle"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The <see cref="Rectangle"/> to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <returns><c>true</c> if the provided <see cref="Rectangle"/>'s bounds lie entirely inside this <see cref="Rectangle"/>; <c>false</c> otherwise.</returns>
bool Rectangle::Contains(Rectangle& value)
{
	return ((((this->X <= value.X) && ((value.X + value.Width) <= (this->X + this->Width))) && (this->Y <= value.Y)) && ((value.Y + value.Height) <= (this->Y + this->Height)));
}

/// <summary>
/// Gets whether or not the provided <see cref="Rectangle"/> lies within the bounds of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="value">The <see cref="Rectangle"/> to check for inclusion in this <see cref="Rectangle"/>.</param>
/// <param name="result"><c>true</c> if the provided <see cref="Rectangle"/>'s bounds lie entirely inside this <see cref="Rectangle"/>; <c>false</c> otherwise. As an output parameter.</param>
void Rectangle::Contains(Rectangle& value, bool& result)
{
	result = ((((this->X <= value.X) && ((value.X + value.Width) <= (this->X + this->Width))) && (this->Y <= value.Y)) && ((value.Y + value.Height) <= (this->Y + this->Height)));
}

/// <summary>
/// Adjusts the edges of this <see cref="Rectangle"/> by specified horizontal and vertical amounts. 
/// </summary>
/// <param name="horizontalAmount">Value to adjust the left and right edges.</param>
/// <param name="verticalAmount">Value to adjust the top and bottom edges.</param>
void Rectangle::Inflate(int horizontalAmount, int verticalAmount)
{
	X -= horizontalAmount;
	Y -= verticalAmount;
	Width += horizontalAmount * 2;
	Height += verticalAmount * 2;
}

/// <summary>
/// Adjusts the edges of this <see cref="Rectangle"/> by specified horizontal and vertical amounts. 
/// </summary>
/// <param name="horizontalAmount">Value to adjust the left and right edges.</param>
/// <param name="verticalAmount">Value to adjust the top and bottom edges.</param>
void Rectangle::Inflate(float horizontalAmount, float verticalAmount)
{
	X -= (int)horizontalAmount;
	Y -= (int)verticalAmount;
	Width += (int)horizontalAmount * 2;
	Height += (int)verticalAmount * 2;
}

/// <summary>
/// Gets whether or not the other <see cref="Rectangle"/> intersects with this rectangle.
/// </summary>
/// <param name="value">The other rectangle for testing.</param>
/// <returns><c>true</c> if other <see cref="Rectangle"/> intersects with this rectangle; <c>false</c> otherwise.</returns>
bool Rectangle::Intersects(Rectangle& value)
{
	return value.GetLeft() < GetRight() &&
		GetLeft() < value.GetRight() &&
		value.GetTop() < GetBottom() &&
		GetTop() < value.GetBottom();
}


/// <summary>
/// Gets whether or not the other <see cref="Rectangle"/> intersects with this rectangle.
/// </summary>
/// <param name="value">The other rectangle for testing.</param>
/// <param name="result"><c>true</c> if other <see cref="Rectangle"/> intersects with this rectangle; <c>false</c> otherwise. As an output parameter.</param>
void Rectangle::Intersects(Rectangle& value, bool result)
{
	result = value.GetLeft() < GetRight() &&
		GetLeft() < value.GetRight() &&
		value.GetTop() < GetBottom() &&
		GetTop() < value.GetBottom();
}

/// <summary>
/// Creates a  <see cref="Rectangle"/> that contains overlapping region of two other rectangles.
/// </summary>
/// <param name="value1">The first <see cref="Rectangle"/>.</param>
/// <param name="value2">The second <see cref="Rectangle"/>.</param>
/// <returns>Overlapping region of the two rectangles.</returns>
Rectangle Rectangle::Intersect(Rectangle& value1, Rectangle& value2)
{
	Rectangle rectangle;
	Intersect(value1, value2, rectangle);
	return rectangle;
}

/// <summary>
/// Creates a  <see cref="Rectangle"/> that contains overlapping region of two other rectangles.
/// </summary>
/// <param name="value1">The first <see cref="Rectangle"/>.</param>
/// <param name="value2">The second <see cref="Rectangle"/>.</param>
/// <param name="result">Overlapping region of the two rectangles as an output parameter.</param>
void Rectangle::Intersect(Rectangle& value1, Rectangle& value2, Rectangle& result)
{
	if (value1.Intersects(value2))
	{
		int right_side = MathHelper::Min(value1.X + value1.Width, value2.X + value2.Width);
		int left_side = MathHelper::Max(value1.X, value2.X);
		int top_side = MathHelper::Max(value1.Y, value2.Y);
		int bottom_side = MathHelper::Min(value1.Y + value1.Height, value2.Y + value2.Height);
		result = Rectangle(left_side, top_side, right_side - left_side, bottom_side - top_side);
	}
	else
	{
		result = Rectangle(0, 0, 0, 0);
	}
}

/// <summary>
/// Changes the <see cref="Location"/> of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="offsetX">The x coordinate to add to this <see cref="Rectangle"/>.</param>
/// <param name="offsetY">The y coordinate to add to this <see cref="Rectangle"/>.</param>
void Rectangle::Offset(int offsetX, int offsetY)
{
	X += offsetX;
	Y += offsetY;
}

/// <summary>
/// Changes the <see cref="Location"/> of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="offsetX">The x coordinate to add to this <see cref="Rectangle"/>.</param>
/// <param name="offsetY">The y coordinate to add to this <see cref="Rectangle"/>.</param>
void Rectangle::Offset(float offsetX, float offsetY)
{
	X += (int)offsetX;
	Y += (int)offsetY;
}

/// <summary>
/// Changes the <see cref="Location"/> of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="amount">The x and y components to add to this <see cref="Rectangle"/>.</param>
void Rectangle::Offset(Point& amount)
{
	X += amount.X;
	Y += amount.Y;
}

/// <summary>
/// Changes the <see cref="Location"/> of this <see cref="Rectangle"/>.
/// </summary>
/// <param name="amount">The x and y components to add to this <see cref="Rectangle"/>.</param>
void Rectangle::Offset(Vector2& amount)
{
	X += (int)amount.X;
	Y += (int)amount.Y;
}

/// <summary>
/// Creates a new <see cref="Rectangle"/> that completely contains two other rectangles.
/// </summary>
/// <param name="value1">The first <see cref="Rectangle"/>.</param>
/// <param name="value2">The second <see cref="Rectangle"/>.</param>
/// <returns>The union of the two rectangles.</returns>
Rectangle Rectangle::Union(Rectangle& value1, Rectangle& value2)
{
	int x = MathHelper::Min(value1.X, value2.X);
	int y = MathHelper::Min(value1.Y, value2.Y);
	return  Rectangle(x, y,
		MathHelper::Max(value1.GetRight(), value2.GetRight()) - x,
		MathHelper::Max(value1.GetBottom(), value2.GetBottom()) - y);
}

/// <summary>
/// Creates a new <see cref="Rectangle"/> that completely contains two other rectangles.
/// </summary>
/// <param name="value1">The first <see cref="Rectangle"/>.</param>
/// <param name="value2">The second <see cref="Rectangle"/>.</param>
/// <param name="result">The union of the two rectangles as an output parameter.</param>
void Rectangle::Union(Rectangle& value1, Rectangle& value2, Rectangle& result)
{
	result.X = MathHelper::Min(value1.X, value2.X);
	result.Y = MathHelper::Min(value1.Y, value2.Y);
	result.Width = MathHelper::Max(value1.GetRight(), value2.GetRight()) - result.X;
	result.Height = MathHelper::Max(value1.GetBottom(), value2.GetBottom()) - result.Y;
}