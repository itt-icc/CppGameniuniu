#include<stdio.h>
#include<string>
#include<algorithm>
#include<iostream>
#include <time.h>
using namespace std;
/*
---------游戏规则---------
1.允许2-6个人同时发牌
2.胜利者唯一，无庄家
3.无特殊的牌型，不计算特殊情况

	1.计算每个玩家的手牌的得分来判定谁是胜利者
	2.牛牛>有牛>无牛
	3.剩余点数相同时，比较花色。黑红梅方。依次排列
	4.若都无牛，比较最大点数，点数相同比花色
	5.计算手牌的分计算方式：
		5.1 牛牛获得100000分，有牛获得10000，无牛0分
		5.2 点数得分为牛1:1000分，牛2:2000分。。。依次类推
		5.3 有牛点数相同或者无牛或者牛牛，比较最大牌的点数和花色， 点数得分：点数*10+花色：黑（3），红（2）。。。依次类推

* */
/*-------------------------------------------------------------------------------------*/
class CardData						//玩家手牌的数据，模拟一个公开的数据，类似于结构体
{
public:							
	int point=-1;					//牌的点数  J=10 Q=11  K=12
	int realPoint=-1;				//真正的点数 J=Q=k=10
	string flowerColor="";			//花色
	int playingCard=-1;				//保存基础的点数

};

/*-------------------------------------------------------------------------------------*/

class Player														//玩家
{
private:
	int playingCard[5];												//5张扑克牌
	string FLOWERCOLOR[4] = { "DIAMOND","SPADE","HEART","CLUB" };	//扑克的四种花色
	int CARDNUMBER = 5;												//每个玩家的扑克牌数量
	CardData Cards[5];												//五张手牌
	CardData remainCards[2];										//剩下的两张
	int flag;														//标记此玩家是否有牛  牛牛：1  有牛：2  无牛：3
	int cardScore;													//此牌的得分
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
	void translateFlowerColor()										//将5张基础点数牌转化为点数不同的扑克牌
	{
		int point;//点数
		int fColor;//花色

		for (int i = 0; i < CARDNUMBER; ++i)
		{
			point = playingCard[i] / 4;//五张扑克牌
			fColor = playingCard[i] % 4;//五张扑克牌的点数
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
			Cards[i].flowerColor = FLOWERCOLOR[fColor];//花色
			Cards[i].playingCard = i;//保存基础的点数
		}
	}
	void calCard()//计算剩下的牌
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
					if ((Cards[i].realPoint + Cards[j].realPoint + Cards[k].realPoint) % 10 == 0)    //保存有牛
					{
						//System.out.println(Cards[i].realPoint+"-"+Cards[j].realPoint+"-"+Cards[k].realPoint);
						temp[0] = i;
						temp[1] = j;
						temp[2] = k;
						flag = 2;
						tflag++;
						cardScore = 10000;						//有牛10000分
						if (cardScore != 100000)                //未找到牛牛就继续查找
						{
							recordRemain(temp);
							if (cardScore == 100000)
							{
								return;							//牛牛找到就退出查找
							}
						}

					}
				}
			}
		}
		if (tflag == 0)
		{
			flag = 3;
			cardScore = 0;                      //无牛没分
		}
	}
	void recordRemain(int t[])                       //此处需要优化一下
	{
		int j = 0;
		int sum = (remainCards[0].realPoint + remainCards[1].realPoint) % 10;
		int sumRe = 0;
		int pos[2] = {};
		for (int i = 0; i < CARDNUMBER; i++)            //找出剩下的牌是哪两张  并保存其数组下标
		{
			if (i != t[1] && i != t[2] && i != t[0])
			{
				pos[j++] = i;
				// sumRe += Cards[i].realPoint;

			}
		}
		sumRe = (Cards[pos[0]].realPoint + Cards[pos[1]].realPoint) % 10;
		//System.out.println(sumRe);
		if (sum < sumRe || sumRe == 0)						//满足条件之后可能为牛牛
		{
			remainCards[0] = Cards[pos[0]];
			remainCards[1] = Cards[pos[1]];
			if (sumRe == 0)
			{
				flag = 1;
				cardScore = 100000;                         //牛牛100000分
			}
		}
	}

	
	int showFlag()
	{
		return flag;
	}												//显示该玩家手牌类型：牛牛，有牛，无牛


	void showFlowerColor()                           //显示玩家手上的手牌
	{
		char JQK;
		//cout<<"等级:"<<flag<<" --- 分数:"<<cardScore<<" --- "<<endl;
		if (flag == 1)
		{
			cout << "------牛牛--" << endl;;
		}
		else if (flag == 2)
		{
			cout<<"------牛" << (remainCards[0].realPoint + remainCards[1].realPoint) % 10 <<"--"<<endl;
		}
		else
		{
			cout<<"------无牛--"<<endl;
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

	void showRemain(int a)                           //显示斗牛后剩下两张牌的属性
	{
		calCard();//计算剩下的牌数量
		if (flag == 3)
		{
			cout << "无牛！！！" << endl;;
			return;
		}
		cout << "--------------------------------" << endl;
		cout << remainCards[0].flowerColor << ": " << remainCards[0].point << "----" << remainCards[0].realPoint << endl;
		cout << remainCards[1].flowerColor << ": " << remainCards[1].point << "----" << remainCards[1].realPoint << endl;
	}


	void getMax(int maxpos[])                        //获取五张牌里面得分最高的一张   返回最大值和其所在下标
	{
		maxpos[0] = 0;   //最大值
		maxpos[1] = 0;   //下标
		for (int i = 0; i < CARDNUMBER; i++)
		{
			if (maxpos[0] < Cards[i].point)
			{
				maxpos[0] = Cards[i].point;
				maxpos[1] = i;
			}
			else if (maxpos[0] == Cards[i].point)                       //点数相同时比较花色
			{
				if (playingCard[maxpos[1]] > playingCard[i])
				{
					maxpos[0] = Cards[i].point;
					maxpos[1] = i;
				}
			}
		}
	}


	void addSocre()                                  //手牌花色点数加分   计算五张牌所得的最大得分
	{
		int maxpos[2];								//第一个保存最大值，第二个保存下标
		getMax(maxpos);
		if (cardScore == 10000)
		{
			cardScore += ((remainCards[0].realPoint + remainCards[1].realPoint) % 10) * 1000;       //牛几的分
			cardScore += maxpos[0] * 10 + getSocreFlowerColor(Cards[maxpos[1]].flowerColor);        //最大的点数和花色加分
			return;
		}
		else
		{
			cardScore += maxpos[0] * 10 + getSocreFlowerColor(Cards[maxpos[1]].flowerColor);         //最大的点数和花色加分
		}
	}


	int getSocreFlowerColor(string temp)            //获取该花色所得得分
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


class BullFight           //斗牛
{
private:
	string FLOWERCOLOR[4] = { "DIAMOND","SPADE","HEART","CLUB" };				//牌的四种花型
	int playingCard[52];														//扑克牌   52张  数字1-52
	int playerNumber;															//游戏人数   参加游戏的人数   2-6人
	Player* players;															//玩家
	Player winner;																//获胜者
																				//每个玩家的扑克牌数量
public:
	int CARDNUMBER = 5;
	void startGame()                //开始游戏
	{
		cout <<"-----------------------------------------------"<< endl;
		cout <<"--------  Welcome to the BullFight!!  ---------"<<endl;
		cout <<"-----------     欢迎来到斗牛游戏    -----------"<<endl;
		cout <<"-----------------------------------------------"<<endl;
	}

	BullFight()
	{
		startGame();
		
		do
		{
			cout<<"Please input the number of play games person:（请输入玩家个数：2-6）"<<endl;
			cin >> this->playerNumber;
		} while (this->playerNumber < 2 || this->playerNumber>6);

		cout << "玩家个数为：" << this->playerNumber << endl;
		this->players = new Player[this->playerNumber];

		for (int i = 0; i < 52; i++)
		{
			this->playingCard[i] = i + 1;
		}
	}

	void comparePlayer()            //找出获胜者
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

			players[i] = Player(temp);					//创建
			players[i].calCard();                       //发牌后就看有没有牛   初步加分
			players[i].addSocre();						//当前手牌总得分
		}
	}


	void dealCard1()		//发牌   不洗牌，牌为顺序牌，发牌采用随机发牌
	{
		srand(time(0));		//设置随机数种子，使每次获取的随机序列不同。
		int temp[5];		//5张牌
		int pos = 0;
		int length = sizeof(playingCard) / sizeof(playingCard[0]);
		for (int i = 0; i < playerNumber; i++)
		{
			for (int j = 0; j < CARDNUMBER; j++)
			{
				float randm = ((double)(rand() % 10000)) / 10000;
				//cout << "randm = " << randm << endl;
				pos = (int)(length*randm);           //随机下标值
				//cout << "pos = " << pos << endl;
				while (playingCard[pos] == -1)             //防止随机数重复
				{
					randm = ((double)(rand() % 10)) / 10;
					pos = (int)(randm*length);
				}
				temp[j] = playingCard[pos];
				playingCard[pos] = -1;                  //发过的牌不再出现
			}
			players[i] = Player(temp);              //创建
			players[i].calCard();                       //发牌后就看有没有牛   初步加分
			players[i].addSocre();                      //这手牌总得分
		}
	}

	void showWinner()               //显示获胜者
	{
		cout << endl;
		cout << "--------获胜玩家--------" << endl;
		winner.showFlowerColor();
	}
	void showAllPlayer()            //显示本局所有玩家
	{
		cout << "所有玩家：  " << endl;
		for (int i = 0; i < playerNumber; i++)
		{
			cout << endl;
			cout<<"---------玩家" << (i + 1) << "--------"<<endl;
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
	BullFight bF;						//开始游戏
	bF.dealCard();                      //发牌
	bF.comparePlayer();                 //比较
	bF.showAllPlayer();                 //显示所有牌
	bF.showWinner();                    //显示获胜者

	return 0;
}				
