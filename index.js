import Cube from './Cube.js'

const cube = new Cube();
cube.init();
console.log(cube, cube.get(0,0,0))
console.log("Cubo antes da alteracao")
cube.print()
const newCube = cube.U()
console.log("Cubo depois da alteracao")
cube.print()
console.log("Cubo clone depois da alteracao")
newCube.print()