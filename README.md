# 1st Homework - Processamento de Imagens

## Dependências

- CMake >= 3.10
- OpenCV
- GLM

## Compilação

```bash
cmake -S . -B build
cmake --build build
```

Os executáveis serão gerados dentro da pasta `build/`.

---

## Execução

### Q2 — Convolução (filtro passa-alta ou passa-baixa)

```bash
./question2 <imagem> <h|l>
```

- `h` — filtro laplaciano (passa-alta)
- `l` — filtro de média (passa-baixa)

---

### Q3 — Equalização de Histograma

```bash
./question3 <imagem>
```

---

### Q4 — Filtro da Mediana

```bash
./question4 <imagem> <tamanho_janela>
```

- `tamanho_janela` — tamanho da vizinhança (ex: `3` para janela 3×3)

---

### Q5 — Filtragem no Domínio da Frequência

```bash
./question5 <imagem> <k1> <k2>
```

- `k1`, `k2` — coeficientes do filtro gaussiano (ex: `0.35 2`)