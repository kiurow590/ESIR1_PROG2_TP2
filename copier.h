/**
   3.2.1 chercher une valeur dans une liste triée, nom de la fonction fonction : chercherTri
   @param premier : itérateur positionné sur le premier élément
   @param dernier : itérateur positionné après le dernier élément
   @param x : valeur à chercher
   @return position du premier élément de valeur >= x
   ou end() si un tel élément n'existe pas
 */
#pragma once
#include "Liste.h"

/**
 * @brief  Cherche un élément dans une liste triée
 * @tparam T  Type de la liste
 * @param premier  Itérateur positionné sur le premier élément
 * @param dernier  Itérateur positionné après le dernier élément
 * @param x  Valeur à chercher
 * @return  Position du premier élément de valeur >= x ou end() si un tel élément n'existe pas
 */
template <typename T>
typename Liste<T>::iterator chercherTri(typename Liste<T>::iterator premier, typename Liste<T>::iterator dernier, const T& x)
{

    while(premier != dernier && *premier < x) // On avance tant que l'élément est plus petit que x
    {
        ++premier; // On avance tant que l'élément est plus petit que x
    }
    return premier; // On retourne l'élément

}


/**
   3.2.2 créer une copie triée par valeurs croissantes d'une liste, nom de la fonction fonction : copierTri
   @param l : liste à copier
   @return liste triée
*/
// TODO
template <typename T>
Liste<T> * copierTri(const Liste<T>& l)
{
    auto * copieListe = new Liste<T>; // On crée une copie de la liste
    for(typename Liste<T>::const_iterator it = l.begin(); it != l.end(); ++it)
    {
        auto element = *it; // On récupère l'élément
        copieListe->insert(chercherTri(copieListe->begin(), copieListe->end(), element), element);  // On l'insère à la bonne position
    }
    return copieListe; // On retourne la copie
}
