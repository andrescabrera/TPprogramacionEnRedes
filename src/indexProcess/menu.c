#include "menu.h"

void menuGUI()
{
    logger("\t\t----------------MENU------------------\n\n");
    logger("1-Mostrar la opcion uno\n");
    logger("2-Mostrar la opcion dos\n");
    logger("3-Mostrar la opcion tres\n");
    logger("4-Salir\n");
}

//THREAD para manejar el menu del servidor
void *menu_servidor()
{
    char option;
    char ignored;
    do
    {
        menuGUI();
        option = fgetc(stdin);
        do
        {
            ignored = fgetc(stdin);
        }
        while ((ignored != '\n') && (ignored != EOF));

        switch (option)
        {
        case '1':
            printf("Usted eligio la opcion 1:\n");
            printf("\n\nPresione cualquier tecla para continuar\n");
            getchar();
            break;
        case '4':
            exit(1);
            break;
        }
    }
    while (1);
}