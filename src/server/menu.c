void menuGUI()
{
    printf("\t\t----------------MENU------------------\n\n");
    printf("1-Mostrar la opcion uno\n");
    printf("2-Mostrar la opcion dos\n");
    printf("3-Mostrar la opcion tres\n");
    printf("4-Salir\n");
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
            printf("Usted eligio la opcion 1: %d\n", cantidadDeClientesConectados);
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