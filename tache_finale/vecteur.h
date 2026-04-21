#define DECL_VECTOR(t)                                      \
    typedef struct                                          \
    {                                                       \
        int taille;                                         \
        int capacite;                                       \
        t *tab;                                             \
    } vector_##t;                                           \
                                                            \
    vector_##t creer_vector_##t();                          \
    void redimensionner_##t(vector_##t *v, int n);          \
    void concatenation_##t(vector_##t *v1, vector_##t *v2); \
    void ajouter_fin_##t(vector_##t *v, t element);         \
    void supprimer_premier_element_##t(vector_##t *v);

#define IMPL_VECTOR(t)                                                     \
                                                                           \
    vector_##t creer_vector_##t()                                          \
    {                                                                      \
        vector_##t v;                                                      \
        v.taille = 0;                                                      \
        v.capacite = 0;                                                    \
        v.tab = NULL;                                                      \
        return v;                                                          \
    }                                                                      \
                                                                           \
    void redimensionner_##t(vector_##t *v, int n)                          \
                                                                           \
    {                                                                      \
        if (v->taille > n)                                                 \
        {                                                                  \
            printf("ERREUR: redimensionnement inferieur a la taille");     \
            return;                                                        \
        }                                                                  \
        v->tab = realloc(v->tab, n * sizeof(t));                           \
        v->capacite = n;                                                   \
    }                                                                      \
    void concatenation_##t(vector_##t *v1, vector_##t *v2)                 \
    {                                                                      \
                                                                           \
        int tmin = v1->taille + v2->taille;                                \
        if (v1->capacite >= tmin)                                          \
        {                                                                  \
                                                                           \
            memcpy(&v1->tab[v1->taille], v2->tab, v2->taille * sizeof(t)); \
            v1->taille += v2->taille;                                      \
            return;                                                        \
        }                                                                  \
        redimensionner_##t(v1, v1->taille + v2->taille);                   \
        memmove(&v1->tab[v1->taille], v2->tab, v2->taille * sizeof(t));    \
        v1->taille = tmin;                                                 \
        return;                                                            \
    }                                                                      \
                                                                           \
    void ajouter_fin_##t(vector_##t *v, t element)                         \
    {                                                                      \
        if (v->taille == v->capacite)                                      \
            redimensionner_##t(v, v->capacite == 0 ? 1 : v->capacite * 2); \
                                                                           \
        memcpy(&v->tab[v->taille++], &element, sizeof(t));                 \
    }                                                                      \
    void supprimer_premier_element_##t(vector_##t *v)                      \
    {                                                                      \
        memmove(&v->tab[0], &v->tab[1], (--(v->taille)) * sizeof(t));      \
    }

// DECL_VECTOR(int);