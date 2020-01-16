// const fs = require('fs');
// const path = require('path');
const Cart = require('./cart')

const db = require('./../util/database');

// const p = path.join(
//     path.dirname(process.mainModule.filename),
//     'data',
//     'products.json'
// );

// const getProductsFromFile = cb => {
//     fs.readFile(p, (err, fileContent) => {
//         if (err) {
//             cb([]);
//         } else {
//             cb(JSON.parse(fileContent));
//         }
//     });
// };

module.exports = class Product {
    constructor(id, title, imageURL, description, price) {
        this.id = id;
        this.title = title;
        this.imageURL = imageURL;
        this.description = description;
        this.price = price;
    }

    save() {
        db.execute('INSERT INTO products(title,price,imageUrl,description) VALUES(?,?,?,?)', [this.title, this.price, this.imageURL, this.description])
            // getProductsFromFile(products => {
            //     if (this.id) {
            //         const existingProductIndex = products.findIndex(prod => prod.id === this.id);
            //         const updatedProducts = [...products];
            //         updatedProducts[existingProductIndex] = this;
            //         fs.writeFile(p, JSON.stringify(updatedProducts), err => {
            //             console.log(err)
            //         });

        //     } 
        //     else {
        //         this.id = Math.random().toString();
        //         products.push(this);
        //         fs.writeFile(p, JSON.stringify(products), err => {
        //             console.log(err)
        //         });
        //     }
        // });
    }

    static deleteById(id) {
        // getProductsFromFile(products => {
        //     const product = products.find(prod => prod.id === id);
        //     const updatedProducts = products.filter(prod => prod.id !== id);

        //     fs.writeFile(p, JSON.stringify(updatedProducts), err => {
        //         if (!err) {
        //             Cart.deleteProduct(id, product.price);
        //         }
        //     })
        // });
    };

    static fetchAll() {
        // getProductsFromFile(cb);
        return db.execute('SELECT * FROM products')
    }

    static findbyId(id) {
        // getProductsFromFile(products => {
        //     const product = products.find(p => p.id === id);
        //     cb(product);
        // })
    }
};