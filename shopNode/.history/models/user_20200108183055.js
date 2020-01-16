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

}


module.exports = User