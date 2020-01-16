const mongoDb = require('mongodb');
const getDb = require('../util/database').getDb;

const ObjectId = mongoDb.ObjectId;

class User {
    constructor(user, email, cart, id) {
        this.name = user;
        this.email = email;
        this.cart = cart; // {item:[]}
        this._id = id;
    }


    save() {
        const db = getDb();
        return db.collection('users').insertOne(this)
    }

    addToCart(product) {
        const cartProduct = this.cart.items.findIndex(cp => {
            return cp_.id === product._id;
        })
        const updatedCart = { items: [{ prodId: product._id, quantity: 1 }] }
        const db = getDb();
        return db.collection('users')
            .updateOne({ _id: new ObjectId(this._id) }, { $set: { cart: updatedCart } })
    }


    static findById(userId) {
        const db = getDb();
        return db.collection('users').findOne({ _id: new mongoDb.ObjectId(userId) })
            .then(user => {
                console.log(user)
                return user
            })
            .catch(err => { console.log(err) })
    }
}


module.exports = User