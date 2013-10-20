#include <iostream>
#include<time.h>
#include <conio.h>
#include <stdio.h>
#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

using namespace std;


const int mapYInt =39;
const int mapXInt =24;
int mapXY [mapXInt][mapYInt];//map width
int PlayerSpawnX = mapXInt-2;
int PlayerSpawnY = 0;


//Player Class
class Player{
public:
    Player(int health = 100,int attack = 10);
    virtual void Greet() const = 0; //pur virtual member function
    virtual void DisplayHealth() const;
    virtual void DisplayStats() const;
    virtual void LoseHealth(int damage);
    virtual void GainHealth(int heal);
    virtual void AttackStatsGain(int boostNumber);
    virtual void DisplayInfo() const;
    virtual void switchPlayerDir();
    virtual void displayPlayerDir();
    virtual int checkPlayerDir();
    //virtual void doDamage(Creature enemy);
private:
    int m_Health;
    int m_MaxHealth = m_Health;
    int m_AttackStat;
    int PlayerX = mapXInt-2;
    int PlayerY = 0;
    int playerDir = 1;
};

Player::Player(int health,int attack):
    m_Health(health),
    m_AttackStat(attack)
{}

void Player::DisplayHealth() const
{
        cout<<"Health: "<<m_Health<<endl;
}

void Player::displayPlayerDir()
{
        cout<<"Direction: "<<playerDir<<endl;
}

void Player::DisplayInfo() const
{
    DisplayHealth();
    DisplayStats();
}

void Player::LoseHealth(int damage)
{
    m_Health = m_Health - damage;
    if(m_Health<= 0)
    {
        cout<<"You are dead!!!"<<endl;
    }else
    {
        cout<<"You took "<<damage<<" damage and your health is now "<<m_Health<<endl;
    }
}

void Player::GainHealth(int heal)
{
    m_Health = m_Health + heal;
    if(m_Health>= m_MaxHealth)
    {
       m_Health = m_MaxHealth;
       cout<<"You are healed all of the way"<<endl;
    }else
    {
        cout<<"You were healed for: "<<heal<<endl;
    }
}

void Player::AttackStatsGain(int BoostedStat)
{
    m_AttackStat+= BoostedStat;
}

void Player::DisplayStats() const
{
        cout<<"Attack Power: "<<m_AttackStat<<endl;
}

/*void Player::doDamage(Player enemy){
    if((enemy.PlayerX && enemy.PlayerY)<1){
        enemy.doDamage(Player.m_AttackStat);
    }else{
        cout<<"No Enemy in Range"<<endl;
    }
}*/
void Player::switchPlayerDir(){
    if(playerDir == 1)
    {
        playerDir = 0;

    }
    else if(playerDir == 0){
        playerDir = 1;
    }
}
int Player::checkPlayerDir(){
    return playerDir;
}

//Derrived Samurai Classs
class Samurai : public Player
{
public:
    Samurai(int health =120);
    virtual void Greet() const;
};

Samurai::Samurai(int health):
    Player(health)
    {}


void Samurai::Greet() const{
    cout<<"Hello I am a Samurai!"<<endl;
}

//Base Creature Class
class Creature{
public:
    Creature(int health = 100);
    virtual void Greet() const = 0; //pur virtual member function
    virtual void DisplayHealth() const;
private:
    int m_Health;
};

Creature::Creature(int health):
    m_Health(health)
{}

void Creature::DisplayHealth() const
{
        cout<<"Health: "<<m_Health<<endl;
}

//Derived Orc Class
class Orc : public Creature
{
public:
    Orc(int health =120);
    virtual void Greet() const;
};

Orc::Orc(int health):
    Creature(health)
    {}

void Orc::Greet() const
{
    cout<<"Hello Orc"<<endl;
}

//Derived Dragon Class
class Dragon: public Creature
{
public:
    Dragon(int health = 1000);
    virtual void Greet() const;
};

Dragon::Dragon(int health):
    Creature(health)
    {}


void Dragon::Greet() const{
    cout<<"DRAGON!!!"<<endl;
}

void makeMap(int x[mapXInt] [mapYInt]){
    for(int z = 0; z<mapXInt ;z++){
        for(int xz = 0; xz<mapYInt;xz++){
            if(z==mapXInt-1){
                mapXY[z][xz] = 1;
            }
           /* if((xz%2)==0){
                mapXY[z][xz] = 1;
            }*/
           else{
                mapXY[z][xz] = 0;
            }

        }
    }
}

void drawMap(int x[mapXInt] [mapYInt]){
    for(int z = 0; z<mapXInt ;z++){
            cout<<endl;
        for(int xz = 0; xz<mapYInt;xz++){
            cout<<mapXY[z][xz]<<" ";
        }
    }
    cout<<endl;
}

void updateFunction(){//needs to be fixed
    clock_t update;
    bool unPause = true;
    while(unPause){
        update = clock();
        if(update==1){
            update = clock() - update;
            cout<<update<<endl;
            update = clock();
        }
    }
}


int main()
{

   // updateFunction();
    //Create an orc
    Creature* pOrc = new Orc();
    pOrc->Greet();
    pOrc->DisplayHealth();

    //Create a Dragon
    Creature* pDragon = new Dragon();
    pDragon->Greet();
    pDragon->DisplayHealth();

    //Create a  Samurai Player
    Player* pSamurai = new Samurai();
    pSamurai->Greet();
    pSamurai->DisplayInfo();
    pSamurai->AttackStatsGain(10);
    pSamurai->LoseHealth(50);
    pSamurai->DisplayInfo();
    pSamurai->GainHealth(10);
    pSamurai->DisplayInfo();
    makeMap(mapXY);
    drawMap(mapXY);
    mapXY[PlayerSpawnX][PlayerSpawnY] = 3;
    drawMap(mapXY);
/*
    bool loopBool = true;
    while(loopBool)
    {
        int inputInt;
        cin>>inputInt;
        switch(inputInt)
        {
        case 0:
            pSamurai->GainHealth(25);
            pSamurai->DisplayHealth();
              break;
        case 1:
            pSamurai->LoseHealth(30);
            pSamurai->DisplayHealth();
            break;
        case 2:
            pSamurai->DisplayInfo();
            loopBool = false;
            break;
        default:
            pSamurai->DisplayInfo();
            loopBool = false;
            break;
        }
    }
    //Getline with whitespace till newline
    string hello;
    getline(cin,hello);
    cout<< hello << endl;*/
    int KB_code=0;

   while(KB_code != KB_ESCAPE )
   {
     if (kbhit())
      {
            KB_code = getch();
           // printf("KB_code = %i \n",KB_code);

            switch (KB_code)
            {
                case KB_LEFT:
                    if(pSamurai->checkPlayerDir() == 1){
                        pSamurai->switchPlayerDir();
                        pSamurai->displayPlayerDir();
                    }
                           //Do something
                break;

                case KB_RIGHT:
                    if(pSamurai->checkPlayerDir() == 0){
                        pSamurai->switchPlayerDir();
                        pSamurai->displayPlayerDir();
                    }else if(mapXY[PlayerSpawnX][PlayerSpawnY+1] == 0){
                        //cout<<"its a zero!"<<endl;
                        mapXY[PlayerSpawnX][PlayerSpawnY+1] = 3;
                        mapXY[PlayerSpawnX][PlayerSpawnY] =0;
                        drawMap(mapXY);
                    }else{
                        //cout<<"its a zero!"<<endl;
                        mapXY[PlayerSpawnX][PlayerSpawnY+1] = 3;
                        mapXY[PlayerSpawnX][PlayerSpawnY] =0;
                        drawMap(mapXY);
                    }
                           //Do something
                break;

                case KB_UP:
                           //Do something
                break;

                case KB_DOWN:
                           //Do something
                break;

            }

      }
  }

    return 0;
}
