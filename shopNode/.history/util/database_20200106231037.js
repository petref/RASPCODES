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

const mongoConnect = (callback) => {
    MongoClient.connect('mongodb+srv://petroupb:Transport@poli2019@cluster0-zo0ok.mongodb.net/test?retryWrites=true&w=majority')
        .then(client => {
            console.log('connected')
            callback(client)
        })
        .catch(err => {
            console.log(err)
        });
}

module.exports = mongoConnect;