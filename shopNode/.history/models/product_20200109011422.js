const mongoDb = require('mongodb')
const getDb = require('./../util/database').getDb;


//with sequelize
class Product {
    constructor(title, price, description, imageUrl, id, userId) {
        this.title = title;
        this.price = price;
        this.description = description;
        this.imageUrl = imageUrl;
        this._id = id ? new mongoDb.ObjectId(id) : null;
        this.userId = userId
    }

    save() {
        const db = getDb();
        let dbOp;
        if (this._id != undefined) {
            dbOp = db.collection('products')
                .updateOne({ _id: this._id }, { $set: this });
        } else {
            dbOp = db.collection('products').insertOne(this)
            console.log(this)
        }

        return dbOp
            .then(result => {

                // console.log(result)
            })
            .catch(err => { console.log(err) })

    }

    static fetchAll() {
        const db = getDb();
        return db.collection('products')
            .find()
            .toArray()
            .then(products => {
                return products
            })
            .catch();
    }

    static findById(prodId) {
        const db = getDb();
        return db.collection('products')
            .find({ _id: new mongoDb.ObjectId(prodId) })
            .next()
            .then(product => {
                console.log(product)
                return product;
            })
            .catch(err => { console.log(err) })
    }

    static deleteById(prodId) {
        const db = getDb();
        return db
            .collection('products')
            .deleteOne({ _id: new mongoDb.ObjectId(prodId) })
            .then(result => {
                console.log(result)
            })
            .catch(err => {
                console.log(err)
            })
    }
}
// const Product = sequelize.define('product', {
//     id: {
//         type: Sequelize.INTEGER,
//         autoIncrement: true,
//         allowNull: false,
//         primaryKey: true
//     },
//     title: Sequelize.STRING,
//     price: {
//         type: Sequelize.DOUBLE,
//         allowNull: false
//     },
//     imageUrl: {
//         type: Sequelize.STRING,
//         allowNull: false
//     },
//     description: {
//         type: Sequelize.STRING,
//         allowNull: false
//     }
// });

module.exports = Product;

//=============== with filesyste and with SQL 

// // const fs = require('fs');
// // const path = require('path');
// const Cart = require('./cart')

// const db = require('./../util/database');

// // const p = path.join(
// //     path.dirname(process.mainModule.filename),
// //     'data',
// //     'products.json'
// // );

// // const getProductsFromFile = cb => {
// //     fs.readFile(p, (err, fileContent) => {
// //         if (err) {
// //             cb([]);
// //         } else {
// //             cb(JSON.parse(fileContent));
// //         }
// //     });
// // };

// module.exports = class Product {
//     constructor(id, title, imageURL, description, price) {
//         this.id = id;
//         this.title = title;
//         this.imageURL = imageURL;
//         this.description = description;
//         this.price = price;
//     }

//     save() {
//         return db.execute('INSERT INTO products(title,price,description,imageUrl) VALUES(?,?,?,?)', [this.title, this.price, this.description, this.imageURL])
//             // getProductsFromFile(products => {
//             //     if (this.id) {
//             //         const existingProductIndex = products.findIndex(prod => prod.id === this.id);
//             //         const updatedProducts = [...products];
//             //         updatedProducts[existingProductIndex] = this;
//             //         fs.writeFile(p, JSON.stringify(updatedProducts), err => {
//             //             console.log(err)
//             //         });

//         //     } 
//         //     else {
//         //         this.id = Math.random().toString();
//         //         products.push(this);
//         //         fs.writeFile(p, JSON.stringify(products), err => {
//         //             console.log(err)
//         //         });
//         //     }
//         // });
//     }

//     static deleteById(id) {
//         // getProductsFromFile(products => {
//         //     const product = products.find(prod => prod.id === id);
//         //     const updatedProducts = products.filter(prod => prod.id !== id);

//         //     fs.writeFile(p, JSON.stringify(updatedProducts), err => {
//         //         if (!err) {
//         //             Cart.deleteProduct(id, product.price);
//         //         }
//         //     })
//         // });
//     };

//     static fetchAll() {
//         // getProductsFromFile(cb);
//         return db.execute('SELECT * FROM products')
//     }

//     static findbyId(id) {
//         // getProductsFromFile(products => {
//         //     const product = products.find(p => p.id === id);
//         //     cb(product);
//         // })

//         return db.execute('SELECT * FROM products WHERE products.id = ?', [id])
//     }
// };