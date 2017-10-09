#include "deploy.h"
#include <stdio.h>
#include <time.h>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>

#define DE_BUG 0
#define DE_BUG2 0
#define DE_BUG3 0
using namespace std;

const int INF = 0x9ffff;
const double TIME_LIMITS = 80;
const int GROUP_CTL = 40;
const double CROSSPRO = 0.2;
const double MUTEPRO = 0.2;
const double MUTEPRO2 = 0.1;

struct edge{
	int u;
	int v;
	int cost;
	int flow;
	int cap;
	int next;
}e[MAX_EDGE_NUM<<1];

struct node{
	int u;
	int v;
	int w;
	int c;
}E[MAX_EDGE_NUM];

//distance for calc 
int dis[MAX_EDGE_NUM2];
//user need flow
int need[MAX_EDGE_NUM2];
//user to network node
int utn[MAX_EDGE_NUM2];
//network to user node
int ntu[MAX_EDGE_NUM2];
//network node sum flow
int nsf[MAX_EDGE_NUM2];
//
int first[MAX_EDGE_NUM2];
//record path for mcmf
int p[MAX_EDGE_NUM2];
//mark if vis the node
bool vis[MAX_EDGE_NUM2];
int edgenum =0;
int user_sum_flow=0;
int sc=0;
int nonn=0;
int nocn=0;
int run_times = 0;
int best_sum = INF;
string best_s;
string best_ans_file;

struct edge tmp_e[MAX_EDGE_NUM<<1];
int tmp_need[MAX_EDGE_NUM2];
int tmp_edgenum = 0;
vector<int> nounode;

//添加普通边
void add(int u,int v,int w,int num){
	e[edgenum].u = u;
	e[edgenum].v = v;
	e[edgenum].cap = num;
	e[edgenum].cost = w;
	e[edgenum].flow = 0;
	e[edgenum].next = first[u];
	first[u] = edgenum++;

	e[edgenum].u = v;
	e[edgenum].v = u;
    e[edgenum].cap = num;
    e[edgenum].cost = w;
	e[edgenum].flow = 0;
	e[edgenum].next = first[v];
	first[v] = edgenum++;
}

//添加特殊边
void add2(int u,int v,int w,int num){
    e[edgenum].u = u;
    e[edgenum].v = v;
    e[edgenum].cap = num;
    e[edgenum].cost = w;
    e[edgenum].flow = 0;
    e[edgenum].next = first[u];
    first[u] = edgenum++;
}

//判断时候有解
bool isNA(){
    if(DE_BUG) cout<<"in isNA "<<endl;
	for(int i=0;i<nocn;++i){
		if(need[i]>0){
			return true;
		}
	}
	return false;
}

//通过数组中的权重返回概率值高的下标，数字小，概率大s
int rvts(vector<int>& rv){
    if(DE_BUG) cout<<"in rvts... "<<endl;
    int min_c = INF;
    int max_c = 0;
    for(int g=1;g<(int)rv.size();++g){
        min_c = min(min_c,rv[g]);
        max_c = max(max_c,rv[g]);
    }
    double dif = (max_c - min_c);
    if(DE_BUG2) cout<<"in rvts dif "<<dif<<endl;
    if((dif/min_c) < 0.0001) return -1;
    vector<double> dv;
    double sum = 0.0;
    for(int g=1;g<(int)rv.size();++g){
        double t = (max_c - rv[g]);
        dv.push_back(t);
        sum += t;
    }
    double tt = ((double)rand()/RAND_MAX)*sum;
    for(int g=0;g<(int)dv.size();++g){
        tt -= dv[g];
        if(tt<=0) return g;
    }
    return rand()%((int)rv.size()-1);
}

//编码操作，将数组变为字符串
void encode(vector<int> &vc,string & str){
    for(int i=0;i<(int)vc.size();++i){
        str[vc[i]] = '1';
    }
}

//解码操作，将字符串还原数组
void decode(string &str,vector<int> &vc){
    for(int i=0;i<(int)str.size();++i){
        if(str[i]=='1') vc.push_back(i);
    }
}

//最小开销最大流算法，最为底层算法，返回路径和总共开销数值
int mcmf(int s,int t){
    if(DE_BUG) cout<<"in mcmf"<<endl;
    unordered_set<int> servers;
    queue <int> q;
    int cost_sum = 0;
    while(1){
        int c = 0;
        for(int i = 0;i < t+1; i++)
            dis[i] = INF;
        dis[s] = 0;
        memset(vis,false,sizeof(vis));
        memset(p,-1,sizeof(p));
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int k = first[u]; k != -1; k = e[k].next)
            {
                int v = e[k].v;
                if(e[k].cap > e[k].flow && dis[v] > dis[u] + e[k].cost)
                {
                    dis[v] = (dis[u] + e[k].cost);
                    p[v] = k;
                    if(!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        if(dis[t]==INF) {
            break;
        }
        int a = INF;
        int u_b = 0;
        int user_id = ntu[e[p[t]].u];
        for(int u = p[t]; u!=-1; u = p[e[u].u]){
            a = min(a,e[u].cap - e[u].flow);
            u_b = u;
        }
        servers.insert(e[u_b].v);
        need[user_id] -= a;
        for(int u = p[t]; u!=-1; u = p[e[u].u])//增广,这里的u是指第u条边，不再是邻接矩阵里面的顶点
        {
            e[u].flow += a;

        }
        c += dis[t] * a;//注意需要乘以距离
        cost_sum += c;
    }
    cost_sum += sc*(int)servers.size();
    return cost_sum;
}

//时候保存
int is_save(vector<int> &score_j,int score){
    if(DE_BUG) cout<<"in is_save ..."<<endl;
    int dif_max = 0;
    int dif_id = 0;
    for(int g=1;g<(int)score_j.size();++g){
        if(dif_max < (score_j[g] - score)){
            dif_max = (score_j[g] - score);
            dif_id = g;
        }
    }
    return dif_id;
}

//一次搜索过程，返回该解的数值
int one_search(string &stc) {
    if(DE_BUG) cout<<"in one_search"<<endl;
    vector<int> s;
    decode(stc,s);
    run_times++;
    for(vector<int>::iterator it = s.begin(); it != s.end(); ++it) {
        add2(nonn+1,(*it),0,INF);
    }
    int cost_sum = mcmf(nonn+1,nonn);

    for(int i=0;i<nocn;++i){
        if(need[i]>0){
            stc[utn[i]] = '1';
            cost_sum += sc;
        }
    }

//    if(isNA()){
//        memcpy((void*)e,(void*)tmp_e,sizeof(tmp_e));
//        memcpy((void*)need,(void*)tmp_need,sizeof(tmp_need));
//        first[nonn+1] = -1;
//        edgenum = tmp_edgenum;
//        if(DE_BUG) cout<<"return inf as need is not afford"<<endl;
//        return INF;
//    }

    memcpy((void*)e,(void*)tmp_e,sizeof(tmp_e));
    memcpy((void*)need,(void*)tmp_need,sizeof(tmp_need));
    first[nonn+1] = -1;
    edgenum = tmp_edgenum;
    return cost_sum;
}

//通过直连集，变异产生群体，其中nu为终止数值，bn为每次变异次数
void get_start(vector<string> &group_i,vector<int> &score_i){
    if(DE_BUG) cout<<"in get start"<<endl;
    for(int i=0;i<nonn*0.1;++i) {
        string stg(nonn, '0');
        for (int g = 0; g < nocn; ++g) {
            if ((double) rand()/RAND_MAX < 0.7) {
                stg[utn[g]] = '1';
            }
        }
        int sg_i_score = one_search(stg);
        if (DE_BUG2) cout << "sg_i_score " << sg_i_score << endl;
        if (sg_i_score < best_sum) {
            best_sum = sg_i_score;
            best_s = stg;
            if (DE_BUG3) cout << "\n" << endl;
            if (DE_BUG3) cout << "get best_sum :" << best_sum << endl;
        }
        score_i[0] += sg_i_score;
        score_i.push_back(sg_i_score);
        group_i.push_back(stg);
    }
}

//控制种群大小，很关键
void get_control(vector<string> &group_p,vector<int> &score_p){
    if((int)group_p.size() < GROUP_CTL) return ;
    if(DE_BUG) cout<<"in control group"<<endl;
    unordered_set<string> group_s;
    unordered_map<string,int> group_si;
    vector<int> score_s;
    score_s.push_back(0);
    int score_up = (int)((score_p[0]/(score_p.size()-1)));
    for(int g=0;g<(int)group_p.size();++g){
        if(score_p[g+1]<score_up){
            group_s.insert(group_p[g]);
            group_si[group_p[g]] = score_p[g+1];
        }
    }
    vector<string> group_ss(group_s.begin(),group_s.end());
    group_p = group_ss;
    for(vector<string>::iterator it=group_ss.begin();it!=group_ss.end();++it){
        score_s.push_back(group_si[*it]);
        score_s[0] += group_si[*it];
    }
    score_p = score_s;
}

//遗传迭代函数，k为交配变化次数
int get_crosspro(vector<string> &group_j,vector<int> &score_j){
    if(DE_BUG) cout<<"in get_crosspro "<<endl;
    int gjs = (int)group_j.size();
    if(gjs>=2 && (double)rand()/RAND_MAX > CROSSPRO) {
        int i, j;
        if (gjs == 2) {
            i = 0;
            j = 1;
        } else {
            i = rvts(score_j);
            j = i;
            int same = 0;
            while (i == j) {
                j = rvts(score_j);
                if(j==-1) return -1;
                same++;
                if(same>10) return -1;
            }
        }
        if(DE_BUG2) cout<<"i and j is "<<i<<" "<<j<<endl;
        string sg_i = group_j[i];
        string sg_j = group_j[j];

        //===========================================================
        //开始交易
        //===========================================================
        int tt = 15;
        while(tt>0) {
            int ks = (rand() % nonn);
            string tp(sg_i.begin() + ks, sg_i.end());
            sg_i.erase(sg_i.begin() + ks, sg_i.end());
            sg_i.insert(sg_i.end(), sg_j.begin() + ks, sg_j.end());
            sg_j.erase(sg_j.begin() + ks, sg_j.end());
            sg_j.insert(sg_j.end(), tp.begin(), tp.end());
            tt--;
        }
        int sg_i_score = one_search(sg_i);
        if (DE_BUG2) cout << "sg_i_score " << sg_i_score << endl;
        int dif = is_save(score_j,sg_i_score);
        if (dif) {
            if (sg_i_score < best_sum) {
                best_sum = sg_i_score;
                best_s = sg_i;
                if (DE_BUG3) cout << "\n" << endl;
                if (DE_BUG3) cout << "get best_sum :" << best_sum << endl;
            }
            score_j[0] += (sg_i_score - score_j[dif]);
            score_j[dif] = sg_i_score;
            group_j[dif-1] = sg_i;
        }
        int sg_j_score = one_search(sg_j);
        if (DE_BUG2) cout << "sg_j_score " << sg_j_score << endl;
        dif = is_save(score_j,sg_j_score);
        if (dif) {
            if (sg_j_score < best_sum) {
                best_sum = sg_j_score;
                best_s = sg_j;
                if (DE_BUG3) cout << "\n" << endl;
                if (DE_BUG3) cout << "get best_sum :" << best_sum << endl;
            }
            score_j[0] += (sg_j_score - score_j[dif]);
            score_j[dif] = sg_j_score;
            group_j[dif-1] = sg_j;
        }
        //===========================================================
        //服务器直连点消失
        //===========================================================
        if (DE_BUG) cout << "in function xiaoshi  "<< endl;
        string mutev2  = group_j[rand()%(int)group_j.size()];
        for(int g=0;g < nocn;++g){
            if(mutev2[utn[g]] == '1'){
                mutev2[utn[g]] = (char)(rand()%2 + '0');
            }
        }
        sg_j_score = one_search(mutev2);
        if (DE_BUG2) cout << "sg_i_score " << sg_j_score << endl;
        dif = is_save(score_j,sg_j_score);
        if(dif) {
            if (sg_j_score < best_sum) {
                best_sum = sg_j_score;
                best_s = mutev2;
                if (DE_BUG3) cout << "\n" << endl;
                if (DE_BUG3) cout << "get best_sum :" << best_sum << endl;
            }
            score_j[0] += (sg_j_score - score_j[dif]);
            score_j[dif] = sg_j_score;
            group_j[dif-1] = mutev2;
        }
    }
    if(DE_BUG) cout<<"after ctl group j size is "<<(int)group_j.size()<<" "<<(int)score_j.size()<<endl;
    return 0;
}

void get_mutepro(vector<string> &group_j,vector<int> &score_j){
    if(DE_BUG) cout<<"in get_mutepro "<<endl;
    //===========================================================
    //开始变异
    //===========================================================
    if((double)rand()/RAND_MAX < MUTEPRO) {
        if (DE_BUG) cout << "in function bianyi  " << endl;
        string mutev = group_j[rand() % (int) group_j.size()];
        for (int g = 0; g < nonn; ++g) {
            if ((double) rand() / RAND_MAX < MUTEPRO2) {
                if (mutev[g] == '0') {
                    mutev[g] = '1';
                }
                mutev[g] = '0';
            }
        }
        int sg_i_score = one_search(mutev);
        if (DE_BUG2) cout << "sg_i_score " << sg_i_score << endl;

        if (sg_i_score < best_sum) {
            best_sum = sg_i_score;
            best_s = mutev;
            if (DE_BUG3) cout << "\n" << endl;
            if (DE_BUG3) cout << "get best_sum :" << best_sum << endl;
        }
        score_j[0] += sg_i_score;
        score_j.push_back(sg_i_score);
        group_j.push_back(mutev);
    }
}

void mcmf_f(int s,int t,string& ans_file){
    if(DE_BUG) cout<<"in mcmf_f"<<endl;
    string ans_file2;
    vector<int> path;
    queue <int> q;
    int link_num = 0;
    while(1){
        if(!path.empty())
            path.clear();
        for(int i = 0;i < t+1; i++)
            dis[i] = INF;
        dis[s] = 0;
        memset(vis,false,sizeof(vis));
        memset(p,-1,sizeof(p));
        q.push(s);
        path.push_back(t);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int k = first[u]; k != -1; k = e[k].next)
            {
                int v = e[k].v;
                if(e[k].cap > e[k].flow && dis[v] > dis[u] + e[k].cost)
                {
                    dis[v] = (dis[u] + e[k].cost);
                    p[v] = k;
                    if(!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        if(dis[t]==INF) {
            break;
        }
        int a = INF;
        for(int u = p[t]; u!=-1; u = p[e[u].u]){
            a = min(a,e[u].cap - e[u].flow);
            path.push_back(e[u].u);
        }
        path.pop_back();
        int id = (int)path.size() - 1;
        for(int i=id;i>0;--i){
            ans_file2 += (to_string(path[i]) + " ");
        }
        ans_file2 += (to_string(ntu[path[1]])+" ");
        need[ntu[path[1]]] -= a;
        for(int u = p[t]; u!=-1; u = p[e[u].u])//增广,这里的u是指第u条边，不再是邻接矩阵里面的顶点
        {
            e[u].flow += a;
        }
        ans_file2 += (std::to_string(a)+"\n");
        link_num++;
    }
    ans_file = to_string(link_num)+"\n\n"+ans_file2;
}

//一次搜索过程，返回该解的数值
void one_search_f(string &stc,string &ans_file){
    if(DE_BUG) cout<<"in one_search"<<endl;
    vector<int> s;
    decode(stc,s);
    for(vector<int>::iterator it = s.begin(); it != s.end(); ++it) {
        add2(nonn+1,(*it),0,INF);
    }
    mcmf_f(nonn+1,nonn,ans_file);
    if(isNA()){
        ans_file = "";
    }
}

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename) {
    int i = 0;
    int noe = 0;
    stringstream tmp_stream;
    tmp_stream << string(topo[0]);
    tmp_stream >> nonn >> noe >> nocn;
    if (DE_BUG) cout << "num of cum node :" << nocn << " noe :" << noe << " nonn :" << nonn << endl;
    tmp_stream << string(topo[2]);
    tmp_stream >> sc;
    if (DE_BUG) cout << "server cost :" << sc << endl;
    memset(nsf, 0, sizeof(nsf));
    memset(first, -1, sizeof(first));
    memset(utn, -1, sizeof(utn));
    memset(ntu, -1, sizeof(ntu));
    memset(need, 0, sizeof(need));

    //===================================================================
    // 读取图的信息，存与邻接表
    //===================================================================
    i = 4;
    for (int j = 0; j < noe; ++j) {
        tmp_stream << string(topo[i++]);
        tmp_stream >> E[j].u >> E[j].v >> E[j].w >> E[j].c;
        if (DE_BUG) cout << "E: " << E[j].u << " " << E[j].v << " " << E[j].w << " " << E[j].c << endl;
        nsf[E[j].u] += E[j].w;
        nsf[E[j].v] += E[j].w;
        add(E[j].u, E[j].v, E[j].c, E[j].w);
    }
    i++;
    tmp_stream.clear();
    while (i < line_num) {
        tmp_stream << string(topo[i]);
        int id1, id2, need_u;
        tmp_stream >> id1 >> id2 >> need_u;
        if (DE_BUG) cout << "N: " << id1 << " " << id2 << " " << need_u <<endl;
        utn[id1] = id2;
        ntu[id2] = id1;
        need[id1] = need_u;
        user_sum_flow += need_u;
        i++;
    }
    //初始化最优解，默认为用户连接的节点放置服务器
    best_sum = nocn * sc;
    best_ans_file = to_string(nocn) + "\n\n";
    for (int g = 0; g < nocn; ++g) {
        best_ans_file += to_string(utn[g]) + " " + to_string(g) + " " + to_string(need[g]) + "\n";
    }
    for (int g = 0; g < nocn; ++g) {
        add2(utn[g], nonn, 0, need[g]);
    }
    for(int g=0;g<nonn;++g){
        if(ntu[g] == -1)
            nounode.push_back(g);
    }
    memcpy((void *) tmp_e, (void *) e, sizeof(e));
    memcpy((void *) tmp_need, (void *) need, sizeof(need));
    tmp_edgenum = edgenum;
    srand((unsigned) time(0));
    //===================================================================

    //===================================================================
    //以下为遗传算法过程
    //===================================================================
    vector<string> group_s;
    vector<int> score_s(1, 0);


    vector<int> beg;
    string str0(nonn,'0');
    for(int g=0;g<nocn;++g){
        str0[utn[g]]= '1';
        beg.push_back(utn[g]);
    }

    group_s.push_back(str0);
    score_s[0] += nocn*sc;
    score_s.push_back(nocn*sc);

    time_t start, finish;
    double duration = 0;

    //调用函数产生集群
    start = time(NULL);
    get_start(group_s,score_s);
    finish = time(NULL);
    duration += (double)(finish - start);
    if(DE_BUG) cout<<"get start2 over score_s size is "<<(int)group_s.size()<<endl;
    //开始遗传迭代
    srand((unsigned) time(0));
    do{
        start = time(NULL);
        //============开始遗传算法
        int ret = get_crosspro(group_s, score_s);
        if(ret == -1) get_start(group_s,score_s);
        get_mutepro(group_s,score_s);
        get_control(group_s, score_s);
        if((int)group_s.size() < 5){
            get_start(group_s,score_s);
        }
        finish = time(NULL);
        duration += (double)(finish - start);
        if(DE_BUG) cout<<"time is duration "<<duration<<endl;
        if (duration > TIME_LIMITS) {
            break;
        }
    }while(1);
    one_search_f(best_s,best_ans_file);
	if(DE_BUG3) cout<<"\n\n"<<endl;
	if(DE_BUG3) cout<<best_ans_file<<endl;
	if(DE_BUG3) cout<<best_sum<<endl;
    if(DE_BUG3) cout<<run_times<<endl;
	write_result(best_ans_file.c_str(), filename);
}
