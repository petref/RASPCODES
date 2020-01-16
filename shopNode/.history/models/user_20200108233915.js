const mongoDb = require('mongodb');
const getDb = require('../util/database').getDb;

class User {
    constructor(user, email, cart) {
        this.name = username;
        this.email = email;
        this.cart = cart; // {item:[]}
    }


    save() {
        const db = getDb();
        return db.collectio('users').insertOne(this)
    }

    static addToCart() {
        const cartProduct = this.cart.items.findIndex(cp => {
            return cp_.id === product._id
        })
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