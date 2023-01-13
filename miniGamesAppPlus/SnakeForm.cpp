#include "SnakeForm.h"

struct Vector2
{
	int X, Y;
};

Vector2 direction;
Vector2 positionFruit;
Vector2 gameArea;

//����������� ������� �����

miniGamesAppPlus::SnakeForm::SnakeForm(void) 
{
	InitializeComponent();

	//������ ������� ������� ����
	gameArea.X = 500;
	gameArea.Y = 500;
	firstLaunch = true;//������ ������
	NewGame();//����� ����
}

void miniGamesAppPlus::SnakeForm::GeneratePositionFruit()
{
	//���������� ������� ������

	Random^ rand = gcnew Random();
	positionFruit.X = rand->Next(50, gameArea.X);
	positionFruit.Y = rand->Next(150, gameArea.Y);

	//��������, ��� ����� �� �� ������
	for (int i = 0; i < score; i++) {
		if (positionFruit.X == Snake[i]->Location.X && positionFruit.Y == Snake[i]->Location.Y)
			GeneratePositionFruit();
	}
	//�������������� ��������, ����� ��� ���� ������ ����

	int tempX = positionFruit.X % step;
	positionFruit.X -= tempX;
	int tempY = positionFruit.Y % step;
	positionFruit.Y -= tempY;

	//���� ������ �������

	fruit->Location = Point(positionFruit.X, positionFruit.Y);

	//��������� ������ �� �����

	this->Controls->Add(fruit);
}

void miniGamesAppPlus::SnakeForm::Eating()
{
	//��������� ������� ������ ���� � ������

	if (Snake[0]->Location.X == positionFruit.X && Snake[0]->Location.Y == positionFruit.Y)
	{
		labelScore->Text = "����: " + ++score;

		//��������� ������ ����� �������

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
	//������� ������ ��������� ������

	for (int i = score; i >= 1; i--)
	{
		Snake[i]->Location = Snake[i - 1]->Location;
	}
	Snake[0]->Location = Point(Snake[0]->Location.X + step * direction.X, Snake[0]->Location.Y + step * direction.Y);
}

void miniGamesAppPlus::SnakeForm::EatYourself() 
{
	//�������� ������� ��������

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
	//�������������� ������
	Snake = gcnew array <PictureBox^, 1>(400);
	Snake[0] = gcnew PictureBox();
	Snake[0]->Location = Point(200, 200);
	Snake[0]->BackColor = Color::Green;
	Snake[0]->Width = step;
	Snake[0]->Height = step;
	score = 0;
	this->Controls->Add(Snake[0]);

	//�������������� �����
	fruit = gcnew PictureBox();
	fruit->Location = Point(200, 200);
	fruit->BackColor = Color::Yellow;
	fruit->Width = step;
	fruit->Height = step;
	GeneratePositionFruit();

	//������ �������� ���������� ��� ������� � ��������� ���
	timer->Interval = updateInterval;
	timer->Start();

	//������ ����������� �� �������
	direction.X = 1;
	direction.Y = 0;

	//����� ������
	play = true;
	die = false;
	labelScore->Text = "����: 0";

	//�������� �������� ���������� �� �����
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
	//��������� ����
	play = true;
	timer->Start();
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Hide();
}

System::Void miniGamesAppPlus::SnakeForm::���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("������� ����: \n1. ��� ���������� ������������ �������\n2. ����� ������ ��� ���������� ����� � ������\n3. ������ ���� ���� � ��������� � ������", "���������� � ����");
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	NewGame();
	return System::Void();
}

System::Void miniGamesAppPlus::SnakeForm::���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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

System::Void miniGamesAppPlus::SnakeForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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
	//��������� ������� �������
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
		MessageBox::Show("���� ��������!", "��������!");
	}
	else if (!die && !play) 
	{
		timer->Stop();
		MessageBox::Show("���� ��������������", "��������!");
	}
}