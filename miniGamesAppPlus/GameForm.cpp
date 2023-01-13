#include "GameForm.h"


miniGamesAppPlus::GameForm::GameForm(void)
{
	InitializeComponent();
	this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &miniGamesAppPlus::GameForm::OnKeyDown);
	map[0, 0] = 1;
	map[0, 1] = 1;
	createPics();
	createMap();
	generateNewPic();
}

System::Void miniGamesAppPlus::GameForm::правилаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Правила игры: \n1. В каждом раунде появляется плитка номинала «2»\n2. Нажатием стрелки игрок может скинуть все плитки игрового поля в одну из 4 сторон. Если при сбрасывании две плитки одного номинала «налетают» одна на другую, то они превращаются в одну, номинал которой равен сумме соединившихся плиток.\n3. За каждое соединение игровые очки увеличиваются на номинал получившейся плитки.", "Информация о игре");
	return System::Void();
}

System::Void miniGamesAppPlus::GameForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Hide();
}

void miniGamesAppPlus::GameForm::OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	bool ifPicWasMoved = false;
	//Считываем нажатую клавишу
	if (e->KeyCode.ToString() == "Right")
	{
		for (int k = 0; k < 4; k++) 
		{
			for (int l = 2; l >=0 ; l--)
			{
				if (map[k, l] == 1) 
				{
					for (int j = l + 1; j < 4; j++)
					{
						if (map[k, j] == 0) {
							ifPicWasMoved = true;
							map[k, j - 1] = 0;
							map[k, j] = 1;
							pics[k, j] = pics[k, j - 1];
							pics[k, j - 1] = nullptr;
							labels[k, j] = labels[k, j - 1];
							labels[k, j - 1] = nullptr;
							pics[k, j]->Location = Point(pics[k, j]->Location.X + 66, pics[k, j]->Location.Y);
						}
						else
						{
							Int64 a = Convert::ToInt64(labels[k, j]->Text);
							Int64 b = Convert::ToInt64(labels[k, j-1]->Text);
							if (a == b)
							{
								ifPicWasMoved = true;
								labels[k, j]->Text = (a+b).ToString();
								score += a + b;
								changeColor(a + b, k, j);
								label1->Text = "Счёт: " + score;
								map[k, j - 1] = 0;
								this->Controls->Remove(pics[k, j - 1]);
								this->Controls->Remove(labels[k, j - 1]);
								pics[k, j - 1] = nullptr;
								labels[k, j - 1] = nullptr;
							}
						}
					}
				}
			}
		}
	}
	if (e->KeyCode.ToString() == "Left")
	{
		for (int k = 0; k < 4; k++) 
		{
			for (int l = 1; l < 4; l++)
			{
				if (map[k, l] == 1) 
				{
					for (int j = l - 1; j >= 0; j--)
					{
						if (map[k, j] == 0) 
						{
							ifPicWasMoved = true;
							map[k, j + 1] = 0;
							map[k, j] = 1;
							pics[k, j] = pics[k, j + 1];
							pics[k, j + 1] = nullptr;
							labels[k, j] = labels[k, j + 1];
							labels[k, j + 1] = nullptr;
							pics[k, j]->Location = Point(pics[k, j]->Location.X - 66, pics[k, j]->Location.Y);
						}
						else
						{
							Int64 a = Convert::ToInt64(labels[k, j]->Text);
							Int64 b = Convert::ToInt64(labels[k, j + 1]->Text);
							if (a == b)
							{
								ifPicWasMoved = true;
								labels[k, j]->Text = (a + b).ToString();
								score += a + b;
								changeColor(a + b, k, j);
								label1->Text = "Счёт: " + score;
								map[k, j + 1] = 0;
								this->Controls->Remove(pics[k, j + 1]);
								this->Controls->Remove(labels[k, j + 1]);
								pics[k, j + 1] = nullptr;
								labels[k, j + 1] = nullptr;
							}
						}
					}
				}
			}
		}
	}
	if (e->KeyCode.ToString() == "Up")
	{
		for (int k = 1; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				if (map[k, l] == 1)
				{
					for (int j = k - 1; j >= 0; j--)
					{
						if (map[j, l] == 0)
						{
							ifPicWasMoved = true;
							map[j + 1, l] = 0;
							map[j, l] = 1;
							pics[j, l] = pics[j + 1, l];
							pics[j + 1, l] = nullptr;
							labels[j, l] = labels[j + 1, l];
							labels[j + 1, l] = nullptr;
							pics[j, l]->Location = Point(pics[j, l]->Location.X, pics[j, l]->Location.Y - 66);
						}
						else
						{
							Int64 a = Convert::ToInt64(labels[j, l]->Text);
							Int64 b = Convert::ToInt64(labels[j + 1, l]->Text);
							if (a == b)
							{
								ifPicWasMoved = true;
								labels[j, l]->Text = (a + b).ToString();
								score += a + b;
								changeColor(a + b, j, l);
								label1->Text = "Счёт: " + score;
								map[j + 1, l] = 0;
								this->Controls->Remove(pics[j + 1, l]);
								this->Controls->Remove(labels[j + 1, l]);
								pics[j + 1, l] = nullptr;
								labels[j + 1, l] = nullptr;
							}
						}
					}
				}
			}
		}
	}
	if (e->KeyCode.ToString() == "Down")
	{
		for (int k = 2; k >= 0; k--)
		{
			for (int l = 0; l < 4; l++)
			{
				if (map[k, l] == 1)
				{
					for (int j = k + 1; j < 4; j++)
					{
						if (map[j, l] == 0) 
						{
							ifPicWasMoved = true;
							map[j - 1, l] = 0;
							map[j, l] = 1;
							pics[j, l] = pics[j - 1, l];
							pics[j - 1, l] = nullptr;
							labels[j, l] = labels[j - 1, l];
							labels[j - 1, l] = nullptr;
							pics[j, l]->Location = Point(pics[j, l]->Location.X, pics[j, l]->Location.Y + 66);
						}
						else
						{
							Int64 a = Convert::ToInt64(labels[j, l]->Text);
							Int64 b = Convert::ToInt64(labels[j - 1, l]->Text);
							if (a == b)
							{
								ifPicWasMoved = true;
								labels[j, l]->Text = (a + b).ToString();
								score += a + b;
								changeColor(a + b, j, l);
								label1->Text = "Счёт: " + score;
								map[j - 1, l] = 0;
								this->Controls->Remove(pics[j - 1, l]);
								this->Controls->Remove(labels[j - 1, l]);
								pics[j - 1, l] = nullptr;
								labels[j - 1, l] = nullptr;
							}
						}
					}
				}
			}
		}
	}
	if (ifPicWasMoved)
		generateNewPic();
}

void miniGamesAppPlus::GameForm::createPics()
{
	pics[0, 0] = gcnew PictureBox();
	labels[0,0] = gcnew Label();
	labels[0, 0]->Text = "2";
	labels[0, 0]->Size = System::Drawing::Size(60, 60);
	labels[0, 0]->TextAlign = ContentAlignment::MiddleCenter;
	labels[0, 0]->Font = gcnew System::Drawing::Font("Arial", 15);
	pics[0, 0]->Controls->Add(labels[0, 0]);
	pics[0, 0]->Location = Point(16, 71);
	pics[0, 0]->Size = System::Drawing::Size(60, 60);
	pics[0, 0]->BackColor = Color::Yellow;
	this->Controls->Add(pics[0, 0]);

	pics[0, 1] = gcnew PictureBox();
	labels[0, 1] = gcnew Label();
	labels[0, 1]->Text = "2";
	labels[0, 1]->Size = System::Drawing::Size(60, 60);
	labels[0, 1]->TextAlign = ContentAlignment::MiddleCenter;
	labels[0, 1]->Font = gcnew System::Drawing::Font("Arial", 15);
	pics[0, 1]->Controls->Add(labels[0, 1]);
	pics[0, 1]->Location = Point(82, 71);
	pics[0, 1]->Size = System::Drawing::Size(60, 60);
	pics[0, 1]->BackColor = Color::Yellow;
	this->Controls->Add(pics[0, 1]);
}

void miniGamesAppPlus::GameForm::createMap()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			PictureBox^ pic = gcnew PictureBox();
			pic->Location = Point(16 + (66 * i), 71 + (66 * j));
			pic->BackColor = Color::Gray;
			pic->Size = System::Drawing::Size(60, 60);
			this->Controls->Add(pic);
		}
	}
}

void miniGamesAppPlus::GameForm::createMap(int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			PictureBox^ pic = gcnew PictureBox();
			pic->Location = Point(16 + (66 * i), 71 + (66 * j));
			pic->BackColor = Color::Gray;
			pic->Size = System::Drawing::Size(60, 60);
			this->Controls->Add(pic);
		}
	}
}

void miniGamesAppPlus::GameForm::generateNewPic()
{
	Random^ rnd = gcnew Random();
	int a = rnd->Next(0, 3);
	int b = rnd->Next(0, 3);
	while (pics[a, b] != nullptr)
	{
		a = rnd->Next(0, 4);
		b = rnd->Next(0, 4);
	}
	map[a, b] = 1;
	pics[a, b] = gcnew PictureBox();
	labels[a, b] = gcnew Label();
	labels[a, b]->Text = "2";
	labels[a, b]->Size = System::Drawing::Size(60, 60);
	labels[a, b]->TextAlign = ContentAlignment::MiddleCenter;
	labels[a, b]->Font = gcnew System::Drawing::Font("Arial", 15);
	pics[a, b]->Controls->Add(labels[a, b]);
	pics[a, b]->Location = Point(16 + (66 * b), 71 + (66 * a));
	pics[a, b]->Size = System::Drawing::Size(60, 60);
	pics[a, b]->BackColor = Color::Yellow;
	this->Controls->Add(pics[a, b]);
	pics[a, b]->BringToFront();
}

void miniGamesAppPlus::GameForm::changeColor(int sum, int k, int j)
{
	if (sum % 1024 == 0) pics[k, j]->BackColor = Color::Pink;
	else if (sum % 512 == 0) pics[k, j]->BackColor = Color::Red;
	else if (sum % 256 == 0) pics[k, j]->BackColor = Color::DarkViolet;
	else if (sum % 128 == 0) pics[k, j]->BackColor = Color::Blue;
	else if (sum % 64 == 0) pics[k, j]->BackColor = Color::Brown;
	else if (sum % 32 == 0) pics[k, j]->BackColor = Color::Coral;
	else if (sum % 16 == 0) pics[k, j]->BackColor = Color::Cyan;
	else if (sum % 8 == 0) pics[k, j]->BackColor = Color::Maroon;
	else pics[k, j]->BackColor = Color::Green;
}
