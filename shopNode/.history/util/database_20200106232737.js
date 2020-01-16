// const mysql = require('mysql2');

// const pool = mysql.createPool({
//     host: 'localhost',
//     user: 'root',
//     database: 'node-complete',
//     password: 'nodeServerTest@2020'
// })

// module.exports = pool.promise();

// const Sequelize = require('sequelize');

// const sequelize = new Sequelize('node-complete', 'root', 'nodeServerTest@2020', { dialect: 'mysql', host: 'localhost' });

// module.exports = sequelize;

const mongodb = require('mongodb')
const MongoClient = mongodb.MongoClient

let _db;

const mongoConnect = (callback) => {
    MongoClient.connect('mongodb+srv://petroupb:Transport@poli2019@cluster0-zo0ok.mongodb.net/shop?retryWrites=true&w=majority')
        .then(client => {
            console.log('connected')
            _db = client.db()
            callback()
        })
        .catch(err => {
            console.log(err)
            throw err;
        });
}

const getDb = () => {
    if (_db) {
        return _db
    }
    throw 'No database found'
}

exports.mongoConnect = mongoConnect;
exports.getDb = getDb;

module.exports = mongoConnect;