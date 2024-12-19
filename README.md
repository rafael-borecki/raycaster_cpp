# Raycaster C++

## Participantes

- Bruno Rusca Janini
- Rafael Guimarães Borecki de Carvalho
- Vitor Alexandre Garcia Vaz

## Funcionamento do Jogo

Este projeto é um jogo de raycasting desenvolvido em C++. O raycasting é uma técnica de renderização que simula a projeção de raios para criar uma perspectiva 3D a partir de um mapa 2D.

### Controles do Jogo

- **W**: Mover para frente
- **S**: Mover para trás
- **A**: Rotacionar visão para a esquerda
- **D**: Rotacionar visão para a direita
- **G**: Voltar ao spawn (centro do maoa)

### Objetivos

- Encontrar a saída do labirinto.
- Completar o trajeto de saída antes que o tempo se esgote

### Como Executar

1. Clone o repositório:
    ```sh
    git clone "https://github.com/rafael-borecki/raycaster_cpp.git"
    ```
2. Navegue até o diretório do projeto:
    ```sh
    cd raycaster_cpp
    ```
3. Compile o projeto:
    ```sh
    make all
    ```
4. Execute o jogo:
    ```sh
    make run
    ```
    ou
   ```sh
   ./game
   ```

   

### Dependências

- SFML (Simple and Fast Multimedia Library)

Certifique-se de ter a biblioteca SFML instalada no seu sistema antes de compilar o projeto: <a href = "https://www.sfml-dev.org/download.php"> Download SFML</a>


## Resumo do projeto

### Fluxograma do loop de jogo
![mainRaycaster](https://github.com/user-attachments/assets/55940140-3069-4e64-83b2-69c19954b2d5)

## Jogo em funcionamento
### Login

O jogador deve digitar seu nickname e pressionar enter

![nome](https://github.com/user-attachments/assets/d8aefb77-1afa-47c4-8043-0d981cc6b615)



### Menu
![menu](https://github.com/user-attachments/assets/4091cf8d-d8fa-41c9-b42a-eb191f8a86c9)

### Interface de Jogo
![jogoRenderizado](https://github.com/user-attachments/assets/a13ead60-d8a6-44d6-910f-67bbeacd62fc)

### Saída do mapa
![miniMapa](https://github.com/user-attachments/assets/410a4f19-243d-4c27-8816-0e961f3608a1)
![saidaMapa](https://github.com/user-attachments/assets/175062b5-0619-4359-9a20-23595ae804ec)


