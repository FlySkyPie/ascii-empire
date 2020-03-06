bool Empire_Get_Battling(int x,int y);
int  Empire_Get_ArmyTotal(int E);
int  Empire_Get_AreaArmy(int x,int y);
int  Empire_Get_MyArmy(int x,int y,int id,int Password);
int  Empire_Get_Gold(int id,int Password);

void Empire_Move(int x,int y,int direct,int amount,int E,int password);
void Empire_BuyArmy(int x,int y,int amount,int E,int password);
