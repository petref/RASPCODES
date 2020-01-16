const Product = require('../models/product')

exports.getAddProduct = (req, res, next) => {

    res.render('admin/edit-product', {
        pageTitle: 'Add Product',
        path: '/admin/add-product',
        editing: false
    });
};

exports.postAddProduct = (req, res, next) => {
    const title = req.body.title;
    const imageURL = req.body.imageUrl;
    const price = req.body.price;
    const description = req.body.description;
    const product = new Product({ title: title, price: price, description: description, imageUrl: imageUrl });
    product
        .save()
        .then((result) => {
            // console.log(result);
            res.redirect('/products');
        }).catch((err) => {
            console.log('ERR: ' + err)
        })
};

exports.getEditProduct = (req, res, next) => {
    const editMode = req.query.edit;

    if (!editMode) {
        return res.redirect('/');
    }

    const prodId = req.params.productId;
    Product.findById(prodId)
        .then(product => {
            if (!product) {
                return res.redirect('/');
            }
            res.render('admin/edit-product', {
                pageTitle: 'Edit Product',
                path: 'admin/edit-product',
                editing: editMode,
                product: product
            })
        })
        .catch((err) => {
            console.log(err)
        })
};

exports.postEditProduct = (req, res, next) => {
    const prodId = req.body.productId
    const updatedTitle = req.body.title;
    const updatedPrice = req.body.price;
    const updatedImageURL = req.body.imageURL;
    const updatedDesc = req.body.description;


    const product = new Product(updatedTitle, updatedPrice, updatedDesc, updatedImageURL, prodId);
    console.log(product)
    product
        .save()
        .then(result => {
            // console.log('UPDATED PRODUCT')
            res.redirect('/admin/products')
        })
        .catch(err => {
            console.log(err)
        })
};

exports.getProducts = (req, res, next) => {
    Product.fetchAll()
        .then(products => {
            res.render('admin/products', {
                prods: products,
                pageTitle: 'Admin  Product',
                path: '/admin/products'
            })

        })
        .catch((err) => {
            console.log(err)
        })

    //     // Product.fetchAll(products => {
    //     //     res.render('admin/products', {
    //     //         prods: products,
    //     //         pageTitle: 'Admin  Product',
    //     //         path: '/admin/products'
    //     //     });
    //     // });
}

exports.postDeleteProduct = (req, res, next) => {
    const prodId = req.body.productId;
    // Product.deleteById(prodId);
    Product.deleteById(prodId)
        .then(() => {
            res.redirect('/admin/products');
        })
        .catch(err => {
            console.log(err)
        })
};