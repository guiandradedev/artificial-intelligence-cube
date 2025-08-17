class MiniCube {
    constructor(name, left, right, mid) {
        this.name = name;
        this._left = left;
        this._right = right;
        this._mid = mid;
    }

    get left() {
        return this._left;
    }

    set left(value) {
        this._left = value;
    }

    get right() {
        return this._right;
    }

    set right(value) {
        this._right = value;
    }

    get mid() {
        return this._mid;
    }

    set mid(value) {
        this._mid = value;
    }
}

export default MiniCube;