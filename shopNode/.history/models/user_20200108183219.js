const mongoDb = require('mongodb')
const getDb = require('../util/database').getDb;

class User {
    constructor(user, email) {
        this.name = username;
        this.email = email;
    }
}

save() {
    const db = getDb();
    return db.collectio('users').insertOne(this)
}


static findById(userId) {
    const db = getDb();
    return db.collection('users').find({ _id: new mongoDb.ObjectId(userId) })
}


module.exports = User