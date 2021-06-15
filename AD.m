%求整数ADresult代码
x=[8 9 10 11 12 13 14 15 17]         %ADresult
u=x*5/1024%电压
d=asind(u)%角度
k=d/360%占比
T=k*20%采样周期 ms
del=T-0.132%与132的差
del_de=mod((del-0.02),0.01)%延时20us+n*10us  选取最小的值

% 13 误差最小 0.2022ms=200