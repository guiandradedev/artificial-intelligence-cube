import Cube from './Cube.js'

const cube = new Cube();
cube.init();
console.log(cube, cube.get(0,0,0))
cube.print()
const newCube = cube.U()
cube.print()
newCube.print()