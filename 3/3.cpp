#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
struct node
{
	char inf[256];
	struct node* next;
	int priority = 0;
};

struct node* head = NULL;
int dlinna = 0;

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

//char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int priority = 0;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: ");
	scanf("%s", s);
	printf("\n");
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	// Добавляем приоритет
	printf("Введите приоритет объекта: ");
	scanf("%d", &priority);
	printf("\n");
	if (priority < 0) {
		return NULL;

	}
	p->priority = priority;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (по приоритету)*/
void spstore()
{
	node* p = get_struct();

	if (p == NULL)
		return;

	if (head == NULL) // если списка нет, то устанавливаем голову списка
	{
		head = p;
	}
	else // список уже есть, то вставляем в конец
	{
		node* current = head;
		if (p->priority > current->priority) // если приоритет нового элемента больше, чем у текущего элемента
		{
			p->next = current;
			head = p;
		}
		else // если приоритет нового элемента меньше или равен, чем у текущего элемента
		{
			while (current->next != NULL && current->next->priority >= p->priority)
			{
				current = current->next;
			}
			p->next = current->next;
			current->next = p;
		}
	}
	return;
}

/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	int i = 1;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("%d) Имя - %s, приоритет - %d\n", i++, struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}

/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}

void delete_element()
{
	char name[256];
	printf("Введите имя элемента: ");
	scanf("%s", name);
	printf("\n");
	del(name);
}

void print_menu()
{
	printf("Выберете действие:\n");
	printf("1. Добавить элемент в список\n");
	printf("2. Удалить элемент \n");
	printf("3. Вывести список \n");
	printf("4. Выход \n");
}

int main()
{


	bool exit = false;
	while (!exit)
	{
		print_menu();
		int option = 0;
		scanf("%d", &option);

		switch (option)
		{
		case 1: spstore(); break;
		case 2: delete_element(); break;
		case 3: review(); break;
		case 4: exit = true; break;
		default: std::cin.get(); break;

		}
	}

	return 0;
}