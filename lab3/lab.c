#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int TREE_COUNT = 1;
pthread_mutex_t mutex;
int FIND_ME;

//Структура дерева

typedef struct TTree
{
	int key;//Значение в узле
	int was;//Переменная, помогающая потоку определить обрабатывать этот узел или нет
	struct TTree* son;//Указатели на "брата" и "сынв"
	struct TTree* brother;
}Tree;

//Добавление в дерево

Tree* Add(Tree* seed, int key, char* way, int count)
{
	if(seed == NULL)
	{
		if(way[count] != '\n' && way[count] != '\0' && way[count] != '\000')
		{
			printf("Ваш путь содержит ошибку, но раз уж он привёл вас в пустой лист, то так и быть зачту эту попытку\n");
		}
		Tree* tree = (Tree*)malloc(sizeof(Tree));
		tree->key = key;
		tree->was = 0;
		tree->brother = NULL;
		tree->son = NULL;
		TREE_COUNT++;
		return tree;
	}
	if(way[count] != 's' && way[count] != 'b')
	{
		printf("Некорректный путь\n");
		return seed;
	}
	if(way[count] == 's')
	{
		seed->son = Add(seed->son, key, way, count + 1);
	}
	if(way[count] == 'b')
	{
		seed->brother = Add(seed->brother, key, way, count + 1);
	}
	if(way[count] != '\n' && way[count] != '\0' && way[count] != '\000' 
	   && way[count] != 's' && way[count] != 'b' && way[count] != 'y')
	{
		printf("Вы пришли в заполненный элемент, хотите провести замену?\ny (англ.) - одобрение замены, всё остальное - отмена\n");
		scanf("%c", &way[0]);
		scanf("%c", &way[0]);
		if(way[0] == 'y')
		{
			seed->key = key;
		}
		scanf("%c", &way[0]);
		return seed;
	}
	return seed;
}

//Печать дерева

void PrintTree(Tree* tree, int tab)
{
	if(tree == NULL)
	{
		return;
	}
	int count;
	for(count = 0; count < tab; count++)
	{
		printf("\t");
	}
	printf("%d\n", tree->key);
	PrintTree(tree->son, tab + 1);
	PrintTree(tree->brother, tab);
	return;
}

//Поиск элемента в дереве

void Find(Tree* tree)
{
	pthread_mutex_lock(&mutex);
	int row = 0;
	if(tree->key == FIND_ME)
	{
		printf("Элемент найден\n");
		tree->was = 1;
		pthread_mutex_unlock(&mutex);
	}
	else
	{
		if(tree->brother != NULL)
		{
			if(tree->brother->was == 0)
			{
				row = 1;
				pthread_mutex_unlock(&mutex);
				Find(tree->brother);
			}
		}
		if(tree->son != NULL && row == 0)
		{
			if(tree->son == 0)
			{
				pthread_mutex_unlock(&mutex);
				Find(tree->son);
			}
		}
		else
		{
			tree->was = 1;
			pthread_mutex_unlock(&mutex);
		}
	}
	return;
}

//

void* Pthr(void* seed)
{
	Tree* tree = (Tree*) seed;
	Find(seed);
	pthread_exit(0);
}

//Обнуление 

void ReWas(Tree* tree)
{
	tree->was = 0;
	if(tree->brother != NULL)
	{
		ReWas(tree->brother);
	}
	if(tree->son != NULL)
	{
		ReWas(tree->son);
	}
	return;
}

//Удаление дерева

void DeleteTree(Tree* tree)
{
	if(tree == NULL)
	{
		return;
	}
	if(tree->son != NULL)
	{
		DeleteTree(tree->son);
	}
	if(tree->brother != NULL)
	{
		DeleteTree(tree->brother);
	}
	free(tree);
	return;
}

int main()
{
	int count;
	Tree *tree = NULL;
	int key;
	printf("Введите число которое будет в корне дерева: ");
	if(scanf("%d", &key) != 1)
	{
		printf("Не надо ломать программу\n");
		return -1;
	}
	tree = (Tree*)malloc(sizeof(Tree));
	tree->key = key;
	tree->was = 0;
	tree->brother = NULL;
	tree->son = NULL;
	char way[2048];
	int whatToDo;
	printf("Что вы хотите сделать:\n1 - добавить элемент в дерево\n2 - распечатать дерево\n3 - найти элемент в дереве\n4 - выйти из программы\n");
	while(whatToDo != 4)
	{
		printf("Ваше действие?\n");
		if(scanf("%d", &whatToDo) != 1)
		{
			printf("Попробуйте снова\n");
			return -1;
		}
		switch(whatToDo)
		{
			case 1://Добавление элемента в дерево
				printf("Введите путь по которому хотите добавить элемент (s - сын, b - брат), ограничившись 2048 символами и число которое хотите добавить\n");
				scanf("%s", way);
				if(scanf("%d", &key) != 1)
				{
					printf("Некорректный ввод, попробуйте ещё раз\n");
					return -1;
				}
				tree = Add(tree, key, way, 0);
				break;
			case 2://Печать дерева
				printf("--------------\n");
				PrintTree(tree, 0);
				printf("--------------\n");
				break;
			case 3://Распараллеленный поиск в дереве
				printf("Введите элемент который хотите найти: ");
				if(scanf("%d", &FIND_ME) != 1)
				{
					printf("Некорректный ввод, попробуйте ещё раз\n");
					return -1;
				}
				pthread_t* stream = (pthread_t*) malloc(TREE_COUNT * sizeof(pthread_t));
				pthread_mutex_init(&mutex, NULL);
				printf("Если под этой строчкой не будет надписи \"Найден\", то элемент не найден. Может он присутствует несколько раз\n");
				for(count = 0; count < TREE_COUNT; count++)
				{
					pthread_create(&(stream[count]), NULL, Pthr, &tree);
				}
				for(count = 0; count < TREE_COUNT; count++)
				{
					pthread_join(stream[count], NULL);
				}
				free(stream);
				ReWas(tree);
				break;
			case 4://Выход из программы
				break;
		}
	}
	DeleteTree(tree);//Освобождение памяти занятой деревом
	return 0;
}
