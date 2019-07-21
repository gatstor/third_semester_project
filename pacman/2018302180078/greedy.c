#include "util.h"
#include <stdio.h>
#include <string.h>

typedef struct l {
	long long 	int x;
	long long 	int y;
	char path[800];
	long long 	int length;
}box;

int visited[1000][1000];
box queue[10000];
int exist[1000][1000];
int hav_eat[1000][1000];


int judge_no_douzi(game_state_t state)
{
	for(int i=0;i<state.n;i++)
	{
		for(int j=0;j<state.m;j++)
		{
			if(state.food[i][j]==1&&hav_eat[i][j]!=1)
				return 0;//to express not eat all douzi
		}
	}
	return 1;// to express have eaten all
}

void BFS(game_state_t state,game_state_t u, game_state_t *v)//state is u
{
	long long int rear = 0;
	long long int maxsize = 10000;
	long long int front = 0;
	box temp1;
	box temp2;
	temp1.x = u.start_x;
	temp1.y = u.start_y;
	temp1.length = 0;
	temp1.path[temp1.length] = '\0';
	exist[temp1.x][temp1.y] = 1;
	queue[front] = temp1;
	front++;
	front = front % maxsize;
	while (rear != front)
	{
		temp1 = queue[rear];
		rear++;
		rear = rear%maxsize;
		visited[temp1.x][temp1.y]=1;
		exist[temp1.x][temp1.y] = 0;
		if (state.food[temp1.x][temp1.y]==1&&hav_eat[temp1.x][temp1.y]==0)
		{
			hav_eat[temp1.x][temp1.y]=1;
			for ( int i = 0; i < temp1.length; i++)
			{
				printf("%c", temp1.path[i]);
			}
			(*v).start_x=temp1.x;
			(*v).start_y=temp1.y;
			
			return;
		}
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				temp2.x = temp1.x + 1;
				temp2.y = temp1.y;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'S';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front%maxsize;
				}
			}
			if (i == 1)
			{
				temp2.x = temp1.x - 1;
				temp2.y = temp1.y;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'N';
				temp2.path[temp2.length] = '\0';


				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front %maxsize ;
				}
			}
			if (i == 2)
			{
				temp2.x = temp1.x;
				temp2.y = temp1.y - 1;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'W';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}

			}
			if (i == 3)
			{
				temp2.x = temp1.x;
				temp2.y = temp1.y + 1;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'E';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}

			}


		}

	}
	printf("123");

}


int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	game_state_t u;
	game_state_t v;
	game_state_t temp;
	u.start_x=state.start_x;
	u.start_y=state.start_y;
	// write your code here
	while(!judge_no_douzi(state))
	{
	
		for(int i=0;i<1000;i++)
		{
			for(int j=0;j<1000;j++)
				{
					exist[i][j]=0;
					visited[i][j]=0;
				}
		}
		BFS(state,u,&v);
		u=v;
	}

	// 
	destroy(&state);
	return 0;
}
