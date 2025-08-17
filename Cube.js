import MiniCube from "./MiniCube.js";

class Cube {
    constructor() {
        this.matrix = Array.from({ length: 2 }, () =>
            Array.from({ length: 2 }, () =>
                Array.from({ length: 2 }, () => 0)
            )
        );
    }

    init() {
        // mapa de cores por coordenada (left, right, mid)
        const colors = {
            "000": [4, 2, 0], // laranja, azul, amarelo
            "001": [4, 2, 1], // laranja, azul, branco
            "010": [3, 4, 0], // verde, laranja, amarelo
            "011": [3, 4, 1], // verde, laranja, branco
            "100": [2, 5, 0], // azul, vermelho, amarelo
            "101": [2, 5, 1], // azul, vermelho, branco
            "110": [5, 3, 0], // vermelho, verde, amarelo
            "111": [5, 3, 1], // vermelho, verde, branco
        };

        for (let x = 0; x < this.matrix.length; x++) {
            for (let y = 0; y < this.matrix[x].length; y++) {
                for (let z = 0; z < this.matrix[x][y].length; z++) {
                    const key = `${x}${y}${z}`;
                    const [left, right, mid] = colors[key];

                    const element = new MiniCube(key, left, right, mid);

                    this.matrix[x][y][z] = element;
                }
            }
        }
    }

    get(x, y, z) {
        return this.matrix[x][y][z];
    }

    set(x, y, z, value) {
        this.matrix[x][y][z] = value;
    }

    U() {
        // Rotação para cima
        const temp = this.matrix[0][0][0];
        this.matrix[0][0][0] = this.matrix[1][0][0];
        this.matrix[1][0][0] = this.matrix[1][1][0];
        this.matrix[1][1][0] = this.matrix[0][1][0];
        this.matrix[0][1][0] = temp;
    }

    D() {
        // Rotação para baixo
        const temp = this.matrix[0][1][0];
        this.matrix[0][1][0] = this.matrix[0][0][0];
        this.matrix[0][0][0] = this.matrix[1][0][0];
        this.matrix[1][0][0] = this.matrix[1][1][0];
        this.matrix[1][1][0] = temp;
    }

    B() {
        // Rotação para trás
        const temp = this.matrix[0][0][1];
        this.matrix[0][0][1] = this.matrix[1][0][1];
        this.matrix[1][0][1] = this.matrix[1][1][1];
        this.matrix[1][1][1] = this.matrix[0][1][1];
        this.matrix[0][1][1] = temp;
    }

    R() {
        // Rotação para a direita
        const temp = this.matrix[0][0][0];
        this.matrix[0][0][0] = this.matrix[0][0][1];
        this.matrix[0][0][1] = this.matrix[0][1][1];
        this.matrix[0][1][1] = this.matrix[0][1][0];
        this.matrix[0][1][0] = temp;
    }

    L() {
        // Rotação para a esquerda
        const temp = this.matrix[0][0][0];
        this.matrix[0][0][0] = this.matrix[0][1][0];
        this.matrix[0][1][0] = this.matrix[0][1][1];
        this.matrix[0][1][1] = this.matrix[0][0][1];
        this.matrix[0][0][1] = temp;
    }

    F() {
        // Rotação para frente
        const temp = this.matrix[0][0][0];
        this.matrix[0][0][0] = this.matrix[0][0][1];
        this.matrix[0][0][1] = this.matrix[0][1][1];
        this.matrix[0][1][1] = this.matrix[0][1][0];
        this.matrix[0][1][0] = temp;
    }

    print() {
        for (let x = 0; x < this.matrix.length; x++) {
            for (let y = 0; y < this.matrix[x].length; y++) {
                for (let z = 0; z < this.matrix[x][y].length; z++) {
                    console.log(x,y,z, this.matrix[x][y][z].name, this.matrix[x][y][z].left, this.matrix[x][y][z].right, this.matrix[x][y][z].mid);
                }
            }
        }
    }
}

export default Cube;
