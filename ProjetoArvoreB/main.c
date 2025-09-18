#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "ArvoreB.h"

int main()
{
    no *raiz = NULL;
    int ordem;

    printf("\nZX=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=XZ\n");
    printf("\nZX=-=-=-=-=-SPELLBOOK DIGITAL=-=-=-=-=XZ\n");
    printf("\nZX=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=XZ\n\n");

    printf("\nO relatorio tem o nome dos autores e explica o funcionamento\n\n");

    printf("Digite a ordem da Arvore B: ");
    scanf("%d", &ordem);
    getchar();

    int opcao;
    char buffer[100];
    no *receptor;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Inserir spell\n");
        printf("2. Buscar spell\n");
        printf("3. Remover spell\n");
        printf("4. Imprimir arvore\n");
        printf("5. Sair\n");
        printf("6. Adicionar 10 spells para teste.\n");
        printf("====================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:
                printf("Digite o nome do spell: ");
                if(fgets(buffer, sizeof(buffer), stdin))
                {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    insercaoCLRS(&raiz, buffer, ordem);
                }
                break;

            case 2:
                receptor = NULL;
                printf("Digite o nome do spell para buscar: ");
                if(fgets(buffer, sizeof(buffer), stdin))
                {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    receptor = busca(raiz, buffer);
                    if(receptor) printf("\nAbrindo imagem do spell...\n");
                }
                break;

            case 3:
                printf("Digite o nome do spell que deseja remover: ");
                if(fgets(buffer, sizeof(buffer), stdin))
                {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    remover(&raiz, buffer, ordem);
                }
                break;

            case 4:
                printf("\n--- Estrutura da Arvore B ---\n");
                imprimir(raiz);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            case 6:
            {
                const char *spells[10] =
                {
                    "Magic Missile",
                    "Fireball",
                    "Mage Armor",
                    "Shield",
                    "Cure Wounds",
                    "Healing Word",
                    "Eldritch Blast",
                    "Thunderwave",
                    "Burning Hands",
                    "Invisibility"
                };
                for(int i = 0; i < 10; i++)
                {
                    insercaoCLRS(&raiz, spells[i], ordem);
                }
                printf("10 spells foram adicionados para teste.\n");
                break;
            }

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 5);

    limpar(raiz);
    return 0;
}
