//
// Created by Aubry TONNERRE on 05/03/23.
//

#ifndef LISTE_TP2_LISTE_H
#define LISTE_TP2_LISTE_H

#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <cassert>
#include "cyclicNode.h"


template<class T>
class Liste {
protected:
    typedef DataStructure::cyclicNode<T> Chainon;
protected:
    // attributs
    Chainon *m_sentinelle; // pointeur vers la sentinelle pour le premier et le dernier élément
    int m_nbElements; // nombre d'éléments dans la liste
public:

    /**
     * \brief Destructeur
     */
    ~Liste() {
        for (int i = m_nbElements; i > 0; i--) {
            pop_back();// on retire chaque élément de la liste de la liste
        }
        delete m_sentinelle; // on supprime la sentinelle
    }

    /**
     * \brief Constructeur par défaut
     */
    Liste() : m_sentinelle(new Chainon()), m_nbElements(0) { std::cout << "Liste() vide" << std::endl; }

    /**
     * \brief Constructeur de copie
     */
    Liste(const Liste &liste) : m_sentinelle(new Chainon()), m_nbElements(0) {
        std::cout << "Liste(const Liste &liste) : COPIE" << std::endl;
        for (auto it = liste.begin(); it != liste.end(); ++it) {
            push_back(*it); // on ajoute chaque élément de la liste à la liste
        }
    }

    /**
     * \brief Si la liste est vide
     * @return  true si la liste est vide, false sinon
     */
    [[nodiscard]] bool empty() const {
        return m_nbElements == 0; // si le nombre d'éléments est égal à 0, la liste est vide
    }

    /**
     * \brief Retourne le nombre d'éléments dans la liste
     * @return Le nombre d'éléments dans la liste
     */
    [[nodiscard]] int size() const {
        return m_nbElements; // on retourne le nombre d'éléments dans la liste
    }

    /**
    * \brief Retourne la valeur de l'élément à l'index spécifié
    * @param index L'index de l'élément à retourner
    * @return La valeur de l'élément à l'index spécifié
    */
    T &front() {
        assert(!empty() && "La liste est vide");
        std::cout << "front() : " << m_sentinelle->next()->data() << std::endl;
        return m_sentinelle->next()->data();

    }

    /**
     * \brief Retourne la valeur de l'élément à l'index spécifié
     * @param index L'index de l'élément à retourner
     * @return La valeur de l'élément à l'index spécifié
     */
    const T &front() const {
        assert(!empty() && "La liste est vide");
        std::cout << "front() const: " << m_sentinelle->next()->data() << std::endl;
        return m_sentinelle->next()->data();

    }


    /**
     * \brief Retourne la valeur de l'élément à l'index spécifié
     * @param index L'index de l'élément à retourner
     * @return La valeur de l'élément à l'index spécifié
     */
    T &back() {
        assert(!empty() && "La liste est vide");
        return m_sentinelle->previous()->data();

    }

    /**
     * \brief Retourne la valeur de l'élément à l'index spécifié
     * @param index L'index de l'élément à retourner
     * @return La valeur de l'élément à l'index spécifié
     */
    const T &back() const {
        assert(!empty() && "La liste est vide");
        return m_sentinelle->previous()->data();
    }

    /**
    * \brief Supprime le premier élément de la liste
    */
    void pop_front() {
        assert(!empty() && "La liste est vide");
        auto temp = m_sentinelle->next();
        m_sentinelle->next()->detach();
        delete temp;
        m_nbElements--;
    }


    /**
    * \brief Supprime le dernier élément de la liste
    */
    void pop_back() {
        assert(!empty() && "La liste est vide");
        auto temp = m_sentinelle->previous();
        m_sentinelle->previous()->detach();
        delete temp;
        m_nbElements--;

    }


    /**
    * \brief Ajoute un élément à la fin de la liste
    * @param element L'élément à ajouter
    */
    void push_back(const T &element) {

        Chainon *nouveau(new Chainon(element));
        m_sentinelle->insertBefore(nouveau);
        m_nbElements++;
    }

    /**
    * \brief Ajoute un élément au début de la liste
    * @param element L'élément à ajouter
    */
    void push_front(const T &element) {
        Chainon *nouveau = new Chainon(element);
        m_sentinelle->insertAfter(nouveau);
        m_nbElements++;
    }

    /**
     * \brief Operateur d'egalite
     * @param liste La liste à copier
     * @return Les deux liste sont egales
     */
    bool operator==(const Liste<T> &other) {
        return this->m_sentinelle == other.m_sentinelle;
    }

    /**
     * \brief Operateur d'affectation
     * @param liste La liste à copier
     * @return La liste copiée
     */
    Liste<T> &operator=(const Liste<T> &liste) {
        std::cout << "operator=(const Liste &liste)" << std::endl;
        if (this->operator==(liste)) return *this;
        while (!empty()) {
            this->pop_back();
        }
        for (auto iter = liste.begin(); iter != liste.end(); ++iter) {
            push_back(*iter);
        }
        return *this;
    }

    /**
     * \brief Concatenation de plusieur liste en surchargeant l'operateur +
     * @param liste La liste à concatener
     * @return La liste concatener
     */
    Liste operator+(const Liste &liste) {
        Liste temp(*this);
        for (auto it = liste.begin(); it != liste.end(); ++it) {
            temp.push_back(*it);
        }
        return temp;
    }

    /**
     * \brief Ecriture d'un toString surchargeant l'operateur <<
     * @param os Le flux de sortie
     * @param liste La liste à afficher
     * @return Le flux de sortie
     */
    friend std::ostream &operator<<(std::ostream &os, const Liste &liste) {
        os << "<";
        for (auto it = liste.begin(); it != liste.end(); ++it) {
            os << *it;
            if (it != --liste.end()) {
                os << " ";
            }
        }
        os << " >";
        return os;
    }

    /**
     * \brief const_iterator : iterateur constant
     */
    class const_iterator {
    protected:
        friend class Liste<T>;

        const Chainon *m_current;
        const Chainon *m_sentinelle;

        const_iterator(const Chainon *current, const Chainon *sentinelle) : m_current(current),
                                                                            m_sentinelle(sentinelle) {}

    public:
        /**
         * operateur ++ prefixe
         * positionne l'iterateur sur le prochain élément de la liste
         * @pre l'iterateur designe une position validé dans la liste (!= end())
         * @return l'iterateur positionné sur le prochain élément de la liste
         */
        const_iterator &operator++() {
            assert(m_current != m_sentinelle && "La liste est vide");
            m_current = m_current->next();
            return *this;
        }

        /**
         * operateurs -- prefixe
         * positionne l'iterateur sur le précédent élément de la liste
         * @pre l'iterateur designe une position valide dans la liste (!= begin())
         * @return l'iterateur positionné sur le précédent élément de la liste
         */
        const_iterator &operator--() {
            assert(m_current != m_sentinelle->next() && "La liste est vide");
            m_current = m_current->previous();
            return *this;
        }

        /**
         * operateur d'indirection * (acces non modifiable)
         * @pre l'iterateur designe une position valide dans la liste (!= end())
         * @return la valeur de l'élément designé par l'iterateur
         */
        const T &operator*() const {
            assert(m_current != m_sentinelle && "La liste est vide");
            return m_current->data();
        }

        /**
         * operateur d'indirection -> (acces non modifiable)
         * @pre l'iterateur designe une position valide dans la liste (!= end())
         * @return l'adresse de l'élément designé par l'iterateur
         */
        const T *operator->() const {
            assert(m_current != m_sentinelle && "La liste est vide");
            return &m_current->data();
        }

        /**
         * operateur de comparaison ==
         *  @param other L'iterateur a comparer
         *  @return true si les deux iterateurs designent la meme position dans la liste
         */
        bool operator==(const const_iterator &other) const {
            //assert(!empty() && "La liste est vide");
            return m_current == other.m_current;
        }

        /**
         * operateur de comparaison !=
         *  @param other L'iterateur a comparer
         *  @return true si les deux iterateurs designent une position differente dans la liste
         */
        bool operator!=(const const_iterator &other) {
            //assert(!empty() && "La liste est vide");
            return this->m_current != other.m_current || this->m_sentinelle != other.m_sentinelle;
        }

    };

    /**
     * renvoie un itérateur sur le premier élément de la liste
     * cet iterateur designe le premier élément de la liste si elle n'est pas vide
     * sinon, il designe la meme position que l'iterateur end()
     */
    const_iterator begin() const {
        //assert(!empty() && "La liste est vide");
        return const_iterator(m_sentinelle->next(), m_sentinelle);
    }

    /**
     * renvoie un iterateur qui designe une position située apres le dernier élément de la liste
     */
    const_iterator end() const {
        //assert(!empty() && "La liste est vide");
        return const_iterator(m_sentinelle, m_sentinelle);
    }

    /**
     * \brief Classe iterator
     */
    class iterator {
    protected:
        friend class Liste<T>;        // pour que la classe Liste<T> puisse acceder aux attributs prives de iterator

        Chainon *m_current;           // pointe sur l'element courant de la liste
        Chainon *m_sentinelle;       // pointe sur le chainon sentinelle de la liste

        /**
         * \brief Constructeur de iterator
         * @param current  chainon courant
         * @param sentinelle  chainon sentinelle
         */
        iterator(Chainon *current, Chainon *sentinelle) : m_current(current),
                                                          m_sentinelle(sentinelle) {}

    public:


        /**
         * operateur ++ prefixe
         * positionne l'iterateur sur le prochain élément de la liste
         * @pre l'iterateur designe une position validé dans la liste (!= end())
         * @return l'iterateur positionné sur le prochain élément de la liste
         */
        iterator &operator++() {
            assert(m_current != m_sentinelle && "La liste est vide");
            m_current = m_current->next();
            return *this;
        }

        /**
         * operateurs -- prefixe
         * positionne l'iterateur sur le précédent élément de la liste
         * @pre l'iterateur designe une position valide dans la liste (!= begin())
         * @return l'iterateur positionné sur le précédent élément de la liste
         */
        iterator &operator--() {
            assert(m_current != m_sentinelle->next() && "La liste est vide");
            m_current = m_current->previous();
            return *this;
        }

        /**
         * operateur d'indirection * (acces non modifiable)
         * @pre l'iterateur designe une position valide dans la liste (!= end())
         * @return la valeur de l'élément designé par l'iterateur
         */
        T &operator*() const {
            assert(m_current != m_sentinelle && "La liste est vide");
            return m_current->data();
        }

        /**
         * operateur d'indirection -> (acces non modifiable)
         * @pre l'iterateur designe une position valide dans la liste (!= end())
         * @return l'adresse de l'élément designé par l'iterateur
         */
        T *operator->() const {
            assert(m_current != m_sentinelle && "La liste est vide");
            return &m_current->data();
        }

        /**
         * operateur de comparaison ==
         *  @param other L'iterateur a comparer
         *  @return true si les deux iterateurs designent la meme position dans la liste
         */
        bool operator==(const iterator &other) const {
            //assert(!empty() && "La liste est vide");
            return m_current == other.m_current;
        }

        /**
         * operateur de comparaison !=
         *  @param other L'iterateur a comparer
         *  @return true si les deux iterateurs designent une position differente dans la liste
         */
        bool operator!=(const iterator &other) const {
            //assert(!empty() && "La liste est vide");
            return this->m_current != other.m_current || this->m_sentinelle != other.m_sentinelle;
        }

    };


    /**
     * renvoie un itérateur sur le premier élément de la liste
     * cet iterateur designe le premier élément de la liste si elle n'est pas vide
     * sinon, il designe la meme position que l'iterateur end()
     */
    iterator begin() {
        //assert(!empty() && "La liste est vide");
        return iterator(m_sentinelle->next(), m_sentinelle);
    }

    /**
     * renvoie un iterateur qui designe une position située apres le dernier élément de la liste
     */
    iterator end() {
        //assert(!empty() && "La liste est vide");
        return iterator(m_sentinelle, m_sentinelle);
    }

    /**
     * 3.1.2 inserer un élément dans la liste
     * @param position : position d'insertion
     * @param x : valeur à inserer
     * @return un iterateur qui designe l'élément inseré
     */
    iterator insert(iterator position, const T &x) {
        assert(position.m_sentinelle == m_sentinelle && "La liste est vide");
        Chainon *newChainon = new Chainon(x);
        position.m_current->insertBefore(newChainon);
        m_nbElements++;
        return --position;
    }

    /**
     * 3.1.3 ecrase l'élément designé par position par x
     * @param position : position de l'élément à ecraser
     * @return un iterateur qui designe l'élément ecrasé
     */
    iterator erase(iterator position) {
        assert(position.m_sentinelle == m_sentinelle && position.m_current != position.m_sentinelle && !empty() &&
               "La liste est vide"); // si la liste est vide
        auto temp = position.m_current;
        position.m_current = position.m_current->next();
        temp->detach();
        delete temp;
        m_nbElements--;
        return position;
    }


};

/**
 * 3.1 chercher un élément dans la séquence [premier, dernier[
 * @param premier : début de la séquance
 * @param dernier : fin de la sequences
 * @param x : valeur cherchée
 * @return iterateur qui designe x s'il est trouvé :
 *         cet itérateur est égal à dernier si x est absent
 */
template<class InputIterator, class T>
InputIterator find(InputIterator premier, InputIterator dernier, const T &x) {
    InputIterator returnId = dernier; // si x est absent
    for (; premier != dernier; ++premier) {// parcours de la séquence
        if (*premier == x) { // si x est trouvé
            returnId = premier; // on renvoie l'iterateur
            break;
        }
    }
    return returnId; // on renvoie l'iterateur
}

#endif //LISTE_TP2_LISTE_H