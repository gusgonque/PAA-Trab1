#include "Grafos.h"

Grafo *criaGrafo(){
    Grafo *gAux = (Grafo *) malloc(sizeof(Grafo));
    gAux->listaVertices = NULL;
    gAux->listaArestas = NULL;
    gAux->numVertices = 0;
    gAux->orientacao = 0;
    return gAux;
}

ListaAresta *criaListaAresta(){
    ListaAresta *lAux = (ListaAresta *) malloc(sizeof (ListaAresta));
    lAux->prox = NULL;
    lAux->peso = 0;
    lAux->u = 0;
    lAux->v = 0;
    return lAux;
}

ListaVertices **criaListaVerticesAdjacentes(int numVertices){
    ListaVertices **lAux = malloc(numVertices * sizeof (ListaVertices *));
    for (int i = 0; i < numVertices; ++i) {
        lAux[i] = NULL;
    }
    return lAux;
}

ListaAresta *insereListaAresta(ListaAresta *l, unsigned int u, unsigned int v, int peso){
    ListaAresta *lAux = criaListaAresta();
    lAux->peso = peso;
    lAux->u = u;
    lAux->v = v;
    lAux->prox = l; // muda a cabeça.
    return lAux;
}

ListaVertices *insereVertice(ListaVertices *l, int i, int peso) {
    ListaVertices *lAux = malloc(sizeof (ListaVertices));
    lAux->noAdjacente = i;
    lAux->peso = peso;
    lAux->prox = l; // muda a cabeça.
    return lAux;
}

void carregaVertices(Grafo *g) {
    g->listaVertices = criaListaVerticesAdjacentes(g->numVertices);
    ListaAresta *lAux = g->listaArestas;
    int i;

    while (lAux != NULL) {
        for (i = 0; i < g->numVertices; ++i) {
            if(lAux->v == i){
                if(g->orientacao)
                    g->listaVertices[lAux->u] = insereVertice(g->listaVertices[lAux->u], lAux->v, lAux->peso);
                else {
                    g->listaVertices[lAux->u] = insereVertice(g->listaVertices[lAux->u], lAux->v, lAux->peso);
                    g->listaVertices[lAux->v] = insereVertice(g->listaVertices[lAux->v], lAux->u, lAux->peso);
                }
                break;
            }
        }
        lAux = lAux->prox;
    }
}

Grafo * carregaGrafo(FILE *arq) {
    Grafo *gAux = criaGrafo();
    char *strAux = malloc(3*sizeof (char ));

    fscanf(arq,"%*10c%3s%*c",strAux);

    gAux->orientacao = (strcmp(strAux,"sim") == 0);


    fscanf(arq,"%*2c%d%*c", &(gAux->numVertices));

    int peso;
    unsigned int u, v;
    while(feof(arq) == 0){
        fscanf(arq,"%*c%u%*c%u%*2c%d%*c", &u, &v, &peso);
        gAux->listaArestas = insereListaAresta(gAux->listaArestas,u,v,peso);
    }

    carregaVertices(gAux);

    return gAux;
}
