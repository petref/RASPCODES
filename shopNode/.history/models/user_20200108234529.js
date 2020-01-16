const mongoDb = require('mongodb');
const getDb = require('../util/database').getDb;

class User {
    constructor(user, email, cart, id) {
        this.name = username;
        this.email = email;
        this.cart = cart; // {item:[]}
        this._id = id;
    }


    save() {
        const db = getDb();
        return db.collectio('users').insertOne(this)
    }

    static addToCart() {
        // const cartProduct = this.cart.items.findIndex(cp => {
        //     return cp_.id === product._id;
        // })
        const updatedCart = { item: [{...product, quantity: 1 }] }
        const db = getDb();
        db.collection('users').updateOne({ _id: new ObjectId(this._id) })
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