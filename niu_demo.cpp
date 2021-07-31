#include<stdio.h>
#include<string>
#include<algorithm>
#include<iostream>
#include <time.h>
using namespace std;
/*
---------��Ϸ����---------
1.����2-6����ͬʱ����
2.ʤ����Ψһ����ׯ��
3.����������ͣ��������������

	1.����ÿ����ҵ����Ƶĵ÷����ж�˭��ʤ����
	2.ţţ>��ţ>��ţ
	3.ʣ�������ͬʱ���Ƚϻ�ɫ���ں�÷������������
	4.������ţ���Ƚ���������������ͬ�Ȼ�ɫ
	5.�������Ƶķּ��㷽ʽ��
		5.1 ţţ���100000�֣���ţ���10000����ţ0��
		5.2 �����÷�Ϊţ1:1000�֣�ţ2:2000�֡�������������
		5.3 ��ţ������ͬ������ţ����ţţ���Ƚ�����Ƶĵ����ͻ�ɫ�� �����÷֣�����*10+��ɫ���ڣ�3�����죨2����������������

* */
/*-------------------------------------------------------------------------------------*/
class CardData						//������Ƶ����ݣ�ģ��һ�����������ݣ������ڽṹ��
{
public:							
	int point=-1;					//�Ƶĵ���  J=10 Q=11  K=12
	int realPoint=-1;				//�����ĵ��� J=Q=k=10
	string flowerColor="";			//��ɫ
	int playingCard=-1;				//��������ĵ���

};

/*-------------------------------------------------------------------------------------*/

class Player														//���
{
private:
	int playingCard[5];												//5���˿���
	string FLOWERCOLOR[4] = { "DIAMOND","SPADE","HEART","CLUB" };	//�˿˵����ֻ�ɫ
	int CARDNUMBER = 5;												//ÿ����ҵ��˿�������
	CardData Cards[5];												//��������
	CardData remainCards[2];										//ʣ�µ�����
	int flag;														//��Ǵ�����Ƿ���ţ  ţţ��1  ��ţ��2  ��ţ��3
	int cardScore;													//���Ƶĵ÷�
public:
	Player() {};

	Player(int pCard[])
	{
		for (int i = 0; i < CARDNUMBER; ++i)
		{
			playingCard[i] = pCard[i];
		}
		flag = 3;
	}
	void translateFlowerColor()										//��5�Ż���������ת��Ϊ������ͬ���˿���
	{
		int point;//����
		int fColor;//��ɫ

		for (int i = 0; i < CARDNUMBER; ++i)
		{
			point = playingCard[i] / 4;//�����˿���
			fColor = playingCard[i] % 4;//�����˿��Ƶĵ���
			if (fColor != 0)
			{
				point++;
			}
			if (point > 10)
			{
				Cards[i].realPoint = 10;
			}
			else
			{
				Cards[i].realPoint = point;
			}
			Cards[i].point = point;
			Cards[i].flowerColor = FLOWERCOLOR[fColor];//��ɫ
			Cards[i].playingCard = i;//��������ĵ���
		}
	}
	void calCard()//����ʣ�µ���
	{
		translateFlowerColor();
		int tflag = 0;
		int temp[3];
		for (int i = 0; i < CARDNUMBER; i++)
		{
			for (int j = i + 1; j < CARDNUMBER; j++)
			{
				for (int k = j + 1; k < CARDNUMBER; k++)
				{
					if ((Cards[i].realPoint + Cards[j].realPoint + Cards[k].realPoint) % 10 == 0)    //������ţ
					{
						//System.out.println(Cards[i].realPoint+"-"+Cards[j].realPoint+"-"+Cards[k].realPoint);
						temp[0] = i;
						temp[1] = j;
						temp[2] = k;
						flag = 2;
						tflag++;
						cardScore = 10000;						//��ţ10000��
						if (cardScore != 100000)                //δ�ҵ�ţţ�ͼ�������
						{
							recordRemain(temp);
							if (cardScore == 100000)
							{
								return;							//ţţ�ҵ����˳�����
							}
						}

					}
				}
			}
		}
		if (tflag == 0)
		{
			flag = 3;
			cardScore = 0;                      //��ţû��
		}
	}
	void recordRemain(int t[])                       //�˴���Ҫ�Ż�һ��
	{
		int j = 0;
		int sum = (remainCards[0].realPoint + remainCards[1].realPoint) % 10;
		int sumRe = 0;
		int pos[2] = {};
		for (int i = 0; i < CARDNUMBER; i++)            //�ҳ�ʣ�µ�����������  �������������±�
		{
			if (i != t[1] && i != t[2] && i != t[0])
			{
				pos[j++] = i;
				// sumRe += Cards[i].realPoint;

			}
		}
		sumRe = (Cards[pos[0]].realPoint + Cards[pos[1]].realPoint) % 10;
		//System.out.println(sumRe);
		if (sum < sumRe || sumRe == 0)						//��������֮�����Ϊţţ
		{
			remainCards[0] = Cards[pos[0]];
			remainCards[1] = Cards[pos[1]];
			if (sumRe == 0)
			{
				flag = 1;
				cardScore = 100000;                         //ţţ100000��
			}
		}
	}

	
	int showFlag()
	{
		return flag;
	}												//��ʾ������������ͣ�ţţ����ţ����ţ


	void showFlowerColor()                           //��ʾ������ϵ�����
	{
		char JQK;
		//cout<<"�ȼ�:"<<flag<<" --- ����:"<<cardScore<<" --- "<<endl;
		if (flag == 1)
		{
			cout << "------ţţ--" << endl;;
		}
		else if (flag == 2)
		{
			cout<<"------ţ" << (remainCards[0].realPoint + remainCards[1].realPoint) % 10 <<"--"<<endl;
		}
		else
		{
			cout<<"------��ţ--"<<endl;
		}
		for (int i = 0; i < CARDNUMBER; i++)
		{
			if (Cards[i].point == 1 || (Cards[i].point > 10 && Cards[i].point < 15))
			{
				if (Cards[i].point == 11)
				{
					JQK = 'J';
				}
				else if (Cards[i].point == 12)
				{
					JQK = 'Q';
				}
				else if (Cards[i].point == 13)
				{
					JQK = 'K';
				}
				else
				{
					JQK = 'A';
				}
				cout<<Cards[i].flowerColor << ": " << JQK/*+"----"+Cards[i].realPoint+"-----"+playingCard[i]*/<<endl;
				continue;
			}
			cout << Cards[i].flowerColor << ": " << Cards[i].point/*+"----"+Cards[i].realPoint+"-----"+playingCard[i]*/ << endl;
		}
	}

	void showRemain(int a)                           //��ʾ��ţ��ʣ�������Ƶ�����
	{
		calCard();//����ʣ�µ�������
		if (flag == 3)
		{
			cout << "��ţ������" << endl;;
			return;
		}
		cout << "--------------------------------" << endl;
		cout << remainCards[0].flowerColor << ": " << remainCards[0].point << "----" << remainCards[0].realPoint << endl;
		cout << remainCards[1].flowerColor << ": " << remainCards[1].point << "----" << remainCards[1].realPoint << endl;
	}


	void getMax(int maxpos[])                        //��ȡ����������÷���ߵ�һ��   �������ֵ���������±�
	{
		maxpos[0] = 0;   //���ֵ
		maxpos[1] = 0;   //�±�
		for (int i = 0; i < CARDNUMBER; i++)
		{
			if (maxpos[0] < Cards[i].point)
			{
				maxpos[0] = Cards[i].point;
				maxpos[1] = i;
			}
			else if (maxpos[0] == Cards[i].point)                       //������ͬʱ�Ƚϻ�ɫ
			{
				if (playingCard[maxpos[1]] > playingCard[i])
				{
					maxpos[0] = Cards[i].point;
					maxpos[1] = i;
				}
			}
		}
	}


	void addSocre()                                  //���ƻ�ɫ�����ӷ�   �������������õ����÷�
	{
		int maxpos[2];								//��һ���������ֵ���ڶ��������±�
		getMax(maxpos);
		if (cardScore == 10000)
		{
			cardScore += ((remainCards[0].realPoint + remainCards[1].realPoint) % 10) * 1000;       //ţ���ķ�
			cardScore += maxpos[0] * 10 + getSocreFlowerColor(Cards[maxpos[1]].flowerColor);        //���ĵ����ͻ�ɫ�ӷ�
			return;
		}
		else
		{
			cardScore += maxpos[0] * 10 + getSocreFlowerColor(Cards[maxpos[1]].flowerColor);         //���ĵ����ͻ�ɫ�ӷ�
		}
	}


	int getSocreFlowerColor(string temp)            //��ȡ�û�ɫ���õ÷�
	{
		if (temp=="DIAMOND")
		{
			return 0;
		}
		else if (temp=="SPADE")
		{
			return 3;
		}
		else if (temp=="HEART")
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}

	int getSocre()
	{
		return cardScore;
	}
};


class BullFight           //��ţ
{
private:
	string FLOWERCOLOR[4] = { "DIAMOND","SPADE","HEART","CLUB" };				//�Ƶ����ֻ���
	int playingCard[52];														//�˿���   52��  ����1-52
	int playerNumber;															//��Ϸ����   �μ���Ϸ������   2-6��
	Player* players;															//���
	Player winner;																//��ʤ��
																				//ÿ����ҵ��˿�������
public:
	int CARDNUMBER = 5;
	void startGame()                //��ʼ��Ϸ
	{
		cout <<"-----------------------------------------------"<< endl;
		cout <<"--------  Welcome to the BullFight!!  ---------"<<endl;
		cout <<"-----------     ��ӭ������ţ��Ϸ    -----------"<<endl;
		cout <<"-----------------------------------------------"<<endl;
	}

	BullFight()
	{
		startGame();
		
		do
		{
			cout<<"Please input the number of play games person:����������Ҹ�����2-6��"<<endl;
			cin >> this->playerNumber;
		} while (this->playerNumber < 2 || this->playerNumber>6);

		cout << "��Ҹ���Ϊ��" << this->playerNumber << endl;
		this->players = new Player[this->playerNumber];

		for (int i = 0; i < 52; i++)
		{
			this->playingCard[i] = i + 1;
		}
	}

	void comparePlayer()            //�ҳ���ʤ��
	{
		int pos = 0;
		int maxScore = players[0].getSocre();
		for (int i = 0; i < this->playerNumber; i++)
		{
			if (maxScore < players[i].getSocre())
			{
				maxScore = players[i].getSocre();
				pos = i;
			}
		}
		winner = players[pos];
	}

	void dealCard()
	{
		int i, j;
		int tmp_pos, tmp;
		int temp[5];
		for (i = 51; i >= 0; i--) {
			srand((unsigned)time(NULL));
			tmp_pos = rand() % (i + 1);
			tmp = playingCard[tmp_pos];
			playingCard[tmp_pos] = playingCard[i];
			playingCard[i] = tmp;
		}


		for (i = 0; i < playerNumber; i++) {
			for (j = 0; j < CARDNUMBER; j++) {
				temp[j] = playingCard[i * CARDNUMBER + j];
			}

			players[i] = Player(temp);					//����
			players[i].calCard();                       //���ƺ�Ϳ���û��ţ   �����ӷ�
			players[i].addSocre();						//��ǰ�����ܵ÷�
		}
	}


	void dealCard1()		//����   ��ϴ�ƣ���Ϊ˳���ƣ����Ʋ����������
	{
		srand(time(0));		//������������ӣ�ʹÿ�λ�ȡ��������в�ͬ��
		int temp[5];		//5����
		int pos = 0;
		int length = sizeof(playingCard) / sizeof(playingCard[0]);
		for (int i = 0; i < playerNumber; i++)
		{
			for (int j = 0; j < CARDNUMBER; j++)
			{
				float randm = ((double)(rand() % 10000)) / 10000;
				//cout << "randm = " << randm << endl;
				pos = (int)(length*randm);           //����±�ֵ
				//cout << "pos = " << pos << endl;
				while (playingCard[pos] == -1)             //��ֹ������ظ�
				{
					randm = ((double)(rand() % 10)) / 10;
					pos = (int)(randm*length);
				}
				temp[j] = playingCard[pos];
				playingCard[pos] = -1;                  //�������Ʋ��ٳ���
			}
			players[i] = Player(temp);              //����
			players[i].calCard();                       //���ƺ�Ϳ���û��ţ   �����ӷ�
			players[i].addSocre();                      //�������ܵ÷�
		}
	}

	void showWinner()               //��ʾ��ʤ��
	{
		cout << endl;
		cout << "--------��ʤ���--------" << endl;
		winner.showFlowerColor();
	}
	void showAllPlayer()            //��ʾ�����������
	{
		cout << "������ң�  " << endl;
		for (int i = 0; i < playerNumber; i++)
		{
			cout << endl;
			cout<<"---------���" << (i + 1) << "--------"<<endl;
			players[i].showFlowerColor();
		}
	}
};




int main() 
{
	/*Player*/
	//int temp[5] = { 7,21,30,8,14 };
	//Player player = Player(temp);
	//player.showFlowerColor();
	//player.showRemain(1);
	//cout << player.showFlag() << endl;

	/*mian*/
	BullFight bF;						//��ʼ��Ϸ
	bF.dealCard();                      //����
	bF.comparePlayer();                 //�Ƚ�
	bF.showAllPlayer();                 //��ʾ������
	bF.showWinner();                    //��ʾ��ʤ��

	return 0;
}				