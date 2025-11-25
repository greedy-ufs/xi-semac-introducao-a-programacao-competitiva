# Notas de Aula sobre busca Binária

## Uma breve (!!!) introdução aos algoritmos de ordenação

Antes de tudo, é importante entender por que é relevante conhecer os algoritmos de ordenação. Eles são fundamentais porque diferentes algoritmos podem demandar mais ou menos tempo de execução. E como tempo é dinheiro, torna-se essencial compreender essas otimizações para evitar desperdício de processamento. Um exemplo disso ocorre em ambientes como as funções Lambda da AWS, que podem executar processos de ordenação, como a classificação de usuários em um placar (scoreboard) dos melhores jogadores, onde um algoritmo ineficiente pode gerar custos desnecessários.

### Tabela de algoritmos de ordenação (do mais burro ao mais eficiente)


| Algoritmo                        | Melhor caso | Caso médio | Pior caso  | Operações aproximadas |
| -------------------------------- | ----------- | ---------- | ---------- | --------------------- |
| [Selection Sort][selection_sort] | O(n²)       | O(n²)      | O(n²)      | n(n - 1) / 2          |
| [Merge Sort][merge_sort]         | O(n log n)  | O(n log n) | O(n log n) | n log₂ n              |
| [Quick Sort][quick_sort]         | O(n log n)  | O(n log n) | O(n²)      | 1,39⋅nlog2​n          |

---

![Tabela de número de elementos por número de operações][bigo_chart]




### Quantidade aproximada de operações (comparações)

| n (elementos) | Selection Sort | Quick Sort (caso médio) |
| ------------- | -------------- | ----------------------- |
| 5             | 10             | 16                      |
| 10            | 45             | 46                      |
| 100           | 4.950          | 923                     |
| 500           | 124.750        | 6.215                   |
| 1000          | 499.500        | 13.900                  |

### Código!

Antes de começar no código, é importante saber que a implementação padrão da STL utiliza um algoritmo híbrido entre quicksort, heapsort e insertion sort, chamado de [introsort][sort_cppreference]. Isso significa que o C++ já escolhe automaticamente o melhor algoritmo para cada situação, eliminando a necessidade de você implementar esses algoritmos manualmente.

Na prática, você só precisa usar a função `sort()` da STL. Abaixo, veremos os diferentes contextos em que você pode usá-la:

#### Ordenação em array simples

O caso mais básico: ordenar um array de números inteiros ou qualquer tipo primitivo em ordem crescente.

```cpp
ll v[] = {5, 2, 9, 1, 3};
ll n = size(v) / size(v[0]);

sort(v, v + n);
```

Aqui, `sort(v, v + n)` ordena todos os `n` elementos do array `v`. O resultado será `{1, 2, 3, 5, 9}`.

#### Ordenação de indices em posições diferentes

Às vezes, você não quer ordenar o array inteiro, apenas uma parte dele. Para isso, você passa os iteradores (ou ponteiros) que definem o intervalo desejado.

```cpp
ll v[] = {5, 2, 9, 1, 3};

// Ordena apenas os elementos do índice 1 ao 3
sort(v + 1, v + 4);
```

Neste exemplo, apenas os elementos nos índices 1, 2 e 3 (valores `{2, 9, 1}`) serão ordenados, resultando em `{5, 1, 2, 9, 3}`.

#### Ordenação de vetor

Quando você trabalha com `vector` em vez de arrays tradicionais, o processo é similar, mas você usa `begin()` e `end()` para especificar o intervalo.

```cpp
vector<string> nomes = {"Carlos", "Ana", "Bruno"};

sort(nomes.begin(), nomes.end());
```

Este código ordena os nomes em ordem lexicográfica (alfabética), resultando em `{"Ana", "Bruno", "Carlos"}`.

#### Ordenação de vetor com pair

Estruturas como `pair` têm uma ordem padrão: primeiro comparam pelo primeiro elemento, e se forem iguais, comparam pelo segundo. Isso torna fácil ordenar dados compostos de duas chaves.

```cpp
vector<pair<int,int>> v;
v.push_back({1,5});
v.push_back({2,3});
v.push_back({1,2});

sort(v.begin(), v.end());
```

O resultado será `{{1,2}, {1,5}, {2,3}}`. Observe que os pares começando com `1` aparecem antes dos pares começando com `2`, e entre os pares que começam com `1`, o que tem segundo elemento menor vem primeiro.

#### Ordenação personalizada

Nem sempre a ordem padrão é o que você quer. Para casos como ordenar strings pelo tamanho em vez de lexicograficamente, você precisa definir uma função comparadora personalizada.

```cpp
bool comp(const string &a, const string &b) {
  // critério 1: menor tamanho
  if (a.size() != b.size()) return a.size() < b.size();

  // critério 2: ordem lexicográfica
  return a < b;
}

int main() {
      vector<string> frutas = {
        "uva",
        "banana",
        "melancia",
        "abacate",
        "maçã",
        "kiwi",
        "pera",
        "goiaba"
    };

    sort(frutas.begin(), frutas.end(), comp);
}
```

A função `comp` define dois critérios: primeiro, ordena por tamanho (palavras mais curtas primeiro); segundo, se duas palavras têm o mesmo tamanho, ordena alfabeticamente. O resultado será: `{"uva", "kiwi", "pera", "Ana", "maçã", ...}` (ordenado por tamanho, depois alfabeticamente dentro de cada tamanho).

#### Ordenação com struct

Quando você trabalha com estruturas de dados mais complexas, a função comparadora permite especificar múltiplos critérios de ordenação. Isso é muito útil em problemas competitivos.

```cpp
struct Pessoa {
  string nome;
  int idade;
};

bool comp(const Pessoa& a, const Pessoa& b) {
  // critério 1: nome (ordem alfabética)
  if (a.nome != b.nome)
    return a.nome < b.nome;

  // critério 2: idade (crescente)
  return a.idade < b.idade;
}

int main() {
  vector<Pessoa> pessoas = {{"Ana", 22},   {"Carlos", 18}, {"Bruno", 40},
                            {"Maria", 88}, {"Bruno", 20},  {"Leila", 60}};

  sort(pessoas.begin(), pessoas.end(), comp);

  for (auto p : pessoas) cout << p.nome << " - " << p.idade << endl;
}
```

Este exemplo ordena as pessoas primeiro por nome (alfabeticamente) e depois por idade dentro de cada nome. Assim, "Ana" aparece antes de "Bruno", havendo dois "Brunos" com idades diferentes, o mais jovem apareceria primeiro.

## Problema! Boi.pdf

Implemente o que está comentado para obter a resolução correta!

## Estrutura do algoritmo binary search

A busca binária é um algoritmo fundamental para encontrar um elemento em uma **array ordenada**. Ela funciona dividindo o problema pela metade a cada iteração, reduzindo o tempo de busca de O(n) para O(log n).

A ideia é manter dois ponteiros: `left` (esquerda) e `right` (direita). A cada iteração:
1. Calcula a posição do meio: `mid`
2. Compara o elemento no meio com o alvo
3. Descarta metade do array mantendo apenas a metade onde o alvo pode estar

```cpp
int binary_search(const vector<int>& values, int target) {
    int left = 0; int right = values.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (values[mid] == target)
            return mid;
        else if (values[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}
```

A função retorna o índice do elemento se encontrado, ou `-1` se não existir no array.

### Demonstração do algoritmo

Para visualizar passo a passo como o algoritmo funciona, abra o arquivo `visualizacao.excalidraw`. Ele mostra como os ponteiros se movem a cada iteração até encontrar (ou não) o elemento desejado.

### Porque a formula não é simplesmente $\frac{(left+right)}{2}$ ?

Você pode estar se perguntando por que usamos `mid = left + (right - left) / 2` em vez de simplesmente `mid = (left + right) / 2`. A razão é evitar **overflow**.

O overflow ocorre quando um número ultrapassa o limite máximo que seu tipo pode armazenar. Se os valores de `left` e `right` estiverem muito próximos do valor máximo (por exemplo, em um array muito grande), a soma `left + right` pode ultrapassar esse limite antes da divisão.

Por exemplo, em `uint32_t`, o valor máximo é $(2^{32} - 1)$. Se ambos `left` e `right` forem próximos a esse limite e você somá-los diretamente, o resultado será inválido.

A solução é usar a manipulação matemática mostrada abaixo, que evita a soma direta:

$$
\begin{aligned}
\text{mid} &= \frac{low + high}{2} \\
&= \frac{2 \cdot low + high - low}{2} \\
&= \frac{low + low + high - low}{2} \\
&= low + \frac{high - low}{2}
\end{aligned}
$$

Assim, `mid = left + (right - left) / 2` garante que nunca haverá overflow, pois estamos calculando a diferença antes de dividir.


## lower_bound e upper_bound

Além de buscar um elemento exato, existem situações em que você quer encontrar a posição onde um valor deveria ser inserido, ou contar quantas vezes um valor aparece em um array ordenado. Para isso, a STL fornece duas funções úteis:

- **`lower_bound()`**: retorna um iterador para o primeiro elemento que é **maior ou igual** ao valor buscado
- **`upper_bound()`**: retorna um iterador para o primeiro elemento que é **estritamente maior** que o valor buscado

A diferença entre elas permite contar quantas vezes um valor aparece: `upper_bound(x) - lower_bound(x)`.

```cpp
  ll arr[] = {0, 0, 1, 1, 2, 4, 4, 6, 7, 7, 7, 8, 12, 15, 21, 21};
  ll n = sizeof(arr) / sizeof(arr[0]);
  ll a = lower_bound(arr, arr + n, 4) - arr;
  ll b = upper_bound(arr, arr + n, 4) - arr;
  cout << "(array)  count number of 4's is: " << b - a << '\n';

  vll v = {0, 0, 1, 1, 2, 4, 4, 6, 7, 7, 7, 8, 12, 15, 21, 21};
  a = lower_bound(v.begin(), v.end(), 4) - v.begin();
  b = upper_bound(v.begin(), v.end(), 4) - v.begin();
  cout << "(vector) count number of 4's is: " << b - a << '\n';
```

Neste exemplo, `lower_bound()` retorna o índice 5 (posição do primeiro `4`) e `upper_bound()` retorna o índice 7 (posição logo após o último `4`). Portanto, `7 - 5 = 2`, que é o número de `4`s no array. Ambas as funções funcionam com arrays e vetores.

## Problema! haybales.md


### Exercícios

- [K-th Not Divisible by n](https://codeforces.com/contest/1352/problem/C)
- [Factory Machines - CSES](https://cses.fi/problemset/task/1620)
- [Aquário - Codeforces 1873E](https://codeforces.com/contest/1873/problem/E)
- [+ Problemas selecionados da maratona UFMG](https://docs.google.com/spreadsheets/d/1QQ1QvYNDPKv9Aqh5c2VL_KCtpqASDWeRcLkyyXlPM0M/edit?gid=1907459156#gid=1907459156)

# Referências

- [USACO Introduction to Sorting][usaco_intro_sort]
- [USACO Binary search][usaco_binary_search]
- [USACO Binary Search on a Sorted Array][usaco_binary_search_sorted]
- [CSES Capitulo 3 sobre sorting][cses_book]
- [Youtube Visualization of Binary Search][binary_search_visu]

[selection_sort]: https://pt.wikipedia.org/wiki/Selection_sort
[merge_sort]: https://pt.wikipedia.org/wiki/Merge_sort
[quick_sort]: https://pt.wikipedia.org/wiki/Quicksort
[bigo_chart]: https://cdn-media-1.freecodecamp.org/images/1*KfZYFUT2OKfjekJlCeYvuQ.jpeg
[usaco_intro_sort]: https://usaco.guide/bronze/intro-sorting?lang=cpp
[usaco_binary_search]: https://usaco.guide/silver/binary-search?lang=cpp
[usaco_binary_search_sorted]: https://usaco.guide/silver/binary-search-sorted-array?lang=cpp
[cses_book]: https://cses.fi/book.pdf
[binary_search_visu]: https://www.youtube.com/watch?v=E6IOrZUpvSE
[sort_cppreference]: https://en.cppreference.com/w/cpp/algorithm/sort.html
