#define DECL_TABLEAU(t)                                              \
    typedef struct                                                   \
    {                                                                \
        unsigned int taille;                                         \
        unsigned int capacite;                                       \
        t *tab;                                                      \
    } Tableau_##t;                                                   \
                                                                     \
    Tableau_##t creer_tableau_##t();                                 \
    void redimensionner_tableau_##t(Tableau_##t *v, unsigned int n); \
    void ajouter_fin_tableau_##t(Tableau_##t *v, t element);         \
    void supprimer_premier_tableau_##t(Tableau_##t *v);              \
    void concatener_tableau_##t(Tableau_##t *v1, Tableau_##t *v2);

#define IMPL_TABLEAU(t)                                                            \
    Tableau_##t creer_tableau_##t()                                                \
    {                                                                              \
        Tableau_##t v = {0, 0, NULL};                                              \
        return v;                                                                  \
    }                                                                              \
                                                                                   \
    void redimensionner_tableau_##t(Tableau_##t *v, unsigned int n)                \
    {                                                                              \
        if (v->taille > n)                                                         \
            return;                                                                \
        t *tmp = realloc(v->tab, n * sizeof(t));                                   \
        if (tmp != NULL || n == 0)                                                 \
        {                                                                          \
            v->tab = tmp;                                                          \
            v->capacite = n;                                                       \
        }                                                                          \
    }                                                                              \
                                                                                   \
    void ajouter_fin_tableau_##t(Tableau_##t *v, t element)                        \
    {                                                                              \
        if (v->taille == v->capacite)                                              \
            redimensionner_tableau_##t(v, v->capacite == 0 ? 1 : v->capacite * 2); \
        v->tab[v->taille++] = element;                                             \
    }                                                                              \
                                                                                   \
    void supprimer_premier_tableau_##t(Tableau_##t *v)                             \
    {                                                                              \
        if (v->taille == 0)                                                        \
            return;                                                                \
        v->taille--;                                                               \
        if (v->taille > 0)                                                         \
            memmove(&v->tab[0], &v->tab[1], v->taille * sizeof(t));                \
    }                                                                              \
                                                                                   \
    void concatener_tableau_##t(Tableau_##t *v1, Tableau_##t *v2)                  \
    {                                                                              \
        unsigned int tmin = v1->taille + v2->taille;                               \
        if (v1->capacite < tmin)                                                   \
            redimensionner_tableau_##t(v1, tmin);                                  \
        memcpy(&v1->tab[v1->taille], v2->tab, v2->taille * sizeof(t));             \
        v1->taille = tmin;                                                         \
    }