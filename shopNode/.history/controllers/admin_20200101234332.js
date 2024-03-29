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
    const imageURL = req.body.imageURL;
    const price = req.body.price;
    const description = req.body.description;
    Product.create({
            title: title,
            price: price,
            imageUrl: imageURL,
            description: description
        })
        .then((result) => {
            // console.log(result);
            res.redirect('admin/products');
        }).catch((err) => {
            console.log(err)
        })
};

exports.getEditProduct = (req, res, next) => {
    const editMode = req.query.edit;

    if (!editMode) {
        return res.redirect('/');
    }

    const prodId = req.params.productId;
    Product.findByPk(prodId)
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
    const updatedProduct = new Product(prodId, updatedTitle, updatedImageURL, updatedDesc, updatedPrice);

    Product.findByPk(prodId)
        .then(product => {
            product.title = updatedTitle,
                product.price = updatedPrice,
                product.description = updatedDesc,
                product.imageURL = updatedImageURL,
                product.save();
        })
        .then(result => {
            res.redirect('/admin/products')
        })
        .catch(err => {
            console.log(err)
        })
};

exports.getProducts = (req, res, next) => {

    Product.findAll()
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

    // Product.fetchAll(products => {
    //     res.render('admin/products', {
    //         prods: products,
    //         pageTitle: 'Admin  Product',
    //         path: '/admin/products'
    //     });
    // });
}

exports.postDeleteProduct = (req, res, next) => {
    const prodId = req.body.productId;
    // Product.deleteById(prodId);
    Product.findByPk(prodId)
        .then(product => {
            return product.destroy();
        })
        .then(result => {
            res.redirect('/admin/products');
        })
        .catch(err => {
            console.log(err)
        })
};