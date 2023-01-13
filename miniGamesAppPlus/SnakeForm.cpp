#include "SnakeForm.h"

struct Vector2
{
	int X, Y;
};

Vector2 direction;
Vector2 positionFruit;
Vector2 gameArea;

//Конструктор игровой формы

miniGamesAppPlus::SnakeForm::SnakeForm(void) 
{
	InitializeComponent();

	//Задаем размеры игровой зоны
	gameArea.X = 500;
	gameArea.Y = 500;
	firstLaunch = true;//первый запуск
	NewGame();//новая игра
}

void miniGamesAppPlus::SnakeForm::GeneratePositionFruit()
{
	//Генерируем позицию фрукта

	Random^ rand = gcnew Random();
	positionFruit.X = rand->Next(50, gameArea.X);
	positionFruit.Y = rand->Next(150, gameArea.Y);

	//Проверка, что фрукт не на змейке
	for (int i = 0; i < score; i++) {
		if (positionFruit.X == Snake[i]->Location.X && positionFruit.Y == Snake[i]->Location.Y)
			GeneratePositionFruit();
	}
	//Преобразование значения, чтобы оно было кратно шагу

	int tempX = positionFruit.X % step;
	positionFruit.X -= tempX;
	int tempY = positionFruit.Y % step;
	positionFruit.Y -= tempY;

	//Даем фрукту позицию

	fruit->Location = Point(positionFruit.X, positionFruit.Y);

	//Добавляем объект на форму

	this->Controls->Add(fruit);
}

void miniGamesAppPlus::SnakeForm::Eating()
{
	//Проверяем позицию головы змеи и фрукта

	if (Snake[0]->Location.X == positionFruit.X && Snake[0]->Location.Y == positionFruit.Y)
	{
		labelScore->Text = "Счет: " + ++score;

		//Добавляем змейке новый сегмент

		Snake[score] = gcnew PictureBox();
		Snake[score]->Location = Point(Snake[score - 1]->Location.X + step * direction.X, Snake[score - 1]->Location.Y + step * direction.Y);
		Snake[score]->BackColor = Color::Red;
		Snake[score]->Width = step;
		Snake[score]->Height = step;
		this->Controls->Add(Snake[score]);
		GeneratePositionFruit();
	}
}

void miniGamesAppPlus::SnakeForm::Movement() 
{
	//Двигаем каждый компонент змейки

	for (int i = score; i >= 1; i--)
	{
		Snake[i]->Location = Snake[i - 1]->Location;
	}
	Snake[0]->Location = Point(Snake[0]->Location.X + step * direction.X, Snake[0]->Location.Y + step * direction.Y);
}

void miniGamesAppPlus::SnakeForm::EatYourself() 
{
	//Проверка каждого сегмента

	for (int i = 1; i < score; i++)
	{
		if (Snake[0]->Location == Snake[i]->Location)
			GameOver();
	}
}

void miniGamesAppPlus::SnakeForm::GameOver()
{
	play = true;
	die = true;
	labelGameOver->Visible = true;
}

void miniGamesAppPlus::SnakeForm::NewGame() 
{
	if (!firstLaunch)
	{
		this->Controls->Remove(fruit);
		for (int i = 0; i <= score; i++)
			this->Controls->Remove(Snake[i]);
		score = 0;
	}
	else
		firstLaunch = false;
	//Инициализируем змейку
	Snake = gcnew array <PictureBox^, 1>(400);
	Snake[0] = gcnew PictureBox();
	Snake[0]->Location = Point(200, 200);
	Snake[0]->BackColor = Color::Green;
	Snake[0]->Width = step;
	Snake[0]->Height = step;
	score = 0;
	this->Controls->Add(Snake[0]);

	//Инициализируем фрукт
	fruit = gcnew PictureBox();
	fruit->Location = Point(200, 200);
	fruit->BackColor = Color::Yellow;
	fruit->Width = step;
	fruit->Height = step;
	GeneratePositionFruit();

	//Задаем интервал обновления для таймера и запускаем его
	timer->Interval = updateInterval;
	timer->Start();

	//Задаем направление на запуске
	direction.X = 1;
	direction.Y = 0;

	//Можно играть
	play = true;
	die = false;
	labelScore->Text = "Счет: 0";

	//Скрываем ненужные компоненты на форме
	labelGameOver->Visible = false;
	groupBoxSettings->Visible = false;
}

void miniGamesAppPlus::SnakeForm::CheckBorders()
{
	if (Snake[0]->Location.X >= RightBorder->Location.X || Snake[0]->Location.X <= LeftBorder->Location.X)
		GameOver();
	if (Snake[0]->Location.Y <= UpperBorder->Location.Y || Snake[0]->Location.Y >= LowerBorder->Location.Y)
		GameOver();
}

System::Void miniGamesAppPlus::SnakeForm::buttonApplySpeed_Click(System::Object^ sender, System::EventArgs^ e)
{
	updateInterval = Convert::ToSingle(numericUpDownSpeedSetting->Value);
	timer->Interval = updateInterval;
	buttonApplySpeed->Enabled = false;
	numericUpDownSpeedSetting->Enabled = false;
	groupBoxSettings->Visible = false;
	//Запускаем игру
	play = true;
	timer->Start();
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::вГлавноеМенюToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Hide();
}

System::Void miniGamesAppPlus::SnakeForm::информацияОИгреToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Правила игры: \n1. Для управления использовать стрелки\n2. Ешьте фрукты для увелечения счета и змейки\n3. Нельзя есть себя и врезаться в стенки", "Информация о игре");
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::новаяИграToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	NewGame();
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::паузапродолжитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (play)
		play = false;
	else 
	{
		play = true;
		timer->Start();
	}
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::настройкиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (groupBoxSettings->Visible == false)
	{
		play = false;
		buttonApplySpeed->Enabled = true;
		numericUpDownSpeedSetting->Enabled = true;
		groupBoxSettings->Visible = true;
	}
	else
	{
		play = true;
		buttonApplySpeed->Enabled = false;
		numericUpDownSpeedSetting->Enabled = false;
		groupBoxSettings->Visible = false;
	}
}

System::Void miniGamesAppPlus::SnakeForm::GameForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	//Считываем нажатую клавишу
	if (e->KeyCode.ToString() == "Right") 
	{
		direction.X = 1;
		direction.Y = 0;
	}
	if (e->KeyCode.ToString() == "Left")
	{
		direction.X = -1;
		direction.Y = 0;
	}
	if (e->KeyCode.ToString() == "Up") 
	{
		direction.X = 0;
		direction.Y = -1;
	}
	if (e->KeyCode.ToString() == "Down")
	{
		direction.X = 0;
		direction.Y = 1;
	}
	return System::Void();
}

void miniGamesAppPlus::SnakeForm::GameForm_Update(Object^ object, EventArgs^ e)
{
	if (!die && play)
	{
		Movement();
		Eating();
		EatYourself();
		CheckBorders();
	}
	else if (die && play)
	{
		timer->Stop();
		MessageBox::Show("Игра окончена!", "Внимание!");
	}
	else if (!die && !play) 
	{
		timer->Stop();
		MessageBox::Show("Игра приостановлена", "Внимание!");
	}
}