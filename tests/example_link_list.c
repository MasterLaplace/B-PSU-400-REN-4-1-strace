/*
** EPITECH PROJECT, 2023
** B-PSU-400-ftrace
** File description:
** example_link_list
*/

#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

#define NB_WAVE 10

typedef struct wave_s {
    double wavelength;
    double wave_speed;
    double wave_direction;
} wave_t;

link_t *wave_list;

// Quand tu veux ajouter un élément à la liste, tu fais ça:
void init_wave()
{
    wave_list = NULL;

    for (unsigned i = 0; i < NB_WAVE; i++) {
        wave_t *wave = malloc(sizeof(wave_t));
        wave->wavelength = 0;
        wave->wave_speed = 0;
        wave->wave_direction = 0;

        // Add the wave to the list
        list_append(&(wave_list), create_link(wave));
    }
}

void free_wave(wave_t *wave)
{
    // Free the wave and all its content
    free(wave);
}

// Quand tu veux supprimer un élément de la liste, tu fais ça:
void delete_wave()
{
    link_t *actual = wave_list;

    if (!actual)
        return;
    do {
        wave_t *wave = (wave_t *)actual->obj;

        if (wave->wavelength == 0) {
            list_remove(&(wave_list), actual, &free_wave);
            break;
        }

        // Si tu veux supprimer le dernier élément de la liste, tu fais ça:
        list_remove(&(wave_list), wave_list->prev, &free_wave);
        // Si tu veux supprimer le premier élément de la liste, tu fais ça:
        list_remove(&(wave_list), wave_list, &free_wave);

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

// Quand tu veux supprimer tous les éléments de la liste, tu fais ça:
void delete_all_wave()
{
    if (!wave_list)
        return;
    while (wave_list) {
        list_remove(&(wave_list), wave_list, &free_wave);
    }
}

// Quand tu veux boucler sur la liste, tu fais ça:
void print_wave()
{
    link_t *actual = wave_list;

    if (!actual)
        return;
    do {
        wave_t *wave = (wave_t *)actual->obj;

        printf("Wavelength: %f\n", wave->wavelength);
        printf("Wave speed: %f\n", wave->wave_speed);
        printf("Wave direction: %f\n", wave->wave_direction);

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

unsigned main(void)
{
    init_wave();
    print_wave();
    delete_wave();
    print_wave();
    delete_all_wave();
    print_wave();
    return (0);
}
