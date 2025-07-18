/*********************************************************************/
/**   Estruturas de Dados II                                        **/
/**         CDIA                                                    **/
/**   GRAFOS EM REDES SOCIAIS                                      **/
/**   Igor Oliveira Duarte                                          **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

#define INFINITO 999999
typedef int bool;

typedef struct{
    int numVertices;
    int numArestas;
    bool** matriz;
}Grafo;

//Func. auxiliar para o sistema de correção automática (não mexer)
void pritf123(){
            ////
}

typedef struct aux{
    int vertice;
    struct aux* prox;
}ElementoLista, *PONT;

typedef struct aux2{
    int origem;
    int destino;
    struct aux2* prox;
}ArestaLista, * PONT2;


bool inicializaGrafo(Grafo* g, int vertices){
    if(g==NULL || vertices<1)return false;
    g->numVertices = vertices;
    g->numArestas = 0;
    int x, y;
    g->matriz = (bool**)malloc(sizeof(bool*)*vertices);
    for (x=0; x<vertices; x++){
        g->matriz[x] = (bool*)malloc(sizeof(bool)*vertices);
        for(y=0; y<vertices; y++){
            g->matriz[x][y] = false;
        }
    }
    return true;
}


bool liberaGrafo(Grafo* g){
    if(g==NULL)return false;
    int x;
    for(x=0; x<g->numVertices; x++)
        free(g->matriz[x]);
    free(g->matriz);
    g->numVertices = 0;
    g->numArestas = 0;
    g->matriz = NULL;
    return true;
}

bool insereAresta(Grafo* g, int v1, int v2){
    if(!g || v1<0 || v2 < 0 || v1 >= g->numVertices|| v2 >= g->numVertices)return false;
    if(g->matriz[v1][v2] == false){
        g->matriz[v1][v2] = true;
        g->numArestas++;
    }
    return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
    if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
    g->matriz[v1][v2] = false;
    g->numArestas--;
    return true;
  }
  
  
  /* Funcao que cria um grafo com o numero de vertices e
     numero de arestas passados como parametro e retorna seu endereco.
  */
  Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
    int x, y, a, total;
    if (numVertices < 1 || numArestas >= numVertices*numVertices/2) {
      printf("Parametros invalidos, o grafo nao sera gerado.\n");
      return NULL;  
    }
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    inicializaGrafo(g,numVertices);
  
    a = 0;
    while(a<numArestas){
      x = rand()%numVertices;
      y = rand()%numVertices;
      if (g->matriz[x][y] == false){
        g->matriz[x][y] = true;
        a++;
      }
    }
    g->numArestas = numArestas;
    return g;
  }
  
  
  
  /* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
     de adjacencias.
  */
  void exibeGrafo(Grafo* g){
    if(!g) return;
    int x, y;
    printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
    for (x=0;x<g->numVertices;x++) printf(" %3i",x);
    printf("\n");
    for (x=0;x<g->numVertices;x++){
      printf("%3i",x);
      for (y=0;y<g->numVertices;y++)
        printf(" %3i",g->matriz[x][y]);  
      printf("\n");
    }
    printf("\n");
  }
  
  
  /* Funcao que calcula a distancia e o predecedor considerando todos os pares
     vertices (distancia de todos para todos), com base no algoritmo de 
     Floyd-Warshall.
  */
  void calculaDistanciaFloydWarshall(Grafo* g, int** dist, int** pred){
    int i, j, k, n;
    n = g->numVertices;
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(g->matriz[i][j] != false){
          dist[i][j] = g->matriz[i][j];
          pred[i][j] = i;
        }else{
          dist[i][j] = INFINITO;
          pred[i][j] = -1;
        }
    for(i=0;i<n;i++) {
      dist[i][i] = 0;
      pred[i][i] = i;
    }
  
    for(k=0;k<n;k++)
      for(i=0;i<n;i++)
        for(j=0;j<n;j++)
          if(dist[i][j] > dist[i][k] + dist[k][j]){
            dist[i][j] = dist[i][k] + dist[k][j];
            pred[i][j] = pred[k][j];
          }
  }
  
  
  /* Funcao que exibe uma matriz de distancias.
     Caso a distancia seja INFINITO, imprime '-'.
  */
  void exibeMatrizDistancias(int** matriz, int n){
    printf("Exibindo matriz de distancias.\n");
    int x, y;
    for (x=0; x<n; x++) printf("\t%3i", x);
    printf("\n");
    for (x=0; x<n; x++){
      printf("%i", x);
      for (y=0; y<n; y++){
        if (matriz[x][y] == INFINITO) printf("\t-");
        else printf("\t%3i",matriz[x][y]);
      }
      printf("\n");
    }
    printf("\n");
  }
  
  
  /* Funcao que exibe uma matriz de predecessores.
     Caso a distancia seja INFINITO, imprime '-'.
  */
  void exibeMatrizPredecessores(int** matriz, int n){
    printf("Exibindo matriz de predecessores.\n");
    int x, y;
    for (x=0; x<n; x++) printf("\t%3i", x);
    printf("\n");
    for (x=0; x<n; x++){
      printf("%i", x);
      for (y=0; y<n; y++){
        printf("\t%3i",matriz[x][y]);
      }
      printf("\n");
    }
    printf("\n");
  }
  
  
  /* Funcao que exibe os valores de um arranjo de numeros reais */
  void exibeArranjoReais(double* arranjo, int n){
    int x;
    for (x=0; x<n; x++) printf("  v%i\t", x);
    printf("\n");
    for (x=0; x<n; x++){
      printf("%4.3f\t",arranjo[x]);
    }
    printf("\n\n");
  }
  
  
  
  /* Funcao que calcula a Centralidade de Grau de todos os vertices. */
  void centralidadeDeGrau(Grafo* g, double* valores) {
    if(g==NULL || valores ==NULL)return;
    int n = g->numVertices;
    if(n<=1){
      for(int v=0; v < n; v++){
        valores[v]= 0.0;
      }
      return;
    }
    for(int v = 0; v < n; v++){
      int grauEntrada = 0;
      for(int u = 0; u < n; u++){
        if(u != v && g->matriz[u][v]){
          grauEntrada++;
        }
      }
      valores[v] = (double)grauEntrada / (n-1);
    }
  }
  
  
  /* Funcao que calcula a Centralidade de Proximidade de todos os vertices. */
  void centralidadeDeProximidade(Grafo* g, double* valores) {
     if(g==NULL || valores ==NULL)return;
    
    
     int n = g->numVertices;
     int** dist =(int**)malloc(n*sizeof(int*));
     for(int i=0; i<n; i++){
      dist[i] = (int*)malloc(n * sizeof(int));
     }
     int** pred =(int**)malloc(n*sizeof(int*));
     for(int i=0; i<n; i++){
      pred[i] = (int*)malloc(n * sizeof(int));
     }

     //TESTE DE CHAMADA DE DISTANCIA CALCULO FLOYD-WARSHALL
     calculaDistanciaFloydWarshall(g,  dist, pred);
     //para cada vertice
     for (int v = 0; v<n; v++){
      double somaDistancias = 0.0;
      int verticesAlcancaveis = 0;  
      //distancia de v pa4ra todos os outros vertices
      for(int u = 0; u< n; u++){
        if(v != u && dist[v][u]< INFINITO){
          somaDistancias  += dist[v][u];
          verticesAlcancaveis++;
        }
      }

      if(verticesAlcancaveis > 0 && somaDistancias >0){
        valores[v] = (double)(n-1)/ somaDistancias; 
      }else{
        valores[v] = 0.0;
      }
     }
     for(int i = 0; i<n; i++){
      free(dist[i]);
      free(pred[i]);
     }
     free(dist);
     free(pred);
    
  }
  
  
  /* Funcao que calcula a Centralidade de Intermediacao de todos os vertices. */
  //TOPICOS PARA NÃO ESQUECER DEPOIS
  //-> fazer função para cada par de vértices (s,t) -> função para MENOR distancia -> Inspirar em algoritmos de Brandes
  void centralidadeDeIntermediacao(Grafo* g, double* valores) {
    if(!g || !valores || g->numVertices < 5){          // para caso o vértice seja menor que 5 ele ser equivalente à: 0.0
      
  
  /* Funcao que calcula a Centralidade Page Rank de todos os vertices. */
  /* Adiciondo mais parametros. Função baseada no Algoritmo de Power Interation*/
  void centralidadePageRank(Grafo* g, double* valores, int iteracoes) {
    if(!g || !valores || iteracoes<=0)return;
    int n= g->numVertices;
    //adicionando os fatores de amortecimento
    const double d = 0.85;
    double* r_prev = (double*)malloc(n * sizeof(double)); // alocação de memória do pagerank anterior 

    //Uniformizando todos os valores para 1.0/n
    for(int i = 0; i<n; i++){
      valores[i] = 1.0 /n;

    }
    for(int t = 0; t < iteracoes; t++){
      for(int i = 0; i<n; i++){     //loop do Power Interation para interar todo PageRank para r_prev
        r_prev[i] = valores[i];
      }
      int* grau_saida =(int*)calloc(n, sizeof(int)); //calculo de saída 
      for(int i = 0; i<n ; i++){
        for (int j = 0; j<n; j++){
          if(i != j && g->matriz[i][j]){
            grau_saida[i]++;
          }
        }
      }
      //Atualizando o valor da Pagina
      for (int i=0; i<n; i++){
        double soma = 0.0; 
        for(int j = 0; j< n; j++){
          if(g->matriz[j][i] && j != i){
            if(grau_saida[j]>0){
              soma += r_prev[j] / grau_saida[j];
            }
          }
        }
        valores[i] = (1.0 - d)/ n + d *soma;
      }
      free(grau_saida);
    }
    free(r_prev);
  }
  
  
  /* FIM DAS FUNCOES QUE DEVEM SER COMPLETADAS */
  
  
  /* Funcao que invoca e exibe os valores de cada uma das funcoes que voces
     devem implementar neste EP.
  */
  void testaFuncoes(Grafo* g, int n){
  
    double* valoresReais = (double*)malloc(sizeof(double)*n);
  
    printf("Centralidade de Grau:\n");
    centralidadeDeGrau(g, valoresReais);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade de Proximidade:\n");
    centralidadeDeProximidade(g, valoresReais);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade de Intermediacao:\n");
    centralidadeDeIntermediacao(g, valoresReais);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade Page Rank: 0 iteracoes\n");
    centralidadePageRank(g, valoresReais, 0);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade Page Rank: 1 iteracao\n");
    centralidadePageRank(g, valoresReais, 1);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade Page Rank: 10 iteracoes\n");
    centralidadePageRank(g, valoresReais, 10);
    exibeArranjoReais(valoresReais, n);
  
    printf("Centralidade Page Rank: 100 iteracoes\n");
    centralidadePageRank(g, valoresReais, 100);
    exibeArranjoReais(valoresReais, n);
  
    free(valoresReais);
  }
  
  
  /* Funcao main para testar as funcoes implementadas neste EP.
     Esta parte do codigo nao sera usada na correcao do EP e nao contempla
     todos os testes possiveis.
     Fique a vontade para realizar testes adicionais.
  */
  int main() {
  
    int n = 5;
    double* valoresReais = (double*)malloc(sizeof(double)*n);
    
    Grafo g1;
  
    printf("PRIMEIRO EXEMPLO\n");
  
    inicializaGrafo(&g1, n);
    insereAresta(&g1,0,1);
    insereAresta(&g1,1,2);
    insereAresta(&g1,2,3);
    insereAresta(&g1,3,4);
    insereAresta(&g1,4,0);
    insereAresta(&g1,0,2);
    insereAresta(&g1,1,4);
    insereAresta(&g1,1,3);
  
    exibeGrafo(&g1);
  
    testaFuncoes(&g1, n);
  
  
    printf("\n\nSEGUNDO EXEMPLO [auto-lacos]\n");
    insereAresta(&g1,0,0);
    insereAresta(&g1,2,2);
  
    exibeGrafo(&g1);
  
    testaFuncoes(&g1, n);
  
  
    printf("\n\nTERCEIRO EXEMPLO\n");
    Grafo g2;
    inicializaGrafo(&g2, n);
    insereAresta(&g2,0,2);
    insereAresta(&g2,1,2);
    insereAresta(&g2,3,2);
    insereAresta(&g2,4,2);
    insereAresta(&g2,2,0);
    insereAresta(&g2,2,1);
    insereAresta(&g2,2,3);
    insereAresta(&g2,2,4);
  
    exibeGrafo(&g2);
  
    testaFuncoes(&g2, n);
  
  
    printf("\n\nQUARTO EXEMPLO (grafo aleatorio)\n\n");
    n = 10;
    int arestas = 40;
    
    Grafo* g3 = criaGrafoAleatorio(n,arestas);
  
    exibeGrafo(g3);
   
    testaFuncoes(g3, n);
  
      return 0;  
  }
